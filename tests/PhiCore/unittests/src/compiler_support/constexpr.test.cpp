#include <phi/test/test_macros.hpp>

#include <phi/algorithm/string_equals.hpp>
#include <phi/compiler_support/constexpr.hpp>
#include <phi/compiler_support/warning.hpp>
#include <phi/preprocessor/stringify.hpp>

PHI_MSVC_SUPPRESS_WARNING_PUSH()
PHI_MSVC_SUPPRESS_WARNING(
        4003) // not enough actual parameters for macro 'identifier' - https://learn.microsoft.com/cpp/error-messages/compiler-warnings/compiler-warning-level-1-c4003

TEST_CASE("PHI_CONSTEXPR")
{
#if PHI_HAS_FEATURE_CONSTEXPR()
    STATIC_REQUIRE(phi::string_equals(PHI_STRINGIFY(PHI_CONSTEXPR), "constexpr"));
#else
    STATIC_REQUIRE(phi::string_equals("" PHI_STRINGIFY(PHI_CONSTEXPR), ""));
#endif
}

TEST_CASE("PHI_CONSTEXPR_OR_CONST")
{
#if PHI_HAS_FEATURE_CONSTEXPR()
    STATIC_REQUIRE(phi::string_equals(PHI_STRINGIFY(PHI_CONSTEXPR_OR_CONST), "constexpr"));
#else
    STATIC_REQUIRE(phi::string_equals(PHI_STRINGIFY(PHI_CONSTEXPR_OR_CONST), "const"));
#endif
}

TEST_CASE("PHI_CONSTEXPR_OR_INLINE")
{
#if PHI_HAS_FEATURE_CONSTEXPR()
    STATIC_REQUIRE(phi::string_equals(PHI_STRINGIFY(PHI_CONSTEXPR_OR_INLINE), "constexpr"));
#else
    STATIC_REQUIRE(phi::string_equals(PHI_STRINGIFY(PHI_CONSTEXPR_OR_INLINE), "inline"));
#endif
}

TEST_CASE("PHI_CONSTEXPR_OR_STATIC")
{
#if PHI_HAS_FEATURE_CONSTEXPR()
    STATIC_REQUIRE(phi::string_equals(PHI_STRINGIFY(PHI_CONSTEXPR_OR_STATIC), "constexpr"));
#else
    STATIC_REQUIRE(phi::string_equals(PHI_STRINGIFY(PHI_CONSTEXPR_OR_STATIC), "static"));
#endif
}

TEST_CASE("PHI_CONSTEXPR_OR")
{
#if PHI_HAS_FEATURE_CONSTEXPR()
    STATIC_REQUIRE(phi::string_equals(PHI_STRINGIFY(PHI_CONSTEXPR_OR(blub)), "constexpr"));
#else
    STATIC_REQUIRE(phi::string_equals(PHI_STRINGIFY(PHI_CONSTEXPR_OR(blub)), "blub"));
#endif
}

TEST_CASE("PHI_CONSTEXPR_IF")
{
#if PHI_HAS_FEATURE_CONSTEXPR()
    STATIC_REQUIRE(phi::string_equals("" PHI_STRINGIFY(PHI_CONSTEXPR_IF(0)), ""));
    STATIC_REQUIRE(phi::string_equals(PHI_STRINGIFY(PHI_CONSTEXPR_IF(1)), "constexpr"));
#else
    STATIC_REQUIRE(phi::string_equals("" PHI_STRINGIFY(PHI_CONSTEXPR_IF(0)), ""));
    STATIC_REQUIRE(phi::string_equals("" PHI_STRINGIFY(PHI_CONSTEXPR_IF(1)), ""));
#endif
}

TEST_CASE("PHI_EXTENDED_CONSTEXPR")
{
#if PHI_HAS_FEATURE_EXTENDED_CONSTEXPR()
    STATIC_REQUIRE(phi::string_equals(PHI_STRINGIFY(PHI_EXTENDED_CONSTEXPR), "constexpr"));
#else
    STATIC_REQUIRE(phi::string_equals(PHI_STRINGIFY(PHI_EXTENDED_CONSTEXPR), ""));
#endif
}

