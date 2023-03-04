#ifndef LFT_TRANSFORM_RESULTS_HPP_INCLUDED
#define LFT_TRANSFORM_RESULTS_HPP_INCLUDED

#include <map>

template<typename T>
class transform_results {
public:
    transform_results()
        : _results() {}
    transform_results(const std::map<double, T> &results)
        : _results(results) {}
    transform_results(std::map<double, T> &&results)
        : _results(std::move(results)) {}

    transform_results(const transform_results<T> &other) :
        _results(other._results)
    {}

    transform_results(transform_results<T> &&other) :
        _results(std::move(other._results))
    {}

    inline transform_results &operator=(const transform_results<T> &other) {
        _results = other._results;
        return *this;
    }

    inline transform_results &operator=(transform_results<T> &&other) {
        _results = std::move(other._results);
        return *this;
    }

    inline const std::map<double, T> &get_results() const
        { return _results; }

private:
    std::map<double, T> _results;
};

#endif // LFT_TRANSFORM_RESULTS_HPP_INCLUDED