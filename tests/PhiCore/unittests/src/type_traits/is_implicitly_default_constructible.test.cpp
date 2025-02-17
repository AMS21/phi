#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_default_constructible.hpp>
#include <phi/type_traits/is_implicitly_default_constructible.hpp>
#include <type_traits>
#include <vector>

template <typename TypeT>
void test_is_implicitly_default_constructible_impl()
{
#if PHI_HAS_WORKING_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE()
    STATIC_REQUIRE(phi::is_implicitly_default_constructible<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_implicitly_default_constructible<TypeT>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_implicitly_default_constructible_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_not_implicitly_default_constructible_v<TypeT>);
#    endif

    STATIC_REQUIRE(phi::is_default_constructible<TypeT>::value);

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_implicitly_default_constructible<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_implicitly_default_constructible<TypeT>);
#endif
}

template <typename TypeT>
void test_is_not_implicitly_default_constructible_impl()
{
#if PHI_HAS_WORKING_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE()
    STATIC_REQUIRE_FALSE(phi::is_implicitly_default_constructible<TypeT>::value);
    STATIC_REQUIRE(phi::is_not_implicitly_default_constructible<TypeT>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_implicitly_default_constructible_v<TypeT>);
    STATIC_REQUIRE(phi::is_not_implicitly_default_constructible_v<TypeT>);
#    endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_implicitly_default_constructible<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_implicitly_default_constructible<TypeT>);
#endif
}

template <typename TypeT>
void test_is_implicitly_default_constructible()
{
    test_is_implicitly_default_constructible_impl<TypeT>();
    test_is_implicitly_default_constructible_impl<const TypeT>();
    test_is_not_implicitly_default_constructible_impl<volatile TypeT>();
    test_is_not_implicitly_default_constructible_impl<const volatile TypeT>();
}

template <typename TypeT>
void test_is_not_implicitly_default_constructible()
{
    test_is_not_implicitly_default_constructible_impl<TypeT>();
    test_is_not_implicitly_default_constructible_impl<const TypeT>();
    test_is_not_implicitly_default_constructible_impl<volatile TypeT>();
    test_is_not_implicitly_default_constructible_impl<const volatile TypeT>();
}

struct NoDefaultConstructor
{
private:
    NoDefaultConstructor(int /*unused*/)
    {}
};

struct A
{
    A();
};

struct B
{
private:
    // NOLINTNEXTLINE(modernize-use-equals-delete)
    B();
};

struct C
{
    C() = default;
};

struct D
{
    D() = delete;
};

struct ExplicitlyDefaultConstructible1
{
    explicit ExplicitlyDefaultConstructible1() = default;
};

struct ExplicitlyDefaultConstructible2
{
    // NOLINTNEXTLINE(modernize-use-equals-default)
    explicit ExplicitlyDefaultConstructible2()
    {}
};

struct ImplicitlyDefaultConstructible1
{
    // NOLINTNEXTLINE(modernize-use-equals-default)
    ImplicitlyDefaultConstructible1()
    {}
};

struct ImplicitlyDefaultConstructible2
{
    ImplicitlyDefaultConstructible2() = default;
};

struct NonDefaultConstructible1
{
    NonDefaultConstructible1() = delete;
};

struct NonDefaultConstructible2
{
    explicit NonDefaultConstructible2() = delete;
};

struct NonDefaultConstructible3
{
    NonDefaultConstructible3(NonDefaultConstructible3&& /*other*/) noexcept
    {}
};

struct ProtectedDefaultConstructible
{
protected:
    ProtectedDefaultConstructible() = default;
};

struct PrivateDefaultConstructible
{
private:
    PrivateDefaultConstructible() = default;
};

struct Base
{};

struct ProtectedDefaultConstructibleWithBase : Base
{
protected:
    ProtectedDefaultConstructibleWithBase() = default;
};

struct PrivateDefaultConstructibleWithBase : Base
{
private:
    PrivateDefaultConstructibleWithBase() = default;
};

