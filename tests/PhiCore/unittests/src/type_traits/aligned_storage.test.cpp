#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/constexpr.hpp>
#include <phi/compiler_support/warning.hpp>
#include <phi/core/max_align_t.hpp>
#include <phi/type_traits/aligned_storage.hpp>
#include <phi/type_traits/alignment_of.hpp>
#include <phi/type_traits/is_pod.hpp>
#include <phi/type_traits/is_standard_layout.hpp>
#include <phi/type_traits/is_trivial.hpp>

template <typename TypeT>
void test_aligned_storage()
{
#if PHI_HAS_WORKING_IS_POD()
    STATIC_REQUIRE(phi::is_pod<TypeT>::value);
#endif
#if PHI_HAS_WORKING_IS_TRIVIAL()
    STATIC_REQUIRE(phi::is_trivial<TypeT>::value);
#endif
#if PHI_HAS_WORKING_IS_STANDARD_LAYOUT()
    STATIC_REQUIRE(phi::is_standard_layout<TypeT>::value);
#endif
}

// The following tests assume naturally aligned types exist
// up to 64bit (double). For larger types, max_align_t should
// give the correct alignment. For pre-C++11 testing, only
// the lower bound is checked.

TEST_CASE("aligned_storage")
{
    {
        using T1 = phi::aligned_storage<10, 1>::type;
        CHECK_SAME_TYPE(T1, phi::aligned_storage_t<10, 1>);

        test_aligned_storage<T1>();
        STATIC_REQUIRE(phi::alignment_of<T1>::value == 1);
        STATIC_REQUIRE(sizeof(T1) == 10);
    }
    {
        using T1 = phi::aligned_storage<10, 2>::type;
        CHECK_SAME_TYPE(T1, phi::aligned_storage_t<10, 2>);

        test_aligned_storage<T1>();
        STATIC_REQUIRE(phi::alignment_of<T1>::value == 2);
        STATIC_REQUIRE(sizeof(T1) == 10);
    }
    {
        using T1 = phi::aligned_storage<10, 4>::type;
        CHECK_SAME_TYPE(T1, phi::aligned_storage_t<10, 4>);

        test_aligned_storage<T1>();
        STATIC_REQUIRE(phi::alignment_of<T1>::value == 4);
        STATIC_REQUIRE(sizeof(T1) == 12);
    }
    {
        using T1 = phi::aligned_storage<10, 8>::type;
        CHECK_SAME_TYPE(T1, phi::aligned_storage_t<10, 8>);

        test_aligned_storage<T1>();
        STATIC_REQUIRE(phi::alignment_of<T1>::value == 8);
        STATIC_REQUIRE(sizeof(T1) == 16);
    }
    {
        using T1 = phi::aligned_storage<10, 16>::type;
        CHECK_SAME_TYPE(T1, phi::aligned_storage_t<10, 16>);

        test_aligned_storage<T1>();
        STATIC_REQUIRE(phi::alignment_of<T1>::value == 16);
        STATIC_REQUIRE(sizeof(T1) == 16);
    }
    {
        using T1 = phi::aligned_storage<10, 32>::type;
        CHECK_SAME_TYPE(T1, phi::aligned_storage_t<10, 32>);

        test_aligned_storage<T1>();
        STATIC_REQUIRE(phi::alignment_of<T1>::value == 32);
        STATIC_REQUIRE(sizeof(T1) == 32);
    }
    {
        using T1 = phi::aligned_storage<20, 32>::type;
        CHECK_SAME_TYPE(T1, phi::aligned_storage_t<20, 32>);

        test_aligned_storage<T1>();
        STATIC_REQUIRE(phi::alignment_of<T1>::value == 32);
        STATIC_REQUIRE(sizeof(T1) == 32);
    }
    {
        using T1 = phi::aligned_storage<40, 32>::type;
        CHECK_SAME_TYPE(T1, phi::aligned_storage_t<40, 32>);

        test_aligned_storage<T1>();
        STATIC_REQUIRE(phi::alignment_of<T1>::value == 32);
        STATIC_REQUIRE(sizeof(T1) == 64);
    }
    {
        using T1 = phi::aligned_storage<12, 16>::type;
        CHECK_SAME_TYPE(T1, phi::aligned_storage_t<12, 16>);

        test_aligned_storage<T1>();
        STATIC_REQUIRE(phi::alignment_of<T1>::value == 16);
        STATIC_REQUIRE(sizeof(T1) == 16);
    }
    {
        using T1 = phi::aligned_storage<1>::type;
        CHECK_SAME_TYPE(T1, phi::aligned_storage_t<1>);

        test_aligned_storage<T1>();
        STATIC_REQUIRE(phi::alignment_of<T1>::value == 1);
        STATIC_REQUIRE(sizeof(T1) == 1);
    }
    {
        using T1 = phi::aligned_storage<2>::type;
        CHECK_SAME_TYPE(T1, phi::aligned_storage_t<2>);

        test_aligned_storage<T1>();
        STATIC_REQUIRE(phi::alignment_of<T1>::value == 2);
        STATIC_REQUIRE(sizeof(T1) == 2);
    }
    {
        using T1 = phi::aligned_storage<3>::type;
        CHECK_SAME_TYPE(T1, phi::aligned_storage_t<3>);

        test_aligned_storage<T1>();
        STATIC_REQUIRE(phi::alignment_of<T1>::value == 2);
        STATIC_REQUIRE(sizeof(T1) == 4);
    }
    {
        using T1 = phi::aligned_storage<4>::type;
        CHECK_SAME_TYPE(T1, phi::aligned_storage_t<4>);

        test_aligned_storage<T1>();
        STATIC_REQUIRE(phi::alignment_of<T1>::value == 4);
        STATIC_REQUIRE(sizeof(T1) == 4);
    }
    {
        using T1 = phi::aligned_storage<5>::type;
        CHECK_SAME_TYPE(T1, phi::aligned_storage_t<5>);

        test_aligned_storage<T1>();
        STATIC_REQUIRE(phi::alignment_of<T1>::value == 4);
        STATIC_REQUIRE(sizeof(T1) == 8);
    }
    {
        using T1 = phi::aligned_storage<7>::type;
        CHECK_SAME_TYPE(T1, phi::aligned_storage_t<7>);

        test_aligned_storage<T1>();
        STATIC_REQUIRE(phi::alignment_of<T1>::value == 4);
        STATIC_REQUIRE(sizeof(T1) == 8);
    }
    {
        using T1 = phi::aligned_storage<8>::type;
        CHECK_SAME_TYPE(T1, phi::aligned_storage_t<8>);

        test_aligned_storage<T1>();
        STATIC_REQUIRE(phi::alignment_of<T1>::value == 8);
        STATIC_REQUIRE(sizeof(T1) == 8);
    }
    {
        using T1 = phi::aligned_storage<9>::type;
        CHECK_SAME_TYPE(T1, phi::aligned_storage_t<9>);

        test_aligned_storage<T1>();
        STATIC_REQUIRE(phi::alignment_of<T1>::value == 8);
        STATIC_REQUIRE(sizeof(T1) == 16);
    }
    {
        using T1 = phi::aligned_storage<15>::type;
        CHECK_SAME_TYPE(T1, phi::aligned_storage_t<15>);

        test_aligned_storage<T1>();
        STATIC_REQUIRE(phi::alignment_of<T1>::value == 8);
        STATIC_REQUIRE(sizeof(T1) == 16);
    }

    PHI_GCC_SUPPRESS_WARNING_PUSH()
#if PHI_COMPILER_IS_ATLEAST(GCC, 7, 0, 0)
    PHI_GCC_SUPPRESS_WARNING("-Wduplicated-branches")
#endif

    {
        using T1 = phi::aligned_storage<16>::type;
        CHECK_SAME_TYPE(T1, phi::aligned_storage_t<16>);

        test_aligned_storage<T1>();
        PHI_CONSTEXPR_AND_CONST phi::size_t alignment =
                alignof(phi::max_align_t) > 16 ? 16 : alignof(phi::max_align_t);
        STATIC_REQUIRE(phi::alignment_of<T1>::value == alignment);

        STATIC_REQUIRE(sizeof(T1) == 16);
    }
    {
        using T1 = phi::aligned_storage<17>::type;
        CHECK_SAME_TYPE(T1, phi::aligned_storage_t<17>);

        test_aligned_storage<T1>();
        PHI_CONSTEXPR_AND_CONST phi::size_t alignment =
                alignof(phi::max_align_t) > 16 ? 16 : alignof(phi::max_align_t);
        STATIC_REQUIRE(phi::alignment_of<T1>::value == alignment);
        STATIC_REQUIRE(sizeof(T1) == 16 + alignment);
    }

    PHI_GCC_SUPPRESS_WARNING_POP()

    {
        using T1 = phi::aligned_storage<10>::type;
        CHECK_SAME_TYPE(T1, phi::aligned_storage_t<10>);

        test_aligned_storage<T1>();
        STATIC_REQUIRE(phi::alignment_of<T1>::value == 8);
        STATIC_REQUIRE(sizeof(T1) == 16);
    }
    {
        // Max align on MSVC is 8192
        // https://learn.microsoft.com/cpp/cpp/align-cpp
#if PHI_COMPILER_IS(MSVC) || PHI_COMPILER_IS(WINCLANG)
        PHI_CONSTEXPR_AND_CONST int align = 8192;
#elif PHI_COMPILER_IS_BELOW(GCC, 7, 0, 0)
        // Max align for gcc versions before 7 is 128
        PHI_CONSTEXPR_AND_CONST int align = 128;
#else
        PHI_CONSTEXPR_AND_CONST int align = 65536;
#endif
        using T1 = typename phi::aligned_storage<1, align>::type;
        CHECK_SAME_TYPE(T1, phi::aligned_storage_t<1, align>);

        test_aligned_storage<T1>();
        STATIC_REQUIRE(phi::alignment_of<T1>::value == align);
        STATIC_REQUIRE(sizeof(T1) == align);
    }

    {
        PHI_CONSTEXPR_AND_CONST phi::size_t align_c = phi::alignment_of<char>::value;
        using T1 = typename phi::aligned_storage<4, align_c>::type;
        CHECK_SAME_TYPE(T1, phi::aligned_storage_t<4, align_c>);

        test_aligned_storage<T1>();
        STATIC_REQUIRE(sizeof(T1) >= 4);
        STATIC_REQUIRE(alignof(T1) == align_c);
    }
    {
        PHI_CONSTEXPR_AND_CONST phi::size_t align_s = phi::alignment_of<short>::value;
        using T1 = typename phi::aligned_storage<1, align_s>::type;
        CHECK_SAME_TYPE(T1, phi::aligned_storage_t<1, align_s>);

        test_aligned_storage<T1>();
        STATIC_REQUIRE(sizeof(T1) >= 1);
        STATIC_REQUIRE(alignof(T1) == align_s);
    }
    {
        PHI_CONSTEXPR_AND_CONST phi::size_t align_i = phi::alignment_of<int>::value;
        using T1 = typename phi::aligned_storage<7, align_i>::type;
        CHECK_SAME_TYPE(T1, phi::aligned_storage_t<7, align_i>);

        test_aligned_storage<T1>();
        STATIC_REQUIRE(sizeof(T1) >= 7);
        STATIC_REQUIRE(alignof(T1) == align_i);
    }
    {
        PHI_CONSTEXPR_AND_CONST phi::size_t align_d = phi::alignment_of<double>::value;
        using T1 = typename phi::aligned_storage<2, align_d>::type;
        CHECK_SAME_TYPE(T1, phi::aligned_storage_t<2, align_d>);

        test_aligned_storage<T1>();
        STATIC_REQUIRE(sizeof(T1) >= 2);
        STATIC_REQUIRE(alignof(T1) == align_d);
    }
    {
        PHI_CONSTEXPR_AND_CONST phi::size_t align_ai = phi::alignment_of<int[4]>::value;
        using T1 = typename phi::aligned_storage<20, align_ai>::type;
        CHECK_SAME_TYPE(T1, phi::aligned_storage_t<20, align_ai>);

        test_aligned_storage<T1>();
        STATIC_REQUIRE(sizeof(T1) >= 20);
        STATIC_REQUIRE(alignof(T1) == align_ai);
    }
    {
        PHI_CONSTEXPR_AND_CONST phi::size_t align_ct = phi::alignment_of<class_type>::value;
        using T1 = typename phi::aligned_storage<11, align_ct>::type;
        CHECK_SAME_TYPE(T1, phi::aligned_storage_t<11, align_ct>);

        test_aligned_storage<T1>();
        STATIC_REQUIRE(sizeof(T1) >= 11);
        STATIC_REQUIRE(alignof(T1) == align_ct);
    }
}
