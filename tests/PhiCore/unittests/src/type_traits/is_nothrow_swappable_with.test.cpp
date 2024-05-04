#include <phi/test/test_macros.hpp>

#include "type_traits_helper.hpp"
#include <phi/compiler_support/noexcept.hpp>
#include <phi/compiler_support/warning.hpp>
#include <type_traits>

PHI_GCC_SUPPRESS_WARNING_PUSH()
PHI_GCC_SUPPRESS_WARNING("-Wnoexcept")

#include <phi/algorithm/swap.hpp>
#include <phi/type_traits/is_nothrow_swappable_with.hpp>
#include <phi/type_traits/is_swappable_with.hpp>

namespace is_nothrow_swappable_with_ns
{
    struct A
    {
        A(A const&)            = delete;
        A& operator=(A const&) = delete;
    };

    struct B
    {
        B(B const&)            = delete;
        B& operator=(B const&) = delete;
    };

    struct C
    {};
    struct D
    {};

    void swap(A&, A&);

    void swap(A&, B&) PHI_NOEXCEPT;
    void swap(B&, A&) PHI_NOEXCEPT;

    void swap(A&, C&) PHI_NOEXCEPT;
    void swap(C&, A&);

    struct M
    {};

    void swap(M&&, M&&) PHI_NOEXCEPT;

} // namespace is_nothrow_swappable_with_ns

template <typename LhsT, typename RhsT>
void test_is_nothrow_swappable_with()
{
    STATIC_REQUIRE(phi::is_nothrow_swappable_with<LhsT, RhsT>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_nothrow_swappable_with<LhsT, RhsT>::value);
    STATIC_REQUIRE(phi::is_swappable_with<LhsT, RhsT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_nothrow_swappable_with_v<LhsT, RhsT>);
    STATIC_REQUIRE_FALSE(phi::is_not_nothrow_swappable_with_v<LhsT, RhsT>);
    STATIC_REQUIRE(phi::is_swappable_with_v<LhsT, RhsT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_nothrow_swappable_with<LhsT, RhsT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_nothrow_swappable_with<LhsT, RhsT>);

    // Standard compatibility
#if PHI_CPP_STANDARD_IS_ATLEAST(17) && PHI_COMPILER_WORKAROUND(GCC, 7, 0, 0)
    STATIC_REQUIRE(std::is_nothrow_swappable_with<LhsT, RhsT>::value);
    STATIC_REQUIRE(std::is_swappable_with<LhsT, RhsT>::value);
#endif
}

template <typename LhsT, typename RhsT>
void test_is_not_nothrow_swappable_with()
{
    STATIC_REQUIRE_FALSE(phi::is_nothrow_swappable_with<LhsT, RhsT>::value);
    STATIC_REQUIRE(phi::is_not_nothrow_swappable_with<LhsT, RhsT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_nothrow_swappable_with_v<LhsT, RhsT>);
    STATIC_REQUIRE(phi::is_not_nothrow_swappable_with_v<LhsT, RhsT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_nothrow_swappable_with<LhsT, RhsT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_nothrow_swappable_with<LhsT, RhsT>);

    // Standard compatibility
#if PHI_CPP_STANDARD_IS_ATLEAST(17) && PHI_COMPILER_WORKAROUND(GCC, 7, 0, 0)
    STATIC_REQUIRE_FALSE(std::is_nothrow_swappable_with<LhsT, RhsT>::value);
#endif
}

TEST_CASE("is_nothrow_swappable_with")
{
    using namespace is_nothrow_swappable_with_ns;

    test_is_nothrow_swappable_with<int&, int&>();
    test_is_not_nothrow_swappable_with<int&&, int&&>();

    {
        // Test that is_swappable_with doesn't apply an lvalue reference
        // to the type. Instead it is up to the user.
        test_is_not_nothrow_swappable_with<int, int>();
        test_is_nothrow_swappable_with<int&, int&>();
        test_is_nothrow_swappable_with<M, M>();
        STATIC_REQUIRE(phi::is_swappable_with<A&, A&>::value);
        test_is_not_nothrow_swappable_with<A&, A&>();
    }
    {
        // test that heterogeneous swap is allowed only if both 'swap(A, B)' and
        // 'swap(B, A)' are valid.
        test_is_nothrow_swappable_with<A&, B&>();
        STATIC_REQUIRE(phi::is_swappable_with<A&, C&>::value);
        test_is_not_nothrow_swappable_with<A&, C&>();
        test_is_not_nothrow_swappable_with<D&, C&>();
    }
    {
        // test we guard against cv void inputs as required.
        test_is_not_nothrow_swappable_with<void, int>();
        test_is_not_nothrow_swappable_with<int, void>();

        test_is_not_nothrow_swappable_with<void, void>();
        test_is_not_nothrow_swappable_with<void, const void>();
        test_is_not_nothrow_swappable_with<void, volatile void>();
        test_is_not_nothrow_swappable_with<void, const volatile void>();

        test_is_not_nothrow_swappable_with<const void, void>();
        test_is_not_nothrow_swappable_with<const void, const void>();
        test_is_not_nothrow_swappable_with<const void, volatile void>();
        test_is_not_nothrow_swappable_with<const void, const volatile void>();

        test_is_not_nothrow_swappable_with<volatile void, void>();
        test_is_not_nothrow_swappable_with<volatile void, const void>();
        test_is_not_nothrow_swappable_with<volatile void, volatile void>();
        test_is_not_nothrow_swappable_with<volatile void, const volatile void>();

        test_is_not_nothrow_swappable_with<const volatile void, void>();
        test_is_not_nothrow_swappable_with<const volatile void, const void>();
        test_is_not_nothrow_swappable_with<const volatile void, volatile void>();
        test_is_not_nothrow_swappable_with<const volatile void, const volatile void>();
    }
}

PHI_GCC_SUPPRESS_WARNING_POP()
