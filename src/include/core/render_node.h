#pragma once

#include <memory>
#include "core/transform.h"

namespace APC
{
    class RenderNode
    {
    public:
        template<typename T>
        std::shared_ptr<typename std::enable_if<std::is_convertible<T*, IPosition*>::value, T>::type> getTypedPositionTransform();

        template<typename T>
        std::shared_ptr<typename std::enable_if<std::is_convertible<T*, IRotation*>::value, T>::type> getTypedRotationTransform();

        template<typename T>
        std::shared_ptr<typename std::enable_if<std::is_convertible<T*, IScale*>::value, T>::type> getTypedScaleTransform();

        template<typename T>
        std::shared_ptr<typename std::enable_if<std::is_convertible<T*, IColor*>::value, T>::type> getTypedColorTransform();

        void setParent(std::shared_ptr<RenderNode> parent);
        FCoord getPosition() const;
        Color getColor() const;
        glm::mat4 getMatrix() const;
    private:
        std::shared_ptr<IPosition> m_position;
        std::shared_ptr<IRotation> m_rotation;
        std::shared_ptr<IScale> m_scale;
        std::shared_ptr<IColor> m_color;
        std::shared_ptr<RenderNode> m_parent;
    };

    template<typename T>
    std::shared_ptr<typename std::enable_if<std::is_convertible<T*, IPosition*>::value, T>::type> RenderNode::getTypedPositionTransform()
    {
        auto transform = std::dynamic_pointer_cast<T>(m_position);
        if(transform)
        {
            return transform;
        }
        m_position = std::make_shared<T>();
        return std::dynamic_pointer_cast<T>(m_position);
    }

    template<typename T>
    std::shared_ptr<typename std::enable_if<std::is_convertible<T*, IRotation*>::value, T>::type> RenderNode::getTypedRotationTransform()
    {
        auto transform = std::dynamic_pointer_cast<T>(m_rotation);
        if(transform)
        {
            return transform;
        }
        m_rotation = std::make_shared<T>();
        return std::dynamic_pointer_cast<T>(m_rotation);
    }

    template<typename T>
    std::shared_ptr<typename std::enable_if<std::is_convertible<T*, IScale*>::value, T>::type> RenderNode::getTypedScaleTransform()
    {
        auto transform = std::dynamic_pointer_cast<T>(m_scale);
        if(transform)
        {
            return transform;
        }
        m_scale = std::make_shared<T>();
        return std::dynamic_pointer_cast<T>(m_scale);
    }

    template<typename T>
    std::shared_ptr<typename std::enable_if<std::is_convertible<T*, IColor*>::value, T>::type> RenderNode::getTypedColorTransform()
    {
        auto transform = std::dynamic_pointer_cast<T>(m_color);
        if(transform)
        {
            return transform;
        }
        m_color = std::make_shared<T>();
        return std::dynamic_pointer_cast<T>(m_color);
    }
}