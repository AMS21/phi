#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_empty.hpp>
#include <type_traits>
#include <vector>

template <typename TypeT>
void test_is_empty_impl()
{
#if PHI_HAS_WORKING_IS_EMPTY()
    STATIC_REQUIRE(phi::is_empty<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_empty<TypeT>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_empty_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_not_empty_v<TypeT>);
#    endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_empty<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_empty<TypeT>);

    // Standard compatibility
    STATIC_REQUIRE(std::is_empty<TypeT>::value);
#endif
}

template <typename TypeT>
void test_is_empty()
{
    test_is_empty_impl<TypeT>();
    test_is_empty_impl<const TypeT>();
    test_is_empty_impl<volatile TypeT>();
    test_is_empty_impl<const volatile TypeT>();
}

template <typename TypeT>
void test_is_not_empty_impl()
{
#if PHI_HAS_WORKING_IS_EMPTY()
    STATIC_REQUIRE_FALSE(phi::is_empty<TypeT>::value);
    STATIC_REQUIRE(phi::is_not_empty<TypeT>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_empty_v<TypeT>);
    STATIC_REQUIRE(phi::is_not_empty_v<TypeT>);
#    endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_empty<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_empty<TypeT>);

    // Standard compatibility
    STATIC_REQUIRE_FALSE(std::is_empty<TypeT>::value);
#endif
}

template <typename TypeT>
void test_is_not_empty()
{
    test_is_not_empty_impl<TypeT>();
    test_is_not_empty_impl<const TypeT>();
    test_is_not_empty_impl<volatile TypeT>();
    test_is_not_empty_impl<const volatile TypeT>();
}

// NOLINTNEXTLINE(cppcoreguidelines-virtual-class-destructor)
class virtual_fn
{
    // NOLINTNEXTLINE(modernize-use-equals-delete)
    virtual ~virtual_fn();
};

struct StaticMember
{
    // NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
    static int foo;
};

struct NonStaticMember
{
    int foo;
};

