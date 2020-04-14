#pragma once

#include <memory>
#include <glm/glm.hpp>
#include "core/utility.h"
#include "core/component.h"
#include "core/components/screen_sensative.h"

namespace APC
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
        
        glm::mat4 getMatrix() const;

        void screenSizeChanged(const Coord& newSize) override;
    private:
        FCoord m_position;
        float m_rotation;
        FCoord m_scale;
        Color m_color;
        std::shared_ptr<Transform> m_parent;
    };
}