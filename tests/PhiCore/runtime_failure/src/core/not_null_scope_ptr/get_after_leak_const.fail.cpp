#include "SetupRuntimeFailure.hpp"

#include <phi/compiler_support/warning.hpp>
#include <phi/core/scope_ptr.hpp>

PHI_GCC_SUPPRESS_WARNING("-Wunused-result")

int main()
{
    SetupRuntimeFailure();

    const phi::not_null_scope_ptr<int> ptr(new int(3));

    // NOTE: Ugly hack around the language and compiler preventing us from doing something stupid
    (void)const_cast<phi::not_null_scope_ptr<int>*>(&ptr)->leak_ptr();

    (void)ptr.get();
}
