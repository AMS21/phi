// This file is heavily inspired by Sy Brands optional library https://github.com/TartanLlama/optional
// licensed under CC0 https://github.com/TartanLlama/optional/blob/master/COPYING
// Original files at
// * https://github.com/TartanLlama/optional/blob/master/tests/assignment.cpp
// * https://github.com/TartanLlama/optional/blob/master/tests/bases.cpp
// * https://github.com/TartanLlama/optional/blob/master/tests/constexpr.cpp
// * https://github.com/TartanLlama/optional/blob/master/tests/constructors.cpp
// * https://github.com/TartanLlama/optional/blob/master/tests/emplace.cpp
// * https://github.com/TartanLlama/optional/blob/master/tests/extensions.cpp
// * https://github.com/TartanLlama/optional/blob/master/tests/in_place.cpp
// * https://github.com/TartanLlama/optional/blob/master/tests/issues.cpp
// * https://github.com/TartanLlama/optional/blob/master/tests/make_optional.cpp
// * https://github.com/TartanLlama/optional/blob/master/tests/noexcept.cpp
// * https://github.com/TartanLlama/optional/blob/master/tests/nullopt.cpp
// * https://github.com/TartanLlama/optional/blob/master/tests/observers.cpp
// * https://github.com/TartanLlama/optional/blob/master/tests/relops.cpp
// * https://github.com/TartanLlama/optional/blob/master/tests/swap.cpp

#include <phi/compiler_support/warning.hpp>

PHI_CLANG_SUPPRESS_WARNING_PUSH()
PHI_CLANG_SUPPRESS_WARNING("-Wimplicit-int-conversion")
#if PHI_COMPILER_IS_ATLEAST(CLANG, 10, 0, 0)
PHI_CLANG_SUPPRESS_WARNING("-Wimplicit-int-float-conversion")
#endif
PHI_CLANG_SUPPRESS_WARNING("-Wunused-member-function")
PHI_CLANG_SUPPRESS_WARNING("-Wunneeded-member-function")
#if PHI_COMPILER_IS_ATLEAST(CLANG, 10, 0, 0)
PHI_CLANG_SUPPRESS_WARNING("-Wdeprecated-copy")
#else
PHI_CLANG_SUPPRESS_WARNING("-Wdeprecated")
#endif
PHI_CLANG_SUPPRESS_WARNING("-Wfloat-equal")
PHI_CLANG_SUPPRESS_WARNING("-Wself-assign-overloaded")

PHI_GCC_SUPPRESS_WARNING_PUSH()
PHI_GCC_SUPPRESS_WARNING("-Wconversion")
#if PHI_COMPILER_IS_ATLEAST(GCC, 9, 0, 0)
PHI_GCC_SUPPRESS_WARNING("-Wdeprecated-copy")
#endif
PHI_GCC_SUPPRESS_WARNING("-Wnoexcept")
PHI_GCC_SUPPRESS_WARNING("-Wuseless-cast")
PHI_GCC_SUPPRESS_WARNING("-Wfloat-equal")

// NOTE: Not sure why gcc with asan enabled thinks that some of them are uninitialized
// TODO: Investigate further and maybe open a bug report
PHI_GCC_SUPPRESS_WARNING("-Wmaybe-uninitialized")

PHI_MSVC_SUPPRESS_WARNING_PUSH()
PHI_MSVC_SUPPRESS_WARNING(4242) // conversion from 'TypeT' to 'TypeT', possible loss of data
PHI_MSVC_SUPPRESS_WARNING(
        4244) // 'initializing': conversion from 'TypeT' to 'TypeT', possible loss of data

#include <phi/test/test_macros.hpp>

#include "constexpr_helper.hpp"
#include <phi/compiler_support/constexpr.hpp>
#include <phi/compiler_support/noexcept.hpp>
#include <phi/compiler_support/unused.hpp>
#include <phi/core/declval.hpp>
#include <phi/core/forward.hpp>
#include <phi/core/move.hpp>
#include <phi/core/optional.hpp>
#include <phi/type_traits/is_default_constructible.hpp>
#include <phi/type_traits/is_destructible.hpp>
#include <phi/type_traits/is_same.hpp>
#include <phi/type_traits/is_trivially_copy_assignable.hpp>
#include <phi/type_traits/is_trivially_copy_constructible.hpp>
#include <phi/type_traits/is_trivially_destructible.hpp>
#include <phi/type_traits/is_trivially_move_assignable.hpp>
#include <phi/type_traits/is_trivially_move_constructible.hpp>
#include <string>
#include <tuple>
#include <vector>

#if PHI_HAS_WORKING_OPTIONAL()

TEST_CASE("optional Assigment value")
{
    phi::optional<int> o1 = 42;
    phi::optional<int> o2 = 12;
    phi::optional<int> o3;

    o1 = o1;
    REQUIRE(*o1 == 42);

    o1 = o2;
    REQUIRE(*o1 == 12);

    o1 = o3;
    REQUIRE(!o1);

    o1 = 42;
    REQUIRE(*o1 == 42);

    o1 = phi::nullopt;
    REQUIRE(!o1);

    o1 = phi::move(o2);
    REQUIRE(*o1 == 12);

    phi::optional<short> o4 = 42;

    o1 = o4;
    REQUIRE(*o1 == 42);

    o1 = phi::move(o4);
    REQUIRE(*o1 == 42);
}

TEST_CASE("optional assignment reference")
{
    auto i = 42;
    auto j = 12;

    phi::optional<int&> o1 = i;
    phi::optional<int&> o2 = j;
    phi::optional<int&> o3;

    o1 = o1;
    REQUIRE(*o1 == 42);
    REQUIRE(&*o1 == &i);

    o1 = o2;
    REQUIRE(*o1 == 12);

    o1 = o3;
    REQUIRE(!o1);

    auto k = 42;
    o1     = k;
    REQUIRE(*o1 == 42);
    REQUIRE(*o1 == i);
    REQUIRE(*o1 == k);
    REQUIRE(&*o1 != &i);
    REQUIRE(&*o1 == &k);

    k = 12;
    REQUIRE(*o1 == 12);

    o1 = phi::nullopt;
    REQUIRE(!o1);

    o1 = phi::move(o2);
    REQUIRE(*o1 == 12);
}

