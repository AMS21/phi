#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_DESTRUCTIBLE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_DESTRUCTIBLE_HPP

#include "Phi/PhiConfig.hpp"

#include "Phi/CompilerSupport/Features.hpp"
#include "Phi/CompilerSupport/InlineVariables.hpp"
#include "Phi/Core/Declval.hpp"
#include "Phi/TypeTraits/integral_constant.hpp"
#include "Phi/TypeTraits/internals.hpp"
#include "Phi/TypeTraits/is_function.hpp"
#include "Phi/TypeTraits/is_reference.hpp"
#include "Phi/TypeTraits/remove_all_extents.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_HAS_INTRINSIC_IS_DESTRUCTIBLE()

template <typename TypeT>
struct is_destructible : bool_constant<__is_destructible(TypeT)>
{};

template <typename TypeT>
PHI_INLINE_VARIABLE constexpr bool is_destructible_v = __is_destructible(TypeT);

#else

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
        static char test(
                typename is_destructible_apply<decltype(declval<Type1T&>().~Type1T())>::type);

        template <typename Type1T>
        static two test(...);

        static const bool value = sizeof(test<TypeT>(12)) == sizeof(char);
    };

    template <typename TypeT, bool>
    struct destructible_impl;

    template <typename TypeT>
    struct destructible_impl<TypeT, false>
        : public bool_constant<
                  is_destructor_wellformed<typename remove_all_extents<TypeT>::type>::value>
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
PHI_INLINE_VARIABLE constexpr bool is_destructible_v = is_destructible<TypeT>::value;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_DESTRUCTIBLE_HPP
