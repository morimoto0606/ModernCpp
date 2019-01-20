//
// Created by MORIMOTO on 2018/01/04.
//

#ifndef MODERNCPP_CONCEPTOFPOINT_H
#define MODERNCPP_CONCEPTOFPOINT_H

#include <cmath>
namespace concept {
    
    class MyPoint1 {
    public:
        MyPoint1() = default;
        MyPoint1(double x, double y) : _x(x), _y(y) {}
        
        double x() const {
            return _x;
        }
        double y() const {
            return _y;
        }
    private:
        double _x = 0;
        double _y = 0;
    };
    
    
    class MyPoint2 {
    public:
        MyPoint2() = default;
        MyPoint2(double x, double y) : _x(x), _y(y) {}
        
        double getX() const {
            return _x;
        }
        double getY() const {
            return _y;
        }
    private:
        double _x = 0;
        double _y = 0;
    };
    
    template <typename T, typename Enable = void>
    struct point_traits {
        static double x(const T& p) {
            return p.x();
        }
        static double y(const T& p) {
            return p.y();
        }
        
        static T subtract(const T& a, const T& b) {
            return T(a.x() - b.x(), a.y() - b.y());
        }
    };
    
    
    template <>
    struct point_traits<MyPoint2> {
        static double  x(const MyPoint2& p) {
            return p.getX();
        }
        static double  y(const MyPoint2& p) {
            return p.getY();
        }
        static MyPoint2 subtract(const MyPoint2& a, const MyPoint2& b) {
            return MyPoint2(a.getX() - b.getX(), a.getY() - b.getY());
        }
        
    };
}

#endif //MODERNCPP_CONCEPTOFPOINT_H
