#pragma once

#include "core/utility.h"
#include <glm/gtc/matrix_transform.hpp>

namespace APC
{
    class ITransform
    {
    public:
        virtual Coord getPosition() const = 0;
        virtual glm::mat4 getMatrix() const = 0;
    };
}