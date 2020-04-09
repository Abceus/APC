#pragma once

#include "core/scene_manager.h"
#include <map>
#include <string>
#include <memory>

namespace APC
{
    class SceneManager : public ISceneManager
    {
    public:
        void addScene(std::string name, std::shared_ptr<IScene> scene) override;
        void removeScene(std::string name) override;
        void changeScene(std::string name) override;
        std::shared_ptr<IScene> getScene(std::string name) const override;
        std::shared_ptr<IScene> getCurrentScene() const override;
    private:
        std::map<std::string, std::shared_ptr<IScene>> m_scenes;
        std::shared_ptr<IScene> m_currentScene;
    };
}