#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/bugs/gcc_102305.hpp>
#include <phi/compiler_support/char8_t.hpp>
#include <phi/compiler_support/compiler.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_copy_constructible.hpp>
#include <type_traits>
#include <vector>

// TODO: A lot of these tests currently don't work with MSVC correctly

template <typename TypeT>
void test_is_copy_constructible_impl()
{
#if PHI_HAS_WORKING_IS_COPY_CONSTRUCTIBLE()
    STATIC_REQUIRE(phi::is_copy_constructible<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_copy_constructible<TypeT>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_copy_constructible_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_not_copy_constructible_v<TypeT>);
#    endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_copy_constructible<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_copy_constructible<TypeT>);

    // Standard compatibility
    STATIC_REQUIRE(std::is_copy_constructible<TypeT>::value);
#endif
}

template <typename TypeT>
void test_is_copy_constructible()
{
    test_is_copy_constructible_impl<TypeT>();
    test_is_copy_constructible_impl<const TypeT>();
}

template <typename TypeT>
void test_is_not_copy_constructible_impl()
{
#if PHI_HAS_WORKING_IS_COPY_CONSTRUCTIBLE()
    STATIC_REQUIRE_FALSE(phi::is_copy_constructible<TypeT>::value);
    STATIC_REQUIRE(phi::is_not_copy_constructible<TypeT>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_copy_constructible_v<TypeT>);
    STATIC_REQUIRE(phi::is_not_copy_constructible_v<TypeT>);
#    endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_copy_constructible<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_copy_constructible<TypeT>);

    // Standard compatibility
    STATIC_REQUIRE_FALSE(std::is_copy_constructible<TypeT>::value);
#endif
}

template <typename TypeT>
void test_is_not_copy_constructible()
{
    test_is_not_copy_constructible_impl<TypeT>();
    test_is_not_copy_constructible_impl<const TypeT>();
}

struct A
{
    A(const A&);
};

// NOLINTNEXTLINE(readability-identifier-naming)
class B
{
    // NOLINTNEXTLINE(modernize-use-equals-delete)
    B(const B&);
};

struct C
{
    // NOLINTNEXTLINE(misc-unconventional-assign-operator)
    C(C&); // not const

    // NOLINTNEXTLINE(misc-unconventional-assign-operator)
    void operator=(C&); // not const
};

