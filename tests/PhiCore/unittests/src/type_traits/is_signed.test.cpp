#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/compiler_support/platform.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_signed.hpp>
#include <phi/type_traits/make_unsafe.hpp>
#include <type_traits>
#include <vector>

struct A; // incomplete

template <typename TypeT>
void test_is_signed_impl()
{
    STATIC_REQUIRE(phi::is_signed<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_signed<TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_signed_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_not_signed_v<TypeT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_signed<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_signed<TypeT>);

    // Standard compatibility
    STATIC_REQUIRE(std::is_signed<phi::make_unsafe_t<TypeT>>::value);
}

template <typename TypeT>
void test_is_not_signed_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_signed<TypeT>::value);
    STATIC_REQUIRE(phi::is_not_signed<TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_signed_v<TypeT>);
    STATIC_REQUIRE(phi::is_not_signed_v<TypeT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_signed<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_signed<TypeT>);

    // Standard compatibility
    STATIC_REQUIRE_FALSE(std::is_signed<TypeT>::value);
}

template <typename TypeT>
void test_is_signed()
{
    test_is_signed_impl<TypeT>();
    test_is_signed_impl<const TypeT>();
    test_is_signed_impl<volatile TypeT>();
    test_is_signed_impl<const volatile TypeT>();
}

template <typename TypeT>
void test_is_not_signed()
{
    test_is_not_signed_impl<TypeT>();
    test_is_not_signed_impl<const TypeT>();
    test_is_not_signed_impl<volatile TypeT>();
    test_is_not_signed_impl<const volatile TypeT>();
}

