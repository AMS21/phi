#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/bugs/msvc_10741077.hpp>
#include <phi/compiler_support/char8_t.hpp>
#include <phi/compiler_support/compiler.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_destructible.hpp>
#include <type_traits>
#include <vector>

template <typename TypeT>
void test_is_destructible_impl()
{
    STATIC_REQUIRE(phi::is_destructible<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_destructible<TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_destructible_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_not_destructible_v<TypeT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_destructible<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_destructible<TypeT>);

    // Standard compatibility
    STATIC_REQUIRE(std::is_destructible<TypeT>::value);
}

template <typename TypeT>
void test_is_destructible()
{
    test_is_destructible_impl<TypeT>();
    test_is_destructible_impl<const TypeT>();
    test_is_destructible_impl<volatile TypeT>();
    test_is_destructible_impl<const volatile TypeT>();
}

template <typename TypeT>
void test_is_not_destructible_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_destructible<TypeT>::value);
    STATIC_REQUIRE(phi::is_not_destructible<TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_destructible_v<TypeT>);
    STATIC_REQUIRE(phi::is_not_destructible_v<TypeT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_destructible<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_destructible<TypeT>);

    // Standard compatibility
    STATIC_REQUIRE_FALSE(std::is_destructible<TypeT>::value);
}

template <typename TypeT>
void test_is_not_destructible()
{
    test_is_not_destructible_impl<TypeT>();
    test_is_not_destructible_impl<const TypeT>();
    test_is_not_destructible_impl<volatile TypeT>();
    test_is_not_destructible_impl<const volatile TypeT>();
}

// NOLINTNEXTLINE(cppcoreguidelines-virtual-class-destructor)
class not_empty2
{
    // NOLINTNEXTLINE(modernize-use-equals-delete)
    virtual ~not_empty2();
};

struct A
{
    ~A();
};

