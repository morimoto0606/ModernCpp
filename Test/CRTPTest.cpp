//
// Created by MORIMOTO on 2017/12/30.
//

#include <gtest/gtest.h>
#include "../Source/CRTP.h"

TEST(crtptest, unirateral) {
    crtp::unirateral hoge{};
    double x = 0.4354;
    double actual = crtp::cva_func(x, hoge);
    EXPECT_DOUBLE_EQ(x, actual);
}


TEST(crtptest, birateral) {
    crtp::birateral hoge{};
    double x = 0.4354;
    double actual = crtp::cva_func(x, hoge);
    EXPECT_DOUBLE_EQ(-x, actual);
}
