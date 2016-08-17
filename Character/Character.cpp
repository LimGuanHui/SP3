#include "Character.h"

namespace CHARACTER
{
	CCharacter::CCharacter()
	{
		Movement = new MOVEMENT::CMovement();
		Skill = new SKILLS::CSkills();
		Attribute = new ATTRIBUTE::CAttribute();

//		Attribute->SetMaxHP(100);
	}

	CCharacter::~CCharacter()
	{
	}

	CCharacter* N_Character()
	{
		return new CCharacter();
	}
}
