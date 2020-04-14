#include "core/transform.h"
#include "base/context.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace APC
{
    Transform::Transform() : m_position({0.0f, 0.0f}), m_rotation(0.0f), m_scale({1.0f, 1.0f}), m_color({1.0f, 1.0f, 1.0f, 1.0f})
    {

    }
    void Transform::setParent(std::shared_ptr<Transform> parent)
    {
        m_parent = parent;
    }

    FCoord Transform::getPosition() const
    {
        return m_position;
    }

    void Transform::setPosition(FCoord position)
    {
        m_position = position;
    }

    float Transform::getRotation() const
    {
        return m_rotation;
    }

    void Transform::setRotation(float rotation)
    {
        m_rotation = rotation;
    }

    FCoord Transform::getScale() const
    {
        return m_scale;
    }

    void Transform::setScale(FCoord scale)
    {
        m_scale = scale;
    }

    void Transform::setScale(float scale)
    {
        m_scale = FCoord{scale, scale};
    }

    Color Transform::getColor() const
    {
        return m_color;
    }

    void Transform::setColor(Color color)
    {
        m_color = color;
    }

    glm::mat4 Transform::getMatrix() const
    {
        glm::mat4 result(1.0);

        if(m_parent)
        {
            result = m_parent->getMatrix();
        }

        result = glm::translate(result, glm::fvec3(m_position.x/Context::getInstance().getScreenSize().x, 
        m_position.y/Context::getInstance().getScreenSize().y, 0.0f));

        result = glm::rotate(result, glm::radians(-m_rotation), glm::fvec3(0.0f, 0.0f, 1.0f));

        result = glm::scale(result, glm::fvec3(m_scale.x, m_scale.y, 1.0f));

        return result;
    }

    void Transform::screenSizeChanged(const Coord& newSize)
    {
        
    }
}