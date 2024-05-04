#ifndef INCG_PHI_CORE_ALGORITHM_FIND_IF_NOT_HPP
#define INCG_PHI_CORE_ALGORITHM_FIND_IF_NOT_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include "phi/compiler_support/noexcept.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename InputIteratorT, typename UnaryPredicateT>
PHI_NODISCARD PHI_EXTENDED_CONSTEXPR InputIteratorT
find_if_not(InputIteratorT first, InputIteratorT last, UnaryPredicateT predicate) PHI_NOEXCEPT
{
    for (; first != last; ++first)
    {
        if (!predicate(*first))
        {
            return first;
        }
    }

    return last;
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_ALGORITHM_FIND_IF_NOT_HPP
