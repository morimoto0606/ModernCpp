//
// Created by MORIMOTO on 2017/10/15.
//


#include <gtest/gtest.h>
using testing::Test;

#include "../Source/GenericProgramming.h"
#include <complex>

TEST(Generic, max) {
    float a = 1.0;
    float b = 3.0;
    float c = generic::max(a, b);
    EXPECT_DOUBLE_EQ(b, c);
}

//TEST(Generic, complexMax) {
//    std::complex<float> z(3,2);
//    std::complex<float> w(2,3);
//    std::cout << generic::max(z, w) << std::endl;
//}

TEST(Generic, vector) {
    generic::vector<double> v(3);
    generic::vector<double> v2(v);
    
    double a[3] = {3,5,7};
    std::unique_ptr<double[]> b{new double[3]{3,4,5}};
    std::cout << b[0] << b[1] << b[2] << std::endl;
    
    double* x = &b[0];
    double* y = &b[1];
    double* z = &b[2];
    
    *x = -3.0;
    *y = -9.;
    *z = -2.;
    
     std::cout << b[0] << b[1] << b[2] << std::endl;
}

TEST(Generic, maxArray) {
    double a[4] = {2,5,7,.46};
    std::cout << generic::sum(a) << std::endl;
}

TEST(Generic, list) {
    generic::list<float> l;
    l.append(2.0f);
    l.append(4.0f);
    l.append(7.0f);
    
    float sum = 0;
    for (auto entry = l._first; entry != nullptr; entry = entry->_next) {
        sum += entry->_value;
    }
    std::cout << sum << std::endl;
    std::cout << generic::sum(l.begin(), l.end(), 0) << std::endl;
    for (auto v : l) {
        std::cout << v << std::endl;
    }
}

TEST(Generic, decltype) {
    float expr = 1.3f;
    decltype(expr) v = expr;
    decltype(auto) w = expr;
    std::cout << v << w << std::endl;
}

TEST(Generic, my_list) {
    generic::my_list<double> l;
    l.append(1.3);
    l.append(3.6);
    l.append(5.3);
    
    std::cout << l._first->_value << std::endl;
    
    generic::my_list_iterator<double> itr = l.begin();
    std::cout << *itr << std::endl;
    std::cout << *(++itr) << std::endl;
    std::cout << *(++itr) << std::endl;
}

TEST(Generic, abs) {
    float_t f = -1.0f;
    float_t g = generic::abs(f);
    std::cout << f << ',' << g << std::endl;
    
    std::complex<double> c(1, 2);
    std::cout << "complex abs" << generic::abs(c) << std::endl;
}

TEST(Generic, fsize_vector) {
    generic::fsize_vector<double, 3> f;
    generic::fsize_vector<double, 3> g;
    auto h = f + g;
    std::cout << "f" << std::endl;
    f.print();
    std::cout << "g" << std::endl;
    g.print();
    std::cout << "h" << std::endl;
    h.print();
}

TEST(Generic, finiteDiff) {
    generic::sc_f<double> f;
    generic::psc_f<double> g(1);
    double d = generic::fin_diff(f, 1.0, 0.01);
    double h = generic::fin_diff(g, 1.0, 0.01);
    std::cout << "d = " << d << std::endl;
    std::cout << "h = " << h << std::endl;
    
    std::vector<double> v{1, 2, 3, 4, 5, 6, 7, 8, 8, 10};
    for (double x : v) {
        double df = generic::fin_diff(g, x, 0.0001);
        std::cout << df << std::endl;
    }
}
    
TEST(Generic, ComposingFunctors) {
    generic::psc_f<double> f(1.0);
    generic::d_psc_f df(f, 0.001);
    
    std::vector<double> v{1.,2.,3.,4.};//,5,6,7,8,9,10};
    for (double x : v) {
        std::cout << f(x) <<',' << df(x) << std::endl;
    }
    
    generic::dd_psc_f ddf(df, 0.001);
    for (double x : v) {
        std::cout << x << ',' << ddf(x) << std::endl;
    }
    
    generic::second_derivative<generic::psc_f<double>, double>
    ddf2(std::move(f), 0.001);
    std::cout << "direct second deriv" << std::endl;
    for (double x: v) {
        std::cout << ddf2(x) << std::endl;
    }
}

TEST(Generic, ex1) {
    std::cout << generic::to_string(12)<< std::endl;
}
TEST(Generic, stack) {
    generic::stack<int, 3> stack;
    std::cout << stack.top() << std::endl;
    std::cout << stack.isEmpty() << std::endl;
    stack.push(1);
    stack.push(2);
    std::cout << stack.isEmpty() << std::endl;
    std::cout <<  stack.pop() << std::endl;
    std::cout << stack.isFull() << std::endl;
    stack.push(3);
    std::cout << stack.pop() << std::endl;
}

TEST(Gneric, vector_iterator)
{
    generic::vector<int> vec{1, 2, 3, 5, 8, 13};
    generic::vector<int>::iterator it = vec.begin();
    for (; it != vec.end(); ++it) {
        std::cout << *it << std::endl;
    }
    for (int i : vec) {
        std::cout << i << std::endl;
    }
}

TEST(Generic, odd_iterator)
{
    generic::odd_iterator it;
    for (int i = 0; i < 10; ++i) {
        std::cout << i << ',' << *it << std::endl;
        ++it;
    }
}

TEST(Generic, make_unique)
{
    double d = 1.5;
    std::unique_ptr<double> ptr
    = generic::make_unique<double>(d);
    
    std::cout << *ptr << std::endl;
    
    generic::odd_iterator itr;
    auto itrPtr = generic::make_unique<generic::odd_iterator>(itr);
    for (int i = 0; i < 10; ++i) {
        std::cout << *(*itrPtr) << std::endl;
        ++(*itrPtr);
    }
    std::cout << *(++itr) << std::endl;
    std::cout << *(++itr) << std::endl;
}

