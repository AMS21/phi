#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_arithmetic.hpp>
#include <phi/type_traits/is_array.hpp>
#include <phi/type_traits/is_bool.hpp>
#include <phi/type_traits/is_class.hpp>
#include <phi/type_traits/is_compound.hpp>
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
void test_is_member_pointer_impl()
{
    STATIC_REQUIRE(phi::is_member_pointer<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_member_pointer<TypeT>::value);

    STATIC_REQUIRE(phi::is_member_object_pointer<TypeT>::value ||
                   phi::is_member_function_pointer<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_arithmetic<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_array<TypeT>::value);
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

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_member_pointer_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_not_member_pointer_v<TypeT>);

    STATIC_REQUIRE(phi::is_member_object_pointer_v<TypeT> ||
                   phi::is_member_function_pointer_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_arithmetic_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_array_v<TypeT>);
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
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_member_pointer<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_member_pointer<TypeT>);

    // Standard compatibility
    STATIC_REQUIRE(std::is_member_pointer<TypeT>::value);
}

template <typename TypeT>
void test_is_member_pointer()
{
    test_is_member_pointer_impl<TypeT>();
    test_is_member_pointer_impl<const TypeT>();
    test_is_member_pointer_impl<volatile TypeT>();
    test_is_member_pointer_impl<const volatile TypeT>();
}

template <typename TypeT>
void test_is_not_member_pointer_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_member_pointer<TypeT>::value);
    STATIC_REQUIRE(phi::is_not_member_pointer<TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_member_pointer_v<TypeT>);
    STATIC_REQUIRE(phi::is_not_member_pointer_v<TypeT>);
#endif

    // Standard compatibility
    STATIC_REQUIRE_FALSE(std::is_member_pointer<TypeT>::value);
}

template <typename TypeT>
void test_is_not_member_pointer()
{
    test_is_not_member_pointer_impl<TypeT>();
    test_is_not_member_pointer_impl<const TypeT>();
    test_is_not_member_pointer_impl<volatile TypeT>();
    test_is_not_member_pointer_impl<const volatile TypeT>();
}

