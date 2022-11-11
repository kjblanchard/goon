#pragma once
#include "Core.h"
#include "Window.hpp"

namespace Goon {
    class GN_API Application
    {
        public:
            Application();
            virtual ~Application();
            void Run();
        private:
            std::unique_ptr<Window> m_Window;
            bool m_Running = true;
    };

    //To be defined in the client, for the entrypoint
    Application* CreateApplication();
}
