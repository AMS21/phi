#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_safe_bool.hpp>
#include <vector>

template <typename TypeT>
void test_is_safe_bool_impl()
{
    STATIC_REQUIRE(phi::is_safe_bool<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_safe_bool<TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_safe_bool_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_not_safe_bool_v<TypeT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_safe_bool<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_safe_bool<TypeT>);
}

template <typename TypeT>
void test_is_not_safe_bool_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_safe_bool<TypeT>::value);
    STATIC_REQUIRE(phi::is_not_safe_bool<TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_safe_bool_v<TypeT>);
    STATIC_REQUIRE(phi::is_not_safe_bool_v<TypeT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_safe_bool<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_safe_bool<TypeT>);
}

template <typename TypeT>
void test_is_safe_bool()
{
    test_is_safe_bool_impl<TypeT>();
    test_is_safe_bool_impl<const TypeT>();
    test_is_safe_bool_impl<volatile TypeT>();
    test_is_safe_bool_impl<const volatile TypeT>();
}

template <typename TypeT>
void test_is_not_safe_bool()
{
    test_is_not_safe_bool_impl<TypeT>();
    test_is_not_safe_bool_impl<const TypeT>();
    test_is_not_safe_bool_impl<volatile TypeT>();
    test_is_not_safe_bool_impl<const volatile TypeT>();
}

