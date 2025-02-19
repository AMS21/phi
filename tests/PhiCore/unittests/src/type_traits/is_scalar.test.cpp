#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_scalar.hpp>
#include <vector>

template <typename TypeT>
void test_is_scalar_impl()
{
#if PHI_HAS_WORKING_IS_SCALAR()
    STATIC_REQUIRE(phi::is_scalar<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_scalar<TypeT>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_scalar_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_not_scalar_v<TypeT>);
#    endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_scalar<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_scalar<TypeT>);
#endif
}

template <typename TypeT>
void test_is_not_scalar_impl()
{
#if PHI_HAS_WORKING_IS_SCALAR()
    STATIC_REQUIRE_FALSE(phi::is_scalar<TypeT>::value);
    STATIC_REQUIRE(phi::is_not_scalar<TypeT>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_scalar_v<TypeT>);
    STATIC_REQUIRE(phi::is_not_scalar_v<TypeT>);
#    endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_scalar<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_scalar<TypeT>);
#endif
}

template <typename TypeT>
void test_is_scalar()
{
    test_is_scalar_impl<TypeT>();
    test_is_scalar_impl<const TypeT>();
    test_is_scalar_impl<volatile TypeT>();
    test_is_scalar_impl<const volatile TypeT>();
}

template <typename TypeT>
void test_is_not_scalar()
{
    test_is_not_scalar_impl<TypeT>();
    test_is_not_scalar_impl<const TypeT>();
    test_is_not_scalar_impl<volatile TypeT>();
    test_is_not_scalar_impl<const volatile TypeT>();
}

