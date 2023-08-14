//
// Created by felix on 07.08.23.
//

#include <ranges>
#include "gtest/gtest.h"
#include "../include/click.hpp"

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
    
//    click_obj.parse_commandline_args(2, terminal_params);
    
    std::string output = testing::internal::GetCapturedStdout();
    
    ASSERT_TRUE(output.find("Usage: Test [Options]") != std::string::npos);
}

TEST(click, parse_cmd_line_arg_simple_short_option)
{
    char* terminal_params[] = {"./main", "-w"};
    auto result = click::parse_commandline_args(2, terminal_params);
    
    ASSERT_EQ(result.size(), 1);
    ASSERT_EQ(std::get<0>(result[0]), "-w");
    ASSERT_TRUE(std::get<1>(result[0]).empty());
}

TEST(click, parse_cmd_line_arg_simple_short_option_with_equal)
{
    char* terminal_params[] = {"./main", "-u=name"};
    auto result = click::parse_commandline_args(2, terminal_params);
    
    ASSERT_EQ(result.size(), 1);
    ASSERT_EQ(std::get<0>(result[0]), "-u");
    ASSERT_EQ(std::get<1>(result[0]), "name");
}

TEST(click, parse_cmd_line_arg_simple_short_option_with_single_space_value)
{
    char* terminal_params[] = {"./main", "-u", "name"};
    auto result = click::parse_commandline_args(3, terminal_params);
    
    ASSERT_EQ(result.size(), 1);
    ASSERT_EQ(std::get<0>(result[0]), "-u");
    ASSERT_EQ(std::get<1>(result[0]), "name");
}

TEST(click, parse_cmd_line_arg_simple_short_option_with_multiple_space_value)
{
    char* terminal_params[] = {"./main", "-u", "name1", "name2", "name3"};
    auto result = click::parse_commandline_args(5, terminal_params);
    
    ASSERT_EQ(result.size(), 1);
    ASSERT_EQ(std::get<0>(result[0]), "-u");
    ASSERT_EQ(std::get<1>(result[0]), "name1 name2 name3");
}

TEST(click, parse_cmd_line_arg_simple_short_option_value_immediatly_after)
{
    char* terminal_params[] = {"./main", "-uname"};
    auto result = click::parse_commandline_args(2, terminal_params);
    
    ASSERT_EQ(result.size(), 1);
    ASSERT_EQ(std::get<0>(result[0]), "-u");
    ASSERT_EQ(std::get<1>(result[0]), "name");
}

TEST(click, parse_cmd_line_arg_long_option)
{
    char* terminal_params[] = {"./main", "--write"};
    auto result = click::parse_commandline_args(2, terminal_params);
    
    ASSERT_EQ(result.size(), 1);
    ASSERT_EQ(std::get<0>(result[0]), "--write");
    ASSERT_TRUE(std::get<1>(result[0]).empty());
}

TEST(click, parse_cmd_line_arg_long_option_with_equal_sign)
{
    char* terminal_params[] = {"./main", "--user=name"};
    auto result = click::parse_commandline_args(2, terminal_params);
    
    ASSERT_EQ(result.size(), 1);
    ASSERT_EQ(std::get<0>(result[0]), "--user");
    ASSERT_EQ(std::get<1>(result[0]), "name");
}

TEST(click, parse_cmd_line_arg_long_option_with_values_by_space)
{
    char* terminal_params[] = {"./main", "--user", "name1", "name2", "name3"};
    auto result = click::parse_commandline_args(5, terminal_params);
    
    ASSERT_EQ(result.size(), 1);
    ASSERT_EQ(std::get<0>(result[0]), "--user");
    ASSERT_EQ(std::get<1>(result[0]), "name1 name2 name3");
}

TEST(click, parse_cmd_line_arg_long_option_and_arguments)
{
    char* terminal_params[] = {"./main", "foobar", "--user", "name"};
    auto result = click::parse_commandline_args(4, terminal_params);
    
    ASSERT_EQ(result.size(), 2);
    ASSERT_EQ(std::get<0>(result[0]), "foobar");
    ASSERT_TRUE(std::get<1>(result[0]).empty());
    ASSERT_EQ(std::get<0>(result[1]), "--user");
    ASSERT_EQ(std::get<1>(result[1]), "name");
}

TEST(click, parse_cmd_line_with_terminator)
{
    char* terminal_params[] = {"./main", "-w", "--user", "name", "--", "server"};
    auto result = click::parse_commandline_args(6, terminal_params);
    
    ASSERT_EQ(result.size(), 3);
    
    ASSERT_EQ(std::get<0>(result[0]), "-w");
    ASSERT_TRUE(std::get<1>(result[0]).empty());
    
    ASSERT_EQ(std::get<0>(result[1]), "--user");
    ASSERT_EQ(std::get<1>(result[1]), "name");
    
    ASSERT_EQ(std::get<0>(result[2]), "server");
    ASSERT_TRUE(std::get<1>(result[2]).empty());
}

TEST(click, click_parse_cmd_line_arguments)
{
    char* terminal_params[] = {"./main", "/tmp/in", "/tmp/out"};
    
    auto clk = click::Click("my_proj");
    clk.arguments.emplace_back(
            std::make_unique<click::Argument>(
                    click::Argument("path_in", [](const std::string &val){return val;})
                    ));
    clk.arguments.emplace_back(
            std::make_unique<click::Argument>(
                    click::Argument("path_out", [](const std::string &val){return val;})
            ));
    
    clk.parse_commandline_args(3, terminal_params);
    
    ASSERT_EQ(clk.get_argument("path_in").value()->get_value<std::string>(), "/tmp/in");
    ASSERT_EQ(clk.get_argument("path_out").value()->get_value<std::string>(), "/tmp/out");
    
    ASSERT_EQ(clk.arguments.size(), 0);
}

TEST(click, click_parse_cmd_line_arguments_throws_error_when_attributes_missing)
{
    char* terminal_params[] = {"./main", "/tmp/in"};
    
    auto clk = click::Click("my_proj");
    clk.arguments.emplace_back(
            std::make_unique<click::Argument>(
                    click::Argument("path_in", [](const std::string &val){return val;})
            ));
    clk.arguments.emplace_back(
            std::make_unique<click::Argument>(
                    click::Argument("path_out", [](const std::string &val){return val;})
            ));
    
    ASSERT_THROW(clk.parse_commandline_args(2, terminal_params), click::MissingArgument);
}

TEST(click, click_parse_cmd_line_with_terminator)
{
    char* terminal_params[] = {"./main", "-w", "--user", "1234", "--", "server"};
    
    auto clk = click::Click("my_proj");
    clk.arguments.emplace_back(
            std::make_unique<click::Argument>(
                    click::Argument("server", [](const std::string &val){return val;})
            ));
    clk.options.emplace_back(
            std::make_unique<click::Option>(
                    click::Option("w", [](const std::string &val){return val;})
            ));
    clk.options.emplace_back(
            std::make_unique<click::Option>(
                    click::Option("user", [](const std::string &val) -> int {return std::stoi(val);})
            ));
    
    clk.parse_commandline_args(6, terminal_params);
    
    ASSERT_EQ(clk.options.size(), 3); // help options is always included
    ASSERT_EQ(clk.arguments.size(), 1);
    
    auto argument_result = clk.get_argument("server");
    ASSERT_EQ(argument_result->get()->get_value<std::string>(), "server");
    
    auto option_result = clk.get_option("user");
    ASSERT_EQ(option_result->get()->get_value<int>(), 1234);
}
