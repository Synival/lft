#include <cmath>

#include "../api/utils.hpp"
#include "../api/log_transform_stats.hpp"
#include "../api/transform_results.hpp"

#include "../api/log_transformer_filter_hypot.hpp"

log_transform_stats log_transformer_filter_hypot::filter_stats(const log_transform_stats &stats) const
{
    const std::map<double, log_transform_freq_stats> &input_stats = stats.get_freq_stats();
    std::map<double, log_transform_freq_stats> output_stats {};

    if (input_stats.size() <= 1)
        return log_transform_stats { input_stats };

    std::map<double, double> freq_conversion_table = get_freq_conversion_table(get_keys<double>(input_stats));
    for (auto &i : input_stats) {
        // Don't bother actually modifying the stats; they're a bit meaningless now.
        // All we want to do is make sure they correspond to the correct frequencies.
        output_stats.emplace(freq_conversion_table[i.first], i.second);
    }
    return log_transform_stats { std::move(output_stats) };
}

transform_results<std::complex<double>> log_transformer_filter_hypot::filter_transform_complex(const transform_results<std::complex<double>> &transform) const
    { return transform; }

transform_results<double> log_transformer_filter_hypot::filter_transform_real(const transform_results<double> &transform) const
{
    const std::map<double, double> &input_results = transform.get_results();
    if (input_results.size() <= 1)
        return transform_results { input_results };

    const std::map<double, double> &freq_conversion_table = get_freq_conversion_table(get_keys<double>(input_results));

    auto i = input_results.begin();
    auto i_next = std::next(i, 1);
    auto f = freq_conversion_table.begin();

    std::map<double, double> output_results {};

    while (i != input_results.end()) {
        double index = f->second;
        if (i_next == input_results.end()) {
            output_results[index] = i->second;
            break;
        }

        output_results[index] = std::hypot(i->second, i_next->second);

        i = i_next;
        i_next++;
        f++;
    }

    return transform_results { std::move(output_results) };
}

std::map<double, double> log_transformer_filter_hypot::get_freq_conversion_table(const std::vector<double> &freqs) const
{
    std::map<double, double> results;

    if (freqs.size() <= 1) {
        for (auto &i : freqs)
            results[i] = i;
        return results;
    }

    auto i = freqs.begin();
    double mult = get_multiplier_one_first_to_log2_between(*i, *std::next(i, 1));
    for (auto &i : freqs)
        results[i] = i * mult;
    return results;
}

double log_transformer_filter_hypot::inverse_lowest_freq(double lowest_freq_in, int octave_divs) const
    { return std::pow(2.00, std::log2(lowest_freq_in) - (0.50 / (double) octave_divs)); }
