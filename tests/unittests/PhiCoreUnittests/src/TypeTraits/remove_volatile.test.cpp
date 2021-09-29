#include <catch2/catch.hpp>

#include "SameType.hpp"
#include "TestTypes.hpp"
#include <Phi/CompilerSupport/Char8_t.hpp>
#include <Phi/Core/Boolean.hpp>
#include <Phi/Core/FloatingPoint.hpp>
#include <Phi/Core/Integer.hpp>
#include <Phi/Core/Nullptr.hpp>
#include <Phi/Core/ScopePtr.hpp>
#include <Phi/TypeTraits/remove_volatile.hpp>
#include <vector>

template <typename T, typename U>
void test_remove_volatile()
{
    CHECK_SAME_TYPE(typename phi::remove_volatile<T>::type, U);
    CHECK_SAME_TYPE(typename phi::remove_volatile<const T>::type, const U);
    CHECK_SAME_TYPE(typename phi::remove_volatile<volatile T>::type, U);
    CHECK_SAME_TYPE(typename phi::remove_volatile<const volatile T>::type, const U);

    CHECK_SAME_TYPE(phi::remove_volatile_t<T>, U);
    CHECK_SAME_TYPE(phi::remove_volatile_t<const T>, const U);
    CHECK_SAME_TYPE(phi::remove_volatile_t<volatile T>, U);
    CHECK_SAME_TYPE(phi::remove_volatile_t<const volatile T>, const U);
}

