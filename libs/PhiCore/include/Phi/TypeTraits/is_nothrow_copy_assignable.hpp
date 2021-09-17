#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_NOTHROW_COPY_ASSIGNABLE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_NOTHROW_COPY_ASSIGNABLE_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/add_const.hpp"
#include "Phi/TypeTraits/add_lvalue_reference.hpp"
#include "Phi/TypeTraits/is_nothrow_assignable.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_nothrow_copy_assignable
    : public is_nothrow_assignable<add_lvalue_reference_t<TypeT>,
                                   add_lvalue_reference_t<add_const_t<TypeT>>>
{};

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_nothrow_copy_assignable_v =
        is_nothrow_copy_assignable<TypeT>::value;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_NOTHROW_COPY_ASSIGNABLE_HPP
