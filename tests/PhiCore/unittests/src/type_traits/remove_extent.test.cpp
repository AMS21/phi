#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/remove_extent.hpp>
#include <type_traits>
#include <vector>

template <typename TypeT, typename ExpectedT>
void test_remove_extent_impl()
{
    CHECK_SAME_TYPE(typename phi::remove_extent<TypeT>::type, ExpectedT);
    CHECK_SAME_TYPE(phi::remove_extent_t<TypeT>, ExpectedT);

    // Standard compatibility
    CHECK_SAME_TYPE(typename std::remove_extent<TypeT>::type, ExpectedT);
}

template <typename TypeT, typename ExpectedT = TypeT>
void test_remove_extent()
{
    test_remove_extent_impl<TypeT, ExpectedT>();
    test_remove_extent_impl<const TypeT, const ExpectedT>();
    test_remove_extent_impl<volatile TypeT, volatile ExpectedT>();
    test_remove_extent_impl<const volatile TypeT, const volatile ExpectedT>();
}

TEST_CASE("remove_extent")
{
    test_remove_extent<int[], int>();
    test_remove_extent<int[2], int>();
    test_remove_extent<int[][3], int[3]>();
    test_remove_extent<int[2][3], int[3]>();
    test_remove_extent<int[][3][4], int[3][4]>();
    test_remove_extent<int[2][3][4], int[3][4]>();
    test_remove_extent<float[], float>();
    test_remove_extent<float[2], float>();
    test_remove_extent<float[][3], float[3]>();
    test_remove_extent<float[2][3], float[3]>();
    test_remove_extent<float[][3][4], float[3][4]>();
    test_remove_extent<float[2][3][4], float[3][4]>();
    test_remove_extent<class_type[], class_type>();
    test_remove_extent<class_type[2], class_type>();
    test_remove_extent<class_type[][3], class_type[3]>();
    test_remove_extent<class_type[2][3], class_type[3]>();
    test_remove_extent<class_type[][3][4], class_type[3][4]>();
    test_remove_extent<class_type[2][3][4], class_type[3][4]>();

    test_remove_extent<void>();
    test_remove_extent<phi::nullptr_t>();
    test_remove_extent<bool>();
    test_remove_extent<char>();
    test_remove_extent<signed char>();
    test_remove_extent<unsigned char>();
    test_remove_extent<short>();
    test_remove_extent<unsigned short>();
    test_remove_extent<int>();
    test_remove_extent<unsigned int>();
    test_remove_extent<long>();
    test_remove_extent<unsigned long>();
    test_remove_extent<long long>();
    test_remove_extent<unsigned long long>();
    test_remove_extent<float>();
    test_remove_extent<double>();
    test_remove_extent<long double>();
    test_remove_extent<char8_t>();
    test_remove_extent<char16_t>();
    test_remove_extent<char32_t>();
    test_remove_extent<wchar_t>();

    test_remove_extent<phi::boolean>();
    test_remove_extent<phi::integer<signed char>>();
    test_remove_extent<phi::integer<unsigned char>>();
    test_remove_extent<phi::integer<short>>();
    test_remove_extent<phi::integer<unsigned short>>();
    test_remove_extent<phi::integer<int>>();
    test_remove_extent<phi::integer<unsigned int>>();
    test_remove_extent<phi::integer<long>>();
    test_remove_extent<phi::integer<unsigned long>>();
    test_remove_extent<phi::integer<long long>>();
    test_remove_extent<phi::integer<unsigned long long>>();
    test_remove_extent<phi::floating_point<float>>();
    test_remove_extent<phi::floating_point<double>>();
    test_remove_extent<phi::floating_point<long double>>();

    test_remove_extent<std::vector<int>>();
    test_remove_extent<phi::scope_ptr<int>>();

    test_remove_extent<int&>();
    test_remove_extent<const int&>();
    test_remove_extent<volatile int&>();
    test_remove_extent<const volatile int&>();
    test_remove_extent<int&&>();
    test_remove_extent<const int&&>();
    test_remove_extent<volatile int&&>();
    test_remove_extent<const volatile int&&>();
    test_remove_extent<int*>();
    test_remove_extent<const int*>();
    test_remove_extent<volatile int*>();
    test_remove_extent<const volatile int*>();
    test_remove_extent<int**>();
    test_remove_extent<const int**>();
    test_remove_extent<volatile int**>();
    test_remove_extent<const volatile int**>();
    test_remove_extent<int*&>();
    test_remove_extent<const int*&>();
    test_remove_extent<volatile int*&>();
    test_remove_extent<const volatile int*&>();
    test_remove_extent<int*&&>();
    test_remove_extent<const int*&&>();
    test_remove_extent<volatile int*&&>();
    test_remove_extent<const volatile int*&&>();
    test_remove_extent<void*>();
    test_remove_extent<char[3], char>();
    test_remove_extent<char[], char>();
    test_remove_extent<char* [3], char*>();
    test_remove_extent<char*[], char*>();
    test_remove_extent<int(*)[3]>();
    test_remove_extent<int(*)[]>();
    test_remove_extent<int(&)[3]>();
    test_remove_extent<int(&)[]>();
    test_remove_extent<int(&&)[3]>();
    test_remove_extent<int(&&)[]>();
    test_remove_extent<char[3][2], char[2]>();
    test_remove_extent<char[][2], char[2]>();
    test_remove_extent<char* [3][2], char* [2]>();
    test_remove_extent<char*[][2], char* [2]>();
    test_remove_extent<int(*)[3][2]>();
    test_remove_extent<int(*)[][2]>();
    test_remove_extent<int(&)[3][2]>();
    test_remove_extent<int(&)[][2]>();
    test_remove_extent<int(&&)[3][2]>();
    test_remove_extent<int(&&)[][2]>();
    test_remove_extent<class_type>();
    test_remove_extent<class_type[], class_type>();
    test_remove_extent<class_type[2], class_type>();
    test_remove_extent<template_type<void>>();
    test_remove_extent<template_type<int>>();
    test_remove_extent<template_type<class_type>>();
    test_remove_extent<template_type<incomplete_type>>();
    test_remove_extent<variadic_template<>>();
    test_remove_extent<variadic_template<void>>();
    test_remove_extent<variadic_template<int>>();
    test_remove_extent<variadic_template<class_type>>();
    test_remove_extent<variadic_template<incomplete_type>>();
    test_remove_extent<variadic_template<int, void, class_type, volatile char[]>>();
    test_remove_extent<public_derived_from<base>>();
    test_remove_extent<public_derived_from<derived>>();
    test_remove_extent<public_derived_from<class_type>>();
    test_remove_extent<private_derived_from<base>>();
    test_remove_extent<private_derived_from<derived>>();
    test_remove_extent<private_derived_from<class_type>>();
    test_remove_extent<protected_derived_from<base>>();
    test_remove_extent<protected_derived_from<derived>>();
    test_remove_extent<protected_derived_from<class_type>>();
    test_remove_extent<union_type>();
    test_remove_extent<non_empty_union>();
    test_remove_extent<empty>();
    test_remove_extent<not_empty>();
    test_remove_extent<bit_zero>();
    test_remove_extent<bit_one>();
    test_remove_extent<base>();
    test_remove_extent<derived>();
    test_remove_extent<abstract>();
    test_remove_extent<public_abstract>();
    test_remove_extent<private_abstract>();
    test_remove_extent<protected_abstract>();
    test_remove_extent<abstract_template<int>>();
    test_remove_extent<abstract_template<double>>();
    test_remove_extent<abstract_template<class_type>>();
    test_remove_extent<abstract_template<incomplete_type>>();
    test_remove_extent<final_type>();
    test_remove_extent<public_destructor>();
    test_remove_extent<protected_destructor>();
    test_remove_extent<private_destructor>();
    test_remove_extent<virtual_public_destructor>();
    test_remove_extent<virtual_protected_destructor>();
    test_remove_extent<virtual_private_destructor>();
    test_remove_extent<pure_public_destructor>();
    test_remove_extent<pure_protected_destructor>();
    test_remove_extent<pure_private_destructor>();
    test_remove_extent<deleted_public_destructor>();
    test_remove_extent<deleted_protected_destructor>();
    test_remove_extent<deleted_private_destructor>();
    test_remove_extent<deleted_virtual_public_destructor>();
    test_remove_extent<deleted_virtual_protected_destructor>();
    test_remove_extent<deleted_virtual_private_destructor>();
    test_remove_extent<Enum>();
    test_remove_extent<EnumSigned>();
    test_remove_extent<EnumUnsigned>();
    test_remove_extent<EnumClass>();
    test_remove_extent<EnumStruct>();
    test_remove_extent<function_type>();
    test_remove_extent<function_ptr>();
    test_remove_extent<member_object_ptr>();
    test_remove_extent<member_function_ptr>();
    test_remove_extent<incomplete_type>();
    test_remove_extent<incomplete_template<void>>();
    test_remove_extent<incomplete_template<int>>();
    test_remove_extent<incomplete_template<class_type>>();
    test_remove_extent<incomplete_template<incomplete_type>>();
    test_remove_extent<incomplete_variadic_template<>>();
    test_remove_extent<incomplete_variadic_template<void>>();
    test_remove_extent<incomplete_variadic_template<int>>();
    test_remove_extent<incomplete_variadic_template<class_type>>();
    test_remove_extent<incomplete_variadic_template<incomplete_type>>();
    test_remove_extent<incomplete_variadic_template<int, void, class_type, volatile char[]>>();
    test_remove_extent<int class_type::*>();
    test_remove_extent<float class_type::*>();
    test_remove_extent<void * class_type::*>();
    test_remove_extent<int * class_type::*>();
    test_remove_extent<int class_type::*&>();
    test_remove_extent<float class_type::*&>();
    test_remove_extent<void * class_type::*&>();
    test_remove_extent<int * class_type::*&>();
    test_remove_extent<int class_type::*&&>();
    test_remove_extent<float class_type::*&&>();
    test_remove_extent<void * class_type::*&&>();
    test_remove_extent<int * class_type::*&&>();
    test_remove_extent<int class_type::* const>();
    test_remove_extent<float class_type::* const>();
    test_remove_extent<void * class_type::* const>();
    test_remove_extent<int class_type::* const&>();
    test_remove_extent<float class_type::* const&>();
    test_remove_extent<void * class_type::* const&>();
    test_remove_extent<int class_type::* const&&>();
    test_remove_extent<float class_type::* const&&>();
    test_remove_extent<void * class_type::* const&&>();
    test_remove_extent<int class_type::* volatile>();
    test_remove_extent<float class_type::* volatile>();
    test_remove_extent<void * class_type::* volatile>();
    test_remove_extent<int class_type::* volatile&>();
    test_remove_extent<float class_type::* volatile&>();
    test_remove_extent<void * class_type::* volatile&>();
    test_remove_extent<int class_type::* volatile&&>();
    test_remove_extent<float class_type::* volatile&&>();
    test_remove_extent<void * class_type::* volatile&&>();
    test_remove_extent<int class_type::* const volatile>();
    test_remove_extent<float class_type::* const volatile>();
    test_remove_extent<void * class_type::* const volatile>();
    test_remove_extent<int class_type::* const volatile&>();
    test_remove_extent<float class_type::* const volatile&>();
    test_remove_extent<void * class_type::* const volatile&>();
    test_remove_extent<int class_type::* const volatile&&>();
    test_remove_extent<float class_type::* const volatile&&>();
    test_remove_extent<void * class_type::* const volatile&&>();
    test_remove_extent<non_copyable>();
    test_remove_extent<non_moveable>();
    test_remove_extent<non_constructible>();
    test_remove_extent<tracked>();
    test_remove_extent<trap_constructible>();
    test_remove_extent<trap_implicit_conversion>();
    test_remove_extent<trap_comma>();
    test_remove_extent<trap_call>();
    test_remove_extent<trap_self_assign>();
    test_remove_extent<trap_deref>();
    test_remove_extent<trap_array_subscript>();

    test_remove_extent<void()>();
    test_remove_extent<void()&>();
    test_remove_extent<void() &&>();
    test_remove_extent<void() const>();
    test_remove_extent<void() const&>();
    test_remove_extent<void() const&&>();
    test_remove_extent<void() volatile>();
    test_remove_extent<void() volatile&>();
    test_remove_extent<void() volatile&&>();
    test_remove_extent<void() const volatile>();
    test_remove_extent<void() const volatile&>();
    test_remove_extent<void() const volatile&&>();
    test_remove_extent<void() noexcept>();
    test_remove_extent<void() & noexcept>();
    test_remove_extent<void() && noexcept>();
    test_remove_extent<void() const noexcept>();
    test_remove_extent<void() const & noexcept>();
    test_remove_extent<void() const && noexcept>();
    test_remove_extent<void() volatile noexcept>();
    test_remove_extent<void() volatile & noexcept>();
    test_remove_extent<void() volatile && noexcept>();
    test_remove_extent<void() const volatile noexcept>();
    test_remove_extent<void() const volatile & noexcept>();
    test_remove_extent<void() const volatile && noexcept>();

    test_remove_extent<void(int)>();
    test_remove_extent<void(int)&>();
    test_remove_extent<void(int) &&>();
    test_remove_extent<void(int) const>();
    test_remove_extent<void(int) const&>();
    test_remove_extent<void(int) const&&>();
    test_remove_extent<void(int) volatile>();
    test_remove_extent<void(int) volatile&>();
    test_remove_extent<void(int) volatile&&>();
    test_remove_extent<void(int) const volatile>();
    test_remove_extent<void(int) const volatile&>();
    test_remove_extent<void(int) const volatile&&>();
    test_remove_extent<void(int) noexcept>();
    test_remove_extent<void(int) & noexcept>();
    test_remove_extent<void(int) && noexcept>();
    test_remove_extent<void(int) const noexcept>();
    test_remove_extent<void(int) const & noexcept>();
    test_remove_extent<void(int) const && noexcept>();
    test_remove_extent<void(int) volatile noexcept>();
    test_remove_extent<void(int) volatile & noexcept>();
    test_remove_extent<void(int) volatile && noexcept>();
    test_remove_extent<void(int) const volatile noexcept>();
    test_remove_extent<void(int) const volatile & noexcept>();
    test_remove_extent<void(int) const volatile && noexcept>();

    test_remove_extent<void(...)>();
    test_remove_extent<void(...)&>();
    test_remove_extent<void(...) &&>();
    test_remove_extent<void(...) const>();
    test_remove_extent<void(...) const&>();
    test_remove_extent<void(...) const&&>();
    test_remove_extent<void(...) volatile>();
    test_remove_extent<void(...) volatile&>();
    test_remove_extent<void(...) volatile&&>();
    test_remove_extent<void(...) const volatile>();
    test_remove_extent<void(...) const volatile&>();
    test_remove_extent<void(...) const volatile&&>();
    test_remove_extent<void(...) noexcept>();
    test_remove_extent<void(...) & noexcept>();
    test_remove_extent<void(...) && noexcept>();
    test_remove_extent<void(...) const noexcept>();
    test_remove_extent<void(...) const & noexcept>();
    test_remove_extent<void(...) const && noexcept>();
    test_remove_extent<void(...) volatile noexcept>();
    test_remove_extent<void(...) volatile & noexcept>();
    test_remove_extent<void(...) volatile && noexcept>();
    test_remove_extent<void(...) const volatile noexcept>();
    test_remove_extent<void(...) const volatile & noexcept>();
    test_remove_extent<void(...) const volatile && noexcept>();

    test_remove_extent<void(int, ...)>();
    test_remove_extent<void(int, ...)&>();
    test_remove_extent<void(int, ...) &&>();
    test_remove_extent<void(int, ...) const>();
    test_remove_extent<void(int, ...) const&>();
    test_remove_extent<void(int, ...) const&&>();
    test_remove_extent<void(int, ...) volatile>();
    test_remove_extent<void(int, ...) volatile&>();
    test_remove_extent<void(int, ...) volatile&&>();
    test_remove_extent<void(int, ...) const volatile>();
    test_remove_extent<void(int, ...) const volatile&>();
    test_remove_extent<void(int, ...) const volatile&&>();
    test_remove_extent<void(int, ...) noexcept>();
    test_remove_extent<void(int, ...) & noexcept>();
    test_remove_extent<void(int, ...) && noexcept>();
    test_remove_extent<void(int, ...) const noexcept>();
    test_remove_extent<void(int, ...) const & noexcept>();
    test_remove_extent<void(int, ...) const && noexcept>();
    test_remove_extent<void(int, ...) volatile noexcept>();
    test_remove_extent<void(int, ...) volatile & noexcept>();
    test_remove_extent<void(int, ...) volatile && noexcept>();
    test_remove_extent<void(int, ...) const volatile noexcept>();
    test_remove_extent<void(int, ...) const volatile & noexcept>();
    test_remove_extent<void(int, ...) const volatile && noexcept>();

    test_remove_extent<int()>();
    test_remove_extent<int()&>();
    test_remove_extent<int() &&>();
    test_remove_extent<int() const>();
    test_remove_extent<int() const&>();
    test_remove_extent<int() const&&>();
    test_remove_extent<int() volatile>();
    test_remove_extent<int() volatile&>();
    test_remove_extent<int() volatile&&>();
    test_remove_extent<int() const volatile>();
    test_remove_extent<int() const volatile&>();
    test_remove_extent<int() const volatile&&>();
    test_remove_extent<int() noexcept>();
    test_remove_extent<int() & noexcept>();
    test_remove_extent<int() && noexcept>();
    test_remove_extent<int() const noexcept>();
    test_remove_extent<int() const & noexcept>();
    test_remove_extent<int() const && noexcept>();
    test_remove_extent<int() volatile noexcept>();
    test_remove_extent<int() volatile & noexcept>();
    test_remove_extent<int() volatile && noexcept>();
    test_remove_extent<int() const volatile noexcept>();
    test_remove_extent<int() const volatile & noexcept>();
    test_remove_extent<int() const volatile && noexcept>();

    test_remove_extent<int(int)>();
    test_remove_extent<int(int)&>();
    test_remove_extent<int(int) &&>();
    test_remove_extent<int(int) const>();
    test_remove_extent<int(int) const&>();
    test_remove_extent<int(int) const&&>();
    test_remove_extent<int(int) volatile>();
    test_remove_extent<int(int) volatile&>();
    test_remove_extent<int(int) volatile&&>();
    test_remove_extent<int(int) const volatile>();
    test_remove_extent<int(int) const volatile&>();
    test_remove_extent<int(int) const volatile&&>();
    test_remove_extent<int(int) noexcept>();
    test_remove_extent<int(int) & noexcept>();
    test_remove_extent<int(int) && noexcept>();
    test_remove_extent<int(int) const noexcept>();
    test_remove_extent<int(int) const & noexcept>();
    test_remove_extent<int(int) const && noexcept>();
    test_remove_extent<int(int) volatile noexcept>();
    test_remove_extent<int(int) volatile & noexcept>();
    test_remove_extent<int(int) volatile && noexcept>();
    test_remove_extent<int(int) const volatile noexcept>();
    test_remove_extent<int(int) const volatile & noexcept>();
    test_remove_extent<int(int) const volatile && noexcept>();

    test_remove_extent<int(...)>();
    test_remove_extent<int(...)&>();
    test_remove_extent<int(...) &&>();
    test_remove_extent<int(...) const>();
    test_remove_extent<int(...) const&>();
    test_remove_extent<int(...) const&&>();
    test_remove_extent<int(...) volatile>();
    test_remove_extent<int(...) volatile&>();
    test_remove_extent<int(...) volatile&&>();
    test_remove_extent<int(...) const volatile>();
    test_remove_extent<int(...) const volatile&>();
    test_remove_extent<int(...) const volatile&&>();
    test_remove_extent<int(...) noexcept>();
    test_remove_extent<int(...) & noexcept>();
    test_remove_extent<int(...) && noexcept>();
    test_remove_extent<int(...) const noexcept>();
    test_remove_extent<int(...) const & noexcept>();
    test_remove_extent<int(...) const && noexcept>();
    test_remove_extent<int(...) volatile noexcept>();
    test_remove_extent<int(...) volatile & noexcept>();
    test_remove_extent<int(...) volatile && noexcept>();
    test_remove_extent<int(...) const volatile noexcept>();
    test_remove_extent<int(...) const volatile & noexcept>();
    test_remove_extent<int(...) const volatile && noexcept>();

    test_remove_extent<int(int, ...)>();
    test_remove_extent<int(int, ...)&>();
    test_remove_extent<int(int, ...) &&>();
    test_remove_extent<int(int, ...) const>();
    test_remove_extent<int(int, ...) const&>();
    test_remove_extent<int(int, ...) const&&>();
    test_remove_extent<int(int, ...) volatile>();
    test_remove_extent<int(int, ...) volatile&>();
    test_remove_extent<int(int, ...) volatile&&>();
    test_remove_extent<int(int, ...) const volatile>();
    test_remove_extent<int(int, ...) const volatile&>();
    test_remove_extent<int(int, ...) const volatile&&>();
    test_remove_extent<int(int, ...) noexcept>();
    test_remove_extent<int(int, ...) & noexcept>();
    test_remove_extent<int(int, ...) && noexcept>();
    test_remove_extent<int(int, ...) const noexcept>();
    test_remove_extent<int(int, ...) const & noexcept>();
    test_remove_extent<int(int, ...) const && noexcept>();
    test_remove_extent<int(int, ...) volatile noexcept>();
    test_remove_extent<int(int, ...) volatile & noexcept>();
    test_remove_extent<int(int, ...) volatile && noexcept>();
    test_remove_extent<int(int, ...) const volatile noexcept>();
    test_remove_extent<int(int, ...) const volatile & noexcept>();
    test_remove_extent<int(int, ...) const volatile && noexcept>();

    test_remove_extent<void (*)()>();
    test_remove_extent<void (*)() noexcept>();

    test_remove_extent<void (*)(int)>();
    test_remove_extent<void (*)(int) noexcept>();

    test_remove_extent<void (*)(...)>();
    test_remove_extent<void (*)(...) noexcept>();

    test_remove_extent<void (*)(int, ...)>();
    test_remove_extent<void (*)(int, ...) noexcept>();

    test_remove_extent<int (*)()>();
    test_remove_extent<int (*)() noexcept>();

    test_remove_extent<int (*)(int)>();
    test_remove_extent<int (*)(int) noexcept>();

    test_remove_extent<int (*)(...)>();
    test_remove_extent<int (*)(...) noexcept>();

    test_remove_extent<int (*)(int, ...)>();
    test_remove_extent<int (*)(int, ...) noexcept>();

    test_remove_extent<void (&)()>();
    test_remove_extent<void (&)() noexcept>();

    test_remove_extent<void (&)(int)>();
    test_remove_extent<void (&)(int) noexcept>();

    test_remove_extent<void (&)(...)>();
    test_remove_extent<void (&)(...) noexcept>();

    test_remove_extent<void (&)(int, ...)>();
    test_remove_extent<void (&)(int, ...) noexcept>();

    test_remove_extent<int (&)()>();
    test_remove_extent<int (&)() noexcept>();

    test_remove_extent<int (&)(int)>();
    test_remove_extent<int (&)(int) noexcept>();

    test_remove_extent<int (&)(...)>();
    test_remove_extent<int (&)(...) noexcept>();

    test_remove_extent<int (&)(int, ...)>();
    test_remove_extent<int (&)(int, ...) noexcept>();

    test_remove_extent<void (&&)()>();
    test_remove_extent<void (&&)() noexcept>();

    test_remove_extent<void (&&)(int)>();
    test_remove_extent<void (&&)(int) noexcept>();

    test_remove_extent<void (&&)(...)>();
    test_remove_extent<void (&&)(...) noexcept>();

    test_remove_extent<void (&&)(int, ...)>();
    test_remove_extent<void (&&)(int, ...) noexcept>();

    test_remove_extent<int (&&)()>();
    test_remove_extent<int (&&)() noexcept>();

    test_remove_extent<int (&&)(int)>();
    test_remove_extent<int (&&)(int) noexcept>();

    test_remove_extent<int (&&)(...)>();
    test_remove_extent<int (&&)(...) noexcept>();

    test_remove_extent<int (&&)(int, ...)>();
    test_remove_extent<int (&&)(int, ...) noexcept>();

    test_remove_extent<void (class_type::*)()>();
    test_remove_extent<void (class_type::*)()&>();
    test_remove_extent<void (class_type::*)() &&>();
    test_remove_extent<void (class_type::*)() const>();
    test_remove_extent<void (class_type::*)() const&>();
    test_remove_extent<void (class_type::*)() const&&>();
    test_remove_extent<void (class_type::*)() noexcept>();
    test_remove_extent<void (class_type::*)() & noexcept>();
    test_remove_extent<void (class_type::*)() && noexcept>();
    test_remove_extent<void (class_type::*)() const noexcept>();
    test_remove_extent<void (class_type::*)() const & noexcept>();
    test_remove_extent<void (class_type::*)() const && noexcept>();

    test_remove_extent<void (class_type::*)(int)>();
    test_remove_extent<void (class_type::*)(int)&>();
    test_remove_extent<void (class_type::*)(int) &&>();
    test_remove_extent<void (class_type::*)(int) const>();
    test_remove_extent<void (class_type::*)(int) const&>();
    test_remove_extent<void (class_type::*)(int) const&&>();
    test_remove_extent<void (class_type::*)(int) noexcept>();
    test_remove_extent<void (class_type::*)(int) & noexcept>();
    test_remove_extent<void (class_type::*)(int) && noexcept>();
    test_remove_extent<void (class_type::*)(int) const noexcept>();
    test_remove_extent<void (class_type::*)(int) const & noexcept>();
    test_remove_extent<void (class_type::*)(int) const && noexcept>();

    test_remove_extent<void (class_type::*)(...)>();
    test_remove_extent<void (class_type::*)(...)&>();
    test_remove_extent<void (class_type::*)(...) &&>();
    test_remove_extent<void (class_type::*)(...) const>();
    test_remove_extent<void (class_type::*)(...) const&>();
    test_remove_extent<void (class_type::*)(...) const&&>();
    test_remove_extent<void (class_type::*)(...) noexcept>();
    test_remove_extent<void (class_type::*)(...) & noexcept>();
    test_remove_extent<void (class_type::*)(...) && noexcept>();
    test_remove_extent<void (class_type::*)(...) const noexcept>();
    test_remove_extent<void (class_type::*)(...) const & noexcept>();
    test_remove_extent<void (class_type::*)(...) const && noexcept>();

    test_remove_extent<void (class_type::*)(int, ...)>();
    test_remove_extent<void (class_type::*)(int, ...)&>();
    test_remove_extent<void (class_type::*)(int, ...) &&>();
    test_remove_extent<void (class_type::*)(int, ...) const>();
    test_remove_extent<void (class_type::*)(int, ...) const&>();
    test_remove_extent<void (class_type::*)(int, ...) const&&>();
    test_remove_extent<void (class_type::*)(int, ...) noexcept>();
    test_remove_extent<void (class_type::*)(int, ...) & noexcept>();
    test_remove_extent<void (class_type::*)(int, ...) && noexcept>();
    test_remove_extent<void (class_type::*)(int, ...) const noexcept>();
    test_remove_extent<void (class_type::*)(int, ...) const & noexcept>();
    test_remove_extent<void (class_type::*)(int, ...) const && noexcept>();

    test_remove_extent<int (class_type::*)()>();
    test_remove_extent<int (class_type::*)()&>();
    test_remove_extent<int (class_type::*)() &&>();
    test_remove_extent<int (class_type::*)() const>();
    test_remove_extent<int (class_type::*)() const&>();
    test_remove_extent<int (class_type::*)() const&&>();
    test_remove_extent<int (class_type::*)() noexcept>();
    test_remove_extent<int (class_type::*)() & noexcept>();
    test_remove_extent<int (class_type::*)() && noexcept>();
    test_remove_extent<int (class_type::*)() const noexcept>();
    test_remove_extent<int (class_type::*)() const & noexcept>();
    test_remove_extent<int (class_type::*)() const && noexcept>();

    test_remove_extent<int (class_type::*)(int)>();
    test_remove_extent<int (class_type::*)(int)&>();
    test_remove_extent<int (class_type::*)(int) &&>();
    test_remove_extent<int (class_type::*)(int) const>();
    test_remove_extent<int (class_type::*)(int) const&>();
    test_remove_extent<int (class_type::*)(int) const&&>();
    test_remove_extent<int (class_type::*)(int) noexcept>();
    test_remove_extent<int (class_type::*)(int) & noexcept>();
    test_remove_extent<int (class_type::*)(int) && noexcept>();
    test_remove_extent<int (class_type::*)(int) const noexcept>();
    test_remove_extent<int (class_type::*)(int) const & noexcept>();
    test_remove_extent<int (class_type::*)(int) const && noexcept>();

    test_remove_extent<int (class_type::*)(...)>();
    test_remove_extent<int (class_type::*)(...)&>();
    test_remove_extent<int (class_type::*)(...) &&>();
    test_remove_extent<int (class_type::*)(...) const>();
    test_remove_extent<int (class_type::*)(...) const&>();
    test_remove_extent<int (class_type::*)(...) const&&>();
    test_remove_extent<int (class_type::*)(...) noexcept>();
    test_remove_extent<int (class_type::*)(...) & noexcept>();
    test_remove_extent<int (class_type::*)(...) && noexcept>();
    test_remove_extent<int (class_type::*)(...) const noexcept>();
    test_remove_extent<int (class_type::*)(...) const & noexcept>();
    test_remove_extent<int (class_type::*)(...) const && noexcept>();

    test_remove_extent<int (class_type::*)(int, ...)>();
    test_remove_extent<int (class_type::*)(int, ...)&>();
    test_remove_extent<int (class_type::*)(int, ...) &&>();
    test_remove_extent<int (class_type::*)(int, ...) const>();
    test_remove_extent<int (class_type::*)(int, ...) const&>();
    test_remove_extent<int (class_type::*)(int, ...) const&&>();
    test_remove_extent<int (class_type::*)(int, ...) noexcept>();
    test_remove_extent<int (class_type::*)(int, ...) & noexcept>();
    test_remove_extent<int (class_type::*)(int, ...) && noexcept>();
    test_remove_extent<int (class_type::*)(int, ...) const noexcept>();
    test_remove_extent<int (class_type::*)(int, ...) const & noexcept>();
    test_remove_extent<int (class_type::*)(int, ...) const && noexcept>();
}
