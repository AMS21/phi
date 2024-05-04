#ifndef INCG_PHI_COMPILER_SUPPORT_FEATURES_HPP
#define INCG_PHI_COMPILER_SUPPORT_FEATURES_HPP

#include "phi/compiler_support/compiler.hpp"
#include "phi/compiler_support/cpp_standard.hpp"

// C++-11 features
// https://en.cppreference.com/w/cpp/11
// https://en.cppreference.com/w/cpp/compiler_support/11
#if PHI_CPP_STANDARD_IS_ATLEAST(11)

// constexpr
// https://en.cppreference.com/w/cpp/language/constexpr
// https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2007/n2235.pdf
#    if PHI_COMPILER_IS_ATLEAST(GCC, 4, 6, 0) || PHI_COMPILER_IS_ATLEAST(CLANG, 3, 1, 0) ||        \
            PHI_COMPILER_IS_ATLEAST(MSVC, 19, 0, 0) || PHI_COMPILER_IS(APPLECLANG) ||              \
            PHI_COMPILER_IS(EMCC)
#        define PHI_HAS_FEATURE_CONSTEXPR() 1
#    else
#        define PHI_HAS_FEATURE_CONSTEXPR() 0
#    endif

// Attribute noreturn
// https://en.cppreference.com/w/cpp/language/attributes/noreturn
// https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2008/n2761.pdf
#    if PHI_COMPILER_IS_ATLEAST(GCC, 4, 8, 0) || PHI_COMPILER_IS_ATLEAST(CLANG, 3, 3, 0) ||        \
            PHI_COMPILER_IS_ATLEAST(MSVC, 19, 0, 0) || PHI_COMPILER_IS(APPLECLANG) ||              \
            PHI_COMPILER_IS(EMCC)
#        define PHI_HAS_FEATURE_ATTRIBUTE_NORETURN() 1
#    else
#        define PHI_HAS_FEATURE_ATTRIBUTE_NORETURN() 0
#    endif

// extern template
// https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2006/n1987.htm
#    if PHI_COMPILER_IS_ATLEAST(GCC, 3, 3, 0) || PHI_COMPILER_IS(CLANG) ||                         \
            PHI_COMPILER_IS_ATLEAST(MSVC, 12, 0, 0) || PHI_COMPILER_IS(APPLECLANG) ||              \
            PHI_COMPILER_IS(EMCC)
#        define PHI_HAS_FEATURE_EXTERN_TEMPLATE() 1
#    else
#        define PHI_HAS_FEATURE_EXTERN_TEMPLATE() 0
#    endif

// static assert
// https://en.cppreference.com/w/cpp/language/static_assert
// https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2004/n1720.html
#    if PHI_COMPILER_IS_ATLEAST(GCC, 4, 3, 0) || PHI_COMPILER_IS_ATLEAST(CLANG, 2, 9, 0) ||        \
            PHI_COMPILER_IS_ATLEAST(MSVC, 16, 0, 0) || PHI_COMPILER_IS(APPLECLANG) ||              \
            PHI_COMPILER_IS(EMCC)
#        define PHI_HAS_FEATURE_STATIC_ASSERT() 1
#    else
#        define PHI_HAS_FEATURE_STATIC_ASSERT() 0
#    endif

// auto
// https://en.cppreference.com/w/cpp/language/auto
// https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2006/n1984.pdf
#    if PHI_COMPILER_IS_ATLEAST(GCC, 4, 4, 0) || PHI_COMPILER_IS(CLANG) ||                         \
            PHI_COMPILER_IS_ATLEAST(MSVC, 16, 0, 0) || PHI_COMPILER_IS(APPLECLANG) ||              \
            PHI_COMPILER_IS(EMCC)
#        define PHI_HAS_FEATURE_AUTO() 1
#    else
#        define PHI_HAS_FEATURE_AUTO() 0
#    endif

// noexcept
// https://en.cppreference.com/w/cpp/language/noexcept
// https://en.cppreference.com/w/cpp/language/noexcept_spec
// https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2010/n3050.html
#    if PHI_COMPILER_IS_ATLEAST(GCC, 4, 6, 0) || PHI_COMPILER_IS_ATLEAST(CLANG, 3, 0, 0) ||        \
            PHI_COMPILER_IS(APPLECLANG) || PHI_COMPILER_IS(EMCC) ||                                \
            PHI_COMPILER_IS_ATLEAST(MSVC, 19, 0, 0)
