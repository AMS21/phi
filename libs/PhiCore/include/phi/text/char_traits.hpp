#ifndef INCG_PHI_CORE_TEXT_CHAR_TRAITS_HPP
#define INCG_PHI_CORE_TEXT_CHAR_TRAITS_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/algorithm/copy_n.hpp"
#include "phi/compiler_support/char8_t.hpp"
#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/noexcept.hpp"
#include "phi/core/assert.hpp"
#include "phi/core/memcmp.hpp"
#include "phi/core/streamoff.hpp"
#include "phi/core/wint_t.hpp"
#include "phi/forward/char_traits.hpp"
#include <iosfwd>

DETAIL_PHI_BEGIN_NAMESPACE()

template <>
struct char_traits<char>
{
public:
    using this_type  = char_traits<char>;
    using char_type  = char;
    using int_type   = int;
    using off_type   = streamoff;
    using pos_type   = std::fpos<mbstate_t>;
    using state_type = mbstate_t;

    static PHI_CONSTEXPR void assign(char_type& lhs, const char_type& rhs) PHI_NOEXCEPT
    {
        lhs = rhs;
    }

    static PHI_CONSTEXPR bool eq(char_type lhs, char_type rhs) PHI_NOEXCEPT
    {
        return lhs == rhs;
    }

    static PHI_CONSTEXPR bool lt(char_type lhs, char_type rhs) PHI_NOEXCEPT
    {
        return lhs < rhs;
    }

    static PHI_EXTENDED_CONSTEXPR int compare(const char_type* lhs, const char_type* rhs,
                                              size_t count) PHI_NOEXCEPT
    {
        if (count == 0)
        {
            return 0;
        }

        return memcmp(lhs, rhs, count);
    }

    static PHI_EXTENDED_CONSTEXPR char_type* copy(char_type*       string_to,
                                                  const char_type* string_from,
                                                  size_t           count) PHI_NOEXCEPT
    {
        PHI_ASSERT(string_from < string_to || string_from >= string_to + count,
                   "char_traits::copy overlapped range");

        copy_n(string_from, count, string_to);
        return string_to;
    }
};

template <>
struct char_traits<wchar_t>
{
    using char_type  = wchar_t;
    using int_type   = wint_t;
    using off_type   = streamoff;
    using pos_type   = std::fpos<mbstate_t>;
    using state_type = mbstate_t;

    static PHI_CONSTEXPR void assign(char_type& lhs, const char_type& rhs) PHI_NOEXCEPT
    {
        lhs = rhs;
    }

    static PHI_CONSTEXPR bool eq(char_type lhs, char_type rhs) PHI_NOEXCEPT
    {
        return lhs == rhs;
    }

    static PHI_CONSTEXPR bool lt(char_type lhs, char_type rhs) PHI_NOEXCEPT
    {
        return lhs < rhs;
    }

    static PHI_EXTENDED_CONSTEXPR int compare(const char_type* lhs, const char_type* rhs,
                                              size_t count) PHI_NOEXCEPT
    {
        if (count == 0)
        {
            return 0;
        }

        return memcmp(lhs, rhs, count);
    }

    static PHI_EXTENDED_CONSTEXPR char_type* copy(char_type*       string_to,
                                                  const char_type* string_from,
                                                  size_t           count) PHI_NOEXCEPT
    {
        PHI_ASSERT(string_from < string_to || string_from >= string_to + count,
                   "char_traits::copy overlapped range");

        copy_n(string_from, count, string_to);
        return string_to;
    }
};

template <>
struct char_traits<char8_t>
{
    using char_type  = char8_t;
    using int_type   = unsigned int;
    using off_type   = streamoff;
    using pos_type   = std::fpos<mbstate_t>;
    using state_type = mbstate_t;

    static PHI_CONSTEXPR void assign(char_type& lhs, const char_type& rhs) PHI_NOEXCEPT
    {
        lhs = rhs;
    }

    static PHI_CONSTEXPR bool eq(char_type lhs, char_type rhs) PHI_NOEXCEPT
    {
        return lhs == rhs;
    }

