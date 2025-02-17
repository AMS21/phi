#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/add_volatile.hpp>
#include <type_traits>
#include <vector>

template <typename TypeT>
void test_add_volatile()
{
    // TODO: Well for some reason this test crashes the MSVC compiler...
#if PHI_COMPILER_IS(MSVC)
    SKIP_CHECK();
#else
    CHECK_SAME_TYPE(typename phi::add_volatile<TypeT>::type, volatile TypeT);
    CHECK_SAME_TYPE(typename phi::add_volatile<const TypeT>::type, const volatile TypeT);
    CHECK_SAME_TYPE(typename phi::add_volatile<volatile TypeT>::type, volatile TypeT);
    CHECK_SAME_TYPE(typename phi::add_volatile<const volatile TypeT>::type, const volatile TypeT);

    CHECK_SAME_TYPE(phi::add_volatile_t<TypeT>, volatile TypeT);
    CHECK_SAME_TYPE(phi::add_volatile_t<const TypeT>, const volatile TypeT);
    CHECK_SAME_TYPE(phi::add_volatile_t<volatile TypeT>, volatile TypeT);
    CHECK_SAME_TYPE(phi::add_volatile_t<const volatile TypeT>, const volatile TypeT);

    // Standard compatibility
    CHECK_SAME_TYPE(typename phi::add_volatile<TypeT>::type,
                    typename std::add_volatile<TypeT>::type);
    CHECK_SAME_TYPE(typename phi::add_volatile<const TypeT>::type,
                    typename std::add_volatile<const TypeT>::type);
    CHECK_SAME_TYPE(typename phi::add_volatile<volatile TypeT>::type,
                    typename std::add_volatile<volatile TypeT>::type);
    CHECK_SAME_TYPE(typename phi::add_volatile<const volatile TypeT>::type,
                    typename std::add_volatile<const volatile TypeT>::type);
#endif
}

