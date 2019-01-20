//
// Created by MORIMOTO on 2018/01/05.
//
#ifndef MODERNCPP_CONCEPTOVERLOAD_H
#define MODERNCPP_CONCEPTOVERLOAD_H

#include <type_traits>
#include <boost/utility/enable_if.hpp>
#include "ConceptOfPoint.h"
#include "ConceptGeometry.h"

namespace concept {
    template <typename Point>
    class line_segment {
    public:
        using point_type = Point;
        line_segment() = default;
        line_segment(const Point& p1, const Point& p2)
        : _p1(p1), _p2(p2) {}
        const Point& p1() const { return _p1;}
        const Point& p2() const { return _p2;}
        
    private:
        Point _p1;
        Point _p2;
    };
    
    template <typename T>
    struct line_segment_traits {
        using point_type = typename T::point_type;
        static const point_type& p1(const T& line) {
            return line.p1();
        }
        static const point_type& p2(const T& line) {
            return line.p2();
        }
    };
    
    struct point_category{};
    struct line_segment_category{};
    
    template <typename T, typename Enable = void>
    struct get_geometry_category;
    
    template <>
    struct get_geometry_category<MyPoint1> {
        using type = point_category;
    };
    
    template <>
    struct get_geometry_category<MyPoint2> {
        using type = point_category;
    };
    template <>
    struct get_geometry_category<line_segment<MyPoint1>> {
        using type = line_segment_category;
    };
    
    
    //geometry_categoryをgeometry namespaceにあるconcept用に特殊化する
    template <typename T>
    struct get_geometry_category<T,
    std::enable_if_t<geo::is_point_category<T>::value, void>> {
        using type = point_category;
    };
    
    //point_traitsをgeometry namespaceにあるconceptを特殊化する
    template <typename T>
    struct point_traits<T,
    std::enable_if_t<geo::is_point_category<T>::value, void>> {
        static double x(const T& p) {
            return geo::point_traits<T>::getX(p);
        }
        static double y(const T& p) {
            return geo::point_traits<T>::getY(p);
        }
        static T subtract(const T& a, const T& b) {
            return geo::point_traits<T>::subtract(a, b);
        }
    };
    
   
    template <typename Point>
    double distance_impl(Point a, Point b, point_category, point_category) {
        using traits = point_traits<Point>;
        const Point d = traits::subtract(a, b);
        return std::sqrt(traits::x(d) * traits::x(d) +
                         traits::y(d) * traits::y(d));
    }
    
    template <typename Point, typename LineSegment>
    double distance_impl(Point a, LineSegment b, point_category, line_segment_category) {
        using traits = line_segment_traits<LineSegment>;
        return std::min(distance(a, traits::p1(b)),
                        distance(a, traits::p2(b)));
    };
    
    template <typename Point, typename LineSegment>
    double distance_impl(LineSegment a, Point b, line_segment_category, point_category) {
        return distance(b, a);
    };
    
    template <typename LineSegment1, typename LineSegment2>
    double distance_impl(LineSegment1 a, LineSegment2 b, line_segment_category, line_segment_category) {
        using traits = line_segment_traits<LineSegment2>;
        return distance(line_segment_traits<LineSegment1>::p1(a), traits::p1(b));
    };
    
    template <typename Geometry1, typename Geometry2>
    double distance(Geometry1 a, Geometry2 b) {
        return distance_impl(a, b,
            typename get_geometry_category<Geometry1>::type(),
            typename get_geometry_category<Geometry2>::type());
    };
   
    
    
}
#endif //MODERNCPP_CONCEPTOVERLOAD_H
