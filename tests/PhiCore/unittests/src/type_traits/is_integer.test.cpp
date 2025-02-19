#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_integer.hpp>
#include <vector>

struct A; // incomplete

template <typename TypeT>
void test_is_integer_impl()
{
    STATIC_REQUIRE(phi::is_integer<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_integer<TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_integer_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_not_integer_v<TypeT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_integer<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_integer<TypeT>);
}

template <typename TypeT>
void test_is_integer()
{
    test_is_integer_impl<TypeT>();
    test_is_integer_impl<const TypeT>();
    test_is_integer_impl<volatile TypeT>();
    test_is_integer_impl<const volatile TypeT>();
}

template <typename TypeT>
void test_is_not_integer_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_integer<TypeT>::value);
    STATIC_REQUIRE(phi::is_not_integer<TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_integer_v<TypeT>);
    STATIC_REQUIRE(phi::is_not_integer_v<TypeT>);
#endif
}

template <typename TypeT>
void test_is_not_integer()
{
    test_is_not_integer_impl<TypeT>();
    test_is_not_integer_impl<const TypeT>();
    test_is_not_integer_impl<volatile TypeT>();
    test_is_not_integer_impl<const volatile TypeT>();
}

TEST_CASE("is_integer")
{
    test_is_not_integer<A>();

    test_is_not_integer<void>();
    test_is_not_integer<phi::nullptr_t>();
    test_is_not_integer<bool>();
    test_is_not_integer<char>();
    test_is_integer<signed char>();
    test_is_integer<unsigned char>();
    test_is_integer<short>();
    test_is_integer<unsigned short>();
    test_is_integer<int>();
    test_is_integer<unsigned int>();
    test_is_integer<long>();
    test_is_integer<unsigned long>();
    test_is_integer<long long>();
    test_is_integer<unsigned long long>();
    test_is_not_integer<float>();
    test_is_not_integer<double>();
    test_is_not_integer<long double>();
#if PHI_HAS_FEATURE_CHAR8_T()
    test_is_not_integer<char8_t>();
#endif
    test_is_not_integer<char16_t>();
    test_is_not_integer<char32_t>();
    test_is_not_integer<wchar_t>();

    test_is_not_integer<phi::boolean>();
    test_is_integer<phi::integer<signed char>>();
    test_is_integer<phi::integer<unsigned char>>();
    test_is_integer<phi::integer<short>>();
    test_is_integer<phi::integer<unsigned short>>();
    test_is_integer<phi::integer<int>>();
    test_is_integer<phi::integer<unsigned int>>();
    test_is_integer<phi::integer<long>>();
    test_is_integer<phi::integer<unsigned long>>();
    test_is_integer<phi::integer<long long>>();
    test_is_integer<phi::integer<unsigned long long>>();
    test_is_not_integer<phi::floating_point<float>>();
    test_is_not_integer<phi::floating_point<double>>();
    test_is_not_integer<phi::floating_point<long double>>();

    test_is_not_integer<std::vector<int>>();
    test_is_not_integer<phi::scope_ptr<int>>();

    test_is_not_integer<int&>();
    test_is_not_integer<const int&>();
    test_is_not_integer<volatile int&>();
    test_is_not_integer<const volatile int&>();
    test_is_not_integer<int&&>();
    test_is_not_integer<const int&&>();
    test_is_not_integer<volatile int&&>();
    test_is_not_integer<const volatile int&&>();
    test_is_not_integer<int*>();
    test_is_not_integer<const int*>();
    test_is_not_integer<volatile int*>();
    test_is_not_integer<const volatile int*>();
    test_is_not_integer<int**>();
    test_is_not_integer<const int**>();
    test_is_not_integer<volatile int**>();
    test_is_not_integer<const volatile int**>();
    test_is_not_integer<int*&>();
    test_is_not_integer<const int*&>();
    test_is_not_integer<volatile int*&>();
    test_is_not_integer<const volatile int*&>();
    test_is_not_integer<int*&&>();
    test_is_not_integer<const int*&&>();
    test_is_not_integer<volatile int*&&>();
    test_is_not_integer<const volatile int*&&>();
    test_is_not_integer<void*>();
    test_is_not_integer<char[3]>();
    test_is_not_integer<char[]>();
    test_is_not_integer<char* [3]>();
    test_is_not_integer<char*[]>();
    test_is_not_integer<int(*)[3]>();
    test_is_not_integer<int(*)[]>();
    test_is_not_integer<int(&)[3]>();
    test_is_not_integer<int(&)[]>();
    test_is_not_integer<int(&&)[3]>();
    test_is_not_integer<int(&&)[]>();
    test_is_not_integer<char[3][2]>();
    test_is_not_integer<char[][2]>();
    test_is_not_integer<char* [3][2]>();
    test_is_not_integer<char*[][2]>();
    test_is_not_integer<int(*)[3][2]>();
    test_is_not_integer<int(*)[][2]>();
    test_is_not_integer<int(&)[3][2]>();
    test_is_not_integer<int(&)[][2]>();
    test_is_not_integer<int(&&)[3][2]>();
    test_is_not_integer<int(&&)[][2]>();
    test_is_not_integer<class_type>();
    test_is_not_integer<class_type[]>();
    test_is_not_integer<class_type[2]>();
    test_is_not_integer<template_type<void>>();
    test_is_not_integer<template_type<int>>();
    test_is_not_integer<template_type<class_type>>();
    test_is_not_integer<template_type<incomplete_type>>();
    test_is_not_integer<variadic_template<>>();
    test_is_not_integer<variadic_template<void>>();
    test_is_not_integer<variadic_template<int>>();
    test_is_not_integer<variadic_template<class_type>>();
    test_is_not_integer<variadic_template<incomplete_type>>();
    test_is_not_integer<variadic_template<int, void, class_type, volatile char[]>>();
    test_is_not_integer<public_derived_from<base>>();
    test_is_not_integer<public_derived_from<derived>>();
    test_is_not_integer<public_derived_from<class_type>>();
    test_is_not_integer<private_derived_from<base>>();
    test_is_not_integer<private_derived_from<derived>>();
    test_is_not_integer<private_derived_from<class_type>>();
    test_is_not_integer<protected_derived_from<base>>();
    test_is_not_integer<protected_derived_from<derived>>();
    test_is_not_integer<protected_derived_from<class_type>>();
    test_is_not_integer<union_type>();
    test_is_not_integer<non_empty_union>();
    test_is_not_integer<empty>();
    test_is_not_integer<not_empty>();
    test_is_not_integer<bit_zero>();
    test_is_not_integer<bit_one>();
    test_is_not_integer<base>();
    test_is_not_integer<derived>();
    test_is_not_integer<abstract>();
    test_is_not_integer<public_abstract>();
    test_is_not_integer<private_abstract>();
    test_is_not_integer<protected_abstract>();
    test_is_not_integer<abstract_template<int>>();
    test_is_not_integer<abstract_template<double>>();
    test_is_not_integer<abstract_template<class_type>>();
    test_is_not_integer<abstract_template<incomplete_type>>();
    test_is_not_integer<final_type>();
    test_is_not_integer<public_destructor>();
    test_is_not_integer<protected_destructor>();
    test_is_not_integer<private_destructor>();
    test_is_not_integer<virtual_public_destructor>();
    test_is_not_integer<virtual_protected_destructor>();
    test_is_not_integer<virtual_private_destructor>();
    test_is_not_integer<pure_public_destructor>();
    test_is_not_integer<pure_protected_destructor>();
    test_is_not_integer<pure_private_destructor>();
    test_is_not_integer<deleted_public_destructor>();
    test_is_not_integer<deleted_protected_destructor>();
    test_is_not_integer<deleted_private_destructor>();
    test_is_not_integer<deleted_virtual_public_destructor>();
    test_is_not_integer<deleted_virtual_protected_destructor>();
    test_is_not_integer<deleted_virtual_private_destructor>();
    test_is_not_integer<Enum>();
    test_is_not_integer<EnumSigned>();
    test_is_not_integer<EnumUnsigned>();
    test_is_not_integer<EnumClass>();
    test_is_not_integer<EnumStruct>();
    test_is_not_integer<function_type>();
    test_is_not_integer<function_ptr>();
    test_is_not_integer<member_object_ptr>();
    test_is_not_integer<member_function_ptr>();
    test_is_not_integer<incomplete_type>();
    test_is_not_integer<incomplete_template<void>>();
    test_is_not_integer<incomplete_template<int>>();
    test_is_not_integer<incomplete_template<class_type>>();
    test_is_not_integer<incomplete_template<incomplete_type>>();
    test_is_not_integer<incomplete_variadic_template<>>();
    test_is_not_integer<incomplete_variadic_template<void>>();
    test_is_not_integer<incomplete_variadic_template<int>>();
    test_is_not_integer<incomplete_variadic_template<class_type>>();
    test_is_not_integer<incomplete_variadic_template<incomplete_type>>();
    test_is_not_integer<incomplete_variadic_template<int, void, class_type, volatile char[]>>();
    test_is_not_integer<int class_type::*>();
    test_is_not_integer<float class_type::*>();
    test_is_not_integer<void * class_type::*>();
    test_is_not_integer<int * class_type::*>();
    test_is_not_integer<int class_type::*&>();
    test_is_not_integer<float class_type::*&>();
    test_is_not_integer<void * class_type::*&>();
    test_is_not_integer<int * class_type::*&>();
    test_is_not_integer<int class_type::*&&>();
    test_is_not_integer<float class_type::*&&>();
    test_is_not_integer<void * class_type::*&&>();
    test_is_not_integer<int * class_type::*&&>();
    test_is_not_integer<int class_type::* const>();
    test_is_not_integer<float class_type::* const>();
    test_is_not_integer<void * class_type::* const>();
    test_is_not_integer<int class_type::* const&>();
    test_is_not_integer<float class_type::* const&>();
    test_is_not_integer<void * class_type::* const&>();
    test_is_not_integer<int class_type::* const&&>();
    test_is_not_integer<float class_type::* const&&>();
    test_is_not_integer<void * class_type::* const&&>();
    test_is_not_integer<int class_type::* volatile>();
    test_is_not_integer<float class_type::* volatile>();
    test_is_not_integer<void * class_type::* volatile>();
    test_is_not_integer<int class_type::* volatile&>();
    test_is_not_integer<float class_type::* volatile&>();
    test_is_not_integer<void * class_type::* volatile&>();
    test_is_not_integer<int class_type::* volatile&&>();
    test_is_not_integer<float class_type::* volatile&&>();
    test_is_not_integer<void * class_type::* volatile&&>();
    test_is_not_integer<int class_type::* const volatile>();
    test_is_not_integer<float class_type::* const volatile>();
    test_is_not_integer<void * class_type::* const volatile>();
    test_is_not_integer<int class_type::* const volatile&>();
    test_is_not_integer<float class_type::* const volatile&>();
    test_is_not_integer<void * class_type::* const volatile&>();
    test_is_not_integer<int class_type::* const volatile&&>();
    test_is_not_integer<float class_type::* const volatile&&>();
    test_is_not_integer<void * class_type::* const volatile&&>();
    test_is_not_integer<non_copyable>();
    test_is_not_integer<non_moveable>();
    test_is_not_integer<non_constructible>();
    test_is_not_integer<tracked>();
    test_is_not_integer<trap_constructible>();
    test_is_not_integer<trap_implicit_conversion>();
    test_is_not_integer<trap_comma>();
    test_is_not_integer<trap_call>();
    test_is_not_integer<trap_self_assign>();
    test_is_not_integer<trap_deref>();
    test_is_not_integer<trap_array_subscript>();

    test_is_not_integer<void()>();
    test_is_not_integer<void()&>();
    test_is_not_integer<void() &&>();
    test_is_not_integer<void() const>();
    test_is_not_integer<void() const&>();
    test_is_not_integer<void() const&&>();
    test_is_not_integer<void() volatile>();
    test_is_not_integer<void() volatile&>();
    test_is_not_integer<void() volatile&&>();
    test_is_not_integer<void() const volatile>();
    test_is_not_integer<void() const volatile&>();
    test_is_not_integer<void() const volatile&&>();
    test_is_not_integer<void() noexcept>();
    test_is_not_integer<void() & noexcept>();
    test_is_not_integer<void() && noexcept>();
    test_is_not_integer<void() const noexcept>();
    test_is_not_integer<void() const & noexcept>();
    test_is_not_integer<void() const && noexcept>();
    test_is_not_integer<void() volatile noexcept>();
    test_is_not_integer<void() volatile & noexcept>();
    test_is_not_integer<void() volatile && noexcept>();
    test_is_not_integer<void() const volatile noexcept>();
    test_is_not_integer<void() const volatile & noexcept>();
    test_is_not_integer<void() const volatile && noexcept>();

    test_is_not_integer<void(int)>();
    test_is_not_integer<void(int)&>();
    test_is_not_integer<void(int) &&>();
    test_is_not_integer<void(int) const>();
    test_is_not_integer<void(int) const&>();
    test_is_not_integer<void(int) const&&>();
    test_is_not_integer<void(int) volatile>();
    test_is_not_integer<void(int) volatile&>();
    test_is_not_integer<void(int) volatile&&>();
    test_is_not_integer<void(int) const volatile>();
    test_is_not_integer<void(int) const volatile&>();
    test_is_not_integer<void(int) const volatile&&>();
    test_is_not_integer<void(int) noexcept>();
    test_is_not_integer<void(int) & noexcept>();
    test_is_not_integer<void(int) && noexcept>();
    test_is_not_integer<void(int) const noexcept>();
    test_is_not_integer<void(int) const & noexcept>();
    test_is_not_integer<void(int) const && noexcept>();
    test_is_not_integer<void(int) volatile noexcept>();
    test_is_not_integer<void(int) volatile & noexcept>();
    test_is_not_integer<void(int) volatile && noexcept>();
    test_is_not_integer<void(int) const volatile noexcept>();
    test_is_not_integer<void(int) const volatile & noexcept>();
    test_is_not_integer<void(int) const volatile && noexcept>();

    test_is_not_integer<void(...)>();
    test_is_not_integer<void(...)&>();
    test_is_not_integer<void(...) &&>();
    test_is_not_integer<void(...) const>();
    test_is_not_integer<void(...) const&>();
    test_is_not_integer<void(...) const&&>();
    test_is_not_integer<void(...) volatile>();
    test_is_not_integer<void(...) volatile&>();
    test_is_not_integer<void(...) volatile&&>();
    test_is_not_integer<void(...) const volatile>();
    test_is_not_integer<void(...) const volatile&>();
    test_is_not_integer<void(...) const volatile&&>();
    test_is_not_integer<void(...) noexcept>();
    test_is_not_integer<void(...) & noexcept>();
    test_is_not_integer<void(...) && noexcept>();
    test_is_not_integer<void(...) const noexcept>();
    test_is_not_integer<void(...) const & noexcept>();
    test_is_not_integer<void(...) const && noexcept>();
    test_is_not_integer<void(...) volatile noexcept>();
    test_is_not_integer<void(...) volatile & noexcept>();
    test_is_not_integer<void(...) volatile && noexcept>();
    test_is_not_integer<void(...) const volatile noexcept>();
    test_is_not_integer<void(...) const volatile & noexcept>();
    test_is_not_integer<void(...) const volatile && noexcept>();

    test_is_not_integer<void(int, ...)>();
    test_is_not_integer<void(int, ...)&>();
    test_is_not_integer<void(int, ...) &&>();
    test_is_not_integer<void(int, ...) const>();
    test_is_not_integer<void(int, ...) const&>();
    test_is_not_integer<void(int, ...) const&&>();
    test_is_not_integer<void(int, ...) volatile>();
    test_is_not_integer<void(int, ...) volatile&>();
    test_is_not_integer<void(int, ...) volatile&&>();
    test_is_not_integer<void(int, ...) const volatile>();
    test_is_not_integer<void(int, ...) const volatile&>();
    test_is_not_integer<void(int, ...) const volatile&&>();
    test_is_not_integer<void(int, ...) noexcept>();
    test_is_not_integer<void(int, ...) & noexcept>();
    test_is_not_integer<void(int, ...) && noexcept>();
    test_is_not_integer<void(int, ...) const noexcept>();
    test_is_not_integer<void(int, ...) const & noexcept>();
    test_is_not_integer<void(int, ...) const && noexcept>();
    test_is_not_integer<void(int, ...) volatile noexcept>();
    test_is_not_integer<void(int, ...) volatile & noexcept>();
    test_is_not_integer<void(int, ...) volatile && noexcept>();
    test_is_not_integer<void(int, ...) const volatile noexcept>();
    test_is_not_integer<void(int, ...) const volatile & noexcept>();
    test_is_not_integer<void(int, ...) const volatile && noexcept>();

    test_is_not_integer<int()>();
    test_is_not_integer<int()&>();
    test_is_not_integer<int() &&>();
    test_is_not_integer<int() const>();
    test_is_not_integer<int() const&>();
    test_is_not_integer<int() const&&>();
    test_is_not_integer<int() volatile>();
    test_is_not_integer<int() volatile&>();
    test_is_not_integer<int() volatile&&>();
    test_is_not_integer<int() const volatile>();
    test_is_not_integer<int() const volatile&>();
    test_is_not_integer<int() const volatile&&>();
    test_is_not_integer<int() noexcept>();
    test_is_not_integer<int() & noexcept>();
    test_is_not_integer<int() && noexcept>();
    test_is_not_integer<int() const noexcept>();
    test_is_not_integer<int() const & noexcept>();
    test_is_not_integer<int() const && noexcept>();
    test_is_not_integer<int() volatile noexcept>();
    test_is_not_integer<int() volatile & noexcept>();
    test_is_not_integer<int() volatile && noexcept>();
    test_is_not_integer<int() const volatile noexcept>();
    test_is_not_integer<int() const volatile & noexcept>();
    test_is_not_integer<int() const volatile && noexcept>();

    test_is_not_integer<int(int)>();
    test_is_not_integer<int(int)&>();
    test_is_not_integer<int(int) &&>();
    test_is_not_integer<int(int) const>();
    test_is_not_integer<int(int) const&>();
    test_is_not_integer<int(int) const&&>();
    test_is_not_integer<int(int) volatile>();
    test_is_not_integer<int(int) volatile&>();
    test_is_not_integer<int(int) volatile&&>();
    test_is_not_integer<int(int) const volatile>();
    test_is_not_integer<int(int) const volatile&>();
    test_is_not_integer<int(int) const volatile&&>();
    test_is_not_integer<int(int) noexcept>();
    test_is_not_integer<int(int) & noexcept>();
    test_is_not_integer<int(int) && noexcept>();
    test_is_not_integer<int(int) const noexcept>();
    test_is_not_integer<int(int) const & noexcept>();
    test_is_not_integer<int(int) const && noexcept>();
    test_is_not_integer<int(int) volatile noexcept>();
    test_is_not_integer<int(int) volatile & noexcept>();
    test_is_not_integer<int(int) volatile && noexcept>();
    test_is_not_integer<int(int) const volatile noexcept>();
    test_is_not_integer<int(int) const volatile & noexcept>();
    test_is_not_integer<int(int) const volatile && noexcept>();

    test_is_not_integer<int(...)>();
    test_is_not_integer<int(...)&>();
    test_is_not_integer<int(...) &&>();
    test_is_not_integer<int(...) const>();
    test_is_not_integer<int(...) const&>();
    test_is_not_integer<int(...) const&&>();
    test_is_not_integer<int(...) volatile>();
    test_is_not_integer<int(...) volatile&>();
    test_is_not_integer<int(...) volatile&&>();
    test_is_not_integer<int(...) const volatile>();
    test_is_not_integer<int(...) const volatile&>();
    test_is_not_integer<int(...) const volatile&&>();
    test_is_not_integer<int(...) noexcept>();
    test_is_not_integer<int(...) & noexcept>();
    test_is_not_integer<int(...) && noexcept>();
    test_is_not_integer<int(...) const noexcept>();
    test_is_not_integer<int(...) const & noexcept>();
    test_is_not_integer<int(...) const && noexcept>();
    test_is_not_integer<int(...) volatile noexcept>();
    test_is_not_integer<int(...) volatile & noexcept>();
    test_is_not_integer<int(...) volatile && noexcept>();
    test_is_not_integer<int(...) const volatile noexcept>();
    test_is_not_integer<int(...) const volatile & noexcept>();
    test_is_not_integer<int(...) const volatile && noexcept>();

    test_is_not_integer<int(int, ...)>();
    test_is_not_integer<int(int, ...)&>();
    test_is_not_integer<int(int, ...) &&>();
    test_is_not_integer<int(int, ...) const>();
    test_is_not_integer<int(int, ...) const&>();
    test_is_not_integer<int(int, ...) const&&>();
    test_is_not_integer<int(int, ...) volatile>();
    test_is_not_integer<int(int, ...) volatile&>();
    test_is_not_integer<int(int, ...) volatile&&>();
    test_is_not_integer<int(int, ...) const volatile>();
    test_is_not_integer<int(int, ...) const volatile&>();
    test_is_not_integer<int(int, ...) const volatile&&>();
    test_is_not_integer<int(int, ...) noexcept>();
    test_is_not_integer<int(int, ...) & noexcept>();
    test_is_not_integer<int(int, ...) && noexcept>();
    test_is_not_integer<int(int, ...) const noexcept>();
    test_is_not_integer<int(int, ...) const & noexcept>();
    test_is_not_integer<int(int, ...) const && noexcept>();
    test_is_not_integer<int(int, ...) volatile noexcept>();
    test_is_not_integer<int(int, ...) volatile & noexcept>();
    test_is_not_integer<int(int, ...) volatile && noexcept>();
    test_is_not_integer<int(int, ...) const volatile noexcept>();
    test_is_not_integer<int(int, ...) const volatile & noexcept>();
    test_is_not_integer<int(int, ...) const volatile && noexcept>();

    test_is_not_integer<void (*)()>();
    test_is_not_integer<void (*)() noexcept>();

    test_is_not_integer<void (*)(int)>();
    test_is_not_integer<void (*)(int) noexcept>();

    test_is_not_integer<void (*)(...)>();
    test_is_not_integer<void (*)(...) noexcept>();

    test_is_not_integer<void (*)(int, ...)>();
    test_is_not_integer<void (*)(int, ...) noexcept>();

    test_is_not_integer<int (*)()>();
    test_is_not_integer<int (*)() noexcept>();

    test_is_not_integer<int (*)(int)>();
    test_is_not_integer<int (*)(int) noexcept>();

    test_is_not_integer<int (*)(...)>();
    test_is_not_integer<int (*)(...) noexcept>();

    test_is_not_integer<int (*)(int, ...)>();
    test_is_not_integer<int (*)(int, ...) noexcept>();

    test_is_not_integer<void (&)()>();
    test_is_not_integer<void (&)() noexcept>();

    test_is_not_integer<void (&)(int)>();
    test_is_not_integer<void (&)(int) noexcept>();

    test_is_not_integer<void (&)(...)>();
    test_is_not_integer<void (&)(...) noexcept>();

    test_is_not_integer<void (&)(int, ...)>();
    test_is_not_integer<void (&)(int, ...) noexcept>();

    test_is_not_integer<int (&)()>();
    test_is_not_integer<int (&)() noexcept>();

    test_is_not_integer<int (&)(int)>();
    test_is_not_integer<int (&)(int) noexcept>();

    test_is_not_integer<int (&)(...)>();
    test_is_not_integer<int (&)(...) noexcept>();

    test_is_not_integer<int (&)(int, ...)>();
    test_is_not_integer<int (&)(int, ...) noexcept>();

    test_is_not_integer<void (&&)()>();
    test_is_not_integer<void (&&)() noexcept>();

    test_is_not_integer<void (&&)(int)>();
    test_is_not_integer<void (&&)(int) noexcept>();

    test_is_not_integer<void (&&)(...)>();
    test_is_not_integer<void (&&)(...) noexcept>();

    test_is_not_integer<void (&&)(int, ...)>();
    test_is_not_integer<void (&&)(int, ...) noexcept>();

    test_is_not_integer<int (&&)()>();
    test_is_not_integer<int (&&)() noexcept>();

    test_is_not_integer<int (&&)(int)>();
    test_is_not_integer<int (&&)(int) noexcept>();

    test_is_not_integer<int (&&)(...)>();
    test_is_not_integer<int (&&)(...) noexcept>();

    test_is_not_integer<int (&&)(int, ...)>();
    test_is_not_integer<int (&&)(int, ...) noexcept>();

    test_is_not_integer<void (class_type::*)()>();
    test_is_not_integer<void (class_type::*)()&>();
    test_is_not_integer<void (class_type::*)() &&>();
    test_is_not_integer<void (class_type::*)() const>();
    test_is_not_integer<void (class_type::*)() const&>();
    test_is_not_integer<void (class_type::*)() const&&>();
    test_is_not_integer<void (class_type::*)() noexcept>();
    test_is_not_integer<void (class_type::*)() & noexcept>();
    test_is_not_integer<void (class_type::*)() && noexcept>();
    test_is_not_integer<void (class_type::*)() const noexcept>();
    test_is_not_integer<void (class_type::*)() const & noexcept>();
    test_is_not_integer<void (class_type::*)() const && noexcept>();

    test_is_not_integer<void (class_type::*)(int)>();
    test_is_not_integer<void (class_type::*)(int)&>();
    test_is_not_integer<void (class_type::*)(int) &&>();
    test_is_not_integer<void (class_type::*)(int) const>();
    test_is_not_integer<void (class_type::*)(int) const&>();
    test_is_not_integer<void (class_type::*)(int) const&&>();
    test_is_not_integer<void (class_type::*)(int) noexcept>();
    test_is_not_integer<void (class_type::*)(int) & noexcept>();
    test_is_not_integer<void (class_type::*)(int) && noexcept>();
    test_is_not_integer<void (class_type::*)(int) const noexcept>();
    test_is_not_integer<void (class_type::*)(int) const & noexcept>();
    test_is_not_integer<void (class_type::*)(int) const && noexcept>();

    test_is_not_integer<void (class_type::*)(...)>();
    test_is_not_integer<void (class_type::*)(...)&>();
    test_is_not_integer<void (class_type::*)(...) &&>();
    test_is_not_integer<void (class_type::*)(...) const>();
    test_is_not_integer<void (class_type::*)(...) const&>();
    test_is_not_integer<void (class_type::*)(...) const&&>();
    test_is_not_integer<void (class_type::*)(...) noexcept>();
    test_is_not_integer<void (class_type::*)(...) & noexcept>();
    test_is_not_integer<void (class_type::*)(...) && noexcept>();
    test_is_not_integer<void (class_type::*)(...) const noexcept>();
    test_is_not_integer<void (class_type::*)(...) const & noexcept>();
    test_is_not_integer<void (class_type::*)(...) const && noexcept>();

    test_is_not_integer<void (class_type::*)(int, ...)>();
    test_is_not_integer<void (class_type::*)(int, ...)&>();
    test_is_not_integer<void (class_type::*)(int, ...) &&>();
    test_is_not_integer<void (class_type::*)(int, ...) const>();
    test_is_not_integer<void (class_type::*)(int, ...) const&>();
    test_is_not_integer<void (class_type::*)(int, ...) const&&>();
    test_is_not_integer<void (class_type::*)(int, ...) noexcept>();
    test_is_not_integer<void (class_type::*)(int, ...) & noexcept>();
    test_is_not_integer<void (class_type::*)(int, ...) && noexcept>();
    test_is_not_integer<void (class_type::*)(int, ...) const noexcept>();
    test_is_not_integer<void (class_type::*)(int, ...) const & noexcept>();
    test_is_not_integer<void (class_type::*)(int, ...) const && noexcept>();

    test_is_not_integer<int (class_type::*)()>();
    test_is_not_integer<int (class_type::*)()&>();
    test_is_not_integer<int (class_type::*)() &&>();
    test_is_not_integer<int (class_type::*)() const>();
    test_is_not_integer<int (class_type::*)() const&>();
    test_is_not_integer<int (class_type::*)() const&&>();
    test_is_not_integer<int (class_type::*)() noexcept>();
    test_is_not_integer<int (class_type::*)() & noexcept>();
    test_is_not_integer<int (class_type::*)() && noexcept>();
    test_is_not_integer<int (class_type::*)() const noexcept>();
    test_is_not_integer<int (class_type::*)() const & noexcept>();
    test_is_not_integer<int (class_type::*)() const && noexcept>();

    test_is_not_integer<int (class_type::*)(int)>();
    test_is_not_integer<int (class_type::*)(int)&>();
    test_is_not_integer<int (class_type::*)(int) &&>();
    test_is_not_integer<int (class_type::*)(int) const>();
    test_is_not_integer<int (class_type::*)(int) const&>();
    test_is_not_integer<int (class_type::*)(int) const&&>();
    test_is_not_integer<int (class_type::*)(int) noexcept>();
    test_is_not_integer<int (class_type::*)(int) & noexcept>();
    test_is_not_integer<int (class_type::*)(int) && noexcept>();
    test_is_not_integer<int (class_type::*)(int) const noexcept>();
    test_is_not_integer<int (class_type::*)(int) const & noexcept>();
    test_is_not_integer<int (class_type::*)(int) const && noexcept>();

    test_is_not_integer<int (class_type::*)(...)>();
    test_is_not_integer<int (class_type::*)(...)&>();
    test_is_not_integer<int (class_type::*)(...) &&>();
    test_is_not_integer<int (class_type::*)(...) const>();
    test_is_not_integer<int (class_type::*)(...) const&>();
    test_is_not_integer<int (class_type::*)(...) const&&>();
    test_is_not_integer<int (class_type::*)(...) noexcept>();
    test_is_not_integer<int (class_type::*)(...) & noexcept>();
    test_is_not_integer<int (class_type::*)(...) && noexcept>();
    test_is_not_integer<int (class_type::*)(...) const noexcept>();
    test_is_not_integer<int (class_type::*)(...) const & noexcept>();
    test_is_not_integer<int (class_type::*)(...) const && noexcept>();

    test_is_not_integer<int (class_type::*)(int, ...)>();
    test_is_not_integer<int (class_type::*)(int, ...)&>();
    test_is_not_integer<int (class_type::*)(int, ...) &&>();
    test_is_not_integer<int (class_type::*)(int, ...) const>();
    test_is_not_integer<int (class_type::*)(int, ...) const&>();
    test_is_not_integer<int (class_type::*)(int, ...) const&&>();
    test_is_not_integer<int (class_type::*)(int, ...) noexcept>();
    test_is_not_integer<int (class_type::*)(int, ...) & noexcept>();
    test_is_not_integer<int (class_type::*)(int, ...) && noexcept>();
    test_is_not_integer<int (class_type::*)(int, ...) const noexcept>();
    test_is_not_integer<int (class_type::*)(int, ...) const & noexcept>();
    test_is_not_integer<int (class_type::*)(int, ...) const && noexcept>();
}
