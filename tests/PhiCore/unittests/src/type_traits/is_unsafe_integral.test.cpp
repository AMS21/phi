#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_arithmetic.hpp>
#include <phi/type_traits/is_array.hpp>
#include <phi/type_traits/is_bool.hpp>
#include <phi/type_traits/is_class.hpp>
#include <phi/type_traits/is_compound.hpp>
#include <phi/type_traits/is_enum.hpp>
#include <phi/type_traits/is_function.hpp>
#include <phi/type_traits/is_fundamental.hpp>
#include <phi/type_traits/is_integer.hpp>
#include <phi/type_traits/is_lvalue_reference.hpp>
#include <phi/type_traits/is_member_function_pointer.hpp>
#include <phi/type_traits/is_member_object_pointer.hpp>
#include <phi/type_traits/is_member_pointer.hpp>
#include <phi/type_traits/is_null_pointer.hpp>
#include <phi/type_traits/is_object.hpp>
#include <phi/type_traits/is_pointer.hpp>
#include <phi/type_traits/is_reference.hpp>
#include <phi/type_traits/is_rvalue_reference.hpp>
#include <phi/type_traits/is_scalar.hpp>
#include <phi/type_traits/is_union.hpp>
#include <phi/type_traits/is_unsafe_floating_point.hpp>
#include <phi/type_traits/is_unsafe_integral.hpp>
#include <phi/type_traits/is_unsafe_scalar.hpp>
#include <phi/type_traits/is_void.hpp>
#include <type_traits>
#include <vector>

template <typename TypeT>
void test_is_unsafe_integral_impl()
{
    STATIC_REQUIRE(phi::is_unsafe_arithmetic<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_array<TypeT>::value);
#if PHI_HAS_WORKING_IS_CLASS()
    STATIC_REQUIRE_FALSE(phi::is_class<TypeT>::value);
#endif
    STATIC_REQUIRE_FALSE(phi::is_compound<TypeT>::value);
#if PHI_HAS_WORKING_IS_ENUM()
    STATIC_REQUIRE_FALSE(phi::is_enum<TypeT>::value);
#endif
    STATIC_REQUIRE_FALSE(phi::is_unsafe_floating_point<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_function<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_lvalue_reference<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_member_function_pointer<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_member_object_pointer<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_member_pointer<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_null_pointer<TypeT>::value);
#if PHI_HAS_WORKING_IS_OBJECT()
    STATIC_REQUIRE(phi::is_object<TypeT>::value);
#endif
    STATIC_REQUIRE_FALSE(phi::is_pointer<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_reference<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_rvalue_reference<TypeT>::value);
#if PHI_HAS_WORKING_IS_UNSAFE_SCALAR()
    STATIC_REQUIRE(phi::is_unsafe_scalar<TypeT>::value);
#endif
#if PHI_HAS_WORKING_IS_UNION()
    STATIC_REQUIRE_FALSE(phi::is_union<TypeT>::value);
#endif
    STATIC_REQUIRE_FALSE(phi::is_void<TypeT>::value);

    STATIC_REQUIRE(phi::is_unsafe_integral<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_unsafe_integral<TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_unsafe_arithmetic_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_array_v<TypeT>);
#    if PHI_HAS_WORKING_IS_CLASS()
    STATIC_REQUIRE_FALSE(phi::is_class_v<TypeT>);
#    endif
    STATIC_REQUIRE_FALSE(phi::is_compound_v<TypeT>);
#    if PHI_HAS_WORKING_IS_ENUM()
    STATIC_REQUIRE_FALSE(phi::is_enum_v<TypeT>);
#    endif
    STATIC_REQUIRE_FALSE(phi::is_unsafe_floating_point_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_function_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_lvalue_reference_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_member_function_pointer_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_member_object_pointer_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_member_pointer_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_null_pointer_v<TypeT>);
#    if PHI_HAS_WORKING_IS_OBJECT()
    STATIC_REQUIRE(phi::is_object_v<TypeT>);
#    endif
    STATIC_REQUIRE_FALSE(phi::is_pointer_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_reference_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_rvalue_reference_v<TypeT>);
#    if PHI_HAS_WORKING_IS_UNSAFE_SCALAR()
    STATIC_REQUIRE(phi::is_unsafe_scalar_v<TypeT>);
#    endif
#    if PHI_HAS_WORKING_IS_UNION()
    STATIC_REQUIRE_FALSE(phi::is_union_v<TypeT>);
#    endif
    STATIC_REQUIRE_FALSE(phi::is_void_v<TypeT>);

    STATIC_REQUIRE(phi::is_unsafe_integral_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_not_unsafe_integral_v<TypeT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_unsafe_integral<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_unsafe_integral<TypeT>);

    // Standard compatibility
    STATIC_REQUIRE(std::is_integral<TypeT>::value);
#if PHI_CPP_STANDARD_IS_ATLEAST(17) && PHI_COMPILER_WORKAROUND(GCC, 7, 0, 0)
    STATIC_REQUIRE(std::is_integral_v<TypeT>);
#endif
}

template <typename TypeT>
void test_is_unsafe_integral()
{
    test_is_unsafe_integral_impl<TypeT>();
    test_is_unsafe_integral_impl<const TypeT>();
    test_is_unsafe_integral_impl<volatile TypeT>();
    test_is_unsafe_integral_impl<const volatile TypeT>();
}

