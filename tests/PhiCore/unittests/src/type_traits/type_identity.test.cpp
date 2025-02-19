#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/type_identity.hpp>
#include <vector>

template <typename TypeT>
void test_type_identity()
{
    CHECK_SAME_TYPE(TypeT, typename phi::type_identity<TypeT>::type);
    CHECK_SAME_TYPE(const TypeT, const typename phi::type_identity<TypeT>::type);
    CHECK_SAME_TYPE(volatile TypeT, volatile typename phi::type_identity<TypeT>::type);
    CHECK_SAME_TYPE(const volatile TypeT, const volatile typename phi::type_identity<TypeT>::type);

    CHECK_SAME_TYPE(const TypeT, typename phi::type_identity<const TypeT>::type);
    CHECK_SAME_TYPE(volatile TypeT, typename phi::type_identity<volatile TypeT>::type);
    CHECK_SAME_TYPE(const volatile TypeT, typename phi::type_identity<const volatile TypeT>::type);

    CHECK_SAME_TYPE(TypeT, phi::type_identity_t<TypeT>);
    CHECK_SAME_TYPE(const TypeT, const phi::type_identity_t<TypeT>);
    CHECK_SAME_TYPE(volatile TypeT, volatile phi::type_identity_t<TypeT>);
    CHECK_SAME_TYPE(const volatile TypeT, const volatile phi::type_identity_t<TypeT>);

    CHECK_SAME_TYPE(const TypeT, phi::type_identity_t<const TypeT>);
    CHECK_SAME_TYPE(volatile TypeT, phi::type_identity_t<volatile TypeT>);
    CHECK_SAME_TYPE(const volatile TypeT, phi::type_identity_t<const volatile TypeT>);
}

