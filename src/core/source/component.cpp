#include "component.h"

namespace apc
{
    void Component::setSceneObject(SceneObject* object)
    {
        m_sceneObject = object;
    }

    SceneObject* Component::getSceneObject() const
    {
        return m_sceneObject;
    }

    bool Component::isEnabled() const
    {
        return m_enabled;
    }

    void Component::setEnabled(bool enabled)
    {
        m_enabled = enabled;
    }
}