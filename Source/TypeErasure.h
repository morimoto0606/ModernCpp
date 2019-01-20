//
// Created by MORIMOTO on 2018/01/03.
//

#ifndef MODERNCPP_TYPEERASURE_H
#define MODERNCPP_TYPEERASURE_H

namespace erase {
    // type erasureをするために用意////////////////
    class base {
    public:
        virtual ~base() {
            std::cout << "base destructor" << std::endl;
        }
    };
    template <typename T>
    class derived : public base {
    public:
        derived(const T& value)
        : _value(value) {
            std::cout << "derived constructor" << std::endl;
        }
        virtual ~derived() {
            std::cout << "derived destructor" << std::endl;
        }
    private:
        T _value;

    };
    ///////////////////////////////////////////
    
    //作りたいクラス
    class X {
    public:
        template <typename T>
        X (const T& value) {
            std::cout << "X constructor" << std::endl;
            _value = new derived<T>(value);
        }
        ~X() {
            std::cout << "X destructor" << std::endl;
            delete _value;}
    
    private:
        base* _value;
        
    };
    //////////////////////////////////////////
    //custom deleter in shared_ptr sample//////////////////////
    class shared_deleter_base {
    public:
        shared_deleter_base() {
            std::cout << "construct shared deleter base" << std::endl;
        }
        virtual ~shared_deleter_base() {
            std::cout << "destruct shared deleter base" << std::endl;
        }
        virtual void destroy() = 0;
    };
    template <typename T, typename D>
    class shared_deleter : public shared_deleter_base
    {
    public:
        shared_deleter(T* obj, D deleter)
        : _obj(obj), _deleter(deleter) {
            std::cout << "construct shared deleter" << std::endl;
        }
        virtual void destroy() override {
            _deleter(_obj);
        }
    private:
        T* _obj;
        D _deleter;
    };
    
    template <typename T>
    class shared_ptr {
    public:
        explicit shared_ptr(T* obj) : _obj(obj), _deleter(nullptr){
            std::cout << "constructor of shared_ptr" << std::endl;
        }
        
        //custom deleter を使用するバージョン
        template <typename D>
        shared_ptr(T* obj, D deleter) : _obj(obj)
        {
            std::cout << "constructor of shared_ptr with custom deleter" << std::endl;
            _deleter = new shared_deleter<T, D>(_obj, deleter);
        }
        ~shared_ptr(){
            std::cout << "destructor of shared_ptr" << std::endl;
            if (_deleter) {
                std::cout << "called custom deleter" << std::endl;
                _deleter->destroy();
                delete(_deleter);
            } else {
                delete(_obj);
            }
        }
        T* operator->() const {
            return _obj;
        }
    private:
        T* _obj;
        shared_deleter_base* _deleter;
    };
    
    struct deleter {
        template <typename T>
        void operator()(T* obj){
            std::cout << "this is my deleter" << std::endl;
            delete(obj);
        }
    };
    
    
}
#endif //MODERNCPP_TYPEERASURE_H
