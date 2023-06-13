#include "precompiled.h"

CAccuracyFix gAccuracyFix;

void CAccuracyFix::ServerActivate()
{
	this->m_Player.clear();
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
					if (!((BIT(WEAPON_NONE) | BIT(WEAPON_HEGRENADE) | BIT(WEAPON_C4) | BIT(WEAPON_SMOKEGRENADE) | BIT(WEAPON_FLASHBANG) | BIT(WEAPON_KNIFE)) & BIT(Player->m_pActiveItem->m_iId)))
					{
						CBasePlayerWeapon* Weapon = static_cast<CBasePlayerWeapon*>(Player->m_pActiveItem);

						if (Weapon)
						{
							if (!Weapon->m_iShotsFired || (gpGlobals->time >= Weapon->m_flNextPrimaryAttack))
							{
								this->m_Player[EntityIndex].m_Shooting++;

								bool IsWeaponShotGun = ((BIT(WEAPON_XM1014) | BIT(WEAPON_M3)) & BIT(Player->m_pActiveItem->m_iId));

								this->m_Player[EntityIndex].m_TM = this->m_Player[EntityIndex].m_Body;

								if (!IsWeaponShotGun || (IsWeaponShotGun && this->GetUserAiming(pentToSkip, &this->m_Player[EntityIndex].m_Target, &this->m_Player[EntityIndex].m_Body, 2000) && this->m_Player[EntityIndex].m_TM))
								{
									vec3_t vEnd;

									g_engfuncs.pfnMakeVectors(pentToSkip->v.v_angle);

									if (IsWeaponShotGun)
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

				if (this->m_Player[EntityIndex].m_Shooting > 0)
				{
					this->m_Player[EntityIndex].m_Shooting = 0;

					auto PunchAngle = Player->edict()->v.punchangle;

					PunchAngle = PunchAngle * Weapon->m_flAccuracy;

					Player->edict()->v.punchangle = PunchAngle;
				}
			}
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