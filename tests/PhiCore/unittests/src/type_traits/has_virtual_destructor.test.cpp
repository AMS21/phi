#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/has_virtual_destructor.hpp>
#include <type_traits>
#include <vector>

template <typename TypeT>
void test_has_virtual_destructor_impl()
{
#if PHI_HAS_WORKING_HAS_VIRTUAL_DESTRUCTOR()
    STATIC_REQUIRE(phi::has_virtual_destructor<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::has_no_virtual_destructor<TypeT>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::has_virtual_destructor_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::has_no_virtual_destructor_v<TypeT>);
#    endif

    // Standard compatibility
    STATIC_REQUIRE(std::has_virtual_destructor<TypeT>::value);
#endif
}

template <typename TypeT>
void test_has_virtual_destructor()
{
    test_has_virtual_destructor_impl<TypeT>();
    test_has_virtual_destructor_impl<const TypeT>();
    test_has_virtual_destructor_impl<volatile TypeT>();
    test_has_virtual_destructor_impl<const volatile TypeT>();
}

template <typename TypeT>
void test_has_no_virtual_destructor_impl()
{
#if PHI_HAS_WORKING_HAS_VIRTUAL_DESTRUCTOR()
    STATIC_REQUIRE_FALSE(phi::has_virtual_destructor<TypeT>::value);
    STATIC_REQUIRE(phi::has_no_virtual_destructor<TypeT>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::has_virtual_destructor_v<TypeT>);
    STATIC_REQUIRE(phi::has_no_virtual_destructor_v<TypeT>);
#    endif

    // Standard compatibility
    STATIC_REQUIRE_FALSE(std::has_virtual_destructor<TypeT>::value);
#endif
}

template <typename TypeT>
void test_has_no_virtual_destructor()
{
    test_has_no_virtual_destructor_impl<TypeT>();
    test_has_no_virtual_destructor_impl<const TypeT>();
    test_has_no_virtual_destructor_impl<volatile TypeT>();
    test_has_no_virtual_destructor_impl<const volatile TypeT>();
}

struct A
{
    ~A();
};

