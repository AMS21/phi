#include <phi/test/test_macros.hpp>

#include "constexpr_helper.hpp"
#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/compiler_support/constexpr.hpp>
#include <phi/compiler_support/noexcept.hpp>
#include <phi/compiler_support/unused.hpp>
#include <phi/compiler_support/warning.hpp>
#include <phi/core/address_of.hpp>
#include <phi/core/max_align_t.hpp>
#include <phi/iterator/begin.hpp>
#include <phi/iterator/end.hpp>
#include <phi/iterator/iterator_traits.hpp>
#include <phi/iterator/rbegin.hpp>
#include <phi/iterator/rend.hpp>
#include <phi/type_traits/is_aggregate.hpp>
#include <phi/type_traits/is_copy_assignable.hpp>
#include <phi/type_traits/is_copy_constructible.hpp>
#include <phi/type_traits/is_nothrow_swappable.hpp>
#include <phi/type_traits/is_swappable.hpp>
#include <cstdint>

PHI_CLANG_AND_GCC_SUPPRESS_WARNING_PUSH()
PHI_CLANG_AND_GCC_SUPPRESS_WARNING("-Wunreachable-code")
PHI_CLANG_AND_GCC_SUPPRESS_WARNING("-Wunused-variable")
PHI_CLANG_AND_GCC_SUPPRESS_WARNING("-Wunused-result")
PHI_CLANG_AND_GCC_SUPPRESS_WARNING("-Wfloat-equal")

PHI_GCC_SUPPRESS_WARNING("-Wnoexcept")
PHI_GCC_SUPPRESS_WARNING("-Wfloat-equal")

#include <phi/container/array.hpp>

PHI_MSVC_SUPPRESS_WARNING_PUSH()
PHI_MSVC_SUPPRESS_WARNING(4189) // 'x': local variable is initialized but not referenced
PHI_MSVC_SUPPRESS_WARNING(4834) // discarding return value of function with 'nodiscard' attribute
PHI_MSVC_SUPPRESS_WARNING(4702) // unreachable code
PHI_MSVC_SUPPRESS_WARNING(
        5246) // 'member': the initialization of a subobject should be wrapped in braces

struct NoDefault
{
    PHI_CONSTEXPR NoDefault(int /*unused*/)
    {}
};

// Test default initialization
// This one isn't constexpr because omitting to initialize fundamental types
// isn't valid in a constexpr context.

struct test_default_initialization
{
    template <typename T>
    void operator()() const
    {
        phi::array<T, 0> arr0;
        (void)arr0;
        phi::array<T, 1> arr1;
        (void)arr1;
        phi::array<T, 2> arr2;
        (void)arr2;
        phi::array<T, 3> arr3;
        (void)arr3;

        phi::array<NoDefault, 0> nodefault;
        (void)nodefault;
    }
};

struct test_nondefault_initialization
{
    template <typename T>
    PHI_EXTENDED_CONSTEXPR void operator()() const
    {
        // Check direct-list-initialization syntax (introduced in C++11)
        {
            {
                phi::array<T, 0> a0_0{};
                (void)a0_0;
            }
            {
                phi::array<T, 1> a1_0{};
                (void)a1_0;
                phi::array<T, 1> a1_1{T()};
                (void)a1_1;
            }
            {
                phi::array<T, 2> a2_0{};
                (void)a2_0;
                phi::array<T, 2> a2_1{T()};
                (void)a2_1;
                phi::array<T, 2> a2_2{T(), T()};
                (void)a2_2;
            }
            {
                phi::array<T, 3> a3_0{};
                (void)a3_0;
                phi::array<T, 3> a3_1{T()};
                (void)a3_1;
                phi::array<T, 3> a3_2{T(), T()};
                (void)a3_2;
                phi::array<T, 3> a3_3{T(), T(), T()};
                (void)a3_3;
            }

            phi::array<NoDefault, 0> nodefault{};
            (void)nodefault;
        }

        // Check copy-list-initialization syntax
        {
            {
                phi::array<T, 0> a0_0 = {};
                (void)a0_0;
            }
            {
                phi::array<T, 1> a1_0 = {};
                (void)a1_0;
                phi::array<T, 1> a1_1 = {T()};
                (void)a1_1;
            }
            {
                phi::array<T, 2> a2_0 = {};
                (void)a2_0;
                phi::array<T, 2> a2_1 = {T()};
                (void)a2_1;
                phi::array<T, 2> a2_2 = {T(), T()};
                (void)a2_2;
            }
            {
                phi::array<T, 3> a3_0 = {};
                (void)a3_0;
                phi::array<T, 3> a3_1 = {T()};
                (void)a3_1;
                phi::array<T, 3> a3_2 = {T(), T()};
                (void)a3_2;
                phi::array<T, 3> a3_3 = {T(), T(), T()};
                (void)a3_3;
            }

            phi::array<NoDefault, 0> nodefault = {};
            (void)nodefault;
        }

        // Test aggregate initialization
        {
            {
                // TODO: This is failing
                //phi::array<T, 0> a0_0 = {{}};
                //(void)a0_0;
            }
            {
                phi::array<T, 1> a1_0 = {{}};
                (void)a1_0;
                phi::array<T, 1> a1_1 = {{T()}};
                (void)a1_1;
            }
            {
                phi::array<T, 2> a2_0 = {{}};
                (void)a2_0;
                phi::array<T, 2> a2_1 = {{T()}};
                (void)a2_1;
                phi::array<T, 2> a2_2 = {{T(), T()}};
                (void)a2_2;
            }
            {
                phi::array<T, 3> a3_0 = {{}};
                (void)a3_0;
                phi::array<T, 3> a3_1 = {{T()}};
                (void)a3_1;
                phi::array<T, 3> a3_2 = {{T(), T()}};
                (void)a3_2;
                phi::array<T, 3> a3_3 = {{T(), T(), T()}};
                (void)a3_3;
            }

            // See http://wg21.link/LWG2157
            // TODO: This is failing
            //phi::array<NoDefault, 0> nodefault = {{}};
            //(void)nodefault;
        }
    }
};

// Test construction from an initializer-list
PHI_EXTENDED_CONSTEXPR bool test_initializer_list()
{
    {
        const phi::array<double, 3> a3_0 = {};
        PHI_RELEASE_ASSERT(a3_0[0u] >= double(), "");
        PHI_RELEASE_ASSERT(a3_0[1u] >= double(), "");
        PHI_RELEASE_ASSERT(a3_0[2u] >= double(), "");
    }
    {
        const phi::array<double, 3> a3_1 = {1};
        PHI_RELEASE_ASSERT(a3_1[0u] >= double(1), "");
        PHI_RELEASE_ASSERT(a3_1[1u] >= double(), "");
        PHI_RELEASE_ASSERT(a3_1[2u] >= double(), "");
    }
    {
        const phi::array<double, 3> a3_2 = {1, 2.2};
        PHI_RELEASE_ASSERT(a3_2[0u] >= double(1), "");
        PHI_RELEASE_ASSERT(a3_2[1u] >= 2.2, "");
        PHI_RELEASE_ASSERT(a3_2[2u] >= double(), "");
    }
    {
        const phi::array<double, 3> a3_3 = {1, 2, 3.5};
        PHI_RELEASE_ASSERT(a3_3[0u] >= double(1), "");
        PHI_RELEASE_ASSERT(a3_3[1u] >= double(2), "");
        PHI_RELEASE_ASSERT(a3_3[2u] >= 3.5, "");
    }

    return true;
}

struct Empty
{};
struct Trivial
{
    int i;
    int j;
};
struct NonTrivial
{
    PHI_CONSTEXPR NonTrivial()
    {}

    PHI_CONSTEXPR NonTrivial(NonTrivial const&)
    {}
};
struct NonEmptyNonTrivial
{
    int           i;
    int           j;
    PHI_CONSTEXPR NonEmptyNonTrivial()
        : i(22)
        , j(33)
    {}
    PHI_CONSTEXPR NonEmptyNonTrivial(NonEmptyNonTrivial const&)
        : i(22)
        , j(33)
    {}
};

template <typename F>
PHI_EXTENDED_CONSTEXPR bool with_all_types()
{
    F().template operator()<char>();
    F().template operator()<int>();
    F().template operator()<long>();
    F().template operator()<float>();
    F().template operator()<double>();
    F().template operator()<long double>();
    F().template operator()<Empty>();
    F().template operator()<Trivial>();
    F().template operator()<NonTrivial>();
    F().template operator()<NonEmptyNonTrivial>();

    return true;
}

TEST_CASE("Initialization")
{
    with_all_types<test_nondefault_initialization>();
    with_all_types<test_default_initialization>(); // not constexpr
    CHECK(test_initializer_list());

#if PHI_HAS_FEATURE_EXTENDED_CONSTEXPR()
    STATIC_REQUIRE(with_all_types<test_nondefault_initialization>());
    STATIC_REQUIRE(test_initializer_list());
#endif
}

struct NonTrivialCopy
{
    PHI_CONSTEXPR NonTrivialCopy()
    {}

    PHI_CONSTEXPR NonTrivialCopy(NonTrivialCopy const&)
    {}

    PHI_EXTENDED_CONSTEXPR NonTrivialCopy& operator=(NonTrivialCopy const&)
    {
        return *this;
    }
};

#if PHI_HAS_FEATURE_EXTENDED_CONSTEXPR()
PHI_CONSTEXPR bool test_implicit_copy_constexpr()
{
    {
        using Array = phi::array<double, 3>;
        Array array = {1.1, 2.2, 3.3};
        Array copy  = array;
        copy        = array;
    }
    {
        using Array = phi::array<const double, 3>;
        Array array = {1.1, 2.2, 3.3};
        Array copy  = array;
        (void)copy;
    }
    {
        using Array = phi::array<double, 0>;
        Array array = {};
        Array copy  = array;
        copy        = array;
    }
    {
        // const arrays of size 0 should disable the implicit copy assignment operator.
        using Array = phi::array<const double, 0>;
        Array array = {};
        Array copy  = array;
        (void)copy;
    }
    {
        using Array = phi::array<NoDefault, 0>;
        Array array = {};
        Array copy  = array;
        copy        = array;
    }
    {
        using Array = phi::array<const NoDefault, 0>;
        Array array = {};
        Array copy  = array;
        (void)copy;
    }

    // Make sure we can implicitly copy a phi::array of a non-trivially copyable type
    {
        using Array = phi::array<NonTrivialCopy, 0>;
        Array array = {};
        Array copy  = array;
        copy        = array;
    }
    {
        using Array = phi::array<NonTrivialCopy, 1>;
        Array array = {};
        Array copy  = array;
        copy        = array;
    }
    {
        using Array = phi::array<NonTrivialCopy, 2>;
        Array array = {};
        Array copy  = array;
        copy        = array;
    }

    return true;
}

TEST_CASE("array implicit copy constexpr")
{
    STATIC_REQUIRE(test_implicit_copy_constexpr());
}
#endif

TEST_CASE("array implicit copy runtime")
{
    {
        using Array = phi::array<double, 3>;
        Array array = {1.1, 2.2, 3.3};
        Array copy  = array;
        copy        = array;
        STATIC_REQUIRE(phi::is_copy_constructible<Array>::value);
        STATIC_REQUIRE(phi::is_copy_assignable<Array>::value);
    }
    {
        using Array = phi::array<const double, 3>;
        Array array = {1.1, 2.2, 3.3};
        Array copy  = array;
        (void)copy;
        STATIC_REQUIRE(phi::is_copy_constructible<Array>::value);
        STATIC_REQUIRE(phi::is_not_copy_assignable<Array>::value);
    }
    {
        using Array = phi::array<double, 0>;
        Array array = {};
        Array copy  = array;
        copy        = array;
        STATIC_REQUIRE(phi::is_copy_constructible<Array>::value);
        STATIC_REQUIRE(phi::is_copy_assignable<Array>::value);
    }
    {
        // const arrays of size 0 should disable the implicit copy assignment operator.
        using Array = phi::array<const double, 0>;
        Array array = {};
        Array copy  = array;
        (void)copy;
        STATIC_REQUIRE(phi::is_copy_constructible<Array>::value);
        // TODO: This fails
        //STATIC_REQUIRE(phi::is_not_copy_assignable<Array>::value);
    }
    {
        using Array = phi::array<NoDefault, 0>;
        Array array = {};
        Array copy  = array;
        copy        = array;
        STATIC_REQUIRE(phi::is_copy_constructible<Array>::value);
        STATIC_REQUIRE(phi::is_copy_assignable<Array>::value);
    }
    {
        using Array = phi::array<const NoDefault, 0>;
        Array array = {};
        Array copy  = array;
        (void)copy;
        STATIC_REQUIRE(phi::is_copy_constructible<Array>::value);
        // TODO: This fails
        //STATIC_REQUIRE(phi::is_not_copy_assignable<Array>::value);
    }

    // Make sure we can implicitly copy a phi::array of a non-trivially copyable type
    {
        using Array = phi::array<NonTrivialCopy, 0>;
        Array array = {};
        Array copy  = array;
        copy        = array;
        STATIC_REQUIRE(phi::is_copy_constructible<Array>::value);
    }
    {
        using Array = phi::array<NonTrivialCopy, 1>;
        Array array = {};
        Array copy  = array;
        copy        = array;
        STATIC_REQUIRE(phi::is_copy_constructible<Array>::value);
    }
    {
        using Array = phi::array<NonTrivialCopy, 2>;
        Array array = {};
        Array copy  = array;
        copy        = array;
        STATIC_REQUIRE(phi::is_copy_constructible<Array>::value);
    }
}

TEST_CASE("implicit copy")
{
    // Validate whether the container can be copy-assigned with an ADL-hijacking operator&
    phi::array<operator_hijacker, 1> arr_o;
    phi::array<operator_hijacker, 1> arr;
    arr = arr_o;
}

