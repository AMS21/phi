#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/compiler_support/warning.hpp>
#include <phi/core/nullptr_t.hpp>
#include <type_traits>
#include <vector>

PHI_GCC_SUPPRESS_WARNING_PUSH()
PHI_GCC_SUPPRESS_WARNING("-Wnoexcept")

#include <phi/algorithm/swap.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_swappable.hpp>

template <typename TypeT>
void test_is_swappable_impl()
{
    STATIC_REQUIRE(phi::is_swappable<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_swappable<TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_swappable_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_not_swappable_v<TypeT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_swappable<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_swappable<TypeT>);

#if PHI_CPP_STANDARD_IS_ATLEAST(17) && PHI_COMPILER_WORKAROUND(GCC, 7, 0, 0)
    STATIC_REQUIRE(std::is_swappable<TypeT>::value);
#endif
}

template <typename TypeT>
void test_is_not_swappable_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_swappable<TypeT>::value);
    STATIC_REQUIRE(phi::is_not_swappable<TypeT>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_swappable_v<TypeT>);
    STATIC_REQUIRE(phi::is_not_swappable_v<TypeT>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_swappable<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_swappable<TypeT>);

#if PHI_CPP_STANDARD_IS_ATLEAST(17) && PHI_COMPILER_WORKAROUND(GCC, 7, 0, 0)
    STATIC_REQUIRE_FALSE(std::is_swappable<TypeT>::value);
#endif
}

template <typename TypeT>
void test_is_swappable()
{
    test_is_swappable_impl<TypeT>();
    test_is_not_swappable_impl<const TypeT>();
    test_is_not_swappable_impl<volatile TypeT>();
    test_is_not_swappable_impl<const volatile TypeT>();
}

template <typename TypeT>
void test_is_swappable_v()
{
    test_is_swappable_impl<TypeT>();
    test_is_not_swappable_impl<const TypeT>();
    test_is_swappable_impl<volatile TypeT>();
    test_is_not_swappable_impl<const volatile TypeT>();
}

template <typename TypeT>
void test_is_swappable_cv()
{
    test_is_swappable_impl<TypeT>();
    test_is_swappable_impl<const TypeT>();
    test_is_swappable_impl<volatile TypeT>();
    test_is_swappable_impl<const volatile TypeT>();
}

template <typename TypeT>
void test_is_not_swappable()
{
    test_is_not_swappable_impl<TypeT>();
    test_is_not_swappable_impl<const TypeT>();
    test_is_not_swappable_impl<volatile TypeT>();
    test_is_not_swappable_impl<const volatile TypeT>();
}

namespace is_swappable_ns
{
    // Make the test types non-copyable so that generic phi::swap is not valid.
    struct A
    {
        A(A const&)            = delete;
        A& operator=(A const&) = delete;
    };

    struct B
    {
        B(B const&)            = delete;
        B& operator=(B const&) = delete;
    };

    struct C
    {};

    struct D
    {};

    void swap(A&, A&);

    void swap(A&, B&);

    void swap(B&, A&);

    void swap(A&, C&);

    // missing swap(C, A)

    void swap(D&, C&);

    struct M
    {
        M(M const&)            = delete;
        M& operator=(M const&) = delete;
    };

    void swap(M&&, M&&);

    struct DeletedSwap
    {
#if PHI_COMPILER_IS_BELOW(GCC, 5, 0, 0)
        // For some reason gcc before version 5.0 don't compile with the friend declaration...
        void swap(DeletedSwap&, DeletedSwap&) = delete;
#else
        friend void swap(DeletedSwap&, DeletedSwap&) = delete;
#endif
    };

    struct F
    {};

    void swap(F&, F&) = delete;
    void swap(F (&)[5], F (&)[5]);

    struct F2
    {
        friend void swap(F2&, F2&) = delete;
    };

    struct F3
    {
        friend void swap(F3&, F3);
    };
} // namespace is_swappable_ns

namespace is_swappable_ns_2
{
    struct AmbiguousSwap
    {};

    template <typename TypeT>
    void swap(TypeT&, TypeT&);

} // namespace is_swappable_ns_2

