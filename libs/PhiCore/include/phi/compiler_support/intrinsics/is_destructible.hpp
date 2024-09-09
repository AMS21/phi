#ifndef INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_DESTRUCTIBLE_HPP
#define INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_DESTRUCTIBLE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/compiler.hpp"

#if !defined(PHI_IS_DESTRUCTIBLE) && !defined(PHI_SUPPORTS_IS_DESTRUCTIBLE)

#    if PHI_COMPILER_IS_ATLEAST(CLANG, 16, 0, 0) || PHI_COMPILER_IS(APPLECLANG) ||                 \
            PHI_COMPILER_IS(EMCC) || PHI_COMPILER_IS(MSVC)
#        define PHI_IS_DESTRUCTIBLE(type)      __is_destructible(type)
#        define PHI_SUPPORTS_IS_DESTRUCTIBLE() 1
#    else
#        define PHI_SUPPORTS_IS_DESTRUCTIBLE() 0
#    endif

#endif

#endif // INCH_PHI_CORE_COMPILER_SUPPORT_INTRINSICS_IS_DESTRUCTIBLE_HPP
