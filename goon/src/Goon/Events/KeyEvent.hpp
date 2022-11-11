#pragma once

#include "Event.hpp"
#include <sstream>

namespace Goon {
    class GN_API KeyEvent : public Event
    {
        public:
            inline int GetKeyCode() const { return m_KeyCode; }
            EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

        protected:
            KeyEvent(int keycode)
                : m_KeyCode(keycode) {}
            int m_KeyCode;
    };

    class GN_API KeyPressedEvent : public KeyEvent
    {
        public:
            KeyPressedEvent(int keycode, int repeatCount)
                :KeyEvent(keycode), m_RepeatCount(repeatCount) {}
            inline int GetRepeatCount(  ) const { return m_RepeatCount; }
            std::string ToString() const override
            {
                std::stringstream ss;
                ss << "Key pressed event: " << m_KeyCode << " (  " << m_RepeatCount << " repeats)";
                return ss.str();
            }

            EVENT_CLASS_TYPE(KeyPressed)
        private:
            int m_RepeatCount;

    };

    class GN_API KeyReleasedEvent : public KeyEvent
    {
        public:
            KeyReleasedEvent(int keycode)
                :KeyEvent(keycode) {}
        EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "Key released event: " << m_KeyCode;
            return ss.str();
        }
        EVENT_CLASS_TYPE(KeyReleased);
    };
    
}
