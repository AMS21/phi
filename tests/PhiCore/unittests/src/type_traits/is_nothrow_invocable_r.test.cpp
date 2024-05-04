#include <phi/test/test_macros.hpp>

#include "type_traits_helper.hpp"
#include <phi/compiler_support/constexpr.hpp>
#include <phi/compiler_support/noexcept.hpp>
#include <phi/compiler_support/warning.hpp>
#include <phi/core/nullptr_t.hpp>
#include <type_traits>
#include <vector>

PHI_GCC_SUPPRESS_WARNING_PUSH()
PHI_GCC_SUPPRESS_WARNING("-Wnoexcept")

#include <phi/type_traits/is_invocable_r.hpp>
#include <phi/type_traits/is_nothrow_invocable_r.hpp>

struct Tag
{};

struct Implicit
{
    Implicit(int /*unused*/) PHI_NOEXCEPT
    {}
};

struct ThrowsImplicit
{
    ThrowsImplicit(int /*unused*/)
    {}
};

struct Explicit
{
    explicit Explicit(int /*unused*/) PHI_NOEXCEPT
    {}
};

template <bool IsNoexcept, typename RetT, typename... ArgsT>
struct CallObject
{
    RetT operator()(ArgsT&&...) const PHI_NOEXCEPT_EXPR(IsNoexcept);
};

struct Sink
{
    template <typename... ArgsT>
    void operator()(ArgsT&&... /*unused*/) const PHI_NOEXCEPT // NOLINT(cert-dcl50-cpp)
    {}
};

template <typename RetT, typename FuncT, typename... ArgsT>
PHI_CONSTEXPR bool throws_invocable_r()
{
#if PHI_HAS_WORKING_IS_INVOCABLE()
    return phi::is_invocable_r<RetT, FuncT, ArgsT...>::value &&
           !phi::is_not_invocable_r<RetT, FuncT, ArgsT...>::value &&
           !phi::is_nothrow_invocable_r<RetT, FuncT, ArgsT...>::value &&
           phi::is_not_nothrow_invocable_r<RetT, FuncT, ArgsT...>::value
#    if PHI_CPP_STANDARD_IS_ATLEAST(17) && PHI_COMPILER_WORKAROUND(GCC, 7, 0, 0)
           && std::is_invocable_r<RetT, FuncT, ArgsT...>::value &&
           !std::is_nothrow_invocable_r<RetT, FuncT, ArgsT...>::value
#    endif
            ;
#else
    return true;
#endif
}

template <typename FunctionT, typename... ArgsT>
void test_is_nothrow_invocable_r()
{
#if PHI_HAS_WORKING_IS_INVOCABLE()
    STATIC_REQUIRE(phi::is_nothrow_invocable_r<FunctionT, ArgsT...>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_nothrow_invocable_r<FunctionT, ArgsT...>::value);
    STATIC_REQUIRE(phi::is_invocable_r<FunctionT, ArgsT...>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_nothrow_invocable_r_v<FunctionT, ArgsT...>);
    STATIC_REQUIRE_FALSE(phi::is_not_nothrow_invocable_r_v<FunctionT, ArgsT...>);
    STATIC_REQUIRE(phi::is_invocable_r_v<FunctionT, ArgsT...>);
#    endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_nothrow_invocable_r<FunctionT, ArgsT...>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_nothrow_invocable_r<FunctionT, ArgsT...>);

    // Standard compatibility
#    if PHI_CPP_STANDARD_IS_ATLEAST(17) && PHI_COMPILER_WORKAROUND(GCC, 7, 0, 0)
    STATIC_REQUIRE(std::is_invocable_r<FunctionT, ArgsT...>::value);
    STATIC_REQUIRE(std::is_nothrow_invocable_r<FunctionT, ArgsT...>::value);
#    endif
#endif
}

template <typename FunctionT, typename... ArgsT>
void test_is_not_nothrow_invocable_r_no_std()
{
#if PHI_HAS_WORKING_IS_INVOCABLE()
    STATIC_REQUIRE_FALSE(phi::is_nothrow_invocable_r<FunctionT, ArgsT...>::value);
    STATIC_REQUIRE(phi::is_not_nothrow_invocable_r<FunctionT, ArgsT...>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_nothrow_invocable_r_v<FunctionT, ArgsT...>);
    STATIC_REQUIRE(phi::is_not_nothrow_invocable_r_v<FunctionT, ArgsT...>);
#    endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_nothrow_invocable_r<FunctionT, ArgsT...>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_nothrow_invocable_r<FunctionT, ArgsT...>);
#endif
}

