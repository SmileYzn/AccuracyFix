#include "precompiled.h"

CAccuracyFixAttack gAccuracyFixAttack;

void CAccuracyFixAttack::PRE_CBasePlayer_PostThink(CBasePlayer* Player)
{
	if (Player->m_pActiveItem)
	{
		if (Player->m_pActiveItem->iItemSlot() == PRIMARY_WEAPON_SLOT || Player->m_pActiveItem->iItemSlot() == PISTOL_SLOT)
		{
			if (Player->pev->button & IN_ATTACK)
			{
				if (Player->CSPlayer()->m_bCanShootOverride || (Player->m_bCanShoot && g_pGameRules->IsMultiplayer() && !g_pGameRules->IsFreezePeriod() && !Player->m_bIsDefusing) || !g_pGameRules->IsMultiplayer())
				{
					CBasePlayerWeapon* Weapon = static_cast<CBasePlayerWeapon*>(Player->m_pActiveItem);

					if (Weapon)
					{
						switch (Player->m_pActiveItem->m_iId)
						{
							case WEAPON_AK47:
							{
								this->PRE_Attack_Weapon_AK47(Player, Weapon);
								break;
							}
							case WEAPON_M4A1:
							{
								this->PRE_Attack_Weapon_M4A1(Player, Weapon);
								break;
							}
						}
					}
				}
			}
		}
	}
}

void CAccuracyFixAttack::POST_CBasePlayer_PostThink(CBasePlayer* Player)
{
	if (Player->m_pActiveItem)
	{
		if (Player->m_pActiveItem->iItemSlot() == PRIMARY_WEAPON_SLOT || Player->m_pActiveItem->iItemSlot() == PISTOL_SLOT)
		{
			if (Player->pev->button & IN_ATTACK)
			{
				if (Player->CSPlayer()->m_bCanShootOverride || (Player->m_bCanShoot && g_pGameRules->IsMultiplayer() && !g_pGameRules->IsFreezePeriod() && !Player->m_bIsDefusing) || !g_pGameRules->IsMultiplayer())
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
}

void CAccuracyFixAttack::PRE_Attack_Weapon_AK47(CBasePlayer* Player, CBasePlayerWeapon* Weapon)
{
	int ShotsFired = (Weapon->m_iShotsFired - 1);

	if (ShotsFired >= 0)
	{
		auto EntityIndex = Player->entindex();

		this->m_flAccuracy[EntityIndex] = ((ShotsFired * ShotsFired * ShotsFired) / 200.0f) + 0.35f;

		if (this->m_flAccuracy[EntityIndex] > 1.25f)
		{
			this->m_flAccuracy[EntityIndex] = 1.25f;
		}

		Weapon->m_flAccuracy = this->m_flAccuracy[EntityIndex];
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
			Weapon->m_flAccuracy = 0.2f;
		}
	}
}

void CAccuracyFixAttack::PRE_Attack_Weapon_M4A1(CBasePlayer* Player, CBasePlayerWeapon* Weapon)
{
	int ShotsFired = (Weapon->m_iShotsFired - 1);

	if (ShotsFired >= 0)
	{
		auto EntityIndex = Player->entindex();

		this->m_flAccuracy[EntityIndex] = ((ShotsFired * ShotsFired * ShotsFired) / 220.0f) + 0.35f;

		if (this->m_flAccuracy[EntityIndex] > 1.25f)
		{
			this->m_flAccuracy[EntityIndex] = 1.25f;
		}

		Weapon->m_flAccuracy = this->m_flAccuracy[EntityIndex];
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
			Weapon->m_flAccuracy = 0.2f;
		}
	}
}