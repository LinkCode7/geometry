#include "polygon_chain.h"

std::vector<Point2d> PolygonChain::doItersect(const std::vector<Point2d> &polygon1, const std::vector<Point2d> &polygon2)
{
    std::vector<std::vector<int>> MChains1 = getMonotoneChain(polygon1);
    std::vector<std::vector<int>> MChains2 = getMonotoneChain(polygon2);
    SMC_SL(MChains1, polygon1, 1);
    SMC_SL(MChains2, polygon2, 2);
    auto result = getCrossPt(polygon1, polygon2);
    return result;
}

std::vector<std::vector<int>> PolygonChain::getMonotoneChain(const std::vector<Point2d> &polygon)
{
    int size = polygon.size();

    // 统计所有的左右极值点的下标
    std::unordered_set<int> leftExtreme;
    std::unordered_set<int> rightExtreme;
    for (int i = 0; i < size; ++i)
    {
        if (polygon[i].x() < polygon[(i + 1) % size].x() && polygon[i].x() < polygon[(i - 1 + size) % size].x())
            leftExtreme.insert(i);
        else if (polygon[i].x() < polygon[(i + 1) % size].x() && polygon[i].x() == polygon[(i - 1 + size) % size].x())
        {
            if (leftExtreme.count((i - 1 + size) % size) == 0)
                leftExtreme.insert(i);
        }
        else if (polygon[i].x() == polygon[(i + 1) % size].x() && polygon[i].x() < polygon[(i - 1 + size) % size].x())
        {
            if (leftExtreme.count((i + 1) % size) == 0)
                leftExtreme.insert(i);
        }
        else if (polygon[i].x() > polygon[(i + 1) % size].x() && polygon[i].x() > polygon[(i - 1 + size) % size].x())
            rightExtreme.insert(i);
        else if (polygon[i].x() > polygon[(i + 1) % size].x() && polygon[i].x() == polygon[(i - 1 + size) % size].x())
        {
            if (rightExtreme.count((i - 1 + size) % size) == 0)
                rightExtreme.insert(i);
        }
        else if (polygon[i].x() == polygon[(i + 1) % size].x() && polygon[i].x() > polygon[(i - 1 + size) % size].x())
        {
            if (rightExtreme.count((i + 1) % size) == 0)
                rightExtreme.insert(i);
        }
    }

    // 获取当前多边形的所有单调链
    std::vector<std::vector<int>> Chains;
    for (auto &left : leftExtreme)
    {
        std::vector<int> oneChain;
        int              idx = (left + 1) % size;
        oneChain.emplace_back(left);
        while (idx % size != left)
        {
            oneChain.emplace_back(idx % size);
            if (rightExtreme.count(idx % size) != 0)  // 顺时针找到右极值点
                break;
            ++idx;
        }
        Chains.emplace_back(oneChain);
        oneChain.clear();

        idx = (left - 1) % size;
        oneChain.emplace_back(left);
        while ((idx + size) % size != left)
        {
            oneChain.emplace_back((idx + size) % size);
            if (rightExtreme.count((idx + size) % size) != 0)  // 逆时针找到右极值点
                break;
            --idx;
        }
        reverse(oneChain.begin(), oneChain.end());
        Chains.emplace_back(oneChain);
        oneChain.clear();
    }

    return Chains;
}

void PolygonChain::SMC_SL(const std::vector<std::vector<int>> &chains, const std::vector<Point2d> &polygon, int pFlag)
{
    int                           size = polygon.size();
    std::vector<std::vector<int>> SMChains;
    for (auto &chain : chains)
    {
        std::vector<int> curChain;  // 保存严格单调链(不分严格增或者严格减)
        curChain.emplace_back(chain[0]);
        curChain.emplace_back(chain[1]);
        bool flag = polygon[chain[0]].y() < polygon[chain[1]].y() ? true : false;  // true为增，false为减

        for (int i = 2; i < chain.size(); ++i)
        {
            if (flag == true)
            {
                if (polygon[chain[(i - 1 + size) % size]].y() < polygon[chain[i]].y())  // 持续递增
                    curChain.emplace_back(chain[i]);
                else
                {
                    flag = false;
                    SMChains.emplace_back(curChain);

                    addSweepLine(polygon, curChain, pFlag);

                    curChain.clear();
                    curChain.emplace_back(chain[(i - 1 + size) % size]);
                    curChain.emplace_back(chain[i]);
                }
            }
            else
            {
                if (polygon[chain[(i - 1 + size) % size]].y() > polygon[chain[i]].y())  // 持续递减
                    curChain.emplace_back(chain[i]);
                else
                {
                    flag = true;
                    SMChains.emplace_back(curChain);

                    addSweepLine(polygon, curChain, pFlag);

                    curChain.clear();
                    curChain.emplace_back(chain[(i - 1 + size) % size]);
                    curChain.emplace_back(chain[i]);
                }
            }
        }

        addSweepLine(polygon, curChain, pFlag);
        SMChains.emplace_back(curChain);
    }

    return;
}

