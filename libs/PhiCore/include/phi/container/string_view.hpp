#ifndef INCG_PHI_CORE_CONTAINER_STRING_VIEW_HPP
#define INCG_PHI_CORE_CONTAINER_STRING_VIEW_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/algorithm/min.hpp"
#include "phi/algorithm/string_length.hpp"
#include "phi/compiler_support/char8_t.hpp"
#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/extended_attributes.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include "phi/compiler_support/noexcept.hpp"
#include "phi/core/assert.hpp"
#include "phi/core/boolean.hpp"
#include "phi/core/integer.hpp"
#include "phi/core/nullptr_t.hpp"
#include "phi/core/size_t.hpp"
#include "phi/core/types.hpp"
#include "phi/forward/std/string_view.hpp"
#include "phi/forward/string_view.hpp"
#include "phi/iterator/reverse_iterator.hpp"
#include "phi/text/char_traits.hpp"
#include "phi/type_traits/is_array.hpp"
#include "phi/type_traits/is_same.hpp"
#include "phi/type_traits/is_standard_layout.hpp"
#include "phi/type_traits/is_trivial.hpp"
#include <algorithm>
#include <limits>
#include <string>

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT, size_t Size>
class array;

template <typename TypeT, typename TraitsT>
class not_null_basic_string_view;

template <typename CharT, typename TraitsT /*= std::char_traits<CharT>*/>
class PHI_ATTRIBUTE_POINTER basic_string_view
{
public:
    using this_type              = basic_string_view<CharT, TraitsT>;
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
                  "phi::basic_string_view: Character type must not be an array");
#if PHI_HAS_WORKING_IS_STANDARD_LAYOUT()
    static_assert(is_standard_layout<value_type>::value,
                  "phi::basic_string_view: Character type must be standard-layout");
#endif
#if PHI_HAS_WORKING_IS_TRIVIAL()
    static_assert(is_trivial<value_type>::value,
                  "phi::basic_string_view: Character type must be trivial");
