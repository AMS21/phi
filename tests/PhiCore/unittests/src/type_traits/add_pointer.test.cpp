#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/add_pointer.hpp>
#include <type_traits>
#include <vector>

template <typename TypeT, typename ExpectedT = TypeT*>
void test_add_pointer()
{
    CHECK_SAME_TYPE(typename phi::add_pointer<TypeT>::type, ExpectedT);
    CHECK_SAME_TYPE(const typename phi::add_pointer<TypeT>::type, const ExpectedT);
    CHECK_SAME_TYPE(volatile typename phi::add_pointer<TypeT>::type, volatile ExpectedT);
    CHECK_SAME_TYPE(const volatile typename phi::add_pointer<TypeT>::type,
                    const volatile ExpectedT);

    CHECK_SAME_TYPE(phi::add_pointer_t<TypeT>, ExpectedT);
    CHECK_SAME_TYPE(const phi::add_pointer_t<TypeT>, const ExpectedT);
    CHECK_SAME_TYPE(volatile phi::add_pointer_t<TypeT>, volatile ExpectedT);
    CHECK_SAME_TYPE(const volatile phi::add_pointer_t<TypeT>, const volatile ExpectedT);

    // Standard compatibility
    CHECK_SAME_TYPE(typename phi::add_pointer<TypeT>::type, typename std::add_pointer<TypeT>::type);
    CHECK_SAME_TYPE(typename phi::add_pointer<const TypeT>::type,
                    typename std::add_pointer<const TypeT>::type);
    CHECK_SAME_TYPE(typename phi::add_pointer<volatile TypeT>::type,
                    typename std::add_pointer<volatile TypeT>::type);
    CHECK_SAME_TYPE(typename phi::add_pointer<const volatile TypeT>::type,
                    typename std::add_pointer<const volatile TypeT>::type);
}

template <typename FuncT>
void test_function0()
{
    CHECK_SAME_TYPE(FuncT*, typename phi::add_pointer<FuncT>::type);
    CHECK_SAME_TYPE(FuncT*, phi::add_pointer_t<FuncT>);

    // Standard compatibility
    CHECK_SAME_TYPE(typename phi::add_pointer<FuncT>::type, typename std::add_pointer<FuncT>::type);
}

template <typename FuncT>
void test_function1()
{
    CHECK_SAME_TYPE(FuncT, typename phi::add_pointer<FuncT>::type);
    CHECK_SAME_TYPE(FuncT, phi::add_pointer_t<FuncT>);

    // Standard compatibility
    CHECK_SAME_TYPE(typename phi::add_pointer<FuncT>::type, typename std::add_pointer<FuncT>::type);
}

struct Foo
{};

