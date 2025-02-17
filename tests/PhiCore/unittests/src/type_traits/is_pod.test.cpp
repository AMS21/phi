#include <phi/test/test_macros.hpp>

#include <phi/compiler_support/warning.hpp>

PHI_MSVC_SUPPRESS_WARNING_PUSH()
PHI_MSVC_SUPPRESS_WARNING(
        4647) // behavior change: __is_pod(x) has different value in previous versions
PHI_MSVC_SUPPRESS_WARNING(
        4996) // 'std::is_pod<TypeT>': warning STL4025: std::is_pod and std::is_pod_v are deprecated in C++20. The std::is_trivially_copyable and/or std::is_standard_layout traits likely suit your use case. You can define _SILENCE_CXX20_IS_POD_DEPRECATION_WARNING or _SILENCE_ALL_CXX20_DEPRECATION_WARNINGS to acknowledge that you have received this warning.

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/compiler_support/compiler.hpp>
#include <phi/compiler_support/cpp_standard.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_pod.hpp>
#include <type_traits>
#include <vector>

PHI_CLANG_AND_GCC_SUPPRESS_WARNING_PUSH()
PHI_CLANG_AND_GCC_SUPPRESS_WARNING("-Wdeprecated-declarations") // is_pod was deprecated in C++-20

template <typename TypeT>
void test_is_pod_impl()
{
#if PHI_HAS_WORKING_IS_POD()
    STATIC_REQUIRE(phi::is_pod<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_pod<TypeT>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_pod_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_not_pod_v<TypeT>);
#    endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_pod<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_pod<TypeT>);

    // Standard compatibility
    STATIC_REQUIRE(std::is_pod<TypeT>::value);
#endif
}

template <typename TypeT>
void test_is_not_pod_impl()
{
#if PHI_HAS_WORKING_IS_POD()
    STATIC_REQUIRE_FALSE(phi::is_pod<TypeT>::value);
    STATIC_REQUIRE(phi::is_not_pod<TypeT>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_pod_v<TypeT>);
    STATIC_REQUIRE(phi::is_not_pod_v<TypeT>);
#    endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_pod<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_pod<TypeT>);

    // Standard compatibility
    STATIC_REQUIRE_FALSE(std::is_pod<TypeT>::value);
#endif
}

PHI_MSVC_SUPPRESS_WARNING_POP()
PHI_CLANG_AND_GCC_SUPPRESS_WARNING_POP()

template <typename TypeT>
void test_is_pod()
{
    test_is_pod_impl<TypeT>();
    test_is_pod_impl<const TypeT>();
    test_is_pod_impl<volatile TypeT>();
    test_is_pod_impl<const volatile TypeT>();
}

template <typename TypeT>
void test_is_not_pod()
{
    test_is_not_pod_impl<TypeT>();
    test_is_not_pod_impl<const TypeT>();
    test_is_not_pod_impl<volatile TypeT>();
    test_is_not_pod_impl<const volatile TypeT>();
}

struct A
{
    int m;
};

struct B
{
    int m1;

private:
    int m_Private;
};

PHI_GCC_SUPPRESS_WARNING_PUSH()
PHI_GCC_SUPPRESS_WARNING("-Wnon-virtual-dtor")

PHI_MSVC_SUPPRESS_WARNING_PUSH()
PHI_MSVC_SUPPRESS_WARNING(
        5204) // 'name': class has virtual functions, but its trivial destructor is not virtual; instances of objects derived from this class may not be destructed correctly

// NOLINTNEXTLINE(cppcoreguidelines-virtual-class-destructor)
struct C
{
    virtual void foo();
};

PHI_MSVC_SUPPRESS_WARNING_POP()
PHI_GCC_SUPPRESS_WARNING_POP()

template <typename TypeT>
struct D
{
    // NOLINTNEXTLINE(modernize-use-equals-default)
    D()
    {}
};

struct E
{
    const char* const foo;
    const char* const bar;
};

