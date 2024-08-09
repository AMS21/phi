#ifndef INCG_PHI_CORE_CONTAINER_ARRAY_HPP
#define INCG_PHI_CORE_CONTAINER_ARRAY_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include "phi/compiler_support/noexcept.hpp"
#include "phi/core/boolean.hpp"
#include "phi/core/forward.hpp"
#include "phi/type_traits/conditional.hpp"
#include "phi/type_traits/detail/nat.hpp"
#include "phi/type_traits/enable_if.hpp"
#include "phi/type_traits/is_constructible.hpp"
#include "phi/type_traits/is_convertible.hpp"
#include "phi/type_traits/is_copy_assignable.hpp"
#include "phi/type_traits/is_default_constructible.hpp"
#include "phi/type_traits/is_implicitly_default_constructible.hpp"
#include "phi/type_traits/is_move_assignable.hpp"
#include "phi/type_traits/is_nothrow_copy_assignable.hpp"
#include "phi/type_traits/is_nothrow_copy_constructible.hpp"
#include "phi/type_traits/is_nothrow_default_constructible.hpp"
#include "phi/type_traits/is_nothrow_move_assignable.hpp"
#include "phi/type_traits/is_nothrow_swappable.hpp"
#include "phi/type_traits/is_swappable.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

// 22.3.2 Class template pair, http://eel.is/c++draft/pairs#pair
template <typename FirstT, typename SecondT>
class pair
{
    static PHI_CONSTEXPR_AND_CONST bool enable_implicit_default_constructor =
            is_implicitly_default_constructible<FirstT>::value &&
            is_implicitly_default_constructible<SecondT>::value;

    static PHI_CONSTEXPR_AND_CONST bool enable_explicit_default_constructor =
            is_default_constructible<FirstT>::value && is_default_constructible<SecondT>::value &&
            !enable_implicit_default_constructor;

    static PHI_CONSTEXPR_AND_CONST bool enable_nothrow_default_constructor =
            is_nothrow_default_constructible<FirstT>::value &&
            is_nothrow_default_constructible<SecondT>::value;

    static PHI_CONSTEXPR_AND_CONST bool enable_nothrow_copy_constructor =
            is_nothrow_copy_constructible<FirstT>::value &&
            is_nothrow_copy_constructible<SecondT>::value;

    template <typename OtherFirstT, typename OtherSecondT>
    static PHI_CONSTEXPR_AND_CONST bool enable_explicit_constructor =
            is_constructible<FirstT, OtherFirstT>::value &&
            is_constructible<SecondT, OtherSecondT>::value &&
            (is_not_convertible<OtherFirstT, FirstT>::value ||
             is_not_convertible<OtherSecondT, SecondT>::value);

    template <typename OtherFirstT, typename OtherSecondT>
    static PHI_CONSTEXPR_AND_CONST bool enable_implicit_constructor =
            is_constructible<FirstT, OtherFirstT>::value &&
            is_constructible<SecondT, OtherSecondT>::value &&
            is_convertible<OtherFirstT, FirstT>::value &&
            is_convertible<OtherSecondT, SecondT>::value;

public:
    using this_type   = pair<FirstT, SecondT>;
    using first_type  = FirstT;
    using second_type = SecondT;

    // Explicit default constructor
    template <typename enable_if<enable_explicit_default_constructor>::type* = nullptr>
    PHI_CONSTEXPR explicit pair() PHI_NOEXCEPT_EXPR(enable_nothrow_default_constructor)
        : first{}
        , second{}
    {}

    // Implicit default constructor
    template <typename enable_if<enable_implicit_default_constructor>::type* = nullptr>
    PHI_CONSTEXPR pair() PHI_NOEXCEPT_EXPR(enable_nothrow_default_constructor)
        : first{}
        , second{}
    {}

    // Default destructor
    ~pair() = default;

    // Default copy constructor
    pair(pair const&) = default;

    // Default move constructor
    pair(pair&&) = default;

    // Explicit copy constructor
    template <typename enable_if<
                      enable_explicit_constructor<const FirstT&, const SecondT&>>::type* = nullptr>
    PHI_CONSTEXPR explicit pair(const FirstT& first_arg, const SecondT& second_arg)
            PHI_NOEXCEPT_EXPR(enable_nothrow_copy_constructor)
        : first{first_arg}
        , second{second_arg}
    {}

    // Implicit copy constructor
    template <typename enable_if<
                      enable_implicit_constructor<const FirstT&, const SecondT&>>::type* = nullptr>
    PHI_CONSTEXPR pair(const FirstT& first_arg, const SecondT& second_arg)
            PHI_NOEXCEPT_EXPR(enable_nothrow_copy_constructor)
        : first{first_arg}
        , second{second_arg}
    {}

