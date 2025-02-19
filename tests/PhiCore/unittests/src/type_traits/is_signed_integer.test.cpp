#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_integer.hpp>
#include <phi/type_traits/is_signed.hpp>
#include <phi/type_traits/is_signed_integer.hpp>
#include <vector>

template <typename TypeT>
void test_is_signed_integer_impl()
{
    STATIC_REQUIRE(phi::is_signed_integer<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_signed_integer<TypeT>::value);
    STATIC_REQUIRE(phi::is_integer<TypeT>::value && phi::is_signed<TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_signed_integer_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_not_signed_integer_v<TypeT>);
    STATIC_REQUIRE(phi::is_integer_v<TypeT> && phi::is_signed_v<TypeT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_signed_integer<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_signed_integer<TypeT>);
}

template <typename TypeT>
void test_is_not_signed_integer_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_signed_integer<TypeT>::value);
    STATIC_REQUIRE(phi::is_not_signed_integer<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_integer<TypeT>::value && phi::is_signed<TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_signed_integer_v<TypeT>);
    STATIC_REQUIRE(phi::is_not_signed_integer_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_integer_v<TypeT> && phi::is_signed_v<TypeT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_signed_integer<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_signed_integer<TypeT>);
}

template <typename TypeT>
void test_is_signed_integer()
{
    test_is_signed_integer_impl<TypeT>();
    test_is_signed_integer_impl<const TypeT>();
    test_is_signed_integer_impl<volatile TypeT>();
    test_is_signed_integer_impl<const volatile TypeT>();
}

template <typename TypeT>
void test_is_not_signed_integer()
{
    test_is_not_signed_integer_impl<TypeT>();
    test_is_not_signed_integer_impl<const TypeT>();
    test_is_not_signed_integer_impl<volatile TypeT>();
    test_is_not_signed_integer_impl<const volatile TypeT>();
}

