#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/compiler_support/cpp_standard.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_final.hpp>
#include <type_traits>
#include <vector>

struct A
{};

struct B final : public A
{};

struct C : public A
{};

struct P final
{};

union U1
{};

union U2 final
{};

template <typename TypeT>
void test_is_final_impl()
{
#if PHI_HAS_WORKING_IS_FINAL()
    STATIC_REQUIRE(phi::is_final<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_final<TypeT>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_final_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_not_final_v<TypeT>);
#    endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_final<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_final<TypeT>);

    // Standard compatibility
#    if PHI_CPP_STANDARD_IS_ATLEAST(17)
    STATIC_REQUIRE(std::is_final<TypeT>::value);
#    endif
#endif
}

template <typename TypeT>
void test_is_final()
{
    test_is_final_impl<TypeT>();
    test_is_final_impl<const TypeT>();
    test_is_final_impl<volatile TypeT>();
    test_is_final_impl<const volatile TypeT>();
}

template <typename TypeT>
void test_is_not_final_impl()
{
#if PHI_HAS_WORKING_IS_FINAL()
    STATIC_REQUIRE_FALSE(phi::is_final<TypeT>::value);
    STATIC_REQUIRE(phi::is_not_final<TypeT>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_final_v<TypeT>);
    STATIC_REQUIRE(phi::is_not_final_v<TypeT>);
#    endif

    // Standard compatibility
#    if PHI_CPP_STANDARD_IS_ATLEAST(17)
    STATIC_REQUIRE_FALSE(std::is_final<TypeT>::value);
#    endif
#endif
}

template <typename TypeT>
void test_is_not_final()
{
    test_is_not_final_impl<TypeT>();
    test_is_not_final_impl<const TypeT>();
    test_is_not_final_impl<volatile TypeT>();
    test_is_not_final_impl<const volatile TypeT>();
}

