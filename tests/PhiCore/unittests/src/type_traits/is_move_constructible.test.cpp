#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/bugs/gcc_102305.hpp>
#include <phi/compiler_support/char8_t.hpp>
#include <phi/compiler_support/compiler.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_move_constructible.hpp>
#include <type_traits>
#include <vector>

template <typename TypeT>
void test_is_move_constructible_impl()
{
#if PHI_HAS_WORKING_IS_MOVE_CONSTRUCTIBLE()
    STATIC_REQUIRE(phi::is_move_constructible<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_move_constructible<TypeT>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_move_constructible_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_not_move_constructible_v<TypeT>);
#    endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_move_constructible<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_move_constructible<TypeT>);

    // Standard compatibility
    STATIC_REQUIRE(std::is_move_constructible<TypeT>::value);
#endif
}

template <typename TypeT>
void test_is_not_move_constructible_impl()
{
#if PHI_HAS_WORKING_IS_MOVE_CONSTRUCTIBLE()
    STATIC_REQUIRE_FALSE(phi::is_move_constructible<TypeT>::value);
    STATIC_REQUIRE(phi::is_not_move_constructible<TypeT>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_move_constructible_v<TypeT>);
    STATIC_REQUIRE(phi::is_not_move_constructible_v<TypeT>);
#    endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_move_constructible<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_move_constructible<TypeT>);

    // Standard compatibility
    STATIC_REQUIRE_FALSE(std::is_move_constructible<TypeT>::value);
#endif
}

template <typename TypeT>
void test_is_move_constructible()
{
    test_is_move_constructible_impl<TypeT>();
    test_is_not_move_constructible_impl<const TypeT>();
    test_is_not_move_constructible_impl<volatile TypeT>();
    test_is_not_move_constructible_impl<const volatile TypeT>();
}

template <typename TypeT>
void test_is_move_constructible_c()
{
    test_is_move_constructible_impl<TypeT>();
    test_is_not_move_constructible_impl<volatile TypeT>();
    test_is_move_constructible_impl<const TypeT>();
    test_is_not_move_constructible_impl<const volatile TypeT>();
}

template <typename TypeT>
void test_is_move_constructible_cv()
{
    test_is_move_constructible_impl<TypeT>();
    test_is_move_constructible_impl<const TypeT>();
    test_is_move_constructible_impl<volatile TypeT>();
    test_is_move_constructible_impl<const volatile TypeT>();
}

template <typename TypeT>
void test_is_not_move_constructible_cv()
{
    test_is_not_move_constructible_impl<TypeT>();
    test_is_not_move_constructible_impl<const TypeT>();
    test_is_not_move_constructible_impl<volatile TypeT>();
    test_is_not_move_constructible_impl<const volatile TypeT>();
}

template <typename TypeT>
void test_is_not_move_constructible_c()
{
    test_is_not_move_constructible_impl<TypeT>();
    test_is_move_constructible_impl<const TypeT>();
    test_is_not_move_constructible_impl<volatile TypeT>();
    test_is_not_move_constructible_impl<const volatile TypeT>();
}

struct A
{
    A(const A&);
};

struct B
{
    B(B&&);
};

struct C
{
    C() = delete;
};

struct D
{
    D(const D&) = delete;
};

struct E
{
    E(E&&) = delete;
};

struct F
{
    F& operator=(const F&) = delete;
};

struct G
{
    G& operator=(G&&) = delete;
};

struct H
{
    H() = default;

    H(const H&) = default;
    H(H&&)      = default;

    H& operator=(const H&) = default;
    H& operator=(H&&)      = default;
};

