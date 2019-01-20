//
// Created by MORIMOTO on 2017/11/25.
//

#ifndef MODERNCPP_METATUNING_H
#define MODERNCPP_METATUNING_H

#include <memory>
namespace mt {
    template <int N>
    struct fsize_assign
    {
        template <typename Target, typename Source>
        void operator()(Target& tar, const Source& src)
        {
            fsize_assign<N-1>()(tar, src);
            std::cout << "assign entry" << N << std::endl;
            tar._data[N] = src._data[N];
        }
    };
    
    template <>
    struct fsize_assign<0>
    {
        template <typename Target, typename Source>
        void operator()(Target& tar, const Source& src)
        {
            std::cout << "assign entry" << 0 << std::endl;
            tar._data[0] = src._data[0];
        }
    };
    
    template <typename T, int Size>
    class fsize_vector {
    public:
        fsize_vector(): _data(new T[Size]) {}
        fsize_vector(
            std::initializer_list<T> data)
        : _data(new T[Size])
        {
           std::copy(data.begin(), data.end(), &_data[0]);
        }
        fsize_vector<T, Size>& operator =(
            const fsize_vector<T, Size>& that)
        {
            fsize_assign<_size-1>{}(*this, that);
            return *this;
        }
        template <typename Vector>
        fsize_vector<T, Size>& operator =(
            const Vector& that)
        {
            fsize_assign<_size-1>{}(*this, that);
            return *this;
        }
        
        T&operator[](int i) {
            return *_data[i];
        }

    public:
        std::unique_ptr<T[]> _data;
        static constexpr int _size = Size;
    };
    
    template <typename Matrix, typename Vector>
    struct mat_vect_et
    {
        const static int _myRows = Matrix::_myRows;
        const static int _myCols = Matrix::_myCols;
        
        mat_vect_et(const Matrix& A, const Vector& v)
        : _a(A), _v(v) {}
        
        const Matrix& _a;
        const Vector& _v;
    };
    
    template <int Row, int Col>
    struct fsize_mat_vec_mult
    {
    
    };
    
    
    template <typename T, int Rows, int Cols>
    class fsize_matrix
    {
        static_assert(Rows > 0, "Rows must be larger than 0.");
        static_assert(Cols > 0, "Cols must be larger than 0.");
        
        using self = fsize_matrix;

    public:
        using value_type = T;
        const static int _myRows = Rows;
        constexpr static int _myCols = Cols;
       
        fsize_matrix() {
            for (int i = 0; i < Rows; ++i) {
                for (int j = 0; j < Cols; ++j) {
                    _data[i][j] = T(0);
                }
            }
        }
        fsize_matrix(const self& that) {
            for (int i = 0; i < Rows; ++i) {
                for (int j = 0; j < Cols; ++j) {
                    _data[i][j] = that._data[i][j];
                }
            }
        }
        
        const T* operator[](int r) const { return _data[r];}
        T* operator[](int r) { return _data[r];}
        
        mat_vect_et<self, fsize_vector<T, Cols>>
        operator*(const fsize_vector<T, Cols>& v) const {
            return {*this, v};
        }
        

    private:
        T _data[Rows][Cols];
    };
    
   
}


#endif //MODERNCPP_METATUNING_H
