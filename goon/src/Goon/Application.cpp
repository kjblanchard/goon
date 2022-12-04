#include <gnpch.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Goon/Application.hpp>
#include <Goon/Log.hpp>
#include <Goon/Renderer/Renderer.hpp>
#include <Goon/ImGui/ImGuiLayer.hpp>
#include <Goon/Renderer/Shader.hpp>
#include <Goon/Renderer/Buffer.hpp>

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
        glGenVertexArrays(1, &m_VertexArray);
        glBindVertexArray(m_VertexArray);

        float vertices[] = {
            0.5f, 0.5f, 0.0f,   // top right
            0.5f, -0.5f, 0.0f,  // bottom right
            -0.5f, -0.5f, 0.0f, // bottom left
            -0.5f, 0.5f, 0.0f   // top left
        };
        // Vertex buffer
        VertexBuffer::Create(vertices, sizeof(vertices));

        // Vertex shader
        const char *vertexShaderSource = "#version 330 core\n"
                                         "layout (location = 0) in vec3 aPos; out vec3 color;\n"
                                         "void main()\n"
                                         "{\n"
                                         "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                         "color = vec3(1.0,0.25,1.0);"
                                         "}\0";
        // Fragment shader
        const char *fragmentShaderSource = "#version 330 core\n"
                                           "out vec4 FragColor;\n"
                                           "in vec3 color;\n"
                                           "void main()\n"
                                           "{\n"
                                           "FragColor = vec4(color, 1.0f);\n"
                                           "}\n";

        auto shader = Shader::Create(vertexShaderSource, fragmentShaderSource);

        // this is 0 as we set the location = 0 in the vertex shader above.
        glEnableVertexAttribArray(0);
        // We need to tell opengl what this vertices actually looks like.
        // on index 0, we are using 3 each, there is 3 * float for each vertice (we are saying one), then since it is the initial vertice,
        // it beins at byte 0 (it is the only one)
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

        // Index buffer (element buffer)
        // This tells you the "order" to draw this with the indices
        glGenBuffers(1, &m_IndexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
        unsigned int indices[] = {0, 2, 3, 1, 2, 3};
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
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

            glBindVertexArray(m_VertexArray);
            // Since we are drawing with index/element buffers, we use draw elements. Lets draw 2 triangles.
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
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
