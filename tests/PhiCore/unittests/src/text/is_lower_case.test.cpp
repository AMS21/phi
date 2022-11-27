#include "phi/test/test_macros.hpp"

#include <phi/text/is_lower_case.hpp>

PHI_EXTERNAL_HEADERS_BEGIN()
#include <cctype>
PHI_EXTERNAL_HEADERS_END()

void test_is_lower_case(const char character) noexcept
{
    CHECK(phi::is_lower_case(character));
    CHECK(std::islower(character));
    CHECK_NOEXCEPT(phi::is_lower_case(character));
}

void test_is_not_lower_case(const char character) noexcept
{
    CHECK_FALSE(phi::is_lower_case(character));
    CHECK_FALSE(std::islower(character));
    CHECK_NOEXCEPT(phi::is_lower_case(character));
}

TEST_CASE("is_lower_case")
{
    for (char character{0}; character <= 96; ++character)
    {
        test_is_not_lower_case(character);
    }

    for (char character{97}; character <= 122; ++character)
    {
        test_is_lower_case(character);
    }

    for (char character{123}; character <= 126; ++character)
    {
        test_is_not_lower_case(character);
    }

    test_is_not_lower_case(127);
}
