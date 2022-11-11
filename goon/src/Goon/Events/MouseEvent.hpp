#pragma once
#include "Goon/Core.h"
#include "Goon/Events/Event.hpp"

namespace Goon {
    class GN_API MouseMovedEvent : public Event
    {
        public:
            MouseMovedEvent(float x, float y)
                :m_MouseX(x), m_MouseY(y) {}
            inline float GetX() { return m_MouseX; }
            inline float GetY() { return m_MouseY; }
            std::string ToString() const override
            {
                std::stringstream ss;
                ss << "Mouse moved event: " << m_MouseX << ',' << m_MouseY;
                return ss.str();
            }
            EVENT_CLASS_TYPE(MouseMoved)
            EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
        private:
            float m_MouseX, m_MouseY;

    };

    class GN_API MouseScrolledEvent : public Event
    {
        public:
            MouseScrolledEvent(float xOffset, float yOffset)
                :m_XOffset(xOffset), m_YOffset(yOffset) {}
            inline float GetXOffset() { return m_XOffset; }
            inline float GetYOffset() { return m_YOffset; }
            std::string ToString() const override
            {
                std::stringstream ss;
                ss << "Mouse scrilled event: " << m_XOffset << ',' << m_YOffset;
                return ss.str();
            }
            EVENT_CLASS_TYPE(MouseScrolledEvent)
            EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
        private:
            float m_XOffset, m_YOffset;
    };

    class GN_API MouseButtonEvent : public Event
    {
        public:
            inline int GetMouseButton() { return m_Button; }
            EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
        protected:
                MouseButtonEvent(int button)
                    :m_Button(button) {}
                int m_Button;
    };
    class GN_API MouseButtonPressedEvent : public MouseButtonEvent
    {
        public:
            MouseButtonPressedEvent(int button)
                :MouseButtonEvent(button) {}
            std::string ToString() const override
            {
                std::stringstream ss;
                ss << "MouseButtonPressedEvent: " << m_Button;
                return ss.str();
            }
            EVENT_CLASS_TYPE(MouseButtonPressed)
    };

    class GN_API MouseButtonReleasedEvent : public MouseButtonEvent
    {
        public:
            MouseButtonReleasedEvent(int button)
                :MouseButtonEvent(button) {}
            std::string ToString() const override
            {
                std::stringstream ss;
                ss << "MouseButtonReleasedEvent: " << m_Button;
                return ss.str();
            }
            EVENT_CLASS_TYPE(MouseButtonPressed)
    };
}
