#ifndef SINDY_POLYGON2D_H
#define SINDY_POLYGON2D_H
#include "sindy_edges.h"

namespace sindy
{
class Polygon
{
    std::vector<EdgeGroup> _hole;    // 内洞
    EdgeGroup              _contour; // 外轮廓

public:
    Polygon() {}
};

} // namespace sindy

#endif // !SINDY_POLYGON2D_H