// NOLINTNEXTLINE(readability-function-size)
TEST_CASE("Array")
{
    using T   = phi::array<int, 3>;
    using TC  = phi::array<const int, 3>;
    using T0  = phi::array<int, 0>;
    using TC0 = phi::array<const int, 0>;

    SECTION("at/operator[]")
    {
        SECTION("Constexpr")
        {
            PHI_CONSTEXPR T arr = {1, 2, 4};

            CHECK_SAME_TYPE(decltype(arr.at(0u)), T::const_reference);
            CHECK_SAME_TYPE(decltype(arr.at(0u)), const int&);
            CHECK_NOEXCEPT(arr.at(0u));

            CHECK_SAME_TYPE(decltype(arr[0u]), T::const_reference);
            CHECK_SAME_TYPE(decltype(arr[0u]), const int&);
            CHECK_NOEXCEPT(arr[0u]);

            EXT_STATIC_REQUIRE(arr.at(0u) == 1);
            EXT_STATIC_REQUIRE(arr[0u] == 1);
            EXT_STATIC_REQUIRE(arr.at(1u) == 2);
            EXT_STATIC_REQUIRE(arr[1u] == 2);
            EXT_STATIC_REQUIRE(arr.at(2u) == 4);
            EXT_STATIC_REQUIRE(arr[2u] == 4);
        }

        SECTION("non const")
        {
            T arr = {1, 2, 4};

            CHECK_SAME_TYPE(decltype(arr.at(0u)), T::reference);
            CHECK_SAME_TYPE(decltype(arr.at(0u)), int&);
            CHECK_SAME_TYPE(decltype(arr[0u]), T::reference);
            CHECK_SAME_TYPE(decltype(arr[0u]), int&);
            CHECK_NOEXCEPT(arr.at(0u));
            CHECK_NOEXCEPT(arr[0u]);

            typename T::reference ref1 = arr.at(0u);
            CHECK(ref1 == 1);
            ref1 = 5;
            CHECK(ref1 == 5);
            CHECK(arr.at(0u) == 5);
            CHECK(arr[0u] == 5);

            typename T::reference ref2 = arr.at(1u);
            CHECK(ref2 == 2);
            ref2 = 21;
            CHECK(ref2 == 21);
            CHECK(arr.at(1u) == 21);
            CHECK(arr[1u] == 21);
        }

        SECTION("const")
        {
            const T arr = {1, 2, 4};

            CHECK_SAME_TYPE(decltype(arr.at(0u)), T::const_reference);
            CHECK_SAME_TYPE(decltype(arr.at(0u)), const int&);
            CHECK_SAME_TYPE(decltype(arr[0u]), T::const_reference);
            CHECK_SAME_TYPE(decltype(arr[0u]), const int&);
            CHECK_NOEXCEPT(arr.at(0u));
            CHECK_NOEXCEPT(arr[0u]);

            typename T::const_reference ref1 = arr.at(0u);
            CHECK(ref1 == 1);

            typename T::const_reference ref2 = arr.at(1u);
            CHECK(ref2 == 2);
        }

        SECTION("Zero sized non const")
        {
            {
                T0 arr = {};

                CHECK_SAME_TYPE(decltype(arr.at(0u)), T0::reference);
                CHECK_SAME_TYPE(decltype(arr.at(0u)), int&);
                CHECK_SAME_TYPE(decltype(arr[0u]), T0::reference);
                CHECK_SAME_TYPE(decltype(arr[0u]), int&);
                CHECK_NOEXCEPT(arr.at(0u));
                CHECK_NOEXCEPT(arr[0u]);

#if !defined(PHI_CONFIG_COVERAGE_BUILD)
                if (arr.size() > 0u) // always false
                {
                    T0::reference ref1 = arr.at(0u);
                    T0::reference ref2 = arr[0u];
                    (void)ref1;
                    (void)ref2;
                }
#endif
            }

            {
                TC0 arr = {};

                CHECK_SAME_TYPE(decltype(arr.at(0u)), TC0::reference);
                CHECK_SAME_TYPE(decltype(arr.at(0u)), const int&);
                CHECK_SAME_TYPE(decltype(arr[0u]), TC0::reference);
                CHECK_SAME_TYPE(decltype(arr[0u]), const int&);
                CHECK_NOEXCEPT(arr.at(0u));
                CHECK_NOEXCEPT(arr[0u]);

#if !defined(PHI_CONFIG_COVERAGE_BUILD)
                if (arr.size() > 0u) // always false
                {
                    TC0::reference ref1 = arr.at(0u);
                    TC0::reference ref2 = arr[0u];
                    (void)ref1;
                    (void)ref2;
                }
#endif
            }
        }

        SECTION("Zero sized const")
        {
            {
                const T0 arr = {};

                CHECK_SAME_TYPE(decltype(arr.at(0u)), T0::const_reference);
                CHECK_SAME_TYPE(decltype(arr.at(0u)), const int&);
                CHECK_SAME_TYPE(decltype(arr[0u]), T0::const_reference);
                CHECK_SAME_TYPE(decltype(arr[0u]), const int&);
                CHECK_NOEXCEPT(arr.at(0u));
                CHECK_NOEXCEPT(arr[0u]);

#if !defined(PHI_CONFIG_COVERAGE_BUILD)
                if (arr.size() > 0u) // always false
                {
                    T0::const_reference ref1 = arr.at(0u);
                    T0::const_reference ref2 = arr[0u];
                    (void)ref1;
                    (void)ref2;
                }
#endif
            }

            {
                const TC0 arr = {};

                CHECK_SAME_TYPE(decltype(arr.at(0u)), TC0::const_reference);
                CHECK_SAME_TYPE(decltype(arr.at(0u)), const int&);
                CHECK_SAME_TYPE(decltype(arr[0u]), TC0::const_reference);
                CHECK_SAME_TYPE(decltype(arr[0u]), const int&);
                CHECK_NOEXCEPT(arr.at(0u));
                CHECK_NOEXCEPT(arr[0u]);

#if !defined(PHI_CONFIG_COVERAGE_BUILD)
                if (arr.size() > 0u) // always false
                {
                    TC0::const_reference ref1 = arr.at(0u);
                    TC0::const_reference ref2 = arr[0u];
                    (void)ref1;
                    (void)ref2;
                }
#endif
            }
        }

        SECTION("tracked")
        {
            phi::array<tracked, 3> tracked_array;

            CHECK(tracked_array.at(0u).value() == 0);

            tracked_array.at(0u).set_value(25);

            CHECK(tracked_array.at(0u).value() == 25);
        }

        SECTION("Traps")
        {
            phi::array<trap_constructible, 3> test1 = {};
            trap_constructible&               a_ref = test1.at(0u);
            PHI_UNUSED_VARIABLE(a_ref);

            phi::array<trap_implicit_conversion, 3> test2 = {};
            trap_implicit_conversion&               b_ref = test2.at(0u);
            PHI_UNUSED_VARIABLE(b_ref);

            phi::array<trap_comma, 3> test3 = {};
            trap_comma&               c_ref = test3.at(0u);
            PHI_UNUSED_VARIABLE(c_ref);

            phi::array<trap_call, 3> test4 = {};
            trap_call&               d_ref = test4.at(0u);
            PHI_UNUSED_VARIABLE(d_ref);

            phi::array<trap_self_assign, 3> test5 = {};
            trap_self_assign&               e_ref = test5.at(0u);
            PHI_UNUSED_VARIABLE(e_ref);
        }
    }

    SECTION("front")
    {
        SECTION("Constexpr")
        {
            PHI_CONSTEXPR T constexpr_array = {1, 2, 4};

            CHECK_SAME_TYPE(decltype(constexpr_array.front()), T::const_reference);
            CHECK_SAME_TYPE(decltype(constexpr_array.front()), const int&);
            CHECK_NOEXCEPT(constexpr_array.front());

            EXT_STATIC_REQUIRE(constexpr_array.front() == 1);
        }

        SECTION("non const")
        {
            T arr = {1, 2, 4};

            CHECK_SAME_TYPE(decltype(arr.front()), T::reference);
            CHECK_SAME_TYPE(decltype(arr.front()), int&);
            CHECK_NOEXCEPT(arr.front());

            typename T::reference ref = arr.front();
            CHECK(ref == 1);
            CHECK(arr.front() == 1);
            CHECK(arr.at(0u) == 1);
            CHECK(arr[0u] == 1);
            ref = 5;
            CHECK(ref == 5);
            CHECK(arr.front() == 5);
            CHECK(arr.at(0u) == 5);
            CHECK(arr[0u] == 5);
        }

        SECTION("const")
        {
            const T arr = {1, 2, 4};

            CHECK_SAME_TYPE(decltype(arr.front()), T::const_reference);
            CHECK_SAME_TYPE(decltype(arr.front()), const int&);
            CHECK_NOEXCEPT(arr.front());

            typename T::const_reference ref = arr.front();
            CHECK(ref == 1);
            CHECK(arr.front() == 1);
            CHECK(arr.at(0u) == 1);
            CHECK(arr[0u] == 1);

            TC arr2 = {1, 2, 4};

            CHECK_SAME_TYPE(decltype(arr2.front()), TC::reference);
            CHECK_SAME_TYPE(decltype(arr2.front()), const int&);
            CHECK_NOEXCEPT(arr2.front());

            typename TC::reference ref2 = arr2.front();
            CHECK(ref2 == 1);
            CHECK(arr2.front() == 1);
            CHECK(arr2.at(0u) == 1);
            CHECK(arr2[0u] == 1);
        }

        SECTION("Zero size non const")
        {
            T0 arr = {};
            CHECK_SAME_TYPE(decltype(arr.front()), T0::reference);
            CHECK_SAME_TYPE(decltype(arr.front()), int&);
            CHECK_NOEXCEPT(arr.front());

#if !defined(PHI_CONFIG_COVERAGE_BUILD)
            if (arr.size() > 0u) // always false
            {
                (void)arr.front();
            }
#endif

            TC0 arr2 = {};
            CHECK_SAME_TYPE(decltype(arr2.front()), TC0::reference);
            CHECK_SAME_TYPE(decltype(arr2.front()), const int&);
            CHECK_NOEXCEPT(arr2.front());

#if !defined(PHI_CONFIG_COVERAGE_BUILD)
            if (arr2.size() > 0u) // always false
            {
                (void)arr2.front();
            }
#endif
        }

        SECTION("Zero size const")
        {
            const T0 arr = {};
            CHECK_SAME_TYPE(decltype(arr.front()), T0::const_reference);
            CHECK_SAME_TYPE(decltype(arr.front()), const int&);
            CHECK_NOEXCEPT(arr.front());

#if !defined(PHI_CONFIG_COVERAGE_BUILD)
            if (arr.size() > 0u) // always false
            {
                (void)arr.front();
            }
#endif

            const TC0 arr2 = {};
            CHECK_SAME_TYPE(decltype(arr2.front()), TC0::const_reference);
            CHECK_SAME_TYPE(decltype(arr2.front()), const int&);
            CHECK_NOEXCEPT(arr2.front());

#if !defined(PHI_CONFIG_COVERAGE_BUILD)
            if (arr2.size() > 0u) // always false
            {
                (void)arr2.front();
            }
#endif
        }

        SECTION("tracked")
        {
            phi::array<tracked, 3> tracked_array;

            CHECK(tracked_array.front().value() == 0);

            tracked_array.front().set_value(25);

            CHECK(tracked_array.front().value() == 25);
        }

        SECTION("Traps")
        {
            phi::array<trap_constructible, 3> test1 = {};
            trap_constructible&               a_ref = test1.front();
            PHI_UNUSED_VARIABLE(a_ref);

            phi::array<trap_implicit_conversion, 3> test2 = {};
            trap_implicit_conversion&               b_ref = test2.front();
            PHI_UNUSED_VARIABLE(b_ref);

            phi::array<trap_comma, 3> test3 = {};
            trap_comma&               c_ref = test3.front();
            PHI_UNUSED_VARIABLE(c_ref);

            phi::array<trap_call, 3> test4 = {};
            trap_call&               d_ref = test4.front();
            PHI_UNUSED_VARIABLE(d_ref);

            phi::array<trap_self_assign, 3> test5 = {};
            trap_self_assign&               e_ref = test5.front();
            PHI_UNUSED_VARIABLE(e_ref);
        }
    }

    SECTION("back")
    {
        SECTION("Constexpr")
        {
            PHI_CONSTEXPR T constexpr_array = {1, 2, 4};

            EXT_STATIC_REQUIRE(constexpr_array.back() == 4);
        }

        SECTION("non const")
        {
            T arr = {1, 2, 4};

            CHECK_SAME_TYPE(decltype(arr.back()), T::reference);
            CHECK_SAME_TYPE(decltype(arr.back()), int&);
            CHECK_NOEXCEPT(arr.back());

            typename T::reference ref = arr.back();
            CHECK(ref == 4);
            CHECK(arr.back() == 4);
            CHECK(arr.at(2u) == 4);
            CHECK(arr[2u] == 4);
            ref = 5;
            CHECK(ref == 5);
            CHECK(arr.back() == 5);
            CHECK(arr.at(2u) == 5);
            CHECK(arr[2u] == 5);

            TC arr2 = {1, 2, 4};

            CHECK_SAME_TYPE(decltype(arr2.back()), TC::reference);
            CHECK_SAME_TYPE(decltype(arr2.back()), const int&);
            CHECK_NOEXCEPT(arr2.back());

            typename TC::reference ref2 = arr2.back();
            CHECK(ref2 == 4);
            CHECK(arr2.back() == 4);
            CHECK(arr2.at(2u) == 4);
            CHECK(arr2[2u] == 4);
        }

        SECTION("const")
        {
            const T arr = {1, 2, 4};

            CHECK_SAME_TYPE(decltype(arr.back()), T::const_reference);
            CHECK_SAME_TYPE(decltype(arr.back()), const int&);
            CHECK_NOEXCEPT(arr.back());

            typename T::const_reference ref = arr.back();
            CHECK(ref == 4);
            CHECK(arr.back() == 4);
            CHECK(arr.at(2u) == 4);
            CHECK(arr[2u] == 4);

            const TC arr2 = {1, 2, 4};

            CHECK_SAME_TYPE(decltype(arr2.back()), TC::const_reference);
            CHECK_SAME_TYPE(decltype(arr2.back()), const int&);
            CHECK_NOEXCEPT(arr2.back());

            typename T::const_reference ref2 = arr2.back();
            CHECK(ref2 == 4);
            CHECK(arr2.back() == 4);
            CHECK(arr2.at(2u) == 4);
            CHECK(arr2[2u] == 4);
        }

        SECTION("Zero size non const")
        {
            T0 arr = {};
            CHECK_SAME_TYPE(decltype(arr.back()), T0::reference);
            CHECK_SAME_TYPE(decltype(arr.back()), int&);
            CHECK_NOEXCEPT(arr.back());

#if !defined(PHI_CONFIG_COVERAGE_BUILD)
            if (arr.size() > 0u) // always false
            {
                (void)arr.back();
            }
#endif

            TC0 arr2 = {};
            CHECK_SAME_TYPE(decltype(arr2.back()), TC0::reference);
            CHECK_SAME_TYPE(decltype(arr2.back()), const int&);
            CHECK_NOEXCEPT(arr2.back());

#if !defined(PHI_CONFIG_COVERAGE_BUILD)
            if (arr2.size() > 0u) // always false
            {
                (void)arr2.back();
            }
#endif
        }

        SECTION("Zero size const")
        {
            const T0 arr = {};
            CHECK_SAME_TYPE(decltype(arr.back()), T0::const_reference);
            CHECK_SAME_TYPE(decltype(arr.back()), const int&);
            CHECK_NOEXCEPT(arr.back());

#if !defined(PHI_CONFIG_COVERAGE_BUILD)
            if (arr.size() > 0u) // always false
            {
                (void)arr.back();
            }
#endif

            const TC0 arr2 = {};
            CHECK_SAME_TYPE(decltype(arr2.back()), TC0::const_reference);
            CHECK_SAME_TYPE(decltype(arr2.back()), const int&);
            CHECK_NOEXCEPT(arr2.back());

#if !defined(PHI_CONFIG_COVERAGE_BUILD)
            if (arr2.size() > 0u) // always false
            {
                (void)arr2.back();
            }
#endif
        }

        SECTION("tracked")
        {
            phi::array<tracked, 3> tracked_array;

            CHECK(tracked_array.back().value() == 0);

            tracked_array.back().set_value(25);

            CHECK(tracked_array.back().value() == 25);
        }

        SECTION("Traps")
        {
            phi::array<trap_constructible, 3> test1 = {};
            trap_constructible&               a_ref = test1.back();
            PHI_UNUSED_VARIABLE(a_ref);

            phi::array<trap_implicit_conversion, 3> test2 = {};
            trap_implicit_conversion&               b_ref = test2.back();
            PHI_UNUSED_VARIABLE(b_ref);

            phi::array<trap_comma, 3> test3 = {};
            trap_comma&               c_ref = test3.back();
            PHI_UNUSED_VARIABLE(c_ref);

            phi::array<trap_call, 3> test4 = {};
            trap_call&               d_ref = test4.back();
            PHI_UNUSED_VARIABLE(d_ref);

            phi::array<trap_self_assign, 3> test5 = {};
            trap_self_assign&               e_ref = test5.back();
            PHI_UNUSED_VARIABLE(e_ref);
        }
    }

    SECTION("data")
    {
        SECTION("non const")
        {
            {
                T    arr     = {1, 2, 4};
                int* pointer = arr.data();

                CHECK_SAME_TYPE(decltype(arr.data()), T::pointer);
                CHECK_SAME_TYPE(decltype(arr.data()), int*);
                CHECK_NOEXCEPT(arr.data());

                CHECK(arr.data() == &arr[0u]); // NOLINT(readability-container-data-pointer)
                CHECK(*arr.data() == arr[0u]);

                CHECK(pointer != nullptr);
                CHECK(*pointer == 1);
                CHECK(pointer[0] == 1);
                CHECK(pointer[1] == 2);
                CHECK(pointer[2] == 4);

                pointer[0] = 5;

                CHECK(*pointer == 5);
                CHECK(pointer[0] == 5);
                CHECK(*arr.data() == 5);
                CHECK(arr.data()[0] == 5);
                CHECK(arr.at(0u) == 5);
                CHECK(arr[0u] == 5);
            }

            {
                TC         arr     = {1, 2, 4};
                const int* pointer = arr.data();

                CHECK_SAME_TYPE(decltype(arr.data()), TC::pointer);
                CHECK_SAME_TYPE(decltype(arr.data()), const int*);
                CHECK_NOEXCEPT(arr.data());

                CHECK(arr.data() == &arr[0u]); // NOLINT(readability-container-data-pointer)
                CHECK(*arr.data() == arr[0u]);

                CHECK(pointer != nullptr);
                CHECK(*pointer == 1);
                CHECK(pointer[0] == 1);
                CHECK(pointer[1] == 2);
                CHECK(pointer[2] == 4);
            }
        }

        SECTION("const")
        {
            {
                const T    arr     = {1, 2, 4};
                const int* pointer = arr.data();

                CHECK_SAME_TYPE(decltype(arr.data()), T::const_pointer);
                CHECK_SAME_TYPE(decltype(arr.data()), const int*);
                CHECK_NOEXCEPT(arr.data());

                CHECK(arr.data() == &arr[0u]); // NOLINT(readability-container-data-pointer)
                CHECK(*arr.data() == arr[0u]);

                CHECK(pointer != nullptr);
                CHECK(*pointer == 1);
                CHECK(pointer[0] == 1);
                CHECK(pointer[1] == 2);
                CHECK(pointer[2] == 4);
            }

            {
                const TC   arr     = {1, 2, 4};
                const int* pointer = arr.data();

                CHECK_SAME_TYPE(decltype(arr.data()), TC::const_pointer);
                CHECK_SAME_TYPE(decltype(arr.data()), const int*);
                CHECK_NOEXCEPT(arr.data());

                CHECK(arr.data() == &arr[0u]); // NOLINT(readability-container-data-pointer)
                CHECK(*arr.data() == arr[0u]);

                CHECK(pointer != nullptr);
                CHECK(*pointer == 1);
                CHECK(pointer[0] == 1);
                CHECK(pointer[1] == 2);
                CHECK(pointer[2] == 4);
            }
        }

        SECTION("zero sized non const")
        {
            {
                T0   arr     = {};
                int* pointer = arr.data();

                CHECK_SAME_TYPE(decltype(arr.data()), T0::pointer);
                CHECK_SAME_TYPE(decltype(arr.data()), int*);
                CHECK_NOEXCEPT(arr.data());

                CHECK(pointer == nullptr);
            }

            {
                TC0        arr     = {};
                const int* pointer = arr.data();

                CHECK_SAME_TYPE(decltype(arr.data()), TC0::pointer);
                CHECK_SAME_TYPE(decltype(arr.data()), const int*);
                CHECK_NOEXCEPT(arr.data());

                CHECK(pointer == nullptr);
            }

            {
                using T2                           = phi::array<non_default_constructible, 0>;
                T2                         arr     = {};
                non_default_constructible* pointer = arr.data();

                CHECK_SAME_TYPE(decltype(arr.data()), T2::pointer);
                CHECK_SAME_TYPE(decltype(arr.data()), non_default_constructible*);
                CHECK_NOEXCEPT(arr.data());

                CHECK(pointer == nullptr);
            }
        }

        SECTION("zero sized const")
        {
            {
                const T0   arr     = {};
                const int* pointer = arr.data();

                CHECK_SAME_TYPE(decltype(arr.data()), T0::const_pointer);
                CHECK_SAME_TYPE(decltype(arr.data()), const int*);
                CHECK_NOEXCEPT(arr.data());

                CHECK(pointer == nullptr);
            }

            {
                const TC0  arr     = {};
                const int* pointer = arr.data();

                CHECK_SAME_TYPE(decltype(arr.data()), TC0::const_pointer);
                CHECK_SAME_TYPE(decltype(arr.data()), const int*);
                CHECK_NOEXCEPT(arr.data());

                CHECK(pointer == nullptr);
            }

            {
                using T2                                 = phi::array<non_default_constructible, 0>;
                const T2                         arr     = {};
                const non_default_constructible* pointer = arr.data();

                CHECK_SAME_TYPE(decltype(arr.data()), T2::const_pointer);
                CHECK_SAME_TYPE(decltype(arr.data()), const non_default_constructible*);
                CHECK_NOEXCEPT(arr.data());

                CHECK(pointer == nullptr);
            }
        }

        SECTION("alignment")
        {
            {
                using T2                         = phi::array<natural_alignment, 0>;
                const T2                 arr     = {};
                const natural_alignment* pointer = arr.data();
                std::uintptr_t           p_int   = reinterpret_cast<std::uintptr_t>(pointer);

                CHECK(p_int % alignof(natural_alignment) == 0);
            }

            {
                using T2                         = phi::array<natural_alignment, 3>;
                const T2                 arr     = {};
                const natural_alignment* pointer = arr.data();
                std::uintptr_t           p_int   = reinterpret_cast<std::uintptr_t>(pointer);

                CHECK(p_int % alignof(natural_alignment) == 0);
            }

            {
                using T2                        = phi::array<phi::max_align_t, 0>;
                const T2                arr     = {};
                const phi::max_align_t* pointer = arr.data();
                std::uintptr_t          p_int   = reinterpret_cast<std::uintptr_t>(pointer);

                CHECK(p_int % alignof(phi::max_align_t) == 0);
            }

            {
                using T2                        = phi::array<phi::max_align_t, 3>;
                const T2                arr     = {};
                const phi::max_align_t* pointer = arr.data();
                std::uintptr_t          p_int   = reinterpret_cast<std::uintptr_t>(pointer);

                CHECK(p_int % alignof(phi::max_align_t) == 0);
            }
        }

        SECTION("tracked")
        {
            phi::array<tracked, 3> tracked_array;
            tracked*               pointer = tracked_array.data();

            CHECK(pointer->value() == 0);

            pointer->set_value(25);

            CHECK(pointer->value() == 25);
        }

        SECTION("Traps")
        {
            phi::array<trap_constructible, 3> test1 = {};
            trap_constructible*               a_p   = test1.data();
            PHI_UNUSED_VARIABLE(a_p);

            phi::array<trap_implicit_conversion, 3> test2 = {};
            trap_implicit_conversion*               b_p   = test2.data();
            PHI_UNUSED_VARIABLE(b_p);

            phi::array<trap_comma, 3> test3 = {};
            trap_comma*               c_p   = test3.data();
            PHI_UNUSED_VARIABLE(c_p);

            phi::array<trap_call, 3> test4 = {};
            trap_call*               d_p   = test4.data();
            PHI_UNUSED_VARIABLE(d_p);

            phi::array<trap_self_assign, 3> test5 = {};
            trap_self_assign*               e_p   = test5.data();
            PHI_UNUSED_VARIABLE(e_p);
        }
    }

    SECTION("reverse")
    {
        {
            T arr = {1, 2, 3};
            arr.reverse();

            CHECK_NOEXCEPT(arr.reverse());

            CHECK(arr.at(0u) == 3);
            CHECK(arr.at(1u) == 2);
            CHECK(arr.at(2u) == 1);
        }

        SECTION("Traps")
        {
            phi::array<trap_implicit_conversion, 3> test1 = {};
            test1.reverse();

            phi::array<trap_comma, 3> test2 = {};
            test2.reverse();

            phi::array<trap_call, 3> test3 = {};
            test3.reverse();

            phi::array<trap_self_assign, 3> test4 = {};
            test4.reverse();
        }
    }

    SECTION("to_reversed")
    {
        {
            const T arr      = {1, 2, 3};
            T       reversed = arr.to_reversed();

            CHECK_NOEXCEPT(arr.to_reversed());

            CHECK(arr.at(0u) == 1);
            CHECK(arr.at(1u) == 2);
            CHECK(arr.at(2u) == 3);

            CHECK(reversed.at(0u) == 3);
            CHECK(reversed.at(1u) == 2);
            CHECK(reversed.at(2u) == 1);
        }

        SECTION("Traps")
        {
            phi::array<trap_implicit_conversion, 3> test1 = {};
            (void)test1.to_reversed();

            phi::array<trap_comma, 3> test2 = {};
            (void)test2.to_reversed();

            phi::array<trap_call, 3> test3 = {};
            (void)test3.to_reversed();

            phi::array<trap_self_assign, 3> test4 = {};
            (void)test4.to_reversed();
        }
    }
}

