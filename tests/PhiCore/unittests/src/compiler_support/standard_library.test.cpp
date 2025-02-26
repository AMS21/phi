#include <phi/test/test_macros.hpp>

#include <phi/algorithm/string_equals.hpp>
#include <phi/compiler_support/standard_library.hpp>
#include <phi/preprocessor/versioning.hpp>

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

TEST_CASE("PHI_STANDARD_LIBRARY_DATE")
{
#if PHI_STANDARD_LIBRARY_LIBCXX()
    STATIC_REQUIRE(PHI_STANDARD_LIBRARY_DATE() == 0);
    STATIC_REQUIRE_FALSE(PHI_STANDARD_LIBRARY_HAS_DATE());
#elif PHI_STANDARD_LIBRARY_LIBSTDCXX()
    STATIC_REQUIRE(PHI_STANDARD_LIBRARY_DATE() > 0);
    STATIC_REQUIRE(PHI_STANDARD_LIBRARY_DATE() == __GLIBCXX__);
    STATIC_REQUIRE(PHI_STANDARD_LIBRARY_HAS_DATE());
#elif PHI_STANDARD_LIBRARY_MSVC()

#    if defined(_MSVC_STL_UPDATE)
    STATIC_REQUIRE(PHI_STANDARD_LIBRARY_DATE() > 0);
    STATIC_REQUIRE(PHI_STANDARD_LIBRARY_DATE() == _MSVC_STL_UPDATE);
    STATIC_REQUIRE(PHI_STANDARD_LIBRARY_HAS_DATE());
#    else
    STATIC_REQUIRE(PHI_STANDARD_LIBRARY_DATE() == 0);
    STATIC_REQUIRE_FALSE(PHI_STANDARD_LIBRARY_HAS_DATE());
#    endif

#else
    STATIC_REQUIRE(false, "No supported standard library found!");
#endif
}

TEST_CASE("PHI_STANDARD_LIBRARY_VERSION")
{
#if PHI_STANDARD_LIBRARY_LIBCXX()
    STATIC_REQUIRE(PHI_STANDARD_LIBRARY_VERSION_MAJOR() > 0);
    STATIC_REQUIRE(PHI_STANDARD_LIBRARY_VERSION_MINOR() >= 0);
    STATIC_REQUIRE(PHI_STANDARD_LIBRARY_VERSION_PATCH() >= 0);
    STATIC_REQUIRE(PHI_STANDARD_LIBRARY_VERSION() > 0);
#elif PHI_STANDARD_LIBRARY_LIBSTDCXX()
    // '_GLIBCXX_RELEASE' was added with gcc 7.0
#    if PHI_COMPILER_WORKAROUND(GCC, 7, 0, 0)
    STATIC_REQUIRE(PHI_STANDARD_LIBRARY_VERSION_MAJOR() > 0);
#    else
    STATIC_REQUIRE(PHI_STANDARD_LIBRARY_VERSION_MAJOR() == 0);
#    endif
    STATIC_REQUIRE(PHI_STANDARD_LIBRARY_VERSION_MINOR() == 0);
    STATIC_REQUIRE(PHI_STANDARD_LIBRARY_VERSION_PATCH() == 0);
#    if PHI_COMPILER_WORKAROUND(GCC, 7, 0, 0)
    STATIC_REQUIRE(PHI_STANDARD_LIBRARY_VERSION() > 0);
#    else
    STATIC_REQUIRE(PHI_STANDARD_LIBRARY_VERSION() == 0);
#    endif
#elif PHI_STANDARD_LIBRARY_MSVC()
    STATIC_REQUIRE(PHI_STANDARD_LIBRARY_VERSION_MAJOR() > 0);
    STATIC_REQUIRE(PHI_STANDARD_LIBRARY_VERSION_MINOR() >= 0);
    STATIC_REQUIRE(PHI_STANDARD_LIBRARY_VERSION_PATCH() == 0);
    STATIC_REQUIRE(PHI_STANDARD_LIBRARY_VERSION() > 0);
#else
    STATIC_REQUIRE(false && "No supported standard library found!");
#endif

    STATIC_REQUIRE(PHI_STANDARD_LIBRARY_VERSION() ==
                   PHI_VERSION_CREATE(PHI_STANDARD_LIBRARY_VERSION_MAJOR(),
                                      PHI_STANDARD_LIBRARY_VERSION_MINOR(),
                                      PHI_STANDARD_LIBRARY_VERSION_PATCH()));
}
