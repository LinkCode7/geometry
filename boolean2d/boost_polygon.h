#pragma once

#include <boost/polygon/polygon.hpp>
#include <cassert>
#include <iostream>
namespace gtl = boost::polygon;
using namespace boost::polygon::operators;

// lets construct a 10x10 rectangle shaped polygon
typedef gtl::polygon_data<int>                   Polygon;
typedef gtl::polygon_traits<Polygon>::point_type Point;
typedef gtl::polygon_set_data<int>               PolygonSet;
typedef std::vector<Polygon>                     PolygonVec;

PolygonVec BooleanAnd(PolygonVec& polygonVec)
{
    PolygonSet andSet;
    andSet.insert(polygonVec[0], false);

    for (int i = 1; i < polygonVec.size(); i++)
    {
        andSet.insert(polygonVec[i], false);  // Insert As Hole, which works in 1_53 but not in 1_56
        // o_full_set += o_item;  // works in 1_53 and 1_56
    }

    PolygonVec andVec;

    // 求布尔
    andSet.get(andVec);

    for (Polygon o_poly : andVec)
    {
        std::vector<Point> poly_points;
        poly_points.insert(poly_points.end(), o_poly.begin(), o_poly.end());
        for (Point o_pos : poly_points)
        {
            std::cout << "(" << gtl::x(o_pos) << ", " << gtl::y(o_pos) << ") ";
        }
        std::cout << std::endl;
    }

    return andVec;
}
