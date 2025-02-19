#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_complete_or_unbounded.hpp>
#include <vector>

template <typename TypeT>
void test_is_complete_or_unbounded_impl()
{
    STATIC_REQUIRE(phi::is_complete_or_unbounded<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_complete_or_unbounded<TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_complete_or_unbounded_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_not_complete_or_unbounded_v<TypeT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_complete_or_unbounded<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_complete_or_unbounded<TypeT>);
}

template <typename TypeT>
void test_is_complete_or_unbounded()
{
    test_is_complete_or_unbounded_impl<TypeT>();
    test_is_complete_or_unbounded_impl<const TypeT>();
    test_is_complete_or_unbounded_impl<volatile TypeT>();
    test_is_complete_or_unbounded_impl<const volatile TypeT>();
}

template <typename TypeT>
void test_is_not_complete_or_unbounded_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_complete_or_unbounded<TypeT>::value);
    STATIC_REQUIRE(phi::is_not_complete_or_unbounded<TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_complete_or_unbounded_v<TypeT>);
    STATIC_REQUIRE(phi::is_not_complete_or_unbounded_v<TypeT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_complete_or_unbounded<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_complete_or_unbounded<TypeT>);
}

template <typename TypeT>
void test_is_not_complete_or_unbounded()
{
    test_is_not_complete_or_unbounded_impl<TypeT>();
    test_is_not_complete_or_unbounded_impl<const TypeT>();
    test_is_not_complete_or_unbounded_impl<volatile TypeT>();
    test_is_not_complete_or_unbounded_impl<const volatile TypeT>();
}

class A;