TEST_CASE("optional triviality")
{
    REQUIRE(phi::is_trivially_copy_constructible<phi::optional<int>>::value);
    REQUIRE(phi::is_trivially_copy_assignable<phi::optional<int>>::value);
    REQUIRE(phi::is_trivially_move_constructible<phi::optional<int>>::value);
    REQUIRE(phi::is_trivially_move_assignable<phi::optional<int>>::value);
    REQUIRE(phi::is_trivially_destructible<phi::optional<int>>::value);

    {
        struct T
        {
            T(const T&)            = default;
            T(T&&)                 = default;
            T& operator=(const T&) = default;
            T& operator=(T&&)      = default;
            ~T()                   = default;
        };

        REQUIRE(phi::is_trivially_copy_constructible<phi::optional<T>>::value);
        REQUIRE(phi::is_trivially_copy_assignable<phi::optional<T>>::value);
        REQUIRE(phi::is_trivially_move_constructible<phi::optional<T>>::value);
        REQUIRE(phi::is_trivially_move_assignable<phi::optional<T>>::value);
        REQUIRE(phi::is_trivially_destructible<phi::optional<T>>::value);
    }

    {
        struct T
        {
            T(const T&)
            {}
            T(T&&)
            {}
            T& operator=(const T&)
            {
                return *this;
            }
            T& operator=(T&&)
            {
                return *this;
            }
            ~T()
            {}
        };
        REQUIRE_FALSE(phi::is_trivially_copy_constructible<phi::optional<T>>::value);
        REQUIRE_FALSE(phi::is_trivially_copy_assignable<phi::optional<T>>::value);
        REQUIRE_FALSE(phi::is_trivially_move_constructible<phi::optional<T>>::value);
        REQUIRE_FALSE(phi::is_trivially_move_assignable<phi::optional<T>>::value);
        REQUIRE_FALSE(phi::is_trivially_destructible<phi::optional<T>>::value);
    }
}

TEST_CASE("optional Deletion")
{
    REQUIRE(phi::is_copy_constructible<phi::optional<int>>::value);
    REQUIRE(phi::is_copy_assignable<phi::optional<int>>::value);
    REQUIRE(phi::is_move_constructible<phi::optional<int>>::value);
    REQUIRE(phi::is_move_assignable<phi::optional<int>>::value);
    REQUIRE(phi::is_destructible<phi::optional<int>>::value);

    {
        struct T
        {
            T(const T&)            = default;
            T(T&&)                 = default;
            T& operator=(const T&) = default;
            T& operator=(T&&)      = default;
            ~T()                   = default;
        };
        REQUIRE(phi::is_copy_constructible<phi::optional<T>>::value);
        REQUIRE(phi::is_copy_assignable<phi::optional<T>>::value);
        REQUIRE(phi::is_move_constructible<phi::optional<T>>::value);
        REQUIRE(phi::is_move_assignable<phi::optional<T>>::value);
        REQUIRE(phi::is_destructible<phi::optional<T>>::value);
    }

    {
        struct T
        {
            T(const T&)            = delete;
            T(T&&)                 = delete;
            T& operator=(const T&) = delete;
            T& operator=(T&&)      = delete;
        };
        REQUIRE_FALSE(phi::is_copy_constructible<phi::optional<T>>::value);
        REQUIRE_FALSE(phi::is_copy_assignable<phi::optional<T>>::value);
        REQUIRE_FALSE(phi::is_move_constructible<phi::optional<T>>::value);
        REQUIRE_FALSE(phi::is_move_assignable<phi::optional<T>>::value);
    }

    {
        struct T
        {
            T(const T&)            = delete;
            T(T&&)                 = default;
            T& operator=(const T&) = delete;
            T& operator=(T&&)      = default;
        };
        REQUIRE_FALSE(phi::is_copy_constructible<phi::optional<T>>::value);
        REQUIRE_FALSE(phi::is_copy_assignable<phi::optional<T>>::value);
        REQUIRE(phi::is_move_constructible<phi::optional<T>>::value);
        REQUIRE(phi::is_move_assignable<phi::optional<T>>::value);
    }

    {
        struct T
        {
            T(const T&)            = default;
            T(T&&)                 = delete;
            T& operator=(const T&) = default;
            T& operator=(T&&)      = delete;
        };
        REQUIRE(phi::is_copy_constructible<phi::optional<T>>::value);
        REQUIRE(phi::is_copy_assignable<phi::optional<T>>::value);
    }
}

TEST_CASE("optional constexpr")
{
    SECTION("empty construct")
    {
        PHI_CONSTEXPR phi::optional<int> o2{};
        PHI_CONSTEXPR phi::optional<int> o3 = {};
        PHI_CONSTEXPR phi::optional<int> o4 = phi::nullopt;
        PHI_CONSTEXPR phi::optional<int> o5 = {phi::nullopt};
        PHI_CONSTEXPR phi::optional<int> o6(phi::nullopt);

        STATIC_REQUIRE(!o2);
        STATIC_REQUIRE(!o3);
        STATIC_REQUIRE(!o4);
        STATIC_REQUIRE(!o5);
        STATIC_REQUIRE(!o6);
    }

    SECTION("value construct")
    {
        PHI_EXTENDED_CONSTEXPR phi::optional<int> o1 = 42;
        PHI_EXTENDED_CONSTEXPR phi::optional<int> o2{42};
        PHI_EXTENDED_CONSTEXPR phi::optional<int> o3(42);
        PHI_EXTENDED_CONSTEXPR phi::optional<int> o4 = {42};
        PHI_EXTENDED_CONSTEXPR int                i  = 42;
        PHI_EXTENDED_CONSTEXPR phi::optional<int> o5 = phi::move(i);
        PHI_EXTENDED_CONSTEXPR phi::optional<int> o6{phi::move(i)};
        PHI_EXTENDED_CONSTEXPR phi::optional<int> o7(phi::move(i));
        PHI_EXTENDED_CONSTEXPR phi::optional<int> o8 = {phi::move(i)};

        EXT_STATIC_REQUIRE(*o1 == 42);
        EXT_STATIC_REQUIRE(*o2 == 42);
        EXT_STATIC_REQUIRE(*o3 == 42);
        EXT_STATIC_REQUIRE(*o4 == 42);
        EXT_STATIC_REQUIRE(*o5 == 42);
        EXT_STATIC_REQUIRE(*o6 == 42);
        EXT_STATIC_REQUIRE(*o7 == 42);
        EXT_STATIC_REQUIRE(*o8 == 42);
    }
}

struct foo
{
    foo()     = default;
    foo(foo&) = delete;
    foo(foo&&)
    {}
};

