#pragma once

#include <boost/geometry/algorithms/intersection.hpp>
#include <boost/geometry/geometries/adapted/c_array.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/geometries/segment.hpp>
#include <iostream>
#include <memory>
#include <unordered_set>
#include <vector>

namespace bg = boost::geometry;

// typedef bg::model::point<double, 2, bg::cs::cartesian> point_2d;
typedef bg::model::d2::point_xy<double> point_2d;
typedef bg::model::segment<point_2d>    segment_2d;
typedef bg::model::polygon<point_2d>    polygon_2d;

// 暂时用不到
enum class Axis : int
{
    X = 0,
    Y = 1,
};

// 浮点精度
const double EPS       = 0.0000001;
const double SMALL_EPS = 0.00000001;
#define IS_FLOAT_EQUAL(a, b) (((a - b) < EPS) && ((b - a) < EPS))

#pragma region 存交点的容器

struct Point2dHash
{
    size_t operator()(point_2d const& point2d) const // size_t
    {
        // return size_t(l.k ^ l.b);//自定义哈希
        return std::hash<double>()(bg::get<0>(point2d)) ^ std::hash<double>()(bg::get<1>(point2d));
    }
};

struct Point2dIsEqual
{
    bool operator()(point_2d const& firstPoint2d, point_2d const& secondPoint2d) const // 最后的const不能少
    {
        return (IS_FLOAT_EQUAL(bg::get<0>(firstPoint2d), bg::get<0>(secondPoint2d)) &&
                IS_FLOAT_EQUAL(bg::get<1>(firstPoint2d), bg::get<1>(secondPoint2d)));
    }
};

typedef std::unordered_set<point_2d, Point2dHash, Point2dIsEqual> point2d_unordered_set;

#pragma endregion