TEST_CASE("is_implicitly_default_constructible")
{
    test_is_not_implicitly_default_constructible<NoDefaultConstructor>();
    test_is_implicitly_default_constructible<A>();
    test_is_not_implicitly_default_constructible<B>();
    test_is_implicitly_default_constructible<C>();
    test_is_not_implicitly_default_constructible<D>();

    test_is_not_implicitly_default_constructible<ExplicitlyDefaultConstructible1>();
    test_is_not_implicitly_default_constructible<ExplicitlyDefaultConstructible2>();
    test_is_implicitly_default_constructible<ImplicitlyDefaultConstructible1>();
    test_is_implicitly_default_constructible<ImplicitlyDefaultConstructible2>();
    test_is_not_implicitly_default_constructible<NonDefaultConstructible1>();
    test_is_not_implicitly_default_constructible<NonDefaultConstructible2>();
    test_is_not_implicitly_default_constructible<NonDefaultConstructible3>();
    test_is_not_implicitly_default_constructible<ProtectedDefaultConstructible>();
    test_is_not_implicitly_default_constructible<PrivateDefaultConstructible>();
    test_is_not_implicitly_default_constructible<ProtectedDefaultConstructibleWithBase>();
    test_is_not_implicitly_default_constructible<PrivateDefaultConstructibleWithBase>();

    test_is_not_implicitly_default_constructible<void>();
    test_is_implicitly_default_constructible<phi::nullptr_t>();
    test_is_implicitly_default_constructible<bool>();
    test_is_implicitly_default_constructible<char>();
    test_is_implicitly_default_constructible<signed char>();
    test_is_implicitly_default_constructible<unsigned char>();
    test_is_implicitly_default_constructible<short>();
    test_is_implicitly_default_constructible<unsigned short>();
    test_is_implicitly_default_constructible<int>();
    test_is_implicitly_default_constructible<unsigned int>();
    test_is_implicitly_default_constructible<long>();
    test_is_implicitly_default_constructible<unsigned long>();
    test_is_implicitly_default_constructible<long long>();
    test_is_implicitly_default_constructible<unsigned long long>();
    test_is_implicitly_default_constructible<float>();
    test_is_implicitly_default_constructible<double>();
    test_is_implicitly_default_constructible<long double>();
    test_is_implicitly_default_constructible<char8_t>();
    test_is_implicitly_default_constructible<char16_t>();
    test_is_implicitly_default_constructible<char32_t>();
    test_is_implicitly_default_constructible<wchar_t>();

    test_is_not_implicitly_default_constructible<phi::boolean>();
    test_is_not_implicitly_default_constructible<phi::integer<signed char>>();
    test_is_not_implicitly_default_constructible<phi::integer<unsigned char>>();
    test_is_not_implicitly_default_constructible<phi::integer<short>>();
    test_is_not_implicitly_default_constructible<phi::integer<unsigned short>>();
    test_is_not_implicitly_default_constructible<phi::integer<int>>();
    test_is_not_implicitly_default_constructible<phi::integer<unsigned int>>();
    test_is_not_implicitly_default_constructible<phi::integer<long>>();
    test_is_not_implicitly_default_constructible<phi::integer<unsigned long>>();
    test_is_not_implicitly_default_constructible<phi::integer<long long>>();
    test_is_not_implicitly_default_constructible<phi::integer<unsigned long long>>();
    test_is_not_implicitly_default_constructible<phi::floating_point<float>>();
    test_is_not_implicitly_default_constructible<phi::floating_point<double>>();
    test_is_not_implicitly_default_constructible<phi::floating_point<long double>>();

    test_is_implicitly_default_constructible<std::vector<int>>();
    test_is_implicitly_default_constructible<phi::scope_ptr<int>>();

    test_is_not_implicitly_default_constructible<int&>();
    test_is_not_implicitly_default_constructible<const int&>();
    test_is_not_implicitly_default_constructible<volatile int&>();
    test_is_not_implicitly_default_constructible<const volatile int&>();
    test_is_not_implicitly_default_constructible<int&&>();
    test_is_not_implicitly_default_constructible<const int&&>();
    test_is_not_implicitly_default_constructible<volatile int&&>();
    test_is_not_implicitly_default_constructible<const volatile int&&>();
    test_is_implicitly_default_constructible<int*>();
    test_is_implicitly_default_constructible<const int*>();
    test_is_implicitly_default_constructible<volatile int*>();
    test_is_implicitly_default_constructible<const volatile int*>();
    test_is_implicitly_default_constructible<int**>();
    test_is_implicitly_default_constructible<const int**>();
    test_is_implicitly_default_constructible<volatile int**>();
    test_is_implicitly_default_constructible<const volatile int**>();
    test_is_not_implicitly_default_constructible<int*&>();
    test_is_not_implicitly_default_constructible<const int*&>();
    test_is_not_implicitly_default_constructible<volatile int*&>();
    test_is_not_implicitly_default_constructible<const volatile int*&>();
    test_is_not_implicitly_default_constructible<int*&&>();
    test_is_not_implicitly_default_constructible<const int*&&>();
    test_is_not_implicitly_default_constructible<volatile int*&&>();
    test_is_not_implicitly_default_constructible<const volatile int*&&>();
    test_is_implicitly_default_constructible<void*>();
    test_is_implicitly_default_constructible<char[3]>();
#if PHI_COMPILER_WORKAROUND(GCC, 8, 0, 0)
    test_is_not_implicitly_default_constructible<char[]>();
#endif
    test_is_implicitly_default_constructible<char* [3]>();
#if PHI_COMPILER_WORKAROUND(GCC, 8, 0, 0)
    test_is_not_implicitly_default_constructible<char*[]>();
#endif
    test_is_implicitly_default_constructible<int(*)[3]>();
    test_is_implicitly_default_constructible<int(*)[]>();
    test_is_not_implicitly_default_constructible<int(&)[3]>();
    test_is_not_implicitly_default_constructible<int(&)[]>();
    test_is_not_implicitly_default_constructible<int(&&)[3]>();
    test_is_not_implicitly_default_constructible<int(&&)[]>();
    test_is_implicitly_default_constructible<char[3][2]>();
#if PHI_COMPILER_WORKAROUND(GCC, 8, 0, 0)
    test_is_not_implicitly_default_constructible<char[][2]>();
#endif
    test_is_implicitly_default_constructible<char* [3][2]>();
#if PHI_COMPILER_WORKAROUND(GCC, 8, 0, 0)
    test_is_not_implicitly_default_constructible<char*[][2]>();
#endif
    test_is_implicitly_default_constructible<int(*)[3][2]>();
    test_is_implicitly_default_constructible<int(*)[][2]>();
    test_is_not_implicitly_default_constructible<int(&)[3][2]>();
    test_is_not_implicitly_default_constructible<int(&)[][2]>();
    test_is_not_implicitly_default_constructible<int(&&)[3][2]>();
    test_is_not_implicitly_default_constructible<int(&&)[][2]>();
    test_is_implicitly_default_constructible<class_type>();
#if PHI_COMPILER_WORKAROUND(GCC, 8, 0, 0)
    test_is_not_implicitly_default_constructible<class_type[]>();
#endif
    test_is_implicitly_default_constructible<class_type[2]>();
    test_is_implicitly_default_constructible<template_type<void>>();
    test_is_implicitly_default_constructible<template_type<int>>();
    test_is_implicitly_default_constructible<template_type<class_type>>();
    test_is_implicitly_default_constructible<template_type<incomplete_type>>();
    test_is_implicitly_default_constructible<variadic_template<>>();
    test_is_implicitly_default_constructible<variadic_template<void>>();
    test_is_implicitly_default_constructible<variadic_template<int>>();
    test_is_implicitly_default_constructible<variadic_template<class_type>>();
    test_is_implicitly_default_constructible<variadic_template<incomplete_type>>();
    test_is_implicitly_default_constructible<
            variadic_template<int, void, class_type, volatile char[]>>();
    test_is_implicitly_default_constructible<public_derived_from<base>>();
    test_is_implicitly_default_constructible<public_derived_from<derived>>();
    test_is_implicitly_default_constructible<public_derived_from<class_type>>();
    test_is_implicitly_default_constructible<private_derived_from<base>>();
    test_is_implicitly_default_constructible<private_derived_from<derived>>();
    test_is_implicitly_default_constructible<private_derived_from<class_type>>();
    test_is_implicitly_default_constructible<protected_derived_from<base>>();
    test_is_implicitly_default_constructible<protected_derived_from<derived>>();
    test_is_implicitly_default_constructible<protected_derived_from<class_type>>();
    test_is_implicitly_default_constructible<union_type>();
    test_is_implicitly_default_constructible<non_empty_union>();
    test_is_implicitly_default_constructible<empty>();
    test_is_implicitly_default_constructible<not_empty>();
    test_is_implicitly_default_constructible<bit_zero>();
    test_is_implicitly_default_constructible<bit_one>();
    test_is_implicitly_default_constructible<base>();
    test_is_implicitly_default_constructible<derived>();
    test_is_not_implicitly_default_constructible<abstract>();
    test_is_not_implicitly_default_constructible<public_abstract>();
    test_is_not_implicitly_default_constructible<private_abstract>();
    test_is_not_implicitly_default_constructible<protected_abstract>();
    test_is_not_implicitly_default_constructible<abstract_template<int>>();
    test_is_implicitly_default_constructible<abstract_template<double>>();
    test_is_not_implicitly_default_constructible<abstract_template<class_type>>();
    test_is_not_implicitly_default_constructible<abstract_template<incomplete_type>>();
    test_is_implicitly_default_constructible<final_type>();
    test_is_implicitly_default_constructible<public_destructor>();
    test_is_not_implicitly_default_constructible<protected_destructor>();
    test_is_not_implicitly_default_constructible<private_destructor>();
    test_is_implicitly_default_constructible<virtual_public_destructor>();
    test_is_not_implicitly_default_constructible<virtual_protected_destructor>();
    test_is_not_implicitly_default_constructible<virtual_private_destructor>();
    test_is_not_implicitly_default_constructible<pure_public_destructor>();
    test_is_not_implicitly_default_constructible<pure_protected_destructor>();
    test_is_not_implicitly_default_constructible<pure_private_destructor>();
    test_is_not_implicitly_default_constructible<deleted_public_destructor>();
    test_is_not_implicitly_default_constructible<deleted_protected_destructor>();
    test_is_not_implicitly_default_constructible<deleted_private_destructor>();
    test_is_not_implicitly_default_constructible<deleted_virtual_public_destructor>();
    test_is_not_implicitly_default_constructible<deleted_virtual_protected_destructor>();
    test_is_not_implicitly_default_constructible<deleted_virtual_private_destructor>();
    test_is_implicitly_default_constructible<Enum>();
    test_is_implicitly_default_constructible<EnumSigned>();
    test_is_implicitly_default_constructible<EnumUnsigned>();
    test_is_implicitly_default_constructible<EnumClass>();
    test_is_implicitly_default_constructible<EnumStruct>();
    test_is_not_implicitly_default_constructible<function_type>();
    test_is_implicitly_default_constructible<function_ptr>();
    test_is_implicitly_default_constructible<member_object_ptr>();
    test_is_implicitly_default_constructible<member_function_ptr>();
    test_is_implicitly_default_constructible<int class_type::*>();
    test_is_implicitly_default_constructible<float class_type::*>();
    test_is_implicitly_default_constructible<void * class_type::*>();
    test_is_implicitly_default_constructible<int * class_type::*>();
    test_is_not_implicitly_default_constructible<int class_type::*&>();
    test_is_not_implicitly_default_constructible<float class_type::*&>();
    test_is_not_implicitly_default_constructible<void * class_type::*&>();
    test_is_not_implicitly_default_constructible<int * class_type::*&>();
    test_is_not_implicitly_default_constructible<int class_type::*&&>();
    test_is_not_implicitly_default_constructible<float class_type::*&&>();
    test_is_not_implicitly_default_constructible<void * class_type::*&&>();
    test_is_not_implicitly_default_constructible<int * class_type::*&&>();
    test_is_implicitly_default_constructible<int class_type::* const>();
    test_is_implicitly_default_constructible<float class_type::* const>();
    test_is_implicitly_default_constructible<void * class_type::* const>();
    test_is_not_implicitly_default_constructible<int class_type::* const&>();
    test_is_not_implicitly_default_constructible<float class_type::* const&>();
    test_is_not_implicitly_default_constructible<void * class_type::* const&>();
    test_is_not_implicitly_default_constructible<int class_type::* const&&>();
    test_is_not_implicitly_default_constructible<float class_type::* const&&>();
    test_is_not_implicitly_default_constructible<void * class_type::* const&&>();
    test_is_not_implicitly_default_constructible<int class_type::* volatile>();
    test_is_not_implicitly_default_constructible<float class_type::* volatile>();
    test_is_not_implicitly_default_constructible<void * class_type::* volatile>();
    test_is_not_implicitly_default_constructible<int class_type::* volatile&>();
    test_is_not_implicitly_default_constructible<float class_type::* volatile&>();
    test_is_not_implicitly_default_constructible<void * class_type::* volatile&>();
    test_is_not_implicitly_default_constructible<int class_type::* volatile&&>();
    test_is_not_implicitly_default_constructible<float class_type::* volatile&&>();
    test_is_not_implicitly_default_constructible<void * class_type::* volatile&&>();
    test_is_not_implicitly_default_constructible<int class_type::* const volatile>();
    test_is_not_implicitly_default_constructible<float class_type::* const volatile>();
    test_is_not_implicitly_default_constructible<void * class_type::* const volatile>();
    test_is_not_implicitly_default_constructible<int class_type::* const volatile&>();
    test_is_not_implicitly_default_constructible<float class_type::* const volatile&>();
    test_is_not_implicitly_default_constructible<void * class_type::* const volatile&>();
    test_is_not_implicitly_default_constructible<int class_type::* const volatile&&>();
    test_is_not_implicitly_default_constructible<float class_type::* const volatile&&>();
    test_is_not_implicitly_default_constructible<void * class_type::* const volatile&&>();
    test_is_implicitly_default_constructible<non_copyable>();
    test_is_implicitly_default_constructible<non_moveable>();
    test_is_not_implicitly_default_constructible<non_constructible>();
    test_is_implicitly_default_constructible<tracked>();
    test_is_implicitly_default_constructible<trap_constructible>();
    test_is_implicitly_default_constructible<trap_implicit_conversion>();
    test_is_implicitly_default_constructible<trap_comma>();
    test_is_implicitly_default_constructible<trap_call>();
    test_is_implicitly_default_constructible<trap_self_assign>();
    test_is_implicitly_default_constructible<trap_deref>();
    test_is_implicitly_default_constructible<trap_array_subscript>();

    test_is_not_implicitly_default_constructible<void()>();
    test_is_not_implicitly_default_constructible<void()&>();
    test_is_not_implicitly_default_constructible<void() &&>();
    test_is_not_implicitly_default_constructible<void() const>();
    test_is_not_implicitly_default_constructible<void() const&>();
    test_is_not_implicitly_default_constructible<void() const&&>();
    test_is_not_implicitly_default_constructible<void() volatile>();
    test_is_not_implicitly_default_constructible<void() volatile&>();
    test_is_not_implicitly_default_constructible<void() volatile&&>();
    test_is_not_implicitly_default_constructible<void() const volatile>();
    test_is_not_implicitly_default_constructible<void() const volatile&>();
    test_is_not_implicitly_default_constructible<void() const volatile&&>();
    test_is_not_implicitly_default_constructible<void() noexcept>();
    test_is_not_implicitly_default_constructible<void() & noexcept>();
    test_is_not_implicitly_default_constructible<void() && noexcept>();
    test_is_not_implicitly_default_constructible<void() const noexcept>();
    test_is_not_implicitly_default_constructible<void() const & noexcept>();
    test_is_not_implicitly_default_constructible<void() const && noexcept>();
    test_is_not_implicitly_default_constructible<void() volatile noexcept>();
    test_is_not_implicitly_default_constructible<void() volatile & noexcept>();
    test_is_not_implicitly_default_constructible<void() volatile && noexcept>();
    test_is_not_implicitly_default_constructible<void() const volatile noexcept>();
    test_is_not_implicitly_default_constructible<void() const volatile & noexcept>();
    test_is_not_implicitly_default_constructible<void() const volatile && noexcept>();

    test_is_not_implicitly_default_constructible<void(int)>();
    test_is_not_implicitly_default_constructible<void(int)&>();
    test_is_not_implicitly_default_constructible<void(int) &&>();
    test_is_not_implicitly_default_constructible<void(int) const>();
    test_is_not_implicitly_default_constructible<void(int) const&>();
    test_is_not_implicitly_default_constructible<void(int) const&&>();
    test_is_not_implicitly_default_constructible<void(int) volatile>();
    test_is_not_implicitly_default_constructible<void(int) volatile&>();
    test_is_not_implicitly_default_constructible<void(int) volatile&&>();
    test_is_not_implicitly_default_constructible<void(int) const volatile>();
    test_is_not_implicitly_default_constructible<void(int) const volatile&>();
    test_is_not_implicitly_default_constructible<void(int) const volatile&&>();
    test_is_not_implicitly_default_constructible<void(int) noexcept>();
    test_is_not_implicitly_default_constructible<void(int) & noexcept>();
    test_is_not_implicitly_default_constructible<void(int) && noexcept>();
    test_is_not_implicitly_default_constructible<void(int) const noexcept>();
    test_is_not_implicitly_default_constructible<void(int) const & noexcept>();
    test_is_not_implicitly_default_constructible<void(int) const && noexcept>();
    test_is_not_implicitly_default_constructible<void(int) volatile noexcept>();
    test_is_not_implicitly_default_constructible<void(int) volatile & noexcept>();
    test_is_not_implicitly_default_constructible<void(int) volatile && noexcept>();
    test_is_not_implicitly_default_constructible<void(int) const volatile noexcept>();
    test_is_not_implicitly_default_constructible<void(int) const volatile & noexcept>();
    test_is_not_implicitly_default_constructible<void(int) const volatile && noexcept>();

    test_is_not_implicitly_default_constructible<void(...)>();
    test_is_not_implicitly_default_constructible<void(...)&>();
    test_is_not_implicitly_default_constructible<void(...) &&>();
    test_is_not_implicitly_default_constructible<void(...) const>();
    test_is_not_implicitly_default_constructible<void(...) const&>();
    test_is_not_implicitly_default_constructible<void(...) const&&>();
    test_is_not_implicitly_default_constructible<void(...) volatile>();
    test_is_not_implicitly_default_constructible<void(...) volatile&>();
    test_is_not_implicitly_default_constructible<void(...) volatile&&>();
    test_is_not_implicitly_default_constructible<void(...) const volatile>();
    test_is_not_implicitly_default_constructible<void(...) const volatile&>();
    test_is_not_implicitly_default_constructible<void(...) const volatile&&>();
    test_is_not_implicitly_default_constructible<void(...) noexcept>();
    test_is_not_implicitly_default_constructible<void(...) & noexcept>();
    test_is_not_implicitly_default_constructible<void(...) && noexcept>();
    test_is_not_implicitly_default_constructible<void(...) const noexcept>();
    test_is_not_implicitly_default_constructible<void(...) const & noexcept>();
    test_is_not_implicitly_default_constructible<void(...) const && noexcept>();
    test_is_not_implicitly_default_constructible<void(...) volatile noexcept>();
    test_is_not_implicitly_default_constructible<void(...) volatile & noexcept>();
    test_is_not_implicitly_default_constructible<void(...) volatile && noexcept>();
    test_is_not_implicitly_default_constructible<void(...) const volatile noexcept>();
    test_is_not_implicitly_default_constructible<void(...) const volatile & noexcept>();
    test_is_not_implicitly_default_constructible<void(...) const volatile && noexcept>();

    test_is_not_implicitly_default_constructible<void(int, ...)>();
    test_is_not_implicitly_default_constructible<void(int, ...)&>();
    test_is_not_implicitly_default_constructible<void(int, ...) &&>();
    test_is_not_implicitly_default_constructible<void(int, ...) const>();
    test_is_not_implicitly_default_constructible<void(int, ...) const&>();
    test_is_not_implicitly_default_constructible<void(int, ...) const&&>();
    test_is_not_implicitly_default_constructible<void(int, ...) volatile>();
    test_is_not_implicitly_default_constructible<void(int, ...) volatile&>();
    test_is_not_implicitly_default_constructible<void(int, ...) volatile&&>();
    test_is_not_implicitly_default_constructible<void(int, ...) const volatile>();
    test_is_not_implicitly_default_constructible<void(int, ...) const volatile&>();
    test_is_not_implicitly_default_constructible<void(int, ...) const volatile&&>();
    test_is_not_implicitly_default_constructible<void(int, ...) noexcept>();
    test_is_not_implicitly_default_constructible<void(int, ...) & noexcept>();
    test_is_not_implicitly_default_constructible<void(int, ...) && noexcept>();
    test_is_not_implicitly_default_constructible<void(int, ...) const noexcept>();
    test_is_not_implicitly_default_constructible<void(int, ...) const & noexcept>();
    test_is_not_implicitly_default_constructible<void(int, ...) const && noexcept>();
    test_is_not_implicitly_default_constructible<void(int, ...) volatile noexcept>();
    test_is_not_implicitly_default_constructible<void(int, ...) volatile & noexcept>();
    test_is_not_implicitly_default_constructible<void(int, ...) volatile && noexcept>();
    test_is_not_implicitly_default_constructible<void(int, ...) const volatile noexcept>();
    test_is_not_implicitly_default_constructible<void(int, ...) const volatile & noexcept>();
    test_is_not_implicitly_default_constructible<void(int, ...) const volatile && noexcept>();

    test_is_not_implicitly_default_constructible<int()>();
    test_is_not_implicitly_default_constructible<int()&>();
    test_is_not_implicitly_default_constructible<int() &&>();
    test_is_not_implicitly_default_constructible<int() const>();
    test_is_not_implicitly_default_constructible<int() const&>();
    test_is_not_implicitly_default_constructible<int() const&&>();
    test_is_not_implicitly_default_constructible<int() volatile>();
    test_is_not_implicitly_default_constructible<int() volatile&>();
    test_is_not_implicitly_default_constructible<int() volatile&&>();
    test_is_not_implicitly_default_constructible<int() const volatile>();
    test_is_not_implicitly_default_constructible<int() const volatile&>();
    test_is_not_implicitly_default_constructible<int() const volatile&&>();
    test_is_not_implicitly_default_constructible<int() noexcept>();
    test_is_not_implicitly_default_constructible<int() & noexcept>();
    test_is_not_implicitly_default_constructible<int() && noexcept>();
    test_is_not_implicitly_default_constructible<int() const noexcept>();
    test_is_not_implicitly_default_constructible<int() const & noexcept>();
    test_is_not_implicitly_default_constructible<int() const && noexcept>();
    test_is_not_implicitly_default_constructible<int() volatile noexcept>();
    test_is_not_implicitly_default_constructible<int() volatile & noexcept>();
    test_is_not_implicitly_default_constructible<int() volatile && noexcept>();
    test_is_not_implicitly_default_constructible<int() const volatile noexcept>();
    test_is_not_implicitly_default_constructible<int() const volatile & noexcept>();
    test_is_not_implicitly_default_constructible<int() const volatile && noexcept>();

    test_is_not_implicitly_default_constructible<int(int)>();
    test_is_not_implicitly_default_constructible<int(int)&>();
    test_is_not_implicitly_default_constructible<int(int) &&>();
    test_is_not_implicitly_default_constructible<int(int) const>();
    test_is_not_implicitly_default_constructible<int(int) const&>();
    test_is_not_implicitly_default_constructible<int(int) const&&>();
    test_is_not_implicitly_default_constructible<int(int) volatile>();
    test_is_not_implicitly_default_constructible<int(int) volatile&>();
    test_is_not_implicitly_default_constructible<int(int) volatile&&>();
    test_is_not_implicitly_default_constructible<int(int) const volatile>();
    test_is_not_implicitly_default_constructible<int(int) const volatile&>();
    test_is_not_implicitly_default_constructible<int(int) const volatile&&>();
    test_is_not_implicitly_default_constructible<int(int) noexcept>();
    test_is_not_implicitly_default_constructible<int(int) & noexcept>();
    test_is_not_implicitly_default_constructible<int(int) && noexcept>();
    test_is_not_implicitly_default_constructible<int(int) const noexcept>();
    test_is_not_implicitly_default_constructible<int(int) const & noexcept>();
    test_is_not_implicitly_default_constructible<int(int) const && noexcept>();
    test_is_not_implicitly_default_constructible<int(int) volatile noexcept>();
    test_is_not_implicitly_default_constructible<int(int) volatile & noexcept>();
    test_is_not_implicitly_default_constructible<int(int) volatile && noexcept>();
    test_is_not_implicitly_default_constructible<int(int) const volatile noexcept>();
    test_is_not_implicitly_default_constructible<int(int) const volatile & noexcept>();
    test_is_not_implicitly_default_constructible<int(int) const volatile && noexcept>();

    test_is_not_implicitly_default_constructible<int(...)>();
    test_is_not_implicitly_default_constructible<int(...)&>();
    test_is_not_implicitly_default_constructible<int(...) &&>();
    test_is_not_implicitly_default_constructible<int(...) const>();
    test_is_not_implicitly_default_constructible<int(...) const&>();
    test_is_not_implicitly_default_constructible<int(...) const&&>();
    test_is_not_implicitly_default_constructible<int(...) volatile>();
    test_is_not_implicitly_default_constructible<int(...) volatile&>();
    test_is_not_implicitly_default_constructible<int(...) volatile&&>();
    test_is_not_implicitly_default_constructible<int(...) const volatile>();
    test_is_not_implicitly_default_constructible<int(...) const volatile&>();
    test_is_not_implicitly_default_constructible<int(...) const volatile&&>();
    test_is_not_implicitly_default_constructible<int(...) noexcept>();
    test_is_not_implicitly_default_constructible<int(...) & noexcept>();
    test_is_not_implicitly_default_constructible<int(...) && noexcept>();
    test_is_not_implicitly_default_constructible<int(...) const noexcept>();
    test_is_not_implicitly_default_constructible<int(...) const & noexcept>();
    test_is_not_implicitly_default_constructible<int(...) const && noexcept>();
    test_is_not_implicitly_default_constructible<int(...) volatile noexcept>();
    test_is_not_implicitly_default_constructible<int(...) volatile & noexcept>();
    test_is_not_implicitly_default_constructible<int(...) volatile && noexcept>();
    test_is_not_implicitly_default_constructible<int(...) const volatile noexcept>();
    test_is_not_implicitly_default_constructible<int(...) const volatile & noexcept>();
    test_is_not_implicitly_default_constructible<int(...) const volatile && noexcept>();

    test_is_not_implicitly_default_constructible<int(int, ...)>();
    test_is_not_implicitly_default_constructible<int(int, ...)&>();
    test_is_not_implicitly_default_constructible<int(int, ...) &&>();
    test_is_not_implicitly_default_constructible<int(int, ...) const>();
    test_is_not_implicitly_default_constructible<int(int, ...) const&>();
    test_is_not_implicitly_default_constructible<int(int, ...) const&&>();
    test_is_not_implicitly_default_constructible<int(int, ...) volatile>();
    test_is_not_implicitly_default_constructible<int(int, ...) volatile&>();
    test_is_not_implicitly_default_constructible<int(int, ...) volatile&&>();
    test_is_not_implicitly_default_constructible<int(int, ...) const volatile>();
    test_is_not_implicitly_default_constructible<int(int, ...) const volatile&>();
    test_is_not_implicitly_default_constructible<int(int, ...) const volatile&&>();
    test_is_not_implicitly_default_constructible<int(int, ...) noexcept>();
    test_is_not_implicitly_default_constructible<int(int, ...) & noexcept>();
    test_is_not_implicitly_default_constructible<int(int, ...) && noexcept>();
    test_is_not_implicitly_default_constructible<int(int, ...) const noexcept>();
    test_is_not_implicitly_default_constructible<int(int, ...) const & noexcept>();
    test_is_not_implicitly_default_constructible<int(int, ...) const && noexcept>();
    test_is_not_implicitly_default_constructible<int(int, ...) volatile noexcept>();
    test_is_not_implicitly_default_constructible<int(int, ...) volatile & noexcept>();
    test_is_not_implicitly_default_constructible<int(int, ...) volatile && noexcept>();
    test_is_not_implicitly_default_constructible<int(int, ...) const volatile noexcept>();
    test_is_not_implicitly_default_constructible<int(int, ...) const volatile & noexcept>();
    test_is_not_implicitly_default_constructible<int(int, ...) const volatile && noexcept>();

    test_is_implicitly_default_constructible<void (*)()>();
    test_is_implicitly_default_constructible<void (*)() noexcept>();

    test_is_implicitly_default_constructible<void (*)(int)>();
    test_is_implicitly_default_constructible<void (*)(int) noexcept>();

    test_is_implicitly_default_constructible<void (*)(...)>();
    test_is_implicitly_default_constructible<void (*)(...) noexcept>();

    test_is_implicitly_default_constructible<void (*)(int, ...)>();
    test_is_implicitly_default_constructible<void (*)(int, ...) noexcept>();

    test_is_implicitly_default_constructible<int (*)()>();
    test_is_implicitly_default_constructible<int (*)() noexcept>();

    test_is_implicitly_default_constructible<int (*)(int)>();
    test_is_implicitly_default_constructible<int (*)(int) noexcept>();

    test_is_implicitly_default_constructible<int (*)(...)>();
    test_is_implicitly_default_constructible<int (*)(...) noexcept>();

    test_is_implicitly_default_constructible<int (*)(int, ...)>();
    test_is_implicitly_default_constructible<int (*)(int, ...) noexcept>();

    test_is_not_implicitly_default_constructible<void (&)()>();
    test_is_not_implicitly_default_constructible<void (&)() noexcept>();

    test_is_not_implicitly_default_constructible<void (&)(int)>();
    test_is_not_implicitly_default_constructible<void (&)(int) noexcept>();

    test_is_not_implicitly_default_constructible<void (&)(...)>();
    test_is_not_implicitly_default_constructible<void (&)(...) noexcept>();

    test_is_not_implicitly_default_constructible<void (&)(int, ...)>();
    test_is_not_implicitly_default_constructible<void (&)(int, ...) noexcept>();

    test_is_not_implicitly_default_constructible<int (&)()>();
    test_is_not_implicitly_default_constructible<int (&)() noexcept>();

    test_is_not_implicitly_default_constructible<int (&)(int)>();
    test_is_not_implicitly_default_constructible<int (&)(int) noexcept>();

    test_is_not_implicitly_default_constructible<int (&)(...)>();
    test_is_not_implicitly_default_constructible<int (&)(...) noexcept>();

    test_is_not_implicitly_default_constructible<int (&)(int, ...)>();
    test_is_not_implicitly_default_constructible<int (&)(int, ...) noexcept>();

    test_is_not_implicitly_default_constructible<void (&&)()>();
    test_is_not_implicitly_default_constructible<void (&&)() noexcept>();

    test_is_not_implicitly_default_constructible<void (&&)(int)>();
    test_is_not_implicitly_default_constructible<void (&&)(int) noexcept>();

    test_is_not_implicitly_default_constructible<void (&&)(...)>();
    test_is_not_implicitly_default_constructible<void (&&)(...) noexcept>();

    test_is_not_implicitly_default_constructible<void (&&)(int, ...)>();
    test_is_not_implicitly_default_constructible<void (&&)(int, ...) noexcept>();

    test_is_not_implicitly_default_constructible<int (&&)()>();
    test_is_not_implicitly_default_constructible<int (&&)() noexcept>();

    test_is_not_implicitly_default_constructible<int (&&)(int)>();
    test_is_not_implicitly_default_constructible<int (&&)(int) noexcept>();

    test_is_not_implicitly_default_constructible<int (&&)(...)>();
    test_is_not_implicitly_default_constructible<int (&&)(...) noexcept>();

    test_is_not_implicitly_default_constructible<int (&&)(int, ...)>();
    test_is_not_implicitly_default_constructible<int (&&)(int, ...) noexcept>();

    test_is_implicitly_default_constructible<void (class_type::*)()>();
    test_is_implicitly_default_constructible<void (class_type::*)()&>();
    test_is_implicitly_default_constructible<void (class_type::*)() &&>();
    test_is_implicitly_default_constructible<void (class_type::*)() const>();
    test_is_implicitly_default_constructible<void (class_type::*)() const&>();
    test_is_implicitly_default_constructible<void (class_type::*)() const&&>();
    test_is_implicitly_default_constructible<void (class_type::*)() noexcept>();
    test_is_implicitly_default_constructible<void (class_type::*)() & noexcept>();
    test_is_implicitly_default_constructible<void (class_type::*)() && noexcept>();
    test_is_implicitly_default_constructible<void (class_type::*)() const noexcept>();
    test_is_implicitly_default_constructible<void (class_type::*)() const & noexcept>();
    test_is_implicitly_default_constructible<void (class_type::*)() const && noexcept>();

    test_is_implicitly_default_constructible<void (class_type::*)(int)>();
    test_is_implicitly_default_constructible<void (class_type::*)(int)&>();
    test_is_implicitly_default_constructible<void (class_type::*)(int) &&>();
    test_is_implicitly_default_constructible<void (class_type::*)(int) const>();
    test_is_implicitly_default_constructible<void (class_type::*)(int) const&>();
    test_is_implicitly_default_constructible<void (class_type::*)(int) const&&>();
    test_is_implicitly_default_constructible<void (class_type::*)(int) noexcept>();
    test_is_implicitly_default_constructible<void (class_type::*)(int) & noexcept>();
    test_is_implicitly_default_constructible<void (class_type::*)(int) && noexcept>();
    test_is_implicitly_default_constructible<void (class_type::*)(int) const noexcept>();
    test_is_implicitly_default_constructible<void (class_type::*)(int) const & noexcept>();
    test_is_implicitly_default_constructible<void (class_type::*)(int) const && noexcept>();

    test_is_implicitly_default_constructible<void (class_type::*)(...)>();
    test_is_implicitly_default_constructible<void (class_type::*)(...)&>();
    test_is_implicitly_default_constructible<void (class_type::*)(...) &&>();
    test_is_implicitly_default_constructible<void (class_type::*)(...) const>();
    test_is_implicitly_default_constructible<void (class_type::*)(...) const&>();
    test_is_implicitly_default_constructible<void (class_type::*)(...) const&&>();
    test_is_implicitly_default_constructible<void (class_type::*)(...) noexcept>();
    test_is_implicitly_default_constructible<void (class_type::*)(...) & noexcept>();
    test_is_implicitly_default_constructible<void (class_type::*)(...) && noexcept>();
    test_is_implicitly_default_constructible<void (class_type::*)(...) const noexcept>();
    test_is_implicitly_default_constructible<void (class_type::*)(...) const & noexcept>();
    test_is_implicitly_default_constructible<void (class_type::*)(...) const && noexcept>();

    test_is_implicitly_default_constructible<void (class_type::*)(int, ...)>();
    test_is_implicitly_default_constructible<void (class_type::*)(int, ...)&>();
    test_is_implicitly_default_constructible<void (class_type::*)(int, ...) &&>();
    test_is_implicitly_default_constructible<void (class_type::*)(int, ...) const>();
    test_is_implicitly_default_constructible<void (class_type::*)(int, ...) const&>();
    test_is_implicitly_default_constructible<void (class_type::*)(int, ...) const&&>();
    test_is_implicitly_default_constructible<void (class_type::*)(int, ...) noexcept>();
    test_is_implicitly_default_constructible<void (class_type::*)(int, ...) & noexcept>();
    test_is_implicitly_default_constructible<void (class_type::*)(int, ...) && noexcept>();
    test_is_implicitly_default_constructible<void (class_type::*)(int, ...) const noexcept>();
    test_is_implicitly_default_constructible<void (class_type::*)(int, ...) const & noexcept>();
    test_is_implicitly_default_constructible<void (class_type::*)(int, ...) const && noexcept>();

    test_is_implicitly_default_constructible<int (class_type::*)()>();
    test_is_implicitly_default_constructible<int (class_type::*)()&>();
    test_is_implicitly_default_constructible<int (class_type::*)() &&>();
    test_is_implicitly_default_constructible<int (class_type::*)() const>();
    test_is_implicitly_default_constructible<int (class_type::*)() const&>();
    test_is_implicitly_default_constructible<int (class_type::*)() const&&>();
    test_is_implicitly_default_constructible<int (class_type::*)() noexcept>();
    test_is_implicitly_default_constructible<int (class_type::*)() & noexcept>();
    test_is_implicitly_default_constructible<int (class_type::*)() && noexcept>();
    test_is_implicitly_default_constructible<int (class_type::*)() const noexcept>();
    test_is_implicitly_default_constructible<int (class_type::*)() const & noexcept>();
    test_is_implicitly_default_constructible<int (class_type::*)() const && noexcept>();

    test_is_implicitly_default_constructible<int (class_type::*)(int)>();
    test_is_implicitly_default_constructible<int (class_type::*)(int)&>();
    test_is_implicitly_default_constructible<int (class_type::*)(int) &&>();
    test_is_implicitly_default_constructible<int (class_type::*)(int) const>();
    test_is_implicitly_default_constructible<int (class_type::*)(int) const&>();
    test_is_implicitly_default_constructible<int (class_type::*)(int) const&&>();
    test_is_implicitly_default_constructible<int (class_type::*)(int) noexcept>();
    test_is_implicitly_default_constructible<int (class_type::*)(int) & noexcept>();
    test_is_implicitly_default_constructible<int (class_type::*)(int) && noexcept>();
    test_is_implicitly_default_constructible<int (class_type::*)(int) const noexcept>();
    test_is_implicitly_default_constructible<int (class_type::*)(int) const & noexcept>();
    test_is_implicitly_default_constructible<int (class_type::*)(int) const && noexcept>();

    test_is_implicitly_default_constructible<int (class_type::*)(...)>();
    test_is_implicitly_default_constructible<int (class_type::*)(...)&>();
    test_is_implicitly_default_constructible<int (class_type::*)(...) &&>();
    test_is_implicitly_default_constructible<int (class_type::*)(...) const>();
    test_is_implicitly_default_constructible<int (class_type::*)(...) const&>();
    test_is_implicitly_default_constructible<int (class_type::*)(...) const&&>();
    test_is_implicitly_default_constructible<int (class_type::*)(...) noexcept>();
    test_is_implicitly_default_constructible<int (class_type::*)(...) & noexcept>();
    test_is_implicitly_default_constructible<int (class_type::*)(...) && noexcept>();
    test_is_implicitly_default_constructible<int (class_type::*)(...) const noexcept>();
    test_is_implicitly_default_constructible<int (class_type::*)(...) const & noexcept>();
    test_is_implicitly_default_constructible<int (class_type::*)(...) const && noexcept>();

    test_is_implicitly_default_constructible<int (class_type::*)(int, ...)>();
    test_is_implicitly_default_constructible<int (class_type::*)(int, ...)&>();
    test_is_implicitly_default_constructible<int (class_type::*)(int, ...) &&>();
    test_is_implicitly_default_constructible<int (class_type::*)(int, ...) const>();
    test_is_implicitly_default_constructible<int (class_type::*)(int, ...) const&>();
    test_is_implicitly_default_constructible<int (class_type::*)(int, ...) const&&>();
    test_is_implicitly_default_constructible<int (class_type::*)(int, ...) noexcept>();
    test_is_implicitly_default_constructible<int (class_type::*)(int, ...) & noexcept>();
    test_is_implicitly_default_constructible<int (class_type::*)(int, ...) && noexcept>();
    test_is_implicitly_default_constructible<int (class_type::*)(int, ...) const noexcept>();
    test_is_implicitly_default_constructible<int (class_type::*)(int, ...) const & noexcept>();
    test_is_implicitly_default_constructible<int (class_type::*)(int, ...) const && noexcept>();
}
