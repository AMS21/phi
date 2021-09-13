#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_SAME_RCVREF_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_SAME_RCVREF_HPP

#include "Phi/PhiConfig.hpp"

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/is_same.hpp"
#include "Phi/TypeTraits/remove_cvref.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename LhsT, typename RhsT>
struct is_same_rcvref : public is_same<remove_cvref_t<LhsT>, remove_cvref_t<RhsT>>
{};

template <typename LhsT, typename RhsT>
PHI_INLINE_VARIABLE constexpr bool is_same_rcvref_v = is_same_rcvref<LhsT, RhsT>::value;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_SAME_RCVREF_HPP
