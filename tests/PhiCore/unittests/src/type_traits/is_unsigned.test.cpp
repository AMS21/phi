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
#include <phi/type_traits/is_unsigned.hpp>
#include <phi/type_traits/make_unsafe.hpp>
#include <type_traits>
#include <vector>

template <typename TypeT>
void test_is_unsigned_impl()
{
    STATIC_REQUIRE(phi::is_unsigned<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_unsigned<TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_unsigned_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_not_unsigned_v<TypeT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_unsigned<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_unsigned<TypeT>);

    // Standard compatibility
    STATIC_REQUIRE(std::is_unsigned<phi::make_unsafe_t<TypeT>>::value);
}

template <typename TypeT>
void test_is_not_unsigned_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_unsigned<TypeT>::value);
    STATIC_REQUIRE(phi::is_not_unsigned<TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_unsigned_v<TypeT>);
    STATIC_REQUIRE(phi::is_not_unsigned_v<TypeT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_unsigned<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_unsigned<TypeT>);

    // Standard compatibility
    STATIC_REQUIRE_FALSE(std::is_unsigned<phi::make_unsafe_t<TypeT>>::value);
}

template <typename TypeT>
void test_is_unsigned()
{
    test_is_unsigned_impl<TypeT>();
    test_is_unsigned_impl<const TypeT>();
    test_is_unsigned_impl<volatile TypeT>();
    test_is_unsigned_impl<const volatile TypeT>();
}

template <typename TypeT>
void test_is_not_unsigned()
{
    test_is_not_unsigned_impl<TypeT>();
    test_is_not_unsigned_impl<const TypeT>();
    test_is_not_unsigned_impl<volatile TypeT>();
    test_is_not_unsigned_impl<const volatile TypeT>();
}

