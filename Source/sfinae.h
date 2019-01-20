//
// Created by MORIMOTO on 2017/09/12.
//

#ifndef CPPTEMPLATE_SFINAE_H
#define CPPTEMPLATE_SFINAE_H

#include <iostream>
namespace sfinae {
    struct widget {
        using value_type = int;
    };
    
    void hoge() {}
    template <class T>
    typename T::value_type get_value_type(T);
    
    template <class T>
    void something(typename T::value_type)
    {
        std::cout << "value_typeを持っている" << std::endl;
    }

    template <class T>
    void something(...)
    {
        std::cout << "それ以外" << std::endl;
    }

    template <class T>
    struct is_void {
        static const bool value = false;
    };

    template <>
    struct is_void<void> {
        static const bool value = true;
    };

    template <class T>
    struct is_pointer {
        static const bool value = false;
    };

    template <class T>
    struct is_pointer<T*> {
        static const bool value = true;
    };

    template <class T>
    constexpr bool has_iterator_impl(
            typename T::iterator*)
    {
        return true;
    }
    template <class T>
    constexpr bool has_iterator_impl(...)
    {
        return false;
    }

    template <class T>
    constexpr bool has_iterator()
    {
        return has_iterator_impl<T>(nullptr);
    }

    template <class T>
    class has_iterator_class {
        template <class U>
        static constexpr bool check(
                typename U::iterator*)
        {
            return true;
        }

        template <class U>
        static constexpr bool check(...)
        {
            return false;
        }

    public:
        static const bool value = check<T>(nullptr);
    };

//decltypeを使用したhas_iteratorメタ関数
#include <type_traits>
    struct has_iterator_impl {
        template  <class T>
        static std::true_type check(typename T::iterator*);

        template <class T>
        static std::false_type check(...);
    };

    template <class T>
    class has_iterator_meta : public decltype(
    has_iterator_impl::check<T>(nullptr)){};


    //型Tがクラスかどうか判定するメタ関数
    struct is_class_impl {
        template <class T>
        static std::true_type check(int T::*);

        template <class T>
        static std::false_type check(...);
    };

    template <class T>
    struct is_class :
            public decltype(is_class_impl::check<T>(nullptr))
    {};

    struct X {};

    //代入可能か判断する
#include <utility>
    struct is_assignable_imple {
        template <class T>
        static auto check(T*) -> decltype(
        std::declval<T&>() = std::declval<const T&>(),
        std::true_type());

        template <class T>
        static auto check(...) -> std::false_type;
    };

    template <class T>
    struct is_assignable : decltype(is_assignable_imple::check<T>(nullptr))
    {};

    struct A {
        A&operator=(const A&) = delete;
    };
    struct B{};

    struct is_addable_imple {
        template <class T, class U>
        static auto check(T*, U*) -> decltype(
        std::declval<T>() + std::declval<U>(),
        std::true_type());

        template<class T, class U>
        static auto check(...) -> std::false_type;
    };

    template<class T, class U>
    struct is_addable : decltype(
                        is_addable_imple::check<T, U>(
    nullptr, nullptr)) {};
    B operator +(const B&, const B&) {
     return B();
    }

}
#endif //CPPTEMPLATE_SFINAE_H
