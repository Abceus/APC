#pragma once

#include <functional>

#include "apc/coord.h"
#include "apc/component.h"
#include "apc/components/screen_sensative.h"
#include "apc/components/clickable.h"

namespace apc
{
    class ClickableArea : public Component, public IScreenSensative, public IClickable
    {
    public:        
        void setArea(ICoord area);

        void screenSizeChanged(const ICoord& newSize) override;

        void click( const ICoord& value ) override;

        void setCallback(const std::function<void()>& callback);
    private:
        ICoord m_area;
        ICoord m_halfArea;
        std::function<void()> m_callback;
    };
}