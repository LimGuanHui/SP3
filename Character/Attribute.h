#pragma once

#include "AttributeExports.h"

namespace ATTRIBUTE
{
	class ATTRIBUTE_API CAttribute
	{
	public:
		CAttribute();
		~CAttribute();


		void SetMaxHP(int HP);
		void SetDmg(int Dmg);

		int GetMaxHP();
		int GetCurrentHP();
		int GetDmg();

	private:
		int Damage;
		int MaxHealthPoint;
		int CurrentHealthPoint;
	};
}


