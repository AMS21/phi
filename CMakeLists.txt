# Phi top level cmake file

# Set minimum required cmake version
if(${CMAKE_VERSION} VERSION_GREATER 3.26)
  # Since CMake 3.27 all versions before 3.5 are deprecated
  # https://cmake.org/cmake/help/latest/command/cmake_minimum_required.html#policy-settings
  cmake_minimum_required(VERSION 3.5)
else()
  cmake_minimum_required(VERSION 2.8.12)
endif()

# Policy
if(${CMAKE_VERSION} VERSION_LESS 3.30)
  cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
  cmake_policy(VERSION 3.30)
endif()

# Disable scanning for modules since we don't use them and they increase build times and break some
# GCC-14 builds
set(CMAKE_CXX_SCAN_FOR_MODULES
    OFF
    CACHE FORCE INTERNAL "")

# CMake modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/scripts/cmake)

include(internal/IncludeGuard)
include(Functions)

set(PHI_VERSION_MAJOR 0)
set(PHI_VERSION_MINOR 1)
set(PHI_VERSION_PATCH 0)

phi_log("Configuring Phi version ${PHI_VERSION_MAJOR}.${PHI_VERSION_MINOR}.${PHI_VERSION_PATCH}")

# Project
if(${CMAKE_VERSION} VERSION_LESS 3.0)
  project(Phi CXX C)
else()
  project(
    Phi
    VERSION "${PHI_VERSION_MAJOR}.${PHI_VERSION_MINOR}.${PHI_VERSION_PATCH}"
    LANGUAGES CXX C)
endif()

# Check if Phi is being used directly or via add_subdirectory, but allow overriding
if(NOT DEFINED PHI_MAIN_PROJECT)
  if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    phi_set_cache_value(PHI_MAIN_PROJECT ON)
    phi_trace("Building as main project")
  else()
    phi_set_cache_value(PHI_MAIN_PROJECT OFF)
    phi_trace("Building as submodule")
  endif()
endif()

# Load environment information
include(Environment)

# Options
option(PHI_BUILD_TESTS "Build tests" ${PHI_MAIN_PROJECT})
option(PHI_BUILD_EXAMPLES "Build examples" ${PHI_MAIN_PROJECT})
option(PHI_BUILD_DOCS "Generate the source code documentation" OFF)
option(PHI_USE_PCH "Use a pre compiled header (pch)" OFF) # TODO
option(PHI_USE_UNITY_BUILD "Enable unity builds" OFF)
option(PHI_TEST_RUNTIME_FAILURES "Build and run runtime failure tests" ON)
option(PHI_TEST_COMPILE_FAILURES "Build and run compile failure tests" ON)
option(PHI_COVERAGE_BUILD "Enable flags for creating coverage data" OFF)
option(PHI_AUTO_FORMATTING "Automatically format all source code during builds" ${PHI_MAIN_PROJECT})
option(PHI_TEST_WITH_VALGRIND "Automatically run tests with valgrind and print results" OFF)
option(PHI_ENABLE_CACHE "Enable cache if available" ON)
option(PHI_ENABLE_OPTIMIZATION_FLAGS "Enable all the optimization flags from Phi" ON)
option(PHI_WARNINGS_AS_ERRORS "Treat compiler warnings as errors" ${PHI_MAIN_PROJECT})
option(PHI_PEDANTIC_WARNINGS "Enable pedantic mode" ON)
option(PHI_ENABLE_USER_LINKER "Enable a specific linker if available" OFF)
option(PHI_BUILD_WITH_TIME_TRACE
       "Enable -ftime-trace to generate time tracing .json files on clang" OFF)
option(PHI_ENABLE_LTO "Enable Link Time Optimization" OFF)
option(PHI_COLOR_DIAGNOSTICS "Enable colored diagnostics" ON)
option(PHI_ENABLE_CPPCHECK "Enable static analysis with cppcheck" OFF)
option(PHI_ENABLE_CLANG_TIDY "Enable static analysis with clang-tidy" OFF)
option(PHI_ENABLE_IWYU "Enable static analysis with include-what-you-use" OFF)
option(PHI_TEST_WITH_ALL_STANDARDS "Build test application for all standards" ON)
option(PHI_TEST_SPLIT_FILES "Split unittest files into multiple executables" ${PHI_COMPILER_EMCC})
option(PHI_FUZZING_BUILD "Enable specific flags useful for fuzzing" OFF)

phi_option(PHI_STANDARD_RUNTIME "Which standard runtime to use. Only affects windows platforms"
           STRING "Dynamic")
set_property(CACHE PHI_STANDARD_RUNTIME PROPERTY STRINGS "Dynamic" "Static")

