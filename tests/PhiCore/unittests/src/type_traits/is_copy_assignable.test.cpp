#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/compiler_support/compiler.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_copy_assignable.hpp>
#include <type_traits>
#include <vector>

template <typename TypeT>
void test_is_copy_assignable()
{
    STATIC_REQUIRE(phi::is_copy_assignable<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_copy_assignable<TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_copy_assignable_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_not_copy_assignable_v<TypeT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_copy_assignable<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_copy_assignable<TypeT>);

    // Standard compatibility
    STATIC_REQUIRE(std::is_copy_assignable<TypeT>::value);
}

template <typename TypeT>
void test_is_not_copy_assignable()
{
    STATIC_REQUIRE_FALSE(phi::is_copy_assignable<TypeT>::value);
    STATIC_REQUIRE(phi::is_not_copy_assignable<TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_copy_assignable_v<TypeT>);
    STATIC_REQUIRE(phi::is_not_copy_assignable_v<TypeT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_copy_assignable<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_copy_assignable<TypeT>);

    // Standard compatibility
    STATIC_REQUIRE_FALSE(std::is_copy_assignable<TypeT>::value);
}

struct A
{
    A();
};

class B // NOLINT(readability-identifier-naming)
{
    // NOLINTNEXTLINE(modernize-use-equals-delete)
    B& operator=(const B&);
};

struct C
{
    // NOLINTNEXTLINE(misc-unconventional-assign-operator)
    void operator=(C&); // not const
};

