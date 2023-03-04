// log_transform_freq.hpp
// ----------------------
// Class for general stats for a transform, including overall stats and per-note stats

#ifndef LFT_LOG_TRANSFORM_STATS_HPP_INCLUDED
#define LFT_LOG_TRANSFORM_STATS_HPP_INCLUDED

#include <map>

#include "log_transform_freq_stats.hpp"

// General stats for a transform, including overall stats and per-note stats
class log_transform_stats {
public:
    // Constructors
    log_transform_stats()
        : _freq_stats() {}
    log_transform_stats(const std::map<double, log_transform_freq_stats> &freq_stats)
        : _freq_stats(freq_stats) {}
    log_transform_stats(std::map<double, log_transform_freq_stats> &&freq_stats)
        : _freq_stats(std::move(freq_stats)) {}

    log_transform_stats(const log_transform_stats &other) :
        _freq_stats(other._freq_stats) {}
    log_transform_stats(log_transform_stats &&other) :
        _freq_stats(std::move(other._freq_stats)) {}

    // Operator overloads
    log_transform_stats &operator=(const log_transform_stats &other) {
        _freq_stats = other._freq_stats;
        return *this;
    }

    log_transform_stats &operator=(log_transform_stats &&other) {
        _freq_stats = std::move(other._freq_stats);
        return *this;
    }

    // Getters and setters
    inline const std::map<double, log_transform_freq_stats> &get_freq_stats() const
        { return _freq_stats; }

private:
     std::map<double, log_transform_freq_stats> _freq_stats;
};

#endif // LFT_LOG_TRANSFORM_STATS_HPP_INCLUDED
