#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/bugs/gcc_102305.hpp>
#include <phi/compiler_support/char8_t.hpp>
#include <phi/compiler_support/noexcept.hpp>
#include <phi/compiler_support/unused.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_constructible.hpp>
#include <phi/type_traits/is_nothrow_constructible.hpp>
#include <type_traits>
#include <vector>

template <typename TypeT, typename... ArgsT>
void test_is_nothrow_constructible()
{
#if PHI_HAS_WORKING_IS_NOTHROW_CONSTRUCTIBLE()
    STATIC_REQUIRE(phi::is_nothrow_constructible<TypeT, ArgsT...>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_nothrow_constructible<TypeT, ArgsT...>::value);
    STATIC_REQUIRE(phi::is_constructible<TypeT, ArgsT...>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_nothrow_constructible_v<TypeT, ArgsT...>);
    STATIC_REQUIRE_FALSE(phi::is_not_nothrow_constructible_v<TypeT, ArgsT...>);
    STATIC_REQUIRE(phi::is_constructible_v<TypeT, ArgsT...>);
#    endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_nothrow_constructible<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_nothrow_constructible<TypeT>);

    // Standard compatibility
    STATIC_REQUIRE(std::is_nothrow_constructible<TypeT, ArgsT...>::value);
#endif
}

template <typename TypeT, typename... ArgsT>
void test_is_nothrow_constructible_no_std()
{
#if PHI_HAS_WORKING_IS_NOTHROW_CONSTRUCTIBLE()
    STATIC_REQUIRE(phi::is_nothrow_constructible<TypeT, ArgsT...>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_nothrow_constructible<TypeT, ArgsT...>::value);
    STATIC_REQUIRE(phi::is_constructible<TypeT, ArgsT...>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_nothrow_constructible_v<TypeT, ArgsT...>);
    STATIC_REQUIRE_FALSE(phi::is_not_nothrow_constructible_v<TypeT, ArgsT...>);
    STATIC_REQUIRE(phi::is_constructible_v<TypeT, ArgsT...>);
#    endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_nothrow_constructible<TypeT, ArgsT...>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_nothrow_constructible<TypeT, ArgsT...>);
#endif
}

template <typename TypeT, typename... ArgsT>
void test_is_not_nothrow_constructible()
{
#if PHI_HAS_WORKING_IS_NOTHROW_CONSTRUCTIBLE()
    STATIC_REQUIRE_FALSE(phi::is_nothrow_constructible<TypeT, ArgsT...>::value);
    STATIC_REQUIRE(phi::is_not_nothrow_constructible<TypeT, ArgsT...>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_nothrow_constructible_v<TypeT, ArgsT...>);
    STATIC_REQUIRE(phi::is_not_nothrow_constructible_v<TypeT, ArgsT...>);
#    endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_nothrow_constructible<TypeT, ArgsT...>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_nothrow_constructible<TypeT, ArgsT...>);

    // Standard compatibility
    STATIC_REQUIRE_FALSE(std::is_nothrow_constructible<TypeT, ArgsT...>::value);
#endif
}

struct A
{
    A(const A&);
};

struct B
{
    B(const B&) PHI_NOEXCEPT;
};

struct C
{
    C(C&); // not const

    // NOLINTNEXTLINE(misc-unconventional-assign-operator)
    void operator=(C&); // not const
};

struct D
{
    D();
};

struct E
{
    E() PHI_NOEXCEPT;
};

struct F
{
    F(int, double, char) PHI_NOEXCEPT;
};

struct G
{};

struct H
{
    H();
    operator int();
};

struct I
{
    I() = default;
    I(const I&);
    I(I&&) = default;

    I& operator=(I&&);
    I& operator=(const I&) = default;
};

struct J
{
    // NOLINTNEXTLINE(modernize-use-equals-default)
    ~J() PHI_NOEXCEPT_EXPR(false)
    {}
};

struct K
{
    K() = default;

    // TODO: Weird clang formatting here

    template <typename... OtherT>
    K(OtherT...)
    PHI_NOEXCEPT;
};

struct L
{
    template <typename... OtherT>
    L(OtherT...);
};

template <typename TypeT>
struct N
{
    N() PHI_NOEXCEPT
    {
        TypeT::error;
    }
};

struct Tuple
{
    Tuple(empty&& /*unused*/) PHI_NOEXCEPT
    {}
};

struct DThrows
{
    DThrows(int /*unused*/) PHI_NOEXCEPT_EXPR(true)
    {}

    // NOLINTNEXTLINE(modernize-use-equals-default)
    ~DThrows() PHI_NOEXCEPT_EXPR(false)
    {}
};