template <typename TypeT>
void test_is_not_unsafe_integral_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_unsafe_integral<TypeT>::value);
    STATIC_REQUIRE(phi::is_not_unsafe_integral<TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_unsafe_integral_v<TypeT>);
    STATIC_REQUIRE(phi::is_not_unsafe_integral_v<TypeT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_unsafe_integral<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_unsafe_integral<TypeT>);

    // Standard compatibility
    STATIC_REQUIRE_FALSE(std::is_integral<TypeT>::value);
#if PHI_CPP_STANDARD_IS_ATLEAST(17) && PHI_COMPILER_WORKAROUND(GCC, 7, 0, 0)
    STATIC_REQUIRE_FALSE(std::is_integral_v<TypeT>);
#endif
}

template <typename TypeT>
void test_is_not_unsafe_integral()
{
    test_is_not_unsafe_integral_impl<TypeT>();
    test_is_not_unsafe_integral_impl<const TypeT>();
    test_is_not_unsafe_integral_impl<volatile TypeT>();
    test_is_not_unsafe_integral_impl<const volatile TypeT>();
}

TEST_CASE("is_unsafe_integral")
{
    test_is_not_unsafe_integral<void>();
    test_is_not_unsafe_integral<phi::nullptr_t>();
    test_is_unsafe_integral<bool>();
    test_is_unsafe_integral<char>();
    test_is_unsafe_integral<signed char>();
    test_is_unsafe_integral<unsigned char>();
    test_is_unsafe_integral<short>();
    test_is_unsafe_integral<unsigned short>();
    test_is_unsafe_integral<int>();
    test_is_unsafe_integral<unsigned int>();
    test_is_unsafe_integral<long>();
    test_is_unsafe_integral<unsigned long>();
    test_is_unsafe_integral<long long>();
    test_is_unsafe_integral<unsigned long long>();
    test_is_not_unsafe_integral<float>();
    test_is_not_unsafe_integral<double>();
    test_is_not_unsafe_integral<long double>();
    test_is_unsafe_integral<char8_t>();
    test_is_unsafe_integral<char16_t>();
    test_is_unsafe_integral<char32_t>();
    test_is_unsafe_integral<wchar_t>();

    test_is_not_unsafe_integral<phi::boolean>();
    test_is_not_unsafe_integral<phi::integer<signed char>>();
    test_is_not_unsafe_integral<phi::integer<unsigned char>>();
    test_is_not_unsafe_integral<phi::integer<short>>();
    test_is_not_unsafe_integral<phi::integer<unsigned short>>();
    test_is_not_unsafe_integral<phi::integer<int>>();
    test_is_not_unsafe_integral<phi::integer<unsigned int>>();
    test_is_not_unsafe_integral<phi::integer<long>>();
    test_is_not_unsafe_integral<phi::integer<unsigned long>>();
    test_is_not_unsafe_integral<phi::integer<long long>>();
    test_is_not_unsafe_integral<phi::integer<unsigned long long>>();
    test_is_not_unsafe_integral<phi::floating_point<float>>();
    test_is_not_unsafe_integral<phi::floating_point<double>>();
    test_is_not_unsafe_integral<phi::floating_point<long double>>();

    test_is_not_unsafe_integral<std::vector<int>>();
    test_is_not_unsafe_integral<phi::scope_ptr<int>>();

    test_is_not_unsafe_integral<int&>();
    test_is_not_unsafe_integral<const int&>();
    test_is_not_unsafe_integral<volatile int&>();
    test_is_not_unsafe_integral<const volatile int&>();
    test_is_not_unsafe_integral<int&&>();
    test_is_not_unsafe_integral<const int&&>();
    test_is_not_unsafe_integral<volatile int&&>();
    test_is_not_unsafe_integral<const volatile int&&>();
    test_is_not_unsafe_integral<int*>();
    test_is_not_unsafe_integral<const int*>();
    test_is_not_unsafe_integral<volatile int*>();
    test_is_not_unsafe_integral<const volatile int*>();
    test_is_not_unsafe_integral<int**>();
    test_is_not_unsafe_integral<const int**>();
    test_is_not_unsafe_integral<volatile int**>();
    test_is_not_unsafe_integral<const volatile int**>();
    test_is_not_unsafe_integral<int*&>();
    test_is_not_unsafe_integral<const int*&>();
    test_is_not_unsafe_integral<volatile int*&>();
    test_is_not_unsafe_integral<const volatile int*&>();
    test_is_not_unsafe_integral<int*&&>();
    test_is_not_unsafe_integral<const int*&&>();
    test_is_not_unsafe_integral<volatile int*&&>();
    test_is_not_unsafe_integral<const volatile int*&&>();
    test_is_not_unsafe_integral<void*>();
    test_is_not_unsafe_integral<char[3]>();
    test_is_not_unsafe_integral<char[]>();
    test_is_not_unsafe_integral<char* [3]>();
    test_is_not_unsafe_integral<char*[]>();
    test_is_not_unsafe_integral<int(*)[3]>();
    test_is_not_unsafe_integral<int(*)[]>();
    test_is_not_unsafe_integral<int(&)[3]>();
    test_is_not_unsafe_integral<int(&)[]>();
    test_is_not_unsafe_integral<int(&&)[3]>();
    test_is_not_unsafe_integral<int(&&)[]>();
    test_is_not_unsafe_integral<char[3][2]>();
    test_is_not_unsafe_integral<char[][2]>();
    test_is_not_unsafe_integral<char* [3][2]>();
    test_is_not_unsafe_integral<char*[][2]>();
    test_is_not_unsafe_integral<int(*)[3][2]>();
    test_is_not_unsafe_integral<int(*)[][2]>();
    test_is_not_unsafe_integral<int(&)[3][2]>();
    test_is_not_unsafe_integral<int(&)[][2]>();
    test_is_not_unsafe_integral<int(&&)[3][2]>();
    test_is_not_unsafe_integral<int(&&)[][2]>();
    test_is_not_unsafe_integral<class_type>();
    test_is_not_unsafe_integral<class_type[]>();
    test_is_not_unsafe_integral<class_type[2]>();
    test_is_not_unsafe_integral<template_type<void>>();
    test_is_not_unsafe_integral<template_type<int>>();
    test_is_not_unsafe_integral<template_type<class_type>>();
    test_is_not_unsafe_integral<template_type<incomplete_type>>();
    test_is_not_unsafe_integral<variadic_template<>>();
    test_is_not_unsafe_integral<variadic_template<void>>();
    test_is_not_unsafe_integral<variadic_template<int>>();
    test_is_not_unsafe_integral<variadic_template<class_type>>();
    test_is_not_unsafe_integral<variadic_template<incomplete_type>>();
    test_is_not_unsafe_integral<variadic_template<int, void, class_type, volatile char[]>>();
    test_is_not_unsafe_integral<public_derived_from<base>>();
    test_is_not_unsafe_integral<public_derived_from<derived>>();
    test_is_not_unsafe_integral<public_derived_from<class_type>>();
    test_is_not_unsafe_integral<private_derived_from<base>>();
    test_is_not_unsafe_integral<private_derived_from<derived>>();
    test_is_not_unsafe_integral<private_derived_from<class_type>>();
    test_is_not_unsafe_integral<protected_derived_from<base>>();
    test_is_not_unsafe_integral<protected_derived_from<derived>>();
    test_is_not_unsafe_integral<protected_derived_from<class_type>>();
    test_is_not_unsafe_integral<union_type>();
    test_is_not_unsafe_integral<non_empty_union>();
    test_is_not_unsafe_integral<empty>();
    test_is_not_unsafe_integral<not_empty>();
    test_is_not_unsafe_integral<bit_zero>();
    test_is_not_unsafe_integral<bit_one>();
    test_is_not_unsafe_integral<base>();
    test_is_not_unsafe_integral<derived>();
    test_is_not_unsafe_integral<abstract>();
    test_is_not_unsafe_integral<public_abstract>();
    test_is_not_unsafe_integral<private_abstract>();
    test_is_not_unsafe_integral<protected_abstract>();
    test_is_not_unsafe_integral<abstract_template<int>>();
    test_is_not_unsafe_integral<abstract_template<double>>();
    test_is_not_unsafe_integral<abstract_template<class_type>>();
    test_is_not_unsafe_integral<abstract_template<incomplete_type>>();
    test_is_not_unsafe_integral<final_type>();
    test_is_not_unsafe_integral<public_destructor>();
    test_is_not_unsafe_integral<protected_destructor>();
    test_is_not_unsafe_integral<private_destructor>();
    test_is_not_unsafe_integral<virtual_public_destructor>();
    test_is_not_unsafe_integral<virtual_protected_destructor>();
    test_is_not_unsafe_integral<virtual_private_destructor>();
    test_is_not_unsafe_integral<pure_public_destructor>();
    test_is_not_unsafe_integral<pure_protected_destructor>();
    test_is_not_unsafe_integral<pure_private_destructor>();
    test_is_not_unsafe_integral<deleted_public_destructor>();
    test_is_not_unsafe_integral<deleted_protected_destructor>();
    test_is_not_unsafe_integral<deleted_private_destructor>();
    test_is_not_unsafe_integral<deleted_virtual_public_destructor>();
    test_is_not_unsafe_integral<deleted_virtual_protected_destructor>();
    test_is_not_unsafe_integral<deleted_virtual_private_destructor>();
    test_is_not_unsafe_integral<final_type>();
    test_is_not_unsafe_integral<Enum>();
    test_is_not_unsafe_integral<EnumSigned>();
    test_is_not_unsafe_integral<EnumUnsigned>();
    test_is_not_unsafe_integral<EnumClass>();
    test_is_not_unsafe_integral<EnumStruct>();
    test_is_not_unsafe_integral<function_type>();
    test_is_not_unsafe_integral<function_ptr>();
    test_is_not_unsafe_integral<member_object_ptr>();
    test_is_not_unsafe_integral<member_function_ptr>();
    test_is_not_unsafe_integral<incomplete_type>();
    test_is_not_unsafe_integral<incomplete_template<void>>();
    test_is_not_unsafe_integral<incomplete_template<int>>();
    test_is_not_unsafe_integral<incomplete_template<class_type>>();
    test_is_not_unsafe_integral<incomplete_template<incomplete_type>>();
    test_is_not_unsafe_integral<incomplete_variadic_template<>>();
    test_is_not_unsafe_integral<incomplete_variadic_template<void>>();
    test_is_not_unsafe_integral<incomplete_variadic_template<int>>();
    test_is_not_unsafe_integral<incomplete_variadic_template<class_type>>();
    test_is_not_unsafe_integral<incomplete_variadic_template<incomplete_type>>();
    test_is_not_unsafe_integral<
            incomplete_variadic_template<int, void, class_type, volatile char[]>>();
    test_is_not_unsafe_integral<int class_type::*>();
    test_is_not_unsafe_integral<float class_type::*>();
    test_is_not_unsafe_integral<void * class_type::*>();
    test_is_not_unsafe_integral<int * class_type::*>();
    test_is_not_unsafe_integral<int class_type::*&>();
    test_is_not_unsafe_integral<float class_type::*&>();
    test_is_not_unsafe_integral<void * class_type::*&>();
    test_is_not_unsafe_integral<int * class_type::*&>();
    test_is_not_unsafe_integral<int class_type::*&&>();
    test_is_not_unsafe_integral<float class_type::*&&>();
    test_is_not_unsafe_integral<void * class_type::*&&>();
    test_is_not_unsafe_integral<int * class_type::*&&>();
    test_is_not_unsafe_integral<int class_type::*const>();
    test_is_not_unsafe_integral<float class_type::*const>();
    test_is_not_unsafe_integral<void * class_type::*const>();
    test_is_not_unsafe_integral<int class_type::*const&>();
    test_is_not_unsafe_integral<float class_type::*const&>();
    test_is_not_unsafe_integral<void * class_type::*const&>();
    test_is_not_unsafe_integral<int class_type::*const&&>();
    test_is_not_unsafe_integral<float class_type::*const&&>();
    test_is_not_unsafe_integral<void * class_type::*const&&>();
    test_is_not_unsafe_integral<int class_type::*volatile>();
    test_is_not_unsafe_integral<float class_type::*volatile>();
    test_is_not_unsafe_integral<void * class_type::*volatile>();
    test_is_not_unsafe_integral<int class_type::*volatile&>();
    test_is_not_unsafe_integral<float class_type::*volatile&>();
    test_is_not_unsafe_integral<void * class_type::*volatile&>();
    test_is_not_unsafe_integral<int class_type::*volatile&&>();
    test_is_not_unsafe_integral<float class_type::*volatile&&>();
    test_is_not_unsafe_integral<void * class_type::*volatile&&>();
    test_is_not_unsafe_integral<int class_type::*const volatile>();
    test_is_not_unsafe_integral<float class_type::*const volatile>();
    test_is_not_unsafe_integral<void * class_type::*const volatile>();
    test_is_not_unsafe_integral<int class_type::*const volatile&>();
    test_is_not_unsafe_integral<float class_type::*const volatile&>();
    test_is_not_unsafe_integral<void * class_type::*const volatile&>();
    test_is_not_unsafe_integral<int class_type::*const volatile&&>();
    test_is_not_unsafe_integral<float class_type::*const volatile&&>();
    test_is_not_unsafe_integral<void * class_type::*const volatile&&>();
    test_is_not_unsafe_integral<non_copyable>();
    test_is_not_unsafe_integral<non_moveable>();
    test_is_not_unsafe_integral<non_constructible>();
    test_is_not_unsafe_integral<tracked>();
    test_is_not_unsafe_integral<trap_constructible>();
    test_is_not_unsafe_integral<trap_implicit_conversion>();
    test_is_not_unsafe_integral<trap_comma>();
    test_is_not_unsafe_integral<trap_call>();
    test_is_not_unsafe_integral<trap_self_assign>();
    test_is_not_unsafe_integral<trap_deref>();
    test_is_not_unsafe_integral<trap_array_subscript>();

    test_is_not_unsafe_integral<void()>();
    test_is_not_unsafe_integral<void()&>();
    test_is_not_unsafe_integral<void() &&>();
    test_is_not_unsafe_integral<void() const>();
    test_is_not_unsafe_integral<void() const&>();
    test_is_not_unsafe_integral<void() const&&>();
    test_is_not_unsafe_integral<void() volatile>();
    test_is_not_unsafe_integral<void() volatile&>();
    test_is_not_unsafe_integral<void() volatile&&>();
    test_is_not_unsafe_integral<void() const volatile>();
    test_is_not_unsafe_integral<void() const volatile&>();
    test_is_not_unsafe_integral<void() const volatile&&>();
    test_is_not_unsafe_integral<void() noexcept>();
    test_is_not_unsafe_integral<void() & noexcept>();
    test_is_not_unsafe_integral<void() && noexcept>();
    test_is_not_unsafe_integral<void() const noexcept>();
    test_is_not_unsafe_integral<void() const & noexcept>();
    test_is_not_unsafe_integral<void() const && noexcept>();
    test_is_not_unsafe_integral<void() volatile noexcept>();
    test_is_not_unsafe_integral<void() volatile & noexcept>();
    test_is_not_unsafe_integral<void() volatile && noexcept>();
    test_is_not_unsafe_integral<void() const volatile noexcept>();
    test_is_not_unsafe_integral<void() const volatile & noexcept>();
    test_is_not_unsafe_integral<void() const volatile && noexcept>();

    test_is_not_unsafe_integral<void(int)>();
    test_is_not_unsafe_integral<void(int)&>();
    test_is_not_unsafe_integral<void(int) &&>();
    test_is_not_unsafe_integral<void(int) const>();
    test_is_not_unsafe_integral<void(int) const&>();
    test_is_not_unsafe_integral<void(int) const&&>();
    test_is_not_unsafe_integral<void(int) volatile>();
    test_is_not_unsafe_integral<void(int) volatile&>();
    test_is_not_unsafe_integral<void(int) volatile&&>();
    test_is_not_unsafe_integral<void(int) const volatile>();
    test_is_not_unsafe_integral<void(int) const volatile&>();
    test_is_not_unsafe_integral<void(int) const volatile&&>();
    test_is_not_unsafe_integral<void(int) noexcept>();
    test_is_not_unsafe_integral<void(int) & noexcept>();
    test_is_not_unsafe_integral<void(int) && noexcept>();
    test_is_not_unsafe_integral<void(int) const noexcept>();
    test_is_not_unsafe_integral<void(int) const & noexcept>();
    test_is_not_unsafe_integral<void(int) const && noexcept>();
    test_is_not_unsafe_integral<void(int) volatile noexcept>();
    test_is_not_unsafe_integral<void(int) volatile & noexcept>();
    test_is_not_unsafe_integral<void(int) volatile && noexcept>();
    test_is_not_unsafe_integral<void(int) const volatile noexcept>();
    test_is_not_unsafe_integral<void(int) const volatile & noexcept>();
    test_is_not_unsafe_integral<void(int) const volatile && noexcept>();

    test_is_not_unsafe_integral<void(...)>();
    test_is_not_unsafe_integral<void(...)&>();
    test_is_not_unsafe_integral<void(...) &&>();
    test_is_not_unsafe_integral<void(...) const>();
    test_is_not_unsafe_integral<void(...) const&>();
    test_is_not_unsafe_integral<void(...) const&&>();
    test_is_not_unsafe_integral<void(...) volatile>();
    test_is_not_unsafe_integral<void(...) volatile&>();
    test_is_not_unsafe_integral<void(...) volatile&&>();
    test_is_not_unsafe_integral<void(...) const volatile>();
    test_is_not_unsafe_integral<void(...) const volatile&>();
    test_is_not_unsafe_integral<void(...) const volatile&&>();
    test_is_not_unsafe_integral<void(...) noexcept>();
    test_is_not_unsafe_integral<void(...) & noexcept>();
    test_is_not_unsafe_integral<void(...) && noexcept>();
    test_is_not_unsafe_integral<void(...) const noexcept>();
    test_is_not_unsafe_integral<void(...) const & noexcept>();
    test_is_not_unsafe_integral<void(...) const && noexcept>();
    test_is_not_unsafe_integral<void(...) volatile noexcept>();
    test_is_not_unsafe_integral<void(...) volatile & noexcept>();
    test_is_not_unsafe_integral<void(...) volatile && noexcept>();
    test_is_not_unsafe_integral<void(...) const volatile noexcept>();
    test_is_not_unsafe_integral<void(...) const volatile & noexcept>();
    test_is_not_unsafe_integral<void(...) const volatile && noexcept>();

    test_is_not_unsafe_integral<void(int, ...)>();
    test_is_not_unsafe_integral<void(int, ...)&>();
    test_is_not_unsafe_integral<void(int, ...) &&>();
    test_is_not_unsafe_integral<void(int, ...) const>();
    test_is_not_unsafe_integral<void(int, ...) const&>();
    test_is_not_unsafe_integral<void(int, ...) const&&>();
    test_is_not_unsafe_integral<void(int, ...) volatile>();
    test_is_not_unsafe_integral<void(int, ...) volatile&>();
    test_is_not_unsafe_integral<void(int, ...) volatile&&>();
    test_is_not_unsafe_integral<void(int, ...) const volatile>();
    test_is_not_unsafe_integral<void(int, ...) const volatile&>();
    test_is_not_unsafe_integral<void(int, ...) const volatile&&>();
    test_is_not_unsafe_integral<void(int, ...) noexcept>();
    test_is_not_unsafe_integral<void(int, ...) & noexcept>();
    test_is_not_unsafe_integral<void(int, ...) && noexcept>();
    test_is_not_unsafe_integral<void(int, ...) const noexcept>();
    test_is_not_unsafe_integral<void(int, ...) const & noexcept>();
    test_is_not_unsafe_integral<void(int, ...) const && noexcept>();
    test_is_not_unsafe_integral<void(int, ...) volatile noexcept>();
    test_is_not_unsafe_integral<void(int, ...) volatile & noexcept>();
    test_is_not_unsafe_integral<void(int, ...) volatile && noexcept>();
    test_is_not_unsafe_integral<void(int, ...) const volatile noexcept>();
    test_is_not_unsafe_integral<void(int, ...) const volatile & noexcept>();
    test_is_not_unsafe_integral<void(int, ...) const volatile && noexcept>();

    test_is_not_unsafe_integral<int()>();
    test_is_not_unsafe_integral<int()&>();
    test_is_not_unsafe_integral<int() &&>();
    test_is_not_unsafe_integral<int() const>();
    test_is_not_unsafe_integral<int() const&>();
    test_is_not_unsafe_integral<int() const&&>();
    test_is_not_unsafe_integral<int() volatile>();
    test_is_not_unsafe_integral<int() volatile&>();
    test_is_not_unsafe_integral<int() volatile&&>();
    test_is_not_unsafe_integral<int() const volatile>();
    test_is_not_unsafe_integral<int() const volatile&>();
    test_is_not_unsafe_integral<int() const volatile&&>();
    test_is_not_unsafe_integral<int() noexcept>();
    test_is_not_unsafe_integral<int() & noexcept>();
    test_is_not_unsafe_integral<int() && noexcept>();
    test_is_not_unsafe_integral<int() const noexcept>();
    test_is_not_unsafe_integral<int() const & noexcept>();
    test_is_not_unsafe_integral<int() const && noexcept>();
    test_is_not_unsafe_integral<int() volatile noexcept>();
    test_is_not_unsafe_integral<int() volatile & noexcept>();
    test_is_not_unsafe_integral<int() volatile && noexcept>();
    test_is_not_unsafe_integral<int() const volatile noexcept>();
    test_is_not_unsafe_integral<int() const volatile & noexcept>();
    test_is_not_unsafe_integral<int() const volatile && noexcept>();

    test_is_not_unsafe_integral<int(int)>();
    test_is_not_unsafe_integral<int(int)&>();
    test_is_not_unsafe_integral<int(int) &&>();
    test_is_not_unsafe_integral<int(int) const>();
    test_is_not_unsafe_integral<int(int) const&>();
    test_is_not_unsafe_integral<int(int) const&&>();
    test_is_not_unsafe_integral<int(int) volatile>();
    test_is_not_unsafe_integral<int(int) volatile&>();
    test_is_not_unsafe_integral<int(int) volatile&&>();
    test_is_not_unsafe_integral<int(int) const volatile>();
    test_is_not_unsafe_integral<int(int) const volatile&>();
    test_is_not_unsafe_integral<int(int) const volatile&&>();
    test_is_not_unsafe_integral<int(int) noexcept>();
    test_is_not_unsafe_integral<int(int) & noexcept>();
    test_is_not_unsafe_integral<int(int) && noexcept>();
    test_is_not_unsafe_integral<int(int) const noexcept>();
    test_is_not_unsafe_integral<int(int) const & noexcept>();
    test_is_not_unsafe_integral<int(int) const && noexcept>();
    test_is_not_unsafe_integral<int(int) volatile noexcept>();
    test_is_not_unsafe_integral<int(int) volatile & noexcept>();
    test_is_not_unsafe_integral<int(int) volatile && noexcept>();
    test_is_not_unsafe_integral<int(int) const volatile noexcept>();
    test_is_not_unsafe_integral<int(int) const volatile & noexcept>();
    test_is_not_unsafe_integral<int(int) const volatile && noexcept>();

    test_is_not_unsafe_integral<int(...)>();
    test_is_not_unsafe_integral<int(...)&>();
    test_is_not_unsafe_integral<int(...) &&>();
    test_is_not_unsafe_integral<int(...) const>();
    test_is_not_unsafe_integral<int(...) const&>();
    test_is_not_unsafe_integral<int(...) const&&>();
    test_is_not_unsafe_integral<int(...) volatile>();
    test_is_not_unsafe_integral<int(...) volatile&>();
    test_is_not_unsafe_integral<int(...) volatile&&>();
    test_is_not_unsafe_integral<int(...) const volatile>();
    test_is_not_unsafe_integral<int(...) const volatile&>();
    test_is_not_unsafe_integral<int(...) const volatile&&>();
    test_is_not_unsafe_integral<int(...) noexcept>();
    test_is_not_unsafe_integral<int(...) & noexcept>();
    test_is_not_unsafe_integral<int(...) && noexcept>();
    test_is_not_unsafe_integral<int(...) const noexcept>();
    test_is_not_unsafe_integral<int(...) const & noexcept>();
    test_is_not_unsafe_integral<int(...) const && noexcept>();
    test_is_not_unsafe_integral<int(...) volatile noexcept>();
    test_is_not_unsafe_integral<int(...) volatile & noexcept>();
    test_is_not_unsafe_integral<int(...) volatile && noexcept>();
    test_is_not_unsafe_integral<int(...) const volatile noexcept>();
    test_is_not_unsafe_integral<int(...) const volatile & noexcept>();
    test_is_not_unsafe_integral<int(...) const volatile && noexcept>();

    test_is_not_unsafe_integral<int(int, ...)>();
    test_is_not_unsafe_integral<int(int, ...)&>();
    test_is_not_unsafe_integral<int(int, ...) &&>();
    test_is_not_unsafe_integral<int(int, ...) const>();
    test_is_not_unsafe_integral<int(int, ...) const&>();
    test_is_not_unsafe_integral<int(int, ...) const&&>();
    test_is_not_unsafe_integral<int(int, ...) volatile>();
    test_is_not_unsafe_integral<int(int, ...) volatile&>();
    test_is_not_unsafe_integral<int(int, ...) volatile&&>();
    test_is_not_unsafe_integral<int(int, ...) const volatile>();
    test_is_not_unsafe_integral<int(int, ...) const volatile&>();
    test_is_not_unsafe_integral<int(int, ...) const volatile&&>();
    test_is_not_unsafe_integral<int(int, ...) noexcept>();
    test_is_not_unsafe_integral<int(int, ...) & noexcept>();
    test_is_not_unsafe_integral<int(int, ...) && noexcept>();
    test_is_not_unsafe_integral<int(int, ...) const noexcept>();
    test_is_not_unsafe_integral<int(int, ...) const & noexcept>();
    test_is_not_unsafe_integral<int(int, ...) const && noexcept>();
    test_is_not_unsafe_integral<int(int, ...) volatile noexcept>();
    test_is_not_unsafe_integral<int(int, ...) volatile & noexcept>();
    test_is_not_unsafe_integral<int(int, ...) volatile && noexcept>();
    test_is_not_unsafe_integral<int(int, ...) const volatile noexcept>();
    test_is_not_unsafe_integral<int(int, ...) const volatile & noexcept>();
    test_is_not_unsafe_integral<int(int, ...) const volatile && noexcept>();

    test_is_not_unsafe_integral<void (*)()>();
    test_is_not_unsafe_integral<void (*)() noexcept>();

    test_is_not_unsafe_integral<void (*)(int)>();
    test_is_not_unsafe_integral<void (*)(int) noexcept>();

    test_is_not_unsafe_integral<void (*)(...)>();
    test_is_not_unsafe_integral<void (*)(...) noexcept>();

    test_is_not_unsafe_integral<void (*)(int, ...)>();
    test_is_not_unsafe_integral<void (*)(int, ...) noexcept>();

    test_is_not_unsafe_integral<int (*)()>();
    test_is_not_unsafe_integral<int (*)() noexcept>();

    test_is_not_unsafe_integral<int (*)(int)>();
    test_is_not_unsafe_integral<int (*)(int) noexcept>();

    test_is_not_unsafe_integral<int (*)(...)>();
    test_is_not_unsafe_integral<int (*)(...) noexcept>();

    test_is_not_unsafe_integral<int (*)(int, ...)>();
    test_is_not_unsafe_integral<int (*)(int, ...) noexcept>();

    test_is_not_unsafe_integral<void (&)()>();
    test_is_not_unsafe_integral<void (&)() noexcept>();

    test_is_not_unsafe_integral<void (&)(int)>();
    test_is_not_unsafe_integral<void (&)(int) noexcept>();

    test_is_not_unsafe_integral<void (&)(...)>();
    test_is_not_unsafe_integral<void (&)(...) noexcept>();

    test_is_not_unsafe_integral<void (&)(int, ...)>();
    test_is_not_unsafe_integral<void (&)(int, ...) noexcept>();

    test_is_not_unsafe_integral<int (&)()>();
    test_is_not_unsafe_integral<int (&)() noexcept>();

    test_is_not_unsafe_integral<int (&)(int)>();
    test_is_not_unsafe_integral<int (&)(int) noexcept>();

    test_is_not_unsafe_integral<int (&)(...)>();
    test_is_not_unsafe_integral<int (&)(...) noexcept>();

    test_is_not_unsafe_integral<int (&)(int, ...)>();
    test_is_not_unsafe_integral<int (&)(int, ...) noexcept>();

    test_is_not_unsafe_integral<void (&&)()>();
    test_is_not_unsafe_integral<void (&&)() noexcept>();

    test_is_not_unsafe_integral<void (&&)(int)>();
    test_is_not_unsafe_integral<void (&&)(int) noexcept>();

    test_is_not_unsafe_integral<void (&&)(...)>();
    test_is_not_unsafe_integral<void (&&)(...) noexcept>();

    test_is_not_unsafe_integral<void (&&)(int, ...)>();
    test_is_not_unsafe_integral<void (&&)(int, ...) noexcept>();

    test_is_not_unsafe_integral<int (&&)()>();
    test_is_not_unsafe_integral<int (&&)() noexcept>();

    test_is_not_unsafe_integral<int (&&)(int)>();
    test_is_not_unsafe_integral<int (&&)(int) noexcept>();

    test_is_not_unsafe_integral<int (&&)(...)>();
    test_is_not_unsafe_integral<int (&&)(...) noexcept>();

    test_is_not_unsafe_integral<int (&&)(int, ...)>();
    test_is_not_unsafe_integral<int (&&)(int, ...) noexcept>();

    test_is_not_unsafe_integral<void (class_type::*)()>();
    test_is_not_unsafe_integral<void (class_type::*)()&>();
    test_is_not_unsafe_integral<void (class_type::*)() &&>();
    test_is_not_unsafe_integral<void (class_type::*)() const>();
    test_is_not_unsafe_integral<void (class_type::*)() const&>();
    test_is_not_unsafe_integral<void (class_type::*)() const&&>();
    test_is_not_unsafe_integral<void (class_type::*)() noexcept>();
    test_is_not_unsafe_integral<void (class_type::*)() & noexcept>();
    test_is_not_unsafe_integral<void (class_type::*)() && noexcept>();
    test_is_not_unsafe_integral<void (class_type::*)() const noexcept>();
    test_is_not_unsafe_integral<void (class_type::*)() const & noexcept>();
    test_is_not_unsafe_integral<void (class_type::*)() const && noexcept>();

    test_is_not_unsafe_integral<void (class_type::*)(int)>();
    test_is_not_unsafe_integral<void (class_type::*)(int)&>();
    test_is_not_unsafe_integral<void (class_type::*)(int) &&>();
    test_is_not_unsafe_integral<void (class_type::*)(int) const>();
    test_is_not_unsafe_integral<void (class_type::*)(int) const&>();
    test_is_not_unsafe_integral<void (class_type::*)(int) const&&>();
    test_is_not_unsafe_integral<void (class_type::*)(int) noexcept>();
    test_is_not_unsafe_integral<void (class_type::*)(int) & noexcept>();
    test_is_not_unsafe_integral<void (class_type::*)(int) && noexcept>();
    test_is_not_unsafe_integral<void (class_type::*)(int) const noexcept>();
    test_is_not_unsafe_integral<void (class_type::*)(int) const & noexcept>();
    test_is_not_unsafe_integral<void (class_type::*)(int) const && noexcept>();

    test_is_not_unsafe_integral<void (class_type::*)(...)>();
    test_is_not_unsafe_integral<void (class_type::*)(...)&>();
    test_is_not_unsafe_integral<void (class_type::*)(...) &&>();
    test_is_not_unsafe_integral<void (class_type::*)(...) const>();
    test_is_not_unsafe_integral<void (class_type::*)(...) const&>();
    test_is_not_unsafe_integral<void (class_type::*)(...) const&&>();
    test_is_not_unsafe_integral<void (class_type::*)(...) noexcept>();
    test_is_not_unsafe_integral<void (class_type::*)(...) & noexcept>();
    test_is_not_unsafe_integral<void (class_type::*)(...) && noexcept>();
    test_is_not_unsafe_integral<void (class_type::*)(...) const noexcept>();
    test_is_not_unsafe_integral<void (class_type::*)(...) const & noexcept>();
    test_is_not_unsafe_integral<void (class_type::*)(...) const && noexcept>();

    test_is_not_unsafe_integral<void (class_type::*)(int, ...)>();
    test_is_not_unsafe_integral<void (class_type::*)(int, ...)&>();
    test_is_not_unsafe_integral<void (class_type::*)(int, ...) &&>();
    test_is_not_unsafe_integral<void (class_type::*)(int, ...) const>();
    test_is_not_unsafe_integral<void (class_type::*)(int, ...) const&>();
    test_is_not_unsafe_integral<void (class_type::*)(int, ...) const&&>();
    test_is_not_unsafe_integral<void (class_type::*)(int, ...) noexcept>();
    test_is_not_unsafe_integral<void (class_type::*)(int, ...) & noexcept>();
    test_is_not_unsafe_integral<void (class_type::*)(int, ...) && noexcept>();
    test_is_not_unsafe_integral<void (class_type::*)(int, ...) const noexcept>();
    test_is_not_unsafe_integral<void (class_type::*)(int, ...) const & noexcept>();
    test_is_not_unsafe_integral<void (class_type::*)(int, ...) const && noexcept>();

    test_is_not_unsafe_integral<int (class_type::*)()>();
    test_is_not_unsafe_integral<int (class_type::*)()&>();
    test_is_not_unsafe_integral<int (class_type::*)() &&>();
    test_is_not_unsafe_integral<int (class_type::*)() const>();
    test_is_not_unsafe_integral<int (class_type::*)() const&>();
    test_is_not_unsafe_integral<int (class_type::*)() const&&>();
    test_is_not_unsafe_integral<int (class_type::*)() noexcept>();
    test_is_not_unsafe_integral<int (class_type::*)() & noexcept>();
    test_is_not_unsafe_integral<int (class_type::*)() && noexcept>();
    test_is_not_unsafe_integral<int (class_type::*)() const noexcept>();
    test_is_not_unsafe_integral<int (class_type::*)() const & noexcept>();
    test_is_not_unsafe_integral<int (class_type::*)() const && noexcept>();

    test_is_not_unsafe_integral<int (class_type::*)(int)>();
    test_is_not_unsafe_integral<int (class_type::*)(int)&>();
    test_is_not_unsafe_integral<int (class_type::*)(int) &&>();
    test_is_not_unsafe_integral<int (class_type::*)(int) const>();
    test_is_not_unsafe_integral<int (class_type::*)(int) const&>();
    test_is_not_unsafe_integral<int (class_type::*)(int) const&&>();
    test_is_not_unsafe_integral<int (class_type::*)(int) noexcept>();
    test_is_not_unsafe_integral<int (class_type::*)(int) & noexcept>();
    test_is_not_unsafe_integral<int (class_type::*)(int) && noexcept>();
    test_is_not_unsafe_integral<int (class_type::*)(int) const noexcept>();
    test_is_not_unsafe_integral<int (class_type::*)(int) const & noexcept>();
    test_is_not_unsafe_integral<int (class_type::*)(int) const && noexcept>();

    test_is_not_unsafe_integral<int (class_type::*)(...)>();
    test_is_not_unsafe_integral<int (class_type::*)(...)&>();
    test_is_not_unsafe_integral<int (class_type::*)(...) &&>();
    test_is_not_unsafe_integral<int (class_type::*)(...) const>();
    test_is_not_unsafe_integral<int (class_type::*)(...) const&>();
    test_is_not_unsafe_integral<int (class_type::*)(...) const&&>();
    test_is_not_unsafe_integral<int (class_type::*)(...) noexcept>();
    test_is_not_unsafe_integral<int (class_type::*)(...) & noexcept>();
    test_is_not_unsafe_integral<int (class_type::*)(...) && noexcept>();
    test_is_not_unsafe_integral<int (class_type::*)(...) const noexcept>();
    test_is_not_unsafe_integral<int (class_type::*)(...) const & noexcept>();
    test_is_not_unsafe_integral<int (class_type::*)(...) const && noexcept>();

    test_is_not_unsafe_integral<int (class_type::*)(int, ...)>();
    test_is_not_unsafe_integral<int (class_type::*)(int, ...)&>();
    test_is_not_unsafe_integral<int (class_type::*)(int, ...) &&>();
    test_is_not_unsafe_integral<int (class_type::*)(int, ...) const>();
    test_is_not_unsafe_integral<int (class_type::*)(int, ...) const&>();
    test_is_not_unsafe_integral<int (class_type::*)(int, ...) const&&>();
    test_is_not_unsafe_integral<int (class_type::*)(int, ...) noexcept>();
    test_is_not_unsafe_integral<int (class_type::*)(int, ...) & noexcept>();
    test_is_not_unsafe_integral<int (class_type::*)(int, ...) && noexcept>();
    test_is_not_unsafe_integral<int (class_type::*)(int, ...) const noexcept>();
    test_is_not_unsafe_integral<int (class_type::*)(int, ...) const & noexcept>();
    test_is_not_unsafe_integral<int (class_type::*)(int, ...) const && noexcept>();
}
