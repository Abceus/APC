#pragma once

#include <string>
#include <map>

#include "core/scene.h"

namespace apc
{
    class ISceneManager
    {
    public:
        virtual void addScene(std::string name, std::shared_ptr<IScene> scene) = 0;
        virtual void removeScene(std::string name) = 0;
        virtual void changeScene(std::string name) = 0;
        virtual std::shared_ptr<IScene> getScene(std::string name) const = 0;
        virtual std::shared_ptr<IScene> getCurrentScene() const = 0;
    };
}