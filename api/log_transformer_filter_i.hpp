#ifndef LFT_LOG_TRANSFORMER_FITLER_I_HPP_INCLUDED
#define LFT_LOG_TRANSFORMER_FITLER_I_HPP_INCLUDED

#include <complex>

#include "common.hpp"

template<typename T>
class transform_results;

class log_transform_stats;

class LFT_API log_transformer_filter_i
{
    LFT_DELETE_ALL_IMPLICIT_COPY_CONSTRUCTORS_AND_ASSIGNMENT_OPERATORS(log_transformer_filter_i);
public:
    log_transformer_filter_i() {}
    virtual ~log_transformer_filter_i() {}

    template<typename T>
    transform_results<T> filter_transform(const transform_results<T> &transform) const;

    virtual log_transform_stats filter_stats(const log_transform_stats &stats) const;
    virtual double inverse_lowest_freq(double lowest_freq_in, int octave_divs) const;

private:
    virtual transform_results<std::complex<double>> filter_transform_complex(const transform_results<std::complex<double>> &transform) const = 0;
    virtual transform_results<double> filter_transform_real(const transform_results<double> &transform) const = 0;
};

template<> LFT_API transform_results<std::complex<double>> log_transformer_filter_i::filter_transform(const transform_results<std::complex<double>> &transform) const;
template<> LFT_API transform_results<double> log_transformer_filter_i::filter_transform(const transform_results<double> &transform) const;

#endif // LFT_LOG_TRANSFORMER_FITLER_I_HPP_INCLUDED