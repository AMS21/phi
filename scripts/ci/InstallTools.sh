#!/bin/bash

# shellcheck disable=SC2015

# Stop on first error
set -e
set -u

upgraded_pip=0
added_llvm_apt=0
added_ubuntu_test_ppa=0
root_dir=$(pwd)

cmake_build_flags="-O3 -DNDEBUG -w -march=native -mtune=native"

function retry {
    local try=1

    while true; do
        "$@" && break || {
            if [[ $try -lt 10 ]]; then
                ((try++))
                echo "Try failed. Attempt $try/10:"
                sleep 30
            else
                echo "The command has failed after $try attempts."
                exit 1
            fi
        }
    done
}

function apt_install() {
    echo "- Running apt-get install [$*]..."
    retry sudo apt-get install "$@" --no-install-recommends -y
    echo "- Running apt-get install [$*] done"
}

function pip_install() {
    echo "- Running pip install [$*]..."
    retry sudo -H pip3 --no-cache-dir install "$@"
    echo "- Running pip install [$*] done"
}

# Make sure pip is using the latest version
upgrade_pip() {
    if [[ "$upgraded_pip" == 0 ]]; then
        echo "-- Upgrading pip..."

        pip_install --upgrade pip
        upgraded_pip=1

        echo "-- Upgrading pip done"
    fi
}

install_python_wheel() {
    echo "--- Installing wheel on pip..."
    pip_install wheel
    echo "--- Installing wheel on pip done"
}

add_llvm_apt() {
    if [[ "$added_llvm_apt" == 0 ]]; then
        echo "-- Adding LLVM-$1 apt..."
        # Get gpg key
        retry wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key | sudo apt-key add -

        os_release=$(lsb_release -c -s)
        apt_repo="https://apt.llvm.org/$os_release/ llvm-toolchain-$os_release-$1 main"
        echo "Adding the apt repo: $apt_repo"

        # Add the required repo
        retry sudo add-apt-repository "deb $apt_repo" -y

        # Update repo list
        echo "-- Updating apt..."
        retry sudo apt-get update -m
        echo "-- Updating apt done"

        echo "-- Adding LLVM-$1 apt done"

        added_llvm_apt=1
    fi
}

add_ubuntu_test_ppa() {
    if [[ "$added_ubuntu_test_ppa" == 0 ]]; then
        echo "-- Adding Ubuntu Test PPA..."
        retry sudo add-apt-repository ppa:ubuntu-toolchain-r/test -y
        echo "-- Adding Ubuntu Test PPA done"

        echo "-- Updating apt..."
        retry sudo apt-get update -m
        echo "-- Updating apt done"

        added_ubuntu_test_ppa=1
    fi
}

install_gcovr() {
    upgrade_pip
    install_python_wheel

    echo "-- Installing gcovr..."
    pip_install gcovr
    echo "-- Installing gcovr done"

    # Verify
    echo "-- Verifying gcovr..."
    which gcovr
    gcovr --version
    echo "-- Verifying gcovr done"
}

install_cmake_format() {
    upgrade_pip
    install_python_wheel

    echo "-- Installing cmake-format..."
    # See https://cmake-format.readthedocs.io/en/latest/installation.html#installation
    pip_install cmakelang pyyaml
    echo "-- Installing cmake-format done"

    # Verify
    echo "-- Verifying cmake-format..."
    which cmake-format
    cmake-format --version
    echo "-- Verifying cmake-format done"
}

# Expects first parameter to be the requested version
install_clang() {
    add_llvm_apt "$1"

    # Install clang
    echo "-- Installing clang-$1..."
    apt_install "clang-$1" "clang++-$1" "libc++-$1-dev" "libc++abi-$1-dev" "libfuzzer-$1-dev" "llvm-$1" "g++-multilib"

    # Starting with llvm-12 there is the llvm-linker-tools package which is needed for lto support to work
    if [[ $1 -ge 12 ]]; then
        apt_install "llvm-$1-linker-tools"
    fi

    # Starting with llvm-14 there is a separate package for the compiler runtime (rt) which is needed for things like sanitizers and fuzzers
    if [[ $1 -ge 14 ]]; then
        apt_install "libclang-rt-$1-dev"
    fi

    # Starting with llvm-15 we need to install 'llvm-runtime' aswell for lto support to work
    if [[ $1 -ge 15 ]]; then
        apt_install "llvm-$1-runtime"
    fi

    echo "-- Installing clang-$1 done"

    # Verify versions
    echo "-- Verify clang-$1..."
    which "clang-$1"
    "clang-$1" --version
    echo "-- Verify clang-$1 done"

    echo "-- Verify clang++-$1..."
    which "clang++-$1"
    "clang++-$1" --version
    echo "-- Verify clang++-$1 done"

    # Export values
    # shellcheck disable=SC2129
    echo "CLANG=clang-$1" >>"$GITHUB_ENV"
    echo "CLANGXX=clang++-$1" >>"$GITHUB_ENV"

    echo "GCOV_EXECUTABLE=llvm-cov-$1 gcov" >>"$GITHUB_ENV"

    echo "AR_EXECUTABLE=llvm-ar-$1" >>"$GITHUB_ENV"

    echo "CC=clang-$1" >>"$GITHUB_ENV"
    echo "CXX=clang++-$1" >>"$GITHUB_ENV"
}

