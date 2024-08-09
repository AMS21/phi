#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/constexpr.hpp>
#include <phi/compiler_support/noexcept.hpp>
#include <phi/compiler_support/warning.hpp>
#include <phi/core/declval.hpp>
#include <phi/type_traits/is_same.hpp>

PHI_GCC_SUPPRESS_WARNING_PUSH()
PHI_GCC_SUPPRESS_WARNING("-Wnoexcept")

#include <phi/algorithm/swap.hpp>
#include <phi/core/scope_ptr.hpp>

struct CopyOnly
{
    // NOLINTNEXTLINE(modernize-use-equals-default)
    CopyOnly()
    {}

    // NOLINTNEXTLINE(modernize-use-equals-default)
    CopyOnly(const CopyOnly& /*other*/) PHI_NOEXCEPT
    {}

    // NOLINTNEXTLINE(bugprone-unhandled-self-assignment,modernize-use-equals-default)
    CopyOnly& operator=(const CopyOnly& /*other*/)
    {
        return *this;
    }
};

struct MoveOnly
{
    // NOLINTNEXTLINE(modernize-use-equals-default)
    MoveOnly()
    {}

    MoveOnly(MoveOnly&& /*other*/)
    {}

    MoveOnly& operator=(MoveOnly&& /*other*/) PHI_NOEXCEPT
    {
        return *this;
    }
};

struct NoexceptMoveOnly
{
    // NOLINTNEXTLINE(modernize-use-equals-default)
    NoexceptMoveOnly()
    {}

    NoexceptMoveOnly(NoexceptMoveOnly&& /*other*/) PHI_NOEXCEPT
    {}

    NoexceptMoveOnly& operator=(NoexceptMoveOnly&& /*other*/) PHI_NOEXCEPT
    {
        return *this;
    }
};

struct NotMoveConstructible
{
    NotMoveConstructible& operator=(NotMoveConstructible&& /*other*/)
    {
        return *this;
    }

    NotMoveConstructible(NotMoveConstructible&&) = delete;
};

struct NotMoveAssignable
{
    NotMoveAssignable(NotMoveAssignable&&);

private:
    NotMoveAssignable& operator=(NotMoveAssignable&&);
};

template <typename TypeT>
auto can_swap_test(int) -> decltype(phi::swap(phi::declval<TypeT>(), phi::declval<TypeT>()));

template <typename TypeT>
auto can_swap_test(...) -> phi::false_type;

template <typename TypeT>
PHI_CONSTEXPR bool can_swap()
{
    return phi::is_same<decltype(can_swap_test<TypeT>(0)), void>::value;
}

#if PHI_HAS_FEATURE_EXTENDED_CONSTEXPR()
PHI_CONSTEXPR bool test_swap_constexpr()
{
    int lhs = 1;
    int rhs = 2;
    phi::swap(lhs, rhs);
    return lhs == 2 && rhs == 1;
}
#endif

TEST_CASE("swap")
{
    {
        int lhs = 1;
        int rhs = 2;
        phi::swap(lhs, rhs);
        CHECK(lhs == 2);
        CHECK(rhs == 1);
    }

    // phi::scope_ptr
    {
        phi::scope_ptr<int> lhs(new int(1));
        phi::scope_ptr<int> rhs(new int(2));
        phi::swap(lhs, rhs);
        CHECK(*lhs == 2);
        CHECK(*rhs == 1);
    }
    {
        // test that the swap
        STATIC_REQUIRE(can_swap<CopyOnly&>());
        STATIC_REQUIRE(can_swap<MoveOnly&>());
        STATIC_REQUIRE(can_swap<NoexceptMoveOnly&>());

        STATIC_REQUIRE_FALSE(can_swap<NotMoveConstructible&>());
        STATIC_REQUIRE_FALSE(can_swap<NotMoveAssignable&>());

        CopyOnly         copy_only;
        MoveOnly         move_only;
        NoexceptMoveOnly noexcept_move_only;
        CHECK_NOT_NOEXCEPT(phi::swap(copy_only, copy_only));
        CHECK_NOT_NOEXCEPT(phi::swap(move_only, move_only));
        CHECK_NOEXCEPT(phi::swap(noexcept_move_only, noexcept_move_only));
    }

    {
        // Check that swap does not call any copy constructor
        non_copyable lhs;
        non_copyable rhs;

        phi::swap(lhs, rhs);
    }

    {
        tracked lhs;
        tracked rhs;

        phi::swap(lhs, rhs);
    }

    {
        trap_constructible lhs;
        trap_constructible rhs;

        phi::swap(lhs, rhs);
    }

    {
        trap_implicit_conversion lhs;
        trap_implicit_conversion rhs;

        phi::swap(lhs, rhs);
    }

    {
        trap_comma lhs;
        trap_comma rhs;

        phi::swap(lhs, rhs);
    }

    {
        trap_call lhs;
        trap_call rhs;

        phi::swap(lhs, rhs);
    }

    {
        trap_self_assign lhs;
        trap_self_assign rhs;

        phi::swap(lhs, rhs);
    }

    {
        trap_deref lhs;
        trap_deref rhs;

        phi::swap(lhs, rhs);
    }

    {
        trap_array_subscript lhs;
        trap_array_subscript rhs;

        phi::swap(lhs, rhs);
    }

#if PHI_HAS_FEATURE_EXTENDED_CONSTEXPR()
    STATIC_REQUIRE(test_swap_constexpr());
#endif
}

PHI_GCC_SUPPRESS_WARNING_POP()
