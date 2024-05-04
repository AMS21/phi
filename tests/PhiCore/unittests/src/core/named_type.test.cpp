// This file is heavily inspired by Jonathan Boccaras NamedType library https://github.com/joboccara/NamedType
// licensed under the MIT license https://github.com/joboccara/NamedType/blob/master/LICENSE
// Original file at https://github.com/joboccara/NamedType/blob/master/test/tests.cpp
/* MIT License

Copyright (c) 2017 Jonathan Boccara

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

#include <phi/test/test_macros.hpp>

#include "constexpr_helper.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include <phi/compiler_support/compiler.hpp>
#include <phi/compiler_support/constexpr.hpp>
#include <phi/compiler_support/intrinsics/address_of.hpp>
#include <phi/compiler_support/intrinsics/is_union.hpp>
#include <phi/compiler_support/warning.hpp>
#include <phi/core/named_type.hpp>
#include <phi/type_traits/is_default_constructible.hpp>
#include <phi/type_traits/is_nothrow_constructible.hpp>
#include <phi/type_traits/is_trivially_constructible.hpp>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

// gcc-6 throws this warning here
PHI_GCC_SUPPRESS_WARNING("-Wunsafe-loop-optimizations")

#if PHI_SUPPORTS_ADDRESS_OF() || PHI_SUPPORTS_IS_UNION()
#    define STATIC_REQUIRE_ADR(...) EXT_STATIC_REQUIRE(__VA_ARGS__)
#else
#    define STATIC_REQUIRE_ADR(...) REQUIRE(__VA_ARGS__)
#endif

// Usage examples

PHI_CLANG_SUPPRESS_WARNING_PUSH()
#if PHI_COMPILER_IS_ATLEAST(CLANG, 13, 0, 0)
PHI_CLANG_SUPPRESS_WARNING("-Wreserved-identifier")
#endif

using Meter =
        phi::named_type<unsigned long long, struct MeterParameter, phi::addable, phi::comparable>;
PHI_CONSTEXPR Meter operator""_meter(unsigned long long value)
{
    return Meter(value);
}

PHI_CLANG_SUPPRESS_WARNING_POP()

using Width  = phi::named_type<Meter, struct WidthParameter>;
using Height = phi::named_type<Meter, struct HeightParameter>;

class rectangle
{
public:
    rectangle(Width width, Height height)
        : m_Width(width.unsafe())
        , m_Height(height.unsafe())
    {}

    PHI_NODISCARD Meter getWidth() const
    {
        return m_Width;
    }

    PHI_NODISCARD Meter getHeight() const
    {
        return m_Height;
    }

private:
    Meter m_Width;
    Meter m_Height;
};

TEST_CASE("Basic usage")
{
    rectangle rect(Width(10_meter), Height(12_meter));
    REQUIRE(rect.getWidth().unsafe() == 10);
    REQUIRE(rect.getHeight().unsafe() == 12);
}

using NameRef = phi::named_type<std::string&, struct NameRefParameter>;

void changeValue(NameRef name)
{
    name.unsafe() = "value2";
}

TEST_CASE("Passing a strong reference")
{
    std::string value = "value1";
    changeValue(NameRef(value));
    REQUIRE(value == "value2");
}

TEST_CASE("Construction of NamedType::ref from the underlying type")
{
    using StrongInt = phi::named_type<int, struct StrongIntTag>;
    auto add_one    = [](StrongInt::reference strong_int) { ++(strong_int.unsafe()); };

    int integer = 42;
    add_one(StrongInt::reference(integer));
    REQUIRE(integer == 43);
}

TEST_CASE("Implicit conversion of NamedType to NamedType::ref")
{
    using StrongInt = phi::named_type<int, struct StrongIntTag>;
    auto add_one    = [](StrongInt::reference strong_int) { ++(strong_int.unsafe()); };

    StrongInt integer(42);
    add_one(integer);
    REQUIRE(integer.unsafe() == 43);

    StrongInt integer2(42);
    add_one(StrongInt::reference(integer2));
    REQUIRE(integer2.unsafe() == 43);
}

struct PotentiallyThrowing
{
    // NOLINTNEXTLINE(modernize-use-equals-default)
    PotentiallyThrowing()
    {}
};

struct NonDefaultConstructible
{
    NonDefaultConstructible(int /*unused*/)
    {}
};

struct UserProvided
{
    UserProvided();
};
UserProvided::UserProvided() = default;

