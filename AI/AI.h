#pragma once

#include "AIExports.h"
#include "BossMovement.h"
#include "MonsterMovement.h"

namespace AI
{
	class AI_API CAI
	{
	public:
		CAI();
		~CAI();

		BOSS_MOVEMENT::BMovement Boss;
		MONSTER_MOVEMENT::MMovement Monster;
		
	private:
		
	};


}


