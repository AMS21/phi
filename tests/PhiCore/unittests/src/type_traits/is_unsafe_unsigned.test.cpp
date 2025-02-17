#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_unsafe_unsigned.hpp>
#include <vector>

template <typename TypeT>
void test_is_unsafe_unsigned_impl()
{
    STATIC_REQUIRE(phi::is_unsafe_unsigned<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_unsafe_unsigned<TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_unsafe_unsigned_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_not_unsafe_unsigned_v<TypeT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_unsafe_unsigned<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_unsafe_unsigned<TypeT>);
}

template <typename TypeT>
void test_is_not_unsafe_unsigned_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_unsafe_unsigned<TypeT>::value);
    STATIC_REQUIRE(phi::is_not_unsafe_unsigned<TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_unsafe_unsigned_v<TypeT>);
    STATIC_REQUIRE(phi::is_not_unsafe_unsigned_v<TypeT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_unsafe_unsigned<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_unsafe_unsigned<TypeT>);
}

template <typename TypeT>
void test_is_unsafe_unsigned()
{
    test_is_unsafe_unsigned_impl<TypeT>();
    test_is_unsafe_unsigned_impl<const TypeT>();
    test_is_unsafe_unsigned_impl<volatile TypeT>();
    test_is_unsafe_unsigned_impl<const volatile TypeT>();
}

template <typename TypeT>
void test_is_not_unsafe_unsigned()
{
    test_is_not_unsafe_unsigned_impl<TypeT>();
    test_is_not_unsafe_unsigned_impl<const TypeT>();
    test_is_not_unsafe_unsigned_impl<volatile TypeT>();
    test_is_not_unsafe_unsigned_impl<const volatile TypeT>();
}