TEST_CASE("Default construction")
{
    using StrongInt = phi::named_type<int, struct StrongIntTag>;
    StrongInt strong_int;
    strong_int.unsafe() = 42;
    REQUIRE(strong_int.unsafe() == 42);

#if PHI_HAS_WORKING_IS_NOTHROW_CONSTRUCTIBLE()
    STATIC_REQUIRE(phi::is_nothrow_constructible<StrongInt>::value);
#endif

// Default constructible
#if PHI_HAS_WORKING_IS_DEFAULT_CONSTRUCTIBLE()
    STATIC_REQUIRE(phi::is_default_constructible<StrongInt>::value);
    using StrongNonDefaultConstructible =
            phi::named_type<NonDefaultConstructible, struct StrongNonDefaultConstructibleTag>;
    STATIC_REQUIRE_FALSE(phi::is_default_constructible<StrongNonDefaultConstructible>::value);
#endif

    // Trivially constructible
#if PHI_HAS_WORKING_IS_TRIVIALLY_CONSTRUCTIBLE()
    STATIC_REQUIRE(phi::is_trivially_constructible<StrongInt>::value);
    using StrongUserProvided = phi::named_type<UserProvided, struct StrongUserProvidedTag>;
    STATIC_REQUIRE_FALSE(phi::is_trivially_constructible<StrongUserProvided>::value);
#endif

    // Nothrow constructible
#if PHI_HAS_WORKING_IS_NOTHROW_CONSTRUCTIBLE()
    STATIC_REQUIRE(phi::is_nothrow_constructible<StrongInt>::value);
    using StrongPotentiallyThrowing =
            phi::named_type<PotentiallyThrowing, struct StrongPotentiallyThrowingTag>;
    STATIC_REQUIRE_FALSE(phi::is_nothrow_constructible<StrongPotentiallyThrowing>::value);
#endif
}

template <typename FunctionT>
using Comparator = phi::named_type<FunctionT, struct ComparatorParameter>;

template <typename FunctionT>
std::string performAction(Comparator<FunctionT> comp)
{
    return comp.unsafe()();
}

PHI_GCC_SUPPRESS_WARNING_PUSH()
PHI_GCC_SUPPRESS_WARNING("-Wunused-result")

TEST_CASE("Strong generic type")
{
    REQUIRE(performAction(phi::make_named<Comparator>([]() { return std::string("compare"); })) ==
            "compare");
}

PHI_GCC_SUPPRESS_WARNING_POP()

TEST_CASE("Addable")
{
    using AddableType = phi::named_type<int, struct AddableTag, phi::addable>;
    AddableType lhs(12);
    AddableType rhs(10);
    REQUIRE((lhs + rhs).unsafe() == 22);
    REQUIRE((+lhs).unsafe() == 12);
}

TEST_CASE("Addable constexpr")
{
    using AddableType = phi::named_type<int, struct AddableTag, phi::addable>;
    PHI_CONSTEXPR AddableType lhs(12);
    PHI_CONSTEXPR AddableType rhs(10);
    EXT_STATIC_REQUIRE((lhs + rhs).unsafe() == 22);
    EXT_STATIC_REQUIRE((+lhs).unsafe() == 12);
}

TEST_CASE("BinaryAddable")
{
    using BinaryAddableType = phi::named_type<int, struct BinaryAddableTag, phi::binary_addable>;
    BinaryAddableType lhs(12);
    BinaryAddableType rhs(10);
    REQUIRE((lhs + rhs).unsafe() == 22);
}

TEST_CASE("BinaryAddable constexpr")
{
    using BinaryAddableType = phi::named_type<int, struct BinaryAddableTag, phi::binary_addable>;

    PHI_CONSTEXPR BinaryAddableType lhs(12);
    PHI_CONSTEXPR BinaryAddableType rhs(10);
    EXT_STATIC_REQUIRE((lhs + rhs).unsafe() == 22);

    PHI_CONSTEXPR BinaryAddableType strong_int(10);
    EXT_STATIC_REQUIRE(BinaryAddableType{12}.operator+=(strong_int).unsafe() == 22);
}

TEST_CASE("UnaryAddable")
{
    using UnaryAddableType = phi::named_type<int, struct UnaryAddableTag, phi::unary_addable>;
    UnaryAddableType strong_int(12);
    REQUIRE((+strong_int).unsafe() == 12);
}

TEST_CASE("UnaryAddable constexpr")
{
    using UnaryAddableType = phi::named_type<int, struct UnaryAddableTag, phi::unary_addable>;
    PHI_CONSTEXPR UnaryAddableType strong_int(12);
    EXT_STATIC_REQUIRE((+strong_int).unsafe() == 12);
}

TEST_CASE("Subtractable")
{
    using SubtractableType = phi::named_type<int, struct SubtractableTag, phi::subtractable>;
    SubtractableType lhs(12);
    SubtractableType rhs(10);
    REQUIRE((lhs - rhs).unsafe() == 2);
    REQUIRE((-lhs).unsafe() == -12);
}

