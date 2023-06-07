#pragma once

#include "../boolean_pch.h"
#include "point_event.h"

class Segment2d
{
public:
    Segment2d() : m_segment2d(segment_2d()), m_startPointEvent(PointEvent()), m_sweepLineCrossPoint(point_2d()), m_k(0.0), m_isNoK(false) {}
    Segment2d(PointEvent const& pointEvent, PointEvent const& anotherPointEvent);
    Segment2d(Segment2d const& other)
        : m_segment2d(other.m_segment2d),
          m_startPointEvent(other.m_startPointEvent),
          m_sweepLineCrossPoint(other.m_sweepLineCrossPoint),
          m_k(other.m_k),
          m_isNoK(other.m_isNoK)
    {
    }
    ~Segment2d() {}

    Segment2d operator=(Segment2d const& other);
    bool      operator==(Segment2d const& other) const;
    bool      operator<(Segment2d const& other) const;
    bool      operator>(Segment2d const& other) const;

    friend std::ostream& operator<<(std::ostream& out, Segment2d const& other);

    inline segment_2d getSegment() const { return m_segment2d; }
    inline PointEvent getStartPointEvent() const { return m_startPointEvent; }
    inline point_2d   getSweepLineCrossPoint() const { return m_sweepLineCrossPoint; }
    inline bool       getIsNoK() const { return m_isNoK; }

    inline void setSegmentSecond(point_2d const& second) { m_segment2d.second = second; };
    inline void setSegmentSecond(PointEvent const& secondPointEvent) { m_segment2d.second = secondPointEvent.getPoint(); };
    inline void setStartPointEvent(PointEvent startPointEvent) { m_startPointEvent = startPointEvent; } // TODO: 不知道为什么加 & 会报错

public:
    // TODO: 应该设成 private: 的，不过要先给树设个友元
    void updateSweepLineCrossPoint(double x, double y);

private:
    segment_2d m_segment2d;           // 该线段，优化的时候可以考虑去掉这个变量
    PointEvent m_startPointEvent;     // 起点事件，用来查找另一点的事件
    point_2d   m_sweepLineCrossPoint; // 与扫描线的交点，用来排序
    double     m_k;                   // 斜率
    bool       m_isNoK;               // 是否平行扫描线（扫描线默认垂直 x 轴）
};