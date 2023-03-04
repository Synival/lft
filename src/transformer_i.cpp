#include "../api/transform_results.hpp"

#include "../api/transformer_i.hpp"

template<> transform_results<std::complex<double>> transformer_i::transform(const signal_data_i &signal) const
    { return transform_complex(signal); }
template<> transform_results<double> transformer_i::transform(const signal_data_i &signal) const
    { return transform_real(signal); }