TEST_CASE("is_destructible")
{
#if PHI_HAS_BUG_MSVC_10741077() && !PHI_SUPPORTS_IS_DESTRUCTIBLE()

    // NOTE: Skip MSVC versions which crash when compiling the no intrinsic version
    SKIP_CHECK();

#else

    test_is_destructible<A>();
    test_is_not_destructible<not_empty2>();

    test_is_not_destructible<void>();
    test_is_destructible<phi::nullptr_t>();
    test_is_destructible<bool>();
    test_is_destructible<char>();
    test_is_destructible<signed char>();
    test_is_destructible<unsigned char>();
    test_is_destructible<short>();
    test_is_destructible<unsigned short>();
    test_is_destructible<int>();
    test_is_destructible<unsigned int>();
    test_is_destructible<long>();
    test_is_destructible<unsigned long>();
    test_is_destructible<long long>();
    test_is_destructible<unsigned long long>();
    test_is_destructible<float>();
    test_is_destructible<double>();
    test_is_destructible<long double>();
    test_is_destructible<char8_t>();
    test_is_destructible<char16_t>();
    test_is_destructible<char32_t>();
    test_is_destructible<wchar_t>();

    test_is_destructible<phi::boolean>();
    test_is_destructible<phi::integer<signed char>>();
    test_is_destructible<phi::integer<unsigned char>>();
    test_is_destructible<phi::integer<short>>();
    test_is_destructible<phi::integer<unsigned short>>();
    test_is_destructible<phi::integer<int>>();
    test_is_destructible<phi::integer<unsigned int>>();
    test_is_destructible<phi::integer<long>>();
    test_is_destructible<phi::integer<unsigned long>>();
    test_is_destructible<phi::integer<long long>>();
    test_is_destructible<phi::integer<unsigned long long>>();
    test_is_destructible<phi::floating_point<float>>();
    test_is_destructible<phi::floating_point<double>>();
    test_is_destructible<phi::floating_point<long double>>();

    test_is_destructible<std::vector<int>>();
    test_is_destructible<phi::scope_ptr<int>>();

    test_is_destructible<int&>();
    test_is_destructible<const int&>();
    test_is_destructible<volatile int&>();
    test_is_destructible<const volatile int&>();
    test_is_destructible<int&&>();
    test_is_destructible<const int&&>();
    test_is_destructible<volatile int&&>();
    test_is_destructible<const volatile int&&>();
    test_is_destructible<int*>();
    test_is_destructible<const int*>();
    test_is_destructible<volatile int*>();
    test_is_destructible<const volatile int*>();
    test_is_destructible<int**>();
    test_is_destructible<const int**>();
    test_is_destructible<volatile int**>();
    test_is_destructible<const volatile int**>();
    test_is_destructible<int*&>();
    test_is_destructible<const int*&>();
    test_is_destructible<volatile int*&>();
    test_is_destructible<const volatile int*&>();
    test_is_destructible<int*&&>();
    test_is_destructible<const int*&&>();
    test_is_destructible<volatile int*&&>();
    test_is_destructible<const volatile int*&&>();
    test_is_destructible<void*>();
    test_is_destructible<char[3]>();
    test_is_not_destructible<char[]>();
    test_is_destructible<char* [3]>();
    test_is_not_destructible<char*[]>();
    test_is_destructible<int(*)[3]>();
    test_is_destructible<int(*)[]>();
    test_is_destructible<int(&)[3]>();
    test_is_destructible<int(&)[]>();
    test_is_destructible<int(&&)[3]>();
    test_is_destructible<int(&&)[]>();
    test_is_destructible<char[3][2]>();
    test_is_not_destructible<char[][2]>();
    test_is_destructible<char* [3][2]>();
    test_is_not_destructible<char*[][2]>();
    test_is_destructible<int(*)[3][2]>();
    test_is_destructible<int(*)[][2]>();
    test_is_destructible<int(&)[3][2]>();
    test_is_destructible<int(&)[][2]>();
    test_is_destructible<int(&&)[3][2]>();
    test_is_destructible<int(&&)[][2]>();
    test_is_destructible<class_type>();
    test_is_not_destructible<class_type[]>();
    test_is_destructible<class_type[2]>();
    test_is_destructible<template_type<void>>();
    test_is_destructible<template_type<int>>();
    test_is_destructible<template_type<class_type>>();
    test_is_destructible<template_type<incomplete_type>>();
    test_is_destructible<variadic_template<>>();
    test_is_destructible<variadic_template<void>>();
    test_is_destructible<variadic_template<int>>();
    test_is_destructible<variadic_template<class_type>>();
    test_is_destructible<variadic_template<incomplete_type>>();
    test_is_destructible<variadic_template<int, void, class_type, volatile char[]>>();
    test_is_destructible<public_derived_from<base>>();
    test_is_destructible<public_derived_from<derived>>();
    test_is_destructible<public_derived_from<class_type>>();
    test_is_destructible<private_derived_from<base>>();
    test_is_destructible<private_derived_from<derived>>();
    test_is_destructible<private_derived_from<class_type>>();
    test_is_destructible<protected_derived_from<base>>();
    test_is_destructible<protected_derived_from<derived>>();
    test_is_destructible<protected_derived_from<class_type>>();
    test_is_destructible<virtual_derived_from<base>>();
    test_is_destructible<virtual_derived_from<derived>>();
    test_is_destructible<virtual_derived_from<class_type>>();
    test_is_destructible<union_type>();
    test_is_destructible<non_empty_union>();
    test_is_not_destructible<non_trivial_union>();
    test_is_destructible<empty>();
    test_is_destructible<not_empty>();
    test_is_destructible<non_trivial>();
    test_is_destructible<bit_zero>();
    test_is_destructible<bit_one>();
    test_is_destructible<base>();
    test_is_destructible<derived>();
    test_is_destructible<non_empty_base>();
    test_is_destructible<empty_base>();
    test_is_destructible<virtual_base>();
    test_is_destructible<polymorphic>();
    test_is_destructible<derived_polymorphic>();
    test_is_not_destructible<abstract>();
    test_is_destructible<public_abstract>();
    test_is_destructible<private_abstract>();
    test_is_destructible<protected_abstract>();
    test_is_destructible<abstract_template<int>>();
    test_is_destructible<abstract_template<double>>();
    test_is_destructible<abstract_template<class_type>>();
    test_is_destructible<abstract_template<incomplete_type>>();
    test_is_not_destructible<public_abstract_deleted_destructor>();
    test_is_not_destructible<protected_abstract_deleted_destructor>();
    test_is_not_destructible<private_abstract_deleted_destructor>();
    test_is_destructible<final_type>();
    test_is_destructible<final_derived>();
    test_is_destructible<public_destructor>();
    test_is_not_destructible<protected_destructor>();
    test_is_not_destructible<private_destructor>();
    test_is_destructible<virtual_public_destructor>();
    test_is_not_destructible<virtual_protected_destructor>();
    test_is_not_destructible<virtual_private_destructor>();
    test_is_destructible<pure_public_destructor>();
    test_is_not_destructible<pure_protected_destructor>();
    test_is_not_destructible<pure_private_destructor>();
    test_is_not_destructible<deleted_public_destructor>();
    test_is_not_destructible<deleted_protected_destructor>();
    test_is_not_destructible<deleted_private_destructor>();
    test_is_not_destructible<deleted_virtual_public_destructor>();
    test_is_not_destructible<deleted_virtual_protected_destructor>();
    test_is_not_destructible<deleted_virtual_private_destructor>();
    test_is_destructible<explicit_class>();
    test_is_destructible<nothrow_explicit_class>();
    test_is_destructible<throw_explicit_class>();
    test_is_destructible<throw_default_class>();
    test_is_destructible<throw_copy_constructible_class>();
    test_is_destructible<throw_move_constructible_class>();
    test_is_destructible<throw_destructor>();
    test_is_destructible<noexcept_explicit_class>();
    test_is_destructible<except_explicit_class>();
    test_is_destructible<noexcept_default_class>();
    test_is_destructible<except_default_class>();
    test_is_destructible<noexcept_copy_constructible_class>();
    test_is_destructible<except_copy_constructible_class>();
    test_is_destructible<noexcept_move_constructible_class>();
    test_is_destructible<except_move_constructible_class>();
    test_is_destructible<noexcept_copy_assign_class>();
    test_is_destructible<except_copy_assign_class>();
    test_is_destructible<noexcept_move_assign_class>();
    test_is_destructible<except_move_assign_class>();
    test_is_destructible<deleted_copy_assign_class>();
    test_is_destructible<deleted_move_assign_class>();
    test_is_destructible<noexcept_move_constructible_and_assignable_class>();
    test_is_destructible<except_move_constructible_noexcept_move_assign_class>();
    test_is_destructible<noexcept_move_constructible_except_move_assign_class>();
    test_is_destructible<except_move_constructible_and_assign_class>();
    test_is_destructible<implicit_to<int>>();
    test_is_destructible<implicit_to<float>>();
    test_is_destructible<implicit_to<class_type>>();
    test_is_destructible<deleted_implicit_to<int>>();
    test_is_destructible<deleted_implicit_to<float>>();
    test_is_destructible<deleted_implicit_to<class_type>>();
    test_is_destructible<explicit_to<int>>();
    test_is_destructible<explicit_to<float>>();
    test_is_destructible<explicit_to<class_type>>();
    test_is_destructible<deleted_explicit_to<int>>();
    test_is_destructible<deleted_explicit_to<float>>();
    test_is_destructible<deleted_explicit_to<class_type>>();
    test_is_destructible<ellipsis>();
    test_is_destructible<deleted_ellipsis>();
    test_is_destructible<copy_constructible_only_type>();
    test_is_destructible<move_constructible_only_type>();
    test_is_destructible<overloaded_operators>();
    test_is_destructible<public_int_member>();
    test_is_destructible<protected_int_member>();
    test_is_destructible<private_int_member>();
    test_is_destructible<public_static_int_member>();
    test_is_destructible<protected_static_int_member>();
    test_is_destructible<private_static_int_member>();
    test_is_destructible<public_template_member<int>>();
    test_is_destructible<public_template_member<float>>();
    test_is_destructible<public_template_member<class_type>>();
    test_is_destructible<protected_template_member<int>>();
    test_is_destructible<protected_template_member<float>>();
    test_is_destructible<protected_template_member<class_type>>();
    test_is_destructible<private_template_member<int>>();
    test_is_destructible<private_template_member<float>>();
    test_is_destructible<private_template_member<class_type>>();
    test_is_destructible<public_static_template_member<int>>();
    test_is_destructible<public_static_template_member<float>>();
    test_is_destructible<public_static_template_member<class_type>>();
    test_is_destructible<protected_static_template_member<int>>();
    test_is_destructible<protected_static_template_member<float>>();
    test_is_destructible<protected_static_template_member<class_type>>();
    test_is_destructible<private_static_template_member<int>>();
    test_is_destructible<private_static_template_member<float>>();
    test_is_destructible<private_static_template_member<class_type>>();
    test_is_destructible<natural_alignment>();
    test_is_destructible<Enum>();
    test_is_destructible<EnumSigned>();
    test_is_destructible<EnumUnsigned>();
    test_is_destructible<EnumClass>();
    test_is_destructible<EnumStruct>();
    test_is_not_destructible<function_type>();
    test_is_destructible<function_ptr>();
    test_is_destructible<member_object_ptr>();
    test_is_destructible<member_function_ptr>();
    test_is_destructible<lambda_type>();
    test_is_destructible<lambda_noexcept_type>();
    test_is_destructible<lambda_throws_type>();
    test_is_destructible<IncompleteEnumSigned>();
    test_is_destructible<IncompleteEnumUnsigned>();
    test_is_destructible<IncompleteEnumClass>();
    test_is_destructible<IncompleteEnumStruct>();
    test_is_destructible<int class_type::*>();
    test_is_destructible<float class_type::*>();
    test_is_destructible<void * class_type::*>();
    test_is_destructible<int * class_type::*>();
    test_is_destructible<Enum class_type::*>();
    test_is_destructible<not_empty class_type::*>();
    test_is_destructible<int class_type::*&>();
    test_is_destructible<float class_type::*&>();
    test_is_destructible<void * class_type::*&>();
    test_is_destructible<int * class_type::*&>();
    test_is_destructible<Enum class_type::*&>();
    test_is_destructible<not_empty class_type::*&>();
    test_is_destructible<int class_type::*&&>();
    test_is_destructible<float class_type::*&&>();
    test_is_destructible<void * class_type::*&&>();
    test_is_destructible<int * class_type::*&&>();
    test_is_destructible<Enum class_type::*&&>();
    test_is_destructible<not_empty class_type::*&&>();
    test_is_destructible<non_default_constructible>();
    test_is_destructible<non_copy_constructible>();
    test_is_destructible<non_move_constructible>();
    test_is_destructible<non_copy_assignable>();
    test_is_destructible<non_move_assignable>();
    test_is_destructible<non_assignable>();
    test_is_destructible<non_copyable>();
    test_is_destructible<non_moveable>();
    test_is_destructible<non_constructible>();
    test_is_not_destructible<non_destructible>();
    test_is_destructible<tracked>();
    test_is_destructible<trap_constructible>();
    test_is_destructible<trap_implicit_conversion>();
    test_is_destructible<trap_comma>();
    test_is_destructible<trap_call>();
    test_is_destructible<trap_self_assign>();
    test_is_destructible<trap_deref>();
    test_is_destructible<trap_array_subscript>();

    test_is_not_destructible<void()>();
    test_is_not_destructible<void()&>();
    test_is_not_destructible<void() &&>();
    test_is_not_destructible<void() const>();
    test_is_not_destructible<void() const&>();
    test_is_not_destructible<void() const&&>();
    test_is_not_destructible<void() volatile>();
    test_is_not_destructible<void() volatile&>();
    test_is_not_destructible<void() volatile&&>();
    test_is_not_destructible<void() const volatile>();
    test_is_not_destructible<void() const volatile&>();
    test_is_not_destructible<void() const volatile&&>();
    test_is_not_destructible<void() noexcept>();
    test_is_not_destructible<void() & noexcept>();
    test_is_not_destructible<void() && noexcept>();
    test_is_not_destructible<void() const noexcept>();
    test_is_not_destructible<void() const & noexcept>();
    test_is_not_destructible<void() const && noexcept>();
    test_is_not_destructible<void() volatile noexcept>();
    test_is_not_destructible<void() volatile & noexcept>();
    test_is_not_destructible<void() volatile && noexcept>();
    test_is_not_destructible<void() const volatile noexcept>();
    test_is_not_destructible<void() const volatile & noexcept>();
    test_is_not_destructible<void() const volatile && noexcept>();

    test_is_not_destructible<void(int)>();
    test_is_not_destructible<void(int)&>();
    test_is_not_destructible<void(int) &&>();
    test_is_not_destructible<void(int) const>();
    test_is_not_destructible<void(int) const&>();
    test_is_not_destructible<void(int) const&&>();
    test_is_not_destructible<void(int) volatile>();
    test_is_not_destructible<void(int) volatile&>();
    test_is_not_destructible<void(int) volatile&&>();
    test_is_not_destructible<void(int) const volatile>();
    test_is_not_destructible<void(int) const volatile&>();
    test_is_not_destructible<void(int) const volatile&&>();
    test_is_not_destructible<void(int) noexcept>();
    test_is_not_destructible<void(int) & noexcept>();
    test_is_not_destructible<void(int) && noexcept>();
    test_is_not_destructible<void(int) const noexcept>();
    test_is_not_destructible<void(int) const & noexcept>();
    test_is_not_destructible<void(int) const && noexcept>();
    test_is_not_destructible<void(int) volatile noexcept>();
    test_is_not_destructible<void(int) volatile & noexcept>();
    test_is_not_destructible<void(int) volatile && noexcept>();
    test_is_not_destructible<void(int) const volatile noexcept>();
    test_is_not_destructible<void(int) const volatile & noexcept>();
    test_is_not_destructible<void(int) const volatile && noexcept>();

    test_is_not_destructible<void(...)>();
    test_is_not_destructible<void(...)&>();
    test_is_not_destructible<void(...) &&>();
    test_is_not_destructible<void(...) const>();
    test_is_not_destructible<void(...) const&>();
    test_is_not_destructible<void(...) const&&>();
    test_is_not_destructible<void(...) volatile>();
    test_is_not_destructible<void(...) volatile&>();
    test_is_not_destructible<void(...) volatile&&>();
    test_is_not_destructible<void(...) const volatile>();
    test_is_not_destructible<void(...) const volatile&>();
    test_is_not_destructible<void(...) const volatile&&>();
    test_is_not_destructible<void(...) noexcept>();
    test_is_not_destructible<void(...) & noexcept>();
    test_is_not_destructible<void(...) && noexcept>();
    test_is_not_destructible<void(...) const noexcept>();
    test_is_not_destructible<void(...) const & noexcept>();
    test_is_not_destructible<void(...) const && noexcept>();
    test_is_not_destructible<void(...) volatile noexcept>();
    test_is_not_destructible<void(...) volatile & noexcept>();
    test_is_not_destructible<void(...) volatile && noexcept>();
    test_is_not_destructible<void(...) const volatile noexcept>();
    test_is_not_destructible<void(...) const volatile & noexcept>();
    test_is_not_destructible<void(...) const volatile && noexcept>();

    test_is_not_destructible<void(int, ...)>();
    test_is_not_destructible<void(int, ...)&>();
    test_is_not_destructible<void(int, ...) &&>();
    test_is_not_destructible<void(int, ...) const>();
    test_is_not_destructible<void(int, ...) const&>();
    test_is_not_destructible<void(int, ...) const&&>();
    test_is_not_destructible<void(int, ...) volatile>();
    test_is_not_destructible<void(int, ...) volatile&>();
    test_is_not_destructible<void(int, ...) volatile&&>();
    test_is_not_destructible<void(int, ...) const volatile>();
    test_is_not_destructible<void(int, ...) const volatile&>();
    test_is_not_destructible<void(int, ...) const volatile&&>();
    test_is_not_destructible<void(int, ...) noexcept>();
    test_is_not_destructible<void(int, ...) & noexcept>();
    test_is_not_destructible<void(int, ...) && noexcept>();
    test_is_not_destructible<void(int, ...) const noexcept>();
    test_is_not_destructible<void(int, ...) const & noexcept>();
    test_is_not_destructible<void(int, ...) const && noexcept>();
    test_is_not_destructible<void(int, ...) volatile noexcept>();
    test_is_not_destructible<void(int, ...) volatile & noexcept>();
    test_is_not_destructible<void(int, ...) volatile && noexcept>();
    test_is_not_destructible<void(int, ...) const volatile noexcept>();
    test_is_not_destructible<void(int, ...) const volatile & noexcept>();
    test_is_not_destructible<void(int, ...) const volatile && noexcept>();

    test_is_not_destructible<int()>();
    test_is_not_destructible<int()&>();
    test_is_not_destructible<int() &&>();
    test_is_not_destructible<int() const>();
    test_is_not_destructible<int() const&>();
    test_is_not_destructible<int() const&&>();
    test_is_not_destructible<int() volatile>();
    test_is_not_destructible<int() volatile&>();
    test_is_not_destructible<int() volatile&&>();
    test_is_not_destructible<int() const volatile>();
    test_is_not_destructible<int() const volatile&>();
    test_is_not_destructible<int() const volatile&&>();
    test_is_not_destructible<int() noexcept>();
    test_is_not_destructible<int() & noexcept>();
    test_is_not_destructible<int() && noexcept>();
    test_is_not_destructible<int() const noexcept>();
    test_is_not_destructible<int() const & noexcept>();
    test_is_not_destructible<int() const && noexcept>();
    test_is_not_destructible<int() volatile noexcept>();
    test_is_not_destructible<int() volatile & noexcept>();
    test_is_not_destructible<int() volatile && noexcept>();
    test_is_not_destructible<int() const volatile noexcept>();
    test_is_not_destructible<int() const volatile & noexcept>();
    test_is_not_destructible<int() const volatile && noexcept>();

    test_is_not_destructible<int(int)>();
    test_is_not_destructible<int(int)&>();
    test_is_not_destructible<int(int) &&>();
    test_is_not_destructible<int(int) const>();
    test_is_not_destructible<int(int) const&>();
    test_is_not_destructible<int(int) const&&>();
    test_is_not_destructible<int(int) volatile>();
    test_is_not_destructible<int(int) volatile&>();
    test_is_not_destructible<int(int) volatile&&>();
    test_is_not_destructible<int(int) const volatile>();
    test_is_not_destructible<int(int) const volatile&>();
    test_is_not_destructible<int(int) const volatile&&>();
    test_is_not_destructible<int(int) noexcept>();
    test_is_not_destructible<int(int) & noexcept>();
    test_is_not_destructible<int(int) && noexcept>();
    test_is_not_destructible<int(int) const noexcept>();
    test_is_not_destructible<int(int) const & noexcept>();
    test_is_not_destructible<int(int) const && noexcept>();
    test_is_not_destructible<int(int) volatile noexcept>();
    test_is_not_destructible<int(int) volatile & noexcept>();
    test_is_not_destructible<int(int) volatile && noexcept>();
    test_is_not_destructible<int(int) const volatile noexcept>();
    test_is_not_destructible<int(int) const volatile & noexcept>();
    test_is_not_destructible<int(int) const volatile && noexcept>();

    test_is_not_destructible<int(...)>();
    test_is_not_destructible<int(...)&>();
    test_is_not_destructible<int(...) &&>();
    test_is_not_destructible<int(...) const>();
    test_is_not_destructible<int(...) const&>();
    test_is_not_destructible<int(...) const&&>();
    test_is_not_destructible<int(...) volatile>();
    test_is_not_destructible<int(...) volatile&>();
    test_is_not_destructible<int(...) volatile&&>();
    test_is_not_destructible<int(...) const volatile>();
    test_is_not_destructible<int(...) const volatile&>();
    test_is_not_destructible<int(...) const volatile&&>();
    test_is_not_destructible<int(...) noexcept>();
    test_is_not_destructible<int(...) & noexcept>();
    test_is_not_destructible<int(...) && noexcept>();
    test_is_not_destructible<int(...) const noexcept>();
    test_is_not_destructible<int(...) const & noexcept>();
    test_is_not_destructible<int(...) const && noexcept>();
    test_is_not_destructible<int(...) volatile noexcept>();
    test_is_not_destructible<int(...) volatile & noexcept>();
    test_is_not_destructible<int(...) volatile && noexcept>();
    test_is_not_destructible<int(...) const volatile noexcept>();
    test_is_not_destructible<int(...) const volatile & noexcept>();
    test_is_not_destructible<int(...) const volatile && noexcept>();

    test_is_not_destructible<int(int, ...)>();
    test_is_not_destructible<int(int, ...)&>();
    test_is_not_destructible<int(int, ...) &&>();
    test_is_not_destructible<int(int, ...) const>();
    test_is_not_destructible<int(int, ...) const&>();
    test_is_not_destructible<int(int, ...) const&&>();
    test_is_not_destructible<int(int, ...) volatile>();
    test_is_not_destructible<int(int, ...) volatile&>();
    test_is_not_destructible<int(int, ...) volatile&&>();
    test_is_not_destructible<int(int, ...) const volatile>();
    test_is_not_destructible<int(int, ...) const volatile&>();
    test_is_not_destructible<int(int, ...) const volatile&&>();
    test_is_not_destructible<int(int, ...) noexcept>();
    test_is_not_destructible<int(int, ...) & noexcept>();
    test_is_not_destructible<int(int, ...) && noexcept>();
    test_is_not_destructible<int(int, ...) const noexcept>();
    test_is_not_destructible<int(int, ...) const & noexcept>();
    test_is_not_destructible<int(int, ...) const && noexcept>();
    test_is_not_destructible<int(int, ...) volatile noexcept>();
    test_is_not_destructible<int(int, ...) volatile & noexcept>();
    test_is_not_destructible<int(int, ...) volatile && noexcept>();
    test_is_not_destructible<int(int, ...) const volatile noexcept>();
    test_is_not_destructible<int(int, ...) const volatile & noexcept>();
    test_is_not_destructible<int(int, ...) const volatile && noexcept>();

    test_is_destructible<void (*)()>();
    test_is_destructible<void (*)() noexcept>();

    test_is_destructible<void (*)(int)>();
    test_is_destructible<void (*)(int) noexcept>();

    test_is_destructible<void (*)(...)>();
    test_is_destructible<void (*)(...) noexcept>();

    test_is_destructible<void (*)(int, ...)>();
    test_is_destructible<void (*)(int, ...) noexcept>();

    test_is_destructible<int (*)()>();
    test_is_destructible<int (*)() noexcept>();

    test_is_destructible<int (*)(int)>();
    test_is_destructible<int (*)(int) noexcept>();

    test_is_destructible<int (*)(...)>();
    test_is_destructible<int (*)(...) noexcept>();

    test_is_destructible<int (*)(int, ...)>();
    test_is_destructible<int (*)(int, ...) noexcept>();

    test_is_destructible<void (&)()>();
    test_is_destructible<void (&)() noexcept>();

    test_is_destructible<void (&)(int)>();
    test_is_destructible<void (&)(int) noexcept>();

    test_is_destructible<void (&)(...)>();
    test_is_destructible<void (&)(...) noexcept>();

    test_is_destructible<void (&)(int, ...)>();
    test_is_destructible<void (&)(int, ...) noexcept>();

    test_is_destructible<int (&)()>();
    test_is_destructible<int (&)() noexcept>();

    test_is_destructible<int (&)(int)>();
    test_is_destructible<int (&)(int) noexcept>();

    test_is_destructible<int (&)(...)>();
    test_is_destructible<int (&)(...) noexcept>();

    test_is_destructible<int (&)(int, ...)>();
    test_is_destructible<int (&)(int, ...) noexcept>();

    test_is_destructible<void (&&)()>();
    test_is_destructible<void (&&)() noexcept>();

    test_is_destructible<void (&&)(int)>();
    test_is_destructible<void (&&)(int) noexcept>();

    test_is_destructible<void (&&)(...)>();
    test_is_destructible<void (&&)(...) noexcept>();

    test_is_destructible<void (&&)(int, ...)>();
    test_is_destructible<void (&&)(int, ...) noexcept>();

    test_is_destructible<int (&&)()>();
    test_is_destructible<int (&&)() noexcept>();

    test_is_destructible<int (&&)(int)>();
    test_is_destructible<int (&&)(int) noexcept>();

    test_is_destructible<int (&&)(...)>();
    test_is_destructible<int (&&)(...) noexcept>();

    test_is_destructible<int (&&)(int, ...)>();
    test_is_destructible<int (&&)(int, ...) noexcept>();

    test_is_destructible<void (class_type::*)()>();
    test_is_destructible<void (class_type::*)()&>();
    test_is_destructible<void (class_type::*)() &&>();
    test_is_destructible<void (class_type::*)() const>();
    test_is_destructible<void (class_type::*)() const&>();
    test_is_destructible<void (class_type::*)() const&&>();
    test_is_destructible<void (class_type::*)() noexcept>();
    test_is_destructible<void (class_type::*)() & noexcept>();
    test_is_destructible<void (class_type::*)() && noexcept>();
    test_is_destructible<void (class_type::*)() const noexcept>();
    test_is_destructible<void (class_type::*)() const & noexcept>();
    test_is_destructible<void (class_type::*)() const && noexcept>();

    test_is_destructible<void (class_type::*)(int)>();
    test_is_destructible<void (class_type::*)(int)&>();
    test_is_destructible<void (class_type::*)(int) &&>();
    test_is_destructible<void (class_type::*)(int) const>();
    test_is_destructible<void (class_type::*)(int) const&>();
    test_is_destructible<void (class_type::*)(int) const&&>();
    test_is_destructible<void (class_type::*)(int) noexcept>();
    test_is_destructible<void (class_type::*)(int) & noexcept>();
    test_is_destructible<void (class_type::*)(int) && noexcept>();
    test_is_destructible<void (class_type::*)(int) const noexcept>();
    test_is_destructible<void (class_type::*)(int) const & noexcept>();
    test_is_destructible<void (class_type::*)(int) const && noexcept>();

    test_is_destructible<void (class_type::*)(...)>();
    test_is_destructible<void (class_type::*)(...)&>();
    test_is_destructible<void (class_type::*)(...) &&>();
    test_is_destructible<void (class_type::*)(...) const>();
    test_is_destructible<void (class_type::*)(...) const&>();
    test_is_destructible<void (class_type::*)(...) const&&>();
    test_is_destructible<void (class_type::*)(...) noexcept>();
    test_is_destructible<void (class_type::*)(...) & noexcept>();
    test_is_destructible<void (class_type::*)(...) && noexcept>();
    test_is_destructible<void (class_type::*)(...) const noexcept>();
    test_is_destructible<void (class_type::*)(...) const & noexcept>();
    test_is_destructible<void (class_type::*)(...) const && noexcept>();

    test_is_destructible<void (class_type::*)(int, ...)>();
    test_is_destructible<void (class_type::*)(int, ...)&>();
    test_is_destructible<void (class_type::*)(int, ...) &&>();
    test_is_destructible<void (class_type::*)(int, ...) const>();
    test_is_destructible<void (class_type::*)(int, ...) const&>();
    test_is_destructible<void (class_type::*)(int, ...) const&&>();
    test_is_destructible<void (class_type::*)(int, ...) noexcept>();
    test_is_destructible<void (class_type::*)(int, ...) & noexcept>();
    test_is_destructible<void (class_type::*)(int, ...) && noexcept>();
    test_is_destructible<void (class_type::*)(int, ...) const noexcept>();
    test_is_destructible<void (class_type::*)(int, ...) const & noexcept>();
    test_is_destructible<void (class_type::*)(int, ...) const && noexcept>();

    test_is_destructible<int (class_type::*)()>();
    test_is_destructible<int (class_type::*)()&>();
    test_is_destructible<int (class_type::*)() &&>();
    test_is_destructible<int (class_type::*)() const>();
    test_is_destructible<int (class_type::*)() const&>();
    test_is_destructible<int (class_type::*)() const&&>();
    test_is_destructible<int (class_type::*)() noexcept>();
    test_is_destructible<int (class_type::*)() & noexcept>();
    test_is_destructible<int (class_type::*)() && noexcept>();
    test_is_destructible<int (class_type::*)() const noexcept>();
    test_is_destructible<int (class_type::*)() const & noexcept>();
    test_is_destructible<int (class_type::*)() const && noexcept>();

    test_is_destructible<int (class_type::*)(int)>();
    test_is_destructible<int (class_type::*)(int)&>();
    test_is_destructible<int (class_type::*)(int) &&>();
    test_is_destructible<int (class_type::*)(int) const>();
    test_is_destructible<int (class_type::*)(int) const&>();
    test_is_destructible<int (class_type::*)(int) const&&>();
    test_is_destructible<int (class_type::*)(int) noexcept>();
    test_is_destructible<int (class_type::*)(int) & noexcept>();
    test_is_destructible<int (class_type::*)(int) && noexcept>();
    test_is_destructible<int (class_type::*)(int) const noexcept>();
    test_is_destructible<int (class_type::*)(int) const & noexcept>();
    test_is_destructible<int (class_type::*)(int) const && noexcept>();

    test_is_destructible<int (class_type::*)(...)>();
    test_is_destructible<int (class_type::*)(...)&>();
    test_is_destructible<int (class_type::*)(...) &&>();
    test_is_destructible<int (class_type::*)(...) const>();
    test_is_destructible<int (class_type::*)(...) const&>();
    test_is_destructible<int (class_type::*)(...) const&&>();
    test_is_destructible<int (class_type::*)(...) noexcept>();
    test_is_destructible<int (class_type::*)(...) & noexcept>();
    test_is_destructible<int (class_type::*)(...) && noexcept>();
    test_is_destructible<int (class_type::*)(...) const noexcept>();
    test_is_destructible<int (class_type::*)(...) const & noexcept>();
    test_is_destructible<int (class_type::*)(...) const && noexcept>();

    test_is_destructible<int (class_type::*)(int, ...)>();
    test_is_destructible<int (class_type::*)(int, ...)&>();
    test_is_destructible<int (class_type::*)(int, ...) &&>();
    test_is_destructible<int (class_type::*)(int, ...) const>();
    test_is_destructible<int (class_type::*)(int, ...) const&>();
    test_is_destructible<int (class_type::*)(int, ...) const&&>();
    test_is_destructible<int (class_type::*)(int, ...) noexcept>();
    test_is_destructible<int (class_type::*)(int, ...) & noexcept>();
    test_is_destructible<int (class_type::*)(int, ...) && noexcept>();
    test_is_destructible<int (class_type::*)(int, ...) const noexcept>();
    test_is_destructible<int (class_type::*)(int, ...) const & noexcept>();
    test_is_destructible<int (class_type::*)(int, ...) const && noexcept>();
#endif
}
