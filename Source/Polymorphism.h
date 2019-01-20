//
// Created by MORIMOTO on 2017/12/30.
//

#ifndef MODERNCPP_POLIMORPHISM_H
#define MODERNCPP_POLIMORPHISM_H

#include <type_traits>
namespace poli {
    //virtual polymorphism
    
    struct Base1 {
        virtual ~Base1() {}
        virtual void calc() const = 0;
    };
    struct Derived1 : public Base1 {
        void calc() const override {
        }
    };
    struct Derived1Test : public Base1 {
        void calc() const override {
            std::cout << "polymorphic test" << std::endl;
        }
    };
   

    //CRTP
    template <typename T>
    struct Base2 {
        virtual ~Base2(){}
        void calc() const {
            static_cast<const T*>(this)->calc();
        }
    };
    struct Derived2 : public Base2<Derived2>
    {
        void calc() const {
        }
    };
    struct Derived2Test :public Base2<Derived2Test>
    {
        void calc() const {
            std::cout << "CRTP test" << std::endl;
        }
    };
   
    //Enable_if
    struct type{
        static void apply() {
        }
    };
    struct typeTest{
        static void apply() {
            std::cout << "typeTest" << std::endl;
        }
    };
    
    template <typename T, std::enable_if_t<
    std::is_same_v<T, type>, nullptr_t> = nullptr>
    void calc() {
    };
    
    template <typename T, std::enable_if_t<
    std::is_same_v<T, typeTest>, nullptr_t> = nullptr>
    void calc() {
        std::cout << "enable_if_test" << std::endl;
    };
    
    // policy
    template <typename T>
    void f_policy() {
        T::apply();
    }
    
    //traits
    template <typename T>
    struct type_traits {
        static void apply() {
            type::apply();
        }
    };
    template <>
    struct type_traits<typeTest> {
        static void apply()  {
            std::cout << "type_traits_test" << std::endl;
            typeTest::apply();
        }
    };
    
    struct tag1{};
    struct tag_test{};
    //tag dispatch
    template <typename T>
    struct tag_traits {
        using type = tag1;
    };
    template <>
    struct tag_traits<tag_test> {
        using type = tag_test;
    };
    void func(tag1 x) {
    }
    void func(tag_test x) {
        std::cout << "tag dispatch test" << std::endl;
    }
    
   
   
    
    
    // each type functions
    template <typename T>
    void f_crtp(const Base2<T>& x) {
        x.calc();
    }
    void f_inheritence(const Base1& x) {
        x.calc();
    }
    template <typename T>
    void f_enable() {
        calc<T>();
    }
    template <typename T>
    void f_tag() {
        func(typename tag_traits<T>::type());
    }
    template <typename T>
    void f_traits() {
        type_traits<T>::apply();
    }
    
}

#endif //MODERNCPP_POLIMORPHISM_H
