
#include <gtest/gtest.h>
#include "../include/clickArgument.hpp"

TEST(click_argument, create_click_argument)
{
    auto argument = click::Argument("foo", [](const std::string &val) -> int {return std::stoi(val);});
    
    ASSERT_EQ(argument.get_name(), "foo");
    ASSERT_EQ(argument.get_nargs(), 1);
}

TEST(click_argument, move_option)
{
    auto argument = click::Argument("bar", [](const std::string &val) -> int {return std::stoi(val);});
    
    click::Argument other_argument = std::move(argument);
    
    ASSERT_EQ(other_argument.get_name(), "bar");
    ASSERT_TRUE(argument.get_name().empty());
}

TEST(click_argument, set_value)
{
    auto argument = click::Argument("foobar", [](const std::string &val) -> int {return std::stoi(val);});
    
    argument.set_value("1234");
    
    ASSERT_EQ(argument.get_value<int>(), 1234);
    
    argument.set_value("01234");
    ASSERT_EQ(argument.get_value<int>(), 1234);
    
    ASSERT_ANY_THROW(argument.set_value("jon doe"));
}