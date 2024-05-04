#include "SetupRuntimeFailure.hpp"

#include <phi/algorithm/at.hpp>
#include <phi/compiler_support/warning.hpp>
#include <initializer_list>

PHI_GCC_SUPPRESS_WARNING("-Wunused-result")

int main()
{
    SetupRuntimeFailure();

    std::initializer_list<int> list{0, 1};

    (void)phi::at(list, 3u);
}
