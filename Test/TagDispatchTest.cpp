//
// Created by MORIMOTO on 2017/12/19.
//
#include <gtest/gtest.h>
#include "../Source/TagDispatch.h"
#include <vector>
#include <list>
#include <iostream>

namespace tagdipatch {
   TEST(tagdipatch, tag_dispatch)
    {
        double x = 2.5;
        double actual = tag::calc_cva(
        x, tag::unirateral_type{});
        EXPECT_DOUBLE_EQ(2.0 * x, actual);
        
        actual = tag::calc_cva(
        x, tag::birateral_type{});
        EXPECT_DOUBLE_EQ(-x, actual);
    }
}
