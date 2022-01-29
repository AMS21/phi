#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_NOTHROW_DESTRUCTIBLE_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_NOTHROW_DESTRUCTIBLE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/generated/compiler_support/features.hpp"

#if PHI_HAS_INTRINSIC_IS_NOTHROW_DESTRUCTIBLE()
#    define PHI_IS_NOTHROW_DESTRUCTIBLE(type)      __is_nothrow_destructible(type)
#    define PHI_SUPPORTS_IS_NOTHROW_DESTRUCTIBLE() 1
#else
#    define PHI_IS_NOTHROW_DESTRUCTIBLE(type)      false
#    define PHI_SUPPORTS_IS_NOTHROW_DESTRUCTIBLE() 0
#endif

#if defined(PHI_CONFIG_NO_INTRINSICS)
#    undef PHI_SUPPORTS_IS_NOTHROW_DESTRUCTIBLE
#    define PHI_SUPPORTS_IS_NOTHROW_DESTRUCTIBLE() 0
#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_NOTHROW_DESTRUCTIBLE_HPP
