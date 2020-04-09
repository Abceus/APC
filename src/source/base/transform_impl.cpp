#include "base/transform_impl.h"
#include "base/context.h"

namespace APC
{
    Coord Position::getPosition() const
    {
        return m_position;
    }

    glm::mat4 Position::getMatrix() const
    {
        glm::mat4 trans(1.0);
        auto width =  static_cast<float>(Context::getInstance().getScreenSize().x);
        auto height =  static_cast<float>(Context::getInstance().getScreenSize().y);
        auto x = static_cast<float>(m_position.x);
        auto y = static_cast<float>(m_position.y);
        trans = glm::translate(trans, glm::vec3(x/width, y/height, 0.0f));

        return trans;
    }

    void Position::setPosition(const Coord& position)
    {
        m_position = position;
    }

    Coord ScreenPosition::getPosition() const
    {
        return Coord{ m_position.x * static_cast<float>(m_screenSize.x), m_position.y * static_cast<float>(m_screenSize.y) };
    }

    glm::mat4 ScreenPosition::getMatrix() const
    {
        glm::mat4 trans(1.0);
        trans = glm::translate(trans, glm::vec3(m_position.x, m_position.y, 0.0f));
        return trans;
    }

    void ScreenPosition::setPosition(const FCoord& position)
    {
        m_position = position;
    }

    void ScreenPosition::setScreenSize(const Coord& screenSize)
    {
        m_screenSize = screenSize;
    }
}