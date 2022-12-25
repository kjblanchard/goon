#pragma once
#include <Goon/Renderer/RendererAPI.hpp>

namespace Goon
{

    class RenderCommand
    {
    public:
        inline virtual void SetClearColor(const glm::vec4 &color)
        {
            s_RendererAPI->SetClearColor(color);
        }
        inline virtual void Clear()
        {
            s_RendererAPI->Clear();
        }
        inline static void DrawIndexed(const std::shared_ptr<VertexArray> &vertexArray)
        {
            s_RendererAPI->DrawIndexed(vertexArray);
        }

    private:
        static RendererAPI *s_RendererAPI;
    };

}