TEST_CASE("has_virtual_destructor")
{
    test_has_no_virtual_destructor<void>();
    test_has_no_virtual_destructor<phi::nullptr_t>();
    test_has_no_virtual_destructor<bool>();
    test_has_no_virtual_destructor<char>();
    test_has_no_virtual_destructor<signed char>();
    test_has_no_virtual_destructor<unsigned char>();
    test_has_no_virtual_destructor<short>();
    test_has_no_virtual_destructor<unsigned short>();
    test_has_no_virtual_destructor<int>();
    test_has_no_virtual_destructor<unsigned int>();
    test_has_no_virtual_destructor<long>();
    test_has_no_virtual_destructor<unsigned long>();
    test_has_no_virtual_destructor<long long>();
    test_has_no_virtual_destructor<unsigned long long>();
    test_has_no_virtual_destructor<float>();
    test_has_no_virtual_destructor<double>();
    test_has_no_virtual_destructor<long double>();
    test_has_no_virtual_destructor<char8_t>();
    test_has_no_virtual_destructor<char16_t>();
    test_has_no_virtual_destructor<char32_t>();
    test_has_no_virtual_destructor<wchar_t>();

    test_has_no_virtual_destructor<phi::boolean>();
    test_has_no_virtual_destructor<phi::integer<signed char>>();
    test_has_no_virtual_destructor<phi::integer<unsigned char>>();
    test_has_no_virtual_destructor<phi::integer<short>>();
    test_has_no_virtual_destructor<phi::integer<unsigned short>>();
    test_has_no_virtual_destructor<phi::integer<int>>();
    test_has_no_virtual_destructor<phi::integer<unsigned int>>();
    test_has_no_virtual_destructor<phi::integer<long>>();
    test_has_no_virtual_destructor<phi::integer<unsigned long>>();
    test_has_no_virtual_destructor<phi::integer<long long>>();
    test_has_no_virtual_destructor<phi::integer<unsigned long long>>();
    test_has_no_virtual_destructor<phi::floating_point<float>>();
    test_has_no_virtual_destructor<phi::floating_point<double>>();
    test_has_no_virtual_destructor<phi::floating_point<long double>>();

    test_has_no_virtual_destructor<std::vector<int>>();
    test_has_no_virtual_destructor<phi::scope_ptr<int>>();

    test_has_no_virtual_destructor<int&>();
    test_has_no_virtual_destructor<const int&>();
    test_has_no_virtual_destructor<volatile int&>();
    test_has_no_virtual_destructor<const volatile int&>();
    test_has_no_virtual_destructor<int&&>();
    test_has_no_virtual_destructor<const int&&>();
    test_has_no_virtual_destructor<volatile int&&>();
    test_has_no_virtual_destructor<const volatile int&&>();
    test_has_no_virtual_destructor<int*>();
    test_has_no_virtual_destructor<const int*>();
    test_has_no_virtual_destructor<volatile int*>();
    test_has_no_virtual_destructor<const volatile int*>();
    test_has_no_virtual_destructor<int**>();
    test_has_no_virtual_destructor<const int**>();
    test_has_no_virtual_destructor<volatile int**>();
    test_has_no_virtual_destructor<const volatile int**>();
    test_has_no_virtual_destructor<int*&>();
    test_has_no_virtual_destructor<const int*&>();
    test_has_no_virtual_destructor<volatile int*&>();
    test_has_no_virtual_destructor<const volatile int*&>();
    test_has_no_virtual_destructor<int*&&>();
    test_has_no_virtual_destructor<const int*&&>();
    test_has_no_virtual_destructor<volatile int*&&>();
    test_has_no_virtual_destructor<const volatile int*&&>();
    test_has_no_virtual_destructor<void*>();
    test_has_no_virtual_destructor<char[3]>();
    test_has_no_virtual_destructor<char[]>();
    test_has_no_virtual_destructor<char[3]>();
    test_has_no_virtual_destructor<char[]>();
    test_has_no_virtual_destructor<char* [3]>();
    test_has_no_virtual_destructor<char*[]>();
    test_has_no_virtual_destructor<int(*)[3]>();
    test_has_no_virtual_destructor<int(*)[]>();
    test_has_no_virtual_destructor<int(&)[3]>();
    test_has_no_virtual_destructor<int(&)[]>();
    test_has_no_virtual_destructor<int(&&)[3]>();
    test_has_no_virtual_destructor<int(&&)[]>();
    test_has_no_virtual_destructor<char[3][2]>();
    test_has_no_virtual_destructor<char[][2]>();
    test_has_no_virtual_destructor<char* [3][2]>();
    test_has_no_virtual_destructor<char*[][2]>();
    test_has_no_virtual_destructor<int(*)[3][2]>();
    test_has_no_virtual_destructor<int(*)[][2]>();
    test_has_no_virtual_destructor<int(&)[3][2]>();
    test_has_no_virtual_destructor<int(&)[][2]>();
    test_has_no_virtual_destructor<int(&&)[3][2]>();
    test_has_no_virtual_destructor<int(&&)[][2]>();
    test_has_no_virtual_destructor<class_type>();
    test_has_no_virtual_destructor<class_type[]>();
    test_has_no_virtual_destructor<class_type[2]>();
    test_has_no_virtual_destructor<template_type<void>>();
    test_has_no_virtual_destructor<template_type<int>>();
    test_has_no_virtual_destructor<template_type<class_type>>();
    test_has_no_virtual_destructor<template_type<incomplete_type>>();
    test_has_no_virtual_destructor<variadic_template<>>();
    test_has_no_virtual_destructor<variadic_template<void>>();
    test_has_no_virtual_destructor<variadic_template<int>>();
    test_has_no_virtual_destructor<variadic_template<class_type>>();
    test_has_no_virtual_destructor<variadic_template<incomplete_type>>();
    test_has_no_virtual_destructor<variadic_template<int, void, class_type, volatile char[]>>();
    test_has_no_virtual_destructor<public_derived_from<base>>();
    test_has_no_virtual_destructor<public_derived_from<derived>>();
    test_has_no_virtual_destructor<public_derived_from<class_type>>();
    test_has_no_virtual_destructor<private_derived_from<base>>();
    test_has_no_virtual_destructor<private_derived_from<derived>>();
    test_has_no_virtual_destructor<private_derived_from<class_type>>();
    test_has_no_virtual_destructor<protected_derived_from<base>>();
    test_has_no_virtual_destructor<protected_derived_from<derived>>();
    test_has_no_virtual_destructor<protected_derived_from<class_type>>();
    test_has_no_virtual_destructor<union_type>();
    test_has_no_virtual_destructor<non_empty_union>();
    test_has_no_virtual_destructor<empty>();
    test_has_virtual_destructor<not_empty>();
    test_has_no_virtual_destructor<bit_zero>();
    test_has_no_virtual_destructor<bit_one>();
    test_has_no_virtual_destructor<base>();
    test_has_no_virtual_destructor<derived>();
    test_has_virtual_destructor<abstract>();
    test_has_virtual_destructor<public_abstract>();
    test_has_virtual_destructor<private_abstract>();
    test_has_virtual_destructor<protected_abstract>();
    test_has_virtual_destructor<abstract_template<int>>();
    test_has_no_virtual_destructor<abstract_template<double>>();
    test_has_virtual_destructor<abstract_template<class_type>>();
    test_has_virtual_destructor<abstract_template<incomplete_type>>();
    test_has_no_virtual_destructor<final_type>();
    test_has_no_virtual_destructor<public_destructor>();
    test_has_no_virtual_destructor<protected_destructor>();
    test_has_no_virtual_destructor<private_destructor>();
    test_has_virtual_destructor<virtual_public_destructor>();
    test_has_virtual_destructor<virtual_protected_destructor>();
    test_has_virtual_destructor<virtual_private_destructor>();
    test_has_virtual_destructor<pure_public_destructor>();
    test_has_virtual_destructor<pure_protected_destructor>();
    test_has_virtual_destructor<pure_private_destructor>();
    test_has_no_virtual_destructor<deleted_public_destructor>();
    test_has_no_virtual_destructor<deleted_protected_destructor>();
    test_has_no_virtual_destructor<deleted_private_destructor>();
    test_has_virtual_destructor<deleted_virtual_public_destructor>();
    test_has_virtual_destructor<deleted_virtual_protected_destructor>();
    test_has_virtual_destructor<deleted_virtual_private_destructor>();
    test_has_no_virtual_destructor<Enum>();
    test_has_no_virtual_destructor<EnumSigned>();
    test_has_no_virtual_destructor<EnumUnsigned>();
    test_has_no_virtual_destructor<EnumClass>();
    test_has_no_virtual_destructor<EnumStruct>();
    test_has_no_virtual_destructor<function_type>();
    test_has_no_virtual_destructor<function_ptr>();
    test_has_no_virtual_destructor<member_object_ptr>();
    test_has_no_virtual_destructor<member_function_ptr>();
    test_has_no_virtual_destructor<int class_type::*>();
    test_has_no_virtual_destructor<float class_type::*>();
    test_has_no_virtual_destructor<void * class_type::*>();
    test_has_no_virtual_destructor<int * class_type::*>();
    test_has_no_virtual_destructor<int class_type::*&>();
    test_has_no_virtual_destructor<float class_type::*&>();
    test_has_no_virtual_destructor<void * class_type::*&>();
    test_has_no_virtual_destructor<int * class_type::*&>();
    test_has_no_virtual_destructor<int class_type::*&&>();
    test_has_no_virtual_destructor<float class_type::*&&>();
    test_has_no_virtual_destructor<void * class_type::*&&>();
    test_has_no_virtual_destructor<int * class_type::*&&>();
    test_has_no_virtual_destructor<int class_type::* const>();
    test_has_no_virtual_destructor<float class_type::* const>();
    test_has_no_virtual_destructor<void * class_type::* const>();
    test_has_no_virtual_destructor<int class_type::* const&>();
    test_has_no_virtual_destructor<float class_type::* const&>();
    test_has_no_virtual_destructor<void * class_type::* const&>();
    test_has_no_virtual_destructor<int class_type::* const&&>();
    test_has_no_virtual_destructor<float class_type::* const&&>();
    test_has_no_virtual_destructor<void * class_type::* const&&>();
    test_has_no_virtual_destructor<int class_type::* volatile>();
    test_has_no_virtual_destructor<float class_type::* volatile>();
    test_has_no_virtual_destructor<void * class_type::* volatile>();
    test_has_no_virtual_destructor<int class_type::* volatile&>();
    test_has_no_virtual_destructor<float class_type::* volatile&>();
    test_has_no_virtual_destructor<void * class_type::* volatile&>();
    test_has_no_virtual_destructor<int class_type::* volatile&&>();
    test_has_no_virtual_destructor<float class_type::* volatile&&>();
    test_has_no_virtual_destructor<void * class_type::* volatile&&>();
    test_has_no_virtual_destructor<int class_type::* const volatile>();
    test_has_no_virtual_destructor<float class_type::* const volatile>();
    test_has_no_virtual_destructor<void * class_type::* const volatile>();
    test_has_no_virtual_destructor<int class_type::* const volatile&>();
    test_has_no_virtual_destructor<float class_type::* const volatile&>();
    test_has_no_virtual_destructor<void * class_type::* const volatile&>();
    test_has_no_virtual_destructor<int class_type::* const volatile&&>();
    test_has_no_virtual_destructor<float class_type::* const volatile&&>();
    test_has_no_virtual_destructor<void * class_type::* const volatile&&>();
    test_has_no_virtual_destructor<non_copyable>();
    test_has_no_virtual_destructor<non_moveable>();
    test_has_no_virtual_destructor<non_constructible>();
    test_has_no_virtual_destructor<tracked>();
    test_has_no_virtual_destructor<trap_constructible>();
    test_has_no_virtual_destructor<trap_implicit_conversion>();
    test_has_no_virtual_destructor<trap_comma>();
    test_has_no_virtual_destructor<trap_call>();
    test_has_no_virtual_destructor<trap_self_assign>();
    test_has_no_virtual_destructor<trap_deref>();
    test_has_no_virtual_destructor<trap_array_subscript>();

    test_has_no_virtual_destructor<void()>();
    test_has_no_virtual_destructor<void()&>();
    test_has_no_virtual_destructor<void() &&>();
    test_has_no_virtual_destructor<void() const>();
    test_has_no_virtual_destructor<void() const&>();
    test_has_no_virtual_destructor<void() const&&>();
    test_has_no_virtual_destructor<void() volatile>();
    test_has_no_virtual_destructor<void() volatile&>();
    test_has_no_virtual_destructor<void() volatile&&>();
    test_has_no_virtual_destructor<void() const volatile>();
    test_has_no_virtual_destructor<void() const volatile&>();
    test_has_no_virtual_destructor<void() const volatile&&>();
    test_has_no_virtual_destructor<void() noexcept>();
    test_has_no_virtual_destructor<void() & noexcept>();
    test_has_no_virtual_destructor<void() && noexcept>();
    test_has_no_virtual_destructor<void() const noexcept>();
    test_has_no_virtual_destructor<void() const & noexcept>();
    test_has_no_virtual_destructor<void() const && noexcept>();
    test_has_no_virtual_destructor<void() volatile noexcept>();
    test_has_no_virtual_destructor<void() volatile & noexcept>();
    test_has_no_virtual_destructor<void() volatile && noexcept>();
    test_has_no_virtual_destructor<void() const volatile noexcept>();
    test_has_no_virtual_destructor<void() const volatile & noexcept>();
    test_has_no_virtual_destructor<void() const volatile && noexcept>();

    test_has_no_virtual_destructor<void(int)>();
    test_has_no_virtual_destructor<void(int)&>();
    test_has_no_virtual_destructor<void(int) &&>();
    test_has_no_virtual_destructor<void(int) const>();
    test_has_no_virtual_destructor<void(int) const&>();
    test_has_no_virtual_destructor<void(int) const&&>();
    test_has_no_virtual_destructor<void(int) volatile>();
    test_has_no_virtual_destructor<void(int) volatile&>();
    test_has_no_virtual_destructor<void(int) volatile&&>();
    test_has_no_virtual_destructor<void(int) const volatile>();
    test_has_no_virtual_destructor<void(int) const volatile&>();
    test_has_no_virtual_destructor<void(int) const volatile&&>();
    test_has_no_virtual_destructor<void(int) noexcept>();
    test_has_no_virtual_destructor<void(int) & noexcept>();
    test_has_no_virtual_destructor<void(int) && noexcept>();
    test_has_no_virtual_destructor<void(int) const noexcept>();
    test_has_no_virtual_destructor<void(int) const & noexcept>();
    test_has_no_virtual_destructor<void(int) const && noexcept>();
    test_has_no_virtual_destructor<void(int) volatile noexcept>();
    test_has_no_virtual_destructor<void(int) volatile & noexcept>();
    test_has_no_virtual_destructor<void(int) volatile && noexcept>();
    test_has_no_virtual_destructor<void(int) const volatile noexcept>();
    test_has_no_virtual_destructor<void(int) const volatile & noexcept>();
    test_has_no_virtual_destructor<void(int) const volatile && noexcept>();

    test_has_no_virtual_destructor<void(...)>();
    test_has_no_virtual_destructor<void(...)&>();
    test_has_no_virtual_destructor<void(...) &&>();
    test_has_no_virtual_destructor<void(...) const>();
    test_has_no_virtual_destructor<void(...) const&>();
    test_has_no_virtual_destructor<void(...) const&&>();
    test_has_no_virtual_destructor<void(...) volatile>();
    test_has_no_virtual_destructor<void(...) volatile&>();
    test_has_no_virtual_destructor<void(...) volatile&&>();
    test_has_no_virtual_destructor<void(...) const volatile>();
    test_has_no_virtual_destructor<void(...) const volatile&>();
    test_has_no_virtual_destructor<void(...) const volatile&&>();
    test_has_no_virtual_destructor<void(...) noexcept>();
    test_has_no_virtual_destructor<void(...) & noexcept>();
    test_has_no_virtual_destructor<void(...) && noexcept>();
    test_has_no_virtual_destructor<void(...) const noexcept>();
    test_has_no_virtual_destructor<void(...) const & noexcept>();
    test_has_no_virtual_destructor<void(...) const && noexcept>();
    test_has_no_virtual_destructor<void(...) volatile noexcept>();
    test_has_no_virtual_destructor<void(...) volatile & noexcept>();
    test_has_no_virtual_destructor<void(...) volatile && noexcept>();
    test_has_no_virtual_destructor<void(...) const volatile noexcept>();
    test_has_no_virtual_destructor<void(...) const volatile & noexcept>();
    test_has_no_virtual_destructor<void(...) const volatile && noexcept>();

    test_has_no_virtual_destructor<void(int, ...)>();
    test_has_no_virtual_destructor<void(int, ...)&>();
    test_has_no_virtual_destructor<void(int, ...) &&>();
    test_has_no_virtual_destructor<void(int, ...) const>();
    test_has_no_virtual_destructor<void(int, ...) const&>();
    test_has_no_virtual_destructor<void(int, ...) const&&>();
    test_has_no_virtual_destructor<void(int, ...) volatile>();
    test_has_no_virtual_destructor<void(int, ...) volatile&>();
    test_has_no_virtual_destructor<void(int, ...) volatile&&>();
    test_has_no_virtual_destructor<void(int, ...) const volatile>();
    test_has_no_virtual_destructor<void(int, ...) const volatile&>();
    test_has_no_virtual_destructor<void(int, ...) const volatile&&>();
    test_has_no_virtual_destructor<void(int, ...) noexcept>();
    test_has_no_virtual_destructor<void(int, ...) & noexcept>();
    test_has_no_virtual_destructor<void(int, ...) && noexcept>();
    test_has_no_virtual_destructor<void(int, ...) const noexcept>();
    test_has_no_virtual_destructor<void(int, ...) const & noexcept>();
    test_has_no_virtual_destructor<void(int, ...) const && noexcept>();
    test_has_no_virtual_destructor<void(int, ...) volatile noexcept>();
    test_has_no_virtual_destructor<void(int, ...) volatile & noexcept>();
    test_has_no_virtual_destructor<void(int, ...) volatile && noexcept>();
    test_has_no_virtual_destructor<void(int, ...) const volatile noexcept>();
    test_has_no_virtual_destructor<void(int, ...) const volatile & noexcept>();
    test_has_no_virtual_destructor<void(int, ...) const volatile && noexcept>();

    test_has_no_virtual_destructor<int()>();
    test_has_no_virtual_destructor<int()&>();
    test_has_no_virtual_destructor<int() &&>();
    test_has_no_virtual_destructor<int() const>();
    test_has_no_virtual_destructor<int() const&>();
    test_has_no_virtual_destructor<int() const&&>();
    test_has_no_virtual_destructor<int() volatile>();
    test_has_no_virtual_destructor<int() volatile&>();
    test_has_no_virtual_destructor<int() volatile&&>();
    test_has_no_virtual_destructor<int() const volatile>();
    test_has_no_virtual_destructor<int() const volatile&>();
    test_has_no_virtual_destructor<int() const volatile&&>();
    test_has_no_virtual_destructor<int() noexcept>();
    test_has_no_virtual_destructor<int() & noexcept>();
    test_has_no_virtual_destructor<int() && noexcept>();
    test_has_no_virtual_destructor<int() const noexcept>();
    test_has_no_virtual_destructor<int() const & noexcept>();
    test_has_no_virtual_destructor<int() const && noexcept>();
    test_has_no_virtual_destructor<int() volatile noexcept>();
    test_has_no_virtual_destructor<int() volatile & noexcept>();
    test_has_no_virtual_destructor<int() volatile && noexcept>();
    test_has_no_virtual_destructor<int() const volatile noexcept>();
    test_has_no_virtual_destructor<int() const volatile & noexcept>();
    test_has_no_virtual_destructor<int() const volatile && noexcept>();

    test_has_no_virtual_destructor<int(int)>();
    test_has_no_virtual_destructor<int(int)&>();
    test_has_no_virtual_destructor<int(int) &&>();
    test_has_no_virtual_destructor<int(int) const>();
    test_has_no_virtual_destructor<int(int) const&>();
    test_has_no_virtual_destructor<int(int) const&&>();
    test_has_no_virtual_destructor<int(int) volatile>();
    test_has_no_virtual_destructor<int(int) volatile&>();
    test_has_no_virtual_destructor<int(int) volatile&&>();
    test_has_no_virtual_destructor<int(int) const volatile>();
    test_has_no_virtual_destructor<int(int) const volatile&>();
    test_has_no_virtual_destructor<int(int) const volatile&&>();
    test_has_no_virtual_destructor<int(int) noexcept>();
    test_has_no_virtual_destructor<int(int) & noexcept>();
    test_has_no_virtual_destructor<int(int) && noexcept>();
    test_has_no_virtual_destructor<int(int) const noexcept>();
    test_has_no_virtual_destructor<int(int) const & noexcept>();
    test_has_no_virtual_destructor<int(int) const && noexcept>();
    test_has_no_virtual_destructor<int(int) volatile noexcept>();
    test_has_no_virtual_destructor<int(int) volatile & noexcept>();
    test_has_no_virtual_destructor<int(int) volatile && noexcept>();
    test_has_no_virtual_destructor<int(int) const volatile noexcept>();
    test_has_no_virtual_destructor<int(int) const volatile & noexcept>();
    test_has_no_virtual_destructor<int(int) const volatile && noexcept>();

    test_has_no_virtual_destructor<int(...)>();
    test_has_no_virtual_destructor<int(...)&>();
    test_has_no_virtual_destructor<int(...) &&>();
    test_has_no_virtual_destructor<int(...) const>();
    test_has_no_virtual_destructor<int(...) const&>();
    test_has_no_virtual_destructor<int(...) const&&>();
    test_has_no_virtual_destructor<int(...) volatile>();
    test_has_no_virtual_destructor<int(...) volatile&>();
    test_has_no_virtual_destructor<int(...) volatile&&>();
    test_has_no_virtual_destructor<int(...) const volatile>();
    test_has_no_virtual_destructor<int(...) const volatile&>();
    test_has_no_virtual_destructor<int(...) const volatile&&>();
    test_has_no_virtual_destructor<int(...) noexcept>();
    test_has_no_virtual_destructor<int(...) & noexcept>();
    test_has_no_virtual_destructor<int(...) && noexcept>();
    test_has_no_virtual_destructor<int(...) const noexcept>();
    test_has_no_virtual_destructor<int(...) const & noexcept>();
    test_has_no_virtual_destructor<int(...) const && noexcept>();
    test_has_no_virtual_destructor<int(...) volatile noexcept>();
    test_has_no_virtual_destructor<int(...) volatile & noexcept>();
    test_has_no_virtual_destructor<int(...) volatile && noexcept>();
    test_has_no_virtual_destructor<int(...) const volatile noexcept>();
    test_has_no_virtual_destructor<int(...) const volatile & noexcept>();
    test_has_no_virtual_destructor<int(...) const volatile && noexcept>();

    test_has_no_virtual_destructor<int(int, ...)>();
    test_has_no_virtual_destructor<int(int, ...)&>();
    test_has_no_virtual_destructor<int(int, ...) &&>();
    test_has_no_virtual_destructor<int(int, ...) const>();
    test_has_no_virtual_destructor<int(int, ...) const&>();
    test_has_no_virtual_destructor<int(int, ...) const&&>();
    test_has_no_virtual_destructor<int(int, ...) volatile>();
    test_has_no_virtual_destructor<int(int, ...) volatile&>();
    test_has_no_virtual_destructor<int(int, ...) volatile&&>();
    test_has_no_virtual_destructor<int(int, ...) const volatile>();
    test_has_no_virtual_destructor<int(int, ...) const volatile&>();
    test_has_no_virtual_destructor<int(int, ...) const volatile&&>();
    test_has_no_virtual_destructor<int(int, ...) noexcept>();
    test_has_no_virtual_destructor<int(int, ...) & noexcept>();
    test_has_no_virtual_destructor<int(int, ...) && noexcept>();
    test_has_no_virtual_destructor<int(int, ...) const noexcept>();
    test_has_no_virtual_destructor<int(int, ...) const & noexcept>();
    test_has_no_virtual_destructor<int(int, ...) const && noexcept>();
    test_has_no_virtual_destructor<int(int, ...) volatile noexcept>();
    test_has_no_virtual_destructor<int(int, ...) volatile & noexcept>();
    test_has_no_virtual_destructor<int(int, ...) volatile && noexcept>();
    test_has_no_virtual_destructor<int(int, ...) const volatile noexcept>();
    test_has_no_virtual_destructor<int(int, ...) const volatile & noexcept>();
    test_has_no_virtual_destructor<int(int, ...) const volatile && noexcept>();

    test_has_no_virtual_destructor<void (*)()>();
    test_has_no_virtual_destructor<void (*)() noexcept>();

    test_has_no_virtual_destructor<void (*)(int)>();
    test_has_no_virtual_destructor<void (*)(int) noexcept>();

    test_has_no_virtual_destructor<void (*)(...)>();
    test_has_no_virtual_destructor<void (*)(...) noexcept>();

    test_has_no_virtual_destructor<void (*)(int, ...)>();
    test_has_no_virtual_destructor<void (*)(int, ...) noexcept>();

    test_has_no_virtual_destructor<int (*)()>();
    test_has_no_virtual_destructor<int (*)() noexcept>();

    test_has_no_virtual_destructor<int (*)(int)>();
    test_has_no_virtual_destructor<int (*)(int) noexcept>();

    test_has_no_virtual_destructor<int (*)(...)>();
    test_has_no_virtual_destructor<int (*)(...) noexcept>();

    test_has_no_virtual_destructor<int (*)(int, ...)>();
    test_has_no_virtual_destructor<int (*)(int, ...) noexcept>();

    test_has_no_virtual_destructor<void (&)()>();
    test_has_no_virtual_destructor<void (&)() noexcept>();

    test_has_no_virtual_destructor<void (&)(int)>();
    test_has_no_virtual_destructor<void (&)(int) noexcept>();

    test_has_no_virtual_destructor<void (&)(...)>();
    test_has_no_virtual_destructor<void (&)(...) noexcept>();

    test_has_no_virtual_destructor<void (&)(int, ...)>();
    test_has_no_virtual_destructor<void (&)(int, ...) noexcept>();

    test_has_no_virtual_destructor<int (&)()>();
    test_has_no_virtual_destructor<int (&)() noexcept>();

    test_has_no_virtual_destructor<int (&)(int)>();
    test_has_no_virtual_destructor<int (&)(int) noexcept>();

    test_has_no_virtual_destructor<int (&)(...)>();
    test_has_no_virtual_destructor<int (&)(...) noexcept>();

    test_has_no_virtual_destructor<int (&)(int, ...)>();
    test_has_no_virtual_destructor<int (&)(int, ...) noexcept>();

    test_has_no_virtual_destructor<void (&&)()>();
    test_has_no_virtual_destructor<void (&&)() noexcept>();

    test_has_no_virtual_destructor<void (&&)(int)>();
    test_has_no_virtual_destructor<void (&&)(int) noexcept>();

    test_has_no_virtual_destructor<void (&&)(...)>();
    test_has_no_virtual_destructor<void (&&)(...) noexcept>();

    test_has_no_virtual_destructor<void (&&)(int, ...)>();
    test_has_no_virtual_destructor<void (&&)(int, ...) noexcept>();

    test_has_no_virtual_destructor<int (&&)()>();
    test_has_no_virtual_destructor<int (&&)() noexcept>();

    test_has_no_virtual_destructor<int (&&)(int)>();
    test_has_no_virtual_destructor<int (&&)(int) noexcept>();

    test_has_no_virtual_destructor<int (&&)(...)>();
    test_has_no_virtual_destructor<int (&&)(...) noexcept>();

    test_has_no_virtual_destructor<int (&&)(int, ...)>();
    test_has_no_virtual_destructor<int (&&)(int, ...) noexcept>();

    test_has_no_virtual_destructor<void (class_type::*)()>();
    test_has_no_virtual_destructor<void (class_type::*)()&>();
    test_has_no_virtual_destructor<void (class_type::*)() &&>();
    test_has_no_virtual_destructor<void (class_type::*)() const>();
    test_has_no_virtual_destructor<void (class_type::*)() const&>();
    test_has_no_virtual_destructor<void (class_type::*)() const&&>();
    test_has_no_virtual_destructor<void (class_type::*)() noexcept>();
    test_has_no_virtual_destructor<void (class_type::*)() & noexcept>();
    test_has_no_virtual_destructor<void (class_type::*)() && noexcept>();
    test_has_no_virtual_destructor<void (class_type::*)() const noexcept>();
    test_has_no_virtual_destructor<void (class_type::*)() const & noexcept>();
    test_has_no_virtual_destructor<void (class_type::*)() const && noexcept>();

    test_has_no_virtual_destructor<void (class_type::*)(int)>();
    test_has_no_virtual_destructor<void (class_type::*)(int)&>();
    test_has_no_virtual_destructor<void (class_type::*)(int) &&>();
    test_has_no_virtual_destructor<void (class_type::*)(int) const>();
    test_has_no_virtual_destructor<void (class_type::*)(int) const&>();
    test_has_no_virtual_destructor<void (class_type::*)(int) const&&>();
    test_has_no_virtual_destructor<void (class_type::*)(int) noexcept>();
    test_has_no_virtual_destructor<void (class_type::*)(int) & noexcept>();
    test_has_no_virtual_destructor<void (class_type::*)(int) && noexcept>();
    test_has_no_virtual_destructor<void (class_type::*)(int) const noexcept>();
    test_has_no_virtual_destructor<void (class_type::*)(int) const & noexcept>();
    test_has_no_virtual_destructor<void (class_type::*)(int) const && noexcept>();

    test_has_no_virtual_destructor<void (class_type::*)(...)>();
    test_has_no_virtual_destructor<void (class_type::*)(...)&>();
    test_has_no_virtual_destructor<void (class_type::*)(...) &&>();
    test_has_no_virtual_destructor<void (class_type::*)(...) const>();
    test_has_no_virtual_destructor<void (class_type::*)(...) const&>();
    test_has_no_virtual_destructor<void (class_type::*)(...) const&&>();
    test_has_no_virtual_destructor<void (class_type::*)(...) noexcept>();
    test_has_no_virtual_destructor<void (class_type::*)(...) & noexcept>();
    test_has_no_virtual_destructor<void (class_type::*)(...) && noexcept>();
    test_has_no_virtual_destructor<void (class_type::*)(...) const noexcept>();
    test_has_no_virtual_destructor<void (class_type::*)(...) const & noexcept>();
    test_has_no_virtual_destructor<void (class_type::*)(...) const && noexcept>();

    test_has_no_virtual_destructor<void (class_type::*)(int, ...)>();
    test_has_no_virtual_destructor<void (class_type::*)(int, ...)&>();
    test_has_no_virtual_destructor<void (class_type::*)(int, ...) &&>();
    test_has_no_virtual_destructor<void (class_type::*)(int, ...) const>();
    test_has_no_virtual_destructor<void (class_type::*)(int, ...) const&>();
    test_has_no_virtual_destructor<void (class_type::*)(int, ...) const&&>();
    test_has_no_virtual_destructor<void (class_type::*)(int, ...) noexcept>();
    test_has_no_virtual_destructor<void (class_type::*)(int, ...) & noexcept>();
    test_has_no_virtual_destructor<void (class_type::*)(int, ...) && noexcept>();
    test_has_no_virtual_destructor<void (class_type::*)(int, ...) const noexcept>();
    test_has_no_virtual_destructor<void (class_type::*)(int, ...) const & noexcept>();
    test_has_no_virtual_destructor<void (class_type::*)(int, ...) const && noexcept>();

    test_has_no_virtual_destructor<int (class_type::*)()>();
    test_has_no_virtual_destructor<int (class_type::*)()&>();
    test_has_no_virtual_destructor<int (class_type::*)() &&>();
    test_has_no_virtual_destructor<int (class_type::*)() const>();
    test_has_no_virtual_destructor<int (class_type::*)() const&>();
    test_has_no_virtual_destructor<int (class_type::*)() const&&>();
    test_has_no_virtual_destructor<int (class_type::*)() noexcept>();
    test_has_no_virtual_destructor<int (class_type::*)() & noexcept>();
    test_has_no_virtual_destructor<int (class_type::*)() && noexcept>();
    test_has_no_virtual_destructor<int (class_type::*)() const noexcept>();
    test_has_no_virtual_destructor<int (class_type::*)() const & noexcept>();
    test_has_no_virtual_destructor<int (class_type::*)() const && noexcept>();

    test_has_no_virtual_destructor<int (class_type::*)(int)>();
    test_has_no_virtual_destructor<int (class_type::*)(int)&>();
    test_has_no_virtual_destructor<int (class_type::*)(int) &&>();
    test_has_no_virtual_destructor<int (class_type::*)(int) const>();
    test_has_no_virtual_destructor<int (class_type::*)(int) const&>();
    test_has_no_virtual_destructor<int (class_type::*)(int) const&&>();
    test_has_no_virtual_destructor<int (class_type::*)(int) noexcept>();
    test_has_no_virtual_destructor<int (class_type::*)(int) & noexcept>();
    test_has_no_virtual_destructor<int (class_type::*)(int) && noexcept>();
    test_has_no_virtual_destructor<int (class_type::*)(int) const noexcept>();
    test_has_no_virtual_destructor<int (class_type::*)(int) const & noexcept>();
    test_has_no_virtual_destructor<int (class_type::*)(int) const && noexcept>();

    test_has_no_virtual_destructor<int (class_type::*)(...)>();
    test_has_no_virtual_destructor<int (class_type::*)(...)&>();
    test_has_no_virtual_destructor<int (class_type::*)(...) &&>();
    test_has_no_virtual_destructor<int (class_type::*)(...) const>();
    test_has_no_virtual_destructor<int (class_type::*)(...) const&>();
    test_has_no_virtual_destructor<int (class_type::*)(...) const&&>();
    test_has_no_virtual_destructor<int (class_type::*)(...) noexcept>();
    test_has_no_virtual_destructor<int (class_type::*)(...) & noexcept>();
    test_has_no_virtual_destructor<int (class_type::*)(...) && noexcept>();
    test_has_no_virtual_destructor<int (class_type::*)(...) const noexcept>();
    test_has_no_virtual_destructor<int (class_type::*)(...) const & noexcept>();
    test_has_no_virtual_destructor<int (class_type::*)(...) const && noexcept>();

    test_has_no_virtual_destructor<int (class_type::*)(int, ...)>();
    test_has_no_virtual_destructor<int (class_type::*)(int, ...)&>();
    test_has_no_virtual_destructor<int (class_type::*)(int, ...) &&>();
    test_has_no_virtual_destructor<int (class_type::*)(int, ...) const>();
    test_has_no_virtual_destructor<int (class_type::*)(int, ...) const&>();
    test_has_no_virtual_destructor<int (class_type::*)(int, ...) const&&>();
    test_has_no_virtual_destructor<int (class_type::*)(int, ...) noexcept>();
    test_has_no_virtual_destructor<int (class_type::*)(int, ...) & noexcept>();
    test_has_no_virtual_destructor<int (class_type::*)(int, ...) && noexcept>();
    test_has_no_virtual_destructor<int (class_type::*)(int, ...) const noexcept>();
    test_has_no_virtual_destructor<int (class_type::*)(int, ...) const & noexcept>();
    test_has_no_virtual_destructor<int (class_type::*)(int, ...) const && noexcept>();
}
