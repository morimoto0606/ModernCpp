//
// Created by MORIMOTO on 2017/12/17.
//

#include <gtest/gtest.h>
#include "../Source/VariousOverload.h"
using testing::Test;

namespace overload {
    TEST(VariousOverload, enable_if)
    {
        int a = 0;
        overload::f(a);
        double b = 3.4;
        overload::f(a);
        std::vector<int> c;
        overload::f(c);
    }

    TEST(VariousOverload, enable_hogefuga)
    {
        Hoge hoge;
        auto actual = enable_hogefuga(hoge);
        EXPECT_EQ("hoge", actual);

        Fuga fuga;
        actual = enable_hogefuga(fuga);
        EXPECT_EQ("fuga", actual);
    }
    
    TEST(VariousOverload, classFunc)
    {
        int a = 3;
        overload::X b;
        overload::Y c;
        overload::classFunc(a);
        overload::classFunc(b);
        overload::classFunc(c);
    }
    
    TEST(VariousOverload, Crtp)
    {
        overload::Derived d;
        overload::crtpFunc(d);
    }
    
    TEST(VariousOverload, TagDispatch) {
        overload::X1 x1;
        overload::X2 x2;
        func(std::move(x1));
        func(std::move(x2));
    }
    
    TEST(VariousOverload, common_func) {
        auto v = overload::common_func(static_cast<int>(3), -0.1);
    }
}

