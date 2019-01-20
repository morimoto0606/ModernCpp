//
// Created by MORIMOTO on 2017/12/30.
//

#include <gtest/gtest.h>
#include "../Source/Enable_if_function.h"
TEST(ene_func_test, unirateral) {
    double x = 0.2452;
    double actual = ene::cva_func<ene::uniraeral>(x);
    EXPECT_DOUBLE_EQ(-x, actual);
}

TEST(ene_func_test, birateral) {
    double x = 0.4542;
    double actual = ene::cva_func<ene::birateral>(x);
    EXPECT_DOUBLE_EQ(x, actual);
}
