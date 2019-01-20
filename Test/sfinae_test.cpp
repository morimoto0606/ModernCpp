//
// Created by MORIMOTO on 2017/09/12.
//
#include <gtest/gtest.h>
#include "../Source/sfinae.h"
#include <vector>
#include <type_traits>

using ::testing::Test;
namespace sfinae_test {
    static_assert(std::is_same_v<int, sfinae::widget::value_type >,
    "type is not int");

}
