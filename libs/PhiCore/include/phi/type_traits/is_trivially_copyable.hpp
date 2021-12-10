#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_TRIVIALLY_COPYABLE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_TRIVIALLY_COPYABLE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/inline_variables.hpp"
#include "phi/compiler_support/intrinsics/is_trivially_copyable.hpp"
#include "phi/type_traits/false_t.hpp"
#include "phi/type_traits/integral_constant.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_SUPPORTS_IS_TRIVIALLY_COPYABLE()

template <typename TypeT>
struct is_trivially_copyable : public bool_constant<PHI_IS_TRIVIALLY_COPYABLE(TypeT)>
{};

template <typename TypeT>
struct is_not_trivially_copyable : public bool_constant<!PHI_IS_TRIVIALLY_COPYABLE(TypeT)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_trivially_copyable_v = PHI_IS_TRIVIALLY_COPYABLE(TypeT);

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_not_trivially_copyable_v = !PHI_IS_TRIVIALLY_COPYABLE(TypeT);

#    endif

#else

template <typename TypeT>
struct is_trivially_copyable : public false_type
{
    static_assert(false_t<TypeT>::value, "phi::is_trivially_copyable requires compiler support for "
                                         "instrincic __is_trivilly_copyable");
};

template <typename TypeT>
struct is_not_trivially_copyable : public false_type
{
    static_assert(false_t<TypeT>::value,
                  "phi::is_not_trivially_copyable requires compiler support for "
                  "instrincic __is_trivilly_copyable");
};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_trivially_copyable_v = is_trivially_copyable<TypeT>::value;

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_not_trivially_copyable_v =
        is_not_trivially_copyable<TypeT>::value;

#    endif

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_TRIVIALLY_COPYABLE_HPP