TEST_CASE("optional Constructors")
{
    phi::optional<int> o1;
    REQUIRE(!o1);

    phi::optional<int> o2 = phi::nullopt;
    REQUIRE(!o2);

    phi::optional<int> o3 = 42;
    REQUIRE(*o3 == 42);

    phi::optional<int> o4 = o3;
    REQUIRE(*o4 == 42);

    phi::optional<int> o5 = o1;
    REQUIRE(!o5);

    phi::optional<int> o6 = phi::move(o3);
    REQUIRE(*o6 == 42);

    phi::optional<short> o7 = 42;
    REQUIRE(*o7 == 42);

    phi::optional<int> o8 = o7;
    REQUIRE(*o8 == 42);

    phi::optional<int> o9 = phi::move(o7);
    REQUIRE(*o9 == 42);

    {
        phi::optional<int&> o;
        REQUIRE(!o);

        phi::optional<int&> oo = o;
        REQUIRE(!oo);
    }

    {
        auto                i = 42;
        phi::optional<int&> o = i;
        REQUIRE(o);
        REQUIRE(*o == 42);

        phi::optional<int&> oo = o;
        REQUIRE(oo);
        REQUIRE(*oo == 42);
    }

    std::vector<foo> v;
    v.emplace_back();

#    if PHI_COMPILER_WORKAROUND(GCC, 7, 0, 0)
    phi::optional<std::vector<foo>> ov = phi::move(v);
    REQUIRE(ov->size() == 1);
#    else
    SKIP_CHECK();
#    endif
}

TEST_CASE("optional emplace")
{
#    if PHI_COMPILER_IS_BELOW(GCC, 8, 0, 0)
    SKIP_CHECK();
#    else
    phi::optional<std::pair<std::pair<int, int>, std::pair<double, double>>> i;
    i.emplace(std::piecewise_construct, std::make_tuple(0, 2), std::make_tuple(3, 4));
    REQUIRE(i->first.first == 0);
    REQUIRE(i->first.second == 2);
    REQUIRE(i->second.first == 3);
    REQUIRE(i->second.second == 4);
#    endif
}

PHI_CONSTEXPR int get_int(int)
{
    return 42;
}

PHI_CONSTEXPR phi::optional<int> get_opt_int(int)
{
    return 42;
}

