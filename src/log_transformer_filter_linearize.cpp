#include <algorithm>

#include "../api/log_transform_stats.hpp"
#include "../api/transform_results.hpp"
#include "../api/utils.hpp"

#include "../api/log_transformer_filter_linearize.hpp"

log_transform_stats log_transformer_filter_linearize::filter_stats(const log_transform_stats &stats) const
{
    const std::map<double, log_transform_freq_stats> &input_stats = stats.get_freq_stats();
    const std::map<double, double> freq_conversion_table = get_freq_conversion_table(get_keys<double>(input_stats));

    std::map<double, log_transform_freq_stats> output_stats {};
    for (auto &i : input_stats)
        output_stats.emplace(freq_conversion_table.at(i.first), i.second);

    return log_transform_stats { std::move(output_stats) };
}

transform_results<std::complex<double>> log_transformer_filter_linearize::filter_transform_complex(const transform_results<std::complex<double>> &transform) const
{
    // TODO: actually handle this!
    return transform_results<std::complex<double>> { transform };
}

transform_results<double> log_transformer_filter_linearize::filter_transform_real(const transform_results<double> &transform) const
{
    std::map<double, double> new_results {};
    const std::map<double, double> &input_results = transform.get_results();
    const std::vector<double> &freqs = get_keys<double>(input_results);
    const std::map<double, double> &freq_conversion_table = get_freq_conversion_table(freqs);

    for (auto &i : input_results)
        new_results[freq_conversion_table.at(i.first)] = i.second;

    return transform_results<double> { std::move(new_results) };
}

std::map<double, double> log_transformer_filter_linearize::get_freq_conversion_table(const std::vector<double> &freqs) const
{
    std::map<double, double> results;
    double low = freqs.front();
    double high = freqs.back();
    double range = high - low;
    size_t pos_max = freqs.size() - 1;

    int pos = 0;
    for (auto &i : freqs) {
        double percent = (double) pos / (double) pos_max;
        results[i] = percent * range + low;
        ++pos;
    }

    return results;
}