TEST_CASE("is_copy_constructible")
{
    test_is_copy_constructible<A>();
    test_is_not_copy_constructible<B>();
    test_is_not_copy_constructible<C>();

    test_is_not_copy_constructible<void>();
    test_is_copy_constructible<phi::nullptr_t>();
    test_is_copy_constructible<bool>();
    test_is_copy_constructible<char>();
    test_is_copy_constructible<signed char>();
    test_is_copy_constructible<unsigned char>();
    test_is_copy_constructible<short>();
    test_is_copy_constructible<unsigned short>();
    test_is_copy_constructible<int>();
    test_is_copy_constructible<unsigned int>();
    test_is_copy_constructible<long>();
    test_is_copy_constructible<unsigned long>();
    test_is_copy_constructible<long long>();
    test_is_copy_constructible<unsigned long long>();
    test_is_copy_constructible<float>();
    test_is_copy_constructible<double>();
    test_is_copy_constructible<long double>();
    test_is_copy_constructible<char8_t>();
    test_is_copy_constructible<char16_t>();
    test_is_copy_constructible<char32_t>();
    test_is_copy_constructible<wchar_t>();

    test_is_copy_constructible<phi::boolean>();
    test_is_copy_constructible<phi::integer<signed char>>();
    test_is_copy_constructible<phi::integer<unsigned char>>();
    test_is_copy_constructible<phi::integer<short>>();
    test_is_copy_constructible<phi::integer<unsigned short>>();
    test_is_copy_constructible<phi::integer<int>>();
    test_is_copy_constructible<phi::integer<unsigned int>>();
    test_is_copy_constructible<phi::integer<long>>();
    test_is_copy_constructible<phi::integer<unsigned long>>();
    test_is_copy_constructible<phi::integer<long long>>();
    test_is_copy_constructible<phi::integer<unsigned long long>>();
    test_is_copy_constructible<phi::floating_point<float>>();
    test_is_copy_constructible<phi::floating_point<double>>();
    test_is_copy_constructible<phi::floating_point<long double>>();

    test_is_copy_constructible<std::vector<int>>();
    test_is_not_copy_constructible<phi::scope_ptr<int>>();

    test_is_copy_constructible<int&>();
    test_is_copy_constructible<const int&>();
    test_is_copy_constructible<volatile int&>();
    test_is_copy_constructible<const volatile int&>();
    test_is_not_copy_constructible<int&&>();
    test_is_not_copy_constructible<const int&&>();
    test_is_not_copy_constructible<volatile int&&>();
    test_is_not_copy_constructible<const volatile int&&>();
    test_is_copy_constructible<int*>();
    test_is_copy_constructible<const int*>();
    test_is_copy_constructible<volatile int*>();
    test_is_copy_constructible<const volatile int*>();
    test_is_copy_constructible<int**>();
    test_is_copy_constructible<const int**>();
    test_is_copy_constructible<volatile int**>();
    test_is_copy_constructible<const volatile int**>();
    test_is_copy_constructible<int*&>();
    test_is_copy_constructible<const int*&>();
    test_is_copy_constructible<volatile int*&>();
    test_is_copy_constructible<const volatile int*&>();
    test_is_not_copy_constructible<int*&&>();
    test_is_not_copy_constructible<const int*&&>();
    test_is_not_copy_constructible<volatile int*&&>();
    test_is_not_copy_constructible<const volatile int*&&>();
    test_is_copy_constructible<void*>();
    test_is_not_copy_constructible<char[3]>();
#if PHI_SUPPORTS_IS_CONSTRUCTIBLE()
    test_is_not_copy_constructible<char[]>();
    test_is_not_copy_constructible<char*[]>();
    test_is_copy_constructible<int(*)[]>();
    test_is_copy_constructible<int(&)[]>();
    test_is_not_copy_constructible<int(&&)[]>();
    test_is_not_copy_constructible<char[][2]>();
    test_is_not_copy_constructible<char*[][2]>();
    test_is_copy_constructible<int(*)[][2]>();
    test_is_copy_constructible<int(&)[][2]>();
    test_is_not_copy_constructible<int(&&)[][2]>();
#endif
    test_is_not_copy_constructible<char* [3]>();
    test_is_copy_constructible<int(*)[3]>();
    test_is_copy_constructible<int(&)[3]>();
    test_is_not_copy_constructible<int(&&)[3]>();
    test_is_not_copy_constructible<char[3][2]>();
    test_is_not_copy_constructible<char* [3][2]>();
    test_is_copy_constructible<int(*)[3][2]>();
    test_is_copy_constructible<int(&)[3][2]>();
    test_is_not_copy_constructible<int(&&)[3][2]>();
    test_is_copy_constructible<class_type>();
#if PHI_SUPPORTS_IS_CONSTRUCTIBLE()
    test_is_not_copy_constructible<class_type[]>();
#endif
    test_is_not_copy_constructible<class_type[2]>();
    test_is_copy_constructible<template_type<void>>();
    test_is_copy_constructible<template_type<int>>();
    test_is_copy_constructible<template_type<class_type>>();
    test_is_copy_constructible<template_type<incomplete_type>>();
    test_is_copy_constructible<variadic_template<>>();
    test_is_copy_constructible<variadic_template<void>>();
    test_is_copy_constructible<variadic_template<int>>();
    test_is_copy_constructible<variadic_template<class_type>>();
    test_is_copy_constructible<variadic_template<incomplete_type>>();
    test_is_copy_constructible<variadic_template<int, void, class_type, volatile char[]>>();
    test_is_copy_constructible<public_derived_from<base>>();
    test_is_copy_constructible<public_derived_from<derived>>();
    test_is_copy_constructible<public_derived_from<class_type>>();
    test_is_copy_constructible<private_derived_from<base>>();
    test_is_copy_constructible<private_derived_from<derived>>();
    test_is_copy_constructible<private_derived_from<class_type>>();
    test_is_copy_constructible<protected_derived_from<base>>();
    test_is_copy_constructible<protected_derived_from<derived>>();
    test_is_copy_constructible<protected_derived_from<class_type>>();
    test_is_copy_constructible<union_type>();
    test_is_copy_constructible<non_empty_union>();
    test_is_copy_constructible<empty>();
    test_is_copy_constructible<not_empty>();
    test_is_copy_constructible<bit_zero>();
    test_is_copy_constructible<bit_one>();
    test_is_copy_constructible<base>();
    test_is_copy_constructible<derived>();
    test_is_not_copy_constructible<abstract>();
#if PHI_COMPILER_IS_NOT(MSVC) || PHI_SUPPORTS_IS_CONSTRUCTIBLE()
    test_is_not_copy_constructible<public_abstract>();
    test_is_not_copy_constructible<private_abstract>();
    test_is_not_copy_constructible<protected_abstract>();
#endif
#if PHI_SUPPORTS_IS_CONSTRUCTIBLE() && !PHI_HAS_BUG_GCC_102305()
    test_is_not_copy_constructible<abstract_template<int>>();
#endif
    test_is_copy_constructible<abstract_template<double>>();
#if PHI_COMPILER_IS_NOT(GCC) && PHI_COMPILER_IS_NOT(MINGW) &&                                      \
        (PHI_COMPILER_IS_NOT(MSVC) || PHI_SUPPORTS_IS_CONSTRUCTIBLE())
    test_is_not_copy_constructible<abstract_template<class_type>>();
#    if PHI_SUPPORTS_IS_CONSTRUCTIBLE()
    test_is_not_copy_constructible<abstract_template<incomplete_type>>();
#    endif
#endif
    test_is_copy_constructible<final_type>();
    test_is_copy_constructible<public_destructor>();
    test_is_not_copy_constructible<protected_destructor>();
    test_is_not_copy_constructible<private_destructor>();
    test_is_copy_constructible<virtual_public_destructor>();
    test_is_not_copy_constructible<virtual_protected_destructor>();
    test_is_not_copy_constructible<virtual_private_destructor>();
#if PHI_COMPILER_IS_NOT(MSVC) || PHI_SUPPORTS_IS_CONSTRUCTIBLE()
    test_is_not_copy_constructible<pure_public_destructor>();
#endif
    test_is_not_copy_constructible<pure_protected_destructor>();
    test_is_not_copy_constructible<pure_private_destructor>();
    test_is_not_copy_constructible<deleted_public_destructor>();
    test_is_not_copy_constructible<deleted_protected_destructor>();
    test_is_not_copy_constructible<deleted_private_destructor>();
    test_is_not_copy_constructible<deleted_virtual_public_destructor>();
    test_is_not_copy_constructible<deleted_virtual_protected_destructor>();
    test_is_not_copy_constructible<deleted_virtual_private_destructor>();
#if PHI_COMPILER_IS_NOT(MSVC) || PHI_SUPPORTS_IS_CONSTRUCTIBLE()
    test_is_copy_constructible<Enum>();
    test_is_copy_constructible<EnumSigned>();
    test_is_copy_constructible<EnumUnsigned>();
    test_is_copy_constructible<EnumClass>();
    test_is_copy_constructible<EnumStruct>();
#endif
    test_is_not_copy_constructible<function_type>();
#if PHI_COMPILER_IS_NOT(MSVC) || PHI_SUPPORTS_IS_CONSTRUCTIBLE()
    test_is_copy_constructible<function_ptr>();
    test_is_copy_constructible<member_object_ptr>();
    test_is_copy_constructible<member_function_ptr>();
    test_is_copy_constructible<int class_type::*>();
    test_is_copy_constructible<float class_type::*>();
    test_is_copy_constructible<void * class_type::*>();
    test_is_copy_constructible<int * class_type::*>();
#endif
    test_is_copy_constructible<int class_type::*&>();
    test_is_copy_constructible<float class_type::*&>();
    test_is_copy_constructible<void * class_type::*&>();
    test_is_copy_constructible<int * class_type::*&>();
    test_is_not_copy_constructible<int class_type::*&&>();
    test_is_not_copy_constructible<float class_type::*&&>();
    test_is_not_copy_constructible<void * class_type::*&&>();
    test_is_not_copy_constructible<int * class_type::*&&>();
#if PHI_COMPILER_IS_NOT(MSVC) || PHI_SUPPORTS_IS_CONSTRUCTIBLE()
    test_is_copy_constructible<int class_type::* const>();
    test_is_copy_constructible<float class_type::* const>();
    test_is_copy_constructible<void * class_type::* const>();
#endif
    test_is_copy_constructible<int class_type::* const&>();
    test_is_copy_constructible<float class_type::* const&>();
    test_is_copy_constructible<void * class_type::* const&>();
    test_is_not_copy_constructible<int class_type::* const&&>();
    test_is_not_copy_constructible<float class_type::* const&&>();
    test_is_not_copy_constructible<void * class_type::* const&&>();
#if PHI_COMPILER_IS_NOT(MSVC) || PHI_SUPPORTS_IS_CONSTRUCTIBLE()
    test_is_copy_constructible<int class_type::* volatile>();
    test_is_copy_constructible<float class_type::* volatile>();
    test_is_copy_constructible<void * class_type::* volatile>();
#endif
    test_is_copy_constructible<int class_type::* volatile&>();
    test_is_copy_constructible<float class_type::* volatile&>();
    test_is_copy_constructible<void * class_type::* volatile&>();
    test_is_not_copy_constructible<int class_type::* volatile&&>();
    test_is_not_copy_constructible<float class_type::* volatile&&>();
    test_is_not_copy_constructible<void * class_type::* volatile&&>();
#if PHI_COMPILER_IS_NOT(MSVC) || PHI_SUPPORTS_IS_CONSTRUCTIBLE()
    test_is_copy_constructible<int class_type::* const volatile>();
    test_is_copy_constructible<float class_type::* const volatile>();
    test_is_copy_constructible<void * class_type::* const volatile>();
#endif
    test_is_copy_constructible<int class_type::* const volatile&>();
    test_is_copy_constructible<float class_type::* const volatile&>();
    test_is_copy_constructible<void * class_type::* const volatile&>();
    test_is_not_copy_constructible<int class_type::* const volatile&&>();
    test_is_not_copy_constructible<float class_type::* const volatile&&>();
    test_is_not_copy_constructible<void * class_type::* const volatile&&>();
    test_is_not_copy_constructible<non_copyable>();
    test_is_copy_constructible<non_moveable>();
    test_is_not_copy_constructible<non_constructible>();
    test_is_copy_constructible<tracked>();
    test_is_copy_constructible<trap_constructible>();
    test_is_copy_constructible<trap_implicit_conversion>();
    test_is_copy_constructible<trap_comma>();
    test_is_copy_constructible<trap_call>();
    test_is_copy_constructible<trap_self_assign>();
    test_is_copy_constructible<trap_deref>();
    test_is_copy_constructible<trap_array_subscript>();

    test_is_not_copy_constructible<void()>();
    test_is_not_copy_constructible<void()&>();
    test_is_not_copy_constructible<void() &&>();
    test_is_not_copy_constructible<void() const>();
    test_is_not_copy_constructible<void() const&>();
    test_is_not_copy_constructible<void() const&&>();
    test_is_not_copy_constructible<void() volatile>();
    test_is_not_copy_constructible<void() volatile&>();
    test_is_not_copy_constructible<void() volatile&&>();
    test_is_not_copy_constructible<void() const volatile>();
    test_is_not_copy_constructible<void() const volatile&>();
    test_is_not_copy_constructible<void() const volatile&&>();
    test_is_not_copy_constructible<void() noexcept>();
    test_is_not_copy_constructible<void() & noexcept>();
    test_is_not_copy_constructible<void() && noexcept>();
    test_is_not_copy_constructible<void() const noexcept>();
    test_is_not_copy_constructible<void() const & noexcept>();
    test_is_not_copy_constructible<void() const && noexcept>();
    test_is_not_copy_constructible<void() volatile noexcept>();
    test_is_not_copy_constructible<void() volatile & noexcept>();
    test_is_not_copy_constructible<void() volatile && noexcept>();
    test_is_not_copy_constructible<void() const volatile noexcept>();
    test_is_not_copy_constructible<void() const volatile & noexcept>();
    test_is_not_copy_constructible<void() const volatile && noexcept>();

    test_is_not_copy_constructible<void(int)>();
    test_is_not_copy_constructible<void(int)&>();
    test_is_not_copy_constructible<void(int) &&>();
    test_is_not_copy_constructible<void(int) const>();
    test_is_not_copy_constructible<void(int) const&>();
    test_is_not_copy_constructible<void(int) const&&>();
    test_is_not_copy_constructible<void(int) volatile>();
    test_is_not_copy_constructible<void(int) volatile&>();
    test_is_not_copy_constructible<void(int) volatile&&>();
    test_is_not_copy_constructible<void(int) const volatile>();
    test_is_not_copy_constructible<void(int) const volatile&>();
    test_is_not_copy_constructible<void(int) const volatile&&>();
    test_is_not_copy_constructible<void(int) noexcept>();
    test_is_not_copy_constructible<void(int) & noexcept>();
    test_is_not_copy_constructible<void(int) && noexcept>();
    test_is_not_copy_constructible<void(int) const noexcept>();
    test_is_not_copy_constructible<void(int) const & noexcept>();
    test_is_not_copy_constructible<void(int) const && noexcept>();
    test_is_not_copy_constructible<void(int) volatile noexcept>();
    test_is_not_copy_constructible<void(int) volatile & noexcept>();
    test_is_not_copy_constructible<void(int) volatile && noexcept>();
    test_is_not_copy_constructible<void(int) const volatile noexcept>();
    test_is_not_copy_constructible<void(int) const volatile & noexcept>();
    test_is_not_copy_constructible<void(int) const volatile && noexcept>();

    test_is_not_copy_constructible<void(...)>();
    test_is_not_copy_constructible<void(...)&>();
    test_is_not_copy_constructible<void(...) &&>();
    test_is_not_copy_constructible<void(...) const>();
    test_is_not_copy_constructible<void(...) const&>();
    test_is_not_copy_constructible<void(...) const&&>();
    test_is_not_copy_constructible<void(...) volatile>();
    test_is_not_copy_constructible<void(...) volatile&>();
    test_is_not_copy_constructible<void(...) volatile&&>();
    test_is_not_copy_constructible<void(...) const volatile>();
    test_is_not_copy_constructible<void(...) const volatile&>();
    test_is_not_copy_constructible<void(...) const volatile&&>();
    test_is_not_copy_constructible<void(...) noexcept>();
    test_is_not_copy_constructible<void(...) & noexcept>();
    test_is_not_copy_constructible<void(...) && noexcept>();
    test_is_not_copy_constructible<void(...) const noexcept>();
    test_is_not_copy_constructible<void(...) const & noexcept>();
    test_is_not_copy_constructible<void(...) const && noexcept>();
    test_is_not_copy_constructible<void(...) volatile noexcept>();
    test_is_not_copy_constructible<void(...) volatile & noexcept>();
    test_is_not_copy_constructible<void(...) volatile && noexcept>();
    test_is_not_copy_constructible<void(...) const volatile noexcept>();
    test_is_not_copy_constructible<void(...) const volatile & noexcept>();
    test_is_not_copy_constructible<void(...) const volatile && noexcept>();

    test_is_not_copy_constructible<void(int, ...)>();
    test_is_not_copy_constructible<void(int, ...)&>();
    test_is_not_copy_constructible<void(int, ...) &&>();
    test_is_not_copy_constructible<void(int, ...) const>();
    test_is_not_copy_constructible<void(int, ...) const&>();
    test_is_not_copy_constructible<void(int, ...) const&&>();
    test_is_not_copy_constructible<void(int, ...) volatile>();
    test_is_not_copy_constructible<void(int, ...) volatile&>();
    test_is_not_copy_constructible<void(int, ...) volatile&&>();
    test_is_not_copy_constructible<void(int, ...) const volatile>();
    test_is_not_copy_constructible<void(int, ...) const volatile&>();
    test_is_not_copy_constructible<void(int, ...) const volatile&&>();
    test_is_not_copy_constructible<void(int, ...) noexcept>();
    test_is_not_copy_constructible<void(int, ...) & noexcept>();
    test_is_not_copy_constructible<void(int, ...) && noexcept>();
    test_is_not_copy_constructible<void(int, ...) const noexcept>();
    test_is_not_copy_constructible<void(int, ...) const & noexcept>();
    test_is_not_copy_constructible<void(int, ...) const && noexcept>();
    test_is_not_copy_constructible<void(int, ...) volatile noexcept>();
    test_is_not_copy_constructible<void(int, ...) volatile & noexcept>();
    test_is_not_copy_constructible<void(int, ...) volatile && noexcept>();
    test_is_not_copy_constructible<void(int, ...) const volatile noexcept>();
    test_is_not_copy_constructible<void(int, ...) const volatile & noexcept>();
    test_is_not_copy_constructible<void(int, ...) const volatile && noexcept>();

    test_is_not_copy_constructible<int()>();
    test_is_not_copy_constructible<int()&>();
    test_is_not_copy_constructible<int() &&>();
    test_is_not_copy_constructible<int() const>();
    test_is_not_copy_constructible<int() const&>();
    test_is_not_copy_constructible<int() const&&>();
    test_is_not_copy_constructible<int() volatile>();
    test_is_not_copy_constructible<int() volatile&>();
    test_is_not_copy_constructible<int() volatile&&>();
    test_is_not_copy_constructible<int() const volatile>();
    test_is_not_copy_constructible<int() const volatile&>();
    test_is_not_copy_constructible<int() const volatile&&>();
    test_is_not_copy_constructible<int() noexcept>();
    test_is_not_copy_constructible<int() & noexcept>();
    test_is_not_copy_constructible<int() && noexcept>();
    test_is_not_copy_constructible<int() const noexcept>();
    test_is_not_copy_constructible<int() const & noexcept>();
    test_is_not_copy_constructible<int() const && noexcept>();
    test_is_not_copy_constructible<int() volatile noexcept>();
    test_is_not_copy_constructible<int() volatile & noexcept>();
    test_is_not_copy_constructible<int() volatile && noexcept>();
    test_is_not_copy_constructible<int() const volatile noexcept>();
    test_is_not_copy_constructible<int() const volatile & noexcept>();
    test_is_not_copy_constructible<int() const volatile && noexcept>();

    test_is_not_copy_constructible<int(int)>();
    test_is_not_copy_constructible<int(int)&>();
    test_is_not_copy_constructible<int(int) &&>();
    test_is_not_copy_constructible<int(int) const>();
    test_is_not_copy_constructible<int(int) const&>();
    test_is_not_copy_constructible<int(int) const&&>();
    test_is_not_copy_constructible<int(int) volatile>();
    test_is_not_copy_constructible<int(int) volatile&>();
    test_is_not_copy_constructible<int(int) volatile&&>();
    test_is_not_copy_constructible<int(int) const volatile>();
    test_is_not_copy_constructible<int(int) const volatile&>();
    test_is_not_copy_constructible<int(int) const volatile&&>();
    test_is_not_copy_constructible<int(int) noexcept>();
    test_is_not_copy_constructible<int(int) & noexcept>();
    test_is_not_copy_constructible<int(int) && noexcept>();
    test_is_not_copy_constructible<int(int) const noexcept>();
    test_is_not_copy_constructible<int(int) const & noexcept>();
    test_is_not_copy_constructible<int(int) const && noexcept>();
    test_is_not_copy_constructible<int(int) volatile noexcept>();
    test_is_not_copy_constructible<int(int) volatile & noexcept>();
    test_is_not_copy_constructible<int(int) volatile && noexcept>();
    test_is_not_copy_constructible<int(int) const volatile noexcept>();
    test_is_not_copy_constructible<int(int) const volatile & noexcept>();
    test_is_not_copy_constructible<int(int) const volatile && noexcept>();

    test_is_not_copy_constructible<int(...)>();
    test_is_not_copy_constructible<int(...)&>();
    test_is_not_copy_constructible<int(...) &&>();
    test_is_not_copy_constructible<int(...) const>();
    test_is_not_copy_constructible<int(...) const&>();
    test_is_not_copy_constructible<int(...) const&&>();
    test_is_not_copy_constructible<int(...) volatile>();
    test_is_not_copy_constructible<int(...) volatile&>();
    test_is_not_copy_constructible<int(...) volatile&&>();
    test_is_not_copy_constructible<int(...) const volatile>();
    test_is_not_copy_constructible<int(...) const volatile&>();
    test_is_not_copy_constructible<int(...) const volatile&&>();
    test_is_not_copy_constructible<int(...) noexcept>();
    test_is_not_copy_constructible<int(...) & noexcept>();
    test_is_not_copy_constructible<int(...) && noexcept>();
    test_is_not_copy_constructible<int(...) const noexcept>();
    test_is_not_copy_constructible<int(...) const & noexcept>();
    test_is_not_copy_constructible<int(...) const && noexcept>();
    test_is_not_copy_constructible<int(...) volatile noexcept>();
    test_is_not_copy_constructible<int(...) volatile & noexcept>();
    test_is_not_copy_constructible<int(...) volatile && noexcept>();
    test_is_not_copy_constructible<int(...) const volatile noexcept>();
    test_is_not_copy_constructible<int(...) const volatile & noexcept>();
    test_is_not_copy_constructible<int(...) const volatile && noexcept>();

    test_is_not_copy_constructible<int(int, ...)>();
    test_is_not_copy_constructible<int(int, ...)&>();
    test_is_not_copy_constructible<int(int, ...) &&>();
    test_is_not_copy_constructible<int(int, ...) const>();
    test_is_not_copy_constructible<int(int, ...) const&>();
    test_is_not_copy_constructible<int(int, ...) const&&>();
    test_is_not_copy_constructible<int(int, ...) volatile>();
    test_is_not_copy_constructible<int(int, ...) volatile&>();
    test_is_not_copy_constructible<int(int, ...) volatile&&>();
    test_is_not_copy_constructible<int(int, ...) const volatile>();
    test_is_not_copy_constructible<int(int, ...) const volatile&>();
    test_is_not_copy_constructible<int(int, ...) const volatile&&>();
    test_is_not_copy_constructible<int(int, ...) noexcept>();
    test_is_not_copy_constructible<int(int, ...) & noexcept>();
    test_is_not_copy_constructible<int(int, ...) && noexcept>();
    test_is_not_copy_constructible<int(int, ...) const noexcept>();
    test_is_not_copy_constructible<int(int, ...) const & noexcept>();
    test_is_not_copy_constructible<int(int, ...) const && noexcept>();
    test_is_not_copy_constructible<int(int, ...) volatile noexcept>();
    test_is_not_copy_constructible<int(int, ...) volatile & noexcept>();
    test_is_not_copy_constructible<int(int, ...) volatile && noexcept>();
    test_is_not_copy_constructible<int(int, ...) const volatile noexcept>();
    test_is_not_copy_constructible<int(int, ...) const volatile & noexcept>();
    test_is_not_copy_constructible<int(int, ...) const volatile && noexcept>();

#if PHI_COMPILER_IS_NOT(MSVC) || PHI_SUPPORTS_IS_CONSTRUCTIBLE()
    test_is_copy_constructible<void (*)()>();
    test_is_copy_constructible<void (*)() noexcept>();

    test_is_copy_constructible<void (*)(int)>();
    test_is_copy_constructible<void (*)(int) noexcept>();

    test_is_copy_constructible<void (*)(...)>();
    test_is_copy_constructible<void (*)(...) noexcept>();

    test_is_copy_constructible<void (*)(int, ...)>();
    test_is_copy_constructible<void (*)(int, ...) noexcept>();

    test_is_copy_constructible<int (*)()>();
    test_is_copy_constructible<int (*)() noexcept>();

    test_is_copy_constructible<int (*)(int)>();
    test_is_copy_constructible<int (*)(int) noexcept>();

    test_is_copy_constructible<int (*)(...)>();
    test_is_copy_constructible<int (*)(...) noexcept>();

    test_is_copy_constructible<int (*)(int, ...)>();
    test_is_copy_constructible<int (*)(int, ...) noexcept>();
#endif

    test_is_copy_constructible<void (&)()>();
    test_is_copy_constructible<void (&)() noexcept>();

    test_is_copy_constructible<void (&)(int)>();
    test_is_copy_constructible<void (&)(int) noexcept>();

    test_is_copy_constructible<void (&)(...)>();
    test_is_copy_constructible<void (&)(...) noexcept>();

    test_is_copy_constructible<void (&)(int, ...)>();
    test_is_copy_constructible<void (&)(int, ...) noexcept>();

    test_is_copy_constructible<int (&)()>();
    test_is_copy_constructible<int (&)() noexcept>();

    test_is_copy_constructible<int (&)(int)>();
    test_is_copy_constructible<int (&)(int) noexcept>();

    test_is_copy_constructible<int (&)(...)>();
    test_is_copy_constructible<int (&)(...) noexcept>();

    test_is_copy_constructible<int (&)(int, ...)>();
    test_is_copy_constructible<int (&)(int, ...) noexcept>();

    test_is_copy_constructible<void (&&)()>();
    test_is_copy_constructible<void (&&)() noexcept>();

    test_is_copy_constructible<void (&&)(int)>();
    test_is_copy_constructible<void (&&)(int) noexcept>();

    test_is_copy_constructible<void (&&)(...)>();
    test_is_copy_constructible<void (&&)(...) noexcept>();

    test_is_copy_constructible<void (&&)(int, ...)>();
    test_is_copy_constructible<void (&&)(int, ...) noexcept>();

    test_is_copy_constructible<int (&&)()>();
    test_is_copy_constructible<int (&&)() noexcept>();

    test_is_copy_constructible<int (&&)(int)>();
    test_is_copy_constructible<int (&&)(int) noexcept>();

    test_is_copy_constructible<int (&&)(...)>();
    test_is_copy_constructible<int (&&)(...) noexcept>();

    test_is_copy_constructible<int (&&)(int, ...)>();
    test_is_copy_constructible<int (&&)(int, ...) noexcept>();

#if PHI_COMPILER_IS_NOT(MSVC) || PHI_SUPPORTS_IS_CONSTRUCTIBLE()
    test_is_copy_constructible<void (class_type::*)()>();
    test_is_copy_constructible<void (class_type::*)()&>();
    test_is_copy_constructible<void (class_type::*)() &&>();
    test_is_copy_constructible<void (class_type::*)() const>();
    test_is_copy_constructible<void (class_type::*)() const&>();
    test_is_copy_constructible<void (class_type::*)() const&&>();
    test_is_copy_constructible<void (class_type::*)() noexcept>();
    test_is_copy_constructible<void (class_type::*)() & noexcept>();
    test_is_copy_constructible<void (class_type::*)() && noexcept>();
    test_is_copy_constructible<void (class_type::*)() const noexcept>();
    test_is_copy_constructible<void (class_type::*)() const & noexcept>();
    test_is_copy_constructible<void (class_type::*)() const && noexcept>();

    test_is_copy_constructible<void (class_type::*)(int)>();
    test_is_copy_constructible<void (class_type::*)(int)&>();
    test_is_copy_constructible<void (class_type::*)(int) &&>();
    test_is_copy_constructible<void (class_type::*)(int) const>();
    test_is_copy_constructible<void (class_type::*)(int) const&>();
    test_is_copy_constructible<void (class_type::*)(int) const&&>();
    test_is_copy_constructible<void (class_type::*)(int) noexcept>();
    test_is_copy_constructible<void (class_type::*)(int) & noexcept>();
    test_is_copy_constructible<void (class_type::*)(int) && noexcept>();
    test_is_copy_constructible<void (class_type::*)(int) const noexcept>();
    test_is_copy_constructible<void (class_type::*)(int) const & noexcept>();
    test_is_copy_constructible<void (class_type::*)(int) const && noexcept>();

    test_is_copy_constructible<void (class_type::*)(...)>();
    test_is_copy_constructible<void (class_type::*)(...)&>();
    test_is_copy_constructible<void (class_type::*)(...) &&>();
    test_is_copy_constructible<void (class_type::*)(...) const>();
    test_is_copy_constructible<void (class_type::*)(...) const&>();
    test_is_copy_constructible<void (class_type::*)(...) const&&>();
    test_is_copy_constructible<void (class_type::*)(...) noexcept>();
    test_is_copy_constructible<void (class_type::*)(...) & noexcept>();
    test_is_copy_constructible<void (class_type::*)(...) && noexcept>();
    test_is_copy_constructible<void (class_type::*)(...) const noexcept>();
    test_is_copy_constructible<void (class_type::*)(...) const & noexcept>();
    test_is_copy_constructible<void (class_type::*)(...) const && noexcept>();

    test_is_copy_constructible<void (class_type::*)(int, ...)>();
    test_is_copy_constructible<void (class_type::*)(int, ...)&>();
    test_is_copy_constructible<void (class_type::*)(int, ...) &&>();
    test_is_copy_constructible<void (class_type::*)(int, ...) const>();
    test_is_copy_constructible<void (class_type::*)(int, ...) const&>();
    test_is_copy_constructible<void (class_type::*)(int, ...) const&&>();
    test_is_copy_constructible<void (class_type::*)(int, ...) noexcept>();
    test_is_copy_constructible<void (class_type::*)(int, ...) & noexcept>();
    test_is_copy_constructible<void (class_type::*)(int, ...) && noexcept>();
    test_is_copy_constructible<void (class_type::*)(int, ...) const noexcept>();
    test_is_copy_constructible<void (class_type::*)(int, ...) const & noexcept>();
    test_is_copy_constructible<void (class_type::*)(int, ...) const && noexcept>();

    test_is_copy_constructible<int (class_type::*)()>();
    test_is_copy_constructible<int (class_type::*)()&>();
    test_is_copy_constructible<int (class_type::*)() &&>();
    test_is_copy_constructible<int (class_type::*)() const>();
    test_is_copy_constructible<int (class_type::*)() const&>();
    test_is_copy_constructible<int (class_type::*)() const&&>();
    test_is_copy_constructible<int (class_type::*)() noexcept>();
    test_is_copy_constructible<int (class_type::*)() & noexcept>();
    test_is_copy_constructible<int (class_type::*)() && noexcept>();
    test_is_copy_constructible<int (class_type::*)() const noexcept>();
    test_is_copy_constructible<int (class_type::*)() const & noexcept>();
    test_is_copy_constructible<int (class_type::*)() const && noexcept>();

    test_is_copy_constructible<int (class_type::*)(int)>();
    test_is_copy_constructible<int (class_type::*)(int)&>();
    test_is_copy_constructible<int (class_type::*)(int) &&>();
    test_is_copy_constructible<int (class_type::*)(int) const>();
    test_is_copy_constructible<int (class_type::*)(int) const&>();
    test_is_copy_constructible<int (class_type::*)(int) const&&>();
    test_is_copy_constructible<int (class_type::*)(int) noexcept>();
    test_is_copy_constructible<int (class_type::*)(int) & noexcept>();
    test_is_copy_constructible<int (class_type::*)(int) && noexcept>();
    test_is_copy_constructible<int (class_type::*)(int) const noexcept>();
    test_is_copy_constructible<int (class_type::*)(int) const & noexcept>();
    test_is_copy_constructible<int (class_type::*)(int) const && noexcept>();

    test_is_copy_constructible<int (class_type::*)(...)>();
    test_is_copy_constructible<int (class_type::*)(...)&>();
    test_is_copy_constructible<int (class_type::*)(...) &&>();
    test_is_copy_constructible<int (class_type::*)(...) const>();
    test_is_copy_constructible<int (class_type::*)(...) const&>();
    test_is_copy_constructible<int (class_type::*)(...) const&&>();
    test_is_copy_constructible<int (class_type::*)(...) noexcept>();
    test_is_copy_constructible<int (class_type::*)(...) & noexcept>();
    test_is_copy_constructible<int (class_type::*)(...) && noexcept>();
    test_is_copy_constructible<int (class_type::*)(...) const noexcept>();
    test_is_copy_constructible<int (class_type::*)(...) const & noexcept>();
    test_is_copy_constructible<int (class_type::*)(...) const && noexcept>();

    test_is_copy_constructible<int (class_type::*)(int, ...)>();
    test_is_copy_constructible<int (class_type::*)(int, ...)&>();
    test_is_copy_constructible<int (class_type::*)(int, ...) &&>();
    test_is_copy_constructible<int (class_type::*)(int, ...) const>();
    test_is_copy_constructible<int (class_type::*)(int, ...) const&>();
    test_is_copy_constructible<int (class_type::*)(int, ...) const&&>();
    test_is_copy_constructible<int (class_type::*)(int, ...) noexcept>();
    test_is_copy_constructible<int (class_type::*)(int, ...) & noexcept>();
    test_is_copy_constructible<int (class_type::*)(int, ...) && noexcept>();
    test_is_copy_constructible<int (class_type::*)(int, ...) const noexcept>();
    test_is_copy_constructible<int (class_type::*)(int, ...) const & noexcept>();
    test_is_copy_constructible<int (class_type::*)(int, ...) const && noexcept>();
#endif
}
