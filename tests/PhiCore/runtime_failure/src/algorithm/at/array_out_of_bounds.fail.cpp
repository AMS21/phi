#include "SetupRuntimeFailure.hpp"

#include <phi/algorithm/at.hpp>
#include <phi/compiler_support/warning.hpp>
#include <phi/container/array.hpp>

PHI_GCC_SUPPRESS_WARNING("-Wunused-result")

int main()
{
    SetupRuntimeFailure();

    phi::array<int, 2u> arr{0, 1};

    (void)phi::at(arr, 3u);
}
