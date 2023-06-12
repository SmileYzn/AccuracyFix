#include "precompiled.h"

CAccuracyFix gAccuracyFix;

void CAccuracyFix::ServerActivate()
{
	this->m_Player.clear();
}

void CAccuracyFix::CmdEnd(const edict_t* player)
{
	auto Player = UTIL_PlayerByIndexSafe(ENTINDEX(player));

	if (Player)
	{
		this->m_Player[Player->entindex()].m_LastFired[0] = Player->m_flLastFired;
	}
}

void CAccuracyFix::TraceLine(const float* start, const float* end, int fNoMonsters, edict_t* pentToSkip, TraceResult* ptr)
{
	auto EntityIndex = ENTINDEX(pentToSkip);

	auto Player = UTIL_PlayerByIndexSafe(EntityIndex);

	if (Player)
	{
		if (!Player->IsBot() && Player->m_pActiveItem)
		{
			this->m_Player[Player->entindex()].m_LastFired[1] = Player->m_flLastFired;

			if (Player->IsAlive() && !((BIT(WEAPON_NONE) | BIT(WEAPON_HEGRENADE) | BIT(WEAPON_C4) | BIT(WEAPON_SMOKEGRENADE) | BIT(WEAPON_FLASHBANG) | BIT(WEAPON_KNIFE)) & BIT(Player->m_pActiveItem->m_iId)) && fNoMonsters == IGNORE_MONSTERS::dont_ignore_monsters && (abs(this->m_Player[EntityIndex].m_LastFired[0] - this->m_Player[EntityIndex].m_LastFired[1]) >= 1.0f))
			{
				bool IsShotGun = ((BIT(WEAPON_XM1014) | BIT(WEAPON_M3)) & BIT(Player->m_pActiveItem->m_iId));

				this->m_Player[EntityIndex].m_TM = this->m_Player[EntityIndex].m_Body;

				/*if (aim_shotgun_ac_map_ents)
				{
					this->m_Player[EntityIndex].m_TM = this->m_Player[EntityIndex].m_Target;
				}*/

				if (!IsShotGun || (IsShotGun && this->GetUserAiming(pentToSkip, &this->m_Player[EntityIndex].m_Target, &this->m_Player[EntityIndex].m_Body, 2000) && this->m_Player[EntityIndex].m_TM))
				{
					vec3_t vEnd;

					g_engfuncs.pfnMakeVectors(pentToSkip->v.v_angle);

					if (IsShotGun)
					{
						vEnd = gpGlobals->v_forward * 2020.0f;
					}
					else
					{
						vEnd = gpGlobals->v_forward * 9999.0f;
					}

					vEnd[0] = start[0] + vEnd[0];

					vEnd[1] = start[1] + vEnd[1];

					vEnd[2] = start[2] + vEnd[2];

					g_engfuncs.pfnTraceLine(start, vEnd, fNoMonsters, pentToSkip, ptr);

					this->m_Player[EntityIndex].m_Shooting = true;

					this->m_Player[EntityIndex].m_PunchAngle = Player->edict()->v.punchangle;
				}
			}
			else
			{
				this->m_Player[EntityIndex].m_Shooting = false;
			} 
		}
	}
}

void CAccuracyFix::POST_CBasePlayer_PostThink(CBasePlayer* Player)
{
	if (!Player->IsBot())
	{
		auto EntityIndex = Player->entindex();

		if (this->m_Player[EntityIndex].m_Shooting)
		{
			auto PunchAngle = Player->edict()->v.punchangle;

			PunchAngle = PunchAngle - this->m_Player[EntityIndex].m_PunchAngle;

			PunchAngle = PunchAngle * 0.237f;

			PunchAngle = PunchAngle + this->m_Player[EntityIndex].m_PunchAngle;

			Player->edict()->v.punchangle = PunchAngle;

			this->m_Player[EntityIndex].m_Shooting = false;
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

		if (trEnd.flFraction < 1.0)
		{
			pFloat = (trEnd.vecEndPos - v_src).Length();
		}

		return pFloat;
	}

	*cpId = 0;
	*cpBody = 0;

	return pFloat;
}