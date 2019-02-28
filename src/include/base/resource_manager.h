#pragma once

#include <string>
#include <map>
#include <functional>

namespace APC
{
    template<typename ResourceType>
    class ResourcePtr
    {
    public:
        ResourcePtr( std::function<void()>&& slot, const std::string& path );
        ResourcePtr( const ResourcePtr& copy );
        ResourcePtr( ResourcePtr&& copy ) noexcept;
        ~ResourcePtr();
        ResourceType* operator->();
    private:
        ResourceType* m_value;
        long* m_count;
        std::function<void()> m_removeSignal;
        std::string m_path;
        bool m_moved;
    };

    template<typename ResourceType>
    class ResourceManager
    {
    public:
        ResourcePtr<ResourceType> getResource( const std::string& path );
    private:
        std::map<std::string, ResourcePtr<ResourceType>> m_resources;
    };

    class ResourcesManager
    {
    public:
        template<typename ResourceType>
        ResourceType getResource( const std::string &path );
    };

    // Implementation
    template<typename ResourceType>
    ResourcePtr<ResourceType>::ResourcePtr( std::function<void()>&& slot, const std::string& path )
            : m_value(new ResourceType())
            , m_count(new long(1))
            , m_removeSignal(std::move(slot))
            , m_moved(false)
            , m_path(path)
    {

    }

    template<typename ResourceType>
    ResourcePtr<ResourceType>::ResourcePtr( const ResourcePtr &copy )
    {
        m_count = copy.m_count;
        m_value = copy.m_value;
        m_removeSignal = copy.m_removeSignal;
        m_path = copy.m_path;
        m_moved = false;
        (*m_count)++;
    }

    template<typename ResourceType>
    ResourcePtr<ResourceType>::ResourcePtr( ResourcePtr&& copy ) noexcept
    {
        m_count = copy.m_count;
        m_value = copy.m_value;
        m_path = copy.m_path;
        m_moved = false;
        m_removeSignal = std::move(copy.m_removeSignal);
        copy.m_moved = true;
    }

    template<typename ResourceType>
    ResourcePtr<ResourceType>::~ResourcePtr()
    {
        if(!m_moved)
        {
            (*m_count)--;
            if ( *m_count == 1 )
            {
                m_removeSignal(m_path);
            } else if ( *m_count == 0 )
            {
                delete m_value;
                delete m_count;
            }
        }
    }

    template<typename ResourceType>
    ResourceType* ResourcePtr<ResourceType>::operator->()
    {
        return m_value;
    }

    template<typename ResourceType>
    ResourcePtr<ResourceType> ResourceManager<ResourceType>::getResource( const std::string &path )
    {
        auto found = m_resources.find(path);
        if(found == m_resources.end())
        {
            m_resources.emplace(path, ResourcePtr<ResourceType>( [this]( const std::string& path ){ this->m_resources.erase(path); } ));
            found = m_resources.find(path);
        }
        return found->second;
    }

    template<typename ResourceType>
    ResourceType ResourcesManager::getResource( const std::string &path )
    {
        static ResourceManager<ResourceType> rm;
        return rm.getResource(path);
    }
}