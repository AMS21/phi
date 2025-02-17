#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/remove_volatile.hpp>
#include <vector>

template <typename TypeT, typename ExpectedT>
void test_remove_volatile_impl()
{
    CHECK_SAME_TYPE(typename phi::remove_volatile<TypeT>::type, ExpectedT);
    CHECK_SAME_TYPE(phi::remove_volatile_t<TypeT>, ExpectedT);

    // Standard compatibility
    CHECK_SAME_TYPE(typename std::remove_volatile<TypeT>::type, ExpectedT);
}

template <typename TypeT, typename ExpectedT = TypeT>
void test_remove_volatile()
{
    test_remove_volatile_impl<TypeT, ExpectedT>();
    test_remove_volatile_impl<const TypeT, const ExpectedT>();
    test_remove_volatile_impl<volatile TypeT, ExpectedT>();
    test_remove_volatile_impl<const volatile TypeT, const ExpectedT>();
}

TEST_CASE("remove_volatile")
{
    test_remove_volatile<void>();
    test_remove_volatile<phi::nullptr_t>();
    test_remove_volatile<bool>();
    test_remove_volatile<char>();
    test_remove_volatile<signed char>();
    test_remove_volatile<unsigned char>();
    test_remove_volatile<short>();
    test_remove_volatile<unsigned short>();
    test_remove_volatile<int>();
    test_remove_volatile<unsigned int>();
    test_remove_volatile<long>();
    test_remove_volatile<unsigned long>();
    test_remove_volatile<long long>();
    test_remove_volatile<unsigned long long>();
    test_remove_volatile<float>();
    test_remove_volatile<double>();
    test_remove_volatile<long double>();
    test_remove_volatile<char8_t>();
    test_remove_volatile<char16_t>();
    test_remove_volatile<char32_t>();
    test_remove_volatile<wchar_t>();

    test_remove_volatile<phi::boolean>();
    test_remove_volatile<phi::integer<signed char>>();
    test_remove_volatile<phi::integer<unsigned char>>();
    test_remove_volatile<phi::integer<short>>();
    test_remove_volatile<phi::integer<unsigned short>>();
    test_remove_volatile<phi::integer<int>>();
    test_remove_volatile<phi::integer<unsigned int>>();
    test_remove_volatile<phi::integer<long>>();
    test_remove_volatile<phi::integer<unsigned long>>();
    test_remove_volatile<phi::integer<long long>>();
    test_remove_volatile<phi::integer<unsigned long long>>();
    test_remove_volatile<phi::floating_point<float>>();
    test_remove_volatile<phi::floating_point<double>>();
    test_remove_volatile<phi::floating_point<long double>>();

    test_remove_volatile<std::vector<int>>();
    test_remove_volatile<phi::scope_ptr<int>>();

    test_remove_volatile<int&>();
    test_remove_volatile<const int&>();
    test_remove_volatile<volatile int&>();
    test_remove_volatile<const volatile int&>();
    test_remove_volatile<int&&>();
    test_remove_volatile<const int&&>();
    test_remove_volatile<volatile int&&>();
    test_remove_volatile<const volatile int&&>();
    test_remove_volatile<int*>();
    test_remove_volatile<const int*>();
    test_remove_volatile<volatile int*>();
    test_remove_volatile<const volatile int*>();
    test_remove_volatile<int**>();
    test_remove_volatile<const int**>();
    test_remove_volatile<volatile int**>();
    test_remove_volatile<const volatile int**>();
    test_remove_volatile<int*&>();
    test_remove_volatile<const int*&>();
    test_remove_volatile<volatile int*&>();
    test_remove_volatile<const volatile int*&>();
    test_remove_volatile<int*&&>();
    test_remove_volatile<const int*&&>();
    test_remove_volatile<volatile int*&&>();
    test_remove_volatile<const volatile int*&&>();
    test_remove_volatile<void*>();
    test_remove_volatile<char[3]>();
    test_remove_volatile<char[]>();
    test_remove_volatile<char* [3]>();
    test_remove_volatile<char*[]>();
    test_remove_volatile<int(*)[3]>();
    test_remove_volatile<int(*)[]>();
    test_remove_volatile<int(&)[3]>();
    test_remove_volatile<int(&)[]>();
    test_remove_volatile<int(&&)[3]>();
    test_remove_volatile<int(&&)[]>();
    test_remove_volatile<char[3][2]>();
    test_remove_volatile<char[][2]>();
    test_remove_volatile<char* [3][2]>();
    test_remove_volatile<char*[][2]>();
    test_remove_volatile<int(*)[3][2]>();
    test_remove_volatile<int(*)[][2]>();
    test_remove_volatile<int(&)[3][2]>();
    test_remove_volatile<int(&)[][2]>();
    test_remove_volatile<int(&&)[3][2]>();
    test_remove_volatile<int(&&)[][2]>();
    test_remove_volatile<class_type>();
    test_remove_volatile<class_type[]>();
    test_remove_volatile<class_type[2]>();
    test_remove_volatile<template_type<void>>();
    test_remove_volatile<template_type<int>>();
    test_remove_volatile<template_type<class_type>>();
    test_remove_volatile<template_type<incomplete_type>>();
    test_remove_volatile<variadic_template<>>();
    test_remove_volatile<variadic_template<void>>();
    test_remove_volatile<variadic_template<int>>();
    test_remove_volatile<variadic_template<class_type>>();
    test_remove_volatile<variadic_template<incomplete_type>>();
    test_remove_volatile<variadic_template<int, void, class_type, volatile char[]>>();
    test_remove_volatile<public_derived_from<base>>();
    test_remove_volatile<public_derived_from<derived>>();
    test_remove_volatile<public_derived_from<class_type>>();
    test_remove_volatile<private_derived_from<base>>();
    test_remove_volatile<private_derived_from<derived>>();
    test_remove_volatile<private_derived_from<class_type>>();
    test_remove_volatile<protected_derived_from<base>>();
    test_remove_volatile<protected_derived_from<derived>>();
    test_remove_volatile<protected_derived_from<class_type>>();
    test_remove_volatile<union_type>();
    test_remove_volatile<non_empty_union>();
    test_remove_volatile<empty>();
    test_remove_volatile<not_empty>();
    test_remove_volatile<bit_zero>();
    test_remove_volatile<bit_one>();
    test_remove_volatile<base>();
    test_remove_volatile<derived>();
    test_remove_volatile<abstract>();
    test_remove_volatile<public_abstract>();
    test_remove_volatile<private_abstract>();
    test_remove_volatile<protected_abstract>();
    test_remove_volatile<abstract_template<int>>();
    test_remove_volatile<abstract_template<double>>();
    test_remove_volatile<abstract_template<class_type>>();
    test_remove_volatile<abstract_template<incomplete_type>>();
    test_remove_volatile<final_type>();
    test_remove_volatile<public_destructor>();
    test_remove_volatile<protected_destructor>();
    test_remove_volatile<private_destructor>();
    test_remove_volatile<virtual_public_destructor>();
    test_remove_volatile<virtual_protected_destructor>();
    test_remove_volatile<virtual_private_destructor>();
    test_remove_volatile<pure_public_destructor>();
    test_remove_volatile<pure_protected_destructor>();
    test_remove_volatile<pure_private_destructor>();
    test_remove_volatile<deleted_public_destructor>();
    test_remove_volatile<deleted_protected_destructor>();
    test_remove_volatile<deleted_private_destructor>();
    test_remove_volatile<deleted_virtual_public_destructor>();
    test_remove_volatile<deleted_virtual_protected_destructor>();
    test_remove_volatile<deleted_virtual_private_destructor>();
    test_remove_volatile<Enum>();
    test_remove_volatile<EnumSigned>();
    test_remove_volatile<EnumUnsigned>();
    test_remove_volatile<EnumClass>();
    test_remove_volatile<EnumStruct>();
    test_remove_volatile<function_type>();
    test_remove_volatile<function_ptr>();
    test_remove_volatile<member_object_ptr>();
    test_remove_volatile<member_function_ptr>();
    test_remove_volatile<incomplete_type>();
    test_remove_volatile<incomplete_template<void>>();
    test_remove_volatile<incomplete_template<int>>();
    test_remove_volatile<incomplete_template<class_type>>();
    test_remove_volatile<incomplete_template<incomplete_type>>();
    test_remove_volatile<incomplete_variadic_template<>>();
    test_remove_volatile<incomplete_variadic_template<void>>();
    test_remove_volatile<incomplete_variadic_template<int>>();
    test_remove_volatile<incomplete_variadic_template<class_type>>();
    test_remove_volatile<incomplete_variadic_template<incomplete_type>>();
    test_remove_volatile<incomplete_variadic_template<int, void, class_type, volatile char[]>>();
    test_remove_volatile<int class_type::*>();
    test_remove_volatile<float class_type::*>();
    test_remove_volatile<void * class_type::*>();
    test_remove_volatile<int * class_type::*>();
    test_remove_volatile<int class_type::*&>();
    test_remove_volatile<float class_type::*&>();
    test_remove_volatile<void * class_type::*&>();
    test_remove_volatile<int * class_type::*&>();
    test_remove_volatile<int class_type::*&&>();
    test_remove_volatile<float class_type::*&&>();
    test_remove_volatile<void * class_type::*&&>();
    test_remove_volatile<int * class_type::*&&>();
    test_remove_volatile<int class_type::* const>();
    test_remove_volatile<float class_type::* const>();
    test_remove_volatile<void * class_type::* const>();
    test_remove_volatile<int class_type::* const&>();
    test_remove_volatile<float class_type::* const&>();
    test_remove_volatile<void * class_type::* const&>();
    test_remove_volatile<int class_type::* const&&>();
    test_remove_volatile<float class_type::* const&&>();
    test_remove_volatile<void * class_type::* const&&>();
    test_remove_volatile<int class_type::* volatile, int class_type::*>();
    test_remove_volatile<float class_type::* volatile, float class_type::*>();
    test_remove_volatile<void * class_type::* volatile, void * class_type::*>();
    test_remove_volatile<int class_type::* volatile&>();
    test_remove_volatile<float class_type::* volatile&>();
    test_remove_volatile<void * class_type::* volatile&>();
    test_remove_volatile<int class_type::* volatile&&>();
    test_remove_volatile<float class_type::* volatile&&>();
    test_remove_volatile<void * class_type::* volatile&&>();
    test_remove_volatile<int class_type::* const volatile, int class_type::* const>();
    test_remove_volatile<float class_type::* const volatile, float class_type::* const>();
    test_remove_volatile<void * class_type::* const volatile, void * class_type::* const>();
    test_remove_volatile<int class_type::* const volatile&>();
    test_remove_volatile<float class_type::* const volatile&>();
    test_remove_volatile<void * class_type::* const volatile&>();
    test_remove_volatile<int class_type::* const volatile&&>();
    test_remove_volatile<float class_type::* const volatile&&>();
    test_remove_volatile<void * class_type::* const volatile&&>();
    test_remove_volatile<non_copyable>();
    test_remove_volatile<non_moveable>();
    test_remove_volatile<non_constructible>();
    test_remove_volatile<tracked>();
    test_remove_volatile<trap_constructible>();
    test_remove_volatile<trap_implicit_conversion>();
    test_remove_volatile<trap_comma>();
    test_remove_volatile<trap_call>();
    test_remove_volatile<trap_self_assign>();
    test_remove_volatile<trap_deref>();
    test_remove_volatile<trap_array_subscript>();

    test_remove_volatile<void()>();
    test_remove_volatile<void()&>();
    test_remove_volatile<void() &&>();
    test_remove_volatile<void() const>();
    test_remove_volatile<void() const&>();
    test_remove_volatile<void() const&&>();
    test_remove_volatile<void() volatile>();
    test_remove_volatile<void() volatile&>();
    test_remove_volatile<void() volatile&&>();
    test_remove_volatile<void() const volatile>();
    test_remove_volatile<void() const volatile&>();
    test_remove_volatile<void() const volatile&&>();
    test_remove_volatile<void() noexcept>();
    test_remove_volatile<void() & noexcept>();
    test_remove_volatile<void() && noexcept>();
    test_remove_volatile<void() const noexcept>();
    test_remove_volatile<void() const & noexcept>();
    test_remove_volatile<void() const && noexcept>();
    test_remove_volatile<void() volatile noexcept>();
    test_remove_volatile<void() volatile & noexcept>();
    test_remove_volatile<void() volatile && noexcept>();
    test_remove_volatile<void() const volatile noexcept>();
    test_remove_volatile<void() const volatile & noexcept>();
    test_remove_volatile<void() const volatile && noexcept>();

    test_remove_volatile<void(int)>();
    test_remove_volatile<void(int)&>();
    test_remove_volatile<void(int) &&>();
    test_remove_volatile<void(int) const>();
    test_remove_volatile<void(int) const&>();
    test_remove_volatile<void(int) const&&>();
    test_remove_volatile<void(int) volatile>();
    test_remove_volatile<void(int) volatile&>();
    test_remove_volatile<void(int) volatile&&>();
    test_remove_volatile<void(int) const volatile>();
    test_remove_volatile<void(int) const volatile&>();
    test_remove_volatile<void(int) const volatile&&>();
    test_remove_volatile<void(int) noexcept>();
    test_remove_volatile<void(int) & noexcept>();
    test_remove_volatile<void(int) && noexcept>();
    test_remove_volatile<void(int) const noexcept>();
    test_remove_volatile<void(int) const & noexcept>();
    test_remove_volatile<void(int) const && noexcept>();
    test_remove_volatile<void(int) volatile noexcept>();
    test_remove_volatile<void(int) volatile & noexcept>();
    test_remove_volatile<void(int) volatile && noexcept>();
    test_remove_volatile<void(int) const volatile noexcept>();
    test_remove_volatile<void(int) const volatile & noexcept>();
    test_remove_volatile<void(int) const volatile && noexcept>();

    test_remove_volatile<void(...)>();
    test_remove_volatile<void(...)&>();
    test_remove_volatile<void(...) &&>();
    test_remove_volatile<void(...) const>();
    test_remove_volatile<void(...) const&>();
    test_remove_volatile<void(...) const&&>();
    test_remove_volatile<void(...) volatile>();
    test_remove_volatile<void(...) volatile&>();
    test_remove_volatile<void(...) volatile&&>();
    test_remove_volatile<void(...) const volatile>();
    test_remove_volatile<void(...) const volatile&>();
    test_remove_volatile<void(...) const volatile&&>();
    test_remove_volatile<void(...) noexcept>();
    test_remove_volatile<void(...) & noexcept>();
    test_remove_volatile<void(...) && noexcept>();
    test_remove_volatile<void(...) const noexcept>();
    test_remove_volatile<void(...) const & noexcept>();
    test_remove_volatile<void(...) const && noexcept>();
    test_remove_volatile<void(...) volatile noexcept>();
    test_remove_volatile<void(...) volatile & noexcept>();
    test_remove_volatile<void(...) volatile && noexcept>();
    test_remove_volatile<void(...) const volatile noexcept>();
    test_remove_volatile<void(...) const volatile & noexcept>();
    test_remove_volatile<void(...) const volatile && noexcept>();

    test_remove_volatile<void(int, ...)>();
    test_remove_volatile<void(int, ...)&>();
    test_remove_volatile<void(int, ...) &&>();
    test_remove_volatile<void(int, ...) const>();
    test_remove_volatile<void(int, ...) const&>();
    test_remove_volatile<void(int, ...) const&&>();
    test_remove_volatile<void(int, ...) volatile>();
    test_remove_volatile<void(int, ...) volatile&>();
    test_remove_volatile<void(int, ...) volatile&&>();
    test_remove_volatile<void(int, ...) const volatile>();
    test_remove_volatile<void(int, ...) const volatile&>();
    test_remove_volatile<void(int, ...) const volatile&&>();
    test_remove_volatile<void(int, ...) noexcept>();
    test_remove_volatile<void(int, ...) & noexcept>();
    test_remove_volatile<void(int, ...) && noexcept>();
    test_remove_volatile<void(int, ...) const noexcept>();
    test_remove_volatile<void(int, ...) const & noexcept>();
    test_remove_volatile<void(int, ...) const && noexcept>();
    test_remove_volatile<void(int, ...) volatile noexcept>();
    test_remove_volatile<void(int, ...) volatile & noexcept>();
    test_remove_volatile<void(int, ...) volatile && noexcept>();
    test_remove_volatile<void(int, ...) const volatile noexcept>();
    test_remove_volatile<void(int, ...) const volatile & noexcept>();
    test_remove_volatile<void(int, ...) const volatile && noexcept>();

    test_remove_volatile<int()>();
    test_remove_volatile<int()&>();
    test_remove_volatile<int() &&>();
    test_remove_volatile<int() const>();
    test_remove_volatile<int() const&>();
    test_remove_volatile<int() const&&>();
    test_remove_volatile<int() volatile>();
    test_remove_volatile<int() volatile&>();
    test_remove_volatile<int() volatile&&>();
    test_remove_volatile<int() const volatile>();
    test_remove_volatile<int() const volatile&>();
    test_remove_volatile<int() const volatile&&>();
    test_remove_volatile<int() noexcept>();
    test_remove_volatile<int() & noexcept>();
    test_remove_volatile<int() && noexcept>();
    test_remove_volatile<int() const noexcept>();
    test_remove_volatile<int() const & noexcept>();
    test_remove_volatile<int() const && noexcept>();
    test_remove_volatile<int() volatile noexcept>();
    test_remove_volatile<int() volatile & noexcept>();
    test_remove_volatile<int() volatile && noexcept>();
    test_remove_volatile<int() const volatile noexcept>();
    test_remove_volatile<int() const volatile & noexcept>();
    test_remove_volatile<int() const volatile && noexcept>();

    test_remove_volatile<int(int)>();
    test_remove_volatile<int(int)&>();
    test_remove_volatile<int(int) &&>();
    test_remove_volatile<int(int) const>();
    test_remove_volatile<int(int) const&>();
    test_remove_volatile<int(int) const&&>();
    test_remove_volatile<int(int) volatile>();
    test_remove_volatile<int(int) volatile&>();
    test_remove_volatile<int(int) volatile&&>();
    test_remove_volatile<int(int) const volatile>();
    test_remove_volatile<int(int) const volatile&>();
    test_remove_volatile<int(int) const volatile&&>();
    test_remove_volatile<int(int) noexcept>();
    test_remove_volatile<int(int) & noexcept>();
    test_remove_volatile<int(int) && noexcept>();
    test_remove_volatile<int(int) const noexcept>();
    test_remove_volatile<int(int) const & noexcept>();
    test_remove_volatile<int(int) const && noexcept>();
    test_remove_volatile<int(int) volatile noexcept>();
    test_remove_volatile<int(int) volatile & noexcept>();
    test_remove_volatile<int(int) volatile && noexcept>();
    test_remove_volatile<int(int) const volatile noexcept>();
    test_remove_volatile<int(int) const volatile & noexcept>();
    test_remove_volatile<int(int) const volatile && noexcept>();

    test_remove_volatile<int(...)>();
    test_remove_volatile<int(...)&>();
    test_remove_volatile<int(...) &&>();
    test_remove_volatile<int(...) const>();
    test_remove_volatile<int(...) const&>();
    test_remove_volatile<int(...) const&&>();
    test_remove_volatile<int(...) volatile>();
    test_remove_volatile<int(...) volatile&>();
    test_remove_volatile<int(...) volatile&&>();
    test_remove_volatile<int(...) const volatile>();
    test_remove_volatile<int(...) const volatile&>();
    test_remove_volatile<int(...) const volatile&&>();
    test_remove_volatile<int(...) noexcept>();
    test_remove_volatile<int(...) & noexcept>();
    test_remove_volatile<int(...) && noexcept>();
    test_remove_volatile<int(...) const noexcept>();
    test_remove_volatile<int(...) const & noexcept>();
    test_remove_volatile<int(...) const && noexcept>();
    test_remove_volatile<int(...) volatile noexcept>();
    test_remove_volatile<int(...) volatile & noexcept>();
    test_remove_volatile<int(...) volatile && noexcept>();
    test_remove_volatile<int(...) const volatile noexcept>();
    test_remove_volatile<int(...) const volatile & noexcept>();
    test_remove_volatile<int(...) const volatile && noexcept>();

    test_remove_volatile<int(int, ...)>();
    test_remove_volatile<int(int, ...)&>();
    test_remove_volatile<int(int, ...) &&>();
    test_remove_volatile<int(int, ...) const>();
    test_remove_volatile<int(int, ...) const&>();
    test_remove_volatile<int(int, ...) const&&>();
    test_remove_volatile<int(int, ...) volatile>();
    test_remove_volatile<int(int, ...) volatile&>();
    test_remove_volatile<int(int, ...) volatile&&>();
    test_remove_volatile<int(int, ...) const volatile>();
    test_remove_volatile<int(int, ...) const volatile&>();
    test_remove_volatile<int(int, ...) const volatile&&>();
    test_remove_volatile<int(int, ...) noexcept>();
    test_remove_volatile<int(int, ...) & noexcept>();
    test_remove_volatile<int(int, ...) && noexcept>();
    test_remove_volatile<int(int, ...) const noexcept>();
    test_remove_volatile<int(int, ...) const & noexcept>();
    test_remove_volatile<int(int, ...) const && noexcept>();
    test_remove_volatile<int(int, ...) volatile noexcept>();
    test_remove_volatile<int(int, ...) volatile & noexcept>();
    test_remove_volatile<int(int, ...) volatile && noexcept>();
    test_remove_volatile<int(int, ...) const volatile noexcept>();
    test_remove_volatile<int(int, ...) const volatile & noexcept>();
    test_remove_volatile<int(int, ...) const volatile && noexcept>();

    test_remove_volatile<void (*)()>();
    test_remove_volatile<void (*)() noexcept>();

    test_remove_volatile<void (*)(int)>();
    test_remove_volatile<void (*)(int) noexcept>();

    test_remove_volatile<void (*)(...)>();
    test_remove_volatile<void (*)(...) noexcept>();

    test_remove_volatile<void (*)(int, ...)>();
    test_remove_volatile<void (*)(int, ...) noexcept>();

    test_remove_volatile<int (*)()>();
    test_remove_volatile<int (*)() noexcept>();

    test_remove_volatile<int (*)(int)>();
    test_remove_volatile<int (*)(int) noexcept>();

    test_remove_volatile<int (*)(...)>();
    test_remove_volatile<int (*)(...) noexcept>();

    test_remove_volatile<int (*)(int, ...)>();
    test_remove_volatile<int (*)(int, ...) noexcept>();

    test_remove_volatile<void (&)()>();
    test_remove_volatile<void (&)() noexcept>();

    test_remove_volatile<void (&)(int)>();
    test_remove_volatile<void (&)(int) noexcept>();

    test_remove_volatile<void (&)(...)>();
    test_remove_volatile<void (&)(...) noexcept>();

    test_remove_volatile<void (&)(int, ...)>();
    test_remove_volatile<void (&)(int, ...) noexcept>();

    test_remove_volatile<int (&)()>();
    test_remove_volatile<int (&)() noexcept>();

    test_remove_volatile<int (&)(int)>();
    test_remove_volatile<int (&)(int) noexcept>();

    test_remove_volatile<int (&)(...)>();
    test_remove_volatile<int (&)(...) noexcept>();

    test_remove_volatile<int (&)(int, ...)>();
    test_remove_volatile<int (&)(int, ...) noexcept>();

    test_remove_volatile<void (&&)()>();
    test_remove_volatile<void (&&)() noexcept>();

    test_remove_volatile<void (&&)(int)>();
    test_remove_volatile<void (&&)(int) noexcept>();

    test_remove_volatile<void (&&)(...)>();
    test_remove_volatile<void (&&)(...) noexcept>();

    test_remove_volatile<void (&&)(int, ...)>();
    test_remove_volatile<void (&&)(int, ...) noexcept>();

    test_remove_volatile<int (&&)()>();
    test_remove_volatile<int (&&)() noexcept>();

    test_remove_volatile<int (&&)(int)>();
    test_remove_volatile<int (&&)(int) noexcept>();

    test_remove_volatile<int (&&)(...)>();
    test_remove_volatile<int (&&)(...) noexcept>();

    test_remove_volatile<int (&&)(int, ...)>();
    test_remove_volatile<int (&&)(int, ...) noexcept>();

    test_remove_volatile<void (class_type::*)()>();
    test_remove_volatile<void (class_type::*)()&>();
    test_remove_volatile<void (class_type::*)() &&>();
    test_remove_volatile<void (class_type::*)() const>();
    test_remove_volatile<void (class_type::*)() const&>();
    test_remove_volatile<void (class_type::*)() const&&>();
    test_remove_volatile<void (class_type::*)() noexcept>();
    test_remove_volatile<void (class_type::*)() & noexcept>();
    test_remove_volatile<void (class_type::*)() && noexcept>();
    test_remove_volatile<void (class_type::*)() const noexcept>();
    test_remove_volatile<void (class_type::*)() const & noexcept>();
    test_remove_volatile<void (class_type::*)() const && noexcept>();

    test_remove_volatile<void (class_type::*)(int)>();
    test_remove_volatile<void (class_type::*)(int)&>();
    test_remove_volatile<void (class_type::*)(int) &&>();
    test_remove_volatile<void (class_type::*)(int) const>();
    test_remove_volatile<void (class_type::*)(int) const&>();
    test_remove_volatile<void (class_type::*)(int) const&&>();
    test_remove_volatile<void (class_type::*)(int) noexcept>();
    test_remove_volatile<void (class_type::*)(int) & noexcept>();
    test_remove_volatile<void (class_type::*)(int) && noexcept>();
    test_remove_volatile<void (class_type::*)(int) const noexcept>();
    test_remove_volatile<void (class_type::*)(int) const & noexcept>();
    test_remove_volatile<void (class_type::*)(int) const && noexcept>();

    test_remove_volatile<void (class_type::*)(...)>();
    test_remove_volatile<void (class_type::*)(...)&>();
    test_remove_volatile<void (class_type::*)(...) &&>();
    test_remove_volatile<void (class_type::*)(...) const>();
    test_remove_volatile<void (class_type::*)(...) const&>();
    test_remove_volatile<void (class_type::*)(...) const&&>();
    test_remove_volatile<void (class_type::*)(...) noexcept>();
    test_remove_volatile<void (class_type::*)(...) & noexcept>();
    test_remove_volatile<void (class_type::*)(...) && noexcept>();
    test_remove_volatile<void (class_type::*)(...) const noexcept>();
    test_remove_volatile<void (class_type::*)(...) const & noexcept>();
    test_remove_volatile<void (class_type::*)(...) const && noexcept>();

    test_remove_volatile<void (class_type::*)(int, ...)>();
    test_remove_volatile<void (class_type::*)(int, ...)&>();
    test_remove_volatile<void (class_type::*)(int, ...) &&>();
    test_remove_volatile<void (class_type::*)(int, ...) const>();
    test_remove_volatile<void (class_type::*)(int, ...) const&>();
    test_remove_volatile<void (class_type::*)(int, ...) const&&>();
    test_remove_volatile<void (class_type::*)(int, ...) noexcept>();
    test_remove_volatile<void (class_type::*)(int, ...) & noexcept>();
    test_remove_volatile<void (class_type::*)(int, ...) && noexcept>();
    test_remove_volatile<void (class_type::*)(int, ...) const noexcept>();
    test_remove_volatile<void (class_type::*)(int, ...) const & noexcept>();
    test_remove_volatile<void (class_type::*)(int, ...) const && noexcept>();

    test_remove_volatile<int (class_type::*)()>();
    test_remove_volatile<int (class_type::*)()&>();
    test_remove_volatile<int (class_type::*)() &&>();
    test_remove_volatile<int (class_type::*)() const>();
    test_remove_volatile<int (class_type::*)() const&>();
    test_remove_volatile<int (class_type::*)() const&&>();
    test_remove_volatile<int (class_type::*)() noexcept>();
    test_remove_volatile<int (class_type::*)() & noexcept>();
    test_remove_volatile<int (class_type::*)() && noexcept>();
    test_remove_volatile<int (class_type::*)() const noexcept>();
    test_remove_volatile<int (class_type::*)() const & noexcept>();
    test_remove_volatile<int (class_type::*)() const && noexcept>();

    test_remove_volatile<int (class_type::*)(int)>();
    test_remove_volatile<int (class_type::*)(int)&>();
    test_remove_volatile<int (class_type::*)(int) &&>();
    test_remove_volatile<int (class_type::*)(int) const>();
    test_remove_volatile<int (class_type::*)(int) const&>();
    test_remove_volatile<int (class_type::*)(int) const&&>();
    test_remove_volatile<int (class_type::*)(int) noexcept>();
    test_remove_volatile<int (class_type::*)(int) & noexcept>();
    test_remove_volatile<int (class_type::*)(int) && noexcept>();
    test_remove_volatile<int (class_type::*)(int) const noexcept>();
    test_remove_volatile<int (class_type::*)(int) const & noexcept>();
    test_remove_volatile<int (class_type::*)(int) const && noexcept>();

    test_remove_volatile<int (class_type::*)(...)>();
    test_remove_volatile<int (class_type::*)(...)&>();
    test_remove_volatile<int (class_type::*)(...) &&>();
    test_remove_volatile<int (class_type::*)(...) const>();
    test_remove_volatile<int (class_type::*)(...) const&>();
    test_remove_volatile<int (class_type::*)(...) const&&>();
    test_remove_volatile<int (class_type::*)(...) noexcept>();
    test_remove_volatile<int (class_type::*)(...) & noexcept>();
    test_remove_volatile<int (class_type::*)(...) && noexcept>();
    test_remove_volatile<int (class_type::*)(...) const noexcept>();
    test_remove_volatile<int (class_type::*)(...) const & noexcept>();
    test_remove_volatile<int (class_type::*)(...) const && noexcept>();

    test_remove_volatile<int (class_type::*)(int, ...)>();
    test_remove_volatile<int (class_type::*)(int, ...)&>();
    test_remove_volatile<int (class_type::*)(int, ...) &&>();
    test_remove_volatile<int (class_type::*)(int, ...) const>();
    test_remove_volatile<int (class_type::*)(int, ...) const&>();
    test_remove_volatile<int (class_type::*)(int, ...) const&&>();
    test_remove_volatile<int (class_type::*)(int, ...) noexcept>();
    test_remove_volatile<int (class_type::*)(int, ...) & noexcept>();
    test_remove_volatile<int (class_type::*)(int, ...) && noexcept>();
    test_remove_volatile<int (class_type::*)(int, ...) const noexcept>();
    test_remove_volatile<int (class_type::*)(int, ...) const & noexcept>();
    test_remove_volatile<int (class_type::*)(int, ...) const && noexcept>();
}
