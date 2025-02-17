#include <phi/test/test_macros.hpp>

#include <phi/compiler_support/constexpr.hpp>
#include <phi/compiler_support/unused.hpp>
#include <phi/type_traits/is_corresponding_member.hpp>
#include <type_traits>

template <typename LhsT, typename RhsT, typename LhsMemberT, typename RhsMemberT>
PHI_EXTENDED_CONSTEXPR void test_is_corresponding_member(LhsMemberT LhsT::* lhs,
                                                         RhsMemberT RhsT::* rhs) noexcept
{
#if PHI_HAS_WORKING_IS_CORRESPONDING_MEMBER()
    STATIC_REQUIRE(phi::is_corresponding_member(lhs, rhs));
    CHECK_NOEXCEPT(phi::is_corresponding_member(lhs, rhs));

    // Standard compatibility
    STATIC_REQUIRE(std::is_corresponding_member(lhs, rhs));
#else
    PHI_UNUSED_PARAMETER(lhs);
    PHI_UNUSED_PARAMETER(rhs);
#endif
}

template <typename LhsT, typename RhsT, typename LhsMemberT, typename RhsMemberT>
PHI_EXTENDED_CONSTEXPR void test_is_not_corresponding_member(LhsMemberT LhsT::* lhs,
                                                             RhsMemberT RhsT::* rhs) noexcept
{
#if PHI_HAS_WORKING_IS_CORRESPONDING_MEMBER()
    STATIC_REQUIRE_FALSE(phi::is_corresponding_member(lhs, rhs));
    CHECK_NOEXCEPT(!phi::is_corresponding_member(lhs, rhs));

    // Standard compatibility
    STATIC_REQUIRE_FALSE(std::is_corresponding_member(lhs, rhs));
#else
    PHI_UNUSED_PARAMETER(lhs);
    PHI_UNUSED_PARAMETER(rhs);
#endif
}

struct A
{
    int a;
};

struct B
{
    int b;
};

struct C : public A, public B
{}; // not a standard-layout class

struct Foo
{
    int x;
};

struct Bar
{
    int    y;
    double z;
};

struct Baz : Foo, Bar
{}; // not standard-layout

TEST_CASE("is_corresponding_member")
{
    // TODO: This doesn't work like that
#if 0
    // Succeeds because arguments have types int A::* and int B::*
    test_is_corresponding_member(&C::a, &C::b);

    PHI_CONSTEXPR int C::*a = &C::a;
    PHI_CONSTEXPR int C::*b = &C::b;
    test_is_not_corresponding_member(a, b);
    // Not corresponding members, because arguments both have type int C::*

    test_is_corresponding_member(&Foo::x, &Bar::y);
    test_is_corresponding_member(&Baz::x, &Baz::y);
    test_is_not_corresponding_member<Baz, Baz, int, int>(&Baz::x, &Baz::y);
#endif
}
