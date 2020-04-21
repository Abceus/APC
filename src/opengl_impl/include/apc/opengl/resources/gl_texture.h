#pragma once

#include <string>

#include "apc/opengl/gl.h"
#include "apc/resource_manager.h"
#include "apc/opengl/resources/image.h"

namespace apc
{
    class GLTextureResource
    {
    public:
        GLTextureResource();
        GLTextureResource( const std::string& path, const IFileLoader* loader );
        ~GLTextureResource();
        GLuint getIndex() const;
        int getHeight() const;
        int getWidth() const;
    private:
        GLuint m_index;
        int m_width, m_height;
    };

    typedef ResourcePtr<GLTextureResource> GLTextureResourcePtr;
}