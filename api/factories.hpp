#ifndef LFT_LOG_FACTORIES_HPP_INCLUDED
#define LFT_LOG_FACTORIES_HPP_INCLUDED

#include <vector>
#include <memory>

#include "common.hpp"

template<typename T>
class factory_i {
    LFT_DELETE_ALL_IMPLICIT_COPY_CONSTRUCTORS_AND_ASSIGNMENT_OPERATORS(factory_i);
public:
    factory_i() {}

    virtual std::unique_ptr<T> create(const char *name) const = 0;
    virtual const std::vector<const char *> &get_names() const = 0;
};

class log_transformer_filter_i;
class log_transformer_i;
class signal_profile;

class LFT_API factory_log_transformer_filter : public factory_i<log_transformer_filter_i> {
    LFT_DELETE_ALL_IMPLICIT_COPY_CONSTRUCTORS_AND_ASSIGNMENT_OPERATORS(factory_log_transformer_filter);
public:
    factory_log_transformer_filter() {}

    virtual std::unique_ptr<log_transformer_filter_i> create(const char *name) const override;
    virtual const std::vector<const char *> &get_names() const override;
};

class LFT_API factory_log_transformer : public factory_i<log_transformer_i> {
    LFT_DELETE_ALL_IMPLICIT_CONSTRUCTORS_AND_ASSIGNMENT_OPERATORS(factory_log_transformer);
public:
    factory_log_transformer(const signal_profile &profile, double lowest_freq, double sin_count, size_t min_size,
        int octave_subdivisions, int octaves);

    virtual std::unique_ptr<log_transformer_i> create(const char *name) const override;
    virtual const std::vector<const char *> &get_names() const override;

private:
    const signal_profile &_profile;
    const double _lowest_freq;
    const double _sin_count;
    const size_t _min_size;
    const int _octave_subdivisions;
    const int _octaves;
};

#endif // LFT_LOG_FACTORIES_HPP_INCLUDED