TEST_CASE("array size, ssize, max_size and max_ssize")
{
    {
        using array = phi::array<int, 0u>;

        array arr{};
        CHECK(arr.size() == 0u);
        CHECK(arr.ssize() == 0);
        CHECK(arr.max_size() == 0u);
        CHECK(arr.max_ssize() == 0);
        CHECK(arr.is_empty());

        const array carr{};
        CHECK(carr.size() == 0u);
        CHECK(carr.ssize() == 0);
        CHECK(carr.max_size() == 0u);
        CHECK(carr.max_ssize() == 0);
        CHECK(carr.is_empty());

        PHI_CONSTEXPR array ce_arr{};

        STATIC_REQUIRE(ce_arr.size() == 0u);
        STATIC_REQUIRE(ce_arr.ssize() == 0);
        STATIC_REQUIRE(ce_arr.max_size() == 0u);
        STATIC_REQUIRE(ce_arr.max_ssize() == 0);
        STATIC_REQUIRE(ce_arr.is_empty());
    }

    {
        using array = phi::array<int, 1u>;

        array arr{};
        CHECK(arr.size() == 1u);
        CHECK(arr.ssize() == 1);
        CHECK(arr.max_size() == 1u);
        CHECK(arr.max_ssize() == 1);
        CHECK_FALSE(arr.is_empty());

        const array carr{};
        CHECK(carr.size() == 1u);
        CHECK(carr.ssize() == 1);
        CHECK(carr.max_size() == 1u);
        CHECK(carr.max_ssize() == 1);
        CHECK_FALSE(carr.is_empty());

        PHI_CONSTEXPR array ce_arr{};

        STATIC_REQUIRE(ce_arr.size() == 1u);
        STATIC_REQUIRE(ce_arr.ssize() == 1);
        STATIC_REQUIRE(ce_arr.max_size() == 1u);
        STATIC_REQUIRE(ce_arr.max_ssize() == 1);
        STATIC_REQUIRE_FALSE(ce_arr.is_empty());
    }

    {
        using array = phi::array<int, 2u>;

        array arr{};
        CHECK(arr.size() == 2u);
        CHECK(arr.ssize() == 2);
        CHECK(arr.max_size() == 2u);
        CHECK(arr.max_ssize() == 2);
        CHECK_FALSE(arr.is_empty());

        const array carr{};
        CHECK(carr.size() == 2u);
        CHECK(carr.ssize() == 2);
        CHECK(carr.max_size() == 2u);
        CHECK(carr.max_ssize() == 2);
        CHECK_FALSE(carr.is_empty());

        PHI_CONSTEXPR array ce_arr{};

        STATIC_REQUIRE(ce_arr.size() == 2u);
        STATIC_REQUIRE(ce_arr.ssize() == 2);
        STATIC_REQUIRE(ce_arr.max_size() == 2u);
        STATIC_REQUIRE(ce_arr.max_ssize() == 2);
        STATIC_REQUIRE_FALSE(ce_arr.is_empty());
    }

    {
        using array = phi::array<int, 3u>;

        array arr{};
        CHECK(arr.size() == 3u);
        CHECK(arr.ssize() == 3);
        CHECK(arr.max_size() == 3u);
        CHECK(arr.max_ssize() == 3);
        CHECK_FALSE(arr.is_empty());

        const array carr{};
        CHECK(carr.size() == 3u);
        CHECK(carr.ssize() == 3);
        CHECK(carr.max_size() == 3u);
        CHECK(carr.max_ssize() == 3);
        CHECK_FALSE(carr.is_empty());

        PHI_CONSTEXPR array ce_arr{};

        STATIC_REQUIRE(ce_arr.size() == 3u);
        STATIC_REQUIRE(ce_arr.ssize() == 3);
        STATIC_REQUIRE(ce_arr.max_size() == 3u);
        STATIC_REQUIRE(ce_arr.max_ssize() == 3);
        STATIC_REQUIRE_FALSE(ce_arr.is_empty());
    }
}

TEST_CASE("array fill")
{
    {
        phi::array<int, 3u> arr = {1, 2, 3};
        arr.fill(5);

        CHECK(arr.size() == 3u);
        CHECK(arr[0u] == 5);
        CHECK(arr[1u] == 5);
        CHECK(arr[2u] == 5);
    }

    {
        phi::array<int, 0u> arr;
        arr.fill(5);

        CHECK(arr.size() == 0u);
    }
}

struct NonSwappable
{
    PHI_CONSTEXPR NonSwappable() = default;

    NonSwappable(const NonSwappable&)            = delete;
    NonSwappable& operator=(const NonSwappable&) = delete;
};

struct ThrowSwappable
{
    PHI_CONSTEXPR ThrowSwappable() = default;

    ThrowSwappable(const ThrowSwappable&)
    {}
    ThrowSwappable& operator=(const ThrowSwappable&)
    {
        return *this;
    }
};

TEST_CASE("array swap")
{
    {
        using array = phi::array<int, 3u>;

        STATIC_REQUIRE(phi::is_swappable<array>::value);
        STATIC_REQUIRE(phi::is_nothrow_swappable<array>::value);

        array arr1 = {1, 2, 3};
        array arr2 = {4, 5, 6};

        phi::swap(arr1, arr2);
        CHECK_NOEXCEPT(phi::swap(arr1, arr2));

        CHECK(arr1.size() == 3u);
        CHECK(arr1.at(0u) == 4);
        CHECK(arr1.at(1u) == 5);
        CHECK(arr1.at(2u) == 6);

        CHECK(arr2.size() == 3u);
        CHECK(arr2.at(0u) == 1);
        CHECK(arr2.at(1u) == 2);
        CHECK(arr2.at(2u) == 3);

        arr1.swap(arr2);
        CHECK_NOEXCEPT(arr1.swap(arr2));

        CHECK(arr1.size() == 3u);
        CHECK(arr1.at(0u) == 1);
        CHECK(arr1.at(1u) == 2);
        CHECK(arr1.at(2u) == 3);

        CHECK(arr2.size() == 3u);
        CHECK(arr2.at(0u) == 4);
        CHECK(arr2.at(1u) == 5);
        CHECK(arr2.at(2u) == 6);
    }

    {
        using array = phi::array<int, 0>;

        STATIC_REQUIRE(phi::is_swappable<array>::value);
        STATIC_REQUIRE(phi::is_nothrow_swappable<array>::value);

        array arr1{};
        array arr2{};

        phi::swap(arr1, arr2);
        CHECK_NOEXCEPT(phi::swap(arr1, arr2));

        CHECK(arr1.size() == 0u);
        CHECK(arr2.size() == 0u);

        arr1.swap(arr2);
        CHECK_NOEXCEPT(arr1.swap(arr2));

        CHECK(arr1.size() == 0u);
        CHECK(arr2.size() == 0u);
    }

    {
        using array = phi::array<NonSwappable, 0u>;

        STATIC_REQUIRE(phi::is_not_swappable<NonSwappable>::value);
        STATIC_REQUIRE(phi::is_not_nothrow_swappable<NonSwappable>::value);
        STATIC_REQUIRE(phi::is_swappable<array>::value);
        STATIC_REQUIRE(phi::is_nothrow_swappable<array>::value);

        array arr1{};
        array arr2{};

        phi::swap(arr1, arr2);
        CHECK_NOEXCEPT(phi::swap(arr1, arr2));

        CHECK(arr1.size() == 0u);
        CHECK(arr2.size() == 0u);

        arr1.swap(arr2);
        CHECK_NOEXCEPT(arr1.swap(arr2));

        CHECK(arr1.size() == 0u);
        CHECK(arr2.size() == 0u);
    }

    // TODO: These fail with gcc-8
#if PHI_COMPILER_IS_NOT(GCC) || PHI_COMPILER_IS_ATLEAST(GCC, 9, 0, 0)
    {
        using array = phi::array<NonSwappable, 3u>;

        STATIC_REQUIRE(phi::is_not_swappable<NonSwappable>::value);
        STATIC_REQUIRE(phi::is_not_nothrow_swappable<NonSwappable>::value);
        // TODO: This fails
        //STATIC_REQUIRE(phi::is_not_swappable<array>::value);
        STATIC_REQUIRE(phi::is_not_nothrow_swappable<array>::value);

        array arr1{};
        array arr2{};

        CHECK_NOT_NOEXCEPT(phi::swap(arr1, arr2));
        CHECK_NOT_NOEXCEPT(arr1.swap(arr2));
    }
#endif

    {
        using array = phi::array<ThrowSwappable, 0u>;

        STATIC_REQUIRE(phi::is_swappable<ThrowSwappable>::value);
        STATIC_REQUIRE(phi::is_not_nothrow_swappable<ThrowSwappable>::value);
        STATIC_REQUIRE(phi::is_swappable<array>::value);
        STATIC_REQUIRE(phi::is_nothrow_swappable<array>::value);

        array arr1{};
        array arr2{};

        phi::swap(arr1, arr2);
        CHECK_NOEXCEPT(phi::swap(arr1, arr2));

        CHECK(arr1.size() == 0u);
        CHECK(arr2.size() == 0u);

        arr1.swap(arr2);
        CHECK_NOEXCEPT(arr1.swap(arr2));

        CHECK(arr1.size() == 0u);
        CHECK(arr2.size() == 0u);
    }

    {
        using array = phi::array<ThrowSwappable, 3u>;

        STATIC_REQUIRE(phi::is_swappable<ThrowSwappable>::value);
        STATIC_REQUIRE(phi::is_not_nothrow_swappable<ThrowSwappable>::value);
        STATIC_REQUIRE(phi::is_swappable<array>::value);
        STATIC_REQUIRE(phi::is_not_nothrow_swappable<array>::value);

        array arr1{};
        array arr2{};

        phi::swap(arr1, arr2);
        CHECK_NOT_NOEXCEPT(phi::swap(arr1, arr2));

        CHECK(arr1.size() == 3u);
        CHECK(arr2.size() == 3u);

        arr1.swap(arr2);
        CHECK_NOT_NOEXCEPT(arr1.swap(arr2));

        CHECK(arr1.size() == 3u);
        CHECK(arr2.size() == 3u);
    }
}

#if PHI_HAS_FEATURE_DEDUCTION_GUIDES()
TEST_CASE("array deduction guides")
{
    //  Test the explicit deduction guides
    {
        phi::array arr{1, 2, 3}; // array(T, U...)
        CHECK_SAME_TYPE(decltype(arr), phi::array<int, 3u>);
        CHECK_SAME_TYPE(decltype(arr)::value_type, int);
        STATIC_REQUIRE(arr.size() == 3u);

        CHECK(arr[0u] == 1);
        CHECK(arr[1u] == 2);
        CHECK(arr[2u] == 3);
    }

    {
        const long value = 42;
        phi::array arr{1L, 4L, 9L, value}; // array(T, U...)
        CHECK_SAME_TYPE(decltype(arr), phi::array<long, 4u>);
        CHECK_SAME_TYPE(decltype(arr)::value_type, long);
        STATIC_REQUIRE(arr.size() == 4u);

        CHECK(arr[0u] == 1);
        CHECK(arr[1u] == 4);
        CHECK(arr[2u] == 9);
        CHECK(arr[3u] == value);
    }

    // Test the implicit deduction guides
    {
        phi::array<double, 2> source = {4.0, 5.0};
        phi::array            arr(source); // array(array)
        CHECK_SAME_TYPE(decltype(arr), decltype(source));
        CHECK_SAME_TYPE(decltype(arr), phi::array<double, 2u>);

        CHECK(arr[0u] >= 4.0);
        CHECK(arr[1u] >= 5.0);
    }
}
#endif

#if PHI_HAS_WORKING_IS_AGGREGATE()
template <typename TypeT>
void test_array_is_aggregate()
{
    STATIC_REQUIRE(phi::is_aggregate<phi::array<TypeT, 0u>>::value);
    STATIC_REQUIRE(phi::is_aggregate<phi::array<TypeT, 1u>>::value);
    STATIC_REQUIRE(phi::is_aggregate<phi::array<TypeT, 2u>>::value);
    STATIC_REQUIRE(phi::is_aggregate<phi::array<TypeT, 3u>>::value);
    STATIC_REQUIRE(phi::is_aggregate<phi::array<TypeT, 4u>>::value);
    STATIC_REQUIRE(phi::is_aggregate<phi::array<TypeT, 5u>>::value);
}

TEST_CASE("array is_aggregate")
{
    test_array_is_aggregate<bool>();
    test_array_is_aggregate<char>();
    test_array_is_aggregate<signed char>();
    test_array_is_aggregate<unsigned char>();
    test_array_is_aggregate<short>();
    test_array_is_aggregate<unsigned short>();
    test_array_is_aggregate<int>();
    test_array_is_aggregate<unsigned int>();
    test_array_is_aggregate<long>();
    test_array_is_aggregate<unsigned long>();
    test_array_is_aggregate<long long>();
    test_array_is_aggregate<unsigned long long>();
    test_array_is_aggregate<float>();
    test_array_is_aggregate<double>();
    test_array_is_aggregate<long double>();
    test_array_is_aggregate<char8_t>();
    test_array_is_aggregate<char16_t>();
    test_array_is_aggregate<char32_t>();
    test_array_is_aggregate<wchar_t>();

    test_array_is_aggregate<phi::boolean>();
    test_array_is_aggregate<phi::integer<signed char>>();
    test_array_is_aggregate<phi::integer<unsigned char>>();
    test_array_is_aggregate<phi::integer<short>>();
    test_array_is_aggregate<phi::integer<unsigned short>>();
    test_array_is_aggregate<phi::integer<int>>();
    test_array_is_aggregate<phi::integer<unsigned int>>();
    test_array_is_aggregate<phi::integer<long>>();
    test_array_is_aggregate<phi::integer<unsigned long>>();
    test_array_is_aggregate<phi::integer<long long>>();
    test_array_is_aggregate<phi::integer<unsigned long long>>();
    test_array_is_aggregate<phi::floating_point<float>>();
    test_array_is_aggregate<phi::floating_point<double>>();
    test_array_is_aggregate<phi::floating_point<long double>>();

    test_array_is_aggregate<Empty>();
    test_array_is_aggregate<Trivial>();
    test_array_is_aggregate<NonTrivial>();
}
#endif

template <typename ContainerT>
PHI_EXTENDED_CONSTEXPR void test_contiguous(const ContainerT& container)
{
    for (phi::size_t i = 0; i < container.size(); ++i)
    {
        PHI_RELEASE_ASSERT(*(container.begin() + i) == *(phi::address_of(*container.begin()) + i),
                           "");
    }
}

PHI_EXTENDED_CONSTEXPR bool test_contiguous()
{
    test_contiguous(phi::array<bool, 0>());
    test_contiguous(phi::array<bool, 1>());
    test_contiguous(phi::array<bool, 2>());
    test_contiguous(phi::array<bool, 3>());

    test_contiguous(phi::array<char, 0>());
    test_contiguous(phi::array<char, 1>());
    test_contiguous(phi::array<char, 2>());
    test_contiguous(phi::array<char, 3>());

    return true;
}

TEST_CASE("array contiguous")
{
    CHECK(test_contiguous());

    // TODO: Test don't compile with gcc-8
#if PHI_HAS_FEATURE_EXTENDED_CONSTEXPR() &&                                                        \
        (PHI_COMPILER_IS_NOT(GCC) || PHI_COMPILER_IS_ATLEAST(GCC, 9, 0, 0)) &&                     \
        PHI_SUPPORTS_ADDRESS_OF()
    STATIC_REQUIRE(test_contiguous());
#endif
}

TEST_CASE("array is_empty")
{
    {
        using array = phi::array<int, 3u>;
        array arr{1, 2, 3};

        CHECK_FALSE(arr.is_empty());
        CHECK_NOEXCEPT(arr.is_empty());
    }

    {
        using array = phi::array<int, 3u>;
        const array arr{1, 2, 3};

        CHECK_FALSE(arr.is_empty());
        CHECK_NOEXCEPT(arr.is_empty());
    }

    {
        using array = phi::array<int, 3u>;
        PHI_CONSTEXPR array arr{1, 2, 3};

        STATIC_REQUIRE_FALSE(arr.is_empty());
        CHECK_NOEXCEPT(arr.is_empty());
    }

    {
        using array = phi::array<int, 0u>;
        array arr{};

        CHECK(arr.is_empty());
        CHECK_NOEXCEPT(arr.is_empty());
    }

    {
        using array = phi::array<int, 0u>;
        const array arr{};

        CHECK(arr.is_empty());
        CHECK_NOEXCEPT(arr.is_empty());
    }

    {
        using array = phi::array<int, 0u>;
        PHI_CONSTEXPR array arr{};

        STATIC_REQUIRE(arr.is_empty());
        CHECK_NOEXCEPT(arr.is_empty());
    }
}

