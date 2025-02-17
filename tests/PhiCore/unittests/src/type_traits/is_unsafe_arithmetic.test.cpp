#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_unsafe_arithmetic.hpp>
#include <type_traits>
#include <vector>

template <typename TypeT>
void test_is_unsafe_arithmetic_impl()
{
    STATIC_REQUIRE(phi::is_unsafe_arithmetic<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_unsafe_arithmetic<TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_unsafe_arithmetic_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_not_unsafe_arithmetic_v<TypeT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_unsafe_arithmetic<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_unsafe_arithmetic<TypeT>);

    // Standard compatibility
    STATIC_REQUIRE(std::is_arithmetic<TypeT>::value);
}

template <typename TypeT>
void test_is_not_unsafe_arithmetic_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_unsafe_arithmetic<TypeT>::value);
    STATIC_REQUIRE(phi::is_not_unsafe_arithmetic<TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_unsafe_arithmetic_v<TypeT>);
    STATIC_REQUIRE(phi::is_not_unsafe_arithmetic_v<TypeT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_unsafe_arithmetic<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_unsafe_arithmetic<TypeT>);

    // Standard compatibility

    STATIC_REQUIRE_FALSE(std::is_arithmetic<TypeT>::value);
}

template <typename TypeT>
void test_is_unsafe_arithmetic()
{
    test_is_unsafe_arithmetic_impl<TypeT>();
    test_is_unsafe_arithmetic_impl<const TypeT>();
    test_is_unsafe_arithmetic_impl<volatile TypeT>();
    test_is_unsafe_arithmetic_impl<const volatile TypeT>();
}

template <typename TypeT>
void test_is_not_unsafe_arithmetic()
{
    test_is_not_unsafe_arithmetic_impl<TypeT>();
    test_is_not_unsafe_arithmetic_impl<const TypeT>();
    test_is_not_unsafe_arithmetic_impl<volatile TypeT>();
    test_is_not_unsafe_arithmetic_impl<const volatile TypeT>();
}