TEST_CASE("Subtractable constexpr")
{
    using SubtractableType = phi::named_type<int, struct SubtractableTag, phi::subtractable>;
    PHI_CONSTEXPR SubtractableType lhs(12);
    PHI_CONSTEXPR SubtractableType rhs(10);
    EXT_STATIC_REQUIRE((lhs - rhs).unsafe() == 2);
    EXT_STATIC_REQUIRE((-lhs).unsafe() == -12);
}

TEST_CASE("BinarySubtractable")
{
    using BinarySubtractableType =
            phi::named_type<int, struct BinarySubtractableTag, phi::binary_subtractable>;
    BinarySubtractableType lhs(12);
    BinarySubtractableType rhs(10);
    REQUIRE((lhs - rhs).unsafe() == 2);
}

TEST_CASE("BinarySubtractable constexpr")
{
    using BinarySubtractableType =
            phi::named_type<int, struct BinarySubtractableTag, phi::binary_subtractable>;

    PHI_CONSTEXPR BinarySubtractableType lhs(12);
    PHI_CONSTEXPR BinarySubtractableType rhs(10);
    EXT_STATIC_REQUIRE((lhs - rhs).unsafe() == 2);

    PHI_CONSTEXPR BinarySubtractableType strong_int(10);
    EXT_STATIC_REQUIRE(BinarySubtractableType{12}.operator-=(strong_int).unsafe() == 2);
}

TEST_CASE("UnarySubtractable")
{
    using UnarySubtractableType =
            phi::named_type<int, struct UnarySubtractableTag, phi::unary_subtractable>;
    UnarySubtractableType strong_int(12);
    REQUIRE((-strong_int).unsafe() == -12);
}

TEST_CASE("UnarySubtractable constexpr")
{
    using UnarySubtractableType =
            phi::named_type<int, struct UnarySubtractableTag, phi::unary_subtractable>;
    PHI_CONSTEXPR UnarySubtractableType strong_int(12);
    EXT_STATIC_REQUIRE((-strong_int).unsafe() == -12);
}

TEST_CASE("Multiplicable")
{
    using MultiplicableType = phi::named_type<int, struct MultiplicableTag, phi::multiplicable>;
    MultiplicableType lhs(12);
    MultiplicableType rhs(10);
    REQUIRE((lhs * rhs).unsafe() == 120);
    lhs *= rhs;
    REQUIRE(lhs.unsafe() == 120);
}

TEST_CASE("Multiplicable constexpr")
{
    using MultiplicableType = phi::named_type<int, struct MultiplicableTag, phi::multiplicable>;

    PHI_CONSTEXPR MultiplicableType lhs(12);
    PHI_CONSTEXPR MultiplicableType rhs(10);
    EXT_STATIC_REQUIRE((lhs * rhs).unsafe() == 120);

    PHI_CONSTEXPR MultiplicableType strong_int(10);
    EXT_STATIC_REQUIRE(MultiplicableType{12}.operator*=(strong_int).unsafe() == 120);
}

TEST_CASE("Divisible")
{
    using DivisibleType = phi::named_type<int, struct DivisibleTag, phi::divisible>;
    DivisibleType lhs(120);
    DivisibleType rhs(10);
    REQUIRE((lhs / rhs).unsafe() == 12);
    lhs /= rhs;
    REQUIRE(lhs.unsafe() == 12);
}

TEST_CASE("Divisible constexpr")
{
    using DivisibleType = phi::named_type<int, struct DivisibleTag, phi::divisible>;

    PHI_CONSTEXPR DivisibleType lhs(120);
    PHI_CONSTEXPR DivisibleType rhs(10);
    EXT_STATIC_REQUIRE((lhs / rhs).unsafe() == 12);

    PHI_CONSTEXPR DivisibleType strong_int(10);
    EXT_STATIC_REQUIRE(DivisibleType{120}.operator/=(strong_int).unsafe() == 12);
}

TEST_CASE("Modulable")
{
    using ModulableType = phi::named_type<int, struct ModulableTag, phi::modulable>;
    ModulableType lhs(5);
    ModulableType rhs(2);
    CHECK((lhs % rhs).unsafe() == 1);
    lhs %= rhs;
    CHECK(lhs.unsafe() == 1);
}

TEST_CASE("Modulable constexpr")
{
    using ModulableType = phi::named_type<int, struct ModulableTag, phi::modulable>;

    PHI_CONSTEXPR ModulableType lhs(5);
    PHI_CONSTEXPR ModulableType rhs(2);
    EXT_STATIC_REQUIRE((lhs % rhs).unsafe() == 1);

    PHI_CONSTEXPR ModulableType strong_int(2);
    EXT_STATIC_REQUIRE(ModulableType{5}.operator%=(strong_int).unsafe() == 1);
}

