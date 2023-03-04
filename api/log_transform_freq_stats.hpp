// log_transform_freq_stats.hpp
// ----------------------------
// Stats for an individual frequency/note of a transform.

#ifndef LFT_LOG_TRANSFORMS_FREQ_STATS_HPP_INCLUDED
#define LFT_LOG_TRANSFORMS_FREQ_STATS_HPP_INCLUDED

#include <chrono>

// Stats for an individual frequency/note of a transform.
class log_transform_freq_stats {
public:
    // Constructors
    log_transform_freq_stats(double sample_size, std::chrono::milliseconds sample_duration, double sample_step)
        : sample_size(sample_size), sample_duration(sample_duration), sample_step(sample_step)
    {}

    log_transform_freq_stats(const log_transform_freq_stats &other)
        { *this = other; }
    log_transform_freq_stats(log_transform_freq_stats &&other)
        { *this = other; }

    // Operator overloads
    log_transform_freq_stats &operator=(const log_transform_freq_stats &other) {
        sample_size = other.sample_size;
        sample_duration = other.sample_duration;
        sample_step = other.sample_step;
        return *this;
    }

    log_transform_freq_stats &operator=(log_transform_freq_stats &&other) {
        sample_size = other.sample_size;
        sample_duration = other.sample_duration;
        sample_step = other.sample_step;

        other.sample_size = 0;
        other.sample_duration = std::chrono::milliseconds();
        other.sample_step = 0;
        return *this;
    }

    // Getters and setters
    inline double get_sample_size() const
        { return sample_size; }
    inline std::chrono::milliseconds get_sample_duration() const
        { return sample_duration; }
    inline double get_sample_step() const
        { return sample_step; }

private:
    double sample_size;
    std::chrono::milliseconds sample_duration;
    double sample_step;
};

#endif // LFT_LOG_TRANSFORMS_FREQ_STATS_HPP_INCLUDED
