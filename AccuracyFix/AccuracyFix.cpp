#include "precompiled.h"

CAccuracyFix gAccuracyFix;

void CAccuracyFix::ServerActivate()
{
	memset(this->m_Shooting, false, sizeof(m_Shooting));
}

bool CAccuracyFix::TraceLine(const float* start, const float* end, int fNoMonsters, edict_t* pentToSkip, TraceResult* ptr)
{
	auto Player = UTIL_PlayerByIndexSafe(ENTINDEX(pentToSkip));

	if (Player)
	{
		if (fNoMonsters == dont_ignore_monsters)
		{
			if (Player->m_pActiveItem)
			{
				if (!((BIT(WEAPON_NONE) | BIT(WEAPON_HEGRENADE) | BIT(WEAPON_XM1014) | BIT(WEAPON_C4) | BIT(WEAPON_SMOKEGRENADE) | BIT(WEAPON_M3) | BIT(WEAPON_FLASHBANG) | BIT(WEAPON_KNIFE)) & BIT(Player->m_pActiveItem->m_iId)))
				{
					CBasePlayerWeapon* Weapon = static_cast<CBasePlayerWeapon*>(Player->m_pActiveItem);

					if (Weapon)
					{
						if ((Player->edict()->v.button & IN_ATTACK) && (Weapon->m_iShotsFired >= 0 && Weapon->m_iShotsFired <= 2) && (Weapon->m_flNextPrimaryAttack < 0.0f))
						{
							if (Weapon->m_iShotsFired > 0 && Weapon->m_iShotsFired <= 2)
							{
								this->m_Shooting[Player->entindex()] = true;
							}

							vec3_t vEnd;

							g_engfuncs.pfnMakeVectors(pentToSkip->v.v_angle);

							vEnd = gpGlobals->v_forward * 9999.0f;

							vEnd[0] = start[0] + vEnd[0];

							vEnd[1] = start[1] + vEnd[1];

							vEnd[2] = start[2] + vEnd[2];

							g_engfuncs.pfnTraceLine(start, vEnd, fNoMonsters, pentToSkip, ptr);

							return true;
						}
					}
				}
			}
		}
	}

	return false;
}

void CAccuracyFix::PostThink(CBasePlayer* Player)
{
	if (Player->IsAlive() && Player->IsPlayer() && !Player->IsBot())
	{
		if (Player->m_pActiveItem)
		{
			CBasePlayerWeapon* Weapon = static_cast<CBasePlayerWeapon*>(Player->m_pActiveItem);

			if (Weapon)
			{
				auto EntityIndex = Player->entindex();

				if (this->m_Shooting[EntityIndex])
				{
					this->m_Shooting[EntityIndex] = false;

					auto PunchAngle = Player->edict()->v.punchangle;

					PunchAngle = PunchAngle * Weapon->m_flAccuracy;

					Player->edict()->v.punchangle = PunchAngle;
				}
			}
		}
	}
}
