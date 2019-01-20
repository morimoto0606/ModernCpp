//
// Created by MORIMOTO on 2018/01/04.
//

#ifndef MODERNCPP_CONCEPTOFF_H
#define MODERNCPP_CONCEPTOFF_H

namespace concept {
    struct has_f_impl {
        template <typename X, typename Y>
        static auto check(X*, Y*) -> decltype(
        std::declval<X>() + std::declval<Y>(), std::true_type());
        template <typename X, typename Y>
        static auto check(...) -> std::false_type;
    };
    
    template <typename X, typename Y>
    struct has_f : public decltype(
        has_f_impl::check<X, Y>(nullptr, nullptr)){
    };
}

#endif //MODERNCPP_CONCEPTOFF_H
