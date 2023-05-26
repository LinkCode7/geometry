#ifndef BOOLEAN_VERTEX_H
#define BOOLEAN_VERTEX_H

#include "../sindy2d/sindy_point2d.h"

namespace sindy
{
class Vertex
{
public:
    Point2d _pt;
    bool    _interPoint = false;
    Vertex* _next       = nullptr;
};
}  // namespace sindy

#endif  // !BOOLEAN_VERTEX_H
