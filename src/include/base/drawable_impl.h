#include "core/utility.h"
#include "core/transform.h"
#include "core/drawable.h"
#include "base/transform_impl.h"
#include <memory>

namespace APC
{
    class Drawable : public IDrawable
    {
    public:
        // void setTransform(std::shared_ptr<ITransform> transform) override;
        // std::shared_ptr<ITransform> getTransform() const override;
        void setRenderNode(std::shared_ptr<RenderNode> renderNode) override;
        std::shared_ptr<RenderNode> getRenderNode() const override;
        bool enabled() override;
        void setEnabled(bool enabled);
    protected:
        // std::shared_ptr<ITransform> m_transform;
        std::shared_ptr<RenderNode> m_renderNode;
        bool m_enabled;
    };
}