TEST_CASE("add_pointer")
{
    test_add_pointer<Foo, Foo*>();

    test_add_pointer<void, void*>();
    test_add_pointer<phi::nullptr_t, phi::nullptr_t*>();
    test_add_pointer<bool, bool*>();
    test_add_pointer<char, char*>();
    test_add_pointer<signed char, signed char*>();
    test_add_pointer<unsigned char, unsigned char*>();
    test_add_pointer<short, short*>();
    test_add_pointer<unsigned short, unsigned short*>();
    test_add_pointer<int, int*>();
    test_add_pointer<unsigned int, unsigned int*>();
    test_add_pointer<long, long*>();
    test_add_pointer<unsigned long, unsigned long*>();
    test_add_pointer<long long, long long*>();
    test_add_pointer<unsigned long long, unsigned long long*>();
    test_add_pointer<float, float*>();
    test_add_pointer<double, double*>();
    test_add_pointer<long double, long double*>();
    test_add_pointer<char8_t, char8_t*>();
    test_add_pointer<char16_t, char16_t*>();
    test_add_pointer<char32_t, char32_t*>();
    test_add_pointer<wchar_t, wchar_t*>();

    test_add_pointer<phi::boolean, phi::boolean*>();
    test_add_pointer<phi::integer<signed char>, phi::integer<signed char>*>();
    test_add_pointer<phi::integer<unsigned char>, phi::integer<unsigned char>*>();
    test_add_pointer<phi::integer<short>, phi::integer<short>*>();
    test_add_pointer<phi::integer<unsigned short>, phi::integer<unsigned short>*>();
    test_add_pointer<phi::integer<int>, phi::integer<int>*>();
    test_add_pointer<phi::integer<unsigned int>, phi::integer<unsigned int>*>();
    test_add_pointer<phi::integer<long>, phi::integer<long>*>();
    test_add_pointer<phi::integer<unsigned long>, phi::integer<unsigned long>*>();
    test_add_pointer<phi::integer<long long>, phi::integer<long long>*>();
    test_add_pointer<phi::integer<unsigned long long>, phi::integer<unsigned long long>*>();
    test_add_pointer<phi::floating_point<float>, phi::floating_point<float>*>();
    test_add_pointer<phi::floating_point<double>, phi::floating_point<double>*>();
    test_add_pointer<phi::floating_point<long double>, phi::floating_point<long double>*>();

    test_add_pointer<std::vector<int>, std::vector<int>*>();
    test_add_pointer<phi::scope_ptr<int>, phi::scope_ptr<int>*>();

    test_add_pointer<int&, int*>();
    test_add_pointer<const int&, const int*>();
    test_add_pointer<volatile int&, volatile int*>();
    test_add_pointer<const volatile int&, const volatile int*>();
    test_add_pointer<int&&, int*>();
    test_add_pointer<const int&&, const int*>();
    test_add_pointer<volatile int&&, volatile int*>();
    test_add_pointer<const volatile int&&, const volatile int*>();
    test_add_pointer<int*, int**>();
    test_add_pointer<const int*, const int**>();
    test_add_pointer<volatile int*, volatile int**>();
    test_add_pointer<const volatile int*, const volatile int**>();
    test_add_pointer<int**, int***>();
    test_add_pointer<const int**>();
    test_add_pointer<volatile int**>();
    test_add_pointer<const volatile int**>();
    test_add_pointer<int*&, int**>();
    test_add_pointer<const int*&, const int**>();
    test_add_pointer<volatile int*&, volatile int**>();
    test_add_pointer<const volatile int*&, const volatile int**>();
    test_add_pointer<int*&&, int**>();
    test_add_pointer<const int*&&, const int**>();
    test_add_pointer<volatile int*&&, volatile int**>();
    test_add_pointer<const volatile int*&&, const volatile int**>();
    test_add_pointer<void*>();
    test_add_pointer<char[3]>();
    test_add_pointer<char[]>();
    test_add_pointer<char* [3]>();
    test_add_pointer<char*[]>();
    test_add_pointer<int(*)[3]>();
    test_add_pointer<int(*)[]>();
    test_add_pointer<int(&)[3], int(*)[3]>();
    test_add_pointer<int(&)[], int(*)[]>();
    test_add_pointer<int(&&)[3], int(*)[3]>();
    test_add_pointer<int(&&)[], int(*)[]>();
    test_add_pointer<char[3][2]>();
    test_add_pointer<char[][2]>();
    test_add_pointer<char* [3][2]>();
    test_add_pointer<char*[][2]>();
    test_add_pointer<int(*)[3][2]>();
    test_add_pointer<int(*)[][2]>();
    test_add_pointer<int(&)[3][2], int(*)[3][2]>();
    test_add_pointer<int(&)[][2], int(*)[][2]>();
    test_add_pointer<int(&&)[3][2], int(*)[3][2]>();
    test_add_pointer<int(&&)[][2], int(*)[][2]>();
    test_add_pointer<class_type>();
    test_add_pointer<class_type[]>();
    test_add_pointer<class_type[2]>();
    test_add_pointer<template_type<void>>();
    test_add_pointer<template_type<int>>();
    test_add_pointer<template_type<class_type>>();
    test_add_pointer<template_type<incomplete_type>>();
    test_add_pointer<variadic_template<>>();
    test_add_pointer<variadic_template<void>>();
    test_add_pointer<variadic_template<int>>();
    test_add_pointer<variadic_template<class_type>>();
    test_add_pointer<variadic_template<incomplete_type>>();
    test_add_pointer<variadic_template<int, void, class_type, volatile char[]>>();
    test_add_pointer<public_derived_from<base>>();
    test_add_pointer<public_derived_from<derived>>();
    test_add_pointer<public_derived_from<class_type>>();
    test_add_pointer<private_derived_from<base>>();
    test_add_pointer<private_derived_from<derived>>();
    test_add_pointer<private_derived_from<class_type>>();
    test_add_pointer<protected_derived_from<base>>();
    test_add_pointer<protected_derived_from<derived>>();
    test_add_pointer<protected_derived_from<class_type>>();
    test_add_pointer<union_type>();
    test_add_pointer<non_empty_union>();
    test_add_pointer<empty>();
    test_add_pointer<not_empty>();
    test_add_pointer<bit_zero>();
    test_add_pointer<bit_one>();
    test_add_pointer<base>();
    test_add_pointer<derived>();
    test_add_pointer<abstract>();
    test_add_pointer<public_abstract>();
    test_add_pointer<private_abstract>();
    test_add_pointer<protected_abstract>();
    test_add_pointer<abstract_template<int>>();
    test_add_pointer<abstract_template<double>>();
    test_add_pointer<abstract_template<class_type>>();
    test_add_pointer<abstract_template<incomplete_type>>();
    test_add_pointer<final_type>();
    test_add_pointer<public_destructor>();
    test_add_pointer<protected_destructor>();
    test_add_pointer<private_destructor>();
    test_add_pointer<virtual_public_destructor>();
    test_add_pointer<virtual_protected_destructor>();
    test_add_pointer<virtual_private_destructor>();
    test_add_pointer<pure_public_destructor>();
    test_add_pointer<pure_protected_destructor>();
    test_add_pointer<pure_private_destructor>();
    test_add_pointer<deleted_public_destructor>();
    test_add_pointer<deleted_protected_destructor>();
    test_add_pointer<deleted_private_destructor>();
    test_add_pointer<deleted_virtual_public_destructor>();
    test_add_pointer<deleted_virtual_protected_destructor>();
    test_add_pointer<deleted_virtual_private_destructor>();
    test_add_pointer<Enum>();
    test_add_pointer<EnumSigned>();
    test_add_pointer<EnumUnsigned>();
    test_add_pointer<EnumClass>();
    test_add_pointer<EnumStruct>();
    test_add_pointer<function_type>();
    test_add_pointer<function_ptr>();
    test_add_pointer<member_object_ptr>();
    test_add_pointer<member_function_ptr>();
    test_add_pointer<incomplete_type>();
    test_add_pointer<incomplete_template<void>>();
    test_add_pointer<incomplete_template<int>>();
    test_add_pointer<incomplete_template<class_type>>();
    test_add_pointer<incomplete_template<incomplete_type>>();
    test_add_pointer<incomplete_variadic_template<>>();
    test_add_pointer<incomplete_variadic_template<void>>();
    test_add_pointer<incomplete_variadic_template<int>>();
    test_add_pointer<incomplete_variadic_template<class_type>>();
    test_add_pointer<incomplete_variadic_template<incomplete_type>>();
    test_add_pointer<incomplete_variadic_template<int, void, class_type, volatile char[]>>();
    test_add_pointer<int class_type::*>();
    test_add_pointer<float class_type::*>();
    test_add_pointer<void * class_type::*>();
    test_add_pointer<int * class_type::*>();
    test_add_pointer<int class_type::*&, int class_type::**>();
    test_add_pointer<float class_type::*&, float class_type::**>();
    test_add_pointer<void * class_type::*&, void * class_type::**>();
    test_add_pointer<int * class_type::*&, int * class_type::**>();
    test_add_pointer<int class_type::*&&, int class_type::**>();
    test_add_pointer<float class_type::*&&, float class_type::**>();
    test_add_pointer<void * class_type::*&&, void * class_type::**>();
    test_add_pointer<int * class_type::*&&, int * class_type::**>();
    test_add_pointer<int class_type::* const>();
    test_add_pointer<float class_type::* const>();
    test_add_pointer<void * class_type::* const>();
    test_add_pointer<int class_type::* const&, int class_type::* const*>();
    test_add_pointer<float class_type::* const&, float class_type::* const*>();
    test_add_pointer<void * class_type::* const&, void * class_type::* const*>();
    test_add_pointer<int class_type::* const&&, int class_type::* const*>();
    test_add_pointer<float class_type::* const&&, float class_type::* const*>();
    test_add_pointer<void * class_type::* const&&, void * class_type::* const*>();
    test_add_pointer<int class_type::* volatile>();
    test_add_pointer<float class_type::* volatile>();
    test_add_pointer<void * class_type::* volatile>();
    test_add_pointer<int class_type::* volatile&, int class_type::* volatile*>();
    test_add_pointer<float class_type::* volatile&, float class_type::* volatile*>();
    test_add_pointer<void * class_type::* volatile&, void * class_type::* volatile*>();
    test_add_pointer<int class_type::* volatile&&, int class_type::* volatile*>();
    test_add_pointer<float class_type::* volatile&&, float class_type::* volatile*>();
    test_add_pointer<void * class_type::* volatile&&, void * class_type::* volatile*>();
    test_add_pointer<int class_type::* const volatile>();
    test_add_pointer<float class_type::* const volatile>();
    test_add_pointer<void * class_type::* const volatile>();
    test_add_pointer<int class_type::* const volatile&, int class_type::* const volatile*>();
    test_add_pointer<float class_type::* const volatile&, float class_type::* const volatile*>();
    test_add_pointer<void * class_type::* const volatile&, void * class_type::* const volatile*>();
    test_add_pointer<int class_type::* const volatile&&, int class_type::* const volatile*>();
    test_add_pointer<float class_type::* const volatile&&, float class_type::* const volatile*>();
    test_add_pointer<void * class_type::* const volatile&&, void * class_type::* const volatile*>();
    test_add_pointer<non_copyable>();
    test_add_pointer<non_moveable>();
    test_add_pointer<non_constructible>();
    test_add_pointer<tracked>();
    test_add_pointer<trap_constructible>();
    test_add_pointer<trap_implicit_conversion>();
    test_add_pointer<trap_comma>();
    test_add_pointer<trap_call>();
    test_add_pointer<trap_self_assign>();
    test_add_pointer<trap_deref>();
    test_add_pointer<trap_array_subscript>();

    test_add_pointer<void(), void (*)()>();
    test_add_pointer<void()&, void()&>();
    test_add_pointer<void()&&, void() &&>();
    test_add_pointer<void() const, void() const>();
    test_add_pointer<void() const&, void() const&>();
    test_add_pointer<void() const&&, void() const&&>();
    test_add_pointer<void() volatile, void() volatile>();
    test_add_pointer<void() volatile&, void() volatile&>();
    test_add_pointer<void() volatile&&, void() volatile&&>();
    test_add_pointer<void() const volatile, void() const volatile>();
    test_add_pointer<void() const volatile&, void() const volatile&>();
    test_add_pointer<void() const volatile&&, void() const volatile&&>();
    test_add_pointer<void() noexcept, void (*)() noexcept>();
    test_add_pointer<void() & noexcept, void() & noexcept>();
    test_add_pointer<void() && noexcept, void() && noexcept>();
    test_add_pointer<void() const noexcept, void() const noexcept>();
    test_add_pointer<void() const & noexcept, void() const & noexcept>();
    test_add_pointer<void() const && noexcept, void() const && noexcept>();
    test_add_pointer<void() volatile noexcept, void() volatile noexcept>();
    test_add_pointer<void() volatile & noexcept, void() volatile & noexcept>();
    test_add_pointer<void() volatile && noexcept, void() volatile && noexcept>();
    test_add_pointer<void() const volatile noexcept, void() const volatile noexcept>();
    test_add_pointer<void() const volatile & noexcept, void() const volatile & noexcept>();
    test_add_pointer<void() const volatile && noexcept, void() const volatile && noexcept>();

    test_add_pointer<void(int), void (*)(int)>();
    test_add_pointer<void(int)&, void(int)&>();
    test_add_pointer<void(int)&&, void(int) &&>();
    test_add_pointer<void(int) const, void(int) const>();
    test_add_pointer<void(int) const&, void(int) const&>();
    test_add_pointer<void(int) const&&, void(int) const&&>();
    test_add_pointer<void(int) volatile, void(int) volatile>();
    test_add_pointer<void(int) volatile&, void(int) volatile&>();
    test_add_pointer<void(int) volatile&&, void(int) volatile&&>();
    test_add_pointer<void(int) const volatile, void(int) const volatile>();
    test_add_pointer<void(int) const volatile&, void(int) const volatile&>();
    test_add_pointer<void(int) const volatile&&, void(int) const volatile&&>();
    test_add_pointer<void(int) noexcept, void (*)(int) noexcept>();
    test_add_pointer<void(int) & noexcept, void(int) & noexcept>();
    test_add_pointer<void(int) && noexcept, void(int) && noexcept>();
    test_add_pointer<void(int) const noexcept, void(int) const noexcept>();
    test_add_pointer<void(int) const & noexcept, void(int) const & noexcept>();
    test_add_pointer<void(int) const && noexcept, void(int) const && noexcept>();
    test_add_pointer<void(int) volatile noexcept, void(int) volatile noexcept>();
    test_add_pointer<void(int) volatile & noexcept, void(int) volatile & noexcept>();
    test_add_pointer<void(int) volatile && noexcept, void(int) volatile && noexcept>();
    test_add_pointer<void(int) const volatile noexcept, void(int) const volatile noexcept>();
    test_add_pointer<void(int) const volatile & noexcept, void(int) const volatile & noexcept>();
    test_add_pointer<void(int) const volatile && noexcept, void(int) const volatile && noexcept>();

    test_add_pointer<void(...), void (*)(...)>();
    test_add_pointer<void(...)&, void(...)&>();
    test_add_pointer<void(...)&&, void(...) &&>();
    test_add_pointer<void(...) const, void(...) const>();
    test_add_pointer<void(...) const&, void(...) const&>();
    test_add_pointer<void(...) const&&, void(...) const&&>();
    test_add_pointer<void(...) volatile, void(...) volatile>();
    test_add_pointer<void(...) volatile&, void(...) volatile&>();
    test_add_pointer<void(...) volatile&&, void(...) volatile&&>();
    test_add_pointer<void(...) const volatile, void(...) const volatile>();
    test_add_pointer<void(...) const volatile&, void(...) const volatile&>();
    test_add_pointer<void(...) const volatile&&, void(...) const volatile&&>();
    test_add_pointer<void(...) noexcept, void (*)(...) noexcept>();
    test_add_pointer<void(...) & noexcept, void(...) & noexcept>();
    test_add_pointer<void(...) && noexcept, void(...) && noexcept>();
    test_add_pointer<void(...) const noexcept, void(...) const noexcept>();
    test_add_pointer<void(...) const & noexcept, void(...) const & noexcept>();
    test_add_pointer<void(...) const && noexcept, void(...) const && noexcept>();
    test_add_pointer<void(...) volatile noexcept, void(...) volatile noexcept>();
    test_add_pointer<void(...) volatile & noexcept, void(...) volatile & noexcept>();
    test_add_pointer<void(...) volatile && noexcept, void(...) volatile && noexcept>();
    test_add_pointer<void(...) const volatile noexcept, void(...) const volatile noexcept>();
    test_add_pointer<void(...) const volatile & noexcept, void(...) const volatile & noexcept>();
    test_add_pointer<void(...) const volatile && noexcept, void(...) const volatile && noexcept>();

    test_add_pointer<void(int, ...), void (*)(int, ...)>();
    test_add_pointer<void(int, ...)&, void(int, ...)&>();
    test_add_pointer<void(int, ...)&&, void(int, ...) &&>();
    test_add_pointer<void(int, ...) const, void(int, ...) const>();
    test_add_pointer<void(int, ...) const&, void(int, ...) const&>();
    test_add_pointer<void(int, ...) const&&, void(int, ...) const&&>();
    test_add_pointer<void(int, ...) volatile, void(int, ...) volatile>();
    test_add_pointer<void(int, ...) volatile&, void(int, ...) volatile&>();
    test_add_pointer<void(int, ...) volatile&&, void(int, ...) volatile&&>();
    test_add_pointer<void(int, ...) const volatile, void(int, ...) const volatile>();
    test_add_pointer<void(int, ...) const volatile&, void(int, ...) const volatile&>();
    test_add_pointer<void(int, ...) const volatile&&, void(int, ...) const volatile&&>();
    test_add_pointer<void(int, ...) noexcept, void (*)(int, ...) noexcept>();
    test_add_pointer<void(int, ...) & noexcept, void(int, ...) & noexcept>();
    test_add_pointer<void(int, ...) && noexcept, void(int, ...) && noexcept>();
    test_add_pointer<void(int, ...) const noexcept, void(int, ...) const noexcept>();
    test_add_pointer<void(int, ...) const & noexcept, void(int, ...) const & noexcept>();
    test_add_pointer<void(int, ...) const && noexcept, void(int, ...) const && noexcept>();
    test_add_pointer<void(int, ...) volatile noexcept, void(int, ...) volatile noexcept>();
    test_add_pointer<void(int, ...) volatile & noexcept, void(int, ...) volatile & noexcept>();
    test_add_pointer<void(int, ...) volatile && noexcept, void(int, ...) volatile && noexcept>();
    test_add_pointer<void(int, ...) const volatile noexcept,
                     void(int, ...) const volatile noexcept>();
    test_add_pointer<void(int, ...) const volatile & noexcept,
                     void(int, ...) const volatile & noexcept>();
    test_add_pointer<void(int, ...) const volatile && noexcept,
                     void(int, ...) const volatile && noexcept>();

    test_add_pointer<int(), int (*)()>();
    test_add_pointer<int()&, int()&>();
    test_add_pointer<int()&&, int() &&>();
    test_add_pointer<int() const, int() const>();
    test_add_pointer<int() const&, int() const&>();
    test_add_pointer<int() const&&, int() const&&>();
    test_add_pointer<int() volatile, int() volatile>();
    test_add_pointer<int() volatile&, int() volatile&>();
    test_add_pointer<int() volatile&&, int() volatile&&>();
    test_add_pointer<int() const volatile, int() const volatile>();
    test_add_pointer<int() const volatile&, int() const volatile&>();
    test_add_pointer<int() const volatile&&, int() const volatile&&>();
    test_add_pointer<int() noexcept, int (*)() noexcept>();
    test_add_pointer<int() & noexcept, int() & noexcept>();
    test_add_pointer<int() && noexcept, int() && noexcept>();
    test_add_pointer<int() const noexcept, int() const noexcept>();
    test_add_pointer<int() const & noexcept, int() const & noexcept>();
    test_add_pointer<int() const && noexcept, int() const && noexcept>();
    test_add_pointer<int() volatile noexcept, int() volatile noexcept>();
    test_add_pointer<int() volatile & noexcept, int() volatile & noexcept>();
    test_add_pointer<int() volatile && noexcept, int() volatile && noexcept>();
    test_add_pointer<int() const volatile noexcept, int() const volatile noexcept>();
    test_add_pointer<int() const volatile & noexcept, int() const volatile & noexcept>();
    test_add_pointer<int() const volatile && noexcept, int() const volatile && noexcept>();

    test_add_pointer<int(int), int (*)(int)>();
    test_add_pointer<int(int)&, int(int)&>();
    test_add_pointer<int(int)&&, int(int) &&>();
    test_add_pointer<int(int) const, int(int) const>();
    test_add_pointer<int(int) const&, int(int) const&>();
    test_add_pointer<int(int) const&&, int(int) const&&>();
    test_add_pointer<int(int) volatile, int(int) volatile>();
    test_add_pointer<int(int) volatile&, int(int) volatile&>();
    test_add_pointer<int(int) volatile&&, int(int) volatile&&>();
    test_add_pointer<int(int) const volatile, int(int) const volatile>();
    test_add_pointer<int(int) const volatile&, int(int) const volatile&>();
    test_add_pointer<int(int) const volatile&&, int(int) const volatile&&>();
    test_add_pointer<int(int) noexcept, int (*)(int) noexcept>();
    test_add_pointer<int(int) & noexcept, int(int) & noexcept>();
    test_add_pointer<int(int) && noexcept, int(int) && noexcept>();
    test_add_pointer<int(int) const noexcept, int(int) const noexcept>();
    test_add_pointer<int(int) const & noexcept, int(int) const & noexcept>();
    test_add_pointer<int(int) const && noexcept, int(int) const && noexcept>();
    test_add_pointer<int(int) volatile noexcept, int(int) volatile noexcept>();
    test_add_pointer<int(int) volatile & noexcept, int(int) volatile & noexcept>();
    test_add_pointer<int(int) volatile && noexcept, int(int) volatile && noexcept>();
    test_add_pointer<int(int) const volatile noexcept, int(int) const volatile noexcept>();
    test_add_pointer<int(int) const volatile & noexcept, int(int) const volatile & noexcept>();
    test_add_pointer<int(int) const volatile && noexcept, int(int) const volatile && noexcept>();

    test_add_pointer<int(...), int (*)(...)>();
    test_add_pointer<int(...)&, int(...)&>();
    test_add_pointer<int(...)&&, int(...) &&>();
    test_add_pointer<int(...) const, int(...) const>();
    test_add_pointer<int(...) const&, int(...) const&>();
    test_add_pointer<int(...) const&&, int(...) const&&>();
    test_add_pointer<int(...) volatile, int(...) volatile>();
    test_add_pointer<int(...) volatile&, int(...) volatile&>();
    test_add_pointer<int(...) volatile&&, int(...) volatile&&>();
    test_add_pointer<int(...) const volatile, int(...) const volatile>();
    test_add_pointer<int(...) const volatile&, int(...) const volatile&>();
    test_add_pointer<int(...) const volatile&&, int(...) const volatile&&>();
    test_add_pointer<int(...) noexcept, int (*)(...) noexcept>();
    test_add_pointer<int(...) & noexcept, int(...) & noexcept>();
    test_add_pointer<int(...) && noexcept, int(...) && noexcept>();
    test_add_pointer<int(...) const noexcept, int(...) const noexcept>();
    test_add_pointer<int(...) const & noexcept, int(...) const & noexcept>();
    test_add_pointer<int(...) const && noexcept, int(...) const && noexcept>();
    test_add_pointer<int(...) volatile noexcept, int(...) volatile noexcept>();
    test_add_pointer<int(...) volatile & noexcept, int(...) volatile & noexcept>();
    test_add_pointer<int(...) volatile && noexcept, int(...) volatile && noexcept>();
    test_add_pointer<int(...) const volatile noexcept, int(...) const volatile noexcept>();
    test_add_pointer<int(...) const volatile & noexcept, int(...) const volatile & noexcept>();
    test_add_pointer<int(...) const volatile && noexcept, int(...) const volatile && noexcept>();

    test_add_pointer<int(int, ...), int (*)(int, ...)>();
    test_add_pointer<int(int, ...)&, int(int, ...)&>();
    test_add_pointer<int(int, ...)&&, int(int, ...) &&>();
    test_add_pointer<int(int, ...) const, int(int, ...) const>();
    test_add_pointer<int(int, ...) const&, int(int, ...) const&>();
    test_add_pointer<int(int, ...) const&&, int(int, ...) const&&>();
    test_add_pointer<int(int, ...) volatile, int(int, ...) volatile>();
    test_add_pointer<int(int, ...) volatile&, int(int, ...) volatile&>();
    test_add_pointer<int(int, ...) volatile&&, int(int, ...) volatile&&>();
    test_add_pointer<int(int, ...) const volatile, int(int, ...) const volatile>();
    test_add_pointer<int(int, ...) const volatile&, int(int, ...) const volatile&>();
    test_add_pointer<int(int, ...) const volatile&&, int(int, ...) const volatile&&>();
    test_add_pointer<int(int, ...) noexcept, int (*)(int, ...) noexcept>();
    test_add_pointer<int(int, ...) & noexcept, int(int, ...) & noexcept>();
    test_add_pointer<int(int, ...) && noexcept, int(int, ...) && noexcept>();
    test_add_pointer<int(int, ...) const noexcept, int(int, ...) const noexcept>();
    test_add_pointer<int(int, ...) const & noexcept, int(int, ...) const & noexcept>();
    test_add_pointer<int(int, ...) const && noexcept, int(int, ...) const && noexcept>();
    test_add_pointer<int(int, ...) volatile noexcept, int(int, ...) volatile noexcept>();
    test_add_pointer<int(int, ...) volatile & noexcept, int(int, ...) volatile & noexcept>();
    test_add_pointer<int(int, ...) volatile && noexcept, int(int, ...) volatile && noexcept>();
    test_add_pointer<int(int, ...) const volatile noexcept,
                     int(int, ...) const volatile noexcept>();
    test_add_pointer<int(int, ...) const volatile & noexcept,
                     int(int, ...) const volatile & noexcept>();
    test_add_pointer<int(int, ...) const volatile && noexcept,
                     int(int, ...) const volatile && noexcept>();

    test_add_pointer<void (*)()>();
    test_add_pointer<void (*)() noexcept>();

    test_add_pointer<void (*)(int)>();
    test_add_pointer<void (*)(int) noexcept>();

    test_add_pointer<void (*)(...)>();
    test_add_pointer<void (*)(...) noexcept>();

    test_add_pointer<void (*)(int, ...)>();
    test_add_pointer<void (*)(int, ...) noexcept>();

    test_add_pointer<int (*)()>();
    test_add_pointer<int (*)() noexcept>();

    test_add_pointer<int (*)(int)>();
    test_add_pointer<int (*)(int) noexcept>();

    test_add_pointer<int (*)(...)>();
    test_add_pointer<int (*)(...) noexcept>();

    test_add_pointer<int (*)(int, ...)>();
    test_add_pointer<int (*)(int, ...) noexcept>();

    test_add_pointer<void (&)(), void (*)()>();
    test_add_pointer<void (&)() noexcept, void (*)() noexcept>();

    test_add_pointer<void (&)(int), void (*)(int)>();
    test_add_pointer<void (&)(int) noexcept, void (*)(int) noexcept>();

    test_add_pointer<void (&)(...), void (*)(...)>();
    test_add_pointer<void (&)(...) noexcept, void (*)(...) noexcept>();

    test_add_pointer<void (&)(int, ...), void (*)(int, ...)>();
    test_add_pointer<void (&)(int, ...) noexcept, void (*)(int, ...) noexcept>();

    test_add_pointer<int (&)(), int (*)()>();
    test_add_pointer<int (&)() noexcept, int (*)() noexcept>();

    test_add_pointer<int (&)(int), int (*)(int)>();
    test_add_pointer<int (&)(int) noexcept, int (*)(int) noexcept>();

    test_add_pointer<int (&)(...), int (*)(...)>();
    test_add_pointer<int (&)(...) noexcept, int (*)(...) noexcept>();

    test_add_pointer<int (&)(int, ...), int (*)(int, ...)>();
    test_add_pointer<int (&)(int, ...) noexcept, int (*)(int, ...) noexcept>();

    test_add_pointer<void (&&)(), void (*)()>();
    test_add_pointer<void (&&)() noexcept, void (*)() noexcept>();

    test_add_pointer<void (&&)(int), void (*)(int)>();
    test_add_pointer<void (&&)(int) noexcept, void (*)(int) noexcept>();

    test_add_pointer<void (&&)(...), void (*)(...)>();
    test_add_pointer<void (&&)(...) noexcept, void (*)(...) noexcept>();

    test_add_pointer<void (&&)(int, ...), void (*)(int, ...)>();
    test_add_pointer<void (&&)(int, ...) noexcept, void (*)(int, ...) noexcept>();

    test_add_pointer<int (&&)(), int (*)()>();
    test_add_pointer<int (&&)() noexcept, int (*)() noexcept>();

    test_add_pointer<int (&&)(int), int (*)(int)>();
    test_add_pointer<int (&&)(int) noexcept, int (*)(int) noexcept>();

    test_add_pointer<int (&&)(...), int (*)(...)>();
    test_add_pointer<int (&&)(...) noexcept, int (*)(...) noexcept>();

    test_add_pointer<int (&&)(int, ...), int (*)(int, ...)>();
    test_add_pointer<int (&&)(int, ...) noexcept, int (*)(int, ...) noexcept>();

    test_add_pointer<void (class_type::*)()>();
    test_add_pointer<void (class_type::*)()&>();
    test_add_pointer<void (class_type::*)() &&>();
    test_add_pointer<void (class_type::*)() const>();
    test_add_pointer<void (class_type::*)() const&>();
    test_add_pointer<void (class_type::*)() const&&>();
    test_add_pointer<void (class_type::*)() noexcept>();
    test_add_pointer<void (class_type::*)() & noexcept>();
    test_add_pointer<void (class_type::*)() && noexcept>();
    test_add_pointer<void (class_type::*)() const noexcept>();
    test_add_pointer<void (class_type::*)() const & noexcept>();
    test_add_pointer<void (class_type::*)() const && noexcept>();

    test_add_pointer<void (class_type::*)(int)>();
    test_add_pointer<void (class_type::*)(int)&>();
    test_add_pointer<void (class_type::*)(int) &&>();
    test_add_pointer<void (class_type::*)(int) const>();
    test_add_pointer<void (class_type::*)(int) const&>();
    test_add_pointer<void (class_type::*)(int) const&&>();
    test_add_pointer<void (class_type::*)(int) noexcept>();
    test_add_pointer<void (class_type::*)(int) & noexcept>();
    test_add_pointer<void (class_type::*)(int) && noexcept>();
    test_add_pointer<void (class_type::*)(int) const noexcept>();
    test_add_pointer<void (class_type::*)(int) const & noexcept>();
    test_add_pointer<void (class_type::*)(int) const && noexcept>();

    test_add_pointer<void (class_type::*)(...)>();
    test_add_pointer<void (class_type::*)(...)&>();
    test_add_pointer<void (class_type::*)(...) &&>();
    test_add_pointer<void (class_type::*)(...) const>();
    test_add_pointer<void (class_type::*)(...) const&>();
    test_add_pointer<void (class_type::*)(...) const&&>();
    test_add_pointer<void (class_type::*)(...) noexcept>();
    test_add_pointer<void (class_type::*)(...) & noexcept>();
    test_add_pointer<void (class_type::*)(...) && noexcept>();
    test_add_pointer<void (class_type::*)(...) const noexcept>();
    test_add_pointer<void (class_type::*)(...) const & noexcept>();
    test_add_pointer<void (class_type::*)(...) const && noexcept>();

    test_add_pointer<void (class_type::*)(int, ...)>();
    test_add_pointer<void (class_type::*)(int, ...)&>();
    test_add_pointer<void (class_type::*)(int, ...) &&>();
    test_add_pointer<void (class_type::*)(int, ...) const>();
    test_add_pointer<void (class_type::*)(int, ...) const&>();
    test_add_pointer<void (class_type::*)(int, ...) const&&>();
    test_add_pointer<void (class_type::*)(int, ...) noexcept>();
    test_add_pointer<void (class_type::*)(int, ...) & noexcept>();
    test_add_pointer<void (class_type::*)(int, ...) && noexcept>();
    test_add_pointer<void (class_type::*)(int, ...) const noexcept>();
    test_add_pointer<void (class_type::*)(int, ...) const & noexcept>();
    test_add_pointer<void (class_type::*)(int, ...) const && noexcept>();

    test_add_pointer<int (class_type::*)()>();
    test_add_pointer<int (class_type::*)()&>();
    test_add_pointer<int (class_type::*)() &&>();
    test_add_pointer<int (class_type::*)() const>();
    test_add_pointer<int (class_type::*)() const&>();
    test_add_pointer<int (class_type::*)() const&&>();
    test_add_pointer<int (class_type::*)() noexcept>();
    test_add_pointer<int (class_type::*)() & noexcept>();
    test_add_pointer<int (class_type::*)() && noexcept>();
    test_add_pointer<int (class_type::*)() const noexcept>();
    test_add_pointer<int (class_type::*)() const & noexcept>();
    test_add_pointer<int (class_type::*)() const && noexcept>();

    test_add_pointer<int (class_type::*)(int)>();
    test_add_pointer<int (class_type::*)(int)&>();
    test_add_pointer<int (class_type::*)(int) &&>();
    test_add_pointer<int (class_type::*)(int) const>();
    test_add_pointer<int (class_type::*)(int) const&>();
    test_add_pointer<int (class_type::*)(int) const&&>();
    test_add_pointer<int (class_type::*)(int) noexcept>();
    test_add_pointer<int (class_type::*)(int) & noexcept>();
    test_add_pointer<int (class_type::*)(int) && noexcept>();
    test_add_pointer<int (class_type::*)(int) const noexcept>();
    test_add_pointer<int (class_type::*)(int) const & noexcept>();
    test_add_pointer<int (class_type::*)(int) const && noexcept>();

    test_add_pointer<int (class_type::*)(...)>();
    test_add_pointer<int (class_type::*)(...)&>();
    test_add_pointer<int (class_type::*)(...) &&>();
    test_add_pointer<int (class_type::*)(...) const>();
    test_add_pointer<int (class_type::*)(...) const&>();
    test_add_pointer<int (class_type::*)(...) const&&>();
    test_add_pointer<int (class_type::*)(...) noexcept>();
    test_add_pointer<int (class_type::*)(...) & noexcept>();
    test_add_pointer<int (class_type::*)(...) && noexcept>();
    test_add_pointer<int (class_type::*)(...) const noexcept>();
    test_add_pointer<int (class_type::*)(...) const & noexcept>();
    test_add_pointer<int (class_type::*)(...) const && noexcept>();

    test_add_pointer<int (class_type::*)(int, ...)>();
    test_add_pointer<int (class_type::*)(int, ...)&>();
    test_add_pointer<int (class_type::*)(int, ...) &&>();
    test_add_pointer<int (class_type::*)(int, ...) const>();
    test_add_pointer<int (class_type::*)(int, ...) const&>();
    test_add_pointer<int (class_type::*)(int, ...) const&&>();
    test_add_pointer<int (class_type::*)(int, ...) noexcept>();
    test_add_pointer<int (class_type::*)(int, ...) & noexcept>();
    test_add_pointer<int (class_type::*)(int, ...) && noexcept>();
    test_add_pointer<int (class_type::*)(int, ...) const noexcept>();
    test_add_pointer<int (class_type::*)(int, ...) const & noexcept>();
    test_add_pointer<int (class_type::*)(int, ...) const && noexcept>();

    //  LWG 2101 specifically talks about add_pointer and functions.
    //  The term of art is "a referenceable type", which a cv- or ref-qualified function is not.
    test_function0<function_ptr>();
    test_function0<void()>();
    test_function1<void() const>();
    test_function1<void()&>();
    test_function1<void() &&>();
    test_function1<void() const&>();
    test_function1<void() const&&>();

    test_function0<void() noexcept>();
    test_function1<void() const noexcept>();
    test_function1<void() & noexcept>();
    test_function1<void() && noexcept>();
    test_function1<void() const & noexcept>();
    test_function1<void() const && noexcept>();

    //  But a cv- or ref-qualified member function *is* "a referenceable type"
    test_function0<member_function_ptr>();
    test_function0<void (Foo::*)()>();
    test_function0<void (Foo::*)() const>();
    test_function0<void (Foo::*)()&>();
    test_function0<void (Foo::*)() &&>();
    test_function0<void (Foo::*)() const&>();
    test_function0<void (Foo::*)() const&&>();

    test_function0<void (Foo::*)() noexcept>();
    test_function0<void (Foo::*)() const noexcept>();
    test_function0<void (Foo::*)() & noexcept>();
    test_function0<void (Foo::*)() && noexcept>();
    test_function0<void (Foo::*)() const & noexcept>();
    test_function0<void (Foo::*)() const && noexcept>();
}
