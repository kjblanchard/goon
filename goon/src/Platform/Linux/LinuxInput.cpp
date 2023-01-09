#include <gnpch.hpp>
#include <GLFW/glfw3.h>
#include <Goon/Application.hpp>
#include <Platform/Linux/LinuxWindow.hpp>
#include <Platform/Linux/LinuxInput.hpp>

namespace Goon {

    Input* Input::s_Instance = new LinuxInput();

    bool LinuxInput::IsKeyPressedImpl(int keycode) const
    {
        auto& window = Application::Get().GetWindow().GetNativeWindow<LinuxWindow>();
        auto keyState = glfwGetKey(window.GetGlfwWindow(), keycode);
        return keyState == GLFW_PRESS || keyState == GLFW_REPEAT;
    }

    bool LinuxInput::IsMouseButtonPressedImpl(int button) const
    {
        auto& window = Application::Get().GetWindow().GetNativeWindow<LinuxWindow>();
        auto buttonState = glfwGetMouseButton(window.GetGlfwWindow(), button);
        return buttonState == GLFW_PRESS || buttonState == GLFW_REPEAT;

    }

    float LinuxInput::GetMousePositionXImpl() const
    {
        auto& window = Application::Get().GetWindow().GetNativeWindow<LinuxWindow>();
        double xpos, ypos;
        glfwGetCursorPos(window.GetGlfwWindow(), &xpos, &ypos);
        return xpos;
    }

    float LinuxInput::GetMousePositionYImpl() const
    {
        auto& window = Application::Get().GetWindow().GetNativeWindow<LinuxWindow>();
        double xpos, ypos;
        glfwGetCursorPos(window.GetGlfwWindow(), &xpos, &ypos);
        return xpos;
    }
}
