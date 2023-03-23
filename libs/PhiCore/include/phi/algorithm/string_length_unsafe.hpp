#ifndef INCG_PHI_ALGORITHM_STRING_LENGTH_UNSAFE_HPP
#define INCG_PHI_ALGORITHM_STRING_LENGTH_UNSAFE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/algorithm/min.hpp"
#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/extended_attributes.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include "phi/compiler_support/warning.hpp"
#include "phi/core/assert.hpp"
#include "phi/core/nullptr_t.hpp"
#include "phi/core/types.hpp"
#include "phi/forward/std/string.hpp"
#include "phi/forward/std/string_view.hpp"
#include "phi/forward/string_view.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

PHI_CLANG_SUPPRESS_WARNING_PUSH()
PHI_CLANG_SUPPRESS_WARNING("-Wtautological-pointer-compare")
#if PHI_COMPILER_IS_ATLEAST(CLANG, 16, 0, 0)
PHI_CLANG_SUPPRESS_WARNING("-Wunsafe-buffer-usage")
#endif

PHI_GCC_SUPPRESS_WARNING_PUSH()
PHI_GCC_SUPPRESS_WARNING("-Wnonnull-compare")
PHI_GCC_SUPPRESS_WARNING("-Wsuggest-attribute=pure")

template <typename CharT>
PHI_NODISCARD PHI_ATTRIBUTE_NONNULL PHI_EXTENDED_CONSTEXPR usize
string_length_unsafe(CharT* string) noexcept
{
    PHI_ASSERT(string != nullptr, "Passing nullptr to string_length_unsafe is not allowed. Use "
                                  "string_length if you intended to pass a nullptr.");

    usize count = 0u;
    for (; *string != CharT('\0'); ++string)
    {
        ++count;
    }

    return count;
}

template <typename CharT, typename TraitsT>
PHI_NODISCARD PHI_ATTRIBUTE_PURE constexpr usize string_length_unsafe(
        basic_string_view<CharT, TraitsT> string) noexcept
{
    return string.length();
}

template <typename CharT, typename TraitsT, typename AllocatorT>
PHI_NODISCARD PHI_ATTRIBUTE_PURE constexpr usize string_length_unsafe(
        std::basic_string<CharT, TraitsT, AllocatorT> string) noexcept
{
    return string.length();
}

template <typename CharT, typename TraitsT>
PHI_NODISCARD PHI_ATTRIBUTE_PURE constexpr usize string_length_unsafe(
        std::basic_string_view<CharT, TraitsT> string) noexcept
{
    return string.length();
}

template <typename CharT = nullptr_t>
PHI_NODISCARD constexpr usize string_length_unsafe(nullptr_t) noexcept = delete;

template <typename CharT>
PHI_NODISCARD PHI_ATTRIBUTE_NONNULL PHI_EXTENDED_CONSTEXPR usize
string_length_unsafe(CharT* string, usize length) noexcept
{
    PHI_ASSERT(string != nullptr, "Passing nullptr to string_length_unsafe is not allowed. Use "
                                  "string_length if you intended to pass a nullptr.");

    usize count = 0u;
    for (; count < length && *string != CharT('\0'); ++string)
    {
        ++count;
    }

    return count;
}

PHI_GCC_SUPPRESS_WARNING_POP()
PHI_CLANG_SUPPRESS_WARNING_POP()

template <typename CharT, typename TraitsT>
PHI_NODISCARD PHI_ATTRIBUTE_PURE constexpr usize string_length_unsafe(
        basic_string_view<CharT, TraitsT> string, usize length) noexcept
{
    return min(usize(string.length()), length);
}

template <typename CharT, typename TraitsT, typename AllocatorT>
PHI_NODISCARD PHI_ATTRIBUTE_PURE constexpr usize string_length_unsafe(
        std::basic_string<CharT, TraitsT, AllocatorT> string, usize length) noexcept
{
    return min(usize(string.length()), length);
}

template <typename CharT, typename TraitsT>
PHI_NODISCARD PHI_ATTRIBUTE_PURE constexpr usize string_length_unsafe(
        std::basic_string_view<CharT, TraitsT> string, usize length) noexcept
{
    return min(usize(string.length()), length);
}

template <typename CharT = nullptr_t>
PHI_NODISCARD constexpr usize string_length_unsafe(nullptr_t, usize) noexcept = delete;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_ALGORITHM_STRING_LENGTH_UNSAFE_HPP
