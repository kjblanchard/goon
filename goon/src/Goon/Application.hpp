#pragma once
#include <Goon/Events/Event.hpp>
#include <Goon/Events/ApplicationEvent.hpp>
#include <Goon/LayerStack.hpp>
#include <Goon/Window.hpp>

namespace Goon {
    class GN_API Application
    {
        public:
            Application();
            virtual ~Application();
            void Run();
            void PushLayer(Layer* layer);
            void PushOverlay(Layer* overlay);
        private:
            std::unique_ptr<Window> m_Window;
            bool m_Running = true;
            void OnEvent(Event& e);
            bool OnWindowClosed(WindowCloseEvent& e);
            LayerStack m_LayerStack;
    };

    //To be defined in the client, for the entrypoint
    Application* CreateApplication();
}
