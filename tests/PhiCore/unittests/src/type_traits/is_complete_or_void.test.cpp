#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_complete_or_void.hpp>
#include <vector>

template <typename TypeT>
void test_is_complete_or_void_impl()
{
    STATIC_REQUIRE(phi::is_complete_or_void<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_complete_or_void<TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_complete_or_void_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_not_complete_or_void_v<TypeT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_complete_or_void<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_complete_or_void<TypeT>);
}

template <typename TypeT>
void test_is_complete_or_void()
{
    test_is_complete_or_void_impl<TypeT>();
    test_is_complete_or_void_impl<const TypeT>();
    test_is_complete_or_void_impl<volatile TypeT>();
    test_is_complete_or_void_impl<const volatile TypeT>();
}

template <typename TypeT>
void test_is_not_complete_or_void_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_complete_or_void<TypeT>::value);
    STATIC_REQUIRE(phi::is_not_complete_or_void<TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_complete_or_void_v<TypeT>);
    STATIC_REQUIRE(phi::is_not_complete_or_void_v<TypeT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_complete_or_void<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_complete_or_void<TypeT>);
}

template <typename TypeT>
void test_is_not_complete_or_void()
{
    test_is_not_complete_or_void_impl<TypeT>();
    test_is_not_complete_or_void_impl<const TypeT>();
    test_is_not_complete_or_void_impl<volatile TypeT>();
    test_is_not_complete_or_void_impl<const volatile TypeT>();
}

class A;

