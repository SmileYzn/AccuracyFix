#include "precompiled.h"

CAccuracyFix gAccuracyFix;

void CAccuracyFix::PRE_UpdateClientData(CBasePlayer* Player)
{
	if (Player->m_pActiveItem)
	{
		if (Player->pev->button & IN_ATTACK)
		{
			auto Weapon = static_cast<CBasePlayerWeapon*>(Player->m_pActiveItem);

			if (Weapon)
			{
				switch (Player->m_pActiveItem->m_iId)
				{
					case WEAPON_AK47:
					{
						this->PRE_Weapon_AK47(Player, Weapon);
						break;
					}
				}
			}
		}
	}
}

void CAccuracyFix::POST_UpdateClientData(CBasePlayer* Player)
{
	if (Player->m_pActiveItem)
	{
		if (Player->pev->button & IN_ATTACK)
		{
			auto Weapon = static_cast<CBasePlayerWeapon*>(Player->m_pActiveItem);

			if (Weapon)
			{
				switch (Player->m_pActiveItem->m_iId)
				{
					case WEAPON_AK47:
					{
						break;
					}
				}
			}
		}
	}
}

void CAccuracyFix::PRE_Weapon_AK47(CBasePlayer* Player, CBasePlayerWeapon* Weapon)
{
	static int ShotsFired;

	ShotsFired = Weapon->m_iShotsFired + 1;

	if (ShotsFired > 1)
	{
		this->m_fAccuracy = ((ShotsFired * ShotsFired * ShotsFired) / 200.0) + 0.35;

		if (this->m_fAccuracy > 1.25)
		{
			this->m_fAccuracy = 1.25;
		}

		Weapon->m_flAccuracy = this->m_fAccuracy;
	}
	else
	{
		if (Player->pev->flags & FL_ONGROUND)
		{
			if (!Player->pev->velocity[0] && !Player->pev->velocity[1])
			{
				if (Player->pev->flags & FL_DUCKING)
				{
					Weapon->m_flAccuracy = 0.0f;
				}
				else
				{
					Weapon->m_flAccuracy = 0.1f;
				}
			}
			else
			{
				Weapon->m_flAccuracy = 0.2f;
			}
		}
		else
		{
			Weapon->m_flAccuracy = 0.1f;
		}
	}
}
