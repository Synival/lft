#ifndef LFT_SIGNAL_DATA_DOUBLEBUF_HPP_INCLUDED
#define LFT_SIGNAL_DATA_DOUBLEBUF_HPP_INCLUDED

#include <memory>

#include "common.hpp"

#include "signal_data_read_buffer.hpp"
#include "signal_data_i.hpp"

class LFT_API signal_data_doublebuf : public signal_data_i {
    LFT_DELETE_ALL_IMPLICIT_CONSTRUCTORS_AND_ASSIGNMENT_OPERATORS(signal_data_doublebuf);
public:
    signal_data_doublebuf(const signal_profile &profile, size_t data_len);
    signal_data_doublebuf(const signal_profile &profile, std::chrono::milliseconds duration);

    virtual inline size_t get_data_len() const override
        { return _data_len; }

    virtual void reset() override;
    virtual void apply_sine(double hz, double phase, double volume = 1.00) override;
    virtual void apply_square(double hz, double phase, double volume = 1.00) override;
    virtual void apply_triangle(double hz, double phase, double volume = 1.00) override;
    virtual void push(const std::vector<double> &vals) override;
    virtual void push(const double *data, size_t len) override;

    virtual inline signal_data_read_buffer get_data(size_t amount) const override
    {
        amount = std::min(_data_len, amount);
        return signal_data_read_buffer { _buffer + _offset + (_data_len - amount), amount };
    }

private:
    // Order dependent on initialization. Do not re-order!
    const size_t _data_len;    // Length of data (number of double's)
    const size_t _buffer_size; // Size of the entire buffer in bytes
    std::unique_ptr<double[]> _buffer_allocated; // Bytes allocated and owned internally
    double *const _buffer;     // Pointer to data to use (regardless of ownership)
    size_t _offset;            // Offset of _buffer for the current point to read/write
};

#endif // LFT_SIGNAL_DATA_HPP_INCLUDED