#ifndef INCG_PHI_CORE_TYPE_TRAITS_REMOVE_REFERENCE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_REMOVE_REFERENCE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/features.hpp"
#include "phi/compiler_support/intrinsics/remove_reference.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_SUPPORTS_REMOVE_REFERENCE()

template <typename TypeT>
struct remove_reference
{
    using type = PHI_REMOVE_REFERENCE(TypeT);
};

#    if PHI_HAS_FEATURE_ALIAS_TEMPLATES()

template <typename TypeT>
using remove_reference_t = PHI_REMOVE_REFERENCE(TypeT);

#    endif

#else

template <typename TypeT>
struct remove_reference
{
    using type = TypeT;
};

template <typename TypeT>
struct remove_reference<TypeT&>
{
    using type = TypeT;
};

#    if PHI_HAS_FEATURE_RVALUE_REFERENCES()

template <typename TypeT>
struct remove_reference<TypeT&&>
{
    using type = TypeT;
};

#    endif

#    if PHI_HAS_FEATURE_ALIAS_TEMPLATES()

template <typename TypeT>
using remove_reference_t = typename remove_reference<TypeT>::type;

#    endif

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_REMOVE_REFERENCE_HPP
