//
// Created by MORIMOTO on 2017/12/16.
//

#ifndef MODERNCPP_ENABLE_IF_H
#define MODERNCPP_ENABLE_IF_H

#include <utility>
#include <string>
#include <type_traits>
#include <iostream>
namespace enable {
    template <typename T>
    std::enable_if_t<(sizeof(T) > 4)>
    foo() { std::cout << "sizeof(T) > 4 void" << std::endl;}
    
    template <typename T>
    std::enable_if_t<(sizeof(T) > 4), T>
    foo() {
        std::cout << "sizeof(T) > 4 T" << std::endl;
        return T();
    };
   
    template <typename T>
    using EnableIfString = std::enable_if_t <
    std::is_convertible_v<T, std::string>>;
    class Person
    {
    private:
        std::string _name;
    public:
        template <typename STR, typename = EnableIfString<STR>>
        explicit Person(STR&& n) : _name(std::forward<STR>(n))
        {
            std::cout << "TMPL-CONSTR for" << _name << std::endl;
            std::cout << this->_name << std::endl;
        }
        
        Person(Person const& p) : _name(p._name) {
            std::cout << " Copy constructor" << std::endl;
            std::cout << this->_name << std::endl;
        }
        Person(Person&& p) : _name(std::move(p._name)) {
            std::cout << " Move Construcntor" << std::endl;
            std::cout << this->_name << std::endl;
        }
        
    };
    
    class C1 {
    public:
        C1() {}
        template <typename T>
        C1(const T&) {
            std::cout << "template copy constructor1" << std::endl;
        }
    };
    
    class C2 {
    public:
        C2() {}
        C2(const volatile C2&) = delete;
        template <typename T>
        C2(const T&) {
            std::cout << "template copy constructor2" << std::endl;
        }
    };
    
    template <typename T>
    class C
    {
    public:
        C(C const volatile&) = delete;
        
        template <typename U,
        typename = std::enable_if_t <!std::is_integral<U>::value>>
        C(C<U> const&) {
            std::cout << "T is no integral type" << std::endl;
        }
    };
}

#endif //MODERNCPP_ENABLE_IF_H
