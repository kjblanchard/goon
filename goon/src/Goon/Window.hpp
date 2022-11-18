/**
 * @file Window.hpp
 * @brief Defines what a window should be
 * @author Kevin Blanchard
 * @version 0.1.0
 * @date 2022-11-14
 */
#pragma once
#include <gnpch.hpp>
#include <Goon/Core.hpp>
#include <Goon/Events/Event.hpp>

namespace Goon {
    /**
     * @brief The Properties of a window needed to create one
     */
    struct WindowProps
    {
        /**
         * @brief Name of the window
         */
        std::string Title;
        /**
         * @brief WIdth of a window
         */
        unsigned int Width;
        /**
         * @brief Height of a window
         */
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
            /**
             * @brief A function taking in an event, so that we can handle them in the window.
             */
            using EventCallbackFn = std::function<void(Event&)>;
            virtual ~Window() {}
            /**
             * @brief Update function for the window
             */
            virtual void OnUpdate() = 0;
            /**
             * @brief Width of the window
             *
             * @return Width of the window
             */
            virtual unsigned int GetWidth() const = 0;
            /**
             * @brief Height of the window
             *
             * @return The height of the window
             */
            virtual unsigned int GetHeight() const = 0;
            /**
             * @brief Sets the window callback function
             *
             * @param callback The callback function to bind
             */
            virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
            /**
             * @brief Sets the windows vsync
             *
             * @param enabled Should vsync be enabled
             */
            virtual void SetVSync(bool enabled) = 0;
            /**
             * @brief Is Vsync enabled on the window
             *
             * @return True if vsync is enabled.
             */
            virtual bool IsVSync() const = 0;
            /**
             * @brief Creates a window.
             *
             * @param props THe window props to create the window with
             *
             * @return The Created window.
             */
            static Window* Create(const WindowProps& props = WindowProps());

            inline float GetDpi() { return m_DpiScale; }
            template <typename T>
                inline T* GetWindow() { return (T*)this; }


        protected:
            float m_DpiScale;
    };
}