TEST_CASE("is_complete_or_unbounded")
{
    test_is_not_complete_or_unbounded<void>();
    test_is_complete_or_unbounded<phi::nullptr_t>();
    test_is_complete_or_unbounded<bool>();
    test_is_complete_or_unbounded<char>();
    test_is_complete_or_unbounded<signed char>();
    test_is_complete_or_unbounded<unsigned char>();
    test_is_complete_or_unbounded<short>();
    test_is_complete_or_unbounded<unsigned short>();
    test_is_complete_or_unbounded<int>();
    test_is_complete_or_unbounded<unsigned int>();
    test_is_complete_or_unbounded<long>();
    test_is_complete_or_unbounded<unsigned long>();
    test_is_complete_or_unbounded<long long>();
    test_is_complete_or_unbounded<unsigned long long>();
    test_is_complete_or_unbounded<float>();
    test_is_complete_or_unbounded<double>();
    test_is_complete_or_unbounded<long double>();
    test_is_complete_or_unbounded<char8_t>();
    test_is_complete_or_unbounded<char16_t>();
    test_is_complete_or_unbounded<char32_t>();
    test_is_complete_or_unbounded<wchar_t>();

    test_is_complete_or_unbounded<phi::boolean>();
    test_is_complete_or_unbounded<phi::integer<signed char>>();
    test_is_complete_or_unbounded<phi::integer<unsigned char>>();
    test_is_complete_or_unbounded<phi::integer<short>>();
    test_is_complete_or_unbounded<phi::integer<unsigned short>>();
    test_is_complete_or_unbounded<phi::integer<int>>();
    test_is_complete_or_unbounded<phi::integer<unsigned int>>();
    test_is_complete_or_unbounded<phi::integer<long>>();
    test_is_complete_or_unbounded<phi::integer<unsigned long>>();
    test_is_complete_or_unbounded<phi::integer<long long>>();
    test_is_complete_or_unbounded<phi::integer<unsigned long long>>();
    test_is_complete_or_unbounded<phi::floating_point<float>>();
    test_is_complete_or_unbounded<phi::floating_point<double>>();
    test_is_complete_or_unbounded<phi::floating_point<long double>>();

    test_is_complete_or_unbounded<std::vector<int>>();
    test_is_complete_or_unbounded<phi::scope_ptr<int>>();

    test_is_complete_or_unbounded<int&>();
    test_is_complete_or_unbounded<const int&>();
    test_is_complete_or_unbounded<volatile int&>();
    test_is_complete_or_unbounded<const volatile int&>();
    test_is_complete_or_unbounded<int&&>();
    test_is_complete_or_unbounded<const int&&>();
    test_is_complete_or_unbounded<volatile int&&>();
    test_is_complete_or_unbounded<const volatile int&&>();
    test_is_complete_or_unbounded<int*>();
    test_is_complete_or_unbounded<const int*>();
    test_is_complete_or_unbounded<volatile int*>();
    test_is_complete_or_unbounded<const volatile int*>();
    test_is_complete_or_unbounded<int**>();
    test_is_complete_or_unbounded<const int**>();
    test_is_complete_or_unbounded<volatile int**>();
    test_is_complete_or_unbounded<const volatile int**>();
    test_is_complete_or_unbounded<int*&>();
    test_is_complete_or_unbounded<const int*&>();
    test_is_complete_or_unbounded<volatile int*&>();
    test_is_complete_or_unbounded<const volatile int*&>();
    test_is_complete_or_unbounded<int*&&>();
    test_is_complete_or_unbounded<const int*&&>();
    test_is_complete_or_unbounded<volatile int*&&>();
    test_is_complete_or_unbounded<const volatile int*&&>();
    test_is_complete_or_unbounded<void*>();
    test_is_complete_or_unbounded<char[3]>();
    test_is_complete_or_unbounded<char[]>();
    test_is_complete_or_unbounded<char* [3]>();
    test_is_complete_or_unbounded<char*[]>();
    test_is_complete_or_unbounded<int(*)[3]>();
    test_is_complete_or_unbounded<int(*)[]>();
    test_is_complete_or_unbounded<int(&)[3]>();
    test_is_not_complete_or_unbounded<int(&)[]>();
    test_is_complete_or_unbounded<int(&&)[3]>();
    test_is_complete_or_unbounded<int(&&)[]>();
    test_is_complete_or_unbounded<char[3][2]>();
    test_is_complete_or_unbounded<char[][2]>();
    test_is_complete_or_unbounded<char* [3][2]>();
    test_is_complete_or_unbounded<char*[][2]>();
    test_is_complete_or_unbounded<int(*)[3][2]>();
    test_is_complete_or_unbounded<int(*)[][2]>();
    test_is_complete_or_unbounded<int(&)[3][2]>();
    test_is_not_complete_or_unbounded<int(&)[][2]>();
    test_is_complete_or_unbounded<int(&&)[3][2]>();
    test_is_complete_or_unbounded<int(&&)[][2]>();
    test_is_complete_or_unbounded<class_type>();
    test_is_complete_or_unbounded<class_type[]>();
    test_is_complete_or_unbounded<class_type[2]>();
    test_is_complete_or_unbounded<template_type<void>>();
    test_is_complete_or_unbounded<template_type<int>>();
    test_is_complete_or_unbounded<template_type<class_type>>();
    test_is_complete_or_unbounded<template_type<incomplete_type>>();
    test_is_complete_or_unbounded<variadic_template<>>();
    test_is_complete_or_unbounded<variadic_template<void>>();
    test_is_complete_or_unbounded<variadic_template<int>>();
    test_is_complete_or_unbounded<variadic_template<class_type>>();
    test_is_complete_or_unbounded<variadic_template<incomplete_type>>();
    test_is_complete_or_unbounded<variadic_template<int, void, class_type, volatile char[]>>();
    test_is_complete_or_unbounded<public_derived_from<base>>();
    test_is_complete_or_unbounded<public_derived_from<derived>>();
    test_is_complete_or_unbounded<public_derived_from<class_type>>();
    test_is_complete_or_unbounded<private_derived_from<base>>();
    test_is_complete_or_unbounded<private_derived_from<derived>>();
    test_is_complete_or_unbounded<private_derived_from<class_type>>();
    test_is_complete_or_unbounded<protected_derived_from<base>>();
    test_is_complete_or_unbounded<protected_derived_from<derived>>();
    test_is_complete_or_unbounded<protected_derived_from<class_type>>();
    test_is_complete_or_unbounded<union_type>();
    test_is_complete_or_unbounded<non_empty_union>();
    test_is_complete_or_unbounded<empty>();
    test_is_complete_or_unbounded<not_empty>();
    test_is_complete_or_unbounded<bit_zero>();
    test_is_complete_or_unbounded<bit_one>();
    test_is_complete_or_unbounded<base>();
    test_is_complete_or_unbounded<derived>();
    test_is_complete_or_unbounded<abstract>();
    test_is_complete_or_unbounded<public_abstract>();
    test_is_complete_or_unbounded<private_abstract>();
    test_is_complete_or_unbounded<protected_abstract>();
    test_is_complete_or_unbounded<abstract_template<int>>();
    test_is_complete_or_unbounded<abstract_template<double>>();
    test_is_complete_or_unbounded<abstract_template<class_type>>();
    test_is_complete_or_unbounded<abstract_template<incomplete_type>>();
    test_is_complete_or_unbounded<final_type>();
    test_is_complete_or_unbounded<public_destructor>();
    test_is_complete_or_unbounded<protected_destructor>();
    test_is_complete_or_unbounded<private_destructor>();
    test_is_complete_or_unbounded<virtual_public_destructor>();
    test_is_complete_or_unbounded<virtual_protected_destructor>();
    test_is_complete_or_unbounded<virtual_private_destructor>();
    test_is_complete_or_unbounded<pure_public_destructor>();
    test_is_complete_or_unbounded<pure_protected_destructor>();
    test_is_complete_or_unbounded<pure_private_destructor>();
    test_is_complete_or_unbounded<deleted_public_destructor>();
    test_is_complete_or_unbounded<deleted_protected_destructor>();
    test_is_complete_or_unbounded<deleted_private_destructor>();
    test_is_complete_or_unbounded<deleted_virtual_public_destructor>();
    test_is_complete_or_unbounded<deleted_virtual_protected_destructor>();
    test_is_complete_or_unbounded<deleted_virtual_private_destructor>();
    test_is_complete_or_unbounded<Enum>();
    test_is_complete_or_unbounded<EnumSigned>();
    test_is_complete_or_unbounded<EnumUnsigned>();
    test_is_complete_or_unbounded<EnumClass>();
    test_is_complete_or_unbounded<EnumStruct>();
    test_is_complete_or_unbounded<function_type>();
    test_is_complete_or_unbounded<function_ptr>();
    test_is_complete_or_unbounded<member_object_ptr>();
    test_is_complete_or_unbounded<member_function_ptr>();
    test_is_not_complete_or_unbounded<incomplete_type>();
    test_is_not_complete_or_unbounded<incomplete_template<void>>();
    test_is_not_complete_or_unbounded<incomplete_template<int>>();
    test_is_not_complete_or_unbounded<incomplete_template<class_type>>();
    test_is_not_complete_or_unbounded<incomplete_template<incomplete_type>>();
    test_is_not_complete_or_unbounded<incomplete_variadic_template<>>();
    test_is_not_complete_or_unbounded<incomplete_variadic_template<void>>();
    test_is_not_complete_or_unbounded<incomplete_variadic_template<int>>();
    test_is_not_complete_or_unbounded<incomplete_variadic_template<class_type>>();
    test_is_not_complete_or_unbounded<incomplete_variadic_template<incomplete_type>>();
    test_is_not_complete_or_unbounded<
            incomplete_variadic_template<int, void, class_type, volatile char[]>>();
    test_is_complete_or_unbounded<int class_type::*>();
    test_is_complete_or_unbounded<float class_type::*>();
    test_is_complete_or_unbounded<void * class_type::*>();
    test_is_complete_or_unbounded<int * class_type::*>();
    test_is_complete_or_unbounded<int class_type::*&>();
    test_is_complete_or_unbounded<float class_type::*&>();
    test_is_complete_or_unbounded<void * class_type::*&>();
    test_is_complete_or_unbounded<int * class_type::*&>();
    test_is_complete_or_unbounded<int class_type::*&&>();
    test_is_complete_or_unbounded<float class_type::*&&>();
    test_is_complete_or_unbounded<void * class_type::*&&>();
    test_is_complete_or_unbounded<int * class_type::*&&>();
    test_is_complete_or_unbounded<int class_type::* const>();
    test_is_complete_or_unbounded<float class_type::* const>();
    test_is_complete_or_unbounded<void * class_type::* const>();
    test_is_complete_or_unbounded<int class_type::* const&>();
    test_is_complete_or_unbounded<float class_type::* const&>();
    test_is_complete_or_unbounded<void * class_type::* const&>();
    test_is_complete_or_unbounded<int class_type::* const&&>();
    test_is_complete_or_unbounded<float class_type::* const&&>();
    test_is_complete_or_unbounded<void * class_type::* const&&>();
    test_is_complete_or_unbounded<int class_type::* volatile>();
    test_is_complete_or_unbounded<float class_type::* volatile>();
    test_is_complete_or_unbounded<void * class_type::* volatile>();
    test_is_complete_or_unbounded<int class_type::* volatile&>();
    test_is_complete_or_unbounded<float class_type::* volatile&>();
    test_is_complete_or_unbounded<void * class_type::* volatile&>();
    test_is_complete_or_unbounded<int class_type::* volatile&&>();
    test_is_complete_or_unbounded<float class_type::* volatile&&>();
    test_is_complete_or_unbounded<void * class_type::* volatile&&>();
    test_is_complete_or_unbounded<int class_type::* const volatile>();
    test_is_complete_or_unbounded<float class_type::* const volatile>();
    test_is_complete_or_unbounded<void * class_type::* const volatile>();
    test_is_complete_or_unbounded<int class_type::* const volatile&>();
    test_is_complete_or_unbounded<float class_type::* const volatile&>();
    test_is_complete_or_unbounded<void * class_type::* const volatile&>();
    test_is_complete_or_unbounded<int class_type::* const volatile&&>();
    test_is_complete_or_unbounded<float class_type::* const volatile&&>();
    test_is_complete_or_unbounded<void * class_type::* const volatile&&>();
    test_is_complete_or_unbounded<non_copyable>();
    test_is_complete_or_unbounded<non_moveable>();
    test_is_complete_or_unbounded<non_constructible>();
    test_is_complete_or_unbounded<tracked>();
    test_is_complete_or_unbounded<trap_constructible>();
    test_is_complete_or_unbounded<trap_implicit_conversion>();
    test_is_complete_or_unbounded<trap_comma>();
    test_is_complete_or_unbounded<trap_call>();
    test_is_complete_or_unbounded<trap_self_assign>();
    test_is_complete_or_unbounded<trap_deref>();
    test_is_complete_or_unbounded<trap_array_subscript>();

    test_is_complete_or_unbounded<void()>();
    test_is_complete_or_unbounded<void()&>();
    test_is_complete_or_unbounded<void() &&>();
    test_is_complete_or_unbounded<void() const>();
    test_is_complete_or_unbounded<void() const&>();
    test_is_complete_or_unbounded<void() const&&>();
    test_is_complete_or_unbounded<void() volatile>();
    test_is_complete_or_unbounded<void() volatile&>();
    test_is_complete_or_unbounded<void() volatile&&>();
    test_is_complete_or_unbounded<void() const volatile>();
    test_is_complete_or_unbounded<void() const volatile&>();
    test_is_complete_or_unbounded<void() const volatile&&>();
    test_is_complete_or_unbounded<void() noexcept>();
    test_is_complete_or_unbounded<void() & noexcept>();
    test_is_complete_or_unbounded<void() && noexcept>();
    test_is_complete_or_unbounded<void() const noexcept>();
    test_is_complete_or_unbounded<void() const & noexcept>();
    test_is_complete_or_unbounded<void() const && noexcept>();
    test_is_complete_or_unbounded<void() volatile noexcept>();
    test_is_complete_or_unbounded<void() volatile & noexcept>();
    test_is_complete_or_unbounded<void() volatile && noexcept>();
    test_is_complete_or_unbounded<void() const volatile noexcept>();
    test_is_complete_or_unbounded<void() const volatile & noexcept>();
    test_is_complete_or_unbounded<void() const volatile && noexcept>();

    test_is_complete_or_unbounded<void(int)>();
    test_is_complete_or_unbounded<void(int)&>();
    test_is_complete_or_unbounded<void(int) &&>();
    test_is_complete_or_unbounded<void(int) const>();
    test_is_complete_or_unbounded<void(int) const&>();
    test_is_complete_or_unbounded<void(int) const&&>();
    test_is_complete_or_unbounded<void(int) volatile>();
    test_is_complete_or_unbounded<void(int) volatile&>();
    test_is_complete_or_unbounded<void(int) volatile&&>();
    test_is_complete_or_unbounded<void(int) const volatile>();
    test_is_complete_or_unbounded<void(int) const volatile&>();
    test_is_complete_or_unbounded<void(int) const volatile&&>();
    test_is_complete_or_unbounded<void(int) noexcept>();
    test_is_complete_or_unbounded<void(int) & noexcept>();
    test_is_complete_or_unbounded<void(int) && noexcept>();
    test_is_complete_or_unbounded<void(int) const noexcept>();
    test_is_complete_or_unbounded<void(int) const & noexcept>();
    test_is_complete_or_unbounded<void(int) const && noexcept>();
    test_is_complete_or_unbounded<void(int) volatile noexcept>();
    test_is_complete_or_unbounded<void(int) volatile & noexcept>();
    test_is_complete_or_unbounded<void(int) volatile && noexcept>();
    test_is_complete_or_unbounded<void(int) const volatile noexcept>();
    test_is_complete_or_unbounded<void(int) const volatile & noexcept>();
    test_is_complete_or_unbounded<void(int) const volatile && noexcept>();

    test_is_complete_or_unbounded<void(...)>();
    test_is_complete_or_unbounded<void(...)&>();
    test_is_complete_or_unbounded<void(...) &&>();
    test_is_complete_or_unbounded<void(...) const>();
    test_is_complete_or_unbounded<void(...) const&>();
    test_is_complete_or_unbounded<void(...) const&&>();
    test_is_complete_or_unbounded<void(...) volatile>();
    test_is_complete_or_unbounded<void(...) volatile&>();
    test_is_complete_or_unbounded<void(...) volatile&&>();
    test_is_complete_or_unbounded<void(...) const volatile>();
    test_is_complete_or_unbounded<void(...) const volatile&>();
    test_is_complete_or_unbounded<void(...) const volatile&&>();
    test_is_complete_or_unbounded<void(...) noexcept>();
    test_is_complete_or_unbounded<void(...) & noexcept>();
    test_is_complete_or_unbounded<void(...) && noexcept>();
    test_is_complete_or_unbounded<void(...) const noexcept>();
    test_is_complete_or_unbounded<void(...) const & noexcept>();
    test_is_complete_or_unbounded<void(...) const && noexcept>();
    test_is_complete_or_unbounded<void(...) volatile noexcept>();
    test_is_complete_or_unbounded<void(...) volatile & noexcept>();
    test_is_complete_or_unbounded<void(...) volatile && noexcept>();
    test_is_complete_or_unbounded<void(...) const volatile noexcept>();
    test_is_complete_or_unbounded<void(...) const volatile & noexcept>();
    test_is_complete_or_unbounded<void(...) const volatile && noexcept>();

    test_is_complete_or_unbounded<void(int, ...)>();
    test_is_complete_or_unbounded<void(int, ...)&>();
    test_is_complete_or_unbounded<void(int, ...) &&>();
    test_is_complete_or_unbounded<void(int, ...) const>();
    test_is_complete_or_unbounded<void(int, ...) const&>();
    test_is_complete_or_unbounded<void(int, ...) const&&>();
    test_is_complete_or_unbounded<void(int, ...) volatile>();
    test_is_complete_or_unbounded<void(int, ...) volatile&>();
    test_is_complete_or_unbounded<void(int, ...) volatile&&>();
    test_is_complete_or_unbounded<void(int, ...) const volatile>();
    test_is_complete_or_unbounded<void(int, ...) const volatile&>();
    test_is_complete_or_unbounded<void(int, ...) const volatile&&>();
    test_is_complete_or_unbounded<void(int, ...) noexcept>();
    test_is_complete_or_unbounded<void(int, ...) & noexcept>();
    test_is_complete_or_unbounded<void(int, ...) && noexcept>();
    test_is_complete_or_unbounded<void(int, ...) const noexcept>();
    test_is_complete_or_unbounded<void(int, ...) const & noexcept>();
    test_is_complete_or_unbounded<void(int, ...) const && noexcept>();
    test_is_complete_or_unbounded<void(int, ...) volatile noexcept>();
    test_is_complete_or_unbounded<void(int, ...) volatile & noexcept>();
    test_is_complete_or_unbounded<void(int, ...) volatile && noexcept>();
    test_is_complete_or_unbounded<void(int, ...) const volatile noexcept>();
    test_is_complete_or_unbounded<void(int, ...) const volatile & noexcept>();
    test_is_complete_or_unbounded<void(int, ...) const volatile && noexcept>();

    test_is_complete_or_unbounded<int()>();
    test_is_complete_or_unbounded<int()&>();
    test_is_complete_or_unbounded<int() &&>();
    test_is_complete_or_unbounded<int() const>();
    test_is_complete_or_unbounded<int() const&>();
    test_is_complete_or_unbounded<int() const&&>();
    test_is_complete_or_unbounded<int() volatile>();
    test_is_complete_or_unbounded<int() volatile&>();
    test_is_complete_or_unbounded<int() volatile&&>();
    test_is_complete_or_unbounded<int() const volatile>();
    test_is_complete_or_unbounded<int() const volatile&>();
    test_is_complete_or_unbounded<int() const volatile&&>();
    test_is_complete_or_unbounded<int() noexcept>();
    test_is_complete_or_unbounded<int() & noexcept>();
    test_is_complete_or_unbounded<int() && noexcept>();
    test_is_complete_or_unbounded<int() const noexcept>();
    test_is_complete_or_unbounded<int() const & noexcept>();
    test_is_complete_or_unbounded<int() const && noexcept>();
    test_is_complete_or_unbounded<int() volatile noexcept>();
    test_is_complete_or_unbounded<int() volatile & noexcept>();
    test_is_complete_or_unbounded<int() volatile && noexcept>();
    test_is_complete_or_unbounded<int() const volatile noexcept>();
    test_is_complete_or_unbounded<int() const volatile & noexcept>();
    test_is_complete_or_unbounded<int() const volatile && noexcept>();

    test_is_complete_or_unbounded<int(int)>();
    test_is_complete_or_unbounded<int(int)&>();
    test_is_complete_or_unbounded<int(int) &&>();
    test_is_complete_or_unbounded<int(int) const>();
    test_is_complete_or_unbounded<int(int) const&>();
    test_is_complete_or_unbounded<int(int) const&&>();
    test_is_complete_or_unbounded<int(int) volatile>();
    test_is_complete_or_unbounded<int(int) volatile&>();
    test_is_complete_or_unbounded<int(int) volatile&&>();
    test_is_complete_or_unbounded<int(int) const volatile>();
    test_is_complete_or_unbounded<int(int) const volatile&>();
    test_is_complete_or_unbounded<int(int) const volatile&&>();
    test_is_complete_or_unbounded<int(int) noexcept>();
    test_is_complete_or_unbounded<int(int) & noexcept>();
    test_is_complete_or_unbounded<int(int) && noexcept>();
    test_is_complete_or_unbounded<int(int) const noexcept>();
    test_is_complete_or_unbounded<int(int) const & noexcept>();
    test_is_complete_or_unbounded<int(int) const && noexcept>();
    test_is_complete_or_unbounded<int(int) volatile noexcept>();
    test_is_complete_or_unbounded<int(int) volatile & noexcept>();
    test_is_complete_or_unbounded<int(int) volatile && noexcept>();
    test_is_complete_or_unbounded<int(int) const volatile noexcept>();
    test_is_complete_or_unbounded<int(int) const volatile & noexcept>();
    test_is_complete_or_unbounded<int(int) const volatile && noexcept>();

    test_is_complete_or_unbounded<int(...)>();
    test_is_complete_or_unbounded<int(...)&>();
    test_is_complete_or_unbounded<int(...) &&>();
    test_is_complete_or_unbounded<int(...) const>();
    test_is_complete_or_unbounded<int(...) const&>();
    test_is_complete_or_unbounded<int(...) const&&>();
    test_is_complete_or_unbounded<int(...) volatile>();
    test_is_complete_or_unbounded<int(...) volatile&>();
    test_is_complete_or_unbounded<int(...) volatile&&>();
    test_is_complete_or_unbounded<int(...) const volatile>();
    test_is_complete_or_unbounded<int(...) const volatile&>();
    test_is_complete_or_unbounded<int(...) const volatile&&>();
    test_is_complete_or_unbounded<int(...) noexcept>();
    test_is_complete_or_unbounded<int(...) & noexcept>();
    test_is_complete_or_unbounded<int(...) && noexcept>();
    test_is_complete_or_unbounded<int(...) const noexcept>();
    test_is_complete_or_unbounded<int(...) const & noexcept>();
    test_is_complete_or_unbounded<int(...) const && noexcept>();
    test_is_complete_or_unbounded<int(...) volatile noexcept>();
    test_is_complete_or_unbounded<int(...) volatile & noexcept>();
    test_is_complete_or_unbounded<int(...) volatile && noexcept>();
    test_is_complete_or_unbounded<int(...) const volatile noexcept>();
    test_is_complete_or_unbounded<int(...) const volatile & noexcept>();
    test_is_complete_or_unbounded<int(...) const volatile && noexcept>();

    test_is_complete_or_unbounded<int(int, ...)>();
    test_is_complete_or_unbounded<int(int, ...)&>();
    test_is_complete_or_unbounded<int(int, ...) &&>();
    test_is_complete_or_unbounded<int(int, ...) const>();
    test_is_complete_or_unbounded<int(int, ...) const&>();
    test_is_complete_or_unbounded<int(int, ...) const&&>();
    test_is_complete_or_unbounded<int(int, ...) volatile>();
    test_is_complete_or_unbounded<int(int, ...) volatile&>();
    test_is_complete_or_unbounded<int(int, ...) volatile&&>();
    test_is_complete_or_unbounded<int(int, ...) const volatile>();
    test_is_complete_or_unbounded<int(int, ...) const volatile&>();
    test_is_complete_or_unbounded<int(int, ...) const volatile&&>();
    test_is_complete_or_unbounded<int(int, ...) noexcept>();
    test_is_complete_or_unbounded<int(int, ...) & noexcept>();
    test_is_complete_or_unbounded<int(int, ...) && noexcept>();
    test_is_complete_or_unbounded<int(int, ...) const noexcept>();
    test_is_complete_or_unbounded<int(int, ...) const & noexcept>();
    test_is_complete_or_unbounded<int(int, ...) const && noexcept>();
    test_is_complete_or_unbounded<int(int, ...) volatile noexcept>();
    test_is_complete_or_unbounded<int(int, ...) volatile & noexcept>();
    test_is_complete_or_unbounded<int(int, ...) volatile && noexcept>();
    test_is_complete_or_unbounded<int(int, ...) const volatile noexcept>();
    test_is_complete_or_unbounded<int(int, ...) const volatile & noexcept>();
    test_is_complete_or_unbounded<int(int, ...) const volatile && noexcept>();

    test_is_complete_or_unbounded<void (*)()>();
    test_is_complete_or_unbounded<void (*)() noexcept>();

    test_is_complete_or_unbounded<void (*)(int)>();
    test_is_complete_or_unbounded<void (*)(int) noexcept>();

    test_is_complete_or_unbounded<void (*)(...)>();
    test_is_complete_or_unbounded<void (*)(...) noexcept>();

    test_is_complete_or_unbounded<void (*)(int, ...)>();
    test_is_complete_or_unbounded<void (*)(int, ...) noexcept>();

    test_is_complete_or_unbounded<int (*)()>();
    test_is_complete_or_unbounded<int (*)() noexcept>();

    test_is_complete_or_unbounded<int (*)(int)>();
    test_is_complete_or_unbounded<int (*)(int) noexcept>();

    test_is_complete_or_unbounded<int (*)(...)>();
    test_is_complete_or_unbounded<int (*)(...) noexcept>();

    test_is_complete_or_unbounded<int (*)(int, ...)>();
    test_is_complete_or_unbounded<int (*)(int, ...) noexcept>();

    test_is_complete_or_unbounded<void (&)()>();
    test_is_complete_or_unbounded<void (&)() noexcept>();

    test_is_complete_or_unbounded<void (&)(int)>();
    test_is_complete_or_unbounded<void (&)(int) noexcept>();

    test_is_complete_or_unbounded<void (&)(...)>();
    test_is_complete_or_unbounded<void (&)(...) noexcept>();

    test_is_complete_or_unbounded<void (&)(int, ...)>();
    test_is_complete_or_unbounded<void (&)(int, ...) noexcept>();

    test_is_complete_or_unbounded<int (&)()>();
    test_is_complete_or_unbounded<int (&)() noexcept>();

    test_is_complete_or_unbounded<int (&)(int)>();
    test_is_complete_or_unbounded<int (&)(int) noexcept>();

    test_is_complete_or_unbounded<int (&)(...)>();
    test_is_complete_or_unbounded<int (&)(...) noexcept>();

    test_is_complete_or_unbounded<int (&)(int, ...)>();
    test_is_complete_or_unbounded<int (&)(int, ...) noexcept>();

    test_is_complete_or_unbounded<void (&&)()>();
    test_is_complete_or_unbounded<void (&&)() noexcept>();

    test_is_complete_or_unbounded<void (&&)(int)>();
    test_is_complete_or_unbounded<void (&&)(int) noexcept>();

    test_is_complete_or_unbounded<void (&&)(...)>();
    test_is_complete_or_unbounded<void (&&)(...) noexcept>();

    test_is_complete_or_unbounded<void (&&)(int, ...)>();
    test_is_complete_or_unbounded<void (&&)(int, ...) noexcept>();

    test_is_complete_or_unbounded<int (&&)()>();
    test_is_complete_or_unbounded<int (&&)() noexcept>();

    test_is_complete_or_unbounded<int (&&)(int)>();
    test_is_complete_or_unbounded<int (&&)(int) noexcept>();

    test_is_complete_or_unbounded<int (&&)(...)>();
    test_is_complete_or_unbounded<int (&&)(...) noexcept>();

    test_is_complete_or_unbounded<int (&&)(int, ...)>();
    test_is_complete_or_unbounded<int (&&)(int, ...) noexcept>();

    test_is_complete_or_unbounded<void (class_type::*)()>();
    test_is_complete_or_unbounded<void (class_type::*)()&>();
    test_is_complete_or_unbounded<void (class_type::*)() &&>();
    test_is_complete_or_unbounded<void (class_type::*)() const>();
    test_is_complete_or_unbounded<void (class_type::*)() const&>();
    test_is_complete_or_unbounded<void (class_type::*)() const&&>();
    test_is_complete_or_unbounded<void (class_type::*)() noexcept>();
    test_is_complete_or_unbounded<void (class_type::*)() & noexcept>();
    test_is_complete_or_unbounded<void (class_type::*)() && noexcept>();
    test_is_complete_or_unbounded<void (class_type::*)() const noexcept>();
    test_is_complete_or_unbounded<void (class_type::*)() const & noexcept>();
    test_is_complete_or_unbounded<void (class_type::*)() const && noexcept>();

    test_is_complete_or_unbounded<void (class_type::*)(int)>();
    test_is_complete_or_unbounded<void (class_type::*)(int)&>();
    test_is_complete_or_unbounded<void (class_type::*)(int) &&>();
    test_is_complete_or_unbounded<void (class_type::*)(int) const>();
    test_is_complete_or_unbounded<void (class_type::*)(int) const&>();
    test_is_complete_or_unbounded<void (class_type::*)(int) const&&>();
    test_is_complete_or_unbounded<void (class_type::*)(int) noexcept>();
    test_is_complete_or_unbounded<void (class_type::*)(int) & noexcept>();
    test_is_complete_or_unbounded<void (class_type::*)(int) && noexcept>();
    test_is_complete_or_unbounded<void (class_type::*)(int) const noexcept>();
    test_is_complete_or_unbounded<void (class_type::*)(int) const & noexcept>();
    test_is_complete_or_unbounded<void (class_type::*)(int) const && noexcept>();

    test_is_complete_or_unbounded<void (class_type::*)(...)>();
    test_is_complete_or_unbounded<void (class_type::*)(...)&>();
    test_is_complete_or_unbounded<void (class_type::*)(...) &&>();
    test_is_complete_or_unbounded<void (class_type::*)(...) const>();
    test_is_complete_or_unbounded<void (class_type::*)(...) const&>();
    test_is_complete_or_unbounded<void (class_type::*)(...) const&&>();
    test_is_complete_or_unbounded<void (class_type::*)(...) noexcept>();
    test_is_complete_or_unbounded<void (class_type::*)(...) & noexcept>();
    test_is_complete_or_unbounded<void (class_type::*)(...) && noexcept>();
    test_is_complete_or_unbounded<void (class_type::*)(...) const noexcept>();
    test_is_complete_or_unbounded<void (class_type::*)(...) const & noexcept>();
    test_is_complete_or_unbounded<void (class_type::*)(...) const && noexcept>();

    test_is_complete_or_unbounded<void (class_type::*)(int, ...)>();
    test_is_complete_or_unbounded<void (class_type::*)(int, ...)&>();
    test_is_complete_or_unbounded<void (class_type::*)(int, ...) &&>();
    test_is_complete_or_unbounded<void (class_type::*)(int, ...) const>();
    test_is_complete_or_unbounded<void (class_type::*)(int, ...) const&>();
    test_is_complete_or_unbounded<void (class_type::*)(int, ...) const&&>();
    test_is_complete_or_unbounded<void (class_type::*)(int, ...) noexcept>();
    test_is_complete_or_unbounded<void (class_type::*)(int, ...) & noexcept>();
    test_is_complete_or_unbounded<void (class_type::*)(int, ...) && noexcept>();
    test_is_complete_or_unbounded<void (class_type::*)(int, ...) const noexcept>();
    test_is_complete_or_unbounded<void (class_type::*)(int, ...) const & noexcept>();
    test_is_complete_or_unbounded<void (class_type::*)(int, ...) const && noexcept>();

    test_is_complete_or_unbounded<int (class_type::*)()>();
    test_is_complete_or_unbounded<int (class_type::*)()&>();
    test_is_complete_or_unbounded<int (class_type::*)() &&>();
    test_is_complete_or_unbounded<int (class_type::*)() const>();
    test_is_complete_or_unbounded<int (class_type::*)() const&>();
    test_is_complete_or_unbounded<int (class_type::*)() const&&>();
    test_is_complete_or_unbounded<int (class_type::*)() noexcept>();
    test_is_complete_or_unbounded<int (class_type::*)() & noexcept>();
    test_is_complete_or_unbounded<int (class_type::*)() && noexcept>();
    test_is_complete_or_unbounded<int (class_type::*)() const noexcept>();
    test_is_complete_or_unbounded<int (class_type::*)() const & noexcept>();
    test_is_complete_or_unbounded<int (class_type::*)() const && noexcept>();

    test_is_complete_or_unbounded<int (class_type::*)(int)>();
    test_is_complete_or_unbounded<int (class_type::*)(int)&>();
    test_is_complete_or_unbounded<int (class_type::*)(int) &&>();
    test_is_complete_or_unbounded<int (class_type::*)(int) const>();
    test_is_complete_or_unbounded<int (class_type::*)(int) const&>();
    test_is_complete_or_unbounded<int (class_type::*)(int) const&&>();
    test_is_complete_or_unbounded<int (class_type::*)(int) noexcept>();
    test_is_complete_or_unbounded<int (class_type::*)(int) & noexcept>();
    test_is_complete_or_unbounded<int (class_type::*)(int) && noexcept>();
    test_is_complete_or_unbounded<int (class_type::*)(int) const noexcept>();
    test_is_complete_or_unbounded<int (class_type::*)(int) const & noexcept>();
    test_is_complete_or_unbounded<int (class_type::*)(int) const && noexcept>();

    test_is_complete_or_unbounded<int (class_type::*)(...)>();
    test_is_complete_or_unbounded<int (class_type::*)(...)&>();
    test_is_complete_or_unbounded<int (class_type::*)(...) &&>();
    test_is_complete_or_unbounded<int (class_type::*)(...) const>();
    test_is_complete_or_unbounded<int (class_type::*)(...) const&>();
    test_is_complete_or_unbounded<int (class_type::*)(...) const&&>();
    test_is_complete_or_unbounded<int (class_type::*)(...) noexcept>();
    test_is_complete_or_unbounded<int (class_type::*)(...) & noexcept>();
    test_is_complete_or_unbounded<int (class_type::*)(...) && noexcept>();
    test_is_complete_or_unbounded<int (class_type::*)(...) const noexcept>();
    test_is_complete_or_unbounded<int (class_type::*)(...) const & noexcept>();
    test_is_complete_or_unbounded<int (class_type::*)(...) const && noexcept>();

    test_is_complete_or_unbounded<int (class_type::*)(int, ...)>();
    test_is_complete_or_unbounded<int (class_type::*)(int, ...)&>();
    test_is_complete_or_unbounded<int (class_type::*)(int, ...) &&>();
    test_is_complete_or_unbounded<int (class_type::*)(int, ...) const>();
    test_is_complete_or_unbounded<int (class_type::*)(int, ...) const&>();
    test_is_complete_or_unbounded<int (class_type::*)(int, ...) const&&>();
    test_is_complete_or_unbounded<int (class_type::*)(int, ...) noexcept>();
    test_is_complete_or_unbounded<int (class_type::*)(int, ...) & noexcept>();
    test_is_complete_or_unbounded<int (class_type::*)(int, ...) && noexcept>();
    test_is_complete_or_unbounded<int (class_type::*)(int, ...) const noexcept>();
    test_is_complete_or_unbounded<int (class_type::*)(int, ...) const & noexcept>();
    test_is_complete_or_unbounded<int (class_type::*)(int, ...) const && noexcept>();
}
