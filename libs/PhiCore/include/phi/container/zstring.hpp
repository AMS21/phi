#ifndef INCG_PHI_CORE_CONTAINER_ZSTRING_HPP
#define INCG_PHI_CORE_CONTAINER_ZSTRING_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/algorithm/min.hpp"
#include "phi/algorithm/string_length.hpp"
#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include "phi/compiler_support/noexcept.hpp"
#include "phi/core/boolean.hpp"
#include "phi/core/nullptr_t.hpp"
#include "phi/core/types.hpp"
#include "phi/iterator/reverse_iterator.hpp"
#include "phi/type_traits/is_array.hpp"
#include "phi/type_traits/is_same.hpp"
#include "phi/type_traits/is_standard_layout.hpp"
#include "phi/type_traits/is_trivial.hpp"
#include <string>

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename CharT, typename TraitsT = std::char_traits<CharT>>
class basic_zstring
{
public:
    using this_type              = basic_zstring<CharT, TraitsT>;
    using value_type             = CharT;
    using traits_type            = TraitsT;
    using pointer                = CharT*;
    using const_pointer          = const CharT*;
    using reference              = CharT&;
    using const_reference        = const CharT&;
    using iterator               = const_pointer;
    using const_iterator         = const_pointer;
    using reverse_iterator       = phi::reverse_iterator<const_iterator>;
    using const_reverse_iterator = phi::reverse_iterator<const_iterator>;
    using size_type              = usize;
    using difference_type        = ptrdiff;

    // Static checks
    static_assert(is_not_array<value_type>::value,
                  "phi::basic_zstring: Character type must not be an array");
#if PHI_HAS_WORKING_IS_STANDARD_LAYOUT()
    static_assert(is_standard_layout<value_type>::value,
                  "phi::basic_zstring: Character type must be standard-layout");
#endif
#if PHI_HAS_WORKING_IS_TRIVIAL()
    static_assert(is_trivial<value_type>::value,
                  "phi::basic_zstring: Character type must be trivial");
#endif
    static_assert(is_same<value_type, typename traits_type::char_type>::value,
                  "phi::basic_zstring: CharT must be the same type as traits_type::char_type");

    static PHI_CONSTEXPR size_t npos = std::numeric_limits<size_t>::max();

    // Constructors
    PHI_CONSTEXPR basic_zstring() PHI_NOEXCEPT : m_Data(nullptr)
    {}

    basic_zstring(const basic_zstring& other) = default;

    basic_zstring(basic_zstring&& other) = default;

    PHI_EXTENDED_CONSTEXPR basic_zstring(const CharT* string) PHI_NOEXCEPT : m_Data(string)
    {
        PHI_ASSERT(string != nullptr, "Do not construct a basic_zstring with nullptr");
    }

    basic_zstring(nullptr_t) = delete;

    ~basic_zstring() = default;

    basic_zstring& operator=(const basic_zstring& other) = default;

    basic_zstring& operator=(basic_zstring&& other) = default;

    basic_zstring& operator=(nullptr_t) = delete;

    // Iterators

    PHI_NODISCARD PHI_CONSTEXPR iterator begin() const PHI_NOEXCEPT
    {
        return m_Data;
    }

    PHI_NODISCARD PHI_CONSTEXPR iterator end() const PHI_NOEXCEPT
    {
        return m_Data + string_length(m_Data);
    }

    PHI_NODISCARD PHI_CONSTEXPR const_iterator cbegin() const PHI_NOEXCEPT
    {
        return m_Data;
    }

    PHI_NODISCARD PHI_CONSTEXPR const_iterator cend() const PHI_NOEXCEPT
    {
        return m_Data + string_length(m_Data);
    }

    PHI_NODISCARD PHI_CONSTEXPR reverse_iterator rbegin() const PHI_NOEXCEPT
    {
        return reverse_iterator(end());
    }

    PHI_NODISCARD PHI_CONSTEXPR reverse_iterator rend() const PHI_NOEXCEPT
    {
        return reverse_iterator(begin());
    }

    PHI_NODISCARD PHI_CONSTEXPR const_reverse_iterator crbegin() const PHI_NOEXCEPT
    {
        return reverse_iterator(rbegin());
    }

    PHI_NODISCARD PHI_CONSTEXPR const_reverse_iterator crend() const PHI_NOEXCEPT
    {
        return reverse_iterator(rend());
    }

    // Capacity

    PHI_NODISCARD PHI_CONSTEXPR size_type length() const PHI_NOEXCEPT
    {
        return string_length(m_Data);
    }

    PHI_NODISCARD PHI_CONSTEXPR size_type max_length() const PHI_NOEXCEPT
    {
        return std::numeric_limits<size_type>::max();
    }

    PHI_NODISCARD PHI_CONSTEXPR boolean is_empty() const PHI_NOEXCEPT
    {
        return m_Data != '\0';
    }