TEST_CASE("array front")
{
    {
        using array = phi::array<int, 3u>;
        array arr{1, 2, 3};

        CHECK(arr.front() == 1);
        CHECK_SAME_TYPE(decltype(arr.front()), array::reference);
        CHECK_NOEXCEPT(arr.front());
    }

    {
        using array = phi::array<const int, 3u>;
        array arr{1, 2, 3};

        CHECK(arr.front() == 1);
        CHECK_SAME_TYPE(decltype(arr.front()), array::reference);
        CHECK_NOEXCEPT(arr.front());
    }

    {
        using array = phi::array<int, 3u>;
        const array arr{1, 2, 3};

        CHECK(arr.front() == 1);
        CHECK_SAME_TYPE(decltype(arr.front()), array::const_reference);
        CHECK_NOEXCEPT(arr.front());
    }

    {
        using array = phi::array<const int, 3u>;
        const array arr{1, 2, 3};

        CHECK(arr.front() == 1);
        CHECK_SAME_TYPE(decltype(arr.front()), array::const_reference);
        CHECK_NOEXCEPT(arr.front());
    }

    {
        using array = phi::array<int, 3u>;
        PHI_CONSTEXPR array arr{1, 2, 3};

        CHECK(arr.front() == 1);
        CHECK_SAME_TYPE(decltype(arr.front()), array::const_reference);
        CHECK_NOEXCEPT(arr.front());
    }

    // Zero size
    {
        using array = phi::array<int, 0u>;
        array arr{};

        CHECK_SAME_TYPE(decltype(arr.front()), array::reference);
        CHECK_NOEXCEPT(arr.front());

#if !defined(PHI_CONFIG_COVERAGE_BUILD)
        // always false
        if (arr.size() > 0u)
        {
            (void)arr.front();
        }
#endif
    }

    {
        using array = phi::array<const int, 0u>;
        array arr{};

        CHECK_SAME_TYPE(decltype(arr.front()), array::reference);
        CHECK_NOEXCEPT(arr.front());

#if !defined(PHI_CONFIG_COVERAGE_BUILD)
        // always false
        if (arr.size() > 0u)
        {
            (void)arr.front();
        }
#endif
    }

    {
        using array = phi::array<int, 0u>;
        const array arr{};

        CHECK_SAME_TYPE(decltype(arr.front()), array::const_reference);
        CHECK_NOEXCEPT(arr.front());

#if !defined(PHI_CONFIG_COVERAGE_BUILD)
        // always false
        if (arr.size() > 0u)
        {
            (void)arr.front();
        }
#endif
    }

    {
        using array = phi::array<int, 0u>;
        PHI_CONSTEXPR array arr{};

        CHECK_SAME_TYPE(decltype(arr.front()), array::const_reference);
        CHECK_NOEXCEPT(arr.front());

#if !defined(PHI_CONFIG_COVERAGE_BUILD)
        // always false
        if (arr.size() > 0u)
        {
            (void)arr.front();
        }
#endif
    }
}

TEST_CASE("array back")
{
    {
        using array = phi::array<int, 3u>;
        array arr{1, 2, 3};

        CHECK(arr.back() == 3);
        CHECK_SAME_TYPE(decltype(arr.back()), array::reference);
        CHECK_NOEXCEPT(arr.front());
    }

    {
        using array = phi::array<const int, 3u>;
        array arr{1, 2, 3};

        CHECK(arr.front() == 1);
        CHECK_SAME_TYPE(decltype(arr.front()), array::reference);
        CHECK_NOEXCEPT(arr.front());
    }

    {
        using array = phi::array<int, 3u>;
        const array arr{1, 2, 3};

        CHECK(arr.front() == 1);
        CHECK_SAME_TYPE(decltype(arr.front()), array::const_reference);
        CHECK_NOEXCEPT(arr.front());
    }

    {
        using array = phi::array<const int, 3u>;
        const array arr{1, 2, 3};

        CHECK(arr.front() == 1);
        CHECK_SAME_TYPE(decltype(arr.front()), array::const_reference);
        CHECK_NOEXCEPT(arr.front());
    }

    {
        using array = phi::array<int, 3u>;
        PHI_CONSTEXPR array arr{1, 2, 3};

        CHECK(arr.front() == 1);
        CHECK_SAME_TYPE(decltype(arr.front()), array::const_reference);
        CHECK_NOEXCEPT(arr.front());
    }

    // Zero size
    {
        using array = phi::array<int, 0u>;
        array arr{};

        CHECK_SAME_TYPE(decltype(arr.front()), array::reference);
        CHECK_NOEXCEPT(arr.front());

#if !defined(PHI_CONFIG_COVERAGE_BUILD)
        // always false
        if (arr.size() > 0u)
        {
            (void)arr.front();
        }
#endif
    }

    {
        using array = phi::array<const int, 0u>;
        array arr{};

        CHECK_SAME_TYPE(decltype(arr.front()), array::reference);
        CHECK_NOEXCEPT(arr.front());

#if !defined(PHI_CONFIG_COVERAGE_BUILD)
        // always false
        if (arr.size() > 0u)
        {
            (void)arr.front();
        }
#endif
    }

    {
        using array = phi::array<int, 0u>;
        const array arr{};

        CHECK_SAME_TYPE(decltype(arr.front()), array::const_reference);
        CHECK_NOEXCEPT(arr.front());

#if !defined(PHI_CONFIG_COVERAGE_BUILD)
        // always false
        if (arr.size() > 0u)
        {
            (void)arr.front();
        }
#endif
    }

    {
        using array = phi::array<int, 0u>;
        PHI_CONSTEXPR array arr{};

        CHECK_SAME_TYPE(decltype(arr.front()), array::const_reference);
        CHECK_NOEXCEPT(arr.front());

#if !defined(PHI_CONFIG_COVERAGE_BUILD)
        // always false
        if (arr.size() > 0u)
        {
            (void)arr.front();
        }
#endif
    }
}

TEST_CASE("array max")
{
    {
        using array = phi::array<int, 3u>;
        array arr{1, 2, 3};

        CHECK(arr.max() == 3);
        CHECK_NOEXCEPT(arr.max());
    }

    {
        using array = phi::array<int, 1u>;
        array arr{1};

        CHECK(arr.max() == 1);
        CHECK_NOEXCEPT(arr.max());
    }

    {
        using array = phi::array<int, 3u>;
        const array arr{1, 1, 1};

        CHECK(arr.max() == 1);
        CHECK_NOEXCEPT(arr.max());
    }

    {
        using array = phi::array<int, 3u>;
        PHI_CONSTEXPR array arr{5, 2, 3};

        EXT_STATIC_REQUIRE(arr.max() == 5);
        CHECK_NOEXCEPT(arr.max());
    }
}

TEST_CASE("max_index")
{
    {
        using array = phi::array<int, 3u>;
        array arr{1, 2, 3};

        CHECK(arr.max_index() == &arr[2u]);
        CHECK_SAME_TYPE(decltype(arr.max_index()), array::iterator);
        CHECK_NOEXCEPT(arr.max_index());
    }

    {
        using array = phi::array<int, 3u>;
        array arr{2, 3, 1};

        CHECK(arr.max_index() == &arr[1u]);
        CHECK_SAME_TYPE(decltype(arr.max_index()), array::iterator);
        CHECK_NOEXCEPT(arr.max_index());
    }

    {
        using array = phi::array<int, 3u>;
        array arr{3, 1, 2};

        CHECK(arr.max_index() == &arr.front());
        CHECK_SAME_TYPE(decltype(arr.max_index()), array::iterator);
        CHECK_NOEXCEPT(arr.max_index());
    }

    {
        using array = phi::array<int, 1u>;
        array arr{1};

        CHECK(arr.max_index() == &arr.front());
        CHECK_SAME_TYPE(decltype(arr.max_index()), array::iterator);
        CHECK_NOEXCEPT(arr.max_index());
    }

    {
        using array = phi::array<int, 3u>;
        const array arr{1, 2, 3};

        CHECK(arr.max_index() == &arr[2u]);
        CHECK_SAME_TYPE(decltype(arr.max_index()), array::const_iterator);
        CHECK_NOEXCEPT(arr.max_index());
    }

    {
        using array = phi::array<int, 3u>;
        const array arr{3, 2, 1};

        CHECK(arr.max_index() == &arr.front());
        CHECK_SAME_TYPE(decltype(arr.max_index()), array::const_iterator);
        CHECK_NOEXCEPT(arr.max_index());
    }

    {
        using array = phi::array<int, 3u>;
        const array arr{1, 3, 2};

        CHECK(arr.max_index() == &arr[1u]);
        CHECK_SAME_TYPE(decltype(arr.max_index()), array::const_iterator);
        CHECK_NOEXCEPT(arr.max_index());
    }

    {
        using array = phi::array<int, 3u>;
        PHI_CONSTEXPR array arr{1, 2, 3};

        STATIC_REQUIRE_SAN(arr.max_index() == &arr[2u]);
        CHECK_SAME_TYPE(decltype(arr.max_index()), array::const_iterator);
        CHECK_NOEXCEPT(arr.max_index());
    }
}

TEST_CASE("array min")
{
    {
        using array = phi::array<int, 3u>;
        array arr{1, 2, 3};

        CHECK(arr.min() == 1);
        CHECK_NOEXCEPT(arr.min());
    }

    {
        using array = phi::array<int, 1u>;
        array arr{1};

        CHECK(arr.min() == 1);
        CHECK_NOEXCEPT(arr.min());
    }

    {
        using array = phi::array<int, 3u>;
        const array arr{1, 1, 1};

        CHECK(arr.min() == 1);
        CHECK_NOEXCEPT(arr.min());
    }

    {
        using array = phi::array<int, 3u>;
        PHI_CONSTEXPR array arr{5, 2, 3};

        EXT_STATIC_REQUIRE(arr.min() == 2);
        CHECK_NOEXCEPT(arr.min());
    }
}

TEST_CASE("min_index")
{
    {
        using array = phi::array<int, 3u>;
        array arr{1, 2, 3};

        CHECK(arr.min_index() == &arr.front());
        CHECK_SAME_TYPE(decltype(arr.min_index()), array::iterator);
        CHECK_NOEXCEPT(arr.min_index());
    }

    {
        using array = phi::array<int, 3u>;
        array arr{2, 1, 3};

        CHECK(arr.min_index() == &arr.at(1u));
        CHECK_SAME_TYPE(decltype(arr.min_index()), array::iterator);
        CHECK_NOEXCEPT(arr.min_index());
    }

    {
        using array = phi::array<int, 3u>;
        array arr{2, 3, 1};

        CHECK(arr.min_index() == &arr.at(2u));
        CHECK_SAME_TYPE(decltype(arr.min_index()), array::iterator);
        CHECK_NOEXCEPT(arr.min_index());
    }

    {
        using array = phi::array<int, 1u>;
        array arr{1};

        CHECK(arr.min_index() == &arr.front());
        CHECK_SAME_TYPE(decltype(arr.min_index()), array::iterator);
        CHECK_NOEXCEPT(arr.min_index());
    }

    {
        using array = phi::array<int, 3u>;
        const array arr{1, 2, 3};

        CHECK(arr.min_index() == &arr.front());
        CHECK_SAME_TYPE(decltype(arr.min_index()), array::const_iterator);
        CHECK_NOEXCEPT(arr.min_index());
    }

    {
        using array = phi::array<int, 3u>;
        const array arr{2, 1, 3};

        CHECK(arr.min_index() == &arr.at(1u));
        CHECK_SAME_TYPE(decltype(arr.min_index()), array::const_iterator);
        CHECK_NOEXCEPT(arr.min_index());
    }

    {
        using array = phi::array<int, 3u>;
        const array arr{2, 3, 1};

        CHECK(arr.min_index() == &arr.at(2u));
        CHECK_SAME_TYPE(decltype(arr.min_index()), array::const_iterator);
        CHECK_NOEXCEPT(arr.min_index());
    }

    {
        using array = phi::array<int, 3u>;
        PHI_CONSTEXPR array arr{1, 2, 3};

        STATIC_REQUIRE_SAN(arr.min_index() == &arr.front());
        CHECK_SAME_TYPE(decltype(arr.min_index()), array::const_iterator);
        CHECK_NOEXCEPT(arr.min_index());
    }
}

static PHI_CONSTEXPR bool eq0(const int& value) PHI_NOEXCEPT
{
    return value == 0;
}

static PHI_CONSTEXPR bool eq1(const int& value) PHI_NOEXCEPT
{
    return value == 1;
}

static PHI_CONSTEXPR bool eq2(const int& value) PHI_NOEXCEPT
{
    return value == 2;
}

static PHI_CONSTEXPR bool eq3(const int& value) PHI_NOEXCEPT
{
    return value == 3;
}

static PHI_CONSTEXPR bool ne0(const int& value) PHI_NOEXCEPT
{
    return value != 0;
}

static PHI_CONSTEXPR bool ne1(const int& value) PHI_NOEXCEPT
{
    return value != 1;
}

static PHI_CONSTEXPR bool ne2(const int& value) PHI_NOEXCEPT
{
    return value != 2;
}

static PHI_CONSTEXPR bool ne3(const int& value) PHI_NOEXCEPT
{
    return value != 3;
}

static PHI_CONSTEXPR bool even(const int& value) PHI_NOEXCEPT
{
    return value % 2 == 0;
}

static PHI_CONSTEXPR bool odd(const int& value) PHI_NOEXCEPT
{
    return value % 2 == 1;
}

static PHI_CONSTEXPR bool always_true(const int& /*value*/) PHI_NOEXCEPT
{
    return true;
}

static PHI_CONSTEXPR bool always_false(const int& /*value*/) PHI_NOEXCEPT
{
    return false;
}

static bool always_throw(const int& /*value*/)
{
    throw "";
}

#if PHI_HAS_FEATURE_LAMBDA()

static PHI_CONSTEXPR_AND_CONST auto lambda_eq0 = [](const int& value)
                                                         PHI_NOEXCEPT { return value == 0; };
static PHI_CONSTEXPR_AND_CONST auto lambda_eq1 = [](const int& value)
                                                         PHI_NOEXCEPT { return value == 1; };
static PHI_CONSTEXPR_AND_CONST auto lambda_eq2 = [](const int& value)
                                                         PHI_NOEXCEPT { return value == 2; };
static PHI_CONSTEXPR_AND_CONST auto lambda_eq3 = [](const int& value)
                                                         PHI_NOEXCEPT { return value == 3; };
static PHI_CONSTEXPR_AND_CONST auto lambda_ne0 = [](const int& value)
                                                         PHI_NOEXCEPT { return value != 0; };
static PHI_CONSTEXPR_AND_CONST auto lambda_ne1 = [](const int& value)
                                                         PHI_NOEXCEPT { return value != 1; };
static PHI_CONSTEXPR_AND_CONST auto lambda_ne2 = [](const int& value)
                                                         PHI_NOEXCEPT { return value != 2; };
static PHI_CONSTEXPR_AND_CONST auto lambda_ne3 = [](const int& value)
                                                         PHI_NOEXCEPT { return value != 3; };
static PHI_CONSTEXPR_AND_CONST auto lambda_even = [](const int& value)
                                                          PHI_NOEXCEPT { return value % 2 == 0; };
static PHI_CONSTEXPR_AND_CONST auto lambda_odd = [](const int& value)
                                                         PHI_NOEXCEPT { return value % 2 == 1; };
static PHI_CONSTEXPR_AND_CONST auto lambda_true = [](const int& /*value*/)
                                                          PHI_NOEXCEPT { return true; };
static PHI_CONSTEXPR_AND_CONST auto lambda_false = [](const int& /*value*/)
                                                           PHI_NOEXCEPT { return false; };
static PHI_CONSTEXPR_AND_CONST auto lambda_throw = [](const int& /*value*/) -> bool { throw ""; };

#endif

TEST_CASE("array find")
{
    {
        using array = phi::array<int, 3u>;
        array arr{1, 2, 3};

        CHECK(arr.find(1) == &arr.front());
        CHECK(arr.find(2) == &arr.at(1u));
        CHECK(arr.find(3) == &arr.back());
        CHECK(arr.find(0) == arr.end());
        CHECK(arr.find(4) == arr.end());
        CHECK_SAME_TYPE(decltype(arr.find(1)), array::iterator);
        CHECK_NOEXCEPT(arr.find(1));
    }

    {
        using array = phi::array<int, 0u>;
        array arr;

        CHECK(arr.find(0) == arr.end());
        CHECK(arr.find(1) == arr.end());
        CHECK(arr.find(2) == arr.end());
        CHECK(arr.find(3) == arr.end());
        CHECK_SAME_TYPE(decltype(arr.find(1)), array::iterator);
        CHECK_NOEXCEPT(arr.find(1));
    }

    {
        using array = phi::array<int, 3u>;
        const array arr{1, 2, 3};

        CHECK(arr.find(1) == &arr.front());
        CHECK(arr.find(2) == &arr.at(1u));
        CHECK(arr.find(3) == &arr.back());
        CHECK(arr.find(0) == arr.end());
        CHECK(arr.find(4) == arr.end());
        CHECK_SAME_TYPE(decltype(arr.find(1)), array::const_iterator);
#if PHI_HAS_FEATURE_NOEXCEPT_CLASS_EXPR()
        CHECK_NOEXCEPT(arr.find(1));
#endif
    }

    {
        using array = phi::array<int, 0u>;
        const array arr;

        CHECK(arr.find(0) == arr.end());
        CHECK(arr.find(1) == arr.end());
        CHECK(arr.find(2) == arr.end());
        CHECK(arr.find(3) == arr.end());
        CHECK_SAME_TYPE(decltype(arr.find(1)), array::const_iterator);
        CHECK_NOEXCEPT(arr.find(1));
    }

    {
        using array = phi::array<int, 3u>;
        PHI_CONSTEXPR array arr{1, 2, 3};

        EXT_STATIC_REQUIRE(arr.find(1) == &arr.front());
        EXT_STATIC_REQUIRE(arr.find(2) == &arr.at(1u));
        EXT_STATIC_REQUIRE(arr.find(3) == &arr.back());
        EXT_STATIC_REQUIRE(arr.find(0) == arr.end());
        EXT_STATIC_REQUIRE(arr.find(4) == arr.end());
        CHECK_SAME_TYPE(decltype(arr.find(1)), array::const_iterator);
        CHECK_NOEXCEPT(arr.find(1));
    }

    {
        using array = phi::array<int, 0u>;
        PHI_CONSTEXPR array arr;

        STATIC_REQUIRE(arr.find(0) == arr.end());
        STATIC_REQUIRE(arr.find(1) == arr.end());
        STATIC_REQUIRE(arr.find(2) == arr.end());
        STATIC_REQUIRE(arr.find(3) == arr.end());
        CHECK_SAME_TYPE(decltype(arr.find(1)), array::const_iterator);
        CHECK_NOEXCEPT(arr.find(1));
    }
}

