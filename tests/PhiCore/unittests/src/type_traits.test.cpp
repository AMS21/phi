#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/warning.hpp>
#include <phi/type_traits.hpp>

// Very basic tests that all the type traits are actually included.
// Functional testing is done in separate files

PHI_CLANG_SUPPRESS_WARNING("-Wunneeded-member-function")

struct S
{
    float operator()(int);
};

PHI_CLANG_SUPPRESS_WARNING_POP()

// NOLINTNEXTLINE(readability-function-size)
TEST_CASE("type_traits")
{
    // add_const
    CHECK_SAME_TYPE(typename phi::add_const<int>::type, const int);
    CHECK_SAME_TYPE(phi::add_const_t<int>, const int);

    // add_cv
    CHECK_SAME_TYPE(typename phi::add_cv<int>::type, const volatile int);
    CHECK_SAME_TYPE(phi::add_cv_t<int>, const volatile int);

    // add_lvalue_reference
    CHECK_SAME_TYPE(typename phi::add_lvalue_reference<int>::type, int&);
    CHECK_SAME_TYPE(phi::add_lvalue_reference_t<int>, int&);

    // add_member_const
    CHECK_SAME_TYPE(typename phi::add_member_const<void (class_type::*)()>::type,
                    void(class_type::* const)());
    CHECK_SAME_TYPE(phi::add_member_const_t<void (class_type::*)()>, void(class_type::* const)());

    // add_pointer
    CHECK_SAME_TYPE(typename phi::add_pointer<int>::type, int*);
    CHECK_SAME_TYPE(phi::add_pointer_t<int>, int*);

    // add_rvalue_reference
    CHECK_SAME_TYPE(typename phi::add_rvalue_reference<int>::type, int&&);
    CHECK_SAME_TYPE(phi::add_rvalue_reference_t<int>, int&&);

    // add_volatile
    CHECK_SAME_TYPE(typename phi::add_volatile<int>::type, volatile int);
    CHECK_SAME_TYPE(phi::add_volatile_t<int>, volatile int);

    // aligned_storage
    using T1 = phi::aligned_storage<1>::type;
    using T2 = phi::aligned_storage_t<1>;
    CHECK_SAME_TYPE(T1, T2);

    // aligned_union
    using U1 = phi::aligned_union<1, int, int>::type;
    using U2 = phi::aligned_union_t<1, int, int>;
    CHECK_SAME_TYPE(U1, U2);

    // alignment_of
    STATIC_REQUIRE(phi::alignment_of<class_type>::value == 1);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::alignment_of_v<class_type> == 1);
#endif

    // bool_constant
#if PHI_HAS_FEATURE_ALIAS_TEMPLATES()
    STATIC_REQUIRE(phi::bool_constant<true>::value);
    STATIC_REQUIRE_FALSE(phi::bool_constant<false>::value);
#endif

    // common_type
    //CHECK_SAME_TYPE(typename phi::common_type<int, int>::type, int);
    //CHECK_SAME_TYPE(phi::common_type_t<int, int>, int);

    // conditional
    CHECK_SAME_TYPE(typename phi::conditional<true, int, double>::type, int);
    CHECK_SAME_TYPE(phi::conditional_t<true, int, double>, int);

    // conjunction
    STATIC_REQUIRE(phi::conjunction<>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::conjunction_v<>);
#endif

    // copy_const
    CHECK_SAME_TYPE(typename phi::copy_const<const int, float>::type, const float);
    CHECK_SAME_TYPE(phi::copy_const_t<const int, float>, const float);

    // copy_cv
    CHECK_SAME_TYPE(typename phi::copy_cv<const volatile int, float>::type, const volatile float);
    CHECK_SAME_TYPE(phi::copy_cv_t<const volatile int, float>, const volatile float);

    // copy_volatile
    CHECK_SAME_TYPE(typename phi::copy_volatile<volatile int, float>::type, volatile float);
    CHECK_SAME_TYPE(phi::copy_volatile_t<volatile int, float>, volatile float);

    // decay
    CHECK_SAME_TYPE(typename phi::decay<const int>::type, int);
    CHECK_SAME_TYPE(phi::decay_t<const int>, int);

    // disable_if
    CHECK_SAME_TYPE(typename phi::disable_if<false>::type, void);
    CHECK_SAME_TYPE(phi::disable_if_t<false>, void);

    // disjunction
    STATIC_REQUIRE(phi::disjunction<phi::true_type>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::disjunction_v<phi::true_type>);
