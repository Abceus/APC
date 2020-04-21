#include "components/afro.h"

#include "apc/transform.h"
#include "apc/scene_object.h"

#include <iostream>

void Afro::init() 
{
    m_state = 0;
    getSceneObject()->getComponent<apc::Transform>()->setColor({0.75f, 0.25f, 0.25f, 1.0f});
}

void Afro::update(float dt)
{
    float speed = 35.0f;
    auto transformComponent = getSceneObject()->getComponent<apc::Transform>();
    auto currentRotation = transformComponent->getRotation();
    transformComponent->setRotation(currentRotation + speed * dt);
}

void Afro::changeColor()
{
    m_state++;

    if(m_state == 1)
    {
        getSceneObject()->getComponent<apc::Transform>()->setColor({0.25f, 0.75f, 0.25f, 1.0f});
    }
    else if(m_state == 2)
    {
        getSceneObject()->getComponent<apc::Transform>()->setColor({0.25f, 0.25f, 0.75f, 1.0f});
    }
    else if(m_state == 3)
    {
        getSceneObject()->getComponent<apc::Transform>()->setColor({0.75f, 0.25f, 0.25f, 1.0f});
        m_state = 0;
    }
}