#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/compiler_support/compiler.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_const.hpp>
#include <type_traits>
#include <vector>

template <typename TypeT>
void test_is_const_impl()
{
    STATIC_REQUIRE(phi::is_const<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_const<TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_const_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_not_const_v<TypeT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_const<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_const<TypeT>);

    // Standard compatibility
    STATIC_REQUIRE(std::is_const<TypeT>::value);
}

template <typename TypeT>
void test_is_not_const_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_const<TypeT>::value);
    STATIC_REQUIRE(phi::is_not_const<TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_const_v<TypeT>);
    STATIC_REQUIRE(phi::is_not_const_v<TypeT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_const<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_const<TypeT>);

    // Standard compatibility
    STATIC_REQUIRE_FALSE(std::is_const<TypeT>::value);
}

template <typename TypeT>
void test_is_const()
{
    test_is_not_const_impl<TypeT>();
    test_is_const_impl<const TypeT>();
    test_is_not_const_impl<volatile TypeT>();
    test_is_const_impl<const volatile TypeT>();
}

template <typename TypeT>
void test_is_const_always()
{
    test_is_const_impl<TypeT>();
    test_is_const_impl<const TypeT>();
    test_is_const_impl<volatile TypeT>();
    test_is_const_impl<const volatile TypeT>();
}

template <typename TypeT>
void test_is_not_const()
{
    test_is_not_const_impl<TypeT>();
    test_is_not_const_impl<const TypeT>();
    test_is_not_const_impl<volatile TypeT>();
    test_is_not_const_impl<const volatile TypeT>();
}

