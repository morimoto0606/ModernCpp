//
// Created by MORIMOTO on 2018/01/04.
//

#ifndef MODERNCPP_ANY_H
#define MODERNCPP_ANY_H
namespace erase {
    class any {
    public:
       
        ~any() {
            std::cout << "delete content" << std::endl;
            delete _content;
        }

        //型消去を活用して、Tの型を変更している
        template<typename T>
        any& operator=(const T &value) {
            std::cout << "any : T operator = of any" << std::endl;
            delete _content;
            _content = new holder<T>(value);
            return *this;
        }
        any& operator=(const any& other) {
            std::cout << "any : any operator = " << std::endl;
            delete _content;
            _content = other._content ?
                       other._content->clone() : nullptr;
            return *this;
        }
       
         // 型消去を使っている
        template<typename T>
        any(const T& value)
        : _content(new holder<T>(value)) {
            std::cout << "any : T copy constructor" << std::endl;
        }
        any(const any& other) : _content(other._content ? other._content->clone()
                                                        : nullptr){
            std::cout << "any : any copy constructor " << std::endl;
        }
        
        const std::type_info& type() const {
            return _content ? _content->type() : typeid(void);
        }
    private:
        struct holder_base {
            virtual ~holder_base() {}
            virtual holder_base* clone() const = 0;
            virtual const std::type_info& type() const = 0;
        };
        
        template<typename T>
        struct holder : public holder_base {
            T _value;
            
            holder(const T &value) : _value(value) {}
            
            virtual holder_base* clone() const override {
                return new holder(_value);
            }
            
            virtual const std::type_info& type() const override
            {
                return typeid(T);
            }
        };
        
        holder_base* _content;
    };
}
#endif //MODERNCPP_ANY_H
