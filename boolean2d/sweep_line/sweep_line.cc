#include "sweep_line.h"

SweepLine::SweepLine(std::vector<segment_2d>& originalSegments)
{
    // 调整起始点
    ResetSegmentsPoints(originalSegments);

    for (auto& segment : originalSegments)
    {
        PointEvent startPointEvent(segment.first, EventType::StartPoint);
        PointEvent endPointEvent(segment.second, EventType::EndPoint);
        startPointEvent.setOtherEvent(endPointEvent);
        endPointEvent.setOtherEvent(startPointEvent);
        m_pointQueue.emplace(startPointEvent);
        m_pointQueue.emplace(endPointEvent);
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
    for (auto it = m_segmentTree.begin(); it != m_segmentTree.end(); it++)
    {
        (const_cast<Segment2d&>(*it)).updateSweepLineCrossPoint(sweepLineXPos, sweepLineYPos);
    }
}

void SweepLine::EmplaceCrossPoint(int& a, int& b)
{
    std::vector<point_2d> crossPoints;
    bg::intersection(m_segmentTree[a].getSegment(), m_segmentTree[b].getSegment(), crossPoints);
    if (crossPoints.size() == 0)
        return;

    // TODO: 不知道 crossPoint 是否已经排序，不过其实只要 swap() 一下最多了
    // 排序至与 m_priorityQueue 同序
    std::sort(crossPoints.begin(), crossPoints.end(), [](point_2d const& a, point_2d const& b) -> bool {
        if (!IS_FLOAT_EQUAL(bg::get<0>(a), bg::get<0>(b)))
            return bg::get<0>(a) < bg::get<0>(b);
        else
            return bg::get<1>(a) < bg::get<1>(b);
    });

    // 取数据
    point_2d   crossPoint       = crossPoints[0];
    Segment2d  segmentA         = m_segmentTree[a];
    PointEvent aStartPointEvent = segmentA.getStartPointEvent();       // 会变
    PointEvent aEndPointEvent   = *(aStartPointEvent.getOtherEvent()); // 不变
    Segment2d  segmentB         = m_segmentTree[b];
    PointEvent bStartPointEvent = segmentB.getStartPointEvent();       // 会变
    PointEvent bEndPointEvent   = *(bStartPointEvent.getOtherEvent()); // 不变

    // 裁剪线段
    for (int i = 0; i < crossPoints.size(); i++)
    {
        m_allCrossPoints.emplace(crossPoints[i]);
        crossPoint = crossPoints[i];
        PointEvent crossPointEvent(crossPoint, EventType::EndPoint);

        // 不是 a 的起点或终点
        if ((!IS_FLOAT_EQUAL(bg::get<0>(crossPoint), bg::get<0>(segmentA.getSegment().first)) ||
             !IS_FLOAT_EQUAL(bg::get<1>(crossPoint), bg::get<1>(segmentA.getSegment().first))) &&
            (!IS_FLOAT_EQUAL(bg::get<0>(crossPoint), bg::get<0>(segmentA.getSegment().second)) ||
             !IS_FLOAT_EQUAL(bg::get<1>(crossPoint), bg::get<1>(segmentA.getSegment().second))))
        {
            aStartPointEvent.setEventType(EventType::StartPoint);
            aStartPointEvent.setOtherEvent(crossPointEvent);
            crossPointEvent.setOtherEvent(aStartPointEvent);

            // 只有第二个交点需要加起始点
            if (i == 1)
                m_pointQueue.emplace(aStartPointEvent);
            m_pointQueue.emplace(crossPointEvent);

            // 只有第一个交点需要裁剪线段
            if (i == 0)
            {
                m_segmentTree[a].setStartPointEvent(aStartPointEvent);
                m_segmentTree[a].setSegmentSecond(crossPointEvent.getPoint());
            }

            // 更新 startPointEvent
            aStartPointEvent = crossPointEvent;
        }

        // 不是 b 的起点或终点
        if ((!IS_FLOAT_EQUAL(bg::get<0>(crossPoint), bg::get<0>(segmentB.getSegment().first)) ||
             !IS_FLOAT_EQUAL(bg::get<1>(crossPoint), bg::get<1>(segmentB.getSegment().first))) &&
            (!IS_FLOAT_EQUAL(bg::get<0>(crossPoint), bg::get<0>(segmentB.getSegment().second)) ||
             !IS_FLOAT_EQUAL(bg::get<1>(crossPoint), bg::get<1>(segmentB.getSegment().second))))
        {
            bStartPointEvent.setEventType(EventType::StartPoint);
            bStartPointEvent.setOtherEvent(crossPointEvent);
            crossPointEvent.setOtherEvent(bStartPointEvent);

            // 只有第二个交点需要加起始点
            if (i == 1)
                m_pointQueue.emplace(bStartPointEvent);
            m_pointQueue.emplace(crossPointEvent);

            // 只有第一个交点需要裁剪线段
            if (i == 0)
            {
                m_segmentTree[b].setStartPointEvent(bStartPointEvent);
                m_segmentTree[b].setSegmentSecond(crossPointEvent.getPoint());
            }

            // 更新 startPointEvent
            bStartPointEvent = crossPointEvent;
        }
    }

    // 添加最后一段
    {
        // 不是 a 的起点或终点
        if ((!IS_FLOAT_EQUAL(bg::get<0>(crossPoint), bg::get<0>(segmentA.getSegment().first)) ||
             !IS_FLOAT_EQUAL(bg::get<1>(crossPoint), bg::get<1>(segmentA.getSegment().first))) &&
            (!IS_FLOAT_EQUAL(bg::get<0>(crossPoint), bg::get<0>(segmentA.getSegment().second)) ||
             !IS_FLOAT_EQUAL(bg::get<1>(crossPoint), bg::get<1>(segmentA.getSegment().second))))
        {
            aStartPointEvent.setOtherEvent(aEndPointEvent);
            aStartPointEvent.setEventType(EventType::StartPoint);
            aEndPointEvent.setOtherEvent(aStartPointEvent);
            m_pointQueue.emplace(aStartPointEvent);
            m_pointQueue.emplace(aEndPointEvent);
        }

        // 不是 b 的起点或终点
        if ((!IS_FLOAT_EQUAL(bg::get<0>(crossPoint), bg::get<0>(segmentB.getSegment().first)) ||
             !IS_FLOAT_EQUAL(bg::get<1>(crossPoint), bg::get<1>(segmentB.getSegment().first))) &&
            (!IS_FLOAT_EQUAL(bg::get<0>(crossPoint), bg::get<0>(segmentB.getSegment().second)) ||
             !IS_FLOAT_EQUAL(bg::get<1>(crossPoint), bg::get<1>(segmentB.getSegment().second))))
        {
            bStartPointEvent.setOtherEvent(bEndPointEvent);
            bStartPointEvent.setEventType(EventType::StartPoint);
            bEndPointEvent.setOtherEvent(bStartPointEvent);
            m_pointQueue.emplace(bStartPointEvent);
            m_pointQueue.emplace(bEndPointEvent);
        }
    }
}

void SweepLine::Scan()
{
    while (!m_pointQueue.empty())
    {
        PointEvent pointEvent = m_pointQueue.top();
        m_pointQueue.pop();

        // std::cout << "(" << bg::get<0>(pointEvent.getPoint()) << ", " << bg::get<1>(pointEvent.getPoint()) << ") "
        //           << static_cast<std::underlying_type<EventType>::type>(pointEvent.getEventType()) << " ("
        //           << bg::get<0>(pointEvent.getOtherEvent()->getPoint()) << ", " << bg::get<1>(pointEvent.getOtherEvent()->getPoint())
        //           << ") " << std::endl;

        // 更新所有线段的排序标准
        m_sweepLineXPos = bg::get<0>(pointEvent.getPoint());
        UpdateSegmentTree(m_sweepLineXPos, bg::get<1>(pointEvent.getPoint()));

        // 点类型
        if (pointEvent.getEventType() == EventType::StartPoint)
        {
            // 起点
            // 加入线段，并与其左右两条判交

            //// 去重
            // int i;
            // for (i = 0; i < m_segmentTree.size(); i++)
            //{
            //     if (m_segmentTree[i] == pointEvent.GetSegments()[0])
            //         break;
            // }
            // if (i == m_segmentTree.size())
            //     m_segmentTree.emplace_back(pointEvent.GetSegments()[0]);
            // else
            //     continue;

            Segment2d tmpSegment2d(pointEvent, *(pointEvent.getOtherEvent()));
            m_segmentTree.emplace_back(tmpSegment2d);

            sort(m_segmentTree.begin(), m_segmentTree.end(), [](Segment2d& a, Segment2d& b) -> bool {
                // SweepLineCrossPoint.x 肯定一样
                if (!IS_FLOAT_EQUAL(bg::get<1>(a.getSweepLineCrossPoint()), bg::get<1>(b.getSweepLineCrossPoint())))
                    return bg::get<1>(a.getSweepLineCrossPoint()) < bg::get<1>(b.getSweepLineCrossPoint());
                else if (!IS_FLOAT_EQUAL(bg::get<1>(a.getSegment().second), bg::get<1>(b.getSegment().second)))
                    return bg::get<1>(a.getSegment().second) < bg::get<1>(b.getSegment().second);
                else
                    return bg::get<0>(a.getSegment().second) < bg::get<0>(b.getSegment().second);
            });

            // 查找线段位置
            int it;
            for (int i = 0; i < m_segmentTree.size(); i++)
            {
                if (tmpSegment2d == m_segmentTree[i])
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
        else
        {
            // 终点
            // 线段左右判交，并删除线段

            Segment2d tmpSegment2d(pointEvent, *pointEvent.getOtherEvent());

            int it;

            // 如果能找到
            int i;
            for (i = 0; i < m_segmentTree.size(); i++)
            {
                if (tmpSegment2d == m_segmentTree[i])
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

        // PrintSegmentTree();
    }
}