#endif

    // enable_if
    CHECK_SAME_TYPE(typename phi::enable_if<true>::type, void);
    CHECK_SAME_TYPE(phi::enable_if_t<true>, void);

    // extent
    STATIC_REQUIRE(phi::extent<int[1]>::value == 1);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::extent_v<int[1]> == 1);
#endif

    // false_t
    STATIC_REQUIRE_FALSE(phi::false_t<int>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::false_v<int>);
#endif

    // has_difference_type
    STATIC_REQUIRE_FALSE(phi::has_difference_type<int>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::has_difference_type_v<int>);
#endif

    // has_element_type
    STATIC_REQUIRE_FALSE(phi::has_element_type<int>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::has_element_type_v<int>);
#endif

    // has_unique_object_representations
#if PHI_HAS_WORKING_HAS_UNIQUE_OBJECT_REPRESENTATIONS()
    STATIC_REQUIRE(phi::has_unique_object_representations<unsigned>::value);
#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::has_unique_object_representations_v<unsigned>);
#    endif
#endif

    // has_value_type
    STATIC_REQUIRE_FALSE(phi::has_value_type<int>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::has_value_type_v<int>);
#endif

    // has_virtual_destructor
#if PHI_HAS_WORKING_HAS_VIRTUAL_DESTRUCTOR()
    STATIC_REQUIRE_FALSE(phi::has_virtual_destructor<int>::value);
#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::has_virtual_destructor_v<int>);
#    endif
#endif

    // integral_constant
    using two_t = phi::integral_constant<int, 2>;
    STATIC_REQUIRE(two_t::value == 2);
    STATIC_REQUIRE(phi::true_type::value);
    STATIC_REQUIRE_FALSE(phi::false_type::value);

    // invoke_result
    CHECK_SAME_TYPE(typename phi::invoke_result<S, int>::type, float);
    CHECK_SAME_TYPE(phi::invoke_result_t<S, int>, float);

    // is_abstract
#if PHI_HAS_WORKING_IS_ABSTRACT()
    STATIC_REQUIRE_FALSE(phi::is_abstract<void>::value);
#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_abstract_v<void>);
#    endif
#endif

    // is_aggregate
#if PHI_HAS_WORKING_IS_AGGREGATE()
    STATIC_REQUIRE(phi::is_aggregate<class_type>::value);
#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_aggregate_v<class_type>);
#    endif
#endif

    // is_any_of_rc
    STATIC_REQUIRE(phi::is_any_of_rc<int, int>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_any_of_rc_v<int, int>);
#endif

    // is_any_of_rcv
    STATIC_REQUIRE(phi::is_any_of_rcv<int, int>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_any_of_rcv_v<int, int>);
#endif

    // is_any_of_rcvref
    STATIC_REQUIRE(phi::is_any_of_rcvref<int, int>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_any_of_rcvref_v<int, int>);
#endif

    // is_any_of_rref
    STATIC_REQUIRE(phi::is_any_of_rref<int, int>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_any_of_rref_v<int, int>);
#endif

    // is_any_of_rv
    STATIC_REQUIRE(phi::is_any_of_rv<int, int>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_any_of_rv_v<int, int>);
#endif

    // is_any_of
    STATIC_REQUIRE(phi::is_any_of<int, int>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_any_of_v<int, int>);
#endif

    // is_arithmetic
    STATIC_REQUIRE(phi::is_arithmetic<int>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_arithmetic_v<int>);
#endif

    // is_array
    STATIC_REQUIRE(phi::is_array<int[]>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_array_v<int[]>);
#endif

    // is_assignable
    STATIC_REQUIRE(phi::is_assignable<int&, int&>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_assignable_v<int&, int&>);
#endif

    // is_base_of
#if PHI_HAS_WORKING_IS_BASE_OF()
    STATIC_REQUIRE(phi::is_base_of<base, derived>::value);
#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_base_of_v<base, derived>);
#    endif
#endif

    // is_bool
    STATIC_REQUIRE(phi::is_bool<bool>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_bool_v<bool>);
#endif

    // is_bounded_array
    STATIC_REQUIRE(phi::is_bounded_array<char[3]>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_bounded_array_v<char[3]>);
#endif

    // is_class
#if PHI_HAS_WORKING_IS_CLASS()
    STATIC_REQUIRE(phi::is_class<class_type>::value);
#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_class_v<class_type>);
#    endif
#endif

    // is_complete
    STATIC_REQUIRE(phi::is_complete<int>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_complete_v<int>);
