
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
        float combinedRadiusSquared = (go->getscale().x + N_Character->Movement->GetScale_X()) * (go->getscale().x + N_Character->Movement->GetScale_X());
        if (distanceSquared < combinedRadiusSquared)
        {
            Response(go);
        }
    }
    /*for (std::vector<Projectile* >::iterator it = N_Character->Movement->m_projectileList.begin(); it != N_Character->Movement->m_projectileList.end(); ++it)
    {
        Projectile* go = (Projectile*)*it;
        float distanceSquared = Vector3(go->GetPos().x - N_Character->Movement->GetPos_X(), go->GetPos().y - N_Character->Movement->GetPos_Y(), 0.f).LengthSquared();
        if (distanceSquared < 20.f)
        {
            float combinedRadiusSquared = (go->scale.x + N_Character->Movement->GetScale_X()) * (go->scale.x + N_Character->Movement->GetScale_Y());
            if (distanceSquared < combinedRadiusSquared)
            {
                Response(go);
            }
        }
    }*/
	//int distanceApart = (N_Character->Movement->GetScale_Y() / 2) - (Platform->getscale().y / 2);
}

void Collision::Response(Platform* go)
{
    switch (go->type)
    {
    case Platform::Normal:
         N_Character->Movement->SetJumpspeed(0);
        N_Character->Movement->Drop = false;
        N_Character->Movement->SetPos_Y(go->getpos().y + go->getscale().y + 2.f);
        break;
    default:
        break;
    }
}

//void Collision::Response(Projectile* go)
//{
//    go->active = false;
//    N_Character->Attribute->SetCurrentHP(N_Character->Attribute->GetCurrentHP() - 10);
//}

Collision* CreateNewCollisionInstance()
{
    return new Collision();
}