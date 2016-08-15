#include "Mob.h"

MOB_AI::Mob::Mob(float reactionDistance)
{
    ReactDist = 0;
}
MOB_AI::Mob::~Mob()
{

}

void MOB_AI::Mob::Init()
{
    state = Spawn;
    
}
void MOB_AI::Mob::update()
{
    switch (state)
    {
    case MOB_AI::Mob::Spawn:
        break;
    case MOB_AI::Mob::Idle:
        break;
    case MOB_AI::Mob::Attack:
        break;
    case MOB_AI::Mob::Die:
        break;
    default:
        break;
    }
}