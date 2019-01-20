//
// Created by MORIMOTO on 2017/10/22.
//

#ifndef CPPTEMPLATE_ALGORITHM_H
#define CPPTEMPLATE_ALGORITHM_H

#include "GenericProgramming.h"
#include <sstream>
namespace alg {
    
    int evaluate(const std::vector<std::string>& vec)
    {
        generic::stack<int, 3> stack;
        for (std::string v : vec) {
            if (v == "+") {
               stack.push(stack.pop() + stack.pop());
            }
            else if (v == "-") {
                stack.push(-stack.pop() + stack.pop());
            }
            else if (v == "*") {
                stack.push(stack.pop() * stack.pop());
            }
            else {
                int i;
                std::istringstream ss(v);
                ss >> i;
                stack.push(i);
            }
            std::cout << "top is ";
            std::cout << stack.top() << std::endl;
            std::cout << " stack size is full ?"  << stack.isFull() << std::endl;
            std::cout << "stac size is " << stack.top() << std::endl;
        }
        return stack.pop();
    }

}
#endif //CPPTEMPLATE_ALGORITHM_H