TEST_CASE("BitWiseInvertible")
{
    using BitWiseInvertibleType =
            phi::named_type<int, struct BitWiseInvertibleTag, phi::bit_wise_invertible>;
    BitWiseInvertibleType strong_int(13);
    CHECK((~strong_int).unsafe() == (~13));
}

TEST_CASE("BitWiseInvertible constexpr")
{
    using BitWiseInvertibleType =
            phi::named_type<int, struct BitWiseInvertibleTag, phi::bit_wise_invertible>;
    PHI_CONSTEXPR BitWiseInvertibleType strong_int(13);
    EXT_STATIC_REQUIRE((~strong_int).unsafe() == (~13));
}

TEST_CASE("BitWiseAndable")
{
    using BitWiseAndableType =
            phi::named_type<int, struct BitWiseAndableTag, phi::bit_wise_andable>;
    BitWiseAndableType lhs(2);
    BitWiseAndableType rhs(64);
    CHECK((lhs & rhs).unsafe() == (2 & 64));
    lhs &= rhs;
    CHECK(lhs.unsafe() == (2 & 64));
}

TEST_CASE("BitWiseAndable constexpr")
{
    using BitWiseAndableType =
            phi::named_type<int, struct BitWiseAndableTag, phi::bit_wise_andable>;

    PHI_CONSTEXPR BitWiseAndableType lhs(2);
    PHI_CONSTEXPR BitWiseAndableType rhs(64);
    EXT_STATIC_REQUIRE((lhs & rhs).unsafe() == (2 & 64));

    PHI_CONSTEXPR BitWiseAndableType strong_int(64);
    EXT_STATIC_REQUIRE(BitWiseAndableType{2}.operator&=(strong_int).unsafe() == (2 & 64));
}

TEST_CASE("BitWiseOrable")
{
    using BitWiseOrableType = phi::named_type<int, struct BitWiseOrableTag, phi::bit_wise_orable>;
    BitWiseOrableType lhs(2);
    BitWiseOrableType rhs(64);
    CHECK((lhs | rhs).unsafe() == (2 | 64));
    lhs |= rhs;
    CHECK(lhs.unsafe() == (2 | 64));
}

TEST_CASE("BitWiseOrable constexpr")
{
    using BitWiseOrableType = phi::named_type<int, struct BitWiseOrableTag, phi::bit_wise_orable>;

    PHI_CONSTEXPR BitWiseOrableType lhs(2);
    PHI_CONSTEXPR BitWiseOrableType rhs(64);
    EXT_STATIC_REQUIRE((lhs | rhs).unsafe() == (2 | 64));

    PHI_CONSTEXPR BitWiseOrableType strong_int(64);
    EXT_STATIC_REQUIRE(BitWiseOrableType{2}.operator|=(strong_int).unsafe() == (2 | 64));
}

TEST_CASE("BitWiseXorable")
{
    using BitWiseXorableType =
            phi::named_type<int, struct BitWiseXorableTag, phi::bit_wise_xorable>;
    BitWiseXorableType lhs(2);
    BitWiseXorableType rhs(64);
    CHECK((lhs ^ rhs).unsafe() == (2 ^ 64));
    lhs ^= rhs;
    CHECK(lhs.unsafe() == (2 ^ 64));
}

TEST_CASE("BitWiseXorable constexpr")
{
    using BitWiseXorableType =
            phi::named_type<int, struct BitWiseXorableTag, phi::bit_wise_xorable>;
    PHI_CONSTEXPR BitWiseXorableType lhs(2);
    PHI_CONSTEXPR BitWiseXorableType rhs(64);
    EXT_STATIC_REQUIRE((lhs ^ rhs).unsafe() == 66);

    PHI_CONSTEXPR BitWiseXorableType strong_int(64);
    EXT_STATIC_REQUIRE(BitWiseXorableType{2}.operator^=(strong_int).unsafe() == 66);
}

TEST_CASE("BitWiseLeftShiftable")
{
    using BitWiseLeftShiftableType =
            phi::named_type<int, struct BitWiseLeftShiftableTag, phi::bit_wise_left_shiftable>;
    BitWiseLeftShiftableType lhs(2);
    BitWiseLeftShiftableType rhs(3);
    CHECK((lhs << rhs).unsafe() == (2 << 3));
    lhs <<= rhs;
    CHECK(lhs.unsafe() == (2 << 3));
}

