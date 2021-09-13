#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_MEMBER_FUNCTION_POINTER_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_MEMBER_FUNCTION_POINTER_HPP

#include "Phi/PhiConfig.hpp"

#include "Phi/CompilerSupport/Features.hpp"
#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"
#include "Phi/TypeTraits/is_function.hpp"
#include "Phi/TypeTraits/remove_cv.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_HAS_INTRINSIC_IS_MEMBER_FUNCTION_POINTER()

template <typename TypeT>
struct is_member_function_pointer : public bool_constant<__is_member_function_pointer(TypeT)>
{};

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_member_function_pointer_v =
        __is_member_function_pointer(TypeT);

#else

namespace detail
{
    template <typename TypeT>
    struct is_member_function_pointer_impl : false_type
    {};

    template <typename TypeT, typename OtherT>
    struct is_member_function_pointer_impl<TypeT OtherT::*> : is_function<TypeT>
    {};
} // namespace detail

template <typename TypeT>
struct is_member_function_pointer
    : public detail::is_member_function_pointer_impl<remove_cv_t<TypeT>>
{};

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_member_function_pointer_v =
        is_member_function_pointer<TypeT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif //  INCG_PHI_CORE_TYPE_TRAITS_IS_MEMBER_FUNCTION_POINTER_HPP
