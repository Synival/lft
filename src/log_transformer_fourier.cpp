#include <cstdlib>
#include <cmath>

#include "../api/signal_data_i.hpp"
#include "../api/transform_results.hpp"
#include "../api/signal_data_read_buffer.hpp"
#include "../api/transform_results.hpp"
#include "../api/log_transform_freq_stats.hpp"

#include "../api/log_transformer_fourier.hpp"

static const std::vector<fourier_precalculations_single> make_cos_sin_table(size_t len, double sample_len, double sin_count, double step)
{
    constexpr double PIx2 = 2.00 * M_PI;
    const double theta_inc = PIx2 * sin_count * step / sample_len;

    std::vector<fourier_precalculations_single> results;
    double theta = 0.00;

    results.reserve(len);
    for (size_t i = 0; i < len; ++i) {
        results.emplace_back(cos(theta), -sin(theta));
        theta += theta_inc;
    }

    return results;
}

fourier_precalculations::fourier_precalculations(double sample_len, double sin_count, double step) :
    _sample_len(sample_len),
    _sin_count(sin_count),
    _step(step),
    _cos_sin_table_len((int) std::ceil(_sample_len / _step)),
    _cos_sin_table(make_cos_sin_table(_cos_sin_table_len, _sample_len, _sin_count, _step))
{}

static const std::vector<fourier_precalculations> make_precalculations(int bitrate, double sin_count, int octave_subdivisions, const std::vector<double> &freq_table)
{
    std::vector<fourier_precalculations> results;
    results.reserve(octave_subdivisions);

    // Always use the full sample size necessary to detect the lowest frequency.
    double size = (double) bitrate / freq_table[0] * sin_count;

    // Always use the step necessary to detect the highest frequency.
    constexpr double step = 1.00;

    for (int f = 0; f < octave_subdivisions; ++f)
        results.emplace_back((double) size, sin_count, step);

    return results;
}

log_transformer_fourier::log_transformer_fourier(const signal_profile &profile, double lowest_freq, double sin_count, int octave_subdivisions, int octaves) :
    log_transformer_i(profile, lowest_freq, sin_count, octave_subdivisions, octaves),
    _precalculations(make_precalculations(_profile.get_bitrate(), _sin_count, _octave_subdivisions, _freq_table))
{}

transform_results<std::complex<double>> log_transformer_fourier::transform_single_complex(const signal_data_i &signal, int f) const
{
    const fourier_precalculations &pc = _precalculations[f];
    std::map<double, std::complex<double>> results;

    {
        double sample_len = pc.get_sample_len();
        double step = pc.get_step();
        double magnitude = step / sample_len;
        int precalc_incr = 1;
        size_t precalc_len = pc.get_cos_sin_table_len();
        double data_len = std::min(sample_len, (double) signal.get_data_len());
        const signal_data_read_buffer data_in = signal.get_data((size_t) sample_len);

        const double *data = data_in.get_data();

        for (int octave = 0; octave < _octaves; ++octave) {
            // We never need to step by less than 1/2, so give us some minor performance gains.
            while (step < 0.50) {
                step *= 2.00;
                magnitude *= 2.00;
                precalc_incr *= 2;
            }

            double real = 0.00, imag = 0.00;
            {
                double id = 0.00;

                const fourier_precalculations_single *cos_sin_table = pc.get_cos_sin_table().data();
                for (size_t i = 0; i < precalc_len && i < data_len; i += precalc_incr) {
                    double data_val = data[(int) id];

                    real += data_val * cos_sin_table->get_pos_cos();
                    imag += data_val * cos_sin_table->get_neg_sin();

                    id += step;
                    cos_sin_table += precalc_incr;
                }
            }

            results[_freq_table[f]] = std::complex<double> { real, imag } * magnitude;
            f += _octave_subdivisions;
        }
    }

    return transform_results<std::complex<double>>(std::move(results));
}

transform_results<double> log_transformer_fourier::transform_single_real(const signal_data_i &signal, int freq_index) const
{
    transform_results<std::complex<double>> input = transform_single_complex(signal, freq_index);
    std::map<double, double> output;

    for (auto &kv : input.get_results()) {
        const std::complex<double> &val = kv.second;
        output[kv.first] = hypotf(val.real(), val.imag());
    }

    return transform_results<double>(std::move(output));
}

transform_results<std::complex<double>> log_transformer_fourier::transform_complex(const signal_data_i &signal) const
{
    std::map<double, std::complex<double>> results;
    for (int i = 0; i < _octave_subdivisions; ++i) {
        const std::map<double, std::complex<double>> tcs = transform_single_complex(signal, i).get_results();
        results.insert(tcs.begin(), tcs.end());
    }
    return transform_results<std::complex<double>>(std::move(results));
}

transform_results<double> log_transformer_fourier::transform_real(const signal_data_i &signal) const
{
    std::map<double, double> results;
    for (int i = 0; i < _octave_subdivisions; ++i) {
        const std::map<double, double> trs = transform_single_real(signal, i).get_results();
        results.insert(trs.begin(), trs.end());
    }
    return transform_results<double>(std::move(results));
}

log_transform_freq_stats log_transformer_fourier::get_freq_stats(int freq_index) const
{
    const fourier_precalculations &pc = _precalculations[freq_index % _octave_subdivisions];

    double sample_size = pc.get_sample_len();
    auto sample_duration = std::chrono::milliseconds((int) (sample_size / (double) _profile.get_bitrate() * 1000.00));
    double sample_step = pc.get_step();
    while (sample_step <= 0.50)
        sample_step *= 2.00;

    log_transform_freq_stats rval(sample_size, sample_duration, sample_step);

    return rval;
}
