#include <phi/test/test_macros.hpp>

#include "constexpr_helper.hpp"
#include <phi/compiler_support/nodiscard.hpp>
#include <phi/compiler_support/warning.hpp>
#include <phi/core/flat_ptr.hpp>
#include <phi/core/move.hpp>
#include <phi/core/observer_ptr.hpp>
#include <phi/core/scope_ptr.hpp>
#include <phi/math/vector2.hpp>
#include <phi/type_traits/is_copy_assignable.hpp>
#include <phi/type_traits/is_copy_constructible.hpp>
#include <phi/type_traits/is_default_constructible.hpp>
#include <phi/type_traits/is_move_assignable.hpp>
#include <phi/type_traits/is_move_constructible.hpp>

PHI_GCC_SUPPRESS_WARNING("-Wunused-result")

struct A
{
    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    PHI_NODISCARD bool f() const
    {
        return true;
    }
};

struct Base
{};

struct Derived : public Base
{};

PHI_GCC_SUPPRESS_WARNING_PUSH()
PHI_GCC_SUPPRESS_WARNING("-Wuseless-cast")

TEST_CASE("scope_ptr", "[Core][scope_ptr]")
{
    // scope_ptr
    SECTION("Layout")
    {
        STATIC_REQUIRE(sizeof(phi::scope_ptr<int>) == sizeof(int*));

#if PHI_HAS_WORKING_IS_DEFAULT_CONSTRUCTIBLE()
        STATIC_REQUIRE(phi::is_default_constructible<phi::scope_ptr<int>>::value);
#endif
        STATIC_REQUIRE_FALSE(phi::is_copy_constructible<phi::scope_ptr<int>>::value);
        STATIC_REQUIRE(phi::is_move_constructible<phi::scope_ptr<int>>::value);
        STATIC_REQUIRE_FALSE(phi::is_copy_assignable<phi::scope_ptr<int>>::value);
        STATIC_REQUIRE(phi::is_move_assignable<phi::scope_ptr<int>>::value);
    }

    SECTION("Type aliases")
    {
        CHECK_SAME_TYPE(phi::scope_ptr<int>::this_type, phi::scope_ptr<int>);
        CHECK_SAME_TYPE(phi::scope_ptr<int>::value_type, int);
        CHECK_SAME_TYPE(phi::scope_ptr<int>::reference, int&);
        CHECK_SAME_TYPE(phi::scope_ptr<int>::const_reference, const int&);
        CHECK_SAME_TYPE(phi::scope_ptr<int>::pointer, int*);
        CHECK_SAME_TYPE(phi::scope_ptr<int>::const_pointer, const int*);
    }

    SECTION("scope_ptr()")
    {
        phi::scope_ptr<int> ptr;

        CHECK(ptr.get() == nullptr);
        CHECK_FALSE(ptr);

        phi::scope_ptr<int> ptr2{};

        CHECK(ptr2.get() == nullptr);
        CHECK_FALSE(ptr2);
    }

    SECTION("scope_ptr(nullptr_t)")
    {
        phi::scope_ptr<int> ptr(nullptr);

        CHECK(ptr.get() == nullptr);
        CHECK_FALSE(ptr);

        phi::scope_ptr<int> ptr2{nullptr};

        CHECK(ptr2.get() == nullptr);
        CHECK_FALSE(ptr2);
    }

    SECTION("scope_ptr(TypeT*)")
    {
        int*                raw_ptr = new int(23);
        phi::scope_ptr<int> ptr(raw_ptr);

        REQUIRE(ptr);
        CHECK(ptr.get() == raw_ptr);
        CHECK(*ptr == 23);

        *raw_ptr = 19;

        CHECK(*ptr == 19);
    }

    SECTION("scope_ptr(OtherT*)")
    {
        Derived*             raw_ptr = new Derived;
        phi::scope_ptr<Base> ptr(raw_ptr);

        REQUIRE(ptr);
        CHECK(ptr.get() == raw_ptr);
    }

    SECTION("scope_ptr(scope_ptr&&)")
    {
        int* raw_ptr = new int(21);

        phi::scope_ptr<int> base(raw_ptr);
        phi::scope_ptr<int> ptr(phi::move(base));

        CHECK(ptr);
        CHECK(ptr.get() == raw_ptr);
    }

    SECTION("scope_ptr(not_null_scope_ptr&&)")
    {
        int* raw_ptr = new int(33);

        phi::not_null_scope_ptr<int> not_null(raw_ptr);
        phi::scope_ptr<int>          ptr(phi::move(not_null));

        REQUIRE(ptr);
        CHECK(ptr.get() == raw_ptr);
    }

    SECTION("operator=(scope_ptr&&)")
    {
        int* raw_ptr = new int(16);

        phi::scope_ptr<int> base(raw_ptr);
        phi::scope_ptr<int> ptr;

        ptr = phi::move(base);

        CHECK(ptr);
        CHECK(ptr.get() == raw_ptr);

        int* raw_ptr2 = new int(12);

        phi::scope_ptr<int> ptr2(raw_ptr2);

        ptr = phi::move(ptr2);

        CHECK(ptr);
        CHECK(ptr.get() == raw_ptr2);

        ptr = phi::move(ptr);

        CHECK(ptr);
        CHECK(ptr.get() == raw_ptr2);
    }

    SECTION("operator=(not_null_scope_ptr&&)")
    {
        int* raw_ptr = new int(21);

        phi::not_null_scope_ptr<int> not_null(raw_ptr);
        phi::scope_ptr<int>          ptr;

        ptr = phi::move(not_null);

        REQUIRE(ptr);
        CHECK(ptr.get() == raw_ptr);
    }

    SECTION("operator=(TypeT*)")
    {
        int* raw_ptr = new int(21);

        phi::scope_ptr<int> ptr;

        ptr = raw_ptr;

        CHECK(ptr);
        CHECK(ptr.get() == raw_ptr);

        int* raw_ptr2 = new int(22);

        ptr = raw_ptr2;

        CHECK(ptr);
        CHECK(ptr.get() == raw_ptr2);

        ptr = raw_ptr2;

        CHECK(ptr);
        CHECK(ptr.get() == raw_ptr2);
    }

    SECTION("operator=(OtherT*)")
    {
        Derived* raw_ptr = new Derived();

        phi::scope_ptr<Base> ptr;

        ptr = raw_ptr;

        CHECK(ptr);
        CHECK(ptr.get() == raw_ptr);

        Derived* raw_ptr2 = new Derived();

        ptr = raw_ptr2;

        CHECK(ptr);
        CHECK(ptr.get() == raw_ptr2);
    }

    SECTION("operator=(nullptr_t)")
    {
        phi::scope_ptr<int> ptr;

        ptr = nullptr;

        CHECK_FALSE(ptr);
        CHECK(ptr.get() == nullptr);

        ptr = new int(10);

        ptr = nullptr;

        CHECK_FALSE(ptr);
        CHECK(ptr.get() == nullptr);
    }

    SECTION("clear")
    {
        phi::scope_ptr<int> ptr(new int(25));

        ptr.clear();

        CHECK_FALSE(ptr);
        CHECK(ptr.get() == nullptr);
    }

    SECTION("leak_ptr")
    {
        int*                raw_ptr = new int(16);
        phi::scope_ptr<int> ptr(raw_ptr);

        int* leaked_ptr = ptr.leak_ptr();

        CHECK(leaked_ptr == raw_ptr);
        CHECK_FALSE(ptr);
        CHECK(ptr.get() == nullptr);

        delete leaked_ptr;
    }

    SECTION("release_not_null")
    {
        int*                raw_ptr = new int(21);
        phi::scope_ptr<int> ptr(raw_ptr);

        phi::not_null_scope_ptr<int> not_null = ptr.release_not_null();

        CHECK(not_null.get() == raw_ptr);
    }

    SECTION("reset")
    {
        phi::scope_ptr<int> ptr(new int(99));
        int*                raw_ptr = new int(1);

        ptr.reset(raw_ptr);

        CHECK(ptr);
        CHECK(ptr.get() == raw_ptr);

        int* raw_ptr2 = new int(21);

        ptr.reset(raw_ptr2);

        CHECK(ptr);
        CHECK(ptr.get() == raw_ptr2);

        ptr.reset(raw_ptr2);

        CHECK(ptr);
        CHECK(ptr.get() == raw_ptr2);

        ptr.reset();

        CHECK_FALSE(ptr);
        CHECK(ptr.get() == nullptr);

        ptr.reset(nullptr);

        CHECK_FALSE(ptr);
        CHECK(ptr.get() == nullptr);

        ptr = new int(21);

        ptr.reset(nullptr);

        CHECK_FALSE(ptr);
        CHECK(ptr.get() == nullptr);
    }

    SECTION("reset(OtherT*)")
    {
        Base*                raw_base = new Base();
        phi::scope_ptr<Base> base_ptr(raw_base);

        CHECK(base_ptr);
        CHECK(base_ptr.get() == raw_base);

        base_ptr.reset(nullptr);

        CHECK_FALSE(base_ptr);
        CHECK(base_ptr.get() == nullptr);

        Derived* raw_derived = new Derived();
        base_ptr.reset(raw_derived);

        CHECK(base_ptr);
        CHECK(base_ptr.get() == raw_derived);

        base_ptr.reset(raw_derived);

        CHECK(base_ptr);
        CHECK(base_ptr.get() == raw_derived);
    }

    SECTION("swap")
    {
        int* raw_ptr1 = new int(1);
        int* raw_ptr2 = new int(2);

        phi::scope_ptr<int> ptr1(raw_ptr1);
        phi::scope_ptr<int> ptr2(raw_ptr2);

        ptr1.swap(ptr2);

        REQUIRE(ptr1);
        REQUIRE(ptr2);

        CHECK(ptr1.get() == raw_ptr2);
        CHECK(ptr2.get() == raw_ptr1);

        phi::swap(ptr1, ptr2);

        REQUIRE(ptr1);
        REQUIRE(ptr2);

        CHECK(ptr1.get() == raw_ptr1);
        CHECK(ptr2.get() == raw_ptr2);
    }

    SECTION("operator boolean")
    {
        phi::scope_ptr<int> false_ptr;
        phi::scope_ptr<int> true_ptr(new int(9));

        CHECK_FALSE(static_cast<phi::boolean>(false_ptr));
        CHECK(static_cast<phi::boolean>(true_ptr));
    }

    SECTION("operator TypeT*")
    {
        int*                raw_ptr = new int(12);
        phi::scope_ptr<int> ptr(raw_ptr);

        int* new_ptr = static_cast<int*>(ptr);

        CHECK(new_ptr == raw_ptr);

        int*                      const_raw_ptr = new int(22);
        const phi::scope_ptr<int> const_ptr{const_raw_ptr};

        const int* new_const_ptr = static_cast<const int*>(const_ptr);

        CHECK(new_const_ptr == const_raw_ptr);
    }

    SECTION("operator->")
    {
        phi::scope_ptr<A> ptr(new A);

        CHECK(ptr->f());

        const phi::scope_ptr<A> const_ptr{new A};

        CHECK(const_ptr->f());
    }

    SECTION("operator*")
    {
        int*                raw_ptr = new int(0);
        phi::scope_ptr<int> ptr(raw_ptr);

        CHECK(*ptr == 0);

        *raw_ptr = 12;

        CHECK(*ptr == 12);

        *ptr = 9;

        CHECK(*ptr == 9);
        CHECK(*raw_ptr == 9);

        const phi::scope_ptr<A> const_ptr{new A};

        const A& a_ref = *const_ptr;

        CHECK(a_ref.f());
    }

    SECTION("operator==")
    {
        int* raw_ptr1 = new int(1);
        int* raw_ptr2 = new int(2);

        phi::scope_ptr<int> ptr1(raw_ptr1);
        phi::scope_ptr<int> ptr2(raw_ptr2);
        phi::scope_ptr<int> null;

        CHECK_FALSE(ptr1 == ptr2);
        CHECK_FALSE(ptr1 == null);
        CHECK_FALSE(ptr2 == null);

        CHECK_FALSE(ptr1 == nullptr);
        CHECK_FALSE(ptr2 == nullptr);
        CHECK(null == nullptr);

        CHECK_FALSE(nullptr == ptr1);
        CHECK_FALSE(nullptr == ptr2);
        CHECK(nullptr == null);

        ptr2 = raw_ptr1;

        CHECK(ptr1 == ptr2);

        // Need to leak the pointer otherwise we get a double free
        (void)ptr2.leak_ptr();
    }

    SECTION("operator== with plain pointer")
    {
        int* raw_ptr1 = new int(1);
        int* raw_ptr2 = new int(2);

        phi::scope_ptr<int> null_ptr;
        phi::scope_ptr<int> ptr1(raw_ptr1);
        phi::scope_ptr<int> ptr2(raw_ptr2);

        CHECK_FALSE(null_ptr == raw_ptr1);
        CHECK_FALSE(null_ptr == raw_ptr2);

        CHECK(ptr1 == raw_ptr1);
        CHECK_FALSE(ptr1 == raw_ptr2);

        CHECK_FALSE(ptr2 == raw_ptr1);
        CHECK(ptr2 == raw_ptr2);

        CHECK_FALSE(raw_ptr1 == null_ptr);
        CHECK_FALSE(raw_ptr2 == null_ptr);

        CHECK(raw_ptr1 == ptr1);
        CHECK_FALSE(raw_ptr2 == ptr1);

        CHECK_FALSE(raw_ptr1 == ptr2);
        CHECK(raw_ptr2 == ptr2);
    }

    SECTION("operator!=")
    {
        int* raw_ptr1 = new int(1);
        int* raw_ptr2 = new int(2);

        phi::scope_ptr<int> ptr1(raw_ptr1);
        phi::scope_ptr<int> ptr2(raw_ptr2);
        phi::scope_ptr<int> null;

        CHECK(ptr1 != ptr2);
        CHECK(ptr1 != null);
        CHECK(ptr2 != null);

        CHECK(ptr1 != nullptr);
        CHECK(ptr2 != nullptr);
        CHECK_FALSE(null != nullptr);

        CHECK(nullptr != ptr1);
        CHECK(nullptr != ptr2);
        CHECK_FALSE(nullptr != null);

        ptr2 = raw_ptr1;

        CHECK_FALSE(ptr1 != ptr2);

        // Need to leak the pointer otherwise we get a double free
        (void)ptr2.leak_ptr();
    }

    SECTION("operator!= with plain pointer")
    {
        int* raw_ptr1 = new int(1);
        int* raw_ptr2 = new int(2);

        phi::scope_ptr<int> null_ptr;
        phi::scope_ptr<int> ptr1(raw_ptr1);
        phi::scope_ptr<int> ptr2(raw_ptr2);

        CHECK(null_ptr != raw_ptr1);
        CHECK(null_ptr != raw_ptr2);

        CHECK_FALSE(ptr1 != raw_ptr1);
        CHECK(ptr1 != raw_ptr2);

        CHECK(ptr2 != raw_ptr1);
        CHECK_FALSE(ptr2 != raw_ptr2);

        CHECK(raw_ptr1 != null_ptr);
        CHECK(raw_ptr2 != null_ptr);

        CHECK_FALSE(raw_ptr1 != ptr1);
        CHECK(raw_ptr2 != ptr1);

        CHECK(raw_ptr1 != ptr2);
        CHECK_FALSE(raw_ptr2 != ptr2);
    }

    SECTION("make_scope")
    {
        phi::scope_ptr<int> int_ptr  = phi::make_scope<int>();
        phi::scope_ptr<int> int_ptr2 = phi::make_scope<int>(3);

        CHECK(*int_ptr2 == 3);

        phi::scope_ptr<phi::vector2i32> vec2_ptr = phi::make_scope<phi::vector2i32>(3, 12);

        CHECK((vec2_ptr->x == 3));
        CHECK((vec2_ptr->y == 12));
    }

    // not_null_scope_ptr
    SECTION("Layout")
    {
        STATIC_REQUIRE(sizeof(phi::not_null_scope_ptr<int>) == sizeof(int*));

#if PHI_HAS_WORKING_IS_DEFAULT_CONSTRUCTIBLE()
        STATIC_REQUIRE_FALSE(phi::is_default_constructible<phi::not_null_scope_ptr<int>>::value);
#endif
        STATIC_REQUIRE_FALSE(phi::is_copy_constructible<phi::not_null_scope_ptr<int>>::value);
        STATIC_REQUIRE(phi::is_move_constructible<phi::not_null_scope_ptr<int>>::value);
        STATIC_REQUIRE_FALSE(phi::is_copy_assignable<phi::not_null_scope_ptr<int>>::value);
        STATIC_REQUIRE(phi::is_move_assignable<phi::not_null_scope_ptr<int>>::value);
    }

    SECTION("Type aliases")
    {
        CHECK_SAME_TYPE(phi::not_null_scope_ptr<int>::this_type, phi::not_null_scope_ptr<int>);
        CHECK_SAME_TYPE(phi::not_null_scope_ptr<int>::value_type, int);
        CHECK_SAME_TYPE(phi::not_null_scope_ptr<int>::reference, int&);
        CHECK_SAME_TYPE(phi::not_null_scope_ptr<int>::const_reference, const int&);
        CHECK_SAME_TYPE(phi::not_null_scope_ptr<int>::pointer, int*);
        CHECK_SAME_TYPE(phi::not_null_scope_ptr<int>::const_pointer, const int*);
    }

    SECTION("not_null_scope_ptr(TypeT*)")
    {
        int*                         raw_ptr = new int(23);
        phi::not_null_scope_ptr<int> ptr(raw_ptr);

        CHECK(ptr.get() == raw_ptr);
        CHECK(*ptr == 23);

        *raw_ptr = 19;

        CHECK(*ptr == 19);
    }

    SECTION("not_null_scope_ptr(OtherT*)")
    {
        Derived*                      raw_ptr = new Derived();
        phi::not_null_scope_ptr<Base> ptr(raw_ptr);

        CHECK(ptr.get() == raw_ptr);
    }

    SECTION("not_null_scope_ptr(not_null_scope_ptr&&)")
    {
        int* raw_ptr = new int(21);

        phi::not_null_scope_ptr<int> base(raw_ptr);
        phi::not_null_scope_ptr<int> ptr(phi::move(base));

        CHECK(ptr.get() == raw_ptr);
    }

    SECTION("not_null_scope_ptr(not_null_scope_ptr<OtherT>&&)")
    {
        Derived* raw_derived = new Derived();

        phi::not_null_scope_ptr<Derived> derived_ptr{raw_derived};
        phi::not_null_scope_ptr<Base>    base_ptr{phi::move(derived_ptr)};

        CHECK(base_ptr.get() == raw_derived);
    }

    SECTION("operator=(not_null_scope_ptr&&)")
    {
        int* raw_ptr = new int(16);

        phi::not_null_scope_ptr<int> base(raw_ptr);
        phi::not_null_scope_ptr<int> ptr(new int(12));

        ptr = phi::move(base);

        CHECK(ptr.get() == raw_ptr);

        int* raw_ptr2 = new int(12);

        phi::not_null_scope_ptr<int> ptr2(raw_ptr2);

        ptr = phi::move(ptr2);

        CHECK(ptr.get() == raw_ptr2);

        ptr = phi::move(ptr);

        CHECK(ptr.get() == raw_ptr2);
    }

    SECTION("operator=(not_null_scope_ptr<OtherT>&&)")
    {
        Derived*                         raw_derived = new Derived();
        phi::not_null_scope_ptr<Derived> derived_ptr{raw_derived};
        phi::not_null_scope_ptr<Base>    base_ptr{new Base()};

        base_ptr = phi::move(derived_ptr);

        CHECK(base_ptr.get() == raw_derived);

        base_ptr = phi::move(base_ptr);

        CHECK(base_ptr.get() == raw_derived);
    }

    SECTION("operator=(TypeT*)")
    {
        int* raw_ptr = new int(21);

        phi::not_null_scope_ptr<int> ptr(new int(23));

        ptr = raw_ptr;

        CHECK(ptr.get() == raw_ptr);

        int* raw_ptr2 = new int(22);

        ptr = raw_ptr2;

        CHECK(ptr.get() == raw_ptr2);

        ptr = raw_ptr2;

        CHECK(ptr.get() == raw_ptr2);
    }

    SECTION("operator=(OtherT*)")
    {
        Derived* raw_ptr = new Derived();

        phi::not_null_scope_ptr<Base> ptr(new Base());

        ptr = raw_ptr;

        CHECK(ptr.get() == raw_ptr);

        Derived* raw_ptr2 = new Derived();

        ptr = raw_ptr2;

        CHECK(ptr.get() == raw_ptr2);
    }

    SECTION("leak_ptr")
    {
        int*                         raw_ptr = new int(16);
        phi::not_null_scope_ptr<int> ptr(raw_ptr);

        int* leaked_ptr = ptr.leak_ptr();

        CHECK(leaked_ptr == raw_ptr);

        delete leaked_ptr;
    }

    SECTION("reset")
    {
        phi::not_null_scope_ptr<int> ptr(new int(99));
        int*                         raw_ptr = new int(1);

        ptr.reset(raw_ptr);

        CHECK(ptr.get() == raw_ptr);

        int* raw_ptr2 = new int(21);
        ptr.reset(raw_ptr2);

        CHECK(ptr.get() == raw_ptr2);

        ptr.reset(raw_ptr2);

        CHECK(ptr.get() == raw_ptr2);
    }

    SECTION("reset(OtherT*)")
    {
        phi::not_null_scope_ptr<Base> ptr{new Derived()};

        Derived* raw_ptr2 = new Derived();
        ptr.reset(raw_ptr2);

        CHECK(ptr.get() == raw_ptr2);

        ptr.reset(raw_ptr2);

        CHECK(ptr.get() == raw_ptr2);
    }

    SECTION("swap")
    {
        int* raw_ptr1 = new int(1);
        int* raw_ptr2 = new int(2);

        phi::not_null_scope_ptr<int> ptr1(raw_ptr1);
        phi::not_null_scope_ptr<int> ptr2(raw_ptr2);

        ptr1.swap(ptr2);

        CHECK(ptr1.get() == raw_ptr2);
        CHECK(ptr2.get() == raw_ptr1);

        phi::swap(ptr1, ptr2);

        CHECK(ptr1.get() == raw_ptr1);
        CHECK(ptr2.get() == raw_ptr2);
    }

    SECTION("operator TypeT*")
    {
        int*                         raw_ptr = new int(12);
        phi::not_null_scope_ptr<int> ptr(raw_ptr);

        int* new_ptr = static_cast<int*>(ptr);

        CHECK(new_ptr == raw_ptr);

        int*                               raw_const_ptr = new int(21);
        const phi::not_null_scope_ptr<int> const_ptr{raw_const_ptr};

        CHECK(static_cast<const int*>(const_ptr) == raw_const_ptr);
    }

    SECTION("operator->")
    {
        phi::not_null_scope_ptr<A> ptr{new A};
        CHECK(ptr->f());

        const phi::not_null_scope_ptr<A> const_ptr{new A};
        CHECK(const_ptr->f());
    }

    SECTION("operator*")
    {
        int*                         raw_ptr = new int(0);
        phi::not_null_scope_ptr<int> ptr(raw_ptr);

        CHECK(*ptr == 0);

        *raw_ptr = 12;

        CHECK(*ptr == 12);

        *ptr = 9;

        CHECK(*ptr == 9);
        CHECK(*raw_ptr == 9);

        const phi::not_null_scope_ptr<A> const_ptr{new A()};
        const A&                         const_ref = *const_ptr;
        CHECK(const_ref.f());
    }

    SECTION("operator==")
    {
        int* raw_ptr1 = new int(1);
        int* raw_ptr2 = new int(2);
        int* raw_ptr3 = new int(3);

        phi::not_null_scope_ptr<int> ptr1(raw_ptr1);
        phi::not_null_scope_ptr<int> ptr2(raw_ptr2);
        phi::not_null_scope_ptr<int> ptr3(raw_ptr3);

        CHECK_FALSE(ptr1 == ptr2);
        CHECK_FALSE(ptr1 == ptr3);
        CHECK_FALSE(ptr2 == ptr3);

        ptr2 = raw_ptr1;

        CHECK(ptr1 == ptr2);

        // Need to leak the pointer otherwise we get a double free
        (void)ptr2.leak_ptr();
    }

    SECTION("operator== with plain pointer")
    {
        int* raw_ptr1 = new int(1);
        int* raw_ptr2 = new int(2);

        phi::not_null_scope_ptr<int> ptr1(raw_ptr1);
        phi::not_null_scope_ptr<int> ptr2(raw_ptr2);

        CHECK(ptr1 == raw_ptr1);
        CHECK_FALSE(ptr1 == raw_ptr2);

        CHECK_FALSE(ptr2 == raw_ptr1);
        CHECK(ptr2 == raw_ptr2);

        CHECK(raw_ptr1 == ptr1);
        CHECK_FALSE(raw_ptr2 == ptr1);

        CHECK_FALSE(raw_ptr1 == ptr2);
        CHECK(raw_ptr2 == ptr2);
    }

    SECTION("operator!=")
    {
        int* raw_ptr1 = new int(1);
        int* raw_ptr2 = new int(2);
        int* raw_ptr3 = new int(3);

        phi::not_null_scope_ptr<int> ptr1(raw_ptr1);
        phi::not_null_scope_ptr<int> ptr2(raw_ptr2);
        phi::not_null_scope_ptr<int> ptr3(raw_ptr3);

        CHECK(ptr1 != ptr2);
        CHECK(ptr1 != ptr3);
        CHECK(ptr2 != ptr3);

        ptr2 = raw_ptr1;

        CHECK_FALSE(ptr1 != ptr2);

        // Need to leak the pointer otherwise we get a double free
        (void)ptr2.leak_ptr();
    }

    SECTION("operator!= with plain pointer")
    {
        int* raw_ptr1 = new int(1);
        int* raw_ptr2 = new int(2);

        phi::not_null_scope_ptr<int> ptr1(raw_ptr1);
        phi::not_null_scope_ptr<int> ptr2(raw_ptr2);

        CHECK_FALSE(ptr1 != raw_ptr1);
        CHECK(ptr1 != raw_ptr2);

        CHECK(ptr2 != raw_ptr1);
        CHECK_FALSE(ptr2 != raw_ptr2);

        CHECK_FALSE(raw_ptr1 != ptr1);
        CHECK(raw_ptr2 != ptr1);

        CHECK(raw_ptr1 != ptr2);
        CHECK_FALSE(raw_ptr2 != ptr2);
    }

    SECTION("make_not_null_scope")
    {
        phi::not_null_scope_ptr<int> int_ptr  = phi::make_not_null_scope<int>();
        phi::not_null_scope_ptr<int> int_ptr2 = phi::make_not_null_scope<int>(3);

        CHECK(*int_ptr2 == 3);

        phi::not_null_scope_ptr<phi::vector2i32> vec2_ptr =
                phi::make_not_null_scope<phi::vector2i32>(3, 12);

        CHECK((vec2_ptr->x == 3));
        CHECK((vec2_ptr->y == 12));
    }
}

