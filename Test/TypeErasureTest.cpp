//
// Created by MORIMOTO on 2018/01/03.
//
#include <gtest/gtest.h>
#include "../Source/TypeErasure.h"

namespace erase {
    TEST(type_erausre, sample) {
        int a = 10;
        erase::X x(a);
    }
    
    TEST(type_erasure, shared_ptr) {
        struct hoge {
            hoge() { std::cout << "hoge constructor" << std::endl;}
            ~hoge() {std::cout << "hoge destructor" << std::endl;}
            void somthing() const {
                std::cout << "do something" << std::endl;
            }
        };
        std::cout << "row ptr" << std::endl;
        hoge* h = new(hoge);
        h->somthing();
        delete(h);
        std::cout <<"-----------------------------------" << std::endl;
        std::cout << "ordinary object" << std::endl;
        std::cout <<"-----------------------------------" << std::endl;
        hoge g;
        g.somthing();
        std::cout <<"-----------------------------------" << std::endl;
        std::cout << "my shared ptr" << std::endl;
        std::cout <<"-----------------------------------" << std::endl;
        erase::shared_ptr<hoge> s(new(hoge));
        s->somthing();
        std::cout <<"-----------------------------------" << std::endl;
        std::cout << "my shared ptr with my deleter" << std::endl;
        std::cout <<"-----------------------------------" << std::endl;
        erase::deleter del;
        erase::shared_ptr<hoge> myptr(new(hoge), del);
        myptr->somthing();
        std::cout <<"-----------------------------------" << std::endl;
    }
    
    
}
