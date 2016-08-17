#include "BossMovement.h"

namespace BOSS_MOVEMENT
{
	BMovement::BMovement()
	{
	}

	BMovement::~BMovement()
	{
	}

	void BMovement::Init()
	{
		position = Vector3(0, 0, 0);
	}

	int BMovement::GetPos_X()
	{
		return position.x;
	}

	int BMovement::GetPos_Y()
	{
		return position.y;
	}

	void BMovement::SetPos_X(int pos_X)
	{
		this->position.x = pos_X;
	}

	void BMovement::SetPos_Y(int pos_Y)
	{
		this->position.y = pos_Y;
	}

	BMovement* N_Boss()
	{
		return new BMovement();
	}
}