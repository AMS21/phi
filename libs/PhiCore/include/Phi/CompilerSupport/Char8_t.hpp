#ifndef INCG_PHI_CORE_COMPILER_SUPPORT_CHAR8_T_HPP
#define INCG_PHI_CORE_COMPILER_SUPPORT_CHAR8_T_HPP

#include "Phi/Config/CPlusPlus.hpp"
#include "Phi/Config/Compiler.hpp"
#include "Phi/Config/Warning.hpp"
#include "Phi/PhiConfig.hpp"

PHI_CLANG_SUPPRESS_WARNING_PUSH()
PHI_CLANG_SUPPRESS_WARNING("-Wunknown-warning-option")
PHI_CLANG_SUPPRESS_WARNING("-Wc++20-compat")
PHI_CLANG_SUPPRESS_WARNING("-Wc++2a-compat")

#if PHI_CPP_STANDARD_IS_GREATER(17) &&                                                             \
        (PHI_COMPILER_IS_ATLEAST(CLANG_COMPAT, 9, 0, 0) ||                                         \
         PHI_COMPILER_IS_ATLEAST(GCC, 7, 0, 0) || PHI_COMPILER_IS_ATLEAST(MSVC, 19, 22, 0))
// Compiler has native support for char8_t
#else
using char8_t = unsigned char;
#endif

PHI_CLANG_SUPPRESS_WARNING_POP()

#endif // INCG_PHI_CORE_COMPILER_SUPPORT_CHAR8_T_HPP
