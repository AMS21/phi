phi_include_guard()

include(CMakeParseArguments)
include(CompilerFlags)

function(phi_target_enable_coverage)
  # Command line arguments
  cmake_parse_arguments(cov "" "TARGET" "" ${ARGN})

  # Check required arguments
  if(NOT cov_TARGET)
    phi_error("phi_target_enable_coverage: You must specify TARGET")
  endif()

  # Check if target is actually valid
  if(NOT TARGET ${cov_TARGET})
    phi_error(
      "phi_target_enable_coverage: The specified target \"${cov_TARGET}\" doesn't seem to be valid")
  endif()

  # Check if we actually have coverage flags
  if(NOT phi_coverage_compile_flags AND phi_coverage_link_flags)
    phi_warn(
      "phi_target_enable_coverage: There we no coverage flags found for your compiler \"${CMAKE_CXX_COMPILER_ID}\"!"
    )
  endif()

  # Get target type
  get_property(
    target_type
    TARGET ${cov_TARGET}
    PROPERTY TYPE)

  if("${target_type}" STREQUAL "INTERFACE_LIBRARY")
    set(visibility_scope INTERFACE)
  else()
    set(visibility_scope PRIVATE)
  endif()

  # Get linker language
  get_property(
    target_linker_language
    TARGET ${cov_TARGET}
    PROPERTY LINKER_LANGUAGE)

  # Set coverage compile flags
  if("${target_linker_language}" STREQUAL "CXX" OR "${target_linker_language}" STREQUAL "")
    # Set C/C++ warning flags
    target_compile_options(${cov_TARGET} ${visibility_scope} ${phi_coverage_compile_flags}
                           ${phi_cxx_coverage_compile_flags})
  elseif("${target_linker_language}" STREQUAL "C")
    # Set only C warning flags
    target_compile_options(${cov_TARGET} ${visibility_scope} ${phi_coverage_compile_flags})
  endif()

  # Set coverage linker flags
  target_compile_options(${cov_TARGET} ${visibility_scope} ${phi_coverage_link_flags})
  target_link_options(${cov_TARGET} ${visibility_scope} ${phi_coverage_link_flags})

  # Replace always inline with just inline
  target_compile_definitions(${cov_TARGET} ${visibility_scope}
                                           PHI_CONFIG_ALWAYS_INLINE_OVERWRITE=inline)
  # Add define to inform user that it's a coverage build
  target_compile_definitions(${cov_TARGET} ${visibility_scope} PHI_CONFIG_COVERAGE_BUILD)
endfunction()
