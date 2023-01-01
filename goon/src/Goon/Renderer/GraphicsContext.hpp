#pragma once

namespace Goon
{

    class GraphicsContext
    {
        public:
        virtual ~GraphicsContext() = default;
    protected:
        virtual void Init() = 0;
        virtual void SwapBuffers() = 0;
    };
}