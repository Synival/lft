#ifndef LFT_LOG_TRANSFORMER_FILTER_PARTIAL_NORMALIZE_HPP
#define LFT_LOG_TRANSFORMER_FILTER_PARTIAL_NORMALIZE_HPP

#include "log_transformer_filter_i.hpp"

class LFT_API log_transformer_filter_partial_normalize : public log_transformer_filter_i
{
    LFT_DELETE_ALL_IMPLICIT_COPY_CONSTRUCTORS_AND_ASSIGNMENT_OPERATORS(log_transformer_filter_partial_normalize);
public:
    log_transformer_filter_partial_normalize() : log_transformer_filter_i() {}

private:
    virtual transform_results<std::complex<double>> filter_transform_complex(const transform_results<std::complex<double>> &transform) const override;
    virtual transform_results<double> filter_transform_real(const transform_results<double> &transform) const override;
};

#endif // LFT_LOG_TRANSFORMER_FILTER_PARTIAL_NORMALIZE_HPP