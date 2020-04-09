#pragma once

#include <list>
#include <vector>
#include <string>
#include "core/scene.h"

namespace APC
{
    class Scene : public IScene
    {
    public:
        void initLayers(const std::vector<std::string>& layers) override;
        void draw(GLuint shaderProgram) override;
        // std::shared_ptr<RenderNode> getRootNode() const override;
        void addDrawable(std::shared_ptr<IDrawable> drawable, std::string layer) override;
        void removeDrawable(std::shared_ptr<IDrawable> drawable, std::string layer) override;
    private:
        std::vector<std::list<std::shared_ptr<IDrawable>>> m_drawables;
        std::vector<std::string> m_layers;
        // std::shared_ptr<RenderNode> m_rootNode;
    };
}
