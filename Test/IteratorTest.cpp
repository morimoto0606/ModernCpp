//
// Created by MORIMOTO on 2018/01/07.
//
#include "../Source/Iterator.h"
#include <gtest/gtest.h>

namespace it {
    TEST(it, iterator) {
        my_list  root = create_list();
        for (my_list_iterator it = begin(root);
        it != end(root); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }
    
    TEST(it, for_each) {
        auto root = create_list();
        std::for_each(begin(root), end(root), &print);
    }
}