#include "polygon.h"

#include <cmath>
#include <limits>

#include "math_utils.h"
#include "line.h"
#include "coord.h"

namespace apc
{
    Polygon::Polygon(std::vector<FCoord> points)
        : m_points(std::move(points))
    {

    }

    bool Polygon::inside(const FCoord& point) const
    {
        if(m_points.size() < 3)
        {
            return false;
        }

        FCoord extreme { 1000000.0f, point.y };

        int count = 0, i = 0;

        do
        {
            int next = (i+1)%m_points.size();

            if( FLine::isIntersected( { m_points[i], m_points[next] }, { point, extreme } ) )
            { 
                if( FLine::linesOrientation( m_points[i], point, m_points[next] ) == Orientation::Collinear )
                {
                    return FLine::insideSquade( {m_points[i], m_points[next]}, point );
                }
    
                count++; 
            } 
            i = next; 
        } while (i != 0);

        return count&1;
    }

    void Polygon::setPoint(const std::vector<FCoord>& points)
    {
        m_points = points;
    }
    
    std::vector<FCoord> Polygon::getPoints() const
    {
        return m_points;
    }

    Polygon Polygon::makeCirle(float radius, size_t amount)
    {
        std::vector<FCoord> points;
        auto delta = 360.0f / amount;

        auto angle = 0.0f;

        for(size_t i = 0; i < amount; ++i)
        {
            auto r_angle = radians(angle);
            points.emplace_back(FCoord{ std::cos(r_angle)*radius, std::sin(r_angle)*radius});
            angle += delta;
        }
        return Polygon(points);
    }

    Polygon Polygon::makeSquade(const FCoord& leftUp, const FCoord& rightDown)
    {
        return Polygon( std::vector<FCoord>( { rightDown, FCoord{ rightDown.x, leftUp.y }, leftUp, FCoord{ leftUp.x, rightDown.y } } ) );
    }

    Polygon Polygon::getTransformed(const Polygon& polygon, const Matrixf33& matrix)
    {
        auto points = polygon.getPoints();

        for(size_t i = 0; i < points.size(); i++)
        {
            points[i] = FCoord::getTransformed(points[i], matrix);
        }

        return Polygon(points);
    }
}