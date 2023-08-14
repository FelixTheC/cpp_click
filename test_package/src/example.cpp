#include "click.hpp"

using ClickArg = click::Argument;
using ClickOpt = click::Option;

int main(int argv, char* argc[]) {
    
    auto clk = click::Click("example_proj");
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
    
    char* terminal_params[] = {"./main", "-w", "--user", "1234", "--", "server"};
    // normally this way but during the build we need to set it by hand
    // clk.parse_commandline_args(argv, argc);
    clk.parse_commandline_args(6, terminal_params);
}