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
#include <phi/type_traits/is_empty.hpp>
#include <phi/type_traits/is_enum.hpp>
#include <phi/type_traits/is_floating_point.hpp>
#include <phi/type_traits/is_function.hpp>
#include <phi/type_traits/is_fundamental.hpp>
#include <phi/type_traits/is_integer.hpp>
#include <phi/type_traits/is_integral.hpp>
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
#include <phi/type_traits/is_void.hpp>
#include <cstddef> // std::nullptr_t
#include <type_traits>
#include <vector>

template <typename TypeT>
void test_is_null_pointer_impl()
{
    STATIC_REQUIRE(phi::is_null_pointer<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_null_pointer<TypeT>::value);

    STATIC_REQUIRE_FALSE(phi::is_member_pointer<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_member_function_pointer<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_member_object_pointer<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_arithmetic<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_array<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_bool<TypeT>::value);
#if PHI_HAS_WORKING_IS_CLASS()
    STATIC_REQUIRE_FALSE(phi::is_class<TypeT>::value);
#endif
    STATIC_REQUIRE_FALSE(phi::is_compound<TypeT>::value);
#if PHI_HAS_WORKING_IS_ENUM()
    STATIC_REQUIRE_FALSE(phi::is_enum<TypeT>::value);
#endif
    STATIC_REQUIRE_FALSE(phi::is_floating_point<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_function<TypeT>::value);
    STATIC_REQUIRE(phi::is_fundamental<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_integer<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_integral<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_lvalue_reference<TypeT>::value);
#if PHI_HAS_WORKING_IS_OBJECT()
    STATIC_REQUIRE(phi::is_object<TypeT>::value);
#endif
    STATIC_REQUIRE_FALSE(phi::is_pointer<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_reference<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_rvalue_reference<TypeT>::value);
#if PHI_HAS_WORKING_IS_SCALAR()
    STATIC_REQUIRE(phi::is_scalar<TypeT>::value);
#endif
#if PHI_HAS_WORKING_IS_UNION()
    STATIC_REQUIRE_FALSE(phi::is_union<TypeT>::value);
#endif
    STATIC_REQUIRE_FALSE(phi::is_void<TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_null_pointer_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_not_null_pointer_v<TypeT>);

    STATIC_REQUIRE_FALSE(phi::is_member_pointer_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_member_object_pointer_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_member_function_pointer_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_arithmetic_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_array_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_bool_v<TypeT>);
#    if PHI_HAS_WORKING_IS_CLASS()
    STATIC_REQUIRE_FALSE(phi::is_class_v<TypeT>);
#    endif
    STATIC_REQUIRE_FALSE(phi::is_compound_v<TypeT>);
#    if PHI_HAS_WORKING_IS_ENUM()
    STATIC_REQUIRE_FALSE(phi::is_enum_v<TypeT>);
#    endif
    STATIC_REQUIRE_FALSE(phi::is_floating_point_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_function_v<TypeT>);
    STATIC_REQUIRE(phi::is_fundamental_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_integer_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_integral_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_lvalue_reference_v<TypeT>);
#    if PHI_HAS_WORKING_IS_OBJECT()
    STATIC_REQUIRE(phi::is_object_v<TypeT>);
#    endif
    STATIC_REQUIRE_FALSE(phi::is_pointer_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_reference_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_rvalue_reference_v<TypeT>);
#    if PHI_HAS_WORKING_IS_SCALAR()
    STATIC_REQUIRE(phi::is_scalar_v<TypeT>);
#    endif
#    if PHI_HAS_WORKING_IS_UNION()
    STATIC_REQUIRE_FALSE(phi::is_union_v<TypeT>);
#    endif
    STATIC_REQUIRE_FALSE(phi::is_void_v<TypeT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_null_pointer<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_null_pointer<TypeT>);

    // Standard compatibility
#if PHI_CPP_STANDARD_IS_ATLEAST(14)
    STATIC_REQUIRE(std::is_null_pointer<TypeT>::value);
#endif
#if PHI_CPP_STANDARD_IS_ATLEAST(17) && PHI_COMPILER_WORKAROUND(GCC, 7, 0, 0)
    STATIC_REQUIRE(std::is_null_pointer_v<TypeT>);
#endif
}

template <typename TypeT>
void test_is_null_pointer()
{
    test_is_null_pointer_impl<TypeT>();
    test_is_null_pointer_impl<const TypeT>();
    test_is_null_pointer_impl<volatile TypeT>();
    test_is_null_pointer_impl<const volatile TypeT>();
}

template <typename TypeT>
void test_is_not_null_pointer_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_null_pointer<TypeT>::value);
    STATIC_REQUIRE(phi::is_not_null_pointer<TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_null_pointer_v<TypeT>);
    STATIC_REQUIRE(phi::is_not_null_pointer_v<TypeT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_null_pointer<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_null_pointer<TypeT>);

    // Standard compatibility
#if PHI_CPP_STANDARD_IS_ATLEAST(14)
    STATIC_REQUIRE_FALSE(std::is_null_pointer<TypeT>::value);
