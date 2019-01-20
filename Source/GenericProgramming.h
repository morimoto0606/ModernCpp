//
// Created by MORIMOTO on 2017/10/15.
//

#ifndef CPPTEMPLATE_GENERICPROGRAMMING_H
#define CPPTEMPLATE_GENERICPROGRAMMING_H

#include <complex>
namespace generic {
    template <typename T>
    inline T max(T x, T y)
    {
        return x > y ? x : y;
    }
    
    template <typename T>
    inline void swap(T& x, T& y)
    {
        T tmp(x);
        x = y;
        y = tmp;
    }
    
    template <typename T>
    class vector
    {
    public:
        explicit vector(int size)
        : _mySize(size), _data(new T[_mySize])
        {
            std::cout << "called vector constructor" << std::endl;
        }
        
        explicit vector(std::initializer_list<T> data)
        : _mySize(data.size()), _data(new T[_mySize]) {
            std::copy(data.begin(), data.end(), &_data[0]);
        }
        
        ~vector() {
            std::cout << "called vector destructor" << std::endl;
        }
        int size() const {
            return _mySize;
        }
        vector(const vector& that)
        : _mySize(that._mySize), _data(new T[_mySize])
        {
            std::copy(&that._data[0],
                      &that._data[that._mySize],
            &(this->_data[0]));
            
            std::cout << "called vector copy constructor" << std::endl;
        }
        
        using iterator = T*;
        using const_iterator = const T*;
        
        iterator begin()
        {
            return &_data[0];
        }
        const iterator cbegin() const
        {
            return &_data[0];
        }
        
        iterator end()
        {
            return &_data[_mySize];
        }
        iterator cend() const
        {
            return &_data[_mySize];
        }
        
    private:
        int _mySize;
        std::unique_ptr<T[]> _data;
    };
   
    
    template <typename T, unsigned N>
    T sum(const T (&array)[N])
    {
        T sum(0);
        for (unsigned i = 0; i < N; ++i) {
            sum += array[i];
        }
        return sum;
    };
    
    template <typename T>
    struct list_entry
    {
        list_entry(const T& value)
        : _value(value), _next(0)
        {}
        
        T _value;
        list_entry<T>* _next;
    };
    

    template <typename T>
    struct list_iterator {
        using value_type = T;
        
        list_iterator(list_entry<T>* entry) : _entry(entry) {}
        T &operator *() {
            return _entry->_value;
        }
        
        const T& operator*() const {
            return _entry->_value;
        }
        
        list_iterator<T> operator ++() {
            _entry = _entry->_next;
            return *this;
        }
        
        bool operator !=(const list_iterator<T>& other) const {
            return _entry != other._entry;
        }
        list_entry<T>* _entry;
    };
    
    template <typename Iter, typename T>
    inline T sum(Iter it, Iter end, T init)
    {
        for (; it != end; ++it) {
            init += *it;
        }
        return init;
    };
    
    
    template <typename T>
    struct list
    {
        list() : _first(0) , _last(nullptr) {}
        ~list()
        {
            while (_first) {
                list_entry<T> *tmp = _first->_next;
                delete _first;
                _first = tmp;
            }
        }
        void append(const T& x)
        {
            if (_first != nullptr) {
                _last->_next = new list_entry<T>(x);
                _last = _last->_next;
            }
            else {
                _first = new list_entry<T>(x);
                _last = _first;
            }
            
        }
        
        list_iterator<T> begin() {
            return list_iterator<T>(_first);
        }
        list_iterator<T> end() {
            return list_iterator<T>(nullptr);
        }
        list_entry<T>* _first;
        list_entry<T>* _last;
    };
    
    
    template <typename T>
    class my_list_entry {
    public:
        my_list_entry(const T& value) : _value(value), _next(nullptr) {}

    public:
        T _value;
        std::shared_ptr<my_list_entry> _next;
    };
    
    template <typename T>
    class my_list_iterator {
    public:
        my_list_iterator(const std::shared_ptr<my_list_entry<T>>& entry) {
           _entry = entry;
        }
        const T& operator *(){
            return _entry->_value;
        }
        
        my_list_iterator<T> operator++()
        {
            _entry = _entry->_next;
            return *this;
        }
        
    private:
        std::shared_ptr<my_list_entry<T>> _entry;
    };
    
    
    template <typename T>
    class my_list {
    public:
        my_list() : _first(nullptr), _last(nullptr) {}
        void append(const T& value) {
            if (_first == nullptr) {
                _first = std::make_unique<my_list_entry<T>>(value);
                _last = _first;
            }
            else {
                _last->_next = std::make_unique<my_list_entry<T>>(value);
                _last = _last->_next;
            }
        }
        const my_list_iterator<T>& begin() {
            auto itr = std::make_unique<my_list_iterator<T>>(_first);
            return *itr;
        }

    public:
        std::shared_ptr<my_list_entry<T>> _first;
        std::shared_ptr<my_list_entry<T>> _last;
    };
    
//
//    template <typename T>
//    inline T abs(const T& x) {
//        return x < T(0) ? -x : x;
//    }
//
//    template <typename T>
//    inline T abs(const std::complex<T>& x) {
//        return sqrt(std::real(x) * std::real(x)
//        + std::imag(x) * std::imag(x));
//    }
    
    template <typename T>
    struct abs_functor
    {
        using result_type = T;
        T operator()(const T& x)
        {
            return x < T(0) ? -x : x;
        }
    };
    
