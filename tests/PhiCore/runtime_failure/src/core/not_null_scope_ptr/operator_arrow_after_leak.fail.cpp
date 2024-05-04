#include "SetupRuntimeFailure.hpp"

#include <phi/compiler_support/warning.hpp>
#include <phi/core/scope_ptr.hpp>

PHI_GCC_SUPPRESS_WARNING("-Wunused-result")

struct A
{
    void test()
    {}
};

int main()
{
    SetupRuntimeFailure();

    phi::not_null_scope_ptr<A> ptr{new A()};

    ptr->test();

    (void)ptr.leak_ptr();
    ptr->test();
}
