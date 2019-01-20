//
// Created by MORIMOTO on 2018/01/06.
//

#include <gtest/gtest.h>
#include "../Source/ConceptOfNorm.h"
#include <iostream>

namespace concept {
    TEST(norm, norm) {
        Real r(3.4);
        Reals vec{1.0, 1.0};
            Complex c(1.0, 1.0);
        Matrix mat{{1., 2, 3.}, {0, 0, sqrt(2.)}};
        
        std::cout << norm(r) << std::endl;
        std::cout << norm(vec) << std::endl;
        std::cout << norm(c) << std::endl;
        std::cout << norm(mat) << std::endl;
        
        ublas::matrix<double> v(2, 2);
        v(0, 0) = 1;
            v(0, 1) = 0;
        v(1, 0) = 1;
        v(1, 1) = 0;
        
        Matrix2 mat2(v);
        auto w = alg_traits2<Matrix2>::getAllElemet(mat2);
        std::cout << norm(mat2) << std::endl;
        
    }
}

