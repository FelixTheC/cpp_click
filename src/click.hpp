#ifndef CPP_CLICK_LIBRARY_H
#define CPP_CLICK_LIBRARY_H

#include <string>
#include <vector>


namespace click
{
    struct Click
    {
        std::vector<std::string> options {};
        
        Click() = default;
        ~Click() = default;
        
    };
}

#endif //CPP_CLICK_LIBRARY_H
