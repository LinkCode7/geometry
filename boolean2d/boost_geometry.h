#pragma once

#include "boolean_pch.h"

inline point2d_unordered_set GeometryIntersection(std::vector<polygon_2d> const& polygons)
{
    // 尽量保持整体数据结构的相似
    point2d_unordered_set allCrossPoints;
    std::vector<point_2d> crossPoints;

    if (polygons.size() <= 1)
        return allCrossPoints;

    for (int i = 0; i < polygons.size() - 1; i++)
    {
        // 加入多边形顶点
        for (auto point : polygons[i].outer())
            allCrossPoints.emplace(point);

        for (int j = i + 1; j < polygons.size(); j++)
        {
            bg::intersection(polygons[i], polygons[j], crossPoints);
            for (auto crossPoint : crossPoints)
            {
                allCrossPoints.emplace(crossPoint);
            }
        }
    }

    // 加入多边形顶点
    for (auto point : polygons[polygons.size() - 1].outer())
        allCrossPoints.emplace(point);

    return allCrossPoints;
}