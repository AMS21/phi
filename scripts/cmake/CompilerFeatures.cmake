phi_include_guard()

include(internal/CheckCXXSourceCompiles)
include(internal/CXXCheckTypeSize)
include(Standard)

# Lib
phi_check_cxx_source_compiles("#include <string_view>
int main() {}" PHI_HAS_LIB_STRING_VIEW)
phi_check_cxx_source_compiles("#include <span>
int main() {}" PHI_HAS_LIB_SPAN)
phi_check_cxx_source_compiles("#include <version>
int main() {}" PHI_HAS_LIB_VERSION)

# Only require the latest standard flag
set(CMAKE_REQUIRED_FLAGS "${phi_latest_standard_flag}")

# Type system
phi_cxx_check_type_size("void*" PHI_TYPE_SYSTEM_SIZEOF_VOIDPTR)

phi_cxx_check_type_size("bool" PHI_TYPE_SYSTEM_SIZEOF_BOOL)
phi_cxx_check_type_size("char" PHI_TYPE_SYSTEM_SIZEOF_CHAR)
phi_cxx_check_type_size("wchar_t" PHI_TYPE_SYSTEM_SIZEOF_WCHAR_T)
phi_cxx_check_type_size("short" PHI_TYPE_SYSTEM_SIZEOF_SHORT)
phi_cxx_check_type_size("int" PHI_TYPE_SYSTEM_SIZEOF_INT)
phi_cxx_check_type_size("long" PHI_TYPE_SYSTEM_SIZEOF_LONG)
phi_cxx_check_type_size("long long" PHI_TYPE_SYSTEM_SIZEOF_LONG_LONG)

phi_cxx_check_type_size("float" PHI_TYPE_SYSTEM_SIZEOF_FLOAT)
phi_cxx_check_type_size("double" PHI_TYPE_SYSTEM_SIZEOF_DOUBLE)
phi_cxx_check_type_size("long double" PHI_TYPE_SYSTEM_SIZEOF_LONG_DOUBLE)

phi_check_cxx_source_compiles("int main() { static_assert(char(-1) < char(0), \"\"); }"
                              PHI_TYPE_SYSTEM_CHAR_SIGNED)
phi_check_cxx_source_compiles("int main() { static_assert(wchar_t(-1) < wchar_t(0), \"\"); }"
                              PHI_TYPE_SYSTEM_WCHAR_T_SIGNED)

# Extended floating point types
phi_check_cxx_source_compiles("int main() { __float128 f; }" PHI_HAS_EXTENSION_FLOAT128)

# configure files
configure_file("scripts/cmake/configure/libraries.hpp.in"
               "${PHI_GENERATED_FILES_DIR}/phi/generated/compiler_support/libraries.hpp")
configure_file("scripts/cmake/configure/type_system.hpp.in"
               "${PHI_GENERATED_FILES_DIR}/phi/generated/compiler_support/type_system.hpp")
configure_file("scripts/cmake/configure/extensions.hpp.in"
               "${PHI_GENERATED_FILES_DIR}/phi/generated/compiler_support/extensions.hpp")
