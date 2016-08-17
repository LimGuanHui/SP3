#include "Skills.h"

namespace SKILLS
{
	CSkills::CSkills(){

		Attribute = new ATTRIBUTE::CAttribute();
	}


	CSkills::~CSkills(){}

	void CSkills::SetSkill(int Skillnum)
	{
		this->skillnum = Skillnum;
	}

	int CSkills::GetSkill()
	{
		return skillnum;
	}

	void CSkills::SkillEffect(int SkillEffect)
	{
		switch (SkillEffect)
		{
		case HEALING:
			break;
		}
	}

	void CSkills::SetSkillGuageC(int SGCap)
	{
		this->SkillGuageC = SGCap;
	}

	void CSkills::SetRefillspd(int SGSpeed)
	{
		this->SkillCharge = SGSpeed;
	}

	int CSkills::GetSkillGuage()
	{
		return SkillGuageC;
	}

	int CSkills::GetRefillspd()
	{
		return SkillCharge;
	}
}