#endif

    // is_complete_or_unbounded
    STATIC_REQUIRE(phi::is_complete_or_unbounded<int>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_complete_or_unbounded_v<int>);
#endif

    // is_complete_or_unbounded_void
    STATIC_REQUIRE(phi::is_complete_or_unbounded_void<int>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_complete_or_unbounded_void_v<int>);
#endif

    // is_complete_or_void
    STATIC_REQUIRE(phi::is_complete_or_void<int>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_complete_or_void_v<int>);
#endif

    // is_compound
    STATIC_REQUIRE(phi::is_compound<int&>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_compound_v<int&>);
#endif

    // is_const
    STATIC_REQUIRE(phi::is_const<const int>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_const_v<const int>);
#endif

    // is_constant_evaluated
#if PHI_SUPPORTS_IS_CONSTANT_EVALUATED()
    static_assert(phi::is_constant_evaluated(), "is_constant_evaluated");
#endif

    // is_constructible
#if PHI_HAS_WORKING_IS_CONSTRUCTIBLE()
    STATIC_REQUIRE(phi::is_constructible<int>::value);
#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_constructible_v<int>);
#    endif
#endif

    // is_copy_assignable
    STATIC_REQUIRE(phi::is_copy_assignable<int>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_copy_assignable_v<int>);
#endif

    // is_copy_constructible
#if PHI_HAS_WORKING_IS_COPY_CONSTRUCTIBLE()
    STATIC_REQUIRE(phi::is_copy_constructible<int>::value);
#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_copy_constructible_v<int>);
#    endif
#endif

    struct A
    {
        int a;
    };

    struct B
    {
        int b;
    };

    struct C : public A, B
    {};

#if PHI_HAS_WORKING_IS_CORRESPONDING_MEMBER()
    STATIC_REQUIRE(phi::is_corresponding_member(&C::a, &C::b));
#endif

    // is_default_constructible
#if PHI_HAS_WORKING_IS_DEFAULT_CONSTRUCTIBLE()
    STATIC_REQUIRE(phi::is_default_constructible<int>::value);
#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_default_constructible_v<int>);
#    endif
#endif

    // is_derived_from
#if PHI_HAS_WORKING_IS_DERIVED_FROM()
    STATIC_REQUIRE(phi::is_derived_from<derived, base>::value);
#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_derived_from_v<derived, base>);
#    endif
#endif

    // is_destructible
    STATIC_REQUIRE(phi::is_destructible<int>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_destructible_v<int>);
#endif

    // is_empty
#if PHI_HAS_WORKING_IS_EMPTY()
    STATIC_REQUIRE(phi::is_empty<empty>::value);
#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_empty_v<empty>);
#    endif
#endif

    // is_enum
#if PHI_HAS_WORKING_IS_ENUM()
    STATIC_REQUIRE(phi::is_enum<Enum>::value);
#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_enum_v<Enum>);
#    endif
#endif

    // is_final
#if PHI_HAS_WORKING_IS_FINAL()
    STATIC_REQUIRE(phi::is_final<final_type>::value);
#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_final_v<final_type>);
#    endif
#endif

    // is_floating_point
    STATIC_REQUIRE(phi::is_floating_point<float>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_floating_point_v<float>);
#endif

    // is_function
    STATIC_REQUIRE(phi::is_function<function_type>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_function_v<function_type>);
#endif

    // is_function_pointer
    STATIC_REQUIRE(phi::is_function_pointer<function_ptr>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_function_pointer_v<function_ptr>);
#endif

    // is_fundamental
    STATIC_REQUIRE(phi::is_fundamental<int>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_fundamental_v<int>);
#endif

    // is_implicitly_default_constructible
#if PHI_HAS_WORKING_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE()
    STATIC_REQUIRE(phi::is_implicitly_default_constructible<int>::value);
#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_implicitly_default_constructible_v<int>);
#    endif
#endif

    // is_integer
    STATIC_REQUIRE(phi::is_integer<int>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_integer_v<int>);
#endif

    // is_integral
    STATIC_REQUIRE(phi::is_integral<int>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_integral_v<int>);
#endif

    // is_invocable
#if PHI_HAS_WORKING_IS_INVOCABLE()
    STATIC_REQUIRE(phi::is_invocable<function_type>::value);
#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_invocable_v<function_type>);
#    endif
#endif

    // is_invocable_r
#if PHI_HAS_WORKING_IS_INVOCABLE()
    STATIC_REQUIRE(phi::is_invocable_r<void, function_type>::value);
#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_invocable_r_v<void, function_type>);
#    endif
#endif

    // is_layout_compatible
