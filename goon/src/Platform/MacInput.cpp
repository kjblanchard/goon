#include <gnpch.hpp>
#include <GLFW/glfw3.h>
#include <Goon/Application.hpp>
#include <Platform/MacWindow.hpp>
#include <Platform/MacInput.hpp>

namespace Goon {

    Input* Input::s_Instance = new MacInput();

    bool MacInput::IsKeyPressedImpl(int keycode) const
    {
        auto& window = Application::Get().GetWindow().GetNativeWindow<MacWindow>();
        auto keyState = glfwGetKey(window.GetGlfwWindow(), keycode);
        return keyState == GLFW_PRESS || keyState == GLFW_REPEAT;
    }

    bool MacInput::IsMouseButtonPressedImpl(int button) const
    {
        auto& window = Application::Get().GetWindow().GetNativeWindow<MacWindow>();
        auto buttonState = glfwGetMouseButton(window.GetGlfwWindow(), button);
        return buttonState == GLFW_PRESS || buttonState == GLFW_REPEAT;

    }

    float MacInput::GetMousePositionXImpl() const
    {
        auto& window = Application::Get().GetWindow().GetNativeWindow<MacWindow>();
        double xpos, ypos;
        glfwGetCursorPos(window.GetGlfwWindow(), &xpos, &ypos);
        return xpos;
    }

    float MacInput::GetMousePositionYImpl() const
    {
        auto& window = Application::Get().GetWindow().GetNativeWindow<MacWindow>();
        double xpos, ypos;
        glfwGetCursorPos(window.GetGlfwWindow(), &xpos, &ypos);
        return xpos;
    }
}
