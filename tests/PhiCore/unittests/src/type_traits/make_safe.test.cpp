#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_safe_bool.hpp>
#include <phi/type_traits/make_safe.hpp>
#include <vector>

struct A; // incomplete

template <typename InT, typename OutT = InT>
void test_make_safe()
{
    CHECK_SAME_TYPE(typename phi::make_safe<InT>::type, OutT);
    CHECK_SAME_TYPE(typename phi::make_safe<const InT>::type, const OutT);
    CHECK_SAME_TYPE(typename phi::make_safe<volatile InT>::type, volatile OutT);
    CHECK_SAME_TYPE(typename phi::make_safe<const volatile InT>::type, const volatile OutT);

    CHECK_SAME_TYPE(typename phi::make_safe_t<InT>, OutT);
    CHECK_SAME_TYPE(typename phi::make_safe_t<const InT>, const OutT);
    CHECK_SAME_TYPE(typename phi::make_safe_t<volatile InT>, volatile OutT);
    CHECK_SAME_TYPE(typename phi::make_safe_t<const volatile InT>, const volatile OutT);
}

TEST_CASE("make_safe")
{
    test_make_safe<void>();
    test_make_safe<phi::nullptr_t>();
    test_make_safe<bool, phi::boolean>();
    test_make_safe<char, char>();
    test_make_safe<signed char, phi::integer<signed char>>();
    test_make_safe<unsigned char, phi::integer<unsigned char>>();
    test_make_safe<short, phi::integer<short>>();
    test_make_safe<unsigned short, phi::integer<unsigned short>>();
    test_make_safe<int, phi::integer<int>>();
    test_make_safe<unsigned int, phi::integer<unsigned int>>();
    test_make_safe<long, phi::integer<long>>();
    test_make_safe<unsigned long, phi::integer<unsigned long>>();
    test_make_safe<long long, phi::integer<long long>>();
    test_make_safe<unsigned long long, phi::integer<unsigned long long>>();
    test_make_safe<float, phi::floating_point<float>>();
    test_make_safe<double, phi::floating_point<double>>();
    test_make_safe<long double, phi::floating_point<long double>>();
#if PHI_HAS_FEATURE_CHAR8_T()
    test_make_safe<char8_t>();
#endif
    test_make_safe<char16_t>();
    test_make_safe<char32_t>();
    test_make_safe<wchar_t>();

    test_make_safe<phi::boolean>();
    test_make_safe<phi::integer<signed char>>();
    test_make_safe<phi::integer<unsigned char>>();
    test_make_safe<phi::integer<short>>();
    test_make_safe<phi::integer<unsigned short>>();
    test_make_safe<phi::integer<int>>();
    test_make_safe<phi::integer<unsigned int>>();
    test_make_safe<phi::integer<long>>();
    test_make_safe<phi::integer<unsigned long>>();
    test_make_safe<phi::integer<long long>>();
    test_make_safe<phi::integer<unsigned long long>>();
    test_make_safe<phi::floating_point<float>>();
    test_make_safe<phi::floating_point<double>>();
    test_make_safe<phi::floating_point<long double>>();

    test_make_safe<std::vector<int>>();
    test_make_safe<phi::scope_ptr<int>>();

    test_make_safe<int&>();
    test_make_safe<const int&>();
    test_make_safe<volatile int&>();
    test_make_safe<const volatile int&>();
    test_make_safe<int&&>();
    test_make_safe<const int&&>();
    test_make_safe<volatile int&&>();
    test_make_safe<const volatile int&&>();
    test_make_safe<int*>();
    test_make_safe<const int*>();
    test_make_safe<volatile int*>();
    test_make_safe<const volatile int*>();
    test_make_safe<int**>();
    test_make_safe<const int**>();
    test_make_safe<volatile int**>();
    test_make_safe<const volatile int**>();
    test_make_safe<int*&>();
    test_make_safe<const int*&>();
    test_make_safe<volatile int*&>();
    test_make_safe<const volatile int*&>();
    test_make_safe<int*&&>();
    test_make_safe<const int*&&>();
    test_make_safe<volatile int*&&>();
    test_make_safe<const volatile int*&&>();
    test_make_safe<void*>();
    test_make_safe<char[3]>();
    test_make_safe<char[]>();
    test_make_safe<char* [3]>();
    test_make_safe<char*[]>();
    test_make_safe<int(*)[3]>();
    test_make_safe<int(*)[]>();
    test_make_safe<int(&)[3]>();
    test_make_safe<int(&)[]>();
    test_make_safe<int(&&)[3]>();
    test_make_safe<int(&&)[]>();
    test_make_safe<char[3][2]>();
    test_make_safe<char[][2]>();
    test_make_safe<char* [3][2]>();
    test_make_safe<char*[][2]>();
    test_make_safe<int(*)[3][2]>();
    test_make_safe<int(*)[][2]>();
    test_make_safe<int(&)[3][2]>();
    test_make_safe<int(&)[][2]>();
    test_make_safe<int(&&)[3][2]>();
    test_make_safe<int(&&)[][2]>();
    test_make_safe<class_type>();
    test_make_safe<class_type[]>();
    test_make_safe<class_type[2]>();
    test_make_safe<template_type<void>>();
    test_make_safe<template_type<int>>();
    test_make_safe<template_type<class_type>>();
    test_make_safe<template_type<incomplete_type>>();
    test_make_safe<variadic_template<>>();
    test_make_safe<variadic_template<void>>();
    test_make_safe<variadic_template<int>>();
    test_make_safe<variadic_template<class_type>>();
    test_make_safe<variadic_template<incomplete_type>>();
    test_make_safe<variadic_template<int, void, class_type, volatile char[]>>();
    test_make_safe<public_derived_from<base>>();
    test_make_safe<public_derived_from<derived>>();
    test_make_safe<public_derived_from<class_type>>();
    test_make_safe<private_derived_from<base>>();
    test_make_safe<private_derived_from<derived>>();
    test_make_safe<private_derived_from<class_type>>();
    test_make_safe<protected_derived_from<base>>();
    test_make_safe<protected_derived_from<derived>>();
    test_make_safe<protected_derived_from<class_type>>();
    test_make_safe<union_type>();
    test_make_safe<non_empty_union>();
    test_make_safe<empty>();
    test_make_safe<not_empty>();
    test_make_safe<bit_zero>();
    test_make_safe<bit_one>();
    test_make_safe<base>();
    test_make_safe<derived>();
    test_make_safe<abstract>();
    test_make_safe<public_abstract>();
    test_make_safe<private_abstract>();
    test_make_safe<protected_abstract>();
    test_make_safe<abstract_template<int>>();
    test_make_safe<abstract_template<double>>();
    test_make_safe<abstract_template<class_type>>();
    test_make_safe<abstract_template<incomplete_type>>();
    test_make_safe<final_type>();
    test_make_safe<public_destructor>();
    test_make_safe<protected_destructor>();
    test_make_safe<private_destructor>();
    test_make_safe<virtual_public_destructor>();
    test_make_safe<virtual_protected_destructor>();
    test_make_safe<virtual_private_destructor>();
    test_make_safe<pure_public_destructor>();
    test_make_safe<pure_protected_destructor>();
    test_make_safe<pure_private_destructor>();
    test_make_safe<deleted_public_destructor>();
    test_make_safe<deleted_protected_destructor>();
    test_make_safe<deleted_private_destructor>();
    test_make_safe<deleted_virtual_public_destructor>();
    test_make_safe<deleted_virtual_protected_destructor>();
    test_make_safe<deleted_virtual_private_destructor>();
    test_make_safe<Enum>();
    test_make_safe<EnumSigned>();
    test_make_safe<EnumUnsigned>();
    test_make_safe<EnumClass>();
    test_make_safe<EnumStruct>();
    test_make_safe<function_type>();
    test_make_safe<function_ptr>();
    test_make_safe<member_object_ptr>();
    test_make_safe<member_function_ptr>();
    test_make_safe<incomplete_type>();
    test_make_safe<incomplete_template<void>>();
    test_make_safe<incomplete_template<int>>();
    test_make_safe<incomplete_template<class_type>>();
    test_make_safe<incomplete_template<incomplete_type>>();
    test_make_safe<incomplete_variadic_template<>>();
    test_make_safe<incomplete_variadic_template<void>>();
    test_make_safe<incomplete_variadic_template<int>>();
    test_make_safe<incomplete_variadic_template<class_type>>();
    test_make_safe<incomplete_variadic_template<incomplete_type>>();
    test_make_safe<incomplete_variadic_template<int, void, class_type, volatile char[]>>();
    test_make_safe<int class_type::*>();
    test_make_safe<float class_type::*>();
    test_make_safe<void * class_type::*>();
    test_make_safe<int * class_type::*>();
    test_make_safe<int class_type::*&>();
    test_make_safe<float class_type::*&>();
    test_make_safe<void * class_type::*&>();
    test_make_safe<int * class_type::*&>();
    test_make_safe<int class_type::*&&>();
    test_make_safe<float class_type::*&&>();
    test_make_safe<void * class_type::*&&>();
    test_make_safe<int * class_type::*&&>();
    test_make_safe<int class_type::* const>();
    test_make_safe<float class_type::* const>();
    test_make_safe<void * class_type::* const>();
    test_make_safe<int class_type::* const&>();
    test_make_safe<float class_type::* const&>();
    test_make_safe<void * class_type::* const&>();
    test_make_safe<int class_type::* const&&>();
    test_make_safe<float class_type::* const&&>();
    test_make_safe<void * class_type::* const&&>();
    test_make_safe<int class_type::* volatile>();
    test_make_safe<float class_type::* volatile>();
    test_make_safe<void * class_type::* volatile>();
    test_make_safe<int class_type::* volatile&>();
    test_make_safe<float class_type::* volatile&>();
    test_make_safe<void * class_type::* volatile&>();
    test_make_safe<int class_type::* volatile&&>();
    test_make_safe<float class_type::* volatile&&>();
    test_make_safe<void * class_type::* volatile&&>();
    test_make_safe<int class_type::* const volatile>();
    test_make_safe<float class_type::* const volatile>();
    test_make_safe<void * class_type::* const volatile>();
    test_make_safe<int class_type::* const volatile&>();
    test_make_safe<float class_type::* const volatile&>();
    test_make_safe<void * class_type::* const volatile&>();
    test_make_safe<int class_type::* const volatile&&>();
    test_make_safe<float class_type::* const volatile&&>();
    test_make_safe<void * class_type::* const volatile&&>();
    test_make_safe<non_copyable>();
    test_make_safe<non_moveable>();
    test_make_safe<non_constructible>();
    test_make_safe<tracked>();
    test_make_safe<trap_constructible>();
    test_make_safe<trap_implicit_conversion>();
    test_make_safe<trap_comma>();
    test_make_safe<trap_call>();
    test_make_safe<trap_self_assign>();
    test_make_safe<trap_deref>();
    test_make_safe<trap_array_subscript>();

    test_make_safe<void()>();
    test_make_safe<void()&>();
    test_make_safe<void() &&>();
    test_make_safe<void() const>();
    test_make_safe<void() const&>();
    test_make_safe<void() const&&>();
    test_make_safe<void() volatile>();
    test_make_safe<void() volatile&>();
    test_make_safe<void() volatile&&>();
    test_make_safe<void() const volatile>();
    test_make_safe<void() const volatile&>();
    test_make_safe<void() const volatile&&>();
    test_make_safe<void() noexcept>();
    test_make_safe<void() & noexcept>();
    test_make_safe<void() && noexcept>();
    test_make_safe<void() const noexcept>();
    test_make_safe<void() const & noexcept>();
    test_make_safe<void() const && noexcept>();
    test_make_safe<void() volatile noexcept>();
    test_make_safe<void() volatile & noexcept>();
    test_make_safe<void() volatile && noexcept>();
    test_make_safe<void() const volatile noexcept>();
    test_make_safe<void() const volatile & noexcept>();
    test_make_safe<void() const volatile && noexcept>();

    test_make_safe<void(int)>();
    test_make_safe<void(int)&>();
    test_make_safe<void(int) &&>();
    test_make_safe<void(int) const>();
    test_make_safe<void(int) const&>();
    test_make_safe<void(int) const&&>();
    test_make_safe<void(int) volatile>();
    test_make_safe<void(int) volatile&>();
    test_make_safe<void(int) volatile&&>();
    test_make_safe<void(int) const volatile>();
    test_make_safe<void(int) const volatile&>();
    test_make_safe<void(int) const volatile&&>();
    test_make_safe<void(int) noexcept>();
    test_make_safe<void(int) & noexcept>();
    test_make_safe<void(int) && noexcept>();
    test_make_safe<void(int) const noexcept>();
    test_make_safe<void(int) const & noexcept>();
    test_make_safe<void(int) const && noexcept>();
    test_make_safe<void(int) volatile noexcept>();
    test_make_safe<void(int) volatile & noexcept>();
    test_make_safe<void(int) volatile && noexcept>();
    test_make_safe<void(int) const volatile noexcept>();
    test_make_safe<void(int) const volatile & noexcept>();
    test_make_safe<void(int) const volatile && noexcept>();

    test_make_safe<void(...)>();
    test_make_safe<void(...)&>();
    test_make_safe<void(...) &&>();
    test_make_safe<void(...) const>();
    test_make_safe<void(...) const&>();
    test_make_safe<void(...) const&&>();
    test_make_safe<void(...) volatile>();
    test_make_safe<void(...) volatile&>();
    test_make_safe<void(...) volatile&&>();
    test_make_safe<void(...) const volatile>();
    test_make_safe<void(...) const volatile&>();
    test_make_safe<void(...) const volatile&&>();
    test_make_safe<void(...) noexcept>();
    test_make_safe<void(...) & noexcept>();
    test_make_safe<void(...) && noexcept>();
    test_make_safe<void(...) const noexcept>();
    test_make_safe<void(...) const & noexcept>();
    test_make_safe<void(...) const && noexcept>();
    test_make_safe<void(...) volatile noexcept>();
    test_make_safe<void(...) volatile & noexcept>();
    test_make_safe<void(...) volatile && noexcept>();
    test_make_safe<void(...) const volatile noexcept>();
    test_make_safe<void(...) const volatile & noexcept>();
    test_make_safe<void(...) const volatile && noexcept>();

    test_make_safe<void(int, ...)>();
    test_make_safe<void(int, ...)&>();
    test_make_safe<void(int, ...) &&>();
    test_make_safe<void(int, ...) const>();
    test_make_safe<void(int, ...) const&>();
    test_make_safe<void(int, ...) const&&>();
    test_make_safe<void(int, ...) volatile>();
    test_make_safe<void(int, ...) volatile&>();
    test_make_safe<void(int, ...) volatile&&>();
    test_make_safe<void(int, ...) const volatile>();
    test_make_safe<void(int, ...) const volatile&>();
    test_make_safe<void(int, ...) const volatile&&>();
    test_make_safe<void(int, ...) noexcept>();
    test_make_safe<void(int, ...) & noexcept>();
    test_make_safe<void(int, ...) && noexcept>();
    test_make_safe<void(int, ...) const noexcept>();
    test_make_safe<void(int, ...) const & noexcept>();
    test_make_safe<void(int, ...) const && noexcept>();
    test_make_safe<void(int, ...) volatile noexcept>();
    test_make_safe<void(int, ...) volatile & noexcept>();
    test_make_safe<void(int, ...) volatile && noexcept>();
    test_make_safe<void(int, ...) const volatile noexcept>();
    test_make_safe<void(int, ...) const volatile & noexcept>();
    test_make_safe<void(int, ...) const volatile && noexcept>();

    test_make_safe<int()>();
    test_make_safe<int()&>();
    test_make_safe<int() &&>();
    test_make_safe<int() const>();
    test_make_safe<int() const&>();
    test_make_safe<int() const&&>();
    test_make_safe<int() volatile>();
    test_make_safe<int() volatile&>();
    test_make_safe<int() volatile&&>();
    test_make_safe<int() const volatile>();
    test_make_safe<int() const volatile&>();
    test_make_safe<int() const volatile&&>();
    test_make_safe<int() noexcept>();
    test_make_safe<int() & noexcept>();
    test_make_safe<int() && noexcept>();
    test_make_safe<int() const noexcept>();
    test_make_safe<int() const & noexcept>();
    test_make_safe<int() const && noexcept>();
    test_make_safe<int() volatile noexcept>();
    test_make_safe<int() volatile & noexcept>();
    test_make_safe<int() volatile && noexcept>();
    test_make_safe<int() const volatile noexcept>();
    test_make_safe<int() const volatile & noexcept>();
    test_make_safe<int() const volatile && noexcept>();

    test_make_safe<int(int)>();
    test_make_safe<int(int)&>();
    test_make_safe<int(int) &&>();
    test_make_safe<int(int) const>();
    test_make_safe<int(int) const&>();
    test_make_safe<int(int) const&&>();
    test_make_safe<int(int) volatile>();
    test_make_safe<int(int) volatile&>();
    test_make_safe<int(int) volatile&&>();
    test_make_safe<int(int) const volatile>();
    test_make_safe<int(int) const volatile&>();
    test_make_safe<int(int) const volatile&&>();
    test_make_safe<int(int) noexcept>();
    test_make_safe<int(int) & noexcept>();
    test_make_safe<int(int) && noexcept>();
    test_make_safe<int(int) const noexcept>();
    test_make_safe<int(int) const & noexcept>();
    test_make_safe<int(int) const && noexcept>();
    test_make_safe<int(int) volatile noexcept>();
    test_make_safe<int(int) volatile & noexcept>();
    test_make_safe<int(int) volatile && noexcept>();
    test_make_safe<int(int) const volatile noexcept>();
    test_make_safe<int(int) const volatile & noexcept>();
    test_make_safe<int(int) const volatile && noexcept>();

    test_make_safe<int(...)>();
    test_make_safe<int(...)&>();
    test_make_safe<int(...) &&>();
    test_make_safe<int(...) const>();
    test_make_safe<int(...) const&>();
    test_make_safe<int(...) const&&>();
    test_make_safe<int(...) volatile>();
    test_make_safe<int(...) volatile&>();
    test_make_safe<int(...) volatile&&>();
    test_make_safe<int(...) const volatile>();
    test_make_safe<int(...) const volatile&>();
    test_make_safe<int(...) const volatile&&>();
    test_make_safe<int(...) noexcept>();
    test_make_safe<int(...) & noexcept>();
    test_make_safe<int(...) && noexcept>();
    test_make_safe<int(...) const noexcept>();
    test_make_safe<int(...) const & noexcept>();
    test_make_safe<int(...) const && noexcept>();
    test_make_safe<int(...) volatile noexcept>();
    test_make_safe<int(...) volatile & noexcept>();
    test_make_safe<int(...) volatile && noexcept>();
    test_make_safe<int(...) const volatile noexcept>();
    test_make_safe<int(...) const volatile & noexcept>();
    test_make_safe<int(...) const volatile && noexcept>();

    test_make_safe<int(int, ...)>();
    test_make_safe<int(int, ...)&>();
    test_make_safe<int(int, ...) &&>();
    test_make_safe<int(int, ...) const>();
    test_make_safe<int(int, ...) const&>();
    test_make_safe<int(int, ...) const&&>();
    test_make_safe<int(int, ...) volatile>();
    test_make_safe<int(int, ...) volatile&>();
    test_make_safe<int(int, ...) volatile&&>();
    test_make_safe<int(int, ...) const volatile>();
    test_make_safe<int(int, ...) const volatile&>();
    test_make_safe<int(int, ...) const volatile&&>();
    test_make_safe<int(int, ...) noexcept>();
    test_make_safe<int(int, ...) & noexcept>();
    test_make_safe<int(int, ...) && noexcept>();
    test_make_safe<int(int, ...) const noexcept>();
    test_make_safe<int(int, ...) const & noexcept>();
    test_make_safe<int(int, ...) const && noexcept>();
    test_make_safe<int(int, ...) volatile noexcept>();
    test_make_safe<int(int, ...) volatile & noexcept>();
    test_make_safe<int(int, ...) volatile && noexcept>();
    test_make_safe<int(int, ...) const volatile noexcept>();
    test_make_safe<int(int, ...) const volatile & noexcept>();
    test_make_safe<int(int, ...) const volatile && noexcept>();

    test_make_safe<void (*)()>();
    test_make_safe<void (*)() noexcept>();

    test_make_safe<void (*)(int)>();
    test_make_safe<void (*)(int) noexcept>();

    test_make_safe<void (*)(...)>();
    test_make_safe<void (*)(...) noexcept>();

    test_make_safe<void (*)(int, ...)>();
    test_make_safe<void (*)(int, ...) noexcept>();

    test_make_safe<int (*)()>();
    test_make_safe<int (*)() noexcept>();

    test_make_safe<int (*)(int)>();
    test_make_safe<int (*)(int) noexcept>();

    test_make_safe<int (*)(...)>();
    test_make_safe<int (*)(...) noexcept>();

    test_make_safe<int (*)(int, ...)>();
    test_make_safe<int (*)(int, ...) noexcept>();

    test_make_safe<void (&)()>();
    test_make_safe<void (&)() noexcept>();

    test_make_safe<void (&)(int)>();
    test_make_safe<void (&)(int) noexcept>();

    test_make_safe<void (&)(...)>();
    test_make_safe<void (&)(...) noexcept>();

    test_make_safe<void (&)(int, ...)>();
    test_make_safe<void (&)(int, ...) noexcept>();

    test_make_safe<int (&)()>();
    test_make_safe<int (&)() noexcept>();

    test_make_safe<int (&)(int)>();
    test_make_safe<int (&)(int) noexcept>();

    test_make_safe<int (&)(...)>();
    test_make_safe<int (&)(...) noexcept>();

    test_make_safe<int (&)(int, ...)>();
    test_make_safe<int (&)(int, ...) noexcept>();

    test_make_safe<void (&&)()>();
    test_make_safe<void (&&)() noexcept>();

    test_make_safe<void (&&)(int)>();
    test_make_safe<void (&&)(int) noexcept>();

    test_make_safe<void (&&)(...)>();
    test_make_safe<void (&&)(...) noexcept>();

    test_make_safe<void (&&)(int, ...)>();
    test_make_safe<void (&&)(int, ...) noexcept>();

    test_make_safe<int (&&)()>();
    test_make_safe<int (&&)() noexcept>();

    test_make_safe<int (&&)(int)>();
    test_make_safe<int (&&)(int) noexcept>();

    test_make_safe<int (&&)(...)>();
    test_make_safe<int (&&)(...) noexcept>();

    test_make_safe<int (&&)(int, ...)>();
    test_make_safe<int (&&)(int, ...) noexcept>();

    test_make_safe<void (class_type::*)()>();
    test_make_safe<void (class_type::*)()&>();
    test_make_safe<void (class_type::*)() &&>();
    test_make_safe<void (class_type::*)() const>();
    test_make_safe<void (class_type::*)() const&>();
    test_make_safe<void (class_type::*)() const&&>();
    test_make_safe<void (class_type::*)() noexcept>();
    test_make_safe<void (class_type::*)() & noexcept>();
    test_make_safe<void (class_type::*)() && noexcept>();
    test_make_safe<void (class_type::*)() const noexcept>();
    test_make_safe<void (class_type::*)() const & noexcept>();
    test_make_safe<void (class_type::*)() const && noexcept>();

    test_make_safe<void (class_type::*)(int)>();
    test_make_safe<void (class_type::*)(int)&>();
    test_make_safe<void (class_type::*)(int) &&>();
    test_make_safe<void (class_type::*)(int) const>();
    test_make_safe<void (class_type::*)(int) const&>();
    test_make_safe<void (class_type::*)(int) const&&>();
    test_make_safe<void (class_type::*)(int) noexcept>();
    test_make_safe<void (class_type::*)(int) & noexcept>();
    test_make_safe<void (class_type::*)(int) && noexcept>();
    test_make_safe<void (class_type::*)(int) const noexcept>();
    test_make_safe<void (class_type::*)(int) const & noexcept>();
    test_make_safe<void (class_type::*)(int) const && noexcept>();

    test_make_safe<void (class_type::*)(...)>();
    test_make_safe<void (class_type::*)(...)&>();
    test_make_safe<void (class_type::*)(...) &&>();
    test_make_safe<void (class_type::*)(...) const>();
    test_make_safe<void (class_type::*)(...) const&>();
    test_make_safe<void (class_type::*)(...) const&&>();
    test_make_safe<void (class_type::*)(...) noexcept>();
    test_make_safe<void (class_type::*)(...) & noexcept>();
    test_make_safe<void (class_type::*)(...) && noexcept>();
    test_make_safe<void (class_type::*)(...) const noexcept>();
    test_make_safe<void (class_type::*)(...) const & noexcept>();
    test_make_safe<void (class_type::*)(...) const && noexcept>();

    test_make_safe<void (class_type::*)(int, ...)>();
    test_make_safe<void (class_type::*)(int, ...)&>();
    test_make_safe<void (class_type::*)(int, ...) &&>();
    test_make_safe<void (class_type::*)(int, ...) const>();
    test_make_safe<void (class_type::*)(int, ...) const&>();
    test_make_safe<void (class_type::*)(int, ...) const&&>();
    test_make_safe<void (class_type::*)(int, ...) noexcept>();
    test_make_safe<void (class_type::*)(int, ...) & noexcept>();
    test_make_safe<void (class_type::*)(int, ...) && noexcept>();
    test_make_safe<void (class_type::*)(int, ...) const noexcept>();
    test_make_safe<void (class_type::*)(int, ...) const & noexcept>();
    test_make_safe<void (class_type::*)(int, ...) const && noexcept>();

    test_make_safe<int (class_type::*)()>();
    test_make_safe<int (class_type::*)()&>();
    test_make_safe<int (class_type::*)() &&>();
    test_make_safe<int (class_type::*)() const>();
    test_make_safe<int (class_type::*)() const&>();
    test_make_safe<int (class_type::*)() const&&>();
    test_make_safe<int (class_type::*)() noexcept>();
    test_make_safe<int (class_type::*)() & noexcept>();
    test_make_safe<int (class_type::*)() && noexcept>();
    test_make_safe<int (class_type::*)() const noexcept>();
    test_make_safe<int (class_type::*)() const & noexcept>();
    test_make_safe<int (class_type::*)() const && noexcept>();

    test_make_safe<int (class_type::*)(int)>();
    test_make_safe<int (class_type::*)(int)&>();
    test_make_safe<int (class_type::*)(int) &&>();
    test_make_safe<int (class_type::*)(int) const>();
    test_make_safe<int (class_type::*)(int) const&>();
    test_make_safe<int (class_type::*)(int) const&&>();
    test_make_safe<int (class_type::*)(int) noexcept>();
    test_make_safe<int (class_type::*)(int) & noexcept>();
    test_make_safe<int (class_type::*)(int) && noexcept>();
    test_make_safe<int (class_type::*)(int) const noexcept>();
    test_make_safe<int (class_type::*)(int) const & noexcept>();
    test_make_safe<int (class_type::*)(int) const && noexcept>();

    test_make_safe<int (class_type::*)(...)>();
    test_make_safe<int (class_type::*)(...)&>();
    test_make_safe<int (class_type::*)(...) &&>();
    test_make_safe<int (class_type::*)(...) const>();
    test_make_safe<int (class_type::*)(...) const&>();
    test_make_safe<int (class_type::*)(...) const&&>();
    test_make_safe<int (class_type::*)(...) noexcept>();
    test_make_safe<int (class_type::*)(...) & noexcept>();
    test_make_safe<int (class_type::*)(...) && noexcept>();
    test_make_safe<int (class_type::*)(...) const noexcept>();
    test_make_safe<int (class_type::*)(...) const & noexcept>();
    test_make_safe<int (class_type::*)(...) const && noexcept>();

    test_make_safe<int (class_type::*)(int, ...)>();
    test_make_safe<int (class_type::*)(int, ...)&>();
    test_make_safe<int (class_type::*)(int, ...) &&>();
    test_make_safe<int (class_type::*)(int, ...) const>();
    test_make_safe<int (class_type::*)(int, ...) const&>();
    test_make_safe<int (class_type::*)(int, ...) const&&>();
    test_make_safe<int (class_type::*)(int, ...) noexcept>();
    test_make_safe<int (class_type::*)(int, ...) & noexcept>();
    test_make_safe<int (class_type::*)(int, ...) && noexcept>();
    test_make_safe<int (class_type::*)(int, ...) const noexcept>();
    test_make_safe<int (class_type::*)(int, ...) const & noexcept>();
    test_make_safe<int (class_type::*)(int, ...) const && noexcept>();
}
