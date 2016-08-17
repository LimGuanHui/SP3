#pragma once

#include "SkillsExport.h"
#include "Attribute.h"
#include <string>

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

		void SetSkillName(std::string Name);
		std::string GetSkillName();

		void SetSkillEffect(int SkillEffect);
		int GetSkillEffect();

		void SetSkillInfo(std::string Info);
		std::string GetSkillInfo();

		void SetSkillGuageC(int SkillGuageC);
		void SetRefillspd(int SkillCharge);

		int GetSkillGuage();
		int GetRefillspd();

		ATTRIBUTE::CAttribute *Attribute;

	private:

		int SkillEffect;

		int SkillGuageC;
		int SkillCharge;

		

	};

}

