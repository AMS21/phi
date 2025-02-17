#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/compiler_support/noexcept.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_copy_assignable.hpp>
#include <phi/type_traits/is_nothrow_copy_assignable.hpp>
#include <type_traits>
#include <vector>

template <typename TypeT>
void test_is_nothrow_copy_assignable_impl()
{
    STATIC_REQUIRE(phi::is_nothrow_copy_assignable<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_nothrow_copy_assignable<TypeT>::value);
    STATIC_REQUIRE(phi::is_copy_assignable<TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_nothrow_copy_assignable_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_not_nothrow_copy_assignable_v<TypeT>);
    STATIC_REQUIRE(phi::is_copy_assignable_v<TypeT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_nothrow_copy_assignable<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_nothrow_copy_assignable<TypeT>);

    // Standard compatibility
    STATIC_REQUIRE(std::is_copy_assignable<TypeT>::value);
    STATIC_REQUIRE(std::is_nothrow_copy_assignable<TypeT>::value);
}

template <typename TypeT>
void test_is_not_nothrow_copy_assignable_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_nothrow_copy_assignable<TypeT>::value);
    STATIC_REQUIRE(phi::is_not_nothrow_copy_assignable<TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_nothrow_copy_assignable_v<TypeT>);
    STATIC_REQUIRE(phi::is_not_nothrow_copy_assignable_v<TypeT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_nothrow_copy_assignable<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_nothrow_copy_assignable<TypeT>);

    // Standard compatibility
    STATIC_REQUIRE_FALSE(std::is_nothrow_copy_assignable<TypeT>::value);
}

template <typename TypeT>
void test_is_nothrow_copy_assignable()
{
    test_is_nothrow_copy_assignable_impl<TypeT>();
    test_is_not_nothrow_copy_assignable_impl<const TypeT>();
    test_is_not_nothrow_copy_assignable_impl<volatile TypeT>();
    test_is_not_nothrow_copy_assignable_impl<const volatile TypeT>();
}

template <typename TypeT>
void test_is_nothrow_copy_assignable_v()
{
    test_is_nothrow_copy_assignable_impl<TypeT>();
    test_is_not_nothrow_copy_assignable_impl<const TypeT>();
    test_is_nothrow_copy_assignable_impl<volatile TypeT>();
    test_is_not_nothrow_copy_assignable_impl<const volatile TypeT>();
}

template <typename TypeT>
void test_is_nothrow_copy_assignable_cv()
{
    test_is_nothrow_copy_assignable_impl<TypeT>();
    test_is_nothrow_copy_assignable_impl<const TypeT>();
    test_is_nothrow_copy_assignable_impl<volatile TypeT>();
    test_is_nothrow_copy_assignable_impl<const volatile TypeT>();
}

template <typename TypeT>
void test_is_not_nothrow_copy_assignable_cv()
{
    test_is_not_nothrow_copy_assignable_impl<TypeT>();
    test_is_not_nothrow_copy_assignable_impl<const TypeT>();
    test_is_not_nothrow_copy_assignable_impl<volatile TypeT>();
    test_is_not_nothrow_copy_assignable_impl<const volatile TypeT>();
}

struct A
{
    A& operator=(const A&);
};

struct B
{
    B& operator=(const B&) PHI_NOEXCEPT;
};

struct C
{
    C& operator=(const C&) = delete;
};

struct D
{
    D& operator=(const D&) = default;
};

