#pragma once
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
        float m_time;

    };
}
