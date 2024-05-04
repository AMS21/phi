#ifndef INCG_PHI_FORWARD_STD_ARRAY_HPP
#define INCG_PHI_FORWARD_STD_ARRAY_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/standard_library.hpp"
#include "phi/core/size_t.hpp"

// NOTE: Special care needs to taken for glibcxx's debug array implementation.
//       Which was added in this commit: https://github.com/gcc-mirror/gcc/commit/0611ce440a4e5a460b185cb2b64684bd51f94d51
//       And removed in this commit: https://github.com/gcc-mirror/gcc/commit/6db082477ad839438c4b54fc61083276c68d47ec
// It was added with the gcc release 4.8.0 from March 22, 2013
// and removed with the gcc release 11.1.0 from April 27, 2021
#if PHI_STANDARD_LIBRARY_LIBSTDCXX() && __GLIBCXX__ >= 20130322 &&                                 \
        (!defined(_GLIBCXX_RELEASE) || _GLIBCXX_RELEASE < 11)
#    define DETAIL_PHI_FORWARD_STD_DEBUG_ARRAY() 1
#else
#    define DETAIL_PHI_FORWARD_STD_DEBUG_ARRAY() 0
#endif

#if DETAIL_PHI_FORWARD_STD_DEBUG_ARRAY()

namespace std
{
    _GLIBCXX_BEGIN_NAMESPACE_CONTAINER

    template <typename TypeT, phi::size_t Size>
    struct array;

    _GLIBCXX_END_NAMESPACE_CONTAINER
} // namespace std

// Forwarding of debug array implementation
#    if defined(_GLIBCXX_DEBUG)

namespace std
{
    inline namespace __debug
    {

        template <typename TypeT, phi::size_t Size>
        struct array;

    } // namespace __debug
} // namespace std

#    endif

#elif PHI_STANDARD_LIBRARY_MSVC()
// MSVC's std::array uses class instead of struct

DETAIL_PHI_BEGIN_STD_NAMESPACE()

template <typename TypeT, phi::size_t Size>
class array;

DETAIL_PHI_END_STD_NAMESPACE()

#else
// std::array forward with a struct

DETAIL_PHI_BEGIN_STD_NAMESPACE()

template <typename TypeT, phi::size_t Size>
struct array;

DETAIL_PHI_END_STD_NAMESPACE()

#endif

#undef DETAIL_PHI_FORWARD_STD_DEBUG_ARRAY

#endif // INCG_PHI_FORWARD_STD_ARRAY_HPP
