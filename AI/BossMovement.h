#pragma once

#include "BossMovementExports.h"
#include "Vector3.h"

namespace BOSS_MOVEMENT
{
	class BOSS_MOVEMENT_API BMovement
	{
	public:
		BMovement();
		~BMovement();

		void Init();

		int GetPos_X();
		int GetPos_Y();

		void SetPos_X(int pos_X);
		void SetPos_Y(int pos_Y);

	private:
		Vector3 position;
	};

	BOSS_MOVEMENT_API BMovement* N_Boss();
}