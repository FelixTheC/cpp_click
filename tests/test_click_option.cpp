#include "gtest/gtest.h"
#include "../src/option.hpp"


TEST(test_click_option, create_click_option)
{
    auto simple_option = click::Option<int>("--n",
                                            [](const std::string &val) -> int {return std::stoi(val);});
    
    ASSERT_NO_FATAL_FAILURE(simple_option.help_text());
}

TEST(test_click_option, create_option_with_short_name)
{
    auto simple_option = click::Option<int>("--n",
                                            "-n",
                                            [](const std::string &val) -> int {return std::stoi(val);});
    
    ASSERT_EQ(simple_option.get_name(), "--n");
    ASSERT_EQ(simple_option.get_short_name(), "-n");
}

TEST(test_click_option, create_option_with_help_text)
{
    auto simple_option = click::Option<int>("--n",
                                            "",
                                            "lorem ipsum",
                                            [](const std::string &val) -> int {return std::stoi(val);});
    
    ASSERT_EQ(simple_option.help_text(), "lorem ipsum");
}

TEST(test_click_option, create_option_with_default)
{
    auto simple_option = click::Option<int>("--n",
                                            "",
                                            "",
                                            10,
                                            [](const std::string &val) -> int {return std::stoi(val);});
    
    ASSERT_EQ(simple_option.get_value(), 10);
}

TEST(test_click_option, create_option_with_visible_default)
{
    auto simple_option = click::Option<int>("--n",
                                            "",
                                            "",
                                            1,
                                            true,
                                            [](const std::string &val) -> int {return std::stoi(val);});
    
    ASSERT_NO_FATAL_FAILURE(simple_option.help_text());
}

TEST(test_click_option, move_option)
{
    auto simple_option = click::Option<int>("--n",
                                            "",
                                            "",
                                            1,
                                            true,
                                            [](const std::string &val) -> int {return std::stoi(val);});
    
    click::Option<int> other_option = std::move(simple_option);
    
    ASSERT_EQ(other_option.get_value(), 1);
    ASSERT_TRUE(simple_option.get_name().empty());
}