TEST_CASE("is_complete_or_void")
{
    test_is_complete_or_void<void>();
    test_is_complete_or_void<phi::nullptr_t>();
    test_is_complete_or_void<bool>();
    test_is_complete_or_void<char>();
    test_is_complete_or_void<signed char>();
    test_is_complete_or_void<unsigned char>();
    test_is_complete_or_void<short>();
    test_is_complete_or_void<unsigned short>();
    test_is_complete_or_void<int>();
    test_is_complete_or_void<unsigned int>();
    test_is_complete_or_void<long>();
    test_is_complete_or_void<unsigned long>();
    test_is_complete_or_void<long long>();
    test_is_complete_or_void<unsigned long long>();
    test_is_complete_or_void<float>();
    test_is_complete_or_void<double>();
    test_is_complete_or_void<long double>();
    test_is_complete_or_void<char8_t>();
    test_is_complete_or_void<char16_t>();
    test_is_complete_or_void<char32_t>();
    test_is_complete_or_void<wchar_t>();

    test_is_complete_or_void<phi::boolean>();
    test_is_complete_or_void<phi::integer<signed char>>();
    test_is_complete_or_void<phi::integer<unsigned char>>();
    test_is_complete_or_void<phi::integer<short>>();
    test_is_complete_or_void<phi::integer<unsigned short>>();
    test_is_complete_or_void<phi::integer<int>>();
    test_is_complete_or_void<phi::integer<unsigned int>>();
    test_is_complete_or_void<phi::integer<long>>();
    test_is_complete_or_void<phi::integer<unsigned long>>();
    test_is_complete_or_void<phi::integer<long long>>();
    test_is_complete_or_void<phi::integer<unsigned long long>>();
    test_is_complete_or_void<phi::floating_point<float>>();
    test_is_complete_or_void<phi::floating_point<double>>();
    test_is_complete_or_void<phi::floating_point<long double>>();

    test_is_complete_or_void<std::vector<int>>();
    test_is_complete_or_void<phi::scope_ptr<int>>();

    test_is_complete_or_void<int&>();
    test_is_complete_or_void<const int&>();
    test_is_complete_or_void<volatile int&>();
    test_is_complete_or_void<const volatile int&>();
    test_is_complete_or_void<int&&>();
    test_is_complete_or_void<const int&&>();
    test_is_complete_or_void<volatile int&&>();
    test_is_complete_or_void<const volatile int&&>();
    test_is_complete_or_void<int*>();
    test_is_complete_or_void<const int*>();
    test_is_complete_or_void<volatile int*>();
    test_is_complete_or_void<const volatile int*>();
    test_is_complete_or_void<int**>();
    test_is_complete_or_void<const int**>();
    test_is_complete_or_void<volatile int**>();
    test_is_complete_or_void<const volatile int**>();
    test_is_complete_or_void<int*&>();
    test_is_complete_or_void<const int*&>();
    test_is_complete_or_void<volatile int*&>();
    test_is_complete_or_void<const volatile int*&>();
    test_is_complete_or_void<int*&&>();
    test_is_complete_or_void<const int*&&>();
    test_is_complete_or_void<volatile int*&&>();
    test_is_complete_or_void<const volatile int*&&>();
    test_is_complete_or_void<void*>();
    test_is_complete_or_void<char[3]>();
    test_is_not_complete_or_void<char[]>();
    test_is_complete_or_void<char* [3]>();
    test_is_not_complete_or_void<char*[]>();
    test_is_complete_or_void<int(*)[3]>();
    test_is_complete_or_void<int(*)[]>();
    test_is_complete_or_void<int(&)[3]>();
    test_is_not_complete_or_void<int(&)[]>();
    test_is_complete_or_void<int(&&)[3]>();
    test_is_complete_or_void<int(&&)[]>();
    test_is_complete_or_void<char[3][2]>();
    test_is_not_complete_or_void<char[][2]>();
    test_is_complete_or_void<char* [3][2]>();
    test_is_not_complete_or_void<char*[][2]>();
    test_is_complete_or_void<int(*)[3][2]>();
    test_is_complete_or_void<int(*)[][2]>();
    test_is_complete_or_void<int(&)[3][2]>();
    test_is_not_complete_or_void<int(&)[][2]>();
    test_is_complete_or_void<int(&&)[3][2]>();
    test_is_complete_or_void<int(&&)[][2]>();
    test_is_complete_or_void<class_type>();
    test_is_not_complete_or_void<class_type[]>();
    test_is_complete_or_void<class_type[2]>();
    test_is_complete_or_void<template_type<void>>();
    test_is_complete_or_void<template_type<int>>();
    test_is_complete_or_void<template_type<class_type>>();
    test_is_complete_or_void<template_type<incomplete_type>>();
    test_is_complete_or_void<variadic_template<>>();
    test_is_complete_or_void<variadic_template<void>>();
    test_is_complete_or_void<variadic_template<int>>();
    test_is_complete_or_void<variadic_template<class_type>>();
    test_is_complete_or_void<variadic_template<incomplete_type>>();
    test_is_complete_or_void<variadic_template<int, void, class_type, volatile char[]>>();
    test_is_complete_or_void<public_derived_from<base>>();
    test_is_complete_or_void<public_derived_from<derived>>();
    test_is_complete_or_void<public_derived_from<class_type>>();
    test_is_complete_or_void<private_derived_from<base>>();
    test_is_complete_or_void<private_derived_from<derived>>();
    test_is_complete_or_void<private_derived_from<class_type>>();
    test_is_complete_or_void<protected_derived_from<base>>();
    test_is_complete_or_void<protected_derived_from<derived>>();
    test_is_complete_or_void<protected_derived_from<class_type>>();
    test_is_complete_or_void<union_type>();
    test_is_complete_or_void<non_empty_union>();
    test_is_complete_or_void<empty>();
    test_is_complete_or_void<not_empty>();
    test_is_complete_or_void<bit_zero>();
    test_is_complete_or_void<bit_one>();
    test_is_complete_or_void<base>();
    test_is_complete_or_void<derived>();
    test_is_complete_or_void<abstract>();
    test_is_complete_or_void<public_abstract>();
    test_is_complete_or_void<private_abstract>();
    test_is_complete_or_void<protected_abstract>();
    test_is_complete_or_void<abstract_template<int>>();
    test_is_complete_or_void<abstract_template<double>>();
    test_is_complete_or_void<abstract_template<class_type>>();
    test_is_complete_or_void<abstract_template<incomplete_type>>();
    test_is_complete_or_void<final_type>();
    test_is_complete_or_void<public_destructor>();
    test_is_complete_or_void<protected_destructor>();
    test_is_complete_or_void<private_destructor>();
    test_is_complete_or_void<virtual_public_destructor>();
    test_is_complete_or_void<virtual_protected_destructor>();
    test_is_complete_or_void<virtual_private_destructor>();
    test_is_complete_or_void<pure_public_destructor>();
    test_is_complete_or_void<pure_protected_destructor>();
    test_is_complete_or_void<pure_private_destructor>();
    test_is_complete_or_void<deleted_public_destructor>();
    test_is_complete_or_void<deleted_protected_destructor>();
    test_is_complete_or_void<deleted_private_destructor>();
    test_is_complete_or_void<deleted_virtual_public_destructor>();
    test_is_complete_or_void<deleted_virtual_protected_destructor>();
    test_is_complete_or_void<deleted_virtual_private_destructor>();
    test_is_complete_or_void<Enum>();
    test_is_complete_or_void<EnumSigned>();
    test_is_complete_or_void<EnumUnsigned>();
    test_is_complete_or_void<EnumClass>();
    test_is_complete_or_void<EnumStruct>();
    test_is_complete_or_void<function_type>();
    test_is_complete_or_void<function_ptr>();
    test_is_complete_or_void<member_object_ptr>();
    test_is_complete_or_void<member_function_ptr>();
    test_is_not_complete_or_void<incomplete_type>();
    test_is_not_complete_or_void<incomplete_template<void>>();
    test_is_not_complete_or_void<incomplete_template<int>>();
    test_is_not_complete_or_void<incomplete_template<class_type>>();
    test_is_not_complete_or_void<incomplete_template<incomplete_type>>();
    test_is_not_complete_or_void<incomplete_variadic_template<>>();
    test_is_not_complete_or_void<incomplete_variadic_template<void>>();
    test_is_not_complete_or_void<incomplete_variadic_template<int>>();
    test_is_not_complete_or_void<incomplete_variadic_template<class_type>>();
    test_is_not_complete_or_void<incomplete_variadic_template<incomplete_type>>();
    test_is_not_complete_or_void<
            incomplete_variadic_template<int, void, class_type, volatile char[]>>();
    test_is_complete_or_void<int class_type::*>();
    test_is_complete_or_void<float class_type::*>();
    test_is_complete_or_void<void * class_type::*>();
    test_is_complete_or_void<int * class_type::*>();
    test_is_complete_or_void<int class_type::*&>();
    test_is_complete_or_void<float class_type::*&>();
    test_is_complete_or_void<void * class_type::*&>();
    test_is_complete_or_void<int * class_type::*&>();
    test_is_complete_or_void<int class_type::*&&>();
    test_is_complete_or_void<float class_type::*&&>();
    test_is_complete_or_void<void * class_type::*&&>();
    test_is_complete_or_void<int * class_type::*&&>();
    test_is_complete_or_void<int class_type::* const>();
    test_is_complete_or_void<float class_type::* const>();
    test_is_complete_or_void<void * class_type::* const>();
    test_is_complete_or_void<int class_type::* const&>();
    test_is_complete_or_void<float class_type::* const&>();
    test_is_complete_or_void<void * class_type::* const&>();
    test_is_complete_or_void<int class_type::* const&&>();
    test_is_complete_or_void<float class_type::* const&&>();
    test_is_complete_or_void<void * class_type::* const&&>();
    test_is_complete_or_void<int class_type::* volatile>();
    test_is_complete_or_void<float class_type::* volatile>();
    test_is_complete_or_void<void * class_type::* volatile>();
    test_is_complete_or_void<int class_type::* volatile&>();
    test_is_complete_or_void<float class_type::* volatile&>();
    test_is_complete_or_void<void * class_type::* volatile&>();
    test_is_complete_or_void<int class_type::* volatile&&>();
    test_is_complete_or_void<float class_type::* volatile&&>();
    test_is_complete_or_void<void * class_type::* volatile&&>();
    test_is_complete_or_void<int class_type::* const volatile>();
    test_is_complete_or_void<float class_type::* const volatile>();
    test_is_complete_or_void<void * class_type::* const volatile>();
    test_is_complete_or_void<int class_type::* const volatile&>();
    test_is_complete_or_void<float class_type::* const volatile&>();
    test_is_complete_or_void<void * class_type::* const volatile&>();
    test_is_complete_or_void<int class_type::* const volatile&&>();
    test_is_complete_or_void<float class_type::* const volatile&&>();
    test_is_complete_or_void<void * class_type::* const volatile&&>();
    test_is_complete_or_void<non_copyable>();
    test_is_complete_or_void<non_moveable>();
    test_is_complete_or_void<non_constructible>();
    test_is_complete_or_void<tracked>();
    test_is_complete_or_void<trap_constructible>();
    test_is_complete_or_void<trap_implicit_conversion>();
    test_is_complete_or_void<trap_comma>();
    test_is_complete_or_void<trap_call>();
    test_is_complete_or_void<trap_self_assign>();
    test_is_complete_or_void<trap_deref>();
    test_is_complete_or_void<trap_array_subscript>();

    test_is_complete_or_void<void()>();
    test_is_complete_or_void<void()&>();
    test_is_complete_or_void<void() &&>();
    test_is_complete_or_void<void() const>();
    test_is_complete_or_void<void() const&>();
    test_is_complete_or_void<void() const&&>();
    test_is_complete_or_void<void() volatile>();
    test_is_complete_or_void<void() volatile&>();
    test_is_complete_or_void<void() volatile&&>();
    test_is_complete_or_void<void() const volatile>();
    test_is_complete_or_void<void() const volatile&>();
    test_is_complete_or_void<void() const volatile&&>();
    test_is_complete_or_void<void() noexcept>();
    test_is_complete_or_void<void() & noexcept>();
    test_is_complete_or_void<void() && noexcept>();
    test_is_complete_or_void<void() const noexcept>();
    test_is_complete_or_void<void() const & noexcept>();
    test_is_complete_or_void<void() const && noexcept>();
    test_is_complete_or_void<void() volatile noexcept>();
    test_is_complete_or_void<void() volatile & noexcept>();
    test_is_complete_or_void<void() volatile && noexcept>();
    test_is_complete_or_void<void() const volatile noexcept>();
    test_is_complete_or_void<void() const volatile & noexcept>();
    test_is_complete_or_void<void() const volatile && noexcept>();

    test_is_complete_or_void<void(int)>();
    test_is_complete_or_void<void(int)&>();
    test_is_complete_or_void<void(int) &&>();
    test_is_complete_or_void<void(int) const>();
    test_is_complete_or_void<void(int) const&>();
    test_is_complete_or_void<void(int) const&&>();
    test_is_complete_or_void<void(int) volatile>();
    test_is_complete_or_void<void(int) volatile&>();
    test_is_complete_or_void<void(int) volatile&&>();
    test_is_complete_or_void<void(int) const volatile>();
    test_is_complete_or_void<void(int) const volatile&>();
    test_is_complete_or_void<void(int) const volatile&&>();
    test_is_complete_or_void<void(int) noexcept>();
    test_is_complete_or_void<void(int) & noexcept>();
    test_is_complete_or_void<void(int) && noexcept>();
    test_is_complete_or_void<void(int) const noexcept>();
    test_is_complete_or_void<void(int) const & noexcept>();
    test_is_complete_or_void<void(int) const && noexcept>();
    test_is_complete_or_void<void(int) volatile noexcept>();
    test_is_complete_or_void<void(int) volatile & noexcept>();
    test_is_complete_or_void<void(int) volatile && noexcept>();
    test_is_complete_or_void<void(int) const volatile noexcept>();
    test_is_complete_or_void<void(int) const volatile & noexcept>();
    test_is_complete_or_void<void(int) const volatile && noexcept>();

    test_is_complete_or_void<void(...)>();
    test_is_complete_or_void<void(...)&>();
    test_is_complete_or_void<void(...) &&>();
    test_is_complete_or_void<void(...) const>();
    test_is_complete_or_void<void(...) const&>();
    test_is_complete_or_void<void(...) const&&>();
    test_is_complete_or_void<void(...) volatile>();
    test_is_complete_or_void<void(...) volatile&>();
    test_is_complete_or_void<void(...) volatile&&>();
    test_is_complete_or_void<void(...) const volatile>();
    test_is_complete_or_void<void(...) const volatile&>();
    test_is_complete_or_void<void(...) const volatile&&>();
    test_is_complete_or_void<void(...) noexcept>();
    test_is_complete_or_void<void(...) & noexcept>();
    test_is_complete_or_void<void(...) && noexcept>();
    test_is_complete_or_void<void(...) const noexcept>();
    test_is_complete_or_void<void(...) const & noexcept>();
    test_is_complete_or_void<void(...) const && noexcept>();
    test_is_complete_or_void<void(...) volatile noexcept>();
    test_is_complete_or_void<void(...) volatile & noexcept>();
    test_is_complete_or_void<void(...) volatile && noexcept>();
    test_is_complete_or_void<void(...) const volatile noexcept>();
    test_is_complete_or_void<void(...) const volatile & noexcept>();
    test_is_complete_or_void<void(...) const volatile && noexcept>();

    test_is_complete_or_void<void(int, ...)>();
    test_is_complete_or_void<void(int, ...)&>();
    test_is_complete_or_void<void(int, ...) &&>();
    test_is_complete_or_void<void(int, ...) const>();
    test_is_complete_or_void<void(int, ...) const&>();
    test_is_complete_or_void<void(int, ...) const&&>();
    test_is_complete_or_void<void(int, ...) volatile>();
    test_is_complete_or_void<void(int, ...) volatile&>();
    test_is_complete_or_void<void(int, ...) volatile&&>();
    test_is_complete_or_void<void(int, ...) const volatile>();
    test_is_complete_or_void<void(int, ...) const volatile&>();
    test_is_complete_or_void<void(int, ...) const volatile&&>();
    test_is_complete_or_void<void(int, ...) noexcept>();
    test_is_complete_or_void<void(int, ...) & noexcept>();
    test_is_complete_or_void<void(int, ...) && noexcept>();
    test_is_complete_or_void<void(int, ...) const noexcept>();
    test_is_complete_or_void<void(int, ...) const & noexcept>();
    test_is_complete_or_void<void(int, ...) const && noexcept>();
    test_is_complete_or_void<void(int, ...) volatile noexcept>();
    test_is_complete_or_void<void(int, ...) volatile & noexcept>();
    test_is_complete_or_void<void(int, ...) volatile && noexcept>();
    test_is_complete_or_void<void(int, ...) const volatile noexcept>();
    test_is_complete_or_void<void(int, ...) const volatile & noexcept>();
    test_is_complete_or_void<void(int, ...) const volatile && noexcept>();

    test_is_complete_or_void<int()>();
    test_is_complete_or_void<int()&>();
    test_is_complete_or_void<int() &&>();
    test_is_complete_or_void<int() const>();
    test_is_complete_or_void<int() const&>();
    test_is_complete_or_void<int() const&&>();
    test_is_complete_or_void<int() volatile>();
    test_is_complete_or_void<int() volatile&>();
    test_is_complete_or_void<int() volatile&&>();
    test_is_complete_or_void<int() const volatile>();
    test_is_complete_or_void<int() const volatile&>();
    test_is_complete_or_void<int() const volatile&&>();
    test_is_complete_or_void<int() noexcept>();
    test_is_complete_or_void<int() & noexcept>();
    test_is_complete_or_void<int() && noexcept>();
    test_is_complete_or_void<int() const noexcept>();
    test_is_complete_or_void<int() const & noexcept>();
    test_is_complete_or_void<int() const && noexcept>();
    test_is_complete_or_void<int() volatile noexcept>();
    test_is_complete_or_void<int() volatile & noexcept>();
    test_is_complete_or_void<int() volatile && noexcept>();
    test_is_complete_or_void<int() const volatile noexcept>();
    test_is_complete_or_void<int() const volatile & noexcept>();
    test_is_complete_or_void<int() const volatile && noexcept>();

    test_is_complete_or_void<int(int)>();
    test_is_complete_or_void<int(int)&>();
    test_is_complete_or_void<int(int) &&>();
    test_is_complete_or_void<int(int) const>();
    test_is_complete_or_void<int(int) const&>();
    test_is_complete_or_void<int(int) const&&>();
    test_is_complete_or_void<int(int) volatile>();
    test_is_complete_or_void<int(int) volatile&>();
    test_is_complete_or_void<int(int) volatile&&>();
    test_is_complete_or_void<int(int) const volatile>();
    test_is_complete_or_void<int(int) const volatile&>();
    test_is_complete_or_void<int(int) const volatile&&>();
    test_is_complete_or_void<int(int) noexcept>();
    test_is_complete_or_void<int(int) & noexcept>();
    test_is_complete_or_void<int(int) && noexcept>();
    test_is_complete_or_void<int(int) const noexcept>();
    test_is_complete_or_void<int(int) const & noexcept>();
    test_is_complete_or_void<int(int) const && noexcept>();
    test_is_complete_or_void<int(int) volatile noexcept>();
    test_is_complete_or_void<int(int) volatile & noexcept>();
    test_is_complete_or_void<int(int) volatile && noexcept>();
    test_is_complete_or_void<int(int) const volatile noexcept>();
    test_is_complete_or_void<int(int) const volatile & noexcept>();
    test_is_complete_or_void<int(int) const volatile && noexcept>();

    test_is_complete_or_void<int(...)>();
    test_is_complete_or_void<int(...)&>();
    test_is_complete_or_void<int(...) &&>();
    test_is_complete_or_void<int(...) const>();
    test_is_complete_or_void<int(...) const&>();
    test_is_complete_or_void<int(...) const&&>();
    test_is_complete_or_void<int(...) volatile>();
    test_is_complete_or_void<int(...) volatile&>();
    test_is_complete_or_void<int(...) volatile&&>();
    test_is_complete_or_void<int(...) const volatile>();
    test_is_complete_or_void<int(...) const volatile&>();
    test_is_complete_or_void<int(...) const volatile&&>();
    test_is_complete_or_void<int(...) noexcept>();
    test_is_complete_or_void<int(...) & noexcept>();
    test_is_complete_or_void<int(...) && noexcept>();
    test_is_complete_or_void<int(...) const noexcept>();
    test_is_complete_or_void<int(...) const & noexcept>();
    test_is_complete_or_void<int(...) const && noexcept>();
    test_is_complete_or_void<int(...) volatile noexcept>();
    test_is_complete_or_void<int(...) volatile & noexcept>();
    test_is_complete_or_void<int(...) volatile && noexcept>();
    test_is_complete_or_void<int(...) const volatile noexcept>();
    test_is_complete_or_void<int(...) const volatile & noexcept>();
    test_is_complete_or_void<int(...) const volatile && noexcept>();

    test_is_complete_or_void<int(int, ...)>();
    test_is_complete_or_void<int(int, ...)&>();
    test_is_complete_or_void<int(int, ...) &&>();
    test_is_complete_or_void<int(int, ...) const>();
    test_is_complete_or_void<int(int, ...) const&>();
    test_is_complete_or_void<int(int, ...) const&&>();
    test_is_complete_or_void<int(int, ...) volatile>();
    test_is_complete_or_void<int(int, ...) volatile&>();
    test_is_complete_or_void<int(int, ...) volatile&&>();
    test_is_complete_or_void<int(int, ...) const volatile>();
    test_is_complete_or_void<int(int, ...) const volatile&>();
    test_is_complete_or_void<int(int, ...) const volatile&&>();
    test_is_complete_or_void<int(int, ...) noexcept>();
    test_is_complete_or_void<int(int, ...) & noexcept>();
    test_is_complete_or_void<int(int, ...) && noexcept>();
    test_is_complete_or_void<int(int, ...) const noexcept>();
    test_is_complete_or_void<int(int, ...) const & noexcept>();
    test_is_complete_or_void<int(int, ...) const && noexcept>();
    test_is_complete_or_void<int(int, ...) volatile noexcept>();
    test_is_complete_or_void<int(int, ...) volatile & noexcept>();
    test_is_complete_or_void<int(int, ...) volatile && noexcept>();
    test_is_complete_or_void<int(int, ...) const volatile noexcept>();
    test_is_complete_or_void<int(int, ...) const volatile & noexcept>();
    test_is_complete_or_void<int(int, ...) const volatile && noexcept>();

    test_is_complete_or_void<void (*)()>();
    test_is_complete_or_void<void (*)() noexcept>();

    test_is_complete_or_void<void (*)(int)>();
    test_is_complete_or_void<void (*)(int) noexcept>();

    test_is_complete_or_void<void (*)(...)>();
    test_is_complete_or_void<void (*)(...) noexcept>();

    test_is_complete_or_void<void (*)(int, ...)>();
    test_is_complete_or_void<void (*)(int, ...) noexcept>();

    test_is_complete_or_void<int (*)()>();
    test_is_complete_or_void<int (*)() noexcept>();

    test_is_complete_or_void<int (*)(int)>();
    test_is_complete_or_void<int (*)(int) noexcept>();

    test_is_complete_or_void<int (*)(...)>();
    test_is_complete_or_void<int (*)(...) noexcept>();

    test_is_complete_or_void<int (*)(int, ...)>();
    test_is_complete_or_void<int (*)(int, ...) noexcept>();

    test_is_complete_or_void<void (&)()>();
    test_is_complete_or_void<void (&)() noexcept>();

    test_is_complete_or_void<void (&)(int)>();
    test_is_complete_or_void<void (&)(int) noexcept>();

    test_is_complete_or_void<void (&)(...)>();
    test_is_complete_or_void<void (&)(...) noexcept>();

    test_is_complete_or_void<void (&)(int, ...)>();
    test_is_complete_or_void<void (&)(int, ...) noexcept>();

    test_is_complete_or_void<int (&)()>();
    test_is_complete_or_void<int (&)() noexcept>();

    test_is_complete_or_void<int (&)(int)>();
    test_is_complete_or_void<int (&)(int) noexcept>();

    test_is_complete_or_void<int (&)(...)>();
    test_is_complete_or_void<int (&)(...) noexcept>();

    test_is_complete_or_void<int (&)(int, ...)>();
    test_is_complete_or_void<int (&)(int, ...) noexcept>();

    test_is_complete_or_void<void (&&)()>();
    test_is_complete_or_void<void (&&)() noexcept>();

    test_is_complete_or_void<void (&&)(int)>();
    test_is_complete_or_void<void (&&)(int) noexcept>();

    test_is_complete_or_void<void (&&)(...)>();
    test_is_complete_or_void<void (&&)(...) noexcept>();

    test_is_complete_or_void<void (&&)(int, ...)>();
    test_is_complete_or_void<void (&&)(int, ...) noexcept>();

    test_is_complete_or_void<int (&&)()>();
    test_is_complete_or_void<int (&&)() noexcept>();

    test_is_complete_or_void<int (&&)(int)>();
    test_is_complete_or_void<int (&&)(int) noexcept>();

    test_is_complete_or_void<int (&&)(...)>();
    test_is_complete_or_void<int (&&)(...) noexcept>();

    test_is_complete_or_void<int (&&)(int, ...)>();
    test_is_complete_or_void<int (&&)(int, ...) noexcept>();

    test_is_complete_or_void<void (class_type::*)()>();
    test_is_complete_or_void<void (class_type::*)()&>();
    test_is_complete_or_void<void (class_type::*)() &&>();
    test_is_complete_or_void<void (class_type::*)() const>();
    test_is_complete_or_void<void (class_type::*)() const&>();
    test_is_complete_or_void<void (class_type::*)() const&&>();
    test_is_complete_or_void<void (class_type::*)() noexcept>();
    test_is_complete_or_void<void (class_type::*)() & noexcept>();
    test_is_complete_or_void<void (class_type::*)() && noexcept>();
    test_is_complete_or_void<void (class_type::*)() const noexcept>();
    test_is_complete_or_void<void (class_type::*)() const & noexcept>();
    test_is_complete_or_void<void (class_type::*)() const && noexcept>();

    test_is_complete_or_void<void (class_type::*)(int)>();
    test_is_complete_or_void<void (class_type::*)(int)&>();
    test_is_complete_or_void<void (class_type::*)(int) &&>();
    test_is_complete_or_void<void (class_type::*)(int) const>();
    test_is_complete_or_void<void (class_type::*)(int) const&>();
    test_is_complete_or_void<void (class_type::*)(int) const&&>();
    test_is_complete_or_void<void (class_type::*)(int) noexcept>();
    test_is_complete_or_void<void (class_type::*)(int) & noexcept>();
    test_is_complete_or_void<void (class_type::*)(int) && noexcept>();
    test_is_complete_or_void<void (class_type::*)(int) const noexcept>();
    test_is_complete_or_void<void (class_type::*)(int) const & noexcept>();
    test_is_complete_or_void<void (class_type::*)(int) const && noexcept>();

    test_is_complete_or_void<void (class_type::*)(...)>();
    test_is_complete_or_void<void (class_type::*)(...)&>();
    test_is_complete_or_void<void (class_type::*)(...) &&>();
    test_is_complete_or_void<void (class_type::*)(...) const>();
    test_is_complete_or_void<void (class_type::*)(...) const&>();
    test_is_complete_or_void<void (class_type::*)(...) const&&>();
    test_is_complete_or_void<void (class_type::*)(...) noexcept>();
    test_is_complete_or_void<void (class_type::*)(...) & noexcept>();
    test_is_complete_or_void<void (class_type::*)(...) && noexcept>();
    test_is_complete_or_void<void (class_type::*)(...) const noexcept>();
    test_is_complete_or_void<void (class_type::*)(...) const & noexcept>();
    test_is_complete_or_void<void (class_type::*)(...) const && noexcept>();

    test_is_complete_or_void<void (class_type::*)(int, ...)>();
    test_is_complete_or_void<void (class_type::*)(int, ...)&>();
    test_is_complete_or_void<void (class_type::*)(int, ...) &&>();
    test_is_complete_or_void<void (class_type::*)(int, ...) const>();
    test_is_complete_or_void<void (class_type::*)(int, ...) const&>();
    test_is_complete_or_void<void (class_type::*)(int, ...) const&&>();
    test_is_complete_or_void<void (class_type::*)(int, ...) noexcept>();
    test_is_complete_or_void<void (class_type::*)(int, ...) & noexcept>();
    test_is_complete_or_void<void (class_type::*)(int, ...) && noexcept>();
    test_is_complete_or_void<void (class_type::*)(int, ...) const noexcept>();
    test_is_complete_or_void<void (class_type::*)(int, ...) const & noexcept>();
    test_is_complete_or_void<void (class_type::*)(int, ...) const && noexcept>();

    test_is_complete_or_void<int (class_type::*)()>();
    test_is_complete_or_void<int (class_type::*)()&>();
    test_is_complete_or_void<int (class_type::*)() &&>();
    test_is_complete_or_void<int (class_type::*)() const>();
    test_is_complete_or_void<int (class_type::*)() const&>();
    test_is_complete_or_void<int (class_type::*)() const&&>();
    test_is_complete_or_void<int (class_type::*)() noexcept>();
    test_is_complete_or_void<int (class_type::*)() & noexcept>();
    test_is_complete_or_void<int (class_type::*)() && noexcept>();
    test_is_complete_or_void<int (class_type::*)() const noexcept>();
    test_is_complete_or_void<int (class_type::*)() const & noexcept>();
    test_is_complete_or_void<int (class_type::*)() const && noexcept>();

    test_is_complete_or_void<int (class_type::*)(int)>();
    test_is_complete_or_void<int (class_type::*)(int)&>();
    test_is_complete_or_void<int (class_type::*)(int) &&>();
    test_is_complete_or_void<int (class_type::*)(int) const>();
    test_is_complete_or_void<int (class_type::*)(int) const&>();
    test_is_complete_or_void<int (class_type::*)(int) const&&>();
    test_is_complete_or_void<int (class_type::*)(int) noexcept>();
    test_is_complete_or_void<int (class_type::*)(int) & noexcept>();
    test_is_complete_or_void<int (class_type::*)(int) && noexcept>();
    test_is_complete_or_void<int (class_type::*)(int) const noexcept>();
    test_is_complete_or_void<int (class_type::*)(int) const & noexcept>();
    test_is_complete_or_void<int (class_type::*)(int) const && noexcept>();

    test_is_complete_or_void<int (class_type::*)(...)>();
    test_is_complete_or_void<int (class_type::*)(...)&>();
    test_is_complete_or_void<int (class_type::*)(...) &&>();
    test_is_complete_or_void<int (class_type::*)(...) const>();
    test_is_complete_or_void<int (class_type::*)(...) const&>();
    test_is_complete_or_void<int (class_type::*)(...) const&&>();
    test_is_complete_or_void<int (class_type::*)(...) noexcept>();
    test_is_complete_or_void<int (class_type::*)(...) & noexcept>();
    test_is_complete_or_void<int (class_type::*)(...) && noexcept>();
    test_is_complete_or_void<int (class_type::*)(...) const noexcept>();
    test_is_complete_or_void<int (class_type::*)(...) const & noexcept>();
    test_is_complete_or_void<int (class_type::*)(...) const && noexcept>();

    test_is_complete_or_void<int (class_type::*)(int, ...)>();
    test_is_complete_or_void<int (class_type::*)(int, ...)&>();
    test_is_complete_or_void<int (class_type::*)(int, ...) &&>();
    test_is_complete_or_void<int (class_type::*)(int, ...) const>();
    test_is_complete_or_void<int (class_type::*)(int, ...) const&>();
    test_is_complete_or_void<int (class_type::*)(int, ...) const&&>();
    test_is_complete_or_void<int (class_type::*)(int, ...) noexcept>();
    test_is_complete_or_void<int (class_type::*)(int, ...) & noexcept>();
    test_is_complete_or_void<int (class_type::*)(int, ...) && noexcept>();
    test_is_complete_or_void<int (class_type::*)(int, ...) const noexcept>();
    test_is_complete_or_void<int (class_type::*)(int, ...) const & noexcept>();
    test_is_complete_or_void<int (class_type::*)(int, ...) const && noexcept>();
}
