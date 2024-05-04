#ifndef INCG_PHI_CORE_COMPILER_SUPPORT_CONSTEXPR_HPP
#define INCG_PHI_CORE_COMPILER_SUPPORT_CONSTEXPR_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/defect_report.hpp"
#include "phi/compiler_support/features.hpp"
#include "phi/preprocessor/if.hpp"

// Support for C++-11 constexpr
// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2007/n2235.pdf
#if PHI_HAS_FEATURE_CONSTEXPR()

#    define PHI_CONSTEXPR                 constexpr
#    define PHI_CONSTEXPR_OR_CONST        constexpr
#    define PHI_CONSTEXPR_OR_INLINE       constexpr
#    define PHI_CONSTEXPR_OR_STATIC       constexpr
#    define PHI_CONSTEXPR_OR(alternative) constexpr
#    define PHI_CONSTEXPR_IF(condition)   PHI_IF(condition, constexpr)

#else

#    define PHI_CONSTEXPR                 /* Nothing */
#    define PHI_CONSTEXPR_OR_CONST        const
#    define PHI_CONSTEXPR_OR_INLINE       inline
#    define PHI_CONSTEXPR_OR_STATIC       static
#    define PHI_CONSTEXPR_OR(alternative) alternative
#    define PHI_CONSTEXPR_IF(condition)   /* Nothing */

#endif

// Support for C++-14 extended constexpr
// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2013/n3652.html
#if PHI_HAS_FEATURE_EXTENDED_CONSTEXPR()

#    define PHI_EXTENDED_CONSTEXPR                 constexpr
#    define PHI_EXTENDED_CONSTEXPR_OR_CONST        constexpr
#    define PHI_EXTENDED_CONSTEXPR_OR_INLINE       constexpr
#    define PHI_EXTENDED_CONSTEXPR_OR_STATIC       constexpr
#    define PHI_EXTENDED_CONSTEXPR_OR(alternative) constexpr
#    define PHI_EXTENDED_CONSTEXPR_IF(condition)   PHI_IF(condition, constexpr)

// Support for 'constexpr' on non literal classes which was fixed with DR1684
#    if PHI_HAS_DR1684()
#        define PHI_EXTENDED_CONSTEXPR_CLASS constexpr
#    else
#        define PHI_EXTENDED_CONSTEXPR_CLASS /* Nothing */
#    endif

#else

#    define PHI_EXTENDED_CONSTEXPR                 /* Nothing */
#    define PHI_EXTENDED_CONSTEXPR_OR_CONST        const
#    define PHI_EXTENDED_CONSTEXPR_OR_INLINE       inline
#    define PHI_EXTENDED_CONSTEXPR_OR_STATIC       static
#    define PHI_EXTENDED_CONSTEXPR_OR(alternative) alternative
#    define PHI_EXTENDED_CONSTEXPR_IF(condition)   /* Nothing */

#    define PHI_EXTENDED_CONSTEXPR_CLASS /* Nothing */

#endif

// constexpr and const
#if PHI_HAS_FEATURE_EXTENDED_CONSTEXPR()

#    define PHI_CONSTEXPR_AND_CONST                          constexpr const
#    define PHI_CONSTEXPR_AND_CONST_OR(alternative)          constexpr const
#    define PHI_EXTENDED_CONSTEXPR_AND_CONST                 constexpr const
#    define PHI_EXTENDED_CONSTEXPR_AND_CONST_OR(alternative) constexpr const

#elif PHI_HAS_FEATURE_CONSTEXPR()

#    define PHI_CONSTEXPR_AND_CONST                          constexpr
#    define PHI_CONSTEXPR_AND_CONST_OR(alternative)          constexpr
#    define PHI_EXTENDED_CONSTEXPR_AND_CONST                 /* Nothing */
#    define PHI_EXTENDED_CONSTEXPR_AND_CONST_OR(alternative) alternative

#else

#    define PHI_CONSTEXPR_AND_CONST                          const
#    define PHI_CONSTEXPR_AND_CONST_OR(alternative)          alternative
#    define PHI_EXTENDED_CONSTEXPR_AND_CONST                 /* Nothing */
#    define PHI_EXTENDED_CONSTEXPR_AND_CONST_OR(alternative) alternative

#endif

// Constexpr lambda expression
// https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0170r1.pdf
#if PHI_HAS_FEATURE_CONSTEXPR_LAMBDA()

#    define PHI_CONSTEXPR_LAMBDA constexpr

#else

#    define PHI_CONSTEXPR_LAMBDA /* Nothing */

#endif

// Constexpr virtual functions
// https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2018/p1064r0.html
#if PHI_HAS_FEATURE_CONSTEXPR_VIRTUAL()

#    define PHI_CONSTEXPR_VIRTUAL constexpr

#else

#    define PHI_CONSTEXPR_VIRTUAL /* Nothing */

#endif

// Constexpr destructor
#if PHI_HAS_FEATURE_CONSTEXPR_DESTRUCTOR()

#    define PHI_CONSTEXPR_DESTRUCTOR constexpr

#else

#    define PHI_CONSTEXPR_DESTRUCTOR /* Nothing */

#endif

#endif // INCG_PHI_CORE_COMPILER_SUPPORT_CONSTEXPR_HPP
