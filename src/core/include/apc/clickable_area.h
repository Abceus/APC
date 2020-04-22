#pragma once

#include <functional>

#include "apc/polygon.h"
#include "apc/component.h"
#include "apc/components/screen_sensative.h"
#include "apc/components/clickable.h"

namespace apc
{
    class ClickableArea : public Component, public IScreenSensative, public IClickable
    {
    public:        
        void setArea(const Polygon& area);

        void screenSizeChanged(const ICoord& newSize) override;

        void click( const ICoord& value ) override;

        void setCallback(const std::function<void()>& callback);
    private:
        Polygon m_area;
        std::function<void()> m_callback;
    };
}