TEST_CASE("is_nothrow_constructible")
{
    test_is_nothrow_constructible<int>();
    test_is_nothrow_constructible<int, const int&>();
    test_is_nothrow_constructible<empty>();
    test_is_nothrow_constructible<empty, const empty&>();

    test_is_not_nothrow_constructible<A, int>();
    test_is_not_nothrow_constructible<A, int, double>();
    test_is_not_nothrow_constructible<A>();
    test_is_nothrow_constructible<B, const B&>();
    test_is_not_nothrow_constructible<C>();
    test_is_not_nothrow_constructible<D>();
    test_is_not_nothrow_constructible<F>();
    test_is_not_nothrow_constructible<F, int>();
    test_is_not_nothrow_constructible<F, int, double>();
    test_is_nothrow_constructible<F, int, double, char>();
    test_is_nothrow_constructible<F, int, float, char>();
    test_is_nothrow_constructible<Tuple&&, empty>();
    test_is_nothrow_constructible<G>();
    test_is_nothrow_constructible<G, G>();
    test_is_not_nothrow_constructible<H>();
    test_is_nothrow_constructible<H, H>();
    test_is_not_nothrow_constructible<G, H>();
    test_is_not_nothrow_constructible<H, G>();
    test_is_nothrow_constructible<I>();
    test_is_nothrow_constructible<I, I>();
    test_is_not_nothrow_constructible<I, I&>();

    test_is_nothrow_constructible<int, int>();
    test_is_nothrow_constructible<int, double>();
    test_is_not_nothrow_constructible<int, H>();
    test_is_not_nothrow_constructible<void, int>();
    test_is_not_nothrow_constructible<const void, int>();
    test_is_not_nothrow_constructible<volatile void, int>();
    test_is_not_nothrow_constructible<const volatile void, int>();
    test_is_not_nothrow_constructible<int, void*>();
    test_is_not_nothrow_constructible<int, int*>();
    test_is_not_nothrow_constructible<int, const int*>();
    test_is_not_nothrow_constructible<int*, void*>();
    test_is_not_nothrow_constructible<int*, const int*>();

    test_is_not_nothrow_constructible<J>();

    test_is_nothrow_constructible<K>();
    test_is_not_nothrow_constructible<L>();

    int  integer{0};
    auto lambda = [=] { return integer; };
    using M     = decltype(lambda);
    PHI_UNUSED_VARIABLE(integer);
    PHI_UNUSED_VARIABLE(lambda);

    test_is_nothrow_constructible<M, M>();
    test_is_nothrow_constructible<N<int>>();

#if PHI_HAS_WORKING_IS_CONSTRUCTIBLE()
    STATIC_REQUIRE_FALSE(phi::is_constructible<Tuple&, empty>::value);
#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_constructible_v<Tuple&, empty>);
#    endif
#endif
    test_is_not_nothrow_constructible<Tuple&, empty>();

    // Test for LWG#2116 (https://cplusplus.github.io/LWG/issue2116)
    test_is_not_nothrow_constructible<DThrows>();

    test_is_not_nothrow_constructible<void>();
    test_is_nothrow_constructible<phi::nullptr_t>();
    test_is_nothrow_constructible<bool>();
    test_is_nothrow_constructible<char>();
    test_is_nothrow_constructible<signed char>();
    test_is_nothrow_constructible<unsigned char>();
    test_is_nothrow_constructible<short>();
    test_is_nothrow_constructible<unsigned short>();
    test_is_nothrow_constructible<int>();
    test_is_nothrow_constructible<unsigned int>();
    test_is_nothrow_constructible<long>();
    test_is_nothrow_constructible<unsigned long>();
    test_is_nothrow_constructible<long long>();
    test_is_nothrow_constructible<unsigned long long>();
    test_is_nothrow_constructible<float>();
    test_is_nothrow_constructible<double>();
    test_is_nothrow_constructible<long double>();
    test_is_nothrow_constructible<char8_t>();
    test_is_nothrow_constructible<char16_t>();
    test_is_nothrow_constructible<char32_t>();
    test_is_nothrow_constructible<wchar_t>();

    test_is_not_nothrow_constructible<phi::boolean>();
    test_is_not_nothrow_constructible<phi::integer<signed char>>();
    test_is_not_nothrow_constructible<phi::integer<unsigned char>>();
    test_is_not_nothrow_constructible<phi::integer<short>>();
    test_is_not_nothrow_constructible<phi::integer<unsigned short>>();
    test_is_not_nothrow_constructible<phi::integer<int>>();
    test_is_not_nothrow_constructible<phi::integer<unsigned int>>();
    test_is_not_nothrow_constructible<phi::integer<long>>();
    test_is_not_nothrow_constructible<phi::integer<unsigned long>>();
    test_is_not_nothrow_constructible<phi::integer<long long>>();
    test_is_not_nothrow_constructible<phi::integer<unsigned long long>>();
    test_is_not_nothrow_constructible<phi::floating_point<float>>();
    test_is_not_nothrow_constructible<phi::floating_point<double>>();
    test_is_not_nothrow_constructible<phi::floating_point<long double>>();

    test_is_nothrow_constructible<std::vector<int>>();
    test_is_nothrow_constructible<phi::scope_ptr<int>>();

    test_is_not_nothrow_constructible<int&>();
    test_is_not_nothrow_constructible<const int&>();
    test_is_not_nothrow_constructible<volatile int&>();
    test_is_not_nothrow_constructible<const volatile int&>();
    test_is_not_nothrow_constructible<int&&>();
    test_is_not_nothrow_constructible<const int&&>();
    test_is_not_nothrow_constructible<volatile int&&>();
    test_is_not_nothrow_constructible<const volatile int&&>();
    test_is_nothrow_constructible<int*>();
    test_is_nothrow_constructible<const int*>();
    test_is_nothrow_constructible<volatile int*>();
    test_is_nothrow_constructible<const volatile int*>();
    test_is_nothrow_constructible<int**>();
    test_is_nothrow_constructible<const int**>();
    test_is_nothrow_constructible<volatile int**>();
    test_is_nothrow_constructible<const volatile int**>();
    test_is_not_nothrow_constructible<int*&>();
    test_is_not_nothrow_constructible<const int*&>();
    test_is_not_nothrow_constructible<volatile int*&>();
    test_is_not_nothrow_constructible<const volatile int*&>();
    test_is_not_nothrow_constructible<int*&&>();
    test_is_not_nothrow_constructible<const int*&&>();
    test_is_not_nothrow_constructible<volatile int*&&>();
    test_is_not_nothrow_constructible<const volatile int*&&>();
    test_is_nothrow_constructible<void*>();
    test_is_nothrow_constructible<char[3]>();
#if PHI_COMPILER_WORKAROUND(GCC, 8, 0, 0)
    test_is_not_nothrow_constructible<char[]>();
#endif
    test_is_nothrow_constructible<char* [3]>();
#if PHI_COMPILER_WORKAROUND(GCC, 8, 0, 0)
    test_is_not_nothrow_constructible<char*[]>();
#endif
    test_is_nothrow_constructible<int(*)[3]>();
    test_is_nothrow_constructible<int(*)[]>();
    test_is_not_nothrow_constructible<int(&)[3]>();
    test_is_not_nothrow_constructible<int(&)[]>();
    test_is_not_nothrow_constructible<int(&&)[3]>();
    test_is_not_nothrow_constructible<int(&&)[]>();
#if PHI_COMPILER_IS_BELOW(EMCC, 1, 39, 0)
    test_is_nothrow_constructible_no_std<char[3][2]>();
#else
    test_is_nothrow_constructible<char[3][2]>();
#endif
#if PHI_COMPILER_WORKAROUND(GCC, 8, 0, 0)
    test_is_not_nothrow_constructible<char[][2]>();
#endif
#if PHI_COMPILER_IS_BELOW(EMCC, 1, 39, 0)
    test_is_nothrow_constructible_no_std<char* [3][2]>();
#else
    test_is_nothrow_constructible<char* [3][2]>();
#endif
#if PHI_COMPILER_WORKAROUND(GCC, 8, 0, 0)
    test_is_not_nothrow_constructible<char*[][2]>();
#endif
    test_is_nothrow_constructible<int(*)[3][2]>();
    test_is_nothrow_constructible<int(*)[][2]>();
    test_is_not_nothrow_constructible<int(&)[3][2]>();
    test_is_not_nothrow_constructible<int(&)[][2]>();
    test_is_not_nothrow_constructible<int(&&)[3][2]>();
    test_is_not_nothrow_constructible<int(&&)[][2]>();
    test_is_nothrow_constructible<class_type>();
#if PHI_COMPILER_WORKAROUND(GCC, 8, 0, 0)
    test_is_not_nothrow_constructible<class_type[]>();
#endif
    test_is_nothrow_constructible<class_type[2]>();
    test_is_nothrow_constructible<template_type<void>>();
    test_is_nothrow_constructible<template_type<int>>();
    test_is_nothrow_constructible<template_type<class_type>>();
    test_is_nothrow_constructible<template_type<incomplete_type>>();
    test_is_nothrow_constructible<variadic_template<>>();
    test_is_nothrow_constructible<variadic_template<void>>();
    test_is_nothrow_constructible<variadic_template<int>>();
    test_is_nothrow_constructible<variadic_template<class_type>>();
    test_is_nothrow_constructible<variadic_template<incomplete_type>>();
    test_is_nothrow_constructible<variadic_template<int, void, class_type, volatile char[]>>();
    test_is_nothrow_constructible<public_derived_from<base>>();
    test_is_nothrow_constructible<public_derived_from<derived>>();
    test_is_nothrow_constructible<public_derived_from<class_type>>();
    test_is_nothrow_constructible<private_derived_from<base>>();
    test_is_nothrow_constructible<private_derived_from<derived>>();
    test_is_nothrow_constructible<private_derived_from<class_type>>();
    test_is_nothrow_constructible<protected_derived_from<base>>();
    test_is_nothrow_constructible<protected_derived_from<derived>>();
    test_is_nothrow_constructible<protected_derived_from<class_type>>();
    test_is_nothrow_constructible<union_type>();
    test_is_nothrow_constructible<non_empty_union>();
    test_is_nothrow_constructible<empty>();
    test_is_nothrow_constructible<not_empty>();
    test_is_nothrow_constructible<bit_zero>();
    test_is_nothrow_constructible<bit_one>();
    test_is_nothrow_constructible<base>();
    test_is_nothrow_constructible<derived>();
    test_is_not_nothrow_constructible<abstract>();
    test_is_not_nothrow_constructible<public_abstract>();
    test_is_not_nothrow_constructible<private_abstract>();
    test_is_not_nothrow_constructible<protected_abstract>();
    test_is_nothrow_constructible<abstract_template<double>>();
#if !PHI_HAS_BUG_GCC_102305()
    test_is_not_nothrow_constructible<abstract_template<int>>();
    test_is_not_nothrow_constructible<abstract_template<class_type>>();
    test_is_not_nothrow_constructible<abstract_template<incomplete_type>>();
#endif
    test_is_nothrow_constructible<final_type>();
    test_is_nothrow_constructible<public_destructor>();
    test_is_not_nothrow_constructible<protected_destructor>();
    test_is_not_nothrow_constructible<private_destructor>();
    test_is_nothrow_constructible<virtual_public_destructor>();
    test_is_not_nothrow_constructible<virtual_protected_destructor>();
    test_is_not_nothrow_constructible<virtual_private_destructor>();
    test_is_not_nothrow_constructible<pure_public_destructor>();
    test_is_not_nothrow_constructible<pure_protected_destructor>();
    test_is_not_nothrow_constructible<pure_private_destructor>();
    test_is_not_nothrow_constructible<deleted_public_destructor>();
    test_is_not_nothrow_constructible<deleted_protected_destructor>();
    test_is_not_nothrow_constructible<deleted_private_destructor>();
    test_is_not_nothrow_constructible<deleted_virtual_public_destructor>();
    test_is_not_nothrow_constructible<deleted_virtual_protected_destructor>();
    test_is_not_nothrow_constructible<deleted_virtual_private_destructor>();
    test_is_nothrow_constructible<Enum>();
    test_is_nothrow_constructible<EnumSigned>();
    test_is_nothrow_constructible<EnumUnsigned>();
    test_is_nothrow_constructible<EnumClass>();
    test_is_nothrow_constructible<EnumStruct>();
    test_is_not_nothrow_constructible<function_type>();
    test_is_nothrow_constructible<function_ptr>();
    test_is_nothrow_constructible<member_object_ptr>();
    test_is_nothrow_constructible<member_function_ptr>();
    test_is_nothrow_constructible<int class_type::*>();
    test_is_nothrow_constructible<float class_type::*>();
    test_is_nothrow_constructible<void * class_type::*>();
    test_is_nothrow_constructible<int * class_type::*>();
    test_is_not_nothrow_constructible<int class_type::*&>();
    test_is_not_nothrow_constructible<float class_type::*&>();
    test_is_not_nothrow_constructible<void * class_type::*&>();
    test_is_not_nothrow_constructible<int * class_type::*&>();
    test_is_not_nothrow_constructible<int class_type::*&&>();
    test_is_not_nothrow_constructible<float class_type::*&&>();
    test_is_not_nothrow_constructible<void * class_type::*&&>();
    test_is_not_nothrow_constructible<int * class_type::*&&>();
    test_is_nothrow_constructible<int class_type::* const>();
    test_is_nothrow_constructible<float class_type::* const>();
    test_is_nothrow_constructible<void * class_type::* const>();
    test_is_not_nothrow_constructible<int class_type::* const&>();
    test_is_not_nothrow_constructible<float class_type::* const&>();
    test_is_not_nothrow_constructible<void * class_type::* const&>();
    test_is_not_nothrow_constructible<int class_type::* const&&>();
    test_is_not_nothrow_constructible<float class_type::* const&&>();
    test_is_not_nothrow_constructible<void * class_type::* const&&>();
    test_is_nothrow_constructible<int class_type::* volatile>();
    test_is_nothrow_constructible<float class_type::* volatile>();
    test_is_nothrow_constructible<void * class_type::* volatile>();
    test_is_not_nothrow_constructible<int class_type::* volatile&>();
    test_is_not_nothrow_constructible<float class_type::* volatile&>();
    test_is_not_nothrow_constructible<void * class_type::* volatile&>();
    test_is_not_nothrow_constructible<int class_type::* volatile&&>();
    test_is_not_nothrow_constructible<float class_type::* volatile&&>();
    test_is_not_nothrow_constructible<void * class_type::* volatile&&>();
    test_is_nothrow_constructible<int class_type::* const volatile>();
    test_is_nothrow_constructible<float class_type::* const volatile>();
    test_is_nothrow_constructible<void * class_type::* const volatile>();
    test_is_not_nothrow_constructible<int class_type::* const volatile&>();
    test_is_not_nothrow_constructible<float class_type::* const volatile&>();
    test_is_not_nothrow_constructible<void * class_type::* const volatile&>();
    test_is_not_nothrow_constructible<int class_type::* const volatile&&>();
    test_is_not_nothrow_constructible<float class_type::* const volatile&&>();
    test_is_not_nothrow_constructible<void * class_type::* const volatile&&>();
    test_is_nothrow_constructible<non_copyable>();
    test_is_nothrow_constructible<non_moveable>();
    test_is_not_nothrow_constructible<non_constructible>();
    test_is_nothrow_constructible<tracked>();
    test_is_nothrow_constructible<trap_constructible>();
    test_is_nothrow_constructible<trap_implicit_conversion>();
    test_is_nothrow_constructible<trap_comma>();
    test_is_nothrow_constructible<trap_call>();
    test_is_nothrow_constructible<trap_self_assign>();
    test_is_nothrow_constructible<trap_deref>();
    test_is_nothrow_constructible<trap_array_subscript>();

    test_is_not_nothrow_constructible<void()>();
    test_is_not_nothrow_constructible<void()&>();
    test_is_not_nothrow_constructible<void() &&>();
    test_is_not_nothrow_constructible<void() const>();
    test_is_not_nothrow_constructible<void() const&>();
    test_is_not_nothrow_constructible<void() const&&>();
    test_is_not_nothrow_constructible<void() volatile>();
    test_is_not_nothrow_constructible<void() volatile&>();
    test_is_not_nothrow_constructible<void() volatile&&>();
    test_is_not_nothrow_constructible<void() const volatile>();
    test_is_not_nothrow_constructible<void() const volatile&>();
    test_is_not_nothrow_constructible<void() const volatile&&>();
    test_is_not_nothrow_constructible<void() noexcept>();
    test_is_not_nothrow_constructible<void() & noexcept>();
    test_is_not_nothrow_constructible<void() && noexcept>();
    test_is_not_nothrow_constructible<void() const noexcept>();
    test_is_not_nothrow_constructible<void() const & noexcept>();
    test_is_not_nothrow_constructible<void() const && noexcept>();
    test_is_not_nothrow_constructible<void() volatile noexcept>();
    test_is_not_nothrow_constructible<void() volatile & noexcept>();
    test_is_not_nothrow_constructible<void() volatile && noexcept>();
    test_is_not_nothrow_constructible<void() const volatile noexcept>();
    test_is_not_nothrow_constructible<void() const volatile & noexcept>();
    test_is_not_nothrow_constructible<void() const volatile && noexcept>();

    test_is_not_nothrow_constructible<void(int)>();
    test_is_not_nothrow_constructible<void(int)&>();
    test_is_not_nothrow_constructible<void(int) &&>();
    test_is_not_nothrow_constructible<void(int) const>();
    test_is_not_nothrow_constructible<void(int) const&>();
    test_is_not_nothrow_constructible<void(int) const&&>();
    test_is_not_nothrow_constructible<void(int) volatile>();
    test_is_not_nothrow_constructible<void(int) volatile&>();
    test_is_not_nothrow_constructible<void(int) volatile&&>();
    test_is_not_nothrow_constructible<void(int) const volatile>();
    test_is_not_nothrow_constructible<void(int) const volatile&>();
    test_is_not_nothrow_constructible<void(int) const volatile&&>();
    test_is_not_nothrow_constructible<void(int) noexcept>();
    test_is_not_nothrow_constructible<void(int) & noexcept>();
    test_is_not_nothrow_constructible<void(int) && noexcept>();
    test_is_not_nothrow_constructible<void(int) const noexcept>();
    test_is_not_nothrow_constructible<void(int) const & noexcept>();
    test_is_not_nothrow_constructible<void(int) const && noexcept>();
    test_is_not_nothrow_constructible<void(int) volatile noexcept>();
    test_is_not_nothrow_constructible<void(int) volatile & noexcept>();
    test_is_not_nothrow_constructible<void(int) volatile && noexcept>();
    test_is_not_nothrow_constructible<void(int) const volatile noexcept>();
    test_is_not_nothrow_constructible<void(int) const volatile & noexcept>();
    test_is_not_nothrow_constructible<void(int) const volatile && noexcept>();

    test_is_not_nothrow_constructible<void(...)>();
    test_is_not_nothrow_constructible<void(...)&>();
    test_is_not_nothrow_constructible<void(...) &&>();
    test_is_not_nothrow_constructible<void(...) const>();
    test_is_not_nothrow_constructible<void(...) const&>();
    test_is_not_nothrow_constructible<void(...) const&&>();
    test_is_not_nothrow_constructible<void(...) volatile>();
    test_is_not_nothrow_constructible<void(...) volatile&>();
    test_is_not_nothrow_constructible<void(...) volatile&&>();
    test_is_not_nothrow_constructible<void(...) const volatile>();
    test_is_not_nothrow_constructible<void(...) const volatile&>();
    test_is_not_nothrow_constructible<void(...) const volatile&&>();
    test_is_not_nothrow_constructible<void(...) noexcept>();
    test_is_not_nothrow_constructible<void(...) & noexcept>();
    test_is_not_nothrow_constructible<void(...) && noexcept>();
    test_is_not_nothrow_constructible<void(...) const noexcept>();
    test_is_not_nothrow_constructible<void(...) const & noexcept>();
    test_is_not_nothrow_constructible<void(...) const && noexcept>();
    test_is_not_nothrow_constructible<void(...) volatile noexcept>();
    test_is_not_nothrow_constructible<void(...) volatile & noexcept>();
    test_is_not_nothrow_constructible<void(...) volatile && noexcept>();
    test_is_not_nothrow_constructible<void(...) const volatile noexcept>();
    test_is_not_nothrow_constructible<void(...) const volatile & noexcept>();
    test_is_not_nothrow_constructible<void(...) const volatile && noexcept>();

    test_is_not_nothrow_constructible<void(int, ...)>();
    test_is_not_nothrow_constructible<void(int, ...)&>();
    test_is_not_nothrow_constructible<void(int, ...) &&>();
    test_is_not_nothrow_constructible<void(int, ...) const>();
    test_is_not_nothrow_constructible<void(int, ...) const&>();
    test_is_not_nothrow_constructible<void(int, ...) const&&>();
    test_is_not_nothrow_constructible<void(int, ...) volatile>();
    test_is_not_nothrow_constructible<void(int, ...) volatile&>();
    test_is_not_nothrow_constructible<void(int, ...) volatile&&>();
    test_is_not_nothrow_constructible<void(int, ...) const volatile>();
    test_is_not_nothrow_constructible<void(int, ...) const volatile&>();
    test_is_not_nothrow_constructible<void(int, ...) const volatile&&>();
    test_is_not_nothrow_constructible<void(int, ...) noexcept>();
    test_is_not_nothrow_constructible<void(int, ...) & noexcept>();
    test_is_not_nothrow_constructible<void(int, ...) && noexcept>();
    test_is_not_nothrow_constructible<void(int, ...) const noexcept>();
    test_is_not_nothrow_constructible<void(int, ...) const & noexcept>();
    test_is_not_nothrow_constructible<void(int, ...) const && noexcept>();
    test_is_not_nothrow_constructible<void(int, ...) volatile noexcept>();
    test_is_not_nothrow_constructible<void(int, ...) volatile & noexcept>();
    test_is_not_nothrow_constructible<void(int, ...) volatile && noexcept>();
    test_is_not_nothrow_constructible<void(int, ...) const volatile noexcept>();
    test_is_not_nothrow_constructible<void(int, ...) const volatile & noexcept>();
    test_is_not_nothrow_constructible<void(int, ...) const volatile && noexcept>();

    test_is_not_nothrow_constructible<int()>();
    test_is_not_nothrow_constructible<int()&>();
    test_is_not_nothrow_constructible<int() &&>();
    test_is_not_nothrow_constructible<int() const>();
    test_is_not_nothrow_constructible<int() const&>();
    test_is_not_nothrow_constructible<int() const&&>();
    test_is_not_nothrow_constructible<int() volatile>();
    test_is_not_nothrow_constructible<int() volatile&>();
    test_is_not_nothrow_constructible<int() volatile&&>();
    test_is_not_nothrow_constructible<int() const volatile>();
    test_is_not_nothrow_constructible<int() const volatile&>();
    test_is_not_nothrow_constructible<int() const volatile&&>();
    test_is_not_nothrow_constructible<int() noexcept>();
    test_is_not_nothrow_constructible<int() & noexcept>();
    test_is_not_nothrow_constructible<int() && noexcept>();
    test_is_not_nothrow_constructible<int() const noexcept>();
    test_is_not_nothrow_constructible<int() const & noexcept>();
    test_is_not_nothrow_constructible<int() const && noexcept>();
    test_is_not_nothrow_constructible<int() volatile noexcept>();
    test_is_not_nothrow_constructible<int() volatile & noexcept>();
    test_is_not_nothrow_constructible<int() volatile && noexcept>();
    test_is_not_nothrow_constructible<int() const volatile noexcept>();
    test_is_not_nothrow_constructible<int() const volatile & noexcept>();
    test_is_not_nothrow_constructible<int() const volatile && noexcept>();

    test_is_not_nothrow_constructible<int(int)>();
    test_is_not_nothrow_constructible<int(int)&>();
    test_is_not_nothrow_constructible<int(int) &&>();
    test_is_not_nothrow_constructible<int(int) const>();
    test_is_not_nothrow_constructible<int(int) const&>();
    test_is_not_nothrow_constructible<int(int) const&&>();
    test_is_not_nothrow_constructible<int(int) volatile>();
    test_is_not_nothrow_constructible<int(int) volatile&>();
    test_is_not_nothrow_constructible<int(int) volatile&&>();
    test_is_not_nothrow_constructible<int(int) const volatile>();
    test_is_not_nothrow_constructible<int(int) const volatile&>();
    test_is_not_nothrow_constructible<int(int) const volatile&&>();
    test_is_not_nothrow_constructible<int(int) noexcept>();
    test_is_not_nothrow_constructible<int(int) & noexcept>();
    test_is_not_nothrow_constructible<int(int) && noexcept>();
    test_is_not_nothrow_constructible<int(int) const noexcept>();
    test_is_not_nothrow_constructible<int(int) const & noexcept>();
    test_is_not_nothrow_constructible<int(int) const && noexcept>();
    test_is_not_nothrow_constructible<int(int) volatile noexcept>();
    test_is_not_nothrow_constructible<int(int) volatile & noexcept>();
    test_is_not_nothrow_constructible<int(int) volatile && noexcept>();
    test_is_not_nothrow_constructible<int(int) const volatile noexcept>();
    test_is_not_nothrow_constructible<int(int) const volatile & noexcept>();
    test_is_not_nothrow_constructible<int(int) const volatile && noexcept>();

    test_is_not_nothrow_constructible<int(...)>();
    test_is_not_nothrow_constructible<int(...)&>();
    test_is_not_nothrow_constructible<int(...) &&>();
    test_is_not_nothrow_constructible<int(...) const>();
    test_is_not_nothrow_constructible<int(...) const&>();
    test_is_not_nothrow_constructible<int(...) const&&>();
    test_is_not_nothrow_constructible<int(...) volatile>();
    test_is_not_nothrow_constructible<int(...) volatile&>();
    test_is_not_nothrow_constructible<int(...) volatile&&>();
    test_is_not_nothrow_constructible<int(...) const volatile>();
    test_is_not_nothrow_constructible<int(...) const volatile&>();
    test_is_not_nothrow_constructible<int(...) const volatile&&>();
    test_is_not_nothrow_constructible<int(...) noexcept>();
    test_is_not_nothrow_constructible<int(...) & noexcept>();
    test_is_not_nothrow_constructible<int(...) && noexcept>();
    test_is_not_nothrow_constructible<int(...) const noexcept>();
    test_is_not_nothrow_constructible<int(...) const & noexcept>();
    test_is_not_nothrow_constructible<int(...) const && noexcept>();
    test_is_not_nothrow_constructible<int(...) volatile noexcept>();
    test_is_not_nothrow_constructible<int(...) volatile & noexcept>();
    test_is_not_nothrow_constructible<int(...) volatile && noexcept>();
    test_is_not_nothrow_constructible<int(...) const volatile noexcept>();
    test_is_not_nothrow_constructible<int(...) const volatile & noexcept>();
    test_is_not_nothrow_constructible<int(...) const volatile && noexcept>();

    test_is_not_nothrow_constructible<int(int, ...)>();
    test_is_not_nothrow_constructible<int(int, ...)&>();
    test_is_not_nothrow_constructible<int(int, ...) &&>();
    test_is_not_nothrow_constructible<int(int, ...) const>();
    test_is_not_nothrow_constructible<int(int, ...) const&>();
    test_is_not_nothrow_constructible<int(int, ...) const&&>();
    test_is_not_nothrow_constructible<int(int, ...) volatile>();
    test_is_not_nothrow_constructible<int(int, ...) volatile&>();
    test_is_not_nothrow_constructible<int(int, ...) volatile&&>();
    test_is_not_nothrow_constructible<int(int, ...) const volatile>();
    test_is_not_nothrow_constructible<int(int, ...) const volatile&>();
    test_is_not_nothrow_constructible<int(int, ...) const volatile&&>();
    test_is_not_nothrow_constructible<int(int, ...) noexcept>();
    test_is_not_nothrow_constructible<int(int, ...) & noexcept>();
    test_is_not_nothrow_constructible<int(int, ...) && noexcept>();
    test_is_not_nothrow_constructible<int(int, ...) const noexcept>();
    test_is_not_nothrow_constructible<int(int, ...) const & noexcept>();
    test_is_not_nothrow_constructible<int(int, ...) const && noexcept>();
    test_is_not_nothrow_constructible<int(int, ...) volatile noexcept>();
    test_is_not_nothrow_constructible<int(int, ...) volatile & noexcept>();
    test_is_not_nothrow_constructible<int(int, ...) volatile && noexcept>();
    test_is_not_nothrow_constructible<int(int, ...) const volatile noexcept>();
    test_is_not_nothrow_constructible<int(int, ...) const volatile & noexcept>();
    test_is_not_nothrow_constructible<int(int, ...) const volatile && noexcept>();

    test_is_nothrow_constructible<void (*)()>();
    test_is_nothrow_constructible<void (*)() noexcept>();

    test_is_nothrow_constructible<void (*)(int)>();
    test_is_nothrow_constructible<void (*)(int) noexcept>();

    test_is_nothrow_constructible<void (*)(...)>();
    test_is_nothrow_constructible<void (*)(...) noexcept>();

    test_is_nothrow_constructible<void (*)(int, ...)>();
    test_is_nothrow_constructible<void (*)(int, ...) noexcept>();

    test_is_nothrow_constructible<int (*)()>();
    test_is_nothrow_constructible<int (*)() noexcept>();

    test_is_nothrow_constructible<int (*)(int)>();
    test_is_nothrow_constructible<int (*)(int) noexcept>();

    test_is_nothrow_constructible<int (*)(...)>();
    test_is_nothrow_constructible<int (*)(...) noexcept>();

    test_is_nothrow_constructible<int (*)(int, ...)>();
    test_is_nothrow_constructible<int (*)(int, ...) noexcept>();

    test_is_not_nothrow_constructible<void (&)()>();
    test_is_not_nothrow_constructible<void (&)() noexcept>();

    test_is_not_nothrow_constructible<void (&)(int)>();
    test_is_not_nothrow_constructible<void (&)(int) noexcept>();

    test_is_not_nothrow_constructible<void (&)(...)>();
    test_is_not_nothrow_constructible<void (&)(...) noexcept>();

    test_is_not_nothrow_constructible<void (&)(int, ...)>();
    test_is_not_nothrow_constructible<void (&)(int, ...) noexcept>();

    test_is_not_nothrow_constructible<int (&)()>();
    test_is_not_nothrow_constructible<int (&)() noexcept>();

    test_is_not_nothrow_constructible<int (&)(int)>();
    test_is_not_nothrow_constructible<int (&)(int) noexcept>();

    test_is_not_nothrow_constructible<int (&)(...)>();
    test_is_not_nothrow_constructible<int (&)(...) noexcept>();

    test_is_not_nothrow_constructible<int (&)(int, ...)>();
    test_is_not_nothrow_constructible<int (&)(int, ...) noexcept>();

    test_is_not_nothrow_constructible<void (&&)()>();
    test_is_not_nothrow_constructible<void (&&)() noexcept>();

    test_is_not_nothrow_constructible<void (&&)(int)>();
    test_is_not_nothrow_constructible<void (&&)(int) noexcept>();

    test_is_not_nothrow_constructible<void (&&)(...)>();
    test_is_not_nothrow_constructible<void (&&)(...) noexcept>();

    test_is_not_nothrow_constructible<void (&&)(int, ...)>();
    test_is_not_nothrow_constructible<void (&&)(int, ...) noexcept>();

    test_is_not_nothrow_constructible<int (&&)()>();
    test_is_not_nothrow_constructible<int (&&)() noexcept>();

    test_is_not_nothrow_constructible<int (&&)(int)>();
    test_is_not_nothrow_constructible<int (&&)(int) noexcept>();

    test_is_not_nothrow_constructible<int (&&)(...)>();
    test_is_not_nothrow_constructible<int (&&)(...) noexcept>();

    test_is_not_nothrow_constructible<int (&&)(int, ...)>();
    test_is_not_nothrow_constructible<int (&&)(int, ...) noexcept>();

    test_is_nothrow_constructible<void (class_type::*)()>();
    test_is_nothrow_constructible<void (class_type::*)()&>();
    test_is_nothrow_constructible<void (class_type::*)() &&>();
    test_is_nothrow_constructible<void (class_type::*)() const>();
    test_is_nothrow_constructible<void (class_type::*)() const&>();
    test_is_nothrow_constructible<void (class_type::*)() const&&>();
    test_is_nothrow_constructible<void (class_type::*)() noexcept>();
    test_is_nothrow_constructible<void (class_type::*)() & noexcept>();
    test_is_nothrow_constructible<void (class_type::*)() && noexcept>();
    test_is_nothrow_constructible<void (class_type::*)() const noexcept>();
    test_is_nothrow_constructible<void (class_type::*)() const & noexcept>();
    test_is_nothrow_constructible<void (class_type::*)() const && noexcept>();

    test_is_nothrow_constructible<void (class_type::*)(int)>();
    test_is_nothrow_constructible<void (class_type::*)(int)&>();
    test_is_nothrow_constructible<void (class_type::*)(int) &&>();
    test_is_nothrow_constructible<void (class_type::*)(int) const>();
    test_is_nothrow_constructible<void (class_type::*)(int) const&>();
    test_is_nothrow_constructible<void (class_type::*)(int) const&&>();
    test_is_nothrow_constructible<void (class_type::*)(int) noexcept>();
    test_is_nothrow_constructible<void (class_type::*)(int) & noexcept>();
    test_is_nothrow_constructible<void (class_type::*)(int) && noexcept>();
    test_is_nothrow_constructible<void (class_type::*)(int) const noexcept>();
    test_is_nothrow_constructible<void (class_type::*)(int) const & noexcept>();
    test_is_nothrow_constructible<void (class_type::*)(int) const && noexcept>();

    test_is_nothrow_constructible<void (class_type::*)(...)>();
    test_is_nothrow_constructible<void (class_type::*)(...)&>();
    test_is_nothrow_constructible<void (class_type::*)(...) &&>();
    test_is_nothrow_constructible<void (class_type::*)(...) const>();
    test_is_nothrow_constructible<void (class_type::*)(...) const&>();
    test_is_nothrow_constructible<void (class_type::*)(...) const&&>();
    test_is_nothrow_constructible<void (class_type::*)(...) noexcept>();
    test_is_nothrow_constructible<void (class_type::*)(...) & noexcept>();
    test_is_nothrow_constructible<void (class_type::*)(...) && noexcept>();
    test_is_nothrow_constructible<void (class_type::*)(...) const noexcept>();
    test_is_nothrow_constructible<void (class_type::*)(...) const & noexcept>();
    test_is_nothrow_constructible<void (class_type::*)(...) const && noexcept>();

    test_is_nothrow_constructible<void (class_type::*)(int, ...)>();
    test_is_nothrow_constructible<void (class_type::*)(int, ...)&>();
    test_is_nothrow_constructible<void (class_type::*)(int, ...) &&>();
    test_is_nothrow_constructible<void (class_type::*)(int, ...) const>();
    test_is_nothrow_constructible<void (class_type::*)(int, ...) const&>();
    test_is_nothrow_constructible<void (class_type::*)(int, ...) const&&>();
    test_is_nothrow_constructible<void (class_type::*)(int, ...) noexcept>();
    test_is_nothrow_constructible<void (class_type::*)(int, ...) & noexcept>();
    test_is_nothrow_constructible<void (class_type::*)(int, ...) && noexcept>();
    test_is_nothrow_constructible<void (class_type::*)(int, ...) const noexcept>();
    test_is_nothrow_constructible<void (class_type::*)(int, ...) const & noexcept>();
    test_is_nothrow_constructible<void (class_type::*)(int, ...) const && noexcept>();

    test_is_nothrow_constructible<int (class_type::*)()>();
    test_is_nothrow_constructible<int (class_type::*)()&>();
    test_is_nothrow_constructible<int (class_type::*)() &&>();
    test_is_nothrow_constructible<int (class_type::*)() const>();
    test_is_nothrow_constructible<int (class_type::*)() const&>();
    test_is_nothrow_constructible<int (class_type::*)() const&&>();
    test_is_nothrow_constructible<int (class_type::*)() noexcept>();
    test_is_nothrow_constructible<int (class_type::*)() & noexcept>();
    test_is_nothrow_constructible<int (class_type::*)() && noexcept>();
    test_is_nothrow_constructible<int (class_type::*)() const noexcept>();
    test_is_nothrow_constructible<int (class_type::*)() const & noexcept>();
    test_is_nothrow_constructible<int (class_type::*)() const && noexcept>();

    test_is_nothrow_constructible<int (class_type::*)(int)>();
    test_is_nothrow_constructible<int (class_type::*)(int)&>();
    test_is_nothrow_constructible<int (class_type::*)(int) &&>();
    test_is_nothrow_constructible<int (class_type::*)(int) const>();
    test_is_nothrow_constructible<int (class_type::*)(int) const&>();
    test_is_nothrow_constructible<int (class_type::*)(int) const&&>();
    test_is_nothrow_constructible<int (class_type::*)(int) noexcept>();
    test_is_nothrow_constructible<int (class_type::*)(int) & noexcept>();
    test_is_nothrow_constructible<int (class_type::*)(int) && noexcept>();
    test_is_nothrow_constructible<int (class_type::*)(int) const noexcept>();
    test_is_nothrow_constructible<int (class_type::*)(int) const & noexcept>();
    test_is_nothrow_constructible<int (class_type::*)(int) const && noexcept>();

    test_is_nothrow_constructible<int (class_type::*)(...)>();
    test_is_nothrow_constructible<int (class_type::*)(...)&>();
    test_is_nothrow_constructible<int (class_type::*)(...) &&>();
    test_is_nothrow_constructible<int (class_type::*)(...) const>();
    test_is_nothrow_constructible<int (class_type::*)(...) const&>();
    test_is_nothrow_constructible<int (class_type::*)(...) const&&>();
    test_is_nothrow_constructible<int (class_type::*)(...) noexcept>();
    test_is_nothrow_constructible<int (class_type::*)(...) & noexcept>();
    test_is_nothrow_constructible<int (class_type::*)(...) && noexcept>();
    test_is_nothrow_constructible<int (class_type::*)(...) const noexcept>();
    test_is_nothrow_constructible<int (class_type::*)(...) const & noexcept>();
    test_is_nothrow_constructible<int (class_type::*)(...) const && noexcept>();

    test_is_nothrow_constructible<int (class_type::*)(int, ...)>();
    test_is_nothrow_constructible<int (class_type::*)(int, ...)&>();
    test_is_nothrow_constructible<int (class_type::*)(int, ...) &&>();
    test_is_nothrow_constructible<int (class_type::*)(int, ...) const>();
    test_is_nothrow_constructible<int (class_type::*)(int, ...) const&>();
    test_is_nothrow_constructible<int (class_type::*)(int, ...) const&&>();
    test_is_nothrow_constructible<int (class_type::*)(int, ...) noexcept>();
    test_is_nothrow_constructible<int (class_type::*)(int, ...) & noexcept>();
    test_is_nothrow_constructible<int (class_type::*)(int, ...) && noexcept>();
    test_is_nothrow_constructible<int (class_type::*)(int, ...) const noexcept>();
    test_is_nothrow_constructible<int (class_type::*)(int, ...) const & noexcept>();
    test_is_nothrow_constructible<int (class_type::*)(int, ...) const && noexcept>();
}
