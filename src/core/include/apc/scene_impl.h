#pragma once

#include <list>
#include <vector>
#include <string>
#include <memory>
#include "apc/scene.h"
#include "apc/scene_object.h"

namespace apc
{
    class Scene : public IScene
    {
    public:
        void initLayers(const std::vector<std::string>& layers) override;
        std::vector<std::string> getLayers() const override;
        // void draw(GLuint shaderProgram) override;
        // std::shared_ptr<RenderNode> getRootNode() const override;
        // void addDrawable(std::shared_ptr<IDrawable> drawable, std::string layer) override;
        // void removeDrawable(std::shared_ptr<IDrawable> drawable, std::string layer) override;
        void addSceneObject(std::shared_ptr<SceneObject> gameObject, std::string layer) override;
        void removeSceneObject(std::shared_ptr<SceneObject> gameObject, std::string layer) override;
        // std::vector<std::list<std::shared_ptr<SceneObject>>> getObjects() const override;
        std::list<std::shared_ptr<SceneObject>> getObjects() const override;

        void update(float dt) override;
        void click(const ICoord& coord) override;
    private:
        // std::vector<std::list<std::shared_ptr<SceneObject>>> m_objects;
        std::list<std::shared_ptr<SceneObject>> m_objects;
        std::vector<std::string> m_layers;
        // std::shared_ptr<RenderNode> m_rootNode;
    };
}
