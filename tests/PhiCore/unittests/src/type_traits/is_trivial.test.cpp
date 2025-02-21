#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_trivial.hpp>
#include <type_traits>
#include <vector>

template <typename TypeT>
void test_is_trivial_impl()
{
#if PHI_HAS_WORKING_IS_TRIVIAL()
    STATIC_REQUIRE(phi::is_trivial<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_trivial<TypeT>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_trivial_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_not_trivial_v<TypeT>);
#    endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_trivial<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_trivial<TypeT>);

    // Standard compatibility
    STATIC_REQUIRE(std::is_trivial<TypeT>::value);
#endif
}

template <typename TypeT>
void test_is_not_trivial_impl()
{
#if PHI_HAS_WORKING_IS_TRIVIAL()
    STATIC_REQUIRE_FALSE(phi::is_trivial<TypeT>::value);
    STATIC_REQUIRE(phi::is_not_trivial<TypeT>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_trivial_v<TypeT>);
    STATIC_REQUIRE(phi::is_not_trivial_v<TypeT>);
#    endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_trivial<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_trivial<TypeT>);

    // Standard compatibility
    STATIC_REQUIRE_FALSE(std::is_trivial<TypeT>::value);
#endif
}

template <typename TypeT>
void test_is_trivial()
{
    test_is_trivial_impl<TypeT>();
    test_is_trivial_impl<const TypeT>();
    test_is_trivial_impl<volatile TypeT>();
    test_is_trivial_impl<const volatile TypeT>();
}

template <typename TypeT>
void test_is_not_trivial()
{
    test_is_not_trivial_impl<TypeT>();
    test_is_not_trivial_impl<const TypeT>();
    test_is_not_trivial_impl<volatile TypeT>();
    test_is_not_trivial_impl<const volatile TypeT>();
}

struct A
{};

struct B
{
    B();
};

