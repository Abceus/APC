#pragma once

#include <string>

#include "base/gl.h"
#include "core/resource_manager.h"
#include "base/resources/image.h"

namespace APC
{
    class GLTextureResource
    {
    public:
        GLTextureResource();
        GLTextureResource( const std::string& path, const IFileLoader* loader );
        ~GLTextureResource();
        GLuint getIndex();
    private:
        GLuint m_index;
        int m_width, m_height;
    };

    typedef ResourcePtr<GLTextureResource> GLTextureResourcePtr;
}