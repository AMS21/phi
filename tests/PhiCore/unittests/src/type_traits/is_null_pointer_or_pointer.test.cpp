#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_null_pointer.hpp>
#include <phi/type_traits/is_null_pointer_or_pointer.hpp>
#include <phi/type_traits/is_pointer.hpp>
#include <cstddef> // std::nullptr_t
#include <type_traits>
#include <vector>

template <typename TypeT>
void test_is_null_pointer_or_pointer_impl()
{
    STATIC_REQUIRE(phi::is_null_pointer_or_pointer<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_null_pointer_or_pointer<TypeT>::value);
    STATIC_REQUIRE(phi::is_null_pointer<TypeT>::value || phi::is_pointer<TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_null_pointer_or_pointer_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_not_null_pointer_or_pointer_v<TypeT>);
    STATIC_REQUIRE(phi::is_null_pointer_v<TypeT> || phi::is_pointer_v<TypeT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_null_pointer_or_pointer<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_null_pointer_or_pointer<TypeT>);

    // Standard compatibility
#if PHI_CPP_STANDARD_IS_ATLEAST(14)
    STATIC_REQUIRE((std::is_null_pointer<TypeT>::value || std::is_pointer<TypeT>::value));
#endif
#if PHI_CPP_STANDARD_IS_ATLEAST(17) && PHI_COMPILER_WORKAROUND(GCC, 7, 0, 0)
    STATIC_REQUIRE((std::is_null_pointer_v<TypeT> || std::is_pointer_v<TypeT>));
#endif
}

template <typename TypeT>
void test_is_null_pointer_or_pointer()
{
    test_is_null_pointer_or_pointer_impl<TypeT>();
    test_is_null_pointer_or_pointer_impl<const TypeT>();
    test_is_null_pointer_or_pointer_impl<volatile TypeT>();
    test_is_null_pointer_or_pointer_impl<const volatile TypeT>();
}

template <typename TypeT>
void test_is_not_null_pointer_or_pointer_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_null_pointer_or_pointer<TypeT>::value);
    STATIC_REQUIRE(phi::is_not_null_pointer_or_pointer<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_null_pointer<TypeT>::value || phi::is_pointer<TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_null_pointer_or_pointer_v<TypeT>);
    STATIC_REQUIRE(phi::is_not_null_pointer_or_pointer_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_null_pointer_v<TypeT> || phi::is_pointer_v<TypeT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_null_pointer_or_pointer<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_null_pointer_or_pointer<TypeT>);

    // Standard compatibility
#if PHI_CPP_STANDARD_IS_ATLEAST(14)
    STATIC_REQUIRE_FALSE((std::is_null_pointer<TypeT>::value || std::is_pointer<TypeT>::value));
#endif
#if PHI_CPP_STANDARD_IS_ATLEAST(17) && PHI_COMPILER_WORKAROUND(GCC, 7, 0, 0)
    STATIC_REQUIRE_FALSE((std::is_null_pointer_v<TypeT> || std::is_pointer<TypeT>::value));
#endif
}

template <typename TypeT>
void test_is_not_null_pointer_or_pointer()
{
    test_is_not_null_pointer_or_pointer_impl<TypeT>();
    test_is_not_null_pointer_or_pointer_impl<const TypeT>();
    test_is_not_null_pointer_or_pointer_impl<volatile TypeT>();
    test_is_not_null_pointer_or_pointer_impl<const volatile TypeT>();
}

