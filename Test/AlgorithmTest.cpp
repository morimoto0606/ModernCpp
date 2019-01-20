//
// Created by MORIMOTO on 2017/10/22.
//

#include <gtest/gtest.h>
#include "../Source/Algorithm.h"
#include "../Source/GenericProgramming.h"

#include <iostream>
#include <vector>
#include <algorithm>


using testing::Test;

TEST(Alg, stack) {
   std::string input;
   //std::getline(std::cin, input);
   input = "1 2 + 3 4 * -";
   std::stringstream ss(input);
   std::vector<std::string> vec;
   std::copy(std::istream_iterator<std::string>(ss),
             {}, std::back_inserter(vec));
   
   
   for (auto s : vec) {
      std::cout << s << std::endl;
   }
   int result = alg::evaluate(vec);
   std::cout << "result is " << result << std::endl;
   EXPECT_EQ(result, -9);
}