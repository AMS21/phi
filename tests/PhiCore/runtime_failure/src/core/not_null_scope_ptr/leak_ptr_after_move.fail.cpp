#include "SetupRuntimeFailure.hpp"

#include <phi/compiler_support/warning.hpp>
#include <phi/core/move.hpp>
#include <phi/core/scope_ptr.hpp>

PHI_GCC_SUPPRESS_WARNING("-Wunused-result")

int main()
{
    SetupRuntimeFailure();

    phi::not_null_scope_ptr<int> ptr(new int(3));
    phi::not_null_scope_ptr<int> moved_to_ptr{phi::move(ptr)};

    (void)ptr.leak_ptr();
}