# Expects first parameter to the the requested version
install_gcc() {
    add_ubuntu_test_ppa

    echo "-- Installing gcc-$1..."
    apt_install "gcc-$1" "g++-$1" "gcc-$1-multilib" "g++-$1-multilib"
    echo "-- Installing gcc-$1 done"

    # Verify versions
    echo "-- Verify gcc-$1..."
    which "gcc-$1"
    "gcc-$1" --version
    echo "-- Verify gcc-$1 done"

    echo "-- Verify g++-$1..."
    which "g++-$1"
    "g++-$1" --version
    echo "-- Verify g++-$1 done"

    # Export values
    # shellcheck disable=SC2129
    echo "GCC=gcc-$1" >>"$GITHUB_ENV"
    echo "GXX=g++-$1" >>"$GITHUB_ENV"

    echo "GCOV_EXECUTABLE=gcov-$1" >>"$GITHUB_ENV"

    echo "AR_EXECUTABLE=ar" >>"$GITHUB_ENV"

    echo "CC=gcc-$1" >>"$GITHUB_ENV"
    echo "CXX=g++-$1" >>"$GITHUB_ENV"
}

install_valgrind() {
    echo "-- Installing valgrind..."
    apt_install valgrind
    echo "-- Installing valgring done"

    # Verify
    echo "-- Verifying valgrind..."
    which valgrind
    valgrind --version
    echo "-- Verifying valgrind done"
}

# Expects first parameter to the the requested version
install_cppcheck() {
    # Install dependencies
    echo "-- Installing dependencies for cppcheck..."
    apt_install "libpcre3" "libpcre3-dev"
    echo "-- Installing dependencies for cppcheck done"

    mkdir cppcheck -p

    # Download archive
    echo "-- Downloading cppcheck..."
    retry wget --no-check-certificate -O - "https://github.com/danmar/cppcheck/archive/$1.tar.gz" | tar --strip-components=1 -xz -C cppcheck
    echo "-- Downloading cppcheck done"

    # Build CppCheck
    echo "-- Building cppcheck..."
    cd cppcheck || exit

    mkdir build -p
    cd build || exit

    cmake .. -DCMAKE_BUILD_TYPE:STRING="Release" -DUSE_MATCHCOMPILER:BOOL=On -DHAVE_RULES:BOOL=ON -DCMAKE_CXX_FLAGS:STRING="$cmake_build_flags"
    cmake --build . "-j$(nproc)"
    echo "-- Building cppcheck done"

    # Install CppCheck
    echo "-- Installing cppcheck..."
    sudo make install
    echo "-- Installing cppcheck done"

    # Verify
    echo "-- Verifying cppcheck..."
    which cppcheck
    cppcheck --version
    echo "-- Verifiying cppcheck done"

    # Export values
    echo "CPPCHECK=cppcheck" >>"$GITHUB_ENV"
    echo "CPPCHECK_VERSION=$1" >>"$GITHUB_ENV"

    cd "$root_dir" || exit
}

# Expects first parameter to the requested version
install_clang_tidy() {
    add_llvm_apt "$1"

    echo "-- Installing clang-tidy-$1..."
    apt_install "clang-tidy-$1"

    # Verify
    echo "-- Verifying clang-tidy-$1..."
    which "clang-tidy-$1"
    "clang-tidy-$1" --version
    echo "-- Verifiying clang-tidy-$1 done"

    # Export values
    echo "CLANG_TIDY=clang-tidy-$1" >>"$GITHUB_ENV"
    echo "CLANG_TIDY_VERSION=$1" >>"$GITHUB_ENV"

    echo "-- Installing clang-tidy-$1 done"
}

install_llvm() {
    add_llvm_apt "$1"

    # Make sure we also install clang
    install_clang "$1"

    echo "-- Installing llvm-$1..."
    apt_install "llvm-$1" "llvm-$1-dev"

    # Export values
    echo "LLVM_VERSION=$1" >>"$GITHUB_ENV"

    echo "-- Installing llvm-$1 done"
}

