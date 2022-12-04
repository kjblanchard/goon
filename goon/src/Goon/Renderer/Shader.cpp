#include <gnpch.hpp>
#include <Goon/Renderer/Renderer.hpp>
#include <Goon/Renderer/Shader.hpp>
#include <Platform/OpenGL/OpenGLShader.hpp>
#include <Goon/Core.hpp>
#include <Goon/Log.hpp>

namespace Goon
{

    Shader *Shader::Create(const std::string& vertexShader , const std::string& fragmentShader)
    {
        auto rendererType = Renderer::GetAPI();
        GN_CORE_ASSERT(rendererType != RendererAPI::None, "Cannot create API with no backend.");
        if (rendererType == RendererAPI::OpenGL)
        {
            return new OpenGLShader(vertexShader, fragmentShader);
        }
        else
        {
            GN_CORE_ASSERT(true, "The backend type is not currently implemented.");
        }
    }

}