#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/remove_const.hpp>
#include <type_traits>
#include <vector>

template <typename TypeT, typename ExpectedT>
void test_remove_const_impl()
{
    CHECK_SAME_TYPE(typename phi::remove_const<TypeT>::type, ExpectedT);
    CHECK_SAME_TYPE(phi::remove_const_t<TypeT>, ExpectedT);

    // Standard compatibility
    CHECK_SAME_TYPE(typename std::remove_const<TypeT>::type, ExpectedT);
}

template <typename TypeT, typename ExpectedT = TypeT>
void test_remove_const()
{
    test_remove_const_impl<TypeT, ExpectedT>();
    test_remove_const_impl<const TypeT, ExpectedT>();
    test_remove_const_impl<volatile TypeT, volatile ExpectedT>();
    test_remove_const_impl<const volatile TypeT, volatile ExpectedT>();
}

TEST_CASE("remove_const")
{
    test_remove_const<void>();
    test_remove_const<phi::nullptr_t>();
    test_remove_const<bool>();
    test_remove_const<char>();
    test_remove_const<signed char>();
    test_remove_const<unsigned char>();
    test_remove_const<short>();
    test_remove_const<unsigned short>();
    test_remove_const<int>();
    test_remove_const<unsigned int>();
    test_remove_const<long>();
    test_remove_const<unsigned long>();
    test_remove_const<long long>();
    test_remove_const<unsigned long long>();
    test_remove_const<float>();
    test_remove_const<double>();
    test_remove_const<long double>();
    test_remove_const<char8_t>();
    test_remove_const<char16_t>();
    test_remove_const<char32_t>();
    test_remove_const<wchar_t>();

    test_remove_const<phi::boolean>();
    test_remove_const<phi::integer<signed char>>();
    test_remove_const<phi::integer<unsigned char>>();
    test_remove_const<phi::integer<short>>();
    test_remove_const<phi::integer<unsigned short>>();
    test_remove_const<phi::integer<int>>();
    test_remove_const<phi::integer<unsigned int>>();
    test_remove_const<phi::integer<long>>();
    test_remove_const<phi::integer<unsigned long>>();
    test_remove_const<phi::integer<long long>>();
    test_remove_const<phi::integer<unsigned long long>>();
    test_remove_const<phi::floating_point<float>>();
    test_remove_const<phi::floating_point<double>>();
    test_remove_const<phi::floating_point<long double>>();

    test_remove_const<std::vector<int>>();
    test_remove_const<phi::scope_ptr<int>>();

    test_remove_const<int&>();
    test_remove_const<const int&>();
    test_remove_const<volatile int&>();
    test_remove_const<const volatile int&>();
    test_remove_const<int&&>();
    test_remove_const<const int&&>();
    test_remove_const<volatile int&&>();
    test_remove_const<const volatile int&&>();
    test_remove_const<int*>();
    test_remove_const<const int*>();
    test_remove_const<volatile int*>();
    test_remove_const<const volatile int*>();
    test_remove_const<int**>();
    test_remove_const<const int**>();
    test_remove_const<volatile int**>();
    test_remove_const<const volatile int**>();
    test_remove_const<int*&>();
    test_remove_const<const int*&>();
    test_remove_const<volatile int*&>();
    test_remove_const<const volatile int*&>();
    test_remove_const<int*&&>();
    test_remove_const<const int*&&>();
    test_remove_const<volatile int*&&>();
    test_remove_const<const volatile int*&&>();
    test_remove_const<void*>();
    test_remove_const<char[3]>();
    test_remove_const<char[]>();
    test_remove_const<char* [3]>();
    test_remove_const<char*[]>();
    test_remove_const<int(*)[3]>();
    test_remove_const<int(*)[]>();
    test_remove_const<int(&)[3]>();
    test_remove_const<int(&)[]>();
    test_remove_const<int(&&)[3]>();
    test_remove_const<int(&&)[]>();
    test_remove_const<char[3][2]>();
    test_remove_const<char[][2]>();
    test_remove_const<char* [3][2]>();
    test_remove_const<char*[][2]>();
    test_remove_const<int(*)[3][2]>();
    test_remove_const<int(*)[][2]>();
    test_remove_const<int(&)[3][2]>();
    test_remove_const<int(&)[][2]>();
    test_remove_const<int(&&)[3][2]>();
    test_remove_const<int(&&)[][2]>();
    test_remove_const<class_type>();
    test_remove_const<class_type[]>();
    test_remove_const<class_type[2]>();
    test_remove_const<template_type<void>>();
    test_remove_const<template_type<int>>();
    test_remove_const<template_type<class_type>>();
    test_remove_const<template_type<incomplete_type>>();
    test_remove_const<variadic_template<>>();
    test_remove_const<variadic_template<void>>();
    test_remove_const<variadic_template<int>>();
    test_remove_const<variadic_template<class_type>>();
    test_remove_const<variadic_template<incomplete_type>>();
    test_remove_const<variadic_template<int, void, class_type, volatile char[]>>();
    test_remove_const<public_derived_from<base>>();
    test_remove_const<public_derived_from<derived>>();
    test_remove_const<public_derived_from<class_type>>();
    test_remove_const<private_derived_from<base>>();
    test_remove_const<private_derived_from<derived>>();
    test_remove_const<private_derived_from<class_type>>();
    test_remove_const<protected_derived_from<base>>();
    test_remove_const<protected_derived_from<derived>>();
    test_remove_const<protected_derived_from<class_type>>();
    test_remove_const<union_type>();
    test_remove_const<non_empty_union>();
    test_remove_const<empty>();
    test_remove_const<not_empty>();
    test_remove_const<bit_zero>();
    test_remove_const<bit_one>();
    test_remove_const<base>();
    test_remove_const<derived>();
    test_remove_const<abstract>();
    test_remove_const<public_abstract>();
    test_remove_const<private_abstract>();
    test_remove_const<protected_abstract>();
    test_remove_const<abstract_template<int>>();
    test_remove_const<abstract_template<double>>();
    test_remove_const<abstract_template<class_type>>();
    test_remove_const<abstract_template<incomplete_type>>();
    test_remove_const<final_type>();
    test_remove_const<public_destructor>();
    test_remove_const<protected_destructor>();
    test_remove_const<private_destructor>();
    test_remove_const<virtual_public_destructor>();
    test_remove_const<virtual_protected_destructor>();
    test_remove_const<virtual_private_destructor>();
    test_remove_const<pure_public_destructor>();
    test_remove_const<pure_protected_destructor>();
    test_remove_const<pure_private_destructor>();
    test_remove_const<deleted_public_destructor>();
    test_remove_const<deleted_protected_destructor>();
    test_remove_const<deleted_private_destructor>();
    test_remove_const<deleted_virtual_public_destructor>();
    test_remove_const<deleted_virtual_protected_destructor>();
    test_remove_const<deleted_virtual_private_destructor>();
    test_remove_const<Enum>();
    test_remove_const<EnumSigned>();
    test_remove_const<EnumUnsigned>();
    test_remove_const<EnumClass>();
    test_remove_const<EnumStruct>();
    test_remove_const<function_type>();
    test_remove_const<function_ptr>();
    test_remove_const<member_object_ptr>();
    test_remove_const<member_function_ptr>();
    test_remove_const<incomplete_type>();
    test_remove_const<incomplete_template<void>>();
    test_remove_const<incomplete_template<int>>();
    test_remove_const<incomplete_template<class_type>>();
    test_remove_const<incomplete_template<incomplete_type>>();
    test_remove_const<incomplete_variadic_template<>>();
    test_remove_const<incomplete_variadic_template<void>>();
    test_remove_const<incomplete_variadic_template<int>>();
    test_remove_const<incomplete_variadic_template<class_type>>();
    test_remove_const<incomplete_variadic_template<incomplete_type>>();
    test_remove_const<incomplete_variadic_template<int, void, class_type, volatile char[]>>();
    test_remove_const<int class_type::*>();
    test_remove_const<float class_type::*>();
    test_remove_const<void * class_type::*>();
    test_remove_const<int * class_type::*>();
    test_remove_const<int class_type::*&>();
    test_remove_const<float class_type::*&>();
    test_remove_const<void * class_type::*&>();
    test_remove_const<int * class_type::*&>();
    test_remove_const<int class_type::*&&>();
    test_remove_const<float class_type::*&&>();
    test_remove_const<void * class_type::*&&>();
    test_remove_const<int * class_type::*&&>();
    test_remove_const<int class_type::* const, int class_type::*>();
    test_remove_const<float class_type::* const, float class_type::*>();
    test_remove_const<void * class_type::* const, void * class_type::*>();
    test_remove_const<int class_type::* const&>();
    test_remove_const<float class_type::* const&>();
    test_remove_const<void * class_type::* const&>();
    test_remove_const<int class_type::* const&&>();
    test_remove_const<float class_type::* const&&>();
    test_remove_const<void * class_type::* const&&>();
    test_remove_const<int class_type::* volatile>();
    test_remove_const<float class_type::* volatile>();
    test_remove_const<void * class_type::* volatile>();
    test_remove_const<int class_type::* volatile&>();
    test_remove_const<float class_type::* volatile&>();
    test_remove_const<void * class_type::* volatile&>();
    test_remove_const<int class_type::* volatile&&>();
    test_remove_const<float class_type::* volatile&&>();
    test_remove_const<void * class_type::* volatile&&>();
    test_remove_const<int class_type::* const volatile, int class_type::* volatile>();
    test_remove_const<float class_type::* const volatile, float class_type::* volatile>();
    test_remove_const<void * class_type::* const volatile, void * class_type::* volatile>();
    test_remove_const<int class_type::* const volatile&>();
    test_remove_const<float class_type::* const volatile&>();
    test_remove_const<void * class_type::* const volatile&>();
    test_remove_const<int class_type::* const volatile&&>();
    test_remove_const<float class_type::* const volatile&&>();
    test_remove_const<void * class_type::* const volatile&&>();
    test_remove_const<non_copyable>();
    test_remove_const<non_moveable>();
    test_remove_const<non_constructible>();
    test_remove_const<tracked>();
    test_remove_const<trap_constructible>();
    test_remove_const<trap_implicit_conversion>();
    test_remove_const<trap_comma>();
    test_remove_const<trap_call>();
    test_remove_const<trap_self_assign>();
    test_remove_const<trap_deref>();
    test_remove_const<trap_array_subscript>();

    test_remove_const<void()>();
    test_remove_const<void()&>();
    test_remove_const<void() &&>();
    test_remove_const<void() const>();
    test_remove_const<void() const&>();
    test_remove_const<void() const&&>();
    test_remove_const<void() volatile>();
    test_remove_const<void() volatile&>();
    test_remove_const<void() volatile&&>();
    test_remove_const<void() const volatile>();
    test_remove_const<void() const volatile&>();
    test_remove_const<void() const volatile&&>();
    test_remove_const<void() noexcept>();
    test_remove_const<void() & noexcept>();
    test_remove_const<void() && noexcept>();
    test_remove_const<void() const noexcept>();
    test_remove_const<void() const & noexcept>();
    test_remove_const<void() const && noexcept>();
    test_remove_const<void() volatile noexcept>();
    test_remove_const<void() volatile & noexcept>();
    test_remove_const<void() volatile && noexcept>();
    test_remove_const<void() const volatile noexcept>();
    test_remove_const<void() const volatile & noexcept>();
    test_remove_const<void() const volatile && noexcept>();

    test_remove_const<void(int)>();
    test_remove_const<void(int)&>();
    test_remove_const<void(int) &&>();
    test_remove_const<void(int) const>();
    test_remove_const<void(int) const&>();
    test_remove_const<void(int) const&&>();
    test_remove_const<void(int) volatile>();
    test_remove_const<void(int) volatile&>();
    test_remove_const<void(int) volatile&&>();
    test_remove_const<void(int) const volatile>();
    test_remove_const<void(int) const volatile&>();
    test_remove_const<void(int) const volatile&&>();
    test_remove_const<void(int) noexcept>();
    test_remove_const<void(int) & noexcept>();
    test_remove_const<void(int) && noexcept>();
    test_remove_const<void(int) const noexcept>();
    test_remove_const<void(int) const & noexcept>();
    test_remove_const<void(int) const && noexcept>();
    test_remove_const<void(int) volatile noexcept>();
    test_remove_const<void(int) volatile & noexcept>();
    test_remove_const<void(int) volatile && noexcept>();
    test_remove_const<void(int) const volatile noexcept>();
    test_remove_const<void(int) const volatile & noexcept>();
    test_remove_const<void(int) const volatile && noexcept>();

    test_remove_const<void(...)>();
    test_remove_const<void(...)&>();
    test_remove_const<void(...) &&>();
    test_remove_const<void(...) const>();
    test_remove_const<void(...) const&>();
    test_remove_const<void(...) const&&>();
    test_remove_const<void(...) volatile>();
    test_remove_const<void(...) volatile&>();
    test_remove_const<void(...) volatile&&>();
    test_remove_const<void(...) const volatile>();
    test_remove_const<void(...) const volatile&>();
    test_remove_const<void(...) const volatile&&>();
    test_remove_const<void(...) noexcept>();
    test_remove_const<void(...) & noexcept>();
    test_remove_const<void(...) && noexcept>();
    test_remove_const<void(...) const noexcept>();
    test_remove_const<void(...) const & noexcept>();
    test_remove_const<void(...) const && noexcept>();
    test_remove_const<void(...) volatile noexcept>();
    test_remove_const<void(...) volatile & noexcept>();
    test_remove_const<void(...) volatile && noexcept>();
    test_remove_const<void(...) const volatile noexcept>();
    test_remove_const<void(...) const volatile & noexcept>();
    test_remove_const<void(...) const volatile && noexcept>();

    test_remove_const<void(int, ...)>();
    test_remove_const<void(int, ...)&>();
    test_remove_const<void(int, ...) &&>();
    test_remove_const<void(int, ...) const>();
    test_remove_const<void(int, ...) const&>();
    test_remove_const<void(int, ...) const&&>();
    test_remove_const<void(int, ...) volatile>();
    test_remove_const<void(int, ...) volatile&>();
    test_remove_const<void(int, ...) volatile&&>();
    test_remove_const<void(int, ...) const volatile>();
    test_remove_const<void(int, ...) const volatile&>();
    test_remove_const<void(int, ...) const volatile&&>();
    test_remove_const<void(int, ...) noexcept>();
    test_remove_const<void(int, ...) & noexcept>();
    test_remove_const<void(int, ...) && noexcept>();
    test_remove_const<void(int, ...) const noexcept>();
    test_remove_const<void(int, ...) const & noexcept>();
    test_remove_const<void(int, ...) const && noexcept>();
    test_remove_const<void(int, ...) volatile noexcept>();
    test_remove_const<void(int, ...) volatile & noexcept>();
    test_remove_const<void(int, ...) volatile && noexcept>();
    test_remove_const<void(int, ...) const volatile noexcept>();
    test_remove_const<void(int, ...) const volatile & noexcept>();
    test_remove_const<void(int, ...) const volatile && noexcept>();

    test_remove_const<int()>();
    test_remove_const<int()&>();
    test_remove_const<int() &&>();
    test_remove_const<int() const>();
    test_remove_const<int() const&>();
    test_remove_const<int() const&&>();
    test_remove_const<int() volatile>();
    test_remove_const<int() volatile&>();
    test_remove_const<int() volatile&&>();
    test_remove_const<int() const volatile>();
    test_remove_const<int() const volatile&>();
    test_remove_const<int() const volatile&&>();
    test_remove_const<int() noexcept>();
    test_remove_const<int() & noexcept>();
    test_remove_const<int() && noexcept>();
    test_remove_const<int() const noexcept>();
    test_remove_const<int() const & noexcept>();
    test_remove_const<int() const && noexcept>();
    test_remove_const<int() volatile noexcept>();
    test_remove_const<int() volatile & noexcept>();
    test_remove_const<int() volatile && noexcept>();
    test_remove_const<int() const volatile noexcept>();
    test_remove_const<int() const volatile & noexcept>();
    test_remove_const<int() const volatile && noexcept>();

    test_remove_const<int(int)>();
    test_remove_const<int(int)&>();
    test_remove_const<int(int) &&>();
    test_remove_const<int(int) const>();
    test_remove_const<int(int) const&>();
    test_remove_const<int(int) const&&>();
    test_remove_const<int(int) volatile>();
    test_remove_const<int(int) volatile&>();
    test_remove_const<int(int) volatile&&>();
    test_remove_const<int(int) const volatile>();
    test_remove_const<int(int) const volatile&>();
    test_remove_const<int(int) const volatile&&>();
    test_remove_const<int(int) noexcept>();
    test_remove_const<int(int) & noexcept>();
    test_remove_const<int(int) && noexcept>();
    test_remove_const<int(int) const noexcept>();
    test_remove_const<int(int) const & noexcept>();
    test_remove_const<int(int) const && noexcept>();
    test_remove_const<int(int) volatile noexcept>();
    test_remove_const<int(int) volatile & noexcept>();
    test_remove_const<int(int) volatile && noexcept>();
    test_remove_const<int(int) const volatile noexcept>();
    test_remove_const<int(int) const volatile & noexcept>();
    test_remove_const<int(int) const volatile && noexcept>();

    test_remove_const<int(...)>();
    test_remove_const<int(...)&>();
    test_remove_const<int(...) &&>();
    test_remove_const<int(...) const>();
    test_remove_const<int(...) const&>();
    test_remove_const<int(...) const&&>();
    test_remove_const<int(...) volatile>();
    test_remove_const<int(...) volatile&>();
    test_remove_const<int(...) volatile&&>();
    test_remove_const<int(...) const volatile>();
    test_remove_const<int(...) const volatile&>();
    test_remove_const<int(...) const volatile&&>();
    test_remove_const<int(...) noexcept>();
    test_remove_const<int(...) & noexcept>();
    test_remove_const<int(...) && noexcept>();
    test_remove_const<int(...) const noexcept>();
    test_remove_const<int(...) const & noexcept>();
    test_remove_const<int(...) const && noexcept>();
    test_remove_const<int(...) volatile noexcept>();
    test_remove_const<int(...) volatile & noexcept>();
    test_remove_const<int(...) volatile && noexcept>();
    test_remove_const<int(...) const volatile noexcept>();
    test_remove_const<int(...) const volatile & noexcept>();
    test_remove_const<int(...) const volatile && noexcept>();

    test_remove_const<int(int, ...)>();
    test_remove_const<int(int, ...)&>();
    test_remove_const<int(int, ...) &&>();
    test_remove_const<int(int, ...) const>();
    test_remove_const<int(int, ...) const&>();
    test_remove_const<int(int, ...) const&&>();
    test_remove_const<int(int, ...) volatile>();
    test_remove_const<int(int, ...) volatile&>();
    test_remove_const<int(int, ...) volatile&&>();
    test_remove_const<int(int, ...) const volatile>();
    test_remove_const<int(int, ...) const volatile&>();
    test_remove_const<int(int, ...) const volatile&&>();
    test_remove_const<int(int, ...) noexcept>();
    test_remove_const<int(int, ...) & noexcept>();
    test_remove_const<int(int, ...) && noexcept>();
    test_remove_const<int(int, ...) const noexcept>();
    test_remove_const<int(int, ...) const & noexcept>();
    test_remove_const<int(int, ...) const && noexcept>();
    test_remove_const<int(int, ...) volatile noexcept>();
    test_remove_const<int(int, ...) volatile & noexcept>();
    test_remove_const<int(int, ...) volatile && noexcept>();
    test_remove_const<int(int, ...) const volatile noexcept>();
    test_remove_const<int(int, ...) const volatile & noexcept>();
    test_remove_const<int(int, ...) const volatile && noexcept>();

    test_remove_const<void (*)()>();
    test_remove_const<void (*)() noexcept>();

    test_remove_const<void (*)(int)>();
    test_remove_const<void (*)(int) noexcept>();

    test_remove_const<void (*)(...)>();
    test_remove_const<void (*)(...) noexcept>();

    test_remove_const<void (*)(int, ...)>();
    test_remove_const<void (*)(int, ...) noexcept>();

    test_remove_const<int (*)()>();
    test_remove_const<int (*)() noexcept>();

    test_remove_const<int (*)(int)>();
    test_remove_const<int (*)(int) noexcept>();

    test_remove_const<int (*)(...)>();
    test_remove_const<int (*)(...) noexcept>();

    test_remove_const<int (*)(int, ...)>();
    test_remove_const<int (*)(int, ...) noexcept>();

    test_remove_const<void (&)()>();
    test_remove_const<void (&)() noexcept>();

    test_remove_const<void (&)(int)>();
    test_remove_const<void (&)(int) noexcept>();

    test_remove_const<void (&)(...)>();
    test_remove_const<void (&)(...) noexcept>();

    test_remove_const<void (&)(int, ...)>();
    test_remove_const<void (&)(int, ...) noexcept>();

    test_remove_const<int (&)()>();
    test_remove_const<int (&)() noexcept>();

    test_remove_const<int (&)(int)>();
    test_remove_const<int (&)(int) noexcept>();

    test_remove_const<int (&)(...)>();
    test_remove_const<int (&)(...) noexcept>();

    test_remove_const<int (&)(int, ...)>();
    test_remove_const<int (&)(int, ...) noexcept>();

    test_remove_const<void (&&)()>();
    test_remove_const<void (&&)() noexcept>();

    test_remove_const<void (&&)(int)>();
    test_remove_const<void (&&)(int) noexcept>();

    test_remove_const<void (&&)(...)>();
    test_remove_const<void (&&)(...) noexcept>();

    test_remove_const<void (&&)(int, ...)>();
    test_remove_const<void (&&)(int, ...) noexcept>();

    test_remove_const<int (&&)()>();
    test_remove_const<int (&&)() noexcept>();

    test_remove_const<int (&&)(int)>();
    test_remove_const<int (&&)(int) noexcept>();

    test_remove_const<int (&&)(...)>();
    test_remove_const<int (&&)(...) noexcept>();

    test_remove_const<int (&&)(int, ...)>();
    test_remove_const<int (&&)(int, ...) noexcept>();

    test_remove_const<void (class_type::*)()>();
    test_remove_const<void (class_type::*)()&>();
    test_remove_const<void (class_type::*)() &&>();
    test_remove_const<void (class_type::*)() const>();
    test_remove_const<void (class_type::*)() const&>();
    test_remove_const<void (class_type::*)() const&&>();
    test_remove_const<void (class_type::*)() noexcept>();
    test_remove_const<void (class_type::*)() & noexcept>();
    test_remove_const<void (class_type::*)() && noexcept>();
    test_remove_const<void (class_type::*)() const noexcept>();
    test_remove_const<void (class_type::*)() const & noexcept>();
    test_remove_const<void (class_type::*)() const && noexcept>();

    test_remove_const<void (class_type::*)(int)>();
    test_remove_const<void (class_type::*)(int)&>();
    test_remove_const<void (class_type::*)(int) &&>();
    test_remove_const<void (class_type::*)(int) const>();
    test_remove_const<void (class_type::*)(int) const&>();
    test_remove_const<void (class_type::*)(int) const&&>();
    test_remove_const<void (class_type::*)(int) noexcept>();
    test_remove_const<void (class_type::*)(int) & noexcept>();
    test_remove_const<void (class_type::*)(int) && noexcept>();
    test_remove_const<void (class_type::*)(int) const noexcept>();
    test_remove_const<void (class_type::*)(int) const & noexcept>();
    test_remove_const<void (class_type::*)(int) const && noexcept>();

    test_remove_const<void (class_type::*)(...)>();
    test_remove_const<void (class_type::*)(...)&>();
    test_remove_const<void (class_type::*)(...) &&>();
    test_remove_const<void (class_type::*)(...) const>();
    test_remove_const<void (class_type::*)(...) const&>();
    test_remove_const<void (class_type::*)(...) const&&>();
    test_remove_const<void (class_type::*)(...) noexcept>();
    test_remove_const<void (class_type::*)(...) & noexcept>();
    test_remove_const<void (class_type::*)(...) && noexcept>();
    test_remove_const<void (class_type::*)(...) const noexcept>();
    test_remove_const<void (class_type::*)(...) const & noexcept>();
    test_remove_const<void (class_type::*)(...) const && noexcept>();

    test_remove_const<void (class_type::*)(int, ...)>();
    test_remove_const<void (class_type::*)(int, ...)&>();
    test_remove_const<void (class_type::*)(int, ...) &&>();
    test_remove_const<void (class_type::*)(int, ...) const>();
    test_remove_const<void (class_type::*)(int, ...) const&>();
    test_remove_const<void (class_type::*)(int, ...) const&&>();
    test_remove_const<void (class_type::*)(int, ...) noexcept>();
    test_remove_const<void (class_type::*)(int, ...) & noexcept>();
    test_remove_const<void (class_type::*)(int, ...) && noexcept>();
    test_remove_const<void (class_type::*)(int, ...) const noexcept>();
    test_remove_const<void (class_type::*)(int, ...) const & noexcept>();
    test_remove_const<void (class_type::*)(int, ...) const && noexcept>();

    test_remove_const<int (class_type::*)()>();
    test_remove_const<int (class_type::*)()&>();
    test_remove_const<int (class_type::*)() &&>();
    test_remove_const<int (class_type::*)() const>();
    test_remove_const<int (class_type::*)() const&>();
    test_remove_const<int (class_type::*)() const&&>();
    test_remove_const<int (class_type::*)() noexcept>();
    test_remove_const<int (class_type::*)() & noexcept>();
    test_remove_const<int (class_type::*)() && noexcept>();
    test_remove_const<int (class_type::*)() const noexcept>();
    test_remove_const<int (class_type::*)() const & noexcept>();
    test_remove_const<int (class_type::*)() const && noexcept>();

    test_remove_const<int (class_type::*)(int)>();
    test_remove_const<int (class_type::*)(int)&>();
    test_remove_const<int (class_type::*)(int) &&>();
    test_remove_const<int (class_type::*)(int) const>();
    test_remove_const<int (class_type::*)(int) const&>();
    test_remove_const<int (class_type::*)(int) const&&>();
    test_remove_const<int (class_type::*)(int) noexcept>();
    test_remove_const<int (class_type::*)(int) & noexcept>();
    test_remove_const<int (class_type::*)(int) && noexcept>();
    test_remove_const<int (class_type::*)(int) const noexcept>();
    test_remove_const<int (class_type::*)(int) const & noexcept>();
    test_remove_const<int (class_type::*)(int) const && noexcept>();

    test_remove_const<int (class_type::*)(...)>();
    test_remove_const<int (class_type::*)(...)&>();
    test_remove_const<int (class_type::*)(...) &&>();
    test_remove_const<int (class_type::*)(...) const>();
    test_remove_const<int (class_type::*)(...) const&>();
    test_remove_const<int (class_type::*)(...) const&&>();
    test_remove_const<int (class_type::*)(...) noexcept>();
    test_remove_const<int (class_type::*)(...) & noexcept>();
    test_remove_const<int (class_type::*)(...) && noexcept>();
    test_remove_const<int (class_type::*)(...) const noexcept>();
    test_remove_const<int (class_type::*)(...) const & noexcept>();
    test_remove_const<int (class_type::*)(...) const && noexcept>();

    test_remove_const<int (class_type::*)(int, ...)>();
    test_remove_const<int (class_type::*)(int, ...)&>();
    test_remove_const<int (class_type::*)(int, ...) &&>();
    test_remove_const<int (class_type::*)(int, ...) const>();
    test_remove_const<int (class_type::*)(int, ...) const&>();
    test_remove_const<int (class_type::*)(int, ...) const&&>();
    test_remove_const<int (class_type::*)(int, ...) noexcept>();
    test_remove_const<int (class_type::*)(int, ...) & noexcept>();
    test_remove_const<int (class_type::*)(int, ...) && noexcept>();
    test_remove_const<int (class_type::*)(int, ...) const noexcept>();
    test_remove_const<int (class_type::*)(int, ...) const & noexcept>();
    test_remove_const<int (class_type::*)(int, ...) const && noexcept>();
}
