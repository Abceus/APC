#include "sprite.h"

#include "context.h"
#include "transform.h"
#include "vertex_batching.h"

namespace apc
{
    void Sprite::setTexture(TexturePtr texture)
    {
        m_texture = texture;

        m_size = coord_cast<FCoord>( m_texture->getSize() );

        m_hotspot = { m_size.x/2.0f, m_size.y/2.0f };

        // GLfloat vertices[] = {
        //         // Positions        // Texture Coords
        //         1.0f, 1.0f,         1.0f, 1.0f, // Bottom Right
        //         1.0f, 0.0f,         1.0f, 0.0f, // Top Right
        //         0.0f, 0.0f,         0.0f, 0.0f, // Top Left
        //         0.0f, 1.0f,         0.0f, 1.0f  // Bottom Left
        // };

        // GLshort indices[] = {  // Note that we start from 0!
        //         0, 1, 3, // First Triangle
        //         1, 2, 3  // Second Triangle
        // };

        // glGenVertexArrays(1, &VAO);
        // glGenBuffers(1, &VBO);
        // glGenBuffers(1, &EBO);

        // glBindVertexArray(VAO);

        // glBindBuffer(GL_ARRAY_BUFFER, VBO);
        // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // // Position attribute
        // glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
        // glEnableVertexAttribArray(0);
        // // TexCoord attribute
        // glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
        // glEnableVertexAttribArray(1);

        // glBindVertexArray(0); // Unbind VAO
    }

    void Sprite::draw(VertexBatcher& batcher)
    {
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

    FCoord Sprite::getHotspot() const
    { 
        return m_hotspot;
    }

    FCoord Sprite::getSize() const
    { 
        return m_size;
    }
}