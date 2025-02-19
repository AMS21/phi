#ifndef INCG_PHI_CORE_TYPE_TRAITS_DETAIL_INVOKE_IMPL_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_DETAIL_INVOKE_IMPL_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/noexcept.hpp"
#include "phi/compiler_support/warning.hpp"
#include "phi/core/declval.hpp"
#include "phi/type_traits/conditional.hpp"
#include "phi/type_traits/decay.hpp"
#include "phi/type_traits/detail/nat.hpp"
#include "phi/type_traits/enable_if.hpp"
#include "phi/type_traits/is_base_of.hpp"
#include "phi/type_traits/is_convertible.hpp"
#include "phi/type_traits/is_member_function_pointer.hpp"
#include "phi/type_traits/is_member_object_pointer.hpp"
#include "phi/type_traits/is_reference_wrapper.hpp"
#include "phi/type_traits/is_same.hpp"
#include "phi/type_traits/is_void.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

#if PHI_HAS_WORKING_IS_BASE_OF()
#    define PHI_HAS_WORKING_IS_INVOCABLE() 1
#else
#    define PHI_HAS_WORKING_IS_INVOCABLE() 0
#endif

PHI_GCC_SUPPRESS_WARNING_PUSH()
PHI_GCC_SUPPRESS_WARNING("-Wnoexcept")

namespace detail
{
    struct any
    {
        any(...);
    };

    template <typename DecayedFpT>
    struct member_pointer_class_type
    {};

    template <typename RetT, typename ClassTypeT>
    struct member_pointer_class_type<RetT ClassTypeT::*>
    {
        using type = ClassTypeT;
    };

    template <typename FunctionPointerT, typename Arg0T,
              typename DecayFpT   = typename decay<FunctionPointerT>::type,
              typename DecayArg0T = typename decay<Arg0T>::type,
              typename ClassT     = typename member_pointer_class_type<DecayFpT>::type>
    using enable_if_bullet1 = typename enable_if<is_member_function_pointer<DecayFpT>::value &&
                                                 is_base_of<ClassT, DecayArg0T>::value>::type;

    template <typename FunctionPointerT, typename Arg0T,
              typename DecayFpT   = typename decay<FunctionPointerT>::type,
              typename DecayArg0T = typename decay<Arg0T>::type>
    using enable_if_bullet2 = typename enable_if<is_member_function_pointer<DecayFpT>::value &&
                                                 is_reference_wrapper<DecayArg0T>::value>::type;

    template <typename FunctionPointerT, typename Arg0T,
              typename DecayFpT   = typename decay<FunctionPointerT>::type,
              typename DecayArg0T = typename decay<Arg0T>::type,
              typename ClassT     = typename member_pointer_class_type<DecayFpT>::type>
    using enable_if_bullet3 = typename enable_if<is_member_function_pointer<DecayFpT>::value &&
                                                 !is_base_of<ClassT, DecayArg0T>::value &&
                                                 !is_reference_wrapper<DecayArg0T>::value>::type;

    template <typename FunctionPointerT, typename Arg0T,
              typename DecayFpT   = typename decay<FunctionPointerT>::type,
              typename DecayArg0T = typename decay<Arg0T>::type,
              typename ClassT     = typename member_pointer_class_type<DecayFpT>::type>
    using enable_if_bullet4 = typename enable_if<is_member_object_pointer<DecayFpT>::value &&
                                                 is_base_of<ClassT, DecayArg0T>::value>::type;

    template <typename FunctionPointerT, typename Arg0T,
              typename DecayFpT   = typename decay<FunctionPointerT>::type,
              typename DecayArg0T = typename decay<Arg0T>::type>
    using enable_if_bullet5 = typename enable_if<is_member_object_pointer<DecayFpT>::value &&
                                                 is_reference_wrapper<DecayArg0T>::value>::type;

    template <typename FunctionPointerT, typename Arg0T,
              typename DecayFpT   = typename decay<FunctionPointerT>::type,
              typename DecayArg0T = typename decay<Arg0T>::type,
              typename ClassT     = typename member_pointer_class_type<DecayFpT>::type>
    using enable_if_bullet6 = typename enable_if<is_member_object_pointer<DecayFpT>::value &&
                                                 !is_base_of<ClassT, DecayArg0T>::value &&
                                                 !is_reference_wrapper<DecayArg0T>::value>::type;

