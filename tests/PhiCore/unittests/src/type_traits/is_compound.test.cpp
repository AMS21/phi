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
#include <phi/type_traits/is_compound.hpp>
#include <type_traits>
#include <vector>

template <typename TypeT>
void test_is_compound_impl()
{
    STATIC_REQUIRE(phi::is_compound<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_compound<TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_compound_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_not_compound_v<TypeT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_compound<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_compound<TypeT>);

    // Standard compatibility
    STATIC_REQUIRE(std::is_compound<TypeT>::value);
}

template <typename TypeT>
void test_is_compound()
{
    test_is_compound_impl<TypeT>();
    test_is_compound_impl<const TypeT>();
    test_is_compound_impl<volatile TypeT>();
    test_is_compound_impl<const volatile TypeT>();
}

template <typename TypeT>
void test_is_not_compound_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_compound<TypeT>::value);
    STATIC_REQUIRE(phi::is_not_compound<TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_compound_v<TypeT>);
    STATIC_REQUIRE(phi::is_not_compound_v<TypeT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_compound<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_compound<TypeT>);

    // Standard compatibility
    STATIC_REQUIRE_FALSE(std::is_compound<TypeT>::value);
}

template <typename TypeT>
void test_is_not_compound()
{
    test_is_not_compound_impl<TypeT>();
    test_is_not_compound_impl<const TypeT>();
    test_is_not_compound_impl<volatile TypeT>();
    test_is_not_compound_impl<const volatile TypeT>();
}