TEST_CASE("PHI_EXTENDED_CONSTEXPR_OR_CONST")
{
#if PHI_HAS_FEATURE_EXTENDED_CONSTEXPR()
    STATIC_REQUIRE(phi::string_equals(PHI_STRINGIFY(PHI_EXTENDED_CONSTEXPR_OR_CONST), "constexpr"));
#else
    STATIC_REQUIRE(phi::string_equals(PHI_STRINGIFY(PHI_EXTENDED_CONSTEXPR_OR_CONST), "const"));
#endif
}

TEST_CASE("PHI_EXTENDED_CONSTEXPR_OR_INLINE")
{
#if PHI_HAS_FEATURE_EXTENDED_CONSTEXPR()
    STATIC_REQUIRE(
            phi::string_equals(PHI_STRINGIFY(PHI_EXTENDED_CONSTEXPR_OR_INLINE), "constexpr"));
#else
    STATIC_REQUIRE(phi::string_equals(PHI_STRINGIFY(PHI_EXTENDED_CONSTEXPR_OR_INLINE), "inline"));
#endif
}

TEST_CASE("PHI_EXTENDED_CONSTEXPR_OR_STATIC")
{
#if PHI_HAS_FEATURE_EXTENDED_CONSTEXPR()
    STATIC_REQUIRE(
            phi::string_equals(PHI_STRINGIFY(PHI_EXTENDED_CONSTEXPR_OR_STATIC), "constexpr"));
#else
    STATIC_REQUIRE(phi::string_equals(PHI_STRINGIFY(PHI_EXTENDED_CONSTEXPR_OR_STATIC), "static"));
#endif
}

TEST_CASE("PHI_EXTENDED_CONSTEXPR_OR")
{
#if PHI_HAS_FEATURE_EXTENDED_CONSTEXPR()
    STATIC_REQUIRE(phi::string_equals(PHI_STRINGIFY(PHI_EXTENDED_CONSTEXPR_OR(blub)), "constexpr"));
#else
    STATIC_REQUIRE(phi::string_equals(PHI_STRINGIFY(PHI_EXTENDED_CONSTEXPR_OR(blub)), "blub"));
#endif
}

TEST_CASE("PHI_EXTENDED_CONSTEXPR_IF")
{
#if PHI_HAS_FEATURE_EXTENDED_CONSTEXPR()
    STATIC_REQUIRE(phi::string_equals("" PHI_STRINGIFY(PHI_EXTENDED_CONSTEXPR_IF(0)), ""));
    STATIC_REQUIRE(phi::string_equals(PHI_STRINGIFY(PHI_EXTENDED_CONSTEXPR_IF(1)), "constexpr"));
#else
    STATIC_REQUIRE(phi::string_equals("" PHI_STRINGIFY(PHI_EXTENDED_CONSTEXPR_IF(0)), ""));
    STATIC_REQUIRE(phi::string_equals("" PHI_STRINGIFY(PHI_EXTENDED_CONSTEXPR_IF(1)), ""));
#endif
}

TEST_CASE("PHI_EXTENDED_CONSTEXPR_CLASS")
{
#if PHI_HAS_FEATURE_EXTENDED_CONSTEXPR() && PHI_HAS_DR1684()
    STATIC_REQUIRE(phi::string_equals(PHI_STRINGIFY(PHI_EXTENDED_CONSTEXPR_CLASS), "constexpr"));
#else
    STATIC_REQUIRE(phi::string_equals("" PHI_STRINGIFY(PHI_EXTENDED_CONSTEXPR_CLASS), ""));
#endif
}

TEST_CASE("PHI_CONSTEXPR_AND_CONST")
{
#if PHI_HAS_FEATURE_EXTENDED_CONSTEXPR()
    STATIC_REQUIRE(phi::string_equals(PHI_STRINGIFY(PHI_CONSTEXPR_AND_CONST), "constexpr const"));
#elif PHI_HAS_FEATURE_CONSTEXPR()
    STATIC_REQUIRE(phi::string_equals(PHI_STRINGIFY(PHI_CONSTEXPR_AND_CONST), "constexpr"));
#else
    STATIC_REQUIRE(phi::string_equals("" PHI_STRINGIFY(PHI_CONSTEXPR_AND_CONST), ""));
#endif
}

