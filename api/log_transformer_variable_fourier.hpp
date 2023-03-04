#ifndef LFT_LOG_TRANSFORMER_VARIABLE_FOURIER_HPP_INCLUDED
#define LFT_LOG_TRANSFORMER_VARIABLE_FOURIER_HPP_INCLUDED

#include <map>
#include <complex>
#include <chrono>
#include <vector>
#include <cstddef>

#include "common.hpp"
#include "log_transformer_i.hpp"
#include "log_transformer_fourier.hpp"

class LFT_API log_transformer_variable_fourier : public log_transformer_i {
    LFT_DELETE_ALL_IMPLICIT_CONSTRUCTORS_AND_ASSIGNMENT_OPERATORS(log_transformer_variable_fourier);
public:
    log_transformer_variable_fourier(const signal_profile &profile, double lowest_freq, double sin_count, size_t min_size,
        int octave_subdivisions, int octaves);

    inline size_t get_min_size() const
        { return _min_size; }

    virtual log_transform_freq_stats get_freq_stats(int freq_index) const override;

private:
    std::complex<double> transform_single_complex(const signal_data_i &signal, int freq_index) const;
    double transform_single_real(const signal_data_i &signal, int freq_index) const;

    virtual transform_results<std::complex<double>> transform_complex(const signal_data_i &signal) const override;
    virtual transform_results<double> transform_real(const signal_data_i &signal) const override;

    // Do not re-order!
    const size_t _min_size;
    const std::vector<fourier_precalculations> _precalculations;
};

#endif // LFT_LOG_TRANSFORMER_VARIABLE_FOURIER_HPP_INCLUDED