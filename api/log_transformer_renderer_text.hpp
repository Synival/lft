#ifndef LFT_LOG_TRANSFORMER_RENDERER_CONSOLE_HPP_INCLUDED
#define LFT_LOG_TRANSFORMER_RENDERER_CONSOLE_HPP_INCLUDED

#include <map>
#include <iostream>

#include "common.hpp"
#include "log_transformer_renderer_i.hpp"

class LFT_API log_transformer_renderer_text : public log_transformer_renderer_i {
    LFT_DELETE_ALL_IMPLICIT_CONSTRUCTORS_AND_ASSIGNMENT_OPERATORS(log_transformer_renderer_text);
public:
    log_transformer_renderer_text(std::ostream &ostream = std::cout, int width = 80, int height = 24);
    virtual void render(const transform_results<double> &data, const log_transform_stats *stats = nullptr) const override;

private:
    std::ostream &_ostream;
    const int _width;
    const int _height;
};

#endif // LFT_LOG_TRANSFORMER_RENDERER_CONSOLE_HPP_INCLUDED