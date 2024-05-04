#include "SetupRuntimeFailure.hpp"

#include <phi/compiler_support/warning.hpp>
#include <phi/core/scope_ptr.hpp>

PHI_GCC_SUPPRESS_WARNING("-Wunused-result")

struct A
{
    void test() const
    {}
};

int main()
{
    SetupRuntimeFailure();

    const phi::not_null_scope_ptr<A> ptr{new A()};

    ptr->test();

    // NOTE: Ugly hack around the language and compiler preventing us from doing something stupid
    (void)const_cast<phi::not_null_scope_ptr<A>*>(&ptr)->leak_ptr();
    ptr->test();
}
