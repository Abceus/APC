#include "core/transform.h"
#include "core/scene_object.h"
#include "core/clickable_area.h"


namespace APC
{       
    void ClickableArea::setArea(Coord area)
    {
        m_area = area;
        m_halfArea = { m_area.x/2, m_area.y/2 };
    }

    void ClickableArea::screenSizeChanged(const Coord& newSize)
    {
    }

    void ClickableArea::click( const Coord& value )
    {
        std::cout << value.x << " " << value.y << std::endl;
        if(!m_callback)
        {
            return;
        }

        auto transform = getSceneObject()->getComponent<Transform>();
        auto position = transform->getPosition();
        auto scale = transform->getScale();
        auto leftUpPoint = FCoord{ position.x - m_halfArea.x * scale.x, position.y - m_halfArea.y * scale.y };
        auto rightDownPoint = FCoord{ position.x + m_halfArea.x * scale.x, position.y + m_halfArea.y * scale.y };
        if( value.x >= leftUpPoint.x && value.x <= rightDownPoint.x && value.y >= leftUpPoint.y && value.y <= rightDownPoint.y )
        {
            m_callback();
        }
    }

    void ClickableArea::setCallback(const std::function<void()>& callback)
    {
        m_callback = callback;
    }
}