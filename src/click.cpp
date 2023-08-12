#include "click.hpp"

#include <iostream>

//void click::Click::parse_commandline_args(int argv, char *argc[])
//{
//    for (int idx = 1; idx < argv; ++idx)
//    {
//        auto cmd_line_elem = std::string(argc[idx]);
//        std::string cmd_line_val {};
//
//        if (cmd_line_elem == "--help")
//        {
//            display_help_text();
//        }
//
//        if (cmd_line_elem.find('=') < std::string::npos)
//        {
//            auto split_idx = cmd_line_elem.find('=');
//            auto tmp = cmd_line_elem.substr(0, split_idx);
//
//            cmd_line_val = cmd_line_elem.substr(split_idx + 1);
//            cmd_line_elem = std::move(tmp);
//        }
//        else
//        {
//            if (idx + 1 < argv)
//            {
//                auto next_cmd_line_elem = std::string(argc[idx + 1]);
//                if(next_cmd_line_elem.rfind("--") == std::string::npos ||
//                next_cmd_line_elem.rfind("-") == std::string::npos)
//                {
//                    ++idx;
//                    cmd_line_val = next_cmd_line_elem;
//                }
//            }
//        }
//
//        std::for_each(options.begin(),
//                      options.end(),
//                      [&cmd_line_elem, &cmd_line_val](const std::unique_ptr<click::Option> &option_)
//                      {
//                          if (option_->get_param_name() == cmd_line_elem)
//                          {
//                              option_->set_value(cmd_line_val);
//                          }
//                      });
//    }
//}

std::optional<std::unique_ptr<click::Option>> click::Click::get_option(const std::string &name) noexcept
{
    return {};
}

std::optional<std::unique_ptr<click::Argument>> click::Click::get_argument(const std::string &name) noexcept
{
    return {};
}

void click::Click::display_help_text()
{
    std::stringstream sstream;
    sstream << "Usage: Test [Options]";
    sstream << "\n\n";
    sstream << "Options:\n";
    
    std::for_each(options.rbegin(),
                  options.rend(),
                  [&sstream](const std::unique_ptr<click::Option> &elem){sstream << elem->help_text();});
    
    std::cout << sstream.str() << "\n";
    
    exit(1);
}

std::vector<std::tuple<std::string, std::string>> click::parse_commandline_args(int argv, char **argc) noexcept
{
    std::vector<std::tuple<std::string, std::string>> result {};
    for (int idx = 1; idx < argv; ++idx)
    {
        auto cmd_line_elem = std::string(argc[idx]);
        
        if(cmd_line_elem.rfind('-') == 0)
        {
            std::string param_value {};
            auto split_idx = cmd_line_elem.find('=');
            
            if (split_idx < std::string::npos)
            {
                auto tmp = cmd_line_elem.substr(0, split_idx);
                param_value = cmd_line_elem.substr(split_idx + 1);
                cmd_line_elem = tmp;
            }
            else
            {
                // while idx < argv or we find a element which starts with -/--
            }
            result.emplace_back(std::tie(cmd_line_elem, param_value));
        }
    }
    
    return result;
}
