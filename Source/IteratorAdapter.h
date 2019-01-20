//
// Created by MORIMOTO on 2018/01/07.
//

#ifndef MODERNCPP_ITERATORADAPTER_H
#define MODERNCPP_ITERATORADAPTER_H

#include <iostream>
#include <algorithm>
#include <memory>
#include <boost/iterator_adaptors.hpp>

namespace ita {
    
    class container {
    private:
        int _values[100];

    public:
        struct iterator : public boost::iterator_adaptor<iterator, int*>
        {
            iterator(int* p) : iterator::iterator_adaptor(p){}
        };
        
        container() {
            for(int i = 0; i < 100; ++i) {
                _values[i] = i;
            }
        }
        
        iterator begin() { return iterator(_values);}
        iterator end() { return iterator(_values + 100);}
    };
    
  
}

#endif //MODERNCPP_ITERATORADAPTER_H