TEST_CASE("optional monadic operations", "[monadic]")
{
#    if PHI_HAS_FEATURE_DECLTYPE_AUTO()
    SECTION("map")
    { // lhs is empty
        phi::optional<int> o1;
        auto               o1r = o1.map([](int i) { return i + 2; });
        STATIC_REQUIRE((phi::is_same<decltype(o1r), phi::optional<int>>::value));
        REQUIRE(!o1r);

        // lhs has value
        phi::optional<int> o2  = 40;
        auto               o2r = o2.map([](int i) { return i + 2; });
        STATIC_REQUIRE((phi::is_same<decltype(o2r), phi::optional<int>>::value));
        REQUIRE(o2r.value() == 42);

        struct rval_call_map
        {
            double operator()(int) &&
            {
                return 42.0;
            }
        };

        // ensure that function object is forwarded
        phi::optional<int> o3  = 42;
        auto               o3r = o3.map(rval_call_map{});
        STATIC_REQUIRE((phi::is_same<decltype(o3r), phi::optional<double>>::value));
        REQUIRE(o3r.value() == 42);

        // ensure that lhs is forwarded
        phi::optional<int> o4  = 40;
        auto               o4r = phi::move(o4).map([](int&& i) { return i + 2; });
        STATIC_REQUIRE((phi::is_same<decltype(o4r), phi::optional<int>>::value));
        REQUIRE(o4r.value() == 42);

        // ensure that lhs is const-propagated
        const phi::optional<int> o5  = 40;
        auto                     o5r = o5.map([](const int& i) { return i + 2; });
        STATIC_REQUIRE((phi::is_same<decltype(o5r), phi::optional<int>>::value));
        REQUIRE(o5r.value() == 42);

        // test void return
        phi::optional<int> o7  = 40;
        auto               f7  = [](const int&) { return; };
        auto               o7r = o7.map(f7);
        STATIC_REQUIRE((phi::is_same<decltype(o7r), phi::optional<phi::monostate>>::value));
        REQUIRE(o7r.has_value());

        // test each overload in turn
        phi::optional<int> o8  = 42;
        auto               o8r = o8.map([](int) { return 42; });
        REQUIRE(*o8r == 42);

        phi::optional<int> o9  = 42;
        auto               o9r = o9.map([](int) { return; });
        REQUIRE(o9r);

        phi::optional<int> o12  = 42;
        auto               o12r = phi::move(o12).map([](int) { return 42; });
        REQUIRE(*o12r == 42);

        phi::optional<int> o13  = 42;
        auto               o13r = phi::move(o13).map([](int) { return; });
        REQUIRE(o13r);

        const phi::optional<int> o16  = 42;
        auto                     o16r = o16.map([](int) { return 42; });
        REQUIRE(*o16r == 42);

        const phi::optional<int> o17  = 42;
        auto                     o17r = o17.map([](int) { return; });
        REQUIRE(o17r);

        const phi::optional<int> o20  = 42;
        auto                     o20r = phi::move(o20).map([](int) { return 42; });
        REQUIRE(*o20r == 42);

        const phi::optional<int> o21  = 42;
        auto                     o21r = phi::move(o21).map([](int) { return; });
        REQUIRE(o21r);

        phi::optional<int> o24  = phi::nullopt;
        auto               o24r = o24.map([](int) { return 42; });
        REQUIRE(!o24r);

        phi::optional<int> o25  = phi::nullopt;
        auto               o25r = o25.map([](int) { return; });
        REQUIRE(!o25r);

        phi::optional<int> o28  = phi::nullopt;
        auto               o28r = phi::move(o28).map([](int) { return 42; });
        REQUIRE(!o28r);

        phi::optional<int> o29  = phi::nullopt;
        auto               o29r = phi::move(o29).map([](int) { return; });
        REQUIRE(!o29r);

        const phi::optional<int> o32  = phi::nullopt;
        auto                     o32r = o32.map([](int) { return 42; });
        REQUIRE(!o32r);

        const phi::optional<int> o33  = phi::nullopt;
        auto                     o33r = o33.map([](int) { return; });
        REQUIRE(!o33r);

        const phi::optional<int> o36  = phi::nullopt;
        auto                     o36r = phi::move(o36).map([](int) { return 42; });
        REQUIRE(!o36r);

        const phi::optional<int> o37  = phi::nullopt;
        auto                     o37r = phi::move(o37).map([](int) { return; });
        REQUIRE(!o37r);

        // callable which returns a reference
        /*
        phi::optional<int> o38  = 42;
        auto               o38r = o38.map([](int& i) -> const int& { return i; });
        REQUIRE(o38r);
        REQUIRE(*o38r == 42);
        */

        int                 i   = 42;
        phi::optional<int&> o39 = i;
        o39.map([](int& x) { x = 12; });
        REQUIRE(i == 12);
    }

    SECTION("map constexpr")
    {
        // test each overload in turn
        PHI_CONSTEXPR phi::optional<int> o16  = 42;
        PHI_CONSTEXPR auto               o16r = o16.map(get_int);
        STATIC_REQUIRE(*o16r == 42);

        PHI_CONSTEXPR phi::optional<int> o20  = 42;
        PHI_CONSTEXPR auto               o20r = phi::move(o20).map(get_int);
        STATIC_REQUIRE(*o20r == 42);

        PHI_CONSTEXPR phi::optional<int> o32  = phi::nullopt;
        PHI_CONSTEXPR auto               o32r = o32.map(get_int);
        STATIC_REQUIRE(!o32r);
        PHI_CONSTEXPR phi::optional<int> o36  = phi::nullopt;
        PHI_CONSTEXPR auto               o36r = phi::move(o36).map(get_int);
        STATIC_REQUIRE(!o36r);
    }

    SECTION("transform")
    { // lhs is empty
        phi::optional<int> o1;
        auto               o1r = o1.transform([](int i) { return i + 2; });
        STATIC_REQUIRE((phi::is_same<decltype(o1r), phi::optional<int>>::value));
        REQUIRE(!o1r);

        // lhs has value
        phi::optional<int> o2  = 40;
        auto               o2r = o2.transform([](int i) { return i + 2; });
        STATIC_REQUIRE((phi::is_same<decltype(o2r), phi::optional<int>>::value));
        REQUIRE(o2r.value() == 42);

        struct rval_call_transform
        {
            double operator()(int) &&
            {
                return 42.0;
            }
        };

        // ensure that function object is forwarded
        phi::optional<int> o3  = 42;
        auto               o3r = o3.transform(rval_call_transform{});
        STATIC_REQUIRE((phi::is_same<decltype(o3r), phi::optional<double>>::value));
        REQUIRE(o3r.value() == 42);

        // ensure that lhs is forwarded
        phi::optional<int> o4  = 40;
        auto               o4r = phi::move(o4).transform([](int&& i) { return i + 2; });
        STATIC_REQUIRE((phi::is_same<decltype(o4r), phi::optional<int>>::value));
        REQUIRE(o4r.value() == 42);

        // ensure that lhs is const-propagated
        const phi::optional<int> o5  = 40;
        auto                     o5r = o5.transform([](const int& i) { return i + 2; });
        STATIC_REQUIRE((phi::is_same<decltype(o5r), phi::optional<int>>::value));
        REQUIRE(o5r.value() == 42);

        // test void return
        phi::optional<int> o7  = 40;
        auto               f7  = [](const int&) { return; };
        auto               o7r = o7.transform(f7);
        STATIC_REQUIRE((phi::is_same<decltype(o7r), phi::optional<phi::monostate>>::value));
        REQUIRE(o7r.has_value());

        // test each overload in turn
        phi::optional<int> o8  = 42;
        auto               o8r = o8.transform([](int) { return 42; });
        REQUIRE(*o8r == 42);

        phi::optional<int> o9  = 42;
        auto               o9r = o9.transform([](int) { return; });
        REQUIRE(o9r);

        phi::optional<int> o12  = 42;
        auto               o12r = phi::move(o12).transform([](int) { return 42; });
        REQUIRE(*o12r == 42);

        phi::optional<int> o13  = 42;
        auto               o13r = phi::move(o13).transform([](int) { return; });
        REQUIRE(o13r);

        const phi::optional<int> o16  = 42;
        auto                     o16r = o16.transform([](int) { return 42; });
        REQUIRE(*o16r == 42);

        const phi::optional<int> o17  = 42;
        auto                     o17r = o17.transform([](int) { return; });
        REQUIRE(o17r);

        const phi::optional<int> o20  = 42;
        auto                     o20r = phi::move(o20).transform([](int) { return 42; });
        REQUIRE(*o20r == 42);

        const phi::optional<int> o21  = 42;
        auto                     o21r = phi::move(o21).transform([](int) { return; });
        REQUIRE(o21r);

        phi::optional<int> o24  = phi::nullopt;
        auto               o24r = o24.transform([](int) { return 42; });
        REQUIRE(!o24r);

        phi::optional<int> o25  = phi::nullopt;
        auto               o25r = o25.transform([](int) { return; });
        REQUIRE(!o25r);

        phi::optional<int> o28  = phi::nullopt;
        auto               o28r = phi::move(o28).transform([](int) { return 42; });
        REQUIRE(!o28r);

        phi::optional<int> o29  = phi::nullopt;
        auto               o29r = phi::move(o29).transform([](int) { return; });
        REQUIRE(!o29r);

        const phi::optional<int> o32  = phi::nullopt;
        auto                     o32r = o32.transform([](int) { return 42; });
        REQUIRE(!o32r);

        const phi::optional<int> o33  = phi::nullopt;
        auto                     o33r = o33.transform([](int) { return; });
        REQUIRE(!o33r);

        const phi::optional<int> o36  = phi::nullopt;
        auto                     o36r = phi::move(o36).transform([](int) { return 42; });
        REQUIRE(!o36r);

        const phi::optional<int> o37  = phi::nullopt;
        auto                     o37r = phi::move(o37).transform([](int) { return; });
        REQUIRE(!o37r);

        // callable which returns a reference
        /*
        phi::optional<int> o38  = 42;
        auto               o38r = o38.transform([](int& i) -> const int& { return i; });
        REQUIRE(o38r);
        REQUIRE(*o38r == 42);
        */

        int                 i   = 42;
        phi::optional<int&> o39 = i;
        o39.transform([](int& x) { x = 12; });
        REQUIRE(i == 12);
    }

    SECTION("transform constexpr")
    {
        // test each overload in turn
        PHI_CONSTEXPR phi::optional<int> o16  = 42;
        PHI_CONSTEXPR auto               o16r = o16.transform(get_int);
        STATIC_REQUIRE(*o16r == 42);

        PHI_CONSTEXPR phi::optional<int> o20  = 42;
        PHI_CONSTEXPR auto               o20r = phi::move(o20).transform(get_int);
        STATIC_REQUIRE(*o20r == 42);

        PHI_CONSTEXPR phi::optional<int> o32  = phi::nullopt;
        PHI_CONSTEXPR auto               o32r = o32.transform(get_int);
        STATIC_REQUIRE(!o32r);
        PHI_CONSTEXPR phi::optional<int> o36  = phi::nullopt;
        PHI_CONSTEXPR auto               o36r = phi::move(o36).transform(get_int);
        STATIC_REQUIRE(!o36r);
    }

    SECTION("and_then")
    {
        // lhs is empty
        phi::optional<int> o1;
        auto               o1r = o1.and_then([](int) { return phi::optional<float>{42}; });
        STATIC_REQUIRE((phi::is_same<decltype(o1r), phi::optional<float>>::value));
        REQUIRE(!o1r);

        // lhs has value
        phi::optional<int> o2  = 12;
        auto               o2r = o2.and_then([](int) { return phi::optional<float>{42}; });
        STATIC_REQUIRE((phi::is_same<decltype(o2r), phi::optional<float>>::value));
        REQUIRE(o2r.value() == 42.f);

        // lhs is empty, rhs returns empty
        phi::optional<int> o3;
        auto               o3r = o3.and_then([](int) { return phi::optional<float>{}; });
        STATIC_REQUIRE((phi::is_same<decltype(o3r), phi::optional<float>>::value));
        REQUIRE(!o3r);

        // rhs returns empty
        phi::optional<int> o4  = 12;
        auto               o4r = o4.and_then([](int) { return phi::optional<float>{}; });
        STATIC_REQUIRE((phi::is_same<decltype(o4r), phi::optional<float>>::value));
        REQUIRE(!o4r);

        struct rval_call_and_then
        {
            phi::optional<double> operator()(int) &&
            {
                return phi::optional<double>(42.0);
            }
        };

        // ensure that function object is forwarded
        phi::optional<int> o5  = 42;
        auto               o5r = o5.and_then(rval_call_and_then{});
        STATIC_REQUIRE((phi::is_same<decltype(o5r), phi::optional<double>>::value));
        REQUIRE(o5r.value() == 42);

        // ensure that lhs is forwarded
        phi::optional<int> o6 = 42;
        auto o6r = phi::move(o6).and_then([](int&& i) { return phi::optional<double>(i); });
        STATIC_REQUIRE((phi::is_same<decltype(o6r), phi::optional<double>>::value));
        REQUIRE(o6r.value() == 42);

        // ensure that function object is const-propagated
        const phi::optional<int> o7 = 42;
        auto o7r = o7.and_then([](const int& i) { return phi::optional<double>(i); });
        STATIC_REQUIRE((phi::is_same<decltype(o7r), phi::optional<double>>::value));
        REQUIRE(o7r.value() == 42);

        // test each overload in turn
        phi::optional<int> o8  = 42;
        auto               o8r = o8.and_then([](int) { return phi::make_optional(42); });
        REQUIRE(*o8r == 42);

        phi::optional<int> o9  = 42;
        auto               o9r = phi::move(o9).and_then([](int) { return phi::make_optional(42); });
        REQUIRE(*o9r == 42);

        const phi::optional<int> o10  = 42;
        auto                     o10r = o10.and_then([](int) { return phi::make_optional(42); });
        REQUIRE(*o10r == 42);

        const phi::optional<int> o11 = 42;
        auto o11r = phi::move(o11).and_then([](int) { return phi::make_optional(42); });
        REQUIRE(*o11r == 42);

        phi::optional<int> o16  = phi::nullopt;
        auto               o16r = o16.and_then([](int) { return phi::make_optional(42); });
        REQUIRE(!o16r);

        phi::optional<int> o17 = phi::nullopt;
        auto o17r = phi::move(o17).and_then([](int) { return phi::make_optional(42); });
        REQUIRE(!o17r);

        const phi::optional<int> o18  = phi::nullopt;
        auto                     o18r = o18.and_then([](int) { return phi::make_optional(42); });
        REQUIRE(!o18r);

        const phi::optional<int> o19 = phi::nullopt;
        auto o19r = phi::move(o19).and_then([](int) { return phi::make_optional(42); });
        REQUIRE(!o19r);

        int                 i = 3;
        phi::optional<int&> o20{i};
        phi::move(o20).and_then([](int& r) { return phi::optional<int&>{++r}; });
        REQUIRE(o20);
        REQUIRE(i == 4);
    }

    SECTION("constexpr and_then")
    {
        PHI_CONSTEXPR phi::optional<int> o10  = 42;
        PHI_CONSTEXPR auto               o10r = o10.and_then(get_opt_int);
        REQUIRE(*o10r == 42);

        PHI_CONSTEXPR phi::optional<int> o11  = 42;
        PHI_CONSTEXPR auto               o11r = phi::move(o11).and_then(get_opt_int);
        REQUIRE(*o11r == 42);

        PHI_CONSTEXPR phi::optional<int> o18  = phi::nullopt;
        PHI_CONSTEXPR auto               o18r = o18.and_then(get_opt_int);
        REQUIRE(!o18r);

        PHI_CONSTEXPR phi::optional<int> o19  = phi::nullopt;
        PHI_CONSTEXPR auto               o19r = phi::move(o19).and_then(get_opt_int);
        REQUIRE(!o19r);
    }
#    endif

    SECTION("or else")
    {
        phi::optional<int> o1 = 42;
        REQUIRE(*(o1.or_else([] { return phi::make_optional(13); })) == 42);

        phi::optional<int> o2;
        REQUIRE(*(o2.or_else([] { return phi::make_optional(13); })) == 13);
    }

    SECTION("disjunction")
    {
        phi::optional<int> o1 = 42;
        phi::optional<int> o2 = 12;
        phi::optional<int> o3;

        REQUIRE(*o1.disjunction(o2) == 42);
        REQUIRE(*o1.disjunction(o3) == 42);
        REQUIRE(*o2.disjunction(o1) == 12);
        REQUIRE(*o2.disjunction(o3) == 12);
        REQUIRE(*o3.disjunction(o1) == 42);
        REQUIRE(*o3.disjunction(o2) == 12);
    }

    SECTION("conjunction")
    {
        phi::optional<int> o1 = 42;
        REQUIRE(*o1.conjunction(42.0) == 42.0);
        REQUIRE(*o1.conjunction(std::string{"hello"}) == std::string{"hello"});

        phi::optional<int> o2;
        REQUIRE(!o2.conjunction(42.0));
        REQUIRE(!o2.conjunction(std::string{"hello"}));
    }

    SECTION("map_or")
    {
        phi::optional<int> o1 = 21;
        REQUIRE((o1.map_or([](int x) { return x * 2; }, 13)) == 42);

        phi::optional<int> o2;
        REQUIRE((o2.map_or([](int x) { return x * 2; }, 13)) == 13);
    }

    SECTION("map_or_else")
    {
        phi::optional<int> o1 = 21;
        REQUIRE((o1.map_or_else([](int x) { return x * 2; }, [] { return 13; })) == 42);

        phi::optional<int> o2;
        REQUIRE((o2.map_or_else([](int x) { return x * 2; }, [] { return 13; })) == 13);
    }

    SECTION("take")
    {
        phi::optional<int> o1 = 42;
        REQUIRE(*o1.take() == 42);
        REQUIRE(!o1);

        phi::optional<int> o2;
        REQUIRE(!o2.take());
        REQUIRE(!o2);
    }

    struct bar
    {
        void non_const()
        {}
    };

#    if PHI_HAS_FEATURE_DECLTYPE_AUTO()
    SECTION("Issue #1")
    {
        phi::optional<bar> f = bar{};
        auto               l = [](auto&& x) { x.non_const(); };
        f.map(l);
    }
#    endif

    struct overloaded
    {
        phi::optional<int> operator()(bar&)
        {
            return 0;
        }
        phi::optional<std::string> operator()(const bar&)
        {
            return "";
        }
    };

#    if PHI_HAS_FEATURE_DECLTYPE_AUTO()
    SECTION("Issue #2")
    {
        phi::optional<bar> f = bar{};
        auto               x = f.and_then(overloaded{});

        PHI_UNUSED_VARIABLE(x);
    }
#    endif
}

