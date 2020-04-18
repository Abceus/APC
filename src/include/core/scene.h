#pragma once

#include <memory>
#include <string>
#include <vector>
#include <list>
#include "core/scene_object.h"
#include "core/coord.h"
#include "base/gl.h"

namespace apc
{
    class IScene
    {
    public:
        virtual void initLayers(const std::vector<std::string>& layers) = 0;
        virtual void addSceneObject(std::shared_ptr<SceneObject> gameObject, std::string layer) = 0;
        virtual void removeSceneObject(std::shared_ptr<SceneObject> gameObject, std::string layer) = 0;
        virtual std::vector<std::list<std::shared_ptr<SceneObject>>> getObjects() const = 0;

        virtual void update(float dt) = 0;
        virtual void click(const ICoord& coord) = 0;
    };
}