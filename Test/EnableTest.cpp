//
// Created by MORIMOTO on 2017/12/16.
//

#include <gtest/gtest.h>
#include "../Source/enable_if.h"
namespace enable_test {
    using testing::Test;
    
    TEST(enable_test, size) {
        std::vector<double> vec(5);
    }
    
    TEST(enable_test, Person)
    {
        std::string s = "nori";
        enable::Person p1(s);
        enable::Person p2("papa");
        enable::Person p3(p1);
        enable::Person p4(std::move(p1));
    }
    
    TEST(enable_test, SpecialMemberFunc) {
        std::cout << "enable test start !" << std::endl;
        //enable::C<int> hoge;
        enable::C1 c1;
        enable::C1 z1(c1);
        enable::C1 y1{c1};
        
        enable::C2 c2;
        enable::C2 y2(c2);
        enable::C2 z2{c2};
        //enable::C<double> huga();
        //auto d = huga;
    }
}
