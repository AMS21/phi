#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_abstract.hpp>
#include <type_traits>
#include <vector>

template <typename TypeT>
void test_is_abstract_impl()
{
#if PHI_HAS_WORKING_IS_ABSTRACT()
    STATIC_REQUIRE(phi::is_abstract<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_abstract<TypeT>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_abstract_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_not_abstract_v<TypeT>);
#    endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_abstract<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_abstract<TypeT>);

    // Stndard compatbility
    STATIC_REQUIRE(std::is_abstract<TypeT>::value);
#endif
}

template <typename TypeT>
void test_is_abstract()
{
    test_is_abstract_impl<TypeT>();
    test_is_abstract_impl<const TypeT>();
    test_is_abstract_impl<volatile TypeT>();
    test_is_abstract_impl<const volatile TypeT>();
}

template <typename TypeT>
void test_is_not_abstract_impl()
{
#if PHI_HAS_WORKING_IS_ABSTRACT()
    STATIC_REQUIRE_FALSE(phi::is_abstract<TypeT>::value);
    STATIC_REQUIRE(phi::is_not_abstract<TypeT>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_abstract_v<TypeT>);
    STATIC_REQUIRE(phi::is_not_abstract_v<TypeT>);
#    endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_abstract<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_abstract<TypeT>);

    // Standard compatbility
    STATIC_REQUIRE_FALSE(std::is_abstract<TypeT>::value);
#endif
}

template <typename TypeT>
void test_is_not_abstract()
{
    test_is_not_abstract_impl<TypeT>();
    test_is_not_abstract_impl<const TypeT>();
    test_is_not_abstract_impl<volatile TypeT>();
    test_is_not_abstract_impl<const volatile TypeT>();
}

