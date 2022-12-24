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
#include <Goon/Renderer/Buffer.hpp>
#include <Goon/Renderer/VertexArray.hpp>
#include <Goon/Renderer/Shader.hpp>

namespace Goon

{
    class ImGuiLayer;
    /**
     * @brief The application that will be created.
     */
    class GN_API Application
    {
    public:
        Application();
        virtual ~Application();
        static Application &Get() { return *s_Application; }
        /**
         * @brief Called every tick, updates each layer.
         */
        void Run();
        Window &GetWindow() { return *m_Window; }
        void PushLayer(Layer *layer);
        void PushOverlay(Layer *overlay);

    private:
        std::unique_ptr<Window> m_Window;
        ImGuiLayer *m_ImGuiLayer;
        bool m_Running = true;
        void OnEvent(Event &e);
        bool OnWindowClosed(WindowCloseEvent &e);
        LayerStack m_LayerStack;
        static Application *s_Application;

    private:
        std::shared_ptr<Shader> m_Shader;
        std::shared_ptr<VertexArray> m_VertexArray;
        // std::shared_ptr<VertexBuffer> m_VertexBuffer;
        // std::shared_ptr<IndexBuffer> m_IndexBuffer;

        std::shared_ptr<VertexArray> m_SquareVertexArray;
    };

    // To be defined in the client, for the entrypoint
    Application *CreateApplication();
}
