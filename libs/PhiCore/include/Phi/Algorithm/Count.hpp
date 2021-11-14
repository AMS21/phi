#ifndef INCG_PHI_CORE_ALGORITHM_COUNT_HPP
#define INCG_PHI_CORE_ALGORITHM_COUNT_HPP

#include "Phi/PhiConfig.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "Phi/CompilerSupport/Constexpr.hpp"
#include "Phi/CompilerSupport/Nodiscard.hpp"
#include <iterator>

DETAIL_PHI_BEGIN_NAMESPACE()

// TODO: noexcept
template <typename InputIteratorT, typename TypeT>
PHI_NODISCARD typename std::iterator_traits<InputIteratorT>::difference_type PHI_EXTENDED_CONSTEXPR
count(InputIteratorT first, InputIteratorT last, const TypeT& value)
{
    typename std::iterator_traits<InputIteratorT>::difference_type ret = 0;

    for (; first != last; ++first)
    {
        if (*first == value)
        {
            ++ret;
        }
    }

    return ret;
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_ALGORITHM_COUNT_HPP
