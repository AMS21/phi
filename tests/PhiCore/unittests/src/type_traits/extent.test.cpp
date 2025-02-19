#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/extent.hpp>
#include <type_traits>
#include <vector>

template <typename TypeT, unsigned A = 0>
void test_extent()
{
    STATIC_REQUIRE(phi::extent<TypeT>::value == A);
    STATIC_REQUIRE(phi::extent<const TypeT>::value == A);
    STATIC_REQUIRE(phi::extent<volatile TypeT>::value == A);
    STATIC_REQUIRE(phi::extent<const volatile TypeT>::value == A);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::extent_v<TypeT> == A);
    STATIC_REQUIRE(phi::extent_v<const TypeT> == A);
    STATIC_REQUIRE(phi::extent_v<volatile TypeT> == A);
    STATIC_REQUIRE(phi::extent_v<const volatile TypeT> == A);
#endif

    // Standard compatbility
    STATIC_REQUIRE(phi::extent<TypeT>::value == std::extent<TypeT>::value);
}

template <typename TypeT, unsigned Val, unsigned A>
void test_extent_var()
{
    STATIC_REQUIRE(phi::extent<TypeT, Val>::value == A);
    STATIC_REQUIRE(phi::extent<const TypeT, Val>::value == A);
    STATIC_REQUIRE(phi::extent<volatile TypeT, Val>::value == A);
    STATIC_REQUIRE(phi::extent<const volatile TypeT, Val>::value == A);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::extent_v<TypeT, Val> == A);
    STATIC_REQUIRE(phi::extent_v<const TypeT, Val> == A);
    STATIC_REQUIRE(phi::extent_v<volatile TypeT, Val> == A);
    STATIC_REQUIRE(phi::extent_v<const volatile TypeT, Val> == A);
#endif

    // Standard compatbility
    STATIC_REQUIRE(phi::extent<TypeT, Val>::value == std::extent<TypeT, Val>::value);
}

