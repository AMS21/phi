#ifndef INCG_PHI_CORE_TEXT_OCTAL_DIGIT_VALUE_HPP
#define INCG_PHI_CORE_TEXT_OCTAL_DIGIT_VALUE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/nodiscard.hpp"
#include "phi/core/assert.hpp"
#include "phi/core/types.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

PHI_NODISCARD constexpr u8 octal_digit_value(const char character) noexcept
{
    PHI_ASSERT(character >= '0' && character <= '7', "Character out of bounds");

    return static_cast<typename u8::value_type>(character - '0');
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TEXT_OCTAL_DIGIT_VALUE_HPP
