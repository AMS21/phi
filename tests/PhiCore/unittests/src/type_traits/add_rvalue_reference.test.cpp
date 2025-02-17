#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/add_rvalue_reference.hpp>
#include <type_traits>
#include <vector>

template <typename TypeT, typename ExpectedT = TypeT&&>
void test_add_rvalue_reference()
{
    CHECK_SAME_TYPE(ExpectedT, typename phi::add_rvalue_reference<TypeT>::type);
    CHECK_SAME_TYPE(const ExpectedT, const typename phi::add_rvalue_reference<TypeT>::type);
    CHECK_SAME_TYPE(volatile ExpectedT, volatile typename phi::add_rvalue_reference<TypeT>::type);
    CHECK_SAME_TYPE(const volatile ExpectedT,
                    const volatile typename phi::add_rvalue_reference<TypeT>::type);

    CHECK_SAME_TYPE(ExpectedT, phi::add_rvalue_reference_t<TypeT>);
    CHECK_SAME_TYPE(const ExpectedT, const phi::add_rvalue_reference_t<TypeT>);
    CHECK_SAME_TYPE(volatile ExpectedT, volatile phi::add_rvalue_reference_t<TypeT>);
    CHECK_SAME_TYPE(const volatile ExpectedT, const volatile phi::add_rvalue_reference_t<TypeT>);

    // Standard compatibility
    CHECK_SAME_TYPE(typename phi::add_rvalue_reference<TypeT>::type,
                    typename std::add_rvalue_reference<TypeT>::type);
    CHECK_SAME_TYPE(typename phi::add_rvalue_reference<const TypeT>::type,
                    typename std::add_rvalue_reference<const TypeT>::type);
    CHECK_SAME_TYPE(typename phi::add_rvalue_reference<volatile TypeT>::type,
                    typename std::add_rvalue_reference<volatile TypeT>::type);
    CHECK_SAME_TYPE(typename phi::add_rvalue_reference<const volatile TypeT>::type,
                    typename std::add_rvalue_reference<const volatile TypeT>::type);
}

template <typename FunctionT>
void test_function0()
{
    CHECK_SAME_TYPE(FunctionT&&, typename phi::add_rvalue_reference<FunctionT>::type);
    CHECK_SAME_TYPE(FunctionT&&, phi::add_rvalue_reference_t<FunctionT>);

    // Standard compatibility
    CHECK_SAME_TYPE(typename phi::add_rvalue_reference<FunctionT>::type,
                    typename std::add_rvalue_reference<FunctionT>::type);
}

template <typename FunctionT>
void test_function1()
{
    CHECK_SAME_TYPE(FunctionT, typename phi::add_rvalue_reference<FunctionT>::type);
    CHECK_SAME_TYPE(FunctionT, phi::add_rvalue_reference_t<FunctionT>);

    // Standard compatibility
    CHECK_SAME_TYPE(typename phi::add_rvalue_reference<FunctionT>::type,
                    typename std::add_rvalue_reference<FunctionT>::type);
}

struct Foo
{};

struct A; // incomplete

