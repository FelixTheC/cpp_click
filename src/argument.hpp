//
// Created by felix on 08.08.23.
//

#ifndef CPP_CLICK_ARGUMENT_HPP
#define CPP_CLICK_ARGUMENT_HPP

#include <any>
#include <functional>
#include <string>


namespace click
{
    class Argument
    {
    private:
        std::string name_;
        uint nargs_ = 1;
        std::function<std::any(std::string)> parser_;
        std::any value_;
    
    public:
        Argument(Argument &&other) noexcept
        {
            name_ = other.name_;
            nargs_ = other.nargs_;
            parser_ = other.parser_;
            value_ = other.value_;
            
            other.name_ = {};
            other.nargs_ = {};
            other.parser_ = {};
            other.value_ = {};
        }
        explicit Argument(std::string name,
                          std::function<std::any(std::string)> &&parser) : name_(std::move(name)),
                                                                                parser_(std::move(parser)) {};
        
        Argument(std::string name,
                 uint nargs,
                 std::function<std::any(std::string)> &&parser) : name_(std::move(name)),
                                                                       nargs_(nargs),
                                                                       parser_(std::move(parser)) {};
        
        ~Argument() = default;
        Argument& operator=(Argument const &other)
        {
            name_ = other.name_;
            nargs_ = other.nargs_;
            parser_ = other.parser_;
            value_ = other.value_;
            
            return *this;
        }
        Argument& operator=(Argument&& other) noexcept
        {
            name_ = other.name_;
            nargs_ = other.nargs_;
            parser_ = other.parser_;
            value_ = other.value_;
            
            other.name_ = {};
            other.nargs_ = {};
            other.parser_ = {};
            other.value_ = {};
            
            return *this;
        }
        
        std::string get_name()
        {
            return name_;
        }
        
        uint get_nargs()
        {
            return nargs_;
        }
        
        template<typename T>
        T get_value()
        {
            return std::any_cast<T>(value_);
        }
        
        void set_value(std::string val)
        {
            value_ = parser_(std::move(val));
        }
    };
}

#endif //CPP_CLICK_ARGUMENT_HPP
