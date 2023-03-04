#ifndef LFT_FOURIER_PRECALCULATIONS_SINGLE_HPP_INCLUDED
#define LFT_FOURIER_PRECALCULATIONS_SINGLE_HPP_INCLUDED

class fourier_precalculations_single {
public:
    fourier_precalculations_single(double pos_cos, double neg_sin)
        : _pos_cos(pos_cos), _neg_sin(neg_sin)
    {}

    fourier_precalculations_single(const fourier_precalculations_single &other) :
        _pos_cos(other._pos_cos), _neg_sin(other._neg_sin)
    {}

    fourier_precalculations_single(fourier_precalculations_single &&other) :
        _pos_cos(other._pos_cos), _neg_sin(other._neg_sin)
    {
        other._pos_cos = 0;
        other._neg_sin = 0;
    }

    fourier_precalculations_single &operator=(const fourier_precalculations_single &other) {
        _pos_cos = other._pos_cos;
        _neg_sin = other._neg_sin;
        return *this;
    }

    fourier_precalculations_single &operator=(fourier_precalculations_single &&other) {
        _pos_cos = other._pos_cos;
        _neg_sin = other._neg_sin;

        other._pos_cos = 0;
        other._neg_sin = 0;
        return *this;
    }

    inline double get_pos_cos() const
        { return _pos_cos; }
    inline double get_neg_sin() const
        { return _neg_sin; }

private:
    double _pos_cos;
    double _neg_sin;
};

#endif // LFT_FOURIER_PRECALCULATIONS_SINGLE_HPP_INCLUDED