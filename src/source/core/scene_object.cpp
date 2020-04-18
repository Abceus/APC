#include "core/scene_object.h"


namespace apc
{
    // void SceneObject::draw()
    // {
    //     for(auto& drawable: m_drawables)
    //     {
    //         drawable->draw();
    //     }
    // }

    std::vector<std::shared_ptr<IDrawable>> SceneObject::getDrawables() const
    {
        return m_drawables;
    }

    void SceneObject::update(float dt)
    {
        for(auto& updatable: m_updatables)
        {
            updatable->update(dt);
        }
    }

    void SceneObject::click(const ICoord& coord)
    {
        for(auto& clickable: m_clickables)
        {
            clickable->click(coord);
        }
    }
}