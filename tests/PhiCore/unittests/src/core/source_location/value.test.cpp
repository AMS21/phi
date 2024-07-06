#include <phi/test/test_macros.hpp>

#include "constexpr_helper.hpp"
#include <phi/algorithm/string_equals.hpp>
#include <phi/compiler_support/compiler.hpp>
#include <phi/compiler_support/constexpr.hpp>
#include <phi/compiler_support/intrinsics/source_location.hpp>
#include <phi/container/string_view.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/source_location.hpp>
#include <phi/type_traits/is_nothrow_default_constructible.hpp>
#include <phi/type_traits/is_nothrow_destructible.hpp>
#include <phi/type_traits/is_nothrow_move_assignable.hpp>
#include <phi/type_traits/is_nothrow_move_constructible.hpp>
#include <phi/type_traits/is_nothrow_swappable.hpp>
#include <phi/type_traits/is_trivially_assignable.hpp>
#include <phi/type_traits/is_trivially_constructible.hpp>
#include <phi/type_traits/is_trivially_copy_assignable.hpp>
#include <phi/type_traits/is_trivially_copy_constructible.hpp>
#include <phi/type_traits/is_trivially_destructible.hpp>
#include <phi/type_traits/is_trivially_move_assignable.hpp>
#include <phi/type_traits/is_trivially_move_constructible.hpp>

#if PHI_SUPPORTS_BUILTIN_LINE()
#    define TEST_CURRENT() phi::source_location::current()
#else
#    define TEST_CURRENT() PHI_SOURCE_LOCATION_CURRENT()
#endif

// NOTE: MSVC 2019 for some reasons seems to be broken with the line tests

TEST_CASE("source_location")
{
    SECTION("traits")
    {
#if PHI_HAS_WORKING_IS_NOTHROW_DEFAULT_CONSTRUCTIBLE()
        STATIC_REQUIRE(phi::is_nothrow_default_constructible<phi::source_location>::value);
#endif
        STATIC_REQUIRE(phi::is_nothrow_move_assignable<phi::source_location>::value);
        STATIC_REQUIRE(phi::is_nothrow_move_constructible<phi::source_location>::value);
        STATIC_REQUIRE(phi::is_nothrow_swappable<phi::source_location>::value);
        STATIC_REQUIRE(phi::is_nothrow_destructible<phi::source_location>::value);

        // trivial
#if PHI_HAS_WORKING_IS_TRIVIALLY_CONSTRUCTIBLE()
        STATIC_REQUIRE(phi::is_trivially_copy_constructible<phi::source_location>::value);
        STATIC_REQUIRE(phi::is_trivially_move_constructible<phi::source_location>::value);
#endif
#if PHI_HAS_WORKING_IS_TRIVIALLY_ASSIGNABLE()
        STATIC_REQUIRE(phi::is_trivially_copy_assignable<phi::source_location>::value);
        STATIC_REQUIRE(phi::is_trivially_move_assignable<phi::source_location>::value);
#endif
#if PHI_HAS_WORKING_IS_TRIVIALLY_DESTRUCTIBLE()
        STATIC_REQUIRE(phi::is_trivially_destructible<phi::source_location>::value);
#endif

        CHECK_SAME_TYPE(phi::source_location::this_type, phi::source_location);
    }

    SECTION("default constructor")
    {
        phi::source_location loc;

        CHECK(phi::string_equals(loc.file_name(), ""));
        CHECK(loc.file_name_view().is_empty());
        CHECK(phi::string_equals(loc.function_name(), ""));
        CHECK(loc.function_name_view().is_empty());
        CHECK(loc.line() == 0);
        CHECK(loc.column() == 0);
    }

    SECTION("explicit constructor")
    {
        phi::source_location loc("my_file.cpp", "test_function", 42, 21);

        CHECK(phi::string_equals(loc.file_name(), "my_file.cpp"));
        CHECK(loc.file_name_view() == "my_file.cpp");
        CHECK(phi::string_equals(loc.function_name(), "test_function"));
        CHECK(loc.function_name_view() == "test_function");
        CHECK(loc.line() == 42);
        CHECK(loc.column() == 21);
    }

#if PHI_SUPPORTS_BUILTIN_LINE() && PHI_COMPILER_WORKAROUND(MSVC, 19, 30, 0)
    SECTION("current")
    {
        phi::source_location loc = phi::source_location::current();

        //CHECK(phi::string_equals(loc.file_name(), "source_location.test.cpp"));
        //CHECK(phi::string_equals(loc.function_name(), "phi_test_function"));
#    if PHI_COMPILER_WORKAROUND(MSVC, 19, 30, 0)
        CHECK(loc.line() == __LINE__ - 5);
#    else
        SKIP_CHECK();
#    endif

#    if PHI_SUPPORTS_BUILTIN_COLUMN()
        CHECK(loc.column() > 0);
#    else
        CHECK(loc.column() == 0);
#    endif
    }
#endif

    SECTION("noexcept")
    {
        CHECK_NOEXCEPT(phi::source_location());
        CHECK_NOEXCEPT(phi::source_location("file.cpp", "function", 3u, 1u));
#if PHI_SUPPORTS_BUILTIN_LINE()
        CHECK_NOEXCEPT(phi::source_location::current());
#endif
        CHECK_NOEXCEPT(phi::source_location().line());
        CHECK_NOEXCEPT(phi::source_location().column());
        CHECK_NOEXCEPT(phi::source_location().file_name());
        CHECK_NOEXCEPT(phi::source_location().file_name_view());
        CHECK_NOEXCEPT(phi::source_location().function_name());
        CHECK_NOEXCEPT(phi::source_location().function_name_view());
    }

    SECTION("Constexpr")
    {
        PHI_CONSTEXPR phi::source_location location =
                phi::source_location{"file.cpp", "function", 3u, 1u};

        EXT_STATIC_REQUIRE(phi::string_equals(location.file_name(), "file.cpp"));
        //EXT_STATIC_REQUIRE(l.file_name_view() == "file.cpp");
        EXT_STATIC_REQUIRE(phi::string_equals(location.function_name(), "function"));
        //EXT_STATIC_REQUIRE(l.function_name_view() == "function");
        STATIC_REQUIRE(location.line() == 3u);
        STATIC_REQUIRE(location.column() == 1u);
    }

    SECTION("PHI_SOURCE_LOCATION_CURRENT")
    {
        phi::source_location loc = PHI_SOURCE_LOCATION_CURRENT();

        //CHECK(phi::string_equals(loc.file_name(), "source_location.test.cpp"));
        //CHECK(phi::string_equals(loc.function_name(), "phi_test_function"));
#if PHI_COMPILER_WORKAROUND(MSVC, 19, 30, 0)
        CHECK(loc.line() == __LINE__ - 5);
#else
        SKIP_CHECK();
#endif

#if PHI_SUPPORTS_BUILTIN_COLUMN()
        CHECK(loc.column() > 0);
#else
        CHECK(loc.column() == 0);
#endif
    }
}

