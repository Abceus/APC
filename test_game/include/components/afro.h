#include <core/component.h>
#include <core/components/updatable.h>

class Afro : public APC::Component, public APC::IUpdatable
{
public:
    void init() override;
    void update(float dt) override;
    void changeColor();
private:
    int m_state;
};