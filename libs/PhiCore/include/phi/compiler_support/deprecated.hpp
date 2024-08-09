#ifndef INCG_PHI_CORE_COMPILER_SUPPORT_DEPRECATED_HPP
#define INCG_PHI_CORE_COMPILER_SUPPORT_DEPRECATED_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/compiler.hpp"
#include "phi/compiler_support/features.hpp"

// clang-format off
#if PHI_HAS_FEATURE_ATTRIBUTE_DEPRECATED()

#    define PHI_DEPRECATED          [[deprecated]]
#    define PHI_DEPRECATED_MSG(msg) [[deprecated(#msg)]]

#elif PHI_COMPILER_IS(GCC) || PHI_COMPILER_IS(CLANG_COMPAT)

#    define PHI_DEPRECATED          __attribute__((deprecated))
#    define PHI_DEPRECATED_MSG(msg) __attribute__((deprecated(#msg)))

#elif PHI_COMPILER_IS(MSVC)

#    define PHI_DEPRECATED          __declspec(deprecated)
#    define PHI_DEPRECATED_MSG(msg) __declspec(deprecated(#msg))

#else

#    define PHI_DEPRECATED /* Nothing */
#    define PHI_DEPRECATED_MSG(msg)  /* Nothing */

#endif
// clang-format on

#endif // INCG_PHI_CORE_COMPILER_SUPPORT_DEPRECATED_HPP
