#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_FUNCTION_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_FUNCTION_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"
#include "Phi/TypeTraits/is_const.hpp"
#include "Phi/TypeTraits/is_reference.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_function : public bool_constant<!is_const_v<const TypeT> && !is_reference_v<TypeT>>
{};

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_function_v = is_function<TypeT>::value;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_FUNCTION_HPP
