//
// Created by MORIMOTO on 2017/09/14.
//

#ifndef CPPTEMPLATE_META_H
#define CPPTEMPLATE_META_H

namespace meta {
    template <int N>
    struct hoge {
        static const int value = N;
    };

    template <int N>
    struct hoge2 {
        enum {
            value = N
        };
    };

    template <int N>
    struct increment {
        static constexpr int value = N + 1;
    };

    template <int N>
    struct factorial {
        static const int value
        = N * factorial<N-1>::value;
    };
    template <>
    struct factorial<1> {
        static const int value = 1;
    };
    template <int N>
    struct square {
        static constexpr int value = N * N;
    };

    template <int N, int M>
    struct power {
        static constexpr int value
        = power<N, M-1>::value * N;
    };
    template <int N>
    struct power<N, 1> {
        static constexpr int value = N;
    };

    //constexpr関数はコンパイル時に計算される。
    constexpr int pow(int x, int n) {
        return n == 0 ? 1: x * pow(x, n-1);
    }
    //型を操作するメタ関数
    template <class T>
    struct identify {
        using type = T;
    };

    template <class T>
    struct add_pointer {
        typedef T* type;
    };

    template <class T>
    struct add_const_lvalue_reference {
        using type = const T&;
    };

    template <class T>
    struct remove_const {
        using type = T;
    };
    template <class T>
    struct remove_const<const T> {
        using  type = T;
    };

    //compile時if文
    template <bool Cond, class Then, class Else>
    struct if_;
    template <class Then, class Else>
    struct if_<true, Then, Else> {
        using type = Then;
    };
    template <class Then, class Else>
    struct if_<false, Then, Else> {
        using type = Else;
    };

    struct is_even {
        using result_type = bool;
        bool operator()(int x ) const
        {
            return x % 2 == 0;
        }
    };
    template <int N>
    struct is_evenmeta {
        static constexpr bool value
        = N % 2 == 0;
    };

    template <bool Cond, class Then, class Else>
    struct if_c;

    template <class Then, class Else>
    struct if_c<true, Then, Else> {
        using type = Then;
    };
    template <class Then, class Else>
    struct if_c<false, Then, Else> {
        using type = Else;
    };
    template <class Cond, class Then, class Else>
    struct ifmeta_ : public if_c<Cond::value, Then, Else> {};

    //meta function
    template <class T>
    T* add_pointer2();

    template <class T>
    T* add_pointer3(T);

#define DECLVAL(x) std::declval<x>()

    // add_pointers meta function
    // 各型の静的な値を表す型
    template <int N> struct int_{};
    template <bool B> struct bool_{};
    //　各型の静的な状態をあらわすタグ
    struct cont{};
    struct end{};

    template <bool Cond>
    auto is_end(bool_<Cond>) -> typename
    std::conditional<Cond, end, cont>::type;

    //再帰テンプレート
    template <class T, int N>
    auto add_pointers_impl(T, int_<N>, cont)
        -> decltype(add_pointers_impl(
    
    std::declval<T*>(),
    int_<N-1>(),
    std::declval<decltype(
    is_end(bool_<N -1 == 0>())
    )>()
    ));
    
    template <class T, int N>
    auto add_pointers_impl(T, int_<N>, end) -> T;
    
    template <class T, int N>
    auto add_pointers(T, int_<N>)
    -> decltype(add_pointers_impl(
        std::declval<T>(),
        int_<N>(),
        std::declval<decltype(
            is_end(bool_<N == 0>())
        )>()
    ));
    
    
    class IType {
    public:
        virtual ~IType(){}
        virtual int getNum() const = 0;
    };
    
    class AType : public IType {
    public:
        AType() = default;
        int getNum() const override
        {
            int a = 3;
            return a;
        }
        
    };
    
    
    class BType : public IType {
    public:
        virtual int getNum() const override
        {
            return 2;
        }

    };

    template <typename T>
    int num(const T& type) {
        return 100;
    }
    template <>
    int num(const BType& type)
    {
        return 30;
    }

    class Hoge {
    public:
        Hoge(const IType& type) {
            std::cout << num(type) << std::endl;
        }

    };

}
#endif //CPPTEMPLATE_META_H
