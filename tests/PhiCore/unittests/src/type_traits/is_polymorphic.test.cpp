#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_polymorphic.hpp>
#include <phi/type_traits/is_union.hpp>
#include <type_traits>
#include <vector>

template <typename TypeT>
void test_is_polymorphic_impl()
{
    STATIC_REQUIRE(phi::is_polymorphic<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_polymorphic<TypeT>::value);
#if PHI_HAS_WORKING_IS_UNION()
    STATIC_REQUIRE_FALSE(phi::is_union<TypeT>::value);
#endif

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_polymorphic_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_not_polymorphic_v<TypeT>);
#    if PHI_HAS_WORKING_IS_UNION()
    STATIC_REQUIRE_FALSE(phi::is_union_v<TypeT>);
#    endif
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_polymorphic<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_polymorphic<TypeT>);

    // Standard compatibility
    STATIC_REQUIRE(std::is_polymorphic<TypeT>::value);
}

template <typename TypeT>
void test_is_not_polymorphic_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_polymorphic<TypeT>::value);
    STATIC_REQUIRE(phi::is_not_polymorphic<TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_polymorphic_v<TypeT>);
    STATIC_REQUIRE(phi::is_not_polymorphic_v<TypeT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_polymorphic<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_polymorphic<TypeT>);

    // Standard compatibility
    STATIC_REQUIRE_FALSE(std::is_polymorphic<TypeT>::value);
}

template <typename TypeT>
void test_is_polymorphic()
{
    test_is_polymorphic_impl<TypeT>();
    test_is_polymorphic_impl<const TypeT>();
    test_is_polymorphic_impl<volatile TypeT>();
    test_is_polymorphic_impl<const volatile TypeT>();
}

template <typename TypeT>
void test_is_not_polymorphic()
{
    test_is_not_polymorphic_impl<TypeT>();
    test_is_not_polymorphic_impl<const TypeT>();
    test_is_not_polymorphic_impl<volatile TypeT>();
    test_is_not_polymorphic_impl<const volatile TypeT>();
}

