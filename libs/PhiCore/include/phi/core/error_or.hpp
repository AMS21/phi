#ifndef INCG_PHI_CORE_ERROR_OR_HPP
#define INCG_PHI_CORE_ERROR_OR_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/inline.hpp"
#include "phi/compiler_support/noexcept.hpp"
#include "phi/core/assert.hpp"
#include "phi/core/boolean.hpp"
#include "phi/core/forward.hpp"
#include "phi/core/move.hpp"
#include "phi/core/optional.hpp"
#include "phi/type_traits/is_same.hpp"
#include "phi/type_traits/is_void.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename ValueT, typename ErrorT>
class PHI_NODISCARD_CLASS error_or
{
    static_assert(is_not_same<ValueT, ErrorT>::value, "ValueT and ErrorT must be distinct types");
    static_assert(is_not_void<ErrorT>::value, "ErrorT may not be void");

public:
    using this_type  = error_or<ValueT, ErrorT>;
    using value_type = ValueT;
    using error_type = ErrorT;

    PHI_CONSTEXPR error_or(const ValueT& value) PHI_NOEXCEPT : m_Value(value)
    {}

    PHI_CONSTEXPR error_or(ValueT&& value) PHI_NOEXCEPT : m_Value(move(value))
    {}

    template <typename OtherT>
    // NOLINTNEXTLINE(bugprone-forwarding-reference-overload)
    PHI_ALWAYS_INLINE PHI_CONSTEXPR error_or(OtherT&& value) PHI_NOEXCEPT
        : m_Value(forward<OtherT>(value))
    {}

    PHI_CONSTEXPR error_or(ErrorT&& error) PHI_NOEXCEPT : m_Error(move(error))
    {}

    error_or(error_or&& other) = default;

    error_or(error_or const& other) = default;

    ~error_or() = default;

    error_or& operator=(error_or&& other) = default;

    error_or& operator=(error_or const& other) = default;

    PHI_NODISCARD PHI_CONSTEXPR ValueT& value() const PHI_NOEXCEPT
    {
        PHI_ASSERT(!is_error(), "Calling value() with error set");
        PHI_ASSERT(has_value(), "Calling value() with no value set");

        return m_Value.value();
    }

    PHI_NODISCARD PHI_CONSTEXPR ErrorT& error() const PHI_NOEXCEPT
    {
        PHI_ASSERT(is_error(), "Calling error() with no error set");
        PHI_ASSERT(!has_value(), "Calling error() with value set");

        return m_Error.value();
    }

    PHI_NODISCARD PHI_CONSTEXPR boolean is_error() const PHI_NOEXCEPT
    {
        return m_Error.has_value();
    }

    PHI_NODISCARD PHI_CONSTEXPR boolean has_value() const PHI_NOEXCEPT
    {
        return m_Value.has_value();
    }

private:
    optional<ValueT> m_Value;
    optional<ErrorT> m_Error;
};

// Partial specialization for void value type
template <typename ErrorT>
class PHI_NODISCARD_CLASS error_or<void, ErrorT>
{
    static_assert(is_not_void<ErrorT>::value, "ErroT may not be void");

public:
    using this_type  = error_or<void, ErrorT>;
    using value_type = void;
    using error_type = ErrorT;

    error_or() = default;

    PHI_CONSTEXPR error_or(ErrorT error) PHI_NOEXCEPT : m_Error(move(error))
    {}

    error_or(error_or const& other) = default;

    error_or(error_or&& other) = default;

    ~error_or() = default;

    error_or& operator=(error_or const& other) = default;

    error_or& operator=(error_or&& other) = default;

    template <typename ReturnT>
    ReturnT value() = delete;

    PHI_NODISCARD PHI_CONSTEXPR ErrorT& error() const PHI_NOEXCEPT
    {
        PHI_ASSERT(is_error(), "Calling error() with no error set");

        return m_Error.value();
    }

    PHI_NODISCARD PHI_CONSTEXPR boolean is_error() const PHI_NOEXCEPT
    {
        return m_Error.has_value();
    }

    PHI_NODISCARD PHI_ALWAYS_INLINE PHI_CONSTEXPR boolean has_value() const PHI_NOEXCEPT
    {
        return false;
    }

private:
    optional<ErrorT> m_Error;
};

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_ERROR_OR_HPP