template <typename FunctionT, typename... ArgsT>
void test_is_not_nothrow_invocable_r()
{
#if PHI_HAS_WORKING_IS_INVOCABLE()
    test_is_not_nothrow_invocable_r_no_std<FunctionT, ArgsT...>();

    // Standard compatibility
#    if PHI_CPP_STANDARD_IS_ATLEAST(17) && PHI_COMPILER_WORKAROUND(GCC, 7, 0, 0)
    STATIC_REQUIRE_FALSE(std::is_nothrow_invocable_r<FunctionT, ArgsT...>::value);
#    endif
#endif
}

template <typename FunctionT, typename... ArgsT>
void test_is_not_nothrow_invocable_r_compat()
{
#if PHI_COMPILER_IS_BELOW(EMCC, 1, 39, 0)
    test_is_not_nothrow_invocable_r_no_std<FunctionT, ArgsT...>();
#else
    test_is_not_nothrow_invocable_r<FunctionT, ArgsT...>();
#endif
}

TEST_CASE("is_nothrow_invocable_r")
{
#if PHI_HAS_FEATURE_NOEXCEPT_FUNCTION_TYPE()
    using AbominableFunc = void(...) const PHI_NOEXCEPT;
#else
    using AbominableFunc = void(...) const;
#endif
    //  Non-callable things
    {
        test_is_not_nothrow_invocable_r_compat<int, void>();
        test_is_not_nothrow_invocable_r_compat<int, const void>();
        test_is_not_nothrow_invocable_r_compat<int, volatile void>();
        test_is_not_nothrow_invocable_r_compat<int, const volatile void>();
        test_is_not_nothrow_invocable_r<int, phi::nullptr_t>();
        test_is_not_nothrow_invocable_r<int, int>();
        test_is_not_nothrow_invocable_r<int, double>();

        test_is_not_nothrow_invocable_r<int, int[]>();
        test_is_not_nothrow_invocable_r<int, int[3]>();

        test_is_not_nothrow_invocable_r<int, int*>();
        test_is_not_nothrow_invocable_r<int, const int*>();
        test_is_not_nothrow_invocable_r<int, int const*>();

        test_is_not_nothrow_invocable_r<int, int&>();
        test_is_not_nothrow_invocable_r<int, const int&>();
        test_is_not_nothrow_invocable_r<int, int&&>();

        test_is_not_nothrow_invocable_r<int, std::vector<int>>();
        test_is_not_nothrow_invocable_r<int, std::vector<int*>>();
        test_is_not_nothrow_invocable_r<int, std::vector<int**>>();

        test_is_not_nothrow_invocable_r_compat<int, AbominableFunc>();

        //  with parameters
        test_is_not_nothrow_invocable_r<int, int, int>();
        test_is_not_nothrow_invocable_r<int, int, double, float>();
        test_is_not_nothrow_invocable_r<int, int, char, double, float>();
        test_is_not_nothrow_invocable_r_compat<void, Sink, AbominableFunc>();
        test_is_not_nothrow_invocable_r_compat<void, Sink, void>();
        test_is_not_nothrow_invocable_r_compat<void, Sink, const void>();
        test_is_not_nothrow_invocable_r_compat<void, Sink, volatile void>();
        test_is_not_nothrow_invocable_r_compat<void, Sink, const volatile void>();
    }

    {
        // Check that the conversion to the return type is properly checked
        using Fn = CallObject<true, int>;
        test_is_nothrow_invocable_r<Implicit, Fn>();
        test_is_nothrow_invocable_r<double, Fn>();
        test_is_nothrow_invocable_r<void, Fn>();
        test_is_nothrow_invocable_r<const void, Fn>();
        test_is_nothrow_invocable_r<volatile void, Fn>();
        test_is_nothrow_invocable_r<const volatile void, Fn>();
        STATIC_REQUIRE(throws_invocable_r<ThrowsImplicit, Fn>());
    }
    {
        // Check that PMD derefs are noexcept
        using Fn = int Tag::*;
        test_is_nothrow_invocable_r<Implicit, Fn, Tag&>();
        STATIC_REQUIRE(throws_invocable_r<ThrowsImplicit, Fn, Tag&>());
    }
    {
        // Check for is_nothrow_invocable_r_v
        using Fn = CallObject<true, int>;
        test_is_nothrow_invocable_r<void, Fn>();
        test_is_not_nothrow_invocable_r<int, Fn, int>();
    }
}

PHI_GCC_SUPPRESS_WARNING_POP()
