#ifndef INCG_PHI_CORE_STREAMOFF_HPP
#define INCG_PHI_CORE_STREAMOFF_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/standard_library.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if defined(_NEWLIB_VERSION)

// Newlib defines off_t as 'long int'
typedef long int streamoff;

#elif PHI_STANDARD_LIBRARY_LIBSTDCXX() && defined(__INT64_TYPE__)

// Same way gcc defines streamoff
typedef __INT64_TYPE__ streamoff;

#else

// Otherwise fallback to 'long long'
typedef long long streamoff;

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_STREAMOFF_HPP
