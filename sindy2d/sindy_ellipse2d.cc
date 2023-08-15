#include "sindy_ellipse2d.h"

#include "sindy_arc2d.h"

namespace sindy
{
Point2d Ellipse2d::getPoint(double radian) const
{
    radian = Arc2d::normalize(radian);

    auto const& rx = _radiusX;
    auto const& ry = _radiusY;

    if (radian == RADIAN_0)
        return _center.getAdd(rx, 0);
    if (radian == RADIAN_90)
        return _center.getAdd(0, ry);
    if (radian == RADIAN_180)
        return _center.getAdd(-rx, 0);
    if (radian == RADIAN_270)
        return _center.getAdd(0, -ry);

    double rx2 = rx * rx;
    double ry2 = ry * ry;

    // 椭圆公式
    double tg  = tan(radian);
    double tg2 = tg * tg;
    double x   = sqrt((rx2 * ry2) / (rx2 + ry2 / tg2));
    double y   = sqrt((rx2 * ry2) / (ry2 + rx2 / tg2));

    if (radian > RADIAN_90 && radian < RADIAN_270)
        x *= -1;
    if (radian > RADIAN_180 && radian < RADIAN_360)
        y *= -1;

    if (isnan(x))
        x = 0.0;
    if (isnan(y))
        y = 0.0;

    return _center.getAdd(x, y);
}

} // namespace sindy