TEST_CASE("is_null_pointer_or_pointer")
{
    test_is_not_null_pointer_or_pointer<void>();
    test_is_null_pointer_or_pointer<phi::nullptr_t>();
    test_is_null_pointer_or_pointer<std::nullptr_t>();
    test_is_null_pointer_or_pointer<decltype(nullptr)>();
    test_is_not_null_pointer_or_pointer<bool>();
    test_is_not_null_pointer_or_pointer<char>();
    test_is_not_null_pointer_or_pointer<signed char>();
    test_is_not_null_pointer_or_pointer<unsigned char>();
    test_is_not_null_pointer_or_pointer<short>();
    test_is_not_null_pointer_or_pointer<unsigned short>();
    test_is_not_null_pointer_or_pointer<int>();
    test_is_not_null_pointer_or_pointer<unsigned int>();
    test_is_not_null_pointer_or_pointer<long>();
    test_is_not_null_pointer_or_pointer<unsigned long>();
    test_is_not_null_pointer_or_pointer<long long>();
    test_is_not_null_pointer_or_pointer<unsigned long long>();
    test_is_not_null_pointer_or_pointer<float>();
    test_is_not_null_pointer_or_pointer<double>();
    test_is_not_null_pointer_or_pointer<long double>();
    test_is_not_null_pointer_or_pointer<char8_t>();
    test_is_not_null_pointer_or_pointer<char16_t>();
    test_is_not_null_pointer_or_pointer<char32_t>();
    test_is_not_null_pointer_or_pointer<wchar_t>();

    test_is_not_null_pointer_or_pointer<phi::boolean>();
    test_is_not_null_pointer_or_pointer<phi::integer<signed char>>();
    test_is_not_null_pointer_or_pointer<phi::integer<unsigned char>>();
    test_is_not_null_pointer_or_pointer<phi::integer<short>>();
    test_is_not_null_pointer_or_pointer<phi::integer<unsigned short>>();
    test_is_not_null_pointer_or_pointer<phi::integer<int>>();
    test_is_not_null_pointer_or_pointer<phi::integer<unsigned int>>();
    test_is_not_null_pointer_or_pointer<phi::integer<long>>();
    test_is_not_null_pointer_or_pointer<phi::integer<unsigned long>>();
    test_is_not_null_pointer_or_pointer<phi::integer<long long>>();
    test_is_not_null_pointer_or_pointer<phi::integer<unsigned long long>>();
    test_is_not_null_pointer_or_pointer<phi::floating_point<float>>();
    test_is_not_null_pointer_or_pointer<phi::floating_point<double>>();
    test_is_not_null_pointer_or_pointer<phi::floating_point<long double>>();

    test_is_not_null_pointer_or_pointer<std::vector<int>>();
    test_is_not_null_pointer_or_pointer<phi::scope_ptr<int>>();

    test_is_not_null_pointer_or_pointer<int&>();
    test_is_not_null_pointer_or_pointer<const int&>();
    test_is_not_null_pointer_or_pointer<volatile int&>();
    test_is_not_null_pointer_or_pointer<const volatile int&>();
    test_is_not_null_pointer_or_pointer<int&&>();
    test_is_not_null_pointer_or_pointer<const int&&>();
    test_is_not_null_pointer_or_pointer<volatile int&&>();
    test_is_not_null_pointer_or_pointer<const volatile int&&>();
    test_is_null_pointer_or_pointer<int*>();
    test_is_null_pointer_or_pointer<const int*>();
    test_is_null_pointer_or_pointer<volatile int*>();
    test_is_null_pointer_or_pointer<const volatile int*>();
    test_is_null_pointer_or_pointer<int**>();
    test_is_null_pointer_or_pointer<const int**>();
    test_is_null_pointer_or_pointer<volatile int**>();
    test_is_null_pointer_or_pointer<const volatile int**>();
    test_is_not_null_pointer_or_pointer<int*&>();
    test_is_not_null_pointer_or_pointer<const int*&>();
    test_is_not_null_pointer_or_pointer<volatile int*&>();
    test_is_not_null_pointer_or_pointer<const volatile int*&>();
    test_is_not_null_pointer_or_pointer<int*&&>();
    test_is_not_null_pointer_or_pointer<const int*&&>();
    test_is_not_null_pointer_or_pointer<volatile int*&&>();
    test_is_not_null_pointer_or_pointer<const volatile int*&&>();
    test_is_null_pointer_or_pointer<void*>();
    test_is_not_null_pointer_or_pointer<char[3]>();
    test_is_not_null_pointer_or_pointer<char[]>();
    test_is_not_null_pointer_or_pointer<char* [3]>();
    test_is_not_null_pointer_or_pointer<char*[]>();
    test_is_null_pointer_or_pointer<int(*)[3]>();
    test_is_null_pointer_or_pointer<int(*)[]>();
    test_is_not_null_pointer_or_pointer<int(&)[3]>();
    test_is_not_null_pointer_or_pointer<int(&)[]>();
    test_is_not_null_pointer_or_pointer<int(&&)[3]>();
    test_is_not_null_pointer_or_pointer<int(&&)[]>();
    test_is_not_null_pointer_or_pointer<char[3][2]>();
    test_is_not_null_pointer_or_pointer<char[][2]>();
    test_is_not_null_pointer_or_pointer<char* [3][2]>();
    test_is_not_null_pointer_or_pointer<char*[][2]>();
    test_is_null_pointer_or_pointer<int(*)[3][2]>();
    test_is_null_pointer_or_pointer<int(*)[][2]>();
    test_is_not_null_pointer_or_pointer<int(&)[3][2]>();
    test_is_not_null_pointer_or_pointer<int(&)[][2]>();
    test_is_not_null_pointer_or_pointer<int(&&)[3][2]>();
    test_is_not_null_pointer_or_pointer<int(&&)[][2]>();
    test_is_not_null_pointer_or_pointer<class_type>();
    test_is_not_null_pointer_or_pointer<class_type[]>();
    test_is_not_null_pointer_or_pointer<class_type[2]>();
    test_is_not_null_pointer_or_pointer<template_type<void>>();
    test_is_not_null_pointer_or_pointer<template_type<int>>();
    test_is_not_null_pointer_or_pointer<template_type<class_type>>();
    test_is_not_null_pointer_or_pointer<template_type<incomplete_type>>();
    test_is_not_null_pointer_or_pointer<variadic_template<>>();
    test_is_not_null_pointer_or_pointer<variadic_template<void>>();
    test_is_not_null_pointer_or_pointer<variadic_template<int>>();
    test_is_not_null_pointer_or_pointer<variadic_template<class_type>>();
    test_is_not_null_pointer_or_pointer<variadic_template<incomplete_type>>();
    test_is_not_null_pointer_or_pointer<
            variadic_template<int, void, class_type, volatile char[]>>();
    test_is_not_null_pointer_or_pointer<public_derived_from<base>>();
    test_is_not_null_pointer_or_pointer<public_derived_from<derived>>();
    test_is_not_null_pointer_or_pointer<public_derived_from<class_type>>();
    test_is_not_null_pointer_or_pointer<private_derived_from<base>>();
    test_is_not_null_pointer_or_pointer<private_derived_from<derived>>();
    test_is_not_null_pointer_or_pointer<private_derived_from<class_type>>();
    test_is_not_null_pointer_or_pointer<protected_derived_from<base>>();
    test_is_not_null_pointer_or_pointer<protected_derived_from<derived>>();
    test_is_not_null_pointer_or_pointer<protected_derived_from<class_type>>();
    test_is_not_null_pointer_or_pointer<union_type>();
    test_is_not_null_pointer_or_pointer<non_empty_union>();
    test_is_not_null_pointer_or_pointer<empty>();
    test_is_not_null_pointer_or_pointer<not_empty>();
    test_is_not_null_pointer_or_pointer<bit_zero>();
    test_is_not_null_pointer_or_pointer<bit_one>();
    test_is_not_null_pointer_or_pointer<base>();
    test_is_not_null_pointer_or_pointer<derived>();
    test_is_not_null_pointer_or_pointer<abstract>();
    test_is_not_null_pointer_or_pointer<public_abstract>();
    test_is_not_null_pointer_or_pointer<private_abstract>();
    test_is_not_null_pointer_or_pointer<protected_abstract>();
    test_is_not_null_pointer_or_pointer<abstract_template<int>>();
    test_is_not_null_pointer_or_pointer<abstract_template<double>>();
    test_is_not_null_pointer_or_pointer<abstract_template<class_type>>();
    test_is_not_null_pointer_or_pointer<abstract_template<incomplete_type>>();
    test_is_not_null_pointer_or_pointer<final_type>();
    test_is_not_null_pointer_or_pointer<public_destructor>();
    test_is_not_null_pointer_or_pointer<protected_destructor>();
    test_is_not_null_pointer_or_pointer<private_destructor>();
    test_is_not_null_pointer_or_pointer<virtual_public_destructor>();
    test_is_not_null_pointer_or_pointer<virtual_protected_destructor>();
    test_is_not_null_pointer_or_pointer<virtual_private_destructor>();
    test_is_not_null_pointer_or_pointer<pure_public_destructor>();
    test_is_not_null_pointer_or_pointer<pure_protected_destructor>();
    test_is_not_null_pointer_or_pointer<pure_private_destructor>();
    test_is_not_null_pointer_or_pointer<deleted_public_destructor>();
    test_is_not_null_pointer_or_pointer<deleted_protected_destructor>();
    test_is_not_null_pointer_or_pointer<deleted_private_destructor>();
    test_is_not_null_pointer_or_pointer<deleted_virtual_public_destructor>();
    test_is_not_null_pointer_or_pointer<deleted_virtual_protected_destructor>();
    test_is_not_null_pointer_or_pointer<deleted_virtual_private_destructor>();
    test_is_not_null_pointer_or_pointer<final_type>();
    test_is_not_null_pointer_or_pointer<Enum>();
    test_is_not_null_pointer_or_pointer<EnumSigned>();
    test_is_not_null_pointer_or_pointer<EnumUnsigned>();
    test_is_not_null_pointer_or_pointer<EnumClass>();
    test_is_not_null_pointer_or_pointer<EnumStruct>();
    test_is_not_null_pointer_or_pointer<function_type>();
    test_is_null_pointer_or_pointer<function_ptr>();
    test_is_not_null_pointer_or_pointer<member_object_ptr>();
    test_is_not_null_pointer_or_pointer<member_function_ptr>();
    test_is_not_null_pointer_or_pointer<incomplete_type>();
    test_is_not_null_pointer_or_pointer<incomplete_template<void>>();
    test_is_not_null_pointer_or_pointer<incomplete_template<int>>();
    test_is_not_null_pointer_or_pointer<incomplete_template<class_type>>();
    test_is_not_null_pointer_or_pointer<incomplete_template<incomplete_type>>();
    test_is_not_null_pointer_or_pointer<incomplete_variadic_template<>>();
    test_is_not_null_pointer_or_pointer<incomplete_variadic_template<void>>();
    test_is_not_null_pointer_or_pointer<incomplete_variadic_template<int>>();
    test_is_not_null_pointer_or_pointer<incomplete_variadic_template<class_type>>();
    test_is_not_null_pointer_or_pointer<incomplete_variadic_template<incomplete_type>>();
    test_is_not_null_pointer_or_pointer<
            incomplete_variadic_template<int, void, class_type, volatile char[]>>();
    test_is_not_null_pointer_or_pointer<int class_type::*>();
    test_is_not_null_pointer_or_pointer<float class_type::*>();
    test_is_not_null_pointer_or_pointer<void * class_type::*>();
    test_is_not_null_pointer_or_pointer<int * class_type::*>();
    test_is_not_null_pointer_or_pointer<int class_type::*&>();
    test_is_not_null_pointer_or_pointer<float class_type::*&>();
    test_is_not_null_pointer_or_pointer<void * class_type::*&>();
    test_is_not_null_pointer_or_pointer<int * class_type::*&>();
    test_is_not_null_pointer_or_pointer<int class_type::*&&>();
    test_is_not_null_pointer_or_pointer<float class_type::*&&>();
    test_is_not_null_pointer_or_pointer<void * class_type::*&&>();
    test_is_not_null_pointer_or_pointer<int * class_type::*&&>();
    test_is_not_null_pointer_or_pointer<int class_type::* const>();
    test_is_not_null_pointer_or_pointer<float class_type::* const>();
    test_is_not_null_pointer_or_pointer<void * class_type::* const>();
    test_is_not_null_pointer_or_pointer<int class_type::* const&>();
    test_is_not_null_pointer_or_pointer<float class_type::* const&>();
    test_is_not_null_pointer_or_pointer<void * class_type::* const&>();
    test_is_not_null_pointer_or_pointer<int class_type::* const&&>();
    test_is_not_null_pointer_or_pointer<float class_type::* const&&>();
    test_is_not_null_pointer_or_pointer<void * class_type::* const&&>();
    test_is_not_null_pointer_or_pointer<int class_type::* volatile>();
    test_is_not_null_pointer_or_pointer<float class_type::* volatile>();
    test_is_not_null_pointer_or_pointer<void * class_type::* volatile>();
    test_is_not_null_pointer_or_pointer<int class_type::* volatile&>();
    test_is_not_null_pointer_or_pointer<float class_type::* volatile&>();
    test_is_not_null_pointer_or_pointer<void * class_type::* volatile&>();
    test_is_not_null_pointer_or_pointer<int class_type::* volatile&&>();
    test_is_not_null_pointer_or_pointer<float class_type::* volatile&&>();
    test_is_not_null_pointer_or_pointer<void * class_type::* volatile&&>();
    test_is_not_null_pointer_or_pointer<int class_type::* const volatile>();
    test_is_not_null_pointer_or_pointer<float class_type::* const volatile>();
    test_is_not_null_pointer_or_pointer<void * class_type::* const volatile>();
    test_is_not_null_pointer_or_pointer<int class_type::* const volatile&>();
    test_is_not_null_pointer_or_pointer<float class_type::* const volatile&>();
    test_is_not_null_pointer_or_pointer<void * class_type::* const volatile&>();
    test_is_not_null_pointer_or_pointer<int class_type::* const volatile&&>();
    test_is_not_null_pointer_or_pointer<float class_type::* const volatile&&>();
    test_is_not_null_pointer_or_pointer<void * class_type::* const volatile&&>();
    test_is_not_null_pointer_or_pointer<non_copyable>();
    test_is_not_null_pointer_or_pointer<non_moveable>();
    test_is_not_null_pointer_or_pointer<non_constructible>();
    test_is_not_null_pointer_or_pointer<tracked>();
    test_is_not_null_pointer_or_pointer<trap_constructible>();
    test_is_not_null_pointer_or_pointer<trap_implicit_conversion>();
    test_is_not_null_pointer_or_pointer<trap_comma>();
    test_is_not_null_pointer_or_pointer<trap_call>();
    test_is_not_null_pointer_or_pointer<trap_self_assign>();
    test_is_not_null_pointer_or_pointer<trap_deref>();
    test_is_not_null_pointer_or_pointer<trap_array_subscript>();

    test_is_not_null_pointer_or_pointer<void()>();
    test_is_not_null_pointer_or_pointer<void()&>();
    test_is_not_null_pointer_or_pointer<void() &&>();
    test_is_not_null_pointer_or_pointer<void() const>();
    test_is_not_null_pointer_or_pointer<void() const&>();
    test_is_not_null_pointer_or_pointer<void() const&&>();
    test_is_not_null_pointer_or_pointer<void() volatile>();
    test_is_not_null_pointer_or_pointer<void() volatile&>();
    test_is_not_null_pointer_or_pointer<void() volatile&&>();
    test_is_not_null_pointer_or_pointer<void() const volatile>();
    test_is_not_null_pointer_or_pointer<void() const volatile&>();
    test_is_not_null_pointer_or_pointer<void() const volatile&&>();
    test_is_not_null_pointer_or_pointer<void() noexcept>();
    test_is_not_null_pointer_or_pointer<void() & noexcept>();
    test_is_not_null_pointer_or_pointer<void() && noexcept>();
    test_is_not_null_pointer_or_pointer<void() const noexcept>();
    test_is_not_null_pointer_or_pointer<void() const & noexcept>();
    test_is_not_null_pointer_or_pointer<void() const && noexcept>();
    test_is_not_null_pointer_or_pointer<void() volatile noexcept>();
    test_is_not_null_pointer_or_pointer<void() volatile & noexcept>();
    test_is_not_null_pointer_or_pointer<void() volatile && noexcept>();
    test_is_not_null_pointer_or_pointer<void() const volatile noexcept>();
    test_is_not_null_pointer_or_pointer<void() const volatile & noexcept>();
    test_is_not_null_pointer_or_pointer<void() const volatile && noexcept>();

    test_is_not_null_pointer_or_pointer<void(int)>();
    test_is_not_null_pointer_or_pointer<void(int)&>();
    test_is_not_null_pointer_or_pointer<void(int) &&>();
    test_is_not_null_pointer_or_pointer<void(int) const>();
    test_is_not_null_pointer_or_pointer<void(int) const&>();
    test_is_not_null_pointer_or_pointer<void(int) const&&>();
    test_is_not_null_pointer_or_pointer<void(int) volatile>();
    test_is_not_null_pointer_or_pointer<void(int) volatile&>();
    test_is_not_null_pointer_or_pointer<void(int) volatile&&>();
    test_is_not_null_pointer_or_pointer<void(int) const volatile>();
    test_is_not_null_pointer_or_pointer<void(int) const volatile&>();
    test_is_not_null_pointer_or_pointer<void(int) const volatile&&>();
    test_is_not_null_pointer_or_pointer<void(int) noexcept>();
    test_is_not_null_pointer_or_pointer<void(int) & noexcept>();
    test_is_not_null_pointer_or_pointer<void(int) && noexcept>();
    test_is_not_null_pointer_or_pointer<void(int) const noexcept>();
    test_is_not_null_pointer_or_pointer<void(int) const & noexcept>();
    test_is_not_null_pointer_or_pointer<void(int) const && noexcept>();
    test_is_not_null_pointer_or_pointer<void(int) volatile noexcept>();
    test_is_not_null_pointer_or_pointer<void(int) volatile & noexcept>();
    test_is_not_null_pointer_or_pointer<void(int) volatile && noexcept>();
    test_is_not_null_pointer_or_pointer<void(int) const volatile noexcept>();
    test_is_not_null_pointer_or_pointer<void(int) const volatile & noexcept>();
    test_is_not_null_pointer_or_pointer<void(int) const volatile && noexcept>();

    test_is_not_null_pointer_or_pointer<void(...)>();
    test_is_not_null_pointer_or_pointer<void(...)&>();
    test_is_not_null_pointer_or_pointer<void(...) &&>();
    test_is_not_null_pointer_or_pointer<void(...) const>();
    test_is_not_null_pointer_or_pointer<void(...) const&>();
    test_is_not_null_pointer_or_pointer<void(...) const&&>();
    test_is_not_null_pointer_or_pointer<void(...) volatile>();
    test_is_not_null_pointer_or_pointer<void(...) volatile&>();
    test_is_not_null_pointer_or_pointer<void(...) volatile&&>();
    test_is_not_null_pointer_or_pointer<void(...) const volatile>();
    test_is_not_null_pointer_or_pointer<void(...) const volatile&>();
    test_is_not_null_pointer_or_pointer<void(...) const volatile&&>();
    test_is_not_null_pointer_or_pointer<void(...) noexcept>();
    test_is_not_null_pointer_or_pointer<void(...) & noexcept>();
    test_is_not_null_pointer_or_pointer<void(...) && noexcept>();
    test_is_not_null_pointer_or_pointer<void(...) const noexcept>();
    test_is_not_null_pointer_or_pointer<void(...) const & noexcept>();
    test_is_not_null_pointer_or_pointer<void(...) const && noexcept>();
    test_is_not_null_pointer_or_pointer<void(...) volatile noexcept>();
    test_is_not_null_pointer_or_pointer<void(...) volatile & noexcept>();
    test_is_not_null_pointer_or_pointer<void(...) volatile && noexcept>();
    test_is_not_null_pointer_or_pointer<void(...) const volatile noexcept>();
    test_is_not_null_pointer_or_pointer<void(...) const volatile & noexcept>();
    test_is_not_null_pointer_or_pointer<void(...) const volatile && noexcept>();

    test_is_not_null_pointer_or_pointer<void(int, ...)>();
    test_is_not_null_pointer_or_pointer<void(int, ...)&>();
    test_is_not_null_pointer_or_pointer<void(int, ...) &&>();
    test_is_not_null_pointer_or_pointer<void(int, ...) const>();
    test_is_not_null_pointer_or_pointer<void(int, ...) const&>();
    test_is_not_null_pointer_or_pointer<void(int, ...) const&&>();
    test_is_not_null_pointer_or_pointer<void(int, ...) volatile>();
    test_is_not_null_pointer_or_pointer<void(int, ...) volatile&>();
    test_is_not_null_pointer_or_pointer<void(int, ...) volatile&&>();
    test_is_not_null_pointer_or_pointer<void(int, ...) const volatile>();
    test_is_not_null_pointer_or_pointer<void(int, ...) const volatile&>();
    test_is_not_null_pointer_or_pointer<void(int, ...) const volatile&&>();
    test_is_not_null_pointer_or_pointer<void(int, ...) noexcept>();
    test_is_not_null_pointer_or_pointer<void(int, ...) & noexcept>();
    test_is_not_null_pointer_or_pointer<void(int, ...) && noexcept>();
    test_is_not_null_pointer_or_pointer<void(int, ...) const noexcept>();
    test_is_not_null_pointer_or_pointer<void(int, ...) const & noexcept>();
    test_is_not_null_pointer_or_pointer<void(int, ...) const && noexcept>();
    test_is_not_null_pointer_or_pointer<void(int, ...) volatile noexcept>();
    test_is_not_null_pointer_or_pointer<void(int, ...) volatile & noexcept>();
    test_is_not_null_pointer_or_pointer<void(int, ...) volatile && noexcept>();
    test_is_not_null_pointer_or_pointer<void(int, ...) const volatile noexcept>();
    test_is_not_null_pointer_or_pointer<void(int, ...) const volatile & noexcept>();
    test_is_not_null_pointer_or_pointer<void(int, ...) const volatile && noexcept>();

    test_is_not_null_pointer_or_pointer<int()>();
    test_is_not_null_pointer_or_pointer<int()&>();
    test_is_not_null_pointer_or_pointer<int() &&>();
    test_is_not_null_pointer_or_pointer<int() const>();
    test_is_not_null_pointer_or_pointer<int() const&>();
    test_is_not_null_pointer_or_pointer<int() const&&>();
    test_is_not_null_pointer_or_pointer<int() volatile>();
    test_is_not_null_pointer_or_pointer<int() volatile&>();
    test_is_not_null_pointer_or_pointer<int() volatile&&>();
    test_is_not_null_pointer_or_pointer<int() const volatile>();
    test_is_not_null_pointer_or_pointer<int() const volatile&>();
    test_is_not_null_pointer_or_pointer<int() const volatile&&>();
    test_is_not_null_pointer_or_pointer<int() noexcept>();
    test_is_not_null_pointer_or_pointer<int() & noexcept>();
    test_is_not_null_pointer_or_pointer<int() && noexcept>();
    test_is_not_null_pointer_or_pointer<int() const noexcept>();
    test_is_not_null_pointer_or_pointer<int() const & noexcept>();
    test_is_not_null_pointer_or_pointer<int() const && noexcept>();
    test_is_not_null_pointer_or_pointer<int() volatile noexcept>();
    test_is_not_null_pointer_or_pointer<int() volatile & noexcept>();
    test_is_not_null_pointer_or_pointer<int() volatile && noexcept>();
    test_is_not_null_pointer_or_pointer<int() const volatile noexcept>();
    test_is_not_null_pointer_or_pointer<int() const volatile & noexcept>();
    test_is_not_null_pointer_or_pointer<int() const volatile && noexcept>();

    test_is_not_null_pointer_or_pointer<int(int)>();
    test_is_not_null_pointer_or_pointer<int(int)&>();
    test_is_not_null_pointer_or_pointer<int(int) &&>();
    test_is_not_null_pointer_or_pointer<int(int) const>();
    test_is_not_null_pointer_or_pointer<int(int) const&>();
    test_is_not_null_pointer_or_pointer<int(int) const&&>();
    test_is_not_null_pointer_or_pointer<int(int) volatile>();
    test_is_not_null_pointer_or_pointer<int(int) volatile&>();
    test_is_not_null_pointer_or_pointer<int(int) volatile&&>();
    test_is_not_null_pointer_or_pointer<int(int) const volatile>();
    test_is_not_null_pointer_or_pointer<int(int) const volatile&>();
    test_is_not_null_pointer_or_pointer<int(int) const volatile&&>();
    test_is_not_null_pointer_or_pointer<int(int) noexcept>();
    test_is_not_null_pointer_or_pointer<int(int) & noexcept>();
    test_is_not_null_pointer_or_pointer<int(int) && noexcept>();
    test_is_not_null_pointer_or_pointer<int(int) const noexcept>();
    test_is_not_null_pointer_or_pointer<int(int) const & noexcept>();
    test_is_not_null_pointer_or_pointer<int(int) const && noexcept>();
    test_is_not_null_pointer_or_pointer<int(int) volatile noexcept>();
    test_is_not_null_pointer_or_pointer<int(int) volatile & noexcept>();
    test_is_not_null_pointer_or_pointer<int(int) volatile && noexcept>();
    test_is_not_null_pointer_or_pointer<int(int) const volatile noexcept>();
    test_is_not_null_pointer_or_pointer<int(int) const volatile & noexcept>();
    test_is_not_null_pointer_or_pointer<int(int) const volatile && noexcept>();

    test_is_not_null_pointer_or_pointer<int(...)>();
    test_is_not_null_pointer_or_pointer<int(...)&>();
    test_is_not_null_pointer_or_pointer<int(...) &&>();
    test_is_not_null_pointer_or_pointer<int(...) const>();
    test_is_not_null_pointer_or_pointer<int(...) const&>();
    test_is_not_null_pointer_or_pointer<int(...) const&&>();
    test_is_not_null_pointer_or_pointer<int(...) volatile>();
    test_is_not_null_pointer_or_pointer<int(...) volatile&>();
    test_is_not_null_pointer_or_pointer<int(...) volatile&&>();
    test_is_not_null_pointer_or_pointer<int(...) const volatile>();
    test_is_not_null_pointer_or_pointer<int(...) const volatile&>();
    test_is_not_null_pointer_or_pointer<int(...) const volatile&&>();
    test_is_not_null_pointer_or_pointer<int(...) noexcept>();
    test_is_not_null_pointer_or_pointer<int(...) & noexcept>();
    test_is_not_null_pointer_or_pointer<int(...) && noexcept>();
    test_is_not_null_pointer_or_pointer<int(...) const noexcept>();
    test_is_not_null_pointer_or_pointer<int(...) const & noexcept>();
    test_is_not_null_pointer_or_pointer<int(...) const && noexcept>();
    test_is_not_null_pointer_or_pointer<int(...) volatile noexcept>();
    test_is_not_null_pointer_or_pointer<int(...) volatile & noexcept>();
    test_is_not_null_pointer_or_pointer<int(...) volatile && noexcept>();
    test_is_not_null_pointer_or_pointer<int(...) const volatile noexcept>();
    test_is_not_null_pointer_or_pointer<int(...) const volatile & noexcept>();
    test_is_not_null_pointer_or_pointer<int(...) const volatile && noexcept>();

    test_is_not_null_pointer_or_pointer<int(int, ...)>();
    test_is_not_null_pointer_or_pointer<int(int, ...)&>();
    test_is_not_null_pointer_or_pointer<int(int, ...) &&>();
    test_is_not_null_pointer_or_pointer<int(int, ...) const>();
    test_is_not_null_pointer_or_pointer<int(int, ...) const&>();
    test_is_not_null_pointer_or_pointer<int(int, ...) const&&>();
    test_is_not_null_pointer_or_pointer<int(int, ...) volatile>();
    test_is_not_null_pointer_or_pointer<int(int, ...) volatile&>();
    test_is_not_null_pointer_or_pointer<int(int, ...) volatile&&>();
    test_is_not_null_pointer_or_pointer<int(int, ...) const volatile>();
    test_is_not_null_pointer_or_pointer<int(int, ...) const volatile&>();
    test_is_not_null_pointer_or_pointer<int(int, ...) const volatile&&>();
    test_is_not_null_pointer_or_pointer<int(int, ...) noexcept>();
    test_is_not_null_pointer_or_pointer<int(int, ...) & noexcept>();
    test_is_not_null_pointer_or_pointer<int(int, ...) && noexcept>();
    test_is_not_null_pointer_or_pointer<int(int, ...) const noexcept>();
    test_is_not_null_pointer_or_pointer<int(int, ...) const & noexcept>();
    test_is_not_null_pointer_or_pointer<int(int, ...) const && noexcept>();
    test_is_not_null_pointer_or_pointer<int(int, ...) volatile noexcept>();
    test_is_not_null_pointer_or_pointer<int(int, ...) volatile & noexcept>();
    test_is_not_null_pointer_or_pointer<int(int, ...) volatile && noexcept>();
    test_is_not_null_pointer_or_pointer<int(int, ...) const volatile noexcept>();
    test_is_not_null_pointer_or_pointer<int(int, ...) const volatile & noexcept>();
    test_is_not_null_pointer_or_pointer<int(int, ...) const volatile && noexcept>();

    test_is_null_pointer_or_pointer<void (*)()>();
    test_is_null_pointer_or_pointer<void (*)() noexcept>();

    test_is_null_pointer_or_pointer<void (*)(int)>();
    test_is_null_pointer_or_pointer<void (*)(int) noexcept>();

    test_is_null_pointer_or_pointer<void (*)(...)>();
    test_is_null_pointer_or_pointer<void (*)(...) noexcept>();

    test_is_null_pointer_or_pointer<void (*)(int, ...)>();
    test_is_null_pointer_or_pointer<void (*)(int, ...) noexcept>();

    test_is_null_pointer_or_pointer<int (*)()>();
    test_is_null_pointer_or_pointer<int (*)() noexcept>();

    test_is_null_pointer_or_pointer<int (*)(int)>();
    test_is_null_pointer_or_pointer<int (*)(int) noexcept>();

    test_is_null_pointer_or_pointer<int (*)(...)>();
    test_is_null_pointer_or_pointer<int (*)(...) noexcept>();

    test_is_null_pointer_or_pointer<int (*)(int, ...)>();
    test_is_null_pointer_or_pointer<int (*)(int, ...) noexcept>();

    test_is_not_null_pointer_or_pointer<void (&)()>();
    test_is_not_null_pointer_or_pointer<void (&)() noexcept>();

    test_is_not_null_pointer_or_pointer<void (&)(int)>();
    test_is_not_null_pointer_or_pointer<void (&)(int) noexcept>();

    test_is_not_null_pointer_or_pointer<void (&)(...)>();
    test_is_not_null_pointer_or_pointer<void (&)(...) noexcept>();

    test_is_not_null_pointer_or_pointer<void (&)(int, ...)>();
    test_is_not_null_pointer_or_pointer<void (&)(int, ...) noexcept>();

    test_is_not_null_pointer_or_pointer<int (&)()>();
    test_is_not_null_pointer_or_pointer<int (&)() noexcept>();

    test_is_not_null_pointer_or_pointer<int (&)(int)>();
    test_is_not_null_pointer_or_pointer<int (&)(int) noexcept>();

    test_is_not_null_pointer_or_pointer<int (&)(...)>();
    test_is_not_null_pointer_or_pointer<int (&)(...) noexcept>();

    test_is_not_null_pointer_or_pointer<int (&)(int, ...)>();
    test_is_not_null_pointer_or_pointer<int (&)(int, ...) noexcept>();

    test_is_not_null_pointer_or_pointer<void (&&)()>();
    test_is_not_null_pointer_or_pointer<void (&&)() noexcept>();

    test_is_not_null_pointer_or_pointer<void (&&)(int)>();
    test_is_not_null_pointer_or_pointer<void (&&)(int) noexcept>();

    test_is_not_null_pointer_or_pointer<void (&&)(...)>();
    test_is_not_null_pointer_or_pointer<void (&&)(...) noexcept>();

    test_is_not_null_pointer_or_pointer<void (&&)(int, ...)>();
    test_is_not_null_pointer_or_pointer<void (&&)(int, ...) noexcept>();

    test_is_not_null_pointer_or_pointer<int (&&)()>();
    test_is_not_null_pointer_or_pointer<int (&&)() noexcept>();

    test_is_not_null_pointer_or_pointer<int (&&)(int)>();
    test_is_not_null_pointer_or_pointer<int (&&)(int) noexcept>();

    test_is_not_null_pointer_or_pointer<int (&&)(...)>();
    test_is_not_null_pointer_or_pointer<int (&&)(...) noexcept>();

    test_is_not_null_pointer_or_pointer<int (&&)(int, ...)>();
    test_is_not_null_pointer_or_pointer<int (&&)(int, ...) noexcept>();

    test_is_not_null_pointer_or_pointer<void (class_type::*)()>();
    test_is_not_null_pointer_or_pointer<void (class_type::*)()&>();
    test_is_not_null_pointer_or_pointer<void (class_type::*)() &&>();
    test_is_not_null_pointer_or_pointer<void (class_type::*)() const>();
    test_is_not_null_pointer_or_pointer<void (class_type::*)() const&>();
    test_is_not_null_pointer_or_pointer<void (class_type::*)() const&&>();
    test_is_not_null_pointer_or_pointer<void (class_type::*)() noexcept>();
    test_is_not_null_pointer_or_pointer<void (class_type::*)() & noexcept>();
    test_is_not_null_pointer_or_pointer<void (class_type::*)() && noexcept>();
    test_is_not_null_pointer_or_pointer<void (class_type::*)() const noexcept>();
    test_is_not_null_pointer_or_pointer<void (class_type::*)() const & noexcept>();
    test_is_not_null_pointer_or_pointer<void (class_type::*)() const && noexcept>();

    test_is_not_null_pointer_or_pointer<void (class_type::*)(int)>();
    test_is_not_null_pointer_or_pointer<void (class_type::*)(int)&>();
    test_is_not_null_pointer_or_pointer<void (class_type::*)(int) &&>();
    test_is_not_null_pointer_or_pointer<void (class_type::*)(int) const>();
    test_is_not_null_pointer_or_pointer<void (class_type::*)(int) const&>();
    test_is_not_null_pointer_or_pointer<void (class_type::*)(int) const&&>();
    test_is_not_null_pointer_or_pointer<void (class_type::*)(int) noexcept>();
    test_is_not_null_pointer_or_pointer<void (class_type::*)(int) & noexcept>();
    test_is_not_null_pointer_or_pointer<void (class_type::*)(int) && noexcept>();
    test_is_not_null_pointer_or_pointer<void (class_type::*)(int) const noexcept>();
    test_is_not_null_pointer_or_pointer<void (class_type::*)(int) const & noexcept>();
    test_is_not_null_pointer_or_pointer<void (class_type::*)(int) const && noexcept>();

    test_is_not_null_pointer_or_pointer<void (class_type::*)(...)>();
    test_is_not_null_pointer_or_pointer<void (class_type::*)(...)&>();
    test_is_not_null_pointer_or_pointer<void (class_type::*)(...) &&>();
    test_is_not_null_pointer_or_pointer<void (class_type::*)(...) const>();
    test_is_not_null_pointer_or_pointer<void (class_type::*)(...) const&>();
    test_is_not_null_pointer_or_pointer<void (class_type::*)(...) const&&>();
    test_is_not_null_pointer_or_pointer<void (class_type::*)(...) noexcept>();
    test_is_not_null_pointer_or_pointer<void (class_type::*)(...) & noexcept>();
    test_is_not_null_pointer_or_pointer<void (class_type::*)(...) && noexcept>();
    test_is_not_null_pointer_or_pointer<void (class_type::*)(...) const noexcept>();
    test_is_not_null_pointer_or_pointer<void (class_type::*)(...) const & noexcept>();
    test_is_not_null_pointer_or_pointer<void (class_type::*)(...) const && noexcept>();

    test_is_not_null_pointer_or_pointer<void (class_type::*)(int, ...)>();
    test_is_not_null_pointer_or_pointer<void (class_type::*)(int, ...)&>();
    test_is_not_null_pointer_or_pointer<void (class_type::*)(int, ...) &&>();
    test_is_not_null_pointer_or_pointer<void (class_type::*)(int, ...) const>();
    test_is_not_null_pointer_or_pointer<void (class_type::*)(int, ...) const&>();
    test_is_not_null_pointer_or_pointer<void (class_type::*)(int, ...) const&&>();
    test_is_not_null_pointer_or_pointer<void (class_type::*)(int, ...) noexcept>();
    test_is_not_null_pointer_or_pointer<void (class_type::*)(int, ...) & noexcept>();
    test_is_not_null_pointer_or_pointer<void (class_type::*)(int, ...) && noexcept>();
    test_is_not_null_pointer_or_pointer<void (class_type::*)(int, ...) const noexcept>();
    test_is_not_null_pointer_or_pointer<void (class_type::*)(int, ...) const & noexcept>();
    test_is_not_null_pointer_or_pointer<void (class_type::*)(int, ...) const && noexcept>();

    test_is_not_null_pointer_or_pointer<int (class_type::*)()>();
    test_is_not_null_pointer_or_pointer<int (class_type::*)()&>();
    test_is_not_null_pointer_or_pointer<int (class_type::*)() &&>();
    test_is_not_null_pointer_or_pointer<int (class_type::*)() const>();
    test_is_not_null_pointer_or_pointer<int (class_type::*)() const&>();
    test_is_not_null_pointer_or_pointer<int (class_type::*)() const&&>();
    test_is_not_null_pointer_or_pointer<int (class_type::*)() noexcept>();
    test_is_not_null_pointer_or_pointer<int (class_type::*)() & noexcept>();
    test_is_not_null_pointer_or_pointer<int (class_type::*)() && noexcept>();
    test_is_not_null_pointer_or_pointer<int (class_type::*)() const noexcept>();
    test_is_not_null_pointer_or_pointer<int (class_type::*)() const & noexcept>();
    test_is_not_null_pointer_or_pointer<int (class_type::*)() const && noexcept>();

    test_is_not_null_pointer_or_pointer<int (class_type::*)(int)>();
    test_is_not_null_pointer_or_pointer<int (class_type::*)(int)&>();
    test_is_not_null_pointer_or_pointer<int (class_type::*)(int) &&>();
    test_is_not_null_pointer_or_pointer<int (class_type::*)(int) const>();
    test_is_not_null_pointer_or_pointer<int (class_type::*)(int) const&>();
    test_is_not_null_pointer_or_pointer<int (class_type::*)(int) const&&>();
    test_is_not_null_pointer_or_pointer<int (class_type::*)(int) noexcept>();
    test_is_not_null_pointer_or_pointer<int (class_type::*)(int) & noexcept>();
    test_is_not_null_pointer_or_pointer<int (class_type::*)(int) && noexcept>();
    test_is_not_null_pointer_or_pointer<int (class_type::*)(int) const noexcept>();
    test_is_not_null_pointer_or_pointer<int (class_type::*)(int) const & noexcept>();
    test_is_not_null_pointer_or_pointer<int (class_type::*)(int) const && noexcept>();

    test_is_not_null_pointer_or_pointer<int (class_type::*)(...)>();
    test_is_not_null_pointer_or_pointer<int (class_type::*)(...)&>();
    test_is_not_null_pointer_or_pointer<int (class_type::*)(...) &&>();
    test_is_not_null_pointer_or_pointer<int (class_type::*)(...) const>();
    test_is_not_null_pointer_or_pointer<int (class_type::*)(...) const&>();
    test_is_not_null_pointer_or_pointer<int (class_type::*)(...) const&&>();
    test_is_not_null_pointer_or_pointer<int (class_type::*)(...) noexcept>();
    test_is_not_null_pointer_or_pointer<int (class_type::*)(...) & noexcept>();
    test_is_not_null_pointer_or_pointer<int (class_type::*)(...) && noexcept>();
    test_is_not_null_pointer_or_pointer<int (class_type::*)(...) const noexcept>();
    test_is_not_null_pointer_or_pointer<int (class_type::*)(...) const & noexcept>();
    test_is_not_null_pointer_or_pointer<int (class_type::*)(...) const && noexcept>();

    test_is_not_null_pointer_or_pointer<int (class_type::*)(int, ...)>();
    test_is_not_null_pointer_or_pointer<int (class_type::*)(int, ...)&>();
    test_is_not_null_pointer_or_pointer<int (class_type::*)(int, ...) &&>();
    test_is_not_null_pointer_or_pointer<int (class_type::*)(int, ...) const>();
    test_is_not_null_pointer_or_pointer<int (class_type::*)(int, ...) const&>();
    test_is_not_null_pointer_or_pointer<int (class_type::*)(int, ...) const&&>();
    test_is_not_null_pointer_or_pointer<int (class_type::*)(int, ...) noexcept>();
    test_is_not_null_pointer_or_pointer<int (class_type::*)(int, ...) & noexcept>();
    test_is_not_null_pointer_or_pointer<int (class_type::*)(int, ...) && noexcept>();
    test_is_not_null_pointer_or_pointer<int (class_type::*)(int, ...) const noexcept>();
    test_is_not_null_pointer_or_pointer<int (class_type::*)(int, ...) const & noexcept>();
    test_is_not_null_pointer_or_pointer<int (class_type::*)(int, ...) const && noexcept>();
}
