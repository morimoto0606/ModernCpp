//
// Created by MORIMOTO on 2018/01/04.
//
#include <gtest/gtest.h>
#include "../Source/ConceptOfPoint.h"
#include "../Source/ConceptOfMin.h"
#include "../Source/ConceptOverload.h"
#include <cmath>
namespace concept {
    TEST(concept, point1) {
        concept::MyPoint1 a(1., 1.);
        concept::MyPoint1 b(-1., -1.);
        double dist = concept::distance(a, b);
        EXPECT_DOUBLE_EQ(2. * sqrt(2.), dist);
    }
    
    TEST(concept, point2) {
        concept::MyPoint2 a(1., 1.);
        concept::MyPoint2 b(-1., -1.);
        double dist = concept::distance(a, b);
        EXPECT_DOUBLE_EQ(2. * sqrt(2.), dist);
    }
    
    
}
