//
// Created by MORIMOTO on 2017/12/24.
//

#ifndef MODERNCPP_POLICY_H
#define MODERNCPP_POLICY_H
namespace policy {
    struct print_type1 {
        static void print() {
            std::cout << "print type 1"  << std::endl;
        }
    };
    
    struct print_type2 {
        static void print() {
            std::cout << "print type2" << std::endl;
        }
    };
    
    template <typename PrintType>
    struct Printer {
        static void print() {
            PrintType::print();
        }
    };
}
#endif //MODERNCPP_POLICY_H
