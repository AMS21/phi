#include <phi/test/test_macros.hpp>

#include <phi/compiler_support/defect_report.hpp>

TEST_CASE("defect_report")
{
    // DR 1684
#if PHI_HAS_DR1684()
    STATIC_REQUIRE(PHI_HAS_DR1684());
#else
    STATIC_REQUIRE_FALSE(PHI_HAS_DR1684());
#endif
}
