#include "precompiled.h"

CAccuracyFix gAccuracyFix;

void CAccuracyFix::ServerActivate()
{
	this->m_Data.clear();
}

void CAccuracyFix::CmdEnd(const edict_t* pEdict)
{
	auto Player = UTIL_PlayerByIndexSafe(ENTINDEX(pEdict));

	if (Player)
	{
		if (Player->IsAlive() && Player->IsPlayer() && !Player->IsBot())
		{
			this->m_Data[Player->entindex()].LastFired = Player->m_flLastFired;
		}
	}
}

bool CAccuracyFix::TraceLine(const float* start, const float* end, int fNoMonsters, edict_t* pentToSkip, TraceResult* ptr)
{
	auto Player = UTIL_PlayerByIndexSafe(ENTINDEX(pentToSkip));
	
	if (Player)
	{
		if (Player->IsAlive() && Player->IsPlayer() && !Player->IsBot())
		{
			if (fNoMonsters == dont_ignore_monsters)
			{
				if (Player->m_pActiveItem)
				{
					auto EntityIndex = Player->entindex();

					if (!((BIT(WEAPON_NONE) | BIT(WEAPON_HEGRENADE) | BIT(WEAPON_XM1014) | BIT(WEAPON_C4) | BIT(WEAPON_SMOKEGRENADE) | BIT(WEAPON_M3) | BIT(WEAPON_FLASHBANG) | BIT(WEAPON_KNIFE)) & BIT(Player->m_pActiveItem->m_iId)))
					{
						CBasePlayerWeapon* Weapon = static_cast<CBasePlayerWeapon*>(Player->m_pActiveItem);

						if (Weapon)
						{
							if ((Player->edict()->v.button & IN_ATTACK) && ((Player->m_flLastFired - this->m_Data[EntityIndex].LastFired) >= 1.0f))
							{
								this->m_Data[EntityIndex].LastFired = Player->m_flLastFired;

								this->m_Data[EntityIndex].ShotsFired++;

								this->m_Data[EntityIndex].m_TM = this->m_Data[EntityIndex].m_Body;

								if(this->GetUserAiming(pentToSkip, &this->m_Data[EntityIndex].m_Target, &this->m_Data[EntityIndex].m_Body, 2000) && this->m_Data[EntityIndex].m_TM)
								{
									Vector vEnd = Vector(0, 0, 0);

									g_engfuncs.pfnMakeVectors(pentToSkip->v.v_angle);

									vEnd = gpGlobals->v_forward * 9999;

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
		}
	}

	return false;
}

void CAccuracyFix::PostThink(CBasePlayer* Player)
{
	if (Player->IsAlive() && Player->IsPlayer() && !Player->IsBot())
	{
		auto EntityIndex = Player->entindex();

		if (this->m_Data[EntityIndex].ShotsFired > 0)
		{
			auto PunchAngle = Player->edict()->v.punchangle;

			PunchAngle = PunchAngle * 0.237f;

			Player->edict()->v.punchangle = PunchAngle;

			this->m_Data[EntityIndex].ShotsFired = 0;
		}
	}
}

float CAccuracyFix::GetUserAiming(edict_t* edict, int* cpId, int* cpBody, float distance)
{
	float pFloat = 0.0f;

	auto Entityindex = ENTINDEX(edict);

	if (Entityindex > 0 && Entityindex <= gpGlobals->maxClients)
	{
		Vector v_forward;

		Vector v_src = edict->v.origin + edict->v.view_ofs;

		g_engfuncs.pfnAngleVectors(edict->v.v_angle, v_forward, NULL, NULL);

		TraceResult trEnd;

		Vector v_dest = v_src + v_forward * distance;

		g_engfuncs.pfnTraceLine(v_src, v_dest, 0, edict, &trEnd);

		*cpId = FNullEnt(trEnd.pHit) ? 0 : ENTINDEX(trEnd.pHit);

		*cpBody = trEnd.iHitgroup;

		if (trEnd.flFraction < 1.0f)
		{
			pFloat = (trEnd.vecEndPos - v_src).Length();
		}

		return pFloat;
	}

	*cpId = 0;

	*cpBody = 0;

	return pFloat;
}