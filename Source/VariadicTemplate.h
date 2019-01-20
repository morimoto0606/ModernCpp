//
// Created by MORIMOTO on 2017/11/12.
//

#ifndef CPPTEMPLATE_VARIADICTEMPLATE_H
#define CPPTEMPLATE_VARIADICTEMPLATE_H

#include <memory>
#include <type_traits>

namespace variadic {
    template <typename ...P> struct sum_type;
   
    template <typename T>
    struct sum_type<T> {
        using type = T;
    };
    
    template <typename T, typename ...P>
    struct sum_type<T, P... > {
        using  type = decltype(T() +
        typename sum_type<P...>::type());
    };
    
    template <typename ...P>
    using sum_type_t = typename sum_type<P...>::type;
    
    template <typename T>
    inline T sum(T t) { return t;}
    
    template <typename T, typename ...P>
    sum_type_t<T, P...> sum(T t, P... p)
    {
        return t + sum(p...);
    };
    
    template <typename T>
    inline T minimum(const T& t) { return t;}
    
    template <typename T, typename ...P>
    typename std::common_type_t<T, P...>
    minimum(const T& t, const P& ...p)
    {
        //一番左とそれ以外のminimumをどんどん比較していくというアルゴリズム
        using res_type = std::common_type_t<T, P...>;
        return  std::min(res_type(t), res_type(minimum(p...)));
    };
    
    template <typename T>
    inline  T sum2(T t) {
        return  t;
    }
    template <typename T, typename ...P>
    typename std::common_type_t <T, P...> sum2(T t, P... p)
    {
        //return sum2(p...) + t;
        return  t + sum2(p...);
    };
    
    
    class Base {
    public:
        virtual void print() const = 0;
    };
    
    class Derived : public Base {
    public:
        void  print() const override
        {
            std::cout << "derived" << std::endl;
        }
    };
    
    void callDerived(const std::vector<std::unique_ptr<Base>>& bases)
    {
        for (const auto& base : bases) {
            base->print();
        }
    }
    
    template <typename T>
    T mult(T x) {
        return x;
    }
   
    
    template <typename T, typename ...U>
    typename std::common_type_t<T, U...> mult(T x, U... y){
        return x * mult(y...);
    };
   
    
   
}

#endif //CPPTEMPLATE_VARIADICTEMPLATE_H
