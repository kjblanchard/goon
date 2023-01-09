/**
 * @file MacInput.hpp
 * @brief Implements the input functions on mac.  Currently using glfw as windowing / input for mac.
 * @author Kevin Blanchard
 * @version v0.1.0
 * @date 2022-11-19
 */
#pragma once
#include <Goon/Core.hpp>
#include <Goon/Input.hpp>

namespace Goon {
    /**
     * @brief The input implementation for Mac, using glfw
     */
    class GN_API LinuxInput : public Input
    {
        public:
            virtual bool IsKeyPressedImpl(int keycode) const override;
            virtual bool IsMouseButtonPressedImpl(int button) const override;
            virtual float GetMousePositionXImpl() const override;
            virtual float GetMousePositionYImpl() const override;
    };
}
