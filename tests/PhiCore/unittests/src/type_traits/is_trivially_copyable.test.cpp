#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/floating_point.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/type_traits/is_trivially_copyable.hpp>
#include <vector>

template <typename T>
void test_is_trivially_copyable()
{
#if PHI_SUPPORTS_IS_TRIVIALLY_COPYABLE()
    STATIC_REQUIRE(phi::is_trivially_copyable<T>::value);
    STATIC_REQUIRE(phi::is_trivially_copyable<const T>::value);
    STATIC_REQUIRE(phi::is_trivially_copyable<volatile T>::value);
    STATIC_REQUIRE(phi::is_trivially_copyable<const volatile T>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_trivially_copyable_v<T>);
    STATIC_REQUIRE(phi::is_trivially_copyable_v<const T>);
    STATIC_REQUIRE(phi::is_trivially_copyable_v<volatile T>);
    STATIC_REQUIRE(phi::is_trivially_copyable_v<const volatile T>);
#    endif
#endif
}

template <typename T>
void test_is_not_trivially_copyable()
{
#if PHI_SUPPORTS_IS_TRIVIALLY_COPYABLE()
    STATIC_REQUIRE_FALSE(phi::is_trivially_copyable<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_trivially_copyable<const T>::value);
    STATIC_REQUIRE_FALSE(phi::is_trivially_copyable<volatile T>::value);
    STATIC_REQUIRE_FALSE(phi::is_trivially_copyable<const volatile T>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_trivially_copyable_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_trivially_copyable_v<const T>);
    STATIC_REQUIRE_FALSE(phi::is_trivially_copyable_v<volatile T>);
    STATIC_REQUIRE_FALSE(phi::is_trivially_copyable_v<const volatile T>);
#    endif
#endif
}

struct A
{
    int i;
};

struct B
{
    int i;

    ~B()
    {
        i = 3;
    }
};

class C
{
public:
    C();
};

struct S
{
    S(S const&) = default;
    S(S&&)      = default;
    S& operator=(S const&) = delete;
    S& operator=(S&&) = delete;
};

