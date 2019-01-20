//
// Created by MORIMOTO on 2017/11/05.
//

#ifndef CPPTEMPLATE_MOVESEMANTICS_H
#define CPPTEMPLATE_MOVESEMANTICS_H

#include <type_traits>
#include <iostream>
namespace move {
    template <typename T>
    decltype(auto) move(T&& param)
    {
        using ReturnType =
        std::remove_reference_t<T>&&;
        return static_cast<ReturnType>(param);
        
    }
    
    class Text {
    public:
        explicit Text() {
            std::cout << "Text Constructor" << std::endl;
        }
        Text(const Text& other) {
           std::cout << "Text Copy Constructor" << std::endl;
        }
        Text(Text&& other) {
            std::cout << "Text Move Constructor" << std::endl;
        }
        
        Text& operator=(const Text& other) = delete;
        Text& operator=(const Text&& other) = delete;
    
    private:
    };
    class Annotation {
    public:
        //constructor
        explicit Annotation(const Text& text)
        : _value(move::move(text)){}
        
        explicit Annotation(Text&& text)
        : _value(move::move(text)){}
        
    private:
        Text _value;
    };
    
    class Widget {
    public:
        Widget(int a = 0) : _a(a) {}

    public:
        int get() const {
            return _a;
        }
        void set(int a) {
            _a = a;
        }
    private:
        int _a;
    };
    void process(const Widget& lvalArag) {
        std::cout << "called lvalProcess" << std::endl;
    }
    void process(Widget&& rvalArg) {
        
        rvalArg.set(3);
        std::cout << "called rvalProcess" << std::endl;
    }

#include <chrono>
    template <typename T>
    void logAndProcess(T&& param)
    {
        auto now = std::chrono::system_clock::now();
        process(std::forward<T>(param));
    }
    
    template<typename T>
    class vector
    {
    public:
        void push_back(T&& x) {
            std::cout << "called push_back" << std::endl;
        }
        
        template <typename... Args>
        void emplace_back(Args&&... args) {
            std::cout << "called emplace_back" << std::endl;
        }
    };
    
    class SomeData {
    public:
        SomeData() = default;
        SomeData(SomeData&& other) {
            std::cout << "SomeData move constructor" << std::endl;
        }
    };
    class Widget2 {
    public:
        Widget2() : _name("hoge"), _data(std::make_shared<SomeData>()){
        }
        //右辺値参照は常にmove可能オブジェクトがバインドされる
        Widget2(Widget2&& rhs)
        : _name(std::move(rhs._name)),
          _data(std::move(rhs._data)){
            std::cout << "Widget(&&)" << std::endl;
        }
        
        //ユニバーサル参照は常にmove可能オブジェクトがバインドされるかどうか不明。
        //std::forwardを使う。
        template <typename T>
        void setName(T&& newName) {
            _name = std::forward<T>(newName);
            //_name = std::move(newName);
            _name = "hoggee";
        }
        std::string name() const {
            std::cout << _name << std::endl;
            return _name;
        }
    
    private:
        std::string _name;
        std::shared_ptr<SomeData> _data;
    };
    

    template <typename T, typename U>
    void logAndAdd(T&& name,
                   std::multiset<U>& names)
    {
        names.emplace(std::forward<T>(name));
    }
    std::string nameFromIdx(int idx){
        return std::string("hoge");
    }
    template <typename U>
    void logAndAdd(int idx, std::multiset<U>& names)
    {
        names.emplace(nameFromIdx(idx));
    }
    
    class Person {
    public:
        template <typename T,
        typename = typename std::enable_if_t<
        !std::is_base_of<Person, std::decay_t<T>>::value
        && !std::is_integral<std::remove_reference_t<T>>::value>>
        explicit Person(T&& n)
        : _name(std::forward<T>(n)){
            static_assert(
            std::is_constructible<std::string, T>::value,
            "parameter T can't be constructible from std::string"
            );
        }
        
        explicit Person(int idx)
        : _name(nameFromIdx(idx)) {}

    public:
        std::string _name;
    };
    
    class SpecialPerson : public Person
    {
    public:
        SpecialPerson(const std::string& sp)
        : Person(sp){}
        
        SpecialPerson(const SpecialPerson& rhs)
        : Person(rhs) {
            this->_name = rhs._name;
            std::cout << "SpercialPersonCopyCtr" << std::endl;}
        
        SpecialPerson(SpecialPerson&& rhs)
        : Person(std::move(rhs)) {
            this->_name = rhs._name;
            std::cout << "SpecialPersonMoveCtr" << std::endl;}
    };
    
    std::multiset<std::string> names;
    
    template <typename T>
    void logAndAddImpl(T&& name, std::false_type)
    {
        names.emplace(std::forward<T>(name));
    }
    
    void logAndAddImpl(int index, std::true_type);
    template <typename T>
    void logAndAdd(T&& name)
    {
        logAndAddImpl(std::forward<T>(name),
        std::is_integral<std::remove_reference_t<T>>());
    
        std::cout << "logAndAdd2" << std::endl;
        for (auto s : names) {
            std::cout << s << std::endl;
        }
    }
    
    inline void logAndAddImpl(int index, std::true_type)
    {
        logAndAdd(nameFromIdx(index));
    }
    
    void func(std::vector<double>&& x) {
        std::cout << "move func" << std::endl;
    }
//
//    void func(const std::vector<double>& x) {
//        std::cout << "const reference func" << std::endl; //    } //
    void func(std::vector<double> x) {
        std::cout << "value func" << std::endl;
    }
    
    class LargeContainer {
    public:
        LargeContainer(const std::vector<double>& values)
        : _values(values){
            std::cout << "construct with copy" << std::endl;
        }
        LargeContainer(std::vector<double>&& values)
        : _values(values) {
            std::cout << "construct with move" << std::endl;
        }
        LargeContainer& operator=(const LargeContainer& other)
        {
            std::cout << "copy assignment" << std::endl;
            if (this != &other) {
                this->_values = other._values;
            }
            return *this;
        }
        LargeContainer& operator=(LargeContainer&& other)
        {
            std::cout << "move assignment" << std::endl;
            if (this != &other) {
                std::swap(this->_values, other._values);
            }
            return *this;
        }
        
        LargeContainer(const LargeContainer& rhs) {
            std::cout << "copy construct" << std::endl;
            *this = rhs;
        }
        LargeContainer(LargeContainer&& rhs) {
            std::cout << "move construct" << std::endl;
            *this = std::move(rhs);
        }
        
        void show() const {
            for (std::size_t i = 0; i < 10; ++i) {
                std::cout << _values[i] << std::endl;
            }
        }
        
    private:
        std::vector<double> _values;
    };
} //namespace move {
#endif //CPPTEMPLATE_MOVESEMANTICS_H
