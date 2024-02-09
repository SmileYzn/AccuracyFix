#include "precompiled.h"

CAccuracyFix gAccuracyFix;

void CAccuracyFix::ServerActivate()
{
	this->m_af_accuracy_all = gAccuracyUtil.CvarRegister("af_accuracy_all", "-1.0");

	this->m_af_distance_all = gAccuracyUtil.CvarRegister("af_distance_all", "-1.0");

#ifdef ACCURACY_ENABLE_RECOIL_CONTROL
	this->m_Data.clear();

	this->m_af_recoil_all = gAccuracyUtil.CvarRegister("af_recoil_all", "-1.0");
#endif

	for (int WeaponID = WEAPON_P228; WeaponID <= WEAPON_P90; WeaponID++)
	{
		auto SlotInfo = g_ReGameApi->GetWeaponSlot((WeaponIdType)WeaponID);

		if (SlotInfo)
		{
			if ((SlotInfo->slot == PRIMARY_WEAPON_SLOT) || (SlotInfo->slot == PISTOL_SLOT))
			{
				if (SlotInfo->weaponName)
				{
					if (SlotInfo->weaponName[0u] != '\0')
					{
						std::string cvarName = "af_distance_";

						cvarName.append(SlotInfo->weaponName);

						this->m_af_distance[WeaponID] = gAccuracyUtil.CvarRegister(cvarName.c_str(), "8192.0");

						cvarName = "af_accuracy_";

						cvarName.append(SlotInfo->weaponName);

						this->m_af_accuracy[WeaponID] = gAccuracyUtil.CvarRegister(cvarName.c_str(), "9999.0");

#ifdef ACCURACY_ENABLE_RECOIL_CONTROL
						cvarName = "af_recoil_";

						cvarName.append(SlotInfo->weaponName);

						this->m_af_recoil[WeaponID] = gAccuracyUtil.CvarRegister(cvarName.c_str(), "1.0");
#endif
					}
				}
			}
		}
	}

	gAccuracyUtil.ServerCommand("exec %s/accuracyfix.cfg", gAccuracyUtil.GetPath());
}

#ifdef ACCURACY_ENABLE_RECOIL_CONTROL
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

void CAccuracyFix::TraceLine(const float* vStart, const float* vEnd, int fNoMonsters, edict_t* pentToSkip, TraceResult* ptr)
{
	if (fNoMonsters == dont_ignore_monsters)
	{
		if (!FNullEnt(pentToSkip))
		{
			auto EntityIndex = g_engfuncs.pfnIndexOfEdict(pentToSkip);

			if (EntityIndex > 0 && EntityIndex <= gpGlobals->maxClients)
			{
				auto Player = UTIL_PlayerByIndexSafe(EntityIndex);

				if (Player)
				{
					if (Player->IsAlive())
					{
						if (Player->m_pActiveItem)
						{
							if ((Player->m_pActiveItem->iItemSlot() == PRIMARY_WEAPON_SLOT) || (Player->m_pActiveItem->iItemSlot() == PISTOL_SLOT))
							{
#ifdef ACCURACY_ENABLE_RECOIL_CONTROL
								if ((Player->edict()->v.button & IN_ATTACK) && (Player->m_flLastFired != this->m_Data[EntityIndex].LastFired))
								{
									this->m_Data[EntityIndex].LastFired = Player->m_flLastFired;

									this->m_Data[EntityIndex].WeaponId = Player->m_pActiveItem->m_iId;
								}
#endif
								auto DistanceLimit = this->m_af_distance[Player->m_pActiveItem->m_iId]->value;

								if (this->m_af_distance_all->value > 0)
								{
									DistanceLimit = this->m_af_distance_all->value;
								}

								if (DistanceLimit > 0.0f)
								{
									auto trResult = gAccuracyUtil.GetUserAiming(pentToSkip, DistanceLimit);

									if (!FNullEnt(trResult.pHit))
									{
										auto TargetIndex = ENTINDEX(trResult.pHit);

										if (TargetIndex > 0 && TargetIndex <= gpGlobals->maxClients)
										{
											auto fwdVelocity = this->m_af_accuracy[Player->m_pActiveItem->m_iId]->value;

											if (this->m_af_accuracy_all->value > 0.0f)
											{
												fwdVelocity = this->m_af_accuracy_all->value;
											}

											g_engfuncs.pfnMakeVectors(pentToSkip->v.v_angle);

											auto vEndRes = Vector
											(
												(vStart[0] + (gpGlobals->v_forward[0] * fwdVelocity)),
												(vStart[1] + (gpGlobals->v_forward[1] * fwdVelocity)),
												(vStart[2] + (gpGlobals->v_forward[2] * fwdVelocity))
											);

											g_engfuncs.pfnTraceLine(vStart, vEndRes, fNoMonsters, pentToSkip, ptr);
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

#ifdef ACCURACY_ENABLE_RECOIL_CONTROL
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
