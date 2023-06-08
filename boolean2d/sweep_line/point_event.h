#pragma once

#include "../boolean_pch.h"

enum class EventType : int
{
    EndPoint   = 0,
    StartPoint = 1,
};

// 点事件
class PointEvent
{
public:
    PointEvent() : m_point2d(point_2d()), m_eventType(EventType::StartPoint), m_otherEventSP(std::shared_ptr<PointEvent>()) {}
    PointEvent(point_2d const& point2d, EventType eventType)
        : m_point2d(point2d), m_eventType(eventType), m_otherEventSP(std::shared_ptr<PointEvent>())
    {
    }
    PointEvent(point_2d const& point2d, EventType eventType, std::shared_ptr<PointEvent> const& otherEventSP) // 传入指针
        : m_point2d(point2d), m_eventType(eventType), m_otherEventSP(otherEventSP)
    {
    }
    PointEvent(point_2d const& point2d, EventType eventType, PointEvent const& otherEvent) // 传入对象
        : m_point2d(point2d), m_eventType(eventType), m_otherEventSP(std::make_shared<PointEvent>(otherEvent))
    {
    }
    PointEvent(PointEvent const& other) : m_point2d(other.m_point2d), m_eventType(other.m_eventType), m_otherEventSP(other.m_otherEventSP)
    {
        // 太舒服了，共享指针的逻辑比原始指针的逻辑好多了，浅拷贝就能达到深拷贝的效果
        // m_otherEventSP = std::make_shared<PointEvent>(other.m_otherEventSP->m_point2d, other.m_otherEventSP->m_eventType,
        //                                               other.m_otherEventSP->m_otherEventSP);
    }

    bool operator==(PointEvent const& other) const;
    bool operator<(PointEvent const& other) const;
    bool operator>(PointEvent const& other) const;

    inline point_2d                    getPoint() const { return m_point2d; };
    inline EventType                   getEventType() const { return m_eventType; };
    inline std::shared_ptr<PointEvent> getOtherEvent() const { return m_otherEventSP; };

    inline void setEventType(EventType eventType) { m_eventType = eventType; }
    inline void setOtherEvent(std::shared_ptr<PointEvent> otherEvent) { m_otherEventSP = otherEvent; };

private:
    point_2d                    m_point2d;      // 该点
    EventType                   m_eventType;    // 点的类型
    std::shared_ptr<PointEvent> m_otherEventSP; // 另一个相连的点
};