#        define PHI_HAS_FEATURE_NOEXCEPT() 1

// Special feature to check for a problem with gcc prior to version 9 in which you could not use a noexcept expression
// which called a object member function
#        if PHI_COMPILER_WORKAROUND(GCC, 9, 0, 0)
#            define PHI_HAS_FEATURE_NOEXCEPT_CLASS_EXPR() 1
#        else
#            define PHI_HAS_FEATURE_NOEXCEPT_CLASS_EXPR() 0
#        endif

#    else
#        define PHI_HAS_FEATURE_NOEXCEPT()            0
#        define PHI_HAS_FEATURE_NOEXCEPT_CLASS_EXPR() 0
#    endif

// Lambda expression
// https://en.cppreference.com/w/cpp/language/lambda
// https://wg21.link/N2550
// https://wg21.link/N2658
// https://wg21.link/N2927
#    if PHI_COMPILER_IS_ATLEAST(GCC, 4, 5, 0) || PHI_COMPILER_IS_ATLEAST(CLANG, 3, 1, 0) ||        \
            PHI_COMPILER_IS_ATLEAST(MSVC, 17, 0, 0) || PHI_COMPILER_IS(APPLECLANG) ||              \
            PHI_COMPILER_IS(EMCC)
#        define PHI_HAS_FEATURE_LAMBDA() 1
#    else
#        define PHI_HAS_FEATURE_LAMBDA() 0
#    endif

// variadic templates
// https://en.cppreference.com/w/cpp/language/parameter_pack
// https://wg21.link/N2242
// https://wg21.link/N2555
#    if PHI_COMPILER_IS_ATLEAST(GCC, 4, 4, 0) || PHI_COMPILER_IS_ATLEAST(CLANG, 2, 9, 0) ||        \
            PHI_COMPILER_IS_ATLEAST(MSVC, 18, 0, 0) || PHI_COMPILER_IS(APPLECLANG) ||              \
            PHI_COMPILER_IS(EMCC)
#        define PHI_HAS_FEATURE_VARIADIC_TEMPLATE() 1
#    else
#        define PHI_HAS_FEATURE_VARIADIC_TEMPLATE() 0
#    endif

// alias templates (using declarations)
// https://en.cppreference.com/w/cpp/language/type_alias
// https://wg21.link/N2258
#    if PHI_COMPILER_IS_ATLEAST(GCC, 4, 7, 0) || PHI_COMPILER_IS_ATLEAST(CLANG, 2, 9, 0) ||        \
            PHI_COMPILER_IS_ATLEAST(MSVC, 19, 0, 0) || PHI_COMPILER_IS(APPLECLANG) ||              \
            PHI_COMPILER_IS(EMCC)
#        define PHI_HAS_FEATURE_ALIAS_TEMPLATES() 1
#    else
#        define PHI_HAS_FEATURE_ALIAS_TEMPLATES() 0
#    endif

// decltype
// https://en.cppreference.com/w/cpp/language/decltype
// https://wg21.link/N2343
// https://wg21.link/N3276
#    if PHI_COMPILER_IS_ATLEAST(GCC, 4, 8, 1) || PHI_COMPILER_IS_ATLEAST(CLANG, 2, 9, 0) ||        \
            PHI_COMPILER_IS_ATLEAST(MSVC, 16, 0, 0) || PHI_COMPILER_IS(APPLECLANG) ||              \
            PHI_COMPILER_IS(EMCC)
#        define PHI_HAS_FEATURE_DECLTYPE() 1
#    else
#        define PHI_HAS_FEATURE_DECLTYPE() 0
#    endif

// Rvalue references
// https://en.cppreference.com/w/cpp/language/reference#Rvalue_references
// https://wg21.link/N2118
// https://wg21.link/N2844
// https://cplusplus.github.io/CWG/issues/1138.html
#    if PHI_COMPILER_IS_ATLEAST(GCC, 4, 5, 0) || PHI_COMPILER_IS_ATLEAST(CLANG, 2, 9, 0) ||        \
            PHI_COMPILER_IS_ATLEAST(MSVC, 17, 0, 0) || PHI_COMPILER_IS(APPLECLANG) ||              \
            PHI_COMPILER_IS(EMCC)
