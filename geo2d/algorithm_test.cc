#include "algorithm.h"

#include "gtest/gtest.h"

using namespace sindy;

TEST(vector2d, isLeft)
{
    enum
    {
        eLineLeft,
        eLine,
        eLineRight
    };

    auto check = [](Point const& p0, Point const& p1, std::vector<std::pair<Point, int>> const& expect) {
        for (auto const& item : expect)
        {
            double result = isLeft(p0, p1, item.first);
            if (item.second == eLineLeft && result <= 0)
                return false;
            if (item.second == eLine && result != 0)
                return false;
            if (item.second == eLineRight && result >= 0)
                return false;
        }
        return true;
    };

    std::vector<std::pair<Point, int>> expect;

    // 在线的右边
    expect = {{{100, 100}, eLineRight}, {{0.00000001, 0}, eLineRight}, {{55.5, -10}, eLineRight}};
    EXPECT_TRUE(check({0, 0}, {0, 100}, expect));

    // 在线上
    expect = {{{0, 0}, eLine}, {{0, 50}, eLine}, {{0, 100}, eLine}, {{0, 200}, eLine}, {{0, -50}, eLine}};
    EXPECT_TRUE(check({0, 0}, {0, 100}, expect));

    // 在线的左边
    expect = {{{-0.001, 100}, eLineLeft}, {{-10.5, -10.5}, eLineLeft}, {{-100.5, -10}, eLineLeft}};
    EXPECT_TRUE(check({0, 0}, {0, 100}, expect));

    // 45°直线
    expect = {{{50, 50}, eLine}, {{-99.9, -99.9}, eLine}, {{-99.9, -99.88}, eLineLeft}, {{-99.9, -99.91}, eLineRight}};
    EXPECT_TRUE(check({-33.3, -33.3}, {33.3, 33.3}, expect));
}
