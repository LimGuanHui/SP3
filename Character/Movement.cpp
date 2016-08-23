#include "Movement.h"

namespace MOVEMENT
{
    CMovement::CMovement()
        : jumpspeed(0)
        , AnimationCounter(0)
        , InAir(false)
        , velocity(5, 0, 0)
        , scale(6, 6, 1)
	{
		Projectile = new PROJECTILE::Projectile();
	}


	CMovement::~CMovement()
	{
	}

	void CMovement::Init()
	{
		position = Vector3(0, 0, 0);
		//scale = Vector3(10, 10, 1);
	}

	int CMovement::GetPos_X()
	{
		return position.x;
	}

	int CMovement::GetPos_Y()
	{
		return position.y;
	}

	int CMovement::GetScale_X()
	{
		return scale.x;
	}

	int CMovement::GetScale_Y()
	{
		return scale.y;
	}

	int CMovement::GetVel_X()
	{
		return velocity.x;
	}

	int CMovement::GetVel_Y()
	{
		return velocity.y;
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

	void CMovement::SetScale_X(int scale_X)
	{
		this->scale.x = scale_X;
	}

	void CMovement::SetScale_Y(int scale_Y)
	{
		this->scale.y = scale_Y;
	}

	void CMovement::SetVel_X(int vel_X)
	{
		this->velocity.x = vel_X;
	}

	void CMovement::SetVel_Y(int vel_Y)
	{
		this->velocity.y = vel_Y;
	}

	void CMovement::SetAnimationCounter(int AnimationCounter)
	{
		this->AnimationCounter = AnimationCounter;
	}

	void CMovement::SetToJump(bool jump)
	{
		if (jump && InAir == false && Drop == false)
		{
			InAir = true;
			Drop = false;
			jumpspeed = 4;
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

	void CMovement::MoveLeftRight(const bool mode, const float timeDiff)
	{
		if (mode)
		{
			position.x -= (velocity.x * timeDiff);
			AnimationInvert = true;
			AnimationCounter--;
			if (AnimationCounter < 0)
				AnimationCounter = 2;
		}
		else
		{
			position.x += (velocity.x * timeDiff);
			AnimationInvert = false;
			AnimationCounter++;
			if (AnimationCounter > 2)
				AnimationCounter = 0;
		}
	}

	void CMovement::AnimationUpdate(double dt) // Collision Check for Normal Stage
	{
		if (!InAir && !Drop)
		{
			//jumpspeed = 0;
			//InAir = false;
			//Drop = true;
		}

		else if (InAir && !Drop)//going up
		{
			position.y += jumpspeed;
			jumpspeed -= 1;
			if (jumpspeed < 0)
			{
				InAir = false;
				Drop = true;
			}
		}

		else if (!InAir & Drop)//falling
		{
            jumpspeed++;
			position.y -= jumpspeed;
		}
	}

	Projectile* CMovement::FetchProjectile()
	{
		for (std::vector<PROJECTILE::Projectile *>::iterator it = m_projectileList.begin(); it != m_projectileList.end(); ++it)
		{
			PROJECTILE::Projectile *projectile = (PROJECTILE::Projectile *)*it;
			std::vector<PROJECTILE::Projectile *>::iterator it2 = it;
			if (!projectile->active)
			{
				projectile->Init();
				projectile->active = true;

				return projectile;
			}
		}
		for (unsigned i = 0; i < 10; ++i)
		{
			PROJECTILE::Projectile *projectile = new PROJECTILE::Projectile();
			m_projectileList.push_back(projectile);
		}
		PROJECTILE::Projectile *projectile = m_projectileList.back();
		projectile->active = true;
		return projectile;
	}

	void CMovement::ProjectileUpdate(const float timeDiff, double dt, int scale)
	{
		
		if (AnimationInvert == false)
		{
			Projectile = FetchProjectile();
			Projectile->pos.Set(position.x, position.y, 10);
			Projectile->vel.Set(500, 0, 0);
			Projectile->scale.Set(scale, scale, scale);
		}
		else if (AnimationInvert == true)
		{
			Projectile = FetchProjectile();
			Projectile->pos.Set(position.x, position.y, 10);
			Projectile->vel.Set(-500, 0, 0);
			Projectile->scale.Set(scale, scale, scale);
		}
	}
}


