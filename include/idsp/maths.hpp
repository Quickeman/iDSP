#ifndef IDSP_MATHS_H
#define IDSP_MATHS_H

#include <type_traits>
#include <cmath>
#include <stdexcept>

namespace idsp {

/** @return the minimum of @a a and @a b. */
template<class T>
constexpr T min(T a, T b) {
    return a > b ? b : a;
}

/** @return the maximum of @a a and @a b. */
template<class T>
constexpr T max(T a, T b) {
    return a > b ? a : b;
}

/** Limits @a x between @a low and @a high. */
template<class T>
constexpr T clamp(T x, T low, T high) {
    return min(max(x, low), high);
}

/** Signum function.
 * @returns 1 for x > 0, -1 for x < 0, and 0 for x = 0. */
template<class T>
constexpr int sgn(T x) {
    return (x > T(0)) - (x < T(0));
}

/** Scales @a x from the range [ @a xMin : @a xMax ] to the range [ @a yMin : @a yMax ]. */
template<class T,
std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
constexpr T scale(T x, T xMin, T xMax, T yMin, T yMax) {
    return yMin + (x - xMin) / (xMax - xMin) * (yMax - yMin);
}

/** Scales @a x from the range [ @a xMin : @a xMax ] to the range [ @a yMin : @a yMax ]. */
template<class T, class Tf = double,
std::enable_if_t<std::is_integral<T>::value, bool> = true>
constexpr T scale(T x, T xMin, T xMax, T yMin, T yMax) {
    return yMin + T(Tf(x - xMin) / Tf(xMax - xMin) * (yMax - yMin));
}

/** @returns x^n.
 * @note this function may be fast for small n but will decrease in performance
 * with increasing n. */
template<class T>
constexpr T power(T x, unsigned int n) {
    auto r {T(1)};
    for (int i {0}; i < n; i++)
        r *= x;
    return r;
}

/** @returns x!. */
template<class T,
std::enable_if_t<std::is_unsigned<T>::value, bool> = true>
constexpr T factorial(T x) {
    constexpr auto one {T(1)};
    auto r {one};
    while (x >= one) {
        r *= x;
        x -= one;
    }
    return r;
}

/** @returns x!.
 * @note Overload provided for convenience of using literal int types, which are
 * generally signed. Negative input numbers are not valid and will throw an
 * error. */
template<class T,
std::enable_if_t<std::is_integral<T>::value && std::is_signed<T>::value, bool> = true>
constexpr T factorial(T x) {
    if (x < 0)
        throw std::invalid_argument("idsp::factorial: cannot give factorial of negative number.");
    return factorial(static_cast<typename std::make_unsigned<T>::type>(x));
}

/** @returns the modulo of @a a and @a b, that is a % b. */
template<class T, class Ti = intmax_t,
std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
constexpr T mod(T x, T y) {
    return x - (y * T(Ti(x/y)));
}

/** @returns `true` if the difference between @a a and @a b is less than or
 * equal to @a delta. */
template<class T>
constexpr bool near(T a, T b, T delta = T(1e-6)) {
    return std::abs(a - b) <= delta;
}

/** Two-point linear interpolation.
 * Interpolates between @a a and @a b proportionally to @a x. */
template<class T>
constexpr T interpolate(T x, T a, T b) {
    return a + ((b - a) * x);
}

/** Two-point linear interpolation.
 * Interpolates between @a a and @a b proportionally to @a x.
 * This overload allows for data that is not the same type as the fractional
 * parameter. */
template<class Ti, class Td,
std::enable_if_t<std::is_floating_point<Ti>::value && !std::is_same<Ti, Td>::value && std::is_convertible<Td, Ti>::value, bool> = true>
constexpr Td interpolate(Ti x, Td a, Td b) {
    const auto ai {static_cast<Ti>(a)};
    const auto r {ai + ((Ti(b) - ai) * x)};
    return static_cast<Td>(r);
}

/** Four-point interpolation.
 * Interpolates between @a b and @a c proportionally to @a x, where @a a is the
 * value before @a b and @a d is the value after @a c in the sequence. */
template<class T>
constexpr T interpolate(T x, T a, T b, T c, T d) {
    return b + x * ((c - b) - T(0.1666667) * (T(1.0) - x) * ((d - a - T(3.0)*(c - b)) * x + (d + T(2.0)*a - T(3.0)*b)));
}

/** Four-point interpolation.
 * Interpolates between @a b and @a c proportionally to @a x, where @a a is the
 * value before @a b and @a d is the value after @a c in the sequence.
 * This overload allows for data that is not the same type as the fractional
 * parameter. */
template<class Ti, class Td,
std::enable_if_t<std::is_floating_point<Ti>::value && !std::is_same<Ti, Td>::value && std::is_convertible<Td, Ti>::value, bool> = true>
constexpr Td interpolate(Ti x, Td a, Td b, Td c, Td d) {
    const auto ai {static_cast<Ti>(a)};
    const auto bi {static_cast<Ti>(b)};
    const auto ci {static_cast<Ti>(c)};
    const auto di {static_cast<Ti>(d)};
    const auto r {bi + x * ((ci - bi) - Ti(0.1666667) * (Ti(1.0) - x) * ((di - ai - Ti(3.0)*(ci - bi)) * x + (di + Ti(2.0)*ai - Ti(3.0)*bi)))};
    return static_cast<Td>(r);
}

} // namespace idsp

#endif
