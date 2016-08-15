#include "Mob.h"

namespace Mob_AI
{


    Mob::Mob(float reactionDistance)
    {
        ReactDist = 0;
    }
    Mob::~Mob()
    {

    }

    void Mob::Init()
    {
        state = Spawn;

    }
    void Mob::update()
    {
        switch (state)
        {
        case Mob::Spawn:
            break;
        case Mob::Idle:
            break;
        case Mob::Attack:
            break;
        case Mob::Die:
            break;
        default:
            break;
        }
    }

}