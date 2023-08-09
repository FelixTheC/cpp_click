//
// Created by felix on 08.08.23.
//

#ifndef CPP_CLICK_ARGUMENT_HPP
#define CPP_CLICK_ARGUMENT_HPP

#include <functional>
#include "base.hpp"

namespace click
{
    
    template<typename T>
    class Argument : public ClickArgument
    {
    public:
        explicit Argument(std::string name,
                          std::function<T(std::string)> &&parser) : ClickArgument(std::move(name), std::move(parser)) {};

        Argument(std::string name,
                 uint nargs,
                 std::function<T(std::string)> &&parser) : ClickArgument(std::move(name), nargs, std::move(parser)) {};

        ~Argument() = default;
//        Argument& operator=(Argument const &other) = default;
//        Argument& operator=(Argument&& other) = default;
    };
}

#endif //CPP_CLICK_ARGUMENT_HPP
