#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_class.hpp>
#include <phi/type_traits/is_lvalue_reference.hpp>
#include <phi/type_traits/is_reference.hpp>
#include <phi/type_traits/is_reference_wrapper.hpp>
#include <phi/type_traits/is_rvalue_reference.hpp>
#include <functional>
#include <vector>

template <typename TypeT>
void test_is_reference_wrapper_impl()
{
    STATIC_REQUIRE(phi::is_reference_wrapper<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_reference_wrapper<TypeT>::value);

#if PHI_HAS_WORKING_IS_CLASS()
    STATIC_REQUIRE(phi::is_class<TypeT>::value);
#endif
    STATIC_REQUIRE_FALSE(phi::is_lvalue_reference<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_reference<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_rvalue_reference<TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_reference_wrapper_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_not_reference_wrapper_v<TypeT>);

#    if PHI_HAS_WORKING_IS_CLASS()
    STATIC_REQUIRE(phi::is_class_v<TypeT>);
#    endif
    STATIC_REQUIRE_FALSE(phi::is_lvalue_reference_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_reference_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_rvalue_reference_v<TypeT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_reference_wrapper<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_reference_wrapper<TypeT>);
}

template <typename TypeT>
void test_is_not_reference_wrapper_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_reference_wrapper<TypeT>::value);
    STATIC_REQUIRE(phi::is_not_reference_wrapper<TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_reference_wrapper_v<TypeT>);
    STATIC_REQUIRE(phi::is_not_reference_wrapper_v<TypeT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_reference_wrapper<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_reference_wrapper<TypeT>);
}

template <typename TypeT>
void test_is_reference_wrapper()
{
    test_is_reference_wrapper_impl<TypeT>();
    test_is_reference_wrapper_impl<const TypeT>();
    test_is_reference_wrapper_impl<volatile TypeT>();
    test_is_reference_wrapper_impl<const volatile TypeT>();
}

template <typename TypeT>
void test_is_not_reference_wrapper()
{
    test_is_not_reference_wrapper_impl<TypeT>();
    test_is_not_reference_wrapper_impl<const TypeT>();
    test_is_not_reference_wrapper_impl<volatile TypeT>();
    test_is_not_reference_wrapper_impl<const volatile TypeT>();
}

