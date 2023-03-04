#ifndef LFT_UTILS_HPP_INCLUDED
#define LFT_UTILS_HPP_INCLUDED

#include <cmath>
#include <vector>
#include <map>
#include <iostream>

#include "common.hpp"

template<typename Tkey, typename Tvalue>
std::vector<Tkey> get_keys(const std::map<Tkey, Tvalue> map)
{
    std::vector<Tkey> result;
    result.resize(map.size());
    int i = 0;
    for (auto &in : map)
        result[i++] = in.first;
    return result;
}

constexpr double get_multiplier_one_first_to_log2_between(double first, double second)
    { return std::pow(2.00, (std::log2(first) + std::log2(second)) / 2.00) / first; }

// Outputs text to 'ostream' using a printf format string.
// Use this if you don't want to use ten thousand functions just to output some floating points.
LFT_API int ostream_printf(std::ostream &ostream, const char *format, va_list args);

// Outputs text to 'ostream' using a printf format string.
// Use this if you don't want to use ten thousand functions just to output some floating points.
LFT_API int ostream_printf(std::ostream &ostream, const char *format, ...);

#endif // LFT_UTILS_HPP_INCLUDED