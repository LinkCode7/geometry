#ifndef SINDY_ALGORITHM_H
#define SINDY_ALGORITHM_H

#include "point.h"

namespace sindy
{
/*
 * @brief 测试一个点是否在直线的两侧
 * @detail 两个向量的叉积得到的是一个向量，方向垂直于两向量组成的平面，大小等于两向量组成的平行四边形面积
 * @return >0 pt2d在直线左边；=0 pt2d在线上；<0 pt2d在直线右边
 */
inline double isLeft(Point const& P0, Point const& P1, Point const& pt2d)
{
    return ((P1.x - P0.x) * (pt2d.y - P0.y) - (pt2d.x - P0.x) * (P1.y - P0.y));
}

/*
 * @brief 测试三个点的方向：p0->p1->p2
 * @return >0 逆时针；=0 三点共线；<0 顺时针
 */
inline double orientation2D_Triangle(Point const& p0, Point const& p1, Point const& p2)
{
    return isLeft(p0, p1, p2);
}

/*
 * @brief 计算二维平面内的三角形面积
 * @return 面积
 */
inline double area2D_Triangle(Point const& V0, Point const& V1, Point const& V2)
{
    return isLeft(V0, V1, V2) / 2.0;
}

// orientation2D_Polygon(): test the orientation of a simple 2D polygon
//  Input:  int n = the number of vertices in the polygon
//          Point* V = an array of n+1 vertex points with V[n]=V[0]
//  Return: >0 for counterclockwise
//          =0 for none (degenerate)
//          <0 for clockwise
//  Note: this algorithm is faster than computing the signed area.
int orientation2D_Polygon(int n, Point* V);

// area2D_Polygon(): compute the area of a 2D polygon
//  Input:  int n = the number of vertices in the polygon
//          Point* V = an array of n+1 vertex points with V[n]=V[0]
//  Return: the (float) area of the polygon
float area2D_Polygon(int n, Point* V);

// area3D_Polygon(): compute the area of a 3D planar polygon
//  Input:  int n = the number of vertices in the polygon
//          Point* V = an array of n+1 points in a 2D plane with V[n]=V[0]
//          Point N = a normal vector of the polygon's plane
//  Return: the (float) area of the polygon
float area3D_Polygon(int n, Point* V, Point N);

}  // namespace sindy

#endif  // !SINDY_ALGORITHM_H
