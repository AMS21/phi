#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_FLOATING_POINT_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_FLOATING_POINT_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits//integral_constant.hpp"
#include "Phi/TypeTraits/is_safe_floating_point.hpp"
#include "Phi/TypeTraits/is_unsafe_floating_point.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_floating_point
    : public bool_constant<is_safe_floating_point_v<TypeT> || is_unsafe_floating_point_v<TypeT>>
{};

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_floating_point_v = is_floating_point<TypeT>::value;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_FLOATING_POINT_HPP
