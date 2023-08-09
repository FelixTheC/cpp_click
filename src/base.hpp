//
// Created by felix on 08.08.23.
//

#ifndef CPP_CLICK_BASE_HPP
#define CPP_CLICK_BASE_HPP

#include <string>
#include <any>
#include <functional>

namespace click
{
    class ClickOption
    {
    public:
        ClickOption() = default;
        ~ClickOption() = default;
        
        virtual std::string help_text() = 0;
    };
    
    class ClickArgument
    {
    private:
        std::string name_;
        uint nargs_ = 1;
        std::function<std::any(std::string)> parser_;
        std::any value_;
        
    public:
        ClickArgument(const ClickArgument& other)
        {
            name_ = other.name_;
            nargs_ = other.nargs_;
            parser_ = other.parser_;
            value_ = other.value_;
        }
        explicit ClickArgument(std::string name,
                               std::function<std::any(std::string)> &&parser) : name_(std::move(name)),
                                                                                parser_(std::move(parser)) {};
        
        ClickArgument(std::string name,
                      uint nargs,
                      std::function<std::any(std::string)> &&parser) : name_(std::move(name)),
                                                                       nargs_(nargs),
                                                                       parser_(std::move(parser)) {};
        
        ~ClickArgument() = default;
        ClickArgument& operator=(ClickArgument const &other)
        {
            name_ = other.name_;
            nargs_ = other.nargs_;
            parser_ = other.parser_;
            value_ = other.value_;
            
            return *this;
        }
        ClickArgument& operator=(ClickArgument&& other) noexcept
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

#endif //CPP_CLICK_BASE_HPP
