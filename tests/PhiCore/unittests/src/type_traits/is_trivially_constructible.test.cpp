#include <phi/test/test_macros.hpp>

#include "type_traits_helper.hpp"
#include <phi/type_traits/is_constructible.hpp>
#include <phi/type_traits/is_trivially_constructible.hpp>
#include <type_traits>

template <typename TypeT, typename... ArgsT>
void test_is_trivially_constructible()
{
#if PHI_HAS_WORKING_IS_TRIVIALLY_CONSTRUCTIBLE()
    STATIC_REQUIRE(phi::is_trivially_constructible<TypeT, ArgsT...>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_trivially_constructible<TypeT, ArgsT...>::value);
    STATIC_REQUIRE(phi::is_constructible<TypeT, ArgsT...>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_trivially_constructible_v<TypeT, ArgsT...>);
    STATIC_REQUIRE_FALSE(phi::is_not_trivially_constructible_v<TypeT, ArgsT...>);
    STATIC_REQUIRE(phi::is_constructible_v<TypeT, ArgsT...>);
#    endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_trivially_constructible<TypeT, ArgsT...>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_trivially_constructible<TypeT, ArgsT...>);

    // Standard compatibility
    STATIC_REQUIRE(std::is_trivially_constructible<TypeT, ArgsT...>::value);
#endif
}

template <typename TypeT, typename... ArgsT>
void test_is_not_trivially_constructible()
{
#if PHI_HAS_WORKING_IS_TRIVIALLY_CONSTRUCTIBLE()
    STATIC_REQUIRE_FALSE(phi::is_trivially_constructible<TypeT, ArgsT...>::value);
    STATIC_REQUIRE(phi::is_not_trivially_constructible<TypeT, ArgsT...>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_trivially_constructible_v<TypeT, ArgsT...>);
    STATIC_REQUIRE(phi::is_not_trivially_constructible_v<TypeT, ArgsT...>);
#    endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_trivially_constructible<TypeT, ArgsT...>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_trivially_constructible<TypeT, ArgsT...>);

    // Standard compatibility
    STATIC_REQUIRE_FALSE(std::is_trivially_constructible<TypeT, ArgsT...>::value);
#endif
}

struct A
{
    explicit A(int);
    A(int, double);
};

struct B
{
    B() = default;

    B(int /*unused*/)
    {}
};

template <typename TypeT>
struct wrap
{
    TypeT t;
    wrap(const wrap& other)
        : t(other.t)
    {}
};

struct nocopy
{
    nocopy(const nocopy&) = delete;
};

struct HasTemplateCCtor
{
    HasTemplateCCtor(const HasTemplateCCtor&) = default;

    template <typename TypeT>
    // NOLINTNEXTLINE(bugprone-forwarding-reference-overload)
    HasTemplateCCtor(TypeT&&);
};

struct MoveOnly
{
    MoveOnly(MoveOnly&&) = default;
};

struct MoveOnly2
{
    MoveOnly2(MoveOnly2&&) = delete;
};

TEST_CASE("is_trivially_constructible")
{
    test_is_trivially_constructible<int>();
    test_is_trivially_constructible<int, int>();
    test_is_trivially_constructible<int, int&>();
    test_is_trivially_constructible<int, int&&>();
    test_is_trivially_constructible<int, const int&>();

    test_is_not_trivially_constructible<A>();
    test_is_not_trivially_constructible<A, int>();
    test_is_not_trivially_constructible<A, int, double>();

    test_is_trivially_constructible<B>();
    test_is_not_trivially_constructible<B, int>();

#if PHI_COMPILER_WORKAROUND(GCC, 7, 0, 0)
    test_is_not_trivially_constructible<wrap<nocopy>, const wrap<nocopy>&>();
#else
    SKIP_CHECK();
#endif

    test_is_not_trivially_constructible<HasTemplateCCtor>();
    test_is_not_trivially_constructible<HasTemplateCCtor, HasTemplateCCtor>();
    test_is_trivially_constructible<HasTemplateCCtor, const HasTemplateCCtor&>();

    test_is_not_trivially_constructible<MoveOnly>();
    test_is_trivially_constructible<MoveOnly, MoveOnly>();
    test_is_not_trivially_constructible<MoveOnly, MoveOnly&>();
    test_is_trivially_constructible<MoveOnly, MoveOnly&&>();
    test_is_not_trivially_constructible<MoveOnly, const MoveOnly&>();

    test_is_not_trivially_constructible<MoveOnly2>();
}
