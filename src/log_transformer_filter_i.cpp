#include "../api/transformer_i.hpp"

#include "../api/log_transformer_i.hpp"
#include "../api/log_transform_stats.hpp"
#include "../api/transform_results.hpp"

#include "../api/log_transformer_filter_i.hpp"

log_transform_stats log_transformer_filter_i::filter_stats(const log_transform_stats &stats) const
    { return log_transform_stats { stats }; }
double log_transformer_filter_i::inverse_lowest_freq(double lowest_freq_in, int /*octave_divs*/) const
    { return lowest_freq_in; }

template<> transform_results<std::complex<double>> log_transformer_filter_i::filter_transform(const transform_results<std::complex<double>> &transform) const
    { return filter_transform_complex(transform); }
template<> transform_results<double> log_transformer_filter_i::filter_transform(const transform_results<double> &transform) const
    { return filter_transform_real(transform); }
