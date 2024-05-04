project("PhiCoreTestUnittests" CXX)

file(GLOB TEST_HEADERS "include/constexpr_helper.hpp" "include/Noexcept.hpp" "include/SameType.hpp"
     "include/test_types.hpp")

file(
  GLOB
  TEST_SOURCES
  # algorithm
  "src/algorithm/at.test.cpp"
  "src/algorithm/clamp.test.cpp"
  "src/algorithm/compare.test.cpp"
  "src/algorithm/exchange.test.cpp"
  "src/algorithm/fill.test.cpp"
  "src/algorithm/find_if_not.test.cpp"
  "src/algorithm/find_if.test.cpp"
  "src/algorithm/find.test.cpp"
  "src/algorithm/max.test.cpp"
  "src/algorithm/min.test.cpp"
  "src/algorithm/string_compare_unsafe.test.cpp"
  "src/algorithm/string_compare.test.cpp"
  "src/algorithm/string_equals_ignore_case.test.cpp"
  "src/algorithm/string_equals.test.cpp"
  "src/algorithm/string_length_unsafe.test.cpp"
  "src/algorithm/string_length.test.cpp"
  "src/algorithm/swap.test.cpp"
  # compiler_support/intrinsics
  "src/compiler_support/intrinsics/dynamic_object_size.test.cpp"
  "src/compiler_support/intrinsics/object_size.test.cpp"
  # compiler_support
  "src/compiler_support/architecture.test.cpp"
  "src/compiler_support/assume.test.cpp"
  "src/compiler_support/char8_t.test.cpp"
  "src/compiler_support/compiler.test.cpp"
  "src/compiler_support/consteval.test.cpp"
  "src/compiler_support/constexpr.test.cpp"
  "src/compiler_support/counter.test.cpp"
  "src/compiler_support/cpp_standard.test.cpp"
  "src/compiler_support/current_function.test.cpp"
  "src/compiler_support/defect_report.test.cpp"
  "src/compiler_support/inline.test.cpp"
  "src/compiler_support/likely.test.cpp"
  "src/compiler_support/noexcept.test.cpp"
  "src/compiler_support/platform.test.cpp"
  "src/compiler_support/restrict.test.cpp"
  "src/compiler_support/standard_library.test.cpp"
  "src/compiler_support/unreachable.test.cpp"
  "src/compiler_support/warning.test.cpp"
  # container
  "src/container/array.test.cpp"
  "src/container/singly_linked_list.test.cpp"
  "src/container/string_view.test.cpp"
  # core/address_of
  "src/core/address_of/address_of.test.cpp"
  "src/core/address_of/no_address_of_or_is_object.test.cpp"
  "src/core/address_of/no_address_of.test.cpp"
  "src/core/address_of/no_is_object.test.cpp"
  # core/memcmp
  "src/core/memcmp/no_constexpr_memcmp.test.cpp"
  "src/core/memcmp/no_intrinsics.test.cpp"
  "src/core/memcmp/no_memcmp.test.cpp"
  "src/core/memcmp/value.test.cpp"
  # core/source_location
  "src/core/source_location/no_builtin_column.test.cpp"
  "src/core/source_location/no_builtin_line.test.cpp"
  "src/core/source_location/value.test.cpp"
  # core
  "src/core/address_of.test.cpp"
  "src/core/as_const.test.cpp"
  "src/core/assert.test.cpp"
  "src/core/boolean.test.cpp"
  "src/core/declval.test.cpp"
  "src/core/flat_ptr.test.cpp"
  "src/core/floating_point.test.cpp"
  "src/core/forward.test.cpp"
  "src/core/ignore.test.cpp"
  "src/core/integer.test.cpp"
  "src/core/intptr_t.test.cpp"
  "src/core/invoke.test.cpp"
  "src/core/max_align_t.test.cpp"
  "src/core/monitor.test.cpp"
  "src/core/move_if_noexcept.test.cpp"
  "src/core/move.test.cpp"
  "src/core/named_type.test.cpp"
  "src/core/narrow_cast.test.cpp"
  "src/core/non_copyable.test.cpp"
  "src/core/nullptr_t.test.cpp"
  "src/core/observer_ptr.test.cpp"
  "src/core/optional.test.cpp"
  "src/core/pointer_traits.test.cpp"
  "src/core/ptrdiff_t.test.cpp"
  "src/core/ref_ptr.test.cpp"
  "src/core/scope_guard.test.cpp"
  "src/core/scope_ptr.test.cpp"
  "src/core/scoped_value_guard.test.cpp"
  "src/core/size_t.test.cpp"
  "src/core/sized_types.test.cpp"
  "src/core/ssize_t.test.cpp"
  "src/core/stop_watch.test.cpp"
  "src/core/streamoff.test.cpp"
  "src/core/to_address.test.cpp"
  "src/core/types.test.cpp"
  "src/core/unsafe_cast.test.cpp"
  "src/core/voidify.test.cpp"
  "src/core/wint_t.test.cpp"
  # forward
  "src/forward/array.test.cpp"
  "src/forward/flat_ptr.test.cpp"
  "src/forward/observer_ptr.test.cpp"
  "src/forward/ref_ptr.test.cpp"
  "src/forward/scope_ptr.test.cpp"
  "src/forward/string_view.test.cpp"
  # forward/std
  "src/forward/std/allocator.test.cpp"
  "src/forward/std/array.test.cpp"
  "src/forward/std/char_traits.test.cpp"
  "src/forward/std/hash.test.cpp"
  "src/forward/std/initializer_list.test.cpp"
  "src/forward/std/pair.test.cpp"
  "src/forward/std/reference_wrapper.test.cpp"
  "src/forward/std/span.test.cpp"
  "src/forward/std/string_view.test.cpp"
  "src/forward/std/string.test.cpp"
  # iterator
  "src/iterator/iter_reference.test.cpp"
  # limits
  "src/limits/float_denorm_style.test.cpp"
  "src/limits/float_round_style.test.cpp"
  # math
  "src/math/abs.test.cpp"
  "src/math/ceil.test.cpp"
  "src/math/constants.test.cpp"
  "src/math/floor.test.cpp"
  "src/math/is_infinity.test.cpp"
  "src/math/is_nan.test.cpp"
  "src/math/signum.test.cpp"
  "src/math/vector2.test.cpp"
  # preprocessor
  "src/preprocessor/bool.test.cpp"
  "src/preprocessor/function_like_macro.test.cpp"
  "src/preprocessor/glue.test.cpp"
  "src/preprocessor/if_else.test.cpp"
  "src/preprocessor/if.test.cpp"
  "src/preprocessor/source_line.test.cpp"
  "src/preprocessor/stringify.test.cpp"
  "src/preprocessor/versioning.test.cpp"
  # selftest
  "src/selftest/constexpr_helper.test.cpp"
  # text
  "src/text/binary_digit_value.test.cpp"
  "src/text/digit_value.test.cpp"
  "src/text/hex_digit_value.test.cpp"
  "src/text/is_alpha_numeric.test.cpp"
  "src/text/is_alpha.test.cpp"
  "src/text/is_ascii.test.cpp"
  "src/text/is_binary_digit.test.cpp"
  "src/text/is_blank.test.cpp"
  "src/text/is_control.test.cpp"
  "src/text/is_digit.test.cpp"
  "src/text/is_graphical_character.test.cpp"
  "src/text/is_hex_digit.test.cpp"
  "src/text/is_lower_case.test.cpp"
  "src/text/is_octal_digit.test.cpp"
  "src/text/is_printable.test.cpp"
  "src/text/is_punctuation.test.cpp"
  "src/text/is_space.test.cpp"
  "src/text/is_upper_case.test.cpp"
  "src/text/octal_digit_value.test.cpp"
  "src/text/to_lower_case.test.cpp"
  "src/text/to_upper_case.test.cpp"
  # type_system
  "src/type_system/max.test.cpp"
  "src/type_system/min.test.cpp"
  # type_traits
  "src/type_traits/detail/nat.test.cpp"
  "src/type_traits/detail/yes_no_type.test.cpp"
  "src/type_traits/add_const.test.cpp"
  "src/type_traits/add_cv.test.cpp"
  "src/type_traits/add_lvalue_reference.nointrinsic.test.cpp"
  "src/type_traits/add_lvalue_reference.test.cpp"
  "src/type_traits/add_pointer.nointrinsic.test.cpp"
  "src/type_traits/add_pointer.test.cpp"
  "src/type_traits/add_rvalue_reference.nointrinsic.test.cpp"
  "src/type_traits/add_rvalue_reference.test.cpp"
  "src/type_traits/add_volatile.test.cpp"
  "src/type_traits/aligned_storage.test.cpp"
  "src/type_traits/aligned_union.test.cpp"
  "src/type_traits/alignment_of.test.cpp"
  "src/type_traits/array_size.test.cpp"
  "src/type_traits/bool_constant.test.cpp"
  "src/type_traits/common_type.test.cpp"
  "src/type_traits/conditional.test.cpp"
  "src/type_traits/conjunction.test.cpp"
  "src/type_traits/copy_const.test.cpp"
  "src/type_traits/copy_cv.test.cpp"
  "src/type_traits/copy_volatile.test.cpp"
  "src/type_traits/decay.nointrinsic.test.cpp"
  "src/type_traits/decay.test.cpp"
  "src/type_traits/disable_if.test.cpp"
  "src/type_traits/disjunction.test.cpp"
  "src/type_traits/enable_if.test.cpp"
  "src/type_traits/extent.test.cpp"
  "src/type_traits/extent.nointrinsic.test.cpp"
  "src/type_traits/false_t.test.cpp"
  "src/type_traits/has_difference_type.test.cpp"
  "src/type_traits/has_element_type.test.cpp"
  "src/type_traits/has_unique_object_representations.nointrinsic.test.cpp"
  "src/type_traits/has_unique_object_representations.test.cpp"
  "src/type_traits/has_value_type.test.cpp"
  "src/type_traits/has_virtual_destructor.nointrinsic.test.cpp"
  "src/type_traits/has_virtual_destructor.test.cpp"
  "src/type_traits/integral_constant.test.cpp"
  "src/type_traits/invoke_result.no_is_base_of.test.cpp"
  "src/type_traits/invoke_result.nointrinsic.test.cpp"
  "src/type_traits/invoke_result.test.cpp"
  "src/type_traits/is_abstract.nointrinsic.test.cpp"
  "src/type_traits/is_abstract.test.cpp"
  "src/type_traits/is_aggregate.nointrinsic.test.cpp"
  "src/type_traits/is_aggregate.test.cpp"
  "src/type_traits/is_any_of_rc.test.cpp"
  "src/type_traits/is_any_of_rcv.test.cpp"
  "src/type_traits/is_any_of_rcvref.test.cpp"
  "src/type_traits/is_any_of_rref.test.cpp"
  "src/type_traits/is_any_of_rv.test.cpp"
  "src/type_traits/is_any_of.test.cpp"
  "src/type_traits/is_arithmetic.test.cpp"
  "src/type_traits/is_array.test.cpp"
  "src/type_traits/is_assignable.nointrinsic.test.cpp"
  "src/type_traits/is_assignable.test.cpp"
  "src/type_traits/is_base_of.nointrinsic.test.cpp"
  "src/type_traits/is_base_of.nointrinsic2.test.cpp"
  "src/type_traits/is_base_of.nointrinsic3.test.cpp"
  "src/type_traits/is_base_of.test.cpp"
  "src/type_traits/is_bool.test.cpp"
  "src/type_traits/is_bounded_array.no_is_bounded_array.test.cpp"
  "src/type_traits/is_bounded_array.test.cpp"
  "src/type_traits/is_class.test.cpp"
  "src/type_traits/is_complete_or_unbounded_void.test.cpp"
  "src/type_traits/is_complete_or_unbounded.test.cpp"
  "src/type_traits/is_complete_or_void.test.cpp"
  "src/type_traits/is_complete.test.cpp"
  "src/type_traits/is_compound.test.cpp"
  "src/type_traits/is_const.test.cpp"
  "src/type_traits/is_constant_evaluated.test.cpp"
  "src/type_traits/is_constructible.nointrinsic.test.cpp"
  "src/type_traits/is_constructible.nointrinsic2.test.cpp"
  "src/type_traits/is_constructible.nointrinsic3.test.cpp"
  "src/type_traits/is_constructible.test.cpp"
  "src/type_traits/is_convertible.test.cpp"
  "src/type_traits/is_copy_assignable.test.cpp"
  "src/type_traits/is_copy_constructible.test.cpp"
  "src/type_traits/is_corresponding_member.test.cpp"
  "src/type_traits/is_default_constructible.test.cpp"
  "src/type_traits/is_default_constructible.nointrinsic.test.cpp"
  "src/type_traits/is_default_constructible.nointrinsic2.test.cpp"
  "src/type_traits/is_default_constructible.nointrinsic3.test.cpp"
  "src/type_traits/is_derived_from.test.cpp"
  "src/type_traits/is_destructible.nointrinsic.test.cpp"
  "src/type_traits/is_destructible.test.cpp"
  "src/type_traits/is_empty.test.cpp"
  "src/type_traits/is_enum.nointrinsic.test.cpp"
  "src/type_traits/is_enum.nointrinsic2.test.cpp"
  "src/type_traits/is_enum.test.cpp"
  "src/type_traits/is_final.test.cpp"
  "src/type_traits/is_floating_point.test.cpp"
  "src/type_traits/is_function_pointer.test.cpp"
  "src/type_traits/is_function.test.cpp"
  "src/type_traits/is_fundamental.test.cpp"
  "src/type_traits/is_implicitly_default_constructible.test.cpp"
  "src/type_traits/is_integer.test.cpp"
  "src/type_traits/is_integral.test.cpp"
  "src/type_traits/is_invocable_r.test.cpp"
  "src/type_traits/is_invocable.test.cpp"
  "src/type_traits/is_layout_compatible.test.cpp"
  "src/type_traits/is_literal_type.test.cpp"
  "src/type_traits/is_lvalue_reference.test.cpp"
  "src/type_traits/is_member_function_pointer.test.cpp"
  "src/type_traits/is_member_object_pointer.test.cpp"
  "src/type_traits/is_member_pointer.test.cpp"
  "src/type_traits/is_move_assignable.test.cpp"
  "src/type_traits/is_move_constructible.test.cpp"
  "src/type_traits/is_non_bool_integral.test.cpp"
  "src/type_traits/is_none_of_rc.test.cpp"
  "src/type_traits/is_none_of_rcv.test.cpp"
  "src/type_traits/is_none_of_rcvref.test.cpp"
  "src/type_traits/is_none_of_rref.test.cpp"
  "src/type_traits/is_none_of_rv.test.cpp"
  "src/type_traits/is_none_of.test.cpp"
  "src/type_traits/is_nothrow_assignable.test.cpp"
  "src/type_traits/is_nothrow_constructible.test.cpp"
  "src/type_traits/is_nothrow_convertible.test.cpp"
  "src/type_traits/is_nothrow_copy_assignable.test.cpp"
  "src/type_traits/is_nothrow_copy_constructible.test.cpp"
  "src/type_traits/is_nothrow_default_constructible.test.cpp"
  "src/type_traits/is_nothrow_destructible.test.cpp"
  "src/type_traits/is_nothrow_invocable_r.test.cpp"
  "src/type_traits/is_nothrow_invocable.test.cpp"
  "src/type_traits/is_nothrow_move_assignable.test.cpp"
  "src/type_traits/is_nothrow_move_constructible.test.cpp"
  "src/type_traits/is_nothrow_swappable_with.test.cpp"
  "src/type_traits/is_nothrow_swappable.test.cpp"
  "src/type_traits/is_null_pointer_or_pointer.test.cpp"
  "src/type_traits/is_null_pointer.no_is_null_pointer.test.cpp"
  "src/type_traits/is_null_pointer.test.cpp"
  "src/type_traits/is_object.nointrinsic.test.cpp"
  "src/type_traits/is_object.nointrinsic2.test.cpp"
  "src/type_traits/is_object.test.cpp"
  "src/type_traits/is_pod.test.cpp"
  "src/type_traits/is_pointer_interconvertible_base_of.test.cpp"
  "src/type_traits/is_pointer_interconvertible_with_class.test.cpp"
  "src/type_traits/is_pointer.nointrinsic.test.cpp"
  "src/type_traits/is_pointer.test.cpp"
  "src/type_traits/is_polymorphic.test.cpp"
  "src/type_traits/is_reference_wrapper.test.cpp"
  "src/type_traits/is_reference.test.cpp"
  "src/type_traits/is_referenceable.no_is_referenceable.test.cpp"
  "src/type_traits/is_referenceable.test.cpp"
  "src/type_traits/is_rvalue_reference.test.cpp"
  "src/type_traits/is_safe_arithmetic.test.cpp"
  "src/type_traits/is_safe_bool.test.cpp"
  "src/type_traits/is_safe_floating_point.test.cpp"
  "src/type_traits/is_safe_fundamental.test.cpp"
  "src/type_traits/is_safe_integer.test.cpp"
  "src/type_traits/is_safe_integral.test.cpp"
  "src/type_traits/is_safe_non_bool_integral.test.cpp"
  "src/type_traits/is_safe_scalar.test.cpp"
  "src/type_traits/is_safe_signed_integer.test.cpp"
  "src/type_traits/is_safe_signed.test.cpp"
  "src/type_traits/is_safe_type.test.cpp"
  "src/type_traits/is_safe_unsigned_integer.test.cpp"
  "src/type_traits/is_safe_unsigned.test.cpp"
  "src/type_traits/is_same_rc.test.cpp"
  "src/type_traits/is_same_rcv.test.cpp"
  "src/type_traits/is_same_rcvref.test.cpp"
  "src/type_traits/is_same_rv.test.cpp"
  "src/type_traits/is_same.test.cpp"
  "src/type_traits/is_scalar.test.cpp"
  "src/type_traits/is_scoped_enum.no_is_scoped_enum.test.cpp"
  "src/type_traits/is_scoped_enum.test.cpp"
  "src/type_traits/is_signed_integer.test.cpp"
  "src/type_traits/is_signed.test.cpp"
  "src/type_traits/is_standard_layout.test.cpp"
  "src/type_traits/is_static_castable_to.test.cpp"
  "src/type_traits/is_swappable_with.test.cpp"
  "src/type_traits/is_swappable.test.cpp"
  "src/type_traits/is_trivial.test.cpp"
  "src/type_traits/is_trivially_assignable.test.cpp"
  "src/type_traits/is_trivially_constructible.test.cpp"
  "src/type_traits/is_trivially_copy_assignable.test.cpp"
  "src/type_traits/is_trivially_copy_constructible.test.cpp"
  "src/type_traits/is_trivially_copyable.test.cpp"
  "src/type_traits/is_trivially_default_constructible.test.cpp"
  "src/type_traits/is_trivially_destructible.test.cpp"
  "src/type_traits/is_trivially_move_assignable.test.cpp"
  "src/type_traits/is_trivially_move_constructible.test.cpp"
  "src/type_traits/is_unbounded_array.no_is_unbounded_array.test.cpp"
  "src/type_traits/is_unbounded_array.test.cpp"
  "src/type_traits/is_union.test.cpp"
  "src/type_traits/is_unsafe_arithmetic.test.cpp"
  "src/type_traits/is_unsafe_bool.test.cpp"
  "src/type_traits/is_unsafe_floating_point.test.cpp"
  "src/type_traits/is_unsafe_fundamental.test.cpp"
  "src/type_traits/is_unsafe_integer.test.cpp"
  "src/type_traits/is_unsafe_integral.test.cpp"
  "src/type_traits/is_unsafe_non_bool_integral.test.cpp"
  "src/type_traits/is_unsafe_scalar.test.cpp"
  "src/type_traits/is_unsafe_signed_integer.test.cpp"
  "src/type_traits/is_unsafe_signed.test.cpp"
  "src/type_traits/is_unsafe_type.test.cpp"
  "src/type_traits/is_unsafe_unsigned_integer.test.cpp"
  "src/type_traits/is_unsafe_unsigned.test.cpp"
  "src/type_traits/is_unscoped_enum.test.cpp"
  "src/type_traits/is_unsigned_integer.test.cpp"
  "src/type_traits/is_unsigned.test.cpp"
  "src/type_traits/is_void.test.cpp"
  "src/type_traits/is_volatile.test.cpp"
  "src/type_traits/make_safe.test.cpp"
  "src/type_traits/make_signed.test.cpp"
  "src/type_traits/make_unsafe.test.cpp"
  "src/type_traits/make_unsigned.test.cpp"
  "src/type_traits/negation.test.cpp"
  "src/type_traits/rank.test.cpp"
  "src/type_traits/remove_all_extents.nointrinsic.test.cpp"
  "src/type_traits/remove_all_extents.test.cpp"
  "src/type_traits/remove_const.test.cpp"
  "src/type_traits/remove_cv.test.cpp"
  "src/type_traits/remove_cvref.nointrinsic.test.cpp"
  "src/type_traits/remove_cvref.test.cpp"
  "src/type_traits/remove_extent.nointrinsic.test.cpp"
  "src/type_traits/remove_extent.test.cpp"
  "src/type_traits/remove_pointer.nointrinsic.test.cpp"
  "src/type_traits/remove_pointer.test.cpp"
  "src/type_traits/remove_reference.nointrinsic.test.cpp"
  "src/type_traits/remove_reference.test.cpp"
  "src/type_traits/remove_volatile.test.cpp"
  "src/type_traits/signed_int_of_size.test.cpp"
  "src/type_traits/size_constant.test.cpp"
  "src/type_traits/static_clamp.test.cpp"
  "src/type_traits/static_max.test.cpp"
  "src/type_traits/static_min.test.cpp"
  "src/type_traits/to_safe.test.cpp"
  "src/type_traits/to_unsafe.test.cpp"
  "src/type_traits/true_t.test.cpp"
  "src/type_traits/type_identity.test.cpp"
  "src/type_traits/underlying_type.nointrinsic.test.cpp"
  "src/type_traits/underlying_type.nointrinsic2.test.cpp"
  "src/type_traits/underlying_type.test.cpp"
  "src/type_traits/unsigned_int_of_size.test.cpp"
  "src/type_traits/void_t.test.cpp"
  # Base
  "src/phi_config.test.cpp"
  "src/type_traits.test.cpp")

