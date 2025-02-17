#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_union.hpp>
#include <type_traits>
#include <vector>

template <typename TypeT>
void test_is_union_impl()
{
#if PHI_HAS_WORKING_IS_UNION()
    STATIC_REQUIRE(phi::is_union<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_union<TypeT>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_union_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_not_union_v<TypeT>);
#    endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_union<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_union<TypeT>);

    // Standard compatibility
    STATIC_REQUIRE(std::is_union<TypeT>::value);
#    if PHI_CPP_STANDARD_IS_ATLEAST(17) && PHI_COMPILER_WORKAROUND(GCC, 7, 0, 0)
    STATIC_REQUIRE(std::is_union_v<TypeT>);
#    endif
#endif
}

template <typename TypeT>
void test_is_union()
{
    test_is_union_impl<TypeT>();
    test_is_union_impl<const TypeT>();
    test_is_union_impl<volatile TypeT>();
    test_is_union_impl<const volatile TypeT>();
}

template <typename TypeT>
void test_is_not_union_impl()
{
#if PHI_HAS_WORKING_IS_UNION()
    STATIC_REQUIRE_FALSE(phi::is_union<TypeT>::value);
    STATIC_REQUIRE(phi::is_not_union<TypeT>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_union_v<TypeT>);
    STATIC_REQUIRE(phi::is_not_union_v<TypeT>);
#    endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_union<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_union<TypeT>);

    // Standard compatibility
    STATIC_REQUIRE_FALSE(std::is_union<TypeT>::value);
#    if PHI_CPP_STANDARD_IS_ATLEAST(17) && PHI_COMPILER_WORKAROUND(GCC, 7, 0, 0)
    STATIC_REQUIRE_FALSE(std::is_union_v<TypeT>);
#    endif
#endif
}

template <typename TypeT>
void test_is_not_union()
{
    test_is_not_union_impl<TypeT>();
    test_is_not_union_impl<const TypeT>();
    test_is_not_union_impl<volatile TypeT>();
    test_is_not_union_impl<const volatile TypeT>();
}

