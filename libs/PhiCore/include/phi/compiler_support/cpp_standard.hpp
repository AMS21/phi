#ifndef INCG_PHI_CORE_COMPILER_SUPPORT_CPLUSPLUS_HPP
#define INCG_PHI_CORE_COMPILER_SUPPORT_CPLUSPLUS_HPP

#include "phi/compiler_support/compiler.hpp"

// C++-98 standard from november 1997
#define PHI_CPLUSPLUS_98() (199711L)

// C++-11 standard from march 2011
#define PHI_CPLUSPLUS_11() (201103L)

// C++-14 standard from february 2014
#define PHI_CPLUSPLUS_14() (201402L)

// C++-17
#if PHI_COMPILER_IS_BELOW(MSVC, 19, 20, 0)

// MSVC before 2019 uses 201704 for C++-17
#    define PHI_CPLUSPLUS_17() (201704L)

#elif PHI_COMPILER_IS_BELOW(GCC, 7, 0, 0)

// GCC versions before gcc-7 use 201500 for C++-17
// See: https://godbolt.org/z/MEPP5xrEb
#    define PHI_CPLUSPLUS_17() (201500L)

#else

// C++-17 standard from march 2017
#    define PHI_CPLUSPLUS_17() (201703L)

#endif

// C++-20
#if PHI_COMPILER_IS_BELOW(GCC, 11, 0, 0)

// GCC-8 - GCC-10 use 201709 for C++-20
// See: https://godbolt.org/z/86a93zjYo
#    define PHI_CPLUSPLUS_20() (201709L)

#elif PHI_COMPILER_IS_BELOW(CLANG, 10, 0, 0) || PHI_COMPILER_IS_BELOW(EMCC, 1, 39, 0) ||           \
        PHI_COMPILER_IS_BELOW(APPLECLANG, 12, 0, 5)

// Clang version before clang-10 uses 201707 for C++-20
#    define PHI_CPLUSPLUS_20() (201707L)

#else

// C++-20 standard from february 2020
#    define PHI_CPLUSPLUS_20() (202002L)

#endif

// C++-23
#if PHI_COMPILER_IS(GCC) || PHI_COMPILER_IS(MINGW)

#    define PHI_CPLUSPLUS_23() (202100L)

#elif PHI_COMPILER_IS(MSVC) && PHI_COMPILER_IS_NOT(WINCLANG)

#    define PHI_CPLUSPLUS_23() (202004L)

#elif PHI_COMPILER_IS_ATLEAST(EMCC, 3, 1, 39)

#    define PHI_CPLUSPLUS_23() (202302L)

#else

// C++-23 standard (Working draft)
#    define PHI_CPLUSPLUS_23() (202101L)

#endif

// C++-26
// TODO: This is the value clang-17 uses since its the only compiler currently supporting C++-26
#define PHI_CPLUSPLUS_26() (202400L)

// Latest C++ standard
#define PHI_CPLUSPLUS_LATEST() PHI_CPLUSPLUS_26()

#if PHI_COMPILER_IS(MSVC) && PHI_COMPILER_IS_NOT(WINCLANG)

#    if defined(_MSVC_LANG)

#        define PHI_CPP_STANDARD() _MSVC_LANG

#    else

#        define PHI_CPP_STANDARD() PHI_CPLUSPLUS_LATEST()

#    endif

#elif defined(__cplusplus)

#    define PHI_CPP_STANDARD() __cplusplus

#else

// Use C++-98 as fallback
#    define PHI_CPP_STANDARD() PHI_CPLUSPLUS_98()

#endif

#define PHI_CPP_STANDARD_IS_EXACTLY(standard) (PHI_CPP_STANDARD() == PHI_CPLUSPLUS_##standard())

#define PHI_CPP_STANDARD_IS_GREATER(standard) (PHI_CPP_STANDARD() > PHI_CPLUSPLUS_##standard())

#define PHI_CPP_STANDARD_IS_ATLEAST(standard) (PHI_CPP_STANDARD() >= PHI_CPLUSPLUS_##standard())

#define PHI_CPP_STANDARD_IS_BELOW(standard) (PHI_CPP_STANDARD() < PHI_CPLUSPLUS_##standard())

#if PHI_CPP_STANDARD_IS_EXACTLY(26)
#    define PHI_CPP_STANDARD_SHORT() 26
#elif PHI_CPP_STANDARD_IS_EXACTLY(23)
#    define PHI_CPP_STANDARD_SHORT() 23
#elif PHI_CPP_STANDARD_IS_EXACTLY(20)
#    define PHI_CPP_STANDARD_SHORT() 20
#elif PHI_CPP_STANDARD_IS_EXACTLY(17)
#    define PHI_CPP_STANDARD_SHORT() 17
#elif PHI_CPP_STANDARD_IS_EXACTLY(14)
#    define PHI_CPP_STANDARD_SHORT() 14
#elif PHI_CPP_STANDARD_IS_EXACTLY(11)
#    define PHI_CPP_STANDARD_SHORT() 11
#else
// C++-98 as fallback
#    define PHI_CPP_STANDARD_SHORT() 98
#endif

#endif // INCG_PHI_CORE_COMPILER_SUPPORT_CPLUSPLUS_HPP
