#pragma once
#include <gnpch.hpp>

namespace Goon
{
    class OpenGLShader
    {
    public:
        OpenGLShader(std::string filepath);
        std::string m_ShaderData;
    private:
        std::string LoadDataFromFile(std::string filepath);
    };
}