#if PHI_SUPPORTS_IS_LAYOUT_COMPATIBLE()
    STATIC_REQUIRE(phi::is_layout_compatible<void, void>::value);
#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_layout_compatible_v<void, void>);
#    endif
#endif

    // is_literal_type
#if PHI_HAS_WORKING_IS_LITERAL_TYPE()
    STATIC_REQUIRE(phi::is_literal_type<int>::value);
#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_literal_type_v<int>);
#    endif
#endif

    // is_lvalue_reference
    STATIC_REQUIRE(phi::is_lvalue_reference<int&>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_lvalue_reference_v<int&>);
#endif

    // is_member_function_pointer
    STATIC_REQUIRE(phi::is_member_function_pointer<member_function_ptr>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_member_function_pointer_v<member_function_ptr>);
#endif

    // is_member_object_pointer
    STATIC_REQUIRE(phi::is_member_object_pointer<member_object_ptr>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_member_object_pointer_v<member_object_ptr>);
#endif

    // is_member_pointer
    STATIC_REQUIRE(phi::is_member_pointer<member_function_ptr>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_member_pointer_v<member_function_ptr>);
#endif

    // is_move_assignable
    STATIC_REQUIRE(phi::is_move_assignable<int>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_move_assignable_v<int>);
#endif

    // is_move_constructible
#if PHI_HAS_WORKING_IS_MOVE_CONSTRUCTIBLE()
    STATIC_REQUIRE(phi::is_move_constructible<int>::value);
#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_move_constructible_v<int>);
#    endif
#endif

    // is_non_bool_integral
    STATIC_REQUIRE(phi::is_non_bool_integral<int>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_non_bool_integral_v<int>);
#endif

    // is_none_of_rc
    STATIC_REQUIRE(phi::is_none_of_rc<int, void>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_none_of_rc_v<int, void>);
#endif

    // is_none_of_rcv
    STATIC_REQUIRE(phi::is_none_of_rcv<int, void>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_none_of_rcv_v<int, void>);
#endif

    // is_none_of_rcvref
    STATIC_REQUIRE(phi::is_none_of_rcvref<int, void>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_none_of_rcvref_v<int, void>);
#endif

    // is_none_of_rref
    STATIC_REQUIRE(phi::is_none_of_rref<int, void>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_none_of_rref_v<int, void>);
#endif

    // is_none_of_rv
    STATIC_REQUIRE(phi::is_none_of_rv<int, void>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_none_of_rv_v<int, void>);
#endif

    // is_none_of
    STATIC_REQUIRE(phi::is_none_of<int, void>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_none_of_v<int, void>);
#endif

    // is_nothrow_assignable
    STATIC_REQUIRE(phi::is_nothrow_assignable<int&, int&>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_nothrow_assignable_v<int&, int&>);
#endif

    // is_nothrow_constructible
#if PHI_HAS_WORKING_IS_NOTHROW_CONSTRUCTIBLE()
    STATIC_REQUIRE(phi::is_nothrow_constructible<int>::value);
#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_nothrow_constructible_v<int>);
#    endif
#endif

    // is_nothrow_convertible
    STATIC_REQUIRE(phi::is_nothrow_convertible<int, double>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_nothrow_convertible_v<int, double>);
#endif

    // is_nothrow_copy_assignable
    STATIC_REQUIRE(phi::is_nothrow_copy_assignable<int>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_nothrow_copy_assignable_v<int>);
#endif

    // is_nothrow_copy_constructible
#if PHI_HAS_WORKING_IS_NOTHROW_COPY_CONSTRUCTIBLE()
    STATIC_REQUIRE(phi::is_nothrow_copy_constructible<int>::value);
#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_nothrow_copy_constructible_v<int>);
#    endif
#endif

    // is_nothrow_default_constructible
#if PHI_HAS_WORKING_IS_NOTHROW_DEFAULT_CONSTRUCTIBLE()
    STATIC_REQUIRE(phi::is_nothrow_default_constructible<int>::value);
#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_nothrow_default_constructible_v<int>);
#    endif
#endif

    // is_nothrow_destructible
    STATIC_REQUIRE(phi::is_nothrow_destructible<int>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_nothrow_destructible_v<int>);
#endif

    // is_nothrow_invocable
#if PHI_HAS_WORKING_IS_INVOCABLE()
    STATIC_REQUIRE_FALSE(phi::is_nothrow_invocable<function_type>::value);
#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_nothrow_invocable_v<function_type>);
#    endif
#endif

    // is_nothrow_invocable_r