TEST_CASE("is_copy_assignable")
{
    test_is_copy_assignable<A>();

    test_is_not_copy_assignable<B>();
    test_is_not_copy_assignable<C>();

    test_is_not_copy_assignable<void>();
    test_is_copy_assignable<phi::nullptr_t>();
    test_is_copy_assignable<bool>();
    test_is_copy_assignable<char>();
    test_is_copy_assignable<signed char>();
    test_is_copy_assignable<unsigned char>();
    test_is_copy_assignable<short>();
    test_is_copy_assignable<unsigned short>();
    test_is_copy_assignable<int>();
    test_is_copy_assignable<unsigned int>();
    test_is_copy_assignable<long>();
    test_is_copy_assignable<unsigned long>();
    test_is_copy_assignable<long long>();
    test_is_copy_assignable<unsigned long long>();
    test_is_copy_assignable<float>();
    test_is_copy_assignable<double>();
    test_is_copy_assignable<long double>();
    test_is_copy_assignable<char8_t>();
    test_is_copy_assignable<char16_t>();
    test_is_copy_assignable<char32_t>();
    test_is_copy_assignable<wchar_t>();

    test_is_copy_assignable<phi::boolean>();
    test_is_copy_assignable<phi::integer<signed char>>();
    test_is_copy_assignable<phi::integer<unsigned char>>();
    test_is_copy_assignable<phi::integer<short>>();
    test_is_copy_assignable<phi::integer<unsigned short>>();
    test_is_copy_assignable<phi::integer<int>>();
    test_is_copy_assignable<phi::integer<unsigned int>>();
    test_is_copy_assignable<phi::integer<long>>();
    test_is_copy_assignable<phi::integer<unsigned long>>();
    test_is_copy_assignable<phi::integer<long long>>();
    test_is_copy_assignable<phi::integer<unsigned long long>>();
    test_is_copy_assignable<phi::floating_point<float>>();
    test_is_copy_assignable<phi::floating_point<double>>();
    test_is_copy_assignable<phi::floating_point<long double>>();

    test_is_copy_assignable<std::vector<int>>();
    test_is_not_copy_assignable<phi::scope_ptr<int>>();

    test_is_copy_assignable<int&>();
    test_is_not_copy_assignable<const int&>();
    test_is_copy_assignable<volatile int&>();
    test_is_not_copy_assignable<const volatile int&>();
    test_is_copy_assignable<int&&>();
    test_is_not_copy_assignable<const int&&>();
    test_is_copy_assignable<volatile int&&>();
    test_is_not_copy_assignable<const volatile int&&>();
    test_is_copy_assignable<int*>();
    test_is_copy_assignable<const int*>();
    test_is_copy_assignable<volatile int*>();
    test_is_copy_assignable<const volatile int*>();
    test_is_copy_assignable<int**>();
    test_is_copy_assignable<const int**>();
    test_is_copy_assignable<volatile int**>();
    test_is_copy_assignable<const volatile int**>();
    test_is_copy_assignable<int*&>();
    test_is_copy_assignable<const int*&>();
    test_is_copy_assignable<volatile int*&>();
    test_is_copy_assignable<const volatile int*&>();
    test_is_copy_assignable<int*&&>();
    test_is_copy_assignable<const int*&&>();
    test_is_copy_assignable<volatile int*&&>();
    test_is_copy_assignable<const volatile int*&&>();
    test_is_copy_assignable<void*>();
    test_is_not_copy_assignable<char[3]>();
    test_is_not_copy_assignable<char[]>();
    test_is_not_copy_assignable<char* [3]>();
    test_is_not_copy_assignable<char*[]>();
    test_is_copy_assignable<int(*)[3]>();
    test_is_copy_assignable<int(*)[]>();
    test_is_not_copy_assignable<int(&)[3]>();
    test_is_not_copy_assignable<int(&)[]>();
    test_is_not_copy_assignable<int(&&)[3]>();
    test_is_not_copy_assignable<int(&&)[]>();
    test_is_not_copy_assignable<char[3][2]>();
    test_is_not_copy_assignable<char[][2]>();
    test_is_not_copy_assignable<char* [3][2]>();
    test_is_not_copy_assignable<char*[][2]>();
    test_is_copy_assignable<int(*)[3][2]>();
    test_is_copy_assignable<int(*)[][2]>();
    test_is_not_copy_assignable<int(&)[3][2]>();
    test_is_not_copy_assignable<int(&)[][2]>();
    test_is_not_copy_assignable<int(&&)[3][2]>();
    test_is_not_copy_assignable<int(&&)[][2]>();
    test_is_copy_assignable<class_type>();
    test_is_not_copy_assignable<class_type[]>();
    test_is_not_copy_assignable<class_type[2]>();
    test_is_copy_assignable<template_type<void>>();
    test_is_copy_assignable<template_type<int>>();
    test_is_copy_assignable<template_type<class_type>>();
    test_is_copy_assignable<template_type<incomplete_type>>();
    test_is_copy_assignable<variadic_template<>>();
    test_is_copy_assignable<variadic_template<void>>();
    test_is_copy_assignable<variadic_template<int>>();
    test_is_copy_assignable<variadic_template<class_type>>();
    test_is_copy_assignable<variadic_template<incomplete_type>>();
    test_is_copy_assignable<variadic_template<int, void, class_type, volatile char[]>>();
    test_is_copy_assignable<public_derived_from<base>>();
    test_is_copy_assignable<public_derived_from<derived>>();
    test_is_copy_assignable<public_derived_from<class_type>>();
    test_is_copy_assignable<private_derived_from<base>>();
    test_is_copy_assignable<private_derived_from<derived>>();
    test_is_copy_assignable<private_derived_from<class_type>>();
    test_is_copy_assignable<protected_derived_from<base>>();
    test_is_copy_assignable<protected_derived_from<derived>>();
    test_is_copy_assignable<protected_derived_from<class_type>>();
    test_is_copy_assignable<union_type>();
    test_is_copy_assignable<non_empty_union>();
    test_is_copy_assignable<empty>();
    test_is_copy_assignable<not_empty>();
    test_is_copy_assignable<bit_zero>();
    test_is_copy_assignable<bit_one>();
    test_is_copy_assignable<base>();
    test_is_copy_assignable<derived>();
    test_is_copy_assignable<abstract>();
    test_is_copy_assignable<public_abstract>();
    test_is_copy_assignable<private_abstract>();
    test_is_copy_assignable<protected_abstract>();
    test_is_copy_assignable<abstract_template<int>>();
    test_is_copy_assignable<abstract_template<double>>();
    test_is_copy_assignable<abstract_template<class_type>>();
    test_is_copy_assignable<abstract_template<incomplete_type>>();
    test_is_copy_assignable<final_type>();
    test_is_copy_assignable<public_destructor>();
    test_is_copy_assignable<protected_destructor>();
    test_is_copy_assignable<private_destructor>();
    test_is_copy_assignable<virtual_public_destructor>();
    test_is_copy_assignable<virtual_protected_destructor>();
    test_is_copy_assignable<virtual_private_destructor>();
    test_is_copy_assignable<pure_public_destructor>();
    test_is_copy_assignable<pure_protected_destructor>();
    test_is_copy_assignable<pure_private_destructor>();
    test_is_copy_assignable<deleted_public_destructor>();
    test_is_copy_assignable<deleted_protected_destructor>();
    test_is_copy_assignable<deleted_private_destructor>();
    test_is_copy_assignable<deleted_virtual_public_destructor>();
    test_is_copy_assignable<deleted_virtual_protected_destructor>();
    test_is_copy_assignable<deleted_virtual_private_destructor>();
    test_is_copy_assignable<Enum>();
    test_is_copy_assignable<EnumSigned>();
    test_is_copy_assignable<EnumUnsigned>();
    test_is_copy_assignable<EnumClass>();
    test_is_copy_assignable<EnumStruct>();
    test_is_not_copy_assignable<function_type>();
    test_is_copy_assignable<function_ptr>();
    test_is_copy_assignable<member_object_ptr>();
    test_is_copy_assignable<member_function_ptr>();
    //test_is_not_copy_assignable<incomplete_type>();
    //test_is_not_copy_assignable<incomplete_template<void>>();
    //test_is_not_copy_assignable<incomplete_template<int>>();
    //test_is_not_copy_assignable<incomplete_template<class_type>>();
    //test_is_not_copy_assignable<incomplete_template<incomplete_type>>();
    //test_is_not_copy_assignable<incomplete_variadic_template<>>();
    //test_is_not_copy_assignable<incomplete_variadic_template<void>>();
    //test_is_not_copy_assignable<incomplete_variadic_template<int>>();
    //test_is_not_copy_assignable<incomplete_variadic_template<class_type>>();
    //test_is_not_copy_assignable<incomplete_variadic_template<incomplete_type>>();
    //test_is_not_copy_assignable<incomplete_variadic_template<int, void, class_type, volatile char[]>>();
    test_is_copy_assignable<int class_type::*>();
    test_is_copy_assignable<float class_type::*>();
    test_is_copy_assignable<void * class_type::*>();
    test_is_copy_assignable<int * class_type::*>();
    test_is_copy_assignable<int class_type::*&>();
    test_is_copy_assignable<float class_type::*&>();
    test_is_copy_assignable<void * class_type::*&>();
    test_is_copy_assignable<int * class_type::*&>();
    test_is_copy_assignable<int class_type::*&&>();
    test_is_copy_assignable<float class_type::*&&>();
    test_is_copy_assignable<void * class_type::*&&>();
    test_is_copy_assignable<int * class_type::*&&>();
    test_is_not_copy_assignable<int class_type::* const>();
    test_is_not_copy_assignable<float class_type::* const>();
    test_is_not_copy_assignable<void * class_type::* const>();
    test_is_not_copy_assignable<int class_type::* const&>();
    test_is_not_copy_assignable<float class_type::* const&>();
    test_is_not_copy_assignable<void * class_type::* const&>();
    test_is_not_copy_assignable<int class_type::* const&&>();
    test_is_not_copy_assignable<float class_type::* const&&>();
    test_is_not_copy_assignable<void * class_type::* const&&>();
    test_is_copy_assignable<int class_type::* volatile>();
    test_is_copy_assignable<float class_type::* volatile>();
    test_is_copy_assignable<void * class_type::* volatile>();
    test_is_copy_assignable<int class_type::* volatile&>();
    test_is_copy_assignable<float class_type::* volatile&>();
    test_is_copy_assignable<void * class_type::* volatile&>();
    test_is_copy_assignable<int class_type::* volatile&&>();
    test_is_copy_assignable<float class_type::* volatile&&>();
    test_is_copy_assignable<void * class_type::* volatile&&>();
    test_is_not_copy_assignable<int class_type::* const volatile>();
    test_is_not_copy_assignable<float class_type::* const volatile>();
    test_is_not_copy_assignable<void * class_type::* const volatile>();
    test_is_not_copy_assignable<int class_type::* const volatile&>();
    test_is_not_copy_assignable<float class_type::* const volatile&>();
    test_is_not_copy_assignable<void * class_type::* const volatile&>();
    test_is_not_copy_assignable<int class_type::* const volatile&&>();
    test_is_not_copy_assignable<float class_type::* const volatile&&>();
    test_is_not_copy_assignable<void * class_type::* const volatile&&>();
    test_is_not_copy_assignable<non_copyable>();
    test_is_copy_assignable<non_moveable>();
    test_is_not_copy_assignable<non_constructible>();
    test_is_copy_assignable<tracked>();
    test_is_copy_assignable<trap_constructible>();
    test_is_copy_assignable<trap_implicit_conversion>();
    test_is_copy_assignable<trap_comma>();
    test_is_copy_assignable<trap_call>();
    test_is_copy_assignable<trap_self_assign>();
    test_is_copy_assignable<trap_deref>();
    test_is_copy_assignable<trap_array_subscript>();

    test_is_not_copy_assignable<void()>();
    test_is_not_copy_assignable<void()&>();
    test_is_not_copy_assignable<void() &&>();
    test_is_not_copy_assignable<void() const>();
    test_is_not_copy_assignable<void() const&>();
    test_is_not_copy_assignable<void() const&&>();
    test_is_not_copy_assignable<void() volatile>();
    test_is_not_copy_assignable<void() volatile&>();
    test_is_not_copy_assignable<void() volatile&&>();
    test_is_not_copy_assignable<void() const volatile>();
    test_is_not_copy_assignable<void() const volatile&>();
    test_is_not_copy_assignable<void() const volatile&&>();
    test_is_not_copy_assignable<void() noexcept>();
    test_is_not_copy_assignable<void() & noexcept>();
    test_is_not_copy_assignable<void() && noexcept>();
    test_is_not_copy_assignable<void() const noexcept>();
    test_is_not_copy_assignable<void() const & noexcept>();
    test_is_not_copy_assignable<void() const && noexcept>();
    test_is_not_copy_assignable<void() volatile noexcept>();
    test_is_not_copy_assignable<void() volatile & noexcept>();
    test_is_not_copy_assignable<void() volatile && noexcept>();
    test_is_not_copy_assignable<void() const volatile noexcept>();
    test_is_not_copy_assignable<void() const volatile & noexcept>();
    test_is_not_copy_assignable<void() const volatile && noexcept>();

    test_is_not_copy_assignable<void(int)>();
    test_is_not_copy_assignable<void(int)&>();
    test_is_not_copy_assignable<void(int) &&>();
    test_is_not_copy_assignable<void(int) const>();
    test_is_not_copy_assignable<void(int) const&>();
    test_is_not_copy_assignable<void(int) const&&>();
    test_is_not_copy_assignable<void(int) volatile>();
    test_is_not_copy_assignable<void(int) volatile&>();
    test_is_not_copy_assignable<void(int) volatile&&>();
    test_is_not_copy_assignable<void(int) const volatile>();
    test_is_not_copy_assignable<void(int) const volatile&>();
    test_is_not_copy_assignable<void(int) const volatile&&>();
    test_is_not_copy_assignable<void(int) noexcept>();
    test_is_not_copy_assignable<void(int) & noexcept>();
    test_is_not_copy_assignable<void(int) && noexcept>();
    test_is_not_copy_assignable<void(int) const noexcept>();
    test_is_not_copy_assignable<void(int) const & noexcept>();
    test_is_not_copy_assignable<void(int) const && noexcept>();
    test_is_not_copy_assignable<void(int) volatile noexcept>();
    test_is_not_copy_assignable<void(int) volatile & noexcept>();
    test_is_not_copy_assignable<void(int) volatile && noexcept>();
    test_is_not_copy_assignable<void(int) const volatile noexcept>();
    test_is_not_copy_assignable<void(int) const volatile & noexcept>();
    test_is_not_copy_assignable<void(int) const volatile && noexcept>();

    test_is_not_copy_assignable<void(...)>();
    test_is_not_copy_assignable<void(...)&>();
    test_is_not_copy_assignable<void(...) &&>();
    test_is_not_copy_assignable<void(...) const>();
    test_is_not_copy_assignable<void(...) const&>();
    test_is_not_copy_assignable<void(...) const&&>();
    test_is_not_copy_assignable<void(...) volatile>();
    test_is_not_copy_assignable<void(...) volatile&>();
    test_is_not_copy_assignable<void(...) volatile&&>();
    test_is_not_copy_assignable<void(...) const volatile>();
    test_is_not_copy_assignable<void(...) const volatile&>();
    test_is_not_copy_assignable<void(...) const volatile&&>();
    test_is_not_copy_assignable<void(...) noexcept>();
    test_is_not_copy_assignable<void(...) & noexcept>();
    test_is_not_copy_assignable<void(...) && noexcept>();
    test_is_not_copy_assignable<void(...) const noexcept>();
    test_is_not_copy_assignable<void(...) const & noexcept>();
    test_is_not_copy_assignable<void(...) const && noexcept>();
    test_is_not_copy_assignable<void(...) volatile noexcept>();
    test_is_not_copy_assignable<void(...) volatile & noexcept>();
    test_is_not_copy_assignable<void(...) volatile && noexcept>();
    test_is_not_copy_assignable<void(...) const volatile noexcept>();
    test_is_not_copy_assignable<void(...) const volatile & noexcept>();
    test_is_not_copy_assignable<void(...) const volatile && noexcept>();

    test_is_not_copy_assignable<void(int, ...)>();
    test_is_not_copy_assignable<void(int, ...)&>();
    test_is_not_copy_assignable<void(int, ...) &&>();
    test_is_not_copy_assignable<void(int, ...) const>();
    test_is_not_copy_assignable<void(int, ...) const&>();
    test_is_not_copy_assignable<void(int, ...) const&&>();
    test_is_not_copy_assignable<void(int, ...) volatile>();
    test_is_not_copy_assignable<void(int, ...) volatile&>();
    test_is_not_copy_assignable<void(int, ...) volatile&&>();
    test_is_not_copy_assignable<void(int, ...) const volatile>();
    test_is_not_copy_assignable<void(int, ...) const volatile&>();
    test_is_not_copy_assignable<void(int, ...) const volatile&&>();
    test_is_not_copy_assignable<void(int, ...) noexcept>();
    test_is_not_copy_assignable<void(int, ...) & noexcept>();
    test_is_not_copy_assignable<void(int, ...) && noexcept>();
    test_is_not_copy_assignable<void(int, ...) const noexcept>();
    test_is_not_copy_assignable<void(int, ...) const & noexcept>();
    test_is_not_copy_assignable<void(int, ...) const && noexcept>();
    test_is_not_copy_assignable<void(int, ...) volatile noexcept>();
    test_is_not_copy_assignable<void(int, ...) volatile & noexcept>();
    test_is_not_copy_assignable<void(int, ...) volatile && noexcept>();
    test_is_not_copy_assignable<void(int, ...) const volatile noexcept>();
    test_is_not_copy_assignable<void(int, ...) const volatile & noexcept>();
    test_is_not_copy_assignable<void(int, ...) const volatile && noexcept>();

    test_is_not_copy_assignable<int()>();
    test_is_not_copy_assignable<int()&>();
    test_is_not_copy_assignable<int() &&>();
    test_is_not_copy_assignable<int() const>();
    test_is_not_copy_assignable<int() const&>();
    test_is_not_copy_assignable<int() const&&>();
    test_is_not_copy_assignable<int() volatile>();
    test_is_not_copy_assignable<int() volatile&>();
    test_is_not_copy_assignable<int() volatile&&>();
    test_is_not_copy_assignable<int() const volatile>();
    test_is_not_copy_assignable<int() const volatile&>();
    test_is_not_copy_assignable<int() const volatile&&>();
    test_is_not_copy_assignable<int() noexcept>();
    test_is_not_copy_assignable<int() & noexcept>();
    test_is_not_copy_assignable<int() && noexcept>();
    test_is_not_copy_assignable<int() const noexcept>();
    test_is_not_copy_assignable<int() const & noexcept>();
    test_is_not_copy_assignable<int() const && noexcept>();
    test_is_not_copy_assignable<int() volatile noexcept>();
    test_is_not_copy_assignable<int() volatile & noexcept>();
    test_is_not_copy_assignable<int() volatile && noexcept>();
    test_is_not_copy_assignable<int() const volatile noexcept>();
    test_is_not_copy_assignable<int() const volatile & noexcept>();
    test_is_not_copy_assignable<int() const volatile && noexcept>();

    test_is_not_copy_assignable<int(int)>();
    test_is_not_copy_assignable<int(int)&>();
    test_is_not_copy_assignable<int(int) &&>();
    test_is_not_copy_assignable<int(int) const>();
    test_is_not_copy_assignable<int(int) const&>();
    test_is_not_copy_assignable<int(int) const&&>();
    test_is_not_copy_assignable<int(int) volatile>();
    test_is_not_copy_assignable<int(int) volatile&>();
    test_is_not_copy_assignable<int(int) volatile&&>();
    test_is_not_copy_assignable<int(int) const volatile>();
    test_is_not_copy_assignable<int(int) const volatile&>();
    test_is_not_copy_assignable<int(int) const volatile&&>();
    test_is_not_copy_assignable<int(int) noexcept>();
    test_is_not_copy_assignable<int(int) & noexcept>();
    test_is_not_copy_assignable<int(int) && noexcept>();
    test_is_not_copy_assignable<int(int) const noexcept>();
    test_is_not_copy_assignable<int(int) const & noexcept>();
    test_is_not_copy_assignable<int(int) const && noexcept>();
    test_is_not_copy_assignable<int(int) volatile noexcept>();
    test_is_not_copy_assignable<int(int) volatile & noexcept>();
    test_is_not_copy_assignable<int(int) volatile && noexcept>();
    test_is_not_copy_assignable<int(int) const volatile noexcept>();
    test_is_not_copy_assignable<int(int) const volatile & noexcept>();
    test_is_not_copy_assignable<int(int) const volatile && noexcept>();

    test_is_not_copy_assignable<int(...)>();
    test_is_not_copy_assignable<int(...)&>();
    test_is_not_copy_assignable<int(...) &&>();
    test_is_not_copy_assignable<int(...) const>();
    test_is_not_copy_assignable<int(...) const&>();
    test_is_not_copy_assignable<int(...) const&&>();
    test_is_not_copy_assignable<int(...) volatile>();
    test_is_not_copy_assignable<int(...) volatile&>();
    test_is_not_copy_assignable<int(...) volatile&&>();
    test_is_not_copy_assignable<int(...) const volatile>();
    test_is_not_copy_assignable<int(...) const volatile&>();
    test_is_not_copy_assignable<int(...) const volatile&&>();
    test_is_not_copy_assignable<int(...) noexcept>();
    test_is_not_copy_assignable<int(...) & noexcept>();
    test_is_not_copy_assignable<int(...) && noexcept>();
    test_is_not_copy_assignable<int(...) const noexcept>();
    test_is_not_copy_assignable<int(...) const & noexcept>();
    test_is_not_copy_assignable<int(...) const && noexcept>();
    test_is_not_copy_assignable<int(...) volatile noexcept>();
    test_is_not_copy_assignable<int(...) volatile & noexcept>();
    test_is_not_copy_assignable<int(...) volatile && noexcept>();
    test_is_not_copy_assignable<int(...) const volatile noexcept>();
    test_is_not_copy_assignable<int(...) const volatile & noexcept>();
    test_is_not_copy_assignable<int(...) const volatile && noexcept>();

    test_is_not_copy_assignable<int(int, ...)>();
    test_is_not_copy_assignable<int(int, ...)&>();
    test_is_not_copy_assignable<int(int, ...) &&>();
    test_is_not_copy_assignable<int(int, ...) const>();
    test_is_not_copy_assignable<int(int, ...) const&>();
    test_is_not_copy_assignable<int(int, ...) const&&>();
    test_is_not_copy_assignable<int(int, ...) volatile>();
    test_is_not_copy_assignable<int(int, ...) volatile&>();
    test_is_not_copy_assignable<int(int, ...) volatile&&>();
    test_is_not_copy_assignable<int(int, ...) const volatile>();
    test_is_not_copy_assignable<int(int, ...) const volatile&>();
    test_is_not_copy_assignable<int(int, ...) const volatile&&>();
    test_is_not_copy_assignable<int(int, ...) noexcept>();
    test_is_not_copy_assignable<int(int, ...) & noexcept>();
    test_is_not_copy_assignable<int(int, ...) && noexcept>();
    test_is_not_copy_assignable<int(int, ...) const noexcept>();
    test_is_not_copy_assignable<int(int, ...) const & noexcept>();
    test_is_not_copy_assignable<int(int, ...) const && noexcept>();
    test_is_not_copy_assignable<int(int, ...) volatile noexcept>();
    test_is_not_copy_assignable<int(int, ...) volatile & noexcept>();
    test_is_not_copy_assignable<int(int, ...) volatile && noexcept>();
    test_is_not_copy_assignable<int(int, ...) const volatile noexcept>();
    test_is_not_copy_assignable<int(int, ...) const volatile & noexcept>();
    test_is_not_copy_assignable<int(int, ...) const volatile && noexcept>();

    test_is_copy_assignable<void (*)()>();
    test_is_copy_assignable<void (*)() noexcept>();

    test_is_copy_assignable<void (*)(int)>();
    test_is_copy_assignable<void (*)(int) noexcept>();

    test_is_copy_assignable<void (*)(...)>();
    test_is_copy_assignable<void (*)(...) noexcept>();

    test_is_copy_assignable<void (*)(int, ...)>();
    test_is_copy_assignable<void (*)(int, ...) noexcept>();

    test_is_copy_assignable<int (*)()>();
    test_is_copy_assignable<int (*)() noexcept>();

    test_is_copy_assignable<int (*)(int)>();
    test_is_copy_assignable<int (*)(int) noexcept>();

    test_is_copy_assignable<int (*)(...)>();
    test_is_copy_assignable<int (*)(...) noexcept>();

    test_is_copy_assignable<int (*)(int, ...)>();
    test_is_copy_assignable<int (*)(int, ...) noexcept>();

    test_is_not_copy_assignable<void (&)()>();
    test_is_not_copy_assignable<void (&)() noexcept>();

    test_is_not_copy_assignable<void (&)(int)>();
    test_is_not_copy_assignable<void (&)(int) noexcept>();

    test_is_not_copy_assignable<void (&)(...)>();
    test_is_not_copy_assignable<void (&)(...) noexcept>();

    test_is_not_copy_assignable<void (&)(int, ...)>();
    test_is_not_copy_assignable<void (&)(int, ...) noexcept>();

    test_is_not_copy_assignable<int (&)()>();
    test_is_not_copy_assignable<int (&)() noexcept>();

    test_is_not_copy_assignable<int (&)(int)>();
    test_is_not_copy_assignable<int (&)(int) noexcept>();

    test_is_not_copy_assignable<int (&)(...)>();
    test_is_not_copy_assignable<int (&)(...) noexcept>();

    test_is_not_copy_assignable<int (&)(int, ...)>();
    test_is_not_copy_assignable<int (&)(int, ...) noexcept>();

    test_is_not_copy_assignable<void (&&)()>();
    test_is_not_copy_assignable<void (&&)() noexcept>();

    test_is_not_copy_assignable<void (&&)(int)>();
    test_is_not_copy_assignable<void (&&)(int) noexcept>();

    test_is_not_copy_assignable<void (&&)(...)>();
    test_is_not_copy_assignable<void (&&)(...) noexcept>();

    test_is_not_copy_assignable<void (&&)(int, ...)>();
    test_is_not_copy_assignable<void (&&)(int, ...) noexcept>();

    test_is_not_copy_assignable<int (&&)()>();
    test_is_not_copy_assignable<int (&&)() noexcept>();

    test_is_not_copy_assignable<int (&&)(int)>();
    test_is_not_copy_assignable<int (&&)(int) noexcept>();

    test_is_not_copy_assignable<int (&&)(...)>();
    test_is_not_copy_assignable<int (&&)(...) noexcept>();

    test_is_not_copy_assignable<int (&&)(int, ...)>();
    test_is_not_copy_assignable<int (&&)(int, ...) noexcept>();

    test_is_copy_assignable<void (class_type::*)()>();
    test_is_copy_assignable<void (class_type::*)()&>();
    test_is_copy_assignable<void (class_type::*)() &&>();
    test_is_copy_assignable<void (class_type::*)() const>();
    test_is_copy_assignable<void (class_type::*)() const&>();
    test_is_copy_assignable<void (class_type::*)() const&&>();
    test_is_copy_assignable<void (class_type::*)() noexcept>();
    test_is_copy_assignable<void (class_type::*)() & noexcept>();
    test_is_copy_assignable<void (class_type::*)() && noexcept>();
    test_is_copy_assignable<void (class_type::*)() const noexcept>();
    test_is_copy_assignable<void (class_type::*)() const & noexcept>();
    test_is_copy_assignable<void (class_type::*)() const && noexcept>();

    test_is_copy_assignable<void (class_type::*)(int)>();
    test_is_copy_assignable<void (class_type::*)(int)&>();
    test_is_copy_assignable<void (class_type::*)(int) &&>();
    test_is_copy_assignable<void (class_type::*)(int) const>();
    test_is_copy_assignable<void (class_type::*)(int) const&>();
    test_is_copy_assignable<void (class_type::*)(int) const&&>();
    test_is_copy_assignable<void (class_type::*)(int) noexcept>();
    test_is_copy_assignable<void (class_type::*)(int) & noexcept>();
    test_is_copy_assignable<void (class_type::*)(int) && noexcept>();
    test_is_copy_assignable<void (class_type::*)(int) const noexcept>();
    test_is_copy_assignable<void (class_type::*)(int) const & noexcept>();
    test_is_copy_assignable<void (class_type::*)(int) const && noexcept>();

    test_is_copy_assignable<void (class_type::*)(...)>();
    test_is_copy_assignable<void (class_type::*)(...)&>();
    test_is_copy_assignable<void (class_type::*)(...) &&>();
    test_is_copy_assignable<void (class_type::*)(...) const>();
    test_is_copy_assignable<void (class_type::*)(...) const&>();
    test_is_copy_assignable<void (class_type::*)(...) const&&>();
    test_is_copy_assignable<void (class_type::*)(...) noexcept>();
    test_is_copy_assignable<void (class_type::*)(...) & noexcept>();
    test_is_copy_assignable<void (class_type::*)(...) && noexcept>();
    test_is_copy_assignable<void (class_type::*)(...) const noexcept>();
    test_is_copy_assignable<void (class_type::*)(...) const & noexcept>();
    test_is_copy_assignable<void (class_type::*)(...) const && noexcept>();

    test_is_copy_assignable<void (class_type::*)(int, ...)>();
    test_is_copy_assignable<void (class_type::*)(int, ...)&>();
    test_is_copy_assignable<void (class_type::*)(int, ...) &&>();
    test_is_copy_assignable<void (class_type::*)(int, ...) const>();
    test_is_copy_assignable<void (class_type::*)(int, ...) const&>();
    test_is_copy_assignable<void (class_type::*)(int, ...) const&&>();
    test_is_copy_assignable<void (class_type::*)(int, ...) noexcept>();
    test_is_copy_assignable<void (class_type::*)(int, ...) & noexcept>();
    test_is_copy_assignable<void (class_type::*)(int, ...) && noexcept>();
    test_is_copy_assignable<void (class_type::*)(int, ...) const noexcept>();
    test_is_copy_assignable<void (class_type::*)(int, ...) const & noexcept>();
    test_is_copy_assignable<void (class_type::*)(int, ...) const && noexcept>();

    test_is_copy_assignable<int (class_type::*)()>();
    test_is_copy_assignable<int (class_type::*)()&>();
    test_is_copy_assignable<int (class_type::*)() &&>();
    test_is_copy_assignable<int (class_type::*)() const>();
    test_is_copy_assignable<int (class_type::*)() const&>();
    test_is_copy_assignable<int (class_type::*)() const&&>();
    test_is_copy_assignable<int (class_type::*)() noexcept>();
    test_is_copy_assignable<int (class_type::*)() & noexcept>();
    test_is_copy_assignable<int (class_type::*)() && noexcept>();
    test_is_copy_assignable<int (class_type::*)() const noexcept>();
    test_is_copy_assignable<int (class_type::*)() const & noexcept>();
    test_is_copy_assignable<int (class_type::*)() const && noexcept>();

    test_is_copy_assignable<int (class_type::*)(int)>();
    test_is_copy_assignable<int (class_type::*)(int)&>();
    test_is_copy_assignable<int (class_type::*)(int) &&>();
    test_is_copy_assignable<int (class_type::*)(int) const>();
    test_is_copy_assignable<int (class_type::*)(int) const&>();
    test_is_copy_assignable<int (class_type::*)(int) const&&>();
    test_is_copy_assignable<int (class_type::*)(int) noexcept>();
    test_is_copy_assignable<int (class_type::*)(int) & noexcept>();
    test_is_copy_assignable<int (class_type::*)(int) && noexcept>();
    test_is_copy_assignable<int (class_type::*)(int) const noexcept>();
    test_is_copy_assignable<int (class_type::*)(int) const & noexcept>();
    test_is_copy_assignable<int (class_type::*)(int) const && noexcept>();

    test_is_copy_assignable<int (class_type::*)(...)>();
    test_is_copy_assignable<int (class_type::*)(...)&>();
    test_is_copy_assignable<int (class_type::*)(...) &&>();
    test_is_copy_assignable<int (class_type::*)(...) const>();
    test_is_copy_assignable<int (class_type::*)(...) const&>();
    test_is_copy_assignable<int (class_type::*)(...) const&&>();
    test_is_copy_assignable<int (class_type::*)(...) noexcept>();
    test_is_copy_assignable<int (class_type::*)(...) & noexcept>();
    test_is_copy_assignable<int (class_type::*)(...) && noexcept>();
    test_is_copy_assignable<int (class_type::*)(...) const noexcept>();
    test_is_copy_assignable<int (class_type::*)(...) const & noexcept>();
    test_is_copy_assignable<int (class_type::*)(...) const && noexcept>();

    test_is_copy_assignable<int (class_type::*)(int, ...)>();
    test_is_copy_assignable<int (class_type::*)(int, ...)&>();
    test_is_copy_assignable<int (class_type::*)(int, ...) &&>();
    test_is_copy_assignable<int (class_type::*)(int, ...) const>();
    test_is_copy_assignable<int (class_type::*)(int, ...) const&>();
    test_is_copy_assignable<int (class_type::*)(int, ...) const&&>();
    test_is_copy_assignable<int (class_type::*)(int, ...) noexcept>();
    test_is_copy_assignable<int (class_type::*)(int, ...) & noexcept>();
    test_is_copy_assignable<int (class_type::*)(int, ...) && noexcept>();
    test_is_copy_assignable<int (class_type::*)(int, ...) const noexcept>();
    test_is_copy_assignable<int (class_type::*)(int, ...) const & noexcept>();
    test_is_copy_assignable<int (class_type::*)(int, ...) const && noexcept>();
}
