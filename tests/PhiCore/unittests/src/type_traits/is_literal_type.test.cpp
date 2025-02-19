#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/compiler_support/compiler.hpp>
#include <phi/compiler_support/cpp_standard.hpp>
#include <phi/compiler_support/warning.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_literal_type.hpp>
#include <type_traits>
#include <vector>

PHI_CLANG_AND_GCC_SUPPRESS_WARNING_PUSH()
PHI_CLANG_AND_GCC_SUPPRESS_WARNING(
        "-Wdeprecated-declarations") // is_literal_type was deprecated in C++-17 and removed in C++-20

PHI_MSVC_SUPPRESS_WARNING_PUSH()
PHI_MSVC_SUPPRESS_WARNING(
        4996) // 'std::is_literal_type<TypeT>': warning STL4013: std::is_literal_type and std::is_literal_type_v are deprecated in C++17. You can define _SILENCE_CXX17_IS_LITERAL_TYPE_DEPRECATION_WARNING or _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS to acknowledge that you have received this warning.

template <typename TypeT>
void test_is_literal_type_impl()
{
#if PHI_HAS_WORKING_IS_LITERAL_TYPE()
    STATIC_REQUIRE(phi::is_literal_type<TypeT>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_literal_type<TypeT>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_literal_type_v<TypeT>);
    STATIC_REQUIRE_FALSE(phi::is_not_literal_type_v<TypeT>);
#    endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_literal_type<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_literal_type<TypeT>);

    // Standard compatibility
#    if PHI_CPP_STANDARD_IS_BELOW(20)
    STATIC_REQUIRE(std::is_literal_type<TypeT>::value);
#    endif
#endif
}

template <typename TypeT>
void test_is_not_literal_type_impl()
{
#if PHI_HAS_WORKING_IS_LITERAL_TYPE()
    STATIC_REQUIRE_FALSE(phi::is_literal_type<TypeT>::value);
    STATIC_REQUIRE(phi::is_not_literal_type<TypeT>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_literal_type_v<TypeT>);
    STATIC_REQUIRE(phi::is_not_literal_type_v<TypeT>);
#    endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_literal_type<TypeT>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_literal_type<TypeT>);

    // Standard compatibility
#    if PHI_CPP_STANDARD_IS_BELOW(20)
    STATIC_REQUIRE_FALSE(std::is_literal_type<TypeT>::value);
#    endif
#endif
}

PHI_MSVC_SUPPRESS_WARNING_POP()
PHI_CLANG_AND_GCC_SUPPRESS_WARNING_POP()

template <typename TypeT>
void test_is_literal_type()
{
    test_is_literal_type_impl<TypeT>();
    test_is_literal_type_impl<const TypeT>();
    test_is_literal_type_impl<volatile TypeT>();
    test_is_literal_type_impl<const volatile TypeT>();
}

template <typename TypeT>
void test_is_not_literal_type()
{
    test_is_not_literal_type_impl<TypeT>();
    test_is_not_literal_type_impl<const TypeT>();
    test_is_not_literal_type_impl<volatile TypeT>();
    test_is_not_literal_type_impl<const volatile TypeT>();
}

template <typename TypeT>
void test_is_literal_type_cxx23()
{
#if PHI_CPP_STANDARD_IS_ATLEAST(23)
    test_is_literal_type<TypeT>();
#else
    test_is_not_literal_type<TypeT>();
#endif
}

template <typename TypeT>
void test_is_literal_type_cxx20()
{
#if PHI_CPP_STANDARD_IS_ATLEAST(20)
    test_is_literal_type<TypeT>();
#else
    test_is_not_literal_type<TypeT>();
#endif
}

template <typename TypeT>
void test_is_literal_type_cxx17()
{
#if PHI_CPP_STANDARD_IS_ATLEAST(17)
    test_is_literal_type<TypeT>();
#else
    test_is_not_literal_type<TypeT>();
#endif
}

template <typename TypeT>
void test_is_not_literal_type_cxx23()
{
#if PHI_CPP_STANDARD_IS_ATLEAST(23)
    test_is_not_literal_type<TypeT>();
#else
    test_is_literal_type<TypeT>();
#endif
}

template <typename TypeT>
void test_is_not_literal_type_cxx20()
{
#if PHI_CPP_STANDARD_IS_ATLEAST(20)
    test_is_not_literal_type<TypeT>();
#else
    test_is_literal_type<TypeT>();
#endif
}

struct A
{
    int m;
};

struct B
{
    virtual ~B();
};

