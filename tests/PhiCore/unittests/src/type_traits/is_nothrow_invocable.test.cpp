#include <phi/test/test_macros.hpp>

#include "type_traits_helper.hpp"
#include <phi/compiler_support/constexpr.hpp>
#include <phi/compiler_support/warning.hpp>
#include <phi/core/nullptr_t.hpp>

PHI_GCC_SUPPRESS_WARNING_PUSH()
PHI_GCC_SUPPRESS_WARNING("-Wnoexcept")

#include <phi/type_traits/is_invocable.hpp>
#include <phi/type_traits/is_nothrow_invocable.hpp>
#include <type_traits>
#include <vector>

struct Tag
{};

struct Implicit
{
    Implicit(int /*unused*/) noexcept
    {}
};

struct ThrowsImplicit
{
    ThrowsImplicit(int /*unused*/)
    {}
};

struct Explicit
{
    explicit Explicit(int /*unused*/) noexcept
    {}
};

template <bool IsNoexcept, typename RetT, typename... ArgsT>
struct CallObject
{
    RetT operator()(ArgsT&&...) const noexcept(IsNoexcept);
};

struct Sink
{
    template <typename... ArgsT>
    void operator()(ArgsT&&... /*unused*/) const noexcept
    {}
};

template <typename FunctionT, typename... ArgsT>
PHI_CONSTEXPR bool throws_invocable()
{
    return phi::is_invocable<FunctionT, ArgsT...>::value &&
           !phi::is_not_invocable<FunctionT, ArgsT...>::value &&
           !phi::is_nothrow_invocable<FunctionT, ArgsT...>::value &&
           phi::is_not_nothrow_invocable<FunctionT, ArgsT...>::value
#if PHI_CPP_STANDARD_IS_ATLEAST(17) && PHI_COMPILER_WORKAROUND(GCC, 7, 0, 0)
           && std::is_invocable<FunctionT, ArgsT...>::value &&
           !std::is_nothrow_invocable<FunctionT, ArgsT...>::value
#endif
            ;
}

PHI_CLANG_SUPPRESS_WARNING_PUSH()
PHI_CLANG_SUPPRESS_WARNING("-Wunneeded-member-function")
PHI_CLANG_SUPPRESS_WARNING("-Wunused-member-function")

void test_noexcept_function_pointers()
{
    struct Dummy
    {
        void foo() noexcept
        {}
        static void bar() noexcept
        {}
    };

#if PHI_HAS_WORKING_IS_INVOCABLE()
#    if !PHI_HAS_FEATURE_NOEXCEPT_FUNCTION_TYPE()
    {
#        if PHI_COMPILER_WORKAROUND(GCC, 7, 0, 0)
        // Check that PMF's and function pointers *work*. is_nothrow_invocable will always
        // return false because 'noexcept' is not part of the function type.
        STATIC_REQUIRE(throws_invocable<decltype(&Dummy::foo), Dummy&>());
        STATIC_REQUIRE(throws_invocable<decltype(&Dummy::bar)>());
#        else
        SKIP_CHECK();
#        endif
    }
#    else
    {
        // Check that PMF's and function pointers actually work and that
        // is_nothrow_invocable returns true for noexcept PMF's and function
        // pointers.
        STATIC_REQUIRE(phi::is_nothrow_invocable<decltype(&Dummy::foo), Dummy&>::value);
        STATIC_REQUIRE_FALSE(phi::is_not_nothrow_invocable<decltype(&Dummy::foo), Dummy&>::value);
        STATIC_REQUIRE(phi::is_invocable<decltype(&Dummy::foo), Dummy&>::value);

        STATIC_REQUIRE(phi::is_nothrow_invocable<decltype(&Dummy::bar)>::value);
        STATIC_REQUIRE_FALSE(phi::is_not_nothrow_invocable<decltype(&Dummy::bar)>::value);
        STATIC_REQUIRE(phi::is_invocable<decltype(&Dummy::bar)>::value);

#        if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
        STATIC_REQUIRE(phi::is_nothrow_invocable_v<decltype(&Dummy::foo), Dummy&>);
        STATIC_REQUIRE_FALSE(phi::is_not_nothrow_invocable_v<decltype(&Dummy::foo), Dummy&>);
        STATIC_REQUIRE(phi::is_invocable_v<decltype(&Dummy::foo), Dummy&>);

        STATIC_REQUIRE(phi::is_nothrow_invocable_v<decltype(&Dummy::bar)>);
        STATIC_REQUIRE_FALSE(phi::is_not_nothrow_invocable_v<decltype(&Dummy::bar)>);
        STATIC_REQUIRE(phi::is_invocable_v<decltype(&Dummy::bar)>);
#        endif

        TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_nothrow_invocable<decltype(&Dummy::foo), Dummy&>);
        TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_nothrow_invocable<decltype(&Dummy::foo), Dummy&>);

        // Standard compatibility