#        define PHI_HAS_FEATURE_RVALUE_REFERENCES() 1
#    else
#        define PHI_HAS_FEATURE_RVALUE_REFERENCES() 0
#    endif

#else
#    define PHI_HAS_FEATURE_CONSTEXPR()           0
#    define PHI_HAS_FEATURE_ATTRIBUTE_NORETURN()  0
#    define PHI_HAS_FEATURE_EXTERN_TEMPLATE()     0
#    define PHI_HAS_FEATURE_STATIC_ASSERT()       0
#    define PHI_HAS_FEATURE_AUTO()                0
#    define PHI_HAS_FEATURE_NOEXCEPT()            0
#    define PHI_HAS_FEATURE_NOEXCEPT_EXPR()       0
#    define PHI_HAS_FEATURE_NOEXCEPT_CLASS_EXPR() 0
#    define PHI_HAS_FEATURE_LAMBDA()              0
#    define PHI_HAS_FEATURE_VARIADIC_TEMPLATE()   0
#    define PHI_HAS_FEATURE_ALIAS_TEMPLATES()     0
#    define PHI_HAS_FEATURE_DECLTYPE()            0
#    define PHI_HAS_FEATURE_RVALUE_REFERENCES()   0
#endif

// C++-14 features
// https://en.cppreference.com/w/cpp/14
// https://en.cppreference.com/w/cpp/compiler_support/14
#if PHI_CPP_STANDARD_IS_ATLEAST(14)

// binary literals
// https://en.cppreference.com/w/cpp/language/integer_literal
// https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2012/n3472.pdf
#    if PHI_COMPILER_IS_ATLEAST(GCC, 4, 9, 0) || PHI_COMPILER_IS_ATLEAST(CLANG, 2, 9, 0) ||        \
            PHI_COMPILER_IS_ATLEAST(MSVC, 19, 0, 0) || PHI_COMPILER_IS(APPLECLANG) ||              \
            PHI_COMPILER_IS(EMCC)
#        define PHI_HAS_FEATURE_BINARY_LITERALS() 1
#    else
#        define PHI_HAS_FEATURE_BINARY_LITERALS() 0
#    endif

// decltype auto
// https://en.cppreference.com/w/cpp/language/auto
// https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2013/n3638.html
#    if PHI_COMPILER_IS_ATLEAST(GCC, 4, 9, 0) || PHI_COMPILER_IS_ATLEAST(CLANG, 3, 4, 0) ||        \
            PHI_COMPILER_IS_ATLEAST(MSVC, 19, 0, 0) || PHI_COMPILER_IS(APPLECLANG) ||              \
            PHI_COMPILER_IS(EMCC)
#        define PHI_HAS_FEATURE_DECLTYPE_AUTO() 1
#    else
#        define PHI_HAS_FEATURE_DECLTYPE_AUTO() 0
#    endif

// variable template
// https://en.cppreference.com/w/cpp/language/variable_template
// https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2013/n3651.pdf
#    if PHI_COMPILER_IS_ATLEAST(GCC, 5, 0, 0) || PHI_COMPILER_IS_ATLEAST(CLANG, 3, 4, 0) ||        \
            PHI_COMPILER_IS_ATLEAST(MSVC, 19, 0, 0) || PHI_COMPILER_IS(APPLECLANG) ||              \
            PHI_COMPILER_IS(EMCC)
#        define PHI_HAS_FEATURE_VARIABLE_TEMPLATE() 1
#    else
#        define PHI_HAS_FEATURE_VARIABLE_TEMPLATE() 0
#    endif

// attribute deprecated
// https://en.cppreference.com/w/cpp/language/attributes/deprecated
// https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2013/n3760.html
#    if PHI_COMPILER_IS_ATLEAST(GCC, 4, 9, 0) || PHI_COMPILER_IS_ATLEAST(CLANG, 3, 4, 0) ||        \
            PHI_COMPILER_IS_ATLEAST(MSVC, 19, 0, 0) || PHI_COMPILER_IS(APPLECLANG) ||              \
            PHI_COMPILER_IS(EMCC)
