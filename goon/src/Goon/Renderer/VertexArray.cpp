#include "gnpch.hpp"
#include <Goon/Renderer/VertexArray.hpp>
#include <Goon/Renderer/Renderer.hpp>
#include <Platform/OpenGL/OpenGLVertexArray.hpp>

namespace Goon
{

    VertexArray* VertexArray::Create()
    {
        auto rendererType = Renderer::GetAPI();
        GN_CORE_ASSERT(rendererType != RendererAPI::None, "Cannot create API with no backend.");
        if (rendererType == RendererAPI::OpenGL)
        {
            return new OpenGLVertexArray();
        }
        else
        {
            GN_CORE_ASSERT(true, "The backend type is not currently implemented.");
        }

    }
}