#pragma once
#include <gnpch.hpp>
#include <Goon/Renderer/Shader.hpp>

namespace Goon
{
    class OpenGLShader: public Shader
    {
    public:
        OpenGLShader(const std::string& vertex_shader, const std::string& fragment_shader);
        void Bind() override;
        void Unbind();
        std::string m_ShaderData;
    private:
        std::string LoadDataFromFile(std::string filepath);
        unsigned int m_Id;
    };
}