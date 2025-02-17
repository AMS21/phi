#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/compiler_support/extensions/zero_size_array.hpp>
#include <phi/container/array.hpp>
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
#include <array>
#include <type_traits>
#include <vector>

template <typename TypeT>
void test_is_array_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_arithmetic<TypeT>::value);
    STATIC_REQUIRE(phi::is_array<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_bool<TypeT>::value);
#if PHI_HAS_WORKING_IS_CLASS()
    STATIC_REQUIRE_FALSE(phi::is_class<TypeT>::value);
#endif
    STATIC_REQUIRE(phi::is_compound<TypeT>::value);
#if PHI_HAS_WORKING_IS_ENUM()
    STATIC_REQUIRE_FALSE(phi::is_enum<TypeT>::value);
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
    STATIC_REQUIRE_FALSE(phi::is_scalar<TypeT>::value);
#endif
#if PHI_HAS_WORKING_IS_UNION()
    STATIC_REQUIRE_FALSE(phi::is_union<TypeT>::value);
#endif
    STATIC_REQUIRE_FALSE(phi::is_void<TypeT>::value);

    STATIC_REQUIRE_FALSE(phi::is_not_array<TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_arithmetic_v<TypeT>);
    STATIC_REQUIRE(phi::is_array_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_bool_v<TypeT>);
#    if PHI_HAS_WORKING_IS_CLASS()
    STATIC_REQUIRE_FALSE(phi::is_class_v<TypeT>);
#    endif
    STATIC_REQUIRE(phi::is_compound_v<TypeT>);
#    if PHI_HAS_WORKING_IS_ENUM()
    STATIC_REQUIRE_FALSE(phi::is_enum_v<TypeT>);
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
    STATIC_REQUIRE_FALSE(phi::is_scalar_v<TypeT>);
#    endif
#    if PHI_HAS_WORKING_IS_UNION()
    STATIC_REQUIRE_FALSE(phi::is_union_v<TypeT>);
#    endif
    STATIC_REQUIRE_FALSE(phi::is_void_v<TypeT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_array<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_array<TypeT>);

    // Standard compatbility
    STATIC_REQUIRE(std::is_array<TypeT>::value);
#if PHI_CPP_STANDARD_IS_ATLEAST(17) && PHI_COMPILER_WORKAROUND(GCC, 7, 0, 0)
    STATIC_REQUIRE(std::is_array_v<TypeT>);
#endif
}

template <typename TypeT>
void test_is_array()
{
    test_is_array_impl<TypeT>();
    test_is_array_impl<const TypeT>();
    test_is_array_impl<volatile TypeT>();
    test_is_array_impl<const volatile TypeT>();
}

template <typename TypeT>
void test_is_not_array_no_std_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_array<TypeT>::value);
    STATIC_REQUIRE(phi::is_not_array<TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_array_v<TypeT>);
    STATIC_REQUIRE(phi::is_not_array_v<TypeT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_array<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_array<TypeT>);
}

template <typename TypeT>
void test_is_not_array_impl()
{
    test_is_not_array_no_std_impl<TypeT>();

    // Standard compatibility
    STATIC_REQUIRE_FALSE(std::is_array<TypeT>::value);
#if PHI_CPP_STANDARD_IS_ATLEAST(17) && PHI_COMPILER_WORKAROUND(GCC, 7, 0, 0)
    STATIC_REQUIRE_FALSE(std::is_array_v<TypeT>);
#endif
}

template <typename TypeT>
void test_is_not_array_no_std()
{
    test_is_not_array_no_std_impl<TypeT>();
    test_is_not_array_no_std_impl<const TypeT>();
    test_is_not_array_no_std_impl<volatile TypeT>();
    test_is_not_array_no_std_impl<const volatile TypeT>();
}

template <typename TypeT>
void test_is_not_array()
{
    test_is_not_array_impl<TypeT>();
    test_is_not_array_impl<const TypeT>();
    test_is_not_array_impl<volatile TypeT>();
    test_is_not_array_impl<const volatile TypeT>();
}

using array            = char[3];
using const_array      = const char[3];
using incomplete_array = char[];