TEST_CASE("BitWiseLeftShiftable constexpr")
{
    using BitWiseLeftShiftableType =
            phi::named_type<int, struct BitWiseLeftShiftableTag, phi::bit_wise_left_shiftable>;
    PHI_CONSTEXPR BitWiseLeftShiftableType lhs(2);
    PHI_CONSTEXPR BitWiseLeftShiftableType rhs(3);
    EXT_STATIC_REQUIRE((lhs << rhs).unsafe() == (2 << 3));

    PHI_CONSTEXPR BitWiseLeftShiftableType strong_int(3);
    EXT_STATIC_REQUIRE(BitWiseLeftShiftableType{2}.operator<<=(strong_int).unsafe() == (2 << 3));
}

TEST_CASE("BitWiseRightShiftable")
{
    using BitWiseRightShiftableType =
            phi::named_type<int, struct BitWiseRightShiftableTag, phi::bit_wise_right_shiftable>;
    BitWiseRightShiftableType lhs(2);
    BitWiseRightShiftableType rhs(3);
    CHECK((lhs >> rhs).unsafe() == (2 >> 3));
    lhs >>= rhs;
    CHECK(lhs.unsafe() == (2 >> 3));
}

TEST_CASE("BitWiseRightShiftable constexpr")
{
    using BitWiseRightShiftableType =
            phi::named_type<int, struct BitWiseRightShiftableTag, phi::bit_wise_right_shiftable>;
    PHI_CONSTEXPR BitWiseRightShiftableType lhs(2);
    PHI_CONSTEXPR BitWiseRightShiftableType rhs(3);
    EXT_STATIC_REQUIRE((lhs >> rhs).unsafe() == (2 >> 3));

    PHI_CONSTEXPR BitWiseRightShiftableType strong_int(3);
    EXT_STATIC_REQUIRE(BitWiseRightShiftableType{2}.operator>>=(strong_int).unsafe() == (2 >> 3));
}

TEST_CASE("Comparable")
{
    EXT_STATIC_REQUIRE(10_meter == 10_meter);
    EXT_STATIC_REQUIRE_FALSE(10_meter == 11_meter);
    EXT_STATIC_REQUIRE_FALSE(11_meter == 10_meter);
    EXT_STATIC_REQUIRE(10_meter != 11_meter);
    EXT_STATIC_REQUIRE(11_meter != 10_meter);
    EXT_STATIC_REQUIRE_FALSE(10_meter != 10_meter);
    EXT_STATIC_REQUIRE(10_meter < 11_meter);
    EXT_STATIC_REQUIRE_FALSE(10_meter < 10_meter);
    EXT_STATIC_REQUIRE(10_meter <= 10_meter);
    EXT_STATIC_REQUIRE(10_meter <= 11_meter);
    EXT_STATIC_REQUIRE_FALSE(10_meter <= 9_meter);
    EXT_STATIC_REQUIRE(11_meter > 10_meter);
    EXT_STATIC_REQUIRE_FALSE(10_meter > 11_meter);
    EXT_STATIC_REQUIRE(11_meter >= 10_meter);
    EXT_STATIC_REQUIRE(10_meter >= 10_meter);
    EXT_STATIC_REQUIRE_FALSE(9_meter >= 10_meter);
}

TEST_CASE("ConvertibleWithOperator")
{
    struct B
    {
        B(int val)
            : x(val)
        {}
        int x;
    };

    struct A
    {
        A(int val)
            : x(val)
        {}
        operator B() const
        {
            return {x};
        }
        int x;
    };

    using StrongA = phi::named_type<A, struct StrongATag, phi::implicitly_convertible_to<B>::templ>;
    StrongA strong_a(A(42));
    B       just_b = strong_a;
    REQUIRE(just_b.x == 42);
}

TEST_CASE("ConvertibleWithOperator constexpr")
{
    struct B
    {
        PHI_CONSTEXPR B(int val)
            : x(val)
        {}
        int x;
    };

    struct A
    {
        PHI_CONSTEXPR A(int val)
            : x(val)
        {}
        PHI_CONSTEXPR operator B() const
        {
            return {x};
        }
        int x;
    };

    using StrongA = phi::named_type<A, struct StrongATag, phi::implicitly_convertible_to<B>::templ>;
    PHI_EXTENDED_CONSTEXPR StrongA strong_a(A(42));
    PHI_EXTENDED_CONSTEXPR B       just_b = strong_a;
    EXT_STATIC_REQUIRE(just_b.x == 42);
}

TEST_CASE("ConvertibleWithConstructor")
{
    struct A
    {
        A(int val)
            : x(val)
        {}
        int x;
    };

    struct B
    {
        B(A val)
            : x(val.x)
        {}
        int x;
    };

    using StrongA = phi::named_type<A, struct StrongATag, phi::implicitly_convertible_to<B>::templ>;
    StrongA strong_a(A(42));
    B       just_b = strong_a;
    REQUIRE(just_b.x == 42);
}

