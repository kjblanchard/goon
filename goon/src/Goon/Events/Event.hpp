#pragma once
#include "Goon/Log.hpp"
#include <Goon/Core.hpp>
#include <ostream>

namespace Goon {
    //TODO We should make events non-blocking, as right now we deal with each one as they come up.
    enum class EventType
    {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        AppTick, AppUpdate, AppRender,
        KeyPressed, KeyReleased, KeyTyped,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };

    enum EventCategory
    {
        None = 0,
        EventCategoryApplication = BIT(0),
        EventCategoryInput = BIT(1),
        EventCategoryKeyboard = BIT(2),
        EventCategoryMouse = BIT(3),
        EventCategoryMouseButton = BIT(4),
    };

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }
#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

    class GN_API Event
    {
        friend class EventDispatcher;

    public:
        virtual ~Event() {}
        virtual EventType GetEventType() const = 0;
        virtual const char* GetName() const = 0;
        virtual int GetCategoryFlags() const = 0;
        virtual std::string ToString() const { return GetName(); }
        bool Handled = false;
        /**
         * @brief Checks to see if an event is in the category.  Uses bitwise and to check since we use bits for it.
         *
         * @param category The category to match with
         *
         * @return true if is in the category, else false
         */
        inline bool IsInCategory(EventCategory category)
        {
            return GetCategoryFlags() &category;
        }

    };

    class GN_API EventDispatcher
    {
        template<typename T>
            using EventFn = std::function<bool(T&)>;
        public:
        EventDispatcher(Event& event)
            :m_Event(event) {}

        template<typename T>
            bool Dispatch(EventFn<T> func)
            {
                if(m_Event.GetEventType() == T::GetStaticType())
                {
                    m_Event.Handled = func(*(T*)&m_Event);
                    return true;
                }
                return false;
            }


        private:
            Event& m_Event;
    };

    inline std::ostream& operator<< (std::ostream& os, const Event& e)
    {
        return os << e.ToString();
    }

}
