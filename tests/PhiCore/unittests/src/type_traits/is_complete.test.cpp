#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_complete.hpp>
#include <vector>

template <typename TypeT>
void test_is_complete_impl()
{
    STATIC_REQUIRE(phi::is_complete<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_complete<TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_complete_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_not_complete_v<TypeT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_complete<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_complete<TypeT>);
}

template <typename TypeT>
void test_is_complete()
{
    test_is_complete_impl<TypeT>();
    test_is_complete_impl<const TypeT>();
    test_is_complete_impl<volatile TypeT>();
    test_is_complete_impl<const volatile TypeT>();
}

template <typename TypeT>
void test_is_not_complete_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_complete<TypeT>::value);
    STATIC_REQUIRE(phi::is_not_complete<TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_complete_v<TypeT>);
    STATIC_REQUIRE(phi::is_not_complete_v<TypeT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_complete<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_complete<TypeT>);
}

template <typename TypeT>
void test_is_not_complete()
{
    test_is_not_complete_impl<TypeT>();
    test_is_not_complete_impl<const TypeT>();
    test_is_not_complete_impl<volatile TypeT>();
    test_is_not_complete_impl<const volatile TypeT>();
}

class A;

TEST_CASE("is_complete")
{
    test_is_not_complete<void>();
    test_is_complete<phi::nullptr_t>();
    test_is_complete<bool>();
    test_is_complete<char>();
    test_is_complete<signed char>();
    test_is_complete<unsigned char>();
    test_is_complete<short>();
    test_is_complete<unsigned short>();
    test_is_complete<int>();
    test_is_complete<unsigned int>();
    test_is_complete<long>();
    test_is_complete<unsigned long>();
    test_is_complete<long long>();
    test_is_complete<unsigned long long>();
    test_is_complete<float>();
    test_is_complete<double>();
    test_is_complete<long double>();
    test_is_complete<char8_t>();
    test_is_complete<char16_t>();
    test_is_complete<char32_t>();
    test_is_complete<wchar_t>();

    test_is_complete<phi::boolean>();
    test_is_complete<phi::integer<signed char>>();
    test_is_complete<phi::integer<unsigned char>>();
    test_is_complete<phi::integer<short>>();
    test_is_complete<phi::integer<unsigned short>>();
    test_is_complete<phi::integer<int>>();
    test_is_complete<phi::integer<unsigned int>>();
    test_is_complete<phi::integer<long>>();
    test_is_complete<phi::integer<unsigned long>>();
    test_is_complete<phi::integer<long long>>();
    test_is_complete<phi::integer<unsigned long long>>();
    test_is_complete<phi::floating_point<float>>();
    test_is_complete<phi::floating_point<double>>();
    test_is_complete<phi::floating_point<long double>>();

    test_is_complete<std::vector<int>>();
    test_is_complete<phi::scope_ptr<int>>();

    test_is_complete<int&>();
    test_is_complete<const int&>();
    test_is_complete<volatile int&>();
    test_is_complete<const volatile int&>();
    test_is_complete<int&&>();
    test_is_complete<const int&&>();
    test_is_complete<volatile int&&>();
    test_is_complete<const volatile int&&>();
    test_is_complete<int*>();
    test_is_complete<const int*>();
    test_is_complete<volatile int*>();
    test_is_complete<const volatile int*>();
    test_is_complete<int**>();
    test_is_complete<const int**>();
    test_is_complete<volatile int**>();
    test_is_complete<const volatile int**>();
    test_is_complete<int*&>();
    test_is_complete<const int*&>();
    test_is_complete<volatile int*&>();
    test_is_complete<const volatile int*&>();
    test_is_complete<int*&&>();
    test_is_complete<const int*&&>();
    test_is_complete<volatile int*&&>();
    test_is_complete<const volatile int*&&>();
    test_is_complete<void*>();
    test_is_complete<char[3]>();
    test_is_not_complete<char[]>();
    test_is_complete<char* [3]>();
    test_is_not_complete<char*[]>();
    test_is_complete<int(*)[3]>();
    test_is_complete<int(*)[]>();
    test_is_complete<int(&)[3]>();
    test_is_not_complete<int(&)[]>();
    test_is_complete<int(&&)[3]>();
    test_is_complete<int(&&)[]>();
    test_is_complete<char[3][2]>();
    test_is_not_complete<char[][2]>();
    test_is_complete<char* [3][2]>();
    test_is_not_complete<char*[][2]>();
    test_is_complete<int(*)[3][2]>();
    test_is_complete<int(*)[][2]>();
    test_is_complete<int(&)[3][2]>();
    test_is_not_complete<int(&)[][2]>();
    test_is_complete<int(&&)[3][2]>();
    test_is_complete<int(&&)[][2]>();
    test_is_complete<class_type>();
    test_is_not_complete<class_type[]>();
    test_is_complete<class_type[2]>();
    test_is_complete<template_type<void>>();
    test_is_complete<template_type<int>>();
    test_is_complete<template_type<class_type>>();
    test_is_complete<template_type<incomplete_type>>();
    test_is_complete<variadic_template<>>();
    test_is_complete<variadic_template<void>>();
    test_is_complete<variadic_template<int>>();
    test_is_complete<variadic_template<class_type>>();
    test_is_complete<variadic_template<incomplete_type>>();
    test_is_complete<variadic_template<int, void, class_type, volatile char[]>>();
    test_is_complete<public_derived_from<base>>();
    test_is_complete<public_derived_from<derived>>();
    test_is_complete<public_derived_from<class_type>>();
    test_is_complete<private_derived_from<base>>();
    test_is_complete<private_derived_from<derived>>();
    test_is_complete<private_derived_from<class_type>>();
    test_is_complete<protected_derived_from<base>>();
    test_is_complete<protected_derived_from<derived>>();
    test_is_complete<protected_derived_from<class_type>>();
    test_is_complete<union_type>();
    test_is_complete<non_empty_union>();
    test_is_complete<empty>();
    test_is_complete<not_empty>();
    test_is_complete<bit_zero>();
    test_is_complete<bit_one>();
    test_is_complete<base>();
    test_is_complete<derived>();
    test_is_complete<abstract>();
    test_is_complete<public_abstract>();
    test_is_complete<private_abstract>();
    test_is_complete<protected_abstract>();
    test_is_complete<abstract_template<int>>();
    test_is_complete<abstract_template<double>>();
    test_is_complete<abstract_template<class_type>>();
    test_is_complete<abstract_template<incomplete_type>>();
    test_is_complete<final_type>();
    test_is_complete<public_destructor>();
    test_is_complete<protected_destructor>();
    test_is_complete<private_destructor>();
    test_is_complete<virtual_public_destructor>();
    test_is_complete<virtual_protected_destructor>();
    test_is_complete<virtual_private_destructor>();
    test_is_complete<pure_public_destructor>();
    test_is_complete<pure_protected_destructor>();
    test_is_complete<pure_private_destructor>();
    test_is_complete<deleted_public_destructor>();
    test_is_complete<deleted_protected_destructor>();
    test_is_complete<deleted_private_destructor>();
    test_is_complete<deleted_virtual_public_destructor>();
    test_is_complete<deleted_virtual_protected_destructor>();
    test_is_complete<deleted_virtual_private_destructor>();
    test_is_complete<Enum>();
    test_is_complete<EnumSigned>();
    test_is_complete<EnumUnsigned>();
    test_is_complete<EnumClass>();
    test_is_complete<EnumStruct>();
    test_is_complete<function_type>();
    test_is_complete<function_ptr>();
    test_is_complete<member_object_ptr>();
    test_is_complete<member_function_ptr>();
    test_is_not_complete<incomplete_type>();
    test_is_not_complete<incomplete_template<void>>();
    test_is_not_complete<incomplete_template<int>>();
    test_is_not_complete<incomplete_template<class_type>>();
    test_is_not_complete<incomplete_template<incomplete_type>>();
    test_is_not_complete<incomplete_variadic_template<>>();
    test_is_not_complete<incomplete_variadic_template<void>>();
    test_is_not_complete<incomplete_variadic_template<int>>();
    test_is_not_complete<incomplete_variadic_template<class_type>>();
    test_is_not_complete<incomplete_variadic_template<incomplete_type>>();
    test_is_not_complete<incomplete_variadic_template<int, void, class_type, volatile char[]>>();
    test_is_complete<int class_type::*>();
    test_is_complete<float class_type::*>();
    test_is_complete<void * class_type::*>();
    test_is_complete<int * class_type::*>();
    test_is_complete<int class_type::*&>();
    test_is_complete<float class_type::*&>();
    test_is_complete<void * class_type::*&>();
    test_is_complete<int * class_type::*&>();
    test_is_complete<int class_type::*&&>();
    test_is_complete<float class_type::*&&>();
    test_is_complete<void * class_type::*&&>();
    test_is_complete<int * class_type::*&&>();
    test_is_complete<int class_type::* const>();
    test_is_complete<float class_type::* const>();
    test_is_complete<void * class_type::* const>();
    test_is_complete<int class_type::* const&>();
    test_is_complete<float class_type::* const&>();
    test_is_complete<void * class_type::* const&>();
    test_is_complete<int class_type::* const&&>();
    test_is_complete<float class_type::* const&&>();
    test_is_complete<void * class_type::* const&&>();
    test_is_complete<int class_type::* volatile>();
    test_is_complete<float class_type::* volatile>();
    test_is_complete<void * class_type::* volatile>();
    test_is_complete<int class_type::* volatile&>();
    test_is_complete<float class_type::* volatile&>();
    test_is_complete<void * class_type::* volatile&>();
    test_is_complete<int class_type::* volatile&&>();
    test_is_complete<float class_type::* volatile&&>();
    test_is_complete<void * class_type::* volatile&&>();
    test_is_complete<int class_type::* const volatile>();
    test_is_complete<float class_type::* const volatile>();
    test_is_complete<void * class_type::* const volatile>();
    test_is_complete<int class_type::* const volatile&>();
    test_is_complete<float class_type::* const volatile&>();
    test_is_complete<void * class_type::* const volatile&>();
    test_is_complete<int class_type::* const volatile&&>();
    test_is_complete<float class_type::* const volatile&&>();
    test_is_complete<void * class_type::* const volatile&&>();
    test_is_complete<non_copyable>();
    test_is_complete<non_moveable>();
    test_is_complete<non_constructible>();
    test_is_complete<tracked>();
    test_is_complete<trap_constructible>();
    test_is_complete<trap_implicit_conversion>();
    test_is_complete<trap_comma>();
    test_is_complete<trap_call>();
    test_is_complete<trap_self_assign>();
    test_is_complete<trap_deref>();
    test_is_complete<trap_array_subscript>();

    test_is_complete<void()>();
    test_is_complete<void()&>();
    test_is_complete<void() &&>();
    test_is_complete<void() const>();
    test_is_complete<void() const&>();
    test_is_complete<void() const&&>();
    test_is_complete<void() volatile>();
    test_is_complete<void() volatile&>();
    test_is_complete<void() volatile&&>();
    test_is_complete<void() const volatile>();
    test_is_complete<void() const volatile&>();
    test_is_complete<void() const volatile&&>();
    test_is_complete<void() noexcept>();
    test_is_complete<void() & noexcept>();
    test_is_complete<void() && noexcept>();
    test_is_complete<void() const noexcept>();
    test_is_complete<void() const & noexcept>();
    test_is_complete<void() const && noexcept>();
    test_is_complete<void() volatile noexcept>();
    test_is_complete<void() volatile & noexcept>();
    test_is_complete<void() volatile && noexcept>();
    test_is_complete<void() const volatile noexcept>();
    test_is_complete<void() const volatile & noexcept>();
    test_is_complete<void() const volatile && noexcept>();

    test_is_complete<void(int)>();
    test_is_complete<void(int)&>();
    test_is_complete<void(int) &&>();
    test_is_complete<void(int) const>();
    test_is_complete<void(int) const&>();
    test_is_complete<void(int) const&&>();
    test_is_complete<void(int) volatile>();
    test_is_complete<void(int) volatile&>();
    test_is_complete<void(int) volatile&&>();
    test_is_complete<void(int) const volatile>();
    test_is_complete<void(int) const volatile&>();
    test_is_complete<void(int) const volatile&&>();
    test_is_complete<void(int) noexcept>();
    test_is_complete<void(int) & noexcept>();
    test_is_complete<void(int) && noexcept>();
    test_is_complete<void(int) const noexcept>();
    test_is_complete<void(int) const & noexcept>();
    test_is_complete<void(int) const && noexcept>();
    test_is_complete<void(int) volatile noexcept>();
    test_is_complete<void(int) volatile & noexcept>();
    test_is_complete<void(int) volatile && noexcept>();
    test_is_complete<void(int) const volatile noexcept>();
    test_is_complete<void(int) const volatile & noexcept>();
    test_is_complete<void(int) const volatile && noexcept>();

    test_is_complete<void(...)>();
    test_is_complete<void(...)&>();
    test_is_complete<void(...) &&>();
    test_is_complete<void(...) const>();
    test_is_complete<void(...) const&>();
    test_is_complete<void(...) const&&>();
    test_is_complete<void(...) volatile>();
    test_is_complete<void(...) volatile&>();
    test_is_complete<void(...) volatile&&>();
    test_is_complete<void(...) const volatile>();
    test_is_complete<void(...) const volatile&>();
    test_is_complete<void(...) const volatile&&>();
    test_is_complete<void(...) noexcept>();
    test_is_complete<void(...) & noexcept>();
    test_is_complete<void(...) && noexcept>();
    test_is_complete<void(...) const noexcept>();
    test_is_complete<void(...) const & noexcept>();
    test_is_complete<void(...) const && noexcept>();
    test_is_complete<void(...) volatile noexcept>();
    test_is_complete<void(...) volatile & noexcept>();
    test_is_complete<void(...) volatile && noexcept>();
    test_is_complete<void(...) const volatile noexcept>();
    test_is_complete<void(...) const volatile & noexcept>();
    test_is_complete<void(...) const volatile && noexcept>();

    test_is_complete<void(int, ...)>();
    test_is_complete<void(int, ...)&>();
    test_is_complete<void(int, ...) &&>();
    test_is_complete<void(int, ...) const>();
    test_is_complete<void(int, ...) const&>();
    test_is_complete<void(int, ...) const&&>();
    test_is_complete<void(int, ...) volatile>();
    test_is_complete<void(int, ...) volatile&>();
    test_is_complete<void(int, ...) volatile&&>();
    test_is_complete<void(int, ...) const volatile>();
    test_is_complete<void(int, ...) const volatile&>();
    test_is_complete<void(int, ...) const volatile&&>();
    test_is_complete<void(int, ...) noexcept>();
    test_is_complete<void(int, ...) & noexcept>();
    test_is_complete<void(int, ...) && noexcept>();
    test_is_complete<void(int, ...) const noexcept>();
    test_is_complete<void(int, ...) const & noexcept>();
    test_is_complete<void(int, ...) const && noexcept>();
    test_is_complete<void(int, ...) volatile noexcept>();
    test_is_complete<void(int, ...) volatile & noexcept>();
    test_is_complete<void(int, ...) volatile && noexcept>();
    test_is_complete<void(int, ...) const volatile noexcept>();
    test_is_complete<void(int, ...) const volatile & noexcept>();
    test_is_complete<void(int, ...) const volatile && noexcept>();

    test_is_complete<int()>();
    test_is_complete<int()&>();
    test_is_complete<int() &&>();
    test_is_complete<int() const>();
    test_is_complete<int() const&>();
    test_is_complete<int() const&&>();
    test_is_complete<int() volatile>();
    test_is_complete<int() volatile&>();
    test_is_complete<int() volatile&&>();
    test_is_complete<int() const volatile>();
    test_is_complete<int() const volatile&>();
    test_is_complete<int() const volatile&&>();
    test_is_complete<int() noexcept>();
    test_is_complete<int() & noexcept>();
    test_is_complete<int() && noexcept>();
    test_is_complete<int() const noexcept>();
    test_is_complete<int() const & noexcept>();
    test_is_complete<int() const && noexcept>();
    test_is_complete<int() volatile noexcept>();
    test_is_complete<int() volatile & noexcept>();
    test_is_complete<int() volatile && noexcept>();
    test_is_complete<int() const volatile noexcept>();
    test_is_complete<int() const volatile & noexcept>();
    test_is_complete<int() const volatile && noexcept>();

    test_is_complete<int(int)>();
    test_is_complete<int(int)&>();
    test_is_complete<int(int) &&>();
    test_is_complete<int(int) const>();
    test_is_complete<int(int) const&>();
    test_is_complete<int(int) const&&>();
    test_is_complete<int(int) volatile>();
    test_is_complete<int(int) volatile&>();
    test_is_complete<int(int) volatile&&>();
    test_is_complete<int(int) const volatile>();
    test_is_complete<int(int) const volatile&>();
    test_is_complete<int(int) const volatile&&>();
    test_is_complete<int(int) noexcept>();
    test_is_complete<int(int) & noexcept>();
    test_is_complete<int(int) && noexcept>();
    test_is_complete<int(int) const noexcept>();
    test_is_complete<int(int) const & noexcept>();
    test_is_complete<int(int) const && noexcept>();
    test_is_complete<int(int) volatile noexcept>();
    test_is_complete<int(int) volatile & noexcept>();
    test_is_complete<int(int) volatile && noexcept>();
    test_is_complete<int(int) const volatile noexcept>();
    test_is_complete<int(int) const volatile & noexcept>();
    test_is_complete<int(int) const volatile && noexcept>();

    test_is_complete<int(...)>();
    test_is_complete<int(...)&>();
    test_is_complete<int(...) &&>();
    test_is_complete<int(...) const>();
    test_is_complete<int(...) const&>();
    test_is_complete<int(...) const&&>();
    test_is_complete<int(...) volatile>();
    test_is_complete<int(...) volatile&>();
    test_is_complete<int(...) volatile&&>();
    test_is_complete<int(...) const volatile>();
    test_is_complete<int(...) const volatile&>();
    test_is_complete<int(...) const volatile&&>();
    test_is_complete<int(...) noexcept>();
    test_is_complete<int(...) & noexcept>();
    test_is_complete<int(...) && noexcept>();
    test_is_complete<int(...) const noexcept>();
    test_is_complete<int(...) const & noexcept>();
    test_is_complete<int(...) const && noexcept>();
    test_is_complete<int(...) volatile noexcept>();
    test_is_complete<int(...) volatile & noexcept>();
    test_is_complete<int(...) volatile && noexcept>();
    test_is_complete<int(...) const volatile noexcept>();
    test_is_complete<int(...) const volatile & noexcept>();
    test_is_complete<int(...) const volatile && noexcept>();

    test_is_complete<int(int, ...)>();
    test_is_complete<int(int, ...)&>();
    test_is_complete<int(int, ...) &&>();
    test_is_complete<int(int, ...) const>();
    test_is_complete<int(int, ...) const&>();
    test_is_complete<int(int, ...) const&&>();
    test_is_complete<int(int, ...) volatile>();
    test_is_complete<int(int, ...) volatile&>();
    test_is_complete<int(int, ...) volatile&&>();
    test_is_complete<int(int, ...) const volatile>();
    test_is_complete<int(int, ...) const volatile&>();
    test_is_complete<int(int, ...) const volatile&&>();
    test_is_complete<int(int, ...) noexcept>();
    test_is_complete<int(int, ...) & noexcept>();
    test_is_complete<int(int, ...) && noexcept>();
    test_is_complete<int(int, ...) const noexcept>();
    test_is_complete<int(int, ...) const & noexcept>();
    test_is_complete<int(int, ...) const && noexcept>();
    test_is_complete<int(int, ...) volatile noexcept>();
    test_is_complete<int(int, ...) volatile & noexcept>();
    test_is_complete<int(int, ...) volatile && noexcept>();
    test_is_complete<int(int, ...) const volatile noexcept>();
    test_is_complete<int(int, ...) const volatile & noexcept>();
    test_is_complete<int(int, ...) const volatile && noexcept>();

    test_is_complete<void (*)()>();
    test_is_complete<void (*)() noexcept>();

    test_is_complete<void (*)(int)>();
    test_is_complete<void (*)(int) noexcept>();

    test_is_complete<void (*)(...)>();
    test_is_complete<void (*)(...) noexcept>();

    test_is_complete<void (*)(int, ...)>();
    test_is_complete<void (*)(int, ...) noexcept>();

    test_is_complete<int (*)()>();
    test_is_complete<int (*)() noexcept>();

    test_is_complete<int (*)(int)>();
    test_is_complete<int (*)(int) noexcept>();

    test_is_complete<int (*)(...)>();
    test_is_complete<int (*)(...) noexcept>();

    test_is_complete<int (*)(int, ...)>();
    test_is_complete<int (*)(int, ...) noexcept>();

    test_is_complete<void (&)()>();
    test_is_complete<void (&)() noexcept>();

    test_is_complete<void (&)(int)>();
    test_is_complete<void (&)(int) noexcept>();

    test_is_complete<void (&)(...)>();
    test_is_complete<void (&)(...) noexcept>();

    test_is_complete<void (&)(int, ...)>();
    test_is_complete<void (&)(int, ...) noexcept>();

    test_is_complete<int (&)()>();
    test_is_complete<int (&)() noexcept>();

    test_is_complete<int (&)(int)>();
    test_is_complete<int (&)(int) noexcept>();

    test_is_complete<int (&)(...)>();
    test_is_complete<int (&)(...) noexcept>();

    test_is_complete<int (&)(int, ...)>();
    test_is_complete<int (&)(int, ...) noexcept>();

    test_is_complete<void (&&)()>();
    test_is_complete<void (&&)() noexcept>();

    test_is_complete<void (&&)(int)>();
    test_is_complete<void (&&)(int) noexcept>();

    test_is_complete<void (&&)(...)>();
    test_is_complete<void (&&)(...) noexcept>();

    test_is_complete<void (&&)(int, ...)>();
    test_is_complete<void (&&)(int, ...) noexcept>();

    test_is_complete<int (&&)()>();
    test_is_complete<int (&&)() noexcept>();

    test_is_complete<int (&&)(int)>();
    test_is_complete<int (&&)(int) noexcept>();

    test_is_complete<int (&&)(...)>();
    test_is_complete<int (&&)(...) noexcept>();

    test_is_complete<int (&&)(int, ...)>();
    test_is_complete<int (&&)(int, ...) noexcept>();

    test_is_complete<void (class_type::*)()>();
    test_is_complete<void (class_type::*)()&>();
    test_is_complete<void (class_type::*)() &&>();
    test_is_complete<void (class_type::*)() const>();
    test_is_complete<void (class_type::*)() const&>();
    test_is_complete<void (class_type::*)() const&&>();
    test_is_complete<void (class_type::*)() noexcept>();
    test_is_complete<void (class_type::*)() & noexcept>();
    test_is_complete<void (class_type::*)() && noexcept>();
    test_is_complete<void (class_type::*)() const noexcept>();
    test_is_complete<void (class_type::*)() const & noexcept>();
    test_is_complete<void (class_type::*)() const && noexcept>();

    test_is_complete<void (class_type::*)(int)>();
    test_is_complete<void (class_type::*)(int)&>();
    test_is_complete<void (class_type::*)(int) &&>();
    test_is_complete<void (class_type::*)(int) const>();
    test_is_complete<void (class_type::*)(int) const&>();
    test_is_complete<void (class_type::*)(int) const&&>();
    test_is_complete<void (class_type::*)(int) noexcept>();
    test_is_complete<void (class_type::*)(int) & noexcept>();
    test_is_complete<void (class_type::*)(int) && noexcept>();
    test_is_complete<void (class_type::*)(int) const noexcept>();
    test_is_complete<void (class_type::*)(int) const & noexcept>();
    test_is_complete<void (class_type::*)(int) const && noexcept>();

    test_is_complete<void (class_type::*)(...)>();
    test_is_complete<void (class_type::*)(...)&>();
    test_is_complete<void (class_type::*)(...) &&>();
    test_is_complete<void (class_type::*)(...) const>();
    test_is_complete<void (class_type::*)(...) const&>();
    test_is_complete<void (class_type::*)(...) const&&>();
    test_is_complete<void (class_type::*)(...) noexcept>();
    test_is_complete<void (class_type::*)(...) & noexcept>();
    test_is_complete<void (class_type::*)(...) && noexcept>();
    test_is_complete<void (class_type::*)(...) const noexcept>();
    test_is_complete<void (class_type::*)(...) const & noexcept>();
    test_is_complete<void (class_type::*)(...) const && noexcept>();

    test_is_complete<void (class_type::*)(int, ...)>();
    test_is_complete<void (class_type::*)(int, ...)&>();
    test_is_complete<void (class_type::*)(int, ...) &&>();
    test_is_complete<void (class_type::*)(int, ...) const>();
    test_is_complete<void (class_type::*)(int, ...) const&>();
    test_is_complete<void (class_type::*)(int, ...) const&&>();
    test_is_complete<void (class_type::*)(int, ...) noexcept>();
    test_is_complete<void (class_type::*)(int, ...) & noexcept>();
    test_is_complete<void (class_type::*)(int, ...) && noexcept>();
    test_is_complete<void (class_type::*)(int, ...) const noexcept>();
    test_is_complete<void (class_type::*)(int, ...) const & noexcept>();
    test_is_complete<void (class_type::*)(int, ...) const && noexcept>();

    test_is_complete<int (class_type::*)()>();
    test_is_complete<int (class_type::*)()&>();
    test_is_complete<int (class_type::*)() &&>();
    test_is_complete<int (class_type::*)() const>();
    test_is_complete<int (class_type::*)() const&>();
    test_is_complete<int (class_type::*)() const&&>();
    test_is_complete<int (class_type::*)() noexcept>();
    test_is_complete<int (class_type::*)() & noexcept>();
    test_is_complete<int (class_type::*)() && noexcept>();
    test_is_complete<int (class_type::*)() const noexcept>();
    test_is_complete<int (class_type::*)() const & noexcept>();
    test_is_complete<int (class_type::*)() const && noexcept>();

    test_is_complete<int (class_type::*)(int)>();
    test_is_complete<int (class_type::*)(int)&>();
    test_is_complete<int (class_type::*)(int) &&>();
    test_is_complete<int (class_type::*)(int) const>();
    test_is_complete<int (class_type::*)(int) const&>();
    test_is_complete<int (class_type::*)(int) const&&>();
    test_is_complete<int (class_type::*)(int) noexcept>();
    test_is_complete<int (class_type::*)(int) & noexcept>();
    test_is_complete<int (class_type::*)(int) && noexcept>();
    test_is_complete<int (class_type::*)(int) const noexcept>();
    test_is_complete<int (class_type::*)(int) const & noexcept>();
    test_is_complete<int (class_type::*)(int) const && noexcept>();

    test_is_complete<int (class_type::*)(...)>();
    test_is_complete<int (class_type::*)(...)&>();
    test_is_complete<int (class_type::*)(...) &&>();
    test_is_complete<int (class_type::*)(...) const>();
    test_is_complete<int (class_type::*)(...) const&>();
    test_is_complete<int (class_type::*)(...) const&&>();
    test_is_complete<int (class_type::*)(...) noexcept>();
    test_is_complete<int (class_type::*)(...) & noexcept>();
    test_is_complete<int (class_type::*)(...) && noexcept>();
    test_is_complete<int (class_type::*)(...) const noexcept>();
    test_is_complete<int (class_type::*)(...) const & noexcept>();
    test_is_complete<int (class_type::*)(...) const && noexcept>();

    test_is_complete<int (class_type::*)(int, ...)>();
    test_is_complete<int (class_type::*)(int, ...)&>();
    test_is_complete<int (class_type::*)(int, ...) &&>();
    test_is_complete<int (class_type::*)(int, ...) const>();
    test_is_complete<int (class_type::*)(int, ...) const&>();
    test_is_complete<int (class_type::*)(int, ...) const&&>();
    test_is_complete<int (class_type::*)(int, ...) noexcept>();
    test_is_complete<int (class_type::*)(int, ...) & noexcept>();
    test_is_complete<int (class_type::*)(int, ...) && noexcept>();
    test_is_complete<int (class_type::*)(int, ...) const noexcept>();
    test_is_complete<int (class_type::*)(int, ...) const & noexcept>();
    test_is_complete<int (class_type::*)(int, ...) const && noexcept>();
}
