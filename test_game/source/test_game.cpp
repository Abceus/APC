#include "test_game.h"
#include "apc/resource_manager.h"
#include "apc/opengl/resources/gl_texture.h"
#include "apc/opengl/scene.h"
#include "apc/opengl/sprite.h"
#include "apc/transform.h"
#include "apc/clickable_area.h"
#include "apc/scene_object.h"

#include "apc/context.h"

#include "components/afro.h"

#include <memory>

apc::GameConfig TestGame::getGameConfig()
{
    apc::GameConfig gameConfig;
    gameConfig.width = 1024;
    gameConfig.height = 768;

    gameConfig.gameName = "Test game";
    return gameConfig;
}

void TestGame::init()
{
    m_context->getSceneManager()->addScene("main", std::make_shared<apc::Scene>());
    m_context->getSceneManager()->changeScene("main");
    auto currentScene = m_context->getSceneManager()->getCurrentScene();
    currentScene->initLayers({"main"});

    auto texture = m_context->getResource<apc::GLTextureResource>( "Law-abidingAfricanAmerican.png" );

    auto newObject = std::make_shared<apc::SceneObject>();
    newObject->addComponent<apc::Transform>();
    auto context = static_cast<apc::Context*>(m_context);
    auto center = apc::coord_cast<apc::FCoord>(context->getScreenSize())/2.0f;
    newObject->getComponent<apc::Transform>()->setPosition(center);
    newObject->getComponent<apc::Transform>()->setScale(0.5f);
    newObject->addComponent<apc::Sprite>();
    newObject->getComponent<apc::Sprite>()->setTexture(texture);

    newObject->addComponent<Afro>();

    newObject->addComponent<apc::ClickableArea>();
    newObject->getComponent<apc::ClickableArea>()->setArea({ texture->getWidth(), texture->getHeight() });
    newObject->getComponent<apc::ClickableArea>()->setCallback([newObject]{ newObject->getComponent<Afro>()->changeColor(); });

    currentScene->addSceneObject(newObject, "main");
}

void TestGame::quit()
{
}
