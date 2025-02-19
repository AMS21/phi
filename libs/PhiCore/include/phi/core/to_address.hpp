#ifndef PHI_CORE_TO_ADDRESS_HPP
#define PHI_CORE_TO_ADDRESS_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/noexcept.hpp"
#include "phi/core/declval.hpp"
#include "phi/core/pointer_traits.hpp"
#include "phi/type_traits/conjunction.hpp"
#include "phi/type_traits/decay.hpp"
#include "phi/type_traits/enable_if.hpp"
#include "phi/type_traits/is_class.hpp"
#include "phi/type_traits/is_function.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    template <typename TypeT>
    PHI_CONSTEXPR TypeT* to_address_impl(TypeT* pointer) PHI_NOEXCEPT
    {
        static_assert(is_not_function<TypeT>::value,
                      "phi::detail::to_address_impl: TypeT must not be a function type");
        return pointer;
    }

    template <typename PointerT, typename = void>
    struct has_to_address : public false_type
    {};

    template <typename PointerT>
    struct has_to_address<PointerT, decltype((void)pointer_traits<PointerT>::to_address(
                                            declval<const PointerT&>()))> : public true_type
    {};

    template <typename PointerT, typename = void>
    struct pointer_has_operator_arrow : public false_type
    {};

    template <typename PointerT>
    struct pointer_has_operator_arrow<PointerT,
                                      decltype((void)declval<const PointerT&>().operator->())>
        : public true_type
    {};

    template <typename PointerT>
    struct is_fancy_pointer
    {
        static PHI_CONSTEXPR_AND_CONST bool value =
                pointer_has_operator_arrow<PointerT>::value || has_to_address<PointerT>::value;
    };

    template <typename PointerT, typename = void>
    struct to_address_impl_helper;

    // enable_if is needed here to avoid instantiating checks for fancy pointers on raw pointers
    template <typename PointerT, typename = enable_if_t<conjunction<
                                         is_class<PointerT>, is_fancy_pointer<PointerT>>::value>>
    PHI_CONSTEXPR decay_t<
            decltype(to_address_impl_helper<PointerT>::call(declval<const PointerT&>()))>
    to_address_impl(const PointerT& pointer) PHI_NOEXCEPT
    {
        return to_address_impl_helper<PointerT>::call(pointer);
    }

    template <typename PointerT, typename>
    struct to_address_impl_helper
    {
        static PHI_CONSTEXPR decltype(to_address_impl(declval<const PointerT&>().operator->()))
        call(const PointerT& pointer) PHI_NOEXCEPT
        {
            return to_address_impl(pointer.operator->());
        }
    };

    template <typename PointerT>
    struct to_address_impl_helper<PointerT, decltype((void)pointer_traits<PointerT>::to_address(
                                                    declval<const PointerT&>()))>
    {
        static PHI_CONSTEXPR decltype(pointer_traits<PointerT>::to_address(
                declval<const PointerT&>()))
        call(const PointerT& pointer) PHI_NOEXCEPT
        {
            return pointer_traits<PointerT>::to_address(pointer);
        }
    };
} // namespace detail

template <typename TypeT>
PHI_CONSTEXPR auto to_address(TypeT* pointer) PHI_NOEXCEPT
{
    return detail::to_address_impl(pointer);
}

template <typename PointerT>
PHI_CONSTEXPR auto to_address(const PointerT& pointer) PHI_NOEXCEPT
        -> decltype(detail::to_address_impl(pointer))
{
    return detail::to_address_impl(pointer);
}

DETAIL_PHI_END_NAMESPACE()

#endif // PHI_CORE_TO_ADDRESS_HPP
