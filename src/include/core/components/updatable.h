#pragma once
namespace apc
{
    class IUpdatable 
    {
    public:
        virtual void update(float dt) = 0;
    };
}