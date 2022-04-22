#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_move_assignable.hpp>
#include <phi/type_traits/is_trivially_move_assignable.hpp>
#include <type_traits>
#include <vector>

template <typename T>
void test_is_trivially_move_assignable_impl()
{
#if PHI_HAS_WORKING_IS_TRIVIALLY_MOVE_ASSIGNABLE()
    STATIC_REQUIRE(phi::is_trivially_move_assignable<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_trivially_move_assignable<T>::value);
    STATIC_REQUIRE(phi::is_move_assignable<T>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_trivially_move_assignable_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_not_trivially_move_assignable_v<T>);
    STATIC_REQUIRE(phi::is_move_assignable_v<T>);
#    endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_trivially_move_assignable<T>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_trivially_move_assignable<T>);

    // Standard compatibility
    STATIC_REQUIRE(std::is_trivially_move_assignable<T>::value);
    STATIC_REQUIRE(std::is_move_assignable<T>::value);
#endif
}

template <typename T>
void test_is_not_trivially_move_assignable_impl()
{
#if PHI_HAS_WORKING_IS_TRIVIALLY_MOVE_ASSIGNABLE()
    STATIC_REQUIRE_FALSE(phi::is_trivially_move_assignable<T>::value);
    STATIC_REQUIRE(phi::is_not_trivially_move_assignable<T>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_trivially_move_assignable_v<T>);
    STATIC_REQUIRE(phi::is_not_trivially_move_assignable_v<T>);
#    endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_trivially_move_assignable<T>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_trivially_move_assignable<T>);

    // Standard compatibility
    STATIC_REQUIRE_FALSE(std::is_trivially_move_assignable<T>::value);
#endif
}

template <typename T>
void test_is_trivially_move_assignable()
{
    test_is_trivially_move_assignable_impl<T>();
    test_is_not_trivially_move_assignable_impl<const T>();
    test_is_not_trivially_move_assignable_impl<volatile T>();
    test_is_not_trivially_move_assignable_impl<const volatile T>();
}

template <typename T>
void test_is_trivially_move_assignable_v()
{
    test_is_trivially_move_assignable_impl<T>();
    test_is_not_trivially_move_assignable_impl<const T>();
    test_is_trivially_move_assignable_impl<volatile T>();
    test_is_not_trivially_move_assignable_impl<const volatile T>();
}

template <typename T>
void test_is_trivially_move_assignable_cv()
{
    test_is_trivially_move_assignable_impl<T>();
    test_is_trivially_move_assignable_impl<const T>();
    test_is_trivially_move_assignable_impl<volatile T>();
    test_is_trivially_move_assignable_impl<const volatile T>();
}

template <typename T>
void test_is_not_trivially_move_assignable()
{
    test_is_not_trivially_move_assignable_impl<T>();
    test_is_not_trivially_move_assignable_impl<const T>();
    test_is_not_trivially_move_assignable_impl<volatile T>();
    test_is_not_trivially_move_assignable_impl<const volatile T>();
}

struct A
{
    A& operator=(const A&);
};

struct B
{
    B& operator=(const B&) = default;
};

struct C
{
    C& operator=(const C&) = delete;
};

