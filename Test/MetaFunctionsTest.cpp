//
// Created by MORIMOTO on 2017/12/23.
//

#include <gtest/gtest.h>
#include "../Source/meta_functions.h"
#include <tuple>
#include <vector>
#include <list>
#include <algorithm>
#include <iostream>

using testing::Test;
namespace test {
   TEST(MetaFunctionsTest, is_pointer)
    {
        EXPECT_TRUE(meta_functions::is_pointer_v<int*>);
        EXPECT_FALSE(meta_functions::is_pointer_v<int>);
    }
    
    TEST(MetaFunctionsTest, is_vector)
    {
        EXPECT_TRUE(meta_functions::is_vector<std::vector<int>>::value);
        EXPECT_FALSE(meta_functions::is_vector_v<int>);
    }
    
    TEST(MetaFunctionsTest, is_int)
    {
        EXPECT_TRUE(meta_functions::is_int_v<int>);
        EXPECT_FALSE(meta_functions::is_int_v<double>);
    }
    
    TEST(MetaFunctionsTest, f1)
    {
        int x;
        double y;
        meta_functions::f1(x);
        meta_functions::f1(y);
    }
    
    TEST(MetaFunctionTest, has_iterator1)
    {
        EXPECT_TRUE(
        meta_functions::has_iterator1<
        std::vector<double>>::value);
        
        EXPECT_FALSE(
        meta_functions::has_iterator1_v<double>);
    }
    
    TEST(MetaFunctionsTest, has_iterator2)
    {
        EXPECT_TRUE(
        meta_functions::has_iterator2_v<std::vector<int>>);
    }
    
    TEST(MetaFunctionsTest, has_iterator3)
    {
        EXPECT_TRUE(
        meta_functions::has_iterator3_v<std::vector<int>>);
        EXPECT_FALSE(
        meta_functions::has_iterator3_v<int>);
    }
    
    TEST(MetaFunctionsTest, has_value) {
        struct Hoge {
            int value;
        };
        struct Fuga {
            int val;
        };
        EXPECT_TRUE(
        meta_functions::has_value_v<std::false_type>);
        EXPECT_TRUE(
        meta_functions::has_value_v<Hoge>);
        EXPECT_FALSE(
        meta_functions::has_value_v<Fuga>);
    }
    
    TEST(MetaFunctionsTest, has_f)
    {
        struct Hoge {
           double f() const {
               return 0.9;
           }
        };
        EXPECT_FALSE(meta_functions::has_f_v<int>);
        EXPECT_TRUE(meta_functions::has_f_v<Hoge>);
    }
    
    TEST(MetaFunctionsTest, has_member)
    {
        class Hoge {
        public:
            void hoge() const {}
        };
        
        class Fuga {
            //publicならOK　privateだとFalse
        public:
            int hoge = 0;
        };
        
        EXPECT_TRUE(meta_functions::has_member_v<Hoge>);
        EXPECT_TRUE(meta_functions::has_member_v<Fuga>);
        EXPECT_FALSE(meta_functions::has_member_v<float >);
    }
    
    TEST(MetaFunctionsTest, is_assignble)
    {
        int x;
        int y = 3;
        x = 3;
        std::cout << x;
        class Hoge {
        public:
            Hoge& operator =(const Hoge& other) = delete;
        };
        EXPECT_TRUE(meta_functions::is_assignable_v<double>);
        EXPECT_FALSE(meta_functions::is_assignable_v<Hoge>);
    }
    
    TEST(MetaFunctionsTest, void_t)
    {
        class Hoge{
        };
        
        EXPECT_TRUE(meta_functions::is_equality_comparable<int>::value);
        EXPECT_FALSE(meta_functions::is_equality_comparable<Hoge>::value);
    }
    
    TEST(MetaFunctionsTest, sort) {
        std::vector<int> vec{3, 1, 4, 1, 5, 9, 2};
        std::list<int> lis{3, 1, 4, 1, 5, 9, 2};
        for (auto v : vec) {
            std::cout << v << ',' << std::endl;
        }
        for (auto l : lis) {
            std::cout << l << ',' << std::endl;
        }
        meta_functions::generalSort(std::move(vec));
        meta_functions::generalSort(std::move(lis));
//        std::sort(vec.begin(), vec.end());
//        lis.sort();
        for (auto v : vec) {
            std::cout << v << ',' << std::endl;
        }
        for (auto l : lis) {
            std::cout << l << ',' << std::endl;
        }
    }
    
    TEST(MetaFunctionsTest, has_func) {
        
        static_assert(meta_functions::is_assignable_v<meta_functions::X>, "assignable");
        static_assert(meta_functions::has_func_v<meta_functions::X>, "double can be applied for func");
        static_assert(!meta_functions::has_func_v<std::string>, "string can be applied for func");
        std::cout << meta_functions::has_func_v<meta_functions::X> << std::endl;
        std::cout << meta_functions::has_func_v<std::string> << std::endl;
        int x;
        double y;
        std::string z;
        meta_functions::X w;
        EXPECT_EQ(1, meta_functions::get_func_value(x));
        EXPECT_EQ(1, meta_functions::get_func_value(y));
        EXPECT_EQ(2, meta_functions::get_func_value(w));
        EXPECT_EQ(0, meta_functions::get_func_value(z));
    }
    
    
    
}