TEST_CASE("is_pod")
{
    test_is_pod<A>();
    test_is_not_pod<B>();
    test_is_not_pod<C>();
    test_is_not_pod<D<int>>();
    test_is_not_pod<D<double>>();

#if PHI_HAS_WORKING_IS_POD()
    int arr[phi::is_pod<D<int>>::value ? -1 : 1];
    (void)arr;
#endif

#if PHI_COMPILER_IS(MSVC)
    test_is_not_pod<E>();
#else
    test_is_pod<E>();
#endif

    test_is_not_pod<void>();
    test_is_pod<phi::nullptr_t>();
    test_is_pod<bool>();
    test_is_pod<char>();
    test_is_pod<signed char>();
    test_is_pod<unsigned char>();
    test_is_pod<short>();
    test_is_pod<unsigned short>();
    test_is_pod<int>();
    test_is_pod<unsigned int>();
    test_is_pod<long>();
    test_is_pod<unsigned long>();
    test_is_pod<long long>();
    test_is_pod<unsigned long long>();
    test_is_pod<float>();
    test_is_pod<double>();
    test_is_pod<long double>();
    test_is_pod<char8_t>();
    test_is_pod<char16_t>();
    test_is_pod<char32_t>();
    test_is_pod<wchar_t>();

#if PHI_COMPILER_IS(MSVC)
    test_is_not_pod<phi::boolean>();
    test_is_not_pod<phi::integer<signed char>>();
    test_is_not_pod<phi::integer<unsigned char>>();
    test_is_not_pod<phi::integer<short>>();
    test_is_not_pod<phi::integer<unsigned short>>();
    test_is_not_pod<phi::integer<int>>();
    test_is_not_pod<phi::integer<unsigned int>>();
    test_is_not_pod<phi::integer<long>>();
    test_is_not_pod<phi::integer<unsigned long>>();
    test_is_not_pod<phi::integer<long long>>();
    test_is_not_pod<phi::integer<unsigned long long>>();
    test_is_not_pod<phi::floating_point<float>>();
    test_is_not_pod<phi::floating_point<double>>();
    test_is_not_pod<phi::floating_point<long double>>();
#else
    test_is_pod<phi::boolean>();
    test_is_pod<phi::integer<signed char>>();
    test_is_pod<phi::integer<unsigned char>>();
    test_is_pod<phi::integer<short>>();
    test_is_pod<phi::integer<unsigned short>>();
    test_is_pod<phi::integer<int>>();
    test_is_pod<phi::integer<unsigned int>>();
    test_is_pod<phi::integer<long>>();
    test_is_pod<phi::integer<unsigned long>>();
    test_is_pod<phi::integer<long long>>();
    test_is_pod<phi::integer<unsigned long long>>();
    test_is_pod<phi::floating_point<float>>();
    test_is_pod<phi::floating_point<double>>();
    test_is_pod<phi::floating_point<long double>>();
#endif

    test_is_not_pod<std::vector<int>>();
    test_is_not_pod<phi::scope_ptr<int>>();

    test_is_not_pod<int&>();
    test_is_not_pod<const int&>();
    test_is_not_pod<volatile int&>();
    test_is_not_pod<const volatile int&>();
    test_is_not_pod<int&&>();
    test_is_not_pod<const int&&>();
    test_is_not_pod<volatile int&&>();
    test_is_not_pod<const volatile int&&>();
    test_is_pod<int*>();
    test_is_pod<const int*>();
    test_is_pod<volatile int*>();
    test_is_pod<const volatile int*>();
    test_is_pod<int**>();
    test_is_pod<const int**>();
    test_is_pod<volatile int**>();
    test_is_pod<const volatile int**>();
    test_is_not_pod<int*&>();
    test_is_not_pod<const int*&>();
    test_is_not_pod<volatile int*&>();
    test_is_not_pod<const volatile int*&>();
    test_is_not_pod<int*&&>();
    test_is_not_pod<const int*&&>();
    test_is_not_pod<volatile int*&&>();
    test_is_not_pod<const volatile int*&&>();
    test_is_pod<void*>();
    test_is_pod<char[3]>();
    test_is_pod<char[]>();
    test_is_pod<char* [3]>();
    test_is_pod<char*[]>();
    test_is_pod<int(*)[3]>();
    test_is_pod<int(*)[]>();
    test_is_not_pod<int(&)[3]>();
    test_is_not_pod<int(&)[]>();
    test_is_not_pod<int(&&)[3]>();
    test_is_not_pod<int(&&)[]>();
    test_is_pod<char[3][2]>();
    test_is_pod<char[][2]>();
    test_is_pod<char* [3][2]>();
    test_is_pod<char*[][2]>();
    test_is_pod<int(*)[3][2]>();
    test_is_pod<int(*)[][2]>();
    test_is_not_pod<int(&)[3][2]>();
    test_is_not_pod<int(&)[][2]>();
    test_is_not_pod<int(&&)[3][2]>();
    test_is_not_pod<int(&&)[][2]>();
    test_is_not_pod<class_type>();
    test_is_not_pod<class_type[]>();
    test_is_not_pod<class_type[2]>();
    test_is_pod<template_type<void>>();
    test_is_pod<template_type<int>>();
    test_is_pod<template_type<class_type>>();
    test_is_pod<template_type<incomplete_type>>();
    test_is_pod<variadic_template<>>();
    test_is_pod<variadic_template<void>>();
    test_is_pod<variadic_template<int>>();
    test_is_pod<variadic_template<class_type>>();
    test_is_pod<variadic_template<incomplete_type>>();
    test_is_pod<variadic_template<int, void, class_type, volatile char[]>>();
    test_is_pod<public_derived_from<base>>();
    test_is_pod<public_derived_from<derived>>();
    test_is_not_pod<public_derived_from<class_type>>();
    test_is_pod<private_derived_from<base>>();
    test_is_pod<private_derived_from<derived>>();
    test_is_not_pod<private_derived_from<class_type>>();
    test_is_pod<protected_derived_from<base>>();
    test_is_pod<protected_derived_from<derived>>();
    test_is_not_pod<protected_derived_from<class_type>>();
    test_is_not_pod<virtual_derived_from<base>>();
    test_is_not_pod<virtual_derived_from<derived>>();
    test_is_not_pod<virtual_derived_from<class_type>>();
    test_is_pod<union_type>();
    test_is_pod<non_empty_union>();
    test_is_not_pod<non_trivial_union>();
    test_is_pod<empty>();
    test_is_not_pod<not_empty>();
    test_is_not_pod<non_trivial>();
    test_is_pod<bit_zero>();
    test_is_pod<bit_one>();
    test_is_pod<base>();
    test_is_pod<derived>();
    test_is_not_pod<non_empty_base>();
    test_is_pod<empty_base>();
    test_is_not_pod<virtual_base>();
    test_is_not_pod<polymorphic>();
    test_is_not_pod<derived_polymorphic>();
    test_is_not_pod<abstract>();
    test_is_not_pod<public_abstract>();
    test_is_not_pod<private_abstract>();
    test_is_not_pod<protected_abstract>();
    test_is_not_pod<abstract_template<int>>();
    test_is_pod<abstract_template<double>>();
    test_is_not_pod<abstract_template<class_type>>();
    test_is_not_pod<abstract_template<incomplete_type>>();
    test_is_not_pod<public_abstract_deleted_destructor>();
    test_is_not_pod<protected_abstract_deleted_destructor>();
    test_is_not_pod<private_abstract_deleted_destructor>();
    test_is_pod<final_type>();
    test_is_pod<final_derived>();
    test_is_pod<public_destructor>();
    test_is_pod<protected_destructor>();
    test_is_pod<private_destructor>();
    test_is_not_pod<virtual_public_destructor>();
    test_is_not_pod<virtual_protected_destructor>();
    test_is_not_pod<virtual_private_destructor>();
    test_is_not_pod<pure_public_destructor>();
    test_is_not_pod<pure_protected_destructor>();
    test_is_not_pod<pure_private_destructor>();
#if PHI_COMPILER_IS(MSVC)
    test_is_not_pod<deleted_public_destructor>();
    test_is_not_pod<deleted_protected_destructor>();
    test_is_not_pod<deleted_private_destructor>();
#else
    test_is_pod<deleted_public_destructor>();
    test_is_pod<deleted_protected_destructor>();
    test_is_pod<deleted_private_destructor>();
#endif
    test_is_not_pod<deleted_virtual_public_destructor>();
    test_is_not_pod<deleted_virtual_protected_destructor>();
    test_is_not_pod<deleted_virtual_private_destructor>();
    test_is_not_pod<explicit_class>();
    test_is_not_pod<nothrow_explicit_class>();
    test_is_not_pod<throw_explicit_class>();
    test_is_not_pod<throw_default_class>();
    test_is_not_pod<throw_copy_constructible_class>();
    test_is_not_pod<throw_move_constructible_class>();
    test_is_not_pod<throw_destructor>();
    test_is_not_pod<noexcept_explicit_class>();
    test_is_not_pod<except_explicit_class>();
    test_is_not_pod<noexcept_default_class>();
    test_is_not_pod<except_default_class>();
    test_is_not_pod<noexcept_copy_constructible_class>();
    test_is_not_pod<except_copy_constructible_class>();
    test_is_not_pod<noexcept_move_constructible_class>();
    test_is_not_pod<except_move_constructible_class>();
    test_is_not_pod<noexcept_copy_assign_class>();
    test_is_not_pod<except_copy_assign_class>();
    test_is_not_pod<noexcept_move_assign_class>();
    test_is_not_pod<except_move_assign_class>();
    test_is_pod<deleted_copy_assign_class>();
#if PHI_COMPILER_IS(MSVC)
    test_is_not_pod<deleted_move_assign_class>();
#else
    test_is_pod<deleted_move_assign_class>();
#endif
    test_is_not_pod<noexcept_move_constructible_and_assignable_class>();
    test_is_not_pod<except_move_constructible_noexcept_move_assign_class>();
    test_is_not_pod<noexcept_move_constructible_except_move_assign_class>();
    test_is_not_pod<except_move_constructible_and_assign_class>();
    test_is_pod<implicit_to<int>>();
    test_is_pod<implicit_to<float>>();
    test_is_pod<implicit_to<class_type>>();
    test_is_pod<deleted_implicit_to<int>>();
    test_is_pod<deleted_implicit_to<float>>();
    test_is_pod<deleted_implicit_to<class_type>>();
    test_is_pod<explicit_to<int>>();
    test_is_pod<explicit_to<float>>();
    test_is_pod<explicit_to<class_type>>();
    test_is_pod<deleted_explicit_to<int>>();
    test_is_pod<deleted_explicit_to<float>>();
    test_is_pod<deleted_explicit_to<class_type>>();
    test_is_not_pod<ellipsis>();
#if PHI_COMPILER_IS(GCC) || PHI_COMPILER_IS(MINGW)
    test_is_pod<deleted_ellipsis>();
#else
    test_is_not_pod<deleted_ellipsis>();
#endif
    test_is_not_pod<copy_constructible_only_type>();
    test_is_not_pod<move_constructible_only_type>();
    test_is_pod<overloaded_operators>();
    test_is_pod<public_int_member>();
    test_is_pod<protected_int_member>();
    test_is_pod<private_int_member>();
    test_is_pod<public_static_int_member>();
    test_is_pod<protected_static_int_member>();
    test_is_pod<private_static_int_member>();
    test_is_pod<public_template_member<int>>();
    test_is_pod<public_template_member<float>>();
    test_is_not_pod<public_template_member<class_type>>();
    test_is_pod<protected_template_member<int>>();
    test_is_pod<protected_template_member<float>>();
    test_is_not_pod<protected_template_member<class_type>>();
    test_is_pod<private_template_member<int>>();
    test_is_pod<private_template_member<float>>();
    test_is_not_pod<private_template_member<class_type>>();
    test_is_pod<public_static_template_member<int>>();
    test_is_pod<public_static_template_member<float>>();
    test_is_pod<public_static_template_member<class_type>>();
    test_is_pod<protected_static_template_member<int>>();
    test_is_pod<protected_static_template_member<float>>();
    test_is_pod<protected_static_template_member<class_type>>();
    test_is_pod<private_static_template_member<int>>();
    test_is_pod<private_static_template_member<float>>();
    test_is_pod<private_static_template_member<class_type>>();
    test_is_pod<Enum>();
    test_is_pod<EnumSigned>();
    test_is_pod<EnumUnsigned>();
    test_is_pod<EnumClass>();
    test_is_pod<EnumStruct>();
    test_is_not_pod<function_type>();
    test_is_pod<function_ptr>();
    test_is_pod<member_object_ptr>();
    test_is_pod<member_function_ptr>();
#if (PHI_COMPILER_IS_ATLEAST(GCC, 9, 0, 0) || PHI_COMPILER_IS_NOT(GCC)) &&                         \
        PHI_CPP_STANDARD_IS_ATLEAST(20)
    test_is_pod<lambda_type>();
    test_is_pod<lambda_noexcept_type>();
    test_is_pod<lambda_throws_type>();
#else
    test_is_not_pod<lambda_type>();
    test_is_not_pod<lambda_noexcept_type>();
    test_is_not_pod<lambda_throws_type>();
#endif
    test_is_pod<IncompleteEnumSigned>();
    test_is_pod<IncompleteEnumUnsigned>();
    test_is_pod<IncompleteEnumClass>();
    test_is_pod<IncompleteEnumStruct>();
    test_is_pod<int class_type::*>();
    test_is_pod<float class_type::*>();
    test_is_pod<void * class_type::*>();
    test_is_pod<int * class_type::*>();
    test_is_not_pod<int class_type::*&>();
    test_is_not_pod<float class_type::*&>();
    test_is_not_pod<void * class_type::*&>();
    test_is_not_pod<int * class_type::*&>();
    test_is_not_pod<int class_type::*&&>();
    test_is_not_pod<float class_type::*&&>();
    test_is_not_pod<void * class_type::*&&>();
    test_is_not_pod<int * class_type::*&&>();
    test_is_pod<int class_type::* const>();
    test_is_pod<float class_type::* const>();
    test_is_pod<void * class_type::* const>();
    test_is_not_pod<int class_type::* const&>();
    test_is_not_pod<float class_type::* const&>();
    test_is_not_pod<void * class_type::* const&>();
    test_is_not_pod<int class_type::* const&&>();
    test_is_not_pod<float class_type::* const&&>();
    test_is_not_pod<void * class_type::* const&&>();
    test_is_pod<int class_type::* volatile>();
    test_is_pod<float class_type::* volatile>();
    test_is_pod<void * class_type::* volatile>();
    test_is_not_pod<int class_type::* volatile&>();
    test_is_not_pod<float class_type::* volatile&>();
    test_is_not_pod<void * class_type::* volatile&>();
    test_is_not_pod<int class_type::* volatile&&>();
    test_is_not_pod<float class_type::* volatile&&>();
    test_is_not_pod<void * class_type::* volatile&&>();
    test_is_pod<int class_type::* const volatile>();
    test_is_pod<float class_type::* const volatile>();
    test_is_pod<void * class_type::* const volatile>();
    test_is_not_pod<int class_type::* const volatile&>();
    test_is_not_pod<float class_type::* const volatile&>();
    test_is_not_pod<void * class_type::* const volatile&>();
    test_is_not_pod<int class_type::* const volatile&&>();
    test_is_not_pod<float class_type::* const volatile&&>();
    test_is_not_pod<void * class_type::* const volatile&&>();
#if PHI_COMPILER_IS(MSVC)
    test_is_not_pod<non_default_constructible>();
#else
    test_is_pod<non_default_constructible>();
#endif
    test_is_pod<non_copy_constructible>();
    test_is_pod<non_move_constructible>();
    test_is_pod<non_copy_assignable>();
    test_is_pod<non_move_assignable>();
    test_is_pod<non_assignable>();
    test_is_pod<non_copyable>();
    test_is_pod<non_moveable>();
#if PHI_COMPILER_IS(MSVC)
    test_is_not_pod<non_constructible>();
    test_is_not_pod<non_destructible>();
#else
    test_is_pod<non_constructible>();
    test_is_pod<non_destructible>();
#endif
    test_is_not_pod<tracked>();
    test_is_pod<trap_constructible>();
    test_is_pod<trap_implicit_conversion>();
    test_is_pod<trap_comma>();
    test_is_pod<trap_call>();
    test_is_not_pod<trap_self_assign>();
    test_is_pod<trap_deref>();
    test_is_pod<trap_array_subscript>();

    test_is_not_pod<void()>();
    test_is_not_pod<void()&>();
    test_is_not_pod<void() &&>();
    test_is_not_pod<void() const>();
    test_is_not_pod<void() const&>();
    test_is_not_pod<void() const&&>();
    test_is_not_pod<void() volatile>();
    test_is_not_pod<void() volatile&>();
    test_is_not_pod<void() volatile&&>();
    test_is_not_pod<void() const volatile>();
    test_is_not_pod<void() const volatile&>();
    test_is_not_pod<void() const volatile&&>();
    test_is_not_pod<void() noexcept>();
    test_is_not_pod<void() & noexcept>();
    test_is_not_pod<void() && noexcept>();
    test_is_not_pod<void() const noexcept>();
    test_is_not_pod<void() const & noexcept>();
    test_is_not_pod<void() const && noexcept>();
    test_is_not_pod<void() volatile noexcept>();
    test_is_not_pod<void() volatile & noexcept>();
    test_is_not_pod<void() volatile && noexcept>();
    test_is_not_pod<void() const volatile noexcept>();
    test_is_not_pod<void() const volatile & noexcept>();
    test_is_not_pod<void() const volatile && noexcept>();

    test_is_not_pod<void(int)>();
    test_is_not_pod<void(int)&>();
    test_is_not_pod<void(int) &&>();
    test_is_not_pod<void(int) const>();
    test_is_not_pod<void(int) const&>();
    test_is_not_pod<void(int) const&&>();
    test_is_not_pod<void(int) volatile>();
    test_is_not_pod<void(int) volatile&>();
    test_is_not_pod<void(int) volatile&&>();
    test_is_not_pod<void(int) const volatile>();
    test_is_not_pod<void(int) const volatile&>();
    test_is_not_pod<void(int) const volatile&&>();
    test_is_not_pod<void(int) noexcept>();
    test_is_not_pod<void(int) & noexcept>();
    test_is_not_pod<void(int) && noexcept>();
    test_is_not_pod<void(int) const noexcept>();
    test_is_not_pod<void(int) const & noexcept>();
    test_is_not_pod<void(int) const && noexcept>();
    test_is_not_pod<void(int) volatile noexcept>();
    test_is_not_pod<void(int) volatile & noexcept>();
    test_is_not_pod<void(int) volatile && noexcept>();
    test_is_not_pod<void(int) const volatile noexcept>();
    test_is_not_pod<void(int) const volatile & noexcept>();
    test_is_not_pod<void(int) const volatile && noexcept>();

    test_is_not_pod<void(...)>();
    test_is_not_pod<void(...)&>();
    test_is_not_pod<void(...) &&>();
    test_is_not_pod<void(...) const>();
    test_is_not_pod<void(...) const&>();
    test_is_not_pod<void(...) const&&>();
    test_is_not_pod<void(...) volatile>();
    test_is_not_pod<void(...) volatile&>();
    test_is_not_pod<void(...) volatile&&>();
    test_is_not_pod<void(...) const volatile>();
    test_is_not_pod<void(...) const volatile&>();
    test_is_not_pod<void(...) const volatile&&>();
    test_is_not_pod<void(...) noexcept>();
    test_is_not_pod<void(...) & noexcept>();
    test_is_not_pod<void(...) && noexcept>();
    test_is_not_pod<void(...) const noexcept>();
    test_is_not_pod<void(...) const & noexcept>();
    test_is_not_pod<void(...) const && noexcept>();
    test_is_not_pod<void(...) volatile noexcept>();
    test_is_not_pod<void(...) volatile & noexcept>();
    test_is_not_pod<void(...) volatile && noexcept>();
    test_is_not_pod<void(...) const volatile noexcept>();
    test_is_not_pod<void(...) const volatile & noexcept>();
    test_is_not_pod<void(...) const volatile && noexcept>();

    test_is_not_pod<void(int, ...)>();
    test_is_not_pod<void(int, ...)&>();
    test_is_not_pod<void(int, ...) &&>();
    test_is_not_pod<void(int, ...) const>();
    test_is_not_pod<void(int, ...) const&>();
    test_is_not_pod<void(int, ...) const&&>();
    test_is_not_pod<void(int, ...) volatile>();
    test_is_not_pod<void(int, ...) volatile&>();
    test_is_not_pod<void(int, ...) volatile&&>();
    test_is_not_pod<void(int, ...) const volatile>();
    test_is_not_pod<void(int, ...) const volatile&>();
    test_is_not_pod<void(int, ...) const volatile&&>();
    test_is_not_pod<void(int, ...) noexcept>();
    test_is_not_pod<void(int, ...) & noexcept>();
    test_is_not_pod<void(int, ...) && noexcept>();
    test_is_not_pod<void(int, ...) const noexcept>();
    test_is_not_pod<void(int, ...) const & noexcept>();
    test_is_not_pod<void(int, ...) const && noexcept>();
    test_is_not_pod<void(int, ...) volatile noexcept>();
    test_is_not_pod<void(int, ...) volatile & noexcept>();
    test_is_not_pod<void(int, ...) volatile && noexcept>();
    test_is_not_pod<void(int, ...) const volatile noexcept>();
    test_is_not_pod<void(int, ...) const volatile & noexcept>();
    test_is_not_pod<void(int, ...) const volatile && noexcept>();

    test_is_not_pod<int()>();
    test_is_not_pod<int()&>();
    test_is_not_pod<int() &&>();
    test_is_not_pod<int() const>();
    test_is_not_pod<int() const&>();
    test_is_not_pod<int() const&&>();
    test_is_not_pod<int() volatile>();
    test_is_not_pod<int() volatile&>();
    test_is_not_pod<int() volatile&&>();
    test_is_not_pod<int() const volatile>();
    test_is_not_pod<int() const volatile&>();
    test_is_not_pod<int() const volatile&&>();
    test_is_not_pod<int() noexcept>();
    test_is_not_pod<int() & noexcept>();
    test_is_not_pod<int() && noexcept>();
    test_is_not_pod<int() const noexcept>();
    test_is_not_pod<int() const & noexcept>();
    test_is_not_pod<int() const && noexcept>();
    test_is_not_pod<int() volatile noexcept>();
    test_is_not_pod<int() volatile & noexcept>();
    test_is_not_pod<int() volatile && noexcept>();
    test_is_not_pod<int() const volatile noexcept>();
    test_is_not_pod<int() const volatile & noexcept>();
    test_is_not_pod<int() const volatile && noexcept>();

    test_is_not_pod<int(int)>();
    test_is_not_pod<int(int)&>();
    test_is_not_pod<int(int) &&>();
    test_is_not_pod<int(int) const>();
    test_is_not_pod<int(int) const&>();
    test_is_not_pod<int(int) const&&>();
    test_is_not_pod<int(int) volatile>();
    test_is_not_pod<int(int) volatile&>();
    test_is_not_pod<int(int) volatile&&>();
    test_is_not_pod<int(int) const volatile>();
    test_is_not_pod<int(int) const volatile&>();
    test_is_not_pod<int(int) const volatile&&>();
    test_is_not_pod<int(int) noexcept>();
    test_is_not_pod<int(int) & noexcept>();
    test_is_not_pod<int(int) && noexcept>();
    test_is_not_pod<int(int) const noexcept>();
    test_is_not_pod<int(int) const & noexcept>();
    test_is_not_pod<int(int) const && noexcept>();
    test_is_not_pod<int(int) volatile noexcept>();
    test_is_not_pod<int(int) volatile & noexcept>();
    test_is_not_pod<int(int) volatile && noexcept>();
    test_is_not_pod<int(int) const volatile noexcept>();
    test_is_not_pod<int(int) const volatile & noexcept>();
    test_is_not_pod<int(int) const volatile && noexcept>();

    test_is_not_pod<int(...)>();
    test_is_not_pod<int(...)&>();
    test_is_not_pod<int(...) &&>();
    test_is_not_pod<int(...) const>();
    test_is_not_pod<int(...) const&>();
    test_is_not_pod<int(...) const&&>();
    test_is_not_pod<int(...) volatile>();
    test_is_not_pod<int(...) volatile&>();
    test_is_not_pod<int(...) volatile&&>();
    test_is_not_pod<int(...) const volatile>();
    test_is_not_pod<int(...) const volatile&>();
    test_is_not_pod<int(...) const volatile&&>();
    test_is_not_pod<int(...) noexcept>();
    test_is_not_pod<int(...) & noexcept>();
    test_is_not_pod<int(...) && noexcept>();
    test_is_not_pod<int(...) const noexcept>();
    test_is_not_pod<int(...) const & noexcept>();
    test_is_not_pod<int(...) const && noexcept>();
    test_is_not_pod<int(...) volatile noexcept>();
    test_is_not_pod<int(...) volatile & noexcept>();
    test_is_not_pod<int(...) volatile && noexcept>();
    test_is_not_pod<int(...) const volatile noexcept>();
    test_is_not_pod<int(...) const volatile & noexcept>();
    test_is_not_pod<int(...) const volatile && noexcept>();

    test_is_not_pod<int(int, ...)>();
    test_is_not_pod<int(int, ...)&>();
    test_is_not_pod<int(int, ...) &&>();
    test_is_not_pod<int(int, ...) const>();
    test_is_not_pod<int(int, ...) const&>();
    test_is_not_pod<int(int, ...) const&&>();
    test_is_not_pod<int(int, ...) volatile>();
    test_is_not_pod<int(int, ...) volatile&>();
    test_is_not_pod<int(int, ...) volatile&&>();
    test_is_not_pod<int(int, ...) const volatile>();
    test_is_not_pod<int(int, ...) const volatile&>();
    test_is_not_pod<int(int, ...) const volatile&&>();
    test_is_not_pod<int(int, ...) noexcept>();
    test_is_not_pod<int(int, ...) & noexcept>();
    test_is_not_pod<int(int, ...) && noexcept>();
    test_is_not_pod<int(int, ...) const noexcept>();
    test_is_not_pod<int(int, ...) const & noexcept>();
    test_is_not_pod<int(int, ...) const && noexcept>();
    test_is_not_pod<int(int, ...) volatile noexcept>();
    test_is_not_pod<int(int, ...) volatile & noexcept>();
    test_is_not_pod<int(int, ...) volatile && noexcept>();
    test_is_not_pod<int(int, ...) const volatile noexcept>();
    test_is_not_pod<int(int, ...) const volatile & noexcept>();
    test_is_not_pod<int(int, ...) const volatile && noexcept>();

    test_is_pod<void (*)()>();
    test_is_pod<void (*)() noexcept>();

    test_is_pod<void (*)(int)>();
    test_is_pod<void (*)(int) noexcept>();

    test_is_pod<void (*)(...)>();
    test_is_pod<void (*)(...) noexcept>();

    test_is_pod<void (*)(int, ...)>();
    test_is_pod<void (*)(int, ...) noexcept>();

    test_is_pod<int (*)()>();
    test_is_pod<int (*)() noexcept>();

    test_is_pod<int (*)(int)>();
    test_is_pod<int (*)(int) noexcept>();

    test_is_pod<int (*)(...)>();
    test_is_pod<int (*)(...) noexcept>();

    test_is_pod<int (*)(int, ...)>();
    test_is_pod<int (*)(int, ...) noexcept>();

    test_is_not_pod<void (&)()>();
    test_is_not_pod<void (&)() noexcept>();

    test_is_not_pod<void (&)(int)>();
    test_is_not_pod<void (&)(int) noexcept>();

    test_is_not_pod<void (&)(...)>();
    test_is_not_pod<void (&)(...) noexcept>();

    test_is_not_pod<void (&)(int, ...)>();
    test_is_not_pod<void (&)(int, ...) noexcept>();

    test_is_not_pod<int (&)()>();
    test_is_not_pod<int (&)() noexcept>();

    test_is_not_pod<int (&)(int)>();
    test_is_not_pod<int (&)(int) noexcept>();

    test_is_not_pod<int (&)(...)>();
    test_is_not_pod<int (&)(...) noexcept>();

    test_is_not_pod<int (&)(int, ...)>();
    test_is_not_pod<int (&)(int, ...) noexcept>();

    test_is_not_pod<void (&&)()>();
    test_is_not_pod<void (&&)() noexcept>();

    test_is_not_pod<void (&&)(int)>();
    test_is_not_pod<void (&&)(int) noexcept>();

    test_is_not_pod<void (&&)(...)>();
    test_is_not_pod<void (&&)(...) noexcept>();

    test_is_not_pod<void (&&)(int, ...)>();
    test_is_not_pod<void (&&)(int, ...) noexcept>();

    test_is_not_pod<int (&&)()>();
    test_is_not_pod<int (&&)() noexcept>();

    test_is_not_pod<int (&&)(int)>();
    test_is_not_pod<int (&&)(int) noexcept>();

    test_is_not_pod<int (&&)(...)>();
    test_is_not_pod<int (&&)(...) noexcept>();

    test_is_not_pod<int (&&)(int, ...)>();
    test_is_not_pod<int (&&)(int, ...) noexcept>();

    test_is_pod<void (class_type::*)()>();
    test_is_pod<void (class_type::*)()&>();
    test_is_pod<void (class_type::*)() &&>();
    test_is_pod<void (class_type::*)() const>();
    test_is_pod<void (class_type::*)() const&>();
    test_is_pod<void (class_type::*)() const&&>();
    test_is_pod<void (class_type::*)() noexcept>();
    test_is_pod<void (class_type::*)() & noexcept>();
    test_is_pod<void (class_type::*)() && noexcept>();
    test_is_pod<void (class_type::*)() const noexcept>();
    test_is_pod<void (class_type::*)() const & noexcept>();
    test_is_pod<void (class_type::*)() const && noexcept>();

    test_is_pod<void (class_type::*)(int)>();
    test_is_pod<void (class_type::*)(int)&>();
    test_is_pod<void (class_type::*)(int) &&>();
    test_is_pod<void (class_type::*)(int) const>();
    test_is_pod<void (class_type::*)(int) const&>();
    test_is_pod<void (class_type::*)(int) const&&>();
    test_is_pod<void (class_type::*)(int) noexcept>();
    test_is_pod<void (class_type::*)(int) & noexcept>();
    test_is_pod<void (class_type::*)(int) && noexcept>();
    test_is_pod<void (class_type::*)(int) const noexcept>();
    test_is_pod<void (class_type::*)(int) const & noexcept>();
    test_is_pod<void (class_type::*)(int) const && noexcept>();

    test_is_pod<void (class_type::*)(...)>();
    test_is_pod<void (class_type::*)(...)&>();
    test_is_pod<void (class_type::*)(...) &&>();
    test_is_pod<void (class_type::*)(...) const>();
    test_is_pod<void (class_type::*)(...) const&>();
    test_is_pod<void (class_type::*)(...) const&&>();
    test_is_pod<void (class_type::*)(...) noexcept>();
    test_is_pod<void (class_type::*)(...) & noexcept>();
    test_is_pod<void (class_type::*)(...) && noexcept>();
    test_is_pod<void (class_type::*)(...) const noexcept>();
    test_is_pod<void (class_type::*)(...) const & noexcept>();
    test_is_pod<void (class_type::*)(...) const && noexcept>();

    test_is_pod<void (class_type::*)(int, ...)>();
    test_is_pod<void (class_type::*)(int, ...)&>();
    test_is_pod<void (class_type::*)(int, ...) &&>();
    test_is_pod<void (class_type::*)(int, ...) const>();
    test_is_pod<void (class_type::*)(int, ...) const&>();
    test_is_pod<void (class_type::*)(int, ...) const&&>();
    test_is_pod<void (class_type::*)(int, ...) noexcept>();
    test_is_pod<void (class_type::*)(int, ...) & noexcept>();
    test_is_pod<void (class_type::*)(int, ...) && noexcept>();
    test_is_pod<void (class_type::*)(int, ...) const noexcept>();
    test_is_pod<void (class_type::*)(int, ...) const & noexcept>();
    test_is_pod<void (class_type::*)(int, ...) const && noexcept>();

    test_is_pod<int (class_type::*)()>();
    test_is_pod<int (class_type::*)()&>();
    test_is_pod<int (class_type::*)() &&>();
    test_is_pod<int (class_type::*)() const>();
    test_is_pod<int (class_type::*)() const&>();
    test_is_pod<int (class_type::*)() const&&>();
    test_is_pod<int (class_type::*)() noexcept>();
    test_is_pod<int (class_type::*)() & noexcept>();
    test_is_pod<int (class_type::*)() && noexcept>();
    test_is_pod<int (class_type::*)() const noexcept>();
    test_is_pod<int (class_type::*)() const & noexcept>();
    test_is_pod<int (class_type::*)() const && noexcept>();

    test_is_pod<int (class_type::*)(int)>();
    test_is_pod<int (class_type::*)(int)&>();
    test_is_pod<int (class_type::*)(int) &&>();
    test_is_pod<int (class_type::*)(int) const>();
    test_is_pod<int (class_type::*)(int) const&>();
    test_is_pod<int (class_type::*)(int) const&&>();
    test_is_pod<int (class_type::*)(int) noexcept>();
    test_is_pod<int (class_type::*)(int) & noexcept>();
    test_is_pod<int (class_type::*)(int) && noexcept>();
    test_is_pod<int (class_type::*)(int) const noexcept>();
    test_is_pod<int (class_type::*)(int) const & noexcept>();
    test_is_pod<int (class_type::*)(int) const && noexcept>();

    test_is_pod<int (class_type::*)(...)>();
    test_is_pod<int (class_type::*)(...)&>();
    test_is_pod<int (class_type::*)(...) &&>();
    test_is_pod<int (class_type::*)(...) const>();
    test_is_pod<int (class_type::*)(...) const&>();
    test_is_pod<int (class_type::*)(...) const&&>();
    test_is_pod<int (class_type::*)(...) noexcept>();
    test_is_pod<int (class_type::*)(...) & noexcept>();
    test_is_pod<int (class_type::*)(...) && noexcept>();
    test_is_pod<int (class_type::*)(...) const noexcept>();
    test_is_pod<int (class_type::*)(...) const & noexcept>();
    test_is_pod<int (class_type::*)(...) const && noexcept>();

    test_is_pod<int (class_type::*)(int, ...)>();
    test_is_pod<int (class_type::*)(int, ...)&>();
    test_is_pod<int (class_type::*)(int, ...) &&>();
    test_is_pod<int (class_type::*)(int, ...) const>();
    test_is_pod<int (class_type::*)(int, ...) const&>();
    test_is_pod<int (class_type::*)(int, ...) const&&>();
    test_is_pod<int (class_type::*)(int, ...) noexcept>();
    test_is_pod<int (class_type::*)(int, ...) & noexcept>();
    test_is_pod<int (class_type::*)(int, ...) && noexcept>();
    test_is_pod<int (class_type::*)(int, ...) const noexcept>();
    test_is_pod<int (class_type::*)(int, ...) const & noexcept>();
    test_is_pod<int (class_type::*)(int, ...) const && noexcept>();
}
