//
// Created by felix on 07.08.23.
//

#include <ranges>
#include "gtest/gtest.h"
#include "../src/click.hpp"

using ClickArg = click::Argument;
using ClickOpt = click::Option;

TEST(click, add_click_arguments_only)
{
    auto click_obj = click::Click("Test");
    click_obj.arguments.emplace_back(
            std::make_unique<ClickArg>(
                    ClickArg("bar", [](const std::string &val) -> std::string {return val;})
                    )
            );
    
    
    ASSERT_EQ(click_obj.arguments.size(), 1);
    ASSERT_EQ(click_obj.options.size(), 1);
}

TEST(click, add_click_options_only)
{
    auto click_obj = click::Click("Test");
    click_obj.options.emplace_back(
            std::make_unique<ClickOpt>(
                    ClickOpt("bar", [](const std::string &val) -> std::string {return val;})
            )
    );
    
    ASSERT_EQ(click_obj.arguments.size(), 0);
    ASSERT_EQ(click_obj.options.size(), 2);
}

TEST(click, default_help_text)
{
    // display_help_text calls exit(1), to test this properly comment these lines and run this test alone
    GTEST_SKIP();
    char* terminal_params[] = {"./main", "--help"};
    
    auto click_obj = click::Click("Test");
    testing::internal::CaptureStdout();
    
    click_obj.parse_commandline_args(2, terminal_params);
    
    std::string output = testing::internal::GetCapturedStdout();
    
    ASSERT_TRUE(output.find("Usage: Test [Options]") != std::string::npos);
}

//TEST(click, click_argument_parsing)
//{
//    {
//        auto arg = click::Argument<bool>("verbose",
//                                         "v",
//                                         [](const std::string &val){return val == "true";});
//
//        arg.set_value("true");
//
//        ASSERT_TRUE(arg.value);
//
//        arg.set_value("false");
//        ASSERT_FALSE(arg.value);
//
//        arg.set_value("lorem ipsum");
//        ASSERT_FALSE(arg.value);
//
//        arg.set_value("1234");
//        ASSERT_FALSE(arg.value);
//    }
//    {
//        auto arg = click::Argument<std::vector<int>>("verbose",
//                                         "v",
//                                         [](const std::string &val){
//                std::vector<int> items {};
//                const auto range_ = std::ranges::split_view(val, ',')
//                        | std::ranges::views::transform([](auto && chr) -> int {
//                    const std::ranges::common_view cv = std::ranges::common_view{chr};
//                    const std::string elem {cv.begin(), cv.end()};
//                    return std::stoi(elem);
//                });
//
//                items.reserve(std::ranges::distance(range_.begin(), range_.end()));
//                std::ranges::copy(range_, std::back_inserter(items));
//
//                return items;
//            });
//
//        arg.set_value("1,2,3,4");
//
//        ASSERT_EQ(arg.value, std::vector<int>({1, 2, 3, 4}));
//        ASSERT_ANY_THROW(arg.set_value("lorem ipsum"););
//    }
//}
//
//TEST(click_argument, click_object)
//{
//    auto click_obj = click::Click(std::vector<click::ClickArg>({
//        click::Argument<bool>("--verbose", "-v", [](const std::string &val){return val == "true";}),
//        click::Argument<std::string>("--path", "-p", [](const std::string &val){return val;}),
//    }));
//}
