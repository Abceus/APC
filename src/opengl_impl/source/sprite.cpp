#include "sprite.h"

#include "apc/context.h"

namespace apc
{
    void Sprite::setTexture(GLTextureResourcePtr texture)
    {
        m_texture = texture;
        // float height = texture->getHeight() / static_cast<float>( Context::getInstance().getScreenSize().y );
        // float width = texture->getWidth() / static_cast<float>( Context::getInstance().getScreenSize().x );
        // float halfHeight = texture->getHeight() / 2;
        // float halfWidth = texture->getWidth() / 2;
        m_size = { static_cast<float>(texture->getWidth()), static_cast<float>(texture->getHeight()) };
        // m_size = { 500.0f, 500.0f };
        m_hotspot = { m_size.x/2.0f, m_size.y/2.0f };
        // GLfloat vertices[] = {
        //         // Positions          // Colors           // Texture Coords
        //         halfWidth,  halfHeight, 0.0f,   1.0f, 1.0f, // Bottom Right
        //         halfWidth, -halfHeight, 0.0f,   1.0f, 0.0f, // Top Right
        //         -halfWidth, -halfHeight, 0.0f,  0.0f, 0.0f, // Top Left
        //         -halfWidth,  halfHeight, 0.0f,  0.0f, 1.0f  // Bottom Left
        // };

        GLfloat vertices[] = {
                // Positions        // Texture Coords
                1.0f, 1.0f,         1.0f, 1.0f, // Bottom Right
                1.0f, 0.0f,         1.0f, 0.0f, // Top Right
                0.0f, 0.0f,         0.0f, 0.0f, // Top Left
                0.0f, 1.0f,         0.0f, 1.0f  // Bottom Left
        };

        // GLfloat vertices[] = {
        //         // Positions        // Texture Coords
        //         width, height,         1.0f, 1.0f, // Bottom Right
        //         width, 0.0f,         1.0f, 0.0f, // Top Right
        //         0.0f, 0.0f,         0.0f, 0.0f, // Top Left
        //         0.0f, height,         0.0f, 1.0f  // Bottom Left
        // };

        GLshort indices[] = {  // Note that we start from 0!
                0, 1, 3, // First Triangle
                1, 2, 3  // Second Triangle
        };

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // Position attribute
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);
        // TexCoord attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);

        glBindVertexArray(0); // Unbind VAO
    }

    void Sprite::draw()
    {
        glBindVertexArray(VAO);
        GLuint texture = 0;
        if(m_texture)
        {
            texture = m_texture->getIndex();
        }
        glBindTexture(GL_TEXTURE_2D, texture );

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

        glBindVertexArray(0);
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