TEST_CASE("is_swappable")
{
    using namespace is_swappable_ns;

    // Test that is_swappable applies an lvalue reference to the type.
    test_is_swappable<A>();
    test_is_swappable_cv<A&>();
    test_is_swappable_cv<A&&>();
    test_is_not_swappable<M>();
    test_is_not_swappable<M&>();
    test_is_not_swappable<M&&>();

    test_is_not_swappable<B>();
    test_is_swappable<C>();

    // test non-referencable types
    test_is_not_swappable<void>();
    test_is_not_swappable<int() const>();
    test_is_not_swappable<int()&>();

#if !PHI_COMPILER_IS_BELOW(GCC, 5, 0, 0)
    // test that a deleted swap is correctly handled.
    test_is_not_swappable<DeletedSwap>();
#endif

    // test that a swap with ambiguous overloads is handled correctly.
    test_is_not_swappable_impl<is_swappable_ns_2::AmbiguousSwap>();
    test_is_swappable_impl<const is_swappable_ns_2::AmbiguousSwap>();

    // TODO: The commented out tests currently crash
    test_is_swappable<F3>();
    test_is_swappable<F3[1]>();
    //test_is_not_swappable<F3[1][2]>();
    //test_is_swappable<F3[1][2][3]>();

    test_is_not_swappable<F>();
    //test_is_not_swappable<F[1]>();
    test_is_not_swappable<F[1][2]>();
    test_is_not_swappable<F[1][2][3]>();
    //test_is_not_swappable<F[4]>();
    test_is_not_swappable<F2>();
    //test_is_not_swappable<F2[1]>();
    test_is_not_swappable<F2[1][2]>();
    test_is_not_swappable<F2[1][2][3]>();
    //test_is_not_swappable<F2[4]>();
    //test_is_not_swappable<F2[5]>();

    test_is_not_swappable<void>();
    test_is_swappable_v<phi::nullptr_t>();
    test_is_swappable_v<bool>();
    test_is_swappable_v<char>();
    test_is_swappable_v<signed char>();
    test_is_swappable_v<unsigned char>();
    test_is_swappable_v<short>();
    test_is_swappable_v<unsigned short>();
    test_is_swappable_v<int>();
    test_is_swappable_v<unsigned int>();
    test_is_swappable_v<long>();
    test_is_swappable_v<unsigned long>();
    test_is_swappable_v<long long>();
    test_is_swappable_v<unsigned long long>();
    test_is_swappable_v<float>();
    test_is_swappable_v<double>();
    test_is_swappable_v<long double>();
    test_is_swappable_v<char8_t>();
    test_is_swappable_v<char16_t>();
    test_is_swappable_v<char32_t>();
    test_is_swappable_v<wchar_t>();

    test_is_swappable<phi::boolean>();
    test_is_swappable<phi::integer<signed char>>();
    test_is_swappable<phi::integer<unsigned char>>();
    test_is_swappable<phi::integer<short>>();
    test_is_swappable<phi::integer<unsigned short>>();
    test_is_swappable<phi::integer<int>>();
    test_is_swappable<phi::integer<unsigned int>>();
    test_is_swappable<phi::integer<long>>();
    test_is_swappable<phi::integer<unsigned long>>();
    test_is_swappable<phi::integer<long long>>();
    test_is_swappable<phi::integer<unsigned long long>>();
    test_is_swappable<phi::floating_point<float>>();
    test_is_swappable<phi::floating_point<double>>();
    test_is_swappable<phi::floating_point<long double>>();

#if PHI_COMPILER_IS(MSVC) || PHI_COMPILER_IS(WINCLANG)
    SKIP_CHECK();
#else
    test_is_swappable<std::vector<int>>();
#endif
    test_is_swappable<phi::scope_ptr<int>>();

    test_is_swappable_cv<int&>();
    test_is_not_swappable<const int&>();
    test_is_swappable_cv<volatile int&>();
    test_is_not_swappable<const volatile int&>();
    test_is_swappable_cv<int&&>();
    test_is_not_swappable<const int&&>();
    test_is_swappable_cv<volatile int&&>();
    test_is_not_swappable<const volatile int&&>();
    test_is_swappable_v<int*>();
    test_is_swappable_v<const int*>();
    test_is_swappable_v<volatile int*>();
    test_is_swappable_v<const volatile int*>();
    test_is_swappable_v<int**>();
    test_is_swappable_v<const int**>();
    test_is_swappable_v<volatile int**>();
    test_is_swappable_v<const volatile int**>();
    test_is_swappable_cv<int*&>();
    test_is_swappable_cv<const int*&>();
    test_is_swappable_cv<volatile int*&>();
    test_is_swappable_cv<const volatile int*&>();
    test_is_swappable_cv<int*&&>();
    test_is_swappable_cv<const int*&&>();
    test_is_swappable_cv<volatile int*&&>();
    test_is_swappable_cv<const volatile int*&&>();
    test_is_swappable_v<void*>();
    test_is_swappable_v<char[3]>();
    test_is_swappable_v<char* [3]>();
    test_is_swappable_v<int(*)[3]>();
    test_is_swappable_cv<int(&)[3]>();
    test_is_swappable_cv<int(&&)[3]>();
    //test_is_swappable<char[3][2]>();
    //test_is_swappable<char* [3][2]>();
    test_is_swappable_v<int(*)[3][2]>();
    //test_is_swappable<int(&)[3][2]>();
    //test_is_swappable<int(&&)[3][2]>();
    test_is_swappable<class_type>();
    test_is_swappable<class_type[2]>();
    test_is_swappable<template_type<void>>();
    test_is_swappable<template_type<int>>();
    test_is_swappable<template_type<class_type>>();
    test_is_swappable<variadic_template<>>();
    test_is_swappable<variadic_template<void>>();
    test_is_swappable<variadic_template<int>>();
    test_is_swappable<variadic_template<class_type>>();
    test_is_swappable<variadic_template<int, void, class_type, volatile char[]>>();
    test_is_swappable<public_derived_from<base>>();
    test_is_swappable<public_derived_from<derived>>();
    test_is_swappable<public_derived_from<class_type>>();
    test_is_swappable<private_derived_from<base>>();
    test_is_swappable<private_derived_from<derived>>();
    test_is_swappable<private_derived_from<class_type>>();
    test_is_swappable<protected_derived_from<base>>();
    test_is_swappable<protected_derived_from<derived>>();
    test_is_swappable<protected_derived_from<class_type>>();
    test_is_swappable<union_type>();
    test_is_swappable<non_empty_union>();
    test_is_swappable<empty>();
    test_is_swappable<not_empty>();
    test_is_swappable<bit_zero>();
    test_is_swappable<bit_one>();
    test_is_swappable<base>();
    test_is_swappable<derived>();
    test_is_not_swappable<abstract>();
    test_is_not_swappable<public_abstract>();
    test_is_not_swappable<private_abstract>();
    test_is_not_swappable<protected_abstract>();
    test_is_not_swappable<abstract_template<int>>();
    test_is_swappable<abstract_template<double>>();
    test_is_not_swappable<abstract_template<class_type>>();
    test_is_swappable<final_type>();
    test_is_swappable<public_destructor>();
    test_is_not_swappable<protected_destructor>();
    test_is_not_swappable<private_destructor>();
    test_is_swappable<virtual_public_destructor>();
    test_is_not_swappable<virtual_protected_destructor>();
    test_is_not_swappable<virtual_private_destructor>();
    test_is_not_swappable<pure_public_destructor>();
    test_is_not_swappable<pure_protected_destructor>();
    test_is_not_swappable<pure_private_destructor>();
    test_is_not_swappable<deleted_public_destructor>();
    test_is_not_swappable<deleted_protected_destructor>();
    test_is_not_swappable<deleted_private_destructor>();
    test_is_not_swappable<deleted_virtual_public_destructor>();
    test_is_not_swappable<deleted_virtual_protected_destructor>();
    test_is_not_swappable<deleted_virtual_private_destructor>();
    test_is_swappable_v<Enum>();
    test_is_swappable_v<EnumSigned>();
    test_is_swappable_v<EnumUnsigned>();
    test_is_swappable_v<EnumClass>();
    test_is_swappable_v<EnumStruct>();
    test_is_not_swappable<function_type>();
    test_is_swappable_v<function_ptr>();
    test_is_swappable_v<member_object_ptr>();
    test_is_swappable_v<member_function_ptr>();
    test_is_swappable_v<int class_type::*>();
    test_is_swappable_v<float class_type::*>();
    test_is_swappable_v<void * class_type::*>();
    test_is_swappable_v<int * class_type::*>();
    test_is_swappable_cv<int class_type::*&>();
    test_is_swappable_cv<float class_type::*&>();
    test_is_swappable_cv<void * class_type::*&>();
    test_is_swappable_cv<int * class_type::*&>();
    test_is_swappable_cv<int class_type::*&&>();
    test_is_swappable_cv<float class_type::*&&>();
    test_is_swappable_cv<void * class_type::*&&>();
    test_is_swappable_cv<int * class_type::*&&>();
    test_is_not_swappable<int class_type::*const>();
    test_is_not_swappable<float class_type::*const>();
    test_is_not_swappable<void * class_type::*const>();
    test_is_not_swappable<int class_type::*const&>();
    test_is_not_swappable<float class_type::*const&>();
    test_is_not_swappable<void * class_type::*const&>();
    test_is_not_swappable<int class_type::*const&&>();
    test_is_not_swappable<float class_type::*const&&>();
    test_is_not_swappable<void * class_type::*const&&>();
    test_is_swappable_v<int class_type::*volatile>();
    test_is_swappable_v<float class_type::*volatile>();
    test_is_swappable_v<void * class_type::*volatile>();
    test_is_swappable_cv<int class_type::*volatile&>();
    test_is_swappable_cv<float class_type::*volatile&>();
    test_is_swappable_cv<void * class_type::*volatile&>();
    test_is_swappable_cv<int class_type::*volatile&&>();
    test_is_swappable_cv<float class_type::*volatile&&>();
    test_is_swappable_cv<void * class_type::*volatile&&>();
    test_is_not_swappable<int class_type::*const volatile>();
    test_is_not_swappable<float class_type::*const volatile>();
    test_is_not_swappable<void * class_type::*const volatile>();
    test_is_not_swappable<int class_type::*const volatile&>();
    test_is_not_swappable<float class_type::*const volatile&>();
    test_is_not_swappable<void * class_type::*const volatile&>();
    test_is_not_swappable<int class_type::*const volatile&&>();
    test_is_not_swappable<float class_type::*const volatile&&>();
    test_is_not_swappable<void * class_type::*const volatile&&>();
    test_is_swappable<non_copyable>();
    test_is_not_swappable<non_moveable>();
    test_is_not_swappable<non_constructible>();
    test_is_swappable<tracked>();
    test_is_swappable<trap_constructible>();
    test_is_swappable<trap_implicit_conversion>();
    test_is_swappable<trap_comma>();
    test_is_swappable<trap_call>();
    test_is_swappable<trap_self_assign>();
    test_is_swappable<trap_deref>();
    test_is_swappable<trap_array_subscript>();

    test_is_not_swappable<void()>();
    test_is_not_swappable<void()&>();
    test_is_not_swappable<void() &&>();
    test_is_not_swappable<void() const>();
    test_is_not_swappable<void() const&>();
    test_is_not_swappable<void() const&&>();
    test_is_not_swappable<void() volatile>();
    test_is_not_swappable<void() volatile&>();
    test_is_not_swappable<void() volatile&&>();
    test_is_not_swappable<void() const volatile>();
    test_is_not_swappable<void() const volatile&>();
    test_is_not_swappable<void() const volatile&&>();
    test_is_not_swappable<void() noexcept>();
    test_is_not_swappable<void() & noexcept>();
    test_is_not_swappable<void() && noexcept>();
    test_is_not_swappable<void() const noexcept>();
    test_is_not_swappable<void() const & noexcept>();
    test_is_not_swappable<void() const && noexcept>();
    test_is_not_swappable<void() volatile noexcept>();
    test_is_not_swappable<void() volatile & noexcept>();
    test_is_not_swappable<void() volatile && noexcept>();
    test_is_not_swappable<void() const volatile noexcept>();
    test_is_not_swappable<void() const volatile & noexcept>();
    test_is_not_swappable<void() const volatile && noexcept>();

    test_is_not_swappable<void(int)>();
    test_is_not_swappable<void(int)&>();
    test_is_not_swappable<void(int) &&>();
    test_is_not_swappable<void(int) const>();
    test_is_not_swappable<void(int) const&>();
    test_is_not_swappable<void(int) const&&>();
    test_is_not_swappable<void(int) volatile>();
    test_is_not_swappable<void(int) volatile&>();
    test_is_not_swappable<void(int) volatile&&>();
    test_is_not_swappable<void(int) const volatile>();
    test_is_not_swappable<void(int) const volatile&>();
    test_is_not_swappable<void(int) const volatile&&>();
    test_is_not_swappable<void(int) noexcept>();
    test_is_not_swappable<void(int) & noexcept>();
    test_is_not_swappable<void(int) && noexcept>();
    test_is_not_swappable<void(int) const noexcept>();
    test_is_not_swappable<void(int) const & noexcept>();
    test_is_not_swappable<void(int) const && noexcept>();
    test_is_not_swappable<void(int) volatile noexcept>();
    test_is_not_swappable<void(int) volatile & noexcept>();
    test_is_not_swappable<void(int) volatile && noexcept>();
    test_is_not_swappable<void(int) const volatile noexcept>();
    test_is_not_swappable<void(int) const volatile & noexcept>();
    test_is_not_swappable<void(int) const volatile && noexcept>();

    test_is_not_swappable<void(...)>();
    test_is_not_swappable<void(...)&>();
    test_is_not_swappable<void(...) &&>();
    test_is_not_swappable<void(...) const>();
    test_is_not_swappable<void(...) const&>();
    test_is_not_swappable<void(...) const&&>();
    test_is_not_swappable<void(...) volatile>();
    test_is_not_swappable<void(...) volatile&>();
    test_is_not_swappable<void(...) volatile&&>();
    test_is_not_swappable<void(...) const volatile>();
    test_is_not_swappable<void(...) const volatile&>();
    test_is_not_swappable<void(...) const volatile&&>();
    test_is_not_swappable<void(...) noexcept>();
    test_is_not_swappable<void(...) & noexcept>();
    test_is_not_swappable<void(...) && noexcept>();
    test_is_not_swappable<void(...) const noexcept>();
    test_is_not_swappable<void(...) const & noexcept>();
    test_is_not_swappable<void(...) const && noexcept>();
    test_is_not_swappable<void(...) volatile noexcept>();
    test_is_not_swappable<void(...) volatile & noexcept>();
    test_is_not_swappable<void(...) volatile && noexcept>();
    test_is_not_swappable<void(...) const volatile noexcept>();
    test_is_not_swappable<void(...) const volatile & noexcept>();
    test_is_not_swappable<void(...) const volatile && noexcept>();

    test_is_not_swappable<void(int, ...)>();
    test_is_not_swappable<void(int, ...)&>();
    test_is_not_swappable<void(int, ...) &&>();
    test_is_not_swappable<void(int, ...) const>();
    test_is_not_swappable<void(int, ...) const&>();
    test_is_not_swappable<void(int, ...) const&&>();
    test_is_not_swappable<void(int, ...) volatile>();
    test_is_not_swappable<void(int, ...) volatile&>();
    test_is_not_swappable<void(int, ...) volatile&&>();
    test_is_not_swappable<void(int, ...) const volatile>();
    test_is_not_swappable<void(int, ...) const volatile&>();
    test_is_not_swappable<void(int, ...) const volatile&&>();
    test_is_not_swappable<void(int, ...) noexcept>();
    test_is_not_swappable<void(int, ...) & noexcept>();
    test_is_not_swappable<void(int, ...) && noexcept>();
    test_is_not_swappable<void(int, ...) const noexcept>();
    test_is_not_swappable<void(int, ...) const & noexcept>();
    test_is_not_swappable<void(int, ...) const && noexcept>();
    test_is_not_swappable<void(int, ...) volatile noexcept>();
    test_is_not_swappable<void(int, ...) volatile & noexcept>();
    test_is_not_swappable<void(int, ...) volatile && noexcept>();
    test_is_not_swappable<void(int, ...) const volatile noexcept>();
    test_is_not_swappable<void(int, ...) const volatile & noexcept>();
    test_is_not_swappable<void(int, ...) const volatile && noexcept>();

    test_is_not_swappable<int()>();
    test_is_not_swappable<int()&>();
    test_is_not_swappable<int() &&>();
    test_is_not_swappable<int() const>();
    test_is_not_swappable<int() const&>();
    test_is_not_swappable<int() const&&>();
    test_is_not_swappable<int() volatile>();
    test_is_not_swappable<int() volatile&>();
    test_is_not_swappable<int() volatile&&>();
    test_is_not_swappable<int() const volatile>();
    test_is_not_swappable<int() const volatile&>();
    test_is_not_swappable<int() const volatile&&>();
    test_is_not_swappable<int() noexcept>();
    test_is_not_swappable<int() & noexcept>();
    test_is_not_swappable<int() && noexcept>();
    test_is_not_swappable<int() const noexcept>();
    test_is_not_swappable<int() const & noexcept>();
    test_is_not_swappable<int() const && noexcept>();
    test_is_not_swappable<int() volatile noexcept>();
    test_is_not_swappable<int() volatile & noexcept>();
    test_is_not_swappable<int() volatile && noexcept>();
    test_is_not_swappable<int() const volatile noexcept>();
    test_is_not_swappable<int() const volatile & noexcept>();
    test_is_not_swappable<int() const volatile && noexcept>();

    test_is_not_swappable<int(int)>();
    test_is_not_swappable<int(int)&>();
    test_is_not_swappable<int(int) &&>();
    test_is_not_swappable<int(int) const>();
    test_is_not_swappable<int(int) const&>();
    test_is_not_swappable<int(int) const&&>();
    test_is_not_swappable<int(int) volatile>();
    test_is_not_swappable<int(int) volatile&>();
    test_is_not_swappable<int(int) volatile&&>();
    test_is_not_swappable<int(int) const volatile>();
    test_is_not_swappable<int(int) const volatile&>();
    test_is_not_swappable<int(int) const volatile&&>();
    test_is_not_swappable<int(int) noexcept>();
    test_is_not_swappable<int(int) & noexcept>();
    test_is_not_swappable<int(int) && noexcept>();
    test_is_not_swappable<int(int) const noexcept>();
    test_is_not_swappable<int(int) const & noexcept>();
    test_is_not_swappable<int(int) const && noexcept>();
    test_is_not_swappable<int(int) volatile noexcept>();
    test_is_not_swappable<int(int) volatile & noexcept>();
    test_is_not_swappable<int(int) volatile && noexcept>();
    test_is_not_swappable<int(int) const volatile noexcept>();
    test_is_not_swappable<int(int) const volatile & noexcept>();
    test_is_not_swappable<int(int) const volatile && noexcept>();

    test_is_not_swappable<int(...)>();
    test_is_not_swappable<int(...)&>();
    test_is_not_swappable<int(...) &&>();
    test_is_not_swappable<int(...) const>();
    test_is_not_swappable<int(...) const&>();
    test_is_not_swappable<int(...) const&&>();
    test_is_not_swappable<int(...) volatile>();
    test_is_not_swappable<int(...) volatile&>();
    test_is_not_swappable<int(...) volatile&&>();
    test_is_not_swappable<int(...) const volatile>();
    test_is_not_swappable<int(...) const volatile&>();
    test_is_not_swappable<int(...) const volatile&&>();
    test_is_not_swappable<int(...) noexcept>();
    test_is_not_swappable<int(...) & noexcept>();
    test_is_not_swappable<int(...) && noexcept>();
    test_is_not_swappable<int(...) const noexcept>();
    test_is_not_swappable<int(...) const & noexcept>();
    test_is_not_swappable<int(...) const && noexcept>();
    test_is_not_swappable<int(...) volatile noexcept>();
    test_is_not_swappable<int(...) volatile & noexcept>();
    test_is_not_swappable<int(...) volatile && noexcept>();
    test_is_not_swappable<int(...) const volatile noexcept>();
    test_is_not_swappable<int(...) const volatile & noexcept>();
    test_is_not_swappable<int(...) const volatile && noexcept>();

    test_is_not_swappable<int(int, ...)>();
    test_is_not_swappable<int(int, ...)&>();
    test_is_not_swappable<int(int, ...) &&>();
    test_is_not_swappable<int(int, ...) const>();
    test_is_not_swappable<int(int, ...) const&>();
    test_is_not_swappable<int(int, ...) const&&>();
    test_is_not_swappable<int(int, ...) volatile>();
    test_is_not_swappable<int(int, ...) volatile&>();
    test_is_not_swappable<int(int, ...) volatile&&>();
    test_is_not_swappable<int(int, ...) const volatile>();
    test_is_not_swappable<int(int, ...) const volatile&>();
    test_is_not_swappable<int(int, ...) const volatile&&>();
    test_is_not_swappable<int(int, ...) noexcept>();
    test_is_not_swappable<int(int, ...) & noexcept>();
    test_is_not_swappable<int(int, ...) && noexcept>();
    test_is_not_swappable<int(int, ...) const noexcept>();
    test_is_not_swappable<int(int, ...) const & noexcept>();
    test_is_not_swappable<int(int, ...) const && noexcept>();
    test_is_not_swappable<int(int, ...) volatile noexcept>();
    test_is_not_swappable<int(int, ...) volatile & noexcept>();
    test_is_not_swappable<int(int, ...) volatile && noexcept>();
    test_is_not_swappable<int(int, ...) const volatile noexcept>();
    test_is_not_swappable<int(int, ...) const volatile & noexcept>();
    test_is_not_swappable<int(int, ...) const volatile && noexcept>();

    test_is_swappable_v<void (*)()>();
    test_is_swappable_v<void (*)() noexcept>();

    test_is_swappable_v<void (*)(int)>();
    test_is_swappable_v<void (*)(int) noexcept>();

    test_is_swappable_v<void (*)(...)>();
    test_is_swappable_v<void (*)(...) noexcept>();

    test_is_swappable_v<void (*)(int, ...)>();
    test_is_swappable_v<void (*)(int, ...) noexcept>();

    test_is_swappable_v<int (*)()>();
    test_is_swappable_v<int (*)() noexcept>();

    test_is_swappable_v<int (*)(int)>();
    test_is_swappable_v<int (*)(int) noexcept>();

    test_is_swappable_v<int (*)(...)>();
    test_is_swappable_v<int (*)(...) noexcept>();

    test_is_swappable_v<int (*)(int, ...)>();
    test_is_swappable_v<int (*)(int, ...) noexcept>();

    test_is_not_swappable<void (&)()>();
    test_is_not_swappable<void (&)() noexcept>();

    test_is_not_swappable<void (&)(int)>();
    test_is_not_swappable<void (&)(int) noexcept>();

    test_is_not_swappable<void (&)(...)>();
    test_is_not_swappable<void (&)(...) noexcept>();

    test_is_not_swappable<void (&)(int, ...)>();
    test_is_not_swappable<void (&)(int, ...) noexcept>();

    test_is_not_swappable<int (&)()>();
    test_is_not_swappable<int (&)() noexcept>();

    test_is_not_swappable<int (&)(int)>();
    test_is_not_swappable<int (&)(int) noexcept>();

    test_is_not_swappable<int (&)(...)>();
    test_is_not_swappable<int (&)(...) noexcept>();

    test_is_not_swappable<int (&)(int, ...)>();
    test_is_not_swappable<int (&)(int, ...) noexcept>();

    test_is_not_swappable<void (&&)()>();
    test_is_not_swappable<void (&&)() noexcept>();

    test_is_not_swappable<void (&&)(int)>();
    test_is_not_swappable<void (&&)(int) noexcept>();

    test_is_not_swappable<void (&&)(...)>();
    test_is_not_swappable<void (&&)(...) noexcept>();

    test_is_not_swappable<void (&&)(int, ...)>();
    test_is_not_swappable<void (&&)(int, ...) noexcept>();

    test_is_not_swappable<int (&&)()>();
    test_is_not_swappable<int (&&)() noexcept>();

    test_is_not_swappable<int (&&)(int)>();
    test_is_not_swappable<int (&&)(int) noexcept>();

    test_is_not_swappable<int (&&)(...)>();
    test_is_not_swappable<int (&&)(...) noexcept>();

    test_is_not_swappable<int (&&)(int, ...)>();
    test_is_not_swappable<int (&&)(int, ...) noexcept>();

    test_is_swappable_v<void (class_type::*)()>();
    test_is_swappable_v<void (class_type::*)()&>();
    test_is_swappable_v<void (class_type::*)() &&>();
    test_is_swappable_v<void (class_type::*)() const>();
    test_is_swappable_v<void (class_type::*)() const&>();
    test_is_swappable_v<void (class_type::*)() const&&>();
    test_is_swappable_v<void (class_type::*)() noexcept>();
    test_is_swappable_v<void (class_type::*)() & noexcept>();
    test_is_swappable_v<void (class_type::*)() && noexcept>();
    test_is_swappable_v<void (class_type::*)() const noexcept>();
    test_is_swappable_v<void (class_type::*)() const & noexcept>();
    test_is_swappable_v<void (class_type::*)() const && noexcept>();

    test_is_swappable_v<void (class_type::*)(int)>();
    test_is_swappable_v<void (class_type::*)(int)&>();
    test_is_swappable_v<void (class_type::*)(int) &&>();
    test_is_swappable_v<void (class_type::*)(int) const>();
    test_is_swappable_v<void (class_type::*)(int) const&>();
    test_is_swappable_v<void (class_type::*)(int) const&&>();
    test_is_swappable_v<void (class_type::*)(int) noexcept>();
    test_is_swappable_v<void (class_type::*)(int) & noexcept>();
    test_is_swappable_v<void (class_type::*)(int) && noexcept>();
    test_is_swappable_v<void (class_type::*)(int) const noexcept>();
    test_is_swappable_v<void (class_type::*)(int) const & noexcept>();
    test_is_swappable_v<void (class_type::*)(int) const && noexcept>();

    test_is_swappable_v<void (class_type::*)(...)>();
    test_is_swappable_v<void (class_type::*)(...)&>();
    test_is_swappable_v<void (class_type::*)(...) &&>();
    test_is_swappable_v<void (class_type::*)(...) const>();
    test_is_swappable_v<void (class_type::*)(...) const&>();
    test_is_swappable_v<void (class_type::*)(...) const&&>();
    test_is_swappable_v<void (class_type::*)(...) noexcept>();
    test_is_swappable_v<void (class_type::*)(...) & noexcept>();
    test_is_swappable_v<void (class_type::*)(...) && noexcept>();
    test_is_swappable_v<void (class_type::*)(...) const noexcept>();
    test_is_swappable_v<void (class_type::*)(...) const & noexcept>();
    test_is_swappable_v<void (class_type::*)(...) const && noexcept>();

    test_is_swappable_v<void (class_type::*)(int, ...)>();
    test_is_swappable_v<void (class_type::*)(int, ...)&>();
    test_is_swappable_v<void (class_type::*)(int, ...) &&>();
    test_is_swappable_v<void (class_type::*)(int, ...) const>();
    test_is_swappable_v<void (class_type::*)(int, ...) const&>();
    test_is_swappable_v<void (class_type::*)(int, ...) const&&>();
    test_is_swappable_v<void (class_type::*)(int, ...) noexcept>();
    test_is_swappable_v<void (class_type::*)(int, ...) & noexcept>();
    test_is_swappable_v<void (class_type::*)(int, ...) && noexcept>();
    test_is_swappable_v<void (class_type::*)(int, ...) const noexcept>();
    test_is_swappable_v<void (class_type::*)(int, ...) const & noexcept>();
    test_is_swappable_v<void (class_type::*)(int, ...) const && noexcept>();

    test_is_swappable_v<int (class_type::*)()>();
    test_is_swappable_v<int (class_type::*)()&>();
    test_is_swappable_v<int (class_type::*)() &&>();
    test_is_swappable_v<int (class_type::*)() const>();
    test_is_swappable_v<int (class_type::*)() const&>();
    test_is_swappable_v<int (class_type::*)() const&&>();
    test_is_swappable_v<int (class_type::*)() noexcept>();
    test_is_swappable_v<int (class_type::*)() & noexcept>();
    test_is_swappable_v<int (class_type::*)() && noexcept>();
    test_is_swappable_v<int (class_type::*)() const noexcept>();
    test_is_swappable_v<int (class_type::*)() const & noexcept>();
    test_is_swappable_v<int (class_type::*)() const && noexcept>();

    test_is_swappable_v<int (class_type::*)(int)>();
    test_is_swappable_v<int (class_type::*)(int)&>();
    test_is_swappable_v<int (class_type::*)(int) &&>();
    test_is_swappable_v<int (class_type::*)(int) const>();
    test_is_swappable_v<int (class_type::*)(int) const&>();
    test_is_swappable_v<int (class_type::*)(int) const&&>();
    test_is_swappable_v<int (class_type::*)(int) noexcept>();
    test_is_swappable_v<int (class_type::*)(int) & noexcept>();
    test_is_swappable_v<int (class_type::*)(int) && noexcept>();
    test_is_swappable_v<int (class_type::*)(int) const noexcept>();
    test_is_swappable_v<int (class_type::*)(int) const & noexcept>();
    test_is_swappable_v<int (class_type::*)(int) const && noexcept>();

    test_is_swappable_v<int (class_type::*)(...)>();
    test_is_swappable_v<int (class_type::*)(...)&>();
    test_is_swappable_v<int (class_type::*)(...) &&>();
    test_is_swappable_v<int (class_type::*)(...) const>();
    test_is_swappable_v<int (class_type::*)(...) const&>();
    test_is_swappable_v<int (class_type::*)(...) const&&>();
    test_is_swappable_v<int (class_type::*)(...) noexcept>();
    test_is_swappable_v<int (class_type::*)(...) & noexcept>();
    test_is_swappable_v<int (class_type::*)(...) && noexcept>();
    test_is_swappable_v<int (class_type::*)(...) const noexcept>();
    test_is_swappable_v<int (class_type::*)(...) const & noexcept>();
    test_is_swappable_v<int (class_type::*)(...) const && noexcept>();

    test_is_swappable_v<int (class_type::*)(int, ...)>();
    test_is_swappable_v<int (class_type::*)(int, ...)&>();
    test_is_swappable_v<int (class_type::*)(int, ...) &&>();
    test_is_swappable_v<int (class_type::*)(int, ...) const>();
    test_is_swappable_v<int (class_type::*)(int, ...) const&>();
    test_is_swappable_v<int (class_type::*)(int, ...) const&&>();
    test_is_swappable_v<int (class_type::*)(int, ...) noexcept>();
    test_is_swappable_v<int (class_type::*)(int, ...) & noexcept>();
    test_is_swappable_v<int (class_type::*)(int, ...) && noexcept>();
    test_is_swappable_v<int (class_type::*)(int, ...) const noexcept>();
    test_is_swappable_v<int (class_type::*)(int, ...) const & noexcept>();
    test_is_swappable_v<int (class_type::*)(int, ...) const && noexcept>();
}
