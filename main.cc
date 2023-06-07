#include <gtest/gtest.h>

#include <iostream>

//// https://www.docin.com/p-1457815325.html
// int main()
//{
//     testing::InitGoogleTest();
//     return RUN_ALL_TESTS();
//

#include "boolean2d/boolean_pch.h"
#include "boolean2d/boost_polygon.h"
#include "boolean2d/sweep_line/point_event.h"
#include "boolean2d/sweep_line/sweep_line.h"

point2d_unordered_set GeometryIntersection(std::vector<polygon_2d> polygons)
{
    // 尽量保持整体数据结构的相似
    point2d_unordered_set allCrossPoints;
    std::vector<point_2d> crossPoints;

    if (polygons.size() <= 1)
        return allCrossPoints;

    // TODO: 这方法肯定有问题，太慢了
    for (int i = 0; i < polygons.size() - 1; i++)
    {
        // 加入多边形顶点
        for (auto point : polygons[i].outer())
            allCrossPoints.emplace(point);

        for (int j = i + 1; j < polygons.size(); j++)
        {
            bg::intersection(polygons[i], polygons[j], crossPoints);
            for (auto crossPoint : crossPoints)
            {
                allCrossPoints.emplace(crossPoint);
            }
        }
    }

    // 加入多边形顶点
    for (auto point : polygons[polygons.size() - 1].outer())
        allCrossPoints.emplace(point);

    return allCrossPoints;
}

#pragma region Boost::Polygon

PolygonVec TestBoostPolygon()
{
    // Polygon boundary;
    //{
    //     Point pts[] = {gtl::construct<Point>(0, 10), gtl::construct<Point>(-20, 30), gtl::construct<Point>(0, 50),
    //                    gtl::construct<Point>(20, 30)};
    //     gtl::set_points(boundary, pts, pts + 4);
    // }

    PolygonVec polyVec;
    Polygon    poly;
    {
        Point pts[] = {gtl::construct<Point>(0, 0), gtl::construct<Point>(-20, 20), gtl::construct<Point>(0, 40),
                       gtl::construct<Point>(20, 20)};
        gtl::set_points(poly, pts, pts + 4);
        polyVec.emplace_back(poly);
    }
    {
        Point pts[] = {gtl::construct<Point>(0, 10), gtl::construct<Point>(-20, 30), gtl::construct<Point>(0, 50),
                       gtl::construct<Point>(20, 30)};
        gtl::set_points(poly, pts, pts + 4);
        polyVec.emplace_back(poly);
    }

    return BooleanAnd(polyVec);
}

PolygonVec BoostPolygonAnd(PolygonVec& polyVec)
{
    return BooleanAnd(polyVec);
}

#pragma endregion

#pragma region Preprocess

std::vector<segment_2d> DisjointPolygons(const std::vector<polygon_2d>& polygons)
{
    std::vector<segment_2d> segments;

    for (auto& polygon : polygons)
    {
        for (int i = 0; i < polygon.outer().size() - 1; i++)
        {
            // 减少拷贝
            segments.emplace_back(segment_2d(point_2d(bg::get<0>(polygon.outer()[i]), bg::get<1>(polygon.outer()[i])),
                                             point_2d(bg::get<0>(polygon.outer()[i + 1]), bg::get<1>(polygon.outer()[i + 1]))));
        }
    }

    return segments;
}

#pragma endregion

