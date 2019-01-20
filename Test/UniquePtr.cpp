//
// Created by MORIMOTO on 2017/10/14.
//


#include <gtest/gtest.h>
#include <memory>
#include <iostream>
#include <fstream>

using ::testing::Test;

namespace UniquePtrTest {
   TEST(UniquePtrTest, assign) {
        std::unique_ptr<double> pt{new double};
        *pt = 7;
        
        double * raw_dp = pt.get();
        *raw_dp = 6;
        EXPECT_EQ(*pt, 6);
        
    }
    
    TEST(UniquePtrTest, move) {
        std::unique_ptr<double> pt1{new double};
        *pt1 = 5;
        std::cout << "hogemove" << std::endl;
        std::unique_ptr<double> pt2
        = std::move(pt1);
        EXPECT_EQ(pt1, nullptr);
        EXPECT_EQ(*pt2, 5);
    
    }
    
    TEST(UniquePtrTest, Age) {
        std::cout << "What is your age?" << std::endl;
        int age = 0;
//        std::cin >> age;
//
//        std::ofstream myfile;
//        myfile.open("age.txt");
//        myfile << "My age is " << age
//               << "." << std::endl;
//        myfile.close();
    }
    
    TEST(UniquePtrTest, ArrayAndPointers) {
        char* c = new char;
        delete c;
        
        int* iArray = new int[10];
        delete[] iArray;
        
        int array[10];
    }
    
    TEST(UniquePtrTest, CreateArray) {
        int a[10];
        a[0] = 32;
        std::cout << a[0] << std::endl;
    }
}