TEST_CASE("ConvertibleWithConstructor constexpr")
{
    struct A
    {
        PHI_CONSTEXPR A(int val)
            : x(val)
        {}
        int x;
    };

    struct B
    {
        PHI_CONSTEXPR B(A val)
            : x(val.x)
        {}
        int x;
    };

    using StrongA = phi::named_type<A, struct StrongATag, phi::implicitly_convertible_to<B>::templ>;
    PHI_EXTENDED_CONSTEXPR StrongA strong_a(A(42));
    PHI_EXTENDED_CONSTEXPR B       just_b = strong_a;
    EXT_STATIC_REQUIRE(just_b.x == 42);
}

TEST_CASE("ConvertibleToItself")
{
    using MyInt = phi::named_type<int, struct MyIntTag, phi::implicitly_convertible_to<int>::templ>;
    MyInt my_int(42);
    int   integer = my_int;
    REQUIRE(integer == 42);
}

TEST_CASE("ConvertibleToItself constexpr")
{
    using MyInt = phi::named_type<int, struct MyIntTag, phi::implicitly_convertible_to<int>::templ>;
    PHI_EXTENDED_CONSTEXPR MyInt my_int(42);
    PHI_EXTENDED_CONSTEXPR int   integer = my_int;
    EXT_STATIC_REQUIRE(integer == 42);
}

TEST_CASE("Hash")
{
    using SerialNumber =
            phi::named_type<std::string, struct SerialNumberTag, phi::comparable, phi::hashable>;

    std::unordered_map<SerialNumber, int> hash_map = {{SerialNumber{"AA11"}, 10},
                                                      {SerialNumber{"BB22"}, 20}};
    SerialNumber                          cc33{"CC33"};
    hash_map[cc33] = 30;
    REQUIRE(hash_map[SerialNumber{"AA11"}] == 10);
    REQUIRE(hash_map[SerialNumber{"BB22"}] == 20);
    REQUIRE(hash_map[cc33] == 30);
}

struct testFunctionCallable_A
{
    testFunctionCallable_A(int val)
        : x(val)
    {}
    // ensures that passing the argument to a function doesn't make a copy
    testFunctionCallable_A(testFunctionCallable_A const&) = delete;
    testFunctionCallable_A(testFunctionCallable_A&&)      = default;
    testFunctionCallable_A& operator+=(testFunctionCallable_A const& other)
    {
        x += other.x;
        return *this;
    }
    int x;
};

testFunctionCallable_A operator+(testFunctionCallable_A const& lhs,
                                 testFunctionCallable_A const& rhs)
{
    return {lhs.x + rhs.x};
}

bool operator==(testFunctionCallable_A const& lhs, testFunctionCallable_A const& rhs)
{
    return lhs.x == rhs.x;
}

TEST_CASE("Function callable")
{
    using A                = testFunctionCallable_A;
    auto function_taking_a = [](A const& a_value) { return a_value.x; };

    using StrongA = phi::named_type<A, struct StrongATag, phi::function_callable>;
    StrongA       strong_a(A(42));
    const StrongA const_strong_a(A(42));
    REQUIRE(function_taking_a(strong_a) == 42);
    REQUIRE(function_taking_a(const_strong_a) == 42);
    REQUIRE(strong_a + strong_a == 84);
}

struct testFunctionCallable_B
{
    PHI_CONSTEXPR testFunctionCallable_B(int val)
        : x(val)
    {}
    // ensures that passing the argument to a function doesn't make a copy
    testFunctionCallable_B(testFunctionCallable_B const&) = delete;
    testFunctionCallable_B(testFunctionCallable_B&&)      = default;
    PHI_EXTENDED_CONSTEXPR testFunctionCallable_B& operator+=(testFunctionCallable_B const& other)
    {
        x += other.x;
        return *this;
    }
    int x;
};

PHI_CONSTEXPR testFunctionCallable_B operator+(const testFunctionCallable_B& lhs,
                                               const testFunctionCallable_B& rhs)
{
    return {lhs.x + rhs.x};
}

PHI_CONSTEXPR bool operator==(testFunctionCallable_B const& lhs, testFunctionCallable_B const& rhs)
{
    return lhs.x == rhs.x;
}

PHI_CONSTEXPR int functionTakingB(testFunctionCallable_B const& value)
{
    return value.x;
}

TEST_CASE("Function callable constexpr")
{
    using B = testFunctionCallable_B;

    using StrongB = phi::named_type<B, struct StrongATag, phi::function_callable>;
    PHI_CONSTEXPR StrongB const_strong_b(B(42));
    EXT_STATIC_REQUIRE(functionTakingB(StrongB(B(42))) == 42);
    EXT_STATIC_REQUIRE(functionTakingB(const_strong_b) == 42);
    EXT_STATIC_REQUIRE(StrongB(B(42)) + StrongB(B(42)) == 84);
    EXT_STATIC_REQUIRE(const_strong_b + const_strong_b == 84);
}

