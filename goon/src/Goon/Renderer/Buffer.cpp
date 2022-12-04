#include <gnpch.hpp>
#include <Goon/Renderer/Renderer.hpp>
#include <Goon/Renderer/Buffer.hpp>
#include <Goon/Core.hpp>

namespace Goon
{
    VertexBuffer *VertexBuffer::Create(float* vertices, uint32_t size)
    {
        auto rendererType = Renderer::GetAPI();
        GN_CORE_ASSERT(rendererType != RendererAPI::None, "Cannot create API with no backend.");
        if (rendererType == RendererAPI::OpenGL)
        {
        }
        else
        {
            GN_CORE_ASSERT(true, "The backend type is not currently implemented.");
        }
    }

}