#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/compiler_support/cpp_standard.hpp>
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
#include <phi/type_traits/is_unsafe_floating_point.hpp>
#include <phi/type_traits/is_void.hpp>
#include <type_traits>
#include <vector>

template <typename TypeT>
void test_is_unsafe_floating_point_non_std_impl()
{
    STATIC_REQUIRE(phi::is_arithmetic<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_array<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_bool<TypeT>::value);
#if PHI_HAS_WORKING_IS_CLASS()
    STATIC_REQUIRE_FALSE(phi::is_class<TypeT>::value);
#endif
    STATIC_REQUIRE_FALSE(phi::is_compound<TypeT>::value);
#if PHI_HAS_WORKING_IS_ENUM()
    STATIC_REQUIRE_FALSE(phi::is_enum<TypeT>::value);
#endif
    STATIC_REQUIRE(phi::is_unsafe_floating_point<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_function<TypeT>::value);
    STATIC_REQUIRE(phi::is_fundamental<TypeT>::value);
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

    STATIC_REQUIRE_FALSE(phi::is_not_unsafe_floating_point<TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_arithmetic_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_array_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_bool_v<TypeT>);
#    if PHI_HAS_WORKING_IS_CLASS()
    STATIC_REQUIRE_FALSE(phi::is_class_v<TypeT>);
#    endif
    STATIC_REQUIRE_FALSE(phi::is_compound_v<TypeT>);
#    if PHI_HAS_WORKING_IS_ENUM()
    STATIC_REQUIRE_FALSE(phi::is_enum_v<TypeT>);
#    endif
    STATIC_REQUIRE(phi::is_unsafe_floating_point_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_function_v<TypeT>);
    STATIC_REQUIRE(phi::is_fundamental_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_integer_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_integral_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_lvalue_reference_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_member_function_pointer_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_member_object_pointer_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_member_pointer_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_null_pointer_v<TypeT>);
#    if PHI_HAS_WORKING_IS_SCALAR()
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

    STATIC_REQUIRE_FALSE(phi::is_not_unsafe_floating_point_v<TypeT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_unsafe_floating_point<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_unsafe_floating_point<TypeT>);
}

template <typename TypeT>
void test_is_unsafe_floating_point_impl()
{
    test_is_unsafe_floating_point_non_std_impl<TypeT>();

    // Standard compatibility
    STATIC_REQUIRE(std::is_floating_point<TypeT>::value);
#if PHI_CPP_STANDARD_IS_ATLEAST(17) && PHI_COMPILER_WORKAROUND(GCC, 7, 0, 0)
    STATIC_REQUIRE(std::is_floating_point_v<TypeT>);
#endif
}

template <typename TypeT>
void test_is_unsafe_floating_point()
{
    test_is_unsafe_floating_point_impl<TypeT>();
    test_is_unsafe_floating_point_impl<const TypeT>();
    test_is_unsafe_floating_point_impl<volatile TypeT>();
    test_is_unsafe_floating_point_impl<const volatile TypeT>();
}

template <typename TypeT>
void test_is_unsafe_floating_point_non_std()
{
    test_is_unsafe_floating_point_non_std_impl<TypeT>();
    test_is_unsafe_floating_point_non_std_impl<const TypeT>();
    test_is_unsafe_floating_point_non_std_impl<volatile TypeT>();
    test_is_unsafe_floating_point_non_std_impl<const volatile TypeT>();
}

template <typename TypeT>
void test_is_not_unsafe_floating_point_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_unsafe_floating_point<TypeT>::value);
    STATIC_REQUIRE(phi::is_not_unsafe_floating_point<TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_unsafe_floating_point_v<TypeT>);
    STATIC_REQUIRE(phi::is_not_unsafe_floating_point_v<TypeT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_unsafe_floating_point<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_unsafe_floating_point<TypeT>);

    // Standard compatibility
    STATIC_REQUIRE_FALSE(std::is_floating_point<TypeT>::value);
#if PHI_CPP_STANDARD_IS_ATLEAST(17) && PHI_COMPILER_WORKAROUND(GCC, 7, 0, 0)
    STATIC_REQUIRE_FALSE(std::is_floating_point_v<TypeT>);
#endif
}

template <typename TypeT>
void test_is_not_unsafe_floating_point()
{
    test_is_not_unsafe_floating_point_impl<TypeT>();
    test_is_not_unsafe_floating_point_impl<const TypeT>();
    test_is_not_unsafe_floating_point_impl<volatile TypeT>();
    test_is_not_unsafe_floating_point_impl<const volatile TypeT>();
}

