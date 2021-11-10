#ifndef IDSP_FILTER_H
#define IDSP_FILTER_H

#include "types.hpp"
#include "maths.hpp"
#include "trig.hpp"

#include <type_traits>
#include <array>
#include <algorithm>
#include <complex>

namespace idsp {

/** Simple multimode filter using an Euler solver. */
template<class T = FloatT>
class EulerFilter {
public:
    /** Sets the filter to initial conditions. */
    EulerFilter() {
        reset();
        setCutoff(0.1);
    }

    ~EulerFilter() = default;

    /** Sets the filter to initial conditions. */
    void reset() {
        xs = 0.0;
        ys = 0.0;
    }

    /** Sets the cutoff frequency of the filter.
     * @param f normalised cutoff frequency. */
    void setCutoff(T f) {
        c = 1.0 / (num::pi * f);
    }

    /** Filters the input sample @a in.
     * Access the filter output with @ref lowpass and @ref highpass. */
    void process(T in) {
        const auto y = (in + xs - ys * (1.0 - c)) / (1.0 + c);
        xs = in;
        ys = y;
    }

    /** @return the filter's lowpass output. */
    inline T lowpass() {
        return ys;
    }
    /** @return the filter's highpass output. */
    inline T highpass() {
        return xs - ys;
    }

private:
    /** Input state. */
    T xs;
    /** Output state. */
    T ys;

    /** Normalised cutoff frequency. */
    T c;
};


/** State variable / Chamberlin multimode filter. */
template<class T = FloatT>
class StateVariableFilter {
public:
    StateVariableFilter() {
        reset();
    }

    ~StateVariableFilter() = default;

    /** Resets the filter to initial conditions. */
    void reset() {
        yH = yB = yL = yN = 0.0;
    }

    /** Sets the filter's parameters.
     * @param freq normalised cutoff frequency.
     * @param damp filter damping ratio. */
    void setParams(T freq, T damp) {
        f = 2.0 * fast::sin(num::pi * freq);
        q = damp;
    }

    /** Filters the input sample @a in.
     * Access the filter output with @ref lowpass, @ref bandpass, @ref highpass
     * and @ref notch. */
    void process(FloatT in) {
        yH = in - yL - (q * yB);
        yB = (f * yH) + yB;
        yL = (f * yB) + yL;
        yN = yH + yL;
    }

    /** @return the filter's lowpass output. */
    inline T lowpass() const {
        return yL;
    }
    /** @return the filter's bandpass output. */
    inline T bandpass() const {
        return yB;
    }
    /** @return the filter's highpass output. */
    inline T highpass() const {
        return yH;
    }
    /** @return the filter's notch output. */
    inline T notch() const {
        return yN;
    }

private:
    T yH;
    T yB;
    T yL;
    T yN;

    T f;
    T q;
};


/** Base class for a biquad filter. */
template<class T = FloatT>
class _BiquadFilter {
private:
    /** Filter order. */
    static constexpr int order {2};

public:
    /** Sets the filter to initial conditions. */
    _BiquadFilter() {
        reset();
    }

    virtual ~_BiquadFilter() = default;

    /** Resets the filter to initial conditions. */
    void reset() {
        inB.fill(0.0);
        outB.fill(0.0);
    }

    /** Manually sets the filter coefficients. */
    void setCoefficients(const std::array<T, order+1>& poles, const std::array<T, order+1>& zeros) {
        std::copy(poles.begin(), poles.end(), pole.begin());
        std::copy(zeros.begin(), zeros.end(), zero.begin());
    }

    /** Sets the filter parameters.
     * Calculates the appropriate filter coefficients and calls @ref setCoefficients. */
    virtual void setParams(T freq, T param) = 0;

    /** Filters a signal.
     * @param in input sample.
     * @return filtered sample. */
    T process(T in) {
        const T q {0.0 - (pole[0] * in) - (pole[1] * state[0]) - (pole[2] * state[1])};
        const T out {(zero[0] * q) + (zero[1] * state[0]) + (zero[2] * state[1])};
        std::copy(state.begin() + 1, state.end(), state.begin());
        state.back() = q;
        return out;
    }

    /** Computes the transfer function of the filter.
     * @param freq normalised frequency to calculate for.
     * @return transfer function as a std::complex object. */
    std::complex<T> transferFunction(T freq) {
        std::complex<T> zeroSum(zero[0], 0.0);
        std::complex<T> poleSum(pole[0], 0.0);
        for (int i {1}; i < order; i++) {
            T p = -static_cast<T>(i) * freq * 2.0 * num::pi;
            std::complex<T> z(fast::cos(p), fast::sin(p));
            zeroSum += zero[i] * z;
            poleSum += pole[i] * z;
        }
        return zeroSum / poleSum;
    }

    /** Computes the frequency response at normalised frequency @a freq. */
    T frequencyResponse(T freq) {
        return std::abs(transferFunction(freq));
    }

    /** Computes the phase response at normalised frequency @a freq. */
    T phaseResponse(T freq) {
        return std::arg(transferFunction(freq));
    }

private:
    /** Pole filter coefficients. */
    std::array<T, order+1> pole;
    /** Zero filter coefficients. */
    std::array<T, order+1> zero;

    /** Filter state buffer. */
    std::array<T, order> state;
};

}

#endif
