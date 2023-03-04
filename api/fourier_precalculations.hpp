#ifndef LFT_FOURIER_PRECALCULATIONS_HPP_INCLUDED
#define LFT_FOURIER_PRECALCULATIONS_HPP_INCLUDED

#include <cstddef>
#include <vector>

#include "fourier_precalculations_single.hpp"

class fourier_precalculations {
public:
    fourier_precalculations(double sample_len, double sin_count, double step);

    fourier_precalculations(const fourier_precalculations &other) :
        _sample_len(other._sample_len),
        _sin_count(other._sin_count),
        _step(other._step),
        _cos_sin_table_len(other._cos_sin_table_len),
        _cos_sin_table(other._cos_sin_table)
    {}

    fourier_precalculations(fourier_precalculations &&other) :
        _sample_len(other._sample_len),
        _sin_count(other._sin_count),
        _step(other._step),
        _cos_sin_table_len(other._cos_sin_table_len),
        _cos_sin_table(std::move(other._cos_sin_table))
    {
        other._sample_len        = 0;
        other._sin_count         = 0;
        other._step              = 0;
        other._cos_sin_table_len = 0;
    }

    fourier_precalculations &operator=(const fourier_precalculations &other) {
        _sample_len        = other._sample_len;
        _sin_count         = other._sin_count;
        _step              = other._step;
        _cos_sin_table_len = other._cos_sin_table_len;
        _cos_sin_table     = other._cos_sin_table;
        return *this;
    }

    fourier_precalculations &operator=(fourier_precalculations &&other) {
        _sample_len        = other._sample_len;
        _sin_count         = other._sin_count;
        _step              = other._step;
        _cos_sin_table_len = other._cos_sin_table_len;
        _cos_sin_table     = std::move(other._cos_sin_table);

        other._sample_len        = 0;
        other._sin_count         = 0;
        other._step              = 0;
        other._cos_sin_table_len = 0;
        return *this;
    }

    inline double get_sample_len() const
        { return _sample_len; }
    inline double get_sin_count() const
        { return _sin_count; }
    inline double get_step() const
        { return _step; }
    inline size_t get_cos_sin_table_len() const
        { return _cos_sin_table_len; }
    inline const fourier_precalculations_single &get_single(int pos) const
        { return _cos_sin_table[pos]; }
    inline const std::vector<fourier_precalculations_single> &get_cos_sin_table() const
        { return _cos_sin_table; }

private:
    // Keep data in this order for initialization.
     double _sample_len;
     double _sin_count;
     double _step;
     size_t _cos_sin_table_len;
     std::vector<fourier_precalculations_single> _cos_sin_table;
};

#endif // LFT_FOURIER_PRECALCULATIONS_HPP_INCLUDED