TEST_CASE("is_nothrow_copy_assignable")
{
    test_is_not_nothrow_copy_assignable_cv<A>();
    test_is_nothrow_copy_assignable<B>();
    test_is_not_nothrow_copy_assignable_cv<C>();
    test_is_nothrow_copy_assignable<D>();

    test_is_not_nothrow_copy_assignable_cv<void>();
    test_is_nothrow_copy_assignable_v<phi::nullptr_t>();
    test_is_nothrow_copy_assignable_v<bool>();
    test_is_nothrow_copy_assignable_v<char>();
    test_is_nothrow_copy_assignable_v<signed char>();
    test_is_nothrow_copy_assignable_v<unsigned char>();
    test_is_nothrow_copy_assignable_v<short>();
    test_is_nothrow_copy_assignable_v<unsigned short>();
    test_is_nothrow_copy_assignable_v<int>();
    test_is_nothrow_copy_assignable_v<unsigned int>();
    test_is_nothrow_copy_assignable_v<long>();
    test_is_nothrow_copy_assignable_v<unsigned long>();
    test_is_nothrow_copy_assignable_v<long long>();
    test_is_nothrow_copy_assignable_v<unsigned long long>();
    test_is_nothrow_copy_assignable_v<float>();
    test_is_nothrow_copy_assignable_v<double>();
    test_is_nothrow_copy_assignable_v<long double>();
    test_is_nothrow_copy_assignable_v<char8_t>();
    test_is_nothrow_copy_assignable_v<char16_t>();
    test_is_nothrow_copy_assignable_v<char32_t>();
    test_is_nothrow_copy_assignable_v<wchar_t>();

    test_is_nothrow_copy_assignable<phi::boolean>();
    test_is_nothrow_copy_assignable<phi::integer<signed char>>();
    test_is_nothrow_copy_assignable<phi::integer<unsigned char>>();
    test_is_nothrow_copy_assignable<phi::integer<short>>();
    test_is_nothrow_copy_assignable<phi::integer<unsigned short>>();
    test_is_nothrow_copy_assignable<phi::integer<int>>();
    test_is_nothrow_copy_assignable<phi::integer<unsigned int>>();
    test_is_nothrow_copy_assignable<phi::integer<long>>();
    test_is_nothrow_copy_assignable<phi::integer<unsigned long>>();
    test_is_nothrow_copy_assignable<phi::integer<long long>>();
    test_is_nothrow_copy_assignable<phi::integer<unsigned long long>>();
    test_is_nothrow_copy_assignable<phi::floating_point<float>>();
    test_is_nothrow_copy_assignable<phi::floating_point<double>>();
    test_is_nothrow_copy_assignable<phi::floating_point<long double>>();

    test_is_not_nothrow_copy_assignable_cv<std::vector<int>>();
    test_is_not_nothrow_copy_assignable_cv<phi::scope_ptr<int>>();

    test_is_nothrow_copy_assignable_cv<int&>();
    test_is_not_nothrow_copy_assignable_cv<const int&>();
    test_is_nothrow_copy_assignable_cv<volatile int&>();
    test_is_not_nothrow_copy_assignable_cv<const volatile int&>();
    test_is_nothrow_copy_assignable_cv<int&&>();
    test_is_not_nothrow_copy_assignable_cv<const int&&>();
    test_is_nothrow_copy_assignable_cv<volatile int&&>();
    test_is_not_nothrow_copy_assignable_cv<const volatile int&&>();
    test_is_nothrow_copy_assignable_v<int*>();
    test_is_nothrow_copy_assignable_v<const int*>();
    test_is_nothrow_copy_assignable_v<volatile int*>();
    test_is_nothrow_copy_assignable_v<const volatile int*>();
    test_is_nothrow_copy_assignable_v<int**>();
    test_is_nothrow_copy_assignable_v<const int**>();
    test_is_nothrow_copy_assignable_v<volatile int**>();
    test_is_nothrow_copy_assignable_v<const volatile int**>();
    test_is_nothrow_copy_assignable_cv<int*&>();
    test_is_nothrow_copy_assignable_cv<const int*&>();
    test_is_nothrow_copy_assignable_cv<volatile int*&>();
    test_is_nothrow_copy_assignable_cv<const volatile int*&>();
    test_is_nothrow_copy_assignable_cv<int*&&>();
    test_is_nothrow_copy_assignable_cv<const int*&&>();
    test_is_nothrow_copy_assignable_cv<volatile int*&&>();
    test_is_nothrow_copy_assignable_cv<const volatile int*&&>();
    test_is_nothrow_copy_assignable_v<void*>();
    test_is_not_nothrow_copy_assignable_cv<char[3]>();
    test_is_not_nothrow_copy_assignable_cv<char[]>();
    test_is_not_nothrow_copy_assignable_cv<char* [3]>();
    test_is_not_nothrow_copy_assignable_cv<char*[]>();
    test_is_nothrow_copy_assignable_v<int(*)[3]>();
    test_is_nothrow_copy_assignable_v<int(*)[]>();
    test_is_not_nothrow_copy_assignable_cv<int(&)[3]>();
    test_is_not_nothrow_copy_assignable_cv<int(&)[]>();
    test_is_not_nothrow_copy_assignable_cv<int(&&)[3]>();
    test_is_not_nothrow_copy_assignable_cv<int(&&)[]>();
    test_is_not_nothrow_copy_assignable_cv<char[3][2]>();
    test_is_not_nothrow_copy_assignable_cv<char[][2]>();
    test_is_not_nothrow_copy_assignable_cv<char* [3][2]>();
    test_is_not_nothrow_copy_assignable_cv<char*[][2]>();
    test_is_nothrow_copy_assignable_v<int(*)[3][2]>();
    test_is_nothrow_copy_assignable_v<int(*)[][2]>();
    test_is_not_nothrow_copy_assignable_cv<int(&)[3][2]>();
    test_is_not_nothrow_copy_assignable_cv<int(&)[][2]>();
    test_is_not_nothrow_copy_assignable_cv<int(&&)[3][2]>();
    test_is_not_nothrow_copy_assignable_cv<int(&&)[][2]>();
    test_is_nothrow_copy_assignable<class_type>();
    test_is_not_nothrow_copy_assignable_cv<class_type[]>();
    test_is_not_nothrow_copy_assignable_cv<class_type[2]>();
    test_is_nothrow_copy_assignable<template_type<void>>();
    test_is_nothrow_copy_assignable<template_type<int>>();
    test_is_nothrow_copy_assignable<template_type<class_type>>();
    test_is_nothrow_copy_assignable<template_type<incomplete_type>>();
    test_is_nothrow_copy_assignable<variadic_template<>>();
    test_is_nothrow_copy_assignable<variadic_template<void>>();
    test_is_nothrow_copy_assignable<variadic_template<int>>();
    test_is_nothrow_copy_assignable<variadic_template<class_type>>();
    test_is_nothrow_copy_assignable<variadic_template<incomplete_type>>();
    test_is_nothrow_copy_assignable<variadic_template<int, void, class_type, volatile char[]>>();
    test_is_nothrow_copy_assignable<public_derived_from<base>>();
    test_is_nothrow_copy_assignable<public_derived_from<derived>>();
    test_is_nothrow_copy_assignable<public_derived_from<class_type>>();
    test_is_nothrow_copy_assignable<private_derived_from<base>>();
    test_is_nothrow_copy_assignable<private_derived_from<derived>>();
    test_is_nothrow_copy_assignable<private_derived_from<class_type>>();
    test_is_nothrow_copy_assignable<protected_derived_from<base>>();
    test_is_nothrow_copy_assignable<protected_derived_from<derived>>();
    test_is_nothrow_copy_assignable<protected_derived_from<class_type>>();
    test_is_nothrow_copy_assignable<union_type>();
    test_is_nothrow_copy_assignable<non_empty_union>();
    test_is_nothrow_copy_assignable<empty>();
    test_is_nothrow_copy_assignable<not_empty>();
    test_is_nothrow_copy_assignable<bit_zero>();
    test_is_nothrow_copy_assignable<bit_one>();
    test_is_nothrow_copy_assignable<base>();
    test_is_nothrow_copy_assignable<derived>();
    test_is_nothrow_copy_assignable<abstract>();
    test_is_nothrow_copy_assignable<public_abstract>();
    test_is_nothrow_copy_assignable<private_abstract>();
    test_is_nothrow_copy_assignable<protected_abstract>();
    test_is_nothrow_copy_assignable<abstract_template<int>>();
    test_is_nothrow_copy_assignable<abstract_template<double>>();
    test_is_nothrow_copy_assignable<abstract_template<class_type>>();
    test_is_nothrow_copy_assignable<abstract_template<incomplete_type>>();
    test_is_nothrow_copy_assignable<final_type>();
    test_is_nothrow_copy_assignable<public_destructor>();
    test_is_nothrow_copy_assignable<protected_destructor>();
    test_is_nothrow_copy_assignable<private_destructor>();
    test_is_nothrow_copy_assignable<virtual_public_destructor>();
    test_is_nothrow_copy_assignable<virtual_protected_destructor>();
    test_is_nothrow_copy_assignable<virtual_private_destructor>();
    test_is_nothrow_copy_assignable<pure_public_destructor>();
    test_is_nothrow_copy_assignable<pure_protected_destructor>();
    test_is_nothrow_copy_assignable<pure_private_destructor>();
    test_is_nothrow_copy_assignable<deleted_public_destructor>();
    test_is_nothrow_copy_assignable<deleted_protected_destructor>();
    test_is_nothrow_copy_assignable<deleted_private_destructor>();
    test_is_nothrow_copy_assignable<deleted_virtual_public_destructor>();
    test_is_nothrow_copy_assignable<deleted_virtual_protected_destructor>();
    test_is_nothrow_copy_assignable<deleted_virtual_private_destructor>();
    test_is_nothrow_copy_assignable_v<Enum>();
    test_is_nothrow_copy_assignable_v<EnumSigned>();
    test_is_nothrow_copy_assignable_v<EnumUnsigned>();
    test_is_nothrow_copy_assignable_v<EnumClass>();
    test_is_nothrow_copy_assignable_v<EnumStruct>();
    test_is_not_nothrow_copy_assignable_cv<function_type>();
    test_is_nothrow_copy_assignable_v<function_ptr>();
    test_is_nothrow_copy_assignable_v<member_object_ptr>();
    test_is_nothrow_copy_assignable_v<member_function_ptr>();
    test_is_nothrow_copy_assignable_v<int class_type::*>();
    test_is_nothrow_copy_assignable_v<float class_type::*>();
    test_is_nothrow_copy_assignable_v<void * class_type::*>();
    test_is_nothrow_copy_assignable_v<int * class_type::*>();
    test_is_nothrow_copy_assignable_cv<int class_type::*&>();
    test_is_nothrow_copy_assignable_cv<float class_type::*&>();
    test_is_nothrow_copy_assignable_cv<void * class_type::*&>();
    test_is_nothrow_copy_assignable_cv<int * class_type::*&>();
    test_is_nothrow_copy_assignable_cv<int class_type::*&&>();
    test_is_nothrow_copy_assignable_cv<float class_type::*&&>();
    test_is_nothrow_copy_assignable_cv<void * class_type::*&&>();
    test_is_nothrow_copy_assignable_cv<int * class_type::*&&>();
    test_is_not_nothrow_copy_assignable_cv<int class_type::* const>();
    test_is_not_nothrow_copy_assignable_cv<float class_type::* const>();
    test_is_not_nothrow_copy_assignable_cv<void * class_type::* const>();
    test_is_not_nothrow_copy_assignable_cv<int class_type::* const&>();
    test_is_not_nothrow_copy_assignable_cv<float class_type::* const&>();
    test_is_not_nothrow_copy_assignable_cv<void * class_type::* const&>();
    test_is_not_nothrow_copy_assignable_cv<int class_type::* const&&>();
    test_is_not_nothrow_copy_assignable_cv<float class_type::* const&&>();
    test_is_not_nothrow_copy_assignable_cv<void * class_type::* const&&>();
    test_is_nothrow_copy_assignable_v<int class_type::* volatile>();
    test_is_nothrow_copy_assignable_v<float class_type::* volatile>();
    test_is_nothrow_copy_assignable_v<void * class_type::* volatile>();
    test_is_nothrow_copy_assignable_cv<int class_type::* volatile&>();
    test_is_nothrow_copy_assignable_cv<float class_type::* volatile&>();
    test_is_nothrow_copy_assignable_cv<void * class_type::* volatile&>();
    test_is_nothrow_copy_assignable_cv<int class_type::* volatile&&>();
    test_is_nothrow_copy_assignable_cv<float class_type::* volatile&&>();
    test_is_nothrow_copy_assignable_cv<void * class_type::* volatile&&>();
    test_is_not_nothrow_copy_assignable_cv<int class_type::* const volatile>();
    test_is_not_nothrow_copy_assignable_cv<float class_type::* const volatile>();
    test_is_not_nothrow_copy_assignable_cv<void * class_type::* const volatile>();
    test_is_not_nothrow_copy_assignable_cv<int class_type::* const volatile&>();
    test_is_not_nothrow_copy_assignable_cv<float class_type::* const volatile&>();
    test_is_not_nothrow_copy_assignable_cv<void * class_type::* const volatile&>();
    test_is_not_nothrow_copy_assignable_cv<int class_type::* const volatile&&>();
    test_is_not_nothrow_copy_assignable_cv<float class_type::* const volatile&&>();
    test_is_not_nothrow_copy_assignable_cv<void * class_type::* const volatile&&>();
    test_is_not_nothrow_copy_assignable_cv<non_copyable>();
    test_is_nothrow_copy_assignable<non_moveable>();
    test_is_not_nothrow_copy_assignable_cv<non_constructible>();
    test_is_nothrow_copy_assignable<tracked>();
    test_is_nothrow_copy_assignable<trap_constructible>();
    test_is_nothrow_copy_assignable<trap_implicit_conversion>();
    test_is_nothrow_copy_assignable<trap_comma>();
    test_is_nothrow_copy_assignable<trap_call>();
    test_is_nothrow_copy_assignable<trap_self_assign>();
    test_is_nothrow_copy_assignable<trap_deref>();
    test_is_nothrow_copy_assignable<trap_array_subscript>();

    test_is_not_nothrow_copy_assignable_cv<void()>();
    test_is_not_nothrow_copy_assignable_cv<void()&>();
    test_is_not_nothrow_copy_assignable_cv<void() &&>();
    test_is_not_nothrow_copy_assignable_cv<void() const>();
    test_is_not_nothrow_copy_assignable_cv<void() const&>();
    test_is_not_nothrow_copy_assignable_cv<void() const&&>();
    test_is_not_nothrow_copy_assignable_cv<void() volatile>();
    test_is_not_nothrow_copy_assignable_cv<void() volatile&>();
    test_is_not_nothrow_copy_assignable_cv<void() volatile&&>();
    test_is_not_nothrow_copy_assignable_cv<void() const volatile>();
    test_is_not_nothrow_copy_assignable_cv<void() const volatile&>();
    test_is_not_nothrow_copy_assignable_cv<void() const volatile&&>();
    test_is_not_nothrow_copy_assignable_cv<void() noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void() & noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void() && noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void() const noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void() const & noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void() const && noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void() volatile noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void() volatile & noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void() volatile && noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void() const volatile noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void() const volatile & noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void() const volatile && noexcept>();

    test_is_not_nothrow_copy_assignable_cv<void(int)>();
    test_is_not_nothrow_copy_assignable_cv<void(int)&>();
    test_is_not_nothrow_copy_assignable_cv<void(int) &&>();
    test_is_not_nothrow_copy_assignable_cv<void(int) const>();
    test_is_not_nothrow_copy_assignable_cv<void(int) const&>();
    test_is_not_nothrow_copy_assignable_cv<void(int) const&&>();
    test_is_not_nothrow_copy_assignable_cv<void(int) volatile>();
    test_is_not_nothrow_copy_assignable_cv<void(int) volatile&>();
    test_is_not_nothrow_copy_assignable_cv<void(int) volatile&&>();
    test_is_not_nothrow_copy_assignable_cv<void(int) const volatile>();
    test_is_not_nothrow_copy_assignable_cv<void(int) const volatile&>();
    test_is_not_nothrow_copy_assignable_cv<void(int) const volatile&&>();
    test_is_not_nothrow_copy_assignable_cv<void(int) noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void(int) & noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void(int) && noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void(int) const noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void(int) const & noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void(int) const && noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void(int) volatile noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void(int) volatile & noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void(int) volatile && noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void(int) const volatile noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void(int) const volatile & noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void(int) const volatile && noexcept>();

    test_is_not_nothrow_copy_assignable_cv<void(...)>();
    test_is_not_nothrow_copy_assignable_cv<void(...)&>();
    test_is_not_nothrow_copy_assignable_cv<void(...) &&>();
    test_is_not_nothrow_copy_assignable_cv<void(...) const>();
    test_is_not_nothrow_copy_assignable_cv<void(...) const&>();
    test_is_not_nothrow_copy_assignable_cv<void(...) const&&>();
    test_is_not_nothrow_copy_assignable_cv<void(...) volatile>();
    test_is_not_nothrow_copy_assignable_cv<void(...) volatile&>();
    test_is_not_nothrow_copy_assignable_cv<void(...) volatile&&>();
    test_is_not_nothrow_copy_assignable_cv<void(...) const volatile>();
    test_is_not_nothrow_copy_assignable_cv<void(...) const volatile&>();
    test_is_not_nothrow_copy_assignable_cv<void(...) const volatile&&>();
    test_is_not_nothrow_copy_assignable_cv<void(...) noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void(...) & noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void(...) && noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void(...) const noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void(...) const & noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void(...) const && noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void(...) volatile noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void(...) volatile & noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void(...) volatile && noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void(...) const volatile noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void(...) const volatile & noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void(...) const volatile && noexcept>();

    test_is_not_nothrow_copy_assignable_cv<void(int, ...)>();
    test_is_not_nothrow_copy_assignable_cv<void(int, ...)&>();
    test_is_not_nothrow_copy_assignable_cv<void(int, ...) &&>();
    test_is_not_nothrow_copy_assignable_cv<void(int, ...) const>();
    test_is_not_nothrow_copy_assignable_cv<void(int, ...) const&>();
    test_is_not_nothrow_copy_assignable_cv<void(int, ...) const&&>();
    test_is_not_nothrow_copy_assignable_cv<void(int, ...) volatile>();
    test_is_not_nothrow_copy_assignable_cv<void(int, ...) volatile&>();
    test_is_not_nothrow_copy_assignable_cv<void(int, ...) volatile&&>();
    test_is_not_nothrow_copy_assignable_cv<void(int, ...) const volatile>();
    test_is_not_nothrow_copy_assignable_cv<void(int, ...) const volatile&>();
    test_is_not_nothrow_copy_assignable_cv<void(int, ...) const volatile&&>();
    test_is_not_nothrow_copy_assignable_cv<void(int, ...) noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void(int, ...) & noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void(int, ...) && noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void(int, ...) const noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void(int, ...) const & noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void(int, ...) const && noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void(int, ...) volatile noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void(int, ...) volatile & noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void(int, ...) volatile && noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void(int, ...) const volatile noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void(int, ...) const volatile & noexcept>();
    test_is_not_nothrow_copy_assignable_cv<void(int, ...) const volatile && noexcept>();

    test_is_not_nothrow_copy_assignable_cv<int()>();
    test_is_not_nothrow_copy_assignable_cv<int()&>();
    test_is_not_nothrow_copy_assignable_cv<int() &&>();
    test_is_not_nothrow_copy_assignable_cv<int() const>();
    test_is_not_nothrow_copy_assignable_cv<int() const&>();
    test_is_not_nothrow_copy_assignable_cv<int() const&&>();
    test_is_not_nothrow_copy_assignable_cv<int() volatile>();
    test_is_not_nothrow_copy_assignable_cv<int() volatile&>();
    test_is_not_nothrow_copy_assignable_cv<int() volatile&&>();
    test_is_not_nothrow_copy_assignable_cv<int() const volatile>();
    test_is_not_nothrow_copy_assignable_cv<int() const volatile&>();
    test_is_not_nothrow_copy_assignable_cv<int() const volatile&&>();
    test_is_not_nothrow_copy_assignable_cv<int() noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int() & noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int() && noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int() const noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int() const & noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int() const && noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int() volatile noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int() volatile & noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int() volatile && noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int() const volatile noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int() const volatile & noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int() const volatile && noexcept>();

    test_is_not_nothrow_copy_assignable_cv<int(int)>();
    test_is_not_nothrow_copy_assignable_cv<int(int)&>();
    test_is_not_nothrow_copy_assignable_cv<int(int) &&>();
    test_is_not_nothrow_copy_assignable_cv<int(int) const>();
    test_is_not_nothrow_copy_assignable_cv<int(int) const&>();
    test_is_not_nothrow_copy_assignable_cv<int(int) const&&>();
    test_is_not_nothrow_copy_assignable_cv<int(int) volatile>();
    test_is_not_nothrow_copy_assignable_cv<int(int) volatile&>();
    test_is_not_nothrow_copy_assignable_cv<int(int) volatile&&>();
    test_is_not_nothrow_copy_assignable_cv<int(int) const volatile>();
    test_is_not_nothrow_copy_assignable_cv<int(int) const volatile&>();
    test_is_not_nothrow_copy_assignable_cv<int(int) const volatile&&>();
    test_is_not_nothrow_copy_assignable_cv<int(int) noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int(int) & noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int(int) && noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int(int) const noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int(int) const & noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int(int) const && noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int(int) volatile noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int(int) volatile & noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int(int) volatile && noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int(int) const volatile noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int(int) const volatile & noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int(int) const volatile && noexcept>();

    test_is_not_nothrow_copy_assignable_cv<int(...)>();
    test_is_not_nothrow_copy_assignable_cv<int(...)&>();
    test_is_not_nothrow_copy_assignable_cv<int(...) &&>();
    test_is_not_nothrow_copy_assignable_cv<int(...) const>();
    test_is_not_nothrow_copy_assignable_cv<int(...) const&>();
    test_is_not_nothrow_copy_assignable_cv<int(...) const&&>();
    test_is_not_nothrow_copy_assignable_cv<int(...) volatile>();
    test_is_not_nothrow_copy_assignable_cv<int(...) volatile&>();
    test_is_not_nothrow_copy_assignable_cv<int(...) volatile&&>();
    test_is_not_nothrow_copy_assignable_cv<int(...) const volatile>();
    test_is_not_nothrow_copy_assignable_cv<int(...) const volatile&>();
    test_is_not_nothrow_copy_assignable_cv<int(...) const volatile&&>();
    test_is_not_nothrow_copy_assignable_cv<int(...) noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int(...) & noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int(...) && noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int(...) const noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int(...) const & noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int(...) const && noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int(...) volatile noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int(...) volatile & noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int(...) volatile && noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int(...) const volatile noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int(...) const volatile & noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int(...) const volatile && noexcept>();

    test_is_not_nothrow_copy_assignable_cv<int(int, ...)>();
    test_is_not_nothrow_copy_assignable_cv<int(int, ...)&>();
    test_is_not_nothrow_copy_assignable_cv<int(int, ...) &&>();
    test_is_not_nothrow_copy_assignable_cv<int(int, ...) const>();
    test_is_not_nothrow_copy_assignable_cv<int(int, ...) const&>();
    test_is_not_nothrow_copy_assignable_cv<int(int, ...) const&&>();
    test_is_not_nothrow_copy_assignable_cv<int(int, ...) volatile>();
    test_is_not_nothrow_copy_assignable_cv<int(int, ...) volatile&>();
    test_is_not_nothrow_copy_assignable_cv<int(int, ...) volatile&&>();
    test_is_not_nothrow_copy_assignable_cv<int(int, ...) const volatile>();
    test_is_not_nothrow_copy_assignable_cv<int(int, ...) const volatile&>();
    test_is_not_nothrow_copy_assignable_cv<int(int, ...) const volatile&&>();
    test_is_not_nothrow_copy_assignable_cv<int(int, ...) noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int(int, ...) & noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int(int, ...) && noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int(int, ...) const noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int(int, ...) const & noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int(int, ...) const && noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int(int, ...) volatile noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int(int, ...) volatile & noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int(int, ...) volatile && noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int(int, ...) const volatile noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int(int, ...) const volatile & noexcept>();
    test_is_not_nothrow_copy_assignable_cv<int(int, ...) const volatile && noexcept>();

    test_is_nothrow_copy_assignable_v<void (*)()>();
    test_is_nothrow_copy_assignable_v<void (*)() noexcept>();

    test_is_nothrow_copy_assignable_v<void (*)(int)>();
    test_is_nothrow_copy_assignable_v<void (*)(int) noexcept>();

    test_is_nothrow_copy_assignable_v<void (*)(...)>();
    test_is_nothrow_copy_assignable_v<void (*)(...) noexcept>();

    test_is_nothrow_copy_assignable_v<void (*)(int, ...)>();
    test_is_nothrow_copy_assignable_v<void (*)(int, ...) noexcept>();

    test_is_nothrow_copy_assignable_v<int (*)()>();
    test_is_nothrow_copy_assignable_v<int (*)() noexcept>();

    test_is_nothrow_copy_assignable_v<int (*)(int)>();
    test_is_nothrow_copy_assignable_v<int (*)(int) noexcept>();

    test_is_nothrow_copy_assignable_v<int (*)(...)>();
    test_is_nothrow_copy_assignable_v<int (*)(...) noexcept>();

    test_is_nothrow_copy_assignable_v<int (*)(int, ...)>();
    test_is_nothrow_copy_assignable_v<int (*)(int, ...) noexcept>();

    test_is_not_nothrow_copy_assignable_cv<void (&)()>();
    test_is_not_nothrow_copy_assignable_cv<void (&)() noexcept>();

    test_is_not_nothrow_copy_assignable_cv<void (&)(int)>();
    test_is_not_nothrow_copy_assignable_cv<void (&)(int) noexcept>();

    test_is_not_nothrow_copy_assignable_cv<void (&)(...)>();
    test_is_not_nothrow_copy_assignable_cv<void (&)(...) noexcept>();

    test_is_not_nothrow_copy_assignable_cv<void (&)(int, ...)>();
    test_is_not_nothrow_copy_assignable_cv<void (&)(int, ...) noexcept>();

    test_is_not_nothrow_copy_assignable_cv<int (&)()>();
    test_is_not_nothrow_copy_assignable_cv<int (&)() noexcept>();

    test_is_not_nothrow_copy_assignable_cv<int (&)(int)>();
    test_is_not_nothrow_copy_assignable_cv<int (&)(int) noexcept>();

    test_is_not_nothrow_copy_assignable_cv<int (&)(...)>();
    test_is_not_nothrow_copy_assignable_cv<int (&)(...) noexcept>();

    test_is_not_nothrow_copy_assignable_cv<int (&)(int, ...)>();
    test_is_not_nothrow_copy_assignable_cv<int (&)(int, ...) noexcept>();

    test_is_not_nothrow_copy_assignable_cv<void (&&)()>();
    test_is_not_nothrow_copy_assignable_cv<void (&&)() noexcept>();

    test_is_not_nothrow_copy_assignable_cv<void (&&)(int)>();
    test_is_not_nothrow_copy_assignable_cv<void (&&)(int) noexcept>();

    test_is_not_nothrow_copy_assignable_cv<void (&&)(...)>();
    test_is_not_nothrow_copy_assignable_cv<void (&&)(...) noexcept>();

    test_is_not_nothrow_copy_assignable_cv<void (&&)(int, ...)>();
    test_is_not_nothrow_copy_assignable_cv<void (&&)(int, ...) noexcept>();

    test_is_not_nothrow_copy_assignable_cv<int (&&)()>();
    test_is_not_nothrow_copy_assignable_cv<int (&&)() noexcept>();

    test_is_not_nothrow_copy_assignable_cv<int (&&)(int)>();
    test_is_not_nothrow_copy_assignable_cv<int (&&)(int) noexcept>();

    test_is_not_nothrow_copy_assignable_cv<int (&&)(...)>();
    test_is_not_nothrow_copy_assignable_cv<int (&&)(...) noexcept>();

    test_is_not_nothrow_copy_assignable_cv<int (&&)(int, ...)>();
    test_is_not_nothrow_copy_assignable_cv<int (&&)(int, ...) noexcept>();

    test_is_nothrow_copy_assignable_v<void (class_type::*)()>();
    test_is_nothrow_copy_assignable_v<void (class_type::*)()&>();
    test_is_nothrow_copy_assignable_v<void (class_type::*)() &&>();
    test_is_nothrow_copy_assignable_v<void (class_type::*)() const>();
    test_is_nothrow_copy_assignable_v<void (class_type::*)() const&>();
    test_is_nothrow_copy_assignable_v<void (class_type::*)() const&&>();
    test_is_nothrow_copy_assignable_v<void (class_type::*)() noexcept>();
    test_is_nothrow_copy_assignable_v<void (class_type::*)() & noexcept>();
    test_is_nothrow_copy_assignable_v<void (class_type::*)() && noexcept>();
    test_is_nothrow_copy_assignable_v<void (class_type::*)() const noexcept>();
    test_is_nothrow_copy_assignable_v<void (class_type::*)() const & noexcept>();
    test_is_nothrow_copy_assignable_v<void (class_type::*)() const && noexcept>();

    test_is_nothrow_copy_assignable_v<void (class_type::*)(int)>();
    test_is_nothrow_copy_assignable_v<void (class_type::*)(int)&>();
    test_is_nothrow_copy_assignable_v<void (class_type::*)(int) &&>();
    test_is_nothrow_copy_assignable_v<void (class_type::*)(int) const>();
    test_is_nothrow_copy_assignable_v<void (class_type::*)(int) const&>();
    test_is_nothrow_copy_assignable_v<void (class_type::*)(int) const&&>();
    test_is_nothrow_copy_assignable_v<void (class_type::*)(int) noexcept>();
    test_is_nothrow_copy_assignable_v<void (class_type::*)(int) & noexcept>();
    test_is_nothrow_copy_assignable_v<void (class_type::*)(int) && noexcept>();
    test_is_nothrow_copy_assignable_v<void (class_type::*)(int) const noexcept>();
    test_is_nothrow_copy_assignable_v<void (class_type::*)(int) const & noexcept>();
    test_is_nothrow_copy_assignable_v<void (class_type::*)(int) const && noexcept>();

    test_is_nothrow_copy_assignable_v<void (class_type::*)(...)>();
    test_is_nothrow_copy_assignable_v<void (class_type::*)(...)&>();
    test_is_nothrow_copy_assignable_v<void (class_type::*)(...) &&>();
    test_is_nothrow_copy_assignable_v<void (class_type::*)(...) const>();
    test_is_nothrow_copy_assignable_v<void (class_type::*)(...) const&>();
    test_is_nothrow_copy_assignable_v<void (class_type::*)(...) const&&>();
    test_is_nothrow_copy_assignable_v<void (class_type::*)(...) noexcept>();
    test_is_nothrow_copy_assignable_v<void (class_type::*)(...) & noexcept>();
    test_is_nothrow_copy_assignable_v<void (class_type::*)(...) && noexcept>();
    test_is_nothrow_copy_assignable_v<void (class_type::*)(...) const noexcept>();
    test_is_nothrow_copy_assignable_v<void (class_type::*)(...) const & noexcept>();
    test_is_nothrow_copy_assignable_v<void (class_type::*)(...) const && noexcept>();

    test_is_nothrow_copy_assignable_v<void (class_type::*)(int, ...)>();
    test_is_nothrow_copy_assignable_v<void (class_type::*)(int, ...)&>();
    test_is_nothrow_copy_assignable_v<void (class_type::*)(int, ...) &&>();
    test_is_nothrow_copy_assignable_v<void (class_type::*)(int, ...) const>();
    test_is_nothrow_copy_assignable_v<void (class_type::*)(int, ...) const&>();
    test_is_nothrow_copy_assignable_v<void (class_type::*)(int, ...) const&&>();
    test_is_nothrow_copy_assignable_v<void (class_type::*)(int, ...) noexcept>();
    test_is_nothrow_copy_assignable_v<void (class_type::*)(int, ...) & noexcept>();
    test_is_nothrow_copy_assignable_v<void (class_type::*)(int, ...) && noexcept>();
    test_is_nothrow_copy_assignable_v<void (class_type::*)(int, ...) const noexcept>();
    test_is_nothrow_copy_assignable_v<void (class_type::*)(int, ...) const & noexcept>();
    test_is_nothrow_copy_assignable_v<void (class_type::*)(int, ...) const && noexcept>();

    test_is_nothrow_copy_assignable_v<int (class_type::*)()>();
    test_is_nothrow_copy_assignable_v<int (class_type::*)()&>();
    test_is_nothrow_copy_assignable_v<int (class_type::*)() &&>();
    test_is_nothrow_copy_assignable_v<int (class_type::*)() const>();
    test_is_nothrow_copy_assignable_v<int (class_type::*)() const&>();
    test_is_nothrow_copy_assignable_v<int (class_type::*)() const&&>();
    test_is_nothrow_copy_assignable_v<int (class_type::*)() noexcept>();
    test_is_nothrow_copy_assignable_v<int (class_type::*)() & noexcept>();
    test_is_nothrow_copy_assignable_v<int (class_type::*)() && noexcept>();
    test_is_nothrow_copy_assignable_v<int (class_type::*)() const noexcept>();
    test_is_nothrow_copy_assignable_v<int (class_type::*)() const & noexcept>();
    test_is_nothrow_copy_assignable_v<int (class_type::*)() const && noexcept>();

    test_is_nothrow_copy_assignable_v<int (class_type::*)(int)>();
    test_is_nothrow_copy_assignable_v<int (class_type::*)(int)&>();
    test_is_nothrow_copy_assignable_v<int (class_type::*)(int) &&>();
    test_is_nothrow_copy_assignable_v<int (class_type::*)(int) const>();
    test_is_nothrow_copy_assignable_v<int (class_type::*)(int) const&>();
    test_is_nothrow_copy_assignable_v<int (class_type::*)(int) const&&>();
    test_is_nothrow_copy_assignable_v<int (class_type::*)(int) noexcept>();
    test_is_nothrow_copy_assignable_v<int (class_type::*)(int) & noexcept>();
    test_is_nothrow_copy_assignable_v<int (class_type::*)(int) && noexcept>();
    test_is_nothrow_copy_assignable_v<int (class_type::*)(int) const noexcept>();
    test_is_nothrow_copy_assignable_v<int (class_type::*)(int) const & noexcept>();
    test_is_nothrow_copy_assignable_v<int (class_type::*)(int) const && noexcept>();

    test_is_nothrow_copy_assignable_v<int (class_type::*)(...)>();
    test_is_nothrow_copy_assignable_v<int (class_type::*)(...)&>();
    test_is_nothrow_copy_assignable_v<int (class_type::*)(...) &&>();
    test_is_nothrow_copy_assignable_v<int (class_type::*)(...) const>();
    test_is_nothrow_copy_assignable_v<int (class_type::*)(...) const&>();
    test_is_nothrow_copy_assignable_v<int (class_type::*)(...) const&&>();
    test_is_nothrow_copy_assignable_v<int (class_type::*)(...) noexcept>();
    test_is_nothrow_copy_assignable_v<int (class_type::*)(...) & noexcept>();
    test_is_nothrow_copy_assignable_v<int (class_type::*)(...) && noexcept>();
    test_is_nothrow_copy_assignable_v<int (class_type::*)(...) const noexcept>();
    test_is_nothrow_copy_assignable_v<int (class_type::*)(...) const & noexcept>();
    test_is_nothrow_copy_assignable_v<int (class_type::*)(...) const && noexcept>();

    test_is_nothrow_copy_assignable_v<int (class_type::*)(int, ...)>();
    test_is_nothrow_copy_assignable_v<int (class_type::*)(int, ...)&>();
    test_is_nothrow_copy_assignable_v<int (class_type::*)(int, ...) &&>();
    test_is_nothrow_copy_assignable_v<int (class_type::*)(int, ...) const>();
    test_is_nothrow_copy_assignable_v<int (class_type::*)(int, ...) const&>();
    test_is_nothrow_copy_assignable_v<int (class_type::*)(int, ...) const&&>();
    test_is_nothrow_copy_assignable_v<int (class_type::*)(int, ...) noexcept>();
    test_is_nothrow_copy_assignable_v<int (class_type::*)(int, ...) & noexcept>();
    test_is_nothrow_copy_assignable_v<int (class_type::*)(int, ...) && noexcept>();
    test_is_nothrow_copy_assignable_v<int (class_type::*)(int, ...) const noexcept>();
    test_is_nothrow_copy_assignable_v<int (class_type::*)(int, ...) const & noexcept>();
    test_is_nothrow_copy_assignable_v<int (class_type::*)(int, ...) const && noexcept>();
}
