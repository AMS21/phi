#include <phi/test/test_macros.hpp>

#include <phi/compiler_support/libraries.hpp>
#include <phi/forward/std/string_view.hpp>

TEST_CASE("forward.std.string_view.forward")
{
    std::basic_string_view<char, std::char_traits<char>>* pointer  = nullptr;
    std::string_view*                                     pointer2 = nullptr;
    std::wstring_view*                                    pointer3 = nullptr;
    std::u8string_view*                                   pointer4 = nullptr;
    std::u16string_view*                                  pointer5 = nullptr;
    std::u32string_view*                                  pointer6 = nullptr;

    CHECK(pointer == nullptr);
    CHECK(pointer2 == nullptr);
    CHECK(pointer3 == nullptr);
    CHECK(pointer4 == nullptr);
    CHECK(pointer5 == nullptr);
    CHECK(pointer6 == nullptr);
}

#if PHI_SUPPORTS_STDLIB_STRING_VIEW()

#    include <string_view>

TEST_CASE("forward.std.string_view")
{
    std::basic_string_view<char, std::char_traits<char>> view;
    std::string_view                                     view2;
    std::wstring_view                                    view3;
    std::u8string_view                                   view4;
    std::u16string_view                                  view5;
    std::u32string_view                                  view6;

    (void)view;
    (void)view2;
    (void)view3;
    (void)view4;
    (void)view5;
    (void)view6;
}

#endif
