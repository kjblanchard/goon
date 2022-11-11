#pragma once
#include "Core.h"

namespace Goon {
    class GN_API Application
    {
        public:
            Application();
            virtual ~Application();
            void Run();
    };

    //To be defined in the client, for the entrypoint
    Application* CreateApplication();
}