TEST_CASE("is_unsafe_floating_point")
{
// Extended floating point types
#if 0 // TODO:
#    if PHI_HAS_EXTENSION_FLOAT16()
    test_is_unsafe_floating_point_non_std<_Float16>();
    test_is_not_unsafe_floating_point<phi::floating_point<_Float16>>();
#    endif

#    if PHI_HAS_EXTENSION_FP16()
    test_is_unsafe_floating_point_non_std<__fp16>();
    test_is_not_unsafe_floating_point<phi::floating_point<__fp16>>();
#    endif

#    if PHI_HAS_EXTENSION_FLOAT128()
    test_is_unsafe_floating_point_non_std<__float128>();
    test_is_not_unsafe_floating_point<phi::floating_point<__float128>>();
#    endif
#endif

    test_is_not_unsafe_floating_point<void>();
    test_is_not_unsafe_floating_point<phi::nullptr_t>();
    test_is_not_unsafe_floating_point<bool>();
    test_is_not_unsafe_floating_point<char>();
    test_is_not_unsafe_floating_point<signed char>();
    test_is_not_unsafe_floating_point<unsigned char>();
    test_is_not_unsafe_floating_point<short>();
    test_is_not_unsafe_floating_point<unsigned short>();
    test_is_not_unsafe_floating_point<int>();
    test_is_not_unsafe_floating_point<unsigned int>();
    test_is_not_unsafe_floating_point<long>();
    test_is_not_unsafe_floating_point<unsigned long>();
    test_is_not_unsafe_floating_point<long long>();
    test_is_not_unsafe_floating_point<unsigned long long>();
    test_is_unsafe_floating_point<float>();
    test_is_unsafe_floating_point<double>();
    test_is_unsafe_floating_point<long double>();
    test_is_not_unsafe_floating_point<char8_t>();
    test_is_not_unsafe_floating_point<char16_t>();
    test_is_not_unsafe_floating_point<char32_t>();
    test_is_not_unsafe_floating_point<wchar_t>();

    test_is_not_unsafe_floating_point<phi::boolean>();
    test_is_not_unsafe_floating_point<phi::integer<signed char>>();
    test_is_not_unsafe_floating_point<phi::integer<unsigned char>>();
    test_is_not_unsafe_floating_point<phi::integer<short>>();
    test_is_not_unsafe_floating_point<phi::integer<unsigned short>>();
    test_is_not_unsafe_floating_point<phi::integer<int>>();
    test_is_not_unsafe_floating_point<phi::integer<unsigned int>>();
    test_is_not_unsafe_floating_point<phi::integer<long>>();
    test_is_not_unsafe_floating_point<phi::integer<unsigned long>>();
    test_is_not_unsafe_floating_point<phi::integer<long long>>();
    test_is_not_unsafe_floating_point<phi::integer<unsigned long long>>();
    test_is_not_unsafe_floating_point<phi::floating_point<float>>();
    test_is_not_unsafe_floating_point<phi::floating_point<double>>();
    test_is_not_unsafe_floating_point<phi::floating_point<long double>>();

    test_is_not_unsafe_floating_point<std::vector<int>>();
    test_is_not_unsafe_floating_point<phi::scope_ptr<int>>();

    test_is_not_unsafe_floating_point<int&>();
    test_is_not_unsafe_floating_point<const int&>();
    test_is_not_unsafe_floating_point<volatile int&>();
    test_is_not_unsafe_floating_point<const volatile int&>();
    test_is_not_unsafe_floating_point<int&&>();
    test_is_not_unsafe_floating_point<const int&&>();
    test_is_not_unsafe_floating_point<volatile int&&>();
    test_is_not_unsafe_floating_point<const volatile int&&>();
    test_is_not_unsafe_floating_point<int*>();
    test_is_not_unsafe_floating_point<const int*>();
    test_is_not_unsafe_floating_point<volatile int*>();
    test_is_not_unsafe_floating_point<const volatile int*>();
    test_is_not_unsafe_floating_point<int**>();
    test_is_not_unsafe_floating_point<const int**>();
    test_is_not_unsafe_floating_point<volatile int**>();
    test_is_not_unsafe_floating_point<const volatile int**>();
    test_is_not_unsafe_floating_point<int*&>();
    test_is_not_unsafe_floating_point<const int*&>();
    test_is_not_unsafe_floating_point<volatile int*&>();
    test_is_not_unsafe_floating_point<const volatile int*&>();
    test_is_not_unsafe_floating_point<int*&&>();
    test_is_not_unsafe_floating_point<const int*&&>();
    test_is_not_unsafe_floating_point<volatile int*&&>();
    test_is_not_unsafe_floating_point<const volatile int*&&>();
    test_is_not_unsafe_floating_point<void*>();
    test_is_not_unsafe_floating_point<char[3]>();
    test_is_not_unsafe_floating_point<char[]>();
    test_is_not_unsafe_floating_point<char* [3]>();
    test_is_not_unsafe_floating_point<char*[]>();
    test_is_not_unsafe_floating_point<int(*)[3]>();
    test_is_not_unsafe_floating_point<int(*)[]>();
    test_is_not_unsafe_floating_point<int(&)[3]>();
    test_is_not_unsafe_floating_point<int(&)[]>();
    test_is_not_unsafe_floating_point<int(&&)[3]>();
    test_is_not_unsafe_floating_point<int(&&)[]>();
    test_is_not_unsafe_floating_point<char[3][2]>();
    test_is_not_unsafe_floating_point<char[][2]>();
    test_is_not_unsafe_floating_point<char* [3][2]>();
    test_is_not_unsafe_floating_point<char*[][2]>();
    test_is_not_unsafe_floating_point<int(*)[3][2]>();
    test_is_not_unsafe_floating_point<int(*)[][2]>();
    test_is_not_unsafe_floating_point<int(&)[3][2]>();
    test_is_not_unsafe_floating_point<int(&)[][2]>();
    test_is_not_unsafe_floating_point<int(&&)[3][2]>();
    test_is_not_unsafe_floating_point<int(&&)[][2]>();
    test_is_not_unsafe_floating_point<class_type>();
    test_is_not_unsafe_floating_point<class_type[]>();
    test_is_not_unsafe_floating_point<class_type[2]>();
    test_is_not_unsafe_floating_point<template_type<void>>();
    test_is_not_unsafe_floating_point<template_type<int>>();
    test_is_not_unsafe_floating_point<template_type<class_type>>();
    test_is_not_unsafe_floating_point<template_type<incomplete_type>>();
    test_is_not_unsafe_floating_point<variadic_template<>>();
    test_is_not_unsafe_floating_point<variadic_template<void>>();
    test_is_not_unsafe_floating_point<variadic_template<int>>();
    test_is_not_unsafe_floating_point<variadic_template<class_type>>();
    test_is_not_unsafe_floating_point<variadic_template<incomplete_type>>();
    test_is_not_unsafe_floating_point<variadic_template<int, void, class_type, volatile char[]>>();
    test_is_not_unsafe_floating_point<public_derived_from<base>>();
    test_is_not_unsafe_floating_point<public_derived_from<derived>>();
    test_is_not_unsafe_floating_point<public_derived_from<class_type>>();
    test_is_not_unsafe_floating_point<private_derived_from<base>>();
    test_is_not_unsafe_floating_point<private_derived_from<derived>>();
    test_is_not_unsafe_floating_point<private_derived_from<class_type>>();
    test_is_not_unsafe_floating_point<protected_derived_from<base>>();
    test_is_not_unsafe_floating_point<protected_derived_from<derived>>();
    test_is_not_unsafe_floating_point<protected_derived_from<class_type>>();
    test_is_not_unsafe_floating_point<union_type>();
    test_is_not_unsafe_floating_point<non_empty_union>();
    test_is_not_unsafe_floating_point<empty>();
    test_is_not_unsafe_floating_point<not_empty>();
    test_is_not_unsafe_floating_point<bit_zero>();
    test_is_not_unsafe_floating_point<bit_one>();
    test_is_not_unsafe_floating_point<base>();
    test_is_not_unsafe_floating_point<derived>();
    test_is_not_unsafe_floating_point<abstract>();
    test_is_not_unsafe_floating_point<public_abstract>();
    test_is_not_unsafe_floating_point<private_abstract>();
    test_is_not_unsafe_floating_point<protected_abstract>();
    test_is_not_unsafe_floating_point<abstract_template<int>>();
    test_is_not_unsafe_floating_point<abstract_template<double>>();
    test_is_not_unsafe_floating_point<abstract_template<class_type>>();
    test_is_not_unsafe_floating_point<abstract_template<incomplete_type>>();
    test_is_not_unsafe_floating_point<final_type>();
    test_is_not_unsafe_floating_point<public_destructor>();
    test_is_not_unsafe_floating_point<protected_destructor>();
    test_is_not_unsafe_floating_point<private_destructor>();
    test_is_not_unsafe_floating_point<virtual_public_destructor>();
    test_is_not_unsafe_floating_point<virtual_protected_destructor>();
    test_is_not_unsafe_floating_point<virtual_private_destructor>();
    test_is_not_unsafe_floating_point<pure_public_destructor>();
    test_is_not_unsafe_floating_point<pure_protected_destructor>();
    test_is_not_unsafe_floating_point<pure_private_destructor>();
    test_is_not_unsafe_floating_point<deleted_public_destructor>();
    test_is_not_unsafe_floating_point<deleted_protected_destructor>();
    test_is_not_unsafe_floating_point<deleted_private_destructor>();
    test_is_not_unsafe_floating_point<deleted_virtual_public_destructor>();
    test_is_not_unsafe_floating_point<deleted_virtual_protected_destructor>();
    test_is_not_unsafe_floating_point<deleted_virtual_private_destructor>();
    test_is_not_unsafe_floating_point<final_type>();
    test_is_not_unsafe_floating_point<Enum>();
    test_is_not_unsafe_floating_point<EnumSigned>();
    test_is_not_unsafe_floating_point<EnumUnsigned>();
    test_is_not_unsafe_floating_point<EnumClass>();
    test_is_not_unsafe_floating_point<EnumStruct>();
    test_is_not_unsafe_floating_point<function_type>();
    test_is_not_unsafe_floating_point<function_ptr>();
    test_is_not_unsafe_floating_point<member_object_ptr>();
    test_is_not_unsafe_floating_point<member_function_ptr>();
    test_is_not_unsafe_floating_point<incomplete_type>();
    test_is_not_unsafe_floating_point<incomplete_template<void>>();
    test_is_not_unsafe_floating_point<incomplete_template<int>>();
    test_is_not_unsafe_floating_point<incomplete_template<class_type>>();
    test_is_not_unsafe_floating_point<incomplete_template<incomplete_type>>();
    test_is_not_unsafe_floating_point<incomplete_variadic_template<>>();
    test_is_not_unsafe_floating_point<incomplete_variadic_template<void>>();
    test_is_not_unsafe_floating_point<incomplete_variadic_template<int>>();
    test_is_not_unsafe_floating_point<incomplete_variadic_template<class_type>>();
    test_is_not_unsafe_floating_point<incomplete_variadic_template<incomplete_type>>();
    test_is_not_unsafe_floating_point<
            incomplete_variadic_template<int, void, class_type, volatile char[]>>();
    test_is_not_unsafe_floating_point<int class_type::*>();
    test_is_not_unsafe_floating_point<float class_type::*>();
    test_is_not_unsafe_floating_point<void * class_type::*>();
    test_is_not_unsafe_floating_point<int * class_type::*>();
    test_is_not_unsafe_floating_point<int class_type::*&>();
    test_is_not_unsafe_floating_point<float class_type::*&>();
    test_is_not_unsafe_floating_point<void * class_type::*&>();
    test_is_not_unsafe_floating_point<int * class_type::*&>();
    test_is_not_unsafe_floating_point<int class_type::*&&>();
    test_is_not_unsafe_floating_point<float class_type::*&&>();
    test_is_not_unsafe_floating_point<void * class_type::*&&>();
    test_is_not_unsafe_floating_point<int * class_type::*&&>();
    test_is_not_unsafe_floating_point<int class_type::* const>();
    test_is_not_unsafe_floating_point<float class_type::* const>();
    test_is_not_unsafe_floating_point<void * class_type::* const>();
    test_is_not_unsafe_floating_point<int class_type::* const&>();
    test_is_not_unsafe_floating_point<float class_type::* const&>();
    test_is_not_unsafe_floating_point<void * class_type::* const&>();
    test_is_not_unsafe_floating_point<int class_type::* const&&>();
    test_is_not_unsafe_floating_point<float class_type::* const&&>();
    test_is_not_unsafe_floating_point<void * class_type::* const&&>();
    test_is_not_unsafe_floating_point<int class_type::* volatile>();
    test_is_not_unsafe_floating_point<float class_type::* volatile>();
    test_is_not_unsafe_floating_point<void * class_type::* volatile>();
    test_is_not_unsafe_floating_point<int class_type::* volatile&>();
    test_is_not_unsafe_floating_point<float class_type::* volatile&>();
    test_is_not_unsafe_floating_point<void * class_type::* volatile&>();
    test_is_not_unsafe_floating_point<int class_type::* volatile&&>();
    test_is_not_unsafe_floating_point<float class_type::* volatile&&>();
    test_is_not_unsafe_floating_point<void * class_type::* volatile&&>();
    test_is_not_unsafe_floating_point<int class_type::* const volatile>();
    test_is_not_unsafe_floating_point<float class_type::* const volatile>();
    test_is_not_unsafe_floating_point<void * class_type::* const volatile>();
    test_is_not_unsafe_floating_point<int class_type::* const volatile&>();
    test_is_not_unsafe_floating_point<float class_type::* const volatile&>();
    test_is_not_unsafe_floating_point<void * class_type::* const volatile&>();
    test_is_not_unsafe_floating_point<int class_type::* const volatile&&>();
    test_is_not_unsafe_floating_point<float class_type::* const volatile&&>();
    test_is_not_unsafe_floating_point<void * class_type::* const volatile&&>();
    test_is_not_unsafe_floating_point<non_copyable>();
    test_is_not_unsafe_floating_point<non_moveable>();
    test_is_not_unsafe_floating_point<non_constructible>();
    test_is_not_unsafe_floating_point<tracked>();
    test_is_not_unsafe_floating_point<trap_constructible>();
    test_is_not_unsafe_floating_point<trap_implicit_conversion>();
    test_is_not_unsafe_floating_point<trap_comma>();
    test_is_not_unsafe_floating_point<trap_call>();
    test_is_not_unsafe_floating_point<trap_self_assign>();
    test_is_not_unsafe_floating_point<trap_deref>();
    test_is_not_unsafe_floating_point<trap_array_subscript>();

    test_is_not_unsafe_floating_point<void()>();
    test_is_not_unsafe_floating_point<void()&>();
    test_is_not_unsafe_floating_point<void() &&>();
    test_is_not_unsafe_floating_point<void() const>();
    test_is_not_unsafe_floating_point<void() const&>();
    test_is_not_unsafe_floating_point<void() const&&>();
    test_is_not_unsafe_floating_point<void() volatile>();
    test_is_not_unsafe_floating_point<void() volatile&>();
    test_is_not_unsafe_floating_point<void() volatile&&>();
    test_is_not_unsafe_floating_point<void() const volatile>();
    test_is_not_unsafe_floating_point<void() const volatile&>();
    test_is_not_unsafe_floating_point<void() const volatile&&>();
    test_is_not_unsafe_floating_point<void() noexcept>();
    test_is_not_unsafe_floating_point<void() & noexcept>();
    test_is_not_unsafe_floating_point<void() && noexcept>();
    test_is_not_unsafe_floating_point<void() const noexcept>();
    test_is_not_unsafe_floating_point<void() const & noexcept>();
    test_is_not_unsafe_floating_point<void() const && noexcept>();
    test_is_not_unsafe_floating_point<void() volatile noexcept>();
    test_is_not_unsafe_floating_point<void() volatile & noexcept>();
    test_is_not_unsafe_floating_point<void() volatile && noexcept>();
    test_is_not_unsafe_floating_point<void() const volatile noexcept>();
    test_is_not_unsafe_floating_point<void() const volatile & noexcept>();
    test_is_not_unsafe_floating_point<void() const volatile && noexcept>();

    test_is_not_unsafe_floating_point<void(int)>();
    test_is_not_unsafe_floating_point<void(int)&>();
    test_is_not_unsafe_floating_point<void(int) &&>();
    test_is_not_unsafe_floating_point<void(int) const>();
    test_is_not_unsafe_floating_point<void(int) const&>();
    test_is_not_unsafe_floating_point<void(int) const&&>();
    test_is_not_unsafe_floating_point<void(int) volatile>();
    test_is_not_unsafe_floating_point<void(int) volatile&>();
    test_is_not_unsafe_floating_point<void(int) volatile&&>();
    test_is_not_unsafe_floating_point<void(int) const volatile>();
    test_is_not_unsafe_floating_point<void(int) const volatile&>();
    test_is_not_unsafe_floating_point<void(int) const volatile&&>();
    test_is_not_unsafe_floating_point<void(int) noexcept>();
    test_is_not_unsafe_floating_point<void(int) & noexcept>();
    test_is_not_unsafe_floating_point<void(int) && noexcept>();
    test_is_not_unsafe_floating_point<void(int) const noexcept>();
    test_is_not_unsafe_floating_point<void(int) const & noexcept>();
    test_is_not_unsafe_floating_point<void(int) const && noexcept>();
    test_is_not_unsafe_floating_point<void(int) volatile noexcept>();
    test_is_not_unsafe_floating_point<void(int) volatile & noexcept>();
    test_is_not_unsafe_floating_point<void(int) volatile && noexcept>();
    test_is_not_unsafe_floating_point<void(int) const volatile noexcept>();
    test_is_not_unsafe_floating_point<void(int) const volatile & noexcept>();
    test_is_not_unsafe_floating_point<void(int) const volatile && noexcept>();

    test_is_not_unsafe_floating_point<void(...)>();
    test_is_not_unsafe_floating_point<void(...)&>();
    test_is_not_unsafe_floating_point<void(...) &&>();
    test_is_not_unsafe_floating_point<void(...) const>();
    test_is_not_unsafe_floating_point<void(...) const&>();
    test_is_not_unsafe_floating_point<void(...) const&&>();
    test_is_not_unsafe_floating_point<void(...) volatile>();
    test_is_not_unsafe_floating_point<void(...) volatile&>();
    test_is_not_unsafe_floating_point<void(...) volatile&&>();
    test_is_not_unsafe_floating_point<void(...) const volatile>();
    test_is_not_unsafe_floating_point<void(...) const volatile&>();
    test_is_not_unsafe_floating_point<void(...) const volatile&&>();
    test_is_not_unsafe_floating_point<void(...) noexcept>();
    test_is_not_unsafe_floating_point<void(...) & noexcept>();
    test_is_not_unsafe_floating_point<void(...) && noexcept>();
    test_is_not_unsafe_floating_point<void(...) const noexcept>();
    test_is_not_unsafe_floating_point<void(...) const & noexcept>();
    test_is_not_unsafe_floating_point<void(...) const && noexcept>();
    test_is_not_unsafe_floating_point<void(...) volatile noexcept>();
    test_is_not_unsafe_floating_point<void(...) volatile & noexcept>();
    test_is_not_unsafe_floating_point<void(...) volatile && noexcept>();
    test_is_not_unsafe_floating_point<void(...) const volatile noexcept>();
    test_is_not_unsafe_floating_point<void(...) const volatile & noexcept>();
    test_is_not_unsafe_floating_point<void(...) const volatile && noexcept>();

    test_is_not_unsafe_floating_point<void(int, ...)>();
    test_is_not_unsafe_floating_point<void(int, ...)&>();
    test_is_not_unsafe_floating_point<void(int, ...) &&>();
    test_is_not_unsafe_floating_point<void(int, ...) const>();
    test_is_not_unsafe_floating_point<void(int, ...) const&>();
    test_is_not_unsafe_floating_point<void(int, ...) const&&>();
    test_is_not_unsafe_floating_point<void(int, ...) volatile>();
    test_is_not_unsafe_floating_point<void(int, ...) volatile&>();
    test_is_not_unsafe_floating_point<void(int, ...) volatile&&>();
    test_is_not_unsafe_floating_point<void(int, ...) const volatile>();
    test_is_not_unsafe_floating_point<void(int, ...) const volatile&>();
    test_is_not_unsafe_floating_point<void(int, ...) const volatile&&>();
    test_is_not_unsafe_floating_point<void(int, ...) noexcept>();
    test_is_not_unsafe_floating_point<void(int, ...) & noexcept>();
    test_is_not_unsafe_floating_point<void(int, ...) && noexcept>();
    test_is_not_unsafe_floating_point<void(int, ...) const noexcept>();
    test_is_not_unsafe_floating_point<void(int, ...) const & noexcept>();
    test_is_not_unsafe_floating_point<void(int, ...) const && noexcept>();
    test_is_not_unsafe_floating_point<void(int, ...) volatile noexcept>();
    test_is_not_unsafe_floating_point<void(int, ...) volatile & noexcept>();
    test_is_not_unsafe_floating_point<void(int, ...) volatile && noexcept>();
    test_is_not_unsafe_floating_point<void(int, ...) const volatile noexcept>();
    test_is_not_unsafe_floating_point<void(int, ...) const volatile & noexcept>();
    test_is_not_unsafe_floating_point<void(int, ...) const volatile && noexcept>();

    test_is_not_unsafe_floating_point<int()>();
    test_is_not_unsafe_floating_point<int()&>();
    test_is_not_unsafe_floating_point<int() &&>();
    test_is_not_unsafe_floating_point<int() const>();
    test_is_not_unsafe_floating_point<int() const&>();
    test_is_not_unsafe_floating_point<int() const&&>();
    test_is_not_unsafe_floating_point<int() volatile>();
    test_is_not_unsafe_floating_point<int() volatile&>();
    test_is_not_unsafe_floating_point<int() volatile&&>();
    test_is_not_unsafe_floating_point<int() const volatile>();
    test_is_not_unsafe_floating_point<int() const volatile&>();
    test_is_not_unsafe_floating_point<int() const volatile&&>();
    test_is_not_unsafe_floating_point<int() noexcept>();
    test_is_not_unsafe_floating_point<int() & noexcept>();
    test_is_not_unsafe_floating_point<int() && noexcept>();
    test_is_not_unsafe_floating_point<int() const noexcept>();
    test_is_not_unsafe_floating_point<int() const & noexcept>();
    test_is_not_unsafe_floating_point<int() const && noexcept>();
    test_is_not_unsafe_floating_point<int() volatile noexcept>();
    test_is_not_unsafe_floating_point<int() volatile & noexcept>();
    test_is_not_unsafe_floating_point<int() volatile && noexcept>();
    test_is_not_unsafe_floating_point<int() const volatile noexcept>();
    test_is_not_unsafe_floating_point<int() const volatile & noexcept>();
    test_is_not_unsafe_floating_point<int() const volatile && noexcept>();

    test_is_not_unsafe_floating_point<int(int)>();
    test_is_not_unsafe_floating_point<int(int)&>();
    test_is_not_unsafe_floating_point<int(int) &&>();
    test_is_not_unsafe_floating_point<int(int) const>();
    test_is_not_unsafe_floating_point<int(int) const&>();
    test_is_not_unsafe_floating_point<int(int) const&&>();
    test_is_not_unsafe_floating_point<int(int) volatile>();
    test_is_not_unsafe_floating_point<int(int) volatile&>();
    test_is_not_unsafe_floating_point<int(int) volatile&&>();
    test_is_not_unsafe_floating_point<int(int) const volatile>();
    test_is_not_unsafe_floating_point<int(int) const volatile&>();
    test_is_not_unsafe_floating_point<int(int) const volatile&&>();
    test_is_not_unsafe_floating_point<int(int) noexcept>();
    test_is_not_unsafe_floating_point<int(int) & noexcept>();
    test_is_not_unsafe_floating_point<int(int) && noexcept>();
    test_is_not_unsafe_floating_point<int(int) const noexcept>();
    test_is_not_unsafe_floating_point<int(int) const & noexcept>();
    test_is_not_unsafe_floating_point<int(int) const && noexcept>();
    test_is_not_unsafe_floating_point<int(int) volatile noexcept>();
    test_is_not_unsafe_floating_point<int(int) volatile & noexcept>();
    test_is_not_unsafe_floating_point<int(int) volatile && noexcept>();
    test_is_not_unsafe_floating_point<int(int) const volatile noexcept>();
    test_is_not_unsafe_floating_point<int(int) const volatile & noexcept>();
    test_is_not_unsafe_floating_point<int(int) const volatile && noexcept>();

    test_is_not_unsafe_floating_point<int(...)>();
    test_is_not_unsafe_floating_point<int(...)&>();
    test_is_not_unsafe_floating_point<int(...) &&>();
    test_is_not_unsafe_floating_point<int(...) const>();
    test_is_not_unsafe_floating_point<int(...) const&>();
    test_is_not_unsafe_floating_point<int(...) const&&>();
    test_is_not_unsafe_floating_point<int(...) volatile>();
    test_is_not_unsafe_floating_point<int(...) volatile&>();
    test_is_not_unsafe_floating_point<int(...) volatile&&>();
    test_is_not_unsafe_floating_point<int(...) const volatile>();
    test_is_not_unsafe_floating_point<int(...) const volatile&>();
    test_is_not_unsafe_floating_point<int(...) const volatile&&>();
    test_is_not_unsafe_floating_point<int(...) noexcept>();
    test_is_not_unsafe_floating_point<int(...) & noexcept>();
    test_is_not_unsafe_floating_point<int(...) && noexcept>();
    test_is_not_unsafe_floating_point<int(...) const noexcept>();
    test_is_not_unsafe_floating_point<int(...) const & noexcept>();
    test_is_not_unsafe_floating_point<int(...) const && noexcept>();
    test_is_not_unsafe_floating_point<int(...) volatile noexcept>();
    test_is_not_unsafe_floating_point<int(...) volatile & noexcept>();
    test_is_not_unsafe_floating_point<int(...) volatile && noexcept>();
    test_is_not_unsafe_floating_point<int(...) const volatile noexcept>();
    test_is_not_unsafe_floating_point<int(...) const volatile & noexcept>();
    test_is_not_unsafe_floating_point<int(...) const volatile && noexcept>();

    test_is_not_unsafe_floating_point<int(int, ...)>();
    test_is_not_unsafe_floating_point<int(int, ...)&>();
    test_is_not_unsafe_floating_point<int(int, ...) &&>();
    test_is_not_unsafe_floating_point<int(int, ...) const>();
    test_is_not_unsafe_floating_point<int(int, ...) const&>();
    test_is_not_unsafe_floating_point<int(int, ...) const&&>();
    test_is_not_unsafe_floating_point<int(int, ...) volatile>();
    test_is_not_unsafe_floating_point<int(int, ...) volatile&>();
    test_is_not_unsafe_floating_point<int(int, ...) volatile&&>();
    test_is_not_unsafe_floating_point<int(int, ...) const volatile>();
    test_is_not_unsafe_floating_point<int(int, ...) const volatile&>();
    test_is_not_unsafe_floating_point<int(int, ...) const volatile&&>();
    test_is_not_unsafe_floating_point<int(int, ...) noexcept>();
    test_is_not_unsafe_floating_point<int(int, ...) & noexcept>();
    test_is_not_unsafe_floating_point<int(int, ...) && noexcept>();
    test_is_not_unsafe_floating_point<int(int, ...) const noexcept>();
    test_is_not_unsafe_floating_point<int(int, ...) const & noexcept>();
    test_is_not_unsafe_floating_point<int(int, ...) const && noexcept>();
    test_is_not_unsafe_floating_point<int(int, ...) volatile noexcept>();
    test_is_not_unsafe_floating_point<int(int, ...) volatile & noexcept>();
    test_is_not_unsafe_floating_point<int(int, ...) volatile && noexcept>();
    test_is_not_unsafe_floating_point<int(int, ...) const volatile noexcept>();
    test_is_not_unsafe_floating_point<int(int, ...) const volatile & noexcept>();
    test_is_not_unsafe_floating_point<int(int, ...) const volatile && noexcept>();

    test_is_not_unsafe_floating_point<void (*)()>();
    test_is_not_unsafe_floating_point<void (*)() noexcept>();

    test_is_not_unsafe_floating_point<void (*)(int)>();
    test_is_not_unsafe_floating_point<void (*)(int) noexcept>();

    test_is_not_unsafe_floating_point<void (*)(...)>();
    test_is_not_unsafe_floating_point<void (*)(...) noexcept>();

    test_is_not_unsafe_floating_point<void (*)(int, ...)>();
    test_is_not_unsafe_floating_point<void (*)(int, ...) noexcept>();

    test_is_not_unsafe_floating_point<int (*)()>();
    test_is_not_unsafe_floating_point<int (*)() noexcept>();

    test_is_not_unsafe_floating_point<int (*)(int)>();
    test_is_not_unsafe_floating_point<int (*)(int) noexcept>();

    test_is_not_unsafe_floating_point<int (*)(...)>();
    test_is_not_unsafe_floating_point<int (*)(...) noexcept>();

    test_is_not_unsafe_floating_point<int (*)(int, ...)>();
    test_is_not_unsafe_floating_point<int (*)(int, ...) noexcept>();

    test_is_not_unsafe_floating_point<void (&)()>();
    test_is_not_unsafe_floating_point<void (&)() noexcept>();

    test_is_not_unsafe_floating_point<void (&)(int)>();
    test_is_not_unsafe_floating_point<void (&)(int) noexcept>();

    test_is_not_unsafe_floating_point<void (&)(...)>();
    test_is_not_unsafe_floating_point<void (&)(...) noexcept>();

    test_is_not_unsafe_floating_point<void (&)(int, ...)>();
    test_is_not_unsafe_floating_point<void (&)(int, ...) noexcept>();

    test_is_not_unsafe_floating_point<int (&)()>();
    test_is_not_unsafe_floating_point<int (&)() noexcept>();

    test_is_not_unsafe_floating_point<int (&)(int)>();
    test_is_not_unsafe_floating_point<int (&)(int) noexcept>();

    test_is_not_unsafe_floating_point<int (&)(...)>();
    test_is_not_unsafe_floating_point<int (&)(...) noexcept>();

    test_is_not_unsafe_floating_point<int (&)(int, ...)>();
    test_is_not_unsafe_floating_point<int (&)(int, ...) noexcept>();

    test_is_not_unsafe_floating_point<void (&&)()>();
    test_is_not_unsafe_floating_point<void (&&)() noexcept>();

    test_is_not_unsafe_floating_point<void (&&)(int)>();
    test_is_not_unsafe_floating_point<void (&&)(int) noexcept>();

    test_is_not_unsafe_floating_point<void (&&)(...)>();
    test_is_not_unsafe_floating_point<void (&&)(...) noexcept>();

    test_is_not_unsafe_floating_point<void (&&)(int, ...)>();
    test_is_not_unsafe_floating_point<void (&&)(int, ...) noexcept>();

    test_is_not_unsafe_floating_point<int (&&)()>();
    test_is_not_unsafe_floating_point<int (&&)() noexcept>();

    test_is_not_unsafe_floating_point<int (&&)(int)>();
    test_is_not_unsafe_floating_point<int (&&)(int) noexcept>();

    test_is_not_unsafe_floating_point<int (&&)(...)>();
    test_is_not_unsafe_floating_point<int (&&)(...) noexcept>();

    test_is_not_unsafe_floating_point<int (&&)(int, ...)>();
    test_is_not_unsafe_floating_point<int (&&)(int, ...) noexcept>();

    test_is_not_unsafe_floating_point<void (class_type::*)()>();
    test_is_not_unsafe_floating_point<void (class_type::*)()&>();
    test_is_not_unsafe_floating_point<void (class_type::*)() &&>();
    test_is_not_unsafe_floating_point<void (class_type::*)() const>();
    test_is_not_unsafe_floating_point<void (class_type::*)() const&>();
    test_is_not_unsafe_floating_point<void (class_type::*)() const&&>();
    test_is_not_unsafe_floating_point<void (class_type::*)() noexcept>();
    test_is_not_unsafe_floating_point<void (class_type::*)() & noexcept>();
    test_is_not_unsafe_floating_point<void (class_type::*)() && noexcept>();
    test_is_not_unsafe_floating_point<void (class_type::*)() const noexcept>();
    test_is_not_unsafe_floating_point<void (class_type::*)() const & noexcept>();
    test_is_not_unsafe_floating_point<void (class_type::*)() const && noexcept>();

    test_is_not_unsafe_floating_point<void (class_type::*)(int)>();
    test_is_not_unsafe_floating_point<void (class_type::*)(int)&>();
    test_is_not_unsafe_floating_point<void (class_type::*)(int) &&>();
    test_is_not_unsafe_floating_point<void (class_type::*)(int) const>();
    test_is_not_unsafe_floating_point<void (class_type::*)(int) const&>();
    test_is_not_unsafe_floating_point<void (class_type::*)(int) const&&>();
    test_is_not_unsafe_floating_point<void (class_type::*)(int) noexcept>();
    test_is_not_unsafe_floating_point<void (class_type::*)(int) & noexcept>();
    test_is_not_unsafe_floating_point<void (class_type::*)(int) && noexcept>();
    test_is_not_unsafe_floating_point<void (class_type::*)(int) const noexcept>();
    test_is_not_unsafe_floating_point<void (class_type::*)(int) const & noexcept>();
    test_is_not_unsafe_floating_point<void (class_type::*)(int) const && noexcept>();

    test_is_not_unsafe_floating_point<void (class_type::*)(...)>();
    test_is_not_unsafe_floating_point<void (class_type::*)(...)&>();
    test_is_not_unsafe_floating_point<void (class_type::*)(...) &&>();
    test_is_not_unsafe_floating_point<void (class_type::*)(...) const>();
    test_is_not_unsafe_floating_point<void (class_type::*)(...) const&>();
    test_is_not_unsafe_floating_point<void (class_type::*)(...) const&&>();
    test_is_not_unsafe_floating_point<void (class_type::*)(...) noexcept>();
    test_is_not_unsafe_floating_point<void (class_type::*)(...) & noexcept>();
    test_is_not_unsafe_floating_point<void (class_type::*)(...) && noexcept>();
    test_is_not_unsafe_floating_point<void (class_type::*)(...) const noexcept>();
    test_is_not_unsafe_floating_point<void (class_type::*)(...) const & noexcept>();
    test_is_not_unsafe_floating_point<void (class_type::*)(...) const && noexcept>();

    test_is_not_unsafe_floating_point<void (class_type::*)(int, ...)>();
    test_is_not_unsafe_floating_point<void (class_type::*)(int, ...)&>();
    test_is_not_unsafe_floating_point<void (class_type::*)(int, ...) &&>();
    test_is_not_unsafe_floating_point<void (class_type::*)(int, ...) const>();
    test_is_not_unsafe_floating_point<void (class_type::*)(int, ...) const&>();
    test_is_not_unsafe_floating_point<void (class_type::*)(int, ...) const&&>();
    test_is_not_unsafe_floating_point<void (class_type::*)(int, ...) noexcept>();
    test_is_not_unsafe_floating_point<void (class_type::*)(int, ...) & noexcept>();
    test_is_not_unsafe_floating_point<void (class_type::*)(int, ...) && noexcept>();
    test_is_not_unsafe_floating_point<void (class_type::*)(int, ...) const noexcept>();
    test_is_not_unsafe_floating_point<void (class_type::*)(int, ...) const & noexcept>();
    test_is_not_unsafe_floating_point<void (class_type::*)(int, ...) const && noexcept>();

    test_is_not_unsafe_floating_point<int (class_type::*)()>();
    test_is_not_unsafe_floating_point<int (class_type::*)()&>();
    test_is_not_unsafe_floating_point<int (class_type::*)() &&>();
    test_is_not_unsafe_floating_point<int (class_type::*)() const>();
    test_is_not_unsafe_floating_point<int (class_type::*)() const&>();
    test_is_not_unsafe_floating_point<int (class_type::*)() const&&>();
    test_is_not_unsafe_floating_point<int (class_type::*)() noexcept>();
    test_is_not_unsafe_floating_point<int (class_type::*)() & noexcept>();
    test_is_not_unsafe_floating_point<int (class_type::*)() && noexcept>();
    test_is_not_unsafe_floating_point<int (class_type::*)() const noexcept>();
    test_is_not_unsafe_floating_point<int (class_type::*)() const & noexcept>();
    test_is_not_unsafe_floating_point<int (class_type::*)() const && noexcept>();

    test_is_not_unsafe_floating_point<int (class_type::*)(int)>();
    test_is_not_unsafe_floating_point<int (class_type::*)(int)&>();
    test_is_not_unsafe_floating_point<int (class_type::*)(int) &&>();
    test_is_not_unsafe_floating_point<int (class_type::*)(int) const>();
    test_is_not_unsafe_floating_point<int (class_type::*)(int) const&>();
    test_is_not_unsafe_floating_point<int (class_type::*)(int) const&&>();
    test_is_not_unsafe_floating_point<int (class_type::*)(int) noexcept>();
    test_is_not_unsafe_floating_point<int (class_type::*)(int) & noexcept>();
    test_is_not_unsafe_floating_point<int (class_type::*)(int) && noexcept>();
    test_is_not_unsafe_floating_point<int (class_type::*)(int) const noexcept>();
    test_is_not_unsafe_floating_point<int (class_type::*)(int) const & noexcept>();
    test_is_not_unsafe_floating_point<int (class_type::*)(int) const && noexcept>();

    test_is_not_unsafe_floating_point<int (class_type::*)(...)>();
    test_is_not_unsafe_floating_point<int (class_type::*)(...)&>();
    test_is_not_unsafe_floating_point<int (class_type::*)(...) &&>();
    test_is_not_unsafe_floating_point<int (class_type::*)(...) const>();
    test_is_not_unsafe_floating_point<int (class_type::*)(...) const&>();
    test_is_not_unsafe_floating_point<int (class_type::*)(...) const&&>();
    test_is_not_unsafe_floating_point<int (class_type::*)(...) noexcept>();
    test_is_not_unsafe_floating_point<int (class_type::*)(...) & noexcept>();
    test_is_not_unsafe_floating_point<int (class_type::*)(...) && noexcept>();
    test_is_not_unsafe_floating_point<int (class_type::*)(...) const noexcept>();
    test_is_not_unsafe_floating_point<int (class_type::*)(...) const & noexcept>();
    test_is_not_unsafe_floating_point<int (class_type::*)(...) const && noexcept>();

    test_is_not_unsafe_floating_point<int (class_type::*)(int, ...)>();
    test_is_not_unsafe_floating_point<int (class_type::*)(int, ...)&>();
    test_is_not_unsafe_floating_point<int (class_type::*)(int, ...) &&>();
    test_is_not_unsafe_floating_point<int (class_type::*)(int, ...) const>();
    test_is_not_unsafe_floating_point<int (class_type::*)(int, ...) const&>();
    test_is_not_unsafe_floating_point<int (class_type::*)(int, ...) const&&>();
    test_is_not_unsafe_floating_point<int (class_type::*)(int, ...) noexcept>();
    test_is_not_unsafe_floating_point<int (class_type::*)(int, ...) & noexcept>();
    test_is_not_unsafe_floating_point<int (class_type::*)(int, ...) && noexcept>();
    test_is_not_unsafe_floating_point<int (class_type::*)(int, ...) const noexcept>();
    test_is_not_unsafe_floating_point<int (class_type::*)(int, ...) const & noexcept>();
    test_is_not_unsafe_floating_point<int (class_type::*)(int, ...) const && noexcept>();
}
