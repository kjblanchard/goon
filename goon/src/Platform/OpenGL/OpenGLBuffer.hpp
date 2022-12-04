#pragma once
#include <Goon/Renderer/Buffer.hpp>

namespace Goon
{
    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer(float *vertices, uint32_t size);
        ~OpenGLVertexBuffer();
        virtual void Bind() const override;
        virtual void UnBind() const override;

    private:
        uint32_t m_RendererID;
    };
}