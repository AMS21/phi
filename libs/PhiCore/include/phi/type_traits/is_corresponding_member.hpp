#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_CORRESPONDING_MEMBER_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_CORRESPONDING_MEMBER_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/intrinsics/is_corresponding_member.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include "phi/compiler_support/noexcept.hpp"

#if PHI_SUPPORTS_IS_CORRESPONDING_MEMBER()

#    define PHI_HAS_WORKING_IS_CORRESPONDING_MEMBER() 1

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename LhsT, typename RhsT, typename LhsMemberT, typename RhsMemberT>
PHI_NODISCARD PHI_CONSTEXPR bool is_corresponding_member(LhsMemberT LhsT::* lhs,
                                                         RhsMemberT RhsT::* rhs) PHI_NOEXCEPT
{
    return PHI_IS_CORRESPONDING_MEMBER(lhs, rhs);
}

#else

#    include "phi/compiler_support/unused.hpp"
#    include "phi/type_traits/false_t.hpp"

#    define PHI_HAS_WORKING_IS_CORRESPONDING_MEMBER() 0

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename LhsT, typename RhsT, typename LhsMemberT, typename RhsMemberT>
PHI_NODISCARD PHI_CONSTEXPR bool is_corresponding_member(LhsMemberT LhsT::* lhs,
                                                         RhsMemberT RhsT::* rhs) PHI_NOEXCEPT
{
    static_assert(false_t<LhsT>::value, "phi::is_corresponding_member requires compiler support");
    PHI_UNUSED_PARAMETER(lhs);
    PHI_UNUSED_PARAMETER(rhs);

    return false;
}

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_CORRESPONDING_MEMBER_HPP
