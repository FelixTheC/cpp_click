#include "gtest/gtest.h"
#include "../include/clickOption.hpp"


TEST(test_click_option, create_click_option)
{
    auto simple_option = click::Option("num",
                                       [](const std::string &val) -> int {return std::stoi(val);});
    
    ASSERT_EQ(simple_option.get_param_name(), "--num");
    ASSERT_TRUE(simple_option.get_short_name().empty());
}

TEST(test_click_option, create_option_with_short_name)
{
    auto simple_option = click::Option("num",
                                       'n',
                                       [](const std::string &val) -> int {return std::stoi(val);});

    ASSERT_EQ(simple_option.get_param_name(), "--num");
    ASSERT_EQ(simple_option.get_short_name(), "-n");
}

TEST(test_click_option, create_option_with_help_text)
{
    auto simple_option = click::Option("n",
                                       [](const std::string &val) -> int {return std::stoi(val);});
    
    simple_option.set_help_text("lorem ipsum");
    ASSERT_EQ(simple_option.help_text(), "-n      lorem ipsum");
}

TEST(test_click_option, create_option_with_default)
{
    auto simple_option = click::Option("n",
                                       [](const std::string &val) -> int {return std::stoi(val);});
    
    simple_option.set_default_value<int>(10);
    ASSERT_EQ(simple_option.get_value<int>(), 10);
}

TEST(test_click_option, create_option_with_visible_default)
{
    auto simple_option = click::Option("n",
                                       [](const std::string &val) -> int {return std::stoi(val);});
    
    simple_option.set_default_value<int>(3);

    ASSERT_NO_FATAL_FAILURE(simple_option.help_text());
    ASSERT_TRUE(simple_option.help_text().find('n') < std::string::npos);
    ASSERT_TRUE(simple_option.help_text().find("[default: 3]") < std::string::npos);
}

TEST(test_click_option, move_option)
{
    auto simple_option = click::Option("n",
                                       [](const std::string &val) -> int {return std::stoi(val);});
    
    simple_option.set_default_value<int>(42);
    
    click::Option other_option = std::move(simple_option);

    ASSERT_EQ(other_option.get_value<int>(), 42);
    ASSERT_TRUE(simple_option.get_param_name().empty());
}

TEST(test_click_option, click_option_set_value)
{
    auto simple_option = click::Option("n",
                                       [](const std::string &val) -> int {return std::stoi(val);});

    simple_option.set_value("1234");
    ASSERT_EQ(simple_option.get_value<int>(), 1234);
}

TEST(test_click_option, click_option_is_flag)
{
    {
        auto opt = click::Option("check");
        
        ASSERT_EQ(opt.get_param_name(), "--check");
        ASSERT_TRUE(opt.is_flag());
        ASSERT_FALSE(opt.get_value<bool>());
    }
    {
        auto opt = click::Option("check");
        opt.set_default_value<bool>(true);
        
        ASSERT_EQ(opt.get_param_name(), "--check");
        ASSERT_TRUE(opt.is_flag());
        ASSERT_TRUE(opt.get_value<bool>());
    }
}

TEST(test_click_option, set_click_option_flag_value)
{
    {
        auto opt = click::Option("check");
        opt.set_value("");
        
        ASSERT_TRUE(opt.get_value<bool>());
    }
    {
        auto opt = click::Option("check");
        opt.set_value(" ");

        ASSERT_TRUE(opt.get_value<bool>());
    }
    {
        auto opt = click::Option("check");
        opt.set_value("1234");
        
        ASSERT_TRUE(opt.get_value<bool>());
    }
    {
        auto opt = click::Option("check");
        opt.set_value("0");
        
        ASSERT_TRUE(opt.get_value<bool>());
    }
    {
        auto opt = click::Option("check");
        opt.set_value("lorem ipsum");

        ASSERT_TRUE(opt.get_value<bool>());
    }
}
