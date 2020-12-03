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
        // void setTexture(TexturePtr texture);
        void setTexture(std::string texture);
        void draw(VertexBatcher& batcher) override;
        void init() override;
        void deinit() override;
        FCoord getHotspot() const override;
        FCoord getSize() const override;
    private:
        TexturePtr m_texture;
        std::string m_textureName;
        FCoord m_hotspot;
        FCoord m_size;
        bool m_initialized = false;
    };
}