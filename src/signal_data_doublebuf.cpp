#include <cstdlib>
#include <cstring>
#include <cmath>

#include "../api/signal_data_doublebuf.hpp"

signal_data_doublebuf::signal_data_doublebuf(const signal_profile &profile, size_t data_len) :
    signal_data_i(profile),
    _data_len(data_len),
    _buffer_size(sizeof(double) * _data_len * 2),
    _buffer_allocated(std::make_unique<double[]>(data_len * 2)),
    _buffer(_buffer_allocated.get()),
    _offset(0)
{
    reset();
}

signal_data_doublebuf::signal_data_doublebuf(const signal_profile &profile, std::chrono::milliseconds duration) :
    signal_data_doublebuf(profile, (double) profile.get_bitrate() * ((double) duration.count() / 1000.00))
{}

void signal_data_doublebuf::reset()
{
    memset(_buffer, 0, _buffer_size);
    _offset = 0;
}

void signal_data_doublebuf::apply_sine(double hz, double phase, double volume)
{
    constexpr double M_2PI = 2.00 * M_PI;
    const double hz_bitrate = hz / (double) _profile.get_bitrate();

    for (size_t pos = 0; pos < _data_len; ++pos) {
        _buffer[pos]             += std::sin((((double) pos * hz_bitrate) + phase) * M_2PI) * volume;
        _buffer[pos + _data_len] += _buffer[pos];
    }
}

void signal_data_doublebuf::apply_square(double hz, double phase, double volume)
{
    const double sq_size = (double) _profile.get_bitrate() / hz;
    const double sq_half = sq_size * 0.50;

    double sq_pos = std::fmod(phase, 1.00) * sq_size;

    for (size_t pos = 0; pos < _data_len; ++pos) {
        _buffer[pos]             += (sq_pos < sq_half) ? volume : -volume;
        _buffer[pos + _data_len] += _buffer[pos];
        sq_pos = std::fmod(sq_pos + 1.00, sq_size);
    }
}

void signal_data_doublebuf::apply_triangle(double hz, double phase, double volume)
{
    const double sq_4_4 = (double) _profile.get_bitrate() / hz;
    const double sq_1_4 = sq_4_4 * 0.25;
    const double sq_2_4 = sq_4_4 * 0.50;
    const double sq_3_4 = sq_4_4 * 0.75;
    const double vol_sq_1_4 = volume / sq_1_4;

    double sq_pos = std::fmod(phase, 1.00) * sq_4_4;

    for (size_t pos = 0; pos < _data_len; ++pos) {
             if (sq_pos < sq_1_4) _buffer[pos] += (sq_pos - 0.00  ) *  vol_sq_1_4;
        else if (sq_pos < sq_2_4) _buffer[pos] += (sq_2_4 - sq_pos) *  vol_sq_1_4;
        else if (sq_pos < sq_3_4) _buffer[pos] += (sq_pos - sq_2_4) * -vol_sq_1_4;
        else                      _buffer[pos] += (sq_4_4 - sq_pos) * -vol_sq_1_4;

        _buffer[pos + _data_len] = _buffer[pos];
        sq_pos = std::fmod(sq_pos + 1.00, sq_4_4);
    }
}

void signal_data_doublebuf::push(const std::vector<double> &vals)
    { push(vals.data(), vals.size()); }

void signal_data_doublebuf::push(const double *data, size_t len)
{
    const double *remaining_data = data;
    size_t remaining_len = len;

    while ((_offset + remaining_len) >= _data_len) {
        const size_t chunk_len = _data_len - _offset;
        const size_t chunk_size = chunk_len * sizeof(decltype(*data));

        memcpy(&(_buffer[_offset]),             remaining_data, chunk_size);
        memcpy(&(_buffer[_offset]) + _data_len, remaining_data, chunk_size);

        remaining_data += chunk_len;
        remaining_len  -= chunk_len;
        _offset = 0;
    }

    if (remaining_len > 0) {
        const size_t remaining_size = remaining_len * sizeof(decltype(*data));

        memcpy(&(_buffer[_offset]),             remaining_data, remaining_size);
        memcpy(&(_buffer[_offset]) + _data_len, remaining_data, remaining_size);

        _offset += remaining_len;
    }
}
