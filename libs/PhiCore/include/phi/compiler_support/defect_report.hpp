#ifndef INCG_PHI_CORE_COMPILER_SUPPORT_DEFECT_REPORT_HPP
#define INCG_PHI_CORE_COMPILER_SUPPORT_DEFECT_REPORT_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/compiler.hpp"

// DR 1684
// https://www.open-std.org/jtc1/sc22/wg21/docs/cwg_defects.html#1684
#if PHI_COMPILER_IS_ATLEAST(GCC, 7, 0, 0) || PHI_COMPILER_IS_ATLEAST(CLANG, 3, 9, 0) ||            \
        PHI_COMPILER_IS(MSVC) || PHI_COMPILER_IS(APPLECLANG) || PHI_COMPILER_IS(EMCC)
#    define PHI_HAS_DR1684() 1
#else
#    define PHI_HAS_DR1684() 0
#endif

#endif // INCG_PHI_CORE_COMPILER_SUPPORT_DEFECT_REPORT_HPP
