#include "SetupRuntimeFailure.hpp"

#include <phi/algorithm/at.hpp>
#include <phi/compiler_support/warning.hpp>
#include <vector>

PHI_GCC_SUPPRESS_WARNING("-Wunused-result")

int main()
{
    SetupRuntimeFailure();

    std::vector<int> vec{0, 1};

    (void)phi::at(vec, 12u);
}
