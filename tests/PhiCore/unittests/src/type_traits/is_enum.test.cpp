#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/compiler_support/extensions/zero_size_array.hpp>
#include <phi/compiler_support/warning.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_arithmetic.hpp>
#include <phi/type_traits/is_array.hpp>
#include <phi/type_traits/is_bool.hpp>
#include <phi/type_traits/is_class.hpp>
#include <phi/type_traits/is_compound.hpp>
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
#include <type_traits>
#include <vector>

template <typename TypeT>
void test_is_enum_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_arithmetic<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_array<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_bool<TypeT>::value);
#if PHI_HAS_WORKING_IS_CLASS()
    STATIC_REQUIRE_FALSE(phi::is_class<TypeT>::value);
#endif
    STATIC_REQUIRE(phi::is_compound<TypeT>::value);
#if PHI_HAS_WORKING_IS_ENUM()
    STATIC_REQUIRE(phi::is_enum<TypeT>::value);
#endif
    STATIC_REQUIRE_FALSE(phi::is_floating_point<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_function<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_fundamental<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_integer<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_integral<TypeT>::value);
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
#if PHI_HAS_WORKING_IS_SCALAR()
    STATIC_REQUIRE(phi::is_scalar<TypeT>::value);
#endif
#if PHI_HAS_WORKING_IS_UNION()
    STATIC_REQUIRE_FALSE(phi::is_union<TypeT>::value);
#endif
    STATIC_REQUIRE_FALSE(phi::is_void<TypeT>::value);

#if PHI_HAS_WORKING_IS_ENUM()
    STATIC_REQUIRE_FALSE(phi::is_not_enum<TypeT>::value);
#endif

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_arithmetic_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_array_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_bool_v<TypeT>);
#    if PHI_HAS_WORKING_IS_CLASS()
    STATIC_REQUIRE_FALSE(phi::is_class_v<TypeT>);
#    endif
    STATIC_REQUIRE(phi::is_compound_v<TypeT>);
#    if PHI_HAS_WORKING_IS_ENUM()
    STATIC_REQUIRE(phi::is_enum_v<TypeT>);
#    endif
    STATIC_REQUIRE_FALSE(phi::is_floating_point_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_function_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_fundamental_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_integer_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_integral_v<TypeT>);
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
#    if PHI_HAS_WORKING_IS_SCALAR()
    STATIC_REQUIRE(phi::is_scalar_v<TypeT>);
#    endif
#    if PHI_HAS_WORKING_IS_UNION()
    STATIC_REQUIRE_FALSE(phi::is_union_v<TypeT>);
#    endif
    STATIC_REQUIRE_FALSE(phi::is_void_v<TypeT>);

#    if PHI_HAS_WORKING_IS_ENUM()
    STATIC_REQUIRE_FALSE(phi::is_not_enum_v<TypeT>);
#    endif
#endif

#if PHI_HAS_WORKING_IS_ENUM()
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_enum<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_enum<TypeT>);
#endif

    // Standard compatibility
#if PHI_HAS_WORKING_IS_ENUM()
    STATIC_REQUIRE(std::is_enum<TypeT>::value);
#    if PHI_CPP_STANDARD_IS_ATLEAST(17) && PHI_COMPILER_WORKAROUND(GCC, 7, 0, 0)
    STATIC_REQUIRE(std::is_enum_v<TypeT>);
#    endif
#endif
}

template <typename TypeT>
void test_is_enum()
{
    test_is_enum_impl<TypeT>();
    test_is_enum_impl<const TypeT>();
    test_is_enum_impl<volatile TypeT>();
    test_is_enum_impl<const volatile TypeT>();
}

template <typename TypeT>
void test_is_not_enum_impl()
{
#if PHI_HAS_WORKING_IS_ENUM()
    STATIC_REQUIRE_FALSE(phi::is_enum<TypeT>::value);
    STATIC_REQUIRE(phi::is_not_enum<TypeT>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_enum_v<TypeT>);
    STATIC_REQUIRE(phi::is_not_enum_v<TypeT>);
#    endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_enum<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_enum<TypeT>);

    // Standard compatibility
    STATIC_REQUIRE_FALSE(std::is_enum<TypeT>::value);
#    if PHI_CPP_STANDARD_IS_ATLEAST(17) && PHI_COMPILER_WORKAROUND(GCC, 7, 0, 0)
    STATIC_REQUIRE_FALSE(std::is_enum_v<TypeT>);
#    endif
#endif
}

template <typename TypeT>
void test_is_not_enum()
{
    test_is_not_enum_impl<TypeT>();
    test_is_not_enum_impl<const TypeT>();
    test_is_not_enum_impl<volatile TypeT>();
    test_is_not_enum_impl<const volatile TypeT>();
}