TEST_CASE("is_unsigned")
{
    test_is_not_unsigned<void>();
    test_is_not_unsigned<phi::nullptr_t>();
    test_is_unsigned<bool>();
#if PHI_TYPE_SYSTEM_CHAR_SIGNED()
    test_is_not_unsigned<char>();
#else
    test_is_unsigned<char>();
#endif
    test_is_not_unsigned<signed char>();
    test_is_unsigned<unsigned char>();
    test_is_not_unsigned<short>();
    test_is_unsigned<unsigned short>();
    test_is_not_unsigned<int>();
    test_is_unsigned<unsigned int>();
    test_is_not_unsigned<long>();
    test_is_unsigned<unsigned long>();
    test_is_not_unsigned<long long>();
    test_is_unsigned<unsigned long long>();
    test_is_not_unsigned<float>();
    test_is_not_unsigned<double>();
    test_is_not_unsigned<long double>();
    test_is_unsigned<char8_t>();
    test_is_unsigned<char16_t>();
    test_is_unsigned<char32_t>();
#if PHI_TYPE_SYSTEM_WCHAR_T_SIGNED()
    test_is_not_unsigned<wchar_t>();
#else
    test_is_unsigned<wchar_t>();
#endif

    test_is_unsigned<phi::boolean>();
    test_is_not_unsigned<phi::integer<signed char>>();
    test_is_unsigned<phi::integer<unsigned char>>();
    test_is_not_unsigned<phi::integer<short>>();
    test_is_unsigned<phi::integer<unsigned short>>();
    test_is_not_unsigned<phi::integer<int>>();
    test_is_unsigned<phi::integer<unsigned int>>();
    test_is_not_unsigned<phi::integer<long>>();
    test_is_unsigned<phi::integer<unsigned long>>();
    test_is_not_unsigned<phi::integer<long long>>();
    test_is_unsigned<phi::integer<unsigned long long>>();
    test_is_not_unsigned<phi::floating_point<float>>();
    test_is_not_unsigned<phi::floating_point<double>>();
    test_is_not_unsigned<phi::floating_point<long double>>();

    test_is_not_unsigned<std::vector<int>>();
    test_is_not_unsigned<phi::scope_ptr<int>>();

    test_is_not_unsigned<int&>();
    test_is_not_unsigned<const int&>();
    test_is_not_unsigned<volatile int&>();
    test_is_not_unsigned<const volatile int&>();
    test_is_not_unsigned<int&&>();
    test_is_not_unsigned<const int&&>();
    test_is_not_unsigned<volatile int&&>();
    test_is_not_unsigned<const volatile int&&>();
    test_is_not_unsigned<int*>();
    test_is_not_unsigned<const int*>();
    test_is_not_unsigned<volatile int*>();
    test_is_not_unsigned<const volatile int*>();
    test_is_not_unsigned<int**>();
    test_is_not_unsigned<const int**>();
    test_is_not_unsigned<volatile int**>();
    test_is_not_unsigned<const volatile int**>();
    test_is_not_unsigned<int*&>();
    test_is_not_unsigned<const int*&>();
    test_is_not_unsigned<volatile int*&>();
    test_is_not_unsigned<const volatile int*&>();
    test_is_not_unsigned<int*&&>();
    test_is_not_unsigned<const int*&&>();
    test_is_not_unsigned<volatile int*&&>();
    test_is_not_unsigned<const volatile int*&&>();
    test_is_not_unsigned<void*>();
    test_is_not_unsigned<char[3]>();
    test_is_not_unsigned<char[]>();
    test_is_not_unsigned<char* [3]>();
    test_is_not_unsigned<char*[]>();
    test_is_not_unsigned<int(*)[3]>();
    test_is_not_unsigned<int(*)[]>();
    test_is_not_unsigned<int(&)[3]>();
    test_is_not_unsigned<int(&)[]>();
    test_is_not_unsigned<int(&&)[3]>();
    test_is_not_unsigned<int(&&)[]>();
    test_is_not_unsigned<char[3][2]>();
    test_is_not_unsigned<char[][2]>();
    test_is_not_unsigned<char* [3][2]>();
    test_is_not_unsigned<char*[][2]>();
    test_is_not_unsigned<int(*)[3][2]>();
    test_is_not_unsigned<int(*)[][2]>();
    test_is_not_unsigned<int(&)[3][2]>();
    test_is_not_unsigned<int(&)[][2]>();
    test_is_not_unsigned<int(&&)[3][2]>();
    test_is_not_unsigned<int(&&)[][2]>();
    test_is_not_unsigned<class_type>();
    test_is_not_unsigned<class_type[]>();
    test_is_not_unsigned<class_type[2]>();
    test_is_not_unsigned<template_type<void>>();
    test_is_not_unsigned<template_type<int>>();
    test_is_not_unsigned<template_type<class_type>>();
    test_is_not_unsigned<template_type<incomplete_type>>();
    test_is_not_unsigned<variadic_template<>>();
    test_is_not_unsigned<variadic_template<void>>();
    test_is_not_unsigned<variadic_template<int>>();
    test_is_not_unsigned<variadic_template<class_type>>();
    test_is_not_unsigned<variadic_template<incomplete_type>>();
    test_is_not_unsigned<variadic_template<int, void, class_type, volatile char[]>>();
    test_is_not_unsigned<public_derived_from<base>>();
    test_is_not_unsigned<public_derived_from<derived>>();
    test_is_not_unsigned<public_derived_from<class_type>>();
    test_is_not_unsigned<private_derived_from<base>>();
    test_is_not_unsigned<private_derived_from<derived>>();
    test_is_not_unsigned<private_derived_from<class_type>>();
    test_is_not_unsigned<protected_derived_from<base>>();
    test_is_not_unsigned<protected_derived_from<derived>>();
    test_is_not_unsigned<protected_derived_from<class_type>>();
    test_is_not_unsigned<union_type>();
    test_is_not_unsigned<non_empty_union>();
    test_is_not_unsigned<empty>();
    test_is_not_unsigned<not_empty>();
    test_is_not_unsigned<bit_zero>();
    test_is_not_unsigned<bit_one>();
    test_is_not_unsigned<base>();
    test_is_not_unsigned<derived>();
    test_is_not_unsigned<abstract>();
    test_is_not_unsigned<public_abstract>();
    test_is_not_unsigned<private_abstract>();
    test_is_not_unsigned<protected_abstract>();
    test_is_not_unsigned<abstract_template<int>>();
    test_is_not_unsigned<abstract_template<double>>();
    test_is_not_unsigned<abstract_template<class_type>>();
    test_is_not_unsigned<abstract_template<incomplete_type>>();
    test_is_not_unsigned<final_type>();
    test_is_not_unsigned<public_destructor>();
    test_is_not_unsigned<protected_destructor>();
    test_is_not_unsigned<private_destructor>();
    test_is_not_unsigned<virtual_public_destructor>();
    test_is_not_unsigned<virtual_protected_destructor>();
    test_is_not_unsigned<virtual_private_destructor>();
    test_is_not_unsigned<pure_public_destructor>();
    test_is_not_unsigned<pure_protected_destructor>();
    test_is_not_unsigned<pure_private_destructor>();
    test_is_not_unsigned<deleted_public_destructor>();
    test_is_not_unsigned<deleted_protected_destructor>();
    test_is_not_unsigned<deleted_private_destructor>();
    test_is_not_unsigned<deleted_virtual_public_destructor>();
    test_is_not_unsigned<deleted_virtual_protected_destructor>();
    test_is_not_unsigned<deleted_virtual_private_destructor>();
    test_is_not_unsigned<Enum>();
    test_is_not_unsigned<EnumSigned>();
    test_is_not_unsigned<EnumUnsigned>();
    test_is_not_unsigned<EnumClass>();
    test_is_not_unsigned<EnumStruct>();
    test_is_not_unsigned<function_type>();
    test_is_not_unsigned<function_ptr>();
    test_is_not_unsigned<member_object_ptr>();
    test_is_not_unsigned<member_function_ptr>();
    test_is_not_unsigned<incomplete_type>();
    test_is_not_unsigned<incomplete_template<void>>();
    test_is_not_unsigned<incomplete_template<int>>();
    test_is_not_unsigned<incomplete_template<class_type>>();
    test_is_not_unsigned<incomplete_template<incomplete_type>>();
    test_is_not_unsigned<incomplete_variadic_template<>>();
    test_is_not_unsigned<incomplete_variadic_template<void>>();
    test_is_not_unsigned<incomplete_variadic_template<int>>();
    test_is_not_unsigned<incomplete_variadic_template<class_type>>();
    test_is_not_unsigned<incomplete_variadic_template<incomplete_type>>();
    test_is_not_unsigned<incomplete_variadic_template<int, void, class_type, volatile char[]>>();
    test_is_not_unsigned<int class_type::*>();
    test_is_not_unsigned<float class_type::*>();
    test_is_not_unsigned<void * class_type::*>();
    test_is_not_unsigned<int * class_type::*>();
    test_is_not_unsigned<int class_type::*&>();
    test_is_not_unsigned<float class_type::*&>();
    test_is_not_unsigned<void * class_type::*&>();
    test_is_not_unsigned<int * class_type::*&>();
    test_is_not_unsigned<int class_type::*&&>();
    test_is_not_unsigned<float class_type::*&&>();
    test_is_not_unsigned<void * class_type::*&&>();
    test_is_not_unsigned<int * class_type::*&&>();
    test_is_not_unsigned<int class_type::* const>();
    test_is_not_unsigned<float class_type::* const>();
    test_is_not_unsigned<void * class_type::* const>();
    test_is_not_unsigned<int class_type::* const&>();
    test_is_not_unsigned<float class_type::* const&>();
    test_is_not_unsigned<void * class_type::* const&>();
    test_is_not_unsigned<int class_type::* const&&>();
    test_is_not_unsigned<float class_type::* const&&>();
    test_is_not_unsigned<void * class_type::* const&&>();
    test_is_not_unsigned<int class_type::* volatile>();
    test_is_not_unsigned<float class_type::* volatile>();
    test_is_not_unsigned<void * class_type::* volatile>();
    test_is_not_unsigned<int class_type::* volatile&>();
    test_is_not_unsigned<float class_type::* volatile&>();
    test_is_not_unsigned<void * class_type::* volatile&>();
    test_is_not_unsigned<int class_type::* volatile&&>();
    test_is_not_unsigned<float class_type::* volatile&&>();
    test_is_not_unsigned<void * class_type::* volatile&&>();
    test_is_not_unsigned<int class_type::* const volatile>();
    test_is_not_unsigned<float class_type::* const volatile>();
    test_is_not_unsigned<void * class_type::* const volatile>();
    test_is_not_unsigned<int class_type::* const volatile&>();
    test_is_not_unsigned<float class_type::* const volatile&>();
    test_is_not_unsigned<void * class_type::* const volatile&>();
    test_is_not_unsigned<int class_type::* const volatile&&>();
    test_is_not_unsigned<float class_type::* const volatile&&>();
    test_is_not_unsigned<void * class_type::* const volatile&&>();
    test_is_not_unsigned<non_copyable>();
    test_is_not_unsigned<non_moveable>();
    test_is_not_unsigned<non_constructible>();
    test_is_not_unsigned<tracked>();
    test_is_not_unsigned<trap_constructible>();
    test_is_not_unsigned<trap_implicit_conversion>();
    test_is_not_unsigned<trap_comma>();
    test_is_not_unsigned<trap_call>();
    test_is_not_unsigned<trap_self_assign>();
    test_is_not_unsigned<trap_deref>();
    test_is_not_unsigned<trap_array_subscript>();

    test_is_not_unsigned<void()>();
    test_is_not_unsigned<void()&>();
    test_is_not_unsigned<void() &&>();
    test_is_not_unsigned<void() const>();
    test_is_not_unsigned<void() const&>();
    test_is_not_unsigned<void() const&&>();
    test_is_not_unsigned<void() volatile>();
    test_is_not_unsigned<void() volatile&>();
    test_is_not_unsigned<void() volatile&&>();
    test_is_not_unsigned<void() const volatile>();
    test_is_not_unsigned<void() const volatile&>();
    test_is_not_unsigned<void() const volatile&&>();
    test_is_not_unsigned<void() noexcept>();
    test_is_not_unsigned<void() & noexcept>();
    test_is_not_unsigned<void() && noexcept>();
    test_is_not_unsigned<void() const noexcept>();
    test_is_not_unsigned<void() const & noexcept>();
    test_is_not_unsigned<void() const && noexcept>();
    test_is_not_unsigned<void() volatile noexcept>();
    test_is_not_unsigned<void() volatile & noexcept>();
    test_is_not_unsigned<void() volatile && noexcept>();
    test_is_not_unsigned<void() const volatile noexcept>();
    test_is_not_unsigned<void() const volatile & noexcept>();
    test_is_not_unsigned<void() const volatile && noexcept>();

    test_is_not_unsigned<void(int)>();
    test_is_not_unsigned<void(int)&>();
    test_is_not_unsigned<void(int) &&>();
    test_is_not_unsigned<void(int) const>();
    test_is_not_unsigned<void(int) const&>();
    test_is_not_unsigned<void(int) const&&>();
    test_is_not_unsigned<void(int) volatile>();
    test_is_not_unsigned<void(int) volatile&>();
    test_is_not_unsigned<void(int) volatile&&>();
    test_is_not_unsigned<void(int) const volatile>();
    test_is_not_unsigned<void(int) const volatile&>();
    test_is_not_unsigned<void(int) const volatile&&>();
    test_is_not_unsigned<void(int) noexcept>();
    test_is_not_unsigned<void(int) & noexcept>();
    test_is_not_unsigned<void(int) && noexcept>();
    test_is_not_unsigned<void(int) const noexcept>();
    test_is_not_unsigned<void(int) const & noexcept>();
    test_is_not_unsigned<void(int) const && noexcept>();
    test_is_not_unsigned<void(int) volatile noexcept>();
    test_is_not_unsigned<void(int) volatile & noexcept>();
    test_is_not_unsigned<void(int) volatile && noexcept>();
    test_is_not_unsigned<void(int) const volatile noexcept>();
    test_is_not_unsigned<void(int) const volatile & noexcept>();
    test_is_not_unsigned<void(int) const volatile && noexcept>();

    test_is_not_unsigned<void(...)>();
    test_is_not_unsigned<void(...)&>();
    test_is_not_unsigned<void(...) &&>();
    test_is_not_unsigned<void(...) const>();
    test_is_not_unsigned<void(...) const&>();
    test_is_not_unsigned<void(...) const&&>();
    test_is_not_unsigned<void(...) volatile>();
    test_is_not_unsigned<void(...) volatile&>();
    test_is_not_unsigned<void(...) volatile&&>();
    test_is_not_unsigned<void(...) const volatile>();
    test_is_not_unsigned<void(...) const volatile&>();
    test_is_not_unsigned<void(...) const volatile&&>();
    test_is_not_unsigned<void(...) noexcept>();
    test_is_not_unsigned<void(...) & noexcept>();
    test_is_not_unsigned<void(...) && noexcept>();
    test_is_not_unsigned<void(...) const noexcept>();
    test_is_not_unsigned<void(...) const & noexcept>();
    test_is_not_unsigned<void(...) const && noexcept>();
    test_is_not_unsigned<void(...) volatile noexcept>();
    test_is_not_unsigned<void(...) volatile & noexcept>();
    test_is_not_unsigned<void(...) volatile && noexcept>();
    test_is_not_unsigned<void(...) const volatile noexcept>();
    test_is_not_unsigned<void(...) const volatile & noexcept>();
    test_is_not_unsigned<void(...) const volatile && noexcept>();

    test_is_not_unsigned<void(int, ...)>();
    test_is_not_unsigned<void(int, ...)&>();
    test_is_not_unsigned<void(int, ...) &&>();
    test_is_not_unsigned<void(int, ...) const>();
    test_is_not_unsigned<void(int, ...) const&>();
    test_is_not_unsigned<void(int, ...) const&&>();
    test_is_not_unsigned<void(int, ...) volatile>();
    test_is_not_unsigned<void(int, ...) volatile&>();
    test_is_not_unsigned<void(int, ...) volatile&&>();
    test_is_not_unsigned<void(int, ...) const volatile>();
    test_is_not_unsigned<void(int, ...) const volatile&>();
    test_is_not_unsigned<void(int, ...) const volatile&&>();
    test_is_not_unsigned<void(int, ...) noexcept>();
    test_is_not_unsigned<void(int, ...) & noexcept>();
    test_is_not_unsigned<void(int, ...) && noexcept>();
    test_is_not_unsigned<void(int, ...) const noexcept>();
    test_is_not_unsigned<void(int, ...) const & noexcept>();
    test_is_not_unsigned<void(int, ...) const && noexcept>();
    test_is_not_unsigned<void(int, ...) volatile noexcept>();
    test_is_not_unsigned<void(int, ...) volatile & noexcept>();
    test_is_not_unsigned<void(int, ...) volatile && noexcept>();
    test_is_not_unsigned<void(int, ...) const volatile noexcept>();
    test_is_not_unsigned<void(int, ...) const volatile & noexcept>();
    test_is_not_unsigned<void(int, ...) const volatile && noexcept>();

    test_is_not_unsigned<int()>();
    test_is_not_unsigned<int()&>();
    test_is_not_unsigned<int() &&>();
    test_is_not_unsigned<int() const>();
    test_is_not_unsigned<int() const&>();
    test_is_not_unsigned<int() const&&>();
    test_is_not_unsigned<int() volatile>();
    test_is_not_unsigned<int() volatile&>();
    test_is_not_unsigned<int() volatile&&>();
    test_is_not_unsigned<int() const volatile>();
    test_is_not_unsigned<int() const volatile&>();
    test_is_not_unsigned<int() const volatile&&>();
    test_is_not_unsigned<int() noexcept>();
    test_is_not_unsigned<int() & noexcept>();
    test_is_not_unsigned<int() && noexcept>();
    test_is_not_unsigned<int() const noexcept>();
    test_is_not_unsigned<int() const & noexcept>();
    test_is_not_unsigned<int() const && noexcept>();
    test_is_not_unsigned<int() volatile noexcept>();
    test_is_not_unsigned<int() volatile & noexcept>();
    test_is_not_unsigned<int() volatile && noexcept>();
    test_is_not_unsigned<int() const volatile noexcept>();
    test_is_not_unsigned<int() const volatile & noexcept>();
    test_is_not_unsigned<int() const volatile && noexcept>();

    test_is_not_unsigned<int(int)>();
    test_is_not_unsigned<int(int)&>();
    test_is_not_unsigned<int(int) &&>();
    test_is_not_unsigned<int(int) const>();
    test_is_not_unsigned<int(int) const&>();
    test_is_not_unsigned<int(int) const&&>();
    test_is_not_unsigned<int(int) volatile>();
    test_is_not_unsigned<int(int) volatile&>();
    test_is_not_unsigned<int(int) volatile&&>();
    test_is_not_unsigned<int(int) const volatile>();
    test_is_not_unsigned<int(int) const volatile&>();
    test_is_not_unsigned<int(int) const volatile&&>();
    test_is_not_unsigned<int(int) noexcept>();
    test_is_not_unsigned<int(int) & noexcept>();
    test_is_not_unsigned<int(int) && noexcept>();
    test_is_not_unsigned<int(int) const noexcept>();
    test_is_not_unsigned<int(int) const & noexcept>();
    test_is_not_unsigned<int(int) const && noexcept>();
    test_is_not_unsigned<int(int) volatile noexcept>();
    test_is_not_unsigned<int(int) volatile & noexcept>();
    test_is_not_unsigned<int(int) volatile && noexcept>();
    test_is_not_unsigned<int(int) const volatile noexcept>();
    test_is_not_unsigned<int(int) const volatile & noexcept>();
    test_is_not_unsigned<int(int) const volatile && noexcept>();

    test_is_not_unsigned<int(...)>();
    test_is_not_unsigned<int(...)&>();
    test_is_not_unsigned<int(...) &&>();
    test_is_not_unsigned<int(...) const>();
    test_is_not_unsigned<int(...) const&>();
    test_is_not_unsigned<int(...) const&&>();
    test_is_not_unsigned<int(...) volatile>();
    test_is_not_unsigned<int(...) volatile&>();
    test_is_not_unsigned<int(...) volatile&&>();
    test_is_not_unsigned<int(...) const volatile>();
    test_is_not_unsigned<int(...) const volatile&>();
    test_is_not_unsigned<int(...) const volatile&&>();
    test_is_not_unsigned<int(...) noexcept>();
    test_is_not_unsigned<int(...) & noexcept>();
    test_is_not_unsigned<int(...) && noexcept>();
    test_is_not_unsigned<int(...) const noexcept>();
    test_is_not_unsigned<int(...) const & noexcept>();
    test_is_not_unsigned<int(...) const && noexcept>();
    test_is_not_unsigned<int(...) volatile noexcept>();
    test_is_not_unsigned<int(...) volatile & noexcept>();
    test_is_not_unsigned<int(...) volatile && noexcept>();
    test_is_not_unsigned<int(...) const volatile noexcept>();
    test_is_not_unsigned<int(...) const volatile & noexcept>();
    test_is_not_unsigned<int(...) const volatile && noexcept>();

    test_is_not_unsigned<int(int, ...)>();
    test_is_not_unsigned<int(int, ...)&>();
    test_is_not_unsigned<int(int, ...) &&>();
    test_is_not_unsigned<int(int, ...) const>();
    test_is_not_unsigned<int(int, ...) const&>();
    test_is_not_unsigned<int(int, ...) const&&>();
    test_is_not_unsigned<int(int, ...) volatile>();
    test_is_not_unsigned<int(int, ...) volatile&>();
    test_is_not_unsigned<int(int, ...) volatile&&>();
    test_is_not_unsigned<int(int, ...) const volatile>();
    test_is_not_unsigned<int(int, ...) const volatile&>();
    test_is_not_unsigned<int(int, ...) const volatile&&>();
    test_is_not_unsigned<int(int, ...) noexcept>();
    test_is_not_unsigned<int(int, ...) & noexcept>();
    test_is_not_unsigned<int(int, ...) && noexcept>();
    test_is_not_unsigned<int(int, ...) const noexcept>();
    test_is_not_unsigned<int(int, ...) const & noexcept>();
    test_is_not_unsigned<int(int, ...) const && noexcept>();
    test_is_not_unsigned<int(int, ...) volatile noexcept>();
    test_is_not_unsigned<int(int, ...) volatile & noexcept>();
    test_is_not_unsigned<int(int, ...) volatile && noexcept>();
    test_is_not_unsigned<int(int, ...) const volatile noexcept>();
    test_is_not_unsigned<int(int, ...) const volatile & noexcept>();
    test_is_not_unsigned<int(int, ...) const volatile && noexcept>();

    test_is_not_unsigned<void (*)()>();
    test_is_not_unsigned<void (*)() noexcept>();

    test_is_not_unsigned<void (*)(int)>();
    test_is_not_unsigned<void (*)(int) noexcept>();

    test_is_not_unsigned<void (*)(...)>();
    test_is_not_unsigned<void (*)(...) noexcept>();

    test_is_not_unsigned<void (*)(int, ...)>();
    test_is_not_unsigned<void (*)(int, ...) noexcept>();

    test_is_not_unsigned<int (*)()>();
    test_is_not_unsigned<int (*)() noexcept>();

    test_is_not_unsigned<int (*)(int)>();
    test_is_not_unsigned<int (*)(int) noexcept>();

    test_is_not_unsigned<int (*)(...)>();
    test_is_not_unsigned<int (*)(...) noexcept>();

    test_is_not_unsigned<int (*)(int, ...)>();
    test_is_not_unsigned<int (*)(int, ...) noexcept>();

    test_is_not_unsigned<void (&)()>();
    test_is_not_unsigned<void (&)() noexcept>();

    test_is_not_unsigned<void (&)(int)>();
    test_is_not_unsigned<void (&)(int) noexcept>();

    test_is_not_unsigned<void (&)(...)>();
    test_is_not_unsigned<void (&)(...) noexcept>();

    test_is_not_unsigned<void (&)(int, ...)>();
    test_is_not_unsigned<void (&)(int, ...) noexcept>();

    test_is_not_unsigned<int (&)()>();
    test_is_not_unsigned<int (&)() noexcept>();

    test_is_not_unsigned<int (&)(int)>();
    test_is_not_unsigned<int (&)(int) noexcept>();

    test_is_not_unsigned<int (&)(...)>();
    test_is_not_unsigned<int (&)(...) noexcept>();

    test_is_not_unsigned<int (&)(int, ...)>();
    test_is_not_unsigned<int (&)(int, ...) noexcept>();

    test_is_not_unsigned<void (&&)()>();
    test_is_not_unsigned<void (&&)() noexcept>();

    test_is_not_unsigned<void (&&)(int)>();
    test_is_not_unsigned<void (&&)(int) noexcept>();

    test_is_not_unsigned<void (&&)(...)>();
    test_is_not_unsigned<void (&&)(...) noexcept>();

    test_is_not_unsigned<void (&&)(int, ...)>();
    test_is_not_unsigned<void (&&)(int, ...) noexcept>();

    test_is_not_unsigned<int (&&)()>();
    test_is_not_unsigned<int (&&)() noexcept>();

    test_is_not_unsigned<int (&&)(int)>();
    test_is_not_unsigned<int (&&)(int) noexcept>();

    test_is_not_unsigned<int (&&)(...)>();
    test_is_not_unsigned<int (&&)(...) noexcept>();

    test_is_not_unsigned<int (&&)(int, ...)>();
    test_is_not_unsigned<int (&&)(int, ...) noexcept>();

    test_is_not_unsigned<void (class_type::*)()>();
    test_is_not_unsigned<void (class_type::*)()&>();
    test_is_not_unsigned<void (class_type::*)() &&>();
    test_is_not_unsigned<void (class_type::*)() const>();
    test_is_not_unsigned<void (class_type::*)() const&>();
    test_is_not_unsigned<void (class_type::*)() const&&>();
    test_is_not_unsigned<void (class_type::*)() noexcept>();
    test_is_not_unsigned<void (class_type::*)() & noexcept>();
    test_is_not_unsigned<void (class_type::*)() && noexcept>();
    test_is_not_unsigned<void (class_type::*)() const noexcept>();
    test_is_not_unsigned<void (class_type::*)() const & noexcept>();
    test_is_not_unsigned<void (class_type::*)() const && noexcept>();

    test_is_not_unsigned<void (class_type::*)(int)>();
    test_is_not_unsigned<void (class_type::*)(int)&>();
    test_is_not_unsigned<void (class_type::*)(int) &&>();
    test_is_not_unsigned<void (class_type::*)(int) const>();
    test_is_not_unsigned<void (class_type::*)(int) const&>();
    test_is_not_unsigned<void (class_type::*)(int) const&&>();
    test_is_not_unsigned<void (class_type::*)(int) noexcept>();
    test_is_not_unsigned<void (class_type::*)(int) & noexcept>();
    test_is_not_unsigned<void (class_type::*)(int) && noexcept>();
    test_is_not_unsigned<void (class_type::*)(int) const noexcept>();
    test_is_not_unsigned<void (class_type::*)(int) const & noexcept>();
    test_is_not_unsigned<void (class_type::*)(int) const && noexcept>();

    test_is_not_unsigned<void (class_type::*)(...)>();
    test_is_not_unsigned<void (class_type::*)(...)&>();
    test_is_not_unsigned<void (class_type::*)(...) &&>();
    test_is_not_unsigned<void (class_type::*)(...) const>();
    test_is_not_unsigned<void (class_type::*)(...) const&>();
    test_is_not_unsigned<void (class_type::*)(...) const&&>();
    test_is_not_unsigned<void (class_type::*)(...) noexcept>();
    test_is_not_unsigned<void (class_type::*)(...) & noexcept>();
    test_is_not_unsigned<void (class_type::*)(...) && noexcept>();
    test_is_not_unsigned<void (class_type::*)(...) const noexcept>();
    test_is_not_unsigned<void (class_type::*)(...) const & noexcept>();
    test_is_not_unsigned<void (class_type::*)(...) const && noexcept>();

    test_is_not_unsigned<void (class_type::*)(int, ...)>();
    test_is_not_unsigned<void (class_type::*)(int, ...)&>();
    test_is_not_unsigned<void (class_type::*)(int, ...) &&>();
    test_is_not_unsigned<void (class_type::*)(int, ...) const>();
    test_is_not_unsigned<void (class_type::*)(int, ...) const&>();
    test_is_not_unsigned<void (class_type::*)(int, ...) const&&>();
    test_is_not_unsigned<void (class_type::*)(int, ...) noexcept>();
    test_is_not_unsigned<void (class_type::*)(int, ...) & noexcept>();
    test_is_not_unsigned<void (class_type::*)(int, ...) && noexcept>();
    test_is_not_unsigned<void (class_type::*)(int, ...) const noexcept>();
    test_is_not_unsigned<void (class_type::*)(int, ...) const & noexcept>();
    test_is_not_unsigned<void (class_type::*)(int, ...) const && noexcept>();

    test_is_not_unsigned<int (class_type::*)()>();
    test_is_not_unsigned<int (class_type::*)()&>();
    test_is_not_unsigned<int (class_type::*)() &&>();
    test_is_not_unsigned<int (class_type::*)() const>();
    test_is_not_unsigned<int (class_type::*)() const&>();
    test_is_not_unsigned<int (class_type::*)() const&&>();
    test_is_not_unsigned<int (class_type::*)() noexcept>();
    test_is_not_unsigned<int (class_type::*)() & noexcept>();
    test_is_not_unsigned<int (class_type::*)() && noexcept>();
    test_is_not_unsigned<int (class_type::*)() const noexcept>();
    test_is_not_unsigned<int (class_type::*)() const & noexcept>();
    test_is_not_unsigned<int (class_type::*)() const && noexcept>();

    test_is_not_unsigned<int (class_type::*)(int)>();
    test_is_not_unsigned<int (class_type::*)(int)&>();
    test_is_not_unsigned<int (class_type::*)(int) &&>();
    test_is_not_unsigned<int (class_type::*)(int) const>();
    test_is_not_unsigned<int (class_type::*)(int) const&>();
    test_is_not_unsigned<int (class_type::*)(int) const&&>();
    test_is_not_unsigned<int (class_type::*)(int) noexcept>();
    test_is_not_unsigned<int (class_type::*)(int) & noexcept>();
    test_is_not_unsigned<int (class_type::*)(int) && noexcept>();
    test_is_not_unsigned<int (class_type::*)(int) const noexcept>();
    test_is_not_unsigned<int (class_type::*)(int) const & noexcept>();
    test_is_not_unsigned<int (class_type::*)(int) const && noexcept>();

    test_is_not_unsigned<int (class_type::*)(...)>();
    test_is_not_unsigned<int (class_type::*)(...)&>();
    test_is_not_unsigned<int (class_type::*)(...) &&>();
    test_is_not_unsigned<int (class_type::*)(...) const>();
    test_is_not_unsigned<int (class_type::*)(...) const&>();
    test_is_not_unsigned<int (class_type::*)(...) const&&>();
    test_is_not_unsigned<int (class_type::*)(...) noexcept>();
    test_is_not_unsigned<int (class_type::*)(...) & noexcept>();
    test_is_not_unsigned<int (class_type::*)(...) && noexcept>();
    test_is_not_unsigned<int (class_type::*)(...) const noexcept>();
    test_is_not_unsigned<int (class_type::*)(...) const & noexcept>();
    test_is_not_unsigned<int (class_type::*)(...) const && noexcept>();

    test_is_not_unsigned<int (class_type::*)(int, ...)>();
    test_is_not_unsigned<int (class_type::*)(int, ...)&>();
    test_is_not_unsigned<int (class_type::*)(int, ...) &&>();
    test_is_not_unsigned<int (class_type::*)(int, ...) const>();
    test_is_not_unsigned<int (class_type::*)(int, ...) const&>();
    test_is_not_unsigned<int (class_type::*)(int, ...) const&&>();
    test_is_not_unsigned<int (class_type::*)(int, ...) noexcept>();
    test_is_not_unsigned<int (class_type::*)(int, ...) & noexcept>();
    test_is_not_unsigned<int (class_type::*)(int, ...) && noexcept>();
    test_is_not_unsigned<int (class_type::*)(int, ...) const noexcept>();
    test_is_not_unsigned<int (class_type::*)(int, ...) const & noexcept>();
    test_is_not_unsigned<int (class_type::*)(int, ...) const && noexcept>();
}
