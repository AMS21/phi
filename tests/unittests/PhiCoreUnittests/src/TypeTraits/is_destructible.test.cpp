#include <catch2/catch.hpp>

#include "TestTypes.hpp"
#include <Phi/Core/Nullptr.hpp>
#include <Phi/TypeTraits/is_destructible.hpp>

template <typename T>
void test_is_destructible()
{
    STATIC_REQUIRE(phi::is_destructible<T>::value);
    STATIC_REQUIRE(phi::is_destructible<const T>::value);
    STATIC_REQUIRE(phi::is_destructible<volatile T>::value);
    STATIC_REQUIRE(phi::is_destructible<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_destructible_v<T>);
    STATIC_REQUIRE(phi::is_destructible_v<const T>);
    STATIC_REQUIRE(phi::is_destructible_v<volatile T>);
    STATIC_REQUIRE(phi::is_destructible_v<const volatile T>);
#endif
}

template <typename T>
void test_is_not_destructible()
{
    STATIC_REQUIRE_FALSE(phi::is_destructible<T>::value);
    STATIC_REQUIRE_FALSE(phi::is_destructible<const T>::value);
    STATIC_REQUIRE_FALSE(phi::is_destructible<volatile T>::value);
    STATIC_REQUIRE_FALSE(phi::is_destructible<const volatile T>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_destructible_v<T>);
    STATIC_REQUIRE_FALSE(phi::is_destructible_v<const T>);
    STATIC_REQUIRE_FALSE(phi::is_destructible_v<volatile T>);
    STATIC_REQUIRE_FALSE(phi::is_destructible_v<const volatile T>);
#endif
}

class NotEmpty2
{
    virtual ~NotEmpty2();
};

struct A
{
    ~A();
};

using Function = void();

struct PublicAbstract
{
    virtual ~PublicAbstract() = default;

public:
    virtual void foo() = 0;
};

struct ProtectedAbstract
{
    virtual ~ProtectedAbstract() = default;

protected:
    virtual void foo() = 0;
};

struct PrivateAbstract
{
    virtual ~PrivateAbstract() = default;

private:
    virtual void foo() = 0;
};

struct PublicDestructor
{
public:
    ~PublicDestructor() = default;
};

struct ProtectedDestructor
{
protected:
    ~ProtectedDestructor() = default;
};

struct PrivateDestructor
{
private:
    ~PrivateDestructor() = default;
};

struct VirtualPublicDestructor
{
public:
    virtual ~VirtualPublicDestructor() = default;
};

struct VirtualProtectedDestructor
{
protected:
    virtual ~VirtualProtectedDestructor() = default;
};

struct VirtualPrivateDestructor
{
private:
    virtual ~VirtualPrivateDestructor() = default;
};

struct PurePublicDestructor
{
public:
    virtual ~PurePublicDestructor() = 0;
};

struct PureProtectedDestructor
{
protected:
    virtual ~PureProtectedDestructor() = 0;
};

struct PurePrivateDestructor
{
private:
    virtual ~PurePrivateDestructor() = 0;
};

struct DeletedPublicDestructor
{
public:
    ~DeletedPublicDestructor() = delete;
};

struct DeletedProtectedDestructor
{
protected:
    ~DeletedProtectedDestructor() = delete;
};

struct DeletedPrivateDestructor
{
private:
    ~DeletedPrivateDestructor() = delete;
};

struct DeletedVirtualPublicDestructor
{
public:
    virtual ~DeletedVirtualPublicDestructor() = delete;
};

struct DeletedVirtualProtectedDestructor
{
protected:
    virtual ~DeletedVirtualProtectedDestructor() = delete;
};

struct DeletedVirtualPrivateDestructor
{
private:
    virtual ~DeletedVirtualPrivateDestructor() = delete;
};

TEST_CASE("is_destructible")
{
    test_is_destructible<phi::nullptr_t>();
    test_is_destructible<A>();
    test_is_destructible<int&>();
    test_is_destructible<int&&>();
    test_is_destructible<Union>();
    test_is_destructible<Empty>();
    test_is_destructible<int>();
    test_is_destructible<short>();
    test_is_destructible<float>();
    test_is_destructible<double>();
    test_is_destructible<int*>();
    test_is_destructible<const int*>();
    test_is_destructible<volatile int*>();
    test_is_destructible<const volatile int*>();
    test_is_destructible<int**>();
    test_is_destructible<char[3]>();
    test_is_destructible<char[2][3]>();
    test_is_destructible<bit_zero>();
    test_is_destructible<int[3]>();
    test_is_destructible<int[4][3]>();
    test_is_destructible<Class>();
    test_is_destructible<Struct>();
    test_is_destructible<NotEmpty>();
    test_is_destructible<NonEmptyUnion>();
    test_is_destructible<AbstractTemplate<int>>();
    test_is_destructible<AbstractTemplate<double>>();
    test_is_destructible<Enum>();
    test_is_destructible<EnumSigned>();
    test_is_destructible<EnumUnsigned>();
    test_is_destructible<EnumClass>();
    test_is_destructible<ProtectedAbstract>();
    test_is_destructible<PublicAbstract>();
    test_is_destructible<PrivateAbstract>();
    test_is_destructible<PublicDestructor>();
    test_is_destructible<VirtualPublicDestructor>();
    test_is_destructible<PurePublicDestructor>();
    test_is_destructible<FunctionPtr>();
    test_is_destructible<MemberObjectPtr>();
    test_is_destructible<MemberFunctionPtr>();

    test_is_not_destructible<int[]>();
    test_is_not_destructible<char[]>();
    test_is_not_destructible<char[][3]>();
    test_is_not_destructible<int[][3]>();
    test_is_not_destructible<void>();
    test_is_not_destructible<Function>();

    // Test access controlled destructors
    test_is_not_destructible<ProtectedDestructor>();
    test_is_not_destructible<PrivateDestructor>();
    test_is_not_destructible<VirtualProtectedDestructor>();
    test_is_not_destructible<VirtualPrivateDestructor>();
    test_is_not_destructible<PureProtectedDestructor>();
    test_is_not_destructible<PurePrivateDestructor>();

    // Test deleted constructors
    test_is_not_destructible<DeletedPublicDestructor>();
    test_is_not_destructible<DeletedProtectedDestructor>();
    test_is_not_destructible<DeletedPrivateDestructor>();
    test_is_not_destructible<DeletedVirtualPublicDestructor>();
    test_is_not_destructible<DeletedVirtualProtectedDestructor>();
    test_is_not_destructible<DeletedVirtualPrivateDestructor>();

    // Test private destructors
    test_is_not_destructible<NotEmpty2>();
    test_is_not_destructible<Abstract>();
}
