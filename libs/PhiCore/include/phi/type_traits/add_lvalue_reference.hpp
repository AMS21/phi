#ifndef INCG_PHI_CORE_TYPE_TRAITS_ADD_LVALUE_REFERENCE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_ADD_LVALUE_REFERENCE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/features.hpp"
#include "phi/compiler_support/intrinsics/add_lvalue_reference.hpp"

#if PHI_SUPPORTS_ADD_LVALUE_REFERENCE()

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct add_lvalue_reference
{
    using type = PHI_ADD_LVALUE_REFERENCE(TypeT);
};

#    if PHI_HAS_FEATURE_ALIAS_TEMPLATES()

template <typename TypeT>
using add_lvalue_reference_t = PHI_ADD_LVALUE_REFERENCE(TypeT);

#    endif

#else

#    include "phi/type_traits/is_referenceable.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    template <typename TypeT, bool = is_referenceable<TypeT>::value>
    struct add_lvalue_reference_impl
    {
        using type = TypeT;
    };

    template <typename TypeT>
    struct add_lvalue_reference_impl<TypeT, true>
    {
        using type = TypeT&;
    };
} // namespace detail

template <typename TypeT>
struct add_lvalue_reference
{
    using type = typename detail::add_lvalue_reference_impl<TypeT>::type;
};

#    if PHI_HAS_FEATURE_ALIAS_TEMPLATES()

template <typename TypeT>
using add_lvalue_reference_t = typename add_lvalue_reference<TypeT>::type;

#    endif

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_ADD_LVALUE_REFERENCE_HPP
