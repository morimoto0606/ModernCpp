//
// Created by MORIMOTO on 2017/11/22.
//

#include <gtest/gtest.h>
#include <iostream>
#include "../Source/RootFinding.h"
#include <cmath>
#include <memory>

using testing::Test;
namespace roottest {
    class RootTest : public testing::Test {
    public:
    };
    
    TEST_F(RootTest, BisectionTest)
    {
        auto f = [](double x){
        return std::log(x)- 3.986;
        };
        const double tolerance = 0.0001;
        auto root = root::bisection(f, 5.0, 0.0, 100.0,
                                    tolerance, 10000);
        std::cout << "root is " << root << std::endl;
        std::cout << "val is " << std::log(root) << std::endl;
        EXPECT_NEAR(0, f(root), tolerance);
    }
    
    TEST_F(RootTest, NewtonRaphson)
    {
        auto f = [](double x) {
            return std::log(x)- 3.986;
        };
        
        auto df = [](double x) {
            return 1.0/x;
        };
        
        const double tolerance = 0.0001;
        auto root = root::newton_raphson(std::move(f),
                                         std::move(df),
                                         0.5, tolerance,
                                         1000);
        std::cout << "root is " << root << std::endl;
        std::cout << "val is " << std::log(root) << std::endl;
        std::cout << f(root) << std::endl;
        EXPECT_NEAR(0, f(root), tolerance);
    }
}