#if PHI_HAS_WORKING_IS_INVOCABLE()
    STATIC_REQUIRE_FALSE(phi::is_nothrow_invocable_r<void, function_type>::value);
#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_nothrow_invocable_r_v<void, function_type>);
#    endif
#endif

    // is_nothrow_move_assignable
    STATIC_REQUIRE(phi::is_nothrow_move_assignable<int>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_nothrow_move_assignable_v<int>);
#endif

    // is_nothrow_move_constructible
    STATIC_REQUIRE(phi::is_nothrow_move_constructible<int>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_nothrow_move_constructible_v<int>);
#endif

    // is_nothrow_swappable
    STATIC_REQUIRE(phi::is_nothrow_swappable<int>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_nothrow_swappable_v<int>);
#endif

    // is_nothrow_swappable_with
    STATIC_REQUIRE(phi::is_nothrow_swappable_with<int&, int&>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_nothrow_swappable_with_v<int&, int&>);
#endif

    // is_null_pointer
    STATIC_REQUIRE(phi::is_null_pointer<decltype(nullptr)>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_null_pointer_v<decltype(nullptr)>);
#endif

    // is_null_pointer_or_pointer
    STATIC_REQUIRE(phi::is_null_pointer_or_pointer<int*>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_null_pointer_or_pointer_v<int*>);
#endif

    // is_object
#if PHI_HAS_WORKING_IS_OBJECT()
    STATIC_REQUIRE(phi::is_object<int>::value);
#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_object_v<int>);
#    endif
#endif

    // is_pod
#if PHI_HAS_WORKING_IS_POD()
    STATIC_REQUIRE(phi::is_pod<int>::value);
#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_pod_v<int>);
#    endif
#endif

    // is_pointer_interconvertible_base_of
#if PHI_HAS_WORKING_IS_POINTER_INTERCONVERTIBLE_BASE_OF()
    STATIC_REQUIRE_FALSE(phi::is_pointer_interconvertible_base_of<int, int>::value);
#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_pointer_interconvertible_base_of_v<int, int>);
#    endif
#endif

    // is_pointer
    STATIC_REQUIRE(phi::is_pointer<int*>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_pointer_v<int*>);
#endif

    // is_polymorphic
    STATIC_REQUIRE(phi::is_polymorphic<abstract>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_polymorphic_v<abstract>);
#endif

    // is_reference
    STATIC_REQUIRE(phi::is_reference<int&>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_reference_v<int&>);
#endif

    // is_reference_wrapper
    STATIC_REQUIRE_FALSE(phi::is_reference_wrapper<int>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_reference_wrapper_v<int>);
#endif

    // is_referenceable
    STATIC_REQUIRE(phi::is_referenceable<int>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_referenceable_v<int>);
#endif

    // is_rvalue_reference
    STATIC_REQUIRE(phi::is_rvalue_reference<int&&>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_rvalue_reference_v<int&&>);
#endif

    // is_safe_arithmetic
    STATIC_REQUIRE_FALSE(phi::is_safe_arithmetic<int>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_safe_arithmetic_v<int>);
#endif

    // is_safe_bool
    STATIC_REQUIRE_FALSE(phi::is_safe_bool<bool>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_safe_bool_v<bool>);
#endif

    // is_safe_floating_point
    STATIC_REQUIRE_FALSE(phi::is_safe_floating_point<int>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_safe_floating_point_v<int>);
#endif

    // is_safe_integer
    STATIC_REQUIRE_FALSE(phi::is_safe_integer<int>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_safe_integer_v<int>);
#endif

    // is_safe_integral
    STATIC_REQUIRE_FALSE(phi::is_safe_integral<int>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_safe_integral_v<int>);
#endif

    // is_safe_scalar
#if PHI_HAS_WORKING_IS_SAFE_SCALAR()
    STATIC_REQUIRE_FALSE(phi::is_safe_scalar<int>::value);
#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_safe_scalar_v<int>);
#    endif
#endif

    // is_safe_signed_integer
    STATIC_REQUIRE_FALSE(phi::is_safe_signed_integer<int>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_safe_signed_integer_v<int>);
#endif

    // is_safe_signed
    STATIC_REQUIRE_FALSE(phi::is_safe_signed<int>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_safe_signed_v<int>);
#endif

    // is_safe_type
    STATIC_REQUIRE_FALSE(phi::is_safe_type<int>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_safe_type_v<int>);
