#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/remove_reference.hpp>
#include <type_traits>
#include <vector>

template <typename TypeT, typename ExpectedT>
void test_remove_reference_impl()
{
    CHECK_SAME_TYPE(typename phi::remove_reference<TypeT>::type, ExpectedT);
#if PHI_HAS_FEATURE_ALIAS_TEMPLATES()
    CHECK_SAME_TYPE(phi::remove_reference_t<TypeT>, ExpectedT);
#endif

    // Standard compatibility
    CHECK_SAME_TYPE(typename std::remove_reference<TypeT>::type, ExpectedT);
}

template <typename TypeT, typename ExpectedT = TypeT>
void test_remove_reference()
{
    test_remove_reference_impl<TypeT, ExpectedT>();
    test_remove_reference_impl<const TypeT, const ExpectedT>();
    test_remove_reference_impl<volatile TypeT, volatile ExpectedT>();
    test_remove_reference_impl<const volatile TypeT, const volatile ExpectedT>();
}

template <typename TypeT, typename ExpectedT>
void test_remove_reference_ref()
{
    test_remove_reference_impl<TypeT, ExpectedT>();
}

TEST_CASE("remove_reference")
{
    test_remove_reference<void>();
    test_remove_reference<phi::nullptr_t>();
    test_remove_reference<bool>();
    test_remove_reference<char>();
    test_remove_reference<signed char>();
    test_remove_reference<unsigned char>();
    test_remove_reference<short>();
    test_remove_reference<unsigned short>();
    test_remove_reference<int>();
    test_remove_reference<unsigned int>();
    test_remove_reference<long>();
    test_remove_reference<unsigned long>();
    test_remove_reference<long long>();
    test_remove_reference<unsigned long long>();
    test_remove_reference<float>();
    test_remove_reference<double>();
    test_remove_reference<long double>();
    test_remove_reference<char8_t>();
    test_remove_reference<char16_t>();
    test_remove_reference<char32_t>();
    test_remove_reference<wchar_t>();

    test_remove_reference<phi::boolean>();
    test_remove_reference<phi::integer<signed char>>();
    test_remove_reference<phi::integer<unsigned char>>();
    test_remove_reference<phi::integer<short>>();
    test_remove_reference<phi::integer<unsigned short>>();
    test_remove_reference<phi::integer<int>>();
    test_remove_reference<phi::integer<unsigned int>>();
    test_remove_reference<phi::integer<long>>();
    test_remove_reference<phi::integer<unsigned long>>();
    test_remove_reference<phi::integer<long long>>();
    test_remove_reference<phi::integer<unsigned long long>>();
    test_remove_reference<phi::floating_point<float>>();
    test_remove_reference<phi::floating_point<double>>();
    test_remove_reference<phi::floating_point<long double>>();

    test_remove_reference<std::vector<int>>();
    test_remove_reference<phi::scope_ptr<int>>();

    test_remove_reference_ref<int&, int>();
    test_remove_reference_ref<const int&, const int>();
    test_remove_reference_ref<volatile int&, volatile int>();
    test_remove_reference_ref<const volatile int&, const volatile int>();
    test_remove_reference_ref<int&&, int>();
    test_remove_reference_ref<const int&&, const int>();
    test_remove_reference_ref<volatile int&&, volatile int>();
    test_remove_reference_ref<const volatile int&&, const volatile int>();
    test_remove_reference<int*>();
    test_remove_reference<const int*>();
    test_remove_reference<volatile int*>();
    test_remove_reference<const volatile int*>();
    test_remove_reference<int**>();
    test_remove_reference<const int**>();
    test_remove_reference<volatile int**>();
    test_remove_reference<const volatile int**>();
    test_remove_reference_ref<int*&, int*>();
    test_remove_reference_ref<const int*&, const int*>();
    test_remove_reference_ref<volatile int*&, volatile int*>();
    test_remove_reference_ref<const volatile int*&, const volatile int*>();
    test_remove_reference_ref<int*&&, int*>();
    test_remove_reference_ref<const int*&&, const int*>();
    test_remove_reference_ref<volatile int*&&, volatile int*>();
    test_remove_reference_ref<const volatile int*&&, const volatile int*>();
    test_remove_reference<void*>();
    test_remove_reference<char[3]>();
    test_remove_reference<char[]>();
    test_remove_reference<char* [3]>();
    test_remove_reference<char*[]>();
    test_remove_reference<int(*)[3]>();
    test_remove_reference<int(*)[]>();
    test_remove_reference_ref<int(&)[3], int[3]>();
    test_remove_reference_ref<int(&)[], int[]>();
    test_remove_reference_ref<int(&&)[3], int[3]>();
    test_remove_reference_ref<int(&&)[], int[]>();
    test_remove_reference<char[3][2]>();
    test_remove_reference<char[][2]>();
    test_remove_reference<char* [3][2]>();
    test_remove_reference<char*[][2]>();
    test_remove_reference<int(*)[3][2]>();
    test_remove_reference<int(*)[][2]>();
    test_remove_reference_ref<int(&)[3][2], int[3][2]>();
    test_remove_reference_ref<int(&)[][2], int[][2]>();
    test_remove_reference_ref<int(&&)[3][2], int[3][2]>();
    test_remove_reference_ref<int(&&)[][2], int[][2]>();
    test_remove_reference<class_type>();
    test_remove_reference<class_type[]>();
    test_remove_reference<class_type[2]>();
    test_remove_reference<template_type<void>>();
    test_remove_reference<template_type<int>>();
    test_remove_reference<template_type<class_type>>();
    test_remove_reference<template_type<incomplete_type>>();
    test_remove_reference<variadic_template<>>();
    test_remove_reference<variadic_template<void>>();
    test_remove_reference<variadic_template<int>>();
    test_remove_reference<variadic_template<class_type>>();
    test_remove_reference<variadic_template<incomplete_type>>();
    test_remove_reference<variadic_template<int, void, class_type, volatile char[]>>();
    test_remove_reference<public_derived_from<base>>();
    test_remove_reference<public_derived_from<derived>>();
    test_remove_reference<public_derived_from<class_type>>();
    test_remove_reference<private_derived_from<base>>();
    test_remove_reference<private_derived_from<derived>>();
    test_remove_reference<private_derived_from<class_type>>();
    test_remove_reference<protected_derived_from<base>>();
    test_remove_reference<protected_derived_from<derived>>();
    test_remove_reference<protected_derived_from<class_type>>();
    test_remove_reference<union_type>();
    test_remove_reference<non_empty_union>();
    test_remove_reference<empty>();
    test_remove_reference<not_empty>();
    test_remove_reference<bit_zero>();
    test_remove_reference<bit_one>();
    test_remove_reference<base>();
    test_remove_reference<derived>();
    test_remove_reference<abstract>();
    test_remove_reference<public_abstract>();
    test_remove_reference<private_abstract>();
    test_remove_reference<protected_abstract>();
    test_remove_reference<abstract_template<int>>();
    test_remove_reference<abstract_template<double>>();
    test_remove_reference<abstract_template<class_type>>();
    test_remove_reference<abstract_template<incomplete_type>>();
    test_remove_reference<final_type>();
    test_remove_reference<public_destructor>();
    test_remove_reference<protected_destructor>();
    test_remove_reference<private_destructor>();
    test_remove_reference<virtual_public_destructor>();
    test_remove_reference<virtual_protected_destructor>();
    test_remove_reference<virtual_private_destructor>();
    test_remove_reference<pure_public_destructor>();
    test_remove_reference<pure_protected_destructor>();
    test_remove_reference<pure_private_destructor>();
    test_remove_reference<deleted_public_destructor>();
    test_remove_reference<deleted_protected_destructor>();
    test_remove_reference<deleted_private_destructor>();
    test_remove_reference<deleted_virtual_public_destructor>();
    test_remove_reference<deleted_virtual_protected_destructor>();
    test_remove_reference<deleted_virtual_private_destructor>();
    test_remove_reference<Enum>();
    test_remove_reference<EnumSigned>();
    test_remove_reference<EnumUnsigned>();
    test_remove_reference<EnumClass>();
    test_remove_reference<EnumStruct>();
    test_remove_reference<function_type>();
    test_remove_reference<function_ptr>();
    test_remove_reference<member_object_ptr>();
    test_remove_reference<member_function_ptr>();
    test_remove_reference<incomplete_type>();
    test_remove_reference<incomplete_template<void>>();
    test_remove_reference<incomplete_template<int>>();
    test_remove_reference<incomplete_template<class_type>>();
    test_remove_reference<incomplete_template<incomplete_type>>();
    test_remove_reference<incomplete_variadic_template<>>();
    test_remove_reference<incomplete_variadic_template<void>>();
    test_remove_reference<incomplete_variadic_template<int>>();
    test_remove_reference<incomplete_variadic_template<class_type>>();
    test_remove_reference<incomplete_variadic_template<incomplete_type>>();
    test_remove_reference<incomplete_variadic_template<int, void, class_type, volatile char[]>>();
    test_remove_reference<int class_type::*>();
    test_remove_reference<float class_type::*>();
    test_remove_reference<void * class_type::*>();
    test_remove_reference<int * class_type::*>();
    test_remove_reference_ref<int class_type::*&, int class_type::*>();
    test_remove_reference_ref<float class_type::*&, float class_type::*>();
    test_remove_reference_ref<void * class_type::*&, void * class_type::*>();
    test_remove_reference_ref<int * class_type::*&, int * class_type::*>();
    test_remove_reference_ref<int class_type::*&&, int class_type::*>();
    test_remove_reference_ref<float class_type::*&&, float class_type::*>();
    test_remove_reference_ref<void * class_type::*&&, void * class_type::*>();
    test_remove_reference_ref<int * class_type::*&&, int * class_type::*>();
    test_remove_reference<int class_type::*const>();
    test_remove_reference<float class_type::*const>();
    test_remove_reference<void * class_type::*const>();
    test_remove_reference_ref<int class_type::*const&, int class_type::*const>();
    test_remove_reference_ref<float class_type::*const&, float class_type::*const>();
    test_remove_reference_ref<void * class_type::*const&, void * class_type::*const>();
    test_remove_reference_ref<int class_type::*const&&, int class_type::*const>();
    test_remove_reference_ref<float class_type::*const&&, float class_type::*const>();
    test_remove_reference_ref<void * class_type::*const&&, void * class_type::*const>();
    test_remove_reference<int class_type::*volatile>();
    test_remove_reference<float class_type::*volatile>();
    test_remove_reference<void * class_type::*volatile>();
    test_remove_reference_ref<int class_type::*volatile&, int class_type::*volatile>();
    test_remove_reference_ref<float class_type::*volatile&, float class_type::*volatile>();
    test_remove_reference_ref<void * class_type::*volatile&, void * class_type::*volatile>();
    test_remove_reference_ref<int class_type::*volatile&&, int class_type::*volatile>();
    test_remove_reference_ref<float class_type::*volatile&&, float class_type::*volatile>();
    test_remove_reference_ref<void * class_type::*volatile&&, void * class_type::*volatile>();
    test_remove_reference<int class_type::*const volatile>();
    test_remove_reference<float class_type::*const volatile>();
    test_remove_reference<void * class_type::*const volatile>();
    test_remove_reference_ref<int class_type::*const volatile&, int class_type::*const volatile>();
    test_remove_reference_ref<float class_type::*const volatile&,
                              float class_type::*const volatile>();
    test_remove_reference_ref<void * class_type::*const volatile&,
                              void * class_type::*const volatile>();
    test_remove_reference_ref<int class_type::*const volatile&&, int class_type::*const volatile>();
    test_remove_reference_ref<float class_type::*const volatile&&,
                              float class_type::*const volatile>();
    test_remove_reference_ref<void * class_type::*const volatile&&,
                              void * class_type::*const volatile>();
    test_remove_reference<non_copyable>();
    test_remove_reference<non_moveable>();
    test_remove_reference<non_constructible>();
    test_remove_reference<tracked>();
    test_remove_reference<trap_constructible>();
    test_remove_reference<trap_implicit_conversion>();
    test_remove_reference<trap_comma>();
    test_remove_reference<trap_call>();
    test_remove_reference<trap_self_assign>();
    test_remove_reference<trap_deref>();
    test_remove_reference<trap_array_subscript>();

    test_remove_reference<void()>();
    test_remove_reference<void()&>();
    test_remove_reference<void() &&>();
    test_remove_reference<void() const>();
    test_remove_reference<void() const&>();
    test_remove_reference<void() const&&>();
    test_remove_reference<void() volatile>();
    test_remove_reference<void() volatile&>();
    test_remove_reference<void() volatile&&>();
    test_remove_reference<void() const volatile>();
    test_remove_reference<void() const volatile&>();
    test_remove_reference<void() const volatile&&>();
    test_remove_reference<void() noexcept>();
    test_remove_reference<void() & noexcept>();
    test_remove_reference<void() && noexcept>();
    test_remove_reference<void() const noexcept>();
    test_remove_reference<void() const & noexcept>();
    test_remove_reference<void() const && noexcept>();
    test_remove_reference<void() volatile noexcept>();
    test_remove_reference<void() volatile & noexcept>();
    test_remove_reference<void() volatile && noexcept>();
    test_remove_reference<void() const volatile noexcept>();
    test_remove_reference<void() const volatile & noexcept>();
    test_remove_reference<void() const volatile && noexcept>();

    test_remove_reference<void(int)>();
    test_remove_reference<void(int)&>();
    test_remove_reference<void(int) &&>();
    test_remove_reference<void(int) const>();
    test_remove_reference<void(int) const&>();
    test_remove_reference<void(int) const&&>();
    test_remove_reference<void(int) volatile>();
    test_remove_reference<void(int) volatile&>();
    test_remove_reference<void(int) volatile&&>();
    test_remove_reference<void(int) const volatile>();
    test_remove_reference<void(int) const volatile&>();
    test_remove_reference<void(int) const volatile&&>();
    test_remove_reference<void(int) noexcept>();
    test_remove_reference<void(int) & noexcept>();
    test_remove_reference<void(int) && noexcept>();
    test_remove_reference<void(int) const noexcept>();
    test_remove_reference<void(int) const & noexcept>();
    test_remove_reference<void(int) const && noexcept>();
    test_remove_reference<void(int) volatile noexcept>();
    test_remove_reference<void(int) volatile & noexcept>();
    test_remove_reference<void(int) volatile && noexcept>();
    test_remove_reference<void(int) const volatile noexcept>();
    test_remove_reference<void(int) const volatile & noexcept>();
    test_remove_reference<void(int) const volatile && noexcept>();

    test_remove_reference<void(...)>();
    test_remove_reference<void(...)&>();
    test_remove_reference<void(...) &&>();
    test_remove_reference<void(...) const>();
    test_remove_reference<void(...) const&>();
    test_remove_reference<void(...) const&&>();
    test_remove_reference<void(...) volatile>();
    test_remove_reference<void(...) volatile&>();
    test_remove_reference<void(...) volatile&&>();
    test_remove_reference<void(...) const volatile>();
    test_remove_reference<void(...) const volatile&>();
    test_remove_reference<void(...) const volatile&&>();
    test_remove_reference<void(...) noexcept>();
    test_remove_reference<void(...) & noexcept>();
    test_remove_reference<void(...) && noexcept>();
    test_remove_reference<void(...) const noexcept>();
    test_remove_reference<void(...) const & noexcept>();
    test_remove_reference<void(...) const && noexcept>();
    test_remove_reference<void(...) volatile noexcept>();
    test_remove_reference<void(...) volatile & noexcept>();
    test_remove_reference<void(...) volatile && noexcept>();
    test_remove_reference<void(...) const volatile noexcept>();
    test_remove_reference<void(...) const volatile & noexcept>();
    test_remove_reference<void(...) const volatile && noexcept>();

    test_remove_reference<void(int, ...)>();
    test_remove_reference<void(int, ...)&>();
    test_remove_reference<void(int, ...) &&>();
    test_remove_reference<void(int, ...) const>();
    test_remove_reference<void(int, ...) const&>();
    test_remove_reference<void(int, ...) const&&>();
    test_remove_reference<void(int, ...) volatile>();
    test_remove_reference<void(int, ...) volatile&>();
    test_remove_reference<void(int, ...) volatile&&>();
    test_remove_reference<void(int, ...) const volatile>();
    test_remove_reference<void(int, ...) const volatile&>();
    test_remove_reference<void(int, ...) const volatile&&>();
    test_remove_reference<void(int, ...) noexcept>();
    test_remove_reference<void(int, ...) & noexcept>();
    test_remove_reference<void(int, ...) && noexcept>();
    test_remove_reference<void(int, ...) const noexcept>();
    test_remove_reference<void(int, ...) const & noexcept>();
    test_remove_reference<void(int, ...) const && noexcept>();
    test_remove_reference<void(int, ...) volatile noexcept>();
    test_remove_reference<void(int, ...) volatile & noexcept>();
    test_remove_reference<void(int, ...) volatile && noexcept>();
    test_remove_reference<void(int, ...) const volatile noexcept>();
    test_remove_reference<void(int, ...) const volatile & noexcept>();
    test_remove_reference<void(int, ...) const volatile && noexcept>();

    test_remove_reference<int()>();
    test_remove_reference<int()&>();
    test_remove_reference<int() &&>();
    test_remove_reference<int() const>();
    test_remove_reference<int() const&>();
    test_remove_reference<int() const&&>();
    test_remove_reference<int() volatile>();
    test_remove_reference<int() volatile&>();
    test_remove_reference<int() volatile&&>();
    test_remove_reference<int() const volatile>();
    test_remove_reference<int() const volatile&>();
    test_remove_reference<int() const volatile&&>();
    test_remove_reference<int() noexcept>();
    test_remove_reference<int() & noexcept>();
    test_remove_reference<int() && noexcept>();
    test_remove_reference<int() const noexcept>();
    test_remove_reference<int() const & noexcept>();
    test_remove_reference<int() const && noexcept>();
    test_remove_reference<int() volatile noexcept>();
    test_remove_reference<int() volatile & noexcept>();
    test_remove_reference<int() volatile && noexcept>();
    test_remove_reference<int() const volatile noexcept>();
    test_remove_reference<int() const volatile & noexcept>();
    test_remove_reference<int() const volatile && noexcept>();

    test_remove_reference<int(int)>();
    test_remove_reference<int(int)&>();
    test_remove_reference<int(int) &&>();
    test_remove_reference<int(int) const>();
    test_remove_reference<int(int) const&>();
    test_remove_reference<int(int) const&&>();
    test_remove_reference<int(int) volatile>();
    test_remove_reference<int(int) volatile&>();
    test_remove_reference<int(int) volatile&&>();
    test_remove_reference<int(int) const volatile>();
    test_remove_reference<int(int) const volatile&>();
    test_remove_reference<int(int) const volatile&&>();
    test_remove_reference<int(int) noexcept>();
    test_remove_reference<int(int) & noexcept>();
    test_remove_reference<int(int) && noexcept>();
    test_remove_reference<int(int) const noexcept>();
    test_remove_reference<int(int) const & noexcept>();
    test_remove_reference<int(int) const && noexcept>();
    test_remove_reference<int(int) volatile noexcept>();
    test_remove_reference<int(int) volatile & noexcept>();
    test_remove_reference<int(int) volatile && noexcept>();
    test_remove_reference<int(int) const volatile noexcept>();
    test_remove_reference<int(int) const volatile & noexcept>();
    test_remove_reference<int(int) const volatile && noexcept>();

    test_remove_reference<int(...)>();
    test_remove_reference<int(...)&>();
    test_remove_reference<int(...) &&>();
    test_remove_reference<int(...) const>();
    test_remove_reference<int(...) const&>();
    test_remove_reference<int(...) const&&>();
    test_remove_reference<int(...) volatile>();
    test_remove_reference<int(...) volatile&>();
    test_remove_reference<int(...) volatile&&>();
    test_remove_reference<int(...) const volatile>();
    test_remove_reference<int(...) const volatile&>();
    test_remove_reference<int(...) const volatile&&>();
    test_remove_reference<int(...) noexcept>();
    test_remove_reference<int(...) & noexcept>();
    test_remove_reference<int(...) && noexcept>();
    test_remove_reference<int(...) const noexcept>();
    test_remove_reference<int(...) const & noexcept>();
    test_remove_reference<int(...) const && noexcept>();
    test_remove_reference<int(...) volatile noexcept>();
    test_remove_reference<int(...) volatile & noexcept>();
    test_remove_reference<int(...) volatile && noexcept>();
    test_remove_reference<int(...) const volatile noexcept>();
    test_remove_reference<int(...) const volatile & noexcept>();
    test_remove_reference<int(...) const volatile && noexcept>();

    test_remove_reference<int(int, ...)>();
    test_remove_reference<int(int, ...)&>();
    test_remove_reference<int(int, ...) &&>();
    test_remove_reference<int(int, ...) const>();
    test_remove_reference<int(int, ...) const&>();
    test_remove_reference<int(int, ...) const&&>();
    test_remove_reference<int(int, ...) volatile>();
    test_remove_reference<int(int, ...) volatile&>();
    test_remove_reference<int(int, ...) volatile&&>();
    test_remove_reference<int(int, ...) const volatile>();
    test_remove_reference<int(int, ...) const volatile&>();
    test_remove_reference<int(int, ...) const volatile&&>();
    test_remove_reference<int(int, ...) noexcept>();
    test_remove_reference<int(int, ...) & noexcept>();
    test_remove_reference<int(int, ...) && noexcept>();
    test_remove_reference<int(int, ...) const noexcept>();
    test_remove_reference<int(int, ...) const & noexcept>();
    test_remove_reference<int(int, ...) const && noexcept>();
    test_remove_reference<int(int, ...) volatile noexcept>();
    test_remove_reference<int(int, ...) volatile & noexcept>();
    test_remove_reference<int(int, ...) volatile && noexcept>();
    test_remove_reference<int(int, ...) const volatile noexcept>();
    test_remove_reference<int(int, ...) const volatile & noexcept>();
    test_remove_reference<int(int, ...) const volatile && noexcept>();

    test_remove_reference<void (*)()>();
    test_remove_reference<void (*)() noexcept>();

    test_remove_reference<void (*)(int)>();
    test_remove_reference<void (*)(int) noexcept>();

    test_remove_reference<void (*)(...)>();
    test_remove_reference<void (*)(...) noexcept>();

    test_remove_reference<void (*)(int, ...)>();
    test_remove_reference<void (*)(int, ...) noexcept>();

    test_remove_reference<int (*)()>();
    test_remove_reference<int (*)() noexcept>();

    test_remove_reference<int (*)(int)>();
    test_remove_reference<int (*)(int) noexcept>();

    test_remove_reference<int (*)(...)>();
    test_remove_reference<int (*)(...) noexcept>();

    test_remove_reference<int (*)(int, ...)>();
    test_remove_reference<int (*)(int, ...) noexcept>();

    test_remove_reference_ref<void (&)(), void()>();
    test_remove_reference_ref<void (&)() noexcept, void() noexcept>();

    test_remove_reference_ref<void (&)(int), void(int)>();
    test_remove_reference_ref<void (&)(int) noexcept, void(int) noexcept>();

    test_remove_reference_ref<void (&)(...), void(...)>();
    test_remove_reference_ref<void (&)(...) noexcept, void(...) noexcept>();

    test_remove_reference_ref<void (&)(int, ...), void(int, ...)>();
    test_remove_reference_ref<void (&)(int, ...) noexcept, void(int, ...) noexcept>();

    test_remove_reference_ref<int (&)(), int()>();
    test_remove_reference_ref<int (&)() noexcept, int() noexcept>();

    test_remove_reference_ref<int (&)(int), int(int)>();
    test_remove_reference_ref<int (&)(int) noexcept, int(int) noexcept>();

    test_remove_reference_ref<int (&)(...), int(...)>();
    test_remove_reference_ref<int (&)(...) noexcept, int(...) noexcept>();

    test_remove_reference_ref<int (&)(int, ...), int(int, ...)>();
    test_remove_reference_ref<int (&)(int, ...) noexcept, int(int, ...) noexcept>();

    test_remove_reference_ref<void (&&)(), void()>();
    test_remove_reference_ref<void (&&)() noexcept, void() noexcept>();

    test_remove_reference_ref<void (&&)(int), void(int)>();
    test_remove_reference_ref<void (&&)(int) noexcept, void(int) noexcept>();

    test_remove_reference_ref<void (&&)(...), void(...)>();
    test_remove_reference_ref<void (&&)(...) noexcept, void(...) noexcept>();

    test_remove_reference_ref<void (&&)(int, ...), void(int, ...)>();
    test_remove_reference_ref<void (&&)(int, ...) noexcept, void(int, ...) noexcept>();

    test_remove_reference_ref<int (&&)(), int()>();
    test_remove_reference_ref<int (&&)() noexcept, int() noexcept>();

    test_remove_reference_ref<int (&&)(int), int(int)>();
    test_remove_reference_ref<int (&&)(int) noexcept, int(int) noexcept>();

    test_remove_reference_ref<int (&&)(...), int(...)>();
    test_remove_reference_ref<int (&&)(...) noexcept, int(...) noexcept>();

    test_remove_reference_ref<int (&&)(int, ...), int(int, ...)>();
    test_remove_reference_ref<int (&&)(int, ...) noexcept, int(int, ...) noexcept>();

    test_remove_reference<void (class_type::*)()>();
    test_remove_reference<void (class_type::*)()&>();
    test_remove_reference<void (class_type::*)() &&>();
    test_remove_reference<void (class_type::*)() const>();
    test_remove_reference<void (class_type::*)() const&>();
    test_remove_reference<void (class_type::*)() const&&>();
    test_remove_reference<void (class_type::*)() noexcept>();
    test_remove_reference<void (class_type::*)() & noexcept>();
    test_remove_reference<void (class_type::*)() && noexcept>();
    test_remove_reference<void (class_type::*)() const noexcept>();
    test_remove_reference<void (class_type::*)() const & noexcept>();
    test_remove_reference<void (class_type::*)() const && noexcept>();

    test_remove_reference<void (class_type::*)(int)>();
    test_remove_reference<void (class_type::*)(int)&>();
    test_remove_reference<void (class_type::*)(int) &&>();
    test_remove_reference<void (class_type::*)(int) const>();
    test_remove_reference<void (class_type::*)(int) const&>();
    test_remove_reference<void (class_type::*)(int) const&&>();
    test_remove_reference<void (class_type::*)(int) noexcept>();
    test_remove_reference<void (class_type::*)(int) & noexcept>();
    test_remove_reference<void (class_type::*)(int) && noexcept>();
    test_remove_reference<void (class_type::*)(int) const noexcept>();
    test_remove_reference<void (class_type::*)(int) const & noexcept>();
    test_remove_reference<void (class_type::*)(int) const && noexcept>();

    test_remove_reference<void (class_type::*)(...)>();
    test_remove_reference<void (class_type::*)(...)&>();
    test_remove_reference<void (class_type::*)(...) &&>();
    test_remove_reference<void (class_type::*)(...) const>();
    test_remove_reference<void (class_type::*)(...) const&>();
    test_remove_reference<void (class_type::*)(...) const&&>();
    test_remove_reference<void (class_type::*)(...) noexcept>();
    test_remove_reference<void (class_type::*)(...) & noexcept>();
    test_remove_reference<void (class_type::*)(...) && noexcept>();
    test_remove_reference<void (class_type::*)(...) const noexcept>();
    test_remove_reference<void (class_type::*)(...) const & noexcept>();
    test_remove_reference<void (class_type::*)(...) const && noexcept>();

    test_remove_reference<void (class_type::*)(int, ...)>();
    test_remove_reference<void (class_type::*)(int, ...)&>();
    test_remove_reference<void (class_type::*)(int, ...) &&>();
    test_remove_reference<void (class_type::*)(int, ...) const>();
    test_remove_reference<void (class_type::*)(int, ...) const&>();
    test_remove_reference<void (class_type::*)(int, ...) const&&>();
    test_remove_reference<void (class_type::*)(int, ...) noexcept>();
    test_remove_reference<void (class_type::*)(int, ...) & noexcept>();
    test_remove_reference<void (class_type::*)(int, ...) && noexcept>();
    test_remove_reference<void (class_type::*)(int, ...) const noexcept>();
    test_remove_reference<void (class_type::*)(int, ...) const & noexcept>();
    test_remove_reference<void (class_type::*)(int, ...) const && noexcept>();

    test_remove_reference<int (class_type::*)()>();
    test_remove_reference<int (class_type::*)()&>();
    test_remove_reference<int (class_type::*)() &&>();
    test_remove_reference<int (class_type::*)() const>();
    test_remove_reference<int (class_type::*)() const&>();
    test_remove_reference<int (class_type::*)() const&&>();
    test_remove_reference<int (class_type::*)() noexcept>();
    test_remove_reference<int (class_type::*)() & noexcept>();
    test_remove_reference<int (class_type::*)() && noexcept>();
    test_remove_reference<int (class_type::*)() const noexcept>();
    test_remove_reference<int (class_type::*)() const & noexcept>();
    test_remove_reference<int (class_type::*)() const && noexcept>();

    test_remove_reference<int (class_type::*)(int)>();
    test_remove_reference<int (class_type::*)(int)&>();
    test_remove_reference<int (class_type::*)(int) &&>();
    test_remove_reference<int (class_type::*)(int) const>();
    test_remove_reference<int (class_type::*)(int) const&>();
    test_remove_reference<int (class_type::*)(int) const&&>();
    test_remove_reference<int (class_type::*)(int) noexcept>();
    test_remove_reference<int (class_type::*)(int) & noexcept>();
    test_remove_reference<int (class_type::*)(int) && noexcept>();
    test_remove_reference<int (class_type::*)(int) const noexcept>();
    test_remove_reference<int (class_type::*)(int) const & noexcept>();
    test_remove_reference<int (class_type::*)(int) const && noexcept>();

    test_remove_reference<int (class_type::*)(...)>();
    test_remove_reference<int (class_type::*)(...)&>();
    test_remove_reference<int (class_type::*)(...) &&>();
    test_remove_reference<int (class_type::*)(...) const>();
    test_remove_reference<int (class_type::*)(...) const&>();
    test_remove_reference<int (class_type::*)(...) const&&>();
    test_remove_reference<int (class_type::*)(...) noexcept>();
    test_remove_reference<int (class_type::*)(...) & noexcept>();
    test_remove_reference<int (class_type::*)(...) && noexcept>();
    test_remove_reference<int (class_type::*)(...) const noexcept>();
    test_remove_reference<int (class_type::*)(...) const & noexcept>();
    test_remove_reference<int (class_type::*)(...) const && noexcept>();

    test_remove_reference<int (class_type::*)(int, ...)>();
    test_remove_reference<int (class_type::*)(int, ...)&>();
    test_remove_reference<int (class_type::*)(int, ...) &&>();
    test_remove_reference<int (class_type::*)(int, ...) const>();
    test_remove_reference<int (class_type::*)(int, ...) const&>();
    test_remove_reference<int (class_type::*)(int, ...) const&&>();
    test_remove_reference<int (class_type::*)(int, ...) noexcept>();
    test_remove_reference<int (class_type::*)(int, ...) & noexcept>();
    test_remove_reference<int (class_type::*)(int, ...) && noexcept>();
    test_remove_reference<int (class_type::*)(int, ...) const noexcept>();
    test_remove_reference<int (class_type::*)(int, ...) const & noexcept>();
    test_remove_reference<int (class_type::*)(int, ...) const && noexcept>();
}
