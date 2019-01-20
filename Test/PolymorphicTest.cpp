//
// Created by MORIMOTO on 2017/12/30.
//

#include <gtest/gtest.h>
#include <boost/timer.hpp>
#include "../Source/Polymorphism.h"

TEST(Poly, test) {
    poli::f_inheritence(poli::Derived1Test{});
    poli::f_crtp(poli::Derived2Test{});
    poli::f_enable<poli::typeTest>();
    poli::f_tag<poli::tag_test>();
    poli::f_traits<poli::typeTest>();
}

TEST(Poly, polymorphismTimComparison) {
    boost::timer timer;
    std::size_t size = 1e1;
   
    std::cout << "CRTP" << std::endl;
    timer.restart();
    for (std::size_t i = 0; i < size; ++i) {
        poli::f_crtp(poli::Derived2{});
    }
    std::cout << timer.elapsed() << std::endl;
    
    std::cout << "enable_if" << std::endl;
    timer.restart();
    for (std::size_t i = 0; i < size; ++i) {
        poli::f_enable<poli::type>();
    }
    std::cout << timer.elapsed() << std::endl;
    
    std::cout << "polymorphic" << std::endl;
    timer.restart();
    for (std::size_t i = 0; i < size; ++i) {
        poli::f_inheritence(poli::Derived1{});
    }
    std::cout << timer.elapsed() << std::endl;
    
    std::cout << "tag dispatch" << std::endl;
    timer.restart();
    for (std::size_t i = 0; i < size; ++i) {
        poli::f_tag<poli::tag1>();
    }
    std::cout << timer.elapsed() << std::endl;
    
    std::cout << "traits" << std::endl;
    timer.restart();
    for (std::size_t i = 0; i < size; ++i) {
        poli::f_traits<poli::tag1>();
    }
    std::cout << timer.elapsed() << std::endl;
}

