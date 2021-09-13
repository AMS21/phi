#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_SAME_RCV_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_SAME_RCV_HPP

#include "Phi/PhiConfig.hpp"

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/is_same.hpp"
#include "Phi/TypeTraits/remove_cv.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename LhsT, typename RhsT>
struct is_same_rcv : public is_same<remove_cv_t<LhsT>, remove_cv_t<RhsT>>
{};

template <typename LhsT, typename RhsT>
PHI_INLINE_VARIABLE constexpr bool is_same_rcv_v = is_same_rcv<LhsT, RhsT>::value;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_SAME_RCV_HPP
