#include <cstdlib>
#include <cmath>
#include <iostream>
#include <algorithm>

#include "../api/signal_data_i.hpp"

#include "../api/signal_data_doublebuf.hpp"
#include "../api/transform_results.hpp"
#include "../api/log_transform_freq_stats.hpp"

#include "../api/log_transformer_variable_fourier.hpp"

static const std::vector<fourier_precalculations> make_precalculations(int bitrate, double sin_count, size_t min_size, const std::vector<double> &freq_table)
{
    std::vector<fourier_precalculations> results;
    results.reserve(freq_table.size());

    // This is the lowest sample size we can expect, based on the highest frequency always
    // being half the bitrate. The size is calculated as:
    //    size = sin_count * (bitrate / freq)
    // thus, for the highest frequency:
    //    smallest_possible_size = sin_count * (bitrate / highest_freq)
    //    smallest_possible_size = sin_count * (bitrate / (bitrate / 2))
    //    smallest_possible_size = sin_count * (2*bitrate / bitrate)
    //    smallest_possible_size = sin_count * 2
    const double smallest_possible_size = sin_count * 2.00;

    // When looking for lower frequencies, we can skip over data points to save computation time.
    // For whatever reason, a maximum skip of min_size^1/2 is perfect.
    const double max_step = std::sqrt(smallest_possible_size);

    int freq_count = freq_table.size();
    for (int f = 0; f < freq_count; ++f) {
        double freq = freq_table[f];
        double size = std::max(1.00, (double) bitrate / freq * sin_count);
        double step = max_step * freq_table[0] / freq;
        double freq_sin_count = sin_count;

        // Enforce a minimum sample size.
        if (size < (double) min_size) {
            double size_diff = (double) min_size / size;

            // If the step will still be below zero, don't bother - the next check will fix that.
            if (step * size_diff >= 1.00) {
                step *= size_diff;
                freq_sin_count *= size_diff;
                size = (size_t) min_size;
            }
        }

        // The results become very unreliable when the step is less than 1.00, so don't allow it!
        // Expand the sample size and number of waves to sample.
        if (step < 1.00) {
            freq_sin_count /= step;
            size /= step;
            step = 1.00;
        }

        results.emplace_back((double) size, freq_sin_count, step);
    }

    return results;
}

log_transformer_variable_fourier::log_transformer_variable_fourier(const signal_profile &profile, double lowest_freq, double sin_count, size_t min_size,
    int octave_subdivisions, int octaves
) :
    log_transformer_i(profile, lowest_freq, sin_count, octave_subdivisions, octaves),
    _min_size(min_size),
    _precalculations(make_precalculations(_profile.get_bitrate(), _sin_count, _min_size, _freq_table))
{}

std::complex<double> log_transformer_variable_fourier::transform_single_complex(const signal_data_i &signal, int freq_index) const
{
    const fourier_precalculations &pc = _precalculations[freq_index];
    double sample_len = pc.get_sample_len();
    double step = pc.get_step();
    size_t precalc_len = pc.get_cos_sin_table_len();
    double data_len = std::min(sample_len, (double) signal.get_data_len());
    const signal_data_read_buffer data_in = signal.get_data((size_t) sample_len);
    const double *data = data_in.get_data();

    double real = 0.00, imag = 0.00, id = 0.00;
    const fourier_precalculations_single *cos_sin_table = pc.get_cos_sin_table().data();
    for (size_t i = 0; i < precalc_len && (int) id < data_len; ++i, id += step, ++cos_sin_table) {
        double data_val = data[(int) id];
        real += data_val * cos_sin_table->get_pos_cos();
        imag += data_val * cos_sin_table->get_neg_sin();
    }

    double magnitude = 2.00 / (double) precalc_len;
    return std::complex<double> { real * magnitude, imag * magnitude };
}

double log_transformer_variable_fourier::transform_single_real(const signal_data_i &signal, int freq_index) const
{
    std::complex<double> input = transform_single_complex(signal, freq_index);
    return hypotf(input.real(), input.imag());
}

transform_results<std::complex<double>> log_transformer_variable_fourier::transform_complex(const signal_data_i &signal) const
{
    std::map<double, std::complex<double>> results;
    for (int f = 0; f < _freq_count; ++f) {
        std::complex<double> result = transform_single_complex(signal, f);
        results[_freq_table[f]] = result;
    }
    return transform_results<std::complex<double>>(std::move(results));
}

transform_results<double> log_transformer_variable_fourier::transform_real(const signal_data_i &signal) const
{
    std::map<double, double> results;
    for (int f = 0; f < _freq_count; ++f) {
        double result = transform_single_real(signal, f);
        results[_freq_table[f]] = result;
    }
    return transform_results<double>(results /*std::move(results)*/);
}

log_transform_freq_stats log_transformer_variable_fourier::get_freq_stats(int freq_index) const
{
    const fourier_precalculations &pc = _precalculations[freq_index];

    double sample_size = pc.get_sample_len();
    auto sample_duration = std::chrono::milliseconds((int) (sample_size / (double) _profile.get_bitrate() * 1000.00));
    double sample_step = pc.get_step();
    while (sample_step <= 0.50)
        sample_step *= 2.00;

    log_transform_freq_stats rval(sample_size, sample_duration, sample_step);

    return rval;
}
