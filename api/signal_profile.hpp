#ifndef LFT_SIGNAL_PROFILE_HPP_INCLUDED
#define LFT_SIGNAL_PROFILE_HPP_INCLUDED

#include <cstddef>
#include <memory>
#include <chrono>

#include "common.hpp"

class LFT_API signal_profile {
    LFT_DELETE_ALL_IMPLICIT_CONSTRUCTORS_AND_ASSIGNMENT_OPERATORS(signal_profile);
public:
    signal_profile(int bitrate);

    inline int get_bitrate() const
        { return _bitrate; }

private:
    // Order dependent on initialization. Do not re-order!
    const int _bitrate; // Bitrate of data
};

#endif // LFT_SIGNAL_PROFILE_HPP_INCLUDED