TEST_CASE("extent")
{
    test_extent<int[1], 1>();
    test_extent<int[2], 2>();
    test_extent<int[3], 3>();
    test_extent<int[1][4], 1>();
    test_extent<int[2][4], 2>();
    test_extent<int[3][4], 3>();
    test_extent<int[1][4][9], 1>();
    test_extent<int[2][4][9], 2>();
    test_extent<int[3][4][9], 3>();

    test_extent<int[], 0>();
    test_extent<int[][4], 0>();
    test_extent<int[][4][9], 0>();

    // Extent 1
    test_extent_var<int, 1, 0>();
    test_extent_var<int[], 1, 0>();
    test_extent_var<int[1], 1, 0>();
    test_extent_var<int[2], 1, 0>();
    test_extent_var<int[3], 1, 0>();
    test_extent_var<int[1][4], 1, 4>();
    test_extent_var<int[2][4], 1, 4>();
    test_extent_var<int[3][4], 1, 4>();
    test_extent_var<int[2][3], 1, 3>();
    test_extent_var<int[][4], 1, 4>();
    test_extent_var<int[1][4][5], 1, 4>();
    test_extent_var<int[2][4][5], 1, 4>();
    test_extent_var<int[3][4][5], 1, 4>();
    test_extent_var<int[2][3][5], 1, 3>();
    test_extent_var<int[][4][5], 1, 4>();

    // Extent 2
    test_extent_var<int, 2, 0>();
    test_extent_var<int[], 2, 0>();
    test_extent_var<int[1], 2, 0>();
    test_extent_var<int[2], 2, 0>();
    test_extent_var<int[3], 2, 0>();
    test_extent_var<int[1][4], 2, 0>();
    test_extent_var<int[2][4], 2, 0>();
    test_extent_var<int[3][4], 2, 0>();
    test_extent_var<int[2][3], 2, 0>();
    test_extent_var<int[][4], 2, 0>();
    test_extent_var<int[1][1][3], 2, 3>();
    test_extent_var<int[1][1][4], 2, 4>();
    test_extent_var<int[][1][3], 2, 3>();
    test_extent_var<int[][1][3][4], 2, 3>();
    test_extent_var<int[][1][3][5], 2, 3>();

    // Extent 3
    test_extent_var<int, 3, 0>();
    test_extent_var<int[], 3, 0>();
    test_extent_var<int[1], 3, 0>();
    test_extent_var<int[2], 3, 0>();
    test_extent_var<int[3], 3, 0>();
    test_extent_var<int[1][4], 3, 0>();
    test_extent_var<int[2][4], 3, 0>();
    test_extent_var<int[3][4], 3, 0>();
    test_extent_var<int[2][3], 3, 0>();
    test_extent_var<int[][4], 3, 0>();
    test_extent_var<int[1][1][3], 3, 0>();
    test_extent_var<int[1][1][4], 3, 0>();
    test_extent_var<int[][1][3], 3, 0>();
    test_extent_var<int[][1][3][4], 3, 4>();
    test_extent_var<int[][1][3][5], 3, 5>();

    test_extent<void>();
    test_extent<phi::nullptr_t>();
    test_extent<bool>();
    test_extent<char>();
    test_extent<signed char>();
    test_extent<unsigned char>();
    test_extent<short>();
    test_extent<unsigned short>();
    test_extent<int>();
    test_extent<unsigned int>();
    test_extent<long>();
    test_extent<unsigned long>();
    test_extent<long long>();
    test_extent<unsigned long long>();
    test_extent<float>();
    test_extent<double>();
    test_extent<long double>();
    test_extent<char8_t>();
    test_extent<char16_t>();
    test_extent<char32_t>();
    test_extent<wchar_t>();

    test_extent<phi::boolean>();
    test_extent<phi::integer<signed char>>();
    test_extent<phi::integer<unsigned char>>();
    test_extent<phi::integer<short>>();
    test_extent<phi::integer<unsigned short>>();
    test_extent<phi::integer<int>>();
    test_extent<phi::integer<unsigned int>>();
    test_extent<phi::integer<long>>();
    test_extent<phi::integer<unsigned long>>();
    test_extent<phi::integer<long long>>();
    test_extent<phi::integer<unsigned long long>>();
    test_extent<phi::floating_point<float>>();
    test_extent<phi::floating_point<double>>();
    test_extent<phi::floating_point<long double>>();

    test_extent<std::vector<int>>();
    test_extent<phi::scope_ptr<int>>();

    test_extent<int&>();
    test_extent<const int&>();
    test_extent<volatile int&>();
    test_extent<const volatile int&>();
    test_extent<int&&>();
    test_extent<const int&&>();
    test_extent<volatile int&&>();
    test_extent<const volatile int&&>();
    test_extent<int*>();
    test_extent<const int*>();
    test_extent<volatile int*>();
    test_extent<const volatile int*>();
    test_extent<int**>();
    test_extent<const int**>();
    test_extent<volatile int**>();
    test_extent<const volatile int**>();
    test_extent<int*&>();
    test_extent<const int*&>();
    test_extent<volatile int*&>();
    test_extent<const volatile int*&>();
    test_extent<int*&&>();
    test_extent<const int*&&>();
    test_extent<volatile int*&&>();
    test_extent<const volatile int*&&>();
    test_extent<void*>();
    test_extent<char[3], 3>();
    test_extent<char[], 0>();
    test_extent<char[3], 3>();
    test_extent<char[], 0>();
    test_extent<char* [3], 3>();
    test_extent<char*[]>();
    test_extent<int(*)[3]>();
    test_extent<int(*)[]>();
    test_extent<int(&)[3]>();
    test_extent<int(&)[]>();
    test_extent<int(&&)[3]>();
    test_extent<int(&&)[]>();
    test_extent<char[3][2], 3>();
    test_extent<char[][2], 0>();
    test_extent<char* [3][2], 3>();
    test_extent<char*[][2], 0>();
    test_extent<int(*)[3][2]>();
    test_extent<int(*)[][2]>();
    test_extent<int(&)[3][2]>();
    test_extent<int(&)[][2]>();
    test_extent<int(&&)[3][2]>();
    test_extent<int(&&)[][2]>();
    test_extent<class_type>();
    test_extent<class_type[], 0>();
    test_extent<class_type[2], 2>();
    test_extent<template_type<void>>();
    test_extent<template_type<int>>();
    test_extent<template_type<class_type>>();
    test_extent<template_type<incomplete_type>>();
    test_extent<variadic_template<>>();
    test_extent<variadic_template<void>>();
    test_extent<variadic_template<int>>();
    test_extent<variadic_template<class_type>>();
    test_extent<variadic_template<incomplete_type>>();
    test_extent<variadic_template<int, void, class_type, volatile char[]>>();
    test_extent<public_derived_from<base>>();
    test_extent<public_derived_from<derived>>();
    test_extent<public_derived_from<class_type>>();
    test_extent<private_derived_from<base>>();
    test_extent<private_derived_from<derived>>();
    test_extent<private_derived_from<class_type>>();
    test_extent<protected_derived_from<base>>();
    test_extent<protected_derived_from<derived>>();
    test_extent<protected_derived_from<class_type>>();
    test_extent<union_type>();
    test_extent<non_empty_union>();
    test_extent<empty>();
    test_extent<not_empty>();
    test_extent<bit_zero>();
    test_extent<bit_one>();
    test_extent<base>();
    test_extent<derived>();
    test_extent<abstract>();
    test_extent<public_abstract>();
    test_extent<private_abstract>();
    test_extent<protected_abstract>();
    test_extent<abstract_template<int>>();
    test_extent<abstract_template<double>>();
    test_extent<abstract_template<class_type>>();
    test_extent<abstract_template<incomplete_type>>();
    test_extent<final_type>();
    test_extent<public_destructor>();
    test_extent<protected_destructor>();
    test_extent<private_destructor>();
    test_extent<virtual_public_destructor>();
    test_extent<virtual_protected_destructor>();
    test_extent<virtual_private_destructor>();
    test_extent<pure_public_destructor>();
    test_extent<pure_protected_destructor>();
    test_extent<pure_private_destructor>();
    test_extent<deleted_public_destructor>();
    test_extent<deleted_protected_destructor>();
    test_extent<deleted_private_destructor>();
    test_extent<deleted_virtual_public_destructor>();
    test_extent<deleted_virtual_protected_destructor>();
    test_extent<deleted_virtual_private_destructor>();
    test_extent<Enum>();
    test_extent<EnumSigned>();
    test_extent<EnumUnsigned>();
    test_extent<EnumClass>();
    test_extent<EnumStruct>();
    test_extent<function_type>();
    test_extent<function_ptr>();
    test_extent<member_object_ptr>();
    test_extent<member_function_ptr>();
    test_extent<incomplete_type>();
    test_extent<incomplete_template<void>>();
    test_extent<incomplete_template<int>>();
    test_extent<incomplete_template<class_type>>();
    test_extent<incomplete_template<incomplete_type>>();
    test_extent<incomplete_variadic_template<>>();
    test_extent<incomplete_variadic_template<void>>();
    test_extent<incomplete_variadic_template<int>>();
    test_extent<incomplete_variadic_template<class_type>>();
    test_extent<incomplete_variadic_template<incomplete_type>>();
    test_extent<incomplete_variadic_template<int, void, class_type, volatile char[]>>();
    test_extent<int class_type::*>();
    test_extent<float class_type::*>();
    test_extent<void * class_type::*>();
    test_extent<int * class_type::*>();
    test_extent<int class_type::*&>();
    test_extent<float class_type::*&>();
    test_extent<void * class_type::*&>();
    test_extent<int * class_type::*&>();
    test_extent<int class_type::*&&>();
    test_extent<float class_type::*&&>();
    test_extent<void * class_type::*&&>();
    test_extent<int * class_type::*&&>();
    test_extent<int class_type::* const>();
    test_extent<float class_type::* const>();
    test_extent<void * class_type::* const>();
    test_extent<int class_type::* const&>();
    test_extent<float class_type::* const&>();
    test_extent<void * class_type::* const&>();
    test_extent<int class_type::* const&&>();
    test_extent<float class_type::* const&&>();
    test_extent<void * class_type::* const&&>();
    test_extent<int class_type::* volatile>();
    test_extent<float class_type::* volatile>();
    test_extent<void * class_type::* volatile>();
    test_extent<int class_type::* volatile&>();
    test_extent<float class_type::* volatile&>();
    test_extent<void * class_type::* volatile&>();
    test_extent<int class_type::* volatile&&>();
    test_extent<float class_type::* volatile&&>();
    test_extent<void * class_type::* volatile&&>();
    test_extent<int class_type::* const volatile>();
    test_extent<float class_type::* const volatile>();
    test_extent<void * class_type::* const volatile>();
    test_extent<int class_type::* const volatile&>();
    test_extent<float class_type::* const volatile&>();
    test_extent<void * class_type::* const volatile&>();
    test_extent<int class_type::* const volatile&&>();
    test_extent<float class_type::* const volatile&&>();
    test_extent<void * class_type::* const volatile&&>();
    test_extent<non_copyable>();
    test_extent<non_moveable>();
    test_extent<non_constructible>();
    test_extent<tracked>();
    test_extent<trap_constructible>();
    test_extent<trap_implicit_conversion>();
    test_extent<trap_comma>();
    test_extent<trap_call>();
    test_extent<trap_self_assign>();
    test_extent<trap_deref>();
    test_extent<trap_array_subscript>();

    test_extent<void()>();
    test_extent<void()&>();
    test_extent<void() &&>();
    test_extent<void() const>();
    test_extent<void() const&>();
    test_extent<void() const&&>();
    test_extent<void() volatile>();
    test_extent<void() volatile&>();
    test_extent<void() volatile&&>();
    test_extent<void() const volatile>();
    test_extent<void() const volatile&>();
    test_extent<void() const volatile&&>();
    test_extent<void() noexcept>();
    test_extent<void() & noexcept>();
    test_extent<void() && noexcept>();
    test_extent<void() const noexcept>();
    test_extent<void() const & noexcept>();
    test_extent<void() const && noexcept>();
    test_extent<void() volatile noexcept>();
    test_extent<void() volatile & noexcept>();
    test_extent<void() volatile && noexcept>();
    test_extent<void() const volatile noexcept>();
    test_extent<void() const volatile & noexcept>();
    test_extent<void() const volatile && noexcept>();

    test_extent<void(int)>();
    test_extent<void(int)&>();
    test_extent<void(int) &&>();
    test_extent<void(int) const>();
    test_extent<void(int) const&>();
    test_extent<void(int) const&&>();
    test_extent<void(int) volatile>();
    test_extent<void(int) volatile&>();
    test_extent<void(int) volatile&&>();
    test_extent<void(int) const volatile>();
    test_extent<void(int) const volatile&>();
    test_extent<void(int) const volatile&&>();
    test_extent<void(int) noexcept>();
    test_extent<void(int) & noexcept>();
    test_extent<void(int) && noexcept>();
    test_extent<void(int) const noexcept>();
    test_extent<void(int) const & noexcept>();
    test_extent<void(int) const && noexcept>();
    test_extent<void(int) volatile noexcept>();
    test_extent<void(int) volatile & noexcept>();
    test_extent<void(int) volatile && noexcept>();
    test_extent<void(int) const volatile noexcept>();
    test_extent<void(int) const volatile & noexcept>();
    test_extent<void(int) const volatile && noexcept>();

    test_extent<void(...)>();
    test_extent<void(...)&>();
    test_extent<void(...) &&>();
    test_extent<void(...) const>();
    test_extent<void(...) const&>();
    test_extent<void(...) const&&>();
    test_extent<void(...) volatile>();
    test_extent<void(...) volatile&>();
    test_extent<void(...) volatile&&>();
    test_extent<void(...) const volatile>();
    test_extent<void(...) const volatile&>();
    test_extent<void(...) const volatile&&>();
    test_extent<void(...) noexcept>();
    test_extent<void(...) & noexcept>();
    test_extent<void(...) && noexcept>();
    test_extent<void(...) const noexcept>();
    test_extent<void(...) const & noexcept>();
    test_extent<void(...) const && noexcept>();
    test_extent<void(...) volatile noexcept>();
    test_extent<void(...) volatile & noexcept>();
    test_extent<void(...) volatile && noexcept>();
    test_extent<void(...) const volatile noexcept>();
    test_extent<void(...) const volatile & noexcept>();
    test_extent<void(...) const volatile && noexcept>();

    test_extent<void(int, ...)>();
    test_extent<void(int, ...)&>();
    test_extent<void(int, ...) &&>();
    test_extent<void(int, ...) const>();
    test_extent<void(int, ...) const&>();
    test_extent<void(int, ...) const&&>();
    test_extent<void(int, ...) volatile>();
    test_extent<void(int, ...) volatile&>();
    test_extent<void(int, ...) volatile&&>();
    test_extent<void(int, ...) const volatile>();
    test_extent<void(int, ...) const volatile&>();
    test_extent<void(int, ...) const volatile&&>();
    test_extent<void(int, ...) noexcept>();
    test_extent<void(int, ...) & noexcept>();
    test_extent<void(int, ...) && noexcept>();
    test_extent<void(int, ...) const noexcept>();
    test_extent<void(int, ...) const & noexcept>();
    test_extent<void(int, ...) const && noexcept>();
    test_extent<void(int, ...) volatile noexcept>();
    test_extent<void(int, ...) volatile & noexcept>();
    test_extent<void(int, ...) volatile && noexcept>();
    test_extent<void(int, ...) const volatile noexcept>();
    test_extent<void(int, ...) const volatile & noexcept>();
    test_extent<void(int, ...) const volatile && noexcept>();

    test_extent<int()>();
    test_extent<int()&>();
    test_extent<int() &&>();
    test_extent<int() const>();
    test_extent<int() const&>();
    test_extent<int() const&&>();
    test_extent<int() volatile>();
    test_extent<int() volatile&>();
    test_extent<int() volatile&&>();
    test_extent<int() const volatile>();
    test_extent<int() const volatile&>();
    test_extent<int() const volatile&&>();
    test_extent<int() noexcept>();
    test_extent<int() & noexcept>();
    test_extent<int() && noexcept>();
    test_extent<int() const noexcept>();
    test_extent<int() const & noexcept>();
    test_extent<int() const && noexcept>();
    test_extent<int() volatile noexcept>();
    test_extent<int() volatile & noexcept>();
    test_extent<int() volatile && noexcept>();
    test_extent<int() const volatile noexcept>();
    test_extent<int() const volatile & noexcept>();
    test_extent<int() const volatile && noexcept>();

    test_extent<int(int)>();
    test_extent<int(int)&>();
    test_extent<int(int) &&>();
    test_extent<int(int) const>();
    test_extent<int(int) const&>();
    test_extent<int(int) const&&>();
    test_extent<int(int) volatile>();
    test_extent<int(int) volatile&>();
    test_extent<int(int) volatile&&>();
    test_extent<int(int) const volatile>();
    test_extent<int(int) const volatile&>();
    test_extent<int(int) const volatile&&>();
    test_extent<int(int) noexcept>();
    test_extent<int(int) & noexcept>();
    test_extent<int(int) && noexcept>();
    test_extent<int(int) const noexcept>();
    test_extent<int(int) const & noexcept>();
    test_extent<int(int) const && noexcept>();
    test_extent<int(int) volatile noexcept>();
    test_extent<int(int) volatile & noexcept>();
    test_extent<int(int) volatile && noexcept>();
    test_extent<int(int) const volatile noexcept>();
    test_extent<int(int) const volatile & noexcept>();
    test_extent<int(int) const volatile && noexcept>();

    test_extent<int(...)>();
    test_extent<int(...)&>();
    test_extent<int(...) &&>();
    test_extent<int(...) const>();
    test_extent<int(...) const&>();
    test_extent<int(...) const&&>();
    test_extent<int(...) volatile>();
    test_extent<int(...) volatile&>();
    test_extent<int(...) volatile&&>();
    test_extent<int(...) const volatile>();
    test_extent<int(...) const volatile&>();
    test_extent<int(...) const volatile&&>();
    test_extent<int(...) noexcept>();
    test_extent<int(...) & noexcept>();
    test_extent<int(...) && noexcept>();
    test_extent<int(...) const noexcept>();
    test_extent<int(...) const & noexcept>();
    test_extent<int(...) const && noexcept>();
    test_extent<int(...) volatile noexcept>();
    test_extent<int(...) volatile & noexcept>();
    test_extent<int(...) volatile && noexcept>();
    test_extent<int(...) const volatile noexcept>();
    test_extent<int(...) const volatile & noexcept>();
    test_extent<int(...) const volatile && noexcept>();

    test_extent<int(int, ...)>();
    test_extent<int(int, ...)&>();
    test_extent<int(int, ...) &&>();
    test_extent<int(int, ...) const>();
    test_extent<int(int, ...) const&>();
    test_extent<int(int, ...) const&&>();
    test_extent<int(int, ...) volatile>();
    test_extent<int(int, ...) volatile&>();
    test_extent<int(int, ...) volatile&&>();
    test_extent<int(int, ...) const volatile>();
    test_extent<int(int, ...) const volatile&>();
    test_extent<int(int, ...) const volatile&&>();
    test_extent<int(int, ...) noexcept>();
    test_extent<int(int, ...) & noexcept>();
    test_extent<int(int, ...) && noexcept>();
    test_extent<int(int, ...) const noexcept>();
    test_extent<int(int, ...) const & noexcept>();
    test_extent<int(int, ...) const && noexcept>();
    test_extent<int(int, ...) volatile noexcept>();
    test_extent<int(int, ...) volatile & noexcept>();
    test_extent<int(int, ...) volatile && noexcept>();
    test_extent<int(int, ...) const volatile noexcept>();
    test_extent<int(int, ...) const volatile & noexcept>();
    test_extent<int(int, ...) const volatile && noexcept>();

    test_extent<void (*)()>();
    test_extent<void (*)() noexcept>();

    test_extent<void (*)(int)>();
    test_extent<void (*)(int) noexcept>();

    test_extent<void (*)(...)>();
    test_extent<void (*)(...) noexcept>();

    test_extent<void (*)(int, ...)>();
    test_extent<void (*)(int, ...) noexcept>();

    test_extent<int (*)()>();
    test_extent<int (*)() noexcept>();

    test_extent<int (*)(int)>();
    test_extent<int (*)(int) noexcept>();

    test_extent<int (*)(...)>();
    test_extent<int (*)(...) noexcept>();

    test_extent<int (*)(int, ...)>();
    test_extent<int (*)(int, ...) noexcept>();

    test_extent<void (&)()>();
    test_extent<void (&)() noexcept>();

    test_extent<void (&)(int)>();
    test_extent<void (&)(int) noexcept>();

    test_extent<void (&)(...)>();
    test_extent<void (&)(...) noexcept>();

    test_extent<void (&)(int, ...)>();
    test_extent<void (&)(int, ...) noexcept>();

    test_extent<int (&)()>();
    test_extent<int (&)() noexcept>();

    test_extent<int (&)(int)>();
    test_extent<int (&)(int) noexcept>();

    test_extent<int (&)(...)>();
    test_extent<int (&)(...) noexcept>();

    test_extent<int (&)(int, ...)>();
    test_extent<int (&)(int, ...) noexcept>();

    test_extent<void (&&)()>();
    test_extent<void (&&)() noexcept>();

    test_extent<void (&&)(int)>();
    test_extent<void (&&)(int) noexcept>();

    test_extent<void (&&)(...)>();
    test_extent<void (&&)(...) noexcept>();

    test_extent<void (&&)(int, ...)>();
    test_extent<void (&&)(int, ...) noexcept>();

    test_extent<int (&&)()>();
    test_extent<int (&&)() noexcept>();

    test_extent<int (&&)(int)>();
    test_extent<int (&&)(int) noexcept>();

    test_extent<int (&&)(...)>();
    test_extent<int (&&)(...) noexcept>();

    test_extent<int (&&)(int, ...)>();
    test_extent<int (&&)(int, ...) noexcept>();

    test_extent<void (class_type::*)()>();
    test_extent<void (class_type::*)()&>();
    test_extent<void (class_type::*)() &&>();
    test_extent<void (class_type::*)() const>();
    test_extent<void (class_type::*)() const&>();
    test_extent<void (class_type::*)() const&&>();
    test_extent<void (class_type::*)() noexcept>();
    test_extent<void (class_type::*)() & noexcept>();
    test_extent<void (class_type::*)() && noexcept>();
    test_extent<void (class_type::*)() const noexcept>();
    test_extent<void (class_type::*)() const & noexcept>();
    test_extent<void (class_type::*)() const && noexcept>();

    test_extent<void (class_type::*)(int)>();
    test_extent<void (class_type::*)(int)&>();
    test_extent<void (class_type::*)(int) &&>();
    test_extent<void (class_type::*)(int) const>();
    test_extent<void (class_type::*)(int) const&>();
    test_extent<void (class_type::*)(int) const&&>();
    test_extent<void (class_type::*)(int) noexcept>();
    test_extent<void (class_type::*)(int) & noexcept>();
    test_extent<void (class_type::*)(int) && noexcept>();
    test_extent<void (class_type::*)(int) const noexcept>();
    test_extent<void (class_type::*)(int) const & noexcept>();
    test_extent<void (class_type::*)(int) const && noexcept>();

    test_extent<void (class_type::*)(...)>();
    test_extent<void (class_type::*)(...)&>();
    test_extent<void (class_type::*)(...) &&>();
    test_extent<void (class_type::*)(...) const>();
    test_extent<void (class_type::*)(...) const&>();
    test_extent<void (class_type::*)(...) const&&>();
    test_extent<void (class_type::*)(...) noexcept>();
    test_extent<void (class_type::*)(...) & noexcept>();
    test_extent<void (class_type::*)(...) && noexcept>();
    test_extent<void (class_type::*)(...) const noexcept>();
    test_extent<void (class_type::*)(...) const & noexcept>();
    test_extent<void (class_type::*)(...) const && noexcept>();

    test_extent<void (class_type::*)(int, ...)>();
    test_extent<void (class_type::*)(int, ...)&>();
    test_extent<void (class_type::*)(int, ...) &&>();
    test_extent<void (class_type::*)(int, ...) const>();
    test_extent<void (class_type::*)(int, ...) const&>();
    test_extent<void (class_type::*)(int, ...) const&&>();
    test_extent<void (class_type::*)(int, ...) noexcept>();
    test_extent<void (class_type::*)(int, ...) & noexcept>();
    test_extent<void (class_type::*)(int, ...) && noexcept>();
    test_extent<void (class_type::*)(int, ...) const noexcept>();
    test_extent<void (class_type::*)(int, ...) const & noexcept>();
    test_extent<void (class_type::*)(int, ...) const && noexcept>();

    test_extent<int (class_type::*)()>();
    test_extent<int (class_type::*)()&>();
    test_extent<int (class_type::*)() &&>();
    test_extent<int (class_type::*)() const>();
    test_extent<int (class_type::*)() const&>();
    test_extent<int (class_type::*)() const&&>();
    test_extent<int (class_type::*)() noexcept>();
    test_extent<int (class_type::*)() & noexcept>();
    test_extent<int (class_type::*)() && noexcept>();
    test_extent<int (class_type::*)() const noexcept>();
    test_extent<int (class_type::*)() const & noexcept>();
    test_extent<int (class_type::*)() const && noexcept>();

    test_extent<int (class_type::*)(int)>();
    test_extent<int (class_type::*)(int)&>();
    test_extent<int (class_type::*)(int) &&>();
    test_extent<int (class_type::*)(int) const>();
    test_extent<int (class_type::*)(int) const&>();
    test_extent<int (class_type::*)(int) const&&>();
    test_extent<int (class_type::*)(int) noexcept>();
    test_extent<int (class_type::*)(int) & noexcept>();
    test_extent<int (class_type::*)(int) && noexcept>();
    test_extent<int (class_type::*)(int) const noexcept>();
    test_extent<int (class_type::*)(int) const & noexcept>();
    test_extent<int (class_type::*)(int) const && noexcept>();

    test_extent<int (class_type::*)(...)>();
    test_extent<int (class_type::*)(...)&>();
    test_extent<int (class_type::*)(...) &&>();
    test_extent<int (class_type::*)(...) const>();
    test_extent<int (class_type::*)(...) const&>();
    test_extent<int (class_type::*)(...) const&&>();
    test_extent<int (class_type::*)(...) noexcept>();
    test_extent<int (class_type::*)(...) & noexcept>();
    test_extent<int (class_type::*)(...) && noexcept>();
    test_extent<int (class_type::*)(...) const noexcept>();
    test_extent<int (class_type::*)(...) const & noexcept>();
    test_extent<int (class_type::*)(...) const && noexcept>();

    test_extent<int (class_type::*)(int, ...)>();
    test_extent<int (class_type::*)(int, ...)&>();
    test_extent<int (class_type::*)(int, ...) &&>();
    test_extent<int (class_type::*)(int, ...) const>();
    test_extent<int (class_type::*)(int, ...) const&>();
    test_extent<int (class_type::*)(int, ...) const&&>();
    test_extent<int (class_type::*)(int, ...) noexcept>();
    test_extent<int (class_type::*)(int, ...) & noexcept>();
    test_extent<int (class_type::*)(int, ...) && noexcept>();
    test_extent<int (class_type::*)(int, ...) const noexcept>();
    test_extent<int (class_type::*)(int, ...) const & noexcept>();
    test_extent<int (class_type::*)(int, ...) const && noexcept>();
}
