
#include "Collision.h"


Collision::Collision()
{
	N_Character = new CHARACTER::CCharacter();
	Map = new Map_Editor();
	//Platform = new Platform();
}


Collision::~Collision()
{
}

void Collision::Init()
{
	Platform->type = Platform::PLATFORM_TYPE::Normal;
}

void Collision::CheckCollision()
{
	int distanceApart = (N_Character->Movement->GetScale_Y() / 2) - (Platform->getscale().y / 2);
}