#endif

    // is_safe_unsigned_integer
    STATIC_REQUIRE_FALSE(phi::is_safe_unsigned_integer<int>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_safe_unsigned_integer_v<int>);
#endif

    // is_safe_unsigned
    STATIC_REQUIRE_FALSE(phi::is_safe_unsigned<int>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE_FALSE(phi::is_safe_unsigned_v<int>);
#endif

    // is_same
    STATIC_REQUIRE(phi::is_same<int, int>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_same_v<int, int>);
#endif

    // is_same_rc
    STATIC_REQUIRE(phi::is_same_rc<int, int>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_same_rc_v<int, int>);
#endif

    // is_same_rcv
    STATIC_REQUIRE(phi::is_same_rcv<int, int>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_same_rcv_v<int, int>);
#endif

    // is_same_rcvref
    STATIC_REQUIRE(phi::is_same_rcvref<int, int>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_same_rcvref_v<int, int>);
#endif

    // is_same_rref
    STATIC_REQUIRE(phi::is_same_rref<int, int>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_same_rref_v<int, int>);
#endif

    // is_same_rv
    STATIC_REQUIRE(phi::is_same_rv<int, int>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_same_rv_v<int, int>);
#endif

    // is_scalar
#if PHI_HAS_WORKING_IS_SCALAR()
    STATIC_REQUIRE(phi::is_scalar<int>::value);
#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_scalar_v<int>);
#    endif
#endif

    // is_scoped_enum
#if PHI_HAS_WORKING_IS_SCOPED_ENUM()
    STATIC_REQUIRE(phi::is_scoped_enum<EnumClass>::value);
#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_scoped_enum_v<EnumClass>);
#    endif
#endif

    // is_signed_integer
    STATIC_REQUIRE(phi::is_signed_integer<int>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_signed_integer_v<int>);
#endif

    // is_signed
    STATIC_REQUIRE(phi::is_signed<int>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_signed_v<int>);
#endif

    // is_standard_layout
#if PHI_HAS_WORKING_IS_STANDARD_LAYOUT()
    STATIC_REQUIRE(phi::is_standard_layout<int>::value);
#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_standard_layout_v<int>);
#    endif
#endif

    // is_static_castable_to
    STATIC_REQUIRE(phi::is_static_castable_to<int, int>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_static_castable_to_v<int, int>);
#endif

    // is_swappable
    STATIC_REQUIRE(phi::is_swappable<int>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_swappable_v<int>);
#endif

    // is_swappable_with
    STATIC_REQUIRE(phi::is_swappable_with<int&, int&>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_swappable_with_v<int&, int&>);
#endif

    // is_trivial
#if PHI_HAS_WORKING_IS_TRIVIAL()
    STATIC_REQUIRE(phi::is_trivial<int>::value);
#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_trivial_v<int>);
#    endif
#endif

    // is_trivially_assignable
#if PHI_HAS_WORKING_IS_TRIVIALLY_ASSIGNABLE()
    STATIC_REQUIRE(phi::is_trivially_assignable<int&, int&>::value);
#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_trivially_assignable_v<int&, int&>);
#    endif
#endif

    // is_trivially_constructible
#if PHI_HAS_WORKING_IS_TRIVIALLY_CONSTRUCTIBLE()
    STATIC_REQUIRE(phi::is_trivially_constructible<int>::value);
#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_trivially_constructible_v<int>);
#    endif
#endif

    // is_trivially_copy_assignable
#if PHI_HAS_WORKING_IS_TRIVIALLY_COPY_ASSIGNABLE()
    STATIC_REQUIRE(phi::is_trivially_copy_assignable<int>::value);
#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_trivially_copy_assignable_v<int>);
#    endif
#endif

    // is_trivially_copy_constructible
#if PHI_HAS_WORKING_IS_TRIVIALLY_COPY_CONSTRUCTIBLE()
    STATIC_REQUIRE(phi::is_trivially_copy_constructible<int>::value);
#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_trivially_copy_constructible_v<int>);
#    endif
#endif

    // is_trivially_copyable
#if PHI_HAS_WORKING_IS_TRIVIALLY_COPYABLE()
    STATIC_REQUIRE(phi::is_trivially_copyable<int>::value);
#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_trivially_copyable_v<int>);
#    endif
#endif

    // is_trivially_default_constructible
#if PHI_HAS_WORKING_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE()
    STATIC_REQUIRE(phi::is_trivially_default_constructible<int>::value);
#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_trivially_default_constructible_v<int>);
#    endif
#endif

    // is_trivially_destructible
#if PHI_HAS_WORKING_IS_TRIVIALLY_DESTRUCTIBLE()
    STATIC_REQUIRE(phi::is_trivially_destructible<int>::value);
#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_trivially_destructible_v<int>);
#    endif
#endif

    // is_trivially_move_assignable
#if PHI_HAS_WORKING_IS_TRIVIALLY_MOVE_ASSIGNABLE()
    STATIC_REQUIRE(phi::is_trivially_move_assignable<int>::value);
#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_trivially_move_assignable_v<int>);
#    endif
#endif

    // is_trivially_move_constructible
#if PHI_HAS_WORKING_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE()
    STATIC_REQUIRE(phi::is_trivially_move_constructible<int>::value);
#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_trivially_move_constructible_v<int>);
#    endif
#endif

    // is_unbounded_array
    STATIC_REQUIRE(phi::is_unbounded_array<char[]>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_unbounded_array_v<char[]>);
#endif

    // is_union
#if PHI_HAS_WORKING_IS_UNION()
    STATIC_REQUIRE(phi::is_union<union_type>::value);
#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_union_v<union_type>);
#    endif
#endif

    // is_unsafe_arithmetic
    STATIC_REQUIRE(phi::is_unsafe_arithmetic<int>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_unsafe_arithmetic_v<int>);
#endif

    // is_unsafe_bool
    STATIC_REQUIRE(phi::is_unsafe_bool<bool>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_unsafe_bool_v<bool>);
#endif

    // is_unsafe_floating_point
    STATIC_REQUIRE(phi::is_unsafe_floating_point<float>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_unsafe_floating_point_v<float>);
#endif

    // is_unsafe_fundamental
    STATIC_REQUIRE(phi::is_unsafe_fundamental<int>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_unsafe_fundamental_v<int>);
#endif

    // is_unsafe_integer
    STATIC_REQUIRE(phi::is_unsafe_integer<int>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_unsafe_integer_v<int>);
#endif

    // is_unsafe_integral
    STATIC_REQUIRE(phi::is_unsafe_integral<int>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_unsafe_integral_v<int>);
#endif

    // is_unsafe_scalar
#if PHI_HAS_WORKING_IS_UNSAFE_SCALAR()
    STATIC_REQUIRE(phi::is_unsafe_scalar<int>::value);
#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_unsafe_scalar_v<int>);
#    endif
#endif

    // is_unsafe_signed_integer
    STATIC_REQUIRE(phi::is_unsafe_signed_integer<int>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_unsafe_signed_integer_v<int>);
#endif

    // is_unsafe_signed
    STATIC_REQUIRE(phi::is_unsafe_signed<int>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_unsafe_signed_v<int>);
#endif

    // is_unsafe_type
    STATIC_REQUIRE(phi::is_unsafe_type<int>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_unsafe_type_v<int>);
#endif

    // is_unsafe_unsigned_integer
    STATIC_REQUIRE(phi::is_unsafe_unsigned_integer<unsigned int>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_unsafe_unsigned_integer_v<unsigned int>);
#endif

    // is_unsafe_signed
    STATIC_REQUIRE(phi::is_unsafe_unsigned_integer<unsigned>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_unsafe_unsigned_integer_v<unsigned>);
#endif

    // is_unscoped_enum
#if PHI_HAS_WORKING_IS_UNSCOPED_ENUM()
    STATIC_REQUIRE(phi::is_unscoped_enum<Enum>::value);
#    if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_unscoped_enum_v<Enum>);
#    endif
#endif

    // is_unsigned_integer
    STATIC_REQUIRE(phi::is_unsigned_integer<unsigned>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_unsigned_integer_v<unsigned>);
#endif

    // is_unsigned
    STATIC_REQUIRE(phi::is_unsigned<unsigned>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_unsigned_v<unsigned>);
#endif

    // is_void
    STATIC_REQUIRE(phi::is_void<void>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_void_v<void>);
#endif

    // is_volatile
    STATIC_REQUIRE(phi::is_volatile<volatile int>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::is_volatile_v<volatile int>);
#endif

    // make_safe
    CHECK_SAME_TYPE(typename phi::make_safe<int>::type, phi::integer<int>);
    CHECK_SAME_TYPE(phi::make_safe_t<int>, phi::integer<int>);

    // make_signed
    CHECK_SAME_TYPE(typename phi::make_signed<unsigned>::type, int);
    CHECK_SAME_TYPE(phi::make_signed_t<unsigned>, int);

    // make_unsafe
    CHECK_SAME_TYPE(typename phi::make_unsafe<int>::type, int);
    CHECK_SAME_TYPE(phi::make_unsafe_t<int>, int);

    // make_unsigned
    CHECK_SAME_TYPE(typename phi::make_unsigned<int>::type, unsigned);
    CHECK_SAME_TYPE(phi::make_unsigned_t<int>, unsigned);

    // negation
    STATIC_REQUIRE(phi::negation<phi::false_type>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::negation_v<phi::false_type>);
#endif

    // rank
    STATIC_REQUIRE(phi::rank<int>::value == 0);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::rank_v<int> == 0);
