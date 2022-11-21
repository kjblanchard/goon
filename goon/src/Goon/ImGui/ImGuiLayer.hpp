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
        virtual void OnImGuiRender() override;
        void Begin();
        void End();

      private:
        //float m_time = 0.0f;

    };
}
