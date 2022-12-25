#include <gnpch.hpp>
#include <Goon/Renderer/Renderer.hpp>
#include <Goon/Renderer/Shader.hpp>
#include <Platform/OpenGL/OpenGLShader.hpp>
#include <Goon/Core.hpp>
#include <Goon/Log.hpp>
#include <Tools/io.hpp>

namespace Goon
{

    Shader *Shader::Create(const std::string &shaderSourcePath)
    {
        auto rendererType = RendererAPI::GetAPI();
        GN_CORE_ASSERT(rendererType != RendererAPI::API::None, "Cannot create API with no backend.");
        if (rendererType == RendererAPI::API::OpenGL)
        {
            std::string vFilePath = "shaders/vertex/" + shaderSourcePath;
            std::string fFilePath = "shaders/fragment/" + shaderSourcePath;
            auto vshader = ReadFromFile(vFilePath);
            auto fshader = ReadFromFile(fFilePath);
            return new OpenGLShader(vshader, fshader);
        }
        else
        {
            GN_CORE_ASSERT(true, "The backend type is not currently implemented.");
            return nullptr;
        }
    }


}