#ifndef INCG_PHI_CORE_MATH_VECTOR2_HPP
#define INCG_PHI_CORE_MATH_VECTOR2_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/noexcept.hpp"
#include "phi/core/boolean.hpp"
#include "phi/core/move.hpp"
#include "phi/core/types.hpp"
#include "phi/iterator/reverse_iterator.hpp"
#include "phi/type_traits/is_integer.hpp"
#include "phi/type_traits/is_signed.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
class vector2
{
public:
    using this_type              = vector2<TypeT>;
    using value_type             = TypeT;
    using reference              = value_type&;
    using const_reference        = const value_type&;
    using pointer                = value_type*;
    using const_pointer          = const value_type*;
    using iterator               = value_type*;
    using const_iterator         = const value_type*;
    using reverse_iterator       = phi::reverse_iterator<iterator>;
    using const_reverse_iterator = phi::reverse_iterator<const_iterator>;

    // Constructors
    PHI_CONSTEXPR vector2(TypeT val_x, TypeT val_y) PHI_NOEXCEPT : x(val_x), y(val_y)
    {}

    PHI_CONSTEXPR explicit vector2(TypeT val_xy) PHI_NOEXCEPT : x(val_xy), y(val_xy)
    {}

    PHI_CONSTEXPR vector2(const vector2<TypeT>& other) PHI_NOEXCEPT : x(other.x), y(other.y)
    {}

    PHI_CONSTEXPR vector2(vector2<TypeT>&& other) PHI_NOEXCEPT : x(move(other.x)), y(move(other.y))
    {}

    template <typename OtherT>
    PHI_CONSTEXPR vector2(const vector2<OtherT>& other) PHI_NOEXCEPT
        : x(static_cast<TypeT>(other.x)),
          y(static_cast<TypeT>(other.y))
    {}

    template <typename OtherT>
    PHI_CONSTEXPR vector2(vector2<OtherT>&& other) PHI_NOEXCEPT
        : x(static_cast<TypeT>(move(other.x))),
          y(static_cast<TypeT>(move(other.y)))
    {}

    ~vector2() = default;

    // Operators

    vector2<TypeT>& operator=(const vector2<TypeT>& other) = default;

    vector2<TypeT>& operator=(vector2<TypeT>&& other) = default;

    TypeT x;
    TypeT y;
};

// Unary Operators

template <typename TypeT>
PHI_CONSTEXPR vector2<TypeT> operator+(const vector2<TypeT>& rhs) PHI_NOEXCEPT
{
    return rhs;
}

template <typename TypeT>
PHI_CONSTEXPR vector2<TypeT> operator-(const vector2<TypeT>& rhs) PHI_NOEXCEPT
{
    static_assert(!is_integer<TypeT>::value || is_signed<TypeT>::value,
                  "Cannot call unary minus on unsigned integer");

    return vector2<TypeT>(-rhs.x, -rhs.y);
}

// Binary Operators

PHI_MSVC_SUPPRESS_WARNING_PUSH()
PHI_MSVC_SUPPRESS_WARNING(
        4365) // 'action' : conversion from 'type_1' to 'type_2', signed/unsigned mismatch

template <typename LhsT, typename RhsT>
PHI_CONSTEXPR vector2<LhsT> operator+(const vector2<LhsT>& lhs,
                                      const vector2<RhsT>& rhs) PHI_NOEXCEPT
{
    return vector2<LhsT>(lhs.x + rhs.x, lhs.y + rhs.y);
}

template <typename LhsT, typename RhsT>
PHI_EXTENDED_CONSTEXPR vector2<LhsT>& operator+=(vector2<LhsT>&       lhs,
                                                 const vector2<RhsT>& rhs) PHI_NOEXCEPT
{
    lhs.x += rhs.x;
    lhs.y += rhs.y;

    return lhs;
}

template <typename LhsT, typename RhsT>
PHI_CONSTEXPR vector2<LhsT> operator-(const vector2<LhsT>& lhs,
                                      const vector2<RhsT>& rhs) PHI_NOEXCEPT
{
    return vector2<LhsT>(lhs.x - rhs.x, lhs.y - rhs.y);
}

template <typename LhsT, typename RhsT>
PHI_EXTENDED_CONSTEXPR vector2<LhsT>& operator-=(vector2<LhsT>&       lhs,
                                                 const vector2<RhsT>& rhs) PHI_NOEXCEPT
{
    lhs.x -= rhs.x;
    lhs.y -= rhs.y;

    return lhs;
}

template <typename LhsT, typename RhsT>
PHI_CONSTEXPR vector2<LhsT> operator*(const vector2<LhsT>& lhs, const RhsT& rhs) PHI_NOEXCEPT
{
    return vector2<LhsT>(lhs.x * rhs, lhs.y * rhs);
}

template <typename LhsT, typename RhsT>
PHI_EXTENDED_CONSTEXPR vector2<LhsT>& operator*=(vector2<LhsT>& lhs, const RhsT& rhs) PHI_NOEXCEPT
{
    lhs.x *= rhs;
    lhs.y *= rhs;

    return lhs;
}

template <typename LhsT, typename RhsT>
PHI_CONSTEXPR vector2<LhsT> operator/(const vector2<LhsT>& lhs, const RhsT& rhs) PHI_NOEXCEPT
{
    return vector2<LhsT>(lhs.x / rhs, lhs.y / rhs);
}

template <typename LhsT, typename RhsT>
PHI_EXTENDED_CONSTEXPR vector2<LhsT>& operator/=(vector2<LhsT>& lhs, const RhsT& rhs) PHI_NOEXCEPT
{
    lhs.x /= rhs;
    lhs.y /= rhs;

    return lhs;
}

PHI_MSVC_SUPPRESS_WARNING_POP()

template <typename LhsT, typename RhsT>
PHI_CONSTEXPR boolean operator==(const vector2<LhsT>& lhs, const vector2<RhsT>& rhs) PHI_NOEXCEPT
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

template <typename LhsT, typename RhsT>
PHI_CONSTEXPR boolean operator!=(const vector2<LhsT>& lhs, const vector2<RhsT>& rhs) PHI_NOEXCEPT
{
    return lhs.x != rhs.x || lhs.y != rhs.y;
}

// Define the most common types
using vector2i8    = vector2<i8>;
using vector2u8    = vector2<u8>;
using vector2i16   = vector2<i16>;
using vector2u16   = vector2<u16>;
using vector2i32   = vector2<i32>;
using vector2u32   = vector2<u32>;
using vector2i64   = vector2<i64>;
using vector2u64   = vector2<u64>;
using vector2isize = vector2<isize>;
using vector2usize = vector2<usize>;

using vector2f32 = vector2<f32>;
using vector2f64 = vector2<f64>;

using vector2b = vector2<boolean>;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_MATH_VECTOR2_HPP
