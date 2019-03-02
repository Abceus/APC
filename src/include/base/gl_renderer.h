#pragma once
#include "core/renderer.h"

#include "base/resource_manager.h"
#include "base/resources/gl_texture.h"

namespace APC
{
    class GLRenderer : public IRenderer
    {
    public:
        void init(int w, int h) override;
        void draw() override;
        void destroy() override;
    private:
        GLTextureResourcePtr m_texture;
        GLuint VBO, VAO, EBO;
        GLuint shaderProgram;
    };
}