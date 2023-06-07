#pragma once

#include "../boolean_pch.h"

enum class EventType : int
{
    StartPoint = 0,
    EndPoint   = 1,
};

// 点事件
class PointEvent
{
public:
    PointEvent()
    {
        m_point2d    = point_2d();
        m_eventType  = EventType::StartPoint;
        m_otherEvent = nullptr;
    }
    PointEvent(point_2d const& point2d, EventType eventType) : m_point2d(point2d), m_eventType(eventType), m_otherEvent(nullptr) {}
    PointEvent(point_2d const& point2d, EventType eventType, PointEvent* otherEvent)
        : m_point2d(point2d), m_eventType(eventType), m_otherEvent(otherEvent)
    {
    }
    PointEvent(point_2d const& point2d, EventType eventType, PointEvent& otherEvent)
        : m_point2d(point2d), m_eventType(eventType), m_otherEvent(&otherEvent)
    {
    }
    PointEvent(PointEvent const& other) : m_point2d(other.m_point2d), m_eventType(other.m_eventType)
    {
        m_otherEvent = new PointEvent(other.m_otherEvent->m_point2d, other.m_otherEvent->m_eventType, other.m_otherEvent->m_otherEvent);
    }
    ~PointEvent()
    {
        // TODO: 不知道为什么不能删，删了就报错
        // if (m_otherEvent)
        //     delete m_otherEvent;
    }

    bool operator==(PointEvent const& other) const;
    bool operator<(PointEvent const& other) const;
    bool operator>(PointEvent const& other) const;

    inline point_2d    getPoint() const { return m_point2d; };
    inline EventType   getEventType() const { return m_eventType; };
    inline PointEvent* getOtherEvent() const { return m_otherEvent; };

    inline void setEventType(EventType eventType) { m_eventType = eventType; }
    inline void setOtherEvent(PointEvent& otherEvent) { m_otherEvent = &otherEvent; };

private:
    point_2d    m_point2d;    // 该点
    EventType   m_eventType;  // 点的类型
    PointEvent* m_otherEvent; // 另一个相连的点
};