#include "Movement.h"

namespace MOVEMENT
{
	CMovement::CMovement()
		: jumpspeed(0)
		, AnimationCounter(0)
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

	int CMovement::GetAnimationCounter()
	{
		return AnimationCounter;
	}

	int CMovement::GetJumpspeed()
	{
		return jumpspeed;
	}

	void CMovement::SetPos_X(int pos_X)
	{
		this->position.x = pos_X;
	}

	void CMovement::SetPos_Y(int pos_Y)
	{
		this->position.y = pos_Y;
	}

	void CMovement::SetAnimationCounter(int AnimationCounter)
	{
		this->AnimationCounter = AnimationCounter;
	}

	void CMovement::SetToJump(bool jump)
	{
		if (jump && !Drop && !InAir)
		{
			InAir = true;
			Drop = false;
			jumpspeed = 10;
		}
	}

	void CMovement::SetJumpspeed(int jumpspeed)
	{
		this->jumpspeed = jumpspeed;
	}

	void CMovement::SetAnimationInvert(bool AnimationInvert)
	{
		this->AnimationInvert = AnimationInvert;
	}

	bool CMovement::GetAnimationInvert()
	{
		return AnimationInvert;
	}

	void CMovement::UpdateJumpUpwards()
	{
		position.y -= jumpspeed;
		jumpspeed -= 1;
		if (jumpspeed == 0)
		{
			InAir = false;
			Drop = true;
		}
	}

	void CMovement::MoveLeftRight(const bool mode, const float timeDiff)
	{
		if (mode)
		{
			position.x = position.x - (int)(5.0f * timeDiff);
			AnimationInvert = true;
			AnimationCounter--;
			if (AnimationCounter < 0)
				AnimationCounter = 2;
		}
		else
		{
			position.x = position.x + (int)(5.0f * timeDiff);
			AnimationInvert = false;
			AnimationCounter++;
			if (AnimationCounter > 2)
				AnimationCounter = 0;
		}
	}

	CMovement* N_Character()
	{
		return new CMovement();
	}
}
