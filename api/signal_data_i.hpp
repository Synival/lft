#ifndef LFT_SIGNAL_DATA_I_HPP_INCLUDED
#define LFT_SIGNAL_DATA_I_HPP_INCLUDED

#include <chrono>
#include <vector>

#include "common.hpp"

#include "signal_profile.hpp"

class signal_data_read_buffer;

class LFT_API signal_data_i {
    LFT_DELETE_ALL_IMPLICIT_CONSTRUCTORS_AND_ASSIGNMENT_OPERATORS(signal_data_i);
public:
    signal_data_i(const signal_profile &profile)
        : _profile(profile)
    {}
    virtual ~signal_data_i() {}

    inline const signal_profile &get_profile() const
        { return _profile; }
    inline int get_bitrate() const
        { return _profile.get_bitrate(); }

    virtual size_t get_data_len() const = 0;

    virtual void reset() = 0;
    virtual void apply_sine(double hz, double phase, double volume = 1.00) = 0;
    virtual void apply_square(double hz, double phase, double volume = 1.00) = 0;
    virtual void apply_triangle(double hz, double phase, double volume = 1.00) = 0;
    virtual void push(const std::vector<double> &vals) = 0;
    virtual void push(const double *data, size_t len) = 0;

    virtual signal_data_read_buffer get_data(size_t amount) const = 0;

    virtual std::chrono::milliseconds get_duration() const
        { return std::chrono::milliseconds((int) ((double) get_data_len() * 1000.00 / (double) _profile.get_bitrate())); }

protected:
    // Order dependent on initialization. Do not re-order!
    const signal_profile &_profile; // Profile for data (bitrate)
};

#endif // LFT_SIGNAL_DATA_I_HPP_INCLUDED
