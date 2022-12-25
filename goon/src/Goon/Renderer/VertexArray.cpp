#include "gnpch.hpp"
#include <Goon/Renderer/VertexArray.hpp>
#include <Goon/Renderer/RendererAPI.hpp>
#include <Platform/OpenGL/OpenGLVertexArray.hpp>

namespace Goon
{

    VertexArray* VertexArray::Create()
    {
        auto rendererType = RendererAPI::GetAPI();
        GN_CORE_ASSERT(rendererType != RendererAPI::API::None, "Cannot create API with no backend.");
        if (rendererType == RendererAPI::API::OpenGL)
        {
            return new OpenGLVertexArray();
        }
        else
        {
            GN_CORE_ASSERT(true, "The backend type is not currently implemented.");
        }

    }
}