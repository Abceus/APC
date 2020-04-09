#pragma once

#include "base/drawable_impl.h"
#include "base/resources/gl_texture.h"

namespace APC
{
    class Sprite : public Drawable
    {
    public:
        Sprite(GLTextureResourcePtr texture);
        void draw() override;
    private:
        GLTextureResourcePtr m_texture;
        GLuint VBO, VAO, EBO;
    };
}