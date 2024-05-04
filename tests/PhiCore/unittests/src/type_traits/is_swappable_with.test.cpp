#include <phi/test/test_macros.hpp>

#include "type_traits_helper.hpp"
#include <phi/algorithm/swap.hpp>
#include <phi/compiler_support/cpp_standard.hpp>
#include <phi/type_traits/is_swappable_with.hpp>
#include <type_traits>

template <typename TypeT, typename OtherT>
void test_is_swappable_with()
{
    STATIC_REQUIRE(phi::is_swappable_with<TypeT, OtherT>::value);
    STATIC_REQUIRE(phi::is_swappable_with<OtherT, TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_swappable_with<TypeT, OtherT>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_swappable_with<OtherT, TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_swappable_with_v<TypeT, OtherT>);
    STATIC_REQUIRE(phi::is_swappable_with_v<OtherT, TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_not_swappable_with_v<TypeT, OtherT>);
    STATIC_REQUIRE_FALSE(phi::is_not_swappable_with_v<OtherT, TypeT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_swappable_with<TypeT, OtherT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_swappable_with<OtherT, TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_swappable_with<TypeT, OtherT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_swappable_with<OtherT, TypeT>);

#if PHI_CPP_STANDARD_IS_ATLEAST(17) && PHI_COMPILER_WORKAROUND(GCC, 7, 0, 0)
    STATIC_REQUIRE(std::is_swappable_with<TypeT, OtherT>::value);
    STATIC_REQUIRE(std::is_swappable_with<OtherT, TypeT>::value);
#endif
}

template <typename TypeT, typename OtherT>
void test_is_not_swappable_with()
{
    STATIC_REQUIRE_FALSE(phi::is_swappable_with<TypeT, OtherT>::value);
    STATIC_REQUIRE_FALSE(phi::is_swappable_with<OtherT, TypeT>::value);
    STATIC_REQUIRE(phi::is_not_swappable_with<TypeT, OtherT>::value);
    STATIC_REQUIRE(phi::is_not_swappable_with<OtherT, TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_swappable_with_v<TypeT, OtherT>);
    STATIC_REQUIRE_FALSE(phi::is_swappable_with_v<OtherT, TypeT>);
    STATIC_REQUIRE(phi::is_not_swappable_with_v<TypeT, OtherT>);
    STATIC_REQUIRE(phi::is_not_swappable_with_v<OtherT, TypeT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_swappable_with<TypeT, OtherT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_swappable_with<OtherT, TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_swappable_with<TypeT, OtherT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_swappable_with<OtherT, TypeT>);

#if PHI_CPP_STANDARD_IS_ATLEAST(17) && PHI_COMPILER_WORKAROUND(GCC, 7, 0, 0)
    STATIC_REQUIRE_FALSE(std::is_swappable_with<TypeT, OtherT>::value);
    STATIC_REQUIRE_FALSE(std::is_swappable_with<OtherT, TypeT>::value);
#endif
}

namespace is_swappable_with_ns
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

    void swap(A&, B&);

    void swap(B&, A&);

    void swap(A&, C&);

    // missing swap(C, A)

    void swap(D&, C&);

    struct M
    {};

    void swap(M&&, M&&);

    struct T0
    {};

    void swap(T0, T0);

    struct T1
    {};
    struct T2
    {};

    void swap(T1, T2);
    void swap(T2, T1);

    struct BoolLike
    {};

    void swap(BoolLike, bool&);
    void swap(bool&, BoolLike);

    struct F
    {};

    void swap(F&, F&) = delete;
    void swap(F (&)[5], F (&)[5]);

    struct F0
    {};

    void swap(F0, F0) = delete;

    struct F1
    {};

    void swap(F0, F1) = delete;
    void swap(F1, F0) = delete;

    struct F2
    {};
    struct F3
    {};

    void swap(F2, F3);
    void swap(F3, F2) = delete;

    struct F4
    {
        friend void swap(F4, F4) = delete;
    };
} // namespace is_swappable_with_ns

