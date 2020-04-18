#include <core/game.h>
#include <core/game_config.h>
#include <memory>

class TestGame : public apc::IGame
{
public:
    void init() override;
    void quit() override;

    static apc::GameConfig getGameConfig();
private:
    // std::shared_ptr<apc::RenderNode> m_testNode;
    bool m_left;
};