#include "test_game.h"
#include "core/resource_manager.h"
#include "base/resources/gl_texture.h"

void TestGame::init()
{
    m_context->log( "Init" );
    auto texture = m_context->getResource<APC::GLTextureResource>( "Law-abidingAfricanAmerican.png" );
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
    m_context->log( "Button", value.x, value.y );
}

void TestGame::altButton( const APC::Coord& value )
{
    m_context->log( "Alt button", value.x, value.y );
}

void TestGame::holdedMove( const APC::Coord &value )
{
    m_context->log( "Holded move", value.x, value.y );
}

void TestGame::drag( const APC::Coord &value )
{
    m_context->log( "Drag", value.x, value.y );
}

void TestGame::drop( const APC::Coord &value )
{
    m_context->log( "Drop", value.x, value.y );
}
