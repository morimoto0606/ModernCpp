//
// Created by MORIMOTO on 2018/01/05.
//

#ifndef MODERNCPP_CONCEPTGEOMETRY_H
#define MODERNCPP_CONCEPTGEOMETRY_H

#include <utility>
namespace concept {namespace geo {
        template <typename T>
        struct is_point_category {
            static const bool value = false;
        };
        
        template <typename T>
        struct point_traits {
            using point_type = T;
            static double getX(const point_type& p) { return p.getX();}
            static double getY(const point_type& p) { return p.getY();}
            
            static point_type subtract(const point_type& a, const point_type& b) {
                    return point_type(a.getX() - b.getX(),
                        a.getY() - b.getY());
            }
        };
        
        class point {
        public:
            point() = default;
            point(double x, double y) : _x(x), _y(y) {}
            
            double getX() const { return _x;}
            double getY() const { return _y;}
        private:
            double _x = 0;
            double _y = 0;
        };
        
        template <>
        struct is_point_category<point> {
            static const bool value = true;
        };
        
        template <>
        struct point_traits<std::pair<double, double>> {
            using point_type = std::pair<double, double>;
            static double getX(const point_type& p) { return p.first;}
            static double getY(const point_type& p) { return p.second;}
            static point_type subtract(const point_type& a, const point_type& b) {
                    return std::make_pair(a.first - b.first, a.second - b.second);
            }
        };
        
        template <>
        struct is_point_category<std::pair<double, double>> {
            static const bool value = true;
        };
}}

#endif //MODERNCPP_CONCEPTGEOMETRY_H
