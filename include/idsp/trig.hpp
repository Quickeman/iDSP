#ifndef IDSP_TRIG_H
#define IDSP_TRIG_H

#include "maths.hpp"

namespace idsp {
namespace fast {

/** Padé approximant of the hyperbolic sine function. */
template<class T,
std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
constexpr T sinh(T x) {
    const auto x2 {x * x};
    const auto num {-x * (11511339840 + x2 * (1640635920 + x2 * (52785432 + x2 * 479249)))};
    const auto dem {-11511339840.f + x2 * (277920720 + x2 * (-3177720 + x2 * 18361))};
    return num / dem;
}

/** Padé approximant of the hyperbolic cosine function. */
template<class T,
std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
constexpr T cosh(T x) {
    const auto x2 {x * x};
    const auto num {-(T(39251520) + x2 * (T(18471600) + x2 * (T(1075032) + T(14615) * x2)))};
    const auto dem {-T(39251520) + x2 * (T(1154160) + x2 * (T(-16632) + T(127) * x2))};
    return num / dem;
}

/** Padé approximant of the hyperbolic tangent function. */
template<class T,
std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
constexpr T tanh(T x) {
    const auto x2 {x * x};
    return clamp(x * (T(27.0) + x2) / (T(27.0) + (T(9.0) * x2)), T(-1.0), T(1.0));
}

} // namespace fast
} // namespace idsp

#endif