void PolygonChain::addSweepLine(const std::vector<Point2d> &polygon, const std::vector<int> &curChain, int pFlag)
{
    if (pFlag == 1)
    {
        sweepLine[polygon[curChain[0]].x()].insert({curChain, 1});
        sweepLine[polygon[curChain[curChain.size() - 1]].x()].insert({curChain, 1});
    }
    else
    {
        sweepLine[polygon[curChain[0]].x()].insert({curChain, 2});
        sweepLine[polygon[curChain[curChain.size() - 1]].x()].insert({curChain, 2});
    }
}

std::vector<Point2d> PolygonChain::getCrossPt(const std::vector<Point2d> &polygon1, const std::vector<Point2d> &polygon2)
{
    std::set<std::pair<double, double>>           ptOnLines;  // 存储已经添加的端点
    std::vector<Point2d>                          CrossPts;
    std::set<std::pair<std::vector<int>, int>>    curChain;  // first为存储polygon点所在的下标，second表示属于哪个polygon
    std::vector<std::pair<std::vector<int>, int>> newChain;
    int                                           p1size = polygon1.size();
    int                                           p2size = polygon2.size();

    for (auto &sL : sweepLine)
    {
        // 清除右极值点过该扫描线的严格单调链, 加入左极值点过该扫描线的严格单调链
        for (auto &chain : sL.second)
        {
            auto check = curChain.find(chain);
            if (check != curChain.end())
                curChain.erase(check);
            else
                newChain.emplace_back(chain);
        }

        if (newChain.empty())
            continue;

        // 已存在的严格单调链与新加入的严格单调链进行两两求交
        for (auto &curC : curChain)
        {
            for (auto &newC : newChain)
            {
                if (curC.second == newC.second)
                    continue;

                Point2d pt1Begin;
                Point2d pt1End;
                Point2d pt2Begin;
                Point2d pt2End;
                if (curC.second == 1)
                {
                    pt1Begin = polygon1[curC.first[0]];
                    pt1End   = polygon1[curC.first[curC.first.size() - 1]];
                    pt2Begin = polygon2[newC.first[0]];
                    pt2End   = polygon2[newC.first[newC.first.size() - 1]];
                }
                else
                {
                    pt1Begin = polygon2[curC.first[0]];
                    pt1End   = polygon2[curC.first[curC.first.size() - 1]];
                    pt2Begin = polygon1[newC.first[0]];
                    pt2End   = polygon1[newC.first[newC.first.size() - 1]];
                }

                if (!collisionDect(pt1Begin, pt1End, pt2Begin, pt2End))  // 严格单调连碰撞检测
                    continue;
                else
                {
                    std::vector<int> idxCurVec = curC.first;  // 已存在严格单调链每个点的下标
                    std::vector<int> idxNewVec = newC.first;  // 新加入严格单调链每个点的下标

                    for (int i = 0; i < idxCurVec.size() - 1; ++i)
                    {
                        pt1Begin = curC.second == 1 ? polygon1[idxCurVec[i]] : polygon2[idxCurVec[i]];
                        pt1End   = curC.second == 1 ? polygon1[(idxCurVec[i] + 1) % p1size] : polygon2[(idxCurVec[i] + 1) % p2size];
                        for (int j = 0; j < idxNewVec.size() - 1; ++j)
                        {
                            pt2Begin = newC.second == 1 ? polygon1[idxNewVec[j]] : polygon2[idxNewVec[j]];
                            pt2End   = newC.second == 1 ? polygon1[(idxNewVec[j] + 1) % p1size] : polygon2[(idxNewVec[j] + 1) % p2size];
                            if (collisionDect(pt1Begin, pt1End, pt2Begin, pt2End))
                            {
                                if (crossDect(pt1Begin, pt1End, pt2Begin, pt2End))
                                {
                                    auto crossPt = calcCrossPt(pt1Begin, pt1End, pt2Begin, pt2End);
                                    CrossPts.emplace_back(crossPt);
                                    continue;
                                }
                                else
                                {
                                    if (onLineDect(pt1Begin, pt2Begin, pt2End) && ptOnLines.count({pt1Begin.x(), pt1Begin.y()}) == 0)
                                    {
                                        ptOnLines.insert({pt1Begin.x(), pt1Begin.y()});
                                        CrossPts.emplace_back(pt1Begin);
                                    }
                                    if (onLineDect(pt1End, pt2Begin, pt2End) && ptOnLines.count({pt1End.x(), pt1End.y()}) == 0)
                                    {
                                        ptOnLines.insert({pt1End.x(), pt1End.y()});
                                        CrossPts.emplace_back(pt1End);
                                    }
                                    if (onLineDect(pt2Begin, pt1Begin, pt1End) && ptOnLines.count({pt2Begin.x(), pt2Begin.y()}) == 0)
                                    {
                                        ptOnLines.insert({pt2Begin.x(), pt2Begin.y()});
                                        CrossPts.emplace_back(pt2Begin);
                                    }
                                    if (onLineDect(pt2End, pt1Begin, pt1End) && ptOnLines.count({pt2End.x(), pt2End.y()}) == 0)
                                    {
                                        ptOnLines.insert({pt2End.x(), pt2End.y()});
                                        CrossPts.emplace_back(pt2End);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        // 新加入的严格单调链之间进行两两求交
        for (int i = 0; i < newChain.size() - 1; ++i)
        {
            auto C1st = newChain[i];
            for (int j = i + 1; j < newChain.size(); ++j)
            {
                auto C2nd = newChain[j];
                if (C1st.second == C2nd.second)  // 属于同一多边形无需求交（非自交）
                    continue;

                Point2d pt1Begin;
                Point2d pt1End;
                Point2d pt2Begin;
                Point2d pt2End;
                if (C1st.second == 1)
                {
                    pt1Begin = polygon1[C1st.first[0]];
                    pt1End   = polygon1[C1st.first[C1st.first.size() - 1]];
                    pt2Begin = polygon2[C2nd.first[0]];
                    pt2End   = polygon2[C2nd.first[C2nd.first.size() - 1]];
                }
                else
                {
                    pt1Begin = polygon2[C1st.first[0]];
                    pt1End   = polygon2[C1st.first[C1st.first.size() - 1]];
                    pt2Begin = polygon1[C2nd.first[0]];
                    pt2End   = polygon1[C2nd.first[C2nd.first.size() - 1]];
                }

                if (pt1Begin == pt2Begin)  // 有相同左端点的两两严格单调链无需求交
                    continue;
                else
                {
                    if (!collisionDect(pt1Begin, pt1End, pt2Begin, pt2End))  // 严格单调连碰撞检测
                        continue;
                    else
                    {
                        std::vector<int> firstVec  = C1st.first;
                        std::vector<int> secondVec = C2nd.first;
                        for (int m = 0; m < firstVec.size() - 1; ++m)
                        {
                            pt1Begin = C1st.second == 1 ? polygon1[firstVec[m]] : polygon2[firstVec[m]];
                            pt1End   = C1st.second == 1 ? polygon1[(firstVec[m] + 1) % p1size] : polygon2[(firstVec[m] + 1) % p2size];
                            for (int n = 0; n < secondVec.size() - 1; ++n)
                            {
                                pt2Begin = C2nd.second == 1 ? polygon1[secondVec[n]] : polygon2[secondVec[n]];
                                pt2End   = C2nd.second == 1 ? polygon1[(secondVec[n] + 1) % p1size] : polygon2[(secondVec[n] + 1) % p2size];
                                if (collisionDect(pt1Begin, pt1End, pt2Begin, pt2End))
                                {
                                    if (crossDect(pt1Begin, pt1End, pt2Begin, pt2End))
                                    {
                                        auto crossPt = calcCrossPt(pt1Begin, pt1End, pt2Begin, pt2End);
                                        CrossPts.emplace_back(crossPt);
                                        continue;
                                    }
                                    else
                                    {
                                        if (onLineDect(pt1Begin, pt2Begin, pt2End) && ptOnLines.count({pt1Begin.x(), pt1Begin.y()}) == 0)
                                        {
                                            ptOnLines.insert({pt1Begin.x(), pt1Begin.y()});
                                            CrossPts.emplace_back(pt1Begin);
                                        }
                                        if (onLineDect(pt1End, pt2Begin, pt2End) && ptOnLines.count({pt1End.x(), pt1End.y()}) == 0)
                                        {
                                            ptOnLines.insert({pt1End.x(), pt1End.y()});
                                            CrossPts.emplace_back(pt1End);
                                        }
                                        if (onLineDect(pt2Begin, pt1Begin, pt1End) && ptOnLines.count({pt2Begin.x(), pt2Begin.y()}) == 0)
                                        {
                                            ptOnLines.insert({pt2Begin.x(), pt2Begin.y()});
                                            CrossPts.emplace_back(pt2Begin);
                                        }
                                        if (onLineDect(pt2End, pt1Begin, pt1End) && ptOnLines.count({pt2End.x(), pt2End.y()}) == 0)
                                        {
                                            ptOnLines.insert({pt2End.x(), pt2End.y()});
                                            CrossPts.emplace_back(pt2End);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }

            // 特判垂直线段，用完就丢,否则加入到curChain中
            if (C1st.second == 1)
            {
                int cSize = newChain[i].first.size();
                if (polygon1[newChain[i].first[0]].x() != polygon1[newChain[i].first[(cSize - 1) % cSize]].x())
                    curChain.insert(newChain[i]);
            }
            else
            {
                int cSize = newChain[i].first.size();
                if (polygon2[newChain[i].first[0]].x() != polygon2[newChain[i].first[(cSize - 1) % cSize]].x())
                    curChain.insert(newChain[i]);
            }
        }
        curChain.insert(newChain[newChain.size() - 1]);  // TODO:忘了这里为什么要再加最后一次
        newChain.clear();                                // 记得清空
    }
    return CrossPts;
}

Point2d PolygonChain::calcCrossPt(const Point2d &p1, const Point2d &p2, const Point2d &p3, const Point2d &p4)
{
    double slope1 = 0;
    double slope2 = 0;
    double b1     = 0;
    double b2     = 0;
    double resX   = 0;
    double resY   = 0;

    if (p1.x() != p2.x())
        slope1 = (p1.y() - p2.y()) / (p1.x() - p2.x());
    else
    {  // 避免出现一条线是垂直的情况
        resX   = p1.x();
        slope2 = (p3.y() - p4.y()) / (p3.x() - p4.x());
        b2     = p3.y() - slope2 * p3.x();
        resY   = resX * slope2 + b2;
        return Point2d(resX, resY);
    }

    if (p3.x() != p4.x())
        slope2 = (p3.y() - p4.y()) / (p3.x() - p4.x());
    else
    {
        resX = p3.x();
        b1   = p1.y() - slope1 * p1.x();
        resY = resX * slope1 + b1;
        return Point2d(resX, resY);
    }

    b1 = p1.y() - slope1 * p1.x();
    b2 = p3.y() - slope2 * p3.x();

    if (b2 - b1 == 0)
        resX = 0;
    else
        resX = (b2 - b1) / (slope1 - slope2);

    resY = slope1 * resX + b1;
    return Point2d(resX, resY);
}

bool PolygonChain::collisionDect(const Point2d &p1, const Point2d &p2, const Point2d &p3, const Point2d &p4)
{
    double x1max = std::max(p1.x(), p2.x());
    double x1min = std::min(p1.x(), p2.x());
    double y1max = std::max(p1.y(), p2.y());
    double y1min = std::min(p1.y(), p2.y());

    double x2max = std::max(p3.x(), p4.x());
    double x2min = std::min(p3.x(), p4.x());
    double y2max = std::max(p3.y(), p4.y());
    double y2min = std::min(p3.y(), p4.y());

    bool checkX = false;
    bool checkY = false;

    if ((x1max >= x2min && x1max <= x2max) || (x1min >= x2min && x1min <= x2max) || (x2max >= x1min && x2max <= x1max) ||
        (x2max > x1min && x2max <= x1max))
        checkX = true;
    if ((y1max >= y2min && y1max <= y2max) || (y1min >= y2min && y1min <= y2max) || (y2max >= y1min && y2max <= y1max) ||
        (y2max > y1min && y2max <= y1max))
        checkY = true;

    return checkX && checkY;
}

bool PolygonChain::crossDect(const Point2d &p1, const Point2d &p2, const Point2d &p3, const Point2d &p4)
{
    auto   p1p3  = Point2d(p3.x() - p1.x(), p3.y() - p1.y());
    auto   p1p2  = Point2d(p2.x() - p1.x(), p2.y() - p1.y());
    auto   p1p4  = Point2d(p4.x() - p1.x(), p4.y() - p1.y());
    double left  = p1p3.x() * p1p2.y() - p1p3.y() * p1p2.x();
    double right = p1p4.x() * p1p2.y() - p1p4.y() * p1p2.x();
    double res1  = left * right;

    auto p3p1   = Point2d(p1.x() - p3.x(), p1.y() - p3.y());
    auto p3p4   = Point2d(p4.x() - p3.x(), p4.y() - p3.y());
    auto p3p2   = Point2d(p2.x() - p3.x(), p2.y() - p3.y());
    left        = p3p1.x() * p3p4.y() - p3p1.y() * p3p4.x();
    right       = p3p2.x() * p3p4.y() - p3p2.y() * p3p4.x();
    double res2 = left * right;

    return (res1 < 0 && res2 < 0) ? true : false;
}

bool PolygonChain::onLineDect(const Point2d &p, const Point2d &p1, const Point2d &p2)
{
    auto pXpl = Point2d(p1.x() - p.x(), p1.y() - p.y());
    auto pXp2 = Point2d(p2.x() - p.x(), p2.y() - p.y());

    double result = pXpl.x() * pXp2.y() - pXpl.y() * pXp2.x();

    if (distance(p, p1) + distance(p, p2) == distance(p1, p2))
        return result == 0 ? true : false;

    return false;
}