struct takes_init_and_variadic
{
    std::vector<int>     v;
    std::tuple<int, int> t;
    template <class... Args>
    takes_init_and_variadic(std::initializer_list<int> l, Args&&... args)
        : v(l)
        , t(phi::forward<Args>(args)...)
    {}
};

TEST_CASE("In place", "[in_place]")
{
    phi::optional<int> o1{phi::in_place};
    phi::optional<int> o2(phi::in_place);
    REQUIRE(o1);
    REQUIRE(o1 == 0);
    REQUIRE(o2);
    REQUIRE(o2 == 0);

    phi::optional<int> o3(phi::in_place, 42);
    REQUIRE(o3 == 42);

#    if PHI_COMPILER_IS_BELOW(GCC, 8, 0, 0)
    SKIP_CHECK();
#    else
    phi::optional<std::tuple<int, int>> o4(phi::in_place, 0, 1);
    REQUIRE(o4);
    REQUIRE(std::get<0>(*o4) == 0);
    REQUIRE(std::get<1>(*o4) == 1);
#    endif

    phi::optional<std::vector<int>> o5(phi::in_place, {0, 1});
    REQUIRE(o5);
    REQUIRE((*o5)[0] == 0);
    REQUIRE((*o5)[1] == 1);

#    if PHI_COMPILER_IS_BELOW(GCC, 8, 0, 0)
    SKIP_CHECK();
#    else
    phi::optional<takes_init_and_variadic> o6(phi::in_place, {0, 1}, 2, 3);
    REQUIRE(o6->v[0] == 0);
    REQUIRE(o6->v[1] == 1);
    REQUIRE(std::get<0>(o6->t) == 2);
    REQUIRE(std::get<1>(o6->t) == 3);
#    endif
}

