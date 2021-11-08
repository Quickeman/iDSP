#include "trig.hpp"

#include "unit_test_framework.h"

int main() {
    constexpr auto testVal {0.01};
    constexpr auto errDelta {1e-6};

    // sinh
    test::check(idsp::fast::sinh(testVal), std::sinh(testVal), errDelta, "sinh test 1");

    // cosh
    test::check(idsp::fast::cosh(testVal), std::cosh(testVal), errDelta, "cosh test 1");

    // tanh
    test::check(idsp::fast::tanh(testVal), std::tanh(testVal), errDelta, "tanh test 1");
}