TEST_CASE("is_final")
{
    test_is_final<B>();
    test_is_final<P>();
    test_is_final<U2>();
    test_is_not_final<A>();
    test_is_not_final<C>();
    test_is_not_final<P*>();
    test_is_not_final<U1>();
    test_is_not_final<U1*>();
    test_is_not_final<U2*>();

    test_is_not_final<void>();
    test_is_not_final<phi::nullptr_t>();
    test_is_not_final<bool>();
    test_is_not_final<char>();
    test_is_not_final<signed char>();
    test_is_not_final<unsigned char>();
    test_is_not_final<short>();
    test_is_not_final<unsigned short>();
    test_is_not_final<int>();
    test_is_not_final<unsigned int>();
    test_is_not_final<long>();
    test_is_not_final<unsigned long>();
    test_is_not_final<long long>();
    test_is_not_final<unsigned long long>();
    test_is_not_final<float>();
    test_is_not_final<double>();
    test_is_not_final<long double>();
    test_is_not_final<char8_t>();
    test_is_not_final<char16_t>();
    test_is_not_final<char32_t>();
    test_is_not_final<wchar_t>();

    test_is_not_final<phi::boolean>();
    test_is_not_final<phi::integer<signed char>>();
    test_is_not_final<phi::integer<unsigned char>>();
    test_is_not_final<phi::integer<short>>();
    test_is_not_final<phi::integer<unsigned short>>();
    test_is_not_final<phi::integer<int>>();
    test_is_not_final<phi::integer<unsigned int>>();
    test_is_not_final<phi::integer<long>>();
    test_is_not_final<phi::integer<unsigned long>>();
    test_is_not_final<phi::integer<long long>>();
    test_is_not_final<phi::integer<unsigned long long>>();
    test_is_not_final<phi::floating_point<float>>();
    test_is_not_final<phi::floating_point<double>>();
    test_is_not_final<phi::floating_point<long double>>();

    test_is_not_final<std::vector<int>>();
    test_is_not_final<phi::scope_ptr<int>>();

    test_is_not_final<int&>();
    test_is_not_final<const int&>();
    test_is_not_final<volatile int&>();
    test_is_not_final<const volatile int&>();
    test_is_not_final<int&&>();
    test_is_not_final<const int&&>();
    test_is_not_final<volatile int&&>();
    test_is_not_final<const volatile int&&>();
    test_is_not_final<int*>();
    test_is_not_final<const int*>();
    test_is_not_final<volatile int*>();
    test_is_not_final<const volatile int*>();
    test_is_not_final<int**>();
    test_is_not_final<const int**>();
    test_is_not_final<volatile int**>();
    test_is_not_final<const volatile int**>();
    test_is_not_final<int*&>();
    test_is_not_final<const int*&>();
    test_is_not_final<volatile int*&>();
    test_is_not_final<const volatile int*&>();
    test_is_not_final<int*&&>();
    test_is_not_final<const int*&&>();
    test_is_not_final<volatile int*&&>();
    test_is_not_final<const volatile int*&&>();
    test_is_not_final<void*>();
    test_is_not_final<char[3]>();
    test_is_not_final<char[]>();
    test_is_not_final<char* [3]>();
    test_is_not_final<char*[]>();
    test_is_not_final<int(*)[3]>();
    test_is_not_final<int(*)[]>();
    test_is_not_final<int(&)[3]>();
    test_is_not_final<int(&)[]>();
    test_is_not_final<int(&&)[3]>();
    test_is_not_final<int(&&)[]>();
    test_is_not_final<char[3][2]>();
    test_is_not_final<char[][2]>();
    test_is_not_final<char* [3][2]>();
    test_is_not_final<char*[][2]>();
    test_is_not_final<int(*)[3][2]>();
    test_is_not_final<int(*)[][2]>();
    test_is_not_final<int(&)[3][2]>();
    test_is_not_final<int(&)[][2]>();
    test_is_not_final<int(&&)[3][2]>();
    test_is_not_final<int(&&)[][2]>();
    test_is_not_final<class_type>();
    test_is_not_final<class_type[]>();
    test_is_not_final<class_type[2]>();
    test_is_not_final<template_type<void>>();
    test_is_not_final<template_type<int>>();
    test_is_not_final<template_type<class_type>>();
    test_is_not_final<template_type<incomplete_type>>();
    test_is_not_final<variadic_template<>>();
    test_is_not_final<variadic_template<void>>();
    test_is_not_final<variadic_template<int>>();
    test_is_not_final<variadic_template<class_type>>();
    test_is_not_final<variadic_template<incomplete_type>>();
    test_is_not_final<variadic_template<int, void, class_type, volatile char[]>>();
    test_is_not_final<public_derived_from<base>>();
    test_is_not_final<public_derived_from<derived>>();
    test_is_not_final<public_derived_from<class_type>>();
    test_is_not_final<private_derived_from<base>>();
    test_is_not_final<private_derived_from<derived>>();
    test_is_not_final<private_derived_from<class_type>>();
    test_is_not_final<protected_derived_from<base>>();
    test_is_not_final<protected_derived_from<derived>>();
    test_is_not_final<protected_derived_from<class_type>>();
    test_is_not_final<union_type>();
    test_is_not_final<non_empty_union>();
    test_is_not_final<empty>();
    test_is_not_final<not_empty>();
    test_is_not_final<bit_zero>();
    test_is_not_final<bit_one>();
    test_is_not_final<base>();
    test_is_not_final<derived>();
    test_is_not_final<abstract>();
    test_is_not_final<public_abstract>();
    test_is_not_final<private_abstract>();
    test_is_not_final<protected_abstract>();
    test_is_not_final<abstract_template<int>>();
    test_is_not_final<abstract_template<double>>();
    test_is_not_final<abstract_template<class_type>>();
    test_is_not_final<abstract_template<incomplete_type>>();
    test_is_final<final_type>();
    test_is_not_final<public_destructor>();
    test_is_not_final<protected_destructor>();
    test_is_not_final<private_destructor>();
    test_is_not_final<virtual_public_destructor>();
    test_is_not_final<virtual_protected_destructor>();
    test_is_not_final<virtual_private_destructor>();
    test_is_not_final<pure_public_destructor>();
    test_is_not_final<pure_protected_destructor>();
    test_is_not_final<pure_private_destructor>();
    test_is_not_final<deleted_public_destructor>();
    test_is_not_final<deleted_protected_destructor>();
    test_is_not_final<deleted_private_destructor>();
    test_is_not_final<deleted_virtual_public_destructor>();
    test_is_not_final<deleted_virtual_protected_destructor>();
    test_is_not_final<deleted_virtual_private_destructor>();
    test_is_not_final<Enum>();
    test_is_not_final<EnumSigned>();
    test_is_not_final<EnumUnsigned>();
    test_is_not_final<EnumClass>();
    test_is_not_final<EnumStruct>();
    test_is_not_final<function_type>();
    test_is_not_final<function_ptr>();
    test_is_not_final<member_object_ptr>();
    test_is_not_final<member_function_ptr>();
    test_is_not_final<int class_type::*>();
    test_is_not_final<float class_type::*>();
    test_is_not_final<void * class_type::*>();
    test_is_not_final<int * class_type::*>();
    test_is_not_final<int class_type::*&>();
    test_is_not_final<float class_type::*&>();
    test_is_not_final<void * class_type::*&>();
    test_is_not_final<int * class_type::*&>();
    test_is_not_final<int class_type::*&&>();
    test_is_not_final<float class_type::*&&>();
    test_is_not_final<void * class_type::*&&>();
    test_is_not_final<int * class_type::*&&>();
    test_is_not_final<int class_type::* const>();
    test_is_not_final<float class_type::* const>();
    test_is_not_final<void * class_type::* const>();
    test_is_not_final<int class_type::* const&>();
    test_is_not_final<float class_type::* const&>();
    test_is_not_final<void * class_type::* const&>();
    test_is_not_final<int class_type::* const&&>();
    test_is_not_final<float class_type::* const&&>();
    test_is_not_final<void * class_type::* const&&>();
    test_is_not_final<int class_type::* volatile>();
    test_is_not_final<float class_type::* volatile>();
    test_is_not_final<void * class_type::* volatile>();
    test_is_not_final<int class_type::* volatile&>();
    test_is_not_final<float class_type::* volatile&>();
    test_is_not_final<void * class_type::* volatile&>();
    test_is_not_final<int class_type::* volatile&&>();
    test_is_not_final<float class_type::* volatile&&>();
    test_is_not_final<void * class_type::* volatile&&>();
    test_is_not_final<int class_type::* const volatile>();
    test_is_not_final<float class_type::* const volatile>();
    test_is_not_final<void * class_type::* const volatile>();
    test_is_not_final<int class_type::* const volatile&>();
    test_is_not_final<float class_type::* const volatile&>();
    test_is_not_final<void * class_type::* const volatile&>();
    test_is_not_final<int class_type::* const volatile&&>();
    test_is_not_final<float class_type::* const volatile&&>();
    test_is_not_final<void * class_type::* const volatile&&>();
    test_is_not_final<non_copyable>();
    test_is_not_final<non_moveable>();
    test_is_not_final<non_constructible>();
    test_is_not_final<tracked>();
    test_is_not_final<trap_constructible>();
    test_is_not_final<trap_implicit_conversion>();
    test_is_not_final<trap_comma>();
    test_is_not_final<trap_call>();
    test_is_not_final<trap_self_assign>();
    test_is_not_final<trap_deref>();
    test_is_not_final<trap_array_subscript>();

    test_is_not_final<void()>();
    test_is_not_final<void()&>();
    test_is_not_final<void() &&>();
    test_is_not_final<void() const>();
    test_is_not_final<void() const&>();
    test_is_not_final<void() const&&>();
    test_is_not_final<void() volatile>();
    test_is_not_final<void() volatile&>();
    test_is_not_final<void() volatile&&>();
    test_is_not_final<void() const volatile>();
    test_is_not_final<void() const volatile&>();
    test_is_not_final<void() const volatile&&>();
    test_is_not_final<void() noexcept>();
    test_is_not_final<void() & noexcept>();
    test_is_not_final<void() && noexcept>();
    test_is_not_final<void() const noexcept>();
    test_is_not_final<void() const & noexcept>();
    test_is_not_final<void() const && noexcept>();
    test_is_not_final<void() volatile noexcept>();
    test_is_not_final<void() volatile & noexcept>();
    test_is_not_final<void() volatile && noexcept>();
    test_is_not_final<void() const volatile noexcept>();
    test_is_not_final<void() const volatile & noexcept>();
    test_is_not_final<void() const volatile && noexcept>();

    test_is_not_final<void(int)>();
    test_is_not_final<void(int)&>();
    test_is_not_final<void(int) &&>();
    test_is_not_final<void(int) const>();
    test_is_not_final<void(int) const&>();
    test_is_not_final<void(int) const&&>();
    test_is_not_final<void(int) volatile>();
    test_is_not_final<void(int) volatile&>();
    test_is_not_final<void(int) volatile&&>();
    test_is_not_final<void(int) const volatile>();
    test_is_not_final<void(int) const volatile&>();
    test_is_not_final<void(int) const volatile&&>();
    test_is_not_final<void(int) noexcept>();
    test_is_not_final<void(int) & noexcept>();
    test_is_not_final<void(int) && noexcept>();
    test_is_not_final<void(int) const noexcept>();
    test_is_not_final<void(int) const & noexcept>();
    test_is_not_final<void(int) const && noexcept>();
    test_is_not_final<void(int) volatile noexcept>();
    test_is_not_final<void(int) volatile & noexcept>();
    test_is_not_final<void(int) volatile && noexcept>();
    test_is_not_final<void(int) const volatile noexcept>();
    test_is_not_final<void(int) const volatile & noexcept>();
    test_is_not_final<void(int) const volatile && noexcept>();

    test_is_not_final<void(...)>();
    test_is_not_final<void(...)&>();
    test_is_not_final<void(...) &&>();
    test_is_not_final<void(...) const>();
    test_is_not_final<void(...) const&>();
    test_is_not_final<void(...) const&&>();
    test_is_not_final<void(...) volatile>();
    test_is_not_final<void(...) volatile&>();
    test_is_not_final<void(...) volatile&&>();
    test_is_not_final<void(...) const volatile>();
    test_is_not_final<void(...) const volatile&>();
    test_is_not_final<void(...) const volatile&&>();
    test_is_not_final<void(...) noexcept>();
    test_is_not_final<void(...) & noexcept>();
    test_is_not_final<void(...) && noexcept>();
    test_is_not_final<void(...) const noexcept>();
    test_is_not_final<void(...) const & noexcept>();
    test_is_not_final<void(...) const && noexcept>();
    test_is_not_final<void(...) volatile noexcept>();
    test_is_not_final<void(...) volatile & noexcept>();
    test_is_not_final<void(...) volatile && noexcept>();
    test_is_not_final<void(...) const volatile noexcept>();
    test_is_not_final<void(...) const volatile & noexcept>();
    test_is_not_final<void(...) const volatile && noexcept>();

    test_is_not_final<void(int, ...)>();
    test_is_not_final<void(int, ...)&>();
    test_is_not_final<void(int, ...) &&>();
    test_is_not_final<void(int, ...) const>();
    test_is_not_final<void(int, ...) const&>();
    test_is_not_final<void(int, ...) const&&>();
    test_is_not_final<void(int, ...) volatile>();
    test_is_not_final<void(int, ...) volatile&>();
    test_is_not_final<void(int, ...) volatile&&>();
    test_is_not_final<void(int, ...) const volatile>();
    test_is_not_final<void(int, ...) const volatile&>();
    test_is_not_final<void(int, ...) const volatile&&>();
    test_is_not_final<void(int, ...) noexcept>();
    test_is_not_final<void(int, ...) & noexcept>();
    test_is_not_final<void(int, ...) && noexcept>();
    test_is_not_final<void(int, ...) const noexcept>();
    test_is_not_final<void(int, ...) const & noexcept>();
    test_is_not_final<void(int, ...) const && noexcept>();
    test_is_not_final<void(int, ...) volatile noexcept>();
    test_is_not_final<void(int, ...) volatile & noexcept>();
    test_is_not_final<void(int, ...) volatile && noexcept>();
    test_is_not_final<void(int, ...) const volatile noexcept>();
    test_is_not_final<void(int, ...) const volatile & noexcept>();
    test_is_not_final<void(int, ...) const volatile && noexcept>();

    test_is_not_final<int()>();
    test_is_not_final<int()&>();
    test_is_not_final<int() &&>();
    test_is_not_final<int() const>();
    test_is_not_final<int() const&>();
    test_is_not_final<int() const&&>();
    test_is_not_final<int() volatile>();
    test_is_not_final<int() volatile&>();
    test_is_not_final<int() volatile&&>();
    test_is_not_final<int() const volatile>();
    test_is_not_final<int() const volatile&>();
    test_is_not_final<int() const volatile&&>();
    test_is_not_final<int() noexcept>();
    test_is_not_final<int() & noexcept>();
    test_is_not_final<int() && noexcept>();
    test_is_not_final<int() const noexcept>();
    test_is_not_final<int() const & noexcept>();
    test_is_not_final<int() const && noexcept>();
    test_is_not_final<int() volatile noexcept>();
    test_is_not_final<int() volatile & noexcept>();
    test_is_not_final<int() volatile && noexcept>();
    test_is_not_final<int() const volatile noexcept>();
    test_is_not_final<int() const volatile & noexcept>();
    test_is_not_final<int() const volatile && noexcept>();

    test_is_not_final<int(int)>();
    test_is_not_final<int(int)&>();
    test_is_not_final<int(int) &&>();
    test_is_not_final<int(int) const>();
    test_is_not_final<int(int) const&>();
    test_is_not_final<int(int) const&&>();
    test_is_not_final<int(int) volatile>();
    test_is_not_final<int(int) volatile&>();
    test_is_not_final<int(int) volatile&&>();
    test_is_not_final<int(int) const volatile>();
    test_is_not_final<int(int) const volatile&>();
    test_is_not_final<int(int) const volatile&&>();
    test_is_not_final<int(int) noexcept>();
    test_is_not_final<int(int) & noexcept>();
    test_is_not_final<int(int) && noexcept>();
    test_is_not_final<int(int) const noexcept>();
    test_is_not_final<int(int) const & noexcept>();
    test_is_not_final<int(int) const && noexcept>();
    test_is_not_final<int(int) volatile noexcept>();
    test_is_not_final<int(int) volatile & noexcept>();
    test_is_not_final<int(int) volatile && noexcept>();
    test_is_not_final<int(int) const volatile noexcept>();
    test_is_not_final<int(int) const volatile & noexcept>();
    test_is_not_final<int(int) const volatile && noexcept>();

    test_is_not_final<int(...)>();
    test_is_not_final<int(...)&>();
    test_is_not_final<int(...) &&>();
    test_is_not_final<int(...) const>();
    test_is_not_final<int(...) const&>();
    test_is_not_final<int(...) const&&>();
    test_is_not_final<int(...) volatile>();
    test_is_not_final<int(...) volatile&>();
    test_is_not_final<int(...) volatile&&>();
    test_is_not_final<int(...) const volatile>();
    test_is_not_final<int(...) const volatile&>();
    test_is_not_final<int(...) const volatile&&>();
    test_is_not_final<int(...) noexcept>();
    test_is_not_final<int(...) & noexcept>();
    test_is_not_final<int(...) && noexcept>();
    test_is_not_final<int(...) const noexcept>();
    test_is_not_final<int(...) const & noexcept>();
    test_is_not_final<int(...) const && noexcept>();
    test_is_not_final<int(...) volatile noexcept>();
    test_is_not_final<int(...) volatile & noexcept>();
    test_is_not_final<int(...) volatile && noexcept>();
    test_is_not_final<int(...) const volatile noexcept>();
    test_is_not_final<int(...) const volatile & noexcept>();
    test_is_not_final<int(...) const volatile && noexcept>();

    test_is_not_final<int(int, ...)>();
    test_is_not_final<int(int, ...)&>();
    test_is_not_final<int(int, ...) &&>();
    test_is_not_final<int(int, ...) const>();
    test_is_not_final<int(int, ...) const&>();
    test_is_not_final<int(int, ...) const&&>();
    test_is_not_final<int(int, ...) volatile>();
    test_is_not_final<int(int, ...) volatile&>();
    test_is_not_final<int(int, ...) volatile&&>();
    test_is_not_final<int(int, ...) const volatile>();
    test_is_not_final<int(int, ...) const volatile&>();
    test_is_not_final<int(int, ...) const volatile&&>();
    test_is_not_final<int(int, ...) noexcept>();
    test_is_not_final<int(int, ...) & noexcept>();
    test_is_not_final<int(int, ...) && noexcept>();
    test_is_not_final<int(int, ...) const noexcept>();
    test_is_not_final<int(int, ...) const & noexcept>();
    test_is_not_final<int(int, ...) const && noexcept>();
    test_is_not_final<int(int, ...) volatile noexcept>();
    test_is_not_final<int(int, ...) volatile & noexcept>();
    test_is_not_final<int(int, ...) volatile && noexcept>();
    test_is_not_final<int(int, ...) const volatile noexcept>();
    test_is_not_final<int(int, ...) const volatile & noexcept>();
    test_is_not_final<int(int, ...) const volatile && noexcept>();

    test_is_not_final<void (*)()>();
    test_is_not_final<void (*)() noexcept>();

    test_is_not_final<void (*)(int)>();
    test_is_not_final<void (*)(int) noexcept>();

    test_is_not_final<void (*)(...)>();
    test_is_not_final<void (*)(...) noexcept>();

    test_is_not_final<void (*)(int, ...)>();
    test_is_not_final<void (*)(int, ...) noexcept>();

    test_is_not_final<int (*)()>();
    test_is_not_final<int (*)() noexcept>();

    test_is_not_final<int (*)(int)>();
    test_is_not_final<int (*)(int) noexcept>();

    test_is_not_final<int (*)(...)>();
    test_is_not_final<int (*)(...) noexcept>();

    test_is_not_final<int (*)(int, ...)>();
    test_is_not_final<int (*)(int, ...) noexcept>();

    test_is_not_final<void (&)()>();
    test_is_not_final<void (&)() noexcept>();

    test_is_not_final<void (&)(int)>();
    test_is_not_final<void (&)(int) noexcept>();

    test_is_not_final<void (&)(...)>();
    test_is_not_final<void (&)(...) noexcept>();

    test_is_not_final<void (&)(int, ...)>();
    test_is_not_final<void (&)(int, ...) noexcept>();

    test_is_not_final<int (&)()>();
    test_is_not_final<int (&)() noexcept>();

    test_is_not_final<int (&)(int)>();
    test_is_not_final<int (&)(int) noexcept>();

    test_is_not_final<int (&)(...)>();
    test_is_not_final<int (&)(...) noexcept>();

    test_is_not_final<int (&)(int, ...)>();
    test_is_not_final<int (&)(int, ...) noexcept>();

    test_is_not_final<void (&&)()>();
    test_is_not_final<void (&&)() noexcept>();

    test_is_not_final<void (&&)(int)>();
    test_is_not_final<void (&&)(int) noexcept>();

    test_is_not_final<void (&&)(...)>();
    test_is_not_final<void (&&)(...) noexcept>();

    test_is_not_final<void (&&)(int, ...)>();
    test_is_not_final<void (&&)(int, ...) noexcept>();

    test_is_not_final<int (&&)()>();
    test_is_not_final<int (&&)() noexcept>();

    test_is_not_final<int (&&)(int)>();
    test_is_not_final<int (&&)(int) noexcept>();

    test_is_not_final<int (&&)(...)>();
    test_is_not_final<int (&&)(...) noexcept>();

    test_is_not_final<int (&&)(int, ...)>();
    test_is_not_final<int (&&)(int, ...) noexcept>();

    test_is_not_final<void (class_type::*)()>();
    test_is_not_final<void (class_type::*)()&>();
    test_is_not_final<void (class_type::*)() &&>();
    test_is_not_final<void (class_type::*)() const>();
    test_is_not_final<void (class_type::*)() const&>();
    test_is_not_final<void (class_type::*)() const&&>();
    test_is_not_final<void (class_type::*)() noexcept>();
    test_is_not_final<void (class_type::*)() & noexcept>();
    test_is_not_final<void (class_type::*)() && noexcept>();
    test_is_not_final<void (class_type::*)() const noexcept>();
    test_is_not_final<void (class_type::*)() const & noexcept>();
    test_is_not_final<void (class_type::*)() const && noexcept>();

    test_is_not_final<void (class_type::*)(int)>();
    test_is_not_final<void (class_type::*)(int)&>();
    test_is_not_final<void (class_type::*)(int) &&>();
    test_is_not_final<void (class_type::*)(int) const>();
    test_is_not_final<void (class_type::*)(int) const&>();
    test_is_not_final<void (class_type::*)(int) const&&>();
    test_is_not_final<void (class_type::*)(int) noexcept>();
    test_is_not_final<void (class_type::*)(int) & noexcept>();
    test_is_not_final<void (class_type::*)(int) && noexcept>();
    test_is_not_final<void (class_type::*)(int) const noexcept>();
    test_is_not_final<void (class_type::*)(int) const & noexcept>();
    test_is_not_final<void (class_type::*)(int) const && noexcept>();

    test_is_not_final<void (class_type::*)(...)>();
    test_is_not_final<void (class_type::*)(...)&>();
    test_is_not_final<void (class_type::*)(...) &&>();
    test_is_not_final<void (class_type::*)(...) const>();
    test_is_not_final<void (class_type::*)(...) const&>();
    test_is_not_final<void (class_type::*)(...) const&&>();
    test_is_not_final<void (class_type::*)(...) noexcept>();
    test_is_not_final<void (class_type::*)(...) & noexcept>();
    test_is_not_final<void (class_type::*)(...) && noexcept>();
    test_is_not_final<void (class_type::*)(...) const noexcept>();
    test_is_not_final<void (class_type::*)(...) const & noexcept>();
    test_is_not_final<void (class_type::*)(...) const && noexcept>();

    test_is_not_final<void (class_type::*)(int, ...)>();
    test_is_not_final<void (class_type::*)(int, ...)&>();
    test_is_not_final<void (class_type::*)(int, ...) &&>();
    test_is_not_final<void (class_type::*)(int, ...) const>();
    test_is_not_final<void (class_type::*)(int, ...) const&>();
    test_is_not_final<void (class_type::*)(int, ...) const&&>();
    test_is_not_final<void (class_type::*)(int, ...) noexcept>();
    test_is_not_final<void (class_type::*)(int, ...) & noexcept>();
    test_is_not_final<void (class_type::*)(int, ...) && noexcept>();
    test_is_not_final<void (class_type::*)(int, ...) const noexcept>();
    test_is_not_final<void (class_type::*)(int, ...) const & noexcept>();
    test_is_not_final<void (class_type::*)(int, ...) const && noexcept>();

    test_is_not_final<int (class_type::*)()>();
    test_is_not_final<int (class_type::*)()&>();
    test_is_not_final<int (class_type::*)() &&>();
    test_is_not_final<int (class_type::*)() const>();
    test_is_not_final<int (class_type::*)() const&>();
    test_is_not_final<int (class_type::*)() const&&>();
    test_is_not_final<int (class_type::*)() noexcept>();
    test_is_not_final<int (class_type::*)() & noexcept>();
    test_is_not_final<int (class_type::*)() && noexcept>();
    test_is_not_final<int (class_type::*)() const noexcept>();
    test_is_not_final<int (class_type::*)() const & noexcept>();
    test_is_not_final<int (class_type::*)() const && noexcept>();

    test_is_not_final<int (class_type::*)(int)>();
    test_is_not_final<int (class_type::*)(int)&>();
    test_is_not_final<int (class_type::*)(int) &&>();
    test_is_not_final<int (class_type::*)(int) const>();
    test_is_not_final<int (class_type::*)(int) const&>();
    test_is_not_final<int (class_type::*)(int) const&&>();
    test_is_not_final<int (class_type::*)(int) noexcept>();
    test_is_not_final<int (class_type::*)(int) & noexcept>();
    test_is_not_final<int (class_type::*)(int) && noexcept>();
    test_is_not_final<int (class_type::*)(int) const noexcept>();
    test_is_not_final<int (class_type::*)(int) const & noexcept>();
    test_is_not_final<int (class_type::*)(int) const && noexcept>();

    test_is_not_final<int (class_type::*)(...)>();
    test_is_not_final<int (class_type::*)(...)&>();
    test_is_not_final<int (class_type::*)(...) &&>();
    test_is_not_final<int (class_type::*)(...) const>();
    test_is_not_final<int (class_type::*)(...) const&>();
    test_is_not_final<int (class_type::*)(...) const&&>();
    test_is_not_final<int (class_type::*)(...) noexcept>();
    test_is_not_final<int (class_type::*)(...) & noexcept>();
    test_is_not_final<int (class_type::*)(...) && noexcept>();
    test_is_not_final<int (class_type::*)(...) const noexcept>();
    test_is_not_final<int (class_type::*)(...) const & noexcept>();
    test_is_not_final<int (class_type::*)(...) const && noexcept>();

    test_is_not_final<int (class_type::*)(int, ...)>();
    test_is_not_final<int (class_type::*)(int, ...)&>();
    test_is_not_final<int (class_type::*)(int, ...) &&>();
    test_is_not_final<int (class_type::*)(int, ...) const>();
    test_is_not_final<int (class_type::*)(int, ...) const&>();
    test_is_not_final<int (class_type::*)(int, ...) const&&>();
    test_is_not_final<int (class_type::*)(int, ...) noexcept>();
    test_is_not_final<int (class_type::*)(int, ...) & noexcept>();
    test_is_not_final<int (class_type::*)(int, ...) && noexcept>();
    test_is_not_final<int (class_type::*)(int, ...) const noexcept>();
    test_is_not_final<int (class_type::*)(int, ...) const & noexcept>();
    test_is_not_final<int (class_type::*)(int, ...) const && noexcept>();
}
