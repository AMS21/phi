#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/compiler_support/compiler.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_copy_constructible.hpp>
#include <type_traits>
#include <vector>

// TODO: A lot of these tests currently don't work with MSVC correctly

template <typename T>
void test_is_copy_constructible_impl()
{
    STATIC_REQUIRE(phi::is_copy_constructible<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_copy_constructible<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_copy_constructible_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_not_copy_constructible_v<T>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_copy_constructible<T>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_copy_constructible<T>);

    // Standard compatibility
    STATIC_REQUIRE(std::is_copy_constructible<T>::value);
}

template <typename T>
void test_is_copy_constructible()
{
    test_is_copy_constructible_impl<T>();
    test_is_copy_constructible_impl<const T>();
}

template <typename T>
void test_is_not_copy_constructible_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_copy_constructible<T>::value);
    STATIC_REQUIRE(phi::is_not_copy_constructible<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_copy_constructible_v<T>);
    STATIC_REQUIRE(phi::is_not_copy_constructible_v<T>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_copy_constructible<T>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_copy_constructible<T>);

    // Standard compatibility
    STATIC_REQUIRE_FALSE(std::is_copy_constructible<T>::value);
}

template <typename T>
void test_is_not_copy_constructible()
{
    test_is_not_copy_constructible_impl<T>();
    test_is_not_copy_constructible_impl<const T>();
}

struct A
{
    A(const A&);
};

class B
{
    B(const B&);
};

struct C
{
    C(C&);              // not const
    void operator=(C&); // not const
};

