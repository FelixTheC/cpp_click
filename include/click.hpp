#ifndef CPP_CLICK_LIBRARY_H
#define CPP_CLICK_LIBRARY_H

#include <memory>
#include <optional>
#include <string>
#include <typeinfo>
#include <utility>
#include <variant>
#include <vector>

#include "clickArgument.hpp"
#include "clickOption.hpp"

using ClickOpt = click::Option;

namespace click
{
    class MissingArgument : public std::exception
    {
    private:
        std::string message;
    
    public:
        explicit MissingArgument(std::string msg) : message(std::move(msg)) {}
        [[nodiscard]] const char* what() const noexcept override
        {
            return message.c_str();
        }
    };
    
    [[ nodiscard ]]std::vector<std::tuple<std::string, std::string>> parse_commandline_args(int argv, char *argc[]) noexcept;
    
    struct Click
    {
        bool help_called = false;
        std::string project_name = {};
        std::vector<std::unique_ptr<click::Option>> options {};
        std::vector<std::unique_ptr<click::Argument>> arguments {};
        
        explicit Click(std::string proj_name) : project_name(std::move(proj_name))
        {
            auto help_options = click::Option("help", [](const std::string &val){return val;});
            help_options.set_help_text("Show this message and exit.");
            options.emplace_back(std::make_unique<ClickOpt>(std::move(help_options)));
        };
        ~Click() = default;
        
        void parse_commandline_args(int argv, char *argc[]);
        std::optional<std::unique_ptr<click::Option>> get_option(const std::string &name) noexcept;
        std::optional<std::unique_ptr<click::Argument>> get_argument(const std::string &name) noexcept;
        
        void display_help_text();
    };
}

#endif //CPP_CLICK_LIBRARY_H
