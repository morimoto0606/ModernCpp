//
// Created by MORIMOTO on 2017/12/17.
//

#ifndef MODERNCPP_CLASSTEMPLATE_H
#define MODERNCPP_CLASSTEMPLATE_H

#include <vector>
#include <cassert>

namespace {
    template <typename T>
    class Stack {
    private:
        std::vector<double> _elems;
    public:
        void push(const T& elem);
        void pop();
        const T& top() const;
        bool empty() const {
            return _elems.empty();
        }
    };
    
    template <typename T>
    void Stack<T>::push(const T &elem) {
        _elems.push_back(elem);
    }
    
    template <typename T>
    void Stack<T>::pop() {
        assert(!_elems.empty());
        _elems.pop_back();
    }
}


#endif //MODERNCPP_CLASSTEMPLATE_H
