#include "sweep_line.h"

SweepLine::SweepLine(std::vector<segment_2d>& segmentVec)
{
    ResetSegmentsPoints(segmentVec);

    std::vector<Segment2d> processedSegments;
    for (auto& segment : segmentVec)
    {
        processedSegments.emplace_back(Segment2d(segment));
        m_allCrossPoints.emplace(segment.first);
        m_allCrossPoints.emplace(segment.second);
    }

    for (auto& segment : processedSegments)
    {
        m_pointQueue.emplace(PointEvent(segment.GetSegment().first, EventType::StartPoint, segment));
        m_pointQueue.emplace(PointEvent(segment.GetSegment().second, EventType::EndPoint, segment));
    }
}

// 默认输入的线段第一个点是起点，第二个点是终点，因此要输入已经处理过的线段
SweepLine::SweepLine(std::vector<Segment2d>& segmentVec)
{
    for (auto& segment : segmentVec)
    {
        m_pointQueue.emplace(PointEvent(segment.GetSegment().first, EventType::StartPoint, segment));
        m_pointQueue.emplace(PointEvent(segment.GetSegment().second, EventType::EndPoint, segment));
        m_allCrossPoints.emplace(segment.GetSegment().first);
        m_allCrossPoints.emplace(segment.GetSegment().second);
    }
}

void SweepLine::PrintPointQueue()
{
    while (!m_pointQueue.empty())
    {
        PointEvent pointEvent = m_pointQueue.top();
        m_pointQueue.pop();

        std::cout << bg::get<0>(pointEvent.GetPoint()) << " " << bg::get<1>(pointEvent.GetPoint()) << std::endl;
        std::cout << pointEvent.GetSegments()[0] << std::endl;
    }
}

void SweepLine::PrintSegmentTree()
{
    std::cout << "打印线段树" << std::endl;
    for (auto& segment : m_segmentTree)
        std::cout << segment << std::endl;
}

void SweepLine::ResetSegmentsPoints(std::vector<segment_2d>& segments)
{
    point_2d tempPoint2d, startPoint2d, endPoint2d;
    for (auto& segment : segments)
    {
        if (bg::get<0>(segment.first) < bg::get<0>(segment.second))
        {
            startPoint2d = segment.first;
            endPoint2d   = segment.second;
        }
        else if (bg::get<0>(segment.first) == bg::get<0>(segment.second))
        {
            if (bg::get<1>(segment.first) < bg::get<1>(segment.second))
            {
                startPoint2d = segment.first;
                endPoint2d   = segment.second;
            }
            else
            {
                startPoint2d = segment.second;
                endPoint2d   = segment.first;
            }
        }
        else
        {
            startPoint2d = segment.second;
            endPoint2d   = segment.first;
        }

        segment.first  = startPoint2d;
        segment.second = endPoint2d;
    }
}

void SweepLine::UpdateSegmentTree(double sweepLineXPos, double sweepLineYPos)
{
    // TODO: 这里应该能优化
    for (auto it = m_segmentTree.begin(); it != m_segmentTree.end(); it++)
    {
        (const_cast<Segment2d&>(*it)).UpdateSweepLineCrossPoint(sweepLineXPos, sweepLineYPos);
    }
}

void SweepLine::EmplaceCrossPoint(int& a, int& b)
{
    std::vector<point_2d> crossPoint;
    bg::intersection(m_segmentTree[a].GetSegment(), m_segmentTree[b].GetSegment(), crossPoint);

    for (auto& point : crossPoint)
    {
        if (m_allCrossPoints.find(point) == m_allCrossPoints.end())
        {
            m_allCrossPoints.emplace(point);
            m_pointQueue.emplace(PointEvent(point, EventType::CrossPoint, Segment2d(m_segmentTree[a].GetSegment()),
                                            Segment2d(m_segmentTree[b].GetSegment())));
        }
    }
}

