#include "scene_object.h"


namespace apc
{
    SceneObject::SceneObject( const std::string& layer )
        : m_layer( layer )
    {

    }

    void SceneObject::setLayer( const std::string& layer )
    {
        m_layer = layer;
    }

    std::string SceneObject::getLayer() const
    {
        return m_layer;
    }

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