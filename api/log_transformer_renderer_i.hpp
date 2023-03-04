#ifndef LFT_LOG_TRANSFORMER_RENDERER_I_HPP_INCLUDED
#define LFT_LOG_TRANSFORMER_RENDERER_I_HPP_INCLUDED

#include "common.hpp"

template<typename T>
class transform_results;

class log_transform_stats;

class LFT_API log_transformer_renderer_i {
    LFT_DELETE_ALL_IMPLICIT_COPY_CONSTRUCTORS_AND_ASSIGNMENT_OPERATORS(log_transformer_renderer_i);
public:
    log_transformer_renderer_i() {}
    virtual ~log_transformer_renderer_i() {}

    virtual void render(const transform_results<double> &data, const log_transform_stats *stats = nullptr) const = 0;
};

#endif // LFT_LOG_TRANSFORMER_RENDERER_I_HPP_INCLUDED