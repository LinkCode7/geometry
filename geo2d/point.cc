#include "point.h"

Point P_0;  // the "0" Point (0,0,0)

// Read input Point format: "(%f)", "(%f, %f)", or "(%f, %f, %f)"
std::istream& operator>>(std::istream& input, Point& P)
{
    char c;
    input >> c;  // skip '('
    input >> P.x;
    input >> c;
    if (c == ')')
    {
        return input;
    }
    // else                    // skip ','
    input >> P.y;
    input >> c;
    if (c == ')')
    {
        return input;
    }
    // else                    // skip ','
    input >> P.z;
    input >> c;  // skip ')'
    return input;
}

// Write output Point in format: "(%f)", "(%f, %f)", or "(%f, %f, %f)"
std::ostream& operator<<(std::ostream& output, Point P)
{
    output << "(" << P.x << ", " << P.y << ", " << P.z << ")";
    return output;
}

//------------------------------------------------------------------
// Comparison (note: dimension must compare)
//------------------------------------------------------------------

int Point::operator==(Point const& Q)
{
    return (x == Q.x && y == Q.y && z == Q.z);
}

int Point::operator!=(Point const& Q)
{
    return (x != Q.x || y != Q.y || z != Q.z);
}

//------------------------------------------------------------------
// Point Scalar Operations (convenient but often illegal)
//        are not valid for points in general,
//        unless they are 'affine' as coeffs of
//        a sum in which all the coeffs add to 1,
//        such as: the sum (a*P + b*Q) with (a+b == 1).
//        The programmer must enforce this (if they want to).
//------------------------------------------------------------------

Point operator*(int c, Point Q)
{
    Point P;
    P.x = c * Q.x;
    P.y = c * Q.y;
    P.z = c * Q.z;
    return P;
}

Point operator*(double c, Point Q)
{
    Point P;
    P.x = c * Q.x;
    P.y = c * Q.y;
    P.z = c * Q.z;
    return P;
}

Point operator*(Point Q, int c)
{
    Point P;
    P.x = c * Q.x;
    P.y = c * Q.y;
    P.z = c * Q.z;
    return P;
}

Point operator*(Point Q, double c)
{
    Point P;
    P.x = c * Q.x;
    P.y = c * Q.y;
    P.z = c * Q.z;
    return P;
}

Point operator/(Point Q, int c)
{
    Point P;
    P.x = Q.x / c;
    P.y = Q.y / c;
    P.z = Q.z / c;
    return P;
}

Point operator/(Point Q, double c)
{
    Point P;
    P.x = Q.x / c;
    P.y = Q.y / c;
    P.z = Q.z / c;
    return P;
}

//------------------------------------------------------------------
// Point Addition (also convenient but often illegal)
//    is not valid unless part of an affine sum.
//    The programmer must enforce this (if they want to).
//------------------------------------------------------------------

Point operator+(Point const& Q, Point const& R)
{
    Point P;
    P.x = Q.x + R.x;
    P.y = Q.y + R.y;
    P.z = Q.z + R.z;
    return P;
}

//------------------------------------------------------------------
// Affine Sums
// Returns weighted sum, even when not affine, but...
// Tests if coeffs add to 1.  If not, sets: err = Esum.
//------------------------------------------------------------------

Point asum(int n, int c[], Point Q[])
{
    Point P;

    for (int i = 0; i < n; i++)
    {
        P.x += c[i] * Q[i].x;
        P.y += c[i] * Q[i].y;
        P.z += c[i] * Q[i].z;
    }
    return P;
}

Point asum(int n, double c[], Point Q[])
{
    Point P;

    for (int i = 0; i < n; i++)
    {
        P.x += c[i] * Q[i].x;
        P.y += c[i] * Q[i].y;
        P.z += c[i] * Q[i].z;
    }

    return P;
}

//------------------------------------------------------------------
// Distance between Points
//------------------------------------------------------------------

double d(Point P, Point Q)
{  // Euclidean distance
    double dx = P.x - Q.x;
    double dy = P.y - Q.y;
    double dz = P.z - Q.z;
    return sqrt(dx * dx + dy * dy + dz * dz);
}

double d2(Point P, Point Q)
{  // squared distance (more efficient)
    double dx = P.x - Q.x;
    double dy = P.y - Q.y;
    double dz = P.z - Q.z;
    return (dx * dx + dy * dy + dz * dz);
}

//------------------------------------------------------------------
// Sidedness of a Point wrt a directed line P1->P2
//        - makes sense in 2D only
//------------------------------------------------------------------

double Point::isLeft(Point const& P1, Point const& P2)
{
    return (P1.x - x) * (P2.y - y) - (P2.x - x) * (P1.y - y);
}
