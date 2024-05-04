#include "SetupRuntimeFailure.hpp"

#include <phi/compiler_support/warning.hpp>
#include <phi/container/array.hpp>

PHI_GCC_SUPPRESS_WARNING("-Wunused-result")

int main()
{
    SetupRuntimeFailure();

    const phi::array<int, 0u> arr{};
    (void)arr.front();
}
