#include <gnpch.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Goon/Application.hpp>
#include <Goon/Log.hpp>
#include <Goon/Renderer/Renderer.hpp>
#include <Goon/ImGui/ImGuiLayer.hpp>
#include <Goon/Renderer/Shader.hpp>

namespace Goon
{

    Application *Application::s_Application = nullptr;

    Application::Application()
    {
        GN_CORE_ASSERT(!s_Application, "Application is already created");
        s_Application = this;
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);
        // This binds the onEvent callback on every event in the window.
        m_Window->SetEventCallback(GN_BIND_EVENT_FN(&Application::OnEvent));

        // Vertex array
        uint32_t num = 0;
        glGenVertexArrays(1, &num);
        // glBindVertexArray(m_VertexArray);
        m_VertexArray.reset(VertexArray::Create());

        // Basic triangle
        float vertices[] = {
            0.5f, 0.5f, 0.0f, 1.0f, 1, 1.0f, 1.0f,
            0.5f, -0.5f, 0.0f, 1.0f, 0, 1.0f, 1.0f,
            -0.5f, -0.5f, 0.0f, 1.0f, 0, 1.0f, 1.0,
            -0.5f, 0.5f, 0.0f, 1.0f, 0, 1.0f, 1.0f};
        std::shared_ptr<VertexBuffer> vertexBuffer;
        vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
        m_Shader.reset(Shader::Create("basic.glsl"));

        BufferLayout layout = {
            {ShaderDataType::Float3, "a_Position"},
            {ShaderDataType::Float4, "a_Color"},
        };
        vertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(vertexBuffer);

        unsigned int indices[] = {0, 2, 3, 1, 2, 3};
        std::shared_ptr<IndexBuffer> indexBuffer;
        indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices)));
        m_VertexArray->SetIndexBuffer(indexBuffer);

        m_SquareVertexArray.reset(VertexArray::Create());
        float squareVertices[] = {
            -0.75f, -0.75f, 0.0f, 0.0f, 1, 1.0f, 1.0f,
            0.75f, -0.75f, 0.0f, 0.0f, 0, 1.0f, 1.0f,
            0.75f, 0.75f, 0.0f, 0.0f, 0, 1.0f, 1.0,
            -0.75f, 0.75f, 0.0f, 0.0f, 0, 1.0f, 1.0f};
        std::shared_ptr<VertexBuffer> squareVBO;
        squareVBO.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
        BufferLayout squareLayout = {
            {ShaderDataType::Float3, "a_Position"},
            {ShaderDataType::Float4, "a_Color"},
        };
        squareVBO->SetLayout(squareLayout);
        m_SquareVertexArray->AddVertexBuffer(squareVBO);
        unsigned int squareIndices[] = {0, 1, 2, 2, 3, 0};
        std::shared_ptr<IndexBuffer> squareIndexBuffer;
        squareIndexBuffer.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices)));
        m_SquareVertexArray->SetIndexBuffer(squareIndexBuffer);
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {
        while (m_Running)
        {
            glClearColor(0.1, 0.1, 0.1, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            m_Shader->Bind();

            m_SquareVertexArray->Bind();
            glDrawElements(GL_TRIANGLES, m_SquareVertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
            m_VertexArray->Bind();
            // Since we are drawing with index/element buffers, we use draw elements. Lets draw 2 triangles.
            glDrawElements(GL_TRIANGLES, m_VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
            for (Layer *layer : m_LayerStack)
                layer->OnUpdate();
            m_ImGuiLayer->Begin();
            for (Layer *layer : m_LayerStack)
                layer->OnImGuiRender();
            m_ImGuiLayer->End();
            m_Window->OnUpdate();
        }
    }

    void Application::OnEvent(Event &e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(GN_BIND_EVENT_FN(&Application::OnWindowClosed));
        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
        {
            (*--it)->OnEvent(e);
            if (e.Handled)
                break;
        }
    }

    void Application::PushLayer(Layer *layer)
    {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }
    void Application::PushOverlay(Layer *overlay)
    {
        m_LayerStack.PushOverlay(overlay);
        overlay->OnAttach();
    }

    bool Application::OnWindowClosed(WindowCloseEvent &)
    {
        m_Running = false;
        return true;
    }
}
