#pragma once

#include <string>

#include "apc/opengl/gl.h"
#include "apc/resource_manager.h"
#include "apc/texture.h"
#include "apc/opengl/resources/image.h"

namespace apc
{
    class GLTextureResource : public Texture
    {
    public:
        GLTextureResource();
        GLTextureResource( const std::string& path, const IFileLoader* loader );
        ~GLTextureResource();
        GLuint getIndex() const;
    private:
        GLuint m_index;
    };

    typedef ResourcePtr<GLTextureResource> GLTextureResourcePtr;
}