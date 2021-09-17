#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_UNBOUNDED_ARRAY_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_UNBOUNDED_ARRAY_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_unbounded_array : public false_type
{};

template <typename TypeT>
struct is_unbounded_array<TypeT[]> : public true_type
{};

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_unbounded_array_v = is_unbounded_array<TypeT>::value;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_UNBOUNDED_ARRAY_HPP
