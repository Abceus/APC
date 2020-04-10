#include <core/game.h>
#include <memory>

class TestGame : public APC::IGame
{
public:
    void init() override;
    void update( float dt ) override;
    void zoom( float delta ) override;
    void button( const APC::Coord& value ) override;
    void altButton( const APC::Coord& value ) override;
    void holdedMove( const APC::Coord &value ) override;
    void drag( const APC::Coord& value ) override;
    void drop( const APC::Coord &value ) override;
private:
    std::shared_ptr<APC::RenderNode> m_testNode;
    bool m_left;
};