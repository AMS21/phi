#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_volatile.hpp>
#include <vector>

template <typename TypeT>
void test_is_volatile_impl()
{
    STATIC_REQUIRE(phi::is_volatile<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_volatile<TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_volatile_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_not_volatile_v<TypeT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_volatile<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_volatile<TypeT>);

    // Standard compatibility
    STATIC_REQUIRE(std::is_volatile<TypeT>::value);
}

template <typename TypeT>
void test_is_not_volatile_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_volatile<TypeT>::value);
    STATIC_REQUIRE(phi::is_not_volatile<TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_volatile_v<TypeT>);
    STATIC_REQUIRE(phi::is_not_volatile_v<TypeT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_volatile<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_volatile<TypeT>);

    // Standard compatibility
    STATIC_REQUIRE_FALSE(std::is_volatile<TypeT>::value);
}

template <typename TypeT>
void test_is_volatile()
{
    test_is_not_volatile_impl<TypeT>();
    test_is_not_volatile_impl<const TypeT>();
    test_is_volatile_impl<volatile TypeT>();
    test_is_volatile_impl<const volatile TypeT>();
}

template <typename TypeT>
void test_is_volatile_cv()
{
    test_is_volatile_impl<TypeT>();
    test_is_volatile_impl<const TypeT>();
    test_is_volatile_impl<volatile TypeT>();
    test_is_volatile_impl<const volatile TypeT>();
}

template <typename TypeT>
void test_is_not_volatile()
{
    test_is_not_volatile_impl<TypeT>();
    test_is_not_volatile_impl<const TypeT>();
    test_is_not_volatile_impl<volatile TypeT>();
    test_is_not_volatile_impl<const volatile TypeT>();
}

