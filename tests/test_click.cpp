//
// Created by felix on 07.08.23.
//

#include <ranges>
#include <algorithm>
#include "gtest/gtest.h"

//TEST(click_argument, click_argument_parsing)
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
