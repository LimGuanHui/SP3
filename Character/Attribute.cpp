#include "Attribute.h"

namespace ATTRIBUTE
{
	CAttribute::CAttribute() 
		: Damage(0)
		, MaxHealthPoint(100)
		, CurrentHealthPoint(MaxHealthPoint)
	{
	}


	CAttribute::~CAttribute()
	{
	}

	void CAttribute::SetMaxHP(int HP)
	{
		this->MaxHealthPoint = HP;
	}

	void CAttribute::SetDmg(int Dmg)
	{
		this->Damage = Dmg;
	}

	int CAttribute::GetMaxHP()
	{
		return MaxHealthPoint;
	}

	int CAttribute::GetCurrentHP()
	{
		return MaxHealthPoint;
	}

	int CAttribute::GetDmg()
	{
		return Damage;
	}
}

