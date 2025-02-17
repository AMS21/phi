#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/compiler_support/compiler.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_bounded_array.hpp>
#include <type_traits>
#include <vector>

template <typename TypeT>
void test_is_bounded_array_impl()
{
    STATIC_REQUIRE(phi::is_bounded_array<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_bounded_array<TypeT>::value);

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_bounded_array<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_bounded_array<TypeT>);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_bounded_array_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_not_bounded_array_v<TypeT>);
#endif

    // Standard compatibility
#if PHI_CPP_STANDARD_IS_ATLEAST(20) && !PHI_COMPILER_IS_BELOW(GCC, 9, 0, 0) &&                     \
        !PHI_COMPILER_IS_BELOW(EMCC, 1, 39, 0)
    STATIC_REQUIRE(std::is_bounded_array<TypeT>::value);
#endif
}

template <typename TypeT>
void test_is_bounded_array()
{
    test_is_bounded_array_impl<TypeT>();
    test_is_bounded_array_impl<const TypeT>();
    test_is_bounded_array_impl<volatile TypeT>();
    test_is_bounded_array_impl<const volatile TypeT>();
}

template <typename TypeT>
void test_is_not_bounded_array_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_bounded_array<TypeT>::value);
    STATIC_REQUIRE(phi::is_not_bounded_array<TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_bounded_array_v<TypeT>);
    STATIC_REQUIRE(phi::is_not_bounded_array_v<TypeT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_bounded_array<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_bounded_array<TypeT>);

    // Standard compatibility
#if PHI_CPP_STANDARD_IS_ATLEAST(20) && !PHI_COMPILER_IS_BELOW(GCC, 9, 0, 0) &&                     \
        !PHI_COMPILER_IS_BELOW(EMCC, 1, 39, 0)
    STATIC_REQUIRE_FALSE(std::is_bounded_array<TypeT>::value);
#endif
}

template <typename TypeT>
void test_is_not_bounded_array()
{
    test_is_not_bounded_array_impl<TypeT>();
    test_is_not_bounded_array_impl<const TypeT>();
    test_is_not_bounded_array_impl<volatile TypeT>();
    test_is_not_bounded_array_impl<const volatile TypeT>();
}

struct A
{};

