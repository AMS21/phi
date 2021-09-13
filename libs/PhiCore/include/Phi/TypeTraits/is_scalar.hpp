#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_SCALAR_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_SCALAR_HPP

#include "Phi/PhiConfig.hpp"

#include "Phi/CompilerSupport/Features.hpp"
#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/Config/Compiler.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"
#include "Phi/TypeTraits/is_arithmetic.hpp"
#include "Phi/TypeTraits/is_enum.hpp"
#include "Phi/TypeTraits/is_member_pointer.hpp"
#include "Phi/TypeTraits/is_null_pointer.hpp"
#include "Phi/TypeTraits/is_pointer.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_HAS_INTRINSIC_IS_SCALAR() && PHI_HAS_KEYWORD(__is_scalar)

template <typename TypeT>
struct is_scalar : public bool_constant<__is_scalar(TypeT)>
{};

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_scalar_v = __is_scalar(TypeT);

#else

template <typename TypeT>
struct is_scalar
    : bool_constant<is_arithmetic_v<TypeT> || is_enum_v<TypeT> || is_pointer_v<TypeT> ||
                    is_member_pointer_v<TypeT> || is_null_pointer_v<TypeT>>
{};

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_scalar_v = is_scalar<TypeT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_SCALAR_HPP
