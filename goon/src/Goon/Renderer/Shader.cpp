#include <gnpch.hpp>
#include <Goon/Renderer/Renderer.hpp>
#include <Goon/Renderer/Shader.hpp>
#include <Platform/OpenGL/OpenGLShader.hpp>
#include <Goon/Core.hpp>
#include <Goon/Log.hpp>

namespace Goon
{

    Shader *Shader::Create(const std::string &shaderSourcePath)
    {
        auto rendererType = Renderer::GetAPI();
        GN_CORE_ASSERT(rendererType != RendererAPI::None, "Cannot create API with no backend.");
        if (rendererType == RendererAPI::OpenGL)
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

    std::string Shader::ReadFromFile(std::string &filepath)
    {
        std::stringstream data;
        std::ifstream source(filepath, std::ifstream::in);
        char c = source.get();
        while (source.good())
        {
            data << c;
            c = source.get();
        }
        GN_CORE_TRACE("Shader is {0}", data.str());
        source.close();
        return data.str();
    }

}