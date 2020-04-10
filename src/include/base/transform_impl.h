#pragma once
#include "core/utility.h"
#include "core/drawable.h"
#include "core/transform.h"
#include <memory>


namespace APC
{
    class TPosition : public IPosition
    {
    public:
        FCoord get() const override;
        glm::mat4 getMatrix() const override;
        void set(const FCoord& position);
    private:
        FCoord m_position;
    };

    class TScreenPosition : public IPosition
    {
    public:
        FCoord get() const override;
        glm::mat4 getMatrix() const override;
        void set(const FCoord& position);
        void setScreenSize(const Coord& screenSize);
    private:
        FCoord m_position;
        Coord m_screenSize;
    };

    class TRotation : public IRotation
    {
    public:
        float get() const override;
        glm::mat4 getMatrix() const override;
        void set(float rotation);
    private:
        float m_rotation;
    };

    class TScale : public IScale
    {
    public:
        FCoord get() const override;
        glm::mat4 getMatrix() const override;
        void set(const FCoord& scale);
        void set(float scale);
    private:
        FCoord m_scale;
    };

    class TColor : public IColor
    {
    public:
        Color get() const override;
        void set(Color rotation);
    private:
        Color m_color;
    };
}