#include "SetupRuntimeFailure.hpp"

#include <phi/compiler_support/warning.hpp>
#include <phi/core/narrow_cast.hpp>
#include <phi/core/sized_types.hpp>

PHI_GCC_SUPPRESS_WARNING("-Wunused-result")

int main()
{
    SetupRuntimeFailure();

    phi::int32_t large = -1;
    // Unsigned types cannot hold negative values at all
    (void)phi::narrow_cast<phi::uint8_t>(large);
}
