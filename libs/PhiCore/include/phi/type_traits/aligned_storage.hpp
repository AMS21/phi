#ifndef INCG_PHI_CORE_TYPE_TRAITS_ALIGNED_STORAGE_HPP
#define INCG_PHI_CORE_TYPE_TRAITS_ALIGNED_STORAGE_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/extensions/float128.hpp"
#include "phi/core/size_t.hpp"
#include "phi/type_traits/alignment_of.hpp"
#include "phi/type_traits/conditional.hpp"
#include "phi/type_traits/detail/nat.hpp"
#include "phi/type_traits/detail/type_list.hpp"
#include "phi/type_traits/integral_constant.hpp"

DETAIL_PHI_BEGIN_NAMESPACE()

namespace detail
{
    template <typename TypeT>
    struct align_type
    {
        static PHI_CONSTEXPR_AND_CONST size_t value = alignment_of<TypeT>::value;
        using type                                  = TypeT;
    };

    struct struct_double
    {
        long double lx;
    };

    struct struct_double4
    {
        double lx[4];
    };

    using all_types = type_list<
            align_type<unsigned char>,
            type_list<
                    align_type<unsigned short>,
                    type_list<
                            align_type<unsigned int>,
                            type_list<
                                    align_type<unsigned long>,
                                    type_list<
                                            align_type<unsigned long long>,
                                            type_list<
                                                    align_type<double>,
                                                    type_list<
                                                            align_type<long double>,
                                                            type_list<
                                                                    align_type<struct_double>,
                                                                    type_list<
                                                                            align_type<
                                                                                    struct_double4>,
                                                                            type_list<
                                                                                    align_type<
                                                                                            int*>,
#if PHI_HAS_EXTENSION_FLOAT128()
                                                                                    type_list<
                                                                                            align_type<
                                                                                                    PHI_FLOAT128>,
#endif
                                                                                            nat>>>>>>>>>>
#if PHI_HAS_EXTENSION_FLOAT128()
            >
#endif
            ;

    template <size_t Align>
    struct alignas(Align) fallback_overaligned
    {};

    template <typename TypeListT, size_t Align>
    struct find_pod;

    template <typename HeadT, size_t Align>
    struct find_pod<type_list<HeadT, nat>, Align>
    {
        using type = conditional_t<Align == HeadT::value, typename HeadT::type,
                                   fallback_overaligned<Align>>;
    };

    template <typename HeadT, typename TypeT, size_t Align>
    struct find_pod<type_list<HeadT, TypeT>, Align>
    {
        using type = conditional_t<Align == HeadT::value, typename HeadT::type,
                                   typename find_pod<TypeT, Align>::type>;
    };

    template <typename TypeListT, size_t Length>
    struct find_max_align;

    template <typename HeadT, size_t Length>
    struct find_max_align<type_list<HeadT, nat>, Length>
        : public integral_constant<size_t, HeadT::value>
    {};

    template <size_t Length, size_t Align1, size_t Align2>
    struct select_align
    {
    private:
        // NOLINTNEXTLINE(bugprone-branch-clone)
        static PHI_CONSTEXPR_AND_CONST size_t min = Align2 < Align1 ? Align2 : Align1;
        // NOLINTNEXTLINE(bugprone-branch-clone)
        static PHI_CONSTEXPR_AND_CONST size_t max = Align1 < Align2 ? Align2 : Align1;

    public:
        static PHI_CONSTEXPR_AND_CONST size_t value = Length < max ? min : max;
    };

    template <typename HeadT, typename TypeT, size_t Length>
    struct find_max_align<type_list<HeadT, TypeT>, Length>
        : public integral_constant<
                  size_t,
                  select_align<Length, HeadT::value, find_max_align<TypeT, Length>::value>::value>
    {};
} // namespace detail

template <size_t Length, size_t Align = detail::find_max_align<detail::all_types, Length>::value>
struct aligned_storage
{
    using Aligner = typename detail::find_pod<detail::all_types, Align>::type;
    union type
    {
        Aligner       align;
        unsigned char data[(Length + Align - 1) / Align * Align];
    };
};

template <size_t Length, size_t Align = detail::find_max_align<detail::all_types, Length>::value>
using aligned_storage_t = typename aligned_storage<Length, Align>::type;

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_TYPE_TRAITS_ALIGNED_STORAGE_HPP
