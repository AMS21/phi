#include <phi/test/test_macros.hpp>

#include "test_types.hpp"
#include <phi/compiler_support/char8_t.hpp>
#include <phi/compiler_support/extensions/float128.hpp>
#include <phi/compiler_support/unused.hpp>
#include <phi/core/max_align_t.hpp>
#include <phi/core/nullptr_t.hpp>
#include <phi/type_traits/is_pod.hpp>
#include <phi/type_traits/is_standard_layout.hpp>
#include <phi/type_traits/is_trivial.hpp>
#include <phi/type_traits/is_trivially_copyable.hpp>
#include <phi/type_traits/is_trivially_default_constructible.hpp>
#include <cstddef> // std::max_align_t

TEST_CASE("max_align_t")
{
#if PHI_HAS_WORKING_IS_POD()
    STATIC_REQUIRE(phi::is_pod<phi::max_align_t>::value);
#endif
#if PHI_HAS_WORKING_IS_STANDARD_LAYOUT()
    STATIC_REQUIRE(phi::is_standard_layout<phi::max_align_t>::value);
#endif
#if PHI_HAS_WORKING_IS_TRIVIAL()
    STATIC_REQUIRE(phi::is_trivial<phi::max_align_t>::value);
#endif
#if PHI_HAS_WORKING_IS_TRIVIALLY_COPYABLE()
    STATIC_REQUIRE(phi::is_trivially_copyable<phi::max_align_t>::value);
#endif
#if PHI_HAS_WORKING_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE()
    STATIC_REQUIRE(phi::is_trivially_default_constructible<phi::max_align_t>::value);
#endif

    STATIC_REQUIRE(alignof(phi::max_align_t) >= alignof(phi::nullptr_t));
    STATIC_REQUIRE(alignof(phi::max_align_t) >= alignof(bool));
    STATIC_REQUIRE(alignof(phi::max_align_t) >= alignof(char));
    STATIC_REQUIRE(alignof(phi::max_align_t) >= alignof(signed char));
    STATIC_REQUIRE(alignof(phi::max_align_t) >= alignof(unsigned char));
    STATIC_REQUIRE(alignof(phi::max_align_t) >= alignof(short));
    STATIC_REQUIRE(alignof(phi::max_align_t) >= alignof(unsigned short));
    STATIC_REQUIRE(alignof(phi::max_align_t) >= alignof(int));
    STATIC_REQUIRE(alignof(phi::max_align_t) >= alignof(unsigned int));
    STATIC_REQUIRE(alignof(phi::max_align_t) >= alignof(long));
    STATIC_REQUIRE(alignof(phi::max_align_t) >= alignof(unsigned long));
    STATIC_REQUIRE(alignof(phi::max_align_t) >= alignof(long long));
    STATIC_REQUIRE(alignof(phi::max_align_t) >= alignof(unsigned long long));
    STATIC_REQUIRE(alignof(phi::max_align_t) >= alignof(float));
    STATIC_REQUIRE(alignof(phi::max_align_t) >= alignof(double));
    STATIC_REQUIRE(alignof(phi::max_align_t) >= alignof(long double));
    STATIC_REQUIRE(alignof(phi::max_align_t) >= alignof(char8_t));
    STATIC_REQUIRE(alignof(phi::max_align_t) >= alignof(char16_t));
    STATIC_REQUIRE(alignof(phi::max_align_t) >= alignof(char32_t));
    STATIC_REQUIRE(alignof(phi::max_align_t) >= alignof(wchar_t));
    STATIC_REQUIRE(alignof(phi::max_align_t) >= alignof(void*));
    STATIC_REQUIRE(alignof(phi::max_align_t) >= alignof(const void*));
    STATIC_REQUIRE(alignof(phi::max_align_t) >= alignof(volatile void*));
    STATIC_REQUIRE(alignof(phi::max_align_t) >= alignof(const volatile void*));
    STATIC_REQUIRE(alignof(phi::max_align_t) >= alignof(int(*)[3]));
    STATIC_REQUIRE(alignof(phi::max_align_t) >= alignof(int(*)[]));
    STATIC_REQUIRE(alignof(phi::max_align_t) >= alignof(void (*)()));
    STATIC_REQUIRE(alignof(phi::max_align_t) >= alignof(Enum));
    STATIC_REQUIRE(alignof(phi::max_align_t) >= alignof(EnumSigned));
    STATIC_REQUIRE(alignof(phi::max_align_t) >= alignof(EnumUnsigned));
    STATIC_REQUIRE(alignof(phi::max_align_t) >= alignof(EnumClass));
    STATIC_REQUIRE(alignof(phi::max_align_t) >= alignof(EnumStruct));
    STATIC_REQUIRE(alignof(phi::max_align_t) >= alignof(function_ptr));
    STATIC_REQUIRE(alignof(phi::max_align_t) >= alignof(member_object_ptr));
    STATIC_REQUIRE(alignof(phi::max_align_t) >= alignof(member_function_ptr));

#if PHI_HAS_EXTENSION_FLOAT128()
    STATIC_REQUIRE(alignof(phi::max_align_t) >= alignof(PHI_FLOAT128));
#endif

    // Standard compatibility
    STATIC_REQUIRE(alignof(phi::max_align_t) == alignof(std::max_align_t));

    // Make sure the type can be instantiated
    phi::max_align_t max_align;
    PHI_UNUSED_VARIABLE(max_align);
}
