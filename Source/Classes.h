//
// Created by MORIMOTO on 2017/10/14.
//

#ifndef CPPTEMPLATE_CLASSES_H
#define CPPTEMPLATE_CLASSES_H

#include <iostream>
#include <cassert>
#include <vector>
#include <memory>
#include <initializer_list>
#include <mach/notify.h>

namespace classes {
   class vector {
   public:
       
       vector(const std::size_t n, double d)
       : _mysize{n}, _data{new double[_mysize]} {
           std::cout << "called vector constructor" << std::endl;
           for (std::size_t i = 0; i < n; ++i) {
               _data[i] = d + i;
           }
       }
       
       vector(const std::size_t n)
       : vector{n, 0} {}
       
       ~vector(){
           std::cout << "called vector destructor" << std::endl;
           delete[] _data;
       }
       // move constructor
       vector(vector&& v)
       : _mysize(v._mysize), _data(v._data){
           std::cout << "called vector move constructor" << std::endl;
           v._data = 0;
           v._mysize = 0;
       }
       
       //move assignment
       vector& operator=(vector&& src)
       {
           assert(_mysize == 0 || _mysize == src._mysize);
           std::swap(_data, src._data);
           return *this;
       }
       
       std::size_t  getMysize() const
       {
           return _mysize;
       }
       
       double* getData() const {
           return _data;
       }
       

   private:
       std::size_t _mysize;
       double* _data;
   };
    
    class Polynomial {
    public:
        Polynomial(const std::size_t& degree)
        : _coeff(std::make_unique<std::vector<double>>(degree))
        {}
        Polynomial(std::initializer_list<double> values)
        : _coeff(std::make_unique<std::vector<double>>(values.size()))
        {
            std::copy(std::begin(values), std::end(values),
                _coeff->begin());
        }
        
        Polynomial(const Polynomial&) = default;
        Polynomial(Polynomial&&) = default;
        Polynomial& operator=(const Polynomial& rhs)
        {
            std::cout << "called copy assignment operator" << std::endl;
            for (std::size_t i = 0; i < _coeff->size(); ++i) {
                (*_coeff)[i] = (*(rhs._coeff))[i] -1.;
            }
            return *this;
        }
        Polynomial& operator=(Polynomial&& rhs) {
            std::cout << "called move assignment operator" << std::endl;
            assert(rhs._coeff->size() == _coeff->size());
            std::swap(rhs._coeff, this->_coeff);
            return *this;
        }
        ~Polynomial() = default;
        
        void output() const {
            int i = 0;
            for (double a : *_coeff) {
                std::cout << a << "x^" << i << std::endl;
                ++i;
            }
        }
        
        void setCoeffs(const std::vector<double>& c) {
            assert(c.size() == _coeff->size());
            for (std::size_t i = 0; i < c.size(); ++i) {
                (*_coeff)[i] = c[i];
            }
        }
        
    private:
        std::unique_ptr<std::vector<double>> _coeff;
    };
    
    class MyVect {
    public:
        MyVect(const std::initializer_list<double>& elements)
        : _elements(std::make_unique<std::vector<double>>(
        elements.size()))
        {
            std::copy(elements.begin(), elements.end(),
            _elements->begin());
        }
        
        MyVect(MyVect&& rhs)
        : _elements(std::make_unique<std::vector<double>>(*(rhs._elements))){
            //std::copy(rhs._elements->begin(), rhs._elements->end(),
            //this->_elements->begin());
        }
        
        void print() const {
            for (auto v : *_elements) {
               std::cout << v << std::endl;
            }
        }
        
    private:
        std::unique_ptr<std::vector<double>> _elements;
    };
    
    class MyVect2 {
    public:
        MyVect2(std::initializer_list<double> data)
        : _mySize(data.size()), _data(new double[_mySize])
        {
            std::copy(data.begin(), data.end(),
                      &_data[0]);
                      
        }
        void output() {
           for (std::size_t i = 0; i < _mySize; ++i) {
               std::cout << _data[i] << std::endl;
           }
        }
    private:
        int _mySize;
        std::unique_ptr<double[]> _data;
    };
    
    

}

#endif //CPPTEMPLATE_CLASSES_H
