/**
 * @file Input.hpp
 * @brief The abstract, static Input class.  This class needs to be implemented per platform, but also gives some base functions
 * so that we can poll and get current status of our input devices.
 * Use MacInput / WindowsInput to actually implement this.
 * @author Kevin Blanchard
 * @version v0.1.0
 * @date 2022-11-19
 */
#pragma once
#include <gnpch.hpp>
#include <Goon/Core.hpp>

namespace Goon {

    /**
     * @brief The abstract, static Input class. This is basically an interface for input, but also a singleton.  This class needs to be implemented per platform, but also gives some base functions
     * so that we can poll and get current status of our input devices.
     * Use MacInput / WindowsInput to actually implement this.
     */
    class GN_API Input
    {
        public:
            /**
             * @brief Checks if the key is currently pressed down
             *
             * @param keycode The Keycode to check for, should be a GoonKey
             *
             * @return true if the key is down.
             */
            bool IsKeyPressed(int keycode) const { return IsKeyPressedImpl(keycode); }
            /**
             * @brief Checks if the mouse button is currently pressed
             *
             * @param button The button to check for
             *
             * @return true if the key is down
             */
            bool IsMouseButtonPressed(int button) const { return IsMouseButtonPressedImpl(button); }
            /**
             * @brief Gets the current mouse position
             *
             * @return Pair of floats, x/y
             */
            std::pair<float, float> GetMousePosition() const { return { GetMousePositionXImpl(), GetMousePositionYImpl()}; }
            /**
             * @brief Gets the current x position of the mouse
             *
             * @return current mouse position
             */
            float GetMousePositionX() const { return GetMousePositionXImpl(); }
            /**
             * @brief Gets the current y position of the mouse
             *
             * @return  current y position
             */
            float GetMousePositionY() { return GetMousePositionYImpl(); }
            static Input& Get() { return *s_Instance; }

        protected:
            virtual bool IsKeyPressedImpl(int keycode) const = 0;
            virtual bool IsMouseButtonPressedImpl(int button) const = 0;
            virtual float GetMousePositionXImpl() const = 0;
            virtual float GetMousePositionYImpl() const  = 0;
            static Input* s_Instance;


    };
}
