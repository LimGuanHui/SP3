#include "Movement.h"

namespace MOVEMENT
{
	CMovement::CMovement()
		: jumpspeed(0)
		, OnGround(true)
		, InAir(false)
	{
	}


	CMovement::~CMovement()
	{
	}

	void CMovement::Init()
	{
		position = Vector3(0, 0, 0);
	}

	int CMovement::GetPos_X()
	{
		return position.x;
	}

	int CMovement::GetPos_Y()
	{
		return position.y;
	}

	void CMovement::SetPos_X(int pos_X)
	{
		this->position.x = pos_X;
	}

	void CMovement::SetPos_Y(int pos_Y)
	{
		this->position.y = pos_Y;
	}

	void CMovement::SetToJump(bool jump)
	{
		if (jump && OnGround && !InAir)
		{
			OnGround = false;
			InAir = true;
			jumpspeed = 10;
		}
	}

	void CMovement::MoveLeftRight(const bool mode, const float timeDiff)
	{
		if (mode)
		{
			position.x = position.x + (int)(5.0f * timeDiff);
		}
		else
		{
			position.x = position.x - (int)(5.0f * timeDiff);
		}
	}

	CMovement* N_Character()
	{
		return new CMovement();
	}
}
