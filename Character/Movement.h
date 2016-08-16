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

		void SetPos_X(int pos_X);
		void SetPos_Y(int pos_Y);
		void SetAnimationCounter(int AnimationCounter);

		void SetToJump(bool jump);

		void MoveLeftRight(const bool mode, const float timeDiff);

	private:
		Vector3 position;

		bool OnGround;
		bool InAir;

		int AnimationCounter;
		int jumpspeed;
	};

	MOVEMENT_API CMovement* N_Character();
}


