#ifndef INCG_PHI_CORE_SCOPE_GUARD_HPP
#define INCG_PHI_CORE_SCOPE_GUARD_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/features.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include "phi/compiler_support/noexcept.hpp"
#include "phi/core/boolean.hpp"
#include "phi/core/forward.hpp"
#include "phi/core/move.hpp"
#include "phi/type_traits/is_const.hpp"
#include "phi/type_traits/is_reference.hpp"
#include "phi/type_traits/is_volatile.hpp"
#include "phi/type_traits/remove_cvref.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename ActionT>
class scope_guard
{
private:
    static_assert(!is_reference<ActionT>::value && !is_const<ActionT>::value &&
                          !is_volatile<ActionT>::value,
                  "phi::scope_guard should store its callable by value");

public:
    using this_type   = scope_guard<ActionT>;
    using action_type = ActionT;

    PHI_CONSTEXPR explicit scope_guard(ActionT action) PHI_NOEXCEPT : m_Action(phi::move(action))
    {}

#if PHI_HAS_FEATURE_GUARANTEED_COPY_ELISION()
    scope_guard(scope_guard&&)      = delete;
    scope_guard(const scope_guard&) = delete;

    scope_guard& operator=(const scope_guard&) = delete;
    scope_guard& operator=(scope_guard&&)      = delete;
#else
    scope_guard(scope_guard&&)      = default;
    scope_guard(const scope_guard&) = default;

    scope_guard& operator=(const scope_guard&) = default;
    scope_guard& operator=(scope_guard&&)      = default;
#endif

    PHI_CONSTEXPR_DESTRUCTOR ~scope_guard()
    {
        m_Action();
    }

private:
    ActionT m_Action;
};

#if PHI_HAS_FEATURE_DEDUCTION_GUIDES()
template <typename TypeT>
scope_guard(TypeT) -> scope_guard<TypeT>;
#endif

template <typename ActionT>
class armed_scope_guard
{
private:
    static_assert(!is_reference<ActionT>::value && !is_const<ActionT>::value &&
                          !is_volatile<ActionT>::value,
                  "phi::armed_scope_guard should store its callable by value");

public:
    using this_type   = armed_scope_guard<ActionT>;
    using action_type = ActionT;

    PHI_CONSTEXPR explicit armed_scope_guard(ActionT action) PHI_NOEXCEPT
        : m_Action(phi::move(action)),
          m_Armed{true}
    {}

#if PHI_HAS_FEATURE_GUARANTEED_COPY_ELISION()
    armed_scope_guard(armed_scope_guard&&)      = delete;
    armed_scope_guard(const armed_scope_guard&) = delete;

    armed_scope_guard& operator=(const armed_scope_guard&) = delete;
    armed_scope_guard& operator=(armed_scope_guard&&)      = delete;
#else
    armed_scope_guard(armed_scope_guard&&)      = default;
    armed_scope_guard(const armed_scope_guard&) = default;

    armed_scope_guard& operator=(const armed_scope_guard&) = default;
    armed_scope_guard& operator=(armed_scope_guard&&)      = default;
#endif

    PHI_CONSTEXPR_DESTRUCTOR ~armed_scope_guard()
    {
        if (m_Armed)
        {
            m_Action();
        }
    }

    PHI_EXTENDED_CONSTEXPR void disarm() PHI_NOEXCEPT
    {
        m_Armed = false;
    }

    PHI_EXTENDED_CONSTEXPR void rearm() PHI_NOEXCEPT
    {
        m_Armed = true;
    }

    PHI_NODISCARD PHI_CONSTEXPR boolean is_armed() const PHI_NOEXCEPT
    {
        return m_Armed;
    }

private:
    ActionT m_Action;
    boolean m_Armed;
};

#if PHI_HAS_FEATURE_DEDUCTION_GUIDES()
template <typename TypeT>
armed_scope_guard(TypeT) -> armed_scope_guard<TypeT>;
#endif

template <typename ActionT>
PHI_NODISCARD PHI_CONSTEXPR scope_guard<remove_cvref_t<ActionT>> make_scope_guard(ActionT&& action)
        PHI_NOEXCEPT
{
    return scope_guard<remove_cvref_t<ActionT>>(phi::forward<ActionT>(action));
}

template <typename ActionT>
PHI_NODISCARD PHI_CONSTEXPR armed_scope_guard<remove_cvref_t<ActionT>> make_armed_scope_guard(
        ActionT&& action) PHI_NOEXCEPT
{
    return armed_scope_guard<remove_cvref_t<ActionT>>(phi::forward<ActionT>(action));
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_SCOPE_GUARD_HPP
