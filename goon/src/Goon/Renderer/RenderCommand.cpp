#include <gnpch.hpp>
#include <Goon/Renderer/RenderCommand.hpp>
#include <Platform/OpenGL/OpenGLRendererAPI.hpp>

namespace Goon
{
        RendererAPI *RenderCommand::s_RendererAPI = new OpenGLRendererAPI();

}