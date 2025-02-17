#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_fundamental.hpp>
#include <type_traits>
#include <vector>

template <typename TypeT>
void test_is_fundamental_impl()
{
    STATIC_REQUIRE(phi::is_fundamental<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_fundamental<TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_fundamental_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_not_fundamental_v<TypeT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_fundamental<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_fundamental<TypeT>);
}

template <typename TypeT>
void test_is_fundamental()
{
    test_is_fundamental_impl<TypeT>();
    test_is_fundamental_impl<const TypeT>();
    test_is_fundamental_impl<volatile TypeT>();
    test_is_fundamental_impl<const volatile TypeT>();
}

template <typename TypeT>
void test_is_not_fundamental_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_fundamental<TypeT>::value);
    STATIC_REQUIRE(phi::is_not_fundamental<TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_fundamental_v<TypeT>);
    STATIC_REQUIRE(phi::is_not_fundamental_v<TypeT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_fundamental<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_fundamental<TypeT>);
}

template <typename TypeT>
void test_is_not_fundamental()
{
    test_is_not_fundamental_impl<TypeT>();
    test_is_not_fundamental_impl<const TypeT>();
    test_is_not_fundamental_impl<volatile TypeT>();
    test_is_not_fundamental_impl<const volatile TypeT>();
}

TEST_CASE("is_fundamental")
{
    test_is_fundamental<void>();
    test_is_fundamental<phi::nullptr_t>();
    test_is_fundamental<bool>();
    test_is_fundamental<char>();
    test_is_fundamental<signed char>();
    test_is_fundamental<unsigned char>();
    test_is_fundamental<short>();
    test_is_fundamental<unsigned short>();
    test_is_fundamental<int>();
    test_is_fundamental<unsigned int>();
    test_is_fundamental<long>();
    test_is_fundamental<unsigned long>();
    test_is_fundamental<long long>();
    test_is_fundamental<unsigned long long>();
    test_is_fundamental<float>();
    test_is_fundamental<double>();
    test_is_fundamental<long double>();
    test_is_fundamental<char8_t>();
    test_is_fundamental<char16_t>();
    test_is_fundamental<char32_t>();
    test_is_fundamental<wchar_t>();

    test_is_fundamental<phi::boolean>();
    test_is_fundamental<phi::integer<signed char>>();
    test_is_fundamental<phi::integer<unsigned char>>();
    test_is_fundamental<phi::integer<short>>();
    test_is_fundamental<phi::integer<unsigned short>>();
    test_is_fundamental<phi::integer<int>>();
    test_is_fundamental<phi::integer<unsigned int>>();
    test_is_fundamental<phi::integer<long>>();
    test_is_fundamental<phi::integer<unsigned long>>();
    test_is_fundamental<phi::integer<long long>>();
    test_is_fundamental<phi::integer<unsigned long long>>();
    test_is_fundamental<phi::floating_point<float>>();
    test_is_fundamental<phi::floating_point<double>>();
    test_is_fundamental<phi::floating_point<long double>>();

    test_is_not_fundamental<std::vector<int>>();
    test_is_not_fundamental<phi::scope_ptr<int>>();

    test_is_not_fundamental<int&>();
    test_is_not_fundamental<const int&>();
    test_is_not_fundamental<volatile int&>();
    test_is_not_fundamental<const volatile int&>();
    test_is_not_fundamental<int&&>();
    test_is_not_fundamental<const int&&>();
    test_is_not_fundamental<volatile int&&>();
    test_is_not_fundamental<const volatile int&&>();
    test_is_not_fundamental<int*>();
    test_is_not_fundamental<const int*>();
    test_is_not_fundamental<volatile int*>();
    test_is_not_fundamental<const volatile int*>();
    test_is_not_fundamental<int**>();
    test_is_not_fundamental<const int**>();
    test_is_not_fundamental<volatile int**>();
    test_is_not_fundamental<const volatile int**>();
    test_is_not_fundamental<int*&>();
    test_is_not_fundamental<const int*&>();
    test_is_not_fundamental<volatile int*&>();
    test_is_not_fundamental<const volatile int*&>();
    test_is_not_fundamental<int*&&>();
    test_is_not_fundamental<const int*&&>();
    test_is_not_fundamental<volatile int*&&>();
    test_is_not_fundamental<const volatile int*&&>();
    test_is_not_fundamental<void*>();
    test_is_not_fundamental<char[3]>();
    test_is_not_fundamental<char[]>();
    test_is_not_fundamental<char* [3]>();
    test_is_not_fundamental<char*[]>();
    test_is_not_fundamental<int(*)[3]>();
    test_is_not_fundamental<int(*)[]>();
    test_is_not_fundamental<int(&)[3]>();
    test_is_not_fundamental<int(&)[]>();
    test_is_not_fundamental<int(&&)[3]>();
    test_is_not_fundamental<int(&&)[]>();
    test_is_not_fundamental<char[3][2]>();
    test_is_not_fundamental<char[][2]>();
    test_is_not_fundamental<char* [3][2]>();
    test_is_not_fundamental<char*[][2]>();
    test_is_not_fundamental<int(*)[3][2]>();
    test_is_not_fundamental<int(*)[][2]>();
    test_is_not_fundamental<int(&)[3][2]>();
    test_is_not_fundamental<int(&)[][2]>();
    test_is_not_fundamental<int(&&)[3][2]>();
    test_is_not_fundamental<int(&&)[][2]>();
    test_is_not_fundamental<class_type>();
    test_is_not_fundamental<class_type[]>();
    test_is_not_fundamental<class_type[2]>();
    test_is_not_fundamental<template_type<void>>();
    test_is_not_fundamental<template_type<int>>();
    test_is_not_fundamental<template_type<class_type>>();
    test_is_not_fundamental<template_type<incomplete_type>>();
    test_is_not_fundamental<variadic_template<>>();
    test_is_not_fundamental<variadic_template<void>>();
    test_is_not_fundamental<variadic_template<int>>();
    test_is_not_fundamental<variadic_template<class_type>>();
    test_is_not_fundamental<variadic_template<incomplete_type>>();
    test_is_not_fundamental<variadic_template<int, void, class_type, volatile char[]>>();
    test_is_not_fundamental<public_derived_from<base>>();
    test_is_not_fundamental<public_derived_from<derived>>();
    test_is_not_fundamental<public_derived_from<class_type>>();
    test_is_not_fundamental<private_derived_from<base>>();
    test_is_not_fundamental<private_derived_from<derived>>();
    test_is_not_fundamental<private_derived_from<class_type>>();
    test_is_not_fundamental<protected_derived_from<base>>();
    test_is_not_fundamental<protected_derived_from<derived>>();
    test_is_not_fundamental<protected_derived_from<class_type>>();
    test_is_not_fundamental<union_type>();
    test_is_not_fundamental<non_empty_union>();
    test_is_not_fundamental<empty>();
    test_is_not_fundamental<not_empty>();
    test_is_not_fundamental<bit_zero>();
    test_is_not_fundamental<bit_one>();
    test_is_not_fundamental<base>();
    test_is_not_fundamental<derived>();
    test_is_not_fundamental<abstract>();
    test_is_not_fundamental<public_abstract>();
    test_is_not_fundamental<private_abstract>();
    test_is_not_fundamental<protected_abstract>();
    test_is_not_fundamental<abstract_template<int>>();
    test_is_not_fundamental<abstract_template<double>>();
    test_is_not_fundamental<abstract_template<class_type>>();
    test_is_not_fundamental<abstract_template<incomplete_type>>();
    test_is_not_fundamental<final_type>();
    test_is_not_fundamental<public_destructor>();
    test_is_not_fundamental<protected_destructor>();
    test_is_not_fundamental<private_destructor>();
    test_is_not_fundamental<virtual_public_destructor>();
    test_is_not_fundamental<virtual_protected_destructor>();
    test_is_not_fundamental<virtual_private_destructor>();
    test_is_not_fundamental<pure_public_destructor>();
    test_is_not_fundamental<pure_protected_destructor>();
    test_is_not_fundamental<pure_private_destructor>();
    test_is_not_fundamental<deleted_public_destructor>();
    test_is_not_fundamental<deleted_protected_destructor>();
    test_is_not_fundamental<deleted_private_destructor>();
    test_is_not_fundamental<deleted_virtual_public_destructor>();
    test_is_not_fundamental<deleted_virtual_protected_destructor>();
    test_is_not_fundamental<deleted_virtual_private_destructor>();
    test_is_not_fundamental<Enum>();
    test_is_not_fundamental<EnumSigned>();
    test_is_not_fundamental<EnumUnsigned>();
    test_is_not_fundamental<EnumClass>();
    test_is_not_fundamental<EnumStruct>();
    test_is_not_fundamental<function_type>();
    test_is_not_fundamental<function_ptr>();
    test_is_not_fundamental<member_object_ptr>();
    test_is_not_fundamental<member_function_ptr>();
    test_is_not_fundamental<incomplete_type>();
    test_is_not_fundamental<incomplete_template<void>>();
    test_is_not_fundamental<incomplete_template<int>>();
    test_is_not_fundamental<incomplete_template<class_type>>();
    test_is_not_fundamental<incomplete_template<incomplete_type>>();
    test_is_not_fundamental<incomplete_variadic_template<>>();
    test_is_not_fundamental<incomplete_variadic_template<void>>();
    test_is_not_fundamental<incomplete_variadic_template<int>>();
    test_is_not_fundamental<incomplete_variadic_template<class_type>>();
    test_is_not_fundamental<incomplete_variadic_template<incomplete_type>>();
    test_is_not_fundamental<incomplete_variadic_template<int, void, class_type, volatile char[]>>();
    test_is_not_fundamental<int class_type::*>();
    test_is_not_fundamental<float class_type::*>();
    test_is_not_fundamental<void * class_type::*>();
    test_is_not_fundamental<int * class_type::*>();
    test_is_not_fundamental<int class_type::*&>();
    test_is_not_fundamental<float class_type::*&>();
    test_is_not_fundamental<void * class_type::*&>();
    test_is_not_fundamental<int * class_type::*&>();
    test_is_not_fundamental<int class_type::*&&>();
    test_is_not_fundamental<float class_type::*&&>();
    test_is_not_fundamental<void * class_type::*&&>();
    test_is_not_fundamental<int * class_type::*&&>();
    test_is_not_fundamental<int class_type::* const>();
    test_is_not_fundamental<float class_type::* const>();
    test_is_not_fundamental<void * class_type::* const>();
    test_is_not_fundamental<int class_type::* const&>();
    test_is_not_fundamental<float class_type::* const&>();
    test_is_not_fundamental<void * class_type::* const&>();
    test_is_not_fundamental<int class_type::* const&&>();
    test_is_not_fundamental<float class_type::* const&&>();
    test_is_not_fundamental<void * class_type::* const&&>();
    test_is_not_fundamental<int class_type::* volatile>();
    test_is_not_fundamental<float class_type::* volatile>();
    test_is_not_fundamental<void * class_type::* volatile>();
    test_is_not_fundamental<int class_type::* volatile&>();
    test_is_not_fundamental<float class_type::* volatile&>();
    test_is_not_fundamental<void * class_type::* volatile&>();
    test_is_not_fundamental<int class_type::* volatile&&>();
    test_is_not_fundamental<float class_type::* volatile&&>();
    test_is_not_fundamental<void * class_type::* volatile&&>();
    test_is_not_fundamental<int class_type::* const volatile>();
    test_is_not_fundamental<float class_type::* const volatile>();
    test_is_not_fundamental<void * class_type::* const volatile>();
    test_is_not_fundamental<int class_type::* const volatile&>();
    test_is_not_fundamental<float class_type::* const volatile&>();
    test_is_not_fundamental<void * class_type::* const volatile&>();
    test_is_not_fundamental<int class_type::* const volatile&&>();
    test_is_not_fundamental<float class_type::* const volatile&&>();
    test_is_not_fundamental<void * class_type::* const volatile&&>();
    test_is_not_fundamental<non_copyable>();
    test_is_not_fundamental<non_moveable>();
    test_is_not_fundamental<non_constructible>();
    test_is_not_fundamental<tracked>();
    test_is_not_fundamental<trap_constructible>();
    test_is_not_fundamental<trap_implicit_conversion>();
    test_is_not_fundamental<trap_comma>();
    test_is_not_fundamental<trap_call>();
    test_is_not_fundamental<trap_self_assign>();
    test_is_not_fundamental<trap_deref>();
    test_is_not_fundamental<trap_array_subscript>();

    test_is_not_fundamental<void()>();
    test_is_not_fundamental<void()&>();
    test_is_not_fundamental<void() &&>();
    test_is_not_fundamental<void() const>();
    test_is_not_fundamental<void() const&>();
    test_is_not_fundamental<void() const&&>();
    test_is_not_fundamental<void() volatile>();
    test_is_not_fundamental<void() volatile&>();
    test_is_not_fundamental<void() volatile&&>();
    test_is_not_fundamental<void() const volatile>();
    test_is_not_fundamental<void() const volatile&>();
    test_is_not_fundamental<void() const volatile&&>();
    test_is_not_fundamental<void() noexcept>();
    test_is_not_fundamental<void() & noexcept>();
    test_is_not_fundamental<void() && noexcept>();
    test_is_not_fundamental<void() const noexcept>();
    test_is_not_fundamental<void() const & noexcept>();
    test_is_not_fundamental<void() const && noexcept>();
    test_is_not_fundamental<void() volatile noexcept>();
    test_is_not_fundamental<void() volatile & noexcept>();
    test_is_not_fundamental<void() volatile && noexcept>();
    test_is_not_fundamental<void() const volatile noexcept>();
    test_is_not_fundamental<void() const volatile & noexcept>();
    test_is_not_fundamental<void() const volatile && noexcept>();

    test_is_not_fundamental<void(int)>();
    test_is_not_fundamental<void(int)&>();
    test_is_not_fundamental<void(int) &&>();
    test_is_not_fundamental<void(int) const>();
    test_is_not_fundamental<void(int) const&>();
    test_is_not_fundamental<void(int) const&&>();
    test_is_not_fundamental<void(int) volatile>();
    test_is_not_fundamental<void(int) volatile&>();
    test_is_not_fundamental<void(int) volatile&&>();
    test_is_not_fundamental<void(int) const volatile>();
    test_is_not_fundamental<void(int) const volatile&>();
    test_is_not_fundamental<void(int) const volatile&&>();
    test_is_not_fundamental<void(int) noexcept>();
    test_is_not_fundamental<void(int) & noexcept>();
    test_is_not_fundamental<void(int) && noexcept>();
    test_is_not_fundamental<void(int) const noexcept>();
    test_is_not_fundamental<void(int) const & noexcept>();
    test_is_not_fundamental<void(int) const && noexcept>();
    test_is_not_fundamental<void(int) volatile noexcept>();
    test_is_not_fundamental<void(int) volatile & noexcept>();
    test_is_not_fundamental<void(int) volatile && noexcept>();
    test_is_not_fundamental<void(int) const volatile noexcept>();
    test_is_not_fundamental<void(int) const volatile & noexcept>();
    test_is_not_fundamental<void(int) const volatile && noexcept>();

    test_is_not_fundamental<void(...)>();
    test_is_not_fundamental<void(...)&>();
    test_is_not_fundamental<void(...) &&>();
    test_is_not_fundamental<void(...) const>();
    test_is_not_fundamental<void(...) const&>();
    test_is_not_fundamental<void(...) const&&>();
    test_is_not_fundamental<void(...) volatile>();
    test_is_not_fundamental<void(...) volatile&>();
    test_is_not_fundamental<void(...) volatile&&>();
    test_is_not_fundamental<void(...) const volatile>();
    test_is_not_fundamental<void(...) const volatile&>();
    test_is_not_fundamental<void(...) const volatile&&>();
    test_is_not_fundamental<void(...) noexcept>();
    test_is_not_fundamental<void(...) & noexcept>();
    test_is_not_fundamental<void(...) && noexcept>();
    test_is_not_fundamental<void(...) const noexcept>();
    test_is_not_fundamental<void(...) const & noexcept>();
    test_is_not_fundamental<void(...) const && noexcept>();
    test_is_not_fundamental<void(...) volatile noexcept>();
    test_is_not_fundamental<void(...) volatile & noexcept>();
    test_is_not_fundamental<void(...) volatile && noexcept>();
    test_is_not_fundamental<void(...) const volatile noexcept>();
    test_is_not_fundamental<void(...) const volatile & noexcept>();
    test_is_not_fundamental<void(...) const volatile && noexcept>();

    test_is_not_fundamental<void(int, ...)>();
    test_is_not_fundamental<void(int, ...)&>();
    test_is_not_fundamental<void(int, ...) &&>();
    test_is_not_fundamental<void(int, ...) const>();
    test_is_not_fundamental<void(int, ...) const&>();
    test_is_not_fundamental<void(int, ...) const&&>();
    test_is_not_fundamental<void(int, ...) volatile>();
    test_is_not_fundamental<void(int, ...) volatile&>();
    test_is_not_fundamental<void(int, ...) volatile&&>();
    test_is_not_fundamental<void(int, ...) const volatile>();
    test_is_not_fundamental<void(int, ...) const volatile&>();
    test_is_not_fundamental<void(int, ...) const volatile&&>();
    test_is_not_fundamental<void(int, ...) noexcept>();
    test_is_not_fundamental<void(int, ...) & noexcept>();
    test_is_not_fundamental<void(int, ...) && noexcept>();
    test_is_not_fundamental<void(int, ...) const noexcept>();
    test_is_not_fundamental<void(int, ...) const & noexcept>();
    test_is_not_fundamental<void(int, ...) const && noexcept>();
    test_is_not_fundamental<void(int, ...) volatile noexcept>();
    test_is_not_fundamental<void(int, ...) volatile & noexcept>();
    test_is_not_fundamental<void(int, ...) volatile && noexcept>();
    test_is_not_fundamental<void(int, ...) const volatile noexcept>();
    test_is_not_fundamental<void(int, ...) const volatile & noexcept>();
    test_is_not_fundamental<void(int, ...) const volatile && noexcept>();

    test_is_not_fundamental<int()>();
    test_is_not_fundamental<int()&>();
    test_is_not_fundamental<int() &&>();
    test_is_not_fundamental<int() const>();
    test_is_not_fundamental<int() const&>();
    test_is_not_fundamental<int() const&&>();
    test_is_not_fundamental<int() volatile>();
    test_is_not_fundamental<int() volatile&>();
    test_is_not_fundamental<int() volatile&&>();
    test_is_not_fundamental<int() const volatile>();
    test_is_not_fundamental<int() const volatile&>();
    test_is_not_fundamental<int() const volatile&&>();
    test_is_not_fundamental<int() noexcept>();
    test_is_not_fundamental<int() & noexcept>();
    test_is_not_fundamental<int() && noexcept>();
    test_is_not_fundamental<int() const noexcept>();
    test_is_not_fundamental<int() const & noexcept>();
    test_is_not_fundamental<int() const && noexcept>();
    test_is_not_fundamental<int() volatile noexcept>();
    test_is_not_fundamental<int() volatile & noexcept>();
    test_is_not_fundamental<int() volatile && noexcept>();
    test_is_not_fundamental<int() const volatile noexcept>();
    test_is_not_fundamental<int() const volatile & noexcept>();
    test_is_not_fundamental<int() const volatile && noexcept>();

    test_is_not_fundamental<int(int)>();
    test_is_not_fundamental<int(int)&>();
    test_is_not_fundamental<int(int) &&>();
    test_is_not_fundamental<int(int) const>();
    test_is_not_fundamental<int(int) const&>();
    test_is_not_fundamental<int(int) const&&>();
    test_is_not_fundamental<int(int) volatile>();
    test_is_not_fundamental<int(int) volatile&>();
    test_is_not_fundamental<int(int) volatile&&>();
    test_is_not_fundamental<int(int) const volatile>();
    test_is_not_fundamental<int(int) const volatile&>();
    test_is_not_fundamental<int(int) const volatile&&>();
    test_is_not_fundamental<int(int) noexcept>();
    test_is_not_fundamental<int(int) & noexcept>();
    test_is_not_fundamental<int(int) && noexcept>();
    test_is_not_fundamental<int(int) const noexcept>();
    test_is_not_fundamental<int(int) const & noexcept>();
    test_is_not_fundamental<int(int) const && noexcept>();
    test_is_not_fundamental<int(int) volatile noexcept>();
    test_is_not_fundamental<int(int) volatile & noexcept>();
    test_is_not_fundamental<int(int) volatile && noexcept>();
    test_is_not_fundamental<int(int) const volatile noexcept>();
    test_is_not_fundamental<int(int) const volatile & noexcept>();
    test_is_not_fundamental<int(int) const volatile && noexcept>();

    test_is_not_fundamental<int(...)>();
    test_is_not_fundamental<int(...)&>();
    test_is_not_fundamental<int(...) &&>();
    test_is_not_fundamental<int(...) const>();
    test_is_not_fundamental<int(...) const&>();
    test_is_not_fundamental<int(...) const&&>();
    test_is_not_fundamental<int(...) volatile>();
    test_is_not_fundamental<int(...) volatile&>();
    test_is_not_fundamental<int(...) volatile&&>();
    test_is_not_fundamental<int(...) const volatile>();
    test_is_not_fundamental<int(...) const volatile&>();
    test_is_not_fundamental<int(...) const volatile&&>();
    test_is_not_fundamental<int(...) noexcept>();
    test_is_not_fundamental<int(...) & noexcept>();
    test_is_not_fundamental<int(...) && noexcept>();
    test_is_not_fundamental<int(...) const noexcept>();
    test_is_not_fundamental<int(...) const & noexcept>();
    test_is_not_fundamental<int(...) const && noexcept>();
    test_is_not_fundamental<int(...) volatile noexcept>();
    test_is_not_fundamental<int(...) volatile & noexcept>();
    test_is_not_fundamental<int(...) volatile && noexcept>();
    test_is_not_fundamental<int(...) const volatile noexcept>();
    test_is_not_fundamental<int(...) const volatile & noexcept>();
    test_is_not_fundamental<int(...) const volatile && noexcept>();

    test_is_not_fundamental<int(int, ...)>();
    test_is_not_fundamental<int(int, ...)&>();
    test_is_not_fundamental<int(int, ...) &&>();
    test_is_not_fundamental<int(int, ...) const>();
    test_is_not_fundamental<int(int, ...) const&>();
    test_is_not_fundamental<int(int, ...) const&&>();
    test_is_not_fundamental<int(int, ...) volatile>();
    test_is_not_fundamental<int(int, ...) volatile&>();
    test_is_not_fundamental<int(int, ...) volatile&&>();
    test_is_not_fundamental<int(int, ...) const volatile>();
    test_is_not_fundamental<int(int, ...) const volatile&>();
    test_is_not_fundamental<int(int, ...) const volatile&&>();
    test_is_not_fundamental<int(int, ...) noexcept>();
    test_is_not_fundamental<int(int, ...) & noexcept>();
    test_is_not_fundamental<int(int, ...) && noexcept>();
    test_is_not_fundamental<int(int, ...) const noexcept>();
    test_is_not_fundamental<int(int, ...) const & noexcept>();
    test_is_not_fundamental<int(int, ...) const && noexcept>();
    test_is_not_fundamental<int(int, ...) volatile noexcept>();
    test_is_not_fundamental<int(int, ...) volatile & noexcept>();
    test_is_not_fundamental<int(int, ...) volatile && noexcept>();
    test_is_not_fundamental<int(int, ...) const volatile noexcept>();
    test_is_not_fundamental<int(int, ...) const volatile & noexcept>();
    test_is_not_fundamental<int(int, ...) const volatile && noexcept>();

    test_is_not_fundamental<void (*)()>();
    test_is_not_fundamental<void (*)() noexcept>();

    test_is_not_fundamental<void (*)(int)>();
    test_is_not_fundamental<void (*)(int) noexcept>();

    test_is_not_fundamental<void (*)(...)>();
    test_is_not_fundamental<void (*)(...) noexcept>();

    test_is_not_fundamental<void (*)(int, ...)>();
    test_is_not_fundamental<void (*)(int, ...) noexcept>();

    test_is_not_fundamental<int (*)()>();
    test_is_not_fundamental<int (*)() noexcept>();

    test_is_not_fundamental<int (*)(int)>();
    test_is_not_fundamental<int (*)(int) noexcept>();

    test_is_not_fundamental<int (*)(...)>();
    test_is_not_fundamental<int (*)(...) noexcept>();

    test_is_not_fundamental<int (*)(int, ...)>();
    test_is_not_fundamental<int (*)(int, ...) noexcept>();

    test_is_not_fundamental<void (&)()>();
    test_is_not_fundamental<void (&)() noexcept>();

    test_is_not_fundamental<void (&)(int)>();
    test_is_not_fundamental<void (&)(int) noexcept>();

    test_is_not_fundamental<void (&)(...)>();
    test_is_not_fundamental<void (&)(...) noexcept>();

    test_is_not_fundamental<void (&)(int, ...)>();
    test_is_not_fundamental<void (&)(int, ...) noexcept>();

    test_is_not_fundamental<int (&)()>();
    test_is_not_fundamental<int (&)() noexcept>();

    test_is_not_fundamental<int (&)(int)>();
    test_is_not_fundamental<int (&)(int) noexcept>();

    test_is_not_fundamental<int (&)(...)>();
    test_is_not_fundamental<int (&)(...) noexcept>();

    test_is_not_fundamental<int (&)(int, ...)>();
    test_is_not_fundamental<int (&)(int, ...) noexcept>();

    test_is_not_fundamental<void (&&)()>();
    test_is_not_fundamental<void (&&)() noexcept>();

    test_is_not_fundamental<void (&&)(int)>();
    test_is_not_fundamental<void (&&)(int) noexcept>();

    test_is_not_fundamental<void (&&)(...)>();
    test_is_not_fundamental<void (&&)(...) noexcept>();

    test_is_not_fundamental<void (&&)(int, ...)>();
    test_is_not_fundamental<void (&&)(int, ...) noexcept>();

    test_is_not_fundamental<int (&&)()>();
    test_is_not_fundamental<int (&&)() noexcept>();

    test_is_not_fundamental<int (&&)(int)>();
    test_is_not_fundamental<int (&&)(int) noexcept>();

    test_is_not_fundamental<int (&&)(...)>();
    test_is_not_fundamental<int (&&)(...) noexcept>();

    test_is_not_fundamental<int (&&)(int, ...)>();
    test_is_not_fundamental<int (&&)(int, ...) noexcept>();

    test_is_not_fundamental<void (class_type::*)()>();
    test_is_not_fundamental<void (class_type::*)()&>();
    test_is_not_fundamental<void (class_type::*)() &&>();
    test_is_not_fundamental<void (class_type::*)() const>();
    test_is_not_fundamental<void (class_type::*)() const&>();
    test_is_not_fundamental<void (class_type::*)() const&&>();
    test_is_not_fundamental<void (class_type::*)() noexcept>();
    test_is_not_fundamental<void (class_type::*)() & noexcept>();
    test_is_not_fundamental<void (class_type::*)() && noexcept>();
    test_is_not_fundamental<void (class_type::*)() const noexcept>();
    test_is_not_fundamental<void (class_type::*)() const & noexcept>();
    test_is_not_fundamental<void (class_type::*)() const && noexcept>();

    test_is_not_fundamental<void (class_type::*)(int)>();
    test_is_not_fundamental<void (class_type::*)(int)&>();
    test_is_not_fundamental<void (class_type::*)(int) &&>();
    test_is_not_fundamental<void (class_type::*)(int) const>();
    test_is_not_fundamental<void (class_type::*)(int) const&>();
    test_is_not_fundamental<void (class_type::*)(int) const&&>();
    test_is_not_fundamental<void (class_type::*)(int) noexcept>();
    test_is_not_fundamental<void (class_type::*)(int) & noexcept>();
    test_is_not_fundamental<void (class_type::*)(int) && noexcept>();
    test_is_not_fundamental<void (class_type::*)(int) const noexcept>();
    test_is_not_fundamental<void (class_type::*)(int) const & noexcept>();
    test_is_not_fundamental<void (class_type::*)(int) const && noexcept>();

    test_is_not_fundamental<void (class_type::*)(...)>();
    test_is_not_fundamental<void (class_type::*)(...)&>();
    test_is_not_fundamental<void (class_type::*)(...) &&>();
    test_is_not_fundamental<void (class_type::*)(...) const>();
    test_is_not_fundamental<void (class_type::*)(...) const&>();
    test_is_not_fundamental<void (class_type::*)(...) const&&>();
    test_is_not_fundamental<void (class_type::*)(...) noexcept>();
    test_is_not_fundamental<void (class_type::*)(...) & noexcept>();
    test_is_not_fundamental<void (class_type::*)(...) && noexcept>();
    test_is_not_fundamental<void (class_type::*)(...) const noexcept>();
    test_is_not_fundamental<void (class_type::*)(...) const & noexcept>();
    test_is_not_fundamental<void (class_type::*)(...) const && noexcept>();

    test_is_not_fundamental<void (class_type::*)(int, ...)>();
    test_is_not_fundamental<void (class_type::*)(int, ...)&>();
    test_is_not_fundamental<void (class_type::*)(int, ...) &&>();
    test_is_not_fundamental<void (class_type::*)(int, ...) const>();
    test_is_not_fundamental<void (class_type::*)(int, ...) const&>();
    test_is_not_fundamental<void (class_type::*)(int, ...) const&&>();
    test_is_not_fundamental<void (class_type::*)(int, ...) noexcept>();
    test_is_not_fundamental<void (class_type::*)(int, ...) & noexcept>();
    test_is_not_fundamental<void (class_type::*)(int, ...) && noexcept>();
    test_is_not_fundamental<void (class_type::*)(int, ...) const noexcept>();
    test_is_not_fundamental<void (class_type::*)(int, ...) const & noexcept>();
    test_is_not_fundamental<void (class_type::*)(int, ...) const && noexcept>();

    test_is_not_fundamental<int (class_type::*)()>();
    test_is_not_fundamental<int (class_type::*)()&>();
    test_is_not_fundamental<int (class_type::*)() &&>();
    test_is_not_fundamental<int (class_type::*)() const>();
    test_is_not_fundamental<int (class_type::*)() const&>();
    test_is_not_fundamental<int (class_type::*)() const&&>();
    test_is_not_fundamental<int (class_type::*)() noexcept>();
    test_is_not_fundamental<int (class_type::*)() & noexcept>();
    test_is_not_fundamental<int (class_type::*)() && noexcept>();
    test_is_not_fundamental<int (class_type::*)() const noexcept>();
    test_is_not_fundamental<int (class_type::*)() const & noexcept>();
    test_is_not_fundamental<int (class_type::*)() const && noexcept>();

    test_is_not_fundamental<int (class_type::*)(int)>();
    test_is_not_fundamental<int (class_type::*)(int)&>();
    test_is_not_fundamental<int (class_type::*)(int) &&>();
    test_is_not_fundamental<int (class_type::*)(int) const>();
    test_is_not_fundamental<int (class_type::*)(int) const&>();
    test_is_not_fundamental<int (class_type::*)(int) const&&>();
    test_is_not_fundamental<int (class_type::*)(int) noexcept>();
    test_is_not_fundamental<int (class_type::*)(int) & noexcept>();
    test_is_not_fundamental<int (class_type::*)(int) && noexcept>();
    test_is_not_fundamental<int (class_type::*)(int) const noexcept>();
    test_is_not_fundamental<int (class_type::*)(int) const & noexcept>();
    test_is_not_fundamental<int (class_type::*)(int) const && noexcept>();

    test_is_not_fundamental<int (class_type::*)(...)>();
    test_is_not_fundamental<int (class_type::*)(...)&>();
    test_is_not_fundamental<int (class_type::*)(...) &&>();
    test_is_not_fundamental<int (class_type::*)(...) const>();
    test_is_not_fundamental<int (class_type::*)(...) const&>();
    test_is_not_fundamental<int (class_type::*)(...) const&&>();
    test_is_not_fundamental<int (class_type::*)(...) noexcept>();
    test_is_not_fundamental<int (class_type::*)(...) & noexcept>();
    test_is_not_fundamental<int (class_type::*)(...) && noexcept>();
    test_is_not_fundamental<int (class_type::*)(...) const noexcept>();
    test_is_not_fundamental<int (class_type::*)(...) const & noexcept>();
    test_is_not_fundamental<int (class_type::*)(...) const && noexcept>();

    test_is_not_fundamental<int (class_type::*)(int, ...)>();
    test_is_not_fundamental<int (class_type::*)(int, ...)&>();
    test_is_not_fundamental<int (class_type::*)(int, ...) &&>();
    test_is_not_fundamental<int (class_type::*)(int, ...) const>();
    test_is_not_fundamental<int (class_type::*)(int, ...) const&>();
    test_is_not_fundamental<int (class_type::*)(int, ...) const&&>();
    test_is_not_fundamental<int (class_type::*)(int, ...) noexcept>();
    test_is_not_fundamental<int (class_type::*)(int, ...) & noexcept>();
    test_is_not_fundamental<int (class_type::*)(int, ...) && noexcept>();
    test_is_not_fundamental<int (class_type::*)(int, ...) const noexcept>();
    test_is_not_fundamental<int (class_type::*)(int, ...) const & noexcept>();
    test_is_not_fundamental<int (class_type::*)(int, ...) const && noexcept>();
}