TEST_CASE("Method callable")
{
    struct A
    {
        A(int val)
            : m_X(val)
        {}
        A(A const&) = delete; // ensures that invoking a method doesn't make a copy
        A(A&&)      = default;

        // NOLINTNEXTLINE(readability-make-member-function-const)
        int method()
        {
            return m_X;
        }

        PHI_NODISCARD int constMethod() const
        {
            return m_X;
        }

    private:
        int m_X;
    };

    using StrongA = phi::named_type<A, struct StrongATag, phi::method_callable>;
    StrongA       strong_a(A(42));
    const StrongA const_strong_a(A((42)));
    REQUIRE(strong_a->method() == 42);
    REQUIRE(const_strong_a->constMethod() == 42);
}

TEST_CASE("Method callable constexpr")
{
    struct A
    {
        PHI_CONSTEXPR A(int val)
            : m_X(val)
        {}
        A(A const&) = delete; // ensures that invoking a method doesn't make a copy
        A(A&&)      = default;

        // NOLINTNEXTLINE(readability-make-member-function-const)
        PHI_CONSTEXPR int method()
        {
            return m_X;
        }

        PHI_NODISCARD constexpr int constMethod() const
        {
            return m_X;
        }

    private:
        int m_X;
    };

    using StrongA = phi::named_type<A, struct StrongATag, phi::method_callable>;
    PHI_EXTENDED_CONSTEXPR const StrongA const_strong_a(A((42)));
    STATIC_REQUIRE_ADR(StrongA(A(42))->method() == 42);
    STATIC_REQUIRE_ADR(const_strong_a->constMethod() == 42);
}

TEST_CASE("Callable")
{
    struct A
    {
        A(int val)
            : m_X(val)
        {}
        A(A const&) = delete; // ensures that invoking a method or function doesn't make a copy
        A(A&&)      = default;

        // NOLINTNEXTLINE(readability-make-member-function-const)
        int method()
        {
            return m_X;
        }

        PHI_NODISCARD int constMethod() const
        {
            return m_X;
        }

    private:
        int m_X;
    };

    auto function_taking_a = [](const A& val) { return val.constMethod(); };

    using StrongA = phi::named_type<A, struct StrongATag, phi::callable>;
    StrongA       strong_a(A(42));
    const StrongA const_strong_a(A(42));
    REQUIRE(function_taking_a(strong_a) == 42);
    REQUIRE(strong_a->method() == 42);
    REQUIRE(const_strong_a->constMethod() == 42);
}

TEST_CASE("Named arguments")
{
    using FirstName = phi::named_type<std::string, struct FirstNameTag>;
    using LastName  = phi::named_type<std::string, struct LastNameTag>;
    static const FirstName::argument first_name;
    static const LastName::argument  last_name;
    auto get_full_name = [](FirstName const& first_name_arg, LastName const& last_name_arg) {
        return first_name_arg.unsafe() + last_name_arg.unsafe();
    };

    auto full_name = get_full_name(first_name = "James", last_name = "Bond");
    REQUIRE(full_name == "JamesBond");
}

TEST_CASE("Named arguments with bracket constructor")
{
    using Numbers = phi::named_type<std::vector<int>, struct NumbersTag>;
    static const Numbers::argument numbers;
    auto get_numbers = [](Numbers const& numbers_arg) { return numbers_arg.unsafe(); };

    auto vec = get_numbers(numbers = {1, 2, 3});
    REQUIRE(vec == std::vector<int>{1, 2, 3});
}

TEST_CASE("Empty base class optimization")
{
    REQUIRE(sizeof(Meter) == sizeof(double));
}

using StrongIntT = phi::named_type<int, struct IntTag>;

TEST_CASE("constexpr")
{
    using strong_bool = phi::named_type<bool, struct BoolTag>;

    EXT_STATIC_REQUIRE(strong_bool{true}.unsafe());
}

struct throw_on_construction
{
    [[noreturn]] throw_on_construction()
    {
        throw 42;
    }

    [[noreturn]] throw_on_construction(int /*unused*/)
    {
        throw "exception";
    }
};

using C = phi::named_type<throw_on_construction, struct throwTag>;

TEST_CASE("noexcept")
{
#if PHI_HAS_WORKING_IS_NOTHROW_CONSTRUCTIBLE()
    CHECK(noexcept(StrongIntT{}));
#endif
    CHECK(!noexcept(C{}));

#if PHI_HAS_WORKING_IS_NOTHROW_CONSTRUCTIBLE()
    CHECK(noexcept(StrongIntT(3)));
#endif
    CHECK(!noexcept(C{5}));
}

