#include <gnpch.hpp>
#include <glad/glad.h>
#include <Goon/Renderer/Renderer.hpp>

namespace Goon
{
        void Renderer::BeginScene()
        {
        }
        void Renderer::EndScene()
        {
        }
        void Renderer::Submit(const std::shared_ptr<VertexArray> &vertexArray)
        {
                vertexArray->Bind();
                RenderCommand::DrawIndexed(vertexArray);

        }

        void Renderer::ToggleWireframe()
        {
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
}