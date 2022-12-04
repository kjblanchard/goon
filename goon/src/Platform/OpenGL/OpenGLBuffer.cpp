#include <gnpch.hpp>
#include <glad/glad.h>
#include <Platform/OpenGL/OpenGLBuffer.hpp>
#include <Goon/Renderer/Renderer.hpp>
#include <Goon/Core.hpp>

namespace Goon
{

    OpenGLVertexBuffer::OpenGLVertexBuffer(float *vertices, uint32_t size)
    {
        glGenBuffers(1, &m_RendererID);
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        // Now we need to put this data on the GPU, as it was on the CPU before.
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }
    OpenGLVertexBuffer::~OpenGLVertexBuffer()
    {
        glDeleteBuffers(1, &m_RendererID);
    }
    void OpenGLVertexBuffer::Bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    }
    void OpenGLVertexBuffer::UnBind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

}