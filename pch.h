#ifndef PCH_H
#define PCH_H

// #include <float.h>
#include <math.h>
#include <stdint.h>
#include <string.h>

#include <algorithm>
#include <functional>
#include <map>
#include <set>
#include <string>
#include <vector>

#ifdef _DEBUG
    #include <cassert>
#endif

#define SINDY_ZERO 0.0000001 // 1e-7
#define SINDY_DEFAULT_DOUBLE 0.0

#define SINDY_PRECISION 1e-8

#ifndef PI
    #define PI 3.14159265358979323846    // pi
    #define PI2 6.28318530717958623200   // pi*2
    #define PI_2 1.57079632679489661923  // pi/2
    #define PI_4 0.785398163397448309616 // pi/4
#endif

#define RADIAN_0 0.0
#define RADIAN_90 PI_2
#define RADIAN_180 PI
#define RADIAN_270 4.71238898038468967400
#define RADIAN_360 PI2

// 时钟方向
enum class ClockDirection
{
    eUnknownClockwise,
    eClockwise,        // 顺时针
    eCounterClockwise, // 逆时针
};

#endif // !PCH_H
