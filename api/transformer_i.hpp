#ifndef LFT_TRANSFORMER_I_HPP_INCLUDED
#define LFT_TRANSFORMER_I_HPP_INCLUDED

#include <map>
#include <complex>

#include "common.hpp"

class signal_data_i;

template<typename T>
class transform_results;

class LFT_API transformer_i {
    LFT_DELETE_ALL_IMPLICIT_COPY_CONSTRUCTORS_AND_ASSIGNMENT_OPERATORS(transformer_i);
public:
    transformer_i() {}
    virtual ~transformer_i() {}

    virtual int get_freq_count() const = 0;

    // Templated transform, specialized outside of the class to call virtual methods.
    template<typename T> transform_results<T> transform(const signal_data_i &signal) const;

private:
    virtual transform_results<std::complex<double>> transform_complex(const signal_data_i &signal) const = 0;
    virtual transform_results<double> transform_real(const signal_data_i &signal) const = 0;
};

template<> LFT_API transform_results<std::complex<double>> transformer_i::transform(const signal_data_i &signal) const;
template<> LFT_API transform_results<double> transformer_i::transform(const signal_data_i &signal) const;

#endif // LFT_TRANSFORMER_I_HPP_INCLUDED