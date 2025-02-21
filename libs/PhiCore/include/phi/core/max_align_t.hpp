#ifndef INCG_PHI_CORE_MAX_ALIGN_T_HPP
#define INCG_PHI_CORE_MAX_ALIGN_T_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/compiler.hpp"
#include "phi/compiler_support/extensions/float128.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_COMPILER_IS(MSVC)

using max_align_t = double;

#else

// Define 'max_align_t' to match the GCC definition.
using max_align_t = struct
{
    long long   max_align_nonce1 alignas(alignof(long long));
    long double max_align_nonce2 alignas(alignof(long double));

#    if PHI_HAS_EXTENSION_FLOAT128()

    PHI_FLOAT128 max_align_nonce3 alignas(alignof(PHI_FLOAT128));

#    endif
};

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_MAX_ALIGN_T_HPP
