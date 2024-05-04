#ifndef INCG_PHI_CORE_MONITOR_HPP
#define INCG_PHI_CORE_MONITOR_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/extended_attributes.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include "phi/compiler_support/noexcept.hpp"
#include "phi/compiler_support/warning.hpp"
#include "phi/core/forward.hpp"
#include "phi/core/invoke.hpp"
#include "phi/core/move.hpp"
#include "phi/type_traits/is_nothrow_invocable.hpp"
#include <mutex>

// TODO: Add annotations instead of suppressing the warnings
PHI_CLANG_SUPPRESS_WARNING_PUSH()
PHI_CLANG_SUPPRESS_WARNING("-Wthread-safety-negative")

DETAIL_PHI_BEGIN_NAMESPACE()

/*!
* \brief Stores shared data in its private section.
*        Allows different threads to operate on the shared data
*        by passing in callables that operate on the shared data.
**/
template <typename SharedDataT>
class monitor final
{
private:
    struct monitor_helper
    {
        PHI_CONSTEXPR explicit monitor_helper(const monitor* monitor_arg)
                PHI_NOEXCEPT PHI_ATTRIBUTE_NONNULL : monitor{monitor_arg},
                                                     lock{monitor->m_Mutex}
        {}

        PHI_NODISCARD PHI_ATTRIBUTE_RETURNS_NONNULL PHI_CONSTEXPR SharedDataT* operator->()
                PHI_NOEXCEPT
        {
            return &monitor->m_SharedData;
        }

        PHI_NODISCARD PHI_ATTRIBUTE_RETURNS_NONNULL PHI_CONSTEXPR const SharedDataT* operator->()
                const PHI_NOEXCEPT
        {
            return &monitor->m_SharedData;
        }

        const monitor*               monitor;
        std::unique_lock<std::mutex> lock;
    };

public:
    using this_type    = monitor<SharedDataT>;
    using element_type = SharedDataT;

    template <typename... ArgsT>
    PHI_CONSTEXPR monitor(ArgsT&&... args) PHI_NOEXCEPT : m_SharedData{forward<ArgsT>(args)...}
    {}

    /*!
    * \brief Creates a monitor.
    * \param shared_data the data to be protected by the monitor.
    **/
    PHI_CONSTEXPR explicit monitor(SharedDataT shared_data) PHI_NOEXCEPT
        : m_SharedData{move(shared_data)}
    {}

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR monitor_helper operator->() PHI_NOEXCEPT
    {
        return monitor_helper(this);
    }

    // NOLINTNEXTLINE(readability-const-return-type)
    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const monitor_helper operator->() const PHI_NOEXCEPT
    {
        return monitor_helper(this);
    }

#if PHI_HAS_FEATURE_DECLTYPE_AUTO()
    /*!
    * \brief Receives a callable and invokes that callable by passing the
    *        shared data to it. The call itself is protected by a mutex.
    * \param callable The callable to be used to operate on the shared data.
    * \return The result of calling the callable passed in with the shared data
    *         as the callable's call operator's argument.
    **/
    template <typename CallableT>
    auto operator()(CallableT&& callable) const
            PHI_NOEXCEPT_EXPR(is_nothrow_invocable<CallableT, SharedDataT>::value)
    {
        std::lock_guard<std::mutex> lock_guard{m_Mutex};
        return invoke(forward<CallableT>(callable), m_SharedData);
    }
#endif

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR monitor_helper ManuallyLock() const PHI_NOEXCEPT
    {
        return monitor_helper{this};
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR SharedDataT& GetThreadUnsafeAccess() PHI_NOEXCEPT
    {
        return m_SharedData;
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const SharedDataT& GetThreadUnsafeAccess() const
            PHI_NOEXCEPT
    {
        return m_SharedData;
    }

private:
    mutable element_type m_SharedData; /// the shared data
    mutable std::mutex   m_Mutex;      /// the mutex to guard access to the shared data
};

PHI_CLANG_SUPPRESS_WARNING_POP()

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_MONITOR_HPP
