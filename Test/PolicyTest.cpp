//
// Created by MORIMOTO on 2017/12/24.
//

#include <gtest/gtest.h>
#include "../Source/Policy.h"
using testing::Test;
namespace test {
   TEST(Policy, Pring)
    {
        using type1 = policy::print_type1;
        using type2 = policy::print_type2;
        policy::Printer<type1>::print();
        policy::Printer<type2>::print();
    }
}