TEST_CASE("is_trivially_copyable")
{
    test_is_trivially_copyable<A>();
    test_is_not_trivially_copyable<A&>();
    test_is_not_trivially_copyable<const A&>();
    test_is_not_trivially_copyable<B>();
    test_is_not_trivially_copyable<B&>();
    test_is_not_trivially_copyable<const B&>();
    test_is_trivially_copyable<C>();
    test_is_not_trivially_copyable<C&>();
    test_is_not_trivially_copyable<const C&>();

    test_is_trivially_copyable<S>();

    test_is_not_trivially_copyable<void>();
    test_is_trivially_copyable<phi::nullptr_t>();
    test_is_trivially_copyable<bool>();
    test_is_trivially_copyable<char>();
    test_is_trivially_copyable<signed char>();
    test_is_trivially_copyable<unsigned char>();
    test_is_trivially_copyable<short>();
    test_is_trivially_copyable<unsigned short>();
    test_is_trivially_copyable<int>();
    test_is_trivially_copyable<unsigned int>();
    test_is_trivially_copyable<long>();
    test_is_trivially_copyable<unsigned long>();
    test_is_trivially_copyable<long long>();
    test_is_trivially_copyable<unsigned long long>();
    test_is_trivially_copyable<float>();
    test_is_trivially_copyable<double>();
    test_is_trivially_copyable<long double>();
    test_is_trivially_copyable<char8_t>();
    test_is_trivially_copyable<char16_t>();
    test_is_trivially_copyable<char32_t>();
    test_is_trivially_copyable<wchar_t>();

    test_is_trivially_copyable<phi::boolean>();
    test_is_trivially_copyable<phi::integer<signed char>>();
    test_is_trivially_copyable<phi::integer<unsigned char>>();
    test_is_trivially_copyable<phi::integer<short>>();
    test_is_trivially_copyable<phi::integer<unsigned short>>();
    test_is_trivially_copyable<phi::integer<int>>();
    test_is_trivially_copyable<phi::integer<unsigned int>>();
    test_is_trivially_copyable<phi::integer<long>>();
    test_is_trivially_copyable<phi::integer<unsigned long>>();
    test_is_trivially_copyable<phi::integer<long long>>();
    test_is_trivially_copyable<phi::integer<unsigned long long>>();
    test_is_trivially_copyable<phi::floating_point<float>>();
    test_is_trivially_copyable<phi::floating_point<double>>();
    test_is_trivially_copyable<phi::floating_point<long double>>();

    test_is_not_trivially_copyable<std::vector<int>>();
    test_is_not_trivially_copyable<phi::scope_ptr<int>>();

    test_is_not_trivially_copyable<int&>();
    test_is_not_trivially_copyable<const int&>();
    test_is_not_trivially_copyable<volatile int&>();
    test_is_not_trivially_copyable<const volatile int&>();
    test_is_not_trivially_copyable<int&&>();
    test_is_not_trivially_copyable<const int&&>();
    test_is_not_trivially_copyable<volatile int&&>();
    test_is_not_trivially_copyable<const volatile int&&>();
    test_is_trivially_copyable<int*>();
    test_is_trivially_copyable<const int*>();
    test_is_trivially_copyable<volatile int*>();
    test_is_trivially_copyable<const volatile int*>();
    test_is_trivially_copyable<int**>();
    test_is_trivially_copyable<const int**>();
    test_is_trivially_copyable<volatile int**>();
    test_is_trivially_copyable<const volatile int**>();
    test_is_trivially_copyable<void*>();
    test_is_trivially_copyable<char[3]>();
    test_is_trivially_copyable<char[]>();
    test_is_trivially_copyable<char* [3]>();
    test_is_trivially_copyable<char*[]>();
    test_is_not_trivially_copyable<Class>();
    test_is_trivially_copyable<Union>();
    test_is_trivially_copyable<NonEmptyUnion>();
    test_is_trivially_copyable<Empty>();
    test_is_not_trivially_copyable<NotEmpty>();
    test_is_trivially_copyable<bit_zero>();
    test_is_trivially_copyable<bit_one>();
    test_is_not_trivially_copyable<Abstract>();
    test_is_not_trivially_copyable<AbstractTemplate<int>>();
    test_is_trivially_copyable<AbstractTemplate<double>>();
    test_is_not_trivially_copyable<AbstractTemplate<Class>>();
    test_is_not_trivially_copyable<AbstractTemplate<incomplete_type>>();
    test_is_trivially_copyable<Final>();
    test_is_trivially_copyable<Enum>();
    test_is_trivially_copyable<EnumSigned>();
    test_is_trivially_copyable<EnumUnsigned>();
    test_is_trivially_copyable<EnumClass>();
    test_is_not_trivially_copyable<Function>();
    test_is_trivially_copyable<FunctionPtr>();
    test_is_trivially_copyable<MemberObjectPtr>();
    test_is_trivially_copyable<MemberFunctionPtr>();
    test_is_trivially_copyable<int Class::*>();
    test_is_trivially_copyable<float Class::*>();

    test_is_not_trivially_copyable<void()>();
    test_is_not_trivially_copyable<void() noexcept>();
    test_is_not_trivially_copyable<void(int)>();
    test_is_not_trivially_copyable<void(int) noexcept>();

    test_is_not_trivially_copyable<void(...)>();
    test_is_not_trivially_copyable<void(...) noexcept>();
    test_is_not_trivially_copyable<void(int, ...)>();
    test_is_not_trivially_copyable<void(int, ...) noexcept>();

    test_is_trivially_copyable<void (*)()>();
    test_is_trivially_copyable<void (*)() noexcept>();
    test_is_trivially_copyable<void (*)(int)>();
    test_is_trivially_copyable<void (*)(int) noexcept>();

    test_is_trivially_copyable<void (*)(...)>();
    test_is_trivially_copyable<void (*)(...) noexcept>();
    test_is_trivially_copyable<void (*)(int, ...)>();
    test_is_trivially_copyable<void (*)(int, ...) noexcept>();

    test_is_trivially_copyable<void (Class::*)()>();
    test_is_trivially_copyable<void (Class::*)()&>();
    test_is_trivially_copyable<void (Class::*)() &&>();
    test_is_trivially_copyable<void (Class::*)() const>();
    test_is_trivially_copyable<void (Class::*)() const&>();
    test_is_trivially_copyable<void (Class::*)() const&&>();

    test_is_trivially_copyable<void (Class::*)() noexcept>();
    test_is_trivially_copyable<void (Class::*)()& noexcept>();
    test_is_trivially_copyable<void (Class::*)()&& noexcept>();
    test_is_trivially_copyable<void (Class::*)() const noexcept>();
    test_is_trivially_copyable<void (Class::*)() const& noexcept>();
    test_is_trivially_copyable<void (Class::*)() const&& noexcept>();

    test_is_trivially_copyable<void (Class::*)(int)>();
    test_is_trivially_copyable<void (Class::*)(int)&>();
    test_is_trivially_copyable<void (Class::*)(int) &&>();
    test_is_trivially_copyable<void (Class::*)(int) const>();
    test_is_trivially_copyable<void (Class::*)(int) const&>();
    test_is_trivially_copyable<void (Class::*)(int) const&&>();

    test_is_trivially_copyable<void (Class::*)(int) noexcept>();
    test_is_trivially_copyable<void (Class::*)(int)& noexcept>();
    test_is_trivially_copyable<void (Class::*)(int)&& noexcept>();
    test_is_trivially_copyable<void (Class::*)(int) const noexcept>();
    test_is_trivially_copyable<void (Class::*)(int) const& noexcept>();
    test_is_trivially_copyable<void (Class::*)(int) const&& noexcept>();

    test_is_trivially_copyable<void (Class::*)(...)>();
    test_is_trivially_copyable<void (Class::*)(...)&>();
    test_is_trivially_copyable<void (Class::*)(...) &&>();
    test_is_trivially_copyable<void (Class::*)(...) const>();
    test_is_trivially_copyable<void (Class::*)(...) const&>();
    test_is_trivially_copyable<void (Class::*)(...) const&&>();

    test_is_trivially_copyable<void (Class::*)(...) noexcept>();
    test_is_trivially_copyable<void (Class::*)(...)& noexcept>();
    test_is_trivially_copyable<void (Class::*)(...)&& noexcept>();
    test_is_trivially_copyable<void (Class::*)(...) const noexcept>();
    test_is_trivially_copyable<void (Class::*)(...) const& noexcept>();
    test_is_trivially_copyable<void (Class::*)(...) const&& noexcept>();
}