TEST_CASE("array find_if")
{
    {
        using array = phi::array<int, 3u>;
        array arr{1, 2, 3};

        CHECK(arr.find_if(eq0) == arr.end());
        CHECK(arr.find_if(eq1) == &arr.at(0u));
        CHECK(arr.find_if(eq2) == &arr.at(1u));
        CHECK(arr.find_if(eq3) == &arr.at(2u));
        CHECK(arr.find_if(ne0) == &arr.at(0u));
        CHECK(arr.find_if(ne1) == &arr.at(1u));
        CHECK(arr.find_if(ne2) == &arr.at(0u));
        CHECK(arr.find_if(ne3) == &arr.at(0u));
        CHECK(arr.find_if(even) == &arr.at(1u));
        CHECK(arr.find_if(odd) == &arr.at(0u));
        CHECK(arr.find_if(always_false) == arr.end());
        CHECK(arr.find_if(always_true) == &arr.at(0u));
        CHECK_SAME_TYPE(decltype(arr.find_if(always_false)), array::iterator);
        CHECK_NOT_NOEXCEPT(arr.find_if(always_throw));
        CHECK_NOEXCEPT(arr.find_if(always_false));

#if PHI_HAS_FEATURE_LAMBDA()
        CHECK(arr.find_if(lambda_eq0) == arr.end());
        CHECK(arr.find_if(lambda_eq1) == &arr.at(0u));
        CHECK(arr.find_if(lambda_eq2) == &arr.at(1u));
        CHECK(arr.find_if(lambda_eq3) == &arr.at(2u));
        CHECK(arr.find_if(lambda_ne0) == &arr.at(0u));
        CHECK(arr.find_if(lambda_ne1) == &arr.at(1u));
        CHECK(arr.find_if(lambda_ne2) == &arr.at(0u));
        CHECK(arr.find_if(lambda_ne3) == &arr.at(0u));
        CHECK(arr.find_if(lambda_even) == &arr.at(1u));
        CHECK(arr.find_if(lambda_odd) == &arr.at(0u));
        CHECK(arr.find_if(lambda_false) == arr.end());
        CHECK(arr.find_if(lambda_true) == &arr.at(0u));
        CHECK_SAME_TYPE(decltype(arr.find_if(lambda_false)), array::iterator);
        CHECK_NOT_NOEXCEPT(arr.find_if(lambda_throw));
#    if PHI_HAS_FEATURE_NOEXCEPT_CLASS_EXPR()
        CHECK_NOEXCEPT(arr.find_if(lambda_false));
#    endif
#endif
    }

    {
        using array = phi::array<int, 0u>;
        array arr;

        CHECK(arr.find_if(eq0) == arr.end());
        CHECK(arr.find_if(eq1) == arr.end());
        CHECK(arr.find_if(eq2) == arr.end());
        CHECK(arr.find_if(eq3) == arr.end());
        CHECK(arr.find_if(ne0) == arr.end());
        CHECK(arr.find_if(ne1) == arr.end());
        CHECK(arr.find_if(ne2) == arr.end());
        CHECK(arr.find_if(ne3) == arr.end());
        CHECK(arr.find_if(even) == arr.end());
        CHECK(arr.find_if(odd) == arr.end());
        CHECK(arr.find_if(always_false) == arr.end());
        CHECK(arr.find_if(always_true) == arr.end());
        CHECK_SAME_TYPE(decltype(arr.find_if(always_false)), array::iterator);
        CHECK_NOEXCEPT(arr.find_if(always_throw));
        CHECK_NOEXCEPT(arr.find_if(always_false));

#if PHI_HAS_FEATURE_LAMBDA()
        CHECK(arr.find_if(lambda_eq0) == arr.end());
        CHECK(arr.find_if(lambda_eq1) == arr.end());
        CHECK(arr.find_if(lambda_eq2) == arr.end());
        CHECK(arr.find_if(lambda_eq3) == arr.end());
        CHECK(arr.find_if(lambda_ne0) == arr.end());
        CHECK(arr.find_if(lambda_ne1) == arr.end());
        CHECK(arr.find_if(lambda_ne2) == arr.end());
        CHECK(arr.find_if(lambda_ne3) == arr.end());
        CHECK(arr.find_if(lambda_even) == arr.end());
        CHECK(arr.find_if(lambda_odd) == arr.end());
        CHECK(arr.find_if(lambda_false) == arr.end());
        CHECK(arr.find_if(lambda_true) == arr.end());
        CHECK_SAME_TYPE(decltype(arr.find_if(lambda_false)), array::iterator);
        CHECK_NOEXCEPT(arr.find_if(lambda_throw));
        CHECK_NOEXCEPT(arr.find_if(lambda_false));
#endif
    }

    {
        using array = phi::array<int, 3u>;
        const array arr{1, 2, 3};

        CHECK(arr.find_if(eq0) == arr.end());
        CHECK(arr.find_if(eq1) == &arr.at(0u));
        CHECK(arr.find_if(eq2) == &arr.at(1u));
        CHECK(arr.find_if(eq3) == &arr.at(2u));
        CHECK(arr.find_if(ne0) == &arr.at(0u));
        CHECK(arr.find_if(ne1) == &arr.at(1u));
        CHECK(arr.find_if(ne2) == &arr.at(0u));
        CHECK(arr.find_if(ne3) == &arr.at(0u));
        CHECK(arr.find_if(even) == &arr.at(1u));
        CHECK(arr.find_if(odd) == &arr.at(0u));
        CHECK(arr.find_if(always_false) == arr.end());
        CHECK(arr.find_if(always_true) == &arr.at(0u));
        CHECK_SAME_TYPE(decltype(arr.find_if(always_false)), array::const_iterator);
        CHECK_NOT_NOEXCEPT(arr.find_if(always_throw));
        CHECK_NOEXCEPT(arr.find_if(always_false));

#if PHI_HAS_FEATURE_LAMBDA()
        CHECK(arr.find_if(lambda_eq0) == arr.end());
        CHECK(arr.find_if(lambda_eq1) == &arr.at(0u));
        CHECK(arr.find_if(lambda_eq2) == &arr.at(1u));
        CHECK(arr.find_if(lambda_eq3) == &arr.at(2u));
        CHECK(arr.find_if(lambda_ne0) == &arr.at(0u));
        CHECK(arr.find_if(lambda_ne1) == &arr.at(1u));
        CHECK(arr.find_if(lambda_ne2) == &arr.at(0u));
        CHECK(arr.find_if(lambda_ne3) == &arr.at(0u));
        CHECK(arr.find_if(lambda_even) == &arr.at(1u));
        CHECK(arr.find_if(lambda_odd) == &arr.at(0u));
        CHECK(arr.find_if(lambda_false) == arr.end());
        CHECK(arr.find_if(lambda_true) == &arr.at(0u));
        CHECK_SAME_TYPE(decltype(arr.find_if(lambda_false)), array::const_iterator);
        CHECK_NOT_NOEXCEPT(arr.find_if(lambda_throw));
#    if PHI_HAS_FEATURE_NOEXCEPT_CLASS_EXPR()
        CHECK_NOEXCEPT(arr.find_if(lambda_false));
#    endif
#endif
    }

    {
        using array = phi::array<int, 0u>;
        const array arr;

        CHECK(arr.find_if(eq0) == arr.end());
        CHECK(arr.find_if(eq1) == arr.end());
        CHECK(arr.find_if(eq2) == arr.end());
        CHECK(arr.find_if(eq3) == arr.end());
        CHECK(arr.find_if(ne0) == arr.end());
        CHECK(arr.find_if(ne1) == arr.end());
        CHECK(arr.find_if(ne2) == arr.end());
        CHECK(arr.find_if(ne3) == arr.end());
        CHECK(arr.find_if(even) == arr.end());
        CHECK(arr.find_if(odd) == arr.end());
        CHECK(arr.find_if(always_false) == arr.end());
        CHECK(arr.find_if(always_true) == arr.end());
        CHECK_SAME_TYPE(decltype(arr.find_if(always_false)), array::const_iterator);
        CHECK_NOEXCEPT(arr.find_if(always_throw));
        CHECK_NOEXCEPT(arr.find_if(always_false));

#if PHI_HAS_FEATURE_LAMBDA()
        CHECK(arr.find_if(lambda_eq0) == arr.end());
        CHECK(arr.find_if(lambda_eq1) == arr.end());
        CHECK(arr.find_if(lambda_eq2) == arr.end());
        CHECK(arr.find_if(lambda_eq3) == arr.end());
        CHECK(arr.find_if(lambda_ne0) == arr.end());
        CHECK(arr.find_if(lambda_ne1) == arr.end());
        CHECK(arr.find_if(lambda_ne2) == arr.end());
        CHECK(arr.find_if(lambda_ne3) == arr.end());
        CHECK(arr.find_if(lambda_even) == arr.end());
        CHECK(arr.find_if(lambda_odd) == arr.end());
        CHECK(arr.find_if(lambda_false) == arr.end());
        CHECK(arr.find_if(lambda_true) == arr.end());
        CHECK_SAME_TYPE(decltype(arr.find_if(lambda_false)), array::const_iterator);
        CHECK_NOEXCEPT(arr.find_if(lambda_throw));
        CHECK_NOEXCEPT(arr.find_if(lambda_false));
#endif
    }

    {
        using array = phi::array<int, 3u>;
        PHI_CONSTEXPR array arr{1, 2, 3};

        EXT_STATIC_REQUIRE(arr.find_if(eq0) == arr.end());
        EXT_STATIC_REQUIRE(arr.find_if(eq1) == &arr.at(0u));
        EXT_STATIC_REQUIRE(arr.find_if(eq2) == &arr.at(1u));
        EXT_STATIC_REQUIRE(arr.find_if(eq3) == &arr.at(2u));
        EXT_STATIC_REQUIRE(arr.find_if(ne0) == &arr.at(0u));
        EXT_STATIC_REQUIRE(arr.find_if(ne1) == &arr.at(1u));
        EXT_STATIC_REQUIRE(arr.find_if(ne2) == &arr.at(0u));
        EXT_STATIC_REQUIRE(arr.find_if(ne3) == &arr.at(0u));
        EXT_STATIC_REQUIRE(arr.find_if(even) == &arr.at(1u));
        EXT_STATIC_REQUIRE(arr.find_if(odd) == &arr.at(0u));
        EXT_STATIC_REQUIRE(arr.find_if(always_false) == arr.end());
        CHECK_SAME_TYPE(decltype(arr.find_if(always_false)), array::const_iterator);
        CHECK_NOT_NOEXCEPT(arr.find_if(always_throw));
#if PHI_HAS_FEATURE_NOEXCEPT_CLASS_EXPR()
        CHECK_NOEXCEPT(arr.find_if(always_false));
#endif

#if PHI_HAS_FEATURE_LAMBDA() && PHI_HAS_FEATURE_CONSTEXPR_LAMBDA()
        EXT_STATIC_REQUIRE(arr.find_if(lambda_eq0) == arr.end());
        EXT_STATIC_REQUIRE(arr.find_if(lambda_eq1) == &arr.at(0u));
        EXT_STATIC_REQUIRE(arr.find_if(lambda_eq2) == &arr.at(1u));
        EXT_STATIC_REQUIRE(arr.find_if(lambda_eq3) == &arr.at(2u));
        EXT_STATIC_REQUIRE(arr.find_if(lambda_ne0) == &arr.at(0u));
        EXT_STATIC_REQUIRE(arr.find_if(lambda_ne1) == &arr.at(1u));
        EXT_STATIC_REQUIRE(arr.find_if(lambda_ne2) == &arr.at(0u));
        EXT_STATIC_REQUIRE(arr.find_if(lambda_ne3) == &arr.at(0u));
        EXT_STATIC_REQUIRE(arr.find_if(lambda_even) == &arr.at(1u));
        EXT_STATIC_REQUIRE(arr.find_if(lambda_odd) == &arr.at(0u));
        EXT_STATIC_REQUIRE(arr.find_if(lambda_false) == arr.end());
        CHECK_SAME_TYPE(decltype(arr.find_if(lambda_false)), array::const_iterator);
        CHECK_NOT_NOEXCEPT(arr.find_if(lambda_throw));
#    if PHI_HAS_FEATURE_NOEXCEPT_CLASS_EXPR()
        CHECK_NOEXCEPT(arr.find_if(lambda_false));
#    endif
#endif
    }

    {
        using array = phi::array<int, 0u>;
        PHI_CONSTEXPR array arr;

        STATIC_REQUIRE(arr.find_if(eq1) == arr.end());
        STATIC_REQUIRE(arr.find_if(eq2) == arr.end());
        STATIC_REQUIRE(arr.find_if(even) == arr.end());
        STATIC_REQUIRE(arr.find_if(always_false) == arr.end());
        CHECK_SAME_TYPE(decltype(arr.find_if(always_false)), array::const_iterator);
        CHECK_NOEXCEPT(arr.find_if(always_throw));
        CHECK_NOEXCEPT(arr.find_if(always_false));

#if PHI_HAS_FEATURE_LAMBDA() && PHI_HAS_FEATURE_CONSTEXPR_LAMBDA()
        STATIC_REQUIRE(arr.find_if(lambda_eq1) == arr.end());
        STATIC_REQUIRE(arr.find_if(lambda_eq2) == arr.end());
        STATIC_REQUIRE(arr.find_if(lambda_even) == arr.end());
        STATIC_REQUIRE(arr.find_if(lambda_false) == arr.end());
        CHECK_SAME_TYPE(decltype(arr.find_if(lambda_false)), array::const_iterator);
        CHECK_NOEXCEPT(arr.find_if(lambda_throw));
        CHECK_NOEXCEPT(arr.find_if(lambda_false));
#endif
    }
}

