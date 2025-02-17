#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/declval.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/void_t.hpp>
#include <vector>

template <typename TypeT>
void test_void_t()
{
    CHECK_SAME_TYPE(void, phi::void_t<TypeT>);
    CHECK_SAME_TYPE(void, phi::void_t<const TypeT>);
    CHECK_SAME_TYPE(void, phi::void_t<volatile TypeT>);
    CHECK_SAME_TYPE(void, phi::void_t<const volatile TypeT>);
}

template <typename TypeT, typename OtherT>
void test_void_t()
{
    CHECK_SAME_TYPE(void, phi::void_t<TypeT, OtherT>);
    CHECK_SAME_TYPE(void, phi::void_t<TypeT, const OtherT>);
    CHECK_SAME_TYPE(void, phi::void_t<TypeT, volatile OtherT>);
    CHECK_SAME_TYPE(void, phi::void_t<TypeT, const volatile OtherT>);

    CHECK_SAME_TYPE(void, phi::void_t<const TypeT, OtherT>);
    CHECK_SAME_TYPE(void, phi::void_t<const TypeT, const OtherT>);
    CHECK_SAME_TYPE(void, phi::void_t<const TypeT, volatile OtherT>);
    CHECK_SAME_TYPE(void, phi::void_t<const TypeT, const volatile OtherT>);

    CHECK_SAME_TYPE(void, phi::void_t<volatile TypeT, OtherT>);
    CHECK_SAME_TYPE(void, phi::void_t<volatile TypeT, const OtherT>);
    CHECK_SAME_TYPE(void, phi::void_t<volatile TypeT, volatile OtherT>);
    CHECK_SAME_TYPE(void, phi::void_t<volatile TypeT, const volatile OtherT>);

    CHECK_SAME_TYPE(void, phi::void_t<const volatile TypeT, OtherT>);
    CHECK_SAME_TYPE(void, phi::void_t<const volatile TypeT, const OtherT>);
    CHECK_SAME_TYPE(void, phi::void_t<const volatile TypeT, volatile OtherT>);
    CHECK_SAME_TYPE(void, phi::void_t<const volatile TypeT, const volatile OtherT>);
}

struct X
{};

X operator+(const X& val)
{
    return val;
}

template <typename TypeT, typename OtherT = phi::void_t<>>
struct has_unary_plus : public phi::false_type
{};

template <typename TypeT>
struct has_unary_plus<TypeT, phi::void_t<decltype(+phi::declval<X>())>> : public phi::true_type
{};

