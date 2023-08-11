#ifndef CPP_CLICK_LIBRARY_H
#define CPP_CLICK_LIBRARY_H

#include <memory>
#include <optional>
#include <string>
#include <typeinfo>
#include <variant>
#include <vector>

#include "argument.hpp"
#include "option.hpp"


namespace click
{
    struct Click
    {
        std::vector<std::unique_ptr<click::Option>> options {};
        std::vector<std::unique_ptr<click::Argument>> arguments {};
        
        Click() = default;
        ~Click() = default;
        
        void parse_commandline_args(int argv, char *argc[]);
        
        std::optional<std::unique_ptr<click::Option>> get_option(const std::string &name) noexcept;
        std::optional<std::unique_ptr<click::Argument>> get_argument(const std::string &name) noexcept;
        
    };
}

#endif //CPP_CLICK_LIBRARY_H
