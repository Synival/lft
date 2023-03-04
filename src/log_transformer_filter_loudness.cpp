#include <map>
#include <cmath>

#include "../api/log_transformer_i.hpp"
#include "../api/transform_results.hpp"

#include "../api/log_transformer_filter_loudness.hpp"

static double get_loudness_for_freq(double freq)
{
    // Table to convert from 1Db to x phon, based on numbers at 40Phon
    // (This is absolutely not how it works IRL. We'd need an extra dimension in the key for Db, which
    //  would give a different phon value. It's NOT simple scaling. Plus, there's absolutely no way to
    //  know the true Db level for any data - it's not coming out of speakers, so it doesn't really apply.)
    static std::map<double, double> _loudness_table {
        std::pair<double, double>(    0,   0.00 ),
        std::pair<double, double>(   20,   0.40 ),
        std::pair<double, double>(   25,   0.42 ),
        std::pair<double, double>(   31.5, 0.45 ),
        std::pair<double, double>(   40,   0.48 ),
        std::pair<double, double>(   50,   0.51 ),
        std::pair<double, double>(   63,   0.54 ),
        std::pair<double, double>(   80,   0.58 ),
        std::pair<double, double>(  100,   0.62 ),
        std::pair<double, double>(  125,   0.66 ),
        std::pair<double, double>(  160,   0.70 ),
        std::pair<double, double>(  200,   0.74 ),
        std::pair<double, double>(  250,   0.79 ),
        std::pair<double, double>(  315,   0.84 ),
        std::pair<double, double>(  400,   0.88 ),
        std::pair<double, double>(  500,   0.92 ),
        std::pair<double, double>(  630,   0.96 ),
        std::pair<double, double>(  800,   0.99 ),
        std::pair<double, double>( 1000,   0.99 ),
        std::pair<double, double>( 1250,   0.95 ),
        std::pair<double, double>( 1600,   0.94 ),
        std::pair<double, double>( 2000,   1.01 ),
        std::pair<double, double>( 2500,   1.09 ),
        std::pair<double, double>( 3150,   1.12 ),
        std::pair<double, double>( 4000,   1.09 ),
        std::pair<double, double>( 5000,   0.99 ),
        std::pair<double, double>( 6300,   0.87 ),
        std::pair<double, double>( 8000,   0.77 ),
        std::pair<double, double>(10000,   0.73 ),
        std::pair<double, double>(12500,   0.77 ),
        std::pair<double, double>(25000,   0.00 )
    };

    // ignore bogus cases.
    if (freq <= 0.00 || freq >= 25000.00)
        return 0.00;

    // do we already have a value for the requested frequency?
    auto f_iter = _loudness_table.find(freq);
    if (f_iter != _loudness_table.end())
        return f_iter->second;

    // we don't have it - use linear interpolation to push a new value.
    auto upper_f_iter = _loudness_table.upper_bound(freq);
    auto lower_f_iter = std::prev(upper_f_iter);

    double freq_low   = lower_f_iter->first;
    double freq_high  = upper_f_iter->first;
    double freq_range = freq_high - freq_low;
    double mag_low    = lower_f_iter->second;
    double mag_high   = upper_f_iter->second;
    double mag_range  = mag_high - mag_low;
    double freq_pos   = (freq - freq_low) / freq_range;
    double mag_freq   = mag_low + (freq_pos * mag_range);

    _loudness_table.insert(std::pair(freq, mag_freq));
    return mag_freq;
}

transform_results<std::complex<double>> log_transformer_filter_loudness::filter_transform_complex(const transform_results<std::complex<double>> &transform) const
{
    // TODO: actually handle this!
    return transform_results<std::complex<double>> { transform };
}

transform_results<double> log_transformer_filter_loudness::filter_transform_real(const transform_results<double> &transform) const
{
    std::map<double, double> new_results { transform.get_results() };
    for (auto i = new_results.begin(); i != new_results.end(); ++i)
        i->second *= get_loudness_for_freq(i->first);
    return transform_results<double> { std::move(new_results) };
}
