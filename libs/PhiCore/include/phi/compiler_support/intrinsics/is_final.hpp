#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_FINAL_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_FINAL_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/features.hpp"

#if PHI_HAS_INTRINSIC_IS_FINAL()
#    define PHI_IS_FINAL(type)      __is_final(type)
#    define PHI_SUPPORTS_IS_FINAL() 1
#elif PHI_HAS_INTRINSIC_IS_SEALED()
#    define PHI_IS_FINAL(type)      __is_sealed(type)
#    define PHI_SUPPORTS_IS_FINAL() 1
#else
#    define PHI_IS_FINAL(type)      false
#    define PHI_SUPPORTS_IS_FINAL() 0
#endif

#if defined(PHI_CONFIG_NO_INTRINSICS)
#    undef PHI_SUPPORTS_IS_FINAL
#    define PHI_SUPPORTS_IS_FINAL() 0
#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_FINAL_HPP