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
        // virtual void SetLayout(const BufferLayout& layout) const override;
        virtual void SetLayout(const BufferLayout &layout) override { m_Layout = layout;}
        virtual BufferLayout GetLayout() const override { return m_Layout; }

    private:
        uint32_t m_RendererID;
        BufferLayout m_Layout = BufferLayout();
    };

    // Index buffer (element buffer)
    // This tells you the "order" to draw this with the indices
    class OpenGLIndexBuffer : public IndexBuffer
    {
    public:
        OpenGLIndexBuffer(uint32_t *indices, uint32_t size);
        ~OpenGLIndexBuffer();
        inline virtual int GetCount() const { return m_Count; }
        virtual void Bind() const override;
        virtual void UnBind() const override;

    private:
        uint32_t m_RendererID;
        unsigned int m_Count;
    };
}