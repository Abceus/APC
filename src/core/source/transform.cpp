#include "transform.h"
#include "context.h"

namespace apc
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

    Matrixf33 Transform::getMatrix() const
    {
        Matrixf33 result(1.0);

        if(m_parent)
        {
            result = m_parent->getMatrix();
        }

        result = Matrixf33::translate(result, m_position);

        result = Matrixf33::rotate(result, -m_rotation);

        result = Matrixf33::scale(result, m_scale);

        return result;
    }

    Matrixf33 Transform::getScaledMatrix() const
    {
        Matrixf33 result(1.0);

        if(m_parent)
        {
            result = m_parent->getScaledMatrix();
        }

        auto smallerSide = static_cast<float>( std::min(Context::getInstance().getScreenSize().x, Context::getInstance().getScreenSize().y) );
        auto biggerSide = static_cast<float>( std::max(Context::getInstance().getScreenSize().x, Context::getInstance().getScreenSize().y) );

        auto position = m_position / coord_cast<FCoord>( Context::getInstance().getScreenSize() );

        if( Context::getInstance().getScreenSize().x > Context::getInstance().getScreenSize().y )
        {
            position.y = position.y * (smallerSide/biggerSide);
        }
        else if( Context::getInstance().getScreenSize().x < Context::getInstance().getScreenSize().y )
        {
            position.x = position.x * (smallerSide/biggerSide);
        }

        result = Matrixf33::translate(result, position);

        result = Matrixf33::rotate(result, -m_rotation);

        result = Matrixf33::scale(result, m_scale);

        return result;
    }

    void Transform::screenSizeChanged(const ICoord& newSize)
    {
        
    }
}