int main()
{
    int64_t startTime, endTime;

#pragma region 测试用例

    std::vector<polygon_2d> geometryPolygon2dVec;
    polygon_2d              geometryPolygon2d;

#pragma region 测试凸多边形

    {
        const double coor[][2] = {{0, 1}, {-2, 3}, {0, 5}, {2, 3}};
        bg::assign_points(geometryPolygon2d, coor);
        bg::append(geometryPolygon2d.outer(), point_2d({coor[0][0], coor[0][1]}));
    }
    geometryPolygon2dVec.emplace_back(geometryPolygon2d);

    {
        const double coor[][2] = {{-2, 0}, {-2, 2}, {2, 2}, {2, 0}};
        bg::assign_points(geometryPolygon2d, coor);
        bg::append(geometryPolygon2d.outer(), point_2d({coor[0][0], coor[0][1]}));
    }
    geometryPolygon2dVec.emplace_back(geometryPolygon2d);

    {
        const double coor[][2] = {{-1, -1}, {3, 3}, {4, -2}};
        bg::assign_points(geometryPolygon2d, coor);
        bg::append(geometryPolygon2d.outer(), point_2d({coor[0][0], coor[0][1]}));
    }
    geometryPolygon2dVec.emplace_back(geometryPolygon2d);

    {
        const double coor[][2] = {{-1, 2}, {0, 2}, {2.5, -0.5}, {2, -1}, {-2, 1}};
        bg::assign_points(geometryPolygon2d, coor);
        bg::append(geometryPolygon2d.outer(), point_2d({coor[0][0], coor[0][1]}));
    }
    geometryPolygon2dVec.emplace_back(geometryPolygon2d);

    {
        const double coor[][2] = {{0, 0}, {-50, 50}, {0, 100}, {50, 50}};
        bg::assign_points(geometryPolygon2d, coor);
        bg::append(geometryPolygon2d.outer(), point_2d({coor[0][0], coor[0][1]}));
    }
    geometryPolygon2dVec.emplace_back(geometryPolygon2d);

    {
        const double coor[][2] = {{0, 50}, {50, 0}, {0, -50}, {-50, 0}};
        bg::assign_points(geometryPolygon2d, coor);
        bg::append(geometryPolygon2d.outer(), point_2d({coor[0][0], coor[0][1]}));
    }
    geometryPolygon2dVec.emplace_back(geometryPolygon2d);

    {
        const double coor[][2] = {{12.7012, -637.599}, {-100.763, -594.415}, {-135, -508}, {-118, -413}, {10, -350},
                                  {129, -379},         {184, -474},          {132, -570},  {84, -617}};
        bg::assign_points(geometryPolygon2d, coor);
        bg::append(geometryPolygon2d.outer(), point_2d({coor[0][0], coor[0][1]}));
    }
    geometryPolygon2dVec.emplace_back(geometryPolygon2d);

    {
        const double coor[][2] = {{178, -615}, {4, -620}, {-156, -572}, {-160, -428}, {-7, -388}, {131, -407}, {214, -423}, {226, -550}};
        bg::assign_points(geometryPolygon2d, coor);
        bg::append(geometryPolygon2d.outer(), point_2d({coor[0][0], coor[0][1]}));
    }
    geometryPolygon2dVec.emplace_back(geometryPolygon2d);

    {
        const double coor[][2] = {{288.66, 245},    {417, 192.6595}, {667, 153},  {793, 143},  {903, 157},
                                  {984, 195},       {1119, 253},     {1177, 283}, {1213, 333}, {1212, 421},
                                  {1113, 502.2262}, {868, 547},      {550, 456},  {381, 385},  {298, 291}};
        bg::assign_points(geometryPolygon2d, coor);
        bg::append(geometryPolygon2d.outer(), point_2d({coor[0][0], coor[0][1]}));
    }
    geometryPolygon2dVec.emplace_back(geometryPolygon2d);

    {
        const double coor[][2] = {{101, 338},  {217, 280},  {322, 255},  {499, 165},  {680, 176},  {807, 133},
                                  {952, 200},  {1042, 240}, {1125, 339}, {1216, 436}, {1179, 531}, {1088, 523},
                                  {1014, 482}, {821, 460},  {608, 488},  {479, 412},  {302, 345}};
        bg::assign_points(geometryPolygon2d, coor);
        bg::append(geometryPolygon2d.outer(), point_2d({coor[0][0], coor[0][1]}));
    }
    geometryPolygon2dVec.emplace_back(geometryPolygon2d);

    {
        const double coor[][2] = {{128.562, 84.9289}, {192.454, 59.9957}, {264.137, 70.1248}, {360.753, 83.3706}, {399.711, 113.758},
                                  {469.057, 150.379}, {514.249, 150.379}, {571.907, 183.104}, {604.632, 226.737}, {610.086, 275.824},
                                  {610.865, 337.378}, {568.79, 403.607},  {544.636, 413.736}, {458.928, 420.749}, {410.62, 411.399},
                                  {338.157, 381.011}, {187.779, 343.612}, {150.379, 324.912}, {98.9539, 293.745}, {97.3956, 216.608},
                                  {137.133, 158.17},  {129.341, 112.979}, {115.316, 104.408}};
        bg::assign_points(geometryPolygon2d, coor);
        bg::append(geometryPolygon2d.outer(), point_2d({coor[0][0], coor[0][1]}));
    }
    geometryPolygon2dVec.emplace_back(geometryPolygon2d);

    {
        const double coor[][2] = {
            {105.187, 124.666}, {141.808, 103.629}, {141.029, 67.0082}, {209.595, 82.5914}, {302.316, 49.8665}, {335.82, 113.758},
            {432.436, 94.2789}, {419.191, 150.379}, {479.965, 130.12},  {486.978, 169.858}, {560.998, 124.666}, {548.532, 205.699},
            {612.423, 210.374}, {553.986, 282.058}, {626.448, 364.649}, {564.894, 384.128}, {551.649, 441.786}, {482.303, 394.257},
            {394.257, 418.411}, {349.845, 374.778}, {279.72, 403.607},  {227.516, 345.949}, {186.22, 358.416},  {175.312, 328.807},
            {144.925, 328.807}, {158.95, 292.966},  {88.8248, 303.874}, {128.562, 263.358}, {55.3207, 251.67},  {163.625, 237.645},
            {78.6956, 214.27},  {123.108, 207.258}, {103.629, 190.895}, {124.666, 204.141}, {105.966, 174.533}, {136.354, 180.766},
            {120.771, 164.404}, {165.183, 152.716}, {117.654, 152.716}, {151.937, 130.9},   {109.083, 139.47},  {135.575, 123.108}};
        bg::assign_points(geometryPolygon2d, coor);
        bg::append(geometryPolygon2d.outer(), point_2d({coor[0][0], coor[0][1]}));
    }
    geometryPolygon2dVec.emplace_back(geometryPolygon2d);

    {
        const double coor[][2] = {{97, 30}, {134, -15}, {219, -8}, {273, 55}, {163, 94}};
        bg::assign_points(geometryPolygon2d, coor);
        bg::append(geometryPolygon2d.outer(), point_2d({coor[0][0], coor[0][1]}));
    }
    geometryPolygon2dVec.emplace_back(geometryPolygon2d);

    {
        const double coor[][2] = {{96, 6}, {148, -7}, {189, -18}, {221, 17}, {289, 25}, {233, 84}};
        bg::assign_points(geometryPolygon2d, coor);
        bg::append(geometryPolygon2d.outer(), point_2d({coor[0][0], coor[0][1]}));
    }
    geometryPolygon2dVec.emplace_back(geometryPolygon2d);

#pragma endregion

#pragma region 测试凹多边形

    {
        const double coor[][2] = {{223.743, -455.054}, {224.414, -398.64},  {174.226, -402.224}, {176.376, -358.489}, {226.565, -360.64},
                                  {230.15, -324.074},  {184.263, -318.338}, {190.716, -288.942}, {230.15, -291.81},   {229.433, -257.395},
                                  {281.772, -265.999}, {276.036, -300.414}, {322.64, -306.149},  {321.206, -331.244}, {275.319, -335.546},
                                  {271.018, -369.243}, {332.678, -372.828}, {324.791, -405.092}, {269.584, -395.055}, {259.546, -460.3}};
        bg::assign_points(geometryPolygon2d, coor);
        bg::append(geometryPolygon2d.outer(), point_2d({coor[0][0], coor[0][1]}));
    }
    geometryPolygon2dVec.emplace_back(geometryPolygon2d);

    {
        const double coor[][2] = {{320.64, -448.633},  {291.611, -447.313}, {294.91, -420.923},  {246.088, -421.583}, {255.325, -377.379},
                                  {296.23, -379.359},  {302.167, -352.968}, {254.005, -350.989}, {254.005, -323.939}, {294.25, -316.682},
                                  {296.889, -292.931}, {263.242, -285.014}, {262.582, -248.067}, {327.898, -252.686}, {328.557, -224.976},
                                  {378.039, -230.254}, {357.587, -262.582}, {424.222, -273.798}, {420.263, -306.126}, {350.329, -290.292},
                                  {345.051, -362.865}, {428.84, -381.338},  {416.964, -411.027}, {354.288, -404.429}, {351.649, -456.55}};
        bg::assign_points(geometryPolygon2d, coor);
        bg::append(geometryPolygon2d.outer(), point_2d({coor[0][0], coor[0][1]}));
    }
    geometryPolygon2dVec.emplace_back(geometryPolygon2d);

    {
        const double coor[][2] = {{113.607, 79.1648}, {147.534, 39.0683}, {152.161, 85.3334}, {224.643, 86.8756}, {187.631, 132.627},
                                  {231.326, 151.647}, {175.807, 166.04},  {207.165, 230.297}, {155.759, 205.109}, {164.498, 262.683},
                                  {138.281, 231.326}, {107.438, 272.964}, {113.607, 195.342}, {60.6587, 192.257}, {72.482, 160.386},
                                  {114.121, 167.068}, {133.141, 121.317}, {62.2009, 118.233}, {58.6025, 79.1648}, {87.9037, 88.4178},
                                  {89.96, 36.498}};
        bg::assign_points(geometryPolygon2d, coor);
        bg::append(geometryPolygon2d.outer(), point_2d({coor[0][0], coor[0][1]}));
    }
    geometryPolygon2dVec.emplace_back(geometryPolygon2d);

    {
        const double coor[][2] = {{211.791, 49.8635}, {143.422, 76.5945}, {127.486, 51.9197}, {101.269, 63.7431}, {72.9961, 60.1447},
                                  {71.968, 84.8194},  {30.8434, 107.438}, {87.9037, 102.811}, {81.735, 131.599},  {145.478, 141.366},
                                  {133.655, 165.012}, {68.3696, 147.534}, {36.498, 178.892},  {83.7913, 178.892}, {71.4539, 221.559},
                                  {125.944, 216.932}, {125.43, 266.796},  {176.322, 230.297}, {170.667, 197.912}, {217.446, 194.314},
                                  {192.257, 147.534}, {238.008, 129.542}, {190.715, 110.008}};
        bg::assign_points(geometryPolygon2d, coor);
        bg::append(geometryPolygon2d.outer(), point_2d({coor[0][0], coor[0][1]}));
    }
    geometryPolygon2dVec.emplace_back(geometryPolygon2d);

    {
        const double coor[][2] = {
            {166.258, 99.6228},  {211.121, 56.0791},  {204.524, 113.478},  {255.325, 79.8302},  {277.756, 133.27},   {308.765, 110.839},
            {349.67, 125.353},   {379.359, 99.6228},  {403.769, 98.9631},  {454.57, 87.0875},   {500.093, 87.0875},  {515.268, 96.3241},
            {565.409, 137.889},  {580.583, 165.598},  {591.14, 207.822},   {581.243, 248.067},  {520.546, 312.723},  {442.695, 365.504},
            {352.309, 351.649},  {294.25, 344.392},   {241.47, 343.072},   {155.702, 335.155},  {134.59, 314.043},   {98.3033, 245.428},
            {74.5522, 209.802},  {50.8011, 190.669},  {58.7181, 132.611},  {77.1912, 116.117},  {126.673, 128.652},  {82.4692, 14.5146},
            {109.519, -4.61828}, {40.9047, -52.7803}, {22.4316, -99.6228}, {151.084, -96.9838}, {255.985, -73.2327}, {511.309, -73.2327},
            {527.803, 15.1743},  {403.11, 29.6889},   {195.287, -13.1951}, {174.175, 23.7511},  {370.122, -3.29877}, {427.521, 45.523},
            {405.089, 56.0791},  {299.528, 56.7388},  {240.15, 45.523},    {202.544, 45.523},   {168.897, 61.3571}};
        bg::assign_points(geometryPolygon2d, coor);
        bg::append(geometryPolygon2d.outer(), point_2d({coor[0][0], coor[0][1]}));
    }
    geometryPolygon2dVec.emplace_back(geometryPolygon2d);

    {
        const double coor[][2] = {{165.962, -134.633}, {107.537, -92.2952}, {56.7319, -26.2491}, {121.931, -21.1686}, {82.1343, 48.2645},
                                  {119.391, 62.6592},  {93.142, 75.3603},   {127.012, 86.368},   {88.0615, 149.874},  {38.9503, 258.257},
                                  {154.954, 254.024},  {140.56, 364.947},   {245.556, 293.821},  {271.805, 362.407},  {295.514, 79.5941},
                                  {339.545, 375.108},  {448.775, 72.8201},  {574.093, 309.062},  {570.706, 96.529},   {278.579, 10.1609},
                                  {431.84, -5.08047},  {491.959, 27.0958},  {558.852, -21.1686}, {498.733, -37.2568}, {701.952, -110.077},
                                  {611.35, 45.7242},   {535.143, 83.8278},  {543.61, 105.843},   {718.04, 40.6438},   {753.603, -162.575},
                                  {437.767, -134.633}, {425.066, -57.5787}, {324.303, -101.609}, {287.047, -46.571},  {281.119, -132.092},
                                  {237.089, -45.7242}, {211.686, -116.851}};
        bg::assign_points(geometryPolygon2d, coor);
        bg::append(geometryPolygon2d.outer(), point_2d({coor[0][0], coor[0][1]}));
    }
    geometryPolygon2dVec.emplace_back(geometryPolygon2d);

    {
        const double coor[][2] = {{83.2379, 64.8027}, {100.556, 27.9322}, {128.488, 74.8582}, {185.47, 69.2718},  {152.51, 110.053},
                                  {207.815, 131.281}, {155.862, 137.985}, {139.102, 172.062}, {128.488, 136.309}, {98.3213, 140.22},
                                  {101.114, 108.377}, {55.8644, 99.4386}, {80.4447, 83.2379}, {56.9816, 66.4786}};
        bg::assign_points(geometryPolygon2d, coor);
        bg::append(geometryPolygon2d.outer(), point_2d({coor[0][0], coor[0][1]}));
    }
    geometryPolygon2dVec.emplace_back(geometryPolygon2d);

    {
        const double coor[][2] = {{191.104, 96.0249}, {156.573, 59.1286}, {104.539, 69.5352}, {116.365, 94.1327}, {63.8589, 118.73},
                                  {117.784, 131.029}, {114.946, 152.315}, {134.813, 137.178}, {158.938, 161.303}, {161.776, 122.514},
                                  {180.224, 146.639}, {180.224, 126.299}, {216.174, 114},     {142.855, 107.378}};
        bg::assign_points(geometryPolygon2d, coor);
        bg::append(geometryPolygon2d.outer(), point_2d({coor[0][0], coor[0][1]}));
    }
    geometryPolygon2dVec.emplace_back(geometryPolygon2d);

#pragma endregion

#pragma region 测试垂直

    {
        const double coor[][2] = {{0, 0}, {0, 100}, {100, 100}, {100, 0}};
        bg::assign_points(geometryPolygon2d, coor);
        bg::append(geometryPolygon2d.outer(), point_2d({coor[0][0], coor[0][1]}));
    }
    geometryPolygon2dVec.emplace_back(geometryPolygon2d);

    {
        const double coor[][2] = {{50, 25}, {50, 50}, {150, 50}, {150, 25}};
        bg::assign_points(geometryPolygon2d, coor);
        bg::append(geometryPolygon2d.outer(), point_2d({coor[0][0], coor[0][1]}));
    }
    geometryPolygon2dVec.emplace_back(geometryPolygon2d);

    {
        const double coor[][2] = {{0.0, 0.0}, {0.0, 5.0}, {5.0, 5.0}, {5.0, 0.0}};
        bg::assign_points(geometryPolygon2d, coor);
        bg::append(geometryPolygon2d.outer(), point_2d({coor[0][0], coor[0][1]}));
    }
    geometryPolygon2dVec.emplace_back(geometryPolygon2d);

    {
        const double coor[][2] = {{2.0, 2.0}, {3.0, 6.0}, {4.0, 2.0}};
        bg::assign_points(geometryPolygon2d, coor);
        bg::append(geometryPolygon2d.outer(), point_2d({coor[0][0], coor[0][1]}));
    }
    geometryPolygon2dVec.emplace_back(geometryPolygon2d);

    {
        const double coor[][2] = {{0, 0}, {0, 100}, {100, 100}, {100, 0}};
        bg::assign_points(geometryPolygon2d, coor);
        bg::append(geometryPolygon2d.outer(), point_2d({coor[0][0], coor[0][1]}));
    }
    geometryPolygon2dVec.emplace_back(geometryPolygon2d);

    {
        const double coor[][2] = {{50, 25}, {50, 50}, {150, 50}, {150, 25}};
        bg::assign_points(geometryPolygon2d, coor);
        bg::append(geometryPolygon2d.outer(), point_2d({coor[0][0], coor[0][1]}));
    }
    geometryPolygon2dVec.emplace_back(geometryPolygon2d);

#pragma endregion

#pragma region 测试点在边上

    {
        const double coor[][2] = {{0, 0}, {0, 4}, {4, 4}, {4, 0}};
        bg::assign_points(geometryPolygon2d, coor);
        bg::append(geometryPolygon2d.outer(), point_2d({coor[0][0], coor[0][1]}));
    }
    geometryPolygon2dVec.emplace_back(geometryPolygon2d);

    {
        const double coor[][2] = {{4, 2}, {8, 4}, {8, 0}, {2, 1}, {6, 1}};
        bg::assign_points(geometryPolygon2d, coor);
        bg::append(geometryPolygon2d.outer(), point_2d({coor[0][0], coor[0][1]}));
    }
    geometryPolygon2dVec.emplace_back(geometryPolygon2d);

    {
        const double coor[][2] = {{0, 0}, {0, 4}, {4, 4}, {4, 0}};
        bg::assign_points(geometryPolygon2d, coor);
        bg::append(geometryPolygon2d.outer(), point_2d({coor[0][0], coor[0][1]}));
    }
    geometryPolygon2dVec.emplace_back(geometryPolygon2d);

    {
        const double coor[][2] = {{4, 2}, {8, 4}, {8, 0}};
        bg::assign_points(geometryPolygon2d, coor);
        bg::append(geometryPolygon2d.outer(), point_2d({coor[0][0], coor[0][1]}));
    }
    geometryPolygon2dVec.emplace_back(geometryPolygon2d);

#pragma endregion

#pragma endregion

    bool                  isTestGeometryIntersection = true;
    std::vector<point_2d> crossPointsVecFromGeometry;
    if (isTestGeometryIntersection)
    {
        point2d_unordered_set geometryCrossPoints;
        startTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        // auto start_time     = std::chrono::steady_clock::now();
        geometryCrossPoints = GeometryIntersection(geometryPolygon2dVec);
        // auto end_time       = std::chrono::steady_clock::now();
        endTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

        // 输出结果
        std::cout << "Geometry Intersection: " << endTime - startTime << "ms"
                  << " Cross Point Num: " << geometryCrossPoints.size() << std::endl;
        // auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time); // 计算运行时间（以微秒为单位）
        // std::cout << "Boost::Geometry 求交消耗时间: " << duration.count() << " ms" << std::endl;

        // 洗一下数据
        for (auto& crossPoint : geometryCrossPoints)
        {
            crossPointsVecFromGeometry.emplace_back(crossPoint);
        }
        sort(crossPointsVecFromGeometry.begin(), crossPointsVecFromGeometry.end(), [](point_2d& a, point_2d& b) -> bool {
            if (bg::get<0>(a) != bg::get<0>(b))
                return bg::get<0>(a) < bg::get<0>(b);
            else
                return bg::get<1>(a) < bg::get<1>(b);
        });
    }

// 目前暂时不会测试 Boost::Polygon，要求传递的数据结构和另两个不一致，单独处理工作量不小
#pragma region 测试 Polygon

    bool isTestPolygonBoolean = false;
    if (isTestPolygonBoolean)
    {
        startTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        TestBoostPolygon();
        // BoostPolygonAnd(polyVec);
        endTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

        // 输出结果
        std::cout << "Build PolygonSet and Boolean: " << endTime - startTime << "ms" << std::endl;
    }

#pragma endregion

    // 测试 SweepLine
    std::vector<point_2d> crossPointsVecFromSweepLine;
    {
        // TODO: 预处理，之后应该根据多边形特性判断内外
        std::vector<segment_2d> originSegments = DisjointPolygons(geometryPolygon2dVec);

        SweepLine sweepLine(originSegments);
        startTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        // auto start_time = std::chrono::steady_clock::now();
        sweepLine.Scan();
        // auto end_time = std::chrono::steady_clock::now();
        endTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

        // 输出结果
        std::cout << "Sweep Line Time: " << endTime - startTime << "ms"
                  << " Cross Point Num: " << sweepLine.GetAllCrossPoints().size() << std::endl;
        // auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time); // 计算运行时间（以微秒为单位）
        // std::cout << "SweepLine 求交消耗时间: " << duration.count() << " ms" << std::endl;

        // 洗一下数据
        for (auto& crossPoint : sweepLine.GetAllCrossPoints())
        {
            crossPointsVecFromSweepLine.emplace_back(crossPoint);
        }
        sort(crossPointsVecFromSweepLine.begin(), crossPointsVecFromSweepLine.end(), [](point_2d& a, point_2d& b) -> bool {
            if (bg::get<0>(a) != bg::get<0>(b))
                return bg::get<0>(a) < bg::get<0>(b);
            else
                return bg::get<1>(a) < bg::get<1>(b);
        });
    }

    //// 输出
    // for (int i = 0; i < crossPointsVecFromGeometry.size(); i++)
    //{
    //     std::cout << "x: " << bg::get<0>(crossPointsVecFromGeometry[i]) << ", y: " << bg::get<1>(crossPointsVecFromGeometry[i])
    //               << " x: " << bg::get<0>(crossPointsVecFromSweepLine[i]) << ", y: " << bg::get<1>(crossPointsVecFromSweepLine[i])
    //               << std::endl;
    // }

    // for (int i = 0; i < crossPointsVecFromGeometry.size(); i++)
    //{
    //     // 判断浮点数是否相等
    //     if (abs(bg::get<0>(crossPointsVecFromGeometry[i]) - bg::get<0>(crossPointsVecFromSweepLine[i])) < EPS &&
    //         abs(bg::get<1>(crossPointsVecFromGeometry[i]) - bg::get<1>(crossPointsVecFromSweepLine[i])) < EPS)
    //     {
    //         continue;
    //     }
    //     else
    //     {
    //         std::cout << "Not equal!" << std::endl;
    //         break;
    //     }
    // }

    return 0;
}
