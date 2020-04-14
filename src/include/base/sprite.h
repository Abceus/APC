#pragma once

#include "core/component.h"
#include "core/components/drawable.h"
#include "base/resources/gl_texture.h"

namespace APC
{
    class Sprite : public Component, public IDrawable
    {
    public:
        Sprite() = default;
        void setTexture(GLTextureResourcePtr texture);
        void draw() override;
    private:
        GLTextureResourcePtr m_texture;
        GLuint VBO, VAO, EBO;
    };
}