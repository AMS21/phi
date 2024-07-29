#include <phi/test/test_macros.hpp>

#include <phi/compiler_support/warning.hpp>
#include <phi/core/narrow_cast.hpp>
#include <phi/core/types.hpp>
#include <phi/type_traits/make_unsafe.hpp>
#include <phi/type_traits/to_unsafe.hpp>

#if PHI_HAS_FEATURE_EXTENDED_CONSTEXPR() || !defined(PHI_DEBUG)
#    define TEST_NARROW_CAST(...) STATIC_REQUIRE(__VA_ARGS__)
#else
#    define TEST_NARROW_CAST(...) REQUIRE(__VA_ARGS__)
#endif

using namespace phi::literals;

PHI_CLANG_AND_GCC_SUPPRESS_WARNING("-Wfloat-equal")

template <typename TypeT>
void test_narrow_cast()
{
    using UnsafeT = phi::make_unsafe_t<TypeT>;

    // From unsafe signed int
    TEST_NARROW_CAST(phi::to_unsafe(phi::narrow_cast<TypeT>(phi::int8_t(1))) == UnsafeT(1));
    TEST_NARROW_CAST(phi::to_unsafe(phi::narrow_cast<TypeT>(phi::int16_t(2))) == UnsafeT(2));
    TEST_NARROW_CAST(phi::to_unsafe(phi::narrow_cast<TypeT>(phi::int32_t(3))) == UnsafeT(3));
    TEST_NARROW_CAST(phi::to_unsafe(phi::narrow_cast<TypeT>(phi::int64_t(4))) == UnsafeT(4));

    // From unsafe unph)i::to_unsafe(signed int
    TEST_NARROW_CAST(phi::to_unsafe(phi::narrow_cast<TypeT>(phi::uint8_t(1))) == UnsafeT(1));
    TEST_NARROW_CAST(phi::to_unsafe(phi::narrow_cast<TypeT>(phi::uint16_t(2))) == UnsafeT(2));
    TEST_NARROW_CAST(phi::to_unsafe(phi::narrow_cast<TypeT>(phi::uint32_t(3))) == UnsafeT(3));
    TEST_NARROW_CAST(phi::to_unsafe(phi::narrow_cast<TypeT>(phi::uint64_t(4))) == UnsafeT(4));

    // From safe signph)i::to_unsafe(ed int
    TEST_NARROW_CAST(phi::to_unsafe(phi::narrow_cast<TypeT>(1_i8)) == UnsafeT(1));
    TEST_NARROW_CAST(phi::to_unsafe(phi::narrow_cast<TypeT>(2_i16)) == UnsafeT(2));
    TEST_NARROW_CAST(phi::to_unsafe(phi::narrow_cast<TypeT>(3_i32)) == UnsafeT(3));
    TEST_NARROW_CAST(phi::to_unsafe(phi::narrow_cast<TypeT>(4_i64)) == UnsafeT(4));

    // From safe unsiph)i::to_unsafe(gned int
    TEST_NARROW_CAST(phi::to_unsafe(phi::narrow_cast<TypeT>(1_u8)) == UnsafeT(1));
    TEST_NARROW_CAST(phi::to_unsafe(phi::narrow_cast<TypeT>(2_u16)) == UnsafeT(2));
    TEST_NARROW_CAST(phi::to_unsafe(phi::narrow_cast<TypeT>(3_u32)) == UnsafeT(3));
    TEST_NARROW_CAST(phi::to_unsafe(phi::narrow_cast<TypeT>(4_u64)) == UnsafeT(4));

    // From unsafe flph)i::to_unsafe(oating point
    TEST_NARROW_CAST(phi::to_unsafe(phi::narrow_cast<TypeT>(1.0f)) == UnsafeT(1));
    TEST_NARROW_CAST(phi::to_unsafe(phi::narrow_cast<TypeT>(2.0)) == UnsafeT(2));
    TEST_NARROW_CAST(phi::to_unsafe(phi::narrow_cast<TypeT>(3.0l)) == UnsafeT(3));

    // From safe floaph)i::to_unsafe(ting point
    TEST_NARROW_CAST(phi::to_unsafe(phi::narrow_cast<TypeT>(phi::floating_point<float>(1.0f))) ==
                     UnsafeT(1));
    TEST_NARROW_CAST(phi::to_unsafe(phi::narrow_cast<TypeT>(phi::floating_point<double>(2.0))) ==
                     UnsafeT(2));
    TEST_NARROW_CAST(phi::to_unsafe(phi::narrow_cast<TypeT>(
                             phi::floating_point<long double>(3.0l))) == UnsafeT(3));
}

