#include "phi/test/test_macros.hpp"

#include "phi/compiler_support/cpp_standard.hpp"

constexpr bool is_any_standard()
{
    return PHI_CPP_STANDARD() == PHI_CPLUSPLUS_98() || PHI_CPP_STANDARD() == PHI_CPLUSPLUS_11() ||
           PHI_CPP_STANDARD() == PHI_CPLUSPLUS_14() || PHI_CPP_STANDARD() == PHI_CPLUSPLUS_17() ||
           PHI_CPP_STANDARD() == PHI_CPLUSPLUS_20() || PHI_CPP_STANDARD() == PHI_CPLUSPLUS_23();
}

TEST_CASE("PHI_CPLUSPLUS_X")
{
    STATIC_REQUIRE(PHI_CPLUSPLUS_98());
    STATIC_REQUIRE(PHI_CPLUSPLUS_11());
    STATIC_REQUIRE(PHI_CPLUSPLUS_14());
    STATIC_REQUIRE(PHI_CPLUSPLUS_17());
    STATIC_REQUIRE(PHI_CPLUSPLUS_20());
    STATIC_REQUIRE(PHI_CPLUSPLUS_23());

    STATIC_REQUIRE(PHI_CPLUSPLUS_LATEST());
    STATIC_REQUIRE(PHI_CPLUSPLUS_LATEST() == PHI_CPLUSPLUS_23());
}

TEST_CASE("PHI_CPP_STANDARD")
{
    STATIC_REQUIRE(is_any_standard());
    STATIC_REQUIRE(PHI_CPP_STANDARD());
}
