#include <Platform/OpenGL/OpenGLShader.hpp>
#include <Goon/Core.hpp>
#include <glad/glad.h>

namespace Goon
{
    OpenGLShader::OpenGLShader(const std::string &vertex_shader, const std::string &fragment_shader)
    {
        //vertex
        unsigned int vertexShader;
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        const GLchar *vertex = vertex_shader.c_str();
        glShaderSource(vertexShader, 1, &vertex, NULL);

        glCompileShader(vertexShader);
        // Check if we are able to compile the shader
        int success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            GN_CORE_ERROR("Vertex shader compilation failed, {0}", infoLog);
        }
        // end vertex

        // fragment
        unsigned int fragmentShader;
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        const GLchar *fragment = fragment_shader.c_str();
        glShaderSource(fragmentShader, 1, &fragment, NULL);
        glCompileShader(fragmentShader);
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            GN_CORE_ERROR("Fragment shader compilation failed, {0}", infoLog);
        }
        // end Fragment Shader

        // Shader program
        m_Id = glCreateProgram();
        glAttachShader(m_Id, vertexShader);
        glAttachShader(m_Id, fragmentShader);
        glLinkProgram(m_Id);
        glUseProgram(m_Id);

        // Cleanup and get rid of te shaders.
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    void OpenGLShader::Bind()
    {
        glUseProgram(m_Id);
    }
    void OpenGLShader::Unbind()
    {
        glUseProgram(0);
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
