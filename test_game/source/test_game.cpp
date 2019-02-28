#include "test_game.h"
#include "base/resource_manager.h"

void TestGame::init()
{
    m_context->log( "Init" );
    auto rm = APC::ResourceManager<int>();
    auto a = rm.getResource( "testa" );
    {
        auto b = rm.getResource( "testb" );
        auto c = rm.getResource( "testc" );
    }
    auto d = rm.getResource( "testd" );
}

void TestGame::update( float dt )
{
//    m_context->log( "Update", dt );
}

void TestGame::zoom( float delta )
{
    m_context->log( "Zoom", delta );
}

void TestGame::button( const APC::Coord& value )
{
    m_context->log( "Button", value.x, " ", value.y );
}

void TestGame::altButton( const APC::Coord& value )
{
    m_context->log( "Alt button", value.x, " ", value.y );
}

void TestGame::holdedMove( const APC::Coord &value )
{
    m_context->log( "Holded move", value.x, " ", value.y );
}

void TestGame::drag( const APC::Coord &value )
{
    m_context->log( "Drag", value.x, " ", value.y );
}

void TestGame::drop( const APC::Coord &value )
{
    m_context->log( "Drop", value.x, " ", value.y );
}