TEST_CASE("add_rvalue_reference")
{
    test_add_rvalue_reference<A, A&&>();
    test_add_rvalue_reference<Foo, Foo&&>();

    test_add_rvalue_reference<void, void>();
    test_add_rvalue_reference<phi::nullptr_t>();
    test_add_rvalue_reference<bool>();
    test_add_rvalue_reference<char>();
    test_add_rvalue_reference<signed char>();
    test_add_rvalue_reference<unsigned char>();
    test_add_rvalue_reference<short>();
    test_add_rvalue_reference<unsigned short>();
    test_add_rvalue_reference<int>();
    test_add_rvalue_reference<unsigned int>();
    test_add_rvalue_reference<long>();
    test_add_rvalue_reference<unsigned long>();
    test_add_rvalue_reference<long long>();
    test_add_rvalue_reference<unsigned long long>();
    test_add_rvalue_reference<float>();
    test_add_rvalue_reference<double>();
    test_add_rvalue_reference<long double>();
    test_add_rvalue_reference<char8_t>();
    test_add_rvalue_reference<char16_t>();
    test_add_rvalue_reference<char32_t>();
    test_add_rvalue_reference<wchar_t>();

    test_add_rvalue_reference<phi::boolean>();
    test_add_rvalue_reference<phi::integer<signed char>>();
    test_add_rvalue_reference<phi::integer<unsigned char>>();
    test_add_rvalue_reference<phi::integer<short>>();
    test_add_rvalue_reference<phi::integer<unsigned short>>();
    test_add_rvalue_reference<phi::integer<int>>();
    test_add_rvalue_reference<phi::integer<unsigned int>>();
    test_add_rvalue_reference<phi::integer<long>>();
    test_add_rvalue_reference<phi::integer<unsigned long>>();
    test_add_rvalue_reference<phi::integer<long long>>();
    test_add_rvalue_reference<phi::integer<unsigned long long>>();
    test_add_rvalue_reference<phi::floating_point<float>>();
    test_add_rvalue_reference<phi::floating_point<double>>();
    test_add_rvalue_reference<phi::floating_point<long double>>();

    test_add_rvalue_reference<std::vector<int>>();
    test_add_rvalue_reference<phi::scope_ptr<int>>();

    test_add_rvalue_reference<int&>();
    test_add_rvalue_reference<const int&>();
    test_add_rvalue_reference<volatile int&>();
    test_add_rvalue_reference<const volatile int&>();
    test_add_rvalue_reference<int&&>();
    test_add_rvalue_reference<const int&&>();
    test_add_rvalue_reference<volatile int&&>();
    test_add_rvalue_reference<const volatile int&&>();
    test_add_rvalue_reference<int*>();
    test_add_rvalue_reference<const int*>();
    test_add_rvalue_reference<volatile int*>();
    test_add_rvalue_reference<const volatile int*>();
    test_add_rvalue_reference<int**>();
    test_add_rvalue_reference<const int**>();
    test_add_rvalue_reference<volatile int**>();
    test_add_rvalue_reference<const volatile int**>();
    test_add_rvalue_reference<int*&>();
    test_add_rvalue_reference<const int*&>();
    test_add_rvalue_reference<volatile int*&>();
    test_add_rvalue_reference<const volatile int*&>();
    test_add_rvalue_reference<int*&&>();
    test_add_rvalue_reference<const int*&&>();
    test_add_rvalue_reference<volatile int*&&>();
    test_add_rvalue_reference<const volatile int*&&>();
    test_add_rvalue_reference<void*>();
    test_add_rvalue_reference<char[3]>();
    test_add_rvalue_reference<char[]>();
    test_add_rvalue_reference<char* [3]>();
    test_add_rvalue_reference<char*[]>();
    test_add_rvalue_reference<int(*)[3]>();
    test_add_rvalue_reference<int(*)[]>();
    test_add_rvalue_reference<int(&)[3]>();
    test_add_rvalue_reference<int(&)[]>();
    test_add_rvalue_reference<int(&&)[3]>();
    test_add_rvalue_reference<int(&&)[]>();
    test_add_rvalue_reference<char[3][2]>();
    test_add_rvalue_reference<char[][2]>();
    test_add_rvalue_reference<char* [3][2]>();
    test_add_rvalue_reference<char*[][2]>();
    test_add_rvalue_reference<int(*)[3][2]>();
    test_add_rvalue_reference<int(*)[][2]>();
    test_add_rvalue_reference<int(&)[3][2]>();
    test_add_rvalue_reference<int(&)[][2]>();
    test_add_rvalue_reference<int(&&)[3][2]>();
    test_add_rvalue_reference<int(&&)[][2]>();
    test_add_rvalue_reference<class_type>();
    test_add_rvalue_reference<class_type[]>();
    test_add_rvalue_reference<class_type[2]>();
    test_add_rvalue_reference<template_type<void>>();
    test_add_rvalue_reference<template_type<int>>();
    test_add_rvalue_reference<template_type<class_type>>();
    test_add_rvalue_reference<template_type<incomplete_type>>();
    test_add_rvalue_reference<variadic_template<>>();
    test_add_rvalue_reference<variadic_template<void>>();
    test_add_rvalue_reference<variadic_template<int>>();
    test_add_rvalue_reference<variadic_template<class_type>>();
    test_add_rvalue_reference<variadic_template<incomplete_type>>();
    test_add_rvalue_reference<variadic_template<int, void, class_type, volatile char[]>>();
    test_add_rvalue_reference<public_derived_from<base>>();
    test_add_rvalue_reference<public_derived_from<derived>>();
    test_add_rvalue_reference<public_derived_from<class_type>>();
    test_add_rvalue_reference<private_derived_from<base>>();
    test_add_rvalue_reference<private_derived_from<derived>>();
    test_add_rvalue_reference<private_derived_from<class_type>>();
    test_add_rvalue_reference<protected_derived_from<base>>();
    test_add_rvalue_reference<protected_derived_from<derived>>();
    test_add_rvalue_reference<protected_derived_from<class_type>>();
    test_add_rvalue_reference<union_type>();
    test_add_rvalue_reference<non_empty_union>();
    test_add_rvalue_reference<empty>();
    test_add_rvalue_reference<not_empty>();
    test_add_rvalue_reference<bit_zero>();
    test_add_rvalue_reference<bit_one>();
    test_add_rvalue_reference<base>();
    test_add_rvalue_reference<derived>();
    test_add_rvalue_reference<abstract>();
    test_add_rvalue_reference<public_abstract>();
    test_add_rvalue_reference<private_abstract>();
    test_add_rvalue_reference<protected_abstract>();
    test_add_rvalue_reference<abstract_template<int>>();
    test_add_rvalue_reference<abstract_template<double>>();
    test_add_rvalue_reference<abstract_template<class_type>>();
    test_add_rvalue_reference<abstract_template<incomplete_type>>();
    test_add_rvalue_reference<final_type>();
    test_add_rvalue_reference<public_destructor>();
    test_add_rvalue_reference<protected_destructor>();
    test_add_rvalue_reference<private_destructor>();
    test_add_rvalue_reference<virtual_public_destructor>();
    test_add_rvalue_reference<virtual_protected_destructor>();
    test_add_rvalue_reference<virtual_private_destructor>();
    test_add_rvalue_reference<pure_public_destructor>();
    test_add_rvalue_reference<pure_protected_destructor>();
    test_add_rvalue_reference<pure_private_destructor>();
    test_add_rvalue_reference<deleted_public_destructor>();
    test_add_rvalue_reference<deleted_protected_destructor>();
    test_add_rvalue_reference<deleted_private_destructor>();
    test_add_rvalue_reference<deleted_virtual_public_destructor>();
    test_add_rvalue_reference<deleted_virtual_protected_destructor>();
    test_add_rvalue_reference<deleted_virtual_private_destructor>();
    test_add_rvalue_reference<Enum>();
    test_add_rvalue_reference<EnumSigned>();
    test_add_rvalue_reference<EnumUnsigned>();
    test_add_rvalue_reference<EnumClass>();
    test_add_rvalue_reference<EnumStruct>();
    test_add_rvalue_reference<function_type>();
    test_add_rvalue_reference<function_ptr>();
    test_add_rvalue_reference<member_object_ptr>();
    test_add_rvalue_reference<member_function_ptr>();
    test_add_rvalue_reference<incomplete_type>();
    test_add_rvalue_reference<incomplete_template<void>>();
    test_add_rvalue_reference<incomplete_template<int>>();
    test_add_rvalue_reference<incomplete_template<class_type>>();
    test_add_rvalue_reference<incomplete_template<incomplete_type>>();
    test_add_rvalue_reference<incomplete_variadic_template<>>();
    test_add_rvalue_reference<incomplete_variadic_template<void>>();
    test_add_rvalue_reference<incomplete_variadic_template<int>>();
    test_add_rvalue_reference<incomplete_variadic_template<class_type>>();
    test_add_rvalue_reference<incomplete_variadic_template<incomplete_type>>();
    test_add_rvalue_reference<
            incomplete_variadic_template<int, void, class_type, volatile char[]>>();
    test_add_rvalue_reference<int class_type::*>();
    test_add_rvalue_reference<float class_type::*>();
    test_add_rvalue_reference<void * class_type::*>();
    test_add_rvalue_reference<int * class_type::*>();
    test_add_rvalue_reference<int class_type::*&>();
    test_add_rvalue_reference<float class_type::*&>();
    test_add_rvalue_reference<void * class_type::*&>();
    test_add_rvalue_reference<int * class_type::*&>();
    test_add_rvalue_reference<int class_type::*&&>();
    test_add_rvalue_reference<float class_type::*&&>();
    test_add_rvalue_reference<void * class_type::*&&>();
    test_add_rvalue_reference<int * class_type::*&&>();
    test_add_rvalue_reference<int class_type::* const>();
    test_add_rvalue_reference<float class_type::* const>();
    test_add_rvalue_reference<void * class_type::* const>();
    test_add_rvalue_reference<int class_type::* const&>();
    test_add_rvalue_reference<float class_type::* const&>();
    test_add_rvalue_reference<void * class_type::* const&>();
    test_add_rvalue_reference<int class_type::* const&&>();
    test_add_rvalue_reference<float class_type::* const&&>();
    test_add_rvalue_reference<void * class_type::* const&&>();
    test_add_rvalue_reference<int class_type::* volatile>();
    test_add_rvalue_reference<float class_type::* volatile>();
    test_add_rvalue_reference<void * class_type::* volatile>();
    test_add_rvalue_reference<int class_type::* volatile&>();
    test_add_rvalue_reference<float class_type::* volatile&>();
    test_add_rvalue_reference<void * class_type::* volatile&>();
    test_add_rvalue_reference<int class_type::* volatile&&>();
    test_add_rvalue_reference<float class_type::* volatile&&>();
    test_add_rvalue_reference<void * class_type::* volatile&&>();
    test_add_rvalue_reference<int class_type::* const volatile>();
    test_add_rvalue_reference<float class_type::* const volatile>();
    test_add_rvalue_reference<void * class_type::* const volatile>();
    test_add_rvalue_reference<int class_type::* const volatile&>();
    test_add_rvalue_reference<float class_type::* const volatile&>();
    test_add_rvalue_reference<void * class_type::* const volatile&>();
    test_add_rvalue_reference<int class_type::* const volatile&&>();
    test_add_rvalue_reference<float class_type::* const volatile&&>();
    test_add_rvalue_reference<void * class_type::* const volatile&&>();
    test_add_rvalue_reference<non_copyable>();
    test_add_rvalue_reference<non_moveable>();
    test_add_rvalue_reference<non_constructible>();
    test_add_rvalue_reference<tracked>();
    test_add_rvalue_reference<trap_constructible>();
    test_add_rvalue_reference<trap_implicit_conversion>();
    test_add_rvalue_reference<trap_comma>();
    test_add_rvalue_reference<trap_call>();
    test_add_rvalue_reference<trap_self_assign>();
    test_add_rvalue_reference<trap_deref>();
    test_add_rvalue_reference<trap_array_subscript>();

    test_function0<void()>();
    test_function1<void()&>();
    test_function1<void() &&>();
    test_function1<void() const>();
    test_function1<void() const&>();
    test_function1<void() const&&>();
    test_function1<void() volatile>();
    test_function1<void() volatile&>();
    test_function1<void() volatile&&>();
    test_function1<void() const volatile>();
    test_function1<void() const volatile&>();
    test_function1<void() const volatile&&>();
    test_function0<void() noexcept>();
    test_function1<void() & noexcept>();
    test_function1<void() && noexcept>();
    test_function1<void() const noexcept>();
    test_function1<void() const & noexcept>();
    test_function1<void() const && noexcept>();
    test_function1<void() volatile noexcept>();
    test_function1<void() volatile & noexcept>();
    test_function1<void() volatile && noexcept>();
    test_function1<void() const volatile noexcept>();
    test_function1<void() const volatile & noexcept>();
    test_function1<void() const volatile && noexcept>();

    test_function0<void(int)>();
    test_function1<void(int)&>();
    test_function1<void(int) &&>();
    test_function1<void(int) const>();
    test_function1<void(int) const&>();
    test_function1<void(int) const&&>();
    test_function1<void(int) volatile>();
    test_function1<void(int) volatile&>();
    test_function1<void(int) volatile&&>();
    test_function1<void(int) const volatile>();
    test_function1<void(int) const volatile&>();
    test_function1<void(int) const volatile&&>();
    test_function0<void(int) noexcept>();
    test_function1<void(int) & noexcept>();
    test_function1<void(int) && noexcept>();
    test_function1<void(int) const noexcept>();
    test_function1<void(int) const & noexcept>();
    test_function1<void(int) const && noexcept>();
    test_function1<void(int) volatile noexcept>();
    test_function1<void(int) volatile & noexcept>();
    test_function1<void(int) volatile && noexcept>();
    test_function1<void(int) const volatile noexcept>();
    test_function1<void(int) const volatile & noexcept>();
    test_function1<void(int) const volatile && noexcept>();

    test_function0<void(...)>();
    test_function1<void(...)&>();
    test_function1<void(...) &&>();
    test_function1<void(...) const>();
    test_function1<void(...) const&>();
    test_function1<void(...) const&&>();
    test_function1<void(...) volatile>();
    test_function1<void(...) volatile&>();
    test_function1<void(...) volatile&&>();
    test_function1<void(...) const volatile>();
    test_function1<void(...) const volatile&>();
    test_function1<void(...) const volatile&&>();
    test_function0<void(...) noexcept>();
    test_function1<void(...) & noexcept>();
    test_function1<void(...) && noexcept>();
    test_function1<void(...) const noexcept>();
    test_function1<void(...) const & noexcept>();
    test_function1<void(...) const && noexcept>();
    test_function1<void(...) volatile noexcept>();
    test_function1<void(...) volatile & noexcept>();
    test_function1<void(...) volatile && noexcept>();
    test_function1<void(...) const volatile noexcept>();
    test_function1<void(...) const volatile & noexcept>();
    test_function1<void(...) const volatile && noexcept>();

    test_function0<void(int, ...)>();
    test_function1<void(int, ...)&>();
    test_function1<void(int, ...) &&>();
    test_function1<void(int, ...) const>();
    test_function1<void(int, ...) const&>();
    test_function1<void(int, ...) const&&>();
    test_function1<void(int, ...) volatile>();
    test_function1<void(int, ...) volatile&>();
    test_function1<void(int, ...) volatile&&>();
    test_function1<void(int, ...) const volatile>();
    test_function1<void(int, ...) const volatile&>();
    test_function1<void(int, ...) const volatile&&>();
    test_function0<void(int, ...) noexcept>();
    test_function1<void(int, ...) & noexcept>();
    test_function1<void(int, ...) && noexcept>();
    test_function1<void(int, ...) const noexcept>();
    test_function1<void(int, ...) const & noexcept>();
    test_function1<void(int, ...) const && noexcept>();
    test_function1<void(int, ...) volatile noexcept>();
    test_function1<void(int, ...) volatile & noexcept>();
    test_function1<void(int, ...) volatile && noexcept>();
    test_function1<void(int, ...) const volatile noexcept>();
    test_function1<void(int, ...) const volatile & noexcept>();
    test_function1<void(int, ...) const volatile && noexcept>();

    test_function0<int()>();
    test_function1<int()&>();
    test_function1<int() &&>();
    test_function1<int() const>();
    test_function1<int() const&>();
    test_function1<int() const&&>();
    test_function1<int() volatile>();
    test_function1<int() volatile&>();
    test_function1<int() volatile&&>();
    test_function1<int() const volatile>();
    test_function1<int() const volatile&>();
    test_function1<int() const volatile&&>();
    test_function0<int() noexcept>();
    test_function1<int() & noexcept>();
    test_function1<int() && noexcept>();
    test_function1<int() const noexcept>();
    test_function1<int() const & noexcept>();
    test_function1<int() const && noexcept>();
    test_function1<int() volatile noexcept>();
    test_function1<int() volatile & noexcept>();
    test_function1<int() volatile && noexcept>();
    test_function1<int() const volatile noexcept>();
    test_function1<int() const volatile & noexcept>();
    test_function1<int() const volatile && noexcept>();

    test_function0<int(int)>();
    test_function1<int(int)&>();
    test_function1<int(int) &&>();
    test_function1<int(int) const>();
    test_function1<int(int) const&>();
    test_function1<int(int) const&&>();
    test_function1<int(int) volatile>();
    test_function1<int(int) volatile&>();
    test_function1<int(int) volatile&&>();
    test_function1<int(int) const volatile>();
    test_function1<int(int) const volatile&>();
    test_function1<int(int) const volatile&&>();
    test_function0<int(int) noexcept>();
    test_function1<int(int) & noexcept>();
    test_function1<int(int) && noexcept>();
    test_function1<int(int) const noexcept>();
    test_function1<int(int) const & noexcept>();
    test_function1<int(int) const && noexcept>();
    test_function1<int(int) volatile noexcept>();
    test_function1<int(int) volatile & noexcept>();
    test_function1<int(int) volatile && noexcept>();
    test_function1<int(int) const volatile noexcept>();
    test_function1<int(int) const volatile & noexcept>();
    test_function1<int(int) const volatile && noexcept>();

    test_function0<int(...)>();
    test_function1<int(...)&>();
    test_function1<int(...) &&>();
    test_function1<int(...) const>();
    test_function1<int(...) const&>();
    test_function1<int(...) const&&>();
    test_function1<int(...) volatile>();
    test_function1<int(...) volatile&>();
    test_function1<int(...) volatile&&>();
    test_function1<int(...) const volatile>();
    test_function1<int(...) const volatile&>();
    test_function1<int(...) const volatile&&>();
    test_function0<int(...) noexcept>();
    test_function1<int(...) & noexcept>();
    test_function1<int(...) && noexcept>();
    test_function1<int(...) const noexcept>();
    test_function1<int(...) const & noexcept>();
    test_function1<int(...) const && noexcept>();
    test_function1<int(...) volatile noexcept>();
    test_function1<int(...) volatile & noexcept>();
    test_function1<int(...) volatile && noexcept>();
    test_function1<int(...) const volatile noexcept>();
    test_function1<int(...) const volatile & noexcept>();
    test_function1<int(...) const volatile && noexcept>();

    test_function0<int(int, ...)>();
    test_function1<int(int, ...)&>();
    test_function1<int(int, ...) &&>();
    test_function1<int(int, ...) const>();
    test_function1<int(int, ...) const&>();
    test_function1<int(int, ...) const&&>();
    test_function1<int(int, ...) volatile>();
    test_function1<int(int, ...) volatile&>();
    test_function1<int(int, ...) volatile&&>();
    test_function1<int(int, ...) const volatile>();
    test_function1<int(int, ...) const volatile&>();
    test_function1<int(int, ...) const volatile&&>();
    test_function0<int(int, ...) noexcept>();
    test_function1<int(int, ...) & noexcept>();
    test_function1<int(int, ...) && noexcept>();
    test_function1<int(int, ...) const noexcept>();
    test_function1<int(int, ...) const & noexcept>();
    test_function1<int(int, ...) const && noexcept>();
    test_function1<int(int, ...) volatile noexcept>();
    test_function1<int(int, ...) volatile & noexcept>();
    test_function1<int(int, ...) volatile && noexcept>();
    test_function1<int(int, ...) const volatile noexcept>();
    test_function1<int(int, ...) const volatile & noexcept>();
    test_function1<int(int, ...) const volatile && noexcept>();

    test_add_rvalue_reference<void (*)()>();
    test_add_rvalue_reference<void (*)() noexcept>();

    test_add_rvalue_reference<void (*)(int)>();
    test_add_rvalue_reference<void (*)(int) noexcept>();

    test_add_rvalue_reference<void (*)(...)>();
    test_add_rvalue_reference<void (*)(...) noexcept>();

    test_add_rvalue_reference<void (*)(int, ...)>();
    test_add_rvalue_reference<void (*)(int, ...) noexcept>();

    test_add_rvalue_reference<int (*)()>();
    test_add_rvalue_reference<int (*)() noexcept>();

    test_add_rvalue_reference<int (*)(int)>();
    test_add_rvalue_reference<int (*)(int) noexcept>();

    test_add_rvalue_reference<int (*)(...)>();
    test_add_rvalue_reference<int (*)(...) noexcept>();

    test_add_rvalue_reference<int (*)(int, ...)>();
    test_add_rvalue_reference<int (*)(int, ...) noexcept>();

    test_add_rvalue_reference<void (&)()>();
    test_add_rvalue_reference<void (&)() noexcept>();

    test_add_rvalue_reference<void (&)(int)>();
    test_add_rvalue_reference<void (&)(int) noexcept>();

    test_add_rvalue_reference<void (&)(...)>();
    test_add_rvalue_reference<void (&)(...) noexcept>();

    test_add_rvalue_reference<void (&)(int, ...)>();
    test_add_rvalue_reference<void (&)(int, ...) noexcept>();

    test_add_rvalue_reference<int (&)()>();
    test_add_rvalue_reference<int (&)() noexcept>();

    test_add_rvalue_reference<int (&)(int)>();
    test_add_rvalue_reference<int (&)(int) noexcept>();

    test_add_rvalue_reference<int (&)(...)>();
    test_add_rvalue_reference<int (&)(...) noexcept>();

    test_add_rvalue_reference<int (&)(int, ...)>();
    test_add_rvalue_reference<int (&)(int, ...) noexcept>();

    test_add_rvalue_reference<void (&&)()>();
    test_add_rvalue_reference<void (&&)() noexcept>();

    test_add_rvalue_reference<void (&&)(int)>();
    test_add_rvalue_reference<void (&&)(int) noexcept>();

    test_add_rvalue_reference<void (&&)(...)>();
    test_add_rvalue_reference<void (&&)(...) noexcept>();

    test_add_rvalue_reference<void (&&)(int, ...)>();
    test_add_rvalue_reference<void (&&)(int, ...) noexcept>();

    test_add_rvalue_reference<int (&&)()>();
    test_add_rvalue_reference<int (&&)() noexcept>();

    test_add_rvalue_reference<int (&&)(int)>();
    test_add_rvalue_reference<int (&&)(int) noexcept>();

    test_add_rvalue_reference<int (&&)(...)>();
    test_add_rvalue_reference<int (&&)(...) noexcept>();

    test_add_rvalue_reference<int (&&)(int, ...)>();
    test_add_rvalue_reference<int (&&)(int, ...) noexcept>();

    test_add_rvalue_reference<void (class_type::*)()>();
    test_add_rvalue_reference<void (class_type::*)()&>();
    test_add_rvalue_reference<void (class_type::*)() &&>();
    test_add_rvalue_reference<void (class_type::*)() const>();
    test_add_rvalue_reference<void (class_type::*)() const&>();
    test_add_rvalue_reference<void (class_type::*)() const&&>();
    test_add_rvalue_reference<void (class_type::*)() noexcept>();
    test_add_rvalue_reference<void (class_type::*)() & noexcept>();
    test_add_rvalue_reference<void (class_type::*)() && noexcept>();
    test_add_rvalue_reference<void (class_type::*)() const noexcept>();
    test_add_rvalue_reference<void (class_type::*)() const & noexcept>();
    test_add_rvalue_reference<void (class_type::*)() const && noexcept>();

    test_add_rvalue_reference<void (class_type::*)(int)>();
    test_add_rvalue_reference<void (class_type::*)(int)&>();
    test_add_rvalue_reference<void (class_type::*)(int) &&>();
    test_add_rvalue_reference<void (class_type::*)(int) const>();
    test_add_rvalue_reference<void (class_type::*)(int) const&>();
    test_add_rvalue_reference<void (class_type::*)(int) const&&>();
    test_add_rvalue_reference<void (class_type::*)(int) noexcept>();
    test_add_rvalue_reference<void (class_type::*)(int) & noexcept>();
    test_add_rvalue_reference<void (class_type::*)(int) && noexcept>();
    test_add_rvalue_reference<void (class_type::*)(int) const noexcept>();
    test_add_rvalue_reference<void (class_type::*)(int) const & noexcept>();
    test_add_rvalue_reference<void (class_type::*)(int) const && noexcept>();

    test_add_rvalue_reference<void (class_type::*)(...)>();
    test_add_rvalue_reference<void (class_type::*)(...)&>();
    test_add_rvalue_reference<void (class_type::*)(...) &&>();
    test_add_rvalue_reference<void (class_type::*)(...) const>();
    test_add_rvalue_reference<void (class_type::*)(...) const&>();
    test_add_rvalue_reference<void (class_type::*)(...) const&&>();
    test_add_rvalue_reference<void (class_type::*)(...) noexcept>();
    test_add_rvalue_reference<void (class_type::*)(...) & noexcept>();
    test_add_rvalue_reference<void (class_type::*)(...) && noexcept>();
    test_add_rvalue_reference<void (class_type::*)(...) const noexcept>();
    test_add_rvalue_reference<void (class_type::*)(...) const & noexcept>();
    test_add_rvalue_reference<void (class_type::*)(...) const && noexcept>();

    test_add_rvalue_reference<void (class_type::*)(int, ...)>();
    test_add_rvalue_reference<void (class_type::*)(int, ...)&>();
    test_add_rvalue_reference<void (class_type::*)(int, ...) &&>();
    test_add_rvalue_reference<void (class_type::*)(int, ...) const>();
    test_add_rvalue_reference<void (class_type::*)(int, ...) const&>();
    test_add_rvalue_reference<void (class_type::*)(int, ...) const&&>();
    test_add_rvalue_reference<void (class_type::*)(int, ...) noexcept>();
    test_add_rvalue_reference<void (class_type::*)(int, ...) & noexcept>();
    test_add_rvalue_reference<void (class_type::*)(int, ...) && noexcept>();
    test_add_rvalue_reference<void (class_type::*)(int, ...) const noexcept>();
    test_add_rvalue_reference<void (class_type::*)(int, ...) const & noexcept>();
    test_add_rvalue_reference<void (class_type::*)(int, ...) const && noexcept>();

    test_add_rvalue_reference<int (class_type::*)()>();
    test_add_rvalue_reference<int (class_type::*)()&>();
    test_add_rvalue_reference<int (class_type::*)() &&>();
    test_add_rvalue_reference<int (class_type::*)() const>();
    test_add_rvalue_reference<int (class_type::*)() const&>();
    test_add_rvalue_reference<int (class_type::*)() const&&>();
    test_add_rvalue_reference<int (class_type::*)() noexcept>();
    test_add_rvalue_reference<int (class_type::*)() & noexcept>();
    test_add_rvalue_reference<int (class_type::*)() && noexcept>();
    test_add_rvalue_reference<int (class_type::*)() const noexcept>();
    test_add_rvalue_reference<int (class_type::*)() const & noexcept>();
    test_add_rvalue_reference<int (class_type::*)() const && noexcept>();

    test_add_rvalue_reference<int (class_type::*)(int)>();
    test_add_rvalue_reference<int (class_type::*)(int)&>();
    test_add_rvalue_reference<int (class_type::*)(int) &&>();
    test_add_rvalue_reference<int (class_type::*)(int) const>();
    test_add_rvalue_reference<int (class_type::*)(int) const&>();
    test_add_rvalue_reference<int (class_type::*)(int) const&&>();
    test_add_rvalue_reference<int (class_type::*)(int) noexcept>();
    test_add_rvalue_reference<int (class_type::*)(int) & noexcept>();
    test_add_rvalue_reference<int (class_type::*)(int) && noexcept>();
    test_add_rvalue_reference<int (class_type::*)(int) const noexcept>();
    test_add_rvalue_reference<int (class_type::*)(int) const & noexcept>();
    test_add_rvalue_reference<int (class_type::*)(int) const && noexcept>();

    test_add_rvalue_reference<int (class_type::*)(...)>();
    test_add_rvalue_reference<int (class_type::*)(...)&>();
    test_add_rvalue_reference<int (class_type::*)(...) &&>();
    test_add_rvalue_reference<int (class_type::*)(...) const>();
    test_add_rvalue_reference<int (class_type::*)(...) const&>();
    test_add_rvalue_reference<int (class_type::*)(...) const&&>();
    test_add_rvalue_reference<int (class_type::*)(...) noexcept>();
    test_add_rvalue_reference<int (class_type::*)(...) & noexcept>();
    test_add_rvalue_reference<int (class_type::*)(...) && noexcept>();
    test_add_rvalue_reference<int (class_type::*)(...) const noexcept>();
    test_add_rvalue_reference<int (class_type::*)(...) const & noexcept>();
    test_add_rvalue_reference<int (class_type::*)(...) const && noexcept>();

    test_add_rvalue_reference<int (class_type::*)(int, ...)>();
    test_add_rvalue_reference<int (class_type::*)(int, ...)&>();
    test_add_rvalue_reference<int (class_type::*)(int, ...) &&>();
    test_add_rvalue_reference<int (class_type::*)(int, ...) const>();
    test_add_rvalue_reference<int (class_type::*)(int, ...) const&>();
    test_add_rvalue_reference<int (class_type::*)(int, ...) const&&>();
    test_add_rvalue_reference<int (class_type::*)(int, ...) noexcept>();
    test_add_rvalue_reference<int (class_type::*)(int, ...) & noexcept>();
    test_add_rvalue_reference<int (class_type::*)(int, ...) && noexcept>();
    test_add_rvalue_reference<int (class_type::*)(int, ...) const noexcept>();
    test_add_rvalue_reference<int (class_type::*)(int, ...) const & noexcept>();
    test_add_rvalue_reference<int (class_type::*)(int, ...) const && noexcept>();

    //  LWG 2101 specifically talks about add_rvalue_reference and functions.
    //  The term of art is "a referenceable type", which a cv- or ref-qualified function is not.
    test_function0<function_ptr>();
    test_function0<void()>();
    test_function1<void() const>();
    test_function1<void()&>();
    test_function1<void() &&>();
    test_function1<void() const&>();
    test_function1<void() const&&>();

    test_function0<void() noexcept>();
    test_function1<void() const noexcept>();
    test_function1<void() & noexcept>();
    test_function1<void() && noexcept>();
    test_function1<void() const & noexcept>();
    test_function1<void() const && noexcept>();

    //  But a cv- or ref-qualified member function *is* "a referenceable type"
    test_function0<member_function_ptr>();
    test_function0<void (Foo::*)()>();
    test_function0<void (Foo::*)() const>();
    test_function0<void (Foo::*)()&>();
    test_function0<void (Foo::*)() &&>();
    test_function0<void (Foo::*)() const&>();
    test_function0<void (Foo::*)() const&&>();

    test_function0<void (Foo::*)() noexcept>();
    test_function0<void (Foo::*)() const noexcept>();
    test_function0<void (Foo::*)() & noexcept>();
    test_function0<void (Foo::*)() && noexcept>();
    test_function0<void (Foo::*)() const & noexcept>();
    test_function0<void (Foo::*)() const && noexcept>();
}
