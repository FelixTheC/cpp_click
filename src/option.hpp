
#ifndef CPP_CLICK_OPTION_HPP
#define CPP_CLICK_OPTION_HPP

#include <functional>
#include <string>
#include <utility>
#include "base.hpp"

namespace click
{
    
    template<typename T>
    class Option : ClickOption
    {
    private:
        bool show_default_ = false;
        bool value_is_set_ = false;
        std::string name_;
        std::string name_short_ {};
        std::string help_text_ {};
        T value_;
        T default_value_ {};
        std::function<T(std::string)> parser_;
        
    public:
        explicit Option(std::string name,
                        std::function<T(std::string)> &&parser) : name_(std::move(name)),
                                                                  parser_(std::move(parser)) {};
        Option(std::string name,
               std::string name_short,
               std::function<T(std::string)> &&parser) : name_(std::move(name)),
                                                         name_short_(std::move(name_short)),
                                                         parser_(std::move(parser)) {};
        Option(std::string name,
               std::string name_short,
               std::string help_text,
               std::function<T(std::string)> &&parser) : name_(std::move(name)),
                                                         name_short_(std::move(name_short)),
                                                         help_text_(std::move(help_text)),
                                                         parser_(std::move(parser)) {};
        Option(std::string name,
               std::string name_short,
               std::string help_text,
               T default_value,
               std::function<T(std::string)> &&parser) : name_(std::move(name)),
                                                         name_short_(std::move(name_short)),
                                                         help_text_(std::move(help_text)),
                                                         default_value_(default_value),
                                                         parser_(std::move(parser)) {};
        Option(std::string name,
               std::string name_short,
               std::string help_text,
               T default_value,
               bool show_default,
               std::function<T(std::string)> &&parser) : name_(std::move(name)),
                                                         name_short_(std::move(name_short)),
                                                         help_text_(std::move(help_text)),
                                                         default_value_(default_value),
                                                         show_default_(show_default),
                                                         parser_(std::move(parser)) {};
        ~Option() = default;
        
        Option(Option&&) = default;
        Option& operator=(Option&& other) noexcept
        {
            show_default_ = other.show_default_;
            value_is_set_ = other.value_is_set_;
            name_ = std::move(other.name_);
            name_short_ = std::move(other.name_short_);
            help_text_ = std::move(other.name_short_);
            value_ = other.value_;
            default_value_ = other.default_value_;
            parser_ = std::move(other.parser_);
            
            other.show_default_ = false;
            other.value_is_set_ = false;
            other.name_ = {};
            other.name_short_ = {};
            other.help_text_ = {};
            other.value_ = {};
            other.default_value_ = {};
            other.parser_ = {};
        }
        
        void set_value(std::string &arg)
        {
            value_ = parser_(std::move(arg));
            value_is_set_ = true;
        }
        
        T get_value()
        {
            if (value_is_set_)
            {
                return value_;
            }
            else
            {
                return default_value_;
            }
        }
        
        std::string get_name()
        {
            return name_;
        }
        
        std::string get_short_name()
        {
            return name_short_;
        }
        
        std::string help_text() override
        {
            if (!help_text_.empty())
            {
                return help_text_;
            }
            
            std::stringstream sstream;
            sstream << name_;
            sstream << " ";
            sstream << typeid(T).name();
            if (show_default_)
            {
                sstream << "       ";
                sstream << "[default: " << default_value_ << "]";
            }
            
            return sstream.str();
        }
    };
}

#endif //CPP_CLICK_OPTION_HPP
