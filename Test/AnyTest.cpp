//
// Created by MORIMOTO on 2018/01/04.
//
#include <gtest/gtest.h>
#include "../Source/Any.h"
namespace erase {
    TEST(anyTest, any) {
        struct hoge{};
        erase::any value = 3;
        erase::any value2 = value;
        value = hoge{};
        value = value2;
    }
}
