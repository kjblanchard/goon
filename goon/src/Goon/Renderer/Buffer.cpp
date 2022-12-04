#include <gnpch.hpp>
#include <Goon/Renderer/Renderer.hpp>
#include <Goon/Renderer/Buffer.hpp>
#include <Goon/Core.hpp>
#include <Platform/OpenGL/OpenGLBuffer.hpp>

namespace Goon
{
    VertexBuffer *VertexBuffer::Create(float *vertices, uint32_t size)
    {
        auto rendererType = Renderer::GetAPI();
        GN_CORE_ASSERT(rendererType != RendererAPI::None, "Cannot create API with no backend.");
        if (rendererType == RendererAPI::OpenGL)
        {
            return new OpenGLVertexBuffer(vertices, size);
        }
        else
        {
            GN_CORE_ASSERT(true, "The backend type is not currently implemented.");
        }
    }

    IndexBuffer *IndexBuffer::Create(uint32_t *indices, uint32_t size)
    {
        auto rendererType = Renderer::GetAPI();
        GN_CORE_ASSERT(rendererType != RendererAPI::None, "Cannot create API with no backend.");
        if (rendererType == RendererAPI::OpenGL)
        {
            return new OpenGLIndexBuffer(indices, size);
        }
        else
        {
            GN_CORE_ASSERT(true, "The backend type is not currently implemented.");
        }
    }

}