#ifndef INCG_PHI_CORE_ALGORITHM_EQUAL_HPP
#define INCG_PHI_CORE_ALGORITHM_EQUAL_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include "phi/compiler_support/warning.hpp"
#include "phi/core/boolean.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

PHI_CLANG_SUPPRESS_WARNING_PUSH()
#if PHI_COMPILER_IS_ATLEAST(CLANG, 16, 0, 0)
PHI_CLANG_SUPPRESS_WARNING("-Wunsafe-buffer-usage")
#endif

// TODO: noexcept
template <typename InputIterator1T, typename InputIterator2T>
PHI_NODISCARD PHI_EXTENDED_CONSTEXPR boolean equal(InputIterator1T first1, InputIterator1T last1,
                                                   InputIterator2T first2)
{
    for (; first1 != last1; ++first1, ++first2)
    {
        if (!(*first1 == *first2))
        {
            return false;
        }
    }

    return true;
}

// TODO: noexcept
template <typename InputIterator1T, typename InputIterator2T, typename BinaryPredicateT>
PHI_NODISCARD PHI_EXTENDED_CONSTEXPR boolean equal(InputIterator1T first1, InputIterator1T last1,
                                                   InputIterator2T  first2,
                                                   BinaryPredicateT predicate)
{
    for (; first1 != last1; ++first1, ++first2)
    {
        if (!predicate(*first1, *first2))
        {
            return false;
        }
    }

    return true;
}

PHI_CLANG_SUPPRESS_WARNING_POP()

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_ALGORITHM_EQUAL_HPP
