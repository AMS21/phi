#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_trivially_copyable.hpp>
#include <type_traits>
#include <vector>

template <typename TypeT>
void test_is_trivially_copyable_impl()
{
#if PHI_HAS_WORKING_IS_TRIVIALLY_COPYABLE()
    STATIC_REQUIRE(phi::is_trivially_copyable<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_trivially_copyable<TypeT>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_trivially_copyable_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_not_trivially_copyable_v<TypeT>);
#    endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_trivially_copyable<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_trivially_copyable<TypeT>);

    // Standard compatibility
    STATIC_REQUIRE(std::is_trivially_copyable<TypeT>::value);
#endif
}

template <typename TypeT>
void test_is_not_trivially_copyable_impl()
{
#if PHI_HAS_WORKING_IS_TRIVIALLY_COPYABLE()
    STATIC_REQUIRE_FALSE(phi::is_trivially_copyable<TypeT>::value);
    STATIC_REQUIRE(phi::is_not_trivially_copyable<TypeT>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_trivially_copyable_v<TypeT>);
    STATIC_REQUIRE(phi::is_not_trivially_copyable_v<TypeT>);
#    endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_trivially_copyable<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_trivially_copyable<TypeT>);

    // Standard compatibility
    STATIC_REQUIRE_FALSE(std::is_trivially_copyable<TypeT>::value);
#endif
}

template <typename TypeT>
void test_is_trivially_copyable()
{
    test_is_trivially_copyable_impl<TypeT>();
    test_is_trivially_copyable_impl<const TypeT>();
    test_is_trivially_copyable_impl<volatile TypeT>();
    test_is_trivially_copyable_impl<const volatile TypeT>();
}

template <typename TypeT>
void test_is_not_trivially_copyable()
{
    test_is_not_trivially_copyable_impl<TypeT>();
    test_is_not_trivially_copyable_impl<const TypeT>();
    test_is_not_trivially_copyable_impl<volatile TypeT>();
    test_is_not_trivially_copyable_impl<const volatile TypeT>();
}

template <typename TypeT>
void test_is_trivially_copyable_gcc_compat()
{
    test_is_trivially_copyable_impl<TypeT>();
    test_is_trivially_copyable_impl<const TypeT>();
#if PHI_COMPILER_IS_BELOW(GCC, 10, 0, 0)
    test_is_not_trivially_copyable_impl<volatile TypeT>();
    test_is_not_trivially_copyable_impl<const volatile TypeT>();
#else
    test_is_trivially_copyable_impl<volatile TypeT>();
    test_is_trivially_copyable_impl<const volatile TypeT>();
#endif
}

template <typename TypeT>
void test_is_trivially_copyable_gcc_compat_volatile()
{
#if PHI_COMPILER_IS_BELOW(GCC, 10, 0, 0)
    test_is_not_trivially_copyable<TypeT>();
#else
    test_is_trivially_copyable<TypeT>();
#endif
}

struct A
{
    int i;
};

struct B
{
    int i;

    ~B()
    {
        i = 3;
    }
};

struct C
{
    C();
};

struct S
{
    S(S const&)            = default;
    S(S&&)                 = default;
    S& operator=(S const&) = delete;
    S& operator=(S&&)      = delete;
};

