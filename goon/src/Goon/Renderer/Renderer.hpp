#pragma once
#include <Goon/Renderer/RenderCommand.hpp>

namespace Goon
{

    class Renderer
    {
    public:
        static void BeginScene();
        static void EndScene();
        static void Submit(const std::shared_ptr<VertexArray>& vertexArray);
        static void ToggleWireframe();
        inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
    };

}