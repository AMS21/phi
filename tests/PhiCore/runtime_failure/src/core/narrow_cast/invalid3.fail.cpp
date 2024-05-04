#include "SetupRuntimeFailure.hpp"

#include <phi/compiler_support/warning.hpp>
#include <phi/core/narrow_cast.hpp>
#include <phi/core/sized_types.hpp>

PHI_GCC_SUPPRESS_WARNING("-Wunused-result")

int main()
{
    SetupRuntimeFailure();

    phi::int16_t large = -500;
    // -500 is too large to be represented in an int8_t
    (void)phi::narrow_cast<phi::int8_t>(large);
}
