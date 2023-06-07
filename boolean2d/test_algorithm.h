#pragma once

#include "boolean_pch.h"
#include "boost_geometry.h"
#include "boost_polygon.h"
#include "sweep_line/sweep_line.h"

// TODO: 还没适配 Boost::Polygon 的数据格式
#pragma region Boost::Polygon

PolygonVec TestBoostPolygon(PolygonVec const& polygons)
{
    //// 数据格式
    // PolygonVec polyVec;
    // Polygon    poly;
    //{
    //     Point pts[] = {gtl::construct<Point>(0, 0), gtl::construct<Point>(-20, 20), gtl::construct<Point>(0, 40),
    //                    gtl::construct<Point>(20, 20)};
    //     gtl::set_points(poly, pts, pts + 4);
    //     polyVec.emplace_back(poly);
    // }
    //{
    //     Point pts[] = {gtl::construct<Point>(0, 10), gtl::construct<Point>(-20, 30), gtl::construct<Point>(0, 50),
    //                    gtl::construct<Point>(20, 30)};
    //     gtl::set_points(poly, pts, pts + 4);
    //     polyVec.emplace_back(poly);
    // }

    int64_t    startTime, endTime;
    PolygonVec polygonsBooleanAnd;

    startTime          = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    polygonsBooleanAnd = BooleanAnd(polygons);
    endTime            = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    // 输出结果
    std::cout << "Polygon Build PolygonSet and Boolean: " << endTime - startTime << "ms" << std::endl;

    return polygonsBooleanAnd;
}

#pragma endregion

point2d_unordered_set TestBoostGeometry(std::vector<polygon_2d> const& polygons)

{
    int64_t               startTime, endTime;
    point2d_unordered_set geometryCrossPoints;

    startTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    geometryCrossPoints = GeometryIntersection(polygons);
    endTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

#ifdef _DEBUG

    // 输出结果
    std::cout << "Geometry Intersection: " << endTime - startTime << "ms"
              << " Cross Point Num: " << geometryCrossPoints.size() << std::endl;
#endif // _DEBUG

    return geometryCrossPoints;
}

point2d_unordered_set TestSweepLine(std::vector<polygon_2d> const& polygons)
{
    int64_t   startTime, endTime;
    SweepLine sweepLine(polygons);

    startTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    sweepLine.scan();
    endTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

#ifdef _DEBUG

    // 输出结果
    std::cout << "Sweep Line Intersection: " << endTime - startTime << "ms"
              << " Cross Point Num: " << sweepLine.GetAllCrossPoints().size() << std::endl;

#endif // _DEBUG

    return sweepLine.GetAllCrossPoints();
}