TEST_CASE("narrow_cast")
{
    // From unsafe signed int
    test_narrow_cast<phi::int8_t>();
    test_narrow_cast<phi::int16_t>();
    test_narrow_cast<phi::int32_t>();
    test_narrow_cast<phi::int64_t>();

    // From unsafe unsigned int
    test_narrow_cast<phi::uint8_t>();
    test_narrow_cast<phi::uint16_t>();
    test_narrow_cast<phi::uint32_t>();
    test_narrow_cast<phi::uint64_t>();

    // From safe signed int
    test_narrow_cast<phi::i8>();
    test_narrow_cast<phi::i16>();
    test_narrow_cast<phi::i32>();
    test_narrow_cast<phi::i64>();

    // From safe unsigned int
    test_narrow_cast<phi::u8>();
    test_narrow_cast<phi::u16>();
    test_narrow_cast<phi::u32>();
    test_narrow_cast<phi::u64>();

    // From unsafe floating point
    test_narrow_cast<float>();
    test_narrow_cast<double>();
    test_narrow_cast<long double>();

    // From safe floating point
    test_narrow_cast<phi::floating_point<float>>();
    test_narrow_cast<phi::floating_point<double>>();
    test_narrow_cast<phi::floating_point<long double>>();
}

TEST_CASE("narrow_cast const usage")
{
    // not const - not const
    {
        phi::i32 large = 21;

        phi::i8 small = phi::narrow_cast<phi::i8>(large);
        CHECK(small.unsafe() == 21);
    }

    // const - not const
    {
        const phi::i32 large = 21;

        phi::i8 small = phi::narrow_cast<phi::i8>(large);
        CHECK(small.unsafe() == 21);
    }

    // not const - const
    {
        phi::i32 large = 21;

        const phi::i8 small = phi::narrow_cast<phi::i8>(large);
        CHECK(small.unsafe() == 21);
    }

    // const - const
    {
        const phi::i32 large = 21;

        const phi::i8 small = phi::narrow_cast<phi::i8>(large);
        CHECK(small.unsafe() == 21);
    }
}

enum E1
{
    A = 0,
    B = 1,
};

enum E2 : unsigned
{
    C = 1u,
    D = 2u,
};

enum E3
{
    E = -1,
    F = -2,
};

TEST_CASE("narrow_cast enum -> int")
{
    TEST_NARROW_CAST(phi::narrow_cast<int>(E1::A) == 0);
    TEST_NARROW_CAST(phi::narrow_cast<int>(E1::B) == 1);
    TEST_NARROW_CAST(phi::narrow_cast<int>(E2::C) == 1);
    TEST_NARROW_CAST(phi::narrow_cast<int>(E2::D) == 2);
    TEST_NARROW_CAST(phi::narrow_cast<int>(E3::E) == -1);
    TEST_NARROW_CAST(phi::narrow_cast<int>(E3::F) == -2);
}

TEST_CASE("narrow_cast int -> enum")
{
    TEST_NARROW_CAST(phi::narrow_cast<E1>(0) == E1::A);
    TEST_NARROW_CAST(phi::narrow_cast<E1>(1) == E1::B);
    TEST_NARROW_CAST(phi::narrow_cast<E2>(1) == E2::C);
    TEST_NARROW_CAST(phi::narrow_cast<E2>(2) == E2::D);
    TEST_NARROW_CAST(phi::narrow_cast<E3>(-1) == E3::E);
    TEST_NARROW_CAST(phi::narrow_cast<E3>(-2) == E3::F);
}

enum class SE1
{
    A = 0,
    B = 1,
};

enum class SE2 : unsigned
{
    A = 0u,
    B = 2u,
};

enum class SE3
{
    A = -1,
    B = -2,
};

TEST_CASE("narrow_cast strong enum -> int")
{
    TEST_NARROW_CAST(phi::narrow_cast<int>(SE1::A) == 0);
    TEST_NARROW_CAST(phi::narrow_cast<int>(SE1::B) == 1);
    TEST_NARROW_CAST(phi::narrow_cast<int>(SE2::A) == 0);
    TEST_NARROW_CAST(phi::narrow_cast<int>(SE2::B) == 2);
    TEST_NARROW_CAST(phi::narrow_cast<int>(SE3::A) == -1);
    TEST_NARROW_CAST(phi::narrow_cast<int>(SE3::B) == -2);
}

TEST_CASE("narrow_cast int -> strong enum")
{
    TEST_NARROW_CAST(phi::narrow_cast<SE1>(0) == SE1::A);
    TEST_NARROW_CAST(phi::narrow_cast<SE1>(1) == SE1::B);
    TEST_NARROW_CAST(phi::narrow_cast<SE2>(0) == SE2::A);
    TEST_NARROW_CAST(phi::narrow_cast<SE2>(2) == SE2::B);
    TEST_NARROW_CAST(phi::narrow_cast<SE3>(-1) == SE3::A);
    TEST_NARROW_CAST(phi::narrow_cast<SE3>(-2) == SE3::B);
}
