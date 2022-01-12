#include <phi/test/test_macros.hpp>

#include <phi/core/nullptr_t.hpp>
#include <phi/type_traits/is_invocable_r.hpp>

struct Tag
{};

struct DerFromTag : Tag
{};

struct Implicit
{
    Implicit(int)
    {}
};

struct Explicit
{
    explicit Explicit(int)
    {}
};

struct NotCallableWithInt
{
    int operator()(int) = delete;
    int operator()(Tag)
    {
        return 42;
    }
};

struct Sink
{
    template <class... Args>
    void operator()(Args&&...) const
    {}
};

template <typename ReturnT, typename FunctionT, typename... ArgsT>
void test_is_invocable_r()
{
    STATIC_REQUIRE(phi::is_invocable_r<ReturnT, FunctionT, ArgsT...>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_invocable_r<ReturnT, FunctionT, ArgsT...>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_invocable_r_v<ReturnT, FunctionT, ArgsT...>);
    STATIC_REQUIRE_FALSE(phi::is_not_invocable_r_v<ReturnT, FunctionT, ArgsT...>);
#endif
}

template <typename ReturnT, typename FunctionT, typename... ArgsT>
void test_is_not_invocable_r()
{
    STATIC_REQUIRE_FALSE(phi::is_invocable_r<ReturnT, FunctionT, ArgsT...>::value);
    STATIC_REQUIRE(phi::is_not_invocable_r<ReturnT, FunctionT, ArgsT...>::value);

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_invocable_r_v<ReturnT, FunctionT, ArgsT...>);
    STATIC_REQUIRE(phi::is_not_invocable_r_v<ReturnT, FunctionT, ArgsT...>);
#endif
}

TEST_CASE("is_invocable_r")
{
    using AbominableFunc = void(...) const;

    //  Non-callable things
    {
        // is_invocable_r
        test_is_not_invocable_r<int, void>();
        test_is_not_invocable_r<int, const void>();
        test_is_not_invocable_r<int, volatile void>();
        test_is_not_invocable_r<int, const volatile void>();
        test_is_not_invocable_r<int, phi::nullptr_t>();
        test_is_not_invocable_r<int, short>();
        test_is_not_invocable_r<int, int>();
        test_is_not_invocable_r<int, float>();
        test_is_not_invocable_r<int, double>();

        test_is_not_invocable_r<int, int[]>();
        test_is_not_invocable_r<int, int[3]>();

        test_is_not_invocable_r<int, int*>();
        test_is_not_invocable_r<int, const int*>();
        test_is_not_invocable_r<int, volatile int*>();
        test_is_not_invocable_r<int, const volatile int*>();
        test_is_not_invocable_r<int, int const*>();
        test_is_not_invocable_r<int, int volatile*>();
        test_is_not_invocable_r<int, int const volatile*>();

        test_is_not_invocable_r<int, int**>();
        test_is_not_invocable_r<int, const int**>();
        test_is_not_invocable_r<int, volatile int**>();
        test_is_not_invocable_r<int, const volatile int**>();
        test_is_not_invocable_r<int, int const**>();
        test_is_not_invocable_r<int, int volatile**>();
        test_is_not_invocable_r<int, int const volatile**>();

        test_is_not_invocable_r<int, int&>();
        test_is_not_invocable_r<int, const int&>();
        test_is_not_invocable_r<int, volatile int&>();
        test_is_not_invocable_r<int, const volatile int&>();
        test_is_not_invocable_r<int, int&&>();
        test_is_not_invocable_r<int, const int&&>();
        test_is_not_invocable_r<int, volatile int&&>();
        test_is_not_invocable_r<int, const volatile int&&>();

        test_is_not_invocable_r<int, std::vector<int>>();
        test_is_not_invocable_r<int, std::vector<int*>>();
        test_is_not_invocable_r<int, std::vector<int**>>();

        test_is_not_invocable_r<int, AbominableFunc>();

        //  with parameters
        test_is_not_invocable_r<int, int, int>();
        test_is_not_invocable_r<int, int, double>();
        test_is_not_invocable_r<int, int, double, float>();
        test_is_not_invocable_r<int, int, char, float, double>();
        test_is_not_invocable_r<int, int, unsigned, short, double, float, float, double,
                                signed char, float, float, float, float, float, double,
                                phi::nullptr_t, AbominableFunc, AbominableFunc>();
        test_is_not_invocable_r<int, Sink, AbominableFunc>();
        test_is_not_invocable_r<int, Sink, void>();
        test_is_not_invocable_r<int, Sink, const void>();
        test_is_not_invocable_r<int, Sink, volatile void>();
        test_is_not_invocable_r<int, Sink, const volatile void>();
    }
    {
        // Check that the conversion to the return type is properly checked
        using Fn = int (*)();
        test_is_invocable_r<Implicit, Fn>();
        test_is_invocable_r<double, Fn>();
        test_is_invocable_r<const volatile void, Fn>();
        test_is_not_invocable_r<Explicit, Fn>();
    }
    {
        // Check for is_invocable_r_v
        using Fn = void (*)();
        test_is_invocable_r<void, Fn>();
        test_is_not_invocable_r<int, Fn>();
    }
}