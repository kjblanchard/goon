#pragma once
#include <Goon/Renderer/GraphicsContext.hpp>

struct GLFWwindow;

namespace Goon {
    class OpenGLContext : public GraphicsContext
    {
        public:
            OpenGLContext(GLFWwindow *window);
            virtual void Init() override;
            virtual void SwapBuffers() override;

        private:
            GLFWwindow *m_window;
    };
}