TEST_CASE("is_bounded_array")
{
    test_is_not_bounded_array<void>();
    test_is_not_bounded_array<phi::nullptr_t>();
    test_is_not_bounded_array<bool>();
    test_is_not_bounded_array<char>();
    test_is_not_bounded_array<signed char>();
    test_is_not_bounded_array<unsigned char>();
    test_is_not_bounded_array<short>();
    test_is_not_bounded_array<unsigned short>();
    test_is_not_bounded_array<int>();
    test_is_not_bounded_array<unsigned int>();
    test_is_not_bounded_array<long>();
    test_is_not_bounded_array<unsigned long>();
    test_is_not_bounded_array<long long>();
    test_is_not_bounded_array<unsigned long long>();
    test_is_not_bounded_array<float>();
    test_is_not_bounded_array<double>();
    test_is_not_bounded_array<long double>();
    test_is_not_bounded_array<char8_t>();
    test_is_not_bounded_array<char16_t>();
    test_is_not_bounded_array<char32_t>();
    test_is_not_bounded_array<wchar_t>();

    test_is_not_bounded_array<phi::boolean>();
    test_is_not_bounded_array<phi::integer<signed char>>();
    test_is_not_bounded_array<phi::integer<unsigned char>>();
    test_is_not_bounded_array<phi::integer<short>>();
    test_is_not_bounded_array<phi::integer<unsigned short>>();
    test_is_not_bounded_array<phi::integer<int>>();
    test_is_not_bounded_array<phi::integer<unsigned int>>();
    test_is_not_bounded_array<phi::integer<long>>();
    test_is_not_bounded_array<phi::integer<unsigned long>>();
    test_is_not_bounded_array<phi::integer<long long>>();
    test_is_not_bounded_array<phi::integer<unsigned long long>>();
    test_is_not_bounded_array<phi::floating_point<float>>();
    test_is_not_bounded_array<phi::floating_point<double>>();
    test_is_not_bounded_array<phi::floating_point<long double>>();

    test_is_not_bounded_array<std::vector<int>>();
    test_is_not_bounded_array<phi::scope_ptr<int>>();

    test_is_not_bounded_array<int&>();
    test_is_not_bounded_array<const int&>();
    test_is_not_bounded_array<volatile int&>();
    test_is_not_bounded_array<const volatile int&>();
    test_is_not_bounded_array<int&&>();
    test_is_not_bounded_array<const int&&>();
    test_is_not_bounded_array<volatile int&&>();
    test_is_not_bounded_array<const volatile int&&>();
    test_is_not_bounded_array<int*>();
    test_is_not_bounded_array<const int*>();
    test_is_not_bounded_array<volatile int*>();
    test_is_not_bounded_array<const volatile int*>();
    test_is_not_bounded_array<int**>();
    test_is_not_bounded_array<const int**>();
    test_is_not_bounded_array<volatile int**>();
    test_is_not_bounded_array<const volatile int**>();
    test_is_not_bounded_array<int*&>();
    test_is_not_bounded_array<const int*&>();
    test_is_not_bounded_array<volatile int*&>();
    test_is_not_bounded_array<const volatile int*&>();
    test_is_not_bounded_array<int*&&>();
    test_is_not_bounded_array<const int*&&>();
    test_is_not_bounded_array<volatile int*&&>();
    test_is_not_bounded_array<const volatile int*&&>();
    test_is_not_bounded_array<void*>();
    test_is_bounded_array<char[3]>();
    test_is_not_bounded_array<char[]>();
    test_is_bounded_array<char* [3]>();
    test_is_not_bounded_array<char*[]>();
    test_is_not_bounded_array<int(*)[3]>();
    test_is_not_bounded_array<int(*)[]>();
    test_is_not_bounded_array<int(&)[3]>();
    test_is_not_bounded_array<int(&)[]>();
    test_is_not_bounded_array<int(&&)[3]>();
    test_is_not_bounded_array<int(&&)[]>();
    test_is_bounded_array<char[3][2]>();
    test_is_not_bounded_array<char[][2]>();
    test_is_bounded_array<char* [3][2]>();
    test_is_not_bounded_array<char*[][2]>();
    test_is_not_bounded_array<int(*)[3][2]>();
    test_is_not_bounded_array<int(*)[][2]>();
    test_is_not_bounded_array<int(&)[3][2]>();
    test_is_not_bounded_array<int(&)[][2]>();
    test_is_not_bounded_array<int(&&)[3][2]>();
    test_is_not_bounded_array<int(&&)[][2]>();
    test_is_not_bounded_array<class_type>();
    test_is_not_bounded_array<class_type[]>();
    test_is_bounded_array<class_type[2]>();
    test_is_not_bounded_array<template_type<void>>();
    test_is_not_bounded_array<template_type<int>>();
    test_is_not_bounded_array<template_type<class_type>>();
    test_is_not_bounded_array<template_type<incomplete_type>>();
    test_is_not_bounded_array<variadic_template<>>();
    test_is_not_bounded_array<variadic_template<void>>();
    test_is_not_bounded_array<variadic_template<int>>();
    test_is_not_bounded_array<variadic_template<class_type>>();
    test_is_not_bounded_array<variadic_template<incomplete_type>>();
    test_is_not_bounded_array<variadic_template<int, void, class_type, volatile char[]>>();
    test_is_not_bounded_array<public_derived_from<base>>();
    test_is_not_bounded_array<public_derived_from<derived>>();
    test_is_not_bounded_array<public_derived_from<class_type>>();
    test_is_not_bounded_array<private_derived_from<base>>();
    test_is_not_bounded_array<private_derived_from<derived>>();
    test_is_not_bounded_array<private_derived_from<class_type>>();
    test_is_not_bounded_array<protected_derived_from<base>>();
    test_is_not_bounded_array<protected_derived_from<derived>>();
    test_is_not_bounded_array<protected_derived_from<class_type>>();
    test_is_not_bounded_array<union_type>();
    test_is_not_bounded_array<non_empty_union>();
    test_is_not_bounded_array<empty>();
    test_is_not_bounded_array<not_empty>();
    test_is_not_bounded_array<bit_zero>();
    test_is_not_bounded_array<bit_one>();
    test_is_not_bounded_array<base>();
    test_is_not_bounded_array<derived>();
    test_is_not_bounded_array<abstract>();
    test_is_not_bounded_array<public_abstract>();
    test_is_not_bounded_array<private_abstract>();
    test_is_not_bounded_array<protected_abstract>();
    test_is_not_bounded_array<abstract_template<int>>();
    test_is_not_bounded_array<abstract_template<double>>();
    test_is_not_bounded_array<abstract_template<class_type>>();
    test_is_not_bounded_array<abstract_template<incomplete_type>>();
    test_is_not_bounded_array<final_type>();
    test_is_not_bounded_array<public_destructor>();
    test_is_not_bounded_array<protected_destructor>();
    test_is_not_bounded_array<private_destructor>();
    test_is_not_bounded_array<virtual_public_destructor>();
    test_is_not_bounded_array<virtual_protected_destructor>();
    test_is_not_bounded_array<virtual_private_destructor>();
    test_is_not_bounded_array<pure_public_destructor>();
    test_is_not_bounded_array<pure_protected_destructor>();
    test_is_not_bounded_array<pure_private_destructor>();
    test_is_not_bounded_array<deleted_public_destructor>();
    test_is_not_bounded_array<deleted_protected_destructor>();
    test_is_not_bounded_array<deleted_private_destructor>();
    test_is_not_bounded_array<deleted_virtual_public_destructor>();
    test_is_not_bounded_array<deleted_virtual_protected_destructor>();
    test_is_not_bounded_array<deleted_virtual_private_destructor>();
    test_is_not_bounded_array<Enum>();
    test_is_not_bounded_array<EnumSigned>();
    test_is_not_bounded_array<EnumUnsigned>();
    test_is_not_bounded_array<EnumClass>();
    test_is_not_bounded_array<EnumStruct>();
    test_is_not_bounded_array<function_type>();
    test_is_not_bounded_array<function_ptr>();
    test_is_not_bounded_array<member_object_ptr>();
    test_is_not_bounded_array<member_function_ptr>();
    test_is_not_bounded_array<incomplete_type>();
    test_is_not_bounded_array<incomplete_template<void>>();
    test_is_not_bounded_array<incomplete_template<int>>();
    test_is_not_bounded_array<incomplete_template<class_type>>();
    test_is_not_bounded_array<incomplete_template<incomplete_type>>();
    test_is_not_bounded_array<incomplete_variadic_template<>>();
    test_is_not_bounded_array<incomplete_variadic_template<void>>();
    test_is_not_bounded_array<incomplete_variadic_template<int>>();
    test_is_not_bounded_array<incomplete_variadic_template<class_type>>();
    test_is_not_bounded_array<incomplete_variadic_template<incomplete_type>>();
    test_is_not_bounded_array<
            incomplete_variadic_template<int, void, class_type, volatile char[]>>();
    test_is_not_bounded_array<int class_type::*>();
    test_is_not_bounded_array<float class_type::*>();
    test_is_not_bounded_array<void * class_type::*>();
    test_is_not_bounded_array<int * class_type::*>();
    test_is_not_bounded_array<int class_type::*&>();
    test_is_not_bounded_array<float class_type::*&>();
    test_is_not_bounded_array<void * class_type::*&>();
    test_is_not_bounded_array<int * class_type::*&>();
    test_is_not_bounded_array<int class_type::*&&>();
    test_is_not_bounded_array<float class_type::*&&>();
    test_is_not_bounded_array<void * class_type::*&&>();
    test_is_not_bounded_array<int * class_type::*&&>();
    test_is_not_bounded_array<int class_type::* const>();
    test_is_not_bounded_array<float class_type::* const>();
    test_is_not_bounded_array<void * class_type::* const>();
    test_is_not_bounded_array<int class_type::* const&>();
    test_is_not_bounded_array<float class_type::* const&>();
    test_is_not_bounded_array<void * class_type::* const&>();
    test_is_not_bounded_array<int class_type::* const&&>();
    test_is_not_bounded_array<float class_type::* const&&>();
    test_is_not_bounded_array<void * class_type::* const&&>();
    test_is_not_bounded_array<int class_type::* volatile>();
    test_is_not_bounded_array<float class_type::* volatile>();
    test_is_not_bounded_array<void * class_type::* volatile>();
    test_is_not_bounded_array<int class_type::* volatile&>();
    test_is_not_bounded_array<float class_type::* volatile&>();
    test_is_not_bounded_array<void * class_type::* volatile&>();
    test_is_not_bounded_array<int class_type::* volatile&&>();
    test_is_not_bounded_array<float class_type::* volatile&&>();
    test_is_not_bounded_array<void * class_type::* volatile&&>();
    test_is_not_bounded_array<int class_type::* const volatile>();
    test_is_not_bounded_array<float class_type::* const volatile>();
    test_is_not_bounded_array<void * class_type::* const volatile>();
    test_is_not_bounded_array<int class_type::* const volatile&>();
    test_is_not_bounded_array<float class_type::* const volatile&>();
    test_is_not_bounded_array<void * class_type::* const volatile&>();
    test_is_not_bounded_array<int class_type::* const volatile&&>();
    test_is_not_bounded_array<float class_type::* const volatile&&>();
    test_is_not_bounded_array<void * class_type::* const volatile&&>();
    test_is_not_bounded_array<non_copyable>();
    test_is_not_bounded_array<non_moveable>();
    test_is_not_bounded_array<non_constructible>();
    test_is_not_bounded_array<tracked>();
    test_is_not_bounded_array<trap_constructible>();
    test_is_not_bounded_array<trap_implicit_conversion>();
    test_is_not_bounded_array<trap_comma>();
    test_is_not_bounded_array<trap_call>();
    test_is_not_bounded_array<trap_self_assign>();
    test_is_not_bounded_array<trap_deref>();
    test_is_not_bounded_array<trap_array_subscript>();

    test_is_not_bounded_array<void()>();
    test_is_not_bounded_array<void()&>();
    test_is_not_bounded_array<void() &&>();
    test_is_not_bounded_array<void() const>();
    test_is_not_bounded_array<void() const&>();
    test_is_not_bounded_array<void() const&&>();
    test_is_not_bounded_array<void() volatile>();
    test_is_not_bounded_array<void() volatile&>();
    test_is_not_bounded_array<void() volatile&&>();
    test_is_not_bounded_array<void() const volatile>();
    test_is_not_bounded_array<void() const volatile&>();
    test_is_not_bounded_array<void() const volatile&&>();
    test_is_not_bounded_array<void() noexcept>();
    test_is_not_bounded_array<void() & noexcept>();
    test_is_not_bounded_array<void() && noexcept>();
    test_is_not_bounded_array<void() const noexcept>();
    test_is_not_bounded_array<void() const & noexcept>();
    test_is_not_bounded_array<void() const && noexcept>();
    test_is_not_bounded_array<void() volatile noexcept>();
    test_is_not_bounded_array<void() volatile & noexcept>();
    test_is_not_bounded_array<void() volatile && noexcept>();
    test_is_not_bounded_array<void() const volatile noexcept>();
    test_is_not_bounded_array<void() const volatile & noexcept>();
    test_is_not_bounded_array<void() const volatile && noexcept>();

    test_is_not_bounded_array<void(int)>();
    test_is_not_bounded_array<void(int)&>();
    test_is_not_bounded_array<void(int) &&>();
    test_is_not_bounded_array<void(int) const>();
    test_is_not_bounded_array<void(int) const&>();
    test_is_not_bounded_array<void(int) const&&>();
    test_is_not_bounded_array<void(int) volatile>();
    test_is_not_bounded_array<void(int) volatile&>();
    test_is_not_bounded_array<void(int) volatile&&>();
    test_is_not_bounded_array<void(int) const volatile>();
    test_is_not_bounded_array<void(int) const volatile&>();
    test_is_not_bounded_array<void(int) const volatile&&>();
    test_is_not_bounded_array<void(int) noexcept>();
    test_is_not_bounded_array<void(int) & noexcept>();
    test_is_not_bounded_array<void(int) && noexcept>();
    test_is_not_bounded_array<void(int) const noexcept>();
    test_is_not_bounded_array<void(int) const & noexcept>();
    test_is_not_bounded_array<void(int) const && noexcept>();
    test_is_not_bounded_array<void(int) volatile noexcept>();
    test_is_not_bounded_array<void(int) volatile & noexcept>();
    test_is_not_bounded_array<void(int) volatile && noexcept>();
    test_is_not_bounded_array<void(int) const volatile noexcept>();
    test_is_not_bounded_array<void(int) const volatile & noexcept>();
    test_is_not_bounded_array<void(int) const volatile && noexcept>();

    test_is_not_bounded_array<void(...)>();
    test_is_not_bounded_array<void(...)&>();
    test_is_not_bounded_array<void(...) &&>();
    test_is_not_bounded_array<void(...) const>();
    test_is_not_bounded_array<void(...) const&>();
    test_is_not_bounded_array<void(...) const&&>();
    test_is_not_bounded_array<void(...) volatile>();
    test_is_not_bounded_array<void(...) volatile&>();
    test_is_not_bounded_array<void(...) volatile&&>();
    test_is_not_bounded_array<void(...) const volatile>();
    test_is_not_bounded_array<void(...) const volatile&>();
    test_is_not_bounded_array<void(...) const volatile&&>();
    test_is_not_bounded_array<void(...) noexcept>();
    test_is_not_bounded_array<void(...) & noexcept>();
    test_is_not_bounded_array<void(...) && noexcept>();
    test_is_not_bounded_array<void(...) const noexcept>();
    test_is_not_bounded_array<void(...) const & noexcept>();
    test_is_not_bounded_array<void(...) const && noexcept>();
    test_is_not_bounded_array<void(...) volatile noexcept>();
    test_is_not_bounded_array<void(...) volatile & noexcept>();
    test_is_not_bounded_array<void(...) volatile && noexcept>();
    test_is_not_bounded_array<void(...) const volatile noexcept>();
    test_is_not_bounded_array<void(...) const volatile & noexcept>();
    test_is_not_bounded_array<void(...) const volatile && noexcept>();

    test_is_not_bounded_array<void(int, ...)>();
    test_is_not_bounded_array<void(int, ...)&>();
    test_is_not_bounded_array<void(int, ...) &&>();
    test_is_not_bounded_array<void(int, ...) const>();
    test_is_not_bounded_array<void(int, ...) const&>();
    test_is_not_bounded_array<void(int, ...) const&&>();
    test_is_not_bounded_array<void(int, ...) volatile>();
    test_is_not_bounded_array<void(int, ...) volatile&>();
    test_is_not_bounded_array<void(int, ...) volatile&&>();
    test_is_not_bounded_array<void(int, ...) const volatile>();
    test_is_not_bounded_array<void(int, ...) const volatile&>();
    test_is_not_bounded_array<void(int, ...) const volatile&&>();
    test_is_not_bounded_array<void(int, ...) noexcept>();
    test_is_not_bounded_array<void(int, ...) & noexcept>();
    test_is_not_bounded_array<void(int, ...) && noexcept>();
    test_is_not_bounded_array<void(int, ...) const noexcept>();
    test_is_not_bounded_array<void(int, ...) const & noexcept>();
    test_is_not_bounded_array<void(int, ...) const && noexcept>();
    test_is_not_bounded_array<void(int, ...) volatile noexcept>();
    test_is_not_bounded_array<void(int, ...) volatile & noexcept>();
    test_is_not_bounded_array<void(int, ...) volatile && noexcept>();
    test_is_not_bounded_array<void(int, ...) const volatile noexcept>();
    test_is_not_bounded_array<void(int, ...) const volatile & noexcept>();
    test_is_not_bounded_array<void(int, ...) const volatile && noexcept>();

    test_is_not_bounded_array<int()>();
    test_is_not_bounded_array<int()&>();
    test_is_not_bounded_array<int() &&>();
    test_is_not_bounded_array<int() const>();
    test_is_not_bounded_array<int() const&>();
    test_is_not_bounded_array<int() const&&>();
    test_is_not_bounded_array<int() volatile>();
    test_is_not_bounded_array<int() volatile&>();
    test_is_not_bounded_array<int() volatile&&>();
    test_is_not_bounded_array<int() const volatile>();
    test_is_not_bounded_array<int() const volatile&>();
    test_is_not_bounded_array<int() const volatile&&>();
    test_is_not_bounded_array<int() noexcept>();
    test_is_not_bounded_array<int() & noexcept>();
    test_is_not_bounded_array<int() && noexcept>();
    test_is_not_bounded_array<int() const noexcept>();
    test_is_not_bounded_array<int() const & noexcept>();
    test_is_not_bounded_array<int() const && noexcept>();
    test_is_not_bounded_array<int() volatile noexcept>();
    test_is_not_bounded_array<int() volatile & noexcept>();
    test_is_not_bounded_array<int() volatile && noexcept>();
    test_is_not_bounded_array<int() const volatile noexcept>();
    test_is_not_bounded_array<int() const volatile & noexcept>();
    test_is_not_bounded_array<int() const volatile && noexcept>();

    test_is_not_bounded_array<int(int)>();
    test_is_not_bounded_array<int(int)&>();
    test_is_not_bounded_array<int(int) &&>();
    test_is_not_bounded_array<int(int) const>();
    test_is_not_bounded_array<int(int) const&>();
    test_is_not_bounded_array<int(int) const&&>();
    test_is_not_bounded_array<int(int) volatile>();
    test_is_not_bounded_array<int(int) volatile&>();
    test_is_not_bounded_array<int(int) volatile&&>();
    test_is_not_bounded_array<int(int) const volatile>();
    test_is_not_bounded_array<int(int) const volatile&>();
    test_is_not_bounded_array<int(int) const volatile&&>();
    test_is_not_bounded_array<int(int) noexcept>();
    test_is_not_bounded_array<int(int) & noexcept>();
    test_is_not_bounded_array<int(int) && noexcept>();
    test_is_not_bounded_array<int(int) const noexcept>();
    test_is_not_bounded_array<int(int) const & noexcept>();
    test_is_not_bounded_array<int(int) const && noexcept>();
    test_is_not_bounded_array<int(int) volatile noexcept>();
    test_is_not_bounded_array<int(int) volatile & noexcept>();
    test_is_not_bounded_array<int(int) volatile && noexcept>();
    test_is_not_bounded_array<int(int) const volatile noexcept>();
    test_is_not_bounded_array<int(int) const volatile & noexcept>();
    test_is_not_bounded_array<int(int) const volatile && noexcept>();

    test_is_not_bounded_array<int(...)>();
    test_is_not_bounded_array<int(...)&>();
    test_is_not_bounded_array<int(...) &&>();
    test_is_not_bounded_array<int(...) const>();
    test_is_not_bounded_array<int(...) const&>();
    test_is_not_bounded_array<int(...) const&&>();
    test_is_not_bounded_array<int(...) volatile>();
    test_is_not_bounded_array<int(...) volatile&>();
    test_is_not_bounded_array<int(...) volatile&&>();
    test_is_not_bounded_array<int(...) const volatile>();
    test_is_not_bounded_array<int(...) const volatile&>();
    test_is_not_bounded_array<int(...) const volatile&&>();
    test_is_not_bounded_array<int(...) noexcept>();
    test_is_not_bounded_array<int(...) & noexcept>();
    test_is_not_bounded_array<int(...) && noexcept>();
    test_is_not_bounded_array<int(...) const noexcept>();
    test_is_not_bounded_array<int(...) const & noexcept>();
    test_is_not_bounded_array<int(...) const && noexcept>();
    test_is_not_bounded_array<int(...) volatile noexcept>();
    test_is_not_bounded_array<int(...) volatile & noexcept>();
    test_is_not_bounded_array<int(...) volatile && noexcept>();
    test_is_not_bounded_array<int(...) const volatile noexcept>();
    test_is_not_bounded_array<int(...) const volatile & noexcept>();
    test_is_not_bounded_array<int(...) const volatile && noexcept>();

    test_is_not_bounded_array<int(int, ...)>();
    test_is_not_bounded_array<int(int, ...)&>();
    test_is_not_bounded_array<int(int, ...) &&>();
    test_is_not_bounded_array<int(int, ...) const>();
    test_is_not_bounded_array<int(int, ...) const&>();
    test_is_not_bounded_array<int(int, ...) const&&>();
    test_is_not_bounded_array<int(int, ...) volatile>();
    test_is_not_bounded_array<int(int, ...) volatile&>();
    test_is_not_bounded_array<int(int, ...) volatile&&>();
    test_is_not_bounded_array<int(int, ...) const volatile>();
    test_is_not_bounded_array<int(int, ...) const volatile&>();
    test_is_not_bounded_array<int(int, ...) const volatile&&>();
    test_is_not_bounded_array<int(int, ...) noexcept>();
    test_is_not_bounded_array<int(int, ...) & noexcept>();
    test_is_not_bounded_array<int(int, ...) && noexcept>();
    test_is_not_bounded_array<int(int, ...) const noexcept>();
    test_is_not_bounded_array<int(int, ...) const & noexcept>();
    test_is_not_bounded_array<int(int, ...) const && noexcept>();
    test_is_not_bounded_array<int(int, ...) volatile noexcept>();
    test_is_not_bounded_array<int(int, ...) volatile & noexcept>();
    test_is_not_bounded_array<int(int, ...) volatile && noexcept>();
    test_is_not_bounded_array<int(int, ...) const volatile noexcept>();
    test_is_not_bounded_array<int(int, ...) const volatile & noexcept>();
    test_is_not_bounded_array<int(int, ...) const volatile && noexcept>();

    test_is_not_bounded_array<void (*)()>();
    test_is_not_bounded_array<void (*)() noexcept>();

    test_is_not_bounded_array<void (*)(int)>();
    test_is_not_bounded_array<void (*)(int) noexcept>();

    test_is_not_bounded_array<void (*)(...)>();
    test_is_not_bounded_array<void (*)(...) noexcept>();

    test_is_not_bounded_array<void (*)(int, ...)>();
    test_is_not_bounded_array<void (*)(int, ...) noexcept>();

    test_is_not_bounded_array<int (*)()>();
    test_is_not_bounded_array<int (*)() noexcept>();

    test_is_not_bounded_array<int (*)(int)>();
    test_is_not_bounded_array<int (*)(int) noexcept>();

    test_is_not_bounded_array<int (*)(...)>();
    test_is_not_bounded_array<int (*)(...) noexcept>();

    test_is_not_bounded_array<int (*)(int, ...)>();
    test_is_not_bounded_array<int (*)(int, ...) noexcept>();

    test_is_not_bounded_array<void (&)()>();
    test_is_not_bounded_array<void (&)() noexcept>();

    test_is_not_bounded_array<void (&)(int)>();
    test_is_not_bounded_array<void (&)(int) noexcept>();

    test_is_not_bounded_array<void (&)(...)>();
    test_is_not_bounded_array<void (&)(...) noexcept>();

    test_is_not_bounded_array<void (&)(int, ...)>();
    test_is_not_bounded_array<void (&)(int, ...) noexcept>();

    test_is_not_bounded_array<int (&)()>();
    test_is_not_bounded_array<int (&)() noexcept>();

    test_is_not_bounded_array<int (&)(int)>();
    test_is_not_bounded_array<int (&)(int) noexcept>();

    test_is_not_bounded_array<int (&)(...)>();
    test_is_not_bounded_array<int (&)(...) noexcept>();

    test_is_not_bounded_array<int (&)(int, ...)>();
    test_is_not_bounded_array<int (&)(int, ...) noexcept>();

    test_is_not_bounded_array<void (&&)()>();
    test_is_not_bounded_array<void (&&)() noexcept>();

    test_is_not_bounded_array<void (&&)(int)>();
    test_is_not_bounded_array<void (&&)(int) noexcept>();

    test_is_not_bounded_array<void (&&)(...)>();
    test_is_not_bounded_array<void (&&)(...) noexcept>();

    test_is_not_bounded_array<void (&&)(int, ...)>();
    test_is_not_bounded_array<void (&&)(int, ...) noexcept>();

    test_is_not_bounded_array<int (&&)()>();
    test_is_not_bounded_array<int (&&)() noexcept>();

    test_is_not_bounded_array<int (&&)(int)>();
    test_is_not_bounded_array<int (&&)(int) noexcept>();

    test_is_not_bounded_array<int (&&)(...)>();
    test_is_not_bounded_array<int (&&)(...) noexcept>();

    test_is_not_bounded_array<int (&&)(int, ...)>();
    test_is_not_bounded_array<int (&&)(int, ...) noexcept>();

    test_is_not_bounded_array<void (class_type::*)()>();
    test_is_not_bounded_array<void (class_type::*)()&>();
    test_is_not_bounded_array<void (class_type::*)() &&>();
    test_is_not_bounded_array<void (class_type::*)() const>();
    test_is_not_bounded_array<void (class_type::*)() const&>();
    test_is_not_bounded_array<void (class_type::*)() const&&>();
    test_is_not_bounded_array<void (class_type::*)() noexcept>();
    test_is_not_bounded_array<void (class_type::*)() & noexcept>();
    test_is_not_bounded_array<void (class_type::*)() && noexcept>();
    test_is_not_bounded_array<void (class_type::*)() const noexcept>();
    test_is_not_bounded_array<void (class_type::*)() const & noexcept>();
    test_is_not_bounded_array<void (class_type::*)() const && noexcept>();

    test_is_not_bounded_array<void (class_type::*)(int)>();
    test_is_not_bounded_array<void (class_type::*)(int)&>();
    test_is_not_bounded_array<void (class_type::*)(int) &&>();
    test_is_not_bounded_array<void (class_type::*)(int) const>();
    test_is_not_bounded_array<void (class_type::*)(int) const&>();
    test_is_not_bounded_array<void (class_type::*)(int) const&&>();
    test_is_not_bounded_array<void (class_type::*)(int) noexcept>();
    test_is_not_bounded_array<void (class_type::*)(int) & noexcept>();
    test_is_not_bounded_array<void (class_type::*)(int) && noexcept>();
    test_is_not_bounded_array<void (class_type::*)(int) const noexcept>();
    test_is_not_bounded_array<void (class_type::*)(int) const & noexcept>();
    test_is_not_bounded_array<void (class_type::*)(int) const && noexcept>();

    test_is_not_bounded_array<void (class_type::*)(...)>();
    test_is_not_bounded_array<void (class_type::*)(...)&>();
    test_is_not_bounded_array<void (class_type::*)(...) &&>();
    test_is_not_bounded_array<void (class_type::*)(...) const>();
    test_is_not_bounded_array<void (class_type::*)(...) const&>();
    test_is_not_bounded_array<void (class_type::*)(...) const&&>();
    test_is_not_bounded_array<void (class_type::*)(...) noexcept>();
    test_is_not_bounded_array<void (class_type::*)(...) & noexcept>();
    test_is_not_bounded_array<void (class_type::*)(...) && noexcept>();
    test_is_not_bounded_array<void (class_type::*)(...) const noexcept>();
    test_is_not_bounded_array<void (class_type::*)(...) const & noexcept>();
    test_is_not_bounded_array<void (class_type::*)(...) const && noexcept>();

    test_is_not_bounded_array<void (class_type::*)(int, ...)>();
    test_is_not_bounded_array<void (class_type::*)(int, ...)&>();
    test_is_not_bounded_array<void (class_type::*)(int, ...) &&>();
    test_is_not_bounded_array<void (class_type::*)(int, ...) const>();
    test_is_not_bounded_array<void (class_type::*)(int, ...) const&>();
    test_is_not_bounded_array<void (class_type::*)(int, ...) const&&>();
    test_is_not_bounded_array<void (class_type::*)(int, ...) noexcept>();
    test_is_not_bounded_array<void (class_type::*)(int, ...) & noexcept>();
    test_is_not_bounded_array<void (class_type::*)(int, ...) && noexcept>();
    test_is_not_bounded_array<void (class_type::*)(int, ...) const noexcept>();
    test_is_not_bounded_array<void (class_type::*)(int, ...) const & noexcept>();
    test_is_not_bounded_array<void (class_type::*)(int, ...) const && noexcept>();

    test_is_not_bounded_array<int (class_type::*)()>();
    test_is_not_bounded_array<int (class_type::*)()&>();
    test_is_not_bounded_array<int (class_type::*)() &&>();
    test_is_not_bounded_array<int (class_type::*)() const>();
    test_is_not_bounded_array<int (class_type::*)() const&>();
    test_is_not_bounded_array<int (class_type::*)() const&&>();
    test_is_not_bounded_array<int (class_type::*)() noexcept>();
    test_is_not_bounded_array<int (class_type::*)() & noexcept>();
    test_is_not_bounded_array<int (class_type::*)() && noexcept>();
    test_is_not_bounded_array<int (class_type::*)() const noexcept>();
    test_is_not_bounded_array<int (class_type::*)() const & noexcept>();
    test_is_not_bounded_array<int (class_type::*)() const && noexcept>();

    test_is_not_bounded_array<int (class_type::*)(int)>();
    test_is_not_bounded_array<int (class_type::*)(int)&>();
    test_is_not_bounded_array<int (class_type::*)(int) &&>();
    test_is_not_bounded_array<int (class_type::*)(int) const>();
    test_is_not_bounded_array<int (class_type::*)(int) const&>();
    test_is_not_bounded_array<int (class_type::*)(int) const&&>();
    test_is_not_bounded_array<int (class_type::*)(int) noexcept>();
    test_is_not_bounded_array<int (class_type::*)(int) & noexcept>();
    test_is_not_bounded_array<int (class_type::*)(int) && noexcept>();
    test_is_not_bounded_array<int (class_type::*)(int) const noexcept>();
    test_is_not_bounded_array<int (class_type::*)(int) const & noexcept>();
    test_is_not_bounded_array<int (class_type::*)(int) const && noexcept>();

    test_is_not_bounded_array<int (class_type::*)(...)>();
    test_is_not_bounded_array<int (class_type::*)(...)&>();
    test_is_not_bounded_array<int (class_type::*)(...) &&>();
    test_is_not_bounded_array<int (class_type::*)(...) const>();
    test_is_not_bounded_array<int (class_type::*)(...) const&>();
    test_is_not_bounded_array<int (class_type::*)(...) const&&>();
    test_is_not_bounded_array<int (class_type::*)(...) noexcept>();
    test_is_not_bounded_array<int (class_type::*)(...) & noexcept>();
    test_is_not_bounded_array<int (class_type::*)(...) && noexcept>();
    test_is_not_bounded_array<int (class_type::*)(...) const noexcept>();
    test_is_not_bounded_array<int (class_type::*)(...) const & noexcept>();
    test_is_not_bounded_array<int (class_type::*)(...) const && noexcept>();

    test_is_not_bounded_array<int (class_type::*)(int, ...)>();
    test_is_not_bounded_array<int (class_type::*)(int, ...)&>();
    test_is_not_bounded_array<int (class_type::*)(int, ...) &&>();
    test_is_not_bounded_array<int (class_type::*)(int, ...) const>();
    test_is_not_bounded_array<int (class_type::*)(int, ...) const&>();
    test_is_not_bounded_array<int (class_type::*)(int, ...) const&&>();
    test_is_not_bounded_array<int (class_type::*)(int, ...) noexcept>();
    test_is_not_bounded_array<int (class_type::*)(int, ...) & noexcept>();
    test_is_not_bounded_array<int (class_type::*)(int, ...) && noexcept>();
    test_is_not_bounded_array<int (class_type::*)(int, ...) const noexcept>();
    test_is_not_bounded_array<int (class_type::*)(int, ...) const & noexcept>();
    test_is_not_bounded_array<int (class_type::*)(int, ...) const && noexcept>();
}
