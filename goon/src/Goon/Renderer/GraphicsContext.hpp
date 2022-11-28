#pragma once

namespace Goon {

    class GraphicsContext
    {
    protected:
        virtual void Init() = 0;
        virtual void SwapBuffers() = 0;
    };


}