#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_POINTER_INTERCONVERTIBLE_WITH_CLASS_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_POINTER_INTERCONVERTIBLE_WITH_CLASS_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/intrinsics/is_pointer_interconvertible_with_class.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include "phi/compiler_support/noexcept.hpp"

#if PHI_SUPPORTS_IS_POINTER_INTERCONVERTIBLE_WITH_CLASS()

#    define PHI_HAS_WORKING_IS_POINTER_INTERCONVERTIBLE_WITH_CLASS() 1

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT, typename MemberT>
PHI_NODISCARD PHI_CONSTEXPR bool is_pointer_interconvertible_with_class(
        MemberT TypeT::* member_pointer) PHI_NOEXCEPT
{
    return PHI_IS_POINTER_INTERCONVERTIBLE_WITH_CLASS(member_pointer);
}

#else

#    include "phi/compiler_support/unused.hpp"
#    include "phi/type_traits/false_t.hpp"

#    define PHI_HAS_WORKING_IS_POINTER_INTERCONVERTIBLE_WITH_CLASS() 0

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT, typename MemberT>
PHI_NODISCARD PHI_CONSTEXPR bool is_pointer_interconvertible_with_class(
        MemberT TypeT::* member_pointer) PHI_NOEXCEPT
{
    static_assert(false_t<TypeT>::value,
                  "phi::is_pointer_interconvertible_with_class requires compiler support");
    PHI_UNUSED_PARAMETER(member_pointer);

    return false;
}

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_POINTER_INTERCONVERTIBLE_WITH_CLASS_HPP