TEST_CASE("remove_volatile")
{
    test_remove_volatile<void, void>();
    test_remove_volatile<phi::nullptr_t, phi::nullptr_t>();
    test_remove_volatile<bool, bool>();
    test_remove_volatile<char, char>();
    test_remove_volatile<signed char, signed char>();
    test_remove_volatile<unsigned char, unsigned char>();
    test_remove_volatile<short, short>();
    test_remove_volatile<unsigned short, unsigned short>();
    test_remove_volatile<int, int>();
    test_remove_volatile<unsigned int, unsigned int>();
    test_remove_volatile<long, long>();
    test_remove_volatile<unsigned long, unsigned long>();
    test_remove_volatile<long long, long long>();
    test_remove_volatile<unsigned long long, unsigned long long>();
    test_remove_volatile<float, float>();
    test_remove_volatile<double, double>();
    test_remove_volatile<long double, long double>();
    test_remove_volatile<char8_t, char8_t>();
    test_remove_volatile<char16_t, char16_t>();
    test_remove_volatile<char32_t, char32_t>();
    test_remove_volatile<wchar_t, wchar_t>();

    test_remove_volatile<phi::Boolean, phi::Boolean>();
    test_remove_volatile<phi::Integer<signed char>, phi::Integer<signed char>>();
    test_remove_volatile<phi::Integer<unsigned char>, phi::Integer<unsigned char>>();
    test_remove_volatile<phi::Integer<short>, phi::Integer<short>>();
    test_remove_volatile<phi::Integer<unsigned short>, phi::Integer<unsigned short>>();
    test_remove_volatile<phi::Integer<int>, phi::Integer<int>>();
    test_remove_volatile<phi::Integer<unsigned int>, phi::Integer<unsigned int>>();
    test_remove_volatile<phi::Integer<long>, phi::Integer<long>>();
    test_remove_volatile<phi::Integer<unsigned long>, phi::Integer<unsigned long>>();
    test_remove_volatile<phi::Integer<long long>, phi::Integer<long long>>();
    test_remove_volatile<phi::Integer<unsigned long long>, phi::Integer<unsigned long long>>();
    test_remove_volatile<phi::FloatingPoint<float>, phi::FloatingPoint<float>>();
    test_remove_volatile<phi::FloatingPoint<double>, phi::FloatingPoint<double>>();
    test_remove_volatile<phi::FloatingPoint<long double>, phi::FloatingPoint<long double>>();

    test_remove_volatile<std::vector<int>, std::vector<int>>();
    test_remove_volatile<phi::ScopePtr<int>, phi::ScopePtr<int>>();

    test_remove_volatile<int&, int&>();
    test_remove_volatile<const int&, const int&>();
    test_remove_volatile<volatile int&, volatile int&>();
    test_remove_volatile<const volatile int&, const volatile int&>();
    test_remove_volatile<int&&, int&&>();
    test_remove_volatile<const int&&, const int&&>();
    test_remove_volatile<volatile int&&, volatile int&&>();
    test_remove_volatile<const volatile int&&, const volatile int&&>();
    test_remove_volatile<int*, int*>();
    test_remove_volatile<const int*, const int*>();
    test_remove_volatile<volatile int*, volatile int*>();
    test_remove_volatile<const volatile int*, const volatile int*>();
    test_remove_volatile<int**, int**>();
    test_remove_volatile<const int**, const int**>();
    test_remove_volatile<volatile int**, volatile int**>();
    test_remove_volatile<const volatile int**, const volatile int**>();
    test_remove_volatile<void*, void*>();
    test_remove_volatile<char[3], char[3]>();
    test_remove_volatile<char[], char[]>();
    test_remove_volatile<char* [3], char* [3]>();
    test_remove_volatile<char*[], char*[]>();
    test_remove_volatile<Class, Class>();
    test_remove_volatile<Struct, Struct>();
    test_remove_volatile<Union, Union>();
    test_remove_volatile<NonEmptyUnion, NonEmptyUnion>();
    test_remove_volatile<Empty, Empty>();
    test_remove_volatile<NotEmpty, NotEmpty>();
    test_remove_volatile<bit_zero, bit_zero>();
    test_remove_volatile<bit_one, bit_one>();
    test_remove_volatile<Abstract, Abstract>();
    test_remove_volatile<AbstractTemplate<int>, AbstractTemplate<int>>();
    test_remove_volatile<AbstractTemplate<double>, AbstractTemplate<double>>();
    test_remove_volatile<AbstractTemplate<Class>, AbstractTemplate<Class>>();
    test_remove_volatile<AbstractTemplate<incomplete_type>, AbstractTemplate<incomplete_type>>();
    test_remove_volatile<Final, Final>();
    test_remove_volatile<Enum, Enum>();
    test_remove_volatile<EnumSigned, EnumSigned>();
    test_remove_volatile<EnumUnsigned, EnumUnsigned>();
    test_remove_volatile<EnumClass, EnumClass>();
    test_remove_volatile<Function, Function>();
    test_remove_volatile<FunctionPtr, FunctionPtr>();
    test_remove_volatile<MemberObjectPtr, MemberObjectPtr>();
    test_remove_volatile<MemberFunctionPtr, MemberFunctionPtr>();
    test_remove_volatile<incomplete_type, incomplete_type>();
    test_remove_volatile<int Class::*, int Class::*>();
    test_remove_volatile<float Class::*, float Class::*>();

    test_remove_volatile<void(), void()>();
    test_remove_volatile<void() noexcept, void() noexcept>();
    test_remove_volatile<void(int), void(int)>();
    test_remove_volatile<void(int) noexcept, void(int) noexcept>();

    test_remove_volatile<void(...), void(...)>();
    test_remove_volatile<void(...) noexcept, void(...) noexcept>();
    test_remove_volatile<void(int, ...), void(int, ...)>();
    test_remove_volatile<void(int, ...) noexcept, void(int, ...) noexcept>();

    test_remove_volatile<void (*)(), void (*)()>();
    test_remove_volatile<void (*)() noexcept, void (*)() noexcept>();
    test_remove_volatile<void (*)(int), void (*)(int)>();
    test_remove_volatile<void (*)(int) noexcept, void (*)(int) noexcept>();

    test_remove_volatile<void (*)(...), void (*)(...)>();
    test_remove_volatile<void (*)(...) noexcept, void (*)(...) noexcept>();
    test_remove_volatile<void (*)(int, ...), void (*)(int, ...)>();
    test_remove_volatile<void (*)(int, ...) noexcept, void (*)(int, ...) noexcept>();

    test_remove_volatile<void (Class::*)(), void (Class::*)()>();
    test_remove_volatile<void (Class::*)()&, void (Class::*)()&>();
    test_remove_volatile<void (Class::*)()&&, void (Class::*)() &&>();
    test_remove_volatile<void (Class::*)() const, void (Class::*)() const>();
    test_remove_volatile<void (Class::*)() const&, void (Class::*)() const&>();
    test_remove_volatile<void (Class::*)() const&&, void (Class::*)() const&&>();

    test_remove_volatile<void (Class::*)() noexcept, void (Class::*)() noexcept>();
    test_remove_volatile<void (Class::*)()& noexcept, void (Class::*)()& noexcept>();
    test_remove_volatile<void (Class::*)()&& noexcept, void (Class::*)()&& noexcept>();
    test_remove_volatile<void (Class::*)() const noexcept, void (Class::*)() const noexcept>();
    test_remove_volatile<void (Class::*)() const& noexcept, void (Class::*)() const& noexcept>();
    test_remove_volatile<void (Class::*)() const&& noexcept, void (Class::*)() const&& noexcept>();

    test_remove_volatile<void (Class::*)(int), void (Class::*)(int)>();
    test_remove_volatile<void (Class::*)(int)&, void (Class::*)(int)&>();
    test_remove_volatile<void (Class::*)(int)&&, void (Class::*)(int) &&>();
    test_remove_volatile<void (Class::*)(int) const, void (Class::*)(int) const>();
    test_remove_volatile<void (Class::*)(int) const&, void (Class::*)(int) const&>();
    test_remove_volatile<void (Class::*)(int) const&&, void (Class::*)(int) const&&>();

    test_remove_volatile<void (Class::*)(int) noexcept, void (Class::*)(int) noexcept>();
    test_remove_volatile<void (Class::*)(int)& noexcept, void (Class::*)(int)& noexcept>();
    test_remove_volatile<void (Class::*)(int)&& noexcept, void (Class::*)(int)&& noexcept>();
    test_remove_volatile<void (Class::*)(int) const noexcept,
                         void (Class::*)(int) const noexcept>();
    test_remove_volatile<void (Class::*)(int) const& noexcept,
                         void (Class::*)(int) const& noexcept>();
    test_remove_volatile<void (Class::*)(int) const&& noexcept,
                         void (Class::*)(int) const&& noexcept>();

    test_remove_volatile<void (Class::*)(...), void (Class::*)(...)>();
    test_remove_volatile<void (Class::*)(...)&, void (Class::*)(...)&>();
    test_remove_volatile<void (Class::*)(...)&&, void (Class::*)(...) &&>();
    test_remove_volatile<void (Class::*)(...) const, void (Class::*)(...) const>();
    test_remove_volatile<void (Class::*)(...) const&, void (Class::*)(...) const&>();
    test_remove_volatile<void (Class::*)(...) const&&, void (Class::*)(...) const&&>();

    test_remove_volatile<void (Class::*)(...) noexcept, void (Class::*)(...) noexcept>();
    test_remove_volatile<void (Class::*)(...)& noexcept, void (Class::*)(...)& noexcept>();
    test_remove_volatile<void (Class::*)(...)&& noexcept, void (Class::*)(...)&& noexcept>();
    test_remove_volatile<void (Class::*)(...) const noexcept,
                         void (Class::*)(...) const noexcept>();
    test_remove_volatile<void (Class::*)(...) const& noexcept,
                         void (Class::*)(...) const& noexcept>();
    test_remove_volatile<void (Class::*)(...) const&& noexcept,
                         void (Class::*)(...) const&& noexcept>();
}
