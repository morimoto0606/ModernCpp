//
// Created by MORIMOTO on 2018/01/06.
//

#include <gtest/gtest.h>
#include "../Source/MetaFuncitons2.h"
#include <memory>

namespace meta2 {
    TEST(meta2, is_pointer) {
        EXPECT_TRUE(is_pointer_v<float*>);
        EXPECT_FALSE(is_pointer_v<float>);
        
        float* x = new float(2);
        auto y = get_pointer_value(x);
        EXPECT_EQ(2, y);
        delete(x);
        
        std::unique_ptr<float> z(new float(3));
        auto w2 = get_pointer_value(z.get());
        EXPECT_EQ(3, w2);
        
        auto w = get_pointer_value(std::move(z));
        EXPECT_EQ(0, w);
    }
    
    TEST(meta2, isvector) {
        EXPECT_TRUE(is_vector_v<std::vector<double>>);
        EXPECT_TRUE(is_vector_v<ublas::vector<double>>);
        EXPECT_FALSE(is_vector_v<double>);
        std::vector<double> v {1, 2, 4};
        ublas::vector<double> w(2);
        w(0) = 3.5;
        w(1) = 2.4;
        auto a = get_vector_value(v);
        auto b = get_vector_value(w);
        auto c = get_vector_value(3.5);
        EXPECT_EQ(1, a);
        EXPECT_EQ(3.5, b);
        EXPECT_EQ(0, c);
    }
    
    TEST(meta2, has_iterator) {
        std::vector<double>::iterator it;
        EXPECT_TRUE(has_iterator_v<std::vector<double>>);
        EXPECT_FALSE(has_iterator_v<double>);
    }
    
    TEST(meta2, has_value_type) {
        EXPECT_TRUE(has_value_type_v<std::vector<int>>);
        EXPECT_FALSE(has_value_type_v<double>);
    }
    TEST(meta2, iterator_sum) {
        std::vector<int> v{1, 2, 3, 4, 5};
        auto sum = get_iterator_sum(v);
        EXPECT_EQ(15, sum);
        
        int a = 4;
        auto sum2 = get_iterator_sum(a);
        EXPECT_EQ(0, sum2);
    }
}
