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
            GN_INFO("Example Layer Update");

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
            PushLayer(new ExampleLayer());

        }
        ~Sandbox()
        {

        }

};

Goon::Application* Goon::CreateApplication()
{
    return new Sandbox();
}
