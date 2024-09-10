#ifndef INCG_PHI_PHI_CONFIG_HPP
#define INCG_PHI_PHI_CONFIG_HPP

#include "phi/compiler_support/extensions/pragma_once.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/compiler.hpp"
#include "phi/compiler_support/platform.hpp"
#include "phi/preprocessor/stringify.hpp"
#include "phi/preprocessor/versioning.hpp"

#define PHI_VERSION_MAJOR() 0
#define PHI_VERSION_MINOR() 1
#define PHI_VERSION_PATCH() 0

#define PHI_VERSION()                                                                              \
    PHI_VERSION_CREATE(PHI_VERSION_MAJOR(), PHI_VERSION_MINOR(), PHI_VERSION_PATCH())

#define PHI_VERSION_MAJOR_STR() PHI_STRINGIFY(PHI_VERSION_MAJOR())
#define PHI_VERSION_MINOR_STR() PHI_STRINGIFY(PHI_VERSION_MINOR())
#define PHI_VERSION_PATCH_STR() PHI_STRINGIFY(PHI_VERSION_PATCH())

#define PHI_VERSION_STR()                                                                          \
    PHI_VERSION_MAJOR_STR() "." PHI_VERSION_MINOR_STR() "." PHI_VERSION_PATCH_STR()

/// \cond detail
#define DETAIL_PHI_BEGIN_NAMESPACE()                                                               \
    namespace phi                                                                                  \
    {

// clang-format off
#define DETAIL_PHI_END_NAMESPACE() }
// clang-format on
/// \endcond

#if !defined(PHI_DEBUG) && (!defined(NDEBUG) || defined(_DEBUG))
#    define PHI_DEBUG
#endif

// No min max on Windows
#if PHI_PLATFORM_IS(WINDOWS)
#    ifndef NOMINMAX
#        define NOMINMAX
#    endif
#endif

// Import/Export
#if PHI_PLATFORM_IS(WINDOWS)
#    define PHI_API_EXPORT __declspec(dllexport)
#    define PHI_API_IMPORT __declspec(dllimport)
#elif PHI_COMPILER_IS_ATLEAST(GCC, 4, 0, 0) || PHI_COMPILER_IS(CLANG)
#    define PHI_API_EXPORT __attribute__((__visibility__("default")))
#    define PHI_API_IMPORT __attribute__((__visibility__("default")))
#else
#    define PHI_API_EXPORT
#    define PHI_API_IMPORT
#endif

// Define PHI_API macro
#if !defined(PHI_STATIC_BUILD)
#    if defined(PHI_IMPORT)
#        define PHI_API PHI_API_IMPORT
#    else
#        define PHI_API PHI_API_EXPORT
#    endif
#else
#    define PHI_API
#endif

// Assertions
#ifndef PHI_CONFIG_ENABLE_ASSERTIONS
// Automatically enable assertions for debug builds
#    if defined(PHI_DEBUG)
#        define PHI_CONFIG_ENABLE_ASSERTIONS 1
#    else
#        define PHI_CONFIG_ENABLE_ASSERTIONS 0
#    endif
#endif

// Checked narrow_cast
#ifndef PHI_CONFIG_NARROW_CAST_CHECKED
// Automatically enable checked narrow_cast for debug builds
#    if defined(PHI_DEBUG)
#        define PHI_CONFIG_NARROW_CAST_CHECKED 1
#    else
#        define PHI_CONFIG_NARROW_CAST_CHECKED 0
#    endif
#endif

#endif // INCG_PHI_PHI_CONFIG_HPP
