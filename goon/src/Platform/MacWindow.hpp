#pragma once
#include "Goon/Window.hpp"
#include <GLFW/glfw3.h>

namespace Goon {
    class MacWindow : public Window
    {
        public:
            MacWindow(const WindowProps& props);
            virtual ~MacWindow();
            void OnUpdate() override;
            inline unsigned int GetWidth() const override { return m_Data.Width; }
            inline unsigned int GetHeight() const override { return m_Data.Height; }

            virtual void SetEventCallback(const EventCallbackFn& callback) override {m_Data.Event = callback;};
            virtual void SetVSync(bool enabled) override;
            virtual bool IsVSync() const override;
        private:
            virtual void Init(const WindowProps& props);
            virtual void Shutdown();
        private:
            GLFWwindow* m_window;

            struct WindowData
            {
                std::string Title;
                unsigned int Width, Height;
                bool VSync;
                EventCallbackFn Event;
            };
            WindowData m_Data;

    };
}
