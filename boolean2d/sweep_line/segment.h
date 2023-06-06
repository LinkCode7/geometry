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

    // friend std::ostream& operator<<(std::ostream& out, Segment2d& other);
    friend std::ostream& operator<<(std::ostream& out, Segment2d const& other);

    inline segment_2d getSegment() const { return m_segment2d; }
    inline void       setSegmentSecond(point_2d second) { m_segment2d.second = second; };
    inline void       setSegmentSecond(PointEvent secondPointEvent) { m_segment2d.second = secondPointEvent.getPoint(); };
    inline PointEvent getStartPointEvent() const { return m_startPointEvent; }
    inline void       setStartPointEvent(PointEvent startPointEvent) { m_startPointEvent = startPointEvent; }
    inline point_2d   getSweepLineCrossPoint() const { return m_sweepLineCrossPoint; }
    inline bool       getIsNoK() const { return m_isNoK; }

    void updateSweepLineCrossPoint(double const x, double const y);

private:
    segment_2d m_segment2d;
    PointEvent m_startPointEvent;
    point_2d   m_sweepLineCrossPoint;
    double     m_k;
    bool       m_isNoK;
};