#        define PHI_HAS_FEATURE_ATTRIBUTE_DEPRECATED() 1
#    else
#        define PHI_HAS_FEATURE_ATTRIBUTE_DEPRECATED() 0
#    endif

// extended constexpr
// https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2013/n3652.html
#    if PHI_COMPILER_IS_ATLEAST(GCC, 5, 0, 0) || PHI_COMPILER_IS_ATLEAST(CLANG, 3, 4, 0) ||        \
            PHI_COMPILER_IS_ATLEAST(MSVC, 19, 10, 0) || PHI_COMPILER_IS(APPLECLANG) ||             \
            PHI_COMPILER_IS(EMCC)
#        define PHI_HAS_FEATURE_EXTENDED_CONSTEXPR() 1
#    else
#        define PHI_HAS_FEATURE_EXTENDED_CONSTEXPR() 0
#    endif

#else
#    define PHI_HAS_FEATURE_BINARY_LITERALS()      0
#    define PHI_HAS_FEATURE_DECLTYPE_AUTO()        0
#    define PHI_HAS_FEATURE_VARIABLE_TEMPLATE()    0
#    define PHI_HAS_FEATURE_ATTRIBUTE_DEPRECATED() 0
#    define PHI_HAS_FEATURE_EXTENDED_CONSTEXPR()   0
#endif

// C++-17 features
// https://en.cppreference.com/w/cpp/17
// https://en.cppreference.com/w/cpp/compiler_support/17
#if PHI_CPP_STANDARD_IS_ATLEAST(17)

// inline variables
// https://en.cppreference.com/w/cpp/language/inline
// https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0386r2.pdf
#    if PHI_COMPILER_IS_ATLEAST(GCC, 7, 0, 0) || PHI_COMPILER_IS_ATLEAST(CLANG, 3, 9, 0) ||        \
            PHI_COMPILER_IS_ATLEAST(MSVC, 19, 12, 0) || PHI_COMPILER_IS(APPLECLANG)
#        define PHI_HAS_FEATURE_INLINE_VARIABLES() 1
#    else
#        define PHI_HAS_FEATURE_INLINE_VARIABLES() 0
#    endif

// noexcept function type
// https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2015/p0012r1.html
#    if PHI_COMPILER_IS_ATLEAST(GCC, 7, 0, 0) || PHI_COMPILER_IS_ATLEAST(CLANG, 4, 0, 0) ||        \
            PHI_COMPILER_IS_ATLEAST(MSVC, 19, 12, 0) || PHI_COMPILER_IS(APPLECLANG) ||             \
            PHI_COMPILER_IS(EMCC)
#        define PHI_HAS_FEATURE_NOEXCEPT_FUNCTION_TYPE() 1
#    else
#        define PHI_HAS_FEATURE_NOEXCEPT_FUNCTION_TYPE() 0
#    endif

// attribute nodiscard
// https://en.cppreference.com/w/cpp/language/attributes/nodiscard
// https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0189r1.pdf
#    if PHI_COMPILER_IS_ATLEAST(GCC, 7, 0, 0) || PHI_COMPILER_IS_ATLEAST(CLANG, 3, 9, 0) ||        \
            PHI_COMPILER_IS_ATLEAST(MSVC, 19, 11, 0) || PHI_COMPILER_IS(APPLECLANG) ||             \
            PHI_COMPILER_IS(EMCC)
#        define PHI_HAS_FEATURE_ATTRIBUTE_NODISCARD() 1
#    else
#        define PHI_HAS_FEATURE_ATTRIBUTE_NODISCARD() 0
#    endif

// deduction guides
// https://en.cppreference.com/w/cpp/language/class_template_argument_deduction
// https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0091r3.html
#    if PHI_COMPILER_IS_ATLEAST(GCC, 7, 0, 0) || PHI_COMPILER_IS_ATLEAST(CLANG, 5, 0, 0) ||        \
            PHI_COMPILER_IS_ATLEAST(MSVC, 19, 14, 0) || PHI_COMPILER_IS(APPLECLANG) ||             \
            PHI_COMPILER_IS(EMCC)
#        define PHI_HAS_FEATURE_DEDUCTION_GUIDES() 1
#    else
#        define PHI_HAS_FEATURE_DEDUCTION_GUIDES() 0
#    endif

