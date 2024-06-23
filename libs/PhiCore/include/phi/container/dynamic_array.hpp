#ifndef INCG_PHI_CORE_CONTAINER_DYNAMIC_ARRAY_HPP
#define INCG_PHI_CORE_CONTAINER_DYNAMIC_ARRAY_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/algorithm/exchange.hpp"
#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/extended_attributes.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include "phi/compiler_support/noexcept.hpp"
#include "phi/core/assert.hpp"
#include "phi/core/types.hpp"
#include "phi/iterator/reverse_iterator.hpp"
#include <new>

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
class PHI_ATTRIBUTE_OWNER dynamic_array
{
public:
    using this_type              = dynamic_array<TypeT>;
    using value_type             = TypeT;
    using size_type              = usize;
    using difference_type        = ptrdiff;
    using reference              = TypeT&;
    using const_reference        = const TypeT&;
    using pointer                = TypeT*;
    using const_pointer          = const TypeT*;
    using iterator               = pointer;
    using const_iterator         = const_pointer;
    using reverse_iterator       = phi::reverse_iterator<pointer>;
    using const_reverse_iterator = phi::reverse_iterator<const_pointer>;

    explicit dynamic_array(size_type size) PHI_NOEXCEPT
        : m_Size{size},
          m_Elements{new(std::nothrow) TypeT[size.unsafe()]}
    {
        PHI_ASSERT(size > 0u, "Allocating zero elements");
        PHI_ASSERT(m_Elements != nullptr, "Failed to allocate");
    }

    PHI_EXTENDED_CONSTEXPR dynamic_array(const dynamic_array& other) PHI_NOEXCEPT
        : m_Elements{new(std::nothrow) TypeT[other.m_Size.unsafe()]},
          m_Size{other.m_Size}
    {
        // Copy elements
        for (usize i{0u}; i < other.m_Size; ++i)
        {
            m_Elements[i.unsafe()] = other.at(i);
        }
    }

    PHI_EXTENDED_CONSTEXPR dynamic_array(dynamic_array&& other) PHI_NOEXCEPT
        : m_Elements(exchange(other.m_Elements, nullptr)),
          m_Size(other.m_Size)
    {
        PHI_ASSERT(m_Elements != nullptr, "Assigned nullptr");
        PHI_ASSERT(m_Size > 0u, "Created zero sized array");
    }

    PHI_CONSTEXPR_DESTRUCTOR ~dynamic_array() PHI_NOEXCEPT
    {
        delete[] m_Elements;
    }

    PHI_EXTENDED_CONSTEXPR dynamic_array& operator=(const dynamic_array& other) PHI_NOEXCEPT
    {
        // Handle self assignment
        if (&other == this)
        {
            return *this;
        }

        m_Elements = new (std::nothrow) TypeT[other.m_Size.unsafe()];
        m_Size     = other.m_Size;

        PHI_ASSERT(m_Elements != nullptr, "Failed to allocate elements");
        PHI_ASSERT(m_Size > 0u, "Zero sized array");

        // Copy elements
        for (usize i{0u}; i < other.m_Size; ++i)
        {
            m_Elements[i.unsafe()] = other.at(i);
        }

        return *this;
    }

    PHI_EXTENDED_CONSTEXPR dynamic_array& operator=(dynamic_array&& other) PHI_NOEXCEPT
    {
        m_Elements = exchange(other.m_Elements, nullptr);
        m_Size     = other.m_Size;
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR reference at(size_type pos) PHI_NOEXCEPT
    {
        PHI_ASSERT(pos < m_Size, "Index out of range");
        PHI_ASSERT(m_Elements != nullptr, "Accessing nullptr");

        return m_Elements[pos.unsafe()];
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const_reference at(size_type pos) const PHI_NOEXCEPT
    {
        PHI_ASSERT(pos < m_Size, "Index out of range");
        PHI_ASSERT(m_Elements != nullptr, "Accessing nullptr");

        return m_Elements[pos.unsafe()];
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR reference operator[](size_type pos) PHI_NOEXCEPT
    {
        return at(pos);
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const_reference
    operator[](size_type pos) const PHI_NOEXCEPT
    {
        return at(pos);
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR reference front() PHI_NOEXCEPT
    {
        return at(0u);
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const_reference front() const PHI_NOEXCEPT
    {
        return at(0u);
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR reference back() PHI_NOEXCEPT
    {
        return at(m_Size - 1u);
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const_reference back() const PHI_NOEXCEPT
    {
        return at(m_Size - 1u);
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR pointer data() PHI_NOEXCEPT
    {
        PHI_ASSERT(m_Elements != nullptr, "Accessing nullptr");

        return m_Elements;
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const_pointer data() const PHI_NOEXCEPT
    {
        PHI_ASSERT(m_Elements != nullptr, "Accessing nullptr");

        return m_Elements;
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR iterator begin() PHI_NOEXCEPT
    {
        return iterator(data());
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const_iterator begin() const PHI_NOEXCEPT
    {
        return const_iterator(data());
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const_iterator cbegin() const PHI_NOEXCEPT
    {
        return const_iterator(data());
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR iterator end() PHI_NOEXCEPT
    {
        return iterator(data() + m_Size);
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const_iterator end() const PHI_NOEXCEPT
    {
        return const_iterator(data() + m_Size);
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const_iterator cend() const PHI_NOEXCEPT
    {
        return const_iterator(data() + m_Size);
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR reverse_iterator rbegin() PHI_NOEXCEPT
    {
        return reverse_iterator(end());
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const_reverse_iterator rbegin() const PHI_NOEXCEPT
    {
        return const_reverse_iterator(end());
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const_reverse_iterator crbegin() const PHI_NOEXCEPT
    {
        return const_reverse_iterator(end());
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR reverse_iterator rend() PHI_NOEXCEPT
    {
        return reverse_iterator(begin());
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const_reverse_iterator rend() const PHI_NOEXCEPT
    {
        return const_reverse_iterator(begin());
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const_reverse_iterator crend() const PHI_NOEXCEPT
    {
        return const_reverse_iterator(begin());
    }

    PHI_NODISCARD PHI_CONSTEXPR size_type size() const PHI_NOEXCEPT
    {
        return m_Size;
    }

    PHI_NODISCARD PHI_CONSTEXPR size_type max_size() const PHI_NOEXCEPT
    {
        return size_type::max();
    }

    PHI_EXTENDED_CONSTEXPR void fill(const TypeT& value) PHI_NOEXCEPT
    {
        fill_n(m_Elements, m_Size, value);
    }

    PHI_EXTENDED_CONSTEXPR void clear() PHI_NOEXCEPT
    {
        delete[] m_Elements;
        m_Size = 0u;
    }

private:
    pointer   m_Elements;
    size_type m_Size;
};

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_CONTAINER_DYNAMIC_ARRAY_HPP
