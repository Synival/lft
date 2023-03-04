#ifndef LFT_LOG_TRANSFORMER_FOURIER_HPP_INCLUDED
#define LFT_LOG_TRANSFORMER_FOURIER_HPP_INCLUDED

#include <map>
#include <complex>
#include <chrono>
#include <vector>
#include <cstddef>

#include "common.hpp"
#include "fourier_precalculations.hpp"
#include "log_transformer_i.hpp"

class LFT_API log_transformer_fourier : public log_transformer_i {
    LFT_DELETE_ALL_IMPLICIT_CONSTRUCTORS_AND_ASSIGNMENT_OPERATORS(log_transformer_fourier);
public:
    log_transformer_fourier(const signal_profile &profile, double lowest_freq, double sin_count, int octave_subdivisions, int octaves);

    virtual log_transform_freq_stats get_freq_stats(int freq_index) const override;

private:
    transform_results<std::complex<double>> transform_single_complex(const signal_data_i &signal, int freq_index) const;
    transform_results<double> transform_single_real(const signal_data_i &signal, int freq_index) const;

    virtual transform_results<std::complex<double>> transform_complex(const signal_data_i &signal) const override;
    virtual transform_results<double> transform_real(const signal_data_i &signal) const override;

    // Do not re-order!
    const std::vector<fourier_precalculations> _precalculations;
};

#endif // LFT_LOG_TRANSFORMER_FOURIER_HPP_INCLUDED