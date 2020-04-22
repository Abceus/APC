#pragma once

#include <vector>

#include "coord.h"

namespace apc
{
    class Polygon
    {
    public:
        Polygon() = default;
        Polygon(std::vector<FCoord> points);

        bool inside(const FCoord& point) const;

        void setPoint(const std::vector<FCoord>& points);
        std::vector<FCoord> getPoints() const;

        static Polygon makeCirle(float radius, size_t amount);
        static Polygon makeSquade(const FCoord& leftUp, const FCoord& rightDown);
        static Polygon getTransformed(const Polygon& polygon, const Matrixf33& matrix);
    private:
        std::vector<FCoord> m_points;
    };
}