#include <gnpch.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Platform/OpenGL/OpenGLContext.hpp>
#include <Goon/Core.hpp>
#include <Goon/Log.hpp>


namespace Goon {

    OpenGLContext::OpenGLContext(GLFWwindow *window)
    : GraphicsContext(), m_window(window)
    {

    }

    void OpenGLContext::Init()
    {
        glfwMakeContextCurrent(m_window);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        GN_CORE_ASSERT(status, "Failed to initialize glad");
        auto vendor = (char*)glGetString(GL_VENDOR);
        auto renderer = (char*)glGetString(GL_RENDERER);
        auto version = (char*)glGetString(GL_VERSION);
        GN_CORE_INFO("Vendor {0}/ Renderer: {1}, version {2}", vendor, renderer, version);
    }

    void OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(m_window);
    }
}