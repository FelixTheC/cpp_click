
#ifndef CPP_CLICK_OPTION_HPP
#define CPP_CLICK_OPTION_HPP

#include <functional>
#include <sstream>
#include <string>
#include <utility>


namespace click
{
    class Option
    {
    private:
        std::string default_val_str {};
        bool value_is_set_ = false;
        std::string name_;
        std::string name_short_ {};
        std::string help_text_ {};
        std::any value_;
        std::any default_value_ {};
        std::function<std::any(std::string)> parser_;
    
    public:
        Option(Option &&other) noexcept
          {
            default_val_str = other.default_val_str;
            value_is_set_ = other.value_is_set_;
            name_ = other.name_;
            name_short_ = other.name_short_;
            help_text_ = other.name_short_;
            value_ = other.value_;
            default_value_ = other.default_value_;
            parser_ = other.parser_;
            
            other.default_val_str = {};
            other.value_is_set_ = false;
            other.name_ = {};
            other.name_short_ = {};
            other.help_text_ = {};
            other.value_ = {};
            other.default_value_ = {};
            other.parser_ = {};
        }
        Option(std::string name,
                        std::function<std::any(std::string)> &&parser) : name_(std::move(name)),
                                                                         parser_(std::move(parser)) {};
        Option(std::string name,
               std::string name_short,
               std::function<std::any(std::string)> &&parser) : name_(std::move(name)),
                                                                     name_short_(std::move(name_short)),
                                                                     parser_(std::move(parser)) {};
        ~Option() = default;
        
        Option& operator=(Option const &other)
        {
            default_val_str = other.default_val_str;
            value_is_set_ = other.value_is_set_;
            name_ = other.name_;
            name_short_ = other.name_short_;
            help_text_ = other.name_short_;
            value_ = other.value_;
            default_value_ = other.default_value_;
            parser_ = other.parser_;
            
            return *this;
        }
        
        Option& operator=(Option&& other) noexcept
        {
            default_val_str = other.default_val_str;
            value_is_set_ = other.value_is_set_;
            name_ = std::move(other.name_);
            name_short_ = std::move(other.name_short_);
            help_text_ = std::move(other.name_short_);
            value_ = other.value_;
            default_value_ = other.default_value_;
            parser_ = std::move(other.parser_);
            
            other.default_val_str = {};
            other.value_is_set_ = false;
            other.name_ = {};
            other.name_short_ = {};
            other.help_text_ = {};
            other.value_ = {};
            other.default_value_ = {};
            other.parser_ = {};
            
            return *this;
        }
        
        void set_value(std::string arg)
        {
            value_ = parser_(std::move(arg));
            value_is_set_ = true;
        }
        
        template<typename T>
        void set_default_value(const T &default_val)
        {
            std::stringstream sstream;
            sstream << default_val;
            
            default_value_ = std::move(default_val);
            default_val_str = sstream.str();
        }
        
        template<typename T>
        T get_value()
        {
            if (value_is_set_)
            {
                return std::any_cast<T>(value_);
            }
            else
            {
                return std::any_cast<T>(default_value_);
            }
        }
        
        std::string get_name() noexcept
        {
            return name_;
        }
        
        std::string get_short_name() noexcept
        {
            return name_short_;
        }
        
        void set_help_text(const std::string &val) noexcept
        {
            help_text_ = val;
        }
        
        std::string help_text()
        {
            if (!help_text_.empty())
            {
                return help_text_;
            }
            
            std::stringstream sstream;
            sstream << name_;
            sstream << " ";
            sstream << "<" << default_value_.type().name() << ">";
            
            if (!default_val_str.empty())
            {
                sstream << "     ";
                sstream << "[default: " << default_val_str << "]";
            }
            
            return sstream.str();
        }
    };
}

#endif //CPP_CLICK_OPTION_HPP