TEST_CASE("is_unsafe_arithmetic")
{
    test_is_not_unsafe_arithmetic<void>();
    test_is_not_unsafe_arithmetic<phi::nullptr_t>();
    test_is_unsafe_arithmetic<bool>();
    test_is_unsafe_arithmetic<char>();
    test_is_unsafe_arithmetic<signed char>();
    test_is_unsafe_arithmetic<unsigned char>();
    test_is_unsafe_arithmetic<short>();
    test_is_unsafe_arithmetic<unsigned short>();
    test_is_unsafe_arithmetic<int>();
    test_is_unsafe_arithmetic<unsigned int>();
    test_is_unsafe_arithmetic<long>();
    test_is_unsafe_arithmetic<unsigned long>();
    test_is_unsafe_arithmetic<long long>();
    test_is_unsafe_arithmetic<unsigned long long>();
    test_is_unsafe_arithmetic<float>();
    test_is_unsafe_arithmetic<double>();
    test_is_unsafe_arithmetic<long double>();
    test_is_unsafe_arithmetic<char8_t>();
    test_is_unsafe_arithmetic<char16_t>();
    test_is_unsafe_arithmetic<char32_t>();
    test_is_unsafe_arithmetic<wchar_t>();

    test_is_not_unsafe_arithmetic<phi::boolean>();
    test_is_not_unsafe_arithmetic<phi::integer<signed char>>();
    test_is_not_unsafe_arithmetic<phi::integer<unsigned char>>();
    test_is_not_unsafe_arithmetic<phi::integer<short>>();
    test_is_not_unsafe_arithmetic<phi::integer<unsigned short>>();
    test_is_not_unsafe_arithmetic<phi::integer<int>>();
    test_is_not_unsafe_arithmetic<phi::integer<unsigned int>>();
    test_is_not_unsafe_arithmetic<phi::integer<long>>();
    test_is_not_unsafe_arithmetic<phi::integer<unsigned long>>();
    test_is_not_unsafe_arithmetic<phi::integer<long long>>();
    test_is_not_unsafe_arithmetic<phi::integer<unsigned long long>>();
    test_is_not_unsafe_arithmetic<phi::floating_point<float>>();
    test_is_not_unsafe_arithmetic<phi::floating_point<double>>();
    test_is_not_unsafe_arithmetic<phi::floating_point<long double>>();

    test_is_not_unsafe_arithmetic<std::vector<int>>();
    test_is_not_unsafe_arithmetic<phi::scope_ptr<int>>();

    test_is_not_unsafe_arithmetic<int&>();
    test_is_not_unsafe_arithmetic<const int&>();
    test_is_not_unsafe_arithmetic<volatile int&>();
    test_is_not_unsafe_arithmetic<const volatile int&>();
    test_is_not_unsafe_arithmetic<int&&>();
    test_is_not_unsafe_arithmetic<const int&&>();
    test_is_not_unsafe_arithmetic<volatile int&&>();
    test_is_not_unsafe_arithmetic<const volatile int&&>();
    test_is_not_unsafe_arithmetic<int*>();
    test_is_not_unsafe_arithmetic<const int*>();
    test_is_not_unsafe_arithmetic<volatile int*>();
    test_is_not_unsafe_arithmetic<const volatile int*>();
    test_is_not_unsafe_arithmetic<int**>();
    test_is_not_unsafe_arithmetic<const int**>();
    test_is_not_unsafe_arithmetic<volatile int**>();
    test_is_not_unsafe_arithmetic<const volatile int**>();
    test_is_not_unsafe_arithmetic<int*&>();
    test_is_not_unsafe_arithmetic<const int*&>();
    test_is_not_unsafe_arithmetic<volatile int*&>();
    test_is_not_unsafe_arithmetic<const volatile int*&>();
    test_is_not_unsafe_arithmetic<int*&&>();
    test_is_not_unsafe_arithmetic<const int*&&>();
    test_is_not_unsafe_arithmetic<volatile int*&&>();
    test_is_not_unsafe_arithmetic<const volatile int*&&>();
    test_is_not_unsafe_arithmetic<void*>();
    test_is_not_unsafe_arithmetic<char[3]>();
    test_is_not_unsafe_arithmetic<char[]>();
    test_is_not_unsafe_arithmetic<char* [3]>();
    test_is_not_unsafe_arithmetic<char*[]>();
    test_is_not_unsafe_arithmetic<int(*)[3]>();
    test_is_not_unsafe_arithmetic<int(*)[]>();
    test_is_not_unsafe_arithmetic<int(&)[3]>();
    test_is_not_unsafe_arithmetic<int(&)[]>();
    test_is_not_unsafe_arithmetic<int(&&)[3]>();
    test_is_not_unsafe_arithmetic<int(&&)[]>();
    test_is_not_unsafe_arithmetic<char[3][2]>();
    test_is_not_unsafe_arithmetic<char[][2]>();
    test_is_not_unsafe_arithmetic<char* [3][2]>();
    test_is_not_unsafe_arithmetic<char*[][2]>();
    test_is_not_unsafe_arithmetic<int(*)[3][2]>();
    test_is_not_unsafe_arithmetic<int(*)[][2]>();
    test_is_not_unsafe_arithmetic<int(&)[3][2]>();
    test_is_not_unsafe_arithmetic<int(&)[][2]>();
    test_is_not_unsafe_arithmetic<int(&&)[3][2]>();
    test_is_not_unsafe_arithmetic<int(&&)[][2]>();
    test_is_not_unsafe_arithmetic<class_type>();
    test_is_not_unsafe_arithmetic<class_type[]>();
    test_is_not_unsafe_arithmetic<class_type[2]>();
    test_is_not_unsafe_arithmetic<template_type<void>>();
    test_is_not_unsafe_arithmetic<template_type<int>>();
    test_is_not_unsafe_arithmetic<template_type<class_type>>();
    test_is_not_unsafe_arithmetic<template_type<incomplete_type>>();
    test_is_not_unsafe_arithmetic<variadic_template<>>();
    test_is_not_unsafe_arithmetic<variadic_template<void>>();
    test_is_not_unsafe_arithmetic<variadic_template<int>>();
    test_is_not_unsafe_arithmetic<variadic_template<class_type>>();
    test_is_not_unsafe_arithmetic<variadic_template<incomplete_type>>();
    test_is_not_unsafe_arithmetic<variadic_template<int, void, class_type, volatile char[]>>();
    test_is_not_unsafe_arithmetic<public_derived_from<base>>();
    test_is_not_unsafe_arithmetic<public_derived_from<derived>>();
    test_is_not_unsafe_arithmetic<public_derived_from<class_type>>();
    test_is_not_unsafe_arithmetic<private_derived_from<base>>();
    test_is_not_unsafe_arithmetic<private_derived_from<derived>>();
    test_is_not_unsafe_arithmetic<private_derived_from<class_type>>();
    test_is_not_unsafe_arithmetic<protected_derived_from<base>>();
    test_is_not_unsafe_arithmetic<protected_derived_from<derived>>();
    test_is_not_unsafe_arithmetic<protected_derived_from<class_type>>();
    test_is_not_unsafe_arithmetic<union_type>();
    test_is_not_unsafe_arithmetic<non_empty_union>();
    test_is_not_unsafe_arithmetic<empty>();
    test_is_not_unsafe_arithmetic<not_empty>();
    test_is_not_unsafe_arithmetic<bit_zero>();
    test_is_not_unsafe_arithmetic<bit_one>();
    test_is_not_unsafe_arithmetic<base>();
    test_is_not_unsafe_arithmetic<derived>();
    test_is_not_unsafe_arithmetic<abstract>();
    test_is_not_unsafe_arithmetic<public_abstract>();
    test_is_not_unsafe_arithmetic<private_abstract>();
    test_is_not_unsafe_arithmetic<protected_abstract>();
    test_is_not_unsafe_arithmetic<abstract_template<int>>();
    test_is_not_unsafe_arithmetic<abstract_template<double>>();
    test_is_not_unsafe_arithmetic<abstract_template<class_type>>();
    test_is_not_unsafe_arithmetic<abstract_template<incomplete_type>>();
    test_is_not_unsafe_arithmetic<final_type>();
    test_is_not_unsafe_arithmetic<public_destructor>();
    test_is_not_unsafe_arithmetic<protected_destructor>();
    test_is_not_unsafe_arithmetic<private_destructor>();
    test_is_not_unsafe_arithmetic<virtual_public_destructor>();
    test_is_not_unsafe_arithmetic<virtual_protected_destructor>();
    test_is_not_unsafe_arithmetic<virtual_private_destructor>();
    test_is_not_unsafe_arithmetic<pure_public_destructor>();
    test_is_not_unsafe_arithmetic<pure_protected_destructor>();
    test_is_not_unsafe_arithmetic<pure_private_destructor>();
    test_is_not_unsafe_arithmetic<deleted_public_destructor>();
    test_is_not_unsafe_arithmetic<deleted_protected_destructor>();
    test_is_not_unsafe_arithmetic<deleted_private_destructor>();
    test_is_not_unsafe_arithmetic<deleted_virtual_public_destructor>();
    test_is_not_unsafe_arithmetic<deleted_virtual_protected_destructor>();
    test_is_not_unsafe_arithmetic<deleted_virtual_private_destructor>();
    test_is_not_unsafe_arithmetic<Enum>();
    test_is_not_unsafe_arithmetic<EnumSigned>();
    test_is_not_unsafe_arithmetic<EnumUnsigned>();
    test_is_not_unsafe_arithmetic<EnumClass>();
    test_is_not_unsafe_arithmetic<EnumStruct>();
    test_is_not_unsafe_arithmetic<function_type>();
    test_is_not_unsafe_arithmetic<function_ptr>();
    test_is_not_unsafe_arithmetic<member_object_ptr>();
    test_is_not_unsafe_arithmetic<member_function_ptr>();
    test_is_not_unsafe_arithmetic<incomplete_type>();
    test_is_not_unsafe_arithmetic<incomplete_template<void>>();
    test_is_not_unsafe_arithmetic<incomplete_template<int>>();
    test_is_not_unsafe_arithmetic<incomplete_template<class_type>>();
    test_is_not_unsafe_arithmetic<incomplete_template<incomplete_type>>();
    test_is_not_unsafe_arithmetic<incomplete_variadic_template<>>();
    test_is_not_unsafe_arithmetic<incomplete_variadic_template<void>>();
    test_is_not_unsafe_arithmetic<incomplete_variadic_template<int>>();
    test_is_not_unsafe_arithmetic<incomplete_variadic_template<class_type>>();
    test_is_not_unsafe_arithmetic<incomplete_variadic_template<incomplete_type>>();
    test_is_not_unsafe_arithmetic<
            incomplete_variadic_template<int, void, class_type, volatile char[]>>();
    test_is_not_unsafe_arithmetic<int class_type::*>();
    test_is_not_unsafe_arithmetic<float class_type::*>();
    test_is_not_unsafe_arithmetic<void * class_type::*>();
    test_is_not_unsafe_arithmetic<int * class_type::*>();
    test_is_not_unsafe_arithmetic<int class_type::*&>();
    test_is_not_unsafe_arithmetic<float class_type::*&>();
    test_is_not_unsafe_arithmetic<void * class_type::*&>();
    test_is_not_unsafe_arithmetic<int * class_type::*&>();
    test_is_not_unsafe_arithmetic<int class_type::*&&>();
    test_is_not_unsafe_arithmetic<float class_type::*&&>();
    test_is_not_unsafe_arithmetic<void * class_type::*&&>();
    test_is_not_unsafe_arithmetic<int * class_type::*&&>();
    test_is_not_unsafe_arithmetic<int class_type::* const>();
    test_is_not_unsafe_arithmetic<float class_type::* const>();
    test_is_not_unsafe_arithmetic<void * class_type::* const>();
    test_is_not_unsafe_arithmetic<int class_type::* const&>();
    test_is_not_unsafe_arithmetic<float class_type::* const&>();
    test_is_not_unsafe_arithmetic<void * class_type::* const&>();
    test_is_not_unsafe_arithmetic<int class_type::* const&&>();
    test_is_not_unsafe_arithmetic<float class_type::* const&&>();
    test_is_not_unsafe_arithmetic<void * class_type::* const&&>();
    test_is_not_unsafe_arithmetic<int class_type::* volatile>();
    test_is_not_unsafe_arithmetic<float class_type::* volatile>();
    test_is_not_unsafe_arithmetic<void * class_type::* volatile>();
    test_is_not_unsafe_arithmetic<int class_type::* volatile&>();
    test_is_not_unsafe_arithmetic<float class_type::* volatile&>();
    test_is_not_unsafe_arithmetic<void * class_type::* volatile&>();
    test_is_not_unsafe_arithmetic<int class_type::* volatile&&>();
    test_is_not_unsafe_arithmetic<float class_type::* volatile&&>();
    test_is_not_unsafe_arithmetic<void * class_type::* volatile&&>();
    test_is_not_unsafe_arithmetic<int class_type::* const volatile>();
    test_is_not_unsafe_arithmetic<float class_type::* const volatile>();
    test_is_not_unsafe_arithmetic<void * class_type::* const volatile>();
    test_is_not_unsafe_arithmetic<int class_type::* const volatile&>();
    test_is_not_unsafe_arithmetic<float class_type::* const volatile&>();
    test_is_not_unsafe_arithmetic<void * class_type::* const volatile&>();
    test_is_not_unsafe_arithmetic<int class_type::* const volatile&&>();
    test_is_not_unsafe_arithmetic<float class_type::* const volatile&&>();
    test_is_not_unsafe_arithmetic<void * class_type::* const volatile&&>();
    test_is_not_unsafe_arithmetic<non_copyable>();
    test_is_not_unsafe_arithmetic<non_moveable>();
    test_is_not_unsafe_arithmetic<non_constructible>();
    test_is_not_unsafe_arithmetic<tracked>();
    test_is_not_unsafe_arithmetic<trap_constructible>();
    test_is_not_unsafe_arithmetic<trap_implicit_conversion>();
    test_is_not_unsafe_arithmetic<trap_comma>();
    test_is_not_unsafe_arithmetic<trap_call>();
    test_is_not_unsafe_arithmetic<trap_self_assign>();
    test_is_not_unsafe_arithmetic<trap_deref>();
    test_is_not_unsafe_arithmetic<trap_array_subscript>();

    test_is_not_unsafe_arithmetic<void()>();
    test_is_not_unsafe_arithmetic<void()&>();
    test_is_not_unsafe_arithmetic<void() &&>();
    test_is_not_unsafe_arithmetic<void() const>();
    test_is_not_unsafe_arithmetic<void() const&>();
    test_is_not_unsafe_arithmetic<void() const&&>();
    test_is_not_unsafe_arithmetic<void() volatile>();
    test_is_not_unsafe_arithmetic<void() volatile&>();
    test_is_not_unsafe_arithmetic<void() volatile&&>();
    test_is_not_unsafe_arithmetic<void() const volatile>();
    test_is_not_unsafe_arithmetic<void() const volatile&>();
    test_is_not_unsafe_arithmetic<void() const volatile&&>();
    test_is_not_unsafe_arithmetic<void() noexcept>();
    test_is_not_unsafe_arithmetic<void() & noexcept>();
    test_is_not_unsafe_arithmetic<void() && noexcept>();
    test_is_not_unsafe_arithmetic<void() const noexcept>();
    test_is_not_unsafe_arithmetic<void() const & noexcept>();
    test_is_not_unsafe_arithmetic<void() const && noexcept>();
    test_is_not_unsafe_arithmetic<void() volatile noexcept>();
    test_is_not_unsafe_arithmetic<void() volatile & noexcept>();
    test_is_not_unsafe_arithmetic<void() volatile && noexcept>();
    test_is_not_unsafe_arithmetic<void() const volatile noexcept>();
    test_is_not_unsafe_arithmetic<void() const volatile & noexcept>();
    test_is_not_unsafe_arithmetic<void() const volatile && noexcept>();

    test_is_not_unsafe_arithmetic<void(int)>();
    test_is_not_unsafe_arithmetic<void(int)&>();
    test_is_not_unsafe_arithmetic<void(int) &&>();
    test_is_not_unsafe_arithmetic<void(int) const>();
    test_is_not_unsafe_arithmetic<void(int) const&>();
    test_is_not_unsafe_arithmetic<void(int) const&&>();
    test_is_not_unsafe_arithmetic<void(int) volatile>();
    test_is_not_unsafe_arithmetic<void(int) volatile&>();
    test_is_not_unsafe_arithmetic<void(int) volatile&&>();
    test_is_not_unsafe_arithmetic<void(int) const volatile>();
    test_is_not_unsafe_arithmetic<void(int) const volatile&>();
    test_is_not_unsafe_arithmetic<void(int) const volatile&&>();
    test_is_not_unsafe_arithmetic<void(int) noexcept>();
    test_is_not_unsafe_arithmetic<void(int) & noexcept>();
    test_is_not_unsafe_arithmetic<void(int) && noexcept>();
    test_is_not_unsafe_arithmetic<void(int) const noexcept>();
    test_is_not_unsafe_arithmetic<void(int) const & noexcept>();
    test_is_not_unsafe_arithmetic<void(int) const && noexcept>();
    test_is_not_unsafe_arithmetic<void(int) volatile noexcept>();
    test_is_not_unsafe_arithmetic<void(int) volatile & noexcept>();
    test_is_not_unsafe_arithmetic<void(int) volatile && noexcept>();
    test_is_not_unsafe_arithmetic<void(int) const volatile noexcept>();
    test_is_not_unsafe_arithmetic<void(int) const volatile & noexcept>();
    test_is_not_unsafe_arithmetic<void(int) const volatile && noexcept>();

    test_is_not_unsafe_arithmetic<void(...)>();
    test_is_not_unsafe_arithmetic<void(...)&>();
    test_is_not_unsafe_arithmetic<void(...) &&>();
    test_is_not_unsafe_arithmetic<void(...) const>();
    test_is_not_unsafe_arithmetic<void(...) const&>();
    test_is_not_unsafe_arithmetic<void(...) const&&>();
    test_is_not_unsafe_arithmetic<void(...) volatile>();
    test_is_not_unsafe_arithmetic<void(...) volatile&>();
    test_is_not_unsafe_arithmetic<void(...) volatile&&>();
    test_is_not_unsafe_arithmetic<void(...) const volatile>();
    test_is_not_unsafe_arithmetic<void(...) const volatile&>();
    test_is_not_unsafe_arithmetic<void(...) const volatile&&>();
    test_is_not_unsafe_arithmetic<void(...) noexcept>();
    test_is_not_unsafe_arithmetic<void(...) & noexcept>();
    test_is_not_unsafe_arithmetic<void(...) && noexcept>();
    test_is_not_unsafe_arithmetic<void(...) const noexcept>();
    test_is_not_unsafe_arithmetic<void(...) const & noexcept>();
    test_is_not_unsafe_arithmetic<void(...) const && noexcept>();
    test_is_not_unsafe_arithmetic<void(...) volatile noexcept>();
    test_is_not_unsafe_arithmetic<void(...) volatile & noexcept>();
    test_is_not_unsafe_arithmetic<void(...) volatile && noexcept>();
    test_is_not_unsafe_arithmetic<void(...) const volatile noexcept>();
    test_is_not_unsafe_arithmetic<void(...) const volatile & noexcept>();
    test_is_not_unsafe_arithmetic<void(...) const volatile && noexcept>();

    test_is_not_unsafe_arithmetic<void(int, ...)>();
    test_is_not_unsafe_arithmetic<void(int, ...)&>();
    test_is_not_unsafe_arithmetic<void(int, ...) &&>();
    test_is_not_unsafe_arithmetic<void(int, ...) const>();
    test_is_not_unsafe_arithmetic<void(int, ...) const&>();
    test_is_not_unsafe_arithmetic<void(int, ...) const&&>();
    test_is_not_unsafe_arithmetic<void(int, ...) volatile>();
    test_is_not_unsafe_arithmetic<void(int, ...) volatile&>();
    test_is_not_unsafe_arithmetic<void(int, ...) volatile&&>();
    test_is_not_unsafe_arithmetic<void(int, ...) const volatile>();
    test_is_not_unsafe_arithmetic<void(int, ...) const volatile&>();
    test_is_not_unsafe_arithmetic<void(int, ...) const volatile&&>();
    test_is_not_unsafe_arithmetic<void(int, ...) noexcept>();
    test_is_not_unsafe_arithmetic<void(int, ...) & noexcept>();
    test_is_not_unsafe_arithmetic<void(int, ...) && noexcept>();
    test_is_not_unsafe_arithmetic<void(int, ...) const noexcept>();
    test_is_not_unsafe_arithmetic<void(int, ...) const & noexcept>();
    test_is_not_unsafe_arithmetic<void(int, ...) const && noexcept>();
    test_is_not_unsafe_arithmetic<void(int, ...) volatile noexcept>();
    test_is_not_unsafe_arithmetic<void(int, ...) volatile & noexcept>();
    test_is_not_unsafe_arithmetic<void(int, ...) volatile && noexcept>();
    test_is_not_unsafe_arithmetic<void(int, ...) const volatile noexcept>();
    test_is_not_unsafe_arithmetic<void(int, ...) const volatile & noexcept>();
    test_is_not_unsafe_arithmetic<void(int, ...) const volatile && noexcept>();

    test_is_not_unsafe_arithmetic<int()>();
    test_is_not_unsafe_arithmetic<int()&>();
    test_is_not_unsafe_arithmetic<int() &&>();
    test_is_not_unsafe_arithmetic<int() const>();
    test_is_not_unsafe_arithmetic<int() const&>();
    test_is_not_unsafe_arithmetic<int() const&&>();
    test_is_not_unsafe_arithmetic<int() volatile>();
    test_is_not_unsafe_arithmetic<int() volatile&>();
    test_is_not_unsafe_arithmetic<int() volatile&&>();
    test_is_not_unsafe_arithmetic<int() const volatile>();
    test_is_not_unsafe_arithmetic<int() const volatile&>();
    test_is_not_unsafe_arithmetic<int() const volatile&&>();
    test_is_not_unsafe_arithmetic<int() noexcept>();
    test_is_not_unsafe_arithmetic<int() & noexcept>();
    test_is_not_unsafe_arithmetic<int() && noexcept>();
    test_is_not_unsafe_arithmetic<int() const noexcept>();
    test_is_not_unsafe_arithmetic<int() const & noexcept>();
    test_is_not_unsafe_arithmetic<int() const && noexcept>();
    test_is_not_unsafe_arithmetic<int() volatile noexcept>();
    test_is_not_unsafe_arithmetic<int() volatile & noexcept>();
    test_is_not_unsafe_arithmetic<int() volatile && noexcept>();
    test_is_not_unsafe_arithmetic<int() const volatile noexcept>();
    test_is_not_unsafe_arithmetic<int() const volatile & noexcept>();
    test_is_not_unsafe_arithmetic<int() const volatile && noexcept>();

    test_is_not_unsafe_arithmetic<int(int)>();
    test_is_not_unsafe_arithmetic<int(int)&>();
    test_is_not_unsafe_arithmetic<int(int) &&>();
    test_is_not_unsafe_arithmetic<int(int) const>();
    test_is_not_unsafe_arithmetic<int(int) const&>();
    test_is_not_unsafe_arithmetic<int(int) const&&>();
    test_is_not_unsafe_arithmetic<int(int) volatile>();
    test_is_not_unsafe_arithmetic<int(int) volatile&>();
    test_is_not_unsafe_arithmetic<int(int) volatile&&>();
    test_is_not_unsafe_arithmetic<int(int) const volatile>();
    test_is_not_unsafe_arithmetic<int(int) const volatile&>();
    test_is_not_unsafe_arithmetic<int(int) const volatile&&>();
    test_is_not_unsafe_arithmetic<int(int) noexcept>();
    test_is_not_unsafe_arithmetic<int(int) & noexcept>();
    test_is_not_unsafe_arithmetic<int(int) && noexcept>();
    test_is_not_unsafe_arithmetic<int(int) const noexcept>();
    test_is_not_unsafe_arithmetic<int(int) const & noexcept>();
    test_is_not_unsafe_arithmetic<int(int) const && noexcept>();
    test_is_not_unsafe_arithmetic<int(int) volatile noexcept>();
    test_is_not_unsafe_arithmetic<int(int) volatile & noexcept>();
    test_is_not_unsafe_arithmetic<int(int) volatile && noexcept>();
    test_is_not_unsafe_arithmetic<int(int) const volatile noexcept>();
    test_is_not_unsafe_arithmetic<int(int) const volatile & noexcept>();
    test_is_not_unsafe_arithmetic<int(int) const volatile && noexcept>();

    test_is_not_unsafe_arithmetic<int(...)>();
    test_is_not_unsafe_arithmetic<int(...)&>();
    test_is_not_unsafe_arithmetic<int(...) &&>();
    test_is_not_unsafe_arithmetic<int(...) const>();
    test_is_not_unsafe_arithmetic<int(...) const&>();
    test_is_not_unsafe_arithmetic<int(...) const&&>();
    test_is_not_unsafe_arithmetic<int(...) volatile>();
    test_is_not_unsafe_arithmetic<int(...) volatile&>();
    test_is_not_unsafe_arithmetic<int(...) volatile&&>();
    test_is_not_unsafe_arithmetic<int(...) const volatile>();
    test_is_not_unsafe_arithmetic<int(...) const volatile&>();
    test_is_not_unsafe_arithmetic<int(...) const volatile&&>();
    test_is_not_unsafe_arithmetic<int(...) noexcept>();
    test_is_not_unsafe_arithmetic<int(...) & noexcept>();
    test_is_not_unsafe_arithmetic<int(...) && noexcept>();
    test_is_not_unsafe_arithmetic<int(...) const noexcept>();
    test_is_not_unsafe_arithmetic<int(...) const & noexcept>();
    test_is_not_unsafe_arithmetic<int(...) const && noexcept>();
    test_is_not_unsafe_arithmetic<int(...) volatile noexcept>();
    test_is_not_unsafe_arithmetic<int(...) volatile & noexcept>();
    test_is_not_unsafe_arithmetic<int(...) volatile && noexcept>();
    test_is_not_unsafe_arithmetic<int(...) const volatile noexcept>();
    test_is_not_unsafe_arithmetic<int(...) const volatile & noexcept>();
    test_is_not_unsafe_arithmetic<int(...) const volatile && noexcept>();

    test_is_not_unsafe_arithmetic<int(int, ...)>();
    test_is_not_unsafe_arithmetic<int(int, ...)&>();
    test_is_not_unsafe_arithmetic<int(int, ...) &&>();
    test_is_not_unsafe_arithmetic<int(int, ...) const>();
    test_is_not_unsafe_arithmetic<int(int, ...) const&>();
    test_is_not_unsafe_arithmetic<int(int, ...) const&&>();
    test_is_not_unsafe_arithmetic<int(int, ...) volatile>();
    test_is_not_unsafe_arithmetic<int(int, ...) volatile&>();
    test_is_not_unsafe_arithmetic<int(int, ...) volatile&&>();
    test_is_not_unsafe_arithmetic<int(int, ...) const volatile>();
    test_is_not_unsafe_arithmetic<int(int, ...) const volatile&>();
    test_is_not_unsafe_arithmetic<int(int, ...) const volatile&&>();
    test_is_not_unsafe_arithmetic<int(int, ...) noexcept>();
    test_is_not_unsafe_arithmetic<int(int, ...) & noexcept>();
    test_is_not_unsafe_arithmetic<int(int, ...) && noexcept>();
    test_is_not_unsafe_arithmetic<int(int, ...) const noexcept>();
    test_is_not_unsafe_arithmetic<int(int, ...) const & noexcept>();
    test_is_not_unsafe_arithmetic<int(int, ...) const && noexcept>();
    test_is_not_unsafe_arithmetic<int(int, ...) volatile noexcept>();
    test_is_not_unsafe_arithmetic<int(int, ...) volatile & noexcept>();
    test_is_not_unsafe_arithmetic<int(int, ...) volatile && noexcept>();
    test_is_not_unsafe_arithmetic<int(int, ...) const volatile noexcept>();
    test_is_not_unsafe_arithmetic<int(int, ...) const volatile & noexcept>();
    test_is_not_unsafe_arithmetic<int(int, ...) const volatile && noexcept>();

    test_is_not_unsafe_arithmetic<void (*)()>();
    test_is_not_unsafe_arithmetic<void (*)() noexcept>();

    test_is_not_unsafe_arithmetic<void (*)(int)>();
    test_is_not_unsafe_arithmetic<void (*)(int) noexcept>();

    test_is_not_unsafe_arithmetic<void (*)(...)>();
    test_is_not_unsafe_arithmetic<void (*)(...) noexcept>();

    test_is_not_unsafe_arithmetic<void (*)(int, ...)>();
    test_is_not_unsafe_arithmetic<void (*)(int, ...) noexcept>();

    test_is_not_unsafe_arithmetic<int (*)()>();
    test_is_not_unsafe_arithmetic<int (*)() noexcept>();

    test_is_not_unsafe_arithmetic<int (*)(int)>();
    test_is_not_unsafe_arithmetic<int (*)(int) noexcept>();

    test_is_not_unsafe_arithmetic<int (*)(...)>();
    test_is_not_unsafe_arithmetic<int (*)(...) noexcept>();

    test_is_not_unsafe_arithmetic<int (*)(int, ...)>();
    test_is_not_unsafe_arithmetic<int (*)(int, ...) noexcept>();

    test_is_not_unsafe_arithmetic<void (&)()>();
    test_is_not_unsafe_arithmetic<void (&)() noexcept>();

    test_is_not_unsafe_arithmetic<void (&)(int)>();
    test_is_not_unsafe_arithmetic<void (&)(int) noexcept>();

    test_is_not_unsafe_arithmetic<void (&)(...)>();
    test_is_not_unsafe_arithmetic<void (&)(...) noexcept>();

    test_is_not_unsafe_arithmetic<void (&)(int, ...)>();
    test_is_not_unsafe_arithmetic<void (&)(int, ...) noexcept>();

    test_is_not_unsafe_arithmetic<int (&)()>();
    test_is_not_unsafe_arithmetic<int (&)() noexcept>();

    test_is_not_unsafe_arithmetic<int (&)(int)>();
    test_is_not_unsafe_arithmetic<int (&)(int) noexcept>();

    test_is_not_unsafe_arithmetic<int (&)(...)>();
    test_is_not_unsafe_arithmetic<int (&)(...) noexcept>();

    test_is_not_unsafe_arithmetic<int (&)(int, ...)>();
    test_is_not_unsafe_arithmetic<int (&)(int, ...) noexcept>();

    test_is_not_unsafe_arithmetic<void (&&)()>();
    test_is_not_unsafe_arithmetic<void (&&)() noexcept>();

    test_is_not_unsafe_arithmetic<void (&&)(int)>();
    test_is_not_unsafe_arithmetic<void (&&)(int) noexcept>();

    test_is_not_unsafe_arithmetic<void (&&)(...)>();
    test_is_not_unsafe_arithmetic<void (&&)(...) noexcept>();

    test_is_not_unsafe_arithmetic<void (&&)(int, ...)>();
    test_is_not_unsafe_arithmetic<void (&&)(int, ...) noexcept>();

    test_is_not_unsafe_arithmetic<int (&&)()>();
    test_is_not_unsafe_arithmetic<int (&&)() noexcept>();

    test_is_not_unsafe_arithmetic<int (&&)(int)>();
    test_is_not_unsafe_arithmetic<int (&&)(int) noexcept>();

    test_is_not_unsafe_arithmetic<int (&&)(...)>();
    test_is_not_unsafe_arithmetic<int (&&)(...) noexcept>();

    test_is_not_unsafe_arithmetic<int (&&)(int, ...)>();
    test_is_not_unsafe_arithmetic<int (&&)(int, ...) noexcept>();

    test_is_not_unsafe_arithmetic<void (class_type::*)()>();
    test_is_not_unsafe_arithmetic<void (class_type::*)()&>();
    test_is_not_unsafe_arithmetic<void (class_type::*)() &&>();
    test_is_not_unsafe_arithmetic<void (class_type::*)() const>();
    test_is_not_unsafe_arithmetic<void (class_type::*)() const&>();
    test_is_not_unsafe_arithmetic<void (class_type::*)() const&&>();
    test_is_not_unsafe_arithmetic<void (class_type::*)() noexcept>();
    test_is_not_unsafe_arithmetic<void (class_type::*)() & noexcept>();
    test_is_not_unsafe_arithmetic<void (class_type::*)() && noexcept>();
    test_is_not_unsafe_arithmetic<void (class_type::*)() const noexcept>();
    test_is_not_unsafe_arithmetic<void (class_type::*)() const & noexcept>();
    test_is_not_unsafe_arithmetic<void (class_type::*)() const && noexcept>();

    test_is_not_unsafe_arithmetic<void (class_type::*)(int)>();
    test_is_not_unsafe_arithmetic<void (class_type::*)(int)&>();
    test_is_not_unsafe_arithmetic<void (class_type::*)(int) &&>();
    test_is_not_unsafe_arithmetic<void (class_type::*)(int) const>();
    test_is_not_unsafe_arithmetic<void (class_type::*)(int) const&>();
    test_is_not_unsafe_arithmetic<void (class_type::*)(int) const&&>();
    test_is_not_unsafe_arithmetic<void (class_type::*)(int) noexcept>();
    test_is_not_unsafe_arithmetic<void (class_type::*)(int) & noexcept>();
    test_is_not_unsafe_arithmetic<void (class_type::*)(int) && noexcept>();
    test_is_not_unsafe_arithmetic<void (class_type::*)(int) const noexcept>();
    test_is_not_unsafe_arithmetic<void (class_type::*)(int) const & noexcept>();
    test_is_not_unsafe_arithmetic<void (class_type::*)(int) const && noexcept>();

    test_is_not_unsafe_arithmetic<void (class_type::*)(...)>();
    test_is_not_unsafe_arithmetic<void (class_type::*)(...)&>();
    test_is_not_unsafe_arithmetic<void (class_type::*)(...) &&>();
    test_is_not_unsafe_arithmetic<void (class_type::*)(...) const>();
    test_is_not_unsafe_arithmetic<void (class_type::*)(...) const&>();
    test_is_not_unsafe_arithmetic<void (class_type::*)(...) const&&>();
    test_is_not_unsafe_arithmetic<void (class_type::*)(...) noexcept>();
    test_is_not_unsafe_arithmetic<void (class_type::*)(...) & noexcept>();
    test_is_not_unsafe_arithmetic<void (class_type::*)(...) && noexcept>();
    test_is_not_unsafe_arithmetic<void (class_type::*)(...) const noexcept>();
    test_is_not_unsafe_arithmetic<void (class_type::*)(...) const & noexcept>();
    test_is_not_unsafe_arithmetic<void (class_type::*)(...) const && noexcept>();

    test_is_not_unsafe_arithmetic<void (class_type::*)(int, ...)>();
    test_is_not_unsafe_arithmetic<void (class_type::*)(int, ...)&>();
    test_is_not_unsafe_arithmetic<void (class_type::*)(int, ...) &&>();
    test_is_not_unsafe_arithmetic<void (class_type::*)(int, ...) const>();
    test_is_not_unsafe_arithmetic<void (class_type::*)(int, ...) const&>();
    test_is_not_unsafe_arithmetic<void (class_type::*)(int, ...) const&&>();
    test_is_not_unsafe_arithmetic<void (class_type::*)(int, ...) noexcept>();
    test_is_not_unsafe_arithmetic<void (class_type::*)(int, ...) & noexcept>();
    test_is_not_unsafe_arithmetic<void (class_type::*)(int, ...) && noexcept>();
    test_is_not_unsafe_arithmetic<void (class_type::*)(int, ...) const noexcept>();
    test_is_not_unsafe_arithmetic<void (class_type::*)(int, ...) const & noexcept>();
    test_is_not_unsafe_arithmetic<void (class_type::*)(int, ...) const && noexcept>();

    test_is_not_unsafe_arithmetic<int (class_type::*)()>();
    test_is_not_unsafe_arithmetic<int (class_type::*)()&>();
    test_is_not_unsafe_arithmetic<int (class_type::*)() &&>();
    test_is_not_unsafe_arithmetic<int (class_type::*)() const>();
    test_is_not_unsafe_arithmetic<int (class_type::*)() const&>();
    test_is_not_unsafe_arithmetic<int (class_type::*)() const&&>();
    test_is_not_unsafe_arithmetic<int (class_type::*)() noexcept>();
    test_is_not_unsafe_arithmetic<int (class_type::*)() & noexcept>();
    test_is_not_unsafe_arithmetic<int (class_type::*)() && noexcept>();
    test_is_not_unsafe_arithmetic<int (class_type::*)() const noexcept>();
    test_is_not_unsafe_arithmetic<int (class_type::*)() const & noexcept>();
    test_is_not_unsafe_arithmetic<int (class_type::*)() const && noexcept>();

    test_is_not_unsafe_arithmetic<int (class_type::*)(int)>();
    test_is_not_unsafe_arithmetic<int (class_type::*)(int)&>();
    test_is_not_unsafe_arithmetic<int (class_type::*)(int) &&>();
    test_is_not_unsafe_arithmetic<int (class_type::*)(int) const>();
    test_is_not_unsafe_arithmetic<int (class_type::*)(int) const&>();
    test_is_not_unsafe_arithmetic<int (class_type::*)(int) const&&>();
    test_is_not_unsafe_arithmetic<int (class_type::*)(int) noexcept>();
    test_is_not_unsafe_arithmetic<int (class_type::*)(int) & noexcept>();
    test_is_not_unsafe_arithmetic<int (class_type::*)(int) && noexcept>();
    test_is_not_unsafe_arithmetic<int (class_type::*)(int) const noexcept>();
    test_is_not_unsafe_arithmetic<int (class_type::*)(int) const & noexcept>();
    test_is_not_unsafe_arithmetic<int (class_type::*)(int) const && noexcept>();

    test_is_not_unsafe_arithmetic<int (class_type::*)(...)>();
    test_is_not_unsafe_arithmetic<int (class_type::*)(...)&>();
    test_is_not_unsafe_arithmetic<int (class_type::*)(...) &&>();
    test_is_not_unsafe_arithmetic<int (class_type::*)(...) const>();
    test_is_not_unsafe_arithmetic<int (class_type::*)(...) const&>();
    test_is_not_unsafe_arithmetic<int (class_type::*)(...) const&&>();
    test_is_not_unsafe_arithmetic<int (class_type::*)(...) noexcept>();
    test_is_not_unsafe_arithmetic<int (class_type::*)(...) & noexcept>();
    test_is_not_unsafe_arithmetic<int (class_type::*)(...) && noexcept>();
    test_is_not_unsafe_arithmetic<int (class_type::*)(...) const noexcept>();
    test_is_not_unsafe_arithmetic<int (class_type::*)(...) const & noexcept>();
    test_is_not_unsafe_arithmetic<int (class_type::*)(...) const && noexcept>();

    test_is_not_unsafe_arithmetic<int (class_type::*)(int, ...)>();
    test_is_not_unsafe_arithmetic<int (class_type::*)(int, ...)&>();
    test_is_not_unsafe_arithmetic<int (class_type::*)(int, ...) &&>();
    test_is_not_unsafe_arithmetic<int (class_type::*)(int, ...) const>();
    test_is_not_unsafe_arithmetic<int (class_type::*)(int, ...) const&>();
    test_is_not_unsafe_arithmetic<int (class_type::*)(int, ...) const&&>();
    test_is_not_unsafe_arithmetic<int (class_type::*)(int, ...) noexcept>();
    test_is_not_unsafe_arithmetic<int (class_type::*)(int, ...) & noexcept>();
    test_is_not_unsafe_arithmetic<int (class_type::*)(int, ...) && noexcept>();
    test_is_not_unsafe_arithmetic<int (class_type::*)(int, ...) const noexcept>();
    test_is_not_unsafe_arithmetic<int (class_type::*)(int, ...) const & noexcept>();
    test_is_not_unsafe_arithmetic<int (class_type::*)(int, ...) const && noexcept>();
}
