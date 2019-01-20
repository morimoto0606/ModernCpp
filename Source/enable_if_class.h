//
// Created by MORIMOTO on 2018/01/20.
//

#ifndef MODERNCPP_ENABLE_IF_CLASS_H
#define MODERNCPP_ENABLE_IF_CLASS_H

#include <type_traits>
#include <iostream>
namespace enable {
    class Hoge {
    public:
        void show() const {
            std::cout << "hoge" << std::endl;
        }
    private:
    };
    
    template <typename T>
    class Fuga {
    public:
        Fuga(T x) : _x(x) {}

        template <typename U, std::enable_if_t<std::is_same_v<U, Hoge>, nullptr_t > = nullptr>
        void func(U x) {
            _x.show();
        }
        template <typename U, std::enable_if_t<!std::is_same_v<U, Hoge>, nullptr_t > = nullptr>
        void func(U x) {
            std::cout << "!Hoge" << std::endl;
        };
    private:
        T _x;
    };
    
    template <typename T,
        std::enable_if_t<std::is_same_v<T, Hoge>, nullptr_t> = nullptr>
    void func(T x) {
       x.show();
    }
    
    template <typename T,
        std::enable_if_t<!std::is_same_v<T, Hoge>, nullptr_t> = nullptr>
    void func(T x) {
        std::cout << "!hoge" << std::endl;
    };
    
    template <typename T>
    std::enable_if_t<!std::is_same_v<T, Hoge>, int>
    get(T x) {
        std::cout << "int" << std::endl;
        return 3;
    }
    template <typename T>
    std::enable_if_t<std::is_same_v<T, Hoge>, void>
    get(T x) {
        x.show();
    };
    
    int func2(int x) {
        std::cout << x << std::endl;
       return x;
    }
    void func2(Hoge x){
       x.show();
    }
    
    //meta function
    struct is_applicable_func2_impl {
        template <typename T>
        static auto check(T*) -> decltype(
            func2(std::declval<T>()), std::true_type{});
        template <typename T>
        static auto check(...) -> std::false_type;
    };
    
    template <typename T>
    struct is_applicable_func2 :
        decltype(is_applicable_func2_impl::check<T>(nullptr)){};
    
    template <typename T>
    constexpr bool is_applicable_func2_v = is_applicable_func2<T>::value;
    
    template <typename T>
    std::enable_if_t<is_applicable_func2_v<T>, void>
    show_func2(T x) {
        func2(x);
    };
    template <typename T>
    std::enable_if_t<!is_applicable_func2_v<T>, void>
    show_func2(T x) {
       std::cout << "not applicable func2" << std::endl;
    }
}

#endif //MODERNCPP_ENABLE_IF_CLASS_H