TEST_CASE("is_move_constructible")
{
    test_is_move_constructible_c<A>();
    test_is_move_constructible<B>();
    test_is_move_constructible_c<C>();
    test_is_not_move_constructible_cv<D>();
    test_is_not_move_constructible_cv<E>();
    test_is_move_constructible_c<F>();
    test_is_not_move_constructible_cv<G>();
    test_is_move_constructible_c<H>();

    // Incomplete types only work with the intrinsic functions
#if PHI_SUPPORTS_IS_CONSTRUCTIBLE()
    test_is_not_move_constructible_cv<void>();
#endif
    test_is_move_constructible_cv<phi::nullptr_t>();
    test_is_move_constructible_cv<bool>();
    test_is_move_constructible_cv<char>();
    test_is_move_constructible_cv<signed char>();
    test_is_move_constructible_cv<unsigned char>();
    test_is_move_constructible_cv<short>();
    test_is_move_constructible_cv<unsigned short>();
    test_is_move_constructible_cv<int>();
    test_is_move_constructible_cv<unsigned int>();
    test_is_move_constructible_cv<long>();
    test_is_move_constructible_cv<unsigned long>();
    test_is_move_constructible_cv<long long>();
    test_is_move_constructible_cv<unsigned long long>();
    test_is_move_constructible_cv<float>();
    test_is_move_constructible_cv<double>();
    test_is_move_constructible_cv<long double>();
    test_is_move_constructible_cv<char8_t>();
    test_is_move_constructible_cv<char16_t>();
    test_is_move_constructible_cv<char32_t>();
    test_is_move_constructible_cv<wchar_t>();

    test_is_move_constructible_c<phi::boolean>();
    test_is_move_constructible_c<phi::integer<signed char>>();
    test_is_move_constructible_c<phi::integer<unsigned char>>();
    test_is_move_constructible_c<phi::integer<short>>();
    test_is_move_constructible_c<phi::integer<unsigned short>>();
    test_is_move_constructible_c<phi::integer<int>>();
    test_is_move_constructible_c<phi::integer<unsigned int>>();
    test_is_move_constructible_c<phi::integer<long>>();
    test_is_move_constructible_c<phi::integer<unsigned long>>();
    test_is_move_constructible_c<phi::integer<long long>>();
    test_is_move_constructible_c<phi::integer<unsigned long long>>();
    test_is_move_constructible_c<phi::floating_point<float>>();
    test_is_move_constructible_c<phi::floating_point<double>>();
    test_is_move_constructible_c<phi::floating_point<long double>>();

    test_is_move_constructible_c<std::vector<int>>();
    test_is_move_constructible<phi::scope_ptr<int>>();

    test_is_move_constructible_cv<int&>();
    test_is_move_constructible_cv<const int&>();
    test_is_move_constructible_cv<volatile int&>();
    test_is_move_constructible_cv<const volatile int&>();
    test_is_move_constructible_cv<int&&>();
    test_is_move_constructible_cv<const int&&>();
    test_is_move_constructible_cv<volatile int&&>();
    test_is_move_constructible_cv<const volatile int&&>();
    test_is_move_constructible_cv<int*>();
    test_is_move_constructible_cv<const int*>();
    test_is_move_constructible_cv<volatile int*>();
    test_is_move_constructible_cv<const volatile int*>();
    test_is_move_constructible_cv<int**>();
    test_is_move_constructible_cv<const int**>();
    test_is_move_constructible_cv<volatile int**>();
    test_is_move_constructible_cv<const volatile int**>();
    test_is_move_constructible_cv<int*&>();
    test_is_move_constructible_cv<const int*&>();
    test_is_move_constructible_cv<volatile int*&>();
    test_is_move_constructible_cv<const volatile int*&>();
    test_is_move_constructible_cv<int*&&>();
    test_is_move_constructible_cv<const int*&&>();
    test_is_move_constructible_cv<volatile int*&&>();
    test_is_move_constructible_cv<const volatile int*&&>();
    test_is_move_constructible_cv<void*>();
    test_is_not_move_constructible_cv<char[3]>();
    test_is_not_move_constructible_cv<char* [3]>();
    test_is_move_constructible_cv<int(*)[3]>();
    test_is_move_constructible_cv<int(&)[3]>();
    test_is_move_constructible_cv<int(&&)[3]>();
    test_is_not_move_constructible_cv<char[3][2]>();
    test_is_not_move_constructible_cv<char* [3][2]>();
    test_is_move_constructible_cv<int(*)[3][2]>();
    test_is_move_constructible_cv<int(&)[3][2]>();
    test_is_move_constructible_cv<int(&&)[3][2]>();
#if PHI_SUPPORTS_IS_CONSTRUCTIBLE()
    test_is_not_move_constructible_cv<char[]>();
    test_is_not_move_constructible_cv<char*[]>();
    test_is_move_constructible_cv<int(*)[]>();
    test_is_move_constructible_cv<int(&)[]>();
    test_is_move_constructible_cv<int(&&)[]>();
    test_is_not_move_constructible_cv<char[][2]>();
    test_is_not_move_constructible_cv<char*[][2]>();
    test_is_move_constructible_cv<int(*)[][2]>();
    test_is_move_constructible_cv<int(&)[][2]>();
    test_is_move_constructible_cv<int(&&)[][2]>();
#endif
    test_is_move_constructible_c<class_type>();
#if PHI_SUPPORTS_IS_CONSTRUCTIBLE()
    test_is_not_move_constructible_cv<class_type[]>();
    test_is_not_move_constructible_cv<class_type[2]>();
#else
    SKIP_CHECK();
    SKIP_CHECK();
#endif
    test_is_move_constructible_c<template_type<void>>();
    test_is_move_constructible_c<template_type<int>>();
    test_is_move_constructible_c<template_type<class_type>>();
    test_is_move_constructible_c<template_type<incomplete_type>>();
    test_is_move_constructible_c<variadic_template<>>();
    test_is_move_constructible_c<variadic_template<void>>();
    test_is_move_constructible_c<variadic_template<int>>();
    test_is_move_constructible_c<variadic_template<class_type>>();
    test_is_move_constructible_c<variadic_template<incomplete_type>>();
    test_is_move_constructible_c<variadic_template<int, void, class_type, volatile char[]>>();
    test_is_move_constructible_c<public_derived_from<base>>();
    test_is_move_constructible_c<public_derived_from<derived>>();
    test_is_move_constructible_c<public_derived_from<class_type>>();
    test_is_move_constructible_c<private_derived_from<base>>();
    test_is_move_constructible_c<private_derived_from<derived>>();
    test_is_move_constructible_c<private_derived_from<class_type>>();
    test_is_move_constructible_c<protected_derived_from<base>>();
    test_is_move_constructible_c<protected_derived_from<derived>>();
    test_is_move_constructible_c<protected_derived_from<class_type>>();
    test_is_move_constructible_c<union_type>();
    test_is_move_constructible_c<non_empty_union>();
    test_is_move_constructible_c<empty>();
    test_is_move_constructible_c<not_empty>();
    test_is_move_constructible_c<bit_zero>();
    test_is_move_constructible_c<bit_one>();
    test_is_move_constructible_c<base>();
    test_is_move_constructible_c<derived>();
    test_is_not_move_constructible_cv<abstract>();
    test_is_not_move_constructible_cv<public_abstract>();
    test_is_not_move_constructible_cv<private_abstract>();
    test_is_not_move_constructible_cv<protected_abstract>();
#if !PHI_HAS_BUG_GCC_102305()
    // Test GCC bug 102305 (https://gcc.gnu.org/bugzilla/show_bug.cgi?id=102305)
    test_is_not_move_constructible_cv<abstract_template<int>>();
    test_is_move_constructible_c<abstract_template<double>>();
    test_is_not_move_constructible_cv<abstract_template<class_type>>();
    test_is_not_move_constructible_cv<abstract_template<incomplete_type>>();
#endif
    test_is_move_constructible_c<final_type>();
    test_is_move_constructible_c<public_destructor>();
    test_is_not_move_constructible_cv<protected_destructor>();
    test_is_not_move_constructible_cv<private_destructor>();
    test_is_move_constructible_c<virtual_public_destructor>();
    test_is_not_move_constructible_cv<virtual_protected_destructor>();
    test_is_not_move_constructible_cv<virtual_private_destructor>();
    test_is_not_move_constructible_cv<pure_public_destructor>();
    test_is_not_move_constructible_cv<pure_protected_destructor>();
    test_is_not_move_constructible_cv<pure_private_destructor>();
    test_is_not_move_constructible_cv<deleted_public_destructor>();
    test_is_not_move_constructible_cv<deleted_protected_destructor>();
    test_is_not_move_constructible_cv<deleted_private_destructor>();
    test_is_not_move_constructible_cv<deleted_virtual_public_destructor>();
    test_is_not_move_constructible_cv<deleted_virtual_protected_destructor>();
    test_is_not_move_constructible_cv<deleted_virtual_private_destructor>();
    test_is_move_constructible_cv<Enum>();
    test_is_move_constructible_cv<EnumSigned>();
    test_is_move_constructible_cv<EnumUnsigned>();
    test_is_move_constructible_cv<EnumClass>();
    test_is_move_constructible_cv<EnumStruct>();
    test_is_not_move_constructible_cv<function_type>();
    test_is_move_constructible_cv<function_ptr>();
    test_is_move_constructible_cv<member_object_ptr>();
    test_is_move_constructible_cv<member_function_ptr>();
    test_is_move_constructible_cv<int class_type::*>();
    test_is_move_constructible_cv<float class_type::*>();
    test_is_move_constructible_cv<void * class_type::*>();
    test_is_move_constructible_cv<int * class_type::*>();
    test_is_move_constructible_cv<int class_type::*&>();
    test_is_move_constructible_cv<float class_type::*&>();
    test_is_move_constructible_cv<void * class_type::*&>();
    test_is_move_constructible_cv<int * class_type::*&>();
    test_is_move_constructible_cv<int class_type::*&&>();
    test_is_move_constructible_cv<float class_type::*&&>();
    test_is_move_constructible_cv<void * class_type::*&&>();
    test_is_move_constructible_cv<int * class_type::*&&>();
    test_is_move_constructible_cv<int class_type::*const>();
    test_is_move_constructible_cv<float class_type::*const>();
    test_is_move_constructible_cv<void * class_type::*const>();
    test_is_move_constructible_cv<int class_type::*const&>();
    test_is_move_constructible_cv<float class_type::*const&>();
    test_is_move_constructible_cv<void * class_type::*const&>();
    test_is_move_constructible_cv<int class_type::*const&&>();
    test_is_move_constructible_cv<float class_type::*const&&>();
    test_is_move_constructible_cv<void * class_type::*const&&>();
    test_is_move_constructible_cv<int class_type::*volatile>();
    test_is_move_constructible_cv<float class_type::*volatile>();
    test_is_move_constructible_cv<void * class_type::*volatile>();
    test_is_move_constructible_cv<int class_type::*volatile&>();
    test_is_move_constructible_cv<float class_type::*volatile&>();
    test_is_move_constructible_cv<void * class_type::*volatile&>();
    test_is_move_constructible_cv<int class_type::*volatile&&>();
    test_is_move_constructible_cv<float class_type::*volatile&&>();
    test_is_move_constructible_cv<void * class_type::*volatile&&>();
    test_is_move_constructible_cv<int class_type::*const volatile>();
    test_is_move_constructible_cv<float class_type::*const volatile>();
    test_is_move_constructible_cv<void * class_type::*const volatile>();
    test_is_move_constructible_cv<int class_type::*const volatile&>();
    test_is_move_constructible_cv<float class_type::*const volatile&>();
    test_is_move_constructible_cv<void * class_type::*const volatile&>();
    test_is_move_constructible_cv<int class_type::*const volatile&&>();
    test_is_move_constructible_cv<float class_type::*const volatile&&>();
    test_is_move_constructible_cv<void * class_type::*const volatile&&>();
    test_is_move_constructible<non_copyable>();
    test_is_not_move_constructible_c<non_moveable>();
    test_is_not_move_constructible_cv<non_constructible>();
    test_is_move_constructible_c<tracked>();
    test_is_move_constructible_cv<trap_constructible>();
    test_is_move_constructible_c<trap_implicit_conversion>();
    test_is_move_constructible_c<trap_comma>();
    test_is_move_constructible_c<trap_call>();
    test_is_move_constructible_c<trap_self_assign>();
    test_is_move_constructible_c<trap_deref>();
    test_is_move_constructible_c<trap_array_subscript>();

    test_is_not_move_constructible_cv<void()>();
    test_is_not_move_constructible_cv<void()&>();
    test_is_not_move_constructible_cv<void() &&>();
    test_is_not_move_constructible_cv<void() const>();
    test_is_not_move_constructible_cv<void() const&>();
    test_is_not_move_constructible_cv<void() const&&>();
    test_is_not_move_constructible_cv<void() volatile>();
    test_is_not_move_constructible_cv<void() volatile&>();
    test_is_not_move_constructible_cv<void() volatile&&>();
    test_is_not_move_constructible_cv<void() const volatile>();
    test_is_not_move_constructible_cv<void() const volatile&>();
    test_is_not_move_constructible_cv<void() const volatile&&>();
    test_is_not_move_constructible_cv<void() noexcept>();
    test_is_not_move_constructible_cv<void() & noexcept>();
    test_is_not_move_constructible_cv<void() && noexcept>();
    test_is_not_move_constructible_cv<void() const noexcept>();
    test_is_not_move_constructible_cv<void() const & noexcept>();
    test_is_not_move_constructible_cv<void() const && noexcept>();
    test_is_not_move_constructible_cv<void() volatile noexcept>();
    test_is_not_move_constructible_cv<void() volatile & noexcept>();
    test_is_not_move_constructible_cv<void() volatile && noexcept>();
    test_is_not_move_constructible_cv<void() const volatile noexcept>();
    test_is_not_move_constructible_cv<void() const volatile & noexcept>();
    test_is_not_move_constructible_cv<void() const volatile && noexcept>();

    test_is_not_move_constructible_cv<void(int)>();
    test_is_not_move_constructible_cv<void(int)&>();
    test_is_not_move_constructible_cv<void(int) &&>();
    test_is_not_move_constructible_cv<void(int) const>();
    test_is_not_move_constructible_cv<void(int) const&>();
    test_is_not_move_constructible_cv<void(int) const&&>();
    test_is_not_move_constructible_cv<void(int) volatile>();
    test_is_not_move_constructible_cv<void(int) volatile&>();
    test_is_not_move_constructible_cv<void(int) volatile&&>();
    test_is_not_move_constructible_cv<void(int) const volatile>();
    test_is_not_move_constructible_cv<void(int) const volatile&>();
    test_is_not_move_constructible_cv<void(int) const volatile&&>();
    test_is_not_move_constructible_cv<void(int) noexcept>();
    test_is_not_move_constructible_cv<void(int) & noexcept>();
    test_is_not_move_constructible_cv<void(int) && noexcept>();
    test_is_not_move_constructible_cv<void(int) const noexcept>();
    test_is_not_move_constructible_cv<void(int) const & noexcept>();
    test_is_not_move_constructible_cv<void(int) const && noexcept>();
    test_is_not_move_constructible_cv<void(int) volatile noexcept>();
    test_is_not_move_constructible_cv<void(int) volatile & noexcept>();
    test_is_not_move_constructible_cv<void(int) volatile && noexcept>();
    test_is_not_move_constructible_cv<void(int) const volatile noexcept>();
    test_is_not_move_constructible_cv<void(int) const volatile & noexcept>();
    test_is_not_move_constructible_cv<void(int) const volatile && noexcept>();

    test_is_not_move_constructible_cv<void(...)>();
    test_is_not_move_constructible_cv<void(...)&>();
    test_is_not_move_constructible_cv<void(...) &&>();
    test_is_not_move_constructible_cv<void(...) const>();
    test_is_not_move_constructible_cv<void(...) const&>();
    test_is_not_move_constructible_cv<void(...) const&&>();
    test_is_not_move_constructible_cv<void(...) volatile>();
    test_is_not_move_constructible_cv<void(...) volatile&>();
    test_is_not_move_constructible_cv<void(...) volatile&&>();
    test_is_not_move_constructible_cv<void(...) const volatile>();
    test_is_not_move_constructible_cv<void(...) const volatile&>();
    test_is_not_move_constructible_cv<void(...) const volatile&&>();
    test_is_not_move_constructible_cv<void(...) noexcept>();
    test_is_not_move_constructible_cv<void(...) & noexcept>();
    test_is_not_move_constructible_cv<void(...) && noexcept>();
    test_is_not_move_constructible_cv<void(...) const noexcept>();
    test_is_not_move_constructible_cv<void(...) const & noexcept>();
    test_is_not_move_constructible_cv<void(...) const && noexcept>();
    test_is_not_move_constructible_cv<void(...) volatile noexcept>();
    test_is_not_move_constructible_cv<void(...) volatile & noexcept>();
    test_is_not_move_constructible_cv<void(...) volatile && noexcept>();
    test_is_not_move_constructible_cv<void(...) const volatile noexcept>();
    test_is_not_move_constructible_cv<void(...) const volatile & noexcept>();
    test_is_not_move_constructible_cv<void(...) const volatile && noexcept>();

    test_is_not_move_constructible_cv<void(int, ...)>();
    test_is_not_move_constructible_cv<void(int, ...)&>();
    test_is_not_move_constructible_cv<void(int, ...) &&>();
    test_is_not_move_constructible_cv<void(int, ...) const>();
    test_is_not_move_constructible_cv<void(int, ...) const&>();
    test_is_not_move_constructible_cv<void(int, ...) const&&>();
    test_is_not_move_constructible_cv<void(int, ...) volatile>();
    test_is_not_move_constructible_cv<void(int, ...) volatile&>();
    test_is_not_move_constructible_cv<void(int, ...) volatile&&>();
    test_is_not_move_constructible_cv<void(int, ...) const volatile>();
    test_is_not_move_constructible_cv<void(int, ...) const volatile&>();
    test_is_not_move_constructible_cv<void(int, ...) const volatile&&>();
    test_is_not_move_constructible_cv<void(int, ...) noexcept>();
    test_is_not_move_constructible_cv<void(int, ...) & noexcept>();
    test_is_not_move_constructible_cv<void(int, ...) && noexcept>();
    test_is_not_move_constructible_cv<void(int, ...) const noexcept>();
    test_is_not_move_constructible_cv<void(int, ...) const & noexcept>();
    test_is_not_move_constructible_cv<void(int, ...) const && noexcept>();
    test_is_not_move_constructible_cv<void(int, ...) volatile noexcept>();
    test_is_not_move_constructible_cv<void(int, ...) volatile & noexcept>();
    test_is_not_move_constructible_cv<void(int, ...) volatile && noexcept>();
    test_is_not_move_constructible_cv<void(int, ...) const volatile noexcept>();
    test_is_not_move_constructible_cv<void(int, ...) const volatile & noexcept>();
    test_is_not_move_constructible_cv<void(int, ...) const volatile && noexcept>();

    test_is_not_move_constructible_cv<int()>();
    test_is_not_move_constructible_cv<int()&>();
    test_is_not_move_constructible_cv<int() &&>();
    test_is_not_move_constructible_cv<int() const>();
    test_is_not_move_constructible_cv<int() const&>();
    test_is_not_move_constructible_cv<int() const&&>();
    test_is_not_move_constructible_cv<int() volatile>();
    test_is_not_move_constructible_cv<int() volatile&>();
    test_is_not_move_constructible_cv<int() volatile&&>();
    test_is_not_move_constructible_cv<int() const volatile>();
    test_is_not_move_constructible_cv<int() const volatile&>();
    test_is_not_move_constructible_cv<int() const volatile&&>();
    test_is_not_move_constructible_cv<int() noexcept>();
    test_is_not_move_constructible_cv<int() & noexcept>();
    test_is_not_move_constructible_cv<int() && noexcept>();
    test_is_not_move_constructible_cv<int() const noexcept>();
    test_is_not_move_constructible_cv<int() const & noexcept>();
    test_is_not_move_constructible_cv<int() const && noexcept>();
    test_is_not_move_constructible_cv<int() volatile noexcept>();
    test_is_not_move_constructible_cv<int() volatile & noexcept>();
    test_is_not_move_constructible_cv<int() volatile && noexcept>();
    test_is_not_move_constructible_cv<int() const volatile noexcept>();
    test_is_not_move_constructible_cv<int() const volatile & noexcept>();
    test_is_not_move_constructible_cv<int() const volatile && noexcept>();

    test_is_not_move_constructible_cv<int(int)>();
    test_is_not_move_constructible_cv<int(int)&>();
    test_is_not_move_constructible_cv<int(int) &&>();
    test_is_not_move_constructible_cv<int(int) const>();
    test_is_not_move_constructible_cv<int(int) const&>();
    test_is_not_move_constructible_cv<int(int) const&&>();
    test_is_not_move_constructible_cv<int(int) volatile>();
    test_is_not_move_constructible_cv<int(int) volatile&>();
    test_is_not_move_constructible_cv<int(int) volatile&&>();
    test_is_not_move_constructible_cv<int(int) const volatile>();
    test_is_not_move_constructible_cv<int(int) const volatile&>();
    test_is_not_move_constructible_cv<int(int) const volatile&&>();
    test_is_not_move_constructible_cv<int(int) noexcept>();
    test_is_not_move_constructible_cv<int(int) & noexcept>();
    test_is_not_move_constructible_cv<int(int) && noexcept>();
    test_is_not_move_constructible_cv<int(int) const noexcept>();
    test_is_not_move_constructible_cv<int(int) const & noexcept>();
    test_is_not_move_constructible_cv<int(int) const && noexcept>();
    test_is_not_move_constructible_cv<int(int) volatile noexcept>();
    test_is_not_move_constructible_cv<int(int) volatile & noexcept>();
    test_is_not_move_constructible_cv<int(int) volatile && noexcept>();
    test_is_not_move_constructible_cv<int(int) const volatile noexcept>();
    test_is_not_move_constructible_cv<int(int) const volatile & noexcept>();
    test_is_not_move_constructible_cv<int(int) const volatile && noexcept>();

    test_is_not_move_constructible_cv<int(...)>();
    test_is_not_move_constructible_cv<int(...)&>();
    test_is_not_move_constructible_cv<int(...) &&>();
    test_is_not_move_constructible_cv<int(...) const>();
    test_is_not_move_constructible_cv<int(...) const&>();
    test_is_not_move_constructible_cv<int(...) const&&>();
    test_is_not_move_constructible_cv<int(...) volatile>();
    test_is_not_move_constructible_cv<int(...) volatile&>();
    test_is_not_move_constructible_cv<int(...) volatile&&>();
    test_is_not_move_constructible_cv<int(...) const volatile>();
    test_is_not_move_constructible_cv<int(...) const volatile&>();
    test_is_not_move_constructible_cv<int(...) const volatile&&>();
    test_is_not_move_constructible_cv<int(...) noexcept>();
    test_is_not_move_constructible_cv<int(...) & noexcept>();
    test_is_not_move_constructible_cv<int(...) && noexcept>();
    test_is_not_move_constructible_cv<int(...) const noexcept>();
    test_is_not_move_constructible_cv<int(...) const & noexcept>();
    test_is_not_move_constructible_cv<int(...) const && noexcept>();
    test_is_not_move_constructible_cv<int(...) volatile noexcept>();
    test_is_not_move_constructible_cv<int(...) volatile & noexcept>();
    test_is_not_move_constructible_cv<int(...) volatile && noexcept>();
    test_is_not_move_constructible_cv<int(...) const volatile noexcept>();
    test_is_not_move_constructible_cv<int(...) const volatile & noexcept>();
    test_is_not_move_constructible_cv<int(...) const volatile && noexcept>();

    test_is_not_move_constructible_cv<int(int, ...)>();
    test_is_not_move_constructible_cv<int(int, ...)&>();
    test_is_not_move_constructible_cv<int(int, ...) &&>();
    test_is_not_move_constructible_cv<int(int, ...) const>();
    test_is_not_move_constructible_cv<int(int, ...) const&>();
    test_is_not_move_constructible_cv<int(int, ...) const&&>();
    test_is_not_move_constructible_cv<int(int, ...) volatile>();
    test_is_not_move_constructible_cv<int(int, ...) volatile&>();
    test_is_not_move_constructible_cv<int(int, ...) volatile&&>();
    test_is_not_move_constructible_cv<int(int, ...) const volatile>();
    test_is_not_move_constructible_cv<int(int, ...) const volatile&>();
    test_is_not_move_constructible_cv<int(int, ...) const volatile&&>();
    test_is_not_move_constructible_cv<int(int, ...) noexcept>();
    test_is_not_move_constructible_cv<int(int, ...) & noexcept>();
    test_is_not_move_constructible_cv<int(int, ...) && noexcept>();
    test_is_not_move_constructible_cv<int(int, ...) const noexcept>();
    test_is_not_move_constructible_cv<int(int, ...) const & noexcept>();
    test_is_not_move_constructible_cv<int(int, ...) const && noexcept>();
    test_is_not_move_constructible_cv<int(int, ...) volatile noexcept>();
    test_is_not_move_constructible_cv<int(int, ...) volatile & noexcept>();
    test_is_not_move_constructible_cv<int(int, ...) volatile && noexcept>();
    test_is_not_move_constructible_cv<int(int, ...) const volatile noexcept>();
    test_is_not_move_constructible_cv<int(int, ...) const volatile & noexcept>();
    test_is_not_move_constructible_cv<int(int, ...) const volatile && noexcept>();

    test_is_move_constructible_cv<void (*)()>();
    test_is_move_constructible_cv<void (*)() noexcept>();

    test_is_move_constructible_cv<void (*)(int)>();
    test_is_move_constructible_cv<void (*)(int) noexcept>();

    test_is_move_constructible_cv<void (*)(...)>();
    test_is_move_constructible_cv<void (*)(...) noexcept>();

    test_is_move_constructible_cv<void (*)(int, ...)>();
    test_is_move_constructible_cv<void (*)(int, ...) noexcept>();

    test_is_move_constructible_cv<int (*)()>();
    test_is_move_constructible_cv<int (*)() noexcept>();

    test_is_move_constructible_cv<int (*)(int)>();
    test_is_move_constructible_cv<int (*)(int) noexcept>();

    test_is_move_constructible_cv<int (*)(...)>();
    test_is_move_constructible_cv<int (*)(...) noexcept>();

    test_is_move_constructible_cv<int (*)(int, ...)>();
    test_is_move_constructible_cv<int (*)(int, ...) noexcept>();

    test_is_move_constructible_cv<void (&)()>();
    test_is_move_constructible_cv<void (&)() noexcept>();

    test_is_move_constructible_cv<void (&)(int)>();
    test_is_move_constructible_cv<void (&)(int) noexcept>();

    test_is_move_constructible_cv<void (&)(...)>();
    test_is_move_constructible_cv<void (&)(...) noexcept>();

    test_is_move_constructible_cv<void (&)(int, ...)>();
    test_is_move_constructible_cv<void (&)(int, ...) noexcept>();

    test_is_move_constructible_cv<int (&)()>();
    test_is_move_constructible_cv<int (&)() noexcept>();

    test_is_move_constructible_cv<int (&)(int)>();
    test_is_move_constructible_cv<int (&)(int) noexcept>();

    test_is_move_constructible_cv<int (&)(...)>();
    test_is_move_constructible_cv<int (&)(...) noexcept>();

    test_is_move_constructible_cv<int (&)(int, ...)>();
    test_is_move_constructible_cv<int (&)(int, ...) noexcept>();

    test_is_move_constructible_cv<void (&&)()>();
    test_is_move_constructible_cv<void (&&)() noexcept>();

    test_is_move_constructible_cv<void (&&)(int)>();
    test_is_move_constructible_cv<void (&&)(int) noexcept>();

    test_is_move_constructible_cv<void (&&)(...)>();
    test_is_move_constructible_cv<void (&&)(...) noexcept>();

    test_is_move_constructible_cv<void (&&)(int, ...)>();
    test_is_move_constructible_cv<void (&&)(int, ...) noexcept>();

    test_is_move_constructible_cv<int (&&)()>();
    test_is_move_constructible_cv<int (&&)() noexcept>();

    test_is_move_constructible_cv<int (&&)(int)>();
    test_is_move_constructible_cv<int (&&)(int) noexcept>();

    test_is_move_constructible_cv<int (&&)(...)>();
    test_is_move_constructible_cv<int (&&)(...) noexcept>();

    test_is_move_constructible_cv<int (&&)(int, ...)>();
    test_is_move_constructible_cv<int (&&)(int, ...) noexcept>();

    test_is_move_constructible_cv<void (class_type::*)()>();
    test_is_move_constructible_cv<void (class_type::*)()&>();
    test_is_move_constructible_cv<void (class_type::*)() &&>();
    test_is_move_constructible_cv<void (class_type::*)() const>();
    test_is_move_constructible_cv<void (class_type::*)() const&>();
    test_is_move_constructible_cv<void (class_type::*)() const&&>();
    test_is_move_constructible_cv<void (class_type::*)() noexcept>();
    test_is_move_constructible_cv<void (class_type::*)() & noexcept>();
    test_is_move_constructible_cv<void (class_type::*)() && noexcept>();
    test_is_move_constructible_cv<void (class_type::*)() const noexcept>();
    test_is_move_constructible_cv<void (class_type::*)() const & noexcept>();
    test_is_move_constructible_cv<void (class_type::*)() const && noexcept>();

    test_is_move_constructible_cv<void (class_type::*)(int)>();
    test_is_move_constructible_cv<void (class_type::*)(int)&>();
    test_is_move_constructible_cv<void (class_type::*)(int) &&>();
    test_is_move_constructible_cv<void (class_type::*)(int) const>();
    test_is_move_constructible_cv<void (class_type::*)(int) const&>();
    test_is_move_constructible_cv<void (class_type::*)(int) const&&>();
    test_is_move_constructible_cv<void (class_type::*)(int) noexcept>();
    test_is_move_constructible_cv<void (class_type::*)(int) & noexcept>();
    test_is_move_constructible_cv<void (class_type::*)(int) && noexcept>();
    test_is_move_constructible_cv<void (class_type::*)(int) const noexcept>();
    test_is_move_constructible_cv<void (class_type::*)(int) const & noexcept>();
    test_is_move_constructible_cv<void (class_type::*)(int) const && noexcept>();

    test_is_move_constructible_cv<void (class_type::*)(...)>();
    test_is_move_constructible_cv<void (class_type::*)(...)&>();
    test_is_move_constructible_cv<void (class_type::*)(...) &&>();
    test_is_move_constructible_cv<void (class_type::*)(...) const>();
    test_is_move_constructible_cv<void (class_type::*)(...) const&>();
    test_is_move_constructible_cv<void (class_type::*)(...) const&&>();
    test_is_move_constructible_cv<void (class_type::*)(...) noexcept>();
    test_is_move_constructible_cv<void (class_type::*)(...) & noexcept>();
    test_is_move_constructible_cv<void (class_type::*)(...) && noexcept>();
    test_is_move_constructible_cv<void (class_type::*)(...) const noexcept>();
    test_is_move_constructible_cv<void (class_type::*)(...) const & noexcept>();
    test_is_move_constructible_cv<void (class_type::*)(...) const && noexcept>();

    test_is_move_constructible_cv<void (class_type::*)(int, ...)>();
    test_is_move_constructible_cv<void (class_type::*)(int, ...)&>();
    test_is_move_constructible_cv<void (class_type::*)(int, ...) &&>();
    test_is_move_constructible_cv<void (class_type::*)(int, ...) const>();
    test_is_move_constructible_cv<void (class_type::*)(int, ...) const&>();
    test_is_move_constructible_cv<void (class_type::*)(int, ...) const&&>();
    test_is_move_constructible_cv<void (class_type::*)(int, ...) noexcept>();
    test_is_move_constructible_cv<void (class_type::*)(int, ...) & noexcept>();
    test_is_move_constructible_cv<void (class_type::*)(int, ...) && noexcept>();
    test_is_move_constructible_cv<void (class_type::*)(int, ...) const noexcept>();
    test_is_move_constructible_cv<void (class_type::*)(int, ...) const & noexcept>();
    test_is_move_constructible_cv<void (class_type::*)(int, ...) const && noexcept>();

    test_is_move_constructible_cv<int (class_type::*)()>();
    test_is_move_constructible_cv<int (class_type::*)()&>();
    test_is_move_constructible_cv<int (class_type::*)() &&>();
    test_is_move_constructible_cv<int (class_type::*)() const>();
    test_is_move_constructible_cv<int (class_type::*)() const&>();
    test_is_move_constructible_cv<int (class_type::*)() const&&>();
    test_is_move_constructible_cv<int (class_type::*)() noexcept>();
    test_is_move_constructible_cv<int (class_type::*)() & noexcept>();
    test_is_move_constructible_cv<int (class_type::*)() && noexcept>();
    test_is_move_constructible_cv<int (class_type::*)() const noexcept>();
    test_is_move_constructible_cv<int (class_type::*)() const & noexcept>();
    test_is_move_constructible_cv<int (class_type::*)() const && noexcept>();

    test_is_move_constructible_cv<int (class_type::*)(int)>();
    test_is_move_constructible_cv<int (class_type::*)(int)&>();
    test_is_move_constructible_cv<int (class_type::*)(int) &&>();
    test_is_move_constructible_cv<int (class_type::*)(int) const>();
    test_is_move_constructible_cv<int (class_type::*)(int) const&>();
    test_is_move_constructible_cv<int (class_type::*)(int) const&&>();
    test_is_move_constructible_cv<int (class_type::*)(int) noexcept>();
    test_is_move_constructible_cv<int (class_type::*)(int) & noexcept>();
    test_is_move_constructible_cv<int (class_type::*)(int) && noexcept>();
    test_is_move_constructible_cv<int (class_type::*)(int) const noexcept>();
    test_is_move_constructible_cv<int (class_type::*)(int) const & noexcept>();
    test_is_move_constructible_cv<int (class_type::*)(int) const && noexcept>();

    test_is_move_constructible_cv<int (class_type::*)(...)>();
    test_is_move_constructible_cv<int (class_type::*)(...)&>();
    test_is_move_constructible_cv<int (class_type::*)(...) &&>();
    test_is_move_constructible_cv<int (class_type::*)(...) const>();
    test_is_move_constructible_cv<int (class_type::*)(...) const&>();
    test_is_move_constructible_cv<int (class_type::*)(...) const&&>();
    test_is_move_constructible_cv<int (class_type::*)(...) noexcept>();
    test_is_move_constructible_cv<int (class_type::*)(...) & noexcept>();
    test_is_move_constructible_cv<int (class_type::*)(...) && noexcept>();
    test_is_move_constructible_cv<int (class_type::*)(...) const noexcept>();
    test_is_move_constructible_cv<int (class_type::*)(...) const & noexcept>();
    test_is_move_constructible_cv<int (class_type::*)(...) const && noexcept>();

    test_is_move_constructible_cv<int (class_type::*)(int, ...)>();
    test_is_move_constructible_cv<int (class_type::*)(int, ...)&>();
    test_is_move_constructible_cv<int (class_type::*)(int, ...) &&>();
    test_is_move_constructible_cv<int (class_type::*)(int, ...) const>();
    test_is_move_constructible_cv<int (class_type::*)(int, ...) const&>();
    test_is_move_constructible_cv<int (class_type::*)(int, ...) const&&>();
    test_is_move_constructible_cv<int (class_type::*)(int, ...) noexcept>();
    test_is_move_constructible_cv<int (class_type::*)(int, ...) & noexcept>();
    test_is_move_constructible_cv<int (class_type::*)(int, ...) && noexcept>();
    test_is_move_constructible_cv<int (class_type::*)(int, ...) const noexcept>();
    test_is_move_constructible_cv<int (class_type::*)(int, ...) const & noexcept>();
    test_is_move_constructible_cv<int (class_type::*)(int, ...) const && noexcept>();
}
