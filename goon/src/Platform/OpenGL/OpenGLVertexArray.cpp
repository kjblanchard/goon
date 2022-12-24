#include <gnpch.hpp>
#include <Platform/OpenGL/OpenGLVertexArray.hpp>
#include <glad/glad.h>

namespace Goon
{
    static GLenum ShaderDataTypeToGLBaseType(ShaderDataType type)
    {
        switch (type)
        {
        case ShaderDataType::Float:
        case ShaderDataType::Float2:
        case ShaderDataType::Float3:
        case ShaderDataType::Float4:
        case ShaderDataType::Mat3:
        case ShaderDataType::Mat4:
            return GL_FLOAT;
        case ShaderDataType::Int:
        case ShaderDataType::Int2:
        case ShaderDataType::Int3:
        case ShaderDataType::Int4:
            return GL_INT;
        case ShaderDataType::Bool:
            return GL_BOOL;
        }

        return 0;
    }
    OpenGLVertexArray::OpenGLVertexArray()
    {
        glGenVertexArrays(1, &m_RendererID);
    }
    OpenGLVertexArray::~OpenGLVertexArray()
    {
        glDeleteVertexArrays(1, &m_RendererID);
    }
    void OpenGLVertexArray::Bind() const
    {
        glBindVertexArray(m_RendererID);
    }
    void OpenGLVertexArray::UnBind() const
    {
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer> &vertexBuffer)
    {
        glBindVertexArray(m_RendererID);
        vertexBuffer->Bind();
        GN_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex buffer has no layout!")
        uint32_t index = 0;
        const auto &layout = vertexBuffer->GetLayout();
        for (const auto &element : layout)
        {
            // this is 0 as we set the location = 0 in the vertex shader above.
            glEnableVertexAttribArray(index);
            // We need to tell opengl what this vertices actually looks like.
            // on index 0, we are using 3 each, there is 3 * float for each vertice (we are saying one), then since it is the initial vertice,
            // it beins at byte 0 (it is the only one)
            glVertexAttribPointer(index,
                                  element.GetElementCount(),
                                  ShaderDataTypeToGLBaseType(element.Type),
                                  element.Normalized ? GL_TRUE : GL_FALSE,
                                  layout.GetStride(),
                                  (const void *)element.Offset);
            ++index;
        }
        m_VertexBuffers.push_back(vertexBuffer);
    }
    void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer> &indexBuffer)
    {
        m_IndexBuffer = indexBuffer;
        glBindVertexArray(m_RendererID);
        indexBuffer->Bind();
    }

}