#include "sprite.h"

#include "context.h"
#include "transform.h"
#include "vertex_batching.h"

namespace apc
{
    void Sprite::setTexture(std::string texture)
    {
        m_textureName = texture;

        if(m_initialized)
        {
            init();
        }
    }

    void Sprite::draw(VertexBatcher& batcher)
    {
        if(!m_initialized)
        {
            return;
        }

        auto sceneObject = getSceneObject();
        auto transform = sceneObject->getComponent<Transform>();
        auto matrix = transform->getScaledMatrix();

        auto virtualWidth = Context::getInstance().getGameConfig().width;
        auto virtualHeight = Context::getInstance().getGameConfig().height;

        auto s = m_size;

        s.x /= virtualWidth;
        s.y /= virtualHeight;

        Matrixf33 size(1.0f);

        Matrixf33::scale( size, s );

        batcher.addVertices( sceneObject->getLayer(), static_resource_cast<Texture>( m_texture ), 
            {
                FCoord{ 0.5f, 0.5f },
                FCoord{ 0.5f, -0.5f },
                FCoord{ -0.5f, -0.5f },
                FCoord{ -0.5f, 0.5f }
            }, 
            {
                FCoord{ 1.0f, 1.0f },
                FCoord{ 1.0f, 0.0f },
                FCoord{ 0.0f, 0.0f },
                FCoord{ 0.0f, 1.0f }
            },
            {
                0, 1, 3, 
                1, 2, 3 
            },
            matrix * size, transform->getColor() );
        // glBindVertexArray(VAO);
        // GLuint texture = 0;
        // if(m_texture)
        // {
        //     texture = m_texture->getIndex();
        // }
        // glBindTexture(GL_TEXTURE_2D, texture );

        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

        // glBindVertexArray(0);
    }

    void Sprite::init()
    {
        if(!m_textureName.empty())
        {
            m_texture = Texture::makeTexture(m_textureName);

            m_size = coord_cast<FCoord>( m_texture->getSize() );

            m_hotspot = { m_size.x/2.0f, m_size.y/2.0f };

            m_initialized = true;
        }
    }

    void Sprite::deinit()
    {
        m_texture = TexturePtr();
        m_size = { 0.0f, 0.0f };
        m_hotspot = { 0.0f, 0.0f };
        m_initialized = false;
    }

    FCoord Sprite::getHotspot() const
    { 
        return m_hotspot;
    }

    FCoord Sprite::getSize() const
    { 
        return m_size;
    }
}