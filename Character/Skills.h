#pragma once

#include "SkillsExport.h"
#include "Attribute.h"

namespace SKILLS
{
	class SKILLS_API CSkills
	{

		enum SKILLS
		{
			HEALING,
		};


	public:
		CSkills();
		~CSkills();

		void SetSkill(int Skillnum);
		int GetSkill();

		void SkillEffect(int SkillEffect);
		int GetSkillEffect();

		void SetSkillGuageC(int SGCap);
		void SetRefillspd(int SGSpeed);

		int GetSkillGuage();
		int GetRefillspd();

		ATTRIBUTE::CAttribute *Attribute;

	private:
		int skillnum;
		int skilleffect;
		int SkillGuageC;
		int SkillCharge;

		

	};

}

