#pragma once
#include "core/renderer.h"

#include "core/resource_manager.h"
#include "base/resources/gl_texture.h"
#include "core/drawable.h"

#include <list>

namespace APC
{
    class GLRenderer : public IRenderer
    {
    public:
        GLRenderer();
        void init(int w, int h) override;
        void draw() override;
        void destroy() override;
        int getWidth() override;
        int getHeight() override;
    private:
        // GLTextureResourcePtr m_texture;
        // GLuint VBO, VAO, EBO;
        GLuint shaderProgram;
        int m_width, m_height;
    };
}