TEST_CASE("is_trivial")
{
    test_is_trivial<A>();
    test_is_not_trivial<B>();

    test_is_not_trivial<void>();
    test_is_trivial<phi::nullptr_t>();
    test_is_trivial<bool>();
    test_is_trivial<char>();
    test_is_trivial<signed char>();
    test_is_trivial<unsigned char>();
    test_is_trivial<short>();
    test_is_trivial<unsigned short>();
    test_is_trivial<int>();
    test_is_trivial<unsigned int>();
    test_is_trivial<long>();
    test_is_trivial<unsigned long>();
    test_is_trivial<long long>();
    test_is_trivial<unsigned long long>();
    test_is_trivial<float>();
    test_is_trivial<double>();
    test_is_trivial<long double>();
    test_is_trivial<char8_t>();
    test_is_trivial<char16_t>();
    test_is_trivial<char32_t>();
    test_is_trivial<wchar_t>();

#if PHI_COMPILER_IS(MSVC)
    test_is_not_trivial<phi::boolean>();
    test_is_not_trivial<phi::integer<signed char>>();
    test_is_not_trivial<phi::integer<unsigned char>>();
    test_is_not_trivial<phi::integer<short>>();
    test_is_not_trivial<phi::integer<unsigned short>>();
    test_is_not_trivial<phi::integer<int>>();
    test_is_not_trivial<phi::integer<unsigned int>>();
    test_is_not_trivial<phi::integer<long>>();
    test_is_not_trivial<phi::integer<unsigned long>>();
    test_is_not_trivial<phi::integer<long long>>();
    test_is_not_trivial<phi::integer<unsigned long long>>();
    test_is_not_trivial<phi::floating_point<float>>();
    test_is_not_trivial<phi::floating_point<double>>();
    test_is_not_trivial<phi::floating_point<long double>>();
#elif PHI_COMPILER_IS(WINCLANG)
    // TODO: Investigate these
    SKIP_CHECK();
    SKIP_CHECK();
    SKIP_CHECK();
    SKIP_CHECK();
    SKIP_CHECK();
    SKIP_CHECK();
    SKIP_CHECK();
    SKIP_CHECK();
    SKIP_CHECK();
    SKIP_CHECK();
    SKIP_CHECK();
    SKIP_CHECK();
    SKIP_CHECK();
    SKIP_CHECK();
#else
    test_is_trivial<phi::boolean>();
    test_is_trivial<phi::integer<signed char>>();
    test_is_trivial<phi::integer<unsigned char>>();
    test_is_trivial<phi::integer<short>>();
    test_is_trivial<phi::integer<unsigned short>>();
    test_is_trivial<phi::integer<int>>();
    test_is_trivial<phi::integer<unsigned int>>();
    test_is_trivial<phi::integer<long>>();
    test_is_trivial<phi::integer<unsigned long>>();
    test_is_trivial<phi::integer<long long>>();
    test_is_trivial<phi::integer<unsigned long long>>();
    test_is_trivial<phi::floating_point<float>>();
    test_is_trivial<phi::floating_point<double>>();
    test_is_trivial<phi::floating_point<long double>>();
#endif

    test_is_not_trivial<std::vector<int>>();
    test_is_not_trivial<phi::scope_ptr<int>>();

    test_is_not_trivial<int&>();
    test_is_not_trivial<const int&>();
    test_is_not_trivial<volatile int&>();
    test_is_not_trivial<const volatile int&>();
    test_is_not_trivial<int&&>();
    test_is_not_trivial<const int&&>();
    test_is_not_trivial<volatile int&&>();
    test_is_not_trivial<const volatile int&&>();
    test_is_trivial<int*>();
    test_is_trivial<const int*>();
    test_is_trivial<volatile int*>();
    test_is_trivial<const volatile int*>();
    test_is_trivial<int**>();
    test_is_trivial<const int**>();
    test_is_trivial<volatile int**>();
    test_is_trivial<const volatile int**>();
    test_is_not_trivial<int*&>();
    test_is_not_trivial<const int*&>();
    test_is_not_trivial<volatile int*&>();
    test_is_not_trivial<const volatile int*&>();
    test_is_not_trivial<int*&&>();
    test_is_not_trivial<const int*&&>();
    test_is_not_trivial<volatile int*&&>();
    test_is_not_trivial<const volatile int*&&>();
    test_is_trivial<void*>();
    test_is_trivial<char[3]>();
#if PHI_COMPILER_IS(MSVC) || PHI_COMPILER_IS(WINCLANG)
    SKIP_CHECK();
#else
    test_is_trivial<char[]>();
#endif
    test_is_trivial<char* [3]>();
#if PHI_COMPILER_IS(MSVC) || PHI_COMPILER_IS(WINCLANG)
    SKIP_CHECK();
#else
    test_is_trivial<char*[]>();
#endif
    test_is_trivial<int(*)[3]>();
    test_is_trivial<int(*)[]>();
    test_is_not_trivial<int(&)[3]>();
    test_is_not_trivial<int(&)[]>();
    test_is_not_trivial<int(&&)[3]>();
    test_is_not_trivial<int(&&)[]>();
    test_is_trivial<char[3][2]>();
#if PHI_COMPILER_IS(MSVC) || PHI_COMPILER_IS(WINCLANG)
    SKIP_CHECK();
#else
    test_is_trivial<char[][2]>();
#endif
    test_is_trivial<char* [3][2]>();
#if PHI_COMPILER_IS(MSVC) || PHI_COMPILER_IS(WINCLANG)
    SKIP_CHECK();
#else
    test_is_trivial<char*[][2]>();
#endif
    test_is_trivial<int(*)[3][2]>();
    test_is_trivial<int(*)[][2]>();
    test_is_not_trivial<int(&)[3][2]>();
    test_is_not_trivial<int(&)[][2]>();
    test_is_not_trivial<int(&&)[3][2]>();
    test_is_not_trivial<int(&&)[][2]>();
    test_is_not_trivial<class_type>();
    test_is_not_trivial<class_type[]>();
    test_is_not_trivial<class_type[2]>();
    test_is_trivial<template_type<void>>();
    test_is_trivial<template_type<int>>();
    test_is_trivial<template_type<class_type>>();
    test_is_trivial<template_type<incomplete_type>>();
    test_is_trivial<variadic_template<>>();
    test_is_trivial<variadic_template<void>>();
    test_is_trivial<variadic_template<int>>();
    test_is_trivial<variadic_template<class_type>>();
    test_is_trivial<variadic_template<incomplete_type>>();
    test_is_trivial<variadic_template<int, void, class_type, volatile char[]>>();
    test_is_trivial<public_derived_from<base>>();
    test_is_trivial<public_derived_from<derived>>();
    test_is_not_trivial<public_derived_from<class_type>>();
    test_is_trivial<private_derived_from<base>>();
    test_is_trivial<private_derived_from<derived>>();
    test_is_not_trivial<private_derived_from<class_type>>();
    test_is_trivial<protected_derived_from<base>>();
    test_is_trivial<protected_derived_from<derived>>();
    test_is_not_trivial<protected_derived_from<class_type>>();
    test_is_trivial<union_type>();
    test_is_trivial<non_empty_union>();
    test_is_trivial<empty>();
    test_is_not_trivial<not_empty>();
    test_is_trivial<bit_zero>();
    test_is_trivial<bit_one>();
    test_is_trivial<base>();
    test_is_trivial<derived>();
    test_is_not_trivial<abstract>();
    test_is_not_trivial<public_abstract>();
    test_is_not_trivial<private_abstract>();
    test_is_not_trivial<protected_abstract>();
    test_is_not_trivial<abstract_template<int>>();
    test_is_trivial<abstract_template<double>>();
    test_is_not_trivial<abstract_template<class_type>>();
    test_is_not_trivial<abstract_template<incomplete_type>>();
    test_is_trivial<final_type>();
    test_is_trivial<public_destructor>();
#if PHI_COMPILER_IS(MSVC) || PHI_COMPILER_IS(WINCLANG)
    SKIP_CHECK();
    SKIP_CHECK();
#else
    test_is_trivial<protected_destructor>();
    test_is_trivial<private_destructor>();
#endif
    test_is_not_trivial<virtual_public_destructor>();
    test_is_not_trivial<virtual_protected_destructor>();
    test_is_not_trivial<virtual_private_destructor>();
    test_is_not_trivial<pure_public_destructor>();
    test_is_not_trivial<pure_protected_destructor>();
    test_is_not_trivial<pure_private_destructor>();
#if PHI_COMPILER_IS(MSVC)
    test_is_not_trivial<deleted_public_destructor>();
    test_is_not_trivial<deleted_protected_destructor>();
    test_is_not_trivial<deleted_private_destructor>();
#elif PHI_COMPILER_IS(WINCLANG)
    SKIP_CHECK();
    SKIP_CHECK();
    SKIP_CHECK();
#else
    test_is_trivial<deleted_public_destructor>();
    test_is_trivial<deleted_protected_destructor>();
    test_is_trivial<deleted_private_destructor>();
#endif
    test_is_not_trivial<deleted_virtual_public_destructor>();
    test_is_not_trivial<deleted_virtual_protected_destructor>();
    test_is_not_trivial<deleted_virtual_private_destructor>();
    test_is_trivial<Enum>();
    test_is_trivial<EnumSigned>();
    test_is_trivial<EnumUnsigned>();
    test_is_trivial<EnumClass>();
    test_is_trivial<EnumStruct>();
    test_is_not_trivial<function_type>();
    test_is_trivial<function_ptr>();
    test_is_trivial<member_object_ptr>();
    test_is_trivial<member_function_ptr>();
    test_is_trivial<int class_type::*>();
    test_is_trivial<float class_type::*>();
    test_is_trivial<void * class_type::*>();
    test_is_trivial<int * class_type::*>();
    test_is_not_trivial<int class_type::*&>();
    test_is_not_trivial<float class_type::*&>();
    test_is_not_trivial<void * class_type::*&>();
    test_is_not_trivial<int * class_type::*&>();
    test_is_not_trivial<int class_type::*&&>();
    test_is_not_trivial<float class_type::*&&>();
    test_is_not_trivial<void * class_type::*&&>();
    test_is_not_trivial<int * class_type::*&&>();
    test_is_trivial<int class_type::* const>();
    test_is_trivial<float class_type::* const>();
    test_is_trivial<void * class_type::* const>();
    test_is_not_trivial<int class_type::* const&>();
    test_is_not_trivial<float class_type::* const&>();
    test_is_not_trivial<void * class_type::* const&>();
    test_is_not_trivial<int class_type::* const&&>();
    test_is_not_trivial<float class_type::* const&&>();
    test_is_not_trivial<void * class_type::* const&&>();
    test_is_trivial<int class_type::* volatile>();
    test_is_trivial<float class_type::* volatile>();
    test_is_trivial<void * class_type::* volatile>();
    test_is_not_trivial<int class_type::* volatile&>();
    test_is_not_trivial<float class_type::* volatile&>();
    test_is_not_trivial<void * class_type::* volatile&>();
    test_is_not_trivial<int class_type::* volatile&&>();
    test_is_not_trivial<float class_type::* volatile&&>();
    test_is_not_trivial<void * class_type::* volatile&&>();
    test_is_trivial<int class_type::* const volatile>();
    test_is_trivial<float class_type::* const volatile>();
    test_is_trivial<void * class_type::* const volatile>();
    test_is_not_trivial<int class_type::* const volatile&>();
    test_is_not_trivial<float class_type::* const volatile&>();
    test_is_not_trivial<void * class_type::* const volatile&>();
    test_is_not_trivial<int class_type::* const volatile&&>();
    test_is_not_trivial<float class_type::* const volatile&&>();
    test_is_not_trivial<void * class_type::* const volatile&&>();
    test_is_trivial<non_copyable>();
    test_is_trivial<non_moveable>();
#if PHI_COMPILER_IS(MSVC)
    test_is_not_trivial<non_constructible>();
#elif PHI_COMPILER_IS(WINCLANG)
    SKIP_CHECK();
#else
    test_is_trivial<non_constructible>();
#endif
    test_is_not_trivial<tracked>();
#if PHI_COMPILER_IS(GCC) || PHI_COMPILER_IS(MINGW) || PHI_COMPILER_IS(MSVC) ||                     \
        PHI_COMPILER_IS_BELOW(CLANG, 11, 0, 0)
    // TODO: Investigate why clang, GCC and MSVC disagree here so much
    test_is_trivial<trap_constructible>();
#elif PHI_COMPILER_IS(WINCLANG) || PHI_COMPILER_IS(APPLECLANG) || PHI_COMPILER_IS(EMCC)
    SKIP_CHECK();
#else
    test_is_not_trivial<trap_constructible>();
#endif
    test_is_trivial<trap_implicit_conversion>();
    test_is_trivial<trap_comma>();
    test_is_trivial<trap_call>();
    test_is_not_trivial<trap_self_assign>();
    test_is_trivial<trap_deref>();
    test_is_trivial<trap_array_subscript>();

    test_is_not_trivial<void()>();
    test_is_not_trivial<void()&>();
    test_is_not_trivial<void() &&>();
    test_is_not_trivial<void() const>();
    test_is_not_trivial<void() const&>();
    test_is_not_trivial<void() const&&>();
    test_is_not_trivial<void() volatile>();
    test_is_not_trivial<void() volatile&>();
    test_is_not_trivial<void() volatile&&>();
    test_is_not_trivial<void() const volatile>();
    test_is_not_trivial<void() const volatile&>();
    test_is_not_trivial<void() const volatile&&>();
    test_is_not_trivial<void() noexcept>();
    test_is_not_trivial<void() & noexcept>();
    test_is_not_trivial<void() && noexcept>();
    test_is_not_trivial<void() const noexcept>();
    test_is_not_trivial<void() const & noexcept>();
    test_is_not_trivial<void() const && noexcept>();
    test_is_not_trivial<void() volatile noexcept>();
    test_is_not_trivial<void() volatile & noexcept>();
    test_is_not_trivial<void() volatile && noexcept>();
    test_is_not_trivial<void() const volatile noexcept>();
    test_is_not_trivial<void() const volatile & noexcept>();
    test_is_not_trivial<void() const volatile && noexcept>();

    test_is_not_trivial<void(int)>();
    test_is_not_trivial<void(int)&>();
    test_is_not_trivial<void(int) &&>();
    test_is_not_trivial<void(int) const>();
    test_is_not_trivial<void(int) const&>();
    test_is_not_trivial<void(int) const&&>();
    test_is_not_trivial<void(int) volatile>();
    test_is_not_trivial<void(int) volatile&>();
    test_is_not_trivial<void(int) volatile&&>();
    test_is_not_trivial<void(int) const volatile>();
    test_is_not_trivial<void(int) const volatile&>();
    test_is_not_trivial<void(int) const volatile&&>();
    test_is_not_trivial<void(int) noexcept>();
    test_is_not_trivial<void(int) & noexcept>();
    test_is_not_trivial<void(int) && noexcept>();
    test_is_not_trivial<void(int) const noexcept>();
    test_is_not_trivial<void(int) const & noexcept>();
    test_is_not_trivial<void(int) const && noexcept>();
    test_is_not_trivial<void(int) volatile noexcept>();
    test_is_not_trivial<void(int) volatile & noexcept>();
    test_is_not_trivial<void(int) volatile && noexcept>();
    test_is_not_trivial<void(int) const volatile noexcept>();
    test_is_not_trivial<void(int) const volatile & noexcept>();
    test_is_not_trivial<void(int) const volatile && noexcept>();

    test_is_not_trivial<void(...)>();
    test_is_not_trivial<void(...)&>();
    test_is_not_trivial<void(...) &&>();
    test_is_not_trivial<void(...) const>();
    test_is_not_trivial<void(...) const&>();
    test_is_not_trivial<void(...) const&&>();
    test_is_not_trivial<void(...) volatile>();
    test_is_not_trivial<void(...) volatile&>();
    test_is_not_trivial<void(...) volatile&&>();
    test_is_not_trivial<void(...) const volatile>();
    test_is_not_trivial<void(...) const volatile&>();
    test_is_not_trivial<void(...) const volatile&&>();
    test_is_not_trivial<void(...) noexcept>();
    test_is_not_trivial<void(...) & noexcept>();
    test_is_not_trivial<void(...) && noexcept>();
    test_is_not_trivial<void(...) const noexcept>();
    test_is_not_trivial<void(...) const & noexcept>();
    test_is_not_trivial<void(...) const && noexcept>();
    test_is_not_trivial<void(...) volatile noexcept>();
    test_is_not_trivial<void(...) volatile & noexcept>();
    test_is_not_trivial<void(...) volatile && noexcept>();
    test_is_not_trivial<void(...) const volatile noexcept>();
    test_is_not_trivial<void(...) const volatile & noexcept>();
    test_is_not_trivial<void(...) const volatile && noexcept>();

    test_is_not_trivial<void(int, ...)>();
    test_is_not_trivial<void(int, ...)&>();
    test_is_not_trivial<void(int, ...) &&>();
    test_is_not_trivial<void(int, ...) const>();
    test_is_not_trivial<void(int, ...) const&>();
    test_is_not_trivial<void(int, ...) const&&>();
    test_is_not_trivial<void(int, ...) volatile>();
    test_is_not_trivial<void(int, ...) volatile&>();
    test_is_not_trivial<void(int, ...) volatile&&>();
    test_is_not_trivial<void(int, ...) const volatile>();
    test_is_not_trivial<void(int, ...) const volatile&>();
    test_is_not_trivial<void(int, ...) const volatile&&>();
    test_is_not_trivial<void(int, ...) noexcept>();
    test_is_not_trivial<void(int, ...) & noexcept>();
    test_is_not_trivial<void(int, ...) && noexcept>();
    test_is_not_trivial<void(int, ...) const noexcept>();
    test_is_not_trivial<void(int, ...) const & noexcept>();
    test_is_not_trivial<void(int, ...) const && noexcept>();
    test_is_not_trivial<void(int, ...) volatile noexcept>();
    test_is_not_trivial<void(int, ...) volatile & noexcept>();
    test_is_not_trivial<void(int, ...) volatile && noexcept>();
    test_is_not_trivial<void(int, ...) const volatile noexcept>();
    test_is_not_trivial<void(int, ...) const volatile & noexcept>();
    test_is_not_trivial<void(int, ...) const volatile && noexcept>();

    test_is_not_trivial<int()>();
    test_is_not_trivial<int()&>();
    test_is_not_trivial<int() &&>();
    test_is_not_trivial<int() const>();
    test_is_not_trivial<int() const&>();
    test_is_not_trivial<int() const&&>();
    test_is_not_trivial<int() volatile>();
    test_is_not_trivial<int() volatile&>();
    test_is_not_trivial<int() volatile&&>();
    test_is_not_trivial<int() const volatile>();
    test_is_not_trivial<int() const volatile&>();
    test_is_not_trivial<int() const volatile&&>();
    test_is_not_trivial<int() noexcept>();
    test_is_not_trivial<int() & noexcept>();
    test_is_not_trivial<int() && noexcept>();
    test_is_not_trivial<int() const noexcept>();
    test_is_not_trivial<int() const & noexcept>();
    test_is_not_trivial<int() const && noexcept>();
    test_is_not_trivial<int() volatile noexcept>();
    test_is_not_trivial<int() volatile & noexcept>();
    test_is_not_trivial<int() volatile && noexcept>();
    test_is_not_trivial<int() const volatile noexcept>();
    test_is_not_trivial<int() const volatile & noexcept>();
    test_is_not_trivial<int() const volatile && noexcept>();

    test_is_not_trivial<int(int)>();
    test_is_not_trivial<int(int)&>();
    test_is_not_trivial<int(int) &&>();
    test_is_not_trivial<int(int) const>();
    test_is_not_trivial<int(int) const&>();
    test_is_not_trivial<int(int) const&&>();
    test_is_not_trivial<int(int) volatile>();
    test_is_not_trivial<int(int) volatile&>();
    test_is_not_trivial<int(int) volatile&&>();
    test_is_not_trivial<int(int) const volatile>();
    test_is_not_trivial<int(int) const volatile&>();
    test_is_not_trivial<int(int) const volatile&&>();
    test_is_not_trivial<int(int) noexcept>();
    test_is_not_trivial<int(int) & noexcept>();
    test_is_not_trivial<int(int) && noexcept>();
    test_is_not_trivial<int(int) const noexcept>();
    test_is_not_trivial<int(int) const & noexcept>();
    test_is_not_trivial<int(int) const && noexcept>();
    test_is_not_trivial<int(int) volatile noexcept>();
    test_is_not_trivial<int(int) volatile & noexcept>();
    test_is_not_trivial<int(int) volatile && noexcept>();
    test_is_not_trivial<int(int) const volatile noexcept>();
    test_is_not_trivial<int(int) const volatile & noexcept>();
    test_is_not_trivial<int(int) const volatile && noexcept>();

    test_is_not_trivial<int(...)>();
    test_is_not_trivial<int(...)&>();
    test_is_not_trivial<int(...) &&>();
    test_is_not_trivial<int(...) const>();
    test_is_not_trivial<int(...) const&>();
    test_is_not_trivial<int(...) const&&>();
    test_is_not_trivial<int(...) volatile>();
    test_is_not_trivial<int(...) volatile&>();
    test_is_not_trivial<int(...) volatile&&>();
    test_is_not_trivial<int(...) const volatile>();
    test_is_not_trivial<int(...) const volatile&>();
    test_is_not_trivial<int(...) const volatile&&>();
    test_is_not_trivial<int(...) noexcept>();
    test_is_not_trivial<int(...) & noexcept>();
    test_is_not_trivial<int(...) && noexcept>();
    test_is_not_trivial<int(...) const noexcept>();
    test_is_not_trivial<int(...) const & noexcept>();
    test_is_not_trivial<int(...) const && noexcept>();
    test_is_not_trivial<int(...) volatile noexcept>();
    test_is_not_trivial<int(...) volatile & noexcept>();
    test_is_not_trivial<int(...) volatile && noexcept>();
    test_is_not_trivial<int(...) const volatile noexcept>();
    test_is_not_trivial<int(...) const volatile & noexcept>();
    test_is_not_trivial<int(...) const volatile && noexcept>();

    test_is_not_trivial<int(int, ...)>();
    test_is_not_trivial<int(int, ...)&>();
    test_is_not_trivial<int(int, ...) &&>();
    test_is_not_trivial<int(int, ...) const>();
    test_is_not_trivial<int(int, ...) const&>();
    test_is_not_trivial<int(int, ...) const&&>();
    test_is_not_trivial<int(int, ...) volatile>();
    test_is_not_trivial<int(int, ...) volatile&>();
    test_is_not_trivial<int(int, ...) volatile&&>();
    test_is_not_trivial<int(int, ...) const volatile>();
    test_is_not_trivial<int(int, ...) const volatile&>();
    test_is_not_trivial<int(int, ...) const volatile&&>();
    test_is_not_trivial<int(int, ...) noexcept>();
    test_is_not_trivial<int(int, ...) & noexcept>();
    test_is_not_trivial<int(int, ...) && noexcept>();
    test_is_not_trivial<int(int, ...) const noexcept>();
    test_is_not_trivial<int(int, ...) const & noexcept>();
    test_is_not_trivial<int(int, ...) const && noexcept>();
    test_is_not_trivial<int(int, ...) volatile noexcept>();
    test_is_not_trivial<int(int, ...) volatile & noexcept>();
    test_is_not_trivial<int(int, ...) volatile && noexcept>();
    test_is_not_trivial<int(int, ...) const volatile noexcept>();
    test_is_not_trivial<int(int, ...) const volatile & noexcept>();
    test_is_not_trivial<int(int, ...) const volatile && noexcept>();

    test_is_trivial<void (*)()>();
    test_is_trivial<void (*)() noexcept>();

    test_is_trivial<void (*)(int)>();
    test_is_trivial<void (*)(int) noexcept>();

    test_is_trivial<void (*)(...)>();
    test_is_trivial<void (*)(...) noexcept>();

    test_is_trivial<void (*)(int, ...)>();
    test_is_trivial<void (*)(int, ...) noexcept>();

    test_is_trivial<int (*)()>();
    test_is_trivial<int (*)() noexcept>();

    test_is_trivial<int (*)(int)>();
    test_is_trivial<int (*)(int) noexcept>();

    test_is_trivial<int (*)(...)>();
    test_is_trivial<int (*)(...) noexcept>();

    test_is_trivial<int (*)(int, ...)>();
    test_is_trivial<int (*)(int, ...) noexcept>();

    test_is_not_trivial<void (&)()>();
    test_is_not_trivial<void (&)() noexcept>();

    test_is_not_trivial<void (&)(int)>();
    test_is_not_trivial<void (&)(int) noexcept>();

    test_is_not_trivial<void (&)(...)>();
    test_is_not_trivial<void (&)(...) noexcept>();

    test_is_not_trivial<void (&)(int, ...)>();
    test_is_not_trivial<void (&)(int, ...) noexcept>();

    test_is_not_trivial<int (&)()>();
    test_is_not_trivial<int (&)() noexcept>();

    test_is_not_trivial<int (&)(int)>();
    test_is_not_trivial<int (&)(int) noexcept>();

    test_is_not_trivial<int (&)(...)>();
    test_is_not_trivial<int (&)(...) noexcept>();

    test_is_not_trivial<int (&)(int, ...)>();
    test_is_not_trivial<int (&)(int, ...) noexcept>();

    test_is_not_trivial<void (&&)()>();
    test_is_not_trivial<void (&&)() noexcept>();

    test_is_not_trivial<void (&&)(int)>();
    test_is_not_trivial<void (&&)(int) noexcept>();

    test_is_not_trivial<void (&&)(...)>();
    test_is_not_trivial<void (&&)(...) noexcept>();

    test_is_not_trivial<void (&&)(int, ...)>();
    test_is_not_trivial<void (&&)(int, ...) noexcept>();

    test_is_not_trivial<int (&&)()>();
    test_is_not_trivial<int (&&)() noexcept>();

    test_is_not_trivial<int (&&)(int)>();
    test_is_not_trivial<int (&&)(int) noexcept>();

    test_is_not_trivial<int (&&)(...)>();
    test_is_not_trivial<int (&&)(...) noexcept>();

    test_is_not_trivial<int (&&)(int, ...)>();
    test_is_not_trivial<int (&&)(int, ...) noexcept>();

    test_is_trivial<void (class_type::*)()>();
    test_is_trivial<void (class_type::*)()&>();
    test_is_trivial<void (class_type::*)() &&>();
    test_is_trivial<void (class_type::*)() const>();
    test_is_trivial<void (class_type::*)() const&>();
    test_is_trivial<void (class_type::*)() const&&>();
    test_is_trivial<void (class_type::*)() noexcept>();
    test_is_trivial<void (class_type::*)() & noexcept>();
    test_is_trivial<void (class_type::*)() && noexcept>();
    test_is_trivial<void (class_type::*)() const noexcept>();
    test_is_trivial<void (class_type::*)() const & noexcept>();
    test_is_trivial<void (class_type::*)() const && noexcept>();

    test_is_trivial<void (class_type::*)(int)>();
    test_is_trivial<void (class_type::*)(int)&>();
    test_is_trivial<void (class_type::*)(int) &&>();
    test_is_trivial<void (class_type::*)(int) const>();
    test_is_trivial<void (class_type::*)(int) const&>();
    test_is_trivial<void (class_type::*)(int) const&&>();
    test_is_trivial<void (class_type::*)(int) noexcept>();
    test_is_trivial<void (class_type::*)(int) & noexcept>();
    test_is_trivial<void (class_type::*)(int) && noexcept>();
    test_is_trivial<void (class_type::*)(int) const noexcept>();
    test_is_trivial<void (class_type::*)(int) const & noexcept>();
    test_is_trivial<void (class_type::*)(int) const && noexcept>();

    test_is_trivial<void (class_type::*)(...)>();
    test_is_trivial<void (class_type::*)(...)&>();
    test_is_trivial<void (class_type::*)(...) &&>();
    test_is_trivial<void (class_type::*)(...) const>();
    test_is_trivial<void (class_type::*)(...) const&>();
    test_is_trivial<void (class_type::*)(...) const&&>();
    test_is_trivial<void (class_type::*)(...) noexcept>();
    test_is_trivial<void (class_type::*)(...) & noexcept>();
    test_is_trivial<void (class_type::*)(...) && noexcept>();
    test_is_trivial<void (class_type::*)(...) const noexcept>();
    test_is_trivial<void (class_type::*)(...) const & noexcept>();
    test_is_trivial<void (class_type::*)(...) const && noexcept>();

    test_is_trivial<void (class_type::*)(int, ...)>();
    test_is_trivial<void (class_type::*)(int, ...)&>();
    test_is_trivial<void (class_type::*)(int, ...) &&>();
    test_is_trivial<void (class_type::*)(int, ...) const>();
    test_is_trivial<void (class_type::*)(int, ...) const&>();
    test_is_trivial<void (class_type::*)(int, ...) const&&>();
    test_is_trivial<void (class_type::*)(int, ...) noexcept>();
    test_is_trivial<void (class_type::*)(int, ...) & noexcept>();
    test_is_trivial<void (class_type::*)(int, ...) && noexcept>();
    test_is_trivial<void (class_type::*)(int, ...) const noexcept>();
    test_is_trivial<void (class_type::*)(int, ...) const & noexcept>();
    test_is_trivial<void (class_type::*)(int, ...) const && noexcept>();

    test_is_trivial<int (class_type::*)()>();
    test_is_trivial<int (class_type::*)()&>();
    test_is_trivial<int (class_type::*)() &&>();
    test_is_trivial<int (class_type::*)() const>();
    test_is_trivial<int (class_type::*)() const&>();
    test_is_trivial<int (class_type::*)() const&&>();
    test_is_trivial<int (class_type::*)() noexcept>();
    test_is_trivial<int (class_type::*)() & noexcept>();
    test_is_trivial<int (class_type::*)() && noexcept>();
    test_is_trivial<int (class_type::*)() const noexcept>();
    test_is_trivial<int (class_type::*)() const & noexcept>();
    test_is_trivial<int (class_type::*)() const && noexcept>();

    test_is_trivial<int (class_type::*)(int)>();
    test_is_trivial<int (class_type::*)(int)&>();
    test_is_trivial<int (class_type::*)(int) &&>();
    test_is_trivial<int (class_type::*)(int) const>();
    test_is_trivial<int (class_type::*)(int) const&>();
    test_is_trivial<int (class_type::*)(int) const&&>();
    test_is_trivial<int (class_type::*)(int) noexcept>();
    test_is_trivial<int (class_type::*)(int) & noexcept>();
    test_is_trivial<int (class_type::*)(int) && noexcept>();
    test_is_trivial<int (class_type::*)(int) const noexcept>();
    test_is_trivial<int (class_type::*)(int) const & noexcept>();
    test_is_trivial<int (class_type::*)(int) const && noexcept>();

    test_is_trivial<int (class_type::*)(...)>();
    test_is_trivial<int (class_type::*)(...)&>();
    test_is_trivial<int (class_type::*)(...) &&>();
    test_is_trivial<int (class_type::*)(...) const>();
    test_is_trivial<int (class_type::*)(...) const&>();
    test_is_trivial<int (class_type::*)(...) const&&>();
    test_is_trivial<int (class_type::*)(...) noexcept>();
    test_is_trivial<int (class_type::*)(...) & noexcept>();
    test_is_trivial<int (class_type::*)(...) && noexcept>();
    test_is_trivial<int (class_type::*)(...) const noexcept>();
    test_is_trivial<int (class_type::*)(...) const & noexcept>();
    test_is_trivial<int (class_type::*)(...) const && noexcept>();

    test_is_trivial<int (class_type::*)(int, ...)>();
    test_is_trivial<int (class_type::*)(int, ...)&>();
    test_is_trivial<int (class_type::*)(int, ...) &&>();
    test_is_trivial<int (class_type::*)(int, ...) const>();
    test_is_trivial<int (class_type::*)(int, ...) const&>();
    test_is_trivial<int (class_type::*)(int, ...) const&&>();
    test_is_trivial<int (class_type::*)(int, ...) noexcept>();
    test_is_trivial<int (class_type::*)(int, ...) & noexcept>();
    test_is_trivial<int (class_type::*)(int, ...) && noexcept>();
    test_is_trivial<int (class_type::*)(int, ...) const noexcept>();
    test_is_trivial<int (class_type::*)(int, ...) const & noexcept>();
    test_is_trivial<int (class_type::*)(int, ...) const && noexcept>();
}