TEST_CASE("is_copy_constructible")
{
    test_is_copy_constructible<A>();
    test_is_not_copy_constructible<B>();
    test_is_not_copy_constructible<C>();

    test_is_not_copy_constructible<void>();
    test_is_copy_constructible<phi::nullptr_t>();
    test_is_copy_constructible<bool>();
    test_is_copy_constructible<char>();
    test_is_copy_constructible<signed char>();
    test_is_copy_constructible<unsigned char>();
    test_is_copy_constructible<short>();
    test_is_copy_constructible<unsigned short>();
    test_is_copy_constructible<int>();
    test_is_copy_constructible<unsigned int>();
    test_is_copy_constructible<long>();
    test_is_copy_constructible<unsigned long>();
    test_is_copy_constructible<long long>();
    test_is_copy_constructible<unsigned long long>();
    test_is_copy_constructible<float>();
    test_is_copy_constructible<double>();
    test_is_copy_constructible<long double>();
    test_is_copy_constructible<char8_t>();
    test_is_copy_constructible<char16_t>();
    test_is_copy_constructible<char32_t>();
    test_is_copy_constructible<wchar_t>();

    test_is_copy_constructible<phi::boolean>();
    test_is_copy_constructible<phi::integer<signed char>>();
    test_is_copy_constructible<phi::integer<unsigned char>>();
    test_is_copy_constructible<phi::integer<short>>();
    test_is_copy_constructible<phi::integer<unsigned short>>();
    test_is_copy_constructible<phi::integer<int>>();
    test_is_copy_constructible<phi::integer<unsigned int>>();
    test_is_copy_constructible<phi::integer<long>>();
    test_is_copy_constructible<phi::integer<unsigned long>>();
    test_is_copy_constructible<phi::integer<long long>>();
    test_is_copy_constructible<phi::integer<unsigned long long>>();
    test_is_copy_constructible<phi::floating_point<float>>();
    test_is_copy_constructible<phi::floating_point<double>>();
    test_is_copy_constructible<phi::floating_point<long double>>();

    test_is_copy_constructible<std::vector<int>>();
    test_is_not_copy_constructible<phi::scope_ptr<int>>();

    test_is_copy_constructible<int&>();
    test_is_copy_constructible<const int&>();
    test_is_copy_constructible<volatile int&>();
    test_is_copy_constructible<const volatile int&>();
    test_is_not_copy_constructible<int&&>();
    test_is_not_copy_constructible<const int&&>();
    test_is_not_copy_constructible<volatile int&&>();
    test_is_not_copy_constructible<const volatile int&&>();
    test_is_copy_constructible<int*>();
    test_is_copy_constructible<const int*>();
    test_is_copy_constructible<volatile int*>();
    test_is_copy_constructible<const volatile int*>();
    test_is_copy_constructible<int**>();
    test_is_copy_constructible<const int**>();
    test_is_copy_constructible<volatile int**>();
    test_is_copy_constructible<const volatile int**>();
    test_is_copy_constructible<int*&>();
    test_is_copy_constructible<const int*&>();
    test_is_copy_constructible<volatile int*&>();
    test_is_copy_constructible<const volatile int*&>();
    test_is_not_copy_constructible<int*&&>();
    test_is_not_copy_constructible<const int*&&>();
    test_is_not_copy_constructible<volatile int*&&>();
    test_is_not_copy_constructible<const volatile int*&&>();
    test_is_copy_constructible<void*>();
    test_is_not_copy_constructible<char[3]>();
#if PHI_SUPPORTS_IS_CONSTRUCTIBLE()
    test_is_not_copy_constructible<char[]>();
    test_is_not_copy_constructible<char*[]>();
    test_is_copy_constructible<int(*)[]>();
    test_is_copy_constructible<int(&)[]>();
    test_is_not_copy_constructible<int(&&)[]>();
    test_is_not_copy_constructible<char[][2]>();
    test_is_not_copy_constructible<char*[][2]>();
    test_is_copy_constructible<int(*)[][2]>();
    test_is_copy_constructible<int(&)[][2]>();
    test_is_not_copy_constructible<int(&&)[][2]>();
#endif
    test_is_not_copy_constructible<char* [3]>();
    test_is_copy_constructible<int(*)[3]>();
    test_is_copy_constructible<int(&)[3]>();
    test_is_not_copy_constructible<int(&&)[3]>();
    test_is_not_copy_constructible<char[3][2]>();
    test_is_not_copy_constructible<char* [3][2]>();
    test_is_copy_constructible<int(*)[3][2]>();
    test_is_copy_constructible<int(&)[3][2]>();
    test_is_not_copy_constructible<int(&&)[3][2]>();
    test_is_copy_constructible<Class>();
#if PHI_SUPPORTS_IS_CONSTRUCTIBLE()
    test_is_not_copy_constructible<Class[]>();
#endif
    test_is_not_copy_constructible<Class[2]>();
    test_is_copy_constructible<Template<void>>();
    test_is_copy_constructible<Template<int>>();
    test_is_copy_constructible<Template<Class>>();
    test_is_copy_constructible<Template<IncompleteType>>();
    test_is_copy_constructible<VariadicTemplate<>>();
    test_is_copy_constructible<VariadicTemplate<void>>();
    test_is_copy_constructible<VariadicTemplate<int>>();
    test_is_copy_constructible<VariadicTemplate<Class>>();
    test_is_copy_constructible<VariadicTemplate<IncompleteType>>();
    test_is_copy_constructible<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_copy_constructible<PublicDerivedFromTemplate<Base>>();
    test_is_copy_constructible<PublicDerivedFromTemplate<Derived>>();
    test_is_copy_constructible<PublicDerivedFromTemplate<Class>>();
    test_is_copy_constructible<PrivateDerivedFromTemplate<Base>>();
    test_is_copy_constructible<PrivateDerivedFromTemplate<Derived>>();
    test_is_copy_constructible<PrivateDerivedFromTemplate<Class>>();
    test_is_copy_constructible<ProtectedDerivedFromTemplate<Base>>();
    test_is_copy_constructible<ProtectedDerivedFromTemplate<Derived>>();
    test_is_copy_constructible<ProtectedDerivedFromTemplate<Class>>();
    test_is_copy_constructible<Union>();
    test_is_copy_constructible<NonEmptyUnion>();
    test_is_copy_constructible<Empty>();
    test_is_copy_constructible<NotEmpty>();
    test_is_copy_constructible<BitZero>();
    test_is_copy_constructible<BitOne>();
    test_is_copy_constructible<Base>();
    test_is_copy_constructible<Derived>();
    test_is_not_copy_constructible<Abstract>();
#if PHI_COMPILER_IS_NOT(MSVC) || PHI_SUPPORTS_IS_CONSTRUCTIBLE()
    test_is_not_copy_constructible<PublicAbstract>();
    test_is_not_copy_constructible<PrivateAbstract>();
    test_is_not_copy_constructible<ProtectedAbstract>();
#endif
#if PHI_SUPPORTS_IS_CONSTRUCTIBLE() && !PHI_HAS_BUG_GCC_102305()
    test_is_not_copy_constructible<AbstractTemplate<int>>();
#endif
    test_is_copy_constructible<AbstractTemplate<double>>();
#if PHI_COMPILER_IS_NOT(GCC) && (PHI_COMPILER_IS_NOT(MSVC) || PHI_SUPPORTS_IS_CONSTRUCTIBLE())
    test_is_not_copy_constructible<AbstractTemplate<Class>>();
#    if PHI_SUPPORTS_IS_CONSTRUCTIBLE()
    test_is_not_copy_constructible<AbstractTemplate<IncompleteType>>();
#    endif
#endif
    test_is_copy_constructible<Final>();
    test_is_copy_constructible<PublicDestructor>();
    test_is_not_copy_constructible<ProtectedDestructor>();
    test_is_not_copy_constructible<PrivateDestructor>();
    test_is_copy_constructible<VirtualPublicDestructor>();
    test_is_not_copy_constructible<VirtualProtectedDestructor>();
    test_is_not_copy_constructible<VirtualPrivateDestructor>();
#if PHI_COMPILER_IS_NOT(MSVC) || PHI_SUPPORTS_IS_CONSTRUCTIBLE()
    test_is_not_copy_constructible<PurePublicDestructor>();
#endif
    test_is_not_copy_constructible<PureProtectedDestructor>();
    test_is_not_copy_constructible<PurePrivateDestructor>();
    test_is_not_copy_constructible<DeletedPublicDestructor>();
    test_is_not_copy_constructible<DeletedProtectedDestructor>();
    test_is_not_copy_constructible<DeletedPrivateDestructor>();
    test_is_not_copy_constructible<DeletedVirtualPublicDestructor>();
    test_is_not_copy_constructible<DeletedVirtualProtectedDestructor>();
    test_is_not_copy_constructible<DeletedVirtualPrivateDestructor>();
#if PHI_COMPILER_IS_NOT(MSVC) || PHI_SUPPORTS_IS_CONSTRUCTIBLE()
    test_is_copy_constructible<Enum>();
    test_is_copy_constructible<EnumSigned>();
    test_is_copy_constructible<EnumUnsigned>();
    test_is_copy_constructible<EnumClass>();
    test_is_copy_constructible<EnumStruct>();
#endif
    test_is_not_copy_constructible<Function>();
#if PHI_COMPILER_IS_NOT(MSVC) || PHI_SUPPORTS_IS_CONSTRUCTIBLE()
    test_is_copy_constructible<FunctionPtr>();
    test_is_copy_constructible<MemberObjectPtr>();
    test_is_copy_constructible<MemberFunctionPtr>();
    test_is_copy_constructible<int Class::*>();
    test_is_copy_constructible<float Class::*>();
    test_is_copy_constructible<void * Class::*>();
    test_is_copy_constructible<int * Class::*>();
#endif
    test_is_copy_constructible<int Class::*&>();
    test_is_copy_constructible<float Class::*&>();
    test_is_copy_constructible<void * Class::*&>();
    test_is_copy_constructible<int * Class::*&>();
    test_is_not_copy_constructible<int Class::*&&>();
    test_is_not_copy_constructible<float Class::*&&>();
    test_is_not_copy_constructible<void * Class::*&&>();
    test_is_not_copy_constructible<int * Class::*&&>();
#if PHI_COMPILER_IS_NOT(MSVC) || PHI_SUPPORTS_IS_CONSTRUCTIBLE()
    test_is_copy_constructible<int Class::*const>();
    test_is_copy_constructible<float Class::*const>();
    test_is_copy_constructible<void * Class::*const>();
#endif
    test_is_copy_constructible<int Class::*const&>();
    test_is_copy_constructible<float Class::*const&>();
    test_is_copy_constructible<void * Class::*const&>();
    test_is_not_copy_constructible<int Class::*const&&>();
    test_is_not_copy_constructible<float Class::*const&&>();
    test_is_not_copy_constructible<void * Class::*const&&>();
#if PHI_COMPILER_IS_NOT(MSVC) || PHI_SUPPORTS_IS_CONSTRUCTIBLE()
    test_is_copy_constructible<int Class::*volatile>();
    test_is_copy_constructible<float Class::*volatile>();
    test_is_copy_constructible<void * Class::*volatile>();
#endif
    test_is_copy_constructible<int Class::*volatile&>();
    test_is_copy_constructible<float Class::*volatile&>();
    test_is_copy_constructible<void * Class::*volatile&>();
    test_is_not_copy_constructible<int Class::*volatile&&>();
    test_is_not_copy_constructible<float Class::*volatile&&>();
    test_is_not_copy_constructible<void * Class::*volatile&&>();
#if PHI_COMPILER_IS_NOT(MSVC) || PHI_SUPPORTS_IS_CONSTRUCTIBLE()
    test_is_copy_constructible<int Class::*const volatile>();
    test_is_copy_constructible<float Class::*const volatile>();
    test_is_copy_constructible<void * Class::*const volatile>();
#endif
    test_is_copy_constructible<int Class::*const volatile&>();
    test_is_copy_constructible<float Class::*const volatile&>();
    test_is_copy_constructible<void * Class::*const volatile&>();
    test_is_not_copy_constructible<int Class::*const volatile&&>();
    test_is_not_copy_constructible<float Class::*const volatile&&>();
    test_is_not_copy_constructible<void * Class::*const volatile&&>();
    test_is_not_copy_constructible<NonCopyable>();
    test_is_copy_constructible<NonMoveable>();
    test_is_not_copy_constructible<NonConstructible>();
    test_is_copy_constructible<Tracked>();
    test_is_copy_constructible<TrapConstructible>();
    test_is_copy_constructible<TrapImplicitConversion>();
    test_is_copy_constructible<TrapComma>();
    test_is_copy_constructible<TrapCall>();
    test_is_copy_constructible<TrapSelfAssign>();
    test_is_copy_constructible<TrapDeref>();
    test_is_copy_constructible<TrapArraySubscript>();

    test_is_not_copy_constructible<void()>();
    test_is_not_copy_constructible<void()&>();
    test_is_not_copy_constructible<void() &&>();
    test_is_not_copy_constructible<void() const>();
    test_is_not_copy_constructible<void() const&>();
    test_is_not_copy_constructible<void() const&&>();
    test_is_not_copy_constructible<void() volatile>();
    test_is_not_copy_constructible<void() volatile&>();
    test_is_not_copy_constructible<void() volatile&&>();
    test_is_not_copy_constructible<void() const volatile>();
    test_is_not_copy_constructible<void() const volatile&>();
    test_is_not_copy_constructible<void() const volatile&&>();
    test_is_not_copy_constructible<void() noexcept>();
    test_is_not_copy_constructible<void()& noexcept>();
    test_is_not_copy_constructible<void()&& noexcept>();
    test_is_not_copy_constructible<void() const noexcept>();
    test_is_not_copy_constructible<void() const& noexcept>();
    test_is_not_copy_constructible<void() const&& noexcept>();
    test_is_not_copy_constructible<void() volatile noexcept>();
    test_is_not_copy_constructible<void() volatile& noexcept>();
    test_is_not_copy_constructible<void() volatile&& noexcept>();
    test_is_not_copy_constructible<void() const volatile noexcept>();
    test_is_not_copy_constructible<void() const volatile& noexcept>();
    test_is_not_copy_constructible<void() const volatile&& noexcept>();

    test_is_not_copy_constructible<void(int)>();
    test_is_not_copy_constructible<void(int)&>();
    test_is_not_copy_constructible<void(int) &&>();
    test_is_not_copy_constructible<void(int) const>();
    test_is_not_copy_constructible<void(int) const&>();
    test_is_not_copy_constructible<void(int) const&&>();
    test_is_not_copy_constructible<void(int) volatile>();
    test_is_not_copy_constructible<void(int) volatile&>();
    test_is_not_copy_constructible<void(int) volatile&&>();
    test_is_not_copy_constructible<void(int) const volatile>();
    test_is_not_copy_constructible<void(int) const volatile&>();
    test_is_not_copy_constructible<void(int) const volatile&&>();
    test_is_not_copy_constructible<void(int) noexcept>();
    test_is_not_copy_constructible<void(int)& noexcept>();
    test_is_not_copy_constructible<void(int)&& noexcept>();
    test_is_not_copy_constructible<void(int) const noexcept>();
    test_is_not_copy_constructible<void(int) const& noexcept>();
    test_is_not_copy_constructible<void(int) const&& noexcept>();
    test_is_not_copy_constructible<void(int) volatile noexcept>();
    test_is_not_copy_constructible<void(int) volatile& noexcept>();
    test_is_not_copy_constructible<void(int) volatile&& noexcept>();
    test_is_not_copy_constructible<void(int) const volatile noexcept>();
    test_is_not_copy_constructible<void(int) const volatile& noexcept>();
    test_is_not_copy_constructible<void(int) const volatile&& noexcept>();

    test_is_not_copy_constructible<void(...)>();
    test_is_not_copy_constructible<void(...)&>();
    test_is_not_copy_constructible<void(...) &&>();
    test_is_not_copy_constructible<void(...) const>();
    test_is_not_copy_constructible<void(...) const&>();
    test_is_not_copy_constructible<void(...) const&&>();
    test_is_not_copy_constructible<void(...) volatile>();
    test_is_not_copy_constructible<void(...) volatile&>();
    test_is_not_copy_constructible<void(...) volatile&&>();
    test_is_not_copy_constructible<void(...) const volatile>();
    test_is_not_copy_constructible<void(...) const volatile&>();
    test_is_not_copy_constructible<void(...) const volatile&&>();
    test_is_not_copy_constructible<void(...) noexcept>();
    test_is_not_copy_constructible<void(...)& noexcept>();
    test_is_not_copy_constructible<void(...)&& noexcept>();
    test_is_not_copy_constructible<void(...) const noexcept>();
    test_is_not_copy_constructible<void(...) const& noexcept>();
    test_is_not_copy_constructible<void(...) const&& noexcept>();
    test_is_not_copy_constructible<void(...) volatile noexcept>();
    test_is_not_copy_constructible<void(...) volatile& noexcept>();
    test_is_not_copy_constructible<void(...) volatile&& noexcept>();
    test_is_not_copy_constructible<void(...) const volatile noexcept>();
    test_is_not_copy_constructible<void(...) const volatile& noexcept>();
    test_is_not_copy_constructible<void(...) const volatile&& noexcept>();

    test_is_not_copy_constructible<void(int, ...)>();
    test_is_not_copy_constructible<void(int, ...)&>();
    test_is_not_copy_constructible<void(int, ...) &&>();
    test_is_not_copy_constructible<void(int, ...) const>();
    test_is_not_copy_constructible<void(int, ...) const&>();
    test_is_not_copy_constructible<void(int, ...) const&&>();
    test_is_not_copy_constructible<void(int, ...) volatile>();
    test_is_not_copy_constructible<void(int, ...) volatile&>();
    test_is_not_copy_constructible<void(int, ...) volatile&&>();
    test_is_not_copy_constructible<void(int, ...) const volatile>();
    test_is_not_copy_constructible<void(int, ...) const volatile&>();
    test_is_not_copy_constructible<void(int, ...) const volatile&&>();
    test_is_not_copy_constructible<void(int, ...) noexcept>();
    test_is_not_copy_constructible<void(int, ...)& noexcept>();
    test_is_not_copy_constructible<void(int, ...)&& noexcept>();
    test_is_not_copy_constructible<void(int, ...) const noexcept>();
    test_is_not_copy_constructible<void(int, ...) const& noexcept>();
    test_is_not_copy_constructible<void(int, ...) const&& noexcept>();
    test_is_not_copy_constructible<void(int, ...) volatile noexcept>();
    test_is_not_copy_constructible<void(int, ...) volatile& noexcept>();
    test_is_not_copy_constructible<void(int, ...) volatile&& noexcept>();
    test_is_not_copy_constructible<void(int, ...) const volatile noexcept>();
    test_is_not_copy_constructible<void(int, ...) const volatile& noexcept>();
    test_is_not_copy_constructible<void(int, ...) const volatile&& noexcept>();

    test_is_not_copy_constructible<int()>();
    test_is_not_copy_constructible<int()&>();
    test_is_not_copy_constructible<int() &&>();
    test_is_not_copy_constructible<int() const>();
    test_is_not_copy_constructible<int() const&>();
    test_is_not_copy_constructible<int() const&&>();
    test_is_not_copy_constructible<int() volatile>();
    test_is_not_copy_constructible<int() volatile&>();
    test_is_not_copy_constructible<int() volatile&&>();
    test_is_not_copy_constructible<int() const volatile>();
    test_is_not_copy_constructible<int() const volatile&>();
    test_is_not_copy_constructible<int() const volatile&&>();
    test_is_not_copy_constructible<int() noexcept>();
    test_is_not_copy_constructible<int()& noexcept>();
    test_is_not_copy_constructible<int()&& noexcept>();
    test_is_not_copy_constructible<int() const noexcept>();
    test_is_not_copy_constructible<int() const& noexcept>();
    test_is_not_copy_constructible<int() const&& noexcept>();
    test_is_not_copy_constructible<int() volatile noexcept>();
    test_is_not_copy_constructible<int() volatile& noexcept>();
    test_is_not_copy_constructible<int() volatile&& noexcept>();
    test_is_not_copy_constructible<int() const volatile noexcept>();
    test_is_not_copy_constructible<int() const volatile& noexcept>();
    test_is_not_copy_constructible<int() const volatile&& noexcept>();

    test_is_not_copy_constructible<int(int)>();
    test_is_not_copy_constructible<int(int)&>();
    test_is_not_copy_constructible<int(int) &&>();
    test_is_not_copy_constructible<int(int) const>();
    test_is_not_copy_constructible<int(int) const&>();
    test_is_not_copy_constructible<int(int) const&&>();
    test_is_not_copy_constructible<int(int) volatile>();
    test_is_not_copy_constructible<int(int) volatile&>();
    test_is_not_copy_constructible<int(int) volatile&&>();
    test_is_not_copy_constructible<int(int) const volatile>();
    test_is_not_copy_constructible<int(int) const volatile&>();
    test_is_not_copy_constructible<int(int) const volatile&&>();
    test_is_not_copy_constructible<int(int) noexcept>();
    test_is_not_copy_constructible<int(int)& noexcept>();
    test_is_not_copy_constructible<int(int)&& noexcept>();
    test_is_not_copy_constructible<int(int) const noexcept>();
    test_is_not_copy_constructible<int(int) const& noexcept>();
    test_is_not_copy_constructible<int(int) const&& noexcept>();
    test_is_not_copy_constructible<int(int) volatile noexcept>();
    test_is_not_copy_constructible<int(int) volatile& noexcept>();
    test_is_not_copy_constructible<int(int) volatile&& noexcept>();
    test_is_not_copy_constructible<int(int) const volatile noexcept>();
    test_is_not_copy_constructible<int(int) const volatile& noexcept>();
    test_is_not_copy_constructible<int(int) const volatile&& noexcept>();

    test_is_not_copy_constructible<int(...)>();
    test_is_not_copy_constructible<int(...)&>();
    test_is_not_copy_constructible<int(...) &&>();
    test_is_not_copy_constructible<int(...) const>();
    test_is_not_copy_constructible<int(...) const&>();
    test_is_not_copy_constructible<int(...) const&&>();
    test_is_not_copy_constructible<int(...) volatile>();
    test_is_not_copy_constructible<int(...) volatile&>();
    test_is_not_copy_constructible<int(...) volatile&&>();
    test_is_not_copy_constructible<int(...) const volatile>();
    test_is_not_copy_constructible<int(...) const volatile&>();
    test_is_not_copy_constructible<int(...) const volatile&&>();
    test_is_not_copy_constructible<int(...) noexcept>();
    test_is_not_copy_constructible<int(...)& noexcept>();
    test_is_not_copy_constructible<int(...)&& noexcept>();
    test_is_not_copy_constructible<int(...) const noexcept>();
    test_is_not_copy_constructible<int(...) const& noexcept>();
    test_is_not_copy_constructible<int(...) const&& noexcept>();
    test_is_not_copy_constructible<int(...) volatile noexcept>();
    test_is_not_copy_constructible<int(...) volatile& noexcept>();
    test_is_not_copy_constructible<int(...) volatile&& noexcept>();
    test_is_not_copy_constructible<int(...) const volatile noexcept>();
    test_is_not_copy_constructible<int(...) const volatile& noexcept>();
    test_is_not_copy_constructible<int(...) const volatile&& noexcept>();

    test_is_not_copy_constructible<int(int, ...)>();
    test_is_not_copy_constructible<int(int, ...)&>();
    test_is_not_copy_constructible<int(int, ...) &&>();
    test_is_not_copy_constructible<int(int, ...) const>();
    test_is_not_copy_constructible<int(int, ...) const&>();
    test_is_not_copy_constructible<int(int, ...) const&&>();
    test_is_not_copy_constructible<int(int, ...) volatile>();
    test_is_not_copy_constructible<int(int, ...) volatile&>();
    test_is_not_copy_constructible<int(int, ...) volatile&&>();
    test_is_not_copy_constructible<int(int, ...) const volatile>();
    test_is_not_copy_constructible<int(int, ...) const volatile&>();
    test_is_not_copy_constructible<int(int, ...) const volatile&&>();
    test_is_not_copy_constructible<int(int, ...) noexcept>();
    test_is_not_copy_constructible<int(int, ...)& noexcept>();
    test_is_not_copy_constructible<int(int, ...)&& noexcept>();
    test_is_not_copy_constructible<int(int, ...) const noexcept>();
    test_is_not_copy_constructible<int(int, ...) const& noexcept>();
    test_is_not_copy_constructible<int(int, ...) const&& noexcept>();
    test_is_not_copy_constructible<int(int, ...) volatile noexcept>();
    test_is_not_copy_constructible<int(int, ...) volatile& noexcept>();
    test_is_not_copy_constructible<int(int, ...) volatile&& noexcept>();
    test_is_not_copy_constructible<int(int, ...) const volatile noexcept>();
    test_is_not_copy_constructible<int(int, ...) const volatile& noexcept>();
    test_is_not_copy_constructible<int(int, ...) const volatile&& noexcept>();

#if PHI_COMPILER_IS_NOT(MSVC) || PHI_SUPPORTS_IS_CONSTRUCTIBLE()
    test_is_copy_constructible<void (*)()>();
    test_is_copy_constructible<void (*)() noexcept>();

    test_is_copy_constructible<void (*)(int)>();
    test_is_copy_constructible<void (*)(int) noexcept>();

    test_is_copy_constructible<void (*)(...)>();
    test_is_copy_constructible<void (*)(...) noexcept>();

    test_is_copy_constructible<void (*)(int, ...)>();
    test_is_copy_constructible<void (*)(int, ...) noexcept>();

    test_is_copy_constructible<int (*)()>();
    test_is_copy_constructible<int (*)() noexcept>();

    test_is_copy_constructible<int (*)(int)>();
    test_is_copy_constructible<int (*)(int) noexcept>();

    test_is_copy_constructible<int (*)(...)>();
    test_is_copy_constructible<int (*)(...) noexcept>();

    test_is_copy_constructible<int (*)(int, ...)>();
    test_is_copy_constructible<int (*)(int, ...) noexcept>();
#endif

    test_is_copy_constructible<void (&)()>();
    test_is_copy_constructible<void (&)() noexcept>();

    test_is_copy_constructible<void (&)(int)>();
    test_is_copy_constructible<void (&)(int) noexcept>();

    test_is_copy_constructible<void (&)(...)>();
    test_is_copy_constructible<void (&)(...) noexcept>();

    test_is_copy_constructible<void (&)(int, ...)>();
    test_is_copy_constructible<void (&)(int, ...) noexcept>();

    test_is_copy_constructible<int (&)()>();
    test_is_copy_constructible<int (&)() noexcept>();

    test_is_copy_constructible<int (&)(int)>();
    test_is_copy_constructible<int (&)(int) noexcept>();

    test_is_copy_constructible<int (&)(...)>();
    test_is_copy_constructible<int (&)(...) noexcept>();

    test_is_copy_constructible<int (&)(int, ...)>();
    test_is_copy_constructible<int (&)(int, ...) noexcept>();

    test_is_copy_constructible<void(&&)()>();
    test_is_copy_constructible<void(&&)() noexcept>();

    test_is_copy_constructible<void(&&)(int)>();
    test_is_copy_constructible<void(&&)(int) noexcept>();

    test_is_copy_constructible<void(&&)(...)>();
    test_is_copy_constructible<void(&&)(...) noexcept>();

    test_is_copy_constructible<void(&&)(int, ...)>();
    test_is_copy_constructible<void(&&)(int, ...) noexcept>();

    test_is_copy_constructible<int(&&)()>();
    test_is_copy_constructible<int(&&)() noexcept>();

    test_is_copy_constructible<int(&&)(int)>();
    test_is_copy_constructible<int(&&)(int) noexcept>();

    test_is_copy_constructible<int(&&)(...)>();
    test_is_copy_constructible<int(&&)(...) noexcept>();

    test_is_copy_constructible<int(&&)(int, ...)>();
    test_is_copy_constructible<int(&&)(int, ...) noexcept>();

#if PHI_COMPILER_IS_NOT(MSVC) || PHI_SUPPORTS_IS_CONSTRUCTIBLE()
    test_is_copy_constructible<void (Class::*)()>();
    test_is_copy_constructible<void (Class::*)()&>();
    test_is_copy_constructible<void (Class::*)() &&>();
    test_is_copy_constructible<void (Class::*)() const>();
    test_is_copy_constructible<void (Class::*)() const&>();
    test_is_copy_constructible<void (Class::*)() const&&>();
    test_is_copy_constructible<void (Class::*)() noexcept>();
    test_is_copy_constructible<void (Class::*)()& noexcept>();
    test_is_copy_constructible<void (Class::*)()&& noexcept>();
    test_is_copy_constructible<void (Class::*)() const noexcept>();
    test_is_copy_constructible<void (Class::*)() const& noexcept>();
    test_is_copy_constructible<void (Class::*)() const&& noexcept>();

    test_is_copy_constructible<void (Class::*)(int)>();
    test_is_copy_constructible<void (Class::*)(int)&>();
    test_is_copy_constructible<void (Class::*)(int) &&>();
    test_is_copy_constructible<void (Class::*)(int) const>();
    test_is_copy_constructible<void (Class::*)(int) const&>();
    test_is_copy_constructible<void (Class::*)(int) const&&>();
    test_is_copy_constructible<void (Class::*)(int) noexcept>();
    test_is_copy_constructible<void (Class::*)(int)& noexcept>();
    test_is_copy_constructible<void (Class::*)(int)&& noexcept>();
    test_is_copy_constructible<void (Class::*)(int) const noexcept>();
    test_is_copy_constructible<void (Class::*)(int) const& noexcept>();
    test_is_copy_constructible<void (Class::*)(int) const&& noexcept>();

    test_is_copy_constructible<void (Class::*)(...)>();
    test_is_copy_constructible<void (Class::*)(...)&>();
    test_is_copy_constructible<void (Class::*)(...) &&>();
    test_is_copy_constructible<void (Class::*)(...) const>();
    test_is_copy_constructible<void (Class::*)(...) const&>();
    test_is_copy_constructible<void (Class::*)(...) const&&>();
    test_is_copy_constructible<void (Class::*)(...) noexcept>();
    test_is_copy_constructible<void (Class::*)(...)& noexcept>();
    test_is_copy_constructible<void (Class::*)(...)&& noexcept>();
    test_is_copy_constructible<void (Class::*)(...) const noexcept>();
    test_is_copy_constructible<void (Class::*)(...) const& noexcept>();
    test_is_copy_constructible<void (Class::*)(...) const&& noexcept>();

    test_is_copy_constructible<void (Class::*)(int, ...)>();
    test_is_copy_constructible<void (Class::*)(int, ...)&>();
    test_is_copy_constructible<void (Class::*)(int, ...) &&>();
    test_is_copy_constructible<void (Class::*)(int, ...) const>();
    test_is_copy_constructible<void (Class::*)(int, ...) const&>();
    test_is_copy_constructible<void (Class::*)(int, ...) const&&>();
    test_is_copy_constructible<void (Class::*)(int, ...) noexcept>();
    test_is_copy_constructible<void (Class::*)(int, ...)& noexcept>();
    test_is_copy_constructible<void (Class::*)(int, ...)&& noexcept>();
    test_is_copy_constructible<void (Class::*)(int, ...) const noexcept>();
    test_is_copy_constructible<void (Class::*)(int, ...) const& noexcept>();
    test_is_copy_constructible<void (Class::*)(int, ...) const&& noexcept>();

    test_is_copy_constructible<int (Class::*)()>();
    test_is_copy_constructible<int (Class::*)()&>();
    test_is_copy_constructible<int (Class::*)() &&>();
    test_is_copy_constructible<int (Class::*)() const>();
    test_is_copy_constructible<int (Class::*)() const&>();
    test_is_copy_constructible<int (Class::*)() const&&>();
    test_is_copy_constructible<int (Class::*)() noexcept>();
    test_is_copy_constructible<int (Class::*)()& noexcept>();
    test_is_copy_constructible<int (Class::*)()&& noexcept>();
    test_is_copy_constructible<int (Class::*)() const noexcept>();
    test_is_copy_constructible<int (Class::*)() const& noexcept>();
    test_is_copy_constructible<int (Class::*)() const&& noexcept>();

    test_is_copy_constructible<int (Class::*)(int)>();
    test_is_copy_constructible<int (Class::*)(int)&>();
    test_is_copy_constructible<int (Class::*)(int) &&>();
    test_is_copy_constructible<int (Class::*)(int) const>();
    test_is_copy_constructible<int (Class::*)(int) const&>();
    test_is_copy_constructible<int (Class::*)(int) const&&>();
    test_is_copy_constructible<int (Class::*)(int) noexcept>();
    test_is_copy_constructible<int (Class::*)(int)& noexcept>();
    test_is_copy_constructible<int (Class::*)(int)&& noexcept>();
    test_is_copy_constructible<int (Class::*)(int) const noexcept>();
    test_is_copy_constructible<int (Class::*)(int) const& noexcept>();
    test_is_copy_constructible<int (Class::*)(int) const&& noexcept>();

    test_is_copy_constructible<int (Class::*)(...)>();
    test_is_copy_constructible<int (Class::*)(...)&>();
    test_is_copy_constructible<int (Class::*)(...) &&>();
    test_is_copy_constructible<int (Class::*)(...) const>();
    test_is_copy_constructible<int (Class::*)(...) const&>();
    test_is_copy_constructible<int (Class::*)(...) const&&>();
    test_is_copy_constructible<int (Class::*)(...) noexcept>();
    test_is_copy_constructible<int (Class::*)(...)& noexcept>();
    test_is_copy_constructible<int (Class::*)(...)&& noexcept>();
    test_is_copy_constructible<int (Class::*)(...) const noexcept>();
    test_is_copy_constructible<int (Class::*)(...) const& noexcept>();
    test_is_copy_constructible<int (Class::*)(...) const&& noexcept>();

    test_is_copy_constructible<int (Class::*)(int, ...)>();
    test_is_copy_constructible<int (Class::*)(int, ...)&>();
    test_is_copy_constructible<int (Class::*)(int, ...) &&>();
    test_is_copy_constructible<int (Class::*)(int, ...) const>();
    test_is_copy_constructible<int (Class::*)(int, ...) const&>();
    test_is_copy_constructible<int (Class::*)(int, ...) const&&>();
    test_is_copy_constructible<int (Class::*)(int, ...) noexcept>();
    test_is_copy_constructible<int (Class::*)(int, ...)& noexcept>();
    test_is_copy_constructible<int (Class::*)(int, ...)&& noexcept>();
    test_is_copy_constructible<int (Class::*)(int, ...) const noexcept>();
    test_is_copy_constructible<int (Class::*)(int, ...) const& noexcept>();
    test_is_copy_constructible<int (Class::*)(int, ...) const&& noexcept>();
#endif
}