#        if PHI_CPP_STANDARD_IS_ATLEAST(17)
        STATIC_REQUIRE(std::is_nothrow_invocable<decltype(&Dummy::foo), Dummy&>::value);
        STATIC_REQUIRE(std::is_nothrow_invocable<decltype(&Dummy::bar)>::value);
        STATIC_REQUIRE(std::is_invocable<decltype(&Dummy::foo), Dummy&>::value);
        STATIC_REQUIRE(std::is_invocable<decltype(&Dummy::bar)>::value);
#        endif
    }
#    endif
#endif
}

PHI_CLANG_SUPPRESS_WARNING_POP()

template <typename FunctionT, typename... ArgsT>
void test_is_nothrow_invocable()
{
#if PHI_HAS_WORKING_IS_INVOCABLE()
    STATIC_REQUIRE(phi::is_nothrow_invocable<FunctionT, ArgsT...>::value);
    STATIC_REQUIRE_FALSE(phi::is_not_nothrow_invocable<FunctionT, ArgsT...>::value);
    STATIC_REQUIRE(phi::is_invocable<FunctionT, ArgsT...>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_nothrow_invocable_v<FunctionT, ArgsT...>);
    STATIC_REQUIRE_FALSE(phi::is_not_nothrow_invocable_v<FunctionT, ArgsT...>);
    STATIC_REQUIRE(phi::is_invocable_v<FunctionT, ArgsT...>);
#    endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_nothrow_invocable<FunctionT, ArgsT...>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_nothrow_invocable<FunctionT, ArgsT...>);

    // Standard compatibility
#    if PHI_CPP_STANDARD_IS_ATLEAST(17) && PHI_COMPILER_WORKAROUND(GCC, 7, 0, 0)
    STATIC_REQUIRE(std::is_nothrow_invocable<FunctionT, ArgsT...>::value);
    STATIC_REQUIRE(std::is_invocable<FunctionT, ArgsT...>::value);
#    endif
#endif
}

template <typename FunctionT, typename... ArgsT>
void test_is_not_nothrow_invocable_no_std()
{
#if PHI_HAS_WORKING_IS_INVOCABLE()
    STATIC_REQUIRE_FALSE(phi::is_nothrow_invocable<FunctionT, ArgsT...>::value);
    STATIC_REQUIRE(phi::is_not_nothrow_invocable<FunctionT, ArgsT...>::value);

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_nothrow_invocable_v<FunctionT, ArgsT...>);
    STATIC_REQUIRE(phi::is_not_nothrow_invocable_v<FunctionT, ArgsT...>);
#    endif

    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_nothrow_invocable<FunctionT, ArgsT...>);
    TEST_TYPE_TRAITS_TYPE_DEFS(phi::is_not_nothrow_invocable<FunctionT, ArgsT...>);
#endif
}

template <typename FunctionT, typename... ArgsT>
void test_is_not_nothrow_invocable()
{
#if PHI_HAS_WORKING_IS_INVOCABLE()
    test_is_not_nothrow_invocable_no_std<FunctionT, ArgsT...>();

    // Standard compatibility
#    if PHI_CPP_STANDARD_IS_ATLEAST(17) && PHI_COMPILER_WORKAROUND(GCC, 7, 0, 0)
    STATIC_REQUIRE_FALSE(std::is_nothrow_invocable<FunctionT, ArgsT...>::value);
#    endif
#endif
}