    // invoke_impl forward declarations

    // fall back - none of the bullets

    template <typename... ArgsT>
    auto invoke_impl(any, ArgsT&&... args) -> nat;

    // bullets 1, 2 and 3

    template <typename FunctionPointerT, typename Arg0T, typename... ArgsT,
              typename = enable_if_bullet1<FunctionPointerT, Arg0T>>
    inline PHI_CONSTEXPR auto invoke_impl(FunctionPointerT&& func, Arg0T&& arg0, ArgsT&&... args)
            PHI_NOEXCEPT_EXPR(noexcept((static_cast<Arg0T&&>(arg0).*
                                        func)(static_cast<ArgsT&&>(args)...)))
                    -> decltype((static_cast<Arg0T&&>(arg0).*func)(static_cast<ArgsT&&>(args)...))
    {
        return (static_cast<Arg0T&&>(arg0).*func)(static_cast<ArgsT&&>(args)...);
    }

    template <typename FunctionPointerT, typename Arg0T, typename... ArgsT,
              typename = enable_if_bullet2<FunctionPointerT, Arg0T>>
    inline PHI_CONSTEXPR auto invoke_impl(FunctionPointerT&& func, Arg0T&& arg0, ArgsT&&... args)
            PHI_NOEXCEPT_EXPR(noexcept((arg0.get().*func)(static_cast<ArgsT&&>(args)...)))
                    -> decltype((arg0.get().*func)(static_cast<ArgsT&&>(args)...))
    {
        return (arg0.get().*func)(static_cast<ArgsT&&>(args)...);
    }

    template <typename FunctionPointerT, typename Arg0T, typename... ArgsT,
              typename = enable_if_bullet3<FunctionPointerT, Arg0T>>
    inline PHI_CONSTEXPR auto invoke_impl(FunctionPointerT&& func, Arg0T&& arg0, ArgsT&&... args)
            PHI_NOEXCEPT_EXPR(noexcept(((*static_cast<Arg0T&&>(arg0)).*
                                        func)(static_cast<ArgsT&&>(args)...)))
                    -> decltype(((*static_cast<Arg0T&&>(arg0)).*
                                 func)(static_cast<ArgsT&&>(args)...))
    {
        return ((*static_cast<Arg0T&&>(arg0)).*func)(static_cast<ArgsT&&>(args)...);
    }

    // bullets 4, 5 and 6

    template <typename FunctionPointerT, typename Arg0T,
              typename = enable_if_bullet4<FunctionPointerT, Arg0T>>
    inline PHI_CONSTEXPR auto invoke_impl(FunctionPointerT&& func, Arg0T&& arg0)
            PHI_NOEXCEPT_EXPR(noexcept(static_cast<Arg0T&&>(arg0).*func))
                    -> decltype(static_cast<Arg0T&&>(arg0).*func)
    {
        return static_cast<Arg0T&&>(arg0).*func;
    }

    template <typename FunctionPointerT, typename Arg0T,
              typename = enable_if_bullet5<FunctionPointerT, Arg0T>>
    inline PHI_CONSTEXPR auto invoke_impl(FunctionPointerT&& func, Arg0T&& arg0)
            PHI_NOEXCEPT_EXPR(noexcept(arg0.get().*func)) -> decltype(arg0.get().*func)
    {
        return arg0.get().*func;
    }

    template <typename FunctionPointerT, typename Arg0T,
              typename = enable_if_bullet6<FunctionPointerT, Arg0T>>
    inline PHI_CONSTEXPR auto invoke_impl(FunctionPointerT&& func, Arg0T&& arg0)
            PHI_NOEXCEPT_EXPR(noexcept((*static_cast<Arg0T&&>(arg0)).*func))
                    -> decltype((*static_cast<Arg0T&&>(arg0)).*func)
    {
        return (*static_cast<Arg0T&&>(arg0)).*func;
    }

    // bullet 7

