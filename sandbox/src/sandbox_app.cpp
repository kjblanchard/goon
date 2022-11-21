#include "Goon/Input.hpp"
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
        void OnEvent(Goon::Event&) override
        {

        }

};

class Sandbox : public Goon::Application
{
    public:
        Sandbox()
        {

        }
        ~Sandbox()
        {

        }

};

Goon::Application* Goon::CreateApplication()
{
    return new Sandbox();
}
