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
#include <phi/type_traits/is_aggregate.hpp>
#include <type_traits>
#include <vector>

// TODO: No idea why gcc thinks some types here are aggregate although they aren't

template <typename TypeT>
void test_is_aggregate_impl()
{
#if PHI_HAS_WORKING_IS_AGGREGATE()
    STATIC_REQUIRE(phi::is_aggregate<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_aggregate<TypeT>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_aggregate_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_not_aggregate_v<TypeT>);
#    endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_aggregate<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_aggregate<TypeT>);

    // standard compatbility
#    if PHI_CPP_STANDARD_IS_ATLEAST(17)
    STATIC_REQUIRE(std::is_aggregate<TypeT>::value);
#    endif
#endif
}

template <typename TypeT>
void test_is_aggregate()
{
    test_is_aggregate_impl<TypeT>();
    test_is_aggregate_impl<const TypeT>();
    test_is_aggregate_impl<volatile TypeT>();
    test_is_aggregate_impl<const volatile TypeT>();
}

template <typename TypeT>
void test_is_not_aggregate_impl()
{
#if PHI_HAS_WORKING_IS_AGGREGATE()
    STATIC_REQUIRE_FALSE(phi::is_aggregate<TypeT>::value);
    STATIC_REQUIRE(phi::is_not_aggregate<TypeT>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_aggregate_v<TypeT>);
    STATIC_REQUIRE(phi::is_not_aggregate_v<TypeT>);
#    endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_aggregate<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_aggregate<TypeT>);

    // standard compatbility
#    if PHI_CPP_STANDARD_IS_ATLEAST(17)
    STATIC_REQUIRE_FALSE(std::is_aggregate<TypeT>::value);
#    endif
#endif
}

template <typename TypeT>
void test_is_not_aggregate()
{
    test_is_not_aggregate_impl<TypeT>();
    test_is_not_aggregate_impl<const TypeT>();
    test_is_not_aggregate_impl<volatile TypeT>();
    test_is_not_aggregate_impl<const volatile TypeT>();
}

struct Aggregate
{};

struct HasCons
{
    HasCons(int);
};

struct PublicMembers
{
    int    x;
    double y;
};

struct HasPriv
{
    void PreventUnusedPrivateMemberWarning();

private:
    int m_X;
};

