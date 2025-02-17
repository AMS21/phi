#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_safe_floating_point.hpp>
#include <vector>

template <typename TypeT>
void test_is_safe_floating_point_impl()
{
    STATIC_REQUIRE(phi::is_safe_floating_point<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_safe_floating_point<TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_safe_floating_point_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_not_safe_floating_point_v<TypeT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_safe_floating_point<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_safe_floating_point<TypeT>);
}

template <typename TypeT>
void test_is_not_safe_floating_point_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_safe_floating_point<TypeT>::value);
    STATIC_REQUIRE(phi::is_not_safe_floating_point<TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_safe_floating_point_v<TypeT>);
    STATIC_REQUIRE(phi::is_not_safe_floating_point_v<TypeT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_safe_floating_point<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_safe_floating_point<TypeT>);
}

template <typename TypeT>
void test_is_safe_floating_point()
{
    test_is_safe_floating_point_impl<TypeT>();
    test_is_safe_floating_point_impl<const TypeT>();
    test_is_safe_floating_point_impl<volatile TypeT>();
    test_is_safe_floating_point_impl<const volatile TypeT>();
}

template <typename TypeT>
void test_is_not_safe_floating_point()
{
    test_is_not_safe_floating_point_impl<TypeT>();
    test_is_not_safe_floating_point_impl<const TypeT>();
    test_is_not_safe_floating_point_impl<volatile TypeT>();
    test_is_not_safe_floating_point_impl<const volatile TypeT>();
}

