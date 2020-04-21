#pragma once

#include <memory>
#include "apc/coord.h"
#include "apc/color.h"
#include "apc/component.h"
#include "apc/components/screen_sensative.h"
#include "apc/matrix.h"

namespace apc
{
    class Transform : public Component, public IScreenSensative
    {
    public:
        Transform();
        
        FCoord getPosition() const;
        void setPosition(FCoord position);

        float getRotation() const;
        void setRotation(float rotation);

        FCoord getScale() const;
        void setScale(FCoord scale);
        void setScale(float scale);

        Color getColor() const;
        void setColor(Color color);

        void setParent(std::shared_ptr<Transform> parent);
        
        Matrixf33 getMatrix() const;

        void screenSizeChanged(const ICoord& newSize) override;
    private:
        FCoord m_position;
        float m_rotation;
        FCoord m_scale;
        Color m_color;
        std::shared_ptr<Transform> m_parent;
    };
}