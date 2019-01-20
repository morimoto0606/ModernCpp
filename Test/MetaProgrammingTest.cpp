//
// Created by MORIMOTO on 2017/11/02.
//
#include <gtest/gtest.h>
#include <iostream>
#include <algorithm>
#include <complex>
#include "../Source/MetaProgramming.h"
#include <vector>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <algorithm>
#include <typeinfo>

namespace ublas = boost::numeric::ublas;
TEST(MetaProgramming, fibonacci) {
    std::vector<long> expected {1 , 1, 2, 3, 5, 8, 13, 21, 34, 55};
    std::vector<long> actual;
    for (long n = 1; n < 11; ++n) {
        actual.emplace_back(metap::fibonacci(n));
    }
    EXPECT_TRUE(expected == actual);
}

TEST(MetaProgramming, min_magnitude)
{
    double d1 = 0.3;
    double d2 = 0.5;
    std::cout << "min {d1, d2} = " << metap::min_magnitude(d1, d2) << std::endl;
    
    std::complex<double> c1(3., -2.3);
    std::complex<double> c2(4., 1.2);
    std::cout << "min {c1, c2} = " << metap::min_magnitude(c1, c2) << std::endl;
}

TEST(MetaProgramming, matrix_transpose)
{
   ublas::matrix<int> matrix(3, 3);
   std::vector<std::vector<int>> m {
   {2,3,4},
   {5,6,7},
   {8,9,0}
   };
   for (int i = 0; i < 3; ++i) {
      std::copy(m[i].cbegin(), m[i].cend(),
                ublas::matrix_row<ublas::matrix<int>>(matrix, i).begin());
   }
    std::cout << matrix << std::endl;
    
    metap::transposed_view<ublas::matrix<int>> At(matrix);
    for (auto i = 0; i < 3; ++i) {
        for (auto j = 0; j < 3; ++j) {
            At(i, j) = 2;
        }
        for (auto j = 0; j < 3; ++j) {
            std::cout << At(i,j) << ", ";
        }
        std::cout << std::endl;
    }
    const ublas::matrix<int> B(matrix);
   //std::cout << metap::trans(B)(0, 1) << std::endl;
    const auto C = metap::trans(B);
    const int i = C(0, 0);
    std::cout << i << std::endl;
    std::cout << typeid(metap::trans(matrix)).name() << std::endl;
    std::cout << typeid(metap::trans(B)).name() << std::endl;
    
}

TEST(MetaProgramming, Compile_if)
{
    constexpr int max_itr = 200;
    using tmp_type = typename metap::conditional<(max_itr > 180), double, float>::type;
    std::cout << typeid(tmp_type).name() << std::endl;
    
    using new_type = metap::conditional_t<(max_itr > 180), double , float>;
    std::cout << typeid(new_type).name() << std::endl;
}


TEST(MetaProgramming, new_transposed_view)
{
   ublas::matrix<int> matrix(3, 3);
   std::vector<std::vector<int>> m {
   {2,3,4},
   {5,6,7},
   {8,9,0}
   };
   for (int i = 0; i < 3; ++i) {
      std::copy(m[i].cbegin(), m[i].cend(),
                ublas::matrix_row<ublas::matrix<int>>(matrix, i).begin());
   }
    std::cout << matrix << std::endl;
    
    metap::new_transposed_view<const ublas::matrix<int>> At(matrix);
    for (auto i = 0; i < 3; ++i) {
//        for (auto j = 0; j < 3; ++j) {
//            At(i, j) = 2;
//        }
        for (auto j = 0; j < 3; ++j) {
            std::cout << At(i,j) << ", ";
        }
        std::cout << std::endl;
    }
    const ublas::matrix<int> B(matrix);
    auto Bt = metap::new_transposed_view<const ublas::matrix<int>>(B);
    std::cout << Bt(0, 1) << std::endl;
}

TEST(MetaProgramming, is_matrix)
{
    static_assert(metap::is_matrix<ublas::matrix<double>>::value,
    "It is not a Matrix!");
    static_assert(metap::is_matrix<const ublas::matrix<double>>::value,
    "It is not a Matrix!");
    
//    static_assert(metap::is_matrix<ublas::vector<double>>::value,
//    "It is not a Matrix!");
}

TEST(MetaProgramming, one_norm)
{
    ublas::matrix<int> matrix(3, 3);
    std::vector<std::vector<int>> m {
    {2,3,4},
    {5,6,7},
    {8,9,0}
    };
    for (int i = 0; i < 3; ++i) {
        std::copy(m[i].cbegin(), m[i].cend(),
                  ublas::matrix_row<ublas::matrix<int>>(matrix, i).begin());
    }
    auto norm = metap::one_norm(matrix);
    int max = 0;
    for (auto v : m) {
        int tmp = 0;
        for (auto x : v) {
           tmp += std::abs(x);
        }
        max = tmp < max ? max : tmp;
    }
    EXPECT_EQ(max, norm);
    
    metap::enable_if_t<true, int> x;
    //ajmetap::enable_if_t <false, double> y;
    
    std::vector<int> vec{3, 5, -3, 5, -2, -5};
    auto d = metap::one_norm(vec);
    std::cout << d << std::endl;
    
    metap::check(matrix);
    metap::check(vec);
}

TEST(MetaProgramming, sfinae)
{
    double x;
    metap::something();
}