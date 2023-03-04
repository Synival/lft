#ifndef LFT_LOG_TRANSFORMER_FILTER_LINEARIZE_HPP
#define LFT_LOG_TRANSFORMER_FILTER_LINEARIZE_HPP

#include <map>
#include <vector>

#include "common.hpp"
#include "log_transformer_filter_i.hpp"

class LFT_API log_transformer_filter_linearize : public log_transformer_filter_i
{
    LFT_DELETE_ALL_IMPLICIT_COPY_CONSTRUCTORS_AND_ASSIGNMENT_OPERATORS(log_transformer_filter_linearize);
public:
    log_transformer_filter_linearize() : log_transformer_filter_i() {}

    virtual log_transform_stats filter_stats(const log_transform_stats &stats) const override;

private:
    virtual transform_results<std::complex<double>> filter_transform_complex(const transform_results<std::complex<double>> &transform) const override;
    virtual transform_results<double> filter_transform_real(const transform_results<double> &transform) const override;

    std::map<double, double> get_freq_conversion_table(const std::vector<double> &freqs) const;
};

#endif // LFT_LOG_TRANSFORMER_FILTER_LINEARIZE_HPP
