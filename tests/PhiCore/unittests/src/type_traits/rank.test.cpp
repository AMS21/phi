#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/rank.hpp>
#include <phi/type_traits/remove_all_extents.hpp>
#include <type_traits>
#include <vector>

template <typename TypeT, unsigned Expected>
void test_rank_impl()
{
    STATIC_REQUIRE(phi::rank<TypeT>::value == Expected);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::rank_v<TypeT> == Expected);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::rank<TypeT>);

    // Standard compatibility
    STATIC_REQUIRE(std::rank<TypeT>::value == Expected);
}

template <typename TypeT, unsigned Expected = 0>
void test_rank()
{
    test_rank_impl<TypeT, Expected>();
    test_rank_impl<const TypeT, Expected>();
    test_rank_impl<volatile TypeT, Expected>();
    test_rank_impl<const volatile TypeT, Expected>();

    test_rank_impl<phi::remove_all_extents_t<TypeT>, 0>();
    test_rank_impl<phi::remove_all_extents_t<const TypeT>, 0>();
    test_rank_impl<phi::remove_all_extents_t<volatile TypeT>, 0>();
    test_rank_impl<phi::remove_all_extents_t<const volatile TypeT>, 0>();
}

TEST_CASE("rank")
{
    test_rank<char[], 1>();
    test_rank<char[3], 1>();
    test_rank<char[1], 1>();
    test_rank<char[][3], 2>();
    test_rank<char[2][3], 2>();
    test_rank<char[][4][3], 3>();
    test_rank<char[2][4][3], 3>();
    test_rank<char[][2][4][3], 4>();
    test_rank<char[1][2][4][3], 4>();
    test_rank<char[][1][2][4][3], 5>();
    test_rank<char[5][1][2][4][3], 5>();
    test_rank<class_type[], 1>();
    test_rank<class_type[1], 1>();
    test_rank<class_type[][1], 2>();
    test_rank<class_type[2][1], 2>();
    test_rank<class_type[][2][1], 3>();
    test_rank<class_type[3][2][1], 3>();
    test_rank<class_type[][3][2][1], 4>();
    test_rank<class_type[4][3][2][1], 4>();
    test_rank<class_type[][4][3][2][1], 5>();
    test_rank<class_type[5][4][3][2][1], 5>();

    test_rank<void>();
    test_rank<phi::nullptr_t>();
    test_rank<bool>();
    test_rank<char>();
    test_rank<signed char>();
    test_rank<unsigned char>();
    test_rank<short>();
    test_rank<unsigned short>();
    test_rank<int>();
    test_rank<unsigned int>();
    test_rank<long>();
    test_rank<unsigned long>();
    test_rank<long long>();
    test_rank<unsigned long long>();
    test_rank<float>();
    test_rank<double>();
    test_rank<long double>();
    test_rank<char8_t>();
    test_rank<char16_t>();
    test_rank<char32_t>();
    test_rank<wchar_t>();

    test_rank<phi::boolean>();
    test_rank<phi::integer<signed char>>();
    test_rank<phi::integer<unsigned char>>();
    test_rank<phi::integer<short>>();
    test_rank<phi::integer<unsigned short>>();
    test_rank<phi::integer<int>>();
    test_rank<phi::integer<unsigned int>>();
    test_rank<phi::integer<long>>();
    test_rank<phi::integer<unsigned long>>();
    test_rank<phi::integer<long long>>();
    test_rank<phi::integer<unsigned long long>>();
    test_rank<phi::floating_point<float>>();
    test_rank<phi::floating_point<double>>();
    test_rank<phi::floating_point<long double>>();

    test_rank<std::vector<int>>();
    test_rank<phi::scope_ptr<int>>();

    test_rank<int&>();
    test_rank<const int&>();
    test_rank<volatile int&>();
    test_rank<const volatile int&>();
    test_rank<int&&>();
    test_rank<const int&&>();
    test_rank<volatile int&&>();
    test_rank<const volatile int&&>();
    test_rank<int*>();
    test_rank<const int*>();
    test_rank<volatile int*>();
    test_rank<const volatile int*>();
    test_rank<int**>();
    test_rank<const int**>();
    test_rank<volatile int**>();
    test_rank<const volatile int**>();
    test_rank<int*&>();
    test_rank<const int*&>();
    test_rank<volatile int*&>();
    test_rank<const volatile int*&>();
    test_rank<int*&&>();
    test_rank<const int*&&>();
    test_rank<volatile int*&&>();
    test_rank<const volatile int*&&>();
    test_rank<void*>();
    test_rank<char[3], 1>();
    test_rank<char[], 1>();
    test_rank<char* [3], 1>();
    test_rank<char*[], 1>();
    test_rank<int(*)[3]>();
    test_rank<int(*)[]>();
    test_rank<int(&)[3]>();
    test_rank<int(&)[]>();
    test_rank<int(&&)[3]>();
    test_rank<int(&&)[]>();
    test_rank<char[3][2], 2>();
    test_rank<char[][2], 2>();
    test_rank<char* [3][2], 2>();
    test_rank<char*[][2], 2>();
    test_rank<int(*)[3][2]>();
    test_rank<int(*)[][2]>();
    test_rank<int(&)[3][2]>();
    test_rank<int(&)[][2]>();
    test_rank<int(&&)[3][2]>();
    test_rank<int(&&)[][2]>();
    test_rank<class_type>();
    test_rank<class_type[], 1>();
    test_rank<class_type[2], 1>();
    test_rank<template_type<void>>();
    test_rank<template_type<int>>();
    test_rank<template_type<class_type>>();
    test_rank<template_type<incomplete_type>>();
    test_rank<variadic_template<>>();
    test_rank<variadic_template<void>>();
    test_rank<variadic_template<int>>();
    test_rank<variadic_template<class_type>>();
    test_rank<variadic_template<incomplete_type>>();
    test_rank<variadic_template<int, void, class_type, volatile char[]>>();
    test_rank<public_derived_from<base>>();
    test_rank<public_derived_from<derived>>();
    test_rank<public_derived_from<class_type>>();
    test_rank<private_derived_from<base>>();
    test_rank<private_derived_from<derived>>();
    test_rank<private_derived_from<class_type>>();
    test_rank<protected_derived_from<base>>();
    test_rank<protected_derived_from<derived>>();
    test_rank<protected_derived_from<class_type>>();
    test_rank<union_type>();
    test_rank<non_empty_union>();
    test_rank<empty>();
    test_rank<not_empty>();
    test_rank<bit_zero>();
    test_rank<bit_one>();
    test_rank<base>();
    test_rank<derived>();
    test_rank<abstract>();
    test_rank<public_abstract>();
    test_rank<private_abstract>();
    test_rank<protected_abstract>();
    test_rank<abstract_template<int>>();
    test_rank<abstract_template<double>>();
    test_rank<abstract_template<class_type>>();
    test_rank<abstract_template<incomplete_type>>();
    test_rank<final_type>();
    test_rank<public_destructor>();
    test_rank<protected_destructor>();
    test_rank<private_destructor>();
    test_rank<virtual_public_destructor>();
    test_rank<virtual_protected_destructor>();
    test_rank<virtual_private_destructor>();
    test_rank<pure_public_destructor>();
    test_rank<pure_protected_destructor>();
    test_rank<pure_private_destructor>();
    test_rank<deleted_public_destructor>();
    test_rank<deleted_protected_destructor>();
    test_rank<deleted_private_destructor>();
    test_rank<deleted_virtual_public_destructor>();
    test_rank<deleted_virtual_protected_destructor>();
    test_rank<deleted_virtual_private_destructor>();
    test_rank<Enum>();
    test_rank<EnumSigned>();
    test_rank<EnumUnsigned>();
    test_rank<EnumClass>();
    test_rank<EnumStruct>();
    test_rank<function_type>();
    test_rank<function_ptr>();
    test_rank<member_object_ptr>();
    test_rank<member_function_ptr>();
    test_rank<incomplete_type>();
    test_rank<incomplete_template<void>>();
    test_rank<incomplete_template<int>>();
    test_rank<incomplete_template<class_type>>();
    test_rank<incomplete_template<incomplete_type>>();
    test_rank<incomplete_variadic_template<>>();
    test_rank<incomplete_variadic_template<void>>();
    test_rank<incomplete_variadic_template<int>>();
    test_rank<incomplete_variadic_template<class_type>>();
    test_rank<incomplete_variadic_template<incomplete_type>>();
    test_rank<incomplete_variadic_template<int, void, class_type, volatile char[]>>();
    test_rank<int class_type::*>();
    test_rank<float class_type::*>();
    test_rank<void * class_type::*>();
    test_rank<int * class_type::*>();
    test_rank<int class_type::*&>();
    test_rank<float class_type::*&>();
    test_rank<void * class_type::*&>();
    test_rank<int * class_type::*&>();
    test_rank<int class_type::*&&>();
    test_rank<float class_type::*&&>();
    test_rank<void * class_type::*&&>();
    test_rank<int * class_type::*&&>();
    test_rank<int class_type::* const>();
    test_rank<float class_type::* const>();
    test_rank<void * class_type::* const>();
    test_rank<int class_type::* const&>();
    test_rank<float class_type::* const&>();
    test_rank<void * class_type::* const&>();
    test_rank<int class_type::* const&&>();
    test_rank<float class_type::* const&&>();
    test_rank<void * class_type::* const&&>();
    test_rank<int class_type::* volatile>();
    test_rank<float class_type::* volatile>();
    test_rank<void * class_type::* volatile>();
    test_rank<int class_type::* volatile&>();
    test_rank<float class_type::* volatile&>();
    test_rank<void * class_type::* volatile&>();
    test_rank<int class_type::* volatile&&>();
    test_rank<float class_type::* volatile&&>();
    test_rank<void * class_type::* volatile&&>();
    test_rank<int class_type::* const volatile>();
    test_rank<float class_type::* const volatile>();
    test_rank<void * class_type::* const volatile>();
    test_rank<int class_type::* const volatile&>();
    test_rank<float class_type::* const volatile&>();
    test_rank<void * class_type::* const volatile&>();
    test_rank<int class_type::* const volatile&&>();
    test_rank<float class_type::* const volatile&&>();
    test_rank<void * class_type::* const volatile&&>();
    test_rank<non_copyable>();
    test_rank<non_moveable>();
    test_rank<non_constructible>();
    test_rank<tracked>();
    test_rank<trap_constructible>();
    test_rank<trap_implicit_conversion>();
    test_rank<trap_comma>();
    test_rank<trap_call>();
    test_rank<trap_self_assign>();
    test_rank<trap_deref>();
    test_rank<trap_array_subscript>();

    test_rank<void()>();
    test_rank<void()&>();
    test_rank<void() &&>();
    test_rank<void() const>();
    test_rank<void() const&>();
    test_rank<void() const&&>();
    test_rank<void() volatile>();
    test_rank<void() volatile&>();
    test_rank<void() volatile&&>();
    test_rank<void() const volatile>();
    test_rank<void() const volatile&>();
    test_rank<void() const volatile&&>();
    test_rank<void() noexcept>();
    test_rank<void() & noexcept>();
    test_rank<void() && noexcept>();
    test_rank<void() const noexcept>();
    test_rank<void() const & noexcept>();
    test_rank<void() const && noexcept>();
    test_rank<void() volatile noexcept>();
    test_rank<void() volatile & noexcept>();
    test_rank<void() volatile && noexcept>();
    test_rank<void() const volatile noexcept>();
    test_rank<void() const volatile & noexcept>();
    test_rank<void() const volatile && noexcept>();

    test_rank<void(int)>();
    test_rank<void(int)&>();
    test_rank<void(int) &&>();
    test_rank<void(int) const>();
    test_rank<void(int) const&>();
    test_rank<void(int) const&&>();
    test_rank<void(int) volatile>();
    test_rank<void(int) volatile&>();
    test_rank<void(int) volatile&&>();
    test_rank<void(int) const volatile>();
    test_rank<void(int) const volatile&>();
    test_rank<void(int) const volatile&&>();
    test_rank<void(int) noexcept>();
    test_rank<void(int) & noexcept>();
    test_rank<void(int) && noexcept>();
    test_rank<void(int) const noexcept>();
    test_rank<void(int) const & noexcept>();
    test_rank<void(int) const && noexcept>();
    test_rank<void(int) volatile noexcept>();
    test_rank<void(int) volatile & noexcept>();
    test_rank<void(int) volatile && noexcept>();
    test_rank<void(int) const volatile noexcept>();
    test_rank<void(int) const volatile & noexcept>();
    test_rank<void(int) const volatile && noexcept>();

    test_rank<void(...)>();
    test_rank<void(...)&>();
    test_rank<void(...) &&>();
    test_rank<void(...) const>();
    test_rank<void(...) const&>();
    test_rank<void(...) const&&>();
    test_rank<void(...) volatile>();
    test_rank<void(...) volatile&>();
    test_rank<void(...) volatile&&>();
    test_rank<void(...) const volatile>();
    test_rank<void(...) const volatile&>();
    test_rank<void(...) const volatile&&>();
    test_rank<void(...) noexcept>();
    test_rank<void(...) & noexcept>();
    test_rank<void(...) && noexcept>();
    test_rank<void(...) const noexcept>();
    test_rank<void(...) const & noexcept>();
    test_rank<void(...) const && noexcept>();
    test_rank<void(...) volatile noexcept>();
    test_rank<void(...) volatile & noexcept>();
    test_rank<void(...) volatile && noexcept>();
    test_rank<void(...) const volatile noexcept>();
    test_rank<void(...) const volatile & noexcept>();
    test_rank<void(...) const volatile && noexcept>();

    test_rank<void(int, ...)>();
    test_rank<void(int, ...)&>();
    test_rank<void(int, ...) &&>();
    test_rank<void(int, ...) const>();
    test_rank<void(int, ...) const&>();
    test_rank<void(int, ...) const&&>();
    test_rank<void(int, ...) volatile>();
    test_rank<void(int, ...) volatile&>();
    test_rank<void(int, ...) volatile&&>();
    test_rank<void(int, ...) const volatile>();
    test_rank<void(int, ...) const volatile&>();
    test_rank<void(int, ...) const volatile&&>();
    test_rank<void(int, ...) noexcept>();
    test_rank<void(int, ...) & noexcept>();
    test_rank<void(int, ...) && noexcept>();
    test_rank<void(int, ...) const noexcept>();
    test_rank<void(int, ...) const & noexcept>();
    test_rank<void(int, ...) const && noexcept>();
    test_rank<void(int, ...) volatile noexcept>();
    test_rank<void(int, ...) volatile & noexcept>();
    test_rank<void(int, ...) volatile && noexcept>();
    test_rank<void(int, ...) const volatile noexcept>();
    test_rank<void(int, ...) const volatile & noexcept>();
    test_rank<void(int, ...) const volatile && noexcept>();

    test_rank<int()>();
    test_rank<int()&>();
    test_rank<int() &&>();
    test_rank<int() const>();
    test_rank<int() const&>();
    test_rank<int() const&&>();
    test_rank<int() volatile>();
    test_rank<int() volatile&>();
    test_rank<int() volatile&&>();
    test_rank<int() const volatile>();
    test_rank<int() const volatile&>();
    test_rank<int() const volatile&&>();
    test_rank<int() noexcept>();
    test_rank<int() & noexcept>();
    test_rank<int() && noexcept>();
    test_rank<int() const noexcept>();
    test_rank<int() const & noexcept>();
    test_rank<int() const && noexcept>();
    test_rank<int() volatile noexcept>();
    test_rank<int() volatile & noexcept>();
    test_rank<int() volatile && noexcept>();
    test_rank<int() const volatile noexcept>();
    test_rank<int() const volatile & noexcept>();
    test_rank<int() const volatile && noexcept>();

    test_rank<int(int)>();
    test_rank<int(int)&>();
    test_rank<int(int) &&>();
    test_rank<int(int) const>();
    test_rank<int(int) const&>();
    test_rank<int(int) const&&>();
    test_rank<int(int) volatile>();
    test_rank<int(int) volatile&>();
    test_rank<int(int) volatile&&>();
    test_rank<int(int) const volatile>();
    test_rank<int(int) const volatile&>();
    test_rank<int(int) const volatile&&>();
    test_rank<int(int) noexcept>();
    test_rank<int(int) & noexcept>();
    test_rank<int(int) && noexcept>();
    test_rank<int(int) const noexcept>();
    test_rank<int(int) const & noexcept>();
    test_rank<int(int) const && noexcept>();
    test_rank<int(int) volatile noexcept>();
    test_rank<int(int) volatile & noexcept>();
    test_rank<int(int) volatile && noexcept>();
    test_rank<int(int) const volatile noexcept>();
    test_rank<int(int) const volatile & noexcept>();
    test_rank<int(int) const volatile && noexcept>();

    test_rank<int(...)>();
    test_rank<int(...)&>();
    test_rank<int(...) &&>();
    test_rank<int(...) const>();
    test_rank<int(...) const&>();
    test_rank<int(...) const&&>();
    test_rank<int(...) volatile>();
    test_rank<int(...) volatile&>();
    test_rank<int(...) volatile&&>();
    test_rank<int(...) const volatile>();
    test_rank<int(...) const volatile&>();
    test_rank<int(...) const volatile&&>();
    test_rank<int(...) noexcept>();
    test_rank<int(...) & noexcept>();
    test_rank<int(...) && noexcept>();
    test_rank<int(...) const noexcept>();
    test_rank<int(...) const & noexcept>();
    test_rank<int(...) const && noexcept>();
    test_rank<int(...) volatile noexcept>();
    test_rank<int(...) volatile & noexcept>();
    test_rank<int(...) volatile && noexcept>();
    test_rank<int(...) const volatile noexcept>();
    test_rank<int(...) const volatile & noexcept>();
    test_rank<int(...) const volatile && noexcept>();

    test_rank<int(int, ...)>();
    test_rank<int(int, ...)&>();
    test_rank<int(int, ...) &&>();
    test_rank<int(int, ...) const>();
    test_rank<int(int, ...) const&>();
    test_rank<int(int, ...) const&&>();
    test_rank<int(int, ...) volatile>();
    test_rank<int(int, ...) volatile&>();
    test_rank<int(int, ...) volatile&&>();
    test_rank<int(int, ...) const volatile>();
    test_rank<int(int, ...) const volatile&>();
    test_rank<int(int, ...) const volatile&&>();
    test_rank<int(int, ...) noexcept>();
    test_rank<int(int, ...) & noexcept>();
    test_rank<int(int, ...) && noexcept>();
    test_rank<int(int, ...) const noexcept>();
    test_rank<int(int, ...) const & noexcept>();
    test_rank<int(int, ...) const && noexcept>();
    test_rank<int(int, ...) volatile noexcept>();
    test_rank<int(int, ...) volatile & noexcept>();
    test_rank<int(int, ...) volatile && noexcept>();
    test_rank<int(int, ...) const volatile noexcept>();
    test_rank<int(int, ...) const volatile & noexcept>();
    test_rank<int(int, ...) const volatile && noexcept>();

    test_rank<void (*)()>();
    test_rank<void (*)() noexcept>();

    test_rank<void (*)(int)>();
    test_rank<void (*)(int) noexcept>();

    test_rank<void (*)(...)>();
    test_rank<void (*)(...) noexcept>();

    test_rank<void (*)(int, ...)>();
    test_rank<void (*)(int, ...) noexcept>();

    test_rank<int (*)()>();
    test_rank<int (*)() noexcept>();

    test_rank<int (*)(int)>();
    test_rank<int (*)(int) noexcept>();

    test_rank<int (*)(...)>();
    test_rank<int (*)(...) noexcept>();

    test_rank<int (*)(int, ...)>();
    test_rank<int (*)(int, ...) noexcept>();

    test_rank<void (&)()>();
    test_rank<void (&)() noexcept>();

    test_rank<void (&)(int)>();
    test_rank<void (&)(int) noexcept>();

    test_rank<void (&)(...)>();
    test_rank<void (&)(...) noexcept>();

    test_rank<void (&)(int, ...)>();
    test_rank<void (&)(int, ...) noexcept>();

    test_rank<int (&)()>();
    test_rank<int (&)() noexcept>();

    test_rank<int (&)(int)>();
    test_rank<int (&)(int) noexcept>();

    test_rank<int (&)(...)>();
    test_rank<int (&)(...) noexcept>();

    test_rank<int (&)(int, ...)>();
    test_rank<int (&)(int, ...) noexcept>();

    test_rank<void (&&)()>();
    test_rank<void (&&)() noexcept>();

    test_rank<void (&&)(int)>();
    test_rank<void (&&)(int) noexcept>();

    test_rank<void (&&)(...)>();
    test_rank<void (&&)(...) noexcept>();

    test_rank<void (&&)(int, ...)>();
    test_rank<void (&&)(int, ...) noexcept>();

    test_rank<int (&&)()>();
    test_rank<int (&&)() noexcept>();

    test_rank<int (&&)(int)>();
    test_rank<int (&&)(int) noexcept>();

    test_rank<int (&&)(...)>();
    test_rank<int (&&)(...) noexcept>();

    test_rank<int (&&)(int, ...)>();
    test_rank<int (&&)(int, ...) noexcept>();

    test_rank<void (class_type::*)()>();
    test_rank<void (class_type::*)()&>();
    test_rank<void (class_type::*)() &&>();
    test_rank<void (class_type::*)() const>();
    test_rank<void (class_type::*)() const&>();
    test_rank<void (class_type::*)() const&&>();
    test_rank<void (class_type::*)() noexcept>();
    test_rank<void (class_type::*)() & noexcept>();
    test_rank<void (class_type::*)() && noexcept>();
    test_rank<void (class_type::*)() const noexcept>();
    test_rank<void (class_type::*)() const & noexcept>();
    test_rank<void (class_type::*)() const && noexcept>();

    test_rank<void (class_type::*)(int)>();
    test_rank<void (class_type::*)(int)&>();
    test_rank<void (class_type::*)(int) &&>();
    test_rank<void (class_type::*)(int) const>();
    test_rank<void (class_type::*)(int) const&>();
    test_rank<void (class_type::*)(int) const&&>();
    test_rank<void (class_type::*)(int) noexcept>();
    test_rank<void (class_type::*)(int) & noexcept>();
    test_rank<void (class_type::*)(int) && noexcept>();
    test_rank<void (class_type::*)(int) const noexcept>();
    test_rank<void (class_type::*)(int) const & noexcept>();
    test_rank<void (class_type::*)(int) const && noexcept>();

    test_rank<void (class_type::*)(...)>();
    test_rank<void (class_type::*)(...)&>();
    test_rank<void (class_type::*)(...) &&>();
    test_rank<void (class_type::*)(...) const>();
    test_rank<void (class_type::*)(...) const&>();
    test_rank<void (class_type::*)(...) const&&>();
    test_rank<void (class_type::*)(...) noexcept>();
    test_rank<void (class_type::*)(...) & noexcept>();
    test_rank<void (class_type::*)(...) && noexcept>();
    test_rank<void (class_type::*)(...) const noexcept>();
    test_rank<void (class_type::*)(...) const & noexcept>();
    test_rank<void (class_type::*)(...) const && noexcept>();

    test_rank<void (class_type::*)(int, ...)>();
    test_rank<void (class_type::*)(int, ...)&>();
    test_rank<void (class_type::*)(int, ...) &&>();
    test_rank<void (class_type::*)(int, ...) const>();
    test_rank<void (class_type::*)(int, ...) const&>();
    test_rank<void (class_type::*)(int, ...) const&&>();
    test_rank<void (class_type::*)(int, ...) noexcept>();
    test_rank<void (class_type::*)(int, ...) & noexcept>();
    test_rank<void (class_type::*)(int, ...) && noexcept>();
    test_rank<void (class_type::*)(int, ...) const noexcept>();
    test_rank<void (class_type::*)(int, ...) const & noexcept>();
    test_rank<void (class_type::*)(int, ...) const && noexcept>();

    test_rank<int (class_type::*)()>();
    test_rank<int (class_type::*)()&>();
    test_rank<int (class_type::*)() &&>();
    test_rank<int (class_type::*)() const>();
    test_rank<int (class_type::*)() const&>();
    test_rank<int (class_type::*)() const&&>();
    test_rank<int (class_type::*)() noexcept>();
    test_rank<int (class_type::*)() & noexcept>();
    test_rank<int (class_type::*)() && noexcept>();
    test_rank<int (class_type::*)() const noexcept>();
    test_rank<int (class_type::*)() const & noexcept>();
    test_rank<int (class_type::*)() const && noexcept>();

    test_rank<int (class_type::*)(int)>();
    test_rank<int (class_type::*)(int)&>();
    test_rank<int (class_type::*)(int) &&>();
    test_rank<int (class_type::*)(int) const>();
    test_rank<int (class_type::*)(int) const&>();
    test_rank<int (class_type::*)(int) const&&>();
    test_rank<int (class_type::*)(int) noexcept>();
    test_rank<int (class_type::*)(int) & noexcept>();
    test_rank<int (class_type::*)(int) && noexcept>();
    test_rank<int (class_type::*)(int) const noexcept>();
    test_rank<int (class_type::*)(int) const & noexcept>();
    test_rank<int (class_type::*)(int) const && noexcept>();

    test_rank<int (class_type::*)(...)>();
    test_rank<int (class_type::*)(...)&>();
    test_rank<int (class_type::*)(...) &&>();
    test_rank<int (class_type::*)(...) const>();
    test_rank<int (class_type::*)(...) const&>();
    test_rank<int (class_type::*)(...) const&&>();
    test_rank<int (class_type::*)(...) noexcept>();
    test_rank<int (class_type::*)(...) & noexcept>();
    test_rank<int (class_type::*)(...) && noexcept>();
    test_rank<int (class_type::*)(...) const noexcept>();
    test_rank<int (class_type::*)(...) const & noexcept>();
    test_rank<int (class_type::*)(...) const && noexcept>();

    test_rank<int (class_type::*)(int, ...)>();
    test_rank<int (class_type::*)(int, ...)&>();
    test_rank<int (class_type::*)(int, ...) &&>();
    test_rank<int (class_type::*)(int, ...) const>();
    test_rank<int (class_type::*)(int, ...) const&>();
    test_rank<int (class_type::*)(int, ...) const&&>();
    test_rank<int (class_type::*)(int, ...) noexcept>();
    test_rank<int (class_type::*)(int, ...) & noexcept>();
    test_rank<int (class_type::*)(int, ...) && noexcept>();
    test_rank<int (class_type::*)(int, ...) const noexcept>();
    test_rank<int (class_type::*)(int, ...) const & noexcept>();
    test_rank<int (class_type::*)(int, ...) const && noexcept>();
}
