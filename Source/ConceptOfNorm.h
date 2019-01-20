//
// Created by MORIMOTO on 2018/01/06.
//

#ifndef MODERNCPP_CONCEPTOFNORM_H
#define MODERNCPP_CONCEPTOFNORM_H

#include <algorithm>
#include <numeric>
#include <cmath>
#include <boost/numeric/ublas/matrix.hpp>
namespace concept {
    
    class Real {
    public:
        Real(const double x) : _x(x) {}
        double x() const {
            return _x;
        }
    private:
        double _x;
    };
    
    class Complex {
    public:
        Complex(const double x, const double y)
        : _x(x), _y(y) {}
        double real() const {
            return _x;
        }
        double im() const {
            return _y;
        }
    private:
        double _x;
        double _y;
    };
    
    class Reals {
    public:
        Reals(const std::initializer_list<double>& x)
        : _x(x) {}
        std::vector<double> values() const {
            return _x;
        }
    private:
        std::vector<double> _x;
    };
   
    class Matrix {
    public:
        Matrix(const std::initializer_list<
        std::initializer_list<double >>& a)
        : _a(a.begin(), a.end()) {}
        std::vector<std::vector<double>> getElements() const {
            return _a;
        }
    private:
        std::vector<std::vector<double>> _a;
    };
   
    namespace ublas = boost::numeric::ublas;
    class Matrix2 {
    public:
        Matrix2(const ublas::matrix<double>& mat)
        : _mat(mat) {}
        ublas::matrix<double> getMat() const {
            return _mat;
        }
    private:
        ublas::matrix<double>  _mat;
    };
    
    template <typename T>
    struct is_multi_dim_category : public std::true_type {};
    
    template <>
    struct is_multi_dim_category<Real>:  public std::false_type{};
    
    template <typename T>
    struct alg_traits2 {
    };
    template <>
    struct alg_traits2<Matrix2> {
        static ublas::vector<double> getAllElemet(const Matrix2& mat) {
            ublas::vector<double> vec(mat.getMat().size1() * mat.getMat().size2());
            for(std::size_t i = 0; i < mat.getMat().size1(); ++i) {
                for (std::size_t j = 0; j < mat.getMat().size1(); ++j) {
                    vec(mat.getMat().size1() * i + j) = mat.getMat()(i, j);
                }
            }
            return vec;
        }
    };
    
   
    //concept 1 : tagを用意する
    struct one_dim_tag{};
    struct multi_dim_tag{};
    
    //concept 2 : 各クラスがどのタグに該当するかカテゴライズ
    template <typename T, typename Enable = void>
    struct categorize {
        using type = multi_dim_tag;
    };
    template <>
    struct categorize<Real> {
        using type = one_dim_tag;
    };
    template <typename T>
    struct categorize<T, std::enable_if_t<is_multi_dim_category<T>::value, void>> {
        using type = multi_dim_tag;
    };
    
     //concept 3 : overload関数を呼ぶのに必要な具象クラスの呼び出し方をtraitsで呼ぶ。
    template <typename T, typename Enable = void>
    struct alg_traits{};
    
    template <>
    struct alg_traits<Real> {
        static double value(const Real& x) { return x.x(); }
    };
    
    template <>
    struct alg_traits<Complex> {
        static std::vector<double> values(const Complex& x) {
            return std::vector<double> {x.real(), x.im()};
        }
    };
    
    template <>
    struct alg_traits<Reals> {
        static std::vector<double> values(const Reals& x) {
            return x.values();
        }
    };
    
    template <>
    struct alg_traits<Matrix> {
        static std::vector<double> values(const Matrix& x) {
            std::vector<double> ret;
            for (auto v : x.getElements()) {
                std::copy(v.cbegin(), v.cend(),
                          std::back_insert_iterator<std::vector<double>>(ret));
            }
            for (auto x : ret) {
                std::cout << x << std::endl;
            }
            return ret;
        }
    };
    
    template <typename T>
    struct alg_traits<T, std::enable_if_t<is_multi_dim_category<T>::value, void>> {
        static std::vector<double> values(const T& m) {
            ublas::vector<double> u = alg_traits2<T>::getAllElemet(m);
            std::vector<double> v{u.cbegin(), u.cend()};
            return v;
        }
    };
    
    //concept 4 : tagに基づいた関数をオーバーロードで作る
    template <typename T>
    double norm_impl(const T& x, one_dim_tag) {
        using traits = alg_traits<T>;
        double d = std::abs(traits::value(x));
        return d;
    }
    
    template <typename T>
    double norm_impl(const T& x, multi_dim_tag) {
        using traits = alg_traits<T>;
        std::vector<double> allElems = traits::values(x);
        std::vector<double> allElems2;
        std::transform(allElems.cbegin(), allElems.cend(),
        std::back_insert_iterator<std::vector<double>>(allElems2),
        [](double x){ return x * x;});
        
        double ret = std::accumulate(allElems2.cbegin(),
        allElems2.cend(), 0.0);
        return std::sqrt(ret);
    }
    
    //concept last : implをまとめた関数を呼ぶ
    template <typename T>
    double norm(const T& x) {
        return norm_impl(x, typename categorize<T>::type());
    }
   
}

#endif //MODERNCPP_CONCEPTOFNORM_H
