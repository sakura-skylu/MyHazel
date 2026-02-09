#pragma once

#include "Event.h"

namespace Engine {

class EventDispatcher {
public:
    explicit EventDispatcher(Event& event)
        : m_Event(event) {}

    template <typename T, typename F>
    bool Dispatch(const F& func) {
        if (m_Event.GetEventType() == T::GetStaticType()) {
            m_Event.Handled |= func(static_cast<T&>(m_Event));
            return true;
        }
        return false;
    }

private:
    Event& m_Event;
};

} // namespace Engine
