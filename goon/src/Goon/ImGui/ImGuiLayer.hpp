#pragma once
#include "Goon/Events/KeyEvent.hpp"
#include "Goon/Events/MouseEvent.hpp"
#include <Goon/Layer.hpp>

namespace Goon {

    class ImGuiLayer : public Layer
    {
      public:
        ImGuiLayer();
        ~ImGuiLayer();
        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnUpdate() override;
        virtual void OnEvent(Event&) override;

      private:
        bool OnMouseMove(MouseMovedEvent &e);
        bool OnMouseButtonPressed(MouseButtonPressedEvent &e);
        bool OnMouseButtonReleased(MouseButtonReleasedEvent &e);
        bool OnMouseScrolled(MouseScrolledEvent &e);
        bool OnKeyPressed(KeyPressedEvent &e);
        bool OnKeyReleased(KeyReleasedEvent &e);
        bool OnKeyTyped(KeyTypedEvent &e);

      private:
        float m_time;

    };
}