TEST_CASE("is_signed_integer")
{
    test_is_not_signed_integer<void>();
    test_is_not_signed_integer<phi::nullptr_t>();
    test_is_not_signed_integer<bool>();
    //test_is_not_signed_integer<char>();
    test_is_signed_integer<signed char>();
    test_is_not_signed_integer<unsigned char>();
    test_is_signed_integer<short>();
    test_is_not_signed_integer<unsigned short>();
    test_is_signed_integer<int>();
    test_is_not_signed_integer<unsigned int>();
    test_is_signed_integer<long>();
    test_is_not_signed_integer<unsigned long>();
    test_is_signed_integer<long long>();
    test_is_not_signed_integer<unsigned long long>();
    test_is_not_signed_integer<float>();
    test_is_not_signed_integer<double>();
    test_is_not_signed_integer<long double>();
#if PHI_HAS_FEATURE_CHAR8_T()
    test_is_not_signed_integer<char8_t>();
#endif
    test_is_not_signed_integer<char16_t>();
    test_is_not_signed_integer<char32_t>();
    test_is_not_signed_integer<wchar_t>();

    test_is_not_signed_integer<phi::boolean>();
    test_is_signed_integer<phi::integer<signed char>>();
    test_is_not_signed_integer<phi::integer<unsigned char>>();
    test_is_signed_integer<phi::integer<short>>();
    test_is_not_signed_integer<phi::integer<unsigned short>>();
    test_is_signed_integer<phi::integer<int>>();
    test_is_not_signed_integer<phi::integer<unsigned int>>();
    test_is_signed_integer<phi::integer<long>>();
    test_is_not_signed_integer<phi::integer<unsigned long>>();
    test_is_signed_integer<phi::integer<long long>>();
    test_is_not_signed_integer<phi::integer<unsigned long long>>();
    test_is_not_signed_integer<phi::floating_point<float>>();
    test_is_not_signed_integer<phi::floating_point<double>>();
    test_is_not_signed_integer<phi::floating_point<long double>>();

    test_is_not_signed_integer<std::vector<int>>();
    test_is_not_signed_integer<phi::scope_ptr<int>>();

    test_is_not_signed_integer<int&>();
    test_is_not_signed_integer<const int&>();
    test_is_not_signed_integer<volatile int&>();
    test_is_not_signed_integer<const volatile int&>();
    test_is_not_signed_integer<int&&>();
    test_is_not_signed_integer<const int&&>();
    test_is_not_signed_integer<volatile int&&>();
    test_is_not_signed_integer<const volatile int&&>();
    test_is_not_signed_integer<int*>();
    test_is_not_signed_integer<const int*>();
    test_is_not_signed_integer<volatile int*>();
    test_is_not_signed_integer<const volatile int*>();
    test_is_not_signed_integer<int**>();
    test_is_not_signed_integer<const int**>();
    test_is_not_signed_integer<volatile int**>();
    test_is_not_signed_integer<const volatile int**>();
    test_is_not_signed_integer<int*&>();
    test_is_not_signed_integer<const int*&>();
    test_is_not_signed_integer<volatile int*&>();
    test_is_not_signed_integer<const volatile int*&>();
    test_is_not_signed_integer<int*&&>();
    test_is_not_signed_integer<const int*&&>();
    test_is_not_signed_integer<volatile int*&&>();
    test_is_not_signed_integer<const volatile int*&&>();
    test_is_not_signed_integer<void*>();
    test_is_not_signed_integer<char[3]>();
    test_is_not_signed_integer<char[]>();
    test_is_not_signed_integer<char* [3]>();
    test_is_not_signed_integer<char*[]>();
    test_is_not_signed_integer<int(*)[3]>();
    test_is_not_signed_integer<int(*)[]>();
    test_is_not_signed_integer<int(&)[3]>();
    test_is_not_signed_integer<int(&)[]>();
    test_is_not_signed_integer<int(&&)[3]>();
    test_is_not_signed_integer<int(&&)[]>();
    test_is_not_signed_integer<char[3][2]>();
    test_is_not_signed_integer<char[][2]>();
    test_is_not_signed_integer<char* [3][2]>();
    test_is_not_signed_integer<char*[][2]>();
    test_is_not_signed_integer<int(*)[3][2]>();
    test_is_not_signed_integer<int(*)[][2]>();
    test_is_not_signed_integer<int(&)[3][2]>();
    test_is_not_signed_integer<int(&)[][2]>();
    test_is_not_signed_integer<int(&&)[3][2]>();
    test_is_not_signed_integer<int(&&)[][2]>();
    test_is_not_signed_integer<class_type>();
    test_is_not_signed_integer<class_type[]>();
    test_is_not_signed_integer<class_type[2]>();
    test_is_not_signed_integer<template_type<void>>();
    test_is_not_signed_integer<template_type<int>>();
    test_is_not_signed_integer<template_type<class_type>>();
    test_is_not_signed_integer<template_type<incomplete_type>>();
    test_is_not_signed_integer<variadic_template<>>();
    test_is_not_signed_integer<variadic_template<void>>();
    test_is_not_signed_integer<variadic_template<int>>();
    test_is_not_signed_integer<variadic_template<class_type>>();
    test_is_not_signed_integer<variadic_template<incomplete_type>>();
    test_is_not_signed_integer<variadic_template<int, void, class_type, volatile char[]>>();
    test_is_not_signed_integer<public_derived_from<base>>();
    test_is_not_signed_integer<public_derived_from<derived>>();
    test_is_not_signed_integer<public_derived_from<class_type>>();
    test_is_not_signed_integer<private_derived_from<base>>();
    test_is_not_signed_integer<private_derived_from<derived>>();
    test_is_not_signed_integer<private_derived_from<class_type>>();
    test_is_not_signed_integer<protected_derived_from<base>>();
    test_is_not_signed_integer<protected_derived_from<derived>>();
    test_is_not_signed_integer<protected_derived_from<class_type>>();
    test_is_not_signed_integer<virtual_derived_from<base>>();
    test_is_not_signed_integer<virtual_derived_from<derived>>();
    test_is_not_signed_integer<virtual_derived_from<class_type>>();
    test_is_not_signed_integer<union_type>();
    test_is_not_signed_integer<non_empty_union>();
    test_is_not_signed_integer<non_trivial_union>();
    test_is_not_signed_integer<empty>();
    test_is_not_signed_integer<not_empty>();
    test_is_not_signed_integer<non_trivial>();
    test_is_not_signed_integer<bit_zero>();
    test_is_not_signed_integer<bit_one>();
    test_is_not_signed_integer<base>();
    test_is_not_signed_integer<derived>();
    test_is_not_signed_integer<polymorphic>();
    test_is_not_signed_integer<derived_polymorphic>();
    test_is_not_signed_integer<abstract>();
    test_is_not_signed_integer<public_abstract>();
    test_is_not_signed_integer<private_abstract>();
    test_is_not_signed_integer<protected_abstract>();
    test_is_not_signed_integer<abstract_template<int>>();
    test_is_not_signed_integer<abstract_template<double>>();
    test_is_not_signed_integer<abstract_template<class_type>>();
    test_is_not_signed_integer<abstract_template<incomplete_type>>();
    test_is_not_signed_integer<public_abstract_deleted_destructor>();
    test_is_not_signed_integer<protected_abstract_deleted_destructor>();
    test_is_not_signed_integer<private_abstract_deleted_destructor>();
    test_is_not_signed_integer<final_type>();
    test_is_not_signed_integer<final_derived>();
    test_is_not_signed_integer<public_destructor>();
    test_is_not_signed_integer<protected_destructor>();
    test_is_not_signed_integer<private_destructor>();
    test_is_not_signed_integer<virtual_public_destructor>();
    test_is_not_signed_integer<virtual_protected_destructor>();
    test_is_not_signed_integer<virtual_private_destructor>();
    test_is_not_signed_integer<pure_public_destructor>();
    test_is_not_signed_integer<pure_protected_destructor>();
    test_is_not_signed_integer<pure_private_destructor>();
    test_is_not_signed_integer<deleted_public_destructor>();
    test_is_not_signed_integer<deleted_protected_destructor>();
    test_is_not_signed_integer<deleted_private_destructor>();
    test_is_not_signed_integer<deleted_virtual_public_destructor>();
    test_is_not_signed_integer<deleted_virtual_protected_destructor>();
    test_is_not_signed_integer<deleted_virtual_private_destructor>();
    test_is_not_signed_integer<explicit_class>();
    test_is_not_signed_integer<nothrow_explicit_class>();
    test_is_not_signed_integer<throw_explicit_class>();
    test_is_not_signed_integer<throw_default_class>();
    test_is_not_signed_integer<throw_copy_constructible_class>();
    test_is_not_signed_integer<throw_move_constructible_class>();
    test_is_not_signed_integer<noexcept_explicit_class>();
    test_is_not_signed_integer<except_explicit_class>();
    test_is_not_signed_integer<noexcept_default_class>();
    test_is_not_signed_integer<except_default_class>();
    test_is_not_signed_integer<noexcept_copy_constructible_class>();
    test_is_not_signed_integer<except_copy_constructible_class>();
    test_is_not_signed_integer<noexcept_move_constructible_class>();
    test_is_not_signed_integer<except_move_constructible_class>();
    test_is_not_signed_integer<noexcept_copy_assign_class>();
    test_is_not_signed_integer<except_copy_assign_class>();
    test_is_not_signed_integer<noexcept_move_assign_class>();
    test_is_not_signed_integer<except_move_assign_class>();
    test_is_not_signed_integer<deleted_copy_assign_class>();
    test_is_not_signed_integer<deleted_move_assign_class>();
    test_is_not_signed_integer<noexcept_move_constructible_and_assignable_class>();
    test_is_not_signed_integer<except_move_constructible_noexcept_move_assign_class>();
    test_is_not_signed_integer<noexcept_move_constructible_except_move_assign_class>();
    test_is_not_signed_integer<except_move_constructible_and_assign_class>();
    test_is_not_signed_integer<implicit_to<int>>();
    test_is_not_signed_integer<implicit_to<float>>();
    test_is_not_signed_integer<implicit_to<class_type>>();
    test_is_not_signed_integer<deleted_implicit_to<int>>();
    test_is_not_signed_integer<deleted_implicit_to<float>>();
    test_is_not_signed_integer<deleted_implicit_to<class_type>>();
    test_is_not_signed_integer<explicit_to<int>>();
    test_is_not_signed_integer<explicit_to<float>>();
    test_is_not_signed_integer<explicit_to<class_type>>();
    test_is_not_signed_integer<deleted_explicit_to<int>>();
    test_is_not_signed_integer<deleted_explicit_to<float>>();
    test_is_not_signed_integer<deleted_explicit_to<class_type>>();
    test_is_not_signed_integer<ellipsis>();
    test_is_not_signed_integer<deleted_ellipsis>();
    test_is_not_signed_integer<copy_constructible_only_type>();
    test_is_not_signed_integer<move_constructible_only_type>();
    test_is_not_signed_integer<overloaded_operators>();
    test_is_not_signed_integer<public_int_member>();
    test_is_not_signed_integer<protected_int_member>();
    test_is_not_signed_integer<private_int_member>();
    test_is_not_signed_integer<public_static_int_member>();
    test_is_not_signed_integer<protected_static_int_member>();
    test_is_not_signed_integer<private_static_int_member>();
    test_is_not_signed_integer<public_template_member<int>>();
    test_is_not_signed_integer<public_template_member<float>>();
    test_is_not_signed_integer<public_template_member<class_type>>();
    test_is_not_signed_integer<protected_template_member<int>>();
    test_is_not_signed_integer<protected_template_member<float>>();
    test_is_not_signed_integer<protected_template_member<class_type>>();
    test_is_not_signed_integer<private_template_member<int>>();
    test_is_not_signed_integer<private_template_member<float>>();
    test_is_not_signed_integer<private_template_member<class_type>>();
    test_is_not_signed_integer<public_static_template_member<int>>();
    test_is_not_signed_integer<public_static_template_member<float>>();
    test_is_not_signed_integer<public_static_template_member<class_type>>();
    test_is_not_signed_integer<protected_static_template_member<int>>();
    test_is_not_signed_integer<protected_static_template_member<float>>();
    test_is_not_signed_integer<protected_static_template_member<class_type>>();
    test_is_not_signed_integer<private_static_template_member<int>>();
    test_is_not_signed_integer<private_static_template_member<float>>();
    test_is_not_signed_integer<private_static_template_member<class_type>>();
    test_is_not_signed_integer<Enum>();
    test_is_not_signed_integer<EnumSigned>();
    test_is_not_signed_integer<EnumUnsigned>();
    test_is_not_signed_integer<EnumClass>();
    test_is_not_signed_integer<EnumStruct>();
    test_is_not_signed_integer<function_type>();
    test_is_not_signed_integer<function_ptr>();
    test_is_not_signed_integer<member_object_ptr>();
    test_is_not_signed_integer<member_function_ptr>();
    test_is_not_signed_integer<lambda_type>();
    test_is_not_signed_integer<lambda_noexcept_type>();
    test_is_not_signed_integer<lambda_throws_type>();
    test_is_not_signed_integer<incomplete_type>();
    test_is_not_signed_integer<incomplete_template<void>>();
    test_is_not_signed_integer<incomplete_template<int>>();
    test_is_not_signed_integer<incomplete_template<class_type>>();
    test_is_not_signed_integer<incomplete_template<incomplete_type>>();
    test_is_not_signed_integer<incomplete_variadic_template<>>();
    test_is_not_signed_integer<incomplete_variadic_template<void>>();
    test_is_not_signed_integer<incomplete_variadic_template<int>>();
    test_is_not_signed_integer<incomplete_variadic_template<class_type>>();
    test_is_not_signed_integer<incomplete_variadic_template<incomplete_type>>();
    test_is_not_signed_integer<
            incomplete_variadic_template<int, void, class_type, volatile char[]>>();
    test_is_not_signed_integer<incomplete_union>();
    test_is_not_signed_integer<IncompleteEnumSigned>();
    test_is_not_signed_integer<IncompleteEnumUnsigned>();
    test_is_not_signed_integer<IncompleteEnumClass>();
    test_is_not_signed_integer<IncompleteEnumStruct>();
    test_is_not_signed_integer<int class_type::*>();
    test_is_not_signed_integer<float class_type::*>();
    test_is_not_signed_integer<void * class_type::*>();
    test_is_not_signed_integer<int * class_type::*>();
    test_is_not_signed_integer<int class_type::*&>();
    test_is_not_signed_integer<float class_type::*&>();
    test_is_not_signed_integer<void * class_type::*&>();
    test_is_not_signed_integer<int * class_type::*&>();
    test_is_not_signed_integer<int class_type::*&&>();
    test_is_not_signed_integer<float class_type::*&&>();
    test_is_not_signed_integer<void * class_type::*&&>();
    test_is_not_signed_integer<int * class_type::*&&>();
    test_is_not_signed_integer<int class_type::* const>();
    test_is_not_signed_integer<float class_type::* const>();
    test_is_not_signed_integer<void * class_type::* const>();
    test_is_not_signed_integer<int class_type::* const&>();
    test_is_not_signed_integer<float class_type::* const&>();
    test_is_not_signed_integer<void * class_type::* const&>();
    test_is_not_signed_integer<int class_type::* const&&>();
    test_is_not_signed_integer<float class_type::* const&&>();
    test_is_not_signed_integer<void * class_type::* const&&>();
    test_is_not_signed_integer<int class_type::* volatile>();
    test_is_not_signed_integer<float class_type::* volatile>();
    test_is_not_signed_integer<void * class_type::* volatile>();
    test_is_not_signed_integer<int class_type::* volatile&>();
    test_is_not_signed_integer<float class_type::* volatile&>();
    test_is_not_signed_integer<void * class_type::* volatile&>();
    test_is_not_signed_integer<int class_type::* volatile&&>();
    test_is_not_signed_integer<float class_type::* volatile&&>();
    test_is_not_signed_integer<void * class_type::* volatile&&>();
    test_is_not_signed_integer<int class_type::* const volatile>();
    test_is_not_signed_integer<float class_type::* const volatile>();
    test_is_not_signed_integer<void * class_type::* const volatile>();
    test_is_not_signed_integer<int class_type::* const volatile&>();
    test_is_not_signed_integer<float class_type::* const volatile&>();
    test_is_not_signed_integer<void * class_type::* const volatile&>();
    test_is_not_signed_integer<int class_type::* const volatile&&>();
    test_is_not_signed_integer<float class_type::* const volatile&&>();
    test_is_not_signed_integer<void * class_type::* const volatile&&>();
    test_is_not_signed_integer<non_copyable>();
    test_is_not_signed_integer<non_moveable>();
    test_is_not_signed_integer<non_constructible>();
    test_is_not_signed_integer<non_destructible>();
    test_is_not_signed_integer<tracked>();
    test_is_not_signed_integer<trap_constructible>();
    test_is_not_signed_integer<trap_implicit_conversion>();
    test_is_not_signed_integer<trap_comma>();
    test_is_not_signed_integer<trap_call>();
    test_is_not_signed_integer<trap_self_assign>();
    test_is_not_signed_integer<trap_deref>();
    test_is_not_signed_integer<trap_array_subscript>();

    test_is_not_signed_integer<void()>();
    test_is_not_signed_integer<void()&>();
    test_is_not_signed_integer<void() &&>();
    test_is_not_signed_integer<void() const>();
    test_is_not_signed_integer<void() const&>();
    test_is_not_signed_integer<void() const&&>();
    test_is_not_signed_integer<void() volatile>();
    test_is_not_signed_integer<void() volatile&>();
    test_is_not_signed_integer<void() volatile&&>();
    test_is_not_signed_integer<void() const volatile>();
    test_is_not_signed_integer<void() const volatile&>();
    test_is_not_signed_integer<void() const volatile&&>();
    test_is_not_signed_integer<void() noexcept>();
    test_is_not_signed_integer<void() & noexcept>();
    test_is_not_signed_integer<void() && noexcept>();
    test_is_not_signed_integer<void() const noexcept>();
    test_is_not_signed_integer<void() const & noexcept>();
    test_is_not_signed_integer<void() const && noexcept>();
    test_is_not_signed_integer<void() volatile noexcept>();
    test_is_not_signed_integer<void() volatile & noexcept>();
    test_is_not_signed_integer<void() volatile && noexcept>();
    test_is_not_signed_integer<void() const volatile noexcept>();
    test_is_not_signed_integer<void() const volatile & noexcept>();
    test_is_not_signed_integer<void() const volatile && noexcept>();

    test_is_not_signed_integer<void(int)>();
    test_is_not_signed_integer<void(int)&>();
    test_is_not_signed_integer<void(int) &&>();
    test_is_not_signed_integer<void(int) const>();
    test_is_not_signed_integer<void(int) const&>();
    test_is_not_signed_integer<void(int) const&&>();
    test_is_not_signed_integer<void(int) volatile>();
    test_is_not_signed_integer<void(int) volatile&>();
    test_is_not_signed_integer<void(int) volatile&&>();
    test_is_not_signed_integer<void(int) const volatile>();
    test_is_not_signed_integer<void(int) const volatile&>();
    test_is_not_signed_integer<void(int) const volatile&&>();
    test_is_not_signed_integer<void(int) noexcept>();
    test_is_not_signed_integer<void(int) & noexcept>();
    test_is_not_signed_integer<void(int) && noexcept>();
    test_is_not_signed_integer<void(int) const noexcept>();
    test_is_not_signed_integer<void(int) const & noexcept>();
    test_is_not_signed_integer<void(int) const && noexcept>();
    test_is_not_signed_integer<void(int) volatile noexcept>();
    test_is_not_signed_integer<void(int) volatile & noexcept>();
    test_is_not_signed_integer<void(int) volatile && noexcept>();
    test_is_not_signed_integer<void(int) const volatile noexcept>();
    test_is_not_signed_integer<void(int) const volatile & noexcept>();
    test_is_not_signed_integer<void(int) const volatile && noexcept>();

    test_is_not_signed_integer<void(...)>();
    test_is_not_signed_integer<void(...)&>();
    test_is_not_signed_integer<void(...) &&>();
    test_is_not_signed_integer<void(...) const>();
    test_is_not_signed_integer<void(...) const&>();
    test_is_not_signed_integer<void(...) const&&>();
    test_is_not_signed_integer<void(...) volatile>();
    test_is_not_signed_integer<void(...) volatile&>();
    test_is_not_signed_integer<void(...) volatile&&>();
    test_is_not_signed_integer<void(...) const volatile>();
    test_is_not_signed_integer<void(...) const volatile&>();
    test_is_not_signed_integer<void(...) const volatile&&>();
    test_is_not_signed_integer<void(...) noexcept>();
    test_is_not_signed_integer<void(...) & noexcept>();
    test_is_not_signed_integer<void(...) && noexcept>();
    test_is_not_signed_integer<void(...) const noexcept>();
    test_is_not_signed_integer<void(...) const & noexcept>();
    test_is_not_signed_integer<void(...) const && noexcept>();
    test_is_not_signed_integer<void(...) volatile noexcept>();
    test_is_not_signed_integer<void(...) volatile & noexcept>();
    test_is_not_signed_integer<void(...) volatile && noexcept>();
    test_is_not_signed_integer<void(...) const volatile noexcept>();
    test_is_not_signed_integer<void(...) const volatile & noexcept>();
    test_is_not_signed_integer<void(...) const volatile && noexcept>();

    test_is_not_signed_integer<void(int, ...)>();
    test_is_not_signed_integer<void(int, ...)&>();
    test_is_not_signed_integer<void(int, ...) &&>();
    test_is_not_signed_integer<void(int, ...) const>();
    test_is_not_signed_integer<void(int, ...) const&>();
    test_is_not_signed_integer<void(int, ...) const&&>();
    test_is_not_signed_integer<void(int, ...) volatile>();
    test_is_not_signed_integer<void(int, ...) volatile&>();
    test_is_not_signed_integer<void(int, ...) volatile&&>();
    test_is_not_signed_integer<void(int, ...) const volatile>();
    test_is_not_signed_integer<void(int, ...) const volatile&>();
    test_is_not_signed_integer<void(int, ...) const volatile&&>();
    test_is_not_signed_integer<void(int, ...) noexcept>();
    test_is_not_signed_integer<void(int, ...) & noexcept>();
    test_is_not_signed_integer<void(int, ...) && noexcept>();
    test_is_not_signed_integer<void(int, ...) const noexcept>();
    test_is_not_signed_integer<void(int, ...) const & noexcept>();
    test_is_not_signed_integer<void(int, ...) const && noexcept>();
    test_is_not_signed_integer<void(int, ...) volatile noexcept>();
    test_is_not_signed_integer<void(int, ...) volatile & noexcept>();
    test_is_not_signed_integer<void(int, ...) volatile && noexcept>();
    test_is_not_signed_integer<void(int, ...) const volatile noexcept>();
    test_is_not_signed_integer<void(int, ...) const volatile & noexcept>();
    test_is_not_signed_integer<void(int, ...) const volatile && noexcept>();

    test_is_not_signed_integer<int()>();
    test_is_not_signed_integer<int()&>();
    test_is_not_signed_integer<int() &&>();
    test_is_not_signed_integer<int() const>();
    test_is_not_signed_integer<int() const&>();
    test_is_not_signed_integer<int() const&&>();
    test_is_not_signed_integer<int() volatile>();
    test_is_not_signed_integer<int() volatile&>();
    test_is_not_signed_integer<int() volatile&&>();
    test_is_not_signed_integer<int() const volatile>();
    test_is_not_signed_integer<int() const volatile&>();
    test_is_not_signed_integer<int() const volatile&&>();
    test_is_not_signed_integer<int() noexcept>();
    test_is_not_signed_integer<int() & noexcept>();
    test_is_not_signed_integer<int() && noexcept>();
    test_is_not_signed_integer<int() const noexcept>();
    test_is_not_signed_integer<int() const & noexcept>();
    test_is_not_signed_integer<int() const && noexcept>();
    test_is_not_signed_integer<int() volatile noexcept>();
    test_is_not_signed_integer<int() volatile & noexcept>();
    test_is_not_signed_integer<int() volatile && noexcept>();
    test_is_not_signed_integer<int() const volatile noexcept>();
    test_is_not_signed_integer<int() const volatile & noexcept>();
    test_is_not_signed_integer<int() const volatile && noexcept>();

    test_is_not_signed_integer<int(int)>();
    test_is_not_signed_integer<int(int)&>();
    test_is_not_signed_integer<int(int) &&>();
    test_is_not_signed_integer<int(int) const>();
    test_is_not_signed_integer<int(int) const&>();
    test_is_not_signed_integer<int(int) const&&>();
    test_is_not_signed_integer<int(int) volatile>();
    test_is_not_signed_integer<int(int) volatile&>();
    test_is_not_signed_integer<int(int) volatile&&>();
    test_is_not_signed_integer<int(int) const volatile>();
    test_is_not_signed_integer<int(int) const volatile&>();
    test_is_not_signed_integer<int(int) const volatile&&>();
    test_is_not_signed_integer<int(int) noexcept>();
    test_is_not_signed_integer<int(int) & noexcept>();
    test_is_not_signed_integer<int(int) && noexcept>();
    test_is_not_signed_integer<int(int) const noexcept>();
    test_is_not_signed_integer<int(int) const & noexcept>();
    test_is_not_signed_integer<int(int) const && noexcept>();
    test_is_not_signed_integer<int(int) volatile noexcept>();
    test_is_not_signed_integer<int(int) volatile & noexcept>();
    test_is_not_signed_integer<int(int) volatile && noexcept>();
    test_is_not_signed_integer<int(int) const volatile noexcept>();
    test_is_not_signed_integer<int(int) const volatile & noexcept>();
    test_is_not_signed_integer<int(int) const volatile && noexcept>();

    test_is_not_signed_integer<int(...)>();
    test_is_not_signed_integer<int(...)&>();
    test_is_not_signed_integer<int(...) &&>();
    test_is_not_signed_integer<int(...) const>();
    test_is_not_signed_integer<int(...) const&>();
    test_is_not_signed_integer<int(...) const&&>();
    test_is_not_signed_integer<int(...) volatile>();
    test_is_not_signed_integer<int(...) volatile&>();
    test_is_not_signed_integer<int(...) volatile&&>();
    test_is_not_signed_integer<int(...) const volatile>();
    test_is_not_signed_integer<int(...) const volatile&>();
    test_is_not_signed_integer<int(...) const volatile&&>();
    test_is_not_signed_integer<int(...) noexcept>();
    test_is_not_signed_integer<int(...) & noexcept>();
    test_is_not_signed_integer<int(...) && noexcept>();
    test_is_not_signed_integer<int(...) const noexcept>();
    test_is_not_signed_integer<int(...) const & noexcept>();
    test_is_not_signed_integer<int(...) const && noexcept>();
    test_is_not_signed_integer<int(...) volatile noexcept>();
    test_is_not_signed_integer<int(...) volatile & noexcept>();
    test_is_not_signed_integer<int(...) volatile && noexcept>();
    test_is_not_signed_integer<int(...) const volatile noexcept>();
    test_is_not_signed_integer<int(...) const volatile & noexcept>();
    test_is_not_signed_integer<int(...) const volatile && noexcept>();

    test_is_not_signed_integer<int(int, ...)>();
    test_is_not_signed_integer<int(int, ...)&>();
    test_is_not_signed_integer<int(int, ...) &&>();
    test_is_not_signed_integer<int(int, ...) const>();
    test_is_not_signed_integer<int(int, ...) const&>();
    test_is_not_signed_integer<int(int, ...) const&&>();
    test_is_not_signed_integer<int(int, ...) volatile>();
    test_is_not_signed_integer<int(int, ...) volatile&>();
    test_is_not_signed_integer<int(int, ...) volatile&&>();
    test_is_not_signed_integer<int(int, ...) const volatile>();
    test_is_not_signed_integer<int(int, ...) const volatile&>();
    test_is_not_signed_integer<int(int, ...) const volatile&&>();
    test_is_not_signed_integer<int(int, ...) noexcept>();
    test_is_not_signed_integer<int(int, ...) & noexcept>();
    test_is_not_signed_integer<int(int, ...) && noexcept>();
    test_is_not_signed_integer<int(int, ...) const noexcept>();
    test_is_not_signed_integer<int(int, ...) const & noexcept>();
    test_is_not_signed_integer<int(int, ...) const && noexcept>();
    test_is_not_signed_integer<int(int, ...) volatile noexcept>();
    test_is_not_signed_integer<int(int, ...) volatile & noexcept>();
    test_is_not_signed_integer<int(int, ...) volatile && noexcept>();
    test_is_not_signed_integer<int(int, ...) const volatile noexcept>();
    test_is_not_signed_integer<int(int, ...) const volatile & noexcept>();
    test_is_not_signed_integer<int(int, ...) const volatile && noexcept>();

    test_is_not_signed_integer<void (*)()>();
    test_is_not_signed_integer<void (*)() noexcept>();

    test_is_not_signed_integer<void (*)(int)>();
    test_is_not_signed_integer<void (*)(int) noexcept>();

    test_is_not_signed_integer<void (*)(...)>();
    test_is_not_signed_integer<void (*)(...) noexcept>();

    test_is_not_signed_integer<void (*)(int, ...)>();
    test_is_not_signed_integer<void (*)(int, ...) noexcept>();

    test_is_not_signed_integer<int (*)()>();
    test_is_not_signed_integer<int (*)() noexcept>();

    test_is_not_signed_integer<int (*)(int)>();
    test_is_not_signed_integer<int (*)(int) noexcept>();

    test_is_not_signed_integer<int (*)(...)>();
    test_is_not_signed_integer<int (*)(...) noexcept>();

    test_is_not_signed_integer<int (*)(int, ...)>();
    test_is_not_signed_integer<int (*)(int, ...) noexcept>();

    test_is_not_signed_integer<void (&)()>();
    test_is_not_signed_integer<void (&)() noexcept>();

    test_is_not_signed_integer<void (&)(int)>();
    test_is_not_signed_integer<void (&)(int) noexcept>();

    test_is_not_signed_integer<void (&)(...)>();
    test_is_not_signed_integer<void (&)(...) noexcept>();

    test_is_not_signed_integer<void (&)(int, ...)>();
    test_is_not_signed_integer<void (&)(int, ...) noexcept>();

    test_is_not_signed_integer<int (&)()>();
    test_is_not_signed_integer<int (&)() noexcept>();

    test_is_not_signed_integer<int (&)(int)>();
    test_is_not_signed_integer<int (&)(int) noexcept>();

    test_is_not_signed_integer<int (&)(...)>();
    test_is_not_signed_integer<int (&)(...) noexcept>();

    test_is_not_signed_integer<int (&)(int, ...)>();
    test_is_not_signed_integer<int (&)(int, ...) noexcept>();

    test_is_not_signed_integer<void (&&)()>();
    test_is_not_signed_integer<void (&&)() noexcept>();

    test_is_not_signed_integer<void (&&)(int)>();
    test_is_not_signed_integer<void (&&)(int) noexcept>();

    test_is_not_signed_integer<void (&&)(...)>();
    test_is_not_signed_integer<void (&&)(...) noexcept>();

    test_is_not_signed_integer<void (&&)(int, ...)>();
    test_is_not_signed_integer<void (&&)(int, ...) noexcept>();

    test_is_not_signed_integer<int (&&)()>();
    test_is_not_signed_integer<int (&&)() noexcept>();

    test_is_not_signed_integer<int (&&)(int)>();
    test_is_not_signed_integer<int (&&)(int) noexcept>();

    test_is_not_signed_integer<int (&&)(...)>();
    test_is_not_signed_integer<int (&&)(...) noexcept>();

    test_is_not_signed_integer<int (&&)(int, ...)>();
    test_is_not_signed_integer<int (&&)(int, ...) noexcept>();

    test_is_not_signed_integer<void (class_type::*)()>();
    test_is_not_signed_integer<void (class_type::*)()&>();
    test_is_not_signed_integer<void (class_type::*)() &&>();
    test_is_not_signed_integer<void (class_type::*)() const>();
    test_is_not_signed_integer<void (class_type::*)() const&>();
    test_is_not_signed_integer<void (class_type::*)() const&&>();
    test_is_not_signed_integer<void (class_type::*)() noexcept>();
    test_is_not_signed_integer<void (class_type::*)() & noexcept>();
    test_is_not_signed_integer<void (class_type::*)() && noexcept>();
    test_is_not_signed_integer<void (class_type::*)() const noexcept>();
    test_is_not_signed_integer<void (class_type::*)() const & noexcept>();
    test_is_not_signed_integer<void (class_type::*)() const && noexcept>();

    test_is_not_signed_integer<void (class_type::*)(int)>();
    test_is_not_signed_integer<void (class_type::*)(int)&>();
    test_is_not_signed_integer<void (class_type::*)(int) &&>();
    test_is_not_signed_integer<void (class_type::*)(int) const>();
    test_is_not_signed_integer<void (class_type::*)(int) const&>();
    test_is_not_signed_integer<void (class_type::*)(int) const&&>();
    test_is_not_signed_integer<void (class_type::*)(int) noexcept>();
    test_is_not_signed_integer<void (class_type::*)(int) & noexcept>();
    test_is_not_signed_integer<void (class_type::*)(int) && noexcept>();
    test_is_not_signed_integer<void (class_type::*)(int) const noexcept>();
    test_is_not_signed_integer<void (class_type::*)(int) const & noexcept>();
    test_is_not_signed_integer<void (class_type::*)(int) const && noexcept>();

    test_is_not_signed_integer<void (class_type::*)(...)>();
    test_is_not_signed_integer<void (class_type::*)(...)&>();
    test_is_not_signed_integer<void (class_type::*)(...) &&>();
    test_is_not_signed_integer<void (class_type::*)(...) const>();
    test_is_not_signed_integer<void (class_type::*)(...) const&>();
    test_is_not_signed_integer<void (class_type::*)(...) const&&>();
    test_is_not_signed_integer<void (class_type::*)(...) noexcept>();
    test_is_not_signed_integer<void (class_type::*)(...) & noexcept>();
    test_is_not_signed_integer<void (class_type::*)(...) && noexcept>();
    test_is_not_signed_integer<void (class_type::*)(...) const noexcept>();
    test_is_not_signed_integer<void (class_type::*)(...) const & noexcept>();
    test_is_not_signed_integer<void (class_type::*)(...) const && noexcept>();

    test_is_not_signed_integer<void (class_type::*)(int, ...)>();
    test_is_not_signed_integer<void (class_type::*)(int, ...)&>();
    test_is_not_signed_integer<void (class_type::*)(int, ...) &&>();
    test_is_not_signed_integer<void (class_type::*)(int, ...) const>();
    test_is_not_signed_integer<void (class_type::*)(int, ...) const&>();
    test_is_not_signed_integer<void (class_type::*)(int, ...) const&&>();
    test_is_not_signed_integer<void (class_type::*)(int, ...) noexcept>();
    test_is_not_signed_integer<void (class_type::*)(int, ...) & noexcept>();
    test_is_not_signed_integer<void (class_type::*)(int, ...) && noexcept>();
    test_is_not_signed_integer<void (class_type::*)(int, ...) const noexcept>();
    test_is_not_signed_integer<void (class_type::*)(int, ...) const & noexcept>();
    test_is_not_signed_integer<void (class_type::*)(int, ...) const && noexcept>();

    test_is_not_signed_integer<int (class_type::*)()>();
    test_is_not_signed_integer<int (class_type::*)()&>();
    test_is_not_signed_integer<int (class_type::*)() &&>();
    test_is_not_signed_integer<int (class_type::*)() const>();
    test_is_not_signed_integer<int (class_type::*)() const&>();
    test_is_not_signed_integer<int (class_type::*)() const&&>();
    test_is_not_signed_integer<int (class_type::*)() noexcept>();
    test_is_not_signed_integer<int (class_type::*)() & noexcept>();
    test_is_not_signed_integer<int (class_type::*)() && noexcept>();
    test_is_not_signed_integer<int (class_type::*)() const noexcept>();
    test_is_not_signed_integer<int (class_type::*)() const & noexcept>();
    test_is_not_signed_integer<int (class_type::*)() const && noexcept>();

    test_is_not_signed_integer<int (class_type::*)(int)>();
    test_is_not_signed_integer<int (class_type::*)(int)&>();
    test_is_not_signed_integer<int (class_type::*)(int) &&>();
    test_is_not_signed_integer<int (class_type::*)(int) const>();
    test_is_not_signed_integer<int (class_type::*)(int) const&>();
    test_is_not_signed_integer<int (class_type::*)(int) const&&>();
    test_is_not_signed_integer<int (class_type::*)(int) noexcept>();
    test_is_not_signed_integer<int (class_type::*)(int) & noexcept>();
    test_is_not_signed_integer<int (class_type::*)(int) && noexcept>();
    test_is_not_signed_integer<int (class_type::*)(int) const noexcept>();
    test_is_not_signed_integer<int (class_type::*)(int) const & noexcept>();
    test_is_not_signed_integer<int (class_type::*)(int) const && noexcept>();

    test_is_not_signed_integer<int (class_type::*)(...)>();
    test_is_not_signed_integer<int (class_type::*)(...)&>();
    test_is_not_signed_integer<int (class_type::*)(...) &&>();
    test_is_not_signed_integer<int (class_type::*)(...) const>();
    test_is_not_signed_integer<int (class_type::*)(...) const&>();
    test_is_not_signed_integer<int (class_type::*)(...) const&&>();
    test_is_not_signed_integer<int (class_type::*)(...) noexcept>();
    test_is_not_signed_integer<int (class_type::*)(...) & noexcept>();
    test_is_not_signed_integer<int (class_type::*)(...) && noexcept>();
    test_is_not_signed_integer<int (class_type::*)(...) const noexcept>();
    test_is_not_signed_integer<int (class_type::*)(...) const & noexcept>();
    test_is_not_signed_integer<int (class_type::*)(...) const && noexcept>();

    test_is_not_signed_integer<int (class_type::*)(int, ...)>();
    test_is_not_signed_integer<int (class_type::*)(int, ...)&>();
    test_is_not_signed_integer<int (class_type::*)(int, ...) &&>();
    test_is_not_signed_integer<int (class_type::*)(int, ...) const>();
    test_is_not_signed_integer<int (class_type::*)(int, ...) const&>();
    test_is_not_signed_integer<int (class_type::*)(int, ...) const&&>();
    test_is_not_signed_integer<int (class_type::*)(int, ...) noexcept>();
    test_is_not_signed_integer<int (class_type::*)(int, ...) & noexcept>();
    test_is_not_signed_integer<int (class_type::*)(int, ...) && noexcept>();
    test_is_not_signed_integer<int (class_type::*)(int, ...) const noexcept>();
    test_is_not_signed_integer<int (class_type::*)(int, ...) const & noexcept>();
    test_is_not_signed_integer<int (class_type::*)(int, ...) const && noexcept>();
}