// constexpr lambda
// https://en.cppreference.com/w/cpp/language/lambda
// https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0170r1.pdf
#    if PHI_COMPILER_IS_ATLEAST(GCC, 7, 0, 0) || PHI_COMPILER_IS_ATLEAST(CLANG, 5, 0, 0) ||        \
            PHI_COMPILER_IS_ATLEAST(MSVC, 19, 11, 0) || PHI_COMPILER_IS(APPLECLANG) ||             \
            PHI_COMPILER_IS(EMCC)
#        define PHI_HAS_FEATURE_CONSTEXPR_LAMBDA() 1
#    else
#        define PHI_HAS_FEATURE_CONSTEXPR_LAMBDA() 0
#    endif

// attribute maybe_unused
// https://en.cppreference.com/w/cpp/language/attributes/maybe_unused
// https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0212r1.pdf
#    if PHI_COMPILER_IS_ATLEAST(GCC, 7, 0, 0) || PHI_COMPILER_IS_ATLEAST(CLANG, 3, 9, 0) ||        \
            PHI_COMPILER_IS_ATLEAST(MSVC, 19, 11, 0) || PHI_COMPILER_IS(APPLECLANG) ||             \
            PHI_COMPILER_IS(EMCC)
#        define PHI_HAS_FEATURE_ATTRIBUTE_MAYBE_UNUSED() 1
#    else
#        define PHI_HAS_FEATURE_ATTRIBUTE_MAYBE_UNUSED() 0
#    endif

// if constexpr
// https://en.cppreference.com/w/cpp/language/if
// https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0292r2.html
#    if PHI_COMPILER_IS_ATLEAST(GCC, 7, 0, 0) || PHI_COMPILER_IS_ATLEAST(CLANG, 3, 9, 0) ||        \
            PHI_COMPILER_IS_ATLEAST(MSVC, 19, 11, 0) || PHI_COMPILER_IS(APPLECLANG) ||             \
            PHI_COMPILER_IS(EMCC)
#        define PHI_HAS_FEATURE_IF_CONSTEXPR() 1
#    else
#        define PHI_HAS_FEATURE_IF_CONSTEXPR() 0
#    endif

// attribute fallthrough
// https://en.cppreference.com/w/cpp/language/attributes/fallthrough
// https://wg21.link/P0188R1
#    if PHI_COMPILER_IS_ATLEAST(GCC, 7, 0, 0) || PHI_COMPILER_IS_ATLEAST(CLANG, 3, 9, 0) ||        \
            PHI_COMPILER_IS_ATLEAST(MSVC, 19, 10, 0) || PHI_COMPILER_IS(APPLECLANG) ||             \
            PHI_COMPILER_IS(EMCC)
#        define PHI_HAS_FEATURE_ATTRIBUTE_FALLTHROUGH() 1
#    else
#        define PHI_HAS_FEATURE_ATTRIBUTE_FALLTHROUGH() 0
#    endif

// Class template argument deduction
// https://en.cppreference.com/w/cpp/language/class_template_argument_deduction
// https://wg21.link/P0091R3
#    if PHI_COMPILER_IS_ATLEAST(GCC, 7, 0, 0) || PHI_COMPILER_IS_ATLEAST(CLANG, 5, 0, 0) ||        \
            PHI_COMPILER_IS_ATLEAST(MSVC, 19, 14, 0) || PHI_COMPILER_IS(APPLECLANG) ||             \
            PHI_COMPILER_IS(EMCC)
#        define PHI_HAS_FEATURE_CLASS_TEMPLATE_ARGUMENT_DEDUCTION() 1
#    else
#        define PHI_HAS_FEATURE_CLASS_TEMPLATE_ARGUMENT_DEDUCTION() 0
#    endif

// Guaranteed copy elision
// https://en.cppreference.com/w/cpp/language/copy_elision
// https://wg21.link/P0135R1
#    if PHI_COMPILER_IS_ATLEAST(GCC, 7, 0, 0) || PHI_COMPILER_IS_ATLEAST(CLANG, 4, 0, 0) ||        \
            PHI_COMPILER_IS_ATLEAST(MSVC, 19, 13, 0) || PHI_COMPILER_IS(APPLECLANG) ||             \
            PHI_COMPILER_IS(EMCC)
