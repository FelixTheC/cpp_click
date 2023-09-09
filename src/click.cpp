#include "../include/clickArgument.hpp"
#include "../include/click.hpp"
#include "../include/utils.hpp"

#include <iostream>

void click::Click::parse_commandline_args(int argv, char *argc[])
{
    bool help_called_ = false;
    auto cmd_args = click::parse_commandline_args(argv, argc);
    std::vector<std::tuple<std::string, std::string>> parsed_args {};
    std::vector<std::tuple<std::string, std::string>> parsed_options {};
    
    std::for_each(cmd_args.begin(), cmd_args.end(),
                  [&parsed_args, &parsed_options](const auto &arg)
                  {
                    if (std::get<0>(arg)[0] == '-')
                    {
                        parsed_options.emplace_back(arg);
                    }
                    else
                    {
                        parsed_args.emplace_back(arg);
                    }
                  });
    
    cmd_args.clear();
    
    if (!arguments.empty() && !parsed_args.empty() && (parsed_args.size() != arguments.size()))
    {
        auto start_missing = arguments.size() - argv;
        std::stringstream missing_args;
        std::for_each(arguments.begin() + start_missing,
                      arguments.end(),
                      [&missing_args](const std::unique_ptr<click::Argument> &arg)
                      {
                          missing_args << arg->get_name() << " ";
                      });
        
        throw click::MissingArgument(missing_args.str());
    }
    
    if (!parsed_args.empty())
    {
        size_t idx = 0;
        std::for_each(arguments.begin(), arguments.end(),
                      [&idx, &parsed_args](const std::unique_ptr<click::Argument> &arg){
                          arg->set_value(std::get<0>(parsed_args[idx]));
                          ++idx;
                      });
    }
    
    std::for_each(options.begin(), options.end(),
                  [&parsed_options, &help_called_](const std::unique_ptr<click::Option> &opt)
                  {
                    std::for_each(parsed_options.begin(), parsed_options.end(),
                                  [&opt, &help_called_](auto &val)
                                  {
                                    const auto opt_name = std::get<0>(val);
                                    auto is_short_option = std::count(opt_name.begin(), opt_name.end(), '-') == 1;
                                      
                                      if (is_short_option)
                                      {
                                          if (opt->get_short_name() == opt_name)
                                          {
                                              opt->set_value(std::get<1>(val));
                                          }
                                      }
                                      else
                                      {
                                          if (opt->get_param_name() == opt_name)
                                          {
                                              if (opt_name == "--help")
                                              {
                                                  help_called_ = true;
                                              }
                                              opt->set_value(std::get<1>(val));
                                          }
                                      }
                                  });
                  });
    
    this->help_called = help_called_;
}

std::optional<std::unique_ptr<click::Option>> click::Click::get_option(const std::string &name) noexcept
{
    std::unique_ptr<click::Option> option = nullptr;
    
    std::for_each(options.begin(),
                  options.end(),
                  [&name, &option](std::unique_ptr<click::Option> &opt)
                  {
                      if (opt != nullptr && opt->get_name() == name)
                      {
                          option = std::move(opt);
                      }
                  });
    
    clean_nullptr_values_from_vec<std::unique_ptr<click::Option>>(options);
    
    if (option != nullptr)
    {
        return option;
    }
    return {};
}

std::optional<std::unique_ptr<click::Argument>> click::Click::get_argument(const std::string &name) noexcept
{
    std::unique_ptr<click::Argument> argument = nullptr;
    
    std::for_each(arguments.begin(),
                  arguments.end(),
                  [&name, &argument](std::unique_ptr<click::Argument> &arg)
                  {
                      if (arg != nullptr && arg->get_name() == name)
                      {
                          argument = std::move(arg);
                      }
                  });
    
    clean_nullptr_values_from_vec<std::unique_ptr<click::Argument>>(arguments);
    
    if (argument != nullptr)
    {
        return argument;
    }
    return {};
}

void click::Click::display_help_text()
{
    std::stringstream sstream;
    sstream << "Usage: " << project_name << " [Options]";
    sstream << "\n\n";
    sstream << "Options:\n";
    
    std::for_each(options.rbegin(),
                  options.rend(),
                  [&sstream](const std::unique_ptr<click::Option> &elem){sstream << elem->help_text() << "\n";});
    
    std::cout << sstream.str() << "\n";
    
    exit(1);
}

std::vector<std::tuple<std::string, std::string>> click::parse_commandline_args(int argv, char **argc) noexcept
{
    std::vector<std::tuple<std::string, std::string>> result {};
    for (int idx = 1; idx < argv; ++idx)
    {
        auto cmd_line_elem = std::string(argc[idx]);
        if (cmd_line_elem == "--")
        {
            // if we got the terminator we ignore it
            continue;
        }
        
        auto is_short_option = std::count(cmd_line_elem.begin(), cmd_line_elem.end(), '-') == 1;
        std::string param_value {};
        auto split_idx = cmd_line_elem.find('=');
        
        if(is_short_option && cmd_line_elem.size() > 2 && split_idx == std::string::npos)
        {
            auto tmp = cmd_line_elem.substr(0, 2);
            param_value = cmd_line_elem.substr(2);
            cmd_line_elem = std::move(tmp);
            
            result.emplace_back(std::tie(cmd_line_elem, param_value));
            continue;
        }
        
        if (split_idx < std::string::npos)
        {
            auto tmp = cmd_line_elem.substr(0, split_idx);
            param_value = cmd_line_elem.substr(split_idx + 1);
            cmd_line_elem = std::move(tmp);
        }
        else if (std::find(cmd_line_elem.begin(), cmd_line_elem.end(), '-') == cmd_line_elem.end())
        {
            result.emplace_back(std::tie(cmd_line_elem, param_value));
            continue;
        }
        else
        {
            // while idx < argv or we find a element which starts with -/--
            auto crnt_idx = idx + 1;
            auto first_element = true;
            
            while (crnt_idx < argv)
            {
                auto next_elem = std::string(argc[crnt_idx]);
                if (next_elem.rfind('-') == std::string::npos)
                {
                    if (!first_element)
                    {
                        param_value += " ";
                    }
                    first_element = false;
                    param_value += next_elem;
                    ++crnt_idx;
                }
                else
                {
                    --crnt_idx;
                    break;
                }
            }
            idx = crnt_idx;
        }
        result.emplace_back(std::tie(cmd_line_elem, param_value));
    }
    
    return result;
}