#endif

    // remove_all_extents
    CHECK_SAME_TYPE(typename phi::remove_all_extents<int[]>::type, int);
    CHECK_SAME_TYPE(phi::remove_all_extents_t<int[]>, int);

    // remove_const
    CHECK_SAME_TYPE(typename phi::remove_const<const int>::type, int);
    CHECK_SAME_TYPE(phi::remove_const_t<const int>, int);

    // remove_cv
    CHECK_SAME_TYPE(typename phi::remove_cv<const volatile int>::type, int);
    CHECK_SAME_TYPE(phi::remove_cv_t<const volatile int>, int);

    // remove_cvref
    CHECK_SAME_TYPE(typename phi::remove_cvref<int>::type, int);
    CHECK_SAME_TYPE(phi::remove_cvref_t<int>, int);

    // remove_extent
    CHECK_SAME_TYPE(typename phi::remove_extent<int[]>::type, int);
    CHECK_SAME_TYPE(phi::remove_extent_t<int[]>, int);

    // remove_pointer
    CHECK_SAME_TYPE(typename phi::remove_pointer<int*>::type, int);
    CHECK_SAME_TYPE(phi::remove_pointer_t<int*>, int);

    // remove_reference
    CHECK_SAME_TYPE(typename phi::remove_reference<int&>::type, int);
    CHECK_SAME_TYPE(phi::remove_reference_t<int&>, int);

    // remove_volatile
    CHECK_SAME_TYPE(typename phi::remove_volatile<volatile int>::type, int);
    CHECK_SAME_TYPE(phi::remove_volatile_t<volatile int>, int);

    // signed_int_of_size
    CHECK_SAME_TYPE(typename phi::signed_int_of_size<1>::type, phi::int8_t);
    CHECK_SAME_TYPE(phi::signed_int_of_size_t<1>, phi::int8_t);

    // size_constant
    CHECK_SAME_TYPE(phi::size_constant<0u>, phi::integral_constant<phi::size_t, 0u>);

    // static_clamp
    STATIC_REQUIRE(phi::static_clamp<1, 0, 2>::value == 1);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::static_clamp_v<1, 0, 2> == 1);
