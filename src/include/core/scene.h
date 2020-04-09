#pragma once

#include <memory>
#include <string>
#include <vector>
#include "core/drawable.h"
#include "base/gl.h"

namespace APC
{
    class IScene
    {
    public:
        virtual void initLayers(const std::vector<std::string>& layers) = 0;
        virtual void draw(GLuint shaderProgram) = 0;
        // virtual std::shared_ptr<RenderNode> getRootNode() const = 0;
        virtual void addDrawable(std::shared_ptr<IDrawable> drawable, std::string layer) = 0;
        virtual void removeDrawable(std::shared_ptr<IDrawable> drawable, std::string layer) = 0;
    };
}