#include "test_game.h"

void TestGame::init()
{
    m_context->log( "Init" );
}

void TestGame::update( float dt )
{
    m_context->log( "Update", dt );
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
