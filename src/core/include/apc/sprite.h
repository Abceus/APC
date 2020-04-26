#pragma once

#include "apc/component.h"
#include "apc/texture.h"
#include "apc/components/drawable.h"
#include "apc/coord.h"

namespace apc
{
    class Sprite : public Component, public IDrawable
    {
    public:
        Sprite() = default;
        void setTexture(TexturePtr texture);
        void draw(VertexBatcher& batcher) override;
        FCoord getHotspot() const override;
        FCoord getSize() const override;
    private:
        TexturePtr m_texture;
        FCoord m_hotspot;
        FCoord m_size;
    };
}