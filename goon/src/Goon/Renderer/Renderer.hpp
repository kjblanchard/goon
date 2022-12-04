#pragma once

namespace Goon
{

    enum class RendererAPI
    {
        None = 0,
        OpenGL = 1
    };

    class Renderer
    {
    public:
        inline static RendererAPI GetAPI() { return s_RendererAPI; }
        static void ToggleWireframe();

    private:
        static RendererAPI s_RendererAPI;
    };

}