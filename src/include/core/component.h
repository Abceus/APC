#pragma once

namespace APC
{
    class SceneObject;
    class Component
    {
    public:
        void setSceneObject(SceneObject* object);
        SceneObject* getSceneObject() const;
        bool isEnabled() const;
        void setEnabled(bool enabled);
        virtual void init(){};
    private:
        SceneObject* m_sceneObject;
        bool m_enabled;
    };
} 