#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include "type_traits_helper.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_function_pointer.hpp>
#include <vector>

template <typename T>
void test_is_function_pointer_impl()
{
    STATIC_REQUIRE(phi::is_function_pointer<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_function_pointer<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_function_pointer_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_not_function_pointer_v<T>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_function_pointer<T>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_function_pointer<T>);
}

template <typename T>
void test_is_function_pointer()
{
    test_is_function_pointer_impl<T>();
    test_is_function_pointer_impl<const T>();
    test_is_function_pointer_impl<volatile T>();
    test_is_function_pointer_impl<const volatile T>();
}

template <typename T>
void test_is_not_function_pointer_impl()
{
    STATIC_REQUIRE_FALSE(phi::is_function_pointer<T>::value);
    STATIC_REQUIRE(phi::is_not_function_pointer<T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_function_pointer_v<T>);
    STATIC_REQUIRE(phi::is_not_function_pointer_v<T>);
#endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_function_pointer<T>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_function_pointer<T>);
}

template <typename T>
void test_is_not_function_pointer()
{
    test_is_not_function_pointer_impl<T>();
    test_is_not_function_pointer_impl<const T>();
    test_is_not_function_pointer_impl<volatile T>();
    test_is_not_function_pointer_impl<const volatile T>();
}

TEST_CASE("is_function_pointer")
{
    test_is_not_function_pointer<void>();
    test_is_not_function_pointer<phi::nullptr_t>();
    test_is_not_function_pointer<bool>();
    test_is_not_function_pointer<char>();
    test_is_not_function_pointer<signed char>();
    test_is_not_function_pointer<unsigned char>();
    test_is_not_function_pointer<short>();
    test_is_not_function_pointer<unsigned short>();
    test_is_not_function_pointer<int>();
    test_is_not_function_pointer<unsigned int>();
    test_is_not_function_pointer<long>();
    test_is_not_function_pointer<unsigned long>();
    test_is_not_function_pointer<long long>();
    test_is_not_function_pointer<unsigned long long>();
    test_is_not_function_pointer<float>();
    test_is_not_function_pointer<double>();
    test_is_not_function_pointer<long double>();
    test_is_not_function_pointer<char8_t>();
    test_is_not_function_pointer<char16_t>();
    test_is_not_function_pointer<char32_t>();
    test_is_not_function_pointer<wchar_t>();

    test_is_not_function_pointer<phi::boolean>();
    test_is_not_function_pointer<phi::integer<signed char>>();
    test_is_not_function_pointer<phi::integer<unsigned char>>();
    test_is_not_function_pointer<phi::integer<short>>();
    test_is_not_function_pointer<phi::integer<unsigned short>>();
    test_is_not_function_pointer<phi::integer<int>>();
    test_is_not_function_pointer<phi::integer<unsigned int>>();
    test_is_not_function_pointer<phi::integer<long>>();
    test_is_not_function_pointer<phi::integer<unsigned long>>();
    test_is_not_function_pointer<phi::integer<long long>>();
    test_is_not_function_pointer<phi::integer<unsigned long long>>();
    test_is_not_function_pointer<phi::floating_point<float>>();
    test_is_not_function_pointer<phi::floating_point<double>>();
    test_is_not_function_pointer<phi::floating_point<long double>>();

    test_is_not_function_pointer<std::vector<int>>();
    test_is_not_function_pointer<phi::scope_ptr<int>>();

    test_is_not_function_pointer<int&>();
    test_is_not_function_pointer<const int&>();
    test_is_not_function_pointer<volatile int&>();
    test_is_not_function_pointer<const volatile int&>();
    test_is_not_function_pointer<int&&>();
    test_is_not_function_pointer<const int&&>();
    test_is_not_function_pointer<volatile int&&>();
    test_is_not_function_pointer<const volatile int&&>();
    test_is_not_function_pointer<int*>();
    test_is_not_function_pointer<const int*>();
    test_is_not_function_pointer<volatile int*>();
    test_is_not_function_pointer<const volatile int*>();
    test_is_not_function_pointer<int**>();
    test_is_not_function_pointer<const int**>();
    test_is_not_function_pointer<volatile int**>();
    test_is_not_function_pointer<const volatile int**>();
    test_is_not_function_pointer<int*&>();
    test_is_not_function_pointer<const int*&>();
    test_is_not_function_pointer<volatile int*&>();
    test_is_not_function_pointer<const volatile int*&>();
    test_is_not_function_pointer<int*&&>();
    test_is_not_function_pointer<const int*&&>();
    test_is_not_function_pointer<volatile int*&&>();
    test_is_not_function_pointer<const volatile int*&&>();
    test_is_not_function_pointer<void*>();
    test_is_not_function_pointer<char[3]>();
    test_is_not_function_pointer<char[]>();
    test_is_not_function_pointer<char* [3]>();
    test_is_not_function_pointer<char*[]>();
    test_is_not_function_pointer<int(*)[3]>();
    test_is_not_function_pointer<int(*)[]>();
    test_is_not_function_pointer<int(&)[3]>();
    test_is_not_function_pointer<int(&)[]>();
    test_is_not_function_pointer<int(&&)[3]>();
    test_is_not_function_pointer<int(&&)[]>();
    test_is_not_function_pointer<char[3][2]>();
    test_is_not_function_pointer<char[][2]>();
    test_is_not_function_pointer<char* [3][2]>();
    test_is_not_function_pointer<char*[][2]>();
    test_is_not_function_pointer<int(*)[3][2]>();
    test_is_not_function_pointer<int(*)[][2]>();
    test_is_not_function_pointer<int(&)[3][2]>();
    test_is_not_function_pointer<int(&)[][2]>();
    test_is_not_function_pointer<int(&&)[3][2]>();
    test_is_not_function_pointer<int(&&)[][2]>();
    test_is_not_function_pointer<Class>();
    test_is_not_function_pointer<Class[]>();
    test_is_not_function_pointer<Class[2]>();
    test_is_not_function_pointer<Template<void>>();
    test_is_not_function_pointer<Template<int>>();
    test_is_not_function_pointer<Template<Class>>();
    test_is_not_function_pointer<Template<IncompleteType>>();
    test_is_not_function_pointer<VariadicTemplate<>>();
    test_is_not_function_pointer<VariadicTemplate<void>>();
    test_is_not_function_pointer<VariadicTemplate<int>>();
    test_is_not_function_pointer<VariadicTemplate<Class>>();
    test_is_not_function_pointer<VariadicTemplate<IncompleteType>>();
    test_is_not_function_pointer<VariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_function_pointer<PublicDerivedFromTemplate<Base>>();
    test_is_not_function_pointer<PublicDerivedFromTemplate<Derived>>();
    test_is_not_function_pointer<PublicDerivedFromTemplate<Class>>();
    test_is_not_function_pointer<PrivateDerivedFromTemplate<Base>>();
    test_is_not_function_pointer<PrivateDerivedFromTemplate<Derived>>();
    test_is_not_function_pointer<PrivateDerivedFromTemplate<Class>>();
    test_is_not_function_pointer<ProtectedDerivedFromTemplate<Base>>();
    test_is_not_function_pointer<ProtectedDerivedFromTemplate<Derived>>();
    test_is_not_function_pointer<ProtectedDerivedFromTemplate<Class>>();
    test_is_not_function_pointer<Union>();
    test_is_not_function_pointer<NonEmptyUnion>();
    test_is_not_function_pointer<Empty>();
    test_is_not_function_pointer<NotEmpty>();
    test_is_not_function_pointer<BitZero>();
    test_is_not_function_pointer<BitOne>();
    test_is_not_function_pointer<Base>();
    test_is_not_function_pointer<Derived>();
    test_is_not_function_pointer<Abstract>();
    test_is_not_function_pointer<PublicAbstract>();
    test_is_not_function_pointer<PrivateAbstract>();
    test_is_not_function_pointer<ProtectedAbstract>();
    test_is_not_function_pointer<AbstractTemplate<int>>();
    test_is_not_function_pointer<AbstractTemplate<double>>();
    test_is_not_function_pointer<AbstractTemplate<Class>>();
    test_is_not_function_pointer<AbstractTemplate<IncompleteType>>();
    test_is_not_function_pointer<Final>();
    test_is_not_function_pointer<PublicDestructor>();
    test_is_not_function_pointer<ProtectedDestructor>();
    test_is_not_function_pointer<PrivateDestructor>();
    test_is_not_function_pointer<VirtualPublicDestructor>();
    test_is_not_function_pointer<VirtualProtectedDestructor>();
    test_is_not_function_pointer<VirtualPrivateDestructor>();
    test_is_not_function_pointer<PurePublicDestructor>();
    test_is_not_function_pointer<PureProtectedDestructor>();
    test_is_not_function_pointer<PurePrivateDestructor>();
    test_is_not_function_pointer<DeletedPublicDestructor>();
    test_is_not_function_pointer<DeletedProtectedDestructor>();
    test_is_not_function_pointer<DeletedPrivateDestructor>();
    test_is_not_function_pointer<DeletedVirtualPublicDestructor>();
    test_is_not_function_pointer<DeletedVirtualProtectedDestructor>();
    test_is_not_function_pointer<DeletedVirtualPrivateDestructor>();
    test_is_not_function_pointer<Final>();
    test_is_not_function_pointer<Enum>();
    test_is_not_function_pointer<EnumSigned>();
    test_is_not_function_pointer<EnumUnsigned>();
    test_is_not_function_pointer<EnumClass>();
    test_is_not_function_pointer<EnumStruct>();
    test_is_not_function_pointer<Function>();
    test_is_function_pointer<FunctionPtr>();
    test_is_not_function_pointer<MemberObjectPtr>();
    test_is_not_function_pointer<MemberFunctionPtr>();
    test_is_not_function_pointer<IncompleteType>();
    test_is_not_function_pointer<IncompleteTemplate<void>>();
    test_is_not_function_pointer<IncompleteTemplate<int>>();
    test_is_not_function_pointer<IncompleteTemplate<Class>>();
    test_is_not_function_pointer<IncompleteTemplate<IncompleteType>>();
    test_is_not_function_pointer<IncompleteVariadicTemplate<>>();
    test_is_not_function_pointer<IncompleteVariadicTemplate<void>>();
    test_is_not_function_pointer<IncompleteVariadicTemplate<int>>();
    test_is_not_function_pointer<IncompleteVariadicTemplate<Class>>();
    test_is_not_function_pointer<IncompleteVariadicTemplate<IncompleteType>>();
    test_is_not_function_pointer<IncompleteVariadicTemplate<int, void, Class, volatile char[]>>();
    test_is_not_function_pointer<int Class::*>();
    test_is_not_function_pointer<float Class::*>();
    test_is_not_function_pointer<void * Class::*>();
    test_is_not_function_pointer<int * Class::*>();
    test_is_not_function_pointer<int Class::*&>();
    test_is_not_function_pointer<float Class::*&>();
    test_is_not_function_pointer<void * Class::*&>();
    test_is_not_function_pointer<int * Class::*&>();
    test_is_not_function_pointer<int Class::*&&>();
    test_is_not_function_pointer<float Class::*&&>();
    test_is_not_function_pointer<void * Class::*&&>();
    test_is_not_function_pointer<int * Class::*&&>();
    test_is_not_function_pointer<int Class::*const>();
    test_is_not_function_pointer<float Class::*const>();
    test_is_not_function_pointer<void * Class::*const>();
    test_is_not_function_pointer<int Class::*const&>();
    test_is_not_function_pointer<float Class::*const&>();
    test_is_not_function_pointer<void * Class::*const&>();
    test_is_not_function_pointer<int Class::*const&&>();
    test_is_not_function_pointer<float Class::*const&&>();
    test_is_not_function_pointer<void * Class::*const&&>();
    test_is_not_function_pointer<int Class::*volatile>();
    test_is_not_function_pointer<float Class::*volatile>();
    test_is_not_function_pointer<void * Class::*volatile>();
    test_is_not_function_pointer<int Class::*volatile&>();
    test_is_not_function_pointer<float Class::*volatile&>();
    test_is_not_function_pointer<void * Class::*volatile&>();
    test_is_not_function_pointer<int Class::*volatile&&>();
    test_is_not_function_pointer<float Class::*volatile&&>();
    test_is_not_function_pointer<void * Class::*volatile&&>();
    test_is_not_function_pointer<int Class::*const volatile>();
    test_is_not_function_pointer<float Class::*const volatile>();
    test_is_not_function_pointer<void * Class::*const volatile>();
    test_is_not_function_pointer<int Class::*const volatile&>();
    test_is_not_function_pointer<float Class::*const volatile&>();
    test_is_not_function_pointer<void * Class::*const volatile&>();
    test_is_not_function_pointer<int Class::*const volatile&&>();
    test_is_not_function_pointer<float Class::*const volatile&&>();
    test_is_not_function_pointer<void * Class::*const volatile&&>();
    test_is_not_function_pointer<NonCopyable>();
    test_is_not_function_pointer<NonMoveable>();
    test_is_not_function_pointer<NonConstructible>();
    test_is_not_function_pointer<Tracked>();
    test_is_not_function_pointer<TrapConstructible>();
    test_is_not_function_pointer<TrapImplicitConversion>();
    test_is_not_function_pointer<TrapComma>();
    test_is_not_function_pointer<TrapCall>();
    test_is_not_function_pointer<TrapSelfAssign>();
    test_is_not_function_pointer<TrapDeref>();
    test_is_not_function_pointer<TrapArraySubscript>();

    test_is_not_function_pointer<void()>();
    test_is_not_function_pointer<void()&>();
    test_is_not_function_pointer<void() &&>();
    test_is_not_function_pointer<void() const>();
    test_is_not_function_pointer<void() const&>();
    test_is_not_function_pointer<void() const&&>();
    test_is_not_function_pointer<void() volatile>();
    test_is_not_function_pointer<void() volatile&>();
    test_is_not_function_pointer<void() volatile&&>();
    test_is_not_function_pointer<void() const volatile>();
    test_is_not_function_pointer<void() const volatile&>();
    test_is_not_function_pointer<void() const volatile&&>();
    test_is_not_function_pointer<void() noexcept>();
    test_is_not_function_pointer<void()& noexcept>();
    test_is_not_function_pointer<void()&& noexcept>();
    test_is_not_function_pointer<void() const noexcept>();
    test_is_not_function_pointer<void() const& noexcept>();
    test_is_not_function_pointer<void() const&& noexcept>();
    test_is_not_function_pointer<void() volatile noexcept>();
    test_is_not_function_pointer<void() volatile& noexcept>();
    test_is_not_function_pointer<void() volatile&& noexcept>();
    test_is_not_function_pointer<void() const volatile noexcept>();
    test_is_not_function_pointer<void() const volatile& noexcept>();
    test_is_not_function_pointer<void() const volatile&& noexcept>();

    test_is_not_function_pointer<void(int)>();
    test_is_not_function_pointer<void(int)&>();
    test_is_not_function_pointer<void(int) &&>();
    test_is_not_function_pointer<void(int) const>();
    test_is_not_function_pointer<void(int) const&>();
    test_is_not_function_pointer<void(int) const&&>();
    test_is_not_function_pointer<void(int) volatile>();
    test_is_not_function_pointer<void(int) volatile&>();
    test_is_not_function_pointer<void(int) volatile&&>();
    test_is_not_function_pointer<void(int) const volatile>();
    test_is_not_function_pointer<void(int) const volatile&>();
    test_is_not_function_pointer<void(int) const volatile&&>();
    test_is_not_function_pointer<void(int) noexcept>();
    test_is_not_function_pointer<void(int)& noexcept>();
    test_is_not_function_pointer<void(int)&& noexcept>();
    test_is_not_function_pointer<void(int) const noexcept>();
    test_is_not_function_pointer<void(int) const& noexcept>();
    test_is_not_function_pointer<void(int) const&& noexcept>();
    test_is_not_function_pointer<void(int) volatile noexcept>();
    test_is_not_function_pointer<void(int) volatile& noexcept>();
    test_is_not_function_pointer<void(int) volatile&& noexcept>();
    test_is_not_function_pointer<void(int) const volatile noexcept>();
    test_is_not_function_pointer<void(int) const volatile& noexcept>();
    test_is_not_function_pointer<void(int) const volatile&& noexcept>();

    test_is_not_function_pointer<void(...)>();
    test_is_not_function_pointer<void(...)&>();
    test_is_not_function_pointer<void(...) &&>();
    test_is_not_function_pointer<void(...) const>();
    test_is_not_function_pointer<void(...) const&>();
    test_is_not_function_pointer<void(...) const&&>();
    test_is_not_function_pointer<void(...) volatile>();
    test_is_not_function_pointer<void(...) volatile&>();
    test_is_not_function_pointer<void(...) volatile&&>();
    test_is_not_function_pointer<void(...) const volatile>();
    test_is_not_function_pointer<void(...) const volatile&>();
    test_is_not_function_pointer<void(...) const volatile&&>();
    test_is_not_function_pointer<void(...) noexcept>();
    test_is_not_function_pointer<void(...)& noexcept>();
    test_is_not_function_pointer<void(...)&& noexcept>();
    test_is_not_function_pointer<void(...) const noexcept>();
    test_is_not_function_pointer<void(...) const& noexcept>();
    test_is_not_function_pointer<void(...) const&& noexcept>();
    test_is_not_function_pointer<void(...) volatile noexcept>();
    test_is_not_function_pointer<void(...) volatile& noexcept>();
    test_is_not_function_pointer<void(...) volatile&& noexcept>();
    test_is_not_function_pointer<void(...) const volatile noexcept>();
    test_is_not_function_pointer<void(...) const volatile& noexcept>();
    test_is_not_function_pointer<void(...) const volatile&& noexcept>();

    test_is_not_function_pointer<void(int, ...)>();
    test_is_not_function_pointer<void(int, ...)&>();
    test_is_not_function_pointer<void(int, ...) &&>();
    test_is_not_function_pointer<void(int, ...) const>();
    test_is_not_function_pointer<void(int, ...) const&>();
    test_is_not_function_pointer<void(int, ...) const&&>();
    test_is_not_function_pointer<void(int, ...) volatile>();
    test_is_not_function_pointer<void(int, ...) volatile&>();
    test_is_not_function_pointer<void(int, ...) volatile&&>();
    test_is_not_function_pointer<void(int, ...) const volatile>();
    test_is_not_function_pointer<void(int, ...) const volatile&>();
    test_is_not_function_pointer<void(int, ...) const volatile&&>();
    test_is_not_function_pointer<void(int, ...) noexcept>();
    test_is_not_function_pointer<void(int, ...)& noexcept>();
    test_is_not_function_pointer<void(int, ...)&& noexcept>();
    test_is_not_function_pointer<void(int, ...) const noexcept>();
    test_is_not_function_pointer<void(int, ...) const& noexcept>();
    test_is_not_function_pointer<void(int, ...) const&& noexcept>();
    test_is_not_function_pointer<void(int, ...) volatile noexcept>();
    test_is_not_function_pointer<void(int, ...) volatile& noexcept>();
    test_is_not_function_pointer<void(int, ...) volatile&& noexcept>();
    test_is_not_function_pointer<void(int, ...) const volatile noexcept>();
    test_is_not_function_pointer<void(int, ...) const volatile& noexcept>();
    test_is_not_function_pointer<void(int, ...) const volatile&& noexcept>();

    test_is_not_function_pointer<int()>();
    test_is_not_function_pointer<int()&>();
    test_is_not_function_pointer<int() &&>();
    test_is_not_function_pointer<int() const>();
    test_is_not_function_pointer<int() const&>();
    test_is_not_function_pointer<int() const&&>();
    test_is_not_function_pointer<int() volatile>();
    test_is_not_function_pointer<int() volatile&>();
    test_is_not_function_pointer<int() volatile&&>();
    test_is_not_function_pointer<int() const volatile>();
    test_is_not_function_pointer<int() const volatile&>();
    test_is_not_function_pointer<int() const volatile&&>();
    test_is_not_function_pointer<int() noexcept>();
    test_is_not_function_pointer<int()& noexcept>();
    test_is_not_function_pointer<int()&& noexcept>();
    test_is_not_function_pointer<int() const noexcept>();
    test_is_not_function_pointer<int() const& noexcept>();
    test_is_not_function_pointer<int() const&& noexcept>();
    test_is_not_function_pointer<int() volatile noexcept>();
    test_is_not_function_pointer<int() volatile& noexcept>();
    test_is_not_function_pointer<int() volatile&& noexcept>();
    test_is_not_function_pointer<int() const volatile noexcept>();
    test_is_not_function_pointer<int() const volatile& noexcept>();
    test_is_not_function_pointer<int() const volatile&& noexcept>();

    test_is_not_function_pointer<int(int)>();
    test_is_not_function_pointer<int(int)&>();
    test_is_not_function_pointer<int(int) &&>();
    test_is_not_function_pointer<int(int) const>();
    test_is_not_function_pointer<int(int) const&>();
    test_is_not_function_pointer<int(int) const&&>();
    test_is_not_function_pointer<int(int) volatile>();
    test_is_not_function_pointer<int(int) volatile&>();
    test_is_not_function_pointer<int(int) volatile&&>();
    test_is_not_function_pointer<int(int) const volatile>();
    test_is_not_function_pointer<int(int) const volatile&>();
    test_is_not_function_pointer<int(int) const volatile&&>();
    test_is_not_function_pointer<int(int) noexcept>();
    test_is_not_function_pointer<int(int)& noexcept>();
    test_is_not_function_pointer<int(int)&& noexcept>();
    test_is_not_function_pointer<int(int) const noexcept>();
    test_is_not_function_pointer<int(int) const& noexcept>();
    test_is_not_function_pointer<int(int) const&& noexcept>();
    test_is_not_function_pointer<int(int) volatile noexcept>();
    test_is_not_function_pointer<int(int) volatile& noexcept>();
    test_is_not_function_pointer<int(int) volatile&& noexcept>();
    test_is_not_function_pointer<int(int) const volatile noexcept>();
    test_is_not_function_pointer<int(int) const volatile& noexcept>();
    test_is_not_function_pointer<int(int) const volatile&& noexcept>();

    test_is_not_function_pointer<int(...)>();
    test_is_not_function_pointer<int(...)&>();
    test_is_not_function_pointer<int(...) &&>();
    test_is_not_function_pointer<int(...) const>();
    test_is_not_function_pointer<int(...) const&>();
    test_is_not_function_pointer<int(...) const&&>();
    test_is_not_function_pointer<int(...) volatile>();
    test_is_not_function_pointer<int(...) volatile&>();
    test_is_not_function_pointer<int(...) volatile&&>();
    test_is_not_function_pointer<int(...) const volatile>();
    test_is_not_function_pointer<int(...) const volatile&>();
    test_is_not_function_pointer<int(...) const volatile&&>();
    test_is_not_function_pointer<int(...) noexcept>();
    test_is_not_function_pointer<int(...)& noexcept>();
    test_is_not_function_pointer<int(...)&& noexcept>();
    test_is_not_function_pointer<int(...) const noexcept>();
    test_is_not_function_pointer<int(...) const& noexcept>();
    test_is_not_function_pointer<int(...) const&& noexcept>();
    test_is_not_function_pointer<int(...) volatile noexcept>();
    test_is_not_function_pointer<int(...) volatile& noexcept>();
    test_is_not_function_pointer<int(...) volatile&& noexcept>();
    test_is_not_function_pointer<int(...) const volatile noexcept>();
    test_is_not_function_pointer<int(...) const volatile& noexcept>();
    test_is_not_function_pointer<int(...) const volatile&& noexcept>();

    test_is_not_function_pointer<int(int, ...)>();
    test_is_not_function_pointer<int(int, ...)&>();
    test_is_not_function_pointer<int(int, ...) &&>();
    test_is_not_function_pointer<int(int, ...) const>();
    test_is_not_function_pointer<int(int, ...) const&>();
    test_is_not_function_pointer<int(int, ...) const&&>();
    test_is_not_function_pointer<int(int, ...) volatile>();
    test_is_not_function_pointer<int(int, ...) volatile&>();
    test_is_not_function_pointer<int(int, ...) volatile&&>();
    test_is_not_function_pointer<int(int, ...) const volatile>();
    test_is_not_function_pointer<int(int, ...) const volatile&>();
    test_is_not_function_pointer<int(int, ...) const volatile&&>();
    test_is_not_function_pointer<int(int, ...) noexcept>();
    test_is_not_function_pointer<int(int, ...)& noexcept>();
    test_is_not_function_pointer<int(int, ...)&& noexcept>();
    test_is_not_function_pointer<int(int, ...) const noexcept>();
    test_is_not_function_pointer<int(int, ...) const& noexcept>();
    test_is_not_function_pointer<int(int, ...) const&& noexcept>();
    test_is_not_function_pointer<int(int, ...) volatile noexcept>();
    test_is_not_function_pointer<int(int, ...) volatile& noexcept>();
    test_is_not_function_pointer<int(int, ...) volatile&& noexcept>();
    test_is_not_function_pointer<int(int, ...) const volatile noexcept>();
    test_is_not_function_pointer<int(int, ...) const volatile& noexcept>();
    test_is_not_function_pointer<int(int, ...) const volatile&& noexcept>();

    test_is_function_pointer<void (*)()>();
    test_is_function_pointer<void (*)() noexcept>();

    test_is_function_pointer<void (*)(int)>();
    test_is_function_pointer<void (*)(int) noexcept>();

    test_is_function_pointer<void (*)(...)>();
    test_is_function_pointer<void (*)(...) noexcept>();

    test_is_function_pointer<void (*)(int, ...)>();
    test_is_function_pointer<void (*)(int, ...) noexcept>();

    test_is_function_pointer<int (*)()>();
    test_is_function_pointer<int (*)() noexcept>();

    test_is_function_pointer<int (*)(int)>();
    test_is_function_pointer<int (*)(int) noexcept>();

    test_is_function_pointer<int (*)(...)>();
    test_is_function_pointer<int (*)(...) noexcept>();

    test_is_function_pointer<int (*)(int, ...)>();
    test_is_function_pointer<int (*)(int, ...) noexcept>();

    test_is_not_function_pointer<void (&)()>();
    test_is_not_function_pointer<void (&)() noexcept>();

    test_is_not_function_pointer<void (&)(int)>();
    test_is_not_function_pointer<void (&)(int) noexcept>();

    test_is_not_function_pointer<void (&)(...)>();
    test_is_not_function_pointer<void (&)(...) noexcept>();

    test_is_not_function_pointer<void (&)(int, ...)>();
    test_is_not_function_pointer<void (&)(int, ...) noexcept>();

    test_is_not_function_pointer<int (&)()>();
    test_is_not_function_pointer<int (&)() noexcept>();

    test_is_not_function_pointer<int (&)(int)>();
    test_is_not_function_pointer<int (&)(int) noexcept>();

    test_is_not_function_pointer<int (&)(...)>();
    test_is_not_function_pointer<int (&)(...) noexcept>();

    test_is_not_function_pointer<int (&)(int, ...)>();
    test_is_not_function_pointer<int (&)(int, ...) noexcept>();

    test_is_not_function_pointer<void(&&)()>();
    test_is_not_function_pointer<void(&&)() noexcept>();

    test_is_not_function_pointer<void(&&)(int)>();
    test_is_not_function_pointer<void(&&)(int) noexcept>();

    test_is_not_function_pointer<void(&&)(...)>();
    test_is_not_function_pointer<void(&&)(...) noexcept>();

    test_is_not_function_pointer<void(&&)(int, ...)>();
    test_is_not_function_pointer<void(&&)(int, ...) noexcept>();

    test_is_not_function_pointer<int(&&)()>();
    test_is_not_function_pointer<int(&&)() noexcept>();

    test_is_not_function_pointer<int(&&)(int)>();
    test_is_not_function_pointer<int(&&)(int) noexcept>();

    test_is_not_function_pointer<int(&&)(...)>();
    test_is_not_function_pointer<int(&&)(...) noexcept>();

    test_is_not_function_pointer<int(&&)(int, ...)>();
    test_is_not_function_pointer<int(&&)(int, ...) noexcept>();

    test_is_not_function_pointer<void (Class::*)()>();
    test_is_not_function_pointer<void (Class::*)()&>();
    test_is_not_function_pointer<void (Class::*)() &&>();
    test_is_not_function_pointer<void (Class::*)() const>();
    test_is_not_function_pointer<void (Class::*)() const&>();
    test_is_not_function_pointer<void (Class::*)() const&&>();
    test_is_not_function_pointer<void (Class::*)() noexcept>();
    test_is_not_function_pointer<void (Class::*)()& noexcept>();
    test_is_not_function_pointer<void (Class::*)()&& noexcept>();
    test_is_not_function_pointer<void (Class::*)() const noexcept>();
    test_is_not_function_pointer<void (Class::*)() const& noexcept>();
    test_is_not_function_pointer<void (Class::*)() const&& noexcept>();

    test_is_not_function_pointer<void (Class::*)(int)>();
    test_is_not_function_pointer<void (Class::*)(int)&>();
    test_is_not_function_pointer<void (Class::*)(int) &&>();
    test_is_not_function_pointer<void (Class::*)(int) const>();
    test_is_not_function_pointer<void (Class::*)(int) const&>();
    test_is_not_function_pointer<void (Class::*)(int) const&&>();
    test_is_not_function_pointer<void (Class::*)(int) noexcept>();
    test_is_not_function_pointer<void (Class::*)(int)& noexcept>();
    test_is_not_function_pointer<void (Class::*)(int)&& noexcept>();
    test_is_not_function_pointer<void (Class::*)(int) const noexcept>();
    test_is_not_function_pointer<void (Class::*)(int) const& noexcept>();
    test_is_not_function_pointer<void (Class::*)(int) const&& noexcept>();

    test_is_not_function_pointer<void (Class::*)(...)>();
    test_is_not_function_pointer<void (Class::*)(...)&>();
    test_is_not_function_pointer<void (Class::*)(...) &&>();
    test_is_not_function_pointer<void (Class::*)(...) const>();
    test_is_not_function_pointer<void (Class::*)(...) const&>();
    test_is_not_function_pointer<void (Class::*)(...) const&&>();
    test_is_not_function_pointer<void (Class::*)(...) noexcept>();
    test_is_not_function_pointer<void (Class::*)(...)& noexcept>();
    test_is_not_function_pointer<void (Class::*)(...)&& noexcept>();
    test_is_not_function_pointer<void (Class::*)(...) const noexcept>();
    test_is_not_function_pointer<void (Class::*)(...) const& noexcept>();
    test_is_not_function_pointer<void (Class::*)(...) const&& noexcept>();

    test_is_not_function_pointer<void (Class::*)(int, ...)>();
    test_is_not_function_pointer<void (Class::*)(int, ...)&>();
    test_is_not_function_pointer<void (Class::*)(int, ...) &&>();
    test_is_not_function_pointer<void (Class::*)(int, ...) const>();
    test_is_not_function_pointer<void (Class::*)(int, ...) const&>();
    test_is_not_function_pointer<void (Class::*)(int, ...) const&&>();
    test_is_not_function_pointer<void (Class::*)(int, ...) noexcept>();
    test_is_not_function_pointer<void (Class::*)(int, ...)& noexcept>();
    test_is_not_function_pointer<void (Class::*)(int, ...)&& noexcept>();
    test_is_not_function_pointer<void (Class::*)(int, ...) const noexcept>();
    test_is_not_function_pointer<void (Class::*)(int, ...) const& noexcept>();
    test_is_not_function_pointer<void (Class::*)(int, ...) const&& noexcept>();

    test_is_not_function_pointer<int (Class::*)()>();
    test_is_not_function_pointer<int (Class::*)()&>();
    test_is_not_function_pointer<int (Class::*)() &&>();
    test_is_not_function_pointer<int (Class::*)() const>();
    test_is_not_function_pointer<int (Class::*)() const&>();
    test_is_not_function_pointer<int (Class::*)() const&&>();
    test_is_not_function_pointer<int (Class::*)() noexcept>();
    test_is_not_function_pointer<int (Class::*)()& noexcept>();
    test_is_not_function_pointer<int (Class::*)()&& noexcept>();
    test_is_not_function_pointer<int (Class::*)() const noexcept>();
    test_is_not_function_pointer<int (Class::*)() const& noexcept>();
    test_is_not_function_pointer<int (Class::*)() const&& noexcept>();

    test_is_not_function_pointer<int (Class::*)(int)>();
    test_is_not_function_pointer<int (Class::*)(int)&>();
    test_is_not_function_pointer<int (Class::*)(int) &&>();
    test_is_not_function_pointer<int (Class::*)(int) const>();
    test_is_not_function_pointer<int (Class::*)(int) const&>();
    test_is_not_function_pointer<int (Class::*)(int) const&&>();
    test_is_not_function_pointer<int (Class::*)(int) noexcept>();
    test_is_not_function_pointer<int (Class::*)(int)& noexcept>();
    test_is_not_function_pointer<int (Class::*)(int)&& noexcept>();
    test_is_not_function_pointer<int (Class::*)(int) const noexcept>();
    test_is_not_function_pointer<int (Class::*)(int) const& noexcept>();
    test_is_not_function_pointer<int (Class::*)(int) const&& noexcept>();

    test_is_not_function_pointer<int (Class::*)(...)>();
    test_is_not_function_pointer<int (Class::*)(...)&>();
    test_is_not_function_pointer<int (Class::*)(...) &&>();
    test_is_not_function_pointer<int (Class::*)(...) const>();
    test_is_not_function_pointer<int (Class::*)(...) const&>();
    test_is_not_function_pointer<int (Class::*)(...) const&&>();
    test_is_not_function_pointer<int (Class::*)(...) noexcept>();
    test_is_not_function_pointer<int (Class::*)(...)& noexcept>();
    test_is_not_function_pointer<int (Class::*)(...)&& noexcept>();
    test_is_not_function_pointer<int (Class::*)(...) const noexcept>();
    test_is_not_function_pointer<int (Class::*)(...) const& noexcept>();
    test_is_not_function_pointer<int (Class::*)(...) const&& noexcept>();

    test_is_not_function_pointer<int (Class::*)(int, ...)>();
    test_is_not_function_pointer<int (Class::*)(int, ...)&>();
    test_is_not_function_pointer<int (Class::*)(int, ...) &&>();
    test_is_not_function_pointer<int (Class::*)(int, ...) const>();
    test_is_not_function_pointer<int (Class::*)(int, ...) const&>();
    test_is_not_function_pointer<int (Class::*)(int, ...) const&&>();
    test_is_not_function_pointer<int (Class::*)(int, ...) noexcept>();
    test_is_not_function_pointer<int (Class::*)(int, ...)& noexcept>();
    test_is_not_function_pointer<int (Class::*)(int, ...)&& noexcept>();
    test_is_not_function_pointer<int (Class::*)(int, ...) const noexcept>();
    test_is_not_function_pointer<int (Class::*)(int, ...) const& noexcept>();
    test_is_not_function_pointer<int (Class::*)(int, ...) const&& noexcept>();
}
