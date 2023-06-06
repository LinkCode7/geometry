#pragma once

#include "../boolean_geometry_pch.h"

class Segment2d
{
public:
    Segment2d()
    {
        m_segment2d           = segment_2d();
        m_sweepLineCrossPoint = point_2d();
    }
    Segment2d(const segment_2d& segment2d);
    Segment2d(const Segment2d& other)
    {
        this->m_segment2d           = other.m_segment2d;
        this->m_sweepLineCrossPoint = other.m_sweepLineCrossPoint;
        this->m_k                   = other.m_k;
        this->m_isNoK               = other.m_isNoK;
    }
    ~Segment2d() {}

    Segment2d operator=(const Segment2d& other);
    bool      operator==(const Segment2d& other) const;
    bool      operator<(const Segment2d& other) const;
    bool      operator>(const Segment2d& other) const;

    friend std::ostream& operator<<(std::ostream& out, Segment2d& other);
    friend std::ostream& operator<<(std::ostream& out, const Segment2d& other);

    inline segment_2d GetSegment() const { return m_segment2d; }
    // segment_2d        GetOriginSegment() const;
    inline point_2d GetSweepLineCrossPoint() const { return m_sweepLineCrossPoint; }
    inline bool     GetIsNoK() const { return m_isNoK; }

    void UpdateSweepLineCrossPoint(double x, double y);

private:
    segment_2d m_segment2d;
    // point_2d   m_originStartPoint;
    point_2d m_sweepLineCrossPoint;
    double   m_k;
    bool     m_isNoK;
};