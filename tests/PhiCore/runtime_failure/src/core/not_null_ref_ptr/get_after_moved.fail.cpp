#include "SetupRuntimeFailure.hpp"

#include <phi/compiler_support/warning.hpp>
#include <phi/core/ref_ptr.hpp>

PHI_GCC_SUPPRESS_WARNING("-Wunused-result")

int main()
{
    SetupRuntimeFailure();

    phi::not_null_ref_ptr<int> ptr{new int(21)};
    phi::not_null_ref_ptr<int> ptr2{phi::move(ptr)};

    (void)ptr.get();
}
