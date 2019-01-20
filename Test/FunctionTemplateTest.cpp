//
// Created by MORIMOTO on 2017/12/17.
//

#include <gtest/gtest.h>
#include "../Source/FunctionTemplate.h"
#include <iostream>
using testing::Test;
namespace Func {
    TEST(FuncTest, max) {
        auto d = func::max(7.1, 3);
        std::cout << d << std::endl;
    }
}
