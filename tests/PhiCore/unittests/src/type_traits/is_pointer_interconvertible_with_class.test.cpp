#include <phi/test/test_macros.hpp>

#include <phi/compiler_support/constexpr.hpp>
#include <phi/compiler_support/unused.hpp>
#include <phi/type_traits/is_pointer_interconvertible_with_class.hpp>
#include <type_traits>

template <typename TypeT, typename MemberT>
PHI_EXTENDED_CONSTEXPR void test_is_pointer_interconvertible_with_class(
        MemberT TypeT::* member_pointer)
{
    PHI_UNUSED_PARAMETER(member_pointer);
#if PHI_HAS_WORKING_IS_POINTER_INTERCONVERTIBLE_WITH_CLASS()
    STATIC_REQUIRE(phi::is_pointer_interconvertible_with_class(member_pointer));
    CHECK_NOEXCEPT(phi::is_pointer_interconvertible_with_class(member_pointer));

    // Standard compatibility
    STATIC_REQUIRE(std::is_pointer_interconvertible_with_class(member_pointer));
#endif
}

template <typename TypeT, typename MemberT>
PHI_EXTENDED_CONSTEXPR void test_is_not_pointer_interconvertible_with_class(
        MemberT TypeT::* member_pointer)
{
    PHI_UNUSED_PARAMETER(member_pointer);
#if PHI_HAS_WORKING_IS_POINTER_INTERCONVERTIBLE_WITH_CLASS()
    STATIC_REQUIRE_FALSE(phi::is_pointer_interconvertible_with_class(member_pointer));
    CHECK_NOEXCEPT(phi::is_pointer_interconvertible_with_class(member_pointer));

    // Standard compatibility
    STATIC_REQUIRE_FALSE(std::is_pointer_interconvertible_with_class(member_pointer));
#endif
}

struct A
{
    int  i;
    long l;
};

struct B
{
    const int i;
};

struct C
{
    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    int f()
    {
        return 21;
    }
};

struct D : A
{};

struct E : A
{
    int j;
};

struct Foo
{
    int x;
};
struct Bar
{
    int y;
};

struct Baz : Foo, Bar
{}; // not standard-layout

TEST_CASE("is_pointer_interconvertible_with_class")
{
    // TODO: Fix test implementation
#if 0
    test_is_pointer_interconvertible_with_class(&A::i);
    test_is_pointer_interconvertible_with_class(&A::l);

    PHI_CONSTEXPR int A::*a = nullptr;
    test_is_not_pointer_interconvertible_with_class(a);

    test_is_pointer_interconvertible_with_class(&B::i);

    test_is_not_pointer_interconvertible_with_class(&C::f);

    test_is_pointer_interconvertible_with_class(&D::i);

    // This works because the type of &E::i is int A::* and A is standard-layout:
    test_is_pointer_interconvertible_with_class(&E::i);

    PHI_CONSTEXPR int E::*e = a;
    // This fails because E is not standard-layout:
    test_is_not_pointer_interconvertible_with_class(e);
    test_is_not_pointer_interconvertible_with_class(&E::j);

    test_is_pointer_interconvertible_with_class(&Baz::x);
    test_is_not_pointer_interconvertible_with_class<Baz, int>(&Baz::x);
#endif
}
