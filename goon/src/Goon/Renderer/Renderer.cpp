#include <gnpch.hpp>
#include <glad/glad.h>
#include <Goon/Renderer/Renderer.hpp>

namespace Goon
{

        RendererAPI Renderer::s_RendererAPI = RendererAPI::OpenGL;

        void Renderer::ToggleWireframe()
        {
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
}