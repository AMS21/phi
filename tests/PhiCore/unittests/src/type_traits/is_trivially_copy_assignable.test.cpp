#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_trivially_copy_assignable.hpp>
#include <vector>

template <typename T>
void test_is_trivially_copy_assignable()
{
#if PHI_SUPPORTS_IS_TRIVIALLY_ASSIGNABLE()
    STATIC_REQUIRE(phi::is_trivially_copy_assignable<T>::value);
#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_trivially_copy_assignable_v<T>);
#    endif
#endif
}

template <typename T>
void test_is_not_trivially_copy_assignable()
{
#if PHI_SUPPORTS_IS_TRIVIALLY_ASSIGNABLE()
    STATIC_REQUIRE_FALSE(phi::is_trivially_copy_assignable<T>::value);
#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_trivially_copy_assignable_v<T>);
#    endif
#endif
}

struct A
{
    A& operator=(const A&);
};

struct B
{
    B& operator=(const B&) = default;
};

TEST_CASE("is_trivially_copy_assignable")
{
    test_is_not_trivially_copy_assignable<A>();
    test_is_not_trivially_copy_assignable<const A>();
    test_is_not_trivially_copy_assignable<volatile A>();
    test_is_not_trivially_copy_assignable<const volatile A>();

    test_is_trivially_copy_assignable<B>();
    test_is_not_trivially_copy_assignable<const B>();
    test_is_not_trivially_copy_assignable<volatile B>();
    test_is_not_trivially_copy_assignable<const volatile B>();

    test_is_not_trivially_copy_assignable<void>();
    test_is_trivially_copy_assignable<phi::nullptr_t>();
    test_is_trivially_copy_assignable<bool>();
    test_is_trivially_copy_assignable<char>();
    test_is_trivially_copy_assignable<signed char>();
    test_is_trivially_copy_assignable<unsigned char>();
    test_is_trivially_copy_assignable<short>();
    test_is_trivially_copy_assignable<unsigned short>();
    test_is_trivially_copy_assignable<int>();
    test_is_trivially_copy_assignable<unsigned int>();
    test_is_trivially_copy_assignable<long>();
    test_is_trivially_copy_assignable<unsigned long>();
    test_is_trivially_copy_assignable<long long>();
    test_is_trivially_copy_assignable<unsigned long long>();
    test_is_trivially_copy_assignable<float>();
    test_is_trivially_copy_assignable<double>();
    test_is_trivially_copy_assignable<long double>();
    test_is_trivially_copy_assignable<char8_t>();
    test_is_trivially_copy_assignable<char16_t>();
    test_is_trivially_copy_assignable<char32_t>();
    test_is_trivially_copy_assignable<wchar_t>();

    test_is_trivially_copy_assignable<phi::boolean>();
    test_is_trivially_copy_assignable<phi::integer<signed char>>();
    test_is_trivially_copy_assignable<phi::integer<unsigned char>>();
    test_is_trivially_copy_assignable<phi::integer<short>>();
    test_is_trivially_copy_assignable<phi::integer<unsigned short>>();
    test_is_trivially_copy_assignable<phi::integer<int>>();
    test_is_trivially_copy_assignable<phi::integer<unsigned int>>();
    test_is_trivially_copy_assignable<phi::integer<long>>();
    test_is_trivially_copy_assignable<phi::integer<unsigned long>>();
    test_is_trivially_copy_assignable<phi::integer<long long>>();
    test_is_trivially_copy_assignable<phi::integer<unsigned long long>>();
    test_is_trivially_copy_assignable<phi::floating_point<float>>();
    test_is_trivially_copy_assignable<phi::floating_point<double>>();
    test_is_trivially_copy_assignable<phi::floating_point<long double>>();

    test_is_not_trivially_copy_assignable<std::vector<int>>();
    test_is_not_trivially_copy_assignable<phi::scope_ptr<int>>();

    test_is_trivially_copy_assignable<int&>();
    test_is_not_trivially_copy_assignable<const int&>();
    test_is_trivially_copy_assignable<volatile int&>();
    test_is_not_trivially_copy_assignable<const volatile int&>();
    test_is_trivially_copy_assignable<int&&>();
    test_is_not_trivially_copy_assignable<const int&&>();
    test_is_trivially_copy_assignable<volatile int&&>();
    test_is_not_trivially_copy_assignable<const volatile int&&>();
    test_is_trivially_copy_assignable<int*>();
    test_is_trivially_copy_assignable<const int*>();
    test_is_trivially_copy_assignable<volatile int*>();
    test_is_trivially_copy_assignable<const volatile int*>();
    test_is_trivially_copy_assignable<int**>();
    test_is_trivially_copy_assignable<const int**>();
    test_is_trivially_copy_assignable<volatile int**>();
    test_is_trivially_copy_assignable<const volatile int**>();
    test_is_trivially_copy_assignable<void*>();
    test_is_not_trivially_copy_assignable<char[3]>();
    test_is_not_trivially_copy_assignable<char[]>();
    test_is_not_trivially_copy_assignable<char* [3]>();
    test_is_not_trivially_copy_assignable<char*[]>();
    test_is_trivially_copy_assignable<Class>();
    test_is_not_trivially_copy_assignable<const Class>();
    test_is_not_trivially_copy_assignable<volatile Class>();
    test_is_not_trivially_copy_assignable<const volatile Class>();
    test_is_trivially_copy_assignable<Union>();
    test_is_trivially_copy_assignable<NonEmptyUnion>();
    test_is_trivially_copy_assignable<Empty>();
    test_is_not_trivially_copy_assignable<NotEmpty>();
    test_is_trivially_copy_assignable<bit_zero>();
    test_is_trivially_copy_assignable<bit_one>();
    test_is_not_trivially_copy_assignable<Abstract>();
    test_is_not_trivially_copy_assignable<AbstractTemplate<int>>();
    test_is_trivially_copy_assignable<AbstractTemplate<double>>();
    test_is_not_trivially_copy_assignable<AbstractTemplate<Class>>();
    test_is_trivially_copy_assignable<Final>();
    test_is_trivially_copy_assignable<Enum>();
    test_is_trivially_copy_assignable<EnumSigned>();
    test_is_trivially_copy_assignable<EnumUnsigned>();
    test_is_trivially_copy_assignable<EnumClass>();
    test_is_not_trivially_copy_assignable<Function>();
    test_is_trivially_copy_assignable<FunctionPtr>();
    test_is_trivially_copy_assignable<MemberObjectPtr>();
    test_is_trivially_copy_assignable<MemberFunctionPtr>();
    test_is_trivially_copy_assignable<int Class::*>();
    test_is_trivially_copy_assignable<float Class::*>();

    test_is_not_trivially_copy_assignable<void()>();
    test_is_not_trivially_copy_assignable<void() noexcept>();
    test_is_not_trivially_copy_assignable<void(int)>();
    test_is_not_trivially_copy_assignable<void(int) noexcept>();

    test_is_not_trivially_copy_assignable<void(...)>();
    test_is_not_trivially_copy_assignable<void(...) noexcept>();
    test_is_not_trivially_copy_assignable<void(int, ...)>();
    test_is_not_trivially_copy_assignable<void(int, ...) noexcept>();

    test_is_trivially_copy_assignable<void (*)()>();
    test_is_trivially_copy_assignable<void (*)() noexcept>();
    test_is_trivially_copy_assignable<void (*)(int)>();
    test_is_trivially_copy_assignable<void (*)(int) noexcept>();

    test_is_trivially_copy_assignable<void (*)(...)>();
    test_is_trivially_copy_assignable<void (*)(...) noexcept>();
    test_is_trivially_copy_assignable<void (*)(int, ...)>();
    test_is_trivially_copy_assignable<void (*)(int, ...) noexcept>();

    test_is_trivially_copy_assignable<void (Class::*)()>();
    test_is_trivially_copy_assignable<void (Class::*)()&>();
    test_is_trivially_copy_assignable<void (Class::*)() &&>();
    test_is_trivially_copy_assignable<void (Class::*)() const>();
    test_is_trivially_copy_assignable<void (Class::*)() const&>();
    test_is_trivially_copy_assignable<void (Class::*)() const&&>();

    test_is_trivially_copy_assignable<void (Class::*)() noexcept>();
    test_is_trivially_copy_assignable<void (Class::*)()& noexcept>();
    test_is_trivially_copy_assignable<void (Class::*)()&& noexcept>();
    test_is_trivially_copy_assignable<void (Class::*)() const noexcept>();
    test_is_trivially_copy_assignable<void (Class::*)() const& noexcept>();
    test_is_trivially_copy_assignable<void (Class::*)() const&& noexcept>();

    test_is_trivially_copy_assignable<void (Class::*)(int)>();
    test_is_trivially_copy_assignable<void (Class::*)(int)&>();
    test_is_trivially_copy_assignable<void (Class::*)(int) &&>();
    test_is_trivially_copy_assignable<void (Class::*)(int) const>();
    test_is_trivially_copy_assignable<void (Class::*)(int) const&>();
    test_is_trivially_copy_assignable<void (Class::*)(int) const&&>();

    test_is_trivially_copy_assignable<void (Class::*)(int) noexcept>();
    test_is_trivially_copy_assignable<void (Class::*)(int)& noexcept>();
    test_is_trivially_copy_assignable<void (Class::*)(int)&& noexcept>();
    test_is_trivially_copy_assignable<void (Class::*)(int) const noexcept>();
    test_is_trivially_copy_assignable<void (Class::*)(int) const& noexcept>();
    test_is_trivially_copy_assignable<void (Class::*)(int) const&& noexcept>();

    test_is_trivially_copy_assignable<void (Class::*)(...)>();
    test_is_trivially_copy_assignable<void (Class::*)(...)&>();
    test_is_trivially_copy_assignable<void (Class::*)(...) &&>();
    test_is_trivially_copy_assignable<void (Class::*)(...) const>();
    test_is_trivially_copy_assignable<void (Class::*)(...) const&>();
    test_is_trivially_copy_assignable<void (Class::*)(...) const&&>();

    test_is_trivially_copy_assignable<void (Class::*)(...) noexcept>();
    test_is_trivially_copy_assignable<void (Class::*)(...)& noexcept>();
    test_is_trivially_copy_assignable<void (Class::*)(...)&& noexcept>();
    test_is_trivially_copy_assignable<void (Class::*)(...) const noexcept>();
    test_is_trivially_copy_assignable<void (Class::*)(...) const& noexcept>();
    test_is_trivially_copy_assignable<void (Class::*)(...) const&& noexcept>();
}