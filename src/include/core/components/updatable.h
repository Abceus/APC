#pragma once
namespace APC
{
    class IUpdatable 
    {
    public:
        virtual void update(float dt) = 0;
    };
}