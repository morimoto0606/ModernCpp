//
// Created by MORIMOTO on 2017/11/21.
//
#include <gtest/gtest.h>
#include "../Source/ExpressionTemplate.h"

using testing::Test;
namespace test {
    TEST(ET, vectorsum)
    {
        et::vector<float> x = {1.0, 1.3},
        y = {3.5, 6.3}, z = {5.2, 58}, w(4);
        
        w = x + y + z;
        for (int i = 0; i < x.size(); ++i){
            std::cout << x[i] + y[i] + z[i] << std::endl;
            std::cout << w[i]<< std::endl;
        }
   }
    

}