install_iwyu() {
    # Install the appropriate llvm version
    install_llvm "$1"

    echo "-- Cloning iwyu..."
    retry git clone https://github.com/include-what-you-use/include-what-you-use.git
    echo "-- Cloning iwyu done"

    # Checkout branch
    cd "include-what-you-use" || exit
    git checkout "clang_$1"

    echo "-- Building iwyu..."
    mkdir build -p
    cd build || exit

    cmake .. -DCMAKE_PREFIX_PATH:STRING="/usr/lib/llvm-$1" -DCMAKE_BUILD_TYPE:STRING="Release" -DCMAKE_CXX_FLAGS:STRING="$cmake_build_flags"
    cmake --build . "-j$(nproc)"
    echo "-- Building iwyu done"

    # Install
    echo "-- Installing iwyu..."
    sudo make install
    echo "-- Installing iwyu done"

    # Verify
    echo "-- Verifying iwyu..."
    which include-what-you-use
    include-what-you-use --version

    which iwyu_tool.py
    iwyu_tool.py -h
    echo "-- Verifying iwyu done"

    # Export values
    echo "IWYU_VERSION=$1" >>"$GITHUB_ENV"

    cd "$root_dir" || exit
}

install_pvs_studio() {
    # Get gpg key
    echo "-- Adding viva64 repo..."
    retry wget -q -O - https://files.viva64.com/etc/pubkey.txt | sudo apt-key add
    retry sudo wget -O /etc/apt/sources.list.d/viva64.list https://files.viva64.com/etc/viva64.list
    echo "-- Adding viva64 repo done"

    # Udpate repo list
    retry sudo apt-get update

    echo "-- Installing pvs-studio..."
    apt_install pvs-studio
    echo "-- Installing pvs-studio done"

    # Verify
    echo "-- Verifying pvs-studio..."
    # NOTE pvs-studio doens't support a --version flag so we use which
    which pvs-studio-analyzer
    echo "-- Verifying pvs-studio done"
}

install_mull() {
    echo "-- Setting up mull-$1..."
    # https://mull.readthedocs.io/en/latest/Installation.html#install-on-ubuntu
    retry curl -1sLf 'https://dl.cloudsmith.io/public/mull-project/mull-stable/setup.deb.sh' | sudo -E bash

    # Update repo list
    retry sudo apt-get update

    echo "-- Setting up mull-$1 done"

    echo "-- Installing mull-$1..."
    apt_install "mull-$1"
    echo "-- Installing mull-$1 done"

    # Verify
    echo "-- Verifying mull-$1..."
    which "mull-runner-$1"
    "mull-runner-$1" --version
    echo "-- Verifying mull-$1 done"

    # Export values
    echo "MULL_RUNNER=mull-runner-$1" >>"$GITHUB_ENV"
}

install_clang_format() {
    add_llvm_apt "$1"

    echo "-- Installing clang-format..."
    apt_install "clang-format-$1"
    echo "-- Installing clang-format done"

    # Verify
    echo "-- Verifying clang-format-$1..."
    which "clang-format-$1"
    "clang-format-$1" --version
    echo "-- Verifying clang-format-$1 done"

    # Export values
    echo "CLANG_FORMAT=clang-format-$1" >>"$GITHUB_ENV"
    echo "CLANG_FORMAT_VERSION=$1" >>"$GITHUB_ENV"
}

install_ninja() {
    echo "-- Installing ninja..."
    apt_install ninja-build
    echo "-- Installing ninja done"

    # Verify
    echo "-- Verifying ninja..."
    which ninja
    ninja --version
    echo "-- Verifying ninja done"
}

# Check is sudo command exists and try to install it otherwise
if ! command -v sudo /dev/null; then
    echo "No sudo found, probably ran inside a docker container"

    apt update

    # NOTE: We can't use the the 'apt_install' function since it uses the 'sudo' command
    retry apt install sudo -y --no-install-recommends
fi

# Ensure required packages are installed (mostly for running inside a docker container)
echo "- Ensuring required packages are installed..."
apt_install wget gnupg lsb-release software-properties-common pip
echo "- Ensuring required packages are installed done"

for tool in "$@"; do
    if [[ "$tool" == "gcovr" ]]; then
        install_gcovr
    elif [[ "$tool" == "cmake-format" ]]; then
        install_cmake_format
    elif [[ "$tool" == gcc-* ]]; then
        install_gcc "${tool:4}"
    elif [[ "$tool" == "valgrind" ]]; then
        install_valgrind
    elif [[ "$tool" == cppcheck-* ]]; then
        install_cppcheck "${tool:9}"
    elif [[ "$tool" == clang-tidy-* ]]; then
        install_clang_tidy "${tool:11}"
    elif [[ "$tool" == clang-format-* ]]; then
        install_clang_format "${tool:13}"
    elif [[ "$tool" == llvm-* ]]; then
        install_llvm "${tool:5}"
    elif [[ "$tool" == clang-* ]]; then
        install_clang "${tool:6}"
    elif [[ "$tool" == iwyu-* ]]; then
        install_iwyu "${tool:5}"
    elif [[ "$tool" == pvs-studio ]]; then
        install_pvs_studio
    elif [[ "$tool" == mull-* ]]; then
        install_mull "${tool:5}"
    elif [[ "$tool" == ninja ]]; then
        install_ninja
    else
        echo "!- Unknown tool '$tool'"
        exit 1
    fi
done
