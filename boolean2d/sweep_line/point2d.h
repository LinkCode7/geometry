// #pragma once
//
// #include "../boolean_pch.h"
//
// class Point2d
//{
// public:
//     Point2d() : m_x(0.0), m_y(0.0) {}
//     Point2d(double x, double y) : m_x(x), m_y(y) {}
//     Point2d(Point2d const& other) : m_x(other.m_x), m_y(other.m_y) {}
//     ~Point2d() {}
//
//     Point2d operator=(Point2d const& other);
//     bool    operator==(Point2d const& other) const;
//     bool    operator<(Point2d const& other) const;
//     bool    operator>(Point2d const& other) const;
//
//     inline double getX() { return m_x; }
//     inline double getY() { return m_y; }
//
//     inline void setX(double x) { m_x = x; }
//     inline void setY(double y) { m_y = y; }
//
// private:
//     double m_x;
//     double m_y;
// };