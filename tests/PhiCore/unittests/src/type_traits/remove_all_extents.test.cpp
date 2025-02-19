#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/remove_all_extents.hpp>
#include <type_traits>
#include <vector>

template <typename TypeT, typename ExpectedT>
void test_remove_all_extents_impl()
{
    CHECK_SAME_TYPE(typename phi::remove_all_extents<TypeT>::type, ExpectedT);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    CHECK_SAME_TYPE(phi::remove_all_extents_t<TypeT>, ExpectedT);
#endif

    // Standard compatibility
    CHECK_SAME_TYPE(typename std::remove_all_extents<TypeT>::type, ExpectedT);
}

template <typename TypeT, typename ExpectedT = TypeT>
void test_remove_all_extents()
{
    test_remove_all_extents_impl<TypeT, ExpectedT>();
    test_remove_all_extents_impl<const TypeT, const ExpectedT>();
    test_remove_all_extents_impl<volatile TypeT, volatile ExpectedT>();
    test_remove_all_extents_impl<const volatile TypeT, const volatile ExpectedT>();
}

TEST_CASE("remove_all_extents")
{
    test_remove_all_extents<int[], int>();
    test_remove_all_extents<int[2], int>();
    test_remove_all_extents<int[][3], int>();
    test_remove_all_extents<int[2][3], int>();
    test_remove_all_extents<int[][3][4], int>();
    test_remove_all_extents<int[2][3][4], int>();
    test_remove_all_extents<float[], float>();
    test_remove_all_extents<float[2], float>();
    test_remove_all_extents<float[][3], float>();
    test_remove_all_extents<float[2][3], float>();
    test_remove_all_extents<float[][3][4], float>();
    test_remove_all_extents<float[2][3][4], float>();
    test_remove_all_extents<class_type[], class_type>();
    test_remove_all_extents<class_type[2], class_type>();
    test_remove_all_extents<class_type[][3], class_type>();
    test_remove_all_extents<class_type[2][3], class_type>();
    test_remove_all_extents<class_type[][3][4], class_type>();
    test_remove_all_extents<class_type[2][3][4], class_type>();

    test_remove_all_extents<void>();
    test_remove_all_extents<phi::nullptr_t>();
    test_remove_all_extents<bool>();
    test_remove_all_extents<char>();
    test_remove_all_extents<signed char>();
    test_remove_all_extents<unsigned char>();
    test_remove_all_extents<short>();
    test_remove_all_extents<unsigned short>();
    test_remove_all_extents<int>();
    test_remove_all_extents<unsigned int>();
    test_remove_all_extents<long>();
    test_remove_all_extents<unsigned long>();
    test_remove_all_extents<long long>();
    test_remove_all_extents<unsigned long long>();
    test_remove_all_extents<float>();
    test_remove_all_extents<double>();
    test_remove_all_extents<long double>();
    test_remove_all_extents<char8_t>();
    test_remove_all_extents<char16_t>();
    test_remove_all_extents<char32_t>();
    test_remove_all_extents<wchar_t>();

    test_remove_all_extents<phi::boolean>();
    test_remove_all_extents<phi::integer<signed char>>();
    test_remove_all_extents<phi::integer<unsigned char>>();
    test_remove_all_extents<phi::integer<short>>();
    test_remove_all_extents<phi::integer<unsigned short>>();
    test_remove_all_extents<phi::integer<int>>();
    test_remove_all_extents<phi::integer<unsigned int>>();
    test_remove_all_extents<phi::integer<long>>();
    test_remove_all_extents<phi::integer<unsigned long>>();
    test_remove_all_extents<phi::integer<long long>>();
    test_remove_all_extents<phi::integer<unsigned long long>>();
    test_remove_all_extents<phi::floating_point<float>>();
    test_remove_all_extents<phi::floating_point<double>>();
    test_remove_all_extents<phi::floating_point<long double>>();

    test_remove_all_extents<std::vector<int>>();
    test_remove_all_extents<phi::scope_ptr<int>>();

    test_remove_all_extents<int&>();
    test_remove_all_extents<const int&>();
    test_remove_all_extents<volatile int&>();
    test_remove_all_extents<const volatile int&>();
    test_remove_all_extents<int&&>();
    test_remove_all_extents<const int&&>();
    test_remove_all_extents<volatile int&&>();
    test_remove_all_extents<const volatile int&&>();
    test_remove_all_extents<int*>();
    test_remove_all_extents<const int*>();
    test_remove_all_extents<volatile int*>();
    test_remove_all_extents<const volatile int*>();
    test_remove_all_extents<int**>();
    test_remove_all_extents<const int**>();
    test_remove_all_extents<volatile int**>();
    test_remove_all_extents<const volatile int**>();
    test_remove_all_extents<int*&>();
    test_remove_all_extents<const int*&>();
    test_remove_all_extents<volatile int*&>();
    test_remove_all_extents<const volatile int*&>();
    test_remove_all_extents<int*&&>();
    test_remove_all_extents<const int*&&>();
    test_remove_all_extents<volatile int*&&>();
    test_remove_all_extents<const volatile int*&&>();
    test_remove_all_extents<void*>();
    test_remove_all_extents<char[3], char>();
    test_remove_all_extents<char[], char>();
    test_remove_all_extents<char* [3], char*>();
    test_remove_all_extents<char*[], char*>();
    test_remove_all_extents<int(*)[3]>();
    test_remove_all_extents<int(*)[]>();
    test_remove_all_extents<int(&)[3]>();
    test_remove_all_extents<int(&)[]>();
    test_remove_all_extents<int(&&)[3]>();
    test_remove_all_extents<int(&&)[]>();
    test_remove_all_extents<char[3][2], char>();
    test_remove_all_extents<char[][2], char>();
    test_remove_all_extents<char* [3][2], char*>();
    test_remove_all_extents<char*[][2], char*>();
    test_remove_all_extents<int(*)[3][2]>();
    test_remove_all_extents<int(*)[][2]>();
    test_remove_all_extents<int(&)[3][2]>();
    test_remove_all_extents<int(&)[][2]>();
    test_remove_all_extents<int(&&)[3][2]>();
    test_remove_all_extents<int(&&)[][2]>();
    test_remove_all_extents<class_type>();
    test_remove_all_extents<class_type[], class_type>();
    test_remove_all_extents<class_type[2], class_type>();
    test_remove_all_extents<template_type<void>>();
    test_remove_all_extents<template_type<int>>();
    test_remove_all_extents<template_type<class_type>>();
    test_remove_all_extents<template_type<incomplete_type>>();
    test_remove_all_extents<variadic_template<>>();
    test_remove_all_extents<variadic_template<void>>();
    test_remove_all_extents<variadic_template<int>>();
    test_remove_all_extents<variadic_template<class_type>>();
    test_remove_all_extents<variadic_template<incomplete_type>>();
    test_remove_all_extents<variadic_template<int, void, class_type, volatile char[]>>();
    test_remove_all_extents<public_derived_from<base>>();
    test_remove_all_extents<public_derived_from<derived>>();
    test_remove_all_extents<public_derived_from<class_type>>();
    test_remove_all_extents<private_derived_from<base>>();
    test_remove_all_extents<private_derived_from<derived>>();
    test_remove_all_extents<private_derived_from<class_type>>();
    test_remove_all_extents<protected_derived_from<base>>();
    test_remove_all_extents<protected_derived_from<derived>>();
    test_remove_all_extents<protected_derived_from<class_type>>();
    test_remove_all_extents<union_type>();
    test_remove_all_extents<non_empty_union>();
    test_remove_all_extents<empty>();
    test_remove_all_extents<not_empty>();
    test_remove_all_extents<bit_zero>();
    test_remove_all_extents<bit_one>();
    test_remove_all_extents<base>();
    test_remove_all_extents<derived>();
    test_remove_all_extents<abstract>();
    test_remove_all_extents<public_abstract>();
    test_remove_all_extents<private_abstract>();
    test_remove_all_extents<protected_abstract>();
    test_remove_all_extents<abstract_template<int>>();
    test_remove_all_extents<abstract_template<double>>();
    test_remove_all_extents<abstract_template<class_type>>();
    test_remove_all_extents<abstract_template<incomplete_type>>();
    test_remove_all_extents<final_type>();
    test_remove_all_extents<public_destructor>();
    test_remove_all_extents<protected_destructor>();
    test_remove_all_extents<private_destructor>();
    test_remove_all_extents<virtual_public_destructor>();
    test_remove_all_extents<virtual_protected_destructor>();
    test_remove_all_extents<virtual_private_destructor>();
    test_remove_all_extents<pure_public_destructor>();
    test_remove_all_extents<pure_protected_destructor>();
    test_remove_all_extents<pure_private_destructor>();
    test_remove_all_extents<deleted_public_destructor>();
    test_remove_all_extents<deleted_protected_destructor>();
    test_remove_all_extents<deleted_private_destructor>();
    test_remove_all_extents<deleted_virtual_public_destructor>();
    test_remove_all_extents<deleted_virtual_protected_destructor>();
    test_remove_all_extents<deleted_virtual_private_destructor>();
    test_remove_all_extents<Enum>();
    test_remove_all_extents<EnumSigned>();
    test_remove_all_extents<EnumUnsigned>();
    test_remove_all_extents<EnumClass>();
    test_remove_all_extents<EnumStruct>();
    test_remove_all_extents<function_type>();
    test_remove_all_extents<function_ptr>();
    test_remove_all_extents<member_object_ptr>();
    test_remove_all_extents<member_function_ptr>();
    test_remove_all_extents<incomplete_type>();
    test_remove_all_extents<incomplete_template<void>>();
    test_remove_all_extents<incomplete_template<int>>();
    test_remove_all_extents<incomplete_template<class_type>>();
    test_remove_all_extents<incomplete_template<incomplete_type>>();
    test_remove_all_extents<incomplete_variadic_template<>>();
    test_remove_all_extents<incomplete_variadic_template<void>>();
    test_remove_all_extents<incomplete_variadic_template<int>>();
    test_remove_all_extents<incomplete_variadic_template<class_type>>();
    test_remove_all_extents<incomplete_variadic_template<incomplete_type>>();
    test_remove_all_extents<incomplete_variadic_template<int, void, class_type, volatile char[]>>();
    test_remove_all_extents<int class_type::*>();
    test_remove_all_extents<float class_type::*>();
    test_remove_all_extents<void * class_type::*>();
    test_remove_all_extents<int * class_type::*>();
    test_remove_all_extents<int class_type::*&>();
    test_remove_all_extents<float class_type::*&>();
    test_remove_all_extents<void * class_type::*&>();
    test_remove_all_extents<int * class_type::*&>();
    test_remove_all_extents<int class_type::*&&>();
    test_remove_all_extents<float class_type::*&&>();
    test_remove_all_extents<void * class_type::*&&>();
    test_remove_all_extents<int * class_type::*&&>();
    test_remove_all_extents<int class_type::* const>();
    test_remove_all_extents<float class_type::* const>();
    test_remove_all_extents<void * class_type::* const>();
    test_remove_all_extents<int class_type::* const&>();
    test_remove_all_extents<float class_type::* const&>();
    test_remove_all_extents<void * class_type::* const&>();
    test_remove_all_extents<int class_type::* const&&>();
    test_remove_all_extents<float class_type::* const&&>();
    test_remove_all_extents<void * class_type::* const&&>();
    test_remove_all_extents<int class_type::* volatile>();
    test_remove_all_extents<float class_type::* volatile>();
    test_remove_all_extents<void * class_type::* volatile>();
    test_remove_all_extents<int class_type::* volatile&>();
    test_remove_all_extents<float class_type::* volatile&>();
    test_remove_all_extents<void * class_type::* volatile&>();
    test_remove_all_extents<int class_type::* volatile&&>();
    test_remove_all_extents<float class_type::* volatile&&>();
    test_remove_all_extents<void * class_type::* volatile&&>();
    test_remove_all_extents<int class_type::* const volatile>();
    test_remove_all_extents<float class_type::* const volatile>();
    test_remove_all_extents<void * class_type::* const volatile>();
    test_remove_all_extents<int class_type::* const volatile&>();
    test_remove_all_extents<float class_type::* const volatile&>();
    test_remove_all_extents<void * class_type::* const volatile&>();
    test_remove_all_extents<int class_type::* const volatile&&>();
    test_remove_all_extents<float class_type::* const volatile&&>();
    test_remove_all_extents<void * class_type::* const volatile&&>();
    test_remove_all_extents<non_copyable>();
    test_remove_all_extents<non_moveable>();
    test_remove_all_extents<non_constructible>();
    test_remove_all_extents<tracked>();
    test_remove_all_extents<trap_constructible>();
    test_remove_all_extents<trap_implicit_conversion>();
    test_remove_all_extents<trap_comma>();
    test_remove_all_extents<trap_call>();
    test_remove_all_extents<trap_self_assign>();
    test_remove_all_extents<trap_deref>();
    test_remove_all_extents<trap_array_subscript>();

    test_remove_all_extents<void()>();
    test_remove_all_extents<void()&>();
    test_remove_all_extents<void() &&>();
    test_remove_all_extents<void() const>();
    test_remove_all_extents<void() const&>();
    test_remove_all_extents<void() const&&>();
    test_remove_all_extents<void() volatile>();
    test_remove_all_extents<void() volatile&>();
    test_remove_all_extents<void() volatile&&>();
    test_remove_all_extents<void() const volatile>();
    test_remove_all_extents<void() const volatile&>();
    test_remove_all_extents<void() const volatile&&>();
    test_remove_all_extents<void() noexcept>();
    test_remove_all_extents<void() & noexcept>();
    test_remove_all_extents<void() && noexcept>();
    test_remove_all_extents<void() const noexcept>();
    test_remove_all_extents<void() const & noexcept>();
    test_remove_all_extents<void() const && noexcept>();
    test_remove_all_extents<void() volatile noexcept>();
    test_remove_all_extents<void() volatile & noexcept>();
    test_remove_all_extents<void() volatile && noexcept>();
    test_remove_all_extents<void() const volatile noexcept>();
    test_remove_all_extents<void() const volatile & noexcept>();
    test_remove_all_extents<void() const volatile && noexcept>();

    test_remove_all_extents<void(int)>();
    test_remove_all_extents<void(int)&>();
    test_remove_all_extents<void(int) &&>();
    test_remove_all_extents<void(int) const>();
    test_remove_all_extents<void(int) const&>();
    test_remove_all_extents<void(int) const&&>();
    test_remove_all_extents<void(int) volatile>();
    test_remove_all_extents<void(int) volatile&>();
    test_remove_all_extents<void(int) volatile&&>();
    test_remove_all_extents<void(int) const volatile>();
    test_remove_all_extents<void(int) const volatile&>();
    test_remove_all_extents<void(int) const volatile&&>();
    test_remove_all_extents<void(int) noexcept>();
    test_remove_all_extents<void(int) & noexcept>();
    test_remove_all_extents<void(int) && noexcept>();
    test_remove_all_extents<void(int) const noexcept>();
    test_remove_all_extents<void(int) const & noexcept>();
    test_remove_all_extents<void(int) const && noexcept>();
    test_remove_all_extents<void(int) volatile noexcept>();
    test_remove_all_extents<void(int) volatile & noexcept>();
    test_remove_all_extents<void(int) volatile && noexcept>();
    test_remove_all_extents<void(int) const volatile noexcept>();
    test_remove_all_extents<void(int) const volatile & noexcept>();
    test_remove_all_extents<void(int) const volatile && noexcept>();

    test_remove_all_extents<void(...)>();
    test_remove_all_extents<void(...)&>();
    test_remove_all_extents<void(...) &&>();
    test_remove_all_extents<void(...) const>();
    test_remove_all_extents<void(...) const&>();
    test_remove_all_extents<void(...) const&&>();
    test_remove_all_extents<void(...) volatile>();
    test_remove_all_extents<void(...) volatile&>();
    test_remove_all_extents<void(...) volatile&&>();
    test_remove_all_extents<void(...) const volatile>();
    test_remove_all_extents<void(...) const volatile&>();
    test_remove_all_extents<void(...) const volatile&&>();
    test_remove_all_extents<void(...) noexcept>();
    test_remove_all_extents<void(...) & noexcept>();
    test_remove_all_extents<void(...) && noexcept>();
    test_remove_all_extents<void(...) const noexcept>();
    test_remove_all_extents<void(...) const & noexcept>();
    test_remove_all_extents<void(...) const && noexcept>();
    test_remove_all_extents<void(...) volatile noexcept>();
    test_remove_all_extents<void(...) volatile & noexcept>();
    test_remove_all_extents<void(...) volatile && noexcept>();
    test_remove_all_extents<void(...) const volatile noexcept>();
    test_remove_all_extents<void(...) const volatile & noexcept>();
    test_remove_all_extents<void(...) const volatile && noexcept>();

    test_remove_all_extents<void(int, ...)>();
    test_remove_all_extents<void(int, ...)&>();
    test_remove_all_extents<void(int, ...) &&>();
    test_remove_all_extents<void(int, ...) const>();
    test_remove_all_extents<void(int, ...) const&>();
    test_remove_all_extents<void(int, ...) const&&>();
    test_remove_all_extents<void(int, ...) volatile>();
    test_remove_all_extents<void(int, ...) volatile&>();
    test_remove_all_extents<void(int, ...) volatile&&>();
    test_remove_all_extents<void(int, ...) const volatile>();
    test_remove_all_extents<void(int, ...) const volatile&>();
    test_remove_all_extents<void(int, ...) const volatile&&>();
    test_remove_all_extents<void(int, ...) noexcept>();
    test_remove_all_extents<void(int, ...) & noexcept>();
    test_remove_all_extents<void(int, ...) && noexcept>();
    test_remove_all_extents<void(int, ...) const noexcept>();
    test_remove_all_extents<void(int, ...) const & noexcept>();
    test_remove_all_extents<void(int, ...) const && noexcept>();
    test_remove_all_extents<void(int, ...) volatile noexcept>();
    test_remove_all_extents<void(int, ...) volatile & noexcept>();
    test_remove_all_extents<void(int, ...) volatile && noexcept>();
    test_remove_all_extents<void(int, ...) const volatile noexcept>();
    test_remove_all_extents<void(int, ...) const volatile & noexcept>();
    test_remove_all_extents<void(int, ...) const volatile && noexcept>();

    test_remove_all_extents<int()>();
    test_remove_all_extents<int()&>();
    test_remove_all_extents<int() &&>();
    test_remove_all_extents<int() const>();
    test_remove_all_extents<int() const&>();
    test_remove_all_extents<int() const&&>();
    test_remove_all_extents<int() volatile>();
    test_remove_all_extents<int() volatile&>();
    test_remove_all_extents<int() volatile&&>();
    test_remove_all_extents<int() const volatile>();
    test_remove_all_extents<int() const volatile&>();
    test_remove_all_extents<int() const volatile&&>();
    test_remove_all_extents<int() noexcept>();
    test_remove_all_extents<int() & noexcept>();
    test_remove_all_extents<int() && noexcept>();
    test_remove_all_extents<int() const noexcept>();
    test_remove_all_extents<int() const & noexcept>();
    test_remove_all_extents<int() const && noexcept>();
    test_remove_all_extents<int() volatile noexcept>();
    test_remove_all_extents<int() volatile & noexcept>();
    test_remove_all_extents<int() volatile && noexcept>();
    test_remove_all_extents<int() const volatile noexcept>();
    test_remove_all_extents<int() const volatile & noexcept>();
    test_remove_all_extents<int() const volatile && noexcept>();

    test_remove_all_extents<int(int)>();
    test_remove_all_extents<int(int)&>();
    test_remove_all_extents<int(int) &&>();
    test_remove_all_extents<int(int) const>();
    test_remove_all_extents<int(int) const&>();
    test_remove_all_extents<int(int) const&&>();
    test_remove_all_extents<int(int) volatile>();
    test_remove_all_extents<int(int) volatile&>();
    test_remove_all_extents<int(int) volatile&&>();
    test_remove_all_extents<int(int) const volatile>();
    test_remove_all_extents<int(int) const volatile&>();
    test_remove_all_extents<int(int) const volatile&&>();
    test_remove_all_extents<int(int) noexcept>();
    test_remove_all_extents<int(int) & noexcept>();
    test_remove_all_extents<int(int) && noexcept>();
    test_remove_all_extents<int(int) const noexcept>();
    test_remove_all_extents<int(int) const & noexcept>();
    test_remove_all_extents<int(int) const && noexcept>();
    test_remove_all_extents<int(int) volatile noexcept>();
    test_remove_all_extents<int(int) volatile & noexcept>();
    test_remove_all_extents<int(int) volatile && noexcept>();
    test_remove_all_extents<int(int) const volatile noexcept>();
    test_remove_all_extents<int(int) const volatile & noexcept>();
    test_remove_all_extents<int(int) const volatile && noexcept>();

    test_remove_all_extents<int(...)>();
    test_remove_all_extents<int(...)&>();
    test_remove_all_extents<int(...) &&>();
    test_remove_all_extents<int(...) const>();
    test_remove_all_extents<int(...) const&>();
    test_remove_all_extents<int(...) const&&>();
    test_remove_all_extents<int(...) volatile>();
    test_remove_all_extents<int(...) volatile&>();
    test_remove_all_extents<int(...) volatile&&>();
    test_remove_all_extents<int(...) const volatile>();
    test_remove_all_extents<int(...) const volatile&>();
    test_remove_all_extents<int(...) const volatile&&>();
    test_remove_all_extents<int(...) noexcept>();
    test_remove_all_extents<int(...) & noexcept>();
    test_remove_all_extents<int(...) && noexcept>();
    test_remove_all_extents<int(...) const noexcept>();
    test_remove_all_extents<int(...) const & noexcept>();
    test_remove_all_extents<int(...) const && noexcept>();
    test_remove_all_extents<int(...) volatile noexcept>();
    test_remove_all_extents<int(...) volatile & noexcept>();
    test_remove_all_extents<int(...) volatile && noexcept>();
    test_remove_all_extents<int(...) const volatile noexcept>();
    test_remove_all_extents<int(...) const volatile & noexcept>();
    test_remove_all_extents<int(...) const volatile && noexcept>();

    test_remove_all_extents<int(int, ...)>();
    test_remove_all_extents<int(int, ...)&>();
    test_remove_all_extents<int(int, ...) &&>();
    test_remove_all_extents<int(int, ...) const>();
    test_remove_all_extents<int(int, ...) const&>();
    test_remove_all_extents<int(int, ...) const&&>();
    test_remove_all_extents<int(int, ...) volatile>();
    test_remove_all_extents<int(int, ...) volatile&>();
    test_remove_all_extents<int(int, ...) volatile&&>();
    test_remove_all_extents<int(int, ...) const volatile>();
    test_remove_all_extents<int(int, ...) const volatile&>();
    test_remove_all_extents<int(int, ...) const volatile&&>();
    test_remove_all_extents<int(int, ...) noexcept>();
    test_remove_all_extents<int(int, ...) & noexcept>();
    test_remove_all_extents<int(int, ...) && noexcept>();
    test_remove_all_extents<int(int, ...) const noexcept>();
    test_remove_all_extents<int(int, ...) const & noexcept>();
    test_remove_all_extents<int(int, ...) const && noexcept>();
    test_remove_all_extents<int(int, ...) volatile noexcept>();
    test_remove_all_extents<int(int, ...) volatile & noexcept>();
    test_remove_all_extents<int(int, ...) volatile && noexcept>();
    test_remove_all_extents<int(int, ...) const volatile noexcept>();
    test_remove_all_extents<int(int, ...) const volatile & noexcept>();
    test_remove_all_extents<int(int, ...) const volatile && noexcept>();

    test_remove_all_extents<void (*)()>();
    test_remove_all_extents<void (*)() noexcept>();

    test_remove_all_extents<void (*)(int)>();
    test_remove_all_extents<void (*)(int) noexcept>();

    test_remove_all_extents<void (*)(...)>();
    test_remove_all_extents<void (*)(...) noexcept>();

    test_remove_all_extents<void (*)(int, ...)>();
    test_remove_all_extents<void (*)(int, ...) noexcept>();

    test_remove_all_extents<int (*)()>();
    test_remove_all_extents<int (*)() noexcept>();

    test_remove_all_extents<int (*)(int)>();
    test_remove_all_extents<int (*)(int) noexcept>();

    test_remove_all_extents<int (*)(...)>();
    test_remove_all_extents<int (*)(...) noexcept>();

    test_remove_all_extents<int (*)(int, ...)>();
    test_remove_all_extents<int (*)(int, ...) noexcept>();

    test_remove_all_extents<void (&)()>();
    test_remove_all_extents<void (&)() noexcept>();

    test_remove_all_extents<void (&)(int)>();
    test_remove_all_extents<void (&)(int) noexcept>();

    test_remove_all_extents<void (&)(...)>();
    test_remove_all_extents<void (&)(...) noexcept>();

    test_remove_all_extents<void (&)(int, ...)>();
    test_remove_all_extents<void (&)(int, ...) noexcept>();

    test_remove_all_extents<int (&)()>();
    test_remove_all_extents<int (&)() noexcept>();

    test_remove_all_extents<int (&)(int)>();
    test_remove_all_extents<int (&)(int) noexcept>();

    test_remove_all_extents<int (&)(...)>();
    test_remove_all_extents<int (&)(...) noexcept>();

    test_remove_all_extents<int (&)(int, ...)>();
    test_remove_all_extents<int (&)(int, ...) noexcept>();

    test_remove_all_extents<void (&&)()>();
    test_remove_all_extents<void (&&)() noexcept>();

    test_remove_all_extents<void (&&)(int)>();
    test_remove_all_extents<void (&&)(int) noexcept>();

    test_remove_all_extents<void (&&)(...)>();
    test_remove_all_extents<void (&&)(...) noexcept>();

    test_remove_all_extents<void (&&)(int, ...)>();
    test_remove_all_extents<void (&&)(int, ...) noexcept>();

    test_remove_all_extents<int (&&)()>();
    test_remove_all_extents<int (&&)() noexcept>();

    test_remove_all_extents<int (&&)(int)>();
    test_remove_all_extents<int (&&)(int) noexcept>();

    test_remove_all_extents<int (&&)(...)>();
    test_remove_all_extents<int (&&)(...) noexcept>();

    test_remove_all_extents<int (&&)(int, ...)>();
    test_remove_all_extents<int (&&)(int, ...) noexcept>();

    test_remove_all_extents<void (class_type::*)()>();
    test_remove_all_extents<void (class_type::*)()&>();
    test_remove_all_extents<void (class_type::*)() &&>();
    test_remove_all_extents<void (class_type::*)() const>();
    test_remove_all_extents<void (class_type::*)() const&>();
    test_remove_all_extents<void (class_type::*)() const&&>();
    test_remove_all_extents<void (class_type::*)() noexcept>();
    test_remove_all_extents<void (class_type::*)() & noexcept>();
    test_remove_all_extents<void (class_type::*)() && noexcept>();
    test_remove_all_extents<void (class_type::*)() const noexcept>();
    test_remove_all_extents<void (class_type::*)() const & noexcept>();
    test_remove_all_extents<void (class_type::*)() const && noexcept>();

    test_remove_all_extents<void (class_type::*)(int)>();
    test_remove_all_extents<void (class_type::*)(int)&>();
    test_remove_all_extents<void (class_type::*)(int) &&>();
    test_remove_all_extents<void (class_type::*)(int) const>();
    test_remove_all_extents<void (class_type::*)(int) const&>();
    test_remove_all_extents<void (class_type::*)(int) const&&>();
    test_remove_all_extents<void (class_type::*)(int) noexcept>();
    test_remove_all_extents<void (class_type::*)(int) & noexcept>();
    test_remove_all_extents<void (class_type::*)(int) && noexcept>();
    test_remove_all_extents<void (class_type::*)(int) const noexcept>();
    test_remove_all_extents<void (class_type::*)(int) const & noexcept>();
    test_remove_all_extents<void (class_type::*)(int) const && noexcept>();

    test_remove_all_extents<void (class_type::*)(...)>();
    test_remove_all_extents<void (class_type::*)(...)&>();
    test_remove_all_extents<void (class_type::*)(...) &&>();
    test_remove_all_extents<void (class_type::*)(...) const>();
    test_remove_all_extents<void (class_type::*)(...) const&>();
    test_remove_all_extents<void (class_type::*)(...) const&&>();
    test_remove_all_extents<void (class_type::*)(...) noexcept>();
    test_remove_all_extents<void (class_type::*)(...) & noexcept>();
    test_remove_all_extents<void (class_type::*)(...) && noexcept>();
    test_remove_all_extents<void (class_type::*)(...) const noexcept>();
    test_remove_all_extents<void (class_type::*)(...) const & noexcept>();
    test_remove_all_extents<void (class_type::*)(...) const && noexcept>();

    test_remove_all_extents<void (class_type::*)(int, ...)>();
    test_remove_all_extents<void (class_type::*)(int, ...)&>();
    test_remove_all_extents<void (class_type::*)(int, ...) &&>();
    test_remove_all_extents<void (class_type::*)(int, ...) const>();
    test_remove_all_extents<void (class_type::*)(int, ...) const&>();
    test_remove_all_extents<void (class_type::*)(int, ...) const&&>();
    test_remove_all_extents<void (class_type::*)(int, ...) noexcept>();
    test_remove_all_extents<void (class_type::*)(int, ...) & noexcept>();
    test_remove_all_extents<void (class_type::*)(int, ...) && noexcept>();
    test_remove_all_extents<void (class_type::*)(int, ...) const noexcept>();
    test_remove_all_extents<void (class_type::*)(int, ...) const & noexcept>();
    test_remove_all_extents<void (class_type::*)(int, ...) const && noexcept>();

    test_remove_all_extents<int (class_type::*)()>();
    test_remove_all_extents<int (class_type::*)()&>();
    test_remove_all_extents<int (class_type::*)() &&>();
    test_remove_all_extents<int (class_type::*)() const>();
    test_remove_all_extents<int (class_type::*)() const&>();
    test_remove_all_extents<int (class_type::*)() const&&>();
    test_remove_all_extents<int (class_type::*)() noexcept>();
    test_remove_all_extents<int (class_type::*)() & noexcept>();
    test_remove_all_extents<int (class_type::*)() && noexcept>();
    test_remove_all_extents<int (class_type::*)() const noexcept>();
    test_remove_all_extents<int (class_type::*)() const & noexcept>();
    test_remove_all_extents<int (class_type::*)() const && noexcept>();

    test_remove_all_extents<int (class_type::*)(int)>();
    test_remove_all_extents<int (class_type::*)(int)&>();
    test_remove_all_extents<int (class_type::*)(int) &&>();
    test_remove_all_extents<int (class_type::*)(int) const>();
    test_remove_all_extents<int (class_type::*)(int) const&>();
    test_remove_all_extents<int (class_type::*)(int) const&&>();
    test_remove_all_extents<int (class_type::*)(int) noexcept>();
    test_remove_all_extents<int (class_type::*)(int) & noexcept>();
    test_remove_all_extents<int (class_type::*)(int) && noexcept>();
    test_remove_all_extents<int (class_type::*)(int) const noexcept>();
    test_remove_all_extents<int (class_type::*)(int) const & noexcept>();
    test_remove_all_extents<int (class_type::*)(int) const && noexcept>();

    test_remove_all_extents<int (class_type::*)(...)>();
    test_remove_all_extents<int (class_type::*)(...)&>();
    test_remove_all_extents<int (class_type::*)(...) &&>();
    test_remove_all_extents<int (class_type::*)(...) const>();
    test_remove_all_extents<int (class_type::*)(...) const&>();
    test_remove_all_extents<int (class_type::*)(...) const&&>();
    test_remove_all_extents<int (class_type::*)(...) noexcept>();
    test_remove_all_extents<int (class_type::*)(...) & noexcept>();
    test_remove_all_extents<int (class_type::*)(...) && noexcept>();
    test_remove_all_extents<int (class_type::*)(...) const noexcept>();
    test_remove_all_extents<int (class_type::*)(...) const & noexcept>();
    test_remove_all_extents<int (class_type::*)(...) const && noexcept>();

    test_remove_all_extents<int (class_type::*)(int, ...)>();
    test_remove_all_extents<int (class_type::*)(int, ...)&>();
    test_remove_all_extents<int (class_type::*)(int, ...) &&>();
    test_remove_all_extents<int (class_type::*)(int, ...) const>();
    test_remove_all_extents<int (class_type::*)(int, ...) const&>();
    test_remove_all_extents<int (class_type::*)(int, ...) const&&>();
    test_remove_all_extents<int (class_type::*)(int, ...) noexcept>();
    test_remove_all_extents<int (class_type::*)(int, ...) & noexcept>();
    test_remove_all_extents<int (class_type::*)(int, ...) && noexcept>();
    test_remove_all_extents<int (class_type::*)(int, ...) const noexcept>();
    test_remove_all_extents<int (class_type::*)(int, ...) const & noexcept>();
    test_remove_all_extents<int (class_type::*)(int, ...) const && noexcept>();
}