    // http://wg21.link/P1951
    // Explicit conversion constructor
    template <typename OtherFirstT = FirstT, typename OtherSecondT = SecondT,
              typename enable_if<enable_explicit_constructor<OtherFirstT, OtherSecondT>()>::type* =
                      nullptr>
    PHI_CONSTEXPR explicit pair(OtherFirstT&& other_first, OtherSecondT&& other_second)
            PHI_NOEXCEPT_EXPR(is_nothrow_constructible<FirstT, OtherFirstT>::value&&
                                      is_nothrow_constructible<SecondT, OtherSecondT>::value)
        : first{forward<OtherFirstT>(other_first)}
        , second{forward<OtherSecondT>(other_second)}
    {}

    // http://wg21.link/P1951
    // Implicit conversion constructor
    template <typename OtherFirstT = FirstT, typename OtherSecondT = SecondT,
              typename enable_if<enable_implicit_constructor<OtherFirstT, OtherSecondT>()>::type* =
                      nullptr>
    PHI_CONSTEXPR pair(OtherFirstT&& other_first, OtherSecondT&& other_second)
            PHI_NOEXCEPT_EXPR(is_nothrow_constructible<FirstT, OtherFirstT>::value&&
                                      is_nothrow_constructible<SecondT, OtherSecondT>::value)
        : first{forward<OtherFirstT>(other_first)}
        , second{forward<OtherSecondT>(other_second)}
    {}

    // Explicit pair conversion constructor
    template <typename OtherFirstT, typename OtherSecondT,
              typename enable_if<enable_explicit_constructor<const OtherFirstT&,
                                                             const OtherSecondT&>>::type* = nullptr>
    PHI_CONSTEXPR explicit pair(const pair<OtherFirstT, OtherSecondT>& other_pair)
            PHI_NOEXCEPT_EXPR(is_nothrow_constructible<FirstT, const OtherFirstT&>::value&&
                                      is_nothrow_constructible<SecondT, const OtherSecondT&>::value)
        : first{other_pair.first}
        , second(other_pair.second)
    {}

    // Implicit pair conversion constructor
    template <typename OtherFirstT, typename OtherSecondT,
              typename enable_if<enable_implicit_constructor<const OtherFirstT&,
                                                             const OtherSecondT&>>::type* = nullptr>
    PHI_CONSTEXPR pair(const pair<OtherFirstT, SecondT>& other_pair)
            PHI_NOEXCEPT_EXPR(is_nothrow_constructible<FirstT, const OtherFirstT&>::value&&
                                      is_nothrow_constructible<SecondT, const OtherSecondT&>::value)
        : first{other_pair.first}
        , second{other_pair.second}
    {}

    // Explicit pair conversion move constructor
    template <typename OtherFirstT, typename OtherSecondT,
              typename enable_if<enable_explicit_constructor<OtherFirstT, OtherSecondT>()>::type* =
                      nullptr>
    PHI_CONSTEXPR explicit pair(pair<OtherFirstT, OtherSecondT>&& other_pair)
            PHI_NOEXCEPT_EXPR(is_nothrow_constructible<FirstT, OtherFirstT&&>::value&&
                                      is_nothrow_constructible<SecondT, OtherSecondT&&>::value)
        : first{forward<OtherFirstT>(other_pair.first)}
        , second{forward<OtherSecondT>(other_pair.second)}
    {}

    // Implicit pair conversion move constructor
    template <typename OtherFirstT, typename OtherSecondT,
              typename enable_if<enable_implicit_constructor<OtherFirstT, OtherSecondT>()>::type* =
                      nullptr>
    PHI_CONSTEXPR pair(pair<OtherFirstT, OtherSecondT>&& other_pair)
            PHI_NOEXCEPT_EXPR(is_nothrow_constructible<FirstT, OtherFirstT&&>::value&&
                                      is_nothrow_constructible<SecondT, OtherSecondT&&>::value)
        : first{forward<OtherFirstT>(other_pair.first)}
        , second{forward<OtherSecondT>(other_pair.second)}
    {}

    pair& operator=(const pair&) = default;

    pair& operator=(pair&&) = default;

    PHI_CONSTEXPR pair& operator=(typename conditional<is_copy_assignable<FirstT>::value &&
                                                               is_copy_assignable<SecondT>::value,
                                                       pair, nat>::type const& other_pair)
            PHI_NOEXCEPT_EXPR(is_nothrow_copy_assignable<first_type>::value&&
                                      is_nothrow_copy_assignable<second_type>::value)
    {
        first  = other_pair.first;
        second = other_pair.second;

        return *this;
    }

