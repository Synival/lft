#include <algorithm>

#include "../api/transform_results.hpp"

#include "../api/log_transformer_filter_partial_normalize.hpp"

transform_results<std::complex<double>> log_transformer_filter_partial_normalize::filter_transform_complex(const transform_results<std::complex<double>> &transform) const
{
    // TODO: actually handle this!
    return transform_results<std::complex<double>> { transform };
}

transform_results<double> log_transformer_filter_partial_normalize::filter_transform_real(const transform_results<double> &transform) const
{
    std::map<double, double> new_results { transform.get_results() };

    // Get the maximum value in the transformation set.
    double max = std::max_element(
        new_results.begin(), new_results.end(),
        [](const std::pair<const double, double> &p1, const std::pair<const double, double> &p2) { return p1.second < p2.second; }
    )->second;
/*
    // If the volume is below 100%, we don't need to do anything here.
    if (max < 1.00)
        return transform_results<double> { std::move(new_results) };
*/

    // Determine the new max and the multiplier for it.
    double new_max = (max - 1.00) * 0.50 + 1.00;
    double mult = 1.00 / new_max;

    // Give us the new result set.
    for (auto i = new_results.begin(); i != new_results.end(); ++i)
        i->second *= mult;
    return transform_results<double> { std::move(new_results) };
}