#include "transform.h"
#include "scene_object.h"
#include "clickable_area.h"
#include "context.h"


namespace apc
{       
    void ClickableArea::setArea(const Polygon& area)
    {
        m_area = area;
    }

    void ClickableArea::screenSizeChanged(const ICoord& newSize)
    {
    }

    void ClickableArea::click( const ICoord& value )
    {
        if(!m_callback)
        {
            return;
        }

        auto transform = getSceneObject()->getComponent<Transform>();

        auto transformedPolygon = Polygon::getTransformed(m_area, transform->getMatrix());

        if( transformedPolygon.inside( coord_cast<FCoord>( value ) ) )
        {
            m_callback();
        }
    }

    void ClickableArea::setCallback(const std::function<void()>& callback)
    {
        m_callback = callback;
    }
}