#ifndef INCG_PHI_CORE_OFFSETOF_HPP
#define INCG_PHI_CORE_OFFSETOF_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/intrinsics/offsetof.hpp"

#ifdef offsetof
#    undef offsetof
#endif

#if PHI_SUPPORTS_OFFSETOF()

#    define offsetof(type, member) PHI_OFFSETOF(type, member)

#else

#    include "phi/core/size_t.hpp"

#    define offsetof(type, member)                                                                 \
        ((::phi::size_t)&reinterpret_cast<char const volatile&>((((type*)0)->member)))

#endif

#endif // INCG_PHI_CORE_OFFSETOF_HPP
