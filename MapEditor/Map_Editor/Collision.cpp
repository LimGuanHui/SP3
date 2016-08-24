
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

void Collision::CheckCollisionX()
{
    for (std::vector<Platform* >::iterator it = Map->Platform_List.begin(); it != Map->Platform_List.end(); ++it)
    {

        Platform* go = (Platform*)*it;
        //x check
        if ((abs(go->getpos().x - N_Character->Movement->GetPos_X()) * 2 < (go->getscale().x + N_Character->Movement->GetScale_X()) &&
            (abs(go->getpos().y - N_Character->Movement->GetPos_Y()) * 2 < (go->getscale().y + N_Character->Movement->GetScale_Y()))))
        {
            if (go->getpos().x < N_Character->Movement->GetPos_X())//left
            {
                Response_X(go, true);
                return;
            }
            else if (go->getpos().x > N_Character->Movement->GetPos_X())//right
            {
                Response_X(go, false);
                return;
            }
        }        
    }
    return;
}
bool Collision::CheckCollisionY()
{
    for (std::vector<Platform* >::iterator it = Map->Platform_List.begin(); it != Map->Platform_List.end(); ++it)
    {
        Platform* go = (Platform*)*it;
        //y check
        if (go->getpos().y < N_Character->Movement->GetPos_Y())
        {
            if ((abs(go->getpos().x - N_Character->Movement->GetPos_X()) * 2 < (go->getscale().x + N_Character->Movement->GetScale_X()) &&
                (abs(go->getpos().y - N_Character->Movement->GetPos_Y()) * 2 < (go->getscale().y + N_Character->Movement->GetScale_Y()))))
            {
                Response_Y(go, true);                
                return true;
            }
        }
        else if (go->getpos().y > N_Character->Movement->GetPos_Y())
        {
            if ((abs(go->getpos().x - N_Character->Movement->GetPos_X()) * 2 < (go->getscale().x + N_Character->Movement->GetScale_X()) &&
                (abs(go->getpos().y - N_Character->Movement->GetPos_Y()) * 2 < (go->getscale().y + N_Character->Movement->GetScale_Y()))))
            {
                Response_Y(go, false);                
                return true;
            }
        }
    }
    return false;
}

void Collision::CheckCollision()
{
    /*CheckCollisionX();
    if (!CheckCollisionY())
    {
        N_Character->Movement->setground(false);
        N_Character->Movement->jumpstate = N_Character->Movement->DROP;
    }*/
        //x check
       /* if (go->getpos().x < N_Character->Movement->GetPos_X())
        {
            if ((abs(go->getpos().x - N_Character->Movement->GetPos_X()) * 2 < (go->getscale().x + N_Character->Movement->GetScale_X())))
            {
                Response_X(go, true);
                return;
            }
        }
        else if (go->getpos().x > N_Character->Movement->GetPos_X())
        {
            if ((abs(go->getpos().x - N_Character->Movement->GetPos_X()) * 2 < (go->getscale().x + N_Character->Movement->GetScale_X())))
            {
                Response_X(go, false);
                return;
            }
        }*/
    
    
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

    Vector3(N_Character->Movement->GetPos_X(), N_Character->Movement->GetPos_Y(), 0);

}

void Collision::Response_X(Platform* go, bool left)
{
    switch (go->type)
    {
    case Platform::Normal:

        if (left)
        {
            if (N_Character->Movement->GetVel_X() < 0)
                N_Character->Movement->SetVel_X(0);
            
        }
        else
        {
            if (N_Character->Movement->GetVel_X() > 0)
                N_Character->Movement->SetVel_X(0);
        }
        break;
    default:
        break;
    }
}
void Collision::Response_Y(Platform* go, bool below)
{
    switch (go->type)
    {
    case Platform::Normal:

        if (below)
        {
            N_Character->Movement->setground(true);
            if (N_Character->Movement->jumpstate != N_Character->Movement->JUMP)
                N_Character->Movement->SetVel_Y(0);
            
            N_Character->Movement->jumpstate = N_Character->Movement->ONGROUND;
            N_Character->Movement->SetPos_Y(N_Character->Movement->GetPos_Y());
        }
        else
        {
            N_Character->Movement->SetVel_Y(0);
            N_Character->Movement->jumpstate = N_Character->Movement->DROP;
        }
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