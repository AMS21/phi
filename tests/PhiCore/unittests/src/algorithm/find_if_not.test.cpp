#include <phi/test/test_macros.hpp>

#include "constexpr_helper.hpp"
#include <phi/algorithm/at.hpp>
#include <phi/algorithm/find_if_not.hpp>
#include <phi/compiler_support/constexpr.hpp>
#include <phi/compiler_support/features.hpp>
#include <phi/compiler_support/noexcept.hpp>
#include <phi/container/array.hpp>
#include <phi/iterator/begin.hpp>
#include <phi/iterator/end.hpp>

static PHI_CONSTEXPR bool eq0(const int& value) PHI_NOEXCEPT
{
    return value == 0;
}

static PHI_CONSTEXPR bool eq1(const int& value) PHI_NOEXCEPT
{
    return value == 1;
}

static PHI_CONSTEXPR bool eq9(const int& value) PHI_NOEXCEPT
{
    return value == 9;
}

static PHI_CONSTEXPR bool eq10(const int& value) PHI_NOEXCEPT
{
    return value == 10;
}

static PHI_CONSTEXPR bool even(const int& value) PHI_NOEXCEPT
{
    return value % 2 == 0;
}

static PHI_CONSTEXPR bool odd(const int& value) PHI_NOEXCEPT
{
    return value % 2 == 1;
}

static PHI_CONSTEXPR bool always_true(const int& /*value*/) PHI_NOEXCEPT
{
    return true;
}

static PHI_CONSTEXPR bool always_false(const int& /*value*/) PHI_NOEXCEPT
{
    return false;
}

static bool always_false_throw(const int& /*value*/)
{
    throw "";
}

#if PHI_HAS_FEATURE_LAMBDA()

static PHI_CONSTEXPR_AND_CONST auto lambda_eq0 = [](const int& value)
                                                         PHI_NOEXCEPT { return value == 0; };
static PHI_CONSTEXPR_AND_CONST auto lambda_eq1 = [](const int& value)
                                                         PHI_NOEXCEPT { return value == 1; };
static PHI_CONSTEXPR_AND_CONST auto lambda_eq9 = [](const int& value)
                                                         PHI_NOEXCEPT { return value == 9; };
static PHI_CONSTEXPR_AND_CONST auto lambda_eq10 = [](const int& value)
                                                          PHI_NOEXCEPT { return value == 10; };
static PHI_CONSTEXPR_AND_CONST auto lambda_even = [](const int& value)
                                                          PHI_NOEXCEPT { return value % 2 == 0; };
static PHI_CONSTEXPR_AND_CONST auto lambda_odd = [](const int& value)
                                                         PHI_NOEXCEPT { return value % 2 == 1; };
static PHI_CONSTEXPR_AND_CONST auto lambda_true = [](const int& /*value*/)
                                                          PHI_NOEXCEPT { return true; };
static PHI_CONSTEXPR_AND_CONST auto lambda_false = [](const int& /*value*/)
                                                           PHI_NOEXCEPT { return false; };
static PHI_CONSTEXPR_AND_CONST auto lambda_false_throw = [](const int& /*value*/) -> bool {
    throw "";
};

#endif

