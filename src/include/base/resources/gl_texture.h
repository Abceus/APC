#pragma once

#include <string>

#include "base/gl.h"
#include "base/resource_manager.h"
#include "base/resources/image.h"

namespace APC
{
    class GLTextureResource
    {
    public:
        GLTextureResource();
        GLTextureResource( const std::string& path );
        ~GLTextureResource();
        GLuint getIndex();
    private:
        GLuint m_index;
        int m_width, m_height;
    };
}