    PHI_NODISCARD PHI_CONSTEXPR boolean is_null() const PHI_NOEXCEPT
    {
        return m_Data == nullptr;
    }

    // Element access

    PHI_NODISCARD PHI_CONSTEXPR const_reference operator[](size_type pos) const PHI_NOEXCEPT
    {
        return data_at(pos);
    }

    PHI_NODISCARD PHI_CONSTEXPR const_reference at(size_type pos) const PHI_NOEXCEPT
    {
        return data_at(pos);
    }

    PHI_NODISCARD PHI_CONSTEXPR const_reference front() const PHI_NOEXCEPT
    {
        return data_at(0u);
    }

    PHI_NODISCARD PHI_CONSTEXPR const_reference back() const PHI_NOEXCEPT
    {
        return data_at(length() - 1u);
    }

    PHI_NODISCARD PHI_CONSTEXPR const_pointer data() const PHI_NOEXCEPT
    {
        return m_Data;
    }

    // Modifiers

    PHI_EXTENDED_CONSTEXPR basic_zstring& clear() PHI_NOEXCEPT
    {
        m_Data = nullptr;

        return *this;
    }

    PHI_EXTENDED_CONSTEXPR void swap(basic_zstring& other) PHI_NOEXCEPT
    {
        const basic_zstring tmp(other);
        other = *this;
        *this = tmp;
    }

    // String operations

