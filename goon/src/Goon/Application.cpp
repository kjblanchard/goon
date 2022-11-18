#include <gnpch.hpp>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <Goon/Application.hpp>
#include <Goon/Log.hpp>


namespace Goon {

    Application* Application::s_Application = nullptr;

    Application::Application()
    {
        GN_CORE_ASSERT(!s_Application, "Application is already created");
        s_Application = this;
        m_Window = std::unique_ptr<Window>(Window::Create());

    }

    Application::~Application()
    {

    }

    void Application::Run()
    {
        while (m_Running)
        {
            glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
            for(Layer* layer: m_LayerStack)
                layer->OnUpdate();
            m_Window->OnUpdate();

            //This binds the onEvent callback on every event in the window.
            m_Window->SetEventCallback(GN_BIND_EVENT_FN(&Application::OnEvent));
        }
    }

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(GN_BIND_EVENT_FN(&Application::OnWindowClosed));
        //GN_CORE_TRACE("{0}",e);
        for(auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
        {
            (*--it)->OnEvent(e);
            if(e.Handled)
                break;
        }
    }

    void Application::PushLayer(Layer* layer)
    {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }
    void Application::PushOverlay(Layer* overlay)
    {
        m_LayerStack.PushOverlay(overlay);
        overlay->OnAttach();
    }

    bool Application::OnWindowClosed(WindowCloseEvent& e)
    {
        m_Running = false;
        return true;
    }
}
