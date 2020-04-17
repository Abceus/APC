#include "test_game.h"
#include "core/resource_manager.h"
#include "base/resources/gl_texture.h"
#include "base/scene.h"
#include "base/sprite.h"
#include "core/transform.h"
#include "core/clickable_area.h"
#include "core/scene_object.h"

#include "base/context.h"

#include "components/afro.h"

#include <memory>

APC::GameConfig TestGame::getGameConfig()
{
    APC::GameConfig gameConfig;
    gameConfig.width = 1024;
    gameConfig.height = 768;

    // gameConfig.width = 400;
    // gameConfig.height = 1024;

    // gameConfig.width = 692;
    // gameConfig.height = 700;

    // gameConfig.width = 1384;
    // gameConfig.height = 1400;
    gameConfig.gameName = "Test game";
    return gameConfig;
}

void TestGame::init()
{
    m_context->getSceneManager()->addScene("main", std::make_shared<APC::Scene>());
    m_context->getSceneManager()->changeScene("main");
    auto currentScene = m_context->getSceneManager()->getCurrentScene();
    currentScene->initLayers({"main"});

    auto texture = m_context->getResource<APC::GLTextureResource>( "Law-abidingAfricanAmerican.png" );

    auto newObject = std::make_shared<APC::SceneObject>();
    newObject->addComponent<APC::Transform>();
    auto context = static_cast<APC::Context*>(m_context);
    auto center = APC::FCoord { context->getScreenSize().x/2.0f, context->getScreenSize().y/2.0f };
    // newObject->getComponent<APC::Transform>()->setPosition({300.0f, 200.0f});
    newObject->getComponent<APC::Transform>()->setPosition(center);
    newObject->getComponent<APC::Transform>()->setScale(0.5f);
    newObject->addComponent<APC::Sprite>();
    newObject->getComponent<APC::Sprite>()->setTexture(texture);

    newObject->addComponent<Afro>();

    newObject->addComponent<APC::ClickableArea>();
    newObject->getComponent<APC::ClickableArea>()->setArea({ texture->getWidth(), texture->getHeight() });
    newObject->getComponent<APC::ClickableArea>()->setCallback([newObject]{ newObject->getComponent<Afro>()->changeColor(); });

    currentScene->addSceneObject(newObject, "main");




    // m_context->log( "Init" );
    // auto texture = m_context->getResource<APC::GLTextureResource>( "Law-abidingAfricanAmerican.png" );
    // auto sprite = std::make_shared<APC::Sprite>( texture );

    // m_testNode = std::make_shared<APC::RenderNode>();
    // m_testNode->getTypedPositionTransform<APC::TPosition>()->set({400, 0});
    // // m_testNode->getTypedRotationTransform<APC::Rotation>()->setRotation(90.0f);
    // m_testNode->getTypedScaleTransform<APC::TScale>()->set(0.4f);

    // auto parentNode = std::make_shared<APC::RenderNode>();
    // parentNode->getTypedPositionTransform<APC::TPosition>()->set({400, 300});
    // // parentNode->getTypedPositionTransform<APC::TPosition>()->set({0, 100});
    // parentNode->getTypedRotationTransform<APC::TRotation>()->set(45.0f);
    // m_testNode->setParent(parentNode);

    // sprite->setRenderNode(m_testNode);

    // // auto node = std::make_shared<APC::RenderNode>();
    // // node->getTypedTransform<APC::TScreenPosition>()->set({0.5f, 0.5f});
    // // sprite->setRenderNode(node);

    // m_context->getSceneManager()->addScene("main", std::make_shared<APC::Scene>());
    // m_context->getSceneManager()->changeScene("main");
    // m_context->getSceneManager()->getCurrentScene()->initLayers({"main"});
    // m_context->getSceneManager()->getCurrentScene()->addDrawable(sprite, "main");

    // m_left = false;
}

void TestGame::quit()
{
}

// void TestGame::update( float dt )
// {
    // {
    //     float speed = 50.0f; 
    //     auto rotationTransform = m_testNode->getTypedRotationTransform<APC::TRotation>();
    //     auto currentRotation = rotationTransform->get();
    //     rotationTransform->set(currentRotation + dt * speed);
    // }

    // {
    //     float speed = 200.0f;
    //     auto positionTransform = m_testNode->getTypedPositionTransform<APC::TPosition>();
    //     auto currentPosition = positionTransform->get();

    //     if(currentPosition.x >= 400 && !m_left)
    //     {
    //         m_left = true;
    //     }
    //     else if(currentPosition.x <= 50 && m_left)
    //     {
    //         m_left = false;
    //     }

    //     {
    //         auto colorTransform = m_testNode->getTypedColorTransform<APC::TColor>();
    //         auto currentColor = colorTransform->get();
    //         float colorSpeed = 0.5f;
    //         if(m_left)
    //         {
    //             m_left = true;
    //             positionTransform->set({currentPosition.x - dt * speed, 0});
    //             colorTransform->set({currentColor.r, currentColor.g, currentColor.b, currentColor.a - dt * colorSpeed});
    //         }
    //         else
    //         {
    //             m_left = false;
    //             positionTransform->set({currentPosition.x + dt * speed, 0});
    //             colorTransform->set({currentColor.r, currentColor.g, currentColor.b, currentColor.a + dt * colorSpeed});
    //         }
    //     }
    // }
// }

// void TestGame::zoom( float delta )
// {
//     m_context->log( "Zoom", delta );
// }

// void TestGame::button( const APC::Coord& value )
// {
//     m_context->log( "Button", value.x, value.y );
// }

// void TestGame::altButton( const APC::Coord& value )
// {
//     m_context->log( "Alt button", value.x, value.y );
// }

// void TestGame::holdedMove( const APC::Coord &value )
// {
//     m_context->log( "Holded move", value.x, value.y );
// }

// void TestGame::drag( const APC::Coord &value )
// {
//     m_context->log( "Drag", value.x, value.y );
// }

// void TestGame::drop( const APC::Coord &value )
// {
//     m_context->log( "Drop", value.x, value.y );
// }
