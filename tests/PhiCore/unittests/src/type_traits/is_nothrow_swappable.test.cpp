#include <phi/test/test_macros.hpp>

#include "type_traits_helper.hpp"
#include <phi/compiler_support/noexcept.hpp>
#include <phi/compiler_support/warning.hpp>
#include <type_traits>

PHI_GCC_SUPPRESS_WARNING_PUSH()
PHI_GCC_SUPPRESS_WARNING("-Wnoexcept")

#include <phi/algorithm/swap.hpp>
#include <phi/type_traits/is_nothrow_swappable.hpp>
#include <phi/type_traits/is_swappable.hpp>

namespace my_ns
{
    // Make the test types non-copyable so that generic swap is not valid.
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

    void swap(A&, A&) PHI_NOEXCEPT;

    void swap(B&, B&);

    struct M
    {
        M(M const&)            = delete;
        M& operator=(M const&) = delete;
    };

    void swap(M&&, M&&) PHI_NOEXCEPT;

    struct ThrowingMove
    {
        ThrowingMove(ThrowingMove&&);

        ThrowingMove& operator=(ThrowingMove&&);
    };

} // namespace my_ns

template <typename TypeT>
void test_is_nothrow_swappable()
{
    STATIC_REQUIRE(phi::is_nothrow_swappable<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_nothrow_swappable<TypeT>::value);
    STATIC_REQUIRE(phi::is_swappable<TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_nothrow_swappable_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_not_nothrow_swappable_v<TypeT>);
    STATIC_REQUIRE(phi::is_swappable_v<TypeT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_nothrow_swappable<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_nothrow_swappable<TypeT>);

    // Standard compatibility
#if PHI_CPP_STANDARD_IS_ATLEAST(17) && PHI_COMPILER_WORKAROUND(GCC, 7, 0, 0)
    STATIC_REQUIRE(std::is_nothrow_swappable<TypeT>::value);
    STATIC_REQUIRE(std::is_swappable<TypeT>::value);
#endif
}

template <typename TypeT>
void test_is_not_nothrow_swappable()
{
    STATIC_REQUIRE_FALSE(phi::is_nothrow_swappable<TypeT>::value);
    STATIC_REQUIRE(phi::is_not_nothrow_swappable<TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_nothrow_swappable_v<TypeT>);
    STATIC_REQUIRE(phi::is_not_nothrow_swappable_v<TypeT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_nothrow_swappable<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_nothrow_swappable<TypeT>);

    // Standard compatibility
#if PHI_CPP_STANDARD_IS_ATLEAST(17) && PHI_COMPILER_WORKAROUND(GCC, 7, 0, 0)
    STATIC_REQUIRE_FALSE(std::is_nothrow_swappable<TypeT>::value);
#endif
}

TEST_CASE("is_nothrow_swappable")
{
    using namespace my_ns;

    // Test that is_swappable applies an lvalue reference to the type.
    test_is_nothrow_swappable<int>();
    test_is_nothrow_swappable<int&>();
    test_is_not_nothrow_swappable<M>();
    test_is_not_nothrow_swappable<M&&>();

    // Test that it correctly deduces the noexcept of swap.
    test_is_nothrow_swappable<A>();
    test_is_not_nothrow_swappable<B>();
    STATIC_REQUIRE(phi::is_swappable<B>::value);
    test_is_not_nothrow_swappable<ThrowingMove>();
    STATIC_REQUIRE(phi::is_swappable<ThrowingMove>::value);

    // Test that it doesn't drop the qualifiers
    test_is_not_nothrow_swappable<const A>();

    // test non-referenceable types
    test_is_not_nothrow_swappable<void>();
    test_is_not_nothrow_swappable<const void>();
    test_is_not_nothrow_swappable<volatile void>();
    test_is_not_nothrow_swappable<const volatile void>();
    test_is_not_nothrow_swappable<int() const>();
    test_is_not_nothrow_swappable<int(int, ...) const&>();
}

PHI_GCC_SUPPRESS_WARNING_POP()
