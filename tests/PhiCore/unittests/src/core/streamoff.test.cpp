#include <phi/test/test_macros.hpp>

#include <phi/core/streamoff.hpp>
#include <phi/type_traits/is_signed.hpp>
#include <phi/type_traits/is_unsafe_integral.hpp>
#include <ios>

TEST_CASE("core.streamoff")
{
    STATIC_REQUIRE(phi::is_unsafe_integral<phi::streamoff>::value);
    STATIC_REQUIRE(phi::is_signed<phi::streamoff>::value);

#if defined(_NEWLIB_VERSION)
    CHECK_SAME_TYPE(phi::streamoff, long int);
#elif defined(__INT64_TYPE__)
    CHECK_SAME_TYPE(phi::streamoff, __INT64_TYPE__);
#else
    CHECK_SAME_TYPE(phi::streamoff, long long);
#endif

    // Standard compatibility
    CHECK_SAME_TYPE(std::streamoff, phi::streamoff);
    STATIC_REQUIRE(sizeof(phi::streamoff) == sizeof(std::streamoff));
}
