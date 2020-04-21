#pragma once

#include "apc/component.h"
#include "apc/components/drawable.h"
#include "apc/opengl/resources/gl_texture.h"
#include "apc/coord.h"

namespace apc
{
    class Sprite : public Component, public IDrawable
    {
    public:
        Sprite() = default;
        void setTexture(GLTextureResourcePtr texture);
        void draw() override;
        FCoord getHotspot() const override;
        FCoord getSize() const override;
    private:
        GLTextureResourcePtr m_texture;
        GLuint VBO, VAO, EBO;
        FCoord m_hotspot;
        FCoord m_size;
    };
}