TEST_CASE("is_scalar")
{
    test_is_not_scalar<void>();
    test_is_scalar<phi::nullptr_t>();
    test_is_scalar<bool>();
    test_is_scalar<char>();
    test_is_scalar<signed char>();
    test_is_scalar<unsigned char>();
    test_is_scalar<short>();
    test_is_scalar<unsigned short>();
    test_is_scalar<int>();
    test_is_scalar<unsigned int>();
    test_is_scalar<long>();
    test_is_scalar<unsigned long>();
    test_is_scalar<long long>();
    test_is_scalar<unsigned long long>();
    test_is_scalar<float>();
    test_is_scalar<double>();
    test_is_scalar<long double>();
    test_is_scalar<char8_t>();
    test_is_scalar<char16_t>();
    test_is_scalar<char32_t>();
    test_is_scalar<wchar_t>();

    test_is_scalar<phi::boolean>();
    test_is_scalar<phi::integer<signed char>>();
    test_is_scalar<phi::integer<unsigned char>>();
    test_is_scalar<phi::integer<short>>();
    test_is_scalar<phi::integer<unsigned short>>();
    test_is_scalar<phi::integer<int>>();
    test_is_scalar<phi::integer<unsigned int>>();
    test_is_scalar<phi::integer<long>>();
    test_is_scalar<phi::integer<unsigned long>>();
    test_is_scalar<phi::integer<long long>>();
    test_is_scalar<phi::integer<unsigned long long>>();
    test_is_scalar<phi::floating_point<float>>();
    test_is_scalar<phi::floating_point<double>>();
    test_is_scalar<phi::floating_point<long double>>();

    test_is_not_scalar<std::vector<int>>();
    test_is_not_scalar<phi::scope_ptr<int>>();

    test_is_not_scalar<int&>();
    test_is_not_scalar<const int&>();
    test_is_not_scalar<volatile int&>();
    test_is_not_scalar<const volatile int&>();
    test_is_not_scalar<int&&>();
    test_is_not_scalar<const int&&>();
    test_is_not_scalar<volatile int&&>();
    test_is_not_scalar<const volatile int&&>();
    test_is_scalar<int*>();
    test_is_scalar<const int*>();
    test_is_scalar<volatile int*>();
    test_is_scalar<const volatile int*>();
    test_is_scalar<int**>();
    test_is_scalar<const int**>();
    test_is_scalar<volatile int**>();
    test_is_scalar<const volatile int**>();
    test_is_not_scalar<int*&>();
    test_is_not_scalar<const int*&>();
    test_is_not_scalar<volatile int*&>();
    test_is_not_scalar<const volatile int*&>();
    test_is_not_scalar<int*&&>();
    test_is_not_scalar<const int*&&>();
    test_is_not_scalar<volatile int*&&>();
    test_is_not_scalar<const volatile int*&&>();
    test_is_scalar<void*>();
    test_is_not_scalar<char[3]>();
    test_is_not_scalar<char[]>();
    test_is_not_scalar<char* [3]>();
    test_is_not_scalar<char*[]>();
    test_is_scalar<int(*)[3]>();
    test_is_scalar<int(*)[]>();
    test_is_not_scalar<int(&)[3]>();
    test_is_not_scalar<int(&)[]>();
    test_is_not_scalar<int(&&)[3]>();
    test_is_not_scalar<int(&&)[]>();
    test_is_not_scalar<char[3][2]>();
    test_is_not_scalar<char[][2]>();
    test_is_not_scalar<char* [3][2]>();
    test_is_not_scalar<char*[][2]>();
    test_is_scalar<int(*)[3][2]>();
    test_is_scalar<int(*)[][2]>();
    test_is_not_scalar<int(&)[3][2]>();
    test_is_not_scalar<int(&)[][2]>();
    test_is_not_scalar<int(&&)[3][2]>();
    test_is_not_scalar<int(&&)[][2]>();
    test_is_not_scalar<class_type>();
    test_is_not_scalar<class_type[]>();
    test_is_not_scalar<class_type[2]>();
    test_is_not_scalar<template_type<void>>();
    test_is_not_scalar<template_type<int>>();
    test_is_not_scalar<template_type<class_type>>();
    test_is_not_scalar<template_type<incomplete_type>>();
    test_is_not_scalar<variadic_template<>>();
    test_is_not_scalar<variadic_template<void>>();
    test_is_not_scalar<variadic_template<int>>();
    test_is_not_scalar<variadic_template<class_type>>();
    test_is_not_scalar<variadic_template<incomplete_type>>();
    test_is_not_scalar<variadic_template<int, void, class_type, volatile char[]>>();
    test_is_not_scalar<public_derived_from<base>>();
    test_is_not_scalar<public_derived_from<derived>>();
    test_is_not_scalar<public_derived_from<class_type>>();
    test_is_not_scalar<private_derived_from<base>>();
    test_is_not_scalar<private_derived_from<derived>>();
    test_is_not_scalar<private_derived_from<class_type>>();
    test_is_not_scalar<protected_derived_from<base>>();
    test_is_not_scalar<protected_derived_from<derived>>();
    test_is_not_scalar<protected_derived_from<class_type>>();
    test_is_not_scalar<union_type>();
    test_is_not_scalar<non_empty_union>();
    test_is_not_scalar<empty>();
    test_is_not_scalar<not_empty>();
    test_is_not_scalar<bit_zero>();
    test_is_not_scalar<bit_one>();
    test_is_not_scalar<base>();
    test_is_not_scalar<derived>();
    test_is_not_scalar<abstract>();
    test_is_not_scalar<public_abstract>();
    test_is_not_scalar<private_abstract>();
    test_is_not_scalar<protected_abstract>();
    test_is_not_scalar<abstract_template<int>>();
    test_is_not_scalar<abstract_template<double>>();
    test_is_not_scalar<abstract_template<class_type>>();
    test_is_not_scalar<abstract_template<incomplete_type>>();
    test_is_not_scalar<final_type>();
    test_is_not_scalar<public_destructor>();
    test_is_not_scalar<protected_destructor>();
    test_is_not_scalar<private_destructor>();
    test_is_not_scalar<virtual_public_destructor>();
    test_is_not_scalar<virtual_protected_destructor>();
    test_is_not_scalar<virtual_private_destructor>();
    test_is_not_scalar<pure_public_destructor>();
    test_is_not_scalar<pure_protected_destructor>();
    test_is_not_scalar<pure_private_destructor>();
    test_is_not_scalar<deleted_public_destructor>();
    test_is_not_scalar<deleted_protected_destructor>();
    test_is_not_scalar<deleted_private_destructor>();
    test_is_not_scalar<deleted_virtual_public_destructor>();
    test_is_not_scalar<deleted_virtual_protected_destructor>();
    test_is_not_scalar<deleted_virtual_private_destructor>();
    test_is_scalar<Enum>();
    test_is_scalar<EnumSigned>();
    test_is_scalar<EnumUnsigned>();
    test_is_scalar<EnumClass>();
    test_is_scalar<EnumStruct>();
    test_is_not_scalar<function_type>();
    test_is_scalar<function_ptr>();
    test_is_scalar<member_object_ptr>();
    test_is_scalar<member_function_ptr>();
    test_is_not_scalar<incomplete_type>();
    test_is_not_scalar<incomplete_template<void>>();
    test_is_not_scalar<incomplete_template<int>>();
    test_is_not_scalar<incomplete_template<class_type>>();
    test_is_not_scalar<incomplete_template<incomplete_type>>();
    test_is_not_scalar<incomplete_variadic_template<>>();
    test_is_not_scalar<incomplete_variadic_template<void>>();
    test_is_not_scalar<incomplete_variadic_template<int>>();
    test_is_not_scalar<incomplete_variadic_template<class_type>>();
    test_is_not_scalar<incomplete_variadic_template<incomplete_type>>();
    test_is_not_scalar<incomplete_variadic_template<int, void, class_type, volatile char[]>>();
    test_is_scalar<int class_type::*>();
    test_is_scalar<float class_type::*>();
    test_is_scalar<void * class_type::*>();
    test_is_scalar<int * class_type::*>();
    test_is_not_scalar<int class_type::*&>();
    test_is_not_scalar<float class_type::*&>();
    test_is_not_scalar<void * class_type::*&>();
    test_is_not_scalar<int * class_type::*&>();
    test_is_not_scalar<int class_type::*&&>();
    test_is_not_scalar<float class_type::*&&>();
    test_is_not_scalar<void * class_type::*&&>();
    test_is_not_scalar<int * class_type::*&&>();
    test_is_scalar<int class_type::* const>();
    test_is_scalar<float class_type::* const>();
    test_is_scalar<void * class_type::* const>();
    test_is_not_scalar<int class_type::* const&>();
    test_is_not_scalar<float class_type::* const&>();
    test_is_not_scalar<void * class_type::* const&>();
    test_is_not_scalar<int class_type::* const&&>();
    test_is_not_scalar<float class_type::* const&&>();
    test_is_not_scalar<void * class_type::* const&&>();
    test_is_scalar<int class_type::* volatile>();
    test_is_scalar<float class_type::* volatile>();
    test_is_scalar<void * class_type::* volatile>();
    test_is_not_scalar<int class_type::* volatile&>();
    test_is_not_scalar<float class_type::* volatile&>();
    test_is_not_scalar<void * class_type::* volatile&>();
    test_is_not_scalar<int class_type::* volatile&&>();
    test_is_not_scalar<float class_type::* volatile&&>();
    test_is_not_scalar<void * class_type::* volatile&&>();
    test_is_scalar<int class_type::* const volatile>();
    test_is_scalar<float class_type::* const volatile>();
    test_is_scalar<void * class_type::* const volatile>();
    test_is_not_scalar<int class_type::* const volatile&>();
    test_is_not_scalar<float class_type::* const volatile&>();
    test_is_not_scalar<void * class_type::* const volatile&>();
    test_is_not_scalar<int class_type::* const volatile&&>();
    test_is_not_scalar<float class_type::* const volatile&&>();
    test_is_not_scalar<void * class_type::* const volatile&&>();
    test_is_not_scalar<non_copyable>();
    test_is_not_scalar<non_moveable>();
    test_is_not_scalar<non_constructible>();
    test_is_not_scalar<tracked>();
    test_is_not_scalar<trap_constructible>();
    test_is_not_scalar<trap_implicit_conversion>();
    test_is_not_scalar<trap_comma>();
    test_is_not_scalar<trap_call>();
    test_is_not_scalar<trap_self_assign>();
    test_is_not_scalar<trap_deref>();
    test_is_not_scalar<trap_array_subscript>();

    test_is_not_scalar<void()>();
    test_is_not_scalar<void()&>();
    test_is_not_scalar<void() &&>();
    test_is_not_scalar<void() const>();
    test_is_not_scalar<void() const&>();
    test_is_not_scalar<void() const&&>();
    test_is_not_scalar<void() volatile>();
    test_is_not_scalar<void() volatile&>();
    test_is_not_scalar<void() volatile&&>();
    test_is_not_scalar<void() const volatile>();
    test_is_not_scalar<void() const volatile&>();
    test_is_not_scalar<void() const volatile&&>();
    test_is_not_scalar<void() noexcept>();
    test_is_not_scalar<void() & noexcept>();
    test_is_not_scalar<void() && noexcept>();
    test_is_not_scalar<void() const noexcept>();
    test_is_not_scalar<void() const & noexcept>();
    test_is_not_scalar<void() const && noexcept>();
    test_is_not_scalar<void() volatile noexcept>();
    test_is_not_scalar<void() volatile & noexcept>();
    test_is_not_scalar<void() volatile && noexcept>();
    test_is_not_scalar<void() const volatile noexcept>();
    test_is_not_scalar<void() const volatile & noexcept>();
    test_is_not_scalar<void() const volatile && noexcept>();

    test_is_not_scalar<void(int)>();
    test_is_not_scalar<void(int)&>();
    test_is_not_scalar<void(int) &&>();
    test_is_not_scalar<void(int) const>();
    test_is_not_scalar<void(int) const&>();
    test_is_not_scalar<void(int) const&&>();
    test_is_not_scalar<void(int) volatile>();
    test_is_not_scalar<void(int) volatile&>();
    test_is_not_scalar<void(int) volatile&&>();
    test_is_not_scalar<void(int) const volatile>();
    test_is_not_scalar<void(int) const volatile&>();
    test_is_not_scalar<void(int) const volatile&&>();
    test_is_not_scalar<void(int) noexcept>();
    test_is_not_scalar<void(int) & noexcept>();
    test_is_not_scalar<void(int) && noexcept>();
    test_is_not_scalar<void(int) const noexcept>();
    test_is_not_scalar<void(int) const & noexcept>();
    test_is_not_scalar<void(int) const && noexcept>();
    test_is_not_scalar<void(int) volatile noexcept>();
    test_is_not_scalar<void(int) volatile & noexcept>();
    test_is_not_scalar<void(int) volatile && noexcept>();
    test_is_not_scalar<void(int) const volatile noexcept>();
    test_is_not_scalar<void(int) const volatile & noexcept>();
    test_is_not_scalar<void(int) const volatile && noexcept>();

    test_is_not_scalar<void(...)>();
    test_is_not_scalar<void(...)&>();
    test_is_not_scalar<void(...) &&>();
    test_is_not_scalar<void(...) const>();
    test_is_not_scalar<void(...) const&>();
    test_is_not_scalar<void(...) const&&>();
    test_is_not_scalar<void(...) volatile>();
    test_is_not_scalar<void(...) volatile&>();
    test_is_not_scalar<void(...) volatile&&>();
    test_is_not_scalar<void(...) const volatile>();
    test_is_not_scalar<void(...) const volatile&>();
    test_is_not_scalar<void(...) const volatile&&>();
    test_is_not_scalar<void(...) noexcept>();
    test_is_not_scalar<void(...) & noexcept>();
    test_is_not_scalar<void(...) && noexcept>();
    test_is_not_scalar<void(...) const noexcept>();
    test_is_not_scalar<void(...) const & noexcept>();
    test_is_not_scalar<void(...) const && noexcept>();
    test_is_not_scalar<void(...) volatile noexcept>();
    test_is_not_scalar<void(...) volatile & noexcept>();
    test_is_not_scalar<void(...) volatile && noexcept>();
    test_is_not_scalar<void(...) const volatile noexcept>();
    test_is_not_scalar<void(...) const volatile & noexcept>();
    test_is_not_scalar<void(...) const volatile && noexcept>();

    test_is_not_scalar<void(int, ...)>();
    test_is_not_scalar<void(int, ...)&>();
    test_is_not_scalar<void(int, ...) &&>();
    test_is_not_scalar<void(int, ...) const>();
    test_is_not_scalar<void(int, ...) const&>();
    test_is_not_scalar<void(int, ...) const&&>();
    test_is_not_scalar<void(int, ...) volatile>();
    test_is_not_scalar<void(int, ...) volatile&>();
    test_is_not_scalar<void(int, ...) volatile&&>();
    test_is_not_scalar<void(int, ...) const volatile>();
    test_is_not_scalar<void(int, ...) const volatile&>();
    test_is_not_scalar<void(int, ...) const volatile&&>();
    test_is_not_scalar<void(int, ...) noexcept>();
    test_is_not_scalar<void(int, ...) & noexcept>();
    test_is_not_scalar<void(int, ...) && noexcept>();
    test_is_not_scalar<void(int, ...) const noexcept>();
    test_is_not_scalar<void(int, ...) const & noexcept>();
    test_is_not_scalar<void(int, ...) const && noexcept>();
    test_is_not_scalar<void(int, ...) volatile noexcept>();
    test_is_not_scalar<void(int, ...) volatile & noexcept>();
    test_is_not_scalar<void(int, ...) volatile && noexcept>();
    test_is_not_scalar<void(int, ...) const volatile noexcept>();
    test_is_not_scalar<void(int, ...) const volatile & noexcept>();
    test_is_not_scalar<void(int, ...) const volatile && noexcept>();

    test_is_not_scalar<int()>();
    test_is_not_scalar<int()&>();
    test_is_not_scalar<int() &&>();
    test_is_not_scalar<int() const>();
    test_is_not_scalar<int() const&>();
    test_is_not_scalar<int() const&&>();
    test_is_not_scalar<int() volatile>();
    test_is_not_scalar<int() volatile&>();
    test_is_not_scalar<int() volatile&&>();
    test_is_not_scalar<int() const volatile>();
    test_is_not_scalar<int() const volatile&>();
    test_is_not_scalar<int() const volatile&&>();
    test_is_not_scalar<int() noexcept>();
    test_is_not_scalar<int() & noexcept>();
    test_is_not_scalar<int() && noexcept>();
    test_is_not_scalar<int() const noexcept>();
    test_is_not_scalar<int() const & noexcept>();
    test_is_not_scalar<int() const && noexcept>();
    test_is_not_scalar<int() volatile noexcept>();
    test_is_not_scalar<int() volatile & noexcept>();
    test_is_not_scalar<int() volatile && noexcept>();
    test_is_not_scalar<int() const volatile noexcept>();
    test_is_not_scalar<int() const volatile & noexcept>();
    test_is_not_scalar<int() const volatile && noexcept>();

    test_is_not_scalar<int(int)>();
    test_is_not_scalar<int(int)&>();
    test_is_not_scalar<int(int) &&>();
    test_is_not_scalar<int(int) const>();
    test_is_not_scalar<int(int) const&>();
    test_is_not_scalar<int(int) const&&>();
    test_is_not_scalar<int(int) volatile>();
    test_is_not_scalar<int(int) volatile&>();
    test_is_not_scalar<int(int) volatile&&>();
    test_is_not_scalar<int(int) const volatile>();
    test_is_not_scalar<int(int) const volatile&>();
    test_is_not_scalar<int(int) const volatile&&>();
    test_is_not_scalar<int(int) noexcept>();
    test_is_not_scalar<int(int) & noexcept>();
    test_is_not_scalar<int(int) && noexcept>();
    test_is_not_scalar<int(int) const noexcept>();
    test_is_not_scalar<int(int) const & noexcept>();
    test_is_not_scalar<int(int) const && noexcept>();
    test_is_not_scalar<int(int) volatile noexcept>();
    test_is_not_scalar<int(int) volatile & noexcept>();
    test_is_not_scalar<int(int) volatile && noexcept>();
    test_is_not_scalar<int(int) const volatile noexcept>();
    test_is_not_scalar<int(int) const volatile & noexcept>();
    test_is_not_scalar<int(int) const volatile && noexcept>();

    test_is_not_scalar<int(...)>();
    test_is_not_scalar<int(...)&>();
    test_is_not_scalar<int(...) &&>();
    test_is_not_scalar<int(...) const>();
    test_is_not_scalar<int(...) const&>();
    test_is_not_scalar<int(...) const&&>();
    test_is_not_scalar<int(...) volatile>();
    test_is_not_scalar<int(...) volatile&>();
    test_is_not_scalar<int(...) volatile&&>();
    test_is_not_scalar<int(...) const volatile>();
    test_is_not_scalar<int(...) const volatile&>();
    test_is_not_scalar<int(...) const volatile&&>();
    test_is_not_scalar<int(...) noexcept>();
    test_is_not_scalar<int(...) & noexcept>();
    test_is_not_scalar<int(...) && noexcept>();
    test_is_not_scalar<int(...) const noexcept>();
    test_is_not_scalar<int(...) const & noexcept>();
    test_is_not_scalar<int(...) const && noexcept>();
    test_is_not_scalar<int(...) volatile noexcept>();
    test_is_not_scalar<int(...) volatile & noexcept>();
    test_is_not_scalar<int(...) volatile && noexcept>();
    test_is_not_scalar<int(...) const volatile noexcept>();
    test_is_not_scalar<int(...) const volatile & noexcept>();
    test_is_not_scalar<int(...) const volatile && noexcept>();

    test_is_not_scalar<int(int, ...)>();
    test_is_not_scalar<int(int, ...)&>();
    test_is_not_scalar<int(int, ...) &&>();
    test_is_not_scalar<int(int, ...) const>();
    test_is_not_scalar<int(int, ...) const&>();
    test_is_not_scalar<int(int, ...) const&&>();
    test_is_not_scalar<int(int, ...) volatile>();
    test_is_not_scalar<int(int, ...) volatile&>();
    test_is_not_scalar<int(int, ...) volatile&&>();
    test_is_not_scalar<int(int, ...) const volatile>();
    test_is_not_scalar<int(int, ...) const volatile&>();
    test_is_not_scalar<int(int, ...) const volatile&&>();
    test_is_not_scalar<int(int, ...) noexcept>();
    test_is_not_scalar<int(int, ...) & noexcept>();
    test_is_not_scalar<int(int, ...) && noexcept>();
    test_is_not_scalar<int(int, ...) const noexcept>();
    test_is_not_scalar<int(int, ...) const & noexcept>();
    test_is_not_scalar<int(int, ...) const && noexcept>();
    test_is_not_scalar<int(int, ...) volatile noexcept>();
    test_is_not_scalar<int(int, ...) volatile & noexcept>();
    test_is_not_scalar<int(int, ...) volatile && noexcept>();
    test_is_not_scalar<int(int, ...) const volatile noexcept>();
    test_is_not_scalar<int(int, ...) const volatile & noexcept>();
    test_is_not_scalar<int(int, ...) const volatile && noexcept>();

    test_is_scalar<void (*)()>();
    test_is_scalar<void (*)() noexcept>();

    test_is_scalar<void (*)(int)>();
    test_is_scalar<void (*)(int) noexcept>();

    test_is_scalar<void (*)(...)>();
    test_is_scalar<void (*)(...) noexcept>();

    test_is_scalar<void (*)(int, ...)>();
    test_is_scalar<void (*)(int, ...) noexcept>();

    test_is_scalar<int (*)()>();
    test_is_scalar<int (*)() noexcept>();

    test_is_scalar<int (*)(int)>();
    test_is_scalar<int (*)(int) noexcept>();

    test_is_scalar<int (*)(...)>();
    test_is_scalar<int (*)(...) noexcept>();

    test_is_scalar<int (*)(int, ...)>();
    test_is_scalar<int (*)(int, ...) noexcept>();

    test_is_not_scalar<void (&)()>();
    test_is_not_scalar<void (&)() noexcept>();

    test_is_not_scalar<void (&)(int)>();
    test_is_not_scalar<void (&)(int) noexcept>();

    test_is_not_scalar<void (&)(...)>();
    test_is_not_scalar<void (&)(...) noexcept>();

    test_is_not_scalar<void (&)(int, ...)>();
    test_is_not_scalar<void (&)(int, ...) noexcept>();

    test_is_not_scalar<int (&)()>();
    test_is_not_scalar<int (&)() noexcept>();

    test_is_not_scalar<int (&)(int)>();
    test_is_not_scalar<int (&)(int) noexcept>();

    test_is_not_scalar<int (&)(...)>();
    test_is_not_scalar<int (&)(...) noexcept>();

    test_is_not_scalar<int (&)(int, ...)>();
    test_is_not_scalar<int (&)(int, ...) noexcept>();

    test_is_not_scalar<void (&&)()>();
    test_is_not_scalar<void (&&)() noexcept>();

    test_is_not_scalar<void (&&)(int)>();
    test_is_not_scalar<void (&&)(int) noexcept>();

    test_is_not_scalar<void (&&)(...)>();
    test_is_not_scalar<void (&&)(...) noexcept>();

    test_is_not_scalar<void (&&)(int, ...)>();
    test_is_not_scalar<void (&&)(int, ...) noexcept>();

    test_is_not_scalar<int (&&)()>();
    test_is_not_scalar<int (&&)() noexcept>();

    test_is_not_scalar<int (&&)(int)>();
    test_is_not_scalar<int (&&)(int) noexcept>();

    test_is_not_scalar<int (&&)(...)>();
    test_is_not_scalar<int (&&)(...) noexcept>();

    test_is_not_scalar<int (&&)(int, ...)>();
    test_is_not_scalar<int (&&)(int, ...) noexcept>();

    test_is_scalar<void (class_type::*)()>();
    test_is_scalar<void (class_type::*)()&>();
    test_is_scalar<void (class_type::*)() &&>();
    test_is_scalar<void (class_type::*)() const>();
    test_is_scalar<void (class_type::*)() const&>();
    test_is_scalar<void (class_type::*)() const&&>();
    test_is_scalar<void (class_type::*)() noexcept>();
    test_is_scalar<void (class_type::*)() & noexcept>();
    test_is_scalar<void (class_type::*)() && noexcept>();
    test_is_scalar<void (class_type::*)() const noexcept>();
    test_is_scalar<void (class_type::*)() const & noexcept>();
    test_is_scalar<void (class_type::*)() const && noexcept>();

    test_is_scalar<void (class_type::*)(int)>();
    test_is_scalar<void (class_type::*)(int)&>();
    test_is_scalar<void (class_type::*)(int) &&>();
    test_is_scalar<void (class_type::*)(int) const>();
    test_is_scalar<void (class_type::*)(int) const&>();
    test_is_scalar<void (class_type::*)(int) const&&>();
    test_is_scalar<void (class_type::*)(int) noexcept>();
    test_is_scalar<void (class_type::*)(int) & noexcept>();
    test_is_scalar<void (class_type::*)(int) && noexcept>();
    test_is_scalar<void (class_type::*)(int) const noexcept>();
    test_is_scalar<void (class_type::*)(int) const & noexcept>();
    test_is_scalar<void (class_type::*)(int) const && noexcept>();

    test_is_scalar<void (class_type::*)(...)>();
    test_is_scalar<void (class_type::*)(...)&>();
    test_is_scalar<void (class_type::*)(...) &&>();
    test_is_scalar<void (class_type::*)(...) const>();
    test_is_scalar<void (class_type::*)(...) const&>();
    test_is_scalar<void (class_type::*)(...) const&&>();
    test_is_scalar<void (class_type::*)(...) noexcept>();
    test_is_scalar<void (class_type::*)(...) & noexcept>();
    test_is_scalar<void (class_type::*)(...) && noexcept>();
    test_is_scalar<void (class_type::*)(...) const noexcept>();
    test_is_scalar<void (class_type::*)(...) const & noexcept>();
    test_is_scalar<void (class_type::*)(...) const && noexcept>();

    test_is_scalar<void (class_type::*)(int, ...)>();
    test_is_scalar<void (class_type::*)(int, ...)&>();
    test_is_scalar<void (class_type::*)(int, ...) &&>();
    test_is_scalar<void (class_type::*)(int, ...) const>();
    test_is_scalar<void (class_type::*)(int, ...) const&>();
    test_is_scalar<void (class_type::*)(int, ...) const&&>();
    test_is_scalar<void (class_type::*)(int, ...) noexcept>();
    test_is_scalar<void (class_type::*)(int, ...) & noexcept>();
    test_is_scalar<void (class_type::*)(int, ...) && noexcept>();
    test_is_scalar<void (class_type::*)(int, ...) const noexcept>();
    test_is_scalar<void (class_type::*)(int, ...) const & noexcept>();
    test_is_scalar<void (class_type::*)(int, ...) const && noexcept>();

    test_is_scalar<int (class_type::*)()>();
    test_is_scalar<int (class_type::*)()&>();
    test_is_scalar<int (class_type::*)() &&>();
    test_is_scalar<int (class_type::*)() const>();
    test_is_scalar<int (class_type::*)() const&>();
    test_is_scalar<int (class_type::*)() const&&>();
    test_is_scalar<int (class_type::*)() noexcept>();
    test_is_scalar<int (class_type::*)() & noexcept>();
    test_is_scalar<int (class_type::*)() && noexcept>();
    test_is_scalar<int (class_type::*)() const noexcept>();
    test_is_scalar<int (class_type::*)() const & noexcept>();
    test_is_scalar<int (class_type::*)() const && noexcept>();

    test_is_scalar<int (class_type::*)(int)>();
    test_is_scalar<int (class_type::*)(int)&>();
    test_is_scalar<int (class_type::*)(int) &&>();
    test_is_scalar<int (class_type::*)(int) const>();
    test_is_scalar<int (class_type::*)(int) const&>();
    test_is_scalar<int (class_type::*)(int) const&&>();
    test_is_scalar<int (class_type::*)(int) noexcept>();
    test_is_scalar<int (class_type::*)(int) & noexcept>();
    test_is_scalar<int (class_type::*)(int) && noexcept>();
    test_is_scalar<int (class_type::*)(int) const noexcept>();
    test_is_scalar<int (class_type::*)(int) const & noexcept>();
    test_is_scalar<int (class_type::*)(int) const && noexcept>();

    test_is_scalar<int (class_type::*)(...)>();
    test_is_scalar<int (class_type::*)(...)&>();
    test_is_scalar<int (class_type::*)(...) &&>();
    test_is_scalar<int (class_type::*)(...) const>();
    test_is_scalar<int (class_type::*)(...) const&>();
    test_is_scalar<int (class_type::*)(...) const&&>();
    test_is_scalar<int (class_type::*)(...) noexcept>();
    test_is_scalar<int (class_type::*)(...) & noexcept>();
    test_is_scalar<int (class_type::*)(...) && noexcept>();
    test_is_scalar<int (class_type::*)(...) const noexcept>();
    test_is_scalar<int (class_type::*)(...) const & noexcept>();
    test_is_scalar<int (class_type::*)(...) const && noexcept>();

    test_is_scalar<int (class_type::*)(int, ...)>();
    test_is_scalar<int (class_type::*)(int, ...)&>();
    test_is_scalar<int (class_type::*)(int, ...) &&>();
    test_is_scalar<int (class_type::*)(int, ...) const>();
    test_is_scalar<int (class_type::*)(int, ...) const&>();
    test_is_scalar<int (class_type::*)(int, ...) const&&>();
    test_is_scalar<int (class_type::*)(int, ...) noexcept>();
    test_is_scalar<int (class_type::*)(int, ...) & noexcept>();
    test_is_scalar<int (class_type::*)(int, ...) && noexcept>();
    test_is_scalar<int (class_type::*)(int, ...) const noexcept>();
    test_is_scalar<int (class_type::*)(int, ...) const & noexcept>();
    test_is_scalar<int (class_type::*)(int, ...) const && noexcept>();
}
