#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_DESTRUCTIBLE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_DESTRUCTIBLE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/inline_variables.hpp"
#include "phi/compiler_support/intrinsics/is_destructible.hpp"
#include "phi/type_traits/integral_constant.hpp"

#if PHI_SUPPORTS_IS_DESTRUCTIBLE()

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
struct is_destructible : public integral_constant<bool, PHI_IS_DESTRUCTIBLE(TypeT)>
{};

template <typename TypeT>
struct is_not_destructible : public integral_constant<bool, !PHI_IS_DESTRUCTIBLE(TypeT)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_destructible_v = PHI_IS_DESTRUCTIBLE(TypeT);

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_not_destructible_v = !PHI_IS_DESTRUCTIBLE(TypeT);

#    endif

#else

#    include "phi/core/declval.hpp"
#    include "phi/type_traits/detail/yes_no_type.hpp"
#    include "phi/type_traits/is_function.hpp"
#    include "phi/type_traits/is_reference.hpp"
#    include "phi/type_traits/remove_all_extents.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    template <typename>
    struct is_destructible_apply
    {
        using type = int;
    };

    template <typename TypeT>
    struct is_destructor_wellformed
    {
        template <typename Type1T>
        static yes_type test(
                typename is_destructible_apply<decltype(declval<Type1T&>().~Type1T())>::type);

        template <typename Type1T>
        static no_type test(...);

        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-vararg)
        static PHI_CONSTEXPR_AND_CONST bool value = sizeof(test<TypeT>(12)) == sizeof_yes_type;
    };

    template <typename TypeT, bool>
    struct destructible_impl;

    template <typename TypeT>
    struct destructible_impl<TypeT, false>
        : public integral_constant<
                  bool, is_destructor_wellformed<typename remove_all_extents<TypeT>::type>::value>
    {};

    template <typename TypeT>
    struct destructible_impl<TypeT, true> : public true_type
    {};

    template <typename TypeT, bool>
    struct destructible_false;

    template <typename TypeT>
    struct destructible_false<TypeT, false>
        : public destructible_impl<TypeT, is_reference<TypeT>::value>
    {};

    template <typename TypeT>
    struct destructible_false<TypeT, true> : public false_type
    {};
} // namespace detail

template <typename TypeT>
struct is_destructible : public detail::destructible_false<TypeT, is_function<TypeT>::value>
{};

template <typename TypeT>
struct is_destructible<TypeT[]> : public false_type
{};

template <>
struct is_destructible<void> : public false_type
{};

template <typename TypeT>
struct is_not_destructible : public integral_constant<bool, !is_destructible<TypeT>::value>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_destructible_v = is_destructible<TypeT>::value;

template <typename TypeT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_not_destructible_v = is_not_destructible<TypeT>::value;

#    endif

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_DESTRUCTIBLE_HPP
