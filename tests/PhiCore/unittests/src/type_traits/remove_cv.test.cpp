#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/remove_cv.hpp>
#include <type_traits>
#include <vector>

template <typename TypeT, typename ExpectedT>
void test_remove_cv_impl()
{
    CHECK_SAME_TYPE(typename phi::remove_cv<TypeT>::type, ExpectedT);
    CHECK_SAME_TYPE(phi::remove_cv_t<TypeT>, ExpectedT);

    // Standard compatibility
    CHECK_SAME_TYPE(typename std::remove_cv<TypeT>::type, ExpectedT);
}

template <typename TypeT, typename ExpectedT = TypeT>
void test_remove_cv()
{
    test_remove_cv_impl<TypeT, ExpectedT>();
    test_remove_cv_impl<const TypeT, ExpectedT>();
    test_remove_cv_impl<volatile TypeT, ExpectedT>();
    test_remove_cv_impl<const volatile TypeT, ExpectedT>();
}

TEST_CASE("remove_cv")
{
    test_remove_cv<void>();
    test_remove_cv<phi::nullptr_t>();
    test_remove_cv<bool>();
    test_remove_cv<char>();
    test_remove_cv<signed char>();
    test_remove_cv<unsigned char>();
    test_remove_cv<short>();
    test_remove_cv<unsigned short>();
    test_remove_cv<int>();
    test_remove_cv<unsigned int>();
    test_remove_cv<long>();
    test_remove_cv<unsigned long>();
    test_remove_cv<long long>();
    test_remove_cv<unsigned long long>();
    test_remove_cv<float>();
    test_remove_cv<double>();
    test_remove_cv<long double>();
    test_remove_cv<char8_t>();
    test_remove_cv<char16_t>();
    test_remove_cv<char32_t>();
    test_remove_cv<wchar_t>();

    test_remove_cv<phi::boolean>();
    test_remove_cv<phi::integer<signed char>>();
    test_remove_cv<phi::integer<unsigned char>>();
    test_remove_cv<phi::integer<short>>();
    test_remove_cv<phi::integer<unsigned short>>();
    test_remove_cv<phi::integer<int>>();
    test_remove_cv<phi::integer<unsigned int>>();
    test_remove_cv<phi::integer<long>>();
    test_remove_cv<phi::integer<unsigned long>>();
    test_remove_cv<phi::integer<long long>>();
    test_remove_cv<phi::integer<unsigned long long>>();
    test_remove_cv<phi::floating_point<float>>();
    test_remove_cv<phi::floating_point<double>>();
    test_remove_cv<phi::floating_point<long double>>();

    test_remove_cv<std::vector<int>>();
    test_remove_cv<phi::scope_ptr<int>>();

    test_remove_cv<int&>();
    test_remove_cv<const int&>();
    test_remove_cv<volatile int&>();
    test_remove_cv<const volatile int&>();
    test_remove_cv<int&&>();
    test_remove_cv<const int&&>();
    test_remove_cv<volatile int&&>();
    test_remove_cv<const volatile int&&>();
    test_remove_cv<int*>();
    test_remove_cv<const int*>();
    test_remove_cv<volatile int*>();
    test_remove_cv<const volatile int*>();
    test_remove_cv<int**>();
    test_remove_cv<const int**>();
    test_remove_cv<volatile int**>();
    test_remove_cv<const volatile int**>();
    test_remove_cv<int*&>();
    test_remove_cv<const int*&>();
    test_remove_cv<volatile int*&>();
    test_remove_cv<const volatile int*&>();
    test_remove_cv<int*&&>();
    test_remove_cv<const int*&&>();
    test_remove_cv<volatile int*&&>();
    test_remove_cv<const volatile int*&&>();
    test_remove_cv<void*>();
    test_remove_cv<char[3]>();
    test_remove_cv<char[]>();
    test_remove_cv<char* [3]>();
    test_remove_cv<char*[]>();
    test_remove_cv<int(*)[3]>();
    test_remove_cv<int(*)[]>();
    test_remove_cv<int(&)[3]>();
    test_remove_cv<int(&)[]>();
    test_remove_cv<int(&&)[3]>();
    test_remove_cv<int(&&)[]>();
    test_remove_cv<char[3][2]>();
    test_remove_cv<char[][2]>();
    test_remove_cv<char* [3][2]>();
    test_remove_cv<char*[][2]>();
    test_remove_cv<int(*)[3][2]>();
    test_remove_cv<int(*)[][2]>();
    test_remove_cv<int(&)[3][2]>();
    test_remove_cv<int(&)[][2]>();
    test_remove_cv<int(&&)[3][2]>();
    test_remove_cv<int(&&)[][2]>();
    test_remove_cv<class_type>();
    test_remove_cv<class_type[]>();
    test_remove_cv<class_type[2]>();
    test_remove_cv<template_type<void>>();
    test_remove_cv<template_type<int>>();
    test_remove_cv<template_type<class_type>>();
    test_remove_cv<template_type<incomplete_type>>();
    test_remove_cv<variadic_template<>>();
    test_remove_cv<variadic_template<void>>();
    test_remove_cv<variadic_template<int>>();
    test_remove_cv<variadic_template<class_type>>();
    test_remove_cv<variadic_template<incomplete_type>>();
    test_remove_cv<variadic_template<int, void, class_type, volatile char[]>>();
    test_remove_cv<public_derived_from<base>>();
    test_remove_cv<public_derived_from<derived>>();
    test_remove_cv<public_derived_from<class_type>>();
    test_remove_cv<private_derived_from<base>>();
    test_remove_cv<private_derived_from<derived>>();
    test_remove_cv<private_derived_from<class_type>>();
    test_remove_cv<protected_derived_from<base>>();
    test_remove_cv<protected_derived_from<derived>>();
    test_remove_cv<protected_derived_from<class_type>>();
    test_remove_cv<union_type>();
    test_remove_cv<non_empty_union>();
    test_remove_cv<empty>();
    test_remove_cv<not_empty>();
    test_remove_cv<bit_zero>();
    test_remove_cv<bit_one>();
    test_remove_cv<base>();
    test_remove_cv<derived>();
    test_remove_cv<abstract>();
    test_remove_cv<public_abstract>();
    test_remove_cv<private_abstract>();
    test_remove_cv<protected_abstract>();
    test_remove_cv<abstract_template<int>>();
    test_remove_cv<abstract_template<double>>();
    test_remove_cv<abstract_template<class_type>>();
    test_remove_cv<abstract_template<incomplete_type>>();
    test_remove_cv<final_type>();
    test_remove_cv<public_destructor>();
    test_remove_cv<protected_destructor>();
    test_remove_cv<private_destructor>();
    test_remove_cv<virtual_public_destructor>();
    test_remove_cv<virtual_protected_destructor>();
    test_remove_cv<virtual_private_destructor>();
    test_remove_cv<pure_public_destructor>();
    test_remove_cv<pure_protected_destructor>();
    test_remove_cv<pure_private_destructor>();
    test_remove_cv<deleted_public_destructor>();
    test_remove_cv<deleted_protected_destructor>();
    test_remove_cv<deleted_private_destructor>();
    test_remove_cv<deleted_virtual_public_destructor>();
    test_remove_cv<deleted_virtual_protected_destructor>();
    test_remove_cv<deleted_virtual_private_destructor>();
    test_remove_cv<Enum>();
    test_remove_cv<EnumSigned>();
    test_remove_cv<EnumUnsigned>();
    test_remove_cv<EnumClass>();
    test_remove_cv<EnumStruct>();
    test_remove_cv<function_type>();
    test_remove_cv<function_ptr>();
    test_remove_cv<member_object_ptr>();
    test_remove_cv<member_function_ptr>();
    test_remove_cv<incomplete_type>();
    test_remove_cv<incomplete_template<void>>();
    test_remove_cv<incomplete_template<int>>();
    test_remove_cv<incomplete_template<class_type>>();
    test_remove_cv<incomplete_template<incomplete_type>>();
    test_remove_cv<incomplete_variadic_template<>>();
    test_remove_cv<incomplete_variadic_template<void>>();
    test_remove_cv<incomplete_variadic_template<int>>();
    test_remove_cv<incomplete_variadic_template<class_type>>();
    test_remove_cv<incomplete_variadic_template<incomplete_type>>();
    test_remove_cv<incomplete_variadic_template<int, void, class_type, volatile char[]>>();
    test_remove_cv<int class_type::*>();
    test_remove_cv<float class_type::*>();
    test_remove_cv<void * class_type::*>();
    test_remove_cv<int * class_type::*>();
    test_remove_cv<int class_type::*&>();
    test_remove_cv<float class_type::*&>();
    test_remove_cv<void * class_type::*&>();
    test_remove_cv<int * class_type::*&>();
    test_remove_cv<int class_type::*&&>();
    test_remove_cv<float class_type::*&&>();
    test_remove_cv<void * class_type::*&&>();
    test_remove_cv<int * class_type::*&&>();
    test_remove_cv<int class_type::* const, int class_type::*>();
    test_remove_cv<float class_type::* const, float class_type::*>();
    test_remove_cv<void * class_type::* const, void * class_type::*>();
    test_remove_cv<int class_type::* const&>();
    test_remove_cv<float class_type::* const&>();
    test_remove_cv<void * class_type::* const&>();
    test_remove_cv<int class_type::* const&&>();
    test_remove_cv<float class_type::* const&&>();
    test_remove_cv<void * class_type::* const&&>();
    test_remove_cv<int class_type::* volatile, int class_type::*>();
    test_remove_cv<float class_type::* volatile, float class_type::*>();
    test_remove_cv<void * class_type::* volatile, void * class_type::*>();
    test_remove_cv<int class_type::* volatile&>();
    test_remove_cv<float class_type::* volatile&>();
    test_remove_cv<void * class_type::* volatile&>();
    test_remove_cv<int class_type::* volatile&&>();
    test_remove_cv<float class_type::* volatile&&>();
    test_remove_cv<void * class_type::* volatile&&>();
    test_remove_cv<int class_type::* const volatile, int class_type::*>();
    test_remove_cv<float class_type::* const volatile, float class_type::*>();
    test_remove_cv<void * class_type::* const volatile, void * class_type::*>();
    test_remove_cv<int class_type::* const volatile&>();
    test_remove_cv<float class_type::* const volatile&>();
    test_remove_cv<void * class_type::* const volatile&>();
    test_remove_cv<int class_type::* const volatile&&>();
    test_remove_cv<float class_type::* const volatile&&>();
    test_remove_cv<void * class_type::* const volatile&&>();
    test_remove_cv<non_copyable>();
    test_remove_cv<non_moveable>();
    test_remove_cv<non_constructible>();
    test_remove_cv<tracked>();
    test_remove_cv<trap_constructible>();
    test_remove_cv<trap_implicit_conversion>();
    test_remove_cv<trap_comma>();
    test_remove_cv<trap_call>();
    test_remove_cv<trap_self_assign>();
    test_remove_cv<trap_deref>();
    test_remove_cv<trap_array_subscript>();

    test_remove_cv<void()>();
    test_remove_cv<void()&>();
    test_remove_cv<void() &&>();
    test_remove_cv<void() const>();
    test_remove_cv<void() const&>();
    test_remove_cv<void() const&&>();
    test_remove_cv<void() volatile>();
    test_remove_cv<void() volatile&>();
    test_remove_cv<void() volatile&&>();
    test_remove_cv<void() const volatile>();
    test_remove_cv<void() const volatile&>();
    test_remove_cv<void() const volatile&&>();
    test_remove_cv<void() noexcept>();
    test_remove_cv<void() & noexcept>();
    test_remove_cv<void() && noexcept>();
    test_remove_cv<void() const noexcept>();
    test_remove_cv<void() const & noexcept>();
    test_remove_cv<void() const && noexcept>();
    test_remove_cv<void() volatile noexcept>();
    test_remove_cv<void() volatile & noexcept>();
    test_remove_cv<void() volatile && noexcept>();
    test_remove_cv<void() const volatile noexcept>();
    test_remove_cv<void() const volatile & noexcept>();
    test_remove_cv<void() const volatile && noexcept>();

    test_remove_cv<void(int)>();
    test_remove_cv<void(int)&>();
    test_remove_cv<void(int) &&>();
    test_remove_cv<void(int) const>();
    test_remove_cv<void(int) const&>();
    test_remove_cv<void(int) const&&>();
    test_remove_cv<void(int) volatile>();
    test_remove_cv<void(int) volatile&>();
    test_remove_cv<void(int) volatile&&>();
    test_remove_cv<void(int) const volatile>();
    test_remove_cv<void(int) const volatile&>();
    test_remove_cv<void(int) const volatile&&>();
    test_remove_cv<void(int) noexcept>();
    test_remove_cv<void(int) & noexcept>();
    test_remove_cv<void(int) && noexcept>();
    test_remove_cv<void(int) const noexcept>();
    test_remove_cv<void(int) const & noexcept>();
    test_remove_cv<void(int) const && noexcept>();
    test_remove_cv<void(int) volatile noexcept>();
    test_remove_cv<void(int) volatile & noexcept>();
    test_remove_cv<void(int) volatile && noexcept>();
    test_remove_cv<void(int) const volatile noexcept>();
    test_remove_cv<void(int) const volatile & noexcept>();
    test_remove_cv<void(int) const volatile && noexcept>();

    test_remove_cv<void(...)>();
    test_remove_cv<void(...)&>();
    test_remove_cv<void(...) &&>();
    test_remove_cv<void(...) const>();
    test_remove_cv<void(...) const&>();
    test_remove_cv<void(...) const&&>();
    test_remove_cv<void(...) volatile>();
    test_remove_cv<void(...) volatile&>();
    test_remove_cv<void(...) volatile&&>();
    test_remove_cv<void(...) const volatile>();
    test_remove_cv<void(...) const volatile&>();
    test_remove_cv<void(...) const volatile&&>();
    test_remove_cv<void(...) noexcept>();
    test_remove_cv<void(...) & noexcept>();
    test_remove_cv<void(...) && noexcept>();
    test_remove_cv<void(...) const noexcept>();
    test_remove_cv<void(...) const & noexcept>();
    test_remove_cv<void(...) const && noexcept>();
    test_remove_cv<void(...) volatile noexcept>();
    test_remove_cv<void(...) volatile & noexcept>();
    test_remove_cv<void(...) volatile && noexcept>();
    test_remove_cv<void(...) const volatile noexcept>();
    test_remove_cv<void(...) const volatile & noexcept>();
    test_remove_cv<void(...) const volatile && noexcept>();

    test_remove_cv<void(int, ...)>();
    test_remove_cv<void(int, ...)&>();
    test_remove_cv<void(int, ...) &&>();
    test_remove_cv<void(int, ...) const>();
    test_remove_cv<void(int, ...) const&>();
    test_remove_cv<void(int, ...) const&&>();
    test_remove_cv<void(int, ...) volatile>();
    test_remove_cv<void(int, ...) volatile&>();
    test_remove_cv<void(int, ...) volatile&&>();
    test_remove_cv<void(int, ...) const volatile>();
    test_remove_cv<void(int, ...) const volatile&>();
    test_remove_cv<void(int, ...) const volatile&&>();
    test_remove_cv<void(int, ...) noexcept>();
    test_remove_cv<void(int, ...) & noexcept>();
    test_remove_cv<void(int, ...) && noexcept>();
    test_remove_cv<void(int, ...) const noexcept>();
    test_remove_cv<void(int, ...) const & noexcept>();
    test_remove_cv<void(int, ...) const && noexcept>();
    test_remove_cv<void(int, ...) volatile noexcept>();
    test_remove_cv<void(int, ...) volatile & noexcept>();
    test_remove_cv<void(int, ...) volatile && noexcept>();
    test_remove_cv<void(int, ...) const volatile noexcept>();
    test_remove_cv<void(int, ...) const volatile & noexcept>();
    test_remove_cv<void(int, ...) const volatile && noexcept>();

    test_remove_cv<int()>();
    test_remove_cv<int()&>();
    test_remove_cv<int() &&>();
    test_remove_cv<int() const>();
    test_remove_cv<int() const&>();
    test_remove_cv<int() const&&>();
    test_remove_cv<int() volatile>();
    test_remove_cv<int() volatile&>();
    test_remove_cv<int() volatile&&>();
    test_remove_cv<int() const volatile>();
    test_remove_cv<int() const volatile&>();
    test_remove_cv<int() const volatile&&>();
    test_remove_cv<int() noexcept>();
    test_remove_cv<int() & noexcept>();
    test_remove_cv<int() && noexcept>();
    test_remove_cv<int() const noexcept>();
    test_remove_cv<int() const & noexcept>();
    test_remove_cv<int() const && noexcept>();
    test_remove_cv<int() volatile noexcept>();
    test_remove_cv<int() volatile & noexcept>();
    test_remove_cv<int() volatile && noexcept>();
    test_remove_cv<int() const volatile noexcept>();
    test_remove_cv<int() const volatile & noexcept>();
    test_remove_cv<int() const volatile && noexcept>();

    test_remove_cv<int(int)>();
    test_remove_cv<int(int)&>();
    test_remove_cv<int(int) &&>();
    test_remove_cv<int(int) const>();
    test_remove_cv<int(int) const&>();
    test_remove_cv<int(int) const&&>();
    test_remove_cv<int(int) volatile>();
    test_remove_cv<int(int) volatile&>();
    test_remove_cv<int(int) volatile&&>();
    test_remove_cv<int(int) const volatile>();
    test_remove_cv<int(int) const volatile&>();
    test_remove_cv<int(int) const volatile&&>();
    test_remove_cv<int(int) noexcept>();
    test_remove_cv<int(int) & noexcept>();
    test_remove_cv<int(int) && noexcept>();
    test_remove_cv<int(int) const noexcept>();
    test_remove_cv<int(int) const & noexcept>();
    test_remove_cv<int(int) const && noexcept>();
    test_remove_cv<int(int) volatile noexcept>();
    test_remove_cv<int(int) volatile & noexcept>();
    test_remove_cv<int(int) volatile && noexcept>();
    test_remove_cv<int(int) const volatile noexcept>();
    test_remove_cv<int(int) const volatile & noexcept>();
    test_remove_cv<int(int) const volatile && noexcept>();

    test_remove_cv<int(...)>();
    test_remove_cv<int(...)&>();
    test_remove_cv<int(...) &&>();
    test_remove_cv<int(...) const>();
    test_remove_cv<int(...) const&>();
    test_remove_cv<int(...) const&&>();
    test_remove_cv<int(...) volatile>();
    test_remove_cv<int(...) volatile&>();
    test_remove_cv<int(...) volatile&&>();
    test_remove_cv<int(...) const volatile>();
    test_remove_cv<int(...) const volatile&>();
    test_remove_cv<int(...) const volatile&&>();
    test_remove_cv<int(...) noexcept>();
    test_remove_cv<int(...) & noexcept>();
    test_remove_cv<int(...) && noexcept>();
    test_remove_cv<int(...) const noexcept>();
    test_remove_cv<int(...) const & noexcept>();
    test_remove_cv<int(...) const && noexcept>();
    test_remove_cv<int(...) volatile noexcept>();
    test_remove_cv<int(...) volatile & noexcept>();
    test_remove_cv<int(...) volatile && noexcept>();
    test_remove_cv<int(...) const volatile noexcept>();
    test_remove_cv<int(...) const volatile & noexcept>();
    test_remove_cv<int(...) const volatile && noexcept>();

    test_remove_cv<int(int, ...)>();
    test_remove_cv<int(int, ...)&>();
    test_remove_cv<int(int, ...) &&>();
    test_remove_cv<int(int, ...) const>();
    test_remove_cv<int(int, ...) const&>();
    test_remove_cv<int(int, ...) const&&>();
    test_remove_cv<int(int, ...) volatile>();
    test_remove_cv<int(int, ...) volatile&>();
    test_remove_cv<int(int, ...) volatile&&>();
    test_remove_cv<int(int, ...) const volatile>();
    test_remove_cv<int(int, ...) const volatile&>();
    test_remove_cv<int(int, ...) const volatile&&>();
    test_remove_cv<int(int, ...) noexcept>();
    test_remove_cv<int(int, ...) & noexcept>();
    test_remove_cv<int(int, ...) && noexcept>();
    test_remove_cv<int(int, ...) const noexcept>();
    test_remove_cv<int(int, ...) const & noexcept>();
    test_remove_cv<int(int, ...) const && noexcept>();
    test_remove_cv<int(int, ...) volatile noexcept>();
    test_remove_cv<int(int, ...) volatile & noexcept>();
    test_remove_cv<int(int, ...) volatile && noexcept>();
    test_remove_cv<int(int, ...) const volatile noexcept>();
    test_remove_cv<int(int, ...) const volatile & noexcept>();
    test_remove_cv<int(int, ...) const volatile && noexcept>();

    test_remove_cv<void (*)()>();
    test_remove_cv<void (*)() noexcept>();

    test_remove_cv<void (*)(int)>();
    test_remove_cv<void (*)(int) noexcept>();

    test_remove_cv<void (*)(...)>();
    test_remove_cv<void (*)(...) noexcept>();

    test_remove_cv<void (*)(int, ...)>();
    test_remove_cv<void (*)(int, ...) noexcept>();

    test_remove_cv<int (*)()>();
    test_remove_cv<int (*)() noexcept>();

    test_remove_cv<int (*)(int)>();
    test_remove_cv<int (*)(int) noexcept>();

    test_remove_cv<int (*)(...)>();
    test_remove_cv<int (*)(...) noexcept>();

    test_remove_cv<int (*)(int, ...)>();
    test_remove_cv<int (*)(int, ...) noexcept>();

    test_remove_cv<void (&)()>();
    test_remove_cv<void (&)() noexcept>();

    test_remove_cv<void (&)(int)>();
    test_remove_cv<void (&)(int) noexcept>();

    test_remove_cv<void (&)(...)>();
    test_remove_cv<void (&)(...) noexcept>();

    test_remove_cv<void (&)(int, ...)>();
    test_remove_cv<void (&)(int, ...) noexcept>();

    test_remove_cv<int (&)()>();
    test_remove_cv<int (&)() noexcept>();

    test_remove_cv<int (&)(int)>();
    test_remove_cv<int (&)(int) noexcept>();

    test_remove_cv<int (&)(...)>();
    test_remove_cv<int (&)(...) noexcept>();

    test_remove_cv<int (&)(int, ...)>();
    test_remove_cv<int (&)(int, ...) noexcept>();

    test_remove_cv<void (&&)()>();
    test_remove_cv<void (&&)() noexcept>();

    test_remove_cv<void (&&)(int)>();
    test_remove_cv<void (&&)(int) noexcept>();

    test_remove_cv<void (&&)(...)>();
    test_remove_cv<void (&&)(...) noexcept>();

    test_remove_cv<void (&&)(int, ...)>();
    test_remove_cv<void (&&)(int, ...) noexcept>();

    test_remove_cv<int (&&)()>();
    test_remove_cv<int (&&)() noexcept>();

    test_remove_cv<int (&&)(int)>();
    test_remove_cv<int (&&)(int) noexcept>();

    test_remove_cv<int (&&)(...)>();
    test_remove_cv<int (&&)(...) noexcept>();

    test_remove_cv<int (&&)(int, ...)>();
    test_remove_cv<int (&&)(int, ...) noexcept>();

    test_remove_cv<void (class_type::*)()>();
    test_remove_cv<void (class_type::*)()&>();
    test_remove_cv<void (class_type::*)() &&>();
    test_remove_cv<void (class_type::*)() const>();
    test_remove_cv<void (class_type::*)() const&>();
    test_remove_cv<void (class_type::*)() const&&>();
    test_remove_cv<void (class_type::*)() noexcept>();
    test_remove_cv<void (class_type::*)() & noexcept>();
    test_remove_cv<void (class_type::*)() && noexcept>();
    test_remove_cv<void (class_type::*)() const noexcept>();
    test_remove_cv<void (class_type::*)() const & noexcept>();
    test_remove_cv<void (class_type::*)() const && noexcept>();

    test_remove_cv<void (class_type::*)(int)>();
    test_remove_cv<void (class_type::*)(int)&>();
    test_remove_cv<void (class_type::*)(int) &&>();
    test_remove_cv<void (class_type::*)(int) const>();
    test_remove_cv<void (class_type::*)(int) const&>();
    test_remove_cv<void (class_type::*)(int) const&&>();
    test_remove_cv<void (class_type::*)(int) noexcept>();
    test_remove_cv<void (class_type::*)(int) & noexcept>();
    test_remove_cv<void (class_type::*)(int) && noexcept>();
    test_remove_cv<void (class_type::*)(int) const noexcept>();
    test_remove_cv<void (class_type::*)(int) const & noexcept>();
    test_remove_cv<void (class_type::*)(int) const && noexcept>();

    test_remove_cv<void (class_type::*)(...)>();
    test_remove_cv<void (class_type::*)(...)&>();
    test_remove_cv<void (class_type::*)(...) &&>();
    test_remove_cv<void (class_type::*)(...) const>();
    test_remove_cv<void (class_type::*)(...) const&>();
    test_remove_cv<void (class_type::*)(...) const&&>();
    test_remove_cv<void (class_type::*)(...) noexcept>();
    test_remove_cv<void (class_type::*)(...) & noexcept>();
    test_remove_cv<void (class_type::*)(...) && noexcept>();
    test_remove_cv<void (class_type::*)(...) const noexcept>();
    test_remove_cv<void (class_type::*)(...) const & noexcept>();
    test_remove_cv<void (class_type::*)(...) const && noexcept>();

    test_remove_cv<void (class_type::*)(int, ...)>();
    test_remove_cv<void (class_type::*)(int, ...)&>();
    test_remove_cv<void (class_type::*)(int, ...) &&>();
    test_remove_cv<void (class_type::*)(int, ...) const>();
    test_remove_cv<void (class_type::*)(int, ...) const&>();
    test_remove_cv<void (class_type::*)(int, ...) const&&>();
    test_remove_cv<void (class_type::*)(int, ...) noexcept>();
    test_remove_cv<void (class_type::*)(int, ...) & noexcept>();
    test_remove_cv<void (class_type::*)(int, ...) && noexcept>();
    test_remove_cv<void (class_type::*)(int, ...) const noexcept>();
    test_remove_cv<void (class_type::*)(int, ...) const & noexcept>();
    test_remove_cv<void (class_type::*)(int, ...) const && noexcept>();

    test_remove_cv<int (class_type::*)()>();
    test_remove_cv<int (class_type::*)()&>();
    test_remove_cv<int (class_type::*)() &&>();
    test_remove_cv<int (class_type::*)() const>();
    test_remove_cv<int (class_type::*)() const&>();
    test_remove_cv<int (class_type::*)() const&&>();
    test_remove_cv<int (class_type::*)() noexcept>();
    test_remove_cv<int (class_type::*)() & noexcept>();
    test_remove_cv<int (class_type::*)() && noexcept>();
    test_remove_cv<int (class_type::*)() const noexcept>();
    test_remove_cv<int (class_type::*)() const & noexcept>();
    test_remove_cv<int (class_type::*)() const && noexcept>();

    test_remove_cv<int (class_type::*)(int)>();
    test_remove_cv<int (class_type::*)(int)&>();
    test_remove_cv<int (class_type::*)(int) &&>();
    test_remove_cv<int (class_type::*)(int) const>();
    test_remove_cv<int (class_type::*)(int) const&>();
    test_remove_cv<int (class_type::*)(int) const&&>();
    test_remove_cv<int (class_type::*)(int) noexcept>();
    test_remove_cv<int (class_type::*)(int) & noexcept>();
    test_remove_cv<int (class_type::*)(int) && noexcept>();
    test_remove_cv<int (class_type::*)(int) const noexcept>();
    test_remove_cv<int (class_type::*)(int) const & noexcept>();
    test_remove_cv<int (class_type::*)(int) const && noexcept>();

    test_remove_cv<int (class_type::*)(...)>();
    test_remove_cv<int (class_type::*)(...)&>();
    test_remove_cv<int (class_type::*)(...) &&>();
    test_remove_cv<int (class_type::*)(...) const>();
    test_remove_cv<int (class_type::*)(...) const&>();
    test_remove_cv<int (class_type::*)(...) const&&>();
    test_remove_cv<int (class_type::*)(...) noexcept>();
    test_remove_cv<int (class_type::*)(...) & noexcept>();
    test_remove_cv<int (class_type::*)(...) && noexcept>();
    test_remove_cv<int (class_type::*)(...) const noexcept>();
    test_remove_cv<int (class_type::*)(...) const & noexcept>();
    test_remove_cv<int (class_type::*)(...) const && noexcept>();

    test_remove_cv<int (class_type::*)(int, ...)>();
    test_remove_cv<int (class_type::*)(int, ...)&>();
    test_remove_cv<int (class_type::*)(int, ...) &&>();
    test_remove_cv<int (class_type::*)(int, ...) const>();
    test_remove_cv<int (class_type::*)(int, ...) const&>();
    test_remove_cv<int (class_type::*)(int, ...) const&&>();
    test_remove_cv<int (class_type::*)(int, ...) noexcept>();
    test_remove_cv<int (class_type::*)(int, ...) & noexcept>();
    test_remove_cv<int (class_type::*)(int, ...) && noexcept>();
    test_remove_cv<int (class_type::*)(int, ...) const noexcept>();
    test_remove_cv<int (class_type::*)(int, ...) const & noexcept>();
    test_remove_cv<int (class_type::*)(int, ...) const && noexcept>();
}
