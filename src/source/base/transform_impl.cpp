#include "base/transform_impl.h"
#include "base/context.h"

namespace APC
{
    FCoord TPosition::get() const
    {
        return m_position;
    }

    glm::mat4 TPosition::getMatrix() const
    {
        glm::mat4 trans(1.0);
        auto width =  static_cast<float>(Context::getInstance().getScreenSize().x);
        auto height =  static_cast<float>(Context::getInstance().getScreenSize().y);
        auto x = static_cast<float>(m_position.x);
        auto y = static_cast<float>(m_position.y);
        trans = glm::translate(trans, glm::vec3(x/width, y/height, 0.0f));

        return trans;
    }

    void TPosition::set(const FCoord& position)
    {
        m_position = position;
    }

    FCoord TScreenPosition::get() const
    {
        return FCoord{ m_position.x * m_screenSize.x, m_position.y * m_screenSize.y };
    }

    glm::mat4 TScreenPosition::getMatrix() const
    {
        glm::mat4 trans(1.0);
        trans = glm::translate(trans, glm::vec3(m_position.x, m_position.y, 0.0f));
        return trans;
    }

    void TScreenPosition::set(const FCoord& position)
    {
        m_position = position;
    }

    void TScreenPosition::setScreenSize(const Coord& screenSize)
    {
        m_screenSize = screenSize;
    }

    float TRotation::get() const 
    {
        return m_rotation;
    }

    glm::mat4 TRotation::getMatrix() const
    {
        glm::mat4 trans(1.0);
        trans = glm::rotate(trans, glm::radians(-m_rotation), glm::vec3(0.0f, 0.0f, 1.0f));
        return trans;
    }

    void TRotation::set(float rotation)
    {
        m_rotation = rotation;
    }

    FCoord TScale::get() const
    {
        return m_scale;
    }

    glm::mat4 TScale::getMatrix() const
    {
        glm::mat4 trans(1.0);
        trans = glm::scale(trans, glm::vec3(m_scale.x, m_scale.y, 1.0f));
        return trans;
    }

    void TScale::set(const FCoord& scale)
    {
        m_scale = scale;
    }

    void TScale::set(float scale)
    {
        m_scale = FCoord{scale, scale};
    }

    void TColor::set(Color color)
    {
        m_color = color;
    }

    Color TColor::get() const
    {
        return m_color;
    }
}