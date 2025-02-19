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
#include <phi/type_traits/is_destructible.hpp>
#include <phi/type_traits/is_nothrow_destructible.hpp>
#include <type_traits>
#include <vector>

template <typename TypeT>
void test_is_nothrow_destructible_impl()
{
    STATIC_REQUIRE(phi::is_nothrow_destructible<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_nothrow_destructible<TypeT>::value);
    STATIC_REQUIRE(phi::is_destructible<TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_nothrow_destructible_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_not_nothrow_destructible_v<TypeT>);
    STATIC_REQUIRE(phi::is_destructible_v<TypeT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_nothrow_destructible<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_nothrow_destructible<TypeT>);

    // Standard compatibility
    STATIC_REQUIRE(std::is_nothrow_destructible<TypeT>::value);
    STATIC_REQUIRE(std::is_destructible<TypeT>::value);
}

template <typename TypeT>
void test_is_not_nothrow_destructible_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_nothrow_destructible<TypeT>::value);
    STATIC_REQUIRE(phi::is_not_nothrow_destructible<TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_nothrow_destructible_v<TypeT>);
    STATIC_REQUIRE(phi::is_not_nothrow_destructible_v<TypeT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_nothrow_destructible<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_nothrow_destructible<TypeT>);

    // Standard compatibility
    STATIC_REQUIRE_FALSE(std::is_nothrow_destructible<TypeT>::value);
}

template <typename TypeT>
void test_is_nothrow_destructible()
{
    test_is_nothrow_destructible_impl<TypeT>();
    test_is_nothrow_destructible_impl<const TypeT>();
    test_is_nothrow_destructible_impl<volatile TypeT>();
    test_is_nothrow_destructible_impl<const volatile TypeT>();
}

template <typename TypeT>
void test_is_not_nothrow_destructible()
{
    test_is_not_nothrow_destructible_impl<TypeT>();
    test_is_not_nothrow_destructible_impl<const TypeT>();
    test_is_not_nothrow_destructible_impl<volatile TypeT>();
    test_is_not_nothrow_destructible_impl<const volatile TypeT>();
}

PHI_CLANG_SUPPRESS_WARNING_PUSH()
PHI_CLANG_SUPPRESS_WARNING("-Wnon-virtual-dtor")
PHI_GCC_SUPPRESS_WARNING_PUSH()
PHI_GCC_SUPPRESS_WARNING("-Wnon-virtual-dtor")
PHI_MSVC_SUPPRESS_WARNING_PUSH()
PHI_MSVC_SUPPRESS_WARNING(
        5204) // 'name': class has virtual functions, but its trivial destructor is not virtual; instances of objects derived from this class may not be destructed correctly

// NOLINTNEXTLINE(cppcoreguidelines-virtual-class-destructor,readability-identifier-naming)
class A
{
    virtual void foo() = 0;
};

struct B
{
    ~B() noexcept(false);
};

struct C
{
    ~C() noexcept;
};

struct D
{
    ~D() = default;
};

struct E
{
    ~E() = delete;
};

PHI_MSVC_SUPPRESS_WARNING_POP()
PHI_GCC_SUPPRESS_WARNING_POP()
PHI_CLANG_SUPPRESS_WARNING_POP()