TEST_CASE("PHI_CONSTEXPR_AND_CONST_OR")
{
#if PHI_HAS_FEATURE_EXTENDED_CONSTEXPR()
    STATIC_REQUIRE(
            phi::string_equals(PHI_STRINGIFY(PHI_CONSTEXPR_AND_CONST_OR(blub)), "constexpr const"));
#elif PHI_HAS_FEATURE_CONSTEXPR()
    STATIC_REQUIRE(
            phi::string_equals(PHI_STRINGIFY(PHI_CONSTEXPR_AND_CONST_OR(blub)), "constexpr"));
#else
    STATIC_REQUIRE(phi::string_equals(PHI_STRINGIFY(PHI_CONSTEXPR_AND_CONST_OR(blub)), "blub"));
#endif
}

TEST_CASE("PHI_EXTENDED_CONSTEXPR_AND_CONST")
{
#if PHI_HAS_FEATURE_EXTENDED_CONSTEXPR()
    STATIC_REQUIRE(
            phi::string_equals(PHI_STRINGIFY(PHI_EXTENDED_CONSTEXPR_AND_CONST), "constexpr const"));
#elif PHI_HAS_FEATURE_CONSTEXPR()
    STATIC_REQUIRE(phi::string_equals("" PHI_STRINGIFY(PHI_EXTENDED_CONSTEXPR_AND_CONST), ""));
#else
    STATIC_REQUIRE(phi::string_equals("" PHI_STRINGIFY(PHI_EXTENDED_CONSTEXPR_AND_CONST), ""));
#endif
}

TEST_CASE("PHI_EXTENDED_CONSTEXPR_AND_CONST_OR")
{
#if PHI_HAS_FEATURE_EXTENDED_CONSTEXPR()
    STATIC_REQUIRE(phi::string_equals(PHI_STRINGIFY(PHI_EXTENDED_CONSTEXPR_AND_CONST_OR(blub)),
                                      "constexpr const"));
#elif PHI_HAS_FEATURE_CONSTEXPR()
    STATIC_REQUIRE(
            phi::string_equals(PHI_STRINGIFY(PHI_EXTENDED_CONSTEXPR_AND_CONST_OR(blub)), "blub"));
#else
    STATIC_REQUIRE(
            phi::string_equals(PHI_STRINGIFY(PHI_EXTENDED_CONSTEXPR_AND_CONST_OR(blub)), "blub"));
#endif
}

TEST_CASE("PHI_CONSTEXPR_LAMBDA")
{
#if PHI_HAS_FEATURE_CONSTEXPR_LAMBDA()
    STATIC_REQUIRE(phi::string_equals(PHI_STRINGIFY(PHI_CONSTEXPR_LAMBDA), "constexpr"));
#else
    STATIC_REQUIRE(phi::string_equals("" PHI_STRINGIFY(PHI_CONSTEXPR_LAMBDA), ""));
#endif
}

TEST_CASE("PHI_CONSTEXPR_VIRTUAL")
{
#if PHI_HAS_FEATURE_CONSTEXPR_VIRTUAL()
    STATIC_REQUIRE(phi::string_equals(PHI_STRINGIFY(PHI_CONSTEXPR_VIRTUAL), "constexpr"));
#else
    STATIC_REQUIRE(phi::string_equals("" PHI_STRINGIFY(PHI_CONSTEXPR_VIRTUAL), ""));
#endif
}

TEST_CASE("PHI_CONSTEXPR_DESTRUCTOR")
{
#if PHI_HAS_FEATURE_CONSTEXPR_DESTRUCTOR()
    STATIC_REQUIRE(phi::string_equals(PHI_STRINGIFY(PHI_CONSTEXPR_DESTRUCTOR), "constexpr"));
#else
    STATIC_REQUIRE(phi::string_equals("" PHI_STRINGIFY(PHI_CONSTEXPR_DESTRUCTOR), ""));
#endif
}

PHI_MSVC_SUPPRESS_WARNING_POP()
