//
// Created by MORIMOTO on 2018/01/06.
//

#ifndef MODERNCPP_METAFUNCITONS2_H
#define MODERNCPP_METAFUNCITONS2_H

#include <type_traits>
#include <boost/numeric/ublas/vector.hpp>
#include <numeric>

namespace ublas = boost::numeric::ublas;

namespace meta2 {
    //is_pointer
    template <typename T>
    struct is_pointer : std::false_type {};
    template <typename T>
    struct is_pointer<T*> : std::true_type{};
    template <typename T>
    constexpr bool is_pointer_v = is_pointer<T>::value;
    
    template <typename T, std::enable_if_t<is_pointer_v<T>,
    nullptr_t> = nullptr>
    auto get_pointer_value(const T x) -> decltype(*x) {
        return *x;
    };
    template <typename T, std::enable_if_t<!is_pointer_v<T>,
    nullptr_t> = nullptr>
    int get_pointer_value(const T) { return 0;}
    
    //is_vector
    template <typename T>
    struct is_vector : std::false_type {};
    template <typename T>
    struct is_vector<std::vector<T>> : std::true_type{};
    template <typename T>
    struct is_vector<ublas::vector<T>> : std::true_type{};
    template <typename T>
    constexpr bool is_vector_v = is_vector<T>::value;
    
    template <typename T, std::enable_if_t<
    is_vector_v<T>, nullptr_t> = nullptr>
    typename T::value_type get_vector_value(const T& v) {
        return *(v.begin());
    }
    template <typename T, std::enable_if_t<
    !is_vector_v<T>, nullptr_t> = nullptr>
    int get_vector_value(const T& v) {
        return 0;
    };
    
    //is_tuple
   
    //is_int
   
    //has_iterator type1 (関数を使う)
   
    //has_iterator type2 (関数の宣言のみ使う、std::true_type, false_type)
   
    //has_iterator type3 (継承を使って、Baseクラスのvalueを呼ぶ。std::true_typeかfalse_typeのいずれかを継承する事になる)
    struct has_iterator_impl {
        template <typename T>
        static auto check(T*)
        -> decltype(typename T::iterator{}, std::true_type{});
        template <typename T>
        static auto check(...) -> std::false_type;
    };
    
    template <typename T>
    struct has_iterator :
        decltype(has_iterator_impl::check<T>(nullptr)){};
    template <typename T>
    constexpr bool has_iterator_v = has_iterator<T>::value;
    
    struct has_value_type_impl {
        template <typename T>
        static auto check(T*) -> decltype(typename T::value_type{}, std::true_type{});
        template <typename T>
        static auto check(...) -> std::false_type;
    };
    template <typename T>
    struct has_value_type
    : decltype(has_value_type_impl::check<T>(nullptr)){};
    
    template <typename T>
    constexpr bool has_value_type_v
    = has_value_type<T>::value;
    
    template <typename T,
    std::enable_if_t<has_iterator_v<T> && has_iterator_v<T>, nullptr_t> = nullptr>
    typename T::value_type get_iterator_sum(const T& x) {
        return std::accumulate(x.begin(), x.end(), typename T::value_type(0));
    };
    template <typename T,
    std::enable_if_t<!(has_iterator_v<T> && has_iterator_v<T>),
    nullptr_t> = nullptr>
    int get_iterator_sum(const T& x) {
        return 0;
    };
    
    // メンバ変数value があるかどうかをチェックする
   
    //　メンバ関数f()を持っているかをチェックする
   
    //class がhogeという名前のメンバ変数またはメンバ関数を持つかチェックする。
   
    // Tが代入可能か(assignable)？
   
    //detected idiom (void_t)
   
    //T がsort メンバ関数を持っているかチェック
    
    //T が関数funcに適応可能

}

#endif //MODERNCPP_METAFUNCITONS2_H
