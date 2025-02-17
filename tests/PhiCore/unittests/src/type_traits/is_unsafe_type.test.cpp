#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_unsafe_type.hpp>
#include <vector>

template <typename TypeT>
void test_is_unsafe_type_impl()
{
    STATIC_REQUIRE(phi::is_unsafe_type<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_unsafe_type<TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_unsafe_type_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_not_unsafe_type_v<TypeT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_unsafe_type<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_unsafe_type<TypeT>);
}

template <typename TypeT>
void test_is_not_unsafe_type_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_unsafe_type<TypeT>::value);
    STATIC_REQUIRE(phi::is_not_unsafe_type<TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_unsafe_type_v<TypeT>);
    STATIC_REQUIRE(phi::is_not_unsafe_type_v<TypeT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_unsafe_type<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_unsafe_type<TypeT>);
}

template <typename TypeT>
void test_is_unsafe_type()
{
    test_is_unsafe_type_impl<TypeT>();
    test_is_unsafe_type_impl<const TypeT>();
    test_is_unsafe_type_impl<volatile TypeT>();
    test_is_unsafe_type_impl<const volatile TypeT>();
}

template <typename TypeT>
void test_is_not_unsafe_type()
{
    test_is_not_unsafe_type_impl<TypeT>();
    test_is_not_unsafe_type_impl<const TypeT>();
    test_is_not_unsafe_type_impl<volatile TypeT>();
    test_is_not_unsafe_type_impl<const volatile TypeT>();
}

