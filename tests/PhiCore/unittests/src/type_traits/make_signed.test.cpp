#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/conditional.hpp>
#include <phi/type_traits/make_signed.hpp>
#include <cstdint>
#include <vector>

template <typename TypeT, typename ExpectedT>
void test_make_signed_impl()
{
    CHECK_SAME_TYPE(typename phi::make_signed<TypeT>::type, ExpectedT);
    CHECK_SAME_TYPE(phi::make_signed_t<TypeT>, ExpectedT);
}

template <typename TypeT, typename ExpectedT = TypeT>
void test_make_signed()
{
    test_make_signed_impl<TypeT, ExpectedT>();
    test_make_signed_impl<const TypeT, const ExpectedT>();
    test_make_signed_impl<volatile TypeT, volatile ExpectedT>();
    test_make_signed_impl<const volatile TypeT, const volatile ExpectedT>();
}

enum BigEnum : long long
{
    bigzero,
    big = 0xFFFFFFFFFFFFFFFLL
};

TEST_CASE("make_signed")
{
    // test_make_signed<
    //         Enum, phi::conditional<sizeof(Enum) == sizeof(int), int,  char>>();

    test_make_signed<void>();
    test_make_signed<phi::nullptr_t>();
    test_make_signed<bool>();
    test_make_signed<char, signed char>();
    test_make_signed<signed char>();
    test_make_signed<unsigned char, signed char>();
    test_make_signed<short>();
    test_make_signed<unsigned short, short>();
    test_make_signed<int>();
    test_make_signed<unsigned int, int>();
    test_make_signed<long>();
    test_make_signed<unsigned long, long>();
    test_make_signed<long long>();
    test_make_signed<unsigned long long, long long>();
    test_make_signed<float>();
    test_make_signed<double>();
    test_make_signed<long double>();
    //test_make_signed<char8_t>();
    //test_make_signed<char16_t>();
    //test_make_signed<char32_t>();
    //test_make_signed<wchar_t>();

    test_make_signed<phi::boolean>();
    test_make_signed<phi::integer<signed char>>();
    test_make_signed<phi::integer<unsigned char>, phi::integer<signed char>>();
    test_make_signed<phi::integer<short>>();
    test_make_signed<phi::integer<unsigned short>, phi::integer<short>>();
    test_make_signed<phi::integer<int>>();
    test_make_signed<phi::integer<unsigned int>, phi::integer<int>>();
    test_make_signed<phi::integer<long>>();
    test_make_signed<phi::integer<unsigned long>, phi::integer<long>>();
    test_make_signed<phi::integer<long long>>();
    test_make_signed<phi::integer<unsigned long long>, phi::integer<long long>>();
    test_make_signed<phi::floating_point<float>>();
    test_make_signed<phi::floating_point<double>>();
    test_make_signed<phi::floating_point<long double>>();

    test_make_signed<std::vector<int>>();
    test_make_signed<phi::scope_ptr<int>>();

    test_make_signed<int&>();
    test_make_signed<const int&>();
    test_make_signed<volatile int&>();
    test_make_signed<const volatile int&>();
    test_make_signed<int&&>();
    test_make_signed<const int&&>();
    test_make_signed<volatile int&&>();
    test_make_signed<const volatile int&&>();
    test_make_signed<int*>();
    test_make_signed<const int*>();
    test_make_signed<volatile int*>();
    test_make_signed<const volatile int*>();
    test_make_signed<int**>();
    test_make_signed<const int**>();
    test_make_signed<volatile int**>();
    test_make_signed<const volatile int**>();
    test_make_signed<int*&>();
    test_make_signed<const int*&>();
    test_make_signed<volatile int*&>();
    test_make_signed<const volatile int*&>();
    test_make_signed<int*&&>();
    test_make_signed<const int*&&>();
    test_make_signed<volatile int*&&>();
    test_make_signed<const volatile int*&&>();
    test_make_signed<void*>();
    test_make_signed<char[3]>();
    test_make_signed<char[]>();
    test_make_signed<char* [3]>();
    test_make_signed<char*[]>();
    test_make_signed<int(*)[3]>();
    test_make_signed<int(*)[]>();
    test_make_signed<int(&)[3]>();
    test_make_signed<int(&)[]>();
    test_make_signed<int(&&)[3]>();
    test_make_signed<int(&&)[]>();
    test_make_signed<char[3][2]>();
    test_make_signed<char[][2]>();
    test_make_signed<char* [3][2]>();
    test_make_signed<char*[][2]>();
    test_make_signed<int(*)[3][2]>();
    test_make_signed<int(*)[][2]>();
    test_make_signed<int(&)[3][2]>();
    test_make_signed<int(&)[][2]>();
    test_make_signed<int(&&)[3][2]>();
    test_make_signed<int(&&)[][2]>();
    test_make_signed<class_type>();
    test_make_signed<class_type[]>();
    test_make_signed<class_type[2]>();
    test_make_signed<template_type<void>>();
    test_make_signed<template_type<int>>();
    test_make_signed<template_type<class_type>>();
    test_make_signed<template_type<incomplete_type>>();
    test_make_signed<variadic_template<>>();
    test_make_signed<variadic_template<void>>();
    test_make_signed<variadic_template<int>>();
    test_make_signed<variadic_template<class_type>>();
    test_make_signed<variadic_template<incomplete_type>>();
    test_make_signed<variadic_template<int, void, class_type, volatile char[]>>();
    test_make_signed<public_derived_from<base>>();
    test_make_signed<public_derived_from<derived>>();
    test_make_signed<public_derived_from<class_type>>();
    test_make_signed<private_derived_from<base>>();
    test_make_signed<private_derived_from<derived>>();
    test_make_signed<private_derived_from<class_type>>();
    test_make_signed<protected_derived_from<base>>();
    test_make_signed<protected_derived_from<derived>>();
    test_make_signed<protected_derived_from<class_type>>();
    test_make_signed<union_type>();
    test_make_signed<non_empty_union>();
    test_make_signed<empty>();
    test_make_signed<not_empty>();
    test_make_signed<bit_zero>();
    test_make_signed<bit_one>();
    test_make_signed<base>();
    test_make_signed<derived>();
    test_make_signed<abstract>();
    test_make_signed<public_abstract>();
    test_make_signed<private_abstract>();
    test_make_signed<protected_abstract>();
    test_make_signed<abstract_template<int>>();
    test_make_signed<abstract_template<double>>();
    test_make_signed<abstract_template<class_type>>();
    test_make_signed<abstract_template<incomplete_type>>();
    test_make_signed<final_type>();
    test_make_signed<public_destructor>();
    test_make_signed<protected_destructor>();
    test_make_signed<private_destructor>();
    test_make_signed<virtual_public_destructor>();
    test_make_signed<virtual_protected_destructor>();
    test_make_signed<virtual_private_destructor>();
    test_make_signed<pure_public_destructor>();
    test_make_signed<pure_protected_destructor>();
    test_make_signed<pure_private_destructor>();
    test_make_signed<deleted_public_destructor>();
    test_make_signed<deleted_protected_destructor>();
    test_make_signed<deleted_private_destructor>();
    test_make_signed<deleted_virtual_public_destructor>();
    test_make_signed<deleted_virtual_protected_destructor>();
    test_make_signed<deleted_virtual_private_destructor>();
    //test_make_signed<Enum>();
    //test_make_signed<EnumSigned>();
    //test_make_signed<EnumUnsigned>();
    //test_make_signed<EnumClass>();
    //test_make_signed<EnumStruct>();
    test_make_signed<function_type>();
    test_make_signed<function_ptr>();
    test_make_signed<member_object_ptr>();
    test_make_signed<member_function_ptr>();
    test_make_signed<incomplete_type>();
    test_make_signed<incomplete_template<void>>();
    test_make_signed<incomplete_template<int>>();
    test_make_signed<incomplete_template<class_type>>();
    test_make_signed<incomplete_template<incomplete_type>>();
    test_make_signed<incomplete_variadic_template<>>();
    test_make_signed<incomplete_variadic_template<void>>();
    test_make_signed<incomplete_variadic_template<int>>();
    test_make_signed<incomplete_variadic_template<class_type>>();
    test_make_signed<incomplete_variadic_template<incomplete_type>>();
    test_make_signed<incomplete_variadic_template<int, void, class_type, volatile char[]>>();
    test_make_signed<int class_type::*>();
    test_make_signed<float class_type::*>();
    test_make_signed<void * class_type::*>();
    test_make_signed<int * class_type::*>();
    test_make_signed<int class_type::*&>();
    test_make_signed<float class_type::*&>();
    test_make_signed<void * class_type::*&>();
    test_make_signed<int * class_type::*&>();
    test_make_signed<int class_type::*&&>();
    test_make_signed<float class_type::*&&>();
    test_make_signed<void * class_type::*&&>();
    test_make_signed<int * class_type::*&&>();
    test_make_signed<int class_type::* const>();
    test_make_signed<float class_type::* const>();
    test_make_signed<void * class_type::* const>();
    test_make_signed<int class_type::* const&>();
    test_make_signed<float class_type::* const&>();
    test_make_signed<void * class_type::* const&>();
    test_make_signed<int class_type::* const&&>();
    test_make_signed<float class_type::* const&&>();
    test_make_signed<void * class_type::* const&&>();
    test_make_signed<int class_type::* volatile>();
    test_make_signed<float class_type::* volatile>();
    test_make_signed<void * class_type::* volatile>();
    test_make_signed<int class_type::* volatile&>();
    test_make_signed<float class_type::* volatile&>();
    test_make_signed<void * class_type::* volatile&>();
    test_make_signed<int class_type::* volatile&&>();
    test_make_signed<float class_type::* volatile&&>();
    test_make_signed<void * class_type::* volatile&&>();
    test_make_signed<int class_type::* const volatile>();
    test_make_signed<float class_type::* const volatile>();
    test_make_signed<void * class_type::* const volatile>();
    test_make_signed<int class_type::* const volatile&>();
    test_make_signed<float class_type::* const volatile&>();
    test_make_signed<void * class_type::* const volatile&>();
    test_make_signed<int class_type::* const volatile&&>();
    test_make_signed<float class_type::* const volatile&&>();
    test_make_signed<void * class_type::* const volatile&&>();
    test_make_signed<non_copyable>();
    test_make_signed<non_moveable>();
    test_make_signed<non_constructible>();
    test_make_signed<tracked>();
    test_make_signed<trap_constructible>();
    test_make_signed<trap_implicit_conversion>();
    test_make_signed<trap_comma>();
    test_make_signed<trap_call>();
    test_make_signed<trap_self_assign>();
    test_make_signed<trap_deref>();
    test_make_signed<trap_array_subscript>();

    test_make_signed<void()>();
    test_make_signed<void()&>();
    test_make_signed<void() &&>();
    test_make_signed<void() const>();
    test_make_signed<void() const&>();
    test_make_signed<void() const&&>();
    test_make_signed<void() volatile>();
    test_make_signed<void() volatile&>();
    test_make_signed<void() volatile&&>();
    test_make_signed<void() const volatile>();
    test_make_signed<void() const volatile&>();
    test_make_signed<void() const volatile&&>();
    test_make_signed<void() noexcept>();
    test_make_signed<void() & noexcept>();
    test_make_signed<void() && noexcept>();
    test_make_signed<void() const noexcept>();
    test_make_signed<void() const & noexcept>();
    test_make_signed<void() const && noexcept>();
    test_make_signed<void() volatile noexcept>();
    test_make_signed<void() volatile & noexcept>();
    test_make_signed<void() volatile && noexcept>();
    test_make_signed<void() const volatile noexcept>();
    test_make_signed<void() const volatile & noexcept>();
    test_make_signed<void() const volatile && noexcept>();

    test_make_signed<void(int)>();
    test_make_signed<void(int)&>();
    test_make_signed<void(int) &&>();
    test_make_signed<void(int) const>();
    test_make_signed<void(int) const&>();
    test_make_signed<void(int) const&&>();
    test_make_signed<void(int) volatile>();
    test_make_signed<void(int) volatile&>();
    test_make_signed<void(int) volatile&&>();
    test_make_signed<void(int) const volatile>();
    test_make_signed<void(int) const volatile&>();
    test_make_signed<void(int) const volatile&&>();
    test_make_signed<void(int) noexcept>();
    test_make_signed<void(int) & noexcept>();
    test_make_signed<void(int) && noexcept>();
    test_make_signed<void(int) const noexcept>();
    test_make_signed<void(int) const & noexcept>();
    test_make_signed<void(int) const && noexcept>();
    test_make_signed<void(int) volatile noexcept>();
    test_make_signed<void(int) volatile & noexcept>();
    test_make_signed<void(int) volatile && noexcept>();
    test_make_signed<void(int) const volatile noexcept>();
    test_make_signed<void(int) const volatile & noexcept>();
    test_make_signed<void(int) const volatile && noexcept>();

    test_make_signed<void(...)>();
    test_make_signed<void(...)&>();
    test_make_signed<void(...) &&>();
    test_make_signed<void(...) const>();
    test_make_signed<void(...) const&>();
    test_make_signed<void(...) const&&>();
    test_make_signed<void(...) volatile>();
    test_make_signed<void(...) volatile&>();
    test_make_signed<void(...) volatile&&>();
    test_make_signed<void(...) const volatile>();
    test_make_signed<void(...) const volatile&>();
    test_make_signed<void(...) const volatile&&>();
    test_make_signed<void(...) noexcept>();
    test_make_signed<void(...) & noexcept>();
    test_make_signed<void(...) && noexcept>();
    test_make_signed<void(...) const noexcept>();
    test_make_signed<void(...) const & noexcept>();
    test_make_signed<void(...) const && noexcept>();
    test_make_signed<void(...) volatile noexcept>();
    test_make_signed<void(...) volatile & noexcept>();
    test_make_signed<void(...) volatile && noexcept>();
    test_make_signed<void(...) const volatile noexcept>();
    test_make_signed<void(...) const volatile & noexcept>();
    test_make_signed<void(...) const volatile && noexcept>();

    test_make_signed<void(int, ...)>();
    test_make_signed<void(int, ...)&>();
    test_make_signed<void(int, ...) &&>();
    test_make_signed<void(int, ...) const>();
    test_make_signed<void(int, ...) const&>();
    test_make_signed<void(int, ...) const&&>();
    test_make_signed<void(int, ...) volatile>();
    test_make_signed<void(int, ...) volatile&>();
    test_make_signed<void(int, ...) volatile&&>();
    test_make_signed<void(int, ...) const volatile>();
    test_make_signed<void(int, ...) const volatile&>();
    test_make_signed<void(int, ...) const volatile&&>();
    test_make_signed<void(int, ...) noexcept>();
    test_make_signed<void(int, ...) & noexcept>();
    test_make_signed<void(int, ...) && noexcept>();
    test_make_signed<void(int, ...) const noexcept>();
    test_make_signed<void(int, ...) const & noexcept>();
    test_make_signed<void(int, ...) const && noexcept>();
    test_make_signed<void(int, ...) volatile noexcept>();
    test_make_signed<void(int, ...) volatile & noexcept>();
    test_make_signed<void(int, ...) volatile && noexcept>();
    test_make_signed<void(int, ...) const volatile noexcept>();
    test_make_signed<void(int, ...) const volatile & noexcept>();
    test_make_signed<void(int, ...) const volatile && noexcept>();

    test_make_signed<int()>();
    test_make_signed<int()&>();
    test_make_signed<int() &&>();
    test_make_signed<int() const>();
    test_make_signed<int() const&>();
    test_make_signed<int() const&&>();
    test_make_signed<int() volatile>();
    test_make_signed<int() volatile&>();
    test_make_signed<int() volatile&&>();
    test_make_signed<int() const volatile>();
    test_make_signed<int() const volatile&>();
    test_make_signed<int() const volatile&&>();
    test_make_signed<int() noexcept>();
    test_make_signed<int() & noexcept>();
    test_make_signed<int() && noexcept>();
    test_make_signed<int() const noexcept>();
    test_make_signed<int() const & noexcept>();
    test_make_signed<int() const && noexcept>();
    test_make_signed<int() volatile noexcept>();
    test_make_signed<int() volatile & noexcept>();
    test_make_signed<int() volatile && noexcept>();
    test_make_signed<int() const volatile noexcept>();
    test_make_signed<int() const volatile & noexcept>();
    test_make_signed<int() const volatile && noexcept>();

    test_make_signed<int(int)>();
    test_make_signed<int(int)&>();
    test_make_signed<int(int) &&>();
    test_make_signed<int(int) const>();
    test_make_signed<int(int) const&>();
    test_make_signed<int(int) const&&>();
    test_make_signed<int(int) volatile>();
    test_make_signed<int(int) volatile&>();
    test_make_signed<int(int) volatile&&>();
    test_make_signed<int(int) const volatile>();
    test_make_signed<int(int) const volatile&>();
    test_make_signed<int(int) const volatile&&>();
    test_make_signed<int(int) noexcept>();
    test_make_signed<int(int) & noexcept>();
    test_make_signed<int(int) && noexcept>();
    test_make_signed<int(int) const noexcept>();
    test_make_signed<int(int) const & noexcept>();
    test_make_signed<int(int) const && noexcept>();
    test_make_signed<int(int) volatile noexcept>();
    test_make_signed<int(int) volatile & noexcept>();
    test_make_signed<int(int) volatile && noexcept>();
    test_make_signed<int(int) const volatile noexcept>();
    test_make_signed<int(int) const volatile & noexcept>();
    test_make_signed<int(int) const volatile && noexcept>();

    test_make_signed<int(...)>();
    test_make_signed<int(...)&>();
    test_make_signed<int(...) &&>();
    test_make_signed<int(...) const>();
    test_make_signed<int(...) const&>();
    test_make_signed<int(...) const&&>();
    test_make_signed<int(...) volatile>();
    test_make_signed<int(...) volatile&>();
    test_make_signed<int(...) volatile&&>();
    test_make_signed<int(...) const volatile>();
    test_make_signed<int(...) const volatile&>();
    test_make_signed<int(...) const volatile&&>();
    test_make_signed<int(...) noexcept>();
    test_make_signed<int(...) & noexcept>();
    test_make_signed<int(...) && noexcept>();
    test_make_signed<int(...) const noexcept>();
    test_make_signed<int(...) const & noexcept>();
    test_make_signed<int(...) const && noexcept>();
    test_make_signed<int(...) volatile noexcept>();
    test_make_signed<int(...) volatile & noexcept>();
    test_make_signed<int(...) volatile && noexcept>();
    test_make_signed<int(...) const volatile noexcept>();
    test_make_signed<int(...) const volatile & noexcept>();
    test_make_signed<int(...) const volatile && noexcept>();

    test_make_signed<int(int, ...)>();
    test_make_signed<int(int, ...)&>();
    test_make_signed<int(int, ...) &&>();
    test_make_signed<int(int, ...) const>();
    test_make_signed<int(int, ...) const&>();
    test_make_signed<int(int, ...) const&&>();
    test_make_signed<int(int, ...) volatile>();
    test_make_signed<int(int, ...) volatile&>();
    test_make_signed<int(int, ...) volatile&&>();
    test_make_signed<int(int, ...) const volatile>();
    test_make_signed<int(int, ...) const volatile&>();
    test_make_signed<int(int, ...) const volatile&&>();
    test_make_signed<int(int, ...) noexcept>();
    test_make_signed<int(int, ...) & noexcept>();
    test_make_signed<int(int, ...) && noexcept>();
    test_make_signed<int(int, ...) const noexcept>();
    test_make_signed<int(int, ...) const & noexcept>();
    test_make_signed<int(int, ...) const && noexcept>();
    test_make_signed<int(int, ...) volatile noexcept>();
    test_make_signed<int(int, ...) volatile & noexcept>();
    test_make_signed<int(int, ...) volatile && noexcept>();
    test_make_signed<int(int, ...) const volatile noexcept>();
    test_make_signed<int(int, ...) const volatile & noexcept>();
    test_make_signed<int(int, ...) const volatile && noexcept>();

    test_make_signed<void (*)()>();
    test_make_signed<void (*)() noexcept>();

    test_make_signed<void (*)(int)>();
    test_make_signed<void (*)(int) noexcept>();

    test_make_signed<void (*)(...)>();
    test_make_signed<void (*)(...) noexcept>();

    test_make_signed<void (*)(int, ...)>();
    test_make_signed<void (*)(int, ...) noexcept>();

    test_make_signed<int (*)()>();
    test_make_signed<int (*)() noexcept>();

    test_make_signed<int (*)(int)>();
    test_make_signed<int (*)(int) noexcept>();

    test_make_signed<int (*)(...)>();
    test_make_signed<int (*)(...) noexcept>();

    test_make_signed<int (*)(int, ...)>();
    test_make_signed<int (*)(int, ...) noexcept>();

    test_make_signed<void (&)()>();
    test_make_signed<void (&)() noexcept>();

    test_make_signed<void (&)(int)>();
    test_make_signed<void (&)(int) noexcept>();

    test_make_signed<void (&)(...)>();
    test_make_signed<void (&)(...) noexcept>();

    test_make_signed<void (&)(int, ...)>();
    test_make_signed<void (&)(int, ...) noexcept>();

    test_make_signed<int (&)()>();
    test_make_signed<int (&)() noexcept>();

    test_make_signed<int (&)(int)>();
    test_make_signed<int (&)(int) noexcept>();

    test_make_signed<int (&)(...)>();
    test_make_signed<int (&)(...) noexcept>();

    test_make_signed<int (&)(int, ...)>();
    test_make_signed<int (&)(int, ...) noexcept>();

    test_make_signed<void (&&)()>();
    test_make_signed<void (&&)() noexcept>();

    test_make_signed<void (&&)(int)>();
    test_make_signed<void (&&)(int) noexcept>();

    test_make_signed<void (&&)(...)>();
    test_make_signed<void (&&)(...) noexcept>();

    test_make_signed<void (&&)(int, ...)>();
    test_make_signed<void (&&)(int, ...) noexcept>();

    test_make_signed<int (&&)()>();
    test_make_signed<int (&&)() noexcept>();

    test_make_signed<int (&&)(int)>();
    test_make_signed<int (&&)(int) noexcept>();

    test_make_signed<int (&&)(...)>();
    test_make_signed<int (&&)(...) noexcept>();

    test_make_signed<int (&&)(int, ...)>();
    test_make_signed<int (&&)(int, ...) noexcept>();

    test_make_signed<void (class_type::*)()>();
    test_make_signed<void (class_type::*)()&>();
    test_make_signed<void (class_type::*)() &&>();
    test_make_signed<void (class_type::*)() const>();
    test_make_signed<void (class_type::*)() const&>();
    test_make_signed<void (class_type::*)() const&&>();
    test_make_signed<void (class_type::*)() noexcept>();
    test_make_signed<void (class_type::*)() & noexcept>();
    test_make_signed<void (class_type::*)() && noexcept>();
    test_make_signed<void (class_type::*)() const noexcept>();
    test_make_signed<void (class_type::*)() const & noexcept>();
    test_make_signed<void (class_type::*)() const && noexcept>();

    test_make_signed<void (class_type::*)(int)>();
    test_make_signed<void (class_type::*)(int)&>();
    test_make_signed<void (class_type::*)(int) &&>();
    test_make_signed<void (class_type::*)(int) const>();
    test_make_signed<void (class_type::*)(int) const&>();
    test_make_signed<void (class_type::*)(int) const&&>();
    test_make_signed<void (class_type::*)(int) noexcept>();
    test_make_signed<void (class_type::*)(int) & noexcept>();
    test_make_signed<void (class_type::*)(int) && noexcept>();
    test_make_signed<void (class_type::*)(int) const noexcept>();
    test_make_signed<void (class_type::*)(int) const & noexcept>();
    test_make_signed<void (class_type::*)(int) const && noexcept>();

    test_make_signed<void (class_type::*)(...)>();
    test_make_signed<void (class_type::*)(...)&>();
    test_make_signed<void (class_type::*)(...) &&>();
    test_make_signed<void (class_type::*)(...) const>();
    test_make_signed<void (class_type::*)(...) const&>();
    test_make_signed<void (class_type::*)(...) const&&>();
    test_make_signed<void (class_type::*)(...) noexcept>();
    test_make_signed<void (class_type::*)(...) & noexcept>();
    test_make_signed<void (class_type::*)(...) && noexcept>();
    test_make_signed<void (class_type::*)(...) const noexcept>();
    test_make_signed<void (class_type::*)(...) const & noexcept>();
    test_make_signed<void (class_type::*)(...) const && noexcept>();

    test_make_signed<void (class_type::*)(int, ...)>();
    test_make_signed<void (class_type::*)(int, ...)&>();
    test_make_signed<void (class_type::*)(int, ...) &&>();
    test_make_signed<void (class_type::*)(int, ...) const>();
    test_make_signed<void (class_type::*)(int, ...) const&>();
    test_make_signed<void (class_type::*)(int, ...) const&&>();
    test_make_signed<void (class_type::*)(int, ...) noexcept>();
    test_make_signed<void (class_type::*)(int, ...) & noexcept>();
    test_make_signed<void (class_type::*)(int, ...) && noexcept>();
    test_make_signed<void (class_type::*)(int, ...) const noexcept>();
    test_make_signed<void (class_type::*)(int, ...) const & noexcept>();
    test_make_signed<void (class_type::*)(int, ...) const && noexcept>();

    test_make_signed<int (class_type::*)()>();
    test_make_signed<int (class_type::*)()&>();
    test_make_signed<int (class_type::*)() &&>();
    test_make_signed<int (class_type::*)() const>();
    test_make_signed<int (class_type::*)() const&>();
    test_make_signed<int (class_type::*)() const&&>();
    test_make_signed<int (class_type::*)() noexcept>();
    test_make_signed<int (class_type::*)() & noexcept>();
    test_make_signed<int (class_type::*)() && noexcept>();
    test_make_signed<int (class_type::*)() const noexcept>();
    test_make_signed<int (class_type::*)() const & noexcept>();
    test_make_signed<int (class_type::*)() const && noexcept>();

    test_make_signed<int (class_type::*)(int)>();
    test_make_signed<int (class_type::*)(int)&>();
    test_make_signed<int (class_type::*)(int) &&>();
    test_make_signed<int (class_type::*)(int) const>();
    test_make_signed<int (class_type::*)(int) const&>();
    test_make_signed<int (class_type::*)(int) const&&>();
    test_make_signed<int (class_type::*)(int) noexcept>();
    test_make_signed<int (class_type::*)(int) & noexcept>();
    test_make_signed<int (class_type::*)(int) && noexcept>();
    test_make_signed<int (class_type::*)(int) const noexcept>();
    test_make_signed<int (class_type::*)(int) const & noexcept>();
    test_make_signed<int (class_type::*)(int) const && noexcept>();

    test_make_signed<int (class_type::*)(...)>();
    test_make_signed<int (class_type::*)(...)&>();
    test_make_signed<int (class_type::*)(...) &&>();
    test_make_signed<int (class_type::*)(...) const>();
    test_make_signed<int (class_type::*)(...) const&>();
    test_make_signed<int (class_type::*)(...) const&&>();
    test_make_signed<int (class_type::*)(...) noexcept>();
    test_make_signed<int (class_type::*)(...) & noexcept>();
    test_make_signed<int (class_type::*)(...) && noexcept>();
    test_make_signed<int (class_type::*)(...) const noexcept>();
    test_make_signed<int (class_type::*)(...) const & noexcept>();
    test_make_signed<int (class_type::*)(...) const && noexcept>();

    test_make_signed<int (class_type::*)(int, ...)>();
    test_make_signed<int (class_type::*)(int, ...)&>();
    test_make_signed<int (class_type::*)(int, ...) &&>();
    test_make_signed<int (class_type::*)(int, ...) const>();
    test_make_signed<int (class_type::*)(int, ...) const&>();
    test_make_signed<int (class_type::*)(int, ...) const&&>();
    test_make_signed<int (class_type::*)(int, ...) noexcept>();
    test_make_signed<int (class_type::*)(int, ...) & noexcept>();
    test_make_signed<int (class_type::*)(int, ...) && noexcept>();
    test_make_signed<int (class_type::*)(int, ...) const noexcept>();
    test_make_signed<int (class_type::*)(int, ...) const & noexcept>();
    test_make_signed<int (class_type::*)(int, ...) const && noexcept>();
}