    static PHI_CONSTEXPR bool lt(char_type lhs, char_type rhs) PHI_NOEXCEPT
    {
        return lhs < rhs;
    }

    static PHI_EXTENDED_CONSTEXPR int compare(const char_type* lhs, const char_type* rhs,
                                              size_t count) PHI_NOEXCEPT
    {
        if (count == 0)
        {
            return 0;
        }

        return memcmp(lhs, rhs, count);
    }

    static PHI_EXTENDED_CONSTEXPR char_type* copy(char_type*       string_to,
                                                  const char_type* string_from,
                                                  size_t           count) PHI_NOEXCEPT
    {
        PHI_ASSERT(string_from < string_to || string_from >= string_to + count,
                   "char_traits::copy overlapped range");

        copy_n(string_from, count, string_to);
        return string_to;
    }
};

template <>
struct char_traits<char16_t>
{
    using char_type  = char16_t;
    using int_type   = unsigned int;
    using off_type   = streamoff;
    using pos_type   = std::fpos<mbstate_t>;
    using state_type = mbstate_t;

    static PHI_CONSTEXPR void assign(char_type& lhs, const char_type& rhs) PHI_NOEXCEPT
    {
        lhs = rhs;
    }

    static PHI_CONSTEXPR bool eq(char_type lhs, char_type rhs) PHI_NOEXCEPT
    {
        return lhs == rhs;
    }

    static PHI_CONSTEXPR bool lt(char_type lhs, char_type rhs) PHI_NOEXCEPT
    {
        return lhs < rhs;
    }

    static PHI_EXTENDED_CONSTEXPR int compare(const char_type* lhs, const char_type* rhs,
                                              size_t count) PHI_NOEXCEPT
    {
        if (count == 0)
        {
            return 0;
        }

        return memcmp(lhs, rhs, count);
    }

    static PHI_EXTENDED_CONSTEXPR char_type* copy(char_type*       string_to,
                                                  const char_type* string_from,
                                                  size_t           count) PHI_NOEXCEPT
    {
        PHI_ASSERT(string_from < string_to || string_from >= string_to + count,
                   "char_traits::copy overlapped range");

        copy_n(string_from, count, string_to);
        return string_to;
    }
};

template <>
struct char_traits<char32_t>
{
    using char_type  = char32_t;
    using int_type   = unsigned int;
    using off_type   = streamoff;
    using pos_type   = std::fpos<mbstate_t>;
    using state_type = mbstate_t;

    static PHI_CONSTEXPR void assign(char_type& lhs, const char_type& rhs) PHI_NOEXCEPT
    {
        lhs = rhs;
    }

    static PHI_CONSTEXPR bool eq(char_type lhs, char_type rhs) PHI_NOEXCEPT
    {
        return lhs == rhs;
    }

    static PHI_CONSTEXPR bool lt(char_type lhs, char_type rhs) PHI_NOEXCEPT
    {
        return lhs < rhs;
    }

    static PHI_EXTENDED_CONSTEXPR int compare(const char_type* lhs, const char_type* rhs,
                                              size_t count) PHI_NOEXCEPT
    {
        if (count == 0)
        {
            return 0;
        }

        return memcmp(lhs, rhs, count);
    }

    static PHI_EXTENDED_CONSTEXPR char_type* copy(char_type*       string_to,
                                                  const char_type* string_from,
                                                  size_t           count) PHI_NOEXCEPT
    {
        PHI_ASSERT(string_from < string_to || string_from >= string_to + count,
                   "char_traits::copy overlapped range");

        copy_n(string_from, count, string_to);
        return string_to;
    }
};

DETAIL_PHI_END_NAMESPACE()

// Support for standard library which is missing support
#if PHI_COMPILER_IS_BELOW(GCC, 9, 0, 0)

DETAIL_PHI_BEGIN_STD_NAMESPACE()

template <>
struct char_traits<char8_t> : public phi::char_traits<char8_t>
{};

DETAIL_PHI_END_STD_NAMESPACE()

#endif

#endif // INCG_PHI_CORE_TEXT_CHAR_TRAITS_HPP
