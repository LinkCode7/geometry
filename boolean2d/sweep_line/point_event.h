#pragma once

#include <vector>

#include "../boolean_geometry_pch.h"
#include "segment.h"

enum class EventType : int
{
    StartPoint = 0,
    EndPoint   = 2,
    CrossPoint = 1,
};

// 会重定义
// std::ostream& operator<<(std::ostream& out, const EventType eventType)
//{
//     switch (eventType)
//     {
//         case EventType::StartPoint:
//             out << 1;
//             break;
//         case EventType::EndPoint:
//             out << 2;
//             break;
//         case EventType::CrossPoint:
//             out << 3;
//             break;
//         default:
//             break;
//     }
//
//     return out;
// }

// 点事件
class PointEvent
{
public:
    // PointEvent() {}
    // PointEvent(point_2d point2d) : m_point2d(point2d){};
    PointEvent(const point_2d& point2d, EventType eventType, const Segment2d& segment2d) : m_point2d(point2d), m_eventType(eventType)
    {
        m_segments2d    = std::vector<Segment2d>(2);
        m_segments2d[0] = segment2d;
    }
    PointEvent(const point_2d& point2d, EventType eventType, const Segment2d& segment2d, const Segment2d& anotherSegment2d)
        : m_point2d(point2d), m_eventType(eventType)
    {
        m_segments2d    = std::vector<Segment2d>(2);
        m_segments2d[0] = segment2d;
        m_segments2d[1] = anotherSegment2d;
    }
    PointEvent(const PointEvent& other)
    {
        this->m_point2d   = other.m_point2d;
        this->m_eventType = other.m_eventType;

        if (this->m_segments2d.size() == 0)
            this->m_segments2d = std::vector<Segment2d>(2);

        // TODO: 定死了
        for (int i = 0; i < 2; i++)
        {
            this->m_segments2d[i] = other.m_segments2d[i];
        }
    }
    ~PointEvent() {}

    bool operator<(const PointEvent& other) const;
    bool operator>(const PointEvent& other) const;

    inline point_2d               GetPoint() const { return m_point2d; };
    inline EventType              GetEventType() const { return m_eventType; };
    inline std::vector<Segment2d> GetSegments() const { return m_segments2d; };

private:
    point_2d               m_point2d;
    EventType              m_eventType;
    std::vector<Segment2d> m_segments2d;
};