TEST_CASE("is_trivially_copyable")
{
    test_is_trivially_copyable<A>();
    test_is_not_trivially_copyable<A&>();
    test_is_not_trivially_copyable<const A&>();
    test_is_not_trivially_copyable<B>();
    test_is_not_trivially_copyable<B&>();
    test_is_not_trivially_copyable<const B&>();
    test_is_trivially_copyable<C>();
    test_is_not_trivially_copyable<C&>();
    test_is_not_trivially_copyable<const C&>();

    test_is_trivially_copyable<S>();

    test_is_not_trivially_copyable<void>();
    test_is_trivially_copyable_gcc_compat<phi::nullptr_t>();
    test_is_trivially_copyable_gcc_compat<bool>();
    test_is_trivially_copyable_gcc_compat<char>();
    test_is_trivially_copyable_gcc_compat<signed char>();
    test_is_trivially_copyable_gcc_compat<unsigned char>();
    test_is_trivially_copyable_gcc_compat<short>();
    test_is_trivially_copyable_gcc_compat<unsigned short>();
    test_is_trivially_copyable_gcc_compat<int>();
    test_is_trivially_copyable_gcc_compat<unsigned int>();
    test_is_trivially_copyable_gcc_compat<long>();
    test_is_trivially_copyable_gcc_compat<unsigned long>();
    test_is_trivially_copyable_gcc_compat<long long>();
    test_is_trivially_copyable_gcc_compat<unsigned long long>();
    test_is_trivially_copyable_gcc_compat<float>();
    test_is_trivially_copyable_gcc_compat<double>();
    test_is_trivially_copyable_gcc_compat<long double>();
    test_is_trivially_copyable_gcc_compat<char8_t>();
    test_is_trivially_copyable_gcc_compat<char16_t>();
    test_is_trivially_copyable_gcc_compat<char32_t>();
    test_is_trivially_copyable_gcc_compat<wchar_t>();

    test_is_trivially_copyable<phi::boolean>();
    test_is_trivially_copyable<phi::integer<signed char>>();
    test_is_trivially_copyable<phi::integer<unsigned char>>();
    test_is_trivially_copyable<phi::integer<short>>();
    test_is_trivially_copyable<phi::integer<unsigned short>>();
    test_is_trivially_copyable<phi::integer<int>>();
    test_is_trivially_copyable<phi::integer<unsigned int>>();
    test_is_trivially_copyable<phi::integer<long>>();
    test_is_trivially_copyable<phi::integer<unsigned long>>();
    test_is_trivially_copyable<phi::integer<long long>>();
    test_is_trivially_copyable<phi::integer<unsigned long long>>();
    test_is_trivially_copyable<phi::floating_point<float>>();
    test_is_trivially_copyable<phi::floating_point<double>>();
    test_is_trivially_copyable<phi::floating_point<long double>>();

    test_is_not_trivially_copyable<std::vector<int>>();
    test_is_not_trivially_copyable<phi::scope_ptr<int>>();

    test_is_not_trivially_copyable<int&>();
    test_is_not_trivially_copyable<const int&>();
    test_is_not_trivially_copyable<volatile int&>();
    test_is_not_trivially_copyable<const volatile int&>();
    test_is_not_trivially_copyable<int&&>();
    test_is_not_trivially_copyable<const int&&>();
    test_is_not_trivially_copyable<volatile int&&>();
    test_is_not_trivially_copyable<const volatile int&&>();
    test_is_trivially_copyable_gcc_compat<int*>();
    test_is_trivially_copyable_gcc_compat<const int*>();
    test_is_trivially_copyable_gcc_compat<volatile int*>();
    test_is_trivially_copyable_gcc_compat<const volatile int*>();
    test_is_trivially_copyable_gcc_compat<int**>();
    test_is_trivially_copyable_gcc_compat<const int**>();
    test_is_trivially_copyable_gcc_compat<volatile int**>();
    test_is_trivially_copyable_gcc_compat<const volatile int**>();
    test_is_not_trivially_copyable<int*&>();
    test_is_not_trivially_copyable<const int*&>();
    test_is_not_trivially_copyable<volatile int*&>();
    test_is_not_trivially_copyable<const volatile int*&>();
    test_is_not_trivially_copyable<int*&&>();
    test_is_not_trivially_copyable<const int*&&>();
    test_is_not_trivially_copyable<volatile int*&&>();
    test_is_not_trivially_copyable<const volatile int*&&>();
    test_is_trivially_copyable_gcc_compat<void*>();
    test_is_trivially_copyable_gcc_compat<char[3]>();
    test_is_trivially_copyable_gcc_compat<char[]>();
    test_is_trivially_copyable_gcc_compat<char* [3]>();
    test_is_trivially_copyable_gcc_compat<char*[]>();
    test_is_trivially_copyable_gcc_compat<int(*)[3]>();
    test_is_trivially_copyable_gcc_compat<int(*)[]>();
    test_is_not_trivially_copyable<int(&)[3]>();
    test_is_not_trivially_copyable<int(&)[]>();
    test_is_not_trivially_copyable<int(&&)[3]>();
    test_is_not_trivially_copyable<int(&&)[]>();
    test_is_trivially_copyable_gcc_compat<char[3][2]>();
    test_is_trivially_copyable_gcc_compat<char[][2]>();
    test_is_trivially_copyable_gcc_compat<char* [3][2]>();
    test_is_trivially_copyable_gcc_compat<char*[][2]>();
    test_is_trivially_copyable_gcc_compat<int(*)[3][2]>();
    test_is_trivially_copyable_gcc_compat<int(*)[][2]>();
    test_is_not_trivially_copyable<int(&)[3][2]>();
    test_is_not_trivially_copyable<int(&)[][2]>();
    test_is_not_trivially_copyable<int(&&)[3][2]>();
    test_is_not_trivially_copyable<int(&&)[][2]>();
    test_is_not_trivially_copyable<class_type>();
    test_is_not_trivially_copyable<class_type[]>();
    test_is_not_trivially_copyable<class_type[2]>();
    test_is_trivially_copyable<template_type<void>>();
    test_is_trivially_copyable<template_type<int>>();
    test_is_trivially_copyable<template_type<class_type>>();
    test_is_trivially_copyable<template_type<incomplete_type>>();
    test_is_trivially_copyable<variadic_template<>>();
    test_is_trivially_copyable<variadic_template<void>>();
    test_is_trivially_copyable<variadic_template<int>>();
    test_is_trivially_copyable<variadic_template<class_type>>();
    test_is_trivially_copyable<variadic_template<incomplete_type>>();
    test_is_trivially_copyable<variadic_template<int, void, class_type, volatile char[]>>();
    test_is_trivially_copyable<public_derived_from<base>>();
    test_is_trivially_copyable<public_derived_from<derived>>();
    test_is_not_trivially_copyable<public_derived_from<class_type>>();
    test_is_trivially_copyable<private_derived_from<base>>();
    test_is_trivially_copyable<private_derived_from<derived>>();
    test_is_not_trivially_copyable<private_derived_from<class_type>>();
    test_is_trivially_copyable<protected_derived_from<base>>();
    test_is_trivially_copyable<protected_derived_from<derived>>();
    test_is_not_trivially_copyable<protected_derived_from<class_type>>();
    test_is_trivially_copyable<union_type>();
    test_is_trivially_copyable<non_empty_union>();
    test_is_trivially_copyable<empty>();
    test_is_not_trivially_copyable<not_empty>();
    test_is_trivially_copyable<bit_zero>();
    test_is_trivially_copyable<bit_one>();
    test_is_trivially_copyable<base>();
    test_is_trivially_copyable<derived>();
    test_is_not_trivially_copyable<abstract>();
    test_is_not_trivially_copyable<public_abstract>();
    test_is_not_trivially_copyable<private_abstract>();
    test_is_not_trivially_copyable<protected_abstract>();
    test_is_not_trivially_copyable<abstract_template<int>>();
    test_is_trivially_copyable<abstract_template<double>>();
    test_is_not_trivially_copyable<abstract_template<class_type>>();
    test_is_not_trivially_copyable<abstract_template<incomplete_type>>();
    test_is_trivially_copyable<final_type>();
    test_is_trivially_copyable<public_destructor>();
    test_is_trivially_copyable<protected_destructor>();
    test_is_trivially_copyable<private_destructor>();
    test_is_not_trivially_copyable<virtual_public_destructor>();
    test_is_not_trivially_copyable<virtual_protected_destructor>();
    test_is_not_trivially_copyable<virtual_private_destructor>();
    test_is_not_trivially_copyable<pure_public_destructor>();
    test_is_not_trivially_copyable<pure_protected_destructor>();
    test_is_not_trivially_copyable<pure_private_destructor>();
#if PHI_COMPILER_IS(MSVC)
    test_is_not_trivially_copyable<deleted_public_destructor>();
    test_is_not_trivially_copyable<deleted_protected_destructor>();
    test_is_not_trivially_copyable<deleted_private_destructor>();
#else
    test_is_trivially_copyable<deleted_public_destructor>();
    test_is_trivially_copyable<deleted_protected_destructor>();
    test_is_trivially_copyable<deleted_private_destructor>();
#endif
    test_is_not_trivially_copyable<deleted_virtual_public_destructor>();
    test_is_not_trivially_copyable<deleted_virtual_protected_destructor>();
    test_is_not_trivially_copyable<deleted_virtual_private_destructor>();
    test_is_trivially_copyable_gcc_compat<Enum>();
    test_is_trivially_copyable_gcc_compat<EnumSigned>();
    test_is_trivially_copyable_gcc_compat<EnumUnsigned>();
    test_is_trivially_copyable_gcc_compat<EnumClass>();
    test_is_trivially_copyable_gcc_compat<EnumStruct>();
    test_is_not_trivially_copyable<function_type>();
    test_is_trivially_copyable_gcc_compat<function_ptr>();
    test_is_trivially_copyable_gcc_compat<member_object_ptr>();
    test_is_trivially_copyable_gcc_compat<member_function_ptr>();
    test_is_trivially_copyable_gcc_compat<int class_type::*>();
    test_is_trivially_copyable_gcc_compat<float class_type::*>();
    test_is_trivially_copyable_gcc_compat<void * class_type::*>();
    test_is_trivially_copyable_gcc_compat<int * class_type::*>();
    test_is_not_trivially_copyable<int class_type::*&>();
    test_is_not_trivially_copyable<float class_type::*&>();
    test_is_not_trivially_copyable<void * class_type::*&>();
    test_is_not_trivially_copyable<int * class_type::*&>();
    test_is_not_trivially_copyable<int class_type::*&&>();
    test_is_not_trivially_copyable<float class_type::*&&>();
    test_is_not_trivially_copyable<void * class_type::*&&>();
    test_is_not_trivially_copyable<int * class_type::*&&>();
    test_is_trivially_copyable_gcc_compat<int class_type::* const>();
    test_is_trivially_copyable_gcc_compat<float class_type::* const>();
    test_is_trivially_copyable_gcc_compat<void * class_type::* const>();
    test_is_not_trivially_copyable<int class_type::* const&>();
    test_is_not_trivially_copyable<float class_type::* const&>();
    test_is_not_trivially_copyable<void * class_type::* const&>();
    test_is_not_trivially_copyable<int class_type::* const&&>();
    test_is_not_trivially_copyable<float class_type::* const&&>();
    test_is_not_trivially_copyable<void * class_type::* const&&>();
    test_is_trivially_copyable_gcc_compat_volatile<int class_type::* volatile>();
    test_is_trivially_copyable_gcc_compat_volatile<float class_type::* volatile>();
    test_is_trivially_copyable_gcc_compat_volatile<void * class_type::* volatile>();
    test_is_not_trivially_copyable<int class_type::* volatile&>();
    test_is_not_trivially_copyable<float class_type::* volatile&>();
    test_is_not_trivially_copyable<void * class_type::* volatile&>();
    test_is_not_trivially_copyable<int class_type::* volatile&&>();
    test_is_not_trivially_copyable<float class_type::* volatile&&>();
    test_is_not_trivially_copyable<void * class_type::* volatile&&>();
    test_is_trivially_copyable_gcc_compat_volatile<int class_type::* const volatile>();
    test_is_trivially_copyable_gcc_compat_volatile<float class_type::* const volatile>();
    test_is_trivially_copyable_gcc_compat_volatile<void * class_type::* const volatile>();
    test_is_not_trivially_copyable<int class_type::* const volatile&>();
    test_is_not_trivially_copyable<float class_type::* const volatile&>();
    test_is_not_trivially_copyable<void * class_type::* const volatile&>();
    test_is_not_trivially_copyable<int class_type::* const volatile&&>();
    test_is_not_trivially_copyable<float class_type::* const volatile&&>();
    test_is_not_trivially_copyable<void * class_type::* const volatile&&>();
    test_is_trivially_copyable<non_copyable>();
    test_is_trivially_copyable<non_moveable>();
#if PHI_COMPILER_IS(MSVC)
    test_is_not_trivially_copyable<non_constructible>();
#else
    test_is_trivially_copyable<non_constructible>();
#endif
    test_is_not_trivially_copyable<tracked>();
    test_is_trivially_copyable<trap_constructible>();
    test_is_trivially_copyable<trap_implicit_conversion>();
    test_is_trivially_copyable<trap_comma>();
    test_is_trivially_copyable<trap_call>();
    test_is_not_trivially_copyable<trap_self_assign>();
    test_is_trivially_copyable<trap_deref>();
    test_is_trivially_copyable<trap_array_subscript>();

    test_is_not_trivially_copyable<void()>();
    test_is_not_trivially_copyable<void()&>();
    test_is_not_trivially_copyable<void() &&>();
    test_is_not_trivially_copyable<void() const>();
    test_is_not_trivially_copyable<void() const&>();
    test_is_not_trivially_copyable<void() const&&>();
    test_is_not_trivially_copyable<void() volatile>();
    test_is_not_trivially_copyable<void() volatile&>();
    test_is_not_trivially_copyable<void() volatile&&>();
    test_is_not_trivially_copyable<void() const volatile>();
    test_is_not_trivially_copyable<void() const volatile&>();
    test_is_not_trivially_copyable<void() const volatile&&>();
    test_is_not_trivially_copyable<void() noexcept>();
    test_is_not_trivially_copyable<void() & noexcept>();
    test_is_not_trivially_copyable<void() && noexcept>();
    test_is_not_trivially_copyable<void() const noexcept>();
    test_is_not_trivially_copyable<void() const & noexcept>();
    test_is_not_trivially_copyable<void() const && noexcept>();
    test_is_not_trivially_copyable<void() volatile noexcept>();
    test_is_not_trivially_copyable<void() volatile & noexcept>();
    test_is_not_trivially_copyable<void() volatile && noexcept>();
    test_is_not_trivially_copyable<void() const volatile noexcept>();
    test_is_not_trivially_copyable<void() const volatile & noexcept>();
    test_is_not_trivially_copyable<void() const volatile && noexcept>();

    test_is_not_trivially_copyable<void(int)>();
    test_is_not_trivially_copyable<void(int)&>();
    test_is_not_trivially_copyable<void(int) &&>();
    test_is_not_trivially_copyable<void(int) const>();
    test_is_not_trivially_copyable<void(int) const&>();
    test_is_not_trivially_copyable<void(int) const&&>();
    test_is_not_trivially_copyable<void(int) volatile>();
    test_is_not_trivially_copyable<void(int) volatile&>();
    test_is_not_trivially_copyable<void(int) volatile&&>();
    test_is_not_trivially_copyable<void(int) const volatile>();
    test_is_not_trivially_copyable<void(int) const volatile&>();
    test_is_not_trivially_copyable<void(int) const volatile&&>();
    test_is_not_trivially_copyable<void(int) noexcept>();
    test_is_not_trivially_copyable<void(int) & noexcept>();
    test_is_not_trivially_copyable<void(int) && noexcept>();
    test_is_not_trivially_copyable<void(int) const noexcept>();
    test_is_not_trivially_copyable<void(int) const & noexcept>();
    test_is_not_trivially_copyable<void(int) const && noexcept>();
    test_is_not_trivially_copyable<void(int) volatile noexcept>();
    test_is_not_trivially_copyable<void(int) volatile & noexcept>();
    test_is_not_trivially_copyable<void(int) volatile && noexcept>();
    test_is_not_trivially_copyable<void(int) const volatile noexcept>();
    test_is_not_trivially_copyable<void(int) const volatile & noexcept>();
    test_is_not_trivially_copyable<void(int) const volatile && noexcept>();

    test_is_not_trivially_copyable<void(...)>();
    test_is_not_trivially_copyable<void(...)&>();
    test_is_not_trivially_copyable<void(...) &&>();
    test_is_not_trivially_copyable<void(...) const>();
    test_is_not_trivially_copyable<void(...) const&>();
    test_is_not_trivially_copyable<void(...) const&&>();
    test_is_not_trivially_copyable<void(...) volatile>();
    test_is_not_trivially_copyable<void(...) volatile&>();
    test_is_not_trivially_copyable<void(...) volatile&&>();
    test_is_not_trivially_copyable<void(...) const volatile>();
    test_is_not_trivially_copyable<void(...) const volatile&>();
    test_is_not_trivially_copyable<void(...) const volatile&&>();
    test_is_not_trivially_copyable<void(...) noexcept>();
    test_is_not_trivially_copyable<void(...) & noexcept>();
    test_is_not_trivially_copyable<void(...) && noexcept>();
    test_is_not_trivially_copyable<void(...) const noexcept>();
    test_is_not_trivially_copyable<void(...) const & noexcept>();
    test_is_not_trivially_copyable<void(...) const && noexcept>();
    test_is_not_trivially_copyable<void(...) volatile noexcept>();
    test_is_not_trivially_copyable<void(...) volatile & noexcept>();
    test_is_not_trivially_copyable<void(...) volatile && noexcept>();
    test_is_not_trivially_copyable<void(...) const volatile noexcept>();
    test_is_not_trivially_copyable<void(...) const volatile & noexcept>();
    test_is_not_trivially_copyable<void(...) const volatile && noexcept>();

    test_is_not_trivially_copyable<void(int, ...)>();
    test_is_not_trivially_copyable<void(int, ...)&>();
    test_is_not_trivially_copyable<void(int, ...) &&>();
    test_is_not_trivially_copyable<void(int, ...) const>();
    test_is_not_trivially_copyable<void(int, ...) const&>();
    test_is_not_trivially_copyable<void(int, ...) const&&>();
    test_is_not_trivially_copyable<void(int, ...) volatile>();
    test_is_not_trivially_copyable<void(int, ...) volatile&>();
    test_is_not_trivially_copyable<void(int, ...) volatile&&>();
    test_is_not_trivially_copyable<void(int, ...) const volatile>();
    test_is_not_trivially_copyable<void(int, ...) const volatile&>();
    test_is_not_trivially_copyable<void(int, ...) const volatile&&>();
    test_is_not_trivially_copyable<void(int, ...) noexcept>();
    test_is_not_trivially_copyable<void(int, ...) & noexcept>();
    test_is_not_trivially_copyable<void(int, ...) && noexcept>();
    test_is_not_trivially_copyable<void(int, ...) const noexcept>();
    test_is_not_trivially_copyable<void(int, ...) const & noexcept>();
    test_is_not_trivially_copyable<void(int, ...) const && noexcept>();
    test_is_not_trivially_copyable<void(int, ...) volatile noexcept>();
    test_is_not_trivially_copyable<void(int, ...) volatile & noexcept>();
    test_is_not_trivially_copyable<void(int, ...) volatile && noexcept>();
    test_is_not_trivially_copyable<void(int, ...) const volatile noexcept>();
    test_is_not_trivially_copyable<void(int, ...) const volatile & noexcept>();
    test_is_not_trivially_copyable<void(int, ...) const volatile && noexcept>();

    test_is_not_trivially_copyable<int()>();
    test_is_not_trivially_copyable<int()&>();
    test_is_not_trivially_copyable<int() &&>();
    test_is_not_trivially_copyable<int() const>();
    test_is_not_trivially_copyable<int() const&>();
    test_is_not_trivially_copyable<int() const&&>();
    test_is_not_trivially_copyable<int() volatile>();
    test_is_not_trivially_copyable<int() volatile&>();
    test_is_not_trivially_copyable<int() volatile&&>();
    test_is_not_trivially_copyable<int() const volatile>();
    test_is_not_trivially_copyable<int() const volatile&>();
    test_is_not_trivially_copyable<int() const volatile&&>();
    test_is_not_trivially_copyable<int() noexcept>();
    test_is_not_trivially_copyable<int() & noexcept>();
    test_is_not_trivially_copyable<int() && noexcept>();
    test_is_not_trivially_copyable<int() const noexcept>();
    test_is_not_trivially_copyable<int() const & noexcept>();
    test_is_not_trivially_copyable<int() const && noexcept>();
    test_is_not_trivially_copyable<int() volatile noexcept>();
    test_is_not_trivially_copyable<int() volatile & noexcept>();
    test_is_not_trivially_copyable<int() volatile && noexcept>();
    test_is_not_trivially_copyable<int() const volatile noexcept>();
    test_is_not_trivially_copyable<int() const volatile & noexcept>();
    test_is_not_trivially_copyable<int() const volatile && noexcept>();

    test_is_not_trivially_copyable<int(int)>();
    test_is_not_trivially_copyable<int(int)&>();
    test_is_not_trivially_copyable<int(int) &&>();
    test_is_not_trivially_copyable<int(int) const>();
    test_is_not_trivially_copyable<int(int) const&>();
    test_is_not_trivially_copyable<int(int) const&&>();
    test_is_not_trivially_copyable<int(int) volatile>();
    test_is_not_trivially_copyable<int(int) volatile&>();
    test_is_not_trivially_copyable<int(int) volatile&&>();
    test_is_not_trivially_copyable<int(int) const volatile>();
    test_is_not_trivially_copyable<int(int) const volatile&>();
    test_is_not_trivially_copyable<int(int) const volatile&&>();
    test_is_not_trivially_copyable<int(int) noexcept>();
    test_is_not_trivially_copyable<int(int) & noexcept>();
    test_is_not_trivially_copyable<int(int) && noexcept>();
    test_is_not_trivially_copyable<int(int) const noexcept>();
    test_is_not_trivially_copyable<int(int) const & noexcept>();
    test_is_not_trivially_copyable<int(int) const && noexcept>();
    test_is_not_trivially_copyable<int(int) volatile noexcept>();
    test_is_not_trivially_copyable<int(int) volatile & noexcept>();
    test_is_not_trivially_copyable<int(int) volatile && noexcept>();
    test_is_not_trivially_copyable<int(int) const volatile noexcept>();
    test_is_not_trivially_copyable<int(int) const volatile & noexcept>();
    test_is_not_trivially_copyable<int(int) const volatile && noexcept>();

    test_is_not_trivially_copyable<int(...)>();
    test_is_not_trivially_copyable<int(...)&>();
    test_is_not_trivially_copyable<int(...) &&>();
    test_is_not_trivially_copyable<int(...) const>();
    test_is_not_trivially_copyable<int(...) const&>();
    test_is_not_trivially_copyable<int(...) const&&>();
    test_is_not_trivially_copyable<int(...) volatile>();
    test_is_not_trivially_copyable<int(...) volatile&>();
    test_is_not_trivially_copyable<int(...) volatile&&>();
    test_is_not_trivially_copyable<int(...) const volatile>();
    test_is_not_trivially_copyable<int(...) const volatile&>();
    test_is_not_trivially_copyable<int(...) const volatile&&>();
    test_is_not_trivially_copyable<int(...) noexcept>();
    test_is_not_trivially_copyable<int(...) & noexcept>();
    test_is_not_trivially_copyable<int(...) && noexcept>();
    test_is_not_trivially_copyable<int(...) const noexcept>();
    test_is_not_trivially_copyable<int(...) const & noexcept>();
    test_is_not_trivially_copyable<int(...) const && noexcept>();
    test_is_not_trivially_copyable<int(...) volatile noexcept>();
    test_is_not_trivially_copyable<int(...) volatile & noexcept>();
    test_is_not_trivially_copyable<int(...) volatile && noexcept>();
    test_is_not_trivially_copyable<int(...) const volatile noexcept>();
    test_is_not_trivially_copyable<int(...) const volatile & noexcept>();
    test_is_not_trivially_copyable<int(...) const volatile && noexcept>();

    test_is_not_trivially_copyable<int(int, ...)>();
    test_is_not_trivially_copyable<int(int, ...)&>();
    test_is_not_trivially_copyable<int(int, ...) &&>();
    test_is_not_trivially_copyable<int(int, ...) const>();
    test_is_not_trivially_copyable<int(int, ...) const&>();
    test_is_not_trivially_copyable<int(int, ...) const&&>();
    test_is_not_trivially_copyable<int(int, ...) volatile>();
    test_is_not_trivially_copyable<int(int, ...) volatile&>();
    test_is_not_trivially_copyable<int(int, ...) volatile&&>();
    test_is_not_trivially_copyable<int(int, ...) const volatile>();
    test_is_not_trivially_copyable<int(int, ...) const volatile&>();
    test_is_not_trivially_copyable<int(int, ...) const volatile&&>();
    test_is_not_trivially_copyable<int(int, ...) noexcept>();
    test_is_not_trivially_copyable<int(int, ...) & noexcept>();
    test_is_not_trivially_copyable<int(int, ...) && noexcept>();
    test_is_not_trivially_copyable<int(int, ...) const noexcept>();
    test_is_not_trivially_copyable<int(int, ...) const & noexcept>();
    test_is_not_trivially_copyable<int(int, ...) const && noexcept>();
    test_is_not_trivially_copyable<int(int, ...) volatile noexcept>();
    test_is_not_trivially_copyable<int(int, ...) volatile & noexcept>();
    test_is_not_trivially_copyable<int(int, ...) volatile && noexcept>();
    test_is_not_trivially_copyable<int(int, ...) const volatile noexcept>();
    test_is_not_trivially_copyable<int(int, ...) const volatile & noexcept>();
    test_is_not_trivially_copyable<int(int, ...) const volatile && noexcept>();

    test_is_trivially_copyable_gcc_compat<void (*)()>();
    test_is_trivially_copyable_gcc_compat<void (*)() noexcept>();

    test_is_trivially_copyable_gcc_compat<void (*)(int)>();
    test_is_trivially_copyable_gcc_compat<void (*)(int) noexcept>();

    test_is_trivially_copyable_gcc_compat<void (*)(...)>();
    test_is_trivially_copyable_gcc_compat<void (*)(...) noexcept>();

    test_is_trivially_copyable_gcc_compat<void (*)(int, ...)>();
    test_is_trivially_copyable_gcc_compat<void (*)(int, ...) noexcept>();

    test_is_trivially_copyable_gcc_compat<int (*)()>();
    test_is_trivially_copyable_gcc_compat<int (*)() noexcept>();

    test_is_trivially_copyable_gcc_compat<int (*)(int)>();
    test_is_trivially_copyable_gcc_compat<int (*)(int) noexcept>();

    test_is_trivially_copyable_gcc_compat<int (*)(...)>();
    test_is_trivially_copyable_gcc_compat<int (*)(...) noexcept>();

    test_is_trivially_copyable_gcc_compat<int (*)(int, ...)>();
    test_is_trivially_copyable_gcc_compat<int (*)(int, ...) noexcept>();

    test_is_not_trivially_copyable<void (&)()>();
    test_is_not_trivially_copyable<void (&)() noexcept>();

    test_is_not_trivially_copyable<void (&)(int)>();
    test_is_not_trivially_copyable<void (&)(int) noexcept>();

    test_is_not_trivially_copyable<void (&)(...)>();
    test_is_not_trivially_copyable<void (&)(...) noexcept>();

    test_is_not_trivially_copyable<void (&)(int, ...)>();
    test_is_not_trivially_copyable<void (&)(int, ...) noexcept>();

    test_is_not_trivially_copyable<int (&)()>();
    test_is_not_trivially_copyable<int (&)() noexcept>();

    test_is_not_trivially_copyable<int (&)(int)>();
    test_is_not_trivially_copyable<int (&)(int) noexcept>();

    test_is_not_trivially_copyable<int (&)(...)>();
    test_is_not_trivially_copyable<int (&)(...) noexcept>();

    test_is_not_trivially_copyable<int (&)(int, ...)>();
    test_is_not_trivially_copyable<int (&)(int, ...) noexcept>();

    test_is_not_trivially_copyable<void (&&)()>();
    test_is_not_trivially_copyable<void (&&)() noexcept>();

    test_is_not_trivially_copyable<void (&&)(int)>();
    test_is_not_trivially_copyable<void (&&)(int) noexcept>();

    test_is_not_trivially_copyable<void (&&)(...)>();
    test_is_not_trivially_copyable<void (&&)(...) noexcept>();

    test_is_not_trivially_copyable<void (&&)(int, ...)>();
    test_is_not_trivially_copyable<void (&&)(int, ...) noexcept>();

    test_is_not_trivially_copyable<int (&&)()>();
    test_is_not_trivially_copyable<int (&&)() noexcept>();

    test_is_not_trivially_copyable<int (&&)(int)>();
    test_is_not_trivially_copyable<int (&&)(int) noexcept>();

    test_is_not_trivially_copyable<int (&&)(...)>();
    test_is_not_trivially_copyable<int (&&)(...) noexcept>();

    test_is_not_trivially_copyable<int (&&)(int, ...)>();
    test_is_not_trivially_copyable<int (&&)(int, ...) noexcept>();

    test_is_trivially_copyable_gcc_compat<void (class_type::*)()>();
    test_is_trivially_copyable_gcc_compat<void (class_type::*)()&>();
    test_is_trivially_copyable_gcc_compat<void (class_type::*)() &&>();
    test_is_trivially_copyable_gcc_compat<void (class_type::*)() const>();
    test_is_trivially_copyable_gcc_compat<void (class_type::*)() const&>();
    test_is_trivially_copyable_gcc_compat<void (class_type::*)() const&&>();
    test_is_trivially_copyable_gcc_compat<void (class_type::*)() noexcept>();
    test_is_trivially_copyable_gcc_compat<void (class_type::*)() & noexcept>();
    test_is_trivially_copyable_gcc_compat<void (class_type::*)() && noexcept>();
    test_is_trivially_copyable_gcc_compat<void (class_type::*)() const noexcept>();
    test_is_trivially_copyable_gcc_compat<void (class_type::*)() const & noexcept>();
    test_is_trivially_copyable_gcc_compat<void (class_type::*)() const && noexcept>();

    test_is_trivially_copyable_gcc_compat<void (class_type::*)(int)>();
    test_is_trivially_copyable_gcc_compat<void (class_type::*)(int)&>();
    test_is_trivially_copyable_gcc_compat<void (class_type::*)(int) &&>();
    test_is_trivially_copyable_gcc_compat<void (class_type::*)(int) const>();
    test_is_trivially_copyable_gcc_compat<void (class_type::*)(int) const&>();
    test_is_trivially_copyable_gcc_compat<void (class_type::*)(int) const&&>();
    test_is_trivially_copyable_gcc_compat<void (class_type::*)(int) noexcept>();
    test_is_trivially_copyable_gcc_compat<void (class_type::*)(int) & noexcept>();
    test_is_trivially_copyable_gcc_compat<void (class_type::*)(int) && noexcept>();
    test_is_trivially_copyable_gcc_compat<void (class_type::*)(int) const noexcept>();
    test_is_trivially_copyable_gcc_compat<void (class_type::*)(int) const & noexcept>();
    test_is_trivially_copyable_gcc_compat<void (class_type::*)(int) const && noexcept>();

    test_is_trivially_copyable_gcc_compat<void (class_type::*)(...)>();
    test_is_trivially_copyable_gcc_compat<void (class_type::*)(...)&>();
    test_is_trivially_copyable_gcc_compat<void (class_type::*)(...) &&>();
    test_is_trivially_copyable_gcc_compat<void (class_type::*)(...) const>();
    test_is_trivially_copyable_gcc_compat<void (class_type::*)(...) const&>();
    test_is_trivially_copyable_gcc_compat<void (class_type::*)(...) const&&>();
    test_is_trivially_copyable_gcc_compat<void (class_type::*)(...) noexcept>();
    test_is_trivially_copyable_gcc_compat<void (class_type::*)(...) & noexcept>();
    test_is_trivially_copyable_gcc_compat<void (class_type::*)(...) && noexcept>();
    test_is_trivially_copyable_gcc_compat<void (class_type::*)(...) const noexcept>();
    test_is_trivially_copyable_gcc_compat<void (class_type::*)(...) const & noexcept>();
    test_is_trivially_copyable_gcc_compat<void (class_type::*)(...) const && noexcept>();

    test_is_trivially_copyable_gcc_compat<void (class_type::*)(int, ...)>();
    test_is_trivially_copyable_gcc_compat<void (class_type::*)(int, ...)&>();
    test_is_trivially_copyable_gcc_compat<void (class_type::*)(int, ...) &&>();
    test_is_trivially_copyable_gcc_compat<void (class_type::*)(int, ...) const>();
    test_is_trivially_copyable_gcc_compat<void (class_type::*)(int, ...) const&>();
    test_is_trivially_copyable_gcc_compat<void (class_type::*)(int, ...) const&&>();
    test_is_trivially_copyable_gcc_compat<void (class_type::*)(int, ...) noexcept>();
    test_is_trivially_copyable_gcc_compat<void (class_type::*)(int, ...) & noexcept>();
    test_is_trivially_copyable_gcc_compat<void (class_type::*)(int, ...) && noexcept>();
    test_is_trivially_copyable_gcc_compat<void (class_type::*)(int, ...) const noexcept>();
    test_is_trivially_copyable_gcc_compat<void (class_type::*)(int, ...) const & noexcept>();
    test_is_trivially_copyable_gcc_compat<void (class_type::*)(int, ...) const && noexcept>();

    test_is_trivially_copyable_gcc_compat<int (class_type::*)()>();
    test_is_trivially_copyable_gcc_compat<int (class_type::*)()&>();
    test_is_trivially_copyable_gcc_compat<int (class_type::*)() &&>();
    test_is_trivially_copyable_gcc_compat<int (class_type::*)() const>();
    test_is_trivially_copyable_gcc_compat<int (class_type::*)() const&>();
    test_is_trivially_copyable_gcc_compat<int (class_type::*)() const&&>();
    test_is_trivially_copyable_gcc_compat<int (class_type::*)() noexcept>();
    test_is_trivially_copyable_gcc_compat<int (class_type::*)() & noexcept>();
    test_is_trivially_copyable_gcc_compat<int (class_type::*)() && noexcept>();
    test_is_trivially_copyable_gcc_compat<int (class_type::*)() const noexcept>();
    test_is_trivially_copyable_gcc_compat<int (class_type::*)() const & noexcept>();
    test_is_trivially_copyable_gcc_compat<int (class_type::*)() const && noexcept>();

    test_is_trivially_copyable_gcc_compat<int (class_type::*)(int)>();
    test_is_trivially_copyable_gcc_compat<int (class_type::*)(int)&>();
    test_is_trivially_copyable_gcc_compat<int (class_type::*)(int) &&>();
    test_is_trivially_copyable_gcc_compat<int (class_type::*)(int) const>();
    test_is_trivially_copyable_gcc_compat<int (class_type::*)(int) const&>();
    test_is_trivially_copyable_gcc_compat<int (class_type::*)(int) const&&>();
    test_is_trivially_copyable_gcc_compat<int (class_type::*)(int) noexcept>();
    test_is_trivially_copyable_gcc_compat<int (class_type::*)(int) & noexcept>();
    test_is_trivially_copyable_gcc_compat<int (class_type::*)(int) && noexcept>();
    test_is_trivially_copyable_gcc_compat<int (class_type::*)(int) const noexcept>();
    test_is_trivially_copyable_gcc_compat<int (class_type::*)(int) const & noexcept>();
    test_is_trivially_copyable_gcc_compat<int (class_type::*)(int) const && noexcept>();

    test_is_trivially_copyable_gcc_compat<int (class_type::*)(...)>();
    test_is_trivially_copyable_gcc_compat<int (class_type::*)(...)&>();
    test_is_trivially_copyable_gcc_compat<int (class_type::*)(...) &&>();
    test_is_trivially_copyable_gcc_compat<int (class_type::*)(...) const>();
    test_is_trivially_copyable_gcc_compat<int (class_type::*)(...) const&>();
    test_is_trivially_copyable_gcc_compat<int (class_type::*)(...) const&&>();
    test_is_trivially_copyable_gcc_compat<int (class_type::*)(...) noexcept>();
    test_is_trivially_copyable_gcc_compat<int (class_type::*)(...) & noexcept>();
    test_is_trivially_copyable_gcc_compat<int (class_type::*)(...) && noexcept>();
    test_is_trivially_copyable_gcc_compat<int (class_type::*)(...) const noexcept>();
    test_is_trivially_copyable_gcc_compat<int (class_type::*)(...) const & noexcept>();
    test_is_trivially_copyable_gcc_compat<int (class_type::*)(...) const && noexcept>();

    test_is_trivially_copyable_gcc_compat<int (class_type::*)(int, ...)>();
    test_is_trivially_copyable_gcc_compat<int (class_type::*)(int, ...)&>();
    test_is_trivially_copyable_gcc_compat<int (class_type::*)(int, ...) &&>();
    test_is_trivially_copyable_gcc_compat<int (class_type::*)(int, ...) const>();
    test_is_trivially_copyable_gcc_compat<int (class_type::*)(int, ...) const&>();
    test_is_trivially_copyable_gcc_compat<int (class_type::*)(int, ...) const&&>();
    test_is_trivially_copyable_gcc_compat<int (class_type::*)(int, ...) noexcept>();
    test_is_trivially_copyable_gcc_compat<int (class_type::*)(int, ...) & noexcept>();
    test_is_trivially_copyable_gcc_compat<int (class_type::*)(int, ...) && noexcept>();
    test_is_trivially_copyable_gcc_compat<int (class_type::*)(int, ...) const noexcept>();
    test_is_trivially_copyable_gcc_compat<int (class_type::*)(int, ...) const & noexcept>();
    test_is_trivially_copyable_gcc_compat<int (class_type::*)(int, ...) const && noexcept>();
}
