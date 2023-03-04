#ifndef LFT_LOG_TRANSFORMER_I_HPP_INCLUDED
#define LFT_LOG_TRANSFORMER_I_HPP_INCLUDED

#include <map>
#include <chrono>
#include <vector>

#include "common.hpp"
#include "transformer_i.hpp"

class signal_profile;
class log_transform_stats;
class log_transform_freq_stats;

class LFT_API log_transformer_i : public transformer_i {
    LFT_DELETE_ALL_IMPLICIT_CONSTRUCTORS_AND_ASSIGNMENT_OPERATORS(log_transformer_i);
public:
    virtual ~log_transformer_i() override {};

    log_transformer_i(const signal_profile &profile, double lowest_freq, double sin_count, int octave_subdivisions, int octaves);

    inline double get_lowest_freq() const
        { return _lowest_freq; }
    inline double get_sin_count() const
        { return _sin_count; }
    inline int get_octave_subdivisions() const
        { return _octave_subdivisions; }
    inline int get_octaves() const
        { return _octaves; }
    inline int get_freq_count() const override
        { return _freq_count; }

    virtual log_transform_freq_stats get_freq_stats(int freq_index) const = 0;
    log_transform_stats get_stats() const;

protected:
    const signal_profile &_profile;
    const double _lowest_freq;
    const double _sin_count;
    const int _octave_subdivisions;
    const int _octaves;
    const int _freq_count;
    const std::vector<double> _freq_table;
};

#endif // LFT_I_LOG_TRANSFORMER_HPP_INCLUDED