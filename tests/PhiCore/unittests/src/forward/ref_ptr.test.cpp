#include <phi/test/test_macros.hpp>

#include <phi/compiler_support/warning.hpp>
#include <phi/forward/ref_ptr.hpp>

PHI_GCC_SUPPRESS_WARNING("-Wunused-result")

TEST_CASE("forward.ref_ptr.forward")
{
    phi::ref_ptr<int>*          ptr  = nullptr;
    phi::not_null_ref_ptr<int>* ptr2 = nullptr;

    CHECK(ptr == nullptr);
    CHECK(ptr2 == nullptr);
}

#include <phi/core/ref_ptr.hpp>

TEST_CASE("forward.ref_ptr")
{
    phi::ref_ptr<int>          ptr  = nullptr;
    phi::not_null_ref_ptr<int> ptr2 = new int(42);

    CHECK(ptr.get() == nullptr);
    CHECK(ptr2.get() != nullptr);
}
