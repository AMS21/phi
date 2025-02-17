#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/compiler_support/warning.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_standard_layout.hpp>
#include <type_traits>
#include <vector>

template <typename TypeT>
void test_is_standard_layout_impl()
{
#if PHI_HAS_WORKING_IS_STANDARD_LAYOUT()
    STATIC_REQUIRE(phi::is_standard_layout<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_standard_layout<TypeT>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_standard_layout_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_not_standard_layout_v<TypeT>);
#    endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_standard_layout<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_standard_layout<TypeT>);

    // Standard compatbilility
    STATIC_REQUIRE(std::is_standard_layout<TypeT>::value);
#endif
}

template <typename TypeT>
void test_is_not_standard_layout_impl()
{
#if PHI_HAS_WORKING_IS_STANDARD_LAYOUT()
    STATIC_REQUIRE_FALSE(phi::is_standard_layout<TypeT>::value);
    STATIC_REQUIRE(phi::is_not_standard_layout<TypeT>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_standard_layout_v<TypeT>);
    STATIC_REQUIRE(phi::is_not_standard_layout_v<TypeT>);
#    endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_standard_layout<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_standard_layout<TypeT>);

    // Standard compatbilility
    STATIC_REQUIRE_FALSE(std::is_standard_layout<TypeT>::value);
#endif
}

template <typename TypeT>
void test_is_standard_layout()
{
    test_is_standard_layout_impl<TypeT>();
    test_is_standard_layout_impl<const TypeT>();
    test_is_standard_layout_impl<volatile TypeT>();
    test_is_standard_layout_impl<const volatile TypeT>();
}

template <typename TypeT>
void test_is_not_standard_layout()
{
    test_is_not_standard_layout_impl<TypeT>();
    test_is_not_standard_layout_impl<const TypeT>();
    test_is_not_standard_layout_impl<volatile TypeT>();
    test_is_not_standard_layout_impl<const volatile TypeT>();
}

template <typename TypeT>
void test_is_standard_layout_function()
{
#if PHI_COMPILER_IS(MSVC)
    test_is_standard_layout<TypeT>();
    test_is_standard_layout<const TypeT>();
    test_is_standard_layout<volatile TypeT>();
    test_is_standard_layout<const volatile TypeT>();
#else
    test_is_not_standard_layout<TypeT>();
    test_is_not_standard_layout<const TypeT>();
    test_is_not_standard_layout<volatile TypeT>();
    test_is_not_standard_layout<const volatile TypeT>();
#endif
}

template <typename FirstT, typename SecondT>
struct pair
{
    FirstT  first;
    SecondT second;
};

struct A
{
    int m;
};

PHI_CLANG_SUPPRESS_WARNING_PUSH()
PHI_CLANG_SUPPRESS_WARNING("-Wunused-private-field")

struct B
{
    int m1;

private:
    int m_Private;
};

PHI_CLANG_SUPPRESS_WARNING_POP()

struct C
{
    virtual ~C();
    virtual void foo();
};

