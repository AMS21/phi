phi_include_guard()

# target_link_options (CMake 3.13) Reference:
# https://cmake.org/cmake/help/latest/command/target_link_options.html
if(${CMAKE_VERSION} VERSION_LESS "3.13")
  macro(target_link_options)
    target_compile_options(${ARGN})
  endmacro(target_link_options)
endif()
