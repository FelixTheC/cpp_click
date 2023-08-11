#include "click.hpp"

#include <iostream>

void click::Click::parse_commandline_args(int argv, char **argc)
{

}

std::optional<std::unique_ptr<click::Option>> click::Click::get_option(const std::string &name) noexcept
{
    return {};
}

std::optional<std::unique_ptr<click::Argument>> click::Click::get_argument(const std::string &name) noexcept
{
    return {};
}
