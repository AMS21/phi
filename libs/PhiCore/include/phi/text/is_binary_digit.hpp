#ifndef INCG_PHI_CORE_TEXT_IS_BINARY_DIGIT_HPP
#define INCG_PHI_CORE_TEXT_IS_BINARY_DIGIT_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/nodiscard.hpp"
#include "phi/core/boolean.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

// Implementation comparision: https://godbolt.org/z/8G1EvYTGP

PHI_NODISCARD constexpr phi::boolean is_binary_digit(const char c) noexcept
{
    return (c == '0' || c == '1');
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TEXT_IS_BINARY_DIGIT_HPP