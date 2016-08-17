#pragma once

#include "CharacterExports.h"
#include "Movement.h"
#include "Skills.h"

namespace CHARACTER
{
	class CHARACTER_API CCharacter
	{
	public:
		CCharacter();
		~CCharacter();
		
		ATTRIBUTE::CAttribute *Attribute;
		MOVEMENT::CMovement *Movement;
		SKILLS::CSkills *Skill;
		
	private:
	

	};

	CHARACTER_API CCharacter* N_Character();
}