TEST_CASE("add_volatile")
{
    test_add_volatile<void>();
    test_add_volatile<phi::nullptr_t>();
    test_add_volatile<bool>();
    test_add_volatile<char>();
    test_add_volatile<signed char>();
    test_add_volatile<unsigned char>();
    test_add_volatile<short>();
    test_add_volatile<unsigned short>();
    test_add_volatile<int>();
    test_add_volatile<unsigned int>();
    test_add_volatile<long>();
    test_add_volatile<unsigned long>();
    test_add_volatile<long long>();
    test_add_volatile<unsigned long long>();
    test_add_volatile<float>();
    test_add_volatile<double>();
    test_add_volatile<long double>();
    test_add_volatile<char8_t>();
    test_add_volatile<char16_t>();
    test_add_volatile<char32_t>();
    test_add_volatile<wchar_t>();

    test_add_volatile<phi::boolean>();
    test_add_volatile<phi::integer<signed char>>();
    test_add_volatile<phi::integer<unsigned char>>();
    test_add_volatile<phi::integer<short>>();
    test_add_volatile<phi::integer<unsigned short>>();
    test_add_volatile<phi::integer<int>>();
    test_add_volatile<phi::integer<unsigned int>>();
    test_add_volatile<phi::integer<long>>();
    test_add_volatile<phi::integer<unsigned long>>();
    test_add_volatile<phi::integer<long long>>();
    test_add_volatile<phi::integer<unsigned long long>>();
    test_add_volatile<phi::floating_point<float>>();
    test_add_volatile<phi::floating_point<double>>();
    test_add_volatile<phi::floating_point<long double>>();

    test_add_volatile<std::vector<int>>();
    test_add_volatile<phi::scope_ptr<int>>();

    test_add_volatile<int&>();
    test_add_volatile<const int&>();
    test_add_volatile<volatile int&>();
    test_add_volatile<const volatile int&>();
    test_add_volatile<int&&>();
    test_add_volatile<const int&&>();
    test_add_volatile<volatile int&&>();
    test_add_volatile<const volatile int&&>();
    test_add_volatile<int*>();
    test_add_volatile<const int*>();
    test_add_volatile<volatile int*>();
    test_add_volatile<const volatile int*>();
    test_add_volatile<int**>();
    test_add_volatile<const int**>();
    test_add_volatile<volatile int**>();
    test_add_volatile<const volatile int**>();
    test_add_volatile<int*&>();
    test_add_volatile<const int*&>();
    test_add_volatile<volatile int*&>();
    test_add_volatile<const volatile int*&>();
    test_add_volatile<int*&&>();
    test_add_volatile<const int*&&>();
    test_add_volatile<volatile int*&&>();
    test_add_volatile<const volatile int*&&>();
    test_add_volatile<void*>();
    test_add_volatile<char[3]>();
    test_add_volatile<char[]>();
    test_add_volatile<char* [3]>();
    test_add_volatile<char*[]>();
    test_add_volatile<int(*)[3]>();
    test_add_volatile<int(*)[]>();
    test_add_volatile<int(&)[3]>();
    test_add_volatile<int(&)[]>();
    test_add_volatile<int(&&)[3]>();
    test_add_volatile<int(&&)[]>();
    test_add_volatile<char[3][2]>();
    test_add_volatile<char[][2]>();
    test_add_volatile<char* [3][2]>();
    test_add_volatile<char*[][2]>();
    test_add_volatile<int(*)[3][2]>();
    test_add_volatile<int(*)[][2]>();
    test_add_volatile<int(&)[3][2]>();
    test_add_volatile<int(&)[][2]>();
    test_add_volatile<int(&&)[3][2]>();
    test_add_volatile<int(&&)[][2]>();
    test_add_volatile<class_type>();
    test_add_volatile<class_type[]>();
    test_add_volatile<class_type[2]>();
    test_add_volatile<template_type<void>>();
    test_add_volatile<template_type<int>>();
    test_add_volatile<template_type<class_type>>();
    test_add_volatile<template_type<incomplete_type>>();
    test_add_volatile<variadic_template<>>();
    test_add_volatile<variadic_template<void>>();
    test_add_volatile<variadic_template<int>>();
    test_add_volatile<variadic_template<class_type>>();
    test_add_volatile<variadic_template<incomplete_type>>();
    test_add_volatile<variadic_template<int, void, class_type, volatile char[]>>();
    test_add_volatile<public_derived_from<base>>();
    test_add_volatile<public_derived_from<derived>>();
    test_add_volatile<public_derived_from<class_type>>();
    test_add_volatile<private_derived_from<base>>();
    test_add_volatile<private_derived_from<derived>>();
    test_add_volatile<private_derived_from<class_type>>();
    test_add_volatile<protected_derived_from<base>>();
    test_add_volatile<protected_derived_from<derived>>();
    test_add_volatile<protected_derived_from<class_type>>();
    test_add_volatile<union_type>();
    test_add_volatile<non_empty_union>();
    test_add_volatile<empty>();
    test_add_volatile<not_empty>();
    test_add_volatile<bit_zero>();
    test_add_volatile<bit_one>();
    test_add_volatile<base>();
    test_add_volatile<derived>();
    test_add_volatile<abstract>();
    test_add_volatile<public_abstract>();
    test_add_volatile<private_abstract>();
    test_add_volatile<protected_abstract>();
    test_add_volatile<abstract_template<int>>();
    test_add_volatile<abstract_template<double>>();
    test_add_volatile<abstract_template<class_type>>();
    test_add_volatile<abstract_template<incomplete_type>>();
    test_add_volatile<final_type>();
    test_add_volatile<public_destructor>();
    test_add_volatile<protected_destructor>();
    test_add_volatile<private_destructor>();
    test_add_volatile<virtual_public_destructor>();
    test_add_volatile<virtual_protected_destructor>();
    test_add_volatile<virtual_private_destructor>();
    test_add_volatile<pure_public_destructor>();
    test_add_volatile<pure_protected_destructor>();
    test_add_volatile<pure_private_destructor>();
    test_add_volatile<deleted_public_destructor>();
    test_add_volatile<deleted_protected_destructor>();
    test_add_volatile<deleted_private_destructor>();
    test_add_volatile<deleted_virtual_public_destructor>();
    test_add_volatile<deleted_virtual_protected_destructor>();
    test_add_volatile<deleted_virtual_private_destructor>();
    test_add_volatile<Enum>();
    test_add_volatile<EnumSigned>();
    test_add_volatile<EnumUnsigned>();
    test_add_volatile<EnumClass>();
    test_add_volatile<EnumStruct>();
    test_add_volatile<function_type>();
    test_add_volatile<function_ptr>();
    test_add_volatile<member_object_ptr>();
    test_add_volatile<member_function_ptr>();
    test_add_volatile<incomplete_type>();
    test_add_volatile<incomplete_template<void>>();
    test_add_volatile<incomplete_template<int>>();
    test_add_volatile<incomplete_template<class_type>>();
    test_add_volatile<incomplete_template<incomplete_type>>();
    test_add_volatile<incomplete_variadic_template<>>();
    test_add_volatile<incomplete_variadic_template<void>>();
    test_add_volatile<incomplete_variadic_template<int>>();
    test_add_volatile<incomplete_variadic_template<class_type>>();
    test_add_volatile<incomplete_variadic_template<incomplete_type>>();
    test_add_volatile<incomplete_variadic_template<int, void, class_type, volatile char[]>>();
    test_add_volatile<int class_type::*>();
    test_add_volatile<float class_type::*>();
    test_add_volatile<void * class_type::*>();
    test_add_volatile<int * class_type::*>();
    test_add_volatile<int class_type::*&>();
    test_add_volatile<float class_type::*&>();
    test_add_volatile<void * class_type::*&>();
    test_add_volatile<int * class_type::*&>();
    test_add_volatile<int class_type::*&&>();
    test_add_volatile<float class_type::*&&>();
    test_add_volatile<void * class_type::*&&>();
    test_add_volatile<int * class_type::*&&>();
    test_add_volatile<int class_type::* const>();
    test_add_volatile<float class_type::* const>();
    test_add_volatile<void * class_type::* const>();
    test_add_volatile<int class_type::* const&>();
    test_add_volatile<float class_type::* const&>();
    test_add_volatile<void * class_type::* const&>();
    test_add_volatile<int class_type::* const&&>();
    test_add_volatile<float class_type::* const&&>();
    test_add_volatile<void * class_type::* const&&>();
    test_add_volatile<int class_type::* volatile>();
    test_add_volatile<float class_type::* volatile>();
    test_add_volatile<void * class_type::* volatile>();
    test_add_volatile<int class_type::* volatile&>();
    test_add_volatile<float class_type::* volatile&>();
    test_add_volatile<void * class_type::* volatile&>();
    test_add_volatile<int class_type::* volatile&&>();
    test_add_volatile<float class_type::* volatile&&>();
    test_add_volatile<void * class_type::* volatile&&>();
    test_add_volatile<int class_type::* const volatile>();
    test_add_volatile<float class_type::* const volatile>();
    test_add_volatile<void * class_type::* const volatile>();
    test_add_volatile<int class_type::* const volatile&>();
    test_add_volatile<float class_type::* const volatile&>();
    test_add_volatile<void * class_type::* const volatile&>();
    test_add_volatile<int class_type::* const volatile&&>();
    test_add_volatile<float class_type::* const volatile&&>();
    test_add_volatile<void * class_type::* const volatile&&>();
    test_add_volatile<non_copyable>();
    test_add_volatile<non_moveable>();
    test_add_volatile<non_constructible>();
    test_add_volatile<tracked>();
    test_add_volatile<trap_constructible>();
    test_add_volatile<trap_implicit_conversion>();
    test_add_volatile<trap_comma>();
    test_add_volatile<trap_call>();
    test_add_volatile<trap_self_assign>();
    test_add_volatile<trap_deref>();
    test_add_volatile<trap_array_subscript>();

    test_add_volatile<void()>();
    test_add_volatile<void()&>();
    test_add_volatile<void() &&>();
    test_add_volatile<void() const>();
    test_add_volatile<void() const&>();
    test_add_volatile<void() const&&>();
    test_add_volatile<void() volatile>();
    test_add_volatile<void() volatile&>();
    test_add_volatile<void() volatile&&>();
    test_add_volatile<void() const volatile>();
    test_add_volatile<void() const volatile&>();
    test_add_volatile<void() const volatile&&>();
    test_add_volatile<void() noexcept>();
    test_add_volatile<void() & noexcept>();
    test_add_volatile<void() && noexcept>();
    test_add_volatile<void() const noexcept>();
    test_add_volatile<void() const & noexcept>();
    test_add_volatile<void() const && noexcept>();
    test_add_volatile<void() volatile noexcept>();
    test_add_volatile<void() volatile & noexcept>();
    test_add_volatile<void() volatile && noexcept>();
    test_add_volatile<void() const volatile noexcept>();
    test_add_volatile<void() const volatile & noexcept>();
    test_add_volatile<void() const volatile && noexcept>();

    test_add_volatile<void(int)>();
    test_add_volatile<void(int)&>();
    test_add_volatile<void(int) &&>();
    test_add_volatile<void(int) const>();
    test_add_volatile<void(int) const&>();
    test_add_volatile<void(int) const&&>();
    test_add_volatile<void(int) volatile>();
    test_add_volatile<void(int) volatile&>();
    test_add_volatile<void(int) volatile&&>();
    test_add_volatile<void(int) const volatile>();
    test_add_volatile<void(int) const volatile&>();
    test_add_volatile<void(int) const volatile&&>();
    test_add_volatile<void(int) noexcept>();
    test_add_volatile<void(int) & noexcept>();
    test_add_volatile<void(int) && noexcept>();
    test_add_volatile<void(int) const noexcept>();
    test_add_volatile<void(int) const & noexcept>();
    test_add_volatile<void(int) const && noexcept>();
    test_add_volatile<void(int) volatile noexcept>();
    test_add_volatile<void(int) volatile & noexcept>();
    test_add_volatile<void(int) volatile && noexcept>();
    test_add_volatile<void(int) const volatile noexcept>();
    test_add_volatile<void(int) const volatile & noexcept>();
    test_add_volatile<void(int) const volatile && noexcept>();

    test_add_volatile<void(...)>();
    test_add_volatile<void(...)&>();
    test_add_volatile<void(...) &&>();
    test_add_volatile<void(...) const>();
    test_add_volatile<void(...) const&>();
    test_add_volatile<void(...) const&&>();
    test_add_volatile<void(...) volatile>();
    test_add_volatile<void(...) volatile&>();
    test_add_volatile<void(...) volatile&&>();
    test_add_volatile<void(...) const volatile>();
    test_add_volatile<void(...) const volatile&>();
    test_add_volatile<void(...) const volatile&&>();
    test_add_volatile<void(...) noexcept>();
    test_add_volatile<void(...) & noexcept>();
    test_add_volatile<void(...) && noexcept>();
    test_add_volatile<void(...) const noexcept>();
    test_add_volatile<void(...) const & noexcept>();
    test_add_volatile<void(...) const && noexcept>();
    test_add_volatile<void(...) volatile noexcept>();
    test_add_volatile<void(...) volatile & noexcept>();
    test_add_volatile<void(...) volatile && noexcept>();
    test_add_volatile<void(...) const volatile noexcept>();
    test_add_volatile<void(...) const volatile & noexcept>();
    test_add_volatile<void(...) const volatile && noexcept>();

    test_add_volatile<void(int, ...)>();
    test_add_volatile<void(int, ...)&>();
    test_add_volatile<void(int, ...) &&>();
    test_add_volatile<void(int, ...) const>();
    test_add_volatile<void(int, ...) const&>();
    test_add_volatile<void(int, ...) const&&>();
    test_add_volatile<void(int, ...) volatile>();
    test_add_volatile<void(int, ...) volatile&>();
    test_add_volatile<void(int, ...) volatile&&>();
    test_add_volatile<void(int, ...) const volatile>();
    test_add_volatile<void(int, ...) const volatile&>();
    test_add_volatile<void(int, ...) const volatile&&>();
    test_add_volatile<void(int, ...) noexcept>();
    test_add_volatile<void(int, ...) & noexcept>();
    test_add_volatile<void(int, ...) && noexcept>();
    test_add_volatile<void(int, ...) const noexcept>();
    test_add_volatile<void(int, ...) const & noexcept>();
    test_add_volatile<void(int, ...) const && noexcept>();
    test_add_volatile<void(int, ...) volatile noexcept>();
    test_add_volatile<void(int, ...) volatile & noexcept>();
    test_add_volatile<void(int, ...) volatile && noexcept>();
    test_add_volatile<void(int, ...) const volatile noexcept>();
    test_add_volatile<void(int, ...) const volatile & noexcept>();
    test_add_volatile<void(int, ...) const volatile && noexcept>();

    test_add_volatile<int()>();
    test_add_volatile<int()&>();
    test_add_volatile<int() &&>();
    test_add_volatile<int() const>();
    test_add_volatile<int() const&>();
    test_add_volatile<int() const&&>();
    test_add_volatile<int() volatile>();
    test_add_volatile<int() volatile&>();
    test_add_volatile<int() volatile&&>();
    test_add_volatile<int() const volatile>();
    test_add_volatile<int() const volatile&>();
    test_add_volatile<int() const volatile&&>();
    test_add_volatile<int() noexcept>();
    test_add_volatile<int() & noexcept>();
    test_add_volatile<int() && noexcept>();
    test_add_volatile<int() const noexcept>();
    test_add_volatile<int() const & noexcept>();
    test_add_volatile<int() const && noexcept>();
    test_add_volatile<int() volatile noexcept>();
    test_add_volatile<int() volatile & noexcept>();
    test_add_volatile<int() volatile && noexcept>();
    test_add_volatile<int() const volatile noexcept>();
    test_add_volatile<int() const volatile & noexcept>();
    test_add_volatile<int() const volatile && noexcept>();

    test_add_volatile<int(int)>();
    test_add_volatile<int(int)&>();
    test_add_volatile<int(int) &&>();
    test_add_volatile<int(int) const>();
    test_add_volatile<int(int) const&>();
    test_add_volatile<int(int) const&&>();
    test_add_volatile<int(int) volatile>();
    test_add_volatile<int(int) volatile&>();
    test_add_volatile<int(int) volatile&&>();
    test_add_volatile<int(int) const volatile>();
    test_add_volatile<int(int) const volatile&>();
    test_add_volatile<int(int) const volatile&&>();
    test_add_volatile<int(int) noexcept>();
    test_add_volatile<int(int) & noexcept>();
    test_add_volatile<int(int) && noexcept>();
    test_add_volatile<int(int) const noexcept>();
    test_add_volatile<int(int) const & noexcept>();
    test_add_volatile<int(int) const && noexcept>();
    test_add_volatile<int(int) volatile noexcept>();
    test_add_volatile<int(int) volatile & noexcept>();
    test_add_volatile<int(int) volatile && noexcept>();
    test_add_volatile<int(int) const volatile noexcept>();
    test_add_volatile<int(int) const volatile & noexcept>();
    test_add_volatile<int(int) const volatile && noexcept>();

    test_add_volatile<int(...)>();
    test_add_volatile<int(...)&>();
    test_add_volatile<int(...) &&>();
    test_add_volatile<int(...) const>();
    test_add_volatile<int(...) const&>();
    test_add_volatile<int(...) const&&>();
    test_add_volatile<int(...) volatile>();
    test_add_volatile<int(...) volatile&>();
    test_add_volatile<int(...) volatile&&>();
    test_add_volatile<int(...) const volatile>();
    test_add_volatile<int(...) const volatile&>();
    test_add_volatile<int(...) const volatile&&>();
    test_add_volatile<int(...) noexcept>();
    test_add_volatile<int(...) & noexcept>();
    test_add_volatile<int(...) && noexcept>();
    test_add_volatile<int(...) const noexcept>();
    test_add_volatile<int(...) const & noexcept>();
    test_add_volatile<int(...) const && noexcept>();
    test_add_volatile<int(...) volatile noexcept>();
    test_add_volatile<int(...) volatile & noexcept>();
    test_add_volatile<int(...) volatile && noexcept>();
    test_add_volatile<int(...) const volatile noexcept>();
    test_add_volatile<int(...) const volatile & noexcept>();
    test_add_volatile<int(...) const volatile && noexcept>();

    test_add_volatile<int(int, ...)>();
    test_add_volatile<int(int, ...)&>();
    test_add_volatile<int(int, ...) &&>();
    test_add_volatile<int(int, ...) const>();
    test_add_volatile<int(int, ...) const&>();
    test_add_volatile<int(int, ...) const&&>();
    test_add_volatile<int(int, ...) volatile>();
    test_add_volatile<int(int, ...) volatile&>();
    test_add_volatile<int(int, ...) volatile&&>();
    test_add_volatile<int(int, ...) const volatile>();
    test_add_volatile<int(int, ...) const volatile&>();
    test_add_volatile<int(int, ...) const volatile&&>();
    test_add_volatile<int(int, ...) noexcept>();
    test_add_volatile<int(int, ...) & noexcept>();
    test_add_volatile<int(int, ...) && noexcept>();
    test_add_volatile<int(int, ...) const noexcept>();
    test_add_volatile<int(int, ...) const & noexcept>();
    test_add_volatile<int(int, ...) const && noexcept>();
    test_add_volatile<int(int, ...) volatile noexcept>();
    test_add_volatile<int(int, ...) volatile & noexcept>();
    test_add_volatile<int(int, ...) volatile && noexcept>();
    test_add_volatile<int(int, ...) const volatile noexcept>();
    test_add_volatile<int(int, ...) const volatile & noexcept>();
    test_add_volatile<int(int, ...) const volatile && noexcept>();

    test_add_volatile<void (*)()>();
    test_add_volatile<void (*)() noexcept>();

    test_add_volatile<void (*)(int)>();
    test_add_volatile<void (*)(int) noexcept>();

    test_add_volatile<void (*)(...)>();
    test_add_volatile<void (*)(...) noexcept>();

    test_add_volatile<void (*)(int, ...)>();
    test_add_volatile<void (*)(int, ...) noexcept>();

    test_add_volatile<int (*)()>();
    test_add_volatile<int (*)() noexcept>();

    test_add_volatile<int (*)(int)>();
    test_add_volatile<int (*)(int) noexcept>();

    test_add_volatile<int (*)(...)>();
    test_add_volatile<int (*)(...) noexcept>();

    test_add_volatile<int (*)(int, ...)>();
    test_add_volatile<int (*)(int, ...) noexcept>();

    test_add_volatile<void (&)()>();
    test_add_volatile<void (&)() noexcept>();

    test_add_volatile<void (&)(int)>();
    test_add_volatile<void (&)(int) noexcept>();

    test_add_volatile<void (&)(...)>();
    test_add_volatile<void (&)(...) noexcept>();

    test_add_volatile<void (&)(int, ...)>();
    test_add_volatile<void (&)(int, ...) noexcept>();

    test_add_volatile<int (&)()>();
    test_add_volatile<int (&)() noexcept>();

    test_add_volatile<int (&)(int)>();
    test_add_volatile<int (&)(int) noexcept>();

    test_add_volatile<int (&)(...)>();
    test_add_volatile<int (&)(...) noexcept>();

    test_add_volatile<int (&)(int, ...)>();
    test_add_volatile<int (&)(int, ...) noexcept>();

    test_add_volatile<void (&&)()>();
    test_add_volatile<void (&&)() noexcept>();

    test_add_volatile<void (&&)(int)>();
    test_add_volatile<void (&&)(int) noexcept>();

    test_add_volatile<void (&&)(...)>();
    test_add_volatile<void (&&)(...) noexcept>();

    test_add_volatile<void (&&)(int, ...)>();
    test_add_volatile<void (&&)(int, ...) noexcept>();

    test_add_volatile<int (&&)()>();
    test_add_volatile<int (&&)() noexcept>();

    test_add_volatile<int (&&)(int)>();
    test_add_volatile<int (&&)(int) noexcept>();

    test_add_volatile<int (&&)(...)>();
    test_add_volatile<int (&&)(...) noexcept>();

    test_add_volatile<int (&&)(int, ...)>();
    test_add_volatile<int (&&)(int, ...) noexcept>();

    test_add_volatile<void (class_type::*)()>();
    test_add_volatile<void (class_type::*)()&>();
    test_add_volatile<void (class_type::*)() &&>();
    test_add_volatile<void (class_type::*)() const>();
    test_add_volatile<void (class_type::*)() const&>();
    test_add_volatile<void (class_type::*)() const&&>();
    test_add_volatile<void (class_type::*)() noexcept>();
    test_add_volatile<void (class_type::*)() & noexcept>();
    test_add_volatile<void (class_type::*)() && noexcept>();
    test_add_volatile<void (class_type::*)() const noexcept>();
    test_add_volatile<void (class_type::*)() const & noexcept>();
    test_add_volatile<void (class_type::*)() const && noexcept>();

    test_add_volatile<void (class_type::*)(int)>();
    test_add_volatile<void (class_type::*)(int)&>();
    test_add_volatile<void (class_type::*)(int) &&>();
    test_add_volatile<void (class_type::*)(int) const>();
    test_add_volatile<void (class_type::*)(int) const&>();
    test_add_volatile<void (class_type::*)(int) const&&>();
    test_add_volatile<void (class_type::*)(int) noexcept>();
    test_add_volatile<void (class_type::*)(int) & noexcept>();
    test_add_volatile<void (class_type::*)(int) && noexcept>();
    test_add_volatile<void (class_type::*)(int) const noexcept>();
    test_add_volatile<void (class_type::*)(int) const & noexcept>();
    test_add_volatile<void (class_type::*)(int) const && noexcept>();

    test_add_volatile<void (class_type::*)(...)>();
    test_add_volatile<void (class_type::*)(...)&>();
    test_add_volatile<void (class_type::*)(...) &&>();
    test_add_volatile<void (class_type::*)(...) const>();
    test_add_volatile<void (class_type::*)(...) const&>();
    test_add_volatile<void (class_type::*)(...) const&&>();
    test_add_volatile<void (class_type::*)(...) noexcept>();
    test_add_volatile<void (class_type::*)(...) & noexcept>();
    test_add_volatile<void (class_type::*)(...) && noexcept>();
    test_add_volatile<void (class_type::*)(...) const noexcept>();
    test_add_volatile<void (class_type::*)(...) const & noexcept>();
    test_add_volatile<void (class_type::*)(...) const && noexcept>();

    test_add_volatile<void (class_type::*)(int, ...)>();
    test_add_volatile<void (class_type::*)(int, ...)&>();
    test_add_volatile<void (class_type::*)(int, ...) &&>();
    test_add_volatile<void (class_type::*)(int, ...) const>();
    test_add_volatile<void (class_type::*)(int, ...) const&>();
    test_add_volatile<void (class_type::*)(int, ...) const&&>();
    test_add_volatile<void (class_type::*)(int, ...) noexcept>();
    test_add_volatile<void (class_type::*)(int, ...) & noexcept>();
    test_add_volatile<void (class_type::*)(int, ...) && noexcept>();
    test_add_volatile<void (class_type::*)(int, ...) const noexcept>();
    test_add_volatile<void (class_type::*)(int, ...) const & noexcept>();
    test_add_volatile<void (class_type::*)(int, ...) const && noexcept>();

    test_add_volatile<int (class_type::*)()>();
    test_add_volatile<int (class_type::*)()&>();
    test_add_volatile<int (class_type::*)() &&>();
    test_add_volatile<int (class_type::*)() const>();
    test_add_volatile<int (class_type::*)() const&>();
    test_add_volatile<int (class_type::*)() const&&>();
    test_add_volatile<int (class_type::*)() noexcept>();
    test_add_volatile<int (class_type::*)() & noexcept>();
    test_add_volatile<int (class_type::*)() && noexcept>();
    test_add_volatile<int (class_type::*)() const noexcept>();
    test_add_volatile<int (class_type::*)() const & noexcept>();
    test_add_volatile<int (class_type::*)() const && noexcept>();

    test_add_volatile<int (class_type::*)(int)>();
    test_add_volatile<int (class_type::*)(int)&>();
    test_add_volatile<int (class_type::*)(int) &&>();
    test_add_volatile<int (class_type::*)(int) const>();
    test_add_volatile<int (class_type::*)(int) const&>();
    test_add_volatile<int (class_type::*)(int) const&&>();
    test_add_volatile<int (class_type::*)(int) noexcept>();
    test_add_volatile<int (class_type::*)(int) & noexcept>();
    test_add_volatile<int (class_type::*)(int) && noexcept>();
    test_add_volatile<int (class_type::*)(int) const noexcept>();
    test_add_volatile<int (class_type::*)(int) const & noexcept>();
    test_add_volatile<int (class_type::*)(int) const && noexcept>();

    test_add_volatile<int (class_type::*)(...)>();
    test_add_volatile<int (class_type::*)(...)&>();
    test_add_volatile<int (class_type::*)(...) &&>();
    test_add_volatile<int (class_type::*)(...) const>();
    test_add_volatile<int (class_type::*)(...) const&>();
    test_add_volatile<int (class_type::*)(...) const&&>();
    test_add_volatile<int (class_type::*)(...) noexcept>();
    test_add_volatile<int (class_type::*)(...) & noexcept>();
    test_add_volatile<int (class_type::*)(...) && noexcept>();
    test_add_volatile<int (class_type::*)(...) const noexcept>();
    test_add_volatile<int (class_type::*)(...) const & noexcept>();
    test_add_volatile<int (class_type::*)(...) const && noexcept>();

    test_add_volatile<int (class_type::*)(int, ...)>();
    test_add_volatile<int (class_type::*)(int, ...)&>();
    test_add_volatile<int (class_type::*)(int, ...) &&>();
    test_add_volatile<int (class_type::*)(int, ...) const>();
    test_add_volatile<int (class_type::*)(int, ...) const&>();
    test_add_volatile<int (class_type::*)(int, ...) const&&>();
    test_add_volatile<int (class_type::*)(int, ...) noexcept>();
    test_add_volatile<int (class_type::*)(int, ...) & noexcept>();
    test_add_volatile<int (class_type::*)(int, ...) && noexcept>();
    test_add_volatile<int (class_type::*)(int, ...) const noexcept>();
    test_add_volatile<int (class_type::*)(int, ...) const & noexcept>();
    test_add_volatile<int (class_type::*)(int, ...) const && noexcept>();
}
