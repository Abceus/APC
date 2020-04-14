#include "core/scene_object.h"


namespace APC
{
    void SceneObject::draw()
    {
        for(auto& drawable: m_drawables)
        {
            drawable->draw();
        }
    }

    void SceneObject::update(float dt)
    {
        for(auto& updatable: m_updatables)
        {
            updatable->update(dt);
        }
    }

    void SceneObject::click(const Coord& coord)
    {
        for(auto& clickable: m_clickables)
        {
            clickable->click(coord);
        }
    }
}