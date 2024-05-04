#ifndef INCG_PHI_CORE_SOURCE_LOCATION_HPP
#define INCG_PHI_CORE_SOURCE_LOCATION_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/intrinsics/source_location.hpp"
#include "phi/compiler_support/noexcept.hpp"
#include "phi/container/string_view.hpp"
#include "phi/core/assert.hpp"
#include "phi/core/sized_types.hpp"
#include "phi/type_traits/false_t.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

struct source_location
{
    using this_type = source_location;

    PHI_CONSTEXPR source_location() PHI_NOEXCEPT : m_FileName{""},
                                                   m_FunctionName{m_FileName},
                                                   m_LineNumber{0},
                                                   m_Column{0}
    {}

    // NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
    PHI_CONSTEXPR source_location(const char* file, const char* function, uint_least32_t line,
                                  uint_least32_t column) PHI_NOEXCEPT : m_FileName{file},
                                                                        m_FunctionName{function},
                                                                        m_LineNumber{line},
                                                                        m_Column{column}
    {
#if PHI_HAS_FEATURE_EXTENDED_CONSTEXPR()
        PHI_ASSERT(file != nullptr, "phi::source_location: Invalid file name");
        PHI_ASSERT(function != nullptr, "phi::source_location: Invalid function name");
        PHI_ASSERT(line > 0u, "phi::source_location: Invalid line number");
#endif
    }

#if PHI_SUPPORTS_BUILTIN_LINE()
    static PHI_CONSTEXPR source_location current(
            const char* file = __builtin_FILE(), const char* function = __builtin_FUNCTION(),
            uint_least32_t line = static_cast<uint_least32_t>(__builtin_LINE())
#    if PHI_SUPPORTS_BUILTIN_COLUMN()
                    ,
            uint_least32_t column = __builtin_COLUMN()
#    endif
                    ) PHI_NOEXCEPT
    {
        return source_location{file, function, line,
#    if PHI_SUPPORTS_BUILTIN_COLUMN()
                               column
#    else
                               0
#    endif
        };
    }
#else
    template <typename TypeT = void>
    static PHI_CONSTEXPR source_location current() PHI_NOEXCEPT
    {
        static_assert(false_t<TypeT>::value,
                      "phi::source_location requires compiler support for current.");

        return {};
    }
#endif

    PHI_NODISCARD PHI_CONSTEXPR uint_least32_t line() const PHI_NOEXCEPT
    {
        return m_LineNumber;
    }

    PHI_NODISCARD PHI_CONSTEXPR uint_least32_t column() const PHI_NOEXCEPT
    {
        return m_Column;
    }

    PHI_NODISCARD PHI_CONSTEXPR const char* file_name() const PHI_NOEXCEPT
    {
        return m_FileName;
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR string_view file_name_view() const PHI_NOEXCEPT
    {
        return m_FileName;
    }

    PHI_NODISCARD PHI_CONSTEXPR const char* function_name() const PHI_NOEXCEPT
    {
        return m_FunctionName;
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR string_view function_name_view() const PHI_NOEXCEPT
    {
        return m_FunctionName;
    }

private:
    const char*    m_FileName;
    const char*    m_FunctionName;
    uint_least32_t m_LineNumber;
    uint_least32_t m_Column;
};

#if PHI_SUPPORTS_BUILTIN_LINE()
#    define PHI_SOURCE_LOCATION_CURRENT() ::phi::source_location::current()
#else
#    define PHI_SOURCE_LOCATION_CURRENT()                                                          \
        ::phi::source_location(__FILE__, __FUNCTION__, __LINE__, 0u)
#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_SOURCE_LOCATION_HPP
