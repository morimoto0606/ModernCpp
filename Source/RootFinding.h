//
// Created by MORIMOTO on 2017/11/22.
//

#ifndef MODERNCPP_ROOTFINDING_H
#define MODERNCPP_ROOTFINDING_H

namespace root {
    template <typename F, typename T>
    T bisection(F f, T ini, T min, T max,
                const double tolerance, int maxiteration)
    {
        T x = ini;
       for (int iter = 0; iter < maxiteration; ++iter)
        {
            T val = f(x);
            if (-tolerance < val && val < tolerance) {
                return x;
            }
            
            if (val > 0){
                max = x;
            }
            else {
                min = x;
            }
            std::cout << iter << std::endl;
            x = 0.5 * (min + max);
        }
        return ini;
    }
   
    template <typename F, typename DF, typename T>
    T newton_raphson(F&& f, DF&& df, T x, const double torelance, int maxiteration)
    {
        for (int i = 0; i < maxiteration; ++i)
        {
            T val = f(x);
            if (-torelance < val && val < torelance)
            {
                return x;
            }
            else {
                x -= val / df(x);
            }
            std::cout << i << std::endl;
        }
        return x;
    }
}
#endif //MODERNCPP_ROOTFINDING_H