struct bar
{
    int& v()
    {
        return i;
    }
    int i = 0;
};

int& x(int& i)
{
    i = 42;
    return i;
}

PHI_GCC_SUPPRESS_WARNING_WITH_PUSH("-Wnull-dereference")

#    if PHI_HAS_FEATURE_DECLTYPE_AUTO()
TEST_CASE("issue 14")
{
    phi::optional<bar> f = bar{};
    auto               v = f.map(&bar::v).map(x);

    // Must return a reference
    CHECK_SAME_TYPE(decltype(v), phi::optional<int&>);

    REQUIRE(f->i == 42);
    REQUIRE(*v == 42);
    REQUIRE((&f->i) == (&*v));
}
#    endif

PHI_GCC_SUPPRESS_WARNING_POP()

struct fail_on_copy_self
{
    int value;
    fail_on_copy_self(int v)
        : value(v)
    {}
    fail_on_copy_self(const fail_on_copy_self& other)
        : value(other.value)
    {
        REQUIRE(&other != this);
    }
};

TEST_CASE("issue 15")
{
    phi::optional<fail_on_copy_self> o = fail_on_copy_self(42);

    o = o;
    REQUIRE(o->value == 42);
}

TEST_CASE("issue 33")
{
    int                 i = 0;
    int                 j = 0;
    phi::optional<int&> a = i;
    a.emplace(j);
    *a = 42;
    REQUIRE(j == 42);
    REQUIRE(*a == 42);
    REQUIRE(a.has_value());
}

TEST_CASE("Make optional", "[make_optional]")
{
    auto o1 = phi::make_optional(42);
    auto o2 = phi::optional<int>(42);

    PHI_CONSTEXPR bool is_same = phi::is_same<decltype(o1), phi::optional<int>>::value;
    REQUIRE(is_same);
    REQUIRE(o1 == o2);

#    if PHI_COMPILER_IS_BELOW(GCC, 8, 0, 0)
    SKIP_CHECK();
#    else
    auto o3 = phi::make_optional<std::tuple<int, int, int, int>>(0, 1, 2, 3);
    REQUIRE(std::get<0>(*o3) == 0);
    REQUIRE(std::get<1>(*o3) == 1);
    REQUIRE(std::get<2>(*o3) == 2);
    REQUIRE(std::get<3>(*o3) == 3);
#    endif

    auto o4 = phi::make_optional<std::vector<int>>({0, 1, 2, 3});
    REQUIRE(o4.value()[0] == 0);
    REQUIRE(o4.value()[1] == 1);
    REQUIRE(o4.value()[2] == 2);
    REQUIRE(o4.value()[3] == 3);

#    if PHI_COMPILER_IS_BELOW(GCC, 8, 0, 0)
    SKIP_CHECK();
#    else
    auto o5 = phi::make_optional<takes_init_and_variadic>({0, 1}, 2, 3);
    REQUIRE(o5->v[0] == 0);
    REQUIRE(o5->v[1] == 1);
    REQUIRE(std::get<0>(o5->t) == 2);
    REQUIRE(std::get<1>(o5->t) == 3);
#    endif

    auto i  = 42;
    auto o6 = phi::make_optional<int&>(i);
    REQUIRE((phi::is_same<decltype(o6), phi::optional<int&>>::value));
    REQUIRE(o6);
    REQUIRE(*o6 == 42);
}

