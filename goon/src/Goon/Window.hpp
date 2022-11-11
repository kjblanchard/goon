#pragma once

#include <functional>
#include <gnpch.hpp>
#include <Goon/Core.h>
#include <Goon/Events/Event.hpp>

namespace Goon {
    struct WindowProps
    {
        std::string Title;
        unsigned int Width;
        unsigned int Height;
        WindowProps(const std::string& title = "Goon Engine",
                unsigned int width = 1280,
                unsigned int height = 720)
            : Title(title), Width(width), Height(height) {}
    };

    /**
     * @brief Interface representing a Desktop window
     */
    class GN_API Window
    {
        public:
            using EventCallbackFn = std::function<void(Event&)>;
            virtual ~Window() {}
            virtual void OnUpdate() = 0;
            virtual unsigned int GetWidth() const = 0;
            virtual unsigned int GetHeight() const = 0;
            virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
            virtual void SetVSync(bool enabled) = 0;
            virtual bool IsVSync() const = 0;
            static Window* Create(const WindowProps& props = WindowProps());
    };
}
