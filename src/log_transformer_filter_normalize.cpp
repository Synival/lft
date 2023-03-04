#include <algorithm>

#include "../api/log_transformer_i.hpp"
#include "../api/transform_results.hpp"

#include "../api/log_transformer_filter_normalize.hpp"

transform_results<std::complex<double>> log_transformer_filter_normalize::filter_transform_complex(const transform_results<std::complex<double>> &transform) const
{
    // TODO: actually handle this!
    return transform_results<std::complex<double>> { transform };
}

transform_results<double> log_transformer_filter_normalize::filter_transform_real(const transform_results<double> &transform) const
{
    std::map<double, double> new_results { transform.get_results() };

    // Get the maximum value in the transformation set. Don't let it be too low to avoid division by zero errors.
    double max = std::max_element(
        new_results.begin(), new_results.end(),
        [](const std::pair<const double, double> &p1, const std::pair<const double, double> &p2) { return p1.second < p2.second; }
    )->second;
    if (max < 0.001)
        max = 0.001;

    // Give us the new result set.
    for (auto i = new_results.begin(); i != new_results.end(); ++i)
        i->second /= max;
    return transform_results<double> { std::move(new_results) };
}