TEST_CASE("scope_ptr - flat")
{
    int*                raw_ptr = new int(21);
    phi::scope_ptr<int> ptr{raw_ptr};

    phi::flat_ptr flat = ptr.flat();

    CHECK(ptr.get() == flat.get());
    CHECK(flat.get() == raw_ptr);
}

TEST_CASE("scope_ptr - flat - const")
{
    int*                      raw_ptr = new int(21);
    const phi::scope_ptr<int> ptr{raw_ptr};

    const phi::flat_ptr flat = ptr.flat();

    CHECK(ptr.get() == flat.get());
    CHECK(flat.get() == raw_ptr);
}

TEST_CASE("scope_ptr - not_null_flat")
{
    int*                raw_ptr = new int(21);
    phi::scope_ptr<int> ptr{raw_ptr};

    phi::not_null_flat_ptr flat = ptr.not_null_flat();

    CHECK(ptr.get() == flat.get());
    CHECK(flat.get() == raw_ptr);
}

TEST_CASE("scope_ptr - not_null_flat - const")
{
    int*                      raw_ptr = new int(21);
    const phi::scope_ptr<int> ptr{raw_ptr};

    const phi::not_null_flat_ptr flat = ptr.not_null_flat();

    CHECK(ptr.get() == flat.get());
    CHECK(flat.get() == raw_ptr);
}

