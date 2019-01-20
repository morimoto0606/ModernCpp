//
// Created by MORIMOTO on 2018/01/04.
//

#include <gtest/gtest.h>
#include "../Source/ConceptOfF.h"

namespace concept {
    TEST(conceptF, f) {
        static_assert(concept::has_f<double, double>::value, "double + double");
        static_assert(concept::has_f<int, double >::value, "int, double");
        //static_assert(concept::has_f<int, std::string>::value, "int, string");
    }
}