    PHI_CLANG_SUPPRESS_WARNING_PUSH()
    PHI_CLANG_SUPPRESS_WARNING("-Wsign-conversion")

    template <typename FunctionPointerT, typename... ArgsT>
    inline PHI_CONSTEXPR auto invoke_impl(FunctionPointerT&& func, ArgsT&&... args)
            PHI_NOEXCEPT_EXPR(
                    noexcept(static_cast<FunctionPointerT&&>(func)(static_cast<ArgsT&&>(args)...)))
                    -> decltype(static_cast<FunctionPointerT&&>(func)(
                            static_cast<ArgsT&&>(args)...))
    {
        return static_cast<FunctionPointerT&&>(func)(static_cast<ArgsT&&>(args)...);
    }

    PHI_CLANG_SUPPRESS_WARNING_POP()

    template <typename ReturnT, typename FunctionPointerT, typename... ArgsT>
    struct invokable_r_impl
    {
        template <typename XFunctionPointerT, typename... XArgsT>
        static auto try_call(int)
                -> decltype(invoke_impl(declval<XFunctionPointerT>(), declval<XArgsT>()...));

        template <typename XFunctionPointerT, typename... XArgsT>
        static nat try_call(...);

        // FIXME: Check that ReturnT, FunctionPointerT, and ArgsT... are all complete types, cv void,
        // or incomplete array types as required by the standard.
        using ResultT = decltype(try_call<FunctionPointerT, ArgsT...>(0));

        using type = conditional_t<
                is_not_same<ResultT, nat>::value,
                conditional_t<is_void<ReturnT>::value, true_type, is_convertible<ResultT, ReturnT>>,
                false_type>;
        static PHI_CONSTEXPR_AND_CONST bool value = type::value;
    };

    template <typename FunctionPointerT, typename... ArgsT>
    using invokable_impl = invokable_r_impl<void, FunctionPointerT, ArgsT...>;

    template <bool IsInvokable, bool IsCVVoid, typename ReturnT, typename FunctionPointerT,
              typename... ArgsT>
    struct nothrow_invokable_r_impl
    {
        static PHI_CONSTEXPR_AND_CONST bool value = false;
    };

    template <typename ReturnT, typename FunctionPointerT, typename... ArgsT>
    struct nothrow_invokable_r_impl<true, false, ReturnT, FunctionPointerT, ArgsT...>
    {
        using ThisT = nothrow_invokable_r_impl;

        template <typename TypeT>
        static void test_noexcept(TypeT) PHI_NOEXCEPT;

        static PHI_CONSTEXPR_AND_CONST bool value = PHI_NOEXCEPT_EXPR(ThisT::test_noexcept<ReturnT>(
                invoke_impl(declval<FunctionPointerT>(), declval<ArgsT>()...)));
    };

    template <typename ReturnT, typename FunctionPointerT, typename... ArgsT>
    struct nothrow_invokable_r_impl<true, true, ReturnT, FunctionPointerT, ArgsT...>
    {
        static PHI_CONSTEXPR_AND_CONST bool value =
                PHI_NOEXCEPT_EXPR(invoke_impl(declval<FunctionPointerT>(), declval<ArgsT>()...));
    };

    template <typename ReturnT, typename FunctionPointerT, typename... ArgsT>
    using nothrow_invokable_r =
            nothrow_invokable_r_impl<invokable_r_impl<ReturnT, FunctionPointerT, ArgsT...>::value,
                                     is_void<ReturnT>::value, ReturnT, FunctionPointerT, ArgsT...>;

    template <typename FunctionPointerT, typename... ArgsT>
    using nothrow_invokable =
            nothrow_invokable_r_impl<invokable_impl<FunctionPointerT, ArgsT...>::value, true, void,
                                     FunctionPointerT, ArgsT...>;

    template <typename FunctionPointerT, typename... ArgsT>
    struct invoke_of
        : public enable_if<invokable_impl<FunctionPointerT, ArgsT...>::value,
                           typename invokable_r_impl<void, FunctionPointerT, ArgsT...>::ResultT>
    {};
} // namespace detail

PHI_GCC_SUPPRESS_WARNING_POP()

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_DETAIL_INVOKE_IMPL_HPP
