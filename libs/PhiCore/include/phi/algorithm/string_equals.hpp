#ifndef INCG_PHI_CORE_ALGORITHM_STRING_EQUALS_HPP
#define INCG_PHI_CORE_ALGORITHM_STRING_EQUALS_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include "phi/compiler_support/noexcept.hpp"
#include "phi/core/boolean.hpp"
#include "phi/core/nullptr_t.hpp"
#include "phi/core/types.hpp"
#include "phi/forward/std/string.hpp"
#include "phi/forward/std/string_view.hpp"
#include "phi/forward/string_view.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

// nullptr_t - x

template <typename CharT = char>
PHI_NODISCARD PHI_CONSTEXPR boolean string_equals(nullptr_t, nullptr_t) PHI_NOEXCEPT
{
    return true;
}

template <typename CharT>
PHI_NODISCARD PHI_CONSTEXPR boolean string_equals(nullptr_t, const CharT* rhs) PHI_NOEXCEPT
{
    return rhs == nullptr;
}

template <typename CharT, typename TraitsT>
PHI_NODISCARD PHI_CONSTEXPR boolean string_equals(nullptr_t, basic_string_view<CharT, TraitsT> rhs)
        PHI_NOEXCEPT
{
    return rhs.is_null();
}

template <typename CharT, typename TraitsT>
PHI_NODISCARD PHI_CONSTEXPR boolean
string_equals(nullptr_t, std::basic_string_view<CharT, TraitsT> rhs) PHI_NOEXCEPT
{
    return rhs.data() == nullptr;
}

template <typename CharT, typename TraitsT, typename AllocatorT>
PHI_NODISCARD PHI_CONSTEXPR boolean
string_equals(nullptr_t, std::basic_string<CharT, TraitsT, AllocatorT> rhs) PHI_NOEXCEPT
{
    return rhs.data() == nullptr;
}

// CharT - x

template <typename CharT>
PHI_NODISCARD PHI_CONSTEXPR boolean string_equals(const CharT* lhs, nullptr_t) PHI_NOEXCEPT
{
    return lhs == nullptr;
}

template <typename CharT>
PHI_NODISCARD PHI_EXTENDED_CONSTEXPR boolean string_equals(const CharT* lhs,
                                                           const CharT* rhs) PHI_NOEXCEPT
{
    if (lhs == nullptr || rhs == nullptr)
    {
        return static_cast<bool>(lhs == rhs);
    }

    while (*lhs != CharT('\0'))
    {
        if (*lhs != *rhs)
        {
            return false;
        }

        ++lhs;
        ++rhs;
    }

    return *lhs == *rhs;
}

template <typename CharT, typename TraitsT>
PHI_NODISCARD PHI_EXTENDED_CONSTEXPR boolean
string_equals(const CharT* lhs, basic_string_view<CharT, TraitsT> rhs) PHI_NOEXCEPT
{
    if (lhs == nullptr)
    {
        return rhs.is_null();
    }

    return lhs == rhs;
}

template <typename CharT, typename TraitsT>
PHI_NODISCARD PHI_EXTENDED_CONSTEXPR boolean
string_equals(const CharT* lhs, std::basic_string_view<CharT, TraitsT> rhs) PHI_NOEXCEPT
{
    // Check for nullptr
    if (lhs == nullptr || rhs.data() == nullptr)
    {
        return rhs.data() == lhs;
    }

    return lhs == rhs;
}

template <typename CharT, typename TraitsT, typename AllocatorT>
PHI_NODISCARD PHI_CONSTEXPR boolean
string_equals(const CharT* lhs, std::basic_string<CharT, TraitsT, AllocatorT> rhs) PHI_NOEXCEPT
{
    return lhs == basic_string_view<CharT, TraitsT>(rhs.data(), rhs.length());
}

// phi::basic_string_view - x

template <typename CharT, typename TraitsT>
PHI_NODISCARD PHI_CONSTEXPR boolean string_equals(basic_string_view<CharT, TraitsT> lhs,
                                                  nullptr_t) PHI_NOEXCEPT
{
    return lhs.is_null();
}

template <typename CharT, typename TraitsT>
PHI_NODISCARD PHI_EXTENDED_CONSTEXPR boolean string_equals(basic_string_view<CharT, TraitsT> lhs,
                                                           const CharT* rhs) PHI_NOEXCEPT
{
    if (lhs.is_null())
    {
        return rhs == nullptr;
    }
    if (rhs == nullptr)
    {
        return lhs.is_null();
    }

    return lhs == rhs;
}

template <typename CharT, typename TraitsT>
PHI_NODISCARD PHI_CONSTEXPR boolean string_equals(
        basic_string_view<CharT, TraitsT> lhs, basic_string_view<CharT, TraitsT> rhs) PHI_NOEXCEPT
{
    return lhs == rhs;
}

template <typename CharT, typename TraitsT>
PHI_NODISCARD PHI_CONSTEXPR boolean string_equals(basic_string_view<CharT, TraitsT>      lhs,
                                                  std::basic_string_view<CharT, TraitsT> rhs)
        PHI_NOEXCEPT
{
    return lhs == phi::basic_string_view<CharT, TraitsT>(rhs);
}