TEST_CASE("is_abstract")
{
    test_is_not_abstract<void>();
    test_is_not_abstract<phi::nullptr_t>();
    test_is_not_abstract<bool>();
    test_is_not_abstract<char>();
    test_is_not_abstract<signed char>();
    test_is_not_abstract<unsigned char>();
    test_is_not_abstract<short>();
    test_is_not_abstract<unsigned short>();
    test_is_not_abstract<int>();
    test_is_not_abstract<unsigned int>();
    test_is_not_abstract<long>();
    test_is_not_abstract<unsigned long>();
    test_is_not_abstract<long long>();
    test_is_not_abstract<unsigned long long>();
    test_is_not_abstract<float>();
    test_is_not_abstract<double>();
    test_is_not_abstract<long double>();
    test_is_not_abstract<char8_t>();
    test_is_not_abstract<char16_t>();
    test_is_not_abstract<char32_t>();
    test_is_not_abstract<wchar_t>();

    test_is_not_abstract<phi::boolean>();
    test_is_not_abstract<phi::integer<signed char>>();
    test_is_not_abstract<phi::integer<unsigned char>>();
    test_is_not_abstract<phi::integer<short>>();
    test_is_not_abstract<phi::integer<unsigned short>>();
    test_is_not_abstract<phi::integer<int>>();
    test_is_not_abstract<phi::integer<unsigned int>>();
    test_is_not_abstract<phi::integer<long>>();
    test_is_not_abstract<phi::integer<unsigned long>>();
    test_is_not_abstract<phi::integer<long long>>();
    test_is_not_abstract<phi::integer<unsigned long long>>();
    test_is_not_abstract<phi::floating_point<float>>();
    test_is_not_abstract<phi::floating_point<double>>();
    test_is_not_abstract<phi::floating_point<long double>>();

    test_is_not_abstract<std::vector<int>>();
    test_is_not_abstract<phi::scope_ptr<int>>();

    test_is_not_abstract<int&>();
    test_is_not_abstract<const int&>();
    test_is_not_abstract<volatile int&>();
    test_is_not_abstract<const volatile int&>();
    test_is_not_abstract<int&&>();
    test_is_not_abstract<const int&&>();
    test_is_not_abstract<volatile int&&>();
    test_is_not_abstract<const volatile int&&>();
    test_is_not_abstract<int*>();
    test_is_not_abstract<const int*>();
    test_is_not_abstract<volatile int*>();
    test_is_not_abstract<const volatile int*>();
    test_is_not_abstract<int**>();
    test_is_not_abstract<const int**>();
    test_is_not_abstract<volatile int**>();
    test_is_not_abstract<const volatile int**>();
    test_is_not_abstract<int*&>();
    test_is_not_abstract<const int*&>();
    test_is_not_abstract<volatile int*&>();
    test_is_not_abstract<const volatile int*&>();
    test_is_not_abstract<int*&&>();
    test_is_not_abstract<const int*&&>();
    test_is_not_abstract<volatile int*&&>();
    test_is_not_abstract<const volatile int*&&>();
    test_is_not_abstract<void*>();
    test_is_not_abstract<char[3]>();
    test_is_not_abstract<char[]>();
    test_is_not_abstract<char[3]>();
    test_is_not_abstract<char[]>();
    test_is_not_abstract<char* [3]>();
    test_is_not_abstract<char*[]>();
    test_is_not_abstract<int(*)[3]>();
    test_is_not_abstract<int(*)[]>();
    test_is_not_abstract<int(&)[3]>();
    test_is_not_abstract<int(&)[]>();
    test_is_not_abstract<int(&&)[3]>();
    test_is_not_abstract<int(&&)[]>();
    test_is_not_abstract<char[3][2]>();
    test_is_not_abstract<char[][2]>();
    test_is_not_abstract<char* [3][2]>();
    test_is_not_abstract<char*[][2]>();
    test_is_not_abstract<int(*)[3][2]>();
    test_is_not_abstract<int(*)[][2]>();
    test_is_not_abstract<int(&)[3][2]>();
    test_is_not_abstract<int(&)[][2]>();
    test_is_not_abstract<int(&&)[3][2]>();
    test_is_not_abstract<int(&&)[][2]>();
    test_is_not_abstract<class_type>();
    test_is_not_abstract<class_type[]>();
    test_is_not_abstract<class_type[2]>();
    test_is_not_abstract<template_type<void>>();
    test_is_not_abstract<template_type<int>>();
    test_is_not_abstract<template_type<class_type>>();
    test_is_not_abstract<template_type<incomplete_type>>();
    test_is_not_abstract<variadic_template<>>();
    test_is_not_abstract<variadic_template<void>>();
    test_is_not_abstract<variadic_template<int>>();
    test_is_not_abstract<variadic_template<class_type>>();
    test_is_not_abstract<variadic_template<incomplete_type>>();
    test_is_not_abstract<variadic_template<int, void, class_type, volatile char[]>>();
    test_is_not_abstract<public_derived_from<base>>();
    test_is_not_abstract<public_derived_from<derived>>();
    test_is_not_abstract<public_derived_from<class_type>>();
    test_is_not_abstract<private_derived_from<base>>();
    test_is_not_abstract<private_derived_from<derived>>();
    test_is_not_abstract<private_derived_from<class_type>>();
    test_is_not_abstract<protected_derived_from<base>>();
    test_is_not_abstract<protected_derived_from<derived>>();
    test_is_not_abstract<protected_derived_from<class_type>>();
    test_is_not_abstract<union_type>();
    test_is_not_abstract<non_empty_union>();
    test_is_not_abstract<empty>();
    test_is_not_abstract<not_empty>();
    test_is_not_abstract<bit_zero>();
    test_is_not_abstract<bit_one>();
    test_is_not_abstract<base>();
    test_is_not_abstract<derived>();
    test_is_abstract<abstract>();
    test_is_abstract<public_abstract>();
    test_is_abstract<private_abstract>();
    test_is_abstract<protected_abstract>();
    test_is_abstract<abstract_template<int>>();
    test_is_not_abstract<abstract_template<double>>();
    test_is_abstract<abstract_template<class_type>>();
    test_is_abstract<abstract_template<incomplete_type>>();
    test_is_not_abstract<final_type>();
    test_is_not_abstract<public_destructor>();
    test_is_not_abstract<protected_destructor>();
    test_is_not_abstract<private_destructor>();
    test_is_not_abstract<virtual_public_destructor>();
    test_is_not_abstract<virtual_protected_destructor>();
    test_is_not_abstract<virtual_private_destructor>();
    test_is_abstract<pure_public_destructor>();
    test_is_abstract<pure_protected_destructor>();
    test_is_abstract<pure_private_destructor>();
    test_is_not_abstract<deleted_public_destructor>();
    test_is_not_abstract<deleted_protected_destructor>();
    test_is_not_abstract<deleted_private_destructor>();
    test_is_not_abstract<deleted_virtual_public_destructor>();
    test_is_not_abstract<deleted_virtual_protected_destructor>();
    test_is_not_abstract<deleted_virtual_private_destructor>();
    test_is_not_abstract<Enum>();
    test_is_not_abstract<EnumSigned>();
    test_is_not_abstract<EnumUnsigned>();
    test_is_not_abstract<EnumClass>();
    test_is_not_abstract<EnumStruct>();
    test_is_not_abstract<function_type>();
    test_is_not_abstract<function_ptr>();
    test_is_not_abstract<member_object_ptr>();
    test_is_not_abstract<member_function_ptr>();
    test_is_not_abstract<int class_type::*>();
    test_is_not_abstract<float class_type::*>();
    test_is_not_abstract<void * class_type::*>();
    test_is_not_abstract<int * class_type::*>();
    test_is_not_abstract<int class_type::*&>();
    test_is_not_abstract<float class_type::*&>();
    test_is_not_abstract<void * class_type::*&>();
    test_is_not_abstract<int * class_type::*&>();
    test_is_not_abstract<int class_type::*&&>();
    test_is_not_abstract<float class_type::*&&>();
    test_is_not_abstract<void * class_type::*&&>();
    test_is_not_abstract<int * class_type::*&&>();
    test_is_not_abstract<int class_type::* const>();
    test_is_not_abstract<float class_type::* const>();
    test_is_not_abstract<void * class_type::* const>();
    test_is_not_abstract<int class_type::* const&>();
    test_is_not_abstract<float class_type::* const&>();
    test_is_not_abstract<void * class_type::* const&>();
    test_is_not_abstract<int class_type::* const&&>();
    test_is_not_abstract<float class_type::* const&&>();
    test_is_not_abstract<void * class_type::* const&&>();
    test_is_not_abstract<int class_type::* volatile>();
    test_is_not_abstract<float class_type::* volatile>();
    test_is_not_abstract<void * class_type::* volatile>();
    test_is_not_abstract<int class_type::* volatile&>();
    test_is_not_abstract<float class_type::* volatile&>();
    test_is_not_abstract<void * class_type::* volatile&>();
    test_is_not_abstract<int class_type::* volatile&&>();
    test_is_not_abstract<float class_type::* volatile&&>();
    test_is_not_abstract<void * class_type::* volatile&&>();
    test_is_not_abstract<int class_type::* const volatile>();
    test_is_not_abstract<float class_type::* const volatile>();
    test_is_not_abstract<void * class_type::* const volatile>();
    test_is_not_abstract<int class_type::* const volatile&>();
    test_is_not_abstract<float class_type::* const volatile&>();
    test_is_not_abstract<void * class_type::* const volatile&>();
    test_is_not_abstract<int class_type::* const volatile&&>();
    test_is_not_abstract<float class_type::* const volatile&&>();
    test_is_not_abstract<void * class_type::* const volatile&&>();
    test_is_not_abstract<non_copyable>();
    test_is_not_abstract<non_moveable>();
    test_is_not_abstract<non_constructible>();
    test_is_not_abstract<tracked>();
    test_is_not_abstract<trap_constructible>();
    test_is_not_abstract<trap_implicit_conversion>();
    test_is_not_abstract<trap_comma>();
    test_is_not_abstract<trap_call>();
    test_is_not_abstract<trap_self_assign>();
    test_is_not_abstract<trap_deref>();
    test_is_not_abstract<trap_array_subscript>();

    test_is_not_abstract<void()>();
    test_is_not_abstract<void()&>();
    test_is_not_abstract<void() &&>();
    test_is_not_abstract<void() const>();
    test_is_not_abstract<void() const&>();
    test_is_not_abstract<void() const&&>();
    test_is_not_abstract<void() volatile>();
    test_is_not_abstract<void() volatile&>();
    test_is_not_abstract<void() volatile&&>();
    test_is_not_abstract<void() const volatile>();
    test_is_not_abstract<void() const volatile&>();
    test_is_not_abstract<void() const volatile&&>();
    test_is_not_abstract<void() noexcept>();
    test_is_not_abstract<void() & noexcept>();
    test_is_not_abstract<void() && noexcept>();
    test_is_not_abstract<void() const noexcept>();
    test_is_not_abstract<void() const & noexcept>();
    test_is_not_abstract<void() const && noexcept>();
    test_is_not_abstract<void() volatile noexcept>();
    test_is_not_abstract<void() volatile & noexcept>();
    test_is_not_abstract<void() volatile && noexcept>();
    test_is_not_abstract<void() const volatile noexcept>();
    test_is_not_abstract<void() const volatile & noexcept>();
    test_is_not_abstract<void() const volatile && noexcept>();

    test_is_not_abstract<void(int)>();
    test_is_not_abstract<void(int)&>();
    test_is_not_abstract<void(int) &&>();
    test_is_not_abstract<void(int) const>();
    test_is_not_abstract<void(int) const&>();
    test_is_not_abstract<void(int) const&&>();
    test_is_not_abstract<void(int) volatile>();
    test_is_not_abstract<void(int) volatile&>();
    test_is_not_abstract<void(int) volatile&&>();
    test_is_not_abstract<void(int) const volatile>();
    test_is_not_abstract<void(int) const volatile&>();
    test_is_not_abstract<void(int) const volatile&&>();
    test_is_not_abstract<void(int) noexcept>();
    test_is_not_abstract<void(int) & noexcept>();
    test_is_not_abstract<void(int) && noexcept>();
    test_is_not_abstract<void(int) const noexcept>();
    test_is_not_abstract<void(int) const & noexcept>();
    test_is_not_abstract<void(int) const && noexcept>();
    test_is_not_abstract<void(int) volatile noexcept>();
    test_is_not_abstract<void(int) volatile & noexcept>();
    test_is_not_abstract<void(int) volatile && noexcept>();
    test_is_not_abstract<void(int) const volatile noexcept>();
    test_is_not_abstract<void(int) const volatile & noexcept>();
    test_is_not_abstract<void(int) const volatile && noexcept>();

    test_is_not_abstract<void(...)>();
    test_is_not_abstract<void(...)&>();
    test_is_not_abstract<void(...) &&>();
    test_is_not_abstract<void(...) const>();
    test_is_not_abstract<void(...) const&>();
    test_is_not_abstract<void(...) const&&>();
    test_is_not_abstract<void(...) volatile>();
    test_is_not_abstract<void(...) volatile&>();
    test_is_not_abstract<void(...) volatile&&>();
    test_is_not_abstract<void(...) const volatile>();
    test_is_not_abstract<void(...) const volatile&>();
    test_is_not_abstract<void(...) const volatile&&>();
    test_is_not_abstract<void(...) noexcept>();
    test_is_not_abstract<void(...) & noexcept>();
    test_is_not_abstract<void(...) && noexcept>();
    test_is_not_abstract<void(...) const noexcept>();
    test_is_not_abstract<void(...) const & noexcept>();
    test_is_not_abstract<void(...) const && noexcept>();
    test_is_not_abstract<void(...) volatile noexcept>();
    test_is_not_abstract<void(...) volatile & noexcept>();
    test_is_not_abstract<void(...) volatile && noexcept>();
    test_is_not_abstract<void(...) const volatile noexcept>();
    test_is_not_abstract<void(...) const volatile & noexcept>();
    test_is_not_abstract<void(...) const volatile && noexcept>();

    test_is_not_abstract<void(int, ...)>();
    test_is_not_abstract<void(int, ...)&>();
    test_is_not_abstract<void(int, ...) &&>();
    test_is_not_abstract<void(int, ...) const>();
    test_is_not_abstract<void(int, ...) const&>();
    test_is_not_abstract<void(int, ...) const&&>();
    test_is_not_abstract<void(int, ...) volatile>();
    test_is_not_abstract<void(int, ...) volatile&>();
    test_is_not_abstract<void(int, ...) volatile&&>();
    test_is_not_abstract<void(int, ...) const volatile>();
    test_is_not_abstract<void(int, ...) const volatile&>();
    test_is_not_abstract<void(int, ...) const volatile&&>();
    test_is_not_abstract<void(int, ...) noexcept>();
    test_is_not_abstract<void(int, ...) & noexcept>();
    test_is_not_abstract<void(int, ...) && noexcept>();
    test_is_not_abstract<void(int, ...) const noexcept>();
    test_is_not_abstract<void(int, ...) const & noexcept>();
    test_is_not_abstract<void(int, ...) const && noexcept>();
    test_is_not_abstract<void(int, ...) volatile noexcept>();
    test_is_not_abstract<void(int, ...) volatile & noexcept>();
    test_is_not_abstract<void(int, ...) volatile && noexcept>();
    test_is_not_abstract<void(int, ...) const volatile noexcept>();
    test_is_not_abstract<void(int, ...) const volatile & noexcept>();
    test_is_not_abstract<void(int, ...) const volatile && noexcept>();

    test_is_not_abstract<int()>();
    test_is_not_abstract<int()&>();
    test_is_not_abstract<int() &&>();
    test_is_not_abstract<int() const>();
    test_is_not_abstract<int() const&>();
    test_is_not_abstract<int() const&&>();
    test_is_not_abstract<int() volatile>();
    test_is_not_abstract<int() volatile&>();
    test_is_not_abstract<int() volatile&&>();
    test_is_not_abstract<int() const volatile>();
    test_is_not_abstract<int() const volatile&>();
    test_is_not_abstract<int() const volatile&&>();
    test_is_not_abstract<int() noexcept>();
    test_is_not_abstract<int() & noexcept>();
    test_is_not_abstract<int() && noexcept>();
    test_is_not_abstract<int() const noexcept>();
    test_is_not_abstract<int() const & noexcept>();
    test_is_not_abstract<int() const && noexcept>();
    test_is_not_abstract<int() volatile noexcept>();
    test_is_not_abstract<int() volatile & noexcept>();
    test_is_not_abstract<int() volatile && noexcept>();
    test_is_not_abstract<int() const volatile noexcept>();
    test_is_not_abstract<int() const volatile & noexcept>();
    test_is_not_abstract<int() const volatile && noexcept>();

    test_is_not_abstract<int(int)>();
    test_is_not_abstract<int(int)&>();
    test_is_not_abstract<int(int) &&>();
    test_is_not_abstract<int(int) const>();
    test_is_not_abstract<int(int) const&>();
    test_is_not_abstract<int(int) const&&>();
    test_is_not_abstract<int(int) volatile>();
    test_is_not_abstract<int(int) volatile&>();
    test_is_not_abstract<int(int) volatile&&>();
    test_is_not_abstract<int(int) const volatile>();
    test_is_not_abstract<int(int) const volatile&>();
    test_is_not_abstract<int(int) const volatile&&>();
    test_is_not_abstract<int(int) noexcept>();
    test_is_not_abstract<int(int) & noexcept>();
    test_is_not_abstract<int(int) && noexcept>();
    test_is_not_abstract<int(int) const noexcept>();
    test_is_not_abstract<int(int) const & noexcept>();
    test_is_not_abstract<int(int) const && noexcept>();
    test_is_not_abstract<int(int) volatile noexcept>();
    test_is_not_abstract<int(int) volatile & noexcept>();
    test_is_not_abstract<int(int) volatile && noexcept>();
    test_is_not_abstract<int(int) const volatile noexcept>();
    test_is_not_abstract<int(int) const volatile & noexcept>();
    test_is_not_abstract<int(int) const volatile && noexcept>();

    test_is_not_abstract<int(...)>();
    test_is_not_abstract<int(...)&>();
    test_is_not_abstract<int(...) &&>();
    test_is_not_abstract<int(...) const>();
    test_is_not_abstract<int(...) const&>();
    test_is_not_abstract<int(...) const&&>();
    test_is_not_abstract<int(...) volatile>();
    test_is_not_abstract<int(...) volatile&>();
    test_is_not_abstract<int(...) volatile&&>();
    test_is_not_abstract<int(...) const volatile>();
    test_is_not_abstract<int(...) const volatile&>();
    test_is_not_abstract<int(...) const volatile&&>();
    test_is_not_abstract<int(...) noexcept>();
    test_is_not_abstract<int(...) & noexcept>();
    test_is_not_abstract<int(...) && noexcept>();
    test_is_not_abstract<int(...) const noexcept>();
    test_is_not_abstract<int(...) const & noexcept>();
    test_is_not_abstract<int(...) const && noexcept>();
    test_is_not_abstract<int(...) volatile noexcept>();
    test_is_not_abstract<int(...) volatile & noexcept>();
    test_is_not_abstract<int(...) volatile && noexcept>();
    test_is_not_abstract<int(...) const volatile noexcept>();
    test_is_not_abstract<int(...) const volatile & noexcept>();
    test_is_not_abstract<int(...) const volatile && noexcept>();

    test_is_not_abstract<int(int, ...)>();
    test_is_not_abstract<int(int, ...)&>();
    test_is_not_abstract<int(int, ...) &&>();
    test_is_not_abstract<int(int, ...) const>();
    test_is_not_abstract<int(int, ...) const&>();
    test_is_not_abstract<int(int, ...) const&&>();
    test_is_not_abstract<int(int, ...) volatile>();
    test_is_not_abstract<int(int, ...) volatile&>();
    test_is_not_abstract<int(int, ...) volatile&&>();
    test_is_not_abstract<int(int, ...) const volatile>();
    test_is_not_abstract<int(int, ...) const volatile&>();
    test_is_not_abstract<int(int, ...) const volatile&&>();
    test_is_not_abstract<int(int, ...) noexcept>();
    test_is_not_abstract<int(int, ...) & noexcept>();
    test_is_not_abstract<int(int, ...) && noexcept>();
    test_is_not_abstract<int(int, ...) const noexcept>();
    test_is_not_abstract<int(int, ...) const & noexcept>();
    test_is_not_abstract<int(int, ...) const && noexcept>();
    test_is_not_abstract<int(int, ...) volatile noexcept>();
    test_is_not_abstract<int(int, ...) volatile & noexcept>();
    test_is_not_abstract<int(int, ...) volatile && noexcept>();
    test_is_not_abstract<int(int, ...) const volatile noexcept>();
    test_is_not_abstract<int(int, ...) const volatile & noexcept>();
    test_is_not_abstract<int(int, ...) const volatile && noexcept>();

    test_is_not_abstract<void (*)()>();
    test_is_not_abstract<void (*)() noexcept>();

    test_is_not_abstract<void (*)(int)>();
    test_is_not_abstract<void (*)(int) noexcept>();

    test_is_not_abstract<void (*)(...)>();
    test_is_not_abstract<void (*)(...) noexcept>();

    test_is_not_abstract<void (*)(int, ...)>();
    test_is_not_abstract<void (*)(int, ...) noexcept>();

    test_is_not_abstract<int (*)()>();
    test_is_not_abstract<int (*)() noexcept>();

    test_is_not_abstract<int (*)(int)>();
    test_is_not_abstract<int (*)(int) noexcept>();

    test_is_not_abstract<int (*)(...)>();
    test_is_not_abstract<int (*)(...) noexcept>();

    test_is_not_abstract<int (*)(int, ...)>();
    test_is_not_abstract<int (*)(int, ...) noexcept>();

    test_is_not_abstract<void (&)()>();
    test_is_not_abstract<void (&)() noexcept>();

    test_is_not_abstract<void (&)(int)>();
    test_is_not_abstract<void (&)(int) noexcept>();

    test_is_not_abstract<void (&)(...)>();
    test_is_not_abstract<void (&)(...) noexcept>();

    test_is_not_abstract<void (&)(int, ...)>();
    test_is_not_abstract<void (&)(int, ...) noexcept>();

    test_is_not_abstract<int (&)()>();
    test_is_not_abstract<int (&)() noexcept>();

    test_is_not_abstract<int (&)(int)>();
    test_is_not_abstract<int (&)(int) noexcept>();

    test_is_not_abstract<int (&)(...)>();
    test_is_not_abstract<int (&)(...) noexcept>();

    test_is_not_abstract<int (&)(int, ...)>();
    test_is_not_abstract<int (&)(int, ...) noexcept>();

    test_is_not_abstract<void (&&)()>();
    test_is_not_abstract<void (&&)() noexcept>();

    test_is_not_abstract<void (&&)(int)>();
    test_is_not_abstract<void (&&)(int) noexcept>();

    test_is_not_abstract<void (&&)(...)>();
    test_is_not_abstract<void (&&)(...) noexcept>();

    test_is_not_abstract<void (&&)(int, ...)>();
    test_is_not_abstract<void (&&)(int, ...) noexcept>();

    test_is_not_abstract<int (&&)()>();
    test_is_not_abstract<int (&&)() noexcept>();

    test_is_not_abstract<int (&&)(int)>();
    test_is_not_abstract<int (&&)(int) noexcept>();

    test_is_not_abstract<int (&&)(...)>();
    test_is_not_abstract<int (&&)(...) noexcept>();

    test_is_not_abstract<int (&&)(int, ...)>();
    test_is_not_abstract<int (&&)(int, ...) noexcept>();

    test_is_not_abstract<void (class_type::*)()>();
    test_is_not_abstract<void (class_type::*)()&>();
    test_is_not_abstract<void (class_type::*)() &&>();
    test_is_not_abstract<void (class_type::*)() const>();
    test_is_not_abstract<void (class_type::*)() const&>();
    test_is_not_abstract<void (class_type::*)() const&&>();
    test_is_not_abstract<void (class_type::*)() noexcept>();
    test_is_not_abstract<void (class_type::*)() & noexcept>();
    test_is_not_abstract<void (class_type::*)() && noexcept>();
    test_is_not_abstract<void (class_type::*)() const noexcept>();
    test_is_not_abstract<void (class_type::*)() const & noexcept>();
    test_is_not_abstract<void (class_type::*)() const && noexcept>();

    test_is_not_abstract<void (class_type::*)(int)>();
    test_is_not_abstract<void (class_type::*)(int)&>();
    test_is_not_abstract<void (class_type::*)(int) &&>();
    test_is_not_abstract<void (class_type::*)(int) const>();
    test_is_not_abstract<void (class_type::*)(int) const&>();
    test_is_not_abstract<void (class_type::*)(int) const&&>();
    test_is_not_abstract<void (class_type::*)(int) noexcept>();
    test_is_not_abstract<void (class_type::*)(int) & noexcept>();
    test_is_not_abstract<void (class_type::*)(int) && noexcept>();
    test_is_not_abstract<void (class_type::*)(int) const noexcept>();
    test_is_not_abstract<void (class_type::*)(int) const & noexcept>();
    test_is_not_abstract<void (class_type::*)(int) const && noexcept>();

    test_is_not_abstract<void (class_type::*)(...)>();
    test_is_not_abstract<void (class_type::*)(...)&>();
    test_is_not_abstract<void (class_type::*)(...) &&>();
    test_is_not_abstract<void (class_type::*)(...) const>();
    test_is_not_abstract<void (class_type::*)(...) const&>();
    test_is_not_abstract<void (class_type::*)(...) const&&>();
    test_is_not_abstract<void (class_type::*)(...) noexcept>();
    test_is_not_abstract<void (class_type::*)(...) & noexcept>();
    test_is_not_abstract<void (class_type::*)(...) && noexcept>();
    test_is_not_abstract<void (class_type::*)(...) const noexcept>();
    test_is_not_abstract<void (class_type::*)(...) const & noexcept>();
    test_is_not_abstract<void (class_type::*)(...) const && noexcept>();

    test_is_not_abstract<void (class_type::*)(int, ...)>();
    test_is_not_abstract<void (class_type::*)(int, ...)&>();
    test_is_not_abstract<void (class_type::*)(int, ...) &&>();
    test_is_not_abstract<void (class_type::*)(int, ...) const>();
    test_is_not_abstract<void (class_type::*)(int, ...) const&>();
    test_is_not_abstract<void (class_type::*)(int, ...) const&&>();
    test_is_not_abstract<void (class_type::*)(int, ...) noexcept>();
    test_is_not_abstract<void (class_type::*)(int, ...) & noexcept>();
    test_is_not_abstract<void (class_type::*)(int, ...) && noexcept>();
    test_is_not_abstract<void (class_type::*)(int, ...) const noexcept>();
    test_is_not_abstract<void (class_type::*)(int, ...) const & noexcept>();
    test_is_not_abstract<void (class_type::*)(int, ...) const && noexcept>();

    test_is_not_abstract<int (class_type::*)()>();
    test_is_not_abstract<int (class_type::*)()&>();
    test_is_not_abstract<int (class_type::*)() &&>();
    test_is_not_abstract<int (class_type::*)() const>();
    test_is_not_abstract<int (class_type::*)() const&>();
    test_is_not_abstract<int (class_type::*)() const&&>();
    test_is_not_abstract<int (class_type::*)() noexcept>();
    test_is_not_abstract<int (class_type::*)() & noexcept>();
    test_is_not_abstract<int (class_type::*)() && noexcept>();
    test_is_not_abstract<int (class_type::*)() const noexcept>();
    test_is_not_abstract<int (class_type::*)() const & noexcept>();
    test_is_not_abstract<int (class_type::*)() const && noexcept>();

    test_is_not_abstract<int (class_type::*)(int)>();
    test_is_not_abstract<int (class_type::*)(int)&>();
    test_is_not_abstract<int (class_type::*)(int) &&>();
    test_is_not_abstract<int (class_type::*)(int) const>();
    test_is_not_abstract<int (class_type::*)(int) const&>();
    test_is_not_abstract<int (class_type::*)(int) const&&>();
    test_is_not_abstract<int (class_type::*)(int) noexcept>();
    test_is_not_abstract<int (class_type::*)(int) & noexcept>();
    test_is_not_abstract<int (class_type::*)(int) && noexcept>();
    test_is_not_abstract<int (class_type::*)(int) const noexcept>();
    test_is_not_abstract<int (class_type::*)(int) const & noexcept>();
    test_is_not_abstract<int (class_type::*)(int) const && noexcept>();

    test_is_not_abstract<int (class_type::*)(...)>();
    test_is_not_abstract<int (class_type::*)(...)&>();
    test_is_not_abstract<int (class_type::*)(...) &&>();
    test_is_not_abstract<int (class_type::*)(...) const>();
    test_is_not_abstract<int (class_type::*)(...) const&>();
    test_is_not_abstract<int (class_type::*)(...) const&&>();
    test_is_not_abstract<int (class_type::*)(...) noexcept>();
    test_is_not_abstract<int (class_type::*)(...) & noexcept>();
    test_is_not_abstract<int (class_type::*)(...) && noexcept>();
    test_is_not_abstract<int (class_type::*)(...) const noexcept>();
    test_is_not_abstract<int (class_type::*)(...) const & noexcept>();
    test_is_not_abstract<int (class_type::*)(...) const && noexcept>();

    test_is_not_abstract<int (class_type::*)(int, ...)>();
    test_is_not_abstract<int (class_type::*)(int, ...)&>();
    test_is_not_abstract<int (class_type::*)(int, ...) &&>();
    test_is_not_abstract<int (class_type::*)(int, ...) const>();
    test_is_not_abstract<int (class_type::*)(int, ...) const&>();
    test_is_not_abstract<int (class_type::*)(int, ...) const&&>();
    test_is_not_abstract<int (class_type::*)(int, ...) noexcept>();
    test_is_not_abstract<int (class_type::*)(int, ...) & noexcept>();
    test_is_not_abstract<int (class_type::*)(int, ...) && noexcept>();
    test_is_not_abstract<int (class_type::*)(int, ...) const noexcept>();
    test_is_not_abstract<int (class_type::*)(int, ...) const & noexcept>();
    test_is_not_abstract<int (class_type::*)(int, ...) const && noexcept>();
}
