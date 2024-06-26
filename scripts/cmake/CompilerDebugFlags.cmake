phi_include_guard()

include(CMakeParseArguments)
include(CompilerFlags)

set(phi_extra_debug_defines
    _GLIBCXX_ASSERTIONS _GLIBCXX_DEBUG _GLIBCXX_DEBUG_PEDANTIC _GLIBCXX_SANITIZE_VECTOR
    _LIBCPP_ENABLE_THREAD_SAFETY_ANNOTATIONS
    CACHE INTERNAL "")

# Starting with LLVM 17 _LIBCPP_ENABLE_ASSERTIONS was replaced with _LIBCPP_HARDENING_MODE
if(PHI_COMPILER_CLANG AND PHI_CLANG_VERSION VERSION_GREATER_EQUAL 17)
  set(phi_extra_debug_defines ${phi_extra_debug_defines}
                              _LIBCPP_HARDENING_MODE=_LIBCPP_HARDENING_MODE_DEBUG)
else()
  set(phi_extra_debug_defines ${phi_extra_debug_defines} _LIBCPP_ENABLE_ASSERTIONS=1)
endif()

function(phi_target_enable_extra_debug_flags)
  # Command line arguments
  cmake_parse_arguments(dbg "" "TARGET" "CONFIGS" ${ARGN})

  # Check required arguments
  if(NOT dbg_TARGET)
    phi_error("phi_target_enable_extra_debug_flags: You must specify TARGET")
  endif()

  # Check if target is valid
  if(NOT TARGET ${dbg_TARGET})
    phi_error(
      "phi_target_enable_extra_debug_flags: The specified target \"${dbg_TARGET}\" doesn't seem to be valid"
    )
  endif()

  # Optionally set configs
  if(NOT DEFINED ${dbg_CONFIGS})
    # set a default value
    set(dbg_CONFIGS "Debug;RelWithDebInfo")
  endif()

  # Get target type
  get_property(
    target_type
    TARGET ${dbg_TARGET}
    PROPERTY TYPE)

  if("${target_type}" STREQUAL "INTERFACE_LIBRARY")
    set(visibility_scope INTERFACE)
  else()
    set(visibility_scope PRIVATE)
  endif()

  # Enable extra debug flags for each configuration
  foreach(config ${dbg_CONFIGS})
    if("${config}" STREQUAL "Debug")
      target_compile_options(${dbg_TARGET} ${visibility_scope}
                             $<$<CONFIG:${config}>:${phi_debug_only_flags}>)
    endif()

    # Set each flag
    target_compile_options(${dbg_TARGET} ${visibility_scope}
                           $<$<CONFIG:${config}>:${phi_debug_flags}>)

    # Set extra debug defines
    target_compile_definitions(${dbg_TARGET} ${visibility_scope}
                                             $<$<CONFIG:${config}>:${phi_extra_debug_defines}>)
  endforeach()
endfunction()