TEST_CASE("array find_if_not")
{
    {
        using array = phi::array<int, 3u>;
        array arr{1, 2, 3};

        CHECK(arr.find_if_not(eq0) == &arr.at(0u));
        CHECK(arr.find_if_not(eq1) == &arr.at(1u));
        CHECK(arr.find_if_not(eq2) == &arr.at(0u));
        CHECK(arr.find_if_not(eq3) == &arr.at(0u));
        CHECK(arr.find_if_not(ne0) == arr.end());
        CHECK(arr.find_if_not(ne1) == &arr.at(0u));
        CHECK(arr.find_if_not(ne2) == &arr.at(1u));
        CHECK(arr.find_if_not(ne3) == &arr.at(2u));
        CHECK(arr.find_if_not(even) == &arr.at(0u));
        CHECK(arr.find_if_not(odd) == &arr.at(1u));
        CHECK(arr.find_if_not(always_false) == &arr.at(0u));
        CHECK(arr.find_if_not(always_true) == arr.end());
        CHECK_SAME_TYPE(decltype(arr.find_if_not(always_false)), array::iterator);
        CHECK_NOT_NOEXCEPT(arr.find_if_not(always_throw));
#if PHI_HAS_FEATURE_NOEXCEPT_CLASS_EXPR()
        CHECK_NOEXCEPT(arr.find_if_not(always_false));
#endif

#if PHI_HAS_FEATURE_LAMBDA()
        CHECK(arr.find_if_not(lambda_eq0) == &arr.at(0u));
        CHECK(arr.find_if_not(lambda_eq1) == &arr.at(1u));
        CHECK(arr.find_if_not(lambda_eq2) == &arr.at(0u));
        CHECK(arr.find_if_not(lambda_eq3) == &arr.at(0u));
        CHECK(arr.find_if_not(lambda_ne0) == arr.end());
        CHECK(arr.find_if_not(lambda_ne1) == &arr.at(0u));
        CHECK(arr.find_if_not(lambda_ne2) == &arr.at(1u));
        CHECK(arr.find_if_not(lambda_ne3) == &arr.at(2u));
        CHECK(arr.find_if_not(lambda_even) == &arr.at(0u));
        CHECK(arr.find_if_not(lambda_odd) == &arr.at(1u));
        CHECK(arr.find_if_not(lambda_false) == &arr.at(0u));
        CHECK(arr.find_if_not(lambda_true) == arr.end());
        CHECK_SAME_TYPE(decltype(arr.find_if_not(lambda_false)), array::iterator);
        CHECK_NOT_NOEXCEPT(arr.find_if_not(lambda_throw));
#    if PHI_HAS_FEATURE_NOEXCEPT_CLASS_EXPR()
        CHECK_NOEXCEPT(arr.find_if_not(lambda_false));
#    endif
#endif
    }

    {
        using array = phi::array<int, 0u>;
        array arr;

        CHECK(arr.find_if_not(eq1) == arr.end());
        CHECK(arr.find_if_not(eq2) == arr.end());
        CHECK(arr.find_if_not(even) == arr.end());
        CHECK(arr.find_if_not(always_false) == arr.end());
        CHECK_SAME_TYPE(decltype(arr.find_if_not(always_false)), array::iterator);
        CHECK_NOEXCEPT(arr.find_if_not(always_throw));
        CHECK_NOEXCEPT(arr.find_if_not(always_false));

#if PHI_HAS_FEATURE_LAMBDA()
        CHECK(arr.find_if_not(lambda_eq1) == arr.end());
        CHECK(arr.find_if_not(lambda_eq2) == arr.end());
        CHECK(arr.find_if_not(lambda_even) == arr.end());
        CHECK(arr.find_if_not(lambda_false) == arr.end());
        CHECK_SAME_TYPE(decltype(arr.find_if_not(lambda_false)), array::iterator);
        CHECK_NOEXCEPT(arr.find_if_not(lambda_throw));
        CHECK_NOEXCEPT(arr.find_if_not(lambda_false));
#endif
    }

    {
        using array = phi::array<int, 3u>;
        const array arr{1, 2, 3};

        CHECK(arr.find_if_not(eq0) == &arr.at(0u));
        CHECK(arr.find_if_not(eq1) == &arr.at(1u));
        CHECK(arr.find_if_not(eq2) == &arr.at(0u));
        CHECK(arr.find_if_not(eq3) == &arr.at(0u));
        CHECK(arr.find_if_not(ne0) == arr.end());
        CHECK(arr.find_if_not(ne1) == &arr.at(0u));
        CHECK(arr.find_if_not(ne2) == &arr.at(1u));
        CHECK(arr.find_if_not(ne3) == &arr.at(2u));
        CHECK(arr.find_if_not(even) == &arr.at(0u));
        CHECK(arr.find_if_not(odd) == &arr.at(1u));
        CHECK(arr.find_if_not(always_false) == &arr.at(0u));
        CHECK(arr.find_if_not(always_true) == arr.end());
        CHECK_SAME_TYPE(decltype(arr.find_if_not(always_false)), array::const_iterator);
        CHECK_NOT_NOEXCEPT(arr.find_if_not(always_throw));
#if PHI_HAS_FEATURE_NOEXCEPT_CLASS_EXPR()
        CHECK_NOEXCEPT(arr.find_if_not(always_false));
#endif

#if PHI_HAS_FEATURE_LAMBDA()
        CHECK(arr.find_if_not(lambda_eq0) == &arr.at(0u));
        CHECK(arr.find_if_not(lambda_eq1) == &arr.at(1u));
        CHECK(arr.find_if_not(lambda_eq2) == &arr.at(0u));
        CHECK(arr.find_if_not(lambda_eq3) == &arr.at(0u));
        CHECK(arr.find_if_not(lambda_ne0) == arr.end());
        CHECK(arr.find_if_not(lambda_ne1) == &arr.at(0u));
        CHECK(arr.find_if_not(lambda_ne2) == &arr.at(1u));
        CHECK(arr.find_if_not(lambda_ne3) == &arr.at(2u));
        CHECK(arr.find_if_not(lambda_even) == &arr.at(0u));
        CHECK(arr.find_if_not(lambda_odd) == &arr.at(1u));
        CHECK(arr.find_if_not(lambda_false) == &arr.at(0u));
        CHECK(arr.find_if_not(lambda_true) == arr.end());
        CHECK_SAME_TYPE(decltype(arr.find_if_not(lambda_false)), array::const_iterator);
        CHECK_NOT_NOEXCEPT(arr.find_if_not(lambda_throw));
#    if PHI_HAS_FEATURE_NOEXCEPT_CLASS_EXPR()
        CHECK_NOEXCEPT(arr.find_if_not(lambda_false));
#    endif
#endif
    }

    {
        using array = phi::array<int, 0u>;
        const array arr;

        CHECK(arr.find_if_not(eq1) == arr.end());
        CHECK(arr.find_if_not(eq2) == arr.end());
        CHECK(arr.find_if_not(even) == arr.end());
        CHECK(arr.find_if_not(always_false) == arr.end());
        CHECK_SAME_TYPE(decltype(arr.find_if_not(always_false)), array::const_iterator);
        CHECK_NOEXCEPT(arr.find_if_not(always_throw));
        CHECK_NOEXCEPT(arr.find_if_not(always_false));

#if PHI_HAS_FEATURE_LAMBDA()
        CHECK(arr.find_if_not(lambda_eq1) == arr.end());
        CHECK(arr.find_if_not(lambda_eq2) == arr.end());
        CHECK(arr.find_if_not(lambda_even) == arr.end());
        CHECK(arr.find_if_not(lambda_false) == arr.end());
        CHECK_SAME_TYPE(decltype(arr.find_if_not(lambda_false)), array::const_iterator);
        CHECK_NOEXCEPT(arr.find_if_not(lambda_throw));
        CHECK_NOEXCEPT(arr.find_if_not(lambda_false));
#endif
    }

    {
        using array = phi::array<int, 3u>;
        PHI_CONSTEXPR array arr{1, 2, 3};

        EXT_STATIC_REQUIRE(arr.find_if_not(eq0) == &arr.at(0u));
        EXT_STATIC_REQUIRE(arr.find_if_not(eq1) == &arr.at(1u));
        EXT_STATIC_REQUIRE(arr.find_if_not(eq2) == &arr.at(0u));
        EXT_STATIC_REQUIRE(arr.find_if_not(eq3) == &arr.at(0u));
        EXT_STATIC_REQUIRE(arr.find_if_not(ne0) == arr.end());
        EXT_STATIC_REQUIRE(arr.find_if_not(ne1) == &arr.at(0u));
        EXT_STATIC_REQUIRE(arr.find_if_not(ne2) == &arr.at(1u));
        EXT_STATIC_REQUIRE(arr.find_if_not(ne3) == &arr.at(2u));
        EXT_STATIC_REQUIRE(arr.find_if_not(even) == &arr.at(0u));
        EXT_STATIC_REQUIRE(arr.find_if_not(odd) == &arr.at(1u));
        EXT_STATIC_REQUIRE(arr.find_if_not(always_false) == &arr.at(0u));
        EXT_STATIC_REQUIRE(arr.find_if_not(always_true) == arr.end());
        CHECK_SAME_TYPE(decltype(arr.find_if_not(always_false)), array::const_iterator);
        CHECK_NOT_NOEXCEPT(arr.find_if_not(always_throw));
#if PHI_HAS_FEATURE_NOEXCEPT_CLASS_EXPR()
        CHECK_NOEXCEPT(arr.find_if_not(always_false));
#endif

#if PHI_HAS_FEATURE_LAMBDA() && PHI_HAS_FEATURE_CONSTEXPR_LAMBDA()
        EXT_STATIC_REQUIRE(arr.find_if_not(lambda_eq0) == &arr.at(0u));
        EXT_STATIC_REQUIRE(arr.find_if_not(lambda_eq1) == &arr.at(1u));
        EXT_STATIC_REQUIRE(arr.find_if_not(lambda_eq2) == &arr.at(0u));
        EXT_STATIC_REQUIRE(arr.find_if_not(lambda_eq3) == &arr.at(0u));
        EXT_STATIC_REQUIRE(arr.find_if_not(lambda_ne0) == arr.end());
        EXT_STATIC_REQUIRE(arr.find_if_not(lambda_ne1) == &arr.at(0u));
        EXT_STATIC_REQUIRE(arr.find_if_not(lambda_ne2) == &arr.at(1u));
        EXT_STATIC_REQUIRE(arr.find_if_not(lambda_ne3) == &arr.at(2u));
        EXT_STATIC_REQUIRE(arr.find_if_not(lambda_even) == &arr.at(0u));
        EXT_STATIC_REQUIRE(arr.find_if_not(lambda_odd) == &arr.at(1u));
        EXT_STATIC_REQUIRE(arr.find_if_not(lambda_false) == &arr.at(0u));
        EXT_STATIC_REQUIRE(arr.find_if_not(lambda_true) == arr.end());
        CHECK_SAME_TYPE(decltype(arr.find_if_not(lambda_false)), array::const_iterator);
        CHECK_NOT_NOEXCEPT(arr.find_if_not(lambda_throw));
#    if PHI_HAS_FEATURE_NOEXCEPT_CLASS_EXPR()
        CHECK_NOEXCEPT(arr.find_if_not(lambda_false));
#    endif
#endif
    }

    {
        using array = phi::array<int, 0u>;
        PHI_CONSTEXPR array arr;

        STATIC_REQUIRE(arr.find_if_not(eq1) == arr.end());
        STATIC_REQUIRE(arr.find_if_not(eq2) == arr.end());
        STATIC_REQUIRE(arr.find_if_not(even) == arr.end());
        STATIC_REQUIRE(arr.find_if_not(always_false) == arr.end());
        CHECK_SAME_TYPE(decltype(arr.find_if_not(always_false)), array::const_iterator);
        CHECK_NOEXCEPT(arr.find_if_not(always_throw));
        CHECK_NOEXCEPT(arr.find_if_not(always_false));

#if PHI_HAS_FEATURE_LAMBDA() && PHI_HAS_FEATURE_CONSTEXPR_LAMBDA()
        STATIC_REQUIRE(arr.find_if_not(lambda_eq1) == arr.end());
        STATIC_REQUIRE(arr.find_if_not(lambda_eq2) == arr.end());
        STATIC_REQUIRE(arr.find_if_not(lambda_even) == arr.end());
        STATIC_REQUIRE(arr.find_if_not(lambda_false) == arr.end());
        CHECK_SAME_TYPE(decltype(arr.find_if_not(lambda_false)), array::const_iterator);
        CHECK_NOEXCEPT(arr.find_if_not(lambda_throw));
        CHECK_NOEXCEPT(arr.find_if_not(lambda_false));
#endif
    }
}

TEST_CASE("array find_last")
{
    {
        using array = phi::array<int, 4u>;
        array arr{1, 2, 3, 1};

        CHECK(arr.find_last(1) == &arr.back());
        CHECK(arr.find_last(2) == &arr.at(1u));
        CHECK(arr.find_last(3) == &arr.at(2u));
        CHECK(arr.find_last(0) == arr.end());
        CHECK(arr.find_last(4) == arr.end());
        CHECK_SAME_TYPE(decltype(arr.find_last(1)), array::iterator);
        CHECK_NOEXCEPT(arr.find_last(1));

        array arr2{0, 1, 2, 3};
        CHECK(arr2.find_last(0) == &arr2.front());
        CHECK(arr2.find_last(1) == &arr2.at(1u));
        CHECK(arr2.find_last(2) == &arr2.at(2u));
        CHECK(arr2.find_last(3) == &arr2.at(3u));
        CHECK(arr2.find_last(4) == arr2.end());
    }

    {
        using array = phi::array<int, 0u>;
        array arr;

        CHECK(arr.find_last(0) == arr.end());
        CHECK(arr.find_last(1) == arr.end());
        CHECK(arr.find_last(2) == arr.end());
        CHECK(arr.find_last(3) == arr.end());
        CHECK_SAME_TYPE(decltype(arr.find_last(1)), array::iterator);
        CHECK_NOEXCEPT(arr.find_last(1));
    }

    {
        using array = phi::array<int, 3u>;
        const array arr{1, 2, 3};

        CHECK(arr.find_last(1) == &arr.front());
        CHECK(arr.find_last(2) == &arr.at(1u));
        CHECK(arr.find_last(3) == &arr.back());
        CHECK(arr.find_last(0) == arr.end());
        CHECK(arr.find_last(4) == arr.end());
        CHECK_SAME_TYPE(decltype(arr.find_last(1)), array::const_iterator);
        CHECK_NOEXCEPT(arr.find_last(1));

        array arr2{1, 2, 2};
        CHECK(arr2.find_last(0) == arr2.end());
        CHECK(arr2.find_last(1) == &arr2.at(0u));
        CHECK(arr2.find_last(2) == &arr2.at(2u));
        CHECK(arr2.find_last(3) == arr2.end());
        CHECK(arr2.find_last(4) == arr2.end());
    }

    {
        using array = phi::array<int, 0u>;
        const array arr;

        CHECK(arr.find_last(0) == arr.end());
        CHECK(arr.find_last(1) == arr.end());
        CHECK(arr.find_last(2) == arr.end());
        CHECK(arr.find_last(3) == arr.end());
        CHECK_SAME_TYPE(decltype(arr.find_last(1)), array::const_iterator);
        CHECK_NOEXCEPT(arr.find_last(1));
    }

    {
        using array = phi::array<int, 3u>;
        PHI_CONSTEXPR array arr{1, 2, 3};

        // NOTE: Before gcc-10 some of the sanitizer pointer functions are not constexpr
#if PHI_COMPILER_IS_BELOW(GCC, 10, 0, 0)
        CHECK(arr.find_last(1) == &arr.front());
        CHECK(arr.find_last(2) == &arr.at(1u));
        CHECK(arr.find_last(3) == &arr.back());
        CHECK(arr.find_last(0) == arr.end());
        CHECK(arr.find_last(4) == arr.end());
#else
        EXT_STATIC_REQUIRE(arr.find_last(1) == &arr.front());
        EXT_STATIC_REQUIRE(arr.find_last(2) == &arr.at(1u));
        EXT_STATIC_REQUIRE(arr.find_last(3) == &arr.back());
        EXT_STATIC_REQUIRE(arr.find_last(0) == arr.end());
        EXT_STATIC_REQUIRE(arr.find_last(4) == arr.end());
#endif

        CHECK_SAME_TYPE(decltype(arr.find_last(1)), array::const_iterator);
        CHECK_NOEXCEPT(arr.find_last(1));
    }

    {
        using array = phi::array<int, 0u>;
        PHI_CONSTEXPR array arr;

        STATIC_REQUIRE(arr.find_last(0) == arr.end());
        STATIC_REQUIRE(arr.find_last(1) == arr.end());
        STATIC_REQUIRE(arr.find_last(2) == arr.end());
        STATIC_REQUIRE(arr.find_last(3) == arr.end());
        CHECK_SAME_TYPE(decltype(arr.find_last(1)), array::const_iterator);
        CHECK_NOEXCEPT(arr.find_last(1));
    }
}

TEST_CASE("array find_last_if")
{
    {
        using array = phi::array<int, 3u>;
        array arr{1, 2, 3};

        CHECK(arr.find_last_if(eq0) == arr.end());
        CHECK(arr.find_last_if(eq1) == &arr.at(0u));
        CHECK(arr.find_last_if(eq2) == &arr.at(1u));
        CHECK(arr.find_last_if(eq3) == &arr.at(2u));
        CHECK(arr.find_last_if(ne0) == &arr.at(2u));
        CHECK(arr.find_last_if(ne1) == &arr.at(2u));
        CHECK(arr.find_last_if(ne2) == &arr.at(2u));
        CHECK(arr.find_last_if(ne3) == &arr.at(1u));
        CHECK(arr.find_last_if(even) == &arr.at(1u));
        CHECK(arr.find_last_if(odd) == &arr.at(2u));
        CHECK(arr.find_last_if(always_false) == arr.end());
        CHECK(arr.find_last_if(always_true) == &arr.at(2u));
        CHECK_SAME_TYPE(decltype(arr.find_last_if(always_false)), array::iterator);
        CHECK_NOT_NOEXCEPT(arr.find_last_if(always_throw));
#if PHI_HAS_FEATURE_NOEXCEPT_CLASS_EXPR()
        CHECK_NOEXCEPT(arr.find_last_if(always_false));
#endif

#if PHI_HAS_FEATURE_LAMBDA()
        CHECK(arr.find_last_if(lambda_eq0) == arr.end());
        CHECK(arr.find_last_if(lambda_eq1) == &arr.at(0u));
        CHECK(arr.find_last_if(lambda_eq2) == &arr.at(1u));
        CHECK(arr.find_last_if(lambda_eq3) == &arr.at(2u));
        CHECK(arr.find_last_if(lambda_ne0) == &arr.at(2u));
        CHECK(arr.find_last_if(lambda_ne1) == &arr.at(2u));
        CHECK(arr.find_last_if(lambda_ne2) == &arr.at(2u));
        CHECK(arr.find_last_if(lambda_ne3) == &arr.at(1u));
        CHECK(arr.find_last_if(lambda_even) == &arr.at(1u));
        CHECK(arr.find_last_if(lambda_odd) == &arr.at(2u));
        CHECK(arr.find_last_if(lambda_false) == arr.end());
        CHECK(arr.find_last_if(lambda_true) == &arr.at(2u));
        CHECK_SAME_TYPE(decltype(arr.find_last_if(lambda_false)), array::iterator);
        CHECK_NOT_NOEXCEPT(arr.find_last_if(lambda_throw));
#    if PHI_HAS_FEATURE_NOEXCEPT_CLASS_EXPR()
        CHECK_NOEXCEPT(arr.find_last_if(lambda_false));
#    endif
#endif
    }

    {
        using array = phi::array<int, 0u>;
        array arr;

        CHECK(arr.find_last_if(eq1) == arr.end());
        CHECK(arr.find_last_if(eq2) == arr.end());
        CHECK(arr.find_last_if(even) == arr.end());
        CHECK(arr.find_last_if(always_false) == arr.end());
        CHECK_SAME_TYPE(decltype(arr.find_last_if(always_false)), array::iterator);
        CHECK_NOEXCEPT(arr.find_last_if(always_throw));
        CHECK_NOEXCEPT(arr.find_last_if(always_false));

#if PHI_HAS_FEATURE_LAMBDA()
        CHECK(arr.find_last_if(lambda_eq1) == arr.end());
        CHECK(arr.find_last_if(lambda_eq2) == arr.end());
        CHECK(arr.find_last_if(lambda_even) == arr.end());
        CHECK(arr.find_last_if(lambda_false) == arr.end());
        CHECK_SAME_TYPE(decltype(arr.find_last_if(lambda_false)), array::iterator);
        CHECK_NOEXCEPT(arr.find_last_if(lambda_throw));
        CHECK_NOEXCEPT(arr.find_last_if(lambda_false));
#endif
    }

    {
        using array = phi::array<int, 3u>;
        const array arr{1, 2, 3};

        CHECK(arr.find_last_if(eq0) == arr.end());
        CHECK(arr.find_last_if(eq1) == &arr.at(0u));
        CHECK(arr.find_last_if(eq2) == &arr.at(1u));
        CHECK(arr.find_last_if(eq3) == &arr.at(2u));
        CHECK(arr.find_last_if(ne0) == &arr.at(2u));
        CHECK(arr.find_last_if(ne1) == &arr.at(2u));
        CHECK(arr.find_last_if(ne2) == &arr.at(2u));
        CHECK(arr.find_last_if(ne3) == &arr.at(1u));
        CHECK(arr.find_last_if(even) == &arr.at(1u));
        CHECK(arr.find_last_if(odd) == &arr.at(2u));
        CHECK(arr.find_last_if(always_false) == arr.end());
        CHECK(arr.find_last_if(always_true) == &arr.at(2u));
        CHECK_SAME_TYPE(decltype(arr.find_last_if(always_false)), array::const_iterator);
        CHECK_NOT_NOEXCEPT(arr.find_last_if(always_throw));
#if PHI_HAS_FEATURE_NOEXCEPT_CLASS_EXPR()
        CHECK_NOEXCEPT(arr.find_last_if(always_false));
#endif

#if PHI_HAS_FEATURE_LAMBDA()
        CHECK(arr.find_last_if(lambda_eq0) == arr.end());
        CHECK(arr.find_last_if(lambda_eq1) == &arr.at(0u));
        CHECK(arr.find_last_if(lambda_eq2) == &arr.at(1u));
        CHECK(arr.find_last_if(lambda_eq3) == &arr.at(2u));
        CHECK(arr.find_last_if(lambda_ne0) == &arr.at(2u));
        CHECK(arr.find_last_if(lambda_ne1) == &arr.at(2u));
        CHECK(arr.find_last_if(lambda_ne2) == &arr.at(2u));
        CHECK(arr.find_last_if(lambda_ne3) == &arr.at(1u));
        CHECK(arr.find_last_if(lambda_even) == &arr.at(1u));
        CHECK(arr.find_last_if(lambda_odd) == &arr.at(2u));
        CHECK(arr.find_last_if(lambda_false) == arr.end());
        CHECK(arr.find_last_if(lambda_true) == &arr.at(2u));
        CHECK_SAME_TYPE(decltype(arr.find_last_if(lambda_false)), array::const_iterator);
        CHECK_NOT_NOEXCEPT(arr.find_last_if(lambda_throw));
#    if PHI_HAS_FEATURE_NOEXCEPT_CLASS_EXPR()
        CHECK_NOEXCEPT(arr.find_last_if(lambda_false));
#    endif
#endif
    }

    {
        using array = phi::array<int, 0u>;
        const array arr;

        CHECK(arr.find_last_if(eq1) == arr.end());
        CHECK(arr.find_last_if(eq2) == arr.end());
        CHECK(arr.find_last_if(even) == arr.end());
        CHECK(arr.find_last_if(always_false) == arr.end());
        CHECK_SAME_TYPE(decltype(arr.find_last_if(always_false)), array::const_iterator);
        CHECK_NOEXCEPT(arr.find_last_if(always_throw));
        CHECK_NOEXCEPT(arr.find_last_if(always_false));

#if PHI_HAS_FEATURE_LAMBDA()
        CHECK(arr.find_last_if(lambda_eq1) == arr.end());
        CHECK(arr.find_last_if(lambda_eq2) == arr.end());
        CHECK(arr.find_last_if(lambda_even) == arr.end());
        CHECK(arr.find_last_if(lambda_false) == arr.end());
        CHECK_SAME_TYPE(decltype(arr.find_last_if(lambda_false)), array::const_iterator);
        CHECK_NOEXCEPT(arr.find_last_if(lambda_throw));
        CHECK_NOEXCEPT(arr.find_last_if(lambda_false));
#endif
    }

    {
        using array = phi::array<int, 3u>;
        PHI_CONSTEXPR array arr{1, 2, 3};

        // NOTE: Before gcc-10 some of the sanitizer pointer functions are not constexpr
#if PHI_COMPILER_IS_BELOW(GCC, 10, 0, 0)
        CHECK(arr.find_last_if(eq1) == &arr.at(0u));
        CHECK(arr.find_last_if(eq2) == &arr.at(1u));
        CHECK(arr.find_last_if(even) == &arr.at(1u));
        CHECK(arr.find_last_if(always_false) == arr.end());
#else
        EXT_STATIC_REQUIRE(arr.find_last_if(eq1) == &arr.at(0u));
        EXT_STATIC_REQUIRE(arr.find_last_if(eq2) == &arr.at(1u));
        EXT_STATIC_REQUIRE(arr.find_last_if(even) == &arr.at(1u));
        EXT_STATIC_REQUIRE(arr.find_last_if(always_false) == arr.end());
#endif

        CHECK_SAME_TYPE(decltype(arr.find_last_if(always_false)), array::const_iterator);
        CHECK_NOT_NOEXCEPT(arr.find_last_if(always_throw));
#if PHI_HAS_FEATURE_NOEXCEPT_CLASS_EXPR()
        CHECK_NOEXCEPT(arr.find_last_if(always_false));
#endif

#if PHI_HAS_FEATURE_LAMBDA() && PHI_HAS_FEATURE_CONSTEXPR_LAMBDA()
        // NOTE: Before gcc-10 some of the sanitizer pointer functions are not constexpr
#    if PHI_COMPILER_IS_BELOW(GCC, 10, 0, 0)
        CHECK(arr.find_last_if(lambda_eq1) == &arr.at(0u));
        CHECK(arr.find_last_if(lambda_eq2) == &arr.at(1u));
        CHECK(arr.find_last_if(lambda_even) == &arr.at(1u));
        CHECK(arr.find_last_if(lambda_false) == arr.end());
#    else
        EXT_STATIC_REQUIRE(arr.find_last_if(lambda_eq1) == &arr.at(0u));
        EXT_STATIC_REQUIRE(arr.find_last_if(lambda_eq2) == &arr.at(1u));
        EXT_STATIC_REQUIRE(arr.find_last_if(lambda_even) == &arr.at(1u));
        EXT_STATIC_REQUIRE(arr.find_last_if(lambda_false) == arr.end());
#    endif

        CHECK_SAME_TYPE(decltype(arr.find_last_if(lambda_false)), array::const_iterator);
        CHECK_NOT_NOEXCEPT(arr.find_last_if(lambda_throw));
#    if PHI_HAS_FEATURE_NOEXCEPT_CLASS_EXPR()
        CHECK_NOEXCEPT(arr.find_last_if(lambda_false));
#    endif
#endif
    }

    {
        using array = phi::array<int, 0u>;
        PHI_CONSTEXPR array arr;

        STATIC_REQUIRE(arr.find_last_if(eq1) == arr.end());
        STATIC_REQUIRE(arr.find_last_if(eq2) == arr.end());
        STATIC_REQUIRE(arr.find_last_if(even) == arr.end());
        STATIC_REQUIRE(arr.find_last_if(always_false) == arr.end());
        CHECK_SAME_TYPE(decltype(arr.find_last_if(always_false)), array::const_iterator);
        CHECK_NOEXCEPT(arr.find_last_if(always_throw));
        CHECK_NOEXCEPT(arr.find_last_if(always_false));

#if PHI_HAS_FEATURE_LAMBDA() && PHI_HAS_FEATURE_CONSTEXPR_LAMBDA()
        STATIC_REQUIRE(arr.find_last_if(lambda_eq1) == arr.end());
        STATIC_REQUIRE(arr.find_last_if(lambda_eq2) == arr.end());
        STATIC_REQUIRE(arr.find_last_if(lambda_even) == arr.end());
        STATIC_REQUIRE(arr.find_last_if(lambda_false) == arr.end());
        CHECK_SAME_TYPE(decltype(arr.find_last_if(lambda_false)), array::const_iterator);
        CHECK_NOEXCEPT(arr.find_last_if(lambda_throw));
        CHECK_NOEXCEPT(arr.find_last_if(lambda_false));
#endif
    }
}

