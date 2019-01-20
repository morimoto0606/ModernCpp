//
// Created by MORIMOTO on 2017/11/21.
//

#ifndef MODERNCPP_EXPRESSIONTEMPLATE_H
#define MODERNCPP_EXPRESSIONTEMPLATE_H

#include <initializer_list>
#include <algorithm>

namespace et {
    template <typename V1, typename V2> class vector_sum;
    template <typename T>
    class vector {
    public:
        using value_type = T;
    public:
        explicit vector(int size)
        : _size(size),
        _data(new T[_size]){}
       
        vector(std::initializer_list<T> values)
        : _size(values.size()), _data(new T[_size])
        {
            std::copy(std::begin(values), std::end(values),
            &_data[0]);
        }
        
        vector& operator =(std::initializer_list<T> values)
        {
            std::copy(std::begin(values), std::end(values),
            std::begin(_data));
            return *this;
        }
        
        template <typename Src>
        vector& operator =(const Src& that)
        {
            for (int i = 0; i < _size; ++i) {
                _data[i] = that[i];
            }
            return *this;
        }
        
        const T& operator[](int i) const
        {
            return _data[i];
        }
        T& operator[](int i)
        {
            return _data[i];
        }
        int size() const
        { return _size;}
    private:
        int _size;
        std::unique_ptr<T[]> _data;
        
    };
    

    
    template <typename V1, typename V2>
    class vector_sum
    {
    public:
        using value_type = std::common_type_t<
        typename V1::value_type,
        typename V2::value_type>;
        
    public:
        vector_sum(const V1& v1, const V2& v2)
        : _v1(v1), _v2(v2) {}
        
        friend int size(const vector_sum& x) { return std::size(x);}
        value_type operator[](int i) const
        { return _v1[i] + _v2[i]; }
        
        
    private:
        const V1 &_v1;
        const V2 &_v2;
    };
    
    template <typename V1, typename V2>
    inline vector_sum<V1, V2> operator+(
        const V1& x, const V2& y)
    {
        return {x, y};
    }
    
}

#endif //MODERNCPP_EXPRESSIONTEMPLATE_H
