
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
        bool value_is_set_ = false;
        bool is_flag_ = false;
        std::string name_ {};
        std::string default_val_str {};
        std::string param_name_ {};
        std::string param_name_short_ {};
        std::string help_text_ {};
        std::any value_;
        std::any default_value_ {};
        std::function<std::any(std::string)> parser_;
        
        void set_name(std::string val)
        {
            name_ = std::move(val);
            if (name_.size() == 1)
            {
                param_name_short_ = "-" + name_;
            }
            else
            {
                param_name_ = "--" + name_;
            }
        }
    
    public:
        Option(Option &&other) noexcept
          {
            value_is_set_ = other.value_is_set_;
            is_flag_ = other.is_flag_;
            name_ = other.name_;
            default_val_str = other.default_val_str;
            param_name_ = other.param_name_;
            param_name_short_ = other.param_name_short_;
            help_text_ = other.help_text_;
            value_ = other.value_;
            default_value_ = other.default_value_;
            parser_ = other.parser_;
            
            other.value_is_set_ = {};
            other.is_flag_ = false;
            other.name_ = {};
            other.default_val_str = {};
            other.help_text_ = {};
            other.help_text_ = {};
            other.value_ = {};
            other.default_value_ = {};
            other.parser_ = {};
        }
        explicit Option(std::string flag_name)
        {
            set_name(std::move(flag_name));
            is_flag_ = true;
            set_default_value<bool>(false);
        };
        Option(std::string name, std::function<std::any(std::string)> &&parser)
        {
            set_name(std::move(name));
            parser_ = std::move(parser);
        };
        Option(std::string name,
               char name_short,
               std::function<std::any(std::string)> &&parser)
        {
            name_ = std::move(name);
            param_name_ = "--" + name_;
            param_name_short_ = "-";
            param_name_short_ += name_short;
            parser_ = std::move(parser);
        };
        ~Option() = default;
        
        Option& operator=(Option const &other)
        {
            value_is_set_ = other.value_is_set_;
            is_flag_ = other.is_flag_;
            name_ = other.name_;
            default_val_str = other.default_val_str;
            param_name_ = other.param_name_;
            param_name_short_ = other.param_name_short_;
            help_text_ = other.help_text_;
            value_ = other.value_;
            default_value_ = other.default_value_;
            parser_ = other.parser_;
            
            return *this;
        }
        
        Option& operator=(Option&& other) noexcept
        {
            value_is_set_ = other.value_is_set_;
            is_flag_ = other.is_flag_;
            name_ = other.name_;
            default_val_str = other.default_val_str;
            param_name_ = other.param_name_;
            param_name_short_ = other.param_name_short_;
            help_text_ = other.help_text_;
            value_ = other.value_;
            default_value_ = other.default_value_;
            parser_ = other.parser_;
            
            other.value_is_set_ = {};
            other.is_flag_ = false;
            other.name_ = {};
            other.default_val_str = {};
            other.help_text_ = {};
            other.help_text_ = {};
            other.value_ = {};
            other.default_value_ = {};
            other.parser_ = {};
            
            return *this;
        }
        
        void set_value(std::string arg)
        {
            if (is_flag_)
            {
                value_ = !std::any_cast<bool>(default_value_);
            }
            else
            {
                value_ = parser_(std::move(arg));
            }
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
        [[nodiscard]] T get_value()
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
        
        [[nodiscard]] std::string get_name() noexcept
        {
            return name_;
        }
        
        [[nodiscard]] std::string get_param_name() noexcept
        {
            return param_name_;
        }
        
        [[nodiscard]] std::string get_short_name() noexcept
        {
            return param_name_short_;
        }
        
        [[nodiscard]] bool is_flag() const noexcept
        {
            return is_flag_;
        }
        
        void set_help_text(const std::string &val) noexcept
        {
            help_text_ = val;
        }
        
        [[nodiscard]] std::string help_text()
        {
            std::stringstream sstream;
            sstream << (param_name_.empty() ? param_name_short_ : param_name_);
            sstream << " ";
            if (!help_text_.empty())
            {
                sstream << "     ";
                sstream << help_text_;
            }
            else
            {
                sstream << "<" << default_value_.type().name() << ">";
                if (!default_val_str.empty())
                {
                    sstream << "     ";
                    sstream << "[default: " << default_val_str << "]";
                }
            }
            
            return sstream.str();
        }
    };
}

#endif //CPP_CLICK_OPTION_HPP