#        define PHI_HAS_FEATURE_GUARANTEED_COPY_ELISION() 1
#    else
#        define PHI_HAS_FEATURE_GUARANTEED_COPY_ELISION() 0
#    endif

#else
#    define PHI_HAS_FEATURE_INLINE_VARIABLES()                  0
#    define PHI_HAS_FEATURE_NOEXCEPT_FUNCTION_TYPE()            0
#    define PHI_HAS_FEATURE_ATTRIBUTE_NODISCARD()               0
#    define PHI_HAS_FEATURE_DEDUCTION_GUIDES()                  0
#    define PHI_HAS_FEATURE_CONSTEXPR_LAMBDA()                  0
#    define PHI_HAS_FEATURE_ATTRIBUTE_MAYBE_UNUSED()            0
#    define PHI_HAS_FEATURE_IF_CONSTEXPR()                      0
#    define PHI_HAS_FEATURE_ATTRIBUTE_FALLTHROUGH()             0
#    define PHI_HAS_FEATURE_CLASS_TEMPLATE_ARGUMENT_DEDUCTION() 0
#    define PHI_HAS_FEATURE_GUARANTEED_COPY_ELISION()           0
#endif

// C++-20 features
// https://en.cppreference.com/w/cpp/20
// https://en.cppreference.com/w/cpp/compiler_support/20
#if PHI_CPP_STANDARD_IS_ATLEAST(20)

// char8_t
// https://en.cppreference.com/w/cpp/language/types#char8_t
// https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2018/p0482r6.html
#    if PHI_COMPILER_IS_ATLEAST(GCC, 9, 0, 0) || PHI_COMPILER_IS_ATLEAST(CLANG, 7, 0, 0) ||        \
            PHI_COMPILER_IS_ATLEAST(MSVC, 19, 22, 0) ||                                            \
            PHI_COMPILER_IS_ATLEAST(APPLECLANG, 10, 0, 0) || PHI_COMPILER_IS(EMCC)
#        define PHI_HAS_FEATURE_CHAR8_T() 1
#    else
#        define PHI_HAS_FEATURE_CHAR8_T() 0
#    endif

// constexpr destructor
// https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2019/p0784r7.html
#    if PHI_COMPILER_IS_ATLEAST(GCC, 10, 0, 0) || PHI_COMPILER_IS_ATLEAST(CLANG, 10, 0, 0) ||      \
            PHI_COMPILER_IS_ATLEAST(MSVC, 19, 28, 0) ||                                            \
            PHI_COMPILER_IS_ATLEAST(APPLECLANG, 12, 0, 0) || PHI_COMPILER_IS(EMCC)
#        define PHI_HAS_FEATURE_CONSTEXPR_DESTRUCTOR() 1
#    else
#        define PHI_HAS_FEATURE_CONSTEXPR_DESTRUCTOR() 0
#    endif

// constexpr virtual
// https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2018/p1064r0.html
#    if PHI_COMPILER_IS_ATLEAST(GCC, 9, 0, 0) || PHI_COMPILER_IS_ATLEAST(CLANG, 9, 0, 0) ||        \
            PHI_COMPILER_IS_ATLEAST(MSVC, 19, 27, 0) ||                                            \
            PHI_COMPILER_IS_ATLEAST(APPLECLANG, 11, 0, 3) || PHI_COMPILER_IS(EMCC)
#        define PHI_HAS_FEATURE_CONSTEXPR_VIRTUAL() 1
#    else
#        define PHI_HAS_FEATURE_CONSTEXPR_VIRTUAL() 0
#    endif

// attribute likely/unlikely
// https://en.cppreference.com/w/cpp/language/attributes/likely
// https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2018/p0479r5.html
#    if PHI_COMPILER_IS_ATLEAST(GCC, 9, 0, 0) || PHI_COMPILER_IS_ATLEAST(CLANG, 12, 0, 0) ||       \
            PHI_COMPILER_IS_ATLEAST(MSVC, 19, 26, 0) ||                                            \
            PHI_COMPILER_IS_ATLEAST(APPLECLANG, 13, 0, 0) || PHI_COMPILER_IS(EMCC)
