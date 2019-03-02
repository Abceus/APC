#include "base/gl_renderer.h"
#include <iostream>

#include "base/gl.h"

namespace APC
{
    void GLRenderer::init(int w, int h)
    {
        glViewport(0, 0, w, h);
    }

    void GLRenderer::draw()
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }
}