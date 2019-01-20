//
// Created by MORIMOTO on 2017/10/14.
//

#include <gtest/gtest.h>
#include "../Source/Classes.h"


using testing::Test;

TEST(ClassesTest, move) {
   classes::vector v(10, 12);
   std::cout << v.getData()[0] << std::endl;
   std::cout << v.getMysize() << std::endl;
   classes::vector mv(std::move(v));
   EXPECT_EQ(v.getData(), nullptr);
   std::cout << mv.getData()[0] << std::endl;
   std::cout << mv.getMysize() << std::endl;
   
   classes::vector v2(10, 3);
   v2 = std::move(mv);
   std::cout << v2.getData()[0] << std::endl;
   std::cout << v2.getMysize() << std::endl;
   std::cout << mv.getData()[0] << std::endl;
   std::cout << mv.getMysize() << std::endl;
}

TEST(ClassesTest, Polyn) {
   std::vector<double> coeff {1, 2, 3};
   classes::Polynomial polynomial(3);
   polynomial.setCoeffs(coeff);
   polynomial.output();
   
   classes::Polynomial polynomial2(3);
   std::vector<double> coeff2{6,4,2};
   polynomial2.setCoeffs(coeff2);
   std::cout << "polyn2" << std::endl;
   polynomial2.output();
   
   polynomial = polynomial2;
   std::cout << "polyn1 after assignment" << std::endl;
   polynomial.output();
   std::cout << "polyn2 after assignment" << std::endl;
   polynomial2.output();
   
}

TEST(ClassesTest, moveAssignment) {
   classes::Polynomial polynomial(3);
   classes::Polynomial polynomial2(3);
   std::vector<double> coeff {1,3, 5};
   std::vector<double> coeff2 {2,4,6};
   polynomial.setCoeffs(coeff);
   polynomial2.setCoeffs(coeff2);
   std::cout << "polyn1" << std::endl;
   polynomial.output();
   std::cout << "polyn2"  << std::endl;
   polynomial2.output();
   polynomial = polynomial2;
      std::cout << "polyn1 after move assignment" << std::endl;
   polynomial.output();
   std::cout << "polyn2 after move assignment"  << std::endl;
   polynomial2.output();
}

TEST(ClassesTest, initializer_list) {
   classes::Polynomial polynomial{1, 5, 9};
   polynomial.output();
}

TEST(ClassesTest, MyVect) {
   classes::MyVect v{.3, .5, .9};
   v.print();
   
   classes::MyVect v2(std::move(v));
   v.print();
   
   classes::MyVect v3(std::forward<classes::MyVect>(v));
   v.print();
   
   classes::MyVect v4{classes::MyVect{1,2,3}};
   v4.print();
}

TEST(ClassesTest, MyVect2) {
   classes::MyVect2 vec{-3, -2, -1};
   vec.output();
   
}

