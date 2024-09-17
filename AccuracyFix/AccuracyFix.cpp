#include "precompiled.h"

CAccuracyFix gAccuracyFix;

void CAccuracyFix::ServerActivate()
{
	/*this->m_af_accuracy_all = gAccuracyUtil.CvarRegister("af_accuracy_all", "-1.0");

	this->m_af_distance_all = gAccuracyUtil.CvarRegister("af_distance_all", "-1.0");

	this->m_af_jump_fix = gAccuracyUtil.CvarRegister("af_jump_fix", "0");

	char cvarName[64] = { 0 };

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
						Q_snprintf(cvarName, sizeof(cvarName), "af_distance_%s", SlotInfo->weaponName);

						this->m_af_distance[WeaponID] = gAccuracyUtil.CvarRegister(cvarName, "8192.0");

						Q_snprintf(cvarName, sizeof(cvarName), "af_accuracy_%s", SlotInfo->weaponName);

						this->m_af_accuracy[WeaponID] = gAccuracyUtil.CvarRegister(cvarName, "9999.0");
					}
				}
			}
		}
	}

	auto Path = gAccuracyUtil.GetPath();

	if (Path)
	{
		if (Path[0u] != '\0')
		{
			gAccuracyUtil.ServerCommand("exec %s/accuracyfix.cfg", Path);
		}
	}*/
}

void CAccuracyFix::TraceLine(const float* vStart, const float* vEnd, int fNoMonsters, edict_t* pentToSkip, TraceResult* ptr)
{
	/*if ((fNoMonsters == dont_ignore_monsters) && (gpGlobals->trace_flags != FTRACE_FLASH))
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
								auto DistanceLimit = this->m_af_distance[Player->m_pActiveItem->m_iId]->value;

								if (this->m_af_distance_all->value > 0)
								{
									DistanceLimit = this->m_af_distance_all->value;
								}

								if (DistanceLimit > 0.0f)
								{
									if ((this->m_af_jump_fix->value > 0) || (Player->pev->flags & FL_ONGROUND))
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
	
												auto vEndRes = (Vector)vStart + gpGlobals->v_forward * fwdVelocity;

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
	}*/
}

