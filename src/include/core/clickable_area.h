#pragma once

#include <functional>

#include "core/utility.h"
#include "core/component.h"
#include "core/components/screen_sensative.h"
#include "core/components/clickable.h"

namespace APC
{
    class ClickableArea : public Component, public IScreenSensative, public IClickable
    {
    public:        
        void setArea(Coord area);

        void screenSizeChanged(const Coord& newSize) override;

        void click( const Coord& value ) override;

        void setCallback(const std::function<void()>& callback);
    private:
        Coord m_area;
        Coord m_halfArea;
        std::function<void()> m_callback;
    };
}