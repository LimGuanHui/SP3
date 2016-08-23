#pragma once

#include "MovementExport.h"
#include "Projectile.h"
using namespace PROJECTILE;
#include "Vector3.h"
#include <vector>

namespace MOVEMENT
{
	class MOVEMENT_API CMovement
	{
	public:
		CMovement();
		~CMovement();

		void Init();

		int GetPos_X();
		int GetPos_Y();
		int GetScale_X();
		int GetScale_Y();
		int GetVel_X();
		int GetVel_Y();
		int GetAnimationCounter();
		int GetJumpspeed(void);

		void SetPos_X(int pos_X);
		void SetPos_Y(int pos_Y);
		void SetScale_X(int scale_X);
		void SetScale_Y(int scale_Y);
		void SetVel_X(int vel_X);
		void SetVel_Y(int vel_Y);
		void SetAnimationCounter(int AnimationCounter);

		void SetToJump(bool jump);
		void SetJumpspeed(int jumpspeed);

		void MoveLeftRight(const bool mode, const float timeDiff);

		void UpdateJumpUpwards();

		void SetAnimationInvert(bool AnimationInvert);
		bool GetAnimationInvert();

		void AnimationUpdate(double dt);
		void ProjectileUpdate(const float timeDiff, double dt, int scale);

		PROJECTILE::Projectile* Projectile;
		PROJECTILE::Projectile* FetchProjectile();

		std::vector<PROJECTILE::Projectile *>m_projectileList;

		bool InAir;
		bool Drop;

	private:
		Vector3 position;
		Vector3 scale;
		Vector3 velocity;

		bool AnimationInvert;
		int AnimationCounter;
		int jumpspeed;

	};

}