TEST_CASE("is_empty")
{
    test_is_not_empty<virtual_fn>();
    test_is_not_empty<virtual_base>();
    test_is_not_empty<non_empty_base>();
    test_is_not_empty<NonStaticMember>();
    test_is_empty<empty_base>();
    test_is_empty<StaticMember>();

    test_is_not_empty<void>();
    test_is_not_empty<phi::nullptr_t>();
    test_is_not_empty<bool>();
    test_is_not_empty<char>();
    test_is_not_empty<signed char>();
    test_is_not_empty<unsigned char>();
    test_is_not_empty<short>();
    test_is_not_empty<unsigned short>();
    test_is_not_empty<int>();
    test_is_not_empty<unsigned int>();
    test_is_not_empty<long>();
    test_is_not_empty<unsigned long>();
    test_is_not_empty<long long>();
    test_is_not_empty<unsigned long long>();
    test_is_not_empty<float>();
    test_is_not_empty<double>();
    test_is_not_empty<long double>();
    test_is_not_empty<char8_t>();
    test_is_not_empty<char16_t>();
    test_is_not_empty<char32_t>();
    test_is_not_empty<wchar_t>();

    test_is_not_empty<phi::boolean>();
    test_is_not_empty<phi::integer<signed char>>();
    test_is_not_empty<phi::integer<unsigned char>>();
    test_is_not_empty<phi::integer<short>>();
    test_is_not_empty<phi::integer<unsigned short>>();
    test_is_not_empty<phi::integer<int>>();
    test_is_not_empty<phi::integer<unsigned int>>();
    test_is_not_empty<phi::integer<long>>();
    test_is_not_empty<phi::integer<unsigned long>>();
    test_is_not_empty<phi::integer<long long>>();
    test_is_not_empty<phi::integer<unsigned long long>>();
    test_is_not_empty<phi::floating_point<float>>();
    test_is_not_empty<phi::floating_point<double>>();
    test_is_not_empty<phi::floating_point<long double>>();

    test_is_not_empty<std::vector<int>>();
    test_is_not_empty<phi::scope_ptr<int>>();

    test_is_not_empty<int&>();
    test_is_not_empty<const int&>();
    test_is_not_empty<volatile int&>();
    test_is_not_empty<const volatile int&>();
    test_is_not_empty<int&&>();
    test_is_not_empty<const int&&>();
    test_is_not_empty<volatile int&&>();
    test_is_not_empty<const volatile int&&>();
    test_is_not_empty<int*>();
    test_is_not_empty<const int*>();
    test_is_not_empty<volatile int*>();
    test_is_not_empty<const volatile int*>();
    test_is_not_empty<int**>();
    test_is_not_empty<const int**>();
    test_is_not_empty<volatile int**>();
    test_is_not_empty<const volatile int**>();
    test_is_not_empty<int*&>();
    test_is_not_empty<const int*&>();
    test_is_not_empty<volatile int*&>();
    test_is_not_empty<const volatile int*&>();
    test_is_not_empty<int*&&>();
    test_is_not_empty<const int*&&>();
    test_is_not_empty<volatile int*&&>();
    test_is_not_empty<const volatile int*&&>();
    test_is_not_empty<void*>();
    test_is_not_empty<char[3]>();
    test_is_not_empty<char[]>();
    test_is_not_empty<char* [3]>();
    test_is_not_empty<char*[]>();
    test_is_not_empty<int(*)[3]>();
    test_is_not_empty<int(*)[]>();
    test_is_not_empty<int(&)[3]>();
    test_is_not_empty<int(&)[]>();
    test_is_not_empty<int(&&)[3]>();
    test_is_not_empty<int(&&)[]>();
    test_is_not_empty<char[3][2]>();
    test_is_not_empty<char[][2]>();
    test_is_not_empty<char* [3][2]>();
    test_is_not_empty<char*[][2]>();
    test_is_not_empty<int(*)[3][2]>();
    test_is_not_empty<int(*)[][2]>();
    test_is_not_empty<int(&)[3][2]>();
    test_is_not_empty<int(&)[][2]>();
    test_is_not_empty<int(&&)[3][2]>();
    test_is_not_empty<int(&&)[][2]>();
    test_is_empty<class_type>();
    test_is_not_empty<class_type[]>();
    test_is_not_empty<class_type[2]>();
    test_is_empty<template_type<void>>();
    test_is_empty<template_type<int>>();
    test_is_empty<template_type<class_type>>();
    test_is_empty<template_type<incomplete_type>>();
    test_is_empty<variadic_template<>>();
    test_is_empty<variadic_template<void>>();
    test_is_empty<variadic_template<int>>();
    test_is_empty<variadic_template<class_type>>();
    test_is_empty<variadic_template<incomplete_type>>();
    test_is_empty<variadic_template<int, void, class_type, volatile char[]>>();
    test_is_empty<public_derived_from<base>>();
    test_is_empty<public_derived_from<derived>>();
    test_is_empty<public_derived_from<class_type>>();
    test_is_empty<private_derived_from<base>>();
    test_is_empty<private_derived_from<derived>>();
    test_is_empty<private_derived_from<class_type>>();
    test_is_empty<protected_derived_from<base>>();
    test_is_empty<protected_derived_from<derived>>();
    test_is_empty<protected_derived_from<class_type>>();
    test_is_not_empty<union_type>();
    test_is_not_empty<non_empty_union>();
    test_is_empty<empty>();
    test_is_not_empty<not_empty>();
    test_is_empty<bit_zero>();
    // TODO: Why on earth do emcc and AppleClang think bit_one is empty?
#if PHI_COMPILER_IS(EMCC) || PHI_COMPILER_IS(APPLECLANG)
    SKIP_CHECK();
#else
    test_is_not_empty<bit_one>();
#endif
    test_is_empty<base>();
    test_is_empty<derived>();
    test_is_not_empty<abstract>();
    test_is_not_empty<public_abstract>();
    test_is_not_empty<private_abstract>();
    test_is_not_empty<protected_abstract>();
    test_is_not_empty<abstract_template<int>>();
    test_is_empty<abstract_template<double>>();
    test_is_not_empty<abstract_template<class_type>>();
    test_is_not_empty<abstract_template<incomplete_type>>();
    // final_type can only be tests with the intrinsic version
#if PHI_SUPPORTS_IS_EMPTY()
    test_is_empty<final_type>();
#endif
    test_is_empty<public_destructor>();
    test_is_empty<protected_destructor>();
    test_is_empty<private_destructor>();
    test_is_not_empty<virtual_public_destructor>();
    test_is_not_empty<virtual_protected_destructor>();
    test_is_not_empty<virtual_private_destructor>();
    test_is_not_empty<pure_public_destructor>();
    test_is_not_empty<pure_protected_destructor>();
    test_is_not_empty<pure_private_destructor>();
    test_is_empty<deleted_public_destructor>();
    test_is_empty<deleted_protected_destructor>();
    test_is_empty<deleted_private_destructor>();
    test_is_not_empty<deleted_virtual_public_destructor>();
    test_is_not_empty<deleted_virtual_protected_destructor>();
    test_is_not_empty<deleted_virtual_private_destructor>();
    test_is_not_empty<Enum>();
    test_is_not_empty<EnumSigned>();
    test_is_not_empty<EnumUnsigned>();
    test_is_not_empty<EnumClass>();
    test_is_not_empty<EnumStruct>();
    test_is_not_empty<function_type>();
    test_is_not_empty<function_ptr>();
    test_is_not_empty<member_object_ptr>();
    test_is_not_empty<member_function_ptr>();
    test_is_not_empty<int class_type::*>();
    test_is_not_empty<float class_type::*>();
    test_is_not_empty<void * class_type::*>();
    test_is_not_empty<int * class_type::*>();
    test_is_not_empty<int class_type::*&>();
    test_is_not_empty<float class_type::*&>();
    test_is_not_empty<void * class_type::*&>();
    test_is_not_empty<int * class_type::*&>();
    test_is_not_empty<int class_type::*&&>();
    test_is_not_empty<float class_type::*&&>();
    test_is_not_empty<void * class_type::*&&>();
    test_is_not_empty<int * class_type::*&&>();
    test_is_not_empty<int class_type::* const>();
    test_is_not_empty<float class_type::* const>();
    test_is_not_empty<void * class_type::* const>();
    test_is_not_empty<int class_type::* const&>();
    test_is_not_empty<float class_type::* const&>();
    test_is_not_empty<void * class_type::* const&>();
    test_is_not_empty<int class_type::* const&&>();
    test_is_not_empty<float class_type::* const&&>();
    test_is_not_empty<void * class_type::* const&&>();
    test_is_not_empty<int class_type::* volatile>();
    test_is_not_empty<float class_type::* volatile>();
    test_is_not_empty<void * class_type::* volatile>();
    test_is_not_empty<int class_type::* volatile&>();
    test_is_not_empty<float class_type::* volatile&>();
    test_is_not_empty<void * class_type::* volatile&>();
    test_is_not_empty<int class_type::* volatile&&>();
    test_is_not_empty<float class_type::* volatile&&>();
    test_is_not_empty<void * class_type::* volatile&&>();
    test_is_not_empty<int class_type::* const volatile>();
    test_is_not_empty<float class_type::* const volatile>();
    test_is_not_empty<void * class_type::* const volatile>();
    test_is_not_empty<int class_type::* const volatile&>();
    test_is_not_empty<float class_type::* const volatile&>();
    test_is_not_empty<void * class_type::* const volatile&>();
    test_is_not_empty<int class_type::* const volatile&&>();
    test_is_not_empty<float class_type::* const volatile&&>();
    test_is_not_empty<void * class_type::* const volatile&&>();
    test_is_empty<non_copyable>();
    test_is_empty<non_moveable>();
    test_is_empty<non_constructible>();
    test_is_not_empty<tracked>();
    test_is_empty<trap_constructible>();
    test_is_empty<trap_implicit_conversion>();
    test_is_empty<trap_comma>();
    test_is_empty<trap_call>();
    test_is_empty<trap_self_assign>();
    test_is_empty<trap_deref>();
    test_is_empty<trap_array_subscript>();

    test_is_not_empty<void()>();
    test_is_not_empty<void()&>();
    test_is_not_empty<void() &&>();
    test_is_not_empty<void() const>();
    test_is_not_empty<void() const&>();
    test_is_not_empty<void() const&&>();
    test_is_not_empty<void() volatile>();
    test_is_not_empty<void() volatile&>();
    test_is_not_empty<void() volatile&&>();
    test_is_not_empty<void() const volatile>();
    test_is_not_empty<void() const volatile&>();
    test_is_not_empty<void() const volatile&&>();
    test_is_not_empty<void() noexcept>();
    test_is_not_empty<void() & noexcept>();
    test_is_not_empty<void() && noexcept>();
    test_is_not_empty<void() const noexcept>();
    test_is_not_empty<void() const & noexcept>();
    test_is_not_empty<void() const && noexcept>();
    test_is_not_empty<void() volatile noexcept>();
    test_is_not_empty<void() volatile & noexcept>();
    test_is_not_empty<void() volatile && noexcept>();
    test_is_not_empty<void() const volatile noexcept>();
    test_is_not_empty<void() const volatile & noexcept>();
    test_is_not_empty<void() const volatile && noexcept>();

    test_is_not_empty<void(int)>();
    test_is_not_empty<void(int)&>();
    test_is_not_empty<void(int) &&>();
    test_is_not_empty<void(int) const>();
    test_is_not_empty<void(int) const&>();
    test_is_not_empty<void(int) const&&>();
    test_is_not_empty<void(int) volatile>();
    test_is_not_empty<void(int) volatile&>();
    test_is_not_empty<void(int) volatile&&>();
    test_is_not_empty<void(int) const volatile>();
    test_is_not_empty<void(int) const volatile&>();
    test_is_not_empty<void(int) const volatile&&>();
    test_is_not_empty<void(int) noexcept>();
    test_is_not_empty<void(int) & noexcept>();
    test_is_not_empty<void(int) && noexcept>();
    test_is_not_empty<void(int) const noexcept>();
    test_is_not_empty<void(int) const & noexcept>();
    test_is_not_empty<void(int) const && noexcept>();
    test_is_not_empty<void(int) volatile noexcept>();
    test_is_not_empty<void(int) volatile & noexcept>();
    test_is_not_empty<void(int) volatile && noexcept>();
    test_is_not_empty<void(int) const volatile noexcept>();
    test_is_not_empty<void(int) const volatile & noexcept>();
    test_is_not_empty<void(int) const volatile && noexcept>();

    test_is_not_empty<void(...)>();
    test_is_not_empty<void(...)&>();
    test_is_not_empty<void(...) &&>();
    test_is_not_empty<void(...) const>();
    test_is_not_empty<void(...) const&>();
    test_is_not_empty<void(...) const&&>();
    test_is_not_empty<void(...) volatile>();
    test_is_not_empty<void(...) volatile&>();
    test_is_not_empty<void(...) volatile&&>();
    test_is_not_empty<void(...) const volatile>();
    test_is_not_empty<void(...) const volatile&>();
    test_is_not_empty<void(...) const volatile&&>();
    test_is_not_empty<void(...) noexcept>();
    test_is_not_empty<void(...) & noexcept>();
    test_is_not_empty<void(...) && noexcept>();
    test_is_not_empty<void(...) const noexcept>();
    test_is_not_empty<void(...) const & noexcept>();
    test_is_not_empty<void(...) const && noexcept>();
    test_is_not_empty<void(...) volatile noexcept>();
    test_is_not_empty<void(...) volatile & noexcept>();
    test_is_not_empty<void(...) volatile && noexcept>();
    test_is_not_empty<void(...) const volatile noexcept>();
    test_is_not_empty<void(...) const volatile & noexcept>();
    test_is_not_empty<void(...) const volatile && noexcept>();

    test_is_not_empty<void(int, ...)>();
    test_is_not_empty<void(int, ...)&>();
    test_is_not_empty<void(int, ...) &&>();
    test_is_not_empty<void(int, ...) const>();
    test_is_not_empty<void(int, ...) const&>();
    test_is_not_empty<void(int, ...) const&&>();
    test_is_not_empty<void(int, ...) volatile>();
    test_is_not_empty<void(int, ...) volatile&>();
    test_is_not_empty<void(int, ...) volatile&&>();
    test_is_not_empty<void(int, ...) const volatile>();
    test_is_not_empty<void(int, ...) const volatile&>();
    test_is_not_empty<void(int, ...) const volatile&&>();
    test_is_not_empty<void(int, ...) noexcept>();
    test_is_not_empty<void(int, ...) & noexcept>();
    test_is_not_empty<void(int, ...) && noexcept>();
    test_is_not_empty<void(int, ...) const noexcept>();
    test_is_not_empty<void(int, ...) const & noexcept>();
    test_is_not_empty<void(int, ...) const && noexcept>();
    test_is_not_empty<void(int, ...) volatile noexcept>();
    test_is_not_empty<void(int, ...) volatile & noexcept>();
    test_is_not_empty<void(int, ...) volatile && noexcept>();
    test_is_not_empty<void(int, ...) const volatile noexcept>();
    test_is_not_empty<void(int, ...) const volatile & noexcept>();
    test_is_not_empty<void(int, ...) const volatile && noexcept>();

    test_is_not_empty<int()>();
    test_is_not_empty<int()&>();
    test_is_not_empty<int() &&>();
    test_is_not_empty<int() const>();
    test_is_not_empty<int() const&>();
    test_is_not_empty<int() const&&>();
    test_is_not_empty<int() volatile>();
    test_is_not_empty<int() volatile&>();
    test_is_not_empty<int() volatile&&>();
    test_is_not_empty<int() const volatile>();
    test_is_not_empty<int() const volatile&>();
    test_is_not_empty<int() const volatile&&>();
    test_is_not_empty<int() noexcept>();
    test_is_not_empty<int() & noexcept>();
    test_is_not_empty<int() && noexcept>();
    test_is_not_empty<int() const noexcept>();
    test_is_not_empty<int() const & noexcept>();
    test_is_not_empty<int() const && noexcept>();
    test_is_not_empty<int() volatile noexcept>();
    test_is_not_empty<int() volatile & noexcept>();
    test_is_not_empty<int() volatile && noexcept>();
    test_is_not_empty<int() const volatile noexcept>();
    test_is_not_empty<int() const volatile & noexcept>();
    test_is_not_empty<int() const volatile && noexcept>();

    test_is_not_empty<int(int)>();
    test_is_not_empty<int(int)&>();
    test_is_not_empty<int(int) &&>();
    test_is_not_empty<int(int) const>();
    test_is_not_empty<int(int) const&>();
    test_is_not_empty<int(int) const&&>();
    test_is_not_empty<int(int) volatile>();
    test_is_not_empty<int(int) volatile&>();
    test_is_not_empty<int(int) volatile&&>();
    test_is_not_empty<int(int) const volatile>();
    test_is_not_empty<int(int) const volatile&>();
    test_is_not_empty<int(int) const volatile&&>();
    test_is_not_empty<int(int) noexcept>();
    test_is_not_empty<int(int) & noexcept>();
    test_is_not_empty<int(int) && noexcept>();
    test_is_not_empty<int(int) const noexcept>();
    test_is_not_empty<int(int) const & noexcept>();
    test_is_not_empty<int(int) const && noexcept>();
    test_is_not_empty<int(int) volatile noexcept>();
    test_is_not_empty<int(int) volatile & noexcept>();
    test_is_not_empty<int(int) volatile && noexcept>();
    test_is_not_empty<int(int) const volatile noexcept>();
    test_is_not_empty<int(int) const volatile & noexcept>();
    test_is_not_empty<int(int) const volatile && noexcept>();

    test_is_not_empty<int(...)>();
    test_is_not_empty<int(...)&>();
    test_is_not_empty<int(...) &&>();
    test_is_not_empty<int(...) const>();
    test_is_not_empty<int(...) const&>();
    test_is_not_empty<int(...) const&&>();
    test_is_not_empty<int(...) volatile>();
    test_is_not_empty<int(...) volatile&>();
    test_is_not_empty<int(...) volatile&&>();
    test_is_not_empty<int(...) const volatile>();
    test_is_not_empty<int(...) const volatile&>();
    test_is_not_empty<int(...) const volatile&&>();
    test_is_not_empty<int(...) noexcept>();
    test_is_not_empty<int(...) & noexcept>();
    test_is_not_empty<int(...) && noexcept>();
    test_is_not_empty<int(...) const noexcept>();
    test_is_not_empty<int(...) const & noexcept>();
    test_is_not_empty<int(...) const && noexcept>();
    test_is_not_empty<int(...) volatile noexcept>();
    test_is_not_empty<int(...) volatile & noexcept>();
    test_is_not_empty<int(...) volatile && noexcept>();
    test_is_not_empty<int(...) const volatile noexcept>();
    test_is_not_empty<int(...) const volatile & noexcept>();
    test_is_not_empty<int(...) const volatile && noexcept>();

    test_is_not_empty<int(int, ...)>();
    test_is_not_empty<int(int, ...)&>();
    test_is_not_empty<int(int, ...) &&>();
    test_is_not_empty<int(int, ...) const>();
    test_is_not_empty<int(int, ...) const&>();
    test_is_not_empty<int(int, ...) const&&>();
    test_is_not_empty<int(int, ...) volatile>();
    test_is_not_empty<int(int, ...) volatile&>();
    test_is_not_empty<int(int, ...) volatile&&>();
    test_is_not_empty<int(int, ...) const volatile>();
    test_is_not_empty<int(int, ...) const volatile&>();
    test_is_not_empty<int(int, ...) const volatile&&>();
    test_is_not_empty<int(int, ...) noexcept>();
    test_is_not_empty<int(int, ...) & noexcept>();
    test_is_not_empty<int(int, ...) && noexcept>();
    test_is_not_empty<int(int, ...) const noexcept>();
    test_is_not_empty<int(int, ...) const & noexcept>();
    test_is_not_empty<int(int, ...) const && noexcept>();
    test_is_not_empty<int(int, ...) volatile noexcept>();
    test_is_not_empty<int(int, ...) volatile & noexcept>();
    test_is_not_empty<int(int, ...) volatile && noexcept>();
    test_is_not_empty<int(int, ...) const volatile noexcept>();
    test_is_not_empty<int(int, ...) const volatile & noexcept>();
    test_is_not_empty<int(int, ...) const volatile && noexcept>();

    test_is_not_empty<void (*)()>();
    test_is_not_empty<void (*)() noexcept>();

    test_is_not_empty<void (*)(int)>();
    test_is_not_empty<void (*)(int) noexcept>();

    test_is_not_empty<void (*)(...)>();
    test_is_not_empty<void (*)(...) noexcept>();

    test_is_not_empty<void (*)(int, ...)>();
    test_is_not_empty<void (*)(int, ...) noexcept>();

    test_is_not_empty<int (*)()>();
    test_is_not_empty<int (*)() noexcept>();

    test_is_not_empty<int (*)(int)>();
    test_is_not_empty<int (*)(int) noexcept>();

    test_is_not_empty<int (*)(...)>();
    test_is_not_empty<int (*)(...) noexcept>();

    test_is_not_empty<int (*)(int, ...)>();
    test_is_not_empty<int (*)(int, ...) noexcept>();

    test_is_not_empty<void (&)()>();
    test_is_not_empty<void (&)() noexcept>();

    test_is_not_empty<void (&)(int)>();
    test_is_not_empty<void (&)(int) noexcept>();

    test_is_not_empty<void (&)(...)>();
    test_is_not_empty<void (&)(...) noexcept>();

    test_is_not_empty<void (&)(int, ...)>();
    test_is_not_empty<void (&)(int, ...) noexcept>();

    test_is_not_empty<int (&)()>();
    test_is_not_empty<int (&)() noexcept>();

    test_is_not_empty<int (&)(int)>();
    test_is_not_empty<int (&)(int) noexcept>();

    test_is_not_empty<int (&)(...)>();
    test_is_not_empty<int (&)(...) noexcept>();

    test_is_not_empty<int (&)(int, ...)>();
    test_is_not_empty<int (&)(int, ...) noexcept>();

    test_is_not_empty<void (&&)()>();
    test_is_not_empty<void (&&)() noexcept>();

    test_is_not_empty<void (&&)(int)>();
    test_is_not_empty<void (&&)(int) noexcept>();

    test_is_not_empty<void (&&)(...)>();
    test_is_not_empty<void (&&)(...) noexcept>();

    test_is_not_empty<void (&&)(int, ...)>();
    test_is_not_empty<void (&&)(int, ...) noexcept>();

    test_is_not_empty<int (&&)()>();
    test_is_not_empty<int (&&)() noexcept>();

    test_is_not_empty<int (&&)(int)>();
    test_is_not_empty<int (&&)(int) noexcept>();

    test_is_not_empty<int (&&)(...)>();
    test_is_not_empty<int (&&)(...) noexcept>();

    test_is_not_empty<int (&&)(int, ...)>();
    test_is_not_empty<int (&&)(int, ...) noexcept>();

    test_is_not_empty<void (class_type::*)()>();
    test_is_not_empty<void (class_type::*)()&>();
    test_is_not_empty<void (class_type::*)() &&>();
    test_is_not_empty<void (class_type::*)() const>();
    test_is_not_empty<void (class_type::*)() const&>();
    test_is_not_empty<void (class_type::*)() const&&>();
    test_is_not_empty<void (class_type::*)() noexcept>();
    test_is_not_empty<void (class_type::*)() & noexcept>();
    test_is_not_empty<void (class_type::*)() && noexcept>();
    test_is_not_empty<void (class_type::*)() const noexcept>();
    test_is_not_empty<void (class_type::*)() const & noexcept>();
    test_is_not_empty<void (class_type::*)() const && noexcept>();

    test_is_not_empty<void (class_type::*)(int)>();
    test_is_not_empty<void (class_type::*)(int)&>();
    test_is_not_empty<void (class_type::*)(int) &&>();
    test_is_not_empty<void (class_type::*)(int) const>();
    test_is_not_empty<void (class_type::*)(int) const&>();
    test_is_not_empty<void (class_type::*)(int) const&&>();
    test_is_not_empty<void (class_type::*)(int) noexcept>();
    test_is_not_empty<void (class_type::*)(int) & noexcept>();
    test_is_not_empty<void (class_type::*)(int) && noexcept>();
    test_is_not_empty<void (class_type::*)(int) const noexcept>();
    test_is_not_empty<void (class_type::*)(int) const & noexcept>();
    test_is_not_empty<void (class_type::*)(int) const && noexcept>();

    test_is_not_empty<void (class_type::*)(...)>();
    test_is_not_empty<void (class_type::*)(...)&>();
    test_is_not_empty<void (class_type::*)(...) &&>();
    test_is_not_empty<void (class_type::*)(...) const>();
    test_is_not_empty<void (class_type::*)(...) const&>();
    test_is_not_empty<void (class_type::*)(...) const&&>();
    test_is_not_empty<void (class_type::*)(...) noexcept>();
    test_is_not_empty<void (class_type::*)(...) & noexcept>();
    test_is_not_empty<void (class_type::*)(...) && noexcept>();
    test_is_not_empty<void (class_type::*)(...) const noexcept>();
    test_is_not_empty<void (class_type::*)(...) const & noexcept>();
    test_is_not_empty<void (class_type::*)(...) const && noexcept>();

    test_is_not_empty<void (class_type::*)(int, ...)>();
    test_is_not_empty<void (class_type::*)(int, ...)&>();
    test_is_not_empty<void (class_type::*)(int, ...) &&>();
    test_is_not_empty<void (class_type::*)(int, ...) const>();
    test_is_not_empty<void (class_type::*)(int, ...) const&>();
    test_is_not_empty<void (class_type::*)(int, ...) const&&>();
    test_is_not_empty<void (class_type::*)(int, ...) noexcept>();
    test_is_not_empty<void (class_type::*)(int, ...) & noexcept>();
    test_is_not_empty<void (class_type::*)(int, ...) && noexcept>();
    test_is_not_empty<void (class_type::*)(int, ...) const noexcept>();
    test_is_not_empty<void (class_type::*)(int, ...) const & noexcept>();
    test_is_not_empty<void (class_type::*)(int, ...) const && noexcept>();

    test_is_not_empty<int (class_type::*)()>();
    test_is_not_empty<int (class_type::*)()&>();
    test_is_not_empty<int (class_type::*)() &&>();
    test_is_not_empty<int (class_type::*)() const>();
    test_is_not_empty<int (class_type::*)() const&>();
    test_is_not_empty<int (class_type::*)() const&&>();
    test_is_not_empty<int (class_type::*)() noexcept>();
    test_is_not_empty<int (class_type::*)() & noexcept>();
    test_is_not_empty<int (class_type::*)() && noexcept>();
    test_is_not_empty<int (class_type::*)() const noexcept>();
    test_is_not_empty<int (class_type::*)() const & noexcept>();
    test_is_not_empty<int (class_type::*)() const && noexcept>();

    test_is_not_empty<int (class_type::*)(int)>();
    test_is_not_empty<int (class_type::*)(int)&>();
    test_is_not_empty<int (class_type::*)(int) &&>();
    test_is_not_empty<int (class_type::*)(int) const>();
    test_is_not_empty<int (class_type::*)(int) const&>();
    test_is_not_empty<int (class_type::*)(int) const&&>();
    test_is_not_empty<int (class_type::*)(int) noexcept>();
    test_is_not_empty<int (class_type::*)(int) & noexcept>();
    test_is_not_empty<int (class_type::*)(int) && noexcept>();
    test_is_not_empty<int (class_type::*)(int) const noexcept>();
    test_is_not_empty<int (class_type::*)(int) const & noexcept>();
    test_is_not_empty<int (class_type::*)(int) const && noexcept>();

    test_is_not_empty<int (class_type::*)(...)>();
    test_is_not_empty<int (class_type::*)(...)&>();
    test_is_not_empty<int (class_type::*)(...) &&>();
    test_is_not_empty<int (class_type::*)(...) const>();
    test_is_not_empty<int (class_type::*)(...) const&>();
    test_is_not_empty<int (class_type::*)(...) const&&>();
    test_is_not_empty<int (class_type::*)(...) noexcept>();
    test_is_not_empty<int (class_type::*)(...) & noexcept>();
    test_is_not_empty<int (class_type::*)(...) && noexcept>();
    test_is_not_empty<int (class_type::*)(...) const noexcept>();
    test_is_not_empty<int (class_type::*)(...) const & noexcept>();
    test_is_not_empty<int (class_type::*)(...) const && noexcept>();

    test_is_not_empty<int (class_type::*)(int, ...)>();
    test_is_not_empty<int (class_type::*)(int, ...)&>();
    test_is_not_empty<int (class_type::*)(int, ...) &&>();
    test_is_not_empty<int (class_type::*)(int, ...) const>();
    test_is_not_empty<int (class_type::*)(int, ...) const&>();
    test_is_not_empty<int (class_type::*)(int, ...) const&&>();
    test_is_not_empty<int (class_type::*)(int, ...) noexcept>();
    test_is_not_empty<int (class_type::*)(int, ...) & noexcept>();
    test_is_not_empty<int (class_type::*)(int, ...) && noexcept>();
    test_is_not_empty<int (class_type::*)(int, ...) const noexcept>();
    test_is_not_empty<int (class_type::*)(int, ...) const & noexcept>();
    test_is_not_empty<int (class_type::*)(int, ...) const && noexcept>();
}
