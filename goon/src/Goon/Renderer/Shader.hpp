#pragma once

namespace Goon
{
    class Shader
    {

    public:
        static Shader *Create(const std::string& vertexShader, const std::string& fragmentShader);
    };
}