TEST_CASE("is_literal_type")
{
    test_is_literal_type<A>();
    test_is_not_literal_type<B>();

#if PHI_CPP_STANDARD_IS_ATLEAST(14)
    // In C++14, cv-void is a literal type
    test_is_literal_type<void>();
#else
    // Before C++-14, void was not a literal type
    test_is_not_literal_type<void>();
#endif
    test_is_literal_type<phi::nullptr_t>();
    test_is_literal_type<bool>();
    test_is_literal_type<char>();
    test_is_literal_type<signed char>();
    test_is_literal_type<unsigned char>();
    test_is_literal_type<short>();
    test_is_literal_type<unsigned short>();
    test_is_literal_type<int>();
    test_is_literal_type<unsigned int>();
    test_is_literal_type<long>();
    test_is_literal_type<unsigned long>();
    test_is_literal_type<long long>();
    test_is_literal_type<unsigned long long>();
    test_is_literal_type<float>();
    test_is_literal_type<double>();
    test_is_literal_type<long double>();
    test_is_literal_type<char8_t>();
    test_is_literal_type<char16_t>();
    test_is_literal_type<char32_t>();
    test_is_literal_type<wchar_t>();

    test_is_literal_type<phi::boolean>();
    test_is_literal_type<phi::integer<signed char>>();
    test_is_literal_type<phi::integer<unsigned char>>();
    test_is_literal_type<phi::integer<short>>();
    test_is_literal_type<phi::integer<unsigned short>>();
    test_is_literal_type<phi::integer<int>>();
    test_is_literal_type<phi::integer<unsigned int>>();
    test_is_literal_type<phi::integer<long>>();
    test_is_literal_type<phi::integer<unsigned long>>();
    test_is_literal_type<phi::integer<long long>>();
    test_is_literal_type<phi::integer<unsigned long long>>();
    test_is_literal_type<phi::floating_point<float>>();
    test_is_literal_type<phi::floating_point<double>>();
    test_is_literal_type<phi::floating_point<long double>>();

#if PHI_COMPILER_IS(WINCLANG) || PHI_COMPILER_IS(MSVC)
    SKIP_CHECK();
#else
    SKIP_CHECK();
    //test_is_not_literal_type<std::vector<int>>();
#endif
#if PHI_COMPILER_IS_BELOW(CLANG, 10, 0, 0) || PHI_COMPILER_IS_BELOW(GCC, 10, 0, 0) ||              \
        PHI_COMPILER_IS_BELOW(APPLECLANG, 12, 0, 0)
    test_is_not_literal_type<phi::scope_ptr<int>>();
#else
    test_is_literal_type_cxx20<phi::scope_ptr<int>>();
#endif

    test_is_literal_type<int&>();
    test_is_literal_type<const int&>();
    test_is_literal_type<volatile int&>();
    test_is_literal_type<const volatile int&>();
    test_is_literal_type<int&&>();
    test_is_literal_type<const int&&>();
    test_is_literal_type<volatile int&&>();
    test_is_literal_type<const volatile int&&>();
    test_is_literal_type<int*>();
    test_is_literal_type<const int*>();
    test_is_literal_type<volatile int*>();
    test_is_literal_type<const volatile int*>();
    test_is_literal_type<int**>();
    test_is_literal_type<const int**>();
    test_is_literal_type<volatile int**>();
    test_is_literal_type<const volatile int**>();
    test_is_literal_type<int*&>();
    test_is_literal_type<const int*&>();
    test_is_literal_type<volatile int*&>();
    test_is_literal_type<const volatile int*&>();
    test_is_literal_type<int*&&>();
    test_is_literal_type<const int*&&>();
    test_is_literal_type<volatile int*&&>();
    test_is_literal_type<const volatile int*&&>();
    test_is_literal_type<void*>();
    test_is_literal_type<char[3]>();
    test_is_literal_type<char[]>();
    test_is_literal_type<char* [3]>();
    test_is_literal_type<char*[]>();
    test_is_literal_type<int(*)[3]>();
    test_is_literal_type<int(*)[]>();
    test_is_literal_type<int(&)[3]>();
    test_is_literal_type<int(&)[]>();
    test_is_literal_type<int(&&)[3]>();
    test_is_literal_type<int(&&)[]>();
    test_is_literal_type<char[3][2]>();
    test_is_literal_type<char[][2]>();
    test_is_literal_type<char* [3][2]>();
    test_is_literal_type<char*[][2]>();
    test_is_literal_type<int(*)[3][2]>();
    test_is_literal_type<int(*)[][2]>();
    test_is_literal_type<int(&)[3][2]>();
    test_is_literal_type<int(&)[][2]>();
    test_is_literal_type<int(&&)[3][2]>();
    test_is_literal_type<int(&&)[][2]>();
    test_is_not_literal_type<class_type>();
    test_is_not_literal_type<class_type[]>();
    test_is_not_literal_type<class_type[2]>();
    test_is_literal_type<template_type<void>>();
    test_is_literal_type<template_type<int>>();
    test_is_literal_type<template_type<class_type>>();
    test_is_literal_type<template_type<incomplete_type>>();
    test_is_literal_type<variadic_template<>>();
    test_is_literal_type<variadic_template<void>>();
    test_is_literal_type<variadic_template<int>>();
    test_is_literal_type<variadic_template<class_type>>();
    test_is_literal_type<variadic_template<incomplete_type>>();
    test_is_literal_type<variadic_template<int, void, class_type, volatile char[]>>();
    test_is_literal_type<public_derived_from<base>>();
    test_is_literal_type<public_derived_from<derived>>();
    test_is_not_literal_type<public_derived_from<class_type>>();
    test_is_literal_type<private_derived_from<base>>();
    test_is_literal_type<private_derived_from<derived>>();
    test_is_not_literal_type<private_derived_from<class_type>>();
    test_is_literal_type<protected_derived_from<base>>();
    test_is_literal_type<protected_derived_from<derived>>();
    test_is_not_literal_type<protected_derived_from<class_type>>();
#if PHI_COMPILER_IS(GCC) || PHI_COMPILER_IS(MINGW) || PHI_COMPILER_IS(MSVC)
    test_is_literal_type<virtual_derived_from<base>>();
    test_is_literal_type<virtual_derived_from<derived>>();
#else
    test_is_not_literal_type<virtual_derived_from<base>>();
    test_is_not_literal_type<virtual_derived_from<derived>>();
#endif
    test_is_not_literal_type<virtual_derived_from<class_type>>();
    test_is_literal_type<union_type>();
    test_is_literal_type<non_empty_union>();
#if PHI_COMPILER_IS_ATLEAST(CLANG, 19, 0, 0) || PHI_COMPILER_IS_ATLEAST(EMCC, 3, 1, 56)
    test_is_literal_type_cxx23<non_trivial_union>();
#elif PHI_COMPILER_IS_ATLEAST(GCC, 10, 0, 0) || PHI_COMPILER_IS(MINGW)
    test_is_literal_type_cxx20<non_trivial_union>();
#elif PHI_COMPILER_IS(MSVC)
    test_is_literal_type_cxx17<non_trivial_union>();
#else
    test_is_not_literal_type<non_trivial_union>();
#endif
    test_is_literal_type<empty>();
    test_is_not_literal_type<not_empty>();
    test_is_not_literal_type<non_trivial>();
    test_is_literal_type<bit_zero>();
    test_is_literal_type<bit_one>();
    test_is_literal_type<base>();
    test_is_literal_type<derived>();
    test_is_not_literal_type<non_empty_base>();
    test_is_literal_type<empty_base>();
#if PHI_COMPILER_IS(GCC) || PHI_COMPILER_IS(MINGW) || PHI_COMPILER_IS(MSVC)
    test_is_literal_type<virtual_base>();
#else
    test_is_not_literal_type<virtual_base>();
#endif
    test_is_literal_type<polymorphic>();
    test_is_literal_type<derived_polymorphic>();
    test_is_not_literal_type<abstract>();
#if PHI_COMPILER_IS_BELOW(CLANG, 10, 0, 0) || PHI_COMPILER_IS_BELOW(GCC, 10, 0, 0) ||              \
        PHI_COMPILER_IS_BELOW(APPLECLANG, 12, 0, 0)
    test_is_not_literal_type<public_abstract>();
    test_is_not_literal_type<private_abstract>();
    test_is_not_literal_type<protected_abstract>();
#else
    test_is_literal_type_cxx20<public_abstract>();
    test_is_literal_type_cxx20<private_abstract>();
    test_is_literal_type_cxx20<protected_abstract>();
#endif
    test_is_not_literal_type<abstract_template<int>>();
    test_is_literal_type<abstract_template<double>>();
    test_is_not_literal_type<abstract_template<class_type>>();
    test_is_not_literal_type<abstract_template<incomplete_type>>();
#if PHI_COMPILER_IS(GCC) || PHI_COMPILER_IS(MINGW) || PHI_COMPILER_IS(MSVC) ||                     \
        PHI_COMPILER_IS_BELOW(CLANG, 10, 0, 0) || PHI_COMPILER_IS_BELOW(APPLECLANG, 12, 0, 0)
    test_is_literal_type<public_abstract_deleted_destructor>();
    test_is_literal_type<protected_abstract_deleted_destructor>();
    test_is_literal_type<private_abstract_deleted_destructor>();
#else
    test_is_not_literal_type_cxx20<public_abstract_deleted_destructor>();
    test_is_not_literal_type_cxx20<protected_abstract_deleted_destructor>();
    test_is_not_literal_type_cxx20<private_abstract_deleted_destructor>();
#endif
    test_is_literal_type<final_type>();
    test_is_literal_type<final_derived>();
    test_is_literal_type<public_destructor>();
    test_is_literal_type<protected_destructor>();
    test_is_literal_type<private_destructor>();
#if PHI_COMPILER_IS_BELOW(CLANG, 10, 0, 0) || PHI_COMPILER_IS_BELOW(GCC, 10, 0, 0) ||              \
        PHI_COMPILER_IS_BELOW(APPLECLANG, 12, 0, 0)
    test_is_not_literal_type<virtual_public_destructor>();
    test_is_not_literal_type<virtual_protected_destructor>();
    test_is_not_literal_type<virtual_private_destructor>();
#else
    test_is_literal_type_cxx20<virtual_public_destructor>();
    test_is_literal_type_cxx20<virtual_protected_destructor>();
    test_is_literal_type_cxx20<virtual_private_destructor>();
#endif
    test_is_not_literal_type<pure_public_destructor>();
    test_is_not_literal_type<pure_protected_destructor>();
    test_is_not_literal_type<pure_private_destructor>();
#if PHI_COMPILER_IS(GCC) || PHI_COMPILER_IS(MINGW) || PHI_COMPILER_IS(MSVC) ||                     \
        PHI_COMPILER_IS_BELOW(CLANG, 10, 0, 0) || PHI_COMPILER_IS_BELOW(APPLECLANG, 12, 0, 0)
    test_is_literal_type<deleted_public_destructor>();
    test_is_literal_type<deleted_protected_destructor>();
    test_is_literal_type<deleted_private_destructor>();
#else
    test_is_not_literal_type_cxx20<deleted_public_destructor>();
    test_is_not_literal_type_cxx20<deleted_protected_destructor>();
    test_is_not_literal_type_cxx20<deleted_private_destructor>();
#endif
#if PHI_COMPILER_IS(MSVC)
    test_is_literal_type<deleted_virtual_public_destructor>();
    test_is_literal_type<deleted_virtual_protected_destructor>();
    test_is_literal_type<deleted_virtual_private_destructor>();
#elif PHI_COMPILER_IS(GCC)
    SKIP_CHECK();
    SKIP_CHECK();
    SKIP_CHECK();
#else
    test_is_not_literal_type<deleted_virtual_public_destructor>();
    test_is_not_literal_type<deleted_virtual_protected_destructor>();
    test_is_not_literal_type<deleted_virtual_private_destructor>();
#endif
    test_is_not_literal_type<explicit_class>();
    test_is_not_literal_type<nothrow_explicit_class>();
    test_is_not_literal_type<throw_explicit_class>();
    test_is_not_literal_type<throw_default_class>();
    test_is_not_literal_type<throw_copy_constructible_class>();
    test_is_not_literal_type<throw_move_constructible_class>();
    test_is_not_literal_type<throw_destructor>();
    test_is_not_literal_type<noexcept_explicit_class>();
    test_is_not_literal_type<except_explicit_class>();
    test_is_not_literal_type<noexcept_default_class>();
    test_is_not_literal_type<except_default_class>();
    test_is_not_literal_type<noexcept_copy_constructible_class>();
    test_is_not_literal_type<except_copy_constructible_class>();
    test_is_not_literal_type<noexcept_move_constructible_class>();
    test_is_not_literal_type<except_move_constructible_class>();
    test_is_literal_type<noexcept_copy_assign_class>();
    test_is_literal_type<except_copy_assign_class>();
#if PHI_COMPILER_IS_BELOW(GCC, 9, 0, 0)
    test_is_literal_type<noexcept_move_assign_class>();
#else
    test_is_not_literal_type_cxx20<noexcept_move_assign_class>();
#endif
    test_is_literal_type<except_move_assign_class>();
    test_is_literal_type<deleted_copy_assign_class>();
    test_is_literal_type<deleted_move_assign_class>();
    test_is_not_literal_type<noexcept_move_constructible_and_assignable_class>();
    test_is_not_literal_type<except_move_constructible_noexcept_move_assign_class>();
    test_is_not_literal_type<noexcept_move_constructible_except_move_assign_class>();
    test_is_not_literal_type<except_move_constructible_and_assign_class>();
    test_is_literal_type<implicit_to<int>>();
    test_is_literal_type<implicit_to<float>>();
    test_is_literal_type<implicit_to<class_type>>();
    test_is_literal_type<deleted_implicit_to<int>>();
    test_is_literal_type<deleted_implicit_to<float>>();
    test_is_literal_type<deleted_implicit_to<class_type>>();
    test_is_literal_type<explicit_to<int>>();
    test_is_literal_type<explicit_to<float>>();
    test_is_literal_type<explicit_to<class_type>>();
    test_is_literal_type<deleted_explicit_to<int>>();
    test_is_literal_type<deleted_explicit_to<float>>();
    test_is_literal_type<deleted_explicit_to<class_type>>();
#if PHI_COMPILER_IS(GCC) || PHI_COMPILER_IS(MINGW)
    // TODO: Fails with gcc-12 in release mode...
    //test_is_not_literal_type<ellipsis>();
    SKIP_CHECK();
    test_is_literal_type<deleted_ellipsis>();
#else
    test_is_not_literal_type<ellipsis>();
    test_is_not_literal_type_cxx20<deleted_ellipsis>();
#endif
#if (PHI_COMPILER_IS(GCC) || PHI_COMPILER_IS(MINGW))
    // TODO: For some reason only fails in Release mode?
    SKIP_CHECK();
    SKIP_CHECK();
    //test_is_not_literal_type<copy_constructible_only_type>();
    //test_is_not_literal_type_cxx23<move_constructible_only_type>();
#else
    test_is_not_literal_type<copy_constructible_only_type>();
    test_is_not_literal_type<move_constructible_only_type>();
#endif
    test_is_literal_type<overloaded_operators>();
    test_is_literal_type<public_int_member>();
    test_is_literal_type<protected_int_member>();
    test_is_literal_type<private_int_member>();
    test_is_literal_type<public_static_int_member>();
    test_is_literal_type<protected_static_int_member>();
    test_is_literal_type<private_static_int_member>();
    test_is_literal_type<public_template_member<int>>();
    test_is_literal_type<public_template_member<float>>();
    test_is_not_literal_type<public_template_member<class_type>>();
    test_is_literal_type<protected_template_member<int>>();
    test_is_literal_type<protected_template_member<float>>();
    test_is_not_literal_type<protected_template_member<class_type>>();
    test_is_literal_type<private_template_member<int>>();
    test_is_literal_type<private_template_member<float>>();
    test_is_not_literal_type<private_template_member<class_type>>();
    test_is_literal_type<public_static_template_member<int>>();
    test_is_literal_type<public_static_template_member<float>>();
    test_is_literal_type<public_static_template_member<class_type>>();
    test_is_literal_type<protected_static_template_member<int>>();
    test_is_literal_type<protected_static_template_member<float>>();
    test_is_literal_type<protected_static_template_member<class_type>>();
    test_is_literal_type<private_static_template_member<int>>();
    test_is_literal_type<private_static_template_member<float>>();
    test_is_literal_type<private_static_template_member<class_type>>();
    test_is_literal_type<Enum>();
    test_is_literal_type<EnumSigned>();
    test_is_literal_type<EnumUnsigned>();
    test_is_literal_type<EnumClass>();
    test_is_literal_type<EnumStruct>();
    test_is_not_literal_type<function_type>();
    test_is_literal_type<function_ptr>();
    test_is_literal_type<member_object_ptr>();
    test_is_literal_type<member_function_ptr>();
    test_is_literal_type_cxx17<lambda_type>();
    test_is_literal_type_cxx17<lambda_noexcept_type>();
    test_is_literal_type_cxx17<lambda_throws_type>();
    test_is_literal_type<IncompleteEnumSigned>();
    test_is_literal_type<IncompleteEnumUnsigned>();
    test_is_literal_type<IncompleteEnumClass>();
    test_is_literal_type<IncompleteEnumStruct>();
    test_is_literal_type<int class_type::*>();
    test_is_literal_type<float class_type::*>();
    test_is_literal_type<void * class_type::*>();
    test_is_literal_type<int * class_type::*>();
    test_is_literal_type<int class_type::*&>();
    test_is_literal_type<float class_type::*&>();
    test_is_literal_type<void * class_type::*&>();
    test_is_literal_type<int * class_type::*&>();
    test_is_literal_type<int class_type::*&&>();
    test_is_literal_type<float class_type::*&&>();
    test_is_literal_type<void * class_type::*&&>();
    test_is_literal_type<int * class_type::*&&>();
    test_is_literal_type<int class_type::* const>();
    test_is_literal_type<float class_type::* const>();
    test_is_literal_type<void * class_type::* const>();
    test_is_literal_type<int class_type::* const&>();
    test_is_literal_type<float class_type::* const&>();
    test_is_literal_type<void * class_type::* const&>();
    test_is_literal_type<int class_type::* const&&>();
    test_is_literal_type<float class_type::* const&&>();
    test_is_literal_type<void * class_type::* const&&>();
    test_is_literal_type<int class_type::* volatile>();
    test_is_literal_type<float class_type::* volatile>();
    test_is_literal_type<void * class_type::* volatile>();
    test_is_literal_type<int class_type::* volatile&>();
    test_is_literal_type<float class_type::* volatile&>();
    test_is_literal_type<void * class_type::* volatile&>();
    test_is_literal_type<int class_type::* volatile&&>();
    test_is_literal_type<float class_type::* volatile&&>();
    test_is_literal_type<void * class_type::* volatile&&>();
    test_is_literal_type<int class_type::* const volatile>();
    test_is_literal_type<float class_type::* const volatile>();
    test_is_literal_type<void * class_type::* const volatile>();
    test_is_literal_type<int class_type::* const volatile&>();
    test_is_literal_type<float class_type::* const volatile&>();
    test_is_literal_type<void * class_type::* const volatile&>();
    test_is_literal_type<int class_type::* const volatile&&>();
    test_is_literal_type<float class_type::* const volatile&&>();
    test_is_literal_type<void * class_type::* const volatile&&>();
#if PHI_COMPILER_IS(MSVC)
    test_is_not_literal_type_cxx20<non_default_constructible>();
#else
    test_is_literal_type<non_default_constructible>();
#endif
    test_is_literal_type<non_copy_constructible>();
    test_is_literal_type<non_move_constructible>();
    test_is_literal_type<non_copy_assignable>();
    test_is_literal_type<non_move_assignable>();
    test_is_literal_type<non_assignable>();
    test_is_literal_type<non_copyable>();
    test_is_literal_type<non_moveable>();
#if PHI_COMPILER_IS(MSVC)
    test_is_not_literal_type_cxx20<non_constructible>();
#else
    test_is_literal_type<non_constructible>();
#endif
#if PHI_COMPILER_IS(GCC) || PHI_COMPILER_IS(MINGW) || PHI_COMPILER_IS(MSVC) ||                     \
        PHI_COMPILER_IS_BELOW(CLANG, 10, 0, 0) || PHI_COMPILER_IS_BELOW(APPLECLANG, 12, 0, 0)
    test_is_literal_type<non_destructible>();
#else
    test_is_not_literal_type_cxx20<non_destructible>();
#endif
#if PHI_COMPILER_IS_BELOW(CLANG, 10, 0, 0) || PHI_COMPILER_IS_BELOW(GCC, 10, 0, 0) ||              \
        PHI_COMPILER_IS_BELOW(APPLECLANG, 12, 0, 0)
    test_is_not_literal_type<tracked>();
#else
    test_is_literal_type_cxx20<tracked>();
#endif
    test_is_literal_type<trap_constructible>();
    test_is_literal_type<trap_implicit_conversion>();
    test_is_literal_type<trap_comma>();
    test_is_literal_type<trap_call>();
    test_is_literal_type<trap_self_assign>();
    test_is_literal_type<trap_deref>();
    test_is_literal_type<trap_array_subscript>();

    test_is_not_literal_type<void()>();
    test_is_not_literal_type<void()&>();
    test_is_not_literal_type<void() &&>();
    test_is_not_literal_type<void() const>();
    test_is_not_literal_type<void() const&>();
    test_is_not_literal_type<void() const&&>();
    test_is_not_literal_type<void() volatile>();
    test_is_not_literal_type<void() volatile&>();
    test_is_not_literal_type<void() volatile&&>();
    test_is_not_literal_type<void() const volatile>();
    test_is_not_literal_type<void() const volatile&>();
    test_is_not_literal_type<void() const volatile&&>();
    test_is_not_literal_type<void() noexcept>();
    test_is_not_literal_type<void() & noexcept>();
    test_is_not_literal_type<void() && noexcept>();
    test_is_not_literal_type<void() const noexcept>();
    test_is_not_literal_type<void() const & noexcept>();
    test_is_not_literal_type<void() const && noexcept>();
    test_is_not_literal_type<void() volatile noexcept>();
    test_is_not_literal_type<void() volatile & noexcept>();
    test_is_not_literal_type<void() volatile && noexcept>();
    test_is_not_literal_type<void() const volatile noexcept>();
    test_is_not_literal_type<void() const volatile & noexcept>();
    test_is_not_literal_type<void() const volatile && noexcept>();

    test_is_not_literal_type<void(int)>();
    test_is_not_literal_type<void(int)&>();
    test_is_not_literal_type<void(int) &&>();
    test_is_not_literal_type<void(int) const>();
    test_is_not_literal_type<void(int) const&>();
    test_is_not_literal_type<void(int) const&&>();
    test_is_not_literal_type<void(int) volatile>();
    test_is_not_literal_type<void(int) volatile&>();
    test_is_not_literal_type<void(int) volatile&&>();
    test_is_not_literal_type<void(int) const volatile>();
    test_is_not_literal_type<void(int) const volatile&>();
    test_is_not_literal_type<void(int) const volatile&&>();
    test_is_not_literal_type<void(int) noexcept>();
    test_is_not_literal_type<void(int) & noexcept>();
    test_is_not_literal_type<void(int) && noexcept>();
    test_is_not_literal_type<void(int) const noexcept>();
    test_is_not_literal_type<void(int) const & noexcept>();
    test_is_not_literal_type<void(int) const && noexcept>();
    test_is_not_literal_type<void(int) volatile noexcept>();
    test_is_not_literal_type<void(int) volatile & noexcept>();
    test_is_not_literal_type<void(int) volatile && noexcept>();
    test_is_not_literal_type<void(int) const volatile noexcept>();
    test_is_not_literal_type<void(int) const volatile & noexcept>();
    test_is_not_literal_type<void(int) const volatile && noexcept>();

    test_is_not_literal_type<void(...)>();
    test_is_not_literal_type<void(...)&>();
    test_is_not_literal_type<void(...) &&>();
    test_is_not_literal_type<void(...) const>();
    test_is_not_literal_type<void(...) const&>();
    test_is_not_literal_type<void(...) const&&>();
    test_is_not_literal_type<void(...) volatile>();
    test_is_not_literal_type<void(...) volatile&>();
    test_is_not_literal_type<void(...) volatile&&>();
    test_is_not_literal_type<void(...) const volatile>();
    test_is_not_literal_type<void(...) const volatile&>();
    test_is_not_literal_type<void(...) const volatile&&>();
    test_is_not_literal_type<void(...) noexcept>();
    test_is_not_literal_type<void(...) & noexcept>();
    test_is_not_literal_type<void(...) && noexcept>();
    test_is_not_literal_type<void(...) const noexcept>();
    test_is_not_literal_type<void(...) const & noexcept>();
    test_is_not_literal_type<void(...) const && noexcept>();
    test_is_not_literal_type<void(...) volatile noexcept>();
    test_is_not_literal_type<void(...) volatile & noexcept>();
    test_is_not_literal_type<void(...) volatile && noexcept>();
    test_is_not_literal_type<void(...) const volatile noexcept>();
    test_is_not_literal_type<void(...) const volatile & noexcept>();
    test_is_not_literal_type<void(...) const volatile && noexcept>();

    test_is_not_literal_type<void(int, ...)>();
    test_is_not_literal_type<void(int, ...)&>();
    test_is_not_literal_type<void(int, ...) &&>();
    test_is_not_literal_type<void(int, ...) const>();
    test_is_not_literal_type<void(int, ...) const&>();
    test_is_not_literal_type<void(int, ...) const&&>();
    test_is_not_literal_type<void(int, ...) volatile>();
    test_is_not_literal_type<void(int, ...) volatile&>();
    test_is_not_literal_type<void(int, ...) volatile&&>();
    test_is_not_literal_type<void(int, ...) const volatile>();
    test_is_not_literal_type<void(int, ...) const volatile&>();
    test_is_not_literal_type<void(int, ...) const volatile&&>();
    test_is_not_literal_type<void(int, ...) noexcept>();
    test_is_not_literal_type<void(int, ...) & noexcept>();
    test_is_not_literal_type<void(int, ...) && noexcept>();
    test_is_not_literal_type<void(int, ...) const noexcept>();
    test_is_not_literal_type<void(int, ...) const & noexcept>();
    test_is_not_literal_type<void(int, ...) const && noexcept>();
    test_is_not_literal_type<void(int, ...) volatile noexcept>();
    test_is_not_literal_type<void(int, ...) volatile & noexcept>();
    test_is_not_literal_type<void(int, ...) volatile && noexcept>();
    test_is_not_literal_type<void(int, ...) const volatile noexcept>();
    test_is_not_literal_type<void(int, ...) const volatile & noexcept>();
    test_is_not_literal_type<void(int, ...) const volatile && noexcept>();

    test_is_not_literal_type<int()>();
    test_is_not_literal_type<int()&>();
    test_is_not_literal_type<int() &&>();
    test_is_not_literal_type<int() const>();
    test_is_not_literal_type<int() const&>();
    test_is_not_literal_type<int() const&&>();
    test_is_not_literal_type<int() volatile>();
    test_is_not_literal_type<int() volatile&>();
    test_is_not_literal_type<int() volatile&&>();
    test_is_not_literal_type<int() const volatile>();
    test_is_not_literal_type<int() const volatile&>();
    test_is_not_literal_type<int() const volatile&&>();
    test_is_not_literal_type<int() noexcept>();
    test_is_not_literal_type<int() & noexcept>();
    test_is_not_literal_type<int() && noexcept>();
    test_is_not_literal_type<int() const noexcept>();
    test_is_not_literal_type<int() const & noexcept>();
    test_is_not_literal_type<int() const && noexcept>();
    test_is_not_literal_type<int() volatile noexcept>();
    test_is_not_literal_type<int() volatile & noexcept>();
    test_is_not_literal_type<int() volatile && noexcept>();
    test_is_not_literal_type<int() const volatile noexcept>();
    test_is_not_literal_type<int() const volatile & noexcept>();
    test_is_not_literal_type<int() const volatile && noexcept>();

    test_is_not_literal_type<int(int)>();
    test_is_not_literal_type<int(int)&>();
    test_is_not_literal_type<int(int) &&>();
    test_is_not_literal_type<int(int) const>();
    test_is_not_literal_type<int(int) const&>();
    test_is_not_literal_type<int(int) const&&>();
    test_is_not_literal_type<int(int) volatile>();
    test_is_not_literal_type<int(int) volatile&>();
    test_is_not_literal_type<int(int) volatile&&>();
    test_is_not_literal_type<int(int) const volatile>();
    test_is_not_literal_type<int(int) const volatile&>();
    test_is_not_literal_type<int(int) const volatile&&>();
    test_is_not_literal_type<int(int) noexcept>();
    test_is_not_literal_type<int(int) & noexcept>();
    test_is_not_literal_type<int(int) && noexcept>();
    test_is_not_literal_type<int(int) const noexcept>();
    test_is_not_literal_type<int(int) const & noexcept>();
    test_is_not_literal_type<int(int) const && noexcept>();
    test_is_not_literal_type<int(int) volatile noexcept>();
    test_is_not_literal_type<int(int) volatile & noexcept>();
    test_is_not_literal_type<int(int) volatile && noexcept>();
    test_is_not_literal_type<int(int) const volatile noexcept>();
    test_is_not_literal_type<int(int) const volatile & noexcept>();
    test_is_not_literal_type<int(int) const volatile && noexcept>();

    test_is_not_literal_type<int(...)>();
    test_is_not_literal_type<int(...)&>();
    test_is_not_literal_type<int(...) &&>();
    test_is_not_literal_type<int(...) const>();
    test_is_not_literal_type<int(...) const&>();
    test_is_not_literal_type<int(...) const&&>();
    test_is_not_literal_type<int(...) volatile>();
    test_is_not_literal_type<int(...) volatile&>();
    test_is_not_literal_type<int(...) volatile&&>();
    test_is_not_literal_type<int(...) const volatile>();
    test_is_not_literal_type<int(...) const volatile&>();
    test_is_not_literal_type<int(...) const volatile&&>();
    test_is_not_literal_type<int(...) noexcept>();
    test_is_not_literal_type<int(...) & noexcept>();
    test_is_not_literal_type<int(...) && noexcept>();
    test_is_not_literal_type<int(...) const noexcept>();
    test_is_not_literal_type<int(...) const & noexcept>();
    test_is_not_literal_type<int(...) const && noexcept>();
    test_is_not_literal_type<int(...) volatile noexcept>();
    test_is_not_literal_type<int(...) volatile & noexcept>();
    test_is_not_literal_type<int(...) volatile && noexcept>();
    test_is_not_literal_type<int(...) const volatile noexcept>();
    test_is_not_literal_type<int(...) const volatile & noexcept>();
    test_is_not_literal_type<int(...) const volatile && noexcept>();

    test_is_not_literal_type<int(int, ...)>();
    test_is_not_literal_type<int(int, ...)&>();
    test_is_not_literal_type<int(int, ...) &&>();
    test_is_not_literal_type<int(int, ...) const>();
    test_is_not_literal_type<int(int, ...) const&>();
    test_is_not_literal_type<int(int, ...) const&&>();
    test_is_not_literal_type<int(int, ...) volatile>();
    test_is_not_literal_type<int(int, ...) volatile&>();
    test_is_not_literal_type<int(int, ...) volatile&&>();
    test_is_not_literal_type<int(int, ...) const volatile>();
    test_is_not_literal_type<int(int, ...) const volatile&>();
    test_is_not_literal_type<int(int, ...) const volatile&&>();
    test_is_not_literal_type<int(int, ...) noexcept>();
    test_is_not_literal_type<int(int, ...) & noexcept>();
    test_is_not_literal_type<int(int, ...) && noexcept>();
    test_is_not_literal_type<int(int, ...) const noexcept>();
    test_is_not_literal_type<int(int, ...) const & noexcept>();
    test_is_not_literal_type<int(int, ...) const && noexcept>();
    test_is_not_literal_type<int(int, ...) volatile noexcept>();
    test_is_not_literal_type<int(int, ...) volatile & noexcept>();
    test_is_not_literal_type<int(int, ...) volatile && noexcept>();
    test_is_not_literal_type<int(int, ...) const volatile noexcept>();
    test_is_not_literal_type<int(int, ...) const volatile & noexcept>();
    test_is_not_literal_type<int(int, ...) const volatile && noexcept>();

    test_is_literal_type<void (*)()>();
    test_is_literal_type<void (*)() noexcept>();

    test_is_literal_type<void (*)(int)>();
    test_is_literal_type<void (*)(int) noexcept>();

    test_is_literal_type<void (*)(...)>();
    test_is_literal_type<void (*)(...) noexcept>();

    test_is_literal_type<void (*)(int, ...)>();
    test_is_literal_type<void (*)(int, ...) noexcept>();

    test_is_literal_type<int (*)()>();
    test_is_literal_type<int (*)() noexcept>();

    test_is_literal_type<int (*)(int)>();
    test_is_literal_type<int (*)(int) noexcept>();

    test_is_literal_type<int (*)(...)>();
    test_is_literal_type<int (*)(...) noexcept>();

    test_is_literal_type<int (*)(int, ...)>();
    test_is_literal_type<int (*)(int, ...) noexcept>();

    test_is_literal_type<void (&)()>();
    test_is_literal_type<void (&)() noexcept>();

    test_is_literal_type<void (&)(int)>();
    test_is_literal_type<void (&)(int) noexcept>();

    test_is_literal_type<void (&)(...)>();
    test_is_literal_type<void (&)(...) noexcept>();

    test_is_literal_type<void (&)(int, ...)>();
    test_is_literal_type<void (&)(int, ...) noexcept>();

    test_is_literal_type<int (&)()>();
    test_is_literal_type<int (&)() noexcept>();

    test_is_literal_type<int (&)(int)>();
    test_is_literal_type<int (&)(int) noexcept>();

    test_is_literal_type<int (&)(...)>();
    test_is_literal_type<int (&)(...) noexcept>();

    test_is_literal_type<int (&)(int, ...)>();
    test_is_literal_type<int (&)(int, ...) noexcept>();

    test_is_literal_type<void (&&)()>();
    test_is_literal_type<void (&&)() noexcept>();

    test_is_literal_type<void (&&)(int)>();
    test_is_literal_type<void (&&)(int) noexcept>();

    test_is_literal_type<void (&&)(...)>();
    test_is_literal_type<void (&&)(...) noexcept>();

    test_is_literal_type<void (&&)(int, ...)>();
    test_is_literal_type<void (&&)(int, ...) noexcept>();

    test_is_literal_type<int (&&)()>();
    test_is_literal_type<int (&&)() noexcept>();

    test_is_literal_type<int (&&)(int)>();
    test_is_literal_type<int (&&)(int) noexcept>();

    test_is_literal_type<int (&&)(...)>();
    test_is_literal_type<int (&&)(...) noexcept>();

    test_is_literal_type<int (&&)(int, ...)>();
    test_is_literal_type<int (&&)(int, ...) noexcept>();

    test_is_literal_type<void (class_type::*)()>();
    test_is_literal_type<void (class_type::*)()&>();
    test_is_literal_type<void (class_type::*)() &&>();
    test_is_literal_type<void (class_type::*)() const>();
    test_is_literal_type<void (class_type::*)() const&>();
    test_is_literal_type<void (class_type::*)() const&&>();
    test_is_literal_type<void (class_type::*)() noexcept>();
    test_is_literal_type<void (class_type::*)() & noexcept>();
    test_is_literal_type<void (class_type::*)() && noexcept>();
    test_is_literal_type<void (class_type::*)() const noexcept>();
    test_is_literal_type<void (class_type::*)() const & noexcept>();
    test_is_literal_type<void (class_type::*)() const && noexcept>();

    test_is_literal_type<void (class_type::*)(int)>();
    test_is_literal_type<void (class_type::*)(int)&>();
    test_is_literal_type<void (class_type::*)(int) &&>();
    test_is_literal_type<void (class_type::*)(int) const>();
    test_is_literal_type<void (class_type::*)(int) const&>();
    test_is_literal_type<void (class_type::*)(int) const&&>();
    test_is_literal_type<void (class_type::*)(int) noexcept>();
    test_is_literal_type<void (class_type::*)(int) & noexcept>();
    test_is_literal_type<void (class_type::*)(int) && noexcept>();
    test_is_literal_type<void (class_type::*)(int) const noexcept>();
    test_is_literal_type<void (class_type::*)(int) const & noexcept>();
    test_is_literal_type<void (class_type::*)(int) const && noexcept>();

    test_is_literal_type<void (class_type::*)(...)>();
    test_is_literal_type<void (class_type::*)(...)&>();
    test_is_literal_type<void (class_type::*)(...) &&>();
    test_is_literal_type<void (class_type::*)(...) const>();
    test_is_literal_type<void (class_type::*)(...) const&>();
    test_is_literal_type<void (class_type::*)(...) const&&>();
    test_is_literal_type<void (class_type::*)(...) noexcept>();
    test_is_literal_type<void (class_type::*)(...) & noexcept>();
    test_is_literal_type<void (class_type::*)(...) && noexcept>();
    test_is_literal_type<void (class_type::*)(...) const noexcept>();
    test_is_literal_type<void (class_type::*)(...) const & noexcept>();
    test_is_literal_type<void (class_type::*)(...) const && noexcept>();

    test_is_literal_type<void (class_type::*)(int, ...)>();
    test_is_literal_type<void (class_type::*)(int, ...)&>();
    test_is_literal_type<void (class_type::*)(int, ...) &&>();
    test_is_literal_type<void (class_type::*)(int, ...) const>();
    test_is_literal_type<void (class_type::*)(int, ...) const&>();
    test_is_literal_type<void (class_type::*)(int, ...) const&&>();
    test_is_literal_type<void (class_type::*)(int, ...) noexcept>();
    test_is_literal_type<void (class_type::*)(int, ...) & noexcept>();
    test_is_literal_type<void (class_type::*)(int, ...) && noexcept>();
    test_is_literal_type<void (class_type::*)(int, ...) const noexcept>();
    test_is_literal_type<void (class_type::*)(int, ...) const & noexcept>();
    test_is_literal_type<void (class_type::*)(int, ...) const && noexcept>();

    test_is_literal_type<int (class_type::*)()>();
    test_is_literal_type<int (class_type::*)()&>();
    test_is_literal_type<int (class_type::*)() &&>();
    test_is_literal_type<int (class_type::*)() const>();
    test_is_literal_type<int (class_type::*)() const&>();
    test_is_literal_type<int (class_type::*)() const&&>();
    test_is_literal_type<int (class_type::*)() noexcept>();
    test_is_literal_type<int (class_type::*)() & noexcept>();
    test_is_literal_type<int (class_type::*)() && noexcept>();
    test_is_literal_type<int (class_type::*)() const noexcept>();
    test_is_literal_type<int (class_type::*)() const & noexcept>();
    test_is_literal_type<int (class_type::*)() const && noexcept>();

    test_is_literal_type<int (class_type::*)(int)>();
    test_is_literal_type<int (class_type::*)(int)&>();
    test_is_literal_type<int (class_type::*)(int) &&>();
    test_is_literal_type<int (class_type::*)(int) const>();
    test_is_literal_type<int (class_type::*)(int) const&>();
    test_is_literal_type<int (class_type::*)(int) const&&>();
    test_is_literal_type<int (class_type::*)(int) noexcept>();
    test_is_literal_type<int (class_type::*)(int) & noexcept>();
    test_is_literal_type<int (class_type::*)(int) && noexcept>();
    test_is_literal_type<int (class_type::*)(int) const noexcept>();
    test_is_literal_type<int (class_type::*)(int) const & noexcept>();
    test_is_literal_type<int (class_type::*)(int) const && noexcept>();

    test_is_literal_type<int (class_type::*)(...)>();
    test_is_literal_type<int (class_type::*)(...)&>();
    test_is_literal_type<int (class_type::*)(...) &&>();
    test_is_literal_type<int (class_type::*)(...) const>();
    test_is_literal_type<int (class_type::*)(...) const&>();
    test_is_literal_type<int (class_type::*)(...) const&&>();
    test_is_literal_type<int (class_type::*)(...) noexcept>();
    test_is_literal_type<int (class_type::*)(...) & noexcept>();
    test_is_literal_type<int (class_type::*)(...) && noexcept>();
    test_is_literal_type<int (class_type::*)(...) const noexcept>();
    test_is_literal_type<int (class_type::*)(...) const & noexcept>();
    test_is_literal_type<int (class_type::*)(...) const && noexcept>();

    test_is_literal_type<int (class_type::*)(int, ...)>();
    test_is_literal_type<int (class_type::*)(int, ...)&>();
    test_is_literal_type<int (class_type::*)(int, ...) &&>();
    test_is_literal_type<int (class_type::*)(int, ...) const>();
    test_is_literal_type<int (class_type::*)(int, ...) const&>();
    test_is_literal_type<int (class_type::*)(int, ...) const&&>();
    test_is_literal_type<int (class_type::*)(int, ...) noexcept>();
    test_is_literal_type<int (class_type::*)(int, ...) & noexcept>();
    test_is_literal_type<int (class_type::*)(int, ...) && noexcept>();
    test_is_literal_type<int (class_type::*)(int, ...) const noexcept>();
    test_is_literal_type<int (class_type::*)(int, ...) const & noexcept>();
    test_is_literal_type<int (class_type::*)(int, ...) const && noexcept>();
}
