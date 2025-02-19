#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/remove_pointer.hpp>
#include <vector>

template <typename TypeT, typename ExpectedT>
void test_remove_pointer_impl()
{
    CHECK_SAME_TYPE(typename phi::remove_pointer<TypeT>::type, ExpectedT);
    CHECK_SAME_TYPE(phi::remove_pointer_t<TypeT>, ExpectedT);

    // Standard compatibility
    CHECK_SAME_TYPE(typename std::remove_pointer<TypeT>::type, ExpectedT);
}

template <typename TypeT, typename ExpectedT = TypeT>
void test_remove_pointer()
{
    test_remove_pointer_impl<TypeT, ExpectedT>();
    test_remove_pointer_impl<const TypeT, const ExpectedT>();
    test_remove_pointer_impl<volatile TypeT, volatile ExpectedT>();
    test_remove_pointer_impl<const volatile TypeT, const volatile ExpectedT>();
}

template <typename TypeT, typename ExpectedT>
void test_remove_pointer_ptr()
{
    CHECK_SAME_TYPE(typename phi::remove_pointer<TypeT>::type, ExpectedT);
    CHECK_SAME_TYPE(phi::remove_pointer_t<TypeT>, ExpectedT);

    // Standard compatibility
    CHECK_SAME_TYPE(typename std::remove_pointer<TypeT>::type, ExpectedT);
}

