#include "Application.hpp"
#include "Goon/Events/ApplicationEvent.hpp"
#include "Goon/Events/Event.hpp"
#include "Goon/Log.hpp"
#include "gnpch.hpp"


namespace Goon {

    void Application::Run()
    {
        WindowResizeEvent e(1234, 1234);
        if(EventType::WindowResize == e.GetEventType())
            GN_TRACE("Its the thing!");
        if(e.IsInCategory(EventCategoryApplication))
            GN_TRACE("ITS THE CATEGORY!!!");
        GN_TRACE(e);
        while (true)
        {}
    }

    Application::Application()
    {

    }

    Application::~Application()
    {

    }

}
