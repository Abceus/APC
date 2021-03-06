#include "resources/gl_texture.h"
#include "apc/context.h"

namespace apc
{
    GLTextureResource::GLTextureResource()
            : m_index( 0 )
    {
    }
    
    GLTextureResource::GLTextureResource( const std::string& path, const IFileLoader* loader )
     : m_index( 0 )
    {
        auto image = Context::getInstance().getResource<ImageResource>( path );
        glGenTextures( 1, &m_index );

        glBindTexture( GL_TEXTURE_2D, m_index );

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // Set texture filtering
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        auto comp = image->getChannels();

        m_size = { image->getWidth(), image->getHeight() };

        if(comp == 3)
        {
            glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, m_size.x, m_size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, image->getData() );
        }
        else if(comp == 4)
        {
            glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, m_size.x, m_size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->getData() );
        }

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    GLTextureResource::~GLTextureResource()
    {
        glDeleteTextures( 1, &m_index );
    }

    GLuint GLTextureResource::getIndex() const
    {
        return m_index;
    }
}