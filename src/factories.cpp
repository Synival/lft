#include <cstring>
#include <stdexcept>

#include "../api/log_transformer_filter_i.hpp"
#include "../api/log_transformer_filter_none.hpp"
#include "../api/log_transformer_filter_hypot.hpp"
#include "../api/log_transformer_filter_normalize.hpp"
#include "../api/log_transformer_filter_loudness.hpp"
#include "../api/log_transformer_filter_linearize.hpp"
#include "../api/log_transformer_filter_partial_normalize.hpp"

#include "../api/log_transformer_i.hpp"
#include "../api/log_transformer_fourier.hpp"
#include "../api/log_transformer_variable_fourier.hpp"

#include "../api/factories.hpp"

static constexpr const char *LOG_TRANSFORMER_FILTER_NONE      = "none";
static constexpr const char *LOG_TRANSFORMER_FILTER_HYPOT     = "hypot";
static constexpr const char *LOG_TRANSFORMER_FILTER_NORMALIZE = "normalize";
static constexpr const char *LOG_TRANSFORMER_FILTER_LOUDNESS  = "loudness";
static constexpr const char *LOG_TRANSFORMER_FILTER_LINEARIZE = "linearize";
static constexpr const char *LOG_TRANSFORMER_FILTER_PARTIAL_NORMALIZE   = "partial_normalize";

static constexpr const char *LOG_TRANSFORMER_FOURIER          = "fourier";
static constexpr const char *LOG_TRANSFORMER_VARIABLE_FOURIER = "variable_fourier";

std::unique_ptr<log_transformer_filter_i> factory_log_transformer_filter::create(const char *name) const
{
    if (name == nullptr)
        throw std::invalid_argument(std::string(__PRETTY_FUNCTION__) + ": 'name' is nullptr");

    if (std::strcmp(name, LOG_TRANSFORMER_FILTER_NONE) == 0)
        return std::make_unique<log_transformer_filter_none>();
    else if (std::strcmp(name, LOG_TRANSFORMER_FILTER_HYPOT) == 0)
        return std::make_unique<log_transformer_filter_hypot>();
    else if (std::strcmp(name, LOG_TRANSFORMER_FILTER_NORMALIZE) == 0)
        return std::make_unique<log_transformer_filter_normalize>();
    else if (std::strcmp(name, LOG_TRANSFORMER_FILTER_LOUDNESS) == 0)
        return std::make_unique<log_transformer_filter_loudness>();
    else if (std::strcmp(name, LOG_TRANSFORMER_FILTER_LINEARIZE) == 0)
        return std::make_unique<log_transformer_filter_linearize>();
    else if (std::strcmp(name, LOG_TRANSFORMER_FILTER_PARTIAL_NORMALIZE) == 0)
        return std::make_unique<log_transformer_filter_partial_normalize>();

    // No matching name - throw exception
    throw std::invalid_argument(std::string(__PRETTY_FUNCTION__) + ": unknown type '" + name + "'");
}

const std::vector<const char *> &factory_log_transformer_filter::get_names() const
{
    static const std::vector<const char *> names = {
        LOG_TRANSFORMER_FILTER_NONE,
        LOG_TRANSFORMER_FILTER_HYPOT,
        LOG_TRANSFORMER_FILTER_NORMALIZE,
        LOG_TRANSFORMER_FILTER_LOUDNESS,
        LOG_TRANSFORMER_FILTER_LINEARIZE,
        LOG_TRANSFORMER_FILTER_PARTIAL_NORMALIZE,
    };
    return names;
}

factory_log_transformer::factory_log_transformer(const signal_profile &profile, double lowest_freq, double sin_count, size_t min_size,
    int octave_subdivisions, int octaves
) :
    _profile(profile),
    _lowest_freq(lowest_freq),
    _sin_count(sin_count),
    _min_size(min_size),
    _octave_subdivisions(octave_subdivisions),
    _octaves(octaves)
{}

std::unique_ptr<log_transformer_i> factory_log_transformer::create(const char *name) const
{
    if (name == nullptr)
        throw std::invalid_argument(std::string(__PRETTY_FUNCTION__) + ": 'name' is nullptr");

    if (std::strcmp(name, LOG_TRANSFORMER_FOURIER) == 0)
        return std::make_unique<log_transformer_fourier>(_profile, _lowest_freq, _sin_count, _octave_subdivisions, _octaves);
    else if (std::strcmp(name, LOG_TRANSFORMER_VARIABLE_FOURIER) == 0)
        return std::make_unique<log_transformer_variable_fourier>(_profile, _lowest_freq, _sin_count, _min_size, _octave_subdivisions, _octaves);

    // No matching name - throw exception
    throw std::invalid_argument(std::string(__PRETTY_FUNCTION__) + ": unknown type '" + name + "'");
}

const std::vector<const char *> &factory_log_transformer::get_names() const
{
    static const std::vector<const char *> names = {
        LOG_TRANSFORMER_FOURIER,
        LOG_TRANSFORMER_VARIABLE_FOURIER,
    };
    return names;
}