template <typename CharT, typename TraitsT, typename AllocatorT>
PHI_NODISCARD PHI_CONSTEXPR boolean string_equals(basic_string_view<CharT, TraitsT>             lhs,
                                                  std::basic_string<CharT, TraitsT, AllocatorT> rhs)
        PHI_NOEXCEPT
{
    return lhs == basic_string_view<CharT, TraitsT>(rhs.data(), rhs.length());
}

// std::string_view - x

template <typename CharT, typename TraitsT>
PHI_NODISCARD PHI_CONSTEXPR boolean string_equals(std::basic_string_view<CharT, TraitsT> lhs,
                                                  nullptr_t) PHI_NOEXCEPT
{
    return lhs.data() == nullptr;
}

template <typename CharT, typename TraitsT>
PHI_NODISCARD PHI_EXTENDED_CONSTEXPR boolean
string_equals(std::basic_string_view<CharT, TraitsT> lhs, const CharT* rhs) PHI_NOEXCEPT
{
    if (lhs.data() == nullptr)
    {
        return lhs.data() == rhs;
    }
    if (rhs == nullptr)
    {
        return lhs.data() == nullptr;
    }

    return lhs == rhs;
}

template <typename CharT, typename TraitsT>
PHI_NODISCARD PHI_CONSTEXPR boolean string_equals(std::basic_string_view<CharT, TraitsT> lhs,
                                                  basic_string_view<CharT, TraitsT>      rhs)
        PHI_NOEXCEPT
{
    return phi::basic_string_view<CharT, TraitsT>(lhs) == rhs;
}

template <typename CharT, typename TraitsT>
PHI_NODISCARD PHI_CONSTEXPR boolean string_equals(std::basic_string_view<CharT, TraitsT> lhs,
                                                  std::basic_string_view<CharT, TraitsT> rhs)
        PHI_NOEXCEPT
{
    return lhs == rhs;
}

template <typename CharT, typename TraitsT, typename AllocatorT>
PHI_NODISCARD PHI_CONSTEXPR boolean string_equals(std::basic_string_view<CharT, TraitsT>        lhs,
                                                  std::basic_string<CharT, TraitsT, AllocatorT> rhs)
        PHI_NOEXCEPT
{
    return phi::basic_string_view<CharT, TraitsT>(lhs) ==
           phi::basic_string_view<CharT, TraitsT>(rhs);
}

// std::basic_string - x

template <typename CharT, typename TraitsT, typename AllocatorT>
PHI_NODISCARD PHI_CONSTEXPR boolean string_equals(std::basic_string<CharT, TraitsT, AllocatorT> lhs,
                                                  nullptr_t) PHI_NOEXCEPT
{
    return lhs.data() == nullptr;
}

template <typename CharT, typename TraitsT, typename AllocatorT>
PHI_NODISCARD PHI_CONSTEXPR boolean string_equals(std::basic_string<CharT, TraitsT, AllocatorT> lhs,
                                                  const CharT* rhs) PHI_NOEXCEPT
{
    return basic_string_view<CharT, TraitsT>(lhs.data(), lhs.length()) == rhs;
}

template <typename CharT, typename TraitsT, typename AllocatorT>
PHI_NODISCARD PHI_CONSTEXPR boolean string_equals(std::basic_string<CharT, TraitsT, AllocatorT> lhs,
                                                  basic_string_view<CharT, TraitsT>             rhs)
        PHI_NOEXCEPT
{
    return basic_string_view<CharT, TraitsT>(lhs.data(), lhs.length()) == rhs;
}

template <typename CharT, typename TraitsT, typename AllocatorT>
PHI_NODISCARD PHI_CONSTEXPR boolean string_equals(std::basic_string<CharT, TraitsT, AllocatorT> lhs,
                                                  std::basic_string_view<CharT, TraitsT>        rhs)
        PHI_NOEXCEPT
{
    return lhs == rhs;
}

template <typename CharT, typename TraitsT, typename AllocatorT>
PHI_NODISCARD PHI_CONSTEXPR boolean string_equals(std::basic_string<CharT, TraitsT, AllocatorT> lhs,
                                                  std::basic_string<CharT, TraitsT, AllocatorT> rhs)
        PHI_NOEXCEPT
{
    return lhs == rhs;
}

// TODO: implement with count

template <typename CharT>
PHI_NODISCARD PHI_EXTENDED_CONSTEXPR boolean string_equals(const CharT* lhs, const CharT* rhs,
                                                           usize count) PHI_NOEXCEPT
{
    PHI_ASSERT(count > 0u, "count must be greater than zero");

    if ((lhs == nullptr || rhs == nullptr))
    {
        return static_cast<bool>(lhs == rhs);
    }

    while (*lhs != CharT('\0') && (--count > 0u))
    {
        if (*lhs != *rhs)
        {
            return false;
        }

        ++lhs;
        ++rhs;
    }

    return *lhs == *rhs;
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_ALGORITHM_STRING_EQUALS_HPP
