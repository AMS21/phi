#include "SetupRuntimeFailure.hpp"

#include <phi/algorithm/string_compare_unsafe.hpp>
#include <phi/compiler_support/warning.hpp>

PHI_GCC_SUPPRESS_WARNING("-Wunused-result")

int main()
{
    SetupRuntimeFailure();

    const char* ptr = nullptr;

    (void)phi::string_compare_unsafe(ptr, "Test", 3u);
}