TEST_CASE("is_union")
{
    test_is_not_union<void>();
    test_is_not_union<phi::nullptr_t>();
    test_is_not_union<bool>();
    test_is_not_union<char>();
    test_is_not_union<signed char>();
    test_is_not_union<unsigned char>();
    test_is_not_union<short>();
    test_is_not_union<unsigned short>();
    test_is_not_union<int>();
    test_is_not_union<unsigned int>();
    test_is_not_union<long>();
    test_is_not_union<unsigned long>();
    test_is_not_union<long long>();
    test_is_not_union<unsigned long long>();
    test_is_not_union<float>();
    test_is_not_union<double>();
    test_is_not_union<long double>();
    test_is_not_union<char8_t>();
    test_is_not_union<char16_t>();
    test_is_not_union<char32_t>();
    test_is_not_union<wchar_t>();

    test_is_not_union<phi::boolean>();
    test_is_not_union<phi::integer<signed char>>();
    test_is_not_union<phi::integer<unsigned char>>();
    test_is_not_union<phi::integer<short>>();
    test_is_not_union<phi::integer<unsigned short>>();
    test_is_not_union<phi::integer<int>>();
    test_is_not_union<phi::integer<unsigned int>>();
    test_is_not_union<phi::integer<long>>();
    test_is_not_union<phi::integer<unsigned long>>();
    test_is_not_union<phi::integer<long long>>();
    test_is_not_union<phi::integer<unsigned long long>>();
    test_is_not_union<phi::floating_point<float>>();
    test_is_not_union<phi::floating_point<double>>();
    test_is_not_union<phi::floating_point<long double>>();

    test_is_not_union<std::vector<int>>();
    test_is_not_union<phi::scope_ptr<int>>();

    test_is_not_union<int&>();
    test_is_not_union<const int&>();
    test_is_not_union<volatile int&>();
    test_is_not_union<const volatile int&>();
    test_is_not_union<int&&>();
    test_is_not_union<const int&&>();
    test_is_not_union<volatile int&&>();
    test_is_not_union<const volatile int&&>();
    test_is_not_union<int*>();
    test_is_not_union<const int*>();
    test_is_not_union<volatile int*>();
    test_is_not_union<const volatile int*>();
    test_is_not_union<int**>();
    test_is_not_union<const int**>();
    test_is_not_union<volatile int**>();
    test_is_not_union<const volatile int**>();
    test_is_not_union<int*&>();
    test_is_not_union<const int*&>();
    test_is_not_union<volatile int*&>();
    test_is_not_union<const volatile int*&>();
    test_is_not_union<int*&&>();
    test_is_not_union<const int*&&>();
    test_is_not_union<volatile int*&&>();
    test_is_not_union<const volatile int*&&>();
    test_is_not_union<void*>();
    test_is_not_union<char[3]>();
    test_is_not_union<char[]>();
    test_is_not_union<char* [3]>();
    test_is_not_union<char*[]>();
    test_is_not_union<int(*)[3]>();
    test_is_not_union<int(*)[]>();
    test_is_not_union<int(&)[3]>();
    test_is_not_union<int(&)[]>();
    test_is_not_union<int(&&)[3]>();
    test_is_not_union<int(&&)[]>();
    test_is_not_union<char[3][2]>();
    test_is_not_union<char[][2]>();
    test_is_not_union<char* [3][2]>();
    test_is_not_union<char*[][2]>();
    test_is_not_union<int(*)[3][2]>();
    test_is_not_union<int(*)[][2]>();
    test_is_not_union<int(&)[3][2]>();
    test_is_not_union<int(&)[][2]>();
    test_is_not_union<int(&&)[3][2]>();
    test_is_not_union<int(&&)[][2]>();
    test_is_not_union<class_type>();
    test_is_not_union<class_type[]>();
    test_is_not_union<class_type[2]>();
    test_is_not_union<template_type<void>>();
    test_is_not_union<template_type<int>>();
    test_is_not_union<template_type<class_type>>();
    test_is_not_union<template_type<incomplete_type>>();
    test_is_not_union<variadic_template<>>();
    test_is_not_union<variadic_template<void>>();
    test_is_not_union<variadic_template<int>>();
    test_is_not_union<variadic_template<class_type>>();
    test_is_not_union<variadic_template<incomplete_type>>();
    test_is_not_union<variadic_template<int, void, class_type, volatile char[]>>();
    test_is_not_union<public_derived_from<base>>();
    test_is_not_union<public_derived_from<derived>>();
    test_is_not_union<public_derived_from<class_type>>();
    test_is_not_union<private_derived_from<base>>();
    test_is_not_union<private_derived_from<derived>>();
    test_is_not_union<private_derived_from<class_type>>();
    test_is_not_union<protected_derived_from<base>>();
    test_is_not_union<protected_derived_from<derived>>();
    test_is_not_union<protected_derived_from<class_type>>();
    test_is_union<union_type>();
    test_is_union<non_empty_union>();
    test_is_not_union<empty>();
    test_is_not_union<not_empty>();
    test_is_not_union<bit_zero>();
    test_is_not_union<bit_one>();
    test_is_not_union<base>();
    test_is_not_union<derived>();
    test_is_not_union<abstract>();
    test_is_not_union<public_abstract>();
    test_is_not_union<private_abstract>();
    test_is_not_union<protected_abstract>();
    test_is_not_union<abstract_template<int>>();
    test_is_not_union<abstract_template<double>>();
    test_is_not_union<abstract_template<class_type>>();
    test_is_not_union<abstract_template<incomplete_type>>();
    test_is_not_union<final_type>();
    test_is_not_union<public_destructor>();
    test_is_not_union<protected_destructor>();
    test_is_not_union<private_destructor>();
    test_is_not_union<virtual_public_destructor>();
    test_is_not_union<virtual_protected_destructor>();
    test_is_not_union<virtual_private_destructor>();
    test_is_not_union<pure_public_destructor>();
    test_is_not_union<pure_protected_destructor>();
    test_is_not_union<pure_private_destructor>();
    test_is_not_union<deleted_public_destructor>();
    test_is_not_union<deleted_protected_destructor>();
    test_is_not_union<deleted_private_destructor>();
    test_is_not_union<deleted_virtual_public_destructor>();
    test_is_not_union<deleted_virtual_protected_destructor>();
    test_is_not_union<deleted_virtual_private_destructor>();
    test_is_not_union<final_type>();
    test_is_not_union<Enum>();
    test_is_not_union<EnumSigned>();
    test_is_not_union<EnumUnsigned>();
    test_is_not_union<EnumClass>();
    test_is_not_union<EnumStruct>();
    test_is_not_union<function_type>();
    test_is_not_union<function_ptr>();
    test_is_not_union<member_object_ptr>();
    test_is_not_union<member_function_ptr>();
    test_is_not_union<incomplete_type>();
    test_is_not_union<incomplete_template<void>>();
    test_is_not_union<incomplete_template<int>>();
    test_is_not_union<incomplete_template<class_type>>();
    test_is_not_union<incomplete_template<incomplete_type>>();
    test_is_not_union<incomplete_variadic_template<>>();
    test_is_not_union<incomplete_variadic_template<void>>();
    test_is_not_union<incomplete_variadic_template<int>>();
    test_is_not_union<incomplete_variadic_template<class_type>>();
    test_is_not_union<incomplete_variadic_template<incomplete_type>>();
    test_is_not_union<incomplete_variadic_template<int, void, class_type, volatile char[]>>();
    test_is_not_union<int class_type::*>();
    test_is_not_union<float class_type::*>();
    test_is_not_union<void * class_type::*>();
    test_is_not_union<int * class_type::*>();
    test_is_not_union<int class_type::*&>();
    test_is_not_union<float class_type::*&>();
    test_is_not_union<void * class_type::*&>();
    test_is_not_union<int * class_type::*&>();
    test_is_not_union<int class_type::*&&>();
    test_is_not_union<float class_type::*&&>();
    test_is_not_union<void * class_type::*&&>();
    test_is_not_union<int * class_type::*&&>();
    test_is_not_union<int class_type::* const>();
    test_is_not_union<float class_type::* const>();
    test_is_not_union<void * class_type::* const>();
    test_is_not_union<int class_type::* const&>();
    test_is_not_union<float class_type::* const&>();
    test_is_not_union<void * class_type::* const&>();
    test_is_not_union<int class_type::* const&&>();
    test_is_not_union<float class_type::* const&&>();
    test_is_not_union<void * class_type::* const&&>();
    test_is_not_union<int class_type::* volatile>();
    test_is_not_union<float class_type::* volatile>();
    test_is_not_union<void * class_type::* volatile>();
    test_is_not_union<int class_type::* volatile&>();
    test_is_not_union<float class_type::* volatile&>();
    test_is_not_union<void * class_type::* volatile&>();
    test_is_not_union<int class_type::* volatile&&>();
    test_is_not_union<float class_type::* volatile&&>();
    test_is_not_union<void * class_type::* volatile&&>();
    test_is_not_union<int class_type::* const volatile>();
    test_is_not_union<float class_type::* const volatile>();
    test_is_not_union<void * class_type::* const volatile>();
    test_is_not_union<int class_type::* const volatile&>();
    test_is_not_union<float class_type::* const volatile&>();
    test_is_not_union<void * class_type::* const volatile&>();
    test_is_not_union<int class_type::* const volatile&&>();
    test_is_not_union<float class_type::* const volatile&&>();
    test_is_not_union<void * class_type::* const volatile&&>();
    test_is_not_union<non_copyable>();
    test_is_not_union<non_moveable>();
    test_is_not_union<non_constructible>();
    test_is_not_union<tracked>();
    test_is_not_union<trap_constructible>();
    test_is_not_union<trap_implicit_conversion>();
    test_is_not_union<trap_comma>();
    test_is_not_union<trap_call>();
    test_is_not_union<trap_self_assign>();
    test_is_not_union<trap_deref>();
    test_is_not_union<trap_array_subscript>();

    test_is_not_union<void()>();
    test_is_not_union<void()&>();
    test_is_not_union<void() &&>();
    test_is_not_union<void() const>();
    test_is_not_union<void() const&>();
    test_is_not_union<void() const&&>();
    test_is_not_union<void() volatile>();
    test_is_not_union<void() volatile&>();
    test_is_not_union<void() volatile&&>();
    test_is_not_union<void() const volatile>();
    test_is_not_union<void() const volatile&>();
    test_is_not_union<void() const volatile&&>();
    test_is_not_union<void() noexcept>();
    test_is_not_union<void() & noexcept>();
    test_is_not_union<void() && noexcept>();
    test_is_not_union<void() const noexcept>();
    test_is_not_union<void() const & noexcept>();
    test_is_not_union<void() const && noexcept>();
    test_is_not_union<void() volatile noexcept>();
    test_is_not_union<void() volatile & noexcept>();
    test_is_not_union<void() volatile && noexcept>();
    test_is_not_union<void() const volatile noexcept>();
    test_is_not_union<void() const volatile & noexcept>();
    test_is_not_union<void() const volatile && noexcept>();

    test_is_not_union<void(int)>();
    test_is_not_union<void(int)&>();
    test_is_not_union<void(int) &&>();
    test_is_not_union<void(int) const>();
    test_is_not_union<void(int) const&>();
    test_is_not_union<void(int) const&&>();
    test_is_not_union<void(int) volatile>();
    test_is_not_union<void(int) volatile&>();
    test_is_not_union<void(int) volatile&&>();
    test_is_not_union<void(int) const volatile>();
    test_is_not_union<void(int) const volatile&>();
    test_is_not_union<void(int) const volatile&&>();
    test_is_not_union<void(int) noexcept>();
    test_is_not_union<void(int) & noexcept>();
    test_is_not_union<void(int) && noexcept>();
    test_is_not_union<void(int) const noexcept>();
    test_is_not_union<void(int) const & noexcept>();
    test_is_not_union<void(int) const && noexcept>();
    test_is_not_union<void(int) volatile noexcept>();
    test_is_not_union<void(int) volatile & noexcept>();
    test_is_not_union<void(int) volatile && noexcept>();
    test_is_not_union<void(int) const volatile noexcept>();
    test_is_not_union<void(int) const volatile & noexcept>();
    test_is_not_union<void(int) const volatile && noexcept>();

    test_is_not_union<void(...)>();
    test_is_not_union<void(...)&>();
    test_is_not_union<void(...) &&>();
    test_is_not_union<void(...) const>();
    test_is_not_union<void(...) const&>();
    test_is_not_union<void(...) const&&>();
    test_is_not_union<void(...) volatile>();
    test_is_not_union<void(...) volatile&>();
    test_is_not_union<void(...) volatile&&>();
    test_is_not_union<void(...) const volatile>();
    test_is_not_union<void(...) const volatile&>();
    test_is_not_union<void(...) const volatile&&>();
    test_is_not_union<void(...) noexcept>();
    test_is_not_union<void(...) & noexcept>();
    test_is_not_union<void(...) && noexcept>();
    test_is_not_union<void(...) const noexcept>();
    test_is_not_union<void(...) const & noexcept>();
    test_is_not_union<void(...) const && noexcept>();
    test_is_not_union<void(...) volatile noexcept>();
    test_is_not_union<void(...) volatile & noexcept>();
    test_is_not_union<void(...) volatile && noexcept>();
    test_is_not_union<void(...) const volatile noexcept>();
    test_is_not_union<void(...) const volatile & noexcept>();
    test_is_not_union<void(...) const volatile && noexcept>();

    test_is_not_union<void(int, ...)>();
    test_is_not_union<void(int, ...)&>();
    test_is_not_union<void(int, ...) &&>();
    test_is_not_union<void(int, ...) const>();
    test_is_not_union<void(int, ...) const&>();
    test_is_not_union<void(int, ...) const&&>();
    test_is_not_union<void(int, ...) volatile>();
    test_is_not_union<void(int, ...) volatile&>();
    test_is_not_union<void(int, ...) volatile&&>();
    test_is_not_union<void(int, ...) const volatile>();
    test_is_not_union<void(int, ...) const volatile&>();
    test_is_not_union<void(int, ...) const volatile&&>();
    test_is_not_union<void(int, ...) noexcept>();
    test_is_not_union<void(int, ...) & noexcept>();
    test_is_not_union<void(int, ...) && noexcept>();
    test_is_not_union<void(int, ...) const noexcept>();
    test_is_not_union<void(int, ...) const & noexcept>();
    test_is_not_union<void(int, ...) const && noexcept>();
    test_is_not_union<void(int, ...) volatile noexcept>();
    test_is_not_union<void(int, ...) volatile & noexcept>();
    test_is_not_union<void(int, ...) volatile && noexcept>();
    test_is_not_union<void(int, ...) const volatile noexcept>();
    test_is_not_union<void(int, ...) const volatile & noexcept>();
    test_is_not_union<void(int, ...) const volatile && noexcept>();

    test_is_not_union<int()>();
    test_is_not_union<int()&>();
    test_is_not_union<int() &&>();
    test_is_not_union<int() const>();
    test_is_not_union<int() const&>();
    test_is_not_union<int() const&&>();
    test_is_not_union<int() volatile>();
    test_is_not_union<int() volatile&>();
    test_is_not_union<int() volatile&&>();
    test_is_not_union<int() const volatile>();
    test_is_not_union<int() const volatile&>();
    test_is_not_union<int() const volatile&&>();
    test_is_not_union<int() noexcept>();
    test_is_not_union<int() & noexcept>();
    test_is_not_union<int() && noexcept>();
    test_is_not_union<int() const noexcept>();
    test_is_not_union<int() const & noexcept>();
    test_is_not_union<int() const && noexcept>();
    test_is_not_union<int() volatile noexcept>();
    test_is_not_union<int() volatile & noexcept>();
    test_is_not_union<int() volatile && noexcept>();
    test_is_not_union<int() const volatile noexcept>();
    test_is_not_union<int() const volatile & noexcept>();
    test_is_not_union<int() const volatile && noexcept>();

    test_is_not_union<int(int)>();
    test_is_not_union<int(int)&>();
    test_is_not_union<int(int) &&>();
    test_is_not_union<int(int) const>();
    test_is_not_union<int(int) const&>();
    test_is_not_union<int(int) const&&>();
    test_is_not_union<int(int) volatile>();
    test_is_not_union<int(int) volatile&>();
    test_is_not_union<int(int) volatile&&>();
    test_is_not_union<int(int) const volatile>();
    test_is_not_union<int(int) const volatile&>();
    test_is_not_union<int(int) const volatile&&>();
    test_is_not_union<int(int) noexcept>();
    test_is_not_union<int(int) & noexcept>();
    test_is_not_union<int(int) && noexcept>();
    test_is_not_union<int(int) const noexcept>();
    test_is_not_union<int(int) const & noexcept>();
    test_is_not_union<int(int) const && noexcept>();
    test_is_not_union<int(int) volatile noexcept>();
    test_is_not_union<int(int) volatile & noexcept>();
    test_is_not_union<int(int) volatile && noexcept>();
    test_is_not_union<int(int) const volatile noexcept>();
    test_is_not_union<int(int) const volatile & noexcept>();
    test_is_not_union<int(int) const volatile && noexcept>();

    test_is_not_union<int(...)>();
    test_is_not_union<int(...)&>();
    test_is_not_union<int(...) &&>();
    test_is_not_union<int(...) const>();
    test_is_not_union<int(...) const&>();
    test_is_not_union<int(...) const&&>();
    test_is_not_union<int(...) volatile>();
    test_is_not_union<int(...) volatile&>();
    test_is_not_union<int(...) volatile&&>();
    test_is_not_union<int(...) const volatile>();
    test_is_not_union<int(...) const volatile&>();
    test_is_not_union<int(...) const volatile&&>();
    test_is_not_union<int(...) noexcept>();
    test_is_not_union<int(...) & noexcept>();
    test_is_not_union<int(...) && noexcept>();
    test_is_not_union<int(...) const noexcept>();
    test_is_not_union<int(...) const & noexcept>();
    test_is_not_union<int(...) const && noexcept>();
    test_is_not_union<int(...) volatile noexcept>();
    test_is_not_union<int(...) volatile & noexcept>();
    test_is_not_union<int(...) volatile && noexcept>();
    test_is_not_union<int(...) const volatile noexcept>();
    test_is_not_union<int(...) const volatile & noexcept>();
    test_is_not_union<int(...) const volatile && noexcept>();

    test_is_not_union<int(int, ...)>();
    test_is_not_union<int(int, ...)&>();
    test_is_not_union<int(int, ...) &&>();
    test_is_not_union<int(int, ...) const>();
    test_is_not_union<int(int, ...) const&>();
    test_is_not_union<int(int, ...) const&&>();
    test_is_not_union<int(int, ...) volatile>();
    test_is_not_union<int(int, ...) volatile&>();
    test_is_not_union<int(int, ...) volatile&&>();
    test_is_not_union<int(int, ...) const volatile>();
    test_is_not_union<int(int, ...) const volatile&>();
    test_is_not_union<int(int, ...) const volatile&&>();
    test_is_not_union<int(int, ...) noexcept>();
    test_is_not_union<int(int, ...) & noexcept>();
    test_is_not_union<int(int, ...) && noexcept>();
    test_is_not_union<int(int, ...) const noexcept>();
    test_is_not_union<int(int, ...) const & noexcept>();
    test_is_not_union<int(int, ...) const && noexcept>();
    test_is_not_union<int(int, ...) volatile noexcept>();
    test_is_not_union<int(int, ...) volatile & noexcept>();
    test_is_not_union<int(int, ...) volatile && noexcept>();
    test_is_not_union<int(int, ...) const volatile noexcept>();
    test_is_not_union<int(int, ...) const volatile & noexcept>();
    test_is_not_union<int(int, ...) const volatile && noexcept>();

    test_is_not_union<void (*)()>();
    test_is_not_union<void (*)() noexcept>();

    test_is_not_union<void (*)(int)>();
    test_is_not_union<void (*)(int) noexcept>();

    test_is_not_union<void (*)(...)>();
    test_is_not_union<void (*)(...) noexcept>();

    test_is_not_union<void (*)(int, ...)>();
    test_is_not_union<void (*)(int, ...) noexcept>();

    test_is_not_union<int (*)()>();
    test_is_not_union<int (*)() noexcept>();

    test_is_not_union<int (*)(int)>();
    test_is_not_union<int (*)(int) noexcept>();

    test_is_not_union<int (*)(...)>();
    test_is_not_union<int (*)(...) noexcept>();

    test_is_not_union<int (*)(int, ...)>();
    test_is_not_union<int (*)(int, ...) noexcept>();

    test_is_not_union<void (&)()>();
    test_is_not_union<void (&)() noexcept>();

    test_is_not_union<void (&)(int)>();
    test_is_not_union<void (&)(int) noexcept>();

    test_is_not_union<void (&)(...)>();
    test_is_not_union<void (&)(...) noexcept>();

    test_is_not_union<void (&)(int, ...)>();
    test_is_not_union<void (&)(int, ...) noexcept>();

    test_is_not_union<int (&)()>();
    test_is_not_union<int (&)() noexcept>();

    test_is_not_union<int (&)(int)>();
    test_is_not_union<int (&)(int) noexcept>();

    test_is_not_union<int (&)(...)>();
    test_is_not_union<int (&)(...) noexcept>();

    test_is_not_union<int (&)(int, ...)>();
    test_is_not_union<int (&)(int, ...) noexcept>();

    test_is_not_union<void (&&)()>();
    test_is_not_union<void (&&)() noexcept>();

    test_is_not_union<void (&&)(int)>();
    test_is_not_union<void (&&)(int) noexcept>();

    test_is_not_union<void (&&)(...)>();
    test_is_not_union<void (&&)(...) noexcept>();

    test_is_not_union<void (&&)(int, ...)>();
    test_is_not_union<void (&&)(int, ...) noexcept>();

    test_is_not_union<int (&&)()>();
    test_is_not_union<int (&&)() noexcept>();

    test_is_not_union<int (&&)(int)>();
    test_is_not_union<int (&&)(int) noexcept>();

    test_is_not_union<int (&&)(...)>();
    test_is_not_union<int (&&)(...) noexcept>();

    test_is_not_union<int (&&)(int, ...)>();
    test_is_not_union<int (&&)(int, ...) noexcept>();

    test_is_not_union<void (class_type::*)()>();
    test_is_not_union<void (class_type::*)()&>();
    test_is_not_union<void (class_type::*)() &&>();
    test_is_not_union<void (class_type::*)() const>();
    test_is_not_union<void (class_type::*)() const&>();
    test_is_not_union<void (class_type::*)() const&&>();
    test_is_not_union<void (class_type::*)() noexcept>();
    test_is_not_union<void (class_type::*)() & noexcept>();
    test_is_not_union<void (class_type::*)() && noexcept>();
    test_is_not_union<void (class_type::*)() const noexcept>();
    test_is_not_union<void (class_type::*)() const & noexcept>();
    test_is_not_union<void (class_type::*)() const && noexcept>();

    test_is_not_union<void (class_type::*)(int)>();
    test_is_not_union<void (class_type::*)(int)&>();
    test_is_not_union<void (class_type::*)(int) &&>();
    test_is_not_union<void (class_type::*)(int) const>();
    test_is_not_union<void (class_type::*)(int) const&>();
    test_is_not_union<void (class_type::*)(int) const&&>();
    test_is_not_union<void (class_type::*)(int) noexcept>();
    test_is_not_union<void (class_type::*)(int) & noexcept>();
    test_is_not_union<void (class_type::*)(int) && noexcept>();
    test_is_not_union<void (class_type::*)(int) const noexcept>();
    test_is_not_union<void (class_type::*)(int) const & noexcept>();
    test_is_not_union<void (class_type::*)(int) const && noexcept>();

    test_is_not_union<void (class_type::*)(...)>();
    test_is_not_union<void (class_type::*)(...)&>();
    test_is_not_union<void (class_type::*)(...) &&>();
    test_is_not_union<void (class_type::*)(...) const>();
    test_is_not_union<void (class_type::*)(...) const&>();
    test_is_not_union<void (class_type::*)(...) const&&>();
    test_is_not_union<void (class_type::*)(...) noexcept>();
    test_is_not_union<void (class_type::*)(...) & noexcept>();
    test_is_not_union<void (class_type::*)(...) && noexcept>();
    test_is_not_union<void (class_type::*)(...) const noexcept>();
    test_is_not_union<void (class_type::*)(...) const & noexcept>();
    test_is_not_union<void (class_type::*)(...) const && noexcept>();

    test_is_not_union<void (class_type::*)(int, ...)>();
    test_is_not_union<void (class_type::*)(int, ...)&>();
    test_is_not_union<void (class_type::*)(int, ...) &&>();
    test_is_not_union<void (class_type::*)(int, ...) const>();
    test_is_not_union<void (class_type::*)(int, ...) const&>();
    test_is_not_union<void (class_type::*)(int, ...) const&&>();
    test_is_not_union<void (class_type::*)(int, ...) noexcept>();
    test_is_not_union<void (class_type::*)(int, ...) & noexcept>();
    test_is_not_union<void (class_type::*)(int, ...) && noexcept>();
    test_is_not_union<void (class_type::*)(int, ...) const noexcept>();
    test_is_not_union<void (class_type::*)(int, ...) const & noexcept>();
    test_is_not_union<void (class_type::*)(int, ...) const && noexcept>();

    test_is_not_union<int (class_type::*)()>();
    test_is_not_union<int (class_type::*)()&>();
    test_is_not_union<int (class_type::*)() &&>();
    test_is_not_union<int (class_type::*)() const>();
    test_is_not_union<int (class_type::*)() const&>();
    test_is_not_union<int (class_type::*)() const&&>();
    test_is_not_union<int (class_type::*)() noexcept>();
    test_is_not_union<int (class_type::*)() & noexcept>();
    test_is_not_union<int (class_type::*)() && noexcept>();
    test_is_not_union<int (class_type::*)() const noexcept>();
    test_is_not_union<int (class_type::*)() const & noexcept>();
    test_is_not_union<int (class_type::*)() const && noexcept>();

    test_is_not_union<int (class_type::*)(int)>();
    test_is_not_union<int (class_type::*)(int)&>();
    test_is_not_union<int (class_type::*)(int) &&>();
    test_is_not_union<int (class_type::*)(int) const>();
    test_is_not_union<int (class_type::*)(int) const&>();
    test_is_not_union<int (class_type::*)(int) const&&>();
    test_is_not_union<int (class_type::*)(int) noexcept>();
    test_is_not_union<int (class_type::*)(int) & noexcept>();
    test_is_not_union<int (class_type::*)(int) && noexcept>();
    test_is_not_union<int (class_type::*)(int) const noexcept>();
    test_is_not_union<int (class_type::*)(int) const & noexcept>();
    test_is_not_union<int (class_type::*)(int) const && noexcept>();

    test_is_not_union<int (class_type::*)(...)>();
    test_is_not_union<int (class_type::*)(...)&>();
    test_is_not_union<int (class_type::*)(...) &&>();
    test_is_not_union<int (class_type::*)(...) const>();
    test_is_not_union<int (class_type::*)(...) const&>();
    test_is_not_union<int (class_type::*)(...) const&&>();
    test_is_not_union<int (class_type::*)(...) noexcept>();
    test_is_not_union<int (class_type::*)(...) & noexcept>();
    test_is_not_union<int (class_type::*)(...) && noexcept>();
    test_is_not_union<int (class_type::*)(...) const noexcept>();
    test_is_not_union<int (class_type::*)(...) const & noexcept>();
    test_is_not_union<int (class_type::*)(...) const && noexcept>();

    test_is_not_union<int (class_type::*)(int, ...)>();
    test_is_not_union<int (class_type::*)(int, ...)&>();
    test_is_not_union<int (class_type::*)(int, ...) &&>();
    test_is_not_union<int (class_type::*)(int, ...) const>();
    test_is_not_union<int (class_type::*)(int, ...) const&>();
    test_is_not_union<int (class_type::*)(int, ...) const&&>();
    test_is_not_union<int (class_type::*)(int, ...) noexcept>();
    test_is_not_union<int (class_type::*)(int, ...) & noexcept>();
    test_is_not_union<int (class_type::*)(int, ...) && noexcept>();
    test_is_not_union<int (class_type::*)(int, ...) const noexcept>();
    test_is_not_union<int (class_type::*)(int, ...) const & noexcept>();
    test_is_not_union<int (class_type::*)(int, ...) const && noexcept>();
}