TEST_CASE("is_unsafe_unsigned")
{
    test_is_not_unsafe_unsigned<void>();
    test_is_not_unsafe_unsigned<phi::nullptr_t>();
    test_is_unsafe_unsigned<bool>();
    //test_is_not_unsafe_unsigned<char>();
    test_is_not_unsafe_unsigned<signed char>();
    test_is_unsafe_unsigned<unsigned char>();
    test_is_not_unsafe_unsigned<short>();
    test_is_unsafe_unsigned<unsigned short>();
    test_is_not_unsafe_unsigned<int>();
    test_is_unsafe_unsigned<unsigned int>();
    test_is_not_unsafe_unsigned<long>();
    test_is_unsafe_unsigned<unsigned long>();
    test_is_not_unsafe_unsigned<long long>();
    test_is_unsafe_unsigned<unsigned long long>();
    test_is_not_unsafe_unsigned<float>();
    test_is_not_unsafe_unsigned<double>();
    test_is_not_unsafe_unsigned<long double>();
#if PHI_HAS_FEATURE_CHAR8_T()
    test_is_unsafe_unsigned<char8_t>();
#endif
    test_is_unsafe_unsigned<char16_t>();
    test_is_unsafe_unsigned<char32_t>();
#if PHI_PLATFORM_IS(WINDOWS)
    test_is_unsafe_unsigned<wchar_t>();
#else
    test_is_not_unsafe_unsigned<wchar_t>();
#endif

    test_is_not_unsafe_unsigned<phi::boolean>();
    test_is_not_unsafe_unsigned<phi::integer<signed char>>();
    test_is_not_unsafe_unsigned<phi::integer<unsigned char>>();
    test_is_not_unsafe_unsigned<phi::integer<short>>();
    test_is_not_unsafe_unsigned<phi::integer<unsigned short>>();
    test_is_not_unsafe_unsigned<phi::integer<int>>();
    test_is_not_unsafe_unsigned<phi::integer<unsigned int>>();
    test_is_not_unsafe_unsigned<phi::integer<long>>();
    test_is_not_unsafe_unsigned<phi::integer<unsigned long>>();
    test_is_not_unsafe_unsigned<phi::integer<long long>>();
    test_is_not_unsafe_unsigned<phi::integer<unsigned long long>>();
    test_is_not_unsafe_unsigned<phi::floating_point<float>>();
    test_is_not_unsafe_unsigned<phi::floating_point<double>>();
    test_is_not_unsafe_unsigned<phi::floating_point<long double>>();

    test_is_not_unsafe_unsigned<std::vector<int>>();
    test_is_not_unsafe_unsigned<phi::scope_ptr<int>>();

    test_is_not_unsafe_unsigned<int&>();
    test_is_not_unsafe_unsigned<const int&>();
    test_is_not_unsafe_unsigned<volatile int&>();
    test_is_not_unsafe_unsigned<const volatile int&>();
    test_is_not_unsafe_unsigned<int&&>();
    test_is_not_unsafe_unsigned<const int&&>();
    test_is_not_unsafe_unsigned<volatile int&&>();
    test_is_not_unsafe_unsigned<const volatile int&&>();
    test_is_not_unsafe_unsigned<int*>();
    test_is_not_unsafe_unsigned<const int*>();
    test_is_not_unsafe_unsigned<volatile int*>();
    test_is_not_unsafe_unsigned<const volatile int*>();
    test_is_not_unsafe_unsigned<int**>();
    test_is_not_unsafe_unsigned<const int**>();
    test_is_not_unsafe_unsigned<volatile int**>();
    test_is_not_unsafe_unsigned<const volatile int**>();
    test_is_not_unsafe_unsigned<int*&>();
    test_is_not_unsafe_unsigned<const int*&>();
    test_is_not_unsafe_unsigned<volatile int*&>();
    test_is_not_unsafe_unsigned<const volatile int*&>();
    test_is_not_unsafe_unsigned<int*&&>();
    test_is_not_unsafe_unsigned<const int*&&>();
    test_is_not_unsafe_unsigned<volatile int*&&>();
    test_is_not_unsafe_unsigned<const volatile int*&&>();
    test_is_not_unsafe_unsigned<void*>();
    test_is_not_unsafe_unsigned<char[3]>();
    test_is_not_unsafe_unsigned<char[]>();
    test_is_not_unsafe_unsigned<char* [3]>();
    test_is_not_unsafe_unsigned<char*[]>();
    test_is_not_unsafe_unsigned<int(*)[3]>();
    test_is_not_unsafe_unsigned<int(*)[]>();
    test_is_not_unsafe_unsigned<int(&)[3]>();
    test_is_not_unsafe_unsigned<int(&)[]>();
    test_is_not_unsafe_unsigned<int(&&)[3]>();
    test_is_not_unsafe_unsigned<int(&&)[]>();
    test_is_not_unsafe_unsigned<char[3][2]>();
    test_is_not_unsafe_unsigned<char[][2]>();
    test_is_not_unsafe_unsigned<char* [3][2]>();
    test_is_not_unsafe_unsigned<char*[][2]>();
    test_is_not_unsafe_unsigned<int(*)[3][2]>();
    test_is_not_unsafe_unsigned<int(*)[][2]>();
    test_is_not_unsafe_unsigned<int(&)[3][2]>();
    test_is_not_unsafe_unsigned<int(&)[][2]>();
    test_is_not_unsafe_unsigned<int(&&)[3][2]>();
    test_is_not_unsafe_unsigned<int(&&)[][2]>();
    test_is_not_unsafe_unsigned<class_type>();
    test_is_not_unsafe_unsigned<class_type[]>();
    test_is_not_unsafe_unsigned<class_type[2]>();
    test_is_not_unsafe_unsigned<template_type<void>>();
    test_is_not_unsafe_unsigned<template_type<int>>();
    test_is_not_unsafe_unsigned<template_type<class_type>>();
    test_is_not_unsafe_unsigned<template_type<incomplete_type>>();
    test_is_not_unsafe_unsigned<variadic_template<>>();
    test_is_not_unsafe_unsigned<variadic_template<void>>();
    test_is_not_unsafe_unsigned<variadic_template<int>>();
    test_is_not_unsafe_unsigned<variadic_template<class_type>>();
    test_is_not_unsafe_unsigned<variadic_template<incomplete_type>>();
    test_is_not_unsafe_unsigned<variadic_template<int, void, class_type, volatile char[]>>();
    test_is_not_unsafe_unsigned<public_derived_from<base>>();
    test_is_not_unsafe_unsigned<public_derived_from<derived>>();
    test_is_not_unsafe_unsigned<public_derived_from<class_type>>();
    test_is_not_unsafe_unsigned<private_derived_from<base>>();
    test_is_not_unsafe_unsigned<private_derived_from<derived>>();
    test_is_not_unsafe_unsigned<private_derived_from<class_type>>();
    test_is_not_unsafe_unsigned<protected_derived_from<base>>();
    test_is_not_unsafe_unsigned<protected_derived_from<derived>>();
    test_is_not_unsafe_unsigned<protected_derived_from<class_type>>();
    test_is_not_unsafe_unsigned<virtual_derived_from<base>>();
    test_is_not_unsafe_unsigned<virtual_derived_from<derived>>();
    test_is_not_unsafe_unsigned<virtual_derived_from<class_type>>();
    test_is_not_unsafe_unsigned<union_type>();
    test_is_not_unsafe_unsigned<non_empty_union>();
    test_is_not_unsafe_unsigned<non_trivial_union>();
    test_is_not_unsafe_unsigned<empty>();
    test_is_not_unsafe_unsigned<not_empty>();
    test_is_not_unsafe_unsigned<non_trivial>();
    test_is_not_unsafe_unsigned<bit_zero>();
    test_is_not_unsafe_unsigned<bit_one>();
    test_is_not_unsafe_unsigned<base>();
    test_is_not_unsafe_unsigned<derived>();
    test_is_not_unsafe_unsigned<polymorphic>();
    test_is_not_unsafe_unsigned<derived_polymorphic>();
    test_is_not_unsafe_unsigned<abstract>();
    test_is_not_unsafe_unsigned<public_abstract>();
    test_is_not_unsafe_unsigned<private_abstract>();
    test_is_not_unsafe_unsigned<protected_abstract>();
    test_is_not_unsafe_unsigned<abstract_template<int>>();
    test_is_not_unsafe_unsigned<abstract_template<double>>();
    test_is_not_unsafe_unsigned<abstract_template<class_type>>();
    test_is_not_unsafe_unsigned<abstract_template<incomplete_type>>();
    test_is_not_unsafe_unsigned<public_abstract_deleted_destructor>();
    test_is_not_unsafe_unsigned<protected_abstract_deleted_destructor>();
    test_is_not_unsafe_unsigned<private_abstract_deleted_destructor>();
    test_is_not_unsafe_unsigned<final_type>();
    test_is_not_unsafe_unsigned<final_derived>();
    test_is_not_unsafe_unsigned<public_destructor>();
    test_is_not_unsafe_unsigned<protected_destructor>();
    test_is_not_unsafe_unsigned<private_destructor>();
    test_is_not_unsafe_unsigned<virtual_public_destructor>();
    test_is_not_unsafe_unsigned<virtual_protected_destructor>();
    test_is_not_unsafe_unsigned<virtual_private_destructor>();
    test_is_not_unsafe_unsigned<pure_public_destructor>();
    test_is_not_unsafe_unsigned<pure_protected_destructor>();
    test_is_not_unsafe_unsigned<pure_private_destructor>();
    test_is_not_unsafe_unsigned<deleted_public_destructor>();
    test_is_not_unsafe_unsigned<deleted_protected_destructor>();
    test_is_not_unsafe_unsigned<deleted_private_destructor>();
    test_is_not_unsafe_unsigned<deleted_virtual_public_destructor>();
    test_is_not_unsafe_unsigned<deleted_virtual_protected_destructor>();
    test_is_not_unsafe_unsigned<deleted_virtual_private_destructor>();
    test_is_not_unsafe_unsigned<explicit_class>();
    test_is_not_unsafe_unsigned<nothrow_explicit_class>();
    test_is_not_unsafe_unsigned<throw_explicit_class>();
    test_is_not_unsafe_unsigned<throw_default_class>();
    test_is_not_unsafe_unsigned<throw_copy_constructible_class>();
    test_is_not_unsafe_unsigned<throw_move_constructible_class>();
    test_is_not_unsafe_unsigned<noexcept_explicit_class>();
    test_is_not_unsafe_unsigned<except_explicit_class>();
    test_is_not_unsafe_unsigned<noexcept_default_class>();
    test_is_not_unsafe_unsigned<except_default_class>();
    test_is_not_unsafe_unsigned<noexcept_copy_constructible_class>();
    test_is_not_unsafe_unsigned<except_copy_constructible_class>();
    test_is_not_unsafe_unsigned<noexcept_move_constructible_class>();
    test_is_not_unsafe_unsigned<except_move_constructible_class>();
    test_is_not_unsafe_unsigned<noexcept_copy_assign_class>();
    test_is_not_unsafe_unsigned<except_copy_assign_class>();
    test_is_not_unsafe_unsigned<noexcept_move_assign_class>();
    test_is_not_unsafe_unsigned<except_move_assign_class>();
    test_is_not_unsafe_unsigned<deleted_copy_assign_class>();
    test_is_not_unsafe_unsigned<deleted_move_assign_class>();
    test_is_not_unsafe_unsigned<noexcept_move_constructible_and_assignable_class>();
    test_is_not_unsafe_unsigned<except_move_constructible_noexcept_move_assign_class>();
    test_is_not_unsafe_unsigned<noexcept_move_constructible_except_move_assign_class>();
    test_is_not_unsafe_unsigned<except_move_constructible_and_assign_class>();
    test_is_not_unsafe_unsigned<implicit_to<int>>();
    test_is_not_unsafe_unsigned<implicit_to<float>>();
    test_is_not_unsafe_unsigned<implicit_to<class_type>>();
    test_is_not_unsafe_unsigned<deleted_implicit_to<int>>();
    test_is_not_unsafe_unsigned<deleted_implicit_to<float>>();
    test_is_not_unsafe_unsigned<deleted_implicit_to<class_type>>();
    test_is_not_unsafe_unsigned<explicit_to<int>>();
    test_is_not_unsafe_unsigned<explicit_to<float>>();
    test_is_not_unsafe_unsigned<explicit_to<class_type>>();
    test_is_not_unsafe_unsigned<deleted_explicit_to<int>>();
    test_is_not_unsafe_unsigned<deleted_explicit_to<float>>();
    test_is_not_unsafe_unsigned<deleted_explicit_to<class_type>>();
    test_is_not_unsafe_unsigned<ellipsis>();
    test_is_not_unsafe_unsigned<deleted_ellipsis>();
    test_is_not_unsafe_unsigned<copy_constructible_only_type>();
    test_is_not_unsafe_unsigned<move_constructible_only_type>();
    test_is_not_unsafe_unsigned<overloaded_operators>();
    test_is_not_unsafe_unsigned<public_int_member>();
    test_is_not_unsafe_unsigned<protected_int_member>();
    test_is_not_unsafe_unsigned<private_int_member>();
    test_is_not_unsafe_unsigned<public_static_int_member>();
    test_is_not_unsafe_unsigned<protected_static_int_member>();
    test_is_not_unsafe_unsigned<private_static_int_member>();
    test_is_not_unsafe_unsigned<public_template_member<int>>();
    test_is_not_unsafe_unsigned<public_template_member<float>>();
    test_is_not_unsafe_unsigned<public_template_member<class_type>>();
    test_is_not_unsafe_unsigned<protected_template_member<int>>();
    test_is_not_unsafe_unsigned<protected_template_member<float>>();
    test_is_not_unsafe_unsigned<protected_template_member<class_type>>();
    test_is_not_unsafe_unsigned<private_template_member<int>>();
    test_is_not_unsafe_unsigned<private_template_member<float>>();
    test_is_not_unsafe_unsigned<private_template_member<class_type>>();
    test_is_not_unsafe_unsigned<public_static_template_member<int>>();
    test_is_not_unsafe_unsigned<public_static_template_member<float>>();
    test_is_not_unsafe_unsigned<public_static_template_member<class_type>>();
    test_is_not_unsafe_unsigned<protected_static_template_member<int>>();
    test_is_not_unsafe_unsigned<protected_static_template_member<float>>();
    test_is_not_unsafe_unsigned<protected_static_template_member<class_type>>();
    test_is_not_unsafe_unsigned<private_static_template_member<int>>();
    test_is_not_unsafe_unsigned<private_static_template_member<float>>();
    test_is_not_unsafe_unsigned<private_static_template_member<class_type>>();
    test_is_not_unsafe_unsigned<Enum>();
    test_is_not_unsafe_unsigned<EnumSigned>();
    test_is_not_unsafe_unsigned<EnumUnsigned>();
    test_is_not_unsafe_unsigned<EnumClass>();
    test_is_not_unsafe_unsigned<EnumStruct>();
    test_is_not_unsafe_unsigned<function_type>();
    test_is_not_unsafe_unsigned<function_ptr>();
    test_is_not_unsafe_unsigned<member_object_ptr>();
    test_is_not_unsafe_unsigned<member_function_ptr>();
    test_is_not_unsafe_unsigned<lambda_type>();
    test_is_not_unsafe_unsigned<lambda_noexcept_type>();
    test_is_not_unsafe_unsigned<lambda_throws_type>();
    test_is_not_unsafe_unsigned<incomplete_type>();
    test_is_not_unsafe_unsigned<incomplete_template<void>>();
    test_is_not_unsafe_unsigned<incomplete_template<int>>();
    test_is_not_unsafe_unsigned<incomplete_template<class_type>>();
    test_is_not_unsafe_unsigned<incomplete_template<incomplete_type>>();
    test_is_not_unsafe_unsigned<incomplete_variadic_template<>>();
    test_is_not_unsafe_unsigned<incomplete_variadic_template<void>>();
    test_is_not_unsafe_unsigned<incomplete_variadic_template<int>>();
    test_is_not_unsafe_unsigned<incomplete_variadic_template<class_type>>();
    test_is_not_unsafe_unsigned<incomplete_variadic_template<incomplete_type>>();
    test_is_not_unsafe_unsigned<
            incomplete_variadic_template<int, void, class_type, volatile char[]>>();
    test_is_not_unsafe_unsigned<incomplete_union>();
    test_is_not_unsafe_unsigned<IncompleteEnumSigned>();
    test_is_not_unsafe_unsigned<IncompleteEnumUnsigned>();
    test_is_not_unsafe_unsigned<IncompleteEnumClass>();
    test_is_not_unsafe_unsigned<IncompleteEnumStruct>();
    test_is_not_unsafe_unsigned<int class_type::*>();
    test_is_not_unsafe_unsigned<float class_type::*>();
    test_is_not_unsafe_unsigned<void * class_type::*>();
    test_is_not_unsafe_unsigned<int * class_type::*>();
    test_is_not_unsafe_unsigned<int class_type::*&>();
    test_is_not_unsafe_unsigned<float class_type::*&>();
    test_is_not_unsafe_unsigned<void * class_type::*&>();
    test_is_not_unsafe_unsigned<int * class_type::*&>();
    test_is_not_unsafe_unsigned<int class_type::*&&>();
    test_is_not_unsafe_unsigned<float class_type::*&&>();
    test_is_not_unsafe_unsigned<void * class_type::*&&>();
    test_is_not_unsafe_unsigned<int * class_type::*&&>();
    test_is_not_unsafe_unsigned<int class_type::* const>();
    test_is_not_unsafe_unsigned<float class_type::* const>();
    test_is_not_unsafe_unsigned<void * class_type::* const>();
    test_is_not_unsafe_unsigned<int class_type::* const&>();
    test_is_not_unsafe_unsigned<float class_type::* const&>();
    test_is_not_unsafe_unsigned<void * class_type::* const&>();
    test_is_not_unsafe_unsigned<int class_type::* const&&>();
    test_is_not_unsafe_unsigned<float class_type::* const&&>();
    test_is_not_unsafe_unsigned<void * class_type::* const&&>();
    test_is_not_unsafe_unsigned<int class_type::* volatile>();
    test_is_not_unsafe_unsigned<float class_type::* volatile>();
    test_is_not_unsafe_unsigned<void * class_type::* volatile>();
    test_is_not_unsafe_unsigned<int class_type::* volatile&>();
    test_is_not_unsafe_unsigned<float class_type::* volatile&>();
    test_is_not_unsafe_unsigned<void * class_type::* volatile&>();
    test_is_not_unsafe_unsigned<int class_type::* volatile&&>();
    test_is_not_unsafe_unsigned<float class_type::* volatile&&>();
    test_is_not_unsafe_unsigned<void * class_type::* volatile&&>();
    test_is_not_unsafe_unsigned<int class_type::* const volatile>();
    test_is_not_unsafe_unsigned<float class_type::* const volatile>();
    test_is_not_unsafe_unsigned<void * class_type::* const volatile>();
    test_is_not_unsafe_unsigned<int class_type::* const volatile&>();
    test_is_not_unsafe_unsigned<float class_type::* const volatile&>();
    test_is_not_unsafe_unsigned<void * class_type::* const volatile&>();
    test_is_not_unsafe_unsigned<int class_type::* const volatile&&>();
    test_is_not_unsafe_unsigned<float class_type::* const volatile&&>();
    test_is_not_unsafe_unsigned<void * class_type::* const volatile&&>();
    test_is_not_unsafe_unsigned<non_copyable>();
    test_is_not_unsafe_unsigned<non_moveable>();
    test_is_not_unsafe_unsigned<non_constructible>();
    test_is_not_unsafe_unsigned<non_destructible>();
    test_is_not_unsafe_unsigned<tracked>();
    test_is_not_unsafe_unsigned<trap_constructible>();
    test_is_not_unsafe_unsigned<trap_implicit_conversion>();
    test_is_not_unsafe_unsigned<trap_comma>();
    test_is_not_unsafe_unsigned<trap_call>();
    test_is_not_unsafe_unsigned<trap_self_assign>();
    test_is_not_unsafe_unsigned<trap_deref>();
    test_is_not_unsafe_unsigned<trap_array_subscript>();

    test_is_not_unsafe_unsigned<void()>();
    test_is_not_unsafe_unsigned<void()&>();
    test_is_not_unsafe_unsigned<void() &&>();
    test_is_not_unsafe_unsigned<void() const>();
    test_is_not_unsafe_unsigned<void() const&>();
    test_is_not_unsafe_unsigned<void() const&&>();
    test_is_not_unsafe_unsigned<void() volatile>();
    test_is_not_unsafe_unsigned<void() volatile&>();
    test_is_not_unsafe_unsigned<void() volatile&&>();
    test_is_not_unsafe_unsigned<void() const volatile>();
    test_is_not_unsafe_unsigned<void() const volatile&>();
    test_is_not_unsafe_unsigned<void() const volatile&&>();
    test_is_not_unsafe_unsigned<void() noexcept>();
    test_is_not_unsafe_unsigned<void() & noexcept>();
    test_is_not_unsafe_unsigned<void() && noexcept>();
    test_is_not_unsafe_unsigned<void() const noexcept>();
    test_is_not_unsafe_unsigned<void() const & noexcept>();
    test_is_not_unsafe_unsigned<void() const && noexcept>();
    test_is_not_unsafe_unsigned<void() volatile noexcept>();
    test_is_not_unsafe_unsigned<void() volatile & noexcept>();
    test_is_not_unsafe_unsigned<void() volatile && noexcept>();
    test_is_not_unsafe_unsigned<void() const volatile noexcept>();
    test_is_not_unsafe_unsigned<void() const volatile & noexcept>();
    test_is_not_unsafe_unsigned<void() const volatile && noexcept>();

    test_is_not_unsafe_unsigned<void(int)>();
    test_is_not_unsafe_unsigned<void(int)&>();
    test_is_not_unsafe_unsigned<void(int) &&>();
    test_is_not_unsafe_unsigned<void(int) const>();
    test_is_not_unsafe_unsigned<void(int) const&>();
    test_is_not_unsafe_unsigned<void(int) const&&>();
    test_is_not_unsafe_unsigned<void(int) volatile>();
    test_is_not_unsafe_unsigned<void(int) volatile&>();
    test_is_not_unsafe_unsigned<void(int) volatile&&>();
    test_is_not_unsafe_unsigned<void(int) const volatile>();
    test_is_not_unsafe_unsigned<void(int) const volatile&>();
    test_is_not_unsafe_unsigned<void(int) const volatile&&>();
    test_is_not_unsafe_unsigned<void(int) noexcept>();
    test_is_not_unsafe_unsigned<void(int) & noexcept>();
    test_is_not_unsafe_unsigned<void(int) && noexcept>();
    test_is_not_unsafe_unsigned<void(int) const noexcept>();
    test_is_not_unsafe_unsigned<void(int) const & noexcept>();
    test_is_not_unsafe_unsigned<void(int) const && noexcept>();
    test_is_not_unsafe_unsigned<void(int) volatile noexcept>();
    test_is_not_unsafe_unsigned<void(int) volatile & noexcept>();
    test_is_not_unsafe_unsigned<void(int) volatile && noexcept>();
    test_is_not_unsafe_unsigned<void(int) const volatile noexcept>();
    test_is_not_unsafe_unsigned<void(int) const volatile & noexcept>();
    test_is_not_unsafe_unsigned<void(int) const volatile && noexcept>();

    test_is_not_unsafe_unsigned<void(...)>();
    test_is_not_unsafe_unsigned<void(...)&>();
    test_is_not_unsafe_unsigned<void(...) &&>();
    test_is_not_unsafe_unsigned<void(...) const>();
    test_is_not_unsafe_unsigned<void(...) const&>();
    test_is_not_unsafe_unsigned<void(...) const&&>();
    test_is_not_unsafe_unsigned<void(...) volatile>();
    test_is_not_unsafe_unsigned<void(...) volatile&>();
    test_is_not_unsafe_unsigned<void(...) volatile&&>();
    test_is_not_unsafe_unsigned<void(...) const volatile>();
    test_is_not_unsafe_unsigned<void(...) const volatile&>();
    test_is_not_unsafe_unsigned<void(...) const volatile&&>();
    test_is_not_unsafe_unsigned<void(...) noexcept>();
    test_is_not_unsafe_unsigned<void(...) & noexcept>();
    test_is_not_unsafe_unsigned<void(...) && noexcept>();
    test_is_not_unsafe_unsigned<void(...) const noexcept>();
    test_is_not_unsafe_unsigned<void(...) const & noexcept>();
    test_is_not_unsafe_unsigned<void(...) const && noexcept>();
    test_is_not_unsafe_unsigned<void(...) volatile noexcept>();
    test_is_not_unsafe_unsigned<void(...) volatile & noexcept>();
    test_is_not_unsafe_unsigned<void(...) volatile && noexcept>();
    test_is_not_unsafe_unsigned<void(...) const volatile noexcept>();
    test_is_not_unsafe_unsigned<void(...) const volatile & noexcept>();
    test_is_not_unsafe_unsigned<void(...) const volatile && noexcept>();

    test_is_not_unsafe_unsigned<void(int, ...)>();
    test_is_not_unsafe_unsigned<void(int, ...)&>();
    test_is_not_unsafe_unsigned<void(int, ...) &&>();
    test_is_not_unsafe_unsigned<void(int, ...) const>();
    test_is_not_unsafe_unsigned<void(int, ...) const&>();
    test_is_not_unsafe_unsigned<void(int, ...) const&&>();
    test_is_not_unsafe_unsigned<void(int, ...) volatile>();
    test_is_not_unsafe_unsigned<void(int, ...) volatile&>();
    test_is_not_unsafe_unsigned<void(int, ...) volatile&&>();
    test_is_not_unsafe_unsigned<void(int, ...) const volatile>();
    test_is_not_unsafe_unsigned<void(int, ...) const volatile&>();
    test_is_not_unsafe_unsigned<void(int, ...) const volatile&&>();
    test_is_not_unsafe_unsigned<void(int, ...) noexcept>();
    test_is_not_unsafe_unsigned<void(int, ...) & noexcept>();
    test_is_not_unsafe_unsigned<void(int, ...) && noexcept>();
    test_is_not_unsafe_unsigned<void(int, ...) const noexcept>();
    test_is_not_unsafe_unsigned<void(int, ...) const & noexcept>();
    test_is_not_unsafe_unsigned<void(int, ...) const && noexcept>();
    test_is_not_unsafe_unsigned<void(int, ...) volatile noexcept>();
    test_is_not_unsafe_unsigned<void(int, ...) volatile & noexcept>();
    test_is_not_unsafe_unsigned<void(int, ...) volatile && noexcept>();
    test_is_not_unsafe_unsigned<void(int, ...) const volatile noexcept>();
    test_is_not_unsafe_unsigned<void(int, ...) const volatile & noexcept>();
    test_is_not_unsafe_unsigned<void(int, ...) const volatile && noexcept>();

    test_is_not_unsafe_unsigned<int()>();
    test_is_not_unsafe_unsigned<int()&>();
    test_is_not_unsafe_unsigned<int() &&>();
    test_is_not_unsafe_unsigned<int() const>();
    test_is_not_unsafe_unsigned<int() const&>();
    test_is_not_unsafe_unsigned<int() const&&>();
    test_is_not_unsafe_unsigned<int() volatile>();
    test_is_not_unsafe_unsigned<int() volatile&>();
    test_is_not_unsafe_unsigned<int() volatile&&>();
    test_is_not_unsafe_unsigned<int() const volatile>();
    test_is_not_unsafe_unsigned<int() const volatile&>();
    test_is_not_unsafe_unsigned<int() const volatile&&>();
    test_is_not_unsafe_unsigned<int() noexcept>();
    test_is_not_unsafe_unsigned<int() & noexcept>();
    test_is_not_unsafe_unsigned<int() && noexcept>();
    test_is_not_unsafe_unsigned<int() const noexcept>();
    test_is_not_unsafe_unsigned<int() const & noexcept>();
    test_is_not_unsafe_unsigned<int() const && noexcept>();
    test_is_not_unsafe_unsigned<int() volatile noexcept>();
    test_is_not_unsafe_unsigned<int() volatile & noexcept>();
    test_is_not_unsafe_unsigned<int() volatile && noexcept>();
    test_is_not_unsafe_unsigned<int() const volatile noexcept>();
    test_is_not_unsafe_unsigned<int() const volatile & noexcept>();
    test_is_not_unsafe_unsigned<int() const volatile && noexcept>();

    test_is_not_unsafe_unsigned<int(int)>();
    test_is_not_unsafe_unsigned<int(int)&>();
    test_is_not_unsafe_unsigned<int(int) &&>();
    test_is_not_unsafe_unsigned<int(int) const>();
    test_is_not_unsafe_unsigned<int(int) const&>();
    test_is_not_unsafe_unsigned<int(int) const&&>();
    test_is_not_unsafe_unsigned<int(int) volatile>();
    test_is_not_unsafe_unsigned<int(int) volatile&>();
    test_is_not_unsafe_unsigned<int(int) volatile&&>();
    test_is_not_unsafe_unsigned<int(int) const volatile>();
    test_is_not_unsafe_unsigned<int(int) const volatile&>();
    test_is_not_unsafe_unsigned<int(int) const volatile&&>();
    test_is_not_unsafe_unsigned<int(int) noexcept>();
    test_is_not_unsafe_unsigned<int(int) & noexcept>();
    test_is_not_unsafe_unsigned<int(int) && noexcept>();
    test_is_not_unsafe_unsigned<int(int) const noexcept>();
    test_is_not_unsafe_unsigned<int(int) const & noexcept>();
    test_is_not_unsafe_unsigned<int(int) const && noexcept>();
    test_is_not_unsafe_unsigned<int(int) volatile noexcept>();
    test_is_not_unsafe_unsigned<int(int) volatile & noexcept>();
    test_is_not_unsafe_unsigned<int(int) volatile && noexcept>();
    test_is_not_unsafe_unsigned<int(int) const volatile noexcept>();
    test_is_not_unsafe_unsigned<int(int) const volatile & noexcept>();
    test_is_not_unsafe_unsigned<int(int) const volatile && noexcept>();

    test_is_not_unsafe_unsigned<int(...)>();
    test_is_not_unsafe_unsigned<int(...)&>();
    test_is_not_unsafe_unsigned<int(...) &&>();
    test_is_not_unsafe_unsigned<int(...) const>();
    test_is_not_unsafe_unsigned<int(...) const&>();
    test_is_not_unsafe_unsigned<int(...) const&&>();
    test_is_not_unsafe_unsigned<int(...) volatile>();
    test_is_not_unsafe_unsigned<int(...) volatile&>();
    test_is_not_unsafe_unsigned<int(...) volatile&&>();
    test_is_not_unsafe_unsigned<int(...) const volatile>();
    test_is_not_unsafe_unsigned<int(...) const volatile&>();
    test_is_not_unsafe_unsigned<int(...) const volatile&&>();
    test_is_not_unsafe_unsigned<int(...) noexcept>();
    test_is_not_unsafe_unsigned<int(...) & noexcept>();
    test_is_not_unsafe_unsigned<int(...) && noexcept>();
    test_is_not_unsafe_unsigned<int(...) const noexcept>();
    test_is_not_unsafe_unsigned<int(...) const & noexcept>();
    test_is_not_unsafe_unsigned<int(...) const && noexcept>();
    test_is_not_unsafe_unsigned<int(...) volatile noexcept>();
    test_is_not_unsafe_unsigned<int(...) volatile & noexcept>();
    test_is_not_unsafe_unsigned<int(...) volatile && noexcept>();
    test_is_not_unsafe_unsigned<int(...) const volatile noexcept>();
    test_is_not_unsafe_unsigned<int(...) const volatile & noexcept>();
    test_is_not_unsafe_unsigned<int(...) const volatile && noexcept>();

    test_is_not_unsafe_unsigned<int(int, ...)>();
    test_is_not_unsafe_unsigned<int(int, ...)&>();
    test_is_not_unsafe_unsigned<int(int, ...) &&>();
    test_is_not_unsafe_unsigned<int(int, ...) const>();
    test_is_not_unsafe_unsigned<int(int, ...) const&>();
    test_is_not_unsafe_unsigned<int(int, ...) const&&>();
    test_is_not_unsafe_unsigned<int(int, ...) volatile>();
    test_is_not_unsafe_unsigned<int(int, ...) volatile&>();
    test_is_not_unsafe_unsigned<int(int, ...) volatile&&>();
    test_is_not_unsafe_unsigned<int(int, ...) const volatile>();
    test_is_not_unsafe_unsigned<int(int, ...) const volatile&>();
    test_is_not_unsafe_unsigned<int(int, ...) const volatile&&>();
    test_is_not_unsafe_unsigned<int(int, ...) noexcept>();
    test_is_not_unsafe_unsigned<int(int, ...) & noexcept>();
    test_is_not_unsafe_unsigned<int(int, ...) && noexcept>();
    test_is_not_unsafe_unsigned<int(int, ...) const noexcept>();
    test_is_not_unsafe_unsigned<int(int, ...) const & noexcept>();
    test_is_not_unsafe_unsigned<int(int, ...) const && noexcept>();
    test_is_not_unsafe_unsigned<int(int, ...) volatile noexcept>();
    test_is_not_unsafe_unsigned<int(int, ...) volatile & noexcept>();
    test_is_not_unsafe_unsigned<int(int, ...) volatile && noexcept>();
    test_is_not_unsafe_unsigned<int(int, ...) const volatile noexcept>();
    test_is_not_unsafe_unsigned<int(int, ...) const volatile & noexcept>();
    test_is_not_unsafe_unsigned<int(int, ...) const volatile && noexcept>();

    test_is_not_unsafe_unsigned<void (*)()>();
    test_is_not_unsafe_unsigned<void (*)() noexcept>();

    test_is_not_unsafe_unsigned<void (*)(int)>();
    test_is_not_unsafe_unsigned<void (*)(int) noexcept>();

    test_is_not_unsafe_unsigned<void (*)(...)>();
    test_is_not_unsafe_unsigned<void (*)(...) noexcept>();

    test_is_not_unsafe_unsigned<void (*)(int, ...)>();
    test_is_not_unsafe_unsigned<void (*)(int, ...) noexcept>();

    test_is_not_unsafe_unsigned<int (*)()>();
    test_is_not_unsafe_unsigned<int (*)() noexcept>();

    test_is_not_unsafe_unsigned<int (*)(int)>();
    test_is_not_unsafe_unsigned<int (*)(int) noexcept>();

    test_is_not_unsafe_unsigned<int (*)(...)>();
    test_is_not_unsafe_unsigned<int (*)(...) noexcept>();

    test_is_not_unsafe_unsigned<int (*)(int, ...)>();
    test_is_not_unsafe_unsigned<int (*)(int, ...) noexcept>();

    test_is_not_unsafe_unsigned<void (&)()>();
    test_is_not_unsafe_unsigned<void (&)() noexcept>();

    test_is_not_unsafe_unsigned<void (&)(int)>();
    test_is_not_unsafe_unsigned<void (&)(int) noexcept>();

    test_is_not_unsafe_unsigned<void (&)(...)>();
    test_is_not_unsafe_unsigned<void (&)(...) noexcept>();

    test_is_not_unsafe_unsigned<void (&)(int, ...)>();
    test_is_not_unsafe_unsigned<void (&)(int, ...) noexcept>();

    test_is_not_unsafe_unsigned<int (&)()>();
    test_is_not_unsafe_unsigned<int (&)() noexcept>();

    test_is_not_unsafe_unsigned<int (&)(int)>();
    test_is_not_unsafe_unsigned<int (&)(int) noexcept>();

    test_is_not_unsafe_unsigned<int (&)(...)>();
    test_is_not_unsafe_unsigned<int (&)(...) noexcept>();

    test_is_not_unsafe_unsigned<int (&)(int, ...)>();
    test_is_not_unsafe_unsigned<int (&)(int, ...) noexcept>();

    test_is_not_unsafe_unsigned<void (&&)()>();
    test_is_not_unsafe_unsigned<void (&&)() noexcept>();

    test_is_not_unsafe_unsigned<void (&&)(int)>();
    test_is_not_unsafe_unsigned<void (&&)(int) noexcept>();

    test_is_not_unsafe_unsigned<void (&&)(...)>();
    test_is_not_unsafe_unsigned<void (&&)(...) noexcept>();

    test_is_not_unsafe_unsigned<void (&&)(int, ...)>();
    test_is_not_unsafe_unsigned<void (&&)(int, ...) noexcept>();

    test_is_not_unsafe_unsigned<int (&&)()>();
    test_is_not_unsafe_unsigned<int (&&)() noexcept>();

    test_is_not_unsafe_unsigned<int (&&)(int)>();
    test_is_not_unsafe_unsigned<int (&&)(int) noexcept>();

    test_is_not_unsafe_unsigned<int (&&)(...)>();
    test_is_not_unsafe_unsigned<int (&&)(...) noexcept>();

    test_is_not_unsafe_unsigned<int (&&)(int, ...)>();
    test_is_not_unsafe_unsigned<int (&&)(int, ...) noexcept>();

    test_is_not_unsafe_unsigned<void (class_type::*)()>();
    test_is_not_unsafe_unsigned<void (class_type::*)()&>();
    test_is_not_unsafe_unsigned<void (class_type::*)() &&>();
    test_is_not_unsafe_unsigned<void (class_type::*)() const>();
    test_is_not_unsafe_unsigned<void (class_type::*)() const&>();
    test_is_not_unsafe_unsigned<void (class_type::*)() const&&>();
    test_is_not_unsafe_unsigned<void (class_type::*)() noexcept>();
    test_is_not_unsafe_unsigned<void (class_type::*)() & noexcept>();
    test_is_not_unsafe_unsigned<void (class_type::*)() && noexcept>();
    test_is_not_unsafe_unsigned<void (class_type::*)() const noexcept>();
    test_is_not_unsafe_unsigned<void (class_type::*)() const & noexcept>();
    test_is_not_unsafe_unsigned<void (class_type::*)() const && noexcept>();

    test_is_not_unsafe_unsigned<void (class_type::*)(int)>();
    test_is_not_unsafe_unsigned<void (class_type::*)(int)&>();
    test_is_not_unsafe_unsigned<void (class_type::*)(int) &&>();
    test_is_not_unsafe_unsigned<void (class_type::*)(int) const>();
    test_is_not_unsafe_unsigned<void (class_type::*)(int) const&>();
    test_is_not_unsafe_unsigned<void (class_type::*)(int) const&&>();
    test_is_not_unsafe_unsigned<void (class_type::*)(int) noexcept>();
    test_is_not_unsafe_unsigned<void (class_type::*)(int) & noexcept>();
    test_is_not_unsafe_unsigned<void (class_type::*)(int) && noexcept>();
    test_is_not_unsafe_unsigned<void (class_type::*)(int) const noexcept>();
    test_is_not_unsafe_unsigned<void (class_type::*)(int) const & noexcept>();
    test_is_not_unsafe_unsigned<void (class_type::*)(int) const && noexcept>();

    test_is_not_unsafe_unsigned<void (class_type::*)(...)>();
    test_is_not_unsafe_unsigned<void (class_type::*)(...)&>();
    test_is_not_unsafe_unsigned<void (class_type::*)(...) &&>();
    test_is_not_unsafe_unsigned<void (class_type::*)(...) const>();
    test_is_not_unsafe_unsigned<void (class_type::*)(...) const&>();
    test_is_not_unsafe_unsigned<void (class_type::*)(...) const&&>();
    test_is_not_unsafe_unsigned<void (class_type::*)(...) noexcept>();
    test_is_not_unsafe_unsigned<void (class_type::*)(...) & noexcept>();
    test_is_not_unsafe_unsigned<void (class_type::*)(...) && noexcept>();
    test_is_not_unsafe_unsigned<void (class_type::*)(...) const noexcept>();
    test_is_not_unsafe_unsigned<void (class_type::*)(...) const & noexcept>();
    test_is_not_unsafe_unsigned<void (class_type::*)(...) const && noexcept>();

    test_is_not_unsafe_unsigned<void (class_type::*)(int, ...)>();
    test_is_not_unsafe_unsigned<void (class_type::*)(int, ...)&>();
    test_is_not_unsafe_unsigned<void (class_type::*)(int, ...) &&>();
    test_is_not_unsafe_unsigned<void (class_type::*)(int, ...) const>();
    test_is_not_unsafe_unsigned<void (class_type::*)(int, ...) const&>();
    test_is_not_unsafe_unsigned<void (class_type::*)(int, ...) const&&>();
    test_is_not_unsafe_unsigned<void (class_type::*)(int, ...) noexcept>();
    test_is_not_unsafe_unsigned<void (class_type::*)(int, ...) & noexcept>();
    test_is_not_unsafe_unsigned<void (class_type::*)(int, ...) && noexcept>();
    test_is_not_unsafe_unsigned<void (class_type::*)(int, ...) const noexcept>();
    test_is_not_unsafe_unsigned<void (class_type::*)(int, ...) const & noexcept>();
    test_is_not_unsafe_unsigned<void (class_type::*)(int, ...) const && noexcept>();

    test_is_not_unsafe_unsigned<int (class_type::*)()>();
    test_is_not_unsafe_unsigned<int (class_type::*)()&>();
    test_is_not_unsafe_unsigned<int (class_type::*)() &&>();
    test_is_not_unsafe_unsigned<int (class_type::*)() const>();
    test_is_not_unsafe_unsigned<int (class_type::*)() const&>();
    test_is_not_unsafe_unsigned<int (class_type::*)() const&&>();
    test_is_not_unsafe_unsigned<int (class_type::*)() noexcept>();
    test_is_not_unsafe_unsigned<int (class_type::*)() & noexcept>();
    test_is_not_unsafe_unsigned<int (class_type::*)() && noexcept>();
    test_is_not_unsafe_unsigned<int (class_type::*)() const noexcept>();
    test_is_not_unsafe_unsigned<int (class_type::*)() const & noexcept>();
    test_is_not_unsafe_unsigned<int (class_type::*)() const && noexcept>();

    test_is_not_unsafe_unsigned<int (class_type::*)(int)>();
    test_is_not_unsafe_unsigned<int (class_type::*)(int)&>();
    test_is_not_unsafe_unsigned<int (class_type::*)(int) &&>();
    test_is_not_unsafe_unsigned<int (class_type::*)(int) const>();
    test_is_not_unsafe_unsigned<int (class_type::*)(int) const&>();
    test_is_not_unsafe_unsigned<int (class_type::*)(int) const&&>();
    test_is_not_unsafe_unsigned<int (class_type::*)(int) noexcept>();
    test_is_not_unsafe_unsigned<int (class_type::*)(int) & noexcept>();
    test_is_not_unsafe_unsigned<int (class_type::*)(int) && noexcept>();
    test_is_not_unsafe_unsigned<int (class_type::*)(int) const noexcept>();
    test_is_not_unsafe_unsigned<int (class_type::*)(int) const & noexcept>();
    test_is_not_unsafe_unsigned<int (class_type::*)(int) const && noexcept>();

    test_is_not_unsafe_unsigned<int (class_type::*)(...)>();
    test_is_not_unsafe_unsigned<int (class_type::*)(...)&>();
    test_is_not_unsafe_unsigned<int (class_type::*)(...) &&>();
    test_is_not_unsafe_unsigned<int (class_type::*)(...) const>();
    test_is_not_unsafe_unsigned<int (class_type::*)(...) const&>();
    test_is_not_unsafe_unsigned<int (class_type::*)(...) const&&>();
    test_is_not_unsafe_unsigned<int (class_type::*)(...) noexcept>();
    test_is_not_unsafe_unsigned<int (class_type::*)(...) & noexcept>();
    test_is_not_unsafe_unsigned<int (class_type::*)(...) && noexcept>();
    test_is_not_unsafe_unsigned<int (class_type::*)(...) const noexcept>();
    test_is_not_unsafe_unsigned<int (class_type::*)(...) const & noexcept>();
    test_is_not_unsafe_unsigned<int (class_type::*)(...) const && noexcept>();

    test_is_not_unsafe_unsigned<int (class_type::*)(int, ...)>();
    test_is_not_unsafe_unsigned<int (class_type::*)(int, ...)&>();
    test_is_not_unsafe_unsigned<int (class_type::*)(int, ...) &&>();
    test_is_not_unsafe_unsigned<int (class_type::*)(int, ...) const>();
    test_is_not_unsafe_unsigned<int (class_type::*)(int, ...) const&>();
    test_is_not_unsafe_unsigned<int (class_type::*)(int, ...) const&&>();
    test_is_not_unsafe_unsigned<int (class_type::*)(int, ...) noexcept>();
    test_is_not_unsafe_unsigned<int (class_type::*)(int, ...) & noexcept>();
    test_is_not_unsafe_unsigned<int (class_type::*)(int, ...) && noexcept>();
    test_is_not_unsafe_unsigned<int (class_type::*)(int, ...) const noexcept>();
    test_is_not_unsafe_unsigned<int (class_type::*)(int, ...) const & noexcept>();
    test_is_not_unsafe_unsigned<int (class_type::*)(int, ...) const && noexcept>();
}