TEST_CASE("is_aggregate")
{
    test_is_aggregate<Aggregate>();
    test_is_aggregate<Aggregate[]>();
    test_is_aggregate<Aggregate[2]>();
    test_is_aggregate<Aggregate[42][101]>();
    test_is_aggregate<PublicMembers>();

    test_is_not_aggregate<void (Aggregate::*)(int) const>();
    test_is_not_aggregate<Aggregate&>();
    test_is_not_aggregate<HasCons>();
    test_is_not_aggregate<HasPriv>();

    test_is_not_aggregate<void>();
    test_is_not_aggregate<phi::nullptr_t>();
    test_is_not_aggregate<bool>();
    test_is_not_aggregate<char>();
    test_is_not_aggregate<signed char>();
    test_is_not_aggregate<unsigned char>();
    test_is_not_aggregate<short>();
    test_is_not_aggregate<unsigned short>();
    test_is_not_aggregate<int>();
    test_is_not_aggregate<unsigned int>();
    test_is_not_aggregate<long>();
    test_is_not_aggregate<unsigned long>();
    test_is_not_aggregate<long long>();
    test_is_not_aggregate<unsigned long long>();
    test_is_not_aggregate<float>();
    test_is_not_aggregate<double>();
    test_is_not_aggregate<long double>();
    test_is_not_aggregate<char8_t>();
    test_is_not_aggregate<char16_t>();
    test_is_not_aggregate<char32_t>();
    test_is_not_aggregate<wchar_t>();

    test_is_not_aggregate<phi::boolean>();
    test_is_not_aggregate<phi::integer<signed char>>();
    test_is_not_aggregate<phi::integer<unsigned char>>();
    test_is_not_aggregate<phi::integer<short>>();
    test_is_not_aggregate<phi::integer<unsigned short>>();
    test_is_not_aggregate<phi::integer<int>>();
    test_is_not_aggregate<phi::integer<unsigned int>>();
    test_is_not_aggregate<phi::integer<long>>();
    test_is_not_aggregate<phi::integer<unsigned long>>();
    test_is_not_aggregate<phi::integer<long long>>();
    test_is_not_aggregate<phi::integer<unsigned long long>>();
    test_is_not_aggregate<phi::floating_point<float>>();
    test_is_not_aggregate<phi::floating_point<double>>();
    test_is_not_aggregate<phi::floating_point<long double>>();

    test_is_not_aggregate<std::vector<int>>();
    test_is_not_aggregate<phi::scope_ptr<int>>();

    test_is_not_aggregate<int&>();
    test_is_not_aggregate<const int&>();
    test_is_not_aggregate<volatile int&>();
    test_is_not_aggregate<const volatile int&>();
    test_is_not_aggregate<int&&>();
    test_is_not_aggregate<const int&&>();
    test_is_not_aggregate<volatile int&&>();
    test_is_not_aggregate<const volatile int&&>();
    test_is_not_aggregate<int*>();
    test_is_not_aggregate<const int*>();
    test_is_not_aggregate<volatile int*>();
    test_is_not_aggregate<const volatile int*>();
    test_is_not_aggregate<int**>();
    test_is_not_aggregate<const int**>();
    test_is_not_aggregate<volatile int**>();
    test_is_not_aggregate<const volatile int**>();
    test_is_not_aggregate<int*&>();
    test_is_not_aggregate<const int*&>();
    test_is_not_aggregate<volatile int*&>();
    test_is_not_aggregate<const volatile int*&>();
    test_is_not_aggregate<int*&&>();
    test_is_not_aggregate<const int*&&>();
    test_is_not_aggregate<volatile int*&&>();
    test_is_not_aggregate<const volatile int*&&>();
    test_is_not_aggregate<void*>();
    test_is_aggregate<char[3]>();
    test_is_aggregate<char[]>();
    test_is_aggregate<char[3]>();
    test_is_aggregate<char[]>();
    test_is_aggregate<char* [3]>();
    test_is_aggregate<char*[]>();
    test_is_not_aggregate<int(*)[3]>();
    test_is_not_aggregate<int(*)[]>();
    test_is_not_aggregate<int(&)[3]>();
    test_is_not_aggregate<int(&)[]>();
    test_is_not_aggregate<int(&&)[3]>();
    test_is_not_aggregate<int(&&)[]>();
    test_is_aggregate<char[3][2]>();
    test_is_aggregate<char[][2]>();
    test_is_aggregate<char* [3][2]>();
    test_is_aggregate<char*[][2]>();
    test_is_not_aggregate<int(*)[3][2]>();
    test_is_not_aggregate<int(*)[][2]>();
    test_is_not_aggregate<int(&)[3][2]>();
    test_is_not_aggregate<int(&)[][2]>();
    test_is_not_aggregate<int(&&)[3][2]>();
    test_is_not_aggregate<int(&&)[][2]>();
    test_is_aggregate<class_type>();
    test_is_aggregate<class_type[]>();
    test_is_aggregate<class_type[2]>();
    test_is_aggregate<template_type<void>>();
    test_is_aggregate<template_type<int>>();
    test_is_aggregate<template_type<class_type>>();
    test_is_aggregate<template_type<incomplete_type>>();
    test_is_aggregate<variadic_template<>>();
    test_is_aggregate<variadic_template<void>>();
    test_is_aggregate<variadic_template<int>>();
    test_is_aggregate<variadic_template<class_type>>();
    test_is_aggregate<variadic_template<incomplete_type>>();
    test_is_aggregate<variadic_template<int, void, class_type, volatile char[]>>();
#if PHI_CPP_STANDARD_IS_ATLEAST(17)
    test_is_aggregate<public_derived_from<base>>();
    test_is_aggregate<public_derived_from<derived>>();
    test_is_aggregate<public_derived_from<class_type>>();
#else
    test_is_not_aggregate<public_derived_from<base>>();
    test_is_not_aggregate<public_derived_from<derived>>();
    test_is_not_aggregate<public_derived_from<class_type>>();
#endif
    test_is_not_aggregate<private_derived_from<base>>();
    test_is_not_aggregate<private_derived_from<derived>>();
    test_is_not_aggregate<private_derived_from<class_type>>();
    test_is_not_aggregate<protected_derived_from<base>>();
    test_is_not_aggregate<protected_derived_from<derived>>();
    test_is_not_aggregate<protected_derived_from<class_type>>();
    test_is_aggregate<union_type>();
    test_is_aggregate<non_empty_union>();
    test_is_aggregate<empty>();
    test_is_not_aggregate<not_empty>();
    test_is_aggregate<bit_zero>();
    test_is_aggregate<bit_one>();
    test_is_aggregate<base>();
#if PHI_CPP_STANDARD_IS_ATLEAST(17)
    test_is_aggregate<derived>();
#else
    test_is_not_aggregate<derived>();
#endif
    test_is_not_aggregate<abstract>();
    test_is_not_aggregate<public_abstract>();
    test_is_not_aggregate<private_abstract>();
    test_is_not_aggregate<protected_abstract>();
    test_is_not_aggregate<abstract_template<int>>();
    test_is_aggregate<abstract_template<double>>();
    test_is_not_aggregate<abstract_template<class_type>>();
    test_is_not_aggregate<abstract_template<incomplete_type>>();
    test_is_aggregate<final_type>();
    test_is_aggregate<public_destructor>();
    test_is_aggregate<protected_destructor>();
    test_is_aggregate<private_destructor>();
    test_is_not_aggregate<virtual_public_destructor>();
    test_is_not_aggregate<virtual_protected_destructor>();
    test_is_not_aggregate<virtual_private_destructor>();
    test_is_not_aggregate<pure_public_destructor>();
    test_is_not_aggregate<pure_protected_destructor>();
    test_is_not_aggregate<pure_private_destructor>();
    test_is_aggregate<deleted_public_destructor>();
    test_is_aggregate<deleted_protected_destructor>();
    test_is_aggregate<deleted_private_destructor>();
    test_is_not_aggregate<deleted_virtual_public_destructor>();
    test_is_not_aggregate<deleted_virtual_protected_destructor>();
    test_is_not_aggregate<deleted_virtual_private_destructor>();
    test_is_not_aggregate<Enum>();
    test_is_not_aggregate<EnumSigned>();
    test_is_not_aggregate<EnumUnsigned>();
    test_is_not_aggregate<EnumClass>();
    test_is_not_aggregate<EnumStruct>();
    test_is_not_aggregate<function_type>();
    test_is_not_aggregate<function_ptr>();
    test_is_not_aggregate<member_object_ptr>();
    test_is_not_aggregate<member_function_ptr>();
    test_is_not_aggregate<int class_type::*>();
    test_is_not_aggregate<float class_type::*>();
    test_is_not_aggregate<void * class_type::*>();
    test_is_not_aggregate<int * class_type::*>();
    test_is_not_aggregate<int class_type::*&>();
    test_is_not_aggregate<float class_type::*&>();
    test_is_not_aggregate<void * class_type::*&>();
    test_is_not_aggregate<int * class_type::*&>();
    test_is_not_aggregate<int class_type::*&&>();
    test_is_not_aggregate<float class_type::*&&>();
    test_is_not_aggregate<void * class_type::*&&>();
    test_is_not_aggregate<int * class_type::*&&>();
    test_is_not_aggregate<int class_type::* const>();
    test_is_not_aggregate<float class_type::* const>();
    test_is_not_aggregate<void * class_type::* const>();
    test_is_not_aggregate<int class_type::* const&>();
    test_is_not_aggregate<float class_type::* const&>();
    test_is_not_aggregate<void * class_type::* const&>();
    test_is_not_aggregate<int class_type::* const&&>();
    test_is_not_aggregate<float class_type::* const&&>();
    test_is_not_aggregate<void * class_type::* const&&>();
    test_is_not_aggregate<int class_type::* volatile>();
    test_is_not_aggregate<float class_type::* volatile>();
    test_is_not_aggregate<void * class_type::* volatile>();
    test_is_not_aggregate<int class_type::* volatile&>();
    test_is_not_aggregate<float class_type::* volatile&>();
    test_is_not_aggregate<void * class_type::* volatile&>();
    test_is_not_aggregate<int class_type::* volatile&&>();
    test_is_not_aggregate<float class_type::* volatile&&>();
    test_is_not_aggregate<void * class_type::* volatile&&>();
    test_is_not_aggregate<int class_type::* const volatile>();
    test_is_not_aggregate<float class_type::* const volatile>();
    test_is_not_aggregate<void * class_type::* const volatile>();
    test_is_not_aggregate<int class_type::* const volatile&>();
    test_is_not_aggregate<float class_type::* const volatile&>();
    test_is_not_aggregate<void * class_type::* const volatile&>();
    test_is_not_aggregate<int class_type::* const volatile&&>();
    test_is_not_aggregate<float class_type::* const volatile&&>();
    test_is_not_aggregate<void * class_type::* const volatile&&>();
#if PHI_COMPILER_IS(EMCC)
    // TODO: Not sure why emscripten has such problems here :/
    SKIP_CHECK();
    SKIP_CHECK();
    SKIP_CHECK();
#elif PHI_COMPILER_IS_BELOW(GCC, 9, 0, 0) || PHI_CPP_STANDARD_IS_BELOW(20)
    test_is_aggregate<non_copyable>();
    test_is_aggregate<non_moveable>();
    test_is_aggregate<non_constructible>();
#else
    test_is_not_aggregate<non_copyable>();
    test_is_not_aggregate<non_moveable>();
    test_is_not_aggregate<non_constructible>();
#endif
    test_is_not_aggregate<tracked>();
    test_is_not_aggregate<trap_constructible>();
    test_is_aggregate<trap_implicit_conversion>();
    test_is_aggregate<trap_comma>();
    test_is_aggregate<trap_call>();
#if PHI_COMPILER_IS(EMCC)
    // TODO: Not sure why emscripten has such problems here
    SKIP_CHECK();
#elif PHI_COMPILER_IS_BELOW(GCC, 9, 0, 0) || PHI_CPP_STANDARD_IS_BELOW(20)
    test_is_aggregate<trap_self_assign>();
#else
    test_is_not_aggregate<trap_self_assign>();
#endif
    test_is_aggregate<trap_deref>();
    test_is_aggregate<trap_array_subscript>();

    test_is_not_aggregate<void()>();
    test_is_not_aggregate<void()&>();
    test_is_not_aggregate<void() &&>();
    test_is_not_aggregate<void() const>();
    test_is_not_aggregate<void() const&>();
    test_is_not_aggregate<void() const&&>();
    test_is_not_aggregate<void() volatile>();
    test_is_not_aggregate<void() volatile&>();
    test_is_not_aggregate<void() volatile&&>();
    test_is_not_aggregate<void() const volatile>();
    test_is_not_aggregate<void() const volatile&>();
    test_is_not_aggregate<void() const volatile&&>();
    test_is_not_aggregate<void() noexcept>();
    test_is_not_aggregate<void() & noexcept>();
    test_is_not_aggregate<void() && noexcept>();
    test_is_not_aggregate<void() const noexcept>();
    test_is_not_aggregate<void() const & noexcept>();
    test_is_not_aggregate<void() const && noexcept>();
    test_is_not_aggregate<void() volatile noexcept>();
    test_is_not_aggregate<void() volatile & noexcept>();
    test_is_not_aggregate<void() volatile && noexcept>();
    test_is_not_aggregate<void() const volatile noexcept>();
    test_is_not_aggregate<void() const volatile & noexcept>();
    test_is_not_aggregate<void() const volatile && noexcept>();

    test_is_not_aggregate<void(int)>();
    test_is_not_aggregate<void(int)&>();
    test_is_not_aggregate<void(int) &&>();
    test_is_not_aggregate<void(int) const>();
    test_is_not_aggregate<void(int) const&>();
    test_is_not_aggregate<void(int) const&&>();
    test_is_not_aggregate<void(int) volatile>();
    test_is_not_aggregate<void(int) volatile&>();
    test_is_not_aggregate<void(int) volatile&&>();
    test_is_not_aggregate<void(int) const volatile>();
    test_is_not_aggregate<void(int) const volatile&>();
    test_is_not_aggregate<void(int) const volatile&&>();
    test_is_not_aggregate<void(int) noexcept>();
    test_is_not_aggregate<void(int) & noexcept>();
    test_is_not_aggregate<void(int) && noexcept>();
    test_is_not_aggregate<void(int) const noexcept>();
    test_is_not_aggregate<void(int) const & noexcept>();
    test_is_not_aggregate<void(int) const && noexcept>();
    test_is_not_aggregate<void(int) volatile noexcept>();
    test_is_not_aggregate<void(int) volatile & noexcept>();
    test_is_not_aggregate<void(int) volatile && noexcept>();
    test_is_not_aggregate<void(int) const volatile noexcept>();
    test_is_not_aggregate<void(int) const volatile & noexcept>();
    test_is_not_aggregate<void(int) const volatile && noexcept>();

    test_is_not_aggregate<void(...)>();
    test_is_not_aggregate<void(...)&>();
    test_is_not_aggregate<void(...) &&>();
    test_is_not_aggregate<void(...) const>();
    test_is_not_aggregate<void(...) const&>();
    test_is_not_aggregate<void(...) const&&>();
    test_is_not_aggregate<void(...) volatile>();
    test_is_not_aggregate<void(...) volatile&>();
    test_is_not_aggregate<void(...) volatile&&>();
    test_is_not_aggregate<void(...) const volatile>();
    test_is_not_aggregate<void(...) const volatile&>();
    test_is_not_aggregate<void(...) const volatile&&>();
    test_is_not_aggregate<void(...) noexcept>();
    test_is_not_aggregate<void(...) & noexcept>();
    test_is_not_aggregate<void(...) && noexcept>();
    test_is_not_aggregate<void(...) const noexcept>();
    test_is_not_aggregate<void(...) const & noexcept>();
    test_is_not_aggregate<void(...) const && noexcept>();
    test_is_not_aggregate<void(...) volatile noexcept>();
    test_is_not_aggregate<void(...) volatile & noexcept>();
    test_is_not_aggregate<void(...) volatile && noexcept>();
    test_is_not_aggregate<void(...) const volatile noexcept>();
    test_is_not_aggregate<void(...) const volatile & noexcept>();
    test_is_not_aggregate<void(...) const volatile && noexcept>();

    test_is_not_aggregate<void(int, ...)>();
    test_is_not_aggregate<void(int, ...)&>();
    test_is_not_aggregate<void(int, ...) &&>();
    test_is_not_aggregate<void(int, ...) const>();
    test_is_not_aggregate<void(int, ...) const&>();
    test_is_not_aggregate<void(int, ...) const&&>();
    test_is_not_aggregate<void(int, ...) volatile>();
    test_is_not_aggregate<void(int, ...) volatile&>();
    test_is_not_aggregate<void(int, ...) volatile&&>();
    test_is_not_aggregate<void(int, ...) const volatile>();
    test_is_not_aggregate<void(int, ...) const volatile&>();
    test_is_not_aggregate<void(int, ...) const volatile&&>();
    test_is_not_aggregate<void(int, ...) noexcept>();
    test_is_not_aggregate<void(int, ...) & noexcept>();
    test_is_not_aggregate<void(int, ...) && noexcept>();
    test_is_not_aggregate<void(int, ...) const noexcept>();
    test_is_not_aggregate<void(int, ...) const & noexcept>();
    test_is_not_aggregate<void(int, ...) const && noexcept>();
    test_is_not_aggregate<void(int, ...) volatile noexcept>();
    test_is_not_aggregate<void(int, ...) volatile & noexcept>();
    test_is_not_aggregate<void(int, ...) volatile && noexcept>();
    test_is_not_aggregate<void(int, ...) const volatile noexcept>();
    test_is_not_aggregate<void(int, ...) const volatile & noexcept>();
    test_is_not_aggregate<void(int, ...) const volatile && noexcept>();

    test_is_not_aggregate<int()>();
    test_is_not_aggregate<int()&>();
    test_is_not_aggregate<int() &&>();
    test_is_not_aggregate<int() const>();
    test_is_not_aggregate<int() const&>();
    test_is_not_aggregate<int() const&&>();
    test_is_not_aggregate<int() volatile>();
    test_is_not_aggregate<int() volatile&>();
    test_is_not_aggregate<int() volatile&&>();
    test_is_not_aggregate<int() const volatile>();
    test_is_not_aggregate<int() const volatile&>();
    test_is_not_aggregate<int() const volatile&&>();
    test_is_not_aggregate<int() noexcept>();
    test_is_not_aggregate<int() & noexcept>();
    test_is_not_aggregate<int() && noexcept>();
    test_is_not_aggregate<int() const noexcept>();
    test_is_not_aggregate<int() const & noexcept>();
    test_is_not_aggregate<int() const && noexcept>();
    test_is_not_aggregate<int() volatile noexcept>();
    test_is_not_aggregate<int() volatile & noexcept>();
    test_is_not_aggregate<int() volatile && noexcept>();
    test_is_not_aggregate<int() const volatile noexcept>();
    test_is_not_aggregate<int() const volatile & noexcept>();
    test_is_not_aggregate<int() const volatile && noexcept>();

    test_is_not_aggregate<int(int)>();
    test_is_not_aggregate<int(int)&>();
    test_is_not_aggregate<int(int) &&>();
    test_is_not_aggregate<int(int) const>();
    test_is_not_aggregate<int(int) const&>();
    test_is_not_aggregate<int(int) const&&>();
    test_is_not_aggregate<int(int) volatile>();
    test_is_not_aggregate<int(int) volatile&>();
    test_is_not_aggregate<int(int) volatile&&>();
    test_is_not_aggregate<int(int) const volatile>();
    test_is_not_aggregate<int(int) const volatile&>();
    test_is_not_aggregate<int(int) const volatile&&>();
    test_is_not_aggregate<int(int) noexcept>();
    test_is_not_aggregate<int(int) & noexcept>();
    test_is_not_aggregate<int(int) && noexcept>();
    test_is_not_aggregate<int(int) const noexcept>();
    test_is_not_aggregate<int(int) const & noexcept>();
    test_is_not_aggregate<int(int) const && noexcept>();
    test_is_not_aggregate<int(int) volatile noexcept>();
    test_is_not_aggregate<int(int) volatile & noexcept>();
    test_is_not_aggregate<int(int) volatile && noexcept>();
    test_is_not_aggregate<int(int) const volatile noexcept>();
    test_is_not_aggregate<int(int) const volatile & noexcept>();
    test_is_not_aggregate<int(int) const volatile && noexcept>();

    test_is_not_aggregate<int(...)>();
    test_is_not_aggregate<int(...)&>();
    test_is_not_aggregate<int(...) &&>();
    test_is_not_aggregate<int(...) const>();
    test_is_not_aggregate<int(...) const&>();
    test_is_not_aggregate<int(...) const&&>();
    test_is_not_aggregate<int(...) volatile>();
    test_is_not_aggregate<int(...) volatile&>();
    test_is_not_aggregate<int(...) volatile&&>();
    test_is_not_aggregate<int(...) const volatile>();
    test_is_not_aggregate<int(...) const volatile&>();
    test_is_not_aggregate<int(...) const volatile&&>();
    test_is_not_aggregate<int(...) noexcept>();
    test_is_not_aggregate<int(...) & noexcept>();
    test_is_not_aggregate<int(...) && noexcept>();
    test_is_not_aggregate<int(...) const noexcept>();
    test_is_not_aggregate<int(...) const & noexcept>();
    test_is_not_aggregate<int(...) const && noexcept>();
    test_is_not_aggregate<int(...) volatile noexcept>();
    test_is_not_aggregate<int(...) volatile & noexcept>();
    test_is_not_aggregate<int(...) volatile && noexcept>();
    test_is_not_aggregate<int(...) const volatile noexcept>();
    test_is_not_aggregate<int(...) const volatile & noexcept>();
    test_is_not_aggregate<int(...) const volatile && noexcept>();

    test_is_not_aggregate<int(int, ...)>();
    test_is_not_aggregate<int(int, ...)&>();
    test_is_not_aggregate<int(int, ...) &&>();
    test_is_not_aggregate<int(int, ...) const>();
    test_is_not_aggregate<int(int, ...) const&>();
    test_is_not_aggregate<int(int, ...) const&&>();
    test_is_not_aggregate<int(int, ...) volatile>();
    test_is_not_aggregate<int(int, ...) volatile&>();
    test_is_not_aggregate<int(int, ...) volatile&&>();
    test_is_not_aggregate<int(int, ...) const volatile>();
    test_is_not_aggregate<int(int, ...) const volatile&>();
    test_is_not_aggregate<int(int, ...) const volatile&&>();
    test_is_not_aggregate<int(int, ...) noexcept>();
    test_is_not_aggregate<int(int, ...) & noexcept>();
    test_is_not_aggregate<int(int, ...) && noexcept>();
    test_is_not_aggregate<int(int, ...) const noexcept>();
    test_is_not_aggregate<int(int, ...) const & noexcept>();
    test_is_not_aggregate<int(int, ...) const && noexcept>();
    test_is_not_aggregate<int(int, ...) volatile noexcept>();
    test_is_not_aggregate<int(int, ...) volatile & noexcept>();
    test_is_not_aggregate<int(int, ...) volatile && noexcept>();
    test_is_not_aggregate<int(int, ...) const volatile noexcept>();
    test_is_not_aggregate<int(int, ...) const volatile & noexcept>();
    test_is_not_aggregate<int(int, ...) const volatile && noexcept>();

    test_is_not_aggregate<void (*)()>();
    test_is_not_aggregate<void (*)() noexcept>();

    test_is_not_aggregate<void (*)(int)>();
    test_is_not_aggregate<void (*)(int) noexcept>();

    test_is_not_aggregate<void (*)(...)>();
    test_is_not_aggregate<void (*)(...) noexcept>();

    test_is_not_aggregate<void (*)(int, ...)>();
    test_is_not_aggregate<void (*)(int, ...) noexcept>();

    test_is_not_aggregate<int (*)()>();
    test_is_not_aggregate<int (*)() noexcept>();

    test_is_not_aggregate<int (*)(int)>();
    test_is_not_aggregate<int (*)(int) noexcept>();

    test_is_not_aggregate<int (*)(...)>();
    test_is_not_aggregate<int (*)(...) noexcept>();

    test_is_not_aggregate<int (*)(int, ...)>();
    test_is_not_aggregate<int (*)(int, ...) noexcept>();

    test_is_not_aggregate<void (&)()>();
    test_is_not_aggregate<void (&)() noexcept>();

    test_is_not_aggregate<void (&)(int)>();
    test_is_not_aggregate<void (&)(int) noexcept>();

    test_is_not_aggregate<void (&)(...)>();
    test_is_not_aggregate<void (&)(...) noexcept>();

    test_is_not_aggregate<void (&)(int, ...)>();
    test_is_not_aggregate<void (&)(int, ...) noexcept>();

    test_is_not_aggregate<int (&)()>();
    test_is_not_aggregate<int (&)() noexcept>();

    test_is_not_aggregate<int (&)(int)>();
    test_is_not_aggregate<int (&)(int) noexcept>();

    test_is_not_aggregate<int (&)(...)>();
    test_is_not_aggregate<int (&)(...) noexcept>();

    test_is_not_aggregate<int (&)(int, ...)>();
    test_is_not_aggregate<int (&)(int, ...) noexcept>();

    test_is_not_aggregate<void (&&)()>();
    test_is_not_aggregate<void (&&)() noexcept>();

    test_is_not_aggregate<void (&&)(int)>();
    test_is_not_aggregate<void (&&)(int) noexcept>();

    test_is_not_aggregate<void (&&)(...)>();
    test_is_not_aggregate<void (&&)(...) noexcept>();

    test_is_not_aggregate<void (&&)(int, ...)>();
    test_is_not_aggregate<void (&&)(int, ...) noexcept>();

    test_is_not_aggregate<int (&&)()>();
    test_is_not_aggregate<int (&&)() noexcept>();

    test_is_not_aggregate<int (&&)(int)>();
    test_is_not_aggregate<int (&&)(int) noexcept>();

    test_is_not_aggregate<int (&&)(...)>();
    test_is_not_aggregate<int (&&)(...) noexcept>();

    test_is_not_aggregate<int (&&)(int, ...)>();
    test_is_not_aggregate<int (&&)(int, ...) noexcept>();

    test_is_not_aggregate<void (class_type::*)()>();
    test_is_not_aggregate<void (class_type::*)()&>();
    test_is_not_aggregate<void (class_type::*)() &&>();
    test_is_not_aggregate<void (class_type::*)() const>();
    test_is_not_aggregate<void (class_type::*)() const&>();
    test_is_not_aggregate<void (class_type::*)() const&&>();
    test_is_not_aggregate<void (class_type::*)() noexcept>();
    test_is_not_aggregate<void (class_type::*)() & noexcept>();
    test_is_not_aggregate<void (class_type::*)() && noexcept>();
    test_is_not_aggregate<void (class_type::*)() const noexcept>();
    test_is_not_aggregate<void (class_type::*)() const & noexcept>();
    test_is_not_aggregate<void (class_type::*)() const && noexcept>();

    test_is_not_aggregate<void (class_type::*)(int)>();
    test_is_not_aggregate<void (class_type::*)(int)&>();
    test_is_not_aggregate<void (class_type::*)(int) &&>();
    test_is_not_aggregate<void (class_type::*)(int) const>();
    test_is_not_aggregate<void (class_type::*)(int) const&>();
    test_is_not_aggregate<void (class_type::*)(int) const&&>();
    test_is_not_aggregate<void (class_type::*)(int) noexcept>();
    test_is_not_aggregate<void (class_type::*)(int) & noexcept>();
    test_is_not_aggregate<void (class_type::*)(int) && noexcept>();
    test_is_not_aggregate<void (class_type::*)(int) const noexcept>();
    test_is_not_aggregate<void (class_type::*)(int) const & noexcept>();
    test_is_not_aggregate<void (class_type::*)(int) const && noexcept>();

    test_is_not_aggregate<void (class_type::*)(...)>();
    test_is_not_aggregate<void (class_type::*)(...)&>();
    test_is_not_aggregate<void (class_type::*)(...) &&>();
    test_is_not_aggregate<void (class_type::*)(...) const>();
    test_is_not_aggregate<void (class_type::*)(...) const&>();
    test_is_not_aggregate<void (class_type::*)(...) const&&>();
    test_is_not_aggregate<void (class_type::*)(...) noexcept>();
    test_is_not_aggregate<void (class_type::*)(...) & noexcept>();
    test_is_not_aggregate<void (class_type::*)(...) && noexcept>();
    test_is_not_aggregate<void (class_type::*)(...) const noexcept>();
    test_is_not_aggregate<void (class_type::*)(...) const & noexcept>();
    test_is_not_aggregate<void (class_type::*)(...) const && noexcept>();

    test_is_not_aggregate<void (class_type::*)(int, ...)>();
    test_is_not_aggregate<void (class_type::*)(int, ...)&>();
    test_is_not_aggregate<void (class_type::*)(int, ...) &&>();
    test_is_not_aggregate<void (class_type::*)(int, ...) const>();
    test_is_not_aggregate<void (class_type::*)(int, ...) const&>();
    test_is_not_aggregate<void (class_type::*)(int, ...) const&&>();
    test_is_not_aggregate<void (class_type::*)(int, ...) noexcept>();
    test_is_not_aggregate<void (class_type::*)(int, ...) & noexcept>();
    test_is_not_aggregate<void (class_type::*)(int, ...) && noexcept>();
    test_is_not_aggregate<void (class_type::*)(int, ...) const noexcept>();
    test_is_not_aggregate<void (class_type::*)(int, ...) const & noexcept>();
    test_is_not_aggregate<void (class_type::*)(int, ...) const && noexcept>();

    test_is_not_aggregate<int (class_type::*)()>();
    test_is_not_aggregate<int (class_type::*)()&>();
    test_is_not_aggregate<int (class_type::*)() &&>();
    test_is_not_aggregate<int (class_type::*)() const>();
    test_is_not_aggregate<int (class_type::*)() const&>();
    test_is_not_aggregate<int (class_type::*)() const&&>();
    test_is_not_aggregate<int (class_type::*)() noexcept>();
    test_is_not_aggregate<int (class_type::*)() & noexcept>();
    test_is_not_aggregate<int (class_type::*)() && noexcept>();
    test_is_not_aggregate<int (class_type::*)() const noexcept>();
    test_is_not_aggregate<int (class_type::*)() const & noexcept>();
    test_is_not_aggregate<int (class_type::*)() const && noexcept>();

    test_is_not_aggregate<int (class_type::*)(int)>();
    test_is_not_aggregate<int (class_type::*)(int)&>();
    test_is_not_aggregate<int (class_type::*)(int) &&>();
    test_is_not_aggregate<int (class_type::*)(int) const>();
    test_is_not_aggregate<int (class_type::*)(int) const&>();
    test_is_not_aggregate<int (class_type::*)(int) const&&>();
    test_is_not_aggregate<int (class_type::*)(int) noexcept>();
    test_is_not_aggregate<int (class_type::*)(int) & noexcept>();
    test_is_not_aggregate<int (class_type::*)(int) && noexcept>();
    test_is_not_aggregate<int (class_type::*)(int) const noexcept>();
    test_is_not_aggregate<int (class_type::*)(int) const & noexcept>();
    test_is_not_aggregate<int (class_type::*)(int) const && noexcept>();

    test_is_not_aggregate<int (class_type::*)(...)>();
    test_is_not_aggregate<int (class_type::*)(...)&>();
    test_is_not_aggregate<int (class_type::*)(...) &&>();
    test_is_not_aggregate<int (class_type::*)(...) const>();
    test_is_not_aggregate<int (class_type::*)(...) const&>();
    test_is_not_aggregate<int (class_type::*)(...) const&&>();
    test_is_not_aggregate<int (class_type::*)(...) noexcept>();
    test_is_not_aggregate<int (class_type::*)(...) & noexcept>();
    test_is_not_aggregate<int (class_type::*)(...) && noexcept>();
    test_is_not_aggregate<int (class_type::*)(...) const noexcept>();
    test_is_not_aggregate<int (class_type::*)(...) const & noexcept>();
    test_is_not_aggregate<int (class_type::*)(...) const && noexcept>();

    test_is_not_aggregate<int (class_type::*)(int, ...)>();
    test_is_not_aggregate<int (class_type::*)(int, ...)&>();
    test_is_not_aggregate<int (class_type::*)(int, ...) &&>();
    test_is_not_aggregate<int (class_type::*)(int, ...) const>();
    test_is_not_aggregate<int (class_type::*)(int, ...) const&>();
    test_is_not_aggregate<int (class_type::*)(int, ...) const&&>();
    test_is_not_aggregate<int (class_type::*)(int, ...) noexcept>();
    test_is_not_aggregate<int (class_type::*)(int, ...) & noexcept>();
    test_is_not_aggregate<int (class_type::*)(int, ...) && noexcept>();
    test_is_not_aggregate<int (class_type::*)(int, ...) const noexcept>();
    test_is_not_aggregate<int (class_type::*)(int, ...) const & noexcept>();
    test_is_not_aggregate<int (class_type::*)(int, ...) const && noexcept>();
}
