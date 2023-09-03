# CPP click
A simple cpp implementation of the awesome python library [click](https://palletsprojects.com/p/click/)

## What features are implemented
currently following features in a simple version are implemented
- options
- arguments

## How to install via conan
- install [conan](https://docs.conan.io/2/installation.html)
- clone project via git
- in the project DIR run
```shell
conan create . -s build_type=Release
```

## How to use
```c++
#include <filesystem>
#include <iostream>

#include "click.hpp"
#include "clickArgument.hpp"
#include "clickOption.hpp"

namespace fs = std::filesystem;

void create_commandline_args(click::Click &cppClick);

int main(int argv, char *argc[])
{
    click::Click cppClick {"isort"};
    create_commandline_args(cppClick);

    cppClick.parse_commandline_args(argv, argc);
    
    if (cppClick.help_called)
    {
        cppClick.display_help_text();
    }
    else
    {
        auto path = cppClick.get_argument("file_path").value()->get_value<std::string>();
        auto check_only = cppClick.get_option("check").value()->get_value<bool>();
        
        ...
    }

    return EXIT_SUCCESS;
}

void create_commandline_args(click::Click &cppClick)
{
    click::Option isortOption {"check"};
    click::Argument fileArg {"file_path",
                             [](const std::string &val) -> std::string
                             {
                                 bool validFile = (fs::is_regular_file(val) &&
                                                   isort::utils::is_cpp_file(val)) ||
                                                   fs::is_directory(val);
                                 if (validFile)
                                 {
                                     return val;
                                 }
                                 else
                                 {
                                     throw std::invalid_argument("Incorrect file path.: '" + val + "'");
                                 }
                             }};
    cppClick.arguments.emplace_back(std::make_unique<click::Argument>(std::move(fileArg)));
    cppClick.options.emplace_back(std::make_unique<click::Option>(std::move(isortOption)));
}

```