TEST_CASE("is_array")
{
    test_is_array<char[3]>();
    test_is_array<char[]>();
    test_is_array<char[][3]>();
    test_is_array<char[3][3]>();
    test_is_array<union_type[]>();
    test_is_array<union_type[2]>();
    test_is_array<class_type[]>();
    test_is_array<class_type[3]>();
    test_is_array<array>();
    test_is_array<const_array>();
    test_is_array<incomplete_array>();
    test_is_array<incomplete_type[]>();
    test_is_array<incomplete_type[3]>();
    test_is_array<int[1]>();
    test_is_array<int[1][2]>();
    test_is_array<int[1][2][3]>();
    test_is_array<int[1][2][3][4]>();
    test_is_array<int[1][2][3][4][5]>();
    test_is_array<int[1][2][3][4][5][6]>();
    test_is_array<int[1][2][3][4][5][6][7]>();
    test_is_array<int[1][2][3][4][5][6][7][8]>();
    test_is_array<int[1][2][3][4][5][6][7][8][9]>();
    test_is_array<int[1][2][3][4][5][6][7][8][9][10]>();
    test_is_not_array<std::array<int, 3>>();
    test_is_not_array<phi::array<int, 3>>();

    test_is_array<int[2]>();
    test_is_array<int[]>();
    test_is_array<int[2][3]>();
    test_is_array<int[][3]>();
    test_is_array<float* [2]>();
    test_is_array<float*[]>();
    test_is_array<float* [2][3]>();
    test_is_array<float*[][3]>();
    test_is_array<class_type[2]>();
    test_is_array<class_type[]>();
    test_is_array<class_type[2][3]>();
    test_is_array<class_type[][3]>();

    // Zero sized arrays are a weird case in C++. The standard doesn't allow them in general so theres no standard answer to whether or not zero sized arrays are "real" arrays. Still some compilers allow them as an extension but give warnings. To discourage their usage we simply force phi::is_array<T[0]> to be false
#if PHI_HAS_EXTENSION_ZERO_SIZE_ARRAY() && PHI_COMPILER_IS_NOT(MINGW)
    PHI_CLANG_SUPPRESS_WARNING_WITH_PUSH("-Wzero-length-array")
    PHI_GCC_SUPPRESS_WARNING_WITH_PUSH("-Wpedantic")

    test_is_not_array_no_std<int[0]>();
    test_is_not_array_no_std<float[0]>();
    test_is_not_array_no_std<class_type[0]>();

    PHI_GCC_SUPPRESS_WARNING_POP()
    PHI_CLANG_SUPPRESS_WARNING_POP()
#endif

    test_is_not_array<void>();
    test_is_not_array<phi::nullptr_t>();
    test_is_not_array<bool>();
    test_is_not_array<char>();
    test_is_not_array<signed char>();
    test_is_not_array<unsigned char>();
    test_is_not_array<short>();
    test_is_not_array<unsigned short>();
    test_is_not_array<int>();
    test_is_not_array<unsigned int>();
    test_is_not_array<long>();
    test_is_not_array<unsigned long>();
    test_is_not_array<long long>();
    test_is_not_array<unsigned long long>();
    test_is_not_array<float>();
    test_is_not_array<double>();
    test_is_not_array<long double>();
    test_is_not_array<char8_t>();
    test_is_not_array<char16_t>();
    test_is_not_array<char32_t>();
    test_is_not_array<wchar_t>();

    test_is_not_array<phi::boolean>();
    test_is_not_array<phi::integer<signed char>>();
    test_is_not_array<phi::integer<unsigned char>>();
    test_is_not_array<phi::integer<short>>();
    test_is_not_array<phi::integer<unsigned short>>();
    test_is_not_array<phi::integer<int>>();
    test_is_not_array<phi::integer<unsigned int>>();
    test_is_not_array<phi::integer<long>>();
    test_is_not_array<phi::integer<unsigned long>>();
    test_is_not_array<phi::integer<long long>>();
    test_is_not_array<phi::integer<unsigned long long>>();
    test_is_not_array<phi::floating_point<float>>();
    test_is_not_array<phi::floating_point<double>>();
    test_is_not_array<phi::floating_point<long double>>();

    test_is_not_array<std::vector<int>>();
    test_is_not_array<phi::scope_ptr<int>>();

    test_is_not_array<int&>();
    test_is_not_array<const int&>();
    test_is_not_array<volatile int&>();
    test_is_not_array<const volatile int&>();
    test_is_not_array<int&&>();
    test_is_not_array<const int&&>();
    test_is_not_array<volatile int&&>();
    test_is_not_array<const volatile int&&>();
    test_is_not_array<int*>();
    test_is_not_array<const int*>();
    test_is_not_array<volatile int*>();
    test_is_not_array<const volatile int*>();
    test_is_not_array<int**>();
    test_is_not_array<const int**>();
    test_is_not_array<volatile int**>();
    test_is_not_array<const volatile int**>();
    test_is_not_array<int*&>();
    test_is_not_array<const int*&>();
    test_is_not_array<volatile int*&>();
    test_is_not_array<const volatile int*&>();
    test_is_not_array<int*&&>();
    test_is_not_array<const int*&&>();
    test_is_not_array<volatile int*&&>();
    test_is_not_array<const volatile int*&&>();
    test_is_not_array<void*>();
    test_is_array<char[3]>();
    test_is_array<char[]>();
    test_is_array<char* [3]>();
    test_is_array<char*[]>();
    test_is_not_array<int(*)[3]>();
    test_is_not_array<int(*)[]>();
    test_is_not_array<int(&)[3]>();
    test_is_not_array<int(&)[]>();
    test_is_not_array<int(&&)[3]>();
    test_is_not_array<int(&&)[]>();
    test_is_array<char[3][2]>();
    test_is_array<char[][2]>();
    test_is_array<char* [3][2]>();
    test_is_array<char*[][2]>();
    test_is_not_array<int(*)[3][2]>();
    test_is_not_array<int(*)[][2]>();
    test_is_not_array<int(&)[3][2]>();
    test_is_not_array<int(&)[][2]>();
    test_is_not_array<int(&&)[3][2]>();
    test_is_not_array<int(&&)[][2]>();
    test_is_not_array<class_type>();
    test_is_array<class_type[]>();
    test_is_array<class_type[2]>();
    test_is_not_array<template_type<void>>();
    test_is_not_array<template_type<int>>();
    test_is_not_array<template_type<class_type>>();
    test_is_not_array<template_type<incomplete_type>>();
    test_is_not_array<variadic_template<>>();
    test_is_not_array<variadic_template<void>>();
    test_is_not_array<variadic_template<int>>();
    test_is_not_array<variadic_template<class_type>>();
    test_is_not_array<variadic_template<incomplete_type>>();
    test_is_not_array<variadic_template<int, void, class_type, volatile char[]>>();
    test_is_not_array<public_derived_from<base>>();
    test_is_not_array<public_derived_from<derived>>();
    test_is_not_array<public_derived_from<class_type>>();
    test_is_not_array<private_derived_from<base>>();
    test_is_not_array<private_derived_from<derived>>();
    test_is_not_array<private_derived_from<class_type>>();
    test_is_not_array<protected_derived_from<base>>();
    test_is_not_array<protected_derived_from<derived>>();
    test_is_not_array<protected_derived_from<class_type>>();
    test_is_not_array<union_type>();
    test_is_not_array<non_empty_union>();
    test_is_not_array<empty>();
    test_is_not_array<not_empty>();
    test_is_not_array<bit_zero>();
    test_is_not_array<bit_one>();
    test_is_not_array<base>();
    test_is_not_array<derived>();
    test_is_not_array<abstract>();
    test_is_not_array<public_abstract>();
    test_is_not_array<private_abstract>();
    test_is_not_array<protected_abstract>();
    test_is_not_array<abstract_template<int>>();
    test_is_not_array<abstract_template<double>>();
    test_is_not_array<abstract_template<class_type>>();
    test_is_not_array<abstract_template<incomplete_type>>();
    test_is_not_array<final_type>();
    test_is_not_array<public_destructor>();
    test_is_not_array<protected_destructor>();
    test_is_not_array<private_destructor>();
    test_is_not_array<virtual_public_destructor>();
    test_is_not_array<virtual_protected_destructor>();
    test_is_not_array<virtual_private_destructor>();
    test_is_not_array<pure_public_destructor>();
    test_is_not_array<pure_protected_destructor>();
    test_is_not_array<pure_private_destructor>();
    test_is_not_array<deleted_public_destructor>();
    test_is_not_array<deleted_protected_destructor>();
    test_is_not_array<deleted_private_destructor>();
    test_is_not_array<deleted_virtual_public_destructor>();
    test_is_not_array<deleted_virtual_protected_destructor>();
    test_is_not_array<deleted_virtual_private_destructor>();
    test_is_not_array<final_type>();
    test_is_not_array<Enum>();
    test_is_not_array<EnumSigned>();
    test_is_not_array<EnumUnsigned>();
    test_is_not_array<EnumClass>();
    test_is_not_array<EnumStruct>();
    test_is_not_array<function_type>();
    test_is_not_array<function_ptr>();
    test_is_not_array<member_object_ptr>();
    test_is_not_array<member_function_ptr>();
    test_is_not_array<incomplete_type>();
    test_is_not_array<incomplete_template<void>>();
    test_is_not_array<incomplete_template<int>>();
    test_is_not_array<incomplete_template<class_type>>();
    test_is_not_array<incomplete_template<incomplete_type>>();
    test_is_not_array<incomplete_variadic_template<>>();
    test_is_not_array<incomplete_variadic_template<void>>();
    test_is_not_array<incomplete_variadic_template<int>>();
    test_is_not_array<incomplete_variadic_template<class_type>>();
    test_is_not_array<incomplete_variadic_template<incomplete_type>>();
    test_is_not_array<incomplete_variadic_template<int, void, class_type, volatile char[]>>();
    test_is_not_array<int class_type::*>();
    test_is_not_array<float class_type::*>();
    test_is_not_array<void * class_type::*>();
    test_is_not_array<int * class_type::*>();
    test_is_not_array<int class_type::*&>();
    test_is_not_array<float class_type::*&>();
    test_is_not_array<void * class_type::*&>();
    test_is_not_array<int * class_type::*&>();
    test_is_not_array<int class_type::*&&>();
    test_is_not_array<float class_type::*&&>();
    test_is_not_array<void * class_type::*&&>();
    test_is_not_array<int * class_type::*&&>();
    test_is_not_array<int class_type::* const>();
    test_is_not_array<float class_type::* const>();
    test_is_not_array<void * class_type::* const>();
    test_is_not_array<int class_type::* const&>();
    test_is_not_array<float class_type::* const&>();
    test_is_not_array<void * class_type::* const&>();
    test_is_not_array<int class_type::* const&&>();
    test_is_not_array<float class_type::* const&&>();
    test_is_not_array<void * class_type::* const&&>();
    test_is_not_array<int class_type::* volatile>();
    test_is_not_array<float class_type::* volatile>();
    test_is_not_array<void * class_type::* volatile>();
    test_is_not_array<int class_type::* volatile&>();
    test_is_not_array<float class_type::* volatile&>();
    test_is_not_array<void * class_type::* volatile&>();
    test_is_not_array<int class_type::* volatile&&>();
    test_is_not_array<float class_type::* volatile&&>();
    test_is_not_array<void * class_type::* volatile&&>();
    test_is_not_array<int class_type::* const volatile>();
    test_is_not_array<float class_type::* const volatile>();
    test_is_not_array<void * class_type::* const volatile>();
    test_is_not_array<int class_type::* const volatile&>();
    test_is_not_array<float class_type::* const volatile&>();
    test_is_not_array<void * class_type::* const volatile&>();
    test_is_not_array<int class_type::* const volatile&&>();
    test_is_not_array<float class_type::* const volatile&&>();
    test_is_not_array<void * class_type::* const volatile&&>();
    test_is_not_array<non_copyable>();
    test_is_not_array<non_moveable>();
    test_is_not_array<non_constructible>();
    test_is_not_array<tracked>();
    test_is_not_array<trap_constructible>();
    test_is_not_array<trap_implicit_conversion>();
    test_is_not_array<trap_comma>();
    test_is_not_array<trap_call>();
    test_is_not_array<trap_self_assign>();
    test_is_not_array<trap_deref>();
    test_is_not_array<trap_array_subscript>();

    test_is_not_array<void()>();
    test_is_not_array<void()&>();
    test_is_not_array<void() &&>();
    test_is_not_array<void() const>();
    test_is_not_array<void() const&>();
    test_is_not_array<void() const&&>();
    test_is_not_array<void() volatile>();
    test_is_not_array<void() volatile&>();
    test_is_not_array<void() volatile&&>();
    test_is_not_array<void() const volatile>();
    test_is_not_array<void() const volatile&>();
    test_is_not_array<void() const volatile&&>();
    test_is_not_array<void() noexcept>();
    test_is_not_array<void() & noexcept>();
    test_is_not_array<void() && noexcept>();
    test_is_not_array<void() const noexcept>();
    test_is_not_array<void() const & noexcept>();
    test_is_not_array<void() const && noexcept>();
    test_is_not_array<void() volatile noexcept>();
    test_is_not_array<void() volatile & noexcept>();
    test_is_not_array<void() volatile && noexcept>();
    test_is_not_array<void() const volatile noexcept>();
    test_is_not_array<void() const volatile & noexcept>();
    test_is_not_array<void() const volatile && noexcept>();

    test_is_not_array<void(int)>();
    test_is_not_array<void(int)&>();
    test_is_not_array<void(int) &&>();
    test_is_not_array<void(int) const>();
    test_is_not_array<void(int) const&>();
    test_is_not_array<void(int) const&&>();
    test_is_not_array<void(int) volatile>();
    test_is_not_array<void(int) volatile&>();
    test_is_not_array<void(int) volatile&&>();
    test_is_not_array<void(int) const volatile>();
    test_is_not_array<void(int) const volatile&>();
    test_is_not_array<void(int) const volatile&&>();
    test_is_not_array<void(int) noexcept>();
    test_is_not_array<void(int) & noexcept>();
    test_is_not_array<void(int) && noexcept>();
    test_is_not_array<void(int) const noexcept>();
    test_is_not_array<void(int) const & noexcept>();
    test_is_not_array<void(int) const && noexcept>();
    test_is_not_array<void(int) volatile noexcept>();
    test_is_not_array<void(int) volatile & noexcept>();
    test_is_not_array<void(int) volatile && noexcept>();
    test_is_not_array<void(int) const volatile noexcept>();
    test_is_not_array<void(int) const volatile & noexcept>();
    test_is_not_array<void(int) const volatile && noexcept>();

    test_is_not_array<void(...)>();
    test_is_not_array<void(...)&>();
    test_is_not_array<void(...) &&>();
    test_is_not_array<void(...) const>();
    test_is_not_array<void(...) const&>();
    test_is_not_array<void(...) const&&>();
    test_is_not_array<void(...) volatile>();
    test_is_not_array<void(...) volatile&>();
    test_is_not_array<void(...) volatile&&>();
    test_is_not_array<void(...) const volatile>();
    test_is_not_array<void(...) const volatile&>();
    test_is_not_array<void(...) const volatile&&>();
    test_is_not_array<void(...) noexcept>();
    test_is_not_array<void(...) & noexcept>();
    test_is_not_array<void(...) && noexcept>();
    test_is_not_array<void(...) const noexcept>();
    test_is_not_array<void(...) const & noexcept>();
    test_is_not_array<void(...) const && noexcept>();
    test_is_not_array<void(...) volatile noexcept>();
    test_is_not_array<void(...) volatile & noexcept>();
    test_is_not_array<void(...) volatile && noexcept>();
    test_is_not_array<void(...) const volatile noexcept>();
    test_is_not_array<void(...) const volatile & noexcept>();
    test_is_not_array<void(...) const volatile && noexcept>();

    test_is_not_array<void(int, ...)>();
    test_is_not_array<void(int, ...)&>();
    test_is_not_array<void(int, ...) &&>();
    test_is_not_array<void(int, ...) const>();
    test_is_not_array<void(int, ...) const&>();
    test_is_not_array<void(int, ...) const&&>();
    test_is_not_array<void(int, ...) volatile>();
    test_is_not_array<void(int, ...) volatile&>();
    test_is_not_array<void(int, ...) volatile&&>();
    test_is_not_array<void(int, ...) const volatile>();
    test_is_not_array<void(int, ...) const volatile&>();
    test_is_not_array<void(int, ...) const volatile&&>();
    test_is_not_array<void(int, ...) noexcept>();
    test_is_not_array<void(int, ...) & noexcept>();
    test_is_not_array<void(int, ...) && noexcept>();
    test_is_not_array<void(int, ...) const noexcept>();
    test_is_not_array<void(int, ...) const & noexcept>();
    test_is_not_array<void(int, ...) const && noexcept>();
    test_is_not_array<void(int, ...) volatile noexcept>();
    test_is_not_array<void(int, ...) volatile & noexcept>();
    test_is_not_array<void(int, ...) volatile && noexcept>();
    test_is_not_array<void(int, ...) const volatile noexcept>();
    test_is_not_array<void(int, ...) const volatile & noexcept>();
    test_is_not_array<void(int, ...) const volatile && noexcept>();

    test_is_not_array<int()>();
    test_is_not_array<int()&>();
    test_is_not_array<int() &&>();
    test_is_not_array<int() const>();
    test_is_not_array<int() const&>();
    test_is_not_array<int() const&&>();
    test_is_not_array<int() volatile>();
    test_is_not_array<int() volatile&>();
    test_is_not_array<int() volatile&&>();
    test_is_not_array<int() const volatile>();
    test_is_not_array<int() const volatile&>();
    test_is_not_array<int() const volatile&&>();
    test_is_not_array<int() noexcept>();
    test_is_not_array<int() & noexcept>();
    test_is_not_array<int() && noexcept>();
    test_is_not_array<int() const noexcept>();
    test_is_not_array<int() const & noexcept>();
    test_is_not_array<int() const && noexcept>();
    test_is_not_array<int() volatile noexcept>();
    test_is_not_array<int() volatile & noexcept>();
    test_is_not_array<int() volatile && noexcept>();
    test_is_not_array<int() const volatile noexcept>();
    test_is_not_array<int() const volatile & noexcept>();
    test_is_not_array<int() const volatile && noexcept>();

    test_is_not_array<int(int)>();
    test_is_not_array<int(int)&>();
    test_is_not_array<int(int) &&>();
    test_is_not_array<int(int) const>();
    test_is_not_array<int(int) const&>();
    test_is_not_array<int(int) const&&>();
    test_is_not_array<int(int) volatile>();
    test_is_not_array<int(int) volatile&>();
    test_is_not_array<int(int) volatile&&>();
    test_is_not_array<int(int) const volatile>();
    test_is_not_array<int(int) const volatile&>();
    test_is_not_array<int(int) const volatile&&>();
    test_is_not_array<int(int) noexcept>();
    test_is_not_array<int(int) & noexcept>();
    test_is_not_array<int(int) && noexcept>();
    test_is_not_array<int(int) const noexcept>();
    test_is_not_array<int(int) const & noexcept>();
    test_is_not_array<int(int) const && noexcept>();
    test_is_not_array<int(int) volatile noexcept>();
    test_is_not_array<int(int) volatile & noexcept>();
    test_is_not_array<int(int) volatile && noexcept>();
    test_is_not_array<int(int) const volatile noexcept>();
    test_is_not_array<int(int) const volatile & noexcept>();
    test_is_not_array<int(int) const volatile && noexcept>();

    test_is_not_array<int(...)>();
    test_is_not_array<int(...)&>();
    test_is_not_array<int(...) &&>();
    test_is_not_array<int(...) const>();
    test_is_not_array<int(...) const&>();
    test_is_not_array<int(...) const&&>();
    test_is_not_array<int(...) volatile>();
    test_is_not_array<int(...) volatile&>();
    test_is_not_array<int(...) volatile&&>();
    test_is_not_array<int(...) const volatile>();
    test_is_not_array<int(...) const volatile&>();
    test_is_not_array<int(...) const volatile&&>();
    test_is_not_array<int(...) noexcept>();
    test_is_not_array<int(...) & noexcept>();
    test_is_not_array<int(...) && noexcept>();
    test_is_not_array<int(...) const noexcept>();
    test_is_not_array<int(...) const & noexcept>();
    test_is_not_array<int(...) const && noexcept>();
    test_is_not_array<int(...) volatile noexcept>();
    test_is_not_array<int(...) volatile & noexcept>();
    test_is_not_array<int(...) volatile && noexcept>();
    test_is_not_array<int(...) const volatile noexcept>();
    test_is_not_array<int(...) const volatile & noexcept>();
    test_is_not_array<int(...) const volatile && noexcept>();

    test_is_not_array<int(int, ...)>();
    test_is_not_array<int(int, ...)&>();
    test_is_not_array<int(int, ...) &&>();
    test_is_not_array<int(int, ...) const>();
    test_is_not_array<int(int, ...) const&>();
    test_is_not_array<int(int, ...) const&&>();
    test_is_not_array<int(int, ...) volatile>();
    test_is_not_array<int(int, ...) volatile&>();
    test_is_not_array<int(int, ...) volatile&&>();
    test_is_not_array<int(int, ...) const volatile>();
    test_is_not_array<int(int, ...) const volatile&>();
    test_is_not_array<int(int, ...) const volatile&&>();
    test_is_not_array<int(int, ...) noexcept>();
    test_is_not_array<int(int, ...) & noexcept>();
    test_is_not_array<int(int, ...) && noexcept>();
    test_is_not_array<int(int, ...) const noexcept>();
    test_is_not_array<int(int, ...) const & noexcept>();
    test_is_not_array<int(int, ...) const && noexcept>();
    test_is_not_array<int(int, ...) volatile noexcept>();
    test_is_not_array<int(int, ...) volatile & noexcept>();
    test_is_not_array<int(int, ...) volatile && noexcept>();
    test_is_not_array<int(int, ...) const volatile noexcept>();
    test_is_not_array<int(int, ...) const volatile & noexcept>();
    test_is_not_array<int(int, ...) const volatile && noexcept>();

    test_is_not_array<void (*)()>();
    test_is_not_array<void (*)() noexcept>();

    test_is_not_array<void (*)(int)>();
    test_is_not_array<void (*)(int) noexcept>();

    test_is_not_array<void (*)(...)>();
    test_is_not_array<void (*)(...) noexcept>();

    test_is_not_array<void (*)(int, ...)>();
    test_is_not_array<void (*)(int, ...) noexcept>();

    test_is_not_array<int (*)()>();
    test_is_not_array<int (*)() noexcept>();

    test_is_not_array<int (*)(int)>();
    test_is_not_array<int (*)(int) noexcept>();

    test_is_not_array<int (*)(...)>();
    test_is_not_array<int (*)(...) noexcept>();

    test_is_not_array<int (*)(int, ...)>();
    test_is_not_array<int (*)(int, ...) noexcept>();

    test_is_not_array<void (&)()>();
    test_is_not_array<void (&)() noexcept>();

    test_is_not_array<void (&)(int)>();
    test_is_not_array<void (&)(int) noexcept>();

    test_is_not_array<void (&)(...)>();
    test_is_not_array<void (&)(...) noexcept>();

    test_is_not_array<void (&)(int, ...)>();
    test_is_not_array<void (&)(int, ...) noexcept>();

    test_is_not_array<int (&)()>();
    test_is_not_array<int (&)() noexcept>();

    test_is_not_array<int (&)(int)>();
    test_is_not_array<int (&)(int) noexcept>();

    test_is_not_array<int (&)(...)>();
    test_is_not_array<int (&)(...) noexcept>();

    test_is_not_array<int (&)(int, ...)>();
    test_is_not_array<int (&)(int, ...) noexcept>();

    test_is_not_array<void (&&)()>();
    test_is_not_array<void (&&)() noexcept>();

    test_is_not_array<void (&&)(int)>();
    test_is_not_array<void (&&)(int) noexcept>();

    test_is_not_array<void (&&)(...)>();
    test_is_not_array<void (&&)(...) noexcept>();

    test_is_not_array<void (&&)(int, ...)>();
    test_is_not_array<void (&&)(int, ...) noexcept>();

    test_is_not_array<int (&&)()>();
    test_is_not_array<int (&&)() noexcept>();

    test_is_not_array<int (&&)(int)>();
    test_is_not_array<int (&&)(int) noexcept>();

    test_is_not_array<int (&&)(...)>();
    test_is_not_array<int (&&)(...) noexcept>();

    test_is_not_array<int (&&)(int, ...)>();
    test_is_not_array<int (&&)(int, ...) noexcept>();

    test_is_not_array<void (class_type::*)()>();
    test_is_not_array<void (class_type::*)()&>();
    test_is_not_array<void (class_type::*)() &&>();
    test_is_not_array<void (class_type::*)() const>();
    test_is_not_array<void (class_type::*)() const&>();
    test_is_not_array<void (class_type::*)() const&&>();
    test_is_not_array<void (class_type::*)() noexcept>();
    test_is_not_array<void (class_type::*)() & noexcept>();
    test_is_not_array<void (class_type::*)() && noexcept>();
    test_is_not_array<void (class_type::*)() const noexcept>();
    test_is_not_array<void (class_type::*)() const & noexcept>();
    test_is_not_array<void (class_type::*)() const && noexcept>();

    test_is_not_array<void (class_type::*)(int)>();
    test_is_not_array<void (class_type::*)(int)&>();
    test_is_not_array<void (class_type::*)(int) &&>();
    test_is_not_array<void (class_type::*)(int) const>();
    test_is_not_array<void (class_type::*)(int) const&>();
    test_is_not_array<void (class_type::*)(int) const&&>();
    test_is_not_array<void (class_type::*)(int) noexcept>();
    test_is_not_array<void (class_type::*)(int) & noexcept>();
    test_is_not_array<void (class_type::*)(int) && noexcept>();
    test_is_not_array<void (class_type::*)(int) const noexcept>();
    test_is_not_array<void (class_type::*)(int) const & noexcept>();
    test_is_not_array<void (class_type::*)(int) const && noexcept>();

    test_is_not_array<void (class_type::*)(...)>();
    test_is_not_array<void (class_type::*)(...)&>();
    test_is_not_array<void (class_type::*)(...) &&>();
    test_is_not_array<void (class_type::*)(...) const>();
    test_is_not_array<void (class_type::*)(...) const&>();
    test_is_not_array<void (class_type::*)(...) const&&>();
    test_is_not_array<void (class_type::*)(...) noexcept>();
    test_is_not_array<void (class_type::*)(...) & noexcept>();
    test_is_not_array<void (class_type::*)(...) && noexcept>();
    test_is_not_array<void (class_type::*)(...) const noexcept>();
    test_is_not_array<void (class_type::*)(...) const & noexcept>();
    test_is_not_array<void (class_type::*)(...) const && noexcept>();

    test_is_not_array<void (class_type::*)(int, ...)>();
    test_is_not_array<void (class_type::*)(int, ...)&>();
    test_is_not_array<void (class_type::*)(int, ...) &&>();
    test_is_not_array<void (class_type::*)(int, ...) const>();
    test_is_not_array<void (class_type::*)(int, ...) const&>();
    test_is_not_array<void (class_type::*)(int, ...) const&&>();
    test_is_not_array<void (class_type::*)(int, ...) noexcept>();
    test_is_not_array<void (class_type::*)(int, ...) & noexcept>();
    test_is_not_array<void (class_type::*)(int, ...) && noexcept>();
    test_is_not_array<void (class_type::*)(int, ...) const noexcept>();
    test_is_not_array<void (class_type::*)(int, ...) const & noexcept>();
    test_is_not_array<void (class_type::*)(int, ...) const && noexcept>();

    test_is_not_array<int (class_type::*)()>();
    test_is_not_array<int (class_type::*)()&>();
    test_is_not_array<int (class_type::*)() &&>();
    test_is_not_array<int (class_type::*)() const>();
    test_is_not_array<int (class_type::*)() const&>();
    test_is_not_array<int (class_type::*)() const&&>();
    test_is_not_array<int (class_type::*)() noexcept>();
    test_is_not_array<int (class_type::*)() & noexcept>();
    test_is_not_array<int (class_type::*)() && noexcept>();
    test_is_not_array<int (class_type::*)() const noexcept>();
    test_is_not_array<int (class_type::*)() const & noexcept>();
    test_is_not_array<int (class_type::*)() const && noexcept>();

    test_is_not_array<int (class_type::*)(int)>();
    test_is_not_array<int (class_type::*)(int)&>();
    test_is_not_array<int (class_type::*)(int) &&>();
    test_is_not_array<int (class_type::*)(int) const>();
    test_is_not_array<int (class_type::*)(int) const&>();
    test_is_not_array<int (class_type::*)(int) const&&>();
    test_is_not_array<int (class_type::*)(int) noexcept>();
    test_is_not_array<int (class_type::*)(int) & noexcept>();
    test_is_not_array<int (class_type::*)(int) && noexcept>();
    test_is_not_array<int (class_type::*)(int) const noexcept>();
    test_is_not_array<int (class_type::*)(int) const & noexcept>();
    test_is_not_array<int (class_type::*)(int) const && noexcept>();

    test_is_not_array<int (class_type::*)(...)>();
    test_is_not_array<int (class_type::*)(...)&>();
    test_is_not_array<int (class_type::*)(...) &&>();
    test_is_not_array<int (class_type::*)(...) const>();
    test_is_not_array<int (class_type::*)(...) const&>();
    test_is_not_array<int (class_type::*)(...) const&&>();
    test_is_not_array<int (class_type::*)(...) noexcept>();
    test_is_not_array<int (class_type::*)(...) & noexcept>();
    test_is_not_array<int (class_type::*)(...) && noexcept>();
    test_is_not_array<int (class_type::*)(...) const noexcept>();
    test_is_not_array<int (class_type::*)(...) const & noexcept>();
    test_is_not_array<int (class_type::*)(...) const && noexcept>();

    test_is_not_array<int (class_type::*)(int, ...)>();
    test_is_not_array<int (class_type::*)(int, ...)&>();
    test_is_not_array<int (class_type::*)(int, ...) &&>();
    test_is_not_array<int (class_type::*)(int, ...) const>();
    test_is_not_array<int (class_type::*)(int, ...) const&>();
    test_is_not_array<int (class_type::*)(int, ...) const&&>();
    test_is_not_array<int (class_type::*)(int, ...) noexcept>();
    test_is_not_array<int (class_type::*)(int, ...) & noexcept>();
    test_is_not_array<int (class_type::*)(int, ...) && noexcept>();
    test_is_not_array<int (class_type::*)(int, ...) const noexcept>();
    test_is_not_array<int (class_type::*)(int, ...) const & noexcept>();
    test_is_not_array<int (class_type::*)(int, ...) const && noexcept>();
}
