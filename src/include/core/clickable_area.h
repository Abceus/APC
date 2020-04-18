#pragma once

#include <functional>

#include "core/coord.h"
#include "core/component.h"
#include "core/components/screen_sensative.h"
#include "core/components/clickable.h"

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