TEST_CASE("is_enum")
{
    test_is_not_enum<void>();
    test_is_not_enum<phi::nullptr_t>();
    test_is_not_enum<bool>();
    test_is_not_enum<char>();
    test_is_not_enum<signed char>();
    test_is_not_enum<unsigned char>();
    test_is_not_enum<short>();
    test_is_not_enum<unsigned short>();
    test_is_not_enum<int>();
    test_is_not_enum<unsigned int>();
    test_is_not_enum<long>();
    test_is_not_enum<unsigned long>();
    test_is_not_enum<long long>();
    test_is_not_enum<unsigned long long>();
    test_is_not_enum<float>();
    test_is_not_enum<double>();
    test_is_not_enum<long double>();
    test_is_not_enum<char8_t>();
    test_is_not_enum<char16_t>();
    test_is_not_enum<char32_t>();
    test_is_not_enum<wchar_t>();

    test_is_not_enum<phi::boolean>();
    test_is_not_enum<phi::integer<signed char>>();
    test_is_not_enum<phi::integer<unsigned char>>();
    test_is_not_enum<phi::integer<short>>();
    test_is_not_enum<phi::integer<unsigned short>>();
    test_is_not_enum<phi::integer<int>>();
    test_is_not_enum<phi::integer<unsigned int>>();
    test_is_not_enum<phi::integer<long>>();
    test_is_not_enum<phi::integer<unsigned long>>();
    test_is_not_enum<phi::integer<long long>>();
    test_is_not_enum<phi::integer<unsigned long long>>();
    test_is_not_enum<phi::floating_point<float>>();
    test_is_not_enum<phi::floating_point<double>>();
    test_is_not_enum<phi::floating_point<long double>>();

    test_is_not_enum<std::vector<int>>();
    test_is_not_enum<phi::scope_ptr<int>>();

    test_is_not_enum<int&>();
    test_is_not_enum<const int&>();
    test_is_not_enum<volatile int&>();
    test_is_not_enum<const volatile int&>();
    test_is_not_enum<int&&>();
    test_is_not_enum<const int&&>();
    test_is_not_enum<volatile int&&>();
    test_is_not_enum<const volatile int&&>();
    test_is_not_enum<int*>();
    test_is_not_enum<const int*>();
    test_is_not_enum<volatile int*>();
    test_is_not_enum<const volatile int*>();
    test_is_not_enum<int**>();
    test_is_not_enum<const int**>();
    test_is_not_enum<volatile int**>();
    test_is_not_enum<const volatile int**>();
    test_is_not_enum<int*&>();
    test_is_not_enum<const int*&>();
    test_is_not_enum<volatile int*&>();
    test_is_not_enum<const volatile int*&>();
    test_is_not_enum<int*&&>();
    test_is_not_enum<const int*&&>();
    test_is_not_enum<volatile int*&&>();
    test_is_not_enum<const volatile int*&&>();
    test_is_not_enum<void*>();
    test_is_not_enum<char[3]>();
    test_is_not_enum<char[]>();
    test_is_not_enum<char* [3]>();
    test_is_not_enum<char*[]>();
    test_is_not_enum<int(*)[3]>();
    test_is_not_enum<int(*)[]>();
    test_is_not_enum<int(&)[3]>();
    test_is_not_enum<int(&)[]>();
    test_is_not_enum<int(&&)[3]>();
    test_is_not_enum<int(&&)[]>();
    test_is_not_enum<char[3][2]>();
    test_is_not_enum<char[][2]>();
    test_is_not_enum<char* [3][2]>();
    test_is_not_enum<char*[][2]>();
    test_is_not_enum<int(*)[3][2]>();
    test_is_not_enum<int(*)[][2]>();
    test_is_not_enum<int(&)[3][2]>();
    test_is_not_enum<int(&)[][2]>();
    test_is_not_enum<int(&&)[3][2]>();
    test_is_not_enum<int(&&)[][2]>();
    test_is_not_enum<class_type>();
    test_is_not_enum<class_type[]>();
    test_is_not_enum<class_type[2]>();
    test_is_not_enum<template_type<void>>();
    test_is_not_enum<template_type<int>>();
    test_is_not_enum<template_type<class_type>>();
    test_is_not_enum<template_type<incomplete_type>>();
    test_is_not_enum<variadic_template<>>();
    test_is_not_enum<variadic_template<void>>();
    test_is_not_enum<variadic_template<int>>();
    test_is_not_enum<variadic_template<class_type>>();
    test_is_not_enum<variadic_template<incomplete_type>>();
    test_is_not_enum<variadic_template<int, void, class_type, volatile char[]>>();
    test_is_not_enum<public_derived_from<base>>();
    test_is_not_enum<public_derived_from<derived>>();
    test_is_not_enum<public_derived_from<class_type>>();
    test_is_not_enum<private_derived_from<base>>();
    test_is_not_enum<private_derived_from<derived>>();
    test_is_not_enum<private_derived_from<class_type>>();
    test_is_not_enum<protected_derived_from<base>>();
    test_is_not_enum<protected_derived_from<derived>>();
    test_is_not_enum<protected_derived_from<class_type>>();
    test_is_not_enum<virtual_derived_from<base>>();
    test_is_not_enum<virtual_derived_from<derived>>();
    test_is_not_enum<virtual_derived_from<class_type>>();
    test_is_not_enum<union_type>();
    test_is_not_enum<non_empty_union>();
    test_is_not_enum<non_trivial_union>();
    test_is_not_enum<empty>();
    test_is_not_enum<not_empty>();
    test_is_not_enum<non_trivial>();
    test_is_not_enum<bit_zero>();
    test_is_not_enum<bit_one>();
    test_is_not_enum<base>();
    test_is_not_enum<derived>();
    test_is_not_enum<non_empty_base>();
    test_is_not_enum<empty_base>();
    test_is_not_enum<virtual_base>();
    test_is_not_enum<polymorphic>();
    test_is_not_enum<derived_polymorphic>();
    test_is_not_enum<abstract>();
    test_is_not_enum<public_abstract>();
    test_is_not_enum<private_abstract>();
    test_is_not_enum<protected_abstract>();
    test_is_not_enum<abstract_template<int>>();
    test_is_not_enum<abstract_template<double>>();
    test_is_not_enum<abstract_template<class_type>>();
    test_is_not_enum<abstract_template<incomplete_type>>();
    test_is_not_enum<public_abstract_deleted_destructor>();
    test_is_not_enum<protected_abstract_deleted_destructor>();
    test_is_not_enum<private_abstract_deleted_destructor>();
    test_is_not_enum<final_type>();
    test_is_not_enum<final_derived>();
    test_is_not_enum<public_destructor>();
    test_is_not_enum<protected_destructor>();
    test_is_not_enum<private_destructor>();
    test_is_not_enum<virtual_public_destructor>();
    test_is_not_enum<virtual_protected_destructor>();
    test_is_not_enum<virtual_private_destructor>();
    test_is_not_enum<pure_public_destructor>();
    test_is_not_enum<pure_protected_destructor>();
    test_is_not_enum<pure_private_destructor>();
    test_is_not_enum<deleted_public_destructor>();
    test_is_not_enum<deleted_protected_destructor>();
    test_is_not_enum<deleted_private_destructor>();
    test_is_not_enum<deleted_virtual_public_destructor>();
    test_is_not_enum<deleted_virtual_protected_destructor>();
    test_is_not_enum<deleted_virtual_private_destructor>();
    test_is_not_enum<explicit_class>();
    test_is_not_enum<nothrow_explicit_class>();
    test_is_not_enum<throw_explicit_class>();
    test_is_not_enum<throw_default_class>();
    test_is_not_enum<throw_copy_constructible_class>();
    test_is_not_enum<throw_move_constructible_class>();
    test_is_not_enum<throw_destructor>();
    test_is_not_enum<noexcept_explicit_class>();
    test_is_not_enum<except_explicit_class>();
    test_is_not_enum<noexcept_default_class>();
    test_is_not_enum<except_default_class>();
    test_is_not_enum<noexcept_copy_constructible_class>();
    test_is_not_enum<except_copy_constructible_class>();
    test_is_not_enum<noexcept_move_constructible_class>();
    test_is_not_enum<except_move_constructible_class>();
    test_is_not_enum<noexcept_copy_assign_class>();
    test_is_not_enum<except_copy_assign_class>();
    test_is_not_enum<noexcept_move_assign_class>();
    test_is_not_enum<except_move_assign_class>();
    test_is_not_enum<deleted_copy_assign_class>();
    test_is_not_enum<deleted_move_assign_class>();
    test_is_not_enum<noexcept_move_constructible_and_assignable_class>();
    test_is_not_enum<except_move_constructible_noexcept_move_assign_class>();
    test_is_not_enum<noexcept_move_constructible_except_move_assign_class>();
    test_is_not_enum<except_move_constructible_and_assign_class>();
    test_is_not_enum<implicit_to<int>>();
    test_is_not_enum<implicit_to<float>>();
    test_is_not_enum<implicit_to<class_type>>();
    test_is_not_enum<deleted_implicit_to<int>>();
    test_is_not_enum<deleted_implicit_to<float>>();
    test_is_not_enum<deleted_implicit_to<class_type>>();
    test_is_not_enum<explicit_to<int>>();
    test_is_not_enum<explicit_to<float>>();
    test_is_not_enum<explicit_to<class_type>>();
    test_is_not_enum<deleted_explicit_to<int>>();
    test_is_not_enum<deleted_explicit_to<float>>();
    test_is_not_enum<deleted_explicit_to<class_type>>();
    test_is_not_enum<ellipsis>();
    test_is_not_enum<deleted_ellipsis>();
    test_is_not_enum<copy_constructible_only_type>();
    test_is_not_enum<move_constructible_only_type>();
    test_is_not_enum<overloaded_operators>();
    test_is_not_enum<public_int_member>();
    test_is_not_enum<protected_int_member>();
    test_is_not_enum<private_int_member>();
    test_is_not_enum<public_static_int_member>();
    test_is_not_enum<protected_static_int_member>();
    test_is_not_enum<private_static_int_member>();
    test_is_not_enum<public_template_member<int>>();
    test_is_not_enum<public_template_member<float>>();
    test_is_not_enum<public_template_member<class_type>>();
    test_is_not_enum<protected_template_member<int>>();
    test_is_not_enum<protected_template_member<float>>();
    test_is_not_enum<protected_template_member<class_type>>();
    test_is_not_enum<private_template_member<int>>();
    test_is_not_enum<private_template_member<float>>();
    test_is_not_enum<private_template_member<class_type>>();
    test_is_not_enum<public_static_template_member<int>>();
    test_is_not_enum<public_static_template_member<float>>();
    test_is_not_enum<public_static_template_member<class_type>>();
    test_is_not_enum<protected_static_template_member<int>>();
    test_is_not_enum<protected_static_template_member<float>>();
    test_is_not_enum<protected_static_template_member<class_type>>();
    test_is_not_enum<private_static_template_member<int>>();
    test_is_not_enum<private_static_template_member<float>>();
    test_is_not_enum<private_static_template_member<class_type>>();
    test_is_not_enum<cannot_instantiate<int>>();
    test_is_not_enum<cannot_instantiate<float>>();
    test_is_not_enum<cannot_instantiate<class_type>>();
    test_is_not_enum<natural_alignment>();
    test_is_enum<Enum>();
    test_is_enum<EnumSigned>();
    test_is_enum<EnumUnsigned>();
    test_is_enum<EnumClass>();
    test_is_enum<EnumStruct>();
    test_is_not_enum<function_type>();
    test_is_not_enum<function_ptr>();
    test_is_not_enum<member_object_ptr>();
    test_is_not_enum<member_function_ptr>();
    test_is_not_enum<lambda_type>();
    test_is_not_enum<lambda_noexcept_type>();
    test_is_not_enum<lambda_throws_type>();
    test_is_not_enum<incomplete_type>();
    test_is_not_enum<incomplete_template<void>>();
    test_is_not_enum<incomplete_template<int>>();
    test_is_not_enum<incomplete_template<class_type>>();
    test_is_not_enum<incomplete_template<incomplete_type>>();
    test_is_not_enum<incomplete_variadic_template<>>();
    test_is_not_enum<incomplete_variadic_template<void>>();
    test_is_not_enum<incomplete_variadic_template<int>>();
    test_is_not_enum<incomplete_variadic_template<class_type>>();
    test_is_not_enum<incomplete_variadic_template<incomplete_type>>();
    test_is_not_enum<incomplete_variadic_template<int, void, class_type, volatile char[]>>();
    test_is_not_enum<incomplete_union>();
    test_is_enum<IncompleteEnumSigned>();
    test_is_enum<IncompleteEnumUnsigned>();
    test_is_enum<IncompleteEnumClass>();
    test_is_enum<IncompleteEnumStruct>();
    test_is_not_enum<int class_type::*>();
    test_is_not_enum<float class_type::*>();
    test_is_not_enum<void * class_type::*>();
    test_is_not_enum<int * class_type::*>();
    test_is_not_enum<Enum class_type::*>();
    test_is_not_enum<not_empty class_type::*>();
    test_is_not_enum<int class_type::*&>();
    test_is_not_enum<float class_type::*&>();
    test_is_not_enum<void * class_type::*&>();
    test_is_not_enum<int * class_type::*&>();
    test_is_not_enum<Enum class_type::*&>();
    test_is_not_enum<not_empty class_type::*&>();
    test_is_not_enum<int class_type::*&&>();
    test_is_not_enum<float class_type::*&&>();
    test_is_not_enum<void * class_type::*&&>();
    test_is_not_enum<int * class_type::*&&>();
    test_is_not_enum<Enum class_type::*&&>();
    test_is_not_enum<not_empty class_type::*&&>();
    test_is_not_enum<non_default_constructible>();
    test_is_not_enum<non_copy_constructible>();
    test_is_not_enum<non_move_constructible>();
    test_is_not_enum<non_copy_assignable>();
    test_is_not_enum<non_move_assignable>();
    test_is_not_enum<non_assignable>();
    test_is_not_enum<non_copyable>();
    test_is_not_enum<non_moveable>();
    test_is_not_enum<non_constructible>();
    test_is_not_enum<non_destructible>();
    test_is_not_enum<tracked>();
    test_is_not_enum<trap_constructible>();
    test_is_not_enum<trap_implicit_conversion>();
    test_is_not_enum<trap_comma>();
    test_is_not_enum<trap_call>();
    test_is_not_enum<trap_self_assign>();
    test_is_not_enum<trap_deref>();
    test_is_not_enum<trap_array_subscript>();

#if PHI_HAS_EXTENSION_ZERO_SIZE_ARRAY() && PHI_SUPPORTS_IS_ENUM()
    PHI_CLANG_SUPPRESS_WARNING_WITH_PUSH("-Wzero-length-array")
    PHI_GCC_SUPPRESS_WARNING_WITH_PUSH("-Wpedantic")

    test_is_not_enum<int[0]>();

    PHI_GCC_SUPPRESS_WARNING_POP()
    PHI_CLANG_SUPPRESS_WARNING_POP()
#endif

    test_is_not_enum<void()>();
    test_is_not_enum<void()&>();
    test_is_not_enum<void() &&>();
    test_is_not_enum<void() const>();
    test_is_not_enum<void() const&>();
    test_is_not_enum<void() const&&>();
    test_is_not_enum<void() volatile>();
    test_is_not_enum<void() volatile&>();
    test_is_not_enum<void() volatile&&>();
    test_is_not_enum<void() const volatile>();
    test_is_not_enum<void() const volatile&>();
    test_is_not_enum<void() const volatile&&>();
    test_is_not_enum<void() noexcept>();
    test_is_not_enum<void() & noexcept>();
    test_is_not_enum<void() && noexcept>();
    test_is_not_enum<void() const noexcept>();
    test_is_not_enum<void() const & noexcept>();
    test_is_not_enum<void() const && noexcept>();
    test_is_not_enum<void() volatile noexcept>();
    test_is_not_enum<void() volatile & noexcept>();
    test_is_not_enum<void() volatile && noexcept>();
    test_is_not_enum<void() const volatile noexcept>();
    test_is_not_enum<void() const volatile & noexcept>();
    test_is_not_enum<void() const volatile && noexcept>();

    test_is_not_enum<void(int)>();
    test_is_not_enum<void(int)&>();
    test_is_not_enum<void(int) &&>();
    test_is_not_enum<void(int) const>();
    test_is_not_enum<void(int) const&>();
    test_is_not_enum<void(int) const&&>();
    test_is_not_enum<void(int) volatile>();
    test_is_not_enum<void(int) volatile&>();
    test_is_not_enum<void(int) volatile&&>();
    test_is_not_enum<void(int) const volatile>();
    test_is_not_enum<void(int) const volatile&>();
    test_is_not_enum<void(int) const volatile&&>();
    test_is_not_enum<void(int) noexcept>();
    test_is_not_enum<void(int) & noexcept>();
    test_is_not_enum<void(int) && noexcept>();
    test_is_not_enum<void(int) const noexcept>();
    test_is_not_enum<void(int) const & noexcept>();
    test_is_not_enum<void(int) const && noexcept>();
    test_is_not_enum<void(int) volatile noexcept>();
    test_is_not_enum<void(int) volatile & noexcept>();
    test_is_not_enum<void(int) volatile && noexcept>();
    test_is_not_enum<void(int) const volatile noexcept>();
    test_is_not_enum<void(int) const volatile & noexcept>();
    test_is_not_enum<void(int) const volatile && noexcept>();

    test_is_not_enum<void(...)>();
    test_is_not_enum<void(...)&>();
    test_is_not_enum<void(...) &&>();
    test_is_not_enum<void(...) const>();
    test_is_not_enum<void(...) const&>();
    test_is_not_enum<void(...) const&&>();
    test_is_not_enum<void(...) volatile>();
    test_is_not_enum<void(...) volatile&>();
    test_is_not_enum<void(...) volatile&&>();
    test_is_not_enum<void(...) const volatile>();
    test_is_not_enum<void(...) const volatile&>();
    test_is_not_enum<void(...) const volatile&&>();
    test_is_not_enum<void(...) noexcept>();
    test_is_not_enum<void(...) & noexcept>();
    test_is_not_enum<void(...) && noexcept>();
    test_is_not_enum<void(...) const noexcept>();
    test_is_not_enum<void(...) const & noexcept>();
    test_is_not_enum<void(...) const && noexcept>();
    test_is_not_enum<void(...) volatile noexcept>();
    test_is_not_enum<void(...) volatile & noexcept>();
    test_is_not_enum<void(...) volatile && noexcept>();
    test_is_not_enum<void(...) const volatile noexcept>();
    test_is_not_enum<void(...) const volatile & noexcept>();
    test_is_not_enum<void(...) const volatile && noexcept>();

    test_is_not_enum<void(int, ...)>();
    test_is_not_enum<void(int, ...)&>();
    test_is_not_enum<void(int, ...) &&>();
    test_is_not_enum<void(int, ...) const>();
    test_is_not_enum<void(int, ...) const&>();
    test_is_not_enum<void(int, ...) const&&>();
    test_is_not_enum<void(int, ...) volatile>();
    test_is_not_enum<void(int, ...) volatile&>();
    test_is_not_enum<void(int, ...) volatile&&>();
    test_is_not_enum<void(int, ...) const volatile>();
    test_is_not_enum<void(int, ...) const volatile&>();
    test_is_not_enum<void(int, ...) const volatile&&>();
    test_is_not_enum<void(int, ...) noexcept>();
    test_is_not_enum<void(int, ...) & noexcept>();
    test_is_not_enum<void(int, ...) && noexcept>();
    test_is_not_enum<void(int, ...) const noexcept>();
    test_is_not_enum<void(int, ...) const & noexcept>();
    test_is_not_enum<void(int, ...) const && noexcept>();
    test_is_not_enum<void(int, ...) volatile noexcept>();
    test_is_not_enum<void(int, ...) volatile & noexcept>();
    test_is_not_enum<void(int, ...) volatile && noexcept>();
    test_is_not_enum<void(int, ...) const volatile noexcept>();
    test_is_not_enum<void(int, ...) const volatile & noexcept>();
    test_is_not_enum<void(int, ...) const volatile && noexcept>();

    test_is_not_enum<int()>();
    test_is_not_enum<int()&>();
    test_is_not_enum<int() &&>();
    test_is_not_enum<int() const>();
    test_is_not_enum<int() const&>();
    test_is_not_enum<int() const&&>();
    test_is_not_enum<int() volatile>();
    test_is_not_enum<int() volatile&>();
    test_is_not_enum<int() volatile&&>();
    test_is_not_enum<int() const volatile>();
    test_is_not_enum<int() const volatile&>();
    test_is_not_enum<int() const volatile&&>();
    test_is_not_enum<int() noexcept>();
    test_is_not_enum<int() & noexcept>();
    test_is_not_enum<int() && noexcept>();
    test_is_not_enum<int() const noexcept>();
    test_is_not_enum<int() const & noexcept>();
    test_is_not_enum<int() const && noexcept>();
    test_is_not_enum<int() volatile noexcept>();
    test_is_not_enum<int() volatile & noexcept>();
    test_is_not_enum<int() volatile && noexcept>();
    test_is_not_enum<int() const volatile noexcept>();
    test_is_not_enum<int() const volatile & noexcept>();
    test_is_not_enum<int() const volatile && noexcept>();

    test_is_not_enum<int(int)>();
    test_is_not_enum<int(int)&>();
    test_is_not_enum<int(int) &&>();
    test_is_not_enum<int(int) const>();
    test_is_not_enum<int(int) const&>();
    test_is_not_enum<int(int) const&&>();
    test_is_not_enum<int(int) volatile>();
    test_is_not_enum<int(int) volatile&>();
    test_is_not_enum<int(int) volatile&&>();
    test_is_not_enum<int(int) const volatile>();
    test_is_not_enum<int(int) const volatile&>();
    test_is_not_enum<int(int) const volatile&&>();
    test_is_not_enum<int(int) noexcept>();
    test_is_not_enum<int(int) & noexcept>();
    test_is_not_enum<int(int) && noexcept>();
    test_is_not_enum<int(int) const noexcept>();
    test_is_not_enum<int(int) const & noexcept>();
    test_is_not_enum<int(int) const && noexcept>();
    test_is_not_enum<int(int) volatile noexcept>();
    test_is_not_enum<int(int) volatile & noexcept>();
    test_is_not_enum<int(int) volatile && noexcept>();
    test_is_not_enum<int(int) const volatile noexcept>();
    test_is_not_enum<int(int) const volatile & noexcept>();
    test_is_not_enum<int(int) const volatile && noexcept>();

    test_is_not_enum<int(...)>();
    test_is_not_enum<int(...)&>();
    test_is_not_enum<int(...) &&>();
    test_is_not_enum<int(...) const>();
    test_is_not_enum<int(...) const&>();
    test_is_not_enum<int(...) const&&>();
    test_is_not_enum<int(...) volatile>();
    test_is_not_enum<int(...) volatile&>();
    test_is_not_enum<int(...) volatile&&>();
    test_is_not_enum<int(...) const volatile>();
    test_is_not_enum<int(...) const volatile&>();
    test_is_not_enum<int(...) const volatile&&>();
    test_is_not_enum<int(...) noexcept>();
    test_is_not_enum<int(...) & noexcept>();
    test_is_not_enum<int(...) && noexcept>();
    test_is_not_enum<int(...) const noexcept>();
    test_is_not_enum<int(...) const & noexcept>();
    test_is_not_enum<int(...) const && noexcept>();
    test_is_not_enum<int(...) volatile noexcept>();
    test_is_not_enum<int(...) volatile & noexcept>();
    test_is_not_enum<int(...) volatile && noexcept>();
    test_is_not_enum<int(...) const volatile noexcept>();
    test_is_not_enum<int(...) const volatile & noexcept>();
    test_is_not_enum<int(...) const volatile && noexcept>();

    test_is_not_enum<int(int, ...)>();
    test_is_not_enum<int(int, ...)&>();
    test_is_not_enum<int(int, ...) &&>();
    test_is_not_enum<int(int, ...) const>();
    test_is_not_enum<int(int, ...) const&>();
    test_is_not_enum<int(int, ...) const&&>();
    test_is_not_enum<int(int, ...) volatile>();
    test_is_not_enum<int(int, ...) volatile&>();
    test_is_not_enum<int(int, ...) volatile&&>();
    test_is_not_enum<int(int, ...) const volatile>();
    test_is_not_enum<int(int, ...) const volatile&>();
    test_is_not_enum<int(int, ...) const volatile&&>();
    test_is_not_enum<int(int, ...) noexcept>();
    test_is_not_enum<int(int, ...) & noexcept>();
    test_is_not_enum<int(int, ...) && noexcept>();
    test_is_not_enum<int(int, ...) const noexcept>();
    test_is_not_enum<int(int, ...) const & noexcept>();
    test_is_not_enum<int(int, ...) const && noexcept>();
    test_is_not_enum<int(int, ...) volatile noexcept>();
    test_is_not_enum<int(int, ...) volatile & noexcept>();
    test_is_not_enum<int(int, ...) volatile && noexcept>();
    test_is_not_enum<int(int, ...) const volatile noexcept>();
    test_is_not_enum<int(int, ...) const volatile & noexcept>();
    test_is_not_enum<int(int, ...) const volatile && noexcept>();

    test_is_not_enum<void (*)()>();
    test_is_not_enum<void (*)() noexcept>();

    test_is_not_enum<void (*)(int)>();
    test_is_not_enum<void (*)(int) noexcept>();

    test_is_not_enum<void (*)(...)>();
    test_is_not_enum<void (*)(...) noexcept>();

    test_is_not_enum<void (*)(int, ...)>();
    test_is_not_enum<void (*)(int, ...) noexcept>();

    test_is_not_enum<int (*)()>();
    test_is_not_enum<int (*)() noexcept>();

    test_is_not_enum<int (*)(int)>();
    test_is_not_enum<int (*)(int) noexcept>();

    test_is_not_enum<int (*)(...)>();
    test_is_not_enum<int (*)(...) noexcept>();

    test_is_not_enum<int (*)(int, ...)>();
    test_is_not_enum<int (*)(int, ...) noexcept>();

    test_is_not_enum<void (&)()>();
    test_is_not_enum<void (&)() noexcept>();

    test_is_not_enum<void (&)(int)>();
    test_is_not_enum<void (&)(int) noexcept>();

    test_is_not_enum<void (&)(...)>();
    test_is_not_enum<void (&)(...) noexcept>();

    test_is_not_enum<void (&)(int, ...)>();
    test_is_not_enum<void (&)(int, ...) noexcept>();

    test_is_not_enum<int (&)()>();
    test_is_not_enum<int (&)() noexcept>();

    test_is_not_enum<int (&)(int)>();
    test_is_not_enum<int (&)(int) noexcept>();

    test_is_not_enum<int (&)(...)>();
    test_is_not_enum<int (&)(...) noexcept>();

    test_is_not_enum<int (&)(int, ...)>();
    test_is_not_enum<int (&)(int, ...) noexcept>();

    test_is_not_enum<void (&&)()>();
    test_is_not_enum<void (&&)() noexcept>();

    test_is_not_enum<void (&&)(int)>();
    test_is_not_enum<void (&&)(int) noexcept>();

    test_is_not_enum<void (&&)(...)>();
    test_is_not_enum<void (&&)(...) noexcept>();

    test_is_not_enum<void (&&)(int, ...)>();
    test_is_not_enum<void (&&)(int, ...) noexcept>();

    test_is_not_enum<int (&&)()>();
    test_is_not_enum<int (&&)() noexcept>();

    test_is_not_enum<int (&&)(int)>();
    test_is_not_enum<int (&&)(int) noexcept>();

    test_is_not_enum<int (&&)(...)>();
    test_is_not_enum<int (&&)(...) noexcept>();

    test_is_not_enum<int (&&)(int, ...)>();
    test_is_not_enum<int (&&)(int, ...) noexcept>();

    test_is_not_enum<void (class_type::*)()>();
    test_is_not_enum<void (class_type::*)()&>();
    test_is_not_enum<void (class_type::*)() &&>();
    test_is_not_enum<void (class_type::*)() const>();
    test_is_not_enum<void (class_type::*)() const&>();
    test_is_not_enum<void (class_type::*)() const&&>();
    test_is_not_enum<void (class_type::*)() noexcept>();
    test_is_not_enum<void (class_type::*)() & noexcept>();
    test_is_not_enum<void (class_type::*)() && noexcept>();
    test_is_not_enum<void (class_type::*)() const noexcept>();
    test_is_not_enum<void (class_type::*)() const & noexcept>();
    test_is_not_enum<void (class_type::*)() const && noexcept>();

    test_is_not_enum<void (class_type::*)(int)>();
    test_is_not_enum<void (class_type::*)(int)&>();
    test_is_not_enum<void (class_type::*)(int) &&>();
    test_is_not_enum<void (class_type::*)(int) const>();
    test_is_not_enum<void (class_type::*)(int) const&>();
    test_is_not_enum<void (class_type::*)(int) const&&>();
    test_is_not_enum<void (class_type::*)(int) noexcept>();
    test_is_not_enum<void (class_type::*)(int) & noexcept>();
    test_is_not_enum<void (class_type::*)(int) && noexcept>();
    test_is_not_enum<void (class_type::*)(int) const noexcept>();
    test_is_not_enum<void (class_type::*)(int) const & noexcept>();
    test_is_not_enum<void (class_type::*)(int) const && noexcept>();

    test_is_not_enum<void (class_type::*)(...)>();
    test_is_not_enum<void (class_type::*)(...)&>();
    test_is_not_enum<void (class_type::*)(...) &&>();
    test_is_not_enum<void (class_type::*)(...) const>();
    test_is_not_enum<void (class_type::*)(...) const&>();
    test_is_not_enum<void (class_type::*)(...) const&&>();
    test_is_not_enum<void (class_type::*)(...) noexcept>();
    test_is_not_enum<void (class_type::*)(...) & noexcept>();
    test_is_not_enum<void (class_type::*)(...) && noexcept>();
    test_is_not_enum<void (class_type::*)(...) const noexcept>();
    test_is_not_enum<void (class_type::*)(...) const & noexcept>();
    test_is_not_enum<void (class_type::*)(...) const && noexcept>();

    test_is_not_enum<void (class_type::*)(int, ...)>();
    test_is_not_enum<void (class_type::*)(int, ...)&>();
    test_is_not_enum<void (class_type::*)(int, ...) &&>();
    test_is_not_enum<void (class_type::*)(int, ...) const>();
    test_is_not_enum<void (class_type::*)(int, ...) const&>();
    test_is_not_enum<void (class_type::*)(int, ...) const&&>();
    test_is_not_enum<void (class_type::*)(int, ...) noexcept>();
    test_is_not_enum<void (class_type::*)(int, ...) & noexcept>();
    test_is_not_enum<void (class_type::*)(int, ...) && noexcept>();
    test_is_not_enum<void (class_type::*)(int, ...) const noexcept>();
    test_is_not_enum<void (class_type::*)(int, ...) const & noexcept>();
    test_is_not_enum<void (class_type::*)(int, ...) const && noexcept>();

    test_is_not_enum<int (class_type::*)()>();
    test_is_not_enum<int (class_type::*)()&>();
    test_is_not_enum<int (class_type::*)() &&>();
    test_is_not_enum<int (class_type::*)() const>();
    test_is_not_enum<int (class_type::*)() const&>();
    test_is_not_enum<int (class_type::*)() const&&>();
    test_is_not_enum<int (class_type::*)() noexcept>();
    test_is_not_enum<int (class_type::*)() & noexcept>();
    test_is_not_enum<int (class_type::*)() && noexcept>();
    test_is_not_enum<int (class_type::*)() const noexcept>();
    test_is_not_enum<int (class_type::*)() const & noexcept>();
    test_is_not_enum<int (class_type::*)() const && noexcept>();

    test_is_not_enum<int (class_type::*)(int)>();
    test_is_not_enum<int (class_type::*)(int)&>();
    test_is_not_enum<int (class_type::*)(int) &&>();
    test_is_not_enum<int (class_type::*)(int) const>();
    test_is_not_enum<int (class_type::*)(int) const&>();
    test_is_not_enum<int (class_type::*)(int) const&&>();
    test_is_not_enum<int (class_type::*)(int) noexcept>();
    test_is_not_enum<int (class_type::*)(int) & noexcept>();
    test_is_not_enum<int (class_type::*)(int) && noexcept>();
    test_is_not_enum<int (class_type::*)(int) const noexcept>();
    test_is_not_enum<int (class_type::*)(int) const & noexcept>();
    test_is_not_enum<int (class_type::*)(int) const && noexcept>();

    test_is_not_enum<int (class_type::*)(...)>();
    test_is_not_enum<int (class_type::*)(...)&>();
    test_is_not_enum<int (class_type::*)(...) &&>();
    test_is_not_enum<int (class_type::*)(...) const>();
    test_is_not_enum<int (class_type::*)(...) const&>();
    test_is_not_enum<int (class_type::*)(...) const&&>();
    test_is_not_enum<int (class_type::*)(...) noexcept>();
    test_is_not_enum<int (class_type::*)(...) & noexcept>();
    test_is_not_enum<int (class_type::*)(...) && noexcept>();
    test_is_not_enum<int (class_type::*)(...) const noexcept>();
    test_is_not_enum<int (class_type::*)(...) const & noexcept>();
    test_is_not_enum<int (class_type::*)(...) const && noexcept>();

    test_is_not_enum<int (class_type::*)(int, ...)>();
    test_is_not_enum<int (class_type::*)(int, ...)&>();
    test_is_not_enum<int (class_type::*)(int, ...) &&>();
    test_is_not_enum<int (class_type::*)(int, ...) const>();
    test_is_not_enum<int (class_type::*)(int, ...) const&>();
    test_is_not_enum<int (class_type::*)(int, ...) const&&>();
    test_is_not_enum<int (class_type::*)(int, ...) noexcept>();
    test_is_not_enum<int (class_type::*)(int, ...) & noexcept>();
    test_is_not_enum<int (class_type::*)(int, ...) && noexcept>();
    test_is_not_enum<int (class_type::*)(int, ...) const noexcept>();
    test_is_not_enum<int (class_type::*)(int, ...) const & noexcept>();
    test_is_not_enum<int (class_type::*)(int, ...) const && noexcept>();
}
