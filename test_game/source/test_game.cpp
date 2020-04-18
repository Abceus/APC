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

apc::GameConfig TestGame::getGameConfig()
{
    apc::GameConfig gameConfig;
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
    m_context->getSceneManager()->addScene("main", std::make_shared<apc::Scene>());
    m_context->getSceneManager()->changeScene("main");
    auto currentScene = m_context->getSceneManager()->getCurrentScene();
    currentScene->initLayers({"main"});

    auto texture = m_context->getResource<apc::GLTextureResource>( "Law-abidingAfricanAmerican.png" );

    auto newObject = std::make_shared<apc::SceneObject>();
    newObject->addComponent<apc::Transform>();
    auto context = static_cast<apc::Context*>(m_context);
    auto center = apc::FCoord { context->getScreenSize().x/2.0f, context->getScreenSize().y/2.0f };
    // newObject->getComponent<apc::Transform>()->setPosition({300.0f, 200.0f});
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
