#include "precompiled.h"

CAccuracyFix gAccuracyFix;

void CAccuracyFix::ServerActivate()
{
	memset(this->m_Shooting, 0, sizeof(m_Shooting));
}

void CAccuracyFix::CmdEnd(const edict_t* pEdict)
{
	auto Player = UTIL_PlayerByIndexSafe(ENTINDEX(pEdict));

	if (Player)
	{
		this->m_LastFired[Player->entindex()] = Player->m_flLastFired;
	}
}


bool CAccuracyFix::TraceLine(const float* start, const float* end, int fNoMonsters, edict_t* pentToSkip, TraceResult* ptr)
{
	auto Player = UTIL_PlayerByIndexSafe(ENTINDEX(pentToSkip));

	if (Player)
	{
		auto EntityIndex = Player->entindex();

		if (Player->IsAlive())
		{
			if (Player->m_pActiveItem)
			{
				if ((fNoMonsters == IGNORE_MONSTERS::dont_ignore_monsters))
				{
					if (!((BIT(WEAPON_NONE) | BIT(WEAPON_HEGRENADE) | BIT(WEAPON_XM1014) | BIT(WEAPON_C4) | BIT(WEAPON_SMOKEGRENADE) | BIT(WEAPON_M3) | BIT(WEAPON_FLASHBANG) | BIT(WEAPON_KNIFE)) & BIT(Player->m_pActiveItem->m_iId)))
					{
						if ((Player->m_flLastFired - this->m_LastFired[EntityIndex]) > 0.8f)
						{
							this->m_Shooting[EntityIndex] = true;

							this->m_LastFired[EntityIndex] = Player->m_flLastFired;

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

void CAccuracyFix::POST_CBasePlayer_PostThink(CBasePlayer* Player)
{
	if (Player->IsAlive())
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