TEST_CASE("is_unsafe_type")
{
    test_is_not_unsafe_type<void>();
    test_is_not_unsafe_type<phi::nullptr_t>();
    test_is_unsafe_type<bool>();
    test_is_not_unsafe_type<char>();
    test_is_unsafe_type<signed char>();
    test_is_unsafe_type<unsigned char>();
    test_is_unsafe_type<short>();
    test_is_unsafe_type<unsigned short>();
    test_is_unsafe_type<int>();
    test_is_unsafe_type<unsigned int>();
    test_is_unsafe_type<long>();
    test_is_unsafe_type<unsigned long>();
    test_is_unsafe_type<long long>();
    test_is_unsafe_type<unsigned long long>();
    test_is_unsafe_type<float>();
    test_is_unsafe_type<double>();
    test_is_unsafe_type<long double>();
#if PHI_HAS_FEATURE_CHAR8_T()
    test_is_not_unsafe_type<char8_t>();
#endif
    test_is_not_unsafe_type<char16_t>();
    test_is_not_unsafe_type<char32_t>();
    test_is_not_unsafe_type<wchar_t>();

    test_is_not_unsafe_type<phi::boolean>();
    test_is_not_unsafe_type<phi::integer<signed char>>();
    test_is_not_unsafe_type<phi::integer<unsigned char>>();
    test_is_not_unsafe_type<phi::integer<short>>();
    test_is_not_unsafe_type<phi::integer<unsigned short>>();
    test_is_not_unsafe_type<phi::integer<int>>();
    test_is_not_unsafe_type<phi::integer<unsigned int>>();
    test_is_not_unsafe_type<phi::integer<long>>();
    test_is_not_unsafe_type<phi::integer<unsigned long>>();
    test_is_not_unsafe_type<phi::integer<long long>>();
    test_is_not_unsafe_type<phi::integer<unsigned long long>>();
    test_is_not_unsafe_type<phi::floating_point<float>>();
    test_is_not_unsafe_type<phi::floating_point<double>>();
    test_is_not_unsafe_type<phi::floating_point<long double>>();

    test_is_not_unsafe_type<std::vector<int>>();
    test_is_not_unsafe_type<phi::scope_ptr<int>>();

    test_is_not_unsafe_type<int&>();
    test_is_not_unsafe_type<const int&>();
    test_is_not_unsafe_type<volatile int&>();
    test_is_not_unsafe_type<const volatile int&>();
    test_is_not_unsafe_type<int&&>();
    test_is_not_unsafe_type<const int&&>();
    test_is_not_unsafe_type<volatile int&&>();
    test_is_not_unsafe_type<const volatile int&&>();
    test_is_not_unsafe_type<int*>();
    test_is_not_unsafe_type<const int*>();
    test_is_not_unsafe_type<volatile int*>();
    test_is_not_unsafe_type<const volatile int*>();
    test_is_not_unsafe_type<int**>();
    test_is_not_unsafe_type<const int**>();
    test_is_not_unsafe_type<volatile int**>();
    test_is_not_unsafe_type<const volatile int**>();
    test_is_not_unsafe_type<int*&>();
    test_is_not_unsafe_type<const int*&>();
    test_is_not_unsafe_type<volatile int*&>();
    test_is_not_unsafe_type<const volatile int*&>();
    test_is_not_unsafe_type<int*&&>();
    test_is_not_unsafe_type<const int*&&>();
    test_is_not_unsafe_type<volatile int*&&>();
    test_is_not_unsafe_type<const volatile int*&&>();
    test_is_not_unsafe_type<void*>();
    test_is_not_unsafe_type<char[3]>();
    test_is_not_unsafe_type<char[]>();
    test_is_not_unsafe_type<char* [3]>();
    test_is_not_unsafe_type<char*[]>();
    test_is_not_unsafe_type<int(*)[3]>();
    test_is_not_unsafe_type<int(*)[]>();
    test_is_not_unsafe_type<int(&)[3]>();
    test_is_not_unsafe_type<int(&)[]>();
    test_is_not_unsafe_type<int(&&)[3]>();
    test_is_not_unsafe_type<int(&&)[]>();
    test_is_not_unsafe_type<char[3][2]>();
    test_is_not_unsafe_type<char[][2]>();
    test_is_not_unsafe_type<char* [3][2]>();
    test_is_not_unsafe_type<char*[][2]>();
    test_is_not_unsafe_type<int(*)[3][2]>();
    test_is_not_unsafe_type<int(*)[][2]>();
    test_is_not_unsafe_type<int(&)[3][2]>();
    test_is_not_unsafe_type<int(&)[][2]>();
    test_is_not_unsafe_type<int(&&)[3][2]>();
    test_is_not_unsafe_type<int(&&)[][2]>();
    test_is_not_unsafe_type<class_type>();
    test_is_not_unsafe_type<class_type[]>();
    test_is_not_unsafe_type<class_type[2]>();
    test_is_not_unsafe_type<template_type<void>>();
    test_is_not_unsafe_type<template_type<int>>();
    test_is_not_unsafe_type<template_type<class_type>>();
    test_is_not_unsafe_type<template_type<incomplete_type>>();
    test_is_not_unsafe_type<variadic_template<>>();
    test_is_not_unsafe_type<variadic_template<void>>();
    test_is_not_unsafe_type<variadic_template<int>>();
    test_is_not_unsafe_type<variadic_template<class_type>>();
    test_is_not_unsafe_type<variadic_template<incomplete_type>>();
    test_is_not_unsafe_type<variadic_template<int, void, class_type, volatile char[]>>();
    test_is_not_unsafe_type<public_derived_from<base>>();
    test_is_not_unsafe_type<public_derived_from<derived>>();
    test_is_not_unsafe_type<public_derived_from<class_type>>();
    test_is_not_unsafe_type<private_derived_from<base>>();
    test_is_not_unsafe_type<private_derived_from<derived>>();
    test_is_not_unsafe_type<private_derived_from<class_type>>();
    test_is_not_unsafe_type<protected_derived_from<base>>();
    test_is_not_unsafe_type<protected_derived_from<derived>>();
    test_is_not_unsafe_type<protected_derived_from<class_type>>();
    test_is_not_unsafe_type<union_type>();
    test_is_not_unsafe_type<non_empty_union>();
    test_is_not_unsafe_type<empty>();
    test_is_not_unsafe_type<not_empty>();
    test_is_not_unsafe_type<bit_zero>();
    test_is_not_unsafe_type<bit_one>();
    test_is_not_unsafe_type<base>();
    test_is_not_unsafe_type<derived>();
    test_is_not_unsafe_type<abstract>();
    test_is_not_unsafe_type<public_abstract>();
    test_is_not_unsafe_type<private_abstract>();
    test_is_not_unsafe_type<protected_abstract>();
    test_is_not_unsafe_type<abstract_template<int>>();
    test_is_not_unsafe_type<abstract_template<double>>();
    test_is_not_unsafe_type<abstract_template<class_type>>();
    test_is_not_unsafe_type<abstract_template<incomplete_type>>();
    test_is_not_unsafe_type<final_type>();
    test_is_not_unsafe_type<public_destructor>();
    test_is_not_unsafe_type<protected_destructor>();
    test_is_not_unsafe_type<private_destructor>();
    test_is_not_unsafe_type<virtual_public_destructor>();
    test_is_not_unsafe_type<virtual_protected_destructor>();
    test_is_not_unsafe_type<virtual_private_destructor>();
    test_is_not_unsafe_type<pure_public_destructor>();
    test_is_not_unsafe_type<pure_protected_destructor>();
    test_is_not_unsafe_type<pure_private_destructor>();
    test_is_not_unsafe_type<deleted_public_destructor>();
    test_is_not_unsafe_type<deleted_protected_destructor>();
    test_is_not_unsafe_type<deleted_private_destructor>();
    test_is_not_unsafe_type<deleted_virtual_public_destructor>();
    test_is_not_unsafe_type<deleted_virtual_protected_destructor>();
    test_is_not_unsafe_type<deleted_virtual_private_destructor>();
    test_is_not_unsafe_type<Enum>();
    test_is_not_unsafe_type<EnumSigned>();
    test_is_not_unsafe_type<EnumUnsigned>();
    test_is_not_unsafe_type<EnumClass>();
    test_is_not_unsafe_type<EnumStruct>();
    test_is_not_unsafe_type<function_type>();
    test_is_not_unsafe_type<function_ptr>();
    test_is_not_unsafe_type<member_object_ptr>();
    test_is_not_unsafe_type<member_function_ptr>();
    test_is_not_unsafe_type<incomplete_type>();
    test_is_not_unsafe_type<incomplete_template<void>>();
    test_is_not_unsafe_type<incomplete_template<int>>();
    test_is_not_unsafe_type<incomplete_template<class_type>>();
    test_is_not_unsafe_type<incomplete_template<incomplete_type>>();
    test_is_not_unsafe_type<incomplete_variadic_template<>>();
    test_is_not_unsafe_type<incomplete_variadic_template<void>>();
    test_is_not_unsafe_type<incomplete_variadic_template<int>>();
    test_is_not_unsafe_type<incomplete_variadic_template<class_type>>();
    test_is_not_unsafe_type<incomplete_variadic_template<incomplete_type>>();
    test_is_not_unsafe_type<incomplete_variadic_template<int, void, class_type, volatile char[]>>();
    test_is_not_unsafe_type<int class_type::*>();
    test_is_not_unsafe_type<float class_type::*>();
    test_is_not_unsafe_type<void * class_type::*>();
    test_is_not_unsafe_type<int * class_type::*>();
    test_is_not_unsafe_type<int class_type::*&>();
    test_is_not_unsafe_type<float class_type::*&>();
    test_is_not_unsafe_type<void * class_type::*&>();
    test_is_not_unsafe_type<int * class_type::*&>();
    test_is_not_unsafe_type<int class_type::*&&>();
    test_is_not_unsafe_type<float class_type::*&&>();
    test_is_not_unsafe_type<void * class_type::*&&>();
    test_is_not_unsafe_type<int * class_type::*&&>();
    test_is_not_unsafe_type<int class_type::* const>();
    test_is_not_unsafe_type<float class_type::* const>();
    test_is_not_unsafe_type<void * class_type::* const>();
    test_is_not_unsafe_type<int class_type::* const&>();
    test_is_not_unsafe_type<float class_type::* const&>();
    test_is_not_unsafe_type<void * class_type::* const&>();
    test_is_not_unsafe_type<int class_type::* const&&>();
    test_is_not_unsafe_type<float class_type::* const&&>();
    test_is_not_unsafe_type<void * class_type::* const&&>();
    test_is_not_unsafe_type<int class_type::* volatile>();
    test_is_not_unsafe_type<float class_type::* volatile>();
    test_is_not_unsafe_type<void * class_type::* volatile>();
    test_is_not_unsafe_type<int class_type::* volatile&>();
    test_is_not_unsafe_type<float class_type::* volatile&>();
    test_is_not_unsafe_type<void * class_type::* volatile&>();
    test_is_not_unsafe_type<int class_type::* volatile&&>();
    test_is_not_unsafe_type<float class_type::* volatile&&>();
    test_is_not_unsafe_type<void * class_type::* volatile&&>();
    test_is_not_unsafe_type<int class_type::* const volatile>();
    test_is_not_unsafe_type<float class_type::* const volatile>();
    test_is_not_unsafe_type<void * class_type::* const volatile>();
    test_is_not_unsafe_type<int class_type::* const volatile&>();
    test_is_not_unsafe_type<float class_type::* const volatile&>();
    test_is_not_unsafe_type<void * class_type::* const volatile&>();
    test_is_not_unsafe_type<int class_type::* const volatile&&>();
    test_is_not_unsafe_type<float class_type::* const volatile&&>();
    test_is_not_unsafe_type<void * class_type::* const volatile&&>();
    test_is_not_unsafe_type<non_copyable>();
    test_is_not_unsafe_type<non_moveable>();
    test_is_not_unsafe_type<non_constructible>();
    test_is_not_unsafe_type<tracked>();
    test_is_not_unsafe_type<trap_constructible>();
    test_is_not_unsafe_type<trap_implicit_conversion>();
    test_is_not_unsafe_type<trap_comma>();
    test_is_not_unsafe_type<trap_call>();
    test_is_not_unsafe_type<trap_self_assign>();
    test_is_not_unsafe_type<trap_deref>();
    test_is_not_unsafe_type<trap_array_subscript>();

    test_is_not_unsafe_type<void()>();
    test_is_not_unsafe_type<void()&>();
    test_is_not_unsafe_type<void() &&>();
    test_is_not_unsafe_type<void() const>();
    test_is_not_unsafe_type<void() const&>();
    test_is_not_unsafe_type<void() const&&>();
    test_is_not_unsafe_type<void() volatile>();
    test_is_not_unsafe_type<void() volatile&>();
    test_is_not_unsafe_type<void() volatile&&>();
    test_is_not_unsafe_type<void() const volatile>();
    test_is_not_unsafe_type<void() const volatile&>();
    test_is_not_unsafe_type<void() const volatile&&>();
    test_is_not_unsafe_type<void() noexcept>();
    test_is_not_unsafe_type<void() & noexcept>();
    test_is_not_unsafe_type<void() && noexcept>();
    test_is_not_unsafe_type<void() const noexcept>();
    test_is_not_unsafe_type<void() const & noexcept>();
    test_is_not_unsafe_type<void() const && noexcept>();
    test_is_not_unsafe_type<void() volatile noexcept>();
    test_is_not_unsafe_type<void() volatile & noexcept>();
    test_is_not_unsafe_type<void() volatile && noexcept>();
    test_is_not_unsafe_type<void() const volatile noexcept>();
    test_is_not_unsafe_type<void() const volatile & noexcept>();
    test_is_not_unsafe_type<void() const volatile && noexcept>();

    test_is_not_unsafe_type<void(int)>();
    test_is_not_unsafe_type<void(int)&>();
    test_is_not_unsafe_type<void(int) &&>();
    test_is_not_unsafe_type<void(int) const>();
    test_is_not_unsafe_type<void(int) const&>();
    test_is_not_unsafe_type<void(int) const&&>();
    test_is_not_unsafe_type<void(int) volatile>();
    test_is_not_unsafe_type<void(int) volatile&>();
    test_is_not_unsafe_type<void(int) volatile&&>();
    test_is_not_unsafe_type<void(int) const volatile>();
    test_is_not_unsafe_type<void(int) const volatile&>();
    test_is_not_unsafe_type<void(int) const volatile&&>();
    test_is_not_unsafe_type<void(int) noexcept>();
    test_is_not_unsafe_type<void(int) & noexcept>();
    test_is_not_unsafe_type<void(int) && noexcept>();
    test_is_not_unsafe_type<void(int) const noexcept>();
    test_is_not_unsafe_type<void(int) const & noexcept>();
    test_is_not_unsafe_type<void(int) const && noexcept>();
    test_is_not_unsafe_type<void(int) volatile noexcept>();
    test_is_not_unsafe_type<void(int) volatile & noexcept>();
    test_is_not_unsafe_type<void(int) volatile && noexcept>();
    test_is_not_unsafe_type<void(int) const volatile noexcept>();
    test_is_not_unsafe_type<void(int) const volatile & noexcept>();
    test_is_not_unsafe_type<void(int) const volatile && noexcept>();

    test_is_not_unsafe_type<void(...)>();
    test_is_not_unsafe_type<void(...)&>();
    test_is_not_unsafe_type<void(...) &&>();
    test_is_not_unsafe_type<void(...) const>();
    test_is_not_unsafe_type<void(...) const&>();
    test_is_not_unsafe_type<void(...) const&&>();
    test_is_not_unsafe_type<void(...) volatile>();
    test_is_not_unsafe_type<void(...) volatile&>();
    test_is_not_unsafe_type<void(...) volatile&&>();
    test_is_not_unsafe_type<void(...) const volatile>();
    test_is_not_unsafe_type<void(...) const volatile&>();
    test_is_not_unsafe_type<void(...) const volatile&&>();
    test_is_not_unsafe_type<void(...) noexcept>();
    test_is_not_unsafe_type<void(...) & noexcept>();
    test_is_not_unsafe_type<void(...) && noexcept>();
    test_is_not_unsafe_type<void(...) const noexcept>();
    test_is_not_unsafe_type<void(...) const & noexcept>();
    test_is_not_unsafe_type<void(...) const && noexcept>();
    test_is_not_unsafe_type<void(...) volatile noexcept>();
    test_is_not_unsafe_type<void(...) volatile & noexcept>();
    test_is_not_unsafe_type<void(...) volatile && noexcept>();
    test_is_not_unsafe_type<void(...) const volatile noexcept>();
    test_is_not_unsafe_type<void(...) const volatile & noexcept>();
    test_is_not_unsafe_type<void(...) const volatile && noexcept>();

    test_is_not_unsafe_type<void(int, ...)>();
    test_is_not_unsafe_type<void(int, ...)&>();
    test_is_not_unsafe_type<void(int, ...) &&>();
    test_is_not_unsafe_type<void(int, ...) const>();
    test_is_not_unsafe_type<void(int, ...) const&>();
    test_is_not_unsafe_type<void(int, ...) const&&>();
    test_is_not_unsafe_type<void(int, ...) volatile>();
    test_is_not_unsafe_type<void(int, ...) volatile&>();
    test_is_not_unsafe_type<void(int, ...) volatile&&>();
    test_is_not_unsafe_type<void(int, ...) const volatile>();
    test_is_not_unsafe_type<void(int, ...) const volatile&>();
    test_is_not_unsafe_type<void(int, ...) const volatile&&>();
    test_is_not_unsafe_type<void(int, ...) noexcept>();
    test_is_not_unsafe_type<void(int, ...) & noexcept>();
    test_is_not_unsafe_type<void(int, ...) && noexcept>();
    test_is_not_unsafe_type<void(int, ...) const noexcept>();
    test_is_not_unsafe_type<void(int, ...) const & noexcept>();
    test_is_not_unsafe_type<void(int, ...) const && noexcept>();
    test_is_not_unsafe_type<void(int, ...) volatile noexcept>();
    test_is_not_unsafe_type<void(int, ...) volatile & noexcept>();
    test_is_not_unsafe_type<void(int, ...) volatile && noexcept>();
    test_is_not_unsafe_type<void(int, ...) const volatile noexcept>();
    test_is_not_unsafe_type<void(int, ...) const volatile & noexcept>();
    test_is_not_unsafe_type<void(int, ...) const volatile && noexcept>();

    test_is_not_unsafe_type<int()>();
    test_is_not_unsafe_type<int()&>();
    test_is_not_unsafe_type<int() &&>();
    test_is_not_unsafe_type<int() const>();
    test_is_not_unsafe_type<int() const&>();
    test_is_not_unsafe_type<int() const&&>();
    test_is_not_unsafe_type<int() volatile>();
    test_is_not_unsafe_type<int() volatile&>();
    test_is_not_unsafe_type<int() volatile&&>();
    test_is_not_unsafe_type<int() const volatile>();
    test_is_not_unsafe_type<int() const volatile&>();
    test_is_not_unsafe_type<int() const volatile&&>();
    test_is_not_unsafe_type<int() noexcept>();
    test_is_not_unsafe_type<int() & noexcept>();
    test_is_not_unsafe_type<int() && noexcept>();
    test_is_not_unsafe_type<int() const noexcept>();
    test_is_not_unsafe_type<int() const & noexcept>();
    test_is_not_unsafe_type<int() const && noexcept>();
    test_is_not_unsafe_type<int() volatile noexcept>();
    test_is_not_unsafe_type<int() volatile & noexcept>();
    test_is_not_unsafe_type<int() volatile && noexcept>();
    test_is_not_unsafe_type<int() const volatile noexcept>();
    test_is_not_unsafe_type<int() const volatile & noexcept>();
    test_is_not_unsafe_type<int() const volatile && noexcept>();

    test_is_not_unsafe_type<int(int)>();
    test_is_not_unsafe_type<int(int)&>();
    test_is_not_unsafe_type<int(int) &&>();
    test_is_not_unsafe_type<int(int) const>();
    test_is_not_unsafe_type<int(int) const&>();
    test_is_not_unsafe_type<int(int) const&&>();
    test_is_not_unsafe_type<int(int) volatile>();
    test_is_not_unsafe_type<int(int) volatile&>();
    test_is_not_unsafe_type<int(int) volatile&&>();
    test_is_not_unsafe_type<int(int) const volatile>();
    test_is_not_unsafe_type<int(int) const volatile&>();
    test_is_not_unsafe_type<int(int) const volatile&&>();
    test_is_not_unsafe_type<int(int) noexcept>();
    test_is_not_unsafe_type<int(int) & noexcept>();
    test_is_not_unsafe_type<int(int) && noexcept>();
    test_is_not_unsafe_type<int(int) const noexcept>();
    test_is_not_unsafe_type<int(int) const & noexcept>();
    test_is_not_unsafe_type<int(int) const && noexcept>();
    test_is_not_unsafe_type<int(int) volatile noexcept>();
    test_is_not_unsafe_type<int(int) volatile & noexcept>();
    test_is_not_unsafe_type<int(int) volatile && noexcept>();
    test_is_not_unsafe_type<int(int) const volatile noexcept>();
    test_is_not_unsafe_type<int(int) const volatile & noexcept>();
    test_is_not_unsafe_type<int(int) const volatile && noexcept>();

    test_is_not_unsafe_type<int(...)>();
    test_is_not_unsafe_type<int(...)&>();
    test_is_not_unsafe_type<int(...) &&>();
    test_is_not_unsafe_type<int(...) const>();
    test_is_not_unsafe_type<int(...) const&>();
    test_is_not_unsafe_type<int(...) const&&>();
    test_is_not_unsafe_type<int(...) volatile>();
    test_is_not_unsafe_type<int(...) volatile&>();
    test_is_not_unsafe_type<int(...) volatile&&>();
    test_is_not_unsafe_type<int(...) const volatile>();
    test_is_not_unsafe_type<int(...) const volatile&>();
    test_is_not_unsafe_type<int(...) const volatile&&>();
    test_is_not_unsafe_type<int(...) noexcept>();
    test_is_not_unsafe_type<int(...) & noexcept>();
    test_is_not_unsafe_type<int(...) && noexcept>();
    test_is_not_unsafe_type<int(...) const noexcept>();
    test_is_not_unsafe_type<int(...) const & noexcept>();
    test_is_not_unsafe_type<int(...) const && noexcept>();
    test_is_not_unsafe_type<int(...) volatile noexcept>();
    test_is_not_unsafe_type<int(...) volatile & noexcept>();
    test_is_not_unsafe_type<int(...) volatile && noexcept>();
    test_is_not_unsafe_type<int(...) const volatile noexcept>();
    test_is_not_unsafe_type<int(...) const volatile & noexcept>();
    test_is_not_unsafe_type<int(...) const volatile && noexcept>();

    test_is_not_unsafe_type<int(int, ...)>();
    test_is_not_unsafe_type<int(int, ...)&>();
    test_is_not_unsafe_type<int(int, ...) &&>();
    test_is_not_unsafe_type<int(int, ...) const>();
    test_is_not_unsafe_type<int(int, ...) const&>();
    test_is_not_unsafe_type<int(int, ...) const&&>();
    test_is_not_unsafe_type<int(int, ...) volatile>();
    test_is_not_unsafe_type<int(int, ...) volatile&>();
    test_is_not_unsafe_type<int(int, ...) volatile&&>();
    test_is_not_unsafe_type<int(int, ...) const volatile>();
    test_is_not_unsafe_type<int(int, ...) const volatile&>();
    test_is_not_unsafe_type<int(int, ...) const volatile&&>();
    test_is_not_unsafe_type<int(int, ...) noexcept>();
    test_is_not_unsafe_type<int(int, ...) & noexcept>();
    test_is_not_unsafe_type<int(int, ...) && noexcept>();
    test_is_not_unsafe_type<int(int, ...) const noexcept>();
    test_is_not_unsafe_type<int(int, ...) const & noexcept>();
    test_is_not_unsafe_type<int(int, ...) const && noexcept>();
    test_is_not_unsafe_type<int(int, ...) volatile noexcept>();
    test_is_not_unsafe_type<int(int, ...) volatile & noexcept>();
    test_is_not_unsafe_type<int(int, ...) volatile && noexcept>();
    test_is_not_unsafe_type<int(int, ...) const volatile noexcept>();
    test_is_not_unsafe_type<int(int, ...) const volatile & noexcept>();
    test_is_not_unsafe_type<int(int, ...) const volatile && noexcept>();

    test_is_not_unsafe_type<void (*)()>();
    test_is_not_unsafe_type<void (*)() noexcept>();

    test_is_not_unsafe_type<void (*)(int)>();
    test_is_not_unsafe_type<void (*)(int) noexcept>();

    test_is_not_unsafe_type<void (*)(...)>();
    test_is_not_unsafe_type<void (*)(...) noexcept>();

    test_is_not_unsafe_type<void (*)(int, ...)>();
    test_is_not_unsafe_type<void (*)(int, ...) noexcept>();

    test_is_not_unsafe_type<int (*)()>();
    test_is_not_unsafe_type<int (*)() noexcept>();

    test_is_not_unsafe_type<int (*)(int)>();
    test_is_not_unsafe_type<int (*)(int) noexcept>();

    test_is_not_unsafe_type<int (*)(...)>();
    test_is_not_unsafe_type<int (*)(...) noexcept>();

    test_is_not_unsafe_type<int (*)(int, ...)>();
    test_is_not_unsafe_type<int (*)(int, ...) noexcept>();

    test_is_not_unsafe_type<void (&)()>();
    test_is_not_unsafe_type<void (&)() noexcept>();

    test_is_not_unsafe_type<void (&)(int)>();
    test_is_not_unsafe_type<void (&)(int) noexcept>();

    test_is_not_unsafe_type<void (&)(...)>();
    test_is_not_unsafe_type<void (&)(...) noexcept>();

    test_is_not_unsafe_type<void (&)(int, ...)>();
    test_is_not_unsafe_type<void (&)(int, ...) noexcept>();

    test_is_not_unsafe_type<int (&)()>();
    test_is_not_unsafe_type<int (&)() noexcept>();

    test_is_not_unsafe_type<int (&)(int)>();
    test_is_not_unsafe_type<int (&)(int) noexcept>();

    test_is_not_unsafe_type<int (&)(...)>();
    test_is_not_unsafe_type<int (&)(...) noexcept>();

    test_is_not_unsafe_type<int (&)(int, ...)>();
    test_is_not_unsafe_type<int (&)(int, ...) noexcept>();

    test_is_not_unsafe_type<void (&&)()>();
    test_is_not_unsafe_type<void (&&)() noexcept>();

    test_is_not_unsafe_type<void (&&)(int)>();
    test_is_not_unsafe_type<void (&&)(int) noexcept>();

    test_is_not_unsafe_type<void (&&)(...)>();
    test_is_not_unsafe_type<void (&&)(...) noexcept>();

    test_is_not_unsafe_type<void (&&)(int, ...)>();
    test_is_not_unsafe_type<void (&&)(int, ...) noexcept>();

    test_is_not_unsafe_type<int (&&)()>();
    test_is_not_unsafe_type<int (&&)() noexcept>();

    test_is_not_unsafe_type<int (&&)(int)>();
    test_is_not_unsafe_type<int (&&)(int) noexcept>();

    test_is_not_unsafe_type<int (&&)(...)>();
    test_is_not_unsafe_type<int (&&)(...) noexcept>();

    test_is_not_unsafe_type<int (&&)(int, ...)>();
    test_is_not_unsafe_type<int (&&)(int, ...) noexcept>();

    test_is_not_unsafe_type<void (class_type::*)()>();
    test_is_not_unsafe_type<void (class_type::*)()&>();
    test_is_not_unsafe_type<void (class_type::*)() &&>();
    test_is_not_unsafe_type<void (class_type::*)() const>();
    test_is_not_unsafe_type<void (class_type::*)() const&>();
    test_is_not_unsafe_type<void (class_type::*)() const&&>();
    test_is_not_unsafe_type<void (class_type::*)() noexcept>();
    test_is_not_unsafe_type<void (class_type::*)() & noexcept>();
    test_is_not_unsafe_type<void (class_type::*)() && noexcept>();
    test_is_not_unsafe_type<void (class_type::*)() const noexcept>();
    test_is_not_unsafe_type<void (class_type::*)() const & noexcept>();
    test_is_not_unsafe_type<void (class_type::*)() const && noexcept>();

    test_is_not_unsafe_type<void (class_type::*)(int)>();
    test_is_not_unsafe_type<void (class_type::*)(int)&>();
    test_is_not_unsafe_type<void (class_type::*)(int) &&>();
    test_is_not_unsafe_type<void (class_type::*)(int) const>();
    test_is_not_unsafe_type<void (class_type::*)(int) const&>();
    test_is_not_unsafe_type<void (class_type::*)(int) const&&>();
    test_is_not_unsafe_type<void (class_type::*)(int) noexcept>();
    test_is_not_unsafe_type<void (class_type::*)(int) & noexcept>();
    test_is_not_unsafe_type<void (class_type::*)(int) && noexcept>();
    test_is_not_unsafe_type<void (class_type::*)(int) const noexcept>();
    test_is_not_unsafe_type<void (class_type::*)(int) const & noexcept>();
    test_is_not_unsafe_type<void (class_type::*)(int) const && noexcept>();

    test_is_not_unsafe_type<void (class_type::*)(...)>();
    test_is_not_unsafe_type<void (class_type::*)(...)&>();
    test_is_not_unsafe_type<void (class_type::*)(...) &&>();
    test_is_not_unsafe_type<void (class_type::*)(...) const>();
    test_is_not_unsafe_type<void (class_type::*)(...) const&>();
    test_is_not_unsafe_type<void (class_type::*)(...) const&&>();
    test_is_not_unsafe_type<void (class_type::*)(...) noexcept>();
    test_is_not_unsafe_type<void (class_type::*)(...) & noexcept>();
    test_is_not_unsafe_type<void (class_type::*)(...) && noexcept>();
    test_is_not_unsafe_type<void (class_type::*)(...) const noexcept>();
    test_is_not_unsafe_type<void (class_type::*)(...) const & noexcept>();
    test_is_not_unsafe_type<void (class_type::*)(...) const && noexcept>();

    test_is_not_unsafe_type<void (class_type::*)(int, ...)>();
    test_is_not_unsafe_type<void (class_type::*)(int, ...)&>();
    test_is_not_unsafe_type<void (class_type::*)(int, ...) &&>();
    test_is_not_unsafe_type<void (class_type::*)(int, ...) const>();
    test_is_not_unsafe_type<void (class_type::*)(int, ...) const&>();
    test_is_not_unsafe_type<void (class_type::*)(int, ...) const&&>();
    test_is_not_unsafe_type<void (class_type::*)(int, ...) noexcept>();
    test_is_not_unsafe_type<void (class_type::*)(int, ...) & noexcept>();
    test_is_not_unsafe_type<void (class_type::*)(int, ...) && noexcept>();
    test_is_not_unsafe_type<void (class_type::*)(int, ...) const noexcept>();
    test_is_not_unsafe_type<void (class_type::*)(int, ...) const & noexcept>();
    test_is_not_unsafe_type<void (class_type::*)(int, ...) const && noexcept>();

    test_is_not_unsafe_type<int (class_type::*)()>();
    test_is_not_unsafe_type<int (class_type::*)()&>();
    test_is_not_unsafe_type<int (class_type::*)() &&>();
    test_is_not_unsafe_type<int (class_type::*)() const>();
    test_is_not_unsafe_type<int (class_type::*)() const&>();
    test_is_not_unsafe_type<int (class_type::*)() const&&>();
    test_is_not_unsafe_type<int (class_type::*)() noexcept>();
    test_is_not_unsafe_type<int (class_type::*)() & noexcept>();
    test_is_not_unsafe_type<int (class_type::*)() && noexcept>();
    test_is_not_unsafe_type<int (class_type::*)() const noexcept>();
    test_is_not_unsafe_type<int (class_type::*)() const & noexcept>();
    test_is_not_unsafe_type<int (class_type::*)() const && noexcept>();

    test_is_not_unsafe_type<int (class_type::*)(int)>();
    test_is_not_unsafe_type<int (class_type::*)(int)&>();
    test_is_not_unsafe_type<int (class_type::*)(int) &&>();
    test_is_not_unsafe_type<int (class_type::*)(int) const>();
    test_is_not_unsafe_type<int (class_type::*)(int) const&>();
    test_is_not_unsafe_type<int (class_type::*)(int) const&&>();
    test_is_not_unsafe_type<int (class_type::*)(int) noexcept>();
    test_is_not_unsafe_type<int (class_type::*)(int) & noexcept>();
    test_is_not_unsafe_type<int (class_type::*)(int) && noexcept>();
    test_is_not_unsafe_type<int (class_type::*)(int) const noexcept>();
    test_is_not_unsafe_type<int (class_type::*)(int) const & noexcept>();
    test_is_not_unsafe_type<int (class_type::*)(int) const && noexcept>();

    test_is_not_unsafe_type<int (class_type::*)(...)>();
    test_is_not_unsafe_type<int (class_type::*)(...)&>();
    test_is_not_unsafe_type<int (class_type::*)(...) &&>();
    test_is_not_unsafe_type<int (class_type::*)(...) const>();
    test_is_not_unsafe_type<int (class_type::*)(...) const&>();
    test_is_not_unsafe_type<int (class_type::*)(...) const&&>();
    test_is_not_unsafe_type<int (class_type::*)(...) noexcept>();
    test_is_not_unsafe_type<int (class_type::*)(...) & noexcept>();
    test_is_not_unsafe_type<int (class_type::*)(...) && noexcept>();
    test_is_not_unsafe_type<int (class_type::*)(...) const noexcept>();
    test_is_not_unsafe_type<int (class_type::*)(...) const & noexcept>();
    test_is_not_unsafe_type<int (class_type::*)(...) const && noexcept>();

    test_is_not_unsafe_type<int (class_type::*)(int, ...)>();
    test_is_not_unsafe_type<int (class_type::*)(int, ...)&>();
    test_is_not_unsafe_type<int (class_type::*)(int, ...) &&>();
    test_is_not_unsafe_type<int (class_type::*)(int, ...) const>();
    test_is_not_unsafe_type<int (class_type::*)(int, ...) const&>();
    test_is_not_unsafe_type<int (class_type::*)(int, ...) const&&>();
    test_is_not_unsafe_type<int (class_type::*)(int, ...) noexcept>();
    test_is_not_unsafe_type<int (class_type::*)(int, ...) & noexcept>();
    test_is_not_unsafe_type<int (class_type::*)(int, ...) && noexcept>();
    test_is_not_unsafe_type<int (class_type::*)(int, ...) const noexcept>();
    test_is_not_unsafe_type<int (class_type::*)(int, ...) const & noexcept>();
    test_is_not_unsafe_type<int (class_type::*)(int, ...) const && noexcept>();
}
