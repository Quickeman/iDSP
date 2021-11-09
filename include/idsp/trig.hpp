#ifndef IDSP_TRIG_H
#define IDSP_TRIG_H

#include "maths.hpp"

namespace idsp {

/** Namespace for imported exact trig functions.
 * Mainly imported from STL. */
namespace exact {

using std::sin;
using std::cos;
using std::tan;

using std::sinh;
using std::cosh;
using std::tanh;

} // namespace exact


/** Namespace for fast approximations of trig functions. */
namespace fast {

/** Padé approximant of the sine function. */
template<class T,
std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
constexpr T sin(T x) {
    const auto x2 {x * x};
    const auto num {-x * (-(T)11511339840.0 + x2 * ((T)1640635920.0 + x2 * (-(T)52785432.0 + x2 * (T)479249.0)))};
    const auto den {(T)11511339840.0 + x2 * ((T)277920720.0 + x2 * ((T)3177720.0 + x2 * (T)18361.0))};
    return num / den;
}

/** Padé approximant of the cosine function. */
template<class T,
std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
constexpr T cos(T x) {
    const auto x2 {x * x};
    const auto num {-(-(T)39251520.0 + x2 * ((T)18471600.0 + x2 * (-(T)1075032.0 + (T)14615.0 * x2)))};
    const auto den {(T)39251520.0 + x2 * ((T)1154160.0 + x2 * ((T)16632.0 + x2 * (T)127.0))};
    return num / den;
}

/** Padé approximant of the tangent function. */
template<class T,
std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
constexpr T tan(T x) {
    const auto x2 {x * x};
    const auto num {x * (-(T)135135.0 + x2 * ((T)17325.0 + x2 * (-(T)378.0 + x2)))};
    const auto den {-(T)135135.0 + x2 * ((T)62370.0 + x2 * (-(T)3150.0 + (T)28.0 * x2))};
    return num / den;
}


/** Padé approximant of the hyperbolic sine function. */
template<class T,
std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
constexpr T sinh(T x) {
    const auto x2 {x * x};
    const auto num {-x * ((T)11511339840.0 + x2 * ((T)1640635920.0 + x2 * ((T)52785432.0 + x2 * (T)479249.0)))};
    const auto den {-(T)11511339840.0 + x2 * ((T)277920720.0 + x2 * (-(T)3177720.0 + x2 * (T)18361.0))};
    return num / den;
}

/** Padé approximant of the hyperbolic cosine function. */
template<class T,
std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
constexpr T cosh(T x) {
    const auto x2 {x * x};
    const auto num {-((T)39251520.0 + x2 * ((T)18471600.0 + x2 * ((T)1075032.0 + (T)14615.0 * x2)))};
    const auto den {-(T)39251520.0 + x2 * ((T)1154160.0 + x2 * (-(T)16632.0 + (T)127.0 * x2))};
    return num / den;
}

/** Padé approximant of the hyperbolic tangent function. */
template<class T,
std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
constexpr T tanh(T x) {
    const auto x2 {x * x};
    const auto num {x * ((T)135135.0 + x2 * ((T)17325.0 + x2 * ((T)378.0 + x2)))};
    const auto den {(T)135135.0 + x2 * ((T)62370.0 + x2 * ((T)3150.0 + (T)28.0 * x2))};
    return num / den;
}

} // namespace fast
} // namespace idsp

#endif
