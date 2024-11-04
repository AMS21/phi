#!/usr/bin/env bash

# shellcheck disable=SC2015

set -e
set -u

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

# Determine OS
case "$(uname -sr)" in

Darwin*)
    echo "Environment: Mac OS X"
    machine=mac
    ;;

Linux*)
    echo "Environment: Linux"
    machine=linux
    ;;

CYGWIN* | MINGW* | MSYS*)
    echo "Environment: Windows"
    machine=windows
    ;;

*)
    echo "Error: Unknown OS"
    exit
    ;;
esac

# Determine number of processors
if [[ $machine == "mac" ]]; then
    PROC_COUNT=$(sysctl -n hw.logicalcpu)
elif [[ $machine == "linux" ]]; then
    PROC_COUNT=$(nproc)
elif [[ $machine == "windows" ]]; then
    PROC_COUNT=$NUMBER_OF_PROCESSORS
fi

# Get number of processors available
# shellcheck disable=SC2129
echo "PROC_COUNT=$PROC_COUNT" >>"$GITHUB_ENV"

# Setup CMake stuff
# https://cmake.org/cmake/help/latest/envvar/CMAKE_BUILD_PARALLEL_LEVEL.html
echo "CMAKE_BUILD_PARALLEL_LEVEL=${PROC_COUNT}" >>"$GITHUB_ENV"
# https://cmake.org/cmake/help/latest/envvar/CTEST_PARALLEL_LEVEL.html
echo "CTEST_PARALLEL_LEVEL=${PROC_COUNT}" >>"$GITHUB_ENV"
# https://cmake.org/cmake/help/latest/envvar/CTEST_OUTPUT_ON_FAILURE.html
echo "CTEST_OUTPUT_ON_FAILURE=ON" >>"$GITHUB_ENV"
# https://cmake.org/cmake/help/latest/variable/CMAKE_GENERATOR.html
echo "CMAKE_GENERATOR=Ninja" >>"$GITHUB_ENV"

# Set some default options
# https://cmake.org/cmake/help/latest/envvar/CMAKE_EXPORT_COMPILE_COMMANDS.html
echo "CMAKE_EXPORT_COMPILE_COMMANDS=ON" >>"$GITHUB_ENV"
# https://cmake.org/cmake/help/latest/envvar/VERBOSE.html
echo "VERBOSE=ON" >>"$GITHUB_ENV"

# Set sanitizer runtime flags
# https://github.com/google/sanitizers/wiki/SanitizerCommonFlags
# https://github.com/google/sanitizers/wiki/AddressSanitizerFlags#run-time-flags
# https://clang.llvm.org/docs/AddressSanitizer.html
if [[ $machine == "linux" ]]; then
    # 'detect_leaks' is not really supported on Linux
    echo "ASAN_OPTIONS=quarantine_size_mb=1024:redzone=256:strict_string_checks=1:detect_odr_violation=2:detect_stack_use_after_return=1:check_initialization_order=1:detect_leaks=1:print_stats=1:use_odr_indicator=1:strict_memcmp=1:print_scariness=1:handle_abort=1:symbolize=1:handle_segv=1:handle_sigill=1:allocator_release_to_os_interval_ms=500:handle_sigfpe=1:handle_sigbus=1:alloc_dealloc_mismatch=1:check_malloc_usable_size=1:abort_on_error=1" >>"$GITHUB_ENV"
else
    echo "ASAN_OPTIONS=quarantine_size_mb=1024:redzone=256:strict_string_checks=1:detect_odr_violation=2:detect_stack_use_after_return=1:check_initialization_order=1:print_stats=1:use_odr_indicator=1:strict_memcmp=1:print_scariness=1:handle_abort=1:symbolize=1:handle_segv=1:handle_sigill=1:allocator_release_to_os_interval_ms=500:handle_sigfpe=1:handle_sigbus=1:alloc_dealloc_mismatch=1:check_malloc_usable_size=1:abort_on_error=1" >>"$GITHUB_ENV"
fi
# https://github.com/google/sanitizers/wiki/AddressSanitizerLeakSanitizer#flags
# https://clang.llvm.org/docs/LeakSanitizer.html
echo "LSAN_OPTIONS=report_objects=1:use_unaligned=1:max_leaks=0" >>"$GITHUB_ENV"
# https://github.com/google/sanitizers/wiki/MemorySanitizer
# https://clang.llvm.org/docs/MemorySanitizer.html
echo "MSAN_OPTIONS=poison_in_dtor=1" >>"$GITHUB_ENV"
# https://github.com/google/sanitizers/wiki/ThreadSanitizerFlags#runtime-flags
# https://clang.llvm.org/docs/ThreadSanitizer.html
echo "TSAN_OPTIONS=halt_on_error=1:history_size=3:force_seq_cst_atomics=1" >>"$GITHUB_ENV"
# https://clang.llvm.org/docs/UndefinedBehaviorSanitizer.html
echo "UBSAN_OPTIONS=print_stacktrace=1:report_error_type=1:halt_on_error=1" >>"$GITHUB_ENV"

# Latest versions
echo "LATEST_LLVM_VERSION=19" >>"$GITHUB_ENV"
echo "LATEST_GCC_VERSION=14" >>"$GITHUB_ENV"

if [[ $machine == "linux" ]]; then
    # Workaround for the unreliable Github Actions caching proxy
    printf 'http://azure.archive.ubuntu.com/ubuntu\tpriority:1\n' | sudo tee /etc/apt/mirrors.txt
    curl http://mirrors.ubuntu.com/mirrors.txt | sudo tee --append /etc/apt/mirrors.txt
    sudo sed -i 's~http://azure.archive.ubuntu.com/ubuntu/~mirror+file:/etc/apt/mirrors.txt~' /etc/apt/sources.list

    # Update sources
    retry sudo apt-get update && sudo apt-get clean
fi
