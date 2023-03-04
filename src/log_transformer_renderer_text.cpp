#include <cstdio>
#include <cstring>

#include "../api/log_transformer_i.hpp"
#include "../api/utils.hpp"
#include "../api/log_transform_stats.hpp"
#include "../api/transform_results.hpp"

#include "../api/log_transformer_renderer_text.hpp"

log_transformer_renderer_text::log_transformer_renderer_text(std::ostream &ostream, int width, int height) :
    _ostream(ostream),
    _width(width),
    _height(height)
{}

static char *get_freq_stats(char *buf, size_t buf_len, const log_transform_stats *stats, double freq)
{
    if (stats == nullptr) {
        std::snprintf(buf, buf_len, "%8.2f Hz", freq);
    }
    else {
        const log_transform_freq_stats &freq_stats = stats->get_freq_stats().find(freq)->second;
        std::snprintf(buf, buf_len, "%8.2f Hz [len=%5lld][step=%7.2f][ms=%4d]",
            freq,
            (long long) freq_stats.get_sample_size(),
            freq_stats.get_sample_step(),
            (int) freq_stats.get_sample_duration().count()
        );
    }
    return buf;
}

void log_transformer_renderer_text::render(const transform_results<double> &data, const log_transform_stats *stats) const
{
    const std::map<double, double> &results = data.get_results();

    int freq_index_i = 0;
    int freq_index_max_i = results.size();

    double freq_index_d = 0.00;
    double freq_index_max_d = (double) freq_index_max_i;

    auto i = results.begin();

    char stats_buf[256];
    double step = freq_index_max_d / (double) _height;

    for (int line = 0; line < _height; line++) {
        double freq = i->first;

        get_freq_stats(stats_buf, sizeof(stats_buf), stats, freq);
        int amp_width = _width - std::strlen(stats_buf) - 5;

        int left_side  = std::min(amp_width, std::max((int) (i->second * (double) amp_width), 1));
        int right_side = amp_width - left_side;

        ostream_printf(_ostream, "| %s |%*s%*s|", stats_buf, left_side, "*", right_side, "");
            _ostream << std::endl;

        freq_index_d += step;
        int new_freq_index_i = std::min(freq_index_max_i - 1, (int) (freq_index_d + 0.001));
        int step = new_freq_index_i - freq_index_i;
        if (step > 0) {
            i = std::next(i, step);
            freq_index_i = new_freq_index_i;
        }
    }
}
