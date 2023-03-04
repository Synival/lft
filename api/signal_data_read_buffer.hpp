#ifndef LFT_SIGNAL_DATA_READ_BUFFER_HPP_INCLUDED
#define LFT_SIGNAL_DATA_READ_BUFFER_HPP_INCLUDED

#include <cstddef>

#include "common.hpp"

class signal_data_read_buffer {
    LFT_DELETE_ALL_IMPLICIT_CONSTRUCTORS_AND_ASSIGNMENT_OPERATORS(signal_data_read_buffer);
public:
    signal_data_read_buffer(const double *data, size_t len)
        : _data(data), _len(len)
    {}

    inline const double *get_data() const
        { return _data; }
    inline size_t get_len() const
        { return _len; }

private:
    const double *_data;
    size_t _len;
};

#endif // LFT_SIGNAL_DATA_READ_BUFFER_HPP_INCLUDED