TEST_CASE("is_swappable_with")
{
    using namespace is_swappable_with_ns;
    {
        // Test that is_swappable_with doesn't apply an lvalue reference
        // to the type. Instead it is up to the user.
        test_is_not_swappable_with<int, int>();
        test_is_swappable_with<int&, int&>();
        test_is_swappable_with<M, M>();
        test_is_swappable_with<A&, A&>();
    }
    {
        // test that heterogeneous swap is allowed only if both 'swap(A, B)' and
        // 'swap(B, A)' are valid.
        test_is_swappable_with<A&, B&>();
        test_is_not_swappable_with<A&, C&>();
        test_is_not_swappable_with<D&, C&>();
    }
    {
        // test that cv void is guarded against as required.
        test_is_not_swappable_with<void, int>();
        test_is_not_swappable_with<const void, int>();
        test_is_not_swappable_with<volatile void, int>();
        test_is_not_swappable_with<const volatile void, int>();

        test_is_not_swappable_with<int, void>();
        test_is_not_swappable_with<int, const void>();
        test_is_not_swappable_with<int, volatile void>();
        test_is_not_swappable_with<int, const volatile void>();

        test_is_not_swappable_with<void, void>();
        test_is_not_swappable_with<void, const void>();
        test_is_not_swappable_with<void, volatile void>();
        test_is_not_swappable_with<void, const volatile void>();
        test_is_not_swappable_with<const void, void>();
        test_is_not_swappable_with<const void, const void>();
        test_is_not_swappable_with<const void, volatile void>();
        test_is_not_swappable_with<const void, const volatile void>();
        test_is_not_swappable_with<volatile void, void>();
        test_is_not_swappable_with<volatile void, const void>();
        test_is_not_swappable_with<volatile void, volatile void>();
        test_is_not_swappable_with<volatile void, const volatile void>();
        test_is_not_swappable_with<const volatile void, void>();
        test_is_not_swappable_with<const volatile void, const void>();
        test_is_not_swappable_with<const volatile void, volatile void>();
        test_is_not_swappable_with<const volatile void, const volatile void>();
    }
    {
        test_is_swappable_with<T0, T0>();
        test_is_swappable_with<T0, const T0>();
        test_is_swappable_with<T1, T2>();
        test_is_swappable_with<T2, T1>();
        test_is_swappable_with<BoolLike, bool&>();
        test_is_swappable_with<const BoolLike, bool&>();
    }
    {
        test_is_not_swappable_with<int&, unsigned&>();
        test_is_not_swappable_with<const int&, int&>();
        test_is_not_swappable_with<const int&, const int&>();
        test_is_not_swappable_with<F0, F0>();
        test_is_not_swappable_with<F0, const F0>();
        test_is_not_swappable_with<const F0, F0>();
        test_is_not_swappable_with<const F0, const F0>();
        test_is_not_swappable_with<T0, T1>();
        test_is_not_swappable_with<T0, const T1>();
        test_is_not_swappable_with<const T0, T1>();
        test_is_not_swappable_with<const T0, const T1>();
        test_is_not_swappable_with<T0, F1>();
        test_is_not_swappable_with<T0, const F1>();
        test_is_not_swappable_with<const T0, F1>();
        test_is_not_swappable_with<const T0, const F1>();
        test_is_not_swappable_with<F0, F1>();
        test_is_not_swappable_with<F0, const F1>();
        test_is_not_swappable_with<const F0, F1>();
        test_is_not_swappable_with<const F0, const F1>();
        test_is_not_swappable_with<F2, F3>();
        test_is_not_swappable_with<F2, const F3>();
        test_is_not_swappable_with<const F2, F3>();
        test_is_not_swappable_with<const F2, const F3>();
        test_is_not_swappable_with<F4, F4>();
        test_is_not_swappable_with<F4, const F4>();
        test_is_not_swappable_with<const F4, F4>();
        test_is_not_swappable_with<const F4, const F4>();
        // TODO: Fix MSVC problems with BoolLike here
#if PHI_COMPILER_IS_NOT(MSVC)
        test_is_not_swappable_with<BoolLike, BoolLike>();
        test_is_not_swappable_with<BoolLike, const BoolLike>();
#endif
        test_is_not_swappable_with<const BoolLike, BoolLike>();
        test_is_not_swappable_with<const BoolLike, const BoolLike>();
    }
    {
        test_is_swappable_with<int*&, int*&>();
        test_is_swappable_with<int**&, int**&>();

        // TODO: The commented out tests currently crash
        test_is_swappable_with<int(&)[1], int(&)[1]>();
        //test_is_swappable_with<int(&)[1][2], int(&)[1][2]>();
        //test_is_swappable_with<int(&)[1][2][3], int(&)[1][2][3]>();

        test_is_not_swappable_with<F&, F&>();
        //test_is_not_swappable_with<F(&)[1], F(&)[1]>();
        test_is_not_swappable_with<F(&)[1][2], F(&)[1][2]>();
        test_is_not_swappable_with<F(&)[1][2][3], F(&)[1][2][3]>();
        //test_is_not_swappable_with<F(&)[4], F(&)[4]>();
        test_is_swappable_with<F(&)[5], F(&)[5]>();
    }
}
