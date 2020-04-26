#pragma once

#include "apc/context.h"
#include "apc/coord.h"
#include "apc/resource_manager.h"
#include <memory>
#include <string>


namespace apc
{
    class ITextureFactory;

    class Texture
    {
    public:
        ICoord getSize() const;

        static ResourcePtr<Texture> makeTexture(const std::string& path);

        static void setTextureFactory(std::shared_ptr<ITextureFactory> factory);
    protected:
        ICoord m_size;
    private:
        static std::shared_ptr<ITextureFactory> m_factory;
    };

    typedef ResourcePtr<Texture> TexturePtr;

    class ITextureFactory
    {
    public:
        virtual TexturePtr make(const std::string& path) = 0;
    };

    template <typename T>
    class TextureFactory : public ITextureFactory
    {
    public:
        TexturePtr make(const std::string& path) override;
    };

    template <typename T>
    TexturePtr TextureFactory<T>::make(const std::string& path) 
    {
        return static_resource_cast<Texture>( Context::getInstance().getResource<T>(path) );
    }
}