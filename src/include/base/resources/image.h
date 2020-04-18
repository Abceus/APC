#pragma once
#include <string>
#include <vector>

#include "core/resource_manager.h"

namespace apc
{
    class ImageResource
    {
    public:
        ImageResource();
        ImageResource( const std::string& path, const IFileLoader* loader );
        ~ImageResource();
        int getWidth();
        int getHeight();
        int getChannels();
        const unsigned char* getData();
    private:
        unsigned char* m_data;
        int m_width, m_height, m_channels;
    };

    typedef ResourcePtr<ImageResource> ImageResourcePtr;
}