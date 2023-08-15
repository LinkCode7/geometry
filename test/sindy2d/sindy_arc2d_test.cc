#include "../../sindy2d/sindy_arc2d.h"

#include <gtest/gtest.h>

#include "../../pch.h"

using namespace sindy;

TEST(arc, construct)
{
    Arc2d arc(Point2d::kOrigin, Point2d::kXAxis, Point2d::kYAxis, 1, ClockDirection::eCounterClockwise);
}