TEST_CASE("is_void")
{
    STATIC_REQUIRE(has_unary_plus<X>::value);
    CHECK_SAME_TYPE(void, phi::void_t<>);

    test_void_t<void, void>();
    test_void_t<void, void*>();
    test_void_t<void, int>();
    test_void_t<void, double>();
    test_void_t<int, void>();
    test_void_t<double, void>();
    test_void_t<double, int>();
    test_void_t<int&, void>();
    test_void_t<int&, void*>();
    test_void_t<int&, int>();
    test_void_t<int&&, void>();
    test_void_t<int&&, void*>();
    test_void_t<int&&, int>();
    test_void_t<class_type, void>();
    test_void_t<class_type, int>();
    test_void_t<class_type&, void>();
    test_void_t<class_type&, int>();
    test_void_t<class_type&&, void>();
    test_void_t<class_type&&, int>();
    test_void_t<class_type[], void>();
    test_void_t<class_type[], int>();
    test_void_t<class_type[3], void>();
    test_void_t<class_type[3], int>();
    test_void_t<void*, void>();
    test_void_t<void*, void*>();
    test_void_t<void*, int&>();
    test_void_t<void*, int&&>();

    CHECK_SAME_TYPE(void, phi::void_t<int>);
    CHECK_SAME_TYPE(void, phi::void_t<int, int>);
    CHECK_SAME_TYPE(void, phi::void_t<int, int, int>);
    CHECK_SAME_TYPE(void, phi::void_t<int, int, int, int>);
    CHECK_SAME_TYPE(void, phi::void_t<int, int, int, int, int>);
    CHECK_SAME_TYPE(void, phi::void_t<int, int, int, int, int, int>);
    CHECK_SAME_TYPE(void, phi::void_t<int, int, int, int, int, int, int>);
    CHECK_SAME_TYPE(void, phi::void_t<int, int, int, int, int, int, int, int>);
    CHECK_SAME_TYPE(void, phi::void_t<int, int, int, int, int, int, int, int, int>);
    CHECK_SAME_TYPE(void, phi::void_t<int, int, int, int, int, int, int, int, int, int>);
    CHECK_SAME_TYPE(void, phi::void_t<int, double const&, class_type, volatile int[], void>);
    CHECK_SAME_TYPE(void, phi::void_t<int, double const&, class_type, volatile int[], void,
                                      int (*)(double, float)>);

    test_void_t<void>();
    test_void_t<phi::nullptr_t>();
    test_void_t<bool>();
    test_void_t<char>();
    test_void_t<signed char>();
    test_void_t<unsigned char>();
    test_void_t<short>();
    test_void_t<unsigned short>();
    test_void_t<int>();
    test_void_t<unsigned int>();
    test_void_t<long>();
    test_void_t<unsigned long>();
    test_void_t<long long>();
    test_void_t<unsigned long long>();
    test_void_t<float>();
    test_void_t<double>();
    test_void_t<long double>();
    test_void_t<char8_t>();
    test_void_t<char16_t>();
    test_void_t<char32_t>();
    test_void_t<wchar_t>();

    test_void_t<phi::boolean>();
    test_void_t<phi::integer<signed char>>();
    test_void_t<phi::integer<unsigned char>>();
    test_void_t<phi::integer<short>>();
    test_void_t<phi::integer<unsigned short>>();
    test_void_t<phi::integer<int>>();
    test_void_t<phi::integer<unsigned int>>();
    test_void_t<phi::integer<long>>();
    test_void_t<phi::integer<unsigned long>>();
    test_void_t<phi::integer<long long>>();
    test_void_t<phi::integer<unsigned long long>>();
    test_void_t<phi::floating_point<float>>();
    test_void_t<phi::floating_point<double>>();
    test_void_t<phi::floating_point<long double>>();

    test_void_t<std::vector<int>>();
    test_void_t<phi::scope_ptr<int>>();

    test_void_t<int&>();
    test_void_t<const int&>();
    test_void_t<volatile int&>();
    test_void_t<const volatile int&>();
    test_void_t<int&&>();
    test_void_t<const int&&>();
    test_void_t<volatile int&&>();
    test_void_t<const volatile int&&>();
    test_void_t<int*>();
    test_void_t<const int*>();
    test_void_t<volatile int*>();
    test_void_t<const volatile int*>();
    test_void_t<int**>();
    test_void_t<const int**>();
    test_void_t<volatile int**>();
    test_void_t<const volatile int**>();
    test_void_t<int*&>();
    test_void_t<const int*&>();
    test_void_t<volatile int*&>();
    test_void_t<const volatile int*&>();
    test_void_t<int*&&>();
    test_void_t<const int*&&>();
    test_void_t<volatile int*&&>();
    test_void_t<const volatile int*&&>();
    test_void_t<void*>();
    test_void_t<char[3]>();
    test_void_t<char[]>();
    test_void_t<char* [3]>();
    test_void_t<char*[]>();
    test_void_t<int(*)[3]>();
    test_void_t<int(*)[]>();
    test_void_t<int(&)[3]>();
    test_void_t<int(&)[]>();
    test_void_t<int(&&)[3]>();
    test_void_t<int(&&)[]>();
    test_void_t<char[3][2]>();
    test_void_t<char[][2]>();
    test_void_t<char* [3][2]>();
    test_void_t<char*[][2]>();
    test_void_t<int(*)[3][2]>();
    test_void_t<int(*)[][2]>();
    test_void_t<int(&)[3][2]>();
    test_void_t<int(&)[][2]>();
    test_void_t<int(&&)[3][2]>();
    test_void_t<int(&&)[][2]>();
    test_void_t<class_type>();
    test_void_t<class_type[]>();
    test_void_t<class_type[2]>();
    test_void_t<template_type<void>>();
    test_void_t<template_type<int>>();
    test_void_t<template_type<class_type>>();
    test_void_t<template_type<incomplete_type>>();
    test_void_t<variadic_template<>>();
    test_void_t<variadic_template<void>>();
    test_void_t<variadic_template<int>>();
    test_void_t<variadic_template<class_type>>();
    test_void_t<variadic_template<incomplete_type>>();
    test_void_t<variadic_template<int, void, class_type, volatile char[]>>();
    test_void_t<public_derived_from<base>>();
    test_void_t<public_derived_from<derived>>();
    test_void_t<public_derived_from<class_type>>();
    test_void_t<private_derived_from<base>>();
    test_void_t<private_derived_from<derived>>();
    test_void_t<private_derived_from<class_type>>();
    test_void_t<protected_derived_from<base>>();
    test_void_t<protected_derived_from<derived>>();
    test_void_t<protected_derived_from<class_type>>();
    test_void_t<union_type>();
    test_void_t<non_empty_union>();
    test_void_t<empty>();
    test_void_t<not_empty>();
    test_void_t<bit_zero>();
    test_void_t<bit_one>();
    test_void_t<base>();
    test_void_t<derived>();
    test_void_t<abstract>();
    test_void_t<public_abstract>();
    test_void_t<private_abstract>();
    test_void_t<protected_abstract>();
    test_void_t<abstract_template<int>>();
    test_void_t<abstract_template<double>>();
    test_void_t<abstract_template<class_type>>();
    test_void_t<abstract_template<incomplete_type>>();
    test_void_t<final_type>();
    test_void_t<public_destructor>();
    test_void_t<protected_destructor>();
    test_void_t<private_destructor>();
    test_void_t<virtual_public_destructor>();
    test_void_t<virtual_protected_destructor>();
    test_void_t<virtual_private_destructor>();
    test_void_t<pure_public_destructor>();
    test_void_t<pure_protected_destructor>();
    test_void_t<pure_private_destructor>();
    test_void_t<deleted_public_destructor>();
    test_void_t<deleted_protected_destructor>();
    test_void_t<deleted_private_destructor>();
    test_void_t<deleted_virtual_public_destructor>();
    test_void_t<deleted_virtual_protected_destructor>();
    test_void_t<deleted_virtual_private_destructor>();
    test_void_t<Enum>();
    test_void_t<EnumSigned>();
    test_void_t<EnumUnsigned>();
    test_void_t<EnumClass>();
    test_void_t<EnumStruct>();
    test_void_t<function_type>();
    test_void_t<function_ptr>();
    test_void_t<member_object_ptr>();
    test_void_t<member_function_ptr>();
    test_void_t<incomplete_type>();
    test_void_t<incomplete_template<void>>();
    test_void_t<incomplete_template<int>>();
    test_void_t<incomplete_template<class_type>>();
    test_void_t<incomplete_template<incomplete_type>>();
    test_void_t<incomplete_variadic_template<>>();
    test_void_t<incomplete_variadic_template<void>>();
    test_void_t<incomplete_variadic_template<int>>();
    test_void_t<incomplete_variadic_template<class_type>>();
    test_void_t<incomplete_variadic_template<incomplete_type>>();
    test_void_t<incomplete_variadic_template<int, void, class_type, volatile char[]>>();
    test_void_t<int class_type::*>();
    test_void_t<float class_type::*>();
    test_void_t<void * class_type::*>();
    test_void_t<int * class_type::*>();
    test_void_t<int class_type::*&>();
    test_void_t<float class_type::*&>();
    test_void_t<void * class_type::*&>();
    test_void_t<int * class_type::*&>();
    test_void_t<int class_type::*&&>();
    test_void_t<float class_type::*&&>();
    test_void_t<void * class_type::*&&>();
    test_void_t<int * class_type::*&&>();
    test_void_t<int class_type::* const>();
    test_void_t<float class_type::* const>();
    test_void_t<void * class_type::* const>();
    test_void_t<int class_type::* const&>();
    test_void_t<float class_type::* const&>();
    test_void_t<void * class_type::* const&>();
    test_void_t<int class_type::* const&&>();
    test_void_t<float class_type::* const&&>();
    test_void_t<void * class_type::* const&&>();
    test_void_t<int class_type::* volatile>();
    test_void_t<float class_type::* volatile>();
    test_void_t<void * class_type::* volatile>();
    test_void_t<int class_type::* volatile&>();
    test_void_t<float class_type::* volatile&>();
    test_void_t<void * class_type::* volatile&>();
    test_void_t<int class_type::* volatile&&>();
    test_void_t<float class_type::* volatile&&>();
    test_void_t<void * class_type::* volatile&&>();
    test_void_t<int class_type::* const volatile>();
    test_void_t<float class_type::* const volatile>();
    test_void_t<void * class_type::* const volatile>();
    test_void_t<int class_type::* const volatile&>();
    test_void_t<float class_type::* const volatile&>();
    test_void_t<void * class_type::* const volatile&>();
    test_void_t<int class_type::* const volatile&&>();
    test_void_t<float class_type::* const volatile&&>();
    test_void_t<void * class_type::* const volatile&&>();
    test_void_t<non_copyable>();
    test_void_t<non_moveable>();
    test_void_t<non_constructible>();
    test_void_t<tracked>();
    test_void_t<trap_constructible>();
    test_void_t<trap_implicit_conversion>();
    test_void_t<trap_comma>();
    test_void_t<trap_call>();
    test_void_t<trap_self_assign>();
    test_void_t<trap_deref>();
    test_void_t<trap_array_subscript>();

    test_void_t<void()>();
    test_void_t<void()&>();
    test_void_t<void() &&>();
    test_void_t<void() const>();
    test_void_t<void() const&>();
    test_void_t<void() const&&>();
    test_void_t<void() volatile>();
    test_void_t<void() volatile&>();
    test_void_t<void() volatile&&>();
    test_void_t<void() const volatile>();
    test_void_t<void() const volatile&>();
    test_void_t<void() const volatile&&>();
    test_void_t<void() noexcept>();
    test_void_t<void() & noexcept>();
    test_void_t<void() && noexcept>();
    test_void_t<void() const noexcept>();
    test_void_t<void() const & noexcept>();
    test_void_t<void() const && noexcept>();
    test_void_t<void() volatile noexcept>();
    test_void_t<void() volatile & noexcept>();
    test_void_t<void() volatile && noexcept>();
    test_void_t<void() const volatile noexcept>();
    test_void_t<void() const volatile & noexcept>();
    test_void_t<void() const volatile && noexcept>();

    test_void_t<void(int)>();
    test_void_t<void(int)&>();
    test_void_t<void(int) &&>();
    test_void_t<void(int) const>();
    test_void_t<void(int) const&>();
    test_void_t<void(int) const&&>();
    test_void_t<void(int) volatile>();
    test_void_t<void(int) volatile&>();
    test_void_t<void(int) volatile&&>();
    test_void_t<void(int) const volatile>();
    test_void_t<void(int) const volatile&>();
    test_void_t<void(int) const volatile&&>();
    test_void_t<void(int) noexcept>();
    test_void_t<void(int) & noexcept>();
    test_void_t<void(int) && noexcept>();
    test_void_t<void(int) const noexcept>();
    test_void_t<void(int) const & noexcept>();
    test_void_t<void(int) const && noexcept>();
    test_void_t<void(int) volatile noexcept>();
    test_void_t<void(int) volatile & noexcept>();
    test_void_t<void(int) volatile && noexcept>();
    test_void_t<void(int) const volatile noexcept>();
    test_void_t<void(int) const volatile & noexcept>();
    test_void_t<void(int) const volatile && noexcept>();

    test_void_t<void(...)>();
    test_void_t<void(...)&>();
    test_void_t<void(...) &&>();
    test_void_t<void(...) const>();
    test_void_t<void(...) const&>();
    test_void_t<void(...) const&&>();
    test_void_t<void(...) volatile>();
    test_void_t<void(...) volatile&>();
    test_void_t<void(...) volatile&&>();
    test_void_t<void(...) const volatile>();
    test_void_t<void(...) const volatile&>();
    test_void_t<void(...) const volatile&&>();
    test_void_t<void(...) noexcept>();
    test_void_t<void(...) & noexcept>();
    test_void_t<void(...) && noexcept>();
    test_void_t<void(...) const noexcept>();
    test_void_t<void(...) const & noexcept>();
    test_void_t<void(...) const && noexcept>();
    test_void_t<void(...) volatile noexcept>();
    test_void_t<void(...) volatile & noexcept>();
    test_void_t<void(...) volatile && noexcept>();
    test_void_t<void(...) const volatile noexcept>();
    test_void_t<void(...) const volatile & noexcept>();
    test_void_t<void(...) const volatile && noexcept>();

    test_void_t<void(int, ...)>();
    test_void_t<void(int, ...)&>();
    test_void_t<void(int, ...) &&>();
    test_void_t<void(int, ...) const>();
    test_void_t<void(int, ...) const&>();
    test_void_t<void(int, ...) const&&>();
    test_void_t<void(int, ...) volatile>();
    test_void_t<void(int, ...) volatile&>();
    test_void_t<void(int, ...) volatile&&>();
    test_void_t<void(int, ...) const volatile>();
    test_void_t<void(int, ...) const volatile&>();
    test_void_t<void(int, ...) const volatile&&>();
    test_void_t<void(int, ...) noexcept>();
    test_void_t<void(int, ...) & noexcept>();
    test_void_t<void(int, ...) && noexcept>();
    test_void_t<void(int, ...) const noexcept>();
    test_void_t<void(int, ...) const & noexcept>();
    test_void_t<void(int, ...) const && noexcept>();
    test_void_t<void(int, ...) volatile noexcept>();
    test_void_t<void(int, ...) volatile & noexcept>();
    test_void_t<void(int, ...) volatile && noexcept>();
    test_void_t<void(int, ...) const volatile noexcept>();
    test_void_t<void(int, ...) const volatile & noexcept>();
    test_void_t<void(int, ...) const volatile && noexcept>();

    test_void_t<int()>();
    test_void_t<int()&>();
    test_void_t<int() &&>();
    test_void_t<int() const>();
    test_void_t<int() const&>();
    test_void_t<int() const&&>();
    test_void_t<int() volatile>();
    test_void_t<int() volatile&>();
    test_void_t<int() volatile&&>();
    test_void_t<int() const volatile>();
    test_void_t<int() const volatile&>();
    test_void_t<int() const volatile&&>();
    test_void_t<int() noexcept>();
    test_void_t<int() & noexcept>();
    test_void_t<int() && noexcept>();
    test_void_t<int() const noexcept>();
    test_void_t<int() const & noexcept>();
    test_void_t<int() const && noexcept>();
    test_void_t<int() volatile noexcept>();
    test_void_t<int() volatile & noexcept>();
    test_void_t<int() volatile && noexcept>();
    test_void_t<int() const volatile noexcept>();
    test_void_t<int() const volatile & noexcept>();
    test_void_t<int() const volatile && noexcept>();

    test_void_t<int(int)>();
    test_void_t<int(int)&>();
    test_void_t<int(int) &&>();
    test_void_t<int(int) const>();
    test_void_t<int(int) const&>();
    test_void_t<int(int) const&&>();
    test_void_t<int(int) volatile>();
    test_void_t<int(int) volatile&>();
    test_void_t<int(int) volatile&&>();
    test_void_t<int(int) const volatile>();
    test_void_t<int(int) const volatile&>();
    test_void_t<int(int) const volatile&&>();
    test_void_t<int(int) noexcept>();
    test_void_t<int(int) & noexcept>();
    test_void_t<int(int) && noexcept>();
    test_void_t<int(int) const noexcept>();
    test_void_t<int(int) const & noexcept>();
    test_void_t<int(int) const && noexcept>();
    test_void_t<int(int) volatile noexcept>();
    test_void_t<int(int) volatile & noexcept>();
    test_void_t<int(int) volatile && noexcept>();
    test_void_t<int(int) const volatile noexcept>();
    test_void_t<int(int) const volatile & noexcept>();
    test_void_t<int(int) const volatile && noexcept>();

    test_void_t<int(...)>();
    test_void_t<int(...)&>();
    test_void_t<int(...) &&>();
    test_void_t<int(...) const>();
    test_void_t<int(...) const&>();
    test_void_t<int(...) const&&>();
    test_void_t<int(...) volatile>();
    test_void_t<int(...) volatile&>();
    test_void_t<int(...) volatile&&>();
    test_void_t<int(...) const volatile>();
    test_void_t<int(...) const volatile&>();
    test_void_t<int(...) const volatile&&>();
    test_void_t<int(...) noexcept>();
    test_void_t<int(...) & noexcept>();
    test_void_t<int(...) && noexcept>();
    test_void_t<int(...) const noexcept>();
    test_void_t<int(...) const & noexcept>();
    test_void_t<int(...) const && noexcept>();
    test_void_t<int(...) volatile noexcept>();
    test_void_t<int(...) volatile & noexcept>();
    test_void_t<int(...) volatile && noexcept>();
    test_void_t<int(...) const volatile noexcept>();
    test_void_t<int(...) const volatile & noexcept>();
    test_void_t<int(...) const volatile && noexcept>();

    test_void_t<int(int, ...)>();
    test_void_t<int(int, ...)&>();
    test_void_t<int(int, ...) &&>();
    test_void_t<int(int, ...) const>();
    test_void_t<int(int, ...) const&>();
    test_void_t<int(int, ...) const&&>();
    test_void_t<int(int, ...) volatile>();
    test_void_t<int(int, ...) volatile&>();
    test_void_t<int(int, ...) volatile&&>();
    test_void_t<int(int, ...) const volatile>();
    test_void_t<int(int, ...) const volatile&>();
    test_void_t<int(int, ...) const volatile&&>();
    test_void_t<int(int, ...) noexcept>();
    test_void_t<int(int, ...) & noexcept>();
    test_void_t<int(int, ...) && noexcept>();
    test_void_t<int(int, ...) const noexcept>();
    test_void_t<int(int, ...) const & noexcept>();
    test_void_t<int(int, ...) const && noexcept>();
    test_void_t<int(int, ...) volatile noexcept>();
    test_void_t<int(int, ...) volatile & noexcept>();
    test_void_t<int(int, ...) volatile && noexcept>();
    test_void_t<int(int, ...) const volatile noexcept>();
    test_void_t<int(int, ...) const volatile & noexcept>();
    test_void_t<int(int, ...) const volatile && noexcept>();

    test_void_t<void (*)()>();
    test_void_t<void (*)() noexcept>();

    test_void_t<void (*)(int)>();
    test_void_t<void (*)(int) noexcept>();

    test_void_t<void (*)(...)>();
    test_void_t<void (*)(...) noexcept>();

    test_void_t<void (*)(int, ...)>();
    test_void_t<void (*)(int, ...) noexcept>();

    test_void_t<int (*)()>();
    test_void_t<int (*)() noexcept>();

    test_void_t<int (*)(int)>();
    test_void_t<int (*)(int) noexcept>();

    test_void_t<int (*)(...)>();
    test_void_t<int (*)(...) noexcept>();

    test_void_t<int (*)(int, ...)>();
    test_void_t<int (*)(int, ...) noexcept>();

    test_void_t<void (&)()>();
    test_void_t<void (&)() noexcept>();

    test_void_t<void (&)(int)>();
    test_void_t<void (&)(int) noexcept>();

    test_void_t<void (&)(...)>();
    test_void_t<void (&)(...) noexcept>();

    test_void_t<void (&)(int, ...)>();
    test_void_t<void (&)(int, ...) noexcept>();

    test_void_t<int (&)()>();
    test_void_t<int (&)() noexcept>();

    test_void_t<int (&)(int)>();
    test_void_t<int (&)(int) noexcept>();

    test_void_t<int (&)(...)>();
    test_void_t<int (&)(...) noexcept>();

    test_void_t<int (&)(int, ...)>();
    test_void_t<int (&)(int, ...) noexcept>();

    test_void_t<void (&&)()>();
    test_void_t<void (&&)() noexcept>();

    test_void_t<void (&&)(int)>();
    test_void_t<void (&&)(int) noexcept>();

    test_void_t<void (&&)(...)>();
    test_void_t<void (&&)(...) noexcept>();

    test_void_t<void (&&)(int, ...)>();
    test_void_t<void (&&)(int, ...) noexcept>();

    test_void_t<int (&&)()>();
    test_void_t<int (&&)() noexcept>();

    test_void_t<int (&&)(int)>();
    test_void_t<int (&&)(int) noexcept>();

    test_void_t<int (&&)(...)>();
    test_void_t<int (&&)(...) noexcept>();

    test_void_t<int (&&)(int, ...)>();
    test_void_t<int (&&)(int, ...) noexcept>();

    test_void_t<void (class_type::*)()>();
    test_void_t<void (class_type::*)()&>();
    test_void_t<void (class_type::*)() &&>();
    test_void_t<void (class_type::*)() const>();
    test_void_t<void (class_type::*)() const&>();
    test_void_t<void (class_type::*)() const&&>();
    test_void_t<void (class_type::*)() noexcept>();
    test_void_t<void (class_type::*)() & noexcept>();
    test_void_t<void (class_type::*)() && noexcept>();
    test_void_t<void (class_type::*)() const noexcept>();
    test_void_t<void (class_type::*)() const & noexcept>();
    test_void_t<void (class_type::*)() const && noexcept>();

    test_void_t<void (class_type::*)(int)>();
    test_void_t<void (class_type::*)(int)&>();
    test_void_t<void (class_type::*)(int) &&>();
    test_void_t<void (class_type::*)(int) const>();
    test_void_t<void (class_type::*)(int) const&>();
    test_void_t<void (class_type::*)(int) const&&>();
    test_void_t<void (class_type::*)(int) noexcept>();
    test_void_t<void (class_type::*)(int) & noexcept>();
    test_void_t<void (class_type::*)(int) && noexcept>();
    test_void_t<void (class_type::*)(int) const noexcept>();
    test_void_t<void (class_type::*)(int) const & noexcept>();
    test_void_t<void (class_type::*)(int) const && noexcept>();

    test_void_t<void (class_type::*)(...)>();
    test_void_t<void (class_type::*)(...)&>();
    test_void_t<void (class_type::*)(...) &&>();
    test_void_t<void (class_type::*)(...) const>();
    test_void_t<void (class_type::*)(...) const&>();
    test_void_t<void (class_type::*)(...) const&&>();
    test_void_t<void (class_type::*)(...) noexcept>();
    test_void_t<void (class_type::*)(...) & noexcept>();
    test_void_t<void (class_type::*)(...) && noexcept>();
    test_void_t<void (class_type::*)(...) const noexcept>();
    test_void_t<void (class_type::*)(...) const & noexcept>();
    test_void_t<void (class_type::*)(...) const && noexcept>();

    test_void_t<void (class_type::*)(int, ...)>();
    test_void_t<void (class_type::*)(int, ...)&>();
    test_void_t<void (class_type::*)(int, ...) &&>();
    test_void_t<void (class_type::*)(int, ...) const>();
    test_void_t<void (class_type::*)(int, ...) const&>();
    test_void_t<void (class_type::*)(int, ...) const&&>();
    test_void_t<void (class_type::*)(int, ...) noexcept>();
    test_void_t<void (class_type::*)(int, ...) & noexcept>();
    test_void_t<void (class_type::*)(int, ...) && noexcept>();
    test_void_t<void (class_type::*)(int, ...) const noexcept>();
    test_void_t<void (class_type::*)(int, ...) const & noexcept>();
    test_void_t<void (class_type::*)(int, ...) const && noexcept>();

    test_void_t<int (class_type::*)()>();
    test_void_t<int (class_type::*)()&>();
    test_void_t<int (class_type::*)() &&>();
    test_void_t<int (class_type::*)() const>();
    test_void_t<int (class_type::*)() const&>();
    test_void_t<int (class_type::*)() const&&>();
    test_void_t<int (class_type::*)() noexcept>();
    test_void_t<int (class_type::*)() & noexcept>();
    test_void_t<int (class_type::*)() && noexcept>();
    test_void_t<int (class_type::*)() const noexcept>();
    test_void_t<int (class_type::*)() const & noexcept>();
    test_void_t<int (class_type::*)() const && noexcept>();

    test_void_t<int (class_type::*)(int)>();
    test_void_t<int (class_type::*)(int)&>();
    test_void_t<int (class_type::*)(int) &&>();
    test_void_t<int (class_type::*)(int) const>();
    test_void_t<int (class_type::*)(int) const&>();
    test_void_t<int (class_type::*)(int) const&&>();
    test_void_t<int (class_type::*)(int) noexcept>();
    test_void_t<int (class_type::*)(int) & noexcept>();
    test_void_t<int (class_type::*)(int) && noexcept>();
    test_void_t<int (class_type::*)(int) const noexcept>();
    test_void_t<int (class_type::*)(int) const & noexcept>();
    test_void_t<int (class_type::*)(int) const && noexcept>();

    test_void_t<int (class_type::*)(...)>();
    test_void_t<int (class_type::*)(...)&>();
    test_void_t<int (class_type::*)(...) &&>();
    test_void_t<int (class_type::*)(...) const>();
    test_void_t<int (class_type::*)(...) const&>();
    test_void_t<int (class_type::*)(...) const&&>();
    test_void_t<int (class_type::*)(...) noexcept>();
    test_void_t<int (class_type::*)(...) & noexcept>();
    test_void_t<int (class_type::*)(...) && noexcept>();
    test_void_t<int (class_type::*)(...) const noexcept>();
    test_void_t<int (class_type::*)(...) const & noexcept>();
    test_void_t<int (class_type::*)(...) const && noexcept>();

    test_void_t<int (class_type::*)(int, ...)>();
    test_void_t<int (class_type::*)(int, ...)&>();
    test_void_t<int (class_type::*)(int, ...) &&>();
    test_void_t<int (class_type::*)(int, ...) const>();
    test_void_t<int (class_type::*)(int, ...) const&>();
    test_void_t<int (class_type::*)(int, ...) const&&>();
    test_void_t<int (class_type::*)(int, ...) noexcept>();
    test_void_t<int (class_type::*)(int, ...) & noexcept>();
    test_void_t<int (class_type::*)(int, ...) && noexcept>();
    test_void_t<int (class_type::*)(int, ...) const noexcept>();
    test_void_t<int (class_type::*)(int, ...) const & noexcept>();
    test_void_t<int (class_type::*)(int, ...) const && noexcept>();

    // Maximizing coverage data
    X x;
    (void)+x;
}