TEST_CASE("is_volatile")
{
    test_is_volatile<void>();
    test_is_volatile<phi::nullptr_t>();
    test_is_volatile<bool>();
    test_is_volatile<char>();
    test_is_volatile<signed char>();
    test_is_volatile<unsigned char>();
    test_is_volatile<short>();
    test_is_volatile<unsigned short>();
    test_is_volatile<int>();
    test_is_volatile<unsigned int>();
    test_is_volatile<long>();
    test_is_volatile<unsigned long>();
    test_is_volatile<long long>();
    test_is_volatile<unsigned long long>();
    test_is_volatile<float>();
    test_is_volatile<double>();
    test_is_volatile<long double>();
    test_is_volatile<char8_t>();
    test_is_volatile<char16_t>();
    test_is_volatile<char32_t>();
    test_is_volatile<wchar_t>();

    test_is_volatile<phi::boolean>();
    test_is_volatile<phi::integer<signed char>>();
    test_is_volatile<phi::integer<unsigned char>>();
    test_is_volatile<phi::integer<short>>();
    test_is_volatile<phi::integer<unsigned short>>();
    test_is_volatile<phi::integer<int>>();
    test_is_volatile<phi::integer<unsigned int>>();
    test_is_volatile<phi::integer<long>>();
    test_is_volatile<phi::integer<unsigned long>>();
    test_is_volatile<phi::integer<long long>>();
    test_is_volatile<phi::integer<unsigned long long>>();
    test_is_volatile<phi::floating_point<float>>();
    test_is_volatile<phi::floating_point<double>>();
    test_is_volatile<phi::floating_point<long double>>();

    test_is_volatile<std::vector<int>>();
    test_is_volatile<phi::scope_ptr<int>>();

    test_is_not_volatile<int&>();
    test_is_not_volatile<const int&>();
    test_is_not_volatile<volatile int&>();
    test_is_not_volatile<const volatile int&>();
    test_is_not_volatile<int&&>();
    test_is_not_volatile<const int&&>();
    test_is_not_volatile<volatile int&&>();
    test_is_not_volatile<const volatile int&&>();
    test_is_volatile<int*>();
    test_is_volatile<const int*>();
    test_is_volatile<volatile int*>();
    test_is_volatile<const volatile int*>();
    test_is_volatile<int**>();
    test_is_volatile<const int**>();
    test_is_volatile<volatile int**>();
    test_is_volatile<const volatile int**>();
    test_is_not_volatile<int*&>();
    test_is_not_volatile<const int*&>();
    test_is_not_volatile<volatile int*&>();
    test_is_not_volatile<const volatile int*&>();
    test_is_not_volatile<int*&&>();
    test_is_not_volatile<const int*&&>();
    test_is_not_volatile<volatile int*&&>();
    test_is_not_volatile<const volatile int*&&>();
    test_is_volatile<void*>();
    test_is_volatile<char[3]>();
    test_is_volatile<char[]>();
    test_is_volatile<char* [3]>();
    test_is_volatile<char*[]>();
    test_is_volatile<int(*)[3]>();
    test_is_volatile<int(*)[]>();
    test_is_not_volatile<int(&)[3]>();
    test_is_not_volatile<int(&)[]>();
    test_is_not_volatile<int(&&)[3]>();
    test_is_not_volatile<int(&&)[]>();
    test_is_volatile<char[3][2]>();
    test_is_volatile<char[][2]>();
    test_is_volatile<char* [3][2]>();
    test_is_volatile<char*[][2]>();
    test_is_volatile<int(*)[3][2]>();
    test_is_volatile<int(*)[][2]>();
    test_is_not_volatile<int(&)[3][2]>();
    test_is_not_volatile<int(&)[][2]>();
    test_is_not_volatile<int(&&)[3][2]>();
    test_is_not_volatile<int(&&)[][2]>();
    test_is_volatile<class_type>();
    test_is_volatile<class_type[]>();
    test_is_volatile<class_type[2]>();
    test_is_volatile<template_type<void>>();
    test_is_volatile<template_type<int>>();
    test_is_volatile<template_type<class_type>>();
    test_is_volatile<template_type<incomplete_type>>();
    test_is_volatile<variadic_template<>>();
    test_is_volatile<variadic_template<void>>();
    test_is_volatile<variadic_template<int>>();
    test_is_volatile<variadic_template<class_type>>();
    test_is_volatile<variadic_template<incomplete_type>>();
    test_is_volatile<variadic_template<int, void, class_type, volatile char[]>>();
    test_is_volatile<public_derived_from<base>>();
    test_is_volatile<public_derived_from<derived>>();
    test_is_volatile<public_derived_from<class_type>>();
    test_is_volatile<private_derived_from<base>>();
    test_is_volatile<private_derived_from<derived>>();
    test_is_volatile<private_derived_from<class_type>>();
    test_is_volatile<protected_derived_from<base>>();
    test_is_volatile<protected_derived_from<derived>>();
    test_is_volatile<protected_derived_from<class_type>>();
    test_is_volatile<union_type>();
    test_is_volatile<non_empty_union>();
    test_is_volatile<empty>();
    test_is_volatile<not_empty>();
    test_is_volatile<bit_zero>();
    test_is_volatile<bit_one>();
    test_is_volatile<base>();
    test_is_volatile<derived>();
    test_is_volatile<abstract>();
    test_is_volatile<public_abstract>();
    test_is_volatile<private_abstract>();
    test_is_volatile<protected_abstract>();
    test_is_volatile<abstract_template<int>>();
    test_is_volatile<abstract_template<double>>();
    test_is_volatile<abstract_template<class_type>>();
    test_is_volatile<abstract_template<incomplete_type>>();
    test_is_volatile<final_type>();
    test_is_volatile<public_destructor>();
    test_is_volatile<protected_destructor>();
    test_is_volatile<private_destructor>();
    test_is_volatile<virtual_public_destructor>();
    test_is_volatile<virtual_protected_destructor>();
    test_is_volatile<virtual_private_destructor>();
    test_is_volatile<pure_public_destructor>();
    test_is_volatile<pure_protected_destructor>();
    test_is_volatile<pure_private_destructor>();
    test_is_volatile<deleted_public_destructor>();
    test_is_volatile<deleted_protected_destructor>();
    test_is_volatile<deleted_private_destructor>();
    test_is_volatile<deleted_virtual_public_destructor>();
    test_is_volatile<deleted_virtual_protected_destructor>();
    test_is_volatile<deleted_virtual_private_destructor>();
    test_is_volatile<Enum>();
    test_is_volatile<EnumSigned>();
    test_is_volatile<EnumUnsigned>();
    test_is_volatile<EnumClass>();
    test_is_volatile<EnumStruct>();
    test_is_not_volatile<function_type>();
    test_is_volatile<function_ptr>();
    test_is_volatile<member_object_ptr>();
    test_is_volatile<member_function_ptr>();
    test_is_volatile<incomplete_type>();
    test_is_volatile<incomplete_template<void>>();
    test_is_volatile<incomplete_template<int>>();
    test_is_volatile<incomplete_template<class_type>>();
    test_is_volatile<incomplete_template<incomplete_type>>();
    test_is_volatile<incomplete_variadic_template<>>();
    test_is_volatile<incomplete_variadic_template<void>>();
    test_is_volatile<incomplete_variadic_template<int>>();
    test_is_volatile<incomplete_variadic_template<class_type>>();
    test_is_volatile<incomplete_variadic_template<incomplete_type>>();
    test_is_volatile<incomplete_variadic_template<int, void, class_type, volatile char[]>>();
    test_is_volatile<int class_type::*>();
    test_is_volatile<float class_type::*>();
    test_is_volatile<void * class_type::*>();
    test_is_volatile<int * class_type::*>();
    test_is_not_volatile<int class_type::*&>();
    test_is_not_volatile<float class_type::*&>();
    test_is_not_volatile<void * class_type::*&>();
    test_is_not_volatile<int * class_type::*&>();
    test_is_not_volatile<int class_type::*&&>();
    test_is_not_volatile<float class_type::*&&>();
    test_is_not_volatile<void * class_type::*&&>();
    test_is_not_volatile<int * class_type::*&&>();
    test_is_volatile<int class_type::* const>();
    test_is_volatile<float class_type::* const>();
    test_is_volatile<void * class_type::* const>();
    test_is_not_volatile<int class_type::* const&>();
    test_is_not_volatile<float class_type::* const&>();
    test_is_not_volatile<void * class_type::* const&>();
    test_is_not_volatile<int class_type::* const&&>();
    test_is_not_volatile<float class_type::* const&&>();
    test_is_not_volatile<void * class_type::* const&&>();
    test_is_volatile_cv<int class_type::* volatile>();
    test_is_volatile_cv<float class_type::* volatile>();
    test_is_volatile_cv<void * class_type::* volatile>();
    test_is_not_volatile<int class_type::* volatile&>();
    test_is_not_volatile<float class_type::* volatile&>();
    test_is_not_volatile<void * class_type::* volatile&>();
    test_is_not_volatile<int class_type::* volatile&&>();
    test_is_not_volatile<float class_type::* volatile&&>();
    test_is_not_volatile<void * class_type::* volatile&&>();
    test_is_volatile_cv<int class_type::* const volatile>();
    test_is_volatile_cv<float class_type::* const volatile>();
    test_is_volatile_cv<void * class_type::* const volatile>();
    test_is_not_volatile<int class_type::* const volatile&>();
    test_is_not_volatile<float class_type::* const volatile&>();
    test_is_not_volatile<void * class_type::* const volatile&>();
    test_is_not_volatile<int class_type::* const volatile&&>();
    test_is_not_volatile<float class_type::* const volatile&&>();
    test_is_not_volatile<void * class_type::* const volatile&&>();
    test_is_volatile<non_copyable>();
    test_is_volatile<non_moveable>();
    test_is_volatile<non_constructible>();
    test_is_volatile<tracked>();
    test_is_volatile<trap_constructible>();
    test_is_volatile<trap_implicit_conversion>();
    test_is_volatile<trap_comma>();
    test_is_volatile<trap_call>();
    test_is_volatile<trap_self_assign>();
    test_is_volatile<trap_deref>();
    test_is_volatile<trap_array_subscript>();

    test_is_not_volatile<void()>();
    test_is_not_volatile<void()&>();
    test_is_not_volatile<void() &&>();
    test_is_not_volatile<void() const>();
    test_is_not_volatile<void() const&>();
    test_is_not_volatile<void() const&&>();
    test_is_not_volatile<void() volatile>();
    test_is_not_volatile<void() volatile&>();
    test_is_not_volatile<void() volatile&&>();
    test_is_not_volatile<void() const volatile>();
    test_is_not_volatile<void() const volatile&>();
    test_is_not_volatile<void() const volatile&&>();
    test_is_not_volatile<void() noexcept>();
    test_is_not_volatile<void() & noexcept>();
    test_is_not_volatile<void() && noexcept>();
    test_is_not_volatile<void() const noexcept>();
    test_is_not_volatile<void() const & noexcept>();
    test_is_not_volatile<void() const && noexcept>();
    test_is_not_volatile<void() volatile noexcept>();
    test_is_not_volatile<void() volatile & noexcept>();
    test_is_not_volatile<void() volatile && noexcept>();
    test_is_not_volatile<void() const volatile noexcept>();
    test_is_not_volatile<void() const volatile & noexcept>();
    test_is_not_volatile<void() const volatile && noexcept>();

    test_is_not_volatile<void(int)>();
    test_is_not_volatile<void(int)&>();
    test_is_not_volatile<void(int) &&>();
    test_is_not_volatile<void(int) const>();
    test_is_not_volatile<void(int) const&>();
    test_is_not_volatile<void(int) const&&>();
    test_is_not_volatile<void(int) volatile>();
    test_is_not_volatile<void(int) volatile&>();
    test_is_not_volatile<void(int) volatile&&>();
    test_is_not_volatile<void(int) const volatile>();
    test_is_not_volatile<void(int) const volatile&>();
    test_is_not_volatile<void(int) const volatile&&>();
    test_is_not_volatile<void(int) noexcept>();
    test_is_not_volatile<void(int) & noexcept>();
    test_is_not_volatile<void(int) && noexcept>();
    test_is_not_volatile<void(int) const noexcept>();
    test_is_not_volatile<void(int) const & noexcept>();
    test_is_not_volatile<void(int) const && noexcept>();
    test_is_not_volatile<void(int) volatile noexcept>();
    test_is_not_volatile<void(int) volatile & noexcept>();
    test_is_not_volatile<void(int) volatile && noexcept>();
    test_is_not_volatile<void(int) const volatile noexcept>();
    test_is_not_volatile<void(int) const volatile & noexcept>();
    test_is_not_volatile<void(int) const volatile && noexcept>();

    test_is_not_volatile<void(...)>();
    test_is_not_volatile<void(...)&>();
    test_is_not_volatile<void(...) &&>();
    test_is_not_volatile<void(...) const>();
    test_is_not_volatile<void(...) const&>();
    test_is_not_volatile<void(...) const&&>();
    test_is_not_volatile<void(...) volatile>();
    test_is_not_volatile<void(...) volatile&>();
    test_is_not_volatile<void(...) volatile&&>();
    test_is_not_volatile<void(...) const volatile>();
    test_is_not_volatile<void(...) const volatile&>();
    test_is_not_volatile<void(...) const volatile&&>();
    test_is_not_volatile<void(...) noexcept>();
    test_is_not_volatile<void(...) & noexcept>();
    test_is_not_volatile<void(...) && noexcept>();
    test_is_not_volatile<void(...) const noexcept>();
    test_is_not_volatile<void(...) const & noexcept>();
    test_is_not_volatile<void(...) const && noexcept>();
    test_is_not_volatile<void(...) volatile noexcept>();
    test_is_not_volatile<void(...) volatile & noexcept>();
    test_is_not_volatile<void(...) volatile && noexcept>();
    test_is_not_volatile<void(...) const volatile noexcept>();
    test_is_not_volatile<void(...) const volatile & noexcept>();
    test_is_not_volatile<void(...) const volatile && noexcept>();

    test_is_not_volatile<void(int, ...)>();
    test_is_not_volatile<void(int, ...)&>();
    test_is_not_volatile<void(int, ...) &&>();
    test_is_not_volatile<void(int, ...) const>();
    test_is_not_volatile<void(int, ...) const&>();
    test_is_not_volatile<void(int, ...) const&&>();
    test_is_not_volatile<void(int, ...) volatile>();
    test_is_not_volatile<void(int, ...) volatile&>();
    test_is_not_volatile<void(int, ...) volatile&&>();
    test_is_not_volatile<void(int, ...) const volatile>();
    test_is_not_volatile<void(int, ...) const volatile&>();
    test_is_not_volatile<void(int, ...) const volatile&&>();
    test_is_not_volatile<void(int, ...) noexcept>();
    test_is_not_volatile<void(int, ...) & noexcept>();
    test_is_not_volatile<void(int, ...) && noexcept>();
    test_is_not_volatile<void(int, ...) const noexcept>();
    test_is_not_volatile<void(int, ...) const & noexcept>();
    test_is_not_volatile<void(int, ...) const && noexcept>();
    test_is_not_volatile<void(int, ...) volatile noexcept>();
    test_is_not_volatile<void(int, ...) volatile & noexcept>();
    test_is_not_volatile<void(int, ...) volatile && noexcept>();
    test_is_not_volatile<void(int, ...) const volatile noexcept>();
    test_is_not_volatile<void(int, ...) const volatile & noexcept>();
    test_is_not_volatile<void(int, ...) const volatile && noexcept>();

    test_is_not_volatile<int()>();
    test_is_not_volatile<int()&>();
    test_is_not_volatile<int() &&>();
    test_is_not_volatile<int() const>();
    test_is_not_volatile<int() const&>();
    test_is_not_volatile<int() const&&>();
    test_is_not_volatile<int() volatile>();
    test_is_not_volatile<int() volatile&>();
    test_is_not_volatile<int() volatile&&>();
    test_is_not_volatile<int() const volatile>();
    test_is_not_volatile<int() const volatile&>();
    test_is_not_volatile<int() const volatile&&>();
    test_is_not_volatile<int() noexcept>();
    test_is_not_volatile<int() & noexcept>();
    test_is_not_volatile<int() && noexcept>();
    test_is_not_volatile<int() const noexcept>();
    test_is_not_volatile<int() const & noexcept>();
    test_is_not_volatile<int() const && noexcept>();
    test_is_not_volatile<int() volatile noexcept>();
    test_is_not_volatile<int() volatile & noexcept>();
    test_is_not_volatile<int() volatile && noexcept>();
    test_is_not_volatile<int() const volatile noexcept>();
    test_is_not_volatile<int() const volatile & noexcept>();
    test_is_not_volatile<int() const volatile && noexcept>();

    test_is_not_volatile<int(int)>();
    test_is_not_volatile<int(int)&>();
    test_is_not_volatile<int(int) &&>();
    test_is_not_volatile<int(int) const>();
    test_is_not_volatile<int(int) const&>();
    test_is_not_volatile<int(int) const&&>();
    test_is_not_volatile<int(int) volatile>();
    test_is_not_volatile<int(int) volatile&>();
    test_is_not_volatile<int(int) volatile&&>();
    test_is_not_volatile<int(int) const volatile>();
    test_is_not_volatile<int(int) const volatile&>();
    test_is_not_volatile<int(int) const volatile&&>();
    test_is_not_volatile<int(int) noexcept>();
    test_is_not_volatile<int(int) & noexcept>();
    test_is_not_volatile<int(int) && noexcept>();
    test_is_not_volatile<int(int) const noexcept>();
    test_is_not_volatile<int(int) const & noexcept>();
    test_is_not_volatile<int(int) const && noexcept>();
    test_is_not_volatile<int(int) volatile noexcept>();
    test_is_not_volatile<int(int) volatile & noexcept>();
    test_is_not_volatile<int(int) volatile && noexcept>();
    test_is_not_volatile<int(int) const volatile noexcept>();
    test_is_not_volatile<int(int) const volatile & noexcept>();
    test_is_not_volatile<int(int) const volatile && noexcept>();

    test_is_not_volatile<int(...)>();
    test_is_not_volatile<int(...)&>();
    test_is_not_volatile<int(...) &&>();
    test_is_not_volatile<int(...) const>();
    test_is_not_volatile<int(...) const&>();
    test_is_not_volatile<int(...) const&&>();
    test_is_not_volatile<int(...) volatile>();
    test_is_not_volatile<int(...) volatile&>();
    test_is_not_volatile<int(...) volatile&&>();
    test_is_not_volatile<int(...) const volatile>();
    test_is_not_volatile<int(...) const volatile&>();
    test_is_not_volatile<int(...) const volatile&&>();
    test_is_not_volatile<int(...) noexcept>();
    test_is_not_volatile<int(...) & noexcept>();
    test_is_not_volatile<int(...) && noexcept>();
    test_is_not_volatile<int(...) const noexcept>();
    test_is_not_volatile<int(...) const & noexcept>();
    test_is_not_volatile<int(...) const && noexcept>();
    test_is_not_volatile<int(...) volatile noexcept>();
    test_is_not_volatile<int(...) volatile & noexcept>();
    test_is_not_volatile<int(...) volatile && noexcept>();
    test_is_not_volatile<int(...) const volatile noexcept>();
    test_is_not_volatile<int(...) const volatile & noexcept>();
    test_is_not_volatile<int(...) const volatile && noexcept>();

    test_is_not_volatile<int(int, ...)>();
    test_is_not_volatile<int(int, ...)&>();
    test_is_not_volatile<int(int, ...) &&>();
    test_is_not_volatile<int(int, ...) const>();
    test_is_not_volatile<int(int, ...) const&>();
    test_is_not_volatile<int(int, ...) const&&>();
    test_is_not_volatile<int(int, ...) volatile>();
    test_is_not_volatile<int(int, ...) volatile&>();
    test_is_not_volatile<int(int, ...) volatile&&>();
    test_is_not_volatile<int(int, ...) const volatile>();
    test_is_not_volatile<int(int, ...) const volatile&>();
    test_is_not_volatile<int(int, ...) const volatile&&>();
    test_is_not_volatile<int(int, ...) noexcept>();
    test_is_not_volatile<int(int, ...) & noexcept>();
    test_is_not_volatile<int(int, ...) && noexcept>();
    test_is_not_volatile<int(int, ...) const noexcept>();
    test_is_not_volatile<int(int, ...) const & noexcept>();
    test_is_not_volatile<int(int, ...) const && noexcept>();
    test_is_not_volatile<int(int, ...) volatile noexcept>();
    test_is_not_volatile<int(int, ...) volatile & noexcept>();
    test_is_not_volatile<int(int, ...) volatile && noexcept>();
    test_is_not_volatile<int(int, ...) const volatile noexcept>();
    test_is_not_volatile<int(int, ...) const volatile & noexcept>();
    test_is_not_volatile<int(int, ...) const volatile && noexcept>();

    test_is_volatile<void (*)()>();
    test_is_volatile<void (*)() noexcept>();

    test_is_volatile<void (*)(int)>();
    test_is_volatile<void (*)(int) noexcept>();

    test_is_volatile<void (*)(...)>();
    test_is_volatile<void (*)(...) noexcept>();

    test_is_volatile<void (*)(int, ...)>();
    test_is_volatile<void (*)(int, ...) noexcept>();

    test_is_volatile<int (*)()>();
    test_is_volatile<int (*)() noexcept>();

    test_is_volatile<int (*)(int)>();
    test_is_volatile<int (*)(int) noexcept>();

    test_is_volatile<int (*)(...)>();
    test_is_volatile<int (*)(...) noexcept>();

    test_is_volatile<int (*)(int, ...)>();
    test_is_volatile<int (*)(int, ...) noexcept>();

    test_is_not_volatile<void (&)()>();
    test_is_not_volatile<void (&)() noexcept>();

    test_is_not_volatile<void (&)(int)>();
    test_is_not_volatile<void (&)(int) noexcept>();

    test_is_not_volatile<void (&)(...)>();
    test_is_not_volatile<void (&)(...) noexcept>();

    test_is_not_volatile<void (&)(int, ...)>();
    test_is_not_volatile<void (&)(int, ...) noexcept>();

    test_is_not_volatile<int (&)()>();
    test_is_not_volatile<int (&)() noexcept>();

    test_is_not_volatile<int (&)(int)>();
    test_is_not_volatile<int (&)(int) noexcept>();

    test_is_not_volatile<int (&)(...)>();
    test_is_not_volatile<int (&)(...) noexcept>();

    test_is_not_volatile<int (&)(int, ...)>();
    test_is_not_volatile<int (&)(int, ...) noexcept>();

    test_is_not_volatile<void (&&)()>();
    test_is_not_volatile<void (&&)() noexcept>();

    test_is_not_volatile<void (&&)(int)>();
    test_is_not_volatile<void (&&)(int) noexcept>();

    test_is_not_volatile<void (&&)(...)>();
    test_is_not_volatile<void (&&)(...) noexcept>();

    test_is_not_volatile<void (&&)(int, ...)>();
    test_is_not_volatile<void (&&)(int, ...) noexcept>();

    test_is_not_volatile<int (&&)()>();
    test_is_not_volatile<int (&&)() noexcept>();

    test_is_not_volatile<int (&&)(int)>();
    test_is_not_volatile<int (&&)(int) noexcept>();

    test_is_not_volatile<int (&&)(...)>();
    test_is_not_volatile<int (&&)(...) noexcept>();

    test_is_not_volatile<int (&&)(int, ...)>();
    test_is_not_volatile<int (&&)(int, ...) noexcept>();

    test_is_volatile<void (class_type::*)()>();
    test_is_volatile<void (class_type::*)()&>();
    test_is_volatile<void (class_type::*)() &&>();
    test_is_volatile<void (class_type::*)() const>();
    test_is_volatile<void (class_type::*)() const&>();
    test_is_volatile<void (class_type::*)() const&&>();
    test_is_volatile<void (class_type::*)() noexcept>();
    test_is_volatile<void (class_type::*)() & noexcept>();
    test_is_volatile<void (class_type::*)() && noexcept>();
    test_is_volatile<void (class_type::*)() const noexcept>();
    test_is_volatile<void (class_type::*)() const & noexcept>();
    test_is_volatile<void (class_type::*)() const && noexcept>();

    test_is_volatile<void (class_type::*)(int)>();
    test_is_volatile<void (class_type::*)(int)&>();
    test_is_volatile<void (class_type::*)(int) &&>();
    test_is_volatile<void (class_type::*)(int) const>();
    test_is_volatile<void (class_type::*)(int) const&>();
    test_is_volatile<void (class_type::*)(int) const&&>();
    test_is_volatile<void (class_type::*)(int) noexcept>();
    test_is_volatile<void (class_type::*)(int) & noexcept>();
    test_is_volatile<void (class_type::*)(int) && noexcept>();
    test_is_volatile<void (class_type::*)(int) const noexcept>();
    test_is_volatile<void (class_type::*)(int) const & noexcept>();
    test_is_volatile<void (class_type::*)(int) const && noexcept>();

    test_is_volatile<void (class_type::*)(...)>();
    test_is_volatile<void (class_type::*)(...)&>();
    test_is_volatile<void (class_type::*)(...) &&>();
    test_is_volatile<void (class_type::*)(...) const>();
    test_is_volatile<void (class_type::*)(...) const&>();
    test_is_volatile<void (class_type::*)(...) const&&>();
    test_is_volatile<void (class_type::*)(...) noexcept>();
    test_is_volatile<void (class_type::*)(...) & noexcept>();
    test_is_volatile<void (class_type::*)(...) && noexcept>();
    test_is_volatile<void (class_type::*)(...) const noexcept>();
    test_is_volatile<void (class_type::*)(...) const & noexcept>();
    test_is_volatile<void (class_type::*)(...) const && noexcept>();

    test_is_volatile<void (class_type::*)(int, ...)>();
    test_is_volatile<void (class_type::*)(int, ...)&>();
    test_is_volatile<void (class_type::*)(int, ...) &&>();
    test_is_volatile<void (class_type::*)(int, ...) const>();
    test_is_volatile<void (class_type::*)(int, ...) const&>();
    test_is_volatile<void (class_type::*)(int, ...) const&&>();
    test_is_volatile<void (class_type::*)(int, ...) noexcept>();
    test_is_volatile<void (class_type::*)(int, ...) & noexcept>();
    test_is_volatile<void (class_type::*)(int, ...) && noexcept>();
    test_is_volatile<void (class_type::*)(int, ...) const noexcept>();
    test_is_volatile<void (class_type::*)(int, ...) const & noexcept>();
    test_is_volatile<void (class_type::*)(int, ...) const && noexcept>();

    test_is_volatile<int (class_type::*)()>();
    test_is_volatile<int (class_type::*)()&>();
    test_is_volatile<int (class_type::*)() &&>();
    test_is_volatile<int (class_type::*)() const>();
    test_is_volatile<int (class_type::*)() const&>();
    test_is_volatile<int (class_type::*)() const&&>();
    test_is_volatile<int (class_type::*)() noexcept>();
    test_is_volatile<int (class_type::*)() & noexcept>();
    test_is_volatile<int (class_type::*)() && noexcept>();
    test_is_volatile<int (class_type::*)() const noexcept>();
    test_is_volatile<int (class_type::*)() const & noexcept>();
    test_is_volatile<int (class_type::*)() const && noexcept>();

    test_is_volatile<int (class_type::*)(int)>();
    test_is_volatile<int (class_type::*)(int)&>();
    test_is_volatile<int (class_type::*)(int) &&>();
    test_is_volatile<int (class_type::*)(int) const>();
    test_is_volatile<int (class_type::*)(int) const&>();
    test_is_volatile<int (class_type::*)(int) const&&>();
    test_is_volatile<int (class_type::*)(int) noexcept>();
    test_is_volatile<int (class_type::*)(int) & noexcept>();
    test_is_volatile<int (class_type::*)(int) && noexcept>();
    test_is_volatile<int (class_type::*)(int) const noexcept>();
    test_is_volatile<int (class_type::*)(int) const & noexcept>();
    test_is_volatile<int (class_type::*)(int) const && noexcept>();

    test_is_volatile<int (class_type::*)(...)>();
    test_is_volatile<int (class_type::*)(...)&>();
    test_is_volatile<int (class_type::*)(...) &&>();
    test_is_volatile<int (class_type::*)(...) const>();
    test_is_volatile<int (class_type::*)(...) const&>();
    test_is_volatile<int (class_type::*)(...) const&&>();
    test_is_volatile<int (class_type::*)(...) noexcept>();
    test_is_volatile<int (class_type::*)(...) & noexcept>();
    test_is_volatile<int (class_type::*)(...) && noexcept>();
    test_is_volatile<int (class_type::*)(...) const noexcept>();
    test_is_volatile<int (class_type::*)(...) const & noexcept>();
    test_is_volatile<int (class_type::*)(...) const && noexcept>();

    test_is_volatile<int (class_type::*)(int, ...)>();
    test_is_volatile<int (class_type::*)(int, ...)&>();
    test_is_volatile<int (class_type::*)(int, ...) &&>();
    test_is_volatile<int (class_type::*)(int, ...) const>();
    test_is_volatile<int (class_type::*)(int, ...) const&>();
    test_is_volatile<int (class_type::*)(int, ...) const&&>();
    test_is_volatile<int (class_type::*)(int, ...) noexcept>();
    test_is_volatile<int (class_type::*)(int, ...) & noexcept>();
    test_is_volatile<int (class_type::*)(int, ...) && noexcept>();
    test_is_volatile<int (class_type::*)(int, ...) const noexcept>();
    test_is_volatile<int (class_type::*)(int, ...) const & noexcept>();
    test_is_volatile<int (class_type::*)(int, ...) const && noexcept>();
}
