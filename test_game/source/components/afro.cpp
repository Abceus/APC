#include "components/afro.h"

#include "core/transform.h"
#include "core/scene_object.h"

#include <iostream>

void Afro::init() 
{
    m_state = 0;
    getSceneObject()->getComponent<APC::Transform>()->setColor({1.0f, 0.0f, 0.0f, 1.0f});
}

void Afro::update(float dt)
{
    // float speed = 90.0f;
    // auto transformComponent = getSceneObject()->getComponent<APC::Transform>();
    // auto currentRotation = transformComponent->getRotation();
    // transformComponent->setRotation(currentRotation + speed * dt);
}

void Afro::changeColor()
{
    m_state++;

    if(m_state == 1)
    {
        getSceneObject()->getComponent<APC::Transform>()->setColor({0.0f, 1.0f, 0.0f, 1.0f});
    }
    else if(m_state == 2)
    {
        getSceneObject()->getComponent<APC::Transform>()->setColor({0.0f, 0.0f, 1.0f, 1.0f});
    }
    else if(m_state == 3)
    {
        getSceneObject()->getComponent<APC::Transform>()->setColor({1.0f, 0.0f, 0.0f, 1.0f});
        m_state = 0;
    }
}