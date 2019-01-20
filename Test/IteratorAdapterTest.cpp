//
// Created by MORIMOTO on 2018/01/07.
//

#include <gtest/gtest.h>
#include "../Source/IteratorAdapter.h"
#include <iostream>
namespace ita {
    
    TEST(iteratorAdapter, display) {
        container c;
        for(container::iterator it = c.begin(); it != c.end(); ++it) {
            std::cout << *it << " ";
        }
    }

}