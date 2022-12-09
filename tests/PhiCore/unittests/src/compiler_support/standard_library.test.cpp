#include <phi/test/test_macros.hpp>

#include <phi/algorithm/string_equals.hpp>
#include <phi/compiler_support/standard_library.hpp>

TEST_CASE("PHI_STANDARD_LIBRARY_LIBCXX")
{
#if PHI_STANDARD_LIBRARY_LIBCXX()
    STATIC_REQUIRE(PHI_STANDARD_LIBRARY_LIBCXX());
    STATIC_REQUIRE_FALSE(PHI_STANDARD_LIBRARY_LIBSTDCXX());
    STATIC_REQUIRE_FALSE(PHI_STANDARD_LIBRARY_MSVC());
#else
    STATIC_REQUIRE_FALSE(PHI_STANDARD_LIBRARY_LIBCXX());
#endif
}

TEST_CASE("PHI_STANDARD_LIBRARY_LIBSTDCXX")
{
#if PHI_STANDARD_LIBRARY_LIBSTDCXX()
    STATIC_REQUIRE_FALSE(PHI_STANDARD_LIBRARY_LIBCXX());
    STATIC_REQUIRE(PHI_STANDARD_LIBRARY_LIBSTDCXX());
    STATIC_REQUIRE_FALSE(PHI_STANDARD_LIBRARY_MSVC());
#else
    STATIC_REQUIRE_FALSE(PHI_STANDARD_LIBRARY_LIBSTDCXX());
#endif
}

TEST_CASE("PHI_STANDARD_LIBRARY_MSVC")
{
#if PHI_STANDARD_LIBRARY_MSVC()
    STATIC_REQUIRE_FALSE(PHI_STANDARD_LIBRARY_LIBCXX());
    STATIC_REQUIRE_FALSE(PHI_STANDARD_LIBRARY_LIBSTDCXX());
    STATIC_REQUIRE(PHI_STANDARD_LIBRARY_MSVC());
#else
    STATIC_REQUIRE_FALSE(PHI_STANDARD_LIBRARY_MSVC());
#endif
}

TEST_CASE("PHI_STANDARD_LIBRARY_NAME")
{
#if PHI_STANDARD_LIBRARY_LIBCXX()
    STATIC_REQUIRE(phi::string_equals(PHI_STANDARD_LIBRARY_NAME(), "libc++"));
#elif PHI_STANDARD_LIBRARY_LIBSTDCXX()
    STATIC_REQUIRE(phi::string_equals(PHI_STANDARD_LIBRARY_NAME(), "libstdc++"));
#elif PHI_STANDARD_LIBRARY_MSVC()
    STATIC_REQUIRE(phi::string_equals(PHI_STANDARD_LIBRARY_NAME(), "msvc-stl"));
#else
    STATIC_REQUIRE(false, "No supported standard library found!");
#endif
}