TEST_CASE("Arithmetic")
{
    using strong_arithmetic = phi::named_type<int, struct ArithmeticTag, phi::arithmetic>;
    strong_arithmetic lhs{1};
    strong_arithmetic rhs{2};

    CHECK((lhs + rhs).unsafe() == 3);

    lhs += rhs;
    CHECK(lhs.unsafe() == 3);

    CHECK((lhs - rhs).unsafe() == 1);

    lhs -= rhs;
    CHECK(lhs.unsafe() == 1);

    lhs.unsafe() = 5;
    CHECK((lhs * rhs).unsafe() == 10);

    lhs *= rhs;
    CHECK(lhs.unsafe() == 10);

    CHECK((lhs / rhs).unsafe() == 5);

    lhs /= rhs;
    CHECK(lhs.unsafe() == 5);
}

TEST_CASE("Printable")
{
    using StrongInt = phi::named_type<int, struct StrongIntTag, phi::printable>;

    std::ostringstream oss;
    oss << StrongInt(42);
    CHECK(oss.str() == "42");
}

TEST_CASE("Dereferenceable")
{
    using StrongInt = phi::named_type<int, struct StrongIntTag, phi::dereferenceable>;

    {
        StrongInt strong_int{1};
        int&      value = *strong_int;
        CHECK(value == 1);
    }

    {
        const StrongInt strong_int{1};
        const int&      value = *strong_int;
        CHECK(value == 1);
    }

    {
        StrongInt strong_int{1};
        int&      value = *strong_int;
        value           = 2;
        CHECK(strong_int.unsafe() == 2);
    }

    {
        auto function_returning_strong_int = []() { return StrongInt{28}; };
        auto function_taking_int           = [](int value) { return value; };

        int value = function_taking_int(*function_returning_strong_int());
        CHECK(value == 28);
    }
}

TEST_CASE("Dereferenceable constexpr")
{
    using StrongInt = phi::named_type<int, struct StrongIntTag, phi::dereferenceable>;

    PHI_EXTENDED_CONSTEXPR StrongInt strong_int{28};
    EXT_STATIC_REQUIRE(*strong_int == 28);
    EXT_STATIC_REQUIRE(*StrongInt{28} == 28);
}

TEST_CASE("PreIncrementable")
{
    using StrongInt = phi::named_type<int, struct StrongIntTag, phi::pre_incrementable>;
    StrongInt lhs{1};
    StrongInt rhs = ++lhs;
    CHECK(lhs.unsafe() == 2);
    CHECK(rhs.unsafe() == 2);
}

TEST_CASE("PreIncrementable constexpr")
{
    using StrongInt = phi::named_type<int, struct StrongIntTag, phi::pre_incrementable>;
    EXT_STATIC_REQUIRE((++StrongInt{1}).unsafe() == 2);
}

TEST_CASE("PostIncrementable")
{
    using StrongInt = phi::named_type<int, struct StrongIntTag, phi::post_incrementable>;
    StrongInt lhs{1};
    StrongInt rhs = lhs++;
    CHECK(lhs.unsafe() == 2);
    CHECK(rhs.unsafe() == 1);
}

TEST_CASE("PostIncrementable constexpr")
{
    using StrongInt = phi::named_type<int, struct StrongIntTag, phi::post_incrementable>;
    EXT_STATIC_REQUIRE((StrongInt { 1 } ++).unsafe() == 1);
}

TEST_CASE("PreDecrementable")
{
    using StrongInt = phi::named_type<int, struct StrongIntTag, phi::pre_decrementable>;
    StrongInt lhs{1};
    StrongInt rhs = --lhs;
    CHECK(lhs.unsafe() == 0);
    CHECK(rhs.unsafe() == 0);
}

TEST_CASE("PreDecrementable constexpr")
{
    using StrongInt = phi::named_type<int, struct StrongIntTag, phi::pre_decrementable>;
    EXT_STATIC_REQUIRE((--StrongInt{1}).unsafe() == 0);
}

TEST_CASE("PostDecrementable")
{
    using StrongInt = phi::named_type<int, struct StrongIntTag, phi::post_decrementable>;
    StrongInt lhs{1};
    StrongInt rhs = lhs--;
    CHECK(lhs.unsafe() == 0);
    CHECK(rhs.unsafe() == 1);
}

TEST_CASE("PostDecrementable constexpr")
{
    using StrongInt = phi::named_type<int, struct StrongIntTag, phi::post_decrementable>;
    EXT_STATIC_REQUIRE((StrongInt { 1 } --).unsafe() == 1);
}
