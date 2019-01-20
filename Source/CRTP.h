//
// Created by MORIMOTO on 2017/12/30.
//

#ifndef MODERNCPP_CRTP_H
#define MODERNCPP_CRTP_H

namespace crtp {
    template<typename T>
    struct cva_function {
        double calc(double x) const {
            return static_cast<const T&>(*this).calc(x);
        }
    };
    
    struct unirateral : public cva_function<unirateral> {
        double calc(double x) const {
            std::cout << "unirateral " << std::endl;
            return x;
        }
    };
    
    struct birateral : public cva_function<birateral>
    {
        double calc(double x) const {
            std::cout << "birateral" << std::endl;
            return -x;
        }
    };
    
    template <typename T>
    double cva_func(const double x,
                    const cva_function<T>& func) {
        return func.calc(x);
    }
    
}

#endif //MODERNCPP_CRTP_H
