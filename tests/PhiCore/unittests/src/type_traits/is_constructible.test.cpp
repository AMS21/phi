#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/bugs/gcc_102305.hpp>
#include <phi/compiler_support/compiler.hpp>
#include <phi/compiler_support/unused.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_constructible.hpp>
#include <type_traits>
#include <vector>

struct A
{
    explicit A(int);
    A(int, double);
    A(int, long, double);

private:
    A(char);
};

struct B
{
    B();
};

// NOLINTNEXTLINE(readability-identifier-naming)
class C
{
    // NOLINTNEXTLINE(modernize-use-equals-delete)
    C();
};

struct D
{
    D() = default;
};

struct E
{
    E() = delete;
};

// NOLINTNEXTLINE(readability-identifier-naming)
class NoDefaultConstructor
{
    NoDefaultConstructor(int /*unused*/)
    {}
};

struct AbstractFunc
{
    virtual ~AbstractFunc();
    virtual void foo() = 0;
};

struct AbstractDestructor
{
    virtual ~AbstractDestructor() = 0;
};

struct PrivateDtor
{
    PrivateDtor(int /*unused*/)
    {}

private:
    // NOLINTNEXTLINE(modernize-use-equals-default)
    ~PrivateDtor()
    {}
};

struct S
{
    template <typename TypeT>
    explicit operator TypeT() const;
};

struct aggressive_aggregate
{
    int a;
    int b;
};

struct vicious_variation
{
    int a;
    int b = 42;
};

struct t_derived;
struct t_base
{
    operator t_derived&() &;
    operator t_derived const&() const&;
    operator t_derived&&() &&;
};

struct t_derived : t_base
{};

inline t_base::operator t_derived&() &
{
    return *static_cast<t_derived*>(this);
}

inline t_base::operator t_derived const&() const&
{
    return *static_cast<t_derived const*>(this);
}

inline t_base::operator t_derived&&() &&
{
    return phi::move(*static_cast<t_derived*>(this));
}

template <typename TypeT>
struct Foo
{
    Foo(TypeT /*unused*/ = nullptr)
    {}
};

template <typename TypeT, typename... ArgsT>
void test_is_constructible()
{
#if PHI_HAS_WORKING_IS_CONSTRUCTIBLE()
    STATIC_REQUIRE(phi::is_constructible<TypeT, ArgsT...>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_constructible<TypeT, ArgsT...>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_constructible_v<TypeT, ArgsT...>);
    STATIC_REQUIRE_FALSE(phi::is_not_constructible_v<TypeT, ArgsT...>);
#    endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_constructible<TypeT, ArgsT...>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_constructible<TypeT, ArgsT...>);

    // Standard compatibility
    STATIC_REQUIRE(std::is_constructible<TypeT, ArgsT...>::value);
#endif
}

template <typename TypeT, typename... ArgsT>
void test_is_not_constructible()
{
#if PHI_HAS_WORKING_IS_CONSTRUCTIBLE()
    STATIC_REQUIRE_FALSE(phi::is_constructible<TypeT, ArgsT...>::value);
    STATIC_REQUIRE(phi::is_not_constructible<TypeT, ArgsT...>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_constructible_v<TypeT, ArgsT...>);
    STATIC_REQUIRE(phi::is_not_constructible_v<TypeT, ArgsT...>);
#    endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_constructible<TypeT, ArgsT...>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_constructible<TypeT, ArgsT...>);

    // Standard compatibility
    STATIC_REQUIRE_FALSE(std::is_constructible<TypeT, ArgsT...>::value);
#endif
}

