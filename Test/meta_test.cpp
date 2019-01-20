//
// Created by MORIMOTO on 2017/09/14.
//
#include <gtest/gtest.h>
#include "../Source/meta.h"

using ::testing::Test;
namespace meta_test {
    TEST(meta_test, meta_function) {
        int val = meta::hoge<3>::value;
        EXPECT_EQ(val, 3);

        int val2 = meta::hoge2<3>::value;
        EXPECT_EQ(val2, 3);
    }
    TEST(meta_test, increment) {
        int n = meta::increment<3>::value;
        EXPECT_EQ(n, 4);
    }
    TEST(meta_test, factorial) {
        int n = meta::factorial<10>::value;
        int expected = 1;
        for(int i = 1; i < 11; ++i) {
            expected *= i;
        }
        EXPECT_EQ(expected, n);
    }
    TEST(meta_test, square) {
        int n = meta::square<10>::value;
        EXPECT_EQ(100, n);
    }
    TEST(meta_test, power) {
        int n = meta::power<10, 3>::value;
        EXPECT_EQ(n, 1000);
    }
    TEST(meta_test, pow) {
        int n = meta::pow(10, 3);
        EXPECT_EQ(n, 1000);
    }
    TEST(meta_test, identify) {
        meta::identify<int>::type value;
        value = 3;
    }
    TEST(meta_test, add_ptr) {
        int value = 3;
        meta::add_pointer<int>::type t = &value;
        using result = meta::add_pointer<int>::type;
        result a = &value;
        value = 4;
        EXPECT_EQ(*a, 4);
    }
    TEST(meta_test, add_const_lval) {
        int value = 3;
        meta::add_const_lvalue_reference<int>::type t = value;
    }
    TEST(meta_test, remove_const ) {
        const int value = 3;
        meta::remove_const<decltype(value)>::type n = 3;
        n = 4;
        decltype(value) m = 3;
    }
    TEST(meta, cmpiletime_if){
        double d = 0.454;
        meta::if_<true, double, int>::type a = 3.0;
        meta::if_<false, double, int>::type b = d;
        EXPECT_EQ(0, b);
    }
    TEST(meta, is_even) {
        std::vector<int> v {1, 2, 3, 4};
        int found = *std::find_if(std::begin(v), std::end(v),
                     meta::is_even());
        EXPECT_EQ(found, 2);
        bool b = meta::is_evenmeta<3>::value;
    }

    TEST(meta, compile_if) {
        auto c = meta::if_c<meta::is_evenmeta<2>::value, int, long>::type();
        meta::ifmeta_<meta::is_evenmeta<3>, int, long>::type value;
    }

    //meta function
    TEST(meta, add_pointer) {
        using result = decltype(meta::add_pointer2<int>());
        int a = 3;
        result b = &a;
        a = 4;
        EXPECT_EQ(*b, 4);
    }
    TEST(meta, add_pointer3) {
        using result = decltype(
        meta::add_pointer3(std::declval<int>()));
        int a = 3;
        result b = &a;
        a = 4;
        EXPECT_EQ(*b, 4);
        
        using newtype = decltype(
        meta::add_pointer3(DECLVAL(int)));
        newtype c = b;
        EXPECT_EQ(*c, a);
    }
    
    TEST(meta, add_pinters) {
        using result = decltype(
            meta::add_pointers(
            std::declval<int>(),
            meta::int_<1>())
        );
        int a = 3;
        result b = &a;
        a = 4;
        EXPECT_EQ(*b, 4);
    }
    
    
    TEST(meta, TypeTest) {
        meta::AType a;
        a.getNum();
        
        meta::BType b;
        
        meta::Hoge hoge(a);
        meta::Hoge hoge2(b);
        
        std::cout << meta::num(b) << std::endl;
    }

}
