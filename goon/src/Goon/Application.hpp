/**
 * @file Application.hpp
 * @brief The actual application that we are going to create
 * @author Kevin Blanchard
 * @version 0.1.0
 * @date 2022-11-14
 */
#pragma once
#include <Goon/Events/Event.hpp>
#include <Goon/Events/ApplicationEvent.hpp>
#include <Goon/LayerStack.hpp>
#include <Goon/Window.hpp>

namespace Goon {
    class ImGuiLayer;
    /**
     * @brief The application that will be created.
     */
    class GN_API Application
    {
        public:
            Application();
            virtual ~Application();
            static Application& Get() { return *s_Application; }
            /**
             * @brief Called every tick, updates each layer.
             */
            void Run();
            Window& GetWindow() { return *m_Window; }
            void PushLayer(Layer* layer);
            void PushOverlay(Layer* overlay);
        private:
            std::unique_ptr<Window> m_Window;
            ImGuiLayer* m_ImGuiLayer;
            bool m_Running = true;
            void OnEvent(Event& e);
            bool OnWindowClosed(WindowCloseEvent& e);
            LayerStack m_LayerStack;
            static Application* s_Application;
    };

    //To be defined in the client, for the entrypoint
    Application* CreateApplication();
}
