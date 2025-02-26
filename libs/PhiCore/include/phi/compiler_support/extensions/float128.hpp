#ifndef INCG_PHI_CORE_COMPILER_SUPPORT_EXTENSIONS_FLOAT128_HPP
#define INCG_PHI_CORE_COMPILER_SUPPORT_EXTENSIONS_FLOAT128_HPP

#include "phi/generated/compiler_support/extensions.hpp"

#if PHI_HAS_EXTENSION_FLOAT128()

#    define PHI_FLOAT128 __float128

#else

#    define PHI_FLOAT128 void

#endif

#endif // INCG_PHI_CORE_COMPILER_SUPPORT_EXTENSIONS_PRAGMA_ONCE_HPP
