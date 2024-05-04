#ifndef INCG_PHI_CORE_POINTER_TRAITS_HPP
#define INCG_PHI_CORE_POINTER_TRAITS_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/noexcept.hpp"
#include "phi/compiler_support/warning.hpp"
#include "phi/core/address_of.hpp"
#include "phi/core/ptrdiff_t.hpp"
#include "phi/type_traits/conditional.hpp"
#include "phi/type_traits/detail/nat.hpp"
#include "phi/type_traits/has_difference_type.hpp"
#include "phi/type_traits/has_element_type.hpp"
#include "phi/type_traits/integral_constant.hpp"
#include "phi/type_traits/is_void.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    template <typename PointerT, bool = has_element_type<PointerT>::value>
    struct pointer_traits_element_type;

    template <typename PointerT>
    struct pointer_traits_element_type<PointerT, true>
    {
        using type = typename PointerT::element_type;
    };

    template <template <typename, typename...> typename FancyPointerT, typename TypeT,
              typename... ArgsT>
    struct pointer_traits_element_type<FancyPointerT<TypeT, ArgsT...>, true>
    {
        using type = typename FancyPointerT<TypeT, ArgsT...>::element_type;
    };

    template <template <typename, typename...> typename FancyPointerT, typename TypeT,
              typename... ArgsT>
    struct pointer_traits_element_type<FancyPointerT<TypeT, ArgsT...>, false>
    {
        using type = TypeT;
    };

    template <typename PointerT, bool = has_difference_type<PointerT>::value>
    struct pointer_traits_difference_type
    {
        using type = ptrdiff_t;
    };

    template <typename PointerT>
    struct pointer_traits_difference_type<PointerT, true>
    {
        using type = typename PointerT::difference_type;
    };

    template <typename TypeT, typename OtherT>
    struct has_rebind
    {
    private:
        template <typename Type2T>
        static false_type test(...);

        template <typename Type2T>
        static true_type test(typename Type2T::template rebind<OtherT>* = 0);

    public:
        PHI_CLANG_SUPPRESS_WARNING_WITH_PUSH("-Wzero-as-null-pointer-constant")

        static PHI_CONSTEXPR_AND_CONST bool value = decltype(test<TypeT>(0))::value;

        PHI_CLANG_SUPPRESS_WARNING_POP()
    };

    template <typename TypeT, typename OtherT, bool = has_rebind<TypeT, OtherT>::value>
    struct pointer_traits_rebind
    {
#if PHI_CPP_STANDARD_IS_ATLEAST(11)
        using type = typename TypeT::template rebind<OtherT>;
#else
        using type = typename TypeT::template rebind<OtherT>::other;
#endif
    };

    template <template <typename, typename...> typename FancyPointerT, typename TypeT,
              typename... ArgsT, typename OtherT>
    struct pointer_traits_rebind<FancyPointerT<TypeT, ArgsT...>, OtherT, true>
    {
#if PHI_CPP_STANDARD_IS_ATLEAST(11)
        using type = typename FancyPointerT<TypeT, ArgsT...>::template rebind<OtherT>;
#else
        using type = typename FancyPointerT<TypeT, ArgsT...>::template rebind<OtherT>::other;
#endif
    };

    template <template <typename, typename...> typename FancyPointerT, typename TypeT,
              typename... ArgsT, typename OtherT>
    struct pointer_traits_rebind<FancyPointerT<TypeT, ArgsT...>, OtherT, false>
    {
        using type = FancyPointerT<OtherT, ArgsT...>;
    };
} // namespace detail

template <typename PointerT>
struct pointer_traits
{
    using this_type       = pointer_traits<PointerT>;
    using pointer         = PointerT;
    using difference_type = typename detail::pointer_traits_difference_type<pointer>::type;
    using element_type    = typename detail::pointer_traits_element_type<pointer>::type;

#if PHI_CPP_STANDARD_IS_ATLEAST(11)
    template <typename OtherT>
    using rebind = typename detail::pointer_traits_rebind<pointer, OtherT>::type;
#else
    template <typename OtherT>
    struct rebind
    {
        using other = typename detail::pointer_traits_rebind<pointer, OtherT>::type;
    };
#endif

public:
    static PHI_CONSTEXPR pointer
    pointer_to(conditional_t<is_void<element_type>::value, nat, element_type>& ptr) PHI_NOEXCEPT
    {
        return pointer::pointer_to(ptr);
    }
};

template <typename TypeT>
struct pointer_traits<TypeT*>
{
    using this_type       = pointer_traits<TypeT*>;
    using pointer         = TypeT*;
    using difference_type = ptrdiff_t;
    using element_type    = TypeT;

#if PHI_CPP_STANDARD_IS_ATLEAST(11)
    template <typename OtherT>
    using rebind = OtherT*;
#else
    template <typename OtherT>
    struct rebind
    {
        using other = OtherT*;
    };
#endif

public:
    static PHI_CONSTEXPR pointer
    pointer_to(conditional_t<is_void<element_type>::value, nat, element_type>& ptr) PHI_NOEXCEPT
    {
        return address_of(ptr);
    }
};

#if PHI_CPP_STANDARD_IS_ATLEAST(11)

template <typename FromT, typename ToT>
using rebind_pointer_t = typename pointer_traits<FromT>::template rebind<ToT>;

#else

template <typename FromT, typename ToT>
using rebind_pointer_t = typename pointer_traits<FromT>::template rebind<ToT>::other;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_POINTER_TRAITS_HPP
