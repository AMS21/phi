#include <phi/test/test_macros.hpp>

#include <phi/compiler_support/compiler.hpp>

TEST_CASE("Config Compiler", "[Config][Compiler]")
{
#if PHI_COMPILER_IS(CLANG)
    STATIC_REQUIRE(PHI_COMPILER_CLANG());
#endif
#if PHI_COMPILER_IS(GCC)
    STATIC_REQUIRE(PHI_COMPILER_GCC());
#endif
#if PHI_COMPILER_IS(MSVC)
    STATIC_REQUIRE(PHI_COMPILER_MSVC());
#endif
#if PHI_COMPILER_IS(MINGW)
    STATIC_REQUIRE(PHI_COMPILER_MINGW());
#endif
#if PHI_COMPILER_IS(EMCC)
    STATIC_REQUIRE(PHI_COMPILER_EMCC());
#endif
#if PHI_COMPILER_IS(ICC)
    STATIC_REQUIRE(PHI_COMPILER_ICC());
#endif

// Compiler compatibility
#if PHI_COMPILER_IS(GCC_COMPAT)
    STATIC_REQUIRE(PHI_COMPILER_GCC_COMPAT());
#endif
#if PHI_COMPILER_IS(CLANG_COMPAT)
    STATIC_REQUIRE(PHI_COMPILER_CLANG_COMPAT());
#endif
}

TEST_CASE("Specific flags")
{
#if PHI_COMPILER_IS(EMCC)
    STATIC_REQUIRE(PHI_COMPILER_EMCC());
    STATIC_REQUIRE(PHI_COMPILER_GCC_COMPAT());
    STATIC_REQUIRE(PHI_COMPILER_CLANG_COMPAT());

    STATIC_REQUIRE_FALSE(PHI_COMPILER_CLANG());
    STATIC_REQUIRE_FALSE(PHI_COMPILER_APPLECLANG());
    STATIC_REQUIRE_FALSE(PHI_COMPILER_GCC());
    STATIC_REQUIRE_FALSE(PHI_COMPILER_ICC());
    STATIC_REQUIRE_FALSE(PHI_COMPILER_MSVC());
    STATIC_REQUIRE_FALSE(PHI_COMPILER_MINGW());
#elif PHI_COMPILER_IS(CLANG)
    STATIC_REQUIRE(PHI_COMPILER_CLANG());
    STATIC_REQUIRE(PHI_COMPILER_GCC_COMPAT());
    STATIC_REQUIRE(PHI_COMPILER_CLANG_COMPAT());

    STATIC_REQUIRE_FALSE(PHI_COMPILER_APPLECLANG());
    STATIC_REQUIRE_FALSE(PHI_COMPILER_EMCC());
    STATIC_REQUIRE_FALSE(PHI_COMPILER_GCC());
    STATIC_REQUIRE_FALSE(PHI_COMPILER_ICC());
    STATIC_REQUIRE_FALSE(PHI_COMPILER_MSVC());
    STATIC_REQUIRE_FALSE(PHI_COMPILER_MINGW());
#elif PHI_COMPILER_IS(APPLECLANG)
    STATIC_REQUIRE(PHI_COMPILER_CLANG());
    STATIC_REQUIRE(PHI_COMPILER_GCC_COMPAT());
    STATIC_REQUIRE(PHI_COMPILER_CLANG_COMPAT());

    STATIC_REQUIRE_FALSE(PHI_COMPILER_CLANG());
    STATIC_REQUIRE_FALSE(PHI_COMPILER_EMCC());
    STATIC_REQUIRE_FALSE(PHI_COMPILER_GCC());
    STATIC_REQUIRE_FALSE(PHI_COMPILER_ICC());
    STATIC_REQUIRE_FALSE(PHI_COMPILER_MSVC());
    STATIC_REQUIRE_FALSE(PHI_COMPILER_MINGW());
#elif PHI_COMPILER_IS(GCC)
    STATIC_REQUIRE(PHI_COMPILER_GCC());
    STATIC_REQUIRE(PHI_COMPILER_GCC_COMPAT());
    STATIC_REQUIRE_FALSE(PHI_COMPILER_CLANG_COMPAT());

    STATIC_REQUIRE_FALSE(PHI_COMPILER_APPLECLANG());
    STATIC_REQUIRE_FALSE(PHI_COMPILER_EMCC());
    STATIC_REQUIRE_FALSE(PHI_COMPILER_CLANG());
    STATIC_REQUIRE_FALSE(PHI_COMPILER_ICC());
    STATIC_REQUIRE_FALSE(PHI_COMPILER_MSVC());
    STATIC_REQUIRE_FALSE(PHI_COMPILER_MINGW());
#elif PHI_COMPILER_IS(MINGW)
    STATIC_REQUIRE(PHI_COMPILER_MINGW());
    STATIC_REQUIRE(PHI_COMPILER_GCC_COMPAT());
    STATIC_REQUIRE_FALSE(PHI_COMPILER_CLANG_COMPAT());

    STATIC_REQUIRE_FALSE(PHI_COMPILER_APPLECLANG());
    STATIC_REQUIRE_FALSE(PHI_COMPILER_EMCC());
    STATIC_REQUIRE_FALSE(PHI_COMPILER_CLANG());
    STATIC_REQUIRE_FALSE(PHI_COMPILER_ICC());
    STATIC_REQUIRE_FALSE(PHI_COMPILER_MSVC());
    STATIC_REQUIRE_FALSE(PHI_COMPILER_GCC());
#elif PHI_COMPILER_IS(MSVC)
    STATIC_REQUIRE(PHI_COMPILER_MSVC());
    STATIC_REQUIRE_FALSE(PHI_COMPILER_GCC_COMPAT());
    STATIC_REQUIRE_FALSE(PHI_COMPILER_CLANG_COMPAT());

    STATIC_REQUIRE_FALSE(PHI_COMPILER_APPLECLANG());
    STATIC_REQUIRE_FALSE(PHI_COMPILER_EMCC());
    STATIC_REQUIRE_FALSE(PHI_COMPILER_GCC());
    STATIC_REQUIRE_FALSE(PHI_COMPILER_ICC());
    STATIC_REQUIRE_FALSE(PHI_COMPILER_CLANG());
    STATIC_REQUIRE_FALSE(PHI_COMPILER_MINGW());
#elif PHI_COMPILER_IS(ICC)
    STATIC_REQUIRE(PHI_COMPILER_ICC());
    STATIC_REQUIRE_FALSE(PHI_COMPILER_GCC_COMPAT());
    STATIC_REQUIRE_FALSE(PHI_COMPILER_CLANG_COMPAT());

    STATIC_REQUIRE_FALSE(PHI_COMPILER_APPLECLANG());
    STATIC_REQUIRE_FALSE(PHI_COMPILER_EMCC());
    STATIC_REQUIRE_FALSE(PHI_COMPILER_GCC());
    STATIC_REQUIRE_FALSE(PHI_COMPILER_MSVC()));
    STATIC_REQUIRE_FALSE(PHI_COMPILER_CLANG());
    STATIC_REQUIRE_FALSE(PHI_COMPILER_MINGW());
#endif
}
