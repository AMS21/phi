#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_COPY_ASSIGNABLE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_COPY_ASSIGNABLE_HPP

#include "Phi/PhiConfig.hpp"

#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/add_const.hpp"
#include "Phi/TypeTraits/add_lvalue_reference.hpp"
#include "Phi/TypeTraits/is_assignable.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_copy_assignable : public is_assignable<add_lvalue_reference_t<TypeT>,
                                                 add_lvalue_reference_t<add_const_t<TypeT>>>
{};

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_copy_assignable_v = is_copy_assignable<TypeT>::value;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_COPY_ASSIGNABLE_HPP