TEST_CASE("is_safe_bool")
{
    test_is_not_safe_bool<void>();
    test_is_not_safe_bool<phi::nullptr_t>();
    test_is_not_safe_bool<bool>();
    test_is_not_safe_bool<char>();
    test_is_not_safe_bool<signed char>();
    test_is_not_safe_bool<unsigned char>();
    test_is_not_safe_bool<short>();
    test_is_not_safe_bool<unsigned short>();
    test_is_not_safe_bool<int>();
    test_is_not_safe_bool<unsigned int>();
    test_is_not_safe_bool<long>();
    test_is_not_safe_bool<unsigned long>();
    test_is_not_safe_bool<long long>();
    test_is_not_safe_bool<unsigned long long>();
    test_is_not_safe_bool<float>();
    test_is_not_safe_bool<double>();
    test_is_not_safe_bool<long double>();
    test_is_not_safe_bool<char8_t>();
    test_is_not_safe_bool<char16_t>();
    test_is_not_safe_bool<char32_t>();
    test_is_not_safe_bool<wchar_t>();

    test_is_safe_bool<phi::boolean>();
    test_is_not_safe_bool<phi::integer<signed char>>();
    test_is_not_safe_bool<phi::integer<unsigned char>>();
    test_is_not_safe_bool<phi::integer<short>>();
    test_is_not_safe_bool<phi::integer<unsigned short>>();
    test_is_not_safe_bool<phi::integer<int>>();
    test_is_not_safe_bool<phi::integer<unsigned int>>();
    test_is_not_safe_bool<phi::integer<long>>();
    test_is_not_safe_bool<phi::integer<unsigned long>>();
    test_is_not_safe_bool<phi::integer<long long>>();
    test_is_not_safe_bool<phi::integer<unsigned long long>>();
    test_is_not_safe_bool<phi::floating_point<float>>();
    test_is_not_safe_bool<phi::floating_point<double>>();
    test_is_not_safe_bool<phi::floating_point<long double>>();

    test_is_not_safe_bool<std::vector<int>>();
    test_is_not_safe_bool<phi::scope_ptr<int>>();

    test_is_not_safe_bool<int&>();
    test_is_not_safe_bool<const int&>();
    test_is_not_safe_bool<volatile int&>();
    test_is_not_safe_bool<const volatile int&>();
    test_is_not_safe_bool<int&&>();
    test_is_not_safe_bool<const int&&>();
    test_is_not_safe_bool<volatile int&&>();
    test_is_not_safe_bool<const volatile int&&>();
    test_is_not_safe_bool<int*>();
    test_is_not_safe_bool<const int*>();
    test_is_not_safe_bool<volatile int*>();
    test_is_not_safe_bool<const volatile int*>();
    test_is_not_safe_bool<int**>();
    test_is_not_safe_bool<const int**>();
    test_is_not_safe_bool<volatile int**>();
    test_is_not_safe_bool<const volatile int**>();
    test_is_not_safe_bool<int*&>();
    test_is_not_safe_bool<const int*&>();
    test_is_not_safe_bool<volatile int*&>();
    test_is_not_safe_bool<const volatile int*&>();
    test_is_not_safe_bool<int*&&>();
    test_is_not_safe_bool<const int*&&>();
    test_is_not_safe_bool<volatile int*&&>();
    test_is_not_safe_bool<const volatile int*&&>();
    test_is_not_safe_bool<void*>();
    test_is_not_safe_bool<char[3]>();
    test_is_not_safe_bool<char[]>();
    test_is_not_safe_bool<char* [3]>();
    test_is_not_safe_bool<char*[]>();
    test_is_not_safe_bool<int(*)[3]>();
    test_is_not_safe_bool<int(*)[]>();
    test_is_not_safe_bool<int(&)[3]>();
    test_is_not_safe_bool<int(&)[]>();
    test_is_not_safe_bool<int(&&)[3]>();
    test_is_not_safe_bool<int(&&)[]>();
    test_is_not_safe_bool<char[3][2]>();
    test_is_not_safe_bool<char[][2]>();
    test_is_not_safe_bool<char* [3][2]>();
    test_is_not_safe_bool<char*[][2]>();
    test_is_not_safe_bool<int(*)[3][2]>();
    test_is_not_safe_bool<int(*)[][2]>();
    test_is_not_safe_bool<int(&)[3][2]>();
    test_is_not_safe_bool<int(&)[][2]>();
    test_is_not_safe_bool<int(&&)[3][2]>();
    test_is_not_safe_bool<int(&&)[][2]>();
    test_is_not_safe_bool<class_type>();
    test_is_not_safe_bool<class_type[]>();
    test_is_not_safe_bool<class_type[2]>();
    test_is_not_safe_bool<template_type<void>>();
    test_is_not_safe_bool<template_type<int>>();
    test_is_not_safe_bool<template_type<class_type>>();
    test_is_not_safe_bool<template_type<incomplete_type>>();
    test_is_not_safe_bool<variadic_template<>>();
    test_is_not_safe_bool<variadic_template<void>>();
    test_is_not_safe_bool<variadic_template<int>>();
    test_is_not_safe_bool<variadic_template<class_type>>();
    test_is_not_safe_bool<variadic_template<incomplete_type>>();
    test_is_not_safe_bool<variadic_template<int, void, class_type, volatile char[]>>();
    test_is_not_safe_bool<public_derived_from<base>>();
    test_is_not_safe_bool<public_derived_from<derived>>();
    test_is_not_safe_bool<public_derived_from<class_type>>();
    test_is_not_safe_bool<private_derived_from<base>>();
    test_is_not_safe_bool<private_derived_from<derived>>();
    test_is_not_safe_bool<private_derived_from<class_type>>();
    test_is_not_safe_bool<protected_derived_from<base>>();
    test_is_not_safe_bool<protected_derived_from<derived>>();
    test_is_not_safe_bool<protected_derived_from<class_type>>();
    test_is_not_safe_bool<union_type>();
    test_is_not_safe_bool<non_empty_union>();
    test_is_not_safe_bool<empty>();
    test_is_not_safe_bool<not_empty>();
    test_is_not_safe_bool<bit_zero>();
    test_is_not_safe_bool<bit_one>();
    test_is_not_safe_bool<base>();
    test_is_not_safe_bool<derived>();
    test_is_not_safe_bool<abstract>();
    test_is_not_safe_bool<public_abstract>();
    test_is_not_safe_bool<private_abstract>();
    test_is_not_safe_bool<protected_abstract>();
    test_is_not_safe_bool<abstract_template<int>>();
    test_is_not_safe_bool<abstract_template<double>>();
    test_is_not_safe_bool<abstract_template<class_type>>();
    test_is_not_safe_bool<abstract_template<incomplete_type>>();
    test_is_not_safe_bool<final_type>();
    test_is_not_safe_bool<public_destructor>();
    test_is_not_safe_bool<protected_destructor>();
    test_is_not_safe_bool<private_destructor>();
    test_is_not_safe_bool<virtual_public_destructor>();
    test_is_not_safe_bool<virtual_protected_destructor>();
    test_is_not_safe_bool<virtual_private_destructor>();
    test_is_not_safe_bool<pure_public_destructor>();
    test_is_not_safe_bool<pure_protected_destructor>();
    test_is_not_safe_bool<pure_private_destructor>();
    test_is_not_safe_bool<deleted_public_destructor>();
    test_is_not_safe_bool<deleted_protected_destructor>();
    test_is_not_safe_bool<deleted_private_destructor>();
    test_is_not_safe_bool<deleted_virtual_public_destructor>();
    test_is_not_safe_bool<deleted_virtual_protected_destructor>();
    test_is_not_safe_bool<deleted_virtual_private_destructor>();
    test_is_not_safe_bool<Enum>();
    test_is_not_safe_bool<EnumSigned>();
    test_is_not_safe_bool<EnumUnsigned>();
    test_is_not_safe_bool<EnumClass>();
    test_is_not_safe_bool<EnumStruct>();
    test_is_not_safe_bool<function_type>();
    test_is_not_safe_bool<function_ptr>();
    test_is_not_safe_bool<member_object_ptr>();
    test_is_not_safe_bool<member_function_ptr>();
    test_is_not_safe_bool<incomplete_type>();
    test_is_not_safe_bool<incomplete_template<void>>();
    test_is_not_safe_bool<incomplete_template<int>>();
    test_is_not_safe_bool<incomplete_template<class_type>>();
    test_is_not_safe_bool<incomplete_template<incomplete_type>>();
    test_is_not_safe_bool<incomplete_variadic_template<>>();
    test_is_not_safe_bool<incomplete_variadic_template<void>>();
    test_is_not_safe_bool<incomplete_variadic_template<int>>();
    test_is_not_safe_bool<incomplete_variadic_template<class_type>>();
    test_is_not_safe_bool<incomplete_variadic_template<incomplete_type>>();
    test_is_not_safe_bool<incomplete_variadic_template<int, void, class_type, volatile char[]>>();
    test_is_not_safe_bool<int class_type::*>();
    test_is_not_safe_bool<float class_type::*>();
    test_is_not_safe_bool<void * class_type::*>();
    test_is_not_safe_bool<int * class_type::*>();
    test_is_not_safe_bool<int class_type::*&>();
    test_is_not_safe_bool<float class_type::*&>();
    test_is_not_safe_bool<void * class_type::*&>();
    test_is_not_safe_bool<int * class_type::*&>();
    test_is_not_safe_bool<int class_type::*&&>();
    test_is_not_safe_bool<float class_type::*&&>();
    test_is_not_safe_bool<void * class_type::*&&>();
    test_is_not_safe_bool<int * class_type::*&&>();
    test_is_not_safe_bool<int class_type::* const>();
    test_is_not_safe_bool<float class_type::* const>();
    test_is_not_safe_bool<void * class_type::* const>();
    test_is_not_safe_bool<int class_type::* const&>();
    test_is_not_safe_bool<float class_type::* const&>();
    test_is_not_safe_bool<void * class_type::* const&>();
    test_is_not_safe_bool<int class_type::* const&&>();
    test_is_not_safe_bool<float class_type::* const&&>();
    test_is_not_safe_bool<void * class_type::* const&&>();
    test_is_not_safe_bool<int class_type::* volatile>();
    test_is_not_safe_bool<float class_type::* volatile>();
    test_is_not_safe_bool<void * class_type::* volatile>();
    test_is_not_safe_bool<int class_type::* volatile&>();
    test_is_not_safe_bool<float class_type::* volatile&>();
    test_is_not_safe_bool<void * class_type::* volatile&>();
    test_is_not_safe_bool<int class_type::* volatile&&>();
    test_is_not_safe_bool<float class_type::* volatile&&>();
    test_is_not_safe_bool<void * class_type::* volatile&&>();
    test_is_not_safe_bool<int class_type::* const volatile>();
    test_is_not_safe_bool<float class_type::* const volatile>();
    test_is_not_safe_bool<void * class_type::* const volatile>();
    test_is_not_safe_bool<int class_type::* const volatile&>();
    test_is_not_safe_bool<float class_type::* const volatile&>();
    test_is_not_safe_bool<void * class_type::* const volatile&>();
    test_is_not_safe_bool<int class_type::* const volatile&&>();
    test_is_not_safe_bool<float class_type::* const volatile&&>();
    test_is_not_safe_bool<void * class_type::* const volatile&&>();
    test_is_not_safe_bool<non_copyable>();
    test_is_not_safe_bool<non_moveable>();
    test_is_not_safe_bool<non_constructible>();
    test_is_not_safe_bool<tracked>();
    test_is_not_safe_bool<trap_constructible>();
    test_is_not_safe_bool<trap_implicit_conversion>();
    test_is_not_safe_bool<trap_comma>();
    test_is_not_safe_bool<trap_call>();
    test_is_not_safe_bool<trap_self_assign>();
    test_is_not_safe_bool<trap_deref>();
    test_is_not_safe_bool<trap_array_subscript>();

    test_is_not_safe_bool<void()>();
    test_is_not_safe_bool<void()&>();
    test_is_not_safe_bool<void() &&>();
    test_is_not_safe_bool<void() const>();
    test_is_not_safe_bool<void() const&>();
    test_is_not_safe_bool<void() const&&>();
    test_is_not_safe_bool<void() volatile>();
    test_is_not_safe_bool<void() volatile&>();
    test_is_not_safe_bool<void() volatile&&>();
    test_is_not_safe_bool<void() const volatile>();
    test_is_not_safe_bool<void() const volatile&>();
    test_is_not_safe_bool<void() const volatile&&>();
    test_is_not_safe_bool<void() noexcept>();
    test_is_not_safe_bool<void() & noexcept>();
    test_is_not_safe_bool<void() && noexcept>();
    test_is_not_safe_bool<void() const noexcept>();
    test_is_not_safe_bool<void() const & noexcept>();
    test_is_not_safe_bool<void() const && noexcept>();
    test_is_not_safe_bool<void() volatile noexcept>();
    test_is_not_safe_bool<void() volatile & noexcept>();
    test_is_not_safe_bool<void() volatile && noexcept>();
    test_is_not_safe_bool<void() const volatile noexcept>();
    test_is_not_safe_bool<void() const volatile & noexcept>();
    test_is_not_safe_bool<void() const volatile && noexcept>();

    test_is_not_safe_bool<void(int)>();
    test_is_not_safe_bool<void(int)&>();
    test_is_not_safe_bool<void(int) &&>();
    test_is_not_safe_bool<void(int) const>();
    test_is_not_safe_bool<void(int) const&>();
    test_is_not_safe_bool<void(int) const&&>();
    test_is_not_safe_bool<void(int) volatile>();
    test_is_not_safe_bool<void(int) volatile&>();
    test_is_not_safe_bool<void(int) volatile&&>();
    test_is_not_safe_bool<void(int) const volatile>();
    test_is_not_safe_bool<void(int) const volatile&>();
    test_is_not_safe_bool<void(int) const volatile&&>();
    test_is_not_safe_bool<void(int) noexcept>();
    test_is_not_safe_bool<void(int) & noexcept>();
    test_is_not_safe_bool<void(int) && noexcept>();
    test_is_not_safe_bool<void(int) const noexcept>();
    test_is_not_safe_bool<void(int) const & noexcept>();
    test_is_not_safe_bool<void(int) const && noexcept>();
    test_is_not_safe_bool<void(int) volatile noexcept>();
    test_is_not_safe_bool<void(int) volatile & noexcept>();
    test_is_not_safe_bool<void(int) volatile && noexcept>();
    test_is_not_safe_bool<void(int) const volatile noexcept>();
    test_is_not_safe_bool<void(int) const volatile & noexcept>();
    test_is_not_safe_bool<void(int) const volatile && noexcept>();

    test_is_not_safe_bool<void(...)>();
    test_is_not_safe_bool<void(...)&>();
    test_is_not_safe_bool<void(...) &&>();
    test_is_not_safe_bool<void(...) const>();
    test_is_not_safe_bool<void(...) const&>();
    test_is_not_safe_bool<void(...) const&&>();
    test_is_not_safe_bool<void(...) volatile>();
    test_is_not_safe_bool<void(...) volatile&>();
    test_is_not_safe_bool<void(...) volatile&&>();
    test_is_not_safe_bool<void(...) const volatile>();
    test_is_not_safe_bool<void(...) const volatile&>();
    test_is_not_safe_bool<void(...) const volatile&&>();
    test_is_not_safe_bool<void(...) noexcept>();
    test_is_not_safe_bool<void(...) & noexcept>();
    test_is_not_safe_bool<void(...) && noexcept>();
    test_is_not_safe_bool<void(...) const noexcept>();
    test_is_not_safe_bool<void(...) const & noexcept>();
    test_is_not_safe_bool<void(...) const && noexcept>();
    test_is_not_safe_bool<void(...) volatile noexcept>();
    test_is_not_safe_bool<void(...) volatile & noexcept>();
    test_is_not_safe_bool<void(...) volatile && noexcept>();
    test_is_not_safe_bool<void(...) const volatile noexcept>();
    test_is_not_safe_bool<void(...) const volatile & noexcept>();
    test_is_not_safe_bool<void(...) const volatile && noexcept>();

    test_is_not_safe_bool<void(int, ...)>();
    test_is_not_safe_bool<void(int, ...)&>();
    test_is_not_safe_bool<void(int, ...) &&>();
    test_is_not_safe_bool<void(int, ...) const>();
    test_is_not_safe_bool<void(int, ...) const&>();
    test_is_not_safe_bool<void(int, ...) const&&>();
    test_is_not_safe_bool<void(int, ...) volatile>();
    test_is_not_safe_bool<void(int, ...) volatile&>();
    test_is_not_safe_bool<void(int, ...) volatile&&>();
    test_is_not_safe_bool<void(int, ...) const volatile>();
    test_is_not_safe_bool<void(int, ...) const volatile&>();
    test_is_not_safe_bool<void(int, ...) const volatile&&>();
    test_is_not_safe_bool<void(int, ...) noexcept>();
    test_is_not_safe_bool<void(int, ...) & noexcept>();
    test_is_not_safe_bool<void(int, ...) && noexcept>();
    test_is_not_safe_bool<void(int, ...) const noexcept>();
    test_is_not_safe_bool<void(int, ...) const & noexcept>();
    test_is_not_safe_bool<void(int, ...) const && noexcept>();
    test_is_not_safe_bool<void(int, ...) volatile noexcept>();
    test_is_not_safe_bool<void(int, ...) volatile & noexcept>();
    test_is_not_safe_bool<void(int, ...) volatile && noexcept>();
    test_is_not_safe_bool<void(int, ...) const volatile noexcept>();
    test_is_not_safe_bool<void(int, ...) const volatile & noexcept>();
    test_is_not_safe_bool<void(int, ...) const volatile && noexcept>();

    test_is_not_safe_bool<int()>();
    test_is_not_safe_bool<int()&>();
    test_is_not_safe_bool<int() &&>();
    test_is_not_safe_bool<int() const>();
    test_is_not_safe_bool<int() const&>();
    test_is_not_safe_bool<int() const&&>();
    test_is_not_safe_bool<int() volatile>();
    test_is_not_safe_bool<int() volatile&>();
    test_is_not_safe_bool<int() volatile&&>();
    test_is_not_safe_bool<int() const volatile>();
    test_is_not_safe_bool<int() const volatile&>();
    test_is_not_safe_bool<int() const volatile&&>();
    test_is_not_safe_bool<int() noexcept>();
    test_is_not_safe_bool<int() & noexcept>();
    test_is_not_safe_bool<int() && noexcept>();
    test_is_not_safe_bool<int() const noexcept>();
    test_is_not_safe_bool<int() const & noexcept>();
    test_is_not_safe_bool<int() const && noexcept>();
    test_is_not_safe_bool<int() volatile noexcept>();
    test_is_not_safe_bool<int() volatile & noexcept>();
    test_is_not_safe_bool<int() volatile && noexcept>();
    test_is_not_safe_bool<int() const volatile noexcept>();
    test_is_not_safe_bool<int() const volatile & noexcept>();
    test_is_not_safe_bool<int() const volatile && noexcept>();

    test_is_not_safe_bool<int(int)>();
    test_is_not_safe_bool<int(int)&>();
    test_is_not_safe_bool<int(int) &&>();
    test_is_not_safe_bool<int(int) const>();
    test_is_not_safe_bool<int(int) const&>();
    test_is_not_safe_bool<int(int) const&&>();
    test_is_not_safe_bool<int(int) volatile>();
    test_is_not_safe_bool<int(int) volatile&>();
    test_is_not_safe_bool<int(int) volatile&&>();
    test_is_not_safe_bool<int(int) const volatile>();
    test_is_not_safe_bool<int(int) const volatile&>();
    test_is_not_safe_bool<int(int) const volatile&&>();
    test_is_not_safe_bool<int(int) noexcept>();
    test_is_not_safe_bool<int(int) & noexcept>();
    test_is_not_safe_bool<int(int) && noexcept>();
    test_is_not_safe_bool<int(int) const noexcept>();
    test_is_not_safe_bool<int(int) const & noexcept>();
    test_is_not_safe_bool<int(int) const && noexcept>();
    test_is_not_safe_bool<int(int) volatile noexcept>();
    test_is_not_safe_bool<int(int) volatile & noexcept>();
    test_is_not_safe_bool<int(int) volatile && noexcept>();
    test_is_not_safe_bool<int(int) const volatile noexcept>();
    test_is_not_safe_bool<int(int) const volatile & noexcept>();
    test_is_not_safe_bool<int(int) const volatile && noexcept>();

    test_is_not_safe_bool<int(...)>();
    test_is_not_safe_bool<int(...)&>();
    test_is_not_safe_bool<int(...) &&>();
    test_is_not_safe_bool<int(...) const>();
    test_is_not_safe_bool<int(...) const&>();
    test_is_not_safe_bool<int(...) const&&>();
    test_is_not_safe_bool<int(...) volatile>();
    test_is_not_safe_bool<int(...) volatile&>();
    test_is_not_safe_bool<int(...) volatile&&>();
    test_is_not_safe_bool<int(...) const volatile>();
    test_is_not_safe_bool<int(...) const volatile&>();
    test_is_not_safe_bool<int(...) const volatile&&>();
    test_is_not_safe_bool<int(...) noexcept>();
    test_is_not_safe_bool<int(...) & noexcept>();
    test_is_not_safe_bool<int(...) && noexcept>();
    test_is_not_safe_bool<int(...) const noexcept>();
    test_is_not_safe_bool<int(...) const & noexcept>();
    test_is_not_safe_bool<int(...) const && noexcept>();
    test_is_not_safe_bool<int(...) volatile noexcept>();
    test_is_not_safe_bool<int(...) volatile & noexcept>();
    test_is_not_safe_bool<int(...) volatile && noexcept>();
    test_is_not_safe_bool<int(...) const volatile noexcept>();
    test_is_not_safe_bool<int(...) const volatile & noexcept>();
    test_is_not_safe_bool<int(...) const volatile && noexcept>();

    test_is_not_safe_bool<int(int, ...)>();
    test_is_not_safe_bool<int(int, ...)&>();
    test_is_not_safe_bool<int(int, ...) &&>();
    test_is_not_safe_bool<int(int, ...) const>();
    test_is_not_safe_bool<int(int, ...) const&>();
    test_is_not_safe_bool<int(int, ...) const&&>();
    test_is_not_safe_bool<int(int, ...) volatile>();
    test_is_not_safe_bool<int(int, ...) volatile&>();
    test_is_not_safe_bool<int(int, ...) volatile&&>();
    test_is_not_safe_bool<int(int, ...) const volatile>();
    test_is_not_safe_bool<int(int, ...) const volatile&>();
    test_is_not_safe_bool<int(int, ...) const volatile&&>();
    test_is_not_safe_bool<int(int, ...) noexcept>();
    test_is_not_safe_bool<int(int, ...) & noexcept>();
    test_is_not_safe_bool<int(int, ...) && noexcept>();
    test_is_not_safe_bool<int(int, ...) const noexcept>();
    test_is_not_safe_bool<int(int, ...) const & noexcept>();
    test_is_not_safe_bool<int(int, ...) const && noexcept>();
    test_is_not_safe_bool<int(int, ...) volatile noexcept>();
    test_is_not_safe_bool<int(int, ...) volatile & noexcept>();
    test_is_not_safe_bool<int(int, ...) volatile && noexcept>();
    test_is_not_safe_bool<int(int, ...) const volatile noexcept>();
    test_is_not_safe_bool<int(int, ...) const volatile & noexcept>();
    test_is_not_safe_bool<int(int, ...) const volatile && noexcept>();

    test_is_not_safe_bool<void (*)()>();
    test_is_not_safe_bool<void (*)() noexcept>();

    test_is_not_safe_bool<void (*)(int)>();
    test_is_not_safe_bool<void (*)(int) noexcept>();

    test_is_not_safe_bool<void (*)(...)>();
    test_is_not_safe_bool<void (*)(...) noexcept>();

    test_is_not_safe_bool<void (*)(int, ...)>();
    test_is_not_safe_bool<void (*)(int, ...) noexcept>();

    test_is_not_safe_bool<int (*)()>();
    test_is_not_safe_bool<int (*)() noexcept>();

    test_is_not_safe_bool<int (*)(int)>();
    test_is_not_safe_bool<int (*)(int) noexcept>();

    test_is_not_safe_bool<int (*)(...)>();
    test_is_not_safe_bool<int (*)(...) noexcept>();

    test_is_not_safe_bool<int (*)(int, ...)>();
    test_is_not_safe_bool<int (*)(int, ...) noexcept>();

    test_is_not_safe_bool<void (&)()>();
    test_is_not_safe_bool<void (&)() noexcept>();

    test_is_not_safe_bool<void (&)(int)>();
    test_is_not_safe_bool<void (&)(int) noexcept>();

    test_is_not_safe_bool<void (&)(...)>();
    test_is_not_safe_bool<void (&)(...) noexcept>();

    test_is_not_safe_bool<void (&)(int, ...)>();
    test_is_not_safe_bool<void (&)(int, ...) noexcept>();

    test_is_not_safe_bool<int (&)()>();
    test_is_not_safe_bool<int (&)() noexcept>();

    test_is_not_safe_bool<int (&)(int)>();
    test_is_not_safe_bool<int (&)(int) noexcept>();

    test_is_not_safe_bool<int (&)(...)>();
    test_is_not_safe_bool<int (&)(...) noexcept>();

    test_is_not_safe_bool<int (&)(int, ...)>();
    test_is_not_safe_bool<int (&)(int, ...) noexcept>();

    test_is_not_safe_bool<void (&&)()>();
    test_is_not_safe_bool<void (&&)() noexcept>();

    test_is_not_safe_bool<void (&&)(int)>();
    test_is_not_safe_bool<void (&&)(int) noexcept>();

    test_is_not_safe_bool<void (&&)(...)>();
    test_is_not_safe_bool<void (&&)(...) noexcept>();

    test_is_not_safe_bool<void (&&)(int, ...)>();
    test_is_not_safe_bool<void (&&)(int, ...) noexcept>();

    test_is_not_safe_bool<int (&&)()>();
    test_is_not_safe_bool<int (&&)() noexcept>();

    test_is_not_safe_bool<int (&&)(int)>();
    test_is_not_safe_bool<int (&&)(int) noexcept>();

    test_is_not_safe_bool<int (&&)(...)>();
    test_is_not_safe_bool<int (&&)(...) noexcept>();

    test_is_not_safe_bool<int (&&)(int, ...)>();
    test_is_not_safe_bool<int (&&)(int, ...) noexcept>();

    test_is_not_safe_bool<void (class_type::*)()>();
    test_is_not_safe_bool<void (class_type::*)()&>();
    test_is_not_safe_bool<void (class_type::*)() &&>();
    test_is_not_safe_bool<void (class_type::*)() const>();
    test_is_not_safe_bool<void (class_type::*)() const&>();
    test_is_not_safe_bool<void (class_type::*)() const&&>();
    test_is_not_safe_bool<void (class_type::*)() noexcept>();
    test_is_not_safe_bool<void (class_type::*)() & noexcept>();
    test_is_not_safe_bool<void (class_type::*)() && noexcept>();
    test_is_not_safe_bool<void (class_type::*)() const noexcept>();
    test_is_not_safe_bool<void (class_type::*)() const & noexcept>();
    test_is_not_safe_bool<void (class_type::*)() const && noexcept>();

    test_is_not_safe_bool<void (class_type::*)(int)>();
    test_is_not_safe_bool<void (class_type::*)(int)&>();
    test_is_not_safe_bool<void (class_type::*)(int) &&>();
    test_is_not_safe_bool<void (class_type::*)(int) const>();
    test_is_not_safe_bool<void (class_type::*)(int) const&>();
    test_is_not_safe_bool<void (class_type::*)(int) const&&>();
    test_is_not_safe_bool<void (class_type::*)(int) noexcept>();
    test_is_not_safe_bool<void (class_type::*)(int) & noexcept>();
    test_is_not_safe_bool<void (class_type::*)(int) && noexcept>();
    test_is_not_safe_bool<void (class_type::*)(int) const noexcept>();
    test_is_not_safe_bool<void (class_type::*)(int) const & noexcept>();
    test_is_not_safe_bool<void (class_type::*)(int) const && noexcept>();

    test_is_not_safe_bool<void (class_type::*)(...)>();
    test_is_not_safe_bool<void (class_type::*)(...)&>();
    test_is_not_safe_bool<void (class_type::*)(...) &&>();
    test_is_not_safe_bool<void (class_type::*)(...) const>();
    test_is_not_safe_bool<void (class_type::*)(...) const&>();
    test_is_not_safe_bool<void (class_type::*)(...) const&&>();
    test_is_not_safe_bool<void (class_type::*)(...) noexcept>();
    test_is_not_safe_bool<void (class_type::*)(...) & noexcept>();
    test_is_not_safe_bool<void (class_type::*)(...) && noexcept>();
    test_is_not_safe_bool<void (class_type::*)(...) const noexcept>();
    test_is_not_safe_bool<void (class_type::*)(...) const & noexcept>();
    test_is_not_safe_bool<void (class_type::*)(...) const && noexcept>();

    test_is_not_safe_bool<void (class_type::*)(int, ...)>();
    test_is_not_safe_bool<void (class_type::*)(int, ...)&>();
    test_is_not_safe_bool<void (class_type::*)(int, ...) &&>();
    test_is_not_safe_bool<void (class_type::*)(int, ...) const>();
    test_is_not_safe_bool<void (class_type::*)(int, ...) const&>();
    test_is_not_safe_bool<void (class_type::*)(int, ...) const&&>();
    test_is_not_safe_bool<void (class_type::*)(int, ...) noexcept>();
    test_is_not_safe_bool<void (class_type::*)(int, ...) & noexcept>();
    test_is_not_safe_bool<void (class_type::*)(int, ...) && noexcept>();
    test_is_not_safe_bool<void (class_type::*)(int, ...) const noexcept>();
    test_is_not_safe_bool<void (class_type::*)(int, ...) const & noexcept>();
    test_is_not_safe_bool<void (class_type::*)(int, ...) const && noexcept>();

    test_is_not_safe_bool<int (class_type::*)()>();
    test_is_not_safe_bool<int (class_type::*)()&>();
    test_is_not_safe_bool<int (class_type::*)() &&>();
    test_is_not_safe_bool<int (class_type::*)() const>();
    test_is_not_safe_bool<int (class_type::*)() const&>();
    test_is_not_safe_bool<int (class_type::*)() const&&>();
    test_is_not_safe_bool<int (class_type::*)() noexcept>();
    test_is_not_safe_bool<int (class_type::*)() & noexcept>();
    test_is_not_safe_bool<int (class_type::*)() && noexcept>();
    test_is_not_safe_bool<int (class_type::*)() const noexcept>();
    test_is_not_safe_bool<int (class_type::*)() const & noexcept>();
    test_is_not_safe_bool<int (class_type::*)() const && noexcept>();

    test_is_not_safe_bool<int (class_type::*)(int)>();
    test_is_not_safe_bool<int (class_type::*)(int)&>();
    test_is_not_safe_bool<int (class_type::*)(int) &&>();
    test_is_not_safe_bool<int (class_type::*)(int) const>();
    test_is_not_safe_bool<int (class_type::*)(int) const&>();
    test_is_not_safe_bool<int (class_type::*)(int) const&&>();
    test_is_not_safe_bool<int (class_type::*)(int) noexcept>();
    test_is_not_safe_bool<int (class_type::*)(int) & noexcept>();
    test_is_not_safe_bool<int (class_type::*)(int) && noexcept>();
    test_is_not_safe_bool<int (class_type::*)(int) const noexcept>();
    test_is_not_safe_bool<int (class_type::*)(int) const & noexcept>();
    test_is_not_safe_bool<int (class_type::*)(int) const && noexcept>();

    test_is_not_safe_bool<int (class_type::*)(...)>();
    test_is_not_safe_bool<int (class_type::*)(...)&>();
    test_is_not_safe_bool<int (class_type::*)(...) &&>();
    test_is_not_safe_bool<int (class_type::*)(...) const>();
    test_is_not_safe_bool<int (class_type::*)(...) const&>();
    test_is_not_safe_bool<int (class_type::*)(...) const&&>();
    test_is_not_safe_bool<int (class_type::*)(...) noexcept>();
    test_is_not_safe_bool<int (class_type::*)(...) & noexcept>();
    test_is_not_safe_bool<int (class_type::*)(...) && noexcept>();
    test_is_not_safe_bool<int (class_type::*)(...) const noexcept>();
    test_is_not_safe_bool<int (class_type::*)(...) const & noexcept>();
    test_is_not_safe_bool<int (class_type::*)(...) const && noexcept>();

    test_is_not_safe_bool<int (class_type::*)(int, ...)>();
    test_is_not_safe_bool<int (class_type::*)(int, ...)&>();
    test_is_not_safe_bool<int (class_type::*)(int, ...) &&>();
    test_is_not_safe_bool<int (class_type::*)(int, ...) const>();
    test_is_not_safe_bool<int (class_type::*)(int, ...) const&>();
    test_is_not_safe_bool<int (class_type::*)(int, ...) const&&>();
    test_is_not_safe_bool<int (class_type::*)(int, ...) noexcept>();
    test_is_not_safe_bool<int (class_type::*)(int, ...) & noexcept>();
    test_is_not_safe_bool<int (class_type::*)(int, ...) && noexcept>();
    test_is_not_safe_bool<int (class_type::*)(int, ...) const noexcept>();
    test_is_not_safe_bool<int (class_type::*)(int, ...) const & noexcept>();
    test_is_not_safe_bool<int (class_type::*)(int, ...) const && noexcept>();
}