template <typename FunctionT, typename... ArgsT>
void test_is_not_nothrow_invocable_compat()
{
#if PHI_COMPILER_IS_BELOW(EMCC, 1, 39, 0)
    test_is_not_nothrow_invocable_no_std<FunctionT, ArgsT...>();
#else
    test_is_not_nothrow_invocable<FunctionT, ArgsT...>();
#endif
}

TEST_CASE("is_nothrow_invocable")
{
#if PHI_HAS_FEATURE_NOEXCEPT_FUNCTION_TYPE()
    using AbominableFunc = void(...) const noexcept;
#else
    using AbominableFunc = void(...) const;
#endif
    //  Non-callable things
    {
        test_is_not_nothrow_invocable_compat<void>();
        test_is_not_nothrow_invocable_compat<const void>();
        test_is_not_nothrow_invocable_compat<volatile void>();
        test_is_not_nothrow_invocable_compat<const volatile void>();
        test_is_not_nothrow_invocable<phi::nullptr_t>();
        test_is_not_nothrow_invocable<int>();
        test_is_not_nothrow_invocable<double>();

        test_is_not_nothrow_invocable<int[]>();
        test_is_not_nothrow_invocable<int[3]>();

        test_is_not_nothrow_invocable<int*>();
        test_is_not_nothrow_invocable<const int*>();
        test_is_not_nothrow_invocable<int const*>();

        test_is_not_nothrow_invocable<int&>();
        test_is_not_nothrow_invocable<const int&>();
        test_is_not_nothrow_invocable<int&&>();

        test_is_not_nothrow_invocable<int, std::vector<int>>();
        test_is_not_nothrow_invocable<int, std::vector<int*>>();
        test_is_not_nothrow_invocable<int, std::vector<int**>>();

        test_is_not_nothrow_invocable_compat<int, AbominableFunc>();

        //  with parameters
        test_is_not_nothrow_invocable<int, int>();
        test_is_not_nothrow_invocable<int, double, float>();
        test_is_not_nothrow_invocable<int, char, float, double>();
        test_is_not_nothrow_invocable_compat<Sink, AbominableFunc>();
        test_is_not_nothrow_invocable_compat<Sink, void>();
        test_is_not_nothrow_invocable_compat<Sink, const void>();
        test_is_not_nothrow_invocable_compat<Sink, volatile void>();
        test_is_not_nothrow_invocable_compat<Sink, const volatile void>();
    }

    {
        // Check that the conversion to the return type is properly checked
        using Fn = CallObject<true, int>;
        test_is_not_nothrow_invocable<Fn(), Explicit>();
    }
    {
        // Check that the conversion to the parameters is properly checked
        using Fn = CallObject<true, void, const Implicit&, const ThrowsImplicit&>;
        test_is_nothrow_invocable<Fn, Implicit&, ThrowsImplicit&>();
        test_is_nothrow_invocable<Fn, int, ThrowsImplicit&>();
        STATIC_REQUIRE(throws_invocable<Fn, int, int>());
        test_is_not_nothrow_invocable<Fn>();
    }
    {
        // Check that the noexcept-ness of function objects is checked.
        using Fn  = CallObject<true, void>;
        using Fn2 = CallObject<false, void>;
        test_is_nothrow_invocable<Fn>();
        STATIC_REQUIRE(throws_invocable<Fn2>());
    }
    {
        // Check that PMD derefs are noexcept
        using Fn = int Tag::*;
        test_is_nothrow_invocable<Fn, Tag&>();
    }
    {
        // Check for is_nothrow_invocable_v
        using Fn = CallObject<true, int>;
        test_is_nothrow_invocable<Fn>();
        test_is_not_nothrow_invocable<Fn, int>();
    }

    test_noexcept_function_pointers();
}

PHI_GCC_SUPPRESS_WARNING_POP()