TEST_CASE("algorithm.find_if_not - c-array")
{
    static PHI_CONSTEXPR_AND_CONST int array[10]{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    // Runtime
    CHECK(phi::find_if_not(phi::begin(array), phi::end(array), eq0) == &phi::at(array, 1u));
    CHECK(phi::find_if_not(phi::begin(array), phi::end(array), eq1) == phi::begin(array));
    CHECK(phi::find_if_not(phi::begin(array), phi::end(array), eq9) == phi::begin(array));
    CHECK(phi::find_if_not(phi::begin(array), phi::end(array), eq10) == phi::begin(array));
    CHECK(phi::find_if_not(phi::begin(array), phi::end(array), even) == &phi::at(array, 1u));
    CHECK(phi::find_if_not(phi::begin(array), phi::end(array), odd) == phi::begin(array));
    CHECK(phi::find_if_not(phi::begin(array), phi::end(array), always_true) == phi::end(array));
    CHECK(phi::find_if_not(phi::begin(array), phi::end(array), always_false) == phi::begin(array));

#if PHI_HAS_FEATURE_LAMBDA()
    CHECK(phi::find_if_not(phi::begin(array), phi::end(array), lambda_eq0) == &phi::at(array, 1u));
    CHECK(phi::find_if_not(phi::begin(array), phi::end(array), lambda_eq1) == phi::begin(array));
    CHECK(phi::find_if_not(phi::begin(array), phi::end(array), lambda_eq9) == phi::begin(array));
    CHECK(phi::find_if_not(phi::begin(array), phi::end(array), lambda_eq10) == phi::begin(array));
    CHECK(phi::find_if_not(phi::begin(array), phi::end(array), lambda_even) == &phi::at(array, 1u));
    CHECK(phi::find_if_not(phi::begin(array), phi::end(array), lambda_odd) == phi::begin(array));
    CHECK(phi::find_if_not(phi::begin(array), phi::end(array), lambda_true) == phi::end(array));
    CHECK(phi::find_if_not(phi::begin(array), phi::end(array), lambda_false) == phi::begin(array));
#endif

    // Constexpr
    EXT_STATIC_REQUIRE(phi::find_if_not(phi::begin(array), phi::end(array), eq0) ==
                       &phi::at(array, 1u));
    EXT_STATIC_REQUIRE(phi::find_if_not(phi::begin(array), phi::end(array), eq1) ==
                       phi::begin(array));
    EXT_STATIC_REQUIRE(phi::find_if_not(phi::begin(array), phi::end(array), eq9) ==
                       phi::begin(array));
    EXT_STATIC_REQUIRE(phi::find_if_not(phi::begin(array), phi::end(array), eq10) ==
                       phi::begin(array));
    EXT_STATIC_REQUIRE(phi::find_if_not(phi::begin(array), phi::end(array), even) ==
                       &phi::at(array, 1u));
    EXT_STATIC_REQUIRE(phi::find_if_not(phi::begin(array), phi::end(array), odd) ==
                       phi::begin(array));
    EXT_STATIC_REQUIRE(phi::find_if_not(phi::begin(array), phi::end(array), always_true) ==
                       phi::end(array));
    EXT_STATIC_REQUIRE(phi::find_if_not(phi::begin(array), phi::end(array), always_false) ==
                       phi::begin(array));

#if PHI_HAS_FEATURE_LAMBDA() && PHI_HAS_FEATURE_CONSTEXPR_LAMBDA()
    EXT_STATIC_REQUIRE(phi::find_if_not(phi::begin(array), phi::end(array), lambda_eq0) ==
                       &phi::at(array, 1u));
    EXT_STATIC_REQUIRE(phi::find_if_not(phi::begin(array), phi::end(array), lambda_eq1) ==
                       phi::begin(array));
    EXT_STATIC_REQUIRE(phi::find_if_not(phi::begin(array), phi::end(array), lambda_eq9) ==
                       phi::begin(array));
    EXT_STATIC_REQUIRE(phi::find_if_not(phi::begin(array), phi::end(array), lambda_eq10) ==
                       phi::begin(array));
    EXT_STATIC_REQUIRE(phi::find_if_not(phi::begin(array), phi::end(array), lambda_even) ==
                       &phi::at(array, 1u));
    EXT_STATIC_REQUIRE(phi::find_if_not(phi::begin(array), phi::end(array), lambda_odd) ==
                       phi::begin(array));
    EXT_STATIC_REQUIRE(phi::find_if_not(phi::begin(array), phi::end(array), lambda_true) ==
                       phi::end(array));
    EXT_STATIC_REQUIRE(phi::find_if_not(phi::begin(array), phi::end(array), lambda_false) ==
                       phi::begin(array));
#endif

    // Noexcept
    CHECK_NOEXCEPT(phi::find_if_not(phi::begin(array), phi::end(array), eq0));
    CHECK_NOEXCEPT(phi::find_if_not(phi::begin(array), phi::end(array), eq1));
    CHECK_NOEXCEPT(phi::find_if_not(phi::begin(array), phi::end(array), eq9));
    CHECK_NOEXCEPT(phi::find_if_not(phi::begin(array), phi::end(array), eq10));
    CHECK_NOEXCEPT(phi::find_if_not(phi::begin(array), phi::end(array), even));
    CHECK_NOEXCEPT(phi::find_if_not(phi::begin(array), phi::end(array), odd));
    CHECK_NOEXCEPT(phi::find_if_not(phi::begin(array), phi::end(array), always_true));
    CHECK_NOEXCEPT(phi::find_if_not(phi::begin(array), phi::end(array), always_false));
    CHECK_NOEXCEPT(phi::find_if_not(phi::begin(array), phi::end(array), always_false_throw));

#if PHI_HAS_FEATURE_LAMBDA()
    CHECK_NOEXCEPT(phi::find_if_not(phi::begin(array), phi::end(array), lambda_eq0));
    CHECK_NOEXCEPT(phi::find_if_not(phi::begin(array), phi::end(array), lambda_eq1));
    CHECK_NOEXCEPT(phi::find_if_not(phi::begin(array), phi::end(array), lambda_eq9));
    CHECK_NOEXCEPT(phi::find_if_not(phi::begin(array), phi::end(array), lambda_eq10));
    CHECK_NOEXCEPT(phi::find_if_not(phi::begin(array), phi::end(array), lambda_even));
    CHECK_NOEXCEPT(phi::find_if_not(phi::begin(array), phi::end(array), lambda_odd));
    CHECK_NOEXCEPT(phi::find_if_not(phi::begin(array), phi::end(array), lambda_true));
    CHECK_NOEXCEPT(phi::find_if_not(phi::begin(array), phi::end(array), lambda_false));
    CHECK_NOEXCEPT(phi::find_if_not(phi::begin(array), phi::end(array), lambda_false_throw));
#endif
}

TEST_CASE("algorithm.find_if_not - phi::array")
{
    static PHI_CONSTEXPR_AND_CONST phi::array<int, 10u> array{{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}};

    // Runtime
    CHECK(phi::find_if_not(phi::begin(array), phi::end(array), eq0) == &phi::at(array, 1u));
    CHECK(phi::find_if_not(phi::begin(array), phi::end(array), eq1) == phi::begin(array));
    CHECK(phi::find_if_not(phi::begin(array), phi::end(array), eq9) == phi::begin(array));
    CHECK(phi::find_if_not(phi::begin(array), phi::end(array), eq10) == phi::begin(array));
    CHECK(phi::find_if_not(phi::begin(array), phi::end(array), even) == &phi::at(array, 1u));
    CHECK(phi::find_if_not(phi::begin(array), phi::end(array), odd) == phi::begin(array));
    CHECK(phi::find_if_not(phi::begin(array), phi::end(array), always_true) == phi::end(array));
    CHECK(phi::find_if_not(phi::begin(array), phi::end(array), always_false) == phi::begin(array));

#if PHI_HAS_FEATURE_LAMBDA()
    CHECK(phi::find_if_not(phi::begin(array), phi::end(array), lambda_eq0) == &phi::at(array, 1u));
    CHECK(phi::find_if_not(phi::begin(array), phi::end(array), lambda_eq1) == phi::begin(array));
    CHECK(phi::find_if_not(phi::begin(array), phi::end(array), lambda_eq9) == phi::begin(array));
    CHECK(phi::find_if_not(phi::begin(array), phi::end(array), lambda_eq10) == phi::begin(array));
    CHECK(phi::find_if_not(phi::begin(array), phi::end(array), lambda_even) == &phi::at(array, 1u));
    CHECK(phi::find_if_not(phi::begin(array), phi::end(array), lambda_odd) == phi::begin(array));
    CHECK(phi::find_if_not(phi::begin(array), phi::end(array), lambda_true) == phi::end(array));
    CHECK(phi::find_if_not(phi::begin(array), phi::end(array), lambda_false) == phi::begin(array));
#endif

    // Constexpr
    EXT_STATIC_REQUIRE(phi::find_if_not(phi::begin(array), phi::end(array), eq0) ==
                       &phi::at(array, 1u));
    EXT_STATIC_REQUIRE(phi::find_if_not(phi::begin(array), phi::end(array), eq1) ==
                       phi::begin(array));
    EXT_STATIC_REQUIRE(phi::find_if_not(phi::begin(array), phi::end(array), eq9) ==
                       phi::begin(array));
    EXT_STATIC_REQUIRE(phi::find_if_not(phi::begin(array), phi::end(array), eq10) ==
                       phi::begin(array));
    EXT_STATIC_REQUIRE(phi::find_if_not(phi::begin(array), phi::end(array), even) ==
                       &phi::at(array, 1u));
    EXT_STATIC_REQUIRE(phi::find_if_not(phi::begin(array), phi::end(array), odd) ==
                       phi::begin(array));
    EXT_STATIC_REQUIRE(phi::find_if_not(phi::begin(array), phi::end(array), always_true) ==
                       phi::end(array));
    EXT_STATIC_REQUIRE(phi::find_if_not(phi::begin(array), phi::end(array), always_false) ==
                       phi::begin(array));

#if PHI_HAS_FEATURE_LAMBDA() && PHI_HAS_FEATURE_CONSTEXPR_LAMBDA()
    EXT_STATIC_REQUIRE(phi::find_if_not(phi::begin(array), phi::end(array), lambda_eq0) ==
                       &phi::at(array, 1u));
    EXT_STATIC_REQUIRE(phi::find_if_not(phi::begin(array), phi::end(array), lambda_eq1) ==
                       phi::begin(array));
    EXT_STATIC_REQUIRE(phi::find_if_not(phi::begin(array), phi::end(array), lambda_eq9) ==
                       phi::begin(array));
    EXT_STATIC_REQUIRE(phi::find_if_not(phi::begin(array), phi::end(array), lambda_eq10) ==
                       phi::begin(array));
    EXT_STATIC_REQUIRE(phi::find_if_not(phi::begin(array), phi::end(array), lambda_even) ==
                       &phi::at(array, 1u));
    EXT_STATIC_REQUIRE(phi::find_if_not(phi::begin(array), phi::end(array), lambda_odd) ==
                       phi::begin(array));
    EXT_STATIC_REQUIRE(phi::find_if_not(phi::begin(array), phi::end(array), lambda_true) ==
                       phi::end(array));
    EXT_STATIC_REQUIRE(phi::find_if_not(phi::begin(array), phi::end(array), lambda_false) ==
                       phi::begin(array));
#endif

    // Noexcept
    CHECK_NOEXCEPT(phi::find_if_not(phi::begin(array), phi::end(array), eq0));
    CHECK_NOEXCEPT(phi::find_if_not(phi::begin(array), phi::end(array), eq1));
    CHECK_NOEXCEPT(phi::find_if_not(phi::begin(array), phi::end(array), eq9));
    CHECK_NOEXCEPT(phi::find_if_not(phi::begin(array), phi::end(array), eq10));
    CHECK_NOEXCEPT(phi::find_if_not(phi::begin(array), phi::end(array), even));
    CHECK_NOEXCEPT(phi::find_if_not(phi::begin(array), phi::end(array), odd));
    CHECK_NOEXCEPT(phi::find_if_not(phi::begin(array), phi::end(array), always_true));
    CHECK_NOEXCEPT(phi::find_if_not(phi::begin(array), phi::end(array), always_false));
    CHECK_NOEXCEPT(phi::find_if_not(phi::begin(array), phi::end(array), always_false_throw));

#if PHI_HAS_FEATURE_LAMBDA()
    CHECK_NOEXCEPT(phi::find_if_not(phi::begin(array), phi::end(array), lambda_eq0));
    CHECK_NOEXCEPT(phi::find_if_not(phi::begin(array), phi::end(array), lambda_eq1));
    CHECK_NOEXCEPT(phi::find_if_not(phi::begin(array), phi::end(array), lambda_eq9));
    CHECK_NOEXCEPT(phi::find_if_not(phi::begin(array), phi::end(array), lambda_eq10));
    CHECK_NOEXCEPT(phi::find_if_not(phi::begin(array), phi::end(array), lambda_even));
    CHECK_NOEXCEPT(phi::find_if_not(phi::begin(array), phi::end(array), lambda_odd));
    CHECK_NOEXCEPT(phi::find_if_not(phi::begin(array), phi::end(array), lambda_true));
    CHECK_NOEXCEPT(phi::find_if_not(phi::begin(array), phi::end(array), lambda_false));
    CHECK_NOEXCEPT(phi::find_if_not(phi::begin(array), phi::end(array), lambda_false_throw));
#endif
}
