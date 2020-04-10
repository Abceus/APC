#pragma once

#include "core/render_node.h"
#include <memory>

namespace APC
{
    class IDrawable
    {
    public:
        virtual void draw() = 0;
        virtual void setRenderNode(std::shared_ptr<RenderNode> renderNode) = 0;
        virtual std::shared_ptr<RenderNode> getRenderNode() const = 0;
        // virtual void setTransform(std::shared_ptr<IPosition> transform) = 0;
        // virtual std::shared_ptr<IPosition> getTransform() const = 0;
        virtual bool enabled() = 0;
    };
}
