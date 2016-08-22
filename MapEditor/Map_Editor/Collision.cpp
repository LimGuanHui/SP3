
#include "Collision.h"


Collision::Collision()
{
	//N_Character = new CHARACTER::CCharacter();
	//Map = new Map_Editor();
	//Platform = new Platform();
}


Collision::~Collision()
{
}

void Collision::Init(CHARACTER::CCharacter* C_CHARACTER, Map_Editor* map)
{
	//Platform->type = Platform::PLATFORM_TYPE::Normal;
    N_Character = C_CHARACTER;
    Map = map;
}

void Collision::CheckCollision()
{
    for (std::vector<Platform* >::iterator it = Map->Platform_List.begin(); it != Map->Platform_List.end(); ++it)
    {
        Platform* go = (Platform*)*it;
        float distanceSquared = Vector3(go->getpos().x - N_Character->Movement->GetPos_X(), go->getpos().y - N_Character->Movement->GetPos_Y(), 0.f).LengthSquared();
        float combinedRadiusSquared = (go->getscale().x + N_Character->Movement->GetScale_X()) * (go->getscale().x + N_Character->Movement->GetScale_Y());
        if (distanceSquared < combinedRadiusSquared)
        {
            Response(go);
        }
    }
	//int distanceApart = (N_Character->Movement->GetScale_Y() / 2) - (Platform->getscale().y / 2);
}

void Collision::Response(Platform* go)
{
    switch (go->type)
    {
    case Platform::Normal:
        //N_Character->Movement->
        break;
    default:
        break;
    }
}