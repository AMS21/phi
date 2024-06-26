#!/usr/bin/env bash

# See these links for help and information
# https://google.github.io/clusterfuzzlite/build-integration/
# https://google.github.io/clusterfuzzlite/running-clusterfuzzlite/

set -e

root_dir="$(pwd)"
build_dir="build-cflite"
oss_fuzz_dir="${build_dir}/oss-fuzz"
help_script="${oss_fuzz_dir}/infra/helper.py"

# Create directory
mkdir -p "${build_dir}"

# Clone or update oss-fuzz
if [ -d "${oss_fuzz_dir}" ]; then
    cd "${oss_fuzz_dir}"

    git stash push -q
    git pull --rebase --recurse-submodules --depth=1
    git stash pop -q || true # Ignore return value

    cd "${root_dir}"
else
    git clone https://github.com/google/oss-fuzz.git "${oss_fuzz_dir}" \
        --depth 1 --branch master --single-branch --recurse-submodules --shallow-submodules --no-tags
fi

# Build docker image
python "${help_script}" build_image --pull --cache --external "${root_dir}"

sanitizers_to_test=("none" "address" "memory" "thread" "undefined" "introspector")

# Test with all sanitizers
for sanitizer in "${sanitizers_to_test[@]}"; do
    # Build fuzzers with sanitizer
    python "${help_script}" build_fuzzers --external "${root_dir}" --sanitizer "${sanitizer}"

    # Check build
    python "${help_script}" check_build --external "${root_dir}" --sanitizer "${sanitizer}"

    # Collect list of fuzzer ignoring "llvm-symbolizer" since it't not a fuzzer and provided by clusterfuzz
    all_fuzz_targets=$(find "${oss_fuzz_dir}/build/out" -maxdepth 2 -type f -not -iname "llvm-symbolizer" -and -not -iname "*.profraw")

    # Run every fuzzer
    for fuzz_target_path in "${all_fuzz_targets[@]}"; do
        fuzz_target=$(basename "${fuzz_target_path}")

        echo "Testing '${fuzz_target}' fuzzer with '${sanitizer}' sanitizer..."

        # Setup corpus directory
        corpus_dir="/tmp/fuzzing_corpus/${fuzz_target}"

        mkdir -p "${corpus_dir}"

        # NOTE: See https://github.com/google/oss-fuzz/issues/7111 on why we need to pass the last argument in such a weird way
        python "${help_script}" run_fuzzer --corpus-dir="${corpus_dir}" --external "${root_dir}" "${fuzz_target}" -- -max_total_time=10
    done
done

echo "Finished testing ClusterFuzzLite"