TEST_CASE("Noexcept", "[noexcept]")
{
    phi::optional<int> o1{4};
    phi::optional<int> o2{42};

    SECTION("comparison with nullopt")
    {
        REQUIRE(noexcept(o1 == phi::nullopt));
        REQUIRE(noexcept(phi::nullopt == o1));
        REQUIRE(noexcept(o1 != phi::nullopt));
        REQUIRE(noexcept(phi::nullopt != o1));
        REQUIRE(noexcept(o1 < phi::nullopt));
        REQUIRE(noexcept(phi::nullopt < o1));
        REQUIRE(noexcept(o1 <= phi::nullopt));
        REQUIRE(noexcept(phi::nullopt <= o1));
        REQUIRE(noexcept(o1 > phi::nullopt));
        REQUIRE(noexcept(phi::nullopt > o1));
        REQUIRE(noexcept(o1 >= phi::nullopt));
        REQUIRE(noexcept(phi::nullopt >= o1));
    }

    SECTION("swap")
    {
        //TODO see why this fails
#    if !defined(_MSC_VER) || _MSC_VER > 1900
        REQUIRE(noexcept(swap(o1, o2)) == noexcept(o1.swap(o2)));

        struct nothrow_swappable
        {
            nothrow_swappable& swap(const nothrow_swappable&) PHI_NOEXCEPT
            {
                return *this;
            }
        };

        struct throw_swappable
        {
            throw_swappable() = default;
            throw_swappable(const throw_swappable&)
            {}
            throw_swappable(throw_swappable&&)
            {}
            throw_swappable& swap(const throw_swappable&)
            {
                return *this;
            }
        };

        phi::optional<nothrow_swappable> ont;
        // TODO: MSVC seems to have a problem with the swap here
#        if PHI_COMPILER_IS_NOT(MSVC)
        phi::optional<throw_swappable> ot;
#        endif

        REQUIRE(noexcept(ont.swap(ont)));
#        if (PHI_COMPILER_IS_NOT(GCC) || PHI_COMPILER_IS_ATLEAST(GCC, 9, 0, 0)) &&                 \
                PHI_COMPILER_IS_NOT(MSVC)
        REQUIRE(!noexcept(ot.swap(ot)));
#        endif
#    endif
    }

    SECTION("constructors")
    {
        //TODO see why this fails
#    if !defined(_MSC_VER) || _MSC_VER > 1900
        REQUIRE(noexcept(phi::optional<int>{}));
        REQUIRE(noexcept(phi::optional<int>{phi::nullopt}));

        struct nothrow_move
        {
            nothrow_move(nothrow_move&&) = default;
        };

        struct throw_move
        {
            throw_move(throw_move&&)
            {}
        };

        using nothrow_opt = phi::optional<nothrow_move>;
        using throw_opt   = phi::optional<throw_move>;

        REQUIRE(phi::is_nothrow_move_constructible<nothrow_opt>::value);
        REQUIRE_FALSE(phi::is_nothrow_move_constructible<throw_opt>::value);
#    endif
    }

    SECTION("assignment")
    {
        REQUIRE(noexcept(o1 = phi::nullopt));

        struct nothrow_move_assign
        {
            nothrow_move_assign()                                      = default;
            nothrow_move_assign(nothrow_move_assign&&)                 = default;
            nothrow_move_assign& operator=(const nothrow_move_assign&) = default;
        };

        struct throw_move_assign
        {
            throw_move_assign() = default;
            throw_move_assign(throw_move_assign&&)
            {}
            throw_move_assign& operator=(const throw_move_assign&)
            {
                return *this;
            }
        };

        using nothrow_opt = phi::optional<nothrow_move_assign>;
        using throw_opt   = phi::optional<throw_move_assign>;

        CHECK_NOEXCEPT(phi::declval<nothrow_opt>() = phi::declval<nothrow_opt>());
        CHECK_NOT_NOEXCEPT(phi::declval<throw_opt>() = phi::declval<throw_opt>());
    }

    SECTION("observers")
    {
        REQUIRE(noexcept(static_cast<bool>(o1)));
        REQUIRE(noexcept(o1.has_value()));
    }

    SECTION("modifiers")
    {
        REQUIRE(noexcept(o1.reset()));
    }
}

TEST_CASE("Nullopt", "[nullopt]")
{
    phi::optional<int> o1 = phi::nullopt;
    phi::optional<int> o2{phi::nullopt};
    phi::optional<int> o3(phi::nullopt);
    phi::optional<int> o4 = {phi::nullopt};

    REQUIRE(!o1);
    REQUIRE(!o2);
    REQUIRE(!o3);
    REQUIRE(!o4);

    REQUIRE_FALSE(phi::is_default_constructible<phi::nullopt_t>::value);
}

struct move_detector
{
    move_detector() = default;
    move_detector(move_detector&& rhs)
    {
        rhs.been_moved = true;
    }
    bool been_moved = false;
};

TEST_CASE("Observers", "[observers]")
{
    phi::optional<int>       o1 = 42;
    phi::optional<int>       o2;
    const phi::optional<int> o3 = 42;

    REQUIRE(*o1 == 42);
    REQUIRE(*o1 == o1.value());
    REQUIRE(o2.value_or(42) == 42);
    REQUIRE(o3.value() == 42);
    auto success = phi::is_same<decltype(o1.value()), int&>::value;
    REQUIRE(success);
    success = phi::is_same<decltype(o3.value()), const int&>::value;
    REQUIRE(success);
    success = phi::is_same<decltype(phi::move(o1).value()), int&&>::value;
    REQUIRE(success);

    success = phi::is_same<decltype(phi::move(o3).value()), const int&&>::value;
    REQUIRE(success);

    phi::optional<move_detector> o4{phi::in_place};
    move_detector                o5 = phi::move(o4).value();
    REQUIRE(o4->been_moved);
    REQUIRE_FALSE(o5.been_moved);
}

