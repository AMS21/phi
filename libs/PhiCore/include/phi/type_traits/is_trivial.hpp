#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_TRIVIAL_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_TRIVIAL_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/inline_variables.hpp"
#include "phi/compiler_support/intrinsics/is_trivial.hpp"
#include "phi/type_traits/integral_constant.hpp"
#include "phi/type_traits/is_trivially_copyable.hpp"
#include "phi/type_traits/is_trivially_default_constructible.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_SUPPORTS_IS_TRIVIAL()

template <typename TypeT>
struct is_trivial : public bool_constant<PHI_IS_TRIVIAL(TypeT)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_trivial_v = PHI_IS_TRIVIAL(TypeT);

#    endif

#else

template <typename TypeT>
struct is_trivial : public bool_constant<is_trivially_copyable_v<TypeT> &&
                                         is_trivially_default_constructible_v<TypeT>>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_trivial_v = is_trivial<TypeT>::value;

#    endif

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_TRIVIAL_HPP