TEST_CASE("is_refenrece_wrapper")
{
    test_is_reference_wrapper<std::reference_wrapper<int>>();
    test_is_reference_wrapper<std::reference_wrapper<float>>();
    test_is_reference_wrapper<std::reference_wrapper<void>>();

    test_is_not_reference_wrapper<void>();
    test_is_not_reference_wrapper<phi::nullptr_t>();
    test_is_not_reference_wrapper<bool>();
    test_is_not_reference_wrapper<char>();
    test_is_not_reference_wrapper<signed char>();
    test_is_not_reference_wrapper<unsigned char>();
    test_is_not_reference_wrapper<short>();
    test_is_not_reference_wrapper<unsigned short>();
    test_is_not_reference_wrapper<int>();
    test_is_not_reference_wrapper<unsigned int>();
    test_is_not_reference_wrapper<long>();
    test_is_not_reference_wrapper<unsigned long>();
    test_is_not_reference_wrapper<long long>();
    test_is_not_reference_wrapper<unsigned long long>();
    test_is_not_reference_wrapper<float>();
    test_is_not_reference_wrapper<double>();
    test_is_not_reference_wrapper<long double>();
    test_is_not_reference_wrapper<char8_t>();
    test_is_not_reference_wrapper<char16_t>();
    test_is_not_reference_wrapper<char32_t>();
    test_is_not_reference_wrapper<wchar_t>();

    test_is_not_reference_wrapper<phi::boolean>();
    test_is_not_reference_wrapper<phi::integer<signed char>>();
    test_is_not_reference_wrapper<phi::integer<unsigned char>>();
    test_is_not_reference_wrapper<phi::integer<short>>();
    test_is_not_reference_wrapper<phi::integer<unsigned short>>();
    test_is_not_reference_wrapper<phi::integer<int>>();
    test_is_not_reference_wrapper<phi::integer<unsigned int>>();
    test_is_not_reference_wrapper<phi::integer<long>>();
    test_is_not_reference_wrapper<phi::integer<unsigned long>>();
    test_is_not_reference_wrapper<phi::integer<long long>>();
    test_is_not_reference_wrapper<phi::integer<unsigned long long>>();
    test_is_not_reference_wrapper<phi::floating_point<float>>();
    test_is_not_reference_wrapper<phi::floating_point<double>>();
    test_is_not_reference_wrapper<phi::floating_point<long double>>();

    test_is_not_reference_wrapper<std::vector<int>>();
    test_is_not_reference_wrapper<phi::scope_ptr<int>>();

    test_is_not_reference_wrapper<int&>();
    test_is_not_reference_wrapper<const int&>();
    test_is_not_reference_wrapper<volatile int&>();
    test_is_not_reference_wrapper<const volatile int&>();
    test_is_not_reference_wrapper<int&&>();
    test_is_not_reference_wrapper<const int&&>();
    test_is_not_reference_wrapper<volatile int&&>();
    test_is_not_reference_wrapper<const volatile int&&>();
    test_is_not_reference_wrapper<int*>();
    test_is_not_reference_wrapper<const int*>();
    test_is_not_reference_wrapper<volatile int*>();
    test_is_not_reference_wrapper<const volatile int*>();
    test_is_not_reference_wrapper<int**>();
    test_is_not_reference_wrapper<const int**>();
    test_is_not_reference_wrapper<volatile int**>();
    test_is_not_reference_wrapper<const volatile int**>();
    test_is_not_reference_wrapper<int*&>();
    test_is_not_reference_wrapper<const int*&>();
    test_is_not_reference_wrapper<volatile int*&>();
    test_is_not_reference_wrapper<const volatile int*&>();
    test_is_not_reference_wrapper<int*&&>();
    test_is_not_reference_wrapper<const int*&&>();
    test_is_not_reference_wrapper<volatile int*&&>();
    test_is_not_reference_wrapper<const volatile int*&&>();
    test_is_not_reference_wrapper<void*>();
    test_is_not_reference_wrapper<char[3]>();
    test_is_not_reference_wrapper<char[]>();
    test_is_not_reference_wrapper<char* [3]>();
    test_is_not_reference_wrapper<char*[]>();
    test_is_not_reference_wrapper<int(*)[3]>();
    test_is_not_reference_wrapper<int(*)[]>();
    test_is_not_reference_wrapper<int(&)[3]>();
    test_is_not_reference_wrapper<int(&)[]>();
    test_is_not_reference_wrapper<int(&&)[3]>();
    test_is_not_reference_wrapper<int(&&)[]>();
    test_is_not_reference_wrapper<char[3][2]>();
    test_is_not_reference_wrapper<char[][2]>();
    test_is_not_reference_wrapper<char* [3][2]>();
    test_is_not_reference_wrapper<char*[][2]>();
    test_is_not_reference_wrapper<int(*)[3][2]>();
    test_is_not_reference_wrapper<int(*)[][2]>();
    test_is_not_reference_wrapper<int(&)[3][2]>();
    test_is_not_reference_wrapper<int(&)[][2]>();
    test_is_not_reference_wrapper<int(&&)[3][2]>();
    test_is_not_reference_wrapper<int(&&)[][2]>();
    test_is_not_reference_wrapper<class_type>();
    test_is_not_reference_wrapper<class_type[]>();
    test_is_not_reference_wrapper<class_type[2]>();
    test_is_not_reference_wrapper<template_type<void>>();
    test_is_not_reference_wrapper<template_type<int>>();
    test_is_not_reference_wrapper<template_type<class_type>>();
    test_is_not_reference_wrapper<template_type<incomplete_type>>();
    test_is_not_reference_wrapper<variadic_template<>>();
    test_is_not_reference_wrapper<variadic_template<void>>();
    test_is_not_reference_wrapper<variadic_template<int>>();
    test_is_not_reference_wrapper<variadic_template<class_type>>();
    test_is_not_reference_wrapper<variadic_template<incomplete_type>>();
    test_is_not_reference_wrapper<variadic_template<int, void, class_type, volatile char[]>>();
    test_is_not_reference_wrapper<public_derived_from<base>>();
    test_is_not_reference_wrapper<public_derived_from<derived>>();
    test_is_not_reference_wrapper<public_derived_from<class_type>>();
    test_is_not_reference_wrapper<private_derived_from<base>>();
    test_is_not_reference_wrapper<private_derived_from<derived>>();
    test_is_not_reference_wrapper<private_derived_from<class_type>>();
    test_is_not_reference_wrapper<protected_derived_from<base>>();
    test_is_not_reference_wrapper<protected_derived_from<derived>>();
    test_is_not_reference_wrapper<protected_derived_from<class_type>>();
    test_is_not_reference_wrapper<union_type>();
    test_is_not_reference_wrapper<non_empty_union>();
    test_is_not_reference_wrapper<empty>();
    test_is_not_reference_wrapper<not_empty>();
    test_is_not_reference_wrapper<bit_zero>();
    test_is_not_reference_wrapper<bit_one>();
    test_is_not_reference_wrapper<base>();
    test_is_not_reference_wrapper<derived>();
    test_is_not_reference_wrapper<abstract>();
    test_is_not_reference_wrapper<public_abstract>();
    test_is_not_reference_wrapper<private_abstract>();
    test_is_not_reference_wrapper<protected_abstract>();
    test_is_not_reference_wrapper<abstract_template<int>>();
    test_is_not_reference_wrapper<abstract_template<double>>();
    test_is_not_reference_wrapper<abstract_template<class_type>>();
    test_is_not_reference_wrapper<abstract_template<incomplete_type>>();
    test_is_not_reference_wrapper<final_type>();
    test_is_not_reference_wrapper<public_destructor>();
    test_is_not_reference_wrapper<protected_destructor>();
    test_is_not_reference_wrapper<private_destructor>();
    test_is_not_reference_wrapper<virtual_public_destructor>();
    test_is_not_reference_wrapper<virtual_protected_destructor>();
    test_is_not_reference_wrapper<virtual_private_destructor>();
    test_is_not_reference_wrapper<pure_public_destructor>();
    test_is_not_reference_wrapper<pure_protected_destructor>();
    test_is_not_reference_wrapper<pure_private_destructor>();
    test_is_not_reference_wrapper<deleted_public_destructor>();
    test_is_not_reference_wrapper<deleted_protected_destructor>();
    test_is_not_reference_wrapper<deleted_private_destructor>();
    test_is_not_reference_wrapper<deleted_virtual_public_destructor>();
    test_is_not_reference_wrapper<deleted_virtual_protected_destructor>();
    test_is_not_reference_wrapper<deleted_virtual_private_destructor>();
    test_is_not_reference_wrapper<Enum>();
    test_is_not_reference_wrapper<EnumSigned>();
    test_is_not_reference_wrapper<EnumUnsigned>();
    test_is_not_reference_wrapper<EnumClass>();
    test_is_not_reference_wrapper<EnumStruct>();
    test_is_not_reference_wrapper<function_type>();
    test_is_not_reference_wrapper<function_ptr>();
    test_is_not_reference_wrapper<member_object_ptr>();
    test_is_not_reference_wrapper<member_function_ptr>();
    test_is_not_reference_wrapper<incomplete_type>();
    test_is_not_reference_wrapper<incomplete_template<void>>();
    test_is_not_reference_wrapper<incomplete_template<int>>();
    test_is_not_reference_wrapper<incomplete_template<class_type>>();
    test_is_not_reference_wrapper<incomplete_template<incomplete_type>>();
    test_is_not_reference_wrapper<incomplete_variadic_template<>>();
    test_is_not_reference_wrapper<incomplete_variadic_template<void>>();
    test_is_not_reference_wrapper<incomplete_variadic_template<int>>();
    test_is_not_reference_wrapper<incomplete_variadic_template<class_type>>();
    test_is_not_reference_wrapper<incomplete_variadic_template<incomplete_type>>();
    test_is_not_reference_wrapper<
            incomplete_variadic_template<int, void, class_type, volatile char[]>>();
    test_is_not_reference_wrapper<int class_type::*>();
    test_is_not_reference_wrapper<float class_type::*>();
    test_is_not_reference_wrapper<void * class_type::*>();
    test_is_not_reference_wrapper<int * class_type::*>();
    test_is_not_reference_wrapper<int class_type::*&>();
    test_is_not_reference_wrapper<float class_type::*&>();
    test_is_not_reference_wrapper<void * class_type::*&>();
    test_is_not_reference_wrapper<int * class_type::*&>();
    test_is_not_reference_wrapper<int class_type::*&&>();
    test_is_not_reference_wrapper<float class_type::*&&>();
    test_is_not_reference_wrapper<void * class_type::*&&>();
    test_is_not_reference_wrapper<int * class_type::*&&>();
    test_is_not_reference_wrapper<int class_type::* const>();
    test_is_not_reference_wrapper<float class_type::* const>();
    test_is_not_reference_wrapper<void * class_type::* const>();
    test_is_not_reference_wrapper<int class_type::* const&>();
    test_is_not_reference_wrapper<float class_type::* const&>();
    test_is_not_reference_wrapper<void * class_type::* const&>();
    test_is_not_reference_wrapper<int class_type::* const&&>();
    test_is_not_reference_wrapper<float class_type::* const&&>();
    test_is_not_reference_wrapper<void * class_type::* const&&>();
    test_is_not_reference_wrapper<int class_type::* volatile>();
    test_is_not_reference_wrapper<float class_type::* volatile>();
    test_is_not_reference_wrapper<void * class_type::* volatile>();
    test_is_not_reference_wrapper<int class_type::* volatile&>();
    test_is_not_reference_wrapper<float class_type::* volatile&>();
    test_is_not_reference_wrapper<void * class_type::* volatile&>();
    test_is_not_reference_wrapper<int class_type::* volatile&&>();
    test_is_not_reference_wrapper<float class_type::* volatile&&>();
    test_is_not_reference_wrapper<void * class_type::* volatile&&>();
    test_is_not_reference_wrapper<int class_type::* const volatile>();
    test_is_not_reference_wrapper<float class_type::* const volatile>();
    test_is_not_reference_wrapper<void * class_type::* const volatile>();
    test_is_not_reference_wrapper<int class_type::* const volatile&>();
    test_is_not_reference_wrapper<float class_type::* const volatile&>();
    test_is_not_reference_wrapper<void * class_type::* const volatile&>();
    test_is_not_reference_wrapper<int class_type::* const volatile&&>();
    test_is_not_reference_wrapper<float class_type::* const volatile&&>();
    test_is_not_reference_wrapper<void * class_type::* const volatile&&>();
    test_is_not_reference_wrapper<non_copyable>();
    test_is_not_reference_wrapper<non_moveable>();
    test_is_not_reference_wrapper<non_constructible>();
    test_is_not_reference_wrapper<tracked>();
    test_is_not_reference_wrapper<trap_constructible>();
    test_is_not_reference_wrapper<trap_implicit_conversion>();
    test_is_not_reference_wrapper<trap_comma>();
    test_is_not_reference_wrapper<trap_call>();
    test_is_not_reference_wrapper<trap_self_assign>();
    test_is_not_reference_wrapper<trap_deref>();
    test_is_not_reference_wrapper<trap_array_subscript>();

    test_is_not_reference_wrapper<void()>();
    test_is_not_reference_wrapper<void()&>();
    test_is_not_reference_wrapper<void() &&>();
    test_is_not_reference_wrapper<void() const>();
    test_is_not_reference_wrapper<void() const&>();
    test_is_not_reference_wrapper<void() const&&>();
    test_is_not_reference_wrapper<void() volatile>();
    test_is_not_reference_wrapper<void() volatile&>();
    test_is_not_reference_wrapper<void() volatile&&>();
    test_is_not_reference_wrapper<void() const volatile>();
    test_is_not_reference_wrapper<void() const volatile&>();
    test_is_not_reference_wrapper<void() const volatile&&>();
    test_is_not_reference_wrapper<void() noexcept>();
    test_is_not_reference_wrapper<void() & noexcept>();
    test_is_not_reference_wrapper<void() && noexcept>();
    test_is_not_reference_wrapper<void() const noexcept>();
    test_is_not_reference_wrapper<void() const & noexcept>();
    test_is_not_reference_wrapper<void() const && noexcept>();
    test_is_not_reference_wrapper<void() volatile noexcept>();
    test_is_not_reference_wrapper<void() volatile & noexcept>();
    test_is_not_reference_wrapper<void() volatile && noexcept>();
    test_is_not_reference_wrapper<void() const volatile noexcept>();
    test_is_not_reference_wrapper<void() const volatile & noexcept>();
    test_is_not_reference_wrapper<void() const volatile && noexcept>();

    test_is_not_reference_wrapper<void(int)>();
    test_is_not_reference_wrapper<void(int)&>();
    test_is_not_reference_wrapper<void(int) &&>();
    test_is_not_reference_wrapper<void(int) const>();
    test_is_not_reference_wrapper<void(int) const&>();
    test_is_not_reference_wrapper<void(int) const&&>();
    test_is_not_reference_wrapper<void(int) volatile>();
    test_is_not_reference_wrapper<void(int) volatile&>();
    test_is_not_reference_wrapper<void(int) volatile&&>();
    test_is_not_reference_wrapper<void(int) const volatile>();
    test_is_not_reference_wrapper<void(int) const volatile&>();
    test_is_not_reference_wrapper<void(int) const volatile&&>();
    test_is_not_reference_wrapper<void(int) noexcept>();
    test_is_not_reference_wrapper<void(int) & noexcept>();
    test_is_not_reference_wrapper<void(int) && noexcept>();
    test_is_not_reference_wrapper<void(int) const noexcept>();
    test_is_not_reference_wrapper<void(int) const & noexcept>();
    test_is_not_reference_wrapper<void(int) const && noexcept>();
    test_is_not_reference_wrapper<void(int) volatile noexcept>();
    test_is_not_reference_wrapper<void(int) volatile & noexcept>();
    test_is_not_reference_wrapper<void(int) volatile && noexcept>();
    test_is_not_reference_wrapper<void(int) const volatile noexcept>();
    test_is_not_reference_wrapper<void(int) const volatile & noexcept>();
    test_is_not_reference_wrapper<void(int) const volatile && noexcept>();

    test_is_not_reference_wrapper<void(...)>();
    test_is_not_reference_wrapper<void(...)&>();
    test_is_not_reference_wrapper<void(...) &&>();
    test_is_not_reference_wrapper<void(...) const>();
    test_is_not_reference_wrapper<void(...) const&>();
    test_is_not_reference_wrapper<void(...) const&&>();
    test_is_not_reference_wrapper<void(...) volatile>();
    test_is_not_reference_wrapper<void(...) volatile&>();
    test_is_not_reference_wrapper<void(...) volatile&&>();
    test_is_not_reference_wrapper<void(...) const volatile>();
    test_is_not_reference_wrapper<void(...) const volatile&>();
    test_is_not_reference_wrapper<void(...) const volatile&&>();
    test_is_not_reference_wrapper<void(...) noexcept>();
    test_is_not_reference_wrapper<void(...) & noexcept>();
    test_is_not_reference_wrapper<void(...) && noexcept>();
    test_is_not_reference_wrapper<void(...) const noexcept>();
    test_is_not_reference_wrapper<void(...) const & noexcept>();
    test_is_not_reference_wrapper<void(...) const && noexcept>();
    test_is_not_reference_wrapper<void(...) volatile noexcept>();
    test_is_not_reference_wrapper<void(...) volatile & noexcept>();
    test_is_not_reference_wrapper<void(...) volatile && noexcept>();
    test_is_not_reference_wrapper<void(...) const volatile noexcept>();
    test_is_not_reference_wrapper<void(...) const volatile & noexcept>();
    test_is_not_reference_wrapper<void(...) const volatile && noexcept>();

    test_is_not_reference_wrapper<void(int, ...)>();
    test_is_not_reference_wrapper<void(int, ...)&>();
    test_is_not_reference_wrapper<void(int, ...) &&>();
    test_is_not_reference_wrapper<void(int, ...) const>();
    test_is_not_reference_wrapper<void(int, ...) const&>();
    test_is_not_reference_wrapper<void(int, ...) const&&>();
    test_is_not_reference_wrapper<void(int, ...) volatile>();
    test_is_not_reference_wrapper<void(int, ...) volatile&>();
    test_is_not_reference_wrapper<void(int, ...) volatile&&>();
    test_is_not_reference_wrapper<void(int, ...) const volatile>();
    test_is_not_reference_wrapper<void(int, ...) const volatile&>();
    test_is_not_reference_wrapper<void(int, ...) const volatile&&>();
    test_is_not_reference_wrapper<void(int, ...) noexcept>();
    test_is_not_reference_wrapper<void(int, ...) & noexcept>();
    test_is_not_reference_wrapper<void(int, ...) && noexcept>();
    test_is_not_reference_wrapper<void(int, ...) const noexcept>();
    test_is_not_reference_wrapper<void(int, ...) const & noexcept>();
    test_is_not_reference_wrapper<void(int, ...) const && noexcept>();
    test_is_not_reference_wrapper<void(int, ...) volatile noexcept>();
    test_is_not_reference_wrapper<void(int, ...) volatile & noexcept>();
    test_is_not_reference_wrapper<void(int, ...) volatile && noexcept>();
    test_is_not_reference_wrapper<void(int, ...) const volatile noexcept>();
    test_is_not_reference_wrapper<void(int, ...) const volatile & noexcept>();
    test_is_not_reference_wrapper<void(int, ...) const volatile && noexcept>();

    test_is_not_reference_wrapper<int()>();
    test_is_not_reference_wrapper<int()&>();
    test_is_not_reference_wrapper<int() &&>();
    test_is_not_reference_wrapper<int() const>();
    test_is_not_reference_wrapper<int() const&>();
    test_is_not_reference_wrapper<int() const&&>();
    test_is_not_reference_wrapper<int() volatile>();
    test_is_not_reference_wrapper<int() volatile&>();
    test_is_not_reference_wrapper<int() volatile&&>();
    test_is_not_reference_wrapper<int() const volatile>();
    test_is_not_reference_wrapper<int() const volatile&>();
    test_is_not_reference_wrapper<int() const volatile&&>();
    test_is_not_reference_wrapper<int() noexcept>();
    test_is_not_reference_wrapper<int() & noexcept>();
    test_is_not_reference_wrapper<int() && noexcept>();
    test_is_not_reference_wrapper<int() const noexcept>();
    test_is_not_reference_wrapper<int() const & noexcept>();
    test_is_not_reference_wrapper<int() const && noexcept>();
    test_is_not_reference_wrapper<int() volatile noexcept>();
    test_is_not_reference_wrapper<int() volatile & noexcept>();
    test_is_not_reference_wrapper<int() volatile && noexcept>();
    test_is_not_reference_wrapper<int() const volatile noexcept>();
    test_is_not_reference_wrapper<int() const volatile & noexcept>();
    test_is_not_reference_wrapper<int() const volatile && noexcept>();

    test_is_not_reference_wrapper<int(int)>();
    test_is_not_reference_wrapper<int(int)&>();
    test_is_not_reference_wrapper<int(int) &&>();
    test_is_not_reference_wrapper<int(int) const>();
    test_is_not_reference_wrapper<int(int) const&>();
    test_is_not_reference_wrapper<int(int) const&&>();
    test_is_not_reference_wrapper<int(int) volatile>();
    test_is_not_reference_wrapper<int(int) volatile&>();
    test_is_not_reference_wrapper<int(int) volatile&&>();
    test_is_not_reference_wrapper<int(int) const volatile>();
    test_is_not_reference_wrapper<int(int) const volatile&>();
    test_is_not_reference_wrapper<int(int) const volatile&&>();
    test_is_not_reference_wrapper<int(int) noexcept>();
    test_is_not_reference_wrapper<int(int) & noexcept>();
    test_is_not_reference_wrapper<int(int) && noexcept>();
    test_is_not_reference_wrapper<int(int) const noexcept>();
    test_is_not_reference_wrapper<int(int) const & noexcept>();
    test_is_not_reference_wrapper<int(int) const && noexcept>();
    test_is_not_reference_wrapper<int(int) volatile noexcept>();
    test_is_not_reference_wrapper<int(int) volatile & noexcept>();
    test_is_not_reference_wrapper<int(int) volatile && noexcept>();
    test_is_not_reference_wrapper<int(int) const volatile noexcept>();
    test_is_not_reference_wrapper<int(int) const volatile & noexcept>();
    test_is_not_reference_wrapper<int(int) const volatile && noexcept>();

    test_is_not_reference_wrapper<int(...)>();
    test_is_not_reference_wrapper<int(...)&>();
    test_is_not_reference_wrapper<int(...) &&>();
    test_is_not_reference_wrapper<int(...) const>();
    test_is_not_reference_wrapper<int(...) const&>();
    test_is_not_reference_wrapper<int(...) const&&>();
    test_is_not_reference_wrapper<int(...) volatile>();
    test_is_not_reference_wrapper<int(...) volatile&>();
    test_is_not_reference_wrapper<int(...) volatile&&>();
    test_is_not_reference_wrapper<int(...) const volatile>();
    test_is_not_reference_wrapper<int(...) const volatile&>();
    test_is_not_reference_wrapper<int(...) const volatile&&>();
    test_is_not_reference_wrapper<int(...) noexcept>();
    test_is_not_reference_wrapper<int(...) & noexcept>();
    test_is_not_reference_wrapper<int(...) && noexcept>();
    test_is_not_reference_wrapper<int(...) const noexcept>();
    test_is_not_reference_wrapper<int(...) const & noexcept>();
    test_is_not_reference_wrapper<int(...) const && noexcept>();
    test_is_not_reference_wrapper<int(...) volatile noexcept>();
    test_is_not_reference_wrapper<int(...) volatile & noexcept>();
    test_is_not_reference_wrapper<int(...) volatile && noexcept>();
    test_is_not_reference_wrapper<int(...) const volatile noexcept>();
    test_is_not_reference_wrapper<int(...) const volatile & noexcept>();
    test_is_not_reference_wrapper<int(...) const volatile && noexcept>();

    test_is_not_reference_wrapper<int(int, ...)>();
    test_is_not_reference_wrapper<int(int, ...)&>();
    test_is_not_reference_wrapper<int(int, ...) &&>();
    test_is_not_reference_wrapper<int(int, ...) const>();
    test_is_not_reference_wrapper<int(int, ...) const&>();
    test_is_not_reference_wrapper<int(int, ...) const&&>();
    test_is_not_reference_wrapper<int(int, ...) volatile>();
    test_is_not_reference_wrapper<int(int, ...) volatile&>();
    test_is_not_reference_wrapper<int(int, ...) volatile&&>();
    test_is_not_reference_wrapper<int(int, ...) const volatile>();
    test_is_not_reference_wrapper<int(int, ...) const volatile&>();
    test_is_not_reference_wrapper<int(int, ...) const volatile&&>();
    test_is_not_reference_wrapper<int(int, ...) noexcept>();
    test_is_not_reference_wrapper<int(int, ...) & noexcept>();
    test_is_not_reference_wrapper<int(int, ...) && noexcept>();
    test_is_not_reference_wrapper<int(int, ...) const noexcept>();
    test_is_not_reference_wrapper<int(int, ...) const & noexcept>();
    test_is_not_reference_wrapper<int(int, ...) const && noexcept>();
    test_is_not_reference_wrapper<int(int, ...) volatile noexcept>();
    test_is_not_reference_wrapper<int(int, ...) volatile & noexcept>();
    test_is_not_reference_wrapper<int(int, ...) volatile && noexcept>();
    test_is_not_reference_wrapper<int(int, ...) const volatile noexcept>();
    test_is_not_reference_wrapper<int(int, ...) const volatile & noexcept>();
    test_is_not_reference_wrapper<int(int, ...) const volatile && noexcept>();

    test_is_not_reference_wrapper<void (*)()>();
    test_is_not_reference_wrapper<void (*)() noexcept>();

    test_is_not_reference_wrapper<void (*)(int)>();
    test_is_not_reference_wrapper<void (*)(int) noexcept>();

    test_is_not_reference_wrapper<void (*)(...)>();
    test_is_not_reference_wrapper<void (*)(...) noexcept>();

    test_is_not_reference_wrapper<void (*)(int, ...)>();
    test_is_not_reference_wrapper<void (*)(int, ...) noexcept>();

    test_is_not_reference_wrapper<int (*)()>();
    test_is_not_reference_wrapper<int (*)() noexcept>();

    test_is_not_reference_wrapper<int (*)(int)>();
    test_is_not_reference_wrapper<int (*)(int) noexcept>();

    test_is_not_reference_wrapper<int (*)(...)>();
    test_is_not_reference_wrapper<int (*)(...) noexcept>();

    test_is_not_reference_wrapper<int (*)(int, ...)>();
    test_is_not_reference_wrapper<int (*)(int, ...) noexcept>();

    test_is_not_reference_wrapper<void (&)()>();
    test_is_not_reference_wrapper<void (&)() noexcept>();

    test_is_not_reference_wrapper<void (&)(int)>();
    test_is_not_reference_wrapper<void (&)(int) noexcept>();

    test_is_not_reference_wrapper<void (&)(...)>();
    test_is_not_reference_wrapper<void (&)(...) noexcept>();

    test_is_not_reference_wrapper<void (&)(int, ...)>();
    test_is_not_reference_wrapper<void (&)(int, ...) noexcept>();

    test_is_not_reference_wrapper<int (&)()>();
    test_is_not_reference_wrapper<int (&)() noexcept>();

    test_is_not_reference_wrapper<int (&)(int)>();
    test_is_not_reference_wrapper<int (&)(int) noexcept>();

    test_is_not_reference_wrapper<int (&)(...)>();
    test_is_not_reference_wrapper<int (&)(...) noexcept>();

    test_is_not_reference_wrapper<int (&)(int, ...)>();
    test_is_not_reference_wrapper<int (&)(int, ...) noexcept>();

    test_is_not_reference_wrapper<void (&&)()>();
    test_is_not_reference_wrapper<void (&&)() noexcept>();

    test_is_not_reference_wrapper<void (&&)(int)>();
    test_is_not_reference_wrapper<void (&&)(int) noexcept>();

    test_is_not_reference_wrapper<void (&&)(...)>();
    test_is_not_reference_wrapper<void (&&)(...) noexcept>();

    test_is_not_reference_wrapper<void (&&)(int, ...)>();
    test_is_not_reference_wrapper<void (&&)(int, ...) noexcept>();

    test_is_not_reference_wrapper<int (&&)()>();
    test_is_not_reference_wrapper<int (&&)() noexcept>();

    test_is_not_reference_wrapper<int (&&)(int)>();
    test_is_not_reference_wrapper<int (&&)(int) noexcept>();

    test_is_not_reference_wrapper<int (&&)(...)>();
    test_is_not_reference_wrapper<int (&&)(...) noexcept>();

    test_is_not_reference_wrapper<int (&&)(int, ...)>();
    test_is_not_reference_wrapper<int (&&)(int, ...) noexcept>();

    test_is_not_reference_wrapper<void (class_type::*)()>();
    test_is_not_reference_wrapper<void (class_type::*)()&>();
    test_is_not_reference_wrapper<void (class_type::*)() &&>();
    test_is_not_reference_wrapper<void (class_type::*)() const>();
    test_is_not_reference_wrapper<void (class_type::*)() const&>();
    test_is_not_reference_wrapper<void (class_type::*)() const&&>();
    test_is_not_reference_wrapper<void (class_type::*)() noexcept>();
    test_is_not_reference_wrapper<void (class_type::*)() & noexcept>();
    test_is_not_reference_wrapper<void (class_type::*)() && noexcept>();
    test_is_not_reference_wrapper<void (class_type::*)() const noexcept>();
    test_is_not_reference_wrapper<void (class_type::*)() const & noexcept>();
    test_is_not_reference_wrapper<void (class_type::*)() const && noexcept>();

    test_is_not_reference_wrapper<void (class_type::*)(int)>();
    test_is_not_reference_wrapper<void (class_type::*)(int)&>();
    test_is_not_reference_wrapper<void (class_type::*)(int) &&>();
    test_is_not_reference_wrapper<void (class_type::*)(int) const>();
    test_is_not_reference_wrapper<void (class_type::*)(int) const&>();
    test_is_not_reference_wrapper<void (class_type::*)(int) const&&>();
    test_is_not_reference_wrapper<void (class_type::*)(int) noexcept>();
    test_is_not_reference_wrapper<void (class_type::*)(int) & noexcept>();
    test_is_not_reference_wrapper<void (class_type::*)(int) && noexcept>();
    test_is_not_reference_wrapper<void (class_type::*)(int) const noexcept>();
    test_is_not_reference_wrapper<void (class_type::*)(int) const & noexcept>();
    test_is_not_reference_wrapper<void (class_type::*)(int) const && noexcept>();

    test_is_not_reference_wrapper<void (class_type::*)(...)>();
    test_is_not_reference_wrapper<void (class_type::*)(...)&>();
    test_is_not_reference_wrapper<void (class_type::*)(...) &&>();
    test_is_not_reference_wrapper<void (class_type::*)(...) const>();
    test_is_not_reference_wrapper<void (class_type::*)(...) const&>();
    test_is_not_reference_wrapper<void (class_type::*)(...) const&&>();
    test_is_not_reference_wrapper<void (class_type::*)(...) noexcept>();
    test_is_not_reference_wrapper<void (class_type::*)(...) & noexcept>();
    test_is_not_reference_wrapper<void (class_type::*)(...) && noexcept>();
    test_is_not_reference_wrapper<void (class_type::*)(...) const noexcept>();
    test_is_not_reference_wrapper<void (class_type::*)(...) const & noexcept>();
    test_is_not_reference_wrapper<void (class_type::*)(...) const && noexcept>();

    test_is_not_reference_wrapper<void (class_type::*)(int, ...)>();
    test_is_not_reference_wrapper<void (class_type::*)(int, ...)&>();
    test_is_not_reference_wrapper<void (class_type::*)(int, ...) &&>();
    test_is_not_reference_wrapper<void (class_type::*)(int, ...) const>();
    test_is_not_reference_wrapper<void (class_type::*)(int, ...) const&>();
    test_is_not_reference_wrapper<void (class_type::*)(int, ...) const&&>();
    test_is_not_reference_wrapper<void (class_type::*)(int, ...) noexcept>();
    test_is_not_reference_wrapper<void (class_type::*)(int, ...) & noexcept>();
    test_is_not_reference_wrapper<void (class_type::*)(int, ...) && noexcept>();
    test_is_not_reference_wrapper<void (class_type::*)(int, ...) const noexcept>();
    test_is_not_reference_wrapper<void (class_type::*)(int, ...) const & noexcept>();
    test_is_not_reference_wrapper<void (class_type::*)(int, ...) const && noexcept>();

    test_is_not_reference_wrapper<int (class_type::*)()>();
    test_is_not_reference_wrapper<int (class_type::*)()&>();
    test_is_not_reference_wrapper<int (class_type::*)() &&>();
    test_is_not_reference_wrapper<int (class_type::*)() const>();
    test_is_not_reference_wrapper<int (class_type::*)() const&>();
    test_is_not_reference_wrapper<int (class_type::*)() const&&>();
    test_is_not_reference_wrapper<int (class_type::*)() noexcept>();
    test_is_not_reference_wrapper<int (class_type::*)() & noexcept>();
    test_is_not_reference_wrapper<int (class_type::*)() && noexcept>();
    test_is_not_reference_wrapper<int (class_type::*)() const noexcept>();
    test_is_not_reference_wrapper<int (class_type::*)() const & noexcept>();
    test_is_not_reference_wrapper<int (class_type::*)() const && noexcept>();

    test_is_not_reference_wrapper<int (class_type::*)(int)>();
    test_is_not_reference_wrapper<int (class_type::*)(int)&>();
    test_is_not_reference_wrapper<int (class_type::*)(int) &&>();
    test_is_not_reference_wrapper<int (class_type::*)(int) const>();
    test_is_not_reference_wrapper<int (class_type::*)(int) const&>();
    test_is_not_reference_wrapper<int (class_type::*)(int) const&&>();
    test_is_not_reference_wrapper<int (class_type::*)(int) noexcept>();
    test_is_not_reference_wrapper<int (class_type::*)(int) & noexcept>();
    test_is_not_reference_wrapper<int (class_type::*)(int) && noexcept>();
    test_is_not_reference_wrapper<int (class_type::*)(int) const noexcept>();
    test_is_not_reference_wrapper<int (class_type::*)(int) const & noexcept>();
    test_is_not_reference_wrapper<int (class_type::*)(int) const && noexcept>();

    test_is_not_reference_wrapper<int (class_type::*)(...)>();
    test_is_not_reference_wrapper<int (class_type::*)(...)&>();
    test_is_not_reference_wrapper<int (class_type::*)(...) &&>();
    test_is_not_reference_wrapper<int (class_type::*)(...) const>();
    test_is_not_reference_wrapper<int (class_type::*)(...) const&>();
    test_is_not_reference_wrapper<int (class_type::*)(...) const&&>();
    test_is_not_reference_wrapper<int (class_type::*)(...) noexcept>();
    test_is_not_reference_wrapper<int (class_type::*)(...) & noexcept>();
    test_is_not_reference_wrapper<int (class_type::*)(...) && noexcept>();
    test_is_not_reference_wrapper<int (class_type::*)(...) const noexcept>();
    test_is_not_reference_wrapper<int (class_type::*)(...) const & noexcept>();
    test_is_not_reference_wrapper<int (class_type::*)(...) const && noexcept>();

    test_is_not_reference_wrapper<int (class_type::*)(int, ...)>();
    test_is_not_reference_wrapper<int (class_type::*)(int, ...)&>();
    test_is_not_reference_wrapper<int (class_type::*)(int, ...) &&>();
    test_is_not_reference_wrapper<int (class_type::*)(int, ...) const>();
    test_is_not_reference_wrapper<int (class_type::*)(int, ...) const&>();
    test_is_not_reference_wrapper<int (class_type::*)(int, ...) const&&>();
    test_is_not_reference_wrapper<int (class_type::*)(int, ...) noexcept>();
    test_is_not_reference_wrapper<int (class_type::*)(int, ...) & noexcept>();
    test_is_not_reference_wrapper<int (class_type::*)(int, ...) && noexcept>();
    test_is_not_reference_wrapper<int (class_type::*)(int, ...) const noexcept>();
    test_is_not_reference_wrapper<int (class_type::*)(int, ...) const & noexcept>();
    test_is_not_reference_wrapper<int (class_type::*)(int, ...) const && noexcept>();
}