TEST_CASE("not_null_scope_ptr - not_null_flat")
{
    int*                         raw_ptr = new int(21);
    phi::not_null_scope_ptr<int> ptr{raw_ptr};

    phi::not_null_flat_ptr flat = ptr.not_null_flat();

    CHECK(ptr.get() == flat.get());
    CHECK(flat.get() == raw_ptr);
}

TEST_CASE("not_null_scope_ptr - not_null_flat - const")
{
    int*                               raw_ptr = new int(21);
    const phi::not_null_scope_ptr<int> ptr{raw_ptr};

    const phi::not_null_flat_ptr flat = ptr.not_null_flat();

    CHECK(ptr.get() == flat.get());
    CHECK(flat.get() == raw_ptr);
}

TEST_CASE("scope_ptr - observer")
{
    int*                raw_ptr = new int(21);
    phi::scope_ptr<int> ptr{raw_ptr};

    phi::observer_ptr<int> observer = ptr.observer();

    CHECK(ptr.get() == observer.get());
    CHECK(observer.get() == raw_ptr);
}

TEST_CASE("scope_ptr - observer - const")
{
    int*                      raw_ptr = new int(21);
    const phi::scope_ptr<int> ptr{raw_ptr};

    phi::observer_ptr<const int> observer = ptr.observer();

    CHECK(ptr.get() == observer.get());
    CHECK(observer.get() == raw_ptr);
}

