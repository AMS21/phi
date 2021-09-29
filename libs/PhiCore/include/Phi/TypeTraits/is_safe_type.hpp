#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_SAFE_TYPE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_SAFE_TYPE_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"
#include "Phi/TypeTraits/is_safe_bool.hpp"
#include "Phi/TypeTraits/is_safe_floating_point.hpp"
#include "Phi/TypeTraits/is_safe_integer.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_safe_type
    : public bool_constant<is_safe_bool<TypeT>::value || is_safe_floating_point<TypeT>::value ||
                           is_safe_integer<TypeT>::value>
{};

#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_safe_type_v = is_safe_type<TypeT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_SAFE_TYPE_HPP
