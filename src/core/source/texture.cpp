#include "texture.h"

namespace apc
{
    std::shared_ptr<ITextureFactory> Texture::m_factory = nullptr;

    ICoord Texture::getSize() const
    {
        return m_size;
    }

    void Texture::setTextureFactory(std::shared_ptr<ITextureFactory> factory)
    {
        m_factory = factory;
    }

    ResourcePtr<Texture> Texture::makeTexture(const std::string& path)
    {
        if(m_factory)
        {
            return m_factory->make(path);
        }
        return ResourcePtr<Texture>();
    }
}