TEST_CASE("is_nothrow_destructible")
{
    test_is_nothrow_destructible<A>();
    test_is_not_nothrow_destructible<B>();
    test_is_nothrow_destructible<C>();
    test_is_nothrow_destructible<D>();
    test_is_not_nothrow_destructible<E>();

    test_is_not_nothrow_destructible<void>();
#if PHI_COMPILER_IS(MSVC)
    SKIP_CHECK();
#else
    test_is_nothrow_destructible<phi::nullptr_t>();
#endif
    test_is_nothrow_destructible<bool>();
    test_is_nothrow_destructible<char>();
    test_is_nothrow_destructible<signed char>();
    test_is_nothrow_destructible<unsigned char>();
    test_is_nothrow_destructible<short>();
    test_is_nothrow_destructible<unsigned short>();
    test_is_nothrow_destructible<int>();
    test_is_nothrow_destructible<unsigned int>();
    test_is_nothrow_destructible<long>();
    test_is_nothrow_destructible<unsigned long>();
    test_is_nothrow_destructible<long long>();
    test_is_nothrow_destructible<unsigned long long>();
    test_is_nothrow_destructible<float>();
    test_is_nothrow_destructible<double>();
    test_is_nothrow_destructible<long double>();
    test_is_nothrow_destructible<char8_t>();
    test_is_nothrow_destructible<char16_t>();
    test_is_nothrow_destructible<char32_t>();
    test_is_nothrow_destructible<wchar_t>();

    test_is_nothrow_destructible<phi::boolean>();
    test_is_nothrow_destructible<phi::integer<signed char>>();
    test_is_nothrow_destructible<phi::integer<unsigned char>>();
    test_is_nothrow_destructible<phi::integer<short>>();
    test_is_nothrow_destructible<phi::integer<unsigned short>>();
    test_is_nothrow_destructible<phi::integer<int>>();
    test_is_nothrow_destructible<phi::integer<unsigned int>>();
    test_is_nothrow_destructible<phi::integer<long>>();
    test_is_nothrow_destructible<phi::integer<unsigned long>>();
    test_is_nothrow_destructible<phi::integer<long long>>();
    test_is_nothrow_destructible<phi::integer<unsigned long long>>();
    test_is_nothrow_destructible<phi::floating_point<float>>();
    test_is_nothrow_destructible<phi::floating_point<double>>();
    test_is_nothrow_destructible<phi::floating_point<long double>>();

    test_is_nothrow_destructible<std::vector<int>>();
    test_is_nothrow_destructible<phi::scope_ptr<int>>();

    test_is_nothrow_destructible<int&>();
    test_is_nothrow_destructible<const int&>();
    test_is_nothrow_destructible<volatile int&>();
    test_is_nothrow_destructible<const volatile int&>();
    test_is_nothrow_destructible<int&&>();
    test_is_nothrow_destructible<const int&&>();
    test_is_nothrow_destructible<volatile int&&>();
    test_is_nothrow_destructible<const volatile int&&>();
    test_is_nothrow_destructible<int*>();
    test_is_nothrow_destructible<const int*>();
    test_is_nothrow_destructible<volatile int*>();
    test_is_nothrow_destructible<const volatile int*>();
    test_is_nothrow_destructible<int**>();
    test_is_nothrow_destructible<const int**>();
    test_is_nothrow_destructible<volatile int**>();
    test_is_nothrow_destructible<const volatile int**>();
    test_is_nothrow_destructible<int*&>();
    test_is_nothrow_destructible<const int*&>();
    test_is_nothrow_destructible<volatile int*&>();
    test_is_nothrow_destructible<const volatile int*&>();
    test_is_nothrow_destructible<int*&&>();
    test_is_nothrow_destructible<const int*&&>();
    test_is_nothrow_destructible<volatile int*&&>();
    test_is_nothrow_destructible<const volatile int*&&>();
    test_is_nothrow_destructible<void*>();
    test_is_nothrow_destructible<char[3]>();
    test_is_not_nothrow_destructible<char[]>();
    test_is_nothrow_destructible<char* [3]>();
    test_is_not_nothrow_destructible<char*[]>();
    test_is_nothrow_destructible<int(*)[3]>();
    test_is_nothrow_destructible<int(*)[]>();
    test_is_nothrow_destructible<int(&)[3]>();
    test_is_nothrow_destructible<int(&)[]>();
    test_is_nothrow_destructible<int(&&)[3]>();
    test_is_nothrow_destructible<int(&&)[]>();
    test_is_nothrow_destructible<char[3][2]>();
    test_is_not_nothrow_destructible<char[][2]>();
    test_is_nothrow_destructible<char* [3][2]>();
    test_is_not_nothrow_destructible<char*[][2]>();
    test_is_nothrow_destructible<int(*)[3][2]>();
    test_is_nothrow_destructible<int(*)[][2]>();
    test_is_nothrow_destructible<int(&)[3][2]>();
    test_is_nothrow_destructible<int(&)[][2]>();
    test_is_nothrow_destructible<int(&&)[3][2]>();
    test_is_nothrow_destructible<int(&&)[][2]>();
    test_is_nothrow_destructible<class_type>();
    test_is_not_nothrow_destructible<class_type[]>();
    test_is_nothrow_destructible<class_type[2]>();
    test_is_nothrow_destructible<template_type<void>>();
    test_is_nothrow_destructible<template_type<int>>();
    test_is_nothrow_destructible<template_type<class_type>>();
    test_is_nothrow_destructible<template_type<incomplete_type>>();
    test_is_nothrow_destructible<variadic_template<>>();
    test_is_nothrow_destructible<variadic_template<void>>();
    test_is_nothrow_destructible<variadic_template<int>>();
    test_is_nothrow_destructible<variadic_template<class_type>>();
    test_is_nothrow_destructible<variadic_template<incomplete_type>>();
    test_is_nothrow_destructible<variadic_template<int, void, class_type, volatile char[]>>();
    test_is_nothrow_destructible<public_derived_from<base>>();
    test_is_nothrow_destructible<public_derived_from<derived>>();
    test_is_nothrow_destructible<public_derived_from<class_type>>();
    test_is_nothrow_destructible<private_derived_from<base>>();
    test_is_nothrow_destructible<private_derived_from<derived>>();
    test_is_nothrow_destructible<private_derived_from<class_type>>();
    test_is_nothrow_destructible<protected_derived_from<base>>();
    test_is_nothrow_destructible<protected_derived_from<derived>>();
    test_is_nothrow_destructible<protected_derived_from<class_type>>();
    test_is_nothrow_destructible<union_type>();
    test_is_nothrow_destructible<non_empty_union>();
    test_is_nothrow_destructible<empty>();
    test_is_nothrow_destructible<not_empty>();
    test_is_nothrow_destructible<bit_zero>();
    test_is_nothrow_destructible<bit_one>();
    test_is_nothrow_destructible<base>();
    test_is_nothrow_destructible<derived>();
    test_is_not_nothrow_destructible<abstract>();
    test_is_nothrow_destructible<public_abstract>();
    test_is_nothrow_destructible<private_abstract>();
    test_is_nothrow_destructible<protected_abstract>();
    test_is_nothrow_destructible<abstract_template<int>>();
    test_is_nothrow_destructible<abstract_template<double>>();
    test_is_nothrow_destructible<abstract_template<class_type>>();
    test_is_nothrow_destructible<abstract_template<incomplete_type>>();
    test_is_nothrow_destructible<final_type>();
    test_is_nothrow_destructible<public_destructor>();
    test_is_not_nothrow_destructible<protected_destructor>();
    test_is_not_nothrow_destructible<private_destructor>();
    test_is_nothrow_destructible<virtual_public_destructor>();
    test_is_not_nothrow_destructible<virtual_protected_destructor>();
    test_is_not_nothrow_destructible<virtual_private_destructor>();
    test_is_nothrow_destructible<pure_public_destructor>();
    test_is_not_nothrow_destructible<pure_protected_destructor>();
    test_is_not_nothrow_destructible<pure_private_destructor>();
    test_is_not_nothrow_destructible<deleted_public_destructor>();
    test_is_not_nothrow_destructible<deleted_protected_destructor>();
    test_is_not_nothrow_destructible<deleted_private_destructor>();
    test_is_not_nothrow_destructible<deleted_virtual_public_destructor>();
    test_is_not_nothrow_destructible<deleted_virtual_protected_destructor>();
    test_is_not_nothrow_destructible<deleted_virtual_private_destructor>();
    test_is_nothrow_destructible<Enum>();
    test_is_nothrow_destructible<EnumSigned>();
    test_is_nothrow_destructible<EnumUnsigned>();
    test_is_nothrow_destructible<EnumClass>();
    test_is_nothrow_destructible<EnumStruct>();
    test_is_not_nothrow_destructible<function_type>();
    test_is_nothrow_destructible<function_ptr>();
    test_is_nothrow_destructible<member_object_ptr>();
    test_is_nothrow_destructible<member_function_ptr>();
    test_is_nothrow_destructible<int class_type::*>();
    test_is_nothrow_destructible<float class_type::*>();
    test_is_nothrow_destructible<void * class_type::*>();
    test_is_nothrow_destructible<int * class_type::*>();
    test_is_nothrow_destructible<int class_type::*&>();
    test_is_nothrow_destructible<float class_type::*&>();
    test_is_nothrow_destructible<void * class_type::*&>();
    test_is_nothrow_destructible<int * class_type::*&>();
    test_is_nothrow_destructible<int class_type::*&&>();
    test_is_nothrow_destructible<float class_type::*&&>();
    test_is_nothrow_destructible<void * class_type::*&&>();
    test_is_nothrow_destructible<int * class_type::*&&>();
    test_is_nothrow_destructible<int class_type::* const>();
    test_is_nothrow_destructible<float class_type::* const>();
    test_is_nothrow_destructible<void * class_type::* const>();
    test_is_nothrow_destructible<int class_type::* const&>();
    test_is_nothrow_destructible<float class_type::* const&>();
    test_is_nothrow_destructible<void * class_type::* const&>();
    test_is_nothrow_destructible<int class_type::* const&&>();
    test_is_nothrow_destructible<float class_type::* const&&>();
    test_is_nothrow_destructible<void * class_type::* const&&>();
    test_is_nothrow_destructible<int class_type::* volatile>();
    test_is_nothrow_destructible<float class_type::* volatile>();
    test_is_nothrow_destructible<void * class_type::* volatile>();
    test_is_nothrow_destructible<int class_type::* volatile&>();
    test_is_nothrow_destructible<float class_type::* volatile&>();
    test_is_nothrow_destructible<void * class_type::* volatile&>();
    test_is_nothrow_destructible<int class_type::* volatile&&>();
    test_is_nothrow_destructible<float class_type::* volatile&&>();
    test_is_nothrow_destructible<void * class_type::* volatile&&>();
    test_is_nothrow_destructible<int class_type::* const volatile>();
    test_is_nothrow_destructible<float class_type::* const volatile>();
    test_is_nothrow_destructible<void * class_type::* const volatile>();
    test_is_nothrow_destructible<int class_type::* const volatile&>();
    test_is_nothrow_destructible<float class_type::* const volatile&>();
    test_is_nothrow_destructible<void * class_type::* const volatile&>();
    test_is_nothrow_destructible<int class_type::* const volatile&&>();
    test_is_nothrow_destructible<float class_type::* const volatile&&>();
    test_is_nothrow_destructible<void * class_type::* const volatile&&>();
    test_is_nothrow_destructible<non_copyable>();
    test_is_nothrow_destructible<non_moveable>();
    test_is_nothrow_destructible<non_constructible>();
    test_is_nothrow_destructible<tracked>();
    test_is_nothrow_destructible<trap_constructible>();
    test_is_nothrow_destructible<trap_implicit_conversion>();
    test_is_nothrow_destructible<trap_comma>();
    test_is_nothrow_destructible<trap_call>();
    test_is_nothrow_destructible<trap_self_assign>();
    test_is_nothrow_destructible<trap_deref>();
    test_is_nothrow_destructible<trap_array_subscript>();

    test_is_not_nothrow_destructible<void()>();
    test_is_not_nothrow_destructible<void()&>();
    test_is_not_nothrow_destructible<void() &&>();
    test_is_not_nothrow_destructible<void() const>();
    test_is_not_nothrow_destructible<void() const&>();
    test_is_not_nothrow_destructible<void() const&&>();
    test_is_not_nothrow_destructible<void() volatile>();
    test_is_not_nothrow_destructible<void() volatile&>();
    test_is_not_nothrow_destructible<void() volatile&&>();
    test_is_not_nothrow_destructible<void() const volatile>();
    test_is_not_nothrow_destructible<void() const volatile&>();
    test_is_not_nothrow_destructible<void() const volatile&&>();
    test_is_not_nothrow_destructible<void() noexcept>();
    test_is_not_nothrow_destructible<void() & noexcept>();
    test_is_not_nothrow_destructible<void() && noexcept>();
    test_is_not_nothrow_destructible<void() const noexcept>();
    test_is_not_nothrow_destructible<void() const & noexcept>();
    test_is_not_nothrow_destructible<void() const && noexcept>();
    test_is_not_nothrow_destructible<void() volatile noexcept>();
    test_is_not_nothrow_destructible<void() volatile & noexcept>();
    test_is_not_nothrow_destructible<void() volatile && noexcept>();
    test_is_not_nothrow_destructible<void() const volatile noexcept>();
    test_is_not_nothrow_destructible<void() const volatile & noexcept>();
    test_is_not_nothrow_destructible<void() const volatile && noexcept>();

    test_is_not_nothrow_destructible<void(int)>();
    test_is_not_nothrow_destructible<void(int)&>();
    test_is_not_nothrow_destructible<void(int) &&>();
    test_is_not_nothrow_destructible<void(int) const>();
    test_is_not_nothrow_destructible<void(int) const&>();
    test_is_not_nothrow_destructible<void(int) const&&>();
    test_is_not_nothrow_destructible<void(int) volatile>();
    test_is_not_nothrow_destructible<void(int) volatile&>();
    test_is_not_nothrow_destructible<void(int) volatile&&>();
    test_is_not_nothrow_destructible<void(int) const volatile>();
    test_is_not_nothrow_destructible<void(int) const volatile&>();
    test_is_not_nothrow_destructible<void(int) const volatile&&>();
    test_is_not_nothrow_destructible<void(int) noexcept>();
    test_is_not_nothrow_destructible<void(int) & noexcept>();
    test_is_not_nothrow_destructible<void(int) && noexcept>();
    test_is_not_nothrow_destructible<void(int) const noexcept>();
    test_is_not_nothrow_destructible<void(int) const & noexcept>();
    test_is_not_nothrow_destructible<void(int) const && noexcept>();
    test_is_not_nothrow_destructible<void(int) volatile noexcept>();
    test_is_not_nothrow_destructible<void(int) volatile & noexcept>();
    test_is_not_nothrow_destructible<void(int) volatile && noexcept>();
    test_is_not_nothrow_destructible<void(int) const volatile noexcept>();
    test_is_not_nothrow_destructible<void(int) const volatile & noexcept>();
    test_is_not_nothrow_destructible<void(int) const volatile && noexcept>();

    test_is_not_nothrow_destructible<void(...)>();
    test_is_not_nothrow_destructible<void(...)&>();
    test_is_not_nothrow_destructible<void(...) &&>();
    test_is_not_nothrow_destructible<void(...) const>();
    test_is_not_nothrow_destructible<void(...) const&>();
    test_is_not_nothrow_destructible<void(...) const&&>();
    test_is_not_nothrow_destructible<void(...) volatile>();
    test_is_not_nothrow_destructible<void(...) volatile&>();
    test_is_not_nothrow_destructible<void(...) volatile&&>();
    test_is_not_nothrow_destructible<void(...) const volatile>();
    test_is_not_nothrow_destructible<void(...) const volatile&>();
    test_is_not_nothrow_destructible<void(...) const volatile&&>();
    test_is_not_nothrow_destructible<void(...) noexcept>();
    test_is_not_nothrow_destructible<void(...) & noexcept>();
    test_is_not_nothrow_destructible<void(...) && noexcept>();
    test_is_not_nothrow_destructible<void(...) const noexcept>();
    test_is_not_nothrow_destructible<void(...) const & noexcept>();
    test_is_not_nothrow_destructible<void(...) const && noexcept>();
    test_is_not_nothrow_destructible<void(...) volatile noexcept>();
    test_is_not_nothrow_destructible<void(...) volatile & noexcept>();
    test_is_not_nothrow_destructible<void(...) volatile && noexcept>();
    test_is_not_nothrow_destructible<void(...) const volatile noexcept>();
    test_is_not_nothrow_destructible<void(...) const volatile & noexcept>();
    test_is_not_nothrow_destructible<void(...) const volatile && noexcept>();

    test_is_not_nothrow_destructible<void(int, ...)>();
    test_is_not_nothrow_destructible<void(int, ...)&>();
    test_is_not_nothrow_destructible<void(int, ...) &&>();
    test_is_not_nothrow_destructible<void(int, ...) const>();
    test_is_not_nothrow_destructible<void(int, ...) const&>();
    test_is_not_nothrow_destructible<void(int, ...) const&&>();
    test_is_not_nothrow_destructible<void(int, ...) volatile>();
    test_is_not_nothrow_destructible<void(int, ...) volatile&>();
    test_is_not_nothrow_destructible<void(int, ...) volatile&&>();
    test_is_not_nothrow_destructible<void(int, ...) const volatile>();
    test_is_not_nothrow_destructible<void(int, ...) const volatile&>();
    test_is_not_nothrow_destructible<void(int, ...) const volatile&&>();
    test_is_not_nothrow_destructible<void(int, ...) noexcept>();
    test_is_not_nothrow_destructible<void(int, ...) & noexcept>();
    test_is_not_nothrow_destructible<void(int, ...) && noexcept>();
    test_is_not_nothrow_destructible<void(int, ...) const noexcept>();
    test_is_not_nothrow_destructible<void(int, ...) const & noexcept>();
    test_is_not_nothrow_destructible<void(int, ...) const && noexcept>();
    test_is_not_nothrow_destructible<void(int, ...) volatile noexcept>();
    test_is_not_nothrow_destructible<void(int, ...) volatile & noexcept>();
    test_is_not_nothrow_destructible<void(int, ...) volatile && noexcept>();
    test_is_not_nothrow_destructible<void(int, ...) const volatile noexcept>();
    test_is_not_nothrow_destructible<void(int, ...) const volatile & noexcept>();
    test_is_not_nothrow_destructible<void(int, ...) const volatile && noexcept>();

    test_is_not_nothrow_destructible<int()>();
    test_is_not_nothrow_destructible<int()&>();
    test_is_not_nothrow_destructible<int() &&>();
    test_is_not_nothrow_destructible<int() const>();
    test_is_not_nothrow_destructible<int() const&>();
    test_is_not_nothrow_destructible<int() const&&>();
    test_is_not_nothrow_destructible<int() volatile>();
    test_is_not_nothrow_destructible<int() volatile&>();
    test_is_not_nothrow_destructible<int() volatile&&>();
    test_is_not_nothrow_destructible<int() const volatile>();
    test_is_not_nothrow_destructible<int() const volatile&>();
    test_is_not_nothrow_destructible<int() const volatile&&>();
    test_is_not_nothrow_destructible<int() noexcept>();
    test_is_not_nothrow_destructible<int() & noexcept>();
    test_is_not_nothrow_destructible<int() && noexcept>();
    test_is_not_nothrow_destructible<int() const noexcept>();
    test_is_not_nothrow_destructible<int() const & noexcept>();
    test_is_not_nothrow_destructible<int() const && noexcept>();
    test_is_not_nothrow_destructible<int() volatile noexcept>();
    test_is_not_nothrow_destructible<int() volatile & noexcept>();
    test_is_not_nothrow_destructible<int() volatile && noexcept>();
    test_is_not_nothrow_destructible<int() const volatile noexcept>();
    test_is_not_nothrow_destructible<int() const volatile & noexcept>();
    test_is_not_nothrow_destructible<int() const volatile && noexcept>();

    test_is_not_nothrow_destructible<int(int)>();
    test_is_not_nothrow_destructible<int(int)&>();
    test_is_not_nothrow_destructible<int(int) &&>();
    test_is_not_nothrow_destructible<int(int) const>();
    test_is_not_nothrow_destructible<int(int) const&>();
    test_is_not_nothrow_destructible<int(int) const&&>();
    test_is_not_nothrow_destructible<int(int) volatile>();
    test_is_not_nothrow_destructible<int(int) volatile&>();
    test_is_not_nothrow_destructible<int(int) volatile&&>();
    test_is_not_nothrow_destructible<int(int) const volatile>();
    test_is_not_nothrow_destructible<int(int) const volatile&>();
    test_is_not_nothrow_destructible<int(int) const volatile&&>();
    test_is_not_nothrow_destructible<int(int) noexcept>();
    test_is_not_nothrow_destructible<int(int) & noexcept>();
    test_is_not_nothrow_destructible<int(int) && noexcept>();
    test_is_not_nothrow_destructible<int(int) const noexcept>();
    test_is_not_nothrow_destructible<int(int) const & noexcept>();
    test_is_not_nothrow_destructible<int(int) const && noexcept>();
    test_is_not_nothrow_destructible<int(int) volatile noexcept>();
    test_is_not_nothrow_destructible<int(int) volatile & noexcept>();
    test_is_not_nothrow_destructible<int(int) volatile && noexcept>();
    test_is_not_nothrow_destructible<int(int) const volatile noexcept>();
    test_is_not_nothrow_destructible<int(int) const volatile & noexcept>();
    test_is_not_nothrow_destructible<int(int) const volatile && noexcept>();

    test_is_not_nothrow_destructible<int(...)>();
    test_is_not_nothrow_destructible<int(...)&>();
    test_is_not_nothrow_destructible<int(...) &&>();
    test_is_not_nothrow_destructible<int(...) const>();
    test_is_not_nothrow_destructible<int(...) const&>();
    test_is_not_nothrow_destructible<int(...) const&&>();
    test_is_not_nothrow_destructible<int(...) volatile>();
    test_is_not_nothrow_destructible<int(...) volatile&>();
    test_is_not_nothrow_destructible<int(...) volatile&&>();
    test_is_not_nothrow_destructible<int(...) const volatile>();
    test_is_not_nothrow_destructible<int(...) const volatile&>();
    test_is_not_nothrow_destructible<int(...) const volatile&&>();
    test_is_not_nothrow_destructible<int(...) noexcept>();
    test_is_not_nothrow_destructible<int(...) & noexcept>();
    test_is_not_nothrow_destructible<int(...) && noexcept>();
    test_is_not_nothrow_destructible<int(...) const noexcept>();
    test_is_not_nothrow_destructible<int(...) const & noexcept>();
    test_is_not_nothrow_destructible<int(...) const && noexcept>();
    test_is_not_nothrow_destructible<int(...) volatile noexcept>();
    test_is_not_nothrow_destructible<int(...) volatile & noexcept>();
    test_is_not_nothrow_destructible<int(...) volatile && noexcept>();
    test_is_not_nothrow_destructible<int(...) const volatile noexcept>();
    test_is_not_nothrow_destructible<int(...) const volatile & noexcept>();
    test_is_not_nothrow_destructible<int(...) const volatile && noexcept>();

    test_is_not_nothrow_destructible<int(int, ...)>();
    test_is_not_nothrow_destructible<int(int, ...)&>();
    test_is_not_nothrow_destructible<int(int, ...) &&>();
    test_is_not_nothrow_destructible<int(int, ...) const>();
    test_is_not_nothrow_destructible<int(int, ...) const&>();
    test_is_not_nothrow_destructible<int(int, ...) const&&>();
    test_is_not_nothrow_destructible<int(int, ...) volatile>();
    test_is_not_nothrow_destructible<int(int, ...) volatile&>();
    test_is_not_nothrow_destructible<int(int, ...) volatile&&>();
    test_is_not_nothrow_destructible<int(int, ...) const volatile>();
    test_is_not_nothrow_destructible<int(int, ...) const volatile&>();
    test_is_not_nothrow_destructible<int(int, ...) const volatile&&>();
    test_is_not_nothrow_destructible<int(int, ...) noexcept>();
    test_is_not_nothrow_destructible<int(int, ...) & noexcept>();
    test_is_not_nothrow_destructible<int(int, ...) && noexcept>();
    test_is_not_nothrow_destructible<int(int, ...) const noexcept>();
    test_is_not_nothrow_destructible<int(int, ...) const & noexcept>();
    test_is_not_nothrow_destructible<int(int, ...) const && noexcept>();
    test_is_not_nothrow_destructible<int(int, ...) volatile noexcept>();
    test_is_not_nothrow_destructible<int(int, ...) volatile & noexcept>();
    test_is_not_nothrow_destructible<int(int, ...) volatile && noexcept>();
    test_is_not_nothrow_destructible<int(int, ...) const volatile noexcept>();
    test_is_not_nothrow_destructible<int(int, ...) const volatile & noexcept>();
    test_is_not_nothrow_destructible<int(int, ...) const volatile && noexcept>();

    test_is_nothrow_destructible<void (*)()>();
    test_is_nothrow_destructible<void (*)() noexcept>();

    test_is_nothrow_destructible<void (*)(int)>();
    test_is_nothrow_destructible<void (*)(int) noexcept>();

    test_is_nothrow_destructible<void (*)(...)>();
    test_is_nothrow_destructible<void (*)(...) noexcept>();

    test_is_nothrow_destructible<void (*)(int, ...)>();
    test_is_nothrow_destructible<void (*)(int, ...) noexcept>();

    test_is_nothrow_destructible<int (*)()>();
    test_is_nothrow_destructible<int (*)() noexcept>();

    test_is_nothrow_destructible<int (*)(int)>();
    test_is_nothrow_destructible<int (*)(int) noexcept>();

    test_is_nothrow_destructible<int (*)(...)>();
    test_is_nothrow_destructible<int (*)(...) noexcept>();

    test_is_nothrow_destructible<int (*)(int, ...)>();
    test_is_nothrow_destructible<int (*)(int, ...) noexcept>();

    test_is_nothrow_destructible<void (&)()>();
    test_is_nothrow_destructible<void (&)() noexcept>();

    test_is_nothrow_destructible<void (&)(int)>();
    test_is_nothrow_destructible<void (&)(int) noexcept>();

    test_is_nothrow_destructible<void (&)(...)>();
    test_is_nothrow_destructible<void (&)(...) noexcept>();

    test_is_nothrow_destructible<void (&)(int, ...)>();
    test_is_nothrow_destructible<void (&)(int, ...) noexcept>();

    test_is_nothrow_destructible<int (&)()>();
    test_is_nothrow_destructible<int (&)() noexcept>();

    test_is_nothrow_destructible<int (&)(int)>();
    test_is_nothrow_destructible<int (&)(int) noexcept>();

    test_is_nothrow_destructible<int (&)(...)>();
    test_is_nothrow_destructible<int (&)(...) noexcept>();

    test_is_nothrow_destructible<int (&)(int, ...)>();
    test_is_nothrow_destructible<int (&)(int, ...) noexcept>();

    test_is_nothrow_destructible<void (&&)()>();
    test_is_nothrow_destructible<void (&&)() noexcept>();

    test_is_nothrow_destructible<void (&&)(int)>();
    test_is_nothrow_destructible<void (&&)(int) noexcept>();

    test_is_nothrow_destructible<void (&&)(...)>();
    test_is_nothrow_destructible<void (&&)(...) noexcept>();

    test_is_nothrow_destructible<void (&&)(int, ...)>();
    test_is_nothrow_destructible<void (&&)(int, ...) noexcept>();

    test_is_nothrow_destructible<int (&&)()>();
    test_is_nothrow_destructible<int (&&)() noexcept>();

    test_is_nothrow_destructible<int (&&)(int)>();
    test_is_nothrow_destructible<int (&&)(int) noexcept>();

    test_is_nothrow_destructible<int (&&)(...)>();
    test_is_nothrow_destructible<int (&&)(...) noexcept>();

    test_is_nothrow_destructible<int (&&)(int, ...)>();
    test_is_nothrow_destructible<int (&&)(int, ...) noexcept>();

    test_is_nothrow_destructible<void (class_type::*)()>();
    test_is_nothrow_destructible<void (class_type::*)()&>();
    test_is_nothrow_destructible<void (class_type::*)() &&>();
    test_is_nothrow_destructible<void (class_type::*)() const>();
    test_is_nothrow_destructible<void (class_type::*)() const&>();
    test_is_nothrow_destructible<void (class_type::*)() const&&>();
    test_is_nothrow_destructible<void (class_type::*)() noexcept>();
    test_is_nothrow_destructible<void (class_type::*)() & noexcept>();
    test_is_nothrow_destructible<void (class_type::*)() && noexcept>();
    test_is_nothrow_destructible<void (class_type::*)() const noexcept>();
    test_is_nothrow_destructible<void (class_type::*)() const & noexcept>();
    test_is_nothrow_destructible<void (class_type::*)() const && noexcept>();

    test_is_nothrow_destructible<void (class_type::*)(int)>();
    test_is_nothrow_destructible<void (class_type::*)(int)&>();
    test_is_nothrow_destructible<void (class_type::*)(int) &&>();
    test_is_nothrow_destructible<void (class_type::*)(int) const>();
    test_is_nothrow_destructible<void (class_type::*)(int) const&>();
    test_is_nothrow_destructible<void (class_type::*)(int) const&&>();
    test_is_nothrow_destructible<void (class_type::*)(int) noexcept>();
    test_is_nothrow_destructible<void (class_type::*)(int) & noexcept>();
    test_is_nothrow_destructible<void (class_type::*)(int) && noexcept>();
    test_is_nothrow_destructible<void (class_type::*)(int) const noexcept>();
    test_is_nothrow_destructible<void (class_type::*)(int) const & noexcept>();
    test_is_nothrow_destructible<void (class_type::*)(int) const && noexcept>();

    test_is_nothrow_destructible<void (class_type::*)(...)>();
    test_is_nothrow_destructible<void (class_type::*)(...)&>();
    test_is_nothrow_destructible<void (class_type::*)(...) &&>();
    test_is_nothrow_destructible<void (class_type::*)(...) const>();
    test_is_nothrow_destructible<void (class_type::*)(...) const&>();
    test_is_nothrow_destructible<void (class_type::*)(...) const&&>();
    test_is_nothrow_destructible<void (class_type::*)(...) noexcept>();
    test_is_nothrow_destructible<void (class_type::*)(...) & noexcept>();
    test_is_nothrow_destructible<void (class_type::*)(...) && noexcept>();
    test_is_nothrow_destructible<void (class_type::*)(...) const noexcept>();
    test_is_nothrow_destructible<void (class_type::*)(...) const & noexcept>();
    test_is_nothrow_destructible<void (class_type::*)(...) const && noexcept>();

    test_is_nothrow_destructible<void (class_type::*)(int, ...)>();
    test_is_nothrow_destructible<void (class_type::*)(int, ...)&>();
    test_is_nothrow_destructible<void (class_type::*)(int, ...) &&>();
    test_is_nothrow_destructible<void (class_type::*)(int, ...) const>();
    test_is_nothrow_destructible<void (class_type::*)(int, ...) const&>();
    test_is_nothrow_destructible<void (class_type::*)(int, ...) const&&>();
    test_is_nothrow_destructible<void (class_type::*)(int, ...) noexcept>();
    test_is_nothrow_destructible<void (class_type::*)(int, ...) & noexcept>();
    test_is_nothrow_destructible<void (class_type::*)(int, ...) && noexcept>();
    test_is_nothrow_destructible<void (class_type::*)(int, ...) const noexcept>();
    test_is_nothrow_destructible<void (class_type::*)(int, ...) const & noexcept>();
    test_is_nothrow_destructible<void (class_type::*)(int, ...) const && noexcept>();

    test_is_nothrow_destructible<int (class_type::*)()>();
    test_is_nothrow_destructible<int (class_type::*)()&>();
    test_is_nothrow_destructible<int (class_type::*)() &&>();
    test_is_nothrow_destructible<int (class_type::*)() const>();
    test_is_nothrow_destructible<int (class_type::*)() const&>();
    test_is_nothrow_destructible<int (class_type::*)() const&&>();
    test_is_nothrow_destructible<int (class_type::*)() noexcept>();
    test_is_nothrow_destructible<int (class_type::*)() & noexcept>();
    test_is_nothrow_destructible<int (class_type::*)() && noexcept>();
    test_is_nothrow_destructible<int (class_type::*)() const noexcept>();
    test_is_nothrow_destructible<int (class_type::*)() const & noexcept>();
    test_is_nothrow_destructible<int (class_type::*)() const && noexcept>();

    test_is_nothrow_destructible<int (class_type::*)(int)>();
    test_is_nothrow_destructible<int (class_type::*)(int)&>();
    test_is_nothrow_destructible<int (class_type::*)(int) &&>();
    test_is_nothrow_destructible<int (class_type::*)(int) const>();
    test_is_nothrow_destructible<int (class_type::*)(int) const&>();
    test_is_nothrow_destructible<int (class_type::*)(int) const&&>();
    test_is_nothrow_destructible<int (class_type::*)(int) noexcept>();
    test_is_nothrow_destructible<int (class_type::*)(int) & noexcept>();
    test_is_nothrow_destructible<int (class_type::*)(int) && noexcept>();
    test_is_nothrow_destructible<int (class_type::*)(int) const noexcept>();
    test_is_nothrow_destructible<int (class_type::*)(int) const & noexcept>();
    test_is_nothrow_destructible<int (class_type::*)(int) const && noexcept>();

    test_is_nothrow_destructible<int (class_type::*)(...)>();
    test_is_nothrow_destructible<int (class_type::*)(...)&>();
    test_is_nothrow_destructible<int (class_type::*)(...) &&>();
    test_is_nothrow_destructible<int (class_type::*)(...) const>();
    test_is_nothrow_destructible<int (class_type::*)(...) const&>();
    test_is_nothrow_destructible<int (class_type::*)(...) const&&>();
    test_is_nothrow_destructible<int (class_type::*)(...) noexcept>();
    test_is_nothrow_destructible<int (class_type::*)(...) & noexcept>();
    test_is_nothrow_destructible<int (class_type::*)(...) && noexcept>();
    test_is_nothrow_destructible<int (class_type::*)(...) const noexcept>();
    test_is_nothrow_destructible<int (class_type::*)(...) const & noexcept>();
    test_is_nothrow_destructible<int (class_type::*)(...) const && noexcept>();

    test_is_nothrow_destructible<int (class_type::*)(int, ...)>();
    test_is_nothrow_destructible<int (class_type::*)(int, ...)&>();
    test_is_nothrow_destructible<int (class_type::*)(int, ...) &&>();
    test_is_nothrow_destructible<int (class_type::*)(int, ...) const>();
    test_is_nothrow_destructible<int (class_type::*)(int, ...) const&>();
    test_is_nothrow_destructible<int (class_type::*)(int, ...) const&&>();
    test_is_nothrow_destructible<int (class_type::*)(int, ...) noexcept>();
    test_is_nothrow_destructible<int (class_type::*)(int, ...) & noexcept>();
    test_is_nothrow_destructible<int (class_type::*)(int, ...) && noexcept>();
    test_is_nothrow_destructible<int (class_type::*)(int, ...) const noexcept>();
    test_is_nothrow_destructible<int (class_type::*)(int, ...) const & noexcept>();
    test_is_nothrow_destructible<int (class_type::*)(int, ...) const && noexcept>();
}
