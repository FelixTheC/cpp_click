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
    class Argument : ClickArgument
    {
    private:
        std::string name_;
        uint nargs_ = 1;
        std::function<T(std::string)> parser_;
        T value_;
        
    public:
        explicit Argument(std::string name,
                          std::function<T(std::string)> parser) : name_(std::move(name)), parser_(std::move(parser)) {};

        Argument(std::string name,
                 uint nargs,
                 std::function<T(std::string)> parser) : name_(std::move(name)), nargs_(nargs), parser_(std::move(parser)) {};
        
        ~Argument() = default;
        
        std::string get_name()
        {
            return name_;
        }
        
        uint get_nargs()
        {
            return nargs_;
        }
        
        T get_value()
        {
            return value_;
        }
        
        void set_value(std::string &val)
        {
            value_ = parser_(std::move(val));
        }
    };
}

#endif //CPP_CLICK_ARGUMENT_HPP
