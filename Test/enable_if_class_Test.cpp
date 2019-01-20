//
// Created by MORIMOTO on 2018/01/20.
//
#include <gtest/gtest.h>
#include "../Source/enable_if_class.h"
#include <string>
namespace enable {
    
    TEST(enable_class, hoge) {
        Hoge x;
        Fuga<Hoge> fuga{x};
        fuga.func(23);

//        int a = 0;
//        Fuga<int> fuga1{a};
//        fuga1.func();
        func(x);
        func(3);
            
            get(x);
        get(3);
            struct X{};
        X dummy;
        func(dummy);
        std::cout << is_applicable_func2_v<std::string> << std::endl;
        std::cout << is_applicable_func2_v<int> << std::endl;
        std::cout << is_applicable_func2_v<Hoge> << std::endl;
        std::cout << is_applicable_func2_v<X> << std::endl;
        
        show_func2(3);
            show_func2(x);
        show_func2(dummy);
    }
}