#        define PHI_HAS_FEATURE_ATTRIBUTE_LIKELY() 1
#    else
#        define PHI_HAS_FEATURE_ATTRIBUTE_LIKELY() 0
#    endif

// Three-way comparison
// https://en.cppreference.com/w/cpp/language/operator_comparison#Three-way_comparison
// https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2017/p0515r3.pdf
#    if PHI_COMPILER_IS_ATLEAST(GCC, 10, 0, 0) || PHI_COMPILER_IS_ATLEAST(CLANG, 10, 0, 0) ||      \
            PHI_COMPILER_IS_ATLEAST(MSVC, 19, 20, 0) ||                                            \
            PHI_COMPILER_IS_ATLEAST(APPLECLANG, 12, 0, 0) || PHI_COMPILER_IS(EMCC)
#        define PHI_HAS_FEATURE_THREE_WAY_COMPARISON() 1
#    else
#        define PHI_HAS_FEATURE_THREE_WAY_COMPARISON() 0
#    endif

// consteval
// https://en.cppreference.com/w/cpp/language/consteval
// https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2018/p1073r3.html
#    if PHI_COMPILER_IS_ATLEAST(GCC, 11, 0, 0) || PHI_COMPILER_IS_ATLEAST(CLANG, 14, 0, 0) ||      \
            PHI_COMPILER_IS_ATLEAST(MSVC, 19, 29, 0) ||                                            \
            PHI_COMPILER_IS_ATLEAST(APPLECLANG, 11, 0, 3) || PHI_COMPILER_IS(EMCC)
#        define PHI_HAS_FEATURE_CONSTEVAL() 1
#    else
#        define PHI_HAS_FEATURE_CONSTEVAL() 0
#    endif

// constinit
// https://en.cppreference.com/w/cpp/language/constinit
// https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2019/p1143r2.html
#    if PHI_COMPILER_IS_ATLEAST(GCC, 10, 0, 0) || PHI_COMPILER_IS_ATLEAST(CLANG, 10, 0, 0) ||      \
            PHI_COMPILER_IS_ATLEAST(MSVC, 19, 29, 0) ||                                            \
            PHI_COMPILER_IS_ATLEAST(APPLECLANG, 12, 0, 0) || PHI_COMPILER_IS(EMCC)
#        define PHI_HAS_FEATURE_CONSTINIT() 1
#    else
#        define PHI_HAS_FEATURE_CONSTINIT() 0
#    endif

#else
#    define PHI_HAS_FEATURE_CHAR8_T()              0
#    define PHI_HAS_FEATURE_CONSTEXPR_DESTRUCTOR() 0
#    define PHI_HAS_FEATURE_CONSTEXPR_VIRTUAL()    0
#    define PHI_HAS_FEATURE_ATTRIBUTE_LIKELY()     0
#    define PHI_HAS_FEATURE_THREE_WAY_COMPARISON() 0
#    define PHI_HAS_FEATURE_CONSTEVAL()            0
#    define PHI_HAS_FEATURE_CONSTINIT()            0
#endif

// C++-23 features
// https://en.cppreference.com/w/cpp/23
// https://en.cppreference.com/w/cpp/compiler_support/23
#if PHI_CPP_STANDARD_IS_ATLEAST(23)

// if consteval
// https://en.cppreference.com/w/cpp/language/if#Consteval_if
// https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2021/p1938r3.html
#    if PHI_COMPILER_IS_ATLEAST(GCC, 12, 0, 0) ||                                                  \
            PHI_COMPILER_IS_ATLEAST(CLANG, 14, 0,                                                  \
                                    0) || /*PHI_COMPILER_IS_ATLEAST(MSVC, X, X, X) || */           \
            PHI_COMPILER_IS_ATLEAST(APPLECLANG, 14, 0, 0) ||                                       \
            PHI_COMPILER_IS(EMCC)
#        define PHI_HAS_FEATURE_IF_CONSTEVAL() 1
#    else
#        define PHI_HAS_FEATURE_IF_CONSTEVAL() 0
#    endif

#else
#    define PHI_HAS_FEATURE_IF_CONSTEVAL() 0
#endif

#endif // INCG_PHI_COMPILER_SUPPORT_FEATURES_HPP
