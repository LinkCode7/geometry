#include "algorithm.h"

namespace sindy
{
int orientation2D_Polygon(const int n, Point* V)
{
    // first find rightmost lowest vertex of the polygon
    int rmin = 0;
    int xmin = V[0].x;
    int ymin = V[0].y;

    for (int i = 1; i < n; i++)
    {
        if (V[i].y > ymin)
            continue;
        if (V[i].y == ymin)
        {                      // just as low
            if (V[i].x < xmin) // and to left
                continue;
        }
        rmin = i; // a new rightmost lowest vertex
        xmin = V[i].x;
        ymin = V[i].y;
    }

    // test orientation at the rmin vertex
    // ccw <=> the edge leaving V[rmin] is left of the entering edge
    if (rmin == 0)
        return isLeft(V[n - 1], V[0], V[1]);
    else
        return isLeft(V[rmin - 1], V[rmin], V[rmin + 1]);
}

float area2D_Polygon(const int n, Point* V)
{
    if (n < 3)
        return 0; // a degenerate polygon

    float area = 0;
    int   i, j, k; // indices

    for (i = 1, j = 2, k = 0; i < n; i++, j++, k++)
    {
        area += V[i].x * (V[j].y - V[k].y);
    }
    area += V[n].x * (V[1].y - V[n - 1].y); // wrap-around term
    return area / 2.0;
}

float area3D_Polygon(const int n, Point* V, const Point& N)
{
    float area = 0;
    float an, ax, ay, az; // abs value of normal and its coords
    int   coord;          // coord to ignore: 1=x, 2=y, 3=z
    int   i, j, k;        // loop indices

    if (n < 3)
        return 0; // a degenerate polygon

    // select largest abs coordinate to ignore for projection
    ax = (N.x > 0 ? N.x : -N.x); // abs x-coord
    ay = (N.y > 0 ? N.y : -N.y); // abs y-coord
    az = (N.z > 0 ? N.z : -N.z); // abs z-coord

    coord = 3; // ignore z-coord
    if (ax > ay)
    {
        if (ax > az)
            coord = 1; // ignore x-coord
    }
    else if (ay > az)
        coord = 2; // ignore y-coord

    // compute area of the 2D projection
    switch (coord)
    {
        case 1:
            for (i = 1, j = 2, k = 0; i < n; i++, j++, k++)
                area += (V[i].y * (V[j].z - V[k].z));
            break;
        case 2:
            for (i = 1, j = 2, k = 0; i < n; i++, j++, k++)
                area += (V[i].z * (V[j].x - V[k].x));
            break;
        case 3:
            for (i = 1, j = 2, k = 0; i < n; i++, j++, k++)
                area += (V[i].x * (V[j].y - V[k].y));
            break;
    }
    switch (coord)
    { // wrap-around term
        case 1:
            area += (V[n].y * (V[1].z - V[n - 1].z));
            break;
        case 2:
            area += (V[n].z * (V[1].x - V[n - 1].x));
            break;
        case 3:
            area += (V[n].x * (V[1].y - V[n - 1].y));
            break;
    }

    // scale to get area before projection
    an = sqrt(ax * ax + ay * ay + az * az); // length of normal vector
    switch (coord)
    {
        case 1:
            area *= (an / (2 * N.x));
            break;
        case 2:
            area *= (an / (2 * N.y));
            break;
        case 3:
            area *= (an / (2 * N.z));
    }
    return area;
}

} // namespace sindy
