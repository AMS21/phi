#ifndef INCG_PHI_CORE_COMPILER_SUPPORT_BUGS_MSVC_10741077_HPP
#define INCG_PHI_CORE_COMPILER_SUPPORT_BUGS_MSVC_10741077_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/compiler.hpp"

// https://developercommunity.microsoft.com/t/Compiler-crashes-for-custom-implementati/10741077
#if PHI_COMPILER_IS_ATLEAST(MSVC, 19, 20, 0) && PHI_COMPILER_IS_BELOW(MSVC, 19, 43, 0)

#    define PHI_HAS_BUG_MSVC_10741077() 1

#else

#    define PHI_HAS_BUG_MSVC_10741077() 0

#endif

#endif // INCG_PHI_CORE_COMPILER_SUPPORT_BUGS_MSVC_10741077_HPP
