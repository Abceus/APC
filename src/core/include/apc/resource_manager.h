#pragma once

#include <string>
#include <map>
#include <functional>

#include "apc/file_loader.h"

namespace apc
{
    template<typename ResourceType>
    class ResourcePtr
    {
    public:
        ResourcePtr();
        ResourcePtr( std::function<void(std::string)>&& slot, const std::string& path, const IFileLoader* loader );
        ResourcePtr( const ResourcePtr<ResourceType>& copy );
        template<typename OtherResourceType>
        ResourcePtr( const ResourcePtr<OtherResourceType>& alias, ResourceType* ptr );
        ResourcePtr( ResourcePtr<ResourceType>&& copy ) noexcept;
        ~ResourcePtr();
        ResourceType* operator->();
        ResourceType* get();
        operator bool() const;
        ResourcePtr<ResourceType>& operator=(ResourcePtr<ResourceType> const&);
        ResourcePtr<ResourceType>& operator=(ResourcePtr<ResourceType>&&);
        void removeSignalDisable();
        std::string getPath() const;
        std::function<void(std::string)> getRemoveSignal() const;
        long* getCounter() const;
    private:
        ResourceType* m_value;
        long* m_count;
        std::function<void(std::string)> m_removeSignal;
        std::string m_path;
        bool m_moved;
    };

    template<typename ResourceType>
    class ResourceManager
    {
    public:
        ResourcePtr<ResourceType> getResource( const std::string& path, const IFileLoader* loader );
        ~ResourceManager();
    private:
        std::map<std::string, ResourcePtr<ResourceType>> m_resources;
    };

    // Implementation
    template<typename ResourceType>
    ResourcePtr<ResourceType>::ResourcePtr()
        : m_value(new ResourceType())
        , m_count(new long(1))
    {
    }

    template<typename ResourceType>
    ResourcePtr<ResourceType>::ResourcePtr( std::function<void(std::string)>&& slot, const std::string& path, const IFileLoader* loader )
            : m_value(new ResourceType( path, loader ))
            , m_count(new long(1))
            , m_removeSignal(std::move(slot))
            , m_moved(false)
            , m_path(path)
    {

    }

    template<typename ResourceType>
    ResourcePtr<ResourceType>::ResourcePtr( const ResourcePtr<ResourceType> &copy )
    {
        m_count = copy.m_count;
        m_value = copy.m_value;
        m_removeSignal = copy.m_removeSignal;
        m_path = copy.m_path;
        m_moved = false;
        (*m_count)++;
    }

    template<typename ResourceType>
    ResourcePtr<ResourceType>::ResourcePtr( ResourcePtr<ResourceType>&& copy ) noexcept
    {
        m_count = copy.m_count;
        m_value = copy.m_value;
        m_path = copy.m_path;
        m_moved = false;
        m_removeSignal = std::move(copy.m_removeSignal);
        copy.m_moved = true;
    }

    template<typename ResourceType>
    template<typename OtherResourceType>
    ResourcePtr<ResourceType>::ResourcePtr( const ResourcePtr<OtherResourceType>& alias, ResourceType* ptr )
    {
        m_count = alias.getCounter();
        m_value = ptr;
        m_removeSignal = alias.getRemoveSignal();
        m_path = alias.getPath();
        m_moved = false;
        (*m_count)++;  
    }

    template<typename ResourceType>
    ResourcePtr<ResourceType>::~ResourcePtr()
    {
        if(!m_moved)
        {
            (*m_count)--;
            if ( *m_count == 1 )
            {
                if(m_removeSignal)
                {
                    m_removeSignal(m_path);
                }
            } else if ( *m_count == 0 )
            {
                if(m_value)
                {
                    delete m_value;
                    delete m_count;
                }
            }
        }
    }

    template<typename ResourceType>
    ResourceType* ResourcePtr<ResourceType>::operator->()
    {
        return m_value;
    }

    template<typename ResourceType>
    ResourceType* ResourcePtr<ResourceType>::get()
    {
        return m_value;
    }

    template<typename ResourceType>
    ResourcePtr<ResourceType>::operator bool() const
    {
        return m_value;
    }

    template<typename ResourceType>
    ResourcePtr<ResourceType>& ResourcePtr<ResourceType>::operator=(ResourcePtr<ResourceType> const& copy)
    {
        m_count = copy.m_count;
        m_value = copy.m_value;
        m_removeSignal = copy.m_removeSignal;
        m_path = copy.m_path;
        m_moved = false;
        (*m_count)++;
        return *this;
    }

    template<typename ResourceType>
    ResourcePtr<ResourceType>& ResourcePtr<ResourceType>::operator=(ResourcePtr<ResourceType>&& copy)
    {
        m_count = copy.m_count;
        m_value = copy.m_value;
        m_path = copy.m_path;
        m_moved = false;
        m_removeSignal = std::move(copy.m_removeSignal);
        copy.m_moved = true;
        return *this;
    }

    template<typename ResourceType>
    void ResourcePtr<ResourceType>::removeSignalDisable()
    {
        m_removeSignal = nullptr;
    }

    template<typename ResourceType>
    std::string ResourcePtr<ResourceType>::getPath() const
    {
        return m_path;
    }

    template<typename ResourceType>
    std::function<void(std::string)> ResourcePtr<ResourceType>::getRemoveSignal() const
    {
        return m_removeSignal;
    }

    template<typename ResourceType>
    long* ResourcePtr<ResourceType>::getCounter() const
    {
        return m_count;
    }

    template<typename ResourceType>
    ResourcePtr<ResourceType> ResourceManager<ResourceType>::getResource( const std::string &path, const IFileLoader* loader )
    {
        auto found = m_resources.find(path);
        if(found == m_resources.end())
        {
            m_resources.emplace(path, ResourcePtr<ResourceType>( [this]( const std::string& path ){ m_resources.erase(path); }, path, loader ));
            found = m_resources.find(path);
        }
        return found->second;
    }

    template<typename ResourceType>
    ResourceManager<ResourceType>::~ResourceManager()
    {
        for(auto& resource : m_resources)
        {
            resource.second.removeSignalDisable();
        }
    }

    template<typename CastResourceType, typename OriginResourceType>
    ResourcePtr<CastResourceType> static_resource_cast( ResourcePtr<OriginResourceType> resource )
    {
        return ResourcePtr<CastResourceType>( resource, static_cast<CastResourceType*>(resource.get()) );
    }
}