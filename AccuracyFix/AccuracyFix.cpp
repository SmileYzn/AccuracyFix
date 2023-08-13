#include "precompiled.h"

CAccuracyFix gAccuracyFix;

void CAccuracyFix::ServerActivate()
{
#ifndef ACCURACY_DISABLE_RECOIL_CONTROL
	this->m_Data.clear();

	this->m_af_recoil_all = this->CvarRegister("af_recoil_all", "-1.0");
#endif

	this->m_af_accuracy_all = this->CvarRegister("af_accuracy_all", "-1.0");

	this->m_af_distance_all = this->CvarRegister("af_distance_all", "-1.0");

	for (int WeaponID = WEAPON_P228; WeaponID <= WEAPON_P90; WeaponID++)
	{
		auto SlotInfo = g_ReGameApi->GetWeaponSlot((WeaponIdType)WeaponID);

		if (SlotInfo)
		{
			if ((SlotInfo->slot == PRIMARY_WEAPON_SLOT) || (SlotInfo->slot == PISTOL_SLOT))
			{
				if (SlotInfo->weaponName)
				{
					char cvarName[32] = { 0 };

					Q_snprintf(cvarName, sizeof(cvarName), "af_accuracy_%s", SlotInfo->weaponName);

					this->m_af_accuracy[WeaponID] = this->CvarRegister(cvarName, "4096.0");

#ifndef ACCURACY_DISABLE_RECOIL_CONTROL
					Q_snprintf(cvarName, sizeof(cvarName), "af_recoil_%s", SlotInfo->weaponName);

					this->m_af_recoil[WeaponID] = this->CvarRegister(cvarName, "1.0");
#endif

					Q_snprintf(cvarName, sizeof(cvarName), "af_distance_%s", SlotInfo->weaponName);

					this->m_af_distance[WeaponID] = this->CvarRegister(cvarName, "4096.0");
				}
			}
		}
	}

	g_engfuncs.pfnServerCommand("exec addons/accuracyfix/accuracyfix.cfg\n");
	g_engfuncs.pfnServerExecute();
}

#ifndef ACCURACY_DISABLE_RECOIL_CONTROL
void CAccuracyFix::CmdEnd(const edict_t* pEdict)
{
	auto Player = UTIL_PlayerByIndexSafe(ENTINDEX(pEdict));

	if (Player)
	{
		if (Player->IsAlive())
		{
			this->m_Data[Player->entindex()].LastFired = Player->m_flLastFired;
		}
	}
}
#endif

bool CAccuracyFix::TraceLine(const float* start, const float* end, int fNoMonsters, edict_t* pentToSkip, TraceResult* ptr)
{
	auto Player = UTIL_PlayerByIndexSafe(ENTINDEX(pentToSkip));
	
	if (Player)
	{
		if (Player->IsAlive())
		{
			if (fNoMonsters == dont_ignore_monsters)
			{
				if (Player->m_pActiveItem)
				{
					if (!((BIT(WEAPON_NONE) | BIT(WEAPON_HEGRENADE) | BIT(WEAPON_C4) | BIT(WEAPON_SMOKEGRENADE) | BIT(WEAPON_FLASHBANG) | BIT(WEAPON_KNIFE)) & BIT(Player->m_pActiveItem->m_iId)))
					{
#ifndef ACCURACY_DISABLE_RECOIL_CONTROL
						auto EntityIndex = Player->entindex();

						if ((Player->edict()->v.button & IN_ATTACK) && (Player->m_flLastFired != this->m_Data[EntityIndex].LastFired))
						{
							this->m_Data[EntityIndex].LastFired = Player->m_flLastFired;

							this->m_Data[EntityIndex].WeaponId = Player->m_pActiveItem->m_iId;
						}
#endif

						auto aimDistance = this->m_af_distance[Player->m_pActiveItem->m_iId]->value;

						if (this->m_af_accuracy_all->value > 0)
						{
							aimDistance = this->m_af_accuracy_all->value;
						}

						int TargetIndex = 0, HitBoxPlace = 0;

						if (this->GetUserAiming(pentToSkip, &TargetIndex, &HitBoxPlace, aimDistance) > 0.0f)
						{
							if (TargetIndex)
							{
								if (HitBoxPlace)
								{
									auto fwdDistance = this->m_af_accuracy[Player->m_pActiveItem->m_iId]->value;

									if (fwdDistance > 0.0f)
									{
										if (this->m_af_accuracy_all->value > 0.0f)
										{
											fwdDistance = this->m_af_accuracy_all->value;
										}

										g_engfuncs.pfnMakeVectors(pentToSkip->v.v_angle);

										Vector vEnd = Vector(0.0f, 0.0f, 0.0f);

										vEnd = gpGlobals->v_forward * fwdDistance;

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
	}

	return false;
}

#ifndef ACCURACY_DISABLE_RECOIL_CONTROL
void CAccuracyFix::PostThink(CBasePlayer* Player)
{
	if (Player->IsAlive())
	{
		auto EntityIndex = Player->entindex();

		if (this->m_Data[EntityIndex].WeaponId != WEAPON_NONE)
		{
			auto Recoil = this->m_af_recoil[this->m_Data[EntityIndex].WeaponId]->value;

			if (Recoil > 0.0f)
			{
				if (this->m_af_recoil_all->value > 0.0f)
				{
					Recoil = this->m_af_recoil_all->value;
				}

				auto PunchAngle = Player->edict()->v.punchangle;

				PunchAngle = PunchAngle * Recoil;

				Player->edict()->v.punchangle = PunchAngle;
			}

			this->m_Data[EntityIndex].WeaponId = WEAPON_NONE;
		}
	}
}
#endif

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

cvar_t* CAccuracyFix::CvarRegister(const char* Name, const char* Value)
{
	cvar_t* Pointer = g_engfuncs.pfnCVarGetPointer(Name);

	if (!Pointer)
	{
		this->m_Cvar[Name].name = Name;

		this->m_Cvar[Name].string = (char*)(Value);

		this->m_Cvar[Name].flags = (FCVAR_SERVER | FCVAR_SPONLY | FCVAR_UNLOGGED);

		g_engfuncs.pfnCVarRegister(&this->m_Cvar[Name]);

		Pointer = g_engfuncs.pfnCVarGetPointer(this->m_Cvar[Name].name);

		if (Pointer)
		{
			g_engfuncs.pfnCvar_DirectSet(Pointer, Value);
		}
	}

	return Pointer;
}