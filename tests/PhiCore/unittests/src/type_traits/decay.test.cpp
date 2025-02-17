#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/decay.hpp>
#include <type_traits>
#include <vector>

template <typename TypeT, typename ExpectedT = TypeT>
void test_decay()
{
    CHECK_SAME_TYPE(typename phi::decay<TypeT>::type, ExpectedT);
    CHECK_SAME_TYPE(phi::decay_t<TypeT>, ExpectedT);

    // Standard compatiblity
    CHECK_SAME_TYPE(typename std::decay<TypeT>::type, typename phi::decay<TypeT>::type);
    CHECK_SAME_TYPE(typename std::decay<TypeT>::type, ExpectedT);
}

struct A
{};

TEST_CASE("decay")
{
    test_decay<A, A>();
    test_decay<const A, A>();
    test_decay<volatile A, A>();
    test_decay<const volatile A, A>();

    test_decay<int, int>();
    test_decay<const int, int>();
    test_decay<volatile int, int>();
    test_decay<const volatile int, int>();

    test_decay<int*, int*>();
    test_decay<const int*, const int*>();
    test_decay<volatile int*, volatile int*>();
    test_decay<const volatile int*, const volatile int*>();
    test_decay<int[], int*>();
    test_decay<const int[], const int*>();
    test_decay<volatile int[], volatile int*>();
    test_decay<const volatile int[], const volatile int*>();
    test_decay<int[3], int*>();
    test_decay<const int[3], const int*>();
    test_decay<volatile int[3], volatile int*>();
    test_decay<const volatile int[3], const volatile int*>();

    test_decay<int**, int**>();
    test_decay<const int**, const int**>();
    test_decay<volatile int**, volatile int**>();
    test_decay<const volatile int**, const volatile int**>();
    test_decay<int[3][2], int(*)[2]>();
    test_decay<const int[3][2], int const(*)[2]>();
    test_decay<volatile int[3][2], volatile int(*)[2]>();
    test_decay<const volatile int[3][2], const volatile int(*)[2]>();

    test_decay<int&, int>();
    test_decay<const int&, int>();
    test_decay<volatile int&, int>();
    test_decay<const volatile int&, int>();

    test_decay<int&&, int>();
    test_decay<const int&&, int>();
    test_decay<volatile int&&, int>();
    test_decay<const volatile int&&, int>();

    test_decay<void(), void (*)()>();
    test_decay<int(int), int (*)(int)>();
    test_decay<int(int) const, int(int) const>();
    test_decay<int(int) volatile, int(int) volatile>();
    test_decay<int(int)&, int(int)&>();
    test_decay<int(int)&&, int(int) &&>();

    test_decay<void>();
    test_decay<phi::nullptr_t>();
    test_decay<bool>();
    test_decay<char>();
    test_decay<signed char>();
    test_decay<unsigned char>();
    test_decay<short>();
    test_decay<unsigned short>();
    test_decay<int>();
    test_decay<unsigned int>();
    test_decay<long>();
    test_decay<unsigned long>();
    test_decay<long long>();
    test_decay<unsigned long long>();
    test_decay<float>();
    test_decay<double>();
    test_decay<long double>();
    test_decay<char8_t>();
    test_decay<char16_t>();
    test_decay<char32_t>();
    test_decay<wchar_t>();

    test_decay<phi::boolean>();
    test_decay<phi::integer<signed char>>();
    test_decay<phi::integer<unsigned char>>();
    test_decay<phi::integer<short>>();
    test_decay<phi::integer<unsigned short>>();
    test_decay<phi::integer<int>>();
    test_decay<phi::integer<unsigned int>>();
    test_decay<phi::integer<long>>();
    test_decay<phi::integer<unsigned long>>();
    test_decay<phi::integer<long long>>();
    test_decay<phi::integer<unsigned long long>>();
    test_decay<phi::floating_point<float>>();
    test_decay<phi::floating_point<double>>();
    test_decay<phi::floating_point<long double>>();

    test_decay<std::vector<int>>();
    test_decay<phi::scope_ptr<int>>();

    test_decay<int&, int>();
    test_decay<const int&, int>();
    test_decay<volatile int&, int>();
    test_decay<const volatile int&, int>();
    test_decay<int&&, int>();
    test_decay<const int&&, int>();
    test_decay<volatile int&&, int>();
    test_decay<const volatile int&&, int>();
    test_decay<int*>();
    test_decay<const int*>();
    test_decay<volatile int*>();
    test_decay<const volatile int*>();
    test_decay<int**>();
    test_decay<const int**>();
    test_decay<volatile int**>();
    test_decay<const volatile int**>();
    test_decay<int*&, int*>();
    test_decay<const int*&, const int*>();
    test_decay<volatile int*&, volatile int*>();
    test_decay<const volatile int*&, const volatile int*>();
    test_decay<int*&&, int*>();
    test_decay<const int*&&, const int*>();
    test_decay<volatile int*&&, volatile int*>();
    test_decay<const volatile int*&&, const volatile int*>();
    test_decay<void*>();
    test_decay<char[3], char*>();
    test_decay<char[], char*>();
    test_decay<char* [3], char**>();
    test_decay<char*[], char**>();
    test_decay<int(*)[3]>();
    test_decay<int(*)[]>();
    test_decay<int(&)[3], int*>();
    test_decay<int(&)[], int*>();
    test_decay<int(&&)[3], int*>();
    test_decay<int(&&)[], int*>();
    test_decay<char[3][2], char(*)[2]>();
    test_decay<char[][2], char(*)[2]>();
    test_decay<char* [3][2], char*(*)[2]>();
    test_decay<char*[][2], char*(*)[2]>();
    test_decay<int(*)[3][2]>();
    test_decay<int(*)[][2]>();
    test_decay<int(&)[3][2], int(*)[2]>();
    test_decay<int(&)[][2], int(*)[2]>();
    test_decay<int(&&)[3][2], int(*)[2]>();
    test_decay<int(&&)[][2], int(*)[2]>();
    test_decay<class_type>();
    test_decay<class_type[], class_type*>();
    test_decay<class_type[2], class_type*>();
    test_decay<template_type<void>>();
    test_decay<template_type<int>>();
    test_decay<template_type<class_type>>();
    test_decay<template_type<incomplete_type>>();
    test_decay<variadic_template<>>();
    test_decay<variadic_template<void>>();
    test_decay<variadic_template<int>>();
    test_decay<variadic_template<class_type>>();
    test_decay<variadic_template<incomplete_type>>();
    test_decay<variadic_template<int, void, class_type, volatile char[]>>();
    test_decay<public_derived_from<base>>();
    test_decay<public_derived_from<derived>>();
    test_decay<public_derived_from<class_type>>();
    test_decay<private_derived_from<base>>();
    test_decay<private_derived_from<derived>>();
    test_decay<private_derived_from<class_type>>();
    test_decay<protected_derived_from<base>>();
    test_decay<protected_derived_from<derived>>();
    test_decay<protected_derived_from<class_type>>();
    test_decay<union_type>();
    test_decay<non_empty_union>();
    test_decay<empty>();
    test_decay<not_empty>();
    test_decay<bit_zero>();
    test_decay<bit_one>();
    test_decay<base>();
    test_decay<derived>();
    test_decay<abstract>();
    test_decay<public_abstract>();
    test_decay<private_abstract>();
    test_decay<protected_abstract>();
    test_decay<abstract_template<int>>();
    test_decay<abstract_template<double>>();
    test_decay<abstract_template<class_type>>();
    test_decay<abstract_template<incomplete_type>>();
    test_decay<final_type>();
    test_decay<public_destructor>();
    test_decay<protected_destructor>();
    test_decay<private_destructor>();
    test_decay<virtual_public_destructor>();
    test_decay<virtual_protected_destructor>();
    test_decay<virtual_private_destructor>();
    test_decay<pure_public_destructor>();
    test_decay<pure_protected_destructor>();
    test_decay<pure_private_destructor>();
    test_decay<deleted_public_destructor>();
    test_decay<deleted_protected_destructor>();
    test_decay<deleted_private_destructor>();
    test_decay<deleted_virtual_public_destructor>();
    test_decay<deleted_virtual_protected_destructor>();
    test_decay<deleted_virtual_private_destructor>();
    test_decay<Enum>();
    test_decay<EnumSigned>();
    test_decay<EnumUnsigned>();
    test_decay<EnumClass>();
    test_decay<EnumStruct>();
    test_decay<function_type, function_ptr>();
    test_decay<function_ptr>();
    test_decay<member_object_ptr>();
    test_decay<member_function_ptr>();
    test_decay<incomplete_type>();
    test_decay<incomplete_template<void>>();
    test_decay<incomplete_template<int>>();
    test_decay<incomplete_template<class_type>>();
    test_decay<incomplete_template<incomplete_type>>();
    test_decay<incomplete_variadic_template<>>();
    test_decay<incomplete_variadic_template<void>>();
    test_decay<incomplete_variadic_template<int>>();
    test_decay<incomplete_variadic_template<class_type>>();
    test_decay<incomplete_variadic_template<incomplete_type>>();
    test_decay<incomplete_variadic_template<int, void, class_type, volatile char[]>>();
    test_decay<int class_type::*>();
    test_decay<float class_type::*>();
    test_decay<void * class_type::*>();
    test_decay<int * class_type::*>();
    test_decay<int class_type::*&, int class_type::*>();
    test_decay<float class_type::*&, float class_type::*>();
    test_decay<void * class_type::*&, void * class_type::*>();
    test_decay<int * class_type::*&, int * class_type::*>();
    test_decay<int class_type::*&&, int class_type::*>();
    test_decay<float class_type::*&&, float class_type::*>();
    test_decay<void * class_type::*&&, void * class_type::*>();
    test_decay<int * class_type::*&&, int * class_type::*>();
    test_decay<int class_type::* const, int class_type::*>();
    test_decay<float class_type::* const, float class_type::*>();
    test_decay<void * class_type::* const, void * class_type::*>();
    test_decay<int class_type::* const&, int class_type::*>();
    test_decay<float class_type::* const&, float class_type::*>();
    test_decay<void * class_type::* const&, void * class_type::*>();
    test_decay<int class_type::* const&&, int class_type::*>();
    test_decay<float class_type::* const&&, float class_type::*>();
    test_decay<void * class_type::* const&&, void * class_type::*>();
    test_decay<int class_type::* volatile, int class_type::*>();
    test_decay<float class_type::* volatile, float class_type::*>();
    test_decay<void * class_type::* volatile, void * class_type::*>();
    test_decay<int class_type::* volatile&, int class_type::*>();
    test_decay<float class_type::* volatile&, float class_type::*>();
    test_decay<void * class_type::* volatile&, void * class_type::*>();
    test_decay<int class_type::* volatile&&, int class_type::*>();
    test_decay<float class_type::* volatile&&, float class_type::*>();
    test_decay<void * class_type::* volatile&&, void * class_type::*>();
    test_decay<int class_type::* const volatile, int class_type::*>();
    test_decay<float class_type::* const volatile, float class_type::*>();
    test_decay<void * class_type::* const volatile, void * class_type::*>();
    test_decay<int class_type::* const volatile&, int class_type::*>();
    test_decay<float class_type::* const volatile&, float class_type::*>();
    test_decay<void * class_type::* const volatile&, void * class_type::*>();
    test_decay<int class_type::* const volatile&&, int class_type::*>();
    test_decay<float class_type::* const volatile&&, float class_type::*>();
    test_decay<void * class_type::* const volatile&&, void * class_type::*>();
    test_decay<non_copyable>();
    test_decay<non_moveable>();
    test_decay<non_constructible>();
    test_decay<tracked>();
    test_decay<trap_constructible>();
    test_decay<trap_implicit_conversion>();
    test_decay<trap_comma>();
    test_decay<trap_call>();
    test_decay<trap_self_assign>();
    test_decay<trap_deref>();
    test_decay<trap_array_subscript>();

    test_decay<void(), void (*)()>();
    test_decay<void()&>();
    test_decay<void() &&>();
    test_decay<void() const>();
    test_decay<void() const&>();
    test_decay<void() const&&>();
    test_decay<void() volatile>();
    test_decay<void() volatile&>();
    test_decay<void() volatile&&>();
    test_decay<void() const volatile>();
    test_decay<void() const volatile&>();
    test_decay<void() const volatile&&>();
    test_decay<void() noexcept, void (*)() noexcept>();
    test_decay<void() & noexcept>();
    test_decay<void() && noexcept>();
    test_decay<void() const noexcept>();
    test_decay<void() const & noexcept>();
    test_decay<void() const && noexcept>();
    test_decay<void() volatile noexcept>();
    test_decay<void() volatile & noexcept>();
    test_decay<void() volatile && noexcept>();
    test_decay<void() const volatile noexcept>();
    test_decay<void() const volatile & noexcept>();
    test_decay<void() const volatile && noexcept>();

    test_decay<void(int), void (*)(int)>();
    test_decay<void(int)&>();
    test_decay<void(int) &&>();
    test_decay<void(int) const>();
    test_decay<void(int) const&>();
    test_decay<void(int) const&&>();
    test_decay<void(int) volatile>();
    test_decay<void(int) volatile&>();
    test_decay<void(int) volatile&&>();
    test_decay<void(int) const volatile>();
    test_decay<void(int) const volatile&>();
    test_decay<void(int) const volatile&&>();
    test_decay<void(int) noexcept, void (*)(int) noexcept>();
    test_decay<void(int) & noexcept>();
    test_decay<void(int) && noexcept>();
    test_decay<void(int) const noexcept>();
    test_decay<void(int) const & noexcept>();
    test_decay<void(int) const && noexcept>();
    test_decay<void(int) volatile noexcept>();
    test_decay<void(int) volatile & noexcept>();
    test_decay<void(int) volatile && noexcept>();
    test_decay<void(int) const volatile noexcept>();
    test_decay<void(int) const volatile & noexcept>();
    test_decay<void(int) const volatile && noexcept>();

    test_decay<void(...), void (*)(...)>();
    test_decay<void(...)&>();
    test_decay<void(...) &&>();
    test_decay<void(...) const>();
    test_decay<void(...) const&>();
    test_decay<void(...) const&&>();
    test_decay<void(...) volatile>();
    test_decay<void(...) volatile&>();
    test_decay<void(...) volatile&&>();
    test_decay<void(...) const volatile>();
    test_decay<void(...) const volatile&>();
    test_decay<void(...) const volatile&&>();
    test_decay<void(...) noexcept, void (*)(...) noexcept>();
    test_decay<void(...) & noexcept>();
    test_decay<void(...) && noexcept>();
    test_decay<void(...) const noexcept>();
    test_decay<void(...) const & noexcept>();
    test_decay<void(...) const && noexcept>();
    test_decay<void(...) volatile noexcept>();
    test_decay<void(...) volatile & noexcept>();
    test_decay<void(...) volatile && noexcept>();
    test_decay<void(...) const volatile noexcept>();
    test_decay<void(...) const volatile & noexcept>();
    test_decay<void(...) const volatile && noexcept>();

    test_decay<void(int, ...), void (*)(int, ...)>();
    test_decay<void(int, ...)&>();
    test_decay<void(int, ...) &&>();
    test_decay<void(int, ...) const>();
    test_decay<void(int, ...) const&>();
    test_decay<void(int, ...) const&&>();
    test_decay<void(int, ...) volatile>();
    test_decay<void(int, ...) volatile&>();
    test_decay<void(int, ...) volatile&&>();
    test_decay<void(int, ...) const volatile>();
    test_decay<void(int, ...) const volatile&>();
    test_decay<void(int, ...) const volatile&&>();
    test_decay<void(int, ...) noexcept, void (*)(int, ...) noexcept>();
    test_decay<void(int, ...) & noexcept>();
    test_decay<void(int, ...) && noexcept>();
    test_decay<void(int, ...) const noexcept>();
    test_decay<void(int, ...) const & noexcept>();
    test_decay<void(int, ...) const && noexcept>();
    test_decay<void(int, ...) volatile noexcept>();
    test_decay<void(int, ...) volatile & noexcept>();
    test_decay<void(int, ...) volatile && noexcept>();
    test_decay<void(int, ...) const volatile noexcept>();
    test_decay<void(int, ...) const volatile & noexcept>();
    test_decay<void(int, ...) const volatile && noexcept>();

    test_decay<int(), int (*)()>();
    test_decay<int()&>();
    test_decay<int() &&>();
    test_decay<int() const>();
    test_decay<int() const&>();
    test_decay<int() const&&>();
    test_decay<int() volatile>();
    test_decay<int() volatile&>();
    test_decay<int() volatile&&>();
    test_decay<int() const volatile>();
    test_decay<int() const volatile&>();
    test_decay<int() const volatile&&>();
    test_decay<int() noexcept, int (*)() noexcept>();
    test_decay<int() & noexcept>();
    test_decay<int() && noexcept>();
    test_decay<int() const noexcept>();
    test_decay<int() const & noexcept>();
    test_decay<int() const && noexcept>();
    test_decay<int() volatile noexcept>();
    test_decay<int() volatile & noexcept>();
    test_decay<int() volatile && noexcept>();
    test_decay<int() const volatile noexcept>();
    test_decay<int() const volatile & noexcept>();
    test_decay<int() const volatile && noexcept>();

    test_decay<int(int), int (*)(int)>();
    test_decay<int(int)&>();
    test_decay<int(int) &&>();
    test_decay<int(int) const>();
    test_decay<int(int) const&>();
    test_decay<int(int) const&&>();
    test_decay<int(int) volatile>();
    test_decay<int(int) volatile&>();
    test_decay<int(int) volatile&&>();
    test_decay<int(int) const volatile>();
    test_decay<int(int) const volatile&>();
    test_decay<int(int) const volatile&&>();
    test_decay<int(int) noexcept, int (*)(int) noexcept>();
    test_decay<int(int) & noexcept>();
    test_decay<int(int) && noexcept>();
    test_decay<int(int) const noexcept>();
    test_decay<int(int) const & noexcept>();
    test_decay<int(int) const && noexcept>();
    test_decay<int(int) volatile noexcept>();
    test_decay<int(int) volatile & noexcept>();
    test_decay<int(int) volatile && noexcept>();
    test_decay<int(int) const volatile noexcept>();
    test_decay<int(int) const volatile & noexcept>();
    test_decay<int(int) const volatile && noexcept>();

    test_decay<int(...), int (*)(...)>();
    test_decay<int(...)&>();
    test_decay<int(...) &&>();
    test_decay<int(...) const>();
    test_decay<int(...) const&>();
    test_decay<int(...) const&&>();
    test_decay<int(...) volatile>();
    test_decay<int(...) volatile&>();
    test_decay<int(...) volatile&&>();
    test_decay<int(...) const volatile>();
    test_decay<int(...) const volatile&>();
    test_decay<int(...) const volatile&&>();
    test_decay<int(...) noexcept, int (*)(...) noexcept>();
    test_decay<int(...) & noexcept>();
    test_decay<int(...) && noexcept>();
    test_decay<int(...) const noexcept>();
    test_decay<int(...) const & noexcept>();
    test_decay<int(...) const && noexcept>();
    test_decay<int(...) volatile noexcept>();
    test_decay<int(...) volatile & noexcept>();
    test_decay<int(...) volatile && noexcept>();
    test_decay<int(...) const volatile noexcept>();
    test_decay<int(...) const volatile & noexcept>();
    test_decay<int(...) const volatile && noexcept>();

    test_decay<int(int, ...), int (*)(int, ...)>();
    test_decay<int(int, ...)&>();
    test_decay<int(int, ...) &&>();
    test_decay<int(int, ...) const>();
    test_decay<int(int, ...) const&>();
    test_decay<int(int, ...) const&&>();
    test_decay<int(int, ...) volatile>();
    test_decay<int(int, ...) volatile&>();
    test_decay<int(int, ...) volatile&&>();
    test_decay<int(int, ...) const volatile>();
    test_decay<int(int, ...) const volatile&>();
    test_decay<int(int, ...) const volatile&&>();
    test_decay<int(int, ...) noexcept, int (*)(int, ...) noexcept>();
    test_decay<int(int, ...) & noexcept>();
    test_decay<int(int, ...) && noexcept>();
    test_decay<int(int, ...) const noexcept>();
    test_decay<int(int, ...) const & noexcept>();
    test_decay<int(int, ...) const && noexcept>();
    test_decay<int(int, ...) volatile noexcept>();
    test_decay<int(int, ...) volatile & noexcept>();
    test_decay<int(int, ...) volatile && noexcept>();
    test_decay<int(int, ...) const volatile noexcept>();
    test_decay<int(int, ...) const volatile & noexcept>();
    test_decay<int(int, ...) const volatile && noexcept>();

    test_decay<void (*)()>();
    test_decay<void (*)() noexcept>();

    test_decay<void (*)(int)>();
    test_decay<void (*)(int) noexcept>();

    test_decay<void (*)(...)>();
    test_decay<void (*)(...) noexcept>();

    test_decay<void (*)(int, ...)>();
    test_decay<void (*)(int, ...) noexcept>();

    test_decay<int (*)()>();
    test_decay<int (*)() noexcept>();

    test_decay<int (*)(int)>();
    test_decay<int (*)(int) noexcept>();

    test_decay<int (*)(...)>();
    test_decay<int (*)(...) noexcept>();

    test_decay<int (*)(int, ...)>();
    test_decay<int (*)(int, ...) noexcept>();

    test_decay<void (&)(), void (*)()>();
    test_decay<void (&)() noexcept, void (*)() noexcept>();

    test_decay<void (&)(int), void (*)(int)>();
    test_decay<void (&)(int) noexcept, void (*)(int) noexcept>();

    test_decay<void (&)(...), void (*)(...)>();
    test_decay<void (&)(...) noexcept, void (*)(...) noexcept>();

    test_decay<void (&)(int, ...), void (*)(int, ...)>();
    test_decay<void (&)(int, ...) noexcept, void (*)(int, ...) noexcept>();

    test_decay<int (&)(), int (*)()>();
    test_decay<int (&)() noexcept, int (*)() noexcept>();

    test_decay<int (&)(int), int (*)(int)>();
    test_decay<int (&)(int) noexcept, int (*)(int) noexcept>();

    test_decay<int (&)(...), int (*)(...)>();
    test_decay<int (&)(...) noexcept, int (*)(...) noexcept>();

    test_decay<int (&)(int, ...), int (*)(int, ...)>();
    test_decay<int (&)(int, ...) noexcept, int (*)(int, ...) noexcept>();

    test_decay<void (&&)(), void (*)()>();
    test_decay<void (&&)() noexcept, void (*)() noexcept>();

    test_decay<void (&&)(int), void (*)(int)>();
    test_decay<void (&&)(int) noexcept, void (*)(int) noexcept>();

    test_decay<void (&&)(...), void (*)(...)>();
    test_decay<void (&&)(...) noexcept, void (*)(...) noexcept>();

    test_decay<void (&&)(int, ...), void (*)(int, ...)>();
    test_decay<void (&&)(int, ...) noexcept, void (*)(int, ...) noexcept>();

    test_decay<int (&&)(), int (*)()>();
    test_decay<int (&&)() noexcept, int (*)() noexcept>();

    test_decay<int (&&)(int), int (*)(int)>();
    test_decay<int (&&)(int) noexcept, int (*)(int) noexcept>();

    test_decay<int (&&)(...), int (*)(...)>();
    test_decay<int (&&)(...) noexcept, int (*)(...) noexcept>();

    test_decay<int (&&)(int, ...), int (*)(int, ...)>();
    test_decay<int (&&)(int, ...) noexcept, int (*)(int, ...) noexcept>();

    test_decay<void (class_type::*)()>();
    test_decay<void (class_type::*)()&>();
    test_decay<void (class_type::*)() &&>();
    test_decay<void (class_type::*)() const>();
    test_decay<void (class_type::*)() const&>();
    test_decay<void (class_type::*)() const&&>();
    test_decay<void (class_type::*)() noexcept>();
    test_decay<void (class_type::*)() & noexcept>();
    test_decay<void (class_type::*)() && noexcept>();
    test_decay<void (class_type::*)() const noexcept>();
    test_decay<void (class_type::*)() const & noexcept>();
    test_decay<void (class_type::*)() const && noexcept>();

    test_decay<void (class_type::*)(int)>();
    test_decay<void (class_type::*)(int)&>();
    test_decay<void (class_type::*)(int) &&>();
    test_decay<void (class_type::*)(int) const>();
    test_decay<void (class_type::*)(int) const&>();
    test_decay<void (class_type::*)(int) const&&>();
    test_decay<void (class_type::*)(int) noexcept>();
    test_decay<void (class_type::*)(int) & noexcept>();
    test_decay<void (class_type::*)(int) && noexcept>();
    test_decay<void (class_type::*)(int) const noexcept>();
    test_decay<void (class_type::*)(int) const & noexcept>();
    test_decay<void (class_type::*)(int) const && noexcept>();

    test_decay<void (class_type::*)(...)>();
    test_decay<void (class_type::*)(...)&>();
    test_decay<void (class_type::*)(...) &&>();
    test_decay<void (class_type::*)(...) const>();
    test_decay<void (class_type::*)(...) const&>();
    test_decay<void (class_type::*)(...) const&&>();
    test_decay<void (class_type::*)(...) noexcept>();
    test_decay<void (class_type::*)(...) & noexcept>();
    test_decay<void (class_type::*)(...) && noexcept>();
    test_decay<void (class_type::*)(...) const noexcept>();
    test_decay<void (class_type::*)(...) const & noexcept>();
    test_decay<void (class_type::*)(...) const && noexcept>();

    test_decay<void (class_type::*)(int, ...)>();
    test_decay<void (class_type::*)(int, ...)&>();
    test_decay<void (class_type::*)(int, ...) &&>();
    test_decay<void (class_type::*)(int, ...) const>();
    test_decay<void (class_type::*)(int, ...) const&>();
    test_decay<void (class_type::*)(int, ...) const&&>();
    test_decay<void (class_type::*)(int, ...) noexcept>();
    test_decay<void (class_type::*)(int, ...) & noexcept>();
    test_decay<void (class_type::*)(int, ...) && noexcept>();
    test_decay<void (class_type::*)(int, ...) const noexcept>();
    test_decay<void (class_type::*)(int, ...) const & noexcept>();
    test_decay<void (class_type::*)(int, ...) const && noexcept>();

    test_decay<int (class_type::*)()>();
    test_decay<int (class_type::*)()&>();
    test_decay<int (class_type::*)() &&>();
    test_decay<int (class_type::*)() const>();
    test_decay<int (class_type::*)() const&>();
    test_decay<int (class_type::*)() const&&>();
    test_decay<int (class_type::*)() noexcept>();
    test_decay<int (class_type::*)() & noexcept>();
    test_decay<int (class_type::*)() && noexcept>();
    test_decay<int (class_type::*)() const noexcept>();
    test_decay<int (class_type::*)() const & noexcept>();
    test_decay<int (class_type::*)() const && noexcept>();

    test_decay<int (class_type::*)(int)>();
    test_decay<int (class_type::*)(int)&>();
    test_decay<int (class_type::*)(int) &&>();
    test_decay<int (class_type::*)(int) const>();
    test_decay<int (class_type::*)(int) const&>();
    test_decay<int (class_type::*)(int) const&&>();
    test_decay<int (class_type::*)(int) noexcept>();
    test_decay<int (class_type::*)(int) & noexcept>();
    test_decay<int (class_type::*)(int) && noexcept>();
    test_decay<int (class_type::*)(int) const noexcept>();
    test_decay<int (class_type::*)(int) const & noexcept>();
    test_decay<int (class_type::*)(int) const && noexcept>();

    test_decay<int (class_type::*)(...)>();
    test_decay<int (class_type::*)(...)&>();
    test_decay<int (class_type::*)(...) &&>();
    test_decay<int (class_type::*)(...) const>();
    test_decay<int (class_type::*)(...) const&>();
    test_decay<int (class_type::*)(...) const&&>();
    test_decay<int (class_type::*)(...) noexcept>();
    test_decay<int (class_type::*)(...) & noexcept>();
    test_decay<int (class_type::*)(...) && noexcept>();
    test_decay<int (class_type::*)(...) const noexcept>();
    test_decay<int (class_type::*)(...) const & noexcept>();
    test_decay<int (class_type::*)(...) const && noexcept>();

    test_decay<int (class_type::*)(int, ...)>();
    test_decay<int (class_type::*)(int, ...)&>();
    test_decay<int (class_type::*)(int, ...) &&>();
    test_decay<int (class_type::*)(int, ...) const>();
    test_decay<int (class_type::*)(int, ...) const&>();
    test_decay<int (class_type::*)(int, ...) const&&>();
    test_decay<int (class_type::*)(int, ...) noexcept>();
    test_decay<int (class_type::*)(int, ...) & noexcept>();
    test_decay<int (class_type::*)(int, ...) && noexcept>();
    test_decay<int (class_type::*)(int, ...) const noexcept>();
    test_decay<int (class_type::*)(int, ...) const & noexcept>();
    test_decay<int (class_type::*)(int, ...) const && noexcept>();
}
