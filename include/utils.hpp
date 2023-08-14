//
// Created by felix on 13.08.23.
//

#ifndef CPP_CLICK_UTILS_HPP
#define CPP_CLICK_UTILS_HPP

#include <vector>

template<typename T>
void clean_nullptr_values_from_vec(std::vector<T> &arguments) noexcept
{
    auto iter = std::remove(arguments.begin(), arguments.end(), nullptr);
    // remove moves all elements which should be deleted to the end of the vector
    arguments.erase(iter, arguments.end());
    arguments.shrink_to_fit();
}

#endif //CPP_CLICK_UTILS_HPP
