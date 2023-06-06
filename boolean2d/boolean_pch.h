#pragma once

#include <boost/geometry/algorithms/intersection.hpp>
#include <boost/geometry/geometries/adapted/c_array.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/geometries/segment.hpp>
#include <iostream>
#include <memory>

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

const double EPS       = 0.0000001;
const double SMALL_EPS = 0.00000001;

#define IS_FLOAT_EQUAL(a, b) (((a - b) < EPS) && ((b - a) < EPS))