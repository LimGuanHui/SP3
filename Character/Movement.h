#pragma once

#include "MovementExport.h"
#include "Vector3.h"

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
		int GetAnimationCounter();
		int GetJumpspeed(void);

		void SetPos_X(int pos_X);
		void SetPos_Y(int pos_Y);
		void SetAnimationCounter(int AnimationCounter);

		void SetToJump(bool jump);
		void SetJumpspeed(int jumpspeed);

		void MoveLeftRight(const bool mode, const float timeDiff);

		void UpdateJumpUpwards();

		void SetAnimationInvert(bool AnimationInvert);

		bool GetAnimationInvert();

	private:
		Vector3 position;

		bool OnGround;
		bool InAir;
		bool Drop;

		bool AnimationInvert;
		int AnimationCounter;
		int jumpspeed;
	};

	MOVEMENT_API CMovement* N_Character();
}


