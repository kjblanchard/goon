#include "Goon/ImGui/ImGuiLayer.hpp"
#include "Goon/Layer.hpp"
#include <Goon.hpp>

class ExampleLayer : public Goon::Layer
{
    public:
        ExampleLayer()
            :Layer("Example")
        {}
        void OnUpdate() override
        {

        }
        void OnEvent(Goon::Event &event) override
        {
            GN_TRACE("{0}", event);

        }

};

class Sandbox : public Goon::Application
{
    public:
        Sandbox()
        {
            PushOverlay(new Goon::ImGuiLayer());

        }
        ~Sandbox()
        {

        }

};

Goon::Application* Goon::CreateApplication()
{
    return new Sandbox();
}