TEST_CASE("is_signed")
{
    test_is_not_signed<void>();
    test_is_not_signed<phi::nullptr_t>();
    test_is_not_signed<bool>();
#if PHI_TYPE_SYSTEM_CHAR_SIGNED()
    test_is_signed<char>();
#else
    test_is_not_signed<char>();
#endif
    test_is_signed<signed char>();
    test_is_not_signed<unsigned char>();
    test_is_signed<short>();
    test_is_not_signed<unsigned short>();
    test_is_signed<int>();
    test_is_not_signed<unsigned int>();
    test_is_signed<long>();
    test_is_not_signed<unsigned long>();
    test_is_signed<long long>();
    test_is_not_signed<unsigned long long>();
    test_is_signed<float>();
    test_is_signed<double>();
    test_is_signed<long double>();
    test_is_not_signed<char8_t>();
    test_is_not_signed<char16_t>();
    test_is_not_signed<char32_t>();
#if PHI_TYPE_SYSTEM_WCHAR_T_SIGNED()
    test_is_signed<wchar_t>();
#else
    test_is_not_signed<wchar_t>();
#endif

    test_is_not_signed<phi::boolean>();
    test_is_signed<phi::integer<signed char>>();
    test_is_not_signed<phi::integer<unsigned char>>();
    test_is_signed<phi::integer<short>>();
    test_is_not_signed<phi::integer<unsigned short>>();
    test_is_signed<phi::integer<int>>();
    test_is_not_signed<phi::integer<unsigned int>>();
    test_is_signed<phi::integer<long>>();
    test_is_not_signed<phi::integer<unsigned long>>();
    test_is_signed<phi::integer<long long>>();
    test_is_not_signed<phi::integer<unsigned long long>>();
    test_is_signed<phi::floating_point<float>>();
    test_is_signed<phi::floating_point<double>>();
    test_is_signed<phi::floating_point<long double>>();

    test_is_not_signed<std::vector<int>>();
    test_is_not_signed<phi::scope_ptr<int>>();

    test_is_not_signed<int&>();
    test_is_not_signed<const int&>();
    test_is_not_signed<volatile int&>();
    test_is_not_signed<const volatile int&>();
    test_is_not_signed<int&&>();
    test_is_not_signed<const int&&>();
    test_is_not_signed<volatile int&&>();
    test_is_not_signed<const volatile int&&>();
    test_is_not_signed<int*>();
    test_is_not_signed<const int*>();
    test_is_not_signed<volatile int*>();
    test_is_not_signed<const volatile int*>();
    test_is_not_signed<int**>();
    test_is_not_signed<const int**>();
    test_is_not_signed<volatile int**>();
    test_is_not_signed<const volatile int**>();
    test_is_not_signed<int*&>();
    test_is_not_signed<const int*&>();
    test_is_not_signed<volatile int*&>();
    test_is_not_signed<const volatile int*&>();
    test_is_not_signed<int*&&>();
    test_is_not_signed<const int*&&>();
    test_is_not_signed<volatile int*&&>();
    test_is_not_signed<const volatile int*&&>();
    test_is_not_signed<void*>();
    test_is_not_signed<char[3]>();
    test_is_not_signed<char[]>();
    test_is_not_signed<char* [3]>();
    test_is_not_signed<char*[]>();
    test_is_not_signed<int(*)[3]>();
    test_is_not_signed<int(*)[]>();
    test_is_not_signed<int(&)[3]>();
    test_is_not_signed<int(&)[]>();
    test_is_not_signed<int(&&)[3]>();
    test_is_not_signed<int(&&)[]>();
    test_is_not_signed<char[3][2]>();
    test_is_not_signed<char[][2]>();
    test_is_not_signed<char* [3][2]>();
    test_is_not_signed<char*[][2]>();
    test_is_not_signed<int(*)[3][2]>();
    test_is_not_signed<int(*)[][2]>();
    test_is_not_signed<int(&)[3][2]>();
    test_is_not_signed<int(&)[][2]>();
    test_is_not_signed<int(&&)[3][2]>();
    test_is_not_signed<int(&&)[][2]>();
    test_is_not_signed<class_type>();
    test_is_not_signed<class_type[]>();
    test_is_not_signed<class_type[2]>();
    test_is_not_signed<template_type<void>>();
    test_is_not_signed<template_type<int>>();
    test_is_not_signed<template_type<class_type>>();
    test_is_not_signed<template_type<incomplete_type>>();
    test_is_not_signed<variadic_template<>>();
    test_is_not_signed<variadic_template<void>>();
    test_is_not_signed<variadic_template<int>>();
    test_is_not_signed<variadic_template<class_type>>();
    test_is_not_signed<variadic_template<incomplete_type>>();
    test_is_not_signed<variadic_template<int, void, class_type, volatile char[]>>();
    test_is_not_signed<public_derived_from<base>>();
    test_is_not_signed<public_derived_from<derived>>();
    test_is_not_signed<public_derived_from<class_type>>();
    test_is_not_signed<private_derived_from<base>>();
    test_is_not_signed<private_derived_from<derived>>();
    test_is_not_signed<private_derived_from<class_type>>();
    test_is_not_signed<protected_derived_from<base>>();
    test_is_not_signed<protected_derived_from<derived>>();
    test_is_not_signed<protected_derived_from<class_type>>();
    test_is_not_signed<union_type>();
    test_is_not_signed<non_empty_union>();
    test_is_not_signed<empty>();
    test_is_not_signed<not_empty>();
    test_is_not_signed<bit_zero>();
    test_is_not_signed<bit_one>();
    test_is_not_signed<base>();
    test_is_not_signed<derived>();
    test_is_not_signed<abstract>();
    test_is_not_signed<public_abstract>();
    test_is_not_signed<private_abstract>();
    test_is_not_signed<protected_abstract>();
    test_is_not_signed<abstract_template<int>>();
    test_is_not_signed<abstract_template<double>>();
    test_is_not_signed<abstract_template<class_type>>();
    test_is_not_signed<abstract_template<incomplete_type>>();
    test_is_not_signed<final_type>();
    test_is_not_signed<public_destructor>();
    test_is_not_signed<protected_destructor>();
    test_is_not_signed<private_destructor>();
    test_is_not_signed<virtual_public_destructor>();
    test_is_not_signed<virtual_protected_destructor>();
    test_is_not_signed<virtual_private_destructor>();
    test_is_not_signed<pure_public_destructor>();
    test_is_not_signed<pure_protected_destructor>();
    test_is_not_signed<pure_private_destructor>();
    test_is_not_signed<deleted_public_destructor>();
    test_is_not_signed<deleted_protected_destructor>();
    test_is_not_signed<deleted_private_destructor>();
    test_is_not_signed<deleted_virtual_public_destructor>();
    test_is_not_signed<deleted_virtual_protected_destructor>();
    test_is_not_signed<deleted_virtual_private_destructor>();
    test_is_not_signed<Enum>();
    test_is_not_signed<EnumSigned>();
    test_is_not_signed<EnumUnsigned>();
    test_is_not_signed<EnumClass>();
    test_is_not_signed<EnumStruct>();
    test_is_not_signed<function_type>();
    test_is_not_signed<function_ptr>();
    test_is_not_signed<member_object_ptr>();
    test_is_not_signed<member_function_ptr>();
    test_is_not_signed<incomplete_type>();
    test_is_not_signed<incomplete_template<void>>();
    test_is_not_signed<incomplete_template<int>>();
    test_is_not_signed<incomplete_template<class_type>>();
    test_is_not_signed<incomplete_template<incomplete_type>>();
    test_is_not_signed<incomplete_variadic_template<>>();
    test_is_not_signed<incomplete_variadic_template<void>>();
    test_is_not_signed<incomplete_variadic_template<int>>();
    test_is_not_signed<incomplete_variadic_template<class_type>>();
    test_is_not_signed<incomplete_variadic_template<incomplete_type>>();
    test_is_not_signed<incomplete_variadic_template<int, void, class_type, volatile char[]>>();
    test_is_not_signed<int class_type::*>();
    test_is_not_signed<float class_type::*>();
    test_is_not_signed<void * class_type::*>();
    test_is_not_signed<int * class_type::*>();
    test_is_not_signed<int class_type::*&>();
    test_is_not_signed<float class_type::*&>();
    test_is_not_signed<void * class_type::*&>();
    test_is_not_signed<int * class_type::*&>();
    test_is_not_signed<int class_type::*&&>();
    test_is_not_signed<float class_type::*&&>();
    test_is_not_signed<void * class_type::*&&>();
    test_is_not_signed<int * class_type::*&&>();
    test_is_not_signed<int class_type::* const>();
    test_is_not_signed<float class_type::* const>();
    test_is_not_signed<void * class_type::* const>();
    test_is_not_signed<int class_type::* const&>();
    test_is_not_signed<float class_type::* const&>();
    test_is_not_signed<void * class_type::* const&>();
    test_is_not_signed<int class_type::* const&&>();
    test_is_not_signed<float class_type::* const&&>();
    test_is_not_signed<void * class_type::* const&&>();
    test_is_not_signed<int class_type::* volatile>();
    test_is_not_signed<float class_type::* volatile>();
    test_is_not_signed<void * class_type::* volatile>();
    test_is_not_signed<int class_type::* volatile&>();
    test_is_not_signed<float class_type::* volatile&>();
    test_is_not_signed<void * class_type::* volatile&>();
    test_is_not_signed<int class_type::* volatile&&>();
    test_is_not_signed<float class_type::* volatile&&>();
    test_is_not_signed<void * class_type::* volatile&&>();
    test_is_not_signed<int class_type::* const volatile>();
    test_is_not_signed<float class_type::* const volatile>();
    test_is_not_signed<void * class_type::* const volatile>();
    test_is_not_signed<int class_type::* const volatile&>();
    test_is_not_signed<float class_type::* const volatile&>();
    test_is_not_signed<void * class_type::* const volatile&>();
    test_is_not_signed<int class_type::* const volatile&&>();
    test_is_not_signed<float class_type::* const volatile&&>();
    test_is_not_signed<void * class_type::* const volatile&&>();
    test_is_not_signed<non_copyable>();
    test_is_not_signed<non_moveable>();
    test_is_not_signed<non_constructible>();
    test_is_not_signed<tracked>();
    test_is_not_signed<trap_constructible>();
    test_is_not_signed<trap_implicit_conversion>();
    test_is_not_signed<trap_comma>();
    test_is_not_signed<trap_call>();
    test_is_not_signed<trap_self_assign>();
    test_is_not_signed<trap_deref>();
    test_is_not_signed<trap_array_subscript>();

    test_is_not_signed<void()>();
    test_is_not_signed<void()&>();
    test_is_not_signed<void() &&>();
    test_is_not_signed<void() const>();
    test_is_not_signed<void() const&>();
    test_is_not_signed<void() const&&>();
    test_is_not_signed<void() volatile>();
    test_is_not_signed<void() volatile&>();
    test_is_not_signed<void() volatile&&>();
    test_is_not_signed<void() const volatile>();
    test_is_not_signed<void() const volatile&>();
    test_is_not_signed<void() const volatile&&>();
    test_is_not_signed<void() noexcept>();
    test_is_not_signed<void() & noexcept>();
    test_is_not_signed<void() && noexcept>();
    test_is_not_signed<void() const noexcept>();
    test_is_not_signed<void() const & noexcept>();
    test_is_not_signed<void() const && noexcept>();
    test_is_not_signed<void() volatile noexcept>();
    test_is_not_signed<void() volatile & noexcept>();
    test_is_not_signed<void() volatile && noexcept>();
    test_is_not_signed<void() const volatile noexcept>();
    test_is_not_signed<void() const volatile & noexcept>();
    test_is_not_signed<void() const volatile && noexcept>();

    test_is_not_signed<void(int)>();
    test_is_not_signed<void(int)&>();
    test_is_not_signed<void(int) &&>();
    test_is_not_signed<void(int) const>();
    test_is_not_signed<void(int) const&>();
    test_is_not_signed<void(int) const&&>();
    test_is_not_signed<void(int) volatile>();
    test_is_not_signed<void(int) volatile&>();
    test_is_not_signed<void(int) volatile&&>();
    test_is_not_signed<void(int) const volatile>();
    test_is_not_signed<void(int) const volatile&>();
    test_is_not_signed<void(int) const volatile&&>();
    test_is_not_signed<void(int) noexcept>();
    test_is_not_signed<void(int) & noexcept>();
    test_is_not_signed<void(int) && noexcept>();
    test_is_not_signed<void(int) const noexcept>();
    test_is_not_signed<void(int) const & noexcept>();
    test_is_not_signed<void(int) const && noexcept>();
    test_is_not_signed<void(int) volatile noexcept>();
    test_is_not_signed<void(int) volatile & noexcept>();
    test_is_not_signed<void(int) volatile && noexcept>();
    test_is_not_signed<void(int) const volatile noexcept>();
    test_is_not_signed<void(int) const volatile & noexcept>();
    test_is_not_signed<void(int) const volatile && noexcept>();

    test_is_not_signed<void(...)>();
    test_is_not_signed<void(...)&>();
    test_is_not_signed<void(...) &&>();
    test_is_not_signed<void(...) const>();
    test_is_not_signed<void(...) const&>();
    test_is_not_signed<void(...) const&&>();
    test_is_not_signed<void(...) volatile>();
    test_is_not_signed<void(...) volatile&>();
    test_is_not_signed<void(...) volatile&&>();
    test_is_not_signed<void(...) const volatile>();
    test_is_not_signed<void(...) const volatile&>();
    test_is_not_signed<void(...) const volatile&&>();
    test_is_not_signed<void(...) noexcept>();
    test_is_not_signed<void(...) & noexcept>();
    test_is_not_signed<void(...) && noexcept>();
    test_is_not_signed<void(...) const noexcept>();
    test_is_not_signed<void(...) const & noexcept>();
    test_is_not_signed<void(...) const && noexcept>();
    test_is_not_signed<void(...) volatile noexcept>();
    test_is_not_signed<void(...) volatile & noexcept>();
    test_is_not_signed<void(...) volatile && noexcept>();
    test_is_not_signed<void(...) const volatile noexcept>();
    test_is_not_signed<void(...) const volatile & noexcept>();
    test_is_not_signed<void(...) const volatile && noexcept>();

    test_is_not_signed<void(int, ...)>();
    test_is_not_signed<void(int, ...)&>();
    test_is_not_signed<void(int, ...) &&>();
    test_is_not_signed<void(int, ...) const>();
    test_is_not_signed<void(int, ...) const&>();
    test_is_not_signed<void(int, ...) const&&>();
    test_is_not_signed<void(int, ...) volatile>();
    test_is_not_signed<void(int, ...) volatile&>();
    test_is_not_signed<void(int, ...) volatile&&>();
    test_is_not_signed<void(int, ...) const volatile>();
    test_is_not_signed<void(int, ...) const volatile&>();
    test_is_not_signed<void(int, ...) const volatile&&>();
    test_is_not_signed<void(int, ...) noexcept>();
    test_is_not_signed<void(int, ...) & noexcept>();
    test_is_not_signed<void(int, ...) && noexcept>();
    test_is_not_signed<void(int, ...) const noexcept>();
    test_is_not_signed<void(int, ...) const & noexcept>();
    test_is_not_signed<void(int, ...) const && noexcept>();
    test_is_not_signed<void(int, ...) volatile noexcept>();
    test_is_not_signed<void(int, ...) volatile & noexcept>();
    test_is_not_signed<void(int, ...) volatile && noexcept>();
    test_is_not_signed<void(int, ...) const volatile noexcept>();
    test_is_not_signed<void(int, ...) const volatile & noexcept>();
    test_is_not_signed<void(int, ...) const volatile && noexcept>();

    test_is_not_signed<int()>();
    test_is_not_signed<int()&>();
    test_is_not_signed<int() &&>();
    test_is_not_signed<int() const>();
    test_is_not_signed<int() const&>();
    test_is_not_signed<int() const&&>();
    test_is_not_signed<int() volatile>();
    test_is_not_signed<int() volatile&>();
    test_is_not_signed<int() volatile&&>();
    test_is_not_signed<int() const volatile>();
    test_is_not_signed<int() const volatile&>();
    test_is_not_signed<int() const volatile&&>();
    test_is_not_signed<int() noexcept>();
    test_is_not_signed<int() & noexcept>();
    test_is_not_signed<int() && noexcept>();
    test_is_not_signed<int() const noexcept>();
    test_is_not_signed<int() const & noexcept>();
    test_is_not_signed<int() const && noexcept>();
    test_is_not_signed<int() volatile noexcept>();
    test_is_not_signed<int() volatile & noexcept>();
    test_is_not_signed<int() volatile && noexcept>();
    test_is_not_signed<int() const volatile noexcept>();
    test_is_not_signed<int() const volatile & noexcept>();
    test_is_not_signed<int() const volatile && noexcept>();

    test_is_not_signed<int(int)>();
    test_is_not_signed<int(int)&>();
    test_is_not_signed<int(int) &&>();
    test_is_not_signed<int(int) const>();
    test_is_not_signed<int(int) const&>();
    test_is_not_signed<int(int) const&&>();
    test_is_not_signed<int(int) volatile>();
    test_is_not_signed<int(int) volatile&>();
    test_is_not_signed<int(int) volatile&&>();
    test_is_not_signed<int(int) const volatile>();
    test_is_not_signed<int(int) const volatile&>();
    test_is_not_signed<int(int) const volatile&&>();
    test_is_not_signed<int(int) noexcept>();
    test_is_not_signed<int(int) & noexcept>();
    test_is_not_signed<int(int) && noexcept>();
    test_is_not_signed<int(int) const noexcept>();
    test_is_not_signed<int(int) const & noexcept>();
    test_is_not_signed<int(int) const && noexcept>();
    test_is_not_signed<int(int) volatile noexcept>();
    test_is_not_signed<int(int) volatile & noexcept>();
    test_is_not_signed<int(int) volatile && noexcept>();
    test_is_not_signed<int(int) const volatile noexcept>();
    test_is_not_signed<int(int) const volatile & noexcept>();
    test_is_not_signed<int(int) const volatile && noexcept>();

    test_is_not_signed<int(...)>();
    test_is_not_signed<int(...)&>();
    test_is_not_signed<int(...) &&>();
    test_is_not_signed<int(...) const>();
    test_is_not_signed<int(...) const&>();
    test_is_not_signed<int(...) const&&>();
    test_is_not_signed<int(...) volatile>();
    test_is_not_signed<int(...) volatile&>();
    test_is_not_signed<int(...) volatile&&>();
    test_is_not_signed<int(...) const volatile>();
    test_is_not_signed<int(...) const volatile&>();
    test_is_not_signed<int(...) const volatile&&>();
    test_is_not_signed<int(...) noexcept>();
    test_is_not_signed<int(...) & noexcept>();
    test_is_not_signed<int(...) && noexcept>();
    test_is_not_signed<int(...) const noexcept>();
    test_is_not_signed<int(...) const & noexcept>();
    test_is_not_signed<int(...) const && noexcept>();
    test_is_not_signed<int(...) volatile noexcept>();
    test_is_not_signed<int(...) volatile & noexcept>();
    test_is_not_signed<int(...) volatile && noexcept>();
    test_is_not_signed<int(...) const volatile noexcept>();
    test_is_not_signed<int(...) const volatile & noexcept>();
    test_is_not_signed<int(...) const volatile && noexcept>();

    test_is_not_signed<int(int, ...)>();
    test_is_not_signed<int(int, ...)&>();
    test_is_not_signed<int(int, ...) &&>();
    test_is_not_signed<int(int, ...) const>();
    test_is_not_signed<int(int, ...) const&>();
    test_is_not_signed<int(int, ...) const&&>();
    test_is_not_signed<int(int, ...) volatile>();
    test_is_not_signed<int(int, ...) volatile&>();
    test_is_not_signed<int(int, ...) volatile&&>();
    test_is_not_signed<int(int, ...) const volatile>();
    test_is_not_signed<int(int, ...) const volatile&>();
    test_is_not_signed<int(int, ...) const volatile&&>();
    test_is_not_signed<int(int, ...) noexcept>();
    test_is_not_signed<int(int, ...) & noexcept>();
    test_is_not_signed<int(int, ...) && noexcept>();
    test_is_not_signed<int(int, ...) const noexcept>();
    test_is_not_signed<int(int, ...) const & noexcept>();
    test_is_not_signed<int(int, ...) const && noexcept>();
    test_is_not_signed<int(int, ...) volatile noexcept>();
    test_is_not_signed<int(int, ...) volatile & noexcept>();
    test_is_not_signed<int(int, ...) volatile && noexcept>();
    test_is_not_signed<int(int, ...) const volatile noexcept>();
    test_is_not_signed<int(int, ...) const volatile & noexcept>();
    test_is_not_signed<int(int, ...) const volatile && noexcept>();

    test_is_not_signed<void (*)()>();
    test_is_not_signed<void (*)() noexcept>();

    test_is_not_signed<void (*)(int)>();
    test_is_not_signed<void (*)(int) noexcept>();

    test_is_not_signed<void (*)(...)>();
    test_is_not_signed<void (*)(...) noexcept>();

    test_is_not_signed<void (*)(int, ...)>();
    test_is_not_signed<void (*)(int, ...) noexcept>();

    test_is_not_signed<int (*)()>();
    test_is_not_signed<int (*)() noexcept>();

    test_is_not_signed<int (*)(int)>();
    test_is_not_signed<int (*)(int) noexcept>();

    test_is_not_signed<int (*)(...)>();
    test_is_not_signed<int (*)(...) noexcept>();

    test_is_not_signed<int (*)(int, ...)>();
    test_is_not_signed<int (*)(int, ...) noexcept>();

    test_is_not_signed<void (&)()>();
    test_is_not_signed<void (&)() noexcept>();

    test_is_not_signed<void (&)(int)>();
    test_is_not_signed<void (&)(int) noexcept>();

    test_is_not_signed<void (&)(...)>();
    test_is_not_signed<void (&)(...) noexcept>();

    test_is_not_signed<void (&)(int, ...)>();
    test_is_not_signed<void (&)(int, ...) noexcept>();

    test_is_not_signed<int (&)()>();
    test_is_not_signed<int (&)() noexcept>();

    test_is_not_signed<int (&)(int)>();
    test_is_not_signed<int (&)(int) noexcept>();

    test_is_not_signed<int (&)(...)>();
    test_is_not_signed<int (&)(...) noexcept>();

    test_is_not_signed<int (&)(int, ...)>();
    test_is_not_signed<int (&)(int, ...) noexcept>();

    test_is_not_signed<void (&&)()>();
    test_is_not_signed<void (&&)() noexcept>();

    test_is_not_signed<void (&&)(int)>();
    test_is_not_signed<void (&&)(int) noexcept>();

    test_is_not_signed<void (&&)(...)>();
    test_is_not_signed<void (&&)(...) noexcept>();

    test_is_not_signed<void (&&)(int, ...)>();
    test_is_not_signed<void (&&)(int, ...) noexcept>();

    test_is_not_signed<int (&&)()>();
    test_is_not_signed<int (&&)() noexcept>();

    test_is_not_signed<int (&&)(int)>();
    test_is_not_signed<int (&&)(int) noexcept>();

    test_is_not_signed<int (&&)(...)>();
    test_is_not_signed<int (&&)(...) noexcept>();

    test_is_not_signed<int (&&)(int, ...)>();
    test_is_not_signed<int (&&)(int, ...) noexcept>();

    test_is_not_signed<void (class_type::*)()>();
    test_is_not_signed<void (class_type::*)()&>();
    test_is_not_signed<void (class_type::*)() &&>();
    test_is_not_signed<void (class_type::*)() const>();
    test_is_not_signed<void (class_type::*)() const&>();
    test_is_not_signed<void (class_type::*)() const&&>();
    test_is_not_signed<void (class_type::*)() noexcept>();
    test_is_not_signed<void (class_type::*)() & noexcept>();
    test_is_not_signed<void (class_type::*)() && noexcept>();
    test_is_not_signed<void (class_type::*)() const noexcept>();
    test_is_not_signed<void (class_type::*)() const & noexcept>();
    test_is_not_signed<void (class_type::*)() const && noexcept>();

    test_is_not_signed<void (class_type::*)(int)>();
    test_is_not_signed<void (class_type::*)(int)&>();
    test_is_not_signed<void (class_type::*)(int) &&>();
    test_is_not_signed<void (class_type::*)(int) const>();
    test_is_not_signed<void (class_type::*)(int) const&>();
    test_is_not_signed<void (class_type::*)(int) const&&>();
    test_is_not_signed<void (class_type::*)(int) noexcept>();
    test_is_not_signed<void (class_type::*)(int) & noexcept>();
    test_is_not_signed<void (class_type::*)(int) && noexcept>();
    test_is_not_signed<void (class_type::*)(int) const noexcept>();
    test_is_not_signed<void (class_type::*)(int) const & noexcept>();
    test_is_not_signed<void (class_type::*)(int) const && noexcept>();

    test_is_not_signed<void (class_type::*)(...)>();
    test_is_not_signed<void (class_type::*)(...)&>();
    test_is_not_signed<void (class_type::*)(...) &&>();
    test_is_not_signed<void (class_type::*)(...) const>();
    test_is_not_signed<void (class_type::*)(...) const&>();
    test_is_not_signed<void (class_type::*)(...) const&&>();
    test_is_not_signed<void (class_type::*)(...) noexcept>();
    test_is_not_signed<void (class_type::*)(...) & noexcept>();
    test_is_not_signed<void (class_type::*)(...) && noexcept>();
    test_is_not_signed<void (class_type::*)(...) const noexcept>();
    test_is_not_signed<void (class_type::*)(...) const & noexcept>();
    test_is_not_signed<void (class_type::*)(...) const && noexcept>();

    test_is_not_signed<void (class_type::*)(int, ...)>();
    test_is_not_signed<void (class_type::*)(int, ...)&>();
    test_is_not_signed<void (class_type::*)(int, ...) &&>();
    test_is_not_signed<void (class_type::*)(int, ...) const>();
    test_is_not_signed<void (class_type::*)(int, ...) const&>();
    test_is_not_signed<void (class_type::*)(int, ...) const&&>();
    test_is_not_signed<void (class_type::*)(int, ...) noexcept>();
    test_is_not_signed<void (class_type::*)(int, ...) & noexcept>();
    test_is_not_signed<void (class_type::*)(int, ...) && noexcept>();
    test_is_not_signed<void (class_type::*)(int, ...) const noexcept>();
    test_is_not_signed<void (class_type::*)(int, ...) const & noexcept>();
    test_is_not_signed<void (class_type::*)(int, ...) const && noexcept>();

    test_is_not_signed<int (class_type::*)()>();
    test_is_not_signed<int (class_type::*)()&>();
    test_is_not_signed<int (class_type::*)() &&>();
    test_is_not_signed<int (class_type::*)() const>();
    test_is_not_signed<int (class_type::*)() const&>();
    test_is_not_signed<int (class_type::*)() const&&>();
    test_is_not_signed<int (class_type::*)() noexcept>();
    test_is_not_signed<int (class_type::*)() & noexcept>();
    test_is_not_signed<int (class_type::*)() && noexcept>();
    test_is_not_signed<int (class_type::*)() const noexcept>();
    test_is_not_signed<int (class_type::*)() const & noexcept>();
    test_is_not_signed<int (class_type::*)() const && noexcept>();

    test_is_not_signed<int (class_type::*)(int)>();
    test_is_not_signed<int (class_type::*)(int)&>();
    test_is_not_signed<int (class_type::*)(int) &&>();
    test_is_not_signed<int (class_type::*)(int) const>();
    test_is_not_signed<int (class_type::*)(int) const&>();
    test_is_not_signed<int (class_type::*)(int) const&&>();
    test_is_not_signed<int (class_type::*)(int) noexcept>();
    test_is_not_signed<int (class_type::*)(int) & noexcept>();
    test_is_not_signed<int (class_type::*)(int) && noexcept>();
    test_is_not_signed<int (class_type::*)(int) const noexcept>();
    test_is_not_signed<int (class_type::*)(int) const & noexcept>();
    test_is_not_signed<int (class_type::*)(int) const && noexcept>();

    test_is_not_signed<int (class_type::*)(...)>();
    test_is_not_signed<int (class_type::*)(...)&>();
    test_is_not_signed<int (class_type::*)(...) &&>();
    test_is_not_signed<int (class_type::*)(...) const>();
    test_is_not_signed<int (class_type::*)(...) const&>();
    test_is_not_signed<int (class_type::*)(...) const&&>();
    test_is_not_signed<int (class_type::*)(...) noexcept>();
    test_is_not_signed<int (class_type::*)(...) & noexcept>();
    test_is_not_signed<int (class_type::*)(...) && noexcept>();
    test_is_not_signed<int (class_type::*)(...) const noexcept>();
    test_is_not_signed<int (class_type::*)(...) const & noexcept>();
    test_is_not_signed<int (class_type::*)(...) const && noexcept>();

    test_is_not_signed<int (class_type::*)(int, ...)>();
    test_is_not_signed<int (class_type::*)(int, ...)&>();
    test_is_not_signed<int (class_type::*)(int, ...) &&>();
    test_is_not_signed<int (class_type::*)(int, ...) const>();
    test_is_not_signed<int (class_type::*)(int, ...) const&>();
    test_is_not_signed<int (class_type::*)(int, ...) const&&>();
    test_is_not_signed<int (class_type::*)(int, ...) noexcept>();
    test_is_not_signed<int (class_type::*)(int, ...) & noexcept>();
    test_is_not_signed<int (class_type::*)(int, ...) && noexcept>();
    test_is_not_signed<int (class_type::*)(int, ...) const noexcept>();
    test_is_not_signed<int (class_type::*)(int, ...) const & noexcept>();
    test_is_not_signed<int (class_type::*)(int, ...) const && noexcept>();
}
