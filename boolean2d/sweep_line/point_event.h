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
    PointEvent() : m_point2d(point_2d()), m_eventType(EventType::StartPoint), m_otherEventSp(std::shared_ptr<PointEvent>()) {}

    PointEvent(const point_2d& point2d, const EventType eventType)
        : m_point2d(point2d), m_eventType(eventType), m_otherEventSp(std::shared_ptr<PointEvent>())
    {
    }

    PointEvent(const point_2d& point2d, const EventType eventType, const std::shared_ptr<PointEvent>& otherEventSP) // 传入指针
        : m_point2d(point2d), m_eventType(eventType), m_otherEventSp(otherEventSP)
    {
    }

    PointEvent(const point_2d& point2d, const EventType eventType, const PointEvent& otherEvent) // 传入对象
        : m_point2d(point2d), m_eventType(eventType), m_otherEventSp(std::make_shared<PointEvent>(otherEvent))
    {
    }

    PointEvent(const PointEvent& other) : m_point2d(other.m_point2d), m_eventType(other.m_eventType), m_otherEventSp(other.m_otherEventSp)
    {
        // 太舒服了，共享指针的逻辑比原始指针的逻辑好多了，浅拷贝就能达到深拷贝的效果
        // m_otherEventSP = std::make_shared<PointEvent>(other.m_otherEventSP->m_point2d, other.m_otherEventSP->m_eventType,
        //                                               other.m_otherEventSP->m_otherEventSP);
    }

    bool operator==(const PointEvent& other) const;
    bool operator<(const PointEvent& other) const;
    bool operator>(const PointEvent& other) const;

    inline point_2d                    getPoint() const { return m_point2d; }
    inline EventType                   getEventType() const { return m_eventType; }
    inline std::shared_ptr<PointEvent> getOtherEvent() const { return m_otherEventSp; }

    void setEventType(const EventType eventType) { m_eventType = eventType; }
    void setOtherEvent(const std::shared_ptr<PointEvent>& otherEvent) { m_otherEventSp = otherEvent; }

private:
    point_2d                    m_point2d;      // 该点
    EventType                   m_eventType;    // 点的类型
    std::shared_ptr<PointEvent> m_otherEventSp; // 另一个相连的点
};
