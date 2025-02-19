#ifndef INCG_PHI_CORE_TYPE_TRAITS_IS_CONVERTIBLE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_IS_CONVERTIBLE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/inline_variables.hpp"
#include "phi/compiler_support/intrinsics/is_convertible.hpp"
#include "phi/type_traits/integral_constant.hpp"

#if PHI_SUPPORTS_IS_CONVERTIBLE()

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename FromT, typename ToT>
struct is_convertible : public integral_constant<bool, PHI_IS_CONVERTIBLE(FromT, ToT)>
{};

template <typename FromT, typename ToT>
struct is_not_convertible : public integral_constant<bool, !PHI_IS_CONVERTIBLE(FromT, ToT)>
{};

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename FromT, typename ToT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_convertible_v = PHI_IS_CONVERTIBLE(FromT, ToT);

template <typename FromT, typename ToT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_not_convertible_v = !PHI_IS_CONVERTIBLE(FromT, ToT);

#    endif

#elif PHI_COMPILER_IS_NOT(MSVC)

#    include "phi/compiler_support/compiler.hpp"
#    include "phi/compiler_support/warning.hpp"
#    include "phi/core/declval.hpp"
#    include "phi/type_traits/is_void.hpp"

PHI_CLANG_SUPPRESS_WARNING_PUSH()
#    if PHI_COMPILER_IS_ATLEAST(CLANG, 10, 0, 0) || PHI_COMPILER_IS_ATLEAST(APPLECLANG, 12, 0, 0)
PHI_CLANG_SUPPRESS_WARNING("-Wdeprecated-volatile")
#    endif

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    template <typename TypeT>
    auto test_returnable(int)
            -> decltype(static_cast<void>(static_cast<TypeT (*)()>(nullptr)), true_type{});

    template <typename>
    auto test_returnable(...) -> false_type;

    template <typename FromT, typename ToT>
    auto test_implicitly_convertible(int)
            -> decltype(static_cast<void>(declval<void (&)(ToT)>()(declval<FromT>())), true_type{});

    template <typename, typename>
    auto test_implicitly_convertible(...) -> false_type;

} // namespace detail

template <typename FromT, typename ToT>
struct is_convertible
    : public integral_constant<bool, (decltype(detail::test_returnable<ToT>(0))::value &&
                                      decltype(detail::test_implicitly_convertible<FromT, ToT>(
                                              0))::value) ||
                                             (is_void<FromT>::value && is_void<ToT>::value)>
{};

template <typename FromT, typename ToT>
struct is_not_convertible : public integral_constant<bool, !is_convertible<FromT, ToT>::value>
{};

PHI_CLANG_SUPPRESS_WARNING_POP()

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename FromT, typename ToT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_convertible_v = is_convertible<FromT, ToT>::value;

template <typename FromT, typename ToT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_not_convertible_v = is_not_convertible<FromT, ToT>::value;

#    endif

#else

// Workaround implementation since the other version crashes the msvc compiler

#    include "phi/core/declval.hpp"
#    include "phi/type_traits/is_array.hpp"
#    include "phi/type_traits/is_function.hpp"
#    include "phi/type_traits/is_void.hpp"
#    include "phi/type_traits/remove_reference.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    template <typename TypeT>
    void test_convert(TypeT);

    template <typename FromT, typename ToT, typename = void>
    struct is_convertible_impl_test : public false_type
    {};

    template <typename FromT, typename ToT>
    struct is_convertible_impl_test<FromT, ToT,
                                    decltype(detail::test_convert<ToT>(declval<FromT>()))>
        : public true_type
    {};

    template <typename TypeT, bool IsArray = is_array<TypeT>::value,
              bool IsFunction = is_function<TypeT>::value, bool IsVoid = is_void<TypeT>::value>
    struct is_array_function_or_void
    {
        enum
        {
            value = 0
        };
    };

    template <typename TypeT>
    struct is_array_function_or_void<TypeT, true, false, false>
    {
        enum
        {
            value = 1
        };
    };

    template <typename TypeT>
    struct is_array_function_or_void<TypeT, false, true, false>
    {
        enum
        {
            value = 2
        };
    };

    template <typename TypeT>
    struct is_array_function_or_void<TypeT, false, false, true>
    {
        enum
        {
            value = 3
        };
    };
    template <typename TypeT, unsigned = detail::is_array_function_or_void<
                                      typename remove_reference<TypeT>::type>::value>
    struct is_convertible_check
    {
        static const size_t value = 0;
    };

    template <typename TypeT>
    struct is_convertible_check<TypeT, 0>
    {
        static const size_t value = sizeof(TypeT);
    };

    template <typename FromT, typename ToT,
              unsigned FromTIsArrayFunctionOrVoid = detail::is_array_function_or_void<FromT>::value,
              unsigned ToTIsArrayFunctionOrVoid   = detail::is_array_function_or_void<ToT>::value>
    struct is_convertible_impl
        : public integral_constant<bool, detail::is_convertible_impl_test<FromT, ToT>::value>
    {};

    template <typename FromT, typename ToT>
    struct is_convertible_impl<FromT, ToT, 0, 1> : public false_type
    {};
    template <typename FromT, typename ToT>
    struct is_convertible_impl<FromT, ToT, 1, 1> : public false_type
    {};
    template <typename FromT, typename ToT>
    struct is_convertible_impl<FromT, ToT, 2, 1> : public false_type
    {};
    template <typename FromT, typename ToT>
    struct is_convertible_impl<FromT, ToT, 3, 1> : public false_type
    {};

    template <typename FromT, typename ToT>
    struct is_convertible_impl<FromT, ToT, 0, 2> : public false_type
    {};
    template <typename FromT, typename ToT>
    struct is_convertible_impl<FromT, ToT, 1, 2> : public false_type
    {};
    template <typename FromT, typename ToT>
    struct is_convertible_impl<FromT, ToT, 2, 2> : public false_type
    {};
    template <typename FromT, typename ToT>
    struct is_convertible_impl<FromT, ToT, 3, 2> : public false_type
    {};

    template <typename FromT, typename ToT>
    struct is_convertible_impl<FromT, ToT, 0, 3> : public false_type
    {};
    template <typename FromT, typename ToT>
    struct is_convertible_impl<FromT, ToT, 1, 3> : public false_type
    {};
    template <typename FromT, typename ToT>
    struct is_convertible_impl<FromT, ToT, 2, 3> : public false_type
    {};
    template <typename FromT, typename ToT>
    struct is_convertible_impl<FromT, ToT, 3, 3> : public true_type
    {};
} // namespace detail

template <typename FromT, typename ToT>
struct is_convertible : public detail::is_convertible_impl<FromT, ToT>
{
private:
    static PHI_CONSTEXPR_AND_CONST size_t complete_check_from_t =
            detail::is_convertible_check<FromT>::value;
    static PHI_CONSTEXPR_AND_CONST size_t complete_check_to_t =
            detail::is_convertible_check<ToT>::value;
};

template <typename FromT, typename ToT>
struct is_not_convertible : public integral_constant<bool, !is_convertible<FromT, ToT>::value>
{};

PHI_CLANG_SUPPRESS_WARNING_POP()

#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()

template <typename FromT, typename ToT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_convertible_v = is_convertible<FromT, ToT>::value;

template <typename FromT, typename ToT>
PHI_INLINE_VARIABLE PHI_CONSTEXPR bool is_not_convertible_v = is_not_convertible<FromT, ToT>::value;

#    endif

#endif

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_IS_CONVERTIBLE_HPP