#endif

    // static_max
    STATIC_REQUIRE(phi::static_max<0, 1, 2>::value == 2);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::static_max_v<0, 1, 2> == 2);
#endif

    // static_min
    STATIC_REQUIRE(phi::static_min<0, 1, 2>::value == 0);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::static_min_v<0, 1, 2> == 0);
#endif

    // to_safe
    CHECK_SAME_TYPE(decltype(phi::to_safe(3)), phi::integer<int>);

    // to_underlying
#if PHI_HAS_WORKING_UNDERLYING_TYPE()
    CHECK_SAME_TYPE(decltype(phi::to_underlying(EnumSigned::two)), int);
#endif

    // to_unsafe
    CHECK_SAME_TYPE(decltype(phi::to_unsafe(3)), int);

    // true_t
    STATIC_REQUIRE(phi::true_t<>::value);
#if PHI_HAS_FEATURE_VARIABLE_TEMPLATE()
    STATIC_REQUIRE(phi::true_v<>);
#endif

    // type_identity
    CHECK_SAME_TYPE(typename phi::type_identity<int>::type, int);
    CHECK_SAME_TYPE(phi::type_identity_t<int>, int);

    // underlying_type
#if PHI_HAS_WORKING_UNDERLYING_TYPE()
    CHECK_SAME_TYPE(typename phi::underlying_type<EnumSigned>::type, int);
    CHECK_SAME_TYPE(phi::underlying_type_t<EnumSigned>, int);
#endif

    // unsigned_int_of_size
    CHECK_SAME_TYPE(typename phi::unsigned_int_of_size<1>::type, phi::uint8_t);
    CHECK_SAME_TYPE(phi::unsigned_int_of_size_t<1>, phi::uint8_t);

    // void_t
    CHECK_SAME_TYPE(typename phi::void_t<>, void);
}