if(${CMAKE_VERSION} VERSION_GREATER "3.7")
  source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${TEST_HEADERS} ${TEST_SOURCES})
endif()

if(${PHI_TEST_WITH_ALL_STANDARDS})
  set(used_standards ${phi_supported_standards})
else()
  set(used_standards ${phi_standard_version})
endif()

# Add tests
if(${PHI_TEST_SPLIT_FILES})
  foreach(file IN ITEMS ${TEST_SOURCES})
    # Compute test name
    get_filename_component(file_name ${file} NAME)
    string(REPLACE ".test.cpp" "" file_name ${file_name})
    string(REPLACE "." "_" file_name ${file_name})

    get_filename_component(directory ${file} DIRECTORY)
    file(RELATIVE_PATH directory "${CMAKE_CURRENT_SOURCE_DIR}/src" ${directory})
    string(REPLACE "/" "_" directory "${directory}")

    if(directory)
      set(test_file_name "${directory}_${file_name}")
    else()
      set(test_file_name "${file_name}")
    endif()

    foreach(std IN ITEMS ${used_standards})
      # Set tests names
      set(test_name "Phi_${test_file_name}-${std}")

      if(DEFINED CMAKE_CXX${std}_STANDARD_COMPILE_OPTION)
        phi_add_executable(
          NAME
          "${test_name}"
          SOURCES
          ${file}
          FOLDER
          "Tests/PhiCore"
          PRIVATE_LINK_LIBRARIES
          Phi::Core
          Phi::Test
          PRIVATE_INCLUDE_DIRS
          "include"
          STANDARD
          ${std})
        phi_add_test(TARGET "${test_name}")
      endif()
    endforeach()
  endforeach()
else()
  foreach(std IN ITEMS ${used_standards})
    # Set tests names
    set(test_name "Phi_CoreUnittest-${std}")

    if(DEFINED CMAKE_CXX${std}_STANDARD_COMPILE_OPTION)
      phi_add_executable(
        NAME
        "${test_name}"
        SOURCES
        ${TEST_SOURCES}
        FOLDER
        "Tests/PhiCore"
        PRIVATE_LINK_LIBRARIES
        Phi::Core
        Phi::Test
        PRIVATE_INCLUDE_DIRS
        "include"
        STANDARD
        ${std})
      phi_add_test(TARGET "${test_name}")
    endif()
  endforeach()
endif()
