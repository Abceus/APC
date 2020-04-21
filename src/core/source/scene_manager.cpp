#include "scene_manager.h"
#include <algorithm>

namespace apc
{
    void SceneManager::addScene(std::string name, std::shared_ptr<IScene> scene)
    {
        m_scenes.emplace(name, scene);
    }

    void SceneManager::removeScene(std::string name)
    {
        auto found = m_scenes.find( name );
        if(found != m_scenes.end())
        {
            m_scenes.erase(found);
        }
    }

    void SceneManager::changeScene(std::string name)
    {
        auto found = m_scenes.find( name );
        if(found != m_scenes.end())
        {
            m_currentScene = found->second;
        }
    }

    std::shared_ptr<IScene> SceneManager::getScene(std::string name) const 
    {
        auto found = m_scenes.find( name );
        if(found != m_scenes.end())
        {
            return found->second;
        }
        return nullptr;
    }

    std::shared_ptr<IScene> SceneManager::getCurrentScene() const 
    {
        return m_currentScene;
    }
}