#include "maths.hpp"

#include "unit_test_framework.h"

int main() {
    // min
    test::check(idsp::min(0, 3), 0, 0, "min test 1");
    test::check(idsp::min(2.4, 1.2), 1.2, 1e-6, "min test 2");
    test::check(idsp::min(-5.0, 2.0), -5.0, 1e-6, "min test 3");

    // max
    test::check(idsp::max(0, 3), 3, 0, "min test 1");
    test::check(idsp::max(2.4, 1.2), 2.4, 1e-6, "min test 2");
    test::check(idsp::max(-5.0, 2.0), 2.0, 1e-6, "min test 3");

    // clamp
    test::check(idsp::clamp(1, 0, 2), 1, 0, "clamp test 1");
    test::check(idsp::clamp(3.0, 1.0, 2.0), 2.0, 1e-6, "clamp test 2");
    test::check(idsp::clamp(-2.f, -1.2f, 0.f), -1.2f, 1e-6f, "clamp test 3");
    // Test for low limit being less than high limit behaviour
    test::check(idsp::clamp(1.0, 1.5, 0.5), 0.5, 1e-6, "clamp test 4");

    // sgn
    test::check(idsp::sgn(3.0), 1, 0, "sgn test 1");
    test::check(idsp::sgn(-2.f), -1, 0, "sgn test 2");
    test::check(idsp::sgn(0), 0, 0, "sgn test 3");

    // scale
    test::check(idsp::scale(1.0, 0.0, 2.0, 0.0, 1.0), 0.5, 1e-6, "scale test 1");
    test::check(idsp::scale(4, 2, 5, 1, 10), 7, 0, "scale test 2");
    test::check(idsp::scale(-1.f, -2.f, 0.f, -4.f, -2.f), -3.f, 1e-6f, "scale test 3");

    // power
    test::check(idsp::power(0.0, 4), 0.0, 1e-6, "power test 1");
    test::check(idsp::power(5, 3), 125, 0, "power test 2");
    test::check(idsp::power(1.6, 7), 26.8435456, 1e-6, "power test 3");

    // factorial
    test::check(idsp::factorial(5), 120, 0, "factorial test 1");
    test::check(idsp::factorial((uint8_t)3), (uint8_t)6, (uint8_t)0, "factorial test 2");
    test::check(idsp::factorial(0), 1, 0, "factorial test 3");
    // Test negative number behaviour
    try {
        idsp::factorial(-2);
        test::check(false, "factorial test 4");
    }
    catch(const std::invalid_argument& e) {
        test::check(true, "factorial test 4");
    }

    // mod
    test::check(idsp::mod(2.0, 0.3), 0.2, 1e-6, "mod test 1");
    test::check(idsp::mod(-3.0, 1.2), -0.6, 1e-6, "mod test 2");

    // near
    test::check(idsp::near(0.1, 0.1 + 1e-7), "near test 1");
    test::check(idsp::near(10, 8, 3), "near test 2");
    test::check(!idsp::near(2.5f, 2.6f), "near test 3");

    // interpolate (2-point)
    test::check(idsp::interpolate(0.25, 2.4, 1.2), 2.1, 1e-6, "interpolate (2-point) test 1");
    test::check(idsp::interpolate(0.5, 2, 8), 5, 0, "interpolate (2-point) test 2");
    test::check(idsp::interpolate(0.9, -10.f, 0.f), -1.f, 1e-6f, "interpolate (2-point) test 3");

    // interpolate (4-point)
    test::check(idsp::interpolate(0.5, 1., 2., 3., 4.), 2.5, 1e-6, "interpolate (4-point) test 1");
    test::check(idsp::interpolate(0.f, 32., 2., 54., 0.), 2., 1e-6, "interpolate (4-point) test 2");
}