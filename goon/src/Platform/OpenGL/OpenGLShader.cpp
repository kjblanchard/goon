#include <Platform/OpenGL/OpenGLShader.hpp>
#include <Goon/Core.hpp>
#include <fstream>

namespace Goon
{

    OpenGLShader::OpenGLShader(std::string filepath)
    {
        m_ShaderData = LoadDataFromFile(filepath);
    }
    std::string OpenGLShader::LoadDataFromFile(std::string filepath)
    {

        std::string result;
        std::ifstream in(filepath, std::ios::in | std::ios::binary); // ifstream closes itself due to RAII
        if (in)
        {
            in.seekg(0, std::ios::end);
            size_t size = in.tellg();
            if (size != -1)
            {
                result.resize(size);
                in.seekg(0, std::ios::beg);
                in.read(&result[0], size);
            }
            else
            {
                GN_CORE_ERROR("Could not read from file '{0}'", filepath);
            }
        }
        else
        {
            GN_CORE_ERROR("Could not open file '{0}'", filepath);
        }

        return result;
    }

}