#pragma once

namespace Goon
{
    class Shader
    {

    public:
        virtual ~Shader() {}
        static Shader *Create(const std::string &shaderSourcePath);

    private:
        static std::string ReadFromFile(std::string &filepath);
    };
}