#endif
#if PHI_CPP_STANDARD_IS_ATLEAST(17) && PHI_COMPILER_WORKAROUND(GCC, 7, 0, 0)
    STATIC_REQUIRE_FALSE(std::is_null_pointer_v<TypeT>);
#endif
}

template <typename TypeT>
void test_is_not_null_pointer()
{
    test_is_not_null_pointer_impl<TypeT>();
    test_is_not_null_pointer_impl<const TypeT>();
    test_is_not_null_pointer_impl<volatile TypeT>();
    test_is_not_null_pointer_impl<const volatile TypeT>();
}

TEST_CASE("is_null_pointer")
{
    test_is_null_pointer<phi::nullptr_t>();
    test_is_null_pointer<std::nullptr_t>();
    test_is_null_pointer<decltype(nullptr)>();

    test_is_not_null_pointer<void>();
    test_is_not_null_pointer<bool>();
    test_is_not_null_pointer<char>();
    test_is_not_null_pointer<signed char>();
    test_is_not_null_pointer<unsigned char>();
    test_is_not_null_pointer<short>();
    test_is_not_null_pointer<unsigned short>();
    test_is_not_null_pointer<int>();
    test_is_not_null_pointer<unsigned int>();
    test_is_not_null_pointer<long>();
    test_is_not_null_pointer<unsigned long>();
    test_is_not_null_pointer<long long>();
    test_is_not_null_pointer<unsigned long long>();
    test_is_not_null_pointer<float>();
    test_is_not_null_pointer<double>();
    test_is_not_null_pointer<long double>();
    test_is_not_null_pointer<char8_t>();
    test_is_not_null_pointer<char16_t>();
    test_is_not_null_pointer<char32_t>();
    test_is_not_null_pointer<wchar_t>();

    test_is_not_null_pointer<phi::boolean>();
    test_is_not_null_pointer<phi::integer<signed char>>();
    test_is_not_null_pointer<phi::integer<unsigned char>>();
    test_is_not_null_pointer<phi::integer<short>>();
    test_is_not_null_pointer<phi::integer<unsigned short>>();
    test_is_not_null_pointer<phi::integer<int>>();
    test_is_not_null_pointer<phi::integer<unsigned int>>();
    test_is_not_null_pointer<phi::integer<long>>();
    test_is_not_null_pointer<phi::integer<unsigned long>>();
    test_is_not_null_pointer<phi::integer<long long>>();
    test_is_not_null_pointer<phi::integer<unsigned long long>>();
    test_is_not_null_pointer<phi::floating_point<float>>();
    test_is_not_null_pointer<phi::floating_point<double>>();
    test_is_not_null_pointer<phi::floating_point<long double>>();

    test_is_not_null_pointer<std::vector<int>>();
    test_is_not_null_pointer<phi::scope_ptr<int>>();

    test_is_not_null_pointer<int&>();
    test_is_not_null_pointer<const int&>();
    test_is_not_null_pointer<volatile int&>();
    test_is_not_null_pointer<const volatile int&>();
    test_is_not_null_pointer<int&&>();
    test_is_not_null_pointer<const int&&>();
    test_is_not_null_pointer<volatile int&&>();
    test_is_not_null_pointer<const volatile int&&>();
    test_is_not_null_pointer<int*>();
    test_is_not_null_pointer<const int*>();
    test_is_not_null_pointer<volatile int*>();
    test_is_not_null_pointer<const volatile int*>();
    test_is_not_null_pointer<int**>();
    test_is_not_null_pointer<const int**>();
    test_is_not_null_pointer<volatile int**>();
    test_is_not_null_pointer<const volatile int**>();
    test_is_not_null_pointer<int*&>();
    test_is_not_null_pointer<const int*&>();
    test_is_not_null_pointer<volatile int*&>();
    test_is_not_null_pointer<const volatile int*&>();
    test_is_not_null_pointer<int*&&>();
    test_is_not_null_pointer<const int*&&>();
    test_is_not_null_pointer<volatile int*&&>();
    test_is_not_null_pointer<const volatile int*&&>();
    test_is_not_null_pointer<void*>();
    test_is_not_null_pointer<char[3]>();
    test_is_not_null_pointer<char[]>();
    test_is_not_null_pointer<char* [3]>();
    test_is_not_null_pointer<char*[]>();
    test_is_not_null_pointer<int(*)[3]>();
    test_is_not_null_pointer<int(*)[]>();
    test_is_not_null_pointer<int(&)[3]>();
    test_is_not_null_pointer<int(&)[]>();
    test_is_not_null_pointer<int(&&)[3]>();
    test_is_not_null_pointer<int(&&)[]>();
    test_is_not_null_pointer<char[3][2]>();
    test_is_not_null_pointer<char[][2]>();
    test_is_not_null_pointer<char* [3][2]>();
    test_is_not_null_pointer<char*[][2]>();
    test_is_not_null_pointer<int(*)[3][2]>();
    test_is_not_null_pointer<int(*)[][2]>();
    test_is_not_null_pointer<int(&)[3][2]>();
    test_is_not_null_pointer<int(&)[][2]>();
    test_is_not_null_pointer<int(&&)[3][2]>();
    test_is_not_null_pointer<int(&&)[][2]>();
    test_is_not_null_pointer<class_type>();
    test_is_not_null_pointer<class_type[]>();
    test_is_not_null_pointer<class_type[2]>();
    test_is_not_null_pointer<template_type<void>>();
    test_is_not_null_pointer<template_type<int>>();
    test_is_not_null_pointer<template_type<class_type>>();
    test_is_not_null_pointer<template_type<incomplete_type>>();
    test_is_not_null_pointer<variadic_template<>>();
    test_is_not_null_pointer<variadic_template<void>>();
    test_is_not_null_pointer<variadic_template<int>>();
    test_is_not_null_pointer<variadic_template<class_type>>();
    test_is_not_null_pointer<variadic_template<incomplete_type>>();
    test_is_not_null_pointer<variadic_template<int, void, class_type, volatile char[]>>();
    test_is_not_null_pointer<public_derived_from<base>>();
    test_is_not_null_pointer<public_derived_from<derived>>();
    test_is_not_null_pointer<public_derived_from<class_type>>();
    test_is_not_null_pointer<private_derived_from<base>>();
    test_is_not_null_pointer<private_derived_from<derived>>();
    test_is_not_null_pointer<private_derived_from<class_type>>();
    test_is_not_null_pointer<protected_derived_from<base>>();
    test_is_not_null_pointer<protected_derived_from<derived>>();
    test_is_not_null_pointer<protected_derived_from<class_type>>();
    test_is_not_null_pointer<union_type>();
    test_is_not_null_pointer<non_empty_union>();
    test_is_not_null_pointer<empty>();
    test_is_not_null_pointer<not_empty>();
    test_is_not_null_pointer<bit_zero>();
    test_is_not_null_pointer<bit_one>();
    test_is_not_null_pointer<base>();
    test_is_not_null_pointer<derived>();
    test_is_not_null_pointer<abstract>();
    test_is_not_null_pointer<public_abstract>();
    test_is_not_null_pointer<private_abstract>();
    test_is_not_null_pointer<protected_abstract>();
    test_is_not_null_pointer<abstract_template<int>>();
    test_is_not_null_pointer<abstract_template<double>>();
    test_is_not_null_pointer<abstract_template<class_type>>();
    test_is_not_null_pointer<abstract_template<incomplete_type>>();
    test_is_not_null_pointer<final_type>();
    test_is_not_null_pointer<public_destructor>();
    test_is_not_null_pointer<protected_destructor>();
    test_is_not_null_pointer<private_destructor>();
    test_is_not_null_pointer<virtual_public_destructor>();
    test_is_not_null_pointer<virtual_protected_destructor>();
    test_is_not_null_pointer<virtual_private_destructor>();
    test_is_not_null_pointer<pure_public_destructor>();
    test_is_not_null_pointer<pure_protected_destructor>();
    test_is_not_null_pointer<pure_private_destructor>();
    test_is_not_null_pointer<deleted_public_destructor>();
    test_is_not_null_pointer<deleted_protected_destructor>();
    test_is_not_null_pointer<deleted_private_destructor>();
    test_is_not_null_pointer<deleted_virtual_public_destructor>();
    test_is_not_null_pointer<deleted_virtual_protected_destructor>();
    test_is_not_null_pointer<deleted_virtual_private_destructor>();
    test_is_not_null_pointer<final_type>();
    test_is_not_null_pointer<Enum>();
    test_is_not_null_pointer<EnumSigned>();
    test_is_not_null_pointer<EnumUnsigned>();
    test_is_not_null_pointer<EnumClass>();
    test_is_not_null_pointer<EnumStruct>();
    test_is_not_null_pointer<function_type>();
    test_is_not_null_pointer<function_ptr>();
    test_is_not_null_pointer<member_object_ptr>();
    test_is_not_null_pointer<member_function_ptr>();
    test_is_not_null_pointer<incomplete_type>();
    test_is_not_null_pointer<incomplete_template<void>>();
    test_is_not_null_pointer<incomplete_template<int>>();
    test_is_not_null_pointer<incomplete_template<class_type>>();
    test_is_not_null_pointer<incomplete_template<incomplete_type>>();
    test_is_not_null_pointer<incomplete_variadic_template<>>();
    test_is_not_null_pointer<incomplete_variadic_template<void>>();
    test_is_not_null_pointer<incomplete_variadic_template<int>>();
    test_is_not_null_pointer<incomplete_variadic_template<class_type>>();
    test_is_not_null_pointer<incomplete_variadic_template<incomplete_type>>();
    test_is_not_null_pointer<
            incomplete_variadic_template<int, void, class_type, volatile char[]>>();
    test_is_not_null_pointer<int class_type::*>();
    test_is_not_null_pointer<float class_type::*>();
    test_is_not_null_pointer<void * class_type::*>();
    test_is_not_null_pointer<int * class_type::*>();
    test_is_not_null_pointer<int class_type::*&>();
    test_is_not_null_pointer<float class_type::*&>();
    test_is_not_null_pointer<void * class_type::*&>();
    test_is_not_null_pointer<int * class_type::*&>();
    test_is_not_null_pointer<int class_type::*&&>();
    test_is_not_null_pointer<float class_type::*&&>();
    test_is_not_null_pointer<void * class_type::*&&>();
    test_is_not_null_pointer<int * class_type::*&&>();
    test_is_not_null_pointer<int class_type::*const>();
    test_is_not_null_pointer<float class_type::*const>();
    test_is_not_null_pointer<void * class_type::*const>();
    test_is_not_null_pointer<int class_type::*const&>();
    test_is_not_null_pointer<float class_type::*const&>();
    test_is_not_null_pointer<void * class_type::*const&>();
    test_is_not_null_pointer<int class_type::*const&&>();
    test_is_not_null_pointer<float class_type::*const&&>();
    test_is_not_null_pointer<void * class_type::*const&&>();
    test_is_not_null_pointer<int class_type::*volatile>();
    test_is_not_null_pointer<float class_type::*volatile>();
    test_is_not_null_pointer<void * class_type::*volatile>();
    test_is_not_null_pointer<int class_type::*volatile&>();
    test_is_not_null_pointer<float class_type::*volatile&>();
    test_is_not_null_pointer<void * class_type::*volatile&>();
    test_is_not_null_pointer<int class_type::*volatile&&>();
    test_is_not_null_pointer<float class_type::*volatile&&>();
    test_is_not_null_pointer<void * class_type::*volatile&&>();
    test_is_not_null_pointer<int class_type::*const volatile>();
    test_is_not_null_pointer<float class_type::*const volatile>();
    test_is_not_null_pointer<void * class_type::*const volatile>();
    test_is_not_null_pointer<int class_type::*const volatile&>();
    test_is_not_null_pointer<float class_type::*const volatile&>();
    test_is_not_null_pointer<void * class_type::*const volatile&>();
    test_is_not_null_pointer<int class_type::*const volatile&&>();
    test_is_not_null_pointer<float class_type::*const volatile&&>();
    test_is_not_null_pointer<void * class_type::*const volatile&&>();
    test_is_not_null_pointer<non_copyable>();
    test_is_not_null_pointer<non_moveable>();
    test_is_not_null_pointer<non_constructible>();
    test_is_not_null_pointer<tracked>();
    test_is_not_null_pointer<trap_constructible>();
    test_is_not_null_pointer<trap_implicit_conversion>();
    test_is_not_null_pointer<trap_comma>();
    test_is_not_null_pointer<trap_call>();
    test_is_not_null_pointer<trap_self_assign>();
    test_is_not_null_pointer<trap_deref>();
    test_is_not_null_pointer<trap_array_subscript>();

    test_is_not_null_pointer<void()>();
    test_is_not_null_pointer<void()&>();
    test_is_not_null_pointer<void() &&>();
    test_is_not_null_pointer<void() const>();
    test_is_not_null_pointer<void() const&>();
    test_is_not_null_pointer<void() const&&>();
    test_is_not_null_pointer<void() volatile>();
    test_is_not_null_pointer<void() volatile&>();
    test_is_not_null_pointer<void() volatile&&>();
    test_is_not_null_pointer<void() const volatile>();
    test_is_not_null_pointer<void() const volatile&>();
    test_is_not_null_pointer<void() const volatile&&>();
    test_is_not_null_pointer<void() noexcept>();
    test_is_not_null_pointer<void() & noexcept>();
    test_is_not_null_pointer<void() && noexcept>();
    test_is_not_null_pointer<void() const noexcept>();
    test_is_not_null_pointer<void() const & noexcept>();
    test_is_not_null_pointer<void() const && noexcept>();
    test_is_not_null_pointer<void() volatile noexcept>();
    test_is_not_null_pointer<void() volatile & noexcept>();
    test_is_not_null_pointer<void() volatile && noexcept>();
    test_is_not_null_pointer<void() const volatile noexcept>();
    test_is_not_null_pointer<void() const volatile & noexcept>();
    test_is_not_null_pointer<void() const volatile && noexcept>();

    test_is_not_null_pointer<void(int)>();
    test_is_not_null_pointer<void(int)&>();
    test_is_not_null_pointer<void(int) &&>();
    test_is_not_null_pointer<void(int) const>();
    test_is_not_null_pointer<void(int) const&>();
    test_is_not_null_pointer<void(int) const&&>();
    test_is_not_null_pointer<void(int) volatile>();
    test_is_not_null_pointer<void(int) volatile&>();
    test_is_not_null_pointer<void(int) volatile&&>();
    test_is_not_null_pointer<void(int) const volatile>();
    test_is_not_null_pointer<void(int) const volatile&>();
    test_is_not_null_pointer<void(int) const volatile&&>();
    test_is_not_null_pointer<void(int) noexcept>();
    test_is_not_null_pointer<void(int) & noexcept>();
    test_is_not_null_pointer<void(int) && noexcept>();
    test_is_not_null_pointer<void(int) const noexcept>();
    test_is_not_null_pointer<void(int) const & noexcept>();
    test_is_not_null_pointer<void(int) const && noexcept>();
    test_is_not_null_pointer<void(int) volatile noexcept>();
    test_is_not_null_pointer<void(int) volatile & noexcept>();
    test_is_not_null_pointer<void(int) volatile && noexcept>();
    test_is_not_null_pointer<void(int) const volatile noexcept>();
    test_is_not_null_pointer<void(int) const volatile & noexcept>();
    test_is_not_null_pointer<void(int) const volatile && noexcept>();

    test_is_not_null_pointer<void(...)>();
    test_is_not_null_pointer<void(...)&>();
    test_is_not_null_pointer<void(...) &&>();
    test_is_not_null_pointer<void(...) const>();
    test_is_not_null_pointer<void(...) const&>();
    test_is_not_null_pointer<void(...) const&&>();
    test_is_not_null_pointer<void(...) volatile>();
    test_is_not_null_pointer<void(...) volatile&>();
    test_is_not_null_pointer<void(...) volatile&&>();
    test_is_not_null_pointer<void(...) const volatile>();
    test_is_not_null_pointer<void(...) const volatile&>();
    test_is_not_null_pointer<void(...) const volatile&&>();
    test_is_not_null_pointer<void(...) noexcept>();
    test_is_not_null_pointer<void(...) & noexcept>();
    test_is_not_null_pointer<void(...) && noexcept>();
    test_is_not_null_pointer<void(...) const noexcept>();
    test_is_not_null_pointer<void(...) const & noexcept>();
    test_is_not_null_pointer<void(...) const && noexcept>();
    test_is_not_null_pointer<void(...) volatile noexcept>();
    test_is_not_null_pointer<void(...) volatile & noexcept>();
    test_is_not_null_pointer<void(...) volatile && noexcept>();
    test_is_not_null_pointer<void(...) const volatile noexcept>();
    test_is_not_null_pointer<void(...) const volatile & noexcept>();
    test_is_not_null_pointer<void(...) const volatile && noexcept>();

    test_is_not_null_pointer<void(int, ...)>();
    test_is_not_null_pointer<void(int, ...)&>();
    test_is_not_null_pointer<void(int, ...) &&>();
    test_is_not_null_pointer<void(int, ...) const>();
    test_is_not_null_pointer<void(int, ...) const&>();
    test_is_not_null_pointer<void(int, ...) const&&>();
    test_is_not_null_pointer<void(int, ...) volatile>();
    test_is_not_null_pointer<void(int, ...) volatile&>();
    test_is_not_null_pointer<void(int, ...) volatile&&>();
    test_is_not_null_pointer<void(int, ...) const volatile>();
    test_is_not_null_pointer<void(int, ...) const volatile&>();
    test_is_not_null_pointer<void(int, ...) const volatile&&>();
    test_is_not_null_pointer<void(int, ...) noexcept>();
    test_is_not_null_pointer<void(int, ...) & noexcept>();
    test_is_not_null_pointer<void(int, ...) && noexcept>();
    test_is_not_null_pointer<void(int, ...) const noexcept>();
    test_is_not_null_pointer<void(int, ...) const & noexcept>();
    test_is_not_null_pointer<void(int, ...) const && noexcept>();
    test_is_not_null_pointer<void(int, ...) volatile noexcept>();
    test_is_not_null_pointer<void(int, ...) volatile & noexcept>();
    test_is_not_null_pointer<void(int, ...) volatile && noexcept>();
    test_is_not_null_pointer<void(int, ...) const volatile noexcept>();
    test_is_not_null_pointer<void(int, ...) const volatile & noexcept>();
    test_is_not_null_pointer<void(int, ...) const volatile && noexcept>();

    test_is_not_null_pointer<int()>();
    test_is_not_null_pointer<int()&>();
    test_is_not_null_pointer<int() &&>();
    test_is_not_null_pointer<int() const>();
    test_is_not_null_pointer<int() const&>();
    test_is_not_null_pointer<int() const&&>();
    test_is_not_null_pointer<int() volatile>();
    test_is_not_null_pointer<int() volatile&>();
    test_is_not_null_pointer<int() volatile&&>();
    test_is_not_null_pointer<int() const volatile>();
    test_is_not_null_pointer<int() const volatile&>();
    test_is_not_null_pointer<int() const volatile&&>();
    test_is_not_null_pointer<int() noexcept>();
    test_is_not_null_pointer<int() & noexcept>();
    test_is_not_null_pointer<int() && noexcept>();
    test_is_not_null_pointer<int() const noexcept>();
    test_is_not_null_pointer<int() const & noexcept>();
    test_is_not_null_pointer<int() const && noexcept>();
    test_is_not_null_pointer<int() volatile noexcept>();
    test_is_not_null_pointer<int() volatile & noexcept>();
    test_is_not_null_pointer<int() volatile && noexcept>();
    test_is_not_null_pointer<int() const volatile noexcept>();
    test_is_not_null_pointer<int() const volatile & noexcept>();
    test_is_not_null_pointer<int() const volatile && noexcept>();

    test_is_not_null_pointer<int(int)>();
    test_is_not_null_pointer<int(int)&>();
    test_is_not_null_pointer<int(int) &&>();
    test_is_not_null_pointer<int(int) const>();
    test_is_not_null_pointer<int(int) const&>();
    test_is_not_null_pointer<int(int) const&&>();
    test_is_not_null_pointer<int(int) volatile>();
    test_is_not_null_pointer<int(int) volatile&>();
    test_is_not_null_pointer<int(int) volatile&&>();
    test_is_not_null_pointer<int(int) const volatile>();
    test_is_not_null_pointer<int(int) const volatile&>();
    test_is_not_null_pointer<int(int) const volatile&&>();
    test_is_not_null_pointer<int(int) noexcept>();
    test_is_not_null_pointer<int(int) & noexcept>();
    test_is_not_null_pointer<int(int) && noexcept>();
    test_is_not_null_pointer<int(int) const noexcept>();
    test_is_not_null_pointer<int(int) const & noexcept>();
    test_is_not_null_pointer<int(int) const && noexcept>();
    test_is_not_null_pointer<int(int) volatile noexcept>();
    test_is_not_null_pointer<int(int) volatile & noexcept>();
    test_is_not_null_pointer<int(int) volatile && noexcept>();
    test_is_not_null_pointer<int(int) const volatile noexcept>();
    test_is_not_null_pointer<int(int) const volatile & noexcept>();
    test_is_not_null_pointer<int(int) const volatile && noexcept>();

    test_is_not_null_pointer<int(...)>();
    test_is_not_null_pointer<int(...)&>();
    test_is_not_null_pointer<int(...) &&>();
    test_is_not_null_pointer<int(...) const>();
    test_is_not_null_pointer<int(...) const&>();
    test_is_not_null_pointer<int(...) const&&>();
    test_is_not_null_pointer<int(...) volatile>();
    test_is_not_null_pointer<int(...) volatile&>();
    test_is_not_null_pointer<int(...) volatile&&>();
    test_is_not_null_pointer<int(...) const volatile>();
    test_is_not_null_pointer<int(...) const volatile&>();
    test_is_not_null_pointer<int(...) const volatile&&>();
    test_is_not_null_pointer<int(...) noexcept>();
    test_is_not_null_pointer<int(...) & noexcept>();
    test_is_not_null_pointer<int(...) && noexcept>();
    test_is_not_null_pointer<int(...) const noexcept>();
    test_is_not_null_pointer<int(...) const & noexcept>();
    test_is_not_null_pointer<int(...) const && noexcept>();
    test_is_not_null_pointer<int(...) volatile noexcept>();
    test_is_not_null_pointer<int(...) volatile & noexcept>();
    test_is_not_null_pointer<int(...) volatile && noexcept>();
    test_is_not_null_pointer<int(...) const volatile noexcept>();
    test_is_not_null_pointer<int(...) const volatile & noexcept>();
    test_is_not_null_pointer<int(...) const volatile && noexcept>();

    test_is_not_null_pointer<int(int, ...)>();
    test_is_not_null_pointer<int(int, ...)&>();
    test_is_not_null_pointer<int(int, ...) &&>();
    test_is_not_null_pointer<int(int, ...) const>();
    test_is_not_null_pointer<int(int, ...) const&>();
    test_is_not_null_pointer<int(int, ...) const&&>();
    test_is_not_null_pointer<int(int, ...) volatile>();
    test_is_not_null_pointer<int(int, ...) volatile&>();
    test_is_not_null_pointer<int(int, ...) volatile&&>();
    test_is_not_null_pointer<int(int, ...) const volatile>();
    test_is_not_null_pointer<int(int, ...) const volatile&>();
    test_is_not_null_pointer<int(int, ...) const volatile&&>();
    test_is_not_null_pointer<int(int, ...) noexcept>();
    test_is_not_null_pointer<int(int, ...) & noexcept>();
    test_is_not_null_pointer<int(int, ...) && noexcept>();
    test_is_not_null_pointer<int(int, ...) const noexcept>();
    test_is_not_null_pointer<int(int, ...) const & noexcept>();
    test_is_not_null_pointer<int(int, ...) const && noexcept>();
    test_is_not_null_pointer<int(int, ...) volatile noexcept>();
    test_is_not_null_pointer<int(int, ...) volatile & noexcept>();
    test_is_not_null_pointer<int(int, ...) volatile && noexcept>();
    test_is_not_null_pointer<int(int, ...) const volatile noexcept>();
    test_is_not_null_pointer<int(int, ...) const volatile & noexcept>();
    test_is_not_null_pointer<int(int, ...) const volatile && noexcept>();

    test_is_not_null_pointer<void (*)()>();
    test_is_not_null_pointer<void (*)() noexcept>();

    test_is_not_null_pointer<void (*)(int)>();
    test_is_not_null_pointer<void (*)(int) noexcept>();

    test_is_not_null_pointer<void (*)(...)>();
    test_is_not_null_pointer<void (*)(...) noexcept>();

    test_is_not_null_pointer<void (*)(int, ...)>();
    test_is_not_null_pointer<void (*)(int, ...) noexcept>();

    test_is_not_null_pointer<int (*)()>();
    test_is_not_null_pointer<int (*)() noexcept>();

    test_is_not_null_pointer<int (*)(int)>();
    test_is_not_null_pointer<int (*)(int) noexcept>();

    test_is_not_null_pointer<int (*)(...)>();
    test_is_not_null_pointer<int (*)(...) noexcept>();

    test_is_not_null_pointer<int (*)(int, ...)>();
    test_is_not_null_pointer<int (*)(int, ...) noexcept>();

    test_is_not_null_pointer<void (&)()>();
    test_is_not_null_pointer<void (&)() noexcept>();

    test_is_not_null_pointer<void (&)(int)>();
    test_is_not_null_pointer<void (&)(int) noexcept>();

    test_is_not_null_pointer<void (&)(...)>();
    test_is_not_null_pointer<void (&)(...) noexcept>();

    test_is_not_null_pointer<void (&)(int, ...)>();
    test_is_not_null_pointer<void (&)(int, ...) noexcept>();

    test_is_not_null_pointer<int (&)()>();
    test_is_not_null_pointer<int (&)() noexcept>();

    test_is_not_null_pointer<int (&)(int)>();
    test_is_not_null_pointer<int (&)(int) noexcept>();

    test_is_not_null_pointer<int (&)(...)>();
    test_is_not_null_pointer<int (&)(...) noexcept>();

    test_is_not_null_pointer<int (&)(int, ...)>();
    test_is_not_null_pointer<int (&)(int, ...) noexcept>();

    test_is_not_null_pointer<void (&&)()>();
    test_is_not_null_pointer<void (&&)() noexcept>();

    test_is_not_null_pointer<void (&&)(int)>();
    test_is_not_null_pointer<void (&&)(int) noexcept>();

    test_is_not_null_pointer<void (&&)(...)>();
    test_is_not_null_pointer<void (&&)(...) noexcept>();

    test_is_not_null_pointer<void (&&)(int, ...)>();
    test_is_not_null_pointer<void (&&)(int, ...) noexcept>();

    test_is_not_null_pointer<int (&&)()>();
    test_is_not_null_pointer<int (&&)() noexcept>();

    test_is_not_null_pointer<int (&&)(int)>();
    test_is_not_null_pointer<int (&&)(int) noexcept>();

    test_is_not_null_pointer<int (&&)(...)>();
    test_is_not_null_pointer<int (&&)(...) noexcept>();

    test_is_not_null_pointer<int (&&)(int, ...)>();
    test_is_not_null_pointer<int (&&)(int, ...) noexcept>();

    test_is_not_null_pointer<void (class_type::*)()>();
    test_is_not_null_pointer<void (class_type::*)()&>();
    test_is_not_null_pointer<void (class_type::*)() &&>();
    test_is_not_null_pointer<void (class_type::*)() const>();
    test_is_not_null_pointer<void (class_type::*)() const&>();
    test_is_not_null_pointer<void (class_type::*)() const&&>();
    test_is_not_null_pointer<void (class_type::*)() noexcept>();
    test_is_not_null_pointer<void (class_type::*)() & noexcept>();
    test_is_not_null_pointer<void (class_type::*)() && noexcept>();
    test_is_not_null_pointer<void (class_type::*)() const noexcept>();
    test_is_not_null_pointer<void (class_type::*)() const & noexcept>();
    test_is_not_null_pointer<void (class_type::*)() const && noexcept>();

    test_is_not_null_pointer<void (class_type::*)(int)>();
    test_is_not_null_pointer<void (class_type::*)(int)&>();
    test_is_not_null_pointer<void (class_type::*)(int) &&>();
    test_is_not_null_pointer<void (class_type::*)(int) const>();
    test_is_not_null_pointer<void (class_type::*)(int) const&>();
    test_is_not_null_pointer<void (class_type::*)(int) const&&>();
    test_is_not_null_pointer<void (class_type::*)(int) noexcept>();
    test_is_not_null_pointer<void (class_type::*)(int) & noexcept>();
    test_is_not_null_pointer<void (class_type::*)(int) && noexcept>();
    test_is_not_null_pointer<void (class_type::*)(int) const noexcept>();
    test_is_not_null_pointer<void (class_type::*)(int) const & noexcept>();
    test_is_not_null_pointer<void (class_type::*)(int) const && noexcept>();

    test_is_not_null_pointer<void (class_type::*)(...)>();
    test_is_not_null_pointer<void (class_type::*)(...)&>();
    test_is_not_null_pointer<void (class_type::*)(...) &&>();
    test_is_not_null_pointer<void (class_type::*)(...) const>();
    test_is_not_null_pointer<void (class_type::*)(...) const&>();
    test_is_not_null_pointer<void (class_type::*)(...) const&&>();
    test_is_not_null_pointer<void (class_type::*)(...) noexcept>();
    test_is_not_null_pointer<void (class_type::*)(...) & noexcept>();
    test_is_not_null_pointer<void (class_type::*)(...) && noexcept>();
    test_is_not_null_pointer<void (class_type::*)(...) const noexcept>();
    test_is_not_null_pointer<void (class_type::*)(...) const & noexcept>();
    test_is_not_null_pointer<void (class_type::*)(...) const && noexcept>();

    test_is_not_null_pointer<void (class_type::*)(int, ...)>();
    test_is_not_null_pointer<void (class_type::*)(int, ...)&>();
    test_is_not_null_pointer<void (class_type::*)(int, ...) &&>();
    test_is_not_null_pointer<void (class_type::*)(int, ...) const>();
    test_is_not_null_pointer<void (class_type::*)(int, ...) const&>();
    test_is_not_null_pointer<void (class_type::*)(int, ...) const&&>();
    test_is_not_null_pointer<void (class_type::*)(int, ...) noexcept>();
    test_is_not_null_pointer<void (class_type::*)(int, ...) & noexcept>();
    test_is_not_null_pointer<void (class_type::*)(int, ...) && noexcept>();
    test_is_not_null_pointer<void (class_type::*)(int, ...) const noexcept>();
    test_is_not_null_pointer<void (class_type::*)(int, ...) const & noexcept>();
    test_is_not_null_pointer<void (class_type::*)(int, ...) const && noexcept>();

    test_is_not_null_pointer<int (class_type::*)()>();
    test_is_not_null_pointer<int (class_type::*)()&>();
    test_is_not_null_pointer<int (class_type::*)() &&>();
    test_is_not_null_pointer<int (class_type::*)() const>();
    test_is_not_null_pointer<int (class_type::*)() const&>();
    test_is_not_null_pointer<int (class_type::*)() const&&>();
    test_is_not_null_pointer<int (class_type::*)() noexcept>();
    test_is_not_null_pointer<int (class_type::*)() & noexcept>();
    test_is_not_null_pointer<int (class_type::*)() && noexcept>();
    test_is_not_null_pointer<int (class_type::*)() const noexcept>();
    test_is_not_null_pointer<int (class_type::*)() const & noexcept>();
    test_is_not_null_pointer<int (class_type::*)() const && noexcept>();

    test_is_not_null_pointer<int (class_type::*)(int)>();
    test_is_not_null_pointer<int (class_type::*)(int)&>();
    test_is_not_null_pointer<int (class_type::*)(int) &&>();
    test_is_not_null_pointer<int (class_type::*)(int) const>();
    test_is_not_null_pointer<int (class_type::*)(int) const&>();
    test_is_not_null_pointer<int (class_type::*)(int) const&&>();
    test_is_not_null_pointer<int (class_type::*)(int) noexcept>();
    test_is_not_null_pointer<int (class_type::*)(int) & noexcept>();
    test_is_not_null_pointer<int (class_type::*)(int) && noexcept>();
    test_is_not_null_pointer<int (class_type::*)(int) const noexcept>();
    test_is_not_null_pointer<int (class_type::*)(int) const & noexcept>();
    test_is_not_null_pointer<int (class_type::*)(int) const && noexcept>();

    test_is_not_null_pointer<int (class_type::*)(...)>();
    test_is_not_null_pointer<int (class_type::*)(...)&>();
    test_is_not_null_pointer<int (class_type::*)(...) &&>();
    test_is_not_null_pointer<int (class_type::*)(...) const>();
    test_is_not_null_pointer<int (class_type::*)(...) const&>();
    test_is_not_null_pointer<int (class_type::*)(...) const&&>();
    test_is_not_null_pointer<int (class_type::*)(...) noexcept>();
    test_is_not_null_pointer<int (class_type::*)(...) & noexcept>();
    test_is_not_null_pointer<int (class_type::*)(...) && noexcept>();
    test_is_not_null_pointer<int (class_type::*)(...) const noexcept>();
    test_is_not_null_pointer<int (class_type::*)(...) const & noexcept>();
    test_is_not_null_pointer<int (class_type::*)(...) const && noexcept>();

    test_is_not_null_pointer<int (class_type::*)(int, ...)>();
    test_is_not_null_pointer<int (class_type::*)(int, ...)&>();
    test_is_not_null_pointer<int (class_type::*)(int, ...) &&>();
    test_is_not_null_pointer<int (class_type::*)(int, ...) const>();
    test_is_not_null_pointer<int (class_type::*)(int, ...) const&>();
    test_is_not_null_pointer<int (class_type::*)(int, ...) const&&>();
    test_is_not_null_pointer<int (class_type::*)(int, ...) noexcept>();
    test_is_not_null_pointer<int (class_type::*)(int, ...) & noexcept>();
    test_is_not_null_pointer<int (class_type::*)(int, ...) && noexcept>();
    test_is_not_null_pointer<int (class_type::*)(int, ...) const noexcept>();
    test_is_not_null_pointer<int (class_type::*)(int, ...) const & noexcept>();
    test_is_not_null_pointer<int (class_type::*)(int, ...) const && noexcept>();
}
