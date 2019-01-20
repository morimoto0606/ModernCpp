//
// Created by MORIMOTO on 2017/12/30.
//

#ifndef MODERNCPP_ENABLE_IF_FUNCTION_H
#define MODERNCPP_ENABLE_IF_FUNCTION_H

#include <type_traits>
namespace ene {
    struct birateral {};
    struct uniraeral {};
    
    template <typename T,
    std::enable_if_t<std::is_same_v<T, birateral>,nullptr_t>
    = nullptr>
    double cva_func(double x) {
        std::cout << "birateral" << std::endl;
        return x;
    };
    template <typename T,
    std::enable_if_t<std::is_same_v<T, uniraeral>, nullptr_t>
    = nullptr>
    double cva_func(double x) {
        std::cout << "unirateral" << std::endl;
        return -x;
    };
    
}
#endif //MODERNCPP_ENABLE_IF_FUNCTION_H