TEST_CASE("is_constructible")
{
    test_is_constructible<int, int>();
    test_is_constructible<int, const int>();
    test_is_constructible<A, int>();
    test_is_constructible<A, int, double>();
    test_is_constructible<A, int, long, double>();
    test_is_constructible<int&, int&>();

    test_is_not_constructible<A>();
    test_is_not_constructible<A, char>();
    test_is_constructible<B>();
    test_is_constructible<B[4]>();
    test_is_not_constructible<C>();
    test_is_constructible<D>();
    test_is_constructible<D[2]>();
    test_is_not_constructible<E>();
    test_is_not_constructible<NoDefaultConstructor>();

    test_is_not_constructible<A, void>();

    test_is_not_constructible<int, void>();
    test_is_not_constructible<int, void()>();
    test_is_not_constructible<int, void() const>();
    test_is_not_constructible<int, void() volatile>();
    test_is_not_constructible<int, void() const volatile>();
    test_is_not_constructible<int, void (&)()>();
    test_is_not_constructible<int, void (&&)()>();
    test_is_not_constructible<int, void() noexcept>();
    test_is_not_constructible<int, void() const noexcept>();
    test_is_not_constructible<int, void() volatile noexcept>();
    test_is_not_constructible<int, void() const volatile noexcept>();
    test_is_not_constructible<int, void (&)() noexcept>();
    test_is_not_constructible<int, void (&&)() noexcept>();

    test_is_not_constructible<int&, void>();
    test_is_not_constructible<int&, void()>();
    test_is_not_constructible<int&, void() const>();
    test_is_not_constructible<int&, void() volatile>();
    test_is_not_constructible<int&, void() const volatile>();
    test_is_not_constructible<int&, void (&)()>();
    test_is_not_constructible<int&, void (&&)()>();
    test_is_not_constructible<int&, void() noexcept>();
    test_is_not_constructible<int&, void() const noexcept>();
    test_is_not_constructible<int&, void() volatile noexcept>();
    test_is_not_constructible<int&, void() const volatile noexcept>();
    test_is_not_constructible<int&, void (&)() noexcept>();
    test_is_not_constructible<int&, void (&&)() noexcept>();

    test_is_not_constructible<int&&, void>();
    test_is_not_constructible<int&&, void()>();
    test_is_not_constructible<int&&, void() const>();
    test_is_not_constructible<int&&, void() volatile>();
    test_is_not_constructible<int&&, void() const volatile>();
    test_is_not_constructible<int&&, void (&)()>();
    test_is_not_constructible<int&&, void (&&)()>();
    test_is_not_constructible<int&&, void() noexcept>();
    test_is_not_constructible<int&&, void() const noexcept>();
    test_is_not_constructible<int&&, void() volatile noexcept>();
    test_is_not_constructible<int&&, void() const volatile noexcept>();
    test_is_not_constructible<int&&, void (&)() noexcept>();
    test_is_not_constructible<int&&, void (&&)() noexcept>();

    // LWG 2738
    test_is_not_constructible<const void>();
    test_is_not_constructible<volatile void>();
    test_is_not_constructible<const volatile void>();

    test_is_not_constructible<abstract>();
    test_is_not_constructible<AbstractFunc>();
    test_is_not_constructible<AbstractDestructor>();
    test_is_constructible<int, S>();
    test_is_not_constructible<int&, S>();

    test_is_constructible<void (&)(), void()>();
    test_is_constructible<void (&)(), void (&)()>();
    test_is_constructible<void (&)(), void (&&)()>();
    test_is_constructible<void (&&)(), void()>();
    test_is_constructible<void (&&)(), void (&)()>();
    test_is_constructible<void (&&)(), void (&&)()>();

    test_is_constructible<int const&, int>();
    test_is_constructible<int const&, int&&>();

    test_is_constructible<int&&, double&>();
    test_is_constructible<void (&)(), void (&&)()>();

    test_is_not_constructible<int&, int>();
    test_is_not_constructible<int&, int const&>();
    test_is_not_constructible<int&, int&&>();

    test_is_constructible<int&&, int>();
    test_is_constructible<int&&, int&&>();
    test_is_not_constructible<int&&, int&>();
    test_is_not_constructible<int&&, int const&&>();

    test_is_constructible<base, derived>();
    test_is_constructible<base&, derived&>();
#if PHI_SUPPORTS_IS_CONSTRUCTIBLE()
    // TODO: GCC without intrinsics thinks this is true
    test_is_not_constructible<derived&, base&>();
#endif
    test_is_constructible<base const&, derived const&>();
#if PHI_COMPILER_IS_BELOW(CLANG, 16, 0, 0)
    test_is_not_constructible<derived const&, base const&>();
    test_is_not_constructible<derived const&, base>();
#else
    SKIP_CHECK();
#endif

    test_is_constructible<base&&, derived>();
    test_is_constructible<base&&, derived&&>();
#if PHI_COMPILER_IS_BELOW(CLANG, 16, 0, 0)
    test_is_not_constructible<derived&&, base&&>();
    test_is_not_constructible<derived&&, base>();
#else
    SKIP_CHECK();
#endif

    // test that T must also be destructible
    test_is_constructible<PrivateDtor&, PrivateDtor&>();
    test_is_not_constructible<PrivateDtor, int>();

    test_is_not_constructible<void() const, void() const>();
    test_is_not_constructible<void() const, void*>();

    test_is_constructible<int&, implicit_to<int&>>();
    test_is_constructible<const int&, implicit_to<int&&>>();
    test_is_constructible<int&&, implicit_to<int&&>>();
    test_is_constructible<const int&, implicit_to<int>>();

    test_is_not_constructible<base&&, base&>();
    test_is_not_constructible<base&&, derived&>();
    test_is_constructible<base&&, implicit_to<derived&&>>();
    test_is_constructible<base&&, implicit_to<derived&&>&>();
    test_is_constructible<int&&, double&>();
    test_is_constructible<const int&, implicit_to<int&>&>();
    test_is_constructible<const int&, implicit_to<int&>>();
#if PHI_COMPILER_IS_NOT(MSVC)
    test_is_constructible<const int&, explicit_to<int&>&>();
    test_is_constructible<const int&, explicit_to<int&>>();
#else
    SKIP_CHECK();
#endif

#if PHI_COMPILER_IS_NOT(MSVC)
    test_is_constructible<const int&, explicit_to<int&>>();
    test_is_constructible<const int&, explicit_to<int&>&>();
#else
    SKIP_CHECK();
#endif

    // Binding through reference-compatible type is required to perform
    // direct-initialization as described in [over.match.ref] p. 1 b. 1:
    //
    // But the rvalue to lvalue reference binding isn't allowed according to
    // [over.match.ref] despite Clang accepting it.
#if PHI_COMPILER_IS(CLANG)
    test_is_constructible<int&, explicit_to<int&>>();
#endif
#if (PHI_COMPILER_IS_NOT(GCC) || PHI_COMPILER_IS_BELOW(GCC, 8, 0, 0)) &&                           \
        PHI_COMPILER_IS_NOT(MINGW) && PHI_COMPILER_IS_NOT(MSVC)
    test_is_constructible<const int&, explicit_to<int&&>>();
#else
    test_is_not_constructible<const int&, explicit_to<int&&>>();
#endif

#if PHI_COMPILER_IS_NOT(MSVC)
    test_is_constructible<int&&, explicit_to<int&&>>();
#else
    SKIP_CHECK();
#endif

#if PHI_COMPILER_IS(CLANG_COMPAT)
    // FIXME Clang and GCC disagree on the validity of this expression.
    test_is_constructible<const int&, explicit_to<int>>();
    test_is_constructible<int&&, explicit_to<int>>();
#else
    test_is_not_constructible<const int&, explicit_to<int>>();
    test_is_not_constructible<int&&, explicit_to<int>>();
#endif

    // Binding through temporary behaves like copy-initialization,
    // see [dcl.init.ref] p. 5, very last sub-bullet:
    test_is_not_constructible<const int&, explicit_to<double&&>>();
    test_is_not_constructible<int&&, explicit_to<double&&>>();

    // Testing aggregates
    // TODO: These tests need a prober guard
#if 0
    test_is_constructible<aggressive_aggregate, int, int>();
    test_is_constructible<aggressive_aggregate, int>();
    test_is_constructible<aggressive_aggregate>();
    test_is_constructible<vicious_variation, int, int>();
    test_is_constructible<vicious_variation, int>();
    test_is_constructible<vicious_variation>();
#endif

    t_base      b;
    t_derived&& d(static_cast<t_derived&&>(phi::move(b)));
    t_derived&& d2(phi::move(b));
    PHI_UNUSED_VARIABLE(d);
    PHI_UNUSED_VARIABLE(d2);
#if PHI_SUPPORTS_IS_CONSTRUCTIBLE()
    test_is_constructible<t_derived&&, t_base&&>();
#endif

    // Test unconstructible types
    // NOTE: This really only works with GCC-8+ and I don't believe its required by the standard
#if PHI_COMPILER_IS_ATLEAST(GCC, 8, 0, 0)
    test_is_not_constructible<Foo<int>>();
#endif

    // Testing for default constructions
    test_is_not_constructible<void>();
    test_is_constructible<phi::nullptr_t>();
    test_is_constructible<bool>();
    test_is_constructible<char>();
    test_is_constructible<signed char>();
    test_is_constructible<unsigned char>();
    test_is_constructible<short>();
    test_is_constructible<unsigned short>();
    test_is_constructible<int>();
    test_is_constructible<unsigned int>();
    test_is_constructible<long>();
    test_is_constructible<unsigned long>();
    test_is_constructible<long long>();
    test_is_constructible<unsigned long long>();
    test_is_constructible<float>();
    test_is_constructible<double>();
    test_is_constructible<long double>();
    test_is_constructible<char8_t>();
    test_is_constructible<char16_t>();
    test_is_constructible<char32_t>();
    test_is_constructible<wchar_t>();

    test_is_not_constructible<phi::boolean>();
    test_is_not_constructible<phi::integer<signed char>>();
    test_is_not_constructible<phi::integer<unsigned char>>();
    test_is_not_constructible<phi::integer<short>>();
    test_is_not_constructible<phi::integer<unsigned short>>();
    test_is_not_constructible<phi::integer<int>>();
    test_is_not_constructible<phi::integer<unsigned int>>();
    test_is_not_constructible<phi::integer<long>>();
    test_is_not_constructible<phi::integer<unsigned long>>();
    test_is_not_constructible<phi::integer<long long>>();
    test_is_not_constructible<phi::integer<unsigned long long>>();
    test_is_not_constructible<phi::floating_point<float>>();
    test_is_not_constructible<phi::floating_point<double>>();
    test_is_not_constructible<phi::floating_point<long double>>();

    test_is_constructible<std::vector<int>>();
    test_is_constructible<phi::scope_ptr<int>>();

    test_is_not_constructible<int&>();
    test_is_not_constructible<const int&>();
    test_is_not_constructible<volatile int&>();
    test_is_not_constructible<const volatile int&>();
    test_is_not_constructible<int&&>();
    test_is_not_constructible<const int&&>();
    test_is_not_constructible<volatile int&&>();
    test_is_not_constructible<const volatile int&&>();
    test_is_constructible<int*>();
    test_is_constructible<const int*>();
    test_is_constructible<volatile int*>();
    test_is_constructible<const volatile int*>();
    test_is_constructible<int**>();
    test_is_constructible<const int**>();
    test_is_constructible<volatile int**>();
    test_is_constructible<const volatile int**>();
    test_is_not_constructible<int*&>();
    test_is_not_constructible<const int*&>();
    test_is_not_constructible<volatile int*&>();
    test_is_not_constructible<const volatile int*&>();
    test_is_not_constructible<int*&&>();
    test_is_not_constructible<const int*&&>();
    test_is_not_constructible<volatile int*&&>();
    test_is_not_constructible<const volatile int*&&>();
    test_is_constructible<void*>();
    test_is_constructible<char[3]>();
    test_is_constructible<char* [3]>();
    test_is_constructible<int(*)[3]>();
    test_is_not_constructible<int(&)[3]>();
    test_is_not_constructible<int(&&)[3]>();
    test_is_constructible<char[3][2]>();
    test_is_constructible<char* [3][2]>();
    test_is_constructible<int(*)[3][2]>();
    test_is_not_constructible<int(&)[3][2]>();
    test_is_not_constructible<int(&&)[3][2]>();

    // Incomplete types only work with the intrinsic version
#if PHI_SUPPORTS_IS_CONSTRUCTIBLE()
    test_is_not_constructible<char[]>();
    test_is_not_constructible<char*[]>();
    test_is_constructible<int(*)[]>();
    test_is_not_constructible<int(&)[]>();
    test_is_not_constructible<int(&&)[]>();
    test_is_not_constructible<char[][2]>();
    test_is_not_constructible<char*[][2]>();
    test_is_constructible<int(*)[][2]>();
    test_is_not_constructible<int(&)[][2]>();
    test_is_not_constructible<int(&&)[][2]>();
#endif
    test_is_constructible<class_type>();
#if PHI_SUPPORTS_IS_CONSTRUCTIBLE()
    test_is_not_constructible<class_type[]>();
    test_is_constructible<class_type[2]>();
#endif
    test_is_constructible<template_type<void>>();
    test_is_constructible<template_type<int>>();
    test_is_constructible<template_type<class_type>>();
    test_is_constructible<template_type<incomplete_type>>();
    test_is_constructible<variadic_template<>>();
    test_is_constructible<variadic_template<void>>();
    test_is_constructible<variadic_template<int>>();
    test_is_constructible<variadic_template<class_type>>();
    test_is_constructible<variadic_template<incomplete_type>>();
    test_is_constructible<variadic_template<int, void, class_type, volatile char[]>>();
    test_is_constructible<public_derived_from<base>>();
    test_is_constructible<public_derived_from<derived>>();
    test_is_constructible<public_derived_from<class_type>>();
    test_is_constructible<private_derived_from<base>>();
    test_is_constructible<private_derived_from<derived>>();
    test_is_constructible<private_derived_from<class_type>>();
    test_is_constructible<protected_derived_from<base>>();
    test_is_constructible<protected_derived_from<derived>>();
    test_is_constructible<protected_derived_from<class_type>>();
    test_is_constructible<union_type>();
    test_is_constructible<non_empty_union>();
    test_is_constructible<empty>();
    test_is_constructible<not_empty>();
    test_is_constructible<bit_zero>();
    test_is_constructible<bit_one>();
    test_is_constructible<base>();
    test_is_constructible<derived>();
    test_is_not_constructible<abstract>();
    test_is_not_constructible<public_abstract>();
    test_is_not_constructible<private_abstract>();
    test_is_not_constructible<protected_abstract>();
#if !PHI_HAS_BUG_GCC_102305()
    // Test GCC bug 102305 (https://gcc.gnu.org/bugzilla/show_bug.cgi?id=102305)
    test_is_not_constructible<abstract_template<int>>();
    test_is_constructible<abstract_template<double>>();
    test_is_not_constructible<abstract_template<class_type>>();
    test_is_not_constructible<abstract_template<incomplete_type>>();
#endif
    test_is_constructible<final_type>();
    test_is_constructible<public_destructor>();
#if PHI_COMPILER_IS_NOT(MSVC) && PHI_COMPILER_IS_NOT(WINCLANG)
    test_is_not_constructible<protected_destructor>();
    test_is_not_constructible<private_destructor>();
#else
    SKIP_CHECK();
#endif
    test_is_constructible<virtual_public_destructor>();
#if PHI_COMPILER_IS_NOT(MSVC) && PHI_COMPILER_IS_NOT(WINCLANG)
    test_is_not_constructible<virtual_protected_destructor>();
    test_is_not_constructible<virtual_private_destructor>();
#else
    SKIP_CHECK();
#endif
    test_is_not_constructible<pure_public_destructor>();
    test_is_not_constructible<pure_protected_destructor>();
    test_is_not_constructible<pure_private_destructor>();
#if PHI_COMPILER_IS_NOT(MSVC) && PHI_COMPILER_IS_NOT(WINCLANG)
    test_is_not_constructible<deleted_public_destructor>();
    test_is_not_constructible<deleted_protected_destructor>();
    test_is_not_constructible<deleted_private_destructor>();
    test_is_not_constructible<deleted_virtual_public_destructor>();
    test_is_not_constructible<deleted_virtual_protected_destructor>();
    test_is_not_constructible<deleted_virtual_private_destructor>();
#else
    SKIP_CHECK();
#endif
    test_is_constructible<Enum>();
    test_is_constructible<EnumSigned>();
    test_is_constructible<EnumUnsigned>();
    test_is_constructible<EnumClass>();
    test_is_constructible<EnumStruct>();
    test_is_not_constructible<function_type>();
    test_is_constructible<function_ptr>();
    test_is_constructible<member_object_ptr>();
    test_is_constructible<member_function_ptr>();
    test_is_constructible<int class_type::*>();
    test_is_constructible<float class_type::*>();
    test_is_constructible<void * class_type::*>();
    test_is_constructible<int * class_type::*>();
    test_is_not_constructible<int class_type::*&>();
    test_is_not_constructible<float class_type::*&>();
    test_is_not_constructible<void * class_type::*&>();
    test_is_not_constructible<int * class_type::*&>();
    test_is_not_constructible<int class_type::*&&>();
    test_is_not_constructible<float class_type::*&&>();
    test_is_not_constructible<void * class_type::*&&>();
    test_is_not_constructible<int * class_type::*&&>();
    test_is_constructible<int class_type::* const>();
    test_is_constructible<float class_type::* const>();
    test_is_constructible<void * class_type::* const>();
    test_is_not_constructible<int class_type::* const&>();
    test_is_not_constructible<float class_type::* const&>();
    test_is_not_constructible<void * class_type::* const&>();
    test_is_not_constructible<int class_type::* const&&>();
    test_is_not_constructible<float class_type::* const&&>();
    test_is_not_constructible<void * class_type::* const&&>();
    test_is_constructible<int class_type::* volatile>();
    test_is_constructible<float class_type::* volatile>();
    test_is_constructible<void * class_type::* volatile>();
    test_is_not_constructible<int class_type::* volatile&>();
    test_is_not_constructible<float class_type::* volatile&>();
    test_is_not_constructible<void * class_type::* volatile&>();
    test_is_not_constructible<int class_type::* volatile&&>();
    test_is_not_constructible<float class_type::* volatile&&>();
    test_is_not_constructible<void * class_type::* volatile&&>();
    test_is_constructible<int class_type::* const volatile>();
    test_is_constructible<float class_type::* const volatile>();
    test_is_constructible<void * class_type::* const volatile>();
    test_is_not_constructible<int class_type::* const volatile&>();
    test_is_not_constructible<float class_type::* const volatile&>();
    test_is_not_constructible<void * class_type::* const volatile&>();
    test_is_not_constructible<int class_type::* const volatile&&>();
    test_is_not_constructible<float class_type::* const volatile&&>();
    test_is_not_constructible<void * class_type::* const volatile&&>();
    test_is_constructible<non_copyable>();
    test_is_constructible<non_moveable>();
    test_is_not_constructible<non_constructible>();
    test_is_constructible<tracked>();
    test_is_constructible<trap_constructible>();
    test_is_constructible<trap_implicit_conversion>();
    test_is_constructible<trap_comma>();
    test_is_constructible<trap_call>();
    test_is_constructible<trap_self_assign>();
    test_is_constructible<trap_deref>();
    test_is_constructible<trap_array_subscript>();

    test_is_not_constructible<void()>();
    test_is_not_constructible<void()&>();
    test_is_not_constructible<void() &&>();
    test_is_not_constructible<void() const>();
    test_is_not_constructible<void() const&>();
    test_is_not_constructible<void() const&&>();
    test_is_not_constructible<void() volatile>();
    test_is_not_constructible<void() volatile&>();
    test_is_not_constructible<void() volatile&&>();
    test_is_not_constructible<void() const volatile>();
    test_is_not_constructible<void() const volatile&>();
    test_is_not_constructible<void() const volatile&&>();
    test_is_not_constructible<void() noexcept>();
    test_is_not_constructible<void() & noexcept>();
    test_is_not_constructible<void() && noexcept>();
    test_is_not_constructible<void() const noexcept>();
    test_is_not_constructible<void() const & noexcept>();
    test_is_not_constructible<void() const && noexcept>();
    test_is_not_constructible<void() volatile noexcept>();
    test_is_not_constructible<void() volatile & noexcept>();
    test_is_not_constructible<void() volatile && noexcept>();
    test_is_not_constructible<void() const volatile noexcept>();
    test_is_not_constructible<void() const volatile & noexcept>();
    test_is_not_constructible<void() const volatile && noexcept>();

    test_is_not_constructible<void(int)>();
    test_is_not_constructible<void(int)&>();
    test_is_not_constructible<void(int) &&>();
    test_is_not_constructible<void(int) const>();
    test_is_not_constructible<void(int) const&>();
    test_is_not_constructible<void(int) const&&>();
    test_is_not_constructible<void(int) volatile>();
    test_is_not_constructible<void(int) volatile&>();
    test_is_not_constructible<void(int) volatile&&>();
    test_is_not_constructible<void(int) const volatile>();
    test_is_not_constructible<void(int) const volatile&>();
    test_is_not_constructible<void(int) const volatile&&>();
    test_is_not_constructible<void(int) noexcept>();
    test_is_not_constructible<void(int) & noexcept>();
    test_is_not_constructible<void(int) && noexcept>();
    test_is_not_constructible<void(int) const noexcept>();
    test_is_not_constructible<void(int) const & noexcept>();
    test_is_not_constructible<void(int) const && noexcept>();
    test_is_not_constructible<void(int) volatile noexcept>();
    test_is_not_constructible<void(int) volatile & noexcept>();
    test_is_not_constructible<void(int) volatile && noexcept>();
    test_is_not_constructible<void(int) const volatile noexcept>();
    test_is_not_constructible<void(int) const volatile & noexcept>();
    test_is_not_constructible<void(int) const volatile && noexcept>();

    test_is_not_constructible<void(...)>();
    test_is_not_constructible<void(...)&>();
    test_is_not_constructible<void(...) &&>();
    test_is_not_constructible<void(...) const>();
    test_is_not_constructible<void(...) const&>();
    test_is_not_constructible<void(...) const&&>();
    test_is_not_constructible<void(...) volatile>();
    test_is_not_constructible<void(...) volatile&>();
    test_is_not_constructible<void(...) volatile&&>();
    test_is_not_constructible<void(...) const volatile>();
    test_is_not_constructible<void(...) const volatile&>();
    test_is_not_constructible<void(...) const volatile&&>();
    test_is_not_constructible<void(...) noexcept>();
    test_is_not_constructible<void(...) & noexcept>();
    test_is_not_constructible<void(...) && noexcept>();
    test_is_not_constructible<void(...) const noexcept>();
    test_is_not_constructible<void(...) const & noexcept>();
    test_is_not_constructible<void(...) const && noexcept>();
    test_is_not_constructible<void(...) volatile noexcept>();
    test_is_not_constructible<void(...) volatile & noexcept>();
    test_is_not_constructible<void(...) volatile && noexcept>();
    test_is_not_constructible<void(...) const volatile noexcept>();
    test_is_not_constructible<void(...) const volatile & noexcept>();
    test_is_not_constructible<void(...) const volatile && noexcept>();

    test_is_not_constructible<void(int, ...)>();
    test_is_not_constructible<void(int, ...)&>();
    test_is_not_constructible<void(int, ...) &&>();
    test_is_not_constructible<void(int, ...) const>();
    test_is_not_constructible<void(int, ...) const&>();
    test_is_not_constructible<void(int, ...) const&&>();
    test_is_not_constructible<void(int, ...) volatile>();
    test_is_not_constructible<void(int, ...) volatile&>();
    test_is_not_constructible<void(int, ...) volatile&&>();
    test_is_not_constructible<void(int, ...) const volatile>();
    test_is_not_constructible<void(int, ...) const volatile&>();
    test_is_not_constructible<void(int, ...) const volatile&&>();
    test_is_not_constructible<void(int, ...) noexcept>();
    test_is_not_constructible<void(int, ...) & noexcept>();
    test_is_not_constructible<void(int, ...) && noexcept>();
    test_is_not_constructible<void(int, ...) const noexcept>();
    test_is_not_constructible<void(int, ...) const & noexcept>();
    test_is_not_constructible<void(int, ...) const && noexcept>();
    test_is_not_constructible<void(int, ...) volatile noexcept>();
    test_is_not_constructible<void(int, ...) volatile & noexcept>();
    test_is_not_constructible<void(int, ...) volatile && noexcept>();
    test_is_not_constructible<void(int, ...) const volatile noexcept>();
    test_is_not_constructible<void(int, ...) const volatile & noexcept>();
    test_is_not_constructible<void(int, ...) const volatile && noexcept>();

    test_is_not_constructible<int()>();
    test_is_not_constructible<int()&>();
    test_is_not_constructible<int() &&>();
    test_is_not_constructible<int() const>();
    test_is_not_constructible<int() const&>();
    test_is_not_constructible<int() const&&>();
    test_is_not_constructible<int() volatile>();
    test_is_not_constructible<int() volatile&>();
    test_is_not_constructible<int() volatile&&>();
    test_is_not_constructible<int() const volatile>();
    test_is_not_constructible<int() const volatile&>();
    test_is_not_constructible<int() const volatile&&>();
    test_is_not_constructible<int() noexcept>();
    test_is_not_constructible<int() & noexcept>();
    test_is_not_constructible<int() && noexcept>();
    test_is_not_constructible<int() const noexcept>();
    test_is_not_constructible<int() const & noexcept>();
    test_is_not_constructible<int() const && noexcept>();
    test_is_not_constructible<int() volatile noexcept>();
    test_is_not_constructible<int() volatile & noexcept>();
    test_is_not_constructible<int() volatile && noexcept>();
    test_is_not_constructible<int() const volatile noexcept>();
    test_is_not_constructible<int() const volatile & noexcept>();
    test_is_not_constructible<int() const volatile && noexcept>();

    test_is_not_constructible<int(int)>();
    test_is_not_constructible<int(int)&>();
    test_is_not_constructible<int(int) &&>();
    test_is_not_constructible<int(int) const>();
    test_is_not_constructible<int(int) const&>();
    test_is_not_constructible<int(int) const&&>();
    test_is_not_constructible<int(int) volatile>();
    test_is_not_constructible<int(int) volatile&>();
    test_is_not_constructible<int(int) volatile&&>();
    test_is_not_constructible<int(int) const volatile>();
    test_is_not_constructible<int(int) const volatile&>();
    test_is_not_constructible<int(int) const volatile&&>();
    test_is_not_constructible<int(int) noexcept>();
    test_is_not_constructible<int(int) & noexcept>();
    test_is_not_constructible<int(int) && noexcept>();
    test_is_not_constructible<int(int) const noexcept>();
    test_is_not_constructible<int(int) const & noexcept>();
    test_is_not_constructible<int(int) const && noexcept>();
    test_is_not_constructible<int(int) volatile noexcept>();
    test_is_not_constructible<int(int) volatile & noexcept>();
    test_is_not_constructible<int(int) volatile && noexcept>();
    test_is_not_constructible<int(int) const volatile noexcept>();
    test_is_not_constructible<int(int) const volatile & noexcept>();
    test_is_not_constructible<int(int) const volatile && noexcept>();

    test_is_not_constructible<int(...)>();
    test_is_not_constructible<int(...)&>();
    test_is_not_constructible<int(...) &&>();
    test_is_not_constructible<int(...) const>();
    test_is_not_constructible<int(...) const&>();
    test_is_not_constructible<int(...) const&&>();
    test_is_not_constructible<int(...) volatile>();
    test_is_not_constructible<int(...) volatile&>();
    test_is_not_constructible<int(...) volatile&&>();
    test_is_not_constructible<int(...) const volatile>();
    test_is_not_constructible<int(...) const volatile&>();
    test_is_not_constructible<int(...) const volatile&&>();
    test_is_not_constructible<int(...) noexcept>();
    test_is_not_constructible<int(...) & noexcept>();
    test_is_not_constructible<int(...) && noexcept>();
    test_is_not_constructible<int(...) const noexcept>();
    test_is_not_constructible<int(...) const & noexcept>();
    test_is_not_constructible<int(...) const && noexcept>();
    test_is_not_constructible<int(...) volatile noexcept>();
    test_is_not_constructible<int(...) volatile & noexcept>();
    test_is_not_constructible<int(...) volatile && noexcept>();
    test_is_not_constructible<int(...) const volatile noexcept>();
    test_is_not_constructible<int(...) const volatile & noexcept>();
    test_is_not_constructible<int(...) const volatile && noexcept>();

    test_is_not_constructible<int(int, ...)>();
    test_is_not_constructible<int(int, ...)&>();
    test_is_not_constructible<int(int, ...) &&>();
    test_is_not_constructible<int(int, ...) const>();
    test_is_not_constructible<int(int, ...) const&>();
    test_is_not_constructible<int(int, ...) const&&>();
    test_is_not_constructible<int(int, ...) volatile>();
    test_is_not_constructible<int(int, ...) volatile&>();
    test_is_not_constructible<int(int, ...) volatile&&>();
    test_is_not_constructible<int(int, ...) const volatile>();
    test_is_not_constructible<int(int, ...) const volatile&>();
    test_is_not_constructible<int(int, ...) const volatile&&>();
    test_is_not_constructible<int(int, ...) noexcept>();
    test_is_not_constructible<int(int, ...) & noexcept>();
    test_is_not_constructible<int(int, ...) && noexcept>();
    test_is_not_constructible<int(int, ...) const noexcept>();
    test_is_not_constructible<int(int, ...) const & noexcept>();
    test_is_not_constructible<int(int, ...) const && noexcept>();
    test_is_not_constructible<int(int, ...) volatile noexcept>();
    test_is_not_constructible<int(int, ...) volatile & noexcept>();
    test_is_not_constructible<int(int, ...) volatile && noexcept>();
    test_is_not_constructible<int(int, ...) const volatile noexcept>();
    test_is_not_constructible<int(int, ...) const volatile & noexcept>();
    test_is_not_constructible<int(int, ...) const volatile && noexcept>();

    test_is_constructible<void (*)()>();
    test_is_constructible<void (*)() noexcept>();

    test_is_constructible<void (*)(int)>();
    test_is_constructible<void (*)(int) noexcept>();

    test_is_constructible<void (*)(...)>();
    test_is_constructible<void (*)(...) noexcept>();

    test_is_constructible<void (*)(int, ...)>();
    test_is_constructible<void (*)(int, ...) noexcept>();

    test_is_constructible<int (*)()>();
    test_is_constructible<int (*)() noexcept>();

    test_is_constructible<int (*)(int)>();
    test_is_constructible<int (*)(int) noexcept>();

    test_is_constructible<int (*)(...)>();
    test_is_constructible<int (*)(...) noexcept>();

    test_is_constructible<int (*)(int, ...)>();
    test_is_constructible<int (*)(int, ...) noexcept>();

    test_is_not_constructible<void (&)()>();
    test_is_not_constructible<void (&)() noexcept>();

    test_is_not_constructible<void (&)(int)>();
    test_is_not_constructible<void (&)(int) noexcept>();

    test_is_not_constructible<void (&)(...)>();
    test_is_not_constructible<void (&)(...) noexcept>();

    test_is_not_constructible<void (&)(int, ...)>();
    test_is_not_constructible<void (&)(int, ...) noexcept>();

    test_is_not_constructible<int (&)()>();
    test_is_not_constructible<int (&)() noexcept>();

    test_is_not_constructible<int (&)(int)>();
    test_is_not_constructible<int (&)(int) noexcept>();

    test_is_not_constructible<int (&)(...)>();
    test_is_not_constructible<int (&)(...) noexcept>();

    test_is_not_constructible<int (&)(int, ...)>();
    test_is_not_constructible<int (&)(int, ...) noexcept>();

    test_is_not_constructible<void (&&)()>();
    test_is_not_constructible<void (&&)() noexcept>();

    test_is_not_constructible<void (&&)(int)>();
    test_is_not_constructible<void (&&)(int) noexcept>();

    test_is_not_constructible<void (&&)(...)>();
    test_is_not_constructible<void (&&)(...) noexcept>();

    test_is_not_constructible<void (&&)(int, ...)>();
    test_is_not_constructible<void (&&)(int, ...) noexcept>();

    test_is_not_constructible<int (&&)()>();
    test_is_not_constructible<int (&&)() noexcept>();

    test_is_not_constructible<int (&&)(int)>();
    test_is_not_constructible<int (&&)(int) noexcept>();

    test_is_not_constructible<int (&&)(...)>();
    test_is_not_constructible<int (&&)(...) noexcept>();

    test_is_not_constructible<int (&&)(int, ...)>();
    test_is_not_constructible<int (&&)(int, ...) noexcept>();

    test_is_constructible<void (class_type::*)()>();
    test_is_constructible<void (class_type::*)()&>();
    test_is_constructible<void (class_type::*)() &&>();
    test_is_constructible<void (class_type::*)() const>();
    test_is_constructible<void (class_type::*)() const&>();
    test_is_constructible<void (class_type::*)() const&&>();
    test_is_constructible<void (class_type::*)() noexcept>();
    test_is_constructible<void (class_type::*)() & noexcept>();
    test_is_constructible<void (class_type::*)() && noexcept>();
    test_is_constructible<void (class_type::*)() const noexcept>();
    test_is_constructible<void (class_type::*)() const & noexcept>();
    test_is_constructible<void (class_type::*)() const && noexcept>();

    test_is_constructible<void (class_type::*)(int)>();
    test_is_constructible<void (class_type::*)(int)&>();
    test_is_constructible<void (class_type::*)(int) &&>();
    test_is_constructible<void (class_type::*)(int) const>();
    test_is_constructible<void (class_type::*)(int) const&>();
    test_is_constructible<void (class_type::*)(int) const&&>();
    test_is_constructible<void (class_type::*)(int) noexcept>();
    test_is_constructible<void (class_type::*)(int) & noexcept>();
    test_is_constructible<void (class_type::*)(int) && noexcept>();
    test_is_constructible<void (class_type::*)(int) const noexcept>();
    test_is_constructible<void (class_type::*)(int) const & noexcept>();
    test_is_constructible<void (class_type::*)(int) const && noexcept>();

    test_is_constructible<void (class_type::*)(...)>();
    test_is_constructible<void (class_type::*)(...)&>();
    test_is_constructible<void (class_type::*)(...) &&>();
    test_is_constructible<void (class_type::*)(...) const>();
    test_is_constructible<void (class_type::*)(...) const&>();
    test_is_constructible<void (class_type::*)(...) const&&>();
    test_is_constructible<void (class_type::*)(...) noexcept>();
    test_is_constructible<void (class_type::*)(...) & noexcept>();
    test_is_constructible<void (class_type::*)(...) && noexcept>();
    test_is_constructible<void (class_type::*)(...) const noexcept>();
    test_is_constructible<void (class_type::*)(...) const & noexcept>();
    test_is_constructible<void (class_type::*)(...) const && noexcept>();

    test_is_constructible<void (class_type::*)(int, ...)>();
    test_is_constructible<void (class_type::*)(int, ...)&>();
    test_is_constructible<void (class_type::*)(int, ...) &&>();
    test_is_constructible<void (class_type::*)(int, ...) const>();
    test_is_constructible<void (class_type::*)(int, ...) const&>();
    test_is_constructible<void (class_type::*)(int, ...) const&&>();
    test_is_constructible<void (class_type::*)(int, ...) noexcept>();
    test_is_constructible<void (class_type::*)(int, ...) & noexcept>();
    test_is_constructible<void (class_type::*)(int, ...) && noexcept>();
    test_is_constructible<void (class_type::*)(int, ...) const noexcept>();
    test_is_constructible<void (class_type::*)(int, ...) const & noexcept>();
    test_is_constructible<void (class_type::*)(int, ...) const && noexcept>();

    test_is_constructible<int (class_type::*)()>();
    test_is_constructible<int (class_type::*)()&>();
    test_is_constructible<int (class_type::*)() &&>();
    test_is_constructible<int (class_type::*)() const>();
    test_is_constructible<int (class_type::*)() const&>();
    test_is_constructible<int (class_type::*)() const&&>();
    test_is_constructible<int (class_type::*)() noexcept>();
    test_is_constructible<int (class_type::*)() & noexcept>();
    test_is_constructible<int (class_type::*)() && noexcept>();
    test_is_constructible<int (class_type::*)() const noexcept>();
    test_is_constructible<int (class_type::*)() const & noexcept>();
    test_is_constructible<int (class_type::*)() const && noexcept>();

    test_is_constructible<int (class_type::*)(int)>();
    test_is_constructible<int (class_type::*)(int)&>();
    test_is_constructible<int (class_type::*)(int) &&>();
    test_is_constructible<int (class_type::*)(int) const>();
    test_is_constructible<int (class_type::*)(int) const&>();
    test_is_constructible<int (class_type::*)(int) const&&>();
    test_is_constructible<int (class_type::*)(int) noexcept>();
    test_is_constructible<int (class_type::*)(int) & noexcept>();
    test_is_constructible<int (class_type::*)(int) && noexcept>();
    test_is_constructible<int (class_type::*)(int) const noexcept>();
    test_is_constructible<int (class_type::*)(int) const & noexcept>();
    test_is_constructible<int (class_type::*)(int) const && noexcept>();

    test_is_constructible<int (class_type::*)(...)>();
    test_is_constructible<int (class_type::*)(...)&>();
    test_is_constructible<int (class_type::*)(...) &&>();
    test_is_constructible<int (class_type::*)(...) const>();
    test_is_constructible<int (class_type::*)(...) const&>();
    test_is_constructible<int (class_type::*)(...) const&&>();
    test_is_constructible<int (class_type::*)(...) noexcept>();
    test_is_constructible<int (class_type::*)(...) & noexcept>();
    test_is_constructible<int (class_type::*)(...) && noexcept>();
    test_is_constructible<int (class_type::*)(...) const noexcept>();
    test_is_constructible<int (class_type::*)(...) const & noexcept>();
    test_is_constructible<int (class_type::*)(...) const && noexcept>();

    test_is_constructible<int (class_type::*)(int, ...)>();
    test_is_constructible<int (class_type::*)(int, ...)&>();
    test_is_constructible<int (class_type::*)(int, ...) &&>();
    test_is_constructible<int (class_type::*)(int, ...) const>();
    test_is_constructible<int (class_type::*)(int, ...) const&>();
    test_is_constructible<int (class_type::*)(int, ...) const&&>();
    test_is_constructible<int (class_type::*)(int, ...) noexcept>();
    test_is_constructible<int (class_type::*)(int, ...) & noexcept>();
    test_is_constructible<int (class_type::*)(int, ...) && noexcept>();
    test_is_constructible<int (class_type::*)(int, ...) const noexcept>();
    test_is_constructible<int (class_type::*)(int, ...) const & noexcept>();
    test_is_constructible<int (class_type::*)(int, ...) const && noexcept>();
}