TEST_CASE("is_member_pointer")
{
    // Member object pointers
    test_is_member_pointer<member_object_ptr>();
    test_is_member_pointer<int abstract::*>();
    test_is_member_pointer<double not_empty::*>();
    test_is_member_pointer<function_ptr empty::*>();
    test_is_member_pointer<void (empty::*)()>();
    test_is_member_pointer<int abstract::*>();
    test_is_member_pointer<double not_empty::*>();
    test_is_member_pointer<function_ptr empty::*>();
    test_is_member_pointer<int class_type::*>();

    // Member function pointers
    test_is_member_pointer<member_function_ptr>();
    test_is_member_pointer<int (empty::*)(int, ...) const>();
    test_is_member_pointer<int (empty::*)(int, long, long) const noexcept>();
    test_is_member_pointer<int (empty::*)() & noexcept>();
    test_is_member_pointer<int empty::*>();
    test_is_member_pointer<void (empty::*)(int)>();

    test_is_member_pointer<void (class_type::*)()>();
    test_is_member_pointer<void (class_type::*)(int)>();
    test_is_member_pointer<void (class_type::*)(int, char)>();

    test_is_member_pointer<void (class_type::*)()>();
    test_is_member_pointer<void (class_type::*)(int)>();
    test_is_member_pointer<void (class_type::*)(int, char)>();

    test_is_member_pointer<void (class_type::*)() const>();
    test_is_member_pointer<void (class_type::*)(int) const>();
    test_is_member_pointer<void (class_type::*)(int, char) const>();

    test_is_member_pointer<void (class_type::*)() volatile>();
    test_is_member_pointer<void (class_type::*)(int) volatile>();
    test_is_member_pointer<void (class_type::*)(int, char) volatile>();

    test_is_member_pointer<void (class_type::*)(...)>();
    test_is_member_pointer<void (class_type::*)(int, ...)>();
    test_is_member_pointer<void (class_type::*)(int, char, ...)>();

    test_is_member_pointer<void (class_type::*)(...) const>();
    test_is_member_pointer<void (class_type::*)(int, ...) const>();
    test_is_member_pointer<void (class_type::*)(int, char, ...) const>();

    test_is_member_pointer<void (class_type::*)(...) volatile>();
    test_is_member_pointer<void (class_type::*)(int, ...) volatile>();
    test_is_member_pointer<void (class_type::*)(int, char, ...) volatile>();

    // Noexcept qualifiers
    test_is_member_pointer<void (class_type::*)() noexcept>();
    test_is_member_pointer<void (class_type::*)(int) noexcept>();
    test_is_member_pointer<void (class_type::*)(int, char) noexcept>();

    test_is_member_pointer<void (class_type::*)() const noexcept>();
    test_is_member_pointer<void (class_type::*)(int) const noexcept>();
    test_is_member_pointer<void (class_type::*)(int, char) const noexcept>();

    test_is_member_pointer<void (class_type::*)() volatile noexcept>();
    test_is_member_pointer<void (class_type::*)(int) volatile noexcept>();
    test_is_member_pointer<void (class_type::*)(int, char) volatile noexcept>();

    test_is_member_pointer<void (class_type::*)(...) noexcept>();
    test_is_member_pointer<void (class_type::*)(int, ...) noexcept>();
    test_is_member_pointer<void (class_type::*)(int, char, ...) noexcept>();

    test_is_member_pointer<void (class_type::*)(...) const noexcept>();
    test_is_member_pointer<void (class_type::*)(int, ...) const noexcept>();
    test_is_member_pointer<void (class_type::*)(int, char, ...) const noexcept>();

    test_is_member_pointer<void (class_type::*)(...) volatile noexcept>();
    test_is_member_pointer<void (class_type::*)(int, ...) volatile noexcept>();
    test_is_member_pointer<void (class_type::*)(int, char, ...) volatile noexcept>();

    // lvalue qualifiers
    test_is_member_pointer<void (class_type::*)()&>();
    test_is_member_pointer<void (class_type::*)(int)&>();
    test_is_member_pointer<void (class_type::*)(int, char)&>();
    test_is_member_pointer<void (class_type::*)(...)&>();
    test_is_member_pointer<void (class_type::*)(int, ...)&>();
    test_is_member_pointer<void (class_type::*)(int, char, ...)&>();

    test_is_member_pointer<void (class_type::*)() const&>();
    test_is_member_pointer<void (class_type::*)(int) const&>();
    test_is_member_pointer<void (class_type::*)(int, char) const&>();
    test_is_member_pointer<void (class_type::*)(...) const&>();
    test_is_member_pointer<void (class_type::*)(int, ...) const&>();
    test_is_member_pointer<void (class_type::*)(int, char, ...) const&>();

    test_is_member_pointer<void (class_type::*)() volatile&>();
    test_is_member_pointer<void (class_type::*)(int) volatile&>();
    test_is_member_pointer<void (class_type::*)(int, char) volatile&>();
    test_is_member_pointer<void (class_type::*)(...) volatile&>();
    test_is_member_pointer<void (class_type::*)(int, ...) volatile&>();
    test_is_member_pointer<void (class_type::*)(int, char, ...) volatile&>();

    test_is_member_pointer<void (class_type::*)() const volatile&>();
    test_is_member_pointer<void (class_type::*)(int) const volatile&>();
    test_is_member_pointer<void (class_type::*)(int, char) const volatile&>();
    test_is_member_pointer<void (class_type::*)(...) const volatile&>();
    test_is_member_pointer<void (class_type::*)(int, ...) const volatile&>();
    test_is_member_pointer<void (class_type::*)(int, char, ...) const volatile&>();

    // Lvalue qualifiers with noexcept
    test_is_member_pointer<void (class_type::*)() & noexcept>();
    test_is_member_pointer<void (class_type::*)(int) & noexcept>();
    test_is_member_pointer<void (class_type::*)(int, char) & noexcept>();
    test_is_member_pointer<void (class_type::*)(...) & noexcept>();
    test_is_member_pointer<void (class_type::*)(int, ...) & noexcept>();
    test_is_member_pointer<void (class_type::*)(int, char, ...) & noexcept>();

    test_is_member_pointer<void (class_type::*)() const & noexcept>();
    test_is_member_pointer<void (class_type::*)(int) const & noexcept>();
    test_is_member_pointer<void (class_type::*)(int, char) const & noexcept>();
    test_is_member_pointer<void (class_type::*)(...) const & noexcept>();
    test_is_member_pointer<void (class_type::*)(int, ...) const & noexcept>();
    test_is_member_pointer<void (class_type::*)(int, char, ...) const & noexcept>();

    test_is_member_pointer<void (class_type::*)() volatile & noexcept>();
    test_is_member_pointer<void (class_type::*)(int) volatile & noexcept>();
    test_is_member_pointer<void (class_type::*)(int, char) volatile & noexcept>();
    test_is_member_pointer<void (class_type::*)(...) volatile & noexcept>();
    test_is_member_pointer<void (class_type::*)(int, ...) volatile & noexcept>();
    test_is_member_pointer<void (class_type::*)(int, char, ...) volatile & noexcept>();

    test_is_member_pointer<void (class_type::*)() const volatile & noexcept>();
    test_is_member_pointer<void (class_type::*)(int) const volatile & noexcept>();
    test_is_member_pointer<void (class_type::*)(int, char) const volatile & noexcept>();
    test_is_member_pointer<void (class_type::*)(...) const volatile & noexcept>();
    test_is_member_pointer<void (class_type::*)(int, ...) const volatile & noexcept>();
    test_is_member_pointer<void (class_type::*)(int, char, ...) const volatile & noexcept>();

    // RValue qualifiers
    test_is_member_pointer<void (class_type::*)() &&>();
    test_is_member_pointer<void (class_type::*)(int) &&>();
    test_is_member_pointer<void (class_type::*)(int, char) &&>();
    test_is_member_pointer<void (class_type::*)(...) &&>();
    test_is_member_pointer<void (class_type::*)(int, ...) &&>();
    test_is_member_pointer<void (class_type::*)(int, char, ...) &&>();

    test_is_member_pointer<void (class_type::*)() const&&>();
    test_is_member_pointer<void (class_type::*)(int) const&&>();
    test_is_member_pointer<void (class_type::*)(int, char) const&&>();
    test_is_member_pointer<void (class_type::*)(...) const&&>();
    test_is_member_pointer<void (class_type::*)(int, ...) const&&>();
    test_is_member_pointer<void (class_type::*)(int, char, ...) const&&>();

    test_is_member_pointer<void (class_type::*)() volatile&&>();
    test_is_member_pointer<void (class_type::*)(int) volatile&&>();
    test_is_member_pointer<void (class_type::*)(int, char) volatile&&>();
    test_is_member_pointer<void (class_type::*)(...) volatile&&>();
    test_is_member_pointer<void (class_type::*)(int, ...) volatile&&>();
    test_is_member_pointer<void (class_type::*)(int, char, ...) volatile&&>();

    test_is_member_pointer<void (class_type::*)() const volatile&&>();
    test_is_member_pointer<void (class_type::*)(int) const volatile&&>();
    test_is_member_pointer<void (class_type::*)(int, char) const volatile&&>();
    test_is_member_pointer<void (class_type::*)(...) const volatile&&>();
    test_is_member_pointer<void (class_type::*)(int, ...) const volatile&&>();
    test_is_member_pointer<void (class_type::*)(int, char, ...) const volatile&&>();

    // RValue qualifiers with noexcept
    test_is_member_pointer<void (class_type::*)() && noexcept>();
    test_is_member_pointer<void (class_type::*)(int) && noexcept>();
    test_is_member_pointer<void (class_type::*)(int, char) && noexcept>();
    test_is_member_pointer<void (class_type::*)(...) && noexcept>();
    test_is_member_pointer<void (class_type::*)(int, ...) && noexcept>();
    test_is_member_pointer<void (class_type::*)(int, char, ...) && noexcept>();

    test_is_member_pointer<void (class_type::*)() const && noexcept>();
    test_is_member_pointer<void (class_type::*)(int) const && noexcept>();
    test_is_member_pointer<void (class_type::*)(int, char) const && noexcept>();
    test_is_member_pointer<void (class_type::*)(...) const && noexcept>();
    test_is_member_pointer<void (class_type::*)(int, ...) const && noexcept>();
    test_is_member_pointer<void (class_type::*)(int, char, ...) const && noexcept>();

    test_is_member_pointer<void (class_type::*)() volatile && noexcept>();
    test_is_member_pointer<void (class_type::*)(int) volatile && noexcept>();
    test_is_member_pointer<void (class_type::*)(int, char) volatile && noexcept>();
    test_is_member_pointer<void (class_type::*)(...) volatile && noexcept>();
    test_is_member_pointer<void (class_type::*)(int, ...) volatile && noexcept>();
    test_is_member_pointer<void (class_type::*)(int, char, ...) volatile && noexcept>();

    test_is_member_pointer<void (class_type::*)() const volatile && noexcept>();
    test_is_member_pointer<void (class_type::*)(int) const volatile && noexcept>();
    test_is_member_pointer<void (class_type::*)(int, char) const volatile && noexcept>();
    test_is_member_pointer<void (class_type::*)(...) const volatile && noexcept>();
    test_is_member_pointer<void (class_type::*)(int, ...) const volatile && noexcept>();
    test_is_member_pointer<void (class_type::*)(int, char, ...) const volatile && noexcept>();

    // Non member pointers
    test_is_not_member_pointer<void>();
    test_is_not_member_pointer<phi::nullptr_t>();
    test_is_not_member_pointer<bool>();
    test_is_not_member_pointer<char>();
    test_is_not_member_pointer<signed char>();
    test_is_not_member_pointer<unsigned char>();
    test_is_not_member_pointer<short>();
    test_is_not_member_pointer<unsigned short>();
    test_is_not_member_pointer<int>();
    test_is_not_member_pointer<unsigned int>();
    test_is_not_member_pointer<long>();
    test_is_not_member_pointer<unsigned long>();
    test_is_not_member_pointer<long long>();
    test_is_not_member_pointer<unsigned long long>();
    test_is_not_member_pointer<float>();
    test_is_not_member_pointer<double>();
    test_is_not_member_pointer<long double>();
    test_is_not_member_pointer<char8_t>();
    test_is_not_member_pointer<char16_t>();
    test_is_not_member_pointer<char32_t>();
    test_is_not_member_pointer<wchar_t>();

    test_is_not_member_pointer<phi::boolean>();
    test_is_not_member_pointer<phi::integer<signed char>>();
    test_is_not_member_pointer<phi::integer<unsigned char>>();
    test_is_not_member_pointer<phi::integer<short>>();
    test_is_not_member_pointer<phi::integer<unsigned short>>();
    test_is_not_member_pointer<phi::integer<int>>();
    test_is_not_member_pointer<phi::integer<unsigned int>>();
    test_is_not_member_pointer<phi::integer<long>>();
    test_is_not_member_pointer<phi::integer<unsigned long>>();
    test_is_not_member_pointer<phi::integer<long long>>();
    test_is_not_member_pointer<phi::integer<unsigned long long>>();
    test_is_not_member_pointer<phi::floating_point<float>>();
    test_is_not_member_pointer<phi::floating_point<double>>();
    test_is_not_member_pointer<phi::floating_point<long double>>();

    test_is_not_member_pointer<std::vector<int>>();
    test_is_not_member_pointer<phi::scope_ptr<int>>();

    test_is_not_member_pointer<int&>();
    test_is_not_member_pointer<const int&>();
    test_is_not_member_pointer<volatile int&>();
    test_is_not_member_pointer<const volatile int&>();
    test_is_not_member_pointer<int&&>();
    test_is_not_member_pointer<const int&&>();
    test_is_not_member_pointer<volatile int&&>();
    test_is_not_member_pointer<const volatile int&&>();
    test_is_not_member_pointer<int*>();
    test_is_not_member_pointer<const int*>();
    test_is_not_member_pointer<volatile int*>();
    test_is_not_member_pointer<const volatile int*>();
    test_is_not_member_pointer<int**>();
    test_is_not_member_pointer<const int**>();
    test_is_not_member_pointer<volatile int**>();
    test_is_not_member_pointer<const volatile int**>();
    test_is_not_member_pointer<int*&>();
    test_is_not_member_pointer<const int*&>();
    test_is_not_member_pointer<volatile int*&>();
    test_is_not_member_pointer<const volatile int*&>();
    test_is_not_member_pointer<int*&&>();
    test_is_not_member_pointer<const int*&&>();
    test_is_not_member_pointer<volatile int*&&>();
    test_is_not_member_pointer<const volatile int*&&>();
    test_is_not_member_pointer<void*>();
    test_is_not_member_pointer<char[3]>();
    test_is_not_member_pointer<char[]>();
    test_is_not_member_pointer<char* [3]>();
    test_is_not_member_pointer<char*[]>();
    test_is_not_member_pointer<int(*)[3]>();
    test_is_not_member_pointer<int(*)[]>();
    test_is_not_member_pointer<int(&)[3]>();
    test_is_not_member_pointer<int(&)[]>();
    test_is_not_member_pointer<int(&&)[3]>();
    test_is_not_member_pointer<int(&&)[]>();
    test_is_not_member_pointer<char[3][2]>();
    test_is_not_member_pointer<char[][2]>();
    test_is_not_member_pointer<char* [3][2]>();
    test_is_not_member_pointer<char*[][2]>();
    test_is_not_member_pointer<int(*)[3][2]>();
    test_is_not_member_pointer<int(*)[][2]>();
    test_is_not_member_pointer<int(&)[3][2]>();
    test_is_not_member_pointer<int(&)[][2]>();
    test_is_not_member_pointer<int(&&)[3][2]>();
    test_is_not_member_pointer<int(&&)[][2]>();
    test_is_not_member_pointer<class_type>();
    test_is_not_member_pointer<class_type[]>();
    test_is_not_member_pointer<class_type[2]>();
    test_is_not_member_pointer<template_type<void>>();
    test_is_not_member_pointer<template_type<int>>();
    test_is_not_member_pointer<template_type<class_type>>();
    test_is_not_member_pointer<template_type<incomplete_type>>();
    test_is_not_member_pointer<variadic_template<>>();
    test_is_not_member_pointer<variadic_template<void>>();
    test_is_not_member_pointer<variadic_template<int>>();
    test_is_not_member_pointer<variadic_template<class_type>>();
    test_is_not_member_pointer<variadic_template<incomplete_type>>();
    test_is_not_member_pointer<variadic_template<int, void, class_type, volatile char[]>>();
    test_is_not_member_pointer<public_derived_from<base>>();
    test_is_not_member_pointer<public_derived_from<derived>>();
    test_is_not_member_pointer<public_derived_from<class_type>>();
    test_is_not_member_pointer<private_derived_from<base>>();
    test_is_not_member_pointer<private_derived_from<derived>>();
    test_is_not_member_pointer<private_derived_from<class_type>>();
    test_is_not_member_pointer<protected_derived_from<base>>();
    test_is_not_member_pointer<protected_derived_from<derived>>();
    test_is_not_member_pointer<protected_derived_from<class_type>>();
    test_is_not_member_pointer<union_type>();
    test_is_not_member_pointer<non_empty_union>();
    test_is_not_member_pointer<empty>();
    test_is_not_member_pointer<not_empty>();
    test_is_not_member_pointer<bit_zero>();
    test_is_not_member_pointer<bit_one>();
    test_is_not_member_pointer<base>();
    test_is_not_member_pointer<derived>();
    test_is_not_member_pointer<abstract>();
    test_is_not_member_pointer<public_abstract>();
    test_is_not_member_pointer<private_abstract>();
    test_is_not_member_pointer<protected_abstract>();
    test_is_not_member_pointer<abstract_template<int>>();
    test_is_not_member_pointer<abstract_template<double>>();
    test_is_not_member_pointer<abstract_template<class_type>>();
    test_is_not_member_pointer<abstract_template<incomplete_type>>();
    test_is_not_member_pointer<final_type>();
    test_is_not_member_pointer<public_destructor>();
    test_is_not_member_pointer<protected_destructor>();
    test_is_not_member_pointer<private_destructor>();
    test_is_not_member_pointer<virtual_public_destructor>();
    test_is_not_member_pointer<virtual_protected_destructor>();
    test_is_not_member_pointer<virtual_private_destructor>();
    test_is_not_member_pointer<pure_public_destructor>();
    test_is_not_member_pointer<pure_protected_destructor>();
    test_is_not_member_pointer<pure_private_destructor>();
    test_is_not_member_pointer<deleted_public_destructor>();
    test_is_not_member_pointer<deleted_protected_destructor>();
    test_is_not_member_pointer<deleted_private_destructor>();
    test_is_not_member_pointer<deleted_virtual_public_destructor>();
    test_is_not_member_pointer<deleted_virtual_protected_destructor>();
    test_is_not_member_pointer<deleted_virtual_private_destructor>();
    test_is_not_member_pointer<Enum>();
    test_is_not_member_pointer<EnumSigned>();
    test_is_not_member_pointer<EnumUnsigned>();
    test_is_not_member_pointer<EnumClass>();
    test_is_not_member_pointer<EnumStruct>();
    test_is_not_member_pointer<function_type>();
    test_is_not_member_pointer<function_ptr>();
    test_is_member_pointer<member_object_ptr>();
    test_is_member_pointer<member_function_ptr>();
    test_is_not_member_pointer<incomplete_type>();
    test_is_not_member_pointer<incomplete_template<void>>();
    test_is_not_member_pointer<incomplete_template<int>>();
    test_is_not_member_pointer<incomplete_template<class_type>>();
    test_is_not_member_pointer<incomplete_template<incomplete_type>>();
    test_is_not_member_pointer<incomplete_variadic_template<>>();
    test_is_not_member_pointer<incomplete_variadic_template<void>>();
    test_is_not_member_pointer<incomplete_variadic_template<int>>();
    test_is_not_member_pointer<incomplete_variadic_template<class_type>>();
    test_is_not_member_pointer<incomplete_variadic_template<incomplete_type>>();
    test_is_not_member_pointer<
            incomplete_variadic_template<int, void, class_type, volatile char[]>>();
    test_is_member_pointer<int class_type::*>();
    test_is_member_pointer<float class_type::*>();
    test_is_member_pointer<void * class_type::*>();
    test_is_member_pointer<int * class_type::*>();
    test_is_not_member_pointer<int class_type::*&>();
    test_is_not_member_pointer<float class_type::*&>();
    test_is_not_member_pointer<void * class_type::*&>();
    test_is_not_member_pointer<int * class_type::*&>();
    test_is_not_member_pointer<int class_type::*&&>();
    test_is_not_member_pointer<float class_type::*&&>();
    test_is_not_member_pointer<void * class_type::*&&>();
    test_is_not_member_pointer<int * class_type::*&&>();
    test_is_member_pointer<int class_type::* const>();
    test_is_member_pointer<float class_type::* const>();
    test_is_member_pointer<void * class_type::* const>();
    test_is_not_member_pointer<int class_type::* const&>();
    test_is_not_member_pointer<float class_type::* const&>();
    test_is_not_member_pointer<void * class_type::* const&>();
    test_is_not_member_pointer<int class_type::* const&&>();
    test_is_not_member_pointer<float class_type::* const&&>();
    test_is_not_member_pointer<void * class_type::* const&&>();
    test_is_member_pointer<int class_type::* volatile>();
    test_is_member_pointer<float class_type::* volatile>();
    test_is_member_pointer<void * class_type::* volatile>();
    test_is_not_member_pointer<int class_type::* volatile&>();
    test_is_not_member_pointer<float class_type::* volatile&>();
    test_is_not_member_pointer<void * class_type::* volatile&>();
    test_is_not_member_pointer<int class_type::* volatile&&>();
    test_is_not_member_pointer<float class_type::* volatile&&>();
    test_is_not_member_pointer<void * class_type::* volatile&&>();
    test_is_member_pointer<int class_type::* const volatile>();
    test_is_member_pointer<float class_type::* const volatile>();
    test_is_member_pointer<void * class_type::* const volatile>();
    test_is_not_member_pointer<int class_type::* const volatile&>();
    test_is_not_member_pointer<float class_type::* const volatile&>();
    test_is_not_member_pointer<void * class_type::* const volatile&>();
    test_is_not_member_pointer<int class_type::* const volatile&&>();
    test_is_not_member_pointer<float class_type::* const volatile&&>();
    test_is_not_member_pointer<void * class_type::* const volatile&&>();
    test_is_not_member_pointer<non_copyable>();
    test_is_not_member_pointer<non_moveable>();
    test_is_not_member_pointer<non_constructible>();
    test_is_not_member_pointer<tracked>();
    test_is_not_member_pointer<trap_constructible>();
    test_is_not_member_pointer<trap_implicit_conversion>();
    test_is_not_member_pointer<trap_comma>();
    test_is_not_member_pointer<trap_call>();
    test_is_not_member_pointer<trap_self_assign>();
    test_is_not_member_pointer<trap_deref>();
    test_is_not_member_pointer<trap_array_subscript>();

    test_is_not_member_pointer<void()>();
    test_is_not_member_pointer<void()&>();
    test_is_not_member_pointer<void() &&>();
    test_is_not_member_pointer<void() const>();
    test_is_not_member_pointer<void() const&>();
    test_is_not_member_pointer<void() const&&>();
    test_is_not_member_pointer<void() volatile>();
    test_is_not_member_pointer<void() volatile&>();
    test_is_not_member_pointer<void() volatile&&>();
    test_is_not_member_pointer<void() const volatile>();
    test_is_not_member_pointer<void() const volatile&>();
    test_is_not_member_pointer<void() const volatile&&>();
    test_is_not_member_pointer<void() noexcept>();
    test_is_not_member_pointer<void() & noexcept>();
    test_is_not_member_pointer<void() && noexcept>();
    test_is_not_member_pointer<void() const noexcept>();
    test_is_not_member_pointer<void() const & noexcept>();
    test_is_not_member_pointer<void() const && noexcept>();
    test_is_not_member_pointer<void() volatile noexcept>();
    test_is_not_member_pointer<void() volatile & noexcept>();
    test_is_not_member_pointer<void() volatile && noexcept>();
    test_is_not_member_pointer<void() const volatile noexcept>();
    test_is_not_member_pointer<void() const volatile & noexcept>();
    test_is_not_member_pointer<void() const volatile && noexcept>();

    test_is_not_member_pointer<void(int)>();
    test_is_not_member_pointer<void(int)&>();
    test_is_not_member_pointer<void(int) &&>();
    test_is_not_member_pointer<void(int) const>();
    test_is_not_member_pointer<void(int) const&>();
    test_is_not_member_pointer<void(int) const&&>();
    test_is_not_member_pointer<void(int) volatile>();
    test_is_not_member_pointer<void(int) volatile&>();
    test_is_not_member_pointer<void(int) volatile&&>();
    test_is_not_member_pointer<void(int) const volatile>();
    test_is_not_member_pointer<void(int) const volatile&>();
    test_is_not_member_pointer<void(int) const volatile&&>();
    test_is_not_member_pointer<void(int) noexcept>();
    test_is_not_member_pointer<void(int) & noexcept>();
    test_is_not_member_pointer<void(int) && noexcept>();
    test_is_not_member_pointer<void(int) const noexcept>();
    test_is_not_member_pointer<void(int) const & noexcept>();
    test_is_not_member_pointer<void(int) const && noexcept>();
    test_is_not_member_pointer<void(int) volatile noexcept>();
    test_is_not_member_pointer<void(int) volatile & noexcept>();
    test_is_not_member_pointer<void(int) volatile && noexcept>();
    test_is_not_member_pointer<void(int) const volatile noexcept>();
    test_is_not_member_pointer<void(int) const volatile & noexcept>();
    test_is_not_member_pointer<void(int) const volatile && noexcept>();

    test_is_not_member_pointer<void(...)>();
    test_is_not_member_pointer<void(...)&>();
    test_is_not_member_pointer<void(...) &&>();
    test_is_not_member_pointer<void(...) const>();
    test_is_not_member_pointer<void(...) const&>();
    test_is_not_member_pointer<void(...) const&&>();
    test_is_not_member_pointer<void(...) volatile>();
    test_is_not_member_pointer<void(...) volatile&>();
    test_is_not_member_pointer<void(...) volatile&&>();
    test_is_not_member_pointer<void(...) const volatile>();
    test_is_not_member_pointer<void(...) const volatile&>();
    test_is_not_member_pointer<void(...) const volatile&&>();
    test_is_not_member_pointer<void(...) noexcept>();
    test_is_not_member_pointer<void(...) & noexcept>();
    test_is_not_member_pointer<void(...) && noexcept>();
    test_is_not_member_pointer<void(...) const noexcept>();
    test_is_not_member_pointer<void(...) const & noexcept>();
    test_is_not_member_pointer<void(...) const && noexcept>();
    test_is_not_member_pointer<void(...) volatile noexcept>();
    test_is_not_member_pointer<void(...) volatile & noexcept>();
    test_is_not_member_pointer<void(...) volatile && noexcept>();
    test_is_not_member_pointer<void(...) const volatile noexcept>();
    test_is_not_member_pointer<void(...) const volatile & noexcept>();
    test_is_not_member_pointer<void(...) const volatile && noexcept>();

    test_is_not_member_pointer<void(int, ...)>();
    test_is_not_member_pointer<void(int, ...)&>();
    test_is_not_member_pointer<void(int, ...) &&>();
    test_is_not_member_pointer<void(int, ...) const>();
    test_is_not_member_pointer<void(int, ...) const&>();
    test_is_not_member_pointer<void(int, ...) const&&>();
    test_is_not_member_pointer<void(int, ...) volatile>();
    test_is_not_member_pointer<void(int, ...) volatile&>();
    test_is_not_member_pointer<void(int, ...) volatile&&>();
    test_is_not_member_pointer<void(int, ...) const volatile>();
    test_is_not_member_pointer<void(int, ...) const volatile&>();
    test_is_not_member_pointer<void(int, ...) const volatile&&>();
    test_is_not_member_pointer<void(int, ...) noexcept>();
    test_is_not_member_pointer<void(int, ...) & noexcept>();
    test_is_not_member_pointer<void(int, ...) && noexcept>();
    test_is_not_member_pointer<void(int, ...) const noexcept>();
    test_is_not_member_pointer<void(int, ...) const & noexcept>();
    test_is_not_member_pointer<void(int, ...) const && noexcept>();
    test_is_not_member_pointer<void(int, ...) volatile noexcept>();
    test_is_not_member_pointer<void(int, ...) volatile & noexcept>();
    test_is_not_member_pointer<void(int, ...) volatile && noexcept>();
    test_is_not_member_pointer<void(int, ...) const volatile noexcept>();
    test_is_not_member_pointer<void(int, ...) const volatile & noexcept>();
    test_is_not_member_pointer<void(int, ...) const volatile && noexcept>();

    test_is_not_member_pointer<int()>();
    test_is_not_member_pointer<int()&>();
    test_is_not_member_pointer<int() &&>();
    test_is_not_member_pointer<int() const>();
    test_is_not_member_pointer<int() const&>();
    test_is_not_member_pointer<int() const&&>();
    test_is_not_member_pointer<int() volatile>();
    test_is_not_member_pointer<int() volatile&>();
    test_is_not_member_pointer<int() volatile&&>();
    test_is_not_member_pointer<int() const volatile>();
    test_is_not_member_pointer<int() const volatile&>();
    test_is_not_member_pointer<int() const volatile&&>();
    test_is_not_member_pointer<int() noexcept>();
    test_is_not_member_pointer<int() & noexcept>();
    test_is_not_member_pointer<int() && noexcept>();
    test_is_not_member_pointer<int() const noexcept>();
    test_is_not_member_pointer<int() const & noexcept>();
    test_is_not_member_pointer<int() const && noexcept>();
    test_is_not_member_pointer<int() volatile noexcept>();
    test_is_not_member_pointer<int() volatile & noexcept>();
    test_is_not_member_pointer<int() volatile && noexcept>();
    test_is_not_member_pointer<int() const volatile noexcept>();
    test_is_not_member_pointer<int() const volatile & noexcept>();
    test_is_not_member_pointer<int() const volatile && noexcept>();

    test_is_not_member_pointer<int(int)>();
    test_is_not_member_pointer<int(int)&>();
    test_is_not_member_pointer<int(int) &&>();
    test_is_not_member_pointer<int(int) const>();
    test_is_not_member_pointer<int(int) const&>();
    test_is_not_member_pointer<int(int) const&&>();
    test_is_not_member_pointer<int(int) volatile>();
    test_is_not_member_pointer<int(int) volatile&>();
    test_is_not_member_pointer<int(int) volatile&&>();
    test_is_not_member_pointer<int(int) const volatile>();
    test_is_not_member_pointer<int(int) const volatile&>();
    test_is_not_member_pointer<int(int) const volatile&&>();
    test_is_not_member_pointer<int(int) noexcept>();
    test_is_not_member_pointer<int(int) & noexcept>();
    test_is_not_member_pointer<int(int) && noexcept>();
    test_is_not_member_pointer<int(int) const noexcept>();
    test_is_not_member_pointer<int(int) const & noexcept>();
    test_is_not_member_pointer<int(int) const && noexcept>();
    test_is_not_member_pointer<int(int) volatile noexcept>();
    test_is_not_member_pointer<int(int) volatile & noexcept>();
    test_is_not_member_pointer<int(int) volatile && noexcept>();
    test_is_not_member_pointer<int(int) const volatile noexcept>();
    test_is_not_member_pointer<int(int) const volatile & noexcept>();
    test_is_not_member_pointer<int(int) const volatile && noexcept>();

    test_is_not_member_pointer<int(...)>();
    test_is_not_member_pointer<int(...)&>();
    test_is_not_member_pointer<int(...) &&>();
    test_is_not_member_pointer<int(...) const>();
    test_is_not_member_pointer<int(...) const&>();
    test_is_not_member_pointer<int(...) const&&>();
    test_is_not_member_pointer<int(...) volatile>();
    test_is_not_member_pointer<int(...) volatile&>();
    test_is_not_member_pointer<int(...) volatile&&>();
    test_is_not_member_pointer<int(...) const volatile>();
    test_is_not_member_pointer<int(...) const volatile&>();
    test_is_not_member_pointer<int(...) const volatile&&>();
    test_is_not_member_pointer<int(...) noexcept>();
    test_is_not_member_pointer<int(...) & noexcept>();
    test_is_not_member_pointer<int(...) && noexcept>();
    test_is_not_member_pointer<int(...) const noexcept>();
    test_is_not_member_pointer<int(...) const & noexcept>();
    test_is_not_member_pointer<int(...) const && noexcept>();
    test_is_not_member_pointer<int(...) volatile noexcept>();
    test_is_not_member_pointer<int(...) volatile & noexcept>();
    test_is_not_member_pointer<int(...) volatile && noexcept>();
    test_is_not_member_pointer<int(...) const volatile noexcept>();
    test_is_not_member_pointer<int(...) const volatile & noexcept>();
    test_is_not_member_pointer<int(...) const volatile && noexcept>();

    test_is_not_member_pointer<int(int, ...)>();
    test_is_not_member_pointer<int(int, ...)&>();
    test_is_not_member_pointer<int(int, ...) &&>();
    test_is_not_member_pointer<int(int, ...) const>();
    test_is_not_member_pointer<int(int, ...) const&>();
    test_is_not_member_pointer<int(int, ...) const&&>();
    test_is_not_member_pointer<int(int, ...) volatile>();
    test_is_not_member_pointer<int(int, ...) volatile&>();
    test_is_not_member_pointer<int(int, ...) volatile&&>();
    test_is_not_member_pointer<int(int, ...) const volatile>();
    test_is_not_member_pointer<int(int, ...) const volatile&>();
    test_is_not_member_pointer<int(int, ...) const volatile&&>();
    test_is_not_member_pointer<int(int, ...) noexcept>();
    test_is_not_member_pointer<int(int, ...) & noexcept>();
    test_is_not_member_pointer<int(int, ...) && noexcept>();
    test_is_not_member_pointer<int(int, ...) const noexcept>();
    test_is_not_member_pointer<int(int, ...) const & noexcept>();
    test_is_not_member_pointer<int(int, ...) const && noexcept>();
    test_is_not_member_pointer<int(int, ...) volatile noexcept>();
    test_is_not_member_pointer<int(int, ...) volatile & noexcept>();
    test_is_not_member_pointer<int(int, ...) volatile && noexcept>();
    test_is_not_member_pointer<int(int, ...) const volatile noexcept>();
    test_is_not_member_pointer<int(int, ...) const volatile & noexcept>();
    test_is_not_member_pointer<int(int, ...) const volatile && noexcept>();

    test_is_not_member_pointer<void (*)()>();
    test_is_not_member_pointer<void (*)() noexcept>();

    test_is_not_member_pointer<void (*)(int)>();
    test_is_not_member_pointer<void (*)(int) noexcept>();

    test_is_not_member_pointer<void (*)(...)>();
    test_is_not_member_pointer<void (*)(...) noexcept>();

    test_is_not_member_pointer<void (*)(int, ...)>();
    test_is_not_member_pointer<void (*)(int, ...) noexcept>();

    test_is_not_member_pointer<int (*)()>();
    test_is_not_member_pointer<int (*)() noexcept>();

    test_is_not_member_pointer<int (*)(int)>();
    test_is_not_member_pointer<int (*)(int) noexcept>();

    test_is_not_member_pointer<int (*)(...)>();
    test_is_not_member_pointer<int (*)(...) noexcept>();

    test_is_not_member_pointer<int (*)(int, ...)>();
    test_is_not_member_pointer<int (*)(int, ...) noexcept>();

    test_is_not_member_pointer<void (&)()>();
    test_is_not_member_pointer<void (&)() noexcept>();

    test_is_not_member_pointer<void (&)(int)>();
    test_is_not_member_pointer<void (&)(int) noexcept>();

    test_is_not_member_pointer<void (&)(...)>();
    test_is_not_member_pointer<void (&)(...) noexcept>();

    test_is_not_member_pointer<void (&)(int, ...)>();
    test_is_not_member_pointer<void (&)(int, ...) noexcept>();

    test_is_not_member_pointer<int (&)()>();
    test_is_not_member_pointer<int (&)() noexcept>();

    test_is_not_member_pointer<int (&)(int)>();
    test_is_not_member_pointer<int (&)(int) noexcept>();

    test_is_not_member_pointer<int (&)(...)>();
    test_is_not_member_pointer<int (&)(...) noexcept>();

    test_is_not_member_pointer<int (&)(int, ...)>();
    test_is_not_member_pointer<int (&)(int, ...) noexcept>();

    test_is_not_member_pointer<void (&&)()>();
    test_is_not_member_pointer<void (&&)() noexcept>();

    test_is_not_member_pointer<void (&&)(int)>();
    test_is_not_member_pointer<void (&&)(int) noexcept>();

    test_is_not_member_pointer<void (&&)(...)>();
    test_is_not_member_pointer<void (&&)(...) noexcept>();

    test_is_not_member_pointer<void (&&)(int, ...)>();
    test_is_not_member_pointer<void (&&)(int, ...) noexcept>();

    test_is_not_member_pointer<int (&&)()>();
    test_is_not_member_pointer<int (&&)() noexcept>();

    test_is_not_member_pointer<int (&&)(int)>();
    test_is_not_member_pointer<int (&&)(int) noexcept>();

    test_is_not_member_pointer<int (&&)(...)>();
    test_is_not_member_pointer<int (&&)(...) noexcept>();

    test_is_not_member_pointer<int (&&)(int, ...)>();
    test_is_not_member_pointer<int (&&)(int, ...) noexcept>();

    test_is_member_pointer<void (class_type::*)()>();
    test_is_member_pointer<void (class_type::*)()&>();
    test_is_member_pointer<void (class_type::*)() &&>();
    test_is_member_pointer<void (class_type::*)() const>();
    test_is_member_pointer<void (class_type::*)() const&>();
    test_is_member_pointer<void (class_type::*)() const&&>();
    test_is_member_pointer<void (class_type::*)() noexcept>();
    test_is_member_pointer<void (class_type::*)() & noexcept>();
    test_is_member_pointer<void (class_type::*)() && noexcept>();
    test_is_member_pointer<void (class_type::*)() const noexcept>();
    test_is_member_pointer<void (class_type::*)() const & noexcept>();
    test_is_member_pointer<void (class_type::*)() const && noexcept>();

    test_is_member_pointer<void (class_type::*)(int)>();
    test_is_member_pointer<void (class_type::*)(int)&>();
    test_is_member_pointer<void (class_type::*)(int) &&>();
    test_is_member_pointer<void (class_type::*)(int) const>();
    test_is_member_pointer<void (class_type::*)(int) const&>();
    test_is_member_pointer<void (class_type::*)(int) const&&>();
    test_is_member_pointer<void (class_type::*)(int) noexcept>();
    test_is_member_pointer<void (class_type::*)(int) & noexcept>();
    test_is_member_pointer<void (class_type::*)(int) && noexcept>();
    test_is_member_pointer<void (class_type::*)(int) const noexcept>();
    test_is_member_pointer<void (class_type::*)(int) const & noexcept>();
    test_is_member_pointer<void (class_type::*)(int) const && noexcept>();

    test_is_member_pointer<void (class_type::*)(...)>();
    test_is_member_pointer<void (class_type::*)(...)&>();
    test_is_member_pointer<void (class_type::*)(...) &&>();
    test_is_member_pointer<void (class_type::*)(...) const>();
    test_is_member_pointer<void (class_type::*)(...) const&>();
    test_is_member_pointer<void (class_type::*)(...) const&&>();
    test_is_member_pointer<void (class_type::*)(...) noexcept>();
    test_is_member_pointer<void (class_type::*)(...) & noexcept>();
    test_is_member_pointer<void (class_type::*)(...) && noexcept>();
    test_is_member_pointer<void (class_type::*)(...) const noexcept>();
    test_is_member_pointer<void (class_type::*)(...) const & noexcept>();
    test_is_member_pointer<void (class_type::*)(...) const && noexcept>();

    test_is_member_pointer<void (class_type::*)(int, ...)>();
    test_is_member_pointer<void (class_type::*)(int, ...)&>();
    test_is_member_pointer<void (class_type::*)(int, ...) &&>();
    test_is_member_pointer<void (class_type::*)(int, ...) const>();
    test_is_member_pointer<void (class_type::*)(int, ...) const&>();
    test_is_member_pointer<void (class_type::*)(int, ...) const&&>();
    test_is_member_pointer<void (class_type::*)(int, ...) noexcept>();
    test_is_member_pointer<void (class_type::*)(int, ...) & noexcept>();
    test_is_member_pointer<void (class_type::*)(int, ...) && noexcept>();
    test_is_member_pointer<void (class_type::*)(int, ...) const noexcept>();
    test_is_member_pointer<void (class_type::*)(int, ...) const & noexcept>();
    test_is_member_pointer<void (class_type::*)(int, ...) const && noexcept>();

    test_is_member_pointer<int (class_type::*)()>();
    test_is_member_pointer<int (class_type::*)()&>();
    test_is_member_pointer<int (class_type::*)() &&>();
    test_is_member_pointer<int (class_type::*)() const>();
    test_is_member_pointer<int (class_type::*)() const&>();
    test_is_member_pointer<int (class_type::*)() const&&>();
    test_is_member_pointer<int (class_type::*)() noexcept>();
    test_is_member_pointer<int (class_type::*)() & noexcept>();
    test_is_member_pointer<int (class_type::*)() && noexcept>();
    test_is_member_pointer<int (class_type::*)() const noexcept>();
    test_is_member_pointer<int (class_type::*)() const & noexcept>();
    test_is_member_pointer<int (class_type::*)() const && noexcept>();

    test_is_member_pointer<int (class_type::*)(int)>();
    test_is_member_pointer<int (class_type::*)(int)&>();
    test_is_member_pointer<int (class_type::*)(int) &&>();
    test_is_member_pointer<int (class_type::*)(int) const>();
    test_is_member_pointer<int (class_type::*)(int) const&>();
    test_is_member_pointer<int (class_type::*)(int) const&&>();
    test_is_member_pointer<int (class_type::*)(int) noexcept>();
    test_is_member_pointer<int (class_type::*)(int) & noexcept>();
    test_is_member_pointer<int (class_type::*)(int) && noexcept>();
    test_is_member_pointer<int (class_type::*)(int) const noexcept>();
    test_is_member_pointer<int (class_type::*)(int) const & noexcept>();
    test_is_member_pointer<int (class_type::*)(int) const && noexcept>();

    test_is_member_pointer<int (class_type::*)(...)>();
    test_is_member_pointer<int (class_type::*)(...)&>();
    test_is_member_pointer<int (class_type::*)(...) &&>();
    test_is_member_pointer<int (class_type::*)(...) const>();
    test_is_member_pointer<int (class_type::*)(...) const&>();
    test_is_member_pointer<int (class_type::*)(...) const&&>();
    test_is_member_pointer<int (class_type::*)(...) noexcept>();
    test_is_member_pointer<int (class_type::*)(...) & noexcept>();
    test_is_member_pointer<int (class_type::*)(...) && noexcept>();
    test_is_member_pointer<int (class_type::*)(...) const noexcept>();
    test_is_member_pointer<int (class_type::*)(...) const & noexcept>();
    test_is_member_pointer<int (class_type::*)(...) const && noexcept>();

    test_is_member_pointer<int (class_type::*)(int, ...)>();
    test_is_member_pointer<int (class_type::*)(int, ...)&>();
    test_is_member_pointer<int (class_type::*)(int, ...) &&>();
    test_is_member_pointer<int (class_type::*)(int, ...) const>();
    test_is_member_pointer<int (class_type::*)(int, ...) const&>();
    test_is_member_pointer<int (class_type::*)(int, ...) const&&>();
    test_is_member_pointer<int (class_type::*)(int, ...) noexcept>();
    test_is_member_pointer<int (class_type::*)(int, ...) & noexcept>();
    test_is_member_pointer<int (class_type::*)(int, ...) && noexcept>();
    test_is_member_pointer<int (class_type::*)(int, ...) const noexcept>();
    test_is_member_pointer<int (class_type::*)(int, ...) const & noexcept>();
    test_is_member_pointer<int (class_type::*)(int, ...) const && noexcept>();
}
