#include <catch2/catch.hpp>

#include "TestTypes.hpp"
#include <Phi/CompilerSupport/Char8_t.hpp>
#include <Phi/Core/Nullptr.hpp>
#include <Phi/TypeTraits/is_nothrow_copy_constructible.hpp>

template <typename T>
void test_is_nothrow_copy_constructible()
{
    STATIC_REQUIRE(phi::is_nothrow_copy_constructible<T>::value);
    STATIC_REQUIRE(phi::is_nothrow_copy_constructible<const T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_nothrow_copy_constructible_v<T>);
    STATIC_REQUIRE(phi::is_nothrow_copy_constructible_v<const T>);
#endif
}

template <class T>
void test_is_not_nothrow_copy_constructible()
{
    STATIC_REQUIRE_FALSE(phi::is_nothrow_copy_constructible<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_nothrow_copy_constructible<const T>::value);
    STATIC_REQUIRE_FALSE(phi::is_nothrow_copy_constructible<volatile T>::value);
    STATIC_REQUIRE_FALSE(phi::is_nothrow_copy_constructible<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_nothrow_copy_constructible_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_nothrow_copy_constructible_v<const T>);
    STATIC_REQUIRE_FALSE(phi::is_nothrow_copy_constructible_v<volatile T>);
    STATIC_REQUIRE_FALSE(phi::is_nothrow_copy_constructible_v<const volatile T>);
#endif
}

struct A
{
    A(const A&);
};

struct B
{
    B(const B&) noexcept;
};

TEST_CASE("is_nothrow_copy_constructible")
{
    test_is_not_nothrow_copy_constructible<void>();
    test_is_nothrow_copy_constructible<phi::nullptr_t>();
    test_is_nothrow_copy_constructible<bool>();
    test_is_nothrow_copy_constructible<char>();
    test_is_nothrow_copy_constructible<signed char>();
    test_is_nothrow_copy_constructible<unsigned char>();
    test_is_nothrow_copy_constructible<short>();
    test_is_nothrow_copy_constructible<unsigned short>();
    test_is_nothrow_copy_constructible<int>();
    test_is_nothrow_copy_constructible<unsigned int>();
    test_is_nothrow_copy_constructible<long>();
    test_is_nothrow_copy_constructible<unsigned long>();
    test_is_nothrow_copy_constructible<long long>();
    test_is_nothrow_copy_constructible<unsigned long long>();
    test_is_nothrow_copy_constructible<float>();
    test_is_nothrow_copy_constructible<double>();
    test_is_nothrow_copy_constructible<long double>();
    test_is_nothrow_copy_constructible<char8_t>();
    test_is_nothrow_copy_constructible<char16_t>();
    test_is_nothrow_copy_constructible<char32_t>();
    test_is_nothrow_copy_constructible<wchar_t>();

    test_is_nothrow_copy_constructible<int&>();
    test_is_not_nothrow_copy_constructible<int&&>();
    test_is_nothrow_copy_constructible<int*>();
    test_is_nothrow_copy_constructible<const int*>();
    test_is_nothrow_copy_constructible<volatile int*>();
    test_is_nothrow_copy_constructible<const volatile int*>();
    test_is_nothrow_copy_constructible<int**>();
    test_is_nothrow_copy_constructible<Class>();
    test_is_nothrow_copy_constructible<Union>();
    test_is_nothrow_copy_constructible<NonEmptyUnion>();
    test_is_nothrow_copy_constructible<Empty>();
    test_is_nothrow_copy_constructible<NotEmpty>();
    test_is_nothrow_copy_constructible<bit_zero>();
    test_is_nothrow_copy_constructible<bit_one>();
    test_is_not_nothrow_copy_constructible<Abstract>();
    test_is_not_nothrow_copy_constructible<AbstractTemplate<int>>();
    test_is_nothrow_copy_constructible<AbstractTemplate<double>>();
    test_is_not_nothrow_copy_constructible<AbstractTemplate<Class>>();
    test_is_nothrow_copy_constructible<Enum>();
    test_is_nothrow_copy_constructible<EnumSigned>();
    test_is_nothrow_copy_constructible<EnumUnsigned>();
    test_is_nothrow_copy_constructible<EnumClass>();
    test_is_not_nothrow_copy_constructible<Function>();
    test_is_nothrow_copy_constructible<FunctionPtr>();
    test_is_nothrow_copy_constructible<MemberObjectPtr>();
    test_is_nothrow_copy_constructible<MemberFunctionPtr>();

    test_is_not_nothrow_copy_constructible<A>();
    test_is_nothrow_copy_constructible<B>();
}
