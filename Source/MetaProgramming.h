//
// Created by MORIMOTO on 2017/11/02.
//

#ifndef CPPTEMPLATE_METAPROGRAMMING_H
#define CPPTEMPLATE_METAPROGRAMMING_H

#include <math.h>
#include <complex>
#include <boost/numeric/ublas/matrix.hpp>
#include <type_traits>
#include <numeric>
#include <algorithm>
#include <utility>

namespace ublas = boost::numeric::ublas;

namespace metap{
    constexpr long fibonacci(long n)
    {
        return  n <=2 ? 1 : fibonacci(n-1) + fibonacci(n-2);
    }
    
    //type traits
    // complex 型の絶対値に備えて以下のType Traitsを用意する。
    template <typename T>
    struct Abs {
        using type = T;
    };
    
    template <typename T>
    struct Abs<std::complex<T>> {
        using type = T;
    };
   
    template <typename T>
    struct Magnitude
    {
        using type = T;
    };
    template <typename T>
    struct Magnitude<std::complex<T>>
    {
        using type = T;
    };
    template <typename T>
    struct Magnitude<ublas::matrix<T>>
    {
        using type = T;
    };
    template <typename T>
    struct Magnitude<std::vector<T>>
    {
        using type = T;
    };
    
    template <typename T>
    using Magnitude_t = typename Magnitude<T>::type;
    
    template <typename T>
    typename Abs<T>::type inline abs(const T& x)
    {
        return x > 0 ? x : -x;
    }
    
    template <>
    typename Abs<std::complex<double>>::type inline abs(const std::complex<double>& x)
    {
        return std::sqrt(x.real() * x.real() + x.imag() * x.imag());
    }
    
    template <typename T>
    T inline min_magnitude(const T& x, const T& y)
    {
        typename metap::Abs<T>::type ax = metap::abs(x);
        typename metap::Abs<T>::type ay = metap::abs(y);
        return ax < ay ? x : y;
    }

#include <type_traits>
    template <typename T>
    inline T clone(const T& x) noexcept (std::is_nothrow_copy_constructible<T>::value)
    { return T{x};}
    
    // 転置行列に変換するメタクラス
    template <typename Matrix>
    class transposed_view
    {
    public:
        using value_type = typename  Matrix::value_type;
        using size_type = typename Matrix::size_type;
        
        explicit transposed_view(Matrix& A) : _ref{A} {}
        
        value_type&  operator()(size_type r, size_type c) {
            return _ref(c, r);
        }
        const value_type& operator()(size_type r, size_type c) const
        {
            return _ref(c, r);
        }
    private:
        Matrix& _ref;
    };
    
    //転置行列を作るメタ関数
    template <typename T>
    inline transposed_view<T> trans(T& A) {
        return transposed_view<T>(A);
    }
    
    //const Matrix に対応
    template <typename T>
    struct is_const
    {
        static const bool value = false;
    };
    template <typename T>
    struct is_const<const T>
    {
        static const bool value = true;
    };
    
    //Complie-Time If
    template <bool Condition, typename ThenType, typename ElseType>
    struct conditional
    {
        using type = ThenType;
    };
    template <typename ThenType, typename ElseType>
    struct conditional<false, ThenType, ElseType>
    {
        using type = ElseType;
    };
    
    //using alias
    template <bool b, class T, class F>
    using conditional_t = typename conditional<b, T, F>::type ;
    
    template<typename Matrix>
    class new_transposed_view
    {
    public:
        using value_type = typename Matrix::value_type;
        using size_type = typename Matrix::size_type;

    private:
        using vref_type = conditional_t<is_const<Matrix>::value,
            const value_type&, value_type&>;
    public:
        new_transposed_view(Matrix& A) : _ref(A) {}
        vref_type operator()(size_type r, size_type c)
        {
            return _ref(c, r);
        }
        const value_type& operator()(size_type r, size_type c) const
        {
            return _ref(c, r);
        }

    private:
        Matrix& _ref;
    };
    
    //matrix type distinction
    template <typename T>
    struct is_matrix : std::false_type
    {};
    
    template <typename T>
    struct is_matrix<ublas::matrix<T>> : std::true_type
    {};
    
    template <typename Matrix>
    struct is_matrix<new_transposed_view<Matrix>>
    : public is_matrix<Matrix>
    {};
   
    //Deal with const matrix
    template <typename T>
    struct is_matrix<const T> : public is_matrix<T>
    {};
    
    // define is vector traits
    template <typename T>
    struct is_vector : public std::false_type {};
    
    template <typename T>
    struct is_vector<std::vector<T>> : public std::true_type
    {};
    
    // define enable if
    template <bool Cond, typename T = void>
    struct enable_if
    {
        using type = T;
    };
    template <typename T>
    struct enable_if<false, T>
    {};
    
    template <bool Cond, typename T = void>
    struct disable_if
    {
        using type = T;
    };
    
    template <typename T>
    struct disable_if<true, T>
    {};
    
    template <bool Cond, typename  T = void>
    using enable_if_t = typename enable_if <Cond, T>::type;
    
    template <typename T>
    enable_if_t<is_matrix<T>::value, Magnitude_t<T>>
    inline one_norm(const T& A)
    {
        Magnitude_t<T> max{0};
        
        for(unsigned c = 0; c < A.size2(); ++c)
        {
            Magnitude_t<T> sum{0};
            for (unsigned r = 0; r < A.size1(); ++r) {
                sum += std::abs(A(r, c));
            }
            max = max < sum ? sum : max;
        }
        return max;
    };
    
    template <typename T>
    enable_if_t<is_vector<T>::value, Magnitude_t<T>>
    inline one_norm(const T& v)
    {
        return std::accumulate(
        std::cbegin(v), std::cend(v), 0,
        [](auto x, auto y){return x + std::abs(y);});
    };
    
    //sfinae
    template <typename T>
    void something(typename T::value_type x) {
        std::cout << "has value_type" << std::endl;
    }
    
    
    void something(...) {
        std::cout << "otherwise" << std::endl;
    }
    
    //enable if を使った関数の切り替え。
    //overload を用いているので、引数に部分にenable_ifをダミーで入れなければならい。
//    template <typename T>
//    void check(T value,
//        typename std::enable_if_t<is_matrix<T>::value> = nullptr)
//    {
//        std::cout << "T is matrix" << std::endl;
//    }
//    template <typename T>
//    void check(T value,
//        typename disable_if<is_matrix<T>::value, T>::type = nullptr)
//    {
//        std::cout << "T is not matrix" << std::endl;
//    }
//
    //関数templateのdefault 引数にenable_ifを用いる方法もある。
    template <typename T,
    std::enable_if_t<is_matrix<T>::value, T>* = nullptr>
    void check(T value)
    {
        std::cout << "T is matrix" << std::endl;
    };
    
    template <typename T,
    typename disable_if<is_matrix<T>::value, T>::type* = nullptr>
    void check(T value)
    {
        std::cout << "T is not matrix" << std::endl;
    };


    
    
}
#endif //CPPTEMPLATE_METAPROGRAMMING_H
