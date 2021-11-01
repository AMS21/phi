#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_BOUNDED_ARRAY_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_BOUNDED_ARRAY_HPP

#include "Phi/PhiConfig.hpp"

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_bounded_array : false_type
{};

template <typename TypeT, std::size_t SizeT>
struct is_bounded_array<TypeT[SizeT]> : true_type
{};

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_bounded_array_v = is_bounded_array<TypeT>::value;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_BOUNDED_ARRAY_HPP