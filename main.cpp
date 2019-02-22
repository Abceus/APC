#include <iostream>
#include "core/game.h"
#include "base/context.h"
#include "base/gl_renderer.h"

class TestGame : public APC::IGame
{
public:
    void init() override
    {
        std::cout << "Init game" << std::endl;
    }
    void update( float dt ) override
    {
        std::cout << "Update game" << std::endl;
    }
    void zoom( float delta ) override
    {}
    void button( const APC::Coord& value ) override
    {}
};

int main()
{
    APC::Context::getInstance().init<APC::GLRenderer, TestGame>(100, 100);
    for(size_t i=0; i<1000; i++)
    {
        APC::Context::getInstance().update(1488.f);
        APC::Context::getInstance().draw();
    }
    return 0;
}