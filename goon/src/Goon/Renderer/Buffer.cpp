#include <gnpch.hpp>
#include <Goon/Renderer/RendererAPI.hpp>
#include <Goon/Renderer/Buffer.hpp>
#include <Goon/Core.hpp>
#include <Platform/OpenGL/OpenGLBuffer.hpp>

namespace Goon
{
    VertexBuffer *VertexBuffer::Create(float *vertices, uint32_t size)
    {
        auto rendererType = RendererAPI::GetAPI();
        GN_CORE_ASSERT(rendererType != RendererAPI::API::None, "Cannot create API with no backend.");
        if (rendererType == RendererAPI::API::OpenGL)
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
        auto rendererType = RendererAPI::GetAPI();
        GN_CORE_ASSERT(rendererType != RendererAPI::API::None, "Cannot create API with no backend.");
        if (rendererType == RendererAPI::API::OpenGL)
        {
            return new OpenGLIndexBuffer(indices, size);
        }
        else
        {
            GN_CORE_ASSERT(true, "The backend type is not currently implemented.");
        }
    }

}