TEST_CASE("is_standard_layout")
{
    test_is_standard_layout<pair<int, double>>();
    test_is_standard_layout<pair<int, double>[5]>();
    test_is_standard_layout<pair<A, A>>();
    test_is_standard_layout<pair<A, A>[12]>();
    test_is_standard_layout<A>();
    test_is_standard_layout<A[3]>();

    test_is_not_standard_layout<B>();
    test_is_not_standard_layout<C>();

    test_is_not_standard_layout<void>();
    test_is_standard_layout<phi::nullptr_t>();
    test_is_standard_layout<bool>();
    test_is_standard_layout<char>();
    test_is_standard_layout<signed char>();
    test_is_standard_layout<unsigned char>();
    test_is_standard_layout<short>();
    test_is_standard_layout<unsigned short>();
    test_is_standard_layout<int>();
    test_is_standard_layout<unsigned int>();
    test_is_standard_layout<long>();
    test_is_standard_layout<unsigned long>();
    test_is_standard_layout<long long>();
    test_is_standard_layout<unsigned long long>();
    test_is_standard_layout<float>();
    test_is_standard_layout<double>();
    test_is_standard_layout<long double>();
    test_is_standard_layout<char8_t>();
    test_is_standard_layout<char16_t>();
    test_is_standard_layout<char32_t>();
    test_is_standard_layout<wchar_t>();

    test_is_standard_layout<phi::boolean>();
    test_is_standard_layout<phi::integer<signed char>>();
    test_is_standard_layout<phi::integer<unsigned char>>();
    test_is_standard_layout<phi::integer<short>>();
    test_is_standard_layout<phi::integer<unsigned short>>();
    test_is_standard_layout<phi::integer<int>>();
    test_is_standard_layout<phi::integer<unsigned int>>();
    test_is_standard_layout<phi::integer<long>>();
    test_is_standard_layout<phi::integer<unsigned long>>();
    test_is_standard_layout<phi::integer<long long>>();
    test_is_standard_layout<phi::integer<unsigned long long>>();
    test_is_standard_layout<phi::floating_point<float>>();
    test_is_standard_layout<phi::floating_point<double>>();
    test_is_standard_layout<phi::floating_point<long double>>();

    test_is_standard_layout<phi::scope_ptr<int>>();

    test_is_not_standard_layout<int&>();
    test_is_not_standard_layout<const int&>();
    test_is_not_standard_layout<volatile int&>();
    test_is_not_standard_layout<const volatile int&>();
    test_is_not_standard_layout<int&&>();
    test_is_not_standard_layout<const int&&>();
    test_is_not_standard_layout<volatile int&&>();
    test_is_not_standard_layout<const volatile int&&>();
    test_is_standard_layout<int*>();
    test_is_standard_layout<const int*>();
    test_is_standard_layout<volatile int*>();
    test_is_standard_layout<const volatile int*>();
    test_is_standard_layout<int**>();
    test_is_standard_layout<const int**>();
    test_is_standard_layout<volatile int**>();
    test_is_standard_layout<const volatile int**>();
    test_is_not_standard_layout<int*&>();
    test_is_not_standard_layout<const int*&>();
    test_is_not_standard_layout<volatile int*&>();
    test_is_not_standard_layout<const volatile int*&>();
    test_is_not_standard_layout<int*&&>();
    test_is_not_standard_layout<const int*&&>();
    test_is_not_standard_layout<volatile int*&&>();
    test_is_not_standard_layout<const volatile int*&&>();
    test_is_standard_layout<void*>();
    test_is_standard_layout<char[3]>();
    test_is_standard_layout<char[]>();
    test_is_standard_layout<char* [3]>();
    test_is_standard_layout<char*[]>();
    test_is_standard_layout<int(*)[3]>();
    test_is_standard_layout<int(*)[]>();
    test_is_not_standard_layout<int(&)[3]>();
    test_is_not_standard_layout<int(&)[]>();
    test_is_not_standard_layout<int(&&)[3]>();
    test_is_not_standard_layout<int(&&)[]>();
    test_is_standard_layout<char[3][2]>();
    test_is_standard_layout<char[][2]>();
    test_is_standard_layout<char* [3][2]>();
    test_is_standard_layout<char*[][2]>();
    test_is_standard_layout<int(*)[3][2]>();
    test_is_standard_layout<int(*)[][2]>();
    test_is_not_standard_layout<int(&)[3][2]>();
    test_is_not_standard_layout<int(&)[][2]>();
    test_is_not_standard_layout<int(&&)[3][2]>();
    test_is_not_standard_layout<int(&&)[][2]>();
    test_is_standard_layout<class_type>();
    test_is_standard_layout<class_type[]>();
    test_is_standard_layout<class_type[2]>();
    test_is_standard_layout<template_type<void>>();
    test_is_standard_layout<template_type<int>>();
    test_is_standard_layout<template_type<class_type>>();
    test_is_standard_layout<template_type<incomplete_type>>();
    test_is_standard_layout<variadic_template<>>();
    test_is_standard_layout<variadic_template<void>>();
    test_is_standard_layout<variadic_template<int>>();
    test_is_standard_layout<variadic_template<class_type>>();
    test_is_standard_layout<variadic_template<incomplete_type>>();
    test_is_standard_layout<variadic_template<int, void, class_type, volatile char[]>>();
    test_is_standard_layout<public_derived_from<base>>();
    test_is_standard_layout<public_derived_from<derived>>();
    test_is_standard_layout<public_derived_from<class_type>>();
    test_is_standard_layout<private_derived_from<base>>();
    test_is_standard_layout<private_derived_from<derived>>();
    test_is_standard_layout<private_derived_from<class_type>>();
    test_is_standard_layout<protected_derived_from<base>>();
    test_is_standard_layout<protected_derived_from<derived>>();
    test_is_standard_layout<protected_derived_from<class_type>>();
    test_is_standard_layout<union_type>();
    test_is_standard_layout<non_empty_union>();
    test_is_standard_layout<empty>();
    test_is_not_standard_layout<not_empty>();
    test_is_standard_layout<bit_zero>();
    test_is_standard_layout<bit_one>();
    test_is_standard_layout<base>();
    test_is_standard_layout<derived>();
    test_is_not_standard_layout<abstract>();
    test_is_not_standard_layout<public_abstract>();
    test_is_not_standard_layout<private_abstract>();
    test_is_not_standard_layout<protected_abstract>();
    test_is_not_standard_layout<abstract_template<int>>();
    test_is_standard_layout<abstract_template<double>>();
    test_is_not_standard_layout<abstract_template<class_type>>();
    test_is_not_standard_layout<abstract_template<incomplete_type>>();
    test_is_standard_layout<final_type>();
    test_is_standard_layout<public_destructor>();
    test_is_standard_layout<protected_destructor>();
    test_is_standard_layout<private_destructor>();
    test_is_not_standard_layout<virtual_public_destructor>();
    test_is_not_standard_layout<virtual_protected_destructor>();
    test_is_not_standard_layout<virtual_private_destructor>();
    test_is_not_standard_layout<pure_public_destructor>();
    test_is_not_standard_layout<pure_protected_destructor>();
    test_is_not_standard_layout<pure_private_destructor>();
    test_is_standard_layout<deleted_public_destructor>();
    test_is_standard_layout<deleted_protected_destructor>();
    test_is_standard_layout<deleted_private_destructor>();
    test_is_not_standard_layout<deleted_virtual_public_destructor>();
    test_is_not_standard_layout<deleted_virtual_protected_destructor>();
    test_is_not_standard_layout<deleted_virtual_private_destructor>();
    test_is_standard_layout<Enum>();
    test_is_standard_layout<EnumSigned>();
    test_is_standard_layout<EnumUnsigned>();
    test_is_standard_layout<EnumClass>();
    test_is_standard_layout<EnumStruct>();
    test_is_standard_layout_function<function_type>();
    test_is_standard_layout<function_ptr>();
    test_is_standard_layout<member_object_ptr>();
    test_is_standard_layout<member_function_ptr>();
    test_is_standard_layout<int class_type::*>();
    test_is_standard_layout<float class_type::*>();
    test_is_standard_layout<void * class_type::*>();
    test_is_standard_layout<int * class_type::*>();
    test_is_not_standard_layout<int class_type::*&>();
    test_is_not_standard_layout<float class_type::*&>();
    test_is_not_standard_layout<void * class_type::*&>();
    test_is_not_standard_layout<int * class_type::*&>();
    test_is_not_standard_layout<int class_type::*&&>();
    test_is_not_standard_layout<float class_type::*&&>();
    test_is_not_standard_layout<void * class_type::*&&>();
    test_is_not_standard_layout<int * class_type::*&&>();
    test_is_standard_layout<int class_type::* const>();
    test_is_standard_layout<float class_type::* const>();
    test_is_standard_layout<void * class_type::* const>();
    test_is_not_standard_layout<int class_type::* const&>();
    test_is_not_standard_layout<float class_type::* const&>();
    test_is_not_standard_layout<void * class_type::* const&>();
    test_is_not_standard_layout<int class_type::* const&&>();
    test_is_not_standard_layout<float class_type::* const&&>();
    test_is_not_standard_layout<void * class_type::* const&&>();
    test_is_standard_layout<int class_type::* volatile>();
    test_is_standard_layout<float class_type::* volatile>();
    test_is_standard_layout<void * class_type::* volatile>();
    test_is_not_standard_layout<int class_type::* volatile&>();
    test_is_not_standard_layout<float class_type::* volatile&>();
    test_is_not_standard_layout<void * class_type::* volatile&>();
    test_is_not_standard_layout<int class_type::* volatile&&>();
    test_is_not_standard_layout<float class_type::* volatile&&>();
    test_is_not_standard_layout<void * class_type::* volatile&&>();
    test_is_standard_layout<int class_type::* const volatile>();
    test_is_standard_layout<float class_type::* const volatile>();
    test_is_standard_layout<void * class_type::* const volatile>();
    test_is_not_standard_layout<int class_type::* const volatile&>();
    test_is_not_standard_layout<float class_type::* const volatile&>();
    test_is_not_standard_layout<void * class_type::* const volatile&>();
    test_is_not_standard_layout<int class_type::* const volatile&&>();
    test_is_not_standard_layout<float class_type::* const volatile&&>();
    test_is_not_standard_layout<void * class_type::* const volatile&&>();
    test_is_standard_layout<non_copyable>();
    test_is_standard_layout<non_moveable>();
    test_is_standard_layout<non_constructible>();
    test_is_standard_layout<tracked>();
    test_is_standard_layout<trap_constructible>();
    test_is_standard_layout<trap_implicit_conversion>();
    test_is_standard_layout<trap_comma>();
    test_is_standard_layout<trap_call>();
    test_is_standard_layout<trap_self_assign>();
    test_is_standard_layout<trap_deref>();
    test_is_standard_layout<trap_array_subscript>();

    test_is_standard_layout_function<void()>();
    test_is_standard_layout_function<void()&>();
    test_is_standard_layout_function<void() &&>();
    test_is_standard_layout_function<void() const>();
    test_is_standard_layout_function<void() const&>();
    test_is_standard_layout_function<void() const&&>();
    test_is_standard_layout_function<void() volatile>();
    test_is_standard_layout_function<void() volatile&>();
    test_is_standard_layout_function<void() volatile&&>();
    test_is_standard_layout_function<void() const volatile>();
    test_is_standard_layout_function<void() const volatile&>();
    test_is_standard_layout_function<void() const volatile&&>();
    test_is_standard_layout_function<void() noexcept>();
    test_is_standard_layout_function<void() & noexcept>();
    test_is_standard_layout_function<void() && noexcept>();
    test_is_standard_layout_function<void() const noexcept>();
    test_is_standard_layout_function<void() const & noexcept>();
    test_is_standard_layout_function<void() const && noexcept>();
    test_is_standard_layout_function<void() volatile noexcept>();
    test_is_standard_layout_function<void() volatile & noexcept>();
    test_is_standard_layout_function<void() volatile && noexcept>();
    test_is_standard_layout_function<void() const volatile noexcept>();
    test_is_standard_layout_function<void() const volatile & noexcept>();
    test_is_standard_layout_function<void() const volatile && noexcept>();

    test_is_standard_layout_function<void(int)>();
    test_is_standard_layout_function<void(int)&>();
    test_is_standard_layout_function<void(int) &&>();
    test_is_standard_layout_function<void(int) const>();
    test_is_standard_layout_function<void(int) const&>();
    test_is_standard_layout_function<void(int) const&&>();
    test_is_standard_layout_function<void(int) volatile>();
    test_is_standard_layout_function<void(int) volatile&>();
    test_is_standard_layout_function<void(int) volatile&&>();
    test_is_standard_layout_function<void(int) const volatile>();
    test_is_standard_layout_function<void(int) const volatile&>();
    test_is_standard_layout_function<void(int) const volatile&&>();
    test_is_standard_layout_function<void(int) noexcept>();
    test_is_standard_layout_function<void(int) & noexcept>();
    test_is_standard_layout_function<void(int) && noexcept>();
    test_is_standard_layout_function<void(int) const noexcept>();
    test_is_standard_layout_function<void(int) const & noexcept>();
    test_is_standard_layout_function<void(int) const && noexcept>();
    test_is_standard_layout_function<void(int) volatile noexcept>();
    test_is_standard_layout_function<void(int) volatile & noexcept>();
    test_is_standard_layout_function<void(int) volatile && noexcept>();
    test_is_standard_layout_function<void(int) const volatile noexcept>();
    test_is_standard_layout_function<void(int) const volatile & noexcept>();
    test_is_standard_layout_function<void(int) const volatile && noexcept>();

    test_is_standard_layout_function<void(...)>();
    test_is_standard_layout_function<void(...)&>();
    test_is_standard_layout_function<void(...) &&>();
    test_is_standard_layout_function<void(...) const>();
    test_is_standard_layout_function<void(...) const&>();
    test_is_standard_layout_function<void(...) const&&>();
    test_is_standard_layout_function<void(...) volatile>();
    test_is_standard_layout_function<void(...) volatile&>();
    test_is_standard_layout_function<void(...) volatile&&>();
    test_is_standard_layout_function<void(...) const volatile>();
    test_is_standard_layout_function<void(...) const volatile&>();
    test_is_standard_layout_function<void(...) const volatile&&>();
    test_is_standard_layout_function<void(...) noexcept>();
    test_is_standard_layout_function<void(...) & noexcept>();
    test_is_standard_layout_function<void(...) && noexcept>();
    test_is_standard_layout_function<void(...) const noexcept>();
    test_is_standard_layout_function<void(...) const & noexcept>();
    test_is_standard_layout_function<void(...) const && noexcept>();
    test_is_standard_layout_function<void(...) volatile noexcept>();
    test_is_standard_layout_function<void(...) volatile & noexcept>();
    test_is_standard_layout_function<void(...) volatile && noexcept>();
    test_is_standard_layout_function<void(...) const volatile noexcept>();
    test_is_standard_layout_function<void(...) const volatile & noexcept>();
    test_is_standard_layout_function<void(...) const volatile && noexcept>();

    test_is_standard_layout_function<void(int, ...)>();
    test_is_standard_layout_function<void(int, ...)&>();
    test_is_standard_layout_function<void(int, ...) &&>();
    test_is_standard_layout_function<void(int, ...) const>();
    test_is_standard_layout_function<void(int, ...) const&>();
    test_is_standard_layout_function<void(int, ...) const&&>();
    test_is_standard_layout_function<void(int, ...) volatile>();
    test_is_standard_layout_function<void(int, ...) volatile&>();
    test_is_standard_layout_function<void(int, ...) volatile&&>();
    test_is_standard_layout_function<void(int, ...) const volatile>();
    test_is_standard_layout_function<void(int, ...) const volatile&>();
    test_is_standard_layout_function<void(int, ...) const volatile&&>();
    test_is_standard_layout_function<void(int, ...) noexcept>();
    test_is_standard_layout_function<void(int, ...) & noexcept>();
    test_is_standard_layout_function<void(int, ...) && noexcept>();
    test_is_standard_layout_function<void(int, ...) const noexcept>();
    test_is_standard_layout_function<void(int, ...) const & noexcept>();
    test_is_standard_layout_function<void(int, ...) const && noexcept>();
    test_is_standard_layout_function<void(int, ...) volatile noexcept>();
    test_is_standard_layout_function<void(int, ...) volatile & noexcept>();
    test_is_standard_layout_function<void(int, ...) volatile && noexcept>();
    test_is_standard_layout_function<void(int, ...) const volatile noexcept>();
    test_is_standard_layout_function<void(int, ...) const volatile & noexcept>();
    test_is_standard_layout_function<void(int, ...) const volatile && noexcept>();

    test_is_standard_layout_function<int()>();
    test_is_standard_layout_function<int()&>();
    test_is_standard_layout_function<int() &&>();
    test_is_standard_layout_function<int() const>();
    test_is_standard_layout_function<int() const&>();
    test_is_standard_layout_function<int() const&&>();
    test_is_standard_layout_function<int() volatile>();
    test_is_standard_layout_function<int() volatile&>();
    test_is_standard_layout_function<int() volatile&&>();
    test_is_standard_layout_function<int() const volatile>();
    test_is_standard_layout_function<int() const volatile&>();
    test_is_standard_layout_function<int() const volatile&&>();
    test_is_standard_layout_function<int() noexcept>();
    test_is_standard_layout_function<int() & noexcept>();
    test_is_standard_layout_function<int() && noexcept>();
    test_is_standard_layout_function<int() const noexcept>();
    test_is_standard_layout_function<int() const & noexcept>();
    test_is_standard_layout_function<int() const && noexcept>();
    test_is_standard_layout_function<int() volatile noexcept>();
    test_is_standard_layout_function<int() volatile & noexcept>();
    test_is_standard_layout_function<int() volatile && noexcept>();
    test_is_standard_layout_function<int() const volatile noexcept>();
    test_is_standard_layout_function<int() const volatile & noexcept>();
    test_is_standard_layout_function<int() const volatile && noexcept>();

    test_is_standard_layout_function<int(int)>();
    test_is_standard_layout_function<int(int)&>();
    test_is_standard_layout_function<int(int) &&>();
    test_is_standard_layout_function<int(int) const>();
    test_is_standard_layout_function<int(int) const&>();
    test_is_standard_layout_function<int(int) const&&>();
    test_is_standard_layout_function<int(int) volatile>();
    test_is_standard_layout_function<int(int) volatile&>();
    test_is_standard_layout_function<int(int) volatile&&>();
    test_is_standard_layout_function<int(int) const volatile>();
    test_is_standard_layout_function<int(int) const volatile&>();
    test_is_standard_layout_function<int(int) const volatile&&>();
    test_is_standard_layout_function<int(int) noexcept>();
    test_is_standard_layout_function<int(int) & noexcept>();
    test_is_standard_layout_function<int(int) && noexcept>();
    test_is_standard_layout_function<int(int) const noexcept>();
    test_is_standard_layout_function<int(int) const & noexcept>();
    test_is_standard_layout_function<int(int) const && noexcept>();
    test_is_standard_layout_function<int(int) volatile noexcept>();
    test_is_standard_layout_function<int(int) volatile & noexcept>();
    test_is_standard_layout_function<int(int) volatile && noexcept>();
    test_is_standard_layout_function<int(int) const volatile noexcept>();
    test_is_standard_layout_function<int(int) const volatile & noexcept>();
    test_is_standard_layout_function<int(int) const volatile && noexcept>();

    test_is_standard_layout_function<int(...)>();
    test_is_standard_layout_function<int(...)&>();
    test_is_standard_layout_function<int(...) &&>();
    test_is_standard_layout_function<int(...) const>();
    test_is_standard_layout_function<int(...) const&>();
    test_is_standard_layout_function<int(...) const&&>();
    test_is_standard_layout_function<int(...) volatile>();
    test_is_standard_layout_function<int(...) volatile&>();
    test_is_standard_layout_function<int(...) volatile&&>();
    test_is_standard_layout_function<int(...) const volatile>();
    test_is_standard_layout_function<int(...) const volatile&>();
    test_is_standard_layout_function<int(...) const volatile&&>();
    test_is_standard_layout_function<int(...) noexcept>();
    test_is_standard_layout_function<int(...) & noexcept>();
    test_is_standard_layout_function<int(...) && noexcept>();
    test_is_standard_layout_function<int(...) const noexcept>();
    test_is_standard_layout_function<int(...) const & noexcept>();
    test_is_standard_layout_function<int(...) const && noexcept>();
    test_is_standard_layout_function<int(...) volatile noexcept>();
    test_is_standard_layout_function<int(...) volatile & noexcept>();
    test_is_standard_layout_function<int(...) volatile && noexcept>();
    test_is_standard_layout_function<int(...) const volatile noexcept>();
    test_is_standard_layout_function<int(...) const volatile & noexcept>();
    test_is_standard_layout_function<int(...) const volatile && noexcept>();

    test_is_standard_layout_function<int(int, ...)>();
    test_is_standard_layout_function<int(int, ...)&>();
    test_is_standard_layout_function<int(int, ...) &&>();
    test_is_standard_layout_function<int(int, ...) const>();
    test_is_standard_layout_function<int(int, ...) const&>();
    test_is_standard_layout_function<int(int, ...) const&&>();
    test_is_standard_layout_function<int(int, ...) volatile>();
    test_is_standard_layout_function<int(int, ...) volatile&>();
    test_is_standard_layout_function<int(int, ...) volatile&&>();
    test_is_standard_layout_function<int(int, ...) const volatile>();
    test_is_standard_layout_function<int(int, ...) const volatile&>();
    test_is_standard_layout_function<int(int, ...) const volatile&&>();
    test_is_standard_layout_function<int(int, ...) noexcept>();
    test_is_standard_layout_function<int(int, ...) & noexcept>();
    test_is_standard_layout_function<int(int, ...) && noexcept>();
    test_is_standard_layout_function<int(int, ...) const noexcept>();
    test_is_standard_layout_function<int(int, ...) const & noexcept>();
    test_is_standard_layout_function<int(int, ...) const && noexcept>();
    test_is_standard_layout_function<int(int, ...) volatile noexcept>();
    test_is_standard_layout_function<int(int, ...) volatile & noexcept>();
    test_is_standard_layout_function<int(int, ...) volatile && noexcept>();
    test_is_standard_layout_function<int(int, ...) const volatile noexcept>();
    test_is_standard_layout_function<int(int, ...) const volatile & noexcept>();
    test_is_standard_layout_function<int(int, ...) const volatile && noexcept>();

    test_is_standard_layout<void (*)()>();
    test_is_standard_layout<void (*)() noexcept>();

    test_is_standard_layout<void (*)(int)>();
    test_is_standard_layout<void (*)(int) noexcept>();

    test_is_standard_layout<void (*)(...)>();
    test_is_standard_layout<void (*)(...) noexcept>();

    test_is_standard_layout<void (*)(int, ...)>();
    test_is_standard_layout<void (*)(int, ...) noexcept>();

    test_is_standard_layout<int (*)()>();
    test_is_standard_layout<int (*)() noexcept>();

    test_is_standard_layout<int (*)(int)>();
    test_is_standard_layout<int (*)(int) noexcept>();

    test_is_standard_layout<int (*)(...)>();
    test_is_standard_layout<int (*)(...) noexcept>();

    test_is_standard_layout<int (*)(int, ...)>();
    test_is_standard_layout<int (*)(int, ...) noexcept>();

    test_is_not_standard_layout<void (&)()>();
    test_is_not_standard_layout<void (&)() noexcept>();

    test_is_not_standard_layout<void (&)(int)>();
    test_is_not_standard_layout<void (&)(int) noexcept>();

    test_is_not_standard_layout<void (&)(...)>();
    test_is_not_standard_layout<void (&)(...) noexcept>();

    test_is_not_standard_layout<void (&)(int, ...)>();
    test_is_not_standard_layout<void (&)(int, ...) noexcept>();

    test_is_not_standard_layout<int (&)()>();
    test_is_not_standard_layout<int (&)() noexcept>();

    test_is_not_standard_layout<int (&)(int)>();
    test_is_not_standard_layout<int (&)(int) noexcept>();

    test_is_not_standard_layout<int (&)(...)>();
    test_is_not_standard_layout<int (&)(...) noexcept>();

    test_is_not_standard_layout<int (&)(int, ...)>();
    test_is_not_standard_layout<int (&)(int, ...) noexcept>();

    test_is_not_standard_layout<void (&&)()>();
    test_is_not_standard_layout<void (&&)() noexcept>();

    test_is_not_standard_layout<void (&&)(int)>();
    test_is_not_standard_layout<void (&&)(int) noexcept>();

    test_is_not_standard_layout<void (&&)(...)>();
    test_is_not_standard_layout<void (&&)(...) noexcept>();

    test_is_not_standard_layout<void (&&)(int, ...)>();
    test_is_not_standard_layout<void (&&)(int, ...) noexcept>();

    test_is_not_standard_layout<int (&&)()>();
    test_is_not_standard_layout<int (&&)() noexcept>();

    test_is_not_standard_layout<int (&&)(int)>();
    test_is_not_standard_layout<int (&&)(int) noexcept>();

    test_is_not_standard_layout<int (&&)(...)>();
    test_is_not_standard_layout<int (&&)(...) noexcept>();

    test_is_not_standard_layout<int (&&)(int, ...)>();
    test_is_not_standard_layout<int (&&)(int, ...) noexcept>();

    test_is_standard_layout<void (class_type::*)()>();
    test_is_standard_layout<void (class_type::*)()&>();
    test_is_standard_layout<void (class_type::*)() &&>();
    test_is_standard_layout<void (class_type::*)() const>();
    test_is_standard_layout<void (class_type::*)() const&>();
    test_is_standard_layout<void (class_type::*)() const&&>();
    test_is_standard_layout<void (class_type::*)() noexcept>();
    test_is_standard_layout<void (class_type::*)() & noexcept>();
    test_is_standard_layout<void (class_type::*)() && noexcept>();
    test_is_standard_layout<void (class_type::*)() const noexcept>();
    test_is_standard_layout<void (class_type::*)() const & noexcept>();
    test_is_standard_layout<void (class_type::*)() const && noexcept>();

    test_is_standard_layout<void (class_type::*)(int)>();
    test_is_standard_layout<void (class_type::*)(int)&>();
    test_is_standard_layout<void (class_type::*)(int) &&>();
    test_is_standard_layout<void (class_type::*)(int) const>();
    test_is_standard_layout<void (class_type::*)(int) const&>();
    test_is_standard_layout<void (class_type::*)(int) const&&>();
    test_is_standard_layout<void (class_type::*)(int) noexcept>();
    test_is_standard_layout<void (class_type::*)(int) & noexcept>();
    test_is_standard_layout<void (class_type::*)(int) && noexcept>();
    test_is_standard_layout<void (class_type::*)(int) const noexcept>();
    test_is_standard_layout<void (class_type::*)(int) const & noexcept>();
    test_is_standard_layout<void (class_type::*)(int) const && noexcept>();

    test_is_standard_layout<void (class_type::*)(...)>();
    test_is_standard_layout<void (class_type::*)(...)&>();
    test_is_standard_layout<void (class_type::*)(...) &&>();
    test_is_standard_layout<void (class_type::*)(...) const>();
    test_is_standard_layout<void (class_type::*)(...) const&>();
    test_is_standard_layout<void (class_type::*)(...) const&&>();
    test_is_standard_layout<void (class_type::*)(...) noexcept>();
    test_is_standard_layout<void (class_type::*)(...) & noexcept>();
    test_is_standard_layout<void (class_type::*)(...) && noexcept>();
    test_is_standard_layout<void (class_type::*)(...) const noexcept>();
    test_is_standard_layout<void (class_type::*)(...) const & noexcept>();
    test_is_standard_layout<void (class_type::*)(...) const && noexcept>();

    test_is_standard_layout<void (class_type::*)(int, ...)>();
    test_is_standard_layout<void (class_type::*)(int, ...)&>();
    test_is_standard_layout<void (class_type::*)(int, ...) &&>();
    test_is_standard_layout<void (class_type::*)(int, ...) const>();
    test_is_standard_layout<void (class_type::*)(int, ...) const&>();
    test_is_standard_layout<void (class_type::*)(int, ...) const&&>();
    test_is_standard_layout<void (class_type::*)(int, ...) noexcept>();
    test_is_standard_layout<void (class_type::*)(int, ...) & noexcept>();
    test_is_standard_layout<void (class_type::*)(int, ...) && noexcept>();
    test_is_standard_layout<void (class_type::*)(int, ...) const noexcept>();
    test_is_standard_layout<void (class_type::*)(int, ...) const & noexcept>();
    test_is_standard_layout<void (class_type::*)(int, ...) const && noexcept>();

    test_is_standard_layout<int (class_type::*)()>();
    test_is_standard_layout<int (class_type::*)()&>();
    test_is_standard_layout<int (class_type::*)() &&>();
    test_is_standard_layout<int (class_type::*)() const>();
    test_is_standard_layout<int (class_type::*)() const&>();
    test_is_standard_layout<int (class_type::*)() const&&>();
    test_is_standard_layout<int (class_type::*)() noexcept>();
    test_is_standard_layout<int (class_type::*)() & noexcept>();
    test_is_standard_layout<int (class_type::*)() && noexcept>();
    test_is_standard_layout<int (class_type::*)() const noexcept>();
    test_is_standard_layout<int (class_type::*)() const & noexcept>();
    test_is_standard_layout<int (class_type::*)() const && noexcept>();

    test_is_standard_layout<int (class_type::*)(int)>();
    test_is_standard_layout<int (class_type::*)(int)&>();
    test_is_standard_layout<int (class_type::*)(int) &&>();
    test_is_standard_layout<int (class_type::*)(int) const>();
    test_is_standard_layout<int (class_type::*)(int) const&>();
    test_is_standard_layout<int (class_type::*)(int) const&&>();
    test_is_standard_layout<int (class_type::*)(int) noexcept>();
    test_is_standard_layout<int (class_type::*)(int) & noexcept>();
    test_is_standard_layout<int (class_type::*)(int) && noexcept>();
    test_is_standard_layout<int (class_type::*)(int) const noexcept>();
    test_is_standard_layout<int (class_type::*)(int) const & noexcept>();
    test_is_standard_layout<int (class_type::*)(int) const && noexcept>();

    test_is_standard_layout<int (class_type::*)(...)>();
    test_is_standard_layout<int (class_type::*)(...)&>();
    test_is_standard_layout<int (class_type::*)(...) &&>();
    test_is_standard_layout<int (class_type::*)(...) const>();
    test_is_standard_layout<int (class_type::*)(...) const&>();
    test_is_standard_layout<int (class_type::*)(...) const&&>();
    test_is_standard_layout<int (class_type::*)(...) noexcept>();
    test_is_standard_layout<int (class_type::*)(...) & noexcept>();
    test_is_standard_layout<int (class_type::*)(...) && noexcept>();
    test_is_standard_layout<int (class_type::*)(...) const noexcept>();
    test_is_standard_layout<int (class_type::*)(...) const & noexcept>();
    test_is_standard_layout<int (class_type::*)(...) const && noexcept>();

    test_is_standard_layout<int (class_type::*)(int, ...)>();
    test_is_standard_layout<int (class_type::*)(int, ...)&>();
    test_is_standard_layout<int (class_type::*)(int, ...) &&>();
    test_is_standard_layout<int (class_type::*)(int, ...) const>();
    test_is_standard_layout<int (class_type::*)(int, ...) const&>();
    test_is_standard_layout<int (class_type::*)(int, ...) const&&>();
    test_is_standard_layout<int (class_type::*)(int, ...) noexcept>();
    test_is_standard_layout<int (class_type::*)(int, ...) & noexcept>();
    test_is_standard_layout<int (class_type::*)(int, ...) && noexcept>();
    test_is_standard_layout<int (class_type::*)(int, ...) const noexcept>();
    test_is_standard_layout<int (class_type::*)(int, ...) const & noexcept>();
    test_is_standard_layout<int (class_type::*)(int, ...) const && noexcept>();
}
