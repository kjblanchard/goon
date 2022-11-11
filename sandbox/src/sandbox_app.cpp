#include <Goon.hpp>

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