static phi::source_location f()
{
    return TEST_CURRENT();
}

TEST_CASE("test f")
{
    phi::source_location f_loc = f();

    //CHECK(phi::string_equals(f_loc.file_name(), "source_location.test.cpp"));
    CHECK(phi::string_equals(f_loc.function_name(), "f"));

#if PHI_COMPILER_WORKAROUND(MSVC, 19, 30, 0)
    CHECK(f_loc.line() == __LINE__ - 11);
#else
    SKIP_CHECK();
#endif

#if PHI_SUPPORTS_BUILTIN_COLUMN()
    CHECK(f_loc.column() > 0);
#else
    CHECK(f_loc.column() == 0);
#endif
}

// NOTE: Messing with the line or current file creates problems with coverage generation
#if !defined(PHI_CONFIG_COVERAGE_BUILD)

static phi::source_location g()
{
#    line 1000
    return TEST_CURRENT();
}

TEST_CASE("test g")
{
    phi::source_location g_loc = g();

    //CHECK(phi::string_equals(g_loc.file_name(), "source_location.test.cpp"));
    CHECK(phi::string_equals(g_loc.function_name(), "g"));
    CHECK(g_loc.function_name_view() == "g");

#    if PHI_COMPILER_WORKAROUND(MSVC, 19, 30, 0)
    CHECK(g_loc.line() == 1000);
#    else
    SKIP_CHECK();
#    endif

#    if PHI_SUPPORTS_BUILTIN_COLUMN()
    CHECK(g_loc.column() > 0);
#    else
    CHECK(g_loc.column() == 0);
#    endif
}

static phi::source_location h()
{
#    line 1000 "test_file.cpp"
    return TEST_CURRENT();
}

TEST_CASE("test h")
{
    phi::source_location h_loc = h();

#    if PHI_COMPILER_IS_NOT(MSVC)
    CHECK(phi::string_equals(h_loc.file_name(), "test_file.cpp"));
    CHECK(h_loc.file_name_view() == "test_file.cpp");
#    else
    SKIP_CHECK();
#    endif
    CHECK(phi::string_equals(h_loc.function_name(), "h"));
    CHECK(h_loc.function_name_view() == "h");

#    if PHI_COMPILER_WORKAROUND(MSVC, 19, 30, 0)
    CHECK(h_loc.line() == 1000);
#    else
    SKIP_CHECK();
#    endif

#    if PHI_SUPPORTS_BUILTIN_COLUMN()
    CHECK(h_loc.column() > 0);
#    else
    CHECK(h_loc.column() == 0);
#    endif
}

#endif
