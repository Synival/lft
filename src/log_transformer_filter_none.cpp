#include "../api/log_transformer_i.hpp"
#include "../api/transform_results.hpp"

#include "../api/log_transformer_filter_none.hpp"

transform_results<std::complex<double>> log_transformer_filter_none::filter_transform_complex(const transform_results<std::complex<double>> &transform) const
    { return transform_results<std::complex<double>> { transform }; }
transform_results<double> log_transformer_filter_none::filter_transform_real(const transform_results<double> &transform) const
    { return transform_results<double> { transform }; }