TEST_CASE("is_const")
{
    test_is_const<void>();
    test_is_const<phi::nullptr_t>();
    test_is_const<bool>();
    test_is_const<char>();
    test_is_const<signed char>();
    test_is_const<unsigned char>();
    test_is_const<short>();
    test_is_const<unsigned short>();
    test_is_const<int>();
    test_is_const<unsigned int>();
    test_is_const<long>();
    test_is_const<unsigned long>();
    test_is_const<long long>();
    test_is_const<unsigned long long>();
    test_is_const<float>();
    test_is_const<double>();
    test_is_const<long double>();
    test_is_const<char8_t>();
    test_is_const<char16_t>();
    test_is_const<char32_t>();
    test_is_const<wchar_t>();

    test_is_const<phi::boolean>();
    test_is_const<phi::integer<signed char>>();
    test_is_const<phi::integer<unsigned char>>();
    test_is_const<phi::integer<short>>();
    test_is_const<phi::integer<unsigned short>>();
    test_is_const<phi::integer<int>>();
    test_is_const<phi::integer<unsigned int>>();
    test_is_const<phi::integer<long>>();
    test_is_const<phi::integer<unsigned long>>();
    test_is_const<phi::integer<long long>>();
    test_is_const<phi::integer<unsigned long long>>();
    test_is_const<phi::floating_point<float>>();
    test_is_const<phi::floating_point<double>>();
    test_is_const<phi::floating_point<long double>>();

    test_is_const<std::vector<int>>();
    test_is_const<phi::scope_ptr<int>>();

    test_is_not_const<int&>();
    test_is_not_const<const int&>();
    test_is_not_const<volatile int&>();
    test_is_not_const<const volatile int&>();
    test_is_not_const<int&&>();
    test_is_not_const<const int&&>();
    test_is_not_const<volatile int&&>();
    test_is_not_const<const volatile int&&>();
    test_is_const<int*>();
    test_is_const<const int*>();
    test_is_const<volatile int*>();
    test_is_const<const volatile int*>();
    test_is_const<int**>();
    test_is_const<const int**>();
    test_is_const<volatile int**>();
    test_is_const<const volatile int**>();
    test_is_not_const<int*&>();
    test_is_not_const<const int*&>();
    test_is_not_const<volatile int*&>();
    test_is_not_const<const volatile int*&>();
    test_is_not_const<int*&&>();
    test_is_not_const<const int*&&>();
    test_is_not_const<volatile int*&&>();
    test_is_not_const<const volatile int*&&>();
    test_is_const<void*>();
    test_is_const<char[3]>();
    test_is_const<char[]>();
    test_is_const<char* [3]>();
    test_is_const<char*[]>();
    test_is_const<int(*)[3]>();
    test_is_const<int(*)[]>();
    test_is_not_const<int(&)[3]>();
    test_is_not_const<int(&)[]>();
    test_is_not_const<int(&&)[3]>();
    test_is_not_const<int(&&)[]>();
    test_is_const<char[3][2]>();
    test_is_const<char[][2]>();
    test_is_const<char* [3][2]>();
    test_is_const<char*[][2]>();
    test_is_const<int(*)[3][2]>();
    test_is_const<int(*)[][2]>();
    test_is_not_const<int(&)[3][2]>();
    test_is_not_const<int(&)[][2]>();
    test_is_not_const<int(&&)[3][2]>();
    test_is_not_const<int(&&)[][2]>();
    test_is_const<class_type>();
    test_is_const<class_type[]>();
    test_is_const<class_type[2]>();
    test_is_const<template_type<void>>();
    test_is_const<template_type<int>>();
    test_is_const<template_type<class_type>>();
    test_is_const<template_type<incomplete_type>>();
    test_is_const<variadic_template<>>();
    test_is_const<variadic_template<void>>();
    test_is_const<variadic_template<int>>();
    test_is_const<variadic_template<class_type>>();
    test_is_const<variadic_template<incomplete_type>>();
    test_is_const<variadic_template<int, void, class_type, volatile char[]>>();
    test_is_const<public_derived_from<base>>();
    test_is_const<public_derived_from<derived>>();
    test_is_const<public_derived_from<class_type>>();
    test_is_const<private_derived_from<base>>();
    test_is_const<private_derived_from<derived>>();
    test_is_const<private_derived_from<class_type>>();
    test_is_const<protected_derived_from<base>>();
    test_is_const<protected_derived_from<derived>>();
    test_is_const<protected_derived_from<class_type>>();
    test_is_const<union_type>();
    test_is_const<non_empty_union>();
    test_is_const<empty>();
    test_is_const<not_empty>();
    test_is_const<bit_zero>();
    test_is_const<bit_one>();
    test_is_const<base>();
    test_is_const<derived>();
    test_is_const<abstract>();
    test_is_const<public_abstract>();
    test_is_const<private_abstract>();
    test_is_const<protected_abstract>();
    test_is_const<abstract_template<int>>();
    test_is_const<abstract_template<double>>();
    test_is_const<abstract_template<class_type>>();
    test_is_const<abstract_template<incomplete_type>>();
    test_is_const<final_type>();
    test_is_const<public_destructor>();
    test_is_const<protected_destructor>();
    test_is_const<private_destructor>();
    test_is_const<virtual_public_destructor>();
    test_is_const<virtual_protected_destructor>();
    test_is_const<virtual_private_destructor>();
    test_is_const<pure_public_destructor>();
    test_is_const<pure_protected_destructor>();
    test_is_const<pure_private_destructor>();
    test_is_const<deleted_public_destructor>();
    test_is_const<deleted_protected_destructor>();
    test_is_const<deleted_private_destructor>();
    test_is_const<deleted_virtual_public_destructor>();
    test_is_const<deleted_virtual_protected_destructor>();
    test_is_const<deleted_virtual_private_destructor>();
    test_is_const<Enum>();
    test_is_const<EnumSigned>();
    test_is_const<EnumUnsigned>();
    test_is_const<EnumClass>();
    test_is_const<EnumStruct>();
    test_is_not_const<function_type>();
    test_is_const<function_ptr>();
    test_is_const<member_object_ptr>();
    test_is_const<member_function_ptr>();
    test_is_const<incomplete_type>();
    test_is_const<incomplete_template<void>>();
    test_is_const<incomplete_template<int>>();
    test_is_const<incomplete_template<class_type>>();
    test_is_const<incomplete_template<incomplete_type>>();
    test_is_const<incomplete_variadic_template<>>();
    test_is_const<incomplete_variadic_template<void>>();
    test_is_const<incomplete_variadic_template<int>>();
    test_is_const<incomplete_variadic_template<class_type>>();
    test_is_const<incomplete_variadic_template<incomplete_type>>();
    test_is_const<incomplete_variadic_template<int, void, class_type, volatile char[]>>();
    test_is_const<int class_type::*>();
    test_is_const<float class_type::*>();
    test_is_const<void * class_type::*>();
    test_is_const<int * class_type::*>();
    test_is_not_const<int class_type::*&>();
    test_is_not_const<float class_type::*&>();
    test_is_not_const<void * class_type::*&>();
    test_is_not_const<int * class_type::*&>();
    test_is_not_const<int class_type::*&&>();
    test_is_not_const<float class_type::*&&>();
    test_is_not_const<void * class_type::*&&>();
    test_is_not_const<int * class_type::*&&>();
    test_is_const_always<int class_type::* const>();
    test_is_const_always<float class_type::* const>();
    test_is_const_always<void * class_type::* const>();
    test_is_not_const<int class_type::* const&>();
    test_is_not_const<float class_type::* const&>();
    test_is_not_const<void * class_type::* const&>();
    test_is_not_const<int class_type::* const&&>();
    test_is_not_const<float class_type::* const&&>();
    test_is_not_const<void * class_type::* const&&>();
    test_is_const<int class_type::* volatile>();
    test_is_const<float class_type::* volatile>();
    test_is_const<void * class_type::* volatile>();
    test_is_not_const<int class_type::* volatile&>();
    test_is_not_const<float class_type::* volatile&>();
    test_is_not_const<void * class_type::* volatile&>();
    test_is_not_const<int class_type::* volatile&&>();
    test_is_not_const<float class_type::* volatile&&>();
    test_is_not_const<void * class_type::* volatile&&>();
    test_is_const_always<int class_type::* const volatile>();
    test_is_const_always<float class_type::* const volatile>();
    test_is_const_always<void * class_type::* const volatile>();
    test_is_not_const<int class_type::* const volatile&>();
    test_is_not_const<float class_type::* const volatile&>();
    test_is_not_const<void * class_type::* const volatile&>();
    test_is_not_const<int class_type::* const volatile&&>();
    test_is_not_const<float class_type::* const volatile&&>();
    test_is_not_const<void * class_type::* const volatile&&>();
    test_is_const<non_copyable>();
    test_is_const<non_moveable>();
    test_is_const<non_constructible>();
    test_is_const<tracked>();
    test_is_const<trap_constructible>();
    test_is_const<trap_implicit_conversion>();
    test_is_const<trap_comma>();
    test_is_const<trap_call>();
    test_is_const<trap_self_assign>();
    test_is_const<trap_deref>();
    test_is_const<trap_array_subscript>();

    test_is_not_const<void()>();
    test_is_not_const<void()&>();
    test_is_not_const<void() &&>();
    test_is_not_const<void() const>();
    test_is_not_const<void() const&>();
    test_is_not_const<void() const&&>();
    test_is_not_const<void() volatile>();
    test_is_not_const<void() volatile&>();
    test_is_not_const<void() volatile&&>();
    test_is_not_const<void() const volatile>();
    test_is_not_const<void() const volatile&>();
    test_is_not_const<void() const volatile&&>();
    test_is_not_const<void() noexcept>();
    test_is_not_const<void() & noexcept>();
    test_is_not_const<void() && noexcept>();
    test_is_not_const<void() const noexcept>();
    test_is_not_const<void() const & noexcept>();
    test_is_not_const<void() const && noexcept>();
    test_is_not_const<void() volatile noexcept>();
    test_is_not_const<void() volatile & noexcept>();
    test_is_not_const<void() volatile && noexcept>();
    test_is_not_const<void() const volatile noexcept>();
    test_is_not_const<void() const volatile & noexcept>();
    test_is_not_const<void() const volatile && noexcept>();

    test_is_not_const<void(int)>();
    test_is_not_const<void(int)&>();
    test_is_not_const<void(int) &&>();
    test_is_not_const<void(int) const>();
    test_is_not_const<void(int) const&>();
    test_is_not_const<void(int) const&&>();
    test_is_not_const<void(int) volatile>();
    test_is_not_const<void(int) volatile&>();
    test_is_not_const<void(int) volatile&&>();
    test_is_not_const<void(int) const volatile>();
    test_is_not_const<void(int) const volatile&>();
    test_is_not_const<void(int) const volatile&&>();
    test_is_not_const<void(int) noexcept>();
    test_is_not_const<void(int) & noexcept>();
    test_is_not_const<void(int) && noexcept>();
    test_is_not_const<void(int) const noexcept>();
    test_is_not_const<void(int) const & noexcept>();
    test_is_not_const<void(int) const && noexcept>();
    test_is_not_const<void(int) volatile noexcept>();
    test_is_not_const<void(int) volatile & noexcept>();
    test_is_not_const<void(int) volatile && noexcept>();
    test_is_not_const<void(int) const volatile noexcept>();
    test_is_not_const<void(int) const volatile & noexcept>();
    test_is_not_const<void(int) const volatile && noexcept>();

    test_is_not_const<void(...)>();
    test_is_not_const<void(...)&>();
    test_is_not_const<void(...) &&>();
    test_is_not_const<void(...) const>();
    test_is_not_const<void(...) const&>();
    test_is_not_const<void(...) const&&>();
    test_is_not_const<void(...) volatile>();
    test_is_not_const<void(...) volatile&>();
    test_is_not_const<void(...) volatile&&>();
    test_is_not_const<void(...) const volatile>();
    test_is_not_const<void(...) const volatile&>();
    test_is_not_const<void(...) const volatile&&>();
    test_is_not_const<void(...) noexcept>();
    test_is_not_const<void(...) & noexcept>();
    test_is_not_const<void(...) && noexcept>();
    test_is_not_const<void(...) const noexcept>();
    test_is_not_const<void(...) const & noexcept>();
    test_is_not_const<void(...) const && noexcept>();
    test_is_not_const<void(...) volatile noexcept>();
    test_is_not_const<void(...) volatile & noexcept>();
    test_is_not_const<void(...) volatile && noexcept>();
    test_is_not_const<void(...) const volatile noexcept>();
    test_is_not_const<void(...) const volatile & noexcept>();
    test_is_not_const<void(...) const volatile && noexcept>();

    test_is_not_const<void(int, ...)>();
    test_is_not_const<void(int, ...)&>();
    test_is_not_const<void(int, ...) &&>();
    test_is_not_const<void(int, ...) const>();
    test_is_not_const<void(int, ...) const&>();
    test_is_not_const<void(int, ...) const&&>();
    test_is_not_const<void(int, ...) volatile>();
    test_is_not_const<void(int, ...) volatile&>();
    test_is_not_const<void(int, ...) volatile&&>();
    test_is_not_const<void(int, ...) const volatile>();
    test_is_not_const<void(int, ...) const volatile&>();
    test_is_not_const<void(int, ...) const volatile&&>();
    test_is_not_const<void(int, ...) noexcept>();
    test_is_not_const<void(int, ...) & noexcept>();
    test_is_not_const<void(int, ...) && noexcept>();
    test_is_not_const<void(int, ...) const noexcept>();
    test_is_not_const<void(int, ...) const & noexcept>();
    test_is_not_const<void(int, ...) const && noexcept>();
    test_is_not_const<void(int, ...) volatile noexcept>();
    test_is_not_const<void(int, ...) volatile & noexcept>();
    test_is_not_const<void(int, ...) volatile && noexcept>();
    test_is_not_const<void(int, ...) const volatile noexcept>();
    test_is_not_const<void(int, ...) const volatile & noexcept>();
    test_is_not_const<void(int, ...) const volatile && noexcept>();

    test_is_not_const<int()>();
    test_is_not_const<int()&>();
    test_is_not_const<int() &&>();
    test_is_not_const<int() const>();
    test_is_not_const<int() const&>();
    test_is_not_const<int() const&&>();
    test_is_not_const<int() volatile>();
    test_is_not_const<int() volatile&>();
    test_is_not_const<int() volatile&&>();
    test_is_not_const<int() const volatile>();
    test_is_not_const<int() const volatile&>();
    test_is_not_const<int() const volatile&&>();
    test_is_not_const<int() noexcept>();
    test_is_not_const<int() & noexcept>();
    test_is_not_const<int() && noexcept>();
    test_is_not_const<int() const noexcept>();
    test_is_not_const<int() const & noexcept>();
    test_is_not_const<int() const && noexcept>();
    test_is_not_const<int() volatile noexcept>();
    test_is_not_const<int() volatile & noexcept>();
    test_is_not_const<int() volatile && noexcept>();
    test_is_not_const<int() const volatile noexcept>();
    test_is_not_const<int() const volatile & noexcept>();
    test_is_not_const<int() const volatile && noexcept>();

    test_is_not_const<int(int)>();
    test_is_not_const<int(int)&>();
    test_is_not_const<int(int) &&>();
    test_is_not_const<int(int) const>();
    test_is_not_const<int(int) const&>();
    test_is_not_const<int(int) const&&>();
    test_is_not_const<int(int) volatile>();
    test_is_not_const<int(int) volatile&>();
    test_is_not_const<int(int) volatile&&>();
    test_is_not_const<int(int) const volatile>();
    test_is_not_const<int(int) const volatile&>();
    test_is_not_const<int(int) const volatile&&>();
    test_is_not_const<int(int) noexcept>();
    test_is_not_const<int(int) & noexcept>();
    test_is_not_const<int(int) && noexcept>();
    test_is_not_const<int(int) const noexcept>();
    test_is_not_const<int(int) const & noexcept>();
    test_is_not_const<int(int) const && noexcept>();
    test_is_not_const<int(int) volatile noexcept>();
    test_is_not_const<int(int) volatile & noexcept>();
    test_is_not_const<int(int) volatile && noexcept>();
    test_is_not_const<int(int) const volatile noexcept>();
    test_is_not_const<int(int) const volatile & noexcept>();
    test_is_not_const<int(int) const volatile && noexcept>();

    test_is_not_const<int(...)>();
    test_is_not_const<int(...)&>();
    test_is_not_const<int(...) &&>();
    test_is_not_const<int(...) const>();
    test_is_not_const<int(...) const&>();
    test_is_not_const<int(...) const&&>();
    test_is_not_const<int(...) volatile>();
    test_is_not_const<int(...) volatile&>();
    test_is_not_const<int(...) volatile&&>();
    test_is_not_const<int(...) const volatile>();
    test_is_not_const<int(...) const volatile&>();
    test_is_not_const<int(...) const volatile&&>();
    test_is_not_const<int(...) noexcept>();
    test_is_not_const<int(...) & noexcept>();
    test_is_not_const<int(...) && noexcept>();
    test_is_not_const<int(...) const noexcept>();
    test_is_not_const<int(...) const & noexcept>();
    test_is_not_const<int(...) const && noexcept>();
    test_is_not_const<int(...) volatile noexcept>();
    test_is_not_const<int(...) volatile & noexcept>();
    test_is_not_const<int(...) volatile && noexcept>();
    test_is_not_const<int(...) const volatile noexcept>();
    test_is_not_const<int(...) const volatile & noexcept>();
    test_is_not_const<int(...) const volatile && noexcept>();

    test_is_not_const<int(int, ...)>();
    test_is_not_const<int(int, ...)&>();
    test_is_not_const<int(int, ...) &&>();
    test_is_not_const<int(int, ...) const>();
    test_is_not_const<int(int, ...) const&>();
    test_is_not_const<int(int, ...) const&&>();
    test_is_not_const<int(int, ...) volatile>();
    test_is_not_const<int(int, ...) volatile&>();
    test_is_not_const<int(int, ...) volatile&&>();
    test_is_not_const<int(int, ...) const volatile>();
    test_is_not_const<int(int, ...) const volatile&>();
    test_is_not_const<int(int, ...) const volatile&&>();
    test_is_not_const<int(int, ...) noexcept>();
    test_is_not_const<int(int, ...) & noexcept>();
    test_is_not_const<int(int, ...) && noexcept>();
    test_is_not_const<int(int, ...) const noexcept>();
    test_is_not_const<int(int, ...) const & noexcept>();
    test_is_not_const<int(int, ...) const && noexcept>();
    test_is_not_const<int(int, ...) volatile noexcept>();
    test_is_not_const<int(int, ...) volatile & noexcept>();
    test_is_not_const<int(int, ...) volatile && noexcept>();
    test_is_not_const<int(int, ...) const volatile noexcept>();
    test_is_not_const<int(int, ...) const volatile & noexcept>();
    test_is_not_const<int(int, ...) const volatile && noexcept>();

    test_is_const<void (*)()>();
    test_is_const<void (*)() noexcept>();

    test_is_const<void (*)(int)>();
    test_is_const<void (*)(int) noexcept>();

    test_is_const<void (*)(...)>();
    test_is_const<void (*)(...) noexcept>();

    test_is_const<void (*)(int, ...)>();
    test_is_const<void (*)(int, ...) noexcept>();

    test_is_const<int (*)()>();
    test_is_const<int (*)() noexcept>();

    test_is_const<int (*)(int)>();
    test_is_const<int (*)(int) noexcept>();

    test_is_const<int (*)(...)>();
    test_is_const<int (*)(...) noexcept>();

    test_is_const<int (*)(int, ...)>();
    test_is_const<int (*)(int, ...) noexcept>();

    test_is_not_const<void (&)()>();
    test_is_not_const<void (&)() noexcept>();

    test_is_not_const<void (&)(int)>();
    test_is_not_const<void (&)(int) noexcept>();

    test_is_not_const<void (&)(...)>();
    test_is_not_const<void (&)(...) noexcept>();

    test_is_not_const<void (&)(int, ...)>();
    test_is_not_const<void (&)(int, ...) noexcept>();

    test_is_not_const<int (&)()>();
    test_is_not_const<int (&)() noexcept>();

    test_is_not_const<int (&)(int)>();
    test_is_not_const<int (&)(int) noexcept>();

    test_is_not_const<int (&)(...)>();
    test_is_not_const<int (&)(...) noexcept>();

    test_is_not_const<int (&)(int, ...)>();
    test_is_not_const<int (&)(int, ...) noexcept>();

    test_is_not_const<void (&&)()>();
    test_is_not_const<void (&&)() noexcept>();

    test_is_not_const<void (&&)(int)>();
    test_is_not_const<void (&&)(int) noexcept>();

    test_is_not_const<void (&&)(...)>();
    test_is_not_const<void (&&)(...) noexcept>();

    test_is_not_const<void (&&)(int, ...)>();
    test_is_not_const<void (&&)(int, ...) noexcept>();

    test_is_not_const<int (&&)()>();
    test_is_not_const<int (&&)() noexcept>();

    test_is_not_const<int (&&)(int)>();
    test_is_not_const<int (&&)(int) noexcept>();

    test_is_not_const<int (&&)(...)>();
    test_is_not_const<int (&&)(...) noexcept>();

    test_is_not_const<int (&&)(int, ...)>();
    test_is_not_const<int (&&)(int, ...) noexcept>();

    test_is_const<void (class_type::*)()>();
    test_is_const<void (class_type::*)()&>();
    test_is_const<void (class_type::*)() &&>();
    test_is_const<void (class_type::*)() const>();
    test_is_const<void (class_type::*)() const&>();
    test_is_const<void (class_type::*)() const&&>();
    test_is_const<void (class_type::*)() noexcept>();
    test_is_const<void (class_type::*)() & noexcept>();
    test_is_const<void (class_type::*)() && noexcept>();
    test_is_const<void (class_type::*)() const noexcept>();
    test_is_const<void (class_type::*)() const & noexcept>();
    test_is_const<void (class_type::*)() const && noexcept>();

    test_is_const<void (class_type::*)(int)>();
    test_is_const<void (class_type::*)(int)&>();
    test_is_const<void (class_type::*)(int) &&>();
    test_is_const<void (class_type::*)(int) const>();
    test_is_const<void (class_type::*)(int) const&>();
    test_is_const<void (class_type::*)(int) const&&>();
    test_is_const<void (class_type::*)(int) noexcept>();
    test_is_const<void (class_type::*)(int) & noexcept>();
    test_is_const<void (class_type::*)(int) && noexcept>();
    test_is_const<void (class_type::*)(int) const noexcept>();
    test_is_const<void (class_type::*)(int) const & noexcept>();
    test_is_const<void (class_type::*)(int) const && noexcept>();

    test_is_const<void (class_type::*)(...)>();
    test_is_const<void (class_type::*)(...)&>();
    test_is_const<void (class_type::*)(...) &&>();
    test_is_const<void (class_type::*)(...) const>();
    test_is_const<void (class_type::*)(...) const&>();
    test_is_const<void (class_type::*)(...) const&&>();
    test_is_const<void (class_type::*)(...) noexcept>();
    test_is_const<void (class_type::*)(...) & noexcept>();
    test_is_const<void (class_type::*)(...) && noexcept>();
    test_is_const<void (class_type::*)(...) const noexcept>();
    test_is_const<void (class_type::*)(...) const & noexcept>();
    test_is_const<void (class_type::*)(...) const && noexcept>();

    test_is_const<void (class_type::*)(int, ...)>();
    test_is_const<void (class_type::*)(int, ...)&>();
    test_is_const<void (class_type::*)(int, ...) &&>();
    test_is_const<void (class_type::*)(int, ...) const>();
    test_is_const<void (class_type::*)(int, ...) const&>();
    test_is_const<void (class_type::*)(int, ...) const&&>();
    test_is_const<void (class_type::*)(int, ...) noexcept>();
    test_is_const<void (class_type::*)(int, ...) & noexcept>();
    test_is_const<void (class_type::*)(int, ...) && noexcept>();
    test_is_const<void (class_type::*)(int, ...) const noexcept>();
    test_is_const<void (class_type::*)(int, ...) const & noexcept>();
    test_is_const<void (class_type::*)(int, ...) const && noexcept>();

    test_is_const<int (class_type::*)()>();
    test_is_const<int (class_type::*)()&>();
    test_is_const<int (class_type::*)() &&>();
    test_is_const<int (class_type::*)() const>();
    test_is_const<int (class_type::*)() const&>();
    test_is_const<int (class_type::*)() const&&>();
    test_is_const<int (class_type::*)() noexcept>();
    test_is_const<int (class_type::*)() & noexcept>();
    test_is_const<int (class_type::*)() && noexcept>();
    test_is_const<int (class_type::*)() const noexcept>();
    test_is_const<int (class_type::*)() const & noexcept>();
    test_is_const<int (class_type::*)() const && noexcept>();

    test_is_const<int (class_type::*)(int)>();
    test_is_const<int (class_type::*)(int)&>();
    test_is_const<int (class_type::*)(int) &&>();
    test_is_const<int (class_type::*)(int) const>();
    test_is_const<int (class_type::*)(int) const&>();
    test_is_const<int (class_type::*)(int) const&&>();
    test_is_const<int (class_type::*)(int) noexcept>();
    test_is_const<int (class_type::*)(int) & noexcept>();
    test_is_const<int (class_type::*)(int) && noexcept>();
    test_is_const<int (class_type::*)(int) const noexcept>();
    test_is_const<int (class_type::*)(int) const & noexcept>();
    test_is_const<int (class_type::*)(int) const && noexcept>();

    test_is_const<int (class_type::*)(...)>();
    test_is_const<int (class_type::*)(...)&>();
    test_is_const<int (class_type::*)(...) &&>();
    test_is_const<int (class_type::*)(...) const>();
    test_is_const<int (class_type::*)(...) const&>();
    test_is_const<int (class_type::*)(...) const&&>();
    test_is_const<int (class_type::*)(...) noexcept>();
    test_is_const<int (class_type::*)(...) & noexcept>();
    test_is_const<int (class_type::*)(...) && noexcept>();
    test_is_const<int (class_type::*)(...) const noexcept>();
    test_is_const<int (class_type::*)(...) const & noexcept>();
    test_is_const<int (class_type::*)(...) const && noexcept>();

    test_is_const<int (class_type::*)(int, ...)>();
    test_is_const<int (class_type::*)(int, ...)&>();
    test_is_const<int (class_type::*)(int, ...) &&>();
    test_is_const<int (class_type::*)(int, ...) const>();
    test_is_const<int (class_type::*)(int, ...) const&>();
    test_is_const<int (class_type::*)(int, ...) const&&>();
    test_is_const<int (class_type::*)(int, ...) noexcept>();
    test_is_const<int (class_type::*)(int, ...) & noexcept>();
    test_is_const<int (class_type::*)(int, ...) && noexcept>();
    test_is_const<int (class_type::*)(int, ...) const noexcept>();
    test_is_const<int (class_type::*)(int, ...) const & noexcept>();
    test_is_const<int (class_type::*)(int, ...) const && noexcept>();
}
