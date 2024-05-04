// This file is heavily inspired by Jonathan Müllers <jonathanmueller.dev@gmail.com> type_safe library https://github.com/foonathan/type_safe
// licensed under the MIT license https://github.com/foonathan/type_safe/blob/master/LICENSE
// Original file at https://github.com/foonathan/type_safe/blob/master/test/integer.cpp
/* MIT License

Copyright (c) 2016-2020 Jonathan Müller

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "constexpr_helper.hpp"
#include <phi/compiler_support/compiler.hpp>
#include <phi/compiler_support/constexpr.hpp>
#include <phi/compiler_support/platform.hpp>
#include <phi/compiler_support/warning.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/sized_types.hpp>
#include <phi/test/test_macros.hpp>
#include <phi/type_traits/is_assignable.hpp>
#include <phi/type_traits/is_constructible.hpp>
#include <phi/type_traits/is_convertible.hpp>
#include <phi/type_traits/is_copy_assignable.hpp>
#include <phi/type_traits/is_copy_constructible.hpp>
#include <phi/type_traits/is_default_constructible.hpp>
#include <phi/type_traits/is_move_assignable.hpp>
#include <phi/type_traits/is_move_constructible.hpp>
#include <phi/type_traits/is_nothrow_assignable.hpp>
#include <phi/type_traits/is_nothrow_constructible.hpp>
#include <phi/type_traits/is_nothrow_convertible.hpp>
#include <phi/type_traits/is_nothrow_copy_assignable.hpp>
#include <phi/type_traits/is_nothrow_copy_constructible.hpp>
#include <phi/type_traits/is_nothrow_default_constructible.hpp>
#include <phi/type_traits/is_nothrow_move_assignable.hpp>
#include <phi/type_traits/is_nothrow_move_constructible.hpp>
#include <phi/type_traits/is_same.hpp>
#include <phi/type_traits/is_standard_layout.hpp>
#include <phi/type_traits/is_trivially_copyable.hpp>
#include <phi/type_traits/is_trivially_destructible.hpp>
#include <limits>
#include <sstream>
#include <string>

template <typename TypeT>
void test_integer_layout()
{
    STATIC_REQUIRE(sizeof(TypeT) == sizeof(typename TypeT::value_type));

#if PHI_HAS_WORKING_IS_STANDARD_LAYOUT()
    STATIC_REQUIRE(phi::is_standard_layout<TypeT>::value);
#endif
#if PHI_HAS_WORKING_IS_TRIVIALLY_COPYABLE()
    STATIC_REQUIRE(phi::is_trivially_copyable<TypeT>::value);
#endif
#if PHI_HAS_WORKING_IS_TRIVIALLY_DESTRUCTIBLE()
    STATIC_REQUIRE(phi::is_trivially_destructible<TypeT>::value);
#endif

#if PHI_HAS_WORKING_IS_DEFAULT_CONSTRUCTIBLE()
    STATIC_REQUIRE_FALSE(phi::is_default_constructible<TypeT>::value);
#endif
#if PHI_HAS_WORKING_IS_NOTHROW_DEFAULT_CONSTRUCTIBLE()
    STATIC_REQUIRE_FALSE(phi::is_nothrow_default_constructible<TypeT>::value);
#endif

    STATIC_REQUIRE(phi::is_copy_assignable<TypeT>::value);
    STATIC_REQUIRE(phi::is_nothrow_copy_assignable<TypeT>::value);
    STATIC_REQUIRE(phi::is_copy_constructible<TypeT>::value);
    STATIC_REQUIRE(phi::is_nothrow_copy_constructible<TypeT>::value);
    STATIC_REQUIRE(phi::is_move_assignable<TypeT>::value);
    STATIC_REQUIRE(phi::is_nothrow_move_assignable<TypeT>::value);
    STATIC_REQUIRE(phi::is_move_constructible<TypeT>::value);
    STATIC_REQUIRE(phi::is_nothrow_move_constructible<TypeT>::value);
}

template <typename LhsT, typename RhsT>
void test_integer_convertible()
{
    STATIC_REQUIRE(phi::is_constructible<LhsT, RhsT>::value);
    STATIC_REQUIRE(phi::is_nothrow_constructible<LhsT, RhsT>::value);
    STATIC_REQUIRE(phi::is_assignable<LhsT, RhsT>::value);
    STATIC_REQUIRE(phi::is_nothrow_assignable<LhsT, RhsT>::value);
    STATIC_REQUIRE_FALSE(phi::is_convertible<LhsT, RhsT>::value);
    STATIC_REQUIRE_FALSE(phi::is_nothrow_convertible<LhsT, RhsT>::value);

    STATIC_REQUIRE(phi::is_constructible<RhsT, LhsT>::value ==
                   phi::is_same<typename LhsT::value_type, RhsT>::value);
    STATIC_REQUIRE(phi::is_nothrow_constructible<RhsT, LhsT>::value ==
                   phi::is_same<typename LhsT::value_type, RhsT>::value);
    STATIC_REQUIRE(phi::is_convertible<RhsT, LhsT>::value);
    STATIC_REQUIRE(phi::is_nothrow_convertible<RhsT, LhsT>::value);
}

template <typename LhsT, typename RhsT>
void test_integer_not_convertible()
{
    STATIC_REQUIRE_FALSE(phi::is_constructible<LhsT, RhsT>::value);
    STATIC_REQUIRE_FALSE(phi::is_nothrow_constructible<LhsT, RhsT>::value);
    STATIC_REQUIRE_FALSE(phi::is_assignable<LhsT, RhsT>::value);
    STATIC_REQUIRE_FALSE(phi::is_nothrow_assignable<LhsT, RhsT>::value);
    STATIC_REQUIRE_FALSE(phi::is_convertible<LhsT, RhsT>::value);
    STATIC_REQUIRE_FALSE(phi::is_nothrow_convertible<LhsT, RhsT>::value);

    STATIC_REQUIRE_FALSE(phi::is_constructible<RhsT, LhsT>::value);
    STATIC_REQUIRE_FALSE(phi::is_nothrow_constructible<RhsT, LhsT>::value);
    STATIC_REQUIRE_FALSE(phi::is_convertible<RhsT, LhsT>::value);
    STATIC_REQUIRE_FALSE(phi::is_nothrow_convertible<RhsT, LhsT>::value);
}

PHI_GCC_SUPPRESS_WARNING_PUSH()
PHI_GCC_SUPPRESS_WARNING("-Wuseless-cast")

PHI_CLANG_SUPPRESS_WARNING_PUSH()
PHI_CLANG_SUPPRESS_WARNING("-Wtautological-compare")

// NOLINTNEXTLINE(readability-function-size)
TEST_CASE("integer")
{
    SECTION("integer layout", "[Utility][Types][integer]")
    {
        STATIC_REQUIRE(sizeof(phi::integer<phi::int8_t>) == sizeof(phi::int8_t));
        STATIC_REQUIRE(sizeof(phi::integer<phi::int16_t>) == sizeof(phi::int16_t));
        STATIC_REQUIRE(sizeof(phi::integer<phi::int32_t>) == sizeof(phi::int32_t));
        STATIC_REQUIRE(sizeof(phi::integer<phi::int64_t>) == sizeof(phi::int64_t));

        STATIC_REQUIRE(sizeof(phi::integer<phi::uint8_t>) == sizeof(phi::uint8_t));
        STATIC_REQUIRE(sizeof(phi::integer<phi::uint16_t>) == sizeof(phi::uint16_t));
        STATIC_REQUIRE(sizeof(phi::integer<phi::uint32_t>) == sizeof(phi::uint32_t));
        STATIC_REQUIRE(sizeof(phi::integer<phi::uint64_t>) == sizeof(phi::uint64_t));

        test_integer_layout<phi::integer<phi::int8_t>>();
        test_integer_layout<phi::integer<phi::int16_t>>();
        test_integer_layout<phi::integer<phi::int32_t>>();
        test_integer_layout<phi::integer<phi::int64_t>>();

        test_integer_layout<phi::integer<phi::uint8_t>>();
        test_integer_layout<phi::integer<phi::uint16_t>>();
        test_integer_layout<phi::integer<phi::uint32_t>>();
        test_integer_layout<phi::integer<phi::uint64_t>>();
    }

    SECTION("integer conversion checks", "[Utility][Types][integer]")
    {
        // phi::int8_t
        test_integer_convertible<phi::integer<phi::int8_t>, phi::int8_t>();
        test_integer_not_convertible<phi::integer<phi::int8_t>, phi::int16_t>();
        test_integer_not_convertible<phi::integer<phi::int8_t>, phi::int32_t>();
        test_integer_not_convertible<phi::integer<phi::int8_t>, phi::int64_t>();

        test_integer_not_convertible<phi::integer<phi::int8_t>, phi::uint8_t>();
        test_integer_not_convertible<phi::integer<phi::int8_t>, phi::uint16_t>();
        test_integer_not_convertible<phi::integer<phi::int8_t>, phi::uint32_t>();
        test_integer_not_convertible<phi::integer<phi::int8_t>, phi::uint64_t>();

        test_integer_not_convertible<phi::integer<phi::int8_t>, bool>();
        test_integer_not_convertible<phi::integer<phi::int8_t>, phi::boolean>();
        test_integer_not_convertible<phi::integer<phi::int8_t>, char>();
        test_integer_not_convertible<phi::integer<phi::int8_t>, wchar_t>();
        test_integer_not_convertible<phi::integer<phi::int8_t>, char16_t>();
        test_integer_not_convertible<phi::integer<phi::int8_t>, char32_t>();
        test_integer_not_convertible<phi::integer<phi::int8_t>, float>();
        test_integer_not_convertible<phi::integer<phi::int8_t>, double>();
        test_integer_not_convertible<phi::integer<phi::int8_t>, long double>();

        // phi::int16_t
        test_integer_convertible<phi::integer<phi::int16_t>, phi::int8_t>();
        test_integer_convertible<phi::integer<phi::int16_t>, phi::int16_t>();
        test_integer_not_convertible<phi::integer<phi::int16_t>, phi::int32_t>();
        test_integer_not_convertible<phi::integer<phi::int16_t>, phi::int64_t>();

        test_integer_convertible<phi::integer<phi::int16_t>, phi::uint8_t>();
        test_integer_not_convertible<phi::integer<phi::int16_t>, phi::uint16_t>();
        test_integer_not_convertible<phi::integer<phi::int16_t>, phi::uint32_t>();
        test_integer_not_convertible<phi::integer<phi::int16_t>, phi::uint64_t>();

        test_integer_not_convertible<phi::integer<phi::int16_t>, bool>();
        test_integer_not_convertible<phi::integer<phi::int16_t>, phi::boolean>();
        test_integer_not_convertible<phi::integer<phi::int16_t>, char>();
        test_integer_not_convertible<phi::integer<phi::int16_t>, wchar_t>();
        test_integer_not_convertible<phi::integer<phi::int16_t>, char16_t>();
        test_integer_not_convertible<phi::integer<phi::int16_t>, char32_t>();
        test_integer_not_convertible<phi::integer<phi::int16_t>, float>();
        test_integer_not_convertible<phi::integer<phi::int16_t>, double>();
        test_integer_not_convertible<phi::integer<phi::int16_t>, long double>();

        // phi::int32_t
        test_integer_convertible<phi::integer<phi::int32_t>, phi::int8_t>();
        test_integer_convertible<phi::integer<phi::int32_t>, phi::int16_t>();
        test_integer_convertible<phi::integer<phi::int32_t>, phi::int32_t>();
        test_integer_not_convertible<phi::integer<phi::int32_t>, phi::int64_t>();

        test_integer_convertible<phi::integer<phi::int32_t>, phi::uint8_t>();
        test_integer_convertible<phi::integer<phi::int32_t>, phi::uint16_t>();
        test_integer_not_convertible<phi::integer<phi::int32_t>, phi::uint32_t>();
        test_integer_not_convertible<phi::integer<phi::int32_t>, phi::uint64_t>();

        test_integer_not_convertible<phi::integer<phi::int32_t>, bool>();
        test_integer_not_convertible<phi::integer<phi::int32_t>, phi::boolean>();
        test_integer_not_convertible<phi::integer<phi::int32_t>, char>();
        test_integer_not_convertible<phi::integer<phi::int32_t>, wchar_t>();
        test_integer_not_convertible<phi::integer<phi::int32_t>, char16_t>();
        test_integer_not_convertible<phi::integer<phi::int32_t>, char32_t>();
        test_integer_not_convertible<phi::integer<phi::int32_t>, float>();
        test_integer_not_convertible<phi::integer<phi::int32_t>, double>();
        test_integer_not_convertible<phi::integer<phi::int32_t>, long double>();

        // phi::int64_t
        test_integer_convertible<phi::integer<phi::int64_t>, phi::int8_t>();
        test_integer_convertible<phi::integer<phi::int64_t>, phi::int16_t>();
        test_integer_convertible<phi::integer<phi::int64_t>, phi::int32_t>();
        test_integer_convertible<phi::integer<phi::int64_t>, phi::int64_t>();

        test_integer_convertible<phi::integer<phi::int64_t>, phi::uint8_t>();
        test_integer_convertible<phi::integer<phi::int64_t>, phi::uint16_t>();
        test_integer_convertible<phi::integer<phi::int64_t>, phi::uint32_t>();
        test_integer_not_convertible<phi::integer<phi::int64_t>, phi::uint64_t>();

        test_integer_not_convertible<phi::integer<phi::int64_t>, bool>();
        test_integer_not_convertible<phi::integer<phi::int64_t>, phi::boolean>();
        test_integer_not_convertible<phi::integer<phi::int64_t>, char>();
        test_integer_not_convertible<phi::integer<phi::int64_t>, wchar_t>();
        test_integer_not_convertible<phi::integer<phi::int64_t>, char16_t>();
        test_integer_not_convertible<phi::integer<phi::int64_t>, char32_t>();
        test_integer_not_convertible<phi::integer<phi::int64_t>, float>();
        test_integer_not_convertible<phi::integer<phi::int64_t>, double>();
        test_integer_not_convertible<phi::integer<phi::int64_t>, long double>();

        // phi::uint8_t
        test_integer_not_convertible<phi::integer<phi::uint8_t>, phi::int8_t>();
        test_integer_not_convertible<phi::integer<phi::uint8_t>, phi::int16_t>();
        test_integer_not_convertible<phi::integer<phi::uint8_t>, phi::int32_t>();
        test_integer_not_convertible<phi::integer<phi::uint8_t>, phi::int64_t>();

        test_integer_convertible<phi::integer<phi::uint8_t>, phi::uint8_t>();
        test_integer_not_convertible<phi::integer<phi::uint8_t>, phi::uint16_t>();
        test_integer_not_convertible<phi::integer<phi::uint8_t>, phi::uint32_t>();
        test_integer_not_convertible<phi::integer<phi::uint8_t>, phi::uint64_t>();

        test_integer_not_convertible<phi::integer<phi::uint8_t>, bool>();
        test_integer_not_convertible<phi::integer<phi::uint8_t>, phi::boolean>();
        test_integer_not_convertible<phi::integer<phi::uint8_t>, char>();
        test_integer_not_convertible<phi::integer<phi::uint8_t>, wchar_t>();
        test_integer_not_convertible<phi::integer<phi::uint8_t>, char16_t>();
        test_integer_not_convertible<phi::integer<phi::uint8_t>, char32_t>();
        test_integer_not_convertible<phi::integer<phi::uint8_t>, float>();
        test_integer_not_convertible<phi::integer<phi::uint8_t>, double>();
        test_integer_not_convertible<phi::integer<phi::uint8_t>, long double>();

        // phi::uint16_t
        test_integer_not_convertible<phi::integer<phi::uint16_t>, phi::int8_t>();
        test_integer_not_convertible<phi::integer<phi::uint16_t>, phi::int16_t>();
        test_integer_not_convertible<phi::integer<phi::uint16_t>, phi::int32_t>();
        test_integer_not_convertible<phi::integer<phi::uint16_t>, phi::int64_t>();

        test_integer_convertible<phi::integer<phi::uint16_t>, phi::uint8_t>();
        test_integer_convertible<phi::integer<phi::uint16_t>, phi::uint16_t>();
        test_integer_not_convertible<phi::integer<phi::uint16_t>, phi::uint32_t>();
        test_integer_not_convertible<phi::integer<phi::uint16_t>, phi::uint64_t>();

        test_integer_not_convertible<phi::integer<phi::uint16_t>, bool>();
        test_integer_not_convertible<phi::integer<phi::uint16_t>, phi::boolean>();
        test_integer_not_convertible<phi::integer<phi::uint16_t>, char>();
        test_integer_not_convertible<phi::integer<phi::uint16_t>, wchar_t>();
        test_integer_not_convertible<phi::integer<phi::uint16_t>, char16_t>();
        test_integer_not_convertible<phi::integer<phi::uint16_t>, char32_t>();
        test_integer_not_convertible<phi::integer<phi::uint16_t>, float>();
        test_integer_not_convertible<phi::integer<phi::uint16_t>, double>();
        test_integer_not_convertible<phi::integer<phi::uint16_t>, long double>();

        // phi::uint32_t
        test_integer_not_convertible<phi::integer<phi::uint32_t>, phi::int8_t>();
        test_integer_not_convertible<phi::integer<phi::uint32_t>, phi::int16_t>();
        test_integer_not_convertible<phi::integer<phi::uint32_t>, phi::int32_t>();
        test_integer_not_convertible<phi::integer<phi::uint32_t>, phi::int64_t>();

        test_integer_convertible<phi::integer<phi::uint32_t>, phi::uint8_t>();
        test_integer_convertible<phi::integer<phi::uint32_t>, phi::uint16_t>();
        test_integer_convertible<phi::integer<phi::uint32_t>, phi::uint32_t>();
        test_integer_not_convertible<phi::integer<phi::uint32_t>, phi::uint64_t>();

        test_integer_not_convertible<phi::integer<phi::uint32_t>, bool>();
        test_integer_not_convertible<phi::integer<phi::uint32_t>, phi::boolean>();
        test_integer_not_convertible<phi::integer<phi::uint32_t>, char>();
        test_integer_not_convertible<phi::integer<phi::uint32_t>, wchar_t>();
        test_integer_not_convertible<phi::integer<phi::uint32_t>, char16_t>();
        test_integer_not_convertible<phi::integer<phi::uint32_t>, char32_t>();
        test_integer_not_convertible<phi::integer<phi::uint32_t>, float>();
        test_integer_not_convertible<phi::integer<phi::uint32_t>, double>();
        test_integer_not_convertible<phi::integer<phi::uint32_t>, long double>();

        // phi::uint64_t
        test_integer_not_convertible<phi::integer<phi::uint64_t>, phi::int8_t>();
        test_integer_not_convertible<phi::integer<phi::uint64_t>, phi::int16_t>();
        test_integer_not_convertible<phi::integer<phi::uint64_t>, phi::int32_t>();
        test_integer_not_convertible<phi::integer<phi::uint64_t>, phi::int64_t>();

        test_integer_convertible<phi::integer<phi::uint64_t>, phi::uint8_t>();
        test_integer_convertible<phi::integer<phi::uint64_t>, phi::uint16_t>();
        test_integer_convertible<phi::integer<phi::uint64_t>, phi::uint32_t>();
        test_integer_convertible<phi::integer<phi::uint64_t>, phi::uint64_t>();

        test_integer_not_convertible<phi::integer<phi::uint64_t>, bool>();
        test_integer_not_convertible<phi::integer<phi::uint64_t>, phi::boolean>();
        test_integer_not_convertible<phi::integer<phi::uint64_t>, char>();
        test_integer_not_convertible<phi::integer<phi::uint64_t>, wchar_t>();
        test_integer_not_convertible<phi::integer<phi::uint64_t>, char16_t>();
        test_integer_not_convertible<phi::integer<phi::uint64_t>, char32_t>();
        test_integer_not_convertible<phi::integer<phi::uint64_t>, float>();
        test_integer_not_convertible<phi::integer<phi::uint64_t>, double>();
        test_integer_not_convertible<phi::integer<phi::uint64_t>, long double>();
    }

    SECTION("integer", "[Utility][Types][integer]")
    {
        using int_t = phi::integer<phi::int32_t>;

        SECTION("Type traits")
        {
            // this_type
            CHECK_SAME_TYPE(phi::integer<phi::int8_t>::this_type, phi::integer<phi::int8_t>);
            CHECK_SAME_TYPE(phi::integer<phi::int16_t>::this_type, phi::integer<phi::int16_t>);
            CHECK_SAME_TYPE(phi::integer<phi::int32_t>::this_type, phi::integer<phi::int32_t>);
            CHECK_SAME_TYPE(phi::integer<phi::int64_t>::this_type, phi::integer<phi::int64_t>);

            CHECK_SAME_TYPE(phi::integer<phi::uint8_t>::this_type, phi::integer<phi::uint8_t>);
            CHECK_SAME_TYPE(phi::integer<phi::uint16_t>::this_type, phi::integer<phi::uint16_t>);
            CHECK_SAME_TYPE(phi::integer<phi::uint32_t>::this_type, phi::integer<phi::uint32_t>);
            CHECK_SAME_TYPE(phi::integer<phi::uint64_t>::this_type, phi::integer<phi::uint64_t>);

            // value_type
            CHECK_SAME_TYPE(phi::integer<phi::int8_t>::value_type, phi::int8_t);
            CHECK_SAME_TYPE(phi::integer<phi::int16_t>::value_type, phi::int16_t);
            CHECK_SAME_TYPE(phi::integer<phi::int32_t>::value_type, phi::int32_t);
            CHECK_SAME_TYPE(phi::integer<phi::int64_t>::value_type, phi::int64_t);

            CHECK_SAME_TYPE(phi::integer<phi::uint8_t>::value_type, phi::uint8_t);
            CHECK_SAME_TYPE(phi::integer<phi::uint16_t>::value_type, phi::uint16_t);
            CHECK_SAME_TYPE(phi::integer<phi::uint32_t>::value_type, phi::uint32_t);
            CHECK_SAME_TYPE(phi::integer<phi::uint64_t>::value_type, phi::uint64_t);

            // limits_type
            CHECK_SAME_TYPE(phi::integer<phi::int8_t>::limits_type,
                            std::numeric_limits<phi::int8_t>);
            CHECK_SAME_TYPE(phi::integer<phi::int16_t>::limits_type,
                            std::numeric_limits<phi::int16_t>);
            CHECK_SAME_TYPE(phi::integer<phi::int32_t>::limits_type,
                            std::numeric_limits<phi::int32_t>);
            CHECK_SAME_TYPE(phi::integer<phi::int64_t>::limits_type,
                            std::numeric_limits<phi::int64_t>);

            CHECK_SAME_TYPE(phi::integer<phi::uint8_t>::limits_type,
                            std::numeric_limits<phi::uint8_t>);
            CHECK_SAME_TYPE(phi::integer<phi::uint16_t>::limits_type,
                            std::numeric_limits<phi::uint16_t>);
            CHECK_SAME_TYPE(phi::integer<phi::uint32_t>::limits_type,
                            std::numeric_limits<phi::uint32_t>);
            CHECK_SAME_TYPE(phi::integer<phi::uint64_t>::limits_type,
                            std::numeric_limits<phi::uint64_t>);
        }

        SECTION("constructor")
        {
            PHI_CONSTEXPR int_t val_a(0);
            STATIC_REQUIRE(static_cast<phi::int32_t>(val_a) == 0);
            PHI_CONSTEXPR int_t val_b(32);
            STATIC_REQUIRE(static_cast<phi::int32_t>(val_b) == 32);
            PHI_CONSTEXPR int_t val_c(-25);
            STATIC_REQUIRE(static_cast<phi::int32_t>(val_c) == -25);
        }

        SECTION("assignment")
        {
            int_t val_a{0};
            val_a = 32;
            CHECK(static_cast<phi::int32_t>(val_a) == 32);
            val_a = -25;
            CHECK(static_cast<phi::int32_t>(val_a) == -25);

            int_t val_b{3};
            val_a = val_b;
            CHECK(static_cast<phi::int32_t>(val_a) == 3);
        }

        SECTION("unary")
        {
            PHI_CONSTEXPR int_t val_a(13);
            STATIC_REQUIRE(static_cast<phi::int32_t>(+val_a) == static_cast<phi::int32_t>(val_a));
            EXT_STATIC_REQUIRE(static_cast<phi::int32_t>(-val_a) ==
                               -static_cast<phi::int32_t>(val_a));
        }

        SECTION("increment")
        {
            int_t val_a(0);
            CHECK(static_cast<phi::int32_t>(++val_a) == 1);
            CHECK(static_cast<phi::int32_t>(val_a++) == 1);
            CHECK(static_cast<phi::int32_t>(val_a) == 2);
        }

        SECTION("decrement")
        {
            int_t val_a(0);
            CHECK(static_cast<phi::int32_t>(--val_a) == -1);
            CHECK(static_cast<phi::int32_t>(val_a--) == -1);
            CHECK(static_cast<phi::int32_t>(val_a) == -2);
        }

        SECTION("addition")
        {
            int_t        wrapper(0);
            phi::int32_t normal(0);
            CHECK(static_cast<phi::int32_t>(wrapper) == normal);

            wrapper += 5;
            normal += 5;
            CHECK(static_cast<phi::int32_t>(wrapper) == normal);

            wrapper += phi::int16_t(5);
            normal += phi::int16_t(5);
            CHECK(static_cast<phi::int32_t>(wrapper) == normal);

            wrapper = wrapper + (-23);
            normal  = normal + (-23);
            CHECK(static_cast<phi::int32_t>(wrapper) == normal);

            wrapper = 22 + wrapper;
            normal  = 22 + normal;
            CHECK(static_cast<phi::int32_t>(wrapper) == normal);

            wrapper = int_t(-4) + wrapper;
            normal  = (-4) + normal;
            CHECK(static_cast<phi::int32_t>(wrapper) == normal);
        }

        SECTION("subtraction")
        {
            int_t        wrapper(0);
            phi::int32_t normal(0);
            CHECK(static_cast<phi::int32_t>(wrapper) == normal);

            wrapper -= 5;
            normal -= 5;
            CHECK(static_cast<phi::int32_t>(wrapper) == normal);

            wrapper -= phi::int16_t(5);
            normal -= phi::int16_t(5);
            CHECK(static_cast<phi::int32_t>(wrapper) == normal);

            wrapper = wrapper - (-23);
            normal  = normal - (-23);
            CHECK(static_cast<phi::int32_t>(wrapper) == normal);

            wrapper = 22 - wrapper;
            normal  = 22 - normal;
            CHECK(static_cast<phi::int32_t>(wrapper) == normal);

            wrapper = int_t(-4) - wrapper;
            normal  = (-4) - normal;
            CHECK(static_cast<phi::int32_t>(wrapper) == normal);
        }

        SECTION("multiplication")
        {
            int_t        wrapper(1);
            phi::int32_t normal(1);
            CHECK(static_cast<phi::int32_t>(wrapper) == normal);

            wrapper *= 5;
            normal *= 5;
            CHECK(static_cast<phi::int32_t>(wrapper) == normal);

            wrapper *= phi::int16_t(5);
            normal *= phi::int16_t(5);
            CHECK(static_cast<phi::int32_t>(wrapper) == normal);

            wrapper = wrapper * (-23);
            normal  = normal * (-23);
            CHECK(static_cast<phi::int32_t>(wrapper) == normal);

            wrapper = 22 * wrapper;
            normal  = 22 * normal;
            CHECK(static_cast<phi::int32_t>(wrapper) == normal);

            wrapper = int_t(-4) * wrapper;
            normal  = (-4) * normal;
            CHECK(static_cast<phi::int32_t>(wrapper) == normal);
        }

        SECTION("division")
        {
            int_t        wrapper(23 * 25);
            phi::int32_t normal(23 * 25);
            CHECK(static_cast<phi::int32_t>(wrapper) == normal);

            wrapper /= 5;
            normal /= 5;
            CHECK(static_cast<phi::int32_t>(wrapper) == normal);

            wrapper /= phi::int16_t(5);
            normal /= phi::int16_t(5);
            CHECK(static_cast<phi::int32_t>(wrapper) == normal);

            wrapper = wrapper / (-23);
            normal  = normal / (-23);
            CHECK(static_cast<phi::int32_t>(wrapper) == normal);

            wrapper = 22 / wrapper;
            normal  = 22 / normal;
            CHECK(static_cast<phi::int32_t>(wrapper) == normal);

            wrapper = int_t(-4) / wrapper;
            normal  = (-4) / normal;
            CHECK(static_cast<phi::int32_t>(wrapper) == normal);
        }

        SECTION("modulo")
        {
            int_t        wrapper(24 * 6);
            phi::int32_t normal(24 * 6);
            CHECK(static_cast<phi::int32_t>(wrapper) == normal);

            wrapper %= 5;
            normal %= 5;
            CHECK(static_cast<phi::int32_t>(wrapper) == normal);

            wrapper %= phi::int16_t(5);
            normal %= phi::int16_t(5);
            CHECK(static_cast<phi::int32_t>(wrapper) == normal);

            wrapper = wrapper % (-23);
            normal  = normal % (-23);
            CHECK(static_cast<phi::int32_t>(wrapper) == normal);

            wrapper = 22 % wrapper;
            normal  = 22 % normal;
            CHECK(static_cast<phi::int32_t>(wrapper) == normal);

            wrapper = int_t(-4) % wrapper;
            normal  = (-4) % normal;
            CHECK(static_cast<phi::int32_t>(wrapper) == normal);
        }

        SECTION("comparison")
        {
            // ==
            STATIC_REQUIRE(bool(int_t(4) == int_t(4)));
            STATIC_REQUIRE(!(int_t(5) == int_t(4)));

            STATIC_REQUIRE(bool(4 == int_t(4)));
            STATIC_REQUIRE(!(5 == int_t(4)));

            STATIC_REQUIRE(bool(int_t(4) == 4));
            STATIC_REQUIRE(!(int_t(5) == 4));

            // !=
            STATIC_REQUIRE(bool(int_t(5) != int_t(4)));
            STATIC_REQUIRE(!(int_t(4) != int_t(4)));

            STATIC_REQUIRE(bool(5 != int_t(4)));
            STATIC_REQUIRE(!(4 != int_t(4)));

            STATIC_REQUIRE(bool(int_t(5) != 4));
            STATIC_REQUIRE(!(int_t(4) != 4));

            // <
            STATIC_REQUIRE(bool(int_t(4) < int_t(5)));
            STATIC_REQUIRE(!(int_t(5) < int_t(4)));
            STATIC_REQUIRE(!(int_t(4) < int_t(4)));

            STATIC_REQUIRE(bool(4 < int_t(5)));
            STATIC_REQUIRE(!(5 < int_t(4)));
            STATIC_REQUIRE(!(4 < int_t(4)));

            STATIC_REQUIRE(bool(int_t(4) < 5));
            STATIC_REQUIRE(!(int_t(5) < 4));
            STATIC_REQUIRE(!(int_t(4) < 4));

            // <=
            STATIC_REQUIRE(bool(int_t(4) <= int_t(5)));
            STATIC_REQUIRE(!(int_t(5) <= int_t(4)));
            STATIC_REQUIRE(bool(int_t(4) <= int_t(4)));

            STATIC_REQUIRE(bool(4 <= int_t(5)));
            STATIC_REQUIRE(!(5 <= int_t(4)));
            STATIC_REQUIRE(bool(4 <= int_t(4)));

            STATIC_REQUIRE(bool(int_t(4) <= 5));
            STATIC_REQUIRE(!(int_t(5) <= 4));
            STATIC_REQUIRE(bool(int_t(4) <= 4));

            // >
            STATIC_REQUIRE(bool(int_t(5) > int_t(4)));
            STATIC_REQUIRE(!(int_t(4) > int_t(5)));
            STATIC_REQUIRE(!(int_t(5) > int_t(5)));

            STATIC_REQUIRE(bool(5 > int_t(4)));
            STATIC_REQUIRE(!(4 > int_t(5)));
            STATIC_REQUIRE(!(5 > int_t(5)));

            STATIC_REQUIRE(bool(int_t(5) > 4));
            STATIC_REQUIRE(!(int_t(4) > 5));
            STATIC_REQUIRE(!(int_t(5) > 5));

            // >=
            STATIC_REQUIRE(bool(int_t(5) >= int_t(4)));
            STATIC_REQUIRE(!(int_t(4) >= int_t(5)));
            STATIC_REQUIRE(bool(int_t(5) >= int_t(5)));

            STATIC_REQUIRE(bool(5 >= int_t(4)));
            STATIC_REQUIRE(!(4 >= int_t(5)));
            STATIC_REQUIRE(bool(5 >= int_t(5)));

            STATIC_REQUIRE(bool(int_t(5) >= 4));
            STATIC_REQUIRE(!(int_t(4) >= 5));
            STATIC_REQUIRE(bool(int_t(5) >= 5));
        }

        SECTION("min")
        {
            STATIC_REQUIRE(phi::integer<phi::int8_t>::min() ==
                           std::numeric_limits<phi::int8_t>::min());
            STATIC_REQUIRE(phi::integer<phi::int16_t>::min() ==
                           std::numeric_limits<phi::int16_t>::min());
            STATIC_REQUIRE(phi::integer<phi::int32_t>::min() ==
                           std::numeric_limits<phi::int32_t>::min());
            STATIC_REQUIRE(phi::integer<phi::int64_t>::min() ==
                           std::numeric_limits<phi::int64_t>::min());

            STATIC_REQUIRE(phi::integer<phi::uint8_t>::min() ==
                           std::numeric_limits<phi::uint8_t>::min());
            STATIC_REQUIRE(phi::integer<phi::uint16_t>::min() ==
                           std::numeric_limits<phi::uint16_t>::min());
            STATIC_REQUIRE(phi::integer<phi::uint32_t>::min() ==
                           std::numeric_limits<phi::uint32_t>::min());
            STATIC_REQUIRE(phi::integer<phi::uint64_t>::min() ==
                           std::numeric_limits<phi::uint64_t>::min());
        }

        SECTION("max")
        {
            STATIC_REQUIRE(phi::integer<phi::int8_t>::max() ==
                           std::numeric_limits<phi::int8_t>::max());
            STATIC_REQUIRE(phi::integer<phi::int16_t>::max() ==
                           std::numeric_limits<phi::int16_t>::max());
            STATIC_REQUIRE(phi::integer<phi::int32_t>::max() ==
                           std::numeric_limits<phi::int32_t>::max());
            STATIC_REQUIRE(phi::integer<phi::int64_t>::max() ==
                           std::numeric_limits<phi::int64_t>::max());

            STATIC_REQUIRE(phi::integer<phi::uint8_t>::max() ==
                           std::numeric_limits<phi::uint8_t>::max());
            STATIC_REQUIRE(phi::integer<phi::uint16_t>::max() ==
                           std::numeric_limits<phi::uint16_t>::max());
            STATIC_REQUIRE(phi::integer<phi::uint32_t>::max() ==
                           std::numeric_limits<phi::uint32_t>::max());
            STATIC_REQUIRE(phi::integer<phi::uint64_t>::max() ==
                           std::numeric_limits<phi::uint64_t>::max());
        }

        SECTION("swap")
        {
            int_t val_a{3};
            int_t val_b{5};

            val_a.swap(val_b);

            CHECK(val_a.unsafe() == 5);
            CHECK(val_b.unsafe() == 3);

            val_b.swap(val_a);

            CHECK(val_a.unsafe() == 3);
            CHECK(val_b.unsafe() == 5);

            phi::swap(val_a, val_b);

            CHECK(val_a.unsafe() == 5);
            CHECK(val_b.unsafe() == 3);

            phi::swap(val_b, val_a);

            CHECK(val_a.unsafe() == 3);
            CHECK(val_b.unsafe() == 5);
        }

        SECTION("i/o")
        {
            std::ostringstream out_stream;
            std::istringstream in_stream("10");

            int_t integer{0};
            out_stream << integer;
            CHECK(out_stream.str() == "0");

            in_stream >> integer;
            CHECK(static_cast<phi::int32_t>(integer) == 10);
        }

        SECTION("signed_to_unsigned")
        {
            // From int8_t
            STATIC_REQUIRE_FALSE(phi::is_convertible<phi::integer<phi::int8_t>,
                                                     phi::integer<phi::uint8_t>>::value);
            STATIC_REQUIRE_FALSE(phi::is_convertible<phi::integer<phi::int8_t>,
                                                     phi::integer<phi::uint16_t>>::value);
            STATIC_REQUIRE_FALSE(phi::is_convertible<phi::integer<phi::int8_t>,
                                                     phi::integer<phi::uint32_t>>::value);
            STATIC_REQUIRE_FALSE(phi::is_convertible<phi::integer<phi::int8_t>,
                                                     phi::integer<phi::uint64_t>>::value);

            // From int16_t
            STATIC_REQUIRE_FALSE(phi::is_convertible<phi::integer<phi::int16_t>,
                                                     phi::integer<phi::uint8_t>>::value);
            STATIC_REQUIRE_FALSE(phi::is_convertible<phi::integer<phi::int16_t>,
                                                     phi::integer<phi::uint16_t>>::value);
            STATIC_REQUIRE_FALSE(phi::is_convertible<phi::integer<phi::int16_t>,
                                                     phi::integer<phi::uint32_t>>::value);
            STATIC_REQUIRE_FALSE(phi::is_convertible<phi::integer<phi::int16_t>,
                                                     phi::integer<phi::uint64_t>>::value);

            // From int32_t
            STATIC_REQUIRE_FALSE(phi::is_convertible<phi::integer<phi::int32_t>,
                                                     phi::integer<phi::uint8_t>>::value);
            STATIC_REQUIRE_FALSE(phi::is_convertible<phi::integer<phi::int32_t>,
                                                     phi::integer<phi::uint16_t>>::value);
            STATIC_REQUIRE_FALSE(phi::is_convertible<phi::integer<phi::int32_t>,
                                                     phi::integer<phi::uint32_t>>::value);
            STATIC_REQUIRE_FALSE(phi::is_convertible<phi::integer<phi::int32_t>,
                                                     phi::integer<phi::uint64_t>>::value);

            // From int64_t
            STATIC_REQUIRE_FALSE(phi::is_convertible<phi::integer<phi::int64_t>,
                                                     phi::integer<phi::uint8_t>>::value);
            STATIC_REQUIRE_FALSE(phi::is_convertible<phi::integer<phi::int64_t>,
                                                     phi::integer<phi::uint16_t>>::value);
            STATIC_REQUIRE_FALSE(phi::is_convertible<phi::integer<phi::int64_t>,
                                                     phi::integer<phi::uint32_t>>::value);
            STATIC_REQUIRE_FALSE(phi::is_convertible<phi::integer<phi::int64_t>,
                                                     phi::integer<phi::uint64_t>>::value);
        }

        SECTION("unsigned_to_signed")
        {
            // From uint8_t
            STATIC_REQUIRE_FALSE(phi::is_convertible<phi::integer<phi::uint8_t>,
                                                     phi::integer<phi::int8_t>>::value);
            STATIC_REQUIRE(phi::is_convertible<phi::integer<phi::uint8_t>,
                                               phi::integer<phi::int16_t>>::value);
            STATIC_REQUIRE(phi::is_convertible<phi::integer<phi::uint8_t>,
                                               phi::integer<phi::int32_t>>::value);
            STATIC_REQUIRE(phi::is_convertible<phi::integer<phi::uint8_t>,
                                               phi::integer<phi::int64_t>>::value);

            // From uint16_t
            STATIC_REQUIRE_FALSE(phi::is_convertible<phi::integer<phi::uint16_t>,
                                                     phi::integer<phi::int8_t>>::value);
            STATIC_REQUIRE_FALSE(phi::is_convertible<phi::integer<phi::uint16_t>,
                                                     phi::integer<phi::int16_t>>::value);
            STATIC_REQUIRE(phi::is_convertible<phi::integer<phi::uint16_t>,
                                               phi::integer<phi::int32_t>>::value);
            STATIC_REQUIRE(phi::is_convertible<phi::integer<phi::uint16_t>,
                                               phi::integer<phi::int64_t>>::value);

            // From uint32_t
            STATIC_REQUIRE_FALSE(phi::is_convertible<phi::integer<phi::uint32_t>,
                                                     phi::integer<phi::int8_t>>::value);
            STATIC_REQUIRE_FALSE(phi::is_convertible<phi::integer<phi::uint32_t>,
                                                     phi::integer<phi::int16_t>>::value);
            STATIC_REQUIRE_FALSE(phi::is_convertible<phi::integer<phi::uint32_t>,
                                                     phi::integer<phi::int32_t>>::value);
            STATIC_REQUIRE(phi::is_convertible<phi::integer<phi::uint32_t>,
                                               phi::integer<phi::int64_t>>::value);

            // From uint64_t
            STATIC_REQUIRE_FALSE(phi::is_convertible<phi::integer<phi::uint64_t>,
                                                     phi::integer<phi::int8_t>>::value);
            STATIC_REQUIRE_FALSE(phi::is_convertible<phi::integer<phi::uint64_t>,
                                                     phi::integer<phi::int16_t>>::value);
            STATIC_REQUIRE_FALSE(phi::is_convertible<phi::integer<phi::uint64_t>,
                                                     phi::integer<phi::int32_t>>::value);
            STATIC_REQUIRE_FALSE(phi::is_convertible<phi::integer<phi::uint64_t>,
                                                     phi::integer<phi::int64_t>>::value);
        }

        SECTION("signed_to_signed")
        {
            // From int8_t
            STATIC_REQUIRE(phi::is_convertible<phi::integer<phi::int8_t>,
                                               phi::integer<phi::int8_t>>::value);
            STATIC_REQUIRE(phi::is_convertible<phi::integer<phi::int8_t>,
                                               phi::integer<phi::int16_t>>::value);
            STATIC_REQUIRE(phi::is_convertible<phi::integer<phi::int8_t>,
                                               phi::integer<phi::int32_t>>::value);
            STATIC_REQUIRE(phi::is_convertible<phi::integer<phi::int8_t>,
                                               phi::integer<phi::int64_t>>::value);

            // From int16_t
            STATIC_REQUIRE_FALSE(phi::is_convertible<phi::integer<phi::int16_t>,
                                                     phi::integer<phi::int8_t>>::value);
            STATIC_REQUIRE(phi::is_convertible<phi::integer<phi::int16_t>,
                                               phi::integer<phi::int16_t>>::value);
            STATIC_REQUIRE(phi::is_convertible<phi::integer<phi::int16_t>,
                                               phi::integer<phi::int32_t>>::value);
            STATIC_REQUIRE(phi::is_convertible<phi::integer<phi::int16_t>,
                                               phi::integer<phi::int64_t>>::value);

            // From int32_t
            STATIC_REQUIRE_FALSE(phi::is_convertible<phi::integer<phi::int32_t>,
                                                     phi::integer<phi::int8_t>>::value);
            STATIC_REQUIRE_FALSE(phi::is_convertible<phi::integer<phi::int32_t>,
                                                     phi::integer<phi::int16_t>>::value);
            STATIC_REQUIRE(phi::is_convertible<phi::integer<phi::int32_t>,
                                               phi::integer<phi::int32_t>>::value);
            STATIC_REQUIRE(phi::is_convertible<phi::integer<phi::int32_t>,
                                               phi::integer<phi::int64_t>>::value);

            // From int64_t
            STATIC_REQUIRE_FALSE(phi::is_convertible<phi::integer<phi::int64_t>,
                                                     phi::integer<phi::int8_t>>::value);
            STATIC_REQUIRE_FALSE(phi::is_convertible<phi::integer<phi::int64_t>,
                                                     phi::integer<phi::int16_t>>::value);
            STATIC_REQUIRE_FALSE(phi::is_convertible<phi::integer<phi::int64_t>,
                                                     phi::integer<phi::int32_t>>::value);
            STATIC_REQUIRE(phi::is_convertible<phi::integer<phi::int64_t>,
                                               phi::integer<phi::int64_t>>::value);
        }

        SECTION("unsigned_to_unsigned")
        {
            // From uint8_t
            STATIC_REQUIRE(phi::is_convertible<phi::integer<phi::uint8_t>,
                                               phi::integer<phi::uint8_t>>::value);
            STATIC_REQUIRE(phi::is_convertible<phi::integer<phi::uint8_t>,
                                               phi::integer<phi::uint16_t>>::value);
            STATIC_REQUIRE(phi::is_convertible<phi::integer<phi::uint8_t>,
                                               phi::integer<phi::uint32_t>>::value);
            STATIC_REQUIRE(phi::is_convertible<phi::integer<phi::uint8_t>,
                                               phi::integer<phi::uint64_t>>::value);

            // From uint16_t
            STATIC_REQUIRE_FALSE(phi::is_convertible<phi::integer<phi::uint16_t>,
                                                     phi::integer<phi::uint8_t>>::value);
            STATIC_REQUIRE(phi::is_convertible<phi::integer<phi::uint16_t>,
                                               phi::integer<phi::uint16_t>>::value);
            STATIC_REQUIRE(phi::is_convertible<phi::integer<phi::uint16_t>,
                                               phi::integer<phi::uint32_t>>::value);
            STATIC_REQUIRE(phi::is_convertible<phi::integer<phi::uint16_t>,
                                               phi::integer<phi::uint64_t>>::value);

            // From uint32_t
            STATIC_REQUIRE_FALSE(phi::is_convertible<phi::integer<phi::uint32_t>,
                                                     phi::integer<phi::uint8_t>>::value);
            STATIC_REQUIRE_FALSE(phi::is_convertible<phi::integer<phi::uint32_t>,
                                                     phi::integer<phi::uint16_t>>::value);
            STATIC_REQUIRE(phi::is_convertible<phi::integer<phi::uint32_t>,
                                               phi::integer<phi::uint32_t>>::value);
            STATIC_REQUIRE(phi::is_convertible<phi::integer<phi::uint32_t>,
                                               phi::integer<phi::uint64_t>>::value);

            // From uint64_t
            STATIC_REQUIRE_FALSE(phi::is_convertible<phi::integer<phi::uint64_t>,
                                                     phi::integer<phi::uint8_t>>::value);
            STATIC_REQUIRE_FALSE(phi::is_convertible<phi::integer<phi::uint64_t>,
                                                     phi::integer<phi::uint16_t>>::value);
            STATIC_REQUIRE_FALSE(phi::is_convertible<phi::integer<phi::uint64_t>,
                                                     phi::integer<phi::uint32_t>>::value);
            STATIC_REQUIRE(phi::is_convertible<phi::integer<phi::uint64_t>,
                                               phi::integer<phi::uint64_t>>::value);
        }

        SECTION("std::hash")
        {
            const phi::size_t zero_hash = std::hash<phi::integer<int>>{}(0);
            const phi::size_t one_hash  = std::hash<phi::integer<int>>{}(1);

            CHECK(zero_hash != one_hash);
            CHECK(zero_hash == std::hash<int>{}(0));
            CHECK(one_hash == std::hash<int>{}(1));
        }
    }
}

PHI_CLANG_SUPPRESS_WARNING_POP()
PHI_GCC_SUPPRESS_WARNING_POP()

PHI_CONSTEXPR_AND_CONST static phi::detail::signed_integer_tag   stag{};
PHI_CONSTEXPR_AND_CONST static phi::detail::unsigned_integer_tag utag{};

PHI_CONSTEXPR_AND_CONST static int imax = std::numeric_limits<int>::max();
PHI_CONSTEXPR_AND_CONST static int imin = std::numeric_limits<int>::min();

PHI_CONSTEXPR_AND_CONST static unsigned umax = std::numeric_limits<unsigned>::max();

TEST_CASE("detail::will_addition_error")
{
    // Signed
    STATIC_REQUIRE_FALSE(phi::detail::will_addition_error(stag, 0, 0));
    STATIC_REQUIRE_FALSE(phi::detail::will_addition_error(stag, 1, 0));
    STATIC_REQUIRE_FALSE(phi::detail::will_addition_error(stag, 0, 1));
    STATIC_REQUIRE_FALSE(phi::detail::will_addition_error(stag, 1, 1));
    STATIC_REQUIRE_FALSE(phi::detail::will_addition_error(stag, imin, 0));
    STATIC_REQUIRE_FALSE(phi::detail::will_addition_error(stag, imin, 1));
    STATIC_REQUIRE_FALSE(phi::detail::will_addition_error(stag, imax, 0));
    STATIC_REQUIRE_FALSE(phi::detail::will_addition_error(stag, imax, -1));
    STATIC_REQUIRE_FALSE(phi::detail::will_addition_error(stag, 0, imin));
    STATIC_REQUIRE_FALSE(phi::detail::will_addition_error(stag, 1, imin));
    STATIC_REQUIRE_FALSE(phi::detail::will_addition_error(stag, 0, imax));
    STATIC_REQUIRE_FALSE(phi::detail::will_addition_error(stag, -1, imax));

    STATIC_REQUIRE(phi::detail::will_addition_error(stag, imin, -1));
    STATIC_REQUIRE(phi::detail::will_addition_error(stag, imax, 1));
    STATIC_REQUIRE(phi::detail::will_addition_error(stag, -1, imin));
    STATIC_REQUIRE(phi::detail::will_addition_error(stag, 1, imax));
    STATIC_REQUIRE(phi::detail::will_addition_error(stag, imax, imax));
    STATIC_REQUIRE(phi::detail::will_addition_error(stag, imin, imin));

    // Unsigned
    STATIC_REQUIRE_FALSE(phi::detail::will_addition_error(utag, 0u, 0u));
    STATIC_REQUIRE_FALSE(phi::detail::will_addition_error(utag, 1u, 0u));
    STATIC_REQUIRE_FALSE(phi::detail::will_addition_error(utag, 0u, 1u));
    STATIC_REQUIRE_FALSE(phi::detail::will_addition_error(utag, 1u, 1u));
    STATIC_REQUIRE_FALSE(phi::detail::will_addition_error(utag, umax, 0u));
    STATIC_REQUIRE_FALSE(phi::detail::will_addition_error(utag, 0u, umax));

    STATIC_REQUIRE(phi::detail::will_addition_error(utag, umax, 1u));
    STATIC_REQUIRE(phi::detail::will_addition_error(utag, 1u, umax));
    STATIC_REQUIRE(phi::detail::will_addition_error(utag, umax, umax));
}

TEST_CASE("detail::will_subtraction_error")
{
    // Signed
    STATIC_REQUIRE_FALSE(phi::detail::will_subtraction_error(stag, 0, 0));
    STATIC_REQUIRE_FALSE(phi::detail::will_subtraction_error(stag, 1, 0));
    STATIC_REQUIRE_FALSE(phi::detail::will_subtraction_error(stag, 0, 1));
    STATIC_REQUIRE_FALSE(phi::detail::will_subtraction_error(stag, 1, 1));
    STATIC_REQUIRE_FALSE(phi::detail::will_subtraction_error(stag, imin, 0));
    STATIC_REQUIRE_FALSE(phi::detail::will_subtraction_error(stag, imin, -11));
    STATIC_REQUIRE_FALSE(phi::detail::will_subtraction_error(stag, imax, 0));
    STATIC_REQUIRE_FALSE(phi::detail::will_subtraction_error(stag, imax, 1));
    STATIC_REQUIRE_FALSE(phi::detail::will_subtraction_error(stag, -1, imin));
    STATIC_REQUIRE_FALSE(phi::detail::will_subtraction_error(stag, 0, imax));
    STATIC_REQUIRE_FALSE(phi::detail::will_subtraction_error(stag, -1, imax));

    STATIC_REQUIRE(will_subtraction_error(stag, imin, 1));
    STATIC_REQUIRE(will_subtraction_error(stag, imin, imax));
    STATIC_REQUIRE(will_subtraction_error(stag, imax, -1));
    STATIC_REQUIRE(will_subtraction_error(stag, imax, imin));
    STATIC_REQUIRE(will_subtraction_error(stag, 0, imin));
    STATIC_REQUIRE(will_subtraction_error(stag, 1, imin));
    STATIC_REQUIRE(will_subtraction_error(stag, -2, imax));

    // Unsigned
    STATIC_REQUIRE_FALSE(phi::detail::will_subtraction_error(utag, 0u, 0u));
    STATIC_REQUIRE_FALSE(phi::detail::will_subtraction_error(utag, 1u, 0u));
    STATIC_REQUIRE_FALSE(phi::detail::will_subtraction_error(utag, 1u, 1u));
    STATIC_REQUIRE_FALSE(phi::detail::will_subtraction_error(utag, umax, 0u));
    STATIC_REQUIRE_FALSE(phi::detail::will_subtraction_error(utag, umax, 1u));
    STATIC_REQUIRE_FALSE(phi::detail::will_subtraction_error(utag, umax, umax));

    STATIC_REQUIRE(phi::detail::will_subtraction_error(utag, 0u, 1u));
    STATIC_REQUIRE(phi::detail::will_subtraction_error(utag, 1u, 2u));
    STATIC_REQUIRE(phi::detail::will_subtraction_error(utag, 0u, umax));
    STATIC_REQUIRE(phi::detail::will_subtraction_error(utag, 1u, umax));
}

TEST_CASE("detail::will_multiplication_error")
{
    // Signed
    STATIC_REQUIRE_FALSE(phi::detail::will_multiplication_error(stag, 0, 0));
    STATIC_REQUIRE_FALSE(phi::detail::will_multiplication_error(stag, 1, 0));
    STATIC_REQUIRE_FALSE(phi::detail::will_multiplication_error(stag, -1, 0));
    STATIC_REQUIRE_FALSE(phi::detail::will_multiplication_error(stag, imin, 0));
    STATIC_REQUIRE_FALSE(phi::detail::will_multiplication_error(stag, imax, 0));
    STATIC_REQUIRE_FALSE(phi::detail::will_multiplication_error(stag, 0, 1));
    STATIC_REQUIRE_FALSE(phi::detail::will_multiplication_error(stag, 1, 1));
    STATIC_REQUIRE_FALSE(phi::detail::will_multiplication_error(stag, -1, 1));
    STATIC_REQUIRE_FALSE(phi::detail::will_multiplication_error(stag, imin, 1));
    STATIC_REQUIRE_FALSE(phi::detail::will_multiplication_error(stag, imax, 1));
    STATIC_REQUIRE_FALSE(phi::detail::will_multiplication_error(stag, 0, -1));
    STATIC_REQUIRE_FALSE(phi::detail::will_multiplication_error(stag, 1, -1));
    STATIC_REQUIRE_FALSE(phi::detail::will_multiplication_error(stag, -1, -1));
    STATIC_REQUIRE_FALSE(phi::detail::will_multiplication_error(stag, imax, -1));
    STATIC_REQUIRE_FALSE(phi::detail::will_multiplication_error(stag, 0, imin));
    STATIC_REQUIRE_FALSE(phi::detail::will_multiplication_error(stag, 1, imin));
    STATIC_REQUIRE_FALSE(phi::detail::will_multiplication_error(stag, 1, imax));
    STATIC_REQUIRE_FALSE(phi::detail::will_multiplication_error(stag, -1, imax));
    STATIC_REQUIRE_FALSE(phi::detail::will_multiplication_error(stag, 0, imax));

    STATIC_REQUIRE(phi::detail::will_multiplication_error(stag, imin, -1));
    STATIC_REQUIRE(phi::detail::will_multiplication_error(stag, -1, imin));
    STATIC_REQUIRE(phi::detail::will_multiplication_error(stag, imin, imin));
    STATIC_REQUIRE(phi::detail::will_multiplication_error(stag, imax, imin));
    STATIC_REQUIRE(phi::detail::will_multiplication_error(stag, imin, imax));
    STATIC_REQUIRE(phi::detail::will_multiplication_error(stag, imax, imax));
    STATIC_REQUIRE(phi::detail::will_multiplication_error(stag, imax, 2));
    STATIC_REQUIRE(phi::detail::will_multiplication_error(stag, imax, 3));
    STATIC_REQUIRE(phi::detail::will_multiplication_error(stag, 2, imax));
    STATIC_REQUIRE(phi::detail::will_multiplication_error(stag, 3, imax));

    // Unsigned
    STATIC_REQUIRE_FALSE(phi::detail::will_multiplication_error(utag, 0u, 0u));
    STATIC_REQUIRE_FALSE(phi::detail::will_multiplication_error(utag, 1u, 0u));
    STATIC_REQUIRE_FALSE(phi::detail::will_multiplication_error(utag, umax, 0u));
    STATIC_REQUIRE_FALSE(phi::detail::will_multiplication_error(utag, 0u, 1u));
    STATIC_REQUIRE_FALSE(phi::detail::will_multiplication_error(utag, 1u, 1u));
    STATIC_REQUIRE_FALSE(phi::detail::will_multiplication_error(utag, umax, 1u));
    STATIC_REQUIRE_FALSE(phi::detail::will_multiplication_error(utag, 0u, umax));
    STATIC_REQUIRE_FALSE(phi::detail::will_multiplication_error(utag, 1u, umax));

    STATIC_REQUIRE(phi::detail::will_multiplication_error(utag, umax, umax));
    STATIC_REQUIRE(phi::detail::will_multiplication_error(utag, umax, 2u));
    STATIC_REQUIRE(phi::detail::will_multiplication_error(utag, umax, 3u));
    STATIC_REQUIRE(phi::detail::will_multiplication_error(utag, 2u, umax));
    STATIC_REQUIRE(phi::detail::will_multiplication_error(utag, 3u, umax));
}

TEST_CASE("detail::will_division_error")
{
    // Signed
    STATIC_REQUIRE_FALSE(phi::detail::will_division_error(stag, 0, 1));
    STATIC_REQUIRE_FALSE(phi::detail::will_division_error(stag, 1, 1));
    STATIC_REQUIRE_FALSE(phi::detail::will_division_error(stag, -1, 1));
    STATIC_REQUIRE_FALSE(phi::detail::will_division_error(stag, imin, 1));
    STATIC_REQUIRE_FALSE(phi::detail::will_division_error(stag, imax, 1));
    STATIC_REQUIRE_FALSE(phi::detail::will_division_error(stag, 0, -1));
    STATIC_REQUIRE_FALSE(phi::detail::will_division_error(stag, 1, -1));
    STATIC_REQUIRE_FALSE(phi::detail::will_division_error(stag, -1, -1));
    STATIC_REQUIRE_FALSE(phi::detail::will_division_error(stag, imax, -1));
    STATIC_REQUIRE_FALSE(phi::detail::will_division_error(stag, 0, imin));
    STATIC_REQUIRE_FALSE(phi::detail::will_division_error(stag, 1, imin));
    STATIC_REQUIRE_FALSE(phi::detail::will_division_error(stag, -1, imin));
    STATIC_REQUIRE_FALSE(phi::detail::will_division_error(stag, imin, imin));
    STATIC_REQUIRE_FALSE(phi::detail::will_division_error(stag, imax, imin));
    STATIC_REQUIRE_FALSE(phi::detail::will_division_error(stag, 0, imax));
    STATIC_REQUIRE_FALSE(phi::detail::will_division_error(stag, 1, imax));
    STATIC_REQUIRE_FALSE(phi::detail::will_division_error(stag, -1, imax));
    STATIC_REQUIRE_FALSE(phi::detail::will_division_error(stag, imin, imax));
    STATIC_REQUIRE_FALSE(phi::detail::will_division_error(stag, imax, imax));

    STATIC_REQUIRE(phi::detail::will_division_error(stag, 0, 0));
    STATIC_REQUIRE(phi::detail::will_division_error(stag, 1, 0));
    STATIC_REQUIRE(phi::detail::will_division_error(stag, -1, 0));
    STATIC_REQUIRE(phi::detail::will_division_error(stag, imin, 0));
    STATIC_REQUIRE(phi::detail::will_division_error(stag, imax, 0));
    STATIC_REQUIRE(phi::detail::will_division_error(stag, imin, -1));

    // Unsigned
    STATIC_REQUIRE_FALSE(phi::detail::will_division_error(utag, 0u, 1u));
    STATIC_REQUIRE_FALSE(phi::detail::will_division_error(utag, 1u, 1u));
    STATIC_REQUIRE_FALSE(phi::detail::will_division_error(utag, umax, 1u));
    STATIC_REQUIRE_FALSE(phi::detail::will_division_error(utag, 0u, umax));
    STATIC_REQUIRE_FALSE(phi::detail::will_division_error(utag, 1u, umax));
    STATIC_REQUIRE_FALSE(phi::detail::will_division_error(utag, umax, umax));

    STATIC_REQUIRE(phi::detail::will_division_error(utag, 0u, 0u));
    STATIC_REQUIRE(phi::detail::will_division_error(utag, 1u, 0u));
    STATIC_REQUIRE(phi::detail::will_division_error(utag, umax, 0u));
}

TEST_CASE("detail::will_modulo_error")
{
    // Signed
    STATIC_REQUIRE_FALSE(phi::detail::will_modulo_error(0, 1));
    STATIC_REQUIRE_FALSE(phi::detail::will_modulo_error(1, 1));
    STATIC_REQUIRE_FALSE(phi::detail::will_modulo_error(0, -1));
    STATIC_REQUIRE_FALSE(phi::detail::will_modulo_error(0, -1));
    STATIC_REQUIRE_FALSE(phi::detail::will_modulo_error(imin, 1));
    STATIC_REQUIRE_FALSE(phi::detail::will_modulo_error(imin, -1));
    STATIC_REQUIRE_FALSE(phi::detail::will_modulo_error(imin, imax));
    STATIC_REQUIRE_FALSE(phi::detail::will_modulo_error(imin, imin));
    STATIC_REQUIRE_FALSE(phi::detail::will_modulo_error(imax, 1));
    STATIC_REQUIRE_FALSE(phi::detail::will_modulo_error(imax, -1));
    STATIC_REQUIRE_FALSE(phi::detail::will_modulo_error(imax, imax));
    STATIC_REQUIRE_FALSE(phi::detail::will_modulo_error(imax, imin));

    STATIC_REQUIRE(phi::detail::will_modulo_error(0, 0));
    STATIC_REQUIRE(phi::detail::will_modulo_error(1, 0));
    STATIC_REQUIRE(phi::detail::will_modulo_error(-1, 0));
    STATIC_REQUIRE(phi::detail::will_modulo_error(imin, 0));
    STATIC_REQUIRE(phi::detail::will_modulo_error(imax, 0));

    // Unsigned
    STATIC_REQUIRE_FALSE(phi::detail::will_modulo_error(0u, 1u));
    STATIC_REQUIRE_FALSE(phi::detail::will_modulo_error(1u, 1u));
    STATIC_REQUIRE_FALSE(phi::detail::will_modulo_error(umax, 1u));
    STATIC_REQUIRE_FALSE(phi::detail::will_modulo_error(umax, umax));

    STATIC_REQUIRE(phi::detail::will_modulo_error(0u, 0u));
    STATIC_REQUIRE(phi::detail::will_modulo_error(1u, 0u));
    STATIC_REQUIRE(phi::detail::will_modulo_error(umax, 0u));
}
