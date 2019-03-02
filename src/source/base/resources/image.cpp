#include <cstring>

#include "base/resources/image.h"
#define STB_IMAGE_IMPLEMENTATION
#include "third/stb/stb_image.h"

namespace APC
{
    ImageResource::ImageResource()
            : m_data( nullptr )
            , m_width( 0 )
            , m_height( 0 )
            , m_channels( 0 )
    {
    }

    ImageResource::ImageResource( const std::string& path )
        : m_data( nullptr )
        , m_width( 0 )
        , m_height( 0 )
        , m_channels( 0 )
    {
        m_data = stbi_load(path.c_str(), &m_width, &m_height, &m_channels, STBI_rgb_alpha);
    }

    ImageResource::~ImageResource()
    {
        stbi_image_free( m_data );
    }

    int ImageResource::getWidth()
    {
        return m_width;
    }

    int ImageResource::getHeight()
    {
        return m_height;
    }

    int ImageResource::getChannels()
    {
        return m_channels;
    }

    const unsigned char* ImageResource::getData()
    {
        return m_data;
    }
}