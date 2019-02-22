#include "base/gl_renderer.h"
#include <iostream>

#ifdef GLES2
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#else
#include <GL/gl.h>
#include <GL/glext.h>
#endif

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