void SweepLine::Scan()
{
    while (!m_pointQueue.empty())
    {
        PointEvent pointEvent = m_pointQueue.top();
        m_pointQueue.pop();

        // std::cout << "(" << bg::get<0>(pointEvent.GetPoint()) << ", " << bg::get<1>(pointEvent.GetPoint()) << ") "
        //           << static_cast<std::underlying_type<EventType>::type>(pointEvent.GetEventType())
        //           << " Line1: " << pointEvent.GetSegments()[0] << " Line2: " << pointEvent.GetSegments()[1] << std::endl;

        // 更新所有线段的排序标准
        m_sweepLineXPos = bg::get<0>(pointEvent.GetPoint());
        UpdateSegmentTree(m_sweepLineXPos, bg::get<1>(pointEvent.GetPoint()));

        // 点类型
        if (pointEvent.GetEventType() == EventType::StartPoint)
        {
            // 起点
            // 加入线段，并与其左右两条判交

            // 去重
            int i;
            for (i = 0; i < m_segmentTree.size(); i++)
            {
                if (m_segmentTree[i] == pointEvent.GetSegments()[0])
                    break;
            }
            if (i == m_segmentTree.size())
                m_segmentTree.emplace_back(pointEvent.GetSegments()[0]);
            else
                continue;

            sort(m_segmentTree.begin(), m_segmentTree.end(), [](Segment2d& a, Segment2d& b) -> bool {
                // SweepLineCrossPoint.x 肯定一样
                if (!(abs(bg::get<1>(a.GetSweepLineCrossPoint()) - bg::get<1>(b.GetSweepLineCrossPoint())) < EPS))
                    return bg::get<1>(a.GetSweepLineCrossPoint()) < bg::get<1>(b.GetSweepLineCrossPoint());
                else if (!(abs(bg::get<1>(a.GetSegment().second) != bg::get<1>(b.GetSegment().second)) < EPS))
                    return bg::get<1>(a.GetSegment().second) < bg::get<1>(b.GetSegment().second);
                else
                    return bg::get<0>(a.GetSegment().second) < bg::get<0>(b.GetSegment().second);
            });

            // 查找线段位置
            int it;
            for (int i = 0; i < m_segmentTree.size(); i++)
            {
                if (pointEvent.GetSegments()[0] == m_segmentTree[i])
                {
                    it = i;
                    break;
                }
            }
            auto prevIt = it - 1;
            auto nextIt = it + 1;

            // nextIt 存在
            if (nextIt != m_segmentTree.size())
                EmplaceCrossPoint(it, nextIt);
            // prevIt 存在
            if (prevIt != -1)
                EmplaceCrossPoint(it, prevIt);
        }
        else if (pointEvent.GetEventType() == EventType::EndPoint)
        {
            // 终点
            // 线段左右判交，并删除线段

            int it;
            int i;
            for (i = 0; i < m_segmentTree.size(); i++)
            {
                if (pointEvent.GetSegments()[0] == m_segmentTree[i])
                {
                    it = i;
                    break;
                }
            }
            if (i == m_segmentTree.size())
                continue;

            auto prevIt = it - 1;
            auto nextIt = it + 1;

            // prevIt 和 nextIt 存在
            if (prevIt != -1 && nextIt != m_segmentTree.size())
                EmplaceCrossPoint(prevIt, nextIt);

            m_segmentTree.erase(m_segmentTree.begin() + it);
        }
        else
        {
            // 交点
            // 线段各自跟左右求交，再交换位置

            // 只要先处理交点再处理终点就不会出现找不到线段的情况
            int firstSegmentIt = 0;
            int i;
            for (i = 0; i < m_segmentTree.size(); i++)
            {
                if (pointEvent.GetSegments()[0] == m_segmentTree[i])
                {
                    firstSegmentIt = i;
                    break;
                }
            }
            // if (i == m_segmentTree.size())
            //     continue;

            int secondSegmentIt = 0;
            for (i = 0; i < m_segmentTree.size(); i++)
            {
                if (pointEvent.GetSegments()[1] == m_segmentTree[i])
                {
                    secondSegmentIt = i;
                    break;
                }
            }
            // if (i == m_segmentTree.size())
            //     continue;

            //// 起点不交换
            // if (bg::get<0>(m_segmentTree[firstSegmentIt].GetSegment().first) == m_sweepLineXPos &&
            //     bg::get<0>(m_segmentTree[secondSegmentIt].GetSegment().first) == m_sweepLineXPos)
            //     continue;

            if (firstSegmentIt + 1 == secondSegmentIt)
            {
                auto nextIt = secondSegmentIt + 1;
                // nextIt 存在
                if (nextIt != m_segmentTree.size())
                    EmplaceCrossPoint(nextIt, firstSegmentIt);

                auto prevIt = firstSegmentIt - 1;
                // prevIt 存在
                if (prevIt != -1)
                    EmplaceCrossPoint(prevIt, secondSegmentIt);
            }
            else
            {
                auto prevIt = secondSegmentIt - 1;
                // prevIt 存在
                if (prevIt != -1)
                    EmplaceCrossPoint(prevIt, firstSegmentIt);

                auto nextIt = firstSegmentIt + 1;
                // nextIt 存在
                if (nextIt != m_segmentTree.size())
                    EmplaceCrossPoint(nextIt, secondSegmentIt);
            }

            Segment2d tmpSegment           = m_segmentTree[firstSegmentIt];
            m_segmentTree[firstSegmentIt]  = m_segmentTree[secondSegmentIt];
            m_segmentTree[secondSegmentIt] = tmpSegment;
        }

        // PrintSegmentTree();
    }
}
