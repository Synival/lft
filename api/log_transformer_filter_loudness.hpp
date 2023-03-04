#ifndef LFT_LOG_TRANSFORMER_FILTER_LOUDNESS_HPP_INCLUDED
#define LFT_LOG_TRANSFORMER_FILTER_LOUDNESS_HPP_INCLUDED

#include <complex>
#include <vector>
#include <map>

#include "common.hpp"
#include "log_transformer_filter_i.hpp"

class LFT_API log_transformer_filter_loudness : public log_transformer_filter_i
{
    LFT_DELETE_ALL_IMPLICIT_COPY_CONSTRUCTORS_AND_ASSIGNMENT_OPERATORS(log_transformer_filter_loudness);
public:
    log_transformer_filter_loudness() : log_transformer_filter_i() {}

private:
    virtual transform_results<std::complex<double>> filter_transform_complex(const transform_results<std::complex<double>> &transform) const override;
    virtual transform_results<double> filter_transform_real(const transform_results<double> &transform) const override;
};

#endif // LFT_LOG_TRANSFORMER_FILTER_LOUDNESS_HPP_INCLUDED