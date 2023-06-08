#ifndef SS_Point_H
#define SS_Point_H

#include <iostream>

enum boolean
{
    FALSE = 0,
    TRUE  = 1,
    ERROR = (-1)
};
enum polytype
{
    ANY      = 0,
    PROPER   = 1,
    SIMPLE   = 2,
    STAR     = 4,
    MONOTONE = 8,
    CONVEX   = 16
};

// Error codes
enum Error
{
    Enot, // no error
    Edim, // error: dim of point invalid for operation
    Esum  // error: sum not affine (cooefs add to 1)
};

class Point
{
    friend class Vector;

public:
    double x, y, z;

    Point() { x = y = z = 0; }
    Point(const double a, const double b)
    {
        x = a;
        y = b;
        z = 0;
    }
    Point(const double a, const double b, const double c)
    {
        x = a;
        y = b;
        z = c;
    }
    ~Point() {}

    friend std::istream& operator>>(std::istream&, Point&);
    friend std::ostream& operator<<(std::ostream&, const Point&);

    int operator==(Point const&) const;
    int operator!=(Point const&) const;

    //----------------------------------------------------------
    // Point Scalar Operations (convenient but often illegal)
    // using any type of scalar (int, float, or double)
    //    are not valid for points in general,
    //    unless they are 'affine' as coeffs of
    //    a sum in which all the coeffs add to 1,
    //    such as: the sum (a*P + b*Q) with (a+b == 1).
    //    The programmer must enforce this (if they want to).

    // Scalar Multiplication
    friend Point operator*(int, const Point&);
    friend Point operator*(double, const Point&);
    friend Point operator*(const Point&, int);
    friend Point operator*(const Point&, double);
    // Scalar Division
    friend Point operator/(const Point&, int);
    friend Point operator/(const Point&, double);

    //----------------------------------------------------------
    // Point Addition (also convenient but often illegal)
    //    is not valid unless part of an affine sum.
    //    The programmer must enforce this (if they want to).

    friend Point operator+(Point const&, Point const&);

    // Affine Sum
    // Returns weighted sum, even when not affine, but...
    // Tests if coeffs add to 1.  If not, sets: err = Esum.

    friend Point asum(int, int[], Point[]);
    friend Point asum(int, double[], Point[]);

    //----------------------------------------------------------
    // Point Relations
    friend double d(const Point&, const Point&);            // Distance
    friend double d2(const Point&, const Point&);           // Distance^2
    double        isLeft(Point const&, Point const&) const; // 2D only

    // double        Area(Point, Point);                  // any dim for triangle PPP

    //// Collinearity Conditions (any dim n)
    // boolean isOnLine(Point, Point, char);  // is On line (char= flag)
    // boolean isOnLine(Point, Point);        // is On line (flag= all)
    // boolean isBefore(Point, Point);        // is On line (flag= before)
    // boolean isBetween(Point, Point);       // is On line (flag= between)
    // boolean isAfter(Point, Point);         // is On line (flag= after)
    // boolean isOnRay(Point, Point);         // is On line (flag= between|after)
};

#endif SS_Point_H
