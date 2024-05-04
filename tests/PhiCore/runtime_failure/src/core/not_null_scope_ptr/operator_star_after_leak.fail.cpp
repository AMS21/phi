#include "SetupRuntimeFailure.hpp"

#include <phi/compiler_support/warning.hpp>
#include <phi/core/scope_ptr.hpp>

PHI_GCC_SUPPRESS_WARNING("-Wunused-result")

int main()
{
    SetupRuntimeFailure();

    phi::not_null_scope_ptr<int> ptr{new int(3)};
    (void)ptr.leak_ptr();

    *ptr;
}
