//
// Created by MORIMOTO on 2018/01/04.
//

#ifndef MODERNCPP_CONCEPTOFMIN_H
#define MODERNCPP_CONCEPTOFMIN_H

#include <utility>
#include <type_traits>
namespace concept {
   struct is_less_than_compatible_impl {
       template <typename T, typename U>
       static auto check(T*, U*) -> decltype(
       std::declval<T>() < std::declval<U>(),
       std::true_type());
       
       template <typename T, typename U>
       static auto check(...) -> std::false_type;
   };
    template <typename T, typename U>
    struct is_less_than_compatible :
    decltype(is_less_than_compatible_impl::check<T, U>(nullptr, nullptr))
    {};
    template <typename T, typename U>
    constexpr bool is_less_than_compatible_v = is_less_than_compatible<T, U>::value;
    
    template <typename T>
    const T& min(const T& a, const T& b)
    {
        static_assert(is_less_than_compatible_v<T, T>,
                      "T must be less than compatible!");
        return a < b ? a : b;
    }
   
}
#endif //MODERNCPP_CONCEPTOFMIN_H