TEST_CASE("Relational ops", "[relops]")
{
    phi::optional<int> o1{4};
    phi::optional<int> o2{42};
    phi::optional<int> o3{};

    SECTION("self simple")
    {
        REQUIRE(!(o1 == o2));
        REQUIRE(o1 == o1);
        REQUIRE(o1 != o2);
        REQUIRE(!(o1 != o1));
        REQUIRE(o1 < o2);
        REQUIRE(!(o1 < o1));
        REQUIRE(!(o1 > o2));
        REQUIRE(!(o1 > o1));
        REQUIRE(o1 <= o2);
        REQUIRE(o1 <= o1);
        REQUIRE(!(o1 >= o2));
        REQUIRE(o1 >= o1);
    }

    SECTION("nullopt simple")
    {
        REQUIRE(!(o1 == phi::nullopt));
        REQUIRE(!(phi::nullopt == o1));
        REQUIRE(o1 != phi::nullopt);
        REQUIRE(phi::nullopt != o1);
        REQUIRE(!(o1 < phi::nullopt));
        REQUIRE(phi::nullopt < o1);
        REQUIRE(o1 > phi::nullopt);
        REQUIRE(!(phi::nullopt > o1));
        REQUIRE(!(o1 <= phi::nullopt));
        REQUIRE(phi::nullopt <= o1);
        REQUIRE(o1 >= phi::nullopt);
        REQUIRE(!(phi::nullopt >= o1));

        REQUIRE(o3 == phi::nullopt);
        REQUIRE(phi::nullopt == o3);
        REQUIRE(!(o3 != phi::nullopt));
        REQUIRE(!(phi::nullopt != o3));
        REQUIRE(!(o3 < phi::nullopt));
        REQUIRE(!(phi::nullopt < o3));
        REQUIRE(!(o3 > phi::nullopt));
        REQUIRE(!(phi::nullopt > o3));
        REQUIRE(o3 <= phi::nullopt);
        REQUIRE(phi::nullopt <= o3);
        REQUIRE(o3 >= phi::nullopt);
        REQUIRE(phi::nullopt >= o3);
    }

    SECTION("with T simple")
    {
        REQUIRE(!(o1 == 1));
        REQUIRE(!(1 == o1));
        REQUIRE(o1 != 1);
        REQUIRE(1 != o1);
        REQUIRE(!(o1 < 1));
        REQUIRE(1 < o1);
        REQUIRE(o1 > 1);
        REQUIRE(!(1 > o1));
        REQUIRE(!(o1 <= 1));
        REQUIRE(1 <= o1);
        REQUIRE(o1 >= 1);
        REQUIRE(!(1 >= o1));

        REQUIRE(o1 == 4);
        REQUIRE(4 == o1);
        REQUIRE(!(o1 != 4));
        REQUIRE(!(4 != o1));
        REQUIRE(!(o1 < 4));
        REQUIRE(!(4 < o1));
        REQUIRE(!(o1 > 4));
        REQUIRE(!(4 > o1));
        REQUIRE(o1 <= 4);
        REQUIRE(4 <= o1);
        REQUIRE(o1 >= 4);
        REQUIRE(4 >= o1);
    }

    phi::optional<std::string> o4{"hello"};
    phi::optional<std::string> o5{"xyz"};

    SECTION("self complex")
    {
        REQUIRE(!(o4 == o5));
        REQUIRE(o4 == o4);
        REQUIRE(o4 != o5);
        REQUIRE(!(o4 != o4));
        REQUIRE(o4 < o5);
        REQUIRE(!(o4 < o4));
        REQUIRE(!(o4 > o5));
        REQUIRE(!(o4 > o4));
        REQUIRE(o4 <= o5);
        REQUIRE(o4 <= o4);
        REQUIRE(!(o4 >= o5));
        REQUIRE(o4 >= o4);
    }

    SECTION("nullopt complex")
    {
        REQUIRE(!(o4 == phi::nullopt));
        REQUIRE(!(phi::nullopt == o4));
        REQUIRE(o4 != phi::nullopt);
        REQUIRE(phi::nullopt != o4);
        REQUIRE(!(o4 < phi::nullopt));
        REQUIRE(phi::nullopt < o4);
        REQUIRE(o4 > phi::nullopt);
        REQUIRE(!(phi::nullopt > o4));
        REQUIRE(!(o4 <= phi::nullopt));
        REQUIRE(phi::nullopt <= o4);
        REQUIRE(o4 >= phi::nullopt);
        REQUIRE(!(phi::nullopt >= o4));

        REQUIRE(o3 == phi::nullopt);
        REQUIRE(phi::nullopt == o3);
        REQUIRE(!(o3 != phi::nullopt));
        REQUIRE(!(phi::nullopt != o3));
        REQUIRE(!(o3 < phi::nullopt));
        REQUIRE(!(phi::nullopt < o3));
        REQUIRE(!(o3 > phi::nullopt));
        REQUIRE(!(phi::nullopt > o3));
        REQUIRE(o3 <= phi::nullopt);
        REQUIRE(phi::nullopt <= o3);
        REQUIRE(o3 >= phi::nullopt);
        REQUIRE(phi::nullopt >= o3);
    }

    SECTION("with T complex")
    {
        REQUIRE(!(o4 == "a"));
        REQUIRE(!("a" == o4));
        REQUIRE(o4 != "a");
        REQUIRE("a" != o4);
        REQUIRE(!(o4 < "a"));
        REQUIRE("a" < o4);
        REQUIRE(o4 > "a");
        REQUIRE(!("a" > o4));
        REQUIRE(!(o4 <= "a"));
        REQUIRE("a" <= o4);
        REQUIRE(o4 >= "a");
        REQUIRE(!("a" >= o4));

        REQUIRE(o4 == "hello");
        REQUIRE("hello" == o4);
        REQUIRE(!(o4 != "hello"));
        REQUIRE(!("hello" != o4));
        REQUIRE(!(o4 < "hello"));
        REQUIRE(!("hello" < o4));
        REQUIRE(!(o4 > "hello"));
        REQUIRE(!("hello" > o4));
        REQUIRE(o4 <= "hello");
        REQUIRE("hello" <= o4);
        REQUIRE(o4 >= "hello");
        REQUIRE("hello" >= o4);
    }
}

TEST_CASE("Swap value", "[swap.value]")
{
    phi::optional<int> o1 = 42;
    phi::optional<int> o2 = 12;
    o1.swap(o2);
    CHECK(o1.value() == 12);
    CHECK(o2.value() == 42);
}

TEST_CASE("Swap value with null intialized", "[swap.value_nullopt]")
{
    phi::optional<int> o1 = 42;
    phi::optional<int> o2 = phi::nullopt;
    o1.swap(o2);
    CHECK(!o1.has_value());
    CHECK(o2.value() == 42);
}

TEST_CASE("Swap null intialized with value", "[swap.nullopt_value]")
{
    phi::optional<int> o1 = phi::nullopt;
    phi::optional<int> o2 = 42;
    o1.swap(o2);
    CHECK(o1.value() == 42);
    CHECK(!o2.has_value());
}

#endif

PHI_MSVC_SUPPRESS_WARNING_POP()
PHI_GCC_SUPPRESS_WARNING_POP()
PHI_CLANG_SUPPRESS_WARNING_POP()
