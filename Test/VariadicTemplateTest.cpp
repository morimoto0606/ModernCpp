//
// Created by MORIMOTO on 2017/11/12.
//

#include <gtest/gtest.h>
#include "../Source/VariadicTemplate.h"
#include <vector>
#include <numeric>
#include <type_traits>

namespace test {
    TEST(VariadicTemplateTest, sum)
    {
        std::vector<int> a{1,4,6};
        int expected = std::accumulate(
        a.cbegin(), a.cend(), 0);
        
        int actual = variadic::sum(a[0], a[1], a[2]);
        EXPECT_EQ(expected, actual);
    }
    
    TEST(VariadicTemplateTest, sum2)
    {
        auto s = variadic::sum(-4, 3.5f, 9u, -2.6);
        auto expected = -4.0 + 3.5 + 9.0 - 2.6;
        EXPECT_EQ(expected, s);
    }
    
    TEST(VariadicTemplateTest, commonType)
    {
        double x = 1.4;
        double y = 3.1;
        auto type = std::is_same<decltype(x), decltype(y)>::value;
        auto type2 = std::is_same<decltype(x), std::common_type_t<
        decltype(x), decltype(y)>>::value;
        bool tyep = std::is_same<decltype(x),
            std::common_type<decltype(x)>::type >::value;
    }

    TEST(VariadicTemplateTest, minimum)
    {
        auto v = variadic::minimum(-7, 4.6f, 5u, -2.46);
    }
    
    TEST(VariadicTemplateTest, FuncOfUnipoTest)
    {
        variadic::Derived d;
        std::vector<std::unique_ptr<variadic::Base>> baseVec {
        };
    }
    
    TEST(VariadicTemplateTest, new_sum2)
    {
        int d1 = 2;
        int d2 = -2;
        int d3 = 4;
        auto d = variadic::sum2(d1, d2, d3);
        //EXPECT_DOUBLE_EQ(d1 + d2 + d3, d);
    }
    
    TEST(VariadicTemplateTest, mult)
    {
        double x1 = 1.2;
        double x2 = 3.4;
        double x3 = 4.5;
        auto d = variadic::mult(x1, x2, x3);
        EXPECT_DOUBLE_EQ(x1 * x2 * x3, d);
    }
    
}

