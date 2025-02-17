#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_referenceable.hpp>
#include <vector>

template <typename TypeT>
void test_is_referenceable_impl()
{
    STATIC_REQUIRE(phi::is_referenceable<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_referenceable<TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_referenceable_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_not_referenceable_v<TypeT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_referenceable<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_referenceable<TypeT>);
}

template <typename TypeT>
void test_is_not_referenceable_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_referenceable<TypeT>::value);
    STATIC_REQUIRE(phi::is_not_referenceable<TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_referenceable_v<TypeT>);
    STATIC_REQUIRE(phi::is_not_referenceable_v<TypeT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_referenceable<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_referenceable<TypeT>);
}

template <typename TypeT>
void test_is_referenceable()
{
    test_is_referenceable_impl<TypeT>();
    test_is_referenceable_impl<const TypeT>();
    test_is_referenceable_impl<volatile TypeT>();
    test_is_referenceable_impl<const volatile TypeT>();
}

template <typename TypeT>
void test_is_not_referenceable()
{
    test_is_not_referenceable_impl<TypeT>();
    test_is_not_referenceable_impl<const TypeT>();
    test_is_not_referenceable_impl<volatile TypeT>();
    test_is_not_referenceable_impl<const volatile TypeT>();
}

TEST_CASE("is_referenceable")
{
    test_is_not_referenceable<void>();
    test_is_referenceable<phi::nullptr_t>();
    test_is_referenceable<bool>();
    test_is_referenceable<char>();
    test_is_referenceable<signed char>();
    test_is_referenceable<unsigned char>();
    test_is_referenceable<short>();
    test_is_referenceable<unsigned short>();
    test_is_referenceable<int>();
    test_is_referenceable<unsigned int>();
    test_is_referenceable<long>();
    test_is_referenceable<unsigned long>();
    test_is_referenceable<long long>();
    test_is_referenceable<unsigned long long>();
    test_is_referenceable<float>();
    test_is_referenceable<double>();
    test_is_referenceable<long double>();
    test_is_referenceable<char8_t>();
    test_is_referenceable<char16_t>();
    test_is_referenceable<char32_t>();
    test_is_referenceable<wchar_t>();

    test_is_referenceable<phi::boolean>();
    test_is_referenceable<phi::integer<signed char>>();
    test_is_referenceable<phi::integer<unsigned char>>();
    test_is_referenceable<phi::integer<short>>();
    test_is_referenceable<phi::integer<unsigned short>>();
    test_is_referenceable<phi::integer<int>>();
    test_is_referenceable<phi::integer<unsigned int>>();
    test_is_referenceable<phi::integer<long>>();
    test_is_referenceable<phi::integer<unsigned long>>();
    test_is_referenceable<phi::integer<long long>>();
    test_is_referenceable<phi::integer<unsigned long long>>();
    test_is_referenceable<phi::floating_point<float>>();
    test_is_referenceable<phi::floating_point<double>>();
    test_is_referenceable<phi::floating_point<long double>>();

    test_is_referenceable<std::vector<int>>();
    test_is_referenceable<phi::scope_ptr<int>>();

    test_is_referenceable<int&>();
    test_is_referenceable<const int&>();
    test_is_referenceable<volatile int&>();
    test_is_referenceable<const volatile int&>();
    test_is_referenceable<int&&>();
    test_is_referenceable<const int&&>();
    test_is_referenceable<volatile int&&>();
    test_is_referenceable<const volatile int&&>();
    test_is_referenceable<int*>();
    test_is_referenceable<const int*>();
    test_is_referenceable<volatile int*>();
    test_is_referenceable<const volatile int*>();
    test_is_referenceable<int**>();
    test_is_referenceable<const int**>();
    test_is_referenceable<volatile int**>();
    test_is_referenceable<const volatile int**>();
    test_is_referenceable<int*&>();
    test_is_referenceable<const int*&>();
    test_is_referenceable<volatile int*&>();
    test_is_referenceable<const volatile int*&>();
    test_is_referenceable<int*&&>();
    test_is_referenceable<const int*&&>();
    test_is_referenceable<volatile int*&&>();
    test_is_referenceable<const volatile int*&&>();
    test_is_referenceable<void*>();
    test_is_referenceable<char[3]>();
    test_is_referenceable<char[]>();
    test_is_referenceable<char* [3]>();
    test_is_referenceable<char*[]>();
    test_is_referenceable<int(*)[3]>();
    test_is_referenceable<int(*)[]>();
    test_is_referenceable<int(&)[3]>();
    test_is_referenceable<int(&)[]>();
    test_is_referenceable<int(&&)[3]>();
    test_is_referenceable<int(&&)[]>();
    test_is_referenceable<char[3][2]>();
    test_is_referenceable<char[][2]>();
    test_is_referenceable<char* [3][2]>();
    test_is_referenceable<char*[][2]>();
    test_is_referenceable<int(*)[3][2]>();
    test_is_referenceable<int(*)[][2]>();
    test_is_referenceable<int(&)[3][2]>();
    test_is_referenceable<int(&)[][2]>();
    test_is_referenceable<int(&&)[3][2]>();
    test_is_referenceable<int(&&)[][2]>();
    test_is_referenceable<class_type>();
    test_is_referenceable<class_type[]>();
    test_is_referenceable<class_type[2]>();
    test_is_referenceable<template_type<void>>();
    test_is_referenceable<template_type<int>>();
    test_is_referenceable<template_type<class_type>>();
    test_is_referenceable<template_type<incomplete_type>>();
    test_is_referenceable<variadic_template<>>();
    test_is_referenceable<variadic_template<void>>();
    test_is_referenceable<variadic_template<int>>();
    test_is_referenceable<variadic_template<class_type>>();
    test_is_referenceable<variadic_template<incomplete_type>>();
    test_is_referenceable<variadic_template<int, void, class_type, volatile char[]>>();
    test_is_referenceable<public_derived_from<base>>();
    test_is_referenceable<public_derived_from<derived>>();
    test_is_referenceable<public_derived_from<class_type>>();
    test_is_referenceable<private_derived_from<base>>();
    test_is_referenceable<private_derived_from<derived>>();
    test_is_referenceable<private_derived_from<class_type>>();
    test_is_referenceable<protected_derived_from<base>>();
    test_is_referenceable<protected_derived_from<derived>>();
    test_is_referenceable<protected_derived_from<class_type>>();
    test_is_referenceable<virtual_derived_from<base>>();
    test_is_referenceable<virtual_derived_from<derived>>();
    test_is_referenceable<virtual_derived_from<class_type>>();
    test_is_referenceable<union_type>();
    test_is_referenceable<non_empty_union>();
    test_is_referenceable<non_trivial_union>();
    test_is_referenceable<empty>();
    test_is_referenceable<not_empty>();
    test_is_referenceable<non_trivial>();
    test_is_referenceable<bit_zero>();
    test_is_referenceable<bit_one>();
    test_is_referenceable<base>();
    test_is_referenceable<derived>();
    test_is_referenceable<non_empty_base>();
    test_is_referenceable<empty_base>();
    test_is_referenceable<virtual_base>();
    test_is_referenceable<polymorphic>();
    test_is_referenceable<derived_polymorphic>();
    test_is_referenceable<abstract>();
    test_is_referenceable<public_abstract>();
    test_is_referenceable<private_abstract>();
    test_is_referenceable<protected_abstract>();
    test_is_referenceable<abstract_template<int>>();
    test_is_referenceable<abstract_template<double>>();
    test_is_referenceable<abstract_template<class_type>>();
    test_is_referenceable<abstract_template<incomplete_type>>();
    test_is_referenceable<public_abstract_deleted_destructor>();
    test_is_referenceable<protected_abstract_deleted_destructor>();
    test_is_referenceable<private_abstract_deleted_destructor>();
    test_is_referenceable<final_type>();
    test_is_referenceable<final_derived>();
    test_is_referenceable<public_destructor>();
    test_is_referenceable<protected_destructor>();
    test_is_referenceable<private_destructor>();
    test_is_referenceable<virtual_public_destructor>();
    test_is_referenceable<virtual_protected_destructor>();
    test_is_referenceable<virtual_private_destructor>();
    test_is_referenceable<pure_public_destructor>();
    test_is_referenceable<pure_protected_destructor>();
    test_is_referenceable<pure_private_destructor>();
    test_is_referenceable<deleted_public_destructor>();
    test_is_referenceable<deleted_protected_destructor>();
    test_is_referenceable<deleted_private_destructor>();
    test_is_referenceable<deleted_virtual_public_destructor>();
    test_is_referenceable<deleted_virtual_protected_destructor>();
    test_is_referenceable<deleted_virtual_private_destructor>();
    test_is_referenceable<explicit_class>();
    test_is_referenceable<nothrow_explicit_class>();
    test_is_referenceable<throw_explicit_class>();
    test_is_referenceable<throw_default_class>();
    test_is_referenceable<throw_copy_constructible_class>();
    test_is_referenceable<throw_move_constructible_class>();
    test_is_referenceable<throw_destructor>();
    test_is_referenceable<noexcept_explicit_class>();
    test_is_referenceable<except_explicit_class>();
    test_is_referenceable<noexcept_default_class>();
    test_is_referenceable<except_default_class>();
    test_is_referenceable<noexcept_copy_constructible_class>();
    test_is_referenceable<except_copy_constructible_class>();
    test_is_referenceable<noexcept_move_constructible_class>();
    test_is_referenceable<except_move_constructible_class>();
    test_is_referenceable<noexcept_copy_assign_class>();
    test_is_referenceable<except_copy_assign_class>();
    test_is_referenceable<noexcept_move_assign_class>();
    test_is_referenceable<except_move_assign_class>();
    test_is_referenceable<deleted_copy_assign_class>();
    test_is_referenceable<deleted_move_assign_class>();
    test_is_referenceable<noexcept_move_constructible_and_assignable_class>();
    test_is_referenceable<except_move_constructible_noexcept_move_assign_class>();
    test_is_referenceable<noexcept_move_constructible_except_move_assign_class>();
    test_is_referenceable<except_move_constructible_and_assign_class>();
    test_is_referenceable<implicit_to<int>>();
    test_is_referenceable<implicit_to<float>>();
    test_is_referenceable<implicit_to<class_type>>();
    test_is_referenceable<deleted_implicit_to<int>>();
    test_is_referenceable<deleted_implicit_to<float>>();
    test_is_referenceable<deleted_implicit_to<class_type>>();
    test_is_referenceable<explicit_to<int>>();
    test_is_referenceable<explicit_to<float>>();
    test_is_referenceable<explicit_to<class_type>>();
    test_is_referenceable<deleted_explicit_to<int>>();
    test_is_referenceable<deleted_explicit_to<float>>();
    test_is_referenceable<deleted_explicit_to<class_type>>();
    test_is_referenceable<ellipsis>();
    test_is_referenceable<deleted_ellipsis>();
    test_is_referenceable<copy_constructible_only_type>();
    test_is_referenceable<move_constructible_only_type>();
    test_is_referenceable<overloaded_operators>();
    test_is_referenceable<public_int_member>();
    test_is_referenceable<protected_int_member>();
    test_is_referenceable<private_int_member>();
    test_is_referenceable<public_static_int_member>();
    test_is_referenceable<protected_static_int_member>();
    test_is_referenceable<private_static_int_member>();
    test_is_referenceable<public_template_member<int>>();
    test_is_referenceable<public_template_member<float>>();
    test_is_referenceable<public_template_member<class_type>>();
    test_is_referenceable<protected_template_member<int>>();
    test_is_referenceable<protected_template_member<float>>();
    test_is_referenceable<protected_template_member<class_type>>();
    test_is_referenceable<private_template_member<int>>();
    test_is_referenceable<private_template_member<float>>();
    test_is_referenceable<private_template_member<class_type>>();
    test_is_referenceable<public_static_template_member<int>>();
    test_is_referenceable<public_static_template_member<float>>();
    test_is_referenceable<public_static_template_member<class_type>>();
    test_is_referenceable<protected_static_template_member<int>>();
    test_is_referenceable<protected_static_template_member<float>>();
    test_is_referenceable<protected_static_template_member<class_type>>();
    test_is_referenceable<private_static_template_member<int>>();
    test_is_referenceable<private_static_template_member<float>>();
    test_is_referenceable<private_static_template_member<class_type>>();
    test_is_referenceable<cannot_instantiate<int>>();
    test_is_referenceable<cannot_instantiate<float>>();
    test_is_referenceable<cannot_instantiate<class_type>>();
    test_is_referenceable<Enum>();
    test_is_referenceable<EnumSigned>();
    test_is_referenceable<EnumUnsigned>();
    test_is_referenceable<EnumClass>();
    test_is_referenceable<EnumStruct>();
    test_is_referenceable<function_type>();
    test_is_referenceable<function_ptr>();
    test_is_referenceable<member_object_ptr>();
    test_is_referenceable<member_function_ptr>();
    test_is_referenceable<lambda_type>();
    test_is_referenceable<lambda_noexcept_type>();
    test_is_referenceable<lambda_throws_type>();
    test_is_referenceable<incomplete_type>();
    test_is_referenceable<incomplete_template<void>>();
    test_is_referenceable<incomplete_template<int>>();
    test_is_referenceable<incomplete_template<class_type>>();
    test_is_referenceable<incomplete_template<incomplete_type>>();
    test_is_referenceable<incomplete_variadic_template<>>();
    test_is_referenceable<incomplete_variadic_template<void>>();
    test_is_referenceable<incomplete_variadic_template<int>>();
    test_is_referenceable<incomplete_variadic_template<class_type>>();
    test_is_referenceable<incomplete_variadic_template<incomplete_type>>();
    test_is_referenceable<incomplete_variadic_template<int, void, class_type, volatile char[]>>();
    test_is_referenceable<incomplete_union>();
    test_is_referenceable<IncompleteEnumSigned>();
    test_is_referenceable<IncompleteEnumUnsigned>();
    test_is_referenceable<IncompleteEnumClass>();
    test_is_referenceable<IncompleteEnumStruct>();
    test_is_referenceable<int class_type::*>();
    test_is_referenceable<float class_type::*>();
    test_is_referenceable<void * class_type::*>();
    test_is_referenceable<int * class_type::*>();
    test_is_referenceable<int class_type::*&>();
    test_is_referenceable<float class_type::*&>();
    test_is_referenceable<void * class_type::*&>();
    test_is_referenceable<int * class_type::*&>();
    test_is_referenceable<int class_type::*&&>();
    test_is_referenceable<float class_type::*&&>();
    test_is_referenceable<void * class_type::*&&>();
    test_is_referenceable<int * class_type::*&&>();
    test_is_referenceable<int class_type::* const>();
    test_is_referenceable<float class_type::* const>();
    test_is_referenceable<void * class_type::* const>();
    test_is_referenceable<int class_type::* const&>();
    test_is_referenceable<float class_type::* const&>();
    test_is_referenceable<void * class_type::* const&>();
    test_is_referenceable<int class_type::* const&&>();
    test_is_referenceable<float class_type::* const&&>();
    test_is_referenceable<void * class_type::* const&&>();
    test_is_referenceable<int class_type::* volatile>();
    test_is_referenceable<float class_type::* volatile>();
    test_is_referenceable<void * class_type::* volatile>();
    test_is_referenceable<int class_type::* volatile&>();
    test_is_referenceable<float class_type::* volatile&>();
    test_is_referenceable<void * class_type::* volatile&>();
    test_is_referenceable<int class_type::* volatile&&>();
    test_is_referenceable<float class_type::* volatile&&>();
    test_is_referenceable<void * class_type::* volatile&&>();
    test_is_referenceable<int class_type::* const volatile>();
    test_is_referenceable<float class_type::* const volatile>();
    test_is_referenceable<void * class_type::* const volatile>();
    test_is_referenceable<int class_type::* const volatile&>();
    test_is_referenceable<float class_type::* const volatile&>();
    test_is_referenceable<void * class_type::* const volatile&>();
    test_is_referenceable<int class_type::* const volatile&&>();
    test_is_referenceable<float class_type::* const volatile&&>();
    test_is_referenceable<void * class_type::* const volatile&&>();
    test_is_referenceable<non_default_constructible>();
    test_is_referenceable<non_copy_constructible>();
    test_is_referenceable<non_move_constructible>();
    test_is_referenceable<non_copy_assignable>();
    test_is_referenceable<non_move_assignable>();
    test_is_referenceable<non_assignable>();
    test_is_referenceable<non_copyable>();
    test_is_referenceable<non_moveable>();
    test_is_referenceable<non_constructible>();
    test_is_referenceable<non_destructible>();
    test_is_referenceable<tracked>();
    test_is_referenceable<trap_constructible>();
    test_is_referenceable<trap_implicit_conversion>();
    test_is_referenceable<trap_comma>();
    test_is_referenceable<trap_call>();
    test_is_referenceable<trap_self_assign>();
    test_is_referenceable<trap_deref>();
    test_is_referenceable<trap_array_subscript>();

    test_is_referenceable<void()>();
    test_is_not_referenceable<void()&>();
    test_is_not_referenceable<void() &&>();
    test_is_not_referenceable<void() const>();
    test_is_not_referenceable<void() const&>();
    test_is_not_referenceable<void() const&&>();
    test_is_not_referenceable<void() volatile>();
    test_is_not_referenceable<void() volatile&>();
    test_is_not_referenceable<void() volatile&&>();
    test_is_not_referenceable<void() const volatile>();
    test_is_not_referenceable<void() const volatile&>();
    test_is_not_referenceable<void() const volatile&&>();
    test_is_referenceable<void() noexcept>();
    test_is_not_referenceable<void() & noexcept>();
    test_is_not_referenceable<void() && noexcept>();
    test_is_not_referenceable<void() const noexcept>();
    test_is_not_referenceable<void() const & noexcept>();
    test_is_not_referenceable<void() const && noexcept>();
    test_is_not_referenceable<void() volatile noexcept>();
    test_is_not_referenceable<void() volatile & noexcept>();
    test_is_not_referenceable<void() volatile && noexcept>();
    test_is_not_referenceable<void() const volatile noexcept>();
    test_is_not_referenceable<void() const volatile & noexcept>();
    test_is_not_referenceable<void() const volatile && noexcept>();

    test_is_referenceable<void(int)>();
    test_is_not_referenceable<void(int)&>();
    test_is_not_referenceable<void(int) &&>();
    test_is_not_referenceable<void(int) const>();
    test_is_not_referenceable<void(int) const&>();
    test_is_not_referenceable<void(int) const&&>();
    test_is_not_referenceable<void(int) volatile>();
    test_is_not_referenceable<void(int) volatile&>();
    test_is_not_referenceable<void(int) volatile&&>();
    test_is_not_referenceable<void(int) const volatile>();
    test_is_not_referenceable<void(int) const volatile&>();
    test_is_not_referenceable<void(int) const volatile&&>();
    test_is_referenceable<void(int) noexcept>();
    test_is_not_referenceable<void(int) & noexcept>();
    test_is_not_referenceable<void(int) && noexcept>();
    test_is_not_referenceable<void(int) const noexcept>();
    test_is_not_referenceable<void(int) const & noexcept>();
    test_is_not_referenceable<void(int) const && noexcept>();
    test_is_not_referenceable<void(int) volatile noexcept>();
    test_is_not_referenceable<void(int) volatile & noexcept>();
    test_is_not_referenceable<void(int) volatile && noexcept>();
    test_is_not_referenceable<void(int) const volatile noexcept>();
    test_is_not_referenceable<void(int) const volatile & noexcept>();
    test_is_not_referenceable<void(int) const volatile && noexcept>();

    test_is_referenceable<void(...)>();
    test_is_not_referenceable<void(...)&>();
    test_is_not_referenceable<void(...) &&>();
    test_is_not_referenceable<void(...) const>();
    test_is_not_referenceable<void(...) const&>();
    test_is_not_referenceable<void(...) const&&>();
    test_is_not_referenceable<void(...) volatile>();
    test_is_not_referenceable<void(...) volatile&>();
    test_is_not_referenceable<void(...) volatile&&>();
    test_is_not_referenceable<void(...) const volatile>();
    test_is_not_referenceable<void(...) const volatile&>();
    test_is_not_referenceable<void(...) const volatile&&>();
    test_is_referenceable<void(...) noexcept>();
    test_is_not_referenceable<void(...) & noexcept>();
    test_is_not_referenceable<void(...) && noexcept>();
    test_is_not_referenceable<void(...) const noexcept>();
    test_is_not_referenceable<void(...) const & noexcept>();
    test_is_not_referenceable<void(...) const && noexcept>();
    test_is_not_referenceable<void(...) volatile noexcept>();
    test_is_not_referenceable<void(...) volatile & noexcept>();
    test_is_not_referenceable<void(...) volatile && noexcept>();
    test_is_not_referenceable<void(...) const volatile noexcept>();
    test_is_not_referenceable<void(...) const volatile & noexcept>();
    test_is_not_referenceable<void(...) const volatile && noexcept>();

    test_is_referenceable<void(int, ...)>();
    test_is_not_referenceable<void(int, ...)&>();
    test_is_not_referenceable<void(int, ...) &&>();
    test_is_not_referenceable<void(int, ...) const>();
    test_is_not_referenceable<void(int, ...) const&>();
    test_is_not_referenceable<void(int, ...) const&&>();
    test_is_not_referenceable<void(int, ...) volatile>();
    test_is_not_referenceable<void(int, ...) volatile&>();
    test_is_not_referenceable<void(int, ...) volatile&&>();
    test_is_not_referenceable<void(int, ...) const volatile>();
    test_is_not_referenceable<void(int, ...) const volatile&>();
    test_is_not_referenceable<void(int, ...) const volatile&&>();
    test_is_referenceable<void(int, ...) noexcept>();
    test_is_not_referenceable<void(int, ...) & noexcept>();
    test_is_not_referenceable<void(int, ...) && noexcept>();
    test_is_not_referenceable<void(int, ...) const noexcept>();
    test_is_not_referenceable<void(int, ...) const & noexcept>();
    test_is_not_referenceable<void(int, ...) const && noexcept>();
    test_is_not_referenceable<void(int, ...) volatile noexcept>();
    test_is_not_referenceable<void(int, ...) volatile & noexcept>();
    test_is_not_referenceable<void(int, ...) volatile && noexcept>();
    test_is_not_referenceable<void(int, ...) const volatile noexcept>();
    test_is_not_referenceable<void(int, ...) const volatile & noexcept>();
    test_is_not_referenceable<void(int, ...) const volatile && noexcept>();

    test_is_referenceable<int()>();
    test_is_not_referenceable<int()&>();
    test_is_not_referenceable<int() &&>();
    test_is_not_referenceable<int() const>();
    test_is_not_referenceable<int() const&>();
    test_is_not_referenceable<int() const&&>();
    test_is_not_referenceable<int() volatile>();
    test_is_not_referenceable<int() volatile&>();
    test_is_not_referenceable<int() volatile&&>();
    test_is_not_referenceable<int() const volatile>();
    test_is_not_referenceable<int() const volatile&>();
    test_is_not_referenceable<int() const volatile&&>();
    test_is_referenceable<int() noexcept>();
    test_is_not_referenceable<int() & noexcept>();
    test_is_not_referenceable<int() && noexcept>();
    test_is_not_referenceable<int() const noexcept>();
    test_is_not_referenceable<int() const & noexcept>();
    test_is_not_referenceable<int() const && noexcept>();
    test_is_not_referenceable<int() volatile noexcept>();
    test_is_not_referenceable<int() volatile & noexcept>();
    test_is_not_referenceable<int() volatile && noexcept>();
    test_is_not_referenceable<int() const volatile noexcept>();
    test_is_not_referenceable<int() const volatile & noexcept>();
    test_is_not_referenceable<int() const volatile && noexcept>();

    test_is_referenceable<int(int)>();
    test_is_not_referenceable<int(int)&>();
    test_is_not_referenceable<int(int) &&>();
    test_is_not_referenceable<int(int) const>();
    test_is_not_referenceable<int(int) const&>();
    test_is_not_referenceable<int(int) const&&>();
    test_is_not_referenceable<int(int) volatile>();
    test_is_not_referenceable<int(int) volatile&>();
    test_is_not_referenceable<int(int) volatile&&>();
    test_is_not_referenceable<int(int) const volatile>();
    test_is_not_referenceable<int(int) const volatile&>();
    test_is_not_referenceable<int(int) const volatile&&>();
    test_is_referenceable<int(int) noexcept>();
    test_is_not_referenceable<int(int) & noexcept>();
    test_is_not_referenceable<int(int) && noexcept>();
    test_is_not_referenceable<int(int) const noexcept>();
    test_is_not_referenceable<int(int) const & noexcept>();
    test_is_not_referenceable<int(int) const && noexcept>();
    test_is_not_referenceable<int(int) volatile noexcept>();
    test_is_not_referenceable<int(int) volatile & noexcept>();
    test_is_not_referenceable<int(int) volatile && noexcept>();
    test_is_not_referenceable<int(int) const volatile noexcept>();
    test_is_not_referenceable<int(int) const volatile & noexcept>();
    test_is_not_referenceable<int(int) const volatile && noexcept>();

    test_is_referenceable<int(...)>();
    test_is_not_referenceable<int(...)&>();
    test_is_not_referenceable<int(...) &&>();
    test_is_not_referenceable<int(...) const>();
    test_is_not_referenceable<int(...) const&>();
    test_is_not_referenceable<int(...) const&&>();
    test_is_not_referenceable<int(...) volatile>();
    test_is_not_referenceable<int(...) volatile&>();
    test_is_not_referenceable<int(...) volatile&&>();
    test_is_not_referenceable<int(...) const volatile>();
    test_is_not_referenceable<int(...) const volatile&>();
    test_is_not_referenceable<int(...) const volatile&&>();
    test_is_referenceable<int(...) noexcept>();
    test_is_not_referenceable<int(...) & noexcept>();
    test_is_not_referenceable<int(...) && noexcept>();
    test_is_not_referenceable<int(...) const noexcept>();
    test_is_not_referenceable<int(...) const & noexcept>();
    test_is_not_referenceable<int(...) const && noexcept>();
    test_is_not_referenceable<int(...) volatile noexcept>();
    test_is_not_referenceable<int(...) volatile & noexcept>();
    test_is_not_referenceable<int(...) volatile && noexcept>();
    test_is_not_referenceable<int(...) const volatile noexcept>();
    test_is_not_referenceable<int(...) const volatile & noexcept>();
    test_is_not_referenceable<int(...) const volatile && noexcept>();

    test_is_referenceable<int(int, ...)>();
    test_is_not_referenceable<int(int, ...)&>();
    test_is_not_referenceable<int(int, ...) &&>();
    test_is_not_referenceable<int(int, ...) const>();
    test_is_not_referenceable<int(int, ...) const&>();
    test_is_not_referenceable<int(int, ...) const&&>();
    test_is_not_referenceable<int(int, ...) volatile>();
    test_is_not_referenceable<int(int, ...) volatile&>();
    test_is_not_referenceable<int(int, ...) volatile&&>();
    test_is_not_referenceable<int(int, ...) const volatile>();
    test_is_not_referenceable<int(int, ...) const volatile&>();
    test_is_not_referenceable<int(int, ...) const volatile&&>();
    test_is_referenceable<int(int, ...) noexcept>();
    test_is_not_referenceable<int(int, ...) & noexcept>();
    test_is_not_referenceable<int(int, ...) && noexcept>();
    test_is_not_referenceable<int(int, ...) const noexcept>();
    test_is_not_referenceable<int(int, ...) const & noexcept>();
    test_is_not_referenceable<int(int, ...) const && noexcept>();
    test_is_not_referenceable<int(int, ...) volatile noexcept>();
    test_is_not_referenceable<int(int, ...) volatile & noexcept>();
    test_is_not_referenceable<int(int, ...) volatile && noexcept>();
    test_is_not_referenceable<int(int, ...) const volatile noexcept>();
    test_is_not_referenceable<int(int, ...) const volatile & noexcept>();
    test_is_not_referenceable<int(int, ...) const volatile && noexcept>();

    test_is_referenceable<void (*)()>();
    test_is_referenceable<void (*)() noexcept>();

    test_is_referenceable<void (*)(int)>();
    test_is_referenceable<void (*)(int) noexcept>();

    test_is_referenceable<void (*)(...)>();
    test_is_referenceable<void (*)(...) noexcept>();

    test_is_referenceable<void (*)(int, ...)>();
    test_is_referenceable<void (*)(int, ...) noexcept>();

    test_is_referenceable<int (*)()>();
    test_is_referenceable<int (*)() noexcept>();

    test_is_referenceable<int (*)(int)>();
    test_is_referenceable<int (*)(int) noexcept>();

    test_is_referenceable<int (*)(...)>();
    test_is_referenceable<int (*)(...) noexcept>();

    test_is_referenceable<int (*)(int, ...)>();
    test_is_referenceable<int (*)(int, ...) noexcept>();

    test_is_referenceable<void (&)()>();
    test_is_referenceable<void (&)() noexcept>();

    test_is_referenceable<void (&)(int)>();
    test_is_referenceable<void (&)(int) noexcept>();

    test_is_referenceable<void (&)(...)>();
    test_is_referenceable<void (&)(...) noexcept>();

    test_is_referenceable<void (&)(int, ...)>();
    test_is_referenceable<void (&)(int, ...) noexcept>();

    test_is_referenceable<int (&)()>();
    test_is_referenceable<int (&)() noexcept>();

    test_is_referenceable<int (&)(int)>();
    test_is_referenceable<int (&)(int) noexcept>();

    test_is_referenceable<int (&)(...)>();
    test_is_referenceable<int (&)(...) noexcept>();

    test_is_referenceable<int (&)(int, ...)>();
    test_is_referenceable<int (&)(int, ...) noexcept>();

    test_is_referenceable<void (&&)()>();
    test_is_referenceable<void (&&)() noexcept>();

    test_is_referenceable<void (&&)(int)>();
    test_is_referenceable<void (&&)(int) noexcept>();

    test_is_referenceable<void (&&)(...)>();
    test_is_referenceable<void (&&)(...) noexcept>();

    test_is_referenceable<void (&&)(int, ...)>();
    test_is_referenceable<void (&&)(int, ...) noexcept>();

    test_is_referenceable<int (&&)()>();
    test_is_referenceable<int (&&)() noexcept>();

    test_is_referenceable<int (&&)(int)>();
    test_is_referenceable<int (&&)(int) noexcept>();

    test_is_referenceable<int (&&)(...)>();
    test_is_referenceable<int (&&)(...) noexcept>();

    test_is_referenceable<int (&&)(int, ...)>();
    test_is_referenceable<int (&&)(int, ...) noexcept>();

    test_is_referenceable<void (class_type::*)()>();
    test_is_referenceable<void (class_type::*)()&>();
    test_is_referenceable<void (class_type::*)() &&>();
    test_is_referenceable<void (class_type::*)() const>();
    test_is_referenceable<void (class_type::*)() const&>();
    test_is_referenceable<void (class_type::*)() const&&>();
    test_is_referenceable<void (class_type::*)() noexcept>();
    test_is_referenceable<void (class_type::*)() & noexcept>();
    test_is_referenceable<void (class_type::*)() && noexcept>();
    test_is_referenceable<void (class_type::*)() const noexcept>();
    test_is_referenceable<void (class_type::*)() const & noexcept>();
    test_is_referenceable<void (class_type::*)() const && noexcept>();

    test_is_referenceable<void (class_type::*)(int)>();
    test_is_referenceable<void (class_type::*)(int)&>();
    test_is_referenceable<void (class_type::*)(int) &&>();
    test_is_referenceable<void (class_type::*)(int) const>();
    test_is_referenceable<void (class_type::*)(int) const&>();
    test_is_referenceable<void (class_type::*)(int) const&&>();
    test_is_referenceable<void (class_type::*)(int) noexcept>();
    test_is_referenceable<void (class_type::*)(int) & noexcept>();
    test_is_referenceable<void (class_type::*)(int) && noexcept>();
    test_is_referenceable<void (class_type::*)(int) const noexcept>();
    test_is_referenceable<void (class_type::*)(int) const & noexcept>();
    test_is_referenceable<void (class_type::*)(int) const && noexcept>();

    test_is_referenceable<void (class_type::*)(...)>();
    test_is_referenceable<void (class_type::*)(...)&>();
    test_is_referenceable<void (class_type::*)(...) &&>();
    test_is_referenceable<void (class_type::*)(...) const>();
    test_is_referenceable<void (class_type::*)(...) const&>();
    test_is_referenceable<void (class_type::*)(...) const&&>();
    test_is_referenceable<void (class_type::*)(...) noexcept>();
    test_is_referenceable<void (class_type::*)(...) & noexcept>();
    test_is_referenceable<void (class_type::*)(...) && noexcept>();
    test_is_referenceable<void (class_type::*)(...) const noexcept>();
    test_is_referenceable<void (class_type::*)(...) const & noexcept>();
    test_is_referenceable<void (class_type::*)(...) const && noexcept>();

    test_is_referenceable<void (class_type::*)(int, ...)>();
    test_is_referenceable<void (class_type::*)(int, ...)&>();
    test_is_referenceable<void (class_type::*)(int, ...) &&>();
    test_is_referenceable<void (class_type::*)(int, ...) const>();
    test_is_referenceable<void (class_type::*)(int, ...) const&>();
    test_is_referenceable<void (class_type::*)(int, ...) const&&>();
    test_is_referenceable<void (class_type::*)(int, ...) noexcept>();
    test_is_referenceable<void (class_type::*)(int, ...) & noexcept>();
    test_is_referenceable<void (class_type::*)(int, ...) && noexcept>();
    test_is_referenceable<void (class_type::*)(int, ...) const noexcept>();
    test_is_referenceable<void (class_type::*)(int, ...) const & noexcept>();
    test_is_referenceable<void (class_type::*)(int, ...) const && noexcept>();

    test_is_referenceable<int (class_type::*)()>();
    test_is_referenceable<int (class_type::*)()&>();
    test_is_referenceable<int (class_type::*)() &&>();
    test_is_referenceable<int (class_type::*)() const>();
    test_is_referenceable<int (class_type::*)() const&>();
    test_is_referenceable<int (class_type::*)() const&&>();
    test_is_referenceable<int (class_type::*)() noexcept>();
    test_is_referenceable<int (class_type::*)() & noexcept>();
    test_is_referenceable<int (class_type::*)() && noexcept>();
    test_is_referenceable<int (class_type::*)() const noexcept>();
    test_is_referenceable<int (class_type::*)() const & noexcept>();
    test_is_referenceable<int (class_type::*)() const && noexcept>();

    test_is_referenceable<int (class_type::*)(int)>();
    test_is_referenceable<int (class_type::*)(int)&>();
    test_is_referenceable<int (class_type::*)(int) &&>();
    test_is_referenceable<int (class_type::*)(int) const>();
    test_is_referenceable<int (class_type::*)(int) const&>();
    test_is_referenceable<int (class_type::*)(int) const&&>();
    test_is_referenceable<int (class_type::*)(int) noexcept>();
    test_is_referenceable<int (class_type::*)(int) & noexcept>();
    test_is_referenceable<int (class_type::*)(int) && noexcept>();
    test_is_referenceable<int (class_type::*)(int) const noexcept>();
    test_is_referenceable<int (class_type::*)(int) const & noexcept>();
    test_is_referenceable<int (class_type::*)(int) const && noexcept>();

    test_is_referenceable<int (class_type::*)(...)>();
    test_is_referenceable<int (class_type::*)(...)&>();
    test_is_referenceable<int (class_type::*)(...) &&>();
    test_is_referenceable<int (class_type::*)(...) const>();
    test_is_referenceable<int (class_type::*)(...) const&>();
    test_is_referenceable<int (class_type::*)(...) const&&>();
    test_is_referenceable<int (class_type::*)(...) noexcept>();
    test_is_referenceable<int (class_type::*)(...) & noexcept>();
    test_is_referenceable<int (class_type::*)(...) && noexcept>();
    test_is_referenceable<int (class_type::*)(...) const noexcept>();
    test_is_referenceable<int (class_type::*)(...) const & noexcept>();
    test_is_referenceable<int (class_type::*)(...) const && noexcept>();

    test_is_referenceable<int (class_type::*)(int, ...)>();
    test_is_referenceable<int (class_type::*)(int, ...)&>();
    test_is_referenceable<int (class_type::*)(int, ...) &&>();
    test_is_referenceable<int (class_type::*)(int, ...) const>();
    test_is_referenceable<int (class_type::*)(int, ...) const&>();
    test_is_referenceable<int (class_type::*)(int, ...) const&&>();
    test_is_referenceable<int (class_type::*)(int, ...) noexcept>();
    test_is_referenceable<int (class_type::*)(int, ...) & noexcept>();
    test_is_referenceable<int (class_type::*)(int, ...) && noexcept>();
    test_is_referenceable<int (class_type::*)(int, ...) const noexcept>();
    test_is_referenceable<int (class_type::*)(int, ...) const & noexcept>();
    test_is_referenceable<int (class_type::*)(int, ...) const && noexcept>();
}