TEST_CASE("type_identity")
{
    test_type_identity<void>();
    test_type_identity<phi::nullptr_t>();
    test_type_identity<bool>();
    test_type_identity<char>();
    test_type_identity<signed char>();
    test_type_identity<unsigned char>();
    test_type_identity<short>();
    test_type_identity<unsigned short>();
    test_type_identity<int>();
    test_type_identity<unsigned int>();
    test_type_identity<long>();
    test_type_identity<unsigned long>();
    test_type_identity<long long>();
    test_type_identity<unsigned long long>();
    test_type_identity<float>();
    test_type_identity<double>();
    test_type_identity<long double>();
    test_type_identity<char8_t>();
    test_type_identity<char16_t>();
    test_type_identity<char32_t>();
    test_type_identity<wchar_t>();

    test_type_identity<phi::boolean>();
    test_type_identity<phi::integer<signed char>>();
    test_type_identity<phi::integer<unsigned char>>();
    test_type_identity<phi::integer<short>>();
    test_type_identity<phi::integer<unsigned short>>();
    test_type_identity<phi::integer<int>>();
    test_type_identity<phi::integer<unsigned int>>();
    test_type_identity<phi::integer<long>>();
    test_type_identity<phi::integer<unsigned long>>();
    test_type_identity<phi::integer<long long>>();
    test_type_identity<phi::integer<unsigned long long>>();
    test_type_identity<phi::floating_point<float>>();
    test_type_identity<phi::floating_point<double>>();
    test_type_identity<phi::floating_point<long double>>();

    test_type_identity<std::vector<int>>();
    test_type_identity<phi::scope_ptr<int>>();

    test_type_identity<int&>();
    test_type_identity<const int&>();
    test_type_identity<volatile int&>();
    test_type_identity<const volatile int&>();
    test_type_identity<int&&>();
    test_type_identity<const int&&>();
    test_type_identity<volatile int&&>();
    test_type_identity<const volatile int&&>();
    test_type_identity<int*>();
    test_type_identity<const int*>();
    test_type_identity<volatile int*>();
    test_type_identity<const volatile int*>();
    test_type_identity<int**>();
    test_type_identity<const int**>();
    test_type_identity<volatile int**>();
    test_type_identity<const volatile int**>();
    test_type_identity<int*&>();
    test_type_identity<const int*&>();
    test_type_identity<volatile int*&>();
    test_type_identity<const volatile int*&>();
    test_type_identity<int*&&>();
    test_type_identity<const int*&&>();
    test_type_identity<volatile int*&&>();
    test_type_identity<const volatile int*&&>();
    test_type_identity<void*>();
    test_type_identity<char[3]>();
    test_type_identity<char[]>();
    test_type_identity<char* [3]>();
    test_type_identity<char*[]>();
    test_type_identity<int(*)[3]>();
    test_type_identity<int(*)[]>();
    test_type_identity<int(&)[3]>();
    test_type_identity<int(&)[]>();
    test_type_identity<int(&&)[3]>();
    test_type_identity<int(&&)[]>();
    test_type_identity<char[3][2]>();
    test_type_identity<char[][2]>();
    test_type_identity<char* [3][2]>();
    test_type_identity<char*[][2]>();
    test_type_identity<int(*)[3][2]>();
    test_type_identity<int(*)[][2]>();
    test_type_identity<int(&)[3][2]>();
    test_type_identity<int(&)[][2]>();
    test_type_identity<int(&&)[3][2]>();
    test_type_identity<int(&&)[][2]>();
    test_type_identity<class_type>();
    test_type_identity<class_type[]>();
    test_type_identity<class_type[2]>();
    test_type_identity<template_type<void>>();
    test_type_identity<template_type<int>>();
    test_type_identity<template_type<class_type>>();
    test_type_identity<template_type<incomplete_type>>();
    test_type_identity<variadic_template<>>();
    test_type_identity<variadic_template<void>>();
    test_type_identity<variadic_template<int>>();
    test_type_identity<variadic_template<class_type>>();
    test_type_identity<variadic_template<incomplete_type>>();
    test_type_identity<variadic_template<int, void, class_type, volatile char[]>>();
    test_type_identity<public_derived_from<base>>();
    test_type_identity<public_derived_from<derived>>();
    test_type_identity<public_derived_from<class_type>>();
    test_type_identity<private_derived_from<base>>();
    test_type_identity<private_derived_from<derived>>();
    test_type_identity<private_derived_from<class_type>>();
    test_type_identity<protected_derived_from<base>>();
    test_type_identity<protected_derived_from<derived>>();
    test_type_identity<protected_derived_from<class_type>>();
    test_type_identity<union_type>();
    test_type_identity<non_empty_union>();
    test_type_identity<empty>();
    test_type_identity<not_empty>();
    test_type_identity<bit_zero>();
    test_type_identity<bit_one>();
    test_type_identity<base>();
    test_type_identity<derived>();
    test_type_identity<abstract>();
    test_type_identity<public_abstract>();
    test_type_identity<private_abstract>();
    test_type_identity<protected_abstract>();
    test_type_identity<abstract_template<int>>();
    test_type_identity<abstract_template<double>>();
    test_type_identity<abstract_template<class_type>>();
    test_type_identity<abstract_template<incomplete_type>>();
    test_type_identity<final_type>();
    test_type_identity<public_destructor>();
    test_type_identity<protected_destructor>();
    test_type_identity<private_destructor>();
    test_type_identity<virtual_public_destructor>();
    test_type_identity<virtual_protected_destructor>();
    test_type_identity<virtual_private_destructor>();
    test_type_identity<pure_public_destructor>();
    test_type_identity<pure_protected_destructor>();
    test_type_identity<pure_private_destructor>();
    test_type_identity<deleted_public_destructor>();
    test_type_identity<deleted_protected_destructor>();
    test_type_identity<deleted_private_destructor>();
    test_type_identity<deleted_virtual_public_destructor>();
    test_type_identity<deleted_virtual_protected_destructor>();
    test_type_identity<deleted_virtual_private_destructor>();
    test_type_identity<Enum>();
    test_type_identity<EnumSigned>();
    test_type_identity<EnumUnsigned>();
    test_type_identity<EnumClass>();
    test_type_identity<EnumStruct>();
    test_type_identity<function_type>();
    test_type_identity<function_ptr>();
    test_type_identity<member_object_ptr>();
    test_type_identity<member_function_ptr>();
    test_type_identity<incomplete_type>();
    test_type_identity<incomplete_template<void>>();
    test_type_identity<incomplete_template<int>>();
    test_type_identity<incomplete_template<class_type>>();
    test_type_identity<incomplete_template<incomplete_type>>();
    test_type_identity<incomplete_variadic_template<>>();
    test_type_identity<incomplete_variadic_template<void>>();
    test_type_identity<incomplete_variadic_template<int>>();
    test_type_identity<incomplete_variadic_template<class_type>>();
    test_type_identity<incomplete_variadic_template<incomplete_type>>();
    test_type_identity<incomplete_variadic_template<int, void, class_type, volatile char[]>>();
    test_type_identity<int class_type::*>();
    test_type_identity<float class_type::*>();
    test_type_identity<void * class_type::*>();
    test_type_identity<int * class_type::*>();
    test_type_identity<int class_type::*&>();
    test_type_identity<float class_type::*&>();
    test_type_identity<void * class_type::*&>();
    test_type_identity<int * class_type::*&>();
    test_type_identity<int class_type::*&&>();
    test_type_identity<float class_type::*&&>();
    test_type_identity<void * class_type::*&&>();
    test_type_identity<int * class_type::*&&>();
    test_type_identity<int class_type::* const>();
    test_type_identity<float class_type::* const>();
    test_type_identity<void * class_type::* const>();
    test_type_identity<int class_type::* const&>();
    test_type_identity<float class_type::* const&>();
    test_type_identity<void * class_type::* const&>();
    test_type_identity<int class_type::* const&&>();
    test_type_identity<float class_type::* const&&>();
    test_type_identity<void * class_type::* const&&>();
    test_type_identity<int class_type::* volatile>();
    test_type_identity<float class_type::* volatile>();
    test_type_identity<void * class_type::* volatile>();
    test_type_identity<int class_type::* volatile&>();
    test_type_identity<float class_type::* volatile&>();
    test_type_identity<void * class_type::* volatile&>();
    test_type_identity<int class_type::* volatile&&>();
    test_type_identity<float class_type::* volatile&&>();
    test_type_identity<void * class_type::* volatile&&>();
    test_type_identity<int class_type::* const volatile>();
    test_type_identity<float class_type::* const volatile>();
    test_type_identity<void * class_type::* const volatile>();
    test_type_identity<int class_type::* const volatile&>();
    test_type_identity<float class_type::* const volatile&>();
    test_type_identity<void * class_type::* const volatile&>();
    test_type_identity<int class_type::* const volatile&&>();
    test_type_identity<float class_type::* const volatile&&>();
    test_type_identity<void * class_type::* const volatile&&>();
    test_type_identity<non_copyable>();
    test_type_identity<non_moveable>();
    test_type_identity<non_constructible>();
    test_type_identity<tracked>();
    test_type_identity<trap_constructible>();
    test_type_identity<trap_implicit_conversion>();
    test_type_identity<trap_comma>();
    test_type_identity<trap_call>();
    test_type_identity<trap_self_assign>();
    test_type_identity<trap_deref>();
    test_type_identity<trap_array_subscript>();

    test_type_identity<void()>();
    test_type_identity<void()&>();
    test_type_identity<void() &&>();
    test_type_identity<void() const>();
    test_type_identity<void() const&>();
    test_type_identity<void() const&&>();
    test_type_identity<void() volatile>();
    test_type_identity<void() volatile&>();
    test_type_identity<void() volatile&&>();
    test_type_identity<void() const volatile>();
    test_type_identity<void() const volatile&>();
    test_type_identity<void() const volatile&&>();
    test_type_identity<void() noexcept>();
    test_type_identity<void() & noexcept>();
    test_type_identity<void() && noexcept>();
    test_type_identity<void() const noexcept>();
    test_type_identity<void() const & noexcept>();
    test_type_identity<void() const && noexcept>();
    test_type_identity<void() volatile noexcept>();
    test_type_identity<void() volatile & noexcept>();
    test_type_identity<void() volatile && noexcept>();
    test_type_identity<void() const volatile noexcept>();
    test_type_identity<void() const volatile & noexcept>();
    test_type_identity<void() const volatile && noexcept>();

    test_type_identity<void(int)>();
    test_type_identity<void(int)&>();
    test_type_identity<void(int) &&>();
    test_type_identity<void(int) const>();
    test_type_identity<void(int) const&>();
    test_type_identity<void(int) const&&>();
    test_type_identity<void(int) volatile>();
    test_type_identity<void(int) volatile&>();
    test_type_identity<void(int) volatile&&>();
    test_type_identity<void(int) const volatile>();
    test_type_identity<void(int) const volatile&>();
    test_type_identity<void(int) const volatile&&>();
    test_type_identity<void(int) noexcept>();
    test_type_identity<void(int) & noexcept>();
    test_type_identity<void(int) && noexcept>();
    test_type_identity<void(int) const noexcept>();
    test_type_identity<void(int) const & noexcept>();
    test_type_identity<void(int) const && noexcept>();
    test_type_identity<void(int) volatile noexcept>();
    test_type_identity<void(int) volatile & noexcept>();
    test_type_identity<void(int) volatile && noexcept>();
    test_type_identity<void(int) const volatile noexcept>();
    test_type_identity<void(int) const volatile & noexcept>();
    test_type_identity<void(int) const volatile && noexcept>();

    test_type_identity<void(...)>();
    test_type_identity<void(...)&>();
    test_type_identity<void(...) &&>();
    test_type_identity<void(...) const>();
    test_type_identity<void(...) const&>();
    test_type_identity<void(...) const&&>();
    test_type_identity<void(...) volatile>();
    test_type_identity<void(...) volatile&>();
    test_type_identity<void(...) volatile&&>();
    test_type_identity<void(...) const volatile>();
    test_type_identity<void(...) const volatile&>();
    test_type_identity<void(...) const volatile&&>();
    test_type_identity<void(...) noexcept>();
    test_type_identity<void(...) & noexcept>();
    test_type_identity<void(...) && noexcept>();
    test_type_identity<void(...) const noexcept>();
    test_type_identity<void(...) const & noexcept>();
    test_type_identity<void(...) const && noexcept>();
    test_type_identity<void(...) volatile noexcept>();
    test_type_identity<void(...) volatile & noexcept>();
    test_type_identity<void(...) volatile && noexcept>();
    test_type_identity<void(...) const volatile noexcept>();
    test_type_identity<void(...) const volatile & noexcept>();
    test_type_identity<void(...) const volatile && noexcept>();

    test_type_identity<void(int, ...)>();
    test_type_identity<void(int, ...)&>();
    test_type_identity<void(int, ...) &&>();
    test_type_identity<void(int, ...) const>();
    test_type_identity<void(int, ...) const&>();
    test_type_identity<void(int, ...) const&&>();
    test_type_identity<void(int, ...) volatile>();
    test_type_identity<void(int, ...) volatile&>();
    test_type_identity<void(int, ...) volatile&&>();
    test_type_identity<void(int, ...) const volatile>();
    test_type_identity<void(int, ...) const volatile&>();
    test_type_identity<void(int, ...) const volatile&&>();
    test_type_identity<void(int, ...) noexcept>();
    test_type_identity<void(int, ...) & noexcept>();
    test_type_identity<void(int, ...) && noexcept>();
    test_type_identity<void(int, ...) const noexcept>();
    test_type_identity<void(int, ...) const & noexcept>();
    test_type_identity<void(int, ...) const && noexcept>();
    test_type_identity<void(int, ...) volatile noexcept>();
    test_type_identity<void(int, ...) volatile & noexcept>();
    test_type_identity<void(int, ...) volatile && noexcept>();
    test_type_identity<void(int, ...) const volatile noexcept>();
    test_type_identity<void(int, ...) const volatile & noexcept>();
    test_type_identity<void(int, ...) const volatile && noexcept>();

    test_type_identity<int()>();
    test_type_identity<int()&>();
    test_type_identity<int() &&>();
    test_type_identity<int() const>();
    test_type_identity<int() const&>();
    test_type_identity<int() const&&>();
    test_type_identity<int() volatile>();
    test_type_identity<int() volatile&>();
    test_type_identity<int() volatile&&>();
    test_type_identity<int() const volatile>();
    test_type_identity<int() const volatile&>();
    test_type_identity<int() const volatile&&>();
    test_type_identity<int() noexcept>();
    test_type_identity<int() & noexcept>();
    test_type_identity<int() && noexcept>();
    test_type_identity<int() const noexcept>();
    test_type_identity<int() const & noexcept>();
    test_type_identity<int() const && noexcept>();
    test_type_identity<int() volatile noexcept>();
    test_type_identity<int() volatile & noexcept>();
    test_type_identity<int() volatile && noexcept>();
    test_type_identity<int() const volatile noexcept>();
    test_type_identity<int() const volatile & noexcept>();
    test_type_identity<int() const volatile && noexcept>();

    test_type_identity<int(int)>();
    test_type_identity<int(int)&>();
    test_type_identity<int(int) &&>();
    test_type_identity<int(int) const>();
    test_type_identity<int(int) const&>();
    test_type_identity<int(int) const&&>();
    test_type_identity<int(int) volatile>();
    test_type_identity<int(int) volatile&>();
    test_type_identity<int(int) volatile&&>();
    test_type_identity<int(int) const volatile>();
    test_type_identity<int(int) const volatile&>();
    test_type_identity<int(int) const volatile&&>();
    test_type_identity<int(int) noexcept>();
    test_type_identity<int(int) & noexcept>();
    test_type_identity<int(int) && noexcept>();
    test_type_identity<int(int) const noexcept>();
    test_type_identity<int(int) const & noexcept>();
    test_type_identity<int(int) const && noexcept>();
    test_type_identity<int(int) volatile noexcept>();
    test_type_identity<int(int) volatile & noexcept>();
    test_type_identity<int(int) volatile && noexcept>();
    test_type_identity<int(int) const volatile noexcept>();
    test_type_identity<int(int) const volatile & noexcept>();
    test_type_identity<int(int) const volatile && noexcept>();

    test_type_identity<int(...)>();
    test_type_identity<int(...)&>();
    test_type_identity<int(...) &&>();
    test_type_identity<int(...) const>();
    test_type_identity<int(...) const&>();
    test_type_identity<int(...) const&&>();
    test_type_identity<int(...) volatile>();
    test_type_identity<int(...) volatile&>();
    test_type_identity<int(...) volatile&&>();
    test_type_identity<int(...) const volatile>();
    test_type_identity<int(...) const volatile&>();
    test_type_identity<int(...) const volatile&&>();
    test_type_identity<int(...) noexcept>();
    test_type_identity<int(...) & noexcept>();
    test_type_identity<int(...) && noexcept>();
    test_type_identity<int(...) const noexcept>();
    test_type_identity<int(...) const & noexcept>();
    test_type_identity<int(...) const && noexcept>();
    test_type_identity<int(...) volatile noexcept>();
    test_type_identity<int(...) volatile & noexcept>();
    test_type_identity<int(...) volatile && noexcept>();
    test_type_identity<int(...) const volatile noexcept>();
    test_type_identity<int(...) const volatile & noexcept>();
    test_type_identity<int(...) const volatile && noexcept>();

    test_type_identity<int(int, ...)>();
    test_type_identity<int(int, ...)&>();
    test_type_identity<int(int, ...) &&>();
    test_type_identity<int(int, ...) const>();
    test_type_identity<int(int, ...) const&>();
    test_type_identity<int(int, ...) const&&>();
    test_type_identity<int(int, ...) volatile>();
    test_type_identity<int(int, ...) volatile&>();
    test_type_identity<int(int, ...) volatile&&>();
    test_type_identity<int(int, ...) const volatile>();
    test_type_identity<int(int, ...) const volatile&>();
    test_type_identity<int(int, ...) const volatile&&>();
    test_type_identity<int(int, ...) noexcept>();
    test_type_identity<int(int, ...) & noexcept>();
    test_type_identity<int(int, ...) && noexcept>();
    test_type_identity<int(int, ...) const noexcept>();
    test_type_identity<int(int, ...) const & noexcept>();
    test_type_identity<int(int, ...) const && noexcept>();
    test_type_identity<int(int, ...) volatile noexcept>();
    test_type_identity<int(int, ...) volatile & noexcept>();
    test_type_identity<int(int, ...) volatile && noexcept>();
    test_type_identity<int(int, ...) const volatile noexcept>();
    test_type_identity<int(int, ...) const volatile & noexcept>();
    test_type_identity<int(int, ...) const volatile && noexcept>();

    test_type_identity<void (*)()>();
    test_type_identity<void (*)() noexcept>();

    test_type_identity<void (*)(int)>();
    test_type_identity<void (*)(int) noexcept>();

    test_type_identity<void (*)(...)>();
    test_type_identity<void (*)(...) noexcept>();

    test_type_identity<void (*)(int, ...)>();
    test_type_identity<void (*)(int, ...) noexcept>();

    test_type_identity<int (*)()>();
    test_type_identity<int (*)() noexcept>();

    test_type_identity<int (*)(int)>();
    test_type_identity<int (*)(int) noexcept>();

    test_type_identity<int (*)(...)>();
    test_type_identity<int (*)(...) noexcept>();

    test_type_identity<int (*)(int, ...)>();
    test_type_identity<int (*)(int, ...) noexcept>();

    test_type_identity<void (&)()>();
    test_type_identity<void (&)() noexcept>();

    test_type_identity<void (&)(int)>();
    test_type_identity<void (&)(int) noexcept>();

    test_type_identity<void (&)(...)>();
    test_type_identity<void (&)(...) noexcept>();

    test_type_identity<void (&)(int, ...)>();
    test_type_identity<void (&)(int, ...) noexcept>();

    test_type_identity<int (&)()>();
    test_type_identity<int (&)() noexcept>();

    test_type_identity<int (&)(int)>();
    test_type_identity<int (&)(int) noexcept>();

    test_type_identity<int (&)(...)>();
    test_type_identity<int (&)(...) noexcept>();

    test_type_identity<int (&)(int, ...)>();
    test_type_identity<int (&)(int, ...) noexcept>();

    test_type_identity<void (&&)()>();
    test_type_identity<void (&&)() noexcept>();

    test_type_identity<void (&&)(int)>();
    test_type_identity<void (&&)(int) noexcept>();

    test_type_identity<void (&&)(...)>();
    test_type_identity<void (&&)(...) noexcept>();

    test_type_identity<void (&&)(int, ...)>();
    test_type_identity<void (&&)(int, ...) noexcept>();

    test_type_identity<int (&&)()>();
    test_type_identity<int (&&)() noexcept>();

    test_type_identity<int (&&)(int)>();
    test_type_identity<int (&&)(int) noexcept>();

    test_type_identity<int (&&)(...)>();
    test_type_identity<int (&&)(...) noexcept>();

    test_type_identity<int (&&)(int, ...)>();
    test_type_identity<int (&&)(int, ...) noexcept>();

    test_type_identity<void (class_type::*)()>();
    test_type_identity<void (class_type::*)()&>();
    test_type_identity<void (class_type::*)() &&>();
    test_type_identity<void (class_type::*)() const>();
    test_type_identity<void (class_type::*)() const&>();
    test_type_identity<void (class_type::*)() const&&>();
    test_type_identity<void (class_type::*)() noexcept>();
    test_type_identity<void (class_type::*)() & noexcept>();
    test_type_identity<void (class_type::*)() && noexcept>();
    test_type_identity<void (class_type::*)() const noexcept>();
    test_type_identity<void (class_type::*)() const & noexcept>();
    test_type_identity<void (class_type::*)() const && noexcept>();

    test_type_identity<void (class_type::*)(int)>();
    test_type_identity<void (class_type::*)(int)&>();
    test_type_identity<void (class_type::*)(int) &&>();
    test_type_identity<void (class_type::*)(int) const>();
    test_type_identity<void (class_type::*)(int) const&>();
    test_type_identity<void (class_type::*)(int) const&&>();
    test_type_identity<void (class_type::*)(int) noexcept>();
    test_type_identity<void (class_type::*)(int) & noexcept>();
    test_type_identity<void (class_type::*)(int) && noexcept>();
    test_type_identity<void (class_type::*)(int) const noexcept>();
    test_type_identity<void (class_type::*)(int) const & noexcept>();
    test_type_identity<void (class_type::*)(int) const && noexcept>();

    test_type_identity<void (class_type::*)(...)>();
    test_type_identity<void (class_type::*)(...)&>();
    test_type_identity<void (class_type::*)(...) &&>();
    test_type_identity<void (class_type::*)(...) const>();
    test_type_identity<void (class_type::*)(...) const&>();
    test_type_identity<void (class_type::*)(...) const&&>();
    test_type_identity<void (class_type::*)(...) noexcept>();
    test_type_identity<void (class_type::*)(...) & noexcept>();
    test_type_identity<void (class_type::*)(...) && noexcept>();
    test_type_identity<void (class_type::*)(...) const noexcept>();
    test_type_identity<void (class_type::*)(...) const & noexcept>();
    test_type_identity<void (class_type::*)(...) const && noexcept>();

    test_type_identity<void (class_type::*)(int, ...)>();
    test_type_identity<void (class_type::*)(int, ...)&>();
    test_type_identity<void (class_type::*)(int, ...) &&>();
    test_type_identity<void (class_type::*)(int, ...) const>();
    test_type_identity<void (class_type::*)(int, ...) const&>();
    test_type_identity<void (class_type::*)(int, ...) const&&>();
    test_type_identity<void (class_type::*)(int, ...) noexcept>();
    test_type_identity<void (class_type::*)(int, ...) & noexcept>();
    test_type_identity<void (class_type::*)(int, ...) && noexcept>();
    test_type_identity<void (class_type::*)(int, ...) const noexcept>();
    test_type_identity<void (class_type::*)(int, ...) const & noexcept>();
    test_type_identity<void (class_type::*)(int, ...) const && noexcept>();

    test_type_identity<int (class_type::*)()>();
    test_type_identity<int (class_type::*)()&>();
    test_type_identity<int (class_type::*)() &&>();
    test_type_identity<int (class_type::*)() const>();
    test_type_identity<int (class_type::*)() const&>();
    test_type_identity<int (class_type::*)() const&&>();
    test_type_identity<int (class_type::*)() noexcept>();
    test_type_identity<int (class_type::*)() & noexcept>();
    test_type_identity<int (class_type::*)() && noexcept>();
    test_type_identity<int (class_type::*)() const noexcept>();
    test_type_identity<int (class_type::*)() const & noexcept>();
    test_type_identity<int (class_type::*)() const && noexcept>();

    test_type_identity<int (class_type::*)(int)>();
    test_type_identity<int (class_type::*)(int)&>();
    test_type_identity<int (class_type::*)(int) &&>();
    test_type_identity<int (class_type::*)(int) const>();
    test_type_identity<int (class_type::*)(int) const&>();
    test_type_identity<int (class_type::*)(int) const&&>();
    test_type_identity<int (class_type::*)(int) noexcept>();
    test_type_identity<int (class_type::*)(int) & noexcept>();
    test_type_identity<int (class_type::*)(int) && noexcept>();
    test_type_identity<int (class_type::*)(int) const noexcept>();
    test_type_identity<int (class_type::*)(int) const & noexcept>();
    test_type_identity<int (class_type::*)(int) const && noexcept>();

    test_type_identity<int (class_type::*)(...)>();
    test_type_identity<int (class_type::*)(...)&>();
    test_type_identity<int (class_type::*)(...) &&>();
    test_type_identity<int (class_type::*)(...) const>();
    test_type_identity<int (class_type::*)(...) const&>();
    test_type_identity<int (class_type::*)(...) const&&>();
    test_type_identity<int (class_type::*)(...) noexcept>();
    test_type_identity<int (class_type::*)(...) & noexcept>();
    test_type_identity<int (class_type::*)(...) && noexcept>();
    test_type_identity<int (class_type::*)(...) const noexcept>();
    test_type_identity<int (class_type::*)(...) const & noexcept>();
    test_type_identity<int (class_type::*)(...) const && noexcept>();

    test_type_identity<int (class_type::*)(int, ...)>();
    test_type_identity<int (class_type::*)(int, ...)&>();
    test_type_identity<int (class_type::*)(int, ...) &&>();
    test_type_identity<int (class_type::*)(int, ...) const>();
    test_type_identity<int (class_type::*)(int, ...) const&>();
    test_type_identity<int (class_type::*)(int, ...) const&&>();
    test_type_identity<int (class_type::*)(int, ...) noexcept>();
    test_type_identity<int (class_type::*)(int, ...) & noexcept>();
    test_type_identity<int (class_type::*)(int, ...) && noexcept>();
    test_type_identity<int (class_type::*)(int, ...) const noexcept>();
    test_type_identity<int (class_type::*)(int, ...) const & noexcept>();
    test_type_identity<int (class_type::*)(int, ...) const && noexcept>();
}
