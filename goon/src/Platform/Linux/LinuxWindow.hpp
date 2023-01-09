/**
 * @file MacWindow.hpp
 * @brief Handles creating a window on MacOS
 * @author Kevin Blanchard
 * @version 0.1.0
 * @date 2022-11-14
 */
#pragma once
#include <Goon/Core.hpp>
#include <Goon/Window.hpp>
#include <Platform/OpenGL/OpenGLContext.hpp>

namespace Goon {
    /**
     * @brief A window used on MacOS
     */
    class GN_API LinuxWindow : public Window
    {
        public:
            /**
             * @brief A window used on MacOS
             *
             * @param props The properties of the window
             */
            LinuxWindow(const WindowProps& props);
            virtual ~LinuxWindow();
            void OnUpdate() override;
            inline unsigned int GetWidth() const override { return m_Data.Width; }
            inline unsigned int GetHeight() const override { return m_Data.Height; }
            inline std::pair<unsigned int, unsigned int> GetWindowSize() override { return { m_Data.Width, m_Data.Height }; }
            virtual void SetEventCallback(const EventCallbackFn& callback) override {m_Data.Event = callback;}
            virtual void SetVSync(bool enabled) override;
            virtual bool IsVSync() const override;
            virtual std::pair<float, float> GetWindowContentScaling() const override;
            virtual std::pair<int, int> GetWindowFrameBufferSize() const override;
            inline GLFWwindow* GetGlfwWindow() { return m_window; }
        private:
            /**
             * @brief Initializes the window, called from the constructor
             *
             * @param props The properties of the window.
             */
            virtual void Init(const WindowProps& props);
            /**
             * @brief Handles closing the window, called in the dtor
             */
            virtual void Shutdown();
        private:
            /**
             * @brief Pointer to the underlying GLFW window
             */
            GLFWwindow* m_window;

            OpenGLContext* m_Context;
            /**
             * @brief Used in macos to scale properly.
             */

            /**
             * @brief The WIndowdata that is stored inside of GLFW for referencing.
             */
            struct WindowData
            {
                std::string Title;
                unsigned int Width, Height;
                bool VSync;
                EventCallbackFn Event;
            };
            /**
             * @brief The widows data.
             */
            WindowData m_Data;

    };
}
