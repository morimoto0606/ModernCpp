//
// Created by MORIMOTO on 2017/12/17.
//

#ifndef MODERNCPP_VARIOUSOVERLOAD_H
#define MODERNCPP_VARIOUSOVERLOAD_H

#include <iostream>
#include <type_traits>
#include <string>
namespace overload {
    
    // 1. enable if
    //simple example for overload by enable_if
    template<typename T,
    typename std::enable_if_t<
    std::is_arithmetic_v<T>, nullptr_t>
    = nullptr>
    void f(T a) {
        std::cout << "T is arithmetic." << std::endl;
    };
    
    template<typename T,
    typename std::enable_if_t<
    !std::is_arithmetic_v<T>, nullptr_t>
    = nullptr>
    void f(T a) {
        std::cout << "T is not arightmetic." << std::endl;
    };
    
    // type overload using enable_if
    class X {
    public:
        virtual ~X() {
            std::cout << "called X destructor" << std::endl;
        }
        
        virtual void show() const {
            std::cout << "this is X" << std::endl;
        }
    };
    
    class Y : public X {
    public:
        ~Y() {
            std::cout << "called Y destructor" << std::endl;
        }
        
        virtual void show() const {
            std::cout << "this is Y" << std::endl;
        }
    };
//    template <typename T,
//        std::enable_if_t<std::is_same_v<T, X>,
//        nullptr_t> = nullptr>
//    void classFunc(T a) {
//        std::cout << "class X." << std::endl;
//    }
    
    template<typename T,
    std::enable_if_t<!std::is_base_of_v<X, T>,
    nullptr_t> = nullptr>
    void classFunc(const T &b) {
        std::cout << "Not class X" << std::endl;
    }
    
    template<typename T,
    std::enable_if_t<std::is_base_of_v<X, T>,
    nullptr_t> = nullptr>
    void classFunc(const T &x) {
        std::cout << "this is base of X" << std::endl;
        x.show();
    }

    class Hoge {
    public:
        std::string hoge() const {
            return "hoge";
        }
    };
    class Fuga {
    public:
        std::string  fuga() const {
            return "fuga";
        }
    };

    template <typename T>
    struct isHoge: std::false_type {};

    template <>
    struct isHoge<Hoge> : std::true_type {};

    template <typename T>
    struct isFuga : std::false_type {};

    template <>
    struct isFuga<Fuga> : std::true_type {};

    template <typename T>
    typename std::enable_if_t<isHoge<T>::value, std::string>
    enable_hogefuga(const T& x) {
        return x.hoge();
    }

    template <typename T>
    typename std::enable_if_t<isFuga<T>::value, std::string>
    enable_hogefuga(const T& x) {
        return x.fuga();
    }



   
    // 2. CRTP
    template <typename T>
    class Base {
    public:
        void show() const {
            static_cast<const T*>(this)->show();
        }
    };
    
    class Derived : public Base<Derived> {
    public:
        void show() const {
            std::cout << "Derived function." << std::endl;
        }
    };
    
    template <typename T>
    void crtpFunc(const Base<T>& base) {
        base.show();
    }
    
    //tag dispatch
    struct tag1{};
    struct tag2{};
    
    class X1{};
    class X2{};
    
    template <typename T>
    void func(T&& x, tag1) {
        std::cout << "called tag1" << std::endl;
    }
    template <typename T>
    void func(T&& x, tag2) {
        std::cout << "called tag2" << std::endl;
    }
    
    template <typename T>
    struct tag_traits {
    };
    template <>
    struct tag_traits<X1> {
        using tag = tag1;
    };
    template <>
    struct tag_traits<X2> {
        using tag = tag2;
    };
    
    template <typename T>
    void func(T&& x) {
        func(std::move(x), typename tag_traits<T>::tag());
    }
    
    template <typename T, typename U>
    T common_func(T x, U y)
    {
        return x < y ? x : y;
    };
   
}


#endif //MODERNCPP_VARIOUSOVERLOAD_H
