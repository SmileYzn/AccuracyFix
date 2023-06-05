#include "precompiled.h"

CAccuracyFixPunch gAccuracyFixPunch;

void CAccuracyFixPunch::PRE_CBasePlayer_PostThink(CBasePlayer* Player)
{
	if (Player->m_pActiveItem)
	{
		if (Player->m_pActiveItem->iItemSlot() == PRIMARY_WEAPON_SLOT || Player->m_pActiveItem->iItemSlot() == PISTOL_SLOT)
		{
			if (Player->pev->button & IN_ATTACK)
			{
				if (Player->CSPlayer()->m_bCanShootOverride || (Player->m_bCanShoot && g_pGameRules->IsMultiplayer() && !g_pGameRules->IsFreezePeriod() && !Player->m_bIsDefusing) || !g_pGameRules->IsMultiplayer())
				{
					if (gAccuracyFix.m_AF_PunchControl[Player->m_pActiveItem->m_iId]->value >= 0.0f)
					{
						this->m_vecPunchAngle[Player->entindex()] = Player->edict()->v.punchangle;
					}
				}
			}
		}
	}
}

void CAccuracyFixPunch::POST_CBasePlayer_PostThink(CBasePlayer* Player)
{
	if (Player->m_pActiveItem)
	{
		if (Player->m_pActiveItem->iItemSlot() == PRIMARY_WEAPON_SLOT || Player->m_pActiveItem->iItemSlot() == PISTOL_SLOT)
		{
			if (Player->pev->button & IN_ATTACK)
			{
				if (Player->CSPlayer()->m_bCanShootOverride || (Player->m_bCanShoot && g_pGameRules->IsMultiplayer() && !g_pGameRules->IsFreezePeriod() && !Player->m_bIsDefusing) || !g_pGameRules->IsMultiplayer())
				{
					if (gAccuracyFix.m_AF_PunchControl[Player->m_pActiveItem->m_iId]->value >= 0.0f)
					{
						auto PunchAngle = Player->edict()->v.punchangle;

						PunchAngle = PunchAngle - this->m_vecPunchAngle[Player->entindex()];

						PunchAngle = PunchAngle * gAccuracyFix.m_AF_PunchControl[Player->m_pActiveItem->m_iId]->value;

						PunchAngle = PunchAngle + this->m_vecPunchAngle[Player->entindex()];

						Player->edict()->v.punchangle = PunchAngle;
					}
				}
			}
		}
	}
}