TEST_CASE("scope_ptr - not_null_observer")
{
    int*                raw_ptr = new int(21);
    phi::scope_ptr<int> ptr{raw_ptr};

    phi::not_null_observer_ptr<int> observer = ptr.not_null_observer();

    CHECK(ptr.get() == observer.get());
    CHECK(observer.get() == raw_ptr);
}

TEST_CASE("scope_ptr - not_null_observer - const")
{
    int*                      raw_ptr = new int(21);
    const phi::scope_ptr<int> ptr{raw_ptr};

    phi::not_null_observer_ptr<const int> observer = ptr.not_null_observer();

    CHECK(ptr.get() == observer.get());
    CHECK(observer.get() == raw_ptr);
}

TEST_CASE("not_null_scope_ptr - not_null_observer")
{
    int*                         raw_ptr = new int(21);
    phi::not_null_scope_ptr<int> ptr{raw_ptr};

    phi::not_null_observer_ptr<int> observer = ptr.not_null_observer();

    CHECK(ptr.get() == observer.get());
    CHECK(observer.get() == raw_ptr);
}

TEST_CASE("not_null_scope_ptr - not_null_observer - const")
{
    int*                               raw_ptr = new int(21);
    const phi::not_null_scope_ptr<int> ptr{raw_ptr};

    const phi::not_null_observer_ptr<const int> observer = ptr.not_null_observer();

    CHECK(ptr.get() == observer.get());
    CHECK(observer.get() == raw_ptr);
}

TEST_CASE("scope_ptr - hash")
{
    int*                raw_ptr = new int(21);
    phi::scope_ptr<int> ptr{raw_ptr};

    const phi::size_t ptr_hash     = std::hash<phi::scope_ptr<int>>{}(ptr);
    const phi::size_t raw_ptr_hash = std::hash<int*>{}(raw_ptr);

    CHECK(ptr_hash == raw_ptr_hash);
}

TEST_CASE("not_null_scope_ptr - hash")
{
    int*                         raw_ptr = new int(21);
    phi::not_null_scope_ptr<int> ptr{raw_ptr};

    const phi::size_t ptr_hash     = std::hash<phi::not_null_scope_ptr<int>>{}(ptr);
    const phi::size_t raw_ptr_hash = std::hash<int*>{}(raw_ptr);

    CHECK(ptr_hash == raw_ptr_hash);
}

PHI_GCC_SUPPRESS_WARNING_POP()