TEST_CASE("is_polymorphic")
{
    test_is_not_polymorphic<not_empty&>();
    test_is_not_polymorphic<not_empty&&>();
    test_is_not_polymorphic<abstract&>();
    test_is_not_polymorphic<abstract&&>();

    test_is_not_polymorphic<void>();
    test_is_not_polymorphic<phi::nullptr_t>();
    test_is_not_polymorphic<bool>();
    test_is_not_polymorphic<char>();
    test_is_not_polymorphic<signed char>();
    test_is_not_polymorphic<unsigned char>();
    test_is_not_polymorphic<short>();
    test_is_not_polymorphic<unsigned short>();
    test_is_not_polymorphic<int>();
    test_is_not_polymorphic<unsigned int>();
    test_is_not_polymorphic<long>();
    test_is_not_polymorphic<unsigned long>();
    test_is_not_polymorphic<long long>();
    test_is_not_polymorphic<unsigned long long>();
    test_is_not_polymorphic<float>();
    test_is_not_polymorphic<double>();
    test_is_not_polymorphic<long double>();
    test_is_not_polymorphic<char8_t>();
    test_is_not_polymorphic<char16_t>();
    test_is_not_polymorphic<char32_t>();
    test_is_not_polymorphic<wchar_t>();

    test_is_not_polymorphic<phi::boolean>();
    test_is_not_polymorphic<phi::integer<signed char>>();
    test_is_not_polymorphic<phi::integer<unsigned char>>();
    test_is_not_polymorphic<phi::integer<short>>();
    test_is_not_polymorphic<phi::integer<unsigned short>>();
    test_is_not_polymorphic<phi::integer<int>>();
    test_is_not_polymorphic<phi::integer<unsigned int>>();
    test_is_not_polymorphic<phi::integer<long>>();
    test_is_not_polymorphic<phi::integer<unsigned long>>();
    test_is_not_polymorphic<phi::integer<long long>>();
    test_is_not_polymorphic<phi::integer<unsigned long long>>();
    test_is_not_polymorphic<phi::floating_point<float>>();
    test_is_not_polymorphic<phi::floating_point<double>>();
    test_is_not_polymorphic<phi::floating_point<long double>>();

    test_is_not_polymorphic<std::vector<int>>();
    test_is_not_polymorphic<phi::scope_ptr<int>>();

    test_is_not_polymorphic<int&>();
    test_is_not_polymorphic<const int&>();
    test_is_not_polymorphic<volatile int&>();
    test_is_not_polymorphic<const volatile int&>();
    test_is_not_polymorphic<int&&>();
    test_is_not_polymorphic<const int&&>();
    test_is_not_polymorphic<volatile int&&>();
    test_is_not_polymorphic<const volatile int&&>();
    test_is_not_polymorphic<int*>();
    test_is_not_polymorphic<const int*>();
    test_is_not_polymorphic<volatile int*>();
    test_is_not_polymorphic<const volatile int*>();
    test_is_not_polymorphic<int**>();
    test_is_not_polymorphic<const int**>();
    test_is_not_polymorphic<volatile int**>();
    test_is_not_polymorphic<const volatile int**>();
    test_is_not_polymorphic<int*&>();
    test_is_not_polymorphic<const int*&>();
    test_is_not_polymorphic<volatile int*&>();
    test_is_not_polymorphic<const volatile int*&>();
    test_is_not_polymorphic<int*&&>();
    test_is_not_polymorphic<const int*&&>();
    test_is_not_polymorphic<volatile int*&&>();
    test_is_not_polymorphic<const volatile int*&&>();
    test_is_not_polymorphic<void*>();
    test_is_not_polymorphic<char[3]>();
    test_is_not_polymorphic<char[]>();
    test_is_not_polymorphic<char* [3]>();
    test_is_not_polymorphic<char*[]>();
    test_is_not_polymorphic<int(*)[3]>();
    test_is_not_polymorphic<int(*)[]>();
    test_is_not_polymorphic<int(&)[3]>();
    test_is_not_polymorphic<int(&)[]>();
    test_is_not_polymorphic<int(&&)[3]>();
    test_is_not_polymorphic<int(&&)[]>();
    test_is_not_polymorphic<char[3][2]>();
    test_is_not_polymorphic<char[][2]>();
    test_is_not_polymorphic<char* [3][2]>();
    test_is_not_polymorphic<char*[][2]>();
    test_is_not_polymorphic<int(*)[3][2]>();
    test_is_not_polymorphic<int(*)[][2]>();
    test_is_not_polymorphic<int(&)[3][2]>();
    test_is_not_polymorphic<int(&)[][2]>();
    test_is_not_polymorphic<int(&&)[3][2]>();
    test_is_not_polymorphic<int(&&)[][2]>();
    test_is_not_polymorphic<class_type>();
    test_is_not_polymorphic<class_type[]>();
    test_is_not_polymorphic<class_type[2]>();
    test_is_not_polymorphic<template_type<void>>();
    test_is_not_polymorphic<template_type<int>>();
    test_is_not_polymorphic<template_type<class_type>>();
    test_is_not_polymorphic<template_type<incomplete_type>>();
    test_is_not_polymorphic<variadic_template<>>();
    test_is_not_polymorphic<variadic_template<void>>();
    test_is_not_polymorphic<variadic_template<int>>();
    test_is_not_polymorphic<variadic_template<class_type>>();
    test_is_not_polymorphic<variadic_template<incomplete_type>>();
    test_is_not_polymorphic<variadic_template<int, void, class_type, volatile char[]>>();
    test_is_not_polymorphic<public_derived_from<base>>();
    test_is_not_polymorphic<public_derived_from<derived>>();
    test_is_not_polymorphic<public_derived_from<class_type>>();
    test_is_not_polymorphic<private_derived_from<base>>();
    test_is_not_polymorphic<private_derived_from<derived>>();
    test_is_not_polymorphic<private_derived_from<class_type>>();
    test_is_not_polymorphic<protected_derived_from<base>>();
    test_is_not_polymorphic<protected_derived_from<derived>>();
    test_is_not_polymorphic<protected_derived_from<class_type>>();
    test_is_not_polymorphic<union_type>();
    test_is_not_polymorphic<non_empty_union>();
    test_is_not_polymorphic<empty>();
    test_is_polymorphic<not_empty>();
    test_is_not_polymorphic<bit_zero>();
    test_is_not_polymorphic<bit_one>();
    test_is_not_polymorphic<base>();
    test_is_not_polymorphic<derived>();
    test_is_polymorphic<abstract>();
    test_is_polymorphic<public_abstract>();
    test_is_polymorphic<private_abstract>();
    test_is_polymorphic<protected_abstract>();
    test_is_polymorphic<abstract_template<int>>();
    test_is_not_polymorphic<abstract_template<double>>();
    test_is_polymorphic<abstract_template<class_type>>();
    test_is_polymorphic<abstract_template<incomplete_type>>();
    test_is_not_polymorphic<final_type>();
    test_is_not_polymorphic<public_destructor>();
    test_is_not_polymorphic<protected_destructor>();
    test_is_not_polymorphic<private_destructor>();
    test_is_polymorphic<virtual_public_destructor>();
    test_is_polymorphic<virtual_protected_destructor>();
    test_is_polymorphic<virtual_private_destructor>();
    test_is_polymorphic<pure_public_destructor>();
    test_is_polymorphic<pure_protected_destructor>();
    test_is_polymorphic<pure_private_destructor>();
    test_is_not_polymorphic<deleted_public_destructor>();
    test_is_not_polymorphic<deleted_protected_destructor>();
    test_is_not_polymorphic<deleted_private_destructor>();
    test_is_polymorphic<deleted_virtual_public_destructor>();
    test_is_polymorphic<deleted_virtual_protected_destructor>();
    test_is_polymorphic<deleted_virtual_private_destructor>();
    test_is_not_polymorphic<Enum>();
    test_is_not_polymorphic<EnumSigned>();
    test_is_not_polymorphic<EnumUnsigned>();
    test_is_not_polymorphic<EnumClass>();
    test_is_not_polymorphic<EnumStruct>();
    test_is_not_polymorphic<function_type>();
    test_is_not_polymorphic<function_ptr>();
    test_is_not_polymorphic<member_object_ptr>();
    test_is_not_polymorphic<member_function_ptr>();
    test_is_not_polymorphic<int class_type::*>();
    test_is_not_polymorphic<float class_type::*>();
    test_is_not_polymorphic<void * class_type::*>();
    test_is_not_polymorphic<int * class_type::*>();
    test_is_not_polymorphic<int class_type::*&>();
    test_is_not_polymorphic<float class_type::*&>();
    test_is_not_polymorphic<void * class_type::*&>();
    test_is_not_polymorphic<int * class_type::*&>();
    test_is_not_polymorphic<int class_type::*&&>();
    test_is_not_polymorphic<float class_type::*&&>();
    test_is_not_polymorphic<void * class_type::*&&>();
    test_is_not_polymorphic<int * class_type::*&&>();
    test_is_not_polymorphic<int class_type::* const>();
    test_is_not_polymorphic<float class_type::* const>();
    test_is_not_polymorphic<void * class_type::* const>();
    test_is_not_polymorphic<int class_type::* const&>();
    test_is_not_polymorphic<float class_type::* const&>();
    test_is_not_polymorphic<void * class_type::* const&>();
    test_is_not_polymorphic<int class_type::* const&&>();
    test_is_not_polymorphic<float class_type::* const&&>();
    test_is_not_polymorphic<void * class_type::* const&&>();
    test_is_not_polymorphic<int class_type::* volatile>();
    test_is_not_polymorphic<float class_type::* volatile>();
    test_is_not_polymorphic<void * class_type::* volatile>();
    test_is_not_polymorphic<int class_type::* volatile&>();
    test_is_not_polymorphic<float class_type::* volatile&>();
    test_is_not_polymorphic<void * class_type::* volatile&>();
    test_is_not_polymorphic<int class_type::* volatile&&>();
    test_is_not_polymorphic<float class_type::* volatile&&>();
    test_is_not_polymorphic<void * class_type::* volatile&&>();
    test_is_not_polymorphic<int class_type::* const volatile>();
    test_is_not_polymorphic<float class_type::* const volatile>();
    test_is_not_polymorphic<void * class_type::* const volatile>();
    test_is_not_polymorphic<int class_type::* const volatile&>();
    test_is_not_polymorphic<float class_type::* const volatile&>();
    test_is_not_polymorphic<void * class_type::* const volatile&>();
    test_is_not_polymorphic<int class_type::* const volatile&&>();
    test_is_not_polymorphic<float class_type::* const volatile&&>();
    test_is_not_polymorphic<void * class_type::* const volatile&&>();
    test_is_not_polymorphic<non_copyable>();
    test_is_not_polymorphic<non_moveable>();
    test_is_not_polymorphic<non_constructible>();
    test_is_not_polymorphic<tracked>();
    test_is_not_polymorphic<trap_constructible>();
    test_is_not_polymorphic<trap_implicit_conversion>();
    test_is_not_polymorphic<trap_comma>();
    test_is_not_polymorphic<trap_call>();
    test_is_not_polymorphic<trap_self_assign>();
    test_is_not_polymorphic<trap_deref>();
    test_is_not_polymorphic<trap_array_subscript>();

    test_is_not_polymorphic<void()>();
    test_is_not_polymorphic<void()&>();
    test_is_not_polymorphic<void() &&>();
    test_is_not_polymorphic<void() const>();
    test_is_not_polymorphic<void() const&>();
    test_is_not_polymorphic<void() const&&>();
    test_is_not_polymorphic<void() volatile>();
    test_is_not_polymorphic<void() volatile&>();
    test_is_not_polymorphic<void() volatile&&>();
    test_is_not_polymorphic<void() const volatile>();
    test_is_not_polymorphic<void() const volatile&>();
    test_is_not_polymorphic<void() const volatile&&>();
    test_is_not_polymorphic<void() noexcept>();
    test_is_not_polymorphic<void() & noexcept>();
    test_is_not_polymorphic<void() && noexcept>();
    test_is_not_polymorphic<void() const noexcept>();
    test_is_not_polymorphic<void() const & noexcept>();
    test_is_not_polymorphic<void() const && noexcept>();
    test_is_not_polymorphic<void() volatile noexcept>();
    test_is_not_polymorphic<void() volatile & noexcept>();
    test_is_not_polymorphic<void() volatile && noexcept>();
    test_is_not_polymorphic<void() const volatile noexcept>();
    test_is_not_polymorphic<void() const volatile & noexcept>();
    test_is_not_polymorphic<void() const volatile && noexcept>();

    test_is_not_polymorphic<void(int)>();
    test_is_not_polymorphic<void(int)&>();
    test_is_not_polymorphic<void(int) &&>();
    test_is_not_polymorphic<void(int) const>();
    test_is_not_polymorphic<void(int) const&>();
    test_is_not_polymorphic<void(int) const&&>();
    test_is_not_polymorphic<void(int) volatile>();
    test_is_not_polymorphic<void(int) volatile&>();
    test_is_not_polymorphic<void(int) volatile&&>();
    test_is_not_polymorphic<void(int) const volatile>();
    test_is_not_polymorphic<void(int) const volatile&>();
    test_is_not_polymorphic<void(int) const volatile&&>();
    test_is_not_polymorphic<void(int) noexcept>();
    test_is_not_polymorphic<void(int) & noexcept>();
    test_is_not_polymorphic<void(int) && noexcept>();
    test_is_not_polymorphic<void(int) const noexcept>();
    test_is_not_polymorphic<void(int) const & noexcept>();
    test_is_not_polymorphic<void(int) const && noexcept>();
    test_is_not_polymorphic<void(int) volatile noexcept>();
    test_is_not_polymorphic<void(int) volatile & noexcept>();
    test_is_not_polymorphic<void(int) volatile && noexcept>();
    test_is_not_polymorphic<void(int) const volatile noexcept>();
    test_is_not_polymorphic<void(int) const volatile & noexcept>();
    test_is_not_polymorphic<void(int) const volatile && noexcept>();

    test_is_not_polymorphic<void(...)>();
    test_is_not_polymorphic<void(...)&>();
    test_is_not_polymorphic<void(...) &&>();
    test_is_not_polymorphic<void(...) const>();
    test_is_not_polymorphic<void(...) const&>();
    test_is_not_polymorphic<void(...) const&&>();
    test_is_not_polymorphic<void(...) volatile>();
    test_is_not_polymorphic<void(...) volatile&>();
    test_is_not_polymorphic<void(...) volatile&&>();
    test_is_not_polymorphic<void(...) const volatile>();
    test_is_not_polymorphic<void(...) const volatile&>();
    test_is_not_polymorphic<void(...) const volatile&&>();
    test_is_not_polymorphic<void(...) noexcept>();
    test_is_not_polymorphic<void(...) & noexcept>();
    test_is_not_polymorphic<void(...) && noexcept>();
    test_is_not_polymorphic<void(...) const noexcept>();
    test_is_not_polymorphic<void(...) const & noexcept>();
    test_is_not_polymorphic<void(...) const && noexcept>();
    test_is_not_polymorphic<void(...) volatile noexcept>();
    test_is_not_polymorphic<void(...) volatile & noexcept>();
    test_is_not_polymorphic<void(...) volatile && noexcept>();
    test_is_not_polymorphic<void(...) const volatile noexcept>();
    test_is_not_polymorphic<void(...) const volatile & noexcept>();
    test_is_not_polymorphic<void(...) const volatile && noexcept>();

    test_is_not_polymorphic<void(int, ...)>();
    test_is_not_polymorphic<void(int, ...)&>();
    test_is_not_polymorphic<void(int, ...) &&>();
    test_is_not_polymorphic<void(int, ...) const>();
    test_is_not_polymorphic<void(int, ...) const&>();
    test_is_not_polymorphic<void(int, ...) const&&>();
    test_is_not_polymorphic<void(int, ...) volatile>();
    test_is_not_polymorphic<void(int, ...) volatile&>();
    test_is_not_polymorphic<void(int, ...) volatile&&>();
    test_is_not_polymorphic<void(int, ...) const volatile>();
    test_is_not_polymorphic<void(int, ...) const volatile&>();
    test_is_not_polymorphic<void(int, ...) const volatile&&>();
    test_is_not_polymorphic<void(int, ...) noexcept>();
    test_is_not_polymorphic<void(int, ...) & noexcept>();
    test_is_not_polymorphic<void(int, ...) && noexcept>();
    test_is_not_polymorphic<void(int, ...) const noexcept>();
    test_is_not_polymorphic<void(int, ...) const & noexcept>();
    test_is_not_polymorphic<void(int, ...) const && noexcept>();
    test_is_not_polymorphic<void(int, ...) volatile noexcept>();
    test_is_not_polymorphic<void(int, ...) volatile & noexcept>();
    test_is_not_polymorphic<void(int, ...) volatile && noexcept>();
    test_is_not_polymorphic<void(int, ...) const volatile noexcept>();
    test_is_not_polymorphic<void(int, ...) const volatile & noexcept>();
    test_is_not_polymorphic<void(int, ...) const volatile && noexcept>();

    test_is_not_polymorphic<int()>();
    test_is_not_polymorphic<int()&>();
    test_is_not_polymorphic<int() &&>();
    test_is_not_polymorphic<int() const>();
    test_is_not_polymorphic<int() const&>();
    test_is_not_polymorphic<int() const&&>();
    test_is_not_polymorphic<int() volatile>();
    test_is_not_polymorphic<int() volatile&>();
    test_is_not_polymorphic<int() volatile&&>();
    test_is_not_polymorphic<int() const volatile>();
    test_is_not_polymorphic<int() const volatile&>();
    test_is_not_polymorphic<int() const volatile&&>();
    test_is_not_polymorphic<int() noexcept>();
    test_is_not_polymorphic<int() & noexcept>();
    test_is_not_polymorphic<int() && noexcept>();
    test_is_not_polymorphic<int() const noexcept>();
    test_is_not_polymorphic<int() const & noexcept>();
    test_is_not_polymorphic<int() const && noexcept>();
    test_is_not_polymorphic<int() volatile noexcept>();
    test_is_not_polymorphic<int() volatile & noexcept>();
    test_is_not_polymorphic<int() volatile && noexcept>();
    test_is_not_polymorphic<int() const volatile noexcept>();
    test_is_not_polymorphic<int() const volatile & noexcept>();
    test_is_not_polymorphic<int() const volatile && noexcept>();

    test_is_not_polymorphic<int(int)>();
    test_is_not_polymorphic<int(int)&>();
    test_is_not_polymorphic<int(int) &&>();
    test_is_not_polymorphic<int(int) const>();
    test_is_not_polymorphic<int(int) const&>();
    test_is_not_polymorphic<int(int) const&&>();
    test_is_not_polymorphic<int(int) volatile>();
    test_is_not_polymorphic<int(int) volatile&>();
    test_is_not_polymorphic<int(int) volatile&&>();
    test_is_not_polymorphic<int(int) const volatile>();
    test_is_not_polymorphic<int(int) const volatile&>();
    test_is_not_polymorphic<int(int) const volatile&&>();
    test_is_not_polymorphic<int(int) noexcept>();
    test_is_not_polymorphic<int(int) & noexcept>();
    test_is_not_polymorphic<int(int) && noexcept>();
    test_is_not_polymorphic<int(int) const noexcept>();
    test_is_not_polymorphic<int(int) const & noexcept>();
    test_is_not_polymorphic<int(int) const && noexcept>();
    test_is_not_polymorphic<int(int) volatile noexcept>();
    test_is_not_polymorphic<int(int) volatile & noexcept>();
    test_is_not_polymorphic<int(int) volatile && noexcept>();
    test_is_not_polymorphic<int(int) const volatile noexcept>();
    test_is_not_polymorphic<int(int) const volatile & noexcept>();
    test_is_not_polymorphic<int(int) const volatile && noexcept>();

    test_is_not_polymorphic<int(...)>();
    test_is_not_polymorphic<int(...)&>();
    test_is_not_polymorphic<int(...) &&>();
    test_is_not_polymorphic<int(...) const>();
    test_is_not_polymorphic<int(...) const&>();
    test_is_not_polymorphic<int(...) const&&>();
    test_is_not_polymorphic<int(...) volatile>();
    test_is_not_polymorphic<int(...) volatile&>();
    test_is_not_polymorphic<int(...) volatile&&>();
    test_is_not_polymorphic<int(...) const volatile>();
    test_is_not_polymorphic<int(...) const volatile&>();
    test_is_not_polymorphic<int(...) const volatile&&>();
    test_is_not_polymorphic<int(...) noexcept>();
    test_is_not_polymorphic<int(...) & noexcept>();
    test_is_not_polymorphic<int(...) && noexcept>();
    test_is_not_polymorphic<int(...) const noexcept>();
    test_is_not_polymorphic<int(...) const & noexcept>();
    test_is_not_polymorphic<int(...) const && noexcept>();
    test_is_not_polymorphic<int(...) volatile noexcept>();
    test_is_not_polymorphic<int(...) volatile & noexcept>();
    test_is_not_polymorphic<int(...) volatile && noexcept>();
    test_is_not_polymorphic<int(...) const volatile noexcept>();
    test_is_not_polymorphic<int(...) const volatile & noexcept>();
    test_is_not_polymorphic<int(...) const volatile && noexcept>();

    test_is_not_polymorphic<int(int, ...)>();
    test_is_not_polymorphic<int(int, ...)&>();
    test_is_not_polymorphic<int(int, ...) &&>();
    test_is_not_polymorphic<int(int, ...) const>();
    test_is_not_polymorphic<int(int, ...) const&>();
    test_is_not_polymorphic<int(int, ...) const&&>();
    test_is_not_polymorphic<int(int, ...) volatile>();
    test_is_not_polymorphic<int(int, ...) volatile&>();
    test_is_not_polymorphic<int(int, ...) volatile&&>();
    test_is_not_polymorphic<int(int, ...) const volatile>();
    test_is_not_polymorphic<int(int, ...) const volatile&>();
    test_is_not_polymorphic<int(int, ...) const volatile&&>();
    test_is_not_polymorphic<int(int, ...) noexcept>();
    test_is_not_polymorphic<int(int, ...) & noexcept>();
    test_is_not_polymorphic<int(int, ...) && noexcept>();
    test_is_not_polymorphic<int(int, ...) const noexcept>();
    test_is_not_polymorphic<int(int, ...) const & noexcept>();
    test_is_not_polymorphic<int(int, ...) const && noexcept>();
    test_is_not_polymorphic<int(int, ...) volatile noexcept>();
    test_is_not_polymorphic<int(int, ...) volatile & noexcept>();
    test_is_not_polymorphic<int(int, ...) volatile && noexcept>();
    test_is_not_polymorphic<int(int, ...) const volatile noexcept>();
    test_is_not_polymorphic<int(int, ...) const volatile & noexcept>();
    test_is_not_polymorphic<int(int, ...) const volatile && noexcept>();

    test_is_not_polymorphic<void (*)()>();
    test_is_not_polymorphic<void (*)() noexcept>();

    test_is_not_polymorphic<void (*)(int)>();
    test_is_not_polymorphic<void (*)(int) noexcept>();

    test_is_not_polymorphic<void (*)(...)>();
    test_is_not_polymorphic<void (*)(...) noexcept>();

    test_is_not_polymorphic<void (*)(int, ...)>();
    test_is_not_polymorphic<void (*)(int, ...) noexcept>();

    test_is_not_polymorphic<int (*)()>();
    test_is_not_polymorphic<int (*)() noexcept>();

    test_is_not_polymorphic<int (*)(int)>();
    test_is_not_polymorphic<int (*)(int) noexcept>();

    test_is_not_polymorphic<int (*)(...)>();
    test_is_not_polymorphic<int (*)(...) noexcept>();

    test_is_not_polymorphic<int (*)(int, ...)>();
    test_is_not_polymorphic<int (*)(int, ...) noexcept>();

    test_is_not_polymorphic<void (&)()>();
    test_is_not_polymorphic<void (&)() noexcept>();

    test_is_not_polymorphic<void (&)(int)>();
    test_is_not_polymorphic<void (&)(int) noexcept>();

    test_is_not_polymorphic<void (&)(...)>();
    test_is_not_polymorphic<void (&)(...) noexcept>();

    test_is_not_polymorphic<void (&)(int, ...)>();
    test_is_not_polymorphic<void (&)(int, ...) noexcept>();

    test_is_not_polymorphic<int (&)()>();
    test_is_not_polymorphic<int (&)() noexcept>();

    test_is_not_polymorphic<int (&)(int)>();
    test_is_not_polymorphic<int (&)(int) noexcept>();

    test_is_not_polymorphic<int (&)(...)>();
    test_is_not_polymorphic<int (&)(...) noexcept>();

    test_is_not_polymorphic<int (&)(int, ...)>();
    test_is_not_polymorphic<int (&)(int, ...) noexcept>();

    test_is_not_polymorphic<void (&&)()>();
    test_is_not_polymorphic<void (&&)() noexcept>();

    test_is_not_polymorphic<void (&&)(int)>();
    test_is_not_polymorphic<void (&&)(int) noexcept>();

    test_is_not_polymorphic<void (&&)(...)>();
    test_is_not_polymorphic<void (&&)(...) noexcept>();

    test_is_not_polymorphic<void (&&)(int, ...)>();
    test_is_not_polymorphic<void (&&)(int, ...) noexcept>();

    test_is_not_polymorphic<int (&&)()>();
    test_is_not_polymorphic<int (&&)() noexcept>();

    test_is_not_polymorphic<int (&&)(int)>();
    test_is_not_polymorphic<int (&&)(int) noexcept>();

    test_is_not_polymorphic<int (&&)(...)>();
    test_is_not_polymorphic<int (&&)(...) noexcept>();

    test_is_not_polymorphic<int (&&)(int, ...)>();
    test_is_not_polymorphic<int (&&)(int, ...) noexcept>();

    test_is_not_polymorphic<void (class_type::*)()>();
    test_is_not_polymorphic<void (class_type::*)()&>();
    test_is_not_polymorphic<void (class_type::*)() &&>();
    test_is_not_polymorphic<void (class_type::*)() const>();
    test_is_not_polymorphic<void (class_type::*)() const&>();
    test_is_not_polymorphic<void (class_type::*)() const&&>();
    test_is_not_polymorphic<void (class_type::*)() noexcept>();
    test_is_not_polymorphic<void (class_type::*)() & noexcept>();
    test_is_not_polymorphic<void (class_type::*)() && noexcept>();
    test_is_not_polymorphic<void (class_type::*)() const noexcept>();
    test_is_not_polymorphic<void (class_type::*)() const & noexcept>();
    test_is_not_polymorphic<void (class_type::*)() const && noexcept>();

    test_is_not_polymorphic<void (class_type::*)(int)>();
    test_is_not_polymorphic<void (class_type::*)(int)&>();
    test_is_not_polymorphic<void (class_type::*)(int) &&>();
    test_is_not_polymorphic<void (class_type::*)(int) const>();
    test_is_not_polymorphic<void (class_type::*)(int) const&>();
    test_is_not_polymorphic<void (class_type::*)(int) const&&>();
    test_is_not_polymorphic<void (class_type::*)(int) noexcept>();
    test_is_not_polymorphic<void (class_type::*)(int) & noexcept>();
    test_is_not_polymorphic<void (class_type::*)(int) && noexcept>();
    test_is_not_polymorphic<void (class_type::*)(int) const noexcept>();
    test_is_not_polymorphic<void (class_type::*)(int) const & noexcept>();
    test_is_not_polymorphic<void (class_type::*)(int) const && noexcept>();

    test_is_not_polymorphic<void (class_type::*)(...)>();
    test_is_not_polymorphic<void (class_type::*)(...)&>();
    test_is_not_polymorphic<void (class_type::*)(...) &&>();
    test_is_not_polymorphic<void (class_type::*)(...) const>();
    test_is_not_polymorphic<void (class_type::*)(...) const&>();
    test_is_not_polymorphic<void (class_type::*)(...) const&&>();
    test_is_not_polymorphic<void (class_type::*)(...) noexcept>();
    test_is_not_polymorphic<void (class_type::*)(...) & noexcept>();
    test_is_not_polymorphic<void (class_type::*)(...) && noexcept>();
    test_is_not_polymorphic<void (class_type::*)(...) const noexcept>();
    test_is_not_polymorphic<void (class_type::*)(...) const & noexcept>();
    test_is_not_polymorphic<void (class_type::*)(...) const && noexcept>();

    test_is_not_polymorphic<void (class_type::*)(int, ...)>();
    test_is_not_polymorphic<void (class_type::*)(int, ...)&>();
    test_is_not_polymorphic<void (class_type::*)(int, ...) &&>();
    test_is_not_polymorphic<void (class_type::*)(int, ...) const>();
    test_is_not_polymorphic<void (class_type::*)(int, ...) const&>();
    test_is_not_polymorphic<void (class_type::*)(int, ...) const&&>();
    test_is_not_polymorphic<void (class_type::*)(int, ...) noexcept>();
    test_is_not_polymorphic<void (class_type::*)(int, ...) & noexcept>();
    test_is_not_polymorphic<void (class_type::*)(int, ...) && noexcept>();
    test_is_not_polymorphic<void (class_type::*)(int, ...) const noexcept>();
    test_is_not_polymorphic<void (class_type::*)(int, ...) const & noexcept>();
    test_is_not_polymorphic<void (class_type::*)(int, ...) const && noexcept>();

    test_is_not_polymorphic<int (class_type::*)()>();
    test_is_not_polymorphic<int (class_type::*)()&>();
    test_is_not_polymorphic<int (class_type::*)() &&>();
    test_is_not_polymorphic<int (class_type::*)() const>();
    test_is_not_polymorphic<int (class_type::*)() const&>();
    test_is_not_polymorphic<int (class_type::*)() const&&>();
    test_is_not_polymorphic<int (class_type::*)() noexcept>();
    test_is_not_polymorphic<int (class_type::*)() & noexcept>();
    test_is_not_polymorphic<int (class_type::*)() && noexcept>();
    test_is_not_polymorphic<int (class_type::*)() const noexcept>();
    test_is_not_polymorphic<int (class_type::*)() const & noexcept>();
    test_is_not_polymorphic<int (class_type::*)() const && noexcept>();

    test_is_not_polymorphic<int (class_type::*)(int)>();
    test_is_not_polymorphic<int (class_type::*)(int)&>();
    test_is_not_polymorphic<int (class_type::*)(int) &&>();
    test_is_not_polymorphic<int (class_type::*)(int) const>();
    test_is_not_polymorphic<int (class_type::*)(int) const&>();
    test_is_not_polymorphic<int (class_type::*)(int) const&&>();
    test_is_not_polymorphic<int (class_type::*)(int) noexcept>();
    test_is_not_polymorphic<int (class_type::*)(int) & noexcept>();
    test_is_not_polymorphic<int (class_type::*)(int) && noexcept>();
    test_is_not_polymorphic<int (class_type::*)(int) const noexcept>();
    test_is_not_polymorphic<int (class_type::*)(int) const & noexcept>();
    test_is_not_polymorphic<int (class_type::*)(int) const && noexcept>();

    test_is_not_polymorphic<int (class_type::*)(...)>();
    test_is_not_polymorphic<int (class_type::*)(...)&>();
    test_is_not_polymorphic<int (class_type::*)(...) &&>();
    test_is_not_polymorphic<int (class_type::*)(...) const>();
    test_is_not_polymorphic<int (class_type::*)(...) const&>();
    test_is_not_polymorphic<int (class_type::*)(...) const&&>();
    test_is_not_polymorphic<int (class_type::*)(...) noexcept>();
    test_is_not_polymorphic<int (class_type::*)(...) & noexcept>();
    test_is_not_polymorphic<int (class_type::*)(...) && noexcept>();
    test_is_not_polymorphic<int (class_type::*)(...) const noexcept>();
    test_is_not_polymorphic<int (class_type::*)(...) const & noexcept>();
    test_is_not_polymorphic<int (class_type::*)(...) const && noexcept>();

    test_is_not_polymorphic<int (class_type::*)(int, ...)>();
    test_is_not_polymorphic<int (class_type::*)(int, ...)&>();
    test_is_not_polymorphic<int (class_type::*)(int, ...) &&>();
    test_is_not_polymorphic<int (class_type::*)(int, ...) const>();
    test_is_not_polymorphic<int (class_type::*)(int, ...) const&>();
    test_is_not_polymorphic<int (class_type::*)(int, ...) const&&>();
    test_is_not_polymorphic<int (class_type::*)(int, ...) noexcept>();
    test_is_not_polymorphic<int (class_type::*)(int, ...) & noexcept>();
    test_is_not_polymorphic<int (class_type::*)(int, ...) && noexcept>();
    test_is_not_polymorphic<int (class_type::*)(int, ...) const noexcept>();
    test_is_not_polymorphic<int (class_type::*)(int, ...) const & noexcept>();
    test_is_not_polymorphic<int (class_type::*)(int, ...) const && noexcept>();
}
