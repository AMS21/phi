#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/remove_cvref.hpp>
#include <vector>

template <typename TypeT, typename ExpectedT>
void test_remove_cvref_impl()
{
    CHECK_SAME_TYPE(typename phi::remove_cvref<TypeT>::type, ExpectedT);
    CHECK_SAME_TYPE(phi::remove_cvref_t<TypeT>, ExpectedT);

    // Standard compatibility
#if PHI_CPP_STANDARD_IS_ATLEAST(20) && !PHI_COMPILER_IS_BELOW(GCC, 9, 0, 0)
    CHECK_SAME_TYPE(typename std::remove_cvref<TypeT>::type, ExpectedT);
#endif
}

template <typename TypeT, typename ExpectedT = TypeT>
void test_remove_cvref()
{
    test_remove_cvref_impl<TypeT, ExpectedT>();
    test_remove_cvref_impl<const TypeT, ExpectedT>();
    test_remove_cvref_impl<volatile TypeT, ExpectedT>();
    test_remove_cvref_impl<const volatile TypeT, ExpectedT>();
}

TEST_CASE("remove_cvref")
{
    test_remove_cvref<void>();
    test_remove_cvref<phi::nullptr_t>();
    test_remove_cvref<bool>();
    test_remove_cvref<char>();
    test_remove_cvref<signed char>();
    test_remove_cvref<unsigned char>();
    test_remove_cvref<short>();
    test_remove_cvref<unsigned short>();
    test_remove_cvref<int>();
    test_remove_cvref<unsigned int>();
    test_remove_cvref<long>();
    test_remove_cvref<unsigned long>();
    test_remove_cvref<long long>();
    test_remove_cvref<unsigned long long>();
    test_remove_cvref<float>();
    test_remove_cvref<double>();
    test_remove_cvref<long double>();
    test_remove_cvref<char8_t>();
    test_remove_cvref<char16_t>();
    test_remove_cvref<char32_t>();
    test_remove_cvref<wchar_t>();

    test_remove_cvref<phi::boolean>();
    test_remove_cvref<phi::integer<signed char>>();
    test_remove_cvref<phi::integer<unsigned char>>();
    test_remove_cvref<phi::integer<short>>();
    test_remove_cvref<phi::integer<unsigned short>>();
    test_remove_cvref<phi::integer<int>>();
    test_remove_cvref<phi::integer<unsigned int>>();
    test_remove_cvref<phi::integer<long>>();
    test_remove_cvref<phi::integer<unsigned long>>();
    test_remove_cvref<phi::integer<long long>>();
    test_remove_cvref<phi::integer<unsigned long long>>();
    test_remove_cvref<phi::floating_point<float>>();
    test_remove_cvref<phi::floating_point<double>>();
    test_remove_cvref<phi::floating_point<long double>>();

    test_remove_cvref<std::vector<int>>();
    test_remove_cvref<phi::scope_ptr<int>>();

    test_remove_cvref<int&, int>();
    test_remove_cvref<const int&, int>();
    test_remove_cvref<volatile int&, int>();
    test_remove_cvref<const volatile int&, int>();
    test_remove_cvref<int&&, int>();
    test_remove_cvref<const int&&, int>();
    test_remove_cvref<volatile int&&, int>();
    test_remove_cvref<const volatile int&&, int>();
    test_remove_cvref<int*>();
    test_remove_cvref<const int*>();
    test_remove_cvref<volatile int*>();
    test_remove_cvref<const volatile int*>();
    test_remove_cvref<int**>();
    test_remove_cvref<const int**>();
    test_remove_cvref<volatile int**>();
    test_remove_cvref<const volatile int**>();
    test_remove_cvref<int*&, int*>();
    test_remove_cvref<const int*&, const int*>();
    test_remove_cvref<volatile int*&, volatile int*>();
    test_remove_cvref<const volatile int*&, const volatile int*>();
    test_remove_cvref<int*&&, int*>();
    test_remove_cvref<const int*&&, const int*>();
    test_remove_cvref<volatile int*&&, volatile int*>();
    test_remove_cvref<const volatile int*&&, const volatile int*>();
    test_remove_cvref<void*>();
    test_remove_cvref<char[3]>();
    test_remove_cvref<char[]>();
    test_remove_cvref<char* [3]>();
    test_remove_cvref<char*[]>();
    test_remove_cvref<int(*)[3]>();
    test_remove_cvref<int(*)[]>();
    test_remove_cvref<int(&)[3], int[3]>();
    test_remove_cvref<int(&)[], int[]>();
    test_remove_cvref<int(&&)[3], int[3]>();
    test_remove_cvref<int(&&)[], int[]>();
    test_remove_cvref<char[3][2]>();
    test_remove_cvref<char[][2]>();
    test_remove_cvref<char* [3][2]>();
    test_remove_cvref<char*[][2]>();
    test_remove_cvref<int(*)[3][2]>();
    test_remove_cvref<int(*)[][2]>();
    test_remove_cvref<int(&)[3][2], int[3][2]>();
    test_remove_cvref<int(&)[][2], int[][2]>();
    test_remove_cvref<int(&&)[3][2], int[3][2]>();
    test_remove_cvref<int(&&)[][2], int[][2]>();
    test_remove_cvref<class_type>();
    test_remove_cvref<class_type[]>();
    test_remove_cvref<class_type[2]>();
    test_remove_cvref<template_type<void>>();
    test_remove_cvref<template_type<int>>();
    test_remove_cvref<template_type<class_type>>();
    test_remove_cvref<template_type<incomplete_type>>();
    test_remove_cvref<variadic_template<>>();
    test_remove_cvref<variadic_template<void>>();
    test_remove_cvref<variadic_template<int>>();
    test_remove_cvref<variadic_template<class_type>>();
    test_remove_cvref<variadic_template<incomplete_type>>();
    test_remove_cvref<variadic_template<int, void, class_type, volatile char[]>>();
    test_remove_cvref<public_derived_from<base>>();
    test_remove_cvref<public_derived_from<derived>>();
    test_remove_cvref<public_derived_from<class_type>>();
    test_remove_cvref<private_derived_from<base>>();
    test_remove_cvref<private_derived_from<derived>>();
    test_remove_cvref<private_derived_from<class_type>>();
    test_remove_cvref<protected_derived_from<base>>();
    test_remove_cvref<protected_derived_from<derived>>();
    test_remove_cvref<protected_derived_from<class_type>>();
    test_remove_cvref<union_type>();
    test_remove_cvref<non_empty_union>();
    test_remove_cvref<empty>();
    test_remove_cvref<not_empty>();
    test_remove_cvref<bit_zero>();
    test_remove_cvref<bit_one>();
    test_remove_cvref<base>();
    test_remove_cvref<derived>();
    test_remove_cvref<abstract>();
    test_remove_cvref<public_abstract>();
    test_remove_cvref<private_abstract>();
    test_remove_cvref<protected_abstract>();
    test_remove_cvref<abstract_template<int>>();
    test_remove_cvref<abstract_template<double>>();
    test_remove_cvref<abstract_template<class_type>>();
    test_remove_cvref<abstract_template<incomplete_type>>();
    test_remove_cvref<final_type>();
    test_remove_cvref<public_destructor>();
    test_remove_cvref<protected_destructor>();
    test_remove_cvref<private_destructor>();
    test_remove_cvref<virtual_public_destructor>();
    test_remove_cvref<virtual_protected_destructor>();
    test_remove_cvref<virtual_private_destructor>();
    test_remove_cvref<pure_public_destructor>();
    test_remove_cvref<pure_protected_destructor>();
    test_remove_cvref<pure_private_destructor>();
    test_remove_cvref<deleted_public_destructor>();
    test_remove_cvref<deleted_protected_destructor>();
    test_remove_cvref<deleted_private_destructor>();
    test_remove_cvref<deleted_virtual_public_destructor>();
    test_remove_cvref<deleted_virtual_protected_destructor>();
    test_remove_cvref<deleted_virtual_private_destructor>();
    test_remove_cvref<Enum>();
    test_remove_cvref<EnumSigned>();
    test_remove_cvref<EnumUnsigned>();
    test_remove_cvref<EnumClass>();
    test_remove_cvref<EnumStruct>();
    test_remove_cvref<function_type>();
    test_remove_cvref<function_ptr>();
    test_remove_cvref<member_object_ptr>();
    test_remove_cvref<member_function_ptr>();
    test_remove_cvref<incomplete_type>();
    test_remove_cvref<incomplete_template<void>>();
    test_remove_cvref<incomplete_template<int>>();
    test_remove_cvref<incomplete_template<class_type>>();
    test_remove_cvref<incomplete_template<incomplete_type>>();
    test_remove_cvref<incomplete_variadic_template<>>();
    test_remove_cvref<incomplete_variadic_template<void>>();
    test_remove_cvref<incomplete_variadic_template<int>>();
    test_remove_cvref<incomplete_variadic_template<class_type>>();
    test_remove_cvref<incomplete_variadic_template<incomplete_type>>();
    test_remove_cvref<incomplete_variadic_template<int, void, class_type, volatile char[]>>();
    test_remove_cvref<int class_type::*>();
    test_remove_cvref<float class_type::*>();
    test_remove_cvref<void * class_type::*>();
    test_remove_cvref<int * class_type::*>();
    test_remove_cvref<int class_type::*&, int class_type::*>();
    test_remove_cvref<float class_type::*&, float class_type::*>();
    test_remove_cvref<void * class_type::*&, void * class_type::*>();
    test_remove_cvref<int * class_type::*&, int * class_type::*>();
    test_remove_cvref<int class_type::*&&, int class_type::*>();
    test_remove_cvref<float class_type::*&&, float class_type::*>();
    test_remove_cvref<void * class_type::*&&, void * class_type::*>();
    test_remove_cvref<int * class_type::*&&, int * class_type::*>();
    test_remove_cvref<int class_type::* const, int class_type::*>();
    test_remove_cvref<float class_type::* const, float class_type::*>();
    test_remove_cvref<void * class_type::* const, void * class_type::*>();
    test_remove_cvref<int class_type::* const&, int class_type::*>();
    test_remove_cvref<float class_type::* const&, float class_type::*>();
    test_remove_cvref<void * class_type::* const&, void * class_type::*>();
    test_remove_cvref<int class_type::* const&&, int class_type::*>();
    test_remove_cvref<float class_type::* const&&, float class_type::*>();
    test_remove_cvref<void * class_type::* const&&, void * class_type::*>();
    test_remove_cvref<int class_type::* volatile, int class_type::*>();
    test_remove_cvref<float class_type::* volatile, float class_type::*>();
    test_remove_cvref<void * class_type::* volatile, void * class_type::*>();
    test_remove_cvref<int class_type::* volatile&, int class_type::*>();
    test_remove_cvref<float class_type::* volatile&, float class_type::*>();
    test_remove_cvref<void * class_type::* volatile&, void * class_type::*>();
    test_remove_cvref<int class_type::* volatile&&, int class_type::*>();
    test_remove_cvref<float class_type::* volatile&&, float class_type::*>();
    test_remove_cvref<void * class_type::* volatile&&, void * class_type::*>();
    test_remove_cvref<int class_type::* const volatile, int class_type::*>();
    test_remove_cvref<float class_type::* const volatile, float class_type::*>();
    test_remove_cvref<void * class_type::* const volatile, void * class_type::*>();
    test_remove_cvref<int class_type::* const volatile&, int class_type::*>();
    test_remove_cvref<float class_type::* const volatile&, float class_type::*>();
    test_remove_cvref<void * class_type::* const volatile&, void * class_type::*>();
    test_remove_cvref<int class_type::* const volatile&&, int class_type::*>();
    test_remove_cvref<float class_type::* const volatile&&, float class_type::*>();
    test_remove_cvref<void * class_type::* const volatile&&, void * class_type::*>();
    test_remove_cvref<non_copyable>();
    test_remove_cvref<non_moveable>();
    test_remove_cvref<non_constructible>();
    test_remove_cvref<tracked>();
    test_remove_cvref<trap_constructible>();
    test_remove_cvref<trap_implicit_conversion>();
    test_remove_cvref<trap_comma>();
    test_remove_cvref<trap_call>();
    test_remove_cvref<trap_self_assign>();
    test_remove_cvref<trap_deref>();
    test_remove_cvref<trap_array_subscript>();

    test_remove_cvref<void()>();
    test_remove_cvref<void()&>();
    test_remove_cvref<void() &&>();
    test_remove_cvref<void() const>();
    test_remove_cvref<void() const&>();
    test_remove_cvref<void() const&&>();
    test_remove_cvref<void() volatile>();
    test_remove_cvref<void() volatile&>();
    test_remove_cvref<void() volatile&&>();
    test_remove_cvref<void() const volatile>();
    test_remove_cvref<void() const volatile&>();
    test_remove_cvref<void() const volatile&&>();
    test_remove_cvref<void() noexcept>();
    test_remove_cvref<void() & noexcept>();
    test_remove_cvref<void() && noexcept>();
    test_remove_cvref<void() const noexcept>();
    test_remove_cvref<void() const & noexcept>();
    test_remove_cvref<void() const && noexcept>();
    test_remove_cvref<void() volatile noexcept>();
    test_remove_cvref<void() volatile & noexcept>();
    test_remove_cvref<void() volatile && noexcept>();
    test_remove_cvref<void() const volatile noexcept>();
    test_remove_cvref<void() const volatile & noexcept>();
    test_remove_cvref<void() const volatile && noexcept>();

    test_remove_cvref<void(int)>();
    test_remove_cvref<void(int)&>();
    test_remove_cvref<void(int) &&>();
    test_remove_cvref<void(int) const>();
    test_remove_cvref<void(int) const&>();
    test_remove_cvref<void(int) const&&>();
    test_remove_cvref<void(int) volatile>();
    test_remove_cvref<void(int) volatile&>();
    test_remove_cvref<void(int) volatile&&>();
    test_remove_cvref<void(int) const volatile>();
    test_remove_cvref<void(int) const volatile&>();
    test_remove_cvref<void(int) const volatile&&>();
    test_remove_cvref<void(int) noexcept>();
    test_remove_cvref<void(int) & noexcept>();
    test_remove_cvref<void(int) && noexcept>();
    test_remove_cvref<void(int) const noexcept>();
    test_remove_cvref<void(int) const & noexcept>();
    test_remove_cvref<void(int) const && noexcept>();
    test_remove_cvref<void(int) volatile noexcept>();
    test_remove_cvref<void(int) volatile & noexcept>();
    test_remove_cvref<void(int) volatile && noexcept>();
    test_remove_cvref<void(int) const volatile noexcept>();
    test_remove_cvref<void(int) const volatile & noexcept>();
    test_remove_cvref<void(int) const volatile && noexcept>();

    test_remove_cvref<void(...)>();
    test_remove_cvref<void(...)&>();
    test_remove_cvref<void(...) &&>();
    test_remove_cvref<void(...) const>();
    test_remove_cvref<void(...) const&>();
    test_remove_cvref<void(...) const&&>();
    test_remove_cvref<void(...) volatile>();
    test_remove_cvref<void(...) volatile&>();
    test_remove_cvref<void(...) volatile&&>();
    test_remove_cvref<void(...) const volatile>();
    test_remove_cvref<void(...) const volatile&>();
    test_remove_cvref<void(...) const volatile&&>();
    test_remove_cvref<void(...) noexcept>();
    test_remove_cvref<void(...) & noexcept>();
    test_remove_cvref<void(...) && noexcept>();
    test_remove_cvref<void(...) const noexcept>();
    test_remove_cvref<void(...) const & noexcept>();
    test_remove_cvref<void(...) const && noexcept>();
    test_remove_cvref<void(...) volatile noexcept>();
    test_remove_cvref<void(...) volatile & noexcept>();
    test_remove_cvref<void(...) volatile && noexcept>();
    test_remove_cvref<void(...) const volatile noexcept>();
    test_remove_cvref<void(...) const volatile & noexcept>();
    test_remove_cvref<void(...) const volatile && noexcept>();

    test_remove_cvref<void(int, ...)>();
    test_remove_cvref<void(int, ...)&>();
    test_remove_cvref<void(int, ...) &&>();
    test_remove_cvref<void(int, ...) const>();
    test_remove_cvref<void(int, ...) const&>();
    test_remove_cvref<void(int, ...) const&&>();
    test_remove_cvref<void(int, ...) volatile>();
    test_remove_cvref<void(int, ...) volatile&>();
    test_remove_cvref<void(int, ...) volatile&&>();
    test_remove_cvref<void(int, ...) const volatile>();
    test_remove_cvref<void(int, ...) const volatile&>();
    test_remove_cvref<void(int, ...) const volatile&&>();
    test_remove_cvref<void(int, ...) noexcept>();
    test_remove_cvref<void(int, ...) & noexcept>();
    test_remove_cvref<void(int, ...) && noexcept>();
    test_remove_cvref<void(int, ...) const noexcept>();
    test_remove_cvref<void(int, ...) const & noexcept>();
    test_remove_cvref<void(int, ...) const && noexcept>();
    test_remove_cvref<void(int, ...) volatile noexcept>();
    test_remove_cvref<void(int, ...) volatile & noexcept>();
    test_remove_cvref<void(int, ...) volatile && noexcept>();
    test_remove_cvref<void(int, ...) const volatile noexcept>();
    test_remove_cvref<void(int, ...) const volatile & noexcept>();
    test_remove_cvref<void(int, ...) const volatile && noexcept>();

    test_remove_cvref<int()>();
    test_remove_cvref<int()&>();
    test_remove_cvref<int() &&>();
    test_remove_cvref<int() const>();
    test_remove_cvref<int() const&>();
    test_remove_cvref<int() const&&>();
    test_remove_cvref<int() volatile>();
    test_remove_cvref<int() volatile&>();
    test_remove_cvref<int() volatile&&>();
    test_remove_cvref<int() const volatile>();
    test_remove_cvref<int() const volatile&>();
    test_remove_cvref<int() const volatile&&>();
    test_remove_cvref<int() noexcept>();
    test_remove_cvref<int() & noexcept>();
    test_remove_cvref<int() && noexcept>();
    test_remove_cvref<int() const noexcept>();
    test_remove_cvref<int() const & noexcept>();
    test_remove_cvref<int() const && noexcept>();
    test_remove_cvref<int() volatile noexcept>();
    test_remove_cvref<int() volatile & noexcept>();
    test_remove_cvref<int() volatile && noexcept>();
    test_remove_cvref<int() const volatile noexcept>();
    test_remove_cvref<int() const volatile & noexcept>();
    test_remove_cvref<int() const volatile && noexcept>();

    test_remove_cvref<int(int)>();
    test_remove_cvref<int(int)&>();
    test_remove_cvref<int(int) &&>();
    test_remove_cvref<int(int) const>();
    test_remove_cvref<int(int) const&>();
    test_remove_cvref<int(int) const&&>();
    test_remove_cvref<int(int) volatile>();
    test_remove_cvref<int(int) volatile&>();
    test_remove_cvref<int(int) volatile&&>();
    test_remove_cvref<int(int) const volatile>();
    test_remove_cvref<int(int) const volatile&>();
    test_remove_cvref<int(int) const volatile&&>();
    test_remove_cvref<int(int) noexcept>();
    test_remove_cvref<int(int) & noexcept>();
    test_remove_cvref<int(int) && noexcept>();
    test_remove_cvref<int(int) const noexcept>();
    test_remove_cvref<int(int) const & noexcept>();
    test_remove_cvref<int(int) const && noexcept>();
    test_remove_cvref<int(int) volatile noexcept>();
    test_remove_cvref<int(int) volatile & noexcept>();
    test_remove_cvref<int(int) volatile && noexcept>();
    test_remove_cvref<int(int) const volatile noexcept>();
    test_remove_cvref<int(int) const volatile & noexcept>();
    test_remove_cvref<int(int) const volatile && noexcept>();

    test_remove_cvref<int(...)>();
    test_remove_cvref<int(...)&>();
    test_remove_cvref<int(...) &&>();
    test_remove_cvref<int(...) const>();
    test_remove_cvref<int(...) const&>();
    test_remove_cvref<int(...) const&&>();
    test_remove_cvref<int(...) volatile>();
    test_remove_cvref<int(...) volatile&>();
    test_remove_cvref<int(...) volatile&&>();
    test_remove_cvref<int(...) const volatile>();
    test_remove_cvref<int(...) const volatile&>();
    test_remove_cvref<int(...) const volatile&&>();
    test_remove_cvref<int(...) noexcept>();
    test_remove_cvref<int(...) & noexcept>();
    test_remove_cvref<int(...) && noexcept>();
    test_remove_cvref<int(...) const noexcept>();
    test_remove_cvref<int(...) const & noexcept>();
    test_remove_cvref<int(...) const && noexcept>();
    test_remove_cvref<int(...) volatile noexcept>();
    test_remove_cvref<int(...) volatile & noexcept>();
    test_remove_cvref<int(...) volatile && noexcept>();
    test_remove_cvref<int(...) const volatile noexcept>();
    test_remove_cvref<int(...) const volatile & noexcept>();
    test_remove_cvref<int(...) const volatile && noexcept>();

    test_remove_cvref<int(int, ...)>();
    test_remove_cvref<int(int, ...)&>();
    test_remove_cvref<int(int, ...) &&>();
    test_remove_cvref<int(int, ...) const>();
    test_remove_cvref<int(int, ...) const&>();
    test_remove_cvref<int(int, ...) const&&>();
    test_remove_cvref<int(int, ...) volatile>();
    test_remove_cvref<int(int, ...) volatile&>();
    test_remove_cvref<int(int, ...) volatile&&>();
    test_remove_cvref<int(int, ...) const volatile>();
    test_remove_cvref<int(int, ...) const volatile&>();
    test_remove_cvref<int(int, ...) const volatile&&>();
    test_remove_cvref<int(int, ...) noexcept>();
    test_remove_cvref<int(int, ...) & noexcept>();
    test_remove_cvref<int(int, ...) && noexcept>();
    test_remove_cvref<int(int, ...) const noexcept>();
    test_remove_cvref<int(int, ...) const & noexcept>();
    test_remove_cvref<int(int, ...) const && noexcept>();
    test_remove_cvref<int(int, ...) volatile noexcept>();
    test_remove_cvref<int(int, ...) volatile & noexcept>();
    test_remove_cvref<int(int, ...) volatile && noexcept>();
    test_remove_cvref<int(int, ...) const volatile noexcept>();
    test_remove_cvref<int(int, ...) const volatile & noexcept>();
    test_remove_cvref<int(int, ...) const volatile && noexcept>();

    test_remove_cvref<void (*)()>();
    test_remove_cvref<void (*)() noexcept>();

    test_remove_cvref<void (*)(int)>();
    test_remove_cvref<void (*)(int) noexcept>();

    test_remove_cvref<void (*)(...)>();
    test_remove_cvref<void (*)(...) noexcept>();

    test_remove_cvref<void (*)(int, ...)>();
    test_remove_cvref<void (*)(int, ...) noexcept>();

    test_remove_cvref<int (*)()>();
    test_remove_cvref<int (*)() noexcept>();

    test_remove_cvref<int (*)(int)>();
    test_remove_cvref<int (*)(int) noexcept>();

    test_remove_cvref<int (*)(...)>();
    test_remove_cvref<int (*)(...) noexcept>();

    test_remove_cvref<int (*)(int, ...)>();
    test_remove_cvref<int (*)(int, ...) noexcept>();

    test_remove_cvref<void (&)(), void()>();
    test_remove_cvref<void (&)() noexcept, void() noexcept>();

    test_remove_cvref<void (&)(int), void(int)>();
    test_remove_cvref<void (&)(int) noexcept, void(int) noexcept>();

    test_remove_cvref<void (&)(...), void(...)>();
    test_remove_cvref<void (&)(...) noexcept, void(...) noexcept>();

    test_remove_cvref<void (&)(int, ...), void(int, ...)>();
    test_remove_cvref<void (&)(int, ...) noexcept, void(int, ...) noexcept>();

    test_remove_cvref<int (&)(), int()>();
    test_remove_cvref<int (&)() noexcept, int() noexcept>();

    test_remove_cvref<int (&)(int), int(int)>();
    test_remove_cvref<int (&)(int) noexcept, int(int) noexcept>();

    test_remove_cvref<int (&)(...), int(...)>();
    test_remove_cvref<int (&)(...) noexcept, int(...) noexcept>();

    test_remove_cvref<int (&)(int, ...), int(int, ...)>();
    test_remove_cvref<int (&)(int, ...) noexcept, int(int, ...) noexcept>();

    test_remove_cvref<void (&&)(), void()>();
    test_remove_cvref<void (&&)() noexcept, void() noexcept>();

    test_remove_cvref<void (&&)(int), void(int)>();
    test_remove_cvref<void (&&)(int) noexcept, void(int) noexcept>();

    test_remove_cvref<void (&&)(...), void(...)>();
    test_remove_cvref<void (&&)(...) noexcept, void(...) noexcept>();

    test_remove_cvref<void (&&)(int, ...), void(int, ...)>();
    test_remove_cvref<void (&&)(int, ...) noexcept, void(int, ...) noexcept>();

    test_remove_cvref<int (&&)(), int()>();
    test_remove_cvref<int (&&)() noexcept, int() noexcept>();

    test_remove_cvref<int (&&)(int), int(int)>();
    test_remove_cvref<int (&&)(int) noexcept, int(int) noexcept>();

    test_remove_cvref<int (&&)(...), int(...)>();
    test_remove_cvref<int (&&)(...) noexcept, int(...) noexcept>();

    test_remove_cvref<int (&&)(int, ...), int(int, ...)>();
    test_remove_cvref<int (&&)(int, ...) noexcept, int(int, ...) noexcept>();

    test_remove_cvref<void (class_type::*)()>();
    test_remove_cvref<void (class_type::*)()&>();
    test_remove_cvref<void (class_type::*)() &&>();
    test_remove_cvref<void (class_type::*)() const>();
    test_remove_cvref<void (class_type::*)() const&>();
    test_remove_cvref<void (class_type::*)() const&&>();
    test_remove_cvref<void (class_type::*)() noexcept>();
    test_remove_cvref<void (class_type::*)() & noexcept>();
    test_remove_cvref<void (class_type::*)() && noexcept>();
    test_remove_cvref<void (class_type::*)() const noexcept>();
    test_remove_cvref<void (class_type::*)() const & noexcept>();
    test_remove_cvref<void (class_type::*)() const && noexcept>();

    test_remove_cvref<void (class_type::*)(int)>();
    test_remove_cvref<void (class_type::*)(int)&>();
    test_remove_cvref<void (class_type::*)(int) &&>();
    test_remove_cvref<void (class_type::*)(int) const>();
    test_remove_cvref<void (class_type::*)(int) const&>();
    test_remove_cvref<void (class_type::*)(int) const&&>();
    test_remove_cvref<void (class_type::*)(int) noexcept>();
    test_remove_cvref<void (class_type::*)(int) & noexcept>();
    test_remove_cvref<void (class_type::*)(int) && noexcept>();
    test_remove_cvref<void (class_type::*)(int) const noexcept>();
    test_remove_cvref<void (class_type::*)(int) const & noexcept>();
    test_remove_cvref<void (class_type::*)(int) const && noexcept>();

    test_remove_cvref<void (class_type::*)(...)>();
    test_remove_cvref<void (class_type::*)(...)&>();
    test_remove_cvref<void (class_type::*)(...) &&>();
    test_remove_cvref<void (class_type::*)(...) const>();
    test_remove_cvref<void (class_type::*)(...) const&>();
    test_remove_cvref<void (class_type::*)(...) const&&>();
    test_remove_cvref<void (class_type::*)(...) noexcept>();
    test_remove_cvref<void (class_type::*)(...) & noexcept>();
    test_remove_cvref<void (class_type::*)(...) && noexcept>();
    test_remove_cvref<void (class_type::*)(...) const noexcept>();
    test_remove_cvref<void (class_type::*)(...) const & noexcept>();
    test_remove_cvref<void (class_type::*)(...) const && noexcept>();

    test_remove_cvref<void (class_type::*)(int, ...)>();
    test_remove_cvref<void (class_type::*)(int, ...)&>();
    test_remove_cvref<void (class_type::*)(int, ...) &&>();
    test_remove_cvref<void (class_type::*)(int, ...) const>();
    test_remove_cvref<void (class_type::*)(int, ...) const&>();
    test_remove_cvref<void (class_type::*)(int, ...) const&&>();
    test_remove_cvref<void (class_type::*)(int, ...) noexcept>();
    test_remove_cvref<void (class_type::*)(int, ...) & noexcept>();
    test_remove_cvref<void (class_type::*)(int, ...) && noexcept>();
    test_remove_cvref<void (class_type::*)(int, ...) const noexcept>();
    test_remove_cvref<void (class_type::*)(int, ...) const & noexcept>();
    test_remove_cvref<void (class_type::*)(int, ...) const && noexcept>();

    test_remove_cvref<int (class_type::*)()>();
    test_remove_cvref<int (class_type::*)()&>();
    test_remove_cvref<int (class_type::*)() &&>();
    test_remove_cvref<int (class_type::*)() const>();
    test_remove_cvref<int (class_type::*)() const&>();
    test_remove_cvref<int (class_type::*)() const&&>();
    test_remove_cvref<int (class_type::*)() noexcept>();
    test_remove_cvref<int (class_type::*)() & noexcept>();
    test_remove_cvref<int (class_type::*)() && noexcept>();
    test_remove_cvref<int (class_type::*)() const noexcept>();
    test_remove_cvref<int (class_type::*)() const & noexcept>();
    test_remove_cvref<int (class_type::*)() const && noexcept>();

    test_remove_cvref<int (class_type::*)(int)>();
    test_remove_cvref<int (class_type::*)(int)&>();
    test_remove_cvref<int (class_type::*)(int) &&>();
    test_remove_cvref<int (class_type::*)(int) const>();
    test_remove_cvref<int (class_type::*)(int) const&>();
    test_remove_cvref<int (class_type::*)(int) const&&>();
    test_remove_cvref<int (class_type::*)(int) noexcept>();
    test_remove_cvref<int (class_type::*)(int) & noexcept>();
    test_remove_cvref<int (class_type::*)(int) && noexcept>();
    test_remove_cvref<int (class_type::*)(int) const noexcept>();
    test_remove_cvref<int (class_type::*)(int) const & noexcept>();
    test_remove_cvref<int (class_type::*)(int) const && noexcept>();

    test_remove_cvref<int (class_type::*)(...)>();
    test_remove_cvref<int (class_type::*)(...)&>();
    test_remove_cvref<int (class_type::*)(...) &&>();
    test_remove_cvref<int (class_type::*)(...) const>();
    test_remove_cvref<int (class_type::*)(...) const&>();
    test_remove_cvref<int (class_type::*)(...) const&&>();
    test_remove_cvref<int (class_type::*)(...) noexcept>();
    test_remove_cvref<int (class_type::*)(...) & noexcept>();
    test_remove_cvref<int (class_type::*)(...) && noexcept>();
    test_remove_cvref<int (class_type::*)(...) const noexcept>();
    test_remove_cvref<int (class_type::*)(...) const & noexcept>();
    test_remove_cvref<int (class_type::*)(...) const && noexcept>();

    test_remove_cvref<int (class_type::*)(int, ...)>();
    test_remove_cvref<int (class_type::*)(int, ...)&>();
    test_remove_cvref<int (class_type::*)(int, ...) &&>();
    test_remove_cvref<int (class_type::*)(int, ...) const>();
    test_remove_cvref<int (class_type::*)(int, ...) const&>();
    test_remove_cvref<int (class_type::*)(int, ...) const&&>();
    test_remove_cvref<int (class_type::*)(int, ...) noexcept>();
    test_remove_cvref<int (class_type::*)(int, ...) & noexcept>();
    test_remove_cvref<int (class_type::*)(int, ...) && noexcept>();
    test_remove_cvref<int (class_type::*)(int, ...) const noexcept>();
    test_remove_cvref<int (class_type::*)(int, ...) const & noexcept>();
    test_remove_cvref<int (class_type::*)(int, ...) const && noexcept>();
}
