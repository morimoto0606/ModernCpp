//
// Created by MORIMOTO on 2017/12/19.
//

#ifndef MODERNCPP_VARIOUSOVERLOAD2_H
#define MODERNCPP_VARIOUSOVERLOAD2_H
namespace tag {
   
    struct unirateral_type{};
    struct birateral_type{};
   
    double cva_func(double x, unirateral_type)
    {
        std::cout << "unirateral type" << std::endl;
        return 2 * x;
    }
    double cva_func(double x, birateral_type)
    {
        std::cout << "birateral_type" << std::endl;
        return -x;
    }
    
    template <typename T>
    struct cva_traits {
        using type = unirateral_type;
    };
    template <>
    struct cva_traits<birateral_type> {
        using type = birateral_type;
    };
   
    template <typename T>
    double calc_cva(double x, T tag)
    {
        double d = cva_func(
        x, typename cva_traits<T>::type{});
        return d;
    }
    
    
}

#endif //MODERNCPP_VARIOUSOVERLOAD2_H
