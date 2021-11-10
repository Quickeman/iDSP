#include "idsp/trig.hpp"

#include "unit_test_framework.h"

int main() {
    constexpr auto testVal {0.5};
    constexpr auto errDelta {1e-6};

    // sin
    test::check(idsp::exact::sin(testVal) == std::sin(testVal), "sin test 1");
    test::check(idsp::fast::sin(testVal), std::sin(testVal), errDelta, "sin test 2");

    // cos
    test::check(idsp::exact::cos(testVal) == std::cos(testVal), "cos test 1");
    test::check(idsp::fast::cos(testVal), std::cos(testVal), errDelta, "cos test 2");

    // tan
    test::check(idsp::exact::tan(testVal) == std::tan(testVal), "tan test 1");
    test::check(idsp::fast::tan(testVal), std::tan(testVal), errDelta, "tan test 2");


    // sinh
    test::check(idsp::exact::sinh(testVal) == std::sinh(testVal), "sinh test 1");
    test::check(idsp::fast::sinh(testVal), std::sinh(testVal), errDelta, "sinh test 2");

    // cosh
    test::check(idsp::exact::cosh(testVal) == std::cosh(testVal), "cosh test 1");
    test::check(idsp::fast::cosh(testVal), std::cosh(testVal), errDelta, "cosh test 2");

    // tanh
    test::check(idsp::exact::tanh(testVal) == std::tanh(testVal), "tanh test 1");
    test::check(idsp::fast::tanh(testVal), std::tanh(testVal), errDelta, "tanh test 2");
}