TEST_CASE("is_safe_floating_point")
{
// Extended floating point types
#if 0 // TODO:
#    if PHI_HAS_EXTENSION_FLOAT16()
    test_is_not_safe_floating_point<_Float16>();
    test_is_safe_floating_point<phi::floating_point<_Float16>>();
#    endif

#    if PHI_HAS_EXTENSION_FP16()
    test_is_not_safe_floating_point<__fp16>();
    test_is_safe_floating_point<phi::floating_point<__fp16>>();
#    endif

#    if PHI_HAS_EXTENSION_FLOAT128()
    test_is_not_safe_floating_point<__float128>();
    test_is_safe_floating_point<phi::floating_point<__float128>>();
#    endif
#endif

    test_is_not_safe_floating_point<void>();
    test_is_not_safe_floating_point<phi::nullptr_t>();
    test_is_not_safe_floating_point<bool>();
    test_is_not_safe_floating_point<char>();
    test_is_not_safe_floating_point<signed char>();
    test_is_not_safe_floating_point<unsigned char>();
    test_is_not_safe_floating_point<short>();
    test_is_not_safe_floating_point<unsigned short>();
    test_is_not_safe_floating_point<int>();
    test_is_not_safe_floating_point<unsigned int>();
    test_is_not_safe_floating_point<long>();
    test_is_not_safe_floating_point<unsigned long>();
    test_is_not_safe_floating_point<long long>();
    test_is_not_safe_floating_point<unsigned long long>();
    test_is_not_safe_floating_point<float>();
    test_is_not_safe_floating_point<double>();
    test_is_not_safe_floating_point<long double>();
    test_is_not_safe_floating_point<char8_t>();
    test_is_not_safe_floating_point<char16_t>();
    test_is_not_safe_floating_point<char32_t>();
    test_is_not_safe_floating_point<wchar_t>();

    test_is_not_safe_floating_point<phi::boolean>();
    test_is_not_safe_floating_point<phi::integer<signed char>>();
    test_is_not_safe_floating_point<phi::integer<unsigned char>>();
    test_is_not_safe_floating_point<phi::integer<short>>();
    test_is_not_safe_floating_point<phi::integer<unsigned short>>();
    test_is_not_safe_floating_point<phi::integer<int>>();
    test_is_not_safe_floating_point<phi::integer<unsigned int>>();
    test_is_not_safe_floating_point<phi::integer<long>>();
    test_is_not_safe_floating_point<phi::integer<unsigned long>>();
    test_is_not_safe_floating_point<phi::integer<long long>>();
    test_is_not_safe_floating_point<phi::integer<unsigned long long>>();
    test_is_safe_floating_point<phi::floating_point<float>>();
    test_is_safe_floating_point<phi::floating_point<double>>();
    test_is_safe_floating_point<phi::floating_point<long double>>();

    test_is_not_safe_floating_point<std::vector<int>>();
    test_is_not_safe_floating_point<phi::scope_ptr<int>>();

    test_is_not_safe_floating_point<int&>();
    test_is_not_safe_floating_point<const int&>();
    test_is_not_safe_floating_point<volatile int&>();
    test_is_not_safe_floating_point<const volatile int&>();
    test_is_not_safe_floating_point<int&&>();
    test_is_not_safe_floating_point<const int&&>();
    test_is_not_safe_floating_point<volatile int&&>();
    test_is_not_safe_floating_point<const volatile int&&>();
    test_is_not_safe_floating_point<int*>();
    test_is_not_safe_floating_point<const int*>();
    test_is_not_safe_floating_point<volatile int*>();
    test_is_not_safe_floating_point<const volatile int*>();
    test_is_not_safe_floating_point<int**>();
    test_is_not_safe_floating_point<const int**>();
    test_is_not_safe_floating_point<volatile int**>();
    test_is_not_safe_floating_point<const volatile int**>();
    test_is_not_safe_floating_point<int*&>();
    test_is_not_safe_floating_point<const int*&>();
    test_is_not_safe_floating_point<volatile int*&>();
    test_is_not_safe_floating_point<const volatile int*&>();
    test_is_not_safe_floating_point<int*&&>();
    test_is_not_safe_floating_point<const int*&&>();
    test_is_not_safe_floating_point<volatile int*&&>();
    test_is_not_safe_floating_point<const volatile int*&&>();
    test_is_not_safe_floating_point<void*>();
    test_is_not_safe_floating_point<char[3]>();
    test_is_not_safe_floating_point<char[]>();
    test_is_not_safe_floating_point<char* [3]>();
    test_is_not_safe_floating_point<char*[]>();
    test_is_not_safe_floating_point<int(*)[3]>();
    test_is_not_safe_floating_point<int(*)[]>();
    test_is_not_safe_floating_point<int(&)[3]>();
    test_is_not_safe_floating_point<int(&)[]>();
    test_is_not_safe_floating_point<int(&&)[3]>();
    test_is_not_safe_floating_point<int(&&)[]>();
    test_is_not_safe_floating_point<char[3][2]>();
    test_is_not_safe_floating_point<char[][2]>();
    test_is_not_safe_floating_point<char* [3][2]>();
    test_is_not_safe_floating_point<char*[][2]>();
    test_is_not_safe_floating_point<int(*)[3][2]>();
    test_is_not_safe_floating_point<int(*)[][2]>();
    test_is_not_safe_floating_point<int(&)[3][2]>();
    test_is_not_safe_floating_point<int(&)[][2]>();
    test_is_not_safe_floating_point<int(&&)[3][2]>();
    test_is_not_safe_floating_point<int(&&)[][2]>();
    test_is_not_safe_floating_point<class_type>();
    test_is_not_safe_floating_point<class_type[]>();
    test_is_not_safe_floating_point<class_type[2]>();
    test_is_not_safe_floating_point<template_type<void>>();
    test_is_not_safe_floating_point<template_type<int>>();
    test_is_not_safe_floating_point<template_type<class_type>>();
    test_is_not_safe_floating_point<template_type<incomplete_type>>();
    test_is_not_safe_floating_point<variadic_template<>>();
    test_is_not_safe_floating_point<variadic_template<void>>();
    test_is_not_safe_floating_point<variadic_template<int>>();
    test_is_not_safe_floating_point<variadic_template<class_type>>();
    test_is_not_safe_floating_point<variadic_template<incomplete_type>>();
    test_is_not_safe_floating_point<variadic_template<int, void, class_type, volatile char[]>>();
    test_is_not_safe_floating_point<public_derived_from<base>>();
    test_is_not_safe_floating_point<public_derived_from<derived>>();
    test_is_not_safe_floating_point<public_derived_from<class_type>>();
    test_is_not_safe_floating_point<private_derived_from<base>>();
    test_is_not_safe_floating_point<private_derived_from<derived>>();
    test_is_not_safe_floating_point<private_derived_from<class_type>>();
    test_is_not_safe_floating_point<protected_derived_from<base>>();
    test_is_not_safe_floating_point<protected_derived_from<derived>>();
    test_is_not_safe_floating_point<protected_derived_from<class_type>>();
    test_is_not_safe_floating_point<union_type>();
    test_is_not_safe_floating_point<non_empty_union>();
    test_is_not_safe_floating_point<empty>();
    test_is_not_safe_floating_point<not_empty>();
    test_is_not_safe_floating_point<bit_zero>();
    test_is_not_safe_floating_point<bit_one>();
    test_is_not_safe_floating_point<base>();
    test_is_not_safe_floating_point<derived>();
    test_is_not_safe_floating_point<abstract>();
    test_is_not_safe_floating_point<public_abstract>();
    test_is_not_safe_floating_point<private_abstract>();
    test_is_not_safe_floating_point<protected_abstract>();
    test_is_not_safe_floating_point<abstract_template<int>>();
    test_is_not_safe_floating_point<abstract_template<double>>();
    test_is_not_safe_floating_point<abstract_template<class_type>>();
    test_is_not_safe_floating_point<abstract_template<incomplete_type>>();
    test_is_not_safe_floating_point<final_type>();
    test_is_not_safe_floating_point<public_destructor>();
    test_is_not_safe_floating_point<protected_destructor>();
    test_is_not_safe_floating_point<private_destructor>();
    test_is_not_safe_floating_point<virtual_public_destructor>();
    test_is_not_safe_floating_point<virtual_protected_destructor>();
    test_is_not_safe_floating_point<virtual_private_destructor>();
    test_is_not_safe_floating_point<pure_public_destructor>();
    test_is_not_safe_floating_point<pure_protected_destructor>();
    test_is_not_safe_floating_point<pure_private_destructor>();
    test_is_not_safe_floating_point<deleted_public_destructor>();
    test_is_not_safe_floating_point<deleted_protected_destructor>();
    test_is_not_safe_floating_point<deleted_private_destructor>();
    test_is_not_safe_floating_point<deleted_virtual_public_destructor>();
    test_is_not_safe_floating_point<deleted_virtual_protected_destructor>();
    test_is_not_safe_floating_point<deleted_virtual_private_destructor>();
    test_is_not_safe_floating_point<Enum>();
    test_is_not_safe_floating_point<EnumSigned>();
    test_is_not_safe_floating_point<EnumUnsigned>();
    test_is_not_safe_floating_point<EnumClass>();
    test_is_not_safe_floating_point<EnumStruct>();
    test_is_not_safe_floating_point<function_type>();
    test_is_not_safe_floating_point<function_ptr>();
    test_is_not_safe_floating_point<member_object_ptr>();
    test_is_not_safe_floating_point<member_function_ptr>();
    test_is_not_safe_floating_point<incomplete_type>();
    test_is_not_safe_floating_point<incomplete_template<void>>();
    test_is_not_safe_floating_point<incomplete_template<int>>();
    test_is_not_safe_floating_point<incomplete_template<class_type>>();
    test_is_not_safe_floating_point<incomplete_template<incomplete_type>>();
    test_is_not_safe_floating_point<incomplete_variadic_template<>>();
    test_is_not_safe_floating_point<incomplete_variadic_template<void>>();
    test_is_not_safe_floating_point<incomplete_variadic_template<int>>();
    test_is_not_safe_floating_point<incomplete_variadic_template<class_type>>();
    test_is_not_safe_floating_point<incomplete_variadic_template<incomplete_type>>();
    test_is_not_safe_floating_point<
            incomplete_variadic_template<int, void, class_type, volatile char[]>>();
    test_is_not_safe_floating_point<int class_type::*>();
    test_is_not_safe_floating_point<float class_type::*>();
    test_is_not_safe_floating_point<void * class_type::*>();
    test_is_not_safe_floating_point<int * class_type::*>();
    test_is_not_safe_floating_point<int class_type::*&>();
    test_is_not_safe_floating_point<float class_type::*&>();
    test_is_not_safe_floating_point<void * class_type::*&>();
    test_is_not_safe_floating_point<int * class_type::*&>();
    test_is_not_safe_floating_point<int class_type::*&&>();
    test_is_not_safe_floating_point<float class_type::*&&>();
    test_is_not_safe_floating_point<void * class_type::*&&>();
    test_is_not_safe_floating_point<int * class_type::*&&>();
    test_is_not_safe_floating_point<int class_type::* const>();
    test_is_not_safe_floating_point<float class_type::* const>();
    test_is_not_safe_floating_point<void * class_type::* const>();
    test_is_not_safe_floating_point<int class_type::* const&>();
    test_is_not_safe_floating_point<float class_type::* const&>();
    test_is_not_safe_floating_point<void * class_type::* const&>();
    test_is_not_safe_floating_point<int class_type::* const&&>();
    test_is_not_safe_floating_point<float class_type::* const&&>();
    test_is_not_safe_floating_point<void * class_type::* const&&>();
    test_is_not_safe_floating_point<int class_type::* volatile>();
    test_is_not_safe_floating_point<float class_type::* volatile>();
    test_is_not_safe_floating_point<void * class_type::* volatile>();
    test_is_not_safe_floating_point<int class_type::* volatile&>();
    test_is_not_safe_floating_point<float class_type::* volatile&>();
    test_is_not_safe_floating_point<void * class_type::* volatile&>();
    test_is_not_safe_floating_point<int class_type::* volatile&&>();
    test_is_not_safe_floating_point<float class_type::* volatile&&>();
    test_is_not_safe_floating_point<void * class_type::* volatile&&>();
    test_is_not_safe_floating_point<int class_type::* const volatile>();
    test_is_not_safe_floating_point<float class_type::* const volatile>();
    test_is_not_safe_floating_point<void * class_type::* const volatile>();
    test_is_not_safe_floating_point<int class_type::* const volatile&>();
    test_is_not_safe_floating_point<float class_type::* const volatile&>();
    test_is_not_safe_floating_point<void * class_type::* const volatile&>();
    test_is_not_safe_floating_point<int class_type::* const volatile&&>();
    test_is_not_safe_floating_point<float class_type::* const volatile&&>();
    test_is_not_safe_floating_point<void * class_type::* const volatile&&>();
    test_is_not_safe_floating_point<non_copyable>();
    test_is_not_safe_floating_point<non_moveable>();
    test_is_not_safe_floating_point<non_constructible>();
    test_is_not_safe_floating_point<tracked>();
    test_is_not_safe_floating_point<trap_constructible>();
    test_is_not_safe_floating_point<trap_implicit_conversion>();
    test_is_not_safe_floating_point<trap_comma>();
    test_is_not_safe_floating_point<trap_call>();
    test_is_not_safe_floating_point<trap_self_assign>();
    test_is_not_safe_floating_point<trap_deref>();
    test_is_not_safe_floating_point<trap_array_subscript>();

    test_is_not_safe_floating_point<void()>();
    test_is_not_safe_floating_point<void()&>();
    test_is_not_safe_floating_point<void() &&>();
    test_is_not_safe_floating_point<void() const>();
    test_is_not_safe_floating_point<void() const&>();
    test_is_not_safe_floating_point<void() const&&>();
    test_is_not_safe_floating_point<void() volatile>();
    test_is_not_safe_floating_point<void() volatile&>();
    test_is_not_safe_floating_point<void() volatile&&>();
    test_is_not_safe_floating_point<void() const volatile>();
    test_is_not_safe_floating_point<void() const volatile&>();
    test_is_not_safe_floating_point<void() const volatile&&>();
    test_is_not_safe_floating_point<void() noexcept>();
    test_is_not_safe_floating_point<void() & noexcept>();
    test_is_not_safe_floating_point<void() && noexcept>();
    test_is_not_safe_floating_point<void() const noexcept>();
    test_is_not_safe_floating_point<void() const & noexcept>();
    test_is_not_safe_floating_point<void() const && noexcept>();
    test_is_not_safe_floating_point<void() volatile noexcept>();
    test_is_not_safe_floating_point<void() volatile & noexcept>();
    test_is_not_safe_floating_point<void() volatile && noexcept>();
    test_is_not_safe_floating_point<void() const volatile noexcept>();
    test_is_not_safe_floating_point<void() const volatile & noexcept>();
    test_is_not_safe_floating_point<void() const volatile && noexcept>();

    test_is_not_safe_floating_point<void(int)>();
    test_is_not_safe_floating_point<void(int)&>();
    test_is_not_safe_floating_point<void(int) &&>();
    test_is_not_safe_floating_point<void(int) const>();
    test_is_not_safe_floating_point<void(int) const&>();
    test_is_not_safe_floating_point<void(int) const&&>();
    test_is_not_safe_floating_point<void(int) volatile>();
    test_is_not_safe_floating_point<void(int) volatile&>();
    test_is_not_safe_floating_point<void(int) volatile&&>();
    test_is_not_safe_floating_point<void(int) const volatile>();
    test_is_not_safe_floating_point<void(int) const volatile&>();
    test_is_not_safe_floating_point<void(int) const volatile&&>();
    test_is_not_safe_floating_point<void(int) noexcept>();
    test_is_not_safe_floating_point<void(int) & noexcept>();
    test_is_not_safe_floating_point<void(int) && noexcept>();
    test_is_not_safe_floating_point<void(int) const noexcept>();
    test_is_not_safe_floating_point<void(int) const & noexcept>();
    test_is_not_safe_floating_point<void(int) const && noexcept>();
    test_is_not_safe_floating_point<void(int) volatile noexcept>();
    test_is_not_safe_floating_point<void(int) volatile & noexcept>();
    test_is_not_safe_floating_point<void(int) volatile && noexcept>();
    test_is_not_safe_floating_point<void(int) const volatile noexcept>();
    test_is_not_safe_floating_point<void(int) const volatile & noexcept>();
    test_is_not_safe_floating_point<void(int) const volatile && noexcept>();

    test_is_not_safe_floating_point<void(...)>();
    test_is_not_safe_floating_point<void(...)&>();
    test_is_not_safe_floating_point<void(...) &&>();
    test_is_not_safe_floating_point<void(...) const>();
    test_is_not_safe_floating_point<void(...) const&>();
    test_is_not_safe_floating_point<void(...) const&&>();
    test_is_not_safe_floating_point<void(...) volatile>();
    test_is_not_safe_floating_point<void(...) volatile&>();
    test_is_not_safe_floating_point<void(...) volatile&&>();
    test_is_not_safe_floating_point<void(...) const volatile>();
    test_is_not_safe_floating_point<void(...) const volatile&>();
    test_is_not_safe_floating_point<void(...) const volatile&&>();
    test_is_not_safe_floating_point<void(...) noexcept>();
    test_is_not_safe_floating_point<void(...) & noexcept>();
    test_is_not_safe_floating_point<void(...) && noexcept>();
    test_is_not_safe_floating_point<void(...) const noexcept>();
    test_is_not_safe_floating_point<void(...) const & noexcept>();
    test_is_not_safe_floating_point<void(...) const && noexcept>();
    test_is_not_safe_floating_point<void(...) volatile noexcept>();
    test_is_not_safe_floating_point<void(...) volatile & noexcept>();
    test_is_not_safe_floating_point<void(...) volatile && noexcept>();
    test_is_not_safe_floating_point<void(...) const volatile noexcept>();
    test_is_not_safe_floating_point<void(...) const volatile & noexcept>();
    test_is_not_safe_floating_point<void(...) const volatile && noexcept>();

    test_is_not_safe_floating_point<void(int, ...)>();
    test_is_not_safe_floating_point<void(int, ...)&>();
    test_is_not_safe_floating_point<void(int, ...) &&>();
    test_is_not_safe_floating_point<void(int, ...) const>();
    test_is_not_safe_floating_point<void(int, ...) const&>();
    test_is_not_safe_floating_point<void(int, ...) const&&>();
    test_is_not_safe_floating_point<void(int, ...) volatile>();
    test_is_not_safe_floating_point<void(int, ...) volatile&>();
    test_is_not_safe_floating_point<void(int, ...) volatile&&>();
    test_is_not_safe_floating_point<void(int, ...) const volatile>();
    test_is_not_safe_floating_point<void(int, ...) const volatile&>();
    test_is_not_safe_floating_point<void(int, ...) const volatile&&>();
    test_is_not_safe_floating_point<void(int, ...) noexcept>();
    test_is_not_safe_floating_point<void(int, ...) & noexcept>();
    test_is_not_safe_floating_point<void(int, ...) && noexcept>();
    test_is_not_safe_floating_point<void(int, ...) const noexcept>();
    test_is_not_safe_floating_point<void(int, ...) const & noexcept>();
    test_is_not_safe_floating_point<void(int, ...) const && noexcept>();
    test_is_not_safe_floating_point<void(int, ...) volatile noexcept>();
    test_is_not_safe_floating_point<void(int, ...) volatile & noexcept>();
    test_is_not_safe_floating_point<void(int, ...) volatile && noexcept>();
    test_is_not_safe_floating_point<void(int, ...) const volatile noexcept>();
    test_is_not_safe_floating_point<void(int, ...) const volatile & noexcept>();
    test_is_not_safe_floating_point<void(int, ...) const volatile && noexcept>();

    test_is_not_safe_floating_point<int()>();
    test_is_not_safe_floating_point<int()&>();
    test_is_not_safe_floating_point<int() &&>();
    test_is_not_safe_floating_point<int() const>();
    test_is_not_safe_floating_point<int() const&>();
    test_is_not_safe_floating_point<int() const&&>();
    test_is_not_safe_floating_point<int() volatile>();
    test_is_not_safe_floating_point<int() volatile&>();
    test_is_not_safe_floating_point<int() volatile&&>();
    test_is_not_safe_floating_point<int() const volatile>();
    test_is_not_safe_floating_point<int() const volatile&>();
    test_is_not_safe_floating_point<int() const volatile&&>();
    test_is_not_safe_floating_point<int() noexcept>();
    test_is_not_safe_floating_point<int() & noexcept>();
    test_is_not_safe_floating_point<int() && noexcept>();
    test_is_not_safe_floating_point<int() const noexcept>();
    test_is_not_safe_floating_point<int() const & noexcept>();
    test_is_not_safe_floating_point<int() const && noexcept>();
    test_is_not_safe_floating_point<int() volatile noexcept>();
    test_is_not_safe_floating_point<int() volatile & noexcept>();
    test_is_not_safe_floating_point<int() volatile && noexcept>();
    test_is_not_safe_floating_point<int() const volatile noexcept>();
    test_is_not_safe_floating_point<int() const volatile & noexcept>();
    test_is_not_safe_floating_point<int() const volatile && noexcept>();

    test_is_not_safe_floating_point<int(int)>();
    test_is_not_safe_floating_point<int(int)&>();
    test_is_not_safe_floating_point<int(int) &&>();
    test_is_not_safe_floating_point<int(int) const>();
    test_is_not_safe_floating_point<int(int) const&>();
    test_is_not_safe_floating_point<int(int) const&&>();
    test_is_not_safe_floating_point<int(int) volatile>();
    test_is_not_safe_floating_point<int(int) volatile&>();
    test_is_not_safe_floating_point<int(int) volatile&&>();
    test_is_not_safe_floating_point<int(int) const volatile>();
    test_is_not_safe_floating_point<int(int) const volatile&>();
    test_is_not_safe_floating_point<int(int) const volatile&&>();
    test_is_not_safe_floating_point<int(int) noexcept>();
    test_is_not_safe_floating_point<int(int) & noexcept>();
    test_is_not_safe_floating_point<int(int) && noexcept>();
    test_is_not_safe_floating_point<int(int) const noexcept>();
    test_is_not_safe_floating_point<int(int) const & noexcept>();
    test_is_not_safe_floating_point<int(int) const && noexcept>();
    test_is_not_safe_floating_point<int(int) volatile noexcept>();
    test_is_not_safe_floating_point<int(int) volatile & noexcept>();
    test_is_not_safe_floating_point<int(int) volatile && noexcept>();
    test_is_not_safe_floating_point<int(int) const volatile noexcept>();
    test_is_not_safe_floating_point<int(int) const volatile & noexcept>();
    test_is_not_safe_floating_point<int(int) const volatile && noexcept>();

    test_is_not_safe_floating_point<int(...)>();
    test_is_not_safe_floating_point<int(...)&>();
    test_is_not_safe_floating_point<int(...) &&>();
    test_is_not_safe_floating_point<int(...) const>();
    test_is_not_safe_floating_point<int(...) const&>();
    test_is_not_safe_floating_point<int(...) const&&>();
    test_is_not_safe_floating_point<int(...) volatile>();
    test_is_not_safe_floating_point<int(...) volatile&>();
    test_is_not_safe_floating_point<int(...) volatile&&>();
    test_is_not_safe_floating_point<int(...) const volatile>();
    test_is_not_safe_floating_point<int(...) const volatile&>();
    test_is_not_safe_floating_point<int(...) const volatile&&>();
    test_is_not_safe_floating_point<int(...) noexcept>();
    test_is_not_safe_floating_point<int(...) & noexcept>();
    test_is_not_safe_floating_point<int(...) && noexcept>();
    test_is_not_safe_floating_point<int(...) const noexcept>();
    test_is_not_safe_floating_point<int(...) const & noexcept>();
    test_is_not_safe_floating_point<int(...) const && noexcept>();
    test_is_not_safe_floating_point<int(...) volatile noexcept>();
    test_is_not_safe_floating_point<int(...) volatile & noexcept>();
    test_is_not_safe_floating_point<int(...) volatile && noexcept>();
    test_is_not_safe_floating_point<int(...) const volatile noexcept>();
    test_is_not_safe_floating_point<int(...) const volatile & noexcept>();
    test_is_not_safe_floating_point<int(...) const volatile && noexcept>();

    test_is_not_safe_floating_point<int(int, ...)>();
    test_is_not_safe_floating_point<int(int, ...)&>();
    test_is_not_safe_floating_point<int(int, ...) &&>();
    test_is_not_safe_floating_point<int(int, ...) const>();
    test_is_not_safe_floating_point<int(int, ...) const&>();
    test_is_not_safe_floating_point<int(int, ...) const&&>();
    test_is_not_safe_floating_point<int(int, ...) volatile>();
    test_is_not_safe_floating_point<int(int, ...) volatile&>();
    test_is_not_safe_floating_point<int(int, ...) volatile&&>();
    test_is_not_safe_floating_point<int(int, ...) const volatile>();
    test_is_not_safe_floating_point<int(int, ...) const volatile&>();
    test_is_not_safe_floating_point<int(int, ...) const volatile&&>();
    test_is_not_safe_floating_point<int(int, ...) noexcept>();
    test_is_not_safe_floating_point<int(int, ...) & noexcept>();
    test_is_not_safe_floating_point<int(int, ...) && noexcept>();
    test_is_not_safe_floating_point<int(int, ...) const noexcept>();
    test_is_not_safe_floating_point<int(int, ...) const & noexcept>();
    test_is_not_safe_floating_point<int(int, ...) const && noexcept>();
    test_is_not_safe_floating_point<int(int, ...) volatile noexcept>();
    test_is_not_safe_floating_point<int(int, ...) volatile & noexcept>();
    test_is_not_safe_floating_point<int(int, ...) volatile && noexcept>();
    test_is_not_safe_floating_point<int(int, ...) const volatile noexcept>();
    test_is_not_safe_floating_point<int(int, ...) const volatile & noexcept>();
    test_is_not_safe_floating_point<int(int, ...) const volatile && noexcept>();

    test_is_not_safe_floating_point<void (*)()>();
    test_is_not_safe_floating_point<void (*)() noexcept>();

    test_is_not_safe_floating_point<void (*)(int)>();
    test_is_not_safe_floating_point<void (*)(int) noexcept>();

    test_is_not_safe_floating_point<void (*)(...)>();
    test_is_not_safe_floating_point<void (*)(...) noexcept>();

    test_is_not_safe_floating_point<void (*)(int, ...)>();
    test_is_not_safe_floating_point<void (*)(int, ...) noexcept>();

    test_is_not_safe_floating_point<int (*)()>();
    test_is_not_safe_floating_point<int (*)() noexcept>();

    test_is_not_safe_floating_point<int (*)(int)>();
    test_is_not_safe_floating_point<int (*)(int) noexcept>();

    test_is_not_safe_floating_point<int (*)(...)>();
    test_is_not_safe_floating_point<int (*)(...) noexcept>();

    test_is_not_safe_floating_point<int (*)(int, ...)>();
    test_is_not_safe_floating_point<int (*)(int, ...) noexcept>();

    test_is_not_safe_floating_point<void (&)()>();
    test_is_not_safe_floating_point<void (&)() noexcept>();

    test_is_not_safe_floating_point<void (&)(int)>();
    test_is_not_safe_floating_point<void (&)(int) noexcept>();

    test_is_not_safe_floating_point<void (&)(...)>();
    test_is_not_safe_floating_point<void (&)(...) noexcept>();

    test_is_not_safe_floating_point<void (&)(int, ...)>();
    test_is_not_safe_floating_point<void (&)(int, ...) noexcept>();

    test_is_not_safe_floating_point<int (&)()>();
    test_is_not_safe_floating_point<int (&)() noexcept>();

    test_is_not_safe_floating_point<int (&)(int)>();
    test_is_not_safe_floating_point<int (&)(int) noexcept>();

    test_is_not_safe_floating_point<int (&)(...)>();
    test_is_not_safe_floating_point<int (&)(...) noexcept>();

    test_is_not_safe_floating_point<int (&)(int, ...)>();
    test_is_not_safe_floating_point<int (&)(int, ...) noexcept>();

    test_is_not_safe_floating_point<void (&&)()>();
    test_is_not_safe_floating_point<void (&&)() noexcept>();

    test_is_not_safe_floating_point<void (&&)(int)>();
    test_is_not_safe_floating_point<void (&&)(int) noexcept>();

    test_is_not_safe_floating_point<void (&&)(...)>();
    test_is_not_safe_floating_point<void (&&)(...) noexcept>();

    test_is_not_safe_floating_point<void (&&)(int, ...)>();
    test_is_not_safe_floating_point<void (&&)(int, ...) noexcept>();

    test_is_not_safe_floating_point<int (&&)()>();
    test_is_not_safe_floating_point<int (&&)() noexcept>();

    test_is_not_safe_floating_point<int (&&)(int)>();
    test_is_not_safe_floating_point<int (&&)(int) noexcept>();

    test_is_not_safe_floating_point<int (&&)(...)>();
    test_is_not_safe_floating_point<int (&&)(...) noexcept>();

    test_is_not_safe_floating_point<int (&&)(int, ...)>();
    test_is_not_safe_floating_point<int (&&)(int, ...) noexcept>();

    test_is_not_safe_floating_point<void (class_type::*)()>();
    test_is_not_safe_floating_point<void (class_type::*)()&>();
    test_is_not_safe_floating_point<void (class_type::*)() &&>();
    test_is_not_safe_floating_point<void (class_type::*)() const>();
    test_is_not_safe_floating_point<void (class_type::*)() const&>();
    test_is_not_safe_floating_point<void (class_type::*)() const&&>();
    test_is_not_safe_floating_point<void (class_type::*)() noexcept>();
    test_is_not_safe_floating_point<void (class_type::*)() & noexcept>();
    test_is_not_safe_floating_point<void (class_type::*)() && noexcept>();
    test_is_not_safe_floating_point<void (class_type::*)() const noexcept>();
    test_is_not_safe_floating_point<void (class_type::*)() const & noexcept>();
    test_is_not_safe_floating_point<void (class_type::*)() const && noexcept>();

    test_is_not_safe_floating_point<void (class_type::*)(int)>();
    test_is_not_safe_floating_point<void (class_type::*)(int)&>();
    test_is_not_safe_floating_point<void (class_type::*)(int) &&>();
    test_is_not_safe_floating_point<void (class_type::*)(int) const>();
    test_is_not_safe_floating_point<void (class_type::*)(int) const&>();
    test_is_not_safe_floating_point<void (class_type::*)(int) const&&>();
    test_is_not_safe_floating_point<void (class_type::*)(int) noexcept>();
    test_is_not_safe_floating_point<void (class_type::*)(int) & noexcept>();
    test_is_not_safe_floating_point<void (class_type::*)(int) && noexcept>();
    test_is_not_safe_floating_point<void (class_type::*)(int) const noexcept>();
    test_is_not_safe_floating_point<void (class_type::*)(int) const & noexcept>();
    test_is_not_safe_floating_point<void (class_type::*)(int) const && noexcept>();

    test_is_not_safe_floating_point<void (class_type::*)(...)>();
    test_is_not_safe_floating_point<void (class_type::*)(...)&>();
    test_is_not_safe_floating_point<void (class_type::*)(...) &&>();
    test_is_not_safe_floating_point<void (class_type::*)(...) const>();
    test_is_not_safe_floating_point<void (class_type::*)(...) const&>();
    test_is_not_safe_floating_point<void (class_type::*)(...) const&&>();
    test_is_not_safe_floating_point<void (class_type::*)(...) noexcept>();
    test_is_not_safe_floating_point<void (class_type::*)(...) & noexcept>();
    test_is_not_safe_floating_point<void (class_type::*)(...) && noexcept>();
    test_is_not_safe_floating_point<void (class_type::*)(...) const noexcept>();
    test_is_not_safe_floating_point<void (class_type::*)(...) const & noexcept>();
    test_is_not_safe_floating_point<void (class_type::*)(...) const && noexcept>();

    test_is_not_safe_floating_point<void (class_type::*)(int, ...)>();
    test_is_not_safe_floating_point<void (class_type::*)(int, ...)&>();
    test_is_not_safe_floating_point<void (class_type::*)(int, ...) &&>();
    test_is_not_safe_floating_point<void (class_type::*)(int, ...) const>();
    test_is_not_safe_floating_point<void (class_type::*)(int, ...) const&>();
    test_is_not_safe_floating_point<void (class_type::*)(int, ...) const&&>();
    test_is_not_safe_floating_point<void (class_type::*)(int, ...) noexcept>();
    test_is_not_safe_floating_point<void (class_type::*)(int, ...) & noexcept>();
    test_is_not_safe_floating_point<void (class_type::*)(int, ...) && noexcept>();
    test_is_not_safe_floating_point<void (class_type::*)(int, ...) const noexcept>();
    test_is_not_safe_floating_point<void (class_type::*)(int, ...) const & noexcept>();
    test_is_not_safe_floating_point<void (class_type::*)(int, ...) const && noexcept>();

    test_is_not_safe_floating_point<int (class_type::*)()>();
    test_is_not_safe_floating_point<int (class_type::*)()&>();
    test_is_not_safe_floating_point<int (class_type::*)() &&>();
    test_is_not_safe_floating_point<int (class_type::*)() const>();
    test_is_not_safe_floating_point<int (class_type::*)() const&>();
    test_is_not_safe_floating_point<int (class_type::*)() const&&>();
    test_is_not_safe_floating_point<int (class_type::*)() noexcept>();
    test_is_not_safe_floating_point<int (class_type::*)() & noexcept>();
    test_is_not_safe_floating_point<int (class_type::*)() && noexcept>();
    test_is_not_safe_floating_point<int (class_type::*)() const noexcept>();
    test_is_not_safe_floating_point<int (class_type::*)() const & noexcept>();
    test_is_not_safe_floating_point<int (class_type::*)() const && noexcept>();

    test_is_not_safe_floating_point<int (class_type::*)(int)>();
    test_is_not_safe_floating_point<int (class_type::*)(int)&>();
    test_is_not_safe_floating_point<int (class_type::*)(int) &&>();
    test_is_not_safe_floating_point<int (class_type::*)(int) const>();
    test_is_not_safe_floating_point<int (class_type::*)(int) const&>();
    test_is_not_safe_floating_point<int (class_type::*)(int) const&&>();
    test_is_not_safe_floating_point<int (class_type::*)(int) noexcept>();
    test_is_not_safe_floating_point<int (class_type::*)(int) & noexcept>();
    test_is_not_safe_floating_point<int (class_type::*)(int) && noexcept>();
    test_is_not_safe_floating_point<int (class_type::*)(int) const noexcept>();
    test_is_not_safe_floating_point<int (class_type::*)(int) const & noexcept>();
    test_is_not_safe_floating_point<int (class_type::*)(int) const && noexcept>();

    test_is_not_safe_floating_point<int (class_type::*)(...)>();
    test_is_not_safe_floating_point<int (class_type::*)(...)&>();
    test_is_not_safe_floating_point<int (class_type::*)(...) &&>();
    test_is_not_safe_floating_point<int (class_type::*)(...) const>();
    test_is_not_safe_floating_point<int (class_type::*)(...) const&>();
    test_is_not_safe_floating_point<int (class_type::*)(...) const&&>();
    test_is_not_safe_floating_point<int (class_type::*)(...) noexcept>();
    test_is_not_safe_floating_point<int (class_type::*)(...) & noexcept>();
    test_is_not_safe_floating_point<int (class_type::*)(...) && noexcept>();
    test_is_not_safe_floating_point<int (class_type::*)(...) const noexcept>();
    test_is_not_safe_floating_point<int (class_type::*)(...) const & noexcept>();
    test_is_not_safe_floating_point<int (class_type::*)(...) const && noexcept>();

    test_is_not_safe_floating_point<int (class_type::*)(int, ...)>();
    test_is_not_safe_floating_point<int (class_type::*)(int, ...)&>();
    test_is_not_safe_floating_point<int (class_type::*)(int, ...) &&>();
    test_is_not_safe_floating_point<int (class_type::*)(int, ...) const>();
    test_is_not_safe_floating_point<int (class_type::*)(int, ...) const&>();
    test_is_not_safe_floating_point<int (class_type::*)(int, ...) const&&>();
    test_is_not_safe_floating_point<int (class_type::*)(int, ...) noexcept>();
    test_is_not_safe_floating_point<int (class_type::*)(int, ...) & noexcept>();
    test_is_not_safe_floating_point<int (class_type::*)(int, ...) && noexcept>();
    test_is_not_safe_floating_point<int (class_type::*)(int, ...) const noexcept>();
    test_is_not_safe_floating_point<int (class_type::*)(int, ...) const & noexcept>();
    test_is_not_safe_floating_point<int (class_type::*)(int, ...) const && noexcept>();
}