TEST_CASE("is_compound")
{
    test_is_not_compound<void>();
    test_is_not_compound<phi::nullptr_t>();
    test_is_not_compound<bool>();
    test_is_not_compound<char>();
    test_is_not_compound<signed char>();
    test_is_not_compound<unsigned char>();
    test_is_not_compound<short>();
    test_is_not_compound<unsigned short>();
    test_is_not_compound<int>();
    test_is_not_compound<unsigned int>();
    test_is_not_compound<long>();
    test_is_not_compound<unsigned long>();
    test_is_not_compound<long long>();
    test_is_not_compound<unsigned long long>();
    test_is_not_compound<float>();
    test_is_not_compound<double>();
    test_is_not_compound<long double>();
    test_is_not_compound<char8_t>();
    test_is_not_compound<char16_t>();
    test_is_not_compound<char32_t>();
    test_is_not_compound<wchar_t>();

    test_is_compound<phi::boolean>();
    test_is_compound<phi::integer<signed char>>();
    test_is_compound<phi::integer<unsigned char>>();
    test_is_compound<phi::integer<short>>();
    test_is_compound<phi::integer<unsigned short>>();
    test_is_compound<phi::integer<int>>();
    test_is_compound<phi::integer<unsigned int>>();
    test_is_compound<phi::integer<long>>();
    test_is_compound<phi::integer<unsigned long>>();
    test_is_compound<phi::integer<long long>>();
    test_is_compound<phi::integer<unsigned long long>>();
    test_is_compound<phi::floating_point<float>>();
    test_is_compound<phi::floating_point<double>>();
    test_is_compound<phi::floating_point<long double>>();

    test_is_compound<std::vector<int>>();
    test_is_compound<phi::scope_ptr<int>>();

    test_is_compound<int&>();
    test_is_compound<const int&>();
    test_is_compound<volatile int&>();
    test_is_compound<const volatile int&>();
    test_is_compound<int&&>();
    test_is_compound<const int&&>();
    test_is_compound<volatile int&&>();
    test_is_compound<const volatile int&&>();
    test_is_compound<int*>();
    test_is_compound<const int*>();
    test_is_compound<volatile int*>();
    test_is_compound<const volatile int*>();
    test_is_compound<int**>();
    test_is_compound<const int**>();
    test_is_compound<volatile int**>();
    test_is_compound<const volatile int**>();
    test_is_compound<int*&>();
    test_is_compound<const int*&>();
    test_is_compound<volatile int*&>();
    test_is_compound<const volatile int*&>();
    test_is_compound<int*&&>();
    test_is_compound<const int*&&>();
    test_is_compound<volatile int*&&>();
    test_is_compound<const volatile int*&&>();
    test_is_compound<void*>();
    test_is_compound<char[3]>();
    test_is_compound<char[]>();
    test_is_compound<char* [3]>();
    test_is_compound<char*[]>();
    test_is_compound<int(*)[3]>();
    test_is_compound<int(*)[]>();
    test_is_compound<int(&)[3]>();
    test_is_compound<int(&)[]>();
    test_is_compound<int(&&)[3]>();
    test_is_compound<int(&&)[]>();
    test_is_compound<char[3][2]>();
    test_is_compound<char[][2]>();
    test_is_compound<char* [3][2]>();
    test_is_compound<char*[][2]>();
    test_is_compound<int(*)[3][2]>();
    test_is_compound<int(*)[][2]>();
    test_is_compound<int(&)[3][2]>();
    test_is_compound<int(&)[][2]>();
    test_is_compound<int(&&)[3][2]>();
    test_is_compound<int(&&)[][2]>();
    test_is_compound<class_type>();
    test_is_compound<class_type[]>();
    test_is_compound<class_type[2]>();
    test_is_compound<template_type<void>>();
    test_is_compound<template_type<int>>();
    test_is_compound<template_type<class_type>>();
    test_is_compound<template_type<incomplete_type>>();
    test_is_compound<variadic_template<>>();
    test_is_compound<variadic_template<void>>();
    test_is_compound<variadic_template<int>>();
    test_is_compound<variadic_template<class_type>>();
    test_is_compound<variadic_template<incomplete_type>>();
    test_is_compound<variadic_template<int, void, class_type, volatile char[]>>();
    test_is_compound<public_derived_from<base>>();
    test_is_compound<public_derived_from<derived>>();
    test_is_compound<public_derived_from<class_type>>();
    test_is_compound<private_derived_from<base>>();
    test_is_compound<private_derived_from<derived>>();
    test_is_compound<private_derived_from<class_type>>();
    test_is_compound<protected_derived_from<base>>();
    test_is_compound<protected_derived_from<derived>>();
    test_is_compound<protected_derived_from<class_type>>();
    test_is_compound<union_type>();
    test_is_compound<non_empty_union>();
    test_is_compound<empty>();
    test_is_compound<not_empty>();
    test_is_compound<bit_zero>();
    test_is_compound<bit_one>();
    test_is_compound<base>();
    test_is_compound<derived>();
    test_is_compound<abstract>();
    test_is_compound<public_abstract>();
    test_is_compound<private_abstract>();
    test_is_compound<protected_abstract>();
    test_is_compound<abstract_template<int>>();
    test_is_compound<abstract_template<double>>();
    test_is_compound<abstract_template<class_type>>();
    test_is_compound<abstract_template<incomplete_type>>();
    test_is_compound<final_type>();
    test_is_compound<public_destructor>();
    test_is_compound<protected_destructor>();
    test_is_compound<private_destructor>();
    test_is_compound<virtual_public_destructor>();
    test_is_compound<virtual_protected_destructor>();
    test_is_compound<virtual_private_destructor>();
    test_is_compound<pure_public_destructor>();
    test_is_compound<pure_protected_destructor>();
    test_is_compound<pure_private_destructor>();
    test_is_compound<deleted_public_destructor>();
    test_is_compound<deleted_protected_destructor>();
    test_is_compound<deleted_private_destructor>();
    test_is_compound<deleted_virtual_public_destructor>();
    test_is_compound<deleted_virtual_protected_destructor>();
    test_is_compound<deleted_virtual_private_destructor>();
    test_is_compound<Enum>();
    test_is_compound<EnumSigned>();
    test_is_compound<EnumUnsigned>();
    test_is_compound<EnumClass>();
    test_is_compound<EnumStruct>();
    test_is_compound<function_type>();
    test_is_compound<function_ptr>();
    test_is_compound<member_object_ptr>();
    test_is_compound<member_function_ptr>();
    test_is_compound<incomplete_type>();
    test_is_compound<incomplete_template<void>>();
    test_is_compound<incomplete_template<int>>();
    test_is_compound<incomplete_template<class_type>>();
    test_is_compound<incomplete_template<incomplete_type>>();
    test_is_compound<incomplete_variadic_template<>>();
    test_is_compound<incomplete_variadic_template<void>>();
    test_is_compound<incomplete_variadic_template<int>>();
    test_is_compound<incomplete_variadic_template<class_type>>();
    test_is_compound<incomplete_variadic_template<incomplete_type>>();
    test_is_compound<incomplete_variadic_template<int, void, class_type, volatile char[]>>();
    test_is_compound<int class_type::*>();
    test_is_compound<float class_type::*>();
    test_is_compound<void * class_type::*>();
    test_is_compound<int * class_type::*>();
    test_is_compound<int class_type::*&>();
    test_is_compound<float class_type::*&>();
    test_is_compound<void * class_type::*&>();
    test_is_compound<int * class_type::*&>();
    test_is_compound<int class_type::*&&>();
    test_is_compound<float class_type::*&&>();
    test_is_compound<void * class_type::*&&>();
    test_is_compound<int * class_type::*&&>();
    test_is_compound<int class_type::* const>();
    test_is_compound<float class_type::* const>();
    test_is_compound<void * class_type::* const>();
    test_is_compound<int class_type::* const&>();
    test_is_compound<float class_type::* const&>();
    test_is_compound<void * class_type::* const&>();
    test_is_compound<int class_type::* const&&>();
    test_is_compound<float class_type::* const&&>();
    test_is_compound<void * class_type::* const&&>();
    test_is_compound<int class_type::* volatile>();
    test_is_compound<float class_type::* volatile>();
    test_is_compound<void * class_type::* volatile>();
    test_is_compound<int class_type::* volatile&>();
    test_is_compound<float class_type::* volatile&>();
    test_is_compound<void * class_type::* volatile&>();
    test_is_compound<int class_type::* volatile&&>();
    test_is_compound<float class_type::* volatile&&>();
    test_is_compound<void * class_type::* volatile&&>();
    test_is_compound<int class_type::* const volatile>();
    test_is_compound<float class_type::* const volatile>();
    test_is_compound<void * class_type::* const volatile>();
    test_is_compound<int class_type::* const volatile&>();
    test_is_compound<float class_type::* const volatile&>();
    test_is_compound<void * class_type::* const volatile&>();
    test_is_compound<int class_type::* const volatile&&>();
    test_is_compound<float class_type::* const volatile&&>();
    test_is_compound<void * class_type::* const volatile&&>();
    test_is_compound<non_copyable>();
    test_is_compound<non_moveable>();
    test_is_compound<non_constructible>();
    test_is_compound<tracked>();
    test_is_compound<trap_constructible>();
    test_is_compound<trap_implicit_conversion>();
    test_is_compound<trap_comma>();
    test_is_compound<trap_call>();
    test_is_compound<trap_self_assign>();
    test_is_compound<trap_deref>();
    test_is_compound<trap_array_subscript>();

    test_is_compound<void()>();
    test_is_compound<void()&>();
    test_is_compound<void() &&>();
    test_is_compound<void() const>();
    test_is_compound<void() const&>();
    test_is_compound<void() const&&>();
    test_is_compound<void() volatile>();
    test_is_compound<void() volatile&>();
    test_is_compound<void() volatile&&>();
    test_is_compound<void() const volatile>();
    test_is_compound<void() const volatile&>();
    test_is_compound<void() const volatile&&>();
    test_is_compound<void() noexcept>();
    test_is_compound<void() & noexcept>();
    test_is_compound<void() && noexcept>();
    test_is_compound<void() const noexcept>();
    test_is_compound<void() const & noexcept>();
    test_is_compound<void() const && noexcept>();
    test_is_compound<void() volatile noexcept>();
    test_is_compound<void() volatile & noexcept>();
    test_is_compound<void() volatile && noexcept>();
    test_is_compound<void() const volatile noexcept>();
    test_is_compound<void() const volatile & noexcept>();
    test_is_compound<void() const volatile && noexcept>();

    test_is_compound<void(int)>();
    test_is_compound<void(int)&>();
    test_is_compound<void(int) &&>();
    test_is_compound<void(int) const>();
    test_is_compound<void(int) const&>();
    test_is_compound<void(int) const&&>();
    test_is_compound<void(int) volatile>();
    test_is_compound<void(int) volatile&>();
    test_is_compound<void(int) volatile&&>();
    test_is_compound<void(int) const volatile>();
    test_is_compound<void(int) const volatile&>();
    test_is_compound<void(int) const volatile&&>();
    test_is_compound<void(int) noexcept>();
    test_is_compound<void(int) & noexcept>();
    test_is_compound<void(int) && noexcept>();
    test_is_compound<void(int) const noexcept>();
    test_is_compound<void(int) const & noexcept>();
    test_is_compound<void(int) const && noexcept>();
    test_is_compound<void(int) volatile noexcept>();
    test_is_compound<void(int) volatile & noexcept>();
    test_is_compound<void(int) volatile && noexcept>();
    test_is_compound<void(int) const volatile noexcept>();
    test_is_compound<void(int) const volatile & noexcept>();
    test_is_compound<void(int) const volatile && noexcept>();

    test_is_compound<void(...)>();
    test_is_compound<void(...)&>();
    test_is_compound<void(...) &&>();
    test_is_compound<void(...) const>();
    test_is_compound<void(...) const&>();
    test_is_compound<void(...) const&&>();
    test_is_compound<void(...) volatile>();
    test_is_compound<void(...) volatile&>();
    test_is_compound<void(...) volatile&&>();
    test_is_compound<void(...) const volatile>();
    test_is_compound<void(...) const volatile&>();
    test_is_compound<void(...) const volatile&&>();
    test_is_compound<void(...) noexcept>();
    test_is_compound<void(...) & noexcept>();
    test_is_compound<void(...) && noexcept>();
    test_is_compound<void(...) const noexcept>();
    test_is_compound<void(...) const & noexcept>();
    test_is_compound<void(...) const && noexcept>();
    test_is_compound<void(...) volatile noexcept>();
    test_is_compound<void(...) volatile & noexcept>();
    test_is_compound<void(...) volatile && noexcept>();
    test_is_compound<void(...) const volatile noexcept>();
    test_is_compound<void(...) const volatile & noexcept>();
    test_is_compound<void(...) const volatile && noexcept>();

    test_is_compound<void(int, ...)>();
    test_is_compound<void(int, ...)&>();
    test_is_compound<void(int, ...) &&>();
    test_is_compound<void(int, ...) const>();
    test_is_compound<void(int, ...) const&>();
    test_is_compound<void(int, ...) const&&>();
    test_is_compound<void(int, ...) volatile>();
    test_is_compound<void(int, ...) volatile&>();
    test_is_compound<void(int, ...) volatile&&>();
    test_is_compound<void(int, ...) const volatile>();
    test_is_compound<void(int, ...) const volatile&>();
    test_is_compound<void(int, ...) const volatile&&>();
    test_is_compound<void(int, ...) noexcept>();
    test_is_compound<void(int, ...) & noexcept>();
    test_is_compound<void(int, ...) && noexcept>();
    test_is_compound<void(int, ...) const noexcept>();
    test_is_compound<void(int, ...) const & noexcept>();
    test_is_compound<void(int, ...) const && noexcept>();
    test_is_compound<void(int, ...) volatile noexcept>();
    test_is_compound<void(int, ...) volatile & noexcept>();
    test_is_compound<void(int, ...) volatile && noexcept>();
    test_is_compound<void(int, ...) const volatile noexcept>();
    test_is_compound<void(int, ...) const volatile & noexcept>();
    test_is_compound<void(int, ...) const volatile && noexcept>();

    test_is_compound<int()>();
    test_is_compound<int()&>();
    test_is_compound<int() &&>();
    test_is_compound<int() const>();
    test_is_compound<int() const&>();
    test_is_compound<int() const&&>();
    test_is_compound<int() volatile>();
    test_is_compound<int() volatile&>();
    test_is_compound<int() volatile&&>();
    test_is_compound<int() const volatile>();
    test_is_compound<int() const volatile&>();
    test_is_compound<int() const volatile&&>();
    test_is_compound<int() noexcept>();
    test_is_compound<int() & noexcept>();
    test_is_compound<int() && noexcept>();
    test_is_compound<int() const noexcept>();
    test_is_compound<int() const & noexcept>();
    test_is_compound<int() const && noexcept>();
    test_is_compound<int() volatile noexcept>();
    test_is_compound<int() volatile & noexcept>();
    test_is_compound<int() volatile && noexcept>();
    test_is_compound<int() const volatile noexcept>();
    test_is_compound<int() const volatile & noexcept>();
    test_is_compound<int() const volatile && noexcept>();

    test_is_compound<int(int)>();
    test_is_compound<int(int)&>();
    test_is_compound<int(int) &&>();
    test_is_compound<int(int) const>();
    test_is_compound<int(int) const&>();
    test_is_compound<int(int) const&&>();
    test_is_compound<int(int) volatile>();
    test_is_compound<int(int) volatile&>();
    test_is_compound<int(int) volatile&&>();
    test_is_compound<int(int) const volatile>();
    test_is_compound<int(int) const volatile&>();
    test_is_compound<int(int) const volatile&&>();
    test_is_compound<int(int) noexcept>();
    test_is_compound<int(int) & noexcept>();
    test_is_compound<int(int) && noexcept>();
    test_is_compound<int(int) const noexcept>();
    test_is_compound<int(int) const & noexcept>();
    test_is_compound<int(int) const && noexcept>();
    test_is_compound<int(int) volatile noexcept>();
    test_is_compound<int(int) volatile & noexcept>();
    test_is_compound<int(int) volatile && noexcept>();
    test_is_compound<int(int) const volatile noexcept>();
    test_is_compound<int(int) const volatile & noexcept>();
    test_is_compound<int(int) const volatile && noexcept>();

    test_is_compound<int(...)>();
    test_is_compound<int(...)&>();
    test_is_compound<int(...) &&>();
    test_is_compound<int(...) const>();
    test_is_compound<int(...) const&>();
    test_is_compound<int(...) const&&>();
    test_is_compound<int(...) volatile>();
    test_is_compound<int(...) volatile&>();
    test_is_compound<int(...) volatile&&>();
    test_is_compound<int(...) const volatile>();
    test_is_compound<int(...) const volatile&>();
    test_is_compound<int(...) const volatile&&>();
    test_is_compound<int(...) noexcept>();
    test_is_compound<int(...) & noexcept>();
    test_is_compound<int(...) && noexcept>();
    test_is_compound<int(...) const noexcept>();
    test_is_compound<int(...) const & noexcept>();
    test_is_compound<int(...) const && noexcept>();
    test_is_compound<int(...) volatile noexcept>();
    test_is_compound<int(...) volatile & noexcept>();
    test_is_compound<int(...) volatile && noexcept>();
    test_is_compound<int(...) const volatile noexcept>();
    test_is_compound<int(...) const volatile & noexcept>();
    test_is_compound<int(...) const volatile && noexcept>();

    test_is_compound<int(int, ...)>();
    test_is_compound<int(int, ...)&>();
    test_is_compound<int(int, ...) &&>();
    test_is_compound<int(int, ...) const>();
    test_is_compound<int(int, ...) const&>();
    test_is_compound<int(int, ...) const&&>();
    test_is_compound<int(int, ...) volatile>();
    test_is_compound<int(int, ...) volatile&>();
    test_is_compound<int(int, ...) volatile&&>();
    test_is_compound<int(int, ...) const volatile>();
    test_is_compound<int(int, ...) const volatile&>();
    test_is_compound<int(int, ...) const volatile&&>();
    test_is_compound<int(int, ...) noexcept>();
    test_is_compound<int(int, ...) & noexcept>();
    test_is_compound<int(int, ...) && noexcept>();
    test_is_compound<int(int, ...) const noexcept>();
    test_is_compound<int(int, ...) const & noexcept>();
    test_is_compound<int(int, ...) const && noexcept>();
    test_is_compound<int(int, ...) volatile noexcept>();
    test_is_compound<int(int, ...) volatile & noexcept>();
    test_is_compound<int(int, ...) volatile && noexcept>();
    test_is_compound<int(int, ...) const volatile noexcept>();
    test_is_compound<int(int, ...) const volatile & noexcept>();
    test_is_compound<int(int, ...) const volatile && noexcept>();

    test_is_compound<void (*)()>();
    test_is_compound<void (*)() noexcept>();

    test_is_compound<void (*)(int)>();
    test_is_compound<void (*)(int) noexcept>();

    test_is_compound<void (*)(...)>();
    test_is_compound<void (*)(...) noexcept>();

    test_is_compound<void (*)(int, ...)>();
    test_is_compound<void (*)(int, ...) noexcept>();

    test_is_compound<int (*)()>();
    test_is_compound<int (*)() noexcept>();

    test_is_compound<int (*)(int)>();
    test_is_compound<int (*)(int) noexcept>();

    test_is_compound<int (*)(...)>();
    test_is_compound<int (*)(...) noexcept>();

    test_is_compound<int (*)(int, ...)>();
    test_is_compound<int (*)(int, ...) noexcept>();

    test_is_compound<void (&)()>();
    test_is_compound<void (&)() noexcept>();

    test_is_compound<void (&)(int)>();
    test_is_compound<void (&)(int) noexcept>();

    test_is_compound<void (&)(...)>();
    test_is_compound<void (&)(...) noexcept>();

    test_is_compound<void (&)(int, ...)>();
    test_is_compound<void (&)(int, ...) noexcept>();

    test_is_compound<int (&)()>();
    test_is_compound<int (&)() noexcept>();

    test_is_compound<int (&)(int)>();
    test_is_compound<int (&)(int) noexcept>();

    test_is_compound<int (&)(...)>();
    test_is_compound<int (&)(...) noexcept>();

    test_is_compound<int (&)(int, ...)>();
    test_is_compound<int (&)(int, ...) noexcept>();

    test_is_compound<void (&&)()>();
    test_is_compound<void (&&)() noexcept>();

    test_is_compound<void (&&)(int)>();
    test_is_compound<void (&&)(int) noexcept>();

    test_is_compound<void (&&)(...)>();
    test_is_compound<void (&&)(...) noexcept>();

    test_is_compound<void (&&)(int, ...)>();
    test_is_compound<void (&&)(int, ...) noexcept>();

    test_is_compound<int (&&)()>();
    test_is_compound<int (&&)() noexcept>();

    test_is_compound<int (&&)(int)>();
    test_is_compound<int (&&)(int) noexcept>();

    test_is_compound<int (&&)(...)>();
    test_is_compound<int (&&)(...) noexcept>();

    test_is_compound<int (&&)(int, ...)>();
    test_is_compound<int (&&)(int, ...) noexcept>();

    test_is_compound<void (class_type::*)()>();
    test_is_compound<void (class_type::*)()&>();
    test_is_compound<void (class_type::*)() &&>();
    test_is_compound<void (class_type::*)() const>();
    test_is_compound<void (class_type::*)() const&>();
    test_is_compound<void (class_type::*)() const&&>();
    test_is_compound<void (class_type::*)() noexcept>();
    test_is_compound<void (class_type::*)() & noexcept>();
    test_is_compound<void (class_type::*)() && noexcept>();
    test_is_compound<void (class_type::*)() const noexcept>();
    test_is_compound<void (class_type::*)() const & noexcept>();
    test_is_compound<void (class_type::*)() const && noexcept>();

    test_is_compound<void (class_type::*)(int)>();
    test_is_compound<void (class_type::*)(int)&>();
    test_is_compound<void (class_type::*)(int) &&>();
    test_is_compound<void (class_type::*)(int) const>();
    test_is_compound<void (class_type::*)(int) const&>();
    test_is_compound<void (class_type::*)(int) const&&>();
    test_is_compound<void (class_type::*)(int) noexcept>();
    test_is_compound<void (class_type::*)(int) & noexcept>();
    test_is_compound<void (class_type::*)(int) && noexcept>();
    test_is_compound<void (class_type::*)(int) const noexcept>();
    test_is_compound<void (class_type::*)(int) const & noexcept>();
    test_is_compound<void (class_type::*)(int) const && noexcept>();

    test_is_compound<void (class_type::*)(...)>();
    test_is_compound<void (class_type::*)(...)&>();
    test_is_compound<void (class_type::*)(...) &&>();
    test_is_compound<void (class_type::*)(...) const>();
    test_is_compound<void (class_type::*)(...) const&>();
    test_is_compound<void (class_type::*)(...) const&&>();
    test_is_compound<void (class_type::*)(...) noexcept>();
    test_is_compound<void (class_type::*)(...) & noexcept>();
    test_is_compound<void (class_type::*)(...) && noexcept>();
    test_is_compound<void (class_type::*)(...) const noexcept>();
    test_is_compound<void (class_type::*)(...) const & noexcept>();
    test_is_compound<void (class_type::*)(...) const && noexcept>();

    test_is_compound<void (class_type::*)(int, ...)>();
    test_is_compound<void (class_type::*)(int, ...)&>();
    test_is_compound<void (class_type::*)(int, ...) &&>();
    test_is_compound<void (class_type::*)(int, ...) const>();
    test_is_compound<void (class_type::*)(int, ...) const&>();
    test_is_compound<void (class_type::*)(int, ...) const&&>();
    test_is_compound<void (class_type::*)(int, ...) noexcept>();
    test_is_compound<void (class_type::*)(int, ...) & noexcept>();
    test_is_compound<void (class_type::*)(int, ...) && noexcept>();
    test_is_compound<void (class_type::*)(int, ...) const noexcept>();
    test_is_compound<void (class_type::*)(int, ...) const & noexcept>();
    test_is_compound<void (class_type::*)(int, ...) const && noexcept>();

    test_is_compound<int (class_type::*)()>();
    test_is_compound<int (class_type::*)()&>();
    test_is_compound<int (class_type::*)() &&>();
    test_is_compound<int (class_type::*)() const>();
    test_is_compound<int (class_type::*)() const&>();
    test_is_compound<int (class_type::*)() const&&>();
    test_is_compound<int (class_type::*)() noexcept>();
    test_is_compound<int (class_type::*)() & noexcept>();
    test_is_compound<int (class_type::*)() && noexcept>();
    test_is_compound<int (class_type::*)() const noexcept>();
    test_is_compound<int (class_type::*)() const & noexcept>();
    test_is_compound<int (class_type::*)() const && noexcept>();

    test_is_compound<int (class_type::*)(int)>();
    test_is_compound<int (class_type::*)(int)&>();
    test_is_compound<int (class_type::*)(int) &&>();
    test_is_compound<int (class_type::*)(int) const>();
    test_is_compound<int (class_type::*)(int) const&>();
    test_is_compound<int (class_type::*)(int) const&&>();
    test_is_compound<int (class_type::*)(int) noexcept>();
    test_is_compound<int (class_type::*)(int) & noexcept>();
    test_is_compound<int (class_type::*)(int) && noexcept>();
    test_is_compound<int (class_type::*)(int) const noexcept>();
    test_is_compound<int (class_type::*)(int) const & noexcept>();
    test_is_compound<int (class_type::*)(int) const && noexcept>();

    test_is_compound<int (class_type::*)(...)>();
    test_is_compound<int (class_type::*)(...)&>();
    test_is_compound<int (class_type::*)(...) &&>();
    test_is_compound<int (class_type::*)(...) const>();
    test_is_compound<int (class_type::*)(...) const&>();
    test_is_compound<int (class_type::*)(...) const&&>();
    test_is_compound<int (class_type::*)(...) noexcept>();
    test_is_compound<int (class_type::*)(...) & noexcept>();
    test_is_compound<int (class_type::*)(...) && noexcept>();
    test_is_compound<int (class_type::*)(...) const noexcept>();
    test_is_compound<int (class_type::*)(...) const & noexcept>();
    test_is_compound<int (class_type::*)(...) const && noexcept>();

    test_is_compound<int (class_type::*)(int, ...)>();
    test_is_compound<int (class_type::*)(int, ...)&>();
    test_is_compound<int (class_type::*)(int, ...) &&>();
    test_is_compound<int (class_type::*)(int, ...) const>();
    test_is_compound<int (class_type::*)(int, ...) const&>();
    test_is_compound<int (class_type::*)(int, ...) const&&>();
    test_is_compound<int (class_type::*)(int, ...) noexcept>();
    test_is_compound<int (class_type::*)(int, ...) & noexcept>();
    test_is_compound<int (class_type::*)(int, ...) && noexcept>();
    test_is_compound<int (class_type::*)(int, ...) const noexcept>();
    test_is_compound<int (class_type::*)(int, ...) const & noexcept>();
    test_is_compound<int (class_type::*)(int, ...) const && noexcept>();
}
