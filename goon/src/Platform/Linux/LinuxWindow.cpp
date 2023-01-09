#ifdef GN_PLATFORM_LINUX
#include <gnpch.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Goon/Events/ApplicationEvent.hpp>
#include <Goon/Events/KeyEvent.hpp>
#include <Goon/Events/MouseEvent.hpp>
#include <Goon/Log.hpp>

// TODO Use windows window hpp file.
#include <Platform/Linux/LinuxWindow.hpp>


namespace Goon {
    /**
     * @brief If GLFW initialized already
     */
    static bool s_GLFWInitialized = false;
    /**
     * @brief The callback that is called when GLFW encounters an error.
     *
     * @param error The error number
     * @param description The description of the error
     */
    static void GLFWErrorCallback(int error, const char* description)
    {
        GN_CORE_ERROR("GLFW Error {0}: {1}",error, description );
    }

    std::pair<float, float> MacWindow::GetWindowContentScaling() const
    {
        float scalex, scaley;
        glfwGetWindowContentScale(m_window, &scalex, &scaley);
        return { scalex, scaley };
    }

    std::pair<int, int> MacWindow::GetWindowFrameBufferSize() const
    {
        int display_w, display_h;
        glfwGetFramebufferSize(m_window, &display_w, &display_h);
        return { display_w, display_h };
    }


    //If this file is included, it defines the Window create function so that when a window create is called, a macwindow is created.
    Window* Window::Create(const WindowProps& props)
    {

        return new MacWindow(props);
    }

    MacWindow::MacWindow(const WindowProps& props)
    {
        Init(props);
    }

    MacWindow::~MacWindow()
    {
        Shutdown();

    }

    void MacWindow::Init(const WindowProps& props)
    {
        m_Data.Title = props.Title;
        m_Data.Width = props.Width;
        m_Data.Height = props.Height;
        GN_CORE_INFO("Creating window {0} ({1} {2})", props.Title, props.Width, props.Height);
        if(!s_GLFWInitialized)
        {
            int success = glfwInit();
            GN_CORE_ASSERT(success, "Could not initialize GLFW!");
            glfwSetErrorCallback(GLFWErrorCallback);
            s_GLFWInitialized = true;
        }
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        m_window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
        //m_DpiScale = GetWindowDpiScaling();
        glfwMakeContextCurrent(m_window);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        GN_CORE_ASSERT(status, "Failed to initialize glad");
        glfwSetWindowUserPointer(m_window, &m_Data);
        SetVSync(true);

        //Callbacks
        glfwSetCharCallback(m_window, [](GLFWwindow* window, unsigned int code)
                {
                    WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
                    auto event = KeyTypedEvent(code);
                    data.Event(event);

                });
        glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height)
                {
                    WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
                    data.Width = width;
                    data.Height = height;
                    WindowResizeEvent event(width, height);
                    data.Event(event);
                });
        glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window)
                {
                    WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
                    WindowCloseEvent event;
                    data.Event(event);
                });
        glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int, int action, int)
                {
                    WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
                    switch(action)
                    {
                        case GLFW_PRESS:
                        {
                        KeyPressedEvent event(key, 0);
                        data.Event(event);
                        break;

                        }
                        case GLFW_RELEASE:
                        {
                        KeyReleasedEvent event(key);
                        data.Event(event);
                        break;

                        }
                        case GLFW_REPEAT:
                        {
                            KeyPressedEvent event(key, 1);
                            data.Event(event);
                            break;
                        }
                    }
                });
        glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int)
                {
                WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
                switch(action)
                {
                case GLFW_PRESS:
                {
                MouseButtonPressedEvent event(button);
                data.Event(event);
                break;

                }
                case GLFW_RELEASE:
                {
                MouseButtonReleasedEvent event(button);
                data.Event(event);
                break;
                }
                }
                });

        glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xoffset, double yoffset)
                {
                WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
                MouseScrolledEvent event((float)xoffset, (float)yoffset);
                data.Event(event);

                });
        glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xpos, double ypos)
                {
                WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
                MouseMovedEvent event((float)xpos, (float)ypos);
                data.Event(event);

                });

    }

    void MacWindow::Shutdown()
    {
        glfwDestroyWindow(m_window);
    }

    void MacWindow::OnUpdate()
    {
        glfwPollEvents();
        glfwSwapBuffers(m_window);
    }

    void MacWindow::SetVSync(bool enabled)
    {
        if(enabled)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);
        m_Data.VSync = enabled;
    }
    bool MacWindow::IsVSync() const
    {
        return m_Data.VSync;
    }

}
#endif