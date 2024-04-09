phi_include_guard()

include(CMakeParseArguments)
include(Common)
include(CompilerDebugFlags)
include(CompilerOptimizations)
include(CompilerWarnings)
include(Coverage)
include(Exceptions)
include(FloatingPointModel)
include(Formatting)
include(Functions)
include(Linker)
include(RuntimeTypeInformation)
include(Sanitizers)
include(Standard)
include(StandardLibrary)
include(StaticAnalyzers)
include(Fuzzing)

#
function(phi_configure_project)
  # Command line arguments
  set(CMD_OPTIONS
      "NO_COMMON;TIME_TRACE;DEBUG_FLAGS;LTO;OPTIMIZATION_FLAGS;WARNINGS;WARNINGS_AS_ERRORS;PEDANTIC;COVERAGE;FPM_FAST;FPM_PRECISE;NO_EXCEPTIONS;UNITY_BUILD;CXX_EXTENSIONS;NO_RTTI;FUZZING_BUILD"
  )
  set(CMD_ONE_VALUE "PSO;STANDARD;EXTERNAL;STANDARD_LIBRARY")
  set(CMD_MULTI_VALUE "SANITIZER;STATIC_ANALYZERS")

  cmake_parse_arguments(conf "${CMD_OPTIONS}" "${CMD_ONE_VALUE}" "${CMD_MULTI_VALUE}" ${ARGN})

  # General parser error
  if(conf_UNPARSED_ARGUMENTS)
    phi_error("phi_configure_project: Unrecognized arguments \"${conf_UNPARSED_ARGUMENTS}\"")
  endif()

  if(conf_KEYWORDS_MISSING_VALUES)
    phi_error("phi_configure_project: Keywords missing values \"${conf_KEYWORDS_MISSING_VALUES}\"")
  endif()

  # Handle optional EXTERNAL
  if(DEFINED conf_EXTERNAL)
    # Make path absolute
    if(NOT IS_ABSOLUTE ${conf_EXTERNAL})
      get_filename_component(external_absolute "${conf_EXTERNAL}" REALPATH BASE_DIR
                             "${CMAKE_CURRENT_SOURCE_DIR}")
    endif()

    # Check if path exists
    if(NOT EXISTS "${external_absolute}")
      phi_error(
        "phi_configure_project: The given external path \"${conf_EXTERNAL}\" (${external_absolute}) doesn't seem to exist"
      )
    endif()

    # Check if directory
    if(NOT IS_DIRECTORY "${external_absolute}")
      phi_error(
        "phi_configure_project: The given external directory \"${conf_EXTERNAL}\" (${external_absolute}) doesn't seem to be a directory!"
      )
    endif()

    # Get path length
    string(LENGTH ${conf_EXTERNAL} external_length)
  endif()

  phi_get_all_targets(_targets_list)

  foreach(target ${_targets_list})
    # Get target type
    get_property(
      target_type
      TARGET ${target}
      PROPERTY TYPE)

    get_property(
      target_linker_language
      TARGET ${target}
      PROPERTY LINKER_LANGUAGE)

    # Skip utility targets
    if("${target_type}" STREQUAL "UTILITY")
      continue()
    endif()

    if("${target_type}" STREQUAL "INTERFACE_LIBRARY")
      set(visibility_scope INTERFACE)
    else()
      set(visibility_scope PRIVATE)
    endif()

    # Link common unless disabled
    if(NOT conf_NO_COMMON)
      if(conf_TIME_TRACE)
        phi_target_set_common_flags(TARGET ${target} ALL)
      else()
        phi_target_set_common_flags(TARGET ${target} COLOR_DIAGNOSTICS)
      endif()
    endif()

    # Link Debug flags
    if(conf_DEBUG_FLAGS)
      phi_target_enable_extra_debug_flags(TARGET ${target})
    endif()

    # Compiler Optimizations
    if(conf_OPTIMIZATION_FLAGS
       OR conf_LTO
       OR DEFINED conf_PSO)
      # Build command
      set(opt_cmd)
      if(conf_LTO)
        set(opt_cmd LTO)
      endif()
      if(DEFINED conf_PSO)
        set(opt_cmd ${opt_cmd} PSO ${conf_PSO})
      endif()

      phi_target_enable_optimizations(TARGET ${target} ${opt_cmd})
    endif()

    # Coverage
    if(conf_COVERAGE)
      phi_target_enable_coverage(TARGET ${target})
    endif()

    # FloatingPointModel
    set(fpm_cmd DEFAULT)
    if(conf_FPM_FAST)
      set(fpm_cmd FAST)
    elseif(conf_FPM_PRECISE)
      set(fpm_cmd PRECISE)
    endif()

    phi_target_set_floating_point_model(TARGET ${target} ${fpm_cmd})

    # TODO: Formatting

    # User Linker
    phi_configure_linker(${target})

    # Standard
    set(use_std latest)
    if(DEFINED conf_STANDARD)
      set(use_std ${conf_STANDARD})
    endif()
    set(use_ext)
    if(DEFINED conf_EXTENSIONS)
      set(use_ext EXTENSIONS)
    endif()
    phi_target_set_standard(TARGET ${target} STANDARD ${use_std} ${use_ext})

    # No exceptions
    if(conf_NO_EXCEPTIONS)
      phi_target_disable_exceptions(TARGET ${target})
    endif()

    # Fuzzing build
    if(conf_FUZZING_BUILD)
      phi_target_enable_fuzzing_flags(TARGET ${target})
    endif()

    # Unity build
    if(conf_UNITY_BUILD)
      set_target_properties(${target} PROPERTIES UNITY_BUILD ON)
    endif()

    # Handle external libraries
    set(is_external FALSE)
    if(DEFINED conf_EXTERNAL)
      # Get target source dir
      get_target_property(target_source_dir ${target} SOURCE_DIR)

      # Source dir to relative
      file(RELATIVE_PATH target_src_dir_rel ${CMAKE_CURRENT_SOURCE_DIR} ${target_source_dir})

      string(SUBSTRING "${target_src_dir_rel}" 0 ${external_length} test_string)

      if("${test_string}" STREQUAL ${conf_EXTERNAL})
        set(is_external TRUE)
      endif()
    endif()

    # Static analyzer
    if(DEFINED conf_STATIC_ANALYZERS AND NOT is_external)
      set(extra)
      if(conf_WARNINGS_AS_ERRORS)
        set(extra WARNINGS_AS_ERRORS)
      endif()

      phi_target_use_static_analyzers(TARGET ${target} ${conf_STATIC_ANALYZERS} ${extra})
    endif()

    # Compiler warnings
    if((conf_WARNINGS
        OR conf_WARNINGS_AS_ERRORS
        OR conf_PEDANTIC)
       AND NOT is_external)
      # Build command
      set(warn_cmd "")
      if(conf_WARNINGS_AS_ERRORS)
        set(warn_cmd WARNINGS_AS_ERRORS)
      endif()
      if(conf_PEDANTIC)
        set(warn_cmd ${warn_cmd} PEDANTIC)
      endif()

      phi_target_set_warnings(TARGET ${target} ${warn_cmd})
    endif()

    # Enable exception warnings only when exceptions are enabled and were using C++
    if(conf_WARNINGS
       AND NOT conf_NO_EXCEPTIONS
       AND NOT is_external
       AND target_linker_language STREQUAL CXX)
      target_compile_options(${target} ${visibility_scope} ${phi_exception_warning_flag})
    endif()

    # RTTI
    if(conf_NO_RTTI)
      phi_target_set_rtti(TARGET ${target} DISABLE)
    else()
      phi_target_set_rtti(TARGET ${target} ENABLE)
    endif()

    # STANDARD_LIBRARY
    if(conf_STANDARD_LIBRARY)
      phi_target_set_stdlib(TARGET ${target} LIBRARY ${conf_STANDARD_LIBRARY})
    else()
      phi_target_set_stdlib(TARGET ${target} LIBRARY DEFAULT)
    endif()

    # Sanitizers
    if(DEFINED conf_SANITIZER AND NOT is_external)
      phi_target_enable_sanitizer(TARGET ${target} SANITIZERS ${conf_SANITIZER})
    endif()

    # Thread support
    if(PHI_CONFIG_THREADS)
      target_compile_definitions(${target} ${visibility_scope} "PHI_CONFIG_THREADS")
    else()
      target_compile_definitions(${target} ${visibility_scope} "PHI_CONFIG_NO_THREADS")
    endif()

    # Handle external target
    if(is_external)
      # Mark include directory as system include
      get_target_property(include_dir ${target} INTERFACE_INCLUDE_DIRECTORIES)
      set_target_properties(${target} PROPERTIES INTERFACE_SYSTEM_INCLUDE_DIRECTORIES
                                                 "${include_dir}")

      # Disable all warnings for external targets
      if(NOT ${target_type} STREQUAL "INTERFACE_LIBRARY")
        target_compile_options(${target} ${visibility_scope} ${phi_disable_all_warnings_flag})
      endif()

      # Set folder to external
      if(NOT ${CMAKE_VERSION} VERSION_LESS "3.17" OR NOT ${target_type} STREQUAL
                                                     "INTERFACE_LIBRARY")
        # Get targets current folder
        get_target_property(target_folder ${target} FOLDER)

        if(target_folder)
          # Prepend external
          set_target_properties(${target} PROPERTIES FOLDER "external/${target_folder}")
        else()
          # Simply set to external
          set_target_properties(${target} PROPERTIES FOLDER "external")
        endif()
      endif()
    endif()
  endforeach()
endfunction()
