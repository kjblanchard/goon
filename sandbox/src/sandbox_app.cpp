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

        }

};

class Sandbox : public Goon::Application
{
    public:
        Sandbox()
        {
            //PushOverlay(new ExampleLayer());
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
