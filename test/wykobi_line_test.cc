#include <gtest/gtest.h>

#if 0
    #include "../third_party/wykobi/wykobi.hpp"
    #include "../third_party/wykobi/wykobi_nd.hpp"
using namespace wykobi;
TEST(wykobi_segment, is_intersect)
{
    segment2d seg({0, 0}, {100, 0});

    EXPECT_TRUE(wykobi::intersect(seg, seg, 0.0));
}

TEST(wykobi_segment, intersect_point)
{
    segment2d seg({0, 0}, {100, 0});

    wykobi::intersection_point(seg, seg, 0.0);
}
#endif