TEST_CASE("array find_last_if_not")
{
    {
        using array = phi::array<int, 3u>;
        array arr{1, 2, 3};

        CHECK(arr.find_last_if_not(eq0) == &arr.at(2u));
        CHECK(arr.find_last_if_not(eq1) == &arr.at(2u));
        CHECK(arr.find_last_if_not(eq2) == &arr.at(2u));
        CHECK(arr.find_last_if_not(eq3) == &arr.at(1u));
        CHECK(arr.find_last_if_not(ne0) == arr.end());
        CHECK(arr.find_last_if_not(ne1) == &arr.at(0u));
        CHECK(arr.find_last_if_not(ne2) == &arr.at(1u));
        CHECK(arr.find_last_if_not(ne3) == &arr.at(2u));
        CHECK(arr.find_last_if_not(odd) == &arr.at(1u));
        CHECK(arr.find_last_if_not(even) == &arr.at(2u));
        CHECK(arr.find_last_if_not(always_false) == &arr.at(2u));
        CHECK(arr.find_last_if_not(always_true) == arr.end());
        CHECK_SAME_TYPE(decltype(arr.find_last_if_not(always_false)), array::iterator);
        CHECK_NOT_NOEXCEPT(arr.find_last_if_not(always_throw));
#if PHI_HAS_FEATURE_NOEXCEPT_CLASS_EXPR()
        CHECK_NOEXCEPT(arr.find_last_if_not(always_false));
#endif

#if PHI_HAS_FEATURE_LAMBDA()
        CHECK(arr.find_last_if_not(lambda_eq0) == &arr.at(2u));
        CHECK(arr.find_last_if_not(lambda_eq1) == &arr.at(2u));
        CHECK(arr.find_last_if_not(lambda_eq2) == &arr.at(2u));
        CHECK(arr.find_last_if_not(lambda_eq3) == &arr.at(1u));
        CHECK(arr.find_last_if_not(lambda_ne0) == arr.end());
        CHECK(arr.find_last_if_not(lambda_ne1) == &arr.at(0u));
        CHECK(arr.find_last_if_not(lambda_ne2) == &arr.at(1u));
        CHECK(arr.find_last_if_not(lambda_ne3) == &arr.at(2u));
        CHECK(arr.find_last_if_not(lambda_odd) == &arr.at(1u));
        CHECK(arr.find_last_if_not(lambda_even) == &arr.at(2u));
        CHECK(arr.find_last_if_not(lambda_false) == &arr.at(2u));
        CHECK(arr.find_last_if_not(lambda_true) == arr.end());
        CHECK_SAME_TYPE(decltype(arr.find_last_if_not(lambda_false)), array::iterator);
        CHECK_NOT_NOEXCEPT(arr.find_last_if_not(lambda_throw));
#    if PHI_HAS_FEATURE_NOEXCEPT_CLASS_EXPR()
        CHECK_NOEXCEPT(arr.find_last_if_not(lambda_false));
#    endif
#endif
    }

    {
        using array = phi::array<int, 0u>;
        array arr;

        CHECK(arr.find_last_if_not(eq1) == arr.end());
        CHECK(arr.find_last_if_not(eq2) == arr.end());
        CHECK(arr.find_last_if_not(even) == arr.end());
        CHECK(arr.find_last_if_not(always_true) == arr.end());
        CHECK_SAME_TYPE(decltype(arr.find_last_if_not(always_false)), array::iterator);
        CHECK_NOEXCEPT(arr.find_last_if_not(always_throw));
        CHECK_NOEXCEPT(arr.find_last_if_not(always_false));

#if PHI_HAS_FEATURE_LAMBDA()
        CHECK(arr.find_last_if_not(lambda_eq1) == arr.end());
        CHECK(arr.find_last_if_not(lambda_eq2) == arr.end());
        CHECK(arr.find_last_if_not(lambda_even) == arr.end());
        CHECK(arr.find_last_if_not(lambda_true) == arr.end());
        CHECK_SAME_TYPE(decltype(arr.find_last_if_not(lambda_false)), array::iterator);
        CHECK_NOEXCEPT(arr.find_last_if_not(lambda_throw));
        CHECK_NOEXCEPT(arr.find_last_if_not(lambda_false));
#endif
    }

    {
        using array = phi::array<int, 3u>;
        const array arr{1, 2, 3};

        CHECK(arr.find_last_if_not(eq0) == &arr.at(2u));
        CHECK(arr.find_last_if_not(eq1) == &arr.at(2u));
        CHECK(arr.find_last_if_not(eq2) == &arr.at(2u));
        CHECK(arr.find_last_if_not(eq3) == &arr.at(1u));
        CHECK(arr.find_last_if_not(ne0) == arr.end());
        CHECK(arr.find_last_if_not(ne1) == &arr.at(0u));
        CHECK(arr.find_last_if_not(ne2) == &arr.at(1u));
        CHECK(arr.find_last_if_not(ne3) == &arr.at(2u));
        CHECK(arr.find_last_if_not(even) == &arr.at(2u));
        CHECK(arr.find_last_if_not(odd) == &arr.at(1u));
        CHECK(arr.find_last_if_not(always_false) == &arr.at(2u));
        CHECK(arr.find_last_if_not(always_true) == arr.end());
        CHECK_SAME_TYPE(decltype(arr.find_last_if_not(always_false)), array::const_iterator);
        CHECK_NOT_NOEXCEPT(arr.find_last_if_not(always_throw));
#if PHI_HAS_FEATURE_NOEXCEPT_CLASS_EXPR()
        CHECK_NOEXCEPT(arr.find_last_if_not(always_false));
#endif

#if PHI_HAS_FEATURE_LAMBDA()
        CHECK(arr.find_last_if_not(lambda_eq0) == &arr.at(2u));
        CHECK(arr.find_last_if_not(lambda_eq1) == &arr.at(2u));
        CHECK(arr.find_last_if_not(lambda_eq2) == &arr.at(2u));
        CHECK(arr.find_last_if_not(lambda_eq3) == &arr.at(1u));
        CHECK(arr.find_last_if_not(lambda_ne0) == arr.end());
        CHECK(arr.find_last_if_not(lambda_ne1) == &arr.at(0u));
        CHECK(arr.find_last_if_not(lambda_ne2) == &arr.at(1u));
        CHECK(arr.find_last_if_not(lambda_ne3) == &arr.at(2u));
        CHECK(arr.find_last_if_not(lambda_even) == &arr.at(2u));
        CHECK(arr.find_last_if_not(lambda_odd) == &arr.at(1u));
        CHECK(arr.find_last_if_not(lambda_false) == &arr.at(2u));
        CHECK(arr.find_last_if_not(lambda_true) == arr.end());
        CHECK_SAME_TYPE(decltype(arr.find_last_if_not(lambda_false)), array::const_iterator);
        CHECK_NOT_NOEXCEPT(arr.find_last_if_not(lambda_throw));
#    if PHI_HAS_FEATURE_NOEXCEPT_CLASS_EXPR()
        CHECK_NOEXCEPT(arr.find_last_if_not(lambda_false));
#    endif
#endif
    }

    {
        using array = phi::array<int, 0u>;
        const array arr;

        CHECK(arr.find_last_if_not(eq1) == arr.end());
        CHECK(arr.find_last_if_not(eq2) == arr.end());
        CHECK(arr.find_last_if_not(even) == arr.end());
        CHECK(arr.find_last_if_not(always_true) == arr.end());
        CHECK_SAME_TYPE(decltype(arr.find_last_if_not(always_false)), array::const_iterator);
        CHECK_NOEXCEPT(arr.find_last_if_not(always_throw));
        CHECK_NOEXCEPT(arr.find_last_if_not(always_false));

#if PHI_HAS_FEATURE_LAMBDA()
        CHECK(arr.find_last_if_not(lambda_eq1) == arr.end());
        CHECK(arr.find_last_if_not(lambda_eq2) == arr.end());
        CHECK(arr.find_last_if_not(lambda_even) == arr.end());
        CHECK(arr.find_last_if_not(lambda_true) == arr.end());
        CHECK_SAME_TYPE(decltype(arr.find_last_if_not(lambda_false)), array::const_iterator);
        CHECK_NOEXCEPT(arr.find_last_if_not(lambda_throw));
        CHECK_NOEXCEPT(arr.find_last_if_not(lambda_false));
#endif
    }

    {
        using array = phi::array<int, 3u>;
        PHI_CONSTEXPR array arr{1, 2, 3};

        // NOTE: Before gcc-10 some of the sanitizer pointer functions are not constexpr
#if PHI_COMPILER_IS_BELOW(GCC, 10, 0, 0)
        CHECK(arr.find_last_if_not(eq3) == &arr.at(1u));
        CHECK(arr.find_last_if_not(eq1) == &arr.at(2u));
        CHECK(arr.find_last_if_not(odd) == &arr.at(1u));
        CHECK(arr.find_last_if_not(always_true) == arr.end());
#else
        EXT_STATIC_REQUIRE(arr.find_last_if_not(eq3) == &arr.at(1u));
        EXT_STATIC_REQUIRE(arr.find_last_if_not(eq1) == &arr.at(2u));
        EXT_STATIC_REQUIRE(arr.find_last_if_not(odd) == &arr.at(1u));
        EXT_STATIC_REQUIRE(arr.find_last_if_not(always_true) == arr.end());
#endif

        CHECK_SAME_TYPE(decltype(arr.find_last_if_not(always_false)), array::const_iterator);
        CHECK_NOT_NOEXCEPT(arr.find_last_if_not(always_throw));
#if PHI_HAS_FEATURE_NOEXCEPT_CLASS_EXPR()
        CHECK_NOEXCEPT(arr.find_last_if_not(always_false));
#endif

#if PHI_HAS_FEATURE_LAMBDA() && PHI_HAS_FEATURE_CONSTEXPR_LAMBDA()
        // NOTE: Before gcc-10 some of the sanitizer pointer functions are not constexpr
#    if PHI_COMPILER_IS_BELOW(GCC, 10, 0, 0)
        CHECK(arr.find_last_if_not(lambda_eq3) == &arr.at(1u));
        CHECK(arr.find_last_if_not(lambda_eq1) == &arr.at(2u));
        CHECK(arr.find_last_if_not(lambda_odd) == &arr.at(1u));
        CHECK(arr.find_last_if_not(lambda_true) == arr.end());
#    else
        EXT_STATIC_REQUIRE(arr.find_last_if_not(lambda_eq3) == &arr.at(1u));
        EXT_STATIC_REQUIRE(arr.find_last_if_not(lambda_eq1) == &arr.at(2u));
        EXT_STATIC_REQUIRE(arr.find_last_if_not(lambda_odd) == &arr.at(1u));
        EXT_STATIC_REQUIRE(arr.find_last_if_not(lambda_true) == arr.end());
#    endif

        CHECK_SAME_TYPE(decltype(arr.find_last_if_not(lambda_false)), array::const_iterator);
        CHECK_NOT_NOEXCEPT(arr.find_last_if_not(lambda_throw));
#    if PHI_HAS_FEATURE_NOEXCEPT_CLASS_EXPR()
        CHECK_NOEXCEPT(arr.find_last_if_not(lambda_false));
#    endif
#endif
    }

    {
        using array = phi::array<int, 0u>;
        PHI_CONSTEXPR array arr;

        STATIC_REQUIRE(arr.find_last_if_not(eq1) == arr.end());
        STATIC_REQUIRE(arr.find_last_if_not(eq2) == arr.end());
        STATIC_REQUIRE(arr.find_last_if_not(even) == arr.end());
        STATIC_REQUIRE(arr.find_last_if_not(always_false) == arr.end());
        CHECK_SAME_TYPE(decltype(arr.find_last_if_not(always_false)), array::const_iterator);
        CHECK_NOEXCEPT(arr.find_last_if_not(always_throw));
        CHECK_NOEXCEPT(arr.find_last_if_not(always_false));

#if PHI_HAS_FEATURE_LAMBDA() && PHI_HAS_FEATURE_CONSTEXPR_LAMBDA()
        STATIC_REQUIRE(arr.find_last_if_not(lambda_eq1) == arr.end());
        STATIC_REQUIRE(arr.find_last_if_not(lambda_eq2) == arr.end());
        STATIC_REQUIRE(arr.find_last_if_not(lambda_even) == arr.end());
        STATIC_REQUIRE(arr.find_last_if_not(lambda_false) == arr.end());
        CHECK_SAME_TYPE(decltype(arr.find_last_if_not(lambda_false)), array::const_iterator);
        CHECK_NOEXCEPT(arr.find_last_if_not(lambda_throw));
        CHECK_NOEXCEPT(arr.find_last_if_not(lambda_false));
#endif
    }
}

template <typename TypeT>
PHI_EXTENDED_CONSTEXPR void check_iterator_noexcept(TypeT& container)
{
    CHECK_NOEXCEPT(container.begin());
    CHECK_NOEXCEPT(container.end());
    CHECK_NOEXCEPT(container.cbegin());
    CHECK_NOEXCEPT(container.cend());
    CHECK_NOEXCEPT(container.rbegin());
    CHECK_NOEXCEPT(container.rend());
    CHECK_NOEXCEPT(container.crbegin());
    CHECK_NOEXCEPT(container.crend());

    const TypeT& const_container = container;
    (void)const_container;
    CHECK_NOEXCEPT(const_container.begin());
    CHECK_NOEXCEPT(const_container.end());
    CHECK_NOEXCEPT(const_container.cbegin());
    CHECK_NOEXCEPT(const_container.cend());
    CHECK_NOEXCEPT(const_container.rbegin());
    CHECK_NOEXCEPT(const_container.rend());
    CHECK_NOEXCEPT(const_container.crbegin());
    CHECK_NOEXCEPT(const_container.crend());
}

