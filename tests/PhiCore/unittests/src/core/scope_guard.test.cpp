#include <phi/test/test_macros.hpp>

#include <phi/compiler_support/features.hpp>
#include <phi/core/scope_guard.hpp>
#include <functional>

void increment(int& val)
{
    val += 1;
}

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
static int global_value = 0;

void set_global_to_zero()
{
    global_value = 0;
}

#if PHI_HAS_FEATURE_CLASS_TEMPLATE_ARGUMENT_DEDUCTION()
TEST_CASE("scope_guard lambda", "[Core][scope_guard]")
{
    int value = 3;
    CHECK(value == 3);
    {
        phi::scope_guard guard([&value]() { value = 7; });
        CHECK(value == 3);
    }
    CHECK(value == 7);
}

TEST_CASE("scope_guard const lvalue lambda", "[Core][scope_guard]")
{
    int value = 0;
    CHECK(value == 0);
    {
        const auto       const_lvalue_lambda = [&value]() { increment(value); };
        phi::scope_guard guard(const_lvalue_lambda);
        CHECK(value == 0);
    }
    CHECK(value == 1);
}

TEST_CASE("scope_guard mutable lvalue lambda", "[Core][scope_guard]")
{
    int value = 0;
    CHECK(value == 0);
    {
        auto             mutable_lvalue_lambda = [&value]() { increment(value); };
        phi::scope_guard guard(mutable_lvalue_lambda);
        CHECK(value == 0);
    }
    CHECK(value == 1);
}

TEST_CASE("scope_guard bind", "[Core][scope_guard]")
{
    int value = 0;
    CHECK(value == 0);
    {
        phi::scope_guard guard(
                std::bind(&increment, std::ref(value))); // NOLINT(modernize-avoid-bind)
        CHECK(value == 0);
    }
    CHECK(value == 1);
}

TEST_CASE("scope_guard function pointer", "[Core][scope_guard]")
{
    global_value = 42;
    CHECK(global_value == 42);
    {
        phi::scope_guard guard(&set_global_to_zero);
        CHECK(global_value == 42);
    }

    // NOTE: Emcc 3.1.14 fails this test, which is obviously a compiler bug and is only present in this exact version
#    if PHI_COMPILER_IS(EMCC) && PHI_COMPILER_VERSION(EMCC) == PHI_VERSION_CREATE(3, 1, 14)
    SKIP_CHECK();
#    else
    CHECK(global_value == 0);
#    endif
}
#endif

TEST_CASE("make_scope_guard lambda", "[Core][scope_guard][make_scope_guard]")
{
    int value = 3;
    CHECK(value == 3);
    {
        auto guard = phi::make_scope_guard([&value]() { value = 7; });
        CHECK(value == 3);
    }
    CHECK(value == 7);
}

TEST_CASE("make_scope_guard const lvalue lambda", "[Core][scope_guard][make_scope_guard]")
{
    int value = 0;
    CHECK(value == 0);
    {
        const auto const_lvalue_lambda = [&value]() { increment(value); };
        auto       guard               = phi::make_scope_guard(const_lvalue_lambda);
        CHECK(value == 0);
    }
    CHECK(value == 1);
}

TEST_CASE("make_scope_guard mutable lvalue lambda", "[Core][scope_guard][make_scope_guard]")
{
    int value = 0;
    CHECK(value == 0);
    {
        auto mutable_lvalue_lambda = [&value]() { increment(value); };
        auto guard                 = phi::make_scope_guard(mutable_lvalue_lambda);
        CHECK(value == 0);
    }
    CHECK(value == 1);
}

TEST_CASE("make_scope_guard bind", "[Core][scope_guard][make_scope_guard]")
{
    int value = 0;
    CHECK(value == 0);
    {
        auto guard = phi::make_scope_guard(
                std::bind(&increment, std::ref(value))); // NOLINT(modernize-avoid-bind)
        CHECK(value == 0);
    }
    CHECK(value == 1);
}

TEST_CASE("make_scope_guard function pointer", "[Core][scope_guard][make_scope_guard]")
{
    global_value = 42;
    CHECK(global_value == 42);
    {
        auto guard = phi::make_scope_guard(&set_global_to_zero);
        CHECK(global_value == 42);
    }

    // NOTE: Emcc 3.1.14 fails this test, which is obviously a compiler bug and is only present in this exact version
#if PHI_COMPILER_IS(EMCC) && PHI_COMPILER_VERSION(EMCC) == PHI_VERSION_CREATE(3, 1, 14)
    SKIP_CHECK();
#else
    CHECK(global_value == 0);
#endif
}

/* armed_scope_guard */

#if PHI_HAS_FEATURE_CLASS_TEMPLATE_ARGUMENT_DEDUCTION()
TEST_CASE("armed_scope_guard default", "[Core][armed_scope_guard]")
{
    int value = 0;
    CHECK(value == 0);
    {
        phi::armed_scope_guard guard([&value] { value = 17; });

        CHECK(guard.is_armed());
        CHECK(value == 0);
    }
    CHECK(value == 17);
}

TEST_CASE("armed_scope_guard disarm", "[Core][armed_scope_guard]")
{
    int value = 0;
    CHECK(value == 0);
    {
        phi::armed_scope_guard guard([&value] { value = 21; });

        CHECK(guard.is_armed());
        guard.disarm();
        CHECK_FALSE(guard.is_armed());

        CHECK(value == 0);
    }
    CHECK(value == 0);
}

TEST_CASE("armed_scope_guard rearm", "[Core][armed_scope_guard]")
{
    int value = 0;
    CHECK(value == 0);
    {
        phi::armed_scope_guard guard([&value] { value = 21; });

        guard.rearm();

        CHECK(guard.is_armed());
        CHECK(value == 0);
    }
    CHECK(value == 21);

    value = 0;
    {
        phi::armed_scope_guard guard([&value] { value = 21; });

        guard.disarm();
        guard.rearm();

        CHECK(guard.is_armed());
        CHECK(value == 0);
    }
    CHECK(value == 21);
}
#endif

TEST_CASE("make_armed_scope_guard default", "[Core][armed_scope_guard][make_armed_scope_guard]")
{
    int value = 0;
    CHECK(value == 0);
    {
        auto guard = phi::make_armed_scope_guard([&value] { value = 17; });

        CHECK(guard.is_armed());
        CHECK(value == 0);
    }
    CHECK(value == 17);
}

TEST_CASE("make_armed_scope_guard disarm", "[Core][armed_scope_guard][make_armed_scope_guard]")
{
    int value = 0;
    CHECK(value == 0);
    {
        auto guard = phi::make_armed_scope_guard([&value] { value = 21; });

        CHECK(guard.is_armed());
        guard.disarm();
        CHECK_FALSE(guard.is_armed());

        CHECK(value == 0);
    }
    CHECK(value == 0);
}

TEST_CASE("make_armed_scope_guard rearm", "[Core][armed_scope_guard][make_armed_scope_guard]")
{
    int value = 0;
    CHECK(value == 0);
    {
        auto guard = phi::make_armed_scope_guard([&value] { value = 21; });

        guard.rearm();

        CHECK(guard.is_armed());
        CHECK(value == 0);
    }
    CHECK(value == 21);

    value = 0;
    {
        auto guard = phi::make_armed_scope_guard([&value] { value = 21; });

        guard.disarm();
        guard.rearm();

        CHECK(guard.is_armed());
        CHECK(value == 0);
    }
    CHECK(value == 21);
}
