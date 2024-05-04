#include <phi/test/test_macros.hpp>

#include "constexpr_helper.hpp"
#include <phi/algorithm/string_equals.hpp>
#include <phi/algorithm/string_length.hpp>
#include <phi/compiler_support/compiler.hpp>
#include <phi/compiler_support/constexpr.hpp>
#include <phi/compiler_support/libraries.hpp>
#include <phi/compiler_support/warning.hpp>
#include <phi/container/array.hpp>
#include <phi/container/string_view.hpp>
#include <phi/core/boolean.hpp>
#include <phi/core/integer.hpp>
#include <phi/core/move.hpp>
#include <phi/core/size_t.hpp>
#include <phi/core/types.hpp>
#include <phi/iterator/reverse_iterator.hpp>
#include <phi/type_traits/is_trivially_copyable.hpp>
#include <string>

#if PHI_SUPPORTS_STDLIB_STRING_VIEW()
#    include <string_view>
#endif

PHI_GCC_SUPPRESS_WARNING_PUSH()
PHI_GCC_SUPPRESS_WARNING("-Wuseless-cast")

// NOLINTNEXTLINE(readability-function-size)
TEST_CASE("BasicStringView", "[Container][StringView]")
{
    SECTION("default constructor")
    {
        PHI_EXTENDED_CONSTEXPR phi::string_view view;

        EXT_STATIC_REQUIRE(view.data() == nullptr);
        EXT_STATIC_REQUIRE(view.length() == 0u);
        EXT_STATIC_REQUIRE(view.is_empty());
        EXT_STATIC_REQUIRE(view.is_null());
        EXT_STATIC_REQUIRE(view.begin() == nullptr);
        EXT_STATIC_REQUIRE(view.end() == nullptr);
    }

    SECTION("basic_string_view(CharT[])")
    {
        PHI_CONSTEXPR phi::string_view view{"Hello World"};

        EXT_STATIC_REQUIRE(phi::string_equals(view.data(), "Hello World"));
        STATIC_REQUIRE(view.length() == 11u);
        STATIC_REQUIRE_FALSE(view.is_null());
        STATIC_REQUIRE_FALSE(view.is_empty());

        EXT_STATIC_REQUIRE(view.front() == 'H');
        EXT_STATIC_REQUIRE(view.back() == 'd');
    }

    SECTION("basic_string_view(phi::array)")
    {
        static PHI_CONSTEXPR phi::array<char, 2> array{{'H', 'i'}};
        PHI_CONSTEXPR phi::string_view view{array};

        STATIC_REQUIRE_SAN(phi::string_equals(view.data(), "Hi", 2u));
        STATIC_REQUIRE(view.length() == 2u);
        STATIC_REQUIRE_SAN(!view.is_null());
        STATIC_REQUIRE_SAN(!view.is_empty());

        STATIC_REQUIRE_SAN(view.front() == 'H');
        STATIC_REQUIRE_SAN(view.back() == 'i');
    }

    SECTION("BasicStringView(CharT*)")
    {
        PHI_CONSTEXPR static const char* data{"Hello World"};
        PHI_EXTENDED_CONSTEXPR phi::string_view view(data);

        EXT_STATIC_REQUIRE(phi::string_equals(view.data(), "Hello World"));
        EXT_STATIC_REQUIRE(view.length() == 11u);
        EXT_STATIC_REQUIRE_FALSE(view.is_empty());
        EXT_STATIC_REQUIRE_FALSE(view.is_null());
        // TODO: For some reason MSVC fails this tests at runtime
#if PHI_COMPILER_IS(MSVC)
        SKIP_CHECK();
#else
        EXT_STATIC_REQUIRE(view.begin() == data);
#endif
        EXT_STATIC_REQUIRE(view.end() == data + 11u);
        EXT_STATIC_REQUIRE(view.front() == 'H');
        EXT_STATIC_REQUIRE(view.back() == 'd');
    }

    SECTION("BasicStringView(CharT*, length_type)")
    {
        PHI_CONSTEXPR static const char* data{"Hello World"};
        PHI_EXTENDED_CONSTEXPR phi::string_view view(data, 11u);

        EXT_STATIC_REQUIRE(phi::string_equals(view.data(), "Hello World"));
        EXT_STATIC_REQUIRE(view.length() == 11u);
        EXT_STATIC_REQUIRE_FALSE(view.is_empty());
        EXT_STATIC_REQUIRE_FALSE(view.is_null());
        EXT_STATIC_REQUIRE(view.begin() == data);
        EXT_STATIC_REQUIRE(view.end() == data + 11u);
        EXT_STATIC_REQUIRE(view.front() == 'H');
        EXT_STATIC_REQUIRE(view.back() == 'd');

        PHI_EXTENDED_CONSTEXPR phi::string_view view2(data, 5u);
        EXT_STATIC_REQUIRE(view2.length() == 5u);
        EXT_STATIC_REQUIRE_FALSE(view2.is_empty());
        EXT_STATIC_REQUIRE_FALSE(view2.is_null());
        EXT_STATIC_REQUIRE(view2.begin() == data);
        EXT_STATIC_REQUIRE(view2.end() == data + 5u);
        EXT_STATIC_REQUIRE(view2.front() == 'H');
        EXT_STATIC_REQUIRE(view2.back() == 'o');
    }

    SECTION("copy constructor")
    {
        PHI_EXTENDED_CONSTEXPR phi::string_view base_view;
        PHI_EXTENDED_CONSTEXPR phi::string_view copy_view(base_view);

        EXT_STATIC_REQUIRE(copy_view.data() == nullptr);
        EXT_STATIC_REQUIRE(copy_view.data() == base_view.data());
        EXT_STATIC_REQUIRE(copy_view.length() == 0u);
        EXT_STATIC_REQUIRE(copy_view.length() == base_view.length());
        EXT_STATIC_REQUIRE(copy_view.is_empty());
        EXT_STATIC_REQUIRE(copy_view.is_null());
        EXT_STATIC_REQUIRE(copy_view.begin() == nullptr);
        EXT_STATIC_REQUIRE(copy_view.begin() == base_view.begin());
        EXT_STATIC_REQUIRE(copy_view.end() == nullptr);
        EXT_STATIC_REQUIRE(copy_view.end() == base_view.end());

        PHI_EXTENDED_CONSTEXPR phi::string_view base_view2("Hello World");
        PHI_EXTENDED_CONSTEXPR phi::string_view copy_view2(base_view2);

        EXT_STATIC_REQUIRE(phi::string_equals(copy_view2.data(), "Hello World"));
        // TODO: For some reason MSVC fails this tests at runtime
#if PHI_COMPILER_IS(MSVC)
        SKIP_CHECK();
#else
        EXT_STATIC_REQUIRE(copy_view2.data() == base_view2.data());
#endif
        EXT_STATIC_REQUIRE(copy_view2.length() == 11u);
        EXT_STATIC_REQUIRE(copy_view2.length() == base_view2.length());
        EXT_STATIC_REQUIRE_FALSE(copy_view2.is_empty());
        EXT_STATIC_REQUIRE_FALSE(copy_view2.is_null());
        EXT_STATIC_REQUIRE(copy_view2.begin() == base_view2.begin());
        EXT_STATIC_REQUIRE(copy_view2.end() == base_view2.end());
    }

    SECTION("move constructor")
    {
        PHI_EXTENDED_CONSTEXPR phi::string_view base_view;
        PHI_EXTENDED_CONSTEXPR phi::string_view move_view(phi::move(base_view));

        EXT_STATIC_REQUIRE(move_view.data() == nullptr);
        EXT_STATIC_REQUIRE(move_view.length() == 0u);
        EXT_STATIC_REQUIRE(move_view.is_empty());
        EXT_STATIC_REQUIRE(move_view.is_null());
        EXT_STATIC_REQUIRE(move_view.begin() == nullptr);
        EXT_STATIC_REQUIRE(move_view.end() == nullptr);

        PHI_EXTENDED_CONSTEXPR phi::string_view base_view2("Hello World");
        PHI_EXTENDED_CONSTEXPR phi::string_view move_view2(phi::move(base_view2));

        EXT_STATIC_REQUIRE(phi::string_equals(move_view2.data(), "Hello World"));
        EXT_STATIC_REQUIRE(move_view2.length() == 11u);
        EXT_STATIC_REQUIRE_FALSE(move_view2.is_empty());
        EXT_STATIC_REQUIRE_FALSE(move_view2.is_null());
        EXT_STATIC_REQUIRE_FALSE(move_view2.begin() == nullptr);
#if PHI_COMPILER_WORKAROUND(GCC, 7, 0, 0)
        EXT_STATIC_REQUIRE_FALSE(move_view2.end() == nullptr);
#else
        SKIP_CHECK();
#endif
    }

#if PHI_SUPPORTS_STDLIB_STRING_VIEW()
    SECTION("basic_string_view(const std::string_view&)")
    {
        std::string_view std_view{"Hello World"};
        phi::string_view view{std_view};

        CHECK(phi::string_equals(view.data(), "Hello World"));
        CHECK(view.length() == 11u);

        CHECK(view.data() == std_view.data());
        CHECK(view.length() == std_view.length());
        CHECK_FALSE(view.is_empty());
        CHECK_FALSE(view.is_null());
    }

    SECTION("basic_string_view(std::string_view&&)")
    {
        std::string_view std_view{"Hello World"};
        phi::string_view view{phi::move(std_view)};

        CHECK(phi::string_equals(view.data(), "Hello World"));
        CHECK(view.length() == 11u);

        CHECK_FALSE(view.is_empty());
        CHECK_FALSE(view.is_null());
    }
#endif

    SECTION("operator=(const BasicStringView&)")
    {
        phi::string_view base_view;
        phi::string_view copy_view;

        copy_view = base_view;

        CHECK(copy_view.data() == nullptr);
        CHECK(copy_view.data() == base_view.data());
        CHECK(copy_view.length() == 0u);
        CHECK(copy_view.length() == base_view.length());
        CHECK(copy_view.is_empty());
        CHECK(copy_view.is_null());
        CHECK(copy_view.begin() == nullptr);
        CHECK(copy_view.begin() == base_view.begin());
        CHECK(copy_view.end() == nullptr);
        CHECK(copy_view.end() == base_view.end());

        phi::string_view base_view2("Hello World");
        phi::string_view copy_view2;

        copy_view2 = base_view2;

        CHECK(phi::string_equals(copy_view2.data(), "Hello World"));
        CHECK(phi::string_equals(copy_view2.data(), base_view2.data()));
        CHECK(base_view2 == copy_view2);
        CHECK(copy_view2.data() == base_view2.data());
        CHECK(copy_view2.length() == 11u);
        CHECK(copy_view2.length() == base_view2.length());
        CHECK_FALSE(copy_view2.is_empty());
        CHECK_FALSE(copy_view2.is_null());
        CHECK_FALSE(copy_view2.begin() == nullptr);
        CHECK(copy_view2.begin() == base_view2.begin());
        CHECK_FALSE(copy_view2.end() == nullptr);
        CHECK(copy_view2.end() == base_view2.end());
    }

    SECTION("operator=(BasicStringView&&)")
    {
        phi::string_view base_view;
        phi::string_view move_view;

        move_view = phi::move(base_view);

        CHECK(move_view.data() == nullptr);
        CHECK(move_view.length() == 0u);
        CHECK(move_view.is_empty());
        CHECK(move_view.is_empty());
        CHECK(move_view.begin() == nullptr);
        CHECK(move_view.end() == nullptr);

        phi::string_view base_view2("Hello World");
        phi::string_view move_view2;

        move_view2 = phi::move(base_view2);

        CHECK(phi::string_equals(move_view2.data(), "Hello World"));
        CHECK(move_view2.length() == 11u);
        CHECK_FALSE(move_view2.data() == nullptr);
        CHECK_FALSE(move_view2.is_empty());
        CHECK_FALSE(move_view2.is_null());
        CHECK_FALSE(move_view2.begin() == nullptr);
        CHECK_FALSE(move_view2.end() == nullptr);
    }

    SECTION("operator=(CharT[Size])")
    {
        phi::string_view view;

        CHECK(view.is_empty());
        CHECK(view.is_null());

        view = "Hello World";

        CHECK(phi::string_equals(view.data(), "Hello World"));
        CHECK(view.length() == 11u);
        CHECK_FALSE(view.is_null());
        CHECK_FALSE(view.is_empty());

        CHECK(view.front() == 'H');
        CHECK(view.back() == 'd');
    }

    SECTION("operator=(phi::array)")
    {
        static PHI_CONSTEXPR phi::array<char, 2> array{{'H', 'i'}};
        phi::string_view                         view;

        view = array;

        CHECK(phi::string_equals(view.data(), "Hi", 2u));
        REQUIRE(view.length() == 2u);
        CHECK_FALSE(view.is_null());
        CHECK_FALSE(view.is_empty());

        CHECK(view.front() == 'H');
        CHECK(view.back() == 'i');
    }

#if PHI_SUPPORTS_STDLIB_STRING_VIEW()
    SECTION("operator=(const std::strinb_view&)")
    {
        std::string_view std_view{"Hello World"};
        phi::string_view view;

        view = std_view;

        CHECK(phi::string_equals(view.data(), "Hello World"));
        CHECK(view.length() == 11u);

        CHECK(view.data() == std_view.data());
        CHECK(view.length() == std_view.length());
        CHECK_FALSE(view.is_empty());
        CHECK_FALSE(view.is_null());
    }

    SECTION("operator=(std::string_view&&)")
    {
        std::string_view std_view{"Hello World"};
        phi::string_view view;

        view = phi::move(std_view);

        CHECK(phi::string_equals(view.data(), "Hello World"));
        CHECK(view.length() == 11u);

        CHECK_FALSE(view.is_empty());
        CHECK_FALSE(view.is_null());
    }

    PHI_GCC_SUPPRESS_WARNING_PUSH()
    PHI_GCC_SUPPRESS_WARNING("-Wconversion")

    SECTION("implicit conversion to std::string_view")
    {
        phi::string_view view{"Hello World"};

        std::string_view std_view{view};

        CHECK(phi::string_equals(std_view.data(), "Hello World"));
        CHECK(std_view.length() == 11u);

        CHECK(view.data() == std_view.data());
        CHECK(view.length() == std_view.length());
    }

    PHI_GCC_SUPPRESS_WARNING_POP()
#endif

    SECTION("begin")
    {
        PHI_EXTENDED_CONSTEXPR static const char* str = "Test";
        PHI_EXTENDED_CONSTEXPR phi::string_view null_view;
        PHI_EXTENDED_CONSTEXPR phi::string_view test_view(str);

        EXT_STATIC_REQUIRE(null_view.begin() == nullptr);
#if PHI_COMPILER_IS(MSVC)
        SKIP_CHECK();
#else
        EXT_STATIC_REQUIRE(test_view.begin() == str);
#endif
        EXT_STATIC_REQUIRE_FALSE(test_view.begin() == nullptr);
    }

    SECTION("end")
    {
        PHI_EXTENDED_CONSTEXPR static const char* str = "Test";
        PHI_EXTENDED_CONSTEXPR phi::string_view null_view;
        PHI_EXTENDED_CONSTEXPR phi::string_view test_view(str);

        EXT_STATIC_REQUIRE(null_view.end() == nullptr);
#if PHI_COMPILER_IS(MSVC)
        SKIP_CHECK();
#else
        EXT_STATIC_REQUIRE(test_view.end() == (str + 4));
#endif
#if PHI_COMPILER_WORKAROUND(GCC, 7, 0, 0)
        EXT_STATIC_REQUIRE_FALSE(test_view.end() == nullptr);
#else
        SKIP_CHECK();
#endif
    }

    SECTION("cbegin")
    {
        PHI_EXTENDED_CONSTEXPR static const char* str = "Test";
        PHI_EXTENDED_CONSTEXPR phi::string_view null_view;
        PHI_EXTENDED_CONSTEXPR phi::string_view test_view(str);

        EXT_STATIC_REQUIRE(null_view.cbegin() == nullptr);
#if PHI_COMPILER_IS(MSVC)
        SKIP_CHECK();
#else
        EXT_STATIC_REQUIRE(test_view.cbegin() == str);
#endif
        EXT_STATIC_REQUIRE_FALSE(test_view.cbegin() == nullptr);
    }

    SECTION("cend")
    {
        PHI_EXTENDED_CONSTEXPR static const char* str = "Test";
        PHI_EXTENDED_CONSTEXPR phi::string_view null_view;
        PHI_EXTENDED_CONSTEXPR phi::string_view test_view(str);

        EXT_STATIC_REQUIRE(null_view.cend() == nullptr);
#if PHI_COMPILER_IS(MSVC)
        SKIP_CHECK();
#else
        EXT_STATIC_REQUIRE(test_view.cend() == (str + 4));
#endif
#if PHI_COMPILER_WORKAROUND(GCC, 7, 0, 0)
        EXT_STATIC_REQUIRE_FALSE(test_view.cend() == nullptr);
#else
        SKIP_CHECK();
#endif
    }

    SECTION("rbegin")
    {
        PHI_EXTENDED_CONSTEXPR static const char* str = "Test";
        PHI_EXTENDED_CONSTEXPR phi::string_view null_view;
        PHI_EXTENDED_CONSTEXPR phi::string_view test_view(str);

        EXT_STATIC_REQUIRE(null_view.rbegin() == phi::reverse_iterator<const char*>(nullptr));
#if PHI_COMPILER_IS(MSVC)
        SKIP_CHECK();
#else
        EXT_STATIC_REQUIRE(test_view.rbegin() == phi::reverse_iterator<const char*>(str + 4));
#endif
    }

    SECTION("rend")
    {
        PHI_EXTENDED_CONSTEXPR static const char* str = "Test";
        PHI_EXTENDED_CONSTEXPR phi::string_view null_view;
        PHI_EXTENDED_CONSTEXPR phi::string_view test_view(str);

        EXT_STATIC_REQUIRE(null_view.rend() == phi::reverse_iterator<const char*>(nullptr));
#if PHI_COMPILER_IS(MSVC)
        SKIP_CHECK();
#else
        EXT_STATIC_REQUIRE(test_view.rend() == phi::reverse_iterator<const char*>(str));
#endif
    }

    SECTION("crbegin")
    {
        PHI_EXTENDED_CONSTEXPR static const char* str = "Test";
        PHI_EXTENDED_CONSTEXPR phi::string_view null_view;
        PHI_EXTENDED_CONSTEXPR phi::string_view test_view(str);

        EXT_STATIC_REQUIRE(null_view.crbegin() == phi::reverse_iterator<const char*>(nullptr));
#if PHI_COMPILER_IS(MSVC)
        SKIP_CHECK();
#else
        EXT_STATIC_REQUIRE(test_view.crbegin() == phi::reverse_iterator<const char*>(str + 4));
#endif
    }

    SECTION("crend")
    {
        PHI_EXTENDED_CONSTEXPR static const char* str = "Test";
        PHI_EXTENDED_CONSTEXPR phi::string_view null_view;
        PHI_EXTENDED_CONSTEXPR phi::string_view test_view(str);

        EXT_STATIC_REQUIRE(null_view.crend() == phi::reverse_iterator<const char*>(nullptr));
#if PHI_COMPILER_IS(MSVC)
        SKIP_CHECK();
#else
        EXT_STATIC_REQUIRE(test_view.crend() == phi::reverse_iterator<const char*>(str));
#endif
    }

    SECTION("length")
    {
        PHI_EXTENDED_CONSTEXPR phi::string_view null_view;
        PHI_EXTENDED_CONSTEXPR phi::string_view test_view("Test");
        PHI_EXTENDED_CONSTEXPR phi::string_view short_view("Hello World", 5u);

        EXT_STATIC_REQUIRE(null_view.length() == 0u);
        EXT_STATIC_REQUIRE(test_view.length() == 4u);
        EXT_STATIC_REQUIRE(short_view.length() == 5u);
    }

    SECTION("max_length")
    {
        PHI_CONSTEXPR phi::string_view view;
        STATIC_REQUIRE(std::numeric_limits<phi::usize>::max() == view.max_length());
    }

    SECTION("is_empty")
    {
        PHI_EXTENDED_CONSTEXPR phi::string_view null_view;
        PHI_EXTENDED_CONSTEXPR phi::string_view test_view("Hello World");

        EXT_STATIC_REQUIRE(null_view.is_empty());
        EXT_STATIC_REQUIRE_FALSE(test_view.is_empty());
    }

    SECTION("is_null")
    {
        PHI_EXTENDED_CONSTEXPR phi::string_view null_view;
        PHI_EXTENDED_CONSTEXPR phi::string_view test_view("Hello World");

        EXT_STATIC_REQUIRE(null_view.is_null());
        EXT_STATIC_REQUIRE_FALSE(test_view.is_null());
    }

    SECTION("is_null_terminated")
    {
        PHI_CONSTEXPR phi::string_view null_view;
        PHI_CONSTEXPR phi::string_view test_view{"Hello World"};
        PHI_CONSTEXPR phi::string_view null_terminated_view{"Hello", 6u};

        STATIC_REQUIRE_FALSE(null_view.is_null_terminated());
        STATIC_REQUIRE_FALSE(test_view.is_null_terminated());
        STATIC_REQUIRE(null_terminated_view.is_null_terminated());
    }

    SECTION("operator[]/at()")
    {
        PHI_EXTENDED_CONSTEXPR phi::string_view test_view("Test");

        EXT_STATIC_REQUIRE(test_view[0u] == 'T');
        EXT_STATIC_REQUIRE(test_view[1u] == 'e');
        EXT_STATIC_REQUIRE(test_view[2u] == 's');
        EXT_STATIC_REQUIRE(test_view[3u] == 't');

        EXT_STATIC_REQUIRE(test_view.at(0u) == 'T');
        EXT_STATIC_REQUIRE(test_view.at(1u) == 'e');
        EXT_STATIC_REQUIRE(test_view.at(2u) == 's');
        EXT_STATIC_REQUIRE(test_view.at(3u) == 't');
    }

    SECTION("front")
    {
        PHI_EXTENDED_CONSTEXPR phi::string_view test_view("Test");
        PHI_EXTENDED_CONSTEXPR phi::string_view test_view2("Hello World");

        EXT_STATIC_REQUIRE(test_view.front() == 'T');
        EXT_STATIC_REQUIRE(test_view2.front() == 'H');
    }

    SECTION("back")
    {
        PHI_EXTENDED_CONSTEXPR phi::string_view test_view("Test");
        PHI_EXTENDED_CONSTEXPR phi::string_view test_view2("Hello World");

        EXT_STATIC_REQUIRE(test_view.back() == 't');
        EXT_STATIC_REQUIRE(test_view2.back() == 'd');
    }

    SECTION("data")
    {
        PHI_CONSTEXPR static const char* str = "Hello World";

        PHI_EXTENDED_CONSTEXPR phi::string_view null_view;
        PHI_EXTENDED_CONSTEXPR phi::string_view test_view(str);

        EXT_STATIC_REQUIRE(null_view.data() == nullptr);
        EXT_STATIC_REQUIRE(test_view.data() == str);
    }

    SECTION("clear")
    {
        phi::string_view view("Hello World");

        view.clear();

        CHECK(view.data() == nullptr);
        CHECK(view.is_empty());
        CHECK(view.is_null());
        CHECK(view.length() == 0u);
        CHECK(view.begin() == nullptr);
        CHECK(view.end() == nullptr);

        view.clear();

        CHECK(view.data() == nullptr);
        CHECK(view.is_empty());
        CHECK(view.is_null());
        CHECK(view.length() == 0u);
        CHECK(view.begin() == nullptr);
        CHECK(view.end() == nullptr);
    }

    SECTION("add_prefix")
    {
        PHI_CONSTEXPR static const char* str = "Hello World";
        phi::string_view                 view(str + 6u);

        CHECK(phi::string_equals(view.data(), "World"));
        CHECK(view.length() == 5u);
        CHECK(view.data() == str + 6u);
        CHECK(view.begin() == str + 6u);
        CHECK(view.end() == str + 11u);
        CHECK(view.front() == 'W');
        CHECK(view.back() == 'd');

        view.add_prefix(6u);

        CHECK(phi::string_equals(view.data(), "Hello World"));
        CHECK(view.length() == 11u);
        CHECK(view.data() == str);
        CHECK(view.begin() == str);
        CHECK(view.end() == str + 11u);
        CHECK(view.front() == 'H');
        CHECK(view.back() == 'd');
    }

    SECTION("add_postfix")
    {
        PHI_CONSTEXPR static const char* str = "Hello World";
        phi::string_view                 view(str, 5u);

        CHECK(view.length() == 5u);
        CHECK(view.data() == str);
        CHECK(view.begin() == str);
        CHECK(view.end() == str + 5u);
        CHECK(view.back() == 'o');
        CHECK(view.front() == 'H');

        view.add_postfix(6u);

        CHECK(phi::string_equals(view.data(), "Hello World"));
        CHECK(view.length() == 11u);
        CHECK(view.data() == str);
        CHECK(view.begin() == str);
        CHECK(view.end() == str + 11u);
        CHECK(view.front() == 'H');
        CHECK(view.back() == 'd');
    }

    SECTION("remove_prefix")
    {
        PHI_CONSTEXPR static const char* str = "Hello World";
        phi::string_view                 view(str);

        CHECK(phi::string_equals(view.data(), "Hello World"));
        CHECK(view.length() == 11u);

        view.remove_prefix(6u);

        CHECK(phi::string_equals(view.data(), "World"));
        CHECK(view.length() == 5u);
    }

    SECTION("remove_suffix")
    {
        PHI_CONSTEXPR static const char* str = "Hello World";
        phi::string_view                 view(str);

        CHECK(phi::string_equals(view.data(), "Hello World"));
        CHECK(view.length() == 11u);

        view.remove_suffix(6u);

        CHECK(view.back() == 'o');
        CHECK(view.length() == 5u);
    }

    SECTION("resize")
    {
        PHI_CONSTEXPR static const char* str = "Hello World";
        phi::string_view                 view(str, 5u);

        view.resize(11u);

        CHECK(view.back() == 'd');
        CHECK(view.length() == 11u);

        view.resize(5u);

        CHECK(view.back() == 'o');
        CHECK(view.length() == 5u);
    }

    SECTION("swap")
    {
        phi::string_view view1("Hello");
        phi::string_view view2("World");

        view1.swap(view2);

        CHECK(phi::string_equals(view1.data(), "World"));
        CHECK(phi::string_equals(view2.data(), "Hello"));
    }

    SECTION("copy")
    {
        char dest[6u] = "";

        phi::string_view view("Hello World");

        view.copy(dest, 5u);
        dest[5u] = '\0';

        CHECK(phi::string_equals(dest, "Hello"));
        CHECK(phi::string_length(dest) == 5u);

        view.copy(dest, 5u, 6u);
        dest[5u] = '\0';

        CHECK(phi::string_equals(dest, "World"));
        CHECK(phi::string_length(dest) == 5u);
    }

    SECTION("substring_view")
    {
        SECTION("with pos and size")
        {
            PHI_EXTENDED_CONSTEXPR phi::string_view base_view("Hello World");
            PHI_EXTENDED_CONSTEXPR phi::string_view sub_view = base_view.substring_view(
                    6u); // TODO: This line generates a linker error with GCC when npos is defined to be size_type instead of size_t

#if PHI_COMPILER_WORKAROUND(GCC, 7, 0, 0)
            EXT_STATIC_REQUIRE(phi::string_equals(sub_view.data(), "World"));
#else
            SKIP_CHECK();
#endif
            EXT_STATIC_REQUIRE(sub_view.length() == 5u);

            PHI_EXTENDED_CONSTEXPR phi::string_view sub_view2 = base_view.substring_view(0u, 5u);

            EXT_STATIC_REQUIRE(sub_view2.back() == 'o');
            EXT_STATIC_REQUIRE(sub_view2.length() == 5u);
        }

        SECTION("with 2 iterators")
        {
            CONSTEXPR_SAN phi::string_view base_view{"Hello World"};
            CONSTEXPR_SAN phi::string_view sub_view =
                    base_view.substring_view(base_view.begin(), base_view.begin() + 5u);

            STATIC_REQUIRE_SAN(phi::string_equals(sub_view.data(), "Hello", 5u));
            STATIC_REQUIRE_SAN(sub_view.length() == 5u);
            STATIC_REQUIRE_SAN(sub_view.data() == base_view.data());
            STATIC_REQUIRE_SAN(sub_view.begin() == base_view.begin());
            STATIC_REQUIRE_SAN(sub_view.front() == 'H');
            STATIC_REQUIRE_SAN(sub_view.back() == 'o');

            CONSTEXPR_SAN phi::string_view sub_view2 =
                    base_view.substring_view(base_view.begin() + 6u, base_view.end());

            STATIC_REQUIRE_SAN(phi::string_equals(sub_view2.data(), "World"));
            STATIC_REQUIRE_SAN(sub_view2.length() == 5u);
            STATIC_REQUIRE_SAN(sub_view2.end() == base_view.end());
            STATIC_REQUIRE_SAN(sub_view2.front() == 'W');
            STATIC_REQUIRE_SAN(sub_view2.back() == 'd');
        }
    }

    SECTION("explicit specilizations")
    {
        CHECK_SAME_TYPE(phi::string_view, phi::basic_string_view<char>);
        CHECK_SAME_TYPE(phi::wstring_view, phi::basic_string_view<wchar_t>);
        CHECK_SAME_TYPE(phi::u8string_view, phi::basic_string_view<char8_t>);
        CHECK_SAME_TYPE(phi::u16string_view, phi::basic_string_view<char16_t>);
        CHECK_SAME_TYPE(phi::u32string_view, phi::basic_string_view<char32_t>);

#if PHI_HAS_WORKING_IS_TRIVIALLY_COPYABLE()
        STATIC_REQUIRE(phi::is_trivially_copyable<phi::string_view>::value);
        STATIC_REQUIRE(phi::is_trivially_copyable<phi::wstring_view>::value);
        STATIC_REQUIRE(phi::is_trivially_copyable<phi::u8string_view>::value);
        STATIC_REQUIRE(phi::is_trivially_copyable<phi::u16string_view>::value);
        STATIC_REQUIRE(phi::is_trivially_copyable<phi::u32string_view>::value);
#endif
    }
}

TEST_CASE("string_view - bytes_length")
{
    PHI_CONSTEXPR static phi::string_view str = "Hello World";
    STATIC_REQUIRE(str.length() == 11u);
    STATIC_REQUIRE(str.bytes_length() == 11u);

    PHI_CONSTEXPR static phi::wstring_view wstr = L"Hello World";
    STATIC_REQUIRE(wstr.length() == 11u);
    STATIC_REQUIRE(wstr.bytes_length() == 11u * sizeof(wchar_t));

    PHI_CONSTEXPR static phi::u16string_view u16str = u"Hello World";
    STATIC_REQUIRE(u16str.length() == 11u);
    STATIC_REQUIRE(u16str.bytes_length() == 22u);

    PHI_CONSTEXPR static phi::u32string_view u32str = U"Hello World";
    STATIC_REQUIRE(u32str.length() == 11u);
    STATIC_REQUIRE(u32str.bytes_length() == 44u);
}

PHI_GCC_SUPPRESS_WARNING_POP()
