#include "Application.hpp"
#include "Goon/Events/ApplicationEvent.hpp"
#include "Goon/Events/Event.hpp"
#include "Goon/Log.hpp"
#include "gnpch.hpp"


namespace Goon {

    void Application::Run()
    {
        while (m_Running)
        {
            m_Window->OnUpdate();
        }
    }

    Application::Application()
    {
        m_Window = std::unique_ptr<Window>(Window::Create());

    }

    Application::~Application()
    {

    }

}