phi_option(PHI_STANDARD_LIBRARY "Which standard library to use" STRING "Default")
set_property(CACHE PHI_STANDARD_LIBRARY PROPERTY STRINGS "Default" "libstdc++" "libc++" "platform")

phi_option(PHI_STANDARD "Which C++ Standard to use" STRING "latest")
set_property(
  CACHE PHI_STANDARD
  PROPERTY STRINGS
           "latest"
           "11"
           "14"
           "17"
           "20"
           "23"
           "26")

option(PHI_ENABLE_PSO "Enable platform specific optimization" OFF)
phi_option(PHI_ARCH "Optimization target for platform specific optimization" STRING "native")

phi_option(PHI_FUZZING_LIBRARY "The fuzzing library to use (use default to let phi figure it out)"
           STRING "default")

# CI Builds Settings
if(${PHI_CI_BUILD} AND ${PHI_MAIN_PROJECT})
  phi_trace("Is CI build")

  # Disable auto formatting
  set(PHI_AUTO_FORMATTING
      FALSE
      CACHE BOOL "" FORCE)

  # Enable verbose makefile
  set(CMAKE_VERBOSE_MAKEFILE
      TRUE
      CACHE BOOL "" FORCE)
endif()

# Settings
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Set output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

phi_set_cache_value(PHI_GENERATED_FILES_DIR "${CMAKE_BINARY_DIR}/generated-includes/")

# Warn about not out-of-source builds
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
  phi_warn(
    "You shouldn't build in a source directory (or any directory with a CMakeLists.txt file). Please consider making a build subdirectory."
  )
endif()

set(PHI_BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Load configuration
include(PhiConfiguration)
include(ProjectOptions)

# Find optional system libs (https://cmake.org/cmake/help/latest/module/FindThreads.html)
find_package(Threads)

if(Threads_FOUND)
  phi_set_cache_value(PHI_CONFIG_THREADS 1)
else()
  phi_set_cache_value(PHI_CONFIG_THREADS 0)
endif()

# Load libs
add_subdirectory(libs)

# Examples
if(${PHI_BUILD_EXAMPLES})
  add_subdirectory(examples)
endif()

# Tests
if(${PHI_BUILD_TESTS})
  include(Testing)

  add_subdirectory(tests)
endif()

# Documentation
if(${PHI_BUILD_DOCS})
  add_subdirectory(docs)
endif()

# Set configure options
set(configure_options DEBUG_FLAGS WARNINGS STANDARD_LIBRARY "${PHI_STANDARD_LIBRARY}") # Default

if(PHI_USE_UNITY_BUILD)
  list(APPEND configure_options UNITY_BUILD)
endif()

if(PHI_COVERAGE_BUILD)
  list(APPEND configure_options COVERAGE)
endif()

if(PHI_ENABLE_OPTIMIZATION_FLAGS)
  list(APPEND configure_options OPTIMIZATION_FLAGS)
endif()

if(PHI_WARNINGS_AS_ERRORS)
  list(APPEND configure_options WARNINGS_AS_ERRORS)
endif()

if(PHI_PEDANTIC_WARNINGS)
  list(APPEND configure_options PEDANTIC)
endif()

if(PHI_BUILD_WITH_TIME_TRACE)
  list(APPEND configure_options TIME_TRACE)
endif()

if(PHI_ENABLE_LTO)
  list(APPEND configure_options LTO)
endif()

if(PHI_FUZZING_BUILD)
  list(APPEND configure_options FUZZING_BUILD)
endif()

# Configure static analyzers
set(config_sa)
if(PHI_ENABLE_CPPCHECK)
  list(APPEND config_sa CPPCHECK)
endif()
if(PHI_ENABLE_CLANG_TIDY)
  list(APPEND config_sa CLANG_TIDY)
endif()
if(PHI_ENABLE_IWYU)
  list(APPEND config_sa IWYU)
endif()

if(config_sa)
  list(APPEND configure_options STATIC_ANALYZERS ${config_sa})
endif()

# Configure sanitizers
set(config_sanitizers)
foreach(option ${PHI_SANITIZER_OPTIONS})
  string(REPLACE "-" "_" var_option ${option})
  string(TOUPPER ${var_option} var_option)

  if(PHI_ENABLE_SANITIZER_${var_option})
    list(APPEND config_sanitizers ${option})

    phi_log("Enabling ${option} sanitizer")
  endif()
endforeach()

if(config_sanitizers)
  list(APPEND configure_options SANITIZER ${config_sanitizers})
endif()

if(PHI_ENABLE_PSO)
  list(APPEND configure_options PSO ${PHI_ARCH})
endif()

phi_configure_project(${configure_options})
