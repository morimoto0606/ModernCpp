//
// Created by MORIMOTO on 2018/01/07.
//

#ifndef MODERNCPP_ITERATOR_H
#define MODERNCPP_ITERATOR_H

#include <boost/numeric/ublas/vector.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <memory>
namespace it {
    struct my_list_node {
        int _data;
        std::shared_ptr<my_list_node> _next;
    };
    
    using my_list = std::shared_ptr<my_list_node>;
    
    //my_listの例を作る
    my_list create_list()
    {
        my_list root = std::make_shared<my_list_node>();
        root->_data = 0;
        my_list p = root;
        for (int i = 1; i < 100; ++i) {
            p->_next = std::make_shared<my_list_node>();
            p->_data = i;
            p = p->_next;
        }
        return root;
    }
    
    //my_list_用のイテレータを作る。
    class my_list_iterator : public boost::iterator_facade<
        my_list_iterator,
        int,
        boost::forward_traversal_tag>
    {
    private:
        std::shared_ptr<my_list_node> _p;
    public:
        my_list_iterator() {}
        explicit my_list_iterator(std::shared_ptr<my_list_node> p)
        : _p(p){}

    private:
        friend class boost::iterator_core_access;
        void increment() {_p = _p->_next;}
        int& dereference() const { return _p->_data;}
        bool equal(const my_list_iterator& other) const {
            return _p == other._p;
        }
    };
    
    my_list_iterator begin(my_list& p) {
        return my_list_iterator(p);
    }
    
    my_list_iterator end(my_list& p)  {
        return my_list_iterator();
    }
    void print(int value) {
        std::cout << value << " " ;
    }
    
    
}

#endif //MODERNCPP_ITERATOR_H