TEST_CASE("remove_pointer")
{
    test_remove_pointer_ptr<int* const, int>();
    test_remove_pointer_ptr<int* volatile, int>();
    test_remove_pointer_ptr<int* const volatile, int>();
    test_remove_pointer_ptr<int** const, int*>();
    test_remove_pointer_ptr<int** volatile, int*>();
    test_remove_pointer_ptr<int** const volatile, int*>();
    test_remove_pointer_ptr<int* const*, int* const>();
    test_remove_pointer_ptr<int* volatile*, int* volatile>();
    test_remove_pointer_ptr<int* const volatile*, int* const volatile>();

    test_remove_pointer<void>();
    test_remove_pointer<phi::nullptr_t>();
    test_remove_pointer<bool>();
    test_remove_pointer<char>();
    test_remove_pointer<signed char>();
    test_remove_pointer<unsigned char>();
    test_remove_pointer<short>();
    test_remove_pointer<unsigned short>();
    test_remove_pointer<int>();
    test_remove_pointer<unsigned int>();
    test_remove_pointer<long>();
    test_remove_pointer<unsigned long>();
    test_remove_pointer<long long>();
    test_remove_pointer<unsigned long long>();
    test_remove_pointer<float>();
    test_remove_pointer<double>();
    test_remove_pointer<long double>();
    test_remove_pointer<char8_t>();
    test_remove_pointer<char16_t>();
    test_remove_pointer<char32_t>();
    test_remove_pointer<wchar_t>();

    test_remove_pointer<phi::boolean>();
    test_remove_pointer<phi::integer<signed char>>();
    test_remove_pointer<phi::integer<unsigned char>>();
    test_remove_pointer<phi::integer<short>>();
    test_remove_pointer<phi::integer<unsigned short>>();
    test_remove_pointer<phi::integer<int>>();
    test_remove_pointer<phi::integer<unsigned int>>();
    test_remove_pointer<phi::integer<long>>();
    test_remove_pointer<phi::integer<unsigned long>>();
    test_remove_pointer<phi::integer<long long>>();
    test_remove_pointer<phi::integer<unsigned long long>>();
    test_remove_pointer<phi::floating_point<float>>();
    test_remove_pointer<phi::floating_point<double>>();
    test_remove_pointer<phi::floating_point<long double>>();

    test_remove_pointer<std::vector<int>>();
    test_remove_pointer<phi::scope_ptr<int>>();

    test_remove_pointer<int&>();
    test_remove_pointer<const int&>();
    test_remove_pointer<volatile int&>();
    test_remove_pointer<const volatile int&>();
    test_remove_pointer<int&&>();
    test_remove_pointer<const int&&>();
    test_remove_pointer<volatile int&&>();
    test_remove_pointer<const volatile int&&>();
    test_remove_pointer_ptr<int*, int>();
    test_remove_pointer_ptr<const int*, const int>();
    test_remove_pointer_ptr<volatile int*, volatile int>();
    test_remove_pointer_ptr<const volatile int*, const volatile int>();
    test_remove_pointer_ptr<int**, int*>();
    test_remove_pointer_ptr<const int**, const int*>();
    test_remove_pointer_ptr<volatile int**, volatile int*>();
    test_remove_pointer_ptr<const volatile int**, const volatile int*>();
    test_remove_pointer<int*&>();
    test_remove_pointer<const int*&>();
    test_remove_pointer<volatile int*&>();
    test_remove_pointer<const volatile int*&>();
    test_remove_pointer<int*&&>();
    test_remove_pointer<const int*&&>();
    test_remove_pointer<volatile int*&&>();
    test_remove_pointer<const volatile int*&&>();
    test_remove_pointer_ptr<void*, void>();
    test_remove_pointer<char[3]>();
    test_remove_pointer<char[]>();
    test_remove_pointer<char* [3]>();
    test_remove_pointer<char*[]>();
    test_remove_pointer_ptr<int(*)[3], int[3]>();
    test_remove_pointer_ptr<int(*)[], int[]>();
    test_remove_pointer<int(&)[3]>();
    test_remove_pointer<int(&)[]>();
    test_remove_pointer<int(&&)[3]>();
    test_remove_pointer<int(&&)[]>();
    test_remove_pointer<char[3][2]>();
    test_remove_pointer<char[][2]>();
    test_remove_pointer<char* [3][2]>();
    test_remove_pointer<char*[][2]>();
    test_remove_pointer_ptr<int(*)[3][2], int[3][2]>();
    test_remove_pointer_ptr<int(*)[][2], int[][2]>();
    test_remove_pointer<int(&)[3][2]>();
    test_remove_pointer<int(&)[][2]>();
    test_remove_pointer<int(&&)[3][2]>();
    test_remove_pointer<int(&&)[][2]>();
    test_remove_pointer<class_type>();
    test_remove_pointer<class_type[]>();
    test_remove_pointer<class_type[2]>();
    test_remove_pointer<template_type<void>>();
    test_remove_pointer<template_type<int>>();
    test_remove_pointer<template_type<class_type>>();
    test_remove_pointer<template_type<incomplete_type>>();
    test_remove_pointer<variadic_template<>>();
    test_remove_pointer<variadic_template<void>>();
    test_remove_pointer<variadic_template<int>>();
    test_remove_pointer<variadic_template<class_type>>();
    test_remove_pointer<variadic_template<incomplete_type>>();
    test_remove_pointer<variadic_template<int, void, class_type, volatile char[]>>();
    test_remove_pointer<public_derived_from<base>>();
    test_remove_pointer<public_derived_from<derived>>();
    test_remove_pointer<public_derived_from<class_type>>();
    test_remove_pointer<private_derived_from<base>>();
    test_remove_pointer<private_derived_from<derived>>();
    test_remove_pointer<private_derived_from<class_type>>();
    test_remove_pointer<protected_derived_from<base>>();
    test_remove_pointer<protected_derived_from<derived>>();
    test_remove_pointer<protected_derived_from<class_type>>();
    test_remove_pointer<union_type>();
    test_remove_pointer<non_empty_union>();
    test_remove_pointer<empty>();
    test_remove_pointer<not_empty>();
    test_remove_pointer<bit_zero>();
    test_remove_pointer<bit_one>();
    test_remove_pointer<base>();
    test_remove_pointer<derived>();
    test_remove_pointer<abstract>();
    test_remove_pointer<public_abstract>();
    test_remove_pointer<private_abstract>();
    test_remove_pointer<protected_abstract>();
    test_remove_pointer<abstract_template<int>>();
    test_remove_pointer<abstract_template<double>>();
    test_remove_pointer<abstract_template<class_type>>();
    test_remove_pointer<abstract_template<incomplete_type>>();
    test_remove_pointer<final_type>();
    test_remove_pointer<public_destructor>();
    test_remove_pointer<protected_destructor>();
    test_remove_pointer<private_destructor>();
    test_remove_pointer<virtual_public_destructor>();
    test_remove_pointer<virtual_protected_destructor>();
    test_remove_pointer<virtual_private_destructor>();
    test_remove_pointer<pure_public_destructor>();
    test_remove_pointer<pure_protected_destructor>();
    test_remove_pointer<pure_private_destructor>();
    test_remove_pointer<deleted_public_destructor>();
    test_remove_pointer<deleted_protected_destructor>();
    test_remove_pointer<deleted_private_destructor>();
    test_remove_pointer<deleted_virtual_public_destructor>();
    test_remove_pointer<deleted_virtual_protected_destructor>();
    test_remove_pointer<deleted_virtual_private_destructor>();
    test_remove_pointer<Enum>();
    test_remove_pointer<EnumSigned>();
    test_remove_pointer<EnumUnsigned>();
    test_remove_pointer<EnumClass>();
    test_remove_pointer<EnumStruct>();
    test_remove_pointer<function_type>();
    test_remove_pointer_ptr<function_ptr, function_type>();
    test_remove_pointer<member_object_ptr>();
    test_remove_pointer<member_function_ptr>();
    test_remove_pointer<incomplete_type>();
    test_remove_pointer<incomplete_template<void>>();
    test_remove_pointer<incomplete_template<int>>();
    test_remove_pointer<incomplete_template<class_type>>();
    test_remove_pointer<incomplete_template<incomplete_type>>();
    test_remove_pointer<incomplete_variadic_template<>>();
    test_remove_pointer<incomplete_variadic_template<void>>();
    test_remove_pointer<incomplete_variadic_template<int>>();
    test_remove_pointer<incomplete_variadic_template<class_type>>();
    test_remove_pointer<incomplete_variadic_template<incomplete_type>>();
    test_remove_pointer<incomplete_variadic_template<int, void, class_type, volatile char[]>>();
    test_remove_pointer<int class_type::*>();
    test_remove_pointer<float class_type::*>();
    test_remove_pointer<void * class_type::*>();
    test_remove_pointer<int * class_type::*>();
    test_remove_pointer<int class_type::*&>();
    test_remove_pointer<float class_type::*&>();
    test_remove_pointer<void * class_type::*&>();
    test_remove_pointer<int * class_type::*&>();
    test_remove_pointer<int class_type::*&&>();
    test_remove_pointer<float class_type::*&&>();
    test_remove_pointer<void * class_type::*&&>();
    test_remove_pointer<int * class_type::*&&>();
    test_remove_pointer<int class_type::* const>();
    test_remove_pointer<float class_type::* const>();
    test_remove_pointer<void * class_type::* const>();
    test_remove_pointer<int class_type::* const&>();
    test_remove_pointer<float class_type::* const&>();
    test_remove_pointer<void * class_type::* const&>();
    test_remove_pointer<int class_type::* const&&>();
    test_remove_pointer<float class_type::* const&&>();
    test_remove_pointer<void * class_type::* const&&>();
    test_remove_pointer<int class_type::* volatile>();
    test_remove_pointer<float class_type::* volatile>();
    test_remove_pointer<void * class_type::* volatile>();
    test_remove_pointer<int class_type::* volatile&>();
    test_remove_pointer<float class_type::* volatile&>();
    test_remove_pointer<void * class_type::* volatile&>();
    test_remove_pointer<int class_type::* volatile&&>();
    test_remove_pointer<float class_type::* volatile&&>();
    test_remove_pointer<void * class_type::* volatile&&>();
    test_remove_pointer<int class_type::* const volatile>();
    test_remove_pointer<float class_type::* const volatile>();
    test_remove_pointer<void * class_type::* const volatile>();
    test_remove_pointer<int class_type::* const volatile&>();
    test_remove_pointer<float class_type::* const volatile&>();
    test_remove_pointer<void * class_type::* const volatile&>();
    test_remove_pointer<int class_type::* const volatile&&>();
    test_remove_pointer<float class_type::* const volatile&&>();
    test_remove_pointer<void * class_type::* const volatile&&>();
    test_remove_pointer<non_copyable>();
    test_remove_pointer<non_moveable>();
    test_remove_pointer<non_constructible>();
    test_remove_pointer<tracked>();
    test_remove_pointer<trap_constructible>();
    test_remove_pointer<trap_implicit_conversion>();
    test_remove_pointer<trap_comma>();
    test_remove_pointer<trap_call>();
    test_remove_pointer<trap_self_assign>();
    test_remove_pointer<trap_deref>();
    test_remove_pointer<trap_array_subscript>();

    test_remove_pointer<void()>();
    test_remove_pointer<void()&>();
    test_remove_pointer<void() &&>();
    test_remove_pointer<void() const>();
    test_remove_pointer<void() const&>();
    test_remove_pointer<void() const&&>();
    test_remove_pointer<void() volatile>();
    test_remove_pointer<void() volatile&>();
    test_remove_pointer<void() volatile&&>();
    test_remove_pointer<void() const volatile>();
    test_remove_pointer<void() const volatile&>();
    test_remove_pointer<void() const volatile&&>();
    test_remove_pointer<void() noexcept>();
    test_remove_pointer<void() & noexcept>();
    test_remove_pointer<void() && noexcept>();
    test_remove_pointer<void() const noexcept>();
    test_remove_pointer<void() const & noexcept>();
    test_remove_pointer<void() const && noexcept>();
    test_remove_pointer<void() volatile noexcept>();
    test_remove_pointer<void() volatile & noexcept>();
    test_remove_pointer<void() volatile && noexcept>();
    test_remove_pointer<void() const volatile noexcept>();
    test_remove_pointer<void() const volatile & noexcept>();
    test_remove_pointer<void() const volatile && noexcept>();

    test_remove_pointer<void(int)>();
    test_remove_pointer<void(int)&>();
    test_remove_pointer<void(int) &&>();
    test_remove_pointer<void(int) const>();
    test_remove_pointer<void(int) const&>();
    test_remove_pointer<void(int) const&&>();
    test_remove_pointer<void(int) volatile>();
    test_remove_pointer<void(int) volatile&>();
    test_remove_pointer<void(int) volatile&&>();
    test_remove_pointer<void(int) const volatile>();
    test_remove_pointer<void(int) const volatile&>();
    test_remove_pointer<void(int) const volatile&&>();
    test_remove_pointer<void(int) noexcept>();
    test_remove_pointer<void(int) & noexcept>();
    test_remove_pointer<void(int) && noexcept>();
    test_remove_pointer<void(int) const noexcept>();
    test_remove_pointer<void(int) const & noexcept>();
    test_remove_pointer<void(int) const && noexcept>();
    test_remove_pointer<void(int) volatile noexcept>();
    test_remove_pointer<void(int) volatile & noexcept>();
    test_remove_pointer<void(int) volatile && noexcept>();
    test_remove_pointer<void(int) const volatile noexcept>();
    test_remove_pointer<void(int) const volatile & noexcept>();
    test_remove_pointer<void(int) const volatile && noexcept>();

    test_remove_pointer<void(...)>();
    test_remove_pointer<void(...)&>();
    test_remove_pointer<void(...) &&>();
    test_remove_pointer<void(...) const>();
    test_remove_pointer<void(...) const&>();
    test_remove_pointer<void(...) const&&>();
    test_remove_pointer<void(...) volatile>();
    test_remove_pointer<void(...) volatile&>();
    test_remove_pointer<void(...) volatile&&>();
    test_remove_pointer<void(...) const volatile>();
    test_remove_pointer<void(...) const volatile&>();
    test_remove_pointer<void(...) const volatile&&>();
    test_remove_pointer<void(...) noexcept>();
    test_remove_pointer<void(...) & noexcept>();
    test_remove_pointer<void(...) && noexcept>();
    test_remove_pointer<void(...) const noexcept>();
    test_remove_pointer<void(...) const & noexcept>();
    test_remove_pointer<void(...) const && noexcept>();
    test_remove_pointer<void(...) volatile noexcept>();
    test_remove_pointer<void(...) volatile & noexcept>();
    test_remove_pointer<void(...) volatile && noexcept>();
    test_remove_pointer<void(...) const volatile noexcept>();
    test_remove_pointer<void(...) const volatile & noexcept>();
    test_remove_pointer<void(...) const volatile && noexcept>();

    test_remove_pointer<void(int, ...)>();
    test_remove_pointer<void(int, ...)&>();
    test_remove_pointer<void(int, ...) &&>();
    test_remove_pointer<void(int, ...) const>();
    test_remove_pointer<void(int, ...) const&>();
    test_remove_pointer<void(int, ...) const&&>();
    test_remove_pointer<void(int, ...) volatile>();
    test_remove_pointer<void(int, ...) volatile&>();
    test_remove_pointer<void(int, ...) volatile&&>();
    test_remove_pointer<void(int, ...) const volatile>();
    test_remove_pointer<void(int, ...) const volatile&>();
    test_remove_pointer<void(int, ...) const volatile&&>();
    test_remove_pointer<void(int, ...) noexcept>();
    test_remove_pointer<void(int, ...) & noexcept>();
    test_remove_pointer<void(int, ...) && noexcept>();
    test_remove_pointer<void(int, ...) const noexcept>();
    test_remove_pointer<void(int, ...) const & noexcept>();
    test_remove_pointer<void(int, ...) const && noexcept>();
    test_remove_pointer<void(int, ...) volatile noexcept>();
    test_remove_pointer<void(int, ...) volatile & noexcept>();
    test_remove_pointer<void(int, ...) volatile && noexcept>();
    test_remove_pointer<void(int, ...) const volatile noexcept>();
    test_remove_pointer<void(int, ...) const volatile & noexcept>();
    test_remove_pointer<void(int, ...) const volatile && noexcept>();

    test_remove_pointer<int()>();
    test_remove_pointer<int()&>();
    test_remove_pointer<int() &&>();
    test_remove_pointer<int() const>();
    test_remove_pointer<int() const&>();
    test_remove_pointer<int() const&&>();
    test_remove_pointer<int() volatile>();
    test_remove_pointer<int() volatile&>();
    test_remove_pointer<int() volatile&&>();
    test_remove_pointer<int() const volatile>();
    test_remove_pointer<int() const volatile&>();
    test_remove_pointer<int() const volatile&&>();
    test_remove_pointer<int() noexcept>();
    test_remove_pointer<int() & noexcept>();
    test_remove_pointer<int() && noexcept>();
    test_remove_pointer<int() const noexcept>();
    test_remove_pointer<int() const & noexcept>();
    test_remove_pointer<int() const && noexcept>();
    test_remove_pointer<int() volatile noexcept>();
    test_remove_pointer<int() volatile & noexcept>();
    test_remove_pointer<int() volatile && noexcept>();
    test_remove_pointer<int() const volatile noexcept>();
    test_remove_pointer<int() const volatile & noexcept>();
    test_remove_pointer<int() const volatile && noexcept>();

    test_remove_pointer<int(int)>();
    test_remove_pointer<int(int)&>();
    test_remove_pointer<int(int) &&>();
    test_remove_pointer<int(int) const>();
    test_remove_pointer<int(int) const&>();
    test_remove_pointer<int(int) const&&>();
    test_remove_pointer<int(int) volatile>();
    test_remove_pointer<int(int) volatile&>();
    test_remove_pointer<int(int) volatile&&>();
    test_remove_pointer<int(int) const volatile>();
    test_remove_pointer<int(int) const volatile&>();
    test_remove_pointer<int(int) const volatile&&>();
    test_remove_pointer<int(int) noexcept>();
    test_remove_pointer<int(int) & noexcept>();
    test_remove_pointer<int(int) && noexcept>();
    test_remove_pointer<int(int) const noexcept>();
    test_remove_pointer<int(int) const & noexcept>();
    test_remove_pointer<int(int) const && noexcept>();
    test_remove_pointer<int(int) volatile noexcept>();
    test_remove_pointer<int(int) volatile & noexcept>();
    test_remove_pointer<int(int) volatile && noexcept>();
    test_remove_pointer<int(int) const volatile noexcept>();
    test_remove_pointer<int(int) const volatile & noexcept>();
    test_remove_pointer<int(int) const volatile && noexcept>();

    test_remove_pointer<int(...)>();
    test_remove_pointer<int(...)&>();
    test_remove_pointer<int(...) &&>();
    test_remove_pointer<int(...) const>();
    test_remove_pointer<int(...) const&>();
    test_remove_pointer<int(...) const&&>();
    test_remove_pointer<int(...) volatile>();
    test_remove_pointer<int(...) volatile&>();
    test_remove_pointer<int(...) volatile&&>();
    test_remove_pointer<int(...) const volatile>();
    test_remove_pointer<int(...) const volatile&>();
    test_remove_pointer<int(...) const volatile&&>();
    test_remove_pointer<int(...) noexcept>();
    test_remove_pointer<int(...) & noexcept>();
    test_remove_pointer<int(...) && noexcept>();
    test_remove_pointer<int(...) const noexcept>();
    test_remove_pointer<int(...) const & noexcept>();
    test_remove_pointer<int(...) const && noexcept>();
    test_remove_pointer<int(...) volatile noexcept>();
    test_remove_pointer<int(...) volatile & noexcept>();
    test_remove_pointer<int(...) volatile && noexcept>();
    test_remove_pointer<int(...) const volatile noexcept>();
    test_remove_pointer<int(...) const volatile & noexcept>();
    test_remove_pointer<int(...) const volatile && noexcept>();

    test_remove_pointer<int(int, ...)>();
    test_remove_pointer<int(int, ...)&>();
    test_remove_pointer<int(int, ...) &&>();
    test_remove_pointer<int(int, ...) const>();
    test_remove_pointer<int(int, ...) const&>();
    test_remove_pointer<int(int, ...) const&&>();
    test_remove_pointer<int(int, ...) volatile>();
    test_remove_pointer<int(int, ...) volatile&>();
    test_remove_pointer<int(int, ...) volatile&&>();
    test_remove_pointer<int(int, ...) const volatile>();
    test_remove_pointer<int(int, ...) const volatile&>();
    test_remove_pointer<int(int, ...) const volatile&&>();
    test_remove_pointer<int(int, ...) noexcept>();
    test_remove_pointer<int(int, ...) & noexcept>();
    test_remove_pointer<int(int, ...) && noexcept>();
    test_remove_pointer<int(int, ...) const noexcept>();
    test_remove_pointer<int(int, ...) const & noexcept>();
    test_remove_pointer<int(int, ...) const && noexcept>();
    test_remove_pointer<int(int, ...) volatile noexcept>();
    test_remove_pointer<int(int, ...) volatile & noexcept>();
    test_remove_pointer<int(int, ...) volatile && noexcept>();
    test_remove_pointer<int(int, ...) const volatile noexcept>();
    test_remove_pointer<int(int, ...) const volatile & noexcept>();
    test_remove_pointer<int(int, ...) const volatile && noexcept>();

    test_remove_pointer<void (*)(), void()>();
    test_remove_pointer<void (*)() noexcept, void() noexcept>();

    test_remove_pointer<void (*)(int), void(int)>();
    test_remove_pointer<void (*)(int) noexcept, void(int) noexcept>();

    test_remove_pointer<void (*)(...), void(...)>();
    test_remove_pointer<void (*)(...) noexcept, void(...) noexcept>();

    test_remove_pointer<void (*)(int, ...), void(int, ...)>();
    test_remove_pointer<void (*)(int, ...) noexcept, void(int, ...) noexcept>();

    test_remove_pointer<int (*)(), int()>();
    test_remove_pointer<int (*)() noexcept, int() noexcept>();

    test_remove_pointer<int (*)(int), int(int)>();
    test_remove_pointer<int (*)(int) noexcept, int(int) noexcept>();

    test_remove_pointer<int (*)(...), int(...)>();
    test_remove_pointer<int (*)(...) noexcept, int(...) noexcept>();

    test_remove_pointer<int (*)(int, ...), int(int, ...)>();
    test_remove_pointer<int (*)(int, ...) noexcept, int(int, ...) noexcept>();

    test_remove_pointer<void (&)()>();
    test_remove_pointer<void (&)() noexcept>();

    test_remove_pointer<void (&)(int)>();
    test_remove_pointer<void (&)(int) noexcept>();

    test_remove_pointer<void (&)(...)>();
    test_remove_pointer<void (&)(...) noexcept>();

    test_remove_pointer<void (&)(int, ...)>();
    test_remove_pointer<void (&)(int, ...) noexcept>();

    test_remove_pointer<int (&)()>();
    test_remove_pointer<int (&)() noexcept>();

    test_remove_pointer<int (&)(int)>();
    test_remove_pointer<int (&)(int) noexcept>();

    test_remove_pointer<int (&)(...)>();
    test_remove_pointer<int (&)(...) noexcept>();

    test_remove_pointer<int (&)(int, ...)>();
    test_remove_pointer<int (&)(int, ...) noexcept>();

    test_remove_pointer<void (&&)()>();
    test_remove_pointer<void (&&)() noexcept>();

    test_remove_pointer<void (&&)(int)>();
    test_remove_pointer<void (&&)(int) noexcept>();

    test_remove_pointer<void (&&)(...)>();
    test_remove_pointer<void (&&)(...) noexcept>();

    test_remove_pointer<void (&&)(int, ...)>();
    test_remove_pointer<void (&&)(int, ...) noexcept>();

    test_remove_pointer<int (&&)()>();
    test_remove_pointer<int (&&)() noexcept>();

    test_remove_pointer<int (&&)(int)>();
    test_remove_pointer<int (&&)(int) noexcept>();

    test_remove_pointer<int (&&)(...)>();
    test_remove_pointer<int (&&)(...) noexcept>();

    test_remove_pointer<int (&&)(int, ...)>();
    test_remove_pointer<int (&&)(int, ...) noexcept>();

    test_remove_pointer<void (class_type::*)()>();
    test_remove_pointer<void (class_type::*)()&>();
    test_remove_pointer<void (class_type::*)() &&>();
    test_remove_pointer<void (class_type::*)() const>();
    test_remove_pointer<void (class_type::*)() const&>();
    test_remove_pointer<void (class_type::*)() const&&>();
    test_remove_pointer<void (class_type::*)() noexcept>();
    test_remove_pointer<void (class_type::*)() & noexcept>();
    test_remove_pointer<void (class_type::*)() && noexcept>();
    test_remove_pointer<void (class_type::*)() const noexcept>();
    test_remove_pointer<void (class_type::*)() const & noexcept>();
    test_remove_pointer<void (class_type::*)() const && noexcept>();

    test_remove_pointer<void (class_type::*)(int)>();
    test_remove_pointer<void (class_type::*)(int)&>();
    test_remove_pointer<void (class_type::*)(int) &&>();
    test_remove_pointer<void (class_type::*)(int) const>();
    test_remove_pointer<void (class_type::*)(int) const&>();
    test_remove_pointer<void (class_type::*)(int) const&&>();
    test_remove_pointer<void (class_type::*)(int) noexcept>();
    test_remove_pointer<void (class_type::*)(int) & noexcept>();
    test_remove_pointer<void (class_type::*)(int) && noexcept>();
    test_remove_pointer<void (class_type::*)(int) const noexcept>();
    test_remove_pointer<void (class_type::*)(int) const & noexcept>();
    test_remove_pointer<void (class_type::*)(int) const && noexcept>();

    test_remove_pointer<void (class_type::*)(...)>();
    test_remove_pointer<void (class_type::*)(...)&>();
    test_remove_pointer<void (class_type::*)(...) &&>();
    test_remove_pointer<void (class_type::*)(...) const>();
    test_remove_pointer<void (class_type::*)(...) const&>();
    test_remove_pointer<void (class_type::*)(...) const&&>();
    test_remove_pointer<void (class_type::*)(...) noexcept>();
    test_remove_pointer<void (class_type::*)(...) & noexcept>();
    test_remove_pointer<void (class_type::*)(...) && noexcept>();
    test_remove_pointer<void (class_type::*)(...) const noexcept>();
    test_remove_pointer<void (class_type::*)(...) const & noexcept>();
    test_remove_pointer<void (class_type::*)(...) const && noexcept>();

    test_remove_pointer<void (class_type::*)(int, ...)>();
    test_remove_pointer<void (class_type::*)(int, ...)&>();
    test_remove_pointer<void (class_type::*)(int, ...) &&>();
    test_remove_pointer<void (class_type::*)(int, ...) const>();
    test_remove_pointer<void (class_type::*)(int, ...) const&>();
    test_remove_pointer<void (class_type::*)(int, ...) const&&>();
    test_remove_pointer<void (class_type::*)(int, ...) noexcept>();
    test_remove_pointer<void (class_type::*)(int, ...) & noexcept>();
    test_remove_pointer<void (class_type::*)(int, ...) && noexcept>();
    test_remove_pointer<void (class_type::*)(int, ...) const noexcept>();
    test_remove_pointer<void (class_type::*)(int, ...) const & noexcept>();
    test_remove_pointer<void (class_type::*)(int, ...) const && noexcept>();

    test_remove_pointer<int (class_type::*)()>();
    test_remove_pointer<int (class_type::*)()&>();
    test_remove_pointer<int (class_type::*)() &&>();
    test_remove_pointer<int (class_type::*)() const>();
    test_remove_pointer<int (class_type::*)() const&>();
    test_remove_pointer<int (class_type::*)() const&&>();
    test_remove_pointer<int (class_type::*)() noexcept>();
    test_remove_pointer<int (class_type::*)() & noexcept>();
    test_remove_pointer<int (class_type::*)() && noexcept>();
    test_remove_pointer<int (class_type::*)() const noexcept>();
    test_remove_pointer<int (class_type::*)() const & noexcept>();
    test_remove_pointer<int (class_type::*)() const && noexcept>();

    test_remove_pointer<int (class_type::*)(int)>();
    test_remove_pointer<int (class_type::*)(int)&>();
    test_remove_pointer<int (class_type::*)(int) &&>();
    test_remove_pointer<int (class_type::*)(int) const>();
    test_remove_pointer<int (class_type::*)(int) const&>();
    test_remove_pointer<int (class_type::*)(int) const&&>();
    test_remove_pointer<int (class_type::*)(int) noexcept>();
    test_remove_pointer<int (class_type::*)(int) & noexcept>();
    test_remove_pointer<int (class_type::*)(int) && noexcept>();
    test_remove_pointer<int (class_type::*)(int) const noexcept>();
    test_remove_pointer<int (class_type::*)(int) const & noexcept>();
    test_remove_pointer<int (class_type::*)(int) const && noexcept>();

    test_remove_pointer<int (class_type::*)(...)>();
    test_remove_pointer<int (class_type::*)(...)&>();
    test_remove_pointer<int (class_type::*)(...) &&>();
    test_remove_pointer<int (class_type::*)(...) const>();
    test_remove_pointer<int (class_type::*)(...) const&>();
    test_remove_pointer<int (class_type::*)(...) const&&>();
    test_remove_pointer<int (class_type::*)(...) noexcept>();
    test_remove_pointer<int (class_type::*)(...) & noexcept>();
    test_remove_pointer<int (class_type::*)(...) && noexcept>();
    test_remove_pointer<int (class_type::*)(...) const noexcept>();
    test_remove_pointer<int (class_type::*)(...) const & noexcept>();
    test_remove_pointer<int (class_type::*)(...) const && noexcept>();

    test_remove_pointer<int (class_type::*)(int, ...)>();
    test_remove_pointer<int (class_type::*)(int, ...)&>();
    test_remove_pointer<int (class_type::*)(int, ...) &&>();
    test_remove_pointer<int (class_type::*)(int, ...) const>();
    test_remove_pointer<int (class_type::*)(int, ...) const&>();
    test_remove_pointer<int (class_type::*)(int, ...) const&&>();
    test_remove_pointer<int (class_type::*)(int, ...) noexcept>();
    test_remove_pointer<int (class_type::*)(int, ...) & noexcept>();
    test_remove_pointer<int (class_type::*)(int, ...) && noexcept>();
    test_remove_pointer<int (class_type::*)(int, ...) const noexcept>();
    test_remove_pointer<int (class_type::*)(int, ...) const & noexcept>();
    test_remove_pointer<int (class_type::*)(int, ...) const && noexcept>();
}