TEST_CASE("is_trivially_move_assignable")
{
    test_is_not_trivially_move_assignable<A>();
    test_is_trivially_move_assignable<B>();
    test_is_not_trivially_move_assignable<C>();

    test_is_not_trivially_move_assignable<void>();
    test_is_trivially_move_assignable_v<phi::nullptr_t>();
    test_is_trivially_move_assignable_v<bool>();
    test_is_trivially_move_assignable_v<char>();
    test_is_trivially_move_assignable_v<signed char>();
    test_is_trivially_move_assignable_v<unsigned char>();
    test_is_trivially_move_assignable_v<short>();
    test_is_trivially_move_assignable_v<unsigned short>();
    test_is_trivially_move_assignable_v<int>();
    test_is_trivially_move_assignable_v<unsigned int>();
    test_is_trivially_move_assignable_v<long>();
    test_is_trivially_move_assignable_v<unsigned long>();
    test_is_trivially_move_assignable_v<long long>();
    test_is_trivially_move_assignable_v<unsigned long long>();
    test_is_trivially_move_assignable_v<float>();
    test_is_trivially_move_assignable_v<double>();
    test_is_trivially_move_assignable_v<long double>();
    test_is_trivially_move_assignable_v<char8_t>();
    test_is_trivially_move_assignable_v<char16_t>();
    test_is_trivially_move_assignable_v<char32_t>();
    test_is_trivially_move_assignable_v<wchar_t>();

    test_is_trivially_move_assignable<phi::boolean>();
    test_is_trivially_move_assignable<phi::integer<signed char>>();
    test_is_trivially_move_assignable<phi::integer<unsigned char>>();
    test_is_trivially_move_assignable<phi::integer<short>>();
    test_is_trivially_move_assignable<phi::integer<unsigned short>>();
    test_is_trivially_move_assignable<phi::integer<int>>();
    test_is_trivially_move_assignable<phi::integer<unsigned int>>();
    test_is_trivially_move_assignable<phi::integer<long>>();
    test_is_trivially_move_assignable<phi::integer<unsigned long>>();
    test_is_trivially_move_assignable<phi::integer<long long>>();
    test_is_trivially_move_assignable<phi::integer<unsigned long long>>();
    test_is_trivially_move_assignable<phi::floating_point<float>>();
    test_is_trivially_move_assignable<phi::floating_point<double>>();
    test_is_trivially_move_assignable<phi::floating_point<long double>>();

    test_is_not_trivially_move_assignable<std::vector<int>>();
    test_is_not_trivially_move_assignable<phi::scope_ptr<int>>();

    test_is_trivially_move_assignable_cv<int&>();
    test_is_not_trivially_move_assignable<const int&>();
    test_is_trivially_move_assignable_cv<volatile int&>();
    test_is_not_trivially_move_assignable<const volatile int&>();
    test_is_trivially_move_assignable_cv<int&&>();
    test_is_not_trivially_move_assignable<const int&&>();
    test_is_trivially_move_assignable_cv<volatile int&&>();
    test_is_not_trivially_move_assignable<const volatile int&&>();
    test_is_trivially_move_assignable_v<int*>();
    test_is_trivially_move_assignable_v<const int*>();
    test_is_trivially_move_assignable_v<volatile int*>();
    test_is_trivially_move_assignable_v<const volatile int*>();
    test_is_trivially_move_assignable_v<int**>();
    test_is_trivially_move_assignable_v<const int**>();
    test_is_trivially_move_assignable_v<volatile int**>();
    test_is_trivially_move_assignable_v<const volatile int**>();
    test_is_trivially_move_assignable_cv<int*&>();
    test_is_trivially_move_assignable_cv<const int*&>();
    test_is_trivially_move_assignable_cv<volatile int*&>();
    test_is_trivially_move_assignable_cv<const volatile int*&>();
    test_is_trivially_move_assignable_cv<int*&&>();
    test_is_trivially_move_assignable_cv<const int*&&>();
    test_is_trivially_move_assignable_cv<volatile int*&&>();
    test_is_trivially_move_assignable_cv<const volatile int*&&>();
    test_is_trivially_move_assignable_v<void*>();
    test_is_not_trivially_move_assignable<char[3]>();
    test_is_not_trivially_move_assignable<char[]>();
    test_is_not_trivially_move_assignable<char* [3]>();
    test_is_not_trivially_move_assignable<char*[]>();
    test_is_trivially_move_assignable_v<int(*)[3]>();
    test_is_trivially_move_assignable_v<int(*)[]>();
    test_is_not_trivially_move_assignable<int(&)[3]>();
    test_is_not_trivially_move_assignable<int(&)[]>();
    test_is_not_trivially_move_assignable<int(&&)[3]>();
    test_is_not_trivially_move_assignable<int(&&)[]>();
    test_is_not_trivially_move_assignable<char[3][2]>();
    test_is_not_trivially_move_assignable<char[][2]>();
    test_is_not_trivially_move_assignable<char* [3][2]>();
    test_is_not_trivially_move_assignable<char*[][2]>();
    test_is_trivially_move_assignable_v<int(*)[3][2]>();
    test_is_trivially_move_assignable_v<int(*)[][2]>();
    test_is_not_trivially_move_assignable<int(&)[3][2]>();
    test_is_not_trivially_move_assignable<int(&)[][2]>();
    test_is_not_trivially_move_assignable<int(&&)[3][2]>();
    test_is_not_trivially_move_assignable<int(&&)[][2]>();
    test_is_trivially_move_assignable<Class>();
    test_is_not_trivially_move_assignable<Class[]>();
    test_is_not_trivially_move_assignable<Class[2]>();
    test_is_trivially_move_assignable<Template<void>>();
    test_is_trivially_move_assignable<Template<int>>();
    test_is_trivially_move_assignable<Template<Class>>();
    test_is_trivially_move_assignable<Template<IncompleteType>>();
    test_is_trivially_move_assignable<VariadicTemplate<>>();
    test_is_trivially_move_assignable<VariadicTemplate<void>>();
    test_is_trivially_move_assignable<VariadicTemplate<int>>();
    test_is_trivially_move_assignable<VariadicTemplate<Class>>();
    test_is_trivially_move_assignable<VariadicTemplate<IncompleteType>>();
    test_is_trivially_move_assignable<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_trivially_move_assignable<PublicDerivedFromTemplate<Base>>();
    test_is_trivially_move_assignable<PublicDerivedFromTemplate<Derived>>();
    test_is_trivially_move_assignable<PublicDerivedFromTemplate<Class>>();
    test_is_trivially_move_assignable<PrivateDerivedFromTemplate<Base>>();
    test_is_trivially_move_assignable<PrivateDerivedFromTemplate<Derived>>();
    test_is_trivially_move_assignable<PrivateDerivedFromTemplate<Class>>();
    test_is_trivially_move_assignable<ProtectedDerivedFromTemplate<Base>>();
    test_is_trivially_move_assignable<ProtectedDerivedFromTemplate<Derived>>();
    test_is_trivially_move_assignable<ProtectedDerivedFromTemplate<Class>>();
    test_is_trivially_move_assignable<Union>();
    test_is_trivially_move_assignable<NonEmptyUnion>();
    test_is_trivially_move_assignable<Empty>();
    test_is_not_trivially_move_assignable<NotEmpty>();
    test_is_trivially_move_assignable<BitZero>();
    test_is_trivially_move_assignable<BitOne>();
    test_is_trivially_move_assignable<Base>();
    test_is_trivially_move_assignable<Derived>();
    test_is_not_trivially_move_assignable<Abstract>();
    test_is_not_trivially_move_assignable<PublicAbstract>();
    test_is_not_trivially_move_assignable<PrivateAbstract>();
    test_is_not_trivially_move_assignable<ProtectedAbstract>();
    test_is_not_trivially_move_assignable<AbstractTemplate<int>>();
    test_is_trivially_move_assignable<AbstractTemplate<double>>();
    test_is_not_trivially_move_assignable<AbstractTemplate<Class>>();
    test_is_not_trivially_move_assignable<AbstractTemplate<IncompleteType>>();
    test_is_trivially_move_assignable<Final>();
    test_is_trivially_move_assignable<PublicDestructor>();
    test_is_trivially_move_assignable<ProtectedDestructor>();
    test_is_trivially_move_assignable<PrivateDestructor>();
    test_is_not_trivially_move_assignable<VirtualPublicDestructor>();
    test_is_not_trivially_move_assignable<VirtualProtectedDestructor>();
    test_is_not_trivially_move_assignable<VirtualPrivateDestructor>();
    test_is_not_trivially_move_assignable<PurePublicDestructor>();
    test_is_not_trivially_move_assignable<PureProtectedDestructor>();
    test_is_not_trivially_move_assignable<PurePrivateDestructor>();
    test_is_trivially_move_assignable<DeletedPublicDestructor>();
    test_is_trivially_move_assignable<DeletedProtectedDestructor>();
    test_is_trivially_move_assignable<DeletedPrivateDestructor>();
    test_is_not_trivially_move_assignable<DeletedVirtualPublicDestructor>();
    test_is_not_trivially_move_assignable<DeletedVirtualProtectedDestructor>();
    test_is_not_trivially_move_assignable<DeletedVirtualPrivateDestructor>();
    test_is_trivially_move_assignable_v<Enum>();
    test_is_trivially_move_assignable_v<EnumSigned>();
    test_is_trivially_move_assignable_v<EnumUnsigned>();
    test_is_trivially_move_assignable_v<EnumClass>();
    test_is_trivially_move_assignable_v<EnumStruct>();
    test_is_not_trivially_move_assignable<Function>();
    test_is_trivially_move_assignable_v<FunctionPtr>();
    test_is_trivially_move_assignable_v<MemberObjectPtr>();
    test_is_trivially_move_assignable_v<MemberFunctionPtr>();
    test_is_trivially_move_assignable_v<int Class::*>();
    test_is_trivially_move_assignable_v<float Class::*>();
    test_is_trivially_move_assignable_v<void * Class::*>();
    test_is_trivially_move_assignable_v<int * Class::*>();
    test_is_trivially_move_assignable_cv<int Class::*&>();
    test_is_trivially_move_assignable_cv<float Class::*&>();
    test_is_trivially_move_assignable_cv<void * Class::*&>();
    test_is_trivially_move_assignable_cv<int * Class::*&>();
    test_is_trivially_move_assignable_cv<int Class::*&&>();
    test_is_trivially_move_assignable_cv<float Class::*&&>();
    test_is_trivially_move_assignable_cv<void * Class::*&&>();
    test_is_trivially_move_assignable_cv<int * Class::*&&>();
    test_is_not_trivially_move_assignable<int Class::*const>();
    test_is_not_trivially_move_assignable<float Class::*const>();
    test_is_not_trivially_move_assignable<void * Class::*const>();
    test_is_not_trivially_move_assignable<int Class::*const&>();
    test_is_not_trivially_move_assignable<float Class::*const&>();
    test_is_not_trivially_move_assignable<void * Class::*const&>();
    test_is_not_trivially_move_assignable<int Class::*const&&>();
    test_is_not_trivially_move_assignable<float Class::*const&&>();
    test_is_not_trivially_move_assignable<void * Class::*const&&>();
    test_is_trivially_move_assignable_v<int Class::*volatile>();
    test_is_trivially_move_assignable_v<float Class::*volatile>();
    test_is_trivially_move_assignable_v<void * Class::*volatile>();
    test_is_trivially_move_assignable_cv<int Class::*volatile&>();
    test_is_trivially_move_assignable_cv<float Class::*volatile&>();
    test_is_trivially_move_assignable_cv<void * Class::*volatile&>();
    test_is_trivially_move_assignable_cv<int Class::*volatile&&>();
    test_is_trivially_move_assignable_cv<float Class::*volatile&&>();
    test_is_trivially_move_assignable_cv<void * Class::*volatile&&>();
    test_is_not_trivially_move_assignable<int Class::*const volatile>();
    test_is_not_trivially_move_assignable<float Class::*const volatile>();
    test_is_not_trivially_move_assignable<void * Class::*const volatile>();
    test_is_not_trivially_move_assignable<int Class::*const volatile&>();
    test_is_not_trivially_move_assignable<float Class::*const volatile&>();
    test_is_not_trivially_move_assignable<void * Class::*const volatile&>();
    test_is_not_trivially_move_assignable<int Class::*const volatile&&>();
    test_is_not_trivially_move_assignable<float Class::*const volatile&&>();
    test_is_not_trivially_move_assignable<void * Class::*const volatile&&>();
    test_is_trivially_move_assignable<NonCopyable>();
    test_is_not_trivially_move_assignable<NonMoveable>();
    test_is_not_trivially_move_assignable<NonConstructible>();
    test_is_not_trivially_move_assignable<Tracked>();
    test_is_trivially_move_assignable<TrapConstructible>();
    test_is_trivially_move_assignable<TrapImplicitConversion>();
    test_is_trivially_move_assignable<TrapComma>();
    test_is_trivially_move_assignable<TrapCall>();
    test_is_not_trivially_move_assignable<TrapSelfAssign>();
    test_is_trivially_move_assignable<TrapDeref>();
    test_is_trivially_move_assignable<TrapArraySubscript>();

    test_is_not_trivially_move_assignable<void()>();
    test_is_not_trivially_move_assignable<void()&>();
    test_is_not_trivially_move_assignable<void() &&>();
    test_is_not_trivially_move_assignable<void() const>();
    test_is_not_trivially_move_assignable<void() const&>();
    test_is_not_trivially_move_assignable<void() const&&>();
    test_is_not_trivially_move_assignable<void() volatile>();
    test_is_not_trivially_move_assignable<void() volatile&>();
    test_is_not_trivially_move_assignable<void() volatile&&>();
    test_is_not_trivially_move_assignable<void() const volatile>();
    test_is_not_trivially_move_assignable<void() const volatile&>();
    test_is_not_trivially_move_assignable<void() const volatile&&>();
    test_is_not_trivially_move_assignable<void() noexcept>();
    test_is_not_trivially_move_assignable<void()& noexcept>();
    test_is_not_trivially_move_assignable<void()&& noexcept>();
    test_is_not_trivially_move_assignable<void() const noexcept>();
    test_is_not_trivially_move_assignable<void() const& noexcept>();
    test_is_not_trivially_move_assignable<void() const&& noexcept>();
    test_is_not_trivially_move_assignable<void() volatile noexcept>();
    test_is_not_trivially_move_assignable<void() volatile& noexcept>();
    test_is_not_trivially_move_assignable<void() volatile&& noexcept>();
    test_is_not_trivially_move_assignable<void() const volatile noexcept>();
    test_is_not_trivially_move_assignable<void() const volatile& noexcept>();
    test_is_not_trivially_move_assignable<void() const volatile&& noexcept>();

    test_is_not_trivially_move_assignable<void(int)>();
    test_is_not_trivially_move_assignable<void(int)&>();
    test_is_not_trivially_move_assignable<void(int) &&>();
    test_is_not_trivially_move_assignable<void(int) const>();
    test_is_not_trivially_move_assignable<void(int) const&>();
    test_is_not_trivially_move_assignable<void(int) const&&>();
    test_is_not_trivially_move_assignable<void(int) volatile>();
    test_is_not_trivially_move_assignable<void(int) volatile&>();
    test_is_not_trivially_move_assignable<void(int) volatile&&>();
    test_is_not_trivially_move_assignable<void(int) const volatile>();
    test_is_not_trivially_move_assignable<void(int) const volatile&>();
    test_is_not_trivially_move_assignable<void(int) const volatile&&>();
    test_is_not_trivially_move_assignable<void(int) noexcept>();
    test_is_not_trivially_move_assignable<void(int)& noexcept>();
    test_is_not_trivially_move_assignable<void(int)&& noexcept>();
    test_is_not_trivially_move_assignable<void(int) const noexcept>();
    test_is_not_trivially_move_assignable<void(int) const& noexcept>();
    test_is_not_trivially_move_assignable<void(int) const&& noexcept>();
    test_is_not_trivially_move_assignable<void(int) volatile noexcept>();
    test_is_not_trivially_move_assignable<void(int) volatile& noexcept>();
    test_is_not_trivially_move_assignable<void(int) volatile&& noexcept>();
    test_is_not_trivially_move_assignable<void(int) const volatile noexcept>();
    test_is_not_trivially_move_assignable<void(int) const volatile& noexcept>();
    test_is_not_trivially_move_assignable<void(int) const volatile&& noexcept>();

    test_is_not_trivially_move_assignable<void(...)>();
    test_is_not_trivially_move_assignable<void(...)&>();
    test_is_not_trivially_move_assignable<void(...) &&>();
    test_is_not_trivially_move_assignable<void(...) const>();
    test_is_not_trivially_move_assignable<void(...) const&>();
    test_is_not_trivially_move_assignable<void(...) const&&>();
    test_is_not_trivially_move_assignable<void(...) volatile>();
    test_is_not_trivially_move_assignable<void(...) volatile&>();
    test_is_not_trivially_move_assignable<void(...) volatile&&>();
    test_is_not_trivially_move_assignable<void(...) const volatile>();
    test_is_not_trivially_move_assignable<void(...) const volatile&>();
    test_is_not_trivially_move_assignable<void(...) const volatile&&>();
    test_is_not_trivially_move_assignable<void(...) noexcept>();
    test_is_not_trivially_move_assignable<void(...)& noexcept>();
    test_is_not_trivially_move_assignable<void(...)&& noexcept>();
    test_is_not_trivially_move_assignable<void(...) const noexcept>();
    test_is_not_trivially_move_assignable<void(...) const& noexcept>();
    test_is_not_trivially_move_assignable<void(...) const&& noexcept>();
    test_is_not_trivially_move_assignable<void(...) volatile noexcept>();
    test_is_not_trivially_move_assignable<void(...) volatile& noexcept>();
    test_is_not_trivially_move_assignable<void(...) volatile&& noexcept>();
    test_is_not_trivially_move_assignable<void(...) const volatile noexcept>();
    test_is_not_trivially_move_assignable<void(...) const volatile& noexcept>();
    test_is_not_trivially_move_assignable<void(...) const volatile&& noexcept>();

    test_is_not_trivially_move_assignable<void(int, ...)>();
    test_is_not_trivially_move_assignable<void(int, ...)&>();
    test_is_not_trivially_move_assignable<void(int, ...) &&>();
    test_is_not_trivially_move_assignable<void(int, ...) const>();
    test_is_not_trivially_move_assignable<void(int, ...) const&>();
    test_is_not_trivially_move_assignable<void(int, ...) const&&>();
    test_is_not_trivially_move_assignable<void(int, ...) volatile>();
    test_is_not_trivially_move_assignable<void(int, ...) volatile&>();
    test_is_not_trivially_move_assignable<void(int, ...) volatile&&>();
    test_is_not_trivially_move_assignable<void(int, ...) const volatile>();
    test_is_not_trivially_move_assignable<void(int, ...) const volatile&>();
    test_is_not_trivially_move_assignable<void(int, ...) const volatile&&>();
    test_is_not_trivially_move_assignable<void(int, ...) noexcept>();
    test_is_not_trivially_move_assignable<void(int, ...)& noexcept>();
    test_is_not_trivially_move_assignable<void(int, ...)&& noexcept>();
    test_is_not_trivially_move_assignable<void(int, ...) const noexcept>();
    test_is_not_trivially_move_assignable<void(int, ...) const& noexcept>();
    test_is_not_trivially_move_assignable<void(int, ...) const&& noexcept>();
    test_is_not_trivially_move_assignable<void(int, ...) volatile noexcept>();
    test_is_not_trivially_move_assignable<void(int, ...) volatile& noexcept>();
    test_is_not_trivially_move_assignable<void(int, ...) volatile&& noexcept>();
    test_is_not_trivially_move_assignable<void(int, ...) const volatile noexcept>();
    test_is_not_trivially_move_assignable<void(int, ...) const volatile& noexcept>();
    test_is_not_trivially_move_assignable<void(int, ...) const volatile&& noexcept>();

    test_is_not_trivially_move_assignable<int()>();
    test_is_not_trivially_move_assignable<int()&>();
    test_is_not_trivially_move_assignable<int() &&>();
    test_is_not_trivially_move_assignable<int() const>();
    test_is_not_trivially_move_assignable<int() const&>();
    test_is_not_trivially_move_assignable<int() const&&>();
    test_is_not_trivially_move_assignable<int() volatile>();
    test_is_not_trivially_move_assignable<int() volatile&>();
    test_is_not_trivially_move_assignable<int() volatile&&>();
    test_is_not_trivially_move_assignable<int() const volatile>();
    test_is_not_trivially_move_assignable<int() const volatile&>();
    test_is_not_trivially_move_assignable<int() const volatile&&>();
    test_is_not_trivially_move_assignable<int() noexcept>();
    test_is_not_trivially_move_assignable<int()& noexcept>();
    test_is_not_trivially_move_assignable<int()&& noexcept>();
    test_is_not_trivially_move_assignable<int() const noexcept>();
    test_is_not_trivially_move_assignable<int() const& noexcept>();
    test_is_not_trivially_move_assignable<int() const&& noexcept>();
    test_is_not_trivially_move_assignable<int() volatile noexcept>();
    test_is_not_trivially_move_assignable<int() volatile& noexcept>();
    test_is_not_trivially_move_assignable<int() volatile&& noexcept>();
    test_is_not_trivially_move_assignable<int() const volatile noexcept>();
    test_is_not_trivially_move_assignable<int() const volatile& noexcept>();
    test_is_not_trivially_move_assignable<int() const volatile&& noexcept>();

    test_is_not_trivially_move_assignable<int(int)>();
    test_is_not_trivially_move_assignable<int(int)&>();
    test_is_not_trivially_move_assignable<int(int) &&>();
    test_is_not_trivially_move_assignable<int(int) const>();
    test_is_not_trivially_move_assignable<int(int) const&>();
    test_is_not_trivially_move_assignable<int(int) const&&>();
    test_is_not_trivially_move_assignable<int(int) volatile>();
    test_is_not_trivially_move_assignable<int(int) volatile&>();
    test_is_not_trivially_move_assignable<int(int) volatile&&>();
    test_is_not_trivially_move_assignable<int(int) const volatile>();
    test_is_not_trivially_move_assignable<int(int) const volatile&>();
    test_is_not_trivially_move_assignable<int(int) const volatile&&>();
    test_is_not_trivially_move_assignable<int(int) noexcept>();
    test_is_not_trivially_move_assignable<int(int)& noexcept>();
    test_is_not_trivially_move_assignable<int(int)&& noexcept>();
    test_is_not_trivially_move_assignable<int(int) const noexcept>();
    test_is_not_trivially_move_assignable<int(int) const& noexcept>();
    test_is_not_trivially_move_assignable<int(int) const&& noexcept>();
    test_is_not_trivially_move_assignable<int(int) volatile noexcept>();
    test_is_not_trivially_move_assignable<int(int) volatile& noexcept>();
    test_is_not_trivially_move_assignable<int(int) volatile&& noexcept>();
    test_is_not_trivially_move_assignable<int(int) const volatile noexcept>();
    test_is_not_trivially_move_assignable<int(int) const volatile& noexcept>();
    test_is_not_trivially_move_assignable<int(int) const volatile&& noexcept>();

    test_is_not_trivially_move_assignable<int(...)>();
    test_is_not_trivially_move_assignable<int(...)&>();
    test_is_not_trivially_move_assignable<int(...) &&>();
    test_is_not_trivially_move_assignable<int(...) const>();
    test_is_not_trivially_move_assignable<int(...) const&>();
    test_is_not_trivially_move_assignable<int(...) const&&>();
    test_is_not_trivially_move_assignable<int(...) volatile>();
    test_is_not_trivially_move_assignable<int(...) volatile&>();
    test_is_not_trivially_move_assignable<int(...) volatile&&>();
    test_is_not_trivially_move_assignable<int(...) const volatile>();
    test_is_not_trivially_move_assignable<int(...) const volatile&>();
    test_is_not_trivially_move_assignable<int(...) const volatile&&>();
    test_is_not_trivially_move_assignable<int(...) noexcept>();
    test_is_not_trivially_move_assignable<int(...)& noexcept>();
    test_is_not_trivially_move_assignable<int(...)&& noexcept>();
    test_is_not_trivially_move_assignable<int(...) const noexcept>();
    test_is_not_trivially_move_assignable<int(...) const& noexcept>();
    test_is_not_trivially_move_assignable<int(...) const&& noexcept>();
    test_is_not_trivially_move_assignable<int(...) volatile noexcept>();
    test_is_not_trivially_move_assignable<int(...) volatile& noexcept>();
    test_is_not_trivially_move_assignable<int(...) volatile&& noexcept>();
    test_is_not_trivially_move_assignable<int(...) const volatile noexcept>();
    test_is_not_trivially_move_assignable<int(...) const volatile& noexcept>();
    test_is_not_trivially_move_assignable<int(...) const volatile&& noexcept>();

    test_is_not_trivially_move_assignable<int(int, ...)>();
    test_is_not_trivially_move_assignable<int(int, ...)&>();
    test_is_not_trivially_move_assignable<int(int, ...) &&>();
    test_is_not_trivially_move_assignable<int(int, ...) const>();
    test_is_not_trivially_move_assignable<int(int, ...) const&>();
    test_is_not_trivially_move_assignable<int(int, ...) const&&>();
    test_is_not_trivially_move_assignable<int(int, ...) volatile>();
    test_is_not_trivially_move_assignable<int(int, ...) volatile&>();
    test_is_not_trivially_move_assignable<int(int, ...) volatile&&>();
    test_is_not_trivially_move_assignable<int(int, ...) const volatile>();
    test_is_not_trivially_move_assignable<int(int, ...) const volatile&>();
    test_is_not_trivially_move_assignable<int(int, ...) const volatile&&>();
    test_is_not_trivially_move_assignable<int(int, ...) noexcept>();
    test_is_not_trivially_move_assignable<int(int, ...)& noexcept>();
    test_is_not_trivially_move_assignable<int(int, ...)&& noexcept>();
    test_is_not_trivially_move_assignable<int(int, ...) const noexcept>();
    test_is_not_trivially_move_assignable<int(int, ...) const& noexcept>();
    test_is_not_trivially_move_assignable<int(int, ...) const&& noexcept>();
    test_is_not_trivially_move_assignable<int(int, ...) volatile noexcept>();
    test_is_not_trivially_move_assignable<int(int, ...) volatile& noexcept>();
    test_is_not_trivially_move_assignable<int(int, ...) volatile&& noexcept>();
    test_is_not_trivially_move_assignable<int(int, ...) const volatile noexcept>();
    test_is_not_trivially_move_assignable<int(int, ...) const volatile& noexcept>();
    test_is_not_trivially_move_assignable<int(int, ...) const volatile&& noexcept>();

    test_is_trivially_move_assignable_v<void (*)()>();
    test_is_trivially_move_assignable_v<void (*)() noexcept>();

    test_is_trivially_move_assignable_v<void (*)(int)>();
    test_is_trivially_move_assignable_v<void (*)(int) noexcept>();

    test_is_trivially_move_assignable_v<void (*)(...)>();
    test_is_trivially_move_assignable_v<void (*)(...) noexcept>();

    test_is_trivially_move_assignable_v<void (*)(int, ...)>();
    test_is_trivially_move_assignable_v<void (*)(int, ...) noexcept>();

    test_is_trivially_move_assignable_v<int (*)()>();
    test_is_trivially_move_assignable_v<int (*)() noexcept>();

    test_is_trivially_move_assignable_v<int (*)(int)>();
    test_is_trivially_move_assignable_v<int (*)(int) noexcept>();

    test_is_trivially_move_assignable_v<int (*)(...)>();
    test_is_trivially_move_assignable_v<int (*)(...) noexcept>();

    test_is_trivially_move_assignable_v<int (*)(int, ...)>();
    test_is_trivially_move_assignable_v<int (*)(int, ...) noexcept>();

    test_is_not_trivially_move_assignable<void (&)()>();
    test_is_not_trivially_move_assignable<void (&)() noexcept>();

    test_is_not_trivially_move_assignable<void (&)(int)>();
    test_is_not_trivially_move_assignable<void (&)(int) noexcept>();

    test_is_not_trivially_move_assignable<void (&)(...)>();
    test_is_not_trivially_move_assignable<void (&)(...) noexcept>();

    test_is_not_trivially_move_assignable<void (&)(int, ...)>();
    test_is_not_trivially_move_assignable<void (&)(int, ...) noexcept>();

    test_is_not_trivially_move_assignable<int (&)()>();
    test_is_not_trivially_move_assignable<int (&)() noexcept>();

    test_is_not_trivially_move_assignable<int (&)(int)>();
    test_is_not_trivially_move_assignable<int (&)(int) noexcept>();

    test_is_not_trivially_move_assignable<int (&)(...)>();
    test_is_not_trivially_move_assignable<int (&)(...) noexcept>();

    test_is_not_trivially_move_assignable<int (&)(int, ...)>();
    test_is_not_trivially_move_assignable<int (&)(int, ...) noexcept>();

    test_is_not_trivially_move_assignable<void(&&)()>();
    test_is_not_trivially_move_assignable<void(&&)() noexcept>();

    test_is_not_trivially_move_assignable<void(&&)(int)>();
    test_is_not_trivially_move_assignable<void(&&)(int) noexcept>();

    test_is_not_trivially_move_assignable<void(&&)(...)>();
    test_is_not_trivially_move_assignable<void(&&)(...) noexcept>();

    test_is_not_trivially_move_assignable<void(&&)(int, ...)>();
    test_is_not_trivially_move_assignable<void(&&)(int, ...) noexcept>();

    test_is_not_trivially_move_assignable<int(&&)()>();
    test_is_not_trivially_move_assignable<int(&&)() noexcept>();

    test_is_not_trivially_move_assignable<int(&&)(int)>();
    test_is_not_trivially_move_assignable<int(&&)(int) noexcept>();

    test_is_not_trivially_move_assignable<int(&&)(...)>();
    test_is_not_trivially_move_assignable<int(&&)(...) noexcept>();

    test_is_not_trivially_move_assignable<int(&&)(int, ...)>();
    test_is_not_trivially_move_assignable<int(&&)(int, ...) noexcept>();

    test_is_trivially_move_assignable_v<void (Class::*)()>();
    test_is_trivially_move_assignable_v<void (Class::*)()&>();
    test_is_trivially_move_assignable_v<void (Class::*)() &&>();
    test_is_trivially_move_assignable_v<void (Class::*)() const>();
    test_is_trivially_move_assignable_v<void (Class::*)() const&>();
    test_is_trivially_move_assignable_v<void (Class::*)() const&&>();
    test_is_trivially_move_assignable_v<void (Class::*)() noexcept>();
    test_is_trivially_move_assignable_v<void (Class::*)()& noexcept>();
    test_is_trivially_move_assignable_v<void (Class::*)()&& noexcept>();
    test_is_trivially_move_assignable_v<void (Class::*)() const noexcept>();
    test_is_trivially_move_assignable_v<void (Class::*)() const& noexcept>();
    test_is_trivially_move_assignable_v<void (Class::*)() const&& noexcept>();

    test_is_trivially_move_assignable_v<void (Class::*)(int)>();
    test_is_trivially_move_assignable_v<void (Class::*)(int)&>();
    test_is_trivially_move_assignable_v<void (Class::*)(int) &&>();
    test_is_trivially_move_assignable_v<void (Class::*)(int) const>();
    test_is_trivially_move_assignable_v<void (Class::*)(int) const&>();
    test_is_trivially_move_assignable_v<void (Class::*)(int) const&&>();
    test_is_trivially_move_assignable_v<void (Class::*)(int) noexcept>();
    test_is_trivially_move_assignable_v<void (Class::*)(int)& noexcept>();
    test_is_trivially_move_assignable_v<void (Class::*)(int)&& noexcept>();
    test_is_trivially_move_assignable_v<void (Class::*)(int) const noexcept>();
    test_is_trivially_move_assignable_v<void (Class::*)(int) const& noexcept>();
    test_is_trivially_move_assignable_v<void (Class::*)(int) const&& noexcept>();

    test_is_trivially_move_assignable_v<void (Class::*)(...)>();
    test_is_trivially_move_assignable_v<void (Class::*)(...)&>();
    test_is_trivially_move_assignable_v<void (Class::*)(...) &&>();
    test_is_trivially_move_assignable_v<void (Class::*)(...) const>();
    test_is_trivially_move_assignable_v<void (Class::*)(...) const&>();
    test_is_trivially_move_assignable_v<void (Class::*)(...) const&&>();
    test_is_trivially_move_assignable_v<void (Class::*)(...) noexcept>();
    test_is_trivially_move_assignable_v<void (Class::*)(...)& noexcept>();
    test_is_trivially_move_assignable_v<void (Class::*)(...)&& noexcept>();
    test_is_trivially_move_assignable_v<void (Class::*)(...) const noexcept>();
    test_is_trivially_move_assignable_v<void (Class::*)(...) const& noexcept>();
    test_is_trivially_move_assignable_v<void (Class::*)(...) const&& noexcept>();

    test_is_trivially_move_assignable_v<void (Class::*)(int, ...)>();
    test_is_trivially_move_assignable_v<void (Class::*)(int, ...)&>();
    test_is_trivially_move_assignable_v<void (Class::*)(int, ...) &&>();
    test_is_trivially_move_assignable_v<void (Class::*)(int, ...) const>();
    test_is_trivially_move_assignable_v<void (Class::*)(int, ...) const&>();
    test_is_trivially_move_assignable_v<void (Class::*)(int, ...) const&&>();
    test_is_trivially_move_assignable_v<void (Class::*)(int, ...) noexcept>();
    test_is_trivially_move_assignable_v<void (Class::*)(int, ...)& noexcept>();
    test_is_trivially_move_assignable_v<void (Class::*)(int, ...)&& noexcept>();
    test_is_trivially_move_assignable_v<void (Class::*)(int, ...) const noexcept>();
    test_is_trivially_move_assignable_v<void (Class::*)(int, ...) const& noexcept>();
    test_is_trivially_move_assignable_v<void (Class::*)(int, ...) const&& noexcept>();

    test_is_trivially_move_assignable_v<int (Class::*)()>();
    test_is_trivially_move_assignable_v<int (Class::*)()&>();
    test_is_trivially_move_assignable_v<int (Class::*)() &&>();
    test_is_trivially_move_assignable_v<int (Class::*)() const>();
    test_is_trivially_move_assignable_v<int (Class::*)() const&>();
    test_is_trivially_move_assignable_v<int (Class::*)() const&&>();
    test_is_trivially_move_assignable_v<int (Class::*)() noexcept>();
    test_is_trivially_move_assignable_v<int (Class::*)()& noexcept>();
    test_is_trivially_move_assignable_v<int (Class::*)()&& noexcept>();
    test_is_trivially_move_assignable_v<int (Class::*)() const noexcept>();
    test_is_trivially_move_assignable_v<int (Class::*)() const& noexcept>();
    test_is_trivially_move_assignable_v<int (Class::*)() const&& noexcept>();

    test_is_trivially_move_assignable_v<int (Class::*)(int)>();
    test_is_trivially_move_assignable_v<int (Class::*)(int)&>();
    test_is_trivially_move_assignable_v<int (Class::*)(int) &&>();
    test_is_trivially_move_assignable_v<int (Class::*)(int) const>();
    test_is_trivially_move_assignable_v<int (Class::*)(int) const&>();
    test_is_trivially_move_assignable_v<int (Class::*)(int) const&&>();
    test_is_trivially_move_assignable_v<int (Class::*)(int) noexcept>();
    test_is_trivially_move_assignable_v<int (Class::*)(int)& noexcept>();
    test_is_trivially_move_assignable_v<int (Class::*)(int)&& noexcept>();
    test_is_trivially_move_assignable_v<int (Class::*)(int) const noexcept>();
    test_is_trivially_move_assignable_v<int (Class::*)(int) const& noexcept>();
    test_is_trivially_move_assignable_v<int (Class::*)(int) const&& noexcept>();

    test_is_trivially_move_assignable_v<int (Class::*)(...)>();
    test_is_trivially_move_assignable_v<int (Class::*)(...)&>();
    test_is_trivially_move_assignable_v<int (Class::*)(...) &&>();
    test_is_trivially_move_assignable_v<int (Class::*)(...) const>();
    test_is_trivially_move_assignable_v<int (Class::*)(...) const&>();
    test_is_trivially_move_assignable_v<int (Class::*)(...) const&&>();
    test_is_trivially_move_assignable_v<int (Class::*)(...) noexcept>();
    test_is_trivially_move_assignable_v<int (Class::*)(...)& noexcept>();
    test_is_trivially_move_assignable_v<int (Class::*)(...)&& noexcept>();
    test_is_trivially_move_assignable_v<int (Class::*)(...) const noexcept>();
    test_is_trivially_move_assignable_v<int (Class::*)(...) const& noexcept>();
    test_is_trivially_move_assignable_v<int (Class::*)(...) const&& noexcept>();

    test_is_trivially_move_assignable_v<int (Class::*)(int, ...)>();
    test_is_trivially_move_assignable_v<int (Class::*)(int, ...)&>();
    test_is_trivially_move_assignable_v<int (Class::*)(int, ...) &&>();
    test_is_trivially_move_assignable_v<int (Class::*)(int, ...) const>();
    test_is_trivially_move_assignable_v<int (Class::*)(int, ...) const&>();
    test_is_trivially_move_assignable_v<int (Class::*)(int, ...) const&&>();
    test_is_trivially_move_assignable_v<int (Class::*)(int, ...) noexcept>();
    test_is_trivially_move_assignable_v<int (Class::*)(int, ...)& noexcept>();
    test_is_trivially_move_assignable_v<int (Class::*)(int, ...)&& noexcept>();
    test_is_trivially_move_assignable_v<int (Class::*)(int, ...) const noexcept>();
    test_is_trivially_move_assignable_v<int (Class::*)(int, ...) const& noexcept>();
    test_is_trivially_move_assignable_v<int (Class::*)(int, ...) const&& noexcept>();
}
