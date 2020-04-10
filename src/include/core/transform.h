#pragma once

#include "core/utility.h"
#include <glm/gtc/matrix_transform.hpp>

namespace APC
{
    class IPosition
    {
    public:
        virtual FCoord get() const = 0;
        virtual glm::mat4 getMatrix() const = 0;
    };

    class IRotation
    {
    public:
        virtual float get() const = 0;
        virtual glm::mat4 getMatrix() const = 0;
    };

    class IScale
    {
    public:
        virtual FCoord get() const = 0;
        virtual glm::mat4 getMatrix() const = 0;
    };

    class IColor
    {
    public:
        virtual Color get() const = 0;
    };
}