    PHI_CONSTEXPR pair& operator=(
            typename conditional<is_move_assignable<first_type>::value &&
                                         is_move_assignable<second_type>::value,
                                 pair, nat>::type&& other_pair)
            PHI_NOEXCEPT_EXPR(is_nothrow_move_assignable<FirstT>::value&&
                                      is_nothrow_move_assignable<SecondT>::value)
    {
        first  = forward<first_type>(other_pair.first);
        second = forward<second_type>(other_pair.second);

        return *this;
    }

    PHI_CONSTEXPR void swap(pair& other_pair) PHI_NOEXCEPT_EXPR(
            is_nothrow_swappable<FirstT>::value&& is_nothrow_swappable<SecondT>::value)
    {
        using phi::swap;

        swap(first, other_pair.first);
        swap(second, other_pair.second);
    }

    PHI_CONSTEXPR void flip() PHI_NOEXCEPT_EXPR(
            is_nothrow_swappable<FirstT>::value&& is_nothrow_swappable<SecondT>::value)
    {
        using phi::swap;

        swap(first, second);
    }

    PHI_NODISCARD PHI_CONSTEXPR pair<SecondT, FirstT> as_flipped()
            PHI_NOEXCEPT_EXPR(enable_nothrow_copy_constructor)
    {
        return pair<SecondT, FirstT>(second, first);
    }

    FirstT  first;
    SecondT second;
};

// 22.3.3 Specialized algorithms, https://eel.is/c++draft/pairs#spec

template <typename FirstT, typename SecondT>
PHI_CONSTEXPR boolean operator==(const pair<FirstT, SecondT>& lhs, const pair<FirstT, SecondT>& rhs)
{
    return lhs.first == rhs.first && lhs.second == rhs.second;
}

template <typename FirstT, typename SecondT>
PHI_CONSTEXPR boolean operator!=(const pair<FirstT, SecondT>& lhs, const pair<FirstT, SecondT>& rhs)
{
    return !(lhs == rhs);
}

template <typename FirstT, typename SecondT>
PHI_CONSTEXPR boolean operator<(const pair<FirstT, SecondT>& lhs, const pair<FirstT, SecondT>& rhs)
{
    return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
}

template <typename FirstT, typename SecondT>
PHI_CONSTEXPR boolean operator>(const pair<FirstT, SecondT>& lhs, const pair<FirstT, SecondT>& rhs)
{
    return rhs < lhs;
}

template <typename FirstT, typename SecondT>
PHI_CONSTEXPR boolean operator>=(const pair<FirstT, SecondT>& lhs, const pair<FirstT, SecondT>& rhs)
{
    return !(lhs < rhs);
}

template <typename FirstT, typename SecondT>
PHI_CONSTEXPR boolean operator<=(const pair<FirstT, SecondT>& lhs, const pair<FirstT, SecondT>& rhs)
{
    return !(rhs < lhs);
}

template <typename FirstT, typename SecondT>
PHI_CONSTEXPR
        typename enable_if<is_swappable<FirstT>::value && is_swappable<SecondT>::value, void>::type
        swap(pair<FirstT, SecondT>& lhs, pair<FirstT, SecondT>& rhs) PHI_NOEXCEPT_EXPR(
                is_nothrow_swappable<FirstT>::value&& is_nothrow_swappable<SecondT>::value)
{
    lhs.swap(rhs);
}

template <typename FirstT, typename SecondT>
PHI_CONSTEXPR
        typename enable_if<is_swappable<const FirstT>::value && is_swappable<const SecondT>::value,
                           void>::type
        swap(const pair<FirstT, SecondT>& lhs, const pair<FirstT, SecondT>& rhs) PHI_NOEXCEPT_EXPR(
                is_nothrow_swappable<FirstT>::value&& is_nothrow_swappable<SecondT>::value)
{
    lhs.swap(rhs);
}

template <typename FirstT, typename SecondT>
pair<FirstT, SecondT> make_pair(FirstT lhs, SecondT rhs)
{
    return pair<FirstT, SecondT>(lhs, rhs);
}

#if PHI_HAS_FEATURE_DEDUCTION_GUIDES()
template <typename FirstTypeT, typename SecondTypeT>
pair(FirstTypeT, SecondTypeT) -> pair<FirstTypeT, SecondTypeT>;
#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_CONTAINER_ARRAY_HPP
