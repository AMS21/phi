#include "SetupRuntimeFailure.hpp"

#include <phi/algorithm/at.hpp>
#include <phi/compiler_support/warning.hpp>

PHI_GCC_SUPPRESS_WARNING("-Wunused-result")

int main()
{
    SetupRuntimeFailure();

    char arr[]{"abc"};

    (void)phi::at(arr, 5u);
}