    template <typename T>
    struct abs_functor<std::complex<T>>
    {
        using result_type = T;
        T operator()(const std::complex<T>& x) {
            return std::sqrt(std::real(x) * std::real(x)
            + std::imag(x) * std::imag(x));
        }
    };
    
    template <typename T>
    typename abs_functor<T>::result_type abs(const T& x)
    {
        return abs_functor<T>()(x);
    }
    
    template <typename T, int Size>
    class fsize_vector {
        using self = fsize_vector;
    public:
        using value_type = T;
        const static int my_size = Size;
        fsize_vector(int s= Size) {assert(s == Size);
            for (int i = 0; i < Size; ++i) {
                _data[i] = 2 * i;
            }
        }
        
        self& operator =(const self& that) {
            std::copy(that._data, that._data + Size, _data);
            return *this;
        }
        
        self operator +(const self& that) const {
            self sum;
            for (int i = 0; i < my_size; ++i) {
                sum._data[i] = _data[i] + that._data[i];
            }
            return sum;
        }
        void print() const {
            for (T x : _data) {
                std::cout << x << std::endl;
            }
        }
    private:
       T _data[my_size];
    };
    
    template <typename T>
    struct sc_f
    {
        double operator()(const T& x) {
            return std::sin(x) + std::cos(x);
        }
    };
    
    template <typename T>
    class psc_f {
    public:
        psc_f(const T& a) : _a(a){}
        double operator()(const T& x) const
        {
            return _a * x * x;
        }
    private:
        T _a;
    };
    template <typename F, typename T>
    T inline fin_diff(F f, const T& x, const T& h)
    {
        return (f(x + h) - f(x)) / h;
    };
    
    template <typename F, typename T>
    class derivative
    {
    public:
        derivative(const F& f, const T& h)
        : _f(f), _h(h) {}
        
        T operator()(const T& x) const
        {
            return (_f(x + _h) - _f(x)) / _h;
        }
    private:
        const F& _f;
        T _h;
    };
    
    using d_psc_f = derivative<psc_f<double>, double>;
    using dd_psc_f = derivative<d_psc_f, double>;
   
    // direct construction
    template <typename F, typename T>
    class second_derivative
    {
    public:
//        second_derivative(const F& f, const T& h)
//        : _h(h), _fp(f, h) {}
//
        second_derivative(F&& f, T&& h)
        : _h(std::move(h)), _fp(std::move(f), std::move(h)) {}
        
        T operator()(const T& x) const
        {
            return (_fp(x + _h) - _fp(x)) / _h;
        }
    private:
        T _h;
        derivative<F, T> _fp;
    };
    
    template <typename F, typename T, unsigned N>
    class nth_derivative
    {
        using prev_derivative = nth_derivative<F, T, N-1>;
    public:
        nth_derivative(F&& f, T&& h)
        : _h(std::move(h)), _fp(std::move(f), std::move(h)){}
        
        T operator()(const T& x) const
        {
            return (_fp(x + _h) - _fp(x)) / _h;
        }
    private:
        T _h;
        prev_derivative _fp;
    };
    
    template <typename F, typename T>
    class nth_derivative<F, T, 1>
    {
    public:
        nth_derivative(const F& f, const T& h)
        : _f(f), _h(h) {}
        
        T operator()(const T& x) const
        {
            return (_f(x + _h) - _f(x)) / _h;
        }
    private:
        const F& _f;
        T _h;
    };

#include <string>
#include <sstream>
    template <typename T>
    std::string to_string(const T& str)
    {
        std::stringstream ss;
        ss << str;
        return ss.str();
    }
    
    template <typename T, unsigned N>
    class stack {
    public:
        stack() : _data{new T[N]}, _top(0) {}
        ~stack() {delete[] _data;}
        T top() const {
            return _data[_top];
        }
        bool isEmpty() const {
            return _top == 0;
        }
        T pop() {
            assert(_top != 0);
            T data = this->top();
            _data[_top] = 0;
            --_top;
            return data;
        }
        void push(const T& x) {
            assert(_top < N);
            ++_top;
            _data[_top] = x;
        }
        bool isFull() const {
            return _top > N - 1;
        }
    private:
        T* _data;
        unsigned _top;
    };
    
    class odd_iterator {
    public:
        odd_iterator() : _value(1) {}
        odd_iterator(const odd_iterator& other)
        : _value(other._value)
        {
            std::cout << "called copy constructor" << std::endl;
        }
        odd_iterator(odd_iterator&& other)
        : _value(other._value)
        {
            other._value = 0;
            std::cout << "called move constructor" << std::endl;
        }
        odd_iterator& operator =(const odd_iterator& other)
        {
            _value = other._value;
            std::cout << "called copy asssignment" << std::endl;
            return *this;
        }
        odd_iterator& operator =(odd_iterator&& other)
        {
            _value = std::move(other._value);
            std::cout << "called move assignment" << std::endl;
            return *this;
        }
        
        bool operator==(const odd_iterator& other) const {
            return this->_value == other._value;
        }
        
        odd_iterator& operator++()
        {
            this->_value += 2;
            return *this;
        }
        
        int operator *() const
        {
            return _value;
        }
    private:
        int _value;
    };
    
    template <typename T, typename ...Args>
    std::unique_ptr<T> make_unique(Args&&... args)
    {
        std::unique_ptr<T> ptr(new T(std::move(args)...));
        return ptr;
    }
 
}



#endif //CPPTEMPLATE_GENERICPROGRAMMING_H
