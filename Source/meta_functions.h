//
// Created by MORIMOTO on 2017/12/23.
//

#ifndef MODERNCPP_META_FUNCTIONS_H
#define MODERNCPP_META_FUNCTIONS_H

#include <type_traits>
#include <tuple>
#include <vector>
#include <algorithm>

namespace meta_functions {
    
    //is_pointer
    template <typename T>
    struct is_pointer : std::false_type{};
    template <typename T>
    struct is_pointer<T*> : std::true_type{};
    template <typename T>
    constexpr bool is_pointer_v = is_pointer<T>::value;
    
    //is_vector
    template <typename T>
    struct is_vector : std::false_type{};
    template <typename T>
    struct is_vector<std::vector<T>> : std::true_type{};
    template <typename T>
    constexpr bool is_vector_v = is_vector<T>::value;
    
    //is_tuple
    template <typename ...T>
    struct is_tuple : std::false_type{};
    template <typename ...T>
    struct is_tuple<std::tuple<T...>> : std::true_type{};
    template <typename ...T>
    constexpr bool is_tuple_v = is_tuple<T...>::value;
    
    //is_int
    template <typename T>
    struct is_int {
        static constexpr bool value = false;
    };
    template <>
    struct is_int<int> {
        static constexpr bool value = true;
    };
    template <typename T>
    constexpr bool is_int_v = is_int<T>::value;
    
    
    // Enable_if によるオーバーロード
    template <typename T, std::enable_if_t<is_int_v<T>, nullptr_t >
        = nullptr>
    void f1(const T& x) {
        std::cout << "This is int f1" << std::endl;
    };
    template <typename T, std::enable_if_t<!is_int_v<T>, nullptr_t >
        = nullptr>
    void f1(const T& x) {
        std::cout << "This is not int f1" << std::endl;
    };
    
    //has_iterator type1 (関数を使う)
    template <typename T>
    class has_iterator1 {
        template <typename U>
        static constexpr bool check(typename U::iterator*)
        {
            return true;
        }
        template <typename U>
        static constexpr bool check(...)
        {
            return false;
        }
    public:
        static constexpr bool value = check<T>(nullptr);
    };
    template <typename T>
    constexpr bool has_iterator1_v = has_iterator1<T>::value;
    
    //has_iterator type2 (関数の宣言のみ使う、std::true_type, false_type)
    template <typename T>
    class has_iterator2 {
        template<typename U>
        static constexpr std::true_type check(
            typename U::iterator*);
        template <typename U>
        static constexpr std::false_type check(
            ...);
    public:
        static constexpr bool value = decltype(check<T>(nullptr))::value;
    };
    template <typename T>
    constexpr bool has_iterator2_v = has_iterator2<T>::value;
    
    //has_iterator type3 (継承を使って、Baseクラスのvalueを呼ぶ。std::true_typeかfalse_typeのいずれかを継承する事になる)
    struct has_iterator3_impl {
        template <typename U>
        static std::true_type check(typename U::iterator*);
        template <typename U>
        static std::false_type check(...);
    };
    template <typename T>
    struct has_iterator3 : decltype(has_iterator3_impl::check<T>(nullptr)){};
    template <typename T>
    constexpr bool has_iterator3_v = has_iterator3<T>::value;
    
    // メンバ変数value があるかどうかをチェックする
    struct has_value_impl {
        template <typename T>
        static std::true_type check(decltype(T::value)*);
        template <typename T>
        static std::false_type check(...);
    };
    template <typename T>
    struct has_value : decltype(has_value_impl::check<T>(nullptr))
    {};
    template <typename T>
    constexpr bool has_value_v = has_value<T>::value;
    
    //　メンバ関数f()を持っているかをチェックする
    struct has_f_impl {
        template <typename T>
        static auto check(T x)->decltype(x.f(), std::true_type{});
        template <typename T>
        static auto check(...)-> std::false_type;
    };
    template <typename T>
    struct has_f : decltype(has_f_impl::check<T>(std::declval<T>())){};
    template <typename T>
    constexpr bool has_f_v = has_f<T>::value;
    
    //class がhogeという名前のメンバ変数またはメンバ関数を持つかチェックする。
    struct has_member_impl {
        template <typename T>
        static std::true_type check(decltype(&T::hoge));
        template <typename T>
        static std::false_type check(...);
    };
    template <typename T>
    struct has_member
    : decltype(has_member_impl::check<T>(nullptr)) {};
    template <typename T>
    constexpr bool has_member_v = has_member<T>::value;
    
    // Tが代入可能か(assignable)？
    struct is_assignable_impl {
        template <typename T>
        static auto check(T x, const T y)
        -> decltype(x=y, std::true_type{});
        //上以外の関数を定義する際に、template<typename T>不要
        static auto  check(...)->std::false_type;
    };
    template <typename T>
    struct is_assignable :
        decltype(is_assignable_impl::check(
        std::declval<T>(), //std::declval()のstdと()は必要
        std::declval<T>())) {};
    template <typename T>
    constexpr bool is_assignable_v = is_assignable<T>::value;
    
    //detected idiom (void_t)
    template <typename ...>
    using void_t = void;
    
    template <typename T, typename = void>
    struct is_equality_comparable : std::false_type{};
   
    template <typename T>
    struct is_equality_comparable<T, void_t<
    decltype(std::declval<T&>() == std::declval<T&>())>>
    : std::true_type{};
    
    //T がsort メンバ関数を持っているかチェック
    struct has_sort_impl {
        template <typename T>
        static auto check(T*) -> decltype(
        std::declval<T>().sort(), std::true_type{});
        template <typename T>
        static auto check(...) -> std::false_type;
    };
    template <typename T>
    struct has_sort : decltype(has_sort_impl::check<T>(nullptr)) {};
    template <typename T>
    constexpr bool has_sort_v = has_sort<T>::value;
    
    template <typename T, std::enable_if_t<
    has_sort_v<T>, nullptr_t> = nullptr>
    void generalSort(T&& x) {
        x.sort();
    }
    template <typename T, std::enable_if_t<
    !has_sort_v<T>, nullptr_t> = nullptr>
    void generalSort(T&& x) {
        std::sort(std::begin(x), std::end(x));
    }
    
    struct X{
        //X& operator=(const X& other) = delete;
    };
    int func(double x) {
        return 1;
    }
    int func(const X& x) {
        return 2;
    }
    struct has_func_impl {
        template <typename T>
        static auto check(T* x) -> decltype(func(*x), std::true_type{});
        template <typename T>
        static auto check(...) -> std::false_type;
    };
    
    //check<T>としないと型Tのことを判断出来ないので注意
    template <typename T>
    struct has_func : decltype(has_func_impl::check<T>(nullptr)){};
    
    template <typename T>
    constexpr bool has_func_v = has_func<T>::value;
    
    template <typename T, std::enable_if_t<has_func_v<T>, nullptr_t> = nullptr>
    int get_func_value(const T& x) {
        return func(x);
    };
    template <typename T, std::enable_if_t<!has_func_v<T>, nullptr_t> = nullptr>
    int get_func_value(const T& x) {
        return 0;
    };
    
}

#endif //MODERNCPP_META_FUNCTIONS_H
