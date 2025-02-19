#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/char8_t.hpp>
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
void test_is_function_impl()
{
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
    STATIC_REQUIRE_FALSE(phi::is_unsafe_floating_point<TypeT>::value);
    STATIC_REQUIRE(phi::is_function<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_fundamental<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_integer<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_integral<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_lvalue_reference<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_member_function_pointer<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_member_object_pointer<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_member_pointer<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_null_pointer<TypeT>::value);
#if PHI_HAS_WORKING_IS_OBJECT()
    STATIC_REQUIRE_FALSE(phi::is_object<TypeT>::value);
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

    STATIC_REQUIRE_FALSE(phi::is_not_function<TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
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
    STATIC_REQUIRE_FALSE(phi::is_unsafe_floating_point_v<TypeT>);
    STATIC_REQUIRE(phi::is_function_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_fundamental_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_integer_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_integral_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_lvalue_reference_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_member_function_pointer_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_member_object_pointer_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_member_pointer_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_null_pointer_v<TypeT>);
#    if PHI_HAS_WORKING_IS_OBJECT()
    STATIC_REQUIRE_FALSE(phi::is_object_v<TypeT>);
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

    STATIC_REQUIRE_FALSE(phi::is_not_function_v<TypeT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_function<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_function<TypeT>);

    // Standard compatibility
    STATIC_REQUIRE(std::is_function<TypeT>::value);
#if PHI_CPP_STANDARD_IS_ATLEAST(17) && PHI_COMPILER_WORKAROUND(GCC, 7, 0, 0)
    STATIC_REQUIRE(std::is_function_v<TypeT>);
#endif
}

template <typename TypeT>
void test_is_function()
{
    test_is_function_impl<TypeT>();
    test_is_function_impl<const TypeT>();
    test_is_function_impl<volatile TypeT>();
    test_is_function_impl<const volatile TypeT>();
}

template <typename TypeT>
void test_is_not_function_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_function<TypeT>::value);
    STATIC_REQUIRE(phi::is_not_function<TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_function_v<TypeT>);
    STATIC_REQUIRE(phi::is_not_function_v<TypeT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_function<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_function<TypeT>);

    // Standard compatibility
    STATIC_REQUIRE_FALSE(std::is_function<TypeT>::value);
#if PHI_CPP_STANDARD_IS_ATLEAST(17) && PHI_COMPILER_WORKAROUND(GCC, 7, 0, 0)
    STATIC_REQUIRE_FALSE(std::is_function_v<TypeT>);
#endif
}

template <typename TypeT>
void test_is_not_function()
{
    test_is_not_function_impl<TypeT>();
    test_is_not_function_impl<const TypeT>();
    test_is_not_function_impl<volatile TypeT>();
    test_is_not_function_impl<const volatile TypeT>();
}

void f()
{}

int g()
{
    return 0;
}

