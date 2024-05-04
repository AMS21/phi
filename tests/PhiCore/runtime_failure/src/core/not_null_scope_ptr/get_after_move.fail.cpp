#include "SetupRuntimeFailure.hpp"

#include <phi/compiler_support/warning.hpp>
#include <phi/core/move.hpp>
#include <phi/core/scope_ptr.hpp>

PHI_GCC_SUPPRESS_WARNING("-Wunused-result")

int main()
{
    SetupRuntimeFailure();

    phi::not_null_scope_ptr<int> ptr1(new int(3));
    phi::not_null_scope_ptr<int> ptr2(phi::move(ptr1));

    // NOLINTNEXTLINE(clang-analyzer-cplusplus.Move)
    (void)ptr1.get();
}