PHI_EXTENDED_CONSTEXPR bool test_iterators()
{
    {
        using C = phi::array<int, 5>;
        C array = {};
        check_iterator_noexcept(array);
        typename C::iterator       i = array.begin();
        typename C::const_iterator j = array.cbegin();
        PHI_RELEASE_ASSERT(i == j, "");
    }

    {
        using C = phi::array<int, 0>;
        C array = {};
        check_iterator_noexcept(array);
        typename C::iterator       i = array.begin();
        typename C::const_iterator j = array.cbegin();
        PHI_RELEASE_ASSERT(i == j, "");
    }

    {
        using C = phi::array<int, 0>;
        C array = {};
        check_iterator_noexcept(array);
        typename C::iterator       i = array.begin();
        typename C::const_iterator j = array.cbegin();
        PHI_RELEASE_ASSERT(i == array.end(), "");
        PHI_RELEASE_ASSERT(j == array.cend(), "");
    }

    {
        using C = phi::array<int, 1>;
        C array = {1};
        check_iterator_noexcept(array);
        typename C::iterator i = array.begin();
        PHI_RELEASE_ASSERT(*i == 1, "");
        PHI_RELEASE_ASSERT(&*i == array.data(), "");
        *i = 99;
        PHI_RELEASE_ASSERT(array[0u] == 99, "");
    }

    {
        using C = phi::array<int, 2>;
        C array = {1, 2};
        check_iterator_noexcept(array);
        typename C::iterator i = array.begin();
        PHI_RELEASE_ASSERT(*i == 1, "");
        PHI_RELEASE_ASSERT(&*i == array.data(), "");
        *i = 99;
        PHI_RELEASE_ASSERT(array[0u] == 99, "");
        PHI_RELEASE_ASSERT(array[1u] == 2, "");
    }

    {
        using C = phi::array<bool, 3>;
        C array = {true, false, true};
        check_iterator_noexcept(array);
        typename C::iterator i = array.begin();
        PHI_RELEASE_ASSERT(*i == true, "");
        PHI_RELEASE_ASSERT(&*i == array.data(), "");
        *i = false;
        PHI_RELEASE_ASSERT(array[0u] == false, "");
        PHI_RELEASE_ASSERT(array[1u] == false, "");
        PHI_RELEASE_ASSERT(array[2u] == true, "");
    }

    {
        using C                    = phi::array<NoDefault, 0>;
        C                    array = {};
        typename C::iterator ib    = array.begin();
        typename C::iterator ie    = array.end();
        PHI_RELEASE_ASSERT(ib == ie, "");
    }

    { // N3644 testing
        {
            using C = phi::array<int, 5>;
            C::iterator       ii1{};
            C::iterator       ii2{};
            C::iterator       ii4 = ii1;
            C::const_iterator cii{};
            PHI_RELEASE_ASSERT(ii1 == ii2, "");
            PHI_RELEASE_ASSERT(ii1 == ii4, "");
            PHI_RELEASE_ASSERT(ii1 == cii, "");

            PHI_RELEASE_ASSERT(!(ii1 != ii2), "");
            PHI_RELEASE_ASSERT(!(ii1 != cii), "");

            C c = {};
            check_iterator_noexcept(c);

            PHI_RELEASE_ASSERT(c.begin() == phi::begin(c), "");
            PHI_RELEASE_ASSERT(c.cbegin() == phi::cbegin(c), "");
            PHI_RELEASE_ASSERT(c.rbegin() == phi::rbegin(c), "");
            PHI_RELEASE_ASSERT(c.crbegin() == phi::crbegin(c), "");
            PHI_RELEASE_ASSERT(c.end() == phi::end(c), "");
            PHI_RELEASE_ASSERT(c.cend() == phi::cend(c), "");
            PHI_RELEASE_ASSERT(c.rend() == phi::rend(c), "");
            PHI_RELEASE_ASSERT(c.crend() == phi::crend(c), "");

            PHI_RELEASE_ASSERT(phi::begin(c) != phi::end(c), "");
            PHI_RELEASE_ASSERT(phi::rbegin(c) != phi::rend(c), "");
            PHI_RELEASE_ASSERT(phi::cbegin(c) != phi::cend(c), "");
            PHI_RELEASE_ASSERT(phi::crbegin(c) != phi::crend(c), "");
        }

        {
            using C = phi::array<int, 0>;
            C::iterator       ii1{};
            C::iterator       ii2{};
            C::iterator       ii4 = ii1;
            C::const_iterator cii{};
            PHI_RELEASE_ASSERT(ii1 == ii2, "");
            PHI_RELEASE_ASSERT(ii1 == ii4, "");

            PHI_RELEASE_ASSERT(!(ii1 != ii2), "");

            PHI_RELEASE_ASSERT((ii1 == cii), "");
            PHI_RELEASE_ASSERT((cii == ii1), "");
            PHI_RELEASE_ASSERT(!(ii1 != cii), "");
            PHI_RELEASE_ASSERT(!(cii != ii1), "");
            PHI_RELEASE_ASSERT(!(ii1 < cii), "");
            PHI_RELEASE_ASSERT(!(cii < ii1), "");
            PHI_RELEASE_ASSERT((ii1 <= cii), "");
            PHI_RELEASE_ASSERT((cii <= ii1), "");
            PHI_RELEASE_ASSERT(!(ii1 > cii), "");
            PHI_RELEASE_ASSERT(!(cii > ii1), "");
            PHI_RELEASE_ASSERT((ii1 >= cii), "");
            PHI_RELEASE_ASSERT((cii >= ii1), "");
            PHI_RELEASE_ASSERT(cii - ii1 == 0, "");
            PHI_RELEASE_ASSERT(ii1 - cii == 0, "");

            C c = {};
            check_iterator_noexcept(c);

            PHI_RELEASE_ASSERT(c.begin() == phi::begin(c), "");
            PHI_RELEASE_ASSERT(c.cbegin() == phi::cbegin(c), "");
            PHI_RELEASE_ASSERT(c.rbegin() == phi::rbegin(c), "");
            PHI_RELEASE_ASSERT(c.crbegin() == phi::crbegin(c), "");
            PHI_RELEASE_ASSERT(c.end() == phi::end(c), "");
            PHI_RELEASE_ASSERT(c.cend() == phi::cend(c), "");
            PHI_RELEASE_ASSERT(c.rend() == phi::rend(c), "");
            PHI_RELEASE_ASSERT(c.crend() == phi::crend(c), "");

            PHI_RELEASE_ASSERT(phi::begin(c) == phi::end(c), "");
            PHI_RELEASE_ASSERT(phi::rbegin(c) == phi::rend(c), "");
            PHI_RELEASE_ASSERT(phi::cbegin(c) == phi::cend(c), "");
            PHI_RELEASE_ASSERT(phi::crbegin(c) == phi::crend(c), "");
        }
    }

    return true;
}

TEST_CASE("array iterators")
{
    test_iterators();
#if PHI_HAS_FEATURE_EXTENDED_CONSTEXPR()
    STATIC_REQUIRE_SAN(test_iterators());
#endif
}

template <typename TypeT, phi::size_t Size>
struct MyArray
{
    TypeT elems[Size];
};

template <typename TypeT, size_t Size>
void test_size_and_alignment_impl()
{
    using CArrayT  = TypeT[Size];
    using ArrayT   = phi::array<TypeT, Size>;
    using MyArrayT = MyArray<TypeT, Size>;
    STATIC_REQUIRE(sizeof(ArrayT) == sizeof(CArrayT));
    STATIC_REQUIRE(sizeof(ArrayT) == sizeof(MyArrayT));
    STATIC_REQUIRE(alignof(ArrayT) == alignof(MyArrayT));
}

template <typename TypeT>
void test_size_and_alignment()
{
    STATIC_REQUIRE(sizeof(phi::array<TypeT, 0u>) == 1);

    test_size_and_alignment_impl<TypeT, 1>();
    test_size_and_alignment_impl<TypeT, 2>();
    test_size_and_alignment_impl<TypeT, 3>();
    test_size_and_alignment_impl<TypeT, 4>();
    test_size_and_alignment_impl<TypeT, 5>();
    test_size_and_alignment_impl<TypeT, 6>();
    test_size_and_alignment_impl<TypeT, 7>();
    test_size_and_alignment_impl<TypeT, 8>();
    test_size_and_alignment_impl<TypeT, 42>();
}

struct alignas(alignof(phi::max_align_t) * 2) TestType1
{};

struct alignas(alignof(phi::max_align_t) * 2) TestType2
{
    char data[1000];
};

struct alignas(alignof(phi::max_align_t)) TestType3
{
    char data[1000];
};

TEST_CASE("array size and alignment")
{
    test_size_and_alignment<bool>();
    test_size_and_alignment<char>();
    test_size_and_alignment<signed char>();
    test_size_and_alignment<unsigned char>();
    test_size_and_alignment<short>();
    test_size_and_alignment<unsigned short>();
    test_size_and_alignment<int>();
    test_size_and_alignment<unsigned int>();
    test_size_and_alignment<long>();
    test_size_and_alignment<unsigned long>();
    test_size_and_alignment<long long>();
    test_size_and_alignment<unsigned long long>();
    test_size_and_alignment<float>();
    test_size_and_alignment<double>();
    test_size_and_alignment<long double>();
    test_size_and_alignment<char8_t>();
    test_size_and_alignment<char16_t>();
    test_size_and_alignment<char32_t>();
    test_size_and_alignment<wchar_t>();

    test_size_and_alignment<phi::boolean>();
    test_size_and_alignment<phi::integer<signed char>>();
    test_size_and_alignment<phi::integer<unsigned char>>();
    test_size_and_alignment<phi::integer<short>>();
    test_size_and_alignment<phi::integer<unsigned short>>();
    test_size_and_alignment<phi::integer<int>>();
    test_size_and_alignment<phi::integer<unsigned int>>();
    test_size_and_alignment<phi::integer<long>>();
    test_size_and_alignment<phi::integer<unsigned long>>();
    test_size_and_alignment<phi::integer<long long>>();
    test_size_and_alignment<phi::integer<unsigned long long>>();
    test_size_and_alignment<phi::floating_point<float>>();
    test_size_and_alignment<phi::floating_point<double>>();
    test_size_and_alignment<phi::floating_point<long double>>();

    test_size_and_alignment<phi::max_align_t>();
    test_size_and_alignment<TestType1>();
    test_size_and_alignment<TestType2>();
    test_size_and_alignment<TestType3>();
}

TEST_CASE("array compare")
{
    // TODO: noexcept checks
    {
        using array = phi::array<int, 3u>;
        array lhs{1, 2, 3};
        array rhs{1, 2, 3};

        CHECK(lhs == rhs);
        CHECK_FALSE(lhs != rhs);

        CHECK_FALSE(lhs < rhs);
        CHECK(lhs <= rhs);
        CHECK_FALSE(lhs > rhs);
        CHECK(lhs >= rhs);
    }

    {
        using array = phi::array<int, 3u>;
        const array lhs{1, 2, 3};
        const array rhs{1, 2, 3};

        CHECK(lhs == rhs);
        CHECK_FALSE(lhs != rhs);

        CHECK_FALSE(lhs < rhs);
        CHECK(lhs <= rhs);
        CHECK_FALSE(lhs > rhs);
        CHECK(lhs >= rhs);
    }

    {
        using array = phi::array<int, 3u>;
        PHI_CONSTEXPR array lhs{1, 2, 3};
        PHI_CONSTEXPR array rhs{1, 2, 3};

        EXT_STATIC_REQUIRE(lhs == rhs);
        EXT_STATIC_REQUIRE_FALSE(lhs != rhs);

        EXT_STATIC_REQUIRE_FALSE(lhs < rhs);
        EXT_STATIC_REQUIRE(lhs <= rhs);
        EXT_STATIC_REQUIRE_FALSE(lhs > rhs);
        EXT_STATIC_REQUIRE(lhs >= rhs);
    }

    {
        using array = phi::array<int, 3u>;
        array lhs{1, 2, 5};
        array rhs{1, 2, 3};

        CHECK_FALSE(lhs == rhs);
        CHECK(lhs != rhs);

        CHECK_FALSE(lhs < rhs);
        CHECK_FALSE(lhs <= rhs);
        CHECK(lhs > rhs);
        CHECK(lhs >= rhs);
    }

    {
        using array = phi::array<int, 3u>;
        const array lhs{1, 2, 5};
        const array rhs{1, 2, 3};

        CHECK_FALSE(lhs == rhs);
        CHECK(lhs != rhs);

        CHECK_FALSE(lhs < rhs);
        CHECK_FALSE(lhs <= rhs);
        CHECK(lhs > rhs);
        CHECK(lhs >= rhs);
    }

    {
        using array = phi::array<int, 3u>;
        PHI_CONSTEXPR array lhs{1, 2, 5};
        PHI_CONSTEXPR array rhs{1, 2, 3};

        EXT_STATIC_REQUIRE_FALSE(lhs == rhs);
        EXT_STATIC_REQUIRE(lhs != rhs);

        EXT_STATIC_REQUIRE_FALSE(lhs < rhs);
        EXT_STATIC_REQUIRE_FALSE(lhs <= rhs);
        EXT_STATIC_REQUIRE(lhs > rhs);
        EXT_STATIC_REQUIRE(lhs >= rhs);
    }

    {
        using array = phi::array<int, 3u>;
        array lhs{1, 2, 3};
        array rhs{5, 2, 3};

        CHECK_FALSE(lhs == rhs);
        CHECK(lhs != rhs);

        CHECK(lhs < rhs);
        CHECK(lhs <= rhs);
        CHECK_FALSE(lhs > rhs);
        CHECK_FALSE(lhs >= rhs);
    }

    {
        using array = phi::array<int, 3u>;
        const array lhs{1, 2, 3};
        const array rhs{5, 2, 3};

        CHECK_FALSE(lhs == rhs);
        CHECK(lhs != rhs);

        CHECK(lhs < rhs);
        CHECK(lhs <= rhs);
        CHECK_FALSE(lhs > rhs);
        CHECK_FALSE(lhs >= rhs);
    }

    {
        using array = phi::array<int, 3u>;
        PHI_CONSTEXPR array lhs{1, 2, 3};
        PHI_CONSTEXPR array rhs{5, 2, 3};

        EXT_STATIC_REQUIRE_FALSE(lhs == rhs);
        EXT_STATIC_REQUIRE(lhs != rhs);

        EXT_STATIC_REQUIRE(lhs < rhs);
        EXT_STATIC_REQUIRE(lhs <= rhs);
        EXT_STATIC_REQUIRE_FALSE(lhs > rhs);
        EXT_STATIC_REQUIRE_FALSE(lhs >= rhs);
    }

    {
        using array = phi::array<int, 0u>;
        array lhs{};
        array rhs{};

        CHECK(lhs == rhs);
        CHECK_FALSE(lhs != rhs);

        CHECK_FALSE(lhs < rhs);
        CHECK(lhs <= rhs);
        CHECK_FALSE(lhs > rhs);
        CHECK(lhs >= rhs);
    }

    {
        using array = phi::array<int, 0u>;
        const array lhs{};
        const array rhs{};

        CHECK(lhs == rhs);
        CHECK_FALSE(lhs != rhs);

        CHECK_FALSE(lhs < rhs);
        CHECK(lhs <= rhs);
        CHECK_FALSE(lhs > rhs);
        CHECK(lhs >= rhs);
    }

    {
        using array = phi::array<int, 0u>;
        PHI_CONSTEXPR array lhs{};
        PHI_CONSTEXPR array rhs{};

        EXT_STATIC_REQUIRE(lhs == rhs);
        EXT_STATIC_REQUIRE_FALSE(lhs != rhs);

        EXT_STATIC_REQUIRE_FALSE(lhs < rhs);
        EXT_STATIC_REQUIRE(lhs <= rhs);
        EXT_STATIC_REQUIRE_FALSE(lhs > rhs);
        EXT_STATIC_REQUIRE(lhs >= rhs);
    }
}

template <typename ContainerT>
void test_iterators()
{
    using ItT  = phi::iterator_traits<typename ContainerT::iterator>;
    using CItT = phi::iterator_traits<typename ContainerT::const_iterator>;

    CHECK_SAME_TYPE(typename ItT::iterator_category, phi::random_access_iterator_tag);
    CHECK_SAME_TYPE(typename ItT::value_type, typename ContainerT::value_type);
    CHECK_SAME_TYPE(typename ItT::reference, typename ContainerT::reference);
    CHECK_SAME_TYPE(typename ItT::pointer, typename ContainerT::pointer);
    CHECK_SAME_TYPE(typename ItT::difference_type, typename ContainerT::difference_type);

    CHECK_SAME_TYPE(typename CItT::iterator_category, phi::random_access_iterator_tag);
    CHECK_SAME_TYPE(typename CItT::value_type, typename ContainerT::value_type);
    CHECK_SAME_TYPE(typename CItT::reference, typename ContainerT::const_reference);
    CHECK_SAME_TYPE(typename CItT::pointer, typename ContainerT::const_pointer);
    CHECK_SAME_TYPE(typename CItT::difference_type, typename ContainerT::difference_type);
}

template <typename TypeT, phi::size_t Size>
void test_array_types_impl()
{
    using T = TypeT;
    using C = phi::array<TypeT, Size>;

    CHECK_SAME_TYPE(typename C::this_type, C);
    CHECK_SAME_TYPE(typename C::value_type, T);
    CHECK_SAME_TYPE(typename C::reference, T&);
    CHECK_SAME_TYPE(typename C::const_reference, const T&);
    CHECK_SAME_TYPE(typename C::iterator, T*);
    CHECK_SAME_TYPE(typename C::const_iterator, const T*);
    test_iterators<C>();

    CHECK_SAME_TYPE(typename C::pointer, T*);
    CHECK_SAME_TYPE(typename C::const_pointer, const T*);
    CHECK_SAME_TYPE(typename C::size_type, phi::usize);
    CHECK_SAME_TYPE(typename C::difference_type, phi::ptrdiff);
    CHECK_SAME_TYPE(typename C::reverse_iterator, phi::reverse_iterator<typename C::iterator>);
    CHECK_SAME_TYPE(typename C::const_reverse_iterator,
                    phi::reverse_iterator<typename C::const_iterator>);

    STATIC_REQUIRE(phi::is_signed<typename C::difference_type>::value);
    STATIC_REQUIRE(phi::is_unsigned<typename C::size_type>::value);
    CHECK_SAME_TYPE(typename C::difference_type,
                    typename phi::iterator_traits<typename C::iterator>::difference_type);
    CHECK_SAME_TYPE(typename C::difference_type,
                    typename phi::iterator_traits<typename C::const_iterator>::difference_type);
}

template <typename TypeT>
void test_array_types()
{
    test_array_types_impl<TypeT, 0u>();
    test_array_types_impl<TypeT, 1u>();
    test_array_types_impl<TypeT, 2u>();
    test_array_types_impl<TypeT, 3u>();
    test_array_types_impl<TypeT, 10u>();
    test_array_types_impl<TypeT, 42u>();
}

TEST_CASE("array types")
{
    test_array_types<bool>();
    test_array_types<char>();
    test_array_types<signed char>();
    test_array_types<unsigned char>();
    test_array_types<short>();
    test_array_types<unsigned short>();
    test_array_types<int>();
    test_array_types<unsigned int>();
    test_array_types<long>();
    test_array_types<unsigned long>();
    test_array_types<long long>();
    test_array_types<unsigned long long>();
    test_array_types<float>();
    test_array_types<double>();
    test_array_types<long double>();
    test_array_types<char8_t>();
    test_array_types<char16_t>();
    test_array_types<char32_t>();
    test_array_types<wchar_t>();

    test_array_types<phi::boolean>();
    test_array_types<phi::integer<signed char>>();
    test_array_types<phi::integer<unsigned char>>();
    test_array_types<phi::integer<short>>();
    test_array_types<phi::integer<unsigned short>>();
    test_array_types<phi::integer<int>>();
    test_array_types<phi::integer<unsigned int>>();
    test_array_types<phi::integer<long>>();
    test_array_types<phi::integer<unsigned long>>();
    test_array_types<phi::integer<long long>>();
    test_array_types<phi::integer<unsigned long long>>();
    test_array_types<phi::floating_point<float>>();
    test_array_types<phi::floating_point<double>>();
    test_array_types<phi::floating_point<long double>>();

    test_array_types<int*>();
    test_array_types<const int*>();

    test_array_types<NoDefault>();
}

PHI_MSVC_SUPPRESS_WARNING_POP()
PHI_CLANG_AND_GCC_SUPPRESS_WARNING_POP()