TEST_CASE("is_function")
{
    test_is_function<void(void)>();
    test_is_function<int(int)>();
    test_is_function<int(int, double)>();
    test_is_function<int(int, double, float, char, bool)>();
    test_is_function<int(abstract*)>();
    test_is_function<void(...)>();
    test_is_function<bool(...)>();
    test_is_function<decltype(f)>();
    test_is_function<decltype(g)>();

    test_is_not_function<void>();
    test_is_not_function<phi::nullptr_t>();
    test_is_not_function<bool>();
    test_is_not_function<char>();
    test_is_not_function<signed char>();
    test_is_not_function<unsigned char>();
    test_is_not_function<short>();
    test_is_not_function<unsigned short>();
    test_is_not_function<int>();
    test_is_not_function<unsigned int>();
    test_is_not_function<long>();
    test_is_not_function<unsigned long>();
    test_is_not_function<long long>();
    test_is_not_function<unsigned long long>();
    test_is_not_function<float>();
    test_is_not_function<double>();
    test_is_not_function<long double>();
    test_is_not_function<char8_t>();
    test_is_not_function<char16_t>();
    test_is_not_function<char32_t>();
    test_is_not_function<wchar_t>();

    test_is_not_function<phi::boolean>();
    test_is_not_function<phi::integer<signed char>>();
    test_is_not_function<phi::integer<unsigned char>>();
    test_is_not_function<phi::integer<short>>();
    test_is_not_function<phi::integer<unsigned short>>();
    test_is_not_function<phi::integer<int>>();
    test_is_not_function<phi::integer<unsigned int>>();
    test_is_not_function<phi::integer<long>>();
    test_is_not_function<phi::integer<unsigned long>>();
    test_is_not_function<phi::integer<long long>>();
    test_is_not_function<phi::integer<unsigned long long>>();
    test_is_not_function<phi::floating_point<float>>();
    test_is_not_function<phi::floating_point<double>>();
    test_is_not_function<phi::floating_point<long double>>();

    test_is_not_function<std::vector<int>>();
    test_is_not_function<phi::scope_ptr<int>>();

    test_is_not_function<int&>();
    test_is_not_function<const int&>();
    test_is_not_function<volatile int&>();
    test_is_not_function<const volatile int&>();
    test_is_not_function<int&&>();
    test_is_not_function<const int&&>();
    test_is_not_function<volatile int&&>();
    test_is_not_function<const volatile int&&>();
    test_is_not_function<int*>();
    test_is_not_function<const int*>();
    test_is_not_function<volatile int*>();
    test_is_not_function<const volatile int*>();
    test_is_not_function<int**>();
    test_is_not_function<const int**>();
    test_is_not_function<volatile int**>();
    test_is_not_function<const volatile int**>();
    test_is_not_function<int*&>();
    test_is_not_function<const int*&>();
    test_is_not_function<volatile int*&>();
    test_is_not_function<const volatile int*&>();
    test_is_not_function<int*&&>();
    test_is_not_function<const int*&&>();
    test_is_not_function<volatile int*&&>();
    test_is_not_function<const volatile int*&&>();
    test_is_not_function<void*>();
    test_is_not_function<char[3]>();
    test_is_not_function<char[]>();
    test_is_not_function<char* [3]>();
    test_is_not_function<char*[]>();
    test_is_not_function<int(*)[3]>();
    test_is_not_function<int(*)[]>();
    test_is_not_function<int(&)[3]>();
    test_is_not_function<int(&)[]>();
    test_is_not_function<int(&&)[3]>();
    test_is_not_function<int(&&)[]>();
    test_is_not_function<char[3][2]>();
    test_is_not_function<char[][2]>();
    test_is_not_function<char* [3][2]>();
    test_is_not_function<char*[][2]>();
    test_is_not_function<int(*)[3][2]>();
    test_is_not_function<int(*)[][2]>();
    test_is_not_function<int(&)[3][2]>();
    test_is_not_function<int(&)[][2]>();
    test_is_not_function<int(&&)[3][2]>();
    test_is_not_function<int(&&)[][2]>();
    test_is_not_function<class_type>();
    test_is_not_function<class_type[]>();
    test_is_not_function<class_type[2]>();
    test_is_not_function<template_type<void>>();
    test_is_not_function<template_type<int>>();
    test_is_not_function<template_type<class_type>>();
    test_is_not_function<template_type<incomplete_type>>();
    test_is_not_function<variadic_template<>>();
    test_is_not_function<variadic_template<void>>();
    test_is_not_function<variadic_template<int>>();
    test_is_not_function<variadic_template<class_type>>();
    test_is_not_function<variadic_template<incomplete_type>>();
    test_is_not_function<variadic_template<int, void, class_type, volatile char[]>>();
    test_is_not_function<public_derived_from<base>>();
    test_is_not_function<public_derived_from<derived>>();
    test_is_not_function<public_derived_from<class_type>>();
    test_is_not_function<private_derived_from<base>>();
    test_is_not_function<private_derived_from<derived>>();
    test_is_not_function<private_derived_from<class_type>>();
    test_is_not_function<protected_derived_from<base>>();
    test_is_not_function<protected_derived_from<derived>>();
    test_is_not_function<protected_derived_from<class_type>>();
    test_is_not_function<union_type>();
    test_is_not_function<non_empty_union>();
    test_is_not_function<empty>();
    test_is_not_function<not_empty>();
    test_is_not_function<bit_zero>();
    test_is_not_function<bit_one>();
    test_is_not_function<base>();
    test_is_not_function<derived>();
    test_is_not_function<abstract>();
    test_is_not_function<public_abstract>();
    test_is_not_function<private_abstract>();
    test_is_not_function<protected_abstract>();
    test_is_not_function<abstract_template<int>>();
    test_is_not_function<abstract_template<double>>();
    test_is_not_function<abstract_template<class_type>>();
    test_is_not_function<abstract_template<incomplete_type>>();
    test_is_not_function<final_type>();
    test_is_not_function<public_destructor>();
    test_is_not_function<protected_destructor>();
    test_is_not_function<private_destructor>();
    test_is_not_function<virtual_public_destructor>();
    test_is_not_function<virtual_protected_destructor>();
    test_is_not_function<virtual_private_destructor>();
    test_is_not_function<pure_public_destructor>();
    test_is_not_function<pure_protected_destructor>();
    test_is_not_function<pure_private_destructor>();
    test_is_not_function<deleted_public_destructor>();
    test_is_not_function<deleted_protected_destructor>();
    test_is_not_function<deleted_private_destructor>();
    test_is_not_function<deleted_virtual_public_destructor>();
    test_is_not_function<deleted_virtual_protected_destructor>();
    test_is_not_function<deleted_virtual_private_destructor>();
    test_is_not_function<final_type>();
    test_is_not_function<Enum>();
    test_is_not_function<EnumSigned>();
    test_is_not_function<EnumUnsigned>();
    test_is_not_function<EnumClass>();
    test_is_not_function<EnumStruct>();
    test_is_function<function_type>();
    test_is_not_function<function_ptr>();
    test_is_not_function<member_object_ptr>();
    test_is_not_function<member_function_ptr>();
    test_is_not_function<incomplete_type>();
    test_is_not_function<incomplete_template<void>>();
    test_is_not_function<incomplete_template<int>>();
    test_is_not_function<incomplete_template<class_type>>();
    test_is_not_function<incomplete_template<incomplete_type>>();
    test_is_not_function<incomplete_variadic_template<>>();
    test_is_not_function<incomplete_variadic_template<void>>();
    test_is_not_function<incomplete_variadic_template<int>>();
    test_is_not_function<incomplete_variadic_template<class_type>>();
    test_is_not_function<incomplete_variadic_template<incomplete_type>>();
    test_is_not_function<incomplete_variadic_template<int, void, class_type, volatile char[]>>();
    test_is_not_function<int class_type::*>();
    test_is_not_function<float class_type::*>();
    test_is_not_function<void * class_type::*>();
    test_is_not_function<int * class_type::*>();
    test_is_not_function<int class_type::*&>();
    test_is_not_function<float class_type::*&>();
    test_is_not_function<void * class_type::*&>();
    test_is_not_function<int * class_type::*&>();
    test_is_not_function<int class_type::*&&>();
    test_is_not_function<float class_type::*&&>();
    test_is_not_function<void * class_type::*&&>();
    test_is_not_function<int * class_type::*&&>();
    test_is_not_function<int class_type::* const>();
    test_is_not_function<float class_type::* const>();
    test_is_not_function<void * class_type::* const>();
    test_is_not_function<int class_type::* const&>();
    test_is_not_function<float class_type::* const&>();
    test_is_not_function<void * class_type::* const&>();
    test_is_not_function<int class_type::* const&&>();
    test_is_not_function<float class_type::* const&&>();
    test_is_not_function<void * class_type::* const&&>();
    test_is_not_function<int class_type::* volatile>();
    test_is_not_function<float class_type::* volatile>();
    test_is_not_function<void * class_type::* volatile>();
    test_is_not_function<int class_type::* volatile&>();
    test_is_not_function<float class_type::* volatile&>();
    test_is_not_function<void * class_type::* volatile&>();
    test_is_not_function<int class_type::* volatile&&>();
    test_is_not_function<float class_type::* volatile&&>();
    test_is_not_function<void * class_type::* volatile&&>();
    test_is_not_function<int class_type::* const volatile>();
    test_is_not_function<float class_type::* const volatile>();
    test_is_not_function<void * class_type::* const volatile>();
    test_is_not_function<int class_type::* const volatile&>();
    test_is_not_function<float class_type::* const volatile&>();
    test_is_not_function<void * class_type::* const volatile&>();
    test_is_not_function<int class_type::* const volatile&&>();
    test_is_not_function<float class_type::* const volatile&&>();
    test_is_not_function<void * class_type::* const volatile&&>();
    test_is_not_function<non_copyable>();
    test_is_not_function<non_moveable>();
    test_is_not_function<non_constructible>();
    test_is_not_function<tracked>();
    test_is_not_function<trap_constructible>();
    test_is_not_function<trap_implicit_conversion>();
    test_is_not_function<trap_comma>();
    test_is_not_function<trap_call>();
    test_is_not_function<trap_self_assign>();
    test_is_not_function<trap_deref>();
    test_is_not_function<trap_array_subscript>();

    test_is_function<void()>();
    test_is_function<void()&>();
    test_is_function<void() &&>();
    test_is_function<void() const>();
    test_is_function<void() const&>();
    test_is_function<void() const&&>();
    test_is_function<void() volatile>();
    test_is_function<void() volatile&>();
    test_is_function<void() volatile&&>();
    test_is_function<void() const volatile>();
    test_is_function<void() const volatile&>();
    test_is_function<void() const volatile&&>();
    test_is_function<void() noexcept>();
    test_is_function<void() & noexcept>();
    test_is_function<void() && noexcept>();
    test_is_function<void() const noexcept>();
    test_is_function<void() const & noexcept>();
    test_is_function<void() const && noexcept>();
    test_is_function<void() volatile noexcept>();
    test_is_function<void() volatile & noexcept>();
    test_is_function<void() volatile && noexcept>();
    test_is_function<void() const volatile noexcept>();
    test_is_function<void() const volatile & noexcept>();
    test_is_function<void() const volatile && noexcept>();

    test_is_function<void(int)>();
    test_is_function<void(int)&>();
    test_is_function<void(int) &&>();
    test_is_function<void(int) const>();
    test_is_function<void(int) const&>();
    test_is_function<void(int) const&&>();
    test_is_function<void(int) volatile>();
    test_is_function<void(int) volatile&>();
    test_is_function<void(int) volatile&&>();
    test_is_function<void(int) const volatile>();
    test_is_function<void(int) const volatile&>();
    test_is_function<void(int) const volatile&&>();
    test_is_function<void(int) noexcept>();
    test_is_function<void(int) & noexcept>();
    test_is_function<void(int) && noexcept>();
    test_is_function<void(int) const noexcept>();
    test_is_function<void(int) const & noexcept>();
    test_is_function<void(int) const && noexcept>();
    test_is_function<void(int) volatile noexcept>();
    test_is_function<void(int) volatile & noexcept>();
    test_is_function<void(int) volatile && noexcept>();
    test_is_function<void(int) const volatile noexcept>();
    test_is_function<void(int) const volatile & noexcept>();
    test_is_function<void(int) const volatile && noexcept>();

    test_is_function<void(...)>();
    test_is_function<void(...)&>();
    test_is_function<void(...) &&>();
    test_is_function<void(...) const>();
    test_is_function<void(...) const&>();
    test_is_function<void(...) const&&>();
    test_is_function<void(...) volatile>();
    test_is_function<void(...) volatile&>();
    test_is_function<void(...) volatile&&>();
    test_is_function<void(...) const volatile>();
    test_is_function<void(...) const volatile&>();
    test_is_function<void(...) const volatile&&>();
    test_is_function<void(...) noexcept>();
    test_is_function<void(...) & noexcept>();
    test_is_function<void(...) && noexcept>();
    test_is_function<void(...) const noexcept>();
    test_is_function<void(...) const & noexcept>();
    test_is_function<void(...) const && noexcept>();
    test_is_function<void(...) volatile noexcept>();
    test_is_function<void(...) volatile & noexcept>();
    test_is_function<void(...) volatile && noexcept>();
    test_is_function<void(...) const volatile noexcept>();
    test_is_function<void(...) const volatile & noexcept>();
    test_is_function<void(...) const volatile && noexcept>();

    test_is_function<void(int, ...)>();
    test_is_function<void(int, ...)&>();
    test_is_function<void(int, ...) &&>();
    test_is_function<void(int, ...) const>();
    test_is_function<void(int, ...) const&>();
    test_is_function<void(int, ...) const&&>();
    test_is_function<void(int, ...) volatile>();
    test_is_function<void(int, ...) volatile&>();
    test_is_function<void(int, ...) volatile&&>();
    test_is_function<void(int, ...) const volatile>();
    test_is_function<void(int, ...) const volatile&>();
    test_is_function<void(int, ...) const volatile&&>();
    test_is_function<void(int, ...) noexcept>();
    test_is_function<void(int, ...) & noexcept>();
    test_is_function<void(int, ...) && noexcept>();
    test_is_function<void(int, ...) const noexcept>();
    test_is_function<void(int, ...) const & noexcept>();
    test_is_function<void(int, ...) const && noexcept>();
    test_is_function<void(int, ...) volatile noexcept>();
    test_is_function<void(int, ...) volatile & noexcept>();
    test_is_function<void(int, ...) volatile && noexcept>();
    test_is_function<void(int, ...) const volatile noexcept>();
    test_is_function<void(int, ...) const volatile & noexcept>();
    test_is_function<void(int, ...) const volatile && noexcept>();

    test_is_function<int()>();
    test_is_function<int()&>();
    test_is_function<int() &&>();
    test_is_function<int() const>();
    test_is_function<int() const&>();
    test_is_function<int() const&&>();
    test_is_function<int() volatile>();
    test_is_function<int() volatile&>();
    test_is_function<int() volatile&&>();
    test_is_function<int() const volatile>();
    test_is_function<int() const volatile&>();
    test_is_function<int() const volatile&&>();
    test_is_function<int() noexcept>();
    test_is_function<int() & noexcept>();
    test_is_function<int() && noexcept>();
    test_is_function<int() const noexcept>();
    test_is_function<int() const & noexcept>();
    test_is_function<int() const && noexcept>();
    test_is_function<int() volatile noexcept>();
    test_is_function<int() volatile & noexcept>();
    test_is_function<int() volatile && noexcept>();
    test_is_function<int() const volatile noexcept>();
    test_is_function<int() const volatile & noexcept>();
    test_is_function<int() const volatile && noexcept>();

    test_is_function<int(int)>();
    test_is_function<int(int)&>();
    test_is_function<int(int) &&>();
    test_is_function<int(int) const>();
    test_is_function<int(int) const&>();
    test_is_function<int(int) const&&>();
    test_is_function<int(int) volatile>();
    test_is_function<int(int) volatile&>();
    test_is_function<int(int) volatile&&>();
    test_is_function<int(int) const volatile>();
    test_is_function<int(int) const volatile&>();
    test_is_function<int(int) const volatile&&>();
    test_is_function<int(int) noexcept>();
    test_is_function<int(int) & noexcept>();
    test_is_function<int(int) && noexcept>();
    test_is_function<int(int) const noexcept>();
    test_is_function<int(int) const & noexcept>();
    test_is_function<int(int) const && noexcept>();
    test_is_function<int(int) volatile noexcept>();
    test_is_function<int(int) volatile & noexcept>();
    test_is_function<int(int) volatile && noexcept>();
    test_is_function<int(int) const volatile noexcept>();
    test_is_function<int(int) const volatile & noexcept>();
    test_is_function<int(int) const volatile && noexcept>();

    test_is_function<int(...)>();
    test_is_function<int(...)&>();
    test_is_function<int(...) &&>();
    test_is_function<int(...) const>();
    test_is_function<int(...) const&>();
    test_is_function<int(...) const&&>();
    test_is_function<int(...) volatile>();
    test_is_function<int(...) volatile&>();
    test_is_function<int(...) volatile&&>();
    test_is_function<int(...) const volatile>();
    test_is_function<int(...) const volatile&>();
    test_is_function<int(...) const volatile&&>();
    test_is_function<int(...) noexcept>();
    test_is_function<int(...) & noexcept>();
    test_is_function<int(...) && noexcept>();
    test_is_function<int(...) const noexcept>();
    test_is_function<int(...) const & noexcept>();
    test_is_function<int(...) const && noexcept>();
    test_is_function<int(...) volatile noexcept>();
    test_is_function<int(...) volatile & noexcept>();
    test_is_function<int(...) volatile && noexcept>();
    test_is_function<int(...) const volatile noexcept>();
    test_is_function<int(...) const volatile & noexcept>();
    test_is_function<int(...) const volatile && noexcept>();

    test_is_function<int(int, ...)>();
    test_is_function<int(int, ...)&>();
    test_is_function<int(int, ...) &&>();
    test_is_function<int(int, ...) const>();
    test_is_function<int(int, ...) const&>();
    test_is_function<int(int, ...) const&&>();
    test_is_function<int(int, ...) volatile>();
    test_is_function<int(int, ...) volatile&>();
    test_is_function<int(int, ...) volatile&&>();
    test_is_function<int(int, ...) const volatile>();
    test_is_function<int(int, ...) const volatile&>();
    test_is_function<int(int, ...) const volatile&&>();
    test_is_function<int(int, ...) noexcept>();
    test_is_function<int(int, ...) & noexcept>();
    test_is_function<int(int, ...) && noexcept>();
    test_is_function<int(int, ...) const noexcept>();
    test_is_function<int(int, ...) const & noexcept>();
    test_is_function<int(int, ...) const && noexcept>();
    test_is_function<int(int, ...) volatile noexcept>();
    test_is_function<int(int, ...) volatile & noexcept>();
    test_is_function<int(int, ...) volatile && noexcept>();
    test_is_function<int(int, ...) const volatile noexcept>();
    test_is_function<int(int, ...) const volatile & noexcept>();
    test_is_function<int(int, ...) const volatile && noexcept>();

    test_is_not_function<void (*)()>();
    test_is_not_function<void (*)() noexcept>();

    test_is_not_function<void (*)(int)>();
    test_is_not_function<void (*)(int) noexcept>();

    test_is_not_function<void (*)(...)>();
    test_is_not_function<void (*)(...) noexcept>();

    test_is_not_function<void (*)(int, ...)>();
    test_is_not_function<void (*)(int, ...) noexcept>();

    test_is_not_function<int (*)()>();
    test_is_not_function<int (*)() noexcept>();

    test_is_not_function<int (*)(int)>();
    test_is_not_function<int (*)(int) noexcept>();

    test_is_not_function<int (*)(...)>();
    test_is_not_function<int (*)(...) noexcept>();

    test_is_not_function<int (*)(int, ...)>();
    test_is_not_function<int (*)(int, ...) noexcept>();

    test_is_not_function<void (&)()>();
    test_is_not_function<void (&)() noexcept>();

    test_is_not_function<void (&)(int)>();
    test_is_not_function<void (&)(int) noexcept>();

    test_is_not_function<void (&)(...)>();
    test_is_not_function<void (&)(...) noexcept>();

    test_is_not_function<void (&)(int, ...)>();
    test_is_not_function<void (&)(int, ...) noexcept>();

    test_is_not_function<int (&)()>();
    test_is_not_function<int (&)() noexcept>();

    test_is_not_function<int (&)(int)>();
    test_is_not_function<int (&)(int) noexcept>();

    test_is_not_function<int (&)(...)>();
    test_is_not_function<int (&)(...) noexcept>();

    test_is_not_function<int (&)(int, ...)>();
    test_is_not_function<int (&)(int, ...) noexcept>();

    test_is_not_function<void (&&)()>();
    test_is_not_function<void (&&)() noexcept>();

    test_is_not_function<void (&&)(int)>();
    test_is_not_function<void (&&)(int) noexcept>();

    test_is_not_function<void (&&)(...)>();
    test_is_not_function<void (&&)(...) noexcept>();

    test_is_not_function<void (&&)(int, ...)>();
    test_is_not_function<void (&&)(int, ...) noexcept>();

    test_is_not_function<int (&&)()>();
    test_is_not_function<int (&&)() noexcept>();

    test_is_not_function<int (&&)(int)>();
    test_is_not_function<int (&&)(int) noexcept>();

    test_is_not_function<int (&&)(...)>();
    test_is_not_function<int (&&)(...) noexcept>();

    test_is_not_function<int (&&)(int, ...)>();
    test_is_not_function<int (&&)(int, ...) noexcept>();

    test_is_not_function<void (class_type::*)()>();
    test_is_not_function<void (class_type::*)()&>();
    test_is_not_function<void (class_type::*)() &&>();
    test_is_not_function<void (class_type::*)() const>();
    test_is_not_function<void (class_type::*)() const&>();
    test_is_not_function<void (class_type::*)() const&&>();
    test_is_not_function<void (class_type::*)() noexcept>();
    test_is_not_function<void (class_type::*)() & noexcept>();
    test_is_not_function<void (class_type::*)() && noexcept>();
    test_is_not_function<void (class_type::*)() const noexcept>();
    test_is_not_function<void (class_type::*)() const & noexcept>();
    test_is_not_function<void (class_type::*)() const && noexcept>();

    test_is_not_function<void (class_type::*)(int)>();
    test_is_not_function<void (class_type::*)(int)&>();
    test_is_not_function<void (class_type::*)(int) &&>();
    test_is_not_function<void (class_type::*)(int) const>();
    test_is_not_function<void (class_type::*)(int) const&>();
    test_is_not_function<void (class_type::*)(int) const&&>();
    test_is_not_function<void (class_type::*)(int) noexcept>();
    test_is_not_function<void (class_type::*)(int) & noexcept>();
    test_is_not_function<void (class_type::*)(int) && noexcept>();
    test_is_not_function<void (class_type::*)(int) const noexcept>();
    test_is_not_function<void (class_type::*)(int) const & noexcept>();
    test_is_not_function<void (class_type::*)(int) const && noexcept>();

    test_is_not_function<void (class_type::*)(...)>();
    test_is_not_function<void (class_type::*)(...)&>();
    test_is_not_function<void (class_type::*)(...) &&>();
    test_is_not_function<void (class_type::*)(...) const>();
    test_is_not_function<void (class_type::*)(...) const&>();
    test_is_not_function<void (class_type::*)(...) const&&>();
    test_is_not_function<void (class_type::*)(...) noexcept>();
    test_is_not_function<void (class_type::*)(...) & noexcept>();
    test_is_not_function<void (class_type::*)(...) && noexcept>();
    test_is_not_function<void (class_type::*)(...) const noexcept>();
    test_is_not_function<void (class_type::*)(...) const & noexcept>();
    test_is_not_function<void (class_type::*)(...) const && noexcept>();

    test_is_not_function<void (class_type::*)(int, ...)>();
    test_is_not_function<void (class_type::*)(int, ...)&>();
    test_is_not_function<void (class_type::*)(int, ...) &&>();
    test_is_not_function<void (class_type::*)(int, ...) const>();
    test_is_not_function<void (class_type::*)(int, ...) const&>();
    test_is_not_function<void (class_type::*)(int, ...) const&&>();
    test_is_not_function<void (class_type::*)(int, ...) noexcept>();
    test_is_not_function<void (class_type::*)(int, ...) & noexcept>();
    test_is_not_function<void (class_type::*)(int, ...) && noexcept>();
    test_is_not_function<void (class_type::*)(int, ...) const noexcept>();
    test_is_not_function<void (class_type::*)(int, ...) const & noexcept>();
    test_is_not_function<void (class_type::*)(int, ...) const && noexcept>();

    test_is_not_function<int (class_type::*)()>();
    test_is_not_function<int (class_type::*)()&>();
    test_is_not_function<int (class_type::*)() &&>();
    test_is_not_function<int (class_type::*)() const>();
    test_is_not_function<int (class_type::*)() const&>();
    test_is_not_function<int (class_type::*)() const&&>();
    test_is_not_function<int (class_type::*)() noexcept>();
    test_is_not_function<int (class_type::*)() & noexcept>();
    test_is_not_function<int (class_type::*)() && noexcept>();
    test_is_not_function<int (class_type::*)() const noexcept>();
    test_is_not_function<int (class_type::*)() const & noexcept>();
    test_is_not_function<int (class_type::*)() const && noexcept>();

    test_is_not_function<int (class_type::*)(int)>();
    test_is_not_function<int (class_type::*)(int)&>();
    test_is_not_function<int (class_type::*)(int) &&>();
    test_is_not_function<int (class_type::*)(int) const>();
    test_is_not_function<int (class_type::*)(int) const&>();
    test_is_not_function<int (class_type::*)(int) const&&>();
    test_is_not_function<int (class_type::*)(int) noexcept>();
    test_is_not_function<int (class_type::*)(int) & noexcept>();
    test_is_not_function<int (class_type::*)(int) && noexcept>();
    test_is_not_function<int (class_type::*)(int) const noexcept>();
    test_is_not_function<int (class_type::*)(int) const & noexcept>();
    test_is_not_function<int (class_type::*)(int) const && noexcept>();

    test_is_not_function<int (class_type::*)(...)>();
    test_is_not_function<int (class_type::*)(...)&>();
    test_is_not_function<int (class_type::*)(...) &&>();
    test_is_not_function<int (class_type::*)(...) const>();
    test_is_not_function<int (class_type::*)(...) const&>();
    test_is_not_function<int (class_type::*)(...) const&&>();
    test_is_not_function<int (class_type::*)(...) noexcept>();
    test_is_not_function<int (class_type::*)(...) & noexcept>();
    test_is_not_function<int (class_type::*)(...) && noexcept>();
    test_is_not_function<int (class_type::*)(...) const noexcept>();
    test_is_not_function<int (class_type::*)(...) const & noexcept>();
    test_is_not_function<int (class_type::*)(...) const && noexcept>();

    test_is_not_function<int (class_type::*)(int, ...)>();
    test_is_not_function<int (class_type::*)(int, ...)&>();
    test_is_not_function<int (class_type::*)(int, ...) &&>();
    test_is_not_function<int (class_type::*)(int, ...) const>();
    test_is_not_function<int (class_type::*)(int, ...) const&>();
    test_is_not_function<int (class_type::*)(int, ...) const&&>();
    test_is_not_function<int (class_type::*)(int, ...) noexcept>();
    test_is_not_function<int (class_type::*)(int, ...) & noexcept>();
    test_is_not_function<int (class_type::*)(int, ...) && noexcept>();
    test_is_not_function<int (class_type::*)(int, ...) const noexcept>();
    test_is_not_function<int (class_type::*)(int, ...) const & noexcept>();
    test_is_not_function<int (class_type::*)(int, ...) const && noexcept>();

    // Needed for maximum coverage
    f();
    (void)g();
}