#endif
    static_assert(is_same<value_type, typename traits_type::char_type>::value,
                  "phi::basic_string_view: CharT must be the same type as traits_type::char_type");

    // Constants
    // TODO: For some reason using size_type instead of size_t causes a linker error in string_view.test.cpp when compiling with GCC
    static PHI_CONSTEXPR_AND_CONST size_t npos = std::numeric_limits<size_t>::max();

    // Constructors
    PHI_CONSTEXPR basic_string_view() PHI_NOEXCEPT : m_Data(nullptr), m_Length(0u)
    {}

    basic_string_view(const basic_string_view& other) = default;

    basic_string_view(basic_string_view&& other) = default;

    template <size_t Size>
    PHI_CONSTEXPR basic_string_view(CharT (&array)[Size]) PHI_NOEXCEPT : m_Data{array},
                                                                         m_Length{Size}
    {}

    template <size_t Size>
    PHI_CONSTEXPR basic_string_view(const array<CharT, Size>& array) PHI_NOEXCEPT
        : m_Data{array.data()},
          m_Length{array.size()}
    {}

    PHI_EXTENDED_CONSTEXPR basic_string_view(const CharT* string) PHI_NOEXCEPT
        : m_Data(string),
          m_Length(string_length(string))
    {}

    PHI_EXTENDED_CONSTEXPR basic_string_view(const CharT* string, size_type count) PHI_NOEXCEPT
        : m_Data(string),
          m_Length(count)
    {}

    PHI_EXTENDED_CONSTEXPR basic_string_view(const std::basic_string_view<CharT, TraitsT>& other)
            PHI_NOEXCEPT : m_Data{other.data()},
                           m_Length{other.length()}
    {}

    PHI_EXTENDED_CONSTEXPR basic_string_view(std::basic_string_view<CharT, TraitsT>&& other)
            PHI_NOEXCEPT : m_Data{other.data()},
                           m_Length{other.length()}
    {}

    template <typename AllocatorT>
    PHI_EXTENDED_CONSTEXPR basic_string_view(
            const std::basic_string<CharT, TraitsT, AllocatorT>& other) PHI_NOEXCEPT
        : m_Data{other.data()},
          m_Length{other.length()}
    {}

    template <typename AllocatorT>
    PHI_EXTENDED_CONSTEXPR basic_string_view(std::basic_string<CharT, TraitsT, AllocatorT>&& other)
            PHI_NOEXCEPT : m_Data{other.data()},
                           m_Length{other.length()}
    {}

    PHI_CONSTEXPR basic_string_view(nullptr_t) PHI_NOEXCEPT : m_Data{nullptr}, m_Length{0u}
    {}

    ~basic_string_view() = default;

    basic_string_view& operator=(const basic_string_view& other) = default;

    basic_string_view& operator=(basic_string_view&& other) = default;

    template <size_t Size>
    PHI_EXTENDED_CONSTEXPR basic_string_view& operator=(CharT (&array)[Size]) PHI_NOEXCEPT
    {
        m_Data   = array;
        m_Length = Size;

        return *this;
    }

    template <size_t Size>
    PHI_EXTENDED_CONSTEXPR basic_string_view& operator=(const array<CharT, Size>& array)
            PHI_NOEXCEPT
    {
        m_Data   = array.data();
        m_Length = Size;

        return *this;
    }

    PHI_EXTENDED_CONSTEXPR basic_string_view& operator=(nullptr_t) PHI_NOEXCEPT
    {
        m_Data   = nullptr;
        m_Length = 0u;

        return *this;
    }

    PHI_EXTENDED_CONSTEXPR operator std::basic_string_view<CharT, TraitsT>() const PHI_NOEXCEPT
    {
        return std::basic_string_view<CharT, TraitsT>(data(), length().unsafe());
    }

    // Iterators

    PHI_NODISCARD PHI_CONSTEXPR iterator begin() const PHI_NOEXCEPT
    {
        return m_Data;
    }

    PHI_NODISCARD PHI_CONSTEXPR iterator end() const PHI_NOEXCEPT
    {
        return m_Data + m_Length.unsafe();
    }

    PHI_NODISCARD PHI_CONSTEXPR const_iterator cbegin() const PHI_NOEXCEPT
    {
        return m_Data;
    }

    PHI_NODISCARD PHI_CONSTEXPR const_iterator cend() const PHI_NOEXCEPT
    {
        return m_Data + m_Length.unsafe();
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
        return m_Length;
    }

    PHI_NODISCARD PHI_CONSTEXPR size_type bytes_length() const PHI_NOEXCEPT
    {
        return m_Length * sizeof(CharT);
    }

    PHI_NODISCARD PHI_CONSTEXPR size_type max_length() const PHI_NOEXCEPT
    {
        return std::numeric_limits<size_type>::max();
    }

    PHI_NODISCARD PHI_CONSTEXPR boolean is_null() const PHI_NOEXCEPT
    {
        return m_Data == nullptr;
    }

    PHI_NODISCARD PHI_CONSTEXPR boolean is_empty() const PHI_NOEXCEPT
    {
        return m_Length == 0u;
    }

    PHI_NODISCARD PHI_CONSTEXPR boolean is_null_terminated() const PHI_NOEXCEPT
    {
        return m_Length > 0u && back() == '\0';
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

    PHI_EXTENDED_CONSTEXPR basic_string_view& clear() PHI_NOEXCEPT
    {
        m_Data   = nullptr;
        m_Length = 0u;

        return *this;
    }

    PHI_EXTENDED_CONSTEXPR basic_string_view& add_prefix(size_type count) PHI_NOEXCEPT
    {
        m_Data -= count.unsafe();
        m_Length += count;

        return *this;
    }

    PHI_EXTENDED_CONSTEXPR basic_string_view& add_postfix(size_type count) PHI_NOEXCEPT
    {
        m_Length += count;

        return *this;
    }

    PHI_EXTENDED_CONSTEXPR basic_string_view& remove_prefix(size_type count) PHI_NOEXCEPT
    {
        PHI_ASSERT(count <= length(), "Cannot remove more than size");

        m_Data += count.unsafe();
        m_Length -= count;

        return *this;
    }

    PHI_EXTENDED_CONSTEXPR basic_string_view& remove_suffix(size_type count) PHI_NOEXCEPT
    {
        PHI_ASSERT(count <= length(), "Cannot remove more than size");

        m_Length -= count;

        return *this;
    }

    PHI_EXTENDED_CONSTEXPR basic_string_view& resize(size_type new_size) PHI_NOEXCEPT
    {
        m_Length = new_size;

        return *this;
    }

    PHI_EXTENDED_CONSTEXPR void swap(basic_string_view& other) PHI_NOEXCEPT
    {
        const basic_string_view tmp(other);
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

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR basic_string_view
    substring_view(size_type pos = 0u, size_type count = npos) const PHI_NOEXCEPT
    {
        PHI_ASSERT(pos <= length(), "Invalid position");

        return basic_string_view(data() + pos.unsafe(), min(count, length() - pos));
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR basic_string_view
    substring_view(iterator begin_iterator, iterator end_iterator) const PHI_NOEXCEPT
    {
        PHI_ASSERT(begin_iterator >= begin() && begin_iterator <= end(),
                   "Invalid position for begin_iterator");
        PHI_ASSERT(end_iterator >= begin() && end_iterator <= end(),
                   "Invalid position for end_iterator");
        PHI_ASSERT(end_iterator >= begin_iterator, "Invalid iterator position for end_iterator");

        return basic_string_view(begin_iterator, static_cast<typename size_type::value_type>(
                                                         end_iterator - begin_iterator));
    }

    // Comparing

    PHI_NODISCARD PHI_CONSTEXPR i32 compare(basic_string_view other) const PHI_NOEXCEPT
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
                                            basic_string_view other) const PHI_NOEXCEPT
    {
        return substring_view(pos, count).compare(other);
    }

    PHI_NODISCARD PHI_CONSTEXPR i32 compare(size_type pos1, size_type count1,
                                            basic_string_view other, size_type pos2,
                                            size_type count2) const PHI_NOEXCEPT
    {
        return substring_view(pos1, count1).compare(other.substring_view(pos2, count2));
    }

    PHI_NODISCARD PHI_CONSTEXPR i32 compare(const CharT* string) const PHI_NOEXCEPT
    {
        return compare(basic_string_view(string));
    }

    PHI_NODISCARD PHI_CONSTEXPR i32 compare(size_type pos, size_type count,
                                            const CharT* string) const PHI_NOEXCEPT
    {
        return substring_view(pos, count).compare(basic_string_view(string));
    }

    PHI_NODISCARD PHI_CONSTEXPR i32 compare(size_type pos, size_type count1, const CharT* string,
                                            size_type count2) const PHI_NOEXCEPT
    {
        return substring_view(pos, count1).compare(basic_string_view(string, count2));
    }

    // Searching

    PHI_NODISCARD PHI_CONSTEXPR boolean starts_with(basic_string_view view) const PHI_NOEXCEPT
    {
        return length() >= view.length() && compare(0u, view.length(), view) == 0;
    }

    PHI_NODISCARD PHI_CONSTEXPR boolean starts_with(CharT character) const PHI_NOEXCEPT
    {
        return starts_with(basic_string_view(&character, 1u));
    }

    PHI_NODISCARD PHI_CONSTEXPR boolean starts_with(const CharT* string) const PHI_NOEXCEPT
    {
        return starts_with(basic_string_view(string));
    }

    PHI_NODISCARD PHI_CONSTEXPR boolean ends_with(basic_string_view view) const PHI_NOEXCEPT
    {
        return length() >= view.length() && compare(length() - view.length(), npos, view) == 0;
    }

    PHI_NODISCARD PHI_CONSTEXPR boolean ends_with(CharT character) const PHI_NOEXCEPT
    {
        return ends_with(basic_string_view(&character, 1u));
    }

    PHI_NODISCARD PHI_CONSTEXPR boolean ends_with(const CharT* string) const PHI_NOEXCEPT
    {
        return ends_with(basic_string_view(string));
    }

    // contains

    PHI_NODISCARD PHI_CONSTEXPR boolean contains(basic_string_view view) const PHI_NOEXCEPT
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

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR size_type find(basic_string_view view,
                                                        size_type pos = 0u) const PHI_NOEXCEPT
    {
        PHI_ASSERT(view.length() == 0u || view.data() != nullptr, "Invalid argument view");

        return pos >= length() ? npos :
                                 to_pos(std::search(cbegin() + pos, cend(), view.cbegin(),
                                                    view.cend(), TraitsT::eq));
    }

    PHI_NODISCARD PHI_CONSTEXPR size_type find(CharT     character,
                                               size_type pos = 0u) const PHI_NOEXCEPT
    {
        return find(basic_string_view(&character, 1u), pos);
    }

    PHI_NODISCARD PHI_CONSTEXPR size_type find(const CharT* string,
                                               size_type    pos = 0u) const PHI_NOEXCEPT
    {
        return find(basic_string_view(string), pos);
    }

    PHI_NODISCARD PHI_CONSTEXPR size_type find(const CharT* string, size_type pos,
                                               size_type count) const PHI_NOEXCEPT
    {
        return find(basic_string_view(string, count), pos);
    }

    // rfind

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR size_type rfind(basic_string_view view,
                                                         size_type pos = npos) const PHI_NOEXCEPT
    {
        if (length() < view.length())
        {
            return npos;
        }

        if (view.empty())
        {
            return min(length(), pos);
        }

        const_iterator last   = cbegin() + min(length() - view.length(), pos) + view.length();
        const_iterator result = find_end(cbegin(), last, view.cbegin(), view.cend(), TraitsT::eq);

        if (result != last)
        {
            return size_type(result - cbegin());
        }

        return npos;
    }

    PHI_NODISCARD PHI_CONSTEXPR size_type rfind(CharT     character,
                                                size_type pos = npos) const PHI_NOEXCEPT
    {
        return rfind(basic_string_view(&character, 1u), pos);
    }

    PHI_NODISCARD PHI_CONSTEXPR size_type rfind(const CharT* string,
                                                size_type    pos = npos) const PHI_NOEXCEPT
    {
        return rfind(basic_string_view(string), pos);
    }

    PHI_NODISCARD PHI_CONSTEXPR size_type rfind(const CharT* string, size_type pos,
                                                size_type count) const PHI_NOEXCEPT
    {
        return rfind(basic_string_view(string, count), pos);
    }

    PHI_NODISCARD PHI_CONSTEXPR size_type find_first_of(basic_string_view view,
                                                        size_type pos = 0u) const PHI_NOEXCEPT
    {
        return pos >= length() ? npos :
                                 to_pos(std::find_first_of(cbegin() + pos, cend(), view.cbegin(),
                                                           view.cend(), TraitsT::eq));
    }

    PHI_NODISCARD PHI_CONSTEXPR size_type find_first_of(CharT     character,
                                                        size_type pos = 0u) const PHI_NOEXCEPT
    {
        return find_first_of(basic_string_view(&character, 1u), pos);
    }

    PHI_NODISCARD PHI_CONSTEXPR size_type find_first_of(const CharT* string,
                                                        size_type    pos = 0u) const PHI_NOEXCEPT
    {
        return find_first_of(basic_string_view(string), pos);
    }

    PHI_NODISCARD PHI_CONSTEXPR size_type find_first_of(const CharT* string, size_type pos,
                                                        size_type count) const PHI_NOEXCEPT
    {
        return find_first_of(basic_string_view(string, count), pos);
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR size_type
    find_last_of(basic_string_view view, size_type pos = npos) const PHI_NOEXCEPT
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
        return find_last_of(basic_string_view(&character, 1u), pos);
    }

    PHI_NODISCARD PHI_CONSTEXPR size_type find_last_of(const CharT* string,
                                                       size_type    pos = npos) const PHI_NOEXCEPT
    {
        return find_last_of(basic_string_view(string), pos);
    }

    PHI_NODISCARD PHI_CONSTEXPR size_type find_last_of(const CharT* string, size_type pos,
                                                       size_type count) const PHI_NOEXCEPT
    {
        return find_last_of(basic_string_view(string, count), pos);
    }

    PHI_NODISCARD PHI_CONSTEXPR size_type find_first_not_of(basic_string_view view,
                                                            size_type pos = 0u) const PHI_NOEXCEPT
    {
        return pos >= length() ? npos :
                                 to_pos(std::find_if(cbegin() + pos, cend(), not_in_view(view)));
    }

    PHI_NODISCARD PHI_CONSTEXPR size_type find_first_not_of(CharT     character,
                                                            size_type pos = 0u) const PHI_NOEXCEPT
    {
        return find_first_not_of(basic_string_view(&character, 1u), pos);
    }

    PHI_NODISCARD PHI_CONSTEXPR size_type find_first_not_of(const CharT* string,
                                                            size_type pos = 0u) const PHI_NOEXCEPT
    {
        return find_first_not_of(basic_string_view(string), pos);
    }

    PHI_NODISCARD PHI_CONSTEXPR size_type find_first_not_of(const CharT* string, size_type pos,
                                                            size_type count) const PHI_NOEXCEPT
    {
        return find_first_not_of(basic_string_view(string, count), pos);
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR size_type
    find_last_not_of(basic_string_view view, size_type pos = npos) const PHI_NOEXCEPT
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
        return find_last_not_of(basic_string_view(&character, 1u), pos);
    }

    PHI_NODISCARD PHI_CONSTEXPR size_type find_last_not_of(const CharT* string,
                                                           size_type pos = npos) const PHI_NOEXCEPT
    {
        return find_last_not_of(basic_string_view(string), pos);
    }

    PHI_NODISCARD PHI_CONSTEXPR size_type find_last_not_of(const CharT* string, size_type pos,
                                                           size_type count) const PHI_NOEXCEPT
    {
        return find_last_not_of(basic_string_view(string, count), pos);
    }

private:
    struct not_in_view
    {
        const basic_string_view view;

        PHI_CONSTEXPR explicit not_in_view(basic_string_view other) PHI_NOEXCEPT : view(other)
        {}

        PHI_NODISCARD PHI_CONSTEXPR boolean operator()(CharT character) const PHI_NOEXCEPT
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

    const CharT* m_Data;
    usize        m_Length;
};

PHI_GCC_SUPPRESS_WARNING_POP()

// Comparison functions

template <typename CharT, typename TraitsT>
PHI_CONSTEXPR boolean operator==(basic_string_view<CharT, TraitsT> lhs,
                                 basic_string_view<CharT, TraitsT> rhs) PHI_NOEXCEPT
{
    return lhs.is_null() == rhs.is_null() && lhs.length() == rhs.length() && lhs.compare(rhs) == 0;
}

template <typename CharT, typename TraitsT>
PHI_CONSTEXPR boolean operator!=(basic_string_view<CharT, TraitsT> lhs,
                                 basic_string_view<CharT, TraitsT> rhs) PHI_NOEXCEPT
{
    return !(lhs == rhs);
}

template <typename CharT, typename TraitsT>
PHI_CONSTEXPR boolean operator<(basic_string_view<CharT, TraitsT> lhs,
                                basic_string_view<CharT, TraitsT> rhs) PHI_NOEXCEPT
{
    return lhs.compare(rhs) < 0;
}

template <typename CharT, typename TraitsT>
PHI_CONSTEXPR boolean operator<=(basic_string_view<CharT, TraitsT> lhs,
                                 basic_string_view<CharT, TraitsT> rhs) PHI_NOEXCEPT
{
    return lhs.compare(rhs) <= 0;
}

template <typename CharT, typename TraitsT>
PHI_CONSTEXPR boolean operator>(basic_string_view<CharT, TraitsT> lhs,
                                basic_string_view<CharT, TraitsT> rhs) PHI_NOEXCEPT
{
    return lhs.compare(rhs) > 0;
}

template <typename CharT, typename TraitsT>
PHI_CONSTEXPR boolean operator>=(basic_string_view<CharT, TraitsT> lhs,
                                 basic_string_view<CharT, TraitsT> rhs) PHI_NOEXCEPT
{
    return lhs.compare(rhs) >= 0;
}

// ==

template <typename CharT, typename TraitsT>
PHI_CONSTEXPR boolean operator==(basic_string_view<CharT, TraitsT> lhs,
                                 const CharT*                      rhs) PHI_NOEXCEPT
{
    return lhs.is_null() == (rhs == nullptr) && lhs.length() == string_length(rhs) &&
           lhs.compare(rhs) == 0;
}

template <typename CharT, typename TraitsT>
PHI_CONSTEXPR boolean operator==(const CharT*                      lhs,
                                 basic_string_view<CharT, TraitsT> rhs) PHI_NOEXCEPT
{
    return (lhs == nullptr) == rhs.is_null() && string_length(lhs) == rhs.length() &&
           rhs.compare(lhs) == 0;
}

template <typename CharT, typename TraitsT>
PHI_CONSTEXPR boolean operator==(basic_string_view<CharT, TraitsT> lhs, nullptr_t) PHI_NOEXCEPT
{
    return lhs.is_null();
}

template <typename CharT, typename TraitsT>
PHI_CONSTEXPR boolean operator==(nullptr_t, basic_string_view<CharT, TraitsT> rhs) PHI_NOEXCEPT
{
    return rhs.is_null();
}

template <typename CharT, typename TraitsT>
PHI_CONSTEXPR boolean operator==(basic_string_view<CharT, TraitsT> lhs,
                                 std::basic_string<CharT, TraitsT> rhs) PHI_NOEXCEPT
{
    return lhs.is_null() == (rhs.data() == nullptr) && lhs.length() == rhs.length() &&
           lhs.compare(rhs) == 0;
}

template <typename CharT, typename TraitsT>
PHI_CONSTEXPR boolean operator==(std::basic_string<CharT, TraitsT> lhs,
                                 basic_string_view<CharT, TraitsT> rhs) PHI_NOEXCEPT
{
    return (lhs.data() == nullptr) == rhs.is_null() && lhs.length() == rhs.length() &&
           rhs.compare(lhs) == 0;
}

// !=

template <typename CharT, typename TraitsT>
PHI_CONSTEXPR boolean operator!=(basic_string_view<CharT, TraitsT> lhs,
                                 const CharT*                      rhs) PHI_NOEXCEPT
{
    return !(lhs == rhs);
}

template <typename CharT, typename TraitsT>
PHI_CONSTEXPR boolean operator!=(const CharT*                      lhs,
                                 basic_string_view<CharT, TraitsT> rhs) PHI_NOEXCEPT
{
    return !(lhs == rhs);
}

template <typename CharT, typename TraitsT>
PHI_CONSTEXPR boolean operator!=(basic_string_view<CharT, TraitsT> lhs, nullptr_t) PHI_NOEXCEPT
{
    return !lhs.is_null();
}

template <typename CharT, typename TraitsT>
PHI_CONSTEXPR boolean operator!=(nullptr_t, basic_string_view<CharT, TraitsT> rhs) PHI_NOEXCEPT
{
    return !rhs.is_null();
}

template <typename CharT, typename TraitsT>
PHI_CONSTEXPR boolean operator!=(basic_string_view<CharT, TraitsT> lhs,
                                 std::basic_string<CharT, TraitsT> rhs) PHI_NOEXCEPT
{
    return !(lhs == rhs);
}

template <typename CharT, typename TraitsT>
PHI_CONSTEXPR boolean operator!=(std::basic_string<CharT, TraitsT> rhs,
                                 basic_string_view<CharT, TraitsT> lhs) PHI_NOEXCEPT
{
    return !(lhs == rhs);
}

// <

template <typename CharT, typename TraitsT>
PHI_CONSTEXPR boolean operator<(basic_string_view<CharT, TraitsT> lhs,
                                const CharT*                      rhs) PHI_NOEXCEPT
{
    return lhs.compare(rhs) < 0;
}

template <typename CharT, typename TraitsT>
PHI_CONSTEXPR boolean operator<(const CharT*                      lhs,
                                basic_string_view<CharT, TraitsT> rhs) PHI_NOEXCEPT
{
    return rhs.compare(lhs) > 0;
}

template <typename CharT, typename TraitsT>
PHI_CONSTEXPR boolean operator<(basic_string_view<CharT, TraitsT> lhs,
                                std::basic_string<CharT, TraitsT> rhs) PHI_NOEXCEPT
{
    return lhs.compare(rhs) < 0;
}

template <typename CharT, typename TraitsT>
PHI_CONSTEXPR boolean operator<(std::basic_string<CharT, TraitsT> rhs,
                                basic_string_view<CharT, TraitsT> lhs) PHI_NOEXCEPT
{
    return rhs.compare(lhs) > 0;
}

// <=

template <typename CharT, typename TraitsT>
PHI_CONSTEXPR boolean operator<=(basic_string_view<CharT, TraitsT> lhs,
                                 const CharT*                      rhs) PHI_NOEXCEPT
{
    return lhs.compare(rhs) <= 0;
}

template <typename CharT, typename TraitsT>
PHI_CONSTEXPR boolean operator<=(const CharT*                      lhs,
                                 basic_string_view<CharT, TraitsT> rhs) PHI_NOEXCEPT
{
    return rhs.compare(lhs) >= 0;
}

template <typename CharT, typename TraitsT>
PHI_CONSTEXPR boolean operator<=(basic_string_view<CharT, TraitsT> lhs,
                                 std::basic_string<CharT, TraitsT> rhs) PHI_NOEXCEPT
{
    return lhs.compare(rhs) <= 0;
}

template <typename CharT, typename TraitsT>
PHI_CONSTEXPR boolean operator<=(std::basic_string<CharT, TraitsT> rhs,
                                 basic_string_view<CharT, TraitsT> lhs) PHI_NOEXCEPT
{
    return rhs.compare(lhs) >= 0;
}

// >

template <typename CharT, typename TraitsT>
PHI_CONSTEXPR boolean operator>(basic_string_view<CharT, TraitsT> lhs,
                                const CharT*                      rhs) PHI_NOEXCEPT
{
    return lhs.compare(rhs) > 0;
}

template <typename CharT, typename TraitsT>
PHI_CONSTEXPR boolean operator>(const CharT*                      lhs,
                                basic_string_view<CharT, TraitsT> rhs) PHI_NOEXCEPT
{
    return rhs.compare(lhs) < 0;
}

template <typename CharT, typename TraitsT>
PHI_CONSTEXPR boolean operator>(basic_string_view<CharT, TraitsT> lhs,
                                std::basic_string<CharT, TraitsT> rhs) PHI_NOEXCEPT
{
    return lhs.compare(rhs) > 0;
}

template <typename CharT, typename TraitsT>
PHI_CONSTEXPR boolean operator>(std::basic_string<CharT, TraitsT> rhs,
                                basic_string_view<CharT, TraitsT> lhs) PHI_NOEXCEPT
{
    return rhs.compare(lhs) < 0;
}

// >=

template <typename CharT, typename TraitsT>
PHI_CONSTEXPR boolean operator>=(basic_string_view<CharT, TraitsT> lhs,
                                 const CharT*                      rhs) PHI_NOEXCEPT
{
    return lhs.compare(rhs) >= 0;
}

template <typename CharT, typename TraitsT>
PHI_CONSTEXPR boolean operator>=(const CharT*                      lhs,
                                 basic_string_view<CharT, TraitsT> rhs) PHI_NOEXCEPT
{
    return rhs.compare(lhs) <= 0;
}

template <typename CharT, typename TraitsT>
PHI_CONSTEXPR boolean operator>=(basic_string_view<CharT, TraitsT> lhs,
                                 std::basic_string<CharT, TraitsT> rhs) PHI_NOEXCEPT
{
    return lhs.compare(rhs) >= 0;
}

template <typename CharT, typename TraitsT>
PHI_CONSTEXPR boolean operator>=(std::basic_string<CharT, TraitsT> rhs,
                                 basic_string_view<CharT, TraitsT> lhs) PHI_NOEXCEPT
{
    return rhs.compare(lhs) <= 0;
}

// Typedefs

using string_view    = basic_string_view<char>;
using wstring_view   = basic_string_view<wchar_t>;
using u8string_view  = basic_string_view<char8_t>;
using u16string_view = basic_string_view<char16_t>;
using u32string_view = basic_string_view<char32_t>;

#if PHI_CPP_STANDARD_IS_BELOW(17)
template <typename CharT, typename TraitsT>
// NOLINTNEXTLINE(readability-redundant-declaration)
PHI_CONSTEXPR size_t basic_string_view<CharT, TraitsT>::npos;
#endif

template <typename CharT, typename TraitsT /*= std::char_traits<CharT>*/>
class PHI_ATTRIBUTE_POINTER not_null_basic_string_view
{
public:
    using this_type              = not_null_basic_string_view<CharT, TraitsT>;
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
                  "phi::basic_string_view: Character type must not be an array");
#if PHI_HAS_WORKING_IS_STANDARD_LAYOUT()
    static_assert(is_standard_layout<value_type>::value,
                  "phi::basic_string_view: Character type must be standard-layout");
#endif
#if PHI_HAS_WORKING_IS_TRIVIAL()
    static_assert(is_trivial<value_type>::value,
                  "phi::basic_string_view: Character type must be trivial");
#endif
    static_assert(is_same<value_type, typename traits_type::char_type>::value,
                  "phi::basic_string_view: CharT must be the same type as traits_type::char_type");

    // Constants
    // TODO: For some reason using size_type instead of size_t causes a linker error in string_view.test.cpp when compiling with GCC
    static PHI_CONSTEXPR size_t npos = std::numeric_limits<size_t>::max();

    // Constructors
    not_null_basic_string_view() = delete;

    not_null_basic_string_view(const not_null_basic_string_view& other) = default;

    not_null_basic_string_view(not_null_basic_string_view&& other) = default;

    template <size_t Size>
    PHI_CONSTEXPR PHI_ATTRIBUTE_NONNULL not_null_basic_string_view(CharT (&array)[Size])
            PHI_NOEXCEPT : m_Data{array},
                           m_Length{Size}
    {
        PHI_ASSERT(m_Data != nullptr, "Invalid data pointer");
        PHI_ASSERT(m_Length > 0u, "Invalid length");
    }

    template <size_t Size>
    PHI_CONSTEXPR not_null_basic_string_view(const array<CharT, Size>& array) PHI_NOEXCEPT
        : m_Data{array.data()},
          m_Length{array.size()}
    {
        PHI_ASSERT(m_Data != nullptr, "Invalid data pointer");
        PHI_ASSERT(m_Length > 0u, "Invalid length");
    }

    PHI_EXTENDED_CONSTEXPR PHI_ATTRIBUTE_NONNULL not_null_basic_string_view(const CharT* string)
            PHI_NOEXCEPT : m_Data{string},
                           m_Length{string_length(string)}
    {
        PHI_ASSERT(m_Data != nullptr, "Invalid data pointer");
        PHI_ASSERT(m_Length > 0u, "Invalid length");
    }

    PHI_EXTENDED_CONSTEXPR PHI_ATTRIBUTE_NONNULL
    not_null_basic_string_view(const CharT* string, size_type count) PHI_NOEXCEPT : m_Data(string),
                                                                                    m_Length(count)
    {
        PHI_ASSERT(m_Data != nullptr, "Invalid data pointer");
        PHI_ASSERT(m_Length > 0u, "Invalid length");
    }

    not_null_basic_string_view(nullptr_t) = delete;

    ~not_null_basic_string_view() = default;

    not_null_basic_string_view& operator=(const not_null_basic_string_view& other) = default;

    not_null_basic_string_view& operator=(not_null_basic_string_view&& other) = default;

    template <size_t Size>
    PHI_EXTENDED_CONSTEXPR PHI_ATTRIBUTE_NONNULL not_null_basic_string_view& operator=(
            CharT (&array)[Size]) PHI_NOEXCEPT
    {
        m_Data   = array;
        m_Length = Size;

        PHI_ASSERT(m_Data != nullptr, "Invalid data pointer");
        PHI_ASSERT(m_Length > 0u, "Invalid length");

        return *this;
    }

    template <size_t Size>
    PHI_EXTENDED_CONSTEXPR not_null_basic_string_view& operator=(const array<CharT, Size>& array)
            PHI_NOEXCEPT
    {
        m_Data   = array.data();
        m_Length = Size;

        PHI_ASSERT(m_Data != nullptr, "Invalid data pointer");
        PHI_ASSERT(m_Length > 0u, "Invalid length");

        return *this;
    }

    not_null_basic_string_view& operator=(nullptr_t) = delete;

    // Iterators

    PHI_NODISCARD PHI_ATTRIBUTE_RETURNS_NONNULL PHI_CONSTEXPR iterator begin() const PHI_NOEXCEPT
    {
        return m_Data;
    }

    PHI_NODISCARD PHI_ATTRIBUTE_RETURNS_NONNULL PHI_CONSTEXPR iterator end() const PHI_NOEXCEPT
    {
        return m_Data + m_Length.unsafe();
    }

    PHI_NODISCARD PHI_ATTRIBUTE_RETURNS_NONNULL PHI_CONSTEXPR const_iterator
    cbegin() const PHI_NOEXCEPT
    {
        return m_Data;
    }

    PHI_NODISCARD PHI_ATTRIBUTE_RETURNS_NONNULL PHI_CONSTEXPR const_iterator
    cend() const PHI_NOEXCEPT
    {
        return m_Data + m_Length.unsafe();
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
        return m_Length;
    }

    PHI_NODISCARD PHI_CONSTEXPR size_type max_length() const PHI_NOEXCEPT
    {
        return std::numeric_limits<size_type>::max();
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

    PHI_NODISCARD PHI_ATTRIBUTE_RETURNS_NONNULL PHI_CONSTEXPR const_pointer
    data() const PHI_NOEXCEPT
    {
        return m_Data;
    }

    // Modifiers

    PHI_EXTENDED_CONSTEXPR not_null_basic_string_view& add_prefix(size_type count) PHI_NOEXCEPT
    {
        m_Data -= count.unsafe();
        m_Length += count;

        PHI_ASSERT(m_Data != nullptr, "Invalid data pointer");
        PHI_ASSERT(m_Length > 0u, "Invalid length");

        return *this;
    }

    PHI_EXTENDED_CONSTEXPR not_null_basic_string_view& add_postfix(size_type count) PHI_NOEXCEPT
    {
        m_Length += count;

        return *this;
    }

    PHI_EXTENDED_CONSTEXPR not_null_basic_string_view& remove_prefix(size_type count) PHI_NOEXCEPT
    {
        PHI_ASSERT(count <= length(), "Cannot remove more than size");

        m_Data += count.unsafe();
        m_Length -= count;

        PHI_ASSERT(m_Data != nullptr, "Invalid data pointer");
        PHI_ASSERT(m_Length > 0u, "Invalid length");

        return *this;
    }

    PHI_EXTENDED_CONSTEXPR not_null_basic_string_view& remove_suffix(size_type count) PHI_NOEXCEPT
    {
        PHI_ASSERT(count <= length(), "Cannot remove more than size");

        m_Length -= count;

        PHI_ASSERT(m_Data != nullptr, "Invalid data pointer");
        PHI_ASSERT(m_Length > 0u, "Invalid length");

        return *this;
    }

    PHI_EXTENDED_CONSTEXPR not_null_basic_string_view& resize(size_type new_size) PHI_NOEXCEPT
    {
        m_Length = new_size;

        PHI_ASSERT(m_Data != nullptr, "Invalid data pointer");
        PHI_ASSERT(m_Length > 0u, "Invalid length");

        return *this;
    }

    PHI_EXTENDED_CONSTEXPR void swap(not_null_basic_string_view& other) PHI_NOEXCEPT
    {
        const not_null_basic_string_view tmp(other);
        other = *this;
        *this = tmp;

        PHI_ASSERT(m_Data != nullptr, "Invalid data pointer");
        PHI_ASSERT(m_Length > 0u, "Invalid length");
    }

    // String operations

    PHI_EXTENDED_CONSTEXPR PHI_ATTRIBUTE_NONNULL size_type
    copy(CharT* destination, size_type count, size_type pos = 0u) const PHI_NOEXCEPT
    {
        PHI_ASSERT(pos <= length(), "Invalid position");

        const size_type rlen = min(count, length() - pos);
        TraitsT::copy(destination, data() + pos.unsafe(), rlen.unsafe());

        PHI_ASSERT(m_Data != nullptr, "Invalid data pointer");
        PHI_ASSERT(m_Length > 0u, "Invalid length");

        return rlen;
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR not_null_basic_string_view
    substring_view(size_type pos = 0u, size_type count = npos) const PHI_NOEXCEPT
    {
        PHI_ASSERT(pos <= length(), "Invalid position");

        return basic_string_view<CharT>(data() + pos.unsafe(), min(count, length() - pos));
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR PHI_ATTRIBUTE_NONNULL not_null_basic_string_view
    substring_view(iterator begin_iterator, iterator end_iterator) const PHI_NOEXCEPT
    {
        PHI_ASSERT(begin_iterator >= begin() && begin_iterator <= end(),
                   "Invalid position for begin_iterator");
        PHI_ASSERT(end_iterator >= begin() && end_iterator <= end(),
                   "Invalid position for end_iterator");
        PHI_ASSERT(end_iterator >= begin_iterator, "Invalid iterator position for end_iterator");

        return basic_string_view<CharT>(begin_iterator, static_cast<typename size_type::value_type>(
                                                                end_iterator - begin_iterator));
    }

    // Comparing

    PHI_NODISCARD PHI_CONSTEXPR i32 compare(not_null_basic_string_view other) const PHI_NOEXCEPT
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
                                            not_null_basic_string_view other) const PHI_NOEXCEPT
    {
        return substring_view(pos, count).compare(other);
    }

    PHI_NODISCARD PHI_CONSTEXPR i32 compare(size_type pos1, size_type count1,
                                            not_null_basic_string_view other, size_type pos2,
                                            size_type count2) const PHI_NOEXCEPT
    {
        return substring_view(pos1, count1).compare(other.substring_view(pos2, count2));
    }

    PHI_NODISCARD PHI_ATTRIBUTE_NONNULL PHI_CONSTEXPR i32
    compare(const CharT* string) const PHI_NOEXCEPT
    {
        return compare(basic_string_view<CharT>(string));
    }

    PHI_NODISCARD PHI_ATTRIBUTE_NONNULL PHI_CONSTEXPR i32
    compare(size_type pos, size_type count, const CharT* string) const PHI_NOEXCEPT
    {
        return substring_view(pos, count).compare(basic_string_view<CharT>(string));
    }

    PHI_NODISCARD PHI_ATTRIBUTE_NONNULL PHI_CONSTEXPR i32
    compare(size_type pos, size_type count1, const CharT* string,
            size_type count2) const PHI_NOEXCEPT
    {
        return substring_view(pos, count1).compare(basic_string_view<CharT>(string, count2));
    }

    // Searching

    PHI_NODISCARD PHI_CONSTEXPR boolean
    starts_with(not_null_basic_string_view view) const PHI_NOEXCEPT
    {
        return length() >= view.length() && compare(0u, view.length(), view) == 0;
    }

    PHI_NODISCARD PHI_CONSTEXPR boolean starts_with(CharT character) const PHI_NOEXCEPT
    {
        return starts_with(basic_string_view<CharT>(&character, 1u));
    }

    PHI_NODISCARD PHI_ATTRIBUTE_NONNULL PHI_CONSTEXPR boolean
    starts_with(const CharT* string) const PHI_NOEXCEPT
    {
        return starts_with(basic_string_view<CharT>(string));
    }

    PHI_NODISCARD PHI_CONSTEXPR boolean
    ends_with(not_null_basic_string_view view) const PHI_NOEXCEPT
    {
        return length() >= view.length() && compare(length() - view.length(), npos, view) == 0;
    }

    PHI_NODISCARD PHI_CONSTEXPR boolean ends_with(CharT character) const PHI_NOEXCEPT
    {
        return ends_with(basic_string_view<CharT>(&character, 1u));
    }

    PHI_NODISCARD PHI_ATTRIBUTE_NONNULL PHI_CONSTEXPR boolean
    ends_with(const CharT* string) const PHI_NOEXCEPT
    {
        return ends_with(basic_string_view<CharT>(string));
    }

    // contains

    PHI_NODISCARD PHI_CONSTEXPR boolean contains(not_null_basic_string_view view) const PHI_NOEXCEPT
    {
        return find(view) != npos;
    }

    PHI_NODISCARD PHI_CONSTEXPR boolean contains(CharT character) const PHI_NOEXCEPT
    {
        return find(character) != npos;
    }

    PHI_NODISCARD PHI_ATTRIBUTE_NONNULL PHI_CONSTEXPR boolean
    contains(const CharT* string) const PHI_NOEXCEPT
    {
        return find(string) != npos;
    }

    PHI_NODISCARD PHI_CONSTEXPR boolean is_null_terminated() const PHI_NOEXCEPT
    {
        return back() == '\0';
    }

    // find

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR size_type find(not_null_basic_string_view view,
                                                        size_type pos = 0u) const PHI_NOEXCEPT
    {
        PHI_ASSERT(view.length() == 0u || view.data() != nullptr, "Invalid argument view");

        return pos >= length() ? npos :
                                 to_pos(std::search(cbegin() + pos, cend(), view.cbegin(),
                                                    view.cend(), TraitsT::eq));
    }

    PHI_NODISCARD PHI_CONSTEXPR size_type find(CharT     character,
                                               size_type pos = 0u) const PHI_NOEXCEPT
    {
        return find(basic_string_view<CharT>(&character, 1u), pos);
    }

    PHI_NODISCARD PHI_ATTRIBUTE_NONNULL PHI_CONSTEXPR size_type
    find(const CharT* string, size_type pos = 0u) const PHI_NOEXCEPT
    {
        return find(basic_string_view<CharT>(string), pos);
    }

    PHI_NODISCARD PHI_ATTRIBUTE_NONNULL PHI_CONSTEXPR size_type
    find(const CharT* string, size_type pos, size_type count) const PHI_NOEXCEPT
    {
        return find(basic_string_view<CharT>(string, count), pos);
    }

    // rfind

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR size_type rfind(not_null_basic_string_view view,
                                                         size_type pos = npos) const PHI_NOEXCEPT
    {
        if (length() < view.length())
        {
            return npos;
        }

        if (view.empty())
        {
            return min(length(), pos);
        }

        const_iterator last   = cbegin() + min(length() - view.length(), pos) + view.length();
        const_iterator result = find_end(cbegin(), last, view.cbegin(), view.cend(), TraitsT::eq);

        if (result != last)
        {
            return size_type(result - cbegin());
        }

        return npos;
    }

    PHI_NODISCARD PHI_CONSTEXPR size_type rfind(CharT     character,
                                                size_type pos = npos) const PHI_NOEXCEPT
    {
        return rfind(basic_string_view<CharT>(&character, 1u), pos);
    }

    PHI_NODISCARD PHI_ATTRIBUTE_NONNULL PHI_CONSTEXPR size_type
    rfind(const CharT* string, size_type pos = npos) const PHI_NOEXCEPT
    {
        return rfind(basic_string_view<CharT>(string), pos);
    }

    PHI_NODISCARD PHI_ATTRIBUTE_NONNULL PHI_CONSTEXPR size_type
    rfind(const CharT* string, size_type pos, size_type count) const PHI_NOEXCEPT
    {
        return rfind(basic_string_view<CharT>(string, count), pos);
    }

    PHI_NODISCARD PHI_CONSTEXPR size_type find_first_of(not_null_basic_string_view view,
                                                        size_type pos = 0u) const PHI_NOEXCEPT
    {
        return pos >= length() ? npos :
                                 to_pos(std::find_first_of(cbegin() + pos, cend(), view.cbegin(),
                                                           view.cend(), TraitsT::eq));
    }

    PHI_NODISCARD PHI_CONSTEXPR size_type find_first_of(CharT     character,
                                                        size_type pos = 0u) const PHI_NOEXCEPT
    {
        return find_first_of(basic_string_view<CharT>(&character, 1u), pos);
    }

    PHI_NODISCARD PHI_ATTRIBUTE_NONNULL PHI_CONSTEXPR size_type
    find_first_of(const CharT* string, size_type pos = 0u) const PHI_NOEXCEPT
    {
        return find_first_of(basic_string_view<CharT>(string), pos);
    }

    PHI_NODISCARD PHI_ATTRIBUTE_NONNULL PHI_CONSTEXPR size_type
    find_first_of(const CharT* string, size_type pos, size_type count) const PHI_NOEXCEPT
    {
        return find_first_of(basic_string_view<CharT>(string, count), pos);
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR size_type
    find_last_of(not_null_basic_string_view view, size_type pos = npos) const PHI_NOEXCEPT
    {
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
        return find_last_of(basic_string_view<CharT>(&character, 1u), pos);
    }

    PHI_NODISCARD PHI_ATTRIBUTE_NONNULL PHI_CONSTEXPR size_type
    find_last_of(const CharT* string, size_type pos = npos) const PHI_NOEXCEPT
    {
        return find_last_of(basic_string_view<CharT>(string), pos);
    }

    PHI_NODISCARD PHI_ATTRIBUTE_NONNULL PHI_CONSTEXPR size_type
    find_last_of(const CharT* string, size_type pos, size_type count) const PHI_NOEXCEPT
    {
        return find_last_of(basic_string_view<CharT>(string, count), pos);
    }

    PHI_NODISCARD PHI_CONSTEXPR size_type find_first_not_of(not_null_basic_string_view view,
                                                            size_type pos = 0u) const PHI_NOEXCEPT
    {
        return pos >= length() ? npos :
                                 to_pos(std::find_if(cbegin() + pos, cend(), not_in_view(view)));
    }

    PHI_NODISCARD PHI_CONSTEXPR size_type find_first_not_of(CharT     character,
                                                            size_type pos = 0u) const PHI_NOEXCEPT
    {
        return find_first_not_of(basic_string_view<CharT>(&character, 1u), pos);
    }

    PHI_NODISCARD PHI_ATTRIBUTE_NONNULL PHI_CONSTEXPR size_type
    find_first_not_of(const CharT* string, size_type pos = 0u) const PHI_NOEXCEPT
    {
        return find_first_not_of(basic_string_view<CharT>(string), pos);
    }

    PHI_NODISCARD PHI_ATTRIBUTE_NONNULL PHI_CONSTEXPR size_type
    find_first_not_of(const CharT* string, size_type pos, size_type count) const PHI_NOEXCEPT
    {
        return find_first_not_of(basic_string_view<CharT>(string, count), pos);
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR size_type
    find_last_not_of(not_null_basic_string_view view, size_type pos = npos) const PHI_NOEXCEPT
    {
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
        return find_last_not_of(basic_string_view<CharT>(&character, 1u), pos);
    }

    PHI_NODISCARD PHI_ATTRIBUTE_NONNULL PHI_CONSTEXPR size_type
    find_last_not_of(const CharT* string, size_type pos = npos) const PHI_NOEXCEPT
    {
        return find_last_not_of(basic_string_view<CharT>(string), pos);
    }

    PHI_NODISCARD PHI_ATTRIBUTE_NONNULL PHI_CONSTEXPR size_type
    find_last_not_of(const CharT* string, size_type pos, size_type count) const PHI_NOEXCEPT
    {
        return find_last_not_of(basic_string_view<CharT>(string, count), pos);
    }

private:
    struct not_in_view
    {
        const not_null_basic_string_view view;

        PHI_CONSTEXPR explicit not_in_view(not_null_basic_string_view other) PHI_NOEXCEPT
            : view(other)
        {}

        PHI_NODISCARD PHI_CONSTEXPR boolean operator()(CharT character) const PHI_NOEXCEPT
        {
            return npos == view.find_first_of(character);
        }
    };

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const_reference data_at(size_type pos) const PHI_NOEXCEPT
    {
        PHI_ASSERT(m_Data != nullptr, "Invalid data pointer");
        PHI_ASSERT(m_Length > 0u, "Invalid length");
        PHI_ASSERT(pos < length(), "Index out of bounds!");

        return m_Data[pos.unsafe()];
    }

    PHI_NODISCARD PHI_ATTRIBUTE_NONNULL PHI_CONSTEXPR size_type
    to_pos(const_iterator position) const PHI_NOEXCEPT
    {
        return position == cend() ? npos : size_type(position - cbegin());
    }

    PHI_NODISCARD PHI_ATTRIBUTE_NONNULL PHI_CONSTEXPR size_type
    to_pos(const_reverse_iterator position) const PHI_NOEXCEPT
    {
        return position == crend() ? npos : size_type(crend() - position - 1);
    }

    const CharT* m_Data;
    usize        m_Length;
};

// Comparison functions

template <typename CharT, typename TraitsT>
PHI_CONSTEXPR boolean operator==(not_null_basic_string_view<CharT, TraitsT> lhs,
                                 not_null_basic_string_view<CharT, TraitsT> rhs) PHI_NOEXCEPT
{
    return lhs.length() == rhs.length() && lhs.compare(rhs) == 0;
}

template <typename CharT, typename TraitsT>
PHI_CONSTEXPR boolean operator!=(not_null_basic_string_view<CharT, TraitsT> lhs,
                                 not_null_basic_string_view<CharT, TraitsT> rhs) PHI_NOEXCEPT
{
    return !(lhs == rhs);
}

template <typename CharT, typename TraitsT>
PHI_CONSTEXPR boolean operator<(not_null_basic_string_view<CharT, TraitsT> lhs,
                                not_null_basic_string_view<CharT, TraitsT> rhs) PHI_NOEXCEPT
{
    return lhs.compare(rhs) < 0;
}

template <typename CharT, typename TraitsT>
PHI_CONSTEXPR boolean operator<=(not_null_basic_string_view<CharT, TraitsT> lhs,
                                 not_null_basic_string_view<CharT, TraitsT> rhs) PHI_NOEXCEPT
{
    return lhs.compare(rhs) <= 0;
}

template <typename CharT, typename TraitsT>
PHI_CONSTEXPR boolean operator>(not_null_basic_string_view<CharT, TraitsT> lhs,
                                not_null_basic_string_view<CharT, TraitsT> rhs) PHI_NOEXCEPT
{
    return lhs.compare(rhs) > 0;
}

template <typename CharT, typename TraitsT>
PHI_CONSTEXPR boolean operator>=(not_null_basic_string_view<CharT, TraitsT> lhs,
                                 not_null_basic_string_view<CharT, TraitsT> rhs) PHI_NOEXCEPT
{
    return lhs.compare(rhs) >= 0;
}

// ==

template <typename CharT, typename TraitsT>
boolean operator==(not_null_basic_string_view<CharT, TraitsT> lhs, nullptr_t) = delete;

template <typename CharT, typename TraitsT>
boolean operator==(nullptr_t, not_null_basic_string_view<CharT, TraitsT> rhs) = delete;

// !=

template <typename CharT, typename TraitsT>
boolean operator!=(not_null_basic_string_view<CharT, TraitsT> lhs, nullptr_t) = delete;

template <typename CharT, typename TraitsT>
boolean operator!=(nullptr_t, not_null_basic_string_view<CharT, TraitsT> rhs) = delete;

// Typedefs

using not_null_string_view    = not_null_basic_string_view<char>;
using not_null_wstring_view   = not_null_basic_string_view<wchar_t>;
using not_null_u8string_view  = not_null_basic_string_view<char8_t>;
using not_null_u16string_view = not_null_basic_string_view<char16_t>;
using not_null_u32string_view = not_null_basic_string_view<char32_t>;

#if PHI_CPP_STANDARD_IS_BELOW(17)

template <typename CharT, typename TraitsT>
// NOLINTNEXTLINE(readability-redundant-declaration)
PHI_CONSTEXPR size_t not_null_basic_string_view<CharT, TraitsT>::npos;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_CONTAINER_STRING_VIEW_HPP