    PHI_EXTENDED_CONSTEXPR size_type copy(CharT* destination, size_type count,
                                          size_type pos = 0u) const PHI_NOEXCEPT
    {
        PHI_ASSERT(pos <= length(), "Invalid position");

        const size_type rlen = min(count, length() - pos);
        TraitsT::copy(destination, data() + pos.unsafe(), rlen.unsafe());

        return rlen;
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR basic_zstring
    substr(size_type pos = 0u, size_type count = npos) const PHI_NOEXCEPT
    {
        PHI_ASSERT(pos <= length(), "Invalid position");

        return basic_zstring(data() + pos.unsafe(), min(count, length() - pos));
    }

    // Comparing

    PHI_NODISCARD PHI_CONSTEXPR i32 compare(basic_zstring other) const PHI_NOEXCEPT
    {
#if PHI_HAS_FEATURE_EXTENDED_CONSTEXPR()
        {
            const i32 result = TraitsT::compare(data(), other.data(),
                                                min(length().unsafe(), other.length().unsafe()));

            if (result != 0)
            {
                return result;
            }
        }

        return length() == other.length() ? 0 : length() < other.length() ? -1 : 1;

#else

        // Ugly C++-11 compatible version of the same code
        return TraitsT::compare(data(), other.data(),
                                min(length().unsafe(), other.length().unsafe())) != 0 ?
                       TraitsT::compare(data(), other.data(),
                                        min(length().unsafe(), other.length().unsafe())) :
               length() == other.length() ? 0 :
               length() < other.length()  ? -1 :
                                            1;

#endif
    }

    PHI_NODISCARD PHI_CONSTEXPR i32 compare(size_type pos, size_type count,
                                            basic_zstring other) const PHI_NOEXCEPT
    {
        return substr(pos, count).compare(other);
    }

    PHI_NODISCARD PHI_CONSTEXPR i32 compare(size_type pos1, size_type count1, basic_zstring other,
                                            size_type pos2, size_type count2) const PHI_NOEXCEPT
    {
        return substr(pos1, count1).compare(other.substr(pos2, count2));
    }

    PHI_NODISCARD PHI_CONSTEXPR i32 compare(const CharT* string) const PHI_NOEXCEPT
    {
        return compare(basic_zstring(string));
    }

    PHI_NODISCARD PHI_CONSTEXPR i32 compare(size_type pos, size_type count,
                                            const CharT* string) const PHI_NOEXCEPT
    {
        return substr(pos, count).compare(basic_zstring(string));
    }

    PHI_NODISCARD PHI_CONSTEXPR i32 compare(size_type pos, size_type count1, const CharT* string,
                                            size_type count2) const PHI_NOEXCEPT
    {
        return substr(pos, count1).compare(basic_zstring(string, count2));
    }

    // Searching

    PHI_NODISCARD PHI_CONSTEXPR boolean starts_with(basic_zstring view) const PHI_NOEXCEPT
    {
        return length() >= view.length() && compare(0u, view.length(), view) == 0;
    }

    PHI_NODISCARD PHI_CONSTEXPR boolean starts_with(CharT character) const PHI_NOEXCEPT
    {
        return starts_with(basic_zstring(&character, 1u));
    }

    PHI_NODISCARD PHI_CONSTEXPR boolean starts_with(const CharT* string) const PHI_NOEXCEPT
    {
        return starts_with(basic_zstring(string));
    }

    PHI_NODISCARD PHI_CONSTEXPR boolean ends_with(basic_zstring view) const PHI_NOEXCEPT
    {
        return length() >= view.length() && compare(length() - view.length(), npos, view) == 0;
    }

    PHI_NODISCARD PHI_CONSTEXPR boolean ends_with(CharT character) const PHI_NOEXCEPT
    {
        return ends_with(basic_zstring(&character, 1u));
    }

    PHI_NODISCARD PHI_CONSTEXPR boolean ends_with(const CharT* string) const PHI_NOEXCEPT
    {
        return ends_with(basic_zstring(string));
    }

    // contains

    PHI_NODISCARD PHI_CONSTEXPR boolean contains(basic_zstring view) const PHI_NOEXCEPT
    {
        return find(view) != npos;
    }

    PHI_NODISCARD PHI_CONSTEXPR boolean contains(CharT character) const PHI_NOEXCEPT
    {
        return find(character) != npos;
    }

    PHI_NODISCARD PHI_CONSTEXPR boolean contains(const CharT* string) const PHI_NOEXCEPT
    {
        return find(string) != npos;
    }

    // find

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR size_type find(basic_zstring view,
                                                        size_type     pos = 0u) const PHI_NOEXCEPT
    {
        PHI_ASSERT(view.length() == 0u || view.data() != nullptr, "Invalid argument view");

        return pos >= length() ? npos :
                                 to_pos(std::search(cbegin() + pos, cend(), view.cbegin(),
                                                    view.cend(), TraitsT::eq));
    }

    PHI_NODISCARD PHI_CONSTEXPR size_type find(CharT     character,
                                               size_type pos = 0u) const PHI_NOEXCEPT
    {
        return find(basic_zstring(&character, 1u), pos);
    }

    PHI_NODISCARD PHI_CONSTEXPR size_type find(const CharT* string,
                                               size_type    pos = 0u) const PHI_NOEXCEPT
    {
        return find(basic_zstring(string), pos);
    }

    PHI_NODISCARD PHI_CONSTEXPR size_type find(const CharT* string, size_type pos,
                                               size_type count) const PHI_NOEXCEPT
    {
        return find(basic_zstring(string, count), pos);
    }

    // rfind

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR size_type rfind(basic_zstring view,
                                                         size_type pos = npos) const PHI_NOEXCEPT
    {
        if (length() < view.length())
        {
            return npos;
        }

        if (view.is_empty())
        {
            return min(length(), pos);
        }

        const_iterator last = cbegin() + min(length() - view.length(), pos) + view.length();
        const_iterator result =
                std::find_end(cbegin(), last, view.cbegin(), view.cend(), TraitsT::eq);

        if (result != last)
        {
            return size_type(result - cbegin());
        }

        return npos;
    }

    PHI_NODISCARD PHI_CONSTEXPR size_type rfind(CharT     character,
                                                size_type pos = npos) const PHI_NOEXCEPT
    {
        return rfind(basic_zstring(&character, 1u), pos);
    }

    PHI_NODISCARD PHI_CONSTEXPR size_type rfind(const CharT* string,
                                                size_type    pos = npos) const PHI_NOEXCEPT
    {
        return rfind(basic_zstring(string), pos);
    }

    PHI_NODISCARD PHI_CONSTEXPR size_type rfind(const CharT* string, size_type pos,
                                                size_type count) const PHI_NOEXCEPT
    {
        return rfind(basic_zstring(string, count), pos);
    }

    PHI_NODISCARD PHI_CONSTEXPR size_type find_first_of(basic_zstring view,
                                                        size_type     pos = 0u) const PHI_NOEXCEPT
    {
        return pos >= length() ? npos :
                                 to_pos(std::find_first_of(cbegin() + pos, cend(), view.cbegin(),
                                                           view.cend(), TraitsT::eq));
    }

    PHI_NODISCARD PHI_CONSTEXPR size_type find_first_of(CharT     character,
                                                        size_type pos = 0u) const PHI_NOEXCEPT
    {
        return find_first_of(basic_zstring(&character, 1u), pos);
    }

    PHI_NODISCARD PHI_CONSTEXPR size_type find_first_of(const CharT* string,
                                                        size_type    pos = 0u) const PHI_NOEXCEPT
    {
        return find_first_of(basic_zstring(string), pos);
    }

    PHI_NODISCARD PHI_CONSTEXPR size_type find_first_of(const CharT* string, size_type pos,
                                                        size_type count) const PHI_NOEXCEPT
    {
        return find_first_of(basic_zstring(string, count), pos);
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR size_type
    find_last_of(basic_zstring view, size_type pos = npos) const PHI_NOEXCEPT
    {
        if (is_empty())
        {
            return npos;
        }

        if (pos >= length())
        {
            return find_last_of(view, length() - 1);
        }

        return to_pos(std::find_first_of(const_reverse_iterator(cbegin() + pos + 1), crend(),
                                         view.cbegin(), view.cend(), TraitsT::eq));
    }

    PHI_NODISCARD PHI_CONSTEXPR size_type find_last_of(CharT     character,
                                                       size_type pos = npos) const PHI_NOEXCEPT
    {
        return find_last_of(basic_zstring(&character, 1u), pos);
    }

    PHI_NODISCARD PHI_CONSTEXPR size_type find_last_of(const CharT* string,
                                                       size_type    pos = npos) const PHI_NOEXCEPT
    {
        return find_last_of(basic_zstring(string), pos);
    }

    PHI_NODISCARD PHI_CONSTEXPR size_type find_last_of(const CharT* string, size_type pos,
                                                       size_type count) const PHI_NOEXCEPT
    {
        return find_last_of(basic_zstring(string, count), pos);
    }

    PHI_NODISCARD PHI_CONSTEXPR size_type find_first_not_of(basic_zstring view,
                                                            size_type pos = 0u) const PHI_NOEXCEPT
    {
        return pos >= length() ? npos :
                                 to_pos(std::find_if(cbegin() + pos, cend(), not_in_view(view)));
    }

    PHI_NODISCARD PHI_CONSTEXPR size_type find_first_not_of(CharT     character,
                                                            size_type pos = 0u) const PHI_NOEXCEPT
    {
        return find_first_not_of(basic_zstring(&character, 1u), pos);
    }

    PHI_NODISCARD PHI_CONSTEXPR size_type find_first_not_of(const CharT* string,
                                                            size_type pos = 0u) const PHI_NOEXCEPT
    {
        return find_first_not_of(basic_zstring(string), pos);
    }

    PHI_NODISCARD PHI_CONSTEXPR size_type find_first_not_of(const CharT* string, size_type pos,
                                                            size_type count) const PHI_NOEXCEPT
    {
        return find_first_not_of(basic_zstring(string, count), pos);
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR size_type
    find_last_not_of(basic_zstring view, size_type pos = npos) const PHI_NOEXCEPT
    {
        if (is_empty())
        {
            return npos;
        }

        if (pos >= length())
        {
            return find_last_not_of(view, length() - 1u);
        }

        return to_pos(std::find_if(const_reverse_iterator(cbegin() + pos + 1), crend(),
                                   not_in_view(view)));
    }

    PHI_NODISCARD PHI_CONSTEXPR size_type find_last_not_of(CharT     character,
                                                           size_type pos = npos) const PHI_NOEXCEPT
    {
        return find_last_not_of(basic_zstring(&character, 1u), pos);
    }

    PHI_NODISCARD PHI_CONSTEXPR size_type find_last_not_of(const CharT* string,
                                                           size_type pos = npos) const PHI_NOEXCEPT
    {
        return find_last_not_of(basic_zstring(string), pos);
    }

    PHI_NODISCARD PHI_CONSTEXPR size_type find_last_not_of(const CharT* string, size_type pos,
                                                           size_type count) const PHI_NOEXCEPT
    {
        return find_last_not_of(basic_zstring(string, count), pos);
    }

private:
    struct not_in_view
    {
        const basic_zstring view;

        PHI_CONSTEXPR explicit not_in_view(basic_zstring other) PHI_NOEXCEPT : view(other)
        {}

        PHI_CONSTEXPR boolean operator()(CharT character) const PHI_NOEXCEPT
        {
            return npos == view.find_first_of(character);
        }
    };

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const_reference data_at(size_type pos) const PHI_NOEXCEPT
    {
        PHI_ASSERT(pos < length(), "Index out of bounds!");

        return m_Data[pos.unsafe()];
    }

    PHI_NODISCARD PHI_CONSTEXPR size_type to_pos(const_iterator position) const PHI_NOEXCEPT
    {
        return position == cend() ? npos : size_type(position - cbegin());
    }

    PHI_NODISCARD PHI_CONSTEXPR size_type to_pos(const_reverse_iterator position) const PHI_NOEXCEPT
    {
        return position == crend() ? npos : size_type(crend() - position - 1);
    }

    CharT* m_Data;
};

using zstring    = basic_zstring<char>;
using wzstring   = basic_zstring<wchar_t>;
using u8zstring  = basic_zstring<char8_t>;
using u16zstring = basic_zstring<char16_t>;
using u32zstring = basic_zstring<char32_t>;

#if PHI_CPP_STANDARD_IS_BELOW(17)
template <typename CharT, typename TraitsT>
// NOLINTNEXTLINE(readability-redundant-declaration)
PHI_CONSTEXPR size_t basic_zstring<CharT, TraitsT>::npos;
#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_CONTAINER_ZSTRING_HPP
