#ifndef INCG_PHI_TYPE_TRAITS_HPP
#define INCG_PHI_TYPE_TRAITS_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/type_traits/detail/invoke_impl.hpp"
#include "phi/type_traits/detail/nat.hpp"
#include "phi/type_traits/detail/yes_no_type.hpp"

#include "phi/type_traits/add_const.hpp"
#include "phi/type_traits/add_cv.hpp"
#include "phi/type_traits/add_lvalue_reference.hpp"
#include "phi/type_traits/add_member_const.hpp"
#include "phi/type_traits/add_pointer.hpp"
#include "phi/type_traits/add_rvalue_reference.hpp"
#include "phi/type_traits/add_volatile.hpp"
#include "phi/type_traits/aligned_storage.hpp"
#include "phi/type_traits/aligned_union.hpp"
#include "phi/type_traits/alignment_of.hpp"
#include "phi/type_traits/bool_constant.hpp"
#include "phi/type_traits/common_type.hpp"
#include "phi/type_traits/conditional.hpp"
#include "phi/type_traits/copy_const.hpp"
#include "phi/type_traits/copy_cv.hpp"
#include "phi/type_traits/copy_volatile.hpp"
#include "phi/type_traits/decay.hpp"
#include "phi/type_traits/disable_if.hpp"
#include "phi/type_traits/disjunction.hpp"
#include "phi/type_traits/enable_if.hpp"
#include "phi/type_traits/extent.hpp"
#include "phi/type_traits/false_t.hpp"
#include "phi/type_traits/has_unique_object_representations.hpp"
#include "phi/type_traits/has_virtual_destructor.hpp"
#include "phi/type_traits/integral_constant.hpp"
#include "phi/type_traits/invoke_result.hpp"
#include "phi/type_traits/is_abstract.hpp"
#include "phi/type_traits/is_aggregate.hpp"
#include "phi/type_traits/is_any_of.hpp"
#include "phi/type_traits/is_any_of_rc.hpp"
#include "phi/type_traits/is_any_of_rcv.hpp"
#include "phi/type_traits/is_any_of_rcvref.hpp"
#include "phi/type_traits/is_any_of_rref.hpp"
#include "phi/type_traits/is_any_of_rv.hpp"
#include "phi/type_traits/is_arithmetic.hpp"
#include "phi/type_traits/is_array.hpp"
#include "phi/type_traits/is_assignable.hpp"
#include "phi/type_traits/is_base_of.hpp"
#include "phi/type_traits/is_bool.hpp"
#include "phi/type_traits/is_bounded_array.hpp"
#include "phi/type_traits/is_class.hpp"
#include "phi/type_traits/is_complete.hpp"
#include "phi/type_traits/is_complete_or_unbounded.hpp"
#include "phi/type_traits/is_complete_or_unbounded_void.hpp"
#include "phi/type_traits/is_complete_or_void.hpp"
#include "phi/type_traits/is_compound.hpp"
#include "phi/type_traits/is_const.hpp"
#include "phi/type_traits/is_constant_evaluated.hpp"
#include "phi/type_traits/is_constructible.hpp"
#include "phi/type_traits/is_copy_assignable.hpp"
#include "phi/type_traits/is_copy_constructible.hpp"
#include "phi/type_traits/is_corresponding_member.hpp"
#include "phi/type_traits/is_default_constructible.hpp"
#include "phi/type_traits/is_derived_from.hpp"
#include "phi/type_traits/is_destructible.hpp"
#include "phi/type_traits/is_empty.hpp"
#include "phi/type_traits/is_enum.hpp"
#include "phi/type_traits/is_final.hpp"
#include "phi/type_traits/is_floating_point.hpp"
#include "phi/type_traits/is_function.hpp"
#include "phi/type_traits/is_function_pointer.hpp"
#include "phi/type_traits/is_fundamental.hpp"
#include "phi/type_traits/is_implicitly_default_constructible.hpp"
#include "phi/type_traits/is_integer.hpp"
#include "phi/type_traits/is_integral.hpp"
#include "phi/type_traits/is_invocable.hpp"
#include "phi/type_traits/is_invocable_r.hpp"
#include "phi/type_traits/is_layout_compatible.hpp"
#include "phi/type_traits/is_literal_type.hpp"
#include "phi/type_traits/is_lvalue_reference.hpp"
#include "phi/type_traits/is_member_function_pointer.hpp"
#include "phi/type_traits/is_member_object_pointer.hpp"
#include "phi/type_traits/is_member_pointer.hpp"
#include "phi/type_traits/is_move_assignable.hpp"
#include "phi/type_traits/is_move_constructible.hpp"
#include "phi/type_traits/is_non_bool_integral.hpp"
#include "phi/type_traits/is_none_of.hpp"
#include "phi/type_traits/is_none_of_rc.hpp"
#include "phi/type_traits/is_none_of_rcv.hpp"
#include "phi/type_traits/is_none_of_rcvref.hpp"
#include "phi/type_traits/is_none_of_rref.hpp"
#include "phi/type_traits/is_none_of_rv.hpp"
#include "phi/type_traits/is_nothrow_assignable.hpp"
#include "phi/type_traits/is_nothrow_constructible.hpp"
#include "phi/type_traits/is_nothrow_convertible.hpp"
#include "phi/type_traits/is_nothrow_copy_assignable.hpp"
#include "phi/type_traits/is_nothrow_copy_constructible.hpp"
#include "phi/type_traits/is_nothrow_default_constructible.hpp"
#include "phi/type_traits/is_nothrow_destructible.hpp"
#include "phi/type_traits/is_nothrow_invocable.hpp"
#include "phi/type_traits/is_nothrow_invocable_r.hpp"
#include "phi/type_traits/is_nothrow_move_assignable.hpp"
#include "phi/type_traits/is_nothrow_move_constructible.hpp"
#include "phi/type_traits/is_nothrow_swappable.hpp"
#include "phi/type_traits/is_nothrow_swappable_with.hpp"
#include "phi/type_traits/is_null_pointer.hpp"
#include "phi/type_traits/is_null_pointer_or_pointer.hpp"
#include "phi/type_traits/is_object.hpp"
#include "phi/type_traits/is_pod.hpp"
#include "phi/type_traits/is_pointer.hpp"
#include "phi/type_traits/is_pointer_interconvertible_base_of.hpp"
#include "phi/type_traits/is_pointer_interconvertible_with_class.hpp"
#include "phi/type_traits/is_polymorphic.hpp"
#include "phi/type_traits/is_reference.hpp"
#include "phi/type_traits/is_reference_wrapper.hpp"
#include "phi/type_traits/is_referenceable.hpp"
#include "phi/type_traits/is_rvalue_reference.hpp"
#include "phi/type_traits/is_safe_arithmetic.hpp"
#include "phi/type_traits/is_safe_bool.hpp"
#include "phi/type_traits/is_safe_floating_point.hpp"
#include "phi/type_traits/is_safe_fundamental.hpp"
#include "phi/type_traits/is_safe_integer.hpp"
#include "phi/type_traits/is_safe_integral.hpp"
#include "phi/type_traits/is_safe_non_bool_integral.hpp"
#include "phi/type_traits/is_safe_scalar.hpp"
#include "phi/type_traits/is_safe_signed.hpp"
#include "phi/type_traits/is_safe_signed_integer.hpp"
#include "phi/type_traits/is_safe_type.hpp"
#include "phi/type_traits/is_safe_unsigned.hpp"
#include "phi/type_traits/is_safe_unsigned_integer.hpp"
#include "phi/type_traits/is_same.hpp"
#include "phi/type_traits/is_same_rc.hpp"
#include "phi/type_traits/is_same_rcv.hpp"
#include "phi/type_traits/is_same_rcvref.hpp"
#include "phi/type_traits/is_same_rref.hpp"
#include "phi/type_traits/is_same_rv.hpp"
#include "phi/type_traits/is_scalar.hpp"
#include "phi/type_traits/is_scoped_enum.hpp"
#include "phi/type_traits/is_signed.hpp"
#include "phi/type_traits/is_signed_integer.hpp"
#include "phi/type_traits/is_standard_layout.hpp"
#include "phi/type_traits/is_static_castable_to.hpp"
#include "phi/type_traits/is_swappable.hpp"
#include "phi/type_traits/is_swappable_with.hpp"
#include "phi/type_traits/is_trivial.hpp"
#include "phi/type_traits/is_trivially_assignable.hpp"
#include "phi/type_traits/is_trivially_constructible.hpp"
#include "phi/type_traits/is_trivially_copy_assignable.hpp"
#include "phi/type_traits/is_trivially_copy_constructible.hpp"
#include "phi/type_traits/is_trivially_copyable.hpp"
#include "phi/type_traits/is_trivially_default_constructible.hpp"
#include "phi/type_traits/is_trivially_destructible.hpp"
#include "phi/type_traits/is_trivially_move_assignable.hpp"
#include "phi/type_traits/is_trivially_move_constructible.hpp"
#include "phi/type_traits/is_unbounded_array.hpp"
#include "phi/type_traits/is_union.hpp"
#include "phi/type_traits/is_unsafe_arithmetic.hpp"
#include "phi/type_traits/is_unsafe_bool.hpp"
#include "phi/type_traits/is_unsafe_floating_point.hpp"
#include "phi/type_traits/is_unsafe_fundamental.hpp"
#include "phi/type_traits/is_unsafe_integer.hpp"
#include "phi/type_traits/is_unsafe_integral.hpp"
#include "phi/type_traits/is_unsafe_non_bool_integral.hpp"
#include "phi/type_traits/is_unsafe_scalar.hpp"
#include "phi/type_traits/is_unsafe_signed.hpp"
#include "phi/type_traits/is_unsafe_signed_integer.hpp"
#include "phi/type_traits/is_unsafe_type.hpp"
#include "phi/type_traits/is_unsafe_unsigned.hpp"
#include "phi/type_traits/is_unsafe_unsigned_integer.hpp"
#include "phi/type_traits/is_unscoped_enum.hpp"
#include "phi/type_traits/is_unsigned.hpp"
#include "phi/type_traits/is_unsigned_integer.hpp"
#include "phi/type_traits/is_void.hpp"
#include "phi/type_traits/is_volatile.hpp"
#include "phi/type_traits/make_safe.hpp"
#include "phi/type_traits/make_signed.hpp"
#include "phi/type_traits/make_unsafe.hpp"
#include "phi/type_traits/make_unsigned.hpp"
#include "phi/type_traits/negation.hpp"
#include "phi/type_traits/rank.hpp"
#include "phi/type_traits/remove_all_extents.hpp"
#include "phi/type_traits/remove_const.hpp"
#include "phi/type_traits/remove_cv.hpp"
#include "phi/type_traits/remove_cvref.hpp"
#include "phi/type_traits/remove_extent.hpp"
#include "phi/type_traits/remove_pointer.hpp"
#include "phi/type_traits/remove_reference.hpp"
#include "phi/type_traits/remove_volatile.hpp"
#include "phi/type_traits/signed_int_of_size.hpp"
#include "phi/type_traits/size_constant.hpp"
#include "phi/type_traits/static_clamp.hpp"
#include "phi/type_traits/static_max.hpp"
#include "phi/type_traits/static_min.hpp"
#include "phi/type_traits/to_safe.hpp"
#include "phi/type_traits/to_underlying.hpp"
#include "phi/type_traits/to_unsafe.hpp"
#include "phi/type_traits/true_t.hpp"
#include "phi/type_traits/type_identity.hpp"
#include "phi/type_traits/underlying_type.hpp"
#include "phi/type_traits/unsigned_int_of_size.hpp"
#include "phi/type_traits/void_t.hpp"

#endif // INCG_PHI_TYPE_TRAITS_HPP
