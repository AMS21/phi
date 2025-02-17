#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/make_unsafe.hpp>
#include <vector>

template <typename InT, typename OutT = InT>
void test_make_unsafe()
{
    CHECK_SAME_TYPE(typename phi::make_unsafe<InT>::type, OutT);
    CHECK_SAME_TYPE(typename phi::make_unsafe<const InT>::type, const OutT);
    CHECK_SAME_TYPE(typename phi::make_unsafe<volatile InT>::type, volatile OutT);
    CHECK_SAME_TYPE(typename phi::make_unsafe<const volatile InT>::type, const volatile OutT);

    CHECK_SAME_TYPE(typename phi::make_unsafe_t<InT>, OutT);
    CHECK_SAME_TYPE(typename phi::make_unsafe_t<const InT>, const OutT);
    CHECK_SAME_TYPE(typename phi::make_unsafe_t<volatile InT>, volatile OutT);
    CHECK_SAME_TYPE(typename phi::make_unsafe_t<const volatile InT>, const volatile OutT);
}

TEST_CASE("make_unsafe")
{
    test_make_unsafe<void>();
    test_make_unsafe<phi::nullptr_t>();
    test_make_unsafe<bool>();
    test_make_unsafe<char>();
    test_make_unsafe<signed char>();
    test_make_unsafe<unsigned char>();
    test_make_unsafe<short>();
    test_make_unsafe<unsigned short>();
    test_make_unsafe<int>();
    test_make_unsafe<unsigned int>();
    test_make_unsafe<long>();
    test_make_unsafe<unsigned long>();
    test_make_unsafe<long long>();
    test_make_unsafe<unsigned long long>();
    test_make_unsafe<float>();
    test_make_unsafe<double>();
    test_make_unsafe<long double>();
    test_make_unsafe<char8_t>();
    test_make_unsafe<char16_t>();
    test_make_unsafe<char32_t>();
    test_make_unsafe<wchar_t>();

    test_make_unsafe<phi::boolean, bool>();
    test_make_unsafe<phi::integer<signed char>, signed char>();
    test_make_unsafe<phi::integer<unsigned char>, unsigned char>();
    test_make_unsafe<phi::integer<short>, short>();
    test_make_unsafe<phi::integer<unsigned short>, unsigned short>();
    test_make_unsafe<phi::integer<int>, int>();
    test_make_unsafe<phi::integer<unsigned int>, unsigned int>();
    test_make_unsafe<phi::integer<long>, long>();
    test_make_unsafe<phi::integer<unsigned long>, unsigned long>();
    test_make_unsafe<phi::integer<long long>, long long>();
    test_make_unsafe<phi::integer<unsigned long long>, unsigned long long>();
    test_make_unsafe<phi::floating_point<float>, float>();
    test_make_unsafe<phi::floating_point<double>, double>();
    test_make_unsafe<phi::floating_point<long double>, long double>();

    test_make_unsafe<std::vector<int>>();
    test_make_unsafe<phi::scope_ptr<int>>();

    test_make_unsafe<int&>();
    test_make_unsafe<const int&>();
    test_make_unsafe<volatile int&>();
    test_make_unsafe<const volatile int&>();
    test_make_unsafe<int&&>();
    test_make_unsafe<const int&&>();
    test_make_unsafe<volatile int&&>();
    test_make_unsafe<const volatile int&&>();
    test_make_unsafe<int*>();
    test_make_unsafe<const int*>();
    test_make_unsafe<volatile int*>();
    test_make_unsafe<const volatile int*>();
    test_make_unsafe<int**>();
    test_make_unsafe<const int**>();
    test_make_unsafe<volatile int**>();
    test_make_unsafe<const volatile int**>();
    test_make_unsafe<int*&>();
    test_make_unsafe<const int*&>();
    test_make_unsafe<volatile int*&>();
    test_make_unsafe<const volatile int*&>();
    test_make_unsafe<int*&&>();
    test_make_unsafe<const int*&&>();
    test_make_unsafe<volatile int*&&>();
    test_make_unsafe<const volatile int*&&>();
    test_make_unsafe<void*>();
    test_make_unsafe<char[3]>();
    test_make_unsafe<char[]>();
    test_make_unsafe<char* [3]>();
    test_make_unsafe<char*[]>();
    test_make_unsafe<int(*)[3]>();
    test_make_unsafe<int(*)[]>();
    test_make_unsafe<int(&)[3]>();
    test_make_unsafe<int(&)[]>();
    test_make_unsafe<int(&&)[3]>();
    test_make_unsafe<int(&&)[]>();
    test_make_unsafe<char[3][2]>();
    test_make_unsafe<char[][2]>();
    test_make_unsafe<char* [3][2]>();
    test_make_unsafe<char*[][2]>();
    test_make_unsafe<int(*)[3][2]>();
    test_make_unsafe<int(*)[][2]>();
    test_make_unsafe<int(&)[3][2]>();
    test_make_unsafe<int(&)[][2]>();
    test_make_unsafe<int(&&)[3][2]>();
    test_make_unsafe<int(&&)[][2]>();
    test_make_unsafe<class_type>();
    test_make_unsafe<class_type[]>();
    test_make_unsafe<class_type[2]>();
    test_make_unsafe<template_type<void>>();
    test_make_unsafe<template_type<int>>();
    test_make_unsafe<template_type<class_type>>();
    test_make_unsafe<template_type<incomplete_type>>();
    test_make_unsafe<variadic_template<>>();
    test_make_unsafe<variadic_template<void>>();
    test_make_unsafe<variadic_template<int>>();
    test_make_unsafe<variadic_template<class_type>>();
    test_make_unsafe<variadic_template<incomplete_type>>();
    test_make_unsafe<variadic_template<int, void, class_type, volatile char[]>>();
    test_make_unsafe<public_derived_from<base>>();
    test_make_unsafe<public_derived_from<derived>>();
    test_make_unsafe<public_derived_from<class_type>>();
    test_make_unsafe<private_derived_from<base>>();
    test_make_unsafe<private_derived_from<derived>>();
    test_make_unsafe<private_derived_from<class_type>>();
    test_make_unsafe<protected_derived_from<base>>();
    test_make_unsafe<protected_derived_from<derived>>();
    test_make_unsafe<protected_derived_from<class_type>>();
    test_make_unsafe<union_type>();
    test_make_unsafe<non_empty_union>();
    test_make_unsafe<empty>();
    test_make_unsafe<not_empty>();
    test_make_unsafe<bit_zero>();
    test_make_unsafe<bit_one>();
    test_make_unsafe<base>();
    test_make_unsafe<derived>();
    test_make_unsafe<abstract>();
    test_make_unsafe<public_abstract>();
    test_make_unsafe<private_abstract>();
    test_make_unsafe<protected_abstract>();
    test_make_unsafe<abstract_template<int>>();
    test_make_unsafe<abstract_template<double>>();
    test_make_unsafe<abstract_template<class_type>>();
    test_make_unsafe<abstract_template<incomplete_type>>();
    test_make_unsafe<final_type>();
    test_make_unsafe<public_destructor>();
    test_make_unsafe<protected_destructor>();
    test_make_unsafe<private_destructor>();
    test_make_unsafe<virtual_public_destructor>();
    test_make_unsafe<virtual_protected_destructor>();
    test_make_unsafe<virtual_private_destructor>();
    test_make_unsafe<pure_public_destructor>();
    test_make_unsafe<pure_protected_destructor>();
    test_make_unsafe<pure_private_destructor>();
    test_make_unsafe<deleted_public_destructor>();
    test_make_unsafe<deleted_protected_destructor>();
    test_make_unsafe<deleted_private_destructor>();
    test_make_unsafe<deleted_virtual_public_destructor>();
    test_make_unsafe<deleted_virtual_protected_destructor>();
    test_make_unsafe<deleted_virtual_private_destructor>();
    test_make_unsafe<Enum>();
    test_make_unsafe<EnumSigned>();
    test_make_unsafe<EnumUnsigned>();
    test_make_unsafe<EnumClass>();
    test_make_unsafe<EnumStruct>();
    test_make_unsafe<function_type>();
    test_make_unsafe<function_ptr>();
    test_make_unsafe<member_object_ptr>();
    test_make_unsafe<member_function_ptr>();
    test_make_unsafe<incomplete_type>();
    test_make_unsafe<incomplete_template<void>>();
    test_make_unsafe<incomplete_template<int>>();
    test_make_unsafe<incomplete_template<class_type>>();
    test_make_unsafe<incomplete_template<incomplete_type>>();
    test_make_unsafe<incomplete_variadic_template<>>();
    test_make_unsafe<incomplete_variadic_template<void>>();
    test_make_unsafe<incomplete_variadic_template<int>>();
    test_make_unsafe<incomplete_variadic_template<class_type>>();
    test_make_unsafe<incomplete_variadic_template<incomplete_type>>();
    test_make_unsafe<incomplete_variadic_template<int, void, class_type, volatile char[]>>();
    test_make_unsafe<int class_type::*>();
    test_make_unsafe<float class_type::*>();
    test_make_unsafe<void * class_type::*>();
    test_make_unsafe<int * class_type::*>();
    test_make_unsafe<int class_type::*&>();
    test_make_unsafe<float class_type::*&>();
    test_make_unsafe<void * class_type::*&>();
    test_make_unsafe<int * class_type::*&>();
    test_make_unsafe<int class_type::*&&>();
    test_make_unsafe<float class_type::*&&>();
    test_make_unsafe<void * class_type::*&&>();
    test_make_unsafe<int * class_type::*&&>();
    test_make_unsafe<int class_type::* const>();
    test_make_unsafe<float class_type::* const>();
    test_make_unsafe<void * class_type::* const>();
    test_make_unsafe<int class_type::* const&>();
    test_make_unsafe<float class_type::* const&>();
    test_make_unsafe<void * class_type::* const&>();
    test_make_unsafe<int class_type::* const&&>();
    test_make_unsafe<float class_type::* const&&>();
    test_make_unsafe<void * class_type::* const&&>();
    test_make_unsafe<int class_type::* volatile>();
    test_make_unsafe<float class_type::* volatile>();
    test_make_unsafe<void * class_type::* volatile>();
    test_make_unsafe<int class_type::* volatile&>();
    test_make_unsafe<float class_type::* volatile&>();
    test_make_unsafe<void * class_type::* volatile&>();
    test_make_unsafe<int class_type::* volatile&&>();
    test_make_unsafe<float class_type::* volatile&&>();
    test_make_unsafe<void * class_type::* volatile&&>();
    test_make_unsafe<int class_type::* const volatile>();
    test_make_unsafe<float class_type::* const volatile>();
    test_make_unsafe<void * class_type::* const volatile>();
    test_make_unsafe<int class_type::* const volatile&>();
    test_make_unsafe<float class_type::* const volatile&>();
    test_make_unsafe<void * class_type::* const volatile&>();
    test_make_unsafe<int class_type::* const volatile&&>();
    test_make_unsafe<float class_type::* const volatile&&>();
    test_make_unsafe<void * class_type::* const volatile&&>();
    test_make_unsafe<non_copyable>();
    test_make_unsafe<non_moveable>();
    test_make_unsafe<non_constructible>();
    test_make_unsafe<tracked>();
    test_make_unsafe<trap_constructible>();
    test_make_unsafe<trap_implicit_conversion>();
    test_make_unsafe<trap_comma>();
    test_make_unsafe<trap_call>();
    test_make_unsafe<trap_self_assign>();
    test_make_unsafe<trap_deref>();
    test_make_unsafe<trap_array_subscript>();

    test_make_unsafe<void()>();
    test_make_unsafe<void()&>();
    test_make_unsafe<void() &&>();
    test_make_unsafe<void() const>();
    test_make_unsafe<void() const&>();
    test_make_unsafe<void() const&&>();
    test_make_unsafe<void() volatile>();
    test_make_unsafe<void() volatile&>();
    test_make_unsafe<void() volatile&&>();
    test_make_unsafe<void() const volatile>();
    test_make_unsafe<void() const volatile&>();
    test_make_unsafe<void() const volatile&&>();
    test_make_unsafe<void() noexcept>();
    test_make_unsafe<void() & noexcept>();
    test_make_unsafe<void() && noexcept>();
    test_make_unsafe<void() const noexcept>();
    test_make_unsafe<void() const & noexcept>();
    test_make_unsafe<void() const && noexcept>();
    test_make_unsafe<void() volatile noexcept>();
    test_make_unsafe<void() volatile & noexcept>();
    test_make_unsafe<void() volatile && noexcept>();
    test_make_unsafe<void() const volatile noexcept>();
    test_make_unsafe<void() const volatile & noexcept>();
    test_make_unsafe<void() const volatile && noexcept>();

    test_make_unsafe<void(int)>();
    test_make_unsafe<void(int)&>();
    test_make_unsafe<void(int) &&>();
    test_make_unsafe<void(int) const>();
    test_make_unsafe<void(int) const&>();
    test_make_unsafe<void(int) const&&>();
    test_make_unsafe<void(int) volatile>();
    test_make_unsafe<void(int) volatile&>();
    test_make_unsafe<void(int) volatile&&>();
    test_make_unsafe<void(int) const volatile>();
    test_make_unsafe<void(int) const volatile&>();
    test_make_unsafe<void(int) const volatile&&>();
    test_make_unsafe<void(int) noexcept>();
    test_make_unsafe<void(int) & noexcept>();
    test_make_unsafe<void(int) && noexcept>();
    test_make_unsafe<void(int) const noexcept>();
    test_make_unsafe<void(int) const & noexcept>();
    test_make_unsafe<void(int) const && noexcept>();
    test_make_unsafe<void(int) volatile noexcept>();
    test_make_unsafe<void(int) volatile & noexcept>();
    test_make_unsafe<void(int) volatile && noexcept>();
    test_make_unsafe<void(int) const volatile noexcept>();
    test_make_unsafe<void(int) const volatile & noexcept>();
    test_make_unsafe<void(int) const volatile && noexcept>();

    test_make_unsafe<void(...)>();
    test_make_unsafe<void(...)&>();
    test_make_unsafe<void(...) &&>();
    test_make_unsafe<void(...) const>();
    test_make_unsafe<void(...) const&>();
    test_make_unsafe<void(...) const&&>();
    test_make_unsafe<void(...) volatile>();
    test_make_unsafe<void(...) volatile&>();
    test_make_unsafe<void(...) volatile&&>();
    test_make_unsafe<void(...) const volatile>();
    test_make_unsafe<void(...) const volatile&>();
    test_make_unsafe<void(...) const volatile&&>();
    test_make_unsafe<void(...) noexcept>();
    test_make_unsafe<void(...) & noexcept>();
    test_make_unsafe<void(...) && noexcept>();
    test_make_unsafe<void(...) const noexcept>();
    test_make_unsafe<void(...) const & noexcept>();
    test_make_unsafe<void(...) const && noexcept>();
    test_make_unsafe<void(...) volatile noexcept>();
    test_make_unsafe<void(...) volatile & noexcept>();
    test_make_unsafe<void(...) volatile && noexcept>();
    test_make_unsafe<void(...) const volatile noexcept>();
    test_make_unsafe<void(...) const volatile & noexcept>();
    test_make_unsafe<void(...) const volatile && noexcept>();

    test_make_unsafe<void(int, ...)>();
    test_make_unsafe<void(int, ...)&>();
    test_make_unsafe<void(int, ...) &&>();
    test_make_unsafe<void(int, ...) const>();
    test_make_unsafe<void(int, ...) const&>();
    test_make_unsafe<void(int, ...) const&&>();
    test_make_unsafe<void(int, ...) volatile>();
    test_make_unsafe<void(int, ...) volatile&>();
    test_make_unsafe<void(int, ...) volatile&&>();
    test_make_unsafe<void(int, ...) const volatile>();
    test_make_unsafe<void(int, ...) const volatile&>();
    test_make_unsafe<void(int, ...) const volatile&&>();
    test_make_unsafe<void(int, ...) noexcept>();
    test_make_unsafe<void(int, ...) & noexcept>();
    test_make_unsafe<void(int, ...) && noexcept>();
    test_make_unsafe<void(int, ...) const noexcept>();
    test_make_unsafe<void(int, ...) const & noexcept>();
    test_make_unsafe<void(int, ...) const && noexcept>();
    test_make_unsafe<void(int, ...) volatile noexcept>();
    test_make_unsafe<void(int, ...) volatile & noexcept>();
    test_make_unsafe<void(int, ...) volatile && noexcept>();
    test_make_unsafe<void(int, ...) const volatile noexcept>();
    test_make_unsafe<void(int, ...) const volatile & noexcept>();
    test_make_unsafe<void(int, ...) const volatile && noexcept>();

    test_make_unsafe<int()>();
    test_make_unsafe<int()&>();
    test_make_unsafe<int() &&>();
    test_make_unsafe<int() const>();
    test_make_unsafe<int() const&>();
    test_make_unsafe<int() const&&>();
    test_make_unsafe<int() volatile>();
    test_make_unsafe<int() volatile&>();
    test_make_unsafe<int() volatile&&>();
    test_make_unsafe<int() const volatile>();
    test_make_unsafe<int() const volatile&>();
    test_make_unsafe<int() const volatile&&>();
    test_make_unsafe<int() noexcept>();
    test_make_unsafe<int() & noexcept>();
    test_make_unsafe<int() && noexcept>();
    test_make_unsafe<int() const noexcept>();
    test_make_unsafe<int() const & noexcept>();
    test_make_unsafe<int() const && noexcept>();
    test_make_unsafe<int() volatile noexcept>();
    test_make_unsafe<int() volatile & noexcept>();
    test_make_unsafe<int() volatile && noexcept>();
    test_make_unsafe<int() const volatile noexcept>();
    test_make_unsafe<int() const volatile & noexcept>();
    test_make_unsafe<int() const volatile && noexcept>();

    test_make_unsafe<int(int)>();
    test_make_unsafe<int(int)&>();
    test_make_unsafe<int(int) &&>();
    test_make_unsafe<int(int) const>();
    test_make_unsafe<int(int) const&>();
    test_make_unsafe<int(int) const&&>();
    test_make_unsafe<int(int) volatile>();
    test_make_unsafe<int(int) volatile&>();
    test_make_unsafe<int(int) volatile&&>();
    test_make_unsafe<int(int) const volatile>();
    test_make_unsafe<int(int) const volatile&>();
    test_make_unsafe<int(int) const volatile&&>();
    test_make_unsafe<int(int) noexcept>();
    test_make_unsafe<int(int) & noexcept>();
    test_make_unsafe<int(int) && noexcept>();
    test_make_unsafe<int(int) const noexcept>();
    test_make_unsafe<int(int) const & noexcept>();
    test_make_unsafe<int(int) const && noexcept>();
    test_make_unsafe<int(int) volatile noexcept>();
    test_make_unsafe<int(int) volatile & noexcept>();
    test_make_unsafe<int(int) volatile && noexcept>();
    test_make_unsafe<int(int) const volatile noexcept>();
    test_make_unsafe<int(int) const volatile & noexcept>();
    test_make_unsafe<int(int) const volatile && noexcept>();

    test_make_unsafe<int(...)>();
    test_make_unsafe<int(...)&>();
    test_make_unsafe<int(...) &&>();
    test_make_unsafe<int(...) const>();
    test_make_unsafe<int(...) const&>();
    test_make_unsafe<int(...) const&&>();
    test_make_unsafe<int(...) volatile>();
    test_make_unsafe<int(...) volatile&>();
    test_make_unsafe<int(...) volatile&&>();
    test_make_unsafe<int(...) const volatile>();
    test_make_unsafe<int(...) const volatile&>();
    test_make_unsafe<int(...) const volatile&&>();
    test_make_unsafe<int(...) noexcept>();
    test_make_unsafe<int(...) & noexcept>();
    test_make_unsafe<int(...) && noexcept>();
    test_make_unsafe<int(...) const noexcept>();
    test_make_unsafe<int(...) const & noexcept>();
    test_make_unsafe<int(...) const && noexcept>();
    test_make_unsafe<int(...) volatile noexcept>();
    test_make_unsafe<int(...) volatile & noexcept>();
    test_make_unsafe<int(...) volatile && noexcept>();
    test_make_unsafe<int(...) const volatile noexcept>();
    test_make_unsafe<int(...) const volatile & noexcept>();
    test_make_unsafe<int(...) const volatile && noexcept>();

    test_make_unsafe<int(int, ...)>();
    test_make_unsafe<int(int, ...)&>();
    test_make_unsafe<int(int, ...) &&>();
    test_make_unsafe<int(int, ...) const>();
    test_make_unsafe<int(int, ...) const&>();
    test_make_unsafe<int(int, ...) const&&>();
    test_make_unsafe<int(int, ...) volatile>();
    test_make_unsafe<int(int, ...) volatile&>();
    test_make_unsafe<int(int, ...) volatile&&>();
    test_make_unsafe<int(int, ...) const volatile>();
    test_make_unsafe<int(int, ...) const volatile&>();
    test_make_unsafe<int(int, ...) const volatile&&>();
    test_make_unsafe<int(int, ...) noexcept>();
    test_make_unsafe<int(int, ...) & noexcept>();
    test_make_unsafe<int(int, ...) && noexcept>();
    test_make_unsafe<int(int, ...) const noexcept>();
    test_make_unsafe<int(int, ...) const & noexcept>();
    test_make_unsafe<int(int, ...) const && noexcept>();
    test_make_unsafe<int(int, ...) volatile noexcept>();
    test_make_unsafe<int(int, ...) volatile & noexcept>();
    test_make_unsafe<int(int, ...) volatile && noexcept>();
    test_make_unsafe<int(int, ...) const volatile noexcept>();
    test_make_unsafe<int(int, ...) const volatile & noexcept>();
    test_make_unsafe<int(int, ...) const volatile && noexcept>();

    test_make_unsafe<void (*)()>();
    test_make_unsafe<void (*)() noexcept>();

    test_make_unsafe<void (*)(int)>();
    test_make_unsafe<void (*)(int) noexcept>();

    test_make_unsafe<void (*)(...)>();
    test_make_unsafe<void (*)(...) noexcept>();

    test_make_unsafe<void (*)(int, ...)>();
    test_make_unsafe<void (*)(int, ...) noexcept>();

    test_make_unsafe<int (*)()>();
    test_make_unsafe<int (*)() noexcept>();

    test_make_unsafe<int (*)(int)>();
    test_make_unsafe<int (*)(int) noexcept>();

    test_make_unsafe<int (*)(...)>();
    test_make_unsafe<int (*)(...) noexcept>();

    test_make_unsafe<int (*)(int, ...)>();
    test_make_unsafe<int (*)(int, ...) noexcept>();

    test_make_unsafe<void (&)()>();
    test_make_unsafe<void (&)() noexcept>();

    test_make_unsafe<void (&)(int)>();
    test_make_unsafe<void (&)(int) noexcept>();

    test_make_unsafe<void (&)(...)>();
    test_make_unsafe<void (&)(...) noexcept>();

    test_make_unsafe<void (&)(int, ...)>();
    test_make_unsafe<void (&)(int, ...) noexcept>();

    test_make_unsafe<int (&)()>();
    test_make_unsafe<int (&)() noexcept>();

    test_make_unsafe<int (&)(int)>();
    test_make_unsafe<int (&)(int) noexcept>();

    test_make_unsafe<int (&)(...)>();
    test_make_unsafe<int (&)(...) noexcept>();

    test_make_unsafe<int (&)(int, ...)>();
    test_make_unsafe<int (&)(int, ...) noexcept>();

    test_make_unsafe<void (&&)()>();
    test_make_unsafe<void (&&)() noexcept>();

    test_make_unsafe<void (&&)(int)>();
    test_make_unsafe<void (&&)(int) noexcept>();

    test_make_unsafe<void (&&)(...)>();
    test_make_unsafe<void (&&)(...) noexcept>();

    test_make_unsafe<void (&&)(int, ...)>();
    test_make_unsafe<void (&&)(int, ...) noexcept>();

    test_make_unsafe<int (&&)()>();
    test_make_unsafe<int (&&)() noexcept>();

    test_make_unsafe<int (&&)(int)>();
    test_make_unsafe<int (&&)(int) noexcept>();

    test_make_unsafe<int (&&)(...)>();
    test_make_unsafe<int (&&)(...) noexcept>();

    test_make_unsafe<int (&&)(int, ...)>();
    test_make_unsafe<int (&&)(int, ...) noexcept>();

    test_make_unsafe<void (class_type::*)()>();
    test_make_unsafe<void (class_type::*)()&>();
    test_make_unsafe<void (class_type::*)() &&>();
    test_make_unsafe<void (class_type::*)() const>();
    test_make_unsafe<void (class_type::*)() const&>();
    test_make_unsafe<void (class_type::*)() const&&>();
    test_make_unsafe<void (class_type::*)() noexcept>();
    test_make_unsafe<void (class_type::*)() & noexcept>();
    test_make_unsafe<void (class_type::*)() && noexcept>();
    test_make_unsafe<void (class_type::*)() const noexcept>();
    test_make_unsafe<void (class_type::*)() const & noexcept>();
    test_make_unsafe<void (class_type::*)() const && noexcept>();

    test_make_unsafe<void (class_type::*)(int)>();
    test_make_unsafe<void (class_type::*)(int)&>();
    test_make_unsafe<void (class_type::*)(int) &&>();
    test_make_unsafe<void (class_type::*)(int) const>();
    test_make_unsafe<void (class_type::*)(int) const&>();
    test_make_unsafe<void (class_type::*)(int) const&&>();
    test_make_unsafe<void (class_type::*)(int) noexcept>();
    test_make_unsafe<void (class_type::*)(int) & noexcept>();
    test_make_unsafe<void (class_type::*)(int) && noexcept>();
    test_make_unsafe<void (class_type::*)(int) const noexcept>();
    test_make_unsafe<void (class_type::*)(int) const & noexcept>();
    test_make_unsafe<void (class_type::*)(int) const && noexcept>();

    test_make_unsafe<void (class_type::*)(...)>();
    test_make_unsafe<void (class_type::*)(...)&>();
    test_make_unsafe<void (class_type::*)(...) &&>();
    test_make_unsafe<void (class_type::*)(...) const>();
    test_make_unsafe<void (class_type::*)(...) const&>();
    test_make_unsafe<void (class_type::*)(...) const&&>();
    test_make_unsafe<void (class_type::*)(...) noexcept>();
    test_make_unsafe<void (class_type::*)(...) & noexcept>();
    test_make_unsafe<void (class_type::*)(...) && noexcept>();
    test_make_unsafe<void (class_type::*)(...) const noexcept>();
    test_make_unsafe<void (class_type::*)(...) const & noexcept>();
    test_make_unsafe<void (class_type::*)(...) const && noexcept>();

    test_make_unsafe<void (class_type::*)(int, ...)>();
    test_make_unsafe<void (class_type::*)(int, ...)&>();
    test_make_unsafe<void (class_type::*)(int, ...) &&>();
    test_make_unsafe<void (class_type::*)(int, ...) const>();
    test_make_unsafe<void (class_type::*)(int, ...) const&>();
    test_make_unsafe<void (class_type::*)(int, ...) const&&>();
    test_make_unsafe<void (class_type::*)(int, ...) noexcept>();
    test_make_unsafe<void (class_type::*)(int, ...) & noexcept>();
    test_make_unsafe<void (class_type::*)(int, ...) && noexcept>();
    test_make_unsafe<void (class_type::*)(int, ...) const noexcept>();
    test_make_unsafe<void (class_type::*)(int, ...) const & noexcept>();
    test_make_unsafe<void (class_type::*)(int, ...) const && noexcept>();

    test_make_unsafe<int (class_type::*)()>();
    test_make_unsafe<int (class_type::*)()&>();
    test_make_unsafe<int (class_type::*)() &&>();
    test_make_unsafe<int (class_type::*)() const>();
    test_make_unsafe<int (class_type::*)() const&>();
    test_make_unsafe<int (class_type::*)() const&&>();
    test_make_unsafe<int (class_type::*)() noexcept>();
    test_make_unsafe<int (class_type::*)() & noexcept>();
    test_make_unsafe<int (class_type::*)() && noexcept>();
    test_make_unsafe<int (class_type::*)() const noexcept>();
    test_make_unsafe<int (class_type::*)() const & noexcept>();
    test_make_unsafe<int (class_type::*)() const && noexcept>();

    test_make_unsafe<int (class_type::*)(int)>();
    test_make_unsafe<int (class_type::*)(int)&>();
    test_make_unsafe<int (class_type::*)(int) &&>();
    test_make_unsafe<int (class_type::*)(int) const>();
    test_make_unsafe<int (class_type::*)(int) const&>();
    test_make_unsafe<int (class_type::*)(int) const&&>();
    test_make_unsafe<int (class_type::*)(int) noexcept>();
    test_make_unsafe<int (class_type::*)(int) & noexcept>();
    test_make_unsafe<int (class_type::*)(int) && noexcept>();
    test_make_unsafe<int (class_type::*)(int) const noexcept>();
    test_make_unsafe<int (class_type::*)(int) const & noexcept>();
    test_make_unsafe<int (class_type::*)(int) const && noexcept>();

    test_make_unsafe<int (class_type::*)(...)>();
    test_make_unsafe<int (class_type::*)(...)&>();
    test_make_unsafe<int (class_type::*)(...) &&>();
    test_make_unsafe<int (class_type::*)(...) const>();
    test_make_unsafe<int (class_type::*)(...) const&>();
    test_make_unsafe<int (class_type::*)(...) const&&>();
    test_make_unsafe<int (class_type::*)(...) noexcept>();
    test_make_unsafe<int (class_type::*)(...) & noexcept>();
    test_make_unsafe<int (class_type::*)(...) && noexcept>();
    test_make_unsafe<int (class_type::*)(...) const noexcept>();
    test_make_unsafe<int (class_type::*)(...) const & noexcept>();
    test_make_unsafe<int (class_type::*)(...) const && noexcept>();

    test_make_unsafe<int (class_type::*)(int, ...)>();
    test_make_unsafe<int (class_type::*)(int, ...)&>();
    test_make_unsafe<int (class_type::*)(int, ...) &&>();
    test_make_unsafe<int (class_type::*)(int, ...) const>();
    test_make_unsafe<int (class_type::*)(int, ...) const&>();
    test_make_unsafe<int (class_type::*)(int, ...) const&&>();
    test_make_unsafe<int (class_type::*)(int, ...) noexcept>();
    test_make_unsafe<int (class_type::*)(int, ...) & noexcept>();
    test_make_unsafe<int (class_type::*)(int, ...) && noexcept>();
    test_make_unsafe<int (class_type::*)(int, ...) const noexcept>();
    test_make_unsafe<int (class_type::*)(int, ...) const & noexcept>();
    test_make_unsafe<int (class_type::*)(int, ...) const && noexcept>();
}
