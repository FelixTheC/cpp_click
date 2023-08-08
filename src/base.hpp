//
// Created by felix on 08.08.23.
//

#ifndef CPP_CLICK_BASE_HPP
#define CPP_CLICK_BASE_HPP

#include <string>

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
    public:
        ClickArgument() = default;
        ~ClickArgument() = default;
    };
}

#endif //CPP_CLICK_BASE_HPP
