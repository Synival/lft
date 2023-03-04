#include "../api/log_transform_stats.hpp"

#include "../api/log_transformer_i.hpp"

static const std::vector<double> make_freq_table(double lowest_freq, int octave_subdivisions, int freq_count)
{
    std::vector<double> results;
    results.reserve(freq_count);

    for (int f = 0; f < freq_count; ++f)
        results.emplace_back(powf(2.00, (double) f / (double) octave_subdivisions) * lowest_freq);
    return results;
}

log_transformer_i::log_transformer_i(const signal_profile &profile, double lowest_freq, double sin_count, int octave_subdivisions, int octaves) :
    _profile(profile),
    _lowest_freq(lowest_freq),
    _sin_count(sin_count),
    _octave_subdivisions(octave_subdivisions),
    _octaves(octaves),
    _freq_count(_octave_subdivisions * _octaves),
    _freq_table(make_freq_table(_lowest_freq, _octave_subdivisions, _freq_count))
{}

log_transform_stats log_transformer_i::get_stats() const
{
    std::map<double, log_transform_freq_stats> results;
    for (int i = 0; i < _freq_count; ++i)
        results.emplace(_freq_table[i], get_freq_stats(i));

    return log_transform_stats { std::move(results) };
}
