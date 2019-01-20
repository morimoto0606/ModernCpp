//
// Created by MORIMOTO on 2018/01/05.
//

#include <gtest/gtest.h>
#include "../Source/ConceptOverload.h"
#include "../Source/ConceptOfPoint.h"

namespace concept {
    
    TEST(conceptOverload, distance) {
        MyPoint1 p1(0.0, 0.0);
        MyPoint1 p2(3.0, 3.0);
        line_segment<MyPoint1> line(MyPoint1(2., 2.), MyPoint1(3., 3.));
        
        double d1 = distance(p1, p2);
        std::cout << d1 << std::endl;
        double d2 = distance(p1, line);
        std::cout << d2 << std::endl;
        double d3 = distance(line, line);
        std::cout << d3 << std::endl;
    }
    
    TEST(conceptOverload, overloadConceptInGeometery) {
            geo::point p1(0.0, 0.0);
            geo::point p2(3.0, 3.0);
            double d = distance(p1, p2);
            std::cout << "distance of geometry namespace" << std::endl;
            std::cout << d << std::endl;
    }
    
}
