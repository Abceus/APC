#pragma once
#include "core/utility.h"
#include "core/drawable.h"
#include "core/transform.h"
#include <memory>


namespace APC
{
    class Position : public ITransform
    {
    public:
        Coord getPosition() const override;
        glm::mat4 getMatrix() const override;
        void setPosition(const Coord& position);
    private:
        Coord m_position;
    };

    class ScreenPosition : public ITransform
    {
    public:
        Coord getPosition() const override;
        glm::mat4 getMatrix() const override;
        void setPosition(const FCoord& position);
        void setScreenSize(const Coord& screenSize);
    private:
        FCoord m_position;
        Coord m_screenSize;
    };
}