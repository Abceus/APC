#include "test_game.h"
#include "core/resource_manager.h"
#include "base/resources/gl_texture.h"
#include "base/scene.h"
#include "base/sprite.h"
#include "core/render_node.h"

void TestGame::init()
{
    m_context->log( "Init" );
    auto texture = m_context->getResource<APC::GLTextureResource>( "Law-abidingAfricanAmerican.png" );
    auto sprite = std::make_shared<APC::Sprite>( texture );

    auto node = std::make_shared<APC::RenderNode>();
    node->getTypedTransform<APC::Position>()->setPosition({400, 300});
    auto parentNode = std::make_shared<APC::RenderNode>();
    parentNode->getTypedTransform<APC::Position>()->setPosition({0, 100});
    node->setParent(parentNode);
    sprite->setRenderNode(node);

    // auto node = std::make_shared<APC::RenderNode>();
    // node->getTypedTransform<APC::ScreenPosition>()->setPosition({0.5f, 0.5f});
    // sprite->setRenderNode(node);

    m_context->getSceneManager()->addScene("main", std::make_shared<APC::Scene>());
    m_context->getSceneManager()->changeScene("main");
    m_context->getSceneManager()->getCurrentScene()->initLayers({"main"});
    m_context->getSceneManager()->getCurrentScene()->addDrawable(sprite, "main");
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
