#pragma once

#include <typeindex>
#include <memory>
#include <map>
#include <vector>
#include <string>
#include <algorithm>

#include "apc/component.h"
#include "apc/components/updatable.h"
#include "apc/components/clickable.h"

namespace apc
{
    class IDrawable; 

    class SceneObject
    {
    public:
        SceneObject( const std::string& layer = std::string("main") );

        void setLayer( const std::string& layer );
        std::string getLayer() const;

        template<typename T, typename std::enable_if<std::is_convertible<T*, Component*>::value, T>::type* = nullptr>
        void addComponent();

        template<typename T, typename std::enable_if<std::is_convertible<T*, Component*>::value, T>::type* = nullptr>
        void removeComponent();

        template<typename T>
        std::shared_ptr<typename std::enable_if<std::is_convertible<T*, Component*>::value, T>::type> getComponent() const;

        // void draw();
        void update(float dt);
        void click(const ICoord& coord);

        std::vector<std::shared_ptr<IDrawable>> getDrawables() const;

    private:
        std::map<std::type_index, std::shared_ptr<Component>> m_components;
        std::vector<std::shared_ptr<IDrawable>> m_drawables;
        std::vector<std::shared_ptr<IUpdatable>> m_updatables;
        std::vector<std::shared_ptr<IClickable>> m_clickables;
        std::string m_layer;
    };


    template<typename T, typename std::enable_if<std::is_convertible<T*, Component*>::value, T>::type*>
    void SceneObject::addComponent()
    {
        auto newComponent = std::make_shared<T>();
        m_components.emplace(std::type_index(typeid(T)), newComponent);
        newComponent->setSceneObject(this);

        auto updatable = std::dynamic_pointer_cast<IUpdatable>(newComponent);

        if(updatable)
        {
            m_updatables.emplace_back(updatable);
        }

        auto drawable = std::dynamic_pointer_cast<IDrawable>(newComponent);
        if(drawable)
        {
            m_drawables.emplace_back(drawable);
        }

        auto clickable = std::dynamic_pointer_cast<IClickable>(newComponent);
        if(clickable)
        {
            m_clickables.emplace_back(clickable);
        }

        newComponent->init();
    }


    template<typename T, typename std::enable_if<std::is_convertible<T*, Component*>::value, T>::type*>
    void SceneObject::removeComponent()
    {
        auto found = m_components.find(std::type_index(typeid(T)));
        if(found != m_components.end())
        {
            m_components.erase(found);
            found->second->setSceneObject(nullptr);

            auto drawable_it = std::find(m_drawables.begin(), m_drawables.end(), found->second);
            if(drawable_it != m_drawables.end())
            {
                m_drawables.erase(drawable_it);
            }
            
            auto updatable_it = std::find(m_updatables.begin(), m_updatables.end(), found->second);
            if(updatable_it != m_updatables.end())
            {
                m_updatables.erase(updatable_it);
            }

            auto clickable_it = std::find(m_clickables.begin(), m_clickables.end(), found->second);
            if(clickable_it != m_clickables.end())
            {
                m_clickables.erase(clickable_it);
            }
        }
    }

    template<typename T>
    std::shared_ptr<typename std::enable_if<std::is_convertible<T*, Component*>::value, T>::type> SceneObject::getComponent() const
    {
        auto found = m_components.find(std::type_index(typeid(T)));
        if(found != m_components.end())
        {
            return std::dynamic_pointer_cast<T>( found->second );
        }
        return nullptr;
    }
}