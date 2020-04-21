#pragma once

#include "apc/scene_manager.h"
#include "apc/scene.h"
#include <map>
#include <string>
#include <memory>

namespace apc
{
    class SceneManager
    {
    public:
        void addScene(std::string name, std::shared_ptr<IScene> scene);
        void removeScene(std::string name);
        void changeScene(std::string name);
        std::shared_ptr<IScene> getScene(std::string name) const;
        std::shared_ptr<IScene> getCurrentScene() const;
    private:
        std::map<std::string, std::shared_ptr<IScene>> m_